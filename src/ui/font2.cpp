// Slice font2 (docs/ANALYSIS/20_menu_ui.md sections 4-5): the font renderer of frFont.c / frFontEx.c / frFontRaster.c /
// fmGslCont.c -- the font table and styles, the glyph cache, glyph lists, the layout loop and its helpers, the
// typewriter reveal, the raster-slot pool and the GS list -- four frTagTable.c handlers, and the still-recompiled
// game functions of the sprite / cursor band 0x100000-0x11FFFF: the H_Cursor destroy callback, the pad layer, the
// debug print, the bust-up portraits, the fade draw, sound-state leaves, the TMX texture loader, the cut-in player and
// the persona effects, sprFontInit and a one-shot sprite draw.
//
// Hand-decompiled from SLUS_216.21 on p3fes_handgen bodies (docs/PHASE5_AGENT_BRIEF.md "Using p3fes_handgen"): every
// body keeps the recompiled body's registers, frame, spills, $ra links, cycle charges and check points
// (game/include/p3fes/game/hg_cpu.h). On top: a role comment per function ([proposed names] in brackets, also in
// symbols/deltas/font2.sym), the named globals and record offsets of font2.h (each constant equals the literal it
// replaced), and block comments where the control flow is not obvious.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/font2.h"

namespace p3fes::recomp_gen {
void fn_H_Cdvd_ArchiveGetFile_00102100(p3fes::EEContext&);
void fn_H_Cdvd_CacheAddArchive_00102720(p3fes::EEContext&);
void fn_H_Cdvd_CacheFindFile_001021c0(p3fes::EEContext&);
void fn_H_Cdvd_CacheRemove_00102870(p3fes::EEContext&);
void fn_H_Cdvd_Destroy_00100ec0(p3fes::EEContext&);
void fn_H_Cdvd_GetArchiveFileBuffer_001022e0(p3fes::EEContext&);
void fn_H_Cdvd_IsFileLoaded_001016b0(p3fes::EEContext&);
void fn_H_Cdvd_ReadSync_001023a0(p3fes::EEContext&);
void fn_H_Cdvd_Request_00100d80(p3fes::EEContext&);
void fn_H_Cursor_DestroyDrawTask_00100580(p3fes::EEContext&);
void fn_H_Fade_DrawBlue_001075b0(p3fes::EEContext&);
void fn_H_Fade_DrawColour_001081e0(p3fes::EEContext&);
void fn_H_Fade_DrawWhite_001078a0(p3fes::EEContext&);
void fn_H_Pad_UpdateWorkPad_00103110(p3fes::EEContext&);
void fn_RpSkyRenderStateSet_004d7f60(p3fes::EEContext&);
void fn_clndGetCurrentWeekDay_0017db00(p3fes::EEContext&);
void fn_clndIsDateInRange_0017e480(p3fes::EEContext&);
void fn_cosf_0052e6d8(p3fes::EEContext&);
void fn_datGetFlag_0016f190(p3fes::EEContext&);
void fn_datSetFlag_0016f1f0(p3fes::EEContext&);
void fn_expl_4_0054d148(p3fes::EEContext&);
void fn_fmGslDecodeGlyph_003b47b0(p3fes::EEContext&);
void fn_fmGslGetGlyphBlocks_003b4770(p3fes::EEContext&);
void fn_fmGslReleaseEntry_003b4580(p3fes::EEContext&);
void fn_fptodp_00530da0(p3fes::EEContext&);
void fn_frAddFontStyle_003afad0(p3fes::EEContext&);
void fn_frFontBuildGlyphList_003b0970(p3fes::EEContext&);
void fn_frFontCacheGlyph_003b0430(p3fes::EEContext&);
void fn_frFontCreateGlyphNode_003b0620(p3fes::EEContext&);
void fn_frFontGetStyleGlyphHeight_003b1a40(p3fes::EEContext&);
void fn_frFontGetStyleGlyphWidth_003b1a10(p3fes::EEContext&);
void fn_frFontInitLineNode_003b05c0(p3fes::EEContext&);
void fn_frFontKerningAdjust_003b0840(p3fes::EEContext&);
void fn_frFontLineChainJoin_003b1920(p3fes::EEContext&);
void fn_frFontLineSetAlpha_003b0bb0(p3fes::EEContext&);
void fn_frFontPrintClutData_003aff50(p3fes::EEContext&);
void fn_frFontRasterAllocSlot_003b3e60(p3fes::EEContext&);
void fn_frFontRasterCreate2_003b3f90(p3fes::EEContext&);
void fn_frFontRasterCreate_003b35e0(p3fes::EEContext&);
void fn_frFontRasterFindOrAlloc_003b3d60(p3fes::EEContext&);
void fn_frFontRasterFind_003b3dd0(p3fes::EEContext&);
void fn_frFontRegisterGlyphRaster_003b03a0(p3fes::EEContext&);
void fn_frFreeFontStyles_003afe30(p3fes::EEContext&);
void fn_frInitFontTable_003af7a0(p3fes::EEContext&);
void fn_frLoadFontData_003afc70(p3fes::EEContext&);
void fn_kwlnTaskCreateWithAutoPriority_00194b80(p3fes::EEContext&);
void fn_kwlnTaskCreate_00194b20(p3fes::EEContext&);
void fn_kwlnTaskDestroyWithHierarchy_00195020(p3fes::EEContext&);
void fn_kwlnTaskGetState_00195290(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_nullsub_1_001007f0(p3fes::EEContext&);
void fn_printf_005225a8(p3fes::EEContext&);
void fn_rbAlloc_003b46b0(p3fes::EEContext&);
void fn_rbFree_003b46f0(p3fes::EEContext&);
void fn_sinf_0052e878(p3fes::EEContext&);
void fn_sprAddFile_00112370(p3fes::EEContext&);
void fn_sprCreateHandleFromData_00112420(p3fes::EEContext&);
void fn_sprCreateHandle_001158b0(p3fes::EEContext&);
void fn_sprFileIsReady_00111f30(p3fes::EEContext&);
void fn_sprFontInit_00111f50(p3fes::EEContext&);
void fn_sprintf_00523ac8(p3fes::EEContext&);
void fn_strcat_00523e68(p3fes::EEContext&);
void fn_strcmp_00524128(p3fes::EEContext&);
void fn_strcpy_00524270(p3fes::EEContext&);
void fn_strlen_00524388(p3fes::EEContext&);
void fn_sub_103580_00103580(p3fes::EEContext&);
void fn_sub_103650_00103650(p3fes::EEContext&);
void fn_sub_1038D0_001038d0(p3fes::EEContext&);
void fn_sub_103990_00103990(p3fes::EEContext&);
void fn_sub_103B10_00103b10(p3fes::EEContext&);
void fn_sub_103CF0_00103cf0(p3fes::EEContext&);
void fn_sub_1040F0_001040f0(p3fes::EEContext&);
void fn_sub_1042E0_001042e0(p3fes::EEContext&);
void fn_sub_1043B0_001043b0(p3fes::EEContext&);
void fn_sub_104EB0_00104eb0(p3fes::EEContext&);
void fn_sub_104FD0_00104fd0(p3fes::EEContext&);
void fn_sub_105210_00105210(p3fes::EEContext&);
void fn_sub_105800_00105800(p3fes::EEContext&);
void fn_sub_1058A0_001058a0(p3fes::EEContext&);
void fn_sub_1059B0_001059b0(p3fes::EEContext&);
void fn_sub_106730_00106730(p3fes::EEContext&);
void fn_sub_106860_00106860(p3fes::EEContext&);
void fn_sub_106E90_00106e90(p3fes::EEContext&);
void fn_sub_106EC0_00106ec0(p3fes::EEContext&);
void fn_sub_106F30_00106f30(p3fes::EEContext&);
void fn_sub_106F60_00106f60(p3fes::EEContext&);
void fn_sub_106FB0_00106fb0(p3fes::EEContext&);
void fn_sub_106FF0_00106ff0(p3fes::EEContext&);
void fn_sub_107060_00107060(p3fes::EEContext&);
void fn_sub_1071F0_001071f0(p3fes::EEContext&);
void fn_sub_107B20_00107b20(p3fes::EEContext&);
void fn_sub_108680_00108680(p3fes::EEContext&);
void fn_sub_108E50_00108e50(p3fes::EEContext&);
void fn_sub_109040_00109040(p3fes::EEContext&);
void fn_sub_109170_00109170(p3fes::EEContext&);
void fn_sub_1099A0_001099a0(p3fes::EEContext&);
void fn_sub_1099D0_001099d0(p3fes::EEContext&);
void fn_sub_10A4E0_0010a4e0(p3fes::EEContext&);
void fn_sub_10A500_0010a500(p3fes::EEContext&);
void fn_sub_10A6D0_0010a6d0(p3fes::EEContext&);
void fn_sub_10C1A0_0010c1a0(p3fes::EEContext&);
void fn_sub_10C3A0_0010c3a0(p3fes::EEContext&);
void fn_sub_10DD10_0010dd10(p3fes::EEContext&);
void fn_sub_10DDC0_0010ddc0(p3fes::EEContext&);
void fn_sub_10DE40_0010de40(p3fes::EEContext&);
void fn_sub_10DEE0_0010dee0(p3fes::EEContext&);
void fn_sub_10DF60_0010df60(p3fes::EEContext&);
void fn_sub_10E010_0010e010(p3fes::EEContext&);
void fn_sub_10E0D0_0010e0d0(p3fes::EEContext&);
void fn_sub_10E500_0010e500(p3fes::EEContext&);
void fn_sub_10E5F0_0010e5f0(p3fes::EEContext&);
void fn_sub_10EC50_0010ec50(p3fes::EEContext&);
void fn_sub_10F6C0_0010f6c0(p3fes::EEContext&);
void fn_sub_1102E0_001102e0(p3fes::EEContext&);
void fn_sub_1103E0_001103e0(p3fes::EEContext&);
void fn_sub_1104B0_001104b0(p3fes::EEContext&);
void fn_sub_1104D0_001104d0(p3fes::EEContext&);
void fn_sub_110510_00110510(p3fes::EEContext&);
void fn_sub_1105D0_001105d0(p3fes::EEContext&);
void fn_sub_110620_00110620(p3fes::EEContext&);
void fn_sub_110650_00110650(p3fes::EEContext&);
void fn_sub_1107D0_001107d0(p3fes::EEContext&);
void fn_sub_110E70_00110e70(p3fes::EEContext&);
void fn_sub_111150_00111150(p3fes::EEContext&);
void fn_sub_111260_00111260(p3fes::EEContext&);
void fn_sub_111380_00111380(p3fes::EEContext&);
void fn_sub_1114B0_001114b0(p3fes::EEContext&);
void fn_sub_111500_00111500(p3fes::EEContext&);
void fn_sub_111520_00111520(p3fes::EEContext&);
void fn_sub_111530_00111530(p3fes::EEContext&);
void fn_sub_111570_00111570(p3fes::EEContext&);
void fn_sub_1115B0_001115b0(p3fes::EEContext&);
void fn_sub_1115E0_001115e0(p3fes::EEContext&);
void fn_sub_111D60_00111d60(p3fes::EEContext&);
void fn_sub_1120C0_001120c0(p3fes::EEContext&);
void fn_sub_1124B0_001124b0(p3fes::EEContext&);
void fn_sub_1127D0_001127d0(p3fes::EEContext&);
void fn_sub_113A30_00113a30(p3fes::EEContext&);
void fn_sub_115350_00115350(p3fes::EEContext&);
void fn_sub_115980_00115980(p3fes::EEContext&);
void fn_sub_115CD0_00115cd0(p3fes::EEContext&);
void fn_sub_115F00_00115f00(p3fes::EEContext&);
void fn_sub_1165C0_001165c0(p3fes::EEContext&);
void fn_sub_1166A0_001166a0(p3fes::EEContext&);
void fn_sub_116760_00116760(p3fes::EEContext&);
void fn_sub_116780_00116780(p3fes::EEContext&);
void fn_sub_1167A0_001167a0(p3fes::EEContext&);
void fn_sub_1167C0_001167c0(p3fes::EEContext&);
void fn_sub_1167F0_001167f0(p3fes::EEContext&);
void fn_sub_116CF0_00116cf0(p3fes::EEContext&);
void fn_sub_116E20_00116e20(p3fes::EEContext&);
void fn_sub_116ED0_00116ed0(p3fes::EEContext&);
void fn_sub_116EF0_00116ef0(p3fes::EEContext&);
void fn_sub_116F10_00116f10(p3fes::EEContext&);
void fn_sub_116F20_00116f20(p3fes::EEContext&);
void fn_sub_116F30_00116f30(p3fes::EEContext&);
void fn_sub_116F50_00116f50(p3fes::EEContext&);
void fn_sub_116F80_00116f80(p3fes::EEContext&);
void fn_sub_117440_00117440(p3fes::EEContext&);
void fn_sub_117470_00117470(p3fes::EEContext&);
void fn_sub_117490_00117490(p3fes::EEContext&);
void fn_sub_117540_00117540(p3fes::EEContext&);
void fn_sub_1191C0_001191c0(p3fes::EEContext&);
void fn_sub_1192B0_001192b0(p3fes::EEContext&);
void fn_sub_119380_00119380(p3fes::EEContext&);
void fn_sub_1193A0_001193a0(p3fes::EEContext&);
void fn_sub_1193C0_001193c0(p3fes::EEContext&);
void fn_sub_1193D0_001193d0(p3fes::EEContext&);
void fn_sub_119930_00119930(p3fes::EEContext&);
void fn_sub_119960_00119960(p3fes::EEContext&);
void fn_sub_133D30_00133d30(p3fes::EEContext&);
void fn_sub_16C6F0_0016c6f0(p3fes::EEContext&);
void fn_sub_16C740_0016c740(p3fes::EEContext&);
void fn_sub_16C790_0016c790(p3fes::EEContext&);
void fn_sub_16C920_0016c920(p3fes::EEContext&);
void fn_sub_16DD40_0016dd40(p3fes::EEContext&);
void fn_sub_16E2B0_0016e2b0(p3fes::EEContext&);
void fn_sub_171C40_00171c40(p3fes::EEContext&);
void fn_sub_172C50_00172c50(p3fes::EEContext&);
void fn_sub_1738D0_001738d0(p3fes::EEContext&);
void fn_sub_17C7F0_0017c7f0(p3fes::EEContext&);
void fn_sub_17D800_0017d800(p3fes::EEContext&);
void fn_sub_18B700_0018b700(p3fes::EEContext&);
void fn_sub_18BC10_0018bc10(p3fes::EEContext&);
void fn_sub_198590_00198590(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_34FCD0_0034fcd0(p3fes::EEContext&);
void fn_sub_34FCF0_0034fcf0(p3fes::EEContext&);
void fn_sub_35AC50_0035ac50(p3fes::EEContext&);
void fn_sub_35AE90_0035ae90(p3fes::EEContext&);
void fn_sub_3AE000_003ae000(p3fes::EEContext&);
void fn_sub_3AE420_003ae420(p3fes::EEContext&);
void fn_sub_3AEE20_003aee20(p3fes::EEContext&);
void fn_sub_3AF110_003af110(p3fes::EEContext&);
void fn_sub_3B0030_003b0030(p3fes::EEContext&);
void fn_sub_3B0F50_003b0f50(p3fes::EEContext&);
void fn_sub_3B1710_003b1710(p3fes::EEContext&);
void fn_sub_3B1D90_003b1d90(p3fes::EEContext&);
void fn_sub_3B2020_003b2020(p3fes::EEContext&);
void fn_sub_3B22A0_003b22a0(p3fes::EEContext&);
void fn_sub_3B2430_003b2430(p3fes::EEContext&);
void fn_sub_3B41A0_003b41a0(p3fes::EEContext&);
void fn_sub_3B44A0_003b44a0(p3fes::EEContext&);
void fn_sub_3B45F0_003b45f0(p3fes::EEContext&);
void fn_sub_3B4B40_003b4b40(p3fes::EEContext&);
void fn_sub_3B4D10_003b4d10(p3fes::EEContext&);
void fn_sub_4A5470_004a5470(p3fes::EEContext&);
void fn_sub_4A5540_004a5540(p3fes::EEContext&);
void fn_sub_4A5DD0_004a5dd0(p3fes::EEContext&);
void fn_sub_4A6200_004a6200(p3fes::EEContext&);
void fn_sub_4A62E0_004a62e0(p3fes::EEContext&);
void fn_sub_4A6600_004a6600(p3fes::EEContext&);
void fn_sub_4A9BF0_004a9bf0(p3fes::EEContext&);
void fn_sub_4A9F20_004a9f20(p3fes::EEContext&);
void fn_sub_4AA390_004aa390(p3fes::EEContext&);
void fn_sub_4AA3D0_004aa3d0(p3fes::EEContext&);
void fn_sub_4AA410_004aa410(p3fes::EEContext&);
void fn_sub_4AAA60_004aaa60(p3fes::EEContext&);
void fn_sub_4AAD50_004aad50(p3fes::EEContext&);
void fn_sub_4AAE00_004aae00(p3fes::EEContext&);
void fn_sub_4AB1B0_004ab1b0(p3fes::EEContext&);
void fn_sub_4AB200_004ab200(p3fes::EEContext&);
void fn_sub_4AB2C0_004ab2c0(p3fes::EEContext&);
void fn_sub_4AB410_004ab410(p3fes::EEContext&);
void fn_sub_4AB6A0_004ab6a0(p3fes::EEContext&);
void fn_sub_4AC120_004ac120(p3fes::EEContext&);
void fn_sub_4AC390_004ac390(p3fes::EEContext&);
void fn_sub_4AC570_004ac570(p3fes::EEContext&);
void fn_sub_4AC5F0_004ac5f0(p3fes::EEContext&);
void fn_sub_4AC710_004ac710(p3fes::EEContext&);
void fn_sub_4ACE70_004ace70(p3fes::EEContext&);
void fn_sub_4B4410_004b4410(p3fes::EEContext&);
void fn_sub_4C5250_004c5250(p3fes::EEContext&);
void fn_sub_4C5780_004c5780(p3fes::EEContext&);
void fn_sub_4C58A0_004c58a0(p3fes::EEContext&);
void fn_sub_4CBE00_004cbe00(p3fes::EEContext&);
void fn_sub_4CBEB0_004cbeb0(p3fes::EEContext&);
void fn_sub_4CBF20_004cbf20(p3fes::EEContext&);
void fn_sub_4CCAC0_004ccac0(p3fes::EEContext&);
void fn_sub_4CDCE0_004cdce0(p3fes::EEContext&);
void fn_sub_4CDE00_004cde00(p3fes::EEContext&);
void fn_sub_4CDE40_004cde40(p3fes::EEContext&);
void fn_sub_4CDF30_004cdf30(p3fes::EEContext&);
void fn_sub_4CE0F0_004ce0f0(p3fes::EEContext&);
void fn_sub_4CE200_004ce200(p3fes::EEContext&);
void fn_sub_4D0F00_004d0f00(p3fes::EEContext&);
void fn_vsprintf_005288c8(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace font2;  // the named globals and record offsets of font2.h

// 0x00100580 H_Cursor_DestroyDrawTask -- 44 bytes; frame 0x10: ra sp+0x0
// Destroy callback of the "H CURSOR Draw" task: frees the task's 0x150-byte work block (task +0x3C) through the
// RwFree slot 0x96017C. Returns RwFree's $v0.
void H_Cursor_DestroyDrawTask(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00100580
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, task::kWork);
    v0 = 0x960000;
    lw(v0, v0, rw::kFree);  // 0x96017C
    jalr(ctx, 0x100594u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001007F0 nullsub_1 -- 8 bytes; leaf frame (no stack)
// [dbgPrintFontLoaded] Empty in retail (a `jr $ra`): sub_1042E0 calls it right after the debug font raster is built.
void nullsub_1(EEContext& ctx) {
    using namespace hg;
    // 0x001007f0
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x00103580 sub_103580 -- 196 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [H_Pad_UpdateAll] The per-frame pad update (kwlnUpdate, kwlnRootUpdateTask): for both ports H_Pad_UpdateWorkPad(pad
// work + 54 * port) and the derived button words (sub_103650); then clears the five frame-edge words of the shared
// pad block (0x7E09F2..0x7E09FE), sets the four analogue bytes 0x7E0A04..0x7E0A07 to the centre 0x80 and steps the
// vibration (sub_103B10).
void sub_103580(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00103580
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = 0;
    for (;;) {
        // 0x001035d0
        charge(ctx, 3);
        v0 = slti(s0, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00103598
        charge(ctx, 14);
        v0 = sll(s0, 3);
        v1 = addu(v0, s0);
        v0 = sll(v1, 2);
        v0 = subu(v0, v1);
        v1 = sll(v0, 1);
        v0 = 0x7E0000;
        v0 = addiu(v0, pad::kLoWorkBase);  // &0x7E09B0
        a0 = addu(v0, v1);
        jal(ctx, 0x1035B8u, gen::fn_H_Pad_UpdateWorkPad_00103110);
        a0 = s0;
        jal(ctx, 0x1035C4u, gen::fn_sub_103650_00103650);
        s0 = addiu(s0, 1);
    }
    // 0x001035dc
    charge(ctx, 26);
    v0 = 0x7E0000;
    sh(zero, v0, pad::kLoEdge0);  // 0x7E09F2
    v0 = 0x7E0000;
    sh(zero, v0, pad::kLoEdge1);  // 0x7E09F4
    v0 = 0x7E0000;
    sh(zero, v0, pad::kLoEdge3);  // 0x7E09FC
    v0 = 0x7E0000;
    sh(zero, v0, pad::kLoEdge4);  // 0x7E09FE
    v0 = 0x7E0000;
    sh(zero, v0, pad::kLoEdge2);  // 0x7E09F8
    v1 = 128;
    v0 = 0x7E0000;
    sb(v1, v0, pad::kLoAnalog0);  // 0x7E0A04
    v0 = 0x7E0000;
    sb(v1, v0, pad::kLoAnalog1);  // 0x7E0A05
    v0 = 0x7E0000;
    sb(v1, v0, pad::kLoAnalog2);  // 0x7E0A06
    v0 = 0x7E0000;
    sb(v1, v0, pad::kLoAnalog3);  // 0x7E0A07
    jal(ctx, 0x103628u, gen::fn_sub_103B10_00103b10);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00103650 sub_103650 -- 640 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [H_Pad_UpdateButtonWords] Derives one port's button words (54-byte pad record at 0x7E09BC + 54 * port): the stick
// word (+10) from the held word's d-pad nibble plus the left stick's bytes (+0x12 x, +0x13 y: >= 0xC1 right / down
// 0x2000 / 0x4000, < 0x40 left / up 0x8000 / 0x1000), the pressed edges (+2 = held & (held ^ previous), +0xC for the
// stick word), copies into the repeat words (+6, +0xE), then the auto-repeat of the four directions (sub_103990) and
// of eight buttons (sub_1038D0; counter slots 4..11).
void sub_103650(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00103650
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    v0 = sll(s0, 3);
    v1 = addu(v0, s0);
    v0 = sll(v1, 2);
    v0 = subu(v0, v1);
    a1 = sll(v0, 1);
    v0 = 0x7E0000;
    v0 = addiu(v0, pad::kLoHeld);  // &0x7E09BC
    v1 = addu(v0, a1);
    v0 = 0x7E0000;
    v0 = addiu(v0, pad::kLoStick);  // &0x7E09C6
    a0 = addu(v0, a1);
    lhu(v0, v1, 0);
    v0 = v0 & 0xF0;
    sh(v0, a0, 0);
    v0 = 0x7E0000;
    v0 = addiu(v0, pad::kLoStickX);  // &0x7E09CE
    v1 = addu(v0, a1);
    lbu(v0, v1, 0);
    at = slti(v0, 193);
    if (at == 0) {
        // 0x001036b4
        charge(ctx, 3);
        lhu(v0, a0, 0);
        v0 = v0 | 0x2000;
        sh(v0, a0, 0);
    }
    // 0x001036c0
    charge(ctx, 4);
    lbu(v0, v1, 0);
    at = slti(v0, 64);
    if (at != 0) {
        // 0x001036d0
        charge(ctx, 3);
        lhu(v0, a0, 0);
        v0 = v0 | 0x8000;
        sh(v0, a0, 0);
    }
    // 0x001036dc
    charge(ctx, 7);
    v0 = 0x7E0000;
    v0 = addiu(v0, pad::kLoStickY);  // &0x7E09CF
    v1 = addu(v0, a1);
    lbu(v0, v1, 0);
    at = slti(v0, 193);
    if (at == 0) {
        // 0x001036f8
        charge(ctx, 3);
        lhu(v0, a0, 0);
        v0 = v0 | 0x4000;
        sh(v0, a0, 0);
    }
    // 0x00103704
    charge(ctx, 4);
    lbu(v0, v1, 0);
    at = slti(v0, 64);
    if (at != 0) {
        // 0x00103714
        charge(ctx, 3);
        lhu(v0, a0, 0);
        v0 = v0 | 0x1000;
        sh(v0, a0, 0);
    }
    // 0x00103720
    charge(ctx, 108);
    v0 = sll(s0, 3);
    v1 = addu(v0, s0);
    v0 = sll(v1, 2);
    v0 = subu(v0, v1);
    v0 = sll(v0, 1);
    v1 = 0x7E0000;
    v1 = addiu(v1, pad::kLoHeld);  // &0x7E09BC
    v1 = addu(v1, v0);
    lhu(a0, v1, 0);
    v1 = 0x7E0000;
    v1 = addiu(v1, pad::kLoPressed);  // &0x7E09BE
    a2 = addu(v1, v0);
    v1 = 0x7E0000;
    v1 = addiu(v1, pad::kLoPrevHeld);  // &0x7E09C0
    v1 = addu(v1, v0);
    lhu(v1, v1, 0);
    v1 = a0 ^ v1;
    v1 = a0 & v1;
    sh(v1, a2, 0);
    v1 = 0x7E0000;
    v1 = addiu(v1, pad::kLoStick);  // &0x7E09C6
    v1 = addu(v1, v0);
    lhu(a0, v1, 0);
    v1 = 0x7E0000;
    v1 = addiu(v1, pad::kLoStickPressed);  // &0x7E09C8
    a1 = addu(v1, v0);
    v1 = 0x7E0000;
    v1 = addiu(v1, pad::kLoStickPrev);  // &0x7E09CC
    v1 = addu(v1, v0);
    lhu(v1, v1, 0);
    v1 = a0 ^ v1;
    v1 = a0 & v1;
    sh(v1, a1, 0);
    lhu(a0, a2, 0);
    v1 = 0x7E0000;
    v1 = addiu(v1, pad::kLoRepeat);  // &0x7E09C2
    v1 = addu(v1, v0);
    sh(a0, v1, 0);
    lhu(a0, a1, 0);
    v1 = 0x7E0000;
    v1 = addiu(v1, pad::kLoStickRepeat);  // &0x7E09CA
    v0 = addu(v1, v0);
    sh(a0, v0, 0);
    a0 = s0;
    a1 = 4096;
    a2 = 0;
    jal(ctx, 0x1037D8u, gen::fn_sub_103990_00103990);
    a0 = s0;
    a1 = 16384;
    a2 = 1;
    jal(ctx, 0x1037ECu, gen::fn_sub_103990_00103990);
    a0 = s0;
    a1 = 0x8000;
    a2 = 2;
    jal(ctx, 0x103800u, gen::fn_sub_103990_00103990);
    a0 = s0;
    a1 = 8192;
    a2 = 3;
    jal(ctx, 0x103814u, gen::fn_sub_103990_00103990);
    a0 = s0;
    a1 = 4;
    a2 = a1;
    jal(ctx, 0x103828u, gen::fn_sub_1038D0_001038d0);
    a0 = s0;
    a1 = 1;
    a2 = 5;
    jal(ctx, 0x10383Cu, gen::fn_sub_1038D0_001038d0);
    a0 = s0;
    a1 = 8;
    a2 = 6;
    jal(ctx, 0x103850u, gen::fn_sub_1038D0_001038d0);
    a0 = s0;
    a1 = 2;
    a2 = 7;
    jal(ctx, 0x103864u, gen::fn_sub_1038D0_001038d0);
    a0 = s0;
    a1 = 64;
    a2 = 8;
    jal(ctx, 0x103878u, gen::fn_sub_1038D0_001038d0);
    a0 = s0;
    a1 = 32;
    a2 = 9;
    jal(ctx, 0x10388Cu, gen::fn_sub_1038D0_001038d0);
    a0 = s0;
    a1 = 16;
    a2 = 10;
    jal(ctx, 0x1038A0u, gen::fn_sub_1038D0_001038d0);
    a0 = s0;
    a1 = 128;
    a2 = 11;
    jal(ctx, 0x1038B4u, gen::fn_sub_1038D0_001038d0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001038D0 sub_1038D0 -- 192 bytes; leaf frame (no stack)
// [H_Pad_RepeatButton] Auto-repeat of one button of a port: a fresh press arms the counter byte (pad record +0x16 +
// slot) with 7; while held it counts down and at 0 ORs the bit into the repeat word (+6) and re-arms with 3.
void sub_1038D0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x001038d0
    enter(ctx, 13);  // entry check point + this block's cycles
    v1 = sll(a0, 3);
    a0 = addu(v1, a0);
    v1 = sll(a0, 2);
    v1 = subu(v1, a0);
    a3 = sll(v1, 1);
    a0 = a1 & 0xFFFF;
    v1 = 0x7E0000;
    v1 = addiu(v1, pad::kLoPressed);  // &0x7E09BE
    v1 = addu(v1, a3);
    lhu(v1, v1, 0);
    v1 = a0 & v1;
    if (v1 == 0) {
        // 0x00103924
        charge(ctx, 7);
        v1 = 0x7E0000;
        v1 = addiu(v1, pad::kLoHeld);  // &0x7E09BC
        v1 = addu(v1, a3);
        lhu(v1, v1, 0);
        v1 = a0 & v1;
        if (v1 != 0) {
            // 0x00103940
            charge(ctx, 10);
            v1 = 0x7E0000;
            v1 = addiu(v1, pad::kLoRepeatCounters);  // &0x7E09D2
            v1 = addu(v1, a3);
            a2 = addu(v1, a2);
            lbu(v1, a2, 0);
            v1 = addiu(v1, -1);
            sb(v1, a2, 0);
            lbu(v1, a2, 0);
            if (v1 == 0) {
                // 0x00103968
                charge(ctx, 8);
                v1 = 0x7E0000;
                v1 = addiu(v1, pad::kLoRepeat);  // &0x7E09C2
                a0 = addu(v1, a3);
                lhu(v1, a0, 0);
                v1 = v1 | a1;
                sh(v1, a0, 0);
                v1 = 3;
                sb(v1, a2, 0);
            }
        }
    } else {
        // 0x00103904
        charge(ctx, 8);
        a0 = 7;
        v1 = 0x7E0000;
        v1 = addiu(v1, pad::kLoRepeatCounters);  // &0x7E09D2
        v1 = addu(v1, a3);
        v1 = addu(a2, v1);
        sb(a0, v1, 0);
    }
    // 0x00103988 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00103990 sub_103990 -- 372 bytes; leaf frame (no stack)
// [H_Pad_RepeatDirection] Auto-repeat of one direction: as sub_1038D0 for the held word (repeat word +6), then the
// same rule again for the stick word (+0xC edges, +0xA held, repeat word +0xE) on the same counter byte.
void sub_103990(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10};
    // 0x00103990
    enter(ctx, 13);  // entry check point + this block's cycles
    v1 = sll(a0, 3);
    a3 = addu(v1, a0);
    v1 = sll(a3, 2);
    v1 = subu(v1, a3);
    a3 = sll(v1, 1);
    v1 = a1 & 0xFFFF;
    t0 = 0x7E0000;
    t0 = addiu(t0, pad::kLoPressed);  // &0x7E09BE
    t0 = addu(t0, a3);
    lhu(t0, t0, 0);
    t0 = v1 & t0;
    if (t0 == 0) {
        // 0x001039e4
        charge(ctx, 7);
        t0 = 0x7E0000;
        t0 = addiu(t0, pad::kLoHeld);  // &0x7E09BC
        t0 = addu(t0, a3);
        lhu(t0, t0, 0);
        t0 = v1 & t0;
        if (t0 != 0) {
            // 0x00103a00
            charge(ctx, 10);
            t0 = 0x7E0000;
            t0 = addiu(t0, pad::kLoRepeatCounters);  // &0x7E09D2
            t0 = addu(t0, a3);
            t2 = addu(t0, a2);
            lbu(t0, t2, 0);
            t0 = addiu(t0, -1);
            sb(t0, t2, 0);
            lbu(t0, t2, 0);
            if (t0 == 0) {
                // 0x00103a28
                charge(ctx, 8);
                t0 = 0x7E0000;
                t0 = addiu(t0, pad::kLoRepeat);  // &0x7E09C2
                t1 = addu(t0, a3);
                lhu(t0, t1, 0);
                t0 = t0 | a1;
                sh(t0, t1, 0);
                t0 = 3;
                sb(t0, t2, 0);
            }
        }
    } else {
        // 0x001039c4
        charge(ctx, 8);
        t1 = 7;
        t0 = 0x7E0000;
        t0 = addiu(t0, pad::kLoRepeatCounters);  // &0x7E09D2
        t0 = addu(t0, a3);
        t0 = addu(a2, t0);
        sb(t1, t0, 0);
    }
    // 0x00103a48
    charge(ctx, 7);
    t0 = 0x7E0000;
    t0 = addiu(t0, pad::kLoStickPressed);  // &0x7E09C8
    t0 = addu(t0, a3);
    lhu(t0, t0, 0);
    t0 = v1 & t0;
    if (t0 == 0) {
        // 0x00103a84
        charge(ctx, 7);
        t0 = 0x7E0000;
        t0 = addiu(t0, pad::kLoStick);  // &0x7E09C6
        a3 = addu(t0, a3);
        lhu(a3, a3, 0);
        v1 = v1 & a3;
        if (v1 != 0) {
            // 0x00103aa0
            charge(ctx, 15);
            v1 = sll(a0, 3);
            a0 = addu(v1, a0);
            v1 = sll(a0, 2);
            v1 = subu(v1, a0);
            a0 = sll(v1, 1);
            v1 = 0x7E0000;
            v1 = addiu(v1, pad::kLoRepeatCounters);  // &0x7E09D2
            v1 = addu(v1, a0);
            a2 = addu(v1, a2);
            lbu(v1, a2, 0);
            v1 = addiu(v1, -1);
            sb(v1, a2, 0);
            lbu(v1, a2, 0);
            if (v1 == 0) {
                // 0x00103adc
                charge(ctx, 8);
                v1 = 0x7E0000;
                v1 = addiu(v1, pad::kLoStickRepeat);  // &0x7E09CA
                a0 = addu(v1, a0);
                lhu(v1, a0, 0);
                v1 = v1 | a1;
                sh(v1, a0, 0);
                v1 = 3;
                sb(v1, a2, 0);
            }
        }
    } else {
        // 0x00103a64
        charge(ctx, 8);
        a0 = 7;
        v1 = 0x7E0000;
        v1 = addiu(v1, pad::kLoRepeatCounters);  // &0x7E09D2
        v1 = addu(v1, a3);
        v1 = addu(a2, v1);
        sb(a0, v1, 0);
    }
    // 0x00103afc (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00103B10 sub_103B10 -- 276 bytes; leaf frame (no stack)
// [H_Pad_UpdateVibration] The vibration state machine (0x7CDE90 s16 state): state 2 pulses the two actuator words
// 0x7E09DE / 0x7E09E0 on and off (on value 0x7CDE94, phase flag 0x7CDE98, off / on frame counts 0x7CDE9C / 0x7CDEA0,
// the frame counter 0x7CDEA4, the pulse count 0x7CDEA8) until the pulses run out (state 1); state 1 keeps the
// actuators off; state 0 resets everything and goes to 1.
void sub_103B10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x00103b10
    enter(ctx, 4);  // entry check point + this block's cycles
    lh(a0, gp, pad::kGpVibState);  // 0x7CDE90
    v1 = 2;
    if (a0 == v1) {
        // 0x00103b80
        charge(ctx, 3);
        lh(v1, gp, pad::kGpVibPulses);  // 0x7CDEA8
        if (v1 != 0) {
            // 0x00103b9c
            charge(ctx, 3);
            lh(v1, gp, pad::kGpVibCounter);  // 0x7CDEA4
            if (v1 != 0) {
                // 0x00103c08
                charge(ctx, 2);
                v1 = addiu(v1, -1);
                sh(v1, gp, pad::kGpVibCounter);  // 0x7CDEA4
            } else {
                // 0x00103ba8
                charge(ctx, 3);
                lh(v1, gp, pad::kGpVibOn);  // 0x7CDE98
                if (v1 != 0) {
                    // 0x00103be4
                    charge(ctx, 9);
                    v1 = 0x7E0000;
                    sh(zero, v1, pad::kLoActuator0);  // 0x7E09DE
                    v1 = 0x7E0000;
                    sh(zero, v1, pad::kLoActuator1);  // 0x7E09E0
                    lh(v1, gp, pad::kGpVibOffFrames);  // 0x7CDE9C
                    sh(v1, gp, pad::kGpVibCounter);  // 0x7CDEA4
                    sh(zero, gp, pad::kGpVibOn);  // 0x7CDE98
                } else {
                    // 0x00103bb4
                    charge(ctx, 12);
                    lbu(v1, gp, pad::kGpVibValue);  // 0x7CDE94
                    a0 = v1;
                    v1 = 0x7E0000;
                    sh(a0, v1, pad::kLoActuator0);  // 0x7E09DE
                    v1 = 0x7E0000;
                    sh(a0, v1, pad::kLoActuator1);  // 0x7E09E0
                    lh(v1, gp, pad::kGpVibOnFrames);  // 0x7CDEA0
                    sh(v1, gp, pad::kGpVibCounter);  // 0x7CDEA4
                    v1 = 1;
                    sh(v1, gp, pad::kGpVibOn);  // 0x7CDE98
                }
            }
            // 0x00103c10
            charge(ctx, 3);
            lh(v1, gp, pad::kGpVibPulses);  // 0x7CDEA8
            v1 = addiu(v1, -1);
            sh(v1, gp, pad::kGpVibPulses);  // 0x7CDEA8
        } else {
            // 0x00103b8c
            charge(ctx, 4);
            v1 = 1;
            sh(v1, gp, pad::kGpVibState);  // 0x7CDE90
        }
    } else {
        // 0x00103b20
        charge(ctx, 3);
        v1 = 1;
        if (a0 == v1) {
            // 0x00103b68
            charge(ctx, 6);
            v1 = 0x7E0000;
            sh(zero, v1, pad::kLoActuator0);  // 0x7E09DE
            v1 = 0x7E0000;
            sh(zero, v1, pad::kLoActuator1);  // 0x7E09E0
        } else {
            // 0x00103b2c
            charge(ctx, 2);
            if (a0 == 0) {
                // 0x00103b3c
                charge(ctx, 11);
                sh(zero, gp, pad::kGpVibPulses);  // 0x7CDEA8
                sh(zero, gp, pad::kGpVibOnFrames);  // 0x7CDEA0
                sh(zero, gp, pad::kGpVibValue);  // 0x7CDE94
                v1 = 0x7E0000;
                sh(zero, v1, pad::kLoActuator0);  // 0x7E09DE
                v1 = 0x7E0000;
                sh(zero, v1, pad::kLoActuator1);  // 0x7E09E0
                v1 = addiu(a0, 1);
                sh(v1, gp, pad::kGpVibState);  // 0x7CDE90
            } else {
                // 0x00103b34
                charge(ctx, 2);
            }
        }
    }
    // 0x00103c1c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00103CF0 sub_103CF0 -- 8 bytes; leaf frame (no stack)
// Empty in retail (a `jr $ra`; the movie player sub_10A860 calls it).
void sub_103CF0(EEContext& ctx) {
    using namespace hg;
    // 0x00103cf0
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x001040F0 sub_1040F0 -- 80 bytes; leaf frame (no stack)
// [H_ChkMem_GetHooks] Fills the four-entry hook table at 0x7E0A20 with sub_104140 / sub_104280 / sub_103F50 /
// sub_104040 (the memory checker's allocate / free / copy / clear hooks) and returns its address (kwlnInitRenderer).
void sub_1040F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3};
    // 0x001040f0
    enter(ctx, 20);  // entry check point + this block's cycles
    v1 = 0x100000;
    v1 = addiu(v1, 16704);  // &sub_104140
    v0 = 0x7E0000;
    sw(v1, v0, dbg::kLoMemHooks);  // 0x7E0A20
    v1 = 0x100000;
    v1 = addiu(v1, 17024);  // &sub_104280
    v0 = 0x7E0000;
    sw(v1, v0, dbg::kLoMemHookFree);  // 0x7E0A24
    v1 = 0x100000;
    v1 = addiu(v1, 16208);  // &sub_103F50
    v0 = 0x7E0000;
    sw(v1, v0, dbg::kLoMemHookCopy);  // 0x7E0A28
    v1 = 0x100000;
    v1 = addiu(v1, 16448);  // &sub_104040
    v0 = 0x7E0000;
    sw(v1, v0, dbg::kLoMemHookClear);  // 0x7E0A2C
    v0 = 0x7E0000;
    v0 = addiu(v0, dbg::kLoMemHooks);  // &0x7E0A20
}

// 0x001042E0 sub_1042E0 -- 200 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [dbgPrintInit] Loads the debug font "font/size12/f11_001.tmx" synchronously (H_Cdvd_Request + ReadSync), reads it
// into an RW image (sub_4CCAC0), creates a 4-bit raster of its size (RwRasterCreate sub_4CE0F0, format 0x4504),
// copies the image in (sub_4CDCE0), destroys the image and the request; then clears the 2,120-byte character screen
// 0x7E1E30 to spaces and the queued-string list (0x7CDEC8).
void sub_1042E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001042e0
    enter(ctx, 50);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0x5D0000;
    a0 = addiu(a0, -5296);  // "font/size12/f11_001.tmx"
    a1 = 0;
    jal(ctx, 0x1042F8u, gen::fn_H_Cdvd_Request_00100d80);
    s0 = v0;
    a0 = s0;
    jal(ctx, 0x104308u, gen::fn_H_Cdvd_ReadSync_001023a0);
    a0 = 0x5D0000;
    a0 = addiu(a0, -5296);  // "font/size12/f11_001.tmx"
    jal(ctx, 0x104318u, gen::fn_sub_4CCAC0_004ccac0);
    sw(v0, gp, dbg::kGpFontImage);  // 0x7CDECC
    a0 = s0;
    jal(ctx, 0x104328u, gen::fn_H_Cdvd_Destroy_00100ec0);
    lw(v0, gp, dbg::kGpFontImage);  // 0x7CDECC
    lw(a0, v0, 4);
    lw(a1, v0, 8);
    a2 = 4;
    a3 = 17668;
    jal(ctx, 0x104344u, gen::fn_sub_4CE0F0_004ce0f0);
    sw(v0, gp, dbg::kGpFontRaster);  // 0x7CDED0
    a0 = v0;
    lw(a1, gp, dbg::kGpFontImage);  // 0x7CDECC
    jal(ctx, 0x104358u, gen::fn_sub_4CDCE0_004cdce0);
    lw(a0, gp, dbg::kGpFontImage);  // 0x7CDECC
    jal(ctx, 0x104364u, gen::fn_sub_4CBEB0_004cbeb0);
    sw(zero, gp, dbg::kGpFontImage);  // 0x7CDECC
    jal(ctx, 0x104370u, gen::fn_nullsub_1_001007f0);
    a0 = 0x7E0000;
    a0 = addiu(a0, dbg::kLoScreen);  // &0x7E1E30
    a1 = 32;
    a2 = 2120;
    jal(ctx, 0x104388u, gen::fn_memset_00521408);
    sw(zero, gp, dbg::kGpPrintList);  // 0x7CDEC8
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001043B0 sub_1043B0 -- 104 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [dbgPrintClear] Per-frame reset of the debug print: the character screen to spaces, then frees every queued string
// node of the list (0x7CDEC8, linked by +0) through RwFree.
void sub_1043B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001043b0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0x7E0000;
    a0 = addiu(a0, dbg::kLoScreen);  // &0x7E1E30
    a1 = 32;
    a2 = 2120;
    jal(ctx, 0x1043CCu, gen::fn_memset_00521408);
    lw(a0, gp, dbg::kGpPrintList);  // 0x7CDEC8
    sw(zero, gp, dbg::kGpPrintList);  // 0x7CDEC8
    for (;;) {
        // 0x001043dc
        charge(ctx, 2);
        if (a0 == 0) {
            break;
        }
        // 0x001043e4
        charge(ctx, 8);
        lw(s0, a0, 0);
        v0 = 0x960000;
        lw(v0, v0, rw::kFree);  // 0x96017C
        jalr(ctx, 0x1043F0u, v0.u());
        a0 = s0;
        backedge(ctx);
    }
    // 0x00104404
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00104EB0 sub_104EB0 -- 284 bytes; frame 0x90: ra sp+0x20, s0 sp+0x10 (sq), f20 sp+0x0
// [dbgPrintColourF] Queues a formatted debug string with a colour: RwCalloc(1, 280) a node, vsprintf the format and
// the variadic arguments into +16, x (+4) and the f32 y (+8) from the first argument pair, colour bytes +276..+279
// from $a1, appended at the tail of the list 0x7CDEC8.
void sub_104EB0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f20{ctx, 20};
    // 0x00104eb0
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    sd(a0, sp, 0x38);
    sw(a1, sp, 0x48);
    sw(a2, sp, 0x58);
    sd(a3, sp, 0x68);
    sd(t0, sp, 0x70);
    sd(t1, sp, 0x78);
    sd(t2, sp, 0x80);
    sd(t3, sp, 0x88);
    lwc1(f20, sp, 0x3C);
    a0 = 1;
    a1 = 280;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, rw::kCalloc);  // 0x960184
    jalr(ctx, 0x104EF8u, v0.u());
    s0 = v0;
    v1 = 3;
    v0 = slti(v1, 8);
    if (v0 != 0) {
        // 0x00104f20
        charge(ctx, 3);
        v0 = 8;
        v0 = subu(v0, v1);
        v1 = sll(v0, 3);
    } else {
        // 0x00104f14
        charge(ctx, 3);
        v1 = 0;
    }
    // 0x00104f2c
    charge(ctx, 22);
    v0 = addiu(sp, 0x90);
    a2 = subu(v0, v1);
    a0 = addiu(s0, 16);
    lw(a1, sp, 0x58);
    jal(ctx, 0x104F3Cu, gen::fn_vsprintf_005288c8);
    lwc1(f0, sp, 0x38);
    swc1(f0, s0, 4);
    swc1(f20, s0, 8);
    sw(zero, s0, 12);
    lbu(a2, sp, 0x48);
    lbu(a1, sp, 0x49);
    lbu(a0, sp, 0x4A);
    lbu(v1, sp, 0x4B);
    sb(a2, s0, 276);
    sb(a1, s0, 277);
    sb(a0, s0, 278);
    sb(v1, s0, 279);
    sw(zero, s0, 272);
    lw(a0, gp, dbg::kGpPrintList);  // 0x7CDEC8
    if (a0 != 0) {
        for (;;) {
            // 0x00104f90
            charge(ctx, 3);
            lw(v1, a0, 0);
            if (v1 == 0) {
                break;
            }
            // 0x00104fa8
            charge(ctx, 3);
            a0 = v1;
            backedge(ctx);
        }
        // 0x00104f9c
        charge(ctx, 3);
        sw(s0, a0, 0);
    } else {
        // 0x00104f84
        charge(ctx, 3);
        sw(s0, gp, dbg::kGpPrintList);  // 0x7CDEC8
    }
    // 0x00104fb4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x00104FD0 sub_104FD0 -- 272 bytes; frame 0x80: ra sp+0x20, s0 sp+0x10 (sq), f20 sp+0x0
// [dbgPrintF] As sub_104EB0 with the colour white (0xFF in the four bytes +276..+279).
void sub_104FD0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f20{ctx, 20};
    // 0x00104fd0
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    sd(a0, sp, 0x30);
    sw(a1, sp, 0x40);
    sd(a2, sp, 0x50);
    sd(a3, sp, 0x58);
    sd(t0, sp, 0x60);
    sd(t1, sp, 0x68);
    sd(t2, sp, 0x70);
    sd(t3, sp, 0x78);
    lwc1(f20, sp, 0x34);
    a0 = 1;
    a1 = 280;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, rw::kCalloc);  // 0x960184
    jalr(ctx, 0x105018u, v0.u());
    s0 = v0;
    v1 = 2;
    v0 = slti(v1, 8);
    if (v0 != 0) {
        // 0x00105040
        charge(ctx, 3);
        v0 = 8;
        v0 = subu(v0, v1);
        v1 = sll(v0, 3);
    } else {
        // 0x00105034
        charge(ctx, 3);
        v1 = 0;
    }
    // 0x0010504c
    charge(ctx, 19);
    v0 = addiu(sp, 0x80);
    a2 = subu(v0, v1);
    a0 = addiu(s0, 16);
    lw(a1, sp, 0x40);
    jal(ctx, 0x10505Cu, gen::fn_vsprintf_005288c8);
    lwc1(f0, sp, 0x30);
    swc1(f0, s0, 4);
    swc1(f20, s0, 8);
    sw(zero, s0, 12);
    sw(zero, s0, 272);
    v1 = 255;
    sb(v1, s0, 279);
    sb(v1, s0, 278);
    sb(v1, s0, 277);
    sb(v1, s0, 276);
    lw(a0, gp, dbg::kGpPrintList);  // 0x7CDEC8
    if (a0 != 0) {
        for (;;) {
            // 0x001050a4
            charge(ctx, 3);
            lw(v1, a0, 0);
            if (v1 == 0) {
                break;
            }
            // 0x001050bc
            charge(ctx, 3);
            a0 = v1;
            backedge(ctx);
        }
        // 0x001050b0
        charge(ctx, 3);
        sw(s0, a0, 0);
    } else {
        // 0x00105098
        charge(ctx, 3);
        sw(s0, gp, dbg::kGpPrintList);  // 0x7CDEC8
    }
    // 0x001050c8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x00105210 sub_105210 -- 156 bytes; frame 0x20: ra sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [dbgPrintScreenZ] Screen z for a debug quad: from the main camera's near / far planes (+0x84 / +0x80 of
// g_kwlnMainCamera) and the Im2D z range (0x960088 near, 0x96008C far) interpolates $f12 into $f0 (an R5900 ACC
// multiply-add).
void sub_105210(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23};
    // 0x00105210
    enter(ctx, 30);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    mov_s(f23, f12);
    v0 = 0x960000;
    lwc1(f22, v0, rw::kIm2DFarZ);  // 0x96008C
    v0 = 0x960000;
    lwc1(f21, v0, rw::kIm2DNearZ);  // g_rwIm2DNearScreenZ
    jal(ctx, 0x10523Cu, gen::fn_sub_198590_00198590);
    lwc1(f20, v0, 132);
    jal(ctx, 0x105248u, gen::fn_sub_198590_00198590);
    lwc1(f3, v0, 128);
    sub_s(f1, f21, f22);
    sub_s(f0, f3, f20);
    div_s(f1, f1, f0);
    sub_s(f0, f23, f20);
    mul_s(f2, f0, f1);
    div_s(f0, f3, f23);
    mtc1(zero, f1);
    adda_s(f1, f22);
    madd_s(f0, f0, f2);
    c_lt_s(f0, f1);
    if (cond(ctx)) {
        // 0x00105288
        charge(ctx, 1);
        mov_s(f0, f1);
    }
    // 0x0010528c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00105800 sub_105800 -- 148 bytes; leaf frame (no stack)
// [H_ChrDsp_Init] Clears the three 1,648-byte bust-up records at 0x7E2680 (state, the request and work words +0x550 /
// +0x554, the three raster words +20..+28).
void sub_105800(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    // 0x00105800
    enter(ctx, 6);  // entry check point + this block's cycles
    t1 = 0;
    a3 = 1648;
    a2 = 0x7E0000;
    a2 = addiu(a2, bust::kLoRecords);  // &0x7E2680
    for (;;) {
        // 0x00105878
        charge(ctx, 5);
        v1 = dsll32(t1, 16);
        v1 = dsra32(v1, 16);
        v1 = slti(v1, 3);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00105818
        charge(ctx, 10);
        v1 = dsll32(t1, 16);
        v1 = dsra32(v1, 16);
        mult(v1, v1, a3);
        a1 = addu(a2, v1);
        sh(zero, a1, 0);
        sw(zero, a1, 1360);
        sw(zero, a1, 1364);
        t0 = 0;
        for (;;) {
            // 0x00105858
            charge(ctx, 5);
            a0 = dsll32(t0, 16);
            a0 = dsra32(a0, 16);
            v1 = slti(a0, 3);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00105840
            charge(ctx, 6);
            v1 = sll(a0, 2);
            v1 = addu(a1, v1);
            sw(zero, v1, 20);
            v1 = addiu(t0, 1);
            t0 = dsll32(v1, 16);
            t0 = dsra32(t0, 16);
        }
        // 0x0010586c
        charge(ctx, 3);
        v1 = addiu(t1, 1);
        t1 = dsll32(v1, 16);
        t1 = dsra32(t1, 16);
    }
    // 0x0010588c
    charge(ctx, 2);
}

// 0x001058A0 sub_1058A0 -- 272 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [H_ChrDsp_DrawAll] Draw task body (kwlnRootUpdateDrawBustupProcTask): the Im2D render states (6,1) (7,2) (8,1)
// (11,6) (10,5) (9,1) (12,1) (2,4) through the RwRenderStateSet slot 0x960090, then the bust-up draw sub_1059B0 on
// each of the three records.
void sub_1058A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001058a0
    enter(ctx, 48);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = 0x960000;
    s0 = addiu(s0, rw::kRenderStateSet);  // &pfn_RwRenderStateSet
    a0 = 6;
    a1 = 1;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x1058C0u, v0.u());
    a0 = 7;
    a1 = 2;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x1058D4u, v0.u());
    a0 = 8;
    a1 = 1;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x1058E8u, v0.u());
    a0 = 11;
    a1 = 6;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x1058FCu, v0.u());
    a0 = 10;
    a1 = 5;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x105910u, v0.u());
    a0 = 9;
    a1 = 1;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x105924u, v0.u());
    a0 = 12;
    a1 = 1;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x105938u, v0.u());
    a0 = 2;
    a1 = 4;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x10594Cu, v0.u());
    s0 = 0;
    for (;;) {
        // 0x00105988
        charge(ctx, 5);
        a0 = dsll32(s0, 16);
        a0 = dsra32(a0, 16);
        v1 = slti(a0, 3);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00105960
        charge(ctx, 10);
        v0 = 1648;
        mult(v1, a0, v0);
        v0 = 0x7E0000;
        v0 = addiu(v0, bust::kLoRecords);  // &0x7E2680
        a0 = addu(v0, v1);
        jal(ctx, 0x105974u, gen::fn_sub_1059B0_001059b0);
        v1 = addiu(s0, 1);
        s0 = dsll32(v1, 16);
        s0 = dsra32(s0, 16);
    }
    // 0x0010599c
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00106730 sub_106730 -- 300 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_ChrDsp_Release] Releases bust-up record `id`: prints "!!! RELEASE CHAR %d", drops its resource request
// (sub_133D30 when +0x548 is set, else H_Cdvd_Destroy of +0x528), destroys its three rasters (RwRasterDestroy
// sub_4D0F00) and clears the state.
void sub_106730(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00106730
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = dsll32(s1, 16);
    s0 = dsra32(s0, 16);
    a0 = 0x5D0000;
    a0 = addiu(a0, 15536);  // "!!! RELEASE CHAR %d\n"
    a1 = s0;
    jal(ctx, 0x10675Cu, gen::fn_printf_005225a8);
    a2 = 1648;
    mult(s0, s0, a2);
    a1 = 0x7E0000;
    a1 = addiu(a1, bust::kLoResReq);  // &0x7E2BC8
    v1 = addu(a1, s0);
    lw(a0, v1, 0);
    if (a0 == 0) {
        // 0x001067bc
        charge(ctx, 6);
        a1 = 0x7E0000;
        a1 = addiu(a1, bust::kLoCdNode);  // &0x7E2BA8
        v1 = addu(a1, s0);
        lw(a0, v1, 0);
        if (a0 != 0) {
            // 0x001067d4
            charge(ctx, 7);
            v0 = dsll32(s1, 16);
            v0 = dsra32(v0, 16);
            mult(v0, v0, a2);
            s1 = addu(a1, v0);
            jal(ctx, 0x1067E4u, gen::fn_H_Cdvd_Destroy_00100ec0);
            sw(zero, s1, 0);
        }
    } else {
        // 0x00106784
        charge(ctx, 14);
        v0 = dsll32(s1, 16);
        v0 = dsra32(v0, 16);
        mult(v1, v0, a2);
        v0 = 0x7E0000;
        v0 = addiu(v0, bust::kLoCdNode);  // &0x7E2BA8
        s2 = addu(v0, v1);
        s1 = addu(a1, v1);
        lw(a1, s2, 0);
        jal(ctx, 0x1067A4u, gen::fn_sub_133D30_00133d30);
        sw(zero, s1, 0);
        sw(zero, s2, 0);
    }
    // 0x001067f0
    charge(ctx, 6);
    s1 = 0;
    v1 = 0x7E0000;
    v1 = addiu(v1, bust::kLoRecords);  // &0x7E2680
    s2 = addu(v1, s0);
    for (;;) {
        // 0x00106830
        charge(ctx, 3);
        v1 = slti(s1, 3);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00106808
        charge(ctx, 6);
        v1 = sll(s1, 2);
        v1 = addu(s2, v1);
        s0 = addiu(v1, 20);
        lw(a0, v1, 20);
        if (a0 != 0) {
            // 0x00106820
            charge(ctx, 3);
            jal(ctx, 0x106820u, gen::fn_sub_4D0F00_004d0f00);
            sw(zero, s0, 0);
        }
        // 0x0010682c
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x0010683c
    charge(ctx, 8);
    sh(zero, s2, 0);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00106860 sub_106860 -- 1580 bytes; frame 0x160: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_ChrDsp_Request] Requests bust-up `id` (character, pose, expression): stores them, releases the old one, builds
// "i_bust_%02d_%x%1d[a|b].tmx" (the summer / winter suffix from clndIsDateInRange(6/1..9/30), the 29 file for
// character 9 when sub_17D800), looks it up in the name table off_5D3350 and turns it into "bustup/i_b_..bin" (or the
// dummy), requests the file (H_Cdvd_Request) and resets colour 0xFFFFFFFF and the two scales 1.0.
void sub_106860(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00106860
    enter(ctx, 44);  // entry check point + this block's cycles
    sp = addiu(sp, -0x160);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s4 = a1;
    s2 = a2;
    s1 = a3;
    s3 = dsll32(s0, 16);
    s3 = dsra32(s3, 16);
    a0 = 0x5D0000;
    a0 = addiu(a0, 15568);  // "!!! READ DISP2  %d\n"
    a1 = s3;
    jal(ctx, 0x1068A0u, gen::fn_printf_005225a8);
    v0 = 1648;
    mult(v1, s3, v0);
    v0 = 0x7E0000;
    v0 = addiu(v0, bust::kLoWord54C);  // &0x7E2BCC
    v0 = addu(v0, v1);
    sw(zero, v0, 0);
    v0 = 0x7E0000;
    v0 = addiu(v0, bust::kLoChar);  // &0x7E2684
    v0 = addu(v0, v1);
    sh(s4, v0, 0);
    v0 = 0x7E0000;
    v0 = addiu(v0, bust::kLoCostume);  // &0x7E2688
    v0 = addu(v0, v1);
    sh(s2, v0, 0);
    v0 = 0x7E0000;
    v0 = addiu(v0, bust::kLoFace);  // &0x7E268A
    v0 = addu(v0, v1);
    sh(s1, v0, 0);
    a0 = s0;
    jal(ctx, 0x1068F4u, gen::fn_sub_106730_00106730);
    s3 = dsll32(s2, 16);
    s3 = dsra32(s3, 16);
    at = slti(s3, 3);
    if (at == 0) {
        // 0x00106aa0
        charge(ctx, 4);
        jal(ctx, 0x106AA0u, gen::fn_sub_17D800_0017d800);
        if (v0 != 0) {
            // 0x00106ae8
            charge(ctx, 5);
            s2 = dsll32(s4, 16);
            s2 = dsra32(s2, 16);
            v0 = 9;
            if (s2 != v0) {
                // 0x00106b28
                charge(ctx, 10);
                s1 = dsll32(s1, 16);
                s1 = dsra32(s1, 16);
                a0 = addiu(sp, 0x60);
                a1 = 0x5D0000;
                a1 = addiu(a1, 15728);  // "i_bust_%02d_%x%1d.tmx"
                a2 = s2;
                a3 = s3;
                t0 = s1;
                jal(ctx, 0x106B48u, gen::fn_sprintf_00523ac8);
            } else {
                // 0x00106afc
                charge(ctx, 11);
                s1 = dsll32(s1, 16);
                s1 = dsra32(s1, 16);
                a0 = addiu(sp, 0x60);
                a1 = 0x5D0000;
                a1 = addiu(a1, 15760);  // "i_bust_29_%x%1d.tmx"
                a2 = s3;
                a3 = s1;
                jal(ctx, 0x106B18u, gen::fn_sprintf_00523ac8);
            }
        } else {
            // 0x00106ab0
            charge(ctx, 14);
            s1 = dsll32(s1, 16);
            s1 = dsra32(s1, 16);
            s2 = dsll32(s4, 16);
            s2 = dsra32(s2, 16);
            a0 = addiu(sp, 0x60);
            a1 = 0x5D0000;
            a1 = addiu(a1, 15728);  // "i_bust_%02d_%x%1d.tmx"
            a2 = s2;
            a3 = s3;
            t0 = s1;
            jal(ctx, 0x106AD8u, gen::fn_sprintf_00523ac8);
        }
    } else {
        // 0x00106910
        charge(ctx, 8);
        a0 = 6;
        a1 = 1;
        a2 = 9;
        a3 = 30;
        jal(ctx, 0x106920u, gen::fn_clndIsDateInRange_0017e480);
        if (v0 == 0) {
            // 0x001069e8
            charge(ctx, 4);
            jal(ctx, 0x1069E8u, gen::fn_sub_17D800_0017d800);
            if (v0 != 0) {
                // 0x00106a30
                charge(ctx, 5);
                s2 = dsll32(s4, 16);
                s2 = dsra32(s2, 16);
                v0 = 9;
                if (s2 != v0) {
                    // 0x00106a70
                    charge(ctx, 12);
                    s1 = dsll32(s1, 16);
                    s1 = dsra32(s1, 16);
                    a0 = addiu(sp, 0x60);
                    a1 = 0x5D0000;
                    a1 = addiu(a1, 15664);  // "i_bust_%02d_%x%1db.tmx"
                    a2 = s2;
                    a3 = s3;
                    t0 = s1;
                    jal(ctx, 0x106A90u, gen::fn_sprintf_00523ac8);
                } else {
                    // 0x00106a44
                    charge(ctx, 11);
                    s1 = dsll32(s1, 16);
                    s1 = dsra32(s1, 16);
                    a0 = addiu(sp, 0x60);
                    a1 = 0x5D0000;
                    a1 = addiu(a1, 15696);  // "i_bust_29_%x%1db.tmx"
                    a2 = s3;
                    a3 = s1;
                    jal(ctx, 0x106A60u, gen::fn_sprintf_00523ac8);
                }
            } else {
                // 0x001069f8
                charge(ctx, 14);
                s1 = dsll32(s1, 16);
                s1 = dsra32(s1, 16);
                s2 = dsll32(s4, 16);
                s2 = dsra32(s2, 16);
                a0 = addiu(sp, 0x60);
                a1 = 0x5D0000;
                a1 = addiu(a1, 15664);  // "i_bust_%02d_%x%1db.tmx"
                a2 = s2;
                a3 = s3;
                t0 = s1;
                jal(ctx, 0x106A20u, gen::fn_sprintf_00523ac8);
            }
        } else {
            // 0x00106930
            charge(ctx, 4);
            jal(ctx, 0x106930u, gen::fn_sub_17D800_0017d800);
            if (v0 != 0) {
                // 0x00106978
                charge(ctx, 5);
                s2 = dsll32(s4, 16);
                s2 = dsra32(s2, 16);
                v0 = 9;
                if (s2 != v0) {
                    // 0x001069b8
                    charge(ctx, 12);
                    s1 = dsll32(s1, 16);
                    s1 = dsra32(s1, 16);
                    a0 = addiu(sp, 0x60);
                    a1 = 0x5D0000;
                    a1 = addiu(a1, 15600);  // "i_bust_%02d_%x%1da.tmx"
                    a2 = s2;
                    a3 = s3;
                    t0 = s1;
                    jal(ctx, 0x1069D8u, gen::fn_sprintf_00523ac8);
                } else {
                    // 0x0010698c
                    charge(ctx, 11);
                    s1 = dsll32(s1, 16);
                    s1 = dsra32(s1, 16);
                    a0 = addiu(sp, 0x60);
                    a1 = 0x5D0000;
                    a1 = addiu(a1, 15632);  // "i_bust_29_%x%1da.tmx"
                    a2 = s3;
                    a3 = s1;
                    jal(ctx, 0x1069A8u, gen::fn_sprintf_00523ac8);
                }
            } else {
                // 0x00106940
                charge(ctx, 14);
                s1 = dsll32(s1, 16);
                s1 = dsra32(s1, 16);
                s2 = dsll32(s4, 16);
                s2 = dsra32(s2, 16);
                a0 = addiu(sp, 0x60);
                a1 = 0x5D0000;
                a1 = addiu(a1, 15600);  // "i_bust_%02d_%x%1da.tmx"
                a2 = s2;
                a3 = s3;
                t0 = s1;
                jal(ctx, 0x106968u, gen::fn_sprintf_00523ac8);
            }
        }
    }
    // 0x00106b50
    charge(ctx, 3);
    s4 = 0;
    for (;;) {
        // 0x00106d8c
        charge(ctx, 3);
        v0 = slti(s4, 5000);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00106b5c
        charge(ctx, 8);
        v1 = sll(s4, 2);
        v0 = 0x5D0000;
        v0 = addiu(v0, bust::kLoNameTable);  // &0x5D3350
        v0 = addu(v0, v1);
        lw(a0, v0, 0);
        lb(v0, a0, 0);
        if (v0 == 0) {
            goto L_00106b7c_19;
        }
        // 0x00106b98
        charge(ctx, 5);
        a1 = addiu(sp, 0x60);
        jal(ctx, 0x106B9Cu, gen::fn_strcmp_00524128);
        if (v0 == 0) {
            goto L_00106bac_21;
        }
        // 0x00106d88
        charge(ctx, 1);
        s4 = addiu(s4, 1);
    }
L_00106d98:
    charge(ctx, 61);
    v1 = dsll32(s0, 16);
    v1 = dsra32(v1, 16);
    v0 = 1648;
    mult(s0, v1, v0);
    v0 = 0x7E0000;
    v0 = addiu(v0, bust::kLoRecords);  // &0x7E2680
    s1 = addu(v0, s0);
    s2 = addiu(s1, 1384);
    a0 = s2;
    a1 = addiu(sp, 0x60);
    jal(ctx, 0x106DC0u, gen::fn_strcpy_00524270);
    a1 = 1;
    sh(a1, s1, 0);
    a0 = s2;
    jal(ctx, 0x106DD4u, gen::fn_H_Cdvd_Request_00100d80);
    v1 = 0x7E0000;
    v1 = addiu(v1, bust::kLoCdNode);  // &0x7E2BA8
    v1 = addu(v1, s0);
    sw(v0, v1, 0);
    a0 = 255;
    v1 = 0x7E0000;
    v1 = addiu(v1, bust::kLoR);  // &0x7E2BA0
    v1 = addu(v1, s0);
    sb(a0, v1, 0);
    v1 = 0x7E0000;
    v1 = addiu(v1, bust::kLoB);  // &0x7E2BA2
    v1 = addu(v1, s0);
    sb(a0, v1, 0);
    v1 = 0x7E0000;
    v1 = addiu(v1, bust::kLoG);  // &0x7E2BA1
    v1 = addu(v1, s0);
    sb(a0, v1, 0);
    v1 = 0x7E0000;
    v1 = addiu(v1, bust::kLoA);  // &0x7E2BA3
    v1 = addu(v1, s0);
    sb(a0, v1, 0);
    a0 = 0x3F800000;
    v1 = 0x7E0000;
    v1 = addiu(v1, bust::kLoScaleX);  // &0x7E2BAC
    v1 = addu(v1, s0);
    sw(a0, v1, 0);
    v1 = 0x7E0000;
    v1 = addiu(v1, bust::kLoScaleY);  // &0x7E2BB0
    v1 = addu(v1, s0);
    sw(a0, v1, 0);
    a0 = 1;
    v1 = 0x7E0000;
    v1 = addiu(v1, bust::kLoWord564);  // &0x7E2BE4
    v1 = addu(v1, s0);
    sw(a0, v1, 0);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x160);
    return;
L_00106b7c_19:
    charge(ctx, 7);
    a0 = addiu(sp, 0x60);
    a1 = 0x5D0000;
    a1 = addiu(a1, 15792);  // "bustup/bust_dummy.bin"
    jal(ctx, 0x106B88u, gen::fn_sprintf_00523ac8);
    goto L_00106d98;
L_00106bac_21:
    charge(ctx, 3);
    at = slti(s3, 3);
    if (at == 0) {
        // 0x00106cf8
        charge(ctx, 4);
        jal(ctx, 0x106CF8u, gen::fn_sub_17D800_0017d800);
        if (v0 != 0) {
            // 0x00106d30
            charge(ctx, 3);
            v0 = 9;
            if (s2 != v0) {
                // 0x00106d60
                charge(ctx, 10);
                a0 = addiu(sp, 0x60);
                a1 = 0x5D0000;
                a1 = addiu(a1, 15952);  // "bustup/i_b_%02d%x%1d.bin"
                a2 = s2;
                a3 = s3;
                t0 = s1;
                jal(ctx, 0x106D78u, gen::fn_sprintf_00523ac8);
            } else {
                // 0x00106d3c
                charge(ctx, 9);
                a0 = addiu(sp, 0x60);
                a1 = 0x5D0000;
                a1 = addiu(a1, 15984);  // "bustup/i_b_29%x%1d.bin"
                a2 = s3;
                a3 = s1;
                jal(ctx, 0x106D50u, gen::fn_sprintf_00523ac8);
            }
        } else {
            // 0x00106d08
            charge(ctx, 10);
            a0 = addiu(sp, 0x60);
            a1 = 0x5D0000;
            a1 = addiu(a1, 15952);  // "bustup/i_b_%02d%x%1d.bin"
            a2 = s2;
            a3 = s3;
            t0 = s1;
            jal(ctx, 0x106D20u, gen::fn_sprintf_00523ac8);
        }
    } else {
        // 0x00106bb8
        charge(ctx, 8);
        a0 = 6;
        a1 = 1;
        a2 = 9;
        a3 = 30;
        jal(ctx, 0x106BC8u, gen::fn_clndIsDateInRange_0017e480);
        if (v0 == 0) {
            // 0x00106c68
            charge(ctx, 4);
            jal(ctx, 0x106C68u, gen::fn_sub_17D800_0017d800);
            if (v0 != 0) {
                // 0x00106ca0
                charge(ctx, 3);
                v0 = 9;
                if (s2 != v0) {
                    // 0x00106cd0
                    charge(ctx, 10);
                    a0 = addiu(sp, 0x60);
                    a1 = 0x5D0000;
                    a1 = addiu(a1, 15888);  // "bustup/i_b_%02d%x%1db.bin"
                    a2 = s2;
                    a3 = s3;
                    t0 = s1;
                    jal(ctx, 0x106CE8u, gen::fn_sprintf_00523ac8);
                } else {
                    // 0x00106cac
                    charge(ctx, 9);
                    a0 = addiu(sp, 0x60);
                    a1 = 0x5D0000;
                    a1 = addiu(a1, 15920);  // "bustup/i_b_29%x%1db.bin"
                    a2 = s3;
                    a3 = s1;
                    jal(ctx, 0x106CC0u, gen::fn_sprintf_00523ac8);
                }
            } else {
                // 0x00106c78
                charge(ctx, 10);
                a0 = addiu(sp, 0x60);
                a1 = 0x5D0000;
                a1 = addiu(a1, 15888);  // "bustup/i_b_%02d%x%1db.bin"
                a2 = s2;
                a3 = s3;
                t0 = s1;
                jal(ctx, 0x106C90u, gen::fn_sprintf_00523ac8);
            }
        } else {
            // 0x00106bd8
            charge(ctx, 4);
            jal(ctx, 0x106BD8u, gen::fn_sub_17D800_0017d800);
            if (v0 != 0) {
                // 0x00106c10
                charge(ctx, 3);
                v0 = 9;
                if (s2 != v0) {
                    // 0x00106c40
                    charge(ctx, 10);
                    a0 = addiu(sp, 0x60);
                    a1 = 0x5D0000;
                    a1 = addiu(a1, 15824);  // "bustup/i_b_%02d%x%1da.bin"
                    a2 = s2;
                    a3 = s3;
                    t0 = s1;
                    jal(ctx, 0x106C58u, gen::fn_sprintf_00523ac8);
                } else {
                    // 0x00106c1c
                    charge(ctx, 9);
                    a0 = addiu(sp, 0x60);
                    a1 = 0x5D0000;
                    a1 = addiu(a1, 15856);  // "bustup/i_b_29%x%1da.bin"
                    a2 = s3;
                    a3 = s1;
                    jal(ctx, 0x106C30u, gen::fn_sprintf_00523ac8);
                }
            } else {
                // 0x00106be8
                charge(ctx, 10);
                a0 = addiu(sp, 0x60);
                a1 = 0x5D0000;
                a1 = addiu(a1, 15824);  // "bustup/i_b_%02d%x%1da.bin"
                a2 = s2;
                a3 = s3;
                t0 = s1;
                jal(ctx, 0x106C00u, gen::fn_sprintf_00523ac8);
            }
        }
    }
    goto L_00106d98;
}

// 0x00106E90 sub_106E90 -- 40 bytes; leaf frame (no stack)
// [H_ChrDsp_SetAlpha] Bust-up record `id`: alpha byte (+0x523) = $a1.
void sub_106E90(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00106e90
    enter(ctx, 10);  // entry check point + this block's cycles
    a0 = dsll32(a0, 16);
    a0 = dsra32(a0, 16);
    v1 = 1648;
    mult(a0, a0, v1);
    v1 = 0x7E0000;
    v1 = addiu(v1, bust::kLoA);  // &0x7E2BA3
    v1 = addu(v1, a0);
    sb(a1, v1, 0);
}

// 0x00106EC0 sub_106EC0 -- 104 bytes; leaf frame (no stack)
// [H_ChrDsp_SetFade] Bust-up record `id`: the fade word (+0x550) = $a1; a non-zero value also starts the fade (+0x558
// = 1, +0x560 = 0, +0x55C = 2).
void sub_106EC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00106ec0
    enter(ctx, 10);  // entry check point + this block's cycles
    a0 = dsll32(a0, 16);
    a0 = dsra32(a0, 16);
    v1 = 1648;
    mult(a2, a0, v1);
    v1 = 0x7E0000;
    v1 = addiu(v1, bust::kLoFade);  // &0x7E2BD0
    v1 = addu(v1, a2);
    sw(a1, v1, 0);
    if (a1 != 0) {
        // 0x00106ee8
        charge(ctx, 14);
        a0 = 1;
        v1 = 0x7E0000;
        v1 = addiu(v1, bust::kLoFadeOn);  // &0x7E2BD8
        v1 = addu(v1, a2);
        sw(a0, v1, 0);
        v1 = 0x7E0000;
        v1 = addiu(v1, bust::kLoFadeFrame);  // &0x7E2BE0
        v1 = addu(v1, a2);
        sw(zero, v1, 0);
        a0 = 2;
        v1 = 0x7E0000;
        v1 = addiu(v1, bust::kLoFadeStep);  // &0x7E2BDC
        v1 = addu(v1, a2);
        sw(a0, v1, 0);
    }
    // 0x00106f20 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00106F30 sub_106F30 -- 40 bytes; leaf frame (no stack)
// [H_ChrDsp_SetFlip] Bust-up record `id`: +0x554 = $a1.
void sub_106F30(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00106f30
    enter(ctx, 10);  // entry check point + this block's cycles
    a0 = dsll32(a0, 16);
    a0 = dsra32(a0, 16);
    v1 = 1648;
    mult(a0, a0, v1);
    v1 = 0x7E0000;
    v1 = addiu(v1, bust::kLoFlip);  // &0x7E2BD4
    v1 = addu(v1, a0);
    sw(a1, v1, 0);
}

// 0x00106F60 sub_106F60 -- 76 bytes; leaf frame (no stack)
// [H_ChrDsp_SetPose] Bust-up record `id`: a loaded record (state 3) goes to state 4; the pose word (+2) = $a1.
void sub_106F60(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x00106f60
    enter(ctx, 11);  // entry check point + this block's cycles
    a0 = dsll32(a0, 16);
    a0 = dsra32(a0, 16);
    v1 = 1648;
    mult(a3, a0, v1);
    v1 = 0x7E0000;
    v1 = addiu(v1, bust::kLoRecords);  // &0x7E2680
    a2 = addu(v1, a3);
    lh(a0, a2, 0);
    v1 = 3;
    if (a0 == v1) {
        // 0x00106f8c
        charge(ctx, 2);
        v1 = 4;
        sh(v1, a2, 0);
    }
    // 0x00106f94 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v1 = 0x7E0000;
    v1 = addiu(v1, bust::kLoPose);  // &0x7E2682
    v1 = addu(v1, a3);
    sh(a1, v1, 0);
}

// 0x00106FB0 sub_106FB0 -- 64 bytes; frame 0x10
// [H_ChrDsp_SetPos] Bust-up record `id`: the 64-bit position word (+0xC: x, y) = $a1.
void sub_106FB0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x00106fb0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(a1, sp, 0x8);
    a0 = dsll32(a0, 16);
    a0 = dsra32(a0, 16);
    v1 = 1648;
    mult(a0, a0, v1);
    v1 = 0x7E0000;
    v1 = addiu(v1, bust::kLoPos);  // &0x7E268C
    v1 = addu(v1, a0);
    lwc1(f1, sp, 0x8);
    lwc1(f0, sp, 0xC);
    swc1(f1, v1, 0);
    swc1(f0, v1, 4);
    sp = addiu(sp, 0x10);
}

// 0x00106FF0 sub_106FF0 -- 48 bytes; leaf frame (no stack)
// [H_ChrDsp_IsReady] Bust-up record `id` is loaded (state == 3).
void sub_106FF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00106ff0
    enter(ctx, 12);  // entry check point + this block's cycles
    v1 = dsll32(a0, 16);
    v1 = dsra32(v1, 16);
    v0 = 1648;
    mult(v1, v1, v0);
    v0 = 0x7E0000;
    v0 = addiu(v0, bust::kLoRecords);  // &0x7E2680
    v0 = addu(v0, v1);
    lh(v0, v0, 0);
    v0 = v0 ^ 0x3;
    v0 = sltiu(v0, 1);
}

// 0x00107060 sub_107060 -- 324 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [H_Fade_DrawTask] The fade draw (kwlnRootUpdateEtcDrawTask): the Im2D render states, then while a fade is active
// (0x7CDED4) the draw of its type (0x7CDF08, jump table 0x7B51C0: 0-2 / 4 sub_1071F0, 3 / 5 H_Fade_DrawBlue, 6
// H_Fade_DrawWhite, 7 sub_107B20, 8 H_Fade_DrawColour).
void sub_107060(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00107060
    enter(ctx, 43);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = 0x960000;
    s0 = addiu(s0, rw::kRenderStateSet);  // &pfn_RwRenderStateSet
    a0 = 6;
    a1 = 1;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x107080u, v0.u());
    a0 = 7;
    a1 = 2;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x107094u, v0.u());
    a0 = 8;
    a1 = 1;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x1070A8u, v0.u());
    a0 = 10;
    a1 = 5;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x1070BCu, v0.u());
    a0 = 11;
    a1 = 6;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x1070D0u, v0.u());
    a0 = 9;
    a1 = 2;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x1070E4u, v0.u());
    a0 = 12;
    a1 = 1;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x1070F8u, v0.u());
    lw(v1, gp, fade::kGpActive);  // 0x7CDED4
    if (v1 != 0) {
        // 0x0010710c
        charge(ctx, 4);
        lh(v1, gp, fade::kGpType);  // 0x7CDF08
        at = sltiu(v1, 9);
        if (at != 0) {
            // 0x0010711c
            charge(ctx, 7);
            a0 = 0x7B0000;
            a0 = addiu(a0, fade::kLoDrawTable);  // &0x7B51C0
            v1 = sll(v1, 2);
            v1 = addu(v1, a0);
            lw(v1, v1, 0);
            switch (v1.u()) {
            case 0x107138u:  // table[0, 1, 2, 4]
                // 0x00107138
                charge(ctx, 4);
                jal(ctx, 0x107138u, gen::fn_sub_1071F0_001071f0);
                break;
            case 0x107148u:  // table[3]
                // 0x00107148
                charge(ctx, 4);
                jal(ctx, 0x107148u, gen::fn_H_Fade_DrawBlue_001075b0);
                break;
            case 0x107158u:  // table[5]
                // 0x00107158
                charge(ctx, 4);
                jal(ctx, 0x107158u, gen::fn_H_Fade_DrawBlue_001075b0);
                break;
            case 0x107168u:  // table[6]
                // 0x00107168
                charge(ctx, 4);
                jal(ctx, 0x107168u, gen::fn_H_Fade_DrawWhite_001078a0);
                break;
            case 0x107178u:  // table[7]
                // 0x00107178
                charge(ctx, 4);
                jal(ctx, 0x107178u, gen::fn_sub_107B20_00107b20);
                break;
            case 0x107188u:  // table[8]
                // 0x00107188
                charge(ctx, 2);
                jal(ctx, 0x107188u, gen::fn_H_Fade_DrawColour_001081e0);
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v1.u());
                return;
            }
        }
    }
    // 0x00107190 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00108680 sub_108680 -- 20 bytes; leaf frame (no stack)
// [H_Fade_SetColour] The fade colour bytes: r 0x7CDEF8, g 0x7CDEF4, b 0x7CDEF0 = $a0, $a1, $a2.
void sub_108680(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28};
    // 0x00108680
    enter(ctx, 5);  // entry check point + this block's cycles
    sb(a0, gp, fade::kGpR);  // 0x7CDEF8
    sb(a1, gp, fade::kGpG);  // 0x7CDEF4
    sb(a2, gp, fade::kGpB);  // 0x7CDEF0
}

// 0x00108E50 sub_108E50 -- 44 bytes; leaf frame (no stack)
// [H_Snd_GetBgmId] The playing BGM: the s16 id 0x7E4438 while the BGM channel record 0x7E4430 is active, else -1.
void sub_108E50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00108e50
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0x7E0000;
    lw(v0, v0, snd::kLoChannels);  // 0x7E4430
    if (v0 != 0) {
        // 0x00108e6c
        charge(ctx, 2);
        v0 = 0x7E0000;
        lh(v0, v0, snd::kLoBgmId);  // 0x7E4438
    } else {
        // 0x00108e60
        charge(ctx, 3);
        v0 = si(-1);
    }
    // 0x00108e74 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00109040 sub_109040 -- 40 bytes; frame 0x10: ra sp+0x0
// [H_Snd_PlayBgmFade] sub_1099D0(bgm, 1) (the BGM request with a fade); returns 1.
void sub_109040(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00109040
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a1 = 1;
    jal(ctx, 0x10904Cu, gen::fn_sub_1099D0_001099d0);
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00109170 sub_109170 -- 12 bytes; leaf frame (no stack)
// Returns 0 (K_Field_DestroyFieldRootTask; a stripped sound query).
void sub_109170(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00109170
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x001099A0 sub_1099A0 -- 44 bytes; leaf frame (no stack)
// [H_Snd_GetBgmId2] Same body as sub_108E50: the s16 BGM id while channel 0 is active, else -1.
void sub_1099A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x001099a0
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0x7E0000;
    lw(v0, v0, snd::kLoChannels);  // 0x7E4430
    if (v0 != 0) {
        // 0x001099bc
        charge(ctx, 2);
        v0 = 0x7E0000;
        lh(v0, v0, snd::kLoBgmId);  // 0x7E4438
    } else {
        // 0x001099b0
        charge(ctx, 3);
        v0 = si(-1);
    }
    // 0x001099c4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0010A500 sub_10A500 -- 156 bytes; frame 0x10: ra sp+0x0
// [H_Snd_IsChannelBusy] Is sound channel `ch` (77-word records from 0x7E4430) still playing: channels 0, 1 and 5
// never; otherwise an active record whose ADX stream (+0x10) is not in state 3 (ADXT_GetStat, expl_4 in the
// database). frFontDraw and the text-wait helpers poll channel 2 (the voice).
void sub_10A500(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0010a500
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v1 = dsll32(a0, 16);
    v1 = dsra32(v1, 16);
    v0 = 5;
    if (v1 != v0) {
        // 0x0010a528
        charge(ctx, 3);
        v0 = slti(v1, 2);
        if (v0 != 0) {
            // 0x0010a588
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x0010a534
            charge(ctx, 8);
            v0 = 308;
            mult(v1, v1, v0);
            v0 = 0x7E0000;
            v0 = addiu(v0, snd::kLoChannels);  // &0x7E4430
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            if (v0 == 0) {
                // 0x0010a57c
                charge(ctx, 3);
                v0 = 0;
            } else {
                // 0x0010a554
                charge(ctx, 10);
                v0 = 0x7E0000;
                v0 = addiu(v0, snd::kLoChannelStream);  // &0x7E4440
                v0 = addu(v0, v1);
                lw(a0, v0, 0);
                jal(ctx, 0x10A564u, gen::fn_expl_4_0054d148);
                v0 = v0 ^ 0x3;
                v0 = sltu(0, v0);
            }
        }
    } else {
        // 0x0010a51c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0010a58c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0010A6D0 sub_10A6D0 -- 80 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [H_Afs_DestroyTask] Destroy callback of "H_AfsSetProc": drops the work's file request (+0x20, H_Cdvd_Destroy) and
// frees the work.
void sub_10A6D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0010a6d0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    lw(a0, s0, 32);
    if (a0 != 0) {
        // 0x0010a6ec
        charge(ctx, 3);
        jal(ctx, 0x10A6ECu, gen::fn_H_Cdvd_Destroy_00100ec0);
        sw(zero, s0, 32);
    }
    // 0x0010a6f8
    charge(ctx, 10);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, rw::kFree);  // 0x96017C
    jalr(ctx, 0x10A704u, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0010DD10 sub_10DD10 -- 172 bytes; leaf frame (no stack)
// [uttmxCopyPixels32] TMX PSMCT32 pixels into a locked RW image (+4 width, +8 height, +0x10 stride, +0x14 pixels):
// RGB copied, alpha < 0x7F scaled by 255 / 128, else 0xFF.
void sub_10DD10(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13};
    // 0x0010dd10
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(t5, a0, 20);
    lw(t2, a0, 4);
    lw(t1, a0, 8);
    t3 = 0;
    a2 = 255;
    for (;;) {
        // 0x0010dda8
        charge(ctx, 3);
        v1 = slt(t3, t1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0010dd2c
        charge(ctx, 3);
        t4 = 0;
        for (;;) {
            // 0x0010dd90
            charge(ctx, 3);
            v1 = slt(t4, t2);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0010dd38
            charge(ctx, 12);
            v1 = sll(t4, 2);
            t0 = addu(t5, v1);
            lbu(v1, a1, 0);
            sb(v1, t0, 0);
            lbu(v1, a1, 1);
            sb(v1, t0, 1);
            lbu(v1, a1, 2);
            sb(v1, t0, 2);
            lbu(a3, a1, 3);
            v1 = slti(a3, 127);
            if (v1 != 0) {
                // 0x0010dd74
                charge(ctx, 5);
                v1 = sll(a3, 8);
                v1 = subu(v1, a3);
                v1 = v1 & 0xFFFF;
                v1 = srl(v1, 7);
                sb(v1, t0, 3);
            } else {
                // 0x0010dd68
                charge(ctx, 3);
                sb(a2, t0, 3);
            }
            // 0x0010dd88
            charge(ctx, 2);
            a1 = addiu(a1, 4);
            t4 = addiu(t4, 1);
        }
        // 0x0010dd9c
        charge(ctx, 3);
        lw(v1, a0, 16);
        t5 = addu(t5, v1);
        t3 = addiu(t3, 1);
    }
    // 0x0010ddb4
    charge(ctx, 2);
}

// 0x0010DDC0 sub_10DDC0 -- 128 bytes; leaf frame (no stack)
// [uttmxCopyPixels24] TMX PSMCT24 pixels: RGB copied, alpha 0xFF.
void sub_10DDC0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12};
    // 0x0010ddc0
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(t4, a0, 20);
    lw(t1, a0, 4);
    lw(t0, a0, 8);
    t2 = 0;
    a2 = 255;
    for (;;) {
        // 0x0010de2c
        charge(ctx, 3);
        v1 = slt(t2, t0);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0010dddc
        charge(ctx, 3);
        t3 = 0;
        for (;;) {
            // 0x0010de14
            charge(ctx, 3);
            v1 = slt(t3, t1);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0010dde8
            charge(ctx, 11);
            v1 = sll(t3, 2);
            a3 = addu(t4, v1);
            lbu(v1, a1, 0);
            sb(v1, a3, 0);
            lbu(v1, a1, 1);
            sb(v1, a3, 1);
            lbu(v1, a1, 2);
            sb(v1, a3, 2);
            sb(a2, a3, 3);
            a1 = addiu(a1, 3);
            t3 = addiu(t3, 1);
        }
        // 0x0010de20
        charge(ctx, 3);
        lw(v1, a0, 16);
        t4 = addu(t4, v1);
        t2 = addiu(t2, 1);
    }
    // 0x0010de38
    charge(ctx, 2);
}

// 0x0010DE40 sub_10DE40 -- 160 bytes; leaf frame (no stack)
// [uttmxCopyPixels16] TMX PSMCT16 / 16S pixels: each 5-bit channel << 3, alpha 0xFF.
void sub_10DE40(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12};
    // 0x0010de40
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(t0, a0, 20);
    lw(a2, a0, 4);
    lw(v1, a0, 8);
    a3 = 0;
    t2 = 255;
    for (;;) {
        // 0x0010decc
        charge(ctx, 3);
        t1 = slt(a3, v1);
        if (t1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0010de5c
        charge(ctx, 3);
        t4 = 0;
        for (;;) {
            // 0x0010deb4
            charge(ctx, 3);
            t1 = slt(t4, a2);
            if (t1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0010de68
            charge(ctx, 19);
            t1 = sll(t4, 2);
            t3 = addu(t0, t1);
            lhu(t1, a1, 0);
            t1 = t1 & 0x1F;
            t1 = sll(t1, 3);
            sb(t1, t3, 0);
            lhu(t1, a1, 0);
            t1 = sra(t1, 5);
            t1 = t1 & 0x1F;
            t1 = sll(t1, 3);
            sb(t1, t3, 1);
            lhu(t1, a1, 0);
            t1 = sra(t1, 10);
            t1 = t1 & 0x1F;
            t1 = sll(t1, 3);
            sb(t1, t3, 2);
            sb(t2, t3, 3);
            a1 = addiu(a1, 2);
            t4 = addiu(t4, 1);
        }
        // 0x0010dec0
        charge(ctx, 3);
        lw(t1, a0, 16);
        t0 = addu(t0, t1);
        a3 = addiu(a3, 1);
    }
    // 0x0010ded8
    charge(ctx, 2);
}

// 0x0010DEE0 sub_10DEE0 -- 128 bytes; leaf frame (no stack)
// [uttmxCopyPixels4] TMX PSMT4 pixels: each byte split into two 4-bit indices, one byte each.
void sub_10DEE0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11};
    // 0x0010dee0
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(t3, a0, 20);
    lw(v1, a0, 4);
    lw(t0, a0, 8);
    t1 = 0;
    a3 = sra(v1, 1);
    for (;;) {
        // 0x0010df4c
        charge(ctx, 3);
        v1 = slt(t1, t0);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0010defc
        charge(ctx, 3);
        t2 = 0;
        for (;;) {
            // 0x0010df34
            charge(ctx, 3);
            v1 = slt(t2, a3);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0010df08
            charge(ctx, 11);
            v1 = sll(t2, 1);
            a2 = addu(t3, v1);
            lbu(v1, a1, 0);
            v1 = v1 & 0xF;
            sb(v1, a2, 0);
            lbu(v1, a1, 0);
            v1 = sra(v1, 4);
            v1 = v1 & 0xF;
            sb(v1, a2, 1);
            a1 = addiu(a1, 1);
            t2 = addiu(t2, 1);
        }
        // 0x0010df40
        charge(ctx, 3);
        lw(v1, a0, 16);
        t3 = addu(t3, v1);
        t1 = addiu(t1, 1);
    }
    // 0x0010df58
    charge(ctx, 2);
}

// 0x0010DF60 sub_10DF60 -- 168 bytes; leaf frame (no stack)
// [uttmxCopyPalette32] A TMX PSMCT32 palette into the image palette (+0x18, 1 << depth entries): RGB copied, alpha <
// 0x7F scaled by 255 / 128 (rounded toward zero), else 0xFF.
void sub_10DF60(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11};
    // 0x0010df60
    enter(ctx, 8);  // entry check point + this block's cycles
    lw(v1, a0, 24);
    lw(a2, a0, 12);
    t3 = 0;
    a0 = 1;
    t2 = sllv(a0, a2);
    a3 = 255;
    for (;;) {
        // 0x0010dff4
        charge(ctx, 3);
        a0 = slt(t3, t2);
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0010df80
        charge(ctx, 16);
        a0 = sll(t3, 2);
        t1 = addu(a1, a0);
        a2 = addu(v1, a0);
        lbu(a0, t1, 0);
        sb(a0, a2, 0);
        lbu(a0, t1, 1);
        sb(a0, a2, 1);
        lbu(a0, t1, 2);
        sb(a0, a2, 2);
        t0 = addiu(a2, 3);
        lbu(a0, t1, 3);
        sb(a0, a2, 3);
        lbu(a2, a2, 3);
        a0 = slti(a2, 127);
        if (a0 != 0) {
            // 0x0010dfcc
            charge(ctx, 5);
            a0 = sll(a2, 8);
            a2 = subu(a0, a2);
            a0 = sra(a2, 7);
            if (i64(a2) < 0) {
                // 0x0010dfe0
                charge(ctx, 2);
                a0 = addiu(a2, 127);
                a0 = sra(a0, 7);
            }
            // 0x0010dfe8
            charge(ctx, 2);
            a0 = a0 & 0xFFFF;
            sb(a0, t0, 0);
        } else {
            // 0x0010dfc0
            charge(ctx, 3);
            sb(a3, t0, 0);
        }
        // 0x0010dff0
        charge(ctx, 1);
        t3 = addiu(t3, 1);
    }
    // 0x0010e000
    charge(ctx, 2);
}

// 0x0010E010 sub_10E010 -- 180 bytes; leaf frame (no stack)
// [uttmxUnswizzlePalette8] For an 8-bit image swaps entries 8..15 and 16..23 of every 32-entry block of the 256-entry
// palette (the PS2 CSM1 palette order).
void sub_10E010(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11};
    // 0x0010e010
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(t2, a0, 24);
    v1 = 8;
    if (a1 == v1) {
        // 0x0010e020
        charge(ctx, 5);
        t3 = 0;
        v1 = 1;
        t1 = sllv(v1, a1);
        for (;;) {
            // 0x0010e0b0
            charge(ctx, 3);
            v1 = slt(t3, t1);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0010e034
            charge(ctx, 3);
            a0 = t3 & 0x1F;
            if (i64(t3) < 0) {
                // 0x0010e040
                charge(ctx, 2);
                if (a0 != 0) {
                    // 0x0010e048
                    charge(ctx, 1);
                    a0 = addiu(a0, -32);
                }
            }
            // 0x0010e04c
            charge(ctx, 3);
            v1 = slti(a0, 8);
            if (v1 == 0) {
                // 0x0010e058
                charge(ctx, 3);
                at = slti(a0, 16);
                if (at != 0) {
                    // 0x0010e064
                    charge(ctx, 18);
                    v1 = sll(t3, 2);
                    t0 = addu(t2, v1);
                    lbu(a3, t0, 0);
                    lbu(a2, t0, 1);
                    lbu(a1, t0, 2);
                    lbu(a0, t0, 3);
                    lbu(v1, t0, 32);
                    sb(v1, t0, 0);
                    lbu(v1, t0, 33);
                    sb(v1, t0, 1);
                    lbu(v1, t0, 34);
                    sb(v1, t0, 2);
                    lbu(v1, t0, 35);
                    sb(v1, t0, 3);
                    sb(a3, t0, 32);
                    sb(a2, t0, 33);
                    sb(a1, t0, 34);
                    sb(a0, t0, 35);
                }
            }
            // 0x0010e0ac
            charge(ctx, 1);
            t3 = addiu(t3, 1);
        }
    }
    // 0x0010e0bc (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0010E0D0 sub_10E0D0 -- 1060 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [uttmxImageFromTmx] Builds an RW image from a TMX file in memory (header checked: 2, 0, "TMX0"): depth from the
// pixel format (+0x16: 0x14 / 0x24 / 0x2C 4-bit, 0x13 / 0x1B 8-bit, 2 / 0xA 16, 1 24, 0 32; 16 and more become 32),
// RwImageCreate (sub_4CBE00) + allocate (sub_4CBF20), the palette (16-bit or 32-bit, sub_10DF60, then sub_10E010) and
// the pixels through the copiers above. Returns the image or 0.
void sub_10E0D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t4{ctx, 12}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0010e0d0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s0 = addiu(s3, 64);
    lbu(v0, a0, 0);
    a0 = 2;
    if (v0 == a0) {
        // 0x0010e100
        charge(ctx, 3);
        lbu(v0, s3, 1);
        if (v0 != 0) {
            goto L_0010e14c;
        }
        // 0x0010e10c
        charge(ctx, 4);
        lbu(v1, s3, 8);
        v0 = 84;
        if (v1 != v0) {
            goto L_0010e14c;
        }
        // 0x0010e11c
        charge(ctx, 4);
        lbu(v1, s3, 9);
        v0 = 77;
        if (v1 != v0) {
            goto L_0010e14c;
        }
        // 0x0010e12c
        charge(ctx, 4);
        lbu(v1, s3, 10);
        v0 = 88;
        if (v1 != v0) {
            goto L_0010e14c;
        }
        // 0x0010e13c
        charge(ctx, 4);
        lbu(v1, s3, 11);
        v0 = 48;
        if (v1 != v0) {
            goto L_0010e14c;
        }
        // 0x0010e158
        charge(ctx, 4);
        lbu(v1, s3, 22);
        v0 = 44;
        if (v1 != v0) {
            // 0x0010e168
            charge(ctx, 3);
            v0 = 36;
            if (v1 == v0) {
                goto L_0010e1f8;
            }
            // 0x0010e174
            charge(ctx, 3);
            v0 = 20;
            if (v1 == v0) {
                goto L_0010e1f8;
            }
            // 0x0010e180
            charge(ctx, 3);
            v0 = 27;
            if (v1 != v0) {
                // 0x0010e18c
                charge(ctx, 3);
                v0 = 19;
                if (v1 == v0) {
                    goto L_0010e1ec;
                }
                // 0x0010e198
                charge(ctx, 3);
                v0 = 10;
                if (v1 != v0) {
                    // 0x0010e1a4
                    charge(ctx, 2);
                    if (v1 == a0) {
                        goto L_0010e1e0;
                    }
                    // 0x0010e1ac
                    charge(ctx, 3);
                    v0 = 1;
                    if (v1 == v0) {
                        // 0x0010e1d4
                        charge(ctx, 3);
                        s1 = 24;
                    } else {
                        // 0x0010e1b8
                        charge(ctx, 2);
                        if (v1 == 0) {
                            // 0x0010e1c8
                            charge(ctx, 3);
                            s1 = 32;
                        } else {
                            // 0x0010e1c0
                            charge(ctx, 2);
                            // 0x0010e204
                            charge(ctx, 1);
                            s1 = 0;
                        }
                    }
                    goto L_0010e208;
                }
            L_0010e1e0:
                charge(ctx, 3);
                s1 = 16;
                goto L_0010e208;
            }
        L_0010e1ec:
            charge(ctx, 3);
            s1 = 8;
            goto L_0010e208;
        }
    L_0010e1f8:
        charge(ctx, 3);
        s1 = 4;
    L_0010e208:
        charge(ctx, 2);
        if (s1 != 0) {
            // 0x0010e21c
            charge(ctx, 3);
            v0 = slti(s1, 16);
            if (v0 == 0) {
                // 0x0010e228
                charge(ctx, 1);
                s1 = 32;
            }
            // 0x0010e22c
            charge(ctx, 12);
            lhu(a0, s3, 18);
            lhu(a1, s3, 20);
            a2 = s1;
            jal(ctx, 0x10E238u, gen::fn_sub_4CBE00_004cbe00);
            s2 = v0;
            a0 = s2;
            jal(ctx, 0x10E248u, gen::fn_sub_4CBF20_004cbf20);
            lbu(a0, s3, 16);
            if (a0 != 0) {
                // 0x0010e25c
                charge(ctx, 4);
                lbu(v1, s3, 17);
                v0 = 10;
                if (v1 != v0) {
                    // 0x0010e26c
                    charge(ctx, 3);
                    v0 = 2;
                    if (v1 == v0) {
                        goto L_0010e294;
                    }
                    // 0x0010e278
                    charge(ctx, 2);
                    if (v1 == 0) {
                        // 0x0010e288
                        charge(ctx, 3);
                        a1 = 32;
                    } else {
                        // 0x0010e280
                        charge(ctx, 2);
                        // 0x0010e2a0
                        charge(ctx, 1);
                        a1 = 0;
                    }
                    goto L_0010e2a4;
                }
            L_0010e294:
                charge(ctx, 3);
                a1 = 16;
            L_0010e2a4:
                charge(ctx, 8);
                v0 = 1;
                v0 = sllv(v0, s1);
                mult(v0, a0, v0);
                mult(v0, a1, v0);
                t4 = sra(v0, 3);
                v0 = 10;
                if (v1 != v0) {
                    // 0x0010e2c4
                    charge(ctx, 3);
                    v0 = 2;
                    if (v1 == v0) {
                        goto L_0010e2f8;
                    }
                    // 0x0010e2d0
                    charge(ctx, 2);
                    if (v1 == 0) {
                        // 0x0010e2e0
                        charge(ctx, 6);
                        a0 = s2;
                        a1 = s0;
                        jal(ctx, 0x10E2E8u, gen::fn_sub_10DF60_0010df60);
                    } else {
                        // 0x0010e2d8
                        charge(ctx, 2);
                    }
                    goto L_0010e38c;
                }
            L_0010e2f8:
                charge(ctx, 8);
                lw(v1, s2, 24);
                lw(a1, s2, 12);
                a0 = 0;
                v0 = 1;
                v0 = sllv(v0, a1);
                a2 = 255;
                for (;;) {
                    // 0x0010e380
                    charge(ctx, 3);
                    a1 = slt(a0, v0);
                    if (a1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0010e318
                    charge(ctx, 20);
                    a1 = sll(a0, 1);
                    t0 = addu(s0, a1);
                    a1 = sll(a0, 2);
                    a3 = addu(v1, a1);
                    lhu(a1, t0, 0);
                    a1 = a1 & 0x1F;
                    a1 = sll(a1, 3);
                    sb(a1, a3, 0);
                    lhu(a1, t0, 0);
                    a1 = sra(a1, 5);
                    a1 = a1 & 0x1F;
                    a1 = sll(a1, 3);
                    sb(a1, a3, 1);
                    lhu(a1, t0, 0);
                    a1 = sra(a1, 10);
                    a1 = a1 & 0x1F;
                    a1 = sll(a1, 3);
                    sb(a1, a3, 2);
                    if (a0 != 0) {
                        // 0x0010e374
                        charge(ctx, 1);
                        a1 = a2;
                    } else {
                        // 0x0010e368
                        charge(ctx, 3);
                        a1 = 0;
                    }
                    // 0x0010e378
                    charge(ctx, 2);
                    sb(a1, a3, 3);
                    a0 = addiu(a0, 1);
                }
            L_0010e38c:
                charge(ctx, 5);
                a0 = s2;
                a1 = s1;
                jal(ctx, 0x10E394u, gen::fn_sub_10E010_0010e010);
                s0 = addu(s0, t4);
            }
            // 0x0010e3a0
            charge(ctx, 4);
            lbu(v1, s3, 22);
            v0 = 44;
            if (v1 != v0) {
                // 0x0010e3b0
                charge(ctx, 3);
                v0 = 36;
                if (v1 == v0) {
                    goto L_0010e4c0;
                }
                // 0x0010e3bc
                charge(ctx, 3);
                v0 = 20;
                if (v1 == v0) {
                    goto L_0010e4c0;
                }
                // 0x0010e3c8
                charge(ctx, 3);
                v0 = 27;
                if (v1 != v0) {
                    // 0x0010e3d4
                    charge(ctx, 3);
                    v0 = 19;
                    if (v1 == v0) {
                        goto L_0010e45c;
                    }
                    // 0x0010e3e0
                    charge(ctx, 3);
                    v0 = 10;
                    if (v1 != v0) {
                        // 0x0010e3ec
                        charge(ctx, 3);
                        v0 = 2;
                        if (v1 == v0) {
                            goto L_0010e444;
                        }
                        // 0x0010e3f8
                        charge(ctx, 3);
                        v0 = 1;
                        if (v1 == v0) {
                            // 0x0010e42c
                            charge(ctx, 6);
                            a0 = s2;
                            a1 = s0;
                            jal(ctx, 0x10E434u, gen::fn_sub_10DDC0_0010ddc0);
                        } else {
                            // 0x0010e404
                            charge(ctx, 2);
                            if (v1 == 0) {
                                // 0x0010e414
                                charge(ctx, 6);
                                a0 = s2;
                                a1 = s0;
                                jal(ctx, 0x10E41Cu, gen::fn_sub_10DD10_0010dd10);
                            } else {
                                // 0x0010e40c
                                charge(ctx, 2);
                            }
                        }
                        goto L_0010e4d0;
                    }
                L_0010e444:
                    charge(ctx, 6);
                    a0 = s2;
                    a1 = s0;
                    jal(ctx, 0x10E44Cu, gen::fn_sub_10DE40_0010de40);
                    goto L_0010e4d0;
                }
            L_0010e45c:
                charge(ctx, 6);
                lw(t0, s2, 20);
                lw(a1, s2, 4);
                lw(a0, s2, 8);
                a2 = 0;
                for (;;) {
                    // 0x0010e4ac
                    charge(ctx, 3);
                    v0 = slt(a2, a0);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0010e474
                    charge(ctx, 3);
                    a3 = 0;
                    for (;;) {
                        // 0x0010e494
                        charge(ctx, 3);
                        v0 = slt(a3, a1);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x0010e480
                        charge(ctx, 5);
                        lbu(v1, s0, 0);
                        v0 = addu(t0, a3);
                        sb(v1, v0, 0);
                        s0 = addiu(s0, 1);
                        a3 = addiu(a3, 1);
                    }
                    // 0x0010e4a0
                    charge(ctx, 3);
                    lw(v0, s2, 16);
                    t0 = addu(t0, v0);
                    a2 = addiu(a2, 1);
                }
                // 0x0010e4b8
                charge(ctx, 2);
                goto L_0010e4d0;
            }
        L_0010e4c0:
            charge(ctx, 4);
            a0 = s2;
            a1 = s0;
            jal(ctx, 0x10E4C8u, gen::fn_sub_10DEE0_0010dee0);
        L_0010e4d0:
            charge(ctx, 1);
            v0 = s2;
        } else {
            // 0x0010e210
            charge(ctx, 3);
            v0 = 0;
        }
        // 0x0010e4d4 (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(ra, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        return;
    }
L_0010e14c:
    charge(ctx, 3);
    v0 = 0;
    // 0x0010e4d4 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0010E500 sub_10E500 -- 232 bytes; frame 0x80: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [uttmxImageRead] RW image reader callback: opens the file (RwStreamOpen sub_4C58A0), reads the 64-byte header and
// the rest into a RwMalloc'd buffer, sub_10E0D0, frees the buffer and closes the stream (sub_4C5780).
void sub_10E500(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0010e500
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a2 = a0;
    s2 = 0;
    a0 = 2;
    a1 = 1;
    jal(ctx, 0x10E524u, gen::fn_sub_4C58A0_004c58a0);
    s0 = v0;
    if (s0 != 0) {
        // 0x0010e538
        charge(ctx, 36);
        a0 = s0;
        a1 = addiu(sp, 0x40);
        a2 = 64;
        jal(ctx, 0x10E544u, gen::fn_sub_4C5250_004c5250);
        lw(a0, sp, 0x44);
        a1 = 0x40000;
        v0 = 0x960000;
        lw(v0, v0, rw::kMalloc);  // 0x960178
        jalr(ctx, 0x10E55Cu, v0.u());
        s1 = v0;
        lw(v0, sp, 0x44);
        a2 = addiu(v0, -64);
        a0 = s0;
        a1 = addiu(s1, 64);
        jal(ctx, 0x10E578u, gen::fn_sub_4C5250_004c5250);
        a0 = s1;
        a1 = addiu(sp, 0x40);
        a2 = 64;
        jal(ctx, 0x10E58Cu, gen::fn_memcpy_00521250);
        a0 = s1;
        jal(ctx, 0x10E598u, gen::fn_sub_10E0D0_0010e0d0);
        s2 = v0;
        a0 = s1;
        v0 = 0x960000;
        lw(v0, v0, rw::kFree);  // 0x96017C
        jalr(ctx, 0x10E5B0u, v0.u());
        a0 = s0;
        a1 = 0;
        jal(ctx, 0x10E5C0u, gen::fn_sub_4C5780_004c5780);
    }
    // 0x0010e5c8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    v0 = s2;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x0010E5F0 sub_10E5F0 -- 60 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [uttmxImageReadHeader] RW image header callback: opens the stream and returns $a0 (the stream is not closed).
void sub_10E5F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0010e5f0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a2 = a1;
    a0 = 2;
    a1 = 1;
    jal(ctx, 0x10E60Cu, gen::fn_sub_4C58A0_004c58a0);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0010EC50 sub_10EC50 -- 2668 bytes; frame 0x130: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_CutInDraw_DrawDirect] Immediate draw of a cut-in's draw work (sub_1115E0): camera and world set-up
// (RwCameraBeginUpdate-style calls sub_4AA390 / sub_4AA3D0 / sub_4A9F20 / sub_4AA410), z test / blend states per
// +0x4E4, and in state 3 the per-layer keyframe draw of the 18-byte key records (colour clamps, the sprite / mesh
// calls sub_4AC5F0 / sub_4AB1B0 / sub_4A62E0 ...).
void sub_10EC50(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15}, f16{ctx, 16}, f17{ctx, 17};
    // 0x0010ec50
    enter(ctx, 51);  // entry check point + this block's cycles
    sp = addiu(sp, -0x130);
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
    lw(s4, a0, task::kWork);
    s0 = 0x960000;
    s0 = addiu(s0, rw::kRenderStateSet);  // &pfn_RwRenderStateSet
    a0 = 8;
    a1 = 0;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x10EC94u, v0.u());
    a0 = 6;
    a1 = 0;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x10ECA8u, v0.u());
    v0 = 0x3F000000;
    mtc1(v0, f12);
    jal(ctx, 0x10ECB8u, gen::fn_sub_4AA390_004aa390);
    jal(ctx, 0x10ECC0u, gen::fn_sub_198590_00198590);
    lwc1(f1, gp, fx::kGpCutInFloat0);  // 0x7CAFF4
    lwc1(f0, v0, 128);
    mul_s(f12, f1, f0);
    jal(ctx, 0x10ECD4u, gen::fn_sub_4AA3D0_004aa3d0);
    mtc1(zero, f12);
    v0 = 0x44200000;
    mtc1(v0, f14);
    v0 = 0x43E00000;
    mtc1(v0, f15);
    mov_s(f13, f12);
    jal(ctx, 0x10ECF4u, gen::fn_sub_4A9F20_004a9f20);
    jal(ctx, 0x10ECFCu, gen::fn_sub_198590_00198590);
    a0 = v0;
    jal(ctx, 0x10ED08u, gen::fn_sub_4AA410_004aa410);
    lw(v0, s4, 1252);
    if (v0 == 0) {
        // 0x0010ed48
        charge(ctx, 9);
        a0 = 2;
        a1 = 68;
        jal(ctx, 0x10ED50u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x17FB;
        jal(ctx, 0x10ED64u, gen::fn_RpSkyRenderStateSet_004d7f60);
    } else {
        // 0x0010ed1c
        charge(ctx, 11);
        a0 = 2;
        a1 = 72;
        jal(ctx, 0x10ED24u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x1801;
        jal(ctx, 0x10ED38u, gen::fn_RpSkyRenderStateSet_004d7f60);
    }
    // 0x0010ed6c
    charge(ctx, 4);
    lw(a0, s4, 0);
    v1 = 3;
    if (a0 == v1) {
        // 0x0010ed7c
        charge(ctx, 10);
        jal(ctx, 0x10ED7Cu, gen::fn_sub_4AAA60_004aaa60);
        jal(ctx, 0x10ED84u, gen::fn_sub_4A9BF0_004a9bf0);
        jal(ctx, 0x10ED8Cu, gen::fn_sub_4AAA60_004aaa60);
        s6 = 0;
        s3 = 0;
        for (;;) {
            // 0x0010f668
            charge(ctx, 4);
            lw(v0, s4, 1248);
            v0 = slt(s3, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0010eda4
            charge(ctx, 20);
            sw(zero, sp, 0xE0);
            s1 = 0;
            s7 = 0;
            sw(zero, sp, 0xD0);
            v0 = sll(s3, 2);
            s0 = addu(s4, v0);
            lw(s2, s0, 488);
            s5 = addiu(s0, 168);
            lw(a0, s0, 168);
            jal(ctx, 0x10EDC8u, gen::fn_sub_4AC5F0_004ac5f0);
            lw(a0, s5, 0);
            jal(ctx, 0x10EDD4u, gen::fn_sub_4AB1B0_004ab1b0);
            v0 = sll(s3, 1);
            v0 = addu(s4, v0);
            sq(v0, sp, 0xC0);
            v0 = sll(s6, 2);
            v0 = addu(s4, v0);
            sq(v0, sp, 0xB0);
            for (;;) {
                // 0x0010edf4
                charge(ctx, 3);
                lw(v0, sp, 0xD0);
                if (v0 == 0) {
                    // 0x0010ee00
                    charge(ctx, 9);
                    lw(v1, s0, 8);
                    v0 = sll(s2, 3);
                    v0 = addu(v0, s2);
                    v0 = sll(v0, 1);
                    a2 = addu(v1, v0);
                    lb(v1, a2, 1);
                    v0 = si(-1);
                    if (v1 != v0) {
                        // 0x0010ee24
                        charge(ctx, 4);
                        lhu(v0, a2, 2);
                        at = slti(v0, 256);
                        if (at != 0) {
                            // 0x0010ee40
                            charge(ctx, 3);
                            v0 = v0 & 0xFF;
                            a1 = dsll32(v0, 16);
                            a1 = dsra32(a1, 16);
                        } else {
                            // 0x0010ee34
                            charge(ctx, 3);
                            a1 = 255;
                        }
                        // 0x0010ee4c
                        charge(ctx, 4);
                        lhu(v0, a2, 4);
                        at = slti(v0, 256);
                        if (at != 0) {
                            // 0x0010ee68
                            charge(ctx, 3);
                            v0 = v0 & 0xFF;
                            a0 = dsll32(v0, 16);
                            a0 = dsra32(a0, 16);
                        } else {
                            // 0x0010ee5c
                            charge(ctx, 3);
                            a0 = 255;
                        }
                        // 0x0010ee74
                        charge(ctx, 4);
                        lhu(v0, a2, 6);
                        at = slti(v0, 256);
                        if (at != 0) {
                            // 0x0010ee90
                            charge(ctx, 3);
                            v0 = v0 & 0xFF;
                            v1 = dsll32(v0, 16);
                            v1 = dsra32(v1, 16);
                        } else {
                            // 0x0010ee84
                            charge(ctx, 3);
                            v1 = 255;
                        }
                        // 0x0010ee9c
                        charge(ctx, 4);
                        lhu(v0, a2, 8);
                        at = slti(v0, 256);
                        if (at != 0) {
                            // 0x0010eeb8
                            charge(ctx, 1);
                            v0 = v0 & 0xFF;
                        } else {
                            // 0x0010eeac
                            charge(ctx, 3);
                            v0 = 255;
                        }
                        // 0x0010eebc
                        charge(ctx, 19);
                        v0 = dsll32(v0, 16);
                        v0 = dsra32(v0, 16);
                        lq(a2, sp, 0xC0);
                        lh(a2, a2, 1008);
                        a1 = addu(a1, a2);
                        a1 = dsll32(a1, 16);
                        a1 = dsra32(a1, 16);
                        lq(a2, sp, 0xC0);
                        lh(a2, a2, 1088);
                        a0 = addu(a0, a2);
                        a0 = dsll32(a0, 16);
                        a0 = dsra32(a0, 16);
                        lq(a2, sp, 0xC0);
                        lh(a2, a2, 1168);
                        v1 = addu(v1, a2);
                        v1 = dsll32(v1, 16);
                        v1 = dsra32(v1, 16);
                        if (i64(a1) < 0) {
                            // 0x0010ef08
                            charge(ctx, 1);
                            a1 = 0;
                        }
                        // 0x0010ef0c
                        charge(ctx, 5);
                        a2 = dsll32(a1, 16);
                        a2 = dsra32(a2, 16);
                        at = slti(a2, 256);
                        if (at == 0) {
                            // 0x0010ef20
                            charge(ctx, 1);
                            a1 = 255;
                        }
                        // 0x0010ef24
                        charge(ctx, 4);
                        a2 = dsll32(a0, 16);
                        a2 = dsra32(a2, 16);
                        if (i64(a2) < 0) {
                            // 0x0010ef34
                            charge(ctx, 1);
                            a0 = 0;
                        }
                        // 0x0010ef38
                        charge(ctx, 5);
                        a2 = dsll32(a0, 16);
                        a2 = dsra32(a2, 16);
                        at = slti(a2, 256);
                        if (at == 0) {
                            // 0x0010ef4c
                            charge(ctx, 1);
                            a0 = 255;
                        }
                        // 0x0010ef50
                        charge(ctx, 4);
                        a2 = dsll32(v1, 16);
                        a2 = dsra32(a2, 16);
                        if (i64(a2) < 0) {
                            // 0x0010ef60
                            charge(ctx, 1);
                            v1 = 0;
                        }
                        // 0x0010ef64
                        charge(ctx, 5);
                        a2 = dsll32(v1, 16);
                        a2 = dsra32(a2, 16);
                        at = slti(a2, 256);
                        if (at == 0) {
                            // 0x0010ef78
                            charge(ctx, 1);
                            v1 = 255;
                        }
                        // 0x0010ef7c
                        charge(ctx, 6);
                        sb(a1, sp, 0x12C);
                        sb(a0, sp, 0x12D);
                        sb(v1, sp, 0x12E);
                        sb(v0, sp, 0x12F);
                        v0 = 1;
                        sw(v0, sp, 0xD0);
                    }
                }
                // 0x0010ef94
                charge(ctx, 10);
                lw(v1, s0, 8);
                v0 = sll(s2, 3);
                v0 = addu(v0, s2);
                v0 = sll(v0, 1);
                sq(v0, sp, 0xA0);
                a0 = addu(v1, v0);
                lb(v1, a0, 1);
                v0 = si(-1);
                if (v1 == v0) {
                    break;
                }
                // 0x0010f120
                charge(ctx, 2);
                if (v1 != v0) {
                    // 0x0010f128
                    charge(ctx, 4);
                    lb(v1, a0, 0);
                    v0 = 2;
                    if (v1 == v0) {
                        // 0x0010f138
                        charge(ctx, 3);
                        lw(v0, sp, 0xE0);
                        if (v0 == 0) {
                            // 0x0010f144
                            charge(ctx, 23);
                            v0 = 1;
                            sw(v0, sp, 0xE0);
                            lw(a0, s0, 328);
                            lq(v0, sp, 0xB0);
                            lw(a1, v0, 808);
                            jal(ctx, 0x10F158u, gen::fn_sub_4A62E0_004a62e0);
                            sw(zero, sp, 0x100);
                            lwc1(f0, gp, fx::kGpCutInFloat1);  // 0x7CAFF8
                            swc1(f0, sp, 0x104);
                            swc1(f0, sp, 0x108);
                            swc1(f0, sp, 0x10C);
                            swc1(f0, sp, 0x110);
                            sw(zero, sp, 0x114);
                            sw(zero, sp, 0x118);
                            sw(zero, sp, 0x11C);
                            lw(a0, s0, 328);
                            a1 = addiu(sp, 0x100);
                            a2 = addiu(sp, 0x108);
                            a3 = addiu(sp, 0x110);
                            t0 = addiu(sp, 0x118);
                            jal(ctx, 0x10F198u, gen::fn_sub_4A6200_004a6200);
                        }
                    }
                }
                // 0x0010f1a0
                charge(ctx, 6);
                lw(v1, s0, 8);
                lq(v0, sp, 0xA0);
                a0 = addu(v1, v0);
                lb(v1, a0, 1);
                if (v1 != 0) {
                    // 0x0010f360
                    charge(ctx, 3);
                    v0 = 1;
                    if (v1 != v0) {
                        // 0x0010f4f0
                        charge(ctx, 3);
                        v0 = 2;
                        if (v1 == v0) {
                            // 0x0010f4fc
                            charge(ctx, 80);
                            v0 = sll(s2, 3);
                            v0 = addu(v0, s2);
                            s7 = sll(v0, 1);
                            lb(v0, a0, 0);
                            sw(v0, s0, 648);
                            lw(v0, s0, 8);
                            a2 = addu(v0, s7);
                            lwc1(f0, s4, 988);
                            cvt_w_s(f0, f0);
                            mfc1(a1, f0);
                            lwc1(f0, s4, 984);
                            cvt_w_s(f0, f0);
                            mfc1(a0, f0);
                            mtc1(fp, f0);
                            cvt_s_w(f12, f0);
                            lh(v0, sp, 0xF0);
                            mtc1(v0, f0);
                            cvt_s_w(f13, f0);
                            lh(v0, a2, 10);
                            v0 = addu(a0, v0);
                            mtc1(v0, f0);
                            cvt_s_w(f14, f0);
                            lh(v0, a2, 12);
                            v0 = addu(a1, v0);
                            v1 = 448;
                            v0 = subu(v1, v0);
                            mtc1(v0, f0);
                            cvt_s_w(f15, f0);
                            lh(v0, a2, 14);
                            v0 = addu(a0, v0);
                            mtc1(v0, f0);
                            cvt_s_w(f16, f0);
                            lh(v0, a2, 16);
                            v0 = addu(a1, v0);
                            v0 = subu(v1, v0);
                            mtc1(v0, f0);
                            cvt_s_w(f17, f0);
                            lw(a0, s0, 168);
                            jal(ctx, 0x10F5ACu, gen::fn_sub_4AB410_004ab410);
                            lw(v0, s0, 8);
                            a0 = addu(v0, s7);
                            lwc1(f0, s4, 984);
                            cvt_w_s(f0, f0);
                            mfc1(v1, f0);
                            lh(v0, a0, 14);
                            v0 = addu(v1, v0);
                            fp = dsll32(v0, 16);
                            fp = dsra32(fp, 16);
                            lwc1(f0, s4, 988);
                            cvt_w_s(f0, f0);
                            mfc1(v1, f0);
                            lh(v0, a0, 16);
                            v0 = addu(v1, v0);
                            mtc1(v0, f0);
                            cvt_s_w(f1, f0);
                            v0 = 0x43E00000;
                            mtc1(v0, f0);
                            sub_s(f0, f0, f1);
                            cvt_w_s(f0, f0);
                            mfc1(v0, f0);
                            sh(v0, sp, 0xF0);
                            lw(a0, s0, 328);
                            a1 = addiu(sp, 0x12C);
                            a2 = a1;
                            a3 = a1;
                            t0 = a1;
                            jal(ctx, 0x10F62Cu, gen::fn_sub_4A5DD0_004a5dd0);
                            s1 = addiu(s1, 1);
                            s7 = 1;
                        }
                    } else {
                        // 0x0010f36c
                        charge(ctx, 4);
                        lb(v0, a0, 0);
                        sw(v0, s0, 648);
                        if (s1 != 0) {
                            // 0x0010f3ec
                            charge(ctx, 26);
                            lw(v1, s0, 8);
                            v0 = sll(s2, 3);
                            v0 = addu(v0, s2);
                            v0 = sll(v0, 1);
                            a0 = addu(v1, v0);
                            lwc1(f0, s4, 984);
                            cvt_w_s(f0, f0);
                            mfc1(v1, f0);
                            lh(v0, a0, 10);
                            v0 = addu(v1, v0);
                            mtc1(v0, f0);
                            cvt_s_w(f12, f0);
                            lwc1(f0, s4, 988);
                            cvt_w_s(f0, f0);
                            mfc1(v1, f0);
                            lh(v0, a0, 12);
                            v1 = addu(v1, v0);
                            v0 = 448;
                            v0 = subu(v0, v1);
                            mtc1(v0, f0);
                            cvt_s_w(f13, f0);
                            lw(a0, s0, 168);
                            jal(ctx, 0x10F44Cu, gen::fn_sub_4AB2C0_004ab2c0);
                        } else {
                            // 0x0010f37c
                            charge(ctx, 28);
                            lw(v1, s0, 8);
                            v0 = sll(s2, 3);
                            v0 = addu(v0, s2);
                            v0 = sll(v0, 1);
                            a0 = addu(v1, v0);
                            lwc1(f0, s4, 984);
                            cvt_w_s(f0, f0);
                            mfc1(v1, f0);
                            lh(v0, a0, 10);
                            v0 = addu(v1, v0);
                            mtc1(v0, f0);
                            cvt_s_w(f12, f0);
                            lwc1(f0, s4, 988);
                            cvt_w_s(f0, f0);
                            mfc1(v1, f0);
                            lh(v0, a0, 12);
                            v1 = addu(v1, v0);
                            v0 = 448;
                            v0 = subu(v0, v1);
                            mtc1(v0, f0);
                            cvt_s_w(f13, f0);
                            lw(a0, s0, 168);
                            jal(ctx, 0x10F3DCu, gen::fn_sub_4AB200_004ab200);
                        }
                        // 0x0010f454
                        charge(ctx, 39);
                        lw(v1, s0, 8);
                        v0 = sll(s2, 3);
                        v0 = addu(v0, s2);
                        v0 = sll(v0, 1);
                        a0 = addu(v1, v0);
                        lwc1(f0, s4, 984);
                        cvt_w_s(f0, f0);
                        mfc1(v1, f0);
                        lh(v0, a0, 10);
                        v0 = addu(v1, v0);
                        fp = dsll32(v0, 16);
                        fp = dsra32(fp, 16);
                        lwc1(f0, s4, 988);
                        cvt_w_s(f0, f0);
                        mfc1(v1, f0);
                        lh(v0, a0, 12);
                        v0 = addu(v1, v0);
                        mtc1(v0, f0);
                        cvt_s_w(f1, f0);
                        v0 = 0x43E00000;
                        mtc1(v0, f0);
                        sub_s(f0, f0, f1);
                        cvt_w_s(f0, f0);
                        mfc1(v0, f0);
                        sh(v0, sp, 0xF0);
                        lw(a0, s0, 328);
                        a1 = addiu(sp, 0x12C);
                        a2 = a1;
                        a3 = a1;
                        t0 = a1;
                        jal(ctx, 0x10F4D8u, gen::fn_sub_4A5DD0_004a5dd0);
                        s7 = 1;
                        s1 = addiu(s1, 1);
                    }
                } else {
                    // 0x0010f1b8
                    charge(ctx, 2);
                    if (s1 != 0) {
                        // 0x0010f1c0
                        charge(ctx, 3);
                        v0 = slti(s1, 3);
                        if (v0 == 0) {
                            // 0x0010f1cc
                            charge(ctx, 3);
                            lw(a0, s0, 168);
                            jal(ctx, 0x10F1D0u, gen::fn_sub_4AB6A0_004ab6a0);
                        }
                        // 0x0010f1d8
                        charge(ctx, 13);
                        lw(a0, s0, 168);
                        jal(ctx, 0x10F1DCu, gen::fn_sub_4AC710_004ac710);
                        jal(ctx, 0x10F1E4u, gen::fn_sub_4AAA60_004aaa60);
                        mtc1(zero, f12);
                        mov_s(f13, f12);
                        jal(ctx, 0x10F1F8u, gen::fn_sub_4AAE00_004aae00);
                        at = slti(s1, 3);
                        if (at == 0) {
                            // 0x0010f224
                            charge(ctx, 4);
                            lw(a0, s0, 168);
                            lw(a1, s0, 328);
                            jal(ctx, 0x10F22Cu, gen::fn_sub_4A6600_004a6600);
                        } else {
                            // 0x0010f20c
                            charge(ctx, 6);
                            lw(a0, s0, 168);
                            lw(a1, s0, 328);
                            jal(ctx, 0x10F214u, gen::fn_sub_4ACE70_004ace70);
                        }
                        // 0x0010f234
                        charge(ctx, 9);
                        jal(ctx, 0x10F234u, gen::fn_sub_4AAD50_004aad50);
                        lw(a0, s0, 168);
                        jal(ctx, 0x10F240u, gen::fn_sub_4AC5F0_004ac5f0);
                        lw(a0, s0, 168);
                        jal(ctx, 0x10F24Cu, gen::fn_sub_4AB1B0_004ab1b0);
                        s1 = 0;
                    }
                    // 0x0010f258
                    charge(ctx, 66);
                    v0 = sll(s2, 3);
                    v0 = addu(v0, s2);
                    s7 = sll(v0, 1);
                    lw(v0, s0, 8);
                    v0 = addu(v0, s7);
                    lb(v0, v0, 0);
                    sw(v0, s0, 648);
                    lw(v0, s0, 8);
                    a0 = addu(v0, s7);
                    lwc1(f0, s4, 984);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    lh(v0, a0, 10);
                    v0 = addu(v1, v0);
                    mtc1(v0, f0);
                    cvt_s_w(f12, f0);
                    lwc1(f0, s4, 988);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    lh(v0, a0, 12);
                    v1 = addu(v1, v0);
                    v0 = 448;
                    v0 = subu(v0, v1);
                    mtc1(v0, f0);
                    cvt_s_w(f13, f0);
                    lw(a0, s0, 168);
                    jal(ctx, 0x10F2C8u, gen::fn_sub_4AB200_004ab200);
                    lw(v0, s0, 8);
                    a0 = addu(v0, s7);
                    lwc1(f0, s4, 984);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    lh(v0, a0, 10);
                    v0 = addu(v1, v0);
                    fp = dsll32(v0, 16);
                    fp = dsra32(fp, 16);
                    lwc1(f0, s4, 988);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    lh(v0, a0, 12);
                    v0 = addu(v1, v0);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    v0 = 0x43E00000;
                    mtc1(v0, f0);
                    sub_s(f0, f0, f1);
                    cvt_w_s(f0, f0);
                    mfc1(v0, f0);
                    sh(v0, sp, 0xF0);
                    lw(a0, s0, 328);
                    a1 = addiu(sp, 0x12C);
                    a2 = a1;
                    a3 = a1;
                    t0 = a1;
                    jal(ctx, 0x10F348u, gen::fn_sub_4A5DD0_004a5dd0);
                    s1 = addiu(s1, 1);
                    s7 = 1;
                }
                // 0x0010f63c
                charge(ctx, 3);
                s2 = addiu(s2, 1);
                backedge(ctx);
            }
            // 0x0010efbc
            charge(ctx, 2);
            if (s7 == 0) {
                // 0x0010f10c
                charge(ctx, 5);
                lw(a0, s5, 0);
                jal(ctx, 0x10F110u, gen::fn_sub_4AC710_004ac710);
            } else {
                // 0x0010efc4
                charge(ctx, 3);
                v0 = slti(s1, 3);
                if (v0 == 0) {
                    // 0x0010efd0
                    charge(ctx, 3);
                    lw(a0, s5, 0);
                    jal(ctx, 0x10EFD4u, gen::fn_sub_4AB6A0_004ab6a0);
                }
                // 0x0010efdc
                charge(ctx, 16);
                v0 = sll(s3, 2);
                s2 = addu(s4, v0);
                lw(a0, s5, 0);
                jal(ctx, 0x10EFE8u, gen::fn_sub_4AC710_004ac710);
                jal(ctx, 0x10EFF0u, gen::fn_sub_4AAA60_004aaa60);
                mtc1(zero, f12);
                mov_s(f13, f12);
                jal(ctx, 0x10F004u, gen::fn_sub_4AAE00_004aae00);
                lw(v1, s2, 648);
                v0 = 1;
                if (v1 != v0) {
                    // 0x0010f068
                    charge(ctx, 3);
                    v0 = 2;
                    if (v1 == v0) {
                        // 0x0010f074
                        charge(ctx, 4);
                        v1 = 0;
                        a1 = addiu(s3, -1);
                        for (;;) {
                            // 0x0010f0c8
                            charge(ctx, 2);
                            if (i64(a1) < 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x0010f084
                            charge(ctx, 5);
                            v0 = sll(a1, 2);
                            s2 = addu(s4, v0);
                            lw(v0, s2, 648);
                            if (v0 == 0) {
                                goto L_0010f098_44;
                            }
                            // 0x0010f0c4
                            charge(ctx, 1);
                            a1 = addiu(a1, -1);
                        }
                    L_0010f0d0:
                        charge(ctx, 2);
                        if (v1 == 0) {
                            // 0x0010f0d8
                            charge(ctx, 3);
                            v0 = slti(s1, 3);
                            if (v0 == 0) {
                                // 0x0010f0e4
                                charge(ctx, 6);
                                v0 = sll(s3, 2);
                                v0 = addu(s4, v0);
                                lw(a0, s5, 0);
                                lw(a1, v0, 328);
                                jal(ctx, 0x10F0F4u, gen::fn_sub_4A6600_004a6600);
                            }
                        }
                    }
                } else {
                    // 0x0010f01c
                    charge(ctx, 3);
                    at = slti(s1, 3);
                    if (at == 0) {
                        // 0x0010f048
                        charge(ctx, 8);
                        v0 = sll(s3, 2);
                        v0 = addu(s4, v0);
                        lw(a0, s5, 0);
                        lw(a1, v0, 328);
                        jal(ctx, 0x10F058u, gen::fn_sub_4A6600_004a6600);
                    } else {
                        // 0x0010f028
                        charge(ctx, 8);
                        v0 = sll(s3, 2);
                        v0 = addu(s4, v0);
                        lw(a0, s5, 0);
                        lw(a1, v0, 328);
                        jal(ctx, 0x10F038u, gen::fn_sub_4ACE70_004ace70);
                    }
                }
                // 0x0010f0fc
                charge(ctx, 4);
                jal(ctx, 0x10F0FCu, gen::fn_sub_4AAD50_004aad50);
            }
            // 0x0010f648
            charge(ctx, 3);
            lw(v0, sp, 0xE0);
            if (v0 != 0) {
                // 0x0010f654
                charge(ctx, 3);
                v0 = 1;
                if (s6 != v0) {
                    // 0x0010f660
                    charge(ctx, 1);
                    s6 = addiu(s6, 1);
                }
            }
            // 0x0010f664
            charge(ctx, 1);
            s3 = addiu(s3, 1);
        }
        // 0x0010f678
        charge(ctx, 4);
        jal(ctx, 0x10F678u, gen::fn_sub_4AAD50_004aad50);
        jal(ctx, 0x10F680u, gen::fn_sub_4AAD50_004aad50);
    }
    // 0x0010f688 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0x130);
    return;
L_0010f098_44:
    charge(ctx, 11);
    a0 = s4;
    a2 = s3;
    jal(ctx, 0x10F0A0u, gen::fn_sub_110650_00110650);
    lw(a0, s2, 168);
    lw(a1, s0, 328);
    jal(ctx, 0x10F0B0u, gen::fn_sub_4A6600_004a6600);
    v1 = 1;
    goto L_0010f0d0;
}

// 0x0010F6C0 sub_10F6C0 -- 3092 bytes; frame 0x130: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_CutInDraw_Update] Update of the "H_CutInDraw" task: the same camera / render-state set-up and keyframe walk as
// sub_10EC50, run every frame unless +0x4E8 (pause) is set; advances the per-layer key indices.
void sub_10F6C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15}, f16{ctx, 16}, f17{ctx, 17};
    // 0x0010f6c0
    enter(ctx, 51);  // entry check point + this block's cycles
    sp = addiu(sp, -0x130);
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
    lw(s4, a0, task::kWork);
    s0 = 0x960000;
    s0 = addiu(s0, rw::kRenderStateSet);  // &pfn_RwRenderStateSet
    a0 = 8;
    a1 = 0;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x10F704u, v0.u());
    a0 = 6;
    a1 = 0;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x10F718u, v0.u());
    v0 = 0x3F000000;
    mtc1(v0, f12);
    jal(ctx, 0x10F728u, gen::fn_sub_4AA390_004aa390);
    jal(ctx, 0x10F730u, gen::fn_sub_198590_00198590);
    lwc1(f1, gp, fx::kGpCutInFloat0);  // 0x7CAFF4
    lwc1(f0, v0, 128);
    mul_s(f12, f1, f0);
    jal(ctx, 0x10F744u, gen::fn_sub_4AA3D0_004aa3d0);
    mtc1(zero, f12);
    v0 = 0x44200000;
    mtc1(v0, f14);
    v0 = 0x43E00000;
    mtc1(v0, f15);
    mov_s(f13, f12);
    jal(ctx, 0x10F764u, gen::fn_sub_4A9F20_004a9f20);
    jal(ctx, 0x10F76Cu, gen::fn_sub_198590_00198590);
    a0 = v0;
    jal(ctx, 0x10F778u, gen::fn_sub_4AA410_004aa410);
    lw(v0, s4, 1252);
    if (v0 == 0) {
        // 0x0010f7b8
        charge(ctx, 9);
        a0 = 2;
        a1 = 68;
        jal(ctx, 0x10F7C0u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x17FB;
        jal(ctx, 0x10F7D4u, gen::fn_RpSkyRenderStateSet_004d7f60);
    } else {
        // 0x0010f78c
        charge(ctx, 11);
        a0 = 2;
        a1 = 72;
        jal(ctx, 0x10F794u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x1801;
        jal(ctx, 0x10F7A8u, gen::fn_RpSkyRenderStateSet_004d7f60);
    }
    // 0x0010f7dc
    charge(ctx, 4);
    lw(a0, s4, 0);
    v0 = 3;
    if (a0 != v0) {
        // 0x0010f7ec
        charge(ctx, 3);
        v1 = 2;
        if (a0 != v1) {
            // 0x0010f7f8
            charge(ctx, 3);
            v0 = 1;
            if (a0 == v0) {
                // 0x0010f960
                charge(ctx, 3);
                sw(v1, s4, 0);
            } else {
                // 0x0010f804
                charge(ctx, 2);
                if (a0 == 0) {
                    // 0x0010f814
                    charge(ctx, 3);
                    s0 = 0;
                    for (;;) {
                        // 0x0010f860
                        charge(ctx, 4);
                        lw(v0, s4, 1248);
                        v0 = slt(s0, v0);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x0010f820
                        charge(ctx, 16);
                        v0 = sll(s0, 2);
                        s2 = addu(s4, v0);
                        s1 = addiu(s2, 328);
                        jal(ctx, 0x10F82Cu, gen::fn_sub_4A5470_004a5470);
                        sw(v0, s1, 0);
                        a0 = v0;
                        a1 = addiu(gp, fx::kGpCutInFmt);  // &0x7CB568
                        a2 = a1;
                        a3 = a1;
                        t0 = a1;
                        jal(ctx, 0x10F84Cu, gen::fn_sub_4A5DD0_004a5dd0);
                        v0 = si(-1);
                        sw(v0, s2, 648);
                        s0 = addiu(s0, 1);
                    }
                    // 0x0010f870
                    charge(ctx, 3);
                    s0 = 0;
                    for (;;) {
                        // 0x0010f8c0
                        charge(ctx, 4);
                        lw(v0, s4, 1248);
                        v0 = slt(s0, v0);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x0010f87c
                        charge(ctx, 17);
                        v0 = sll(s0, 2);
                        s2 = addu(s4, v0);
                        s1 = addiu(s2, 168);
                        jal(ctx, 0x10F888u, gen::fn_sub_4AC570_004ac570);
                        sw(v0, s1, 0);
                        a0 = v0;
                        jal(ctx, 0x10F898u, gen::fn_sub_4AC5F0_004ac5f0);
                        lw(a0, s1, 0);
                        jal(ctx, 0x10F8A4u, gen::fn_sub_4AB1B0_004ab1b0);
                        lw(a0, s1, 0);
                        jal(ctx, 0x10F8B0u, gen::fn_sub_4AC5F0_004ac5f0);
                        sw(zero, s2, 488);
                        s0 = addiu(s0, 1);
                    }
                    // 0x0010f8d0
                    charge(ctx, 7);
                    lw(a1, s4, 4);
                    sw(a1, s4, 8);
                    a3 = 0;
                    a2 = 1;
                    a0 = si(-2);
                    for (;;) {
                        // 0x0010f940
                        charge(ctx, 4);
                        lw(v0, s4, 1248);
                        v0 = slt(a2, v0);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        for (;;) {
                            // 0x0010f8ec
                            charge(ctx, 7);
                            v0 = sll(a3, 3);
                            v0 = addu(v0, a3);
                            v0 = sll(v0, 1);
                            v0 = addu(a1, v0);
                            lb(v0, v0, 1);
                            if (v0 == a0) {
                                break;
                            }
                            // 0x0010f930
                            charge(ctx, 3);
                            a3 = addiu(a3, 1);
                            backedge(ctx);
                        }
                        // 0x0010f908
                        charge(ctx, 10);
                        a3 = addiu(a3, 1);
                        v0 = sll(a3, 3);
                        v0 = addu(v0, a3);
                        v0 = sll(v0, 1);
                        v1 = addu(a1, v0);
                        v0 = sll(a2, 2);
                        v0 = addu(s4, v0);
                        sw(v1, v0, 8);
                        // 0x0010f93c
                        charge(ctx, 1);
                        a2 = addiu(a2, 1);
                    }
                    // 0x0010f950
                    charge(ctx, 4);
                    v0 = 1;
                    sw(v0, s4, 0);
                } else {
                    // 0x0010f80c
                    charge(ctx, 2);
                }
            }
        }
        goto L_0011029c;
    }
    // 0x0010f96c
    charge(ctx, 3);
    lw(v0, s4, 1256);
    if (v0 == 0) {
        // 0x0010f984
        charge(ctx, 10);
        jal(ctx, 0x10F984u, gen::fn_sub_4AAA60_004aaa60);
        jal(ctx, 0x10F98Cu, gen::fn_sub_4A9BF0_004a9bf0);
        jal(ctx, 0x10F994u, gen::fn_sub_4AAA60_004aaa60);
        s6 = 0;
        s0 = 0;
        for (;;) {
            // 0x0011027c
            charge(ctx, 4);
            lw(v0, s4, 1248);
            v0 = slt(s0, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0010f9ac
            charge(ctx, 20);
            sw(zero, sp, 0xE0);
            s2 = 0;
            s7 = 0;
            sw(zero, sp, 0xD0);
            v0 = sll(s0, 2);
            s1 = addu(s4, v0);
            lw(s3, s1, 488);
            s5 = addiu(s1, 168);
            lw(a0, s1, 168);
            jal(ctx, 0x10F9D0u, gen::fn_sub_4AC5F0_004ac5f0);
            lw(a0, s5, 0);
            jal(ctx, 0x10F9DCu, gen::fn_sub_4AB1B0_004ab1b0);
            v0 = sll(s0, 1);
            v0 = addu(s4, v0);
            sq(v0, sp, 0xC0);
            v0 = sll(s6, 2);
            v0 = addu(s4, v0);
            sq(v0, sp, 0xB0);
            for (;;) {
                // 0x0010f9fc
                charge(ctx, 3);
                lw(v0, sp, 0xD0);
                if (v0 == 0) {
                    // 0x0010fa08
                    charge(ctx, 9);
                    lw(v1, s1, 8);
                    v0 = sll(s3, 3);
                    v0 = addu(v0, s3);
                    v0 = sll(v0, 1);
                    a2 = addu(v1, v0);
                    lb(v1, a2, 1);
                    v0 = si(-1);
                    if (v1 != v0) {
                        // 0x0010fa2c
                        charge(ctx, 4);
                        lhu(v0, a2, 2);
                        at = slti(v0, 256);
                        if (at != 0) {
                            // 0x0010fa48
                            charge(ctx, 3);
                            v0 = v0 & 0xFF;
                            a1 = dsll32(v0, 16);
                            a1 = dsra32(a1, 16);
                        } else {
                            // 0x0010fa3c
                            charge(ctx, 3);
                            a1 = 255;
                        }
                        // 0x0010fa54
                        charge(ctx, 4);
                        lhu(v0, a2, 4);
                        at = slti(v0, 256);
                        if (at != 0) {
                            // 0x0010fa70
                            charge(ctx, 3);
                            v0 = v0 & 0xFF;
                            a0 = dsll32(v0, 16);
                            a0 = dsra32(a0, 16);
                        } else {
                            // 0x0010fa64
                            charge(ctx, 3);
                            a0 = 255;
                        }
                        // 0x0010fa7c
                        charge(ctx, 4);
                        lhu(v0, a2, 6);
                        at = slti(v0, 256);
                        if (at != 0) {
                            // 0x0010fa98
                            charge(ctx, 3);
                            v0 = v0 & 0xFF;
                            v1 = dsll32(v0, 16);
                            v1 = dsra32(v1, 16);
                        } else {
                            // 0x0010fa8c
                            charge(ctx, 3);
                            v1 = 255;
                        }
                        // 0x0010faa4
                        charge(ctx, 4);
                        lhu(v0, a2, 8);
                        at = slti(v0, 256);
                        if (at != 0) {
                            // 0x0010fac0
                            charge(ctx, 1);
                            v0 = v0 & 0xFF;
                        } else {
                            // 0x0010fab4
                            charge(ctx, 3);
                            v0 = 255;
                        }
                        // 0x0010fac4
                        charge(ctx, 19);
                        v0 = dsll32(v0, 16);
                        v0 = dsra32(v0, 16);
                        lq(a2, sp, 0xC0);
                        lh(a2, a2, 1008);
                        a1 = addu(a1, a2);
                        a1 = dsll32(a1, 16);
                        a1 = dsra32(a1, 16);
                        lq(a2, sp, 0xC0);
                        lh(a2, a2, 1088);
                        a0 = addu(a0, a2);
                        a0 = dsll32(a0, 16);
                        a0 = dsra32(a0, 16);
                        lq(a2, sp, 0xC0);
                        lh(a2, a2, 1168);
                        v1 = addu(v1, a2);
                        v1 = dsll32(v1, 16);
                        v1 = dsra32(v1, 16);
                        if (i64(a1) < 0) {
                            // 0x0010fb10
                            charge(ctx, 1);
                            a1 = 0;
                        }
                        // 0x0010fb14
                        charge(ctx, 5);
                        a2 = dsll32(a1, 16);
                        a2 = dsra32(a2, 16);
                        at = slti(a2, 256);
                        if (at == 0) {
                            // 0x0010fb28
                            charge(ctx, 1);
                            a1 = 255;
                        }
                        // 0x0010fb2c
                        charge(ctx, 4);
                        a2 = dsll32(a0, 16);
                        a2 = dsra32(a2, 16);
                        if (i64(a2) < 0) {
                            // 0x0010fb3c
                            charge(ctx, 1);
                            a0 = 0;
                        }
                        // 0x0010fb40
                        charge(ctx, 5);
                        a2 = dsll32(a0, 16);
                        a2 = dsra32(a2, 16);
                        at = slti(a2, 256);
                        if (at == 0) {
                            // 0x0010fb54
                            charge(ctx, 1);
                            a0 = 255;
                        }
                        // 0x0010fb58
                        charge(ctx, 4);
                        a2 = dsll32(v1, 16);
                        a2 = dsra32(a2, 16);
                        if (i64(a2) < 0) {
                            // 0x0010fb68
                            charge(ctx, 1);
                            v1 = 0;
                        }
                        // 0x0010fb6c
                        charge(ctx, 5);
                        a2 = dsll32(v1, 16);
                        a2 = dsra32(a2, 16);
                        at = slti(a2, 256);
                        if (at == 0) {
                            // 0x0010fb80
                            charge(ctx, 1);
                            v1 = 255;
                        }
                        // 0x0010fb84
                        charge(ctx, 6);
                        sb(a1, sp, 0x12C);
                        sb(a0, sp, 0x12D);
                        sb(v1, sp, 0x12E);
                        sb(v0, sp, 0x12F);
                        v0 = 1;
                        sw(v0, sp, 0xD0);
                    }
                }
                // 0x0010fb9c
                charge(ctx, 10);
                lw(v1, s1, 8);
                v0 = sll(s3, 3);
                v0 = addu(v0, s3);
                v0 = sll(v0, 1);
                sq(v0, sp, 0xA0);
                a0 = addu(v1, v0);
                lb(v1, a0, 1);
                v0 = si(-1);
                if (v1 == v0) {
                    break;
                }
                // 0x0010fd34
                charge(ctx, 2);
                if (v1 != v0) {
                    // 0x0010fd3c
                    charge(ctx, 4);
                    lb(v1, a0, 0);
                    v0 = 2;
                    if (v1 == v0) {
                        // 0x0010fd4c
                        charge(ctx, 3);
                        lw(v0, sp, 0xE0);
                        if (v0 == 0) {
                            // 0x0010fd58
                            charge(ctx, 23);
                            v0 = 1;
                            sw(v0, sp, 0xE0);
                            lw(a0, s1, 328);
                            lq(v0, sp, 0xB0);
                            lw(a1, v0, 808);
                            jal(ctx, 0x10FD6Cu, gen::fn_sub_4A62E0_004a62e0);
                            sw(zero, sp, 0x100);
                            lwc1(f0, gp, fx::kGpCutInFloat1);  // 0x7CAFF8
                            swc1(f0, sp, 0x104);
                            swc1(f0, sp, 0x108);
                            swc1(f0, sp, 0x10C);
                            swc1(f0, sp, 0x110);
                            sw(zero, sp, 0x114);
                            sw(zero, sp, 0x118);
                            sw(zero, sp, 0x11C);
                            lw(a0, s1, 328);
                            a1 = addiu(sp, 0x100);
                            a2 = addiu(sp, 0x108);
                            a3 = addiu(sp, 0x110);
                            t0 = addiu(sp, 0x118);
                            jal(ctx, 0x10FDACu, gen::fn_sub_4A6200_004a6200);
                        }
                    }
                }
                // 0x0010fdb4
                charge(ctx, 6);
                lw(v1, s1, 8);
                lq(v0, sp, 0xA0);
                a0 = addu(v1, v0);
                lb(v1, a0, 1);
                if (v1 != 0) {
                    // 0x0010ff74
                    charge(ctx, 3);
                    v0 = 1;
                    if (v1 != v0) {
                        // 0x00110104
                        charge(ctx, 3);
                        v0 = 2;
                        if (v1 == v0) {
                            // 0x00110110
                            charge(ctx, 80);
                            v0 = sll(s3, 3);
                            v0 = addu(v0, s3);
                            s7 = sll(v0, 1);
                            lb(v0, a0, 0);
                            sw(v0, s1, 648);
                            lw(v0, s1, 8);
                            a2 = addu(v0, s7);
                            lwc1(f0, s4, 988);
                            cvt_w_s(f0, f0);
                            mfc1(a1, f0);
                            lwc1(f0, s4, 984);
                            cvt_w_s(f0, f0);
                            mfc1(a0, f0);
                            mtc1(fp, f0);
                            cvt_s_w(f12, f0);
                            lh(v0, sp, 0xF0);
                            mtc1(v0, f0);
                            cvt_s_w(f13, f0);
                            lh(v0, a2, 10);
                            v0 = addu(a0, v0);
                            mtc1(v0, f0);
                            cvt_s_w(f14, f0);
                            lh(v0, a2, 12);
                            v0 = addu(a1, v0);
                            v1 = 448;
                            v0 = subu(v1, v0);
                            mtc1(v0, f0);
                            cvt_s_w(f15, f0);
                            lh(v0, a2, 14);
                            v0 = addu(a0, v0);
                            mtc1(v0, f0);
                            cvt_s_w(f16, f0);
                            lh(v0, a2, 16);
                            v0 = addu(a1, v0);
                            v0 = subu(v1, v0);
                            mtc1(v0, f0);
                            cvt_s_w(f17, f0);
                            lw(a0, s1, 168);
                            jal(ctx, 0x1101C0u, gen::fn_sub_4AB410_004ab410);
                            lw(v0, s1, 8);
                            a0 = addu(v0, s7);
                            lwc1(f0, s4, 984);
                            cvt_w_s(f0, f0);
                            mfc1(v1, f0);
                            lh(v0, a0, 14);
                            v0 = addu(v1, v0);
                            fp = dsll32(v0, 16);
                            fp = dsra32(fp, 16);
                            lwc1(f0, s4, 988);
                            cvt_w_s(f0, f0);
                            mfc1(v1, f0);
                            lh(v0, a0, 16);
                            v0 = addu(v1, v0);
                            mtc1(v0, f0);
                            cvt_s_w(f1, f0);
                            v0 = 0x43E00000;
                            mtc1(v0, f0);
                            sub_s(f0, f0, f1);
                            cvt_w_s(f0, f0);
                            mfc1(v0, f0);
                            sh(v0, sp, 0xF0);
                            lw(a0, s1, 328);
                            a1 = addiu(sp, 0x12C);
                            a2 = a1;
                            a3 = a1;
                            t0 = a1;
                            jal(ctx, 0x110240u, gen::fn_sub_4A5DD0_004a5dd0);
                            s2 = addiu(s2, 1);
                            s7 = 1;
                        }
                    } else {
                        // 0x0010ff80
                        charge(ctx, 4);
                        lb(v0, a0, 0);
                        sw(v0, s1, 648);
                        if (s2 != 0) {
                            // 0x00110000
                            charge(ctx, 26);
                            lw(v1, s1, 8);
                            v0 = sll(s3, 3);
                            v0 = addu(v0, s3);
                            v0 = sll(v0, 1);
                            a0 = addu(v1, v0);
                            lwc1(f0, s4, 984);
                            cvt_w_s(f0, f0);
                            mfc1(v1, f0);
                            lh(v0, a0, 10);
                            v0 = addu(v1, v0);
                            mtc1(v0, f0);
                            cvt_s_w(f12, f0);
                            lwc1(f0, s4, 988);
                            cvt_w_s(f0, f0);
                            mfc1(v1, f0);
                            lh(v0, a0, 12);
                            v1 = addu(v1, v0);
                            v0 = 448;
                            v0 = subu(v0, v1);
                            mtc1(v0, f0);
                            cvt_s_w(f13, f0);
                            lw(a0, s1, 168);
                            jal(ctx, 0x110060u, gen::fn_sub_4AB2C0_004ab2c0);
                        } else {
                            // 0x0010ff90
                            charge(ctx, 28);
                            lw(v1, s1, 8);
                            v0 = sll(s3, 3);
                            v0 = addu(v0, s3);
                            v0 = sll(v0, 1);
                            a0 = addu(v1, v0);
                            lwc1(f0, s4, 984);
                            cvt_w_s(f0, f0);
                            mfc1(v1, f0);
                            lh(v0, a0, 10);
                            v0 = addu(v1, v0);
                            mtc1(v0, f0);
                            cvt_s_w(f12, f0);
                            lwc1(f0, s4, 988);
                            cvt_w_s(f0, f0);
                            mfc1(v1, f0);
                            lh(v0, a0, 12);
                            v1 = addu(v1, v0);
                            v0 = 448;
                            v0 = subu(v0, v1);
                            mtc1(v0, f0);
                            cvt_s_w(f13, f0);
                            lw(a0, s1, 168);
                            jal(ctx, 0x10FFF0u, gen::fn_sub_4AB200_004ab200);
                        }
                        // 0x00110068
                        charge(ctx, 39);
                        lw(v1, s1, 8);
                        v0 = sll(s3, 3);
                        v0 = addu(v0, s3);
                        v0 = sll(v0, 1);
                        a0 = addu(v1, v0);
                        lwc1(f0, s4, 984);
                        cvt_w_s(f0, f0);
                        mfc1(v1, f0);
                        lh(v0, a0, 10);
                        v0 = addu(v1, v0);
                        fp = dsll32(v0, 16);
                        fp = dsra32(fp, 16);
                        lwc1(f0, s4, 988);
                        cvt_w_s(f0, f0);
                        mfc1(v1, f0);
                        lh(v0, a0, 12);
                        v0 = addu(v1, v0);
                        mtc1(v0, f0);
                        cvt_s_w(f1, f0);
                        v0 = 0x43E00000;
                        mtc1(v0, f0);
                        sub_s(f0, f0, f1);
                        cvt_w_s(f0, f0);
                        mfc1(v0, f0);
                        sh(v0, sp, 0xF0);
                        lw(a0, s1, 328);
                        a1 = addiu(sp, 0x12C);
                        a2 = a1;
                        a3 = a1;
                        t0 = a1;
                        jal(ctx, 0x1100ECu, gen::fn_sub_4A5DD0_004a5dd0);
                        s7 = 1;
                        s2 = addiu(s2, 1);
                    }
                } else {
                    // 0x0010fdcc
                    charge(ctx, 2);
                    if (s2 != 0) {
                        // 0x0010fdd4
                        charge(ctx, 3);
                        v0 = slti(s2, 3);
                        if (v0 == 0) {
                            // 0x0010fde0
                            charge(ctx, 3);
                            lw(a0, s1, 168);
                            jal(ctx, 0x10FDE4u, gen::fn_sub_4AB6A0_004ab6a0);
                        }
                        // 0x0010fdec
                        charge(ctx, 13);
                        lw(a0, s1, 168);
                        jal(ctx, 0x10FDF0u, gen::fn_sub_4AC710_004ac710);
                        jal(ctx, 0x10FDF8u, gen::fn_sub_4AAA60_004aaa60);
                        mtc1(zero, f12);
                        mov_s(f13, f12);
                        jal(ctx, 0x10FE0Cu, gen::fn_sub_4AAE00_004aae00);
                        at = slti(s2, 3);
                        if (at == 0) {
                            // 0x0010fe38
                            charge(ctx, 4);
                            lw(a0, s1, 168);
                            lw(a1, s1, 328);
                            jal(ctx, 0x10FE40u, gen::fn_sub_4A6600_004a6600);
                        } else {
                            // 0x0010fe20
                            charge(ctx, 6);
                            lw(a0, s1, 168);
                            lw(a1, s1, 328);
                            jal(ctx, 0x10FE28u, gen::fn_sub_4ACE70_004ace70);
                        }
                        // 0x0010fe48
                        charge(ctx, 9);
                        jal(ctx, 0x10FE48u, gen::fn_sub_4AAD50_004aad50);
                        lw(a0, s1, 168);
                        jal(ctx, 0x10FE54u, gen::fn_sub_4AC5F0_004ac5f0);
                        lw(a0, s1, 168);
                        jal(ctx, 0x10FE60u, gen::fn_sub_4AB1B0_004ab1b0);
                        s2 = 0;
                    }
                    // 0x0010fe6c
                    charge(ctx, 66);
                    v0 = sll(s3, 3);
                    v0 = addu(v0, s3);
                    s7 = sll(v0, 1);
                    lw(v0, s1, 8);
                    v0 = addu(v0, s7);
                    lb(v0, v0, 0);
                    sw(v0, s1, 648);
                    lw(v0, s1, 8);
                    a0 = addu(v0, s7);
                    lwc1(f0, s4, 984);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    lh(v0, a0, 10);
                    v0 = addu(v1, v0);
                    mtc1(v0, f0);
                    cvt_s_w(f12, f0);
                    lwc1(f0, s4, 988);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    lh(v0, a0, 12);
                    v1 = addu(v1, v0);
                    v0 = 448;
                    v0 = subu(v0, v1);
                    mtc1(v0, f0);
                    cvt_s_w(f13, f0);
                    lw(a0, s1, 168);
                    jal(ctx, 0x10FEDCu, gen::fn_sub_4AB200_004ab200);
                    lw(v0, s1, 8);
                    a0 = addu(v0, s7);
                    lwc1(f0, s4, 984);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    lh(v0, a0, 10);
                    v0 = addu(v1, v0);
                    fp = dsll32(v0, 16);
                    fp = dsra32(fp, 16);
                    lwc1(f0, s4, 988);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    lh(v0, a0, 12);
                    v0 = addu(v1, v0);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    v0 = 0x43E00000;
                    mtc1(v0, f0);
                    sub_s(f0, f0, f1);
                    cvt_w_s(f0, f0);
                    mfc1(v0, f0);
                    sh(v0, sp, 0xF0);
                    lw(a0, s1, 328);
                    a1 = addiu(sp, 0x12C);
                    a2 = a1;
                    a3 = a1;
                    t0 = a1;
                    jal(ctx, 0x10FF5Cu, gen::fn_sub_4A5DD0_004a5dd0);
                    s2 = addiu(s2, 1);
                    s7 = 1;
                }
                // 0x00110250
                charge(ctx, 3);
                s3 = addiu(s3, 1);
                backedge(ctx);
            }
            // 0x0010fbc4
            charge(ctx, 2);
            if (s7 == 0) {
                // 0x0010fd20
                charge(ctx, 5);
                lw(a0, s5, 0);
                jal(ctx, 0x10FD24u, gen::fn_sub_4AC710_004ac710);
            } else {
                // 0x0010fbcc
                charge(ctx, 3);
                v0 = slti(s2, 3);
                if (v0 == 0) {
                    // 0x0010fbd8
                    charge(ctx, 3);
                    lw(a0, s5, 0);
                    jal(ctx, 0x10FBDCu, gen::fn_sub_4AB6A0_004ab6a0);
                }
                // 0x0010fbe4
                charge(ctx, 16);
                v0 = sll(s0, 2);
                s3 = addu(s4, v0);
                lw(a0, s5, 0);
                jal(ctx, 0x10FBF0u, gen::fn_sub_4AC710_004ac710);
                jal(ctx, 0x10FBF8u, gen::fn_sub_4AAA60_004aaa60);
                mtc1(zero, f12);
                mov_s(f13, f12);
                jal(ctx, 0x10FC0Cu, gen::fn_sub_4AAE00_004aae00);
                lw(v1, s3, 648);
                v0 = 1;
                if (v1 != v0) {
                    // 0x0010fc70
                    charge(ctx, 3);
                    v0 = 2;
                    if (v1 == v0) {
                        // 0x0010fc7c
                        charge(ctx, 4);
                        v1 = 0;
                        a1 = addiu(s0, -1);
                        for (;;) {
                            // 0x0010fcdc
                            charge(ctx, 2);
                            if (i64(a1) < 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x0010fc8c
                            charge(ctx, 5);
                            v0 = sll(a1, 2);
                            s3 = addu(s4, v0);
                            lw(v0, s3, 648);
                            if (v0 == 0) {
                                goto L_0010fca0_64;
                            }
                            // 0x0010fcd8
                            charge(ctx, 1);
                            a1 = addiu(a1, -1);
                        }
                    L_0010fce4:
                        charge(ctx, 2);
                        if (v1 == 0) {
                            // 0x0010fcec
                            charge(ctx, 3);
                            v0 = slti(s2, 3);
                            if (v0 == 0) {
                                // 0x0010fcf8
                                charge(ctx, 6);
                                v0 = sll(s0, 2);
                                v0 = addu(s4, v0);
                                lw(a0, s5, 0);
                                lw(a1, v0, 328);
                                jal(ctx, 0x10FD08u, gen::fn_sub_4A6600_004a6600);
                            }
                        }
                    }
                } else {
                    // 0x0010fc24
                    charge(ctx, 3);
                    at = slti(s2, 3);
                    if (at == 0) {
                        // 0x0010fc50
                        charge(ctx, 8);
                        v0 = sll(s0, 2);
                        v0 = addu(s4, v0);
                        lw(a0, s5, 0);
                        lw(a1, v0, 328);
                        jal(ctx, 0x10FC60u, gen::fn_sub_4A6600_004a6600);
                    } else {
                        // 0x0010fc30
                        charge(ctx, 8);
                        v0 = sll(s0, 2);
                        v0 = addu(s4, v0);
                        lw(a0, s5, 0);
                        lw(a1, v0, 328);
                        jal(ctx, 0x10FC40u, gen::fn_sub_4ACE70_004ace70);
                    }
                }
                // 0x0010fd10
                charge(ctx, 4);
                jal(ctx, 0x10FD10u, gen::fn_sub_4AAD50_004aad50);
            }
            // 0x0011025c
            charge(ctx, 3);
            lw(v0, sp, 0xE0);
            if (v0 != 0) {
                // 0x00110268
                charge(ctx, 3);
                v0 = 1;
                if (s6 != v0) {
                    // 0x00110274
                    charge(ctx, 1);
                    s6 = addiu(s6, 1);
                }
            }
            // 0x00110278
            charge(ctx, 1);
            s0 = addiu(s0, 1);
        }
        // 0x0011028c
        charge(ctx, 4);
        jal(ctx, 0x11028Cu, gen::fn_sub_4AAD50_004aad50);
        jal(ctx, 0x110294u, gen::fn_sub_4AAD50_004aad50);
    L_0011029c:
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x0010f978
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001102a0 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0x130);
    return;
L_0010fca0_64:
    charge(ctx, 7);
    a0 = s4;
    a2 = s0;
    jal(ctx, 0x10FCA8u, gen::fn_sub_110650_00110650);
    v0 = slti(s2, 3);
    if (v0 == 0) {
        // 0x0010fcbc
        charge(ctx, 4);
        lw(a0, s3, 168);
        lw(a1, s1, 328);
        jal(ctx, 0x10FCC4u, gen::fn_sub_4A6600_004a6600);
    }
    // 0x0010fccc
    charge(ctx, 3);
    v1 = 1;
    goto L_0010fce4;
}

// 0x001102E0 sub_1102E0 -- 256 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_CutInDraw_Destroy] Destroy callback of "H_CutInDraw": destroys the layer clumps (+0xA8.., sub_4AC390) and
// atomics (+0x148.., sub_4A5540) of the +0x4E0 layers (" destroy error" on a failure), then frees the work.
void sub_1102E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001102e0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s1, a0, task::kWork);
    s0 = 0;
    for (;;) {
        // 0x00110344
        charge(ctx, 4);
        lw(v0, s1, 1248);
        v0 = slt(s0, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00110304
        charge(ctx, 6);
        v0 = sll(s0, 2);
        v0 = addu(s1, v0);
        s2 = addiu(v0, 168);
        lw(a0, v0, 168);
        if (a0 != 0) {
            // 0x0011031c
            charge(ctx, 4);
            jal(ctx, 0x11031Cu, gen::fn_sub_4AC390_004ac390);
            if (v0 == 0) {
                // 0x0011032c
                charge(ctx, 4);
                a0 = 0x5D0000;
                a0 = addiu(a0, 22656);  // " destroy error \n"
                jal(ctx, 0x110334u, gen::fn_printf_005225a8);
            }
            // 0x0011033c
            charge(ctx, 1);
            sw(zero, s2, 0);
        }
        // 0x00110340
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x00110354
    charge(ctx, 3);
    s0 = 0;
    for (;;) {
        // 0x001103a0
        charge(ctx, 4);
        lw(v0, s1, 1248);
        v0 = slt(s0, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00110360
        charge(ctx, 6);
        v0 = sll(s0, 2);
        v0 = addu(s1, v0);
        s2 = addiu(v0, 328);
        lw(a0, v0, 328);
        if (a0 != 0) {
            // 0x00110378
            charge(ctx, 4);
            jal(ctx, 0x110378u, gen::fn_sub_4A5540_004a5540);
            if (v0 == 0) {
                // 0x00110388
                charge(ctx, 4);
                a0 = 0x5D0000;
                a0 = addiu(a0, 22656);  // " destroy error \n"
                jal(ctx, 0x110390u, gen::fn_printf_005225a8);
            }
            // 0x00110398
            charge(ctx, 1);
            sw(zero, s2, 0);
        }
        // 0x0011039c
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x001103b0
    charge(ctx, 12);
    a0 = s1;
    v0 = 0x960000;
    lw(v0, v0, rw::kFree);  // 0x96017C
    jalr(ctx, 0x1103BCu, v0.u());
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x001103E0 sub_1103E0 -- 204 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_CutInDraw_Create] Creates the "H_CutInDraw" task under `parent` (priority $a1): RwCalloc(1, 0x4EC) work,
// kwlnTaskCreate(update sub_10F6C0, destroy sub_1102E0); key data +4 = $a2, layer count +0x4E0 = $a3.
void sub_1103E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001103e0
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    s1 = a2;
    s0 = a3;
    a0 = 1;
    a1 = 1260;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, rw::kCalloc);  // 0x960184
    jalr(ctx, 0x110420u, v0.u());
    s4 = v0;
    if (s4 != 0) {
        // 0x00110440
        charge(ctx, 13);
        a0 = s3;
        a1 = 0x5D0000;
        a1 = addiu(a1, 22680);  // "H_CutInDraw"
        a2 = s2;
        a3 = 0x110000;
        a3 = addiu(a3, -2368);  // &sub_10F6C0
        t0 = 0x110000;
        t0 = addiu(t0, 736);  // &sub_1102E0
        t1 = s4;
        jal(ctx, 0x110464u, gen::fn_kwlnTaskCreate_00194b20);
        if (v0 != 0) {
            // 0x00110480
            charge(ctx, 2);
            sw(s1, s4, 4);
            sw(s0, s4, 1248);
        } else {
            // 0x00110474
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x00110434
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00110488 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x001104B0 sub_1104B0 -- 24 bytes; leaf frame (no stack)
// [H_CutInDraw_IsLoaded] The draw task's state >= 2.
void sub_1104B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x001104b0
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v0, a0, task::kWork);
    lw(v0, v0, 0);
    v0 = slti(v0, 2);
    v0 = v0 ^ 0x1;
}

// 0x001104D0 sub_1104D0 -- 52 bytes; leaf frame (no stack)
// [H_CutInDraw_Start] State 2 (ready) -> 3 (playing); returns 1, else 0.
void sub_1104D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x001104d0
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(a0, a0, task::kWork);
    lw(v1, a0, 0);
    v0 = 2;
    if (v1 != v0) {
        // 0x001104f8
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x001104e4
        charge(ctx, 5);
        v0 = 3;
        sw(v0, a0, 0);
        v0 = 1;
    }
    // 0x001104fc (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00110510 sub_110510 -- 180 bytes; leaf frame (no stack)
// [H_CutInDraw_StepKeys] While playing (state 3): per layer advances the key index (+0x1E8 + 4 * layer) past the -1
// terminator (counting finished layers in +0x3E8); returns 0 at a -2 (wait) key, 1 when every layer is through.
void sub_110510(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    // 0x00110510
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(t0, a0, task::kWork);
    lw(v1, t0, 0);
    v0 = 3;
    if (v1 == v0) {
        // 0x00110524
        charge(ctx, 5);
        t1 = 0;
        v1 = si(-2);
        a0 = si(-1);
        for (;;) {
            // 0x001105a8
            charge(ctx, 4);
            lw(v0, t0, 1248);
            v0 = slt(t1, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00110538
            charge(ctx, 2);
            v0 = sll(t1, 2);
            a3 = addu(t0, v0);
            for (;;) {
                // 0x00110540
                charge(ctx, 9);
                lw(a2, a3, 8);
                lw(a1, a3, 488);
                v0 = sll(a1, 3);
                v0 = addu(v0, a1);
                v0 = sll(v0, 1);
                v0 = addu(a2, v0);
                lb(v0, v0, 1);
                if (v0 == a0) {
                    break;
                }
                // 0x00110580
                charge(ctx, 2);
                if (v0 == v1) {
                    goto L_00110588_6;
                }
                // 0x00110594
                charge(ctx, 4);
                v0 = addiu(a1, 1);
                sw(v0, a3, 488);
                backedge(ctx);
            }
            // 0x00110564
            charge(ctx, 7);
            v0 = addiu(a1, 1);
            sw(v0, a3, 488);
            lw(v0, t0, 1000);
            v0 = addiu(v0, 1);
            sw(v0, t0, 1000);
            // 0x001105a4
            charge(ctx, 1);
            t1 = addiu(t1, 1);
        }
    }
    // 0x001105b8
    charge(ctx, 1);
    v0 = 1;
    // 0x001105bc (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_00110588_6:
    charge(ctx, 3);
    v0 = 0;
    // 0x001105bc (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x001105D0 sub_1105D0 -- 72 bytes; leaf frame (no stack)
// [H_CutInDraw_SetRaster] Raster slot `i` (< 40) of the draw work (+0x328) = $a2; a non-null raster gets its +0x50
// low byte set to 2.
void sub_1105D0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x001105d0
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(a0, a0, task::kWork);
    at = slti(a1, 40);
    if (at != 0) {
        // 0x001105e0
        charge(ctx, 6);
        v1 = sll(a1, 2);
        a0 = addu(v1, a0);
        v1 = addiu(a0, 808);
        sw(a2, a0, 808);
        if (a2 != 0) {
            // 0x001105f8
            charge(ctx, 6);
            lw(a1, v1, 0);
            lw(a0, a1, 80);
            v1 = si(-256);
            v1 = a0 & v1;
            v1 = v1 | 0x2;
            sw(v1, a1, 80);
        }
    }
    // 0x00110610 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00110620 sub_110620 -- 40 bytes; leaf frame (no stack)
// [H_CutInDraw_SetLayerColour] Layer `i` colour offsets: s16 r +0x3F0, g +0x440, b +0x490 (two bytes per layer).
void sub_110620(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x00110620
    enter(ctx, 10);  // entry check point + this block's cycles
    lw(a0, a0, task::kWork);
    v1 = dsll32(a1, 16);
    v1 = dsra32(v1, 16);
    v1 = sll(v1, 1);
    v1 = addu(v1, a0);
    sh(a2, v1, 1008);
    sh(a3, v1, 1088);
    sh(t0, v1, 1168);
}

// 0x00110650 sub_110650 -- 384 bytes; frame 0x80: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_CutInDraw_MapUv] Maps layer b's screen rectangle onto layer a's raster: reads both frames' bounds (sub_4AC120),
// computes the four UVs from the raster size (448-line screen) and sets them (sub_4A6200).
void sub_110650(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12}, f13{ctx, 13};
    // 0x00110650
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a2;
    v0 = sll(a1, 2);
    v0 = addu(v0, s1);
    lw(a0, v0, 168);
    a1 = addiu(sp, 0x50);
    jal(ctx, 0x11067Cu, gen::fn_sub_4AC120_004ac120);
    s2 = sll(s0, 2);
    v0 = addu(s2, s1);
    lw(a0, v0, 168);
    a1 = addiu(sp, 0x40);
    jal(ctx, 0x110694u, gen::fn_sub_4AC120_004ac120);
    v1 = addu(s2, s1);
    lw(a0, v1, 328);
    lw(v1, a0, 104);
    if (v1 == 0) {
        // 0x001106dc
        charge(ctx, 2);
    } else {
        // 0x001106b0
        charge(ctx, 11);
        v0 = s2;
        v0 = addu(v0, s1);
        lw(v0, v0, 328);
        lw(v0, v0, 104);
        lw(v0, v0, 0);
        lwc1(f0, v0, 12);
        cvt_s_w(f1, f0);
        lwc1(f0, v0, 16);
        cvt_s_w(f0, f0);
        // 0x001106e4
        charge(ctx, 52);
        lwc1(f13, sp, 0x40);
        lwc1(f12, sp, 0x50);
        sub_s(f4, f12, f13);
        lwc1(f11, sp, 0x4C);
        lwc1(f2, sp, 0x44);
        add_s(f2, f2, f11);
        v0 = 0x43E00000;
        mtc1(v0, f3);
        sub_s(f10, f3, f2);
        lwc1(f9, sp, 0x5C);
        lwc1(f2, sp, 0x54);
        add_s(f2, f2, f9);
        sub_s(f8, f3, f2);
        sub_s(f3, f8, f10);
        lwc1(f7, sp, 0x48);
        mul_s(f2, f4, f1);
        div_s(f6, f2, f7);
        mul_s(f2, f3, f0);
        div_s(f5, f2, f11);
        lwc1(f2, sp, 0x58);
        add_s(f2, f12, f2);
        sub_s(f4, f2, f13);
        add_s(f2, f9, f8);
        sub_s(f3, f2, f10);
        mul_s(f2, f4, f1);
        div_s(f4, f2, f7);
        mul_s(f2, f3, f0);
        div_s(f3, f2, f11);
        v0 = 0x3F800000;
        mtc1(v0, f2);
        add_s(f4, f4, f2);
        add_s(f2, f3, f2);
        div_s(f3, f6, f1);
        swc1(f3, sp, 0x60);
        div_s(f2, f2, f0);
        swc1(f2, sp, 0x64);
        div_s(f1, f4, f1);
        swc1(f1, sp, 0x68);
        swc1(f2, sp, 0x6C);
        swc1(f1, sp, 0x70);
        div_s(f0, f5, f0);
        swc1(f0, sp, 0x74);
        swc1(f3, sp, 0x78);
        swc1(f0, sp, 0x7C);
        a1 = addiu(sp, 0x60);
        a2 = addiu(sp, 0x68);
        a3 = addiu(sp, 0x70);
        t0 = addiu(sp, 0x78);
        jal(ctx, 0x1107ACu, gen::fn_sub_4A6200_004a6200);
    }
    // 0x001107b4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x001107D0 sub_1107D0 -- 1692 bytes; frame 0x1A0: ra sp+0x80, s5 sp+0x70 (sq), s4 sp+0x60 (sq), s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq)
// [H_CutInPlayer_Update] Update of "H_CutInPlayer" (jump table 0x7B5310): 0 request the .cpk (when +0x310), 1 wait, 2
// per archive entry either a texture through the resource manager (sub_10C1A0, "h_cutin.c" 1286) or the key file
// (42-byte header to +0xCC, key count by -1 / -2 markers), 4 collect the texture (sub_10C3A0), 6 create the draw task
// (H_CutInDraw inline, priority +0x30C or 5286) and hand it rasters / colours, 7 start it and fire the cut-in voice
// of the table 0x5D53E0 (sub_10A4E0), 8 count frames until +0xB8; returns -1 when done.
void sub_1107D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x001107d0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1A0);
    sd(ra, sp, 0x80);
    sq(s5, sp, 0x70);
    sq(s4, sp, 0x60);
    sq(s3, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    s4 = a0;
    lw(s2, a0, task::kWork);
    lw(v0, s2, 0);
    at = sltiu(v0, 9);
    if (at != 0) {
        // 0x00110808
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, fx::kLoJptCutInPlayer);  // &0x7B5310
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x110824u:  // table[0]
            // 0x00110824
            charge(ctx, 3);
            lw(v0, s2, 784);
            if (v0 != 0) {
                // 0x00110830
                charge(ctx, 5);
                a0 = addiu(s2, 252);
                a1 = 1;
                jal(ctx, 0x110838u, gen::fn_H_Cdvd_Request_00100d80);
                sw(v0, s2, 200);
            }
            // 0x00110844
            charge(ctx, 4);
            v0 = 1;
            sw(v0, s2, 0);
        L_00110e40:
            charge(ctx, 1);
            v0 = 0;
            break;
        case 0x110854u:  // table[1]
            // 0x00110854
            charge(ctx, 3);
            lw(v0, s2, 784);
            if (v0 == 0) {
                // 0x00110888
                charge(ctx, 5);
                sw(zero, s2, 4);
                v0 = 2;
                sw(v0, s2, 0);
            } else {
                // 0x00110860
                charge(ctx, 5);
                lw(a0, s2, 200);
                jal(ctx, 0x110864u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
                if (v0 != 0) {
                    // 0x00110874
                    charge(ctx, 5);
                    sw(zero, s2, 4);
                    v0 = 2;
                    sw(v0, s2, 0);
                }
            }
            goto L_00110e40;
        case 0x11089Cu:  // table[2]
            // 0x0011089c
            charge(ctx, 8);
            lw(v0, s2, 4);
            a1 = addiu(v0, 1);
            lw(a0, s2, 200);
            jal(ctx, 0x1108A8u, gen::fn_H_Cdvd_GetArchiveFileBuffer_001022e0);
            s0 = v0;
            if (s0 == 0) {
                // 0x00110944
                charge(ctx, 19);
                lw(a0, s2, 200);
                a1 = 0;
                a2 = addiu(sp, 0x19C);
                jal(ctx, 0x110950u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                s0 = v0;
                a0 = addiu(s2, 204);
                a1 = s0;
                a2 = 42;
                jal(ctx, 0x110968u, gen::fn_memcpy_00521250);
                a1 = addiu(s0, 42);
                sw(a1, s2, 248);
                sw(zero, s2, 184);
                a2 = 0;
                a0 = si(-2);
                v1 = si(-1);
                for (;;) {
                    // 0x001109d8
                    charge(ctx, 3);
                    v0 = slti(a2, 1000);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00110990
                    charge(ctx, 7);
                    v0 = sll(a2, 3);
                    v0 = addu(v0, a2);
                    v0 = sll(v0, 1);
                    v0 = addu(a1, v0);
                    lb(v0, v0, 1);
                    if (v0 == a0) {
                        goto L_001109ac_13;
                    }
                    // 0x001109c0
                    charge(ctx, 2);
                    if (v0 == v1) {
                        // 0x001109c8
                        charge(ctx, 3);
                        lw(v0, s2, 184);
                        v0 = addiu(v0, 1);
                        sw(v0, s2, 184);
                    }
                    // 0x001109d4
                    charge(ctx, 1);
                    a2 = addiu(a2, 1);
                }
            L_001109e4:
                charge(ctx, 4);
                v0 = 5;
                sw(v0, s2, 0);
            } else {
                // 0x001108bc
                charge(ctx, 34);
                a0 = addiu(sp, 0x90);
                a1 = addiu(s2, 508);
                jal(ctx, 0x1108C4u, gen::fn_strcpy_00524270);
                a0 = addiu(sp, 0x90);
                a1 = s0;
                jal(ctx, 0x1108D4u, gen::fn_strcat_00523e68);
                a0 = addiu(gp, -30596);  // "%s\n"
                a1 = addiu(sp, 0x90);
                jal(ctx, 0x1108E4u, gen::fn_printf_005225a8);
                sd(zero, sp, 0x0);
                sd(zero, sp, 0x8);
                v0 = 0x5D0000;
                v0 = addiu(v0, 22696);  // "h_cutin.c"
                sd(v0, sp, 0x10);
                v0 = 1286;
                sd(v0, sp, 0x18);
                a0 = 0;
                a1 = addiu(sp, 0x90);
                a2 = 0;
                a3 = 0;
                t0 = 0;
                t1 = 0;
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x110928u, gen::fn_sub_10C1A0_0010c1a0);
                sw(v0, s2, 196);
                v0 = 4;
                sw(v0, s2, 0);
            }
            goto L_00110e40;
        case 0x1109F4u:  // table[4]
            // 0x001109f4
            charge(ctx, 12);
            lw(a0, s2, 196);
            a1 = addiu(sp, 0x198);
            a2 = 0;
            jal(ctx, 0x110A00u, gen::fn_sub_10C3A0_0010c3a0);
            lw(v1, s2, 4);
            v1 = sll(v1, 2);
            v1 = addu(v1, s2);
            sw(v0, v1, 8);
            lw(v0, sp, 0x198);
            if (v0 != 0) {
                // 0x00110a24
                charge(ctx, 18);
                sw(zero, s2, 196);
                lw(v0, s2, 4);
                v0 = sll(v0, 2);
                v0 = addu(v0, s2);
                lw(a0, v0, 8);
                lw(v1, a0, 80);
                v0 = lui(0xFFFF);
                v0 = v0 | 0xFF;
                v0 = v1 & v0;
                v0 = v0 | 0x3300;
                sw(v0, a0, 80);
                lw(v0, s2, 4);
                v0 = addiu(v0, 1);
                sw(v0, s2, 4);
                v0 = 2;
                sw(v0, s2, 0);
            }
            goto L_00110e40;
        case 0x110A6Cu:  // table[6]
            // 0x00110a6c
            charge(ctx, 4);
            sw(zero, s2, 180);
            lw(v0, s2, 776);
            if (v0 == 0) {
                // 0x00110b10
                charge(ctx, 12);
                lh(s1, s2, 212);
                lw(s0, s2, 248);
                a0 = 1;
                a1 = 1260;
                a2 = 0x40000;
                v0 = 0x960000;
                lw(v0, v0, rw::kCalloc);  // 0x960184
                jalr(ctx, 0x110B2Cu, v0.u());
                s3 = v0;
                if (s3 != 0) {
                    // 0x00110b4c
                    charge(ctx, 13);
                    a0 = s4;
                    a1 = 0x5D0000;
                    a1 = addiu(a1, 22680);  // "H_CutInDraw"
                    a2 = 5286;
                    a3 = 0x110000;
                    a3 = addiu(a3, -2368);  // &sub_10F6C0
                    t0 = 0x110000;
                    t0 = addiu(t0, 736);  // &sub_1102E0
                    t1 = s3;
                    jal(ctx, 0x110B70u, gen::fn_kwlnTaskCreate_00194b20);
                    if (v0 != 0) {
                        // 0x00110b8c
                        charge(ctx, 2);
                        sw(s0, s3, 4);
                        sw(s1, s3, 1248);
                    } else {
                        // 0x00110b80
                        charge(ctx, 3);
                        v0 = 0;
                    }
                } else {
                    // 0x00110b40
                    charge(ctx, 3);
                    v0 = 0;
                }
                // 0x00110b94
                charge(ctx, 1);
                sw(v0, s2, 176);
            } else {
                // 0x00110a7c
                charge(ctx, 13);
                lh(s1, s2, 212);
                lw(s0, s2, 248);
                lw(s3, s2, 780);
                a0 = 1;
                a1 = 1260;
                a2 = 0x40000;
                v0 = 0x960000;
                lw(v0, v0, rw::kCalloc);  // 0x960184
                jalr(ctx, 0x110A9Cu, v0.u());
                s5 = v0;
                if (s5 != 0) {
                    // 0x00110abc
                    charge(ctx, 13);
                    a0 = s4;
                    a1 = 0x5D0000;
                    a1 = addiu(a1, 22680);  // "H_CutInDraw"
                    a2 = s3;
                    a3 = 0x110000;
                    a3 = addiu(a3, -2368);  // &sub_10F6C0
                    t0 = 0x110000;
                    t0 = addiu(t0, 736);  // &sub_1102E0
                    t1 = s5;
                    jal(ctx, 0x110AE0u, gen::fn_kwlnTaskCreate_00194b20);
                    if (v0 != 0) {
                        // 0x00110afc
                        charge(ctx, 2);
                        sw(s0, s5, 4);
                        sw(s1, s5, 1248);
                    } else {
                        // 0x00110af0
                        charge(ctx, 3);
                        v0 = 0;
                    }
                } else {
                    // 0x00110ab0
                    charge(ctx, 3);
                    v0 = 0;
                }
                // 0x00110b04
                charge(ctx, 3);
                sw(v0, s2, 176);
            }
            // 0x00110b98
            charge(ctx, 14);
            lw(v1, s2, 772);
            lw(v0, s2, 176);
            lw(v0, v0, 60);
            sw(v1, v0, 1252);
            lw(v0, s2, 176);
            lw(v0, v0, 60);
            lwc1(f1, s2, 764);
            lwc1(f0, s2, 768);
            swc1(f1, v0, 984);
            swc1(f0, v0, 988);
            a2 = 0;
            v1 = si(-256);
            for (;;) {
                // 0x00110c1c
                charge(ctx, 3);
                v0 = slti(a2, 2);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00110bd0
                charge(ctx, 8);
                a0 = sll(a2, 2);
                v0 = addu(s2, a0);
                lw(a1, v0, 8);
                lw(v0, s2, 176);
                lw(v0, v0, 60);
                at = slti(a2, 40);
                if (at != 0) {
                    // 0x00110bf0
                    charge(ctx, 5);
                    a0 = addu(v0, a0);
                    v0 = addiu(a0, 808);
                    sw(a1, a0, 808);
                    if (a1 != 0) {
                        // 0x00110c04
                        charge(ctx, 5);
                        lw(a0, v0, 0);
                        lw(v0, a0, 80);
                        v0 = v0 & v1;
                        v0 = v0 | 0x2;
                        sw(v0, a0, 80);
                    }
                }
                // 0x00110c18
                charge(ctx, 1);
                a2 = addiu(a2, 1);
            }
            // 0x00110c28
            charge(ctx, 7);
            t3 = 0;
            t2 = 2;
            a3 = 4;
            t0 = 3;
            t1 = 1;
            for (;;) {
                // 0x00110cac
                charge(ctx, 3);
                v0 = slti(t3, 3);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00110c44
                charge(ctx, 2);
                if (t3 != t2) {
                    // 0x00110c58
                    charge(ctx, 2);
                    if (t3 != 0) {
                        // 0x00110c6c
                        charge(ctx, 1);
                        t4 = a3;
                    } else {
                        // 0x00110c60
                        charge(ctx, 3);
                        t4 = t0;
                    }
                } else {
                    // 0x00110c4c
                    charge(ctx, 3);
                    t4 = t1;
                }
                // 0x00110c70
                charge(ctx, 15);
                v0 = sll(t3, 1);
                a2 = addu(s2, v0);
                lh(a1, a2, 230);
                lh(a0, a2, 222);
                lw(v0, s2, 176);
                lw(v1, v0, 60);
                v0 = dsll32(t4, 16);
                v0 = dsra32(v0, 16);
                v0 = sll(v0, 1);
                v1 = addu(v1, v0);
                lh(v0, a2, 214);
                sh(v0, v1, 1008);
                sh(a0, v1, 1088);
                sh(a1, v1, 1168);
                t3 = addiu(t3, 1);
            }
            // 0x00110cb8
            charge(ctx, 4);
            v0 = 7;
            sw(v0, s2, 0);
            goto L_00110e40;
        case 0x110CC8u:  // table[7]
            // 0x00110cc8
            charge(ctx, 6);
            lw(v0, s2, 176);
            lw(v0, v0, 60);
            lw(v0, v0, 0);
            v0 = slti(v0, 2);
            if (v0 == 0) {
                // 0x00110ce0
                charge(ctx, 3);
                s0 = 0;
                for (;;) {
                    // 0x00110d68
                    charge(ctx, 3);
                    v0 = slti(s0, 256);
                    if (v0 != 0) {
                        backedge(ctx);
                        // 0x00110cec
                        charge(ctx, 9);
                        v0 = sll(s0, 1);
                        v0 = addu(v0, s0);
                        v1 = sll(v0, 1);
                        v0 = 0x5D0000;
                        v0 = addiu(v0, fx::kLoCutInVoices);  // &0x5D53E0
                        a0 = addu(v0, v1);
                        lb(v1, a0, 0);
                        if (v1 != 0) {
                            // 0x00110d10
                            charge(ctx, 3);
                            lh(v0, s2, 168);
                            if (v0 == v1) {
                                // 0x00110d1c
                                charge(ctx, 4);
                                lh(v1, s2, 170);
                                lb(v0, a0, 1);
                                if (v1 == v0) {
                                    // 0x00110d2c
                                    charge(ctx, 4);
                                    lh(v1, s2, 172);
                                    lb(v0, a0, 2);
                                    if (v1 == v0) {
                                        // 0x00110d3c
                                        charge(ctx, 4);
                                        lh(v1, s2, 174);
                                        lb(v0, a0, 3);
                                        if (v1 == v0) {
                                            // 0x00110d4c
                                            charge(ctx, 6);
                                            lb(a2, a0, 4);
                                            lb(a3, a0, 5);
                                            a0 = 0;
                                            a1 = 1;
                                            jal(ctx, 0x110D5Cu, gen::fn_sub_10A4E0_0010a4e0);
                                        }
                                    }
                                }
                            }
                            // 0x00110d64
                            charge(ctx, 1);
                            s0 = addiu(s0, 1);
                            continue;
                        }
                    }
                    break;
                }
                // 0x00110d74
                charge(ctx, 6);
                lw(v0, s2, 176);
                lw(a0, v0, 60);
                lw(v1, a0, 0);
                v0 = 2;
                if (v1 == v0) {
                    // 0x00110d8c
                    charge(ctx, 2);
                    v0 = 3;
                    sw(v0, a0, 0);
                }
                // 0x00110d94
                charge(ctx, 10);
                lw(v0, s2, 176);
                lw(v0, v0, 60);
                lwc1(f1, s2, 764);
                lwc1(f0, s2, 768);
                swc1(f1, v0, 984);
                swc1(f0, v0, 988);
                v0 = 8;
                sw(v0, s2, 0);
            }
            goto L_00110e40;
        case 0x110DBCu:  // table[8]
            // 0x00110dbc
            charge(ctx, 9);
            lw(v0, s2, 176);
            lw(v0, v0, 60);
            lwc1(f1, s2, 764);
            lwc1(f0, s2, 768);
            swc1(f1, v0, 984);
            swc1(f0, v0, 988);
            lw(v0, s2, 192);
            if (v0 == 0) {
                // 0x00110de0
                charge(ctx, 3);
                lh(v1, s2, 210);
                if (v1 == 0) {
                    goto L_00110e08;
                }
                // 0x00110dec
                charge(ctx, 3);
                lw(v0, s2, 180);
                if (v0 != v1) {
                    goto L_00110e08;
                }
                // 0x00110df8
                charge(ctx, 4);
                v0 = 1;
                sw(v0, s2, 188);
                goto L_00110e40;
            }
        L_00110e08:
            charge(ctx, 11);
            lw(v0, s2, 180);
            v0 = addiu(v0, 1);
            sw(v0, s2, 180);
            lw(a0, s2, 176);
            jal(ctx, 0x110E18u, gen::fn_sub_110510_00110510);
            lw(v1, s2, 180);
            lw(v0, s2, 184);
            v0 = slt(v1, v0);
            if (v0 != 0) {
                goto L_00110e40;
            }
            // 0x00110e34
            charge(ctx, 3);
            v0 = si(-1);
            break;
        case 0x110E40u:  // table[3, 5]
            goto L_00110e40;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x00110e44 (the shared epilogue, written out on this path)
        charge(ctx, 10);
        ld(ra, sp, 0x80);
        lq(s5, sp, 0x70);
        lq(s4, sp, 0x60);
        lq(s3, sp, 0x50);
        lq(s2, sp, 0x40);
        lq(s1, sp, 0x30);
        lq(s0, sp, 0x20);
        sp = addiu(sp, 0x1A0);
        return;
    }
    goto L_00110e40;
L_001109ac_13:
    charge(ctx, 5);
    lw(v0, s2, 184);
    v0 = addiu(v0, -1);
    sw(v0, s2, 184);
    goto L_001109e4;
}

// 0x00110E70 sub_110E70 -- 260 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_CutInPlayer_Destroy] Destroy callback of "H_CutInPlayer": drops the pending texture (sub_133D30) or the .cpk
// request, destroys the 40 rasters, prints "*** CUTIN RELEASE %s" and frees the work.
void sub_110E70(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00110e70
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    lw(a0, s0, 196);
    if (a0 == 0) {
        // 0x00110ecc
        charge(ctx, 3);
        lw(v0, s0, 784);
        if (v0 != 0) {
            // 0x00110ed8
            charge(ctx, 3);
            lw(a0, s0, 200);
            if (a0 != 0) {
                // 0x00110ee4
                charge(ctx, 3);
                jal(ctx, 0x110EE4u, gen::fn_H_Cdvd_Destroy_00100ec0);
                sw(zero, s0, 200);
            }
        }
    } else {
        // 0x00110e94
        charge(ctx, 3);
        lw(v0, s0, 784);
        if (v0 == 0) {
            // 0x00110eb4
            charge(ctx, 3);
            a1 = 0;
            jal(ctx, 0x110EB8u, gen::fn_sub_133D30_00133d30);
        } else {
            // 0x00110ea0
            charge(ctx, 5);
            lw(a1, s0, 200);
            jal(ctx, 0x110EA4u, gen::fn_sub_133D30_00133d30);
        }
        // 0x00110ec0
        charge(ctx, 3);
        sw(zero, s0, 200);
    }
    // 0x00110ef0
    charge(ctx, 3);
    s2 = 0;
    for (;;) {
        // 0x00110f24
        charge(ctx, 3);
        v0 = slti(s2, 40);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00110efc
        charge(ctx, 6);
        v0 = sll(s2, 2);
        v0 = addu(s0, v0);
        s1 = addiu(v0, 8);
        lw(a0, v0, 8);
        if (a0 != 0) {
            // 0x00110f14
            charge(ctx, 3);
            jal(ctx, 0x110F14u, gen::fn_sub_4D0F00_004d0f00);
            sw(zero, s1, 0);
        }
        // 0x00110f20
        charge(ctx, 1);
        s2 = addiu(s2, 1);
    }
    // 0x00110f30
    charge(ctx, 17);
    a0 = 0x5D0000;
    a0 = addiu(a0, 22720);  // "*** CUTIN RELEASE %s\n"
    a1 = addiu(s0, 252);
    jal(ctx, 0x110F3Cu, gen::fn_printf_005225a8);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, rw::kFree);  // 0x96017C
    jalr(ctx, 0x110F50u, v0.u());
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00111150 sub_111150 -- 264 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_CutInPlayer_CreateFromFile] Creates "H_CutInPlayer" (RwCalloc 0x314, kwlnTaskCreateWithAutoPriority 4207): the
// four s16 ids of the 64-bit $a1 to +0xA8..+0xAE, the path "battle/cutin/c%02d_%d%x%02d.cpk" (+0xFC), the directory
// "battle/cutin/" (+0x1FC), load-from-file +0x310 = 1.
void sub_111150(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00111150
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    sd(a1, sp, 0x38);
    a0 = 1;
    a1 = 788;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, rw::kCalloc);  // 0x960184
    jalr(ctx, 0x11117Cu, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x0011119c
        charge(ctx, 14);
        a0 = s1;
        a1 = 4207;
        a2 = 0x5D0000;
        a2 = addiu(a2, 27240);  // "H_CutInPlayer"
        a3 = 0x110000;
        a3 = addiu(a3, 2000);  // &sub_1107D0
        t0 = 0x110000;
        t0 = addiu(t0, 3696);  // &sub_110E70
        t1 = s0;
        jal(ctx, 0x1111C0u, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
        s1 = v0;
        if (s1 != 0) {
            // 0x001111e0
            charge(ctx, 24);
            lh(a0, sp, 0x38);
            lh(v1, sp, 0x3A);
            lh(v0, sp, 0x3C);
            lh(t1, sp, 0x3E);
            sh(a0, s0, 168);
            sh(v1, s0, 170);
            sh(v0, s0, 172);
            sh(t1, s0, 174);
            lh(a2, s0, 168);
            lh(a3, s0, 170);
            lh(t0, s0, 172);
            a0 = addiu(s0, 252);
            a1 = 0x5D0000;
            a1 = addiu(a1, 27440);  // "battle/cutin/c%02d_%d%x%02d.cpk"
            jal(ctx, 0x111218u, gen::fn_sprintf_00523ac8);
            a0 = addiu(s0, 508);
            a1 = 0x5D0000;
            a1 = addiu(a1, 27472);  // "battle/cutin/"
            jal(ctx, 0x11122Cu, gen::fn_strcpy_00524270);
            v0 = 1;
            sw(v0, s0, 784);
            v0 = s1;
        } else {
            // 0x001111d4
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x00111190
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00111240 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00111260 sub_111260 -- 276 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_CutInPlayer_CreateFromArchive] As sub_111150 with the archive request $a2 (+0xC8) and +0x310 = 0 (the data is
// already loaded).
void sub_111260(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00111260
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    sd(a1, sp, 0x48);
    s0 = a2;
    a0 = 1;
    a1 = 788;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, rw::kCalloc);  // 0x960184
    jalr(ctx, 0x111294u, v0.u());
    s1 = v0;
    if (s1 != 0) {
        // 0x001112b4
        charge(ctx, 14);
        a0 = s2;
        a1 = 4207;
        a2 = 0x5D0000;
        a2 = addiu(a2, 27240);  // "H_CutInPlayer"
        a3 = 0x110000;
        a3 = addiu(a3, 2000);  // &sub_1107D0
        t0 = 0x110000;
        t0 = addiu(t0, 3696);  // &sub_110E70
        t1 = s1;
        jal(ctx, 0x1112D8u, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
        s2 = v0;
        if (s2 != 0) {
            // 0x001112f8
            charge(ctx, 24);
            lh(a0, sp, 0x48);
            lh(v1, sp, 0x4A);
            lh(v0, sp, 0x4C);
            lh(t1, sp, 0x4E);
            sh(a0, s1, 168);
            sh(v1, s1, 170);
            sh(v0, s1, 172);
            sh(t1, s1, 174);
            lh(a2, s1, 168);
            lh(a3, s1, 170);
            lh(t0, s1, 172);
            a0 = addiu(s1, 252);
            a1 = 0x5D0000;
            a1 = addiu(a1, 27440);  // "battle/cutin/c%02d_%d%x%02d.cpk"
            jal(ctx, 0x111330u, gen::fn_sprintf_00523ac8);
            a0 = addiu(s1, 508);
            a1 = 0x5D0000;
            a1 = addiu(a1, 27472);  // "battle/cutin/"
            jal(ctx, 0x111344u, gen::fn_strcpy_00524270);
            sw(s0, s1, 200);
            sw(zero, s1, 784);
            v0 = s2;
        } else {
            // 0x001112ec
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x001112a8
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00111358 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00111380 sub_111380 -- 304 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_CutInPlayer_CreateWithPriority] As sub_111260 under kwlnTaskCreate with priority $a1 (+0x30C, +0x308 = 1).
void sub_111380(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00111380
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s3 = a1;
    sd(a2, sp, 0x58);
    s2 = a3;
    a0 = 1;
    a1 = 788;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, rw::kCalloc);  // 0x960184
    jalr(ctx, 0x1113BCu, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x001113dc
        charge(ctx, 14);
        a0 = s1;
        a1 = 0x5D0000;
        a1 = addiu(a1, 27240);  // "H_CutInPlayer"
        a2 = s3;
        a3 = 0x110000;
        a3 = addiu(a3, 2000);  // &sub_1107D0
        t0 = 0x110000;
        t0 = addiu(t0, 3696);  // &sub_110E70
        t1 = s0;
        jal(ctx, 0x111400u, gen::fn_kwlnTaskCreate_00194b20);
        s1 = v0;
        if (s1 != 0) {
            // 0x00111420
            charge(ctx, 28);
            lh(a0, sp, 0x58);
            lh(v1, sp, 0x5A);
            lh(v0, sp, 0x5C);
            lh(t1, sp, 0x5E);
            sh(a0, s0, 168);
            sh(v1, s0, 170);
            sh(v0, s0, 172);
            sh(t1, s0, 174);
            lh(a2, s0, 168);
            lh(a3, s0, 170);
            lh(t0, s0, 172);
            a0 = addiu(s0, 252);
            a1 = 0x5D0000;
            a1 = addiu(a1, 27440);  // "battle/cutin/c%02d_%d%x%02d.cpk"
            jal(ctx, 0x111458u, gen::fn_sprintf_00523ac8);
            a0 = addiu(s0, 508);
            a1 = 0x5D0000;
            a1 = addiu(a1, 27472);  // "battle/cutin/"
            jal(ctx, 0x11146Cu, gen::fn_strcpy_00524270);
            v0 = 1;
            sw(v0, s0, 776);
            sw(s3, s0, 780);
            sw(zero, s0, 784);
            sw(s2, s0, 200);
            sw(zero, s0, 784);
            v0 = s1;
        } else {
            // 0x00111414
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x001113d0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00111490 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00111520 sub_111520 -- 16 bytes; leaf frame (no stack)
// [H_CutInPlayer_SetEndFrame] The player's end frame (s16 +0xD2) = $a1.
void sub_111520(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00111520
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, task::kWork);
    sh(a1, v1, 210);
}

// 0x00111570 sub_111570 -- 16 bytes; leaf frame (no stack)
// [H_CutInPlayer_SetBlend] The player's blend mode (+0x304) = $a1 (handed to the draw task's +0x4E4).
void sub_111570(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00111570
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, task::kWork);
    sw(a1, v1, 772);
}

// 0x001115B0 sub_1115B0 -- 36 bytes; leaf frame (no stack)
// [H_CutInPlayer_Pause] Pauses the player's draw task (+0x4E8 = 1) when it exists.
void sub_1115B0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x001115b0
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, task::kWork);
    lw(v1, v1, 176);
    if (v1 != 0) {
        // 0x001115c0
        charge(ctx, 3);
        a0 = 1;
        lw(v1, v1, 60);
        sw(a0, v1, 1256);
    }
    // 0x001115cc (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x001115E0 sub_1115E0 -- 48 bytes; frame 0x10: ra sp+0x0
// [H_CutInPlayer_DrawDirect] Draws the player's draw task immediately (sub_10EC50) when it exists.
void sub_1115E0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001115e0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, a0, task::kWork);
    lw(a0, v1, 176);
    if (a0 != 0) {
        // 0x001115f8
        charge(ctx, 2);
        jal(ctx, 0x1115F8u, gen::fn_sub_10EC50_0010ec50);
    }
    // 0x00111600 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00111D60 sub_111D60 -- 104 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [H_DrawMaestro_Destroy] Destroy callback of "H_DrawMaestro": drops the file request (+4) and the clump (+0xC,
// sub_4B4410), frees the work.
void sub_111D60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00111d60
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    lw(a0, s0, 4);
    if (a0 != 0) {
        // 0x00111d7c
        charge(ctx, 3);
        jal(ctx, 0x111D7Cu, gen::fn_H_Cdvd_Destroy_00100ec0);
        sw(zero, s0, 4);
    }
    // 0x00111d88
    charge(ctx, 3);
    lw(a0, s0, 12);
    if (a0 != 0) {
        // 0x00111d94
        charge(ctx, 3);
        jal(ctx, 0x111D94u, gen::fn_sub_4B4410_004b4410);
        sw(zero, s0, 12);
    }
    // 0x00111da0
    charge(ctx, 10);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, rw::kFree);  // 0x96017C
    jalr(ctx, 0x111DACu, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00111F50 sprFontInit -- 336 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Loads the three sprite fonts synchronously (kwlnInitMain): requests "camp/font/i_font01a.spr", "i_font02a.spr",
// "i_font02b.spr", waits for each (H_Cdvd_ReadSync), registers them (sprAddFile) into sSprFontFiles[3] 0x833A40, runs
// the file list (sub_1120C0) until all three reach state 5, then drops the requests.
void sprFontInit(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00111f50
    enter(ctx, 50);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0x5D0000;
    a0 = addiu(a0, 27600);  // "camp/font/i_font01a.spr"
    a1 = 0;
    jal(ctx, 0x111F70u, gen::fn_H_Cdvd_Request_00100d80);
    s2 = v0;
    a0 = 0x5D0000;
    a0 = addiu(a0, 27632);  // "camp/font/i_font02a.spr"
    a1 = 0;
    jal(ctx, 0x111F88u, gen::fn_H_Cdvd_Request_00100d80);
    s1 = v0;
    a0 = 0x5D0000;
    a0 = addiu(a0, 27664);  // "camp/font/i_font02b.spr"
    a1 = 0;
    jal(ctx, 0x111FA0u, gen::fn_H_Cdvd_Request_00100d80);
    s0 = v0;
    a0 = s2;
    jal(ctx, 0x111FB0u, gen::fn_H_Cdvd_ReadSync_001023a0);
    a0 = s1;
    jal(ctx, 0x111FBCu, gen::fn_H_Cdvd_ReadSync_001023a0);
    a0 = s0;
    jal(ctx, 0x111FC8u, gen::fn_H_Cdvd_ReadSync_001023a0);
    a0 = 0x5D0000;
    a0 = addiu(a0, 27600);  // "camp/font/i_font01a.spr"
    jal(ctx, 0x111FD8u, gen::fn_sprAddFile_00112370);
    v1 = 0x830000;
    sw(v0, v1, spr::kLoFontFiles);  // sSprFontFiles
    a0 = 0x5D0000;
    a0 = addiu(a0, 27632);  // "camp/font/i_font02a.spr"
    jal(ctx, 0x111FF0u, gen::fn_sprAddFile_00112370);
    v1 = 0x830000;
    sw(v0, v1, spr::kLoFontFile1);  // 0x833A44
    a0 = 0x5D0000;
    a0 = addiu(a0, 27664);  // "camp/font/i_font02b.spr"
    jal(ctx, 0x112008u, gen::fn_sprAddFile_00112370);
    v1 = 0x830000;
    sw(v0, v1, spr::kLoFontFile2);  // 0x833A48
    for (;;) {
        // 0x00112018
        charge(ctx, 8);
        jal(ctx, 0x112018u, gen::fn_sub_1120C0_001120c0);
        v0 = 0x830000;
        lw(v0, v0, spr::kLoFontFiles);  // sSprFontFiles
        lh(v0, v0, 0);
        v1 = 5;
        if (v0 != v1) {
            backedge(ctx);
            continue;
        }
        // 0x00112038
        charge(ctx, 5);
        v0 = 0x830000;
        lw(v0, v0, spr::kLoFontFile1);  // 0x833A44
        lh(v0, v0, 0);
        if (v0 != v1) {
            backedge(ctx);
            continue;
        }
        // 0x0011204c
        charge(ctx, 5);
        v0 = 0x830000;
        lw(v0, v0, spr::kLoFontFile2);  // 0x833A48
        lh(v0, v0, 0);
        if (v0 == v1) {
            break;
        }
        backedge(ctx);
    }
    // 0x00112060
    charge(ctx, 16);
    a0 = s2;
    jal(ctx, 0x112064u, gen::fn_H_Cdvd_Destroy_00100ec0);
    a0 = s1;
    jal(ctx, 0x112070u, gen::fn_H_Cdvd_Destroy_00100ec0);
    a0 = s0;
    jal(ctx, 0x11207Cu, gen::fn_H_Cdvd_Destroy_00100ec0);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00115CD0 sub_115CD0 -- 260 bytes; frame 0x70: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [sprDrawSpriteBasic4] One-shot sprite draw: sprCreateHandle(0, file, sprite), x / y / z from $f12 / $f13 / $f14,
// flags $a3, rgb $t0..$t2, sprDrawSprite(handle, 0) (sub_1127D0), unlink from the handle list (gp-0x4DB4) and RwFree.
void sub_115CD0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x00115cd0
    enter(ctx, 35);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    mov_s(f22, f12);
    mov_s(f21, f13);
    s4 = a3;
    s3 = t0;
    s2 = t1;
    s1 = t2;
    mov_s(f20, f14);
    a0 = 0;
    jal(ctx, 0x115D18u, gen::fn_sprCreateHandle_001158b0);
    s0 = v0;
    swc1(f20, v0, spr::kZ);
    swc1(f22, v0, spr::kX);
    swc1(f21, v0, spr::kY);
    sb(s4, v0, spr::kFlags);
    sb(s3, v0, spr::kR);
    sb(s2, v0, spr::kG);
    sb(s1, v0, spr::kB);
    a0 = s0;
    a1 = 0;
    jal(ctx, 0x115D48u, gen::fn_sub_1127D0_001127d0);
    lw(v1, s0, spr::kPrev);
    if (v1 != 0) {
        // 0x00115d78
        charge(ctx, 5);
        lw(v0, s0, spr::kNext);
        sw(v0, v1, spr::kNext);
        lw(v0, s0, spr::kNext);
        if (v0 != 0) {
            // 0x00115d8c
            charge(ctx, 1);
            sw(v1, v0, spr::kPrev);
        }
    } else {
        // 0x00115d5c
        charge(ctx, 4);
        lw(v0, s0, spr::kNext);
        sw(v0, gp, spr::kGpHandleList);  // 0x7CDF3C
        if (v0 != 0) {
            // 0x00115d6c
            charge(ctx, 3);
            sw(zero, v0, spr::kPrev);
        }
    }
    // 0x00115d90
    charge(ctx, 17);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, rw::kFree);  // 0x96017C
    jalr(ctx, 0x115D9Cu, v0.u());
    ld(ra, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x00115F00 sub_115F00 -- 1728 bytes; frame 0x160: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_PerEfect0_Update] Update of "H_PerEfect0Draw" (jump table 0x7B5360): 0 request
// "battle/cutin/per_efc0_%02X_00.bin" (AGS variants), 1 register its three archives (H_Cdvd_CacheAddArchive), start
// three cut-in players (sub_111260) with the persona's frame set and blend 1, load the two effect models
// (sub_34FCD0), 2 wait for the players, 4 start them, 5 run until the players end; returns -1 when finished.
void sub_115F00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00115f00
    enter(ctx, 51);  // entry check point + this block's cycles
    sp = addiu(sp, -0x160);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(s1, a0, task::kWork);
    jal(ctx, 0x115F20u, gen::fn_sub_198590_00198590);
    s0 = 0x960000;
    s0 = addiu(s0, rw::kRenderStateSet);  // &pfn_RwRenderStateSet
    a0 = 6;
    a1 = 1;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x115F3Cu, v0.u());
    a0 = 7;
    a1 = 2;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x115F50u, v0.u());
    a0 = 8;
    a1 = 1;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x115F64u, v0.u());
    a0 = 9;
    a1 = 1;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x115F78u, v0.u());
    a0 = 12;
    a1 = 1;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x115F8Cu, v0.u());
    a0 = 11;
    a1 = 6;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x115FA0u, v0.u());
    a0 = 10;
    a1 = 5;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x115FB4u, v0.u());
    lw(v0, s1, 0);
    at = sltiu(v0, 6);
    if (at != 0) {
        // 0x00115fcc
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, fx::kLoJptPerEfect0);  // &0x7B5360
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x115FE8u:  // table[0]
            // 0x00115fe8
            charge(ctx, 4);
            jal(ctx, 0x115FE8u, gen::fn_sub_17D800_0017d800);
            if (v0 != 0) {
                // 0x00115ff8
                charge(ctx, 4);
                lw(a2, s1, 4);
                v0 = 9;
                if (a2 != v0) {
                    goto L_00116024;
                }
                // 0x00116008
                charge(ctx, 7);
                a0 = addiu(sp, 0x50);
                a1 = 0x5D0000;
                a1 = addiu(a1, 27712);  // "battle/cutin/AGS_per_efc0_%02X_00.bin"
                jal(ctx, 0x116014u, gen::fn_sprintf_00523ac8);
                goto L_00116078;
            }
        L_00116024:
            charge(ctx, 4);
            jal(ctx, 0x116024u, gen::fn_sub_17D800_0017d800);
            if (v0 != 0) {
                // 0x00116034
                charge(ctx, 4);
                lw(v1, s1, 4);
                v0 = 1;
                if (v1 != v0) {
                    goto L_00116060;
                }
                // 0x00116044
                charge(ctx, 7);
                a0 = addiu(sp, 0x50);
                a1 = 0x5D0000;
                a1 = addiu(a1, 27760);  // "battle/cutin/per_efc0_03_00.bin"
                jal(ctx, 0x116050u, gen::fn_sprintf_00523ac8);
                goto L_00116078;
            }
        L_00116060:
            charge(ctx, 6);
            a0 = addiu(sp, 0x50);
            a1 = 0x5D0000;
            a1 = addiu(a1, 27792);  // "battle/cutin/per_efc0_%02X_00.bin"
            lw(a2, s1, 4);
            jal(ctx, 0x116070u, gen::fn_sprintf_00523ac8);
        L_00116078:
            charge(ctx, 9);
            a0 = addiu(sp, 0x50);
            a1 = 1;
            jal(ctx, 0x116080u, gen::fn_H_Cdvd_Request_00100d80);
            sw(v0, s1, 36);
            v0 = 1;
            sw(v0, s1, 0);
        L_0011659c:
            charge(ctx, 1);
            v0 = 0;
            break;
        case 0x11609Cu:  // table[1]
            // 0x0011609c
            charge(ctx, 5);
            lw(a0, s1, 36);
            jal(ctx, 0x1160A0u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
            if (v0 != 0) {
                // 0x001160b0
                charge(ctx, 3);
                s0 = 0;
                for (;;) {
                    // 0x00116108
                    charge(ctx, 3);
                    v0 = slti(s0, 3);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x001160bc
                    charge(ctx, 19);
                    v0 = sll(s0, 5);
                    v1 = subu(v0, s0);
                    v0 = sll(v1, 3);
                    v0 = subu(v0, v1);
                    v0 = sll(v0, 2);
                    v0 = addu(s1, v0);
                    s3 = addiu(v0, 400);
                    lw(a0, s1, 36);
                    a1 = s0;
                    a2 = addiu(v0, 408);
                    jal(ctx, 0x1160E4u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                    sw(v0, s3, 0);
                    a0 = 0x5D0000;
                    a0 = addiu(a0, 27832);  // "battle/cutin/"
                    a1 = v0;
                    jal(ctx, 0x1160FCu, gen::fn_H_Cdvd_CacheAddArchive_00102720);
                    s0 = addiu(s0, 1);
                }
                // 0x00116114
                charge(ctx, 8);
                v0 = 40;
                sh(v0, sp, 0x150);
                a2 = 3;
                sh(a2, sp, 0x152);
                lw(a1, s1, 4);
                v0 = 234;
                if (a1 == v0) {
                    // 0x00116370
                    charge(ctx, 4);
                    v0 = 11;
                    sh(v0, sp, 0x154);
                    v0 = 6;
                    sh(v0, sp, 0x156);
                } else {
                    // 0x00116134
                    charge(ctx, 3);
                    v0 = 233;
                    if (a1 == v0) {
                        // 0x00116358
                        charge(ctx, 6);
                        v0 = 11;
                        sh(v0, sp, 0x154);
                        v0 = 5;
                        sh(v0, sp, 0x156);
                    } else {
                        // 0x00116140
                        charge(ctx, 3);
                        v0 = 103;
                        if (a1 == v0) {
                            // 0x00116344
                            charge(ctx, 5);
                            v0 = 11;
                            sh(v0, sp, 0x154);
                            sh(a2, sp, 0x156);
                        } else {
                            // 0x0011614c
                            charge(ctx, 3);
                            v0 = 17;
                            if (a1 == v0) {
                                // 0x0011632c
                                charge(ctx, 6);
                                v0 = 11;
                                sh(v0, sp, 0x154);
                                v0 = 2;
                                sh(v0, sp, 0x156);
                            } else {
                                // 0x00116158
                                charge(ctx, 3);
                                v0 = 16;
                                if (a1 == v0) {
                                    // 0x00116314
                                    charge(ctx, 6);
                                    v0 = 11;
                                    sh(v0, sp, 0x154);
                                    v0 = 1;
                                    sh(v0, sp, 0x156);
                                } else {
                                    // 0x00116164
                                    charge(ctx, 3);
                                    v0 = 15;
                                    if (a1 == v0) {
                                        // 0x00116300
                                        charge(ctx, 5);
                                        v0 = 11;
                                        sh(v0, sp, 0x154);
                                        sh(zero, sp, 0x156);
                                    } else {
                                        // 0x00116170
                                        charge(ctx, 3);
                                        a0 = 10;
                                        if (a1 == a0) {
                                            // 0x001162ec
                                            charge(ctx, 5);
                                            sh(a0, sp, 0x154);
                                            v0 = 8;
                                            sh(v0, sp, 0x156);
                                        } else {
                                            // 0x0011617c
                                            charge(ctx, 3);
                                            v1 = 9;
                                            if (a1 == v1) {
                                                // 0x001162ac
                                                charge(ctx, 4);
                                                jal(ctx, 0x1162ACu, gen::fn_sub_17D800_0017d800);
                                                if (v0 == 0) {
                                                    // 0x001162d4
                                                    charge(ctx, 6);
                                                    v0 = 10;
                                                    sh(v0, sp, 0x154);
                                                    v0 = 7;
                                                    sh(v0, sp, 0x156);
                                                } else {
                                                    // 0x001162bc
                                                    charge(ctx, 6);
                                                    v0 = 11;
                                                    sh(v0, sp, 0x154);
                                                    v0 = 4;
                                                    sh(v0, sp, 0x156);
                                                }
                                            } else {
                                                // 0x00116188
                                                charge(ctx, 3);
                                                v0 = 8;
                                                if (a1 == v0) {
                                                    // 0x00116298
                                                    charge(ctx, 5);
                                                    sh(a0, sp, 0x154);
                                                    v0 = 6;
                                                    sh(v0, sp, 0x156);
                                                } else {
                                                    // 0x00116194
                                                    charge(ctx, 3);
                                                    v0 = 7;
                                                    if (a1 == v0) {
                                                        // 0x00116284
                                                        charge(ctx, 5);
                                                        sh(a0, sp, 0x154);
                                                        v0 = 5;
                                                        sh(v0, sp, 0x156);
                                                    } else {
                                                        // 0x001161a0
                                                        charge(ctx, 3);
                                                        v0 = 6;
                                                        if (a1 == v0) {
                                                            // 0x00116274
                                                            charge(ctx, 4);
                                                            sh(a0, sp, 0x154);
                                                            sh(v1, sp, 0x156);
                                                        } else {
                                                            // 0x001161ac
                                                            charge(ctx, 3);
                                                            v0 = 5;
                                                            if (a1 == v0) {
                                                                // 0x00116260
                                                                charge(ctx, 5);
                                                                sh(a0, sp, 0x154);
                                                                v0 = 4;
                                                                sh(v0, sp, 0x156);
                                                            } else {
                                                                // 0x001161b8
                                                                charge(ctx, 3);
                                                                v0 = 4;
                                                                if (a1 == v0) {
                                                                    // 0x00116250
                                                                    charge(ctx, 4);
                                                                    sh(a0, sp, 0x154);
                                                                    sh(a2, sp, 0x156);
                                                                } else {
                                                                    // 0x001161c4
                                                                    charge(ctx, 2);
                                                                    if (a1 == a2) {
                                                                        // 0x0011623c
                                                                        charge(ctx, 5);
                                                                        sh(a0, sp, 0x154);
                                                                        v0 = 2;
                                                                        sh(v0, sp, 0x156);
                                                                    } else {
                                                                        // 0x001161cc
                                                                        charge(ctx, 3);
                                                                        v0 = 2;
                                                                        if (a1 == v0) {
                                                                            // 0x00116228
                                                                            charge(ctx, 5);
                                                                            sh(a0, sp, 0x154);
                                                                            v0 = 1;
                                                                            sh(v0, sp, 0x156);
                                                                        } else {
                                                                            // 0x001161d8
                                                                            charge(ctx, 3);
                                                                            v0 = 1;
                                                                            if (a1 == v0) {
                                                                                // 0x001161ec
                                                                                charge(ctx, 4);
                                                                                jal(ctx, 0x1161ECu, gen::fn_sub_17D800_0017d800);
                                                                                if (v0 == 0) {
                                                                                    // 0x00116214
                                                                                    charge(ctx, 5);
                                                                                    v0 = 10;
                                                                                    sh(v0, sp, 0x154);
                                                                                    sh(zero, sp, 0x156);
                                                                                } else {
                                                                                    // 0x001161fc
                                                                                    charge(ctx, 6);
                                                                                    v0 = 10;
                                                                                    sh(v0, sp, 0x154);
                                                                                    v0 = 2;
                                                                                    sh(v0, sp, 0x156);
                                                                                }
                                                                            } else {
                                                                                // 0x001161e4
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
                }
                // 0x00116380
                charge(ctx, 64);
                a0 = s2;
                ld(a1, sp, 0x150);
                a2 = addiu(s1, 1864);
                jal(ctx, 0x11638Cu, gen::fn_sub_111260_00111260);
                sw(v0, s1, 20);
                v0 = 40;
                sh(v0, sp, 0x150);
                v0 = 3;
                sh(v0, sp, 0x152);
                v0 = 11;
                sh(v0, sp, 0x154);
                v0 = 9;
                sh(v0, sp, 0x156);
                a0 = s2;
                ld(a1, sp, 0x150);
                a2 = addiu(s1, 996);
                jal(ctx, 0x1163C4u, gen::fn_sub_111260_00111260);
                sw(v0, s1, 16);
                a0 = v0;
                a1 = 1;
                jal(ctx, 0x1163D8u, gen::fn_sub_111570_00111570);
                v0 = 40;
                sh(v0, sp, 0x150);
                v0 = 3;
                sh(v0, sp, 0x152);
                v0 = 11;
                sh(v0, sp, 0x154);
                v0 = 8;
                sh(v0, sp, 0x156);
                a0 = s2;
                ld(a1, sp, 0x150);
                a2 = addiu(s1, 128);
                jal(ctx, 0x11640Cu, gen::fn_sub_111260_00111260);
                sw(v0, s1, 12);
                a0 = v0;
                a1 = 1;
                jal(ctx, 0x116420u, gen::fn_sub_111570_00111570);
                lw(a0, s1, 36);
                a1 = 3;
                a2 = addiu(sp, 0x15C);
                jal(ctx, 0x116434u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                a0 = v0;
                jal(ctx, 0x116440u, gen::fn_sub_34FCD0_0034fcd0);
                sw(v0, s1, 2732);
                lw(a0, s1, 36);
                a1 = 4;
                a2 = addiu(sp, 0x15C);
                jal(ctx, 0x116458u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                a0 = v0;
                jal(ctx, 0x116464u, gen::fn_sub_34FCD0_0034fcd0);
                sw(v0, s1, 2736);
                v0 = 2;
                sw(v0, s1, 0);
            }
            goto L_0011659c;
        case 0x116480u:  // table[2]
            // 0x00116480
            charge(ctx, 5);
            lw(a0, s1, 12);
            jal(ctx, 0x116484u, gen::fn_sub_1114B0_001114b0);
            if (v0 != 0) {
                // 0x00116494
                charge(ctx, 5);
                lw(a0, s1, 16);
                jal(ctx, 0x116498u, gen::fn_sub_1114B0_001114b0);
                if (v0 != 0) {
                    // 0x001164a8
                    charge(ctx, 5);
                    lw(a0, s1, 20);
                    jal(ctx, 0x1164ACu, gen::fn_sub_1114B0_001114b0);
                    if (v0 != 0) {
                        // 0x001164bc
                        charge(ctx, 4);
                        v0 = 3;
                        sw(v0, s1, 0);
                    }
                }
            }
            goto L_0011659c;
        case 0x1164CCu:  // table[4]
            // 0x001164cc
            charge(ctx, 13);
            lw(a0, s1, 12);
            jal(ctx, 0x1164D0u, gen::fn_sub_111530_00111530);
            lw(a0, s1, 16);
            jal(ctx, 0x1164DCu, gen::fn_sub_111530_00111530);
            lw(a0, s1, 20);
            jal(ctx, 0x1164E8u, gen::fn_sub_111530_00111530);
            v0 = 5;
            sw(v0, s1, 0);
            goto L_0011659c;
        case 0x116500u:  // table[5]
            // 0x00116500
            charge(ctx, 3);
            lw(v0, s1, 20);
            if (v0 != 0) {
                // 0x0011650c
                charge(ctx, 9);
                lw(v0, s1, 112);
                v0 = addiu(v0, 1);
                sw(v0, s1, 112);
                lw(a0, s1, 20);
                jal(ctx, 0x11651Cu, gen::fn_kwlnTaskGetState_00195290);
                v1 = 3;
                if (v0 == v1) {
                    // 0x00116530
                    charge(ctx, 1);
                    sw(zero, s1, 20);
                }
            }
            // 0x00116534
            charge(ctx, 3);
            lw(v0, s1, 124);
            if (v0 != 0) {
                // 0x00116540
                charge(ctx, 6);
                lw(v0, s1, 116);
                v1 = addiu(v0, 1);
                sw(v1, s1, 116);
                v0 = 15;
                if (v1 == v0) {
                    goto L_00116584;
                }
                // 0x00116558
                charge(ctx, 3);
                at = slti(v1, 16);
                if (at != 0) {
                    goto L_00116584;
                }
                // 0x00116564
                charge(ctx, 5);
                lw(v0, s1, 108);
                v0 = addiu(v0, 15);
                v0 = slt(v1, v0);
                if (v0 != 0) {
                    goto L_00116584;
                }
                // 0x00116578
                charge(ctx, 3);
                v0 = si(-1);
                break;
            }
        L_00116584:
            charge(ctx, 3);
            lw(v0, s1, 120);
            if (v0 != 0) {
                // 0x00116590
                charge(ctx, 3);
                sw(zero, s1, 120);
                v0 = 1;
                sw(v0, s1, 124);
            }
            goto L_0011659c;
        case 0x11659Cu:  // table[3]
            goto L_0011659c;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x001165a0 (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(ra, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x160);
        return;
    }
    goto L_0011659c;
}

// 0x001165C0 sub_1165C0 -- 220 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_PerEfect0_Destroy] Destroy callback of "H_PerEfect0Draw": removes the three archives, drops the request, frees
// the two effect models (sub_34FCF0) and the work.
void sub_1165C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001165c0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s2, a0, task::kWork);
    lw(a0, s2, 400);
    if (a0 != 0) {
        // 0x001165e4
        charge(ctx, 2);
        jal(ctx, 0x1165E4u, gen::fn_H_Cdvd_CacheRemove_00102870);
    }
    // 0x001165ec
    charge(ctx, 3);
    lw(a0, s2, 1268);
    if (a0 != 0) {
        // 0x001165f8
        charge(ctx, 2);
        jal(ctx, 0x1165F8u, gen::fn_H_Cdvd_CacheRemove_00102870);
    }
    // 0x00116600
    charge(ctx, 3);
    lw(a0, s2, 2136);
    if (a0 != 0) {
        // 0x0011660c
        charge(ctx, 2);
        jal(ctx, 0x11660Cu, gen::fn_H_Cdvd_CacheRemove_00102870);
    }
    // 0x00116614
    charge(ctx, 3);
    lw(a0, s2, 36);
    if (a0 != 0) {
        // 0x00116620
        charge(ctx, 3);
        jal(ctx, 0x116620u, gen::fn_H_Cdvd_Destroy_00100ec0);
        sw(zero, s2, 36);
    }
    // 0x0011662c
    charge(ctx, 3);
    s1 = 0;
    for (;;) {
        // 0x00116660
        charge(ctx, 3);
        v0 = slti(s1, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00116638
        charge(ctx, 6);
        v0 = sll(s1, 2);
        v0 = addu(s2, v0);
        s0 = addiu(v0, 2732);
        lw(a0, v0, 2732);
        if (a0 != 0) {
            // 0x00116650
            charge(ctx, 3);
            jal(ctx, 0x116650u, gen::fn_sub_34FCF0_0034fcf0);
            sw(zero, s0, 0);
        }
        // 0x0011665c
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x0011666c
    charge(ctx, 12);
    a0 = s2;
    v0 = 0x960000;
    lw(v0, v0, rw::kFree);  // 0x96017C
    jalr(ctx, 0x116678u, v0.u());
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x001166A0 sub_1166A0 -- 192 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_PerEfect0_Create] Creates "H_PerEfect0Draw" (RwCalloc 0xAB4, auto priority 4207, sub_115F00 / sub_1165C0);
// persona +4 = $a1, +8 = $a2.
void sub_1166A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001166a0
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
    a1 = 2740;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, rw::kCalloc);  // 0x960184
    jalr(ctx, 0x1166D8u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x001166f8
        charge(ctx, 13);
        a0 = s3;
        a1 = 4207;
        a2 = 0x5D0000;
        a2 = addiu(a2, 27856);  // "H_PerEfect0Draw"
        a3 = 0x110000;
        a3 = addiu(a3, 24320);  // &sub_115F00
        t0 = 0x110000;
        t0 = addiu(t0, 26048);  // &sub_1165C0
        t1 = s0;
        jal(ctx, 0x11671Cu, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
        if (v0 != 0) {
            // 0x00116738
            charge(ctx, 2);
            sw(s2, s0, 4);
            sw(s1, s0, 8);
        } else {
            // 0x0011672c
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x001166ec
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00116740 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00116760 sub_116760 -- 24 bytes; leaf frame (no stack)
// [H_PerEfect0_IsReady] Effect 0 work state == 3.
void sub_116760(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00116760
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v0, a0, task::kWork);
    lw(v0, v0, 0);
    v0 = v0 ^ 0x3;
    v0 = sltiu(v0, 1);
}

// 0x00116780 sub_116780 -- 20 bytes; leaf frame (no stack)
// [H_PerEfect0_Start] Effect 0 work state = 4.
void sub_116780(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00116780
    enter(ctx, 5);  // entry check point + this block's cycles
    a1 = 4;
    lw(v1, a0, task::kWork);
    sw(a1, v1, 0);
}

// 0x001167A0 sub_1167A0 -- 20 bytes; leaf frame (no stack)
// [H_PerEfect0_End] Effect 0 work +0x78 = 1 (end requested).
void sub_1167A0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x001167a0
    enter(ctx, 5);  // entry check point + this block's cycles
    a1 = 1;
    lw(v1, a0, task::kWork);
    sw(a1, v1, 120);
}

// 0x001167C0 sub_1167C0 -- 44 bytes; leaf frame (no stack)
// [H_PerEfect0_GetFrame] Frame value i of effect 0 (+0x68 + 4 * i); 51 for i == 0.
void sub_1167C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x001167c0
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v1, a0, task::kWork);
    if (a1 != 0) {
        // 0x001167d8
        charge(ctx, 3);
        v0 = sll(a1, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 104);
    } else {
        // 0x001167cc
        charge(ctx, 3);
        v0 = 51;
    }
    // 0x001167e4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x001167F0 sub_1167F0 -- 1276 bytes; frame 0x160: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_PerEfect1_Update] Update of "H_PerEfect1Draw" (jump tables 0x7B53E0 / 0x7B53B0 / 0x7B5380): 0 request
// "battle/cutin/per_efc1_%02d.bin" by persona, 1 register two archives, start a cut-in player and build the mark
// sprite file (sprCreateHandleFromData), 2 wait, end frame 50, 4 start and create the "H_sMarkSprDraw" task, 5 count
// to 50 and stop the player; returns -1 when the player is gone.
void sub_1167F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001167f0
    enter(ctx, 51);  // entry check point + this block's cycles
    sp = addiu(sp, -0x160);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(s1, a0, task::kWork);
    jal(ctx, 0x116810u, gen::fn_sub_198590_00198590);
    s0 = 0x960000;
    s0 = addiu(s0, rw::kRenderStateSet);  // &pfn_RwRenderStateSet
    a0 = 6;
    a1 = 1;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x11682Cu, v0.u());
    a0 = 7;
    a1 = 2;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x116840u, v0.u());
    a0 = 8;
    a1 = 1;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x116854u, v0.u());
    a0 = 9;
    a1 = 1;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x116868u, v0.u());
    a0 = 12;
    a1 = 1;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x11687Cu, v0.u());
    a0 = 11;
    a1 = 6;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x116890u, v0.u());
    a0 = 10;
    a1 = 5;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x1168A4u, v0.u());
    lw(v0, s1, 0);
    at = sltiu(v0, 6);
    if (at != 0) {
        // 0x001168bc
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, fx::kLoJptPerEfect1a);  // &0x7B53E0
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x1168D8u:  // table[0]
            // 0x001168d8
            charge(ctx, 4);
            lw(v0, s1, 4);
            at = sltiu(v0, 11);
            if (at != 0) {
                // 0x001168e8
                charge(ctx, 7);
                v1 = 0x7B0000;
                v1 = addiu(v1, fx::kLoJptPerEfect1b);  // &0x7B53B0
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                lw(v0, v0, 0);
                switch (v0.u()) {
                case 0x116904u:  // table[2]
                    // 0x00116904
                    charge(ctx, 7);
                    a0 = addiu(sp, 0x50);
                    a1 = 0x5D0000;
                    a1 = addiu(a1, 27872);  // "battle/cutin/per_efc1_00.bin"
                    jal(ctx, 0x116910u, gen::fn_sprintf_00523ac8);
                    break;
                case 0x116920u:  // table[3]
                    // 0x00116920
                    charge(ctx, 7);
                    a0 = addiu(sp, 0x50);
                    a1 = 0x5D0000;
                    a1 = addiu(a1, 27904);  // "battle/cutin/per_efc1_01.bin"
                    jal(ctx, 0x11692Cu, gen::fn_sprintf_00523ac8);
                    break;
                case 0x11693Cu:  // table[4]
                    // 0x0011693c
                    charge(ctx, 7);
                    a0 = addiu(sp, 0x50);
                    a1 = 0x5D0000;
                    a1 = addiu(a1, 27936);  // "battle/cutin/per_efc1_02.bin"
                    jal(ctx, 0x116948u, gen::fn_sprintf_00523ac8);
                    break;
                case 0x116958u:  // table[5]
                    // 0x00116958
                    charge(ctx, 7);
                    a0 = addiu(sp, 0x50);
                    a1 = 0x5D0000;
                    a1 = addiu(a1, 27968);  // "battle/cutin/per_efc1_03.bin"
                    jal(ctx, 0x116964u, gen::fn_sprintf_00523ac8);
                    break;
                case 0x116974u:  // table[7]
                    // 0x00116974
                    charge(ctx, 7);
                    a0 = addiu(sp, 0x50);
                    a1 = 0x5D0000;
                    a1 = addiu(a1, 28000);  // "battle/cutin/per_efc1_04.bin"
                    jal(ctx, 0x116980u, gen::fn_sprintf_00523ac8);
                    break;
                case 0x116990u:  // table[8]
                    // 0x00116990
                    charge(ctx, 7);
                    a0 = addiu(sp, 0x50);
                    a1 = 0x5D0000;
                    a1 = addiu(a1, 28032);  // "battle/cutin/per_efc1_05.bin"
                    jal(ctx, 0x11699Cu, gen::fn_sprintf_00523ac8);
                    break;
                case 0x1169ACu:  // table[9]
                    // 0x001169ac
                    charge(ctx, 4);
                    jal(ctx, 0x1169ACu, gen::fn_sub_17D800_0017d800);
                    if (v0 == 0) {
                        // 0x001169d8
                        charge(ctx, 7);
                        a0 = addiu(sp, 0x50);
                        a1 = 0x5D0000;
                        a1 = addiu(a1, 28096);  // "battle/cutin/per_efc1_06.bin"
                        jal(ctx, 0x1169E4u, gen::fn_sprintf_00523ac8);
                    } else {
                        // 0x001169bc
                        charge(ctx, 7);
                        a0 = addiu(sp, 0x50);
                        a1 = 0x5D0000;
                        a1 = addiu(a1, 28064);  // "battle/cutin/per_efc1_08.bin"
                        jal(ctx, 0x1169C8u, gen::fn_sprintf_00523ac8);
                    }
                    break;
                case 0x1169F4u:  // table[10]
                    // 0x001169f4
                    charge(ctx, 7);
                    a0 = addiu(sp, 0x50);
                    a1 = 0x5D0000;
                    a1 = addiu(a1, 28128);  // "battle/cutin/per_efc1_07.bin"
                    jal(ctx, 0x116A00u, gen::fn_sprintf_00523ac8);
                    break;
                case 0x116A10u:  // table[0, 1, 6]
                L_00116a10:
                    charge(ctx, 5);
                    a0 = addiu(sp, 0x50);
                    a1 = 0x5D0000;
                    a1 = addiu(a1, 27872);  // "battle/cutin/per_efc1_00.bin"
                    jal(ctx, 0x116A1Cu, gen::fn_sprintf_00523ac8);
                    break;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, v0.u());
                    return;
                }
                goto L_00116a24;
            }
            goto L_00116a10;
        case 0x116A48u:  // table[1]
            // 0x00116a48
            charge(ctx, 5);
            lw(a0, s1, 36);
            jal(ctx, 0x116A4Cu, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
            if (v0 != 0) {
                // 0x00116a5c
                charge(ctx, 3);
                s0 = 0;
                for (;;) {
                    // 0x00116ab4
                    charge(ctx, 3);
                    v0 = slti(s0, 2);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00116a68
                    charge(ctx, 19);
                    v0 = sll(s0, 5);
                    v1 = subu(v0, s0);
                    v0 = sll(v1, 3);
                    v0 = subu(v0, v1);
                    v0 = sll(v0, 2);
                    v0 = addu(s1, v0);
                    s3 = addiu(v0, 384);
                    lw(a0, s1, 36);
                    a1 = s0;
                    a2 = addiu(v0, 392);
                    jal(ctx, 0x116A90u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                    sw(v0, s3, 0);
                    a0 = 0x5D0000;
                    a0 = addiu(a0, 28160);  // "battle/cutin/"
                    a1 = v0;
                    jal(ctx, 0x116AA8u, gen::fn_H_Cdvd_CacheAddArchive_00102720);
                    s0 = addiu(s0, 1);
                }
                // 0x00116ac0
                charge(ctx, 10);
                v0 = 41;
                sh(v0, sp, 0x150);
                a0 = 4;
                sh(a0, sp, 0x152);
                v0 = 10;
                sh(v0, sp, 0x154);
                lw(v0, s1, 4);
                at = sltiu(v0, 11);
                if (at != 0) {
                    // 0x00116ae8
                    charge(ctx, 7);
                    v1 = 0x7B0000;
                    v1 = addiu(v1, fx::kLoJptPerEfect1c);  // &0x7B5380
                    v0 = sll(v0, 2);
                    v0 = addu(v0, v1);
                    lw(v0, v0, 0);
                    switch (v0.u()) {
                    case 0x116B04u:  // table[2]
                        // 0x00116b04
                        charge(ctx, 3);
                        sh(zero, sp, 0x156);
                        break;
                    case 0x116B10u:  // table[3]
                        // 0x00116b10
                        charge(ctx, 4);
                        v0 = 1;
                        sh(v0, sp, 0x156);
                        break;
                    case 0x116B20u:  // table[4]
                        // 0x00116b20
                        charge(ctx, 4);
                        v0 = 2;
                        sh(v0, sp, 0x156);
                        break;
                    case 0x116B30u:  // table[5]
                        // 0x00116b30
                        charge(ctx, 4);
                        v0 = 3;
                        sh(v0, sp, 0x156);
                        break;
                    case 0x116B40u:  // table[7]
                        // 0x00116b40
                        charge(ctx, 3);
                        sh(a0, sp, 0x156);
                        break;
                    case 0x116B4Cu:  // table[8]
                        // 0x00116b4c
                        charge(ctx, 4);
                        v0 = 5;
                        sh(v0, sp, 0x156);
                        break;
                    case 0x116B5Cu:  // table[9]
                        // 0x00116b5c
                        charge(ctx, 4);
                        jal(ctx, 0x116B5Cu, gen::fn_sub_17D800_0017d800);
                        if (v0 == 0) {
                            // 0x00116b7c
                            charge(ctx, 4);
                            v0 = 6;
                            sh(v0, sp, 0x156);
                        } else {
                            // 0x00116b6c
                            charge(ctx, 4);
                            v0 = 8;
                            sh(v0, sp, 0x156);
                        }
                        break;
                    case 0x116B8Cu:  // table[10]
                        // 0x00116b8c
                        charge(ctx, 4);
                        v0 = 7;
                        sh(v0, sp, 0x156);
                        break;
                    case 0x116B9Cu:  // table[0, 1, 6]
                    L_00116b9c:
                        charge(ctx, 1);
                        sh(zero, sp, 0x156);
                        break;
                    default:  // not one of the table's targets: the dispatch table, as the recompiled body
                        tail(ctx, v0.u());
                        return;
                    }
                    goto L_00116ba0;
                }
                goto L_00116b9c;
            }
        L_00116cc8:
            charge(ctx, 1);
            v0 = 0;
            break;
        case 0x116BECu:  // table[2]
            // 0x00116bec
            charge(ctx, 5);
            lw(a0, s1, 8);
            jal(ctx, 0x116BF0u, gen::fn_sub_1114B0_001114b0);
            if (v0 != 0) {
                // 0x00116c00
                charge(ctx, 5);
                lw(a0, s1, 1848);
                jal(ctx, 0x116C04u, gen::fn_sprFileIsReady_00111f30);
                if (v0 != 0) {
                    // 0x00116c14
                    charge(ctx, 8);
                    lw(a0, s1, 8);
                    a1 = 50;
                    jal(ctx, 0x116C1Cu, gen::fn_sub_111520_00111520);
                    v0 = 3;
                    sw(v0, s1, 0);
                }
            }
            goto L_00116cc8;
        case 0x116C34u:  // table[4]
            // 0x00116c34
            charge(ctx, 12);
            lw(a0, s1, 8);
            jal(ctx, 0x116C38u, gen::fn_sub_111530_00111530);
            a0 = s2;
            lw(a1, s1, 1848);
            jal(ctx, 0x116C48u, gen::fn_sub_117490_00117490);
            sw(v0, s1, 16);
            v0 = 5;
            sw(v0, s1, 0);
            goto L_00116cc8;
        case 0x116C64u:  // table[5]
            // 0x00116c64
            charge(ctx, 4);
            lw(v1, s1, 100);
            v0 = slti(v1, 50);
            if (v0 != 0) {
                // 0x00116c9c
                charge(ctx, 2);
                v0 = addiu(v1, 1);
                sw(v0, s1, 100);
            } else {
                // 0x00116c74
                charge(ctx, 3);
                lw(v0, s1, 108);
                if (v0 != 0) {
                    // 0x00116c80
                    charge(ctx, 7);
                    v0 = addiu(v1, 1);
                    sw(v0, s1, 100);
                    lw(a0, s1, 8);
                    jal(ctx, 0x116C8Cu, gen::fn_sub_111500_00111500);
                }
            }
            // 0x00116ca4
            charge(ctx, 6);
            lw(a0, s1, 8);
            jal(ctx, 0x116CA8u, gen::fn_kwlnTaskGetState_00195290);
            v1 = 3;
            if (v0 != v1) {
                goto L_00116cc8;
            }
            // 0x00116cbc
            charge(ctx, 3);
            v0 = si(-1);
            break;
        case 0x116CC8u:  // table[3]
            goto L_00116cc8;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x00116ccc (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(ra, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x160);
        return;
    }
    goto L_00116cc8;
L_00116a24:
    charge(ctx, 9);
    a0 = addiu(sp, 0x50);
    a1 = 1;
    jal(ctx, 0x116A2Cu, gen::fn_H_Cdvd_Request_00100d80);
    sw(v0, s1, 36);
    v0 = 1;
    sw(v0, s1, 0);
    goto L_00116cc8;
L_00116ba0:
    charge(ctx, 19);
    a0 = s2;
    ld(a1, sp, 0x150);
    a2 = addiu(s1, 112);
    jal(ctx, 0x116BACu, gen::fn_sub_111260_00111260);
    sw(v0, s1, 8);
    lw(a0, s1, 36);
    a1 = 1;
    a2 = addiu(sp, 0x15C);
    jal(ctx, 0x116BC4u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
    a0 = v0;
    jal(ctx, 0x116BD0u, gen::fn_sprCreateHandleFromData_00112420);
    sw(v0, s1, 1848);
    v0 = 2;
    sw(v0, s1, 0);
    goto L_00116cc8;
}

// 0x00116CF0 sub_116CF0 -- 292 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_PerEfect1_Destroy] Destroy callback of "H_PerEfect1Draw": frees the sprite file (sub_1124B0), removes the
// archives, drops the requests, destroys the two rasters and frees the work.
void sub_116CF0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00116cf0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s1, a0, task::kWork);
    lw(a0, s1, 1848);
    jal(ctx, 0x116D0Cu, gen::fn_sub_1124B0_001124b0);
    s0 = 0;
    for (;;) {
        // 0x00116d58
        charge(ctx, 3);
        v0 = slti(s0, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00116d20
        charge(ctx, 10);
        v0 = sll(s0, 5);
        v1 = subu(v0, s0);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v0 = sll(v0, 2);
        v0 = addu(s1, v0);
        s2 = addiu(v0, 384);
        lw(a0, v0, 384);
        if (a0 != 0) {
            // 0x00116d48
            charge(ctx, 3);
            jal(ctx, 0x116D48u, gen::fn_H_Cdvd_CacheRemove_00102870);
            sw(zero, s2, 0);
        }
        // 0x00116d54
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x00116d64
    charge(ctx, 3);
    s2 = 0;
    for (;;) {
        // 0x00116d98
        charge(ctx, 3);
        v0 = slti(s2, 3);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00116d70
        charge(ctx, 6);
        v0 = sll(s2, 2);
        v0 = addu(s1, v0);
        s0 = addiu(v0, 36);
        lw(a0, v0, 36);
        if (a0 != 0) {
            // 0x00116d88
            charge(ctx, 3);
            jal(ctx, 0x116D88u, gen::fn_H_Cdvd_Destroy_00100ec0);
            sw(zero, s0, 0);
        }
        // 0x00116d94
        charge(ctx, 1);
        s2 = addiu(s2, 1);
    }
    // 0x00116da4
    charge(ctx, 3);
    s2 = 0;
    for (;;) {
        // 0x00116dd8
        charge(ctx, 3);
        v0 = slti(s2, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00116db0
        charge(ctx, 6);
        v0 = sll(s2, 2);
        v0 = addu(s1, v0);
        s0 = addiu(v0, 28);
        lw(a0, v0, 28);
        if (a0 != 0) {
            // 0x00116dc8
            charge(ctx, 3);
            jal(ctx, 0x116DC8u, gen::fn_sub_4D0F00_004d0f00);
            sw(zero, s0, 0);
        }
        // 0x00116dd4
        charge(ctx, 1);
        s2 = addiu(s2, 1);
    }
    // 0x00116de4
    charge(ctx, 12);
    a0 = s1;
    v0 = 0x960000;
    lw(v0, v0, rw::kFree);  // 0x96017C
    jalr(ctx, 0x116DF0u, v0.u());
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00116E20 sub_116E20 -- 176 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_PerEfect1_Create] Creates "H_PerEfect1Draw" (RwCalloc 0x73C, auto priority 4207); persona +4 = $a1.
void sub_116E20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00116e20
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    a0 = 1;
    a1 = 1852;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, rw::kCalloc);  // 0x960184
    jalr(ctx, 0x116E50u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x00116e70
        charge(ctx, 13);
        a0 = s2;
        a1 = 4207;
        a2 = 0x5D0000;
        a2 = addiu(a2, 28176);  // "H_PerEfect1Draw"
        a3 = 0x110000;
        a3 = addiu(a3, 26608);  // &sub_1167F0
        t0 = 0x110000;
        t0 = addiu(t0, 27888);  // &sub_116CF0
        t1 = s0;
        jal(ctx, 0x116E94u, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
        if (v0 != 0) {
            // 0x00116eb0
            charge(ctx, 1);
            sw(s1, s0, 4);
        } else {
            // 0x00116ea4
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x00116e64
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00116eb4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00116ED0 sub_116ED0 -- 24 bytes; leaf frame (no stack)
// [H_PerEfect1_IsReady] Effect 1 work state == 3.
void sub_116ED0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00116ed0
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v0, a0, task::kWork);
    lw(v0, v0, 0);
    v0 = v0 ^ 0x3;
    v0 = sltiu(v0, 1);
}

// 0x00116EF0 sub_116EF0 -- 20 bytes; leaf frame (no stack)
// [H_PerEfect1_Start] Effect 1 work state = 4.
void sub_116EF0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00116ef0
    enter(ctx, 5);  // entry check point + this block's cycles
    a1 = 4;
    lw(v1, a0, task::kWork);
    sw(a1, v1, 0);
}

// 0x00116F10 sub_116F10 -- 12 bytes; leaf frame (no stack)
// [H_PerEfect1_GetLength] Returns 63 (effect 1's length in frames).
void sub_116F10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00116f10
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 63;
}

// 0x00116F20 sub_116F20 -- 16 bytes; leaf frame (no stack)
// [H_PerEfect1_GetFrame] Effect 1 frame counter (+0x64).
void sub_116F20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00116f20
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, a0, task::kWork);
    lw(v0, v0, 100);
}

// 0x00116F30 sub_116F30 -- 24 bytes; leaf frame (no stack)
// [H_PerEfect1_IsPastHit] Effect 1 frame counter >= 50.
void sub_116F30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00116f30
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v0, a0, task::kWork);
    lw(v0, v0, 100);
    v0 = slti(v0, 50);
    v0 = v0 ^ 0x1;
}

// 0x00116F50 sub_116F50 -- 48 bytes; frame 0x10: ra sp+0x0
// [H_PerEfect1_End] Effect 1: +0x6C = 1 and ends its mark sprite (sub_117470).
void sub_116F50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00116f50
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, a0, task::kWork);
    v0 = 1;
    sw(v0, v1, 108);
    lw(a0, v1, 16);
    jal(ctx, 0x116F68u, gen::fn_sub_117470_00117470);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00116F80 sub_116F80 -- 1204 bytes; frame 0x70: ra sp+0x40, s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq)
// [H_sMarkSpr_Update] Update of "H_sMarkSprDraw": a four-phase slide of the mark sprite on the eased path sub_18BC10
// / sub_18B700 (phase 0 start from x 666, 1 slide in with a shrinking x offset and a debug printf of the end /
// current x, 2 a 6-frame bounce, 3 wait for the end request, 4 slide out); each frame one sprite handle drawn and
// freed. Returns -1 at the end.
void sub_116F80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x00116f80
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    lw(s1, a0, task::kWork);
    lw(v1, s1, 0);
    a0 = 4;
    if (v1 != a0) {
        // 0x00116fa8
        charge(ctx, 3);
        v0 = 3;
        if (v1 == v0) {
            // 0x00117298
            charge(ctx, 5);
            a0 = addiu(s1, 20);
            jal(ctx, 0x11729Cu, gen::fn_sub_18B700_0018b700);
            if (v0 != 0) {
                // 0x001172ac
                charge(ctx, 25);
                s0 = addiu(s1, 20);
                a0 = 0;
                lw(a1, s1, 16);
                a2 = 0;
                jal(ctx, 0x1172BCu, gen::fn_sprCreateHandle_001158b0);
                s2 = v0;
                v1 = 0x42C80000;
                sw(v1, v0, 44);
                lwc1(f0, s0, 56);
                swc1(f0, v0, 16);
                lwc1(f0, s0, 60);
                swc1(f0, v0, 20);
                v1 = 16;
                sh(v1, v0, 36);
                v1 = 96;
                sh(v1, v0, 38);
                sb(zero, v0, 24);
                a0 = s2;
                a1 = 1;
                jal(ctx, 0x1172FCu, gen::fn_sub_1127D0_001127d0);
                a0 = s2;
                jal(ctx, 0x117308u, gen::fn_sub_115980_00115980);
            }
            // 0x00117310
            charge(ctx, 3);
            lw(v0, s1, 12);
            if (v0 != 0) {
                // 0x0011731c
                charge(ctx, 23);
                v0 = 0x433B0000;
                sw(v0, sp, 0x58);
                v0 = 0x42F00000;
                sw(v0, sp, 0x5C);
                sd(zero, sp, 0x0);
                v0 = 10;
                sd(v0, sp, 0x8);
                v0 = 0x42C80000;
                mtc1(v0, f12);
                a0 = addiu(s1, 20);
                a1 = 0;
                a2 = 2;
                a3 = a2;
                ld(t0, sp, 0x58);
                t1 = t0;
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x117360u, gen::fn_sub_18BC10_0018bc10);
                v0 = 4;
                sw(v0, s1, 0);
            }
        } else {
            // 0x00116fb4
            charge(ctx, 3);
            a2 = 2;
            if (v1 == a2) {
                // 0x00117168
                charge(ctx, 5);
                a0 = addiu(s1, 20);
                jal(ctx, 0x11716Cu, gen::fn_sub_18B700_0018b700);
                if (v0 != 0) {
                    // 0x0011717c
                    charge(ctx, 13);
                    s0 = addiu(s1, 20);
                    a0 = 0;
                    lw(a1, s1, 16);
                    a2 = 0;
                    jal(ctx, 0x11718Cu, gen::fn_sprCreateHandle_001158b0);
                    s2 = v0;
                    lw(v0, s1, 4);
                    v1 = addiu(v0, 1);
                    sw(v1, s1, 4);
                    at = slti(v1, 3);
                    if (at == 0) {
                        // 0x001171e8
                        charge(ctx, 3);
                        at = slti(v1, 6);
                        if (at == 0) {
                            // 0x00117228
                            charge(ctx, 4);
                            v1 = 0;
                            v0 = 3;
                            sw(v0, s1, 0);
                            sw(zero, s1, 4);
                        } else {
                            // 0x001171f4
                            charge(ctx, 8);
                            v1 = addiu(v1, -3);
                            v0 = sll(v1, 2);
                            v0 = addu(v0, v1);
                            v1 = sll(v0, 1);
                            v0 = dsll32(v0, 1);
                            v0 = dsra32(v0, 1);
                            if (i64(v1) < 0) {
                                // 0x00117214
                                charge(ctx, 2);
                                v0 = addiu(v1, 1);
                                v0 = sra(v0, 1);
                            }
                            // 0x0011721c
                            charge(ctx, 3);
                            v1 = addiu(v0, -10);
                        }
                    } else {
                        // 0x001171b0
                        charge(ctx, 7);
                        v0 = sll(v1, 4);
                        v1 = subu(v0, v1);
                        v0 = sll(v1, 1);
                        v1 = dsll32(v1, 1);
                        v1 = dsra32(v1, 1);
                        if (i64(v0) < 0) {
                            // 0x001171cc
                            charge(ctx, 2);
                            v0 = addiu(v0, 1);
                            v1 = sra(v0, 1);
                        }
                        // 0x001171d4
                        charge(ctx, 5);
                        v0 = 30;
                        v0 = subu(v0, v1);
                        v1 = addiu(v0, -10);
                    }
                    // 0x00117238
                    charge(ctx, 24);
                    mtc1(v1, f0);
                    cvt_s_w(f0, f0);
                    swc1(f0, s2, 32);
                    v0 = 0x42C80000;
                    sw(v0, s2, 44);
                    lwc1(f0, s0, 56);
                    swc1(f0, s2, 16);
                    lwc1(f0, s0, 60);
                    swc1(f0, s2, 20);
                    v0 = 16;
                    sh(v0, s2, 36);
                    v0 = 96;
                    sh(v0, s2, 38);
                    sb(zero, s2, 24);
                    a0 = s2;
                    a1 = 1;
                    jal(ctx, 0x11727Cu, gen::fn_sub_1127D0_001127d0);
                    a0 = s2;
                    jal(ctx, 0x117288u, gen::fn_sub_115980_00115980);
                }
            } else {
                // 0x00116fc0
                charge(ctx, 3);
                v0 = 1;
                if (v1 == v0) {
                    // 0x0011704c
                    charge(ctx, 5);
                    a0 = addiu(s1, 20);
                    jal(ctx, 0x117050u, gen::fn_sub_18B700_0018b700);
                    if (v0 != 0) {
                        // 0x00117060
                        charge(ctx, 18);
                        s0 = addiu(s1, 20);
                        lwc1(f12, s1, 68);
                        jal(ctx, 0x117068u, gen::fn_fptodp_00530da0);
                        s2 = v0;
                        lwc1(f12, s0, 56);
                        jal(ctx, 0x117078u, gen::fn_fptodp_00530da0);
                        a0 = 0x5D0000;
                        a0 = addiu(a0, 28192);  // " endPos.x = %f : nowPos.x = %f \n"
                        a1 = s2;
                        a2 = v0;
                        jal(ctx, 0x117090u, gen::fn_printf_005225a8);
                        lw(v1, s0, 32);
                        lw(v0, s0, 24);
                        if (v1 == v0) {
                            // 0x001170a8
                            charge(ctx, 3);
                            sw(zero, s1, 4);
                            v0 = 2;
                            sw(v0, s1, 0);
                        }
                        // 0x001170b4
                        charge(ctx, 28);
                        a0 = 0;
                        lw(a1, s1, 16);
                        a2 = 0;
                        jal(ctx, 0x1170C0u, gen::fn_sprCreateHandle_001158b0);
                        s1 = v0;
                        v1 = 0x42C80000;
                        sw(v1, v0, 44);
                        lwc1(f0, s0, 56);
                        swc1(f0, v0, 16);
                        lwc1(f0, s0, 60);
                        swc1(f0, v0, 20);
                        v1 = 16;
                        sh(v1, v0, 36);
                        v1 = 96;
                        sh(v1, v0, 38);
                        lw(v1, s0, 32);
                        lw(v0, s0, 24);
                        v1 = subu(v1, v0);
                        v0 = 4;
                        v1 = subu(v0, v1);
                        v0 = sll(v1, 2);
                        v1 = addu(v0, v1);
                        v0 = sll(v1, 2);
                        v1 = addu(v1, v0);
                        v0 = sra(v1, 2);
                        if (i64(v1) < 0) {
                            // 0x00117124
                            charge(ctx, 2);
                            v0 = addiu(v1, 3);
                            v0 = sra(v0, 2);
                        }
                        // 0x0011712c
                        charge(ctx, 15);
                        v0 = addiu(v0, -5);
                        mtc1(v0, f0);
                        cvt_s_w(f0, f0);
                        swc1(f0, s1, 32);
                        sb(zero, s1, 24);
                        a0 = s1;
                        a1 = 1;
                        jal(ctx, 0x11714Cu, gen::fn_sub_1127D0_001127d0);
                        a0 = s1;
                        jal(ctx, 0x117158u, gen::fn_sub_115980_00115980);
                    }
                } else {
                    // 0x00116fcc
                    charge(ctx, 2);
                    if (v1 == 0) {
                        // 0x00116fdc
                        charge(ctx, 28);
                        v0 = 666;
                        mtc1(v0, f0);
                        cvt_s_w(f0, f0);
                        swc1(f0, sp, 0x68);
                        v1 = 0x42F00000;
                        sw(v1, sp, 0x6C);
                        v0 = 0x433B0000;
                        sw(v0, sp, 0x60);
                        sw(v1, sp, 0x64);
                        sd(a0, sp, 0x0);
                        v0 = 8;
                        sd(v0, sp, 0x8);
                        v0 = 0x42C80000;
                        mtc1(v0, f12);
                        a0 = addiu(s1, 20);
                        a1 = 0;
                        a3 = 0;
                        ld(t0, sp, 0x68);
                        ld(t1, sp, 0x60);
                        t2 = 0;
                        t3 = 0;
                        jal(ctx, 0x117034u, gen::fn_sub_18BC10_0018bc10);
                        v0 = 1;
                        sw(v0, s1, 0);
                    } else {
                        // 0x00116fd4
                        charge(ctx, 2);
                    }
                }
            }
        }
        goto L_00117414;
    }
    // 0x00117378
    charge(ctx, 5);
    a0 = addiu(s1, 20);
    jal(ctx, 0x11737Cu, gen::fn_sub_18B700_0018b700);
    if (v0 == 0) {
    L_00117414:
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x0011738c
        charge(ctx, 5);
        s0 = addiu(s1, 20);
        lw(v1, s1, 52);
        lw(v0, s1, 44);
        if (v1 != v0) {
            // 0x001173b0
            charge(ctx, 25);
            a0 = 0;
            lw(a1, s1, 16);
            a2 = 0;
            jal(ctx, 0x1173BCu, gen::fn_sprCreateHandle_001158b0);
            s1 = v0;
            v1 = 0x42C80000;
            sw(v1, v0, 44);
            lwc1(f0, s0, 56);
            swc1(f0, v0, 16);
            lwc1(f0, s0, 60);
            swc1(f0, v0, 20);
            v1 = 16;
            sh(v1, v0, 36);
            v1 = 96;
            sh(v1, v0, 38);
            lw(v1, s0, 64);
            sb(v1, v0, 24);
            a0 = s1;
            a1 = 1;
            jal(ctx, 0x117400u, gen::fn_sub_1127D0_001127d0);
            a0 = s1;
            jal(ctx, 0x11740Cu, gen::fn_sub_115980_00115980);
            goto L_00117414;
        }
        // 0x001173a0
        charge(ctx, 4);
        sw(zero, s1, 4);
        v0 = si(-1);
    }
    // 0x00117418 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0x70);
}

// 0x00117440 sub_117440 -- 44 bytes; frame 0x10: ra sp+0x0
// [H_sMarkSpr_Destroy] Destroy callback of "H_sMarkSprDraw": frees the work.
void sub_117440(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00117440
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, task::kWork);
    v0 = 0x960000;
    lw(v0, v0, rw::kFree);  // 0x96017C
    jalr(ctx, 0x117454u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00117470 sub_117470 -- 20 bytes; leaf frame (no stack)
// [H_sMarkSpr_End] Mark sprite work +0xC = 1 (end requested).
void sub_117470(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00117470
    enter(ctx, 5);  // entry check point + this block's cycles
    a1 = 1;
    lw(v1, a0, task::kWork);
    sw(a1, v1, 12);
}

// 0x00117490 sub_117490 -- 176 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_sMarkSpr_Create] Creates "H_sMarkSprDraw" (RwCalloc 0x58, priority 6325, sub_116F80 / sub_117440); sprite file
// +0x10 = $a1.
void sub_117490(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00117490
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    a0 = 1;
    a1 = 88;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, rw::kCalloc);  // 0x960184
    jalr(ctx, 0x1174C0u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x001174e0
        charge(ctx, 13);
        a0 = s2;
        a1 = 0x5D0000;
        a1 = addiu(a1, 28232);  // "H_sMarkSprDraw"
        a2 = 6325;
        a3 = 0x110000;
        a3 = addiu(a3, 28544);  // &sub_116F80
        t0 = 0x110000;
        t0 = addiu(t0, 29760);  // &sub_117440
        t1 = s0;
        jal(ctx, 0x117504u, gen::fn_kwlnTaskCreate_00194b20);
        if (v0 != 0) {
            // 0x00117520
            charge(ctx, 1);
            sw(s1, s0, 16);
        } else {
            // 0x00117514
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x001174d4
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00117524 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00117540 sub_117540 -- 7296 bytes; frame 0x1E0: ra sp+0x90, s5 sp+0x80 (sq), s4 sp+0x70 (sq), s3 sp+0x60 (sq), s2 sp+0x50 (sq), s1 sp+0x40 (sq), s0 sp+0x30 (sq), f21 sp+0x24, f20 sp+0x20
// [H_PerEfect2_Update] Update of "H_PerEfect2Draw" (jump table 0x7B5400): 0 request the one to three persona textures
// "battle/cutin/c71_c80_L_L_1/[AGS_]a_%03X.tmx" and the per_efc2 archive, 1 build the cut-in draw tasks (sub_1103E0,
// layer colours sub_110620) and the texture requests through the resource manager, then the later states map the
// textures, drive the layers (sin / cos motion) and the "H_sMark2SprDraw" task; returns -1 when done.
void sub_117540(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21};
    // 0x00117540
    enter(ctx, 55);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1E0);
    sd(ra, sp, 0x90);
    sq(s5, sp, 0x80);
    sq(s4, sp, 0x70);
    sq(s3, sp, 0x60);
    sq(s2, sp, 0x50);
    sq(s1, sp, 0x40);
    sq(s0, sp, 0x30);
    swc1(f21, sp, 0x24);
    swc1(f20, sp, 0x20);
    s4 = a0;
    lw(s0, a0, task::kWork);
    jal(ctx, 0x117570u, gen::fn_sub_198590_00198590);
    s1 = 0x960000;
    s1 = addiu(s1, rw::kRenderStateSet);  // &pfn_RwRenderStateSet
    a0 = 6;
    a1 = 1;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x11758Cu, v0.u());
    a0 = 7;
    a1 = 2;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x1175A0u, v0.u());
    a0 = 8;
    a1 = 1;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x1175B4u, v0.u());
    a0 = 9;
    a1 = 1;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x1175C8u, v0.u());
    a0 = 12;
    a1 = 1;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x1175DCu, v0.u());
    a0 = 11;
    a1 = 6;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x1175F0u, v0.u());
    a0 = 10;
    a1 = 5;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x117604u, v0.u());
    lw(v0, s0, 0);
    at = sltiu(v0, 6);
    if (at != 0) {
        // 0x0011761c
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, fx::kLoJptPerEfect2);  // &0x7B5400
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x117638u:  // table[0]
            // 0x00117638
            charge(ctx, 4);
            sw(zero, s0, 4);
            v1 = 0;
            for (;;) {
                // 0x0011766c
                charge(ctx, 3);
                v0 = slti(v1, 3);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00117648
                charge(ctx, 5);
                v0 = sll(v1, 2);
                v0 = addu(s0, v0);
                lw(v0, v0, 8);
                if (v0 != 0) {
                    // 0x0011765c
                    charge(ctx, 3);
                    lw(v0, s0, 4);
                    v0 = addiu(v0, 1);
                    sw(v0, s0, 4);
                }
                // 0x00117668
                charge(ctx, 1);
                v1 = addiu(v1, 1);
            }
            // 0x00117678
            charge(ctx, 3);
            lw(v0, s0, 4);
            if (v0 != 0) {
                // 0x00117684
                charge(ctx, 2);
                v0 = addiu(v0, -1);
                sw(v0, s0, 4);
            }
            // 0x0011768c
            charge(ctx, 4);
            jal(ctx, 0x11768Cu, gen::fn_sub_17D800_0017d800);
            if (v0 == 0) {
                // 0x00117920
                charge(ctx, 4);
                lw(v1, s0, 4);
                v0 = 2;
                if (v1 == v0) {
                    // 0x00117a10
                    charge(ctx, 39);
                    a0 = addiu(sp, 0xC0);
                    a1 = 0x5D0000;
                    a1 = addiu(a1, 28304);  // "battle/cutin/c71_c80_L_L_1/a_%03X.tmx"
                    lw(a2, s0, 8);
                    jal(ctx, 0x117A20u, gen::fn_sprintf_00523ac8);
                    a0 = addiu(sp, 0xC0);
                    a1 = 0;
                    jal(ctx, 0x117A30u, gen::fn_H_Cdvd_Request_00100d80);
                    sw(v0, s0, 92);
                    a0 = addiu(sp, 0xC0);
                    a1 = 0x5D0000;
                    a1 = addiu(a1, 28304);  // "battle/cutin/c71_c80_L_L_1/a_%03X.tmx"
                    lw(a2, s0, 12);
                    jal(ctx, 0x117A4Cu, gen::fn_sprintf_00523ac8);
                    a0 = addiu(sp, 0xC0);
                    a1 = 0;
                    jal(ctx, 0x117A5Cu, gen::fn_H_Cdvd_Request_00100d80);
                    sw(v0, s0, 96);
                    a0 = addiu(sp, 0xC0);
                    a1 = 0x5D0000;
                    a1 = addiu(a1, 28304);  // "battle/cutin/c71_c80_L_L_1/a_%03X.tmx"
                    lw(a2, s0, 16);
                    jal(ctx, 0x117A78u, gen::fn_sprintf_00523ac8);
                    a0 = addiu(sp, 0xC0);
                    a1 = 0;
                    jal(ctx, 0x117A88u, gen::fn_H_Cdvd_Request_00100d80);
                    sw(v0, s0, 100);
                    a0 = 0x5D0000;
                    a0 = addiu(a0, 28512);  // "battle/cutin/per_efc2_3.bin"
                    a1 = 1;
                    jal(ctx, 0x117AA0u, gen::fn_H_Cdvd_Request_00100d80);
                    sw(v0, s0, 88);
                } else {
                    // 0x00117930
                    charge(ctx, 3);
                    v0 = 1;
                    if (v1 == v0) {
                        // 0x00117998
                        charge(ctx, 30);
                        a0 = addiu(sp, 0xC0);
                        a1 = 0x5D0000;
                        a1 = addiu(a1, 28304);  // "battle/cutin/c71_c80_L_L_1/a_%03X.tmx"
                        lw(a2, s0, 8);
                        jal(ctx, 0x1179A8u, gen::fn_sprintf_00523ac8);
                        a0 = addiu(sp, 0xC0);
                        a1 = 0;
                        jal(ctx, 0x1179B8u, gen::fn_H_Cdvd_Request_00100d80);
                        sw(v0, s0, 92);
                        a0 = addiu(sp, 0xC0);
                        a1 = 0x5D0000;
                        a1 = addiu(a1, 28304);  // "battle/cutin/c71_c80_L_L_1/a_%03X.tmx"
                        lw(a2, s0, 12);
                        jal(ctx, 0x1179D4u, gen::fn_sprintf_00523ac8);
                        a0 = addiu(sp, 0xC0);
                        a1 = 0;
                        jal(ctx, 0x1179E4u, gen::fn_H_Cdvd_Request_00100d80);
                        sw(v0, s0, 96);
                        a0 = 0x5D0000;
                        a0 = addiu(a0, 28480);  // "battle/cutin/per_efc2_2.bin"
                        a1 = 1;
                        jal(ctx, 0x1179FCu, gen::fn_H_Cdvd_Request_00100d80);
                        sw(v0, s0, 88);
                    } else {
                        // 0x0011793c
                        charge(ctx, 2);
                        if (v1 == 0) {
                            // 0x0011794c
                            charge(ctx, 19);
                            a0 = addiu(sp, 0xC0);
                            a1 = 0x5D0000;
                            a1 = addiu(a1, 28304);  // "battle/cutin/c71_c80_L_L_1/a_%03X.tmx"
                            lw(a2, s0, 8);
                            jal(ctx, 0x11795Cu, gen::fn_sprintf_00523ac8);
                            a0 = addiu(sp, 0xC0);
                            a1 = 0;
                            jal(ctx, 0x11796Cu, gen::fn_H_Cdvd_Request_00100d80);
                            sw(v0, s0, 92);
                            a0 = 0x5D0000;
                            a0 = addiu(a0, 28448);  // "battle/cutin/per_efc2_1.bin"
                            a1 = 1;
                            jal(ctx, 0x117984u, gen::fn_H_Cdvd_Request_00100d80);
                            sw(v0, s0, 88);
                        } else {
                            // 0x00117944
                            charge(ctx, 2);
                        }
                    }
                }
            } else {
                // 0x0011769c
                charge(ctx, 4);
                lw(v1, s0, 4);
                v0 = 2;
                if (v1 == v0) {
                    // 0x00117804
                    charge(ctx, 4);
                    lw(a2, s0, 8);
                    v0 = 9;
                    if (a2 != v0) {
                        // 0x00117830
                        charge(ctx, 5);
                        a0 = addiu(sp, 0xC0);
                        a1 = 0x5D0000;
                        a1 = addiu(a1, 28304);  // "battle/cutin/c71_c80_L_L_1/a_%03X.tmx"
                        jal(ctx, 0x11783Cu, gen::fn_sprintf_00523ac8);
                    } else {
                        // 0x00117814
                        charge(ctx, 7);
                        a0 = addiu(sp, 0xC0);
                        a1 = 0x5D0000;
                        a1 = addiu(a1, 28256);  // "battle/cutin/c71_c80_L_L_1/AGS_a_%03X.tmx"
                        jal(ctx, 0x117820u, gen::fn_sprintf_00523ac8);
                    }
                    // 0x00117844
                    charge(ctx, 9);
                    a0 = addiu(sp, 0xC0);
                    a1 = 0;
                    jal(ctx, 0x11784Cu, gen::fn_H_Cdvd_Request_00100d80);
                    sw(v0, s0, 92);
                    lw(a2, s0, 12);
                    v0 = 9;
                    if (a2 != v0) {
                        // 0x00117884
                        charge(ctx, 5);
                        a0 = addiu(sp, 0xC0);
                        a1 = 0x5D0000;
                        a1 = addiu(a1, 28304);  // "battle/cutin/c71_c80_L_L_1/a_%03X.tmx"
                        jal(ctx, 0x117890u, gen::fn_sprintf_00523ac8);
                    } else {
                        // 0x00117868
                        charge(ctx, 7);
                        a0 = addiu(sp, 0xC0);
                        a1 = 0x5D0000;
                        a1 = addiu(a1, 28256);  // "battle/cutin/c71_c80_L_L_1/AGS_a_%03X.tmx"
                        jal(ctx, 0x117874u, gen::fn_sprintf_00523ac8);
                    }
                    // 0x00117898
                    charge(ctx, 9);
                    a0 = addiu(sp, 0xC0);
                    a1 = 0;
                    jal(ctx, 0x1178A0u, gen::fn_H_Cdvd_Request_00100d80);
                    sw(v0, s0, 96);
                    lw(a2, s0, 16);
                    v0 = 9;
                    if (a2 != v0) {
                        // 0x001178d8
                        charge(ctx, 5);
                        a0 = addiu(sp, 0xC0);
                        a1 = 0x5D0000;
                        a1 = addiu(a1, 28304);  // "battle/cutin/c71_c80_L_L_1/a_%03X.tmx"
                        jal(ctx, 0x1178E4u, gen::fn_sprintf_00523ac8);
                    } else {
                        // 0x001178bc
                        charge(ctx, 7);
                        a0 = addiu(sp, 0xC0);
                        a1 = 0x5D0000;
                        a1 = addiu(a1, 28256);  // "battle/cutin/c71_c80_L_L_1/AGS_a_%03X.tmx"
                        jal(ctx, 0x1178C8u, gen::fn_sprintf_00523ac8);
                    }
                    // 0x001178ec
                    charge(ctx, 13);
                    a0 = addiu(sp, 0xC0);
                    a1 = 0;
                    jal(ctx, 0x1178F4u, gen::fn_H_Cdvd_Request_00100d80);
                    sw(v0, s0, 100);
                    a0 = 0x5D0000;
                    a0 = addiu(a0, 28416);  // "battle/cutin/AGS_per_efc2_3.bin"
                    a1 = 1;
                    jal(ctx, 0x11790Cu, gen::fn_H_Cdvd_Request_00100d80);
                    sw(v0, s0, 88);
                } else {
                    // 0x001176ac
                    charge(ctx, 3);
                    v0 = 1;
                    if (v1 == v0) {
                        // 0x0011773c
                        charge(ctx, 4);
                        lw(a2, s0, 8);
                        v0 = 9;
                        if (a2 != v0) {
                            // 0x00117768
                            charge(ctx, 5);
                            a0 = addiu(sp, 0xC0);
                            a1 = 0x5D0000;
                            a1 = addiu(a1, 28304);  // "battle/cutin/c71_c80_L_L_1/a_%03X.tmx"
                            jal(ctx, 0x117774u, gen::fn_sprintf_00523ac8);
                        } else {
                            // 0x0011774c
                            charge(ctx, 7);
                            a0 = addiu(sp, 0xC0);
                            a1 = 0x5D0000;
                            a1 = addiu(a1, 28256);  // "battle/cutin/c71_c80_L_L_1/AGS_a_%03X.tmx"
                            jal(ctx, 0x117758u, gen::fn_sprintf_00523ac8);
                        }
                        // 0x0011777c
                        charge(ctx, 9);
                        a0 = addiu(sp, 0xC0);
                        a1 = 0;
                        jal(ctx, 0x117784u, gen::fn_H_Cdvd_Request_00100d80);
                        sw(v0, s0, 92);
                        lw(a2, s0, 12);
                        v0 = 9;
                        if (a2 != v0) {
                            // 0x001177bc
                            charge(ctx, 5);
                            a0 = addiu(sp, 0xC0);
                            a1 = 0x5D0000;
                            a1 = addiu(a1, 28304);  // "battle/cutin/c71_c80_L_L_1/a_%03X.tmx"
                            jal(ctx, 0x1177C8u, gen::fn_sprintf_00523ac8);
                        } else {
                            // 0x001177a0
                            charge(ctx, 7);
                            a0 = addiu(sp, 0xC0);
                            a1 = 0x5D0000;
                            a1 = addiu(a1, 28256);  // "battle/cutin/c71_c80_L_L_1/AGS_a_%03X.tmx"
                            jal(ctx, 0x1177ACu, gen::fn_sprintf_00523ac8);
                        }
                        // 0x001177d0
                        charge(ctx, 13);
                        a0 = addiu(sp, 0xC0);
                        a1 = 0;
                        jal(ctx, 0x1177D8u, gen::fn_H_Cdvd_Request_00100d80);
                        sw(v0, s0, 96);
                        a0 = 0x5D0000;
                        a0 = addiu(a0, 28384);  // "battle/cutin/AGS_per_efc2_2.bin"
                        a1 = 1;
                        jal(ctx, 0x1177F0u, gen::fn_H_Cdvd_Request_00100d80);
                        sw(v0, s0, 88);
                    } else {
                        // 0x001176b8
                        charge(ctx, 2);
                        if (v1 == 0) {
                            // 0x001176c8
                            charge(ctx, 4);
                            lw(a2, s0, 8);
                            v0 = 9;
                            if (a2 != v0) {
                                // 0x001176f4
                                charge(ctx, 5);
                                a0 = addiu(sp, 0xC0);
                                a1 = 0x5D0000;
                                a1 = addiu(a1, 28304);  // "battle/cutin/c71_c80_L_L_1/a_%03X.tmx"
                                jal(ctx, 0x117700u, gen::fn_sprintf_00523ac8);
                            } else {
                                // 0x001176d8
                                charge(ctx, 7);
                                a0 = addiu(sp, 0xC0);
                                a1 = 0x5D0000;
                                a1 = addiu(a1, 28256);  // "battle/cutin/c71_c80_L_L_1/AGS_a_%03X.tmx"
                                jal(ctx, 0x1176E4u, gen::fn_sprintf_00523ac8);
                            }
                            // 0x00117708
                            charge(ctx, 13);
                            a0 = addiu(sp, 0xC0);
                            a1 = 0;
                            jal(ctx, 0x117710u, gen::fn_H_Cdvd_Request_00100d80);
                            sw(v0, s0, 92);
                            a0 = 0x5D0000;
                            a0 = addiu(a0, 28352);  // "battle/cutin/AGS_per_efc2_1.bin"
                            a1 = 1;
                            jal(ctx, 0x117728u, gen::fn_H_Cdvd_Request_00100d80);
                            sw(v0, s0, 88);
                        } else {
                            // 0x001176c0
                            charge(ctx, 2);
                        }
                    }
                }
            }
            // 0x00117aac
            charge(ctx, 4);
            v0 = 1;
            sw(v0, s0, 0);
        L_0011918c:
            charge(ctx, 1);
            v0 = 0;
            break;
        case 0x117ABCu:  // table[1]
            // 0x00117abc
            charge(ctx, 4);
            s2 = 1;
            s1 = 0;
            for (;;) {
                // 0x00117af8
                charge(ctx, 3);
                v0 = slti(s1, 9);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00117acc
                charge(ctx, 5);
                v0 = sll(s1, 2);
                v0 = addu(s0, v0);
                lw(a0, v0, 88);
                if (a0 != 0) {
                    // 0x00117ae0
                    charge(ctx, 4);
                    jal(ctx, 0x117AE0u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
                    if (v0 == 0) {
                        // 0x00117af0
                        charge(ctx, 1);
                        s2 = 0;
                    }
                }
                // 0x00117af4
                charge(ctx, 1);
                s1 = addiu(s1, 1);
            }
            // 0x00117b04
            charge(ctx, 2);
            if (s2 != 0) {
                // 0x00117b0c
                charge(ctx, 3);
                s1 = 0;
                for (;;) {
                    // 0x00117c9c
                    charge(ctx, 5);
                    lw(v0, s0, 4);
                    v0 = addiu(v0, 1);
                    v0 = slt(s1, v0);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00117b18
                    charge(ctx, 33);
                    v0 = sll(s1, 3);
                    v1 = subu(v0, s1);
                    v0 = sll(v1, 2);
                    v0 = subu(v0, v1);
                    v0 = sll(v0, 1);
                    s2 = addu(s0, v0);
                    a1 = addiu(s1, 1);
                    lw(a0, s0, 88);
                    a2 = addiu(sp, 0x1DC);
                    jal(ctx, 0x117B3Cu, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                    a0 = addiu(s2, 136);
                    a1 = v0;
                    a2 = 42;
                    jal(ctx, 0x117B50u, gen::fn_memcpy_00521250);
                    a1 = addiu(s1, 1);
                    lw(a0, s0, 88);
                    a2 = addiu(sp, 0x1DC);
                    jal(ctx, 0x117B64u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                    v1 = sll(s1, 2);
                    t0 = addu(s0, v1);
                    v1 = addiu(t0, 124);
                    a3 = addiu(v0, 42);
                    sw(a3, t0, 124);
                    a2 = addiu(t0, 264);
                    sw(zero, t0, 264);
                    t1 = 0;
                    a1 = si(-2);
                    a0 = si(-1);
                    for (;;) {
                        // 0x00117be4
                        charge(ctx, 3);
                        v0 = slti(t1, 1000);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x00117b9c
                        charge(ctx, 7);
                        v0 = sll(t1, 3);
                        v0 = addu(v0, t1);
                        v0 = sll(v0, 1);
                        v0 = addu(a3, v0);
                        lb(v0, v0, 1);
                        if (v0 == a1) {
                            goto L_00117bb8_53;
                        }
                        // 0x00117bcc
                        charge(ctx, 2);
                        if (v0 == a0) {
                            // 0x00117bd4
                            charge(ctx, 3);
                            lw(v0, t0, 264);
                            v0 = addiu(v0, 1);
                            sw(v0, t0, 264);
                        }
                        // 0x00117be0
                        charge(ctx, 1);
                        t1 = addiu(t1, 1);
                    }
                L_00117bf0:
                    charge(ctx, 18);
                    v0 = sll(s1, 3);
                    a0 = subu(v0, s1);
                    v0 = sll(a0, 2);
                    v0 = subu(v0, a0);
                    v0 = sll(v0, 1);
                    s2 = addu(s0, v0);
                    v0 = sll(s1, 2);
                    s3 = addu(s0, v0);
                    lh(a3, s2, 144);
                    a0 = s4;
                    a1 = 6336;
                    lw(a2, v1, 0);
                    jal(ctx, 0x117C20u, gen::fn_sub_1103E0_001103e0);
                    sw(v0, s3, 28);
                    s5 = 0;
                    for (;;) {
                        // 0x00117c8c
                        charge(ctx, 3);
                        v0 = slti(s5, 3);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x00117c38
                        charge(ctx, 3);
                        v0 = 2;
                        if (s5 != v0) {
                            // 0x00117c50
                            charge(ctx, 2);
                            if (s5 != 0) {
                                // 0x00117c64
                                charge(ctx, 1);
                                a1 = 4;
                            } else {
                                // 0x00117c58
                                charge(ctx, 3);
                                a1 = 3;
                            }
                        } else {
                            // 0x00117c44
                            charge(ctx, 3);
                            a1 = 1;
                        }
                        // 0x00117c68
                        charge(ctx, 9);
                        v0 = sll(s5, 1);
                        v0 = addu(s2, v0);
                        lw(a0, s3, 28);
                        lh(a2, v0, 146);
                        lh(a3, v0, 154);
                        lh(t0, v0, 162);
                        jal(ctx, 0x117C80u, gen::fn_sub_110620_00110620);
                        s5 = addiu(s5, 1);
                    }
                    // 0x00117c98
                    charge(ctx, 1);
                    s1 = addiu(s1, 1);
                }
                // 0x00117cb0
                charge(ctx, 13);
                lw(a0, s0, 88);
                a1 = 0;
                a2 = addiu(sp, 0x1D8);
                jal(ctx, 0x117CBCu, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                a0 = v0;
                jal(ctx, 0x117CC8u, gen::fn_sprCreateHandleFromData_00112420);
                sw(v0, s0, 2028);
                jal(ctx, 0x117CD4u, gen::fn_sub_17D800_0017d800);
                if (v0 == 0) {
                    // 0x001183f4
                    charge(ctx, 4);
                    lw(v1, s0, 4);
                    v0 = 2;
                    if (v1 == v0) {
                        // 0x00118764
                        charge(ctx, 132);
                        a0 = addiu(sp, 0xC0);
                        a1 = 0x5D0000;
                        a1 = addiu(a1, 28304);  // "battle/cutin/c71_c80_L_L_1/a_%03X.tmx"
                        lw(a2, s0, 8);
                        jal(ctx, 0x118774u, gen::fn_sprintf_00523ac8);
                        sd(zero, sp, 0x0);
                        sd(zero, sp, 0x8);
                        v0 = 0x5D0000;
                        v0 = addiu(v0, 28544);  // "h_perefect2.c"
                        sd(v0, sp, 0x10);
                        v0 = 370;
                        sd(v0, sp, 0x18);
                        a0 = 0;
                        a1 = addiu(sp, 0xC0);
                        a2 = 0;
                        a3 = 0;
                        t0 = 0;
                        t1 = 0;
                        t2 = 0;
                        t3 = 0;
                        jal(ctx, 0x1187B8u, gen::fn_sub_10C1A0_0010c1a0);
                        sw(v0, s0, 40);
                        sd(zero, sp, 0x0);
                        sd(zero, sp, 0x8);
                        v0 = 0x5D0000;
                        v0 = addiu(v0, 28544);  // "h_perefect2.c"
                        sd(v0, sp, 0x10);
                        v0 = 372;
                        sd(v0, sp, 0x18);
                        a0 = 0;
                        a1 = 0x5D0000;
                        a1 = addiu(a1, 28560);  // "battle/cutin/c71_c80_L_L_1/back00.tmx"
                        a2 = 0;
                        a3 = 0;
                        t0 = 0;
                        t1 = 0;
                        t2 = 0;
                        t3 = 0;
                        jal(ctx, 0x118804u, gen::fn_sub_10C1A0_0010c1a0);
                        sw(v0, s0, 44);
                        a0 = addiu(sp, 0xC0);
                        a1 = 0x5D0000;
                        a1 = addiu(a1, 28304);  // "battle/cutin/c71_c80_L_L_1/a_%03X.tmx"
                        lw(a2, s0, 12);
                        jal(ctx, 0x118820u, gen::fn_sprintf_00523ac8);
                        sd(zero, sp, 0x0);
                        sd(zero, sp, 0x8);
                        v0 = 0x5D0000;
                        v0 = addiu(v0, 28544);  // "h_perefect2.c"
                        sd(v0, sp, 0x10);
                        v0 = 374;
                        sd(v0, sp, 0x18);
                        a0 = 0;
                        a1 = addiu(sp, 0xC0);
                        a2 = 0;
                        a3 = 0;
                        t0 = 0;
                        t1 = 0;
                        t2 = 0;
                        t3 = 0;
                        jal(ctx, 0x118864u, gen::fn_sub_10C1A0_0010c1a0);
                        sw(v0, s0, 48);
                        sd(zero, sp, 0x0);
                        sd(zero, sp, 0x8);
                        v0 = 0x5D0000;
                        v0 = addiu(v0, 28544);  // "h_perefect2.c"
                        sd(v0, sp, 0x10);
                        v0 = 376;
                        sd(v0, sp, 0x18);
                        a0 = 0;
                        a1 = 0x5D0000;
                        a1 = addiu(a1, 28560);  // "battle/cutin/c71_c80_L_L_1/back00.tmx"
                        a2 = 0;
                        a3 = 0;
                        t0 = 0;
                        t1 = 0;
                        t2 = 0;
                        t3 = 0;
                        jal(ctx, 0x1188B0u, gen::fn_sub_10C1A0_0010c1a0);
                        sw(v0, s0, 52);
                        a0 = addiu(sp, 0xC0);
                        a1 = 0x5D0000;
                        a1 = addiu(a1, 28304);  // "battle/cutin/c71_c80_L_L_1/a_%03X.tmx"
                        lw(a2, s0, 16);
                        jal(ctx, 0x1188CCu, gen::fn_sprintf_00523ac8);
                        sd(zero, sp, 0x0);
                        sd(zero, sp, 0x8);
                        v0 = 0x5D0000;
                        v0 = addiu(v0, 28544);  // "h_perefect2.c"
                        sd(v0, sp, 0x10);
                        v0 = 378;
                        sd(v0, sp, 0x18);
                        a0 = 0;
                        a1 = addiu(sp, 0xC0);
                        a2 = 0;
                        a3 = 0;
                        t0 = 0;
                        t1 = 0;
                        t2 = 0;
                        t3 = 0;
                        jal(ctx, 0x118910u, gen::fn_sub_10C1A0_0010c1a0);
                        sw(v0, s0, 56);
                        sd(zero, sp, 0x0);
                        sd(zero, sp, 0x8);
                        v0 = 0x5D0000;
                        v0 = addiu(v0, 28544);  // "h_perefect2.c"
                        sd(v0, sp, 0x10);
                        v0 = 380;
                        sd(v0, sp, 0x18);
                        a0 = 0;
                        a1 = 0x5D0000;
                        a1 = addiu(a1, 28560);  // "battle/cutin/c71_c80_L_L_1/back00.tmx"
                        a2 = 0;
                        a3 = 0;
                        t0 = 0;
                        t1 = 0;
                        t2 = 0;
                        t3 = 0;
                        jal(ctx, 0x11895Cu, gen::fn_sub_10C1A0_0010c1a0);
                        sw(v0, s0, 60);
                        s1 = 0;
                        for (;;) {
                            // 0x001189c0
                            charge(ctx, 2);
                            if (i64(s1) > 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x00118974
                            charge(ctx, 19);
                            v0 = sll(s1, 5);
                            v1 = subu(v0, s1);
                            v0 = sll(v1, 3);
                            v0 = subu(v0, v1);
                            v0 = sll(v0, 2);
                            v0 = addu(s0, v0);
                            s2 = addiu(v0, 564);
                            a1 = addiu(s1, 5);
                            lw(a0, s0, 88);
                            a2 = addiu(v0, 572);
                            jal(ctx, 0x11899Cu, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                            sw(v0, s2, 0);
                            a0 = 0x5D0000;
                            a0 = addiu(a0, 28600);  // "battle/cutin/"
                            a1 = v0;
                            jal(ctx, 0x1189B4u, gen::fn_H_Cdvd_CacheAddArchive_00102720);
                            s1 = addiu(s1, 1);
                        }
                        // 0x001189c8
                        charge(ctx, 14);
                        v0 = 40;
                        sh(v0, sp, 0x1C8);
                        v0 = 2;
                        sh(v0, sp, 0x1CA);
                        v0 = 10;
                        sh(v0, sp, 0x1CC);
                        sh(zero, sp, 0x1CE);
                        a0 = s4;
                        a1 = 6336;
                        ld(a2, sp, 0x1C8);
                        a3 = addiu(s0, 292);
                        jal(ctx, 0x1189F4u, gen::fn_sub_111380_00111380);
                        sw(v0, s0, 20);
                    } else {
                        // 0x00118404
                        charge(ctx, 3);
                        v0 = 1;
                        if (v1 == v0) {
                            // 0x0011856c
                            charge(ctx, 89);
                            a0 = addiu(sp, 0xC0);
                            a1 = 0x5D0000;
                            a1 = addiu(a1, 28304);  // "battle/cutin/c71_c80_L_L_1/a_%03X.tmx"
                            lw(a2, s0, 8);
                            jal(ctx, 0x11857Cu, gen::fn_sprintf_00523ac8);
                            sd(zero, sp, 0x0);
                            sd(zero, sp, 0x8);
                            v0 = 0x5D0000;
                            v0 = addiu(v0, 28544);  // "h_perefect2.c"
                            sd(v0, sp, 0x10);
                            v0 = 350;
                            sd(v0, sp, 0x18);
                            a0 = 0;
                            a1 = addiu(sp, 0xC0);
                            a2 = 0;
                            a3 = 0;
                            t0 = 0;
                            t1 = 0;
                            t2 = 0;
                            t3 = 0;
                            jal(ctx, 0x1185C0u, gen::fn_sub_10C1A0_0010c1a0);
                            sw(v0, s0, 40);
                            sd(zero, sp, 0x0);
                            sd(zero, sp, 0x8);
                            v0 = 0x5D0000;
                            v0 = addiu(v0, 28544);  // "h_perefect2.c"
                            sd(v0, sp, 0x10);
                            v0 = 351;
                            sd(v0, sp, 0x18);
                            a0 = 0;
                            a1 = 0x5D0000;
                            a1 = addiu(a1, 28560);  // "battle/cutin/c71_c80_L_L_1/back00.tmx"
                            a2 = 0;
                            a3 = 0;
                            t0 = 0;
                            t1 = 0;
                            t2 = 0;
                            t3 = 0;
                            jal(ctx, 0x11860Cu, gen::fn_sub_10C1A0_0010c1a0);
                            sw(v0, s0, 44);
                            a0 = addiu(sp, 0xC0);
                            a1 = 0x5D0000;
                            a1 = addiu(a1, 28304);  // "battle/cutin/c71_c80_L_L_1/a_%03X.tmx"
                            lw(a2, s0, 12);
                            jal(ctx, 0x118628u, gen::fn_sprintf_00523ac8);
                            sd(zero, sp, 0x0);
                            sd(zero, sp, 0x8);
                            v0 = 0x5D0000;
                            v0 = addiu(v0, 28544);  // "h_perefect2.c"
                            sd(v0, sp, 0x10);
                            v0 = 353;
                            sd(v0, sp, 0x18);
                            a0 = 0;
                            a1 = addiu(sp, 0xC0);
                            a2 = 0;
                            a3 = 0;
                            t0 = 0;
                            t1 = 0;
                            t2 = 0;
                            t3 = 0;
                            jal(ctx, 0x11866Cu, gen::fn_sub_10C1A0_0010c1a0);
                            sw(v0, s0, 48);
                            sd(zero, sp, 0x0);
                            sd(zero, sp, 0x8);
                            v0 = 0x5D0000;
                            v0 = addiu(v0, 28544);  // "h_perefect2.c"
                            sd(v0, sp, 0x10);
                            v0 = 354;
                            sd(v0, sp, 0x18);
                            a0 = 0;
                            a1 = 0x5D0000;
                            a1 = addiu(a1, 28560);  // "battle/cutin/c71_c80_L_L_1/back00.tmx"
                            a2 = 0;
                            a3 = 0;
                            t0 = 0;
                            t1 = 0;
                            t2 = 0;
                            t3 = 0;
                            jal(ctx, 0x1186B8u, gen::fn_sub_10C1A0_0010c1a0);
                            sw(v0, s0, 52);
                            s1 = 0;
                            for (;;) {
                                // 0x0011871c
                                charge(ctx, 2);
                                if (i64(s1) > 0) {
                                    break;
                                }
                                backedge(ctx);
                                // 0x001186d0
                                charge(ctx, 19);
                                v0 = sll(s1, 5);
                                v1 = subu(v0, s1);
                                v0 = sll(v1, 3);
                                v0 = subu(v0, v1);
                                v0 = sll(v0, 2);
                                v0 = addu(s0, v0);
                                s2 = addiu(v0, 564);
                                a1 = addiu(s1, 4);
                                lw(a0, s0, 88);
                                a2 = addiu(v0, 572);
                                jal(ctx, 0x1186F8u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                                sw(v0, s2, 0);
                                a0 = 0x5D0000;
                                a0 = addiu(a0, 28600);  // "battle/cutin/"
                                a1 = v0;
                                jal(ctx, 0x118710u, gen::fn_H_Cdvd_CacheAddArchive_00102720);
                                s1 = addiu(s1, 1);
                            }
                            // 0x00118724
                            charge(ctx, 16);
                            v0 = 40;
                            sh(v0, sp, 0x1C8);
                            v0 = 1;
                            sh(v0, sp, 0x1CA);
                            v0 = 11;
                            sh(v0, sp, 0x1CC);
                            sh(zero, sp, 0x1CE);
                            a0 = s4;
                            a1 = 6336;
                            ld(a2, sp, 0x1C8);
                            a3 = addiu(s0, 292);
                            jal(ctx, 0x118750u, gen::fn_sub_111380_00111380);
                            sw(v0, s0, 20);
                        } else {
                            // 0x00118410
                            charge(ctx, 2);
                            if (v1 == 0) {
                                // 0x00118420
                                charge(ctx, 46);
                                a0 = addiu(sp, 0xC0);
                                a1 = 0x5D0000;
                                a1 = addiu(a1, 28304);  // "battle/cutin/c71_c80_L_L_1/a_%03X.tmx"
                                lw(a2, s0, 8);
                                jal(ctx, 0x118430u, gen::fn_sprintf_00523ac8);
                                sd(zero, sp, 0x0);
                                sd(zero, sp, 0x8);
                                v0 = 0x5D0000;
                                v0 = addiu(v0, 28544);  // "h_perefect2.c"
                                sd(v0, sp, 0x10);
                                v0 = 333;
                                sd(v0, sp, 0x18);
                                a0 = 0;
                                a1 = addiu(sp, 0xC0);
                                a2 = 0;
                                a3 = 0;
                                t0 = 0;
                                t1 = 0;
                                t2 = 0;
                                t3 = 0;
                                jal(ctx, 0x118474u, gen::fn_sub_10C1A0_0010c1a0);
                                sw(v0, s0, 40);
                                sd(zero, sp, 0x0);
                                sd(zero, sp, 0x8);
                                v0 = 0x5D0000;
                                v0 = addiu(v0, 28544);  // "h_perefect2.c"
                                sd(v0, sp, 0x10);
                                v0 = 334;
                                sd(v0, sp, 0x18);
                                a0 = 0;
                                a1 = 0x5D0000;
                                a1 = addiu(a1, 28560);  // "battle/cutin/c71_c80_L_L_1/back00.tmx"
                                a2 = 0;
                                a3 = 0;
                                t0 = 0;
                                t1 = 0;
                                t2 = 0;
                                t3 = 0;
                                jal(ctx, 0x1184C0u, gen::fn_sub_10C1A0_0010c1a0);
                                sw(v0, s0, 44);
                                s1 = 0;
                                for (;;) {
                                    // 0x00118524
                                    charge(ctx, 2);
                                    if (i64(s1) > 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                    // 0x001184d8
                                    charge(ctx, 19);
                                    v0 = sll(s1, 5);
                                    v1 = subu(v0, s1);
                                    v0 = sll(v1, 3);
                                    v0 = subu(v0, v1);
                                    v0 = sll(v0, 2);
                                    v0 = addu(s0, v0);
                                    s2 = addiu(v0, 564);
                                    a1 = addiu(s1, 3);
                                    lw(a0, s0, 88);
                                    a2 = addiu(v0, 572);
                                    jal(ctx, 0x118500u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                                    sw(v0, s2, 0);
                                    a0 = 0x5D0000;
                                    a0 = addiu(a0, 28600);  // "battle/cutin/"
                                    a1 = v0;
                                    jal(ctx, 0x118518u, gen::fn_H_Cdvd_CacheAddArchive_00102720);
                                    s1 = addiu(s1, 1);
                                }
                                // 0x0011852c
                                charge(ctx, 16);
                                v0 = 40;
                                sh(v0, sp, 0x1C8);
                                v0 = 1;
                                sh(v0, sp, 0x1CA);
                                v0 = 10;
                                sh(v0, sp, 0x1CC);
                                sh(zero, sp, 0x1CE);
                                a0 = s4;
                                a1 = 6336;
                                ld(a2, sp, 0x1C8);
                                a3 = addiu(s0, 292);
                                jal(ctx, 0x118558u, gen::fn_sub_111380_00111380);
                                sw(v0, s0, 20);
                            } else {
                                // 0x00118418
                                charge(ctx, 2);
                            }
                        }
                    }
                } else {
                    // 0x00117ce4
                    charge(ctx, 4);
                    lw(v1, s0, 4);
                    v0 = 2;
                    if (v1 == v0) {
                        // 0x001180d4
                        charge(ctx, 4);
                        lw(a2, s0, 8);
                        v0 = 9;
                        if (a2 != v0) {
                            // 0x00118100
                            charge(ctx, 5);
                            a0 = addiu(sp, 0xC0);
                            a1 = 0x5D0000;
                            a1 = addiu(a1, 28304);  // "battle/cutin/c71_c80_L_L_1/a_%03X.tmx"
                            jal(ctx, 0x11810Cu, gen::fn_sprintf_00523ac8);
                        } else {
                            // 0x001180e4
                            charge(ctx, 7);
                            a0 = addiu(sp, 0xC0);
                            a1 = 0x5D0000;
                            a1 = addiu(a1, 28256);  // "battle/cutin/c71_c80_L_L_1/AGS_a_%03X.tmx"
                            jal(ctx, 0x1180F0u, gen::fn_sprintf_00523ac8);
                        }
                        // 0x00118114
                        charge(ctx, 41);
                        sd(zero, sp, 0x0);
                        sd(zero, sp, 0x8);
                        v0 = 0x5D0000;
                        v0 = addiu(v0, 28544);  // "h_perefect2.c"
                        sd(v0, sp, 0x10);
                        v0 = 299;
                        sd(v0, sp, 0x18);
                        a0 = 0;
                        a1 = addiu(sp, 0xC0);
                        a2 = 0;
                        a3 = 0;
                        t0 = 0;
                        t1 = 0;
                        t2 = 0;
                        t3 = 0;
                        jal(ctx, 0x118150u, gen::fn_sub_10C1A0_0010c1a0);
                        sw(v0, s0, 40);
                        sd(zero, sp, 0x0);
                        sd(zero, sp, 0x8);
                        v0 = 0x5D0000;
                        v0 = addiu(v0, 28544);  // "h_perefect2.c"
                        sd(v0, sp, 0x10);
                        v0 = 300;
                        sd(v0, sp, 0x18);
                        a0 = 0;
                        a1 = 0x5D0000;
                        a1 = addiu(a1, 28560);  // "battle/cutin/c71_c80_L_L_1/back00.tmx"
                        a2 = 0;
                        a3 = 0;
                        t0 = 0;
                        t1 = 0;
                        t2 = 0;
                        t3 = 0;
                        jal(ctx, 0x11819Cu, gen::fn_sub_10C1A0_0010c1a0);
                        sw(v0, s0, 44);
                        lw(a2, s0, 12);
                        v0 = 9;
                        if (a2 != v0) {
                            // 0x001181d4
                            charge(ctx, 5);
                            a0 = addiu(sp, 0xC0);
                            a1 = 0x5D0000;
                            a1 = addiu(a1, 28304);  // "battle/cutin/c71_c80_L_L_1/a_%03X.tmx"
                            jal(ctx, 0x1181E0u, gen::fn_sprintf_00523ac8);
                        } else {
                            // 0x001181b8
                            charge(ctx, 7);
                            a0 = addiu(sp, 0xC0);
                            a1 = 0x5D0000;
                            a1 = addiu(a1, 28256);  // "battle/cutin/c71_c80_L_L_1/AGS_a_%03X.tmx"
                            jal(ctx, 0x1181C4u, gen::fn_sprintf_00523ac8);
                        }
                        // 0x001181e8
                        charge(ctx, 41);
                        sd(zero, sp, 0x0);
                        sd(zero, sp, 0x8);
                        v0 = 0x5D0000;
                        v0 = addiu(v0, 28544);  // "h_perefect2.c"
                        sd(v0, sp, 0x10);
                        v0 = 306;
                        sd(v0, sp, 0x18);
                        a0 = 0;
                        a1 = addiu(sp, 0xC0);
                        a2 = 0;
                        a3 = 0;
                        t0 = 0;
                        t1 = 0;
                        t2 = 0;
                        t3 = 0;
                        jal(ctx, 0x118224u, gen::fn_sub_10C1A0_0010c1a0);
                        sw(v0, s0, 48);
                        sd(zero, sp, 0x0);
                        sd(zero, sp, 0x8);
                        v0 = 0x5D0000;
                        v0 = addiu(v0, 28544);  // "h_perefect2.c"
                        sd(v0, sp, 0x10);
                        v0 = 307;
                        sd(v0, sp, 0x18);
                        a0 = 0;
                        a1 = 0x5D0000;
                        a1 = addiu(a1, 28560);  // "battle/cutin/c71_c80_L_L_1/back00.tmx"
                        a2 = 0;
                        a3 = 0;
                        t0 = 0;
                        t1 = 0;
                        t2 = 0;
                        t3 = 0;
                        jal(ctx, 0x118270u, gen::fn_sub_10C1A0_0010c1a0);
                        sw(v0, s0, 52);
                        lw(a2, s0, 16);
                        v0 = 9;
                        if (a2 != v0) {
                            // 0x001182a8
                            charge(ctx, 5);
                            a0 = addiu(sp, 0xC0);
                            a1 = 0x5D0000;
                            a1 = addiu(a1, 28304);  // "battle/cutin/c71_c80_L_L_1/a_%03X.tmx"
                            jal(ctx, 0x1182B4u, gen::fn_sprintf_00523ac8);
                        } else {
                            // 0x0011828c
                            charge(ctx, 7);
                            a0 = addiu(sp, 0xC0);
                            a1 = 0x5D0000;
                            a1 = addiu(a1, 28256);  // "battle/cutin/c71_c80_L_L_1/AGS_a_%03X.tmx"
                            jal(ctx, 0x118298u, gen::fn_sprintf_00523ac8);
                        }
                        // 0x001182bc
                        charge(ctx, 40);
                        sd(zero, sp, 0x0);
                        sd(zero, sp, 0x8);
                        v0 = 0x5D0000;
                        v0 = addiu(v0, 28544);  // "h_perefect2.c"
                        sd(v0, sp, 0x10);
                        v0 = 313;
                        sd(v0, sp, 0x18);
                        a0 = 0;
                        a1 = addiu(sp, 0xC0);
                        a2 = 0;
                        a3 = 0;
                        t0 = 0;
                        t1 = 0;
                        t2 = 0;
                        t3 = 0;
                        jal(ctx, 0x1182F8u, gen::fn_sub_10C1A0_0010c1a0);
                        sw(v0, s0, 56);
                        sd(zero, sp, 0x0);
                        sd(zero, sp, 0x8);
                        v0 = 0x5D0000;
                        v0 = addiu(v0, 28544);  // "h_perefect2.c"
                        sd(v0, sp, 0x10);
                        v0 = 314;
                        sd(v0, sp, 0x18);
                        a0 = 0;
                        a1 = 0x5D0000;
                        a1 = addiu(a1, 28560);  // "battle/cutin/c71_c80_L_L_1/back00.tmx"
                        a2 = 0;
                        a3 = 0;
                        t0 = 0;
                        t1 = 0;
                        t2 = 0;
                        t3 = 0;
                        jal(ctx, 0x118344u, gen::fn_sub_10C1A0_0010c1a0);
                        sw(v0, s0, 60);
                        s1 = 0;
                        for (;;) {
                            // 0x001183a8
                            charge(ctx, 2);
                            if (i64(s1) > 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x0011835c
                            charge(ctx, 19);
                            v0 = sll(s1, 5);
                            v1 = subu(v0, s1);
                            v0 = sll(v1, 3);
                            v0 = subu(v0, v1);
                            v0 = sll(v0, 2);
                            v0 = addu(s0, v0);
                            s2 = addiu(v0, 564);
                            a1 = addiu(s1, 5);
                            lw(a0, s0, 88);
                            a2 = addiu(v0, 572);
                            jal(ctx, 0x118384u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                            sw(v0, s2, 0);
                            a0 = 0x5D0000;
                            a0 = addiu(a0, 28600);  // "battle/cutin/"
                            a1 = v0;
                            jal(ctx, 0x11839Cu, gen::fn_H_Cdvd_CacheAddArchive_00102720);
                            s1 = addiu(s1, 1);
                        }
                        // 0x001183b0
                        charge(ctx, 17);
                        v0 = 40;
                        sh(v0, sp, 0x1C8);
                        v0 = 2;
                        sh(v0, sp, 0x1CA);
                        v0 = 10;
                        sh(v0, sp, 0x1CC);
                        v0 = 5;
                        sh(v0, sp, 0x1CE);
                        a0 = s4;
                        a1 = 6336;
                        ld(a2, sp, 0x1C8);
                        a3 = addiu(s0, 292);
                        jal(ctx, 0x1183E0u, gen::fn_sub_111380_00111380);
                        sw(v0, s0, 20);
                    } else {
                        // 0x00117cf4
                        charge(ctx, 3);
                        v0 = 1;
                        if (v1 == v0) {
                            // 0x00117e88
                            charge(ctx, 4);
                            lw(a2, s0, 8);
                            v0 = 9;
                            if (a2 != v0) {
                                // 0x00117eb4
                                charge(ctx, 5);
                                a0 = addiu(sp, 0xC0);
                                a1 = 0x5D0000;
                                a1 = addiu(a1, 28304);  // "battle/cutin/c71_c80_L_L_1/a_%03X.tmx"
                                jal(ctx, 0x117EC0u, gen::fn_sprintf_00523ac8);
                            } else {
                                // 0x00117e98
                                charge(ctx, 7);
                                a0 = addiu(sp, 0xC0);
                                a1 = 0x5D0000;
                                a1 = addiu(a1, 28256);  // "battle/cutin/c71_c80_L_L_1/AGS_a_%03X.tmx"
                                jal(ctx, 0x117EA4u, gen::fn_sprintf_00523ac8);
                            }
                            // 0x00117ec8
                            charge(ctx, 41);
                            sd(zero, sp, 0x0);
                            sd(zero, sp, 0x8);
                            v0 = 0x5D0000;
                            v0 = addiu(v0, 28544);  // "h_perefect2.c"
                            sd(v0, sp, 0x10);
                            v0 = 268;
                            sd(v0, sp, 0x18);
                            a0 = 0;
                            a1 = addiu(sp, 0xC0);
                            a2 = 0;
                            a3 = 0;
                            t0 = 0;
                            t1 = 0;
                            t2 = 0;
                            t3 = 0;
                            jal(ctx, 0x117F04u, gen::fn_sub_10C1A0_0010c1a0);
                            sw(v0, s0, 40);
                            sd(zero, sp, 0x0);
                            sd(zero, sp, 0x8);
                            v0 = 0x5D0000;
                            v0 = addiu(v0, 28544);  // "h_perefect2.c"
                            sd(v0, sp, 0x10);
                            v0 = 269;
                            sd(v0, sp, 0x18);
                            a0 = 0;
                            a1 = 0x5D0000;
                            a1 = addiu(a1, 28560);  // "battle/cutin/c71_c80_L_L_1/back00.tmx"
                            a2 = 0;
                            a3 = 0;
                            t0 = 0;
                            t1 = 0;
                            t2 = 0;
                            t3 = 0;
                            jal(ctx, 0x117F50u, gen::fn_sub_10C1A0_0010c1a0);
                            sw(v0, s0, 44);
                            lw(a2, s0, 12);
                            v0 = 9;
                            if (a2 != v0) {
                                // 0x00117f88
                                charge(ctx, 5);
                                a0 = addiu(sp, 0xC0);
                                a1 = 0x5D0000;
                                a1 = addiu(a1, 28304);  // "battle/cutin/c71_c80_L_L_1/a_%03X.tmx"
                                jal(ctx, 0x117F94u, gen::fn_sprintf_00523ac8);
                            } else {
                                // 0x00117f6c
                                charge(ctx, 7);
                                a0 = addiu(sp, 0xC0);
                                a1 = 0x5D0000;
                                a1 = addiu(a1, 28256);  // "battle/cutin/c71_c80_L_L_1/AGS_a_%03X.tmx"
                                jal(ctx, 0x117F78u, gen::fn_sprintf_00523ac8);
                            }
                            // 0x00117f9c
                            charge(ctx, 40);
                            sd(zero, sp, 0x0);
                            sd(zero, sp, 0x8);
                            v0 = 0x5D0000;
                            v0 = addiu(v0, 28544);  // "h_perefect2.c"
                            sd(v0, sp, 0x10);
                            v0 = 275;
                            sd(v0, sp, 0x18);
                            a0 = 0;
                            a1 = addiu(sp, 0xC0);
                            a2 = 0;
                            a3 = 0;
                            t0 = 0;
                            t1 = 0;
                            t2 = 0;
                            t3 = 0;
                            jal(ctx, 0x117FD8u, gen::fn_sub_10C1A0_0010c1a0);
                            sw(v0, s0, 48);
                            sd(zero, sp, 0x0);
                            sd(zero, sp, 0x8);
                            v0 = 0x5D0000;
                            v0 = addiu(v0, 28544);  // "h_perefect2.c"
                            sd(v0, sp, 0x10);
                            v0 = 277;
                            sd(v0, sp, 0x18);
                            a0 = 0;
                            a1 = 0x5D0000;
                            a1 = addiu(a1, 28560);  // "battle/cutin/c71_c80_L_L_1/back00.tmx"
                            a2 = 0;
                            a3 = 0;
                            t0 = 0;
                            t1 = 0;
                            t2 = 0;
                            t3 = 0;
                            jal(ctx, 0x118024u, gen::fn_sub_10C1A0_0010c1a0);
                            sw(v0, s0, 52);
                            s1 = 0;
                            for (;;) {
                                // 0x00118088
                                charge(ctx, 2);
                                if (i64(s1) > 0) {
                                    break;
                                }
                                backedge(ctx);
                                // 0x0011803c
                                charge(ctx, 19);
                                v0 = sll(s1, 5);
                                v1 = subu(v0, s1);
                                v0 = sll(v1, 3);
                                v0 = subu(v0, v1);
                                v0 = sll(v0, 2);
                                v0 = addu(s0, v0);
                                s2 = addiu(v0, 564);
                                a1 = addiu(s1, 4);
                                lw(a0, s0, 88);
                                a2 = addiu(v0, 572);
                                jal(ctx, 0x118064u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                                sw(v0, s2, 0);
                                a0 = 0x5D0000;
                                a0 = addiu(a0, 28600);  // "battle/cutin/"
                                a1 = v0;
                                jal(ctx, 0x11807Cu, gen::fn_H_Cdvd_CacheAddArchive_00102720);
                                s1 = addiu(s1, 1);
                            }
                            // 0x00118090
                            charge(ctx, 17);
                            v0 = 40;
                            sh(v0, sp, 0x1C8);
                            v0 = 1;
                            sh(v0, sp, 0x1CA);
                            v0 = 11;
                            sh(v0, sp, 0x1CC);
                            v0 = 5;
                            sh(v0, sp, 0x1CE);
                            a0 = s4;
                            a1 = 6336;
                            ld(a2, sp, 0x1C8);
                            a3 = addiu(s0, 292);
                            jal(ctx, 0x1180C0u, gen::fn_sub_111380_00111380);
                            sw(v0, s0, 20);
                        } else {
                            // 0x00117d00
                            charge(ctx, 2);
                            if (v1 == 0) {
                                // 0x00117d10
                                charge(ctx, 4);
                                lw(a2, s0, 8);
                                v0 = 9;
                                if (a2 != v0) {
                                    // 0x00117d3c
                                    charge(ctx, 5);
                                    a0 = addiu(sp, 0xC0);
                                    a1 = 0x5D0000;
                                    a1 = addiu(a1, 28304);  // "battle/cutin/c71_c80_L_L_1/a_%03X.tmx"
                                    jal(ctx, 0x117D48u, gen::fn_sprintf_00523ac8);
                                } else {
                                    // 0x00117d20
                                    charge(ctx, 7);
                                    a0 = addiu(sp, 0xC0);
                                    a1 = 0x5D0000;
                                    a1 = addiu(a1, 28256);  // "battle/cutin/c71_c80_L_L_1/AGS_a_%03X.tmx"
                                    jal(ctx, 0x117D2Cu, gen::fn_sprintf_00523ac8);
                                }
                                // 0x00117d50
                                charge(ctx, 40);
                                sd(zero, sp, 0x0);
                                sd(zero, sp, 0x8);
                                v0 = 0x5D0000;
                                v0 = addiu(v0, 28544);  // "h_perefect2.c"
                                sd(v0, sp, 0x10);
                                v0 = 246;
                                sd(v0, sp, 0x18);
                                a0 = 0;
                                a1 = addiu(sp, 0xC0);
                                a2 = 0;
                                a3 = 0;
                                t0 = 0;
                                t1 = 0;
                                t2 = 0;
                                t3 = 0;
                                jal(ctx, 0x117D8Cu, gen::fn_sub_10C1A0_0010c1a0);
                                sw(v0, s0, 40);
                                sd(zero, sp, 0x0);
                                sd(zero, sp, 0x8);
                                v0 = 0x5D0000;
                                v0 = addiu(v0, 28544);  // "h_perefect2.c"
                                sd(v0, sp, 0x10);
                                v0 = 247;
                                sd(v0, sp, 0x18);
                                a0 = 0;
                                a1 = 0x5D0000;
                                a1 = addiu(a1, 28560);  // "battle/cutin/c71_c80_L_L_1/back00.tmx"
                                a2 = 0;
                                a3 = 0;
                                t0 = 0;
                                t1 = 0;
                                t2 = 0;
                                t3 = 0;
                                jal(ctx, 0x117DD8u, gen::fn_sub_10C1A0_0010c1a0);
                                sw(v0, s0, 44);
                                s1 = 0;
                                for (;;) {
                                    // 0x00117e3c
                                    charge(ctx, 2);
                                    if (i64(s1) > 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                    // 0x00117df0
                                    charge(ctx, 19);
                                    v0 = sll(s1, 5);
                                    v1 = subu(v0, s1);
                                    v0 = sll(v1, 3);
                                    v0 = subu(v0, v1);
                                    v0 = sll(v0, 2);
                                    v0 = addu(s0, v0);
                                    s2 = addiu(v0, 564);
                                    a1 = addiu(s1, 3);
                                    lw(a0, s0, 88);
                                    a2 = addiu(v0, 572);
                                    jal(ctx, 0x117E18u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                                    sw(v0, s2, 0);
                                    a0 = 0x5D0000;
                                    a0 = addiu(a0, 28600);  // "battle/cutin/"
                                    a1 = v0;
                                    jal(ctx, 0x117E30u, gen::fn_H_Cdvd_CacheAddArchive_00102720);
                                    s1 = addiu(s1, 1);
                                }
                                // 0x00117e44
                                charge(ctx, 17);
                                v0 = 40;
                                sh(v0, sp, 0x1C8);
                                v0 = 1;
                                sh(v0, sp, 0x1CA);
                                v0 = 10;
                                sh(v0, sp, 0x1CC);
                                v0 = 5;
                                sh(v0, sp, 0x1CE);
                                a0 = s4;
                                a1 = 6336;
                                ld(a2, sp, 0x1C8);
                                a3 = addiu(s0, 292);
                                jal(ctx, 0x117E74u, gen::fn_sub_111380_00111380);
                                sw(v0, s0, 20);
                            } else {
                                // 0x00117d08
                                charge(ctx, 2);
                            }
                        }
                    }
                }
                // 0x00118a00
                charge(ctx, 4);
                v0 = 2;
                sw(v0, s0, 0);
            }
            goto L_0011918c;
        case 0x118A10u:  // table[2]
            // 0x00118a10
            charge(ctx, 6);
            s2 = 1;
            lw(a0, s0, 2028);
            jal(ctx, 0x118A18u, gen::fn_sprFileIsReady_00111f30);
            if (v0 == 0) {
                // 0x00118a28
                charge(ctx, 1);
                s2 = 0;
            }
            // 0x00118a2c
            charge(ctx, 3);
            s1 = 0;
            for (;;) {
                // 0x00118a94
                charge(ctx, 3);
                v0 = slti(s1, 6);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00118a38
                charge(ctx, 6);
                v0 = sll(s1, 2);
                v1 = addu(s0, v0);
                s4 = addiu(v1, 64);
                lw(v0, v1, 64);
                if (v0 == 0) {
                    // 0x00118a50
                    charge(ctx, 4);
                    s3 = addiu(v1, 40);
                    lw(a0, v1, 40);
                    if (a0 != 0) {
                        // 0x00118a60
                        charge(ctx, 8);
                        a1 = addiu(sp, 0x1D4);
                        a2 = 0;
                        jal(ctx, 0x118A68u, gen::fn_sub_10C3A0_0010c3a0);
                        sw(v0, s4, 0);
                        lw(v0, sp, 0x1D4);
                        if (v0 != 0) {
                            // 0x00118a8c
                            charge(ctx, 1);
                            sw(zero, s3, 0);
                        } else {
                            // 0x00118a80
                            charge(ctx, 3);
                            s2 = 0;
                        }
                    }
                }
                // 0x00118a90
                charge(ctx, 1);
                s1 = addiu(s1, 1);
            }
            // 0x00118aa0
            charge(ctx, 3);
            s1 = 0;
            for (;;) {
                // 0x00118ad8
                charge(ctx, 3);
                v0 = slti(s1, 3);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00118aac
                charge(ctx, 5);
                v0 = sll(s1, 2);
                v0 = addu(s0, v0);
                lw(a0, v0, 28);
                if (a0 != 0) {
                    // 0x00118ac0
                    charge(ctx, 4);
                    jal(ctx, 0x118AC0u, gen::fn_sub_1104B0_001104b0);
                    if (v0 == 0) {
                        // 0x00118ad0
                        charge(ctx, 1);
                        s2 = 0;
                    }
                }
                // 0x00118ad4
                charge(ctx, 1);
                s1 = addiu(s1, 1);
            }
            // 0x00118ae4
            charge(ctx, 2);
            if (s2 != 0) {
                // 0x00118aec
                charge(ctx, 5);
                lw(a0, s0, 20);
                jal(ctx, 0x118AF0u, gen::fn_sub_1114B0_001114b0);
                if (v0 != 0) {
                    // 0x00118b00
                    charge(ctx, 4);
                    lw(v1, s0, 4);
                    v0 = 2;
                    if (v1 == v0) {
                        // 0x00118c44
                        charge(ctx, 66);
                        lw(a1, s0, 64);
                        lw(v1, a1, 80);
                        v0 = lui(0xFFFF);
                        a0 = v0 | 0xFF;
                        v0 = v1 & a0;
                        v0 = v0 | 0x3300;
                        sw(v0, a1, 80);
                        lw(v1, s0, 68);
                        lw(v0, v1, 80);
                        v0 = v0 & a0;
                        v0 = v0 | 0x3300;
                        sw(v0, v1, 80);
                        lw(a0, s0, 28);
                        a1 = 0;
                        lw(a2, s0, 68);
                        jal(ctx, 0x118C80u, gen::fn_sub_1105D0_001105d0);
                        lw(a0, s0, 28);
                        a1 = 1;
                        lw(a2, s0, 64);
                        jal(ctx, 0x118C94u, gen::fn_sub_1105D0_001105d0);
                        lw(a1, s0, 72);
                        lw(v1, a1, 80);
                        v0 = lui(0xFFFF);
                        a0 = v0 | 0xFF;
                        v0 = v1 & a0;
                        v0 = v0 | 0x3300;
                        sw(v0, a1, 80);
                        lw(v1, s0, 76);
                        lw(v0, v1, 80);
                        v0 = v0 & a0;
                        v0 = v0 | 0x3300;
                        sw(v0, v1, 80);
                        lw(a0, s0, 32);
                        a1 = 0;
                        lw(a2, s0, 76);
                        jal(ctx, 0x118CD8u, gen::fn_sub_1105D0_001105d0);
                        lw(a0, s0, 32);
                        a1 = 1;
                        lw(a2, s0, 72);
                        jal(ctx, 0x118CECu, gen::fn_sub_1105D0_001105d0);
                        lw(a1, s0, 80);
                        lw(v1, a1, 80);
                        v0 = lui(0xFFFF);
                        a0 = v0 | 0xFF;
                        v0 = v1 & a0;
                        v0 = v0 | 0x3300;
                        sw(v0, a1, 80);
                        lw(v1, s0, 84);
                        lw(v0, v1, 80);
                        v0 = v0 & a0;
                        v0 = v0 | 0x3300;
                        sw(v0, v1, 80);
                        lw(a0, s0, 36);
                        a1 = 0;
                        lw(a2, s0, 84);
                        jal(ctx, 0x118D30u, gen::fn_sub_1105D0_001105d0);
                        lw(a0, s0, 36);
                        a1 = 1;
                        lw(a2, s0, 80);
                        jal(ctx, 0x118D44u, gen::fn_sub_1105D0_001105d0);
                    } else {
                        // 0x00118b10
                        charge(ctx, 3);
                        v0 = 1;
                        if (v1 == v0) {
                            // 0x00118b8c
                            charge(ctx, 46);
                            lw(a1, s0, 64);
                            lw(v1, a1, 80);
                            v0 = lui(0xFFFF);
                            a0 = v0 | 0xFF;
                            v0 = v1 & a0;
                            v0 = v0 | 0x3300;
                            sw(v0, a1, 80);
                            lw(v1, s0, 68);
                            lw(v0, v1, 80);
                            v0 = v0 & a0;
                            v0 = v0 | 0x3300;
                            sw(v0, v1, 80);
                            lw(a0, s0, 28);
                            a1 = 0;
                            lw(a2, s0, 68);
                            jal(ctx, 0x118BC8u, gen::fn_sub_1105D0_001105d0);
                            lw(a0, s0, 28);
                            a1 = 1;
                            lw(a2, s0, 64);
                            jal(ctx, 0x118BDCu, gen::fn_sub_1105D0_001105d0);
                            lw(a1, s0, 72);
                            lw(v1, a1, 80);
                            v0 = lui(0xFFFF);
                            a0 = v0 | 0xFF;
                            v0 = v1 & a0;
                            v0 = v0 | 0x3300;
                            sw(v0, a1, 80);
                            lw(v1, s0, 76);
                            lw(v0, v1, 80);
                            v0 = v0 & a0;
                            v0 = v0 | 0x3300;
                            sw(v0, v1, 80);
                            lw(a0, s0, 32);
                            a1 = 0;
                            lw(a2, s0, 76);
                            jal(ctx, 0x118C20u, gen::fn_sub_1105D0_001105d0);
                            lw(a0, s0, 32);
                            a1 = 1;
                            lw(a2, s0, 72);
                            jal(ctx, 0x118C34u, gen::fn_sub_1105D0_001105d0);
                        } else {
                            // 0x00118b1c
                            charge(ctx, 2);
                            if (v1 == 0) {
                                // 0x00118b2c
                                charge(ctx, 24);
                                lw(a1, s0, 64);
                                lw(v1, a1, 80);
                                v0 = lui(0xFFFF);
                                a0 = v0 | 0xFF;
                                v0 = v1 & a0;
                                v0 = v0 | 0x3300;
                                sw(v0, a1, 80);
                                lw(v1, s0, 68);
                                lw(v0, v1, 80);
                                v0 = v0 & a0;
                                v0 = v0 | 0x3300;
                                sw(v0, v1, 80);
                                lw(a0, s0, 28);
                                a1 = 0;
                                lw(a2, s0, 68);
                                jal(ctx, 0x118B68u, gen::fn_sub_1105D0_001105d0);
                                lw(a0, s0, 28);
                                a1 = 1;
                                lw(a2, s0, 64);
                                jal(ctx, 0x118B7Cu, gen::fn_sub_1105D0_001105d0);
                            } else {
                                // 0x00118b24
                                charge(ctx, 2);
                            }
                        }
                    }
                    // 0x00118d4c
                    charge(ctx, 4);
                    v0 = 3;
                    sw(v0, s0, 0);
                }
            }
            goto L_0011918c;
        case 0x118D5Cu:  // table[4]
            // 0x00118d5c
            charge(ctx, 4);
            lw(v1, s0, 4);
            v0 = 2;
            if (v1 == v0) {
                // 0x00118dbc
                charge(ctx, 9);
                lw(a0, s0, 28);
                jal(ctx, 0x118DC0u, gen::fn_sub_1104D0_001104d0);
                lw(a0, s0, 32);
                jal(ctx, 0x118DCCu, gen::fn_sub_1104D0_001104d0);
                lw(a0, s0, 36);
                jal(ctx, 0x118DD8u, gen::fn_sub_1104D0_001104d0);
            } else {
                // 0x00118d6c
                charge(ctx, 3);
                v0 = 1;
                if (v1 == v0) {
                    // 0x00118d9c
                    charge(ctx, 8);
                    lw(a0, s0, 28);
                    jal(ctx, 0x118DA0u, gen::fn_sub_1104D0_001104d0);
                    lw(a0, s0, 32);
                    jal(ctx, 0x118DACu, gen::fn_sub_1104D0_001104d0);
                } else {
                    // 0x00118d78
                    charge(ctx, 2);
                    if (v1 == 0) {
                        // 0x00118d88
                        charge(ctx, 5);
                        lw(a0, s0, 28);
                        jal(ctx, 0x118D8Cu, gen::fn_sub_1104D0_001104d0);
                    } else {
                        // 0x00118d80
                        charge(ctx, 2);
                    }
                }
            }
            // 0x00118de0
            charge(ctx, 12);
            lw(a0, s0, 20);
            jal(ctx, 0x118DE4u, gen::fn_sub_111530_00111530);
            a0 = s4;
            lw(a1, s0, 4);
            lw(a2, s0, 2028);
            jal(ctx, 0x118DF8u, gen::fn_sub_119960_00119960);
            v0 = 5;
            sw(v0, s0, 0);
            goto L_0011918c;
        case 0x118E10u:  // table[5]
            // 0x00118e10
            charge(ctx, 4);
            lw(v1, s0, 276);
            v0 = slti(v1, 10);
            if (v0 == 0) {
                // 0x00118e20
                charge(ctx, 4);
                v1 = addiu(v1, -10);
                at = slti(v1, 30);
                if (at != 0) {
                    // 0x00118e30
                    charge(ctx, 5);
                    v0 = 0x42C80000;
                    mtc1(v0, f12);
                    at = slti(v1, 5);
                    if (at == 0) {
                        // 0x00118e60
                        charge(ctx, 1);
                        v1 = 255;
                    } else {
                        // 0x00118e44
                        charge(ctx, 7);
                        v0 = sll(v1, 8);
                        v1 = subu(v0, v1);
                        v0 = 5;
                        div(v1, v0);
                        mflo(v1);
                    }
                    // 0x00118e64
                    charge(ctx, 12);
                    v0 = 0xF390000;
                    v0 = v0 | 0x5600;
                    a0 = v1 | v0;
                    mtc1(zero, f13);
                    mov_s(f14, f13);
                    a1 = 640;
                    a2 = 448;
                    jal(ctx, 0x118E84u, gen::fn_sub_113A30_00113a30);
                    goto L_001190f4;
                }
                // 0x00118e94
                charge(ctx, 4);
                v1 = addiu(v1, -30);
                at = slti(v1, 41);
                if (at != 0) {
                    // 0x00118eb0
                    charge(ctx, 11);
                    v0 = sll(v1, 4);
                    v1 = subu(v0, v1);
                    v0 = sll(v1, 2);
                    v0 = subu(v0, v1);
                    v1 = sll(v0, 3);
                    v0 = 10;
                    div(v1, v0);
                    mflo(s1);
                    s2 = 0;
                    for (;;) {
                        // 0x001190e8
                        charge(ctx, 3);
                        v0 = slti(s2, 24);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x00118edc
                        charge(ctx, 103);
                        v0 = sll(s2, 2);
                        v1 = addu(v0, s2);
                        v0 = sll(v1, 2);
                        v0 = addu(v1, v0);
                        v0 = sll(v0, 4);
                        a0 = 24;
                        div(v0, a0);
                        mflo(v0);
                        mtc1(v0, f0);
                        cvt_s_w(f1, f0);
                        v1 = addiu(s2, 1);
                        v0 = sll(v1, 2);
                        v1 = addu(v0, v1);
                        v0 = sll(v1, 2);
                        v0 = addu(v1, v0);
                        v0 = sll(v0, 4);
                        div1(v0, a0);
                        mflo1(v0);
                        mtc1(v0, f0);
                        cvt_s_w(f3, f0);
                        lwc1(f2, gp, fx::kGpPerEfect2Float);  // 0x7CAF38
                        mul_s(f0, f2, f1);
                        v0 = 0x43340000;
                        mtc1(v0, f1);
                        div_s(f21, f0, f1);
                        mul_s(f0, f2, f3);
                        div_s(f20, f0, f1);
                        mov_s(f12, f21);
                        jal(ctx, 0x118F60u, gen::fn_cosf_0052e6d8);
                        v0 = 0x447A0000;
                        mtc1(v0, f1);
                        mul_s(f0, f1, f0);
                        swc1(f0, sp, 0xA0);
                        mov_s(f12, f21);
                        jal(ctx, 0x118F80u, gen::fn_sinf_0052e878);
                        v0 = 0x447A0000;
                        mtc1(v0, f1);
                        mul_s(f0, f1, f0);
                        swc1(f0, sp, 0xA4);
                        mov_s(f12, f20);
                        jal(ctx, 0x118FA0u, gen::fn_cosf_0052e6d8);
                        v0 = 0x447A0000;
                        mtc1(v0, f1);
                        mul_s(f0, f1, f0);
                        swc1(f0, sp, 0xA8);
                        mov_s(f12, f20);
                        jal(ctx, 0x118FC0u, gen::fn_sinf_0052e878);
                        v0 = 0x447A0000;
                        mtc1(v0, f1);
                        mul_s(f0, f1, f0);
                        swc1(f0, sp, 0xAC);
                        mov_s(f12, f21);
                        jal(ctx, 0x118FE0u, gen::fn_cosf_0052e6d8);
                        mtc1(s1, f1);
                        cvt_s_w(f1, f1);
                        mul_s(f0, f1, f0);
                        swc1(f0, sp, 0xB0);
                        mov_s(f12, f21);
                        jal(ctx, 0x119000u, gen::fn_sinf_0052e878);
                        mtc1(s1, f1);
                        cvt_s_w(f1, f1);
                        mul_s(f0, f1, f0);
                        swc1(f0, sp, 0xB4);
                        mov_s(f12, f20);
                        jal(ctx, 0x119020u, gen::fn_cosf_0052e6d8);
                        mtc1(s1, f1);
                        cvt_s_w(f1, f1);
                        mul_s(f0, f1, f0);
                        swc1(f0, sp, 0xB8);
                        mov_s(f12, f20);
                        jal(ctx, 0x119040u, gen::fn_sinf_0052e878);
                        mtc1(s1, f1);
                        cvt_s_w(f1, f1);
                        mul_s(f0, f1, f0);
                        swc1(f0, sp, 0xBC);
                        v1 = 0;
                        v0 = 0x43A00000;
                        mtc1(v0, f2);
                        v0 = 0x43600000;
                        mtc1(v0, f1);
                        for (;;) {
                            // 0x001190a0
                            charge(ctx, 3);
                            v0 = slti(v1, 4);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x00119078
                            charge(ctx, 10);
                            v0 = sll(v1, 3);
                            v0 = addu(v0, sp);
                            v0 = addiu(v0, 160);
                            lwc1(f0, v0, 0);
                            add_s(f0, f0, f2);
                            swc1(f0, v0, 0);
                            lwc1(f0, v0, 4);
                            add_s(f0, f0, f1);
                            swc1(f0, v0, 4);
                            v1 = addiu(v1, 1);
                        }
                        // 0x001190ac
                        charge(ctx, 15);
                        t1 = 255;
                        sd(t1, sp, 0x0);
                        v0 = 0x42C80000;
                        mtc1(v0, f12);
                        v0 = 0xF390000;
                        a0 = v0 | 0x56FF;
                        ld(a1, sp, 0xA0);
                        ld(a2, sp, 0xA8);
                        ld(a3, sp, 0xB0);
                        ld(t0, sp, 0xB8);
                        t2 = t1;
                        t3 = t1;
                        jal(ctx, 0x1190DCu, gen::fn_sub_115350_00115350);
                        s2 = addiu(s2, 1);
                    }
                    goto L_001190f4;
                }
                // 0x00118ea4
                charge(ctx, 3);
                v0 = si(-1);
                break;
            }
        L_001190f4:
            charge(ctx, 6);
            lw(v0, s0, 276);
            v0 = addiu(v0, 1);
            sw(v0, s0, 276);
            s1 = 0;
            for (;;) {
                // 0x0011912c
                charge(ctx, 3);
                v0 = slti(s1, 3);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0011910c
                charge(ctx, 5);
                v0 = sll(s1, 2);
                v0 = addu(s0, v0);
                lw(a0, v0, 28);
                if (a0 != 0) {
                    // 0x00119120
                    charge(ctx, 2);
                    jal(ctx, 0x119120u, gen::fn_sub_110510_00110510);
                }
                // 0x00119128
                charge(ctx, 1);
                s1 = addiu(s1, 1);
            }
            // 0x00119138
            charge(ctx, 5);
            lw(v1, s0, 276);
            lw(v0, s0, 264);
            v0 = slt(v1, v0);
            if (v0 == 0) {
                // 0x0011914c
                charge(ctx, 3);
                s2 = 0;
                for (;;) {
                    // 0x00119180
                    charge(ctx, 3);
                    v0 = slti(s2, 3);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00119158
                    charge(ctx, 6);
                    v0 = sll(s2, 2);
                    v0 = addu(s0, v0);
                    s1 = addiu(v0, 28);
                    lw(a0, v0, 28);
                    if (a0 != 0) {
                        // 0x00119170
                        charge(ctx, 3);
                        jal(ctx, 0x119170u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                        sw(zero, s1, 0);
                    }
                    // 0x0011917c
                    charge(ctx, 1);
                    s2 = addiu(s2, 1);
                }
            }
            goto L_0011918c;
        case 0x11918Cu:  // table[3]
            goto L_0011918c;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x00119190 (the shared epilogue, written out on this path)
        charge(ctx, 12);
        ld(ra, sp, 0x90);
        lq(s5, sp, 0x80);
        lq(s4, sp, 0x70);
        lq(s3, sp, 0x60);
        lq(s2, sp, 0x50);
        lq(s1, sp, 0x40);
        lq(s0, sp, 0x30);
        lwc1(f21, sp, 0x24);
        lwc1(f20, sp, 0x20);
        sp = addiu(sp, 0x1E0);
        return;
    }
    goto L_0011918c;
L_00117bb8_53:
    charge(ctx, 5);
    lw(v0, a2, 0);
    v0 = addiu(v0, -1);
    sw(v0, a2, 0);
    goto L_00117bf0;
}

// 0x001191C0 sub_1191C0 -- 232 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_PerEfect2_Destroy] Destroy callback of "H_PerEfect2Draw": removes the archive, frees the sprite file, drops the
// nine requests, destroys the six rasters and frees the work.
void sub_1191C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001191c0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    lw(a0, s0, 564);
    if (a0 != 0) {
        // 0x001191e4
        charge(ctx, 2);
        jal(ctx, 0x1191E4u, gen::fn_H_Cdvd_CacheRemove_00102870);
    }
    // 0x001191ec
    charge(ctx, 6);
    lw(a0, s0, 2028);
    jal(ctx, 0x1191F0u, gen::fn_sub_1124B0_001124b0);
    s2 = 0;
    for (;;) {
        // 0x0011922c
        charge(ctx, 3);
        v0 = slti(s2, 9);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00119204
        charge(ctx, 6);
        v0 = sll(s2, 2);
        v0 = addu(s0, v0);
        s1 = addiu(v0, 88);
        lw(a0, v0, 88);
        if (a0 != 0) {
            // 0x0011921c
            charge(ctx, 3);
            jal(ctx, 0x11921Cu, gen::fn_H_Cdvd_Destroy_00100ec0);
            sw(zero, s1, 0);
        }
        // 0x00119228
        charge(ctx, 1);
        s2 = addiu(s2, 1);
    }
    // 0x00119238
    charge(ctx, 3);
    s2 = 0;
    for (;;) {
        // 0x0011926c
        charge(ctx, 3);
        v0 = slti(s2, 6);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00119244
        charge(ctx, 6);
        v0 = sll(s2, 2);
        v0 = addu(s0, v0);
        s1 = addiu(v0, 64);
        lw(a0, v0, 64);
        if (a0 != 0) {
            // 0x0011925c
            charge(ctx, 3);
            jal(ctx, 0x11925Cu, gen::fn_sub_4D0F00_004d0f00);
            sw(zero, s1, 0);
        }
        // 0x00119268
        charge(ctx, 1);
        s2 = addiu(s2, 1);
    }
    // 0x00119278
    charge(ctx, 12);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, rw::kFree);  // 0x96017C
    jalr(ctx, 0x119284u, v0.u());
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x001192B0 sub_1192B0 -- 196 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_PerEfect2_Create] Creates "H_PerEfect2Draw" (RwCalloc 0x834, priority 6335); the three persona ids from
// $a1[0..2] to +8..+0x10.
void sub_1192B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001192b0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    a0 = 1;
    a1 = 2100;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, rw::kCalloc);  // 0x960184
    jalr(ctx, 0x1192E0u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x00119300
        charge(ctx, 13);
        a0 = s2;
        a1 = 0x5D0000;
        a1 = addiu(a1, 28624);  // "H_PerEfect2Draw"
        a2 = 6335;
        a3 = 0x110000;
        a3 = addiu(a3, 30016);  // &sub_117540
        t0 = 0x120000;
        t0 = addiu(t0, -28224);  // &sub_1191C0
        t1 = s0;
        jal(ctx, 0x119324u, gen::fn_kwlnTaskCreate_00194b20);
        if (v0 != 0) {
            // 0x00119340
            charge(ctx, 6);
            lw(v1, s1, 0);
            sw(v1, s0, 8);
            lw(v1, s1, 4);
            sw(v1, s0, 12);
            lw(v1, s1, 8);
            sw(v1, s0, 16);
        } else {
            // 0x00119334
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x001192f4
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00119358 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00119380 sub_119380 -- 24 bytes; leaf frame (no stack)
// [H_PerEfect2_IsReady] Effect 2 work state == 3.
void sub_119380(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00119380
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v0, a0, task::kWork);
    lw(v0, v0, 0);
    v0 = v0 ^ 0x3;
    v0 = sltiu(v0, 1);
}

// 0x001193A0 sub_1193A0 -- 20 bytes; leaf frame (no stack)
// [H_PerEfect2_Start] Effect 2 work state = 4.
void sub_1193A0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x001193a0
    enter(ctx, 5);  // entry check point + this block's cycles
    a1 = 4;
    lw(v1, a0, task::kWork);
    sw(a1, v1, 0);
}

// 0x001193C0 sub_1193C0 -- 12 bytes; leaf frame (no stack)
// [H_PerEfect2_GetLength] Returns 40.
void sub_1193C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x001193c0
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 40;
}

// 0x001193D0 sub_1193D0 -- 1364 bytes; frame 0x70: ra sp+0x50, s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq)
// [H_sMark2Spr_Update] Update of "H_sMark2SprDraw": the second mark sprite's zoom-in (12.4 scale 13516 -> 4096 on the
// eased path), a 3-frame and a 2-frame bounce, then the hold and the slide out; one handle drawn and freed per frame.
// Returns -1 at the end.
void sub_1193D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x001193d0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    lw(s1, a0, task::kWork);
    lw(a1, s1, 0);
    a0 = 4;
    if (a1 != a0) {
        // 0x001193fc
        charge(ctx, 3);
        v0 = 3;
        if (a1 == v0) {
            // 0x0011977c
            charge(ctx, 44);
            lw(v0, s1, 8);
            s0 = addiu(v0, 1);
            sw(s0, s1, 8);
            s3 = addiu(s1, 16);
            a0 = 0;
            lw(a1, s1, 84);
            a2 = 0;
            jal(ctx, 0x119798u, gen::fn_sprCreateHandle_001158b0);
            s2 = v0;
            lwc1(f0, s3, 36);
            swc1(f0, v0, 44);
            lwc1(f0, s3, 56);
            swc1(f0, v0, 16);
            lwc1(f0, s3, 60);
            swc1(f0, v0, 20);
            v1 = 16;
            sh(v1, v0, 36);
            v1 = 96;
            sh(v1, v0, 38);
            v1 = sll(s0, 2);
            v1 = addu(v1, s0);
            a0 = sll(v1, 1);
            v1 = 3;
            div(a0, v1);
            mflo(a0);
            v1 = 10;
            v1 = subu(v1, a0);
            mtc1(v1, f0);
            cvt_s_w(f0, f0);
            swc1(f0, v0, 32);
            sb(zero, v0, 24);
            a0 = s2;
            a1 = 1;
            jal(ctx, 0x119808u, gen::fn_sub_1127D0_001127d0);
            a0 = s2;
            jal(ctx, 0x119814u, gen::fn_sub_115980_00115980);
            lw(v1, s1, 8);
            v0 = 2;
            if (v1 == v0) {
                // 0x0011982c
                charge(ctx, 5);
                sw(zero, s1, 8);
                v0 = 4;
                sw(v0, s1, 0);
            }
        } else {
            // 0x00119408
            charge(ctx, 3);
            a2 = 2;
            if (a1 == a2) {
                // 0x001196c0
                charge(ctx, 43);
                lw(v0, s1, 8);
                s0 = addiu(v0, 1);
                sw(s0, s1, 8);
                s3 = addiu(s1, 16);
                a0 = 0;
                lw(a1, s1, 84);
                a2 = 0;
                jal(ctx, 0x1196DCu, gen::fn_sprCreateHandle_001158b0);
                s2 = v0;
                lwc1(f0, s3, 36);
                swc1(f0, v0, 44);
                lwc1(f0, s3, 56);
                swc1(f0, v0, 16);
                lwc1(f0, s3, 60);
                swc1(f0, v0, 20);
                v1 = 16;
                sh(v1, v0, 36);
                v1 = 96;
                sh(v1, v0, 38);
                v1 = sll(s0, 4);
                v1 = subu(v1, s0);
                a0 = sll(v1, 1);
                v1 = 3;
                div(a0, v1);
                mflo(v1);
                v1 = addiu(v1, -20);
                mtc1(v1, f0);
                cvt_s_w(f0, f0);
                swc1(f0, v0, 32);
                sb(zero, v0, 24);
                a0 = s2;
                a1 = 1;
                jal(ctx, 0x119748u, gen::fn_sub_1127D0_001127d0);
                a0 = s2;
                jal(ctx, 0x119754u, gen::fn_sub_115980_00115980);
                lw(v1, s1, 8);
                v0 = 3;
                if (v1 == v0) {
                    // 0x0011976c
                    charge(ctx, 4);
                    sw(zero, s1, 8);
                    sw(v0, s1, 0);
                }
            } else {
                // 0x00119414
                charge(ctx, 3);
                v1 = 1;
                if (a1 == v1) {
                    // 0x00119584
                    charge(ctx, 5);
                    a0 = addiu(s1, 16);
                    jal(ctx, 0x119588u, gen::fn_sub_18B700_0018b700);
                    if (v0 != 0) {
                        // 0x00119598
                        charge(ctx, 32);
                        s0 = addiu(s1, 16);
                        a0 = 0;
                        lw(a1, s1, 84);
                        a2 = 0;
                        jal(ctx, 0x1195A8u, gen::fn_sprCreateHandle_001158b0);
                        s2 = v0;
                        lwc1(f0, s0, 36);
                        swc1(f0, v0, 44);
                        lwc1(f0, s0, 56);
                        swc1(f0, v0, 16);
                        lwc1(f0, s0, 60);
                        swc1(f0, v0, 20);
                        lw(a1, s0, 28);
                        lw(v1, s0, 24);
                        v1 = subu(v1, a1);
                        lw(a0, s0, 32);
                        a1 = subu(a0, a1);
                        a0 = 9420;
                        mult(a0, v1, a0);
                        div(a0, a1);
                        mflo(a1);
                        a0 = 13516;
                        a1 = subu(a0, a1);
                        sh(a1, v0, 40);
                        sh(a1, v0, 42);
                        a0 = sll(a1, 4);
                        v0 = sra(a0, 12);
                        if (i64(a0) < 0) {
                            // 0x00119618
                            charge(ctx, 2);
                            v0 = addiu(a0, 4095);
                            v0 = sra(v0, 12);
                        }
                        // 0x00119620
                        charge(ctx, 7);
                        sh(v0, s2, 36);
                        v0 = sll(a1, 1);
                        v0 = addu(v0, a1);
                        a0 = sll(v0, 5);
                        v0 = sra(a0, 12);
                        if (i64(a0) < 0) {
                            // 0x0011963c
                            charge(ctx, 2);
                            v0 = addiu(a0, 4095);
                            v0 = sra(v0, 12);
                        }
                        // 0x00119644
                        charge(ctx, 26);
                        sh(v0, s2, 38);
                        lw(a0, s0, 32);
                        lw(v0, s0, 28);
                        a0 = subu(a0, v0);
                        v0 = sll(v1, 4);
                        v0 = subu(v0, v1);
                        v0 = sll(v0, 1);
                        div(v0, a0);
                        mflo(v0);
                        v0 = addiu(v0, -50);
                        mtc1(v0, f0);
                        cvt_s_w(f0, f0);
                        swc1(f0, s2, 32);
                        sb(zero, s2, 24);
                        a0 = s2;
                        a1 = 1;
                        jal(ctx, 0x119688u, gen::fn_sub_1127D0_001127d0);
                        a0 = s2;
                        jal(ctx, 0x119694u, gen::fn_sub_115980_00115980);
                        lw(v1, s0, 32);
                        lw(v0, s0, 24);
                        if (v1 == v0) {
                            // 0x001196ac
                            charge(ctx, 5);
                            sw(zero, s1, 8);
                            v0 = 2;
                            sw(v0, s1, 0);
                        }
                    }
                } else {
                    // 0x00119420
                    charge(ctx, 2);
                    if (a1 == 0) {
                        // 0x00119430
                        charge(ctx, 3);
                        lw(v0, s1, 4);
                        if (v0 == a2) {
                            // 0x00119518
                            charge(ctx, 23);
                            v0 = 0x43280000;
                            sw(v0, sp, 0x68);
                            v0 = lui(0xC298);
                            sw(v0, sp, 0x6C);
                            v0 = 0x43840000;
                            sw(v0, sp, 0x60);
                            v0 = 0x430D0000;
                            sw(v0, sp, 0x64);
                            v0 = 13;
                            sd(v0, sp, 0x0);
                            v0 = 15;
                            sd(v0, sp, 0x8);
                            v0 = 0x42C80000;
                            mtc1(v0, f12);
                            a0 = addiu(s1, 16);
                            a1 = 0;
                            a3 = 0;
                            ld(t0, sp, 0x68);
                            ld(t1, sp, 0x60);
                            t2 = 0;
                            t3 = 0;
                            jal(ctx, 0x11956Cu, gen::fn_sub_18BC10_0018bc10);
                        } else {
                            // 0x0011943c
                            charge(ctx, 2);
                            if (v0 == v1) {
                                // 0x001194b4
                                charge(ctx, 25);
                                v0 = 0x42A80000;
                                sw(v0, sp, 0x68);
                                v0 = lui(0xC31E);
                                sw(v0, sp, 0x6C);
                                v0 = 0x43630000;
                                sw(v0, sp, 0x60);
                                v0 = 0x42980000;
                                sw(v0, sp, 0x64);
                                v0 = 8;
                                sd(v0, sp, 0x0);
                                v0 = 10;
                                sd(v0, sp, 0x8);
                                v0 = 0x42C80000;
                                mtc1(v0, f12);
                                a0 = addiu(s1, 16);
                                a1 = 0;
                                a3 = 0;
                                ld(t0, sp, 0x68);
                                ld(t1, sp, 0x60);
                                t2 = 0;
                                t3 = 0;
                                jal(ctx, 0x119508u, gen::fn_sub_18BC10_0018bc10);
                            } else {
                                // 0x00119444
                                charge(ctx, 2);
                                if (v0 == 0) {
                                    // 0x00119454
                                    charge(ctx, 24);
                                    v0 = 0x43280000;
                                    sw(v0, sp, 0x68);
                                    v0 = lui(0xC298);
                                    sw(v0, sp, 0x6C);
                                    v0 = 0x43840000;
                                    sw(v0, sp, 0x60);
                                    v0 = 0x430D0000;
                                    sw(v0, sp, 0x64);
                                    sd(a0, sp, 0x0);
                                    v0 = 8;
                                    sd(v0, sp, 0x8);
                                    v0 = 0x42C80000;
                                    mtc1(v0, f12);
                                    a0 = addiu(s1, 16);
                                    a1 = 0;
                                    a3 = 0;
                                    ld(t0, sp, 0x68);
                                    ld(t1, sp, 0x60);
                                    t2 = 0;
                                    t3 = 0;
                                    jal(ctx, 0x1194A4u, gen::fn_sub_18BC10_0018bc10);
                                } else {
                                    // 0x0011944c
                                    charge(ctx, 2);
                                }
                            }
                        }
                        // 0x00119574
                        charge(ctx, 4);
                        v0 = 1;
                        sw(v0, s1, 0);
                    } else {
                        // 0x00119428
                        charge(ctx, 2);
                    }
                }
            }
        }
        goto L_00119900;
    }
    // 0x00119840
    charge(ctx, 24);
    lw(v0, s1, 8);
    v0 = addiu(v0, 1);
    sw(v0, s1, 8);
    s2 = addiu(s1, 16);
    a0 = 0;
    lw(a1, s1, 84);
    a2 = 0;
    jal(ctx, 0x11985Cu, gen::fn_sprCreateHandle_001158b0);
    s0 = v0;
    lwc1(f0, s2, 36);
    swc1(f0, v0, 44);
    lwc1(f0, s2, 56);
    swc1(f0, v0, 16);
    lwc1(f0, s2, 60);
    swc1(f0, v0, 20);
    v1 = 16;
    sh(v1, v0, 36);
    v1 = 96;
    sh(v1, v0, 38);
    lw(v0, s1, 8);
    at = slti(v0, 15);
    if (at == 0) {
        // 0x001198ac
        charge(ctx, 7);
        v1 = addiu(v0, -15);
        v0 = sll(v1, 8);
        v1 = subu(v0, v1);
        v0 = 3;
        div(v1, v0);
        mflo(v0);
        sb(v0, s0, 24);
    } else {
        // 0x001198a0
        charge(ctx, 3);
        sb(zero, s0, 24);
    }
    // 0x001198c8
    charge(ctx, 11);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x1198D0u, gen::fn_sub_1127D0_001127d0);
    a0 = s0;
    jal(ctx, 0x1198DCu, gen::fn_sub_115980_00115980);
    lw(v1, s1, 8);
    v0 = 18;
    if (v1 != v0) {
    L_00119900:
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x001198f4
        charge(ctx, 3);
        v0 = si(-1);
    }
    // 0x00119904 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0x70);
}

// 0x00119930 sub_119930 -- 44 bytes; frame 0x10: ra sp+0x0
// [H_sMark2Spr_Destroy] Destroy callback of "H_sMark2SprDraw": frees the work.
void sub_119930(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00119930
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, task::kWork);
    v0 = 0x960000;
    lw(v0, v0, rw::kFree);  // 0x96017C
    jalr(ctx, 0x119944u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00119960 sub_119960 -- 192 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_sMark2Spr_Create] Creates "H_sMark2SprDraw" (RwCalloc 0x58, priority 6337); +4 = $a1, sprite file +0x54 = $a2.
void sub_119960(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00119960
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
    a1 = 88;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, rw::kCalloc);  // 0x960184
    jalr(ctx, 0x119998u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x001199b8
        charge(ctx, 13);
        a0 = s3;
        a1 = 0x5D0000;
        a1 = addiu(a1, 28640);  // "H_sMark2SprDraw"
        a2 = 6337;
        a3 = 0x120000;
        a3 = addiu(a3, -27696);  // &sub_1193D0
        t0 = 0x120000;
        t0 = addiu(t0, -26320);  // &sub_119930
        t1 = s0;
        jal(ctx, 0x1199DCu, gen::fn_kwlnTaskCreate_00194b20);
        if (v0 != 0) {
            // 0x001199f8
            charge(ctx, 2);
            sw(s1, s0, 84);
            sw(s2, s0, 4);
        } else {
            // 0x001199ec
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x001199ac
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00119a00 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x003AE000 sub_3AE000 -- 320 bytes; frame 0x40: ra sp+0x10, s0 sp+0x0 (sq)
// [frTagPlayVoiceByWeekday] Tag handler (code, layout): parameter p0; records it for today's weekday (sub_16E2B0 on
// the sub_16DD40 record) and, for p0 != 0, plays the sound sub_10A4E0(0, 0, 4, id) whose id is picked from the three
// thresholds 0x6A2640.. / ids 0x6A2650.. by p0. Returns 0.
void sub_3AE000(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x003ae000
    enter(ctx, 31);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    v0 = 0x6A0000;
    lwc1(f2, v0, fnt::kLoVoiceThresholds);  // 0x6A2640
    v0 = 0x6A0000;
    lwc1(f1, v0, fnt::kLoVoiceThresholds1);  // 0x6A2644
    v0 = 0x6A0000;
    lwc1(f0, v0, fnt::kLoVoiceThresholds2);  // 0x6A2648
    swc1(f2, sp, 0x30);
    swc1(f1, sp, 0x34);
    swc1(f0, sp, 0x38);
    v0 = 0x6A0000;
    lwc1(f2, v0, fnt::kLoVoiceIds);  // 0x6A2650
    v0 = 0x6A0000;
    lwc1(f1, v0, fnt::kLoVoiceIds1);  // 0x6A2654
    v0 = 0x6A0000;
    lwc1(f0, v0, fnt::kLoVoiceIds2);  // 0x6A2658
    swc1(f2, sp, 0x20);
    swc1(f1, sp, 0x24);
    swc1(f0, sp, 0x28);
    lw(v1, a1, lay::kPos);
    lw(v0, a1, lay::kText);
    v1 = addu(v0, v1);
    lbu(v0, v1, 0);
    v0 = addiu(v0, -1);
    a0 = v0 & 0xFF;
    lbu(v1, v1, 1);
    v0 = 255;
    if (v1 != v0) {
        // 0x003ae088
        charge(ctx, 2);
        v0 = addiu(v1, -1);
        v0 = v0 & 0xFF;
    } else {
        // 0x003ae07c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003ae090
    charge(ctx, 14);
    v0 = v0 & 0xFF;
    v1 = sll(v0, 8);
    v0 = a0 & 0xFF;
    s0 = v1 | v0;
    jal(ctx, 0x3AE0A0u, gen::fn_clndGetCurrentWeekDay_0017db00);
    jal(ctx, 0x3AE0A8u, gen::fn_sub_16DD40_0016dd40);
    a0 = v0;
    a1 = s0;
    jal(ctx, 0x3AE0B8u, gen::fn_sub_16E2B0_0016e2b0);
    if (s0 != 0) {
        // 0x003ae0d4
        charge(ctx, 3);
        v1 = 0;
        for (;;) {
            // 0x003ae0fc
            charge(ctx, 3);
            v0 = sltiu(v1, 3);
            if (v0 != 0) {
                backedge(ctx);
                // 0x003ae0e0
                charge(ctx, 6);
                v0 = sll(v1, 2);
                v0 = addu(v0, sp);
                lw(v0, v0, 48);
                at = slt(v0, s0);
                if (at != 0) {
                    // 0x003ae0f8
                    charge(ctx, 1);
                    v1 = addiu(v1, 1);
                    continue;
                }
            }
            break;
        }
        // 0x003ae108
        charge(ctx, 9);
        v0 = sll(v1, 2);
        v0 = addu(v0, sp);
        lh(a3, v0, 32);
        a0 = 0;
        a1 = 0;
        a2 = 4;
        jal(ctx, 0x3AE120u, gen::fn_sub_10A4E0_0010a4e0);
        v0 = 0;
    } else {
        // 0x003ae0c8
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003ae12c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003AE420 sub_3AE420 -- 312 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [frTagSetCommuRank] Tag handler: parameters (p0 < 8, p1 < 4; K_Assert frTagTable.c 721 / 722) -> sub_17C7F0(p0,
// p1). Returns 0.
void sub_3AE420(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ae420
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a1, lay::kPos);
    lw(v0, a1, lay::kText);
    v1 = addu(v0, v1);
    lbu(v0, v1, 0);
    v0 = addiu(v0, -1);
    a0 = v0 & 0xFF;
    lbu(v1, v1, 1);
    v0 = 255;
    if (v1 != v0) {
        // 0x003ae464
        charge(ctx, 2);
        v0 = addiu(v1, -1);
        v0 = v0 & 0xFF;
    } else {
        // 0x003ae458
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003ae46c
    charge(ctx, 14);
    v0 = v0 & 0xFF;
    v1 = sll(v0, 8);
    v0 = a0 & 0xFF;
    s0 = v1 | v0;
    lw(v1, a1, lay::kPos);
    lw(v0, a1, lay::kText);
    v1 = addu(v1, v0);
    lbu(v0, v1, 2);
    v0 = addiu(v0, -1);
    a0 = v0 & 0xFF;
    lbu(v1, v1, 3);
    v0 = 255;
    if (v1 != v0) {
        // 0x003ae4b0
        charge(ctx, 2);
        v0 = addiu(v1, -1);
        v0 = v0 & 0xFF;
    } else {
        // 0x003ae4a4
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003ae4b8
    charge(ctx, 8);
    v0 = v0 & 0xFF;
    v1 = sll(v0, 8);
    v0 = a0 & 0xFF;
    v0 = v1 | v0;
    s1 = dsll32(v0, 16);
    s1 = dsra32(s1, 16);
    bool bad = true;  // p0 outside [0, 8)
    if (i64(s0) >= 0) {
        // 0x003ae4d8
        charge(ctx, 3);
        v0 = slti(s0, 8);
        bad = v0 == 0;
    }
    if (bad) {
        // 0x003ae4e4: K_Assert(p0 < 8)
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 9880);  // "frTagTable.c"
        a1 = 721;
        jal(ctx, 0x3AE4F0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003ae4f8
    charge(ctx, 4);
    v0 = dsll32(s1, 16);
    v0 = dsra32(v0, 16);
    bad = true;  // p1 outside [0, 4)
    if (i64(v0) >= 0) {
        // 0x003ae508
        charge(ctx, 3);
        v0 = slti(v0, 4);
        bad = v0 == 0;
    }
    if (bad) {
        // 0x003ae514: K_Assert(p1 < 4)
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 9880);  // "frTagTable.c"
        a1 = 722;
        jal(ctx, 0x3AE520u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003ae528: sub_17C7F0(p0, p1)
    charge(ctx, 12);
    a1 = dsll32(s1, 16);
    a1 = dsra32(a1, 16);
    a0 = s0;
    jal(ctx, 0x3AE534u, gen::fn_sub_17C7F0_0017c7f0);
    v0 = 0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003AEE20 sub_3AEE20 -- 748 bytes; frame 0x70: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [frTagTestCondition] Tag handler (jump table 0x7BB1E0): tests condition p0 against value p1 -- 0..2 the three
// social stats (sub_16C6F0 / 0x16C740 / 0x16C790) < p1, 3..7 a stat of sub_1738D0 < p1, 8 / 9 sub_16C920 ==/!= p1, 10
// / 11 sub_172C50 none / some, 12..16 flag bank[p0 - 12] + p1 set, 17..21 flag bank[p0 - 17] + p1 clear (the five
// bank bases copied from 0x6A2660); a true condition sets tag flag 0x20. Returns 0.
void sub_3AEE20(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003aee20
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a1, lay::kPos);
    lw(v0, a1, lay::kText);
    v1 = addu(v0, v1);
    lbu(v0, v1, 0);
    v0 = addiu(v0, -1);
    a0 = v0 & 0xFF;
    lbu(v1, v1, 1);
    v0 = 255;
    if (v1 != v0) {
        // 0x003aee64
        charge(ctx, 2);
        v0 = addiu(v1, -1);
        v0 = v0 & 0xFF;
    } else {
        // 0x003aee58
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003aee6c
    charge(ctx, 14);
    v0 = v0 & 0xFF;
    v1 = sll(v0, 8);
    v0 = a0 & 0xFF;
    v0 = v1 | v0;
    lw(a0, a1, lay::kPos);
    lw(v1, a1, lay::kText);
    a0 = addu(a0, v1);
    lbu(v1, a0, 2);
    v1 = addiu(v1, -1);
    a1 = v1 & 0xFF;
    lbu(a0, a0, 3);
    v1 = 255;
    if (a0 != v1) {
        // 0x003aeeb0
        charge(ctx, 2);
        v1 = addiu(a0, -1);
        v1 = v1 & 0xFF;
    } else {
        // 0x003aeea4
        charge(ctx, 3);
        v1 = 0;
    }
    // 0x003aeeb8
    charge(ctx, 8);
    v1 = v1 & 0xFF;
    a0 = sll(v1, 8);
    v1 = a1 & 0xFF;
    s0 = a0 | v1;
    s1 = 0;
    at = sltiu(v0, 26);
    if (at != 0) {
        // 0x003aeed8
        charge(ctx, 7);
        a0 = 0x7C0000;
        a0 = addiu(a0, fnt::kLoJptCondition);  // &0x7BB1E0
        v1 = sll(v0, 2);
        v1 = addu(v1, a0);
        lw(v1, v1, 0);
        switch (v1.u()) {
        case 0x3AEEF4u:  // table[0]
            // 0x003aeef4
            charge(ctx, 8);
            a0 = 1;
            jal(ctx, 0x3AEEF8u, gen::fn_sub_16C6F0_0016c6f0);
            v0 = dsll32(v0, 16);
            v0 = dsra32(v0, 16);
            at = slt(v0, s0);
            if (at != 0) {
                // 0x003aef14
                charge(ctx, 3);
                s1 = 1;
            }
            break;
        case 0x3AEF20u:  // table[1]
            // 0x003aef20
            charge(ctx, 8);
            a0 = 1;
            jal(ctx, 0x3AEF24u, gen::fn_sub_16C740_0016c740);
            v0 = dsll32(v0, 16);
            v0 = dsra32(v0, 16);
            at = slt(v0, s0);
            if (at != 0) {
                // 0x003aef40
                charge(ctx, 3);
                s1 = 1;
            }
            break;
        case 0x3AEF4Cu:  // table[2]
            // 0x003aef4c
            charge(ctx, 8);
            a0 = 1;
            jal(ctx, 0x3AEF50u, gen::fn_sub_16C790_0016c790);
            v0 = dsll32(v0, 16);
            v0 = dsra32(v0, 16);
            at = slt(v0, s0);
            if (at != 0) {
                // 0x003aef6c
                charge(ctx, 3);
                s1 = 1;
            }
            break;
        case 0x3AEF78u:  // table[3, 4, 5, 6, 7]
            // 0x003aef78
            charge(ctx, 9);
            v0 = addiu(v0, -3);
            a1 = v0 & 0xFFFF;
            a0 = 1;
            jal(ctx, 0x3AEF84u, gen::fn_sub_1738D0_001738d0);
            v0 = v0 & 0xFF;
            at = slt(v0, s0);
            if (at != 0) {
                // 0x003aef9c
                charge(ctx, 3);
                s1 = 1;
            }
            break;
        case 0x3AEFA8u:  // table[8]
            // 0x003aefa8
            charge(ctx, 6);
            a0 = 1;
            jal(ctx, 0x3AEFACu, gen::fn_sub_16C920_0016c920);
            v0 = v0 & 0xFFFF;
            if (s0 == v0) {
                // 0x003aefc0
                charge(ctx, 3);
                s1 = 1;
            }
            break;
        case 0x3AEFCCu:  // table[9]
            // 0x003aefcc
            charge(ctx, 6);
            a0 = 1;
            jal(ctx, 0x3AEFD0u, gen::fn_sub_16C920_0016c920);
            v0 = v0 & 0xFFFF;
            if (s0 != v0) {
                // 0x003aefe4
                charge(ctx, 3);
                s1 = 1;
            }
            break;
        case 0x3AEFF0u:  // table[10]
            // 0x003aeff0
            charge(ctx, 5);
            a0 = addiu(sp, 0x6E);
            jal(ctx, 0x3AEFF4u, gen::fn_sub_172C50_00172c50);
            if (v0 == 0) {
                // 0x003af004
                charge(ctx, 3);
                s1 = 1;
            }
            break;
        case 0x3AF010u:  // table[11]
            // 0x003af010
            charge(ctx, 5);
            a0 = addiu(sp, 0x6C);
            jal(ctx, 0x3AF014u, gen::fn_sub_172C50_00172c50);
            if (v0 != 0) {
                // 0x003af024
                charge(ctx, 3);
                s1 = 1;
            }
            break;
        case 0x3AF030u:  // table[12, 13, 14, 15, 16]
            // 0x003af030
            charge(ctx, 4);
            a2 = 0x6A0000;
            a2 = addiu(a2, fnt::kLoCondBanks);  // &0x6A2660
            a1 = addiu(sp, 0x50);
            a0 = 5;
            for (;;) {
                // 0x003af040
                charge(ctx, 7);
                lw(v1, a2, 0);
                a2 = addiu(a2, 4);
                a0 = addiu(a0, -1);
                sw(v1, a1, 0);
                a1 = addiu(a1, 4);
                if (i64(a0) <= 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x003af05c
            charge(ctx, 9);
            v0 = sll(v0, 2);
            v0 = addu(v0, sp);
            lw(v0, v0, 32);
            a0 = addu(s0, v0);
            jal(ctx, 0x3AF06Cu, gen::fn_datGetFlag_0016f190);
            v1 = 1;
            if (v0 == v1) {
                // 0x003af080
                charge(ctx, 3);
                s1 = v1;
            }
            break;
        case 0x3AF08Cu:  // table[17, 18, 19, 20, 21]
            // 0x003af08c
            charge(ctx, 4);
            a2 = 0x6A0000;
            a2 = addiu(a2, fnt::kLoCondBanks);  // &0x6A2660
            a1 = addiu(sp, 0x30);
            a0 = 5;
            for (;;) {
                // 0x003af09c
                charge(ctx, 7);
                lw(v1, a2, 0);
                a2 = addiu(a2, 4);
                a0 = addiu(a0, -1);
                sw(v1, a1, 0);
                a1 = addiu(a1, 4);
                if (i64(a0) <= 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x003af0b8
            charge(ctx, 8);
            v0 = sll(v0, 2);
            v0 = addu(v0, sp);
            lw(v0, v0, -20);
            a0 = addu(s0, v0);
            jal(ctx, 0x3AF0C8u, gen::fn_datGetFlag_0016f190);
            if (v0 == 0) {
                // 0x003af0d8
                charge(ctx, 1);
                s1 = 1;
            }
            break;
        case 0x3AF0DCu:  // table[22, 23, 24, 25]
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
    }
    // 0x003af0dc
    charge(ctx, 2);
    if (s1 != 0) {
        // 0x003af0e4
        charge(ctx, 3);
        lw(v0, gp, fnt::kGpTagFlags);  // 0x7CD4E8
        v0 = v0 | 0x20;
        sw(v0, gp, fnt::kGpTagFlags);  // 0x7CD4E8
    }
    // 0x003af0f0 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = 0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x003AF110 sub_3AF110 -- 580 bytes; frame 0x40: ra sp+0x10, s0 sp+0x0 (sq)
// [frTagSetValue] Tag handler, only while the layout runs (default glyph flags bit 7): parameters (kind, bank, index,
// value): 0 datSetFlag(bank base 0x6A2680[bank] + index, value), 1 sub_171C40, 2 / 3 the weekday record (sub_16E2B0);
// kind 6 does nothing. Returns 0.
void sub_3AF110(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003af110
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lh(v0, gp, fnt::kGpGlyphFlags);  // 0x7CD500
    v0 = v0 & 0x80;
    if (v0 != 0) {
        // 0x003af138
        charge(ctx, 10);
        lw(v1, a1, lay::kPos);
        lw(v0, a1, lay::kText);
        v1 = addu(v0, v1);
        lbu(v0, v1, 0);
        v0 = addiu(v0, -1);
        a0 = v0 & 0xFF;
        lbu(v1, v1, 1);
        v0 = 255;
        if (v1 != v0) {
            // 0x003af16c
            charge(ctx, 2);
            v0 = addiu(v1, -1);
            v0 = v0 & 0xFF;
        } else {
            // 0x003af160
            charge(ctx, 3);
            v0 = 0;
        }
        // 0x003af174
        charge(ctx, 14);
        v0 = v0 & 0xFF;
        v1 = sll(v0, 8);
        v0 = a0 & 0xFF;
        a0 = v1 | v0;
        lw(v1, a1, lay::kPos);
        lw(v0, a1, lay::kText);
        v1 = addu(v1, v0);
        lbu(v0, v1, 2);
        v0 = addiu(v0, -1);
        a2 = v0 & 0xFF;
        lbu(v1, v1, 3);
        v0 = 255;
        if (v1 != v0) {
            // 0x003af1b8
            charge(ctx, 2);
            v0 = addiu(v1, -1);
            v0 = v0 & 0xFF;
        } else {
            // 0x003af1ac
            charge(ctx, 3);
            v0 = 0;
        }
        // 0x003af1c0
        charge(ctx, 14);
        v0 = v0 & 0xFF;
        v1 = sll(v0, 8);
        v0 = a2 & 0xFF;
        v1 = v1 | v0;
        lw(a2, a1, lay::kPos);
        lw(v0, a1, lay::kText);
        a2 = addu(a2, v0);
        lbu(v0, a2, 4);
        v0 = addiu(v0, -1);
        a3 = v0 & 0xFF;
        lbu(a2, a2, 5);
        v0 = 255;
        if (a2 != v0) {
            // 0x003af204
            charge(ctx, 2);
            v0 = addiu(a2, -1);
            v0 = v0 & 0xFF;
        } else {
            // 0x003af1f8
            charge(ctx, 3);
            v0 = 0;
        }
        // 0x003af20c
        charge(ctx, 14);
        v0 = v0 & 0xFF;
        a2 = sll(v0, 8);
        v0 = a3 & 0xFF;
        v0 = a2 | v0;
        lw(a2, a1, lay::kPos);
        lw(a1, a1, lay::kText);
        a2 = addu(a2, a1);
        lbu(a1, a2, 6);
        a1 = addiu(a1, -1);
        a3 = a1 & 0xFF;
        lbu(a2, a2, 7);
        a1 = 255;
        if (a2 != a1) {
            // 0x003af250
            charge(ctx, 2);
            a1 = addiu(a2, -1);
            a1 = a1 & 0xFF;
        } else {
            // 0x003af244
            charge(ctx, 3);
            a1 = 0;
        }
        // 0x003af258
        charge(ctx, 7);
        a1 = a1 & 0xFF;
        a2 = sll(a1, 8);
        a1 = a3 & 0xFF;
        s0 = a2 | a1;
        a1 = 6;
        if (a0 != a1) {
            // 0x003af274
            charge(ctx, 3);
            a1 = 3;
            if (a0 != a1) {
                // 0x003af280
                charge(ctx, 3);
                a1 = 2;
                if (a0 == a1) {
                    goto L_003af31c;
                }
                // 0x003af28c
                charge(ctx, 3);
                a1 = 1;
                if (a0 == a1) {
                    // 0x003af2f8
                    charge(ctx, 9);
                    jal(ctx, 0x3AF2F8u, gen::fn_sub_16DD40_0016dd40);
                    a0 = dsll32(v0, 16);
                    a0 = dsra32(a0, 16);
                    a1 = s0;
                    jal(ctx, 0x3AF30Cu, gen::fn_sub_171C40_00171c40);
                } else {
                    // 0x003af298
                    charge(ctx, 2);
                    if (a0 == 0) {
                        // 0x003af2a8
                        charge(ctx, 4);
                        a3 = 0x6A0000;
                        a3 = addiu(a3, fnt::kLoSetBanks);  // &0x6A2680
                        a2 = addiu(sp, 0x20);
                        a1 = 5;
                        for (;;) {
                            // 0x003af2b8
                            charge(ctx, 7);
                            lw(a0, a3, 0);
                            a3 = addiu(a3, 4);
                            a1 = addiu(a1, -1);
                            sw(a0, a2, 0);
                            a2 = addiu(a2, 4);
                            if (i64(a1) <= 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x003af2d4
                        charge(ctx, 9);
                        v1 = sll(v1, 2);
                        v1 = addu(v1, sp);
                        lw(v1, v1, 32);
                        a0 = addu(v0, v1);
                        a1 = s0;
                        jal(ctx, 0x3AF2E8u, gen::fn_datSetFlag_0016f1f0);
                    } else {
                        // 0x003af2a0
                        charge(ctx, 2);
                    }
                }
                goto L_003af33c;
            }
        L_003af31c:
            charge(ctx, 8);
            jal(ctx, 0x3AF31Cu, gen::fn_clndGetCurrentWeekDay_0017db00);
            jal(ctx, 0x3AF324u, gen::fn_sub_16DD40_0016dd40);
            a0 = v0;
            a1 = s0;
            jal(ctx, 0x3AF334u, gen::fn_sub_16E2B0_0016e2b0);
        }
    L_003af33c:
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003af12c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003af340 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003AF7A0 frInitFontTable -- 668 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Starts the font system (frFontSystemStart: $a0 = GS width in pixels, $a1 = glyph rasters): clears the counters and
// the nine styles' Huffman words, the glyph-size words (512 bytes, log2 9, the GS row of 32 * width / 16 rounded to a
// power of two and its log2, 512 / 64), the GS-list container (sub_3B41A0: 16 x width/16 entries of 32 x 32), the
// glyph ring (sub_3B45F0(0x2C, 4 * n)) and the line ring (0x44, n), loads font0.fnt as style 0 (frLoadFontData),
// prints the CLUT, clears the 32 tag slots, prints "clear texarea", sets the GS width (gp-0x46A8) and creates the
// raster-slot pool (frFontRasterCreate(n)).
void frInitFontTable(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003af7a0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    v0 = 0x960000;
    sw(zero, v0, fnt::kLoCachedGlyphs);  // 0x95AE10
    v0 = 0x960000;
    sw(zero, v0, fnt::kLoGlyphNodes);  // 0x95AE14
    v0 = 0x960000;
    sw(zero, v0, fnt::kLoLineNodes);  // 0x95AE18
    a1 = 0;
    v1 = 0x960000;
    v1 = addiu(v1, fnt::kLoStyles);  // &sFrFontStyles
    for (;;) {
        // 0x003af7f0
        charge(ctx, 3);
        v0 = slti(a1, 9);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003af7e0
        charge(ctx, 4);
        v0 = sll(a1, 5);
        v0 = addu(v1, v0);
        sw(zero, v0, 28);
        a1 = addiu(a1, 1);
    }
    // 0x003af7fc
    charge(ctx, 3);
    s0 = sra(a0, 4);
    if (i64(a0) < 0) {
        // 0x003af808
        charge(ctx, 2);
        v0 = addiu(a0, 15);
        s0 = sra(v0, 4);
    }
    // 0x003af810
    charge(ctx, 6);
    v1 = 512;
    v0 = 0x960000;
    sw(v1, v0, fnt::kLoGlyphBytes);  // 0x95AE2C
    v0 = 0;
    if (v1 != 0) {
        for (;;) {
            // 0x003af838
            charge(ctx, 5);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003af830
            charge(ctx, 2);
            v1 = srl(v1, 1);
            v0 = addiu(v0, 1);
        }
        // 0x003af84c
        charge(ctx, 2);
        v0 = addiu(v0, -1);
        v0 = v0 & 0xFF;
    } else {
        // 0x003af828
        charge(ctx, 2);
    }
    // 0x003af854
    charge(ctx, 7);
    v1 = v0 & 0xFF;
    v0 = 0x960000;
    sw(v1, v0, fnt::kLoGlyphBytesLog2);  // 0x95AE30
    v1 = sll(s0, 5);
    v0 = 0;
    if (v1 != 0) {
        for (;;) {
            // 0x003af880
            charge(ctx, 5);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003af878
            charge(ctx, 2);
            v1 = srl(v1, 1);
            v0 = addiu(v0, 1);
        }
        // 0x003af894
        charge(ctx, 2);
        v0 = addiu(v0, -1);
        v0 = v0 & 0xFF;
    } else {
        // 0x003af870
        charge(ctx, 2);
    }
    // 0x003af89c
    charge(ctx, 9);
    v0 = v0 & 0xFF;
    v1 = addiu(v0, 1);
    v0 = 1;
    v1 = sllv(v0, v1);
    v0 = 0x960000;
    sw(v1, v0, fnt::kLoGsRowPow2);  // 0x95AE34
    v0 = 0;
    if (v1 != 0) {
        for (;;) {
            // 0x003af8d0
            charge(ctx, 5);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003af8c8
            charge(ctx, 2);
            v1 = srl(v1, 1);
            v0 = addiu(v0, 1);
        }
        // 0x003af8e4
        charge(ctx, 2);
        v0 = addiu(v0, -1);
        v0 = v0 & 0xFF;
    } else {
        // 0x003af8c0
        charge(ctx, 2);
    }
    // 0x003af8ec
    charge(ctx, 6);
    v1 = v0 & 0xFF;
    v0 = 0x960000;
    sw(v1, v0, fnt::kLoGsRowLog2);  // 0x95AE38
    v1 = 0;
    for (;;) {
        // 0x003af908
        charge(ctx, 6);
        v0 = slti(v1, 6);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003af904
        charge(ctx, 1);
        v1 = addiu(v1, 1);
    }
    // 0x003af920
    charge(ctx, 10);
    v0 = 0x960000;
    lw(v0, v0, fnt::kLoGlyphBytes);  // 0x95AE2C
    v1 = srl(v0, 6);
    v0 = 0x960000;
    sw(v1, v0, fnt::kLoGlyphQwords64);  // 0x95AE40
    a0 = 0;
    v1 = 0x960000;
    v1 = addiu(v1, fnt::kLoStyles);  // &sFrFontStyles
    for (;;) {
        // 0x003af958
        charge(ctx, 3);
        v0 = slti(a0, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003af948
        charge(ctx, 4);
        v0 = sll(a0, 2);
        v0 = addu(v1, v0);
        sw(zero, v0, 368);
        a0 = addiu(a0, 1);
    }
    // 0x003af964
    charge(ctx, 30);
    v0 = 0x960000;
    lw(a0, v0, fnt::kLoGslArg0);  // 0x95AE3C
    a1 = 16;
    a2 = s0;
    a3 = 32;
    t0 = a3;
    t1 = a1;
    jal(ctx, 0x3AF980u, gen::fn_sub_3B41A0_003b41a0);
    a1 = sll(s1, 2);
    a0 = 44;
    jal(ctx, 0x3AF990u, gen::fn_sub_3B45F0_003b45f0);
    v1 = 0x960000;
    sw(v0, v1, fnt::kLoGlyphRing);  // 0x95AE1C
    a0 = 68;
    a1 = s1;
    jal(ctx, 0x3AF9A8u, gen::fn_sub_3B45F0_003b45f0);
    v1 = 0x960000;
    sw(v0, v1, fnt::kLoLineRing);  // 0x95AE20
    jal(ctx, 0x3AF9B8u, gen::fn_frLoadFontData_003afc70);
    jal(ctx, 0x3AF9C0u, gen::fn_frFontPrintClutData_003aff50);
    a0 = 0;
    v1 = 0x960000;
    v1 = addiu(v1, fnt::kLoTagSlots);  // &0x95AC70
    for (;;) {
        // 0x003af9ec
        charge(ctx, 3);
        v0 = slti(a0, 32);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003af9dc
        charge(ctx, 4);
        v0 = sll(a0, 2);
        v0 = addu(v1, v0);
        sw(zero, v0, 0);
        a0 = addiu(a0, 1);
    }
    // 0x003af9f8
    charge(ctx, 17);
    a0 = 0x6A0000;
    a0 = addiu(a0, 10048);  // "clear texarea  :%s\n"
    a1 = 0x6A0000;
    a1 = addiu(a1, 10032);  // "frFont.c"
    jal(ctx, 0x3AFA08u, gen::fn_printf_005225a8);
    v0 = sll(s0, 4);
    sw(v0, gp, fnt::kGpGsWidth);  // 0x7CE648
    a0 = s1;
    jal(ctx, 0x3AFA1Cu, gen::fn_frFontRasterCreate_003b35e0);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003AFAD0 frAddFontStyle -- 348 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Binds style `s` (< 9, else "Illegal style no error") to a .FNT image: record 0x95ACF0 + 32 * s = {owner (the file
// argument $a2), fnt, width-table bytes, block-2 bytes, width table, block 2, glyph table, Huffman block} from the
// header (CLUT blocks +0xA * 64, the two length-prefixed tables when +0x16, then glyph count * 4 bytes); a null fnt
// takes the file argument (K_Assert 1023 when both are 0); prints "font trans ADDR=...".
void frAddFontStyle(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003afad0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s2 = a1;
    s1 = a2;
    if (s2 == 0) {
        // 0x003afaf8
        charge(ctx, 2);
        if (s1 != 0) {
            // 0x003afb00
            charge(ctx, 1);
            s2 = s1;
        }
    }
    // 0x003afb04
    charge(ctx, 2);
    if (s2 == 0) {
        // 0x003afb0c
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 10032);  // "frFont.c"
        a1 = 1023;
        jal(ctx, 0x3AFB18u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003afb20
    charge(ctx, 8);
    a1 = s0 & 0xFF;
    v1 = sll(a1, 5);
    v0 = 0x960000;
    v0 = addiu(v0, fnt::kLoStyles);  // &sFrFontStyles
    s0 = addu(v0, v1);
    v0 = slti(a1, 9);
    if (v0 == 0) {
        // 0x003afb40
        charge(ctx, 4);
        a0 = 0x6A0000;
        a0 = addiu(a0, 10144);  // "FONT SYS : Illegal style no error.(%x)\n"
        jal(ctx, 0x3AFB48u, gen::fn_sub_35AC50_0035ac50);  // does not return
    }
    // 0x003afb50
    charge(ctx, 9);
    sw(s1, s0, style::kOwner);
    sw(s2, s0, style::kFnt);
    lbu(v0, s2, fnthdr::kClutBlocks);
    v1 = sll(v0, 6);
    lw(v0, s2, fnthdr::kHeaderSize);
    s1 = addu(v0, v1);
    lbu(v0, s2, fnthdr::kHasTables);
    if (v0 == 0) {
        // 0x003afbc4
        charge(ctx, 4);
        sw(zero, s0, style::kWidthBytes);
        sw(zero, s0, style::kWidths);
        sw(zero, s0, style::kBlock2Bytes);
        sw(zero, s0, style::kBlock2);
    } else {
        // 0x003afb74
        charge(ctx, 20);
        v0 = addu(s2, s1);
        lw(v0, v0, 0);
        sw(v0, s0, style::kWidthBytes);
        v0 = addiu(s1, 4);
        v0 = addu(s2, v0);
        sw(v0, s0, style::kWidths);
        lw(v0, s0, style::kWidthBytes);
        v0 = addiu(v0, 4);
        v1 = addu(s1, v0);
        v0 = addu(s2, v1);
        lw(v0, v0, 0);
        sw(v0, s0, style::kBlock2Bytes);
        v0 = addiu(v1, 4);
        v0 = addu(s2, v0);
        sw(v0, s0, style::kBlock2);
        lw(v0, s0, style::kBlock2Bytes);
        v0 = addiu(v0, 4);
        s1 = addu(v1, v0);
    }
    // 0x003afbd4
    charge(ctx, 22);
    a1 = addu(s2, s1);
    sw(a1, s0, style::kGlyphTable);
    lw(v0, s0, style::kFnt);
    lhu(a3, v0, fnthdr::kGlyphCount);
    a0 = 0x6A0000;
    a0 = addiu(a0, 10192);  // "font trans ADDR=0x%x tbloffset=0x%x fontNum=%d\n"
    a2 = s1;
    jal(ctx, 0x3AFBF0u, gen::fn_printf_005225a8);
    lw(v1, s0, style::kFnt);
    lhu(v1, v1, fnthdr::kGlyphCount);
    v1 = sll(v1, 2);
    v1 = addu(s1, v1);
    v1 = addu(s2, v1);
    sw(v1, s0, style::kHuffman);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003AFC70 frLoadFontData -- 444 bytes; frame 0x20: ra sp+0x0
// Loads "font/font0.fnt" once (H_Cdvd_Request + ReadSync, kept in 0x95AE74) and binds it as style 0 ("abort2!! ...
// have been allocated" when style 0 is set); copies style 0's first 32 bytes to styles 1..5 and clears the two scale
// words (gp-0x46B8 / gp-0x46B4).
void frLoadFontData(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003afc70
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x0);
    v1 = 0x960000;
    lw(v1, v1, fnt::kLoStyleHuffman);  // 0x95AD0C
    if (v1 != 0) {
        // 0x003afc88
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 10080);  // "abort2!! FONT SYS : Style %x have been allocated.\n"
        a1 = 0;
        jal(ctx, 0x3AFC94u, gen::fn_printf_005225a8);
    }
    // 0x003afc9c
    charge(ctx, 4);
    v1 = 0x960000;
    lw(v1, v1, fnt::kLoStyleCdNodes);  // 0x95AE74
    if (v1 == 0) {
        // 0x003afcac
        charge(ctx, 20);
        a0 = 0x6A0000;
        a0 = addiu(a0, 10272);  // "font/font0.fnt"
        a1 = 0;
        jal(ctx, 0x3AFCB8u, gen::fn_H_Cdvd_Request_00100d80);
        v1 = 0x960000;
        sw(v0, v1, fnt::kLoStyleCdNodes);  // 0x95AE74
        a0 = v0;
        jal(ctx, 0x3AFCCCu, gen::fn_H_Cdvd_ReadSync_001023a0);
        a0 = 0x6A0000;
        a0 = addiu(a0, 10272);  // "font/font0.fnt"
        a1 = addiu(sp, 0x1C);
        jal(ctx, 0x3AFCE0u, gen::fn_H_Cdvd_CacheFindFile_001021c0);
        a0 = 0;
        a1 = 0;
        a2 = v0;
        jal(ctx, 0x3AFCF4u, gen::fn_frAddFontStyle_003afad0);
    }
    // 0x003afcfc
    charge(ctx, 5);
    a3 = 0x960000;
    a3 = addiu(a3, fnt::kLoStyles);  // &sFrFontStyles
    a2 = 0x960000;
    a2 = addiu(a2, fnt::kLoStyle1);  // &0x95AD10
    a1 = 4;
    for (;;) {
        // 0x003afd10
        charge(ctx, 9);
        lw(a0, a3, 0);
        lw(v1, a3, 4);
        a3 = addiu(a3, 8);
        a1 = addiu(a1, -1);
        sw(a0, a2, 0);
        sw(v1, a2, 4);
        a2 = addiu(a2, 8);
        if (i64(a1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003afd34
    charge(ctx, 5);
    a3 = 0x960000;
    a3 = addiu(a3, fnt::kLoStyles);  // &sFrFontStyles
    a2 = 0x960000;
    a2 = addiu(a2, fnt::kLoStyle2);  // &0x95AD30
    a1 = 4;
    for (;;) {
        // 0x003afd48
        charge(ctx, 9);
        lw(a0, a3, 0);
        lw(v1, a3, 4);
        a3 = addiu(a3, 8);
        a1 = addiu(a1, -1);
        sw(a0, a2, 0);
        sw(v1, a2, 4);
        a2 = addiu(a2, 8);
        if (i64(a1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003afd6c
    charge(ctx, 5);
    a3 = 0x960000;
    a3 = addiu(a3, fnt::kLoStyles);  // &sFrFontStyles
    a2 = 0x960000;
    a2 = addiu(a2, fnt::kLoStyle3);  // &0x95AD50
    a1 = 4;
    for (;;) {
        // 0x003afd80
        charge(ctx, 9);
        lw(a0, a3, 0);
        lw(v1, a3, 4);
        a3 = addiu(a3, 8);
        a1 = addiu(a1, -1);
        sw(a0, a2, 0);
        sw(v1, a2, 4);
        a2 = addiu(a2, 8);
        if (i64(a1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003afda4
    charge(ctx, 5);
    a3 = 0x960000;
    a3 = addiu(a3, fnt::kLoStyles);  // &sFrFontStyles
    a2 = 0x960000;
    a2 = addiu(a2, fnt::kLoStyle4);  // &0x95AD70
    a1 = 4;
    for (;;) {
        // 0x003afdb8
        charge(ctx, 9);
        lw(a0, a3, 0);
        lw(v1, a3, 4);
        a3 = addiu(a3, 8);
        a1 = addiu(a1, -1);
        sw(a0, a2, 0);
        sw(v1, a2, 4);
        a2 = addiu(a2, 8);
        if (i64(a1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003afddc
    charge(ctx, 5);
    a3 = 0x960000;
    a3 = addiu(a3, fnt::kLoStyles);  // &sFrFontStyles
    a2 = 0x960000;
    a2 = addiu(a2, fnt::kLoStyle5);  // &0x95AD90
    a1 = 4;
    for (;;) {
        // 0x003afdf0
        charge(ctx, 9);
        lw(a0, a3, 0);
        lw(v1, a3, 4);
        a3 = addiu(a3, 8);
        a1 = addiu(a1, -1);
        sw(a0, a2, 0);
        sw(v1, a2, 4);
        a2 = addiu(a2, 8);
        if (i64(a1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003afe14
    charge(ctx, 6);
    sw(zero, gp, fnt::kGpScaleY);  // 0x7CE63C
    sw(zero, gp, fnt::kGpScaleX);  // 0x7CE638
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003AFE30 frFreeFontStyles -- 288 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// For every bound style (Huffman word set): drops its file request (0x95AE74 + 4 * s, "font cdvd free StyleNo=%d")
// and clears its owner and Huffman words; the glyph-table word always.
void frFreeFontStyles(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003afe30
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = 0;
    for (;;) {
        // 0x003aff24
        charge(ctx, 3);
        v1 = slti(s3, 9);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003afe54
        charge(ctx, 7);
        a0 = sll(s3, 5);
        v1 = 0x960000;
        v1 = addiu(v1, fnt::kLoStyles);  // &sFrFontStyles
        v1 = addu(v1, a0);
        lw(v1, v1, 28);
        if (v1 != 0) {
            // 0x003afe70
            charge(ctx, 4);
            s2 = s3 & 0xFF;
            v1 = slti(s2, 9);
            if (v1 == 0) {
                // 0x003afe80
                charge(ctx, 5);
                a0 = 0x6A0000;
                a0 = addiu(a0, 10144);  // "FONT SYS : Illegal style no error.(%x)\n"
                a1 = s2;
                jal(ctx, 0x3AFE8Cu, gen::fn_sub_35AC50_0035ac50);  // does not return
            }
            // 0x003afe94
            charge(ctx, 8);
            s1 = s3 & 0xFF;
            a0 = sll(s1, 5);
            v1 = 0x960000;
            v1 = addiu(v1, fnt::kLoStyles);  // &sFrFontStyles
            s0 = addu(v1, a0);
            lw(v1, s0, style::kHuffman);
            if (v1 == 0) {
                // 0x003afeb4
                charge(ctx, 5);
                a0 = 0x6A0000;
                a0 = addiu(a0, 10032);  // "frFont.c"
                a1 = 1074;
                jal(ctx, 0x3AFEC0u, gen::fn_sub_19D3F0_0019d3f0);
            }
            // 0x003afec8
            charge(ctx, 7);
            v1 = sll(s1, 2);
            a1 = 0x960000;
            a1 = addiu(a1, fnt::kLoStyles);  // &sFrFontStyles
            v1 = addu(a1, v1);
            lw(a0, v1, 388);
            if (a0 != 0) {
                // 0x003afee4
                charge(ctx, 14);
                v0 = s3 & 0xFF;
                v0 = sll(v0, 2);
                v0 = addu(a1, v0);
                s1 = addiu(v0, 388);
                jal(ctx, 0x3AFEF4u, gen::fn_H_Cdvd_Destroy_00100ec0);
                sw(zero, s1, 0);
                a0 = 0x6A0000;
                a0 = addiu(a0, 10240);  // "font cdvd free StyleNo=%d\n"
                a1 = s2;
                jal(ctx, 0x3AFF0Cu, gen::fn_printf_005225a8);
                sw(zero, s0, style::kOwner);
                sw(zero, s0, style::kHuffman);
            }
            // 0x003aff1c
            charge(ctx, 1);
            sw(zero, s0, style::kGlyphTable);
        }
        // 0x003aff20
        charge(ctx, 1);
        s3 = addiu(s3, 1);
    }
    // 0x003aff30
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x003B0030 sub_3B0030 -- 316 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [frFontLineChainRelease] Releases a line chain: for every line (+0x24) every glyph node (+0x28) -- a glyph whose
// cache entry (+0x1C) drops to refcount 0 frees its raster slot (in-use bit and GS entry cleared) and its GS-list
// entry (fmGslReleaseEntry), cached-glyph count -1 -- goes back to the glyph ring, then the line to the line ring
// (the two node counters follow). Returns 0.
void sub_3B0030(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b0030
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;  // the chain's first line
    if (s2 != 0) {
        for (;;) {
            // 0x003b0144
            charge(ctx, 2);
            if (s2 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003b005c
            charge(ctx, 3);
            lw(s1, s2, line::kFirstGlyph);  // per line: every glyph back to the glyph ring
            for (;;) {
                // 0x003b010c
                charge(ctx, 2);
                if (s1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x003b0068
                charge(ctx, 4);
                lw(s0, s1, glyph::kNext);
                lw(v0, s1, glyph::kNoCache);
                if (v0 == 0) {  // the glyph holds a cache reference: drop it
                    // 0x003b0078
                    charge(ctx, 7);
                    lw(v1, s1, glyph::kCache);
                    lhu(v0, v1, cache::kRefs);
                    v0 = addiu(v0, -1);
                    sh(v0, v1, cache::kRefs);
                    lw(a1, s1, glyph::kCache);
                    if (a1 != 0) {
                        // 0x003b0094
                        charge(ctx, 3);
                        lhu(v0, a1, cache::kRefs);
                        if (v0 == 0) {
                            // 0x003b00a0: last reference -- the slot leaves use, the GS entry is freed
                            charge(ctx, 3);
                            lw(a0, a1, cache::kSlot);
                            if (a0 != 0) {
                                // 0x003b00ac
                                charge(ctx, 5);
                                lw(v1, a0, slot::kFlags);
                                v0 = si(-2);
                                v0 = v1 & v0;
                                sw(v0, a0, slot::kFlags);
                                sw(zero, a0, slot::kCache);
                            }
                            // 0x003b00c0
                            charge(ctx, 8);
                            lw(a0, a1, cache::kEntry);
                            jal(ctx, 0x3B00C4u, gen::fn_fmGslReleaseEntry_003b4580);
                            v0 = 0x960000;
                            lw(v0, v0, fnt::kLoCachedGlyphs);  // 0x95AE10
                            v1 = addiu(v0, -1);
                            v0 = 0x960000;
                            sw(v1, v0, fnt::kLoCachedGlyphs);  // 0x95AE10
                        }
                    }
                }
                // 0x003b00e0
                charge(ctx, 11);
                a0 = s1;
                v0 = 0x960000;
                lw(a1, v0, fnt::kLoGlyphRing);  // 0x95AE1C
                jal(ctx, 0x3B00ECu, gen::fn_rbFree_003b46f0);
                s1 = s0;
                v0 = 0x960000;
                lw(v0, v0, fnt::kLoGlyphNodes);  // 0x95AE14
                v1 = addiu(v0, -1);
                v0 = 0x960000;
                sw(v1, v0, fnt::kLoGlyphNodes);  // 0x95AE14
            }
            // 0x003b0114
            charge(ctx, 12);
            lw(s0, s2, line::kNext);
            a0 = s2;
            v0 = 0x960000;
            lw(a1, v0, fnt::kLoLineRing);  // 0x95AE20
            jal(ctx, 0x3B0124u, gen::fn_rbFree_003b46f0);
            s2 = s0;
            v0 = 0x960000;
            lw(v0, v0, fnt::kLoLineNodes);  // 0x95AE18
            v1 = addiu(v0, -1);
            v0 = 0x960000;
            sw(v1, v0, fnt::kLoLineNodes);  // 0x95AE18
        }
        // 0x003b014c
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003b0050
        charge(ctx, 3);
        v0 = s2;
    }
    // 0x003b0150 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003B0430 frFontCacheGlyph -- 388 bytes; frame 0x70: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// The glyph cache (frFontCreateGlyphNode, frFontRasterDrawGlyph): looks up (glyph, colour set) in the raster slots
// (frFontRasterFind); a slot with a GS entry is a hit (entry refcount +1). A miss decodes the glyph from its style's
// Huffman block into a RwMalloc'd 512-byte buffer (fmGslGetGlyphBlocks / fmGslDecodeGlyph), takes a slot
// (frFontRasterFindOrAlloc; K_Assert 1730), frees the buffer, then registers a GS entry of the style's glyph size
// (frFontRegisterGlyphRaster) linked both ways with the slot; cached-glyph count +1. Returns the GS entry.
void frFontCacheGlyph(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b0430
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lbu(a1, a0, glyph::kColourSet);
    a0 = s0;
    jal(ctx, 0x3B045Cu, gen::fn_frFontRasterFind_003b3dd0);
    s2 = v0;  // the raster slot holding (glyph, colour set), 0 when none
    if (v0 != 0) {
        // 0x003b0470
        charge(ctx, 3);
        lw(v0, s2, slot::kCache);
        if (v0 != 0) {
            // 0x003b047c: hit -- one more reference to the slot's cache record, which is the result
            charge(ctx, 5);
            lhu(v1, v0, cache::kRefs);
            v1 = addiu(v1, 1);
            sh(v1, v0, cache::kRefs);
            // 0x003b0590 (the shared epilogue, written out on this path)
            charge(ctx, 9);
            ld(ra, sp, 0x50);
            lq(s4, sp, 0x40);
            lq(s3, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x70);
            return;
        }
    }
    // 0x003b0490: miss -- no slot, or a slot whose cache record was released (it keeps its raster; only the GS entry
    // and the cache record are made again below)
    charge(ctx, 2);
    if (s2 == 0) {
        // 0x003b0498: decode the glyph from its style's Huffman block into a scratch buffer and give it a slot
        charge(ctx, 30);
        lbu(v0, s1, glyph::kStyle);
        v1 = sll(v0, 5);
        v0 = 0x960000;
        v0 = addiu(v0, fnt::kLoStyles);  // &sFrFontStyles
        s2 = addu(v0, v1);
        a0 = 512;
        a1 = 0x40000;
        v0 = 0x960000;
        lw(v0, v0, rw::kMalloc);  // 0x960178
        jalr(ctx, 0x3B04BCu, v0.u());
        s3 = v0;
        lw(a0, s2, style::kHuffman);
        a1 = addiu(sp, 0x60);
        jal(ctx, 0x3B04D0u, gen::fn_fmGslGetGlyphBlocks_003b4770);
        a0 = s3;
        a1 = s0;
        lw(a2, s2, style::kHuffman);
        a3 = addiu(sp, 0x60);
        jal(ctx, 0x3B04E8u, gen::fn_fmGslDecodeGlyph_003b47b0);
        lbu(a2, s1, glyph::kColourSet);
        a0 = s0;
        a1 = s3;
        jal(ctx, 0x3B04FCu, gen::fn_frFontRasterFindOrAlloc_003b3d60);
        s2 = v0;
        if (s2 == 0) {
            // 0x003b0510
            charge(ctx, 5);
            a0 = 0x6A0000;
            a0 = addiu(a0, 10032);  // "frFont.c"
            a1 = 1730;
            jal(ctx, 0x3B051Cu, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x003b0524
        charge(ctx, 6);
        a0 = s3;
        v0 = 0x960000;
        lw(v0, v0, rw::kFree);  // 0x96017C
        jalr(ctx, 0x3B0530u, v0.u());
        s3 = 0;
    }
    // 0x003b053c: a GS-list entry + cache record of the style's glyph size, linked both ways with the slot. On the
    // "slot without record" path $a2 is the caller's $s3 (the original passes whatever $s3 holds there).
    charge(ctx, 21);
    lbu(a0, s1, glyph::kStyle);
    jal(ctx, 0x3B0540u, gen::fn_frFontGetStyleGlyphWidth_003b1a10);
    s4 = v0;
    lbu(a0, s1, glyph::kStyle);
    jal(ctx, 0x3B0550u, gen::fn_frFontGetStyleGlyphHeight_003b1a40);
    a0 = s4;
    a1 = v0;
    a2 = s3;
    a3 = 1;
    jal(ctx, 0x3B0568u, gen::fn_frFontRegisterGlyphRaster_003b03a0);
    sh(s0, v0, cache::kGlyph);
    sw(s2, v0, cache::kSlot);
    sw(v0, s2, slot::kCache);
    v1 = 0x960000;
    lw(v1, v1, fnt::kLoCachedGlyphs);  // 0x95AE10
    a0 = addiu(v1, 1);
    v1 = 0x960000;
    sw(a0, v1, fnt::kLoCachedGlyphs);  // 0x95AE10
    // 0x003b0590 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x003B0970 frFontBuildGlyphList -- 572 bytes; frame 0x90: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Appends text to a line node (or a fresh one from the line ring when $t0 is 0; K_Assert 2010): style $a1 (>= 0 sets
// the current style gp-0x46B0), colour set $a2, mode $a3; returns 0 when the style has no font. Each character (two
// bytes from 0x80) becomes a glyph node (frFontCreateGlyphNode; K_Assert 2031) linked at the tail (+0x28 / +0x24),
// the line's width (+0xC) and glyph count (+0x18) grow, pair kerning (frFontKerningAdjust) is taken off the previous
// glyph and the width; the last glyph's scaled sizes go to the line (+0x10 / +0x12). Returns the line.
void frFontBuildGlyphList(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b0970
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;  // text
    s6 = a2;  // colour set
    s7 = a3;  // mode
    s3 = t0;  // the line to append to (0: a new one)
    s5 = 0;  // text length
    v0 = dsll32(a1, 24);
    v0 = dsra32(v0, 24);
    if (i64(v0) >= 0) {
        // 0x003b09bc
        charge(ctx, 1);
        sb(a1, gp, fnt::kGpCurStyle);  // 0x7CE640
    }
    // 0x003b09c0
    charge(ctx, 8);
    lbu(v0, gp, fnt::kGpCurStyle);  // 0x7CE640
    v1 = sll(v0, 5);
    v0 = 0x960000;
    v0 = addiu(v0, fnt::kLoStyleHuffman);  // &0x95AD0C
    v0 = addu(v0, v1);
    lw(v0, v0, 0);  // the current style's Huffman block
    if (v0 != 0) {
        // 0x003b09ec: the style has a font
        charge(ctx, 2);
        if (s4 != 0) {
            // 0x003b09f4
            charge(ctx, 4);
            a0 = s4;
            jal(ctx, 0x3B09F8u, gen::fn_strlen_00524388);
            s5 = v0;
        }
        // 0x003b0a04
        charge(ctx, 2);
        if (s3 == 0) {
            // 0x003b0a0c
            charge(ctx, 12);
            v0 = 0x960000;
            lw(a0, v0, fnt::kLoLineRing);  // 0x95AE20
            jal(ctx, 0x3B0A14u, gen::fn_rbAlloc_003b46b0);
            s3 = v0;
            v0 = 0x960000;
            lw(v0, v0, fnt::kLoLineNodes);  // 0x95AE18
            v1 = addiu(v0, 1);
            v0 = 0x960000;
            sw(v1, v0, fnt::kLoLineNodes);  // 0x95AE18
            if (s3 == 0) {
                // 0x003b0a3c
                charge(ctx, 5);
                a0 = 0x6A0000;
                a0 = addiu(a0, 10032);  // "frFont.c"
                a1 = 2010;
                jal(ctx, 0x3B0A48u, gen::fn_sub_19D3F0_0019d3f0);
            }
            // 0x003b0a50
            charge(ctx, 3);
            a0 = s3;
            jal(ctx, 0x3B0A54u, gen::fn_frFontInitLineNode_003b05c0);
        }
        // 0x003b0a5c
        charge(ctx, 7);
        s1 = 0;
        lw(s0, s3, line::kLastGlyph);  // s0 = the tail glyph, s1 = the new glyph, s2 = the read index
        s2 = 0;
        s7 = s7 & 0xFF;
        s6 = s6 & 0xFF;
        for (;;) {
            // 0x003b0b50
            charge(ctx, 3);
            v0 = sltu(s2, s5);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003b0a78: the code -- one byte, or two from 0x80
            charge(ctx, 5);
            v0 = addu(s4, s2);
            lbu(a0, v0, 0);
            v0 = slti(a0, 128);
            if (v0 == 0) {
                // 0x003b0a8c
                charge(ctx, 6);
                s2 = addiu(s2, 1);
                v0 = addu(s4, s2);
                lbu(v1, v0, 0);
                v0 = sll(a0, 8);
                v0 = v0 | v1;
                a0 = v0 & 0xFFFF;
            }
            // 0x003b0aa4
            charge(ctx, 8);
            lbu(a1, gp, fnt::kGpCurStyle);  // 0x7CE640
            a2 = s6;
            a3 = s7;
            jal(ctx, 0x3B0AB0u, gen::fn_frFontCreateGlyphNode_003b0620);
            s1 = v0;
            if (s0 != 0) {
                // 0x003b0ad0
                charge(ctx, 1);
                sw(s1, s0, glyph::kNext);
            } else {
                // 0x003b0ac4
                charge(ctx, 3);
                sw(s1, s3, line::kFirstGlyph);
            }
            // 0x003b0ad4
            charge(ctx, 2);
            if (s1 == 0) {
                // 0x003b0adc
                charge(ctx, 5);
                a0 = 0x6A0000;
                a0 = addiu(a0, 10032);  // "frFont.c"
                a1 = 2031;
                jal(ctx, 0x3B0AE8u, gen::fn_sub_19D3F0_0019d3f0);
            }
            // 0x003b0af0: link it, grow the width and the count, then take the pair kerning off the previous glyph
            charge(ctx, 14);
            sw(s0, s1, glyph::kPrev);
            s0 = s1;
            lw(v1, s3, line::kWidth);
            lw(v0, s1, glyph::kAdvance);
            v0 = addu(v1, v0);
            sw(v0, s3, line::kWidth);
            lw(v0, s3, line::kCount);
            v0 = addiu(v0, 1);
            sw(v0, s3, line::kCount);
            a0 = s1;
            jal(ctx, 0x3B0B18u, gen::fn_frFontKerningAdjust_003b0840);
            if (v0 != 0) {
                // 0x003b0b28
                charge(ctx, 3);
                lw(a0, s1, glyph::kPrev);
                if (a0 != 0) {
                    // 0x003b0b34
                    charge(ctx, 3);
                    lw(v1, a0, glyph::kAdvance);
                    v1 = subu(v1, v0);
                    sw(v1, a0, glyph::kAdvance);
                }
                // 0x003b0b40
                charge(ctx, 3);
                lw(v1, s3, line::kWidth);
                v0 = subu(v1, v0);
                sw(v0, s3, line::kWidth);
            }
            // 0x003b0b4c
            charge(ctx, 1);
            s2 = addiu(s2, 1);
        }
        // 0x003b0b5c
        charge(ctx, 2);
        if (s1 != 0) {
            // 0x003b0b64
            charge(ctx, 5);
            sw(s1, s3, line::kLastGlyph);
            lbu(v0, s1, glyph::kSizeW);
            sh(v0, s3, line::kSizeW);
            lbu(v0, s1, glyph::kSizeH);
            sh(v0, s3, line::kSizeH);
        }
        // 0x003b0b78
        charge(ctx, 1);
        v0 = s3;
    } else {
        // 0x003b09e0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003b0b7c (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0x90);
}

// 0x003B0F50 sub_3B0F50 -- 932 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [frFontGlyphRevealStep] One glyph of the typewriter reveal (frFontDraw): the glyph becomes visible (its alpha +0x10
// low byte raised by 32 * speed / (advance + spacing), clamped at 255) once the previous glyph is past the threshold
// `skip` (+20 for ASCII), honouring the window's wait tags (F247 / F215: until the voice ends or the ticks run out;
// F214: ticks), and the tag F117 window wait; returns the y jitter of a mode-1 glyph that is not fully shown (-16 *
// (2 * code2 % 5 - 2)).
void sub_3B0F50(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x003b0f50
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s0 = a3;
    s6 = 0;
    s5 = 0;
    a0 = 255;
    v1 = 0;
    s4 = 1;
    lw(v0, a1, glyph::kPrev);
    if (v0 != 0) {
        // 0x003b0fc8
        charge(ctx, 1);
        lbu(a0, v0, glyph::kRgba);
    } else {
        // 0x003b0fa0
        charge(ctx, 3);
        lw(v0, s2, line::kNext);
        if (v0 != 0) {
            // 0x003b0fac
            charge(ctx, 3);
            lw(v0, v0, line::kLastGlyph);
            if (v0 != 0) {
                // 0x003b0fb8
                charge(ctx, 4);
                lbu(a0, v0, glyph::kRgba);
                lbu(v1, v0, glyph::kMode);
            }
        }
    }
    // 0x003b0fcc
    charge(ctx, 3);
    v0 = a2 & 0xFF;
    if (i64(v0) > 0) {
        // 0x003b0fd8
        charge(ctx, 4);
        lhu(v0, s1, glyph::kCode);
        at = slti(v0, 128);
        if (at != 0) {
            // 0x003b0fe8
            charge(ctx, 2);
            v0 = addiu(a2, 20);
            a2 = v0 & 0xFF;
        }
    }
    // 0x003b0ff0
    charge(ctx, 4);
    s3 = addiu(s1, 16);
    v1 = v1 & 0xFF;
    if (v1 != 0) {
        // 0x003b1000
        charge(ctx, 3);
        lbu(v0, s1, glyph::kMode);
        if (v1 == v0) {
            goto L_003b100c;
        }
        // 0x003b102c
        charge(ctx, 4);
        a1 = a0 & 0xFF;
        v0 = 255;
        if (a1 == v0) {
            // 0x003b103c
            charge(ctx, 1);
            s5 = 1;
        }
        goto L_003b1040;
    }
L_003b100c:
    charge(ctx, 5);
    a1 = a0 & 0xFF;
    v0 = a2 & 0xFF;
    v0 = slt(a1, v0);
    if (v0 == 0) {
        // 0x003b1020
        charge(ctx, 3);
        s5 = 1;
    }
L_003b1040:
    charge(ctx, 3);
    lw(a0, s2, line::kNext);
    if (a0 != 0) {
        // 0x003b104c
        charge(ctx, 3);
        lw(v0, s2, line::kFirstGlyph);
        if (v0 == s1) {
            // 0x003b1058
            charge(ctx, 3);
            lw(v0, s2, line::kDirty);
            if (v0 == 0) {
                // 0x003b1064
                charge(ctx, 4);
                lw(v1, a0, line::kWaitCode);
                v0 = 0xF247;
                if (v1 == v0) {
                    // 0x003b110c
                    charge(ctx, 4);
                    lw(v1, a0, line::kWaitTicks);
                    v0 = si(-1);
                    if (v1 == v0) {
                        // 0x003b1138
                        charge(ctx, 5);
                        a0 = 2;
                        jal(ctx, 0x3B113Cu, gen::fn_sub_10A500_0010a500);
                        if (v0 != 0) {
                            // 0x003b114c
                            charge(ctx, 1);
                            s5 = 0;
                        }
                    } else {
                        // 0x003b111c
                        charge(ctx, 2);
                        if (i64(v1) > 0) {
                            // 0x003b1124
                            charge(ctx, 5);
                            s5 = 0;
                            v0 = addiu(v1, -1);
                            sw(v0, a0, line::kWaitTicks);
                        }
                    }
                } else {
                    // 0x003b1074
                    charge(ctx, 3);
                    v0 = 0xF215;
                    if (v1 == v0) {
                        // 0x003b10c0
                        charge(ctx, 4);
                        lw(v1, a0, line::kWaitTicks);
                        v0 = si(-1);
                        if (v1 == v0) {
                            // 0x003b10ec
                            charge(ctx, 5);
                            a0 = 2;
                            jal(ctx, 0x3B10F0u, gen::fn_sub_10A500_0010a500);
                            if (v0 != 0) {
                                // 0x003b1100
                                charge(ctx, 3);
                                s5 = 0;
                            }
                        } else {
                            // 0x003b10d0
                            charge(ctx, 2);
                            if (i64(v1) > 0) {
                                // 0x003b10d8
                                charge(ctx, 5);
                                s5 = 0;
                                v0 = addiu(v1, -1);
                                sw(v0, a0, line::kWaitTicks);
                            }
                        }
                    } else {
                        // 0x003b1080
                        charge(ctx, 3);
                        v0 = 0xF214;
                        if (v1 == v0) {
                            // 0x003b1094
                            charge(ctx, 3);
                            lw(v1, a0, line::kWaitTicks);
                            if (i64(v1) > 0) {
                                // 0x003b10a0
                                charge(ctx, 4);
                                s5 = 0;
                                v0 = 255;
                                if (a1 == v0) {
                                    // 0x003b10b0
                                    charge(ctx, 4);
                                    v0 = addiu(v1, -1);
                                    sw(v0, a0, line::kWaitTicks);
                                }
                            }
                        } else {
                            // 0x003b108c
                            charge(ctx, 2);
                        }
                    }
                }
            }
        }
    }
    // 0x003b1150
    charge(ctx, 4);
    lw(v1, s2, line::kWaitArmed);
    v0 = 0xF117;
    if (v1 == v0) {
        // 0x003b1160
        charge(ctx, 5);
        lw(v0, s2, line::kLastGlyph);
        lbu(v1, v0, glyph::kRgba);
        v0 = 255;
        if (v1 == v0) {
            // 0x003b1174
            charge(ctx, 3);
            lw(v0, s2, line::kWaitFlag);
            if (v0 == 0) {
                // 0x003b1180
                charge(ctx, 3);
                lw(v1, s2, line::kWaitTicks);
                if (i64(v1) > 0) {
                    // 0x003b118c
                    charge(ctx, 3);
                    v0 = 0xFFFF;
                    if (v1 != v0) {
                        // 0x003b11b4
                        charge(ctx, 1);
                        s4 = 0;
                    } else {
                        // 0x003b1198
                        charge(ctx, 4);
                        jal(ctx, 0x3B1198u, gen::fn_sub_35AE90_0035ae90);
                        if (v0 != 0) {
                            // 0x003b11a8
                            charge(ctx, 3);
                            s4 = 0;
                        }
                    }
                }
            }
            // 0x003b11b8
            charge(ctx, 2);
            if (s4 != 0) {
                // 0x003b11c0
                charge(ctx, 1);
                sw(zero, s2, line::kWaitArmed);
            }
        }
    }
    // 0x003b11c4
    charge(ctx, 2);
    if (s5 != 0) {
        // 0x003b11cc
        charge(ctx, 4);
        a0 = s0 & 0xFF;
        at = slti(a0, 255);
        if (at == 0) {
            // 0x003b121c
            charge(ctx, 1);
            v0 = 255;
        } else {
            // 0x003b11dc
            charge(ctx, 16);
            lb(v1, s2, line::kSpacing);
            lw(v0, s1, glyph::kAdvance);
            v0 = addu(v0, v1);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = sll(a0, 5);
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            div_s(f0, f0, f1);
            cvt_w_s(f0, f0);
            mfc1(v0, f0);
        }
        // 0x003b1220
        charge(ctx, 3);
        at = slti(v0, 256);
        if (at != 0) {
            // 0x003b1238
            charge(ctx, 1);
            v0 = v0 & 0xFF;
        } else {
            // 0x003b122c
            charge(ctx, 3);
            v0 = 255;
        }
        // 0x003b123c
        charge(ctx, 8);
        a1 = v0 & 0xFF;
        lw(a0, s3, 0);
        v1 = 255;
        v0 = a0 & 0xFF;
        v0 = subu(v1, v0);
        v0 = sltu(v0, a1);
        if (v0 != 0) {
            // 0x003b126c
            charge(ctx, 4);
            v0 = si(-256);
            v0 = a0 & v0;
            v0 = v0 | 0xFF;
            sw(v0, s3, 0);
        } else {
            // 0x003b125c
            charge(ctx, 4);
            v0 = addu(a0, a1);
            sw(v0, s3, 0);
        }
    }
    // 0x003b127c
    charge(ctx, 5);
    lhu(a0, s1, glyph::kCode2);
    lbu(v0, s3, 0);
    at = slti(v0, 255);
    if (at != 0) {
        // 0x003b1290
        charge(ctx, 4);
        lbu(v1, s1, glyph::kMode);
        v0 = 1;
        if (v1 == v0) {
            // 0x003b12a8
            charge(ctx, 7);
            v1 = sll(a0, 1);
            v0 = 5;
            div(v1, v0);
            mfhi(v0);
            v0 = addiu(v0, -2);
            v0 = sll(v0, 4);
            s6 = subu(0, v0);
        } else {
            // 0x003b12a0
            charge(ctx, 2);
        }
    }
    // 0x003b12c4 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    v0 = s6;
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

// 0x003B1710 sub_3B1710 -- 424 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [frFontChainWaitDone] Sums the glyph counts (+0x18) of a chain (+0x2C, +0x28) and checks the last line's wait tag:
// F247 / F215 wait for the voice (H_Snd channel 2) and ticks, F246 counts ticks down, F214 ticks; returns the count
// when no wait is pending, else 0.
void sub_3B1710(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b1710
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = 1;
    s0 = 0;
    if (s2 != 0) {
        // 0x003b1744
        charge(ctx, 3);
        lw(s2, s2, line::kChainHead);
        for (;;) {
            // 0x003b187c
            charge(ctx, 2);
            if (s2 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003b1750
            charge(ctx, 3);
            lw(v0, s2, line::kChainNext);
            if (v0 == 0) {
                // 0x003b175c
                charge(ctx, 3);
                lw(v0, s2, line::kDirty);
                if (v0 == 0) {
                    // 0x003b1768
                    charge(ctx, 4);
                    lw(v1, s2, line::kWaitCode);
                    v0 = 0xF247;
                    if (v1 == v0) {
                        // 0x003b1834
                        charge(ctx, 5);
                        a0 = 2;
                        jal(ctx, 0x3B1838u, gen::fn_sub_10A500_0010a500);
                        if (v0 == 0) {
                            // 0x003b1854
                            charge(ctx, 4);
                            lw(v1, s2, line::kWaitTicks);
                            v0 = si(-1);
                            if (v1 != v0) {
                                // 0x003b1864
                                charge(ctx, 2);
                                if (i64(v1) > 0) {
                                    // 0x003b186c
                                    charge(ctx, 1);
                                    s1 = 0;
                                }
                            }
                        } else {
                            // 0x003b1848
                            charge(ctx, 3);
                            s1 = 0;
                        }
                    } else {
                        // 0x003b1778
                        charge(ctx, 3);
                        v0 = 0xF246;
                        if (v1 == v0) {
                            // 0x003b1808
                            charge(ctx, 4);
                            lw(v1, s2, line::kWaitTicks);
                            v0 = si(-1);
                            if (v1 != v0) {
                                // 0x003b1818
                                charge(ctx, 2);
                                if (i64(v1) > 0) {
                                    // 0x003b1820
                                    charge(ctx, 5);
                                    v0 = addiu(v1, -1);
                                    sw(v0, s2, line::kWaitTicks);
                                    s1 = 0;
                                }
                            }
                        } else {
                            // 0x003b1784
                            charge(ctx, 3);
                            v0 = 0xF215;
                            if (v1 == v0) {
                                // 0x003b17c4
                                charge(ctx, 5);
                                a0 = 2;
                                jal(ctx, 0x3B17C8u, gen::fn_sub_10A500_0010a500);
                                if (v0 == 0) {
                                    // 0x003b17e4
                                    charge(ctx, 4);
                                    lw(v1, s2, line::kWaitTicks);
                                    v0 = si(-1);
                                    if (v1 != v0) {
                                        // 0x003b17f4
                                        charge(ctx, 2);
                                        if (i64(v1) > 0) {
                                            // 0x003b17fc
                                            charge(ctx, 3);
                                            s1 = 0;
                                        }
                                    }
                                } else {
                                    // 0x003b17d8
                                    charge(ctx, 3);
                                    s1 = 0;
                                }
                            } else {
                                // 0x003b1790
                                charge(ctx, 3);
                                v0 = 0xF214;
                                if (v1 == v0) {
                                    // 0x003b17a4
                                    charge(ctx, 2);
                                    if (s1 != 0) {
                                        // 0x003b17ac
                                        charge(ctx, 3);
                                        lw(v0, s2, line::kWaitTicks);
                                        if (i64(v0) > 0) {
                                            // 0x003b17b8
                                            charge(ctx, 3);
                                            s1 = 0;
                                        }
                                    }
                                } else {
                                    // 0x003b179c
                                    charge(ctx, 2);
                                }
                            }
                        }
                    }
                }
            }
            // 0x003b1870
            charge(ctx, 3);
            lw(v0, s2, line::kCount);
            s0 = addu(s0, v0);
            lw(s2, s2, line::kChainNext);
        }
        // 0x003b1884
        charge(ctx, 4);
        v0 = dsll32(s1, 24);
        v0 = dsra32(v0, 24);
        if (v0 == 0) {
            // 0x003b1894
            charge(ctx, 1);
            s0 = 0;
        }
        // 0x003b1898
        charge(ctx, 1);
        v0 = s0;
    } else {
        // 0x003b1738
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003b189c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003B1D90 sub_3B1D90 -- 652 bytes; frame 0x90: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [frFontLayoutTagSlot] Lays out tag slot `n` (0x95AC70[n]) into the layout record $a1 character by character: a
// style change since the previous character starts a new line node (an empty line from "" joined to the chain, alpha
// from the record) ; each character through frFontBuildGlyphList with the record's style / colour set / mode, letter
// spacing gp-0x5804, the line width recomputed (K_Assert 2072 / 2120).
void sub_3B1D90(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b1d90
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a1;
    v1 = a0 & 0xFF;
    a0 = sll(v1, 2);
    v1 = 0x960000;
    v1 = addiu(v1, fnt::kLoTagSlots);  // &0x95AC70
    v1 = addu(v1, a0);
    lw(s3, v1, 0);
    a0 = addiu(sp, 0x8C);
    v1 = 3;
    if (a0 != 0) {
        for (;;) {
            // 0x003b1de0
            charge(ctx, 7);
            sb(zero, a0, 0);
            a0 = addiu(a0, 1);
            v1 = addiu(v1, -1);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x003b1dfc
    charge(ctx, 2);
    if (s3 != 0) {
        // 0x003b1e04
        charge(ctx, 8);
        a0 = s3;
        jal(ctx, 0x3B1E08u, gen::fn_strlen_00524388);
        s6 = v0;
        lb(s0, s4, lay::kStyle);
        s2 = 0;
        for (;;) {
            // 0x003b1fe4
            charge(ctx, 3);
            v1 = slt(s2, s6);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003b1e24
            charge(ctx, 8);
            v0 = addu(s3, s2);
            lb(v0, v0, 0);
            sb(v0, sp, 0x8C);
            sb(zero, sp, 0x8D);
            v0 = v0 & 0xFF;
            v0 = slti(v0, 128);
            if (v0 == 0) {
                // 0x003b1e44
                charge(ctx, 4);
                s2 = addiu(s2, 1);
                v0 = addu(s3, s2);
                lb(v0, v0, 0);
                sb(v0, sp, 0x8D);
            }
            // 0x003b1e54
            charge(ctx, 5);
            lb(s1, s4, lay::kStyle);
            v0 = dsll32(s0, 24);
            v0 = dsra32(v0, 24);
            if (s1 != v0) {
                // 0x003b1e68
                charge(ctx, 3);
                lw(s0, s4, lay::kLine);
                if (s0 == 0) {
                    // 0x003b1ed0
                    charge(ctx, 9);
                    lb(a2, s4, lay::kColourSet);
                    lb(a3, s4, lay::kMode);
                    a0 = addiu(gp, fnt::kGpEmptyText);  // &0x7CD528
                    a1 = 0;
                    t0 = 0;
                    jal(ctx, 0x3B1EE4u, gen::fn_frFontBuildGlyphList_003b0970);
                    if (v0 != 0) {
                        // 0x003b1efc
                        charge(ctx, 6);
                        a0 = s0;
                        a1 = v0;
                        a2 = 1;
                        jal(ctx, 0x3B1F08u, gen::fn_frFontLineChainJoin_003b1920);
                        s0 = v0;
                    } else {
                        // 0x003b1ef4
                        charge(ctx, 2);
                    }
                    // 0x003b1f14
                    charge(ctx, 1);
                    sw(s0, s4, lay::kLine);
                } else {
                    // 0x003b1e74
                    charge(ctx, 3);
                    lw(v0, s0, line::kFirstGlyph);
                    if (v0 != 0) {
                        // 0x003b1e80
                        charge(ctx, 9);
                        lb(a2, s4, lay::kColourSet);
                        lb(a3, s4, lay::kMode);
                        a0 = addiu(gp, fnt::kGpEmptyText);  // &0x7CD528
                        a1 = 0;
                        t0 = 0;
                        jal(ctx, 0x3B1E94u, gen::fn_frFontBuildGlyphList_003b0970);
                        if (v0 != 0) {
                            // 0x003b1eac
                            charge(ctx, 6);
                            a0 = s0;
                            a1 = v0;
                            a2 = 1;
                            jal(ctx, 0x3B1EB8u, gen::fn_frFontLineChainJoin_003b1920);
                            s0 = v0;
                        } else {
                            // 0x003b1ea4
                            charge(ctx, 2);
                        }
                        // 0x003b1ec4
                        charge(ctx, 3);
                        sw(s0, s4, lay::kLine);
                    }
                }
                // 0x003b1f18
                charge(ctx, 4);
                lbu(s5, s4, lay::kAlpha);
                lw(s0, s4, lay::kLine);
                if (s0 == 0) {
                    // 0x003b1f28
                    charge(ctx, 7);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, 10032);  // "frFont.c"
                    a1 = 2072;
                    jal(ctx, 0x3B1F34u, gen::fn_sub_19D3F0_0019d3f0);
                }
                for (;;) {
                    // 0x003b1f4c
                    charge(ctx, 5);
                    if (s0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x003b1f44
                    charge(ctx, 2);
                    sb(s5, s0, line::kAlpha);
                    lw(s0, s0, line::kNext);
                }
                // 0x003b1f60
                charge(ctx, 2);
                s0 = dsll32(s1, 24);
                s0 = dsra32(s0, 24);
            }
            // 0x003b1f68
            charge(ctx, 12);
            lb(a2, s4, lay::kColourSet);
            lb(a3, s4, lay::kMode);
            a0 = addiu(sp, 0x8C);
            a1 = s1;
            lw(t0, s4, lay::kLine);
            jal(ctx, 0x3B1F7Cu, gen::fn_frFontBuildGlyphList_003b0970);
            sw(v0, s4, lay::kLine);
            lb(s5, gp, fnt::kGpLetterSpacing);  // 0x7CD4EC
            s1 = v0;
            if (s1 == 0) {
                // 0x003b1f98
                charge(ctx, 5);
                a0 = 0x6A0000;
                a0 = addiu(a0, 10032);  // "frFont.c"
                a1 = 2120;
                jal(ctx, 0x3B1FA4u, gen::fn_sub_19D3F0_0019d3f0);
            }
            // 0x003b1fac
            charge(ctx, 5);
            sb(s5, s1, line::kSpacing);
            a0 = 0;
            lw(a1, s1, line::kFirstGlyph);
            for (;;) {
                // 0x003b1fd4
                charge(ctx, 2);
                if (a1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x003b1fc0
                charge(ctx, 5);
                lw(v1, a1, glyph::kAdvance);
                a0 = addu(a0, v1);
                lb(v1, s1, line::kSpacing);
                a0 = addu(a0, v1);
                lw(a1, a1, glyph::kNext);
            }
            // 0x003b1fdc
            charge(ctx, 2);
            sw(a0, s1, line::kWidth);
            s2 = addiu(s2, 1);
        }
    }
    // 0x003b1ff0 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x003B2020 sub_3B2020 -- 632 bytes; frame 0x90: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [frFontLayoutString] As sub_3B1D90 for a string argument (the inserted-string tag handlers: names, dates,
// weekdays).
void sub_3B2020(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b2020
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s3 = a1;
    a0 = addiu(sp, 0x8C);
    v1 = 3;
    if (a0 != 0) {
        for (;;) {
            // 0x003b205c
            charge(ctx, 7);
            sb(zero, a0, 0);
            a0 = addiu(a0, 1);
            v1 = addiu(v1, -1);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x003b2078
    charge(ctx, 2);
    if (s4 != 0) {
        // 0x003b2080
        charge(ctx, 8);
        a0 = s4;
        jal(ctx, 0x3B2084u, gen::fn_strlen_00524388);
        s6 = v0;
        lb(s0, s3, lay::kStyle);
        s2 = 0;
        for (;;) {
            // 0x003b2260
            charge(ctx, 3);
            v1 = slt(s2, s6);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003b20a0
            charge(ctx, 8);
            v0 = addu(s4, s2);
            lb(v0, v0, 0);
            sb(v0, sp, 0x8C);
            sb(zero, sp, 0x8D);
            v0 = v0 & 0xFF;
            v0 = slti(v0, 128);
            if (v0 == 0) {
                // 0x003b20c0
                charge(ctx, 4);
                s2 = addiu(s2, 1);
                v0 = addu(s4, s2);
                lb(v0, v0, 0);
                sb(v0, sp, 0x8D);
            }
            // 0x003b20d0
            charge(ctx, 5);
            lb(s1, s3, lay::kStyle);
            v0 = dsll32(s0, 24);
            v0 = dsra32(v0, 24);
            if (s1 != v0) {
                // 0x003b20e4
                charge(ctx, 3);
                lw(s0, s3, lay::kLine);
                if (s0 == 0) {
                    // 0x003b214c
                    charge(ctx, 9);
                    lb(a2, s3, lay::kColourSet);
                    lb(a3, s3, lay::kMode);
                    a0 = addiu(gp, fnt::kGpEmptyText);  // &0x7CD528
                    a1 = 0;
                    t0 = 0;
                    jal(ctx, 0x3B2160u, gen::fn_frFontBuildGlyphList_003b0970);
                    if (v0 != 0) {
                        // 0x003b2178
                        charge(ctx, 6);
                        a0 = s0;
                        a1 = v0;
                        a2 = 1;
                        jal(ctx, 0x3B2184u, gen::fn_frFontLineChainJoin_003b1920);
                        s0 = v0;
                    } else {
                        // 0x003b2170
                        charge(ctx, 2);
                    }
                    // 0x003b2190
                    charge(ctx, 1);
                    sw(s0, s3, lay::kLine);
                } else {
                    // 0x003b20f0
                    charge(ctx, 3);
                    lw(v0, s0, line::kFirstGlyph);
                    if (v0 != 0) {
                        // 0x003b20fc
                        charge(ctx, 9);
                        lb(a2, s3, lay::kColourSet);
                        lb(a3, s3, lay::kMode);
                        a0 = addiu(gp, fnt::kGpEmptyText);  // &0x7CD528
                        a1 = 0;
                        t0 = 0;
                        jal(ctx, 0x3B2110u, gen::fn_frFontBuildGlyphList_003b0970);
                        if (v0 != 0) {
                            // 0x003b2128
                            charge(ctx, 6);
                            a0 = s0;
                            a1 = v0;
                            a2 = 1;
                            jal(ctx, 0x3B2134u, gen::fn_frFontLineChainJoin_003b1920);
                            s0 = v0;
                        } else {
                            // 0x003b2120
                            charge(ctx, 2);
                        }
                        // 0x003b2140
                        charge(ctx, 3);
                        sw(s0, s3, lay::kLine);
                    }
                }
                // 0x003b2194
                charge(ctx, 4);
                lbu(s5, s3, lay::kAlpha);
                lw(s0, s3, lay::kLine);
                if (s0 == 0) {
                    // 0x003b21a4
                    charge(ctx, 7);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, 10032);  // "frFont.c"
                    a1 = 2072;
                    jal(ctx, 0x3B21B0u, gen::fn_sub_19D3F0_0019d3f0);
                }
                for (;;) {
                    // 0x003b21c8
                    charge(ctx, 5);
                    if (s0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x003b21c0
                    charge(ctx, 2);
                    sb(s5, s0, line::kAlpha);
                    lw(s0, s0, line::kNext);
                }
                // 0x003b21dc
                charge(ctx, 2);
                s0 = dsll32(s1, 24);
                s0 = dsra32(s0, 24);
            }
            // 0x003b21e4
            charge(ctx, 12);
            lb(a2, s3, lay::kColourSet);
            lb(a3, s3, lay::kMode);
            a0 = addiu(sp, 0x8C);
            a1 = s1;
            lw(t0, s3, lay::kLine);
            jal(ctx, 0x3B21F8u, gen::fn_frFontBuildGlyphList_003b0970);
            sw(v0, s3, lay::kLine);
            lb(s5, gp, fnt::kGpLetterSpacing);  // 0x7CD4EC
            s1 = v0;
            if (s1 == 0) {
                // 0x003b2214
                charge(ctx, 5);
                a0 = 0x6A0000;
                a0 = addiu(a0, 10032);  // "frFont.c"
                a1 = 2120;
                jal(ctx, 0x3B2220u, gen::fn_sub_19D3F0_0019d3f0);
            }
            // 0x003b2228
            charge(ctx, 5);
            sb(s5, s1, line::kSpacing);
            a0 = 0;
            lw(a1, s1, line::kFirstGlyph);
            for (;;) {
                // 0x003b2250
                charge(ctx, 2);
                if (a1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x003b223c
                charge(ctx, 5);
                lw(v1, a1, glyph::kAdvance);
                a0 = addu(a0, v1);
                lb(v1, s1, line::kSpacing);
                a0 = addu(a0, v1);
                lw(a1, a1, glyph::kNext);
            }
            // 0x003b2258
            charge(ctx, 2);
            sw(a0, s1, line::kWidth);
            s2 = addiu(s2, 1);
        }
    }
    // 0x003b226c (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x003B22A0 sub_3B22A0 -- 352 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [frFontLayoutFlushLine] Applies a layout record's pending state: a new-line request (+0x1C, dropped when the
// current line is still empty) starts a new line node with the record's alpha and line code (K_Assert 2072 / 2092); a
// pending position (+0x1D) moves the current line to (x, y) (K_Assert 2188).
void sub_3B22A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b22a0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, a0, lay::kLine);
    if (v1 != 0) {
        // 0x003b22c8
        charge(ctx, 3);
        lw(v1, v1, line::kFirstGlyph);
        if (v1 == 0) {
            // 0x003b22d4
            charge(ctx, 1);
            sb(zero, s0, lay::kNewLine);
        }
    }
    // 0x003b22d8
    charge(ctx, 3);
    lb(v1, s0, lay::kNewLine);
    if (v1 != 0) {
        // 0x003b22e4
        charge(ctx, 11);
        lw(s2, s0, lay::kLine);
        lb(a2, s0, lay::kColourSet);
        lb(a3, s0, lay::kMode);
        a0 = addiu(gp, fnt::kGpEmptyText);  // &0x7CD528
        a1 = 0;
        t0 = 0;
        jal(ctx, 0x3B22FCu, gen::fn_frFontBuildGlyphList_003b0970);
        a1 = v0;
        if (a1 != 0) {
            // 0x003b2318
            charge(ctx, 5);
            a0 = s2;
            a2 = 1;
            jal(ctx, 0x3B2320u, gen::fn_frFontLineChainJoin_003b1920);
            s2 = v0;
        } else {
            // 0x003b2310
            charge(ctx, 2);
        }
        // 0x003b232c
        charge(ctx, 4);
        sw(s2, s0, lay::kLine);
        lbu(s1, s0, lay::kAlpha);
        if (s2 == 0) {
            // 0x003b233c
            charge(ctx, 7);
            a0 = 0x6A0000;
            a0 = addiu(a0, 10032);  // "frFont.c"
            a1 = 2072;
            jal(ctx, 0x3B2348u, gen::fn_sub_19D3F0_0019d3f0);
        }
        for (;;) {
            // 0x003b2360
            charge(ctx, 5);
            if (s2 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003b2358
            charge(ctx, 2);
            sb(s1, s2, line::kAlpha);
            lw(s2, s2, line::kNext);
        }
        // 0x003b2374
        charge(ctx, 4);
        lh(s2, s0, lay::kLineCode);
        lw(s1, s0, lay::kLine);
        if (s1 == 0) {
            // 0x003b2384
            charge(ctx, 5);
            a0 = 0x6A0000;
            a0 = addiu(a0, 10032);  // "frFont.c"
            a1 = 2092;
            jal(ctx, 0x3B2390u, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x003b2398
        charge(ctx, 2);
        sh(s2, s1, line::kCode);
        sb(zero, s0, lay::kNewLine);
    }
    // 0x003b23a0
    charge(ctx, 3);
    lb(v1, s0, lay::kPosPending);
    if (v1 != 0) {
        // 0x003b23ac
        charge(ctx, 5);
        lw(s3, s0, lay::kY);
        lw(s2, s0, lay::kX);
        lw(s1, s0, lay::kLine);
        if (s1 == 0) {
            // 0x003b23c0
            charge(ctx, 5);
            a0 = 0x6A0000;
            a0 = addiu(a0, 10032);  // "frFont.c"
            a1 = 2188;
            jal(ctx, 0x3B23CCu, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x003b23d4
        charge(ctx, 3);
        sw(s2, s1, line::kX);
        sw(s3, s1, line::kY);
        sb(zero, s0, lay::kPosPending);
    }
    // 0x003b23e0 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x003B2430 sub_3B2430 -- 1228 bytes; frame 0x70: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [frFontLayoutText] The text layout loop (sub_3B2990): skips a 4-byte header when the second byte is 8, clears the
// tag flags, marks the layout phase (default glyph flags low bits 1); per byte: 0 ends, 0xFn + next byte runs
// sFrTagTable[code & 0xFF] (code 2..0x4C; K_Assert 3577 / 3578) and skips 2 * (n - 1) parameter bytes (a non-zero
// result stops), '\n' with flag 4 steps a row; any other character flushes pending lines (as sub_3B22A0, alpha
// through frFontLineSetAlpha), maps a two-byte code >= 0xC080 to style 8 (- 0x4000) and ' ' to the wide blank 0x83F7,
// appends it (frFontBuildGlyphList), sets letter spacing -2 * size / 32, the width and the line's z (layout +8 >> 4;
// K_Assert 2213). Ends the phase (bits 2) and returns the current line.
void sub_3B2430(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b2430
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(a0, a0, lay::kText);
    lbu(v0, a0, 0);
    v1 = v0 & 0xF0;
    v0 = 240;
    if (v1 != v0) {
        // 0x003b2468
        charge(ctx, 4);
        lbu(v1, a0, 1);
        v0 = 8;
        if (v1 == v0) {
            // 0x003b2478
            charge(ctx, 3);
            lw(v0, s1, lay::kPos);
            v0 = addiu(v0, 4);
            sw(v0, s1, lay::kPos);
        }
    }
    // 0x003b2484
    charge(ctx, 13);
    lw(v1, gp, fnt::kGpTagFlags);  // 0x7CD4E8
    v0 = si(-256);
    v0 = v1 & v0;
    sw(v0, gp, fnt::kGpTagFlags);  // 0x7CD4E8
    lh(v0, gp, fnt::kGpGlyphFlags);  // 0x7CD500
    v0 = v0 | 0x1;
    v1 = dsll32(v0, 16);
    v1 = dsra32(v1, 16);
    v0 = si(-3);
    v0 = v1 & v0;
    sh(v0, gp, fnt::kGpGlyphFlags);  // 0x7CD500
    for (;;) {
        // 0x003b2898
        charge(ctx, 8);
        lw(v1, s1, lay::kPos);
        v0 = addiu(v1, 1);
        sw(v0, s1, lay::kPos);
        lw(v0, s1, lay::kText);
        v0 = addu(v0, v1);
        lbu(s0, v0, 0);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003b24b8
        charge(ctx, 4);
        v1 = s0 & 0xF0;
        v0 = 240;
        if (v1 == v0) {
            // 0x003b24c8
            charge(ctx, 12);
            lw(v1, s1, lay::kPos);
            v0 = addiu(v1, 1);
            sw(v0, s1, lay::kPos);
            lw(v0, s1, lay::kText);
            v0 = addu(v0, v1);
            lbu(v1, v0, 0);
            v0 = sll(s0, 8);
            s0 = v0 | v1;
            s2 = s0 & 0xFF;
            at = sltiu(s2, 77);
            if (at == 0) {
                // 0x003b24f8
                charge(ctx, 5);
                a0 = 0x6A0000;
                a0 = addiu(a0, 10032);  // "frFont.c"
                a1 = 3577;
                jal(ctx, 0x3B2504u, gen::fn_sub_19D3F0_0019d3f0);
            }
            // 0x003b250c
            charge(ctx, 3);
            at = slti(s2, 2);
            if (at != 0) {
                // 0x003b2518
                charge(ctx, 5);
                a0 = 0x6A0000;
                a0 = addiu(a0, 10032);  // "frFont.c"
                a1 = 3578;
                jal(ctx, 0x3B2524u, gen::fn_sub_19D3F0_0019d3f0);
            }
            // 0x003b252c
            charge(ctx, 18);
            a0 = s0;
            a1 = s1;
            v1 = sll(s2, 2);
            v0 = 0x6A0000;
            v0 = addiu(v0, fnt::kLoTagTable);  // &sFrTagTable
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            jalr(ctx, 0x3B2548u, v0.u());
            v1 = s0 & 0xF00;
            v1 = sra(v1, 8);
            v1 = addiu(v1, -1);
            a0 = sll(v1, 1);
            lw(v1, s1, lay::kPos);
            v1 = addu(v1, a0);
            sw(v1, s1, lay::kPos);
            if (v0 == 0) {
                // 0x003b2580
                charge(ctx, 3);
                lb(v0, s1, lay::kNewLine);
                if (v0 == 0) {
                    // 0x003b258c
                    charge(ctx, 2);
                    v0 = 1;
                    sb(v0, s1, lay::kNewLine);
                }
                // 0x003b2594
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x003b2574
                charge(ctx, 3);
                v0 = 1;
            }
            // 0x003b2598
            charge(ctx, 2);
            if (v0 == 0) {
                continue;
            }
            goto L_003b25a0_15;
        }
        // 0x003b25a8
        charge(ctx, 3);
        v0 = 10;
        if (s0 != v0) {
            // 0x003b25ec
            charge(ctx, 3);
            lw(v0, s1, lay::kLine);
            if (v0 != 0) {
                // 0x003b25f8
                charge(ctx, 3);
                lw(v0, v0, 28);
                if (v0 == 0) {
                    // 0x003b2604
                    charge(ctx, 1);
                    sb(zero, s1, lay::kNewLine);
                }
            }
            // 0x003b2608
            charge(ctx, 3);
            lb(v0, s1, lay::kNewLine);
            if (v0 != 0) {
                // 0x003b2614
                charge(ctx, 10);
                lw(s2, s1, lay::kLine);
                lb(a2, s1, lay::kColourSet);
                lb(a3, s1, lay::kMode);
                a0 = addiu(gp, fnt::kGpEmptyText);  // &0x7CD528
                a1 = 0;
                t0 = 0;
                jal(ctx, 0x3B262Cu, gen::fn_frFontBuildGlyphList_003b0970);
                if (v0 != 0) {
                    // 0x003b2644
                    charge(ctx, 6);
                    a0 = s2;
                    a1 = v0;
                    a2 = 1;
                    jal(ctx, 0x3B2650u, gen::fn_frFontLineChainJoin_003b1920);
                    s2 = v0;
                } else {
                    // 0x003b263c
                    charge(ctx, 2);
                }
                // 0x003b265c
                charge(ctx, 9);
                sw(s2, s1, lay::kLine);
                a0 = s2;
                lbu(a1, s1, lay::kAlpha);
                jal(ctx, 0x3B2668u, gen::fn_frFontLineSetAlpha_003b0bb0);
                lh(s3, s1, lay::kLineCode);
                lw(s2, s1, lay::kLine);
                if (s2 == 0) {
                    // 0x003b2680
                    charge(ctx, 5);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, 10032);  // "frFont.c"
                    a1 = 2092;
                    jal(ctx, 0x3B268Cu, gen::fn_sub_19D3F0_0019d3f0);
                }
                // 0x003b2694
                charge(ctx, 2);
                sh(s3, s2, line::kCode);
                sb(zero, s1, lay::kNewLine);
            }
            // 0x003b269c
            charge(ctx, 3);
            lb(v0, s1, lay::kPosPending);
            if (v0 != 0) {
                // 0x003b26a8
                charge(ctx, 5);
                lw(s4, s1, lay::kY);
                lw(s3, s1, lay::kX);
                lw(s2, s1, lay::kLine);
                if (s2 == 0) {
                    // 0x003b26bc
                    charge(ctx, 5);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, 10032);  // "frFont.c"
                    a1 = 2188;
                    jal(ctx, 0x3B26C8u, gen::fn_sub_19D3F0_0019d3f0);
                }
                // 0x003b26d0
                charge(ctx, 3);
                sw(s3, s2, line::kX);
                sw(s4, s2, line::kY);
                sb(zero, s1, lay::kPosPending);
            }
            // 0x003b26dc
            charge(ctx, 3);
            at = slti(s0, 128);
            if (at == 0) {
                // 0x003b2740
                charge(ctx, 12);
                lw(v1, s1, lay::kPos);
                v0 = addiu(v1, 1);
                sw(v0, s1, lay::kPos);
                lw(v0, s1, lay::kText);
                v0 = addu(v0, v1);
                lbu(v1, v0, 0);
                v0 = sll(s0, 8);
                v1 = v0 | v1;
                at = 0xC080;
                at = slt(v1, at);
                if (at == 0) {
                    // 0x003b27ac
                    charge(ctx, 14);
                    v1 = addiu(v1, -16384);
                    v0 = v1 & 0xFF00;
                    v0 = sra(v0, 8);
                    sb(v0, sp, 0x6C);
                    sb(v1, sp, 0x6D);
                    sb(zero, sp, 0x6E);
                    lb(a2, s1, lay::kColourSet);
                    lb(a3, s1, lay::kMode);
                    a0 = addiu(sp, 0x6C);
                    a1 = 8;
                    lw(t0, s1, lay::kLine);
                    jal(ctx, 0x3B27D8u, gen::fn_frFontBuildGlyphList_003b0970);
                    sw(v0, s1, lay::kLine);
                } else {
                    // 0x003b2770
                    charge(ctx, 15);
                    v0 = v1 & 0xFF00;
                    v0 = sra(v0, 8);
                    sb(v0, sp, 0x6C);
                    sb(v1, sp, 0x6D);
                    sb(zero, sp, 0x6E);
                    lb(a1, s1, lay::kStyle);
                    lb(a2, s1, lay::kColourSet);
                    lb(a3, s1, lay::kMode);
                    a0 = addiu(sp, 0x6C);
                    lw(t0, s1, lay::kLine);
                    jal(ctx, 0x3B2798u, gen::fn_frFontBuildGlyphList_003b0970);
                    sw(v0, s1, lay::kLine);
                }
            } else {
                // 0x003b26e8
                charge(ctx, 3);
                v0 = 32;
                if (s0 != v0) {
                    // 0x003b2710
                    charge(ctx, 2);
                    sb(s0, sp, 0x6C);
                    sb(zero, sp, 0x6D);
                } else {
                    // 0x003b26f4
                    charge(ctx, 7);
                    v0 = si(-125);
                    sb(v0, sp, 0x6C);
                    v0 = si(-9);
                    sb(v0, sp, 0x6D);
                    sb(zero, sp, 0x6E);
                }
                // 0x003b2718
                charge(ctx, 10);
                lb(a1, s1, lay::kStyle);
                lb(a2, s1, lay::kColourSet);
                lb(a3, s1, lay::kMode);
                a0 = addiu(sp, 0x6C);
                lw(t0, s1, lay::kLine);
                jal(ctx, 0x3B272Cu, gen::fn_frFontBuildGlyphList_003b0970);
                sw(v0, s1, lay::kLine);
            }
            // 0x003b27e4
            charge(ctx, 9);
            lbu(v1, s1, lay::kStyle);
            v0 = addiu(gp, fnt::kGpStyleSizes);  // &0x7CD4F8
            v0 = addu(v0, v1);
            lb(v0, v0, 0);
            v0 = subu(0, v0);
            v1 = sll(v0, 1);
            v0 = sra(v1, 5);
            if (i64(v1) < 0) {
                // 0x003b2808
                charge(ctx, 2);
                v0 = addiu(v1, 31);
                v0 = sra(v0, 5);
            }
            // 0x003b2810
            charge(ctx, 5);
            s2 = dsll32(v0, 24);
            s2 = dsra32(s2, 24);
            lw(s0, s1, lay::kLine);
            if (s0 == 0) {
                // 0x003b2824
                charge(ctx, 5);
                a0 = 0x6A0000;
                a0 = addiu(a0, 10032);  // "frFont.c"
                a1 = 2120;
                jal(ctx, 0x3B2830u, gen::fn_sub_19D3F0_0019d3f0);
            }
            // 0x003b2838
            charge(ctx, 5);
            sb(s2, s0, line::kSpacing);
            v1 = 0;
            lw(a0, s0, line::kFirstGlyph);
            for (;;) {
                // 0x003b2860
                charge(ctx, 2);
                if (a0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x003b284c
                charge(ctx, 5);
                lw(v0, a0, glyph::kAdvance);
                v1 = addu(v1, v0);
                lb(v0, s0, line::kSpacing);
                v1 = addu(v1, v0);
                lw(a0, a0, glyph::kNext);
            }
            // 0x003b2868
            charge(ctx, 5);
            sw(v1, s0, line::kWidth);
            lw(s2, s1, lay::kZ16);
            lw(s0, s1, lay::kLine);
            if (s0 == 0) {
                // 0x003b287c
                charge(ctx, 5);
                a0 = 0x6A0000;
                a0 = addiu(a0, 10032);  // "frFont.c"
                a1 = 2213;
                jal(ctx, 0x3B2888u, gen::fn_sub_19D3F0_0019d3f0);
            }
            // 0x003b2890
            charge(ctx, 2);
            v0 = srl(s2, 4);
            sw(v0, s0, line::kZ);
        } else {
            // 0x003b25b4
            charge(ctx, 4);
            lh(v0, gp, fnt::kGpGlyphFlags);  // 0x7CD500
            v0 = v0 & 0x4;
            if (v0 != 0) {
                // 0x003b25c4
                charge(ctx, 10);
                lw(v0, gp, fnt::kGpLineSpacing);  // 0x7CD4F0
                v1 = sll(v0, 3);
                lw(v0, s1, lay::kY);
                v0 = addu(v0, v1);
                sw(v0, s1, lay::kY);
                v0 = 1;
                sb(v0, s1, lay::kNewLine);
                sb(v0, s1, lay::kPosPending);
            }
        }
    }
    // 0x003b28b8 (the shared epilogue, written out on this path)
    charge(ctx, 17);
    lh(v1, gp, fnt::kGpGlyphFlags);  // 0x7CD500
    v0 = si(-2);
    v0 = v1 & v0;
    v0 = dsll32(v0, 16);
    v0 = dsra32(v0, 16);
    v0 = v0 | 0x2;
    sh(v0, gp, fnt::kGpGlyphFlags);  // 0x7CD500
    lw(v0, s1, lay::kLine);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
    return;
L_003b25a0_15:
    charge(ctx, 2);
    // 0x003b28b8 (the shared epilogue, written out on this path)
    charge(ctx, 17);
    lh(v1, gp, fnt::kGpGlyphFlags);  // 0x7CD500
    v0 = si(-2);
    v0 = v1 & v0;
    v0 = dsll32(v0, 16);
    v0 = dsra32(v0, 16);
    v0 = v0 | 0x2;
    sh(v0, gp, fnt::kGpGlyphFlags);  // 0x7CD500
    lw(v0, s1, lay::kLine);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x003B35E0 frFontRasterCreate -- 344 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Creates the raster-slot pool (frInitFontTable; K_Assert 36 when one exists): RwMalloc(540 * n + 24), header {n,
// slots, active head, tail, free head, tail} at gp-0x46AC, n slots of 28 bytes each followed by its 512-byte glyph
// buffer (+0xC) chained on the free list (+0x18), then a 32 x 32 4-bit raster per slot (RwRasterCreate, format
// 0x4504; "raster create false" retries).
void frFontRasterCreate(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b35e0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    v0 = sll(s0, 4);
    v1 = subu(v0, s0);
    v0 = sll(v1, 3);
    v0 = addu(v1, v0);
    v0 = sll(v0, 2);
    s1 = addiu(v0, 24);
    lw(v0, gp, fnt::kGpRasterSlots);  // 0x7CE644
    if (v0 != 0) {
        // 0x003b3618
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 10392);  // "frFontRaster.c"
        a1 = 36;
        jal(ctx, 0x3B3624u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003b362c
    charge(ctx, 27);
    a0 = s1;
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, rw::kMalloc);  // 0x960178
    jalr(ctx, 0x3B363Cu, v0.u());
    sw(v0, gp, fnt::kGpRasterSlots);  // 0x7CE644
    a0 = v0;
    a1 = 0;
    a2 = s1;
    jal(ctx, 0x3B3654u, gen::fn_memset_00521408);
    lw(v1, gp, fnt::kGpRasterSlots);  // 0x7CE644
    sw(s0, v1, pool::kCount);
    lw(a0, gp, fnt::kGpRasterSlots);  // 0x7CE644
    v1 = addiu(a0, 24);
    sw(v1, a0, 4);
    lw(v1, gp, fnt::kGpRasterSlots);  // 0x7CE644
    lw(a2, v1, pool::kSlots);
    v1 = addiu(a2, 28);
    sw(v1, a2, slot::kBuffer);
    lw(v1, gp, fnt::kGpRasterSlots);  // 0x7CE644
    sw(a2, v1, pool::kFreeHead);
    a3 = 0;
    a0 = addiu(s0, -1);
    for (;;) {
        // 0x003b36b4
        charge(ctx, 3);
        v1 = slt(a3, a0);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003b3698
        charge(ctx, 7);
        lw(v1, a2, slot::kBuffer);
        a1 = addiu(v1, 512);
        sw(a1, a2, slot::kNext);
        a2 = a1;
        v1 = addiu(a1, 28);
        sw(v1, a1, 12);
        a3 = addiu(a3, 1);
    }
    // 0x003b36c0
    charge(ctx, 6);
    lw(v1, gp, fnt::kGpRasterSlots);  // 0x7CE644
    sw(a2, v1, pool::kFreeTail);
    lw(v1, gp, fnt::kGpRasterSlots);  // 0x7CE644
    lw(s0, v1, pool::kFreeHead);
    for (;;) {
        // 0x003b3718
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003b36d8
        charge(ctx, 9);
        a0 = 32;
        a1 = a0;
        a2 = 4;
        a3 = 17668;
        jal(ctx, 0x3B36E8u, gen::fn_sub_4CE0F0_004ce0f0);
        sw(v0, s0, slot::kRaster);
        if (v0 != 0) {
            // 0x003b3714
            charge(ctx, 1);
            lw(s0, s0, slot::kNext);
        } else {
            // 0x003b36fc
            charge(ctx, 6);
            a0 = 0x6A0000;
            a0 = addiu(a0, 10416);  // "raster create false\n"
            jal(ctx, 0x3B3704u, gen::fn_printf_005225a8);
        }
    }
    // 0x003b3720
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003B3E60 frFontRasterAllocSlot -- 296 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Takes the free list's head slot (K_Assert 291 on a null glyph buffer), appends it to the active list, swizzles the
// glyph into its raster (frFontRasterCreate2), stores glyph / ticks 1 / in-use, copies the 512 bytes into the slot's
// buffer and clears the GS entry. Returns the slot or 0.
void frFontRasterAllocSlot(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b3e60
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    s1 = a2;
    if (s2 == 0) {
        // 0x003b3e8c
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 10392);  // "frFontRaster.c"
        a1 = 291;
        jal(ctx, 0x3B3E98u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003b3ea0
    charge(ctx, 5);
    lw(v0, gp, fnt::kGpRasterSlots);  // 0x7CE644
    v1 = addiu(v0, 16);
    lw(s0, v0, 16);
    if (s0 != 0) {
        // 0x003b3eb4
        charge(ctx, 6);
        lw(v0, s0, slot::kNext);
        sw(v0, v1, 0);
        lw(v1, gp, fnt::kGpRasterSlots);  // 0x7CE644
        lw(v0, v1, 16);
        if (v0 == 0) {
            // 0x003b3ecc
            charge(ctx, 1);
            sw(zero, v1, 20);
        }
        // 0x003b3ed0
        charge(ctx, 6);
        sw(zero, s0, slot::kNext);
        lw(v0, gp, fnt::kGpRasterSlots);  // 0x7CE644
        v1 = addiu(v0, 12);
        lw(v0, v0, 12);
        if (v0 == 0) {
            // 0x003b3efc
            charge(ctx, 3);
            sw(s0, v1, 0);
            lw(v0, gp, fnt::kGpRasterSlots);  // 0x7CE644
            sw(s0, v0, 8);
        } else {
            // 0x003b3ee8
            charge(ctx, 5);
            sw(s0, v0, 24);
            lw(v0, gp, fnt::kGpRasterSlots);  // 0x7CE644
            sw(s0, v0, 12);
        }
        // 0x003b3f08
        charge(ctx, 1);
        sw(zero, s0, slot::kCache);
    }
    // 0x003b3f0c
    charge(ctx, 2);
    if (s0 != 0) {
        // 0x003b3f20
        charge(ctx, 18);
        a0 = s0;
        a1 = s2;
        a2 = s1;
        jal(ctx, 0x3B3F2Cu, gen::fn_frFontRasterCreate2_003b3f90);
        sw(s3, s0, slot::kGlyph);
        v0 = 1;
        sh(v0, s0, slot::kTicks);
        lw(v0, s0, slot::kFlags);
        v0 = v0 | 0x1;
        sw(v0, s0, slot::kFlags);
        lw(a0, s0, slot::kBuffer);
        a1 = s2;
        a2 = 512;
        jal(ctx, 0x3B3F58u, gen::fn_memcpy_00521250);
        sw(zero, s0, slot::kCache);
        v0 = s0;
    } else {
        // 0x003b3f14
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003b3f68 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x003B3F90 frFontRasterCreate2 -- 528 bytes; frame 0x140: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Writes a decoded 4-bit 32 x 32 glyph into the slot's raster: copies the 256-byte swizzle table 0x6A28F0 to its
// frame, locks the raster (sub_4CE200, mode 9) and stores each texel at its PSMT4 block address (the low / high
// nibble by the table's bit 0), unlocks, locks the palette and copies colour set `c` (16 entries from 0x6A2130 + 64 *
// c), unlocks; the slot's colour set (+8) = c. No data prints "font data none" (K_Assert 377).
void frFontRasterCreate2(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b3f90
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x140);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a2;
    if (a1 != 0) {
        // 0x003b3fe0
        charge(ctx, 4);
        a3 = 0x6A0000;
        a3 = addiu(a3, fnt::kLoSwizzle);  // &0x6A28F0
        a2 = addiu(sp, 0x40);
        a0 = 64;
        for (;;) {
            // 0x003b3ff0
            charge(ctx, 9);
            lh(v1, a3, 0);
            lh(v0, a3, 2);
            a3 = addiu(a3, 4);
            a0 = addiu(a0, -1);
            sh(v1, a2, 0);
            sh(v0, a2, 2);
            a2 = addiu(a2, 4);
            if (i64(a0) <= 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x003b4014
        charge(ctx, 9);
        s2 = a1;
        lw(a0, s1, slot::kRaster);
        a1 = 0;
        a2 = 9;
        jal(ctx, 0x3B4024u, gen::fn_sub_4CE200_004ce200);
        a1 = 0;
        for (;;) {
            // 0x003b410c
            charge(ctx, 3);
            v1 = slti(a1, 32);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003b4038
            charge(ctx, 14);
            a2 = 0;
            a3 = a1 & 0xFFFF;
            v1 = a3 & 0x7;
            v1 = sra(v1, 2);
            v1 = sll(v1, 7);
            a0 = addu(v1, sp);
            v1 = a3 & 0x3;
            v1 = sll(v1, 5);
            v1 = addu(v1, a0);
            a0 = addiu(v1, 64);
            v1 = sra(a3, 2);
            v1 = sll(v1, 7);
            for (;;) {
                // 0x003b40fc
                charge(ctx, 3);
                a3 = slti(a2, 32);
                if (a3 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x003b4070
                charge(ctx, 21);
                t1 = a2 & 0xFFFF;
                a3 = t1 & 0xF;
                a3 = sll(a3, 1);
                a3 = addu(a0, a3);
                lhu(t0, a3, 0);
                a3 = sra(t1, 4);
                a3 = sll(a3, 5);
                a3 = addu(a3, v1);
                a3 = a3 & 0xFFFF;
                a3 = addu(t0, a3);
                t3 = a3 & 0xFFFF;
                a3 = sra(t3, 1);
                t2 = addu(v0, a3);
                t1 = a2 & 0x1;
                lbu(t0, s2, 0);
                a3 = sll(t1, 2);
                a3 = srav(t0, a3);
                t0 = a3 & 0xF;
                a3 = t3 & 0x1;
                if (a3 != 0) {
                    // 0x003b40d0
                    charge(ctx, 7);
                    a3 = t0 & 0xFF;
                    a3 = sll(a3, 4);
                    a3 = a3 & 0xF0;
                    t0 = a3 & 0xFF;
                    lbu(a3, t2, 0);
                    a3 = a3 | t0;
                    sb(a3, t2, 0);
                } else {
                    // 0x003b40c4
                    charge(ctx, 3);
                    sb(t0, t2, 0);
                }
                // 0x003b40ec
                charge(ctx, 2);
                if (t1 != 0) {
                    // 0x003b40f4
                    charge(ctx, 1);
                    s2 = addiu(s2, 1);
                }
                // 0x003b40f8
                charge(ctx, 1);
                a2 = addiu(a2, 1);
            }
            // 0x003b4108
            charge(ctx, 1);
            a1 = addiu(a1, 1);
        }
        // 0x003b4118
        charge(ctx, 10);
        lw(a0, s1, slot::kRaster);
        jal(ctx, 0x3B411Cu, gen::fn_sub_4CDE00_004cde00);
        lw(a0, s1, slot::kRaster);
        a1 = 1;
        jal(ctx, 0x3B412Cu, gen::fn_sub_4CDF30_004cdf30);
        s2 = v0;
        if (s2 == 0) {
            // 0x003b4140
            charge(ctx, 5);
            a0 = 0x6A0000;
            a0 = addiu(a0, 10392);  // "frFontRaster.c"
            a1 = 428;
            jal(ctx, 0x3B414Cu, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x003b4154
        charge(ctx, 12);
        v1 = sll(s0, 6);
        v0 = 0x6A0000;
        v0 = addiu(v0, fnt::kLoCluts);  // &0x6A2130
        a1 = addu(v0, v1);
        a0 = s2;
        a2 = 64;
        jal(ctx, 0x3B416Cu, gen::fn_memcpy_00521250);
        lw(a0, s1, slot::kRaster);
        jal(ctx, 0x3B4178u, gen::fn_sub_4CDE40_004cde40);
        sh(s0, s1, slot::kColourSet);
    } else {
        // 0x003b3fb4
        charge(ctx, 11);
        a0 = 0x6A0000;
        a0 = addiu(a0, 10736);  // "font data none!!!!!!!!!!!!!!!!!!!!!!\n"
        jal(ctx, 0x3B3FBCu, gen::fn_printf_005225a8);
        a0 = 0x6A0000;
        a0 = addiu(a0, 10392);  // "frFontRaster.c"
        a1 = 377;
        jal(ctx, 0x3B3FD0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003b4184 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x140);
}

// 0x003B41A0 sub_3B41A0 -- 756 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fmGslInit] Initialises the GS-list container once (gp-0x46A4 flag): entry size w x h, w * h / 2 bytes, cols * rows
// entries (also the free count), RwMalloc(32 * n) entries (K_Assert 81) and an optional n * $t1 work block (K_Assert
// 87); a circular doubly linked list (+0x1C next, +0x18 prev) with each entry's index, GS rectangle (x0, y0, x1, y1
// in 1/16 px) and work pointer. Returns 1 (0 when already set up or on a null entry, after sub_3B44A0).
void sub_3B41A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b41a0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a1;
    s5 = a2;
    s3 = a3;
    s2 = t0;
    s1 = t1;
    s0 = 0;
    v0 = 0x960000;
    lw(v0, v0, fnt::kLoGslList);  // 0x95AEBC
    if (v0 != 0) {
        // 0x003b41ec
        charge(ctx, 3);
        lb(v0, gp, fnt::kGpGslReady);  // 0x7CE64C
        if (v0 == 0) {
            goto L_003b4204;
        }
        // 0x003b41f8
        charge(ctx, 3);
        v0 = 0;
        // 0x003b4468 (the shared epilogue, written out on this path)
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
        return;
    }
L_003b4204:
    charge(ctx, 8);
    v0 = 0x960000;
    sw(s3, v0, fnt::kLoGslEntryW);  // 0x95AEA8
    v0 = 0x960000;
    sw(s2, v0, fnt::kLoGslEntryH);  // 0x95AEAC
    mult(v0, s3, s2);
    v1 = sra(v0, 1);
    if (i64(v0) < 0) {
        // 0x003b4224
        charge(ctx, 2);
        v0 = addiu(v0, 1);
        v1 = sra(v0, 1);
    }
    // 0x003b422c
    charge(ctx, 20);
    v0 = 0x960000;
    sw(v1, v0, fnt::kLoGslEntryBytes);  // 0x95AEB0
    mult(v1, s4, s5);
    v0 = 0x960000;
    sw(v1, v0, fnt::kLoGslFreeCount);  // 0x95AEB8
    v0 = 0x960000;
    sw(v1, v0, fnt::kLoGslEntryCount);  // 0x95AEB4
    s6 = 0x960000;
    s6 = addiu(s6, rw::kMalloc);  // &0x960178
    a0 = sll(v1, 5);
    a1 = 0x40000;
    lw(v0, s6, 0);  // 0x960178
    jalr(ctx, 0x3B425Cu, v0.u());
    v1 = 0x960000;
    sw(v0, v1, fnt::kLoGslBlock0);  // 0x95AEA0
    v1 = 0x960000;
    sw(v0, v1, fnt::kLoGslList);  // 0x95AEBC
    if (v0 == 0) {
        // 0x003b427c
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 10776);  // "fmGslCont.c"
        a1 = 81;
        jal(ctx, 0x3B4288u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003b4290
    charge(ctx, 2);
    if (s1 != 0) {
        // 0x003b4298
        charge(ctx, 12);
        v0 = 0x960000;
        lw(v0, v0, fnt::kLoGslFreeCount);  // 0x95AEB8
        mult(a0, s1, v0);
        a1 = 0x40000;
        lw(v0, s6, 0);
        jalr(ctx, 0x3B42ACu, v0.u());
        v1 = 0x960000;
        sw(v0, v1, fnt::kLoGslBlock1);  // 0x95AEA4
        s0 = v0;
        if (s0 == 0) {
            // 0x003b42c8
            charge(ctx, 5);
            a0 = 0x6A0000;
            a0 = addiu(a0, 10776);  // "fmGslCont.c"
            a1 = 87;
            jal(ctx, 0x3B42D4u, gen::fn_sub_19D3F0_0019d3f0);
        }
    }
    // 0x003b42dc
    charge(ctx, 5);
    t0 = 0;
    v1 = 0x960000;
    v0 = 0x960000;
    for (;;) {
        // 0x003b4310
        charge(ctx, 5);
        lw(a0, v0, -20808);
        a0 = addiu(a0, -1);
        a0 = sltu(t0, a0);
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003b42f0
        charge(ctx, 8);
        lw(a3, v1, -20804);
        a2 = addiu(t0, 1);
        a0 = sll(a2, 5);
        a1 = addu(a3, a0);
        a0 = sll(t0, 5);
        a0 = addu(a3, a0);
        sw(a1, a0, gsl::kNext);
        t0 = a2;
    }
    // 0x003b4324
    charge(ctx, 11);
    v0 = 0x960000;
    lw(v1, v0, fnt::kLoGslList);  // 0x95AEBC
    v0 = sll(t0, 5);
    v0 = addu(v0, v1);
    sw(v1, v0, 28);
    v0 = 0x960000;
    lw(v0, v0, fnt::kLoGslFreeCount);  // 0x95AEB8
    a3 = addiu(v0, -1);
    v0 = 0x960000;
    for (;;) {
        // 0x003b4370
        charge(ctx, 2);
        if (i64(a3) <= 0) {
            break;
        }
        backedge(ctx);
        // 0x003b4350
        charge(ctx, 8);
        lw(a2, v0, -20804);
        a1 = addiu(a3, -1);
        v1 = sll(a1, 5);
        a0 = addu(a2, v1);
        v1 = sll(a3, 5);
        v1 = addu(a2, v1);
        sw(a0, v1, gsl::kPrev);
        a3 = a1;
    }
    // 0x003b4378
    charge(ctx, 15);
    v0 = 0x960000;
    lw(v1, v0, fnt::kLoGslList);  // 0x95AEBC
    v0 = 0x960000;
    lw(v0, v0, fnt::kLoGslFreeCount);  // 0x95AEB8
    v0 = addiu(v0, -1);
    v0 = sll(v0, 5);
    v0 = addu(v1, v0);
    sw(v0, v1, gsl::kPrev);
    a1 = 0;
    a2 = 0;
    a0 = sll(s3, 4);
    v1 = sll(s2, 4);
    t0 = 0x960000;
    for (;;) {
        // 0x003b4454
        charge(ctx, 3);
        v0 = slt(a2, s5);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003b43b4
        charge(ctx, 5);
        a3 = 0;
        mult(v0, a2, s2);
        v0 = sll(v0, 4);
        for (;;) {
            // 0x003b4444
            charge(ctx, 3);
            t1 = slt(a3, s4);
            if (t1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003b43c8
            charge(ctx, 5);
            t2 = sll(a1, 5);
            lw(t1, t0, -20804);
            t2 = addu(t1, t2);
            if (t2 == 0) {
                goto L_003b43dc_19;
            }
            // 0x003b43f0
            charge(ctx, 13);
            sw(a1, t2, gsl::kIndex);
            mult(t1, a3, s3);
            t1 = sll(t1, 4);
            sw(t1, t2, gsl::kX0);
            sw(v0, t2, gsl::kY0);
            lw(t1, t2, gsl::kX0);
            t1 = addu(t1, a0);
            sw(t1, t2, gsl::kX1);
            lw(t1, t2, gsl::kY0);
            t1 = addu(t1, v1);
            sw(t1, t2, gsl::kY1);
            if (s0 == 0) {
                // 0x003b4438
                charge(ctx, 1);
                sw(zero, t2, gsl::kWork);
            } else {
                // 0x003b4424
                charge(ctx, 5);
                mult(t1, a1, s1);
                t1 = addu(s0, t1);
                sw(t1, t2, gsl::kWork);
            }
            // 0x003b443c
            charge(ctx, 2);
            a1 = addiu(a1, 1);
            a3 = addiu(a3, 1);
        }
        // 0x003b4450
        charge(ctx, 1);
        a2 = addiu(a2, 1);
    }
    // 0x003b4460
    charge(ctx, 2);
    v0 = 1;
    sb(v0, gp, fnt::kGpGslReady);  // 0x7CE64C
    // 0x003b4468 (the shared epilogue, written out on this path)
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
    return;
L_003b43dc_19:
    charge(ctx, 5);
    jal(ctx, 0x3B43DCu, gen::fn_sub_3B44A0_003b44a0);
    v0 = 0;
    // 0x003b4468 (the shared epilogue, written out on this path)
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

// 0x003B4D10 sub_3B4D10 -- 384 bytes; frame 0x90: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [itfPnlDrawFrame3] The name-plate frame of a panel (draw type 6): three slices of the rectangle $a0 (left cap of
// width $a3, the stretched middle, the right cap) through sub_3B4B40 with the UV sets 0x6A2A28 / 0x6A2A2C / 0x6A2A30
// of the plate raster gp-0x57C4 and the colour $a1.
void sub_3B4D10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b4d10
    enter(ctx, 96);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a2;
    s2 = a3;
    s1 = t0;
    lw(v0, a0, 8);
    lw(a3, a0, 0);
    v1 = subu(v0, a3);
    v0 = sll(s2, 1);
    s0 = subu(v1, v0);
    lw(a2, a1, 0);
    sw(a2, sp, 0x50);
    lw(v1, a1, 4);
    sw(v1, sp, 0x54);
    lw(v0, a1, 8);
    sw(v0, sp, 0x58);
    sw(zero, sp, 0x5C);
    sw(a2, sp, 0x60);
    sw(v1, sp, 0x64);
    sw(v0, sp, 0x68);
    lw(v0, a1, 12);
    sw(v0, sp, 0x6C);
    sw(a3, sp, 0x70);
    lw(v1, a0, 4);
    sw(v1, sp, 0x74);
    v0 = addu(a3, s2);
    sw(v0, sp, 0x78);
    sw(v1, sp, 0x7C);
    sw(v0, sp, 0x80);
    lw(v0, a0, 12);
    sw(v0, sp, 0x84);
    sw(a3, sp, 0x88);
    sw(v0, sp, 0x8C);
    a0 = addiu(sp, 0x70);
    a1 = addiu(sp, 0x50);
    a2 = addiu(gp, fnt::kGpPlateRaster);  // &0x7CD52C
    a3 = 0x6A0000;
    a3 = addiu(a3, fnt::kLoPlateUv0);  // &0x6A2A28
    t0 = s3;
    t1 = s1;
    jal(ctx, 0x3B4DC0u, gen::fn_sub_3B4B40_003b4b40);
    lw(v0, sp, 0x70);
    v0 = addu(v0, s2);
    sw(v0, sp, 0x70);
    lw(v0, sp, 0x78);
    v0 = addu(v0, s0);
    sw(v0, sp, 0x78);
    lw(v0, sp, 0x80);
    v0 = addu(v0, s0);
    sw(v0, sp, 0x80);
    lw(v0, sp, 0x88);
    v0 = addu(v0, s2);
    sw(v0, sp, 0x88);
    a0 = addiu(sp, 0x70);
    a1 = addiu(sp, 0x50);
    a2 = addiu(gp, fnt::kGpPlateRaster);  // &0x7CD52C
    a3 = 0x6A0000;
    a3 = addiu(a3, fnt::kLoPlateUv1);  // &0x6A2A2C
    t0 = s3;
    t1 = s1;
    jal(ctx, 0x3B4E14u, gen::fn_sub_3B4B40_003b4b40);
    lw(v0, sp, 0x70);
    v0 = addu(v0, s0);
    sw(v0, sp, 0x70);
    lw(v0, sp, 0x78);
    v0 = addu(v0, s2);
    sw(v0, sp, 0x78);
    lw(v0, sp, 0x80);
    v0 = addu(v0, s2);
    sw(v0, sp, 0x80);
    lw(v0, sp, 0x88);
    v0 = addu(v0, s0);
    sw(v0, sp, 0x88);
    a0 = addiu(sp, 0x70);
    a1 = addiu(sp, 0x50);
    a2 = addiu(gp, fnt::kGpPlateRaster);  // &0x7CD52C
    a3 = 0x6A0000;
    a3 = addiu(a3, fnt::kLoPlateUv2);  // &0x6A2A30
    t0 = s3;
    t1 = s1;
    jal(ctx, 0x3B4E68u, gen::fn_sub_3B4B40_003b4b40);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

}  // namespace p3fes::game
