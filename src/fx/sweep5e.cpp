// Phase 5 slice sweep5e: 143 functions of the wave-5 sweep (p3fes/game/sweep5e.h has the list of areas), hand
// decompiled from SLUS_216.21 with p3fes_handgen. Every body keeps the recompiled body's registers, frame, spills, $ra
// links, cycle charges and check points (game/include/p3fes/game/hg_cpu.h); on top: a role comment per function
// (proposed names in brackets, also in symbols/deltas/sweep5e.sym), the gBtl / btlUnit offsets the battle helpers use
// as named constants (namespace sweep5e), and the handgen block structure. Pair tests: tests/game/test_sweep5e.cpp.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/sweep5e.h"

namespace p3fes::recomp_gen {
void fn_H_Cdvd_Destroy_00100ec0(p3fes::EEContext&);
void fn_InvalidDCache_00503b98(p3fes::EEContext&);
void fn_MT_Misc_BitChk_003951d0(p3fes::EEContext&);
void fn_SyncDCache_00503a58(p3fes::EEContext&);
void fn_SyncDmaForRead_0051ade0(p3fes::EEContext&);
void fn_SyncDma_0051ad10(p3fes::EEContext&);
void fn__calloc_r_0051e178(p3fes::EEContext&);
void fn__decPicture_00500f98(p3fes::EEContext&);
void fn__realloc_r_00522fc0(p3fes::EEContext&);
void fn__rwDMAForceBufferSwap_004d4df0(p3fes::EEContext&);
void fn__sceMcCoreChangeSocketTypeDbc2Mc_0051c2e8(p3fes::EEContext&);
void fn__sceMcCoreCheckSocket_0051c250(p3fes::EEContext&);
void fn__sceMpegFlush_00501ae8(p3fes::EEContext&);
void fn__sceMpegNextHeader_004ff9d8(p3fes::EEContext&);
void fn__sceMpegOutputFrame_00501ba8(p3fes::EEContext&);
void fn__sceSignalSema_00503180(p3fes::EEContext&);
void fn__sceWaitSema_005031a0(p3fes::EEContext&);
void fn__updateRefImage_00500430(p3fes::EEContext&);
void fn_asinf_0052ea00(p3fes::EEContext&);
void fn_cosf_0052e6d8(p3fes::EEContext&);
void fn_datCalcChkBadStatus_00300580(p3fes::EEContext&);
void fn_datCalcGetHeldWeaponType_00308c60(p3fes::EEContext&);
void fn_datCalcIsDead_0030b5a0(p3fes::EEContext&);
void fn_datCalcRand_002ffbc0(p3fes::EEContext&);
void fn_datGetEquipmentIdx_0016cb80(p3fes::EEContext&);
void fn_datGetFlag_0016f190(p3fes::EEContext&);
void fn_datGetUnit_0016cd60(p3fes::EEContext&);
void fn_datSetFlag_0016f1f0(p3fes::EEContext&);
void fn_frSetMessageFontStyle_003b19a0(p3fes::EEContext&);
void fn_geometryLock_00493370(p3fes::EEContext&);
void fn_itfMesMngGetDialogueLine_003a5940(p3fes::EEContext&);
void fn_itfMesMngGetMessageEntry_003a50e0(p3fes::EEContext&);
void fn_itfMesMngPushMessageArgs_003a5fd0(p3fes::EEContext&);
void fn_itfMesMngTextGetMaxLineWidth_003a6460(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_name__C9type_info_1_004c21d0(p3fes::EEContext&);
void fn_nmCmdListCancelled_003c6c80(p3fes::EEContext&);
void fn_nmCmdListCloseNow_003c6f50(p3fes::EEContext&);
void fn_nmCmdListDecidedRow_003c6c50(p3fes::EEContext&);
void fn_nmCmdListHold_003c6ea0(p3fes::EEContext&);
void fn_nmCmdListMovedDownRow_003c6ce0(p3fes::EEContext&);
void fn_nmCmdListMovedUp_003c6cc0(p3fes::EEContext&);
void fn_nmCmdListPagedDown_003c6ca0(p3fes::EEContext&);
void fn_nmCmdListScrolledRow_003c6d10(p3fes::EEContext&);
void fn_nmListFindByKey_003c4b50(p3fes::EEContext&);
void fn_nmObjPayloadWord12_003c5460(p3fes::EEContext&);
void fn_nmSequenceAddStep_003c5240(p3fes::EEContext&);
void fn_printf_005225a8(p3fes::EEContext&);
void fn_sceDbcDeleteSocket_0051c8a0(p3fes::EEContext&);
void fn_sceDbcGetConnection_0051cad0(p3fes::EEContext&);
void fn_sceDbcSendData3_0051d308(p3fes::EEContext&);
void fn_sinf_0052e878(p3fes::EEContext&);
void fn_sprintf_00523ac8(p3fes::EEContext&);
void fn_strcpy_00524270(p3fes::EEContext&);
void fn_strlen_00524388(p3fes::EEContext&);
void fn_strncmp_00524670(p3fes::EEContext&);
void fn_sub_1052B0_001052b0(p3fes::EEContext&);
void fn_sub_109DF0_00109df0(p3fes::EEContext&);
void fn_sub_10A4E0_0010a4e0(p3fes::EEContext&);
void fn_sub_10A500_0010a500(p3fes::EEContext&);
void fn_sub_10C1A0_0010c1a0(p3fes::EEContext&);
void fn_sub_10C3A0_0010c3a0(p3fes::EEContext&);
void fn_sub_1192B0_001192b0(p3fes::EEContext&);
void fn_sub_16BA00_0016ba00(p3fes::EEContext&);
void fn_sub_16BA80_0016ba80(p3fes::EEContext&);
void fn_sub_16BB00_0016bb00(p3fes::EEContext&);
void fn_sub_16BB80_0016bb80(p3fes::EEContext&);
void fn_sub_16BC00_0016bc00(p3fes::EEContext&);
void fn_sub_16E9B0_0016e9b0(p3fes::EEContext&);
void fn_sub_16EA40_0016ea40(p3fes::EEContext&);
void fn_sub_16F490_0016f490(p3fes::EEContext&);
void fn_sub_16F630_0016f630(p3fes::EEContext&);
void fn_sub_170C00_00170c00(p3fes::EEContext&);
void fn_sub_171110_00171110(p3fes::EEContext&);
void fn_sub_171250_00171250(p3fes::EEContext&);
void fn_sub_171360_00171360(p3fes::EEContext&);
void fn_sub_171390_00171390(p3fes::EEContext&);
void fn_sub_174E70_00174e70(p3fes::EEContext&);
void fn_sub_17C590_0017c590(p3fes::EEContext&);
void fn_sub_17C610_0017c610(p3fes::EEContext&);
void fn_sub_17C670_0017c670(p3fes::EEContext&);
void fn_sub_17D800_0017d800(p3fes::EEContext&);
void fn_sub_198590_00198590(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_1A0040_001a0040(p3fes::EEContext&);
void fn_sub_1A0150_001a0150(p3fes::EEContext&);
void fn_sub_20D650_0020d650(p3fes::EEContext&);
void fn_sub_27ED20_0027ed20(p3fes::EEContext&);
void fn_sub_280050_00280050(p3fes::EEContext&);
void fn_sub_280480_00280480(p3fes::EEContext&);
void fn_sub_2812D0_002812d0(p3fes::EEContext&);
void fn_sub_282BC0_00282bc0(p3fes::EEContext&);
void fn_sub_282D40_00282d40(p3fes::EEContext&);
void fn_sub_2831C0_002831c0(p3fes::EEContext&);
void fn_sub_284200_00284200(p3fes::EEContext&);
void fn_sub_2D3FE0_002d3fe0(p3fes::EEContext&);
void fn_sub_2D5DC0_002d5dc0(p3fes::EEContext&);
void fn_sub_2D5E10_002d5e10(p3fes::EEContext&);
void fn_sub_2D7E20_002d7e20(p3fes::EEContext&);
void fn_sub_2E4220_002e4220(p3fes::EEContext&);
void fn_sub_2E4250_002e4250(p3fes::EEContext&);
void fn_sub_2EC590_002ec590(p3fes::EEContext&);
void fn_sub_2F6C50_002f6c50(p3fes::EEContext&);
void fn_sub_2F8460_002f8460(p3fes::EEContext&);
void fn_sub_2F8810_002f8810(p3fes::EEContext&);
void fn_sub_311310_00311310(p3fes::EEContext&);
void fn_sub_3142B0_003142b0(p3fes::EEContext&);
void fn_sub_3164F0_003164f0(p3fes::EEContext&);
void fn_sub_316910_00316910(p3fes::EEContext&);
void fn_sub_318A70_00318a70(p3fes::EEContext&);
void fn_sub_318A90_00318a90(p3fes::EEContext&);
void fn_sub_3192A0_003192a0(p3fes::EEContext&);
void fn_sub_319490_00319490(p3fes::EEContext&);
void fn_sub_3195F0_003195f0(p3fes::EEContext&);
void fn_sub_3196D0_003196d0(p3fes::EEContext&);
void fn_sub_31C000_0031c000(p3fes::EEContext&);
void fn_sub_31D6B0_0031d6b0(p3fes::EEContext&);
void fn_sub_31D700_0031d700(p3fes::EEContext&);
void fn_sub_31D7E0_0031d7e0(p3fes::EEContext&);
void fn_sub_31D900_0031d900(p3fes::EEContext&);
void fn_sub_31DFF0_0031dff0(p3fes::EEContext&);
void fn_sub_31E0B0_0031e0b0(p3fes::EEContext&);
void fn_sub_31E420_0031e420(p3fes::EEContext&);
void fn_sub_320230_00320230(p3fes::EEContext&);
void fn_sub_320880_00320880(p3fes::EEContext&);
void fn_sub_323240_00323240(p3fes::EEContext&);
void fn_sub_3233A0_003233a0(p3fes::EEContext&);
void fn_sub_3237C0_003237c0(p3fes::EEContext&);
void fn_sub_323860_00323860(p3fes::EEContext&);
void fn_sub_3238D0_003238d0(p3fes::EEContext&);
void fn_sub_323920_00323920(p3fes::EEContext&);
void fn_sub_329740_00329740(p3fes::EEContext&);
void fn_sub_329BA0_00329ba0(p3fes::EEContext&);
void fn_sub_32A120_0032a120(p3fes::EEContext&);
void fn_sub_32A540_0032a540(p3fes::EEContext&);
void fn_sub_3393D0_003393d0(p3fes::EEContext&);
void fn_sub_339530_00339530(p3fes::EEContext&);
void fn_sub_3395D0_003395d0(p3fes::EEContext&);
void fn_sub_339620_00339620(p3fes::EEContext&);
void fn_sub_339680_00339680(p3fes::EEContext&);
void fn_sub_349090_00349090(p3fes::EEContext&);
void fn_sub_349620_00349620(p3fes::EEContext&);
void fn_sub_34FD10_0034fd10(p3fes::EEContext&);
void fn_sub_34FDF0_0034fdf0(p3fes::EEContext&);
void fn_sub_3500A0_003500a0(p3fes::EEContext&);
void fn_sub_357E30_00357e30(p3fes::EEContext&);
void fn_sub_357FD0_00357fd0(p3fes::EEContext&);
void fn_sub_358030_00358030(p3fes::EEContext&);
void fn_sub_358340_00358340(p3fes::EEContext&);
void fn_sub_3A4360_003a4360(p3fes::EEContext&);
void fn_sub_3B0170_003b0170(p3fes::EEContext&);
void fn_sub_3B2900_003b2900(p3fes::EEContext&);
void fn_sub_3B2CB0_003b2cb0(p3fes::EEContext&);
void fn_sub_3B32D0_003b32d0(p3fes::EEContext&);
void fn_sub_3B5D10_003b5d10(p3fes::EEContext&);
void fn_sub_3B5D50_003b5d50(p3fes::EEContext&);
void fn_sub_3B7460_003b7460(p3fes::EEContext&);
void fn_sub_3BB010_003bb010(p3fes::EEContext&);
void fn_sub_3BB0C0_003bb0c0(p3fes::EEContext&);
void fn_sub_3C44D0_003c44d0(p3fes::EEContext&);
void fn_sub_3C5470_003c5470(p3fes::EEContext&);
void fn_sub_3C7E20_003c7e20(p3fes::EEContext&);
void fn_sub_3CA780_003ca780(p3fes::EEContext&);
void fn_sub_3CDCD0_003cdcd0(p3fes::EEContext&);
void fn_sub_3CDD80_003cdd80(p3fes::EEContext&);
void fn_sub_3CF8F0_003cf8f0(p3fes::EEContext&);
void fn_sub_3DFEB0_003dfeb0(p3fes::EEContext&);
void fn_sub_3DFF30_003dff30(p3fes::EEContext&);
void fn_sub_3E0C20_003e0c20(p3fes::EEContext&);
void fn_sub_3E5B00_003e5b00(p3fes::EEContext&);
void fn_sub_3E5E20_003e5e20(p3fes::EEContext&);
void fn_sub_3E6DC0_003e6dc0(p3fes::EEContext&);
void fn_sub_3F0D60_003f0d60(p3fes::EEContext&);
void fn_sub_3FCA00_003fca00(p3fes::EEContext&);
void fn_sub_3FD570_003fd570(p3fes::EEContext&);
void fn_sub_4026B0_004026b0(p3fes::EEContext&);
void fn_sub_402800_00402800(p3fes::EEContext&);
void fn_sub_402C80_00402c80(p3fes::EEContext&);
void fn_sub_403760_00403760(p3fes::EEContext&);
void fn_sub_403780_00403780(p3fes::EEContext&);
void fn_sub_4037A0_004037a0(p3fes::EEContext&);
void fn_sub_4037C0_004037c0(p3fes::EEContext&);
void fn_sub_403970_00403970(p3fes::EEContext&);
void fn_sub_404120_00404120(p3fes::EEContext&);
void fn_sub_40C520_0040c520(p3fes::EEContext&);
void fn_sub_40CA00_0040ca00(p3fes::EEContext&);
void fn_sub_40E3C0_0040e3c0(p3fes::EEContext&);
void fn_sub_40EB50_0040eb50(p3fes::EEContext&);
void fn_sub_41BEB0_0041beb0(p3fes::EEContext&);
void fn_sub_41BEE0_0041bee0(p3fes::EEContext&);
void fn_sub_468EA0_00468ea0(p3fes::EEContext&);
void fn_sub_469030_00469030(p3fes::EEContext&);
void fn_sub_4699B0_004699b0(p3fes::EEContext&);
void fn_sub_488F30_00488f30(p3fes::EEContext&);
void fn_sub_48D0E0_0048d0e0(p3fes::EEContext&);
void fn_sub_491100_00491100(p3fes::EEContext&);
void fn_sub_4916D0_004916d0(p3fes::EEContext&);
void fn_sub_491A80_00491a80(p3fes::EEContext&);
void fn_sub_491EA0_00491ea0(p3fes::EEContext&);
void fn_sub_4920A0_004920a0(p3fes::EEContext&);
void fn_sub_4933D0_004933d0(p3fes::EEContext&);
void fn_sub_4AAB40_004aab40(p3fes::EEContext&);
void fn_sub_4AAC70_004aac70(p3fes::EEContext&);
void fn_sub_4AAD50_004aad50(p3fes::EEContext&);
void fn_sub_4AB0C0_004ab0c0(p3fes::EEContext&);
void fn_sub_4AEF60_004aef60(p3fes::EEContext&);
void fn_sub_4B1A40_004b1a40(p3fes::EEContext&);
void fn_sub_4B1A60_004b1a60(p3fes::EEContext&);
void fn_sub_4B1A80_004b1a80(p3fes::EEContext&);
void fn_sub_4B1AE0_004b1ae0(p3fes::EEContext&);
void fn_sub_4B1B60_004b1b60(p3fes::EEContext&);
void fn_sub_4B3CC0_004b3cc0(p3fes::EEContext&);
void fn_sub_4B4A70_004b4a70(p3fes::EEContext&);
void fn_sub_4B4EB0_004b4eb0(p3fes::EEContext&);
void fn_sub_4B5380_004b5380(p3fes::EEContext&);
void fn_sub_4B6A40_004b6a40(p3fes::EEContext&);
void fn_sub_4B6DD0_004b6dd0(p3fes::EEContext&);
void fn_sub_4B6E10_004b6e10(p3fes::EEContext&);
void fn_sub_4B6EB0_004b6eb0(p3fes::EEContext&);
void fn_sub_4B6EC0_004b6ec0(p3fes::EEContext&);
void fn_sub_4B7010_004b7010(p3fes::EEContext&);
void fn_sub_4B7020_004b7020(p3fes::EEContext&);
void fn_sub_4B7240_004b7240(p3fes::EEContext&);
void fn_sub_4B74C0_004b74c0(p3fes::EEContext&);
void fn_sub_4B7760_004b7760(p3fes::EEContext&);
void fn_sub_4B77F0_004b77f0(p3fes::EEContext&);
void fn_sub_4B79D0_004b79d0(p3fes::EEContext&);
void fn_sub_4B92D0_004b92d0(p3fes::EEContext&);
void fn_sub_4B9350_004b9350(p3fes::EEContext&);
void fn_sub_4B9370_004b9370(p3fes::EEContext&);
void fn_sub_4B96F0_004b96f0(p3fes::EEContext&);
void fn_sub_4B97B0_004b97b0(p3fes::EEContext&);
void fn_sub_4B97D0_004b97d0(p3fes::EEContext&);
void fn_sub_4BDA10_004bda10(p3fes::EEContext&);
void fn_sub_4BDDE0_004bdde0(p3fes::EEContext&);
void fn_sub_4C1600_004c1600(p3fes::EEContext&);
void fn_sub_4C1970_004c1970(p3fes::EEContext&);
void fn_sub_4C1C50_004c1c50(p3fes::EEContext&);
void fn_sub_4C1D10_004c1d10(p3fes::EEContext&);
void fn_sub_4C2080_004c2080(p3fes::EEContext&);
void fn_sub_4C2090_004c2090(p3fes::EEContext&);
void fn_sub_4C20B0_004c20b0(p3fes::EEContext&);
void fn_sub_4C2120_004c2120(p3fes::EEContext&);
void fn_sub_4C21B0_004c21b0(p3fes::EEContext&);
void fn_sub_4C21E0_004c21e0(p3fes::EEContext&);
void fn_sub_4C2F30_004c2f30(p3fes::EEContext&);
void fn_sub_4C31B0_004c31b0(p3fes::EEContext&);
void fn_sub_4C32A0_004c32a0(p3fes::EEContext&);
void fn_sub_4C33D0_004c33d0(p3fes::EEContext&);
void fn_sub_4C35D0_004c35d0(p3fes::EEContext&);
void fn_sub_4C5250_004c5250(p3fes::EEContext&);
void fn_sub_4C5620_004c5620(p3fes::EEContext&);
void fn_sub_4C5780_004c5780(p3fes::EEContext&);
void fn_sub_4C58A0_004c58a0(p3fes::EEContext&);
void fn_sub_4C69F0_004c69f0(p3fes::EEContext&);
void fn_sub_4C6BE0_004c6be0(p3fes::EEContext&);
void fn_sub_4C6C60_004c6c60(p3fes::EEContext&);
void fn_sub_4C8680_004c8680(p3fes::EEContext&);
void fn_sub_4CB750_004cb750(p3fes::EEContext&);
void fn_sub_4CB7F0_004cb7f0(p3fes::EEContext&);
void fn_sub_4CB890_004cb890(p3fes::EEContext&);
void fn_sub_4CDE00_004cde00(p3fes::EEContext&);
void fn_sub_4CDE40_004cde40(p3fes::EEContext&);
void fn_sub_4CDF30_004cdf30(p3fes::EEContext&);
void fn_sub_4CE200_004ce200(p3fes::EEContext&);
void fn_sub_4D0D10_004d0d10(p3fes::EEContext&);
void fn_sub_4D0DC0_004d0dc0(p3fes::EEContext&);
void fn_sub_4D9520_004d9520(p3fes::EEContext&);
void fn_sub_4D9BC0_004d9bc0(p3fes::EEContext&);
void fn_sub_4DB200_004db200(p3fes::EEContext&);
void fn_sub_4EB8C0_004eb8c0(p3fes::EEContext&);
void fn_sub_4EBB40_004ebb40(p3fes::EEContext&);
void fn_sub_4EF1D0_004ef1d0(p3fes::EEContext&);
void fn_sub_4F1540_004f1540(p3fes::EEContext&);
void fn_sub_4F1780_004f1780(p3fes::EEContext&);
void fn_sub_5383E8_005383e8(p3fes::EEContext&);
void fn_sub_5383F0_005383f0(p3fes::EEContext&);
void fn_sub_539818_00539818(p3fes::EEContext&);
void fn_sub_539830_00539830(p3fes::EEContext&);
void fn_sub_561640_00561640(p3fes::EEContext&);
void fn_width__CQ24_STL8ios_base_00537fe8(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// 0x002E3AE0 sub_2E3AE0 -- 52 bytes; frame 0x10: ra sp+0x0
// Battle (gBtl = *0x7CE3EC): stores sub_1192B0(gBtl+3352, a0) into gBtl+3364 (refreshes a battle-context handle).
void sub_2E3AE0(EEContext& ctx) {
    using namespace sweep5e;
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e3ae0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a1 = a0;
    lw(v0, gp, -18692);  // 0x7CE3EC
    lw(a0, v0, kBtlCtxHandle);
    jal(ctx, 0x2E3AF4u, gen::fn_sub_1192B0_001192b0);
    lw(v1, gp, -18692);  // 0x7CE3EC
    sw(v0, v1, kBtlCtxResult);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002E97E0 sub_2E97E0 -- 364 bytes; frame 0x60: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Battle (gBtl = *0x7CE3EC): walks the unit list (gBtl+344, next at +2612); for live units (datCalcIsDead == 0) whose
// kind word +164 is 256 it picks a focus position (sub_2D5DC0 / sub_2D7E20) and hands it to the camera (sub_27ED20 /
// sub_284200).
void sub_2E97E0(EEContext& ctx) {
    using namespace sweep5e;
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x002e97e0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = 0;
    lw(v0, gp, -18692);  // 0x7CE3EC
    lw(s0, v0, 344);
    for (;;) {
        // 0x002e9840
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002e9808
        charge(ctx, 4);
        lhu(v1, s0, kUnitId);
        v0 = 256;
        if (v1 == v0) {
            // 0x002e9818
            charge(ctx, 6);
            lw(a0, s0, kUnitData);
            a1 = 0;
            jal(ctx, 0x2E9820u, gen::fn_datCalcIsDead_0030b5a0);
            if (v0 == 0) {
                goto L_002e983c;
            }
            goto L_002e9830_3;
        }
    L_002e983c:
        charge(ctx, 1);
        lw(s0, s0, kUnitNext);
    }
L_002e9848:
    charge(ctx, 2);
    if (s1 != 0) {
        // 0x002e9850
        charge(ctx, 10);
        a0 = addiu(sp, 0x40);
        jal(ctx, 0x2E9854u, gen::fn_sub_2D5DC0_002d5dc0);
        v0 = lui(0xFFF0);
        v0 = v0 | 0x1;
        sw(v0, sp, 0x40);
        lw(v0, gp, -18692);  // 0x7CE3EC
        lw(s2, v0, 332);
        for (;;) {
            // 0x002e9924
            charge(ctx, 2);
            if (s2 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002e9878
            charge(ctx, 4);
            lhu(v0, s2, 26);
            v0 = v0 & 0x1;
            if (v0 != 0) {
                // 0x002e9888
                charge(ctx, 5);
                lw(s0, s2, 48);
                lbu(v1, s0, 162);
                v0 = 1;
                if (v1 == v0) {
                    // 0x002e989c
                    charge(ctx, 4);
                    lhu(v1, s0, kUnitId);
                    v0 = 256;
                    if (v1 != v0) {
                        // 0x002e98ac
                        charge(ctx, 6);
                        lw(a0, s0, kUnitData);
                        a1 = 0;
                        jal(ctx, 0x2E98B4u, gen::fn_datCalcIsDead_0030b5a0);
                        if (v0 == 0) {
                            // 0x002e98c4
                            charge(ctx, 23);
                            a0 = s2;
                            a1 = s2;
                            a2 = addiu(sp, 0x40);
                            a3 = 1;
                            t0 = a3;
                            jal(ctx, 0x2E98D8u, gen::fn_sub_2D7E20_002d7e20);
                            a0 = v0;
                            a1 = 1;
                            jal(ctx, 0x2E98E8u, gen::fn_sub_27ED20_0027ed20);
                            v0 = 0x3F800000;
                            mtc1(v0, f12);
                            a0 = s0;
                            a1 = 2;
                            a2 = 0;
                            a3 = 0;
                            jal(ctx, 0x2E9908u, gen::fn_sub_284200_00284200);
                            a0 = v0;
                            a1 = 1;
                            jal(ctx, 0x2E9918u, gen::fn_sub_27ED20_0027ed20);
                        }
                    }
                }
            }
            // 0x002e9920
            charge(ctx, 1);
            lw(s2, s2, 1192);
        }
    }
    // 0x002e992c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    v0 = s1;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
L_002e9830_3:
    charge(ctx, 3);
    s1 = 1;
    goto L_002e9848;
}

// 0x002EAA40 sub_2EAA40 -- 292 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Battle (gBtl = *0x7CE3EC): per-unit pass over the unit list updating each unit's attachments (sub_2D3FE0,
// sub_3195F0, sub_2831C0, sub_282D40, sub_282BC0).
void sub_2EAA40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x002eaa40
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = 0;
    s1 = 0;
    s0 = 0;
    lw(v0, gp, -18692);  // 0x7CE3EC
    lw(s3, v0, 344);
    for (;;) {
        // 0x002eaadc
        charge(ctx, 2);
        if (s3 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002eaa74
        charge(ctx, 4);
        lhu(v1, s3, 164);
        v0 = 277;
        if (v1 == v0) {
            // 0x002eaad4
            charge(ctx, 1);
            s2 = s3;
        } else {
            // 0x002eaa84
            charge(ctx, 3);
            v0 = 262;
            if (v1 == v0) {
                // 0x002eaabc
                charge(ctx, 6);
                lw(s0, s3, 2548);
                a0 = s3;
                jal(ctx, 0x2EAAC4u, gen::fn_sub_2D3FE0_002d3fe0);
            } else {
                // 0x002eaa90
                charge(ctx, 3);
                v0 = 261;
                if (v1 == v0) {
                    // 0x002eaaa4
                    charge(ctx, 6);
                    lw(s1, s3, 2548);
                    a0 = s3;
                    jal(ctx, 0x2EAAACu, gen::fn_sub_2D3FE0_002d3fe0);
                } else {
                    // 0x002eaa9c
                    charge(ctx, 2);
                }
            }
        }
        // 0x002eaad8
        charge(ctx, 1);
        lw(s3, s3, 2612);
    }
    // 0x002eaae4
    charge(ctx, 32);
    lw(a0, s2, 2548);
    a1 = 0;
    a2 = s1;
    jal(ctx, 0x2EAAF0u, gen::fn_sub_3195F0_003195f0);
    lw(a0, s2, 2548);
    a1 = 1;
    a2 = s0;
    jal(ctx, 0x2EAB04u, gen::fn_sub_3195F0_003195f0);
    a0 = s2;
    a1 = 0;
    jal(ctx, 0x2EAB14u, gen::fn_sub_2831C0_002831c0);
    lb(a3, s2, 2536);
    a0 = s2;
    lh(a1, s2, 2528);
    a2 = 0;
    lwc1(f12, s2, 2532);
    jal(ctx, 0x2EAB30u, gen::fn_sub_282D40_00282d40);
    a0 = s2;
    jal(ctx, 0x2EAB3Cu, gen::fn_sub_282BC0_00282bc0);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x002EC190 sub_2EC190 -- 304 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Battle (gBtl = *0x7CE3EC): action hook: for an actor (a0+48) with byte +162 == 1 with id +164 == 263 and flag 0x80 in
// the action word a2+26, clears gBtl+2884, then runs sub_2EC590.
void sub_2EC190(EEContext& ctx) {
    using namespace sweep5e;
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002ec190
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a2;
    lw(a2, a0, 48);
    lbu(a0, a2, 162);
    v1 = 1;
    if (a0 == v1) {
        // 0x002ec1b4
        charge(ctx, 4);
        lhu(a0, a2, 164);
        v1 = 263;
        if (a0 == v1) {
            // 0x002ec1c4
            charge(ctx, 4);
            lhu(v1, s0, 26);
            v1 = v1 & 0x80;
            if (v1 != 0) {
                // 0x002ec1d4
                charge(ctx, 2);
                lw(v1, gp, -18692);  // 0x7CE3EC
                sw(zero, v1, 2884);
            }
        }
    }
    // 0x002ec1dc
    charge(ctx, 5);
    lw(a1, a1, 48);
    lbu(a0, a1, 162);
    v1 = 1;
    if (a0 == v1) {
        // 0x002ec1f0
        charge(ctx, 4);
        lhu(a0, a1, 164);
        v1 = 263;
        if (a0 == v1) {
            // 0x002ec200
            charge(ctx, 5);
            lw(a0, s0, 8);
            v1 = 0x100000;
            v1 = a0 & v1;
            if (v1 == 0) {
                // 0x002ec230
                charge(ctx, 3);
                lw(v1, s0, 0);
                if (i64(v1) < 0) {
                    // 0x002ec23c
                    charge(ctx, 5);
                    jal(ctx, 0x2EC23Cu, gen::fn_sub_2EC590_002ec590);
                    v1 = 1;
                    if (v0 == v1) {
                        // 0x002ec250
                        charge(ctx, 6);
                        lw(v1, gp, -18692);  // 0x7CE3EC
                        a0 = addiu(v1, 2896);
                        lh(v1, v1, 2896);
                        at = slti(v1, 2);
                        if (at != 0) {
                            // 0x002ec268
                            charge(ctx, 2);
                            v1 = addiu(v1, 1);
                            sh(v1, a0, 0);
                        }
                    }
                }
            } else {
                // 0x002ec214
                charge(ctx, 7);
                lw(v1, gp, -18692);  // 0x7CE3EC
                sw(zero, v1, 2884);
                a0 = 2;
                lw(v1, gp, -18692);  // 0x7CE3EC
                sh(a0, v1, 2896);
            }
            // 0x002ec270
            charge(ctx, 3);
            lw(a2, s0, 0);
            if (i64(a2) < 0) {
                // 0x002ec27c
                charge(ctx, 7);
                lw(v1, gp, -18692);  // 0x7CE3EC
                a1 = addiu(v1, 2888);
                lw(a0, v1, 2888);
                v1 = subu(0, a2);
                at = slt(v1, a0);
                if (at == 0) {
                    // 0x002ec2a8
                    charge(ctx, 1);
                    sw(zero, a1, 0);
                } else {
                    // 0x002ec298
                    charge(ctx, 4);
                    v1 = addu(a0, a2);
                    sw(v1, a1, 0);
                }
            }
        }
    }
    // 0x002ec2ac (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002EEE20 sub_2EEE20 -- 472 bytes; frame 0x80: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Battle (gBtl = *0x7CE3EC): skill-table (gBtlSkillTbl 0x7CE3F8) placement: positions an effect between the actor and
// the target (sub_280050 / sub_280480 / sub_2812D0) and builds its matrix (sub_4C69F0).
void sub_2EEE20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x002eee20
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    lw(s0, a0, 48);
    lbu(v0, s0, 162);
    a0 = 1;
    if (v0 == a0) {
        // 0x002eee60
        charge(ctx, 4);
        lhu(v1, s0, 164);
        v0 = 268;
        if (v1 == v0) {
            // 0x002eee7c
            charge(ctx, 3);
            lhu(v0, s2, 106);
            if (v0 == a0) {
                // 0x002eee94
                charge(ctx, 4);
                lhu(v1, s2, 108);
                v0 = 2;
                if (v1 == v0) {
                    // 0x002eeeb0
                    charge(ctx, 12);
                    lhu(v1, s2, 110);
                    v0 = sll(v1, 2);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 1);
                    v0 = addu(v0, v1);
                    v1 = sll(v0, 2);
                    lw(v0, gp, -18680);  // gBtlSkillTbl
                    v0 = addu(v0, v1);
                    lbu(v0, v0, 0);
                    v0 = v0 & 0x2;
                    if (v0 != 0) {
                        // 0x002eeeec
                        charge(ctx, 29);
                        lw(v0, s2, 56);
                        lw(s3, v0, 48);
                        a0 = s0;
                        a1 = addiu(sp, 0x70);
                        jal(ctx, 0x2EEEFCu, gen::fn_sub_280050_00280050);
                        a0 = s3;
                        a1 = s0;
                        a2 = addiu(sp, 0x60);
                        jal(ctx, 0x2EEF10u, gen::fn_sub_280480_00280480);
                        lwc1(f1, sp, 0x70);
                        lwc1(f0, sp, 0x60);
                        sub_s(f0, f1, f0);
                        swc1(f0, sp, 0x50);
                        lwc1(f1, sp, 0x78);
                        lwc1(f0, sp, 0x68);
                        sub_s(f0, f1, f0);
                        swc1(f0, sp, 0x58);
                        sw(zero, sp, 0x54);
                        a0 = addiu(sp, 0x50);
                        a1 = a0;
                        jal(ctx, 0x2EEF44u, gen::fn_sub_4C69F0_004c69f0);
                        a0 = s2;
                        jal(ctx, 0x2EEF50u, gen::fn_sub_2D5E10_002d5e10);
                        if (v0 == 0) {
                            // 0x002eef6c
                            charge(ctx, 1);
                            v0 = 4;
                        } else {
                            // 0x002eef60
                            charge(ctx, 3);
                            v0 = 11;
                        }
                        // 0x002eef70
                        charge(ctx, 26);
                        a2 = v0 & 0xFFFF;
                        a0 = s0;
                        a1 = s3;
                        jal(ctx, 0x2EEF7Cu, gen::fn_sub_2812D0_002812d0);
                        lwc1(f1, sp, 0x50);
                        mul_s(f2, f1, f0);
                        swc1(f2, sp, 0x50);
                        lwc1(f1, sp, 0x54);
                        mul_s(f1, f1, f0);
                        swc1(f1, sp, 0x54);
                        lwc1(f1, sp, 0x58);
                        mul_s(f0, f1, f0);
                        swc1(f0, sp, 0x58);
                        lwc1(f0, sp, 0x60);
                        add_s(f0, f0, f2);
                        swc1(f0, s1, 0);
                        lwc1(f1, sp, 0x64);
                        lwc1(f0, sp, 0x54);
                        add_s(f0, f1, f0);
                        swc1(f0, s1, 4);
                        lwc1(f1, sp, 0x68);
                        lwc1(f0, sp, 0x58);
                        add_s(f0, f1, f0);
                        swc1(f0, s1, 8);
                        v0 = 1;
                    } else {
                        // 0x002eeee0
                        charge(ctx, 3);
                        v0 = 0;
                    }
                } else {
                    // 0x002eeea4
                    charge(ctx, 3);
                    v0 = 0;
                }
            } else {
                // 0x002eee88
                charge(ctx, 3);
                v0 = 0;
            }
        } else {
            // 0x002eee70
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x002eee54
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x002eefd8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x002EF9D0 sub_2EF9D0 -- 364 bytes; frame 0x60: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Battle (gBtl = *0x7CE3EC): twin of sub_2E97E0 for the other focus mode (same unit walk and camera calls).
void sub_2EF9D0(EEContext& ctx) {
    using namespace sweep5e;
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x002ef9d0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = 0;
    lw(v0, gp, -18692);  // 0x7CE3EC
    lw(s0, v0, 344);
    for (;;) {
        // 0x002efa30
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002ef9f8
        charge(ctx, 4);
        lhu(v1, s0, kUnitId);
        v0 = 269;
        if (v1 == v0) {
            // 0x002efa08
            charge(ctx, 6);
            lw(a0, s0, kUnitData);
            a1 = 0;
            jal(ctx, 0x2EFA10u, gen::fn_datCalcIsDead_0030b5a0);
            if (v0 == 0) {
                goto L_002efa2c;
            }
            goto L_002efa20_3;
        }
    L_002efa2c:
        charge(ctx, 1);
        lw(s0, s0, kUnitNext);
    }
L_002efa38:
    charge(ctx, 2);
    if (s1 != 0) {
        // 0x002efa40
        charge(ctx, 10);
        a0 = addiu(sp, 0x40);
        jal(ctx, 0x2EFA44u, gen::fn_sub_2D5DC0_002d5dc0);
        v0 = lui(0xFFF0);
        v0 = v0 | 0x1;
        sw(v0, sp, 0x40);
        lw(v0, gp, -18692);  // 0x7CE3EC
        lw(s2, v0, 332);
        for (;;) {
            // 0x002efb14
            charge(ctx, 2);
            if (s2 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002efa68
            charge(ctx, 4);
            lhu(v0, s2, 26);
            v0 = v0 & 0x1;
            if (v0 != 0) {
                // 0x002efa78
                charge(ctx, 5);
                lw(s0, s2, 48);
                lbu(v1, s0, 162);
                v0 = 1;
                if (v1 == v0) {
                    // 0x002efa8c
                    charge(ctx, 4);
                    lhu(v1, s0, kUnitId);
                    v0 = 269;
                    if (v1 != v0) {
                        // 0x002efa9c
                        charge(ctx, 6);
                        lw(a0, s0, kUnitData);
                        a1 = 0;
                        jal(ctx, 0x2EFAA4u, gen::fn_datCalcIsDead_0030b5a0);
                        if (v0 == 0) {
                            // 0x002efab4
                            charge(ctx, 23);
                            a0 = s2;
                            a1 = s2;
                            a2 = addiu(sp, 0x40);
                            a3 = 1;
                            t0 = a3;
                            jal(ctx, 0x2EFAC8u, gen::fn_sub_2D7E20_002d7e20);
                            a0 = v0;
                            a1 = 1;
                            jal(ctx, 0x2EFAD8u, gen::fn_sub_27ED20_0027ed20);
                            v0 = 0x3F800000;
                            mtc1(v0, f12);
                            a0 = s0;
                            a1 = 2;
                            a2 = 0;
                            a3 = 0;
                            jal(ctx, 0x2EFAF8u, gen::fn_sub_284200_00284200);
                            a0 = v0;
                            a1 = 1;
                            jal(ctx, 0x2EFB08u, gen::fn_sub_27ED20_0027ed20);
                        }
                    }
                }
            }
            // 0x002efb10
            charge(ctx, 1);
            lw(s2, s2, 1192);
        }
    }
    // 0x002efb1c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    v0 = s1;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
L_002efa20_3:
    charge(ctx, 3);
    s1 = 1;
    goto L_002efa38;
}

// 0x002EFB40 sub_2EFB40 -- 332 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Battle (gBtl = *0x7CE3EC): btlUnit $a0: for a unit with byte +162 == 1 with flag bit 1 at +152 and id +164 in {281, 295}, the
// gBtl+2904 / +2908 word (index: id != 281) becomes datCalcChkBadStatus(unit+2604, 1024) != 0 (1 set, 0 cleared).
void sub_2EFB40(EEContext& ctx) {
    using namespace sweep5e;
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002efb40
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lbu(a0, a0, kUnitByte162);
    v1 = 1;
    if (a0 == v1) {
        // 0x002efb60
        charge(ctx, 4);
        lw(v1, s0, kUnitFlags);
        v1 = v1 & 0x2;
        if (v1 != 0) {
            // 0x002efb70
            charge(ctx, 4);
            lhu(a0, s0, kUnitId);
            v1 = 295;
            if (a0 != v1) {
                // 0x002efb80
                charge(ctx, 3);
                v1 = 281;
                if (a0 == v1) {
                    goto L_002efb94;
                }
                // 0x002efb8c
                charge(ctx, 2);
                // 0x002efc78 (the shared epilogue, written out on this path)
                charge(ctx, 5);
                ld(ra, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x20);
                return;
            }
        L_002efb94:
            charge(ctx, 6);
            lw(a0, s0, kUnitData);
            a1 = 1024;
            jal(ctx, 0x2EFB9Cu, gen::fn_datCalcChkBadStatus_00300580);
            if (v0 == 0) {
                // 0x002efbd4
                charge(ctx, 7);
                lhu(v1, s0, kUnitId);
                v1 = v1 ^ 0x119;
                v1 = sltu(0, v1);
                a0 = sll(v1, 2);
                lw(v1, gp, -18692);  // 0x7CE3EC
                v1 = addu(a0, v1);
                sw(zero, v1, kBtlStatusFlags);
            } else {
                // 0x002efbac
                charge(ctx, 10);
                a1 = 1;
                lhu(v1, s0, kUnitId);
                v1 = v1 ^ 0x119;
                v1 = sltu(0, v1);
                a0 = sll(v1, 2);
                lw(v1, gp, -18692);  // 0x7CE3EC
                v1 = addu(a0, v1);
                sw(a1, v1, kBtlStatusFlags);
            }
            // 0x002efbf0
            charge(ctx, 9);
            lhu(v1, s0, kUnitId);
            v1 = v1 ^ 0x119;
            v1 = sltu(0, v1);
            a0 = sll(v1, 2);
            lw(v1, gp, -18692);  // 0x7CE3EC
            v1 = addu(a0, v1);
            lw(v1, v1, kBtlStatusFlags);
            if (v1 == 0) {
                // 0x002efc4c
                charge(ctx, 6);
                lw(v1, s0, 2548);
                a0 = addiu(v1, 1053);
                lbu(v1, v1, 1053);
                at = slti(v1, 33);
                if (at != 0) {
                    // 0x002efc74
                    charge(ctx, 1);
                    sb(zero, a0, 0);
                } else {
                    // 0x002efc64
                    charge(ctx, 4);
                    v1 = addiu(v1, -32);
                    sb(v1, a0, 0);
                }
            } else {
                // 0x002efc14
                charge(ctx, 6);
                lw(v1, s0, 2548);
                a0 = addiu(v1, 1053);
                lbu(v1, v1, 1053);
                at = slti(v1, 223);
                if (at == 0) {
                    // 0x002efc3c
                    charge(ctx, 4);
                    v1 = 255;
                    sb(v1, a0, 0);
                } else {
                    // 0x002efc2c
                    charge(ctx, 4);
                    v1 = addiu(v1, 32);
                    sb(v1, a0, 0);
                }
            }
        }
    }
    // 0x002efc78 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002F1B60 sub_2F1B60 -- 472 bytes; frame 0x80: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Battle (gBtl = *0x7CE3EC): twin of sub_2EEE20 (same skill-table placement for the second effect slot).
void sub_2F1B60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x002f1b60
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    lw(s0, a0, 48);
    lbu(v0, s0, 162);
    a0 = 1;
    if (v0 == a0) {
        // 0x002f1ba0
        charge(ctx, 4);
        lhu(v1, s0, 164);
        v0 = 271;
        if (v1 == v0) {
            // 0x002f1bbc
            charge(ctx, 3);
            lhu(v0, s2, 106);
            if (v0 == a0) {
                // 0x002f1bd4
                charge(ctx, 4);
                lhu(v1, s2, 108);
                v0 = 2;
                if (v1 == v0) {
                    // 0x002f1bf0
                    charge(ctx, 12);
                    lhu(v1, s2, 110);
                    v0 = sll(v1, 2);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 1);
                    v0 = addu(v0, v1);
                    v1 = sll(v0, 2);
                    lw(v0, gp, -18680);  // gBtlSkillTbl
                    v0 = addu(v0, v1);
                    lbu(v0, v0, 0);
                    v0 = v0 & 0x2;
                    if (v0 != 0) {
                        // 0x002f1c2c
                        charge(ctx, 29);
                        lw(v0, s2, 56);
                        lw(s3, v0, 48);
                        a0 = s0;
                        a1 = addiu(sp, 0x70);
                        jal(ctx, 0x2F1C3Cu, gen::fn_sub_280050_00280050);
                        a0 = s3;
                        a1 = s0;
                        a2 = addiu(sp, 0x60);
                        jal(ctx, 0x2F1C50u, gen::fn_sub_280480_00280480);
                        lwc1(f1, sp, 0x70);
                        lwc1(f0, sp, 0x60);
                        sub_s(f0, f1, f0);
                        swc1(f0, sp, 0x50);
                        lwc1(f1, sp, 0x78);
                        lwc1(f0, sp, 0x68);
                        sub_s(f0, f1, f0);
                        swc1(f0, sp, 0x58);
                        sw(zero, sp, 0x54);
                        a0 = addiu(sp, 0x50);
                        a1 = a0;
                        jal(ctx, 0x2F1C84u, gen::fn_sub_4C69F0_004c69f0);
                        a0 = s2;
                        jal(ctx, 0x2F1C90u, gen::fn_sub_2D5E10_002d5e10);
                        if (v0 == 0) {
                            // 0x002f1cac
                            charge(ctx, 1);
                            v0 = 4;
                        } else {
                            // 0x002f1ca0
                            charge(ctx, 3);
                            v0 = 11;
                        }
                        // 0x002f1cb0
                        charge(ctx, 26);
                        a2 = v0 & 0xFFFF;
                        a0 = s0;
                        a1 = s3;
                        jal(ctx, 0x2F1CBCu, gen::fn_sub_2812D0_002812d0);
                        lwc1(f1, sp, 0x50);
                        mul_s(f2, f1, f0);
                        swc1(f2, sp, 0x50);
                        lwc1(f1, sp, 0x54);
                        mul_s(f1, f1, f0);
                        swc1(f1, sp, 0x54);
                        lwc1(f1, sp, 0x58);
                        mul_s(f0, f1, f0);
                        swc1(f0, sp, 0x58);
                        lwc1(f0, sp, 0x60);
                        add_s(f0, f0, f2);
                        swc1(f0, s1, 0);
                        lwc1(f1, sp, 0x64);
                        lwc1(f0, sp, 0x54);
                        add_s(f0, f1, f0);
                        swc1(f0, s1, 4);
                        lwc1(f1, sp, 0x68);
                        lwc1(f0, sp, 0x58);
                        add_s(f0, f1, f0);
                        swc1(f0, s1, 8);
                        v0 = 1;
                    } else {
                        // 0x002f1c20
                        charge(ctx, 3);
                        v0 = 0;
                    }
                } else {
                    // 0x002f1be4
                    charge(ctx, 3);
                    v0 = 0;
                }
            } else {
                // 0x002f1bc8
                charge(ctx, 3);
                v0 = 0;
            }
        } else {
            // 0x002f1bb0
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x002f1b94
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x002f1d18 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x002F5BF0 sub_2F5BF0 -- 396 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Battle (gBtl = *0x7CE3EC): scans the action record a2 for the step kinds of sub_2F6840 / sub_2F6AB0 and forwards
// them (sub_2E4250 / sub_2E4220).
void sub_2F5BF0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002f5bf0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    v1 = 0;
    lw(t0, a0, 48);
    lbu(a3, t0, 162);
    t1 = 1;
    if (a3 == t1) {
        // 0x002f5c14
        charge(ctx, 4);
        lhu(t0, t0, 164);
        a3 = 241;
        if (t0 != a3) {
            goto L_002f5cc0;
        }
        // 0x002f5c24
        charge(ctx, 4);
        lhu(a2, a2, 26);
        a1 = a2 & 0x100;
        if (a1 != 0) {
            // 0x002f5c34
            charge(ctx, 2);
            s0 = a0;
            v1 = t1;
        }
        // 0x002f5c3c
        charge(ctx, 3);
        a1 = a2 & 0x200;
        if (a1 != 0) {
            // 0x002f5c48
            charge(ctx, 9);
            t0 = 1;
            lw(a1, gp, -18692);  // 0x7CE3EC
            sw(t0, a1, 2888);
            lw(a1, gp, -18692);  // 0x7CE3EC
            lw(t1, a1, 344);
            a2 = 10;
            a3 = 242;
            for (;;) {
                // 0x002f5c9c
                charge(ctx, 2);
                if (t1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x002f5c6c
                charge(ctx, 3);
                lhu(a1, t1, 164);
                if (a1 == a3) {
                    // 0x002f5c78
                    charge(ctx, 8);
                    lw(a1, gp, -18692);  // 0x7CE3EC
                    sw(t0, a1, 2896);
                    lw(a1, gp, -18692);  // 0x7CE3EC
                    sh(zero, a1, 2900);
                    lw(a1, gp, -18692);  // 0x7CE3EC
                    sh(a2, a1, 2902);
                    lw(a1, gp, -18692);  // 0x7CE3EC
                    sh(zero, a1, 2904);
                }
                // 0x002f5c98
                charge(ctx, 1);
                lw(t1, t1, 2612);
            }
            // 0x002f5ca4
            charge(ctx, 7);
            lw(a0, a0, 48);
            lw(a1, a0, 2604);
            lhu(a0, a1, 0);
            a0 = a0 | 0x40;
            sh(a0, a1, 0);
        }
        goto L_002f5d34;
    }
L_002f5cc0:
    charge(ctx, 5);
    lw(a3, a1, 48);
    lbu(a0, a3, 162);
    t1 = 1;
    if (a0 == t1) {
        // 0x002f5cd4
        charge(ctx, 4);
        lhu(a3, a3, 164);
        a0 = 241;
        if (a3 == a0) {
            // 0x002f5ce4
            charge(ctx, 3);
            lw(t0, a2, 0);
            if (i64(t0) < 0) {
                // 0x002f5cf0
                charge(ctx, 4);
                lw(a2, gp, -18692);  // 0x7CE3EC
                lw(a0, a2, 2888);
                if (a0 == t1) {
                    // 0x002f5d00
                    charge(ctx, 6);
                    a3 = addiu(a2, 2892);
                    lw(a2, a2, 2892);
                    a0 = subu(0, t0);
                    at = slt(a0, a2);
                    if (at == 0) {
                        // 0x002f5d28
                        charge(ctx, 3);
                        sw(zero, a3, 0);
                        s0 = a1;
                        v1 = t1;
                    } else {
                        // 0x002f5d18
                        charge(ctx, 4);
                        a0 = addu(a2, t0);
                        sw(a0, a3, 0);
                    }
                }
            }
        }
    }
L_002f5d34:
    charge(ctx, 2);
    if (v1 != 0) {
        // 0x002f5d3c
        charge(ctx, 4);
        jal(ctx, 0x2F5D3Cu, gen::fn_sub_2E4250_002e4250);
        if (v0 == 0) {
            // 0x002f5d4c
            charge(ctx, 7);
            a0 = 0x2F0000;
            a0 = addiu(a0, 26688);  // &sub_2F6840
            a1 = 0x2F0000;
            a1 = addiu(a1, 27312);  // &sub_2F6AB0
            a2 = s0;
            jal(ctx, 0x2F5D60u, gen::fn_sub_2E4220_002e4220);
        }
    }
    // 0x002f5d68 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002F8790 sub_2F8790 -- 72 bytes; frame 0x10: ra sp+0x0
// Battle (gBtl = *0x7CE3EC): releases the battle's loaded file node gBtl+2836: sub_2F8460, H_Cdvd_Destroy(node), slot
// cleared. [proposed name btlReleaseFileNode]
void sub_2F8790(EEContext& ctx) {
    using namespace sweep5e;
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002f8790
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, -18692);  // 0x7CE3EC
    lw(v1, v1, kBtlFileNode);
    if (v1 != 0) {
        // 0x002f87a8
        charge(ctx, 8);
        jal(ctx, 0x2F87A8u, gen::fn_sub_2F8460_002f8460);
        lw(v0, gp, -18692);  // 0x7CE3EC
        lw(a0, v0, kBtlFileNode);
        jal(ctx, 0x2F87B8u, gen::fn_H_Cdvd_Destroy_00100ec0);
        lw(v1, gp, -18692);  // 0x7CE3EC
        sw(zero, v1, kBtlFileNode);
    }
    // 0x002f87c8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003138E0 sub_3138E0 -- 764 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Model part (a0): sets the visibility bit (bit 0 of +0 from a3), clears +2, and attaches its RW frame / atomic
// children (sub_4B6E10, sub_4B6EC0, sub_4B7020, sub_4B74C0, sub_4B7010).
void sub_3138E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x003138e0
    enter(ctx, 22);  // entry check point + this block's cycles
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
    lhu(v1, a0, 0);
    v1 = v1 & 0xFFFE;
    sh(v1, a0, 0);
    s1 = a3 & 0xFFFF;
    a1 = s1 & 0x1;
    lhu(v1, a0, 0);
    v1 = v1 | a1;
    sh(v1, a0, 0);
    sb(zero, a0, 2);
    v1 = s2 & 0xFFFF;
    if (i64(v1) > 0) {
        // 0x00313938
        charge(ctx, 4);
        lh(a0, s4, 4);
        v1 = si(-1);
        if (a0 == v1) {
            goto L_00313aa4;
        }
        // 0x00313948
        charge(ctx, 3);
        lw(t0, s4, 44);
        if (t0 == 0) {
            goto L_00313aa4;
        }
        // 0x00313954
        charge(ctx, 4);
        lhu(a3, t0, 4);
        at = slt(a0, a3);
        if (at == 0) {
            goto L_00313aa4;
        }
        // 0x00313964
        charge(ctx, 9);
        v1 = sll(a0, 2);
        v1 = addu(v1, a0);
        a0 = sll(v1, 4);
        lw(v1, t0, 0);
        a2 = addiu(v1, 64);
        v1 = addu(a2, a0);
        lw(v1, v1, 0);
        if (v1 == 0) {
            goto L_00313aa4;
        }
        // 0x00313988
        charge(ctx, 4);
        a1 = 0x950000;
        a1 = addiu(a1, 29136);  // &0x9571D0
        if (v1 == a1) {
            goto L_00313aa4;
        }
        // 0x00313998
        charge(ctx, 2);
        if (t0 == 0) {
            goto L_00313aa4;
        }
        // 0x003139a0
        charge(ctx, 5);
        a0 = dsll32(s3, 16);
        a0 = dsra32(a0, 16);
        at = slt(a0, a3);
        if (at == 0) {
            goto L_00313aa4;
        }
        // 0x003139b4
        charge(ctx, 7);
        v1 = sll(a0, 2);
        v1 = addu(v1, a0);
        s0 = sll(v1, 4);
        v1 = addu(a2, s0);
        lw(v1, v1, 0);
        if (v1 == 0) {
            goto L_00313aa4;
        }
        // 0x003139d0
        charge(ctx, 2);
        if (v1 == a1) {
            goto L_00313aa4;
        }
        // 0x003139d8
        charge(ctx, 3);
        lw(v0, s4, 36);
        if (v0 == 0) {
            // 0x003139e4
            charge(ctx, 7);
            lw(v1, s4, 32);
            lw(v0, v1, 32);
            lw(a0, v1, 4);
            lw(a1, v0, 32);
            jal(ctx, 0x3139F4u, gen::fn_sub_4B6E10_004b6e10);
            sw(v0, s4, 36);
        }
        // 0x00313a00
        charge(ctx, 3);
        lw(v0, s4, 40);
        if (v0 == 0) {
            // 0x00313a0c
            charge(ctx, 7);
            lw(v1, s4, 32);
            lw(v0, v1, 32);
            lw(a0, v1, 4);
            lw(a1, v0, 32);
            jal(ctx, 0x313A1Cu, gen::fn_sub_4B6E10_004b6e10);
            sw(v0, s4, 40);
        }
        // 0x00313a28
        charge(ctx, 31);
        lw(v0, s4, 44);
        lw(a0, v0, 0);
        lh(v1, s4, 4);
        v0 = sll(v1, 2);
        v0 = addu(v0, v1);
        v0 = sll(v0, 4);
        v0 = addu(v0, a0);
        lw(a0, s4, 36);
        lw(a1, v0, 64);
        jal(ctx, 0x313A4Cu, gen::fn_sub_4B6EC0_004b6ec0);
        lw(v0, s4, 44);
        lw(v0, v0, 0);
        v0 = addu(s0, v0);
        lw(a0, s4, 40);
        lw(a1, v0, 64);
        jal(ctx, 0x313A68u, gen::fn_sub_4B6EC0_004b6ec0);
        lw(v0, s4, 32);
        lw(a0, s4, 36);
        lw(a1, v0, 32);
        jal(ctx, 0x313A7Cu, gen::fn_sub_4B7020_004b7020);
        lh(v1, s4, 4);
        sh(v1, s4, 16);
        lwc1(f0, s4, 12);
        swc1(f0, s4, 20);
        sh(s2, s4, 24);
        sw(zero, s4, 28);
        goto L_00313b48;
    }
L_00313aa4:
    charge(ctx, 3);
    lw(a1, s4, 44);
    if (a1 != 0) {
        // 0x00313ab0
        charge(ctx, 6);
        a0 = dsll32(s3, 16);
        a0 = dsra32(a0, 16);
        lhu(v1, a1, 4);
        at = slt(a0, v1);
        if (at != 0) {
            // 0x00313ac8
            charge(ctx, 9);
            v1 = sll(a0, 2);
            v1 = addu(v1, a0);
            a0 = sll(v1, 4);
            lw(v1, a1, 0);
            v1 = addiu(v1, 64);
            v1 = addu(v1, a0);
            lw(a1, v1, 0);
            if (a1 != 0) {
                // 0x00313aec
                charge(ctx, 4);
                v1 = 0x950000;
                v1 = addiu(v1, 29136);  // &0x9571D0
                if (a1 != v1) {
                    // 0x00313afc
                    charge(ctx, 16);
                    lw(v0, s4, 32);
                    lw(a0, v0, 32);
                    jal(ctx, 0x313B04u, gen::fn_sub_4B6EC0_004b6ec0);
                    lw(v0, s4, 32);
                    mtc1(zero, f12);
                    lw(a0, v0, 32);
                    jal(ctx, 0x313B18u, gen::fn_sub_4B74C0_004b74c0);
                    lw(v0, s4, 32);
                    lw(a0, v0, 32);
                    a1 = 0x310000;
                    a1 = addiu(a1, 12432);  // &sub_313090
                    a2 = s4;
                    jal(ctx, 0x313B34u, gen::fn_sub_4B7010_004b7010);
                }
            }
        }
    }
    // 0x00313b3c
    charge(ctx, 3);
    sh(zero, s4, 24);
    v1 = 0x3F800000;
    sw(v1, s4, 28);
L_00313b48:
    charge(ctx, 6);
    lhu(v1, s4, 76);
    v1 = v1 & 0xF7FF;
    sh(v1, s4, 76);
    lw(a1, s4, 48);
    if (a1 != 0) {
        // 0x00313b60
        charge(ctx, 10);
        v1 = dsll32(s3, 16);
        v1 = dsra32(v1, 16);
        a0 = sll(v1, 2);
        lw(v1, a1, 20);
        v1 = addu(v1, a0);
        lw(v1, v1, 0);
        sw(v1, a1, 28);
        v1 = s1 & 0x20;
        if (v1 == 0) {
            // 0x00313b94
            charge(ctx, 3);
            lw(v1, a1, 32);
            v1 = addu(v1, a0);
            lw(v1, v1, 0);
        } else {
            // 0x00313b88
            charge(ctx, 3);
            v1 = 0;
        }
        // 0x00313ba0
        charge(ctx, 4);
        sw(v1, a1, 40);
        v1 = 1;
        sw(v1, a1, 44);
        sh(s2, a1, 48);
    }
    // 0x00313bb0 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    sw(zero, s4, 12);
    sh(s3, s4, 4);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00314850 sub_314850 -- 1236 bytes; frame 0xB0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Model build: walks the clump's atomics by RTTI type name (name__C9type_info_1 / strncmp) and installs the per-atomic
// render callbacks (sub_314020 .. sub_314650 table) for a model.
void sub_314850(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x00314850
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
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
    s2 = a1;
    s1 = a2;
    lw(v1, a1, 24);
    if (v1 != 0) {
        // 0x00314894
        charge(ctx, 13);
        lhu(v0, s2, 0);
        v0 = v0 & 0xFFFE;
        sh(v0, s2, 0);
        v0 = t0 & 0xFFFF;
        v1 = v0 & 0x1;
        lhu(v0, s2, 0);
        v0 = v0 | v1;
        sh(v0, s2, 0);
        sb(zero, s2, 2);
        sw(zero, s2, 16);
        v0 = a3 & 0xFFFF;
        if (i64(v0) > 0) {
            // 0x003148c8
            charge(ctx, 4);
            lh(a2, s2, 4);
            v0 = si(-1);
            if (a2 == v0) {
                goto L_00314948;
            }
            // 0x003148d8
            charge(ctx, 3);
            lw(a1, s2, 24);
            if (a1 == 0) {
                goto L_00314948;
            }
            // 0x003148e4
            charge(ctx, 4);
            lhu(a0, a1, 12);
            at = slt(a2, a0);
            if (at == 0) {
                goto L_00314948;
            }
            // 0x003148f4
            charge(ctx, 6);
            lw(v1, a1, 0);
            v0 = sll(a2, 3);
            v0 = addu(v1, v0);
            lw(v0, v0, 0);
            if (v0 == 0) {
                goto L_00314948;
            }
            // 0x0031490c
            charge(ctx, 2);
            if (a1 == 0) {
                goto L_00314948;
            }
            // 0x00314914
            charge(ctx, 5);
            v0 = dsll32(s1, 16);
            v0 = dsra32(v0, 16);
            at = slt(v0, a0);
            if (at == 0) {
                goto L_00314948;
            }
            // 0x00314928
            charge(ctx, 5);
            v0 = sll(v0, 3);
            v0 = addu(v1, v0);
            lw(v0, v0, 0);
            if (v0 == 0) {
                goto L_00314948;
            }
            // 0x0031493c
            charge(ctx, 3);
            sh(a3, s2, 20);
            goto L_0031494c;
        }
    L_00314948:
        charge(ctx, 1);
        sh(zero, s2, 20);
    L_0031494c:
        charge(ctx, 3);
        lw(a0, s2, 24);
        if (a0 != 0) {
            // 0x00314958
            charge(ctx, 6);
            v1 = dsll32(s1, 16);
            v1 = dsra32(v1, 16);
            lhu(v0, a0, 12);
            at = slt(v1, v0);
            if (at == 0) {
                goto L_00314c5c;
            }
            // 0x00314970
            charge(ctx, 6);
            s7 = sll(v1, 3);
            lw(v0, a0, 0);
            v0 = addu(v0, s7);
            lw(v0, v0, 0);
            if (v0 == 0) {
                goto L_00314c5c;
            }
            // 0x00314988
            charge(ctx, 7);
            lw(s6, a0, 8);
            a0 = s6;
            jal(ctx, 0x314990u, gen::fn_name__C9type_info_1_004c21d0);
            s0 = v0;
            for (;;) {
                // 0x00314c10
                charge(ctx, 5);
                a0 = s6;
                jal(ctx, 0x314C14u, gen::fn_sub_4C21E0_004c21e0);
                if (s0 == v0) {
                    break;
                }
                backedge(ctx);
                // 0x003149a4
                charge(ctx, 6);
                lw(a0, s0, 0);
                jal(ctx, 0x3149A8u, gen::fn_sub_469030_00469030);
                v1 = 6;
                if (v0 != v1) {
                    // 0x003149bc
                    charge(ctx, 3);
                    v1 = 5;
                    if (v0 == v1) {
                        goto L_003149d0;
                    }
                    // 0x003149c8
                    charge(ctx, 2);
                    goto L_003149e4;
                }
            L_003149d0:
                charge(ctx, 5);
                lw(a0, s0, 0);
                a1 = 0;
                a2 = 0;
                jal(ctx, 0x3149DCu, gen::fn_sub_4699B0_004699b0);
            L_003149e4:
                charge(ctx, 6);
                lw(a0, s0, 0);
                jal(ctx, 0x3149E8u, gen::fn_sub_3142B0_003142b0);
                s4 = v0;
                if (s4 != 0) {
                    // 0x003149fc
                    charge(ctx, 10);
                    lw(v0, s2, 24);
                    lw(v0, v0, 0);
                    v0 = addu(s7, v0);
                    lw(a0, v0, 0);
                    a1 = s4;
                    jal(ctx, 0x314A10u, gen::fn_sub_4B77F0_004b77f0);
                    s3 = v0;
                    if (s3 == 0) {
                        // 0x00314bbc
                        charge(ctx, 7);
                        lw(a0, s0, 0);
                        a1 = 1;
                        jal(ctx, 0x314BC4u, gen::fn_sub_4B97B0_004b97b0);
                        s3 = v0;
                        if (s3 != 0) {
                            // 0x00314bd8
                            charge(ctx, 3);
                            lw(v0, s3, 0);
                            if (v0 != 0) {
                                // 0x00314be4
                                charge(ctx, 4);
                                mtc1(zero, f12);
                                a0 = s3;
                                jal(ctx, 0x314BECu, gen::fn_sub_4B74C0_004b74c0);
                            }
                            // 0x00314bf4
                            charge(ctx, 6);
                            v0 = 0x310000;
                            v0 = addiu(v0, 16544);  // &nullsub_52
                            sw(v0, s3, 64);
                            v0 = 0x310000;
                            v0 = addiu(v0, 16560);  // &nullsub_53
                            sw(v0, s3, 68);
                        }
                    } else {
                        // 0x00314a24
                        charge(ctx, 14);
                        a0 = s4;
                        a1 = addiu(gp, -25328);  // "step_"
                        a2 = 5;
                        jal(ctx, 0x314A30u, gen::fn_strncmp_00524670);
                        fp = v0;
                        fp = sltiu(fp, 1);
                        lw(a0, s0, 0);
                        a1 = 1;
                        jal(ctx, 0x314A48u, gen::fn_sub_4B97B0_004b97b0);
                        s4 = v0;
                        if (s4 != 0) {
                            // 0x00314a5c
                            charge(ctx, 11);
                            lw(a0, s4, 0);
                            jal(ctx, 0x314A60u, gen::fn_sub_4B92D0_004b92d0);
                            lw(v0, s4, 44);
                            sq(v0, sp, 0xA0);
                            a0 = s3;
                            jal(ctx, 0x314A74u, gen::fn_sub_4B6DD0_004b6dd0);
                            lq(v1, sp, 0xA0);
                            if (v1 == v0) {
                                // 0x00314a88
                                charge(ctx, 5);
                                lw(v1, s4, 36);
                                lw(v0, s3, 0);
                                lw(v0, v0, 4);
                                if (v1 != v0) {
                                    goto L_00314a9c;
                                }
                                goto L_00314aac;
                            }
                        L_00314a9c:
                            charge(ctx, 4);
                            a0 = s4;
                            jal(ctx, 0x314AA0u, gen::fn_sub_4B6EB0_004b6eb0);
                            s4 = 0;
                        }
                    L_00314aac:
                        charge(ctx, 2);
                        if (s4 == 0) {
                            // 0x00314ad8
                            charge(ctx, 10);
                            lw(a0, s0, 0);
                            a1 = s3;
                            a2 = 1;
                            jal(ctx, 0x314AE4u, gen::fn_sub_4B96F0_004b96f0);
                            lw(a0, s0, 0);
                            a1 = 1;
                            jal(ctx, 0x314AF4u, gen::fn_sub_4B97B0_004b97b0);
                            s4 = v0;
                        } else {
                            // 0x00314ab4
                            charge(ctx, 9);
                            a0 = s4;
                            a1 = s3;
                            jal(ctx, 0x314ABCu, gen::fn_sub_4B6EC0_004b6ec0);
                            a0 = s3;
                            jal(ctx, 0x314AC8u, gen::fn_sub_4B9350_004b9350);
                        }
                        // 0x00314b00
                        charge(ctx, 6);
                        a0 = s3;
                        jal(ctx, 0x314B04u, gen::fn_sub_4B6DD0_004b6dd0);
                        v1 = 1;
                        if (v0 != v1) {
                            // 0x00314b30
                            charge(ctx, 4);
                            lw(a0, s0, 0);
                            a1 = 6;
                            jal(ctx, 0x314B38u, gen::fn_sub_468EA0_00468ea0);
                        } else {
                            // 0x00314b18
                            charge(ctx, 6);
                            lw(a0, s0, 0);
                            a1 = 5;
                            jal(ctx, 0x314B20u, gen::fn_sub_468EA0_00468ea0);
                        }
                        // 0x00314b40
                        charge(ctx, 3);
                        v0 = 1;
                        if (fp != v0) {
                            // 0x00314b84
                            charge(ctx, 14);
                            a0 = s4;
                            a1 = 0x310000;
                            a1 = addiu(a1, 16576);  // &sub_3140C0
                            a2 = s2;
                            jal(ctx, 0x314B94u, gen::fn_sub_4B7010_004b7010);
                            lw(v0, s3, 0);
                            lw(v0, v0, 16);
                            sw(v0, s4, 64);
                            lw(v0, s3, 0);
                            lw(v0, v0, 20);
                            sw(v0, s4, 68);
                        } else {
                            // 0x00314b4c
                            charge(ctx, 14);
                            a0 = s4;
                            a1 = 0x310000;
                            a1 = addiu(a1, 16752);  // &sub_314170
                            a2 = s2;
                            jal(ctx, 0x314B5Cu, gen::fn_sub_4B7010_004b7010);
                            v0 = 0x310000;
                            v0 = addiu(v0, 16416);  // &sub_314020
                            sw(v0, s4, 64);
                            v0 = 0x310000;
                            v0 = addiu(v0, 16480);  // &sub_314060
                            sw(v0, s4, 68);
                        }
                    }
                }
                // 0x00314c0c
                charge(ctx, 1);
                s0 = addiu(s0, 4);
            }
            // 0x00314c24
            charge(ctx, 14);
            a0 = s5;
            a1 = 0x310000;
            a1 = addiu(a1, 18000);  // &sub_314650
            a2 = 0;
            jal(ctx, 0x314C34u, gen::fn_sub_4916D0_004916d0);
            a0 = s5;
            a1 = 0x310000;
            a1 = addiu(a1, 17680);  // &sub_314510
            a2 = 0;
            jal(ctx, 0x314C4Cu, gen::fn_sub_4916D0_004916d0);
            goto L_00314cec;
        }
    L_00314c5c:
        charge(ctx, 7);
        lw(s4, a0, 8);
        a0 = s4;
        jal(ctx, 0x314C64u, gen::fn_name__C9type_info_1_004c21d0);
        s3 = v0;
        for (;;) {
            // 0x00314cd8
            charge(ctx, 5);
            a0 = s4;
            jal(ctx, 0x314CDCu, gen::fn_sub_4C21E0_004c21e0);
            if (s3 == v0) {
                break;
            }
            backedge(ctx);
            // 0x00314c78
            charge(ctx, 5);
            lw(a0, s3, 0);
            jal(ctx, 0x314C7Cu, gen::fn_sub_3142B0_003142b0);
            if (v0 != 0) {
                // 0x00314c8c
                charge(ctx, 7);
                lw(a0, s3, 0);
                a1 = 1;
                jal(ctx, 0x314C94u, gen::fn_sub_4B97B0_004b97b0);
                s0 = v0;
                if (s0 != 0) {
                    // 0x00314ca8
                    charge(ctx, 11);
                    lw(a0, s0, 0);
                    jal(ctx, 0x314CACu, gen::fn_sub_4B92D0_004b92d0);
                    a0 = s0;
                    jal(ctx, 0x314CB8u, gen::fn_sub_4B6EB0_004b6eb0);
                    lw(a0, s3, 0);
                    a1 = 0;
                    a2 = 1;
                    jal(ctx, 0x314CCCu, gen::fn_sub_4B97D0_004b97d0);
                }
            }
            // 0x00314cd4
            charge(ctx, 1);
            s3 = addiu(s3, 4);
        }
    L_00314cec:
        charge(ctx, 1);
        sh(s1, s2, 4);
    }
    // 0x00314cf0 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0xB0);
}

// 0x00314D30 sub_314D30 -- 732 bytes; frame 0x60: ra sp+0x50, s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// Model: per-atomic render-callback setup for a clump (the sub_314020 / sub_314060 / sub_314170 set).
void sub_314D30(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f20{ctx, 20};
    // 0x00314d30
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s3 = a0;
    lw(v1, a0, 24);
    if (v1 != 0) {
        // 0x00314d5c
        charge(ctx, 3);
        lw(v1, v1, 8);
        if (v1 != 0) {
            // 0x00314d68
            charge(ctx, 3);
            lhu(v0, s3, 20);
            if (v0 != 0) {
                // 0x00314d88
                charge(ctx, 3);
                mtc1(zero, f20);
                v0 = addiu(v0, -1);
                sh(v0, s3, 20);
            } else {
                // 0x00314d74
                charge(ctx, 5);
                lwc1(f1, gp, -32540);  // 0x7CADD4
                lwc1(f0, s3, 8);
                mul_s(f20, f1, f0);
            }
            // 0x00314d94
            charge(ctx, 15);
            lwc1(f1, s3, 12);
            lwc1(f0, gp, -32540);  // 0x7CADD4
            add_s(f0, f1, f0);
            swc1(f0, s3, 12);
            lwc1(f0, s3, 16);
            add_s(f0, f0, f20);
            swc1(f0, s3, 16);
            lw(v0, s3, 24);
            lw(s1, v0, 8);
            a0 = s1;
            jal(ctx, 0x314DBCu, gen::fn_name__C9type_info_1_004c21d0);
            s2 = v0;
            for (;;) {
                // 0x00314fd4
                charge(ctx, 5);
                a0 = s1;
                jal(ctx, 0x314FD8u, gen::fn_sub_4C21E0_004c21e0);
                if (s2 == v0) {
                    break;
                }
                backedge(ctx);
                // 0x00314dd0
                charge(ctx, 6);
                lw(a0, s2, 0);
                jal(ctx, 0x314DD4u, gen::fn_sub_469030_00469030);
                v1 = 6;
                if (v0 != v1) {
                    // 0x00314de8
                    charge(ctx, 3);
                    v1 = 5;
                    if (v0 == v1) {
                        goto L_00314dfc;
                    }
                    // 0x00314df4
                    charge(ctx, 2);
                    goto L_00314fd0;
                }
            L_00314dfc:
                charge(ctx, 7);
                lw(a0, s2, 0);
                a1 = 0;
                jal(ctx, 0x314E04u, gen::fn_sub_4B97B0_004b97b0);
                s0 = v0;
                if (s0 != 0) {
                    // 0x00314e18
                    charge(ctx, 5);
                    lw(v1, s0, 64);
                    v0 = 0x310000;
                    v0 = addiu(v0, 16416);  // &sub_314020
                    if (v1 == v0) {
                        // 0x00314e2c
                        charge(ctx, 5);
                        lw(v1, s0, 68);
                        v0 = 0x310000;
                        v0 = addiu(v0, 16480);  // &sub_314060
                        if (v1 != v0) {
                            goto L_00314e58;
                        }
                        // 0x00314e40
                        charge(ctx, 6);
                        a0 = s0;
                        lwc1(f12, gp, -32540);  // 0x7CADD4
                        jal(ctx, 0x314E48u, gen::fn_sub_4B7240_004b7240);
                        goto L_00314e68;
                    }
                L_00314e58:
                    charge(ctx, 4);
                    a0 = s0;
                    lwc1(f12, s3, 12);
                    jal(ctx, 0x314E60u, gen::fn_sub_4B74C0_004b74c0);
                L_00314e68:
                    charge(ctx, 2);
                    lwc1(f0, s0, 4);
                    swc1(f0, s3, 12);
                }
                // 0x00314e70
                charge(ctx, 4);
                lbu(v0, s3, 2);
                a1 = 1;
                if (v0 == a1) {
                    // 0x00314f50
                    charge(ctx, 5);
                    lw(a0, s2, 0);
                    jal(ctx, 0x314F54u, gen::fn_sub_4B97B0_004b97b0);
                    if (v0 != 0) {
                        // 0x00314f64
                        charge(ctx, 5);
                        lw(a0, v0, 64);
                        v1 = 0x310000;
                        v1 = addiu(v1, 16416);  // &sub_314020
                        if (a0 == v1) {
                            // 0x00314f78
                            charge(ctx, 5);
                            lw(a0, v0, 68);
                            v1 = 0x310000;
                            v1 = addiu(v1, 16480);  // &sub_314060
                            if (a0 != v1) {
                                goto L_00314fac;
                            }
                            // 0x00314f8c
                            charge(ctx, 8);
                            a0 = v0;
                            a1 = 0x310000;
                            a1 = addiu(a1, 16752);  // &sub_314170
                            a2 = s3;
                            jal(ctx, 0x314F9Cu, gen::fn_sub_4B7010_004b7010);
                            goto L_00314fc4;
                        }
                    L_00314fac:
                        charge(ctx, 6);
                        a0 = v0;
                        a1 = 0x310000;
                        a1 = addiu(a1, 16576);  // &sub_3140C0
                        a2 = s3;
                        jal(ctx, 0x314FBCu, gen::fn_sub_4B7010_004b7010);
                    }
                } else {
                    // 0x00314e80
                    charge(ctx, 6);
                    lw(a0, s2, 0);
                    jal(ctx, 0x314E84u, gen::fn_sub_4B97B0_004b97b0);
                    s0 = v0;
                    if (s0 != 0) {
                        // 0x00314e98
                        charge(ctx, 5);
                        lw(v1, s0, 64);
                        v0 = 0x310000;
                        v0 = addiu(v0, 16416);  // &sub_314020
                        if (v1 == v0) {
                            // 0x00314eac
                            charge(ctx, 5);
                            lw(v1, s0, 68);
                            v0 = 0x310000;
                            v0 = addiu(v0, 16480);  // &sub_314060
                            if (v1 != v0) {
                                goto L_00314ef0;
                            }
                            // 0x00314ec0
                            charge(ctx, 12);
                            a0 = s0;
                            a1 = 0x310000;
                            a1 = addiu(a1, 16752);  // &sub_314170
                            a2 = s3;
                            jal(ctx, 0x314ED0u, gen::fn_sub_4B7010_004b7010);
                            a0 = s0;
                            mov_s(f12, f20);
                            jal(ctx, 0x314EE0u, gen::fn_sub_4B7240_004b7240);
                            goto L_00314f40;
                        }
                    L_00314ef0:
                        charge(ctx, 11);
                        a0 = s0;
                        a1 = 0x310000;
                        a1 = addiu(a1, 16576);  // &sub_3140C0
                        a2 = s3;
                        jal(ctx, 0x314F00u, gen::fn_sub_4B7010_004b7010);
                        lw(v1, s0, 64);
                        v0 = 0x310000;
                        v0 = addiu(v0, 16544);  // &nullsub_52
                        if (v1 != v0) {
                            // 0x00314f1c
                            charge(ctx, 5);
                            lw(v1, s0, 68);
                            v0 = 0x310000;
                            v0 = addiu(v0, 16560);  // &nullsub_53
                            if (v1 != v0) {
                                // 0x00314f30
                                charge(ctx, 4);
                                a0 = s0;
                                lwc1(f12, s3, 16);
                                jal(ctx, 0x314F38u, gen::fn_sub_4B74C0_004b74c0);
                            }
                        }
                    L_00314f40:
                        charge(ctx, 4);
                        lwc1(f0, s0, 4);
                        swc1(f0, s3, 16);
                    }
                }
            L_00314fc4:
                charge(ctx, 3);
                lw(a0, s2, 0);
                jal(ctx, 0x314FC8u, gen::fn_sub_4B9370_004b9370);
            L_00314fd0:
                charge(ctx, 1);
                s2 = addiu(s2, 4);
            }
        }
    }
    // 0x00314fe8 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00319970 sub_319970 -- 4436 bytes; frame 0xE0: ra sp+0x80, s5 sp+0x70 (sq), s4 sp+0x60 (sq), s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq)
// "mdlManager.c": loads a model record: allocates through RwMalloc (slot 0x960178), reads the RW stream, creates the
// clump / frames / textures and registers it (jalr through the RW memory slots).
void sub_319970(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00319970
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0xE0);
    sd(ra, sp, 0x80);
    sq(s5, sp, 0x70);
    sq(s4, sp, 0x60);
    sq(s3, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    s1 = a0;
    lw(s0, a0, 1064);
    v1 = 32;
    sh(v1, sp, 0xDE);
    a0 = 0;
    for (;;) {
        // 0x003199c4
        charge(ctx, 4);
        v0 = a0 & 0xFFFF;
        v0 = slti(v0, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003199ac
        charge(ctx, 6);
        v0 = a0 & 0xFFFF;
        v0 = sll(v0, 1);
        v0 = addu(s0, v0);
        sh(v1, v0, 32);
        v0 = addiu(a0, 1);
        a0 = v0 & 0xFFFF;
    }
    // 0x003199d4
    charge(ctx, 2);
    for (;;) {
        // 0x0031aa80
        charge(ctx, 6);
        lw(a0, s0, 0);
        a1 = addiu(sp, 0x90);
        jal(ctx, 0x31AA88u, gen::fn_sub_4C1970_004c1970);
        if (v0 != 0) {
            backedge(ctx);
            // 0x003199dc
            charge(ctx, 3);
            lw(v0, sp, 0x90);
            if (v0 != 0) {
                // 0x003199e8
                charge(ctx, 4);
                a0 = lui(0xF0F0);
                v1 = a0 | 0xE1;
                if (v0 == v1) {
                    // 0x0031a95c
                    charge(ctx, 14);
                    lw(v0, s0, 0);
                    lw(v1, s0, 56);
                    lw(v0, v0, 12);
                    s3 = addu(v1, v0);
                    lhu(v1, s0, 28);
                    v0 = sll(v1, 2);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 3);
                    v0 = subu(v0, v1);
                    v0 = sll(v0, 2);
                    v0 = addu(s1, v0);
                    lw(v0, v0, 284);
                    if (v0 == 0) {
                        // 0x0031a994
                        charge(ctx, 32);
                        lhu(s2, sp, 0xDE);
                        v0 = 52;
                        v1 = sll(s2, 2);
                        v0 = addu(v0, v1);
                        s4 = addu(v0, v1);
                        a0 = s4;
                        a1 = 0x40000;
                        v0 = 0x960000;
                        lw(v0, v0, 376);  // 0x960178
                        jalr(ctx, 0x31A9B8u, v0.u());
                        s5 = v0;
                        a0 = s5;
                        a1 = 0;
                        a2 = s4;
                        jal(ctx, 0x31A9D0u, gen::fn_memset_00521408);
                        v0 = s2 & 0xFFFF;
                        sw(v0, s5, 0);
                        v1 = addiu(s5, 52);
                        sw(v1, s5, 20);
                        v0 = sll(v0, 2);
                        v0 = addu(v1, v0);
                        sw(v0, s5, 32);
                        lhu(v1, s0, 28);
                        v0 = sll(v1, 2);
                        v0 = addu(v0, v1);
                        v0 = sll(v0, 3);
                        v0 = subu(v0, v1);
                        v0 = sll(v0, 2);
                        v0 = addu(s1, v0);
                        sw(s5, v0, 284);
                    }
                    // 0x0031aa14
                    charge(ctx, 23);
                    lw(a1, sp, 0x94);
                    a0 = s3;
                    jal(ctx, 0x31AA1Cu, gen::fn_sub_31DFF0_0031dff0);
                    lhu(a0, s0, 28);
                    v1 = sll(a0, 2);
                    v1 = addu(v1, a0);
                    v1 = sll(v1, 3);
                    v1 = subu(v1, a0);
                    v1 = sll(v1, 2);
                    v1 = addu(s1, v1);
                    lw(a1, v1, 284);
                    lhu(v1, s0, 30);
                    a0 = sll(v1, 2);
                    lw(v1, a1, 32);
                    v1 = addu(v1, a0);
                    sw(v0, v1, 0);
                    lw(a0, s0, 0);
                    lw(a1, sp, 0x94);
                    jal(ctx, 0x31AA60u, gen::fn_sub_4C5620_004c5620);
                } else {
                    // 0x003199f8
                    charge(ctx, 3);
                    v1 = a0 | 0xE0;
                    if (v0 == v1) {
                        // 0x0031a718
                        charge(ctx, 16);
                        lw(a0, s0, 0);
                        a1 = addiu(sp, 0xB0);
                        a2 = 20;
                        jal(ctx, 0x31A724u, gen::fn_sub_4C5250_004c5250);
                        lw(a0, s0, 0);
                        lw(a1, sp, 0xB8);
                        jal(ctx, 0x31A734u, gen::fn_sub_4C5620_004c5620);
                        lw(v0, s0, 0);
                        lw(v1, s0, 56);
                        lw(v0, v0, 12);
                        s5 = addu(v1, v0);
                        lw(v0, s1, 220);
                        if (v0 == 0) {
                            // 0x0031a758
                            charge(ctx, 3);
                            lw(v0, s0, 20);
                            if (v0 != 0) {
                                goto L_0031a788;
                            }
                            // 0x0031a764
                            charge(ctx, 3);
                            lw(v0, s1, 1012);
                            if (v0 == 0) {
                                // 0x0031a770
                                charge(ctx, 3);
                                jal(ctx, 0x31A770u, gen::fn_sub_31D6B0_0031d6b0);
                                sw(v0, s1, 1012);
                            }
                            // 0x0031a77c
                            charge(ctx, 3);
                            lw(s4, s1, 1012);
                            goto L_0031a8dc;
                        }
                    L_0031a788:
                        charge(ctx, 10);
                        lhu(v1, s0, 28);
                        v0 = sll(v1, 2);
                        v0 = addu(v0, v1);
                        v0 = sll(v0, 3);
                        v0 = subu(v0, v1);
                        v0 = sll(v0, 2);
                        v0 = addu(s1, v0);
                        lw(v0, v0, 284);
                        if (v0 == 0) {
                            // 0x0031a7b0
                            charge(ctx, 32);
                            lhu(s2, sp, 0xDE);
                            v0 = 52;
                            v1 = sll(s2, 2);
                            v0 = addu(v0, v1);
                            s3 = addu(v0, v1);
                            a0 = s3;
                            a1 = 0x40000;
                            v0 = 0x960000;
                            lw(v0, v0, 376);  // 0x960178
                            jalr(ctx, 0x31A7D4u, v0.u());
                            s4 = v0;
                            a0 = s4;
                            a1 = 0;
                            a2 = s3;
                            jal(ctx, 0x31A7ECu, gen::fn_memset_00521408);
                            v0 = s2 & 0xFFFF;
                            sw(v0, s4, 0);
                            v1 = addiu(s4, 52);
                            sw(v1, s4, 20);
                            v0 = sll(v0, 2);
                            v0 = addu(v1, v0);
                            sw(v0, s4, 32);
                            lhu(v1, s0, 28);
                            v0 = sll(v1, 2);
                            v0 = addu(v0, v1);
                            v0 = sll(v0, 3);
                            v0 = subu(v0, v1);
                            v0 = sll(v0, 2);
                            v0 = addu(s1, v0);
                            sw(s4, v0, 284);
                        }
                        // 0x0031a830
                        charge(ctx, 15);
                        lhu(v1, s0, 28);
                        v0 = sll(v1, 2);
                        v0 = addu(v0, v1);
                        v0 = sll(v0, 3);
                        v0 = subu(v0, v1);
                        v0 = sll(v0, 2);
                        v0 = addu(s1, v0);
                        lw(a0, v0, 284);
                        lhu(v0, s0, 30);
                        v1 = sll(v0, 2);
                        lw(v0, a0, 20);
                        v0 = addu(v0, v1);
                        lw(v0, v0, 0);
                        if (v0 == 0) {
                            // 0x0031a86c
                            charge(ctx, 15);
                            jal(ctx, 0x31A86Cu, gen::fn_sub_31D6B0_0031d6b0);
                            lhu(a0, s0, 28);
                            v1 = sll(a0, 2);
                            v1 = addu(v1, a0);
                            v1 = sll(v1, 3);
                            v1 = subu(v1, a0);
                            v1 = sll(v1, 2);
                            v1 = addu(s1, v1);
                            lw(a1, v1, 284);
                            lhu(v1, s0, 30);
                            a0 = sll(v1, 2);
                            lw(v1, a1, 20);
                            v1 = addu(v1, a0);
                            sw(v0, v1, 0);
                        }
                        // 0x0031a8a8
                        charge(ctx, 13);
                        lhu(v1, s0, 28);
                        v0 = sll(v1, 2);
                        v0 = addu(v0, v1);
                        v0 = sll(v0, 3);
                        v0 = subu(v0, v1);
                        v0 = sll(v0, 2);
                        v0 = addu(s1, v0);
                        lw(a0, v0, 284);
                        lhu(v0, s0, 30);
                        v1 = sll(v0, 2);
                        lw(v0, a0, 20);
                        v0 = addu(v0, v1);
                        lw(s4, v0, 0);
                    L_0031a8dc:
                        charge(ctx, 13);
                        lw(a2, sp, 0xB4);
                        a0 = s4;
                        a1 = s5;
                        lhu(a3, sp, 0xB0);
                        lw(t0, sp, 0xBC);
                        jal(ctx, 0x31A8F0u, gen::fn_sub_31D7E0_0031d7e0);
                        s3 = v0;
                        lhu(v0, sp, 0xB0);
                        v0 = addiu(v0, 1);
                        s2 = v0 & 0xFFFF;
                        for (;;) {
                            // 0x0031a92c
                            charge(ctx, 6);
                            v1 = s2 & 0xFFFF;
                            lhu(v0, sp, 0xB2);
                            v0 = addiu(v0, 1);
                            v0 = slt(v1, v0);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x0031a910
                            charge(ctx, 7);
                            a0 = s4;
                            a1 = s3;
                            a2 = s2;
                            jal(ctx, 0x31A91Cu, gen::fn_sub_31D900_0031d900);
                            v0 = addiu(s2, 1);
                            s2 = v0 & 0xFFFF;
                        }
                        // 0x0031a944
                        charge(ctx, 6);
                        lw(a0, s0, 0);
                        lw(a1, sp, 0xB4);
                        jal(ctx, 0x31A94Cu, gen::fn_sub_4C5620_004c5620);
                    } else {
                        // 0x00319a04
                        charge(ctx, 3);
                        v1 = a0 | 0xF0;
                        if (v0 == v1) {
                            // 0x0031a6e8
                            charge(ctx, 12);
                            lw(a0, s0, 0);
                            a1 = addiu(sp, 0xDE);
                            lw(a2, sp, 0x94);
                            jal(ctx, 0x31A6F4u, gen::fn_sub_4C5250_004c5250);
                            lhu(v1, sp, 0xDE);
                            lhu(v0, s0, 28);
                            v0 = sll(v0, 1);
                            v0 = addu(s0, v0);
                            sh(v1, v0, 32);
                        } else {
                            // 0x00319a10
                            charge(ctx, 3);
                            v1 = a0 | 0x6;
                            if (v0 == v1) {
                                // 0x0031a5f0
                                charge(ctx, 28);
                                lw(s5, s0, 0);
                                a0 = s5;
                                a1 = addiu(sp, 0xDA);
                                a2 = 2;
                                jal(ctx, 0x31A600u, gen::fn_sub_4C5250_004c5250);
                                lhu(v1, sp, 0xDA);
                                v0 = sll(v1, 2);
                                v0 = addu(v0, v1);
                                v0 = sll(v0, 4);
                                a0 = addiu(v0, 8);
                                a1 = 0x40000;
                                v0 = 0x960000;
                                lw(v0, v0, 376);  // 0x960178
                                jalr(ctx, 0x31A628u, v0.u());
                                lhu(a0, sp, 0xDA);
                                v1 = sll(a0, 2);
                                v1 = addu(v1, a0);
                                v1 = sll(v1, 4);
                                s3 = addu(v0, v1);
                                sh(a0, s3, 0);
                                v1 = 1;
                                sh(v1, s3, 2);
                                sw(v0, s3, 4);
                                s4 = 0;
                                for (;;) {
                                    // 0x0031a6c8
                                    charge(ctx, 5);
                                    v1 = s4 & 0xFFFF;
                                    lhu(v0, sp, 0xDA);
                                    v0 = slt(v1, v0);
                                    if (v0 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                    // 0x0031a660
                                    charge(ctx, 26);
                                    v1 = s4 & 0xFFFF;
                                    v0 = sll(v1, 2);
                                    v0 = addu(v0, v1);
                                    s2 = sll(v0, 4);
                                    lw(v0, s3, 4);
                                    v0 = addu(v0, s2);
                                    a0 = s5;
                                    a1 = addiu(v0, 64);
                                    a2 = 4;
                                    jal(ctx, 0x31A684u, gen::fn_sub_4C5250_004c5250);
                                    lw(v0, s3, 4);
                                    v0 = addu(v0, s2);
                                    a0 = s5;
                                    a1 = addiu(v0, 68);
                                    a2 = 4;
                                    jal(ctx, 0x31A6A0u, gen::fn_sub_4C5250_004c5250);
                                    lw(v0, s3, 4);
                                    a1 = addu(v0, s2);
                                    a0 = s5;
                                    a2 = 64;
                                    jal(ctx, 0x31A6B8u, gen::fn_sub_4C5250_004c5250);
                                    v0 = addiu(s4, 1);
                                    s4 = v0 & 0xFFFF;
                                }
                                // 0x0031a6dc
                                charge(ctx, 3);
                                sw(s3, s1, 1008);
                            } else {
                                // 0x00319a1c
                                charge(ctx, 3);
                                v1 = a0 | 0x70;
                                if (v0 == v1) {
                                    // 0x0031a594
                                    charge(ctx, 23);
                                    a0 = 696;
                                    a1 = 0x40000;
                                    v0 = 0x960000;
                                    lw(v0, v0, 376);  // 0x960178
                                    jalr(ctx, 0x31A5A4u, v0.u());
                                    s2 = v0;
                                    lw(a0, s0, 0);
                                    a1 = s2;
                                    lw(a2, sp, 0x94);
                                    jal(ctx, 0x31A5BCu, gen::fn_sub_4C5250_004c5250);
                                    a0 = s1;
                                    a1 = s2;
                                    jal(ctx, 0x31A5CCu, gen::fn_sub_3164F0_003164f0);
                                    a0 = s2;
                                    v0 = 0x960000;
                                    lw(v0, v0, 380);  // 0x96017C
                                    jalr(ctx, 0x31A5E0u, v0.u());
                                } else {
                                    // 0x00319a28
                                    charge(ctx, 3);
                                    v1 = a0 | 0x82;
                                    if (v0 != v1) {
                                        // 0x00319a34
                                        charge(ctx, 3);
                                        v1 = a0 | 0x83;
                                        if (v0 == v1) {
                                            goto L_0031a428;
                                        }
                                        // 0x00319a40
                                        charge(ctx, 3);
                                        v1 = a0 | 0x81;
                                        if (v0 == v1) {
                                            goto L_0031a428;
                                        }
                                        // 0x00319a4c
                                        charge(ctx, 3);
                                        v1 = a0 | 0x80;
                                        if (v0 == v1) {
                                            goto L_0031a428;
                                        }
                                        // 0x00319a58
                                        charge(ctx, 3);
                                        v1 = a0 | 0x3;
                                        if (v0 == v1) {
                                            // 0x0031a154
                                            charge(ctx, 4);
                                            lhu(v0, s1, 216);
                                            v0 = v0 & 0x4000;
                                            if (v0 == 0) {
                                                // 0x0031a358
                                                charge(ctx, 11);
                                                lw(a0, s0, 0);
                                                a1 = addiu(sp, 0xDC);
                                                lw(a2, sp, 0x94);
                                                jal(ctx, 0x31A364u, gen::fn_sub_4C5250_004c5250);
                                                lhu(v0, s0, 28);
                                                v0 = sll(v0, 2);
                                                v0 = addu(s0, v0);
                                                lw(v0, v0, 40);
                                                if (v0 == 0) {
                                                    // 0x0031a384
                                                    charge(ctx, 15);
                                                    lhu(v0, sp, 0xDE);
                                                    a0 = sll(v0, 1);
                                                    a1 = 0x40000;
                                                    v0 = 0x960000;
                                                    lw(v0, v0, 376);  // 0x960178
                                                    jalr(ctx, 0x31A398u, v0.u());
                                                    lhu(v1, s0, 28);
                                                    v1 = sll(v1, 2);
                                                    v1 = addu(s0, v1);
                                                    sw(v0, v1, 40);
                                                    a2 = 0;
                                                    a1 = si(-1);
                                                    for (;;) {
                                                        // 0x0031a3e8
                                                        charge(ctx, 5);
                                                        v1 = a2 & 0xFFFF;
                                                        lhu(v0, sp, 0xDE);
                                                        v0 = slt(v1, v0);
                                                        if (v0 == 0) {
                                                            break;
                                                        }
                                                        backedge(ctx);
                                                        // 0x0031a3c0
                                                        charge(ctx, 10);
                                                        lhu(v0, s0, 28);
                                                        v0 = sll(v0, 2);
                                                        a0 = addu(s0, v0);
                                                        v0 = a2 & 0xFFFF;
                                                        v1 = sll(v0, 1);
                                                        lw(v0, a0, 40);
                                                        v0 = addu(v0, v1);
                                                        sh(a1, v0, 0);
                                                        v0 = addiu(a2, 1);
                                                        a2 = v0 & 0xFFFF;
                                                    }
                                                }
                                                // 0x0031a3fc
                                                charge(ctx, 11);
                                                lhu(a1, sp, 0xDC);
                                                lhu(v0, s0, 28);
                                                v0 = sll(v0, 2);
                                                a0 = addu(s0, v0);
                                                lhu(v0, s0, 30);
                                                v1 = sll(v0, 1);
                                                lw(v0, a0, 40);
                                                v0 = addu(v0, v1);
                                                sh(a1, v0, 0);
                                            } else {
                                                // 0x0031a164
                                                charge(ctx, 23);
                                                lw(a0, s0, 0);
                                                a1 = addiu(sp, 0xDC);
                                                lw(a2, sp, 0x94);
                                                jal(ctx, 0x31A170u, gen::fn_sub_4C5250_004c5250);
                                                lhu(v0, sp, 0xDC);
                                                lhu(t0, s0, 30);
                                                lhu(a0, s0, 28);
                                                v1 = sll(a0, 2);
                                                v1 = addu(v1, a0);
                                                v1 = sll(v1, 3);
                                                v1 = subu(v1, a0);
                                                v1 = sll(v1, 2);
                                                v1 = addu(s1, v1);
                                                lw(a3, v1, 280);
                                                lw(a2, a3, 0);
                                                v1 = sll(v0, 2);
                                                v1 = addu(v1, v0);
                                                v1 = sll(v1, 4);
                                                v1 = addu(a2, v1);
                                                lw(a1, v1, 64);
                                                if (a1 != 0) {
                                                    // 0x0031a1c0
                                                    charge(ctx, 6);
                                                    a0 = t0 & 0xFFFF;
                                                    v1 = sll(a0, 2);
                                                    v1 = addu(v1, a0);
                                                    v1 = sll(v1, 4);
                                                    v1 = addu(a2, v1);
                                                    sw(a1, v1, 64);
                                                }
                                                // 0x0031a1d8
                                                charge(ctx, 12);
                                                a0 = t0 & 0xFFFF;
                                                v1 = sll(a0, 2);
                                                v1 = addu(v1, a0);
                                                a0 = sll(v1, 4);
                                                lw(v1, a3, 0);
                                                a0 = addu(v1, a0);
                                                lw(v1, a0, 68);
                                                v1 = v1 | 0x1;
                                                sw(v1, a0, 68);
                                                lw(a2, s1, 860);
                                                if (a2 != 0) {
                                                    // 0x0031a208
                                                    charge(ctx, 5);
                                                    lhu(a0, a2, 4);
                                                    v1 = v0 & 0xFFFF;
                                                    at = slt(v1, a0);
                                                    if (at != 0) {
                                                        // 0x0031a21c
                                                        charge(ctx, 6);
                                                        v0 = sll(v0, 3);
                                                        lw(a1, a2, 0);
                                                        v0 = addu(a1, v0);
                                                        lw(a0, v0, 0);
                                                        if (a0 != 0) {
                                                            // 0x0031a234
                                                            charge(ctx, 9);
                                                            lhu(v0, s0, 30);
                                                            v1 = sll(v0, 3);
                                                            v0 = addu(a1, v1);
                                                            sw(a0, v0, 0);
                                                            lw(v0, a2, 0);
                                                            v1 = addu(v0, v1);
                                                            lbu(v0, v1, 4);
                                                            v0 = v0 | 0x1;
                                                            sb(v0, v1, 4);
                                                        }
                                                    }
                                                }
                                                // 0x0031a258
                                                charge(ctx, 3);
                                                lw(a2, s1, 892);
                                                if (a2 != 0) {
                                                    // 0x0031a264
                                                    charge(ctx, 5);
                                                    lhu(v1, sp, 0xDC);
                                                    lhu(v0, a2, 12);
                                                    at = slt(v1, v0);
                                                    if (at != 0) {
                                                        // 0x0031a278
                                                        charge(ctx, 6);
                                                        v0 = sll(v1, 3);
                                                        lw(a1, a2, 0);
                                                        v0 = addu(a1, v0);
                                                        lw(a0, v0, 0);
                                                        if (a0 != 0) {
                                                            // 0x0031a290
                                                            charge(ctx, 9);
                                                            lhu(v0, s0, 30);
                                                            v1 = sll(v0, 3);
                                                            v0 = addu(a1, v1);
                                                            sw(a0, v0, 0);
                                                            lw(v0, a2, 0);
                                                            v1 = addu(v0, v1);
                                                            lbu(v0, v1, 4);
                                                            v0 = v0 | 0x1;
                                                            sb(v0, v1, 4);
                                                        }
                                                    }
                                                }
                                                // 0x0031a2b4
                                                charge(ctx, 10);
                                                lhu(v1, s0, 28);
                                                v0 = sll(v1, 2);
                                                v0 = addu(v0, v1);
                                                v0 = sll(v0, 3);
                                                v0 = subu(v0, v1);
                                                v0 = sll(v0, 2);
                                                v0 = addu(s1, v0);
                                                lw(s4, v0, 284);
                                                if (s4 != 0) {
                                                    // 0x0031a2dc
                                                    charge(ctx, 8);
                                                    lhu(s3, sp, 0xDC);
                                                    lhu(s2, s0, 30);
                                                    lw(v1, s4, 20);
                                                    v0 = sll(s3, 2);
                                                    v0 = addu(v1, v0);
                                                    lw(a0, v0, 0);
                                                    if (a0 != 0) {
                                                        // 0x0031a2fc
                                                        charge(ctx, 7);
                                                        jal(ctx, 0x31A2FCu, gen::fn_sub_31D700_0031d700);
                                                        v1 = s2 & 0xFFFF;
                                                        a0 = sll(v1, 2);
                                                        lw(v1, s4, 20);
                                                        v1 = addu(v1, a0);
                                                        sw(v0, v1, 0);
                                                    }
                                                    // 0x0031a318
                                                    charge(ctx, 7);
                                                    lw(v1, s4, 32);
                                                    v0 = s3 & 0xFFFF;
                                                    v0 = sll(v0, 2);
                                                    v0 = addu(v1, v0);
                                                    lw(a0, v0, 0);
                                                    if (a0 != 0) {
                                                        // 0x0031a334
                                                        charge(ctx, 9);
                                                        jal(ctx, 0x31A334u, gen::fn_sub_31E0B0_0031e0b0);
                                                        v1 = s2 & 0xFFFF;
                                                        a0 = sll(v1, 2);
                                                        lw(v1, s4, 32);
                                                        v1 = addu(v1, a0);
                                                        sw(v0, v1, 0);
                                                    }
                                                }
                                            }
                                        } else {
                                            // 0x00319a64
                                            charge(ctx, 3);
                                            v1 = a0 | 0x2;
                                            if (v0 == v1) {
                                                // 0x0031a12c
                                                charge(ctx, 10);
                                                lhu(v0, s0, 28);
                                                v0 = addiu(v0, 1);
                                                sh(v0, s0, 28);
                                                sh(zero, s0, 30);
                                                lw(a0, s0, 0);
                                                lw(a1, sp, 0x94);
                                                jal(ctx, 0x31A144u, gen::fn_sub_4C5620_004c5620);
                                            } else {
                                                // 0x00319a70
                                                charge(ctx, 3);
                                                v1 = a0 | 0x4;
                                                if (v0 == v1) {
                                                    // 0x0031a108
                                                    charge(ctx, 9);
                                                    lhu(v0, s0, 30);
                                                    v0 = addiu(v0, 1);
                                                    sh(v0, s0, 30);
                                                    lw(a0, s0, 0);
                                                    lw(a1, sp, 0x94);
                                                    jal(ctx, 0x31A11Cu, gen::fn_sub_4C5620_004c5620);
                                                } else {
                                                    // 0x00319a7c
                                                    charge(ctx, 3);
                                                    v1 = a0 | 0x5;
                                                    if (v0 == v1) {
                                                        // 0x0031a064
                                                        charge(ctx, 10);
                                                        lhu(v1, s0, 28);
                                                        v0 = sll(v1, 2);
                                                        v0 = addu(v0, v1);
                                                        v0 = sll(v0, 3);
                                                        v0 = subu(v0, v1);
                                                        v0 = sll(v0, 2);
                                                        v0 = addu(s1, v0);
                                                        lw(v0, v0, 280);
                                                        if (v0 == 0) {
                                                            // 0x0031a08c
                                                            charge(ctx, 11);
                                                            lhu(a0, sp, 0xDE);
                                                            jal(ctx, 0x31A090u, gen::fn_sub_311310_00311310);
                                                            lhu(a0, s0, 28);
                                                            v1 = sll(a0, 2);
                                                            v1 = addu(v1, a0);
                                                            v1 = sll(v1, 3);
                                                            v1 = subu(v1, a0);
                                                            v1 = sll(v1, 2);
                                                            v1 = addu(s1, v1);
                                                            sw(v0, v1, 280);
                                                        }
                                                        // 0x0031a0b8
                                                        charge(ctx, 20);
                                                        lhu(v1, s0, 28);
                                                        v0 = sll(v1, 2);
                                                        v0 = addu(v0, v1);
                                                        v0 = sll(v0, 3);
                                                        v0 = subu(v0, v1);
                                                        v0 = sll(v0, 2);
                                                        v0 = addu(s1, v0);
                                                        lw(a0, v0, 280);
                                                        lhu(v1, s0, 30);
                                                        v0 = sll(v1, 2);
                                                        v0 = addu(v0, v1);
                                                        v1 = sll(v0, 4);
                                                        lw(v0, a0, 0);
                                                        a1 = addu(v0, v1);
                                                        lw(a0, s0, 0);
                                                        lw(a2, sp, 0x94);
                                                        jal(ctx, 0x31A0F8u, gen::fn_sub_4C5250_004c5250);
                                                    } else {
                                                        // 0x00319a88
                                                        charge(ctx, 3);
                                                        v1 = a0 | 0x1;
                                                        if (v0 == v1) {
                                                            // 0x00319fb4
                                                            charge(ctx, 10);
                                                            lhu(v1, s0, 28);
                                                            v0 = sll(v1, 2);
                                                            v0 = addu(v0, v1);
                                                            v0 = sll(v0, 3);
                                                            v0 = subu(v0, v1);
                                                            v0 = sll(v0, 2);
                                                            v0 = addu(s1, v0);
                                                            lw(v0, v0, 280);
                                                            if (v0 == 0) {
                                                                // 0x00319fdc
                                                                charge(ctx, 11);
                                                                lhu(a0, sp, 0xDE);
                                                                jal(ctx, 0x319FE0u, gen::fn_sub_311310_00311310);
                                                                lhu(a0, s0, 28);
                                                                v1 = sll(a0, 2);
                                                                v1 = addu(v1, a0);
                                                                v1 = sll(v1, 3);
                                                                v1 = subu(v1, a0);
                                                                v1 = sll(v1, 2);
                                                                v1 = addu(s1, v1);
                                                                sw(v0, v1, 280);
                                                            }
                                                            // 0x0031a008
                                                            charge(ctx, 23);
                                                            a1 = 0x950000;
                                                            a1 = addiu(a1, 29136);  // &0x9571D0
                                                            lhu(v1, s0, 28);
                                                            v0 = sll(v1, 2);
                                                            v0 = addu(v0, v1);
                                                            v0 = sll(v0, 3);
                                                            v0 = subu(v0, v1);
                                                            v0 = sll(v0, 2);
                                                            v0 = addu(s1, v0);
                                                            lw(a0, v0, 280);
                                                            lhu(v1, s0, 30);
                                                            v0 = sll(v1, 2);
                                                            v0 = addu(v0, v1);
                                                            v1 = sll(v0, 4);
                                                            lw(v0, a0, 0);
                                                            v0 = addu(v0, v1);
                                                            sw(a1, v0, 64);
                                                            lw(a0, s0, 0);
                                                            lw(a1, sp, 0x94);
                                                            jal(ctx, 0x31A054u, gen::fn_sub_4C5620_004c5620);
                                                        } else {
                                                            // 0x00319a94
                                                            charge(ctx, 3);
                                                            v1 = 30;
                                                            if (v0 != v1) {
                                                                // 0x00319aa0
                                                                charge(ctx, 3);
                                                                v1 = 16;
                                                                if (v0 == v1) {
                                                                    // 0x00319f0c
                                                                    charge(ctx, 4);
                                                                    lhu(v0, s1, 216);
                                                                    v0 = v0 & 0x4000;
                                                                    if (v0 == 0) {
                                                                        // 0x00319f40
                                                                        charge(ctx, 3);
                                                                        lw(v0, s1, 220);
                                                                        if (v0 == 0) {
                                                                            // 0x00319f4c
                                                                            charge(ctx, 3);
                                                                            lw(v0, s0, 20);
                                                                            if (v0 == 0) {
                                                                                // 0x00319f58
                                                                                charge(ctx, 3);
                                                                                lw(v0, s0, 16);
                                                                                if (v0 == 0) {
                                                                                    // 0x00319f64
                                                                                    charge(ctx, 14);
                                                                                    lw(v0, s0, 0);
                                                                                    lw(v1, v0, 12);
                                                                                    lw(v0, s0, 56);
                                                                                    v0 = addu(v0, v1);
                                                                                    sw(v0, sp, 0xD0);
                                                                                    lw(v0, s0, 60);
                                                                                    v0 = subu(v0, v1);
                                                                                    sw(v0, sp, 0xD4);
                                                                                    a0 = 3;
                                                                                    a1 = 1;
                                                                                    a2 = addiu(sp, 0xD0);
                                                                                    jal(ctx, 0x319F90u, gen::fn_sub_4C58A0_004c58a0);
                                                                                    sw(v0, s0, 20);
                                                                                }
                                                                            }
                                                                        }
                                                                        // 0x00319f9c
                                                                        charge(ctx, 6);
                                                                        lw(a0, s0, 0);
                                                                        lw(a1, sp, 0x94);
                                                                        jal(ctx, 0x319FA4u, gen::fn_sub_4C5620_004c5620);
                                                                    } else {
                                                                        // 0x00319f1c
                                                                        charge(ctx, 3);
                                                                        lw(v0, s1, 220);
                                                                        if (v0 == 0) {
                                                                            // 0x00319f28
                                                                            charge(ctx, 6);
                                                                            lw(a0, s0, 0);
                                                                            jal(ctx, 0x319F2Cu, gen::fn_sub_4920A0_004920a0);
                                                                            sw(v0, s1, 220);
                                                                        }
                                                                    }
                                                                } else {
                                                                    // 0x00319aac
                                                                    charge(ctx, 3);
                                                                    v1 = 43;
                                                                    if (v0 == v1) {
                                                                        // 0x00319ca4
                                                                        charge(ctx, 4);
                                                                        lhu(v0, s1, 216);
                                                                        v0 = v0 & 0x4000;
                                                                        if (v0 == 0) {
                                                                            // 0x00319d78
                                                                            charge(ctx, 3);
                                                                            lw(v0, s0, 20);
                                                                            if (v0 == 0) {
                                                                                // 0x00319d84
                                                                                charge(ctx, 3);
                                                                                lw(v0, s0, 16);
                                                                                if (v0 != 0) {
                                                                                    goto L_00319e1c;
                                                                                }
                                                                                // 0x00319d90
                                                                                charge(ctx, 35);
                                                                                lw(v0, s0, 0);
                                                                                lw(v1, v0, 12);
                                                                                lw(v0, s0, 56);
                                                                                v0 = addu(v0, v1);
                                                                                sw(v0, sp, 0xD0);
                                                                                lw(v0, s0, 60);
                                                                                v0 = subu(v0, v1);
                                                                                sw(v0, sp, 0xD4);
                                                                                a0 = 3;
                                                                                a1 = 1;
                                                                                a2 = addiu(sp, 0xD0);
                                                                                jal(ctx, 0x319DBCu, gen::fn_sub_4C58A0_004c58a0);
                                                                                v1 = 0x780000;
                                                                                v1 = addiu(v1, -6944);  // &0x77E4E0
                                                                                sd(v1, sp, 0x0);
                                                                                sd(zero, sp, 0x8);
                                                                                v1 = 0x6A0000;
                                                                                v1 = addiu(v1, -21560);  // "mdlManager.c"
                                                                                sd(v1, sp, 0x10);
                                                                                v1 = 5153;
                                                                                sd(v1, sp, 0x18);
                                                                                a0 = 7;
                                                                                a1 = 0;
                                                                                a2 = 0;
                                                                                a3 = 0;
                                                                                t0 = v0;
                                                                                t1 = 0;
                                                                                t2 = 0;
                                                                                t3 = 0;
                                                                                jal(ctx, 0x319E08u, gen::fn_sub_10C1A0_0010c1a0);
                                                                                sw(v0, s0, 8);
                                                                                goto L_00319ef4;
                                                                            }
                                                                        L_00319e1c:
                                                                            charge(ctx, 3);
                                                                            lw(v0, s0, 12);
                                                                            if (v0 == 0) {
                                                                                // 0x00319e28
                                                                                charge(ctx, 14);
                                                                                lhu(v0, sp, 0xDE);
                                                                                a0 = sll(v0, 2);
                                                                                a1 = 0x40000;
                                                                                v0 = 0x960000;
                                                                                lw(v0, v0, 376);  // 0x960178
                                                                                jalr(ctx, 0x319E3Cu, v0.u());
                                                                                sw(v0, s0, 12);
                                                                                lhu(v1, sp, 0xDE);
                                                                                a2 = sll(v1, 2);
                                                                                a0 = v0;
                                                                                a1 = 0;
                                                                                jal(ctx, 0x319E58u, gen::fn_memset_00521408);
                                                                            }
                                                                            // 0x00319e60
                                                                            charge(ctx, 37);
                                                                            lw(v0, s0, 0);
                                                                            lw(v1, v0, 12);
                                                                            lw(v0, s0, 56);
                                                                            v0 = addu(v0, v1);
                                                                            sw(v0, sp, 0xD0);
                                                                            lw(v0, s0, 60);
                                                                            v0 = subu(v0, v1);
                                                                            sw(v0, sp, 0xD4);
                                                                            a0 = 3;
                                                                            a1 = 1;
                                                                            a2 = addiu(sp, 0xD0);
                                                                            jal(ctx, 0x319E8Cu, gen::fn_sub_4C58A0_004c58a0);
                                                                            v1 = 0x780000;
                                                                            v1 = addiu(v1, -6944);  // &0x77E4E0
                                                                            sd(v1, sp, 0x0);
                                                                            sd(zero, sp, 0x8);
                                                                            v1 = 0x6A0000;
                                                                            v1 = addiu(v1, -21560);  // "mdlManager.c"
                                                                            sd(v1, sp, 0x10);
                                                                            v1 = 5166;
                                                                            sd(v1, sp, 0x18);
                                                                            a0 = 7;
                                                                            a1 = 0;
                                                                            a2 = 0;
                                                                            a3 = 0;
                                                                            t0 = v0;
                                                                            t1 = 0;
                                                                            t2 = 0;
                                                                            t3 = 0;
                                                                            jal(ctx, 0x319ED8u, gen::fn_sub_10C1A0_0010c1a0);
                                                                            lhu(v1, s0, 30);
                                                                            a0 = sll(v1, 2);
                                                                            lw(v1, s0, 12);
                                                                            v1 = addu(v1, a0);
                                                                            sw(v0, v1, 0);
                                                                        L_00319ef4:
                                                                            charge(ctx, 6);
                                                                            lw(a0, s0, 0);
                                                                            lw(a1, sp, 0x94);
                                                                            jal(ctx, 0x319EFCu, gen::fn_sub_4C5620_004c5620);
                                                                        } else {
                                                                            // 0x00319cb4
                                                                            charge(ctx, 3);
                                                                            lw(v0, s1, 892);
                                                                            if (v0 == 0) {
                                                                                // 0x00319cc0
                                                                                charge(ctx, 21);
                                                                                lhu(s2, sp, 0xDE);
                                                                                v0 = sll(s2, 3);
                                                                                s3 = addiu(v0, 16);
                                                                                a0 = s3;
                                                                                a1 = 0x40000;
                                                                                v0 = 0x960000;
                                                                                lw(v0, v0, 376);  // 0x960178
                                                                                jalr(ctx, 0x319CDCu, v0.u());
                                                                                s4 = v0;
                                                                                a0 = s4;
                                                                                a1 = 0;
                                                                                a2 = s3;
                                                                                jal(ctx, 0x319CF4u, gen::fn_memset_00521408);
                                                                                v0 = addiu(s4, 16);
                                                                                sw(v0, s4, 0);
                                                                                sh(s2, s4, 12);
                                                                                v0 = 1;
                                                                                sh(v0, s4, 14);
                                                                                sw(s4, s1, 892);
                                                                            }
                                                                            // 0x00319d14
                                                                            charge(ctx, 8);
                                                                            a0 = 0x780000;
                                                                            a0 = addiu(a0, -6944);  // &0x77E4E0
                                                                            lw(a1, s0, 0);
                                                                            jal(ctx, 0x319D20u, gen::fn_sub_4B79D0_004b79d0);
                                                                            lw(v1, s1, 220);
                                                                            if (v1 != 0) {
                                                                                // 0x00319d58
                                                                                charge(ctx, 8);
                                                                                lw(a1, s1, 892);
                                                                                lhu(v1, s0, 30);
                                                                                a0 = sll(v1, 3);
                                                                                lw(v1, a1, 0);
                                                                                v1 = addu(v1, a0);
                                                                                sw(v0, v1, 0);
                                                                            } else {
                                                                                // 0x00319d34
                                                                                charge(ctx, 9);
                                                                                lw(v1, s1, 892);
                                                                                sw(v0, v1, 4);
                                                                                a0 = 0x780000;
                                                                                a0 = addiu(a0, -6944);  // &0x77E4E0
                                                                                a1 = v0;
                                                                                jal(ctx, 0x319D48u, gen::fn_sub_4B7760_004b7760);
                                                                            }
                                                                        }
                                                                    } else {
                                                                        // 0x00319ab8
                                                                        charge(ctx, 3);
                                                                        v1 = 27;
                                                                        if (v0 == v1) {
                                                                            // 0x00319c00
                                                                            charge(ctx, 10);
                                                                            lhu(v1, s0, 28);
                                                                            v0 = sll(v1, 2);
                                                                            v0 = addu(v0, v1);
                                                                            v0 = sll(v0, 3);
                                                                            v0 = subu(v0, v1);
                                                                            v0 = sll(v0, 2);
                                                                            v0 = addu(s1, v0);
                                                                            lw(v0, v0, 280);
                                                                            if (v0 == 0) {
                                                                                // 0x00319c28
                                                                                charge(ctx, 11);
                                                                                lhu(a0, sp, 0xDE);
                                                                                jal(ctx, 0x319C2Cu, gen::fn_sub_311310_00311310);
                                                                                lhu(a0, s0, 28);
                                                                                v1 = sll(a0, 2);
                                                                                v1 = addu(v1, a0);
                                                                                v1 = sll(v1, 3);
                                                                                v1 = subu(v1, a0);
                                                                                v1 = sll(v1, 2);
                                                                                v1 = addu(s1, v1);
                                                                                sw(v0, v1, 280);
                                                                            }
                                                                            // 0x00319c54
                                                                            charge(ctx, 20);
                                                                            lw(a0, s0, 0);
                                                                            jal(ctx, 0x319C58u, gen::fn_sub_4B6A40_004b6a40);
                                                                            lhu(a0, s0, 28);
                                                                            v1 = sll(a0, 2);
                                                                            v1 = addu(v1, a0);
                                                                            v1 = sll(v1, 3);
                                                                            v1 = subu(v1, a0);
                                                                            v1 = sll(v1, 2);
                                                                            v1 = addu(s1, v1);
                                                                            lw(a1, v1, 280);
                                                                            lhu(a0, s0, 30);
                                                                            v1 = sll(a0, 2);
                                                                            v1 = addu(v1, a0);
                                                                            a0 = sll(v1, 4);
                                                                            lw(v1, a1, 0);
                                                                            v1 = addu(v1, a0);
                                                                            sw(v0, v1, 64);
                                                                        } else {
                                                                            // 0x00319ac4
                                                                            charge(ctx, 3);
                                                                            v1 = 35;
                                                                            if (v0 == v1) {
                                                                                // 0x00319bc4
                                                                                charge(ctx, 15);
                                                                                lw(a0, s0, 0);
                                                                                jal(ctx, 0x319BC8u, gen::fn_sub_4BDA10_004bda10);
                                                                                s2 = v0;
                                                                                a0 = s2;
                                                                                a1 = 0x1A0000;
                                                                                a1 = addiu(a1, 5040);  // &sub_1A13B0
                                                                                a2 = addiu(s0, 64);
                                                                                jal(ctx, 0x319BE4u, gen::fn_sub_4D0DC0_004d0dc0);
                                                                                a0 = s2;
                                                                                jal(ctx, 0x319BF0u, gen::fn_sub_4D0D10_004d0d10);
                                                                            } else {
                                                                                // 0x00319ad0
                                                                                charge(ctx, 3);
                                                                                v1 = 22;
                                                                                if (v0 == v1) {
                                                                                    // 0x00319ae4
                                                                                    charge(ctx, 4);
                                                                                    lhu(v0, s1, 216);
                                                                                    v0 = v0 & 0x4000;
                                                                                    if (v0 == 0) {
                                                                                        // 0x00319b30
                                                                                        charge(ctx, 37);
                                                                                        lw(v0, s0, 0);
                                                                                        lw(v1, v0, 12);
                                                                                        lw(v0, s0, 56);
                                                                                        v0 = addu(v0, v1);
                                                                                        sw(v0, sp, 0xD0);
                                                                                        lw(v0, s0, 60);
                                                                                        v0 = subu(v0, v1);
                                                                                        sw(v0, sp, 0xD4);
                                                                                        a0 = 3;
                                                                                        a1 = 1;
                                                                                        a2 = addiu(sp, 0xD0);
                                                                                        jal(ctx, 0x319B5Cu, gen::fn_sub_4C58A0_004c58a0);
                                                                                        sd(zero, sp, 0x0);
                                                                                        sd(zero, sp, 0x8);
                                                                                        v1 = 0x6A0000;
                                                                                        v1 = addiu(v1, -21560);  // "mdlManager.c"
                                                                                        sd(v1, sp, 0x10);
                                                                                        v1 = 5081;
                                                                                        sd(v1, sp, 0x18);
                                                                                        a0 = 8;
                                                                                        a1 = 0;
                                                                                        a2 = 0;
                                                                                        a3 = 0;
                                                                                        t0 = v0;
                                                                                        t1 = 0;
                                                                                        t2 = 0;
                                                                                        t3 = 0;
                                                                                        jal(ctx, 0x319BA0u, gen::fn_sub_10C1A0_0010c1a0);
                                                                                        sw(v0, s0, 4);
                                                                                        lw(a0, s0, 0);
                                                                                        lw(a1, sp, 0x94);
                                                                                        jal(ctx, 0x319BB4u, gen::fn_sub_4C5620_004c5620);
                                                                                    } else {
                                                                                        // 0x00319af4
                                                                                        charge(ctx, 15);
                                                                                        lw(a0, s0, 0);
                                                                                        jal(ctx, 0x319AF8u, gen::fn_sub_4C8680_004c8680);
                                                                                        s2 = v0;
                                                                                        a0 = s2;
                                                                                        a1 = 0x1A0000;
                                                                                        a1 = addiu(a1, 5040);  // &sub_1A13B0
                                                                                        a2 = addiu(s0, 64);
                                                                                        jal(ctx, 0x319B14u, gen::fn_sub_4D0DC0_004d0dc0);
                                                                                        a0 = s2;
                                                                                        jal(ctx, 0x319B20u, gen::fn_sub_4D0D10_004d0d10);
                                                                                    }
                                                                                } else {
                                                                                    // 0x00319adc
                                                                                    charge(ctx, 2);
                                                                                    // 0x0031aa70
                                                                                    charge(ctx, 4);
                                                                                    lw(a0, s0, 0);
                                                                                    lw(a1, sp, 0x94);
                                                                                    jal(ctx, 0x31AA78u, gen::fn_sub_4C5620_004c5620);
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
                                        continue;
                                    }
                                L_0031a428:
                                    charge(ctx, 4);
                                    lhu(v0, s1, 216);
                                    v0 = v0 & 0x4000;
                                    if (v0 == 0) {
                                        // 0x0031a50c
                                        charge(ctx, 34);
                                        a0 = 16;
                                        a1 = 0x40000;
                                        v0 = 0x960000;
                                        lw(v0, v0, 376);  // 0x960178
                                        jalr(ctx, 0x31A51Cu, v0.u());
                                        s2 = v0;
                                        lw(v1, s0, 0);
                                        lw(a0, v1, 12);
                                        lw(v1, s0, 56);
                                        v1 = addu(v1, a0);
                                        sw(v1, sp, 0xD0);
                                        lw(v1, s0, 60);
                                        v1 = subu(v1, a0);
                                        sw(v1, sp, 0xD4);
                                        lw(v1, sp, 0x90);
                                        sw(v1, v0, 0);
                                        lhu(v1, s0, 30);
                                        sh(v1, v0, 4);
                                        a0 = 3;
                                        a1 = 1;
                                        a2 = addiu(sp, 0xD0);
                                        jal(ctx, 0x31A564u, gen::fn_sub_4C58A0_004c58a0);
                                        sw(v0, s2, 8);
                                        lw(a0, s0, 0);
                                        lw(a1, sp, 0x94);
                                        jal(ctx, 0x31A578u, gen::fn_sub_4C5620_004c5620);
                                        lw(v0, s0, 24);
                                        sw(v0, s2, 12);
                                        sw(s2, s0, 24);
                                    } else {
                                        // 0x0031a438
                                        charge(ctx, 3);
                                        lw(v0, s1, 860);
                                        if (v0 == 0) {
                                            // 0x0031a444
                                            charge(ctx, 21);
                                            lhu(s2, sp, 0xDE);
                                            v0 = sll(s2, 3);
                                            s3 = addiu(v0, 8);
                                            a0 = s3;
                                            a1 = 0x40000;
                                            v0 = 0x960000;
                                            lw(v0, v0, 376);  // 0x960178
                                            jalr(ctx, 0x31A460u, v0.u());
                                            s4 = v0;
                                            a0 = s4;
                                            a1 = 0;
                                            a2 = s3;
                                            jal(ctx, 0x31A478u, gen::fn_memset_00521408);
                                            v0 = addiu(s4, 8);
                                            sw(v0, s4, 0);
                                            sh(s2, s4, 4);
                                            v0 = 1;
                                            sh(v0, s4, 6);
                                            sw(s4, s1, 860);
                                        }
                                        // 0x0031a498
                                        charge(ctx, 8);
                                        lw(a0, s1, 860);
                                        lhu(v0, s0, 30);
                                        v1 = sll(v0, 3);
                                        lw(v0, a0, 0);
                                        v0 = addu(v0, v1);
                                        lw(v0, v0, 0);
                                        if (v0 == 0) {
                                            // 0x0031a4b8
                                            charge(ctx, 8);
                                            jal(ctx, 0x31A4B8u, gen::fn_sub_320230_00320230);
                                            lw(a1, s1, 860);
                                            lhu(v1, s0, 30);
                                            a0 = sll(v1, 3);
                                            lw(v1, a1, 0);
                                            v1 = addu(v1, a0);
                                            sw(v0, v1, 0);
                                        }
                                        // 0x0031a4d8
                                        charge(ctx, 13);
                                        lw(a0, s1, 860);
                                        lhu(v0, s0, 30);
                                        v1 = sll(v0, 3);
                                        lw(v0, a0, 0);
                                        v0 = addu(v0, v1);
                                        lw(a0, s0, 0);
                                        lw(a1, v0, 0);
                                        lw(a2, sp, 0x90);
                                        lw(a3, s1, 220);
                                        jal(ctx, 0x31A4FCu, gen::fn_sub_320880_00320880);
                                    }
                                }
                            }
                        }
                    }
                }
                continue;
            }
        }
        break;
    }
    // 0x0031aa98 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    v0 = 1;
    ld(ra, sp, 0x80);
    lq(s5, sp, 0x70);
    lq(s4, sp, 0x60);
    lq(s3, sp, 0x50);
    lq(s2, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    sp = addiu(sp, 0xE0);
}

// 0x0031AAD0 sub_31AAD0 -- 1864 bytes; frame 0x110: ra sp+0xB0, fp sp+0xA0 (sq), s7 sp+0x90 (sq), s6 sp+0x80 (sq), s5 sp+0x70 (sq), s4 sp+0x60 (sq), s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), s3 sp+0x104
// "mdlManager.c": rebuilds or releases a model record (RwFree slot 0x96017C, sub_320230 / sub_320880).
void sub_31AAD0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x0031aad0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x110);
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
    s5 = a0;
    lw(s1, a0, 1064);
    s3 = 1;
    fp = s3;
    sw(s3, sp, 0x104);
    lw(a0, s1, 4);
    if (a0 != 0) {
        // 0x0031ab1c
        charge(ctx, 9);
        a1 = addiu(sp, 0x108);
        a2 = addiu(sp, 0x10C);
        jal(ctx, 0x31AB24u, gen::fn_sub_10C3A0_0010c3a0);
        s0 = v0;
        lw(v1, sp, 0x108);
        v0 = s3;
        if (v1 != v0) {
            // 0x0031ab80
            charge(ctx, 2);
            fp = 0;
            s3 = 0;
        } else {
            // 0x0031ab40
            charge(ctx, 16);
            a0 = s0;
            a1 = 0x1A0000;
            a1 = addiu(a1, 5040);  // &sub_1A13B0
            a2 = addiu(s1, 64);
            jal(ctx, 0x31AB50u, gen::fn_sub_4D0DC0_004d0dc0);
            a0 = s0;
            jal(ctx, 0x31AB5Cu, gen::fn_sub_4D0D10_004d0d10);
            lw(a0, sp, 0x10C);
            a1 = 0;
            jal(ctx, 0x31AB6Cu, gen::fn_sub_4C5780_004c5780);
            sw(zero, s1, 4);
        }
    }
    // 0x0031ab88
    charge(ctx, 3);
    lw(a0, s1, 8);
    if (a0 != 0) {
        // 0x0031ab94
        charge(ctx, 9);
        a1 = addiu(sp, 0x108);
        a2 = addiu(sp, 0x10C);
        jal(ctx, 0x31AB9Cu, gen::fn_sub_10C3A0_0010c3a0);
        s4 = v0;
        lw(v1, sp, 0x108);
        v0 = 1;
        if (v1 != v0) {
            // 0x0031ac50
            charge(ctx, 2);
            s3 = 0;
            sw(zero, sp, 0x104);
        } else {
            // 0x0031abb8
            charge(ctx, 3);
            lw(v0, s5, 892);
            if (v0 == 0) {
                // 0x0031abc4
                charge(ctx, 21);
                lhu(s6, s1, 32);
                v0 = sll(s6, 3);
                s0 = addiu(v0, 16);
                a0 = s0;
                a1 = 0x40000;
                v0 = 0x960000;
                lw(v0, v0, 376);  // 0x960178
                jalr(ctx, 0x31ABE0u, v0.u());
                s2 = v0;
                a0 = s2;
                a1 = 0;
                a2 = s0;
                jal(ctx, 0x31ABF8u, gen::fn_memset_00521408);
                v0 = addiu(s2, 16);
                sw(v0, s2, 0);
                sh(s6, s2, 12);
                v0 = 1;
                sh(v0, s2, 14);
                sw(s2, s5, 892);
            }
            // 0x0031ac18
            charge(ctx, 14);
            lw(v0, s5, 892);
            sw(s4, v0, 4);
            a0 = 0x780000;
            a0 = addiu(a0, -6944);  // &0x77E4E0
            a1 = s4;
            jal(ctx, 0x31AC2Cu, gen::fn_sub_4B7760_004b7760);
            lw(a0, sp, 0x10C);
            a1 = 0;
            jal(ctx, 0x31AC3Cu, gen::fn_sub_4C5780_004c5780);
            sw(zero, s1, 8);
        }
    }
    // 0x0031ac58
    charge(ctx, 3);
    lw(v0, s1, 12);
    if (v0 != 0) {
        // 0x0031ac64
        charge(ctx, 3);
        s4 = 0;
        for (;;) {
            // 0x0031ad54
            charge(ctx, 4);
            lhu(v0, s1, 32);
            v0 = sltu(s4, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0031ac70
            charge(ctx, 6);
            lw(v0, s1, 12);
            s6 = sll(s4, 2);
            v0 = addu(v0, s6);
            lw(a0, v0, 0);
            if (a0 != 0) {
                // 0x0031ac88
                charge(ctx, 9);
                a1 = addiu(sp, 0x108);
                a2 = addiu(sp, 0x10C);
                jal(ctx, 0x31AC90u, gen::fn_sub_10C3A0_0010c3a0);
                sq(v0, sp, 0xF0);
                lw(v1, sp, 0x108);
                v0 = 1;
                if (v1 != v0) {
                    // 0x0031ad4c
                    charge(ctx, 1);
                    s3 = 0;
                } else {
                    // 0x0031acac
                    charge(ctx, 3);
                    lw(v0, s5, 892);
                    if (v0 == 0) {
                        // 0x0031acb8
                        charge(ctx, 21);
                        lhu(s7, s1, 32);
                        v0 = sll(s7, 3);
                        s0 = addiu(v0, 16);
                        a0 = s0;
                        a1 = 0x40000;
                        v0 = 0x960000;
                        lw(v0, v0, 376);  // 0x960178
                        jalr(ctx, 0x31ACD4u, v0.u());
                        s2 = v0;
                        a0 = s2;
                        a1 = 0;
                        a2 = s0;
                        jal(ctx, 0x31ACECu, gen::fn_memset_00521408);
                        v0 = addiu(s2, 16);
                        sw(v0, s2, 0);
                        sh(s7, s2, 12);
                        v0 = 1;
                        sh(v0, s2, 14);
                        sw(s2, s5, 892);
                    }
                    // 0x0031ad0c
                    charge(ctx, 16);
                    lw(a0, s5, 892);
                    v0 = s4 & 0xFFFF;
                    v1 = sll(v0, 3);
                    lw(v0, a0, 0);
                    v1 = addu(v0, v1);
                    lq(v0, sp, 0xF0);
                    sw(v0, v1, 0);
                    lw(a0, sp, 0x10C);
                    a1 = 0;
                    jal(ctx, 0x31AD30u, gen::fn_sub_4C5780_004c5780);
                    lw(v0, s1, 12);
                    v0 = addu(v0, s6);
                    sw(zero, v0, 0);
                }
            }
            // 0x0031ad50
            charge(ctx, 1);
            s4 = addiu(s4, 1);
        }
    }
    // 0x0031ad64
    charge(ctx, 3);
    lw(t0, s1, 20);
    if (t0 == 0) {
        // 0x0031ad70
        charge(ctx, 3);
        lw(v0, s1, 16);
        if (v0 != 0) {
            goto L_0031ad7c;
        }
        goto L_0031ae44;
    }
L_0031ad7c:
    charge(ctx, 3);
    v1 = 1;
    if (fp == v1) {
        // 0x0031ad88
        charge(ctx, 3);
        lw(v0, sp, 0x104);
        if (v0 != v1) {
            goto L_0031ae40;
        }
        // 0x0031ad94
        charge(ctx, 2);
        if (t0 == 0) {
            // 0x0031adf0
            charge(ctx, 9);
            lw(a0, s1, 16);
            a1 = addiu(sp, 0x108);
            a2 = addiu(sp, 0x10C);
            jal(ctx, 0x31ADFCu, gen::fn_sub_10C3A0_0010c3a0);
            lw(a0, sp, 0x108);
            v1 = 1;
            if (a0 != v1) {
                // 0x0031ae34
                charge(ctx, 3);
                s3 = 0;
            } else {
                // 0x0031ae14
                charge(ctx, 8);
                sw(v0, s5, 220);
                lw(a0, sp, 0x10C);
                a1 = 0;
                jal(ctx, 0x31AE20u, gen::fn_sub_4C5780_004c5780);
                sw(zero, s1, 16);
            }
        } else {
            // 0x0031ad9c
            charge(ctx, 21);
            sd(zero, sp, 0x0);
            sd(zero, sp, 0x8);
            v0 = 0x6A0000;
            v0 = addiu(v0, -21560);  // "mdlManager.c"
            sd(v0, sp, 0x10);
            v0 = 5513;
            sd(v0, sp, 0x18);
            a0 = 2;
            a1 = 0;
            a2 = 0;
            a3 = 0;
            t1 = 0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x31ADD4u, gen::fn_sub_10C1A0_0010c1a0);
            sw(v0, s1, 16);
            sw(zero, s1, 20);
            s3 = 0;
        }
        goto L_0031ae44;
    }
L_0031ae40:
    charge(ctx, 1);
    s3 = 0;
L_0031ae44:
    charge(ctx, 3);
    lw(s4, s1, 24);
    if (s4 != 0) {
        // 0x0031ae50
        charge(ctx, 3);
        lw(v0, s5, 220);
        if (v0 == 0) {
            // 0x0031af70
            charge(ctx, 1);
            s3 = 0;
        } else {
            // 0x0031ae5c
            charge(ctx, 2);
            for (;;) {
                // 0x0031af5c
                charge(ctx, 2);
                if (s4 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0031ae64
                charge(ctx, 3);
                lw(v0, s5, 860);
                if (v0 == 0) {
                    // 0x0031ae70
                    charge(ctx, 21);
                    lhu(s6, s1, 32);
                    v0 = sll(s6, 3);
                    s0 = addiu(v0, 8);
                    a0 = s0;
                    a1 = 0x40000;
                    v0 = 0x960000;
                    lw(v0, v0, 376);  // 0x960178
                    jalr(ctx, 0x31AE8Cu, v0.u());
                    s2 = v0;
                    a0 = s2;
                    a1 = 0;
                    a2 = s0;
                    jal(ctx, 0x31AEA4u, gen::fn_memset_00521408);
                    v0 = addiu(s2, 8);
                    sw(v0, s2, 0);
                    sh(s6, s2, 4);
                    v0 = 1;
                    sh(v0, s2, 6);
                    sw(s2, s5, 860);
                }
                // 0x0031aec4
                charge(ctx, 8);
                lw(a0, s5, 860);
                lhu(v0, s4, 4);
                v1 = sll(v0, 3);
                lw(v0, a0, 0);
                v0 = addu(v0, v1);
                lw(v0, v0, 0);
                if (v0 == 0) {
                    // 0x0031aee4
                    charge(ctx, 8);
                    jal(ctx, 0x31AEE4u, gen::fn_sub_320230_00320230);
                    lw(a1, s5, 860);
                    lhu(v1, s4, 4);
                    a0 = sll(v1, 3);
                    lw(v1, a1, 0);
                    v1 = addu(v1, a0);
                    sw(v0, v1, 0);
                }
                // 0x0031af04
                charge(ctx, 22);
                lw(a0, s5, 860);
                lhu(v0, s4, 4);
                v1 = sll(v0, 3);
                lw(v0, a0, 0);
                v0 = addu(v0, v1);
                lw(a0, s4, 8);
                lw(a1, v0, 0);
                lw(a2, s4, 0);
                lw(a3, s5, 220);
                jal(ctx, 0x31AF28u, gen::fn_sub_320880_00320880);
                lw(a0, s4, 8);
                a1 = 0;
                jal(ctx, 0x31AF38u, gen::fn_sub_4C5780_004c5780);
                lw(s0, s4, 12);
                a0 = s4;
                v0 = 0x960000;
                lw(v0, v0, 380);  // 0x96017C
                jalr(ctx, 0x31AF50u, v0.u());
                s4 = s0;
            }
            // 0x0031af64
            charge(ctx, 3);
            sw(zero, s1, 24);
        }
    }
    // 0x0031af74
    charge(ctx, 3);
    v0 = 1;
    if (s3 == v0) {
        // 0x0031af80
        charge(ctx, 3);
        s4 = 0;
        for (;;) {
            // 0x0031b1d4
            charge(ctx, 3);
            v0 = sltiu(s4, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0031af8c
            charge(ctx, 7);
            v1 = sll(s4, 2);
            s7 = addu(s1, v1);
            v0 = addiu(s7, 40);
            sq(v0, sp, 0xE0);
            lw(v0, s7, 40);
            if (v0 != 0) {
                // 0x0031afa8
                charge(ctx, 11);
                s2 = 0;
                v0 = addu(v1, s4);
                v0 = sll(v0, 3);
                v0 = subu(v0, s4);
                v0 = sll(v0, 2);
                fp = addu(s5, v0);
                v0 = sll(s4, 1);
                v0 = addu(s1, v0);
                sq(v0, sp, 0xD0);
                for (;;) {
                    // 0x0031b1a4
                    charge(ctx, 5);
                    lq(v0, sp, 0xD0);
                    lhu(v0, v0, 32);
                    v0 = sltu(s2, v0);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0031afd4
                    charge(ctx, 7);
                    lw(v1, s7, 40);
                    v0 = sll(s2, 1);
                    v0 = addu(v1, v0);
                    lh(a0, v0, 0);
                    v0 = si(-1);
                    if (a0 != v0) {
                        // 0x0031aff0
                        charge(ctx, 10);
                        lw(v1, fp, 0x118);
                        lw(t0, v1, 0);
                        v0 = a0 & 0xFFFF;
                        a1 = sll(v0, 2);
                        a1 = addu(a1, v0);
                        a1 = sll(a1, 4);
                        a1 = addu(t0, a1);
                        lw(a3, a1, 64);
                        if (a3 != 0) {
                            // 0x0031b018
                            charge(ctx, 6);
                            a2 = s2 & 0xFFFF;
                            a1 = sll(a2, 2);
                            a1 = addu(a1, a2);
                            a1 = sll(a1, 4);
                            a1 = addu(t0, a1);
                            sw(a3, a1, 64);
                        }
                        // 0x0031b030
                        charge(ctx, 11);
                        s0 = s2 & 0xFFFF;
                        a1 = sll(s0, 2);
                        a1 = addu(a1, s0);
                        a1 = sll(a1, 4);
                        lw(v1, v1, 0);
                        a1 = addu(v1, a1);
                        lw(v1, a1, 68);
                        v1 = v1 | 0x1;
                        sw(v1, a1, 68);
                        if (s4 == 0) {
                            // 0x0031b05c
                            charge(ctx, 3);
                            lw(t0, s5, 860);
                            if (t0 != 0) {
                                // 0x0031b068
                                charge(ctx, 6);
                                a1 = dsll32(a0, 16);
                                a1 = dsra32(a1, 16);
                                lhu(v1, t0, 4);
                                at = slt(a1, v1);
                                if (at != 0) {
                                    // 0x0031b080
                                    charge(ctx, 6);
                                    v1 = sll(a1, 3);
                                    lw(a3, t0, 0);
                                    v1 = addu(a3, v1);
                                    lw(v1, v1, 0);
                                    if (v1 != 0) {
                                        // 0x0031b098
                                        charge(ctx, 11);
                                        a2 = sll(s0, 3);
                                        v1 = sll(v0, 3);
                                        v1 = addu(a3, v1);
                                        lw(a1, v1, 0);
                                        v1 = addu(a3, a2);
                                        sw(a1, v1, 0);
                                        lw(v1, t0, 0);
                                        a1 = addu(v1, a2);
                                        lbu(v1, a1, 4);
                                        v1 = v1 | 0x1;
                                        sb(v1, a1, 4);
                                    }
                                }
                            }
                            // 0x0031b0c4
                            charge(ctx, 3);
                            lw(a3, s5, 892);
                            if (a3 != 0) {
                                // 0x0031b0d0
                                charge(ctx, 6);
                                a0 = dsll32(a0, 16);
                                a0 = dsra32(a0, 16);
                                lhu(v1, a3, 12);
                                at = slt(a0, v1);
                                if (at != 0) {
                                    // 0x0031b0e8
                                    charge(ctx, 6);
                                    v1 = sll(a0, 3);
                                    lw(a2, a3, 0);
                                    v1 = addu(a2, v1);
                                    lw(v1, v1, 0);
                                    if (v1 != 0) {
                                        // 0x0031b100
                                        charge(ctx, 12);
                                        v1 = s2 & 0xFFFF;
                                        a1 = sll(v1, 3);
                                        v1 = sll(v0, 3);
                                        v1 = addu(a2, v1);
                                        lw(a0, v1, 0);
                                        v1 = addu(a2, a1);
                                        sw(a0, v1, 0);
                                        lw(v1, a3, 0);
                                        a0 = addu(v1, a1);
                                        lbu(v1, a0, 4);
                                        v1 = v1 | 0x1;
                                        sb(v1, a0, 4);
                                    }
                                }
                            }
                            // 0x0031b130
                            charge(ctx, 3);
                            lw(s6, fp, 0x11C);
                            if (s6 != 0) {
                                // 0x0031b13c
                                charge(ctx, 7);
                                lw(v1, s6, 20);
                                v0 = sll(v0, 2);
                                sq(v0, sp, 0xC0);
                                v0 = addu(v1, v0);
                                lw(a0, v0, 0);
                                if (a0 != 0) {
                                    // 0x0031b158
                                    charge(ctx, 6);
                                    jal(ctx, 0x31B158u, gen::fn_sub_31D700_0031d700);
                                    a0 = sll(s0, 2);
                                    lw(v1, s6, 20);
                                    v1 = addu(v1, a0);
                                    sw(v0, v1, 0);
                                }
                                // 0x0031b170
                                charge(ctx, 6);
                                lw(v1, s6, 32);
                                lq(v0, sp, 0xC0);
                                v0 = addu(v1, v0);
                                lw(a0, v0, 0);
                                if (a0 != 0) {
                                    // 0x0031b188
                                    charge(ctx, 6);
                                    jal(ctx, 0x31B188u, gen::fn_sub_31E0B0_0031e0b0);
                                    a0 = sll(s0, 2);
                                    lw(v1, s6, 32);
                                    v1 = addu(v1, a0);
                                    sw(v0, v1, 0);
                                }
                            }
                        }
                    }
                    // 0x0031b1a0
                    charge(ctx, 1);
                    s2 = addiu(s2, 1);
                }
                // 0x0031b1b8
                charge(ctx, 6);
                lq(v0, sp, 0xE0);
                lw(a0, v0, 0);
                v0 = 0x960000;
                lw(v0, v0, 380);  // 0x96017C
                jalr(ctx, 0x31B1C8u, v0.u());
            }
            // 0x0031b1d0
            charge(ctx, 1);
            s4 = addiu(s4, 1);
        }
    }
    // 0x0031b1e0 (the shared epilogue, written out on this path)
    charge(ctx, 14);
    v0 = s3;
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
    sp = addiu(sp, 0x110);
}

// 0x0031B820 sub_31B820 -- 1624 bytes; frame 0x150: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Builds the weapon model path "%sweapon/wp%03X_R[_h].RMD" / "_L" for a unit's held weapon (datGetUnit,
// datGetEquipmentIdx, datCalcGetHeldWeaponType; sprintf) and loads it. [proposed name mdlLoadWeaponModel]
void sub_31B820(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0031b820
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x150);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s0 = a1;
    s2 = 0;
    a0 = dsll32(s0, 16);
    a0 = dsra32(a0, 16);
    a1 = 0;
    jal(ctx, 0x31B850u, gen::fn_datGetEquipmentIdx_0016cb80);
    a1 = dsll32(v0, 16);
    a1 = dsra32(a1, 16);
    a0 = dsll32(s0, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x31B868u, gen::fn_sub_16F630_0016f630);
    s1 = v0 & 0xFFFF;
    at = sltiu(s0, 11);
    if (at != 0) {
        // 0x0031b880
        charge(ctx, 7);
        a0 = 0x7C0000;
        a0 = addiu(a0, -28304);  // &0x7B9170
        v1 = sll(s0, 2);
        v1 = addu(v1, a0);
        lw(v1, v1, 0);
        switch (v1.u()) {
        case 0x31B89Cu:  // table[1]
            // 0x0031b89c
            charge(ctx, 10);
            a0 = 1;
            jal(ctx, 0x31B8A0u, gen::fn_datGetUnit_0016cd60);
            a0 = v0;
            jal(ctx, 0x31B8ACu, gen::fn_datCalcGetHeldWeaponType_00308c60);
            s0 = v0 & 0xFF;
            a1 = 3;
            if (s0 != a1) {
                // 0x0031b8c4
                charge(ctx, 3);
                v0 = 7;
                if (s0 == v0) {
                    goto L_0031b8f0;
                }
                // 0x0031b8d0
                charge(ctx, 8);
                a0 = s3;
                a2 = 10;
                a3 = s1;
                t0 = 0;
                jal(ctx, 0x31B8E0u, gen::fn_sub_319490_00319490);
                goto L_0031ba58;
            }
        L_0031b8f0:
            charge(ctx, 7);
            a0 = 7;
            a1 = s1;
            a2 = 0;
            jal(ctx, 0x31B8FCu, gen::fn_sub_316910_00316910);
            if (v0 != 0) {
                // 0x0031b980
                charge(ctx, 7);
                a0 = s3;
                a1 = 3;
                a2 = 7;
                a3 = s1;
                t0 = 0;
                jal(ctx, 0x31B994u, gen::fn_sub_319490_00319490);
            } else {
                // 0x0031b90c
                charge(ctx, 3);
                v0 = 7;
                if (s0 == v0) {
                    // 0x0031b93c
                    charge(ctx, 7);
                    a3 = s1 & 0xFFFF;
                    a0 = addiu(sp, 0x50);
                    a1 = 0x6A0000;
                    a1 = addiu(a1, -20208);  // "%sweapon/wp%03X_R.RMD"
                    a2 = addiu(gp, -25312);  // "model/"
                    jal(ctx, 0x31B950u, gen::fn_sprintf_00523ac8);
                } else {
                    // 0x0031b918
                    charge(ctx, 9);
                    a3 = s1 & 0xFFFF;
                    a0 = addiu(sp, 0x50);
                    a1 = 0x6A0000;
                    a1 = addiu(a1, -20240);  // "%sweapon/wp%03X_R_h.RMD"
                    a2 = addiu(gp, -25312);  // "model/"
                    jal(ctx, 0x31B92Cu, gen::fn_sprintf_00523ac8);
                }
                // 0x0031b958
                charge(ctx, 10);
                a0 = s3;
                a1 = 3;
                a2 = 7;
                a3 = s1;
                t0 = addiu(sp, 0x50);
                t1 = 0;
                jal(ctx, 0x31B970u, gen::fn_sub_3192A0_003192a0);
            }
            // 0x0031b99c
            charge(ctx, 9);
            s2 = s1 & 0xFFFF;
            s1 = addiu(s2, 1000);
            a1 = s1 & 0xFFFF;
            a0 = 7;
            a2 = 0;
            jal(ctx, 0x31B9B0u, gen::fn_sub_316910_00316910);
            if (v0 != 0) {
                // 0x0031ba38
                charge(ctx, 8);
                a3 = s1 & 0xFFFF;
                a0 = s3;
                a1 = 4;
                a2 = 7;
                t0 = 0;
                jal(ctx, 0x31BA4Cu, gen::fn_sub_319490_00319490);
                s2 = 1;
            } else {
                // 0x0031b9c0
                charge(ctx, 3);
                v0 = 7;
                if (s0 == v0) {
                    // 0x0031b9f0
                    charge(ctx, 7);
                    a0 = addiu(sp, 0x50);
                    a1 = 0x6A0000;
                    a1 = addiu(a1, -20144);  // "%sweapon/wp%03X_L.RMD"
                    a2 = addiu(gp, -25312);  // "model/"
                    a3 = s2;
                    jal(ctx, 0x31BA04u, gen::fn_sprintf_00523ac8);
                } else {
                    // 0x0031b9cc
                    charge(ctx, 9);
                    a0 = addiu(sp, 0x50);
                    a1 = 0x6A0000;
                    a1 = addiu(a1, -20176);  // "%sweapon/wp%03X_L_h.RMD"
                    a2 = addiu(gp, -25312);  // "model/"
                    a3 = s2;
                    jal(ctx, 0x31B9E0u, gen::fn_sprintf_00523ac8);
                }
                // 0x0031ba0c
                charge(ctx, 11);
                a3 = s1 & 0xFFFF;
                a0 = s3;
                a1 = 4;
                a2 = 7;
                t0 = addiu(sp, 0x50);
                t1 = 0;
                jal(ctx, 0x31BA24u, gen::fn_sub_3192A0_003192a0);
                s2 = 1;
            }
        L_0031ba58:
            charge(ctx, 3);
            a0 = 1;
        L_0031be18:
            charge(ctx, 3);
            v1 = 1;
            if (a0 == v1) {
                // 0x0031be24
                charge(ctx, 5);
                a0 = s3;
                a1 = 3;
                a2 = 500;
                jal(ctx, 0x31BE30u, gen::fn_sub_3196D0_003196d0);
            }
            // 0x0031be38
            charge(ctx, 3);
            v1 = 1;
            if (s2 == v1) {
                // 0x0031be44
                charge(ctx, 5);
                a0 = s3;
                a1 = 4;
                a2 = 501;
                jal(ctx, 0x31BE50u, gen::fn_sub_3196D0_003196d0);
            }
            break;
        case 0x31BA64u:  // table[2]
            // 0x0031ba64
            charge(ctx, 10);
            a0 = s3;
            a1 = 3;
            a2 = 7;
            a3 = s1;
            t0 = 0;
            jal(ctx, 0x31BA78u, gen::fn_sub_319490_00319490);
            a0 = 1;
            goto L_0031be18;
        case 0x31BA8Cu:  // table[3]
            // 0x0031ba8c
            charge(ctx, 7);
            a0 = 7;
            a1 = s1;
            a2 = 0;
            jal(ctx, 0x31BA98u, gen::fn_sub_316910_00316910);
            if (v0 != 0) {
                // 0x0031baec
                charge(ctx, 7);
                a0 = s3;
                a1 = 3;
                a2 = 7;
                a3 = s1;
                t0 = 0;
                jal(ctx, 0x31BB00u, gen::fn_sub_319490_00319490);
            } else {
                // 0x0031baa8
                charge(ctx, 17);
                a3 = s1 & 0xFFFF;
                a0 = addiu(sp, 0x50);
                a1 = 0x6A0000;
                a1 = addiu(a1, -20208);  // "%sweapon/wp%03X_R.RMD"
                a2 = addiu(gp, -25312);  // "model/"
                jal(ctx, 0x31BABCu, gen::fn_sprintf_00523ac8);
                a0 = s3;
                a1 = 3;
                a2 = 7;
                a3 = s1;
                t0 = addiu(sp, 0x50);
                t1 = 0;
                jal(ctx, 0x31BADCu, gen::fn_sub_3192A0_003192a0);
            }
            // 0x0031bb08
            charge(ctx, 9);
            v0 = s1 & 0xFFFF;
            s0 = addiu(v0, 1000);
            a1 = s0 & 0xFFFF;
            a0 = 7;
            a2 = 0;
            jal(ctx, 0x31BB1Cu, gen::fn_sub_316910_00316910);
            if (v0 != 0) {
                // 0x0031bb74
                charge(ctx, 8);
                a3 = s0 & 0xFFFF;
                a0 = s3;
                a1 = 4;
                a2 = 7;
                t0 = 0;
                jal(ctx, 0x31BB88u, gen::fn_sub_319490_00319490);
                s2 = 1;
            } else {
                // 0x0031bb2c
                charge(ctx, 18);
                a3 = s1 & 0xFFFF;
                a0 = addiu(sp, 0x50);
                a1 = 0x6A0000;
                a1 = addiu(a1, -20144);  // "%sweapon/wp%03X_L.RMD"
                a2 = addiu(gp, -25312);  // "model/"
                jal(ctx, 0x31BB40u, gen::fn_sprintf_00523ac8);
                a3 = s0 & 0xFFFF;
                a0 = s3;
                a1 = 4;
                a2 = 7;
                t0 = addiu(sp, 0x50);
                t1 = 0;
                jal(ctx, 0x31BB60u, gen::fn_sub_3192A0_003192a0);
                s2 = 1;
            }
            // 0x0031bb94
            charge(ctx, 3);
            a0 = 1;
            goto L_0031be18;
        case 0x31BBA0u:  // table[4]
            // 0x0031bba0
            charge(ctx, 10);
            a0 = s3;
            a1 = 3;
            a2 = 7;
            a3 = s1;
            t0 = 0;
            jal(ctx, 0x31BBB4u, gen::fn_sub_319490_00319490);
            a0 = 1;
            goto L_0031be18;
        case 0x31BBC8u:  // table[5]
            // 0x0031bbc8
            charge(ctx, 10);
            a0 = s3;
            a1 = 3;
            a2 = 7;
            a3 = s1;
            t0 = 0;
            jal(ctx, 0x31BBDCu, gen::fn_sub_319490_00319490);
            a0 = 1;
            goto L_0031be18;
        case 0x31BBF0u:  // table[7]
            // 0x0031bbf0
            charge(ctx, 7);
            a0 = 7;
            a1 = s1;
            a2 = 0;
            jal(ctx, 0x31BBFCu, gen::fn_sub_316910_00316910);
            if (v0 != 0) {
                // 0x0031bc50
                charge(ctx, 7);
                a0 = s3;
                a1 = 3;
                a2 = 7;
                a3 = s1;
                t0 = 0;
                jal(ctx, 0x31BC64u, gen::fn_sub_319490_00319490);
            } else {
                // 0x0031bc0c
                charge(ctx, 17);
                a3 = s1 & 0xFFFF;
                a0 = addiu(sp, 0x50);
                a1 = 0x6A0000;
                a1 = addiu(a1, -20208);  // "%sweapon/wp%03X_R.RMD"
                a2 = addiu(gp, -25312);  // "model/"
                jal(ctx, 0x31BC20u, gen::fn_sprintf_00523ac8);
                a0 = s3;
                a1 = 3;
                a2 = 7;
                a3 = s1;
                t0 = addiu(sp, 0x50);
                t1 = 0;
                jal(ctx, 0x31BC40u, gen::fn_sub_3192A0_003192a0);
            }
            // 0x0031bc6c
            charge(ctx, 9);
            v0 = s1 & 0xFFFF;
            s0 = addiu(v0, 1000);
            a1 = s0 & 0xFFFF;
            a0 = 7;
            a2 = 0;
            jal(ctx, 0x31BC80u, gen::fn_sub_316910_00316910);
            if (v0 != 0) {
                // 0x0031bcd8
                charge(ctx, 8);
                a3 = s0 & 0xFFFF;
                a0 = s3;
                a1 = 4;
                a2 = 7;
                t0 = 0;
                jal(ctx, 0x31BCECu, gen::fn_sub_319490_00319490);
                s2 = 1;
            } else {
                // 0x0031bc90
                charge(ctx, 18);
                a3 = s1 & 0xFFFF;
                a0 = addiu(sp, 0x50);
                a1 = 0x6A0000;
                a1 = addiu(a1, -20144);  // "%sweapon/wp%03X_L.RMD"
                a2 = addiu(gp, -25312);  // "model/"
                jal(ctx, 0x31BCA4u, gen::fn_sprintf_00523ac8);
                a3 = s0 & 0xFFFF;
                a0 = s3;
                a1 = 4;
                a2 = 7;
                t0 = addiu(sp, 0x50);
                t1 = 0;
                jal(ctx, 0x31BCC4u, gen::fn_sub_3192A0_003192a0);
                s2 = 1;
            }
            // 0x0031bcf8
            charge(ctx, 3);
            a0 = 1;
            goto L_0031be18;
        case 0x31BD04u:  // table[8]
            // 0x0031bd04
            charge(ctx, 10);
            a0 = s3;
            a1 = 3;
            a2 = 7;
            a3 = s1;
            t0 = 0;
            jal(ctx, 0x31BD18u, gen::fn_sub_319490_00319490);
            a0 = 1;
            goto L_0031be18;
        case 0x31BD2Cu:  // table[9]
            // 0x0031bd2c
            charge(ctx, 4);
            jal(ctx, 0x31BD2Cu, gen::fn_sub_17D800_0017d800);
            if (v0 == 0) {
                // 0x0031bdc0
                charge(ctx, 7);
                a0 = s3;
                a1 = 3;
                a2 = 7;
                a3 = s1;
                t0 = 0;
                jal(ctx, 0x31BDD4u, gen::fn_sub_319490_00319490);
            } else {
                // 0x0031bd3c
                charge(ctx, 7);
                a0 = 7;
                a1 = s1;
                a2 = 0;
                jal(ctx, 0x31BD48u, gen::fn_sub_316910_00316910);
                if (v0 != 0) {
                    // 0x0031bd9c
                    charge(ctx, 9);
                    a0 = s3;
                    a1 = 3;
                    a2 = 7;
                    a3 = s1;
                    t0 = 0;
                    jal(ctx, 0x31BDB0u, gen::fn_sub_319490_00319490);
                } else {
                    // 0x0031bd58
                    charge(ctx, 17);
                    a3 = s1 & 0xFFFF;
                    a0 = addiu(sp, 0x50);
                    a1 = 0x6A0000;
                    a1 = addiu(a1, -20112);  // "%sweapon/wp%03X_f.RMD"
                    a2 = addiu(gp, -25312);  // "model/"
                    jal(ctx, 0x31BD6Cu, gen::fn_sprintf_00523ac8);
                    a0 = s3;
                    a1 = 3;
                    a2 = 7;
                    a3 = s1;
                    t0 = addiu(sp, 0x50);
                    t1 = 0;
                    jal(ctx, 0x31BD8Cu, gen::fn_sub_3192A0_003192a0);
                }
            }
            // 0x0031bddc
            charge(ctx, 3);
            a0 = 1;
            goto L_0031be18;
        case 0x31BDE8u:  // table[10]
            // 0x0031bde8
            charge(ctx, 10);
            a0 = s3;
            a1 = 3;
            a2 = 7;
            a3 = s1;
            t0 = 0;
            jal(ctx, 0x31BDFCu, gen::fn_sub_319490_00319490);
            a0 = 1;
            goto L_0031be18;
        case 0x31BE10u:  // table[0, 6]
        L_0031be10:
            charge(ctx, 2);
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
        // 0x0031be58 (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(ra, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x150);
        return;
    }
    goto L_0031be10;
}

// 0x0031C820 sub_31C820 -- 3280 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Builds the player model path "%splayer/bc003_c?a.RMD" for a character / costume (two jump tables, datGetFlag,
// sprintf) and loads it. [proposed name mdlLoadPlayerModel]
void sub_31C820(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0031c820
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    s2 = a2;
    v0 = a0 & 0xFFFF;
    at = sltiu(v0, 12);
    if (at != 0) {
        // 0x0031c84c
        charge(ctx, 7);
        v1 = 0x7C0000;
        v1 = addiu(v1, -28160);  // &0x7B9200
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x31C868u:  // table[1]
            // 0x0031c868
            charge(ctx, 17);
            s0 = dsll32(s1, 16);
            s0 = dsra32(s0, 16);
            a0 = s0;
            a1 = 1;
            jal(ctx, 0x31C878u, gen::fn_datGetEquipmentIdx_0016cb80);
            a1 = dsll32(v0, 16);
            a1 = dsra32(a1, 16);
            a0 = s0;
            jal(ctx, 0x31C88Cu, gen::fn_sub_16F630_0016f630);
            s0 = dsll32(v0, 16);
            s0 = dsra32(s0, 16);
            a3 = s1 & 0xFFFF;
            v0 = 1;
            if (a3 != v0) {
                // 0x0031cb68
                charge(ctx, 3);
                at = sltiu(a3, 11);
                if (at != 0) {
                    // 0x0031cb74
                    charge(ctx, 7);
                    v1 = 0x7C0000;
                    v1 = addiu(v1, -28208);  // &0x7B91D0
                    v0 = sll(a3, 2);
                    v0 = addu(v0, v1);
                    lw(v0, v0, 0);
                    switch (v0.u()) {
                    case 0x31CB90u:  // table[2]
                        // 0x0031cb90
                        charge(ctx, 5);
                        v1 = dsll32(s0, 16);
                        v1 = dsra32(v1, 16);
                        v0 = 1054;
                        if (v1 == v0) {
                            // 0x0031cc88
                            charge(ctx, 8);
                            a0 = s2;
                            a1 = 0x6A0000;
                            a1 = addiu(a1, -19376);  // "%splayer/bc002_c5.RMD"
                            a2 = addiu(gp, -25312);  // "model/"
                            jal(ctx, 0x31CC98u, gen::fn_sprintf_00523ac8);
                        } else {
                            // 0x0031cba4
                            charge(ctx, 3);
                            v0 = 1122;
                            if (v1 == v0) {
                                // 0x0031cc68
                                charge(ctx, 8);
                                a0 = s2;
                                a1 = 0x6A0000;
                                a1 = addiu(a1, -19408);  // "%splayer/bc002_c4.RMD"
                                a2 = addiu(gp, -25312);  // "model/"
                                jal(ctx, 0x31CC78u, gen::fn_sprintf_00523ac8);
                            } else {
                                // 0x0031cbb0
                                charge(ctx, 3);
                                v0 = 1117;
                                if (v1 == v0) {
                                    // 0x0031cc48
                                    charge(ctx, 8);
                                    a0 = s2;
                                    a1 = 0x6A0000;
                                    a1 = addiu(a1, -19440);  // "%splayer/bc002_c3.RMD"
                                    a2 = addiu(gp, -25312);  // "model/"
                                    jal(ctx, 0x31CC58u, gen::fn_sprintf_00523ac8);
                                } else {
                                    // 0x0031cbbc
                                    charge(ctx, 3);
                                    v0 = 1113;
                                    if (v1 == v0) {
                                        // 0x0031cc28
                                        charge(ctx, 8);
                                        a0 = s2;
                                        a1 = 0x6A0000;
                                        a1 = addiu(a1, -19472);  // "%splayer/bc002_c2.RMD"
                                        a2 = addiu(gp, -25312);  // "model/"
                                        jal(ctx, 0x31CC38u, gen::fn_sprintf_00523ac8);
                                    } else {
                                        // 0x0031cbc8
                                        charge(ctx, 3);
                                        v0 = 1112;
                                        if (v1 == v0) {
                                            // 0x0031cc08
                                            charge(ctx, 8);
                                            a0 = s2;
                                            a1 = 0x6A0000;
                                            a1 = addiu(a1, -19504);  // "%splayer/bc002_c1.RMD"
                                            a2 = addiu(gp, -25312);  // "model/"
                                            jal(ctx, 0x31CC18u, gen::fn_sprintf_00523ac8);
                                        } else {
                                            // 0x0031cbd4
                                            charge(ctx, 3);
                                            v0 = 1082;
                                            if (v1 == v0) {
                                                // 0x0031cbe8
                                                charge(ctx, 8);
                                                a0 = s2;
                                                a1 = 0x6A0000;
                                                a1 = addiu(a1, -19536);  // "%splayer/bc002_c0.RMD"
                                                a2 = addiu(gp, -25312);  // "model/"
                                                jal(ctx, 0x31CBF8u, gen::fn_sprintf_00523ac8);
                                            } else {
                                                // 0x0031cbe0
                                                charge(ctx, 2);
                                                // 0x0031cca8
                                                charge(ctx, 4);
                                                jal(ctx, 0x31CCA8u, gen::fn_sub_17D800_0017d800);
                                                if (v0 == 0) {
                                                    // 0x0031ccd8
                                                    charge(ctx, 8);
                                                    a0 = s2;
                                                    a1 = 0x6A0000;
                                                    a1 = addiu(a1, -19312);  // "%splayer/bc002.RMD"
                                                    a2 = addiu(gp, -25312);  // "model/"
                                                    jal(ctx, 0x31CCE8u, gen::fn_sprintf_00523ac8);
                                                } else {
                                                    // 0x0031ccb8
                                                    charge(ctx, 8);
                                                    a0 = s2;
                                                    a1 = 0x6A0000;
                                                    a1 = addiu(a1, -19344);  // "%splayer/bc002f.RMD"
                                                    a2 = addiu(gp, -25312);  // "model/"
                                                    jal(ctx, 0x31CCC8u, gen::fn_sprintf_00523ac8);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        break;
                    case 0x31CCF8u:  // table[3]
                        // 0x0031ccf8
                        charge(ctx, 5);
                        v1 = dsll32(s0, 16);
                        v1 = dsra32(v1, 16);
                        v0 = 1124;
                        if (v1 == v0) {
                            // 0x0031cd6c
                            charge(ctx, 8);
                            a0 = s2;
                            a1 = 0x6A0000;
                            a1 = addiu(a1, -19216);  // "%splayer/bc003_c4.RMD"
                            a2 = addiu(gp, -25312);  // "model/"
                            jal(ctx, 0x31CD7Cu, gen::fn_sprintf_00523ac8);
                        } else {
                            // 0x0031cd0c
                            charge(ctx, 3);
                            v0 = 1126;
                            if (v1 == v0) {
                                // 0x0031cd4c
                                charge(ctx, 8);
                                a0 = s2;
                                a1 = 0x6A0000;
                                a1 = addiu(a1, -19248);  // "%splayer/bc003_c3.RMD"
                                a2 = addiu(gp, -25312);  // "model/"
                                jal(ctx, 0x31CD5Cu, gen::fn_sprintf_00523ac8);
                            } else {
                                // 0x0031cd18
                                charge(ctx, 3);
                                v0 = 1085;
                                if (v1 == v0) {
                                    // 0x0031cd2c
                                    charge(ctx, 8);
                                    a0 = s2;
                                    a1 = 0x6A0000;
                                    a1 = addiu(a1, -19280);  // "%splayer/bc003_c0.RMD"
                                    a2 = addiu(gp, -25312);  // "model/"
                                    jal(ctx, 0x31CD3Cu, gen::fn_sprintf_00523ac8);
                                } else {
                                    // 0x0031cd24
                                    charge(ctx, 2);
                                    // 0x0031cd8c
                                    charge(ctx, 4);
                                    jal(ctx, 0x31CD8Cu, gen::fn_sub_17D800_0017d800);
                                    if (v0 == 0) {
                                        // 0x0031cdbc
                                        charge(ctx, 8);
                                        a0 = s2;
                                        a1 = 0x6A0000;
                                        a1 = addiu(a1, -19152);  // "%splayer/bc003.RMD"
                                        a2 = addiu(gp, -25312);  // "model/"
                                        jal(ctx, 0x31CDCCu, gen::fn_sprintf_00523ac8);
                                    } else {
                                        // 0x0031cd9c
                                        charge(ctx, 8);
                                        a0 = s2;
                                        a1 = 0x6A0000;
                                        a1 = addiu(a1, -19184);  // "%splayer/bc003f.RMD"
                                        a2 = addiu(gp, -25312);  // "model/"
                                        jal(ctx, 0x31CDACu, gen::fn_sprintf_00523ac8);
                                    }
                                }
                            }
                        }
                        break;
                    case 0x31CDDCu:  // table[4]
                        // 0x0031cddc
                        charge(ctx, 5);
                        v1 = dsll32(s0, 16);
                        v1 = dsra32(v1, 16);
                        v0 = 1054;
                        if (v1 == v0) {
                            // 0x0031ced4
                            charge(ctx, 8);
                            a0 = s2;
                            a1 = 0x6A0000;
                            a1 = addiu(a1, -18960);  // "%splayer/bc004_c5.RMD"
                            a2 = addiu(gp, -25312);  // "model/"
                            jal(ctx, 0x31CEE4u, gen::fn_sprintf_00523ac8);
                        } else {
                            // 0x0031cdf0
                            charge(ctx, 3);
                            v0 = 1123;
                            if (v1 == v0) {
                                // 0x0031ceb4
                                charge(ctx, 8);
                                a0 = s2;
                                a1 = 0x6A0000;
                                a1 = addiu(a1, -18992);  // "%splayer/bc004_c4.RMD"
                                a2 = addiu(gp, -25312);  // "model/"
                                jal(ctx, 0x31CEC4u, gen::fn_sprintf_00523ac8);
                            } else {
                                // 0x0031cdfc
                                charge(ctx, 3);
                                v0 = 1118;
                                if (v1 == v0) {
                                    // 0x0031ce94
                                    charge(ctx, 8);
                                    a0 = s2;
                                    a1 = 0x6A0000;
                                    a1 = addiu(a1, -19024);  // "%splayer/bc004_c3.RMD"
                                    a2 = addiu(gp, -25312);  // "model/"
                                    jal(ctx, 0x31CEA4u, gen::fn_sprintf_00523ac8);
                                } else {
                                    // 0x0031ce08
                                    charge(ctx, 3);
                                    v0 = 1115;
                                    if (v1 == v0) {
                                        // 0x0031ce74
                                        charge(ctx, 8);
                                        a0 = s2;
                                        a1 = 0x6A0000;
                                        a1 = addiu(a1, -19056);  // "%splayer/bc004_c2.RMD"
                                        a2 = addiu(gp, -25312);  // "model/"
                                        jal(ctx, 0x31CE84u, gen::fn_sprintf_00523ac8);
                                    } else {
                                        // 0x0031ce14
                                        charge(ctx, 3);
                                        v0 = 1114;
                                        if (v1 == v0) {
                                            // 0x0031ce54
                                            charge(ctx, 8);
                                            a0 = s2;
                                            a1 = 0x6A0000;
                                            a1 = addiu(a1, -19088);  // "%splayer/bc004_c1.RMD"
                                            a2 = addiu(gp, -25312);  // "model/"
                                            jal(ctx, 0x31CE64u, gen::fn_sprintf_00523ac8);
                                        } else {
                                            // 0x0031ce20
                                            charge(ctx, 3);
                                            v0 = 1084;
                                            if (v1 == v0) {
                                                // 0x0031ce34
                                                charge(ctx, 8);
                                                a0 = s2;
                                                a1 = 0x6A0000;
                                                a1 = addiu(a1, -19120);  // "%splayer/bc004_c0.RMD"
                                                a2 = addiu(gp, -25312);  // "model/"
                                                jal(ctx, 0x31CE44u, gen::fn_sprintf_00523ac8);
                                            } else {
                                                // 0x0031ce2c
                                                charge(ctx, 2);
                                                // 0x0031cef4
                                                charge(ctx, 4);
                                                jal(ctx, 0x31CEF4u, gen::fn_sub_17D800_0017d800);
                                                if (v0 == 0) {
                                                    // 0x0031cf24
                                                    charge(ctx, 8);
                                                    a0 = s2;
                                                    a1 = 0x6A0000;
                                                    a1 = addiu(a1, -18896);  // "%splayer/bc004.RMD"
                                                    a2 = addiu(gp, -25312);  // "model/"
                                                    jal(ctx, 0x31CF34u, gen::fn_sprintf_00523ac8);
                                                } else {
                                                    // 0x0031cf04
                                                    charge(ctx, 8);
                                                    a0 = s2;
                                                    a1 = 0x6A0000;
                                                    a1 = addiu(a1, -18928);  // "%splayer/bc004f.RMD"
                                                    a2 = addiu(gp, -25312);  // "model/"
                                                    jal(ctx, 0x31CF14u, gen::fn_sprintf_00523ac8);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        break;
                    case 0x31CF44u:  // table[5]
                        // 0x0031cf44
                        charge(ctx, 5);
                        v1 = dsll32(s0, 16);
                        v1 = dsra32(v1, 16);
                        v0 = 1038;
                        if (v1 == v0) {
                            // 0x0031d010
                            charge(ctx, 8);
                            a0 = s2;
                            a1 = 0x6A0000;
                            a1 = addiu(a1, -18736);  // "%splayer/bc005_c5.RMD"
                            a2 = addiu(gp, -25312);  // "model/"
                            jal(ctx, 0x31D020u, gen::fn_sprintf_00523ac8);
                        } else {
                            // 0x0031cf58
                            charge(ctx, 3);
                            v0 = 1120;
                            if (v1 == v0) {
                                // 0x0031cff0
                                charge(ctx, 8);
                                a0 = s2;
                                a1 = 0x6A0000;
                                a1 = addiu(a1, -18768);  // "%splayer/bc005_c4.RMD"
                                a2 = addiu(gp, -25312);  // "model/"
                                jal(ctx, 0x31D000u, gen::fn_sprintf_00523ac8);
                            } else {
                                // 0x0031cf64
                                charge(ctx, 3);
                                v0 = 1109;
                                if (v1 == v0) {
                                    // 0x0031cfd0
                                    charge(ctx, 8);
                                    a0 = s2;
                                    a1 = 0x6A0000;
                                    a1 = addiu(a1, -18800);  // "%splayer/bc005_c2.RMD"
                                    a2 = addiu(gp, -25312);  // "model/"
                                    jal(ctx, 0x31CFE0u, gen::fn_sprintf_00523ac8);
                                } else {
                                    // 0x0031cf70
                                    charge(ctx, 3);
                                    v0 = 1108;
                                    if (v1 == v0) {
                                        // 0x0031cfb0
                                        charge(ctx, 8);
                                        a0 = s2;
                                        a1 = 0x6A0000;
                                        a1 = addiu(a1, -18832);  // "%splayer/bc005_c1.RMD"
                                        a2 = addiu(gp, -25312);  // "model/"
                                        jal(ctx, 0x31CFC0u, gen::fn_sprintf_00523ac8);
                                    } else {
                                        // 0x0031cf7c
                                        charge(ctx, 3);
                                        v0 = 1088;
                                        if (v1 == v0) {
                                            // 0x0031cf90
                                            charge(ctx, 8);
                                            a0 = s2;
                                            a1 = 0x6A0000;
                                            a1 = addiu(a1, -18864);  // "%splayer/bc005_c0.RMD"
                                            a2 = addiu(gp, -25312);  // "model/"
                                            jal(ctx, 0x31CFA0u, gen::fn_sprintf_00523ac8);
                                        } else {
                                            // 0x0031cf88
                                            charge(ctx, 2);
                                            // 0x0031d030
                                            charge(ctx, 4);
                                            jal(ctx, 0x31D030u, gen::fn_sub_17D800_0017d800);
                                            if (v0 == 0) {
                                                // 0x0031d060
                                                charge(ctx, 8);
                                                a0 = s2;
                                                a1 = 0x6A0000;
                                                a1 = addiu(a1, -18672);  // "%splayer/bc005.RMD"
                                                a2 = addiu(gp, -25312);  // "model/"
                                                jal(ctx, 0x31D070u, gen::fn_sprintf_00523ac8);
                                            } else {
                                                // 0x0031d040
                                                charge(ctx, 8);
                                                a0 = s2;
                                                a1 = 0x6A0000;
                                                a1 = addiu(a1, -18704);  // "%splayer/bc005f.RMD"
                                                a2 = addiu(gp, -25312);  // "model/"
                                                jal(ctx, 0x31D050u, gen::fn_sprintf_00523ac8);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        break;
                    case 0x31D080u:  // table[7]
                        // 0x0031d080
                        charge(ctx, 5);
                        v1 = dsll32(s0, 16);
                        v1 = dsra32(v1, 16);
                        v0 = 1038;
                        if (v1 == v0) {
                            // 0x0031d14c
                            charge(ctx, 8);
                            a0 = s2;
                            a1 = 0x6A0000;
                            a1 = addiu(a1, -18512);  // "%splayer/bc007_c5.RMD"
                            a2 = addiu(gp, -25312);  // "model/"
                            jal(ctx, 0x31D15Cu, gen::fn_sprintf_00523ac8);
                        } else {
                            // 0x0031d094
                            charge(ctx, 3);
                            v0 = 1121;
                            if (v1 == v0) {
                                // 0x0031d12c
                                charge(ctx, 8);
                                a0 = s2;
                                a1 = 0x6A0000;
                                a1 = addiu(a1, -18544);  // "%splayer/bc007_c4.RMD"
                                a2 = addiu(gp, -25312);  // "model/"
                                jal(ctx, 0x31D13Cu, gen::fn_sprintf_00523ac8);
                            } else {
                                // 0x0031d0a0
                                charge(ctx, 3);
                                v0 = 1111;
                                if (v1 == v0) {
                                    // 0x0031d10c
                                    charge(ctx, 8);
                                    a0 = s2;
                                    a1 = 0x6A0000;
                                    a1 = addiu(a1, -18576);  // "%splayer/bc007_c2.RMD"
                                    a2 = addiu(gp, -25312);  // "model/"
                                    jal(ctx, 0x31D11Cu, gen::fn_sprintf_00523ac8);
                                } else {
                                    // 0x0031d0ac
                                    charge(ctx, 3);
                                    v0 = 1110;
                                    if (v1 == v0) {
                                        // 0x0031d0ec
                                        charge(ctx, 8);
                                        a0 = s2;
                                        a1 = 0x6A0000;
                                        a1 = addiu(a1, -18608);  // "%splayer/bc007_c1.RMD"
                                        a2 = addiu(gp, -25312);  // "model/"
                                        jal(ctx, 0x31D0FCu, gen::fn_sprintf_00523ac8);
                                    } else {
                                        // 0x0031d0b8
                                        charge(ctx, 3);
                                        v0 = 1083;
                                        if (v1 == v0) {
                                            // 0x0031d0cc
                                            charge(ctx, 8);
                                            a0 = s2;
                                            a1 = 0x6A0000;
                                            a1 = addiu(a1, -18640);  // "%splayer/bc007_c0.RMD"
                                            a2 = addiu(gp, -25312);  // "model/"
                                            jal(ctx, 0x31D0DCu, gen::fn_sprintf_00523ac8);
                                        } else {
                                            // 0x0031d0c4
                                            charge(ctx, 2);
                                            // 0x0031d16c
                                            charge(ctx, 4);
                                            jal(ctx, 0x31D16Cu, gen::fn_sub_17D800_0017d800);
                                            if (v0 == 0) {
                                                // 0x0031d19c
                                                charge(ctx, 8);
                                                a0 = s2;
                                                a1 = 0x6A0000;
                                                a1 = addiu(a1, -18448);  // "%splayer/bc007.RMD"
                                                a2 = addiu(gp, -25312);  // "model/"
                                                jal(ctx, 0x31D1ACu, gen::fn_sprintf_00523ac8);
                                            } else {
                                                // 0x0031d17c
                                                charge(ctx, 8);
                                                a0 = s2;
                                                a1 = 0x6A0000;
                                                a1 = addiu(a1, -18480);  // "%splayer/bc007f.RMD"
                                                a2 = addiu(gp, -25312);  // "model/"
                                                jal(ctx, 0x31D18Cu, gen::fn_sprintf_00523ac8);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        break;
                    case 0x31D1BCu:  // table[8]
                        // 0x0031d1bc
                        charge(ctx, 5);
                        v1 = dsll32(s0, 16);
                        v1 = dsra32(v1, 16);
                        v0 = 1038;
                        if (v1 == v0) {
                            // 0x0031d25c
                            charge(ctx, 8);
                            a0 = s2;
                            a1 = 0x6A0000;
                            a1 = addiu(a1, -18320);  // "%splayer/bc008_c5.RMD"
                            a2 = addiu(gp, -25312);  // "model/"
                            jal(ctx, 0x31D26Cu, gen::fn_sprintf_00523ac8);
                        } else {
                            // 0x0031d1d0
                            charge(ctx, 3);
                            v0 = 1125;
                            if (v1 == v0) {
                                // 0x0031d23c
                                charge(ctx, 8);
                                a0 = s2;
                                a1 = 0x6A0000;
                                a1 = addiu(a1, -18352);  // "%splayer/bc008_c4.RMD"
                                a2 = addiu(gp, -25312);  // "model/"
                                jal(ctx, 0x31D24Cu, gen::fn_sprintf_00523ac8);
                            } else {
                                // 0x0031d1dc
                                charge(ctx, 3);
                                v0 = 1116;
                                if (v1 == v0) {
                                    // 0x0031d21c
                                    charge(ctx, 8);
                                    a0 = s2;
                                    a1 = 0x6A0000;
                                    a1 = addiu(a1, -18384);  // "%splayer/bc008_c2.RMD"
                                    a2 = addiu(gp, -25312);  // "model/"
                                    jal(ctx, 0x31D22Cu, gen::fn_sprintf_00523ac8);
                                } else {
                                    // 0x0031d1e8
                                    charge(ctx, 3);
                                    v0 = 1086;
                                    if (v1 == v0) {
                                        // 0x0031d1fc
                                        charge(ctx, 8);
                                        a0 = s2;
                                        a1 = 0x6A0000;
                                        a1 = addiu(a1, -18416);  // "%splayer/bc008_c1.RMD"
                                        a2 = addiu(gp, -25312);  // "model/"
                                        jal(ctx, 0x31D20Cu, gen::fn_sprintf_00523ac8);
                                    } else {
                                        // 0x0031d1f4
                                        charge(ctx, 2);
                                        // 0x0031d27c
                                        charge(ctx, 4);
                                        jal(ctx, 0x31D27Cu, gen::fn_sub_17D800_0017d800);
                                        if (v0 == 0) {
                                            // 0x0031d2ac
                                            charge(ctx, 8);
                                            a0 = s2;
                                            a1 = 0x6A0000;
                                            a1 = addiu(a1, -18256);  // "%splayer/bc008.RMD"
                                            a2 = addiu(gp, -25312);  // "model/"
                                            jal(ctx, 0x31D2BCu, gen::fn_sprintf_00523ac8);
                                        } else {
                                            // 0x0031d28c
                                            charge(ctx, 8);
                                            a0 = s2;
                                            a1 = 0x6A0000;
                                            a1 = addiu(a1, -18288);  // "%splayer/bc008f.RMD"
                                            a2 = addiu(gp, -25312);  // "model/"
                                            jal(ctx, 0x31D29Cu, gen::fn_sprintf_00523ac8);
                                        }
                                    }
                                }
                            }
                        }
                        break;
                    case 0x31D2CCu:  // table[9]
                        // 0x0031d2cc
                        charge(ctx, 4);
                        jal(ctx, 0x31D2CCu, gen::fn_sub_17D800_0017d800);
                        if (v0 == 0) {
                            // 0x0031d2fc
                            charge(ctx, 5);
                            v1 = dsll32(s0, 16);
                            v1 = dsra32(v1, 16);
                            v0 = 1038;
                            if (v1 == v0) {
                                // 0x0031d318
                                charge(ctx, 8);
                                a0 = s2;
                                a1 = 0x6A0000;
                                a1 = addiu(a1, -18192);  // "%splayer/bc009_c5.RMD"
                                a2 = addiu(gp, -25312);  // "model/"
                                jal(ctx, 0x31D328u, gen::fn_sprintf_00523ac8);
                            } else {
                                // 0x0031d310
                                charge(ctx, 2);
                                // 0x0031d338
                                charge(ctx, 8);
                                a0 = s2;
                                a1 = 0x6A0000;
                                a1 = addiu(a1, -18160);  // "%splayer/bc009.RMD"
                                a2 = addiu(gp, -25312);  // "model/"
                                jal(ctx, 0x31D348u, gen::fn_sprintf_00523ac8);
                            }
                        } else {
                            // 0x0031d2dc
                            charge(ctx, 8);
                            a0 = s2;
                            a1 = 0x6A0000;
                            a1 = addiu(a1, -18224);  // "%splayer/bc009f.RMD"
                            a2 = addiu(gp, -25312);  // "model/"
                            jal(ctx, 0x31D2ECu, gen::fn_sprintf_00523ac8);
                        }
                        break;
                    case 0x31D358u:  // table[0, 1, 6, 10]
                    L_0031d358:
                        charge(ctx, 8);
                        a0 = s2;
                        a1 = 0x6A0000;
                        a1 = addiu(a1, -18128);  // "%splayer/bc%03X.RMD"
                        a2 = addiu(gp, -25312);  // "model/"
                        jal(ctx, 0x31D368u, gen::fn_sprintf_00523ac8);
                        break;
                    default:  // not one of the table's targets: the dispatch table, as the recompiled body
                        tail(ctx, v0.u());
                        return;
                    }
                    break;
                }
                goto L_0031d358;
            }
            // 0x0031c8ac
            charge(ctx, 4);
            jal(ctx, 0x31C8ACu, gen::fn_sub_17D800_0017d800);
            if (v0 == 0) {
                // 0x0031c9a8
                charge(ctx, 9);
                a0 = 1;
                jal(ctx, 0x31C9ACu, gen::fn_datGetUnit_0016cd60);
                a0 = v0;
                jal(ctx, 0x31C9B8u, gen::fn_datCalcGetHeldWeaponType_00308c60);
                s1 = v0 & 0xFF;
                if (s1 == 0) {
                    // 0x0031c9cc
                    charge(ctx, 5);
                    a0 = 21;
                    jal(ctx, 0x31C9D0u, gen::fn_datGetFlag_0016f190);
                    if (v0 != 0) {
                        goto L_0031ca2c;
                    }
                    // 0x0031c9e0
                    charge(ctx, 5);
                    a0 = 4880;
                    jal(ctx, 0x31C9E4u, gen::fn_datGetFlag_0016f190);
                    if (v0 != 0) {
                        goto L_0031ca2c;
                    }
                    // 0x0031c9f4
                    charge(ctx, 6);
                    a0 = 1;
                    a1 = a0;
                    jal(ctx, 0x31C9FCu, gen::fn_sub_31E420_0031e420);
                    if (v0 != 0) {
                        goto L_0031ca2c;
                    }
                    // 0x0031ca0c
                    charge(ctx, 8);
                    a0 = s2;
                    a1 = 0x6A0000;
                    a1 = addiu(a1, -19760);  // "%splayer/bc001_wp0_c9.RMD"
                    a2 = addiu(gp, -25312);  // "model/"
                    jal(ctx, 0x31CA1Cu, gen::fn_sprintf_00523ac8);
                    break;
                }
            L_0031ca2c:
                charge(ctx, 5);
                v1 = dsll32(s0, 16);
                v1 = dsra32(v1, 16);
                v0 = 1038;
                if (v1 == v0) {
                    // 0x0031cb18
                    charge(ctx, 10);
                    a0 = s2;
                    a1 = 0x6A0000;
                    a1 = addiu(a1, -19600);  // "%splayer/bc%03X_wp%X_c5.RMD"
                    a2 = addiu(gp, -25312);  // "model/"
                    a3 = 1;
                    t0 = s1;
                    jal(ctx, 0x31CB30u, gen::fn_sprintf_00523ac8);
                } else {
                    // 0x0031ca40
                    charge(ctx, 3);
                    v0 = 1119;
                    if (v1 == v0) {
                        // 0x0031caf0
                        charge(ctx, 10);
                        a0 = s2;
                        a1 = 0x6A0000;
                        a1 = addiu(a1, -19632);  // "%splayer/bc%03X_wp%X_c4.RMD"
                        a2 = addiu(gp, -25312);  // "model/"
                        a3 = 1;
                        t0 = s1;
                        jal(ctx, 0x31CB08u, gen::fn_sprintf_00523ac8);
                    } else {
                        // 0x0031ca4c
                        charge(ctx, 3);
                        v0 = 1107;
                        if (v1 == v0) {
                            // 0x0031cac8
                            charge(ctx, 10);
                            a0 = s2;
                            a1 = 0x6A0000;
                            a1 = addiu(a1, -19664);  // "%splayer/bc%03X_wp%X_c2.RMD"
                            a2 = addiu(gp, -25312);  // "model/"
                            a3 = 1;
                            t0 = s1;
                            jal(ctx, 0x31CAE0u, gen::fn_sprintf_00523ac8);
                        } else {
                            // 0x0031ca58
                            charge(ctx, 3);
                            v0 = 1106;
                            if (v1 == v0) {
                                // 0x0031caa0
                                charge(ctx, 10);
                                a0 = s2;
                                a1 = 0x6A0000;
                                a1 = addiu(a1, -19696);  // "%splayer/bc%03X_wp%X_c1.RMD"
                                a2 = addiu(gp, -25312);  // "model/"
                                a3 = 1;
                                t0 = s1;
                                jal(ctx, 0x31CAB8u, gen::fn_sprintf_00523ac8);
                            } else {
                                // 0x0031ca64
                                charge(ctx, 3);
                                v0 = 1081;
                                if (v1 == v0) {
                                    // 0x0031ca78
                                    charge(ctx, 10);
                                    a0 = s2;
                                    a1 = 0x6A0000;
                                    a1 = addiu(a1, -19728);  // "%splayer/bc%03X_wp%X_c0.RMD"
                                    a2 = addiu(gp, -25312);  // "model/"
                                    a3 = 1;
                                    t0 = s1;
                                    jal(ctx, 0x31CA90u, gen::fn_sprintf_00523ac8);
                                } else {
                                    // 0x0031ca70
                                    charge(ctx, 2);
                                    // 0x0031cb40
                                    charge(ctx, 10);
                                    a0 = s2;
                                    a1 = 0x6A0000;
                                    a1 = addiu(a1, -19568);  // "%splayer/bc%03X_wp%X.RMD"
                                    a2 = addiu(gp, -25312);  // "model/"
                                    a3 = 1;
                                    t0 = s1;
                                    jal(ctx, 0x31CB58u, gen::fn_sprintf_00523ac8);
                                }
                            }
                        }
                    }
                }
            } else {
                // 0x0031c8bc
                charge(ctx, 5);
                v1 = dsll32(s0, 16);
                v1 = dsra32(v1, 16);
                v0 = 1124;
                if (v1 == v0) {
                    // 0x0031c930
                    charge(ctx, 8);
                    a0 = s2;
                    a1 = 0x6A0000;
                    a1 = addiu(a1, -19856);  // "%splayer/bc003_c4a.RMD"
                    a2 = addiu(gp, -25312);  // "model/"
                    jal(ctx, 0x31C940u, gen::fn_sprintf_00523ac8);
                } else {
                    // 0x0031c8d0
                    charge(ctx, 3);
                    v0 = 1126;
                    if (v1 == v0) {
                        // 0x0031c910
                        charge(ctx, 8);
                        a0 = s2;
                        a1 = 0x6A0000;
                        a1 = addiu(a1, -19888);  // "%splayer/bc003_c3a.RMD"
                        a2 = addiu(gp, -25312);  // "model/"
                        jal(ctx, 0x31C920u, gen::fn_sprintf_00523ac8);
                    } else {
                        // 0x0031c8dc
                        charge(ctx, 3);
                        v0 = 1085;
                        if (v1 == v0) {
                            // 0x0031c8f0
                            charge(ctx, 8);
                            a0 = s2;
                            a1 = 0x6A0000;
                            a1 = addiu(a1, -19920);  // "%splayer/bc003_c0a.RMD"
                            a2 = addiu(gp, -25312);  // "model/"
                            jal(ctx, 0x31C900u, gen::fn_sprintf_00523ac8);
                        } else {
                            // 0x0031c8e8
                            charge(ctx, 2);
                            // 0x0031c950
                            charge(ctx, 6);
                            a0 = 752;
                            jal(ctx, 0x31C954u, gen::fn_datGetFlag_0016f190);
                            v1 = 1;
                            if (v0 != v1) {
                                // 0x0031c988
                                charge(ctx, 8);
                                a0 = s2;
                                a1 = 0x6A0000;
                                a1 = addiu(a1, -19792);  // "%splayer/bc001f_c9.RMD"
                                a2 = addiu(gp, -25312);  // "model/"
                                jal(ctx, 0x31C998u, gen::fn_sprintf_00523ac8);
                            } else {
                                // 0x0031c968
                                charge(ctx, 8);
                                a0 = s2;
                                a1 = 0x6A0000;
                                a1 = addiu(a1, -19824);  // "%splayer/bc001f.RMD"
                                a2 = addiu(gp, -25312);  // "model/"
                                jal(ctx, 0x31C978u, gen::fn_sprintf_00523ac8);
                            }
                        }
                    }
                }
            }
            break;
        case 0x31D378u:  // table[2]
            // 0x0031d378
            charge(ctx, 9);
            a3 = s1 & 0xFFFF;
            a0 = s2;
            a1 = 0x6A0000;
            a1 = addiu(a1, -18096);  // "%senemy/em%03X.RMD"
            a2 = addiu(gp, -25312);  // "model/"
            jal(ctx, 0x31D38Cu, gen::fn_sprintf_00523ac8);
            break;
        case 0x31D39Cu:  // table[3]
            // 0x0031d39c
            charge(ctx, 9);
            a3 = s1 & 0xFFFF;
            a0 = s2;
            a1 = 0x6A0000;
            a1 = addiu(a1, -18064);  // "%spersona/ps%03X.RMD"
            a2 = addiu(gp, -25312);  // "model/"
            jal(ctx, 0x31D3B0u, gen::fn_sprintf_00523ac8);
            break;
        case 0x31D3C0u:  // table[10]
            // 0x0031d3c0
            charge(ctx, 9);
            a3 = s1 & 0xFFFF;
            a0 = s2;
            a1 = 0x6A0000;
            a1 = addiu(a1, -18032);  // "%sweapon/wp%03X_h.RMD"
            a2 = addiu(gp, -25312);  // "model/"
            jal(ctx, 0x31D3D4u, gen::fn_sprintf_00523ac8);
            break;
        case 0x31D3E4u:  // table[7]
            // 0x0031d3e4
            charge(ctx, 9);
            a3 = s1 & 0xFFFF;
            a0 = s2;
            a1 = 0x6A0000;
            a1 = addiu(a1, -18000);  // "%sweapon/wp%03X.RMD"
            a2 = addiu(gp, -25312);  // "model/"
            jal(ctx, 0x31D3F8u, gen::fn_sprintf_00523ac8);
            break;
        case 0x31D408u:  // table[8]
            // 0x0031d408
            charge(ctx, 9);
            a3 = s1 & 0xFFFF;
            a0 = s2;
            a1 = 0x6A0000;
            a1 = addiu(a1, -17968);  // "%ssymbol/es%03X.RMD"
            a2 = addiu(gp, -25312);  // "model/"
            jal(ctx, 0x31D41Cu, gen::fn_sprintf_00523ac8);
            break;
        case 0x31D42Cu:  // table[9]
            // 0x0031d42c
            charge(ctx, 12);
            v0 = s1 & 0xFFFF;
            v0 = sra(v0, 8);
            a3 = v0 & 0xFF;
            t0 = s1 & 0xFF;
            a0 = s2;
            a1 = 0x6A0000;
            a1 = addiu(a1, -19952);  // "%sfield/fc_%02d_%02d.RMD"
            a2 = addiu(gp, -25312);  // "model/"
            jal(ctx, 0x31D44Cu, gen::fn_sprintf_00523ac8);
            break;
        case 0x31D45Cu:  // table[5]
            // 0x0031d45c
            charge(ctx, 5);
            a0 = s2;
            jal(ctx, 0x31D460u, gen::fn_sub_31C000_0031c000);
            break;
        case 0x31D470u:  // table[11]
            // 0x0031d470
            charge(ctx, 9);
            a3 = s1 & 0xFFFF;
            a0 = s2;
            a1 = 0x6A0000;
            a1 = addiu(a1, -17936);  // "%sfacilityp/fp%03X.RMD"
            a2 = addiu(gp, -25312);  // "model/"
            jal(ctx, 0x31D484u, gen::fn_sprintf_00523ac8);
            break;
        case 0x31D494u:  // table[0, 4, 6]
        L_0031d494:
            charge(ctx, 15);
            v0 = a0 & 0xFFFF;
            v1 = sll(v0, 3);
            v0 = 0x6A0000;
            v0 = addiu(v0, -20864);  // &0x69AE80
            a0 = addu(v0, v1);
            v0 = s1 & 0xFFFF;
            v1 = sll(v0, 2);
            lw(v0, a0, 0);
            v0 = addu(v0, v1);
            a0 = s2;
            a1 = addiu(gp, -25304);  // "%s%s"
            a2 = addiu(gp, -25312);  // "model/"
            lw(a3, v0, 0);
            jal(ctx, 0x31D4C8u, gen::fn_sprintf_00523ac8);
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x0031d4d0 (the shared epilogue, written out on this path)
        charge(ctx, 8);
        v0 = 1;
        ld(ra, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
        return;
    }
    goto L_0031d494;
}

// 0x0031EF80 sub_31EF80 -- 1596 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Picks a unit model's motion set from its held weapon type, flags and datCalcRand (tables 0x68F0F0, 0x68FAB0,
// 0x691020, 0x69BA18) and starts it.
void sub_31EF80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0031ef80
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
    s1 = a2;
    lhu(v1, a0, 6);
    v1 = v1 & 0x10;
    if (v1 != 0) {
        // 0x0031efb8
        charge(ctx, 3);
        lw(a1, s3, 0);
        if (a1 != 0) {
            // 0x0031efc4
            charge(ctx, 4);
            lhu(v1, a1, 14);
            v1 = v1 & 0x1;
            if (v1 != 0) {
                // 0x0031efd4
                charge(ctx, 4);
                lhu(v1, a1, 12);
                a0 = 2;
                if (v1 == a0) {
                    // 0x0031f2b4
                    charge(ctx, 3);
                    lhu(v1, a1, 8);
                    if (v1 == a0) {
                        // 0x0031f2c0
                        charge(ctx, 8);
                        lhu(a0, a1, 10);
                        jal(ctx, 0x31F2C4u, gen::fn_sub_2F6C50_002f6c50);
                        a2 = dsll32(v0, 16);
                        a2 = dsra32(a2, 16);
                        a0 = si(-1);
                        if (a2 == a0) {
                            goto L_0031f4e4;
                        }
                        // 0x0031f2e0
                        charge(ctx, 19);
                        v1 = dsll32(s2, 16);
                        v1 = dsra32(v1, 16);
                        a1 = sll(a2, 3);
                        a1 = subu(a1, a2);
                        a1 = sll(a1, 3);
                        a1 = addu(a1, a2);
                        a2 = sll(a1, 2);
                        a1 = 0x690000;
                        a1 = addiu(a1, 4128);  // &0x691020
                        a2 = addu(a1, a2);
                        a1 = sll(v1, 1);
                        a1 = addu(a1, v1);
                        a1 = sll(a1, 2);
                        s4 = addu(a1, a2);
                        lhu(a1, s3, 6);
                        a1 = a1 & 0x20;
                        a1 = sltu(0, a1);
                        if (a1 != 0) {
                            // 0x0031f32c
                            charge(ctx, 4);
                            s0 = 0;
                            a3 = 0;
                            for (;;) {
                                // 0x0031f35c
                                charge(ctx, 4);
                                a2 = a3 & 0xFFFF;
                                a1 = slti(a2, 3);
                                if (a1 == 0) {
                                    break;
                                }
                                backedge(ctx);
                                // 0x0031f33c
                                charge(ctx, 4);
                                a1 = addu(s4, a2);
                                lb(a1, a1, 0);
                                if (a1 != a0) {
                                    // 0x0031f34c
                                    charge(ctx, 2);
                                    a1 = addiu(s0, 1);
                                    s0 = a1 & 0xFFFF;
                                }
                                // 0x0031f354
                                charge(ctx, 2);
                                a1 = addiu(a3, 1);
                                a3 = a1 & 0xFFFF;
                            }
                            // 0x0031f36c
                            charge(ctx, 3);
                            a0 = s0 & 0xFFFF;
                            if (i64(a0) > 0) {
                                // 0x0031f378
                                charge(ctx, 3);
                                v0 = 2;
                                if (v1 == v0) {
                                    // 0x0031f384
                                    charge(ctx, 3);
                                    lh(v0, s3, 4);
                                    if (v0 != v1) {
                                        goto L_0031f3a4;
                                    }
                                    // 0x0031f390
                                    charge(ctx, 5);
                                    a0 = 4;
                                    jal(ctx, 0x31F394u, gen::fn_sub_10A500_0010a500);
                                    if (v0 == 0) {
                                        goto L_0031f3a4;
                                    }
                                    goto L_0031f3e0;
                                }
                            L_0031f3a4:
                                charge(ctx, 15);
                                v0 = 4;
                                sh(v0, s3, 8);
                                lb(v1, s4, 3);
                                v0 = s1 & 0xFFFF;
                                v0 = addu(v1, v0);
                                sh(v0, s3, 12);
                                a0 = s0 & 0xFFFF;
                                jal(ctx, 0x31F3C0u, gen::fn_datCalcRand_002ffbc0);
                                v0 = addu(s4, v0);
                                lb(v0, v0, 0);
                                sh(v0, s3, 10);
                                jal(ctx, 0x31F3D4u, gen::fn_sub_2F8810_002f8810);
                                sw(v0, s3, 16);
                            }
                        }
                    L_0031f3e0:
                        charge(ctx, 4);
                        lw(a0, s4, 4);
                        v1 = si(-1);
                        if (a0 == v1) {
                            // 0x0031f4d0
                            charge(ctx, 2);
                            v1 = si(-2);
                            sh(v1, s3, 28);
                        } else {
                            // 0x0031f3f0
                            charge(ctx, 4);
                            v1 = 0x20000000;
                            v1 = a0 & v1;
                            if (v1 == 0) {
                                // 0x0031f40c
                                charge(ctx, 4);
                                v1 = 0x40000000;
                                v1 = a0 & v1;
                                if (v1 == 0) {
                                    // 0x0031f42c
                                    charge(ctx, 3);
                                    v1 = a0 & 0x2000;
                                    if (v1 != 0) {
                                        // 0x0031f438
                                        charge(ctx, 3);
                                        lw(v1, s3, 0);
                                        lw(v1, v1, 0);
                                        sh(v1, s3, 20);
                                    }
                                } else {
                                    // 0x0031f41c
                                    charge(ctx, 4);
                                    v1 = 1;
                                    sh(v1, s3, 20);
                                }
                            } else {
                                // 0x0031f400
                                charge(ctx, 3);
                                sh(zero, s3, 20);
                            }
                            // 0x0031f444
                            charge(ctx, 5);
                            lw(v1, s3, 0);
                            lw(a0, v1, 0);
                            v1 = 5;
                            if (a0 == v1) {
                                // 0x0031f498
                                charge(ctx, 2);
                                v1 = 3;
                                sh(v1, s3, 22);
                            } else {
                                // 0x0031f458
                                charge(ctx, 3);
                                v1 = 4;
                                if (a0 == v1) {
                                    // 0x0031f488
                                    charge(ctx, 4);
                                    v1 = 2;
                                    sh(v1, s3, 22);
                                } else {
                                    // 0x0031f464
                                    charge(ctx, 3);
                                    v1 = 3;
                                    if (a0 == v1) {
                                        // 0x0031f478
                                        charge(ctx, 4);
                                        v1 = 1;
                                        sh(v1, s3, 22);
                                    } else {
                                        // 0x0031f470
                                        charge(ctx, 2);
                                    }
                                }
                            }
                            // 0x0031f4a0
                            charge(ctx, 12);
                            lb(a0, s4, 8);
                            v1 = s1 & 0xFFFF;
                            v1 = addu(a0, v1);
                            sh(v1, s3, 28);
                            lw(v1, s4, 4);
                            v1 = sra(v1, 16);
                            v1 = v1 & 0xFFF;
                            sh(v1, s3, 24);
                            lw(v1, s4, 4);
                            sh(v1, s3, 26);
                        }
                        // 0x0031f4d8
                        charge(ctx, 3);
                        sh(s2, s3, 4);
                        // 0x0031f598 (the shared epilogue, written out on this path)
                        charge(ctx, 9);
                        ld(ra, sp, 0x50);
                        lq(s4, sp, 0x40);
                        lq(s3, sp, 0x30);
                        lq(s2, sp, 0x20);
                        lq(s1, sp, 0x10);
                        lq(s0, sp, 0x0);
                        sp = addiu(sp, 0x60);
                        return;
                    }
                L_0031f4e4:
                    charge(ctx, 5);
                    s0 = dsll32(s2, 16);
                    s0 = dsra32(s0, 16);
                    v1 = 4;
                    if (s0 != v1) {
                        // 0x0031f4f8
                        charge(ctx, 3);
                        v1 = 5;
                        if (s0 == v1) {
                            goto L_0031f504;
                        }
                        // 0x0031f598 (the shared epilogue, written out on this path)
                        charge(ctx, 9);
                        ld(ra, sp, 0x50);
                        lq(s4, sp, 0x40);
                        lq(s3, sp, 0x30);
                        lq(s2, sp, 0x20);
                        lq(s1, sp, 0x10);
                        lq(s0, sp, 0x0);
                        sp = addiu(sp, 0x60);
                        return;
                    }
                L_0031f504:
                    charge(ctx, 6);
                    lw(v0, s3, 0);
                    lh(a0, v0, 0);
                    jal(ctx, 0x31F50Cu, gen::fn_sub_109DF0_00109df0);
                    if (v0 != 0) {
                        // 0x0031f51c
                        charge(ctx, 12);
                        lw(v1, s3, 0);
                        lw(v1, v1, 0);
                        sh(v1, s3, 20);
                        sh(s1, s3, 28);
                        sh(zero, s3, 24);
                        v1 = addiu(s0, -4);
                        sh(v1, s3, 26);
                        lw(v1, s3, 0);
                        lw(a0, v1, 0);
                        v1 = 5;
                        if (a0 == v1) {
                            // 0x0031f58c
                            charge(ctx, 2);
                            v1 = 3;
                            sh(v1, s3, 22);
                        } else {
                            // 0x0031f54c
                            charge(ctx, 3);
                            v1 = 4;
                            if (a0 == v1) {
                                // 0x0031f57c
                                charge(ctx, 4);
                                v1 = 2;
                                sh(v1, s3, 22);
                            } else {
                                // 0x0031f558
                                charge(ctx, 3);
                                v1 = 3;
                                if (a0 == v1) {
                                    // 0x0031f56c
                                    charge(ctx, 4);
                                    v1 = 1;
                                    sh(v1, s3, 22);
                                } else {
                                    // 0x0031f564
                                    charge(ctx, 2);
                                }
                            }
                        }
                        // 0x0031f594
                        charge(ctx, 1);
                        sh(s2, s3, 4);
                    }
                } else {
                    // 0x0031efe4
                    charge(ctx, 3);
                    a0 = 1;
                    if (v1 == a0) {
                        // 0x0031eff8
                        charge(ctx, 3);
                        lhu(v1, a1, 8);
                        if (v1 == a0) {
                            // 0x0031f004
                            charge(ctx, 3);
                            lhu(v1, a1, 10);
                            if (v1 != a0) {
                                // 0x0031f068
                                charge(ctx, 3);
                                at = slti(v1, 2);
                                if (at == 0) {
                                    // 0x0031f080
                                    charge(ctx, 8);
                                    a0 = sll(v1, 2);
                                    v1 = 0x6A0000;
                                    v1 = addiu(v1, -17896);  // &0x69BA18
                                    s0 = addu(v1, a0);
                                    lw(a0, s0, 0);
                                    v1 = si(-1);
                                    if (a0 != v1) {
                                        // 0x0031f0ac
                                        charge(ctx, 4);
                                        jal(ctx, 0x31F0ACu, gen::fn_sub_17D800_0017d800);
                                        if (v0 == 0) {
                                            // 0x0031f0c8
                                            charge(ctx, 4);
                                            lw(a0, s0, 0);
                                            jal(ctx, 0x31F0CCu, gen::fn_datGetFlag_0016f190);
                                            v1 = v0;
                                        } else {
                                            // 0x0031f0bc
                                            charge(ctx, 3);
                                            v1 = 1;
                                        }
                                    } else {
                                        // 0x0031f0a0
                                        charge(ctx, 3);
                                        v1 = 0;
                                    }
                                } else {
                                    // 0x0031f074
                                    charge(ctx, 3);
                                    v1 = 0;
                                }
                                // 0x0031f0d8
                                charge(ctx, 2);
                                if (v1 != 0) {
                                    // 0x0031f12c
                                    charge(ctx, 17);
                                    lw(v1, s3, 0);
                                    lhu(v1, v1, 10);
                                    a0 = addiu(v1, 7);
                                    v1 = sll(a0, 4);
                                    v1 = addu(v1, a0);
                                    v1 = sll(v1, 2);
                                    v1 = addu(v1, a0);
                                    a0 = sll(v1, 2);
                                    v1 = 0x690000;
                                    v1 = addiu(v1, -1360);  // &0x68FAB0
                                    a1 = addu(v1, a0);
                                    a0 = dsll32(s2, 16);
                                    a0 = dsra32(a0, 16);
                                    v1 = sll(a0, 1);
                                    v1 = addu(v1, a0);
                                    v1 = sll(v1, 2);
                                    s4 = addu(v1, a1);
                                } else {
                                    // 0x0031f0e0
                                    charge(ctx, 19);
                                    lw(v1, s3, 0);
                                    lhu(v1, v1, 10);
                                    a0 = addiu(v1, -2);
                                    v1 = sll(a0, 4);
                                    v1 = addu(v1, a0);
                                    v1 = sll(v1, 2);
                                    v1 = addu(v1, a0);
                                    a0 = sll(v1, 2);
                                    v1 = 0x690000;
                                    v1 = addiu(v1, -1360);  // &0x68FAB0
                                    a1 = addu(v1, a0);
                                    a0 = dsll32(s2, 16);
                                    a0 = dsra32(a0, 16);
                                    v1 = sll(a0, 1);
                                    v1 = addu(v1, a0);
                                    v1 = sll(v1, 2);
                                    s4 = addu(v1, a1);
                                }
                            } else {
                                // 0x0031f010
                                charge(ctx, 22);
                                jal(ctx, 0x31F010u, gen::fn_datGetUnit_0016cd60);
                                a0 = v0;
                                jal(ctx, 0x31F01Cu, gen::fn_datCalcGetHeldWeaponType_00308c60);
                                a0 = v0 & 0xFF;
                                v1 = sll(a0, 2);
                                v1 = addu(v1, a0);
                                v1 = sll(v1, 3);
                                v1 = subu(v1, a0);
                                a0 = sll(v1, 3);
                                v1 = 0x690000;
                                v1 = addiu(v1, -3856);  // &0x68F0F0
                                a1 = addu(v1, a0);
                                a0 = dsll32(s2, 16);
                                a0 = dsra32(a0, 16);
                                v1 = sll(a0, 1);
                                v1 = addu(v1, a0);
                                v1 = sll(v1, 2);
                                s4 = addu(v1, a1);
                            }
                        }
                        // 0x0031f170
                        charge(ctx, 5);
                        lhu(v1, s3, 6);
                        v1 = v1 & 0x20;
                        v1 = sltu(0, v1);
                        if (v1 != 0) {
                            // 0x0031f184
                            charge(ctx, 5);
                            s0 = 0;
                            a2 = 0;
                            a1 = si(-1);
                            for (;;) {
                                // 0x0031f1b8
                                charge(ctx, 4);
                                a0 = a2 & 0xFFFF;
                                v1 = slti(a0, 3);
                                if (v1 == 0) {
                                    break;
                                }
                                backedge(ctx);
                                // 0x0031f198
                                charge(ctx, 4);
                                v1 = addu(s4, a0);
                                lb(v1, v1, 0);
                                if (v1 != a1) {
                                    // 0x0031f1a8
                                    charge(ctx, 2);
                                    v1 = addiu(s0, 1);
                                    s0 = v1 & 0xFFFF;
                                }
                                // 0x0031f1b0
                                charge(ctx, 2);
                                v1 = addiu(a2, 1);
                                a2 = v1 & 0xFFFF;
                            }
                            // 0x0031f1c8
                            charge(ctx, 3);
                            v1 = s0 & 0xFFFF;
                            if (i64(v1) > 0) {
                                // 0x0031f1d4
                                charge(ctx, 5);
                                v1 = dsll32(s2, 16);
                                v1 = dsra32(v1, 16);
                                v0 = 2;
                                if (v1 == v0) {
                                    // 0x0031f1e8
                                    charge(ctx, 3);
                                    lh(v0, s3, 4);
                                    if (v0 != v1) {
                                        goto L_0031f208;
                                    }
                                    // 0x0031f1f4
                                    charge(ctx, 5);
                                    a0 = 3;
                                    jal(ctx, 0x31F1F8u, gen::fn_sub_10A500_0010a500);
                                    if (v0 == 0) {
                                        goto L_0031f208;
                                    }
                                    goto L_0031f244;
                                }
                            L_0031f208:
                                charge(ctx, 15);
                                v0 = 3;
                                sh(v0, s3, 8);
                                lb(v1, s4, 3);
                                v0 = s1 & 0xFFFF;
                                v0 = addu(v1, v0);
                                sh(v0, s3, 12);
                                a0 = s0 & 0xFFFF;
                                jal(ctx, 0x31F224u, gen::fn_datCalcRand_002ffbc0);
                                v1 = addu(s4, v0);
                                lb(v1, v1, 0);
                                sh(v1, s3, 10);
                                lw(v1, s3, 0);
                                lw(v1, v1, 0);
                                sw(v1, s3, 16);
                            }
                        }
                    L_0031f244:
                        charge(ctx, 4);
                        lw(a0, s4, 4);
                        v1 = si(-1);
                        if (a0 == v1) {
                            // 0x0031f2a0
                            charge(ctx, 2);
                            v1 = si(-2);
                            sh(v1, s3, 28);
                        } else {
                            // 0x0031f254
                            charge(ctx, 19);
                            v1 = 0x20000000;
                            v1 = a0 & v1;
                            v1 = sltu(0, v1);
                            v1 = v1 ^ 0x1;
                            sh(v1, s3, 20);
                            v1 = 11;
                            sh(v1, s3, 22);
                            lb(a0, s4, 8);
                            v1 = s1 & 0xFFFF;
                            v1 = addu(a0, v1);
                            sh(v1, s3, 28);
                            lw(v1, s4, 4);
                            v1 = sra(v1, 16);
                            v1 = v1 & 0xFFF;
                            sh(v1, s3, 24);
                            lw(v1, s4, 4);
                            sh(v1, s3, 26);
                        }
                        // 0x0031f2a8
                        charge(ctx, 3);
                        sh(s2, s3, 4);
                    } else {
                        // 0x0031eff0
                        charge(ctx, 2);
                    }
                }
            }
        }
    }
    // 0x0031f598 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00329890 sub_329890 -- 284 bytes; frame 0x70: ra sp+0x10, f21 sp+0x4, f20 sp+0x0
// Effect math: a rotation from cos / sin of an angle applied with VU0 (sqc2 / madd).
void sub_329890(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21};
    Vf vf10{ctx, 10}, vf28{ctx, 28}, vf29{ctx, 29}, vf30{ctx, 30};
    // 0x00329890
    enter(ctx, 71);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    mov_s(f21, f12);
    jal(ctx, 0x3298A4u, gen::fn_cosf_0052e6d8);
    mov_s(f20, f0);
    mov_s(f12, f21);
    jal(ctx, 0x3298B4u, gen::fn_sinf_0052e878);
    v1 = addiu(sp, 0x20);
    sqc2(vf10, v1, 0);
    lwc1(f11, sp, 0x20);
    mul_s(f2, f11, f11);
    v1 = 0x3F800000;
    mtc1(v1, f10);
    sub_s(f1, f10, f2);
    mtc1(zero, f9);
    adda_s(f9, f2);
    madd_s(f1, f1, f20);
    swc1(f1, sp, 0x30);
    lwc1(f8, sp, 0x24);
    mul_s(f1, f11, f8);
    sub_s(f7, f10, f20);
    lwc1(f6, sp, 0x28);
    mul_s(f5, f6, f0);
    mul_s(f2, f1, f7);
    add_s(f1, f5, f2);
    swc1(f1, sp, 0x34);
    mul_s(f1, f11, f6);
    mul_s(f4, f8, f0);
    mul_s(f3, f1, f7);
    sub_s(f1, f3, f4);
    swc1(f1, sp, 0x38);
    sw(zero, sp, 0x3C);
    sub_s(f1, f2, f5);
    swc1(f1, sp, 0x40);
    mul_s(f2, f8, f8);
    sub_s(f1, f10, f2);
    adda_s(f9, f2);
    madd_s(f1, f1, f20);
    swc1(f1, sp, 0x44);
    mul_s(f1, f8, f6);
    mul_s(f2, f11, f0);
    mul_s(f1, f1, f7);
    add_s(f0, f2, f1);
    swc1(f0, sp, 0x48);
    sw(zero, sp, 0x4C);
    add_s(f0, f4, f3);
    swc1(f0, sp, 0x50);
    sub_s(f0, f1, f2);
    swc1(f0, sp, 0x54);
    mul_s(f1, f6, f6);
    sub_s(f0, f10, f1);
    adda_s(f9, f1);
    madd_s(f0, f0, f20);
    swc1(f0, sp, 0x58);
    sw(zero, sp, 0x5C);
    v1 = addiu(sp, 0x30);
    lqc2(vf28, v1, 0);
    lqc2(vf29, v1, 16);
    lqc2(vf30, v1, 32);
    ld(ra, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x00329A60 sub_329A60 -- 316 bytes; frame 0x60: ra sp+0x10, f20 sp+0x0
// Effect math: the constant vector 0x69C4D0 transformed by the camera matrix (sub_198590, sub_4C6BE0).
void sub_329A60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f20{ctx, 20};
    Vf vf10{ctx, 10};
    // 0x00329a60
    enter(ctx, 32);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x10);
    swc1(f20, sp, 0x0);
    v0 = 0x6A0000;
    v0 = addiu(v0, -15152);  // &0x69C4D0
    sqc2(vf10, v0, 0);  // 0x69C4D0
    v0 = 0x6A0000;
    lwc1(f0, v0, -15152);  // 0x69C4D0
    swc1(f0, sp, 0x40);
    v0 = 0x6A0000;
    lwc1(f0, v0, -15148);  // 0x69C4D4
    swc1(f0, sp, 0x44);
    v0 = 0x6A0000;
    lwc1(f0, v0, -15144);  // 0x69C4D8
    swc1(f0, sp, 0x48);
    jal(ctx, 0x329A9Cu, gen::fn_sub_198590_00198590);
    a2 = addiu(v0, 32);
    a0 = addiu(sp, 0x50);
    a1 = addiu(sp, 0x40);
    jal(ctx, 0x329AB0u, gen::fn_sub_4C6BE0_004c6be0);
    jal(ctx, 0x329AB8u, gen::fn_sub_198590_00198590);
    lwc1(f20, v0, 128);
    jal(ctx, 0x329AC4u, gen::fn_sub_198590_00198590);
    lwc1(f0, v0, 132);
    lwc1(f1, sp, 0x58);
    c_le_s(f1, f20);
    if (!cond(ctx)) {
        // 0x00329ae0
        charge(ctx, 3);
        c_lt_s(f1, f0);
        if (!cond(ctx)) {
            goto L_00329aec;
        }
        // 0x00329af8
        charge(ctx, 17);
        v0 = 0x44200000;
        mtc1(v0, f4);
        lwc1(f0, sp, 0x50);
        div_s(f0, f0, f1);
        mul_s(f3, f4, f0);
        swc1(f3, sp, 0x38);
        v0 = 0x43E00000;
        mtc1(v0, f2);
        lwc1(f0, sp, 0x54);
        div_s(f0, f0, f1);
        mul_s(f1, f2, f0);
        swc1(f1, sp, 0x3C);
        mtc1(zero, f0);
        c_lt_s(f3, f0);
        if (!cond(ctx)) {
            // 0x00329b3c
            charge(ctx, 3);
            c_lt_s(f1, f0);
            if (cond(ctx)) {
                goto L_00329b84;
            }
            // 0x00329b48
            charge(ctx, 3);
            c_le_s(f3, f4);
            if (!cond(ctx)) {
                goto L_00329b84;
            }
            // 0x00329b54
            charge(ctx, 3);
            c_le_s(f1, f2);
            if (!cond(ctx)) {
                goto L_00329b84;
            }
            // 0x00329b60
            charge(ctx, 9);
            swc1(f3, sp, 0x20);
            swc1(f1, sp, 0x24);
            swc1(f0, sp, 0x28);
            swc1(f0, sp, 0x2C);
            v0 = addiu(sp, 0x20);
            lqc2(vf10, v0, 0);
            v0 = 1;
            // 0x00329b88 (the shared epilogue, written out on this path)
            charge(ctx, 5);
            ld(ra, sp, 0x10);
            lwc1(f20, sp, 0x0);
            sp = addiu(sp, 0x60);
            return;
        }
    L_00329b84:
        charge(ctx, 1);
        v0 = 0;
        // 0x00329b88 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(ra, sp, 0x10);
        lwc1(f20, sp, 0x0);
        sp = addiu(sp, 0x60);
        return;
    }
L_00329aec:
    charge(ctx, 3);
    v0 = 0;
    // 0x00329b88 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00334310 sub_334310 -- 124 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Effect object update callback (data-referenced): sub_357FD0 on the object.
void sub_334310(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00334310
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a0, 48);
    lw(s2, v1, 0);
    lw(v1, a0, 52);
    lw(s0, v1, 56);
    s1 = 0;
    for (;;) {
        // 0x00334364
        charge(ctx, 3);
        v1 = sltu(s1, s0);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00334340
        charge(ctx, 9);
        a0 = 0;
        jal(ctx, 0x334344u, gen::fn_sub_357FD0_00357fd0);
        a0 = v0 & 0x3;
        v1 = si(-1);
        v1 = subu(v1, a0);
        sw(v1, s2, 4);
        s1 = addiu(s1, 1);
        s2 = addiu(s2, 16);
    }
    // 0x00334370
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00334390 sub_334390 -- 1168 bytes; frame 0xE0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Effect object, allocate callback (data-referenced): RwMalloc through the slot 0x960178, then sub_323240 initialises
// the instance.
void sub_334390(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8};
    // 0x00334390
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0xE0);
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
    lw(s7, a0, 56);
    v0 = sll(s7, 4);
    a0 = addiu(v0, 4);
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x3343D8u, v0.u());
    s6 = v0;
    v1 = addiu(s6, 4);
    sw(v1, v0, 0);
    lw(v0, s5, 60);
    at = sltiu(v0, 3);
    if (at != 0) {
        // 0x003343fc
        charge(ctx, 2);
        v0 = 3;
        sw(v0, s5, 60);
    }
    // 0x00334404
    charge(ctx, 34);
    lw(a1, s5, 112);
    v0 = dsll32(a1, 8);
    v0 = dsrl32(v0, 8);
    sq(v0, sp, 0xD0);
    lw(a0, s5, 116);
    v0 = dsll32(a0, 8);
    v0 = dsrl32(v0, 8);
    sq(v0, sp, 0xC0);
    lw(v1, s5, 120);
    v0 = dsll32(v1, 8);
    v0 = dsrl32(v0, 8);
    sq(v0, sp, 0xB0);
    s2 = srl(a1, 24);
    s1 = srl(a0, 24);
    s0 = srl(v1, 24);
    lw(s4, s6, 0);
    lw(v0, s5, 60);
    v0 = addiu(v0, 1);
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, s5, 104);
    mul_s(f0, f0, f1);
    cvt_w_s(f0, f0);
    mfc1(fp, f0);
    lwc1(f0, s5, 108);
    mul_s(f0, f0, f1);
    cvt_w_s(f0, f0);
    mfc1(v0, f0);
    sq(v0, sp, 0xA0);
    s3 = 0;
    for (;;) {
        // 0x003347dc
        charge(ctx, 3);
        v0 = sltu(s3, s7);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0033448c
        charge(ctx, 36);
        lhu(a0, s5, 60);
        a1 = 0x6A0000;
        a1 = addiu(a1, -17120);  // &0x69BD20
        a2 = 5;
        a3 = 72;
        jal(ctx, 0x3344A0u, gen::fn_sub_323240_00323240);
        sw(v0, s4, 0);
        lh(a0, v0, 8);
        v1 = 5;
        div(a0, v1);
        mflo(t0);
        lw(v0, v0, 16);
        lw(v0, v0, 24);
        lw(t1, v0, 48);
        t2 = 0;
        lq(v0, sp, 0xA0);
        a3 = subu(t0, v0);
        a2 = a3 & 0x1;
        mtc1(a3, f6);
        v0 = 0x3F800000;
        mtc1(v0, f5);
        mtc1(fp, f0);
        cvt_s_w(f8, f0);
        a1 = s0 & 0x1;
        mtc1(s0, f4);
        v0 = 0x4F000000;
        mtc1(v0, f3);
        a0 = lui(0x8000);
        v1 = s1 & 0x1;
        mtc1(s1, f2);
        v0 = s2 & 0x1;
        mtc1(s2, f1);
        for (;;) {
            // 0x003347b4
            charge(ctx, 3);
            t3 = sltu(t2, t0);
            if (t3 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0033451c
            charge(ctx, 3);
            at = sltu(t2, fp);
            if (at == 0) {
                // 0x00334580
                charge(ctx, 4);
                lq(t3, sp, 0xA0);
                at = sltu(t3, t2);
                if (at == 0) {
                    // 0x00334618
                    charge(ctx, 1);
                    mov_s(f7, f5);
                } else {
                    // 0x00334590
                    charge(ctx, 3);
                    t3 = subu(t0, t2);
                    if (i64(t3) < 0) {
                        // 0x003345b0
                        charge(ctx, 7);
                        t4 = srl(t3, 1);
                        t3 = t3 & 0x1;
                        t4 = t4 | t3;
                        mtc1(t4, f0);
                        cvt_s_w(f7, f0);
                        add_s(f7, f7, f7);
                    } else {
                        // 0x0033459c
                        charge(ctx, 5);
                        mtc1(t3, f0);
                        cvt_s_w(f7, f0);
                    }
                    // 0x003345cc
                    charge(ctx, 2);
                    if (i64(a3) < 0) {
                        // 0x003345e0
                        charge(ctx, 6);
                        t3 = srl(a3, 1);
                        t3 = t3 | a2;
                        mtc1(t3, f0);
                        cvt_s_w(f0, f0);
                        add_s(f0, f0, f0);
                    } else {
                        // 0x003345d4
                        charge(ctx, 3);
                        cvt_s_w(f0, f6);
                    }
                    // 0x003345f8
                    charge(ctx, 8);
                    div_s(f7, f7, f0);
                }
            } else {
                // 0x00334528
                charge(ctx, 2);
                if (i64(t2) < 0) {
                    // 0x00334544
                    charge(ctx, 7);
                    t4 = srl(t2, 1);
                    t3 = t2 & 0x1;
                    t4 = t4 | t3;
                    mtc1(t4, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f0, f0);
                } else {
                    // 0x00334530
                    charge(ctx, 5);
                    mtc1(t2, f0);
                    cvt_s_w(f0, f0);
                }
                // 0x00334560
                charge(ctx, 8);
                div_s(f7, f0, f8);
            }
            // 0x0033461c
            charge(ctx, 2);
            if (i64(s0) < 0) {
                // 0x00334630
                charge(ctx, 6);
                t3 = srl(s0, 1);
                t3 = t3 | a1;
                mtc1(t3, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f0, f0);
            } else {
                // 0x00334624
                charge(ctx, 3);
                cvt_s_w(f0, f4);
            }
            // 0x00334648
            charge(ctx, 4);
            mul_s(f0, f0, f7);
            c_le_s(f3, f0);
            if (cond(ctx)) {
                // 0x00334668
                charge(ctx, 5);
                sub_s(f0, f0, f3);
                cvt_w_s(f0, f0);
                mfc1(t3, f0);
                t3 = t3 | a0;
            } else {
                // 0x00334658
                charge(ctx, 4);
                cvt_w_s(f0, f0);
                mfc1(t3, f0);
            }
            // 0x0033467c
            charge(ctx, 6);
            t4 = sll(t3, 24);
            lq(t3, sp, 0xB0);
            t3 = t3 | t4;
            sw(t3, t1, 0);
            if (i64(s1) < 0) {
                // 0x003346a0
                charge(ctx, 6);
                t3 = srl(s1, 1);
                t3 = t3 | v1;
                mtc1(t3, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f0, f0);
            } else {
                // 0x00334694
                charge(ctx, 3);
                cvt_s_w(f0, f2);
            }
            // 0x003346b8
            charge(ctx, 4);
            mul_s(f0, f0, f7);
            c_le_s(f3, f0);
            if (cond(ctx)) {
                // 0x003346d8
                charge(ctx, 5);
                sub_s(f0, f0, f3);
                cvt_w_s(f0, f0);
                mfc1(t3, f0);
                t3 = t3 | a0;
            } else {
                // 0x003346c8
                charge(ctx, 4);
                cvt_w_s(f0, f0);
                mfc1(t3, f0);
            }
            // 0x003346ec
            charge(ctx, 6);
            t4 = sll(t3, 24);
            lq(t3, sp, 0xC0);
            t3 = t3 | t4;
            sw(t3, t1, 4);
            if (i64(s2) < 0) {
                // 0x00334710
                charge(ctx, 6);
                t3 = srl(s2, 1);
                t3 = t3 | v0;
                mtc1(t3, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f0, f0);
            } else {
                // 0x00334704
                charge(ctx, 3);
                cvt_s_w(f0, f1);
            }
            // 0x00334728
            charge(ctx, 4);
            mul_s(f0, f0, f7);
            c_le_s(f3, f0);
            if (cond(ctx)) {
                // 0x00334748
                charge(ctx, 5);
                sub_s(f0, f0, f3);
                cvt_w_s(f0, f0);
                mfc1(t3, f0);
                t3 = t3 | a0;
            } else {
                // 0x00334738
                charge(ctx, 4);
                cvt_w_s(f0, f0);
                mfc1(t3, f0);
            }
            // 0x0033475c
            charge(ctx, 22);
            t4 = sll(t3, 24);
            lq(t3, sp, 0xD0);
            t3 = t3 | t4;
            sw(t3, t1, 8);
            lbu(t6, t1, 4);
            lbu(t5, t1, 5);
            lbu(t4, t1, 6);
            lbu(t3, t1, 7);
            sb(t6, t1, 12);
            sb(t5, t1, 13);
            sb(t4, t1, 14);
            sb(t3, t1, 15);
            lbu(t6, t1, 0);
            lbu(t5, t1, 1);
            lbu(t4, t1, 2);
            lbu(t3, t1, 3);
            sb(t6, t1, 16);
            sb(t5, t1, 17);
            sb(t4, t1, 18);
            sb(t3, t1, 19);
            t2 = addiu(t2, 1);
            t1 = addiu(t1, 20);
        }
        // 0x003347c0
        charge(ctx, 7);
        v1 = si(-1);
        v0 = sll(s3, 2);
        v0 = subu(v1, v0);
        sw(v0, s4, 4);
        sw(zero, s4, 12);
        s3 = addiu(s3, 1);
        s4 = addiu(s4, 16);
    }
    // 0x003347e8
    charge(ctx, 14);
    v0 = s6;
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
    sp = addiu(sp, 0xE0);
}

// 0x00334820 sub_334820 -- 136 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Effect object, release callback (data-referenced): sub_3237C0, then RwFree through the slot 0x96017C.
void sub_334820(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00334820
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s3, a0, 48);
    lw(s2, s3, 0);
    lw(v0, a0, 52);
    lw(s0, v0, 56);
    s1 = 0;
    for (;;) {
        // 0x00334868
        charge(ctx, 3);
        v0 = sltu(s1, s0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00334854
        charge(ctx, 5);
        lw(a0, s2, 0);
        jal(ctx, 0x334858u, gen::fn_sub_3237C0_003237c0);
        s1 = addiu(s1, 1);
        s2 = addiu(s2, 16);
    }
    // 0x00334874
    charge(ctx, 13);
    a0 = s3;
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x334880u, v0.u());
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x003348B0 sub_3348B0 -- 2244 bytes; frame 0x180: ra sp+0xC0, fp sp+0xB0 (sq), s7 sp+0xA0 (sq), s6 sp+0x90 (sq), s5 sp+0x80 (sq), s4 sp+0x70 (sq), s3 sp+0x60 (sq), s2 sp+0x50 (sq), s1 sp+0x40 (sq), s0 sp+0x30 (sq), f31 sp+0x2C, f30 sp+0x28, f29 sp+0x24, f28 sp+0x20, f27 sp+0x1C, f26 sp+0x18, f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// Effect object, particle update callback (data-referenced): geometry lock (geometryLock), per-vertex motion with sinf
// / asinf / cosf, unlock (sub_4933D0).
void sub_3348B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25}, f26{ctx, 26}, f27{ctx, 27}, f28{ctx, 28}, f29{ctx, 29}, f30{ctx, 30}, f31{ctx, 31};
    Vf vf0{ctx, 0}, vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11}, vf12{ctx, 12}, vf28{ctx, 28}, vf29{ctx, 29}, vf30{ctx, 30};
    // 0x003348b0
    enter(ctx, 32);  // entry check point + this block's cycles
    sp = addiu(sp, -0x180);
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
    s0 = a0;
    lw(v1, a0, 48);
    lw(s3, a0, 52);
    lw(s1, v1, 0);
    lw(a1, s3, 52);
    lw(v1, a0, 40);
    at = sltu(a1, v1);
    if (at != 0) {
        // 0x00334930
        charge(ctx, 2);
        if (a1 == 0) {
            goto L_00334938;
        }
        // 0x00335110 (the shared epilogue, written out on this path)
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
        sp = addiu(sp, 0x180);
        return;
    }
L_00334938:
    charge(ctx, 9);
    lw(fp, s3, 56);
    lw(s6, s3, 64);
    lwc1(f0, s3, 84);
    swc1(f0, sp, 0x100);
    lwc1(f0, s3, 88);
    swc1(f0, sp, 0xFC);
    lw(v1, s3, 60);
    if (i64(v1) < 0) {
        // 0x00334970
        charge(ctx, 7);
        a0 = srl(v1, 1);
        v1 = v1 & 0x1;
        a0 = a0 | v1;
        mtc1(a0, f0);
        cvt_s_w(f30, f0);
        add_s(f30, f30, f30);
    } else {
        // 0x0033495c
        charge(ctx, 5);
        mtc1(v1, f0);
        cvt_s_w(f30, f0);
    }
    // 0x0033498c
    charge(ctx, 8);
    lwc1(f0, s3, 132);
    div_s(f31, f0, f30);
    lwc1(f0, gp, -32408);  // 0x7CAE58
    swc1(f0, sp, 0xF0);
    lw(v1, s3, 76);
    if (i64(v1) < 0) {
        // 0x003349c0
        charge(ctx, 7);
        a0 = srl(v1, 1);
        v1 = v1 & 0x1;
        a0 = a0 | v1;
        mtc1(a0, f0);
        cvt_s_w(f1, f0);
        add_s(f1, f1, f1);
    } else {
        // 0x003349ac
        charge(ctx, 5);
        mtc1(v1, f0);
        cvt_s_w(f1, f0);
    }
    // 0x003349dc
    charge(ctx, 10);
    lwc1(f0, gp, -32408);  // 0x7CAE58
    mul_s(f0, f0, f1);
    div_s(f0, f0, f30);
    swc1(f0, sp, 0x10C);
    lwc1(f27, s3, 80);
    mtc1(zero, f0);
    c_le_s(f31, f0);
    if (!cond(ctx)) {
        // 0x00334a04
        charge(ctx, 51);
        a0 = addiu(sp, 0x120);
        jal(ctx, 0x334A08u, gen::fn_sub_329740_00329740);
        lqc2(vf10, s0, 16);
        jal(ctx, 0x334A14u, gen::fn_sub_357E30_00357e30);
        v1 = 0x6A0000;
        v1 = addiu(v1, -15168);  // &0x69C4C0
        lqc2(vf10, v1, 0);  // 0x69C4C0
        vmula_bc(0xF, vf28, vf10, 0);  // vmulax.xyzw
        vmadda_bc(0xF, vf29, vf10, 1);  // vmadday.xyzw
        vmadd_bc(0xF, vf10, vf30, vf10, 2);  // vmaddz.xyzw
        v1 = addiu(sp, 0x130);
        sqc2(vf10, v1, 0);
        lwc1(f24, gp, -32340);  // 0x7CAE9C
        mtc1(zero, f20);
        sw(zero, sp, 0x140);
        lwc1(f2, s3, 128);
        swc1(f2, sp, 0x144);
        lwc1(f1, s3, 124);
        add_s(f0, f2, f1);
        swc1(f0, sp, 0x148);
        add_s(f0, f0, f1);
        swc1(f0, sp, 0x14C);
        add_s(f0, f0, f2);
        swc1(f0, sp, 0x150);
        s0 = 0;
        v1 = 0x3F800000;
        mtc1(v1, f0);
        swc1(f0, sp, 0xF4);
        v1 = lui(0xBF80);
        mtc1(v1, f21);
        lwc1(f0, gp, -32644);  // 0x7CAD6C
        swc1(f0, sp, 0xEC);
        lwc1(f0, gp, -32336);  // 0x7CAEA0
        swc1(f0, sp, 0xE8);
        v1 = 0x3F400000;
        mtc1(v1, f0);
        swc1(f0, sp, 0xE4);
        v1 = 0x3E800000;
        mtc1(v1, f0);
        swc1(f0, sp, 0xE0);
        v1 = 0x3F000000;
        mtc1(v1, f0);
        swc1(f0, sp, 0xDC);
        for (;;) {
            // 0x00335104
            charge(ctx, 3);
            v1 = slt(s0, fp);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00334ad0
            charge(ctx, 4);
            lw(a0, s1, 4);
            v1 = si(-1);
            if (a0 == v1) {
                // 0x00334ae0
                charge(ctx, 3);
                sw(v1, s1, 8);
                goto L_003350f0;
            }
            // 0x00334aec
            charge(ctx, 22);
            a0 = 0;
            jal(ctx, 0x334AF0u, gen::fn_sub_358030_00358030);
            lwc1(f2, sp, 0xF4);
            lwc1(f1, sp, 0xFC);
            sub_s(f2, f2, f1);
            mtc1(zero, f1);
            adda_s(f1, f2);
            lwc1(f1, sp, 0xFC);
            madd_s(f1, f1, f0);
            lwc1(f0, sp, 0x100);
            mul_s(f0, f0, f1);
            div_s(f22, f0, f30);
            lwc1(f0, s1, 12);
            swc1(f0, sp, 0x104);
            a0 = 0;
            jal(ctx, 0x334B30u, gen::fn_sub_357FD0_00357fd0);
            v1 = v0 & 0x1;
            if (v1 != 0) {
                // 0x00334b44
                charge(ctx, 1);
                mul_s(f22, f22, f21);
            }
            // 0x00334b48
            charge(ctx, 9);
            mov_s(f23, f22);
            lw(a0, s1, 8);
            v1 = lui(0xFF00);
            v1 = a0 & v1;
            at = 0x40000000;
            at = at | 0x1;
            at = sltu(v1, at);
            if (at != 0) {
                // 0x00334b80
                charge(ctx, 4);
                v1 = si(-1);
                sw(v1, s1, 4);
                if (i64(s6) > 0) {
                    // 0x00334b90
                    charge(ctx, 10);
                    a0 = 0;
                    jal(ctx, 0x334B94u, gen::fn_sub_357FD0_00357fd0);
                    divu(v0, s6);
                    mfhi(a0);
                    lw(v1, s1, 4);
                    v1 = subu(v1, a0);
                    sw(v1, s1, 4);
                }
            } else {
                // 0x00334b6c
                charge(ctx, 5);
                v0 = lui(0xC000);
                v0 = addu(a0, v0);
                sw(v0, s1, 8);
                // 0x00334bb8
                charge(ctx, 20);
                lw(s2, s1, 0);
                lh(v1, s2, 8);
                v0 = 5;
                div(v1, v0);
                mflo(s7);
                lw(v0, s2, 16);
                lw(a0, v0, 24);
                a1 = 2;
                jal(ctx, 0x334BD8u, gen::fn_geometryLock_00493370);
                lw(v0, s2, 16);
                lw(v0, v0, 24);
                lw(v0, v0, 92);
                lw(s4, v0, 20);
                a0 = 0;
                jal(ctx, 0x334BF4u, gen::fn_sub_357FD0_00357fd0);
                v0 = v0 & 0x1;
                if (v0 != 0) {
                    // 0x00334c08
                    charge(ctx, 1);
                    mul_s(f27, f27, f21);
                }
                // 0x00334c0c
                charge(ctx, 131);
                a0 = 0;
                jal(ctx, 0x334C10u, gen::fn_sub_358030_00358030);
                lwc1(f1, sp, 0xF0);
                mul_s(f29, f1, f0);
                a0 = 0;
                jal(ctx, 0x334C24u, gen::fn_sub_358030_00358030);
                mtc1(zero, f2);
                lwc1(f1, sp, 0xE8);
                adda_s(f2, f1);
                lwc1(f1, sp, 0xEC);
                madd_s(f0, f1, f0);
                mul_s(f28, f27, f0);
                mov_s(f12, f29);
                jal(ctx, 0x334C48u, gen::fn_sinf_0052e878);
                mul_s(f25, f28, f0);
                lwc1(f0, sp, 0x10C);
                add_s(f29, f29, f0);
                mov_s(f12, f29);
                jal(ctx, 0x334C60u, gen::fn_sinf_0052e878);
                mul_s(f26, f28, f0);
                sub_s(f1, f26, f25);
                mula_s(f31, f31);
                madd_s(f0, f1, f1);
                sqrt_s(f0, f0);
                div_s(f12, f1, f0);
                jal(ctx, 0x334C94u, gen::fn_asinf_0052ea00);
                lwc1(f3, s3, 124);
                lwc1(f1, s3, 128);
                add_s(f2, f3, f1);
                lwc1(f1, sp, 0x104);
                add_s(f25, f0, f1);
                v1 = addiu(sp, 0x130);
                lqc2(vf10, v1, 0);
                v0 = addiu(sp, 0x120);
                lqc2(vf11, v0, 0);
                vopmula(0xE, vf10, vf11);  // vopmula.xyz
                vopmsub(0xE, vf10, vf11, vf10);  // vopmsub.xyz
                vmul(0xE, vf2, vf10, vf10);  // vmul.xyz
                vmula_bc(0x1, vf0, vf2, 0);  // vmulax.w
                vmadda_bc(0x1, vf0, vf2, 1);  // vmadday.w
                vmadd_bc(0x1, vf2, vf0, vf2, 2);  // vmaddz.w
                vrsqrt(vf0, 3, vf2, 3);  // vrsqrt
                vwaitq(ctx);
                vmulq(0xE, vf10, vf10);  // vmulq.xyz
                vmove(0xF, vf12, vf10);  // vmove.xyzw
                lqc2(vf11, v1, 0);
                vopmula(0xE, vf10, vf11);  // vopmula.xyz
                vopmsub(0xE, vf10, vf11, vf10);  // vopmsub.xyz
                v0 = addiu(sp, 0x110);
                sqc2(vf10, v0, 0);
                vmove(0xF, vf10, vf12);  // vmove.xyzw
                vmove(0xF, vf11, vf12);  // vmove.xyzw
                mfc1(v0, f2);
                qmtc2(v0, vf2, false);  // qmtc2
                vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                v0 = 0x6A0000;
                v0 = addiu(v0, -15152);  // &0x69C4D0
                sqc2(vf10, v0, 0);  // 0x69C4D0
                v1 = 0x6A0000;
                lwc1(f0, v1, -15152);  // 0x69C4D0
                swc1(f0, s4, 0);
                v1 = 0x6A0000;
                lwc1(f0, v1, -15148);  // 0x69C4D4
                swc1(f0, s4, 4);
                v1 = 0x6A0000;
                lwc1(f0, v1, -15144);  // 0x69C4D8
                swc1(f0, s4, 8);
                vsub(0xE, vf10, vf0, vf10);  // vsub.xyz
                sqc2(vf10, v0, 0);  // 0x69C4D0
                v1 = 0x6A0000;
                lwc1(f0, v1, -15152);  // 0x69C4D0
                swc1(f0, s4, 48);
                v1 = 0x6A0000;
                lwc1(f0, v1, -15148);  // 0x69C4D4
                swc1(f0, s4, 52);
                v1 = 0x6A0000;
                lwc1(f0, v1, -15144);  // 0x69C4D8
                swc1(f0, s4, 56);
                mfc1(v1, f3);
                qmtc2(v1, vf2, false);  // qmtc2
                vmul_bc(0xF, vf11, vf11, vf2, 0);  // vmulx.xyzw
                sqc2(vf11, v0, 0);  // 0x69C4D0
                v1 = 0x6A0000;
                lwc1(f0, v1, -15152);  // 0x69C4D0
                swc1(f0, s4, 12);
                v1 = 0x6A0000;
                lwc1(f0, v1, -15148);  // 0x69C4D4
                swc1(f0, s4, 16);
                v1 = 0x6A0000;
                lwc1(f0, v1, -15144);  // 0x69C4D8
                swc1(f0, s4, 20);
                vsub(0xE, vf11, vf0, vf11);  // vsub.xyz
                sqc2(vf11, v0, 0);  // 0x69C4D0
                v1 = 0x6A0000;
                lwc1(f0, v1, -15152);  // 0x69C4D0
                swc1(f0, s4, 36);
                v1 = 0x6A0000;
                lwc1(f0, v1, -15148);  // 0x69C4D4
                swc1(f0, s4, 40);
                v1 = 0x6A0000;
                lwc1(f0, v1, -15144);  // 0x69C4D8
                swc1(f0, s4, 44);
                swc1(f20, s4, 24);
                swc1(f20, s4, 28);
                swc1(f20, s4, 32);
                vmove(0xF, vf11, vf12);  // vmove.xyzw
                mfc1(v1, f26);
                qmtc2(v1, vf2, false);  // qmtc2
                vmul_bc(0xF, vf11, vf11, vf2, 0);  // vmulx.xyzw
                t2 = 0;
                t0 = 0x6A0000;
                a3 = 0x6A0000;
                a2 = 0x6A0000;
                a1 = 0x6A0000;
                a0 = 0x6A0000;
                v1 = 0x6A0000;
                for (;;) {
                    // 0x00334e74
                    charge(ctx, 3);
                    t1 = slti(t2, 5);
                    if (t1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00334e18
                    charge(ctx, 23);
                    t1 = sll(t2, 1);
                    t1 = addu(t1, t2);
                    t1 = sll(t1, 2);
                    t1 = addu(s4, t1);
                    lwc1(f0, t1, 0);
                    swc1(f0, t0, -15152);
                    lwc1(f0, t1, 4);
                    swc1(f0, a3, -15148);
                    lwc1(f0, t1, 8);
                    swc1(f0, a2, -15144);
                    lqc2(vf10, v0, 0);
                    vadd(0xF, vf10, vf10, vf11);  // vadd.xyzw
                    sqc2(vf10, v0, 0);
                    lwc1(f0, a1, -15152);
                    swc1(f0, t1, 0);
                    lwc1(f0, a0, -15148);
                    swc1(f0, t1, 4);
                    lwc1(f0, v1, -15144);
                    swc1(f0, t1, 8);
                    t1 = sll(t2, 2);
                    t1 = addu(t1, sp);
                    swc1(f20, t1, 352);
                    t2 = addiu(t2, 1);
                }
                // 0x00334e80
                charge(ctx, 4);
                s4 = addiu(s4, 60);
                s5 = 1;
                for (;;) {
                    // 0x003350b4
                    charge(ctx, 3);
                    v0 = slt(s5, s7);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00334e90
                    charge(ctx, 16);
                    a0 = 0;
                    jal(ctx, 0x334E94u, gen::fn_sub_358030_00358030);
                    mtc1(zero, f2);
                    lwc1(f1, sp, 0xE0);
                    adda_s(f2, f1);
                    lwc1(f1, sp, 0xE4);
                    madd_s(f0, f1, f0);
                    mul_s(f0, f24, f0);
                    swc1(f0, sp, 0x108);
                    a0 = 0;
                    jal(ctx, 0x334EBCu, gen::fn_sub_357FD0_00357fd0);
                    v0 = v0 & 0x1;
                    if (v0 != 0) {
                        // 0x00334ed0
                        charge(ctx, 1);
                        mul_s(f24, f24, f21);
                    }
                    // 0x00334ed4
                    charge(ctx, 6);
                    lwc1(f0, sp, 0x10C);
                    add_s(f29, f29, f0);
                    lwc1(f0, sp, 0xF0);
                    c_lt_s(f29, f0);
                    if (!cond(ctx)) {
                        // 0x00334eec
                        charge(ctx, 11);
                        sub_s(f29, f29, f0);
                        mul_s(f27, f27, f21);
                        a0 = 0;
                        jal(ctx, 0x334EF8u, gen::fn_sub_358030_00358030);
                        mtc1(zero, f2);
                        lwc1(f1, sp, 0xE8);
                        adda_s(f2, f1);
                        lwc1(f1, sp, 0xEC);
                        madd_s(f0, f1, f0);
                        mul_s(f28, f27, f0);
                    }
                    // 0x00334f18
                    charge(ctx, 61);
                    mov_s(f12, f29);
                    jal(ctx, 0x334F1Cu, gen::fn_sinf_0052e878);
                    mul_s(f0, f28, f0);
                    swc1(f0, sp, 0xD8);
                    sub_s(f1, f0, f26);
                    mula_s(f31, f31);
                    madd_s(f0, f1, f1);
                    sqrt_s(f0, f0);
                    swc1(f0, sp, 0xF8);
                    div_s(f12, f1, f0);
                    jal(ctx, 0x334F54u, gen::fn_asinf_0052ea00);
                    lwc1(f1, sp, 0x108);
                    add_s(f1, f1, f23);
                    add_s(f1, f0, f1);
                    lwc1(f0, sp, 0x104);
                    add_s(f0, f1, f0);
                    swc1(f0, sp, 0xD4);
                    mov_s(f12, f25);
                    a0 = addiu(sp, 0x110);
                    jal(ctx, 0x334F7Cu, gen::fn_sub_358340_00358340);
                    v0 = addiu(sp, 0x130);
                    lqc2(vf10, v0, 0);
                    vmula_bc(0xF, vf28, vf10, 0);  // vmulax.xyzw
                    vmadda_bc(0xF, vf29, vf10, 1);  // vmadday.xyzw
                    vmadd_bc(0xF, vf10, vf30, vf10, 2);  // vmaddz.xyzw
                    lwc1(f0, sp, 0xD4);
                    sub_s(f1, f0, f25);
                    lwc1(f0, sp, 0xDC);
                    mul_s(f26, f0, f1);
                    mov_s(f12, f26);
                    jal(ctx, 0x334FACu, gen::fn_sinf_0052e878);
                    mov_s(f25, f0);
                    mov_s(f12, f26);
                    jal(ctx, 0x334FBCu, gen::fn_cosf_0052e6d8);
                    div_s(f3, f25, f0);
                    lwc1(f26, sp, 0xD8);
                    lwc1(f25, sp, 0xD4);
                    add_s(f23, f23, f22);
                    vmove(0xF, vf12, vf10);  // vmove.xyzw
                    v0 = 0;
                    t0 = 0x6A0000;
                    a3 = 0x6A0000;
                    a2 = 0x6A0000;
                    t2 = 0x6A0000;
                    t2 = addiu(t2, -15152);  // &0x69C4D0
                    a1 = 0x6A0000;
                    a0 = 0x6A0000;
                    v1 = 0x6A0000;
                    for (;;) {
                        // 0x003350a0
                        charge(ctx, 3);
                        t1 = slti(v0, 5);
                        if (t1 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x0033500c
                        charge(ctx, 37);
                        t1 = sll(v0, 2);
                        t4 = addu(t1, sp);
                        lwc1(f0, t4, 320);
                        mul_s(f2, f3, f0);
                        t3 = addiu(t4, 352);
                        lwc1(f0, t3, 0);
                        add_s(f0, f0, f2);
                        swc1(f0, t3, 0);
                        vmove(0xF, vf11, vf12);  // vmove.xyzw
                        t1 = sll(v0, 1);
                        t1 = addu(t1, v0);
                        t1 = sll(t1, 2);
                        t1 = addu(s4, t1);
                        lwc1(f0, t1, -60);
                        swc1(f0, t0, -15152);
                        lwc1(f0, t1, -56);
                        swc1(f0, a3, -15148);
                        lwc1(f0, t1, -52);
                        swc1(f0, a2, -15144);
                        lqc2(vf10, t2, 0);
                        lwc1(f1, t3, 0);
                        lwc1(f0, sp, 0xF8);
                        add_s(f0, f0, f1);
                        mfc1(t3, f0);
                        qmtc2(t3, vf2, false);  // qmtc2
                        vmul_bc(0xF, vf11, vf11, vf2, 0);  // vmulx.xyzw
                        vadd(0xF, vf10, vf10, vf11);  // vadd.xyzw
                        sqc2(vf10, t2, 0);
                        lwc1(f0, a1, -15152);
                        swc1(f0, t1, 0);
                        lwc1(f0, a0, -15148);
                        swc1(f0, t1, 4);
                        lwc1(f0, v1, -15144);
                        swc1(f0, t1, 8);
                        swc1(f2, t4, 352);
                        v0 = addiu(v0, 1);
                    }
                    // 0x003350ac
                    charge(ctx, 2);
                    s5 = addiu(s5, 1);
                    s4 = addiu(s4, 60);
                }
                // 0x003350c0
                charge(ctx, 9);
                lw(v0, s2, 16);
                lw(s4, v0, 24);
                a0 = s4;
                jal(ctx, 0x3350CCu, gen::fn_sub_4933D0_004933d0);
                lhu(v1, s2, 0);
                v1 = v1 & 0x4;
                if (v1 != 0) {
                    // 0x003350e4
                    charge(ctx, 3);
                    lhu(v1, s4, 12);
                    v1 = v1 | 0x1;
                    sh(v1, s4, 12);
                }
            L_003350f0:
                charge(ctx, 3);
                lw(v1, s1, 4);
                v1 = addiu(v1, 1);
                sw(v1, s1, 4);
            }
            // 0x003350fc
            charge(ctx, 2);
            s0 = addiu(s0, 1);
            s1 = addiu(s1, 16);
        }
    }
    // 0x00335110 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0x180);
}

// 0x00335180 sub_335180 -- 612 bytes; frame 0xE0: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// Effect object, draw callback (data-referenced): sub_32A120, sub_323920, sub_4CB7F0, sub_323860.
void sub_335180(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f20{ctx, 20};
    Vf vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11};
    // 0x00335180
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0xE0);
    sd(ra, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s1 = a0;
    lw(v1, a0, 48);
    lw(s4, a0, 52);
    lw(s3, v1, 0);
    lw(a2, a0, 40);
    lw(a3, s4, 52);
    at = slt(a3, a2);
    if (at != 0) {
        // 0x003351c4
        charge(ctx, 2);
        if (a3 == 0) {
            goto L_003351cc;
        }
        // 0x003353bc (the shared epilogue, written out on this path)
        charge(ctx, 10);
        ld(ra, sp, 0x60);
        lq(s4, sp, 0x50);
        lq(s3, sp, 0x40);
        lq(s2, sp, 0x30);
        lq(s1, sp, 0x20);
        lq(s0, sp, 0x10);
        lwc1(f20, sp, 0x0);
        sp = addiu(sp, 0xE0);
        return;
    }
L_003351cc:
    charge(ctx, 43);
    lw(s0, s4, 56);
    a0 = s4;
    a1 = addiu(s4, 36);
    jal(ctx, 0x3351D8u, gen::fn_sub_32A120_0032a120);
    v1 = v0;
    lw(v0, s1, 36);
    sw(v0, sp, 0xD8);
    v0 = addiu(sp, 0xD8);
    lwc1(f20, gp, -32420);  // 0x7CAE4C
    lw(v0, v0, 0);
    pextlb(v0, zero, v0);
    pextlh(v0, zero, v0);
    qmtc2(v0, vf10, false);  // qmtc2
    vitof0(0xF, vf10, vf10);  // vitof0.xyzw
    mfc1(v0, f20);
    qmtc2(v0, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    vmove(0xF, vf11, vf10);  // vmove.xyzw
    sw(v1, sp, 0xD4);
    v0 = addiu(sp, 0xD4);
    lw(v0, v0, 0);
    pextlb(v0, zero, v0);
    pextlh(v0, zero, v0);
    qmtc2(v0, vf10, false);  // qmtc2
    vitof0(0xF, vf10, vf10);  // vitof0.xyzw
    mfc1(v0, f20);
    qmtc2(v0, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
    v0 = addiu(sp, 0xB0);
    sqc2(vf10, v0, 0);
    a0 = addiu(sp, 0x70);
    a1 = s1;
    a2 = 0;
    lwc1(f12, s1, 32);
    jal(ctx, 0x335264u, gen::fn_sub_323920_00323920);
    s2 = 0;
    for (;;) {
        // 0x003353b0
        charge(ctx, 3);
        v1 = slt(s2, s0);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00335278
        charge(ctx, 3);
        lw(v1, s3, 4);
        if (i64(v1) > 0) {
            // 0x00335284
            charge(ctx, 35);
            lw(s1, s3, 0);
            lw(a0, s1, 12);
            a1 = addiu(sp, 0x70);
            a2 = 0;
            jal(ctx, 0x335294u, gen::fn_sub_4CB7F0_004cb7f0);
            lw(v0, s3, 8);
            sw(v0, sp, 0xD0);
            v0 = addiu(sp, 0xD0);
            lw(v0, v0, 0);
            pextlb(v0, zero, v0);
            pextlh(v0, zero, v0);
            qmtc2(v0, vf10, false);  // qmtc2
            vitof0(0xF, vf10, vf10);  // vitof0.xyzw
            mfc1(v0, f20);
            qmtc2(v0, vf2, false);  // qmtc2
            vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
            v0 = addiu(sp, 0xB0);
            lqc2(vf11, v0, 0);
            vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
            v0 = 0x437F0000;
            qmtc2(v0, vf2, false);  // qmtc2
            vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
            vftoi0(0xF, vf10, vf10);  // vftoi0.xyzw
            qmfc2(v0, vf10, false);  // qmfc2
            ppach(v0, zero, v0);
            ppacb(v0, zero, v0);
            sw(v0, sp, 0xCC);
            lw(v0, sp, 0xCC);
            sw(v0, sp, 0xDC);
            lbu(v0, sp, 0xDF);
            a3 = 255;
            if (v0 == a3) {
                // 0x0033533c
                charge(ctx, 12);
                v0 = 254;
                sb(v0, sp, 0xDF);
                lw(a2, s1, 20);
                lbu(a1, sp, 0xDC);
                lbu(a0, sp, 0xDD);
                lbu(v1, sp, 0xDE);
                lbu(v0, sp, 0xDF);
                sb(a1, a2, 4);
                sb(a0, a2, 5);
                sb(v1, a2, 6);
                sb(v0, a2, 7);
                sb(a3, sp, 0xDF);
            } else {
                // 0x00335310
                charge(ctx, 11);
                lw(a2, s1, 20);
                lbu(a1, sp, 0xDC);
                lbu(a0, sp, 0xDD);
                lbu(v1, sp, 0xDE);
                lbu(v0, sp, 0xDF);
                sb(a1, a2, 4);
                sb(a0, a2, 5);
                sb(v1, a2, 6);
                sb(v0, a2, 7);
            }
            // 0x0033536c
            charge(ctx, 3);
            lbu(v0, s4, 92);
            if (v0 == 0) {
                // 0x0033538c
                charge(ctx, 3);
                lhu(v0, s1, 0);
                v0 = v0 & 0xFFFE;
                sh(v0, s1, 0);
            } else {
                // 0x00335378
                charge(ctx, 5);
                lhu(v0, s1, 0);
                v0 = v0 | 0x1;
                sh(v0, s1, 0);
            }
            // 0x00335398
            charge(ctx, 4);
            lhu(a1, s4, 40);
            a0 = s1;
            jal(ctx, 0x3353A0u, gen::fn_sub_323860_00323860);
        }
        // 0x003353a8
        charge(ctx, 2);
        s2 = addiu(s2, 1);
        s3 = addiu(s3, 16);
    }
    // 0x003353bc (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0xE0);
}

// 0x003353F0 sub_3353F0 -- 324 bytes; frame 0x60: ra sp+0x50, s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// Effect object step callback (data-referenced): sub_358030, sub_357FD0.
void sub_3353F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f20{ctx, 20}, f21{ctx, 21};
    // 0x003353f0
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lw(s3, a0, 48);
    lw(s1, a0, 52);
    lw(s2, s3, 0);
    lw(s0, s1, 52);
    lwc1(f20, s1, 144);
    a0 = 0;
    jal(ctx, 0x335428u, gen::fn_sub_358030_00358030);
    v1 = 0x3F800000;
    mtc1(v1, f1);
    sub_s(f2, f1, f20);
    mtc1(zero, f1);
    adda_s(f1, f2);
    madd_s(f2, f20, f0);
    lwc1(f0, s1, 140);
    mul_s(f21, f0, f2);
    if (i64(s0) <= 0) {
        // 0x003354c4
        charge(ctx, 2);
        swc1(f21, s3, 4);
        swc1(f1, s3, 8);
    } else {
        // 0x00335460
        charge(ctx, 25);
        lwc1(f20, s1, 152);
        a0 = 0;
        jal(ctx, 0x335468u, gen::fn_sub_358030_00358030);
        v1 = 0x3F800000;
        mtc1(v1, f1);
        sub_s(f2, f1, f20);
        mtc1(zero, f1);
        adda_s(f1, f2);
        madd_s(f1, f20, f0);
        lwc1(f0, s1, 148);
        mul_s(f0, f0, f1);
        swc1(f21, s3, 4);
        sub_s(f1, f0, f21);
        mtc1(s0, f0);
        cvt_s_w(f0, f0);
        div_s(f0, f1, f0);
        swc1(f0, s3, 8);
    }
    // 0x003354cc
    charge(ctx, 4);
    lw(s0, s1, 56);
    s1 = 0;
    for (;;) {
        // 0x00335500
        charge(ctx, 3);
        v1 = sltu(s1, s0);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003354dc
        charge(ctx, 9);
        a0 = 0;
        jal(ctx, 0x3354E0u, gen::fn_sub_357FD0_00357fd0);
        a0 = v0 & 0x7;
        v1 = si(-1);
        v1 = subu(v1, a0);
        sw(v1, s2, 20);
        s1 = addiu(s1, 1);
        s2 = addiu(s2, 48);
    }
    // 0x0033550c
    charge(ctx, 10);
    ld(ra, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00335540 sub_335540 -- 1176 bytes; frame 0xE0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Effect object, allocate callback (data-referenced): as sub_334390 for the second effect class.
void sub_335540(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8};
    // 0x00335540
    enter(ctx, 30);  // entry check point + this block's cycles
    sp = addiu(sp, -0xE0);
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
    lw(s7, a0, 56);
    v0 = sll(s7, 1);
    v0 = addu(v0, s7);
    v0 = sll(v0, 4);
    a0 = addiu(v0, 16);
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x335590u, v0.u());
    s4 = v0;
    v1 = addiu(s4, 16);
    sw(v1, v0, 0);
    sw(s4, v0, 12);
    lw(v0, s5, 60);
    at = sltiu(v0, 3);
    if (at != 0) {
        // 0x003355b8
        charge(ctx, 2);
        v0 = 3;
        sw(v0, s5, 60);
    }
    // 0x003355c0
    charge(ctx, 34);
    lw(a1, s5, 112);
    v0 = dsll32(a1, 8);
    v0 = dsrl32(v0, 8);
    sq(v0, sp, 0xD0);
    lw(a0, s5, 116);
    v0 = dsll32(a0, 8);
    v0 = dsrl32(v0, 8);
    sq(v0, sp, 0xC0);
    lw(v1, s5, 120);
    v0 = dsll32(v1, 8);
    v0 = dsrl32(v0, 8);
    sq(v0, sp, 0xB0);
    s1 = srl(a1, 24);
    s0 = srl(a0, 24);
    s6 = srl(v1, 24);
    lw(s3, s4, 0);
    lw(v0, s5, 60);
    v0 = addiu(v0, 1);
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, s5, 104);
    mul_s(f0, f0, f1);
    cvt_w_s(f0, f0);
    mfc1(fp, f0);
    lwc1(f0, s5, 108);
    mul_s(f0, f0, f1);
    cvt_w_s(f0, f0);
    mfc1(v0, f0);
    sq(v0, sp, 0xA0);
    s2 = 0;
    for (;;) {
        // 0x00335994
        charge(ctx, 3);
        v0 = sltu(s2, s7);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00335648
        charge(ctx, 36);
        lhu(a0, s5, 60);
        a1 = 0x6A0000;
        a1 = addiu(a1, -17120);  // &0x69BD20
        a2 = 5;
        a3 = 72;
        jal(ctx, 0x33565Cu, gen::fn_sub_323240_00323240);
        sw(v0, s3, 0);
        lh(a0, v0, 8);
        v1 = 5;
        div(a0, v1);
        mflo(t0);
        lw(v0, v0, 16);
        lw(v0, v0, 24);
        lw(t1, v0, 48);
        t2 = 0;
        lq(v0, sp, 0xA0);
        a3 = subu(t0, v0);
        a2 = a3 & 0x1;
        mtc1(a3, f6);
        v0 = 0x3F800000;
        mtc1(v0, f5);
        mtc1(fp, f0);
        cvt_s_w(f8, f0);
        a1 = s6 & 0x1;
        mtc1(s6, f4);
        v0 = 0x4F000000;
        mtc1(v0, f3);
        a0 = lui(0x8000);
        v1 = s0 & 0x1;
        mtc1(s0, f2);
        v0 = s1 & 0x1;
        mtc1(s1, f1);
        for (;;) {
            // 0x00335970
            charge(ctx, 3);
            t3 = sltu(t2, t0);
            if (t3 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003356d8
            charge(ctx, 3);
            at = sltu(t2, fp);
            if (at == 0) {
                // 0x0033573c
                charge(ctx, 4);
                lq(t3, sp, 0xA0);
                at = sltu(t3, t2);
                if (at == 0) {
                    // 0x003357d4
                    charge(ctx, 1);
                    mov_s(f7, f5);
                } else {
                    // 0x0033574c
                    charge(ctx, 3);
                    t3 = subu(t0, t2);
                    if (i64(t3) < 0) {
                        // 0x0033576c
                        charge(ctx, 7);
                        t4 = srl(t3, 1);
                        t3 = t3 & 0x1;
                        t4 = t4 | t3;
                        mtc1(t4, f0);
                        cvt_s_w(f7, f0);
                        add_s(f7, f7, f7);
                    } else {
                        // 0x00335758
                        charge(ctx, 5);
                        mtc1(t3, f0);
                        cvt_s_w(f7, f0);
                    }
                    // 0x00335788
                    charge(ctx, 2);
                    if (i64(a3) < 0) {
                        // 0x0033579c
                        charge(ctx, 6);
                        t3 = srl(a3, 1);
                        t3 = t3 | a2;
                        mtc1(t3, f0);
                        cvt_s_w(f0, f0);
                        add_s(f0, f0, f0);
                    } else {
                        // 0x00335790
                        charge(ctx, 3);
                        cvt_s_w(f0, f6);
                    }
                    // 0x003357b4
                    charge(ctx, 8);
                    div_s(f7, f7, f0);
                }
            } else {
                // 0x003356e4
                charge(ctx, 2);
                if (i64(t2) < 0) {
                    // 0x00335700
                    charge(ctx, 7);
                    t4 = srl(t2, 1);
                    t3 = t2 & 0x1;
                    t4 = t4 | t3;
                    mtc1(t4, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f0, f0);
                } else {
                    // 0x003356ec
                    charge(ctx, 5);
                    mtc1(t2, f0);
                    cvt_s_w(f0, f0);
                }
                // 0x0033571c
                charge(ctx, 8);
                div_s(f7, f0, f8);
            }
            // 0x003357d8
            charge(ctx, 2);
            if (i64(s6) < 0) {
                // 0x003357ec
                charge(ctx, 6);
                t3 = srl(s6, 1);
                t3 = t3 | a1;
                mtc1(t3, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f0, f0);
            } else {
                // 0x003357e0
                charge(ctx, 3);
                cvt_s_w(f0, f4);
            }
            // 0x00335804
            charge(ctx, 4);
            mul_s(f0, f0, f7);
            c_le_s(f3, f0);
            if (cond(ctx)) {
                // 0x00335824
                charge(ctx, 5);
                sub_s(f0, f0, f3);
                cvt_w_s(f0, f0);
                mfc1(t3, f0);
                t3 = t3 | a0;
            } else {
                // 0x00335814
                charge(ctx, 4);
                cvt_w_s(f0, f0);
                mfc1(t3, f0);
            }
            // 0x00335838
            charge(ctx, 6);
            t4 = sll(t3, 24);
            lq(t3, sp, 0xB0);
            t3 = t3 | t4;
            sw(t3, t1, 0);
            if (i64(s0) < 0) {
                // 0x0033585c
                charge(ctx, 6);
                t3 = srl(s0, 1);
                t3 = t3 | v1;
                mtc1(t3, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f0, f0);
            } else {
                // 0x00335850
                charge(ctx, 3);
                cvt_s_w(f0, f2);
            }
            // 0x00335874
            charge(ctx, 4);
            mul_s(f0, f0, f7);
            c_le_s(f3, f0);
            if (cond(ctx)) {
                // 0x00335894
                charge(ctx, 5);
                sub_s(f0, f0, f3);
                cvt_w_s(f0, f0);
                mfc1(t3, f0);
                t3 = t3 | a0;
            } else {
                // 0x00335884
                charge(ctx, 4);
                cvt_w_s(f0, f0);
                mfc1(t3, f0);
            }
            // 0x003358a8
            charge(ctx, 6);
            t4 = sll(t3, 24);
            lq(t3, sp, 0xC0);
            t3 = t3 | t4;
            sw(t3, t1, 4);
            if (i64(s1) < 0) {
                // 0x003358cc
                charge(ctx, 6);
                t3 = srl(s1, 1);
                t3 = t3 | v0;
                mtc1(t3, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f0, f0);
            } else {
                // 0x003358c0
                charge(ctx, 3);
                cvt_s_w(f0, f1);
            }
            // 0x003358e4
            charge(ctx, 4);
            mul_s(f0, f0, f7);
            c_le_s(f3, f0);
            if (cond(ctx)) {
                // 0x00335904
                charge(ctx, 5);
                sub_s(f0, f0, f3);
                cvt_w_s(f0, f0);
                mfc1(t3, f0);
                t3 = t3 | a0;
            } else {
                // 0x003358f4
                charge(ctx, 4);
                cvt_w_s(f0, f0);
                mfc1(t3, f0);
            }
            // 0x00335918
            charge(ctx, 22);
            t4 = sll(t3, 24);
            lq(t3, sp, 0xD0);
            t3 = t3 | t4;
            sw(t3, t1, 8);
            lbu(t6, t1, 4);
            lbu(t5, t1, 5);
            lbu(t4, t1, 6);
            lbu(t3, t1, 7);
            sb(t6, t1, 12);
            sb(t5, t1, 13);
            sb(t4, t1, 14);
            sb(t3, t1, 15);
            lbu(t6, t1, 0);
            lbu(t5, t1, 1);
            lbu(t4, t1, 2);
            lbu(t3, t1, 3);
            sb(t6, t1, 16);
            sb(t5, t1, 17);
            sb(t4, t1, 18);
            sb(t3, t1, 19);
            t2 = addiu(t2, 1);
            t1 = addiu(t1, 20);
        }
        // 0x0033597c
        charge(ctx, 6);
        v1 = si(-1);
        v0 = sll(s2, 2);
        v0 = subu(v1, v0);
        sw(v0, s3, 20);
        s2 = addiu(s2, 1);
        s3 = addiu(s3, 48);
    }
    // 0x003359a0
    charge(ctx, 14);
    v0 = s4;
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
    sp = addiu(sp, 0xE0);
}

// 0x003359E0 sub_3359E0 -- 136 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Effect object, release callback (data-referenced): as sub_334820 for the second effect class.
void sub_3359E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003359e0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s1, a0, 48);
    lw(s3, s1, 0);
    lw(v0, a0, 52);
    lw(s0, v0, 56);
    s2 = 0;
    for (;;) {
        // 0x00335a28
        charge(ctx, 3);
        v0 = sltu(s2, s0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00335a14
        charge(ctx, 5);
        lw(a0, s3, 0);
        jal(ctx, 0x335A18u, gen::fn_sub_3237C0_003237c0);
        s2 = addiu(s2, 1);
        s3 = addiu(s3, 48);
    }
    // 0x00335a34
    charge(ctx, 13);
    lw(a0, s1, 12);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x335A40u, v0.u());
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00336630 sub_336630 -- 612 bytes; frame 0xE0: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// Effect object, draw callback (data-referenced): as sub_335180 for the second effect class.
void sub_336630(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f20{ctx, 20};
    Vf vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11};
    // 0x00336630
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0xE0);
    sd(ra, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s1 = a0;
    lw(v1, a0, 48);
    lw(s4, a0, 52);
    lw(s3, v1, 0);
    lw(a2, a0, 40);
    lw(a3, s4, 52);
    at = slt(a3, a2);
    if (at != 0) {
        // 0x00336674
        charge(ctx, 2);
        if (a3 == 0) {
            goto L_0033667c;
        }
        // 0x0033686c (the shared epilogue, written out on this path)
        charge(ctx, 10);
        ld(ra, sp, 0x60);
        lq(s4, sp, 0x50);
        lq(s3, sp, 0x40);
        lq(s2, sp, 0x30);
        lq(s1, sp, 0x20);
        lq(s0, sp, 0x10);
        lwc1(f20, sp, 0x0);
        sp = addiu(sp, 0xE0);
        return;
    }
L_0033667c:
    charge(ctx, 43);
    lw(s0, s4, 56);
    a0 = s4;
    a1 = addiu(s4, 36);
    jal(ctx, 0x336688u, gen::fn_sub_32A120_0032a120);
    v1 = v0;
    lw(v0, s1, 36);
    sw(v0, sp, 0xD8);
    v0 = addiu(sp, 0xD8);
    lwc1(f20, gp, -32420);  // 0x7CAE4C
    lw(v0, v0, 0);
    pextlb(v0, zero, v0);
    pextlh(v0, zero, v0);
    qmtc2(v0, vf10, false);  // qmtc2
    vitof0(0xF, vf10, vf10);  // vitof0.xyzw
    mfc1(v0, f20);
    qmtc2(v0, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    vmove(0xF, vf11, vf10);  // vmove.xyzw
    sw(v1, sp, 0xD4);
    v0 = addiu(sp, 0xD4);
    lw(v0, v0, 0);
    pextlb(v0, zero, v0);
    pextlh(v0, zero, v0);
    qmtc2(v0, vf10, false);  // qmtc2
    vitof0(0xF, vf10, vf10);  // vitof0.xyzw
    mfc1(v0, f20);
    qmtc2(v0, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
    v0 = addiu(sp, 0xB0);
    sqc2(vf10, v0, 0);
    a0 = addiu(sp, 0x70);
    a1 = s1;
    a2 = addiu(s1, 16);
    lwc1(f12, s1, 32);
    jal(ctx, 0x336714u, gen::fn_sub_323920_00323920);
    s2 = 0;
    for (;;) {
        // 0x00336860
        charge(ctx, 3);
        v1 = slt(s2, s0);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00336728
        charge(ctx, 3);
        lw(v1, s3, 20);
        if (i64(v1) > 0) {
            // 0x00336734
            charge(ctx, 35);
            lw(s1, s3, 0);
            lw(a0, s1, 12);
            a1 = addiu(sp, 0x70);
            a2 = 0;
            jal(ctx, 0x336744u, gen::fn_sub_4CB7F0_004cb7f0);
            lw(v0, s3, 24);
            sw(v0, sp, 0xD0);
            v0 = addiu(sp, 0xD0);
            lw(v0, v0, 0);
            pextlb(v0, zero, v0);
            pextlh(v0, zero, v0);
            qmtc2(v0, vf10, false);  // qmtc2
            vitof0(0xF, vf10, vf10);  // vitof0.xyzw
            mfc1(v0, f20);
            qmtc2(v0, vf2, false);  // qmtc2
            vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
            v0 = addiu(sp, 0xB0);
            lqc2(vf11, v0, 0);
            vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
            v0 = 0x437F0000;
            qmtc2(v0, vf2, false);  // qmtc2
            vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
            vftoi0(0xF, vf10, vf10);  // vftoi0.xyzw
            qmfc2(v0, vf10, false);  // qmfc2
            ppach(v0, zero, v0);
            ppacb(v0, zero, v0);
            sw(v0, sp, 0xCC);
            lw(v0, sp, 0xCC);
            sw(v0, sp, 0xDC);
            lbu(v0, sp, 0xDF);
            a3 = 255;
            if (v0 == a3) {
                // 0x003367ec
                charge(ctx, 12);
                v0 = 254;
                sb(v0, sp, 0xDF);
                lw(a2, s1, 20);
                lbu(a1, sp, 0xDC);
                lbu(a0, sp, 0xDD);
                lbu(v1, sp, 0xDE);
                lbu(v0, sp, 0xDF);
                sb(a1, a2, 4);
                sb(a0, a2, 5);
                sb(v1, a2, 6);
                sb(v0, a2, 7);
                sb(a3, sp, 0xDF);
            } else {
                // 0x003367c0
                charge(ctx, 11);
                lw(a2, s1, 20);
                lbu(a1, sp, 0xDC);
                lbu(a0, sp, 0xDD);
                lbu(v1, sp, 0xDE);
                lbu(v0, sp, 0xDF);
                sb(a1, a2, 4);
                sb(a0, a2, 5);
                sb(v1, a2, 6);
                sb(v0, a2, 7);
            }
            // 0x0033681c
            charge(ctx, 3);
            lbu(v0, s4, 92);
            if (v0 == 0) {
                // 0x0033683c
                charge(ctx, 3);
                lhu(v0, s1, 0);
                v0 = v0 & 0xFFFE;
                sh(v0, s1, 0);
            } else {
                // 0x00336828
                charge(ctx, 5);
                lhu(v0, s1, 0);
                v0 = v0 | 0x1;
                sh(v0, s1, 0);
            }
            // 0x00336848
            charge(ctx, 4);
            lhu(a1, s4, 40);
            a0 = s1;
            jal(ctx, 0x336850u, gen::fn_sub_323860_00323860);
        }
        // 0x00336858
        charge(ctx, 2);
        s2 = addiu(s2, 1);
        s3 = addiu(s3, 48);
    }
    // 0x0033686c (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0xE0);
}

// 0x003368A0 sub_3368A0 -- 124 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Effect object update callback (data-referenced): sub_357FD0 (third class).
void sub_3368A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003368a0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a0, 48);
    lw(s2, v1, 0);
    lw(v1, a0, 52);
    lw(s0, v1, 56);
    s1 = 0;
    for (;;) {
        // 0x003368f4
        charge(ctx, 3);
        v1 = sltu(s1, s0);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003368d0
        charge(ctx, 9);
        a0 = 0;
        jal(ctx, 0x3368D4u, gen::fn_sub_357FD0_00357fd0);
        a0 = v0 & 0x3;
        v1 = si(-1);
        v1 = subu(v1, a0);
        sw(v1, s2, 4);
        s1 = addiu(s1, 1);
        s2 = addiu(s2, 12);
    }
    // 0x00336900
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00336920 sub_336920 -- 1232 bytes; frame 0xF0: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// Effect object, allocate callback (data-referenced): as sub_334390 for the third effect class.
void sub_336920(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f20{ctx, 20};
    // 0x00336920
    enter(ctx, 30);  // entry check point + this block's cycles
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
    swc1(f20, sp, 0x0);
    s5 = a0;
    lw(s7, a0, 56);
    v0 = sll(s7, 1);
    v0 = addu(v0, s7);
    v0 = sll(v0, 2);
    a0 = addiu(v0, 4);
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x336974u, v0.u());
    s6 = v0;
    v1 = addiu(s6, 4);
    sw(v1, v0, 0);
    lw(v0, s5, 60);
    at = sltiu(v0, 3);
    if (at != 0) {
        // 0x00336998
        charge(ctx, 2);
        v0 = 3;
        sw(v0, s5, 60);
    }
    // 0x003369a0
    charge(ctx, 4);
    lw(v1, s5, 60);
    v0 = v1 & 0x1;
    if (v0 == 0) {
        // 0x003369b0
        charge(ctx, 2);
        v0 = addiu(v1, 1);
        sw(v0, s5, 60);
    }
    // 0x003369b8
    charge(ctx, 35);
    lw(a1, s5, 112);
    v0 = dsll32(a1, 8);
    v0 = dsrl32(v0, 8);
    sq(v0, sp, 0xE0);
    lw(a0, s5, 116);
    v0 = dsll32(a0, 8);
    v0 = dsrl32(v0, 8);
    sq(v0, sp, 0xD0);
    lw(v1, s5, 120);
    v0 = dsll32(v1, 8);
    v0 = dsrl32(v0, 8);
    sq(v0, sp, 0xC0);
    s2 = srl(a1, 24);
    s1 = srl(a0, 24);
    s0 = srl(v1, 24);
    lw(s4, s6, 0);
    lw(v0, s5, 60);
    v0 = addiu(v0, 1);
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, s5, 104);
    mul_s(f0, f0, f1);
    cvt_w_s(f0, f0);
    mfc1(fp, f0);
    lwc1(f0, s5, 108);
    mul_s(f0, f0, f1);
    cvt_w_s(f0, f0);
    mfc1(v0, f0);
    sq(v0, sp, 0xB0);
    mtc1(zero, f20);
    s3 = 0;
    for (;;) {
        // 0x00336da8
        charge(ctx, 3);
        v0 = sltu(s3, s7);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00336a44
        charge(ctx, 36);
        lhu(a0, s5, 60);
        a1 = 0x6A0000;
        a1 = addiu(a1, -17120);  // &0x69BD20
        a2 = 5;
        a3 = 72;
        jal(ctx, 0x336A58u, gen::fn_sub_323240_00323240);
        sw(v0, s4, 0);
        lh(a0, v0, 8);
        v1 = 5;
        div(a0, v1);
        mflo(t0);
        lw(v0, v0, 16);
        lw(v0, v0, 24);
        lw(t1, v0, 48);
        t2 = 0;
        lq(v0, sp, 0xB0);
        a3 = subu(t0, v0);
        a2 = a3 & 0x1;
        mtc1(a3, f6);
        v0 = 0x3F800000;
        mtc1(v0, f5);
        mtc1(fp, f0);
        cvt_s_w(f8, f0);
        a1 = s0 & 0x1;
        mtc1(s0, f4);
        v0 = 0x4F000000;
        mtc1(v0, f3);
        a0 = lui(0x8000);
        v1 = s1 & 0x1;
        mtc1(s1, f2);
        v0 = s2 & 0x1;
        mtc1(s2, f1);
        for (;;) {
            // 0x00336d84
            charge(ctx, 3);
            t3 = sltu(t2, t0);
            if (t3 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00336ad4
            charge(ctx, 3);
            t3 = t2 & 0x1;
            if (t3 == 0) {
                // 0x00336ae0
                charge(ctx, 2);
                if (t2 == 0) {
                    goto L_00336ae8;
                }
                goto L_00336bec;
            }
        L_00336ae8:
            charge(ctx, 3);
            at = sltu(t2, fp);
            if (at == 0) {
                // 0x00336b4c
                charge(ctx, 4);
                lq(t3, sp, 0xB0);
                at = sltu(t3, t2);
                if (at == 0) {
                    // 0x00336be8
                    charge(ctx, 1);
                    mov_s(f20, f5);
                } else {
                    // 0x00336b5c
                    charge(ctx, 4);
                    t3 = subu(t0, t2);
                    t3 = addiu(t3, -1);
                    if (i64(t3) < 0) {
                        // 0x00336b80
                        charge(ctx, 7);
                        t4 = srl(t3, 1);
                        t3 = t3 & 0x1;
                        t4 = t4 | t3;
                        mtc1(t4, f0);
                        cvt_s_w(f7, f0);
                        add_s(f7, f7, f7);
                    } else {
                        // 0x00336b6c
                        charge(ctx, 5);
                        mtc1(t3, f0);
                        cvt_s_w(f7, f0);
                    }
                    // 0x00336b9c
                    charge(ctx, 2);
                    if (i64(a3) < 0) {
                        // 0x00336bb0
                        charge(ctx, 6);
                        t3 = srl(a3, 1);
                        t3 = t3 | a2;
                        mtc1(t3, f0);
                        cvt_s_w(f0, f0);
                        add_s(f0, f0, f0);
                    } else {
                        // 0x00336ba4
                        charge(ctx, 3);
                        cvt_s_w(f0, f6);
                    }
                    // 0x00336bc8
                    charge(ctx, 8);
                    div_s(f20, f7, f0);
                }
            } else {
                // 0x00336af4
                charge(ctx, 2);
                if (i64(t2) < 0) {
                    // 0x00336b10
                    charge(ctx, 7);
                    t4 = srl(t2, 1);
                    t3 = t2 & 0x1;
                    t4 = t4 | t3;
                    mtc1(t4, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f0, f0);
                } else {
                    // 0x00336afc
                    charge(ctx, 5);
                    mtc1(t2, f0);
                    cvt_s_w(f0, f0);
                }
                // 0x00336b2c
                charge(ctx, 8);
                div_s(f20, f0, f8);
            }
        L_00336bec:
            charge(ctx, 2);
            if (i64(s0) < 0) {
                // 0x00336c00
                charge(ctx, 6);
                t3 = srl(s0, 1);
                t3 = t3 | a1;
                mtc1(t3, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f0, f0);
            } else {
                // 0x00336bf4
                charge(ctx, 3);
                cvt_s_w(f0, f4);
            }
            // 0x00336c18
            charge(ctx, 4);
            mul_s(f0, f0, f20);
            c_le_s(f3, f0);
            if (cond(ctx)) {
                // 0x00336c38
                charge(ctx, 5);
                sub_s(f0, f0, f3);
                cvt_w_s(f0, f0);
                mfc1(t3, f0);
                t3 = t3 | a0;
            } else {
                // 0x00336c28
                charge(ctx, 4);
                cvt_w_s(f0, f0);
                mfc1(t3, f0);
            }
            // 0x00336c4c
            charge(ctx, 6);
            t4 = sll(t3, 24);
            lq(t3, sp, 0xC0);
            t3 = t3 | t4;
            sw(t3, t1, 0);
            if (i64(s1) < 0) {
                // 0x00336c70
                charge(ctx, 6);
                t3 = srl(s1, 1);
                t3 = t3 | v1;
                mtc1(t3, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f0, f0);
            } else {
                // 0x00336c64
                charge(ctx, 3);
                cvt_s_w(f0, f2);
            }
            // 0x00336c88
            charge(ctx, 4);
            mul_s(f0, f0, f20);
            c_le_s(f3, f0);
            if (cond(ctx)) {
                // 0x00336ca8
                charge(ctx, 5);
                sub_s(f0, f0, f3);
                cvt_w_s(f0, f0);
                mfc1(t3, f0);
                t3 = t3 | a0;
            } else {
                // 0x00336c98
                charge(ctx, 4);
                cvt_w_s(f0, f0);
                mfc1(t3, f0);
            }
            // 0x00336cbc
            charge(ctx, 6);
            t4 = sll(t3, 24);
            lq(t3, sp, 0xD0);
            t3 = t3 | t4;
            sw(t3, t1, 4);
            if (i64(s2) < 0) {
                // 0x00336ce0
                charge(ctx, 6);
                t3 = srl(s2, 1);
                t3 = t3 | v0;
                mtc1(t3, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f0, f0);
            } else {
                // 0x00336cd4
                charge(ctx, 3);
                cvt_s_w(f0, f1);
            }
            // 0x00336cf8
            charge(ctx, 4);
            mul_s(f0, f0, f20);
            c_le_s(f3, f0);
            if (cond(ctx)) {
                // 0x00336d18
                charge(ctx, 5);
                sub_s(f0, f0, f3);
                cvt_w_s(f0, f0);
                mfc1(t3, f0);
                t3 = t3 | a0;
            } else {
                // 0x00336d08
                charge(ctx, 4);
                cvt_w_s(f0, f0);
                mfc1(t3, f0);
            }
            // 0x00336d2c
            charge(ctx, 22);
            t4 = sll(t3, 24);
            lq(t3, sp, 0xE0);
            t3 = t3 | t4;
            sw(t3, t1, 8);
            lbu(t6, t1, 4);
            lbu(t5, t1, 5);
            lbu(t4, t1, 6);
            lbu(t3, t1, 7);
            sb(t6, t1, 12);
            sb(t5, t1, 13);
            sb(t4, t1, 14);
            sb(t3, t1, 15);
            lbu(t6, t1, 0);
            lbu(t5, t1, 1);
            lbu(t4, t1, 2);
            lbu(t3, t1, 3);
            sb(t6, t1, 16);
            sb(t5, t1, 17);
            sb(t4, t1, 18);
            sb(t3, t1, 19);
            t1 = addiu(t1, 20);
            t2 = addiu(t2, 1);
        }
        // 0x00336d90
        charge(ctx, 6);
        v1 = si(-1);
        v0 = sll(s3, 2);
        v0 = subu(v1, v0);
        sw(v0, s4, 4);
        s3 = addiu(s3, 1);
        s4 = addiu(s4, 12);
    }
    // 0x00336db4
    charge(ctx, 15);
    v0 = s6;
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
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0xF0);
}

// 0x00336DF0 sub_336DF0 -- 136 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Effect object, release callback (data-referenced): as sub_334820 for the third effect class.
void sub_336DF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00336df0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s3, a0, 48);
    lw(s2, s3, 0);
    lw(v0, a0, 52);
    lw(s0, v0, 56);
    s1 = 0;
    for (;;) {
        // 0x00336e38
        charge(ctx, 3);
        v0 = sltu(s1, s0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00336e24
        charge(ctx, 5);
        lw(a0, s2, 0);
        jal(ctx, 0x336E28u, gen::fn_sub_3237C0_003237c0);
        s1 = addiu(s1, 1);
        s2 = addiu(s2, 12);
    }
    // 0x00336e44
    charge(ctx, 13);
    a0 = s3;
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x336E50u, v0.u());
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00336E80 sub_336E80 -- 2412 bytes; frame 0x1A0: ra sp+0xC0, fp sp+0xB0 (sq), s7 sp+0xA0 (sq), s6 sp+0x90 (sq), s5 sp+0x80 (sq), s4 sp+0x70 (sq), s3 sp+0x60 (sq), s2 sp+0x50 (sq), s1 sp+0x40 (sq), s0 sp+0x30 (sq), f31 sp+0x2C, f30 sp+0x28, f29 sp+0x24, f28 sp+0x20, f27 sp+0x1C, f26 sp+0x18, f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// Effect object, particle update callback (third class): geometry lock, per-vertex sinf motion, unlock.
void sub_336E80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25}, f26{ctx, 26}, f27{ctx, 27}, f28{ctx, 28}, f29{ctx, 29}, f30{ctx, 30}, f31{ctx, 31};
    Vf vf0{ctx, 0}, vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11}, vf12{ctx, 12}, vf28{ctx, 28}, vf29{ctx, 29}, vf30{ctx, 30};
    // 0x00336e80
    enter(ctx, 32);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1A0);
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
    s2 = a0;
    lw(v1, a0, 48);
    lw(s1, a0, 52);
    lw(s0, v1, 0);
    lw(a1, s1, 52);
    lw(v1, a0, 40);
    at = sltu(a1, v1);
    if (at != 0) {
        // 0x00336f00
        charge(ctx, 2);
        if (a1 == 0) {
            goto L_00336f08;
        }
        // 0x00337788 (the shared epilogue, written out on this path)
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
        sp = addiu(sp, 0x1A0);
        return;
    }
L_00336f08:
    charge(ctx, 61);
    lw(s7, s1, 56);
    lw(s6, s1, 64);
    a0 = addiu(sp, 0x100);
    jal(ctx, 0x336F14u, gen::fn_sub_329740_00329740);
    v0 = 0x6A0000;
    v0 = addiu(v0, -15200);  // &0x69C4A0
    lqc2(vf10, v0, 0);  // 0x69C4A0
    vmove(0xF, vf12, vf10);  // vmove.xyzw
    lwc1(f1, s1, 124);
    mfc1(v0, f1);
    qmtc2(v0, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    v0 = addiu(sp, 0x190);
    sqc2(vf10, v0, 0);
    vmove(0xF, vf10, vf12);  // vmove.xyzw
    lwc1(f0, s1, 128);
    add_s(f0, f1, f0);
    mfc1(v0, f0);
    qmtc2(v0, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    v0 = addiu(sp, 0x180);
    sqc2(vf10, v0, 0);
    vsub(0xE, vf10, vf0, vf10);  // vsub.xyz
    v0 = addiu(sp, 0x170);
    sqc2(vf10, v0, 0);
    lqc2(vf10, s2, 16);
    jal(ctx, 0x336F7Cu, gen::fn_sub_357E30_00357e30);
    v0 = 0x6A0000;
    v0 = addiu(v0, -15168);  // &0x69C4C0
    lqc2(vf10, v0, 0);  // 0x69C4C0
    vmula_bc(0xF, vf28, vf10, 0);  // vmulax.xyzw
    vmadda_bc(0xF, vf29, vf10, 1);  // vmadday.xyzw
    vmadd_bc(0xF, vf10, vf30, vf10, 2);  // vmaddz.xyzw
    lw(v0, s1, 132);
    qmtc2(v0, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    vmove(0xF, vf11, vf0);  // vmove.xyzw
    vmul(0xE, vf2, vf10, vf10);  // vmul.xyz
    vadd_bc(0x8, vf2, vf2, vf2, 1);  // vaddy.x
    vadd_bc(0x8, vf2, vf2, vf2, 2);  // vaddz.x
    vsqrt(vf2, 0);  // vsqrt
    vwaitq(ctx);
    cfc2(v0, 22, false);  // cfc2
    mtc1(v0, f2);
    vmul(0xE, vf2, vf10, vf10);  // vmul.xyz
    vmula_bc(0x1, vf0, vf2, 0);  // vmulax.w
    vmadda_bc(0x1, vf0, vf2, 1);  // vmadday.w
    vmadd_bc(0x1, vf2, vf0, vf2, 2);  // vmaddz.w
    vrsqrt(vf0, 3, vf2, 3);  // vrsqrt
    vwaitq(ctx);
    vmulq(0xE, vf10, vf10);  // vmulq.xyz
    v1 = addiu(sp, 0x160);
    sqc2(vf10, v1, 0);
    lw(v1, s1, 60);
    if (i64(v1) < 0) {
        // 0x00337010
        charge(ctx, 7);
        a0 = srl(v1, 1);
        v1 = v1 & 0x1;
        a0 = a0 | v1;
        mtc1(a0, f0);
        cvt_s_w(f1, f0);
        add_s(f1, f1, f1);
    } else {
        // 0x00336ffc
        charge(ctx, 5);
        mtc1(v1, f0);
        cvt_s_w(f1, f0);
    }
    // 0x0033702c
    charge(ctx, 29);
    v1 = 0x40000000;
    mtc1(v1, f21);
    mul_s(f0, f21, f2);
    div_s(f31, f0, f1);
    lwc1(f26, s1, 68);
    mov_s(f27, f26);
    s4 = 0;
    fp = si(-0x1);
    lwc1(f25, gp, -32352);  // 0x7CAE90
    mtc1(zero, f0);
    swc1(f0, sp, 0xE0);
    lwc1(f24, gp, -32408);  // 0x7CAE58
    v1 = 0x40800000;
    mtc1(v1, f23);
    lwc1(f22, gp, -32472);  // 0x7CAE18
    v1 = 0x3F800000;
    mtc1(v1, f0);
    swc1(f0, sp, 0xEC);
    v1 = 0x3F000000;
    mtc1(v1, f0);
    swc1(f0, sp, 0xE8);
    lwc1(f0, gp, -32348);  // 0x7CAE94
    swc1(f0, sp, 0xE4);
    for (;;) {
        // 0x0033777c
        charge(ctx, 3);
        v1 = slt(s4, s7);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003370a0
        charge(ctx, 4);
        lw(v1, s0, 4);
        a1 = si(-1);
        if (v1 == a1) {
            // 0x003370b0
            charge(ctx, 3);
            sw(fp, s0, 8);
            goto L_00337768;
        }
        // 0x003370bc
        charge(ctx, 8);
        lw(a0, s0, 8);
        v1 = lui(0xFF00);
        v1 = a0 & v1;
        at = 0x40000000;
        at = at | 0x1;
        at = sltu(v1, at);
        if (at != 0) {
            // 0x003370f0
            charge(ctx, 3);
            sw(a1, s0, 4);
            if (i64(s6) > 0) {
                // 0x003370fc
                charge(ctx, 10);
                a0 = 0;
                jal(ctx, 0x337100u, gen::fn_sub_357FD0_00357fd0);
                divu(v0, s6);
                mfhi(a0);
                lw(v1, s0, 4);
                v1 = subu(v1, a0);
                sw(v1, s0, 4);
            }
        } else {
            // 0x003370dc
            charge(ctx, 5);
            v0 = lui(0xC000);
            v0 = addu(a0, v0);
            sw(v0, s0, 8);
            // 0x00337124
            charge(ctx, 91);
            lw(s2, s0, 0);
            lh(v1, s2, 8);
            v0 = 5;
            div(v1, v0);
            mflo(v0);
            s1 = sra(v0, 1);
            lw(v0, s2, 16);
            lw(a0, v0, 24);
            a1 = 2;
            jal(ctx, 0x337148u, gen::fn_geometryLock_00493370);
            lw(v0, s2, 16);
            lw(v0, v0, 24);
            lw(v0, v0, 92);
            lw(s3, v0, 20);
            v0 = addiu(sp, 0x100);
            lqc2(vf10, v0, 0);
            v0 = addiu(sp, 0x160);
            lqc2(vf11, v0, 0);
            vopmula(0xE, vf10, vf11);  // vopmula.xyz
            vopmsub(0xE, vf10, vf11, vf10);  // vopmsub.xyz
            vmul(0xE, vf2, vf10, vf10);  // vmul.xyz
            vmula_bc(0x1, vf0, vf2, 0);  // vmulax.w
            vmadda_bc(0x1, vf0, vf2, 1);  // vmadday.w
            vmadd_bc(0x1, vf2, vf0, vf2, 2);  // vmaddz.w
            vrsqrt(vf0, 3, vf2, 3);  // vrsqrt
            vwaitq(ctx);
            vmulq(0xE, vf10, vf10);  // vmulq.xyz
            v0 = addiu(sp, 0x150);
            sqc2(vf10, v0, 0);
            a0 = 0;
            jal(ctx, 0x3371A0u, gen::fn_sub_358030_00358030);
            mul_s(f30, f25, f0);
            sub_s(f29, f30, f25);
            mov_s(f12, f30);
            jal(ctx, 0x3371B4u, gen::fn_sinf_0052e878);
            mul_s(f28, f27, f0);
            v0 = addiu(sp, 0x150);
            lqc2(vf10, v0, 0);
            mfc1(v0, f28);
            qmtc2(v0, vf2, false);  // qmtc2
            vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
            v0 = addiu(sp, 0x120);
            sqc2(vf10, v0, 0);
            mov_s(f12, f30);
            jal(ctx, 0x3371E4u, gen::fn_sinf_0052e878);
            mul_s(f20, f27, f0);
            sub_s(f0, f20, f28);
            v0 = addiu(sp, 0x160);
            lqc2(vf10, v0, 0);
            mfc1(v0, f31);
            qmtc2(v0, vf2, false);  // qmtc2
            vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
            vmove(0xF, vf12, vf10);  // vmove.xyzw
            v0 = addiu(sp, 0x150);
            lqc2(vf10, v0, 0);
            mfc1(v0, f0);
            qmtc2(v0, vf2, false);  // qmtc2
            vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
            vadd(0xF, vf10, vf10, vf12);  // vadd.xyzw
            vmove(0xF, vf12, vf10);  // vmove.xyzw
            v0 = addiu(sp, 0x120);
            lqc2(vf11, v0, 0);
            vadd(0xF, vf11, vf11, vf10);  // vadd.xyzw
            v0 = addiu(sp, 0x110);
            sqc2(vf11, v0, 0);
            vmove(0xF, vf10, vf12);  // vmove.xyzw
            vmul(0xE, vf2, vf10, vf10);  // vmul.xyz
            vmula_bc(0x1, vf0, vf2, 0);  // vmulax.w
            vmadda_bc(0x1, vf0, vf2, 1);  // vmadday.w
            vmadd_bc(0x1, vf2, vf0, vf2, 2);  // vmaddz.w
            vrsqrt(vf0, 3, vf2, 3);  // vrsqrt
            vwaitq(ctx);
            vmulq(0xE, vf10, vf10);  // vmulq.xyz
            v0 = addiu(sp, 0x140);
            sqc2(vf10, v0, 0);
            mtc1(s1, f0);
            cvt_s_w(f0, f0);
            div_s(f0, f24, f0);
            mul_s(f28, f23, f0);
            s5 = 0;
            for (;;) {
                // 0x0033772c
                charge(ctx, 3);
                v0 = slt(s5, s1);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00337290
                charge(ctx, 171);
                t0 = addiu(sp, 0x140);
                lqc2(vf10, t0, 0);
                v0 = addiu(sp, 0x100);
                lqc2(vf11, v0, 0);
                vopmula(0xE, vf10, vf11);  // vopmula.xyz
                vopmsub(0xE, vf10, vf11, vf10);  // vopmsub.xyz
                vmul(0xE, vf2, vf10, vf10);  // vmul.xyz
                vmula_bc(0x1, vf0, vf2, 0);  // vmulax.w
                vmadda_bc(0x1, vf0, vf2, 1);  // vmadday.w
                vmadd_bc(0x1, vf2, vf0, vf2, 2);  // vmaddz.w
                vrsqrt(vf0, 3, vf2, 3);  // vrsqrt
                vwaitq(ctx);
                vmulq(0xE, vf10, vf10);  // vmulq.xyz
                sqc2(vf10, t0, 0);
                vmove(0xF, vf11, vf10);  // vmove.xyzw
                a3 = addiu(sp, 0x120);
                lqc2(vf10, a3, 0);
                a2 = 0x6A0000;
                a2 = addiu(a2, -15152);  // &0x69C4D0
                sqc2(vf10, a2, 0);  // 0x69C4D0
                v0 = 0x6A0000;
                lwc1(f0, v0, -15152);  // 0x69C4D0
                swc1(f0, s3, 24);
                v0 = 0x6A0000;
                lwc1(f0, v0, -15148);  // 0x69C4D4
                swc1(f0, s3, 28);
                v0 = 0x6A0000;
                lwc1(f0, v0, -15144);  // 0x69C4D8
                swc1(f0, s3, 32);
                vmove(0xF, vf10, vf11);  // vmove.xyzw
                a1 = addiu(sp, 0x190);
                lqc2(vf11, a1, 0);
                vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
                vmove(0xF, vf12, vf10);  // vmove.xyzw
                lqc2(vf10, a3, 0);
                vmove(0xF, vf11, vf10);  // vmove.xyzw
                vadd(0xF, vf10, vf10, vf12);  // vadd.xyzw
                sqc2(vf10, a2, 0);  // 0x69C4D0
                v0 = 0x6A0000;
                lwc1(f0, v0, -15152);  // 0x69C4D0
                swc1(f0, s3, 12);
                v0 = 0x6A0000;
                lwc1(f0, v0, -15148);  // 0x69C4D4
                swc1(f0, s3, 16);
                v0 = 0x6A0000;
                lwc1(f0, v0, -15144);  // 0x69C4D8
                swc1(f0, s3, 20);
                vmove(0xF, vf10, vf12);  // vmove.xyzw
                vsub(0xF, vf11, vf11, vf10);  // vsub.xyzw
                sqc2(vf11, a2, 0);  // 0x69C4D0
                v0 = 0x6A0000;
                lwc1(f0, v0, -15152);  // 0x69C4D0
                swc1(f0, s3, 36);
                v0 = 0x6A0000;
                lwc1(f0, v0, -15148);  // 0x69C4D4
                swc1(f0, s3, 40);
                v0 = 0x6A0000;
                lwc1(f0, v0, -15144);  // 0x69C4D8
                swc1(f0, s3, 44);
                lqc2(vf10, t0, 0);
                a0 = addiu(sp, 0x180);
                lqc2(vf11, a0, 0);
                vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
                vmove(0xF, vf12, vf10);  // vmove.xyzw
                lqc2(vf10, a3, 0);
                vmove(0xF, vf11, vf10);  // vmove.xyzw
                vadd(0xF, vf10, vf10, vf12);  // vadd.xyzw
                sqc2(vf10, a2, 0);  // 0x69C4D0
                v0 = 0x6A0000;
                lwc1(f0, v0, -15152);  // 0x69C4D0
                swc1(f0, s3, 0);
                v0 = 0x6A0000;
                lwc1(f0, v0, -15148);  // 0x69C4D4
                swc1(f0, s3, 4);
                v0 = 0x6A0000;
                lwc1(f0, v0, -15144);  // 0x69C4D8
                swc1(f0, s3, 8);
                vmove(0xF, vf10, vf12);  // vmove.xyzw
                vsub(0xF, vf11, vf11, vf10);  // vsub.xyzw
                sqc2(vf11, a2, 0);  // 0x69C4D0
                v0 = 0x6A0000;
                lwc1(f0, v0, -15152);  // 0x69C4D0
                swc1(f0, s3, 48);
                v0 = 0x6A0000;
                lwc1(f0, v0, -15148);  // 0x69C4D4
                swc1(f0, s3, 52);
                v0 = 0x6A0000;
                lwc1(f0, v0, -15144);  // 0x69C4D8
                swc1(f0, s3, 56);
                v1 = addiu(s3, 60);
                t1 = addiu(sp, 0x130);
                lq(v0, t0, 0);
                sq(v0, t1, 0);
                v0 = addiu(sp, 0x110);
                lq(v0, v0, 0);
                sq(v0, a3, 0);
                lqc2(vf10, a3, 0);
                sqc2(vf10, a2, 0);  // 0x69C4D0
                v0 = 0x6A0000;
                lwc1(f0, v0, -15152);  // 0x69C4D0
                swc1(f0, s3, 84);
                v0 = 0x6A0000;
                lwc1(f0, v0, -15148);  // 0x69C4D4
                swc1(f0, s3, 88);
                v0 = 0x6A0000;
                lwc1(f0, v0, -15144);  // 0x69C4D8
                swc1(f0, s3, 92);
                lqc2(vf10, t0, 0);
                lqc2(vf11, a1, 0);
                vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
                vmove(0xF, vf12, vf10);  // vmove.xyzw
                lqc2(vf10, a3, 0);
                vmove(0xF, vf11, vf10);  // vmove.xyzw
                vadd(0xF, vf10, vf10, vf12);  // vadd.xyzw
                sqc2(vf10, a2, 0);  // 0x69C4D0
                v0 = 0x6A0000;
                lwc1(f0, v0, -15152);  // 0x69C4D0
                swc1(f0, s3, 72);
                v0 = 0x6A0000;
                lwc1(f0, v0, -15148);  // 0x69C4D4
                swc1(f0, s3, 76);
                v0 = 0x6A0000;
                lwc1(f0, v0, -15144);  // 0x69C4D8
                swc1(f0, s3, 80);
                vmove(0xF, vf10, vf12);  // vmove.xyzw
                vsub(0xF, vf11, vf11, vf10);  // vsub.xyzw
                sqc2(vf11, a2, 0);  // 0x69C4D0
                v0 = 0x6A0000;
                lwc1(f0, v0, -15152);  // 0x69C4D0
                swc1(f0, s3, 96);
                v0 = 0x6A0000;
                lwc1(f0, v0, -15148);  // 0x69C4D4
                swc1(f0, s3, 100);
                v0 = 0x6A0000;
                lwc1(f0, v0, -15144);  // 0x69C4D8
                swc1(f0, s3, 104);
                lqc2(vf10, t0, 0);
                lqc2(vf11, a0, 0);
                vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
                vmove(0xF, vf12, vf10);  // vmove.xyzw
                lqc2(vf10, a3, 0);
                vmove(0xF, vf11, vf10);  // vmove.xyzw
                vadd(0xF, vf10, vf10, vf12);  // vadd.xyzw
                sqc2(vf10, a2, 0);  // 0x69C4D0
                v0 = 0x6A0000;
                lwc1(f0, v0, -15152);  // 0x69C4D0
                swc1(f0, s3, 60);
                v0 = 0x6A0000;
                lwc1(f0, v0, -15148);  // 0x69C4D4
                swc1(f0, s3, 64);
                v0 = 0x6A0000;
                lwc1(f0, v0, -15144);  // 0x69C4D8
                swc1(f0, s3, 68);
                vmove(0xF, vf10, vf12);  // vmove.xyzw
                vsub(0xF, vf11, vf11, vf10);  // vsub.xyzw
                sqc2(vf11, a2, 0);  // 0x69C4D0
                v0 = 0x6A0000;
                lwc1(f0, v0, -15152);  // 0x69C4D0
                swc1(f0, s3, 108);
                v0 = 0x6A0000;
                lwc1(f0, v0, -15148);  // 0x69C4D4
                swc1(f0, s3, 112);
                v0 = 0x6A0000;
                lwc1(f0, v0, -15144);  // 0x69C4D8
                swc1(f0, s3, 116);
                s3 = addiu(v1, 60);
                add_s(f30, f30, f28);
                add_s(f29, f29, f28);
                c_le_s(f29, f24);
                if (!cond(ctx)) {
                    // 0x0033753c
                    charge(ctx, 9);
                    sub_s(f29, f29, f24);
                    a0 = 0;
                    jal(ctx, 0x337544u, gen::fn_sub_358030_00358030);
                    mtc1(zero, f2);
                    lwc1(f1, sp, 0xEC);
                    adda_s(f2, f1);
                    msub_s(f0, f22, f0);
                    mul_s(f27, f26, f0);
                }
                // 0x00337560
                charge(ctx, 76);
                swc1(f20, sp, 0xDC);
                mov_s(f12, f30);
                jal(ctx, 0x337568u, gen::fn_sinf_0052e878);
                mul_s(f20, f27, f0);
                lwc1(f0, sp, 0xDC);
                sub_s(f0, f20, f0);
                v0 = addiu(sp, 0x160);
                lqc2(vf10, v0, 0);
                mfc1(v0, f31);
                qmtc2(v0, vf2, false);  // qmtc2
                vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                vmove(0xF, vf12, vf10);  // vmove.xyzw
                v0 = addiu(sp, 0x150);
                lqc2(vf10, v0, 0);
                mfc1(v0, f0);
                qmtc2(v0, vf2, false);  // qmtc2
                vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                vadd(0xF, vf10, vf10, vf12);  // vadd.xyzw
                v0 = addiu(sp, 0xF0);
                sqc2(vf10, v0, 0);
                a0 = 0;
                jal(ctx, 0x3375C0u, gen::fn_sub_358030_00358030);
                lwc1(f1, sp, 0xE8);
                sub_s(f0, f0, f1);
                mul_s(f1, f21, f0);
                lwc1(f0, sp, 0xE4);
                mul_s(f12, f0, f1);
                a0 = addiu(sp, 0x100);
                jal(ctx, 0x3375E0u, gen::fn_sub_358340_00358340);
                v0 = addiu(sp, 0xF0);
                lqc2(vf10, v0, 0);
                vmula_bc(0xF, vf28, vf10, 0);  // vmulax.xyzw
                vmadda_bc(0xF, vf29, vf10, 1);  // vmadday.xyzw
                vmadd_bc(0xF, vf10, vf30, vf10, 2);  // vmaddz.xyzw
                vmove(0xF, vf12, vf10);  // vmove.xyzw
                a0 = addiu(sp, 0x120);
                lqc2(vf11, a0, 0);
                vadd(0xF, vf11, vf11, vf10);  // vadd.xyzw
                v1 = addiu(sp, 0x110);
                sqc2(vf11, v1, 0);
                vmove(0xF, vf10, vf12);  // vmove.xyzw
                vmul(0xE, vf2, vf10, vf10);  // vmul.xyz
                vmula_bc(0x1, vf0, vf2, 0);  // vmulax.w
                vmadda_bc(0x1, vf0, vf2, 1);  // vmadday.w
                vmadd_bc(0x1, vf2, vf0, vf2, 2);  // vmaddz.w
                vrsqrt(vf0, 3, vf2, 3);  // vrsqrt
                vwaitq(ctx);
                vmulq(0xE, vf10, vf10);  // vmulq.xyz
                v0 = addiu(sp, 0x140);
                sqc2(vf10, v0, 0);
                lqc2(vf10, v1, 0);
                lqc2(vf11, a0, 0);
                vsub(0xF, vf10, vf10, vf11);  // vsub.xyzw
                vmul(0xE, vf2, vf10, vf10);  // vmul.xyz
                vmula_bc(0x1, vf0, vf2, 0);  // vmulax.w
                vmadda_bc(0x1, vf0, vf2, 1);  // vmadday.w
                vmadd_bc(0x1, vf2, vf0, vf2, 2);  // vmaddz.w
                vrsqrt(vf0, 3, vf2, 3);  // vrsqrt
                vwaitq(ctx);
                vmulq(0xE, vf10, vf10);  // vmulq.xyz
                v0 = addiu(sp, 0x130);
                lqc2(vf11, v0, 0);
                vmul(0xE, vf2, vf10, vf11);  // vmul.xyz
                vadd_bc(0x8, vf2, vf2, vf2, 1);  // vaddy.x
                vadd_bc(0x8, vf2, vf2, vf2, 2);  // vaddz.x
                qmfc2(v0, vf2, false);  // qmfc2
                mtc1(v0, f1);
                lwc1(f0, sp, 0xE0);
                c_lt_s(f1, f0);
                if (!cond(ctx)) {
                    // 0x003376a4
                    charge(ctx, 3);
                    v1 = addiu(s3, -60);
                    v0 = addiu(sp, 0x170);
                    lqc2(vf12, v0, 0);
                } else {
                    // 0x00337690
                    charge(ctx, 5);
                    v1 = addiu(s3, -12);
                    v0 = addiu(sp, 0x180);
                    lqc2(vf12, v0, 0);
                }
                // 0x003376b0
                charge(ctx, 31);
                v0 = addiu(sp, 0x140);
                lqc2(vf10, v0, 0);
                v0 = addiu(sp, 0x100);
                lqc2(vf11, v0, 0);
                vopmula(0xE, vf10, vf11);  // vopmula.xyz
                vopmsub(0xE, vf10, vf11, vf10);  // vopmsub.xyz
                vmul(0xE, vf2, vf10, vf10);  // vmul.xyz
                vmula_bc(0x1, vf0, vf2, 0);  // vmulax.w
                vmadda_bc(0x1, vf0, vf2, 1);  // vmadday.w
                vmadd_bc(0x1, vf2, vf0, vf2, 2);  // vmaddz.w
                vrsqrt(vf0, 3, vf2, 3);  // vrsqrt
                vwaitq(ctx);
                vmulq(0xE, vf10, vf10);  // vmulq.xyz
                vmove(0xF, vf11, vf12);  // vmove.xyzw
                vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
                lwc1(f0, v1, 0);
                v0 = 0x6A0000;
                swc1(f0, v0, -15152);  // 0x69C4D0
                lwc1(f0, v1, 4);
                v0 = 0x6A0000;
                swc1(f0, v0, -15148);  // 0x69C4D4
                lwc1(f0, v1, 8);
                v0 = 0x6A0000;
                swc1(f0, v0, -15144);  // 0x69C4D8
                v0 = 0x6A0000;
                v0 = addiu(v0, -15152);  // &0x69C4D0
                lqc2(vf11, v0, 0);  // 0x69C4D0
                vadd(0xF, vf10, vf10, vf11);  // vadd.xyzw
                v0 = addiu(sp, 0x120);
                sqc2(vf10, v0, 0);
                s5 = addiu(s5, 1);
            }
            // 0x00337738
            charge(ctx, 9);
            lw(v0, s2, 16);
            lw(s1, v0, 24);
            a0 = s1;
            jal(ctx, 0x337744u, gen::fn_sub_4933D0_004933d0);
            lhu(v1, s2, 0);
            v1 = v1 & 0x4;
            if (v1 != 0) {
                // 0x0033775c
                charge(ctx, 3);
                lhu(v1, s1, 12);
                v1 = v1 | 0x1;
                sh(v1, s1, 12);
            }
        L_00337768:
            charge(ctx, 3);
            lw(v1, s0, 4);
            v1 = addiu(v1, 1);
            sw(v1, s0, 4);
        }
        // 0x00337774
        charge(ctx, 2);
        s4 = addiu(s4, 1);
        s0 = addiu(s0, 12);
    }
    // 0x00337788 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0x1A0);
}

// 0x003377F0 sub_3377F0 -- 612 bytes; frame 0xE0: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// Effect object, draw callback (data-referenced): as sub_335180 for the third effect class.
void sub_3377F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f20{ctx, 20};
    Vf vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11};
    // 0x003377f0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0xE0);
    sd(ra, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s1 = a0;
    lw(v1, a0, 48);
    lw(s4, a0, 52);
    lw(s3, v1, 0);
    lw(a2, a0, 40);
    lw(a3, s4, 52);
    at = slt(a3, a2);
    if (at != 0) {
        // 0x00337834
        charge(ctx, 2);
        if (a3 == 0) {
            goto L_0033783c;
        }
        // 0x00337a2c (the shared epilogue, written out on this path)
        charge(ctx, 10);
        ld(ra, sp, 0x60);
        lq(s4, sp, 0x50);
        lq(s3, sp, 0x40);
        lq(s2, sp, 0x30);
        lq(s1, sp, 0x20);
        lq(s0, sp, 0x10);
        lwc1(f20, sp, 0x0);
        sp = addiu(sp, 0xE0);
        return;
    }
L_0033783c:
    charge(ctx, 43);
    lw(s0, s4, 56);
    a0 = s4;
    a1 = addiu(s4, 36);
    jal(ctx, 0x337848u, gen::fn_sub_32A120_0032a120);
    v1 = v0;
    lw(v0, s1, 36);
    sw(v0, sp, 0xD8);
    v0 = addiu(sp, 0xD8);
    lwc1(f20, gp, -32420);  // 0x7CAE4C
    lw(v0, v0, 0);
    pextlb(v0, zero, v0);
    pextlh(v0, zero, v0);
    qmtc2(v0, vf10, false);  // qmtc2
    vitof0(0xF, vf10, vf10);  // vitof0.xyzw
    mfc1(v0, f20);
    qmtc2(v0, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    vmove(0xF, vf11, vf10);  // vmove.xyzw
    sw(v1, sp, 0xD4);
    v0 = addiu(sp, 0xD4);
    lw(v0, v0, 0);
    pextlb(v0, zero, v0);
    pextlh(v0, zero, v0);
    qmtc2(v0, vf10, false);  // qmtc2
    vitof0(0xF, vf10, vf10);  // vitof0.xyzw
    mfc1(v0, f20);
    qmtc2(v0, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
    v0 = addiu(sp, 0xB0);
    sqc2(vf10, v0, 0);
    a0 = addiu(sp, 0x70);
    a1 = s1;
    a2 = 0;
    lwc1(f12, s1, 32);
    jal(ctx, 0x3378D4u, gen::fn_sub_323920_00323920);
    s2 = 0;
    for (;;) {
        // 0x00337a20
        charge(ctx, 3);
        v1 = slt(s2, s0);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003378e8
        charge(ctx, 3);
        lw(v1, s3, 4);
        if (i64(v1) > 0) {
            // 0x003378f4
            charge(ctx, 35);
            lw(s1, s3, 0);
            lw(a0, s1, 12);
            a1 = addiu(sp, 0x70);
            a2 = 0;
            jal(ctx, 0x337904u, gen::fn_sub_4CB7F0_004cb7f0);
            lw(v0, s3, 8);
            sw(v0, sp, 0xD0);
            v0 = addiu(sp, 0xD0);
            lw(v0, v0, 0);
            pextlb(v0, zero, v0);
            pextlh(v0, zero, v0);
            qmtc2(v0, vf10, false);  // qmtc2
            vitof0(0xF, vf10, vf10);  // vitof0.xyzw
            mfc1(v0, f20);
            qmtc2(v0, vf2, false);  // qmtc2
            vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
            v0 = addiu(sp, 0xB0);
            lqc2(vf11, v0, 0);
            vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
            v0 = 0x437F0000;
            qmtc2(v0, vf2, false);  // qmtc2
            vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
            vftoi0(0xF, vf10, vf10);  // vftoi0.xyzw
            qmfc2(v0, vf10, false);  // qmfc2
            ppach(v0, zero, v0);
            ppacb(v0, zero, v0);
            sw(v0, sp, 0xCC);
            lw(v0, sp, 0xCC);
            sw(v0, sp, 0xDC);
            lbu(v0, sp, 0xDF);
            a3 = 255;
            if (v0 == a3) {
                // 0x003379ac
                charge(ctx, 12);
                v0 = 254;
                sb(v0, sp, 0xDF);
                lw(a2, s1, 20);
                lbu(a1, sp, 0xDC);
                lbu(a0, sp, 0xDD);
                lbu(v1, sp, 0xDE);
                lbu(v0, sp, 0xDF);
                sb(a1, a2, 4);
                sb(a0, a2, 5);
                sb(v1, a2, 6);
                sb(v0, a2, 7);
                sb(a3, sp, 0xDF);
            } else {
                // 0x00337980
                charge(ctx, 11);
                lw(a2, s1, 20);
                lbu(a1, sp, 0xDC);
                lbu(a0, sp, 0xDD);
                lbu(v1, sp, 0xDE);
                lbu(v0, sp, 0xDF);
                sb(a1, a2, 4);
                sb(a0, a2, 5);
                sb(v1, a2, 6);
                sb(v0, a2, 7);
            }
            // 0x003379dc
            charge(ctx, 3);
            lbu(v0, s4, 92);
            if (v0 == 0) {
                // 0x003379fc
                charge(ctx, 3);
                lhu(v0, s1, 0);
                v0 = v0 & 0xFFFE;
                sh(v0, s1, 0);
            } else {
                // 0x003379e8
                charge(ctx, 5);
                lhu(v0, s1, 0);
                v0 = v0 | 0x1;
                sh(v0, s1, 0);
            }
            // 0x00337a08
            charge(ctx, 4);
            lhu(a1, s4, 40);
            a0 = s1;
            jal(ctx, 0x337A10u, gen::fn_sub_323860_00323860);
        }
        // 0x00337a18
        charge(ctx, 2);
        s2 = addiu(s2, 1);
        s3 = addiu(s3, 12);
    }
    // 0x00337a2c (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0xE0);
}

// 0x00338530 sub_338530 -- 152 bytes; frame 0x10: ra sp+0x0
// Effect object callback (data-referenced): sub_3395D0.
void sub_338530(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00338530
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(t0, a0, 60);
    lw(v1, t0, 8);
    lbu(v0, gp, -18345);  // 0x7CE547
    a3 = 255;
    if (v0 == a3) {
        // 0x0033857c
        charge(ctx, 12);
        v0 = 254;
        sb(v0, gp, -18345);  // 0x7CE547
        lw(a2, v1, 20);
        lbu(a1, gp, -18348);  // 0x7CE544
        lbu(a0, gp, -18347);  // 0x7CE545
        lbu(v1, gp, -18346);  // 0x7CE546
        lbu(v0, gp, -18345);  // 0x7CE547
        sb(a1, a2, 4);
        sb(a0, a2, 5);
        sb(v1, a2, 6);
        sb(v0, a2, 7);
        sb(a3, gp, -18345);  // 0x7CE547
    } else {
        // 0x00338550
        charge(ctx, 11);
        lw(a2, v1, 20);
        lbu(a1, gp, -18348);  // 0x7CE544
        lbu(a0, gp, -18347);  // 0x7CE545
        lbu(v1, gp, -18346);  // 0x7CE546
        lbu(v0, gp, -18345);  // 0x7CE547
        sb(a1, a2, 4);
        sb(a0, a2, 5);
        sb(v1, a2, 6);
        sb(v0, a2, 7);
    }
    // 0x003385ac
    charge(ctx, 7);
    lw(a0, t0, 4);
    jal(ctx, 0x3385B0u, gen::fn_sub_3395D0_003395d0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003385D0 sub_3385D0 -- 412 bytes; frame 0xA0: ra sp+0x90, s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// Effect object init callback (data-referenced): copies the template (memcpy), sub_3393D0, sub_3233A0, sub_358030 and
// one call through a function pointer.
void sub_3385D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f20{ctx, 20};
    // 0x003385d0
    enter(ctx, 16);  // entry check point + this block's cycles
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
    swc1(f20, sp, 0x0);
    s5 = a0;
    lw(v0, a0, 56);
    at = sltiu(v0, 3);
    if (at != 0) {
        // 0x00338610
        charge(ctx, 2);
        v0 = 3;
        sw(v0, s5, 56);
    }
    // 0x00338618
    charge(ctx, 46);
    lw(s6, s5, 56);
    s0 = sll(s6, 2);
    a0 = addiu(s0, 16);
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x338630u, v0.u());
    s3 = v0;
    s4 = addu(s3, s0);
    sw(s3, s4, 0);
    sw(v0, s4, 12);
    a0 = addiu(s5, 92);
    a1 = s5;
    a2 = 92;
    jal(ctx, 0x338654u, gen::fn_memcpy_00521250);
    a0 = 1;
    a1 = addiu(s5, 92);
    jal(ctx, 0x338664u, gen::fn_sub_3393D0_003393d0);
    sw(v0, s4, 4);
    a0 = s6 & 0xFFFF;
    a1 = 2;
    a2 = 4;
    a3 = 0x6A0000;
    a3 = addiu(a3, -17072);  // &0x69BD50
    t0 = 72;
    jal(ctx, 0x338688u, gen::fn_sub_3233A0_003233a0);
    sw(v0, s4, 8);
    lw(v0, v0, 16);
    lw(v0, v0, 24);
    lw(s1, v0, 48);
    lw(s0, s5, 68);
    lw(a0, s5, 72);
    s2 = 0;
    v1 = s0 ^ a0;
    v0 = lui(0xFEFE);
    v0 = v0 | 0xFEFE;
    v0 = v1 & v0;
    v1 = srl(v0, 1);
    v0 = s0 & a0;
    s7 = addu(v0, v1);
    for (;;) {
        // 0x00338728
        charge(ctx, 3);
        v0 = sltu(s2, s6);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003386d0
        charge(ctx, 22);
        sw(s0, s1, 0);
        sw(s0, s1, 4);
        sw(s7, s1, 8);
        sw(s0, s1, 12);
        lwc1(f20, s5, 204);
        a0 = 0;
        jal(ctx, 0x3386E8u, gen::fn_sub_358030_00358030);
        v0 = 0x3F800000;
        mtc1(v0, f1);
        sub_s(f2, f1, f20);
        mtc1(zero, f1);
        adda_s(f1, f2);
        madd_s(f1, f20, f0);
        lwc1(f0, s5, 200);
        mul_s(f0, f0, f1);
        swc1(f0, s3, 0);
        s2 = addiu(s2, 1);
        s1 = addiu(s1, 16);
        s3 = addiu(s3, 4);
    }
    // 0x00338734
    charge(ctx, 14);
    v0 = s4;
    ld(ra, sp, 0x90);
    lq(s7, sp, 0x80);
    lq(s6, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// 0x00338770 sub_338770 -- 80 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Effect object, release callback (data-referenced): sub_3237C0, sub_339530, then the RwFree slot.
void sub_338770(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00338770
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, a0, 8);
    jal(ctx, 0x338784u, gen::fn_sub_3237C0_003237c0);
    lw(a0, s0, 4);
    jal(ctx, 0x338790u, gen::fn_sub_339530_00339530);
    lw(a0, s0, 12);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x3387A4u, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003387C0 sub_3387C0 -- 768 bytes; frame 0x90: ra sp+0x80, s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// Effect object geometry update (data-referenced): sub_339620 inside geometryLock / sub_4933D0.
void sub_3387C0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f20{ctx, 20};
    Vf vf0{ctx, 0}, vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11}, vf12{ctx, 12};
    // 0x003387c0
    enter(ctx, 21);  // entry check point + this block's cycles
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
    lw(v1, a0, 60);
    lw(a1, v1, 4);
    lw(s1, a1, 60);
    lw(s3, a0, 64);
    lw(s0, v1, 8);
    lw(s2, v1, 0);
    lw(s5, a0, 52);
    lw(s4, s3, 52);
    at = slt(s4, s5);
    if (at != 0) {
        // 0x00338814
        charge(ctx, 2);
        if (s4 == 0) {
            goto L_0033881c;
        }
        // 0x00338a90 (the shared epilogue, written out on this path)
        charge(ctx, 12);
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
        return;
    }
L_0033881c:
    charge(ctx, 36);
    a0 = a1;
    jal(ctx, 0x338820u, gen::fn_sub_339620_00339620);
    mtc1(s5, f0);
    cvt_s_w(f1, f0);
    mtc1(s4, f0);
    cvt_s_w(f0, f0);
    div_s(f20, f1, f0);
    lw(v0, s0, 16);
    lw(a0, v0, 24);
    a1 = 2;
    jal(ctx, 0x338850u, gen::fn_geometryLock_00493370);
    lw(v0, s1, 0);
    lw(v0, v0, 16);
    lw(a0, v0, 24);
    a1 = 2;
    jal(ctx, 0x338868u, gen::fn_geometryLock_00493370);
    lw(a1, s3, 56);
    lw(a0, s1, 0);
    lh(v0, a0, 8);
    v0 = addiu(v0, -1);
    lw(v1, s0, 16);
    lw(v1, v1, 24);
    lw(v1, v1, 92);
    lw(a3, v1, 20);
    lw(v1, a0, 16);
    lw(v1, v1, 24);
    lw(v1, v1, 92);
    lw(a2, v1, 20);
    lbu(v1, s3, 196);
    if (v1 == 0) {
        // 0x003388ac
        charge(ctx, 21);
        t0 = 0;
        a0 = si(-72);
        s5 = 0x6A0000;
        s4 = 0x6A0000;
        t9 = 0x6A0000;
        v1 = 0x6A0000;
        v1 = addiu(v1, -15152);  // &0x69C4D0
        t8 = 0x6A0000;
        s3 = 0x6A0000;
        t7 = 0x6A0000;
        t6 = 0x6A0000;
        t5 = 0x6A0000;
        t4 = 0x6A0000;
        t3 = 0x6A0000;
        t2 = 0x6A0000;
        t1 = 0x6A0000;
        s6 = sll(v0, 1);
        v0 = addu(s6, v0);
        v0 = sll(v0, 2);
        for (;;) {
            // 0x00338a20
            charge(ctx, 3);
            s6 = sltu(t0, a1);
            if (s6 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00338900
            charge(ctx, 52);
            lwc1(f0, a2, 12);
            swc1(f0, s5, -15152);
            lwc1(f0, a2, 16);
            swc1(f0, s4, -15148);
            lwc1(f0, a2, 20);
            swc1(f0, t9, -15144);
            lqc2(vf10, v1, 0);
            vmove(0xF, vf12, vf10);  // vmove.xyzw
            lwc1(f0, a2, 36);
            swc1(f0, t8, -15152);
            lwc1(f0, a2, 40);
            swc1(f0, s3, -15148);
            lwc1(f0, a2, 44);
            swc1(f0, t7, -15144);
            lqc2(vf11, v1, 0);
            sqc2(vf10, v1, 0);
            lwc1(f0, t6, -15152);
            swc1(f0, a3, 24);
            lwc1(f0, t5, -15148);
            swc1(f0, a3, 28);
            lwc1(f0, t4, -15144);
            swc1(f0, a3, 32);
            vsub(0xF, vf10, vf10, vf11);  // vsub.xyzw
            vmul(0xE, vf2, vf10, vf10);  // vmul.xyz
            vmula_bc(0x1, vf0, vf2, 0);  // vmulax.w
            vmadda_bc(0x1, vf0, vf2, 1);  // vmadday.w
            vmadd_bc(0x1, vf2, vf0, vf2, 2);  // vmaddz.w
            vrsqrt(vf0, 3, vf2, 3);  // vrsqrt
            vwaitq(ctx);
            vmulq(0xE, vf10, vf10);  // vmulq.xyz
            lwc1(f0, s2, 0);
            mul_s(f0, f0, f20);
            mfc1(s6, f0);
            qmtc2(s6, vf2, false);  // qmtc2
            vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
            vadd(0xF, vf10, vf10, vf12);  // vadd.xyzw
            sqc2(vf10, v1, 0);
            lwc1(f0, t3, -15152);
            swc1(f0, a3, 0);
            lwc1(f0, t2, -15148);
            swc1(f0, a3, 4);
            lwc1(f0, t1, -15144);
            swc1(f0, a3, 8);
            lwc1(f2, a2, 60);
            lwc1(f1, a2, 64);
            lwc1(f0, a2, 68);
            swc1(f2, a3, 12);
            swc1(f1, a3, 16);
            swc1(f0, a3, 20);
            if (t0 != 0) {
                // 0x003389f8
                charge(ctx, 6);
                lwc1(f2, a2, -36);
                lwc1(f1, a2, -32);
                lwc1(f0, a2, -28);
                swc1(f2, a3, 36);
                swc1(f1, a3, 40);
                swc1(f0, a3, 44);
            } else {
                // 0x003389d0
                charge(ctx, 10);
                s6 = addu(a2, v0);
                s6 = addu(s6, a0);
                lwc1(f2, s6, 0);
                lwc1(f1, s6, 4);
                lwc1(f0, s6, 8);
                swc1(f2, a3, 36);
                swc1(f1, a3, 40);
                swc1(f0, a3, 44);
            }
            // 0x00338a10
            charge(ctx, 4);
            t0 = addiu(t0, 1);
            a3 = addiu(a3, 48);
            a2 = addiu(a2, 48);
            s2 = addiu(s2, 4);
        }
    }
    // 0x00338a2c
    charge(ctx, 10);
    lw(s2, s1, 0);
    lw(v0, s2, 16);
    lw(s1, v0, 24);
    a0 = s1;
    jal(ctx, 0x338A3Cu, gen::fn_sub_4933D0_004933d0);
    lhu(v0, s2, 0);
    v0 = v0 & 0x4;
    if (v0 != 0) {
        // 0x00338a54
        charge(ctx, 3);
        lhu(v0, s1, 12);
        v0 = v0 | 0x1;
        sh(v0, s1, 12);
    }
    // 0x00338a60
    charge(ctx, 9);
    lw(v0, s0, 16);
    lw(s1, v0, 24);
    a0 = s1;
    jal(ctx, 0x338A6Cu, gen::fn_sub_4933D0_004933d0);
    lhu(v1, s0, 0);
    v1 = v1 & 0x4;
    if (v1 != 0) {
        // 0x00338a84
        charge(ctx, 3);
        lhu(v1, s1, 12);
        v1 = v1 | 0x1;
        sh(v1, s1, 12);
    }
    // 0x00338a90 (the shared epilogue, written out on this path)
    charge(ctx, 12);
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

// 0x00338AC0 sub_338AC0 -- 532 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Effect object, draw callback (data-referenced): sub_32A120, sub_339680, sub_3238D0, sub_323860.
void sub_338AC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    Vf vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11};
    // 0x00338ac0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    lw(s0, a0, 60);
    lw(s2, a0, 64);
    lw(s1, s0, 8);
    lw(a2, a0, 52);
    lw(a3, s2, 52);
    at = sltu(a3, a2);
    if (at != 0) {
        // 0x00338afc
        charge(ctx, 2);
        if (a3 == 0) {
            goto L_00338b04;
        }
        // 0x00338cb4 (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(ra, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x60);
        return;
    }
L_00338b04:
    charge(ctx, 45);
    a0 = s2;
    a1 = addiu(s2, 36);
    jal(ctx, 0x338B0Cu, gen::fn_sub_32A120_0032a120);
    v1 = v0;
    lw(v0, s3, 48);
    sw(v0, sp, 0x58);
    v0 = addiu(sp, 0x58);
    lwc1(f0, gp, -32420);  // 0x7CAE4C
    lw(v0, v0, 0);
    pextlb(v0, zero, v0);
    pextlh(v0, zero, v0);
    qmtc2(v0, vf10, false);  // qmtc2
    vitof0(0xF, vf10, vf10);  // vitof0.xyzw
    mfc1(v0, f0);
    qmtc2(v0, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    vmove(0xF, vf11, vf10);  // vmove.xyzw
    sw(v1, sp, 0x54);
    v0 = addiu(sp, 0x54);
    lw(v0, v0, 0);
    pextlb(v0, zero, v0);
    pextlh(v0, zero, v0);
    qmtc2(v0, vf10, false);  // qmtc2
    vitof0(0xF, vf10, vf10);  // vitof0.xyzw
    mfc1(v1, f0);
    qmtc2(v1, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
    v1 = 0x437F0000;
    qmtc2(v1, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    vftoi0(0xF, vf10, vf10);  // vftoi0.xyzw
    qmfc2(v1, vf10, false);  // qmfc2
    ppach(v1, zero, v1);
    ppacb(v1, zero, v1);
    sw(v1, sp, 0x50);
    lw(v1, sp, 0x50);
    sw(v1, sp, 0x5C);
    lbu(v1, sp, 0x5F);
    t0 = 255;
    if (v1 == t0) {
        // 0x00338be4
        charge(ctx, 12);
        v1 = 254;
        sb(v1, sp, 0x5F);
        lw(a3, s1, 20);
        lbu(a2, sp, 0x5C);
        lbu(a1, sp, 0x5D);
        lbu(a0, sp, 0x5E);
        lbu(v1, sp, 0x5F);
        sb(a2, a3, 4);
        sb(a1, a3, 5);
        sb(a0, a3, 6);
        sb(v1, a3, 7);
        sb(t0, sp, 0x5F);
    } else {
        // 0x00338bb8
        charge(ctx, 11);
        lw(a3, s1, 20);
        lbu(a2, sp, 0x5C);
        lbu(a1, sp, 0x5D);
        lbu(a0, sp, 0x5E);
        lbu(v1, sp, 0x5F);
        sb(a2, a3, 4);
        sb(a1, a3, 5);
        sb(a0, a3, 6);
        sb(v1, a3, 7);
    }
    // 0x00338c14
    charge(ctx, 4);
    lw(v1, s1, 20);
    lbu(v1, v1, 7);
    if (v1 != 0) {
        // 0x00338c24
        charge(ctx, 24);
        lw(v1, s3, 48);
        lw(v0, s0, 4);
        sw(v1, v0, 48);
        lw(v1, s0, 4);
        lq(v0, s3, 32);
        sq(v0, v1, 32);
        lw(v1, s0, 4);
        lq(v0, s3, 0);
        sq(v0, v1, 0);
        lw(v1, s0, 4);
        lq(v0, s3, 16);
        sq(v0, v1, 16);
        lw(a0, s0, 4);
        jal(ctx, 0x338C58u, gen::fn_sub_339680_00339680);
        a0 = s1;
        a1 = s3;
        a2 = addiu(s3, 16);
        a3 = addiu(s3, 32);
        jal(ctx, 0x338C70u, gen::fn_sub_3238D0_003238d0);
        lbu(v0, s2, 60);
        if (v0 == 0) {
            // 0x00338c98
            charge(ctx, 3);
            lhu(v0, s1, 0);
            v0 = v0 & 0xFFFE;
            sh(v0, s1, 0);
        } else {
            // 0x00338c84
            charge(ctx, 5);
            lhu(v0, s1, 0);
            v0 = v0 | 0x1;
            sh(v0, s1, 0);
        }
        // 0x00338ca4
        charge(ctx, 4);
        lhu(a1, s2, 40);
        a0 = s1;
        jal(ctx, 0x338CACu, gen::fn_sub_323860_00323860);
    }
    // 0x00338cb4 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00349FD0 sub_349FD0 -- 508 bytes; frame 0x90: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Effect controller callback (data-referenced): sub_32A540 / sub_329BA0 / sub_32A120 around sub_349090.
void sub_349FD0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    Vf vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11};
    // 0x00349fd0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    lw(s5, a0, 32);
    lw(s3, a0, 36);
    s2 = addiu(s3, 192);
    lw(s0, s3, 184);
    if (s0 != 0) {
        // 0x0034a018
        charge(ctx, 1);
        lw(s1, s4, 28);
    } else {
        // 0x0034a00c
        charge(ctx, 3);
        s1 = 0;
    }
    // 0x0034a01c
    charge(ctx, 3);
    v1 = slt(s0, s1);
    if (v1 != 0) {
        // 0x0034a1a0
        charge(ctx, 1);
        sw(zero, s2, 12);
    } else {
        // 0x0034a028
        charge(ctx, 8);
        a0 = addiu(s3, 140);
        a1 = s1;
        a2 = s0;
        jal(ctx, 0x34A034u, gen::fn_sub_32A540_0032a540);
        lbu(v0, s3, 188);
        if (v0 == 0) {
            // 0x0034a064
            charge(ctx, 12);
            lwc1(f1, s4, 20);
            mul_s(f12, f0, f1);
            lqc2(vf10, s4, 0);
            jal(ctx, 0x34A070u, gen::fn_sub_329BA0_00329ba0);
            swc1(f0, s2, 36);
            v0 = addiu(sp, 0x70);
            sqc2(vf10, v0, 0);
            lwc1(f0, sp, 0x70);
            swc1(f0, s2, 28);
            lwc1(f0, sp, 0x74);
            swc1(f0, s2, 32);
        } else {
            // 0x0034a048
            charge(ctx, 7);
            v0 = 0x43A00000;
            sw(v0, s2, 28);
            v0 = 0x43600000;
            sw(v0, s2, 32);
            swc1(f0, s2, 36);
        }
        // 0x0034a094
        charge(ctx, 67);
        a0 = s3;
        a1 = addiu(s3, 36);
        a2 = s1;
        a3 = s0;
        jal(ctx, 0x34A0A4u, gen::fn_sub_32A120_0032a120);
        v1 = v0;
        lw(v0, s4, 16);
        sw(v0, sp, 0x8C);
        v0 = addiu(sp, 0x8C);
        lwc1(f0, gp, -32420);  // 0x7CAE4C
        lw(v0, v0, 0);
        pextlb(v0, zero, v0);
        pextlh(v0, zero, v0);
        qmtc2(v0, vf10, false);  // qmtc2
        vitof0(0xF, vf10, vf10);  // vitof0.xyzw
        mfc1(v0, f0);
        qmtc2(v0, vf2, false);  // qmtc2
        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
        vmove(0xF, vf11, vf10);  // vmove.xyzw
        sw(v1, sp, 0x88);
        v0 = addiu(sp, 0x88);
        lw(v0, v0, 0);
        pextlb(v0, zero, v0);
        pextlh(v0, zero, v0);
        qmtc2(v0, vf10, false);  // qmtc2
        vitof0(0xF, vf10, vf10);  // vitof0.xyzw
        mfc1(v0, f0);
        qmtc2(v0, vf2, false);  // qmtc2
        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
        vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
        v0 = 0x437F0000;
        qmtc2(v0, vf2, false);  // qmtc2
        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
        vftoi0(0xF, vf10, vf10);  // vftoi0.xyzw
        qmfc2(v0, vf10, false);  // qmfc2
        ppach(v0, zero, v0);
        ppacb(v0, zero, v0);
        sw(v0, sp, 0x84);
        lw(v0, sp, 0x84);
        sw(v0, s2, 12);
        a0 = addiu(s3, 52);
        a1 = s1;
        a2 = s0;
        jal(ctx, 0x34A14Cu, gen::fn_sub_32A540_0032a540);
        lwc1(f1, gp, -32592);  // 0x7CADA0
        mul_s(f0, f1, f0);
        swc1(f0, s2, 24);
        a0 = addiu(s3, 96);
        a1 = s1;
        a2 = s0;
        jal(ctx, 0x34A16Cu, gen::fn_sub_32A540_0032a540);
        lwc1(f1, gp, -32592);  // 0x7CADA0
        mul_s(f0, f1, f0);
        swc1(f0, s2, 20);
        lw(v0, s3, 40);
        sw(v0, s2, 16);
        a0 = s2;
        a1 = s5;
        jal(ctx, 0x34A190u, gen::fn_sub_349090_00349090);
    }
    // 0x0034a1a4 (the shared epilogue, written out on this path)
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

// 0x0034A370 sub_34A370 -- 532 bytes; frame 0x90: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Effect controller callback (data-referenced): as sub_349FD0 around sub_349620.
void sub_34A370(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    Vf vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11};
    // 0x0034a370
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    lw(s5, a0, 32);
    lw(s3, a0, 36);
    s2 = addiu(s3, 192);
    lw(s0, s3, 184);
    if (s0 != 0) {
        // 0x0034a3b8
        charge(ctx, 1);
        lw(s1, s4, 28);
    } else {
        // 0x0034a3ac
        charge(ctx, 3);
        s1 = 0;
    }
    // 0x0034a3bc
    charge(ctx, 3);
    v1 = slt(s0, s1);
    if (v1 != 0) {
        // 0x0034a558
        charge(ctx, 1);
        sw(zero, s2, 12);
    } else {
        // 0x0034a3c8
        charge(ctx, 8);
        a0 = addiu(s3, 140);
        a1 = s1;
        a2 = s0;
        jal(ctx, 0x34A3D4u, gen::fn_sub_32A540_0032a540);
        lbu(v0, s3, 188);
        if (v0 == 0) {
            // 0x0034a410
            charge(ctx, 15);
            lwc1(f1, s4, 20);
            mul_s(f12, f0, f1);
            lqc2(vf10, s4, 0);
            jal(ctx, 0x34A41Cu, gen::fn_sub_329BA0_00329ba0);
            cvt_w_s(f0, f0);
            mfc1(v0, f0);
            sw(v0, s2, 40);
            v0 = addiu(sp, 0x70);
            sqc2(vf10, v0, 0);
            lwc1(f0, sp, 0x70);
            swc1(f0, s2, 32);
            lwc1(f0, sp, 0x74);
            swc1(f0, s2, 36);
        } else {
            // 0x0034a3e8
            charge(ctx, 10);
            v0 = 0x43A00000;
            sw(v0, s2, 32);
            v0 = 0x43600000;
            sw(v0, s2, 36);
            cvt_w_s(f0, f0);
            mfc1(v0, f0);
            sw(v0, s2, 40);
        }
        // 0x0034a44c
        charge(ctx, 67);
        a0 = s3;
        a1 = addiu(s3, 36);
        a2 = s1;
        a3 = s0;
        jal(ctx, 0x34A45Cu, gen::fn_sub_32A120_0032a120);
        v1 = v0;
        lw(v0, s4, 16);
        sw(v0, sp, 0x8C);
        v0 = addiu(sp, 0x8C);
        lwc1(f0, gp, -32420);  // 0x7CAE4C
        lw(v0, v0, 0);
        pextlb(v0, zero, v0);
        pextlh(v0, zero, v0);
        qmtc2(v0, vf10, false);  // qmtc2
        vitof0(0xF, vf10, vf10);  // vitof0.xyzw
        mfc1(v0, f0);
        qmtc2(v0, vf2, false);  // qmtc2
        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
        vmove(0xF, vf11, vf10);  // vmove.xyzw
        sw(v1, sp, 0x88);
        v0 = addiu(sp, 0x88);
        lw(v0, v0, 0);
        pextlb(v0, zero, v0);
        pextlh(v0, zero, v0);
        qmtc2(v0, vf10, false);  // qmtc2
        vitof0(0xF, vf10, vf10);  // vitof0.xyzw
        mfc1(v0, f0);
        qmtc2(v0, vf2, false);  // qmtc2
        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
        vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
        v0 = 0x437F0000;
        qmtc2(v0, vf2, false);  // qmtc2
        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
        vftoi0(0xF, vf10, vf10);  // vftoi0.xyzw
        qmfc2(v0, vf10, false);  // qmfc2
        ppach(v0, zero, v0);
        ppacb(v0, zero, v0);
        sw(v0, sp, 0x84);
        lw(v0, sp, 0x84);
        sw(v0, s2, 12);
        a0 = addiu(s3, 52);
        a1 = s1;
        a2 = s0;
        jal(ctx, 0x34A504u, gen::fn_sub_32A540_0032a540);
        lwc1(f1, gp, -32592);  // 0x7CADA0
        mul_s(f0, f1, f0);
        swc1(f0, s2, 28);
        a0 = addiu(s3, 96);
        a1 = s1;
        a2 = s0;
        jal(ctx, 0x34A524u, gen::fn_sub_32A540_0032a540);
        lwc1(f1, gp, -32592);  // 0x7CADA0
        mul_s(f0, f1, f0);
        swc1(f0, s2, 20);
        lw(v0, s3, 40);
        sw(v0, s2, 16);
        a0 = s2;
        a1 = s5;
        jal(ctx, 0x34A548u, gen::fn_sub_349620_00349620);
    }
    // 0x0034a55c (the shared epilogue, written out on this path)
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

// 0x003A4B90 sub_3A4B90 -- 328 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// "itfMesManager.c": opens a dialogue line in a message window: message entry, pushed arguments, font style
// (frSetMessageFontStyle), the line and its maximum width.
void sub_3A4B90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a4b90
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    s0 = a2;
    v0 = sll(a0, 1);
    v0 = addu(v0, a0);
    v0 = sll(v0, 2);
    v0 = addu(v0, a0);
    v1 = sll(v0, 2);
    v0 = 0x960000;
    v0 = addiu(v0, -24852);  // &0x959EEC
    v0 = addu(v0, v1);
    lw(s2, v0, 0);
    if (s2 == 0) {
        // 0x003a4bd8
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 6768);  // "itfMesManager.c"
        a1 = 3326;
        jal(ctx, 0x3A4BE4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003a4bec
    charge(ctx, 8);
    a0 = s2;
    a1 = s1;
    jal(ctx, 0x3A4BF4u, gen::fn_itfMesMngGetMessageEntry_003a50e0);
    s1 = v0;
    lw(v0, v0, 0);
    if (v0 != 0) {
        // 0x003a4c0c
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 6768);  // "itfMesManager.c"
        a1 = 3331;
        jal(ctx, 0x3A4C18u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003a4c20
    charge(ctx, 4);
    lw(s1, s1, 4);
    lh(v0, s1, 24);
    if (v0 != 0) {
        // 0x003a4c3c
        charge(ctx, 6);
        a0 = addiu(s2, 212);
        jal(ctx, 0x3A4C40u, gen::fn_itfMesMngPushMessageArgs_003a5fd0);
        lw(a0, s2, 8);
        if (a0 != 0) {
            // 0x003a4c54
            charge(ctx, 2);
            jal(ctx, 0x3A4C54u, gen::fn_frSetMessageFontStyle_003b19a0);
        }
        // 0x003a4c5c
        charge(ctx, 6);
        a0 = s1;
        a1 = s0;
        jal(ctx, 0x3A4C64u, gen::fn_itfMesMngGetDialogueLine_003a5940);
        if (v0 != 0) {
            // 0x003a4c80
            charge(ctx, 15);
            a0 = 0;
            a1 = 0;
            a2 = v0;
            a3 = 0;
            jal(ctx, 0x3A4C90u, gen::fn_sub_3B2900_003b2900);
            s0 = v0;
            a0 = s0;
            jal(ctx, 0x3A4CA0u, gen::fn_itfMesMngTextGetMaxLineWidth_003a6460);
            s1 = v0;
            a0 = s0;
            jal(ctx, 0x3A4CB0u, gen::fn_sub_3B0170_003b0170);
            v0 = s1;
        } else {
            // 0x003a4c74
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x003a4c30
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003a4cbc (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003B83D0 sub_3B83D0 -- 160 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Field UI element by handle (sub_3B5D10 resolves the handle): sub_3B5D50 on it.
void sub_3B83D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b83d0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = 1;
    for (;;) {
        // 0x003b8448
        charge(ctx, 3);
        v1 = slti(s1, 22);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003b83f4
        charge(ctx, 6);
        a0 = s1;
        jal(ctx, 0x3B83F8u, gen::fn_sub_3B5D50_003b5d50);
        s0 = v0;
        for (;;) {
            // 0x003b843c
            charge(ctx, 2);
            if (s0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003b840c
            charge(ctx, 5);
            lhu(a0, s0, 0);
            jal(ctx, 0x3B8410u, gen::fn_sub_3B5D10_003b5d10);
            if (v0 != 0) {
                // 0x003b8420
                charge(ctx, 2);
                if (v0 != 0) {
                    // 0x003b8428
                    charge(ctx, 4);
                    lw(v1, v0, 40);
                    v1 = v1 | 0x20;
                    sw(v1, v0, 40);
                    sw(s2, v0, 244);
                }
            }
            // 0x003b8438
            charge(ctx, 1);
            lw(s0, s0, 248);
        }
        // 0x003b8444
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x003b8454
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003B8470 sub_3B8470 -- 200 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Field UI element by handle: sub_3B7460 on the element.
void sub_3B8470(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x003b8470
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    jal(ctx, 0x3B8484u, gen::fn_sub_3B5D10_003b5d10);
    s0 = v0;
    if (s0 != 0) {
        // 0x003b84a4
        charge(ctx, 5);
        a0 = s1;
        jal(ctx, 0x3B84A8u, gen::fn_sub_3B5D10_003b5d10);
        if (v0 != 0) {
            // 0x003b84c4
            charge(ctx, 2);
            if (s0 != 0) {
                // 0x003b84d8
                charge(ctx, 2);
                if (v0 != 0) {
                    // 0x003b84ec
                    charge(ctx, 13);
                    a1 = addiu(s0, 4);
                    lwc1(f2, v0, 4);
                    lwc1(f1, v0, 8);
                    lwc1(f0, v0, 12);
                    swc1(f2, s0, 4);
                    swc1(f1, s0, 8);
                    swc1(f0, s0, 12);
                    a0 = s0;
                    a2 = 0;
                    a3 = 0;
                    jal(ctx, 0x3B8514u, gen::fn_sub_3B7460_003b7460);
                    v0 = 1;
                } else {
                    // 0x003b84e0
                    charge(ctx, 3);
                    v0 = 0;
                }
            } else {
                // 0x003b84cc
                charge(ctx, 3);
                v0 = 0;
            }
        } else {
            // 0x003b84b8
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x003b8498
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003b8520 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003B8730 sub_3B8730 -- 180 bytes; frame 0x30: ra sp+0x20, s0 sp+0x10 (sq), f20 sp+0x0
// Field UI element by handle: starts a move -- sets bit 0 and clears bit 6 of +40, copies the position +4..+12 to the
// start +44..+52 and takes the target from the point a1.
void sub_3B8730(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f20{ctx, 20};
    // 0x003b8730
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s0 = a1;
    mov_s(f20, f12);
    jal(ctx, 0x3B8748u, gen::fn_sub_3B5D10_003b5d10);
    if (v0 != 0) {
        // 0x003b8764
        charge(ctx, 2);
        if (v0 != 0) {
            // 0x003b8778
            charge(ctx, 21);
            lw(v1, v0, 40);
            a0 = v1 | 0x1;
            sw(a0, v0, 40);
            v1 = si(-65);
            v1 = a0 & v1;
            sw(v1, v0, 40);
            lwc1(f2, v0, 4);
            lwc1(f1, v0, 8);
            lwc1(f0, v0, 12);
            swc1(f2, v0, 44);
            swc1(f1, v0, 48);
            swc1(f0, v0, 52);
            lwc1(f2, s0, 0);
            lwc1(f1, s0, 4);
            lwc1(f0, s0, 8);
            swc1(f2, v0, 56);
            swc1(f1, v0, 60);
            swc1(f0, v0, 64);
            swc1(f20, v0, 88);
            sb(zero, v0, 80);
            v0 = 1;
        } else {
            // 0x003b876c
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x003b8758
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003b87cc (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003B8C30 sub_3B8C30 -- 168 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Field UI element by handle: starts the second animation -- sets 0x8000 in +40, copies +28..+36 to +136..+144 and
// takes the target from the record a1.
void sub_3B8C30(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x003b8c30
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    s0 = a2;
    jal(ctx, 0x3B8C48u, gen::fn_sub_3B5D10_003b5d10);
    if (v0 != 0) {
        // 0x003b8c64
        charge(ctx, 2);
        if (v0 != 0) {
            // 0x003b8c78
            charge(ctx, 18);
            lw(v1, v0, 40);
            v1 = v1 | 0x8000;
            sw(v1, v0, 40);
            lwc1(f2, v0, 28);
            lwc1(f1, v0, 32);
            lwc1(f0, v0, 36);
            swc1(f2, v0, 136);
            swc1(f1, v0, 140);
            swc1(f0, v0, 144);
            lwc1(f2, s1, 0);
            lwc1(f1, s1, 4);
            lwc1(f0, s1, 8);
            swc1(f2, v0, 148);
            swc1(f1, v0, 152);
            swc1(f0, v0, 156);
            sw(s0, v0, 160);
            sw(zero, v0, 164);
            v0 = 1;
        } else {
            // 0x003b8c6c
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x003b8c58
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003b8cc0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003B8E80 sub_3B8E80 -- 176 bytes; frame 0x30: ra sp+0x20, s0 sp+0x10 (sq), f20 sp+0x0
// Field UI element by handle of kind 7: sets 0x400 in +40, +196 = +256, +200 = $f12, +204 = a1, +208 = 0; returns 1 (0
// for another kind or no element).
void sub_3B8E80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12}, f20{ctx, 20};
    // 0x003b8e80
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    mov_s(f20, f12);
    s0 = a1;
    jal(ctx, 0x3B8E98u, gen::fn_sub_3B5D10_003b5d10);
    if (v0 != 0) {
        // 0x003b8eb4
        charge(ctx, 2);
        if (v0 != 0) {
            // 0x003b8ec8
            charge(ctx, 8);
            lhu(a0, v0, 0);
            v1 = 0xF0000;
            v1 = v1 | 0xFC00;
            v1 = a0 & v1;
            a0 = sra(v1, 10);
            v1 = 7;
            if (a0 == v1) {
                // 0x003b8ef4
                charge(ctx, 9);
                lw(v1, v0, 40);
                v1 = v1 | 0x400;
                sw(v1, v0, 40);
                lwc1(f0, v0, 256);
                swc1(f0, v0, 196);
                swc1(f20, v0, 200);
                sw(s0, v0, 204);
                sw(zero, v0, 208);
                v0 = 1;
            } else {
                // 0x003b8ee8
                charge(ctx, 3);
                v0 = 0;
            }
        } else {
            // 0x003b8ebc
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x003b8ea8
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003b8f18 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003BB180 sub_3BB180 -- 80 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Field UI element by handle: sub_3BB0C0.
void sub_3BB180(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003bb180
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    jal(ctx, 0x3BB190u, gen::fn_sub_3B5D10_003b5d10);
    if (v0 == 0) {
        // 0x003bb1b8
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003bb1a0
        charge(ctx, 6);
        a0 = v0;
        a1 = s0;
        jal(ctx, 0x3BB1A8u, gen::fn_sub_3BB0C0_003bb0c0);
    }
    // 0x003bb1bc (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003BB390 sub_3BB390 -- 104 bytes; frame 0x30: ra sp+0x20, s0 sp+0x10 (sq), f20 sp+0x0
// Field UI element by handle of kind 7 ((h >> 10) & 0x3F): stores a1 at +268 and $f12 at +260.
void sub_3BB390(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f20{ctx, 20};
    // 0x003bb390
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s0 = a1;
    mov_s(f20, f12);
    a1 = a0 & 0xFFFF;
    v1 = 0xF0000;
    v1 = v1 | 0xFC00;
    v1 = a1 & v1;
    a1 = sra(v1, 10);
    v1 = 7;
    if (a1 == v1) {
        // 0x003bb3c8
        charge(ctx, 4);
        jal(ctx, 0x3BB3C8u, gen::fn_sub_3B5D10_003b5d10);
        if (v0 != 0) {
            // 0x003bb3d8
            charge(ctx, 2);
            sh(s0, v0, 268);
            swc1(f20, v0, 260);
        }
    }
    // 0x003bb3e0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003BCBF0 sub_3BCBF0 -- 136 bytes; frame 0x10: ra sp+0x0
// Wrapper over sub_3500A0 (field UI).
void sub_3BCBF0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003bcbf0
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a1 != 0) {
        // 0x003bcc0c
        charge(ctx, 4);
        v0 = 1;
        sh(v0, gp, -18072);  // 0x7CE658
        if (a0 != 0) {
            // 0x003bcc2c
            charge(ctx, 1);
            sh(a0, gp, -18068);  // 0x7CE65C
        } else {
            // 0x003bcc1c
            charge(ctx, 4);
            v0 = si(-1);
            sh(v0, gp, -18068);  // 0x7CE65C
        }
        // 0x003bcc30
        charge(ctx, 14);
        v0 = sll(a1, 2);
        v0 = addu(v0, a1);
        v0 = sll(v0, 1);
        sh(v0, gp, -18060);  // 0x7CE664
        lhu(v0, gp, -18060);  // 0x7CE664
        v1 = sll(v0, 2);
        v0 = 10;
        div(v1, v0);
        mflo(v0);
        sh(v0, gp, -18064);  // 0x7CE660
        a1 = dsll32(a1, 16);
        a1 = dsra32(a1, 16);
        jal(ctx, 0x3BCC60u, gen::fn_sub_3500A0_003500a0);
    } else {
        // 0x003bcc00
        charge(ctx, 3);
        sh(zero, gp, -18072);  // 0x7CE658
    }
    // 0x003bcc68 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003BD9A0 sub_3BD9A0 -- 184 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Looks (a0, a1) up in the 8-byte rows of *0x95B724 (count *0x95B728: +0 u16 id, +2 u8 sub); returns the row's +4 when
// MT_Misc_BitChk(2696) == 1, else +6; 0 when not found.
void sub_3BD9A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003bd9a0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    t0 = 0;
    v0 = 0x960000;
    lw(a3, v0, -18652);  // 0x95B724
    v0 = 0x960000;
    lw(a2, v0, -18648);  // 0x95B728
    for (;;) {
        // 0x003bda34
        charge(ctx, 3);
        v0 = slt(t0, a2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003bd9c8
        charge(ctx, 5);
        s0 = sll(t0, 3);
        v1 = addu(a3, s0);
        lhu(v0, v1, 0);
        if (a0 == v0) {
            // 0x003bd9dc
            charge(ctx, 3);
            lbu(v0, v1, 2);
            if (a1 != v0) {
                goto L_003bda30;
            }
            goto L_003bd9e8_3;
        }
    L_003bda30:
        charge(ctx, 1);
        t0 = addiu(t0, 1);
    }
    // 0x003bda40
    charge(ctx, 1);
    v0 = 0;
    // 0x003bda44 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
    return;
L_003bd9e8_3:
    charge(ctx, 6);
    a0 = 2696;
    jal(ctx, 0x3BD9ECu, gen::fn_MT_Misc_BitChk_003951d0);
    v1 = 1;
    if (v0 != v1) {
        // 0x003bda18
        charge(ctx, 4);
        v0 = 0x960000;
        lw(v0, v0, -18652);  // 0x95B724
        v0 = addu(s0, v0);
        lhu(v0, v0, 6);
    } else {
        // 0x003bda00
        charge(ctx, 6);
        v0 = 0x960000;
        lw(v0, v0, -18652);  // 0x95B724
        v0 = addu(s0, v0);
        lhu(v0, v0, 4);
    }
    // 0x003bda28
    charge(ctx, 2);
    // 0x003bda44 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003C8230 sub_3C8230 -- 168 bytes; frame 0x10: ra sp+0x0
// nm list helper: sub_3A4360 on the list record.
void sub_3C8230(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c8230
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v0 = 3;
    if (a1 == v0) {
        // 0x003c82b4
        charge(ctx, 4);
        lw(a0, a0, 0);
        a1 = 7;
        jal(ctx, 0x3C82BCu, gen::fn_sub_3A4360_003a4360);
    } else {
        // 0x003c8244
        charge(ctx, 3);
        v0 = 2;
        if (a1 == v0) {
            // 0x003c829c
            charge(ctx, 6);
            lw(a0, a0, 0);
            a1 = 6;
            jal(ctx, 0x3C82A4u, gen::fn_sub_3A4360_003a4360);
        } else {
            // 0x003c8250
            charge(ctx, 3);
            v0 = 1;
            if (a1 == v0) {
                // 0x003c8284
                charge(ctx, 6);
                lw(a0, a0, 0);
                a1 = 5;
                jal(ctx, 0x3C828Cu, gen::fn_sub_3A4360_003a4360);
            } else {
                // 0x003c825c
                charge(ctx, 2);
                if (a1 == 0) {
                    // 0x003c826c
                    charge(ctx, 6);
                    lw(a0, a0, 0);
                    a1 = 4;
                    jal(ctx, 0x3C8274u, gen::fn_sub_3A4360_003a4360);
                } else {
                    // 0x003c8264
                    charge(ctx, 2);
                }
            }
        }
    }
    // 0x003c82c4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003C82E0 sub_3C82E0 -- 196 bytes; frame 0x10: ra sp+0x0
// nm list helper: sub_3A4360 on the list record (second variant).
void sub_3C82E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c82e0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v1 = 0x960000;
    v1 = addiu(v1, -16752);  // &0x95BE90
    if (v1 != 0) {
        // 0x003c8304
        charge(ctx, 3);
        v0 = 3;
        if (a0 == v0) {
            // 0x003c8380
            charge(ctx, 4);
            lw(a0, v1, 0);
            a1 = 7;
            jal(ctx, 0x3C8388u, gen::fn_sub_3A4360_003a4360);
        } else {
            // 0x003c8310
            charge(ctx, 3);
            v0 = 2;
            if (a0 == v0) {
                // 0x003c8368
                charge(ctx, 6);
                lw(a0, v1, 0);
                a1 = 6;
                jal(ctx, 0x3C8370u, gen::fn_sub_3A4360_003a4360);
            } else {
                // 0x003c831c
                charge(ctx, 3);
                v0 = 1;
                if (a0 == v0) {
                    // 0x003c8350
                    charge(ctx, 6);
                    lw(a0, v1, 0);
                    a1 = 5;
                    jal(ctx, 0x3C8358u, gen::fn_sub_3A4360_003a4360);
                } else {
                    // 0x003c8328
                    charge(ctx, 2);
                    if (a0 == 0) {
                        // 0x003c8338
                        charge(ctx, 6);
                        lw(a0, v1, 0);
                        a1 = 4;
                        jal(ctx, 0x3C8340u, gen::fn_sub_3A4360_003a4360);
                    } else {
                        // 0x003c8330
                        charge(ctx, 2);
                    }
                }
            }
        }
        // 0x003c8390
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003c82f8
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003c8394 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003CB100 sub_3CB100 -- 236 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Data-referenced wrapper over sub_3CA780.
void sub_3CB100(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15};
    // 0x003cb100
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
    lw(t2, s0, 208);
    jal(ctx, 0x3CB148u, gen::fn_sub_3CA780_003ca780);
    mtc1(zero, f12);
    lh(v1, s0, 18);
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
    lw(t2, s0, 208);
    jal(ctx, 0x3CB18Cu, gen::fn_sub_3CA780_003ca780);
    mtc1(zero, f12);
    lh(v1, s0, 18);
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
    lw(t2, s0, 208);
    jal(ctx, 0x3CB1D0u, gen::fn_sub_3CA780_003ca780);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003CF240 sub_3CF240 -- 344 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// "fclBankManager.c": sets a facility bank's state (sub_1052B0 / sub_3CF8F0) with the debug printf
// "fclBankManagerSetState:Bank Hit[%d]!!!". [proposed name fclBankManagerSetState]
void sub_3CF240(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003cf240
    enter(ctx, 45);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    a0 = addiu(gp, -21960);  // "[%s:%d]"
    a1 = 0x6A0000;
    a1 = addiu(a1, 17008);  // "fclBankManager.c"
    a2 = 126;
    jal(ctx, 0x3CF274u, gen::fn_printf_005225a8);
    s1 = s3 & 0xFF;
    v0 = s3 & 0xFF00;
    s0 = srl(v0, 8);
    v0 = lui(0xFFFF);
    v0 = s3 & v0;
    s4 = srl(v0, 16);
    a0 = 0x6A0000;
    a0 = addiu(a0, 17048);  // "%d:%d:%d:%d\n"
    a1 = s3;
    a2 = s4;
    a3 = s0;
    t0 = s1;
    jal(ctx, 0x3CF2ACu, gen::fn_printf_005225a8);
    a0 = 0x6A0000;
    a0 = addiu(a0, 17048);  // "%d:%d:%d:%d\n"
    a1 = s3;
    a2 = s4;
    a3 = s0;
    t0 = s1;
    jal(ctx, 0x3CF2CCu, gen::fn_sub_1052B0_001052b0);
    a0 = s3;
    jal(ctx, 0x3CF2D8u, gen::fn_sub_3CF8F0_003cf8f0);
    s0 = dsll32(v0, 16);
    s0 = dsra32(s0, 16);
    v0 = si(-1);
    if (s0 == v0) {
        // 0x003cf370
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003cf2f4
        charge(ctx, 31);
        lw(v0, gp, -18032);  // 0x7CE680
        lw(v1, v0, 36);
        v0 = s2 & 0xFF00;
        a0 = dsll32(v0, 16);
        a0 = dsra32(a0, 16);
        v0 = sll(s0, 2);
        v0 = addu(v0, s0);
        v0 = sll(v0, 2);
        v1 = addu(v0, v1);
        lh(v0, v1, 4);
        v0 = v0 | a0;
        sh(v0, v1, 4);
        a0 = addiu(gp, -21960);  // "[%s:%d]"
        a1 = 0x6A0000;
        a1 = addiu(a1, 17008);  // "fclBankManager.c"
        a2 = 131;
        jal(ctx, 0x3CF334u, gen::fn_printf_005225a8);
        a0 = 0x6A0000;
        a0 = addiu(a0, 17072);  // "fclBankManagerSetState:Bank Hit[%d]!!!\n"
        a1 = s0;
        jal(ctx, 0x3CF348u, gen::fn_printf_005225a8);
        a0 = 0x6A0000;
        a0 = addiu(a0, 17072);  // "fclBankManagerSetState:Bank Hit[%d]!!!\n"
        a1 = s0;
        jal(ctx, 0x3CF35Cu, gen::fn_sub_1052B0_001052b0);
        v0 = 1;
    }
    // 0x003cf374 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x003E6130 sub_3E6130 -- 708 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// nm object step: reads the payload word (nmObjPayloadWord12) and runs sub_3E5B00 / sub_3E5E20 / sub_488F30.
void sub_3E6130(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x003e6130
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(a0, gp, -18024);  // 0x7CE688
    jal(ctx, 0x3E6150u, gen::fn_nmObjPayloadWord12_003c5460);
    s0 = v0;
    lw(s3, s2, 52);
    s1 = 0;
    lh(v1, s3, 8);
    if (v1 == 0) {
        // 0x003e6170
        charge(ctx, 12);
        jal(ctx, 0x3E6170u, gen::fn_sub_488F30_00488f30);
        a1 = 0xFFFF;
        divu(v0, a1);
        mfhi(a0);
        v1 = sll(a0, 4);
        v1 = subu(v1, a0);
        v1 = sll(v1, 2);
        divu(v1, a1);
        mflo(v1);
        v1 = addiu(v1, 10);
        sh(v1, s3, 8);
    }
    // 0x003e61a0
    charge(ctx, 11);
    lh(v1, s2, 38);
    sb(v1, s3, 5);
    lh(v1, s3, 6);
    v1 = addiu(v1, 1);
    sh(v1, s3, 6);
    a0 = dsll32(v1, 16);
    a0 = dsra32(a0, 16);
    lh(v1, s3, 8);
    v1 = slt(a0, v1);
    if (v1 == 0) {
        // 0x003e61cc
        charge(ctx, 19);
        sh(zero, s3, 6);
        jal(ctx, 0x3E61D0u, gen::fn_sub_488F30_00488f30);
        a0 = 0xFFFF;
        divu(v0, a0);
        mfhi(v1);
        v0 = sll(v1, 4);
        v0 = subu(v0, v1);
        v0 = sll(v0, 2);
        divu(v0, a0);
        mflo(v0);
        v0 = addiu(v0, 10);
        sh(v0, s3, 8);
        s2 = 5;
        v0 = dsll32(v0, 16);
        v0 = dsra32(v0, 16);
        v0 = slti(v0, 50);
        if (v0 != 0) {
            // 0x003e624c
            charge(ctx, 11);
            jal(ctx, 0x3E624Cu, gen::fn_sub_488F30_00488f30);
            a0 = 0xFFFF;
            divu(v0, a0);
            mfhi(v1);
            v0 = sll(v1, 4);
            v0 = subu(v0, v1);
            divu(v0, a0);
            mflo(v0);
            v0 = addiu(v0, 10);
            sb(v0, s3, 4);
        } else {
            // 0x003e6218
            charge(ctx, 13);
            jal(ctx, 0x3E6218u, gen::fn_sub_488F30_00488f30);
            a0 = 0xFFFF;
            divu(v0, a0);
            mfhi(v1);
            v0 = sll(v1, 4);
            v0 = subu(v0, v1);
            divu(v0, a0);
            mflo(v0);
            v0 = addiu(v0, 15);
            sb(v0, s3, 4);
        }
        // 0x003e6278
        charge(ctx, 4);
        lb(a2, s3, 4);
        v0 = slti(a2, 25);
        if (v0 == 0) {
            // 0x003e6288
            charge(ctx, 1);
            s2 = 30;
        }
        // 0x003e628c
        charge(ctx, 16);
        mtc1(s2, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, gp, -32544);  // 0x7CADD0
        mul_s(f0, f0, f1);
        cvt_w_s(f0, f0);
        mfc1(a3, f0);
        a0 = s3;
        a1 = 0;
        t0 = 40;
        jal(ctx, 0x3E62B4u, gen::fn_sub_3E5B00_003e5b00);
        lb(v1, s3, 4);
        v0 = 28;
        if (v1 != v0) {
            // 0x003e6318
            charge(ctx, 23);
            v0 = 0x3F000000;
            mtc1(v0, f1);
            mtc1(v1, f0);
            cvt_s_w(f0, f0);
            mul_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(v0, f0);
            a2 = dsll32(v0, 24);
            a2 = dsra32(a2, 24);
            mtc1(s2, f0);
            cvt_s_w(f1, f0);
            lwc1(f0, gp, -32628);  // 0x7CAD7C
            mul_s(f0, f0, f1);
            cvt_w_s(f0, f0);
            mfc1(a3, f0);
            a0 = s3;
            a1 = 1;
            t0 = 40;
            jal(ctx, 0x3E636Cu, gen::fn_sub_3E5B00_003e5b00);
        } else {
            // 0x003e62cc
            charge(ctx, 19);
            v0 = 0x3F000000;
            mtc1(v0, f1);
            mtc1(v1, f0);
            cvt_s_w(f0, f0);
            mul_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(v0, f0);
            a2 = dsll32(v0, 24);
            a2 = dsra32(a2, 24);
            a0 = s3;
            a1 = 1;
            a3 = s2;
            t0 = 40;
            jal(ctx, 0x3E6308u, gen::fn_sub_3E5B00_003e5b00);
        }
    }
    // 0x003e6374
    charge(ctx, 4);
    lw(v1, s0, 8);
    v1 = v1 & 0x20;
    if (v1 != 0) {
        // 0x003e6384
        charge(ctx, 1);
        s1 = 1;
    }
    // 0x003e6388
    charge(ctx, 3);
    s0 = 0;
    for (;;) {
        // 0x003e63c8
        charge(ctx, 3);
        v1 = slti(s0, 64);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003e6394
        charge(ctx, 6);
        v1 = sll(s0, 4);
        v1 = addu(s3, v1);
        a1 = addiu(v1, 12);
        lhu(v1, v1, 22);
        if (i64(v1) > 0) {
            // 0x003e63ac
            charge(ctx, 3);
            lw(v1, a1, 0);
            if (v1 == s1) {
                // 0x003e63b8
                charge(ctx, 3);
                a0 = s3;
                jal(ctx, 0x3E63BCu, gen::fn_sub_3E5E20_003e5e20);
            }
        }
        // 0x003e63c4
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x003e63d4
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x003E9200 sub_3E9200 -- 752 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// nm command-list step: the decided / held / cancelled / paged rows of the command list (nmCmdList*), with sub_3DFF30
// / sub_3E0C20 / sub_40CA00.
void sub_3E9200(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003e9200
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    jal(ctx, 0x3E9218u, gen::fn_nmObjPayloadWord12_003c5460);
    a0 = s0;
    jal(ctx, 0x3E9224u, gen::fn_sub_3C5470_003c5470);
    s0 = v0;
    lw(v0, v0, 16);
    lw(s2, v0, 12);
    lw(v0, s2, 36);
    lw(s1, v0, 68);
    a0 = s1;
    jal(ctx, 0x3E9244u, gen::fn_sub_40CA00_0040ca00);
    v1 = 3;
    if (v0 != v1) {
        // 0x003e9264
        charge(ctx, 4);
        lw(v1, s0, 8);
        v0 = 1;
        if (v1 != v0) {
            // 0x003e9274
            charge(ctx, 2);
            if (v1 != 0) {
                // 0x003e927c
                charge(ctx, 2);
                goto L_003e92cc;
            }
            // 0x003e9284
            charge(ctx, 5);
            lw(a0, s1, 8);
            jal(ctx, 0x3E9288u, gen::fn_sub_3DFF30_003dff30);
            if (v0 != 0) {
                // 0x003e92a4
                charge(ctx, 10);
                lw(a0, gp, -18024);  // 0x7CE688
                jal(ctx, 0x3E92A8u, gen::fn_nmObjPayloadWord12_003c5460);
                a0 = v0;
                a1 = 1;
                a2 = 0;
                jal(ctx, 0x3E92BCu, gen::fn_sub_3E0C20_003e0c20);
                v0 = 1;
                sw(v0, s0, 8);
                goto L_003e92cc;
            }
            // 0x003e9298
            charge(ctx, 3);
            v0 = 0;
            // 0x003e94d4 (the shared epilogue, written out on this path)
            charge(ctx, 7);
            ld(ra, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x40);
            return;
        }
    L_003e92cc:
        charge(ctx, 6);
        a0 = s2;
        jal(ctx, 0x3E92D0u, gen::fn_nmCmdListDecidedRow_003c6c50);
        s0 = v0;
        if (s0 == 0) {
            // 0x003e93cc
            charge(ctx, 5);
            a0 = s2;
            jal(ctx, 0x3E93D0u, gen::fn_nmCmdListCancelled_003c6c80);
            if (v0 == 0) {
                // 0x003e9448
                charge(ctx, 5);
                a0 = s2;
                jal(ctx, 0x3E944Cu, gen::fn_nmCmdListMovedDownRow_003c6ce0);
                if (v0 == 0) {
                    // 0x003e945c
                    charge(ctx, 5);
                    a0 = s2;
                    jal(ctx, 0x3E9460u, gen::fn_nmCmdListScrolledRow_003c6d10);
                    if (v0 != 0) {
                        goto L_003e9470;
                    }
                    // 0x003e9490
                    charge(ctx, 5);
                    a0 = s2;
                    jal(ctx, 0x3E9494u, gen::fn_nmCmdListPagedDown_003c6ca0);
                    if (v0 == 0) {
                        // 0x003e94a4
                        charge(ctx, 5);
                        a0 = s2;
                        jal(ctx, 0x3E94A8u, gen::fn_nmCmdListMovedUp_003c6cc0);
                        if (v0 != 0) {
                            goto L_003e94b8;
                        }
                        goto L_003e94d0;
                    }
                L_003e94b8:
                    charge(ctx, 6);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 5;
                    jal(ctx, 0x3E94C8u, gen::fn_sub_10A4E0_0010a4e0);
                    goto L_003e94d0;
                }
            L_003e9470:
                charge(ctx, 8);
                a0 = 0;
                a1 = 0;
                a2 = 0;
                a3 = 0;
                jal(ctx, 0x3E9480u, gen::fn_sub_10A4E0_0010a4e0);
            L_003e94d0:
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x003e93e0
                charge(ctx, 26);
                a0 = s2;
                jal(ctx, 0x3E93E4u, gen::fn_nmCmdListHold_003c6ea0);
                a0 = 0;
                a1 = 0;
                a2 = 0;
                a3 = 2;
                jal(ctx, 0x3E93FCu, gen::fn_sub_10A4E0_0010a4e0);
                a0 = s2;
                jal(ctx, 0x3E9408u, gen::fn_nmCmdListCloseNow_003c6f50);
                a0 = s1;
                jal(ctx, 0x3E9414u, gen::fn_sub_40C520_0040c520);
                lw(a0, gp, -18024);  // 0x7CE688
                jal(ctx, 0x3E9420u, gen::fn_nmObjPayloadWord12_003c5460);
                a0 = v0;
                a1 = 1;
                a2 = a1;
                jal(ctx, 0x3E9434u, gen::fn_sub_3E0C20_003e0c20);
                v0 = 4;
            }
        } else {
            // 0x003e92e4
            charge(ctx, 6);
            lw(v0, s0, 20);
            lw(v0, v0, 28);
            lw(v0, v0, 0);
            v0 = v0 & 0x1;
            if (v0 != 0) {
                // 0x003e93a4
                charge(ctx, 2);
                if (v0 != 0) {
                    // 0x003e93ac
                    charge(ctx, 8);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 8;
                    jal(ctx, 0x3E93BCu, gen::fn_sub_10A4E0_0010a4e0);
                }
                goto L_003e94d0;
            }
            // 0x003e92fc
            charge(ctx, 42);
            a0 = s2;
            jal(ctx, 0x3E9300u, gen::fn_nmCmdListHold_003c6ea0);
            a0 = 0;
            a1 = 0;
            a2 = 0;
            a3 = 1;
            jal(ctx, 0x3E9318u, gen::fn_sub_10A4E0_0010a4e0);
            a0 = 0;
            a1 = 1;
            jal(ctx, 0x3E9328u, gen::fn_sub_1A0040_001a0040);
            a0 = 3072;
            a1 = 0;
            jal(ctx, 0x3E9338u, gen::fn_sub_1A0150_001a0150);
            a0 = 3073;
            a1 = 0;
            jal(ctx, 0x3E9348u, gen::fn_sub_1A0150_001a0150);
            a0 = 3074;
            a1 = 0;
            jal(ctx, 0x3E9358u, gen::fn_sub_1A0150_001a0150);
            a0 = s2;
            jal(ctx, 0x3E9364u, gen::fn_nmCmdListCloseNow_003c6f50);
            a0 = s1;
            jal(ctx, 0x3E9370u, gen::fn_sub_40C520_0040c520);
            lw(a0, gp, -18024);  // 0x7CE688
            jal(ctx, 0x3E937Cu, gen::fn_nmObjPayloadWord12_003c5460);
            a0 = v0;
            a1 = 1;
            a2 = a1;
            jal(ctx, 0x3E9390u, gen::fn_sub_3E0C20_003e0c20);
            lw(v0, s0, 0);
        }
    } else {
        // 0x003e9258
        charge(ctx, 3);
        v0 = si(-1);
    }
    // 0x003e94d4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003EAD10 sub_3EAD10 -- 188 bytes; frame 0x60: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Name-entry / menu sequence page (nm layer, the list object *0x7CE688): adds the page's step (nmSequenceAddStep,
// table 0x6A70E0).
void sub_3EAD10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x003ead10
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a1 = 0x6A0000;
    a1 = addiu(a1, 28896);  // &0x6A70E0
    a0 = addiu(sp, 0x30);
    v1 = 2;
    for (;;) {
        // 0x003ead34
        charge(ctx, 7);
        lq(v0, a1, 0);
        a1 = addiu(a1, 16);
        v1 = addiu(v1, -1);
        sq(v0, a0, 0);
        a0 = addiu(a0, 16);
        if (i64(v1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003ead50
    charge(ctx, 12);
    lwc1(f0, a1, 0);
    swc1(f0, a0, 0);
    lw(a0, gp, -18024);  // 0x7CE688
    a1 = 7;
    a2 = addiu(sp, 0x30);
    a3 = 0;
    t0 = 2;
    jal(ctx, 0x3EAD6Cu, gen::fn_nmSequenceAddStep_003c5240);
    s1 = v0;
    if (s0 != 0) {
        // 0x003ead80
        charge(ctx, 1);
        sw(s1, s0, 40);
    }
    // 0x003ead84
    charge(ctx, 18);
    lw(a0, gp, -18024);  // 0x7CE688
    jal(ctx, 0x3EAD88u, gen::fn_nmObjPayloadWord12_003c5460);
    a0 = v0;
    a1 = 5;
    a2 = 0;
    jal(ctx, 0x3EAD9Cu, gen::fn_sub_3E0C20_003e0c20);
    a0 = s1;
    jal(ctx, 0x3EADA8u, gen::fn_sub_3C5470_003c5470);
    v0 = s1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x003EADD0 sub_3EADD0 -- 212 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Name-entry / menu sequence page (nm layer, the list object *0x7CE688): the page's per-frame check (sub_3C5470 /
// sub_3E0C20).
void sub_3EADD0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003eadd0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(a0, a0, 40);
    if (a0 != 0) {
        // 0x003eadf4
        charge(ctx, 3);
        lw(s2, a0, 20);
        if (s2 == 0) {
            goto L_003eae00;
        }
        // 0x003eae0c
        charge(ctx, 7);
        jal(ctx, 0x3EAE0Cu, gen::fn_sub_3C5470_003c5470);
        s0 = v0;
        lw(v0, s2, 20);
        v0 = v0 & 0x8;
        if (v0 == 0) {
            // 0x003eae28
            charge(ctx, 4);
            lw(v0, s0, 4);
            v0 = v0 & 0x1;
            if (v0 != 0) {
                goto L_003eae38;
            }
            // 0x003eae84
            charge(ctx, 1);
            v0 = si(-1);
            // 0x003eae88 (the shared epilogue, written out on this path)
            charge(ctx, 7);
            ld(ra, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x40);
            return;
        }
    L_003eae38:
        charge(ctx, 13);
        sw(zero, s1, 40);
        lw(a0, gp, -18024);  // 0x7CE688
        jal(ctx, 0x3EAE40u, gen::fn_nmObjPayloadWord12_003c5460);
        a0 = v0;
        a1 = 5;
        a2 = 1;
        jal(ctx, 0x3EAE54u, gen::fn_sub_3E0C20_003e0c20);
        lw(v0, s0, 4);
        v0 = v0 & 0x8;
        if (v0 == 0) {
            // 0x003eae78
            charge(ctx, 3);
            lw(v0, s0, 0);
        } else {
            // 0x003eae6c
            charge(ctx, 3);
            v0 = 1;
        }
        // 0x003eae88 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(ra, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
        return;
    }
L_003eae00:
    charge(ctx, 3);
    v0 = si(-1);
    // 0x003eae88 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003EBA10 sub_3EBA10 -- 188 bytes; frame 0x60: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Name-entry / menu sequence page (nm layer, the list object *0x7CE688): adds the page's step (table 0x6A7110).
void sub_3EBA10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x003eba10
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a1 = 0x6A0000;
    a1 = addiu(a1, 28944);  // &0x6A7110
    a0 = addiu(sp, 0x30);
    v1 = 2;
    for (;;) {
        // 0x003eba34
        charge(ctx, 7);
        lq(v0, a1, 0);
        a1 = addiu(a1, 16);
        v1 = addiu(v1, -1);
        sq(v0, a0, 0);
        a0 = addiu(a0, 16);
        if (i64(v1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003eba50
    charge(ctx, 12);
    lwc1(f0, a1, 0);
    swc1(f0, a0, 0);
    lw(a0, gp, -18024);  // 0x7CE688
    a1 = 6;
    a2 = addiu(sp, 0x30);
    a3 = 0;
    t0 = 2;
    jal(ctx, 0x3EBA6Cu, gen::fn_nmSequenceAddStep_003c5240);
    s1 = v0;
    if (s0 != 0) {
        // 0x003eba80
        charge(ctx, 1);
        sw(s1, s0, 36);
    }
    // 0x003eba84
    charge(ctx, 18);
    a0 = s1;
    jal(ctx, 0x3EBA88u, gen::fn_sub_3C5470_003c5470);
    lw(a0, gp, -18024);  // 0x7CE688
    jal(ctx, 0x3EBA94u, gen::fn_nmObjPayloadWord12_003c5460);
    a0 = v0;
    a1 = 7;
    a2 = 0;
    jal(ctx, 0x3EBAA8u, gen::fn_sub_3E0C20_003e0c20);
    v0 = s1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x003EBAD0 sub_3EBAD0 -- 184 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Name-entry / menu sequence page (nm layer, the list object *0x7CE688): the page's per-frame check.
void sub_3EBAD0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ebad0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(a0, a0, 36);
    if (a0 != 0) {
        // 0x003ebaf4
        charge(ctx, 3);
        lw(s2, a0, 20);
        if (s2 == 0) {
            goto L_003ebb00;
        }
        // 0x003ebb0c
        charge(ctx, 7);
        jal(ctx, 0x3EBB0Cu, gen::fn_sub_3C5470_003c5470);
        s0 = v0;
        lw(v0, s2, 20);
        v0 = v0 & 0x8;
        if (v0 == 0) {
            // 0x003ebb28
            charge(ctx, 4);
            lw(v0, s0, 4);
            v0 = v0 & 0x1;
            if (v0 != 0) {
                goto L_003ebb38;
            }
            // 0x003ebb68
            charge(ctx, 1);
            v0 = si(-1);
            // 0x003ebb6c (the shared epilogue, written out on this path)
            charge(ctx, 7);
            ld(ra, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x40);
            return;
        }
    L_003ebb38:
        charge(ctx, 12);
        lw(a0, gp, -18024);  // 0x7CE688
        jal(ctx, 0x3EBB3Cu, gen::fn_nmObjPayloadWord12_003c5460);
        a0 = v0;
        a1 = 7;
        a2 = 1;
        jal(ctx, 0x3EBB50u, gen::fn_sub_3E0C20_003e0c20);
        sw(zero, s1, 36);
        lw(v0, s0, 0);
        // 0x003ebb6c (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(ra, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
        return;
    }
L_003ebb00:
    charge(ctx, 3);
    v0 = si(-1);
    // 0x003ebb6c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003EC090 sub_3EC090 -- 188 bytes; frame 0x60: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Name-entry / menu sequence page (nm layer, the list object *0x7CE688): adds the page's step (table 0x6A7140).
void sub_3EC090(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x003ec090
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a1 = 0x6A0000;
    a1 = addiu(a1, 28992);  // &0x6A7140
    a0 = addiu(sp, 0x30);
    v1 = 2;
    for (;;) {
        // 0x003ec0b4
        charge(ctx, 7);
        lq(v0, a1, 0);
        a1 = addiu(a1, 16);
        v1 = addiu(v1, -1);
        sq(v0, a0, 0);
        a0 = addiu(a0, 16);
        if (i64(v1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003ec0d0
    charge(ctx, 12);
    lwc1(f0, a1, 0);
    swc1(f0, a0, 0);
    lw(a0, gp, -18024);  // 0x7CE688
    a1 = 8;
    a2 = addiu(sp, 0x30);
    a3 = 0;
    t0 = 2;
    jal(ctx, 0x3EC0ECu, gen::fn_nmSequenceAddStep_003c5240);
    s1 = v0;
    if (s0 != 0) {
        // 0x003ec100
        charge(ctx, 1);
        sw(s1, s0, 44);
    }
    // 0x003ec104
    charge(ctx, 18);
    a0 = s1;
    jal(ctx, 0x3EC108u, gen::fn_sub_3C5470_003c5470);
    lw(a0, gp, -18024);  // 0x7CE688
    jal(ctx, 0x3EC114u, gen::fn_nmObjPayloadWord12_003c5460);
    a0 = v0;
    a1 = 5;
    a2 = 0;
    jal(ctx, 0x3EC128u, gen::fn_sub_3E0C20_003e0c20);
    v0 = s1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x003EC150 sub_3EC150 -- 184 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Name-entry / menu sequence page (nm layer, the list object *0x7CE688): the page's per-frame check.
void sub_3EC150(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ec150
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(a0, a0, 44);
    if (a0 != 0) {
        // 0x003ec174
        charge(ctx, 3);
        lw(s2, a0, 20);
        if (s2 == 0) {
            goto L_003ec180;
        }
        // 0x003ec18c
        charge(ctx, 7);
        jal(ctx, 0x3EC18Cu, gen::fn_sub_3C5470_003c5470);
        s0 = v0;
        lw(v0, s2, 20);
        v0 = v0 & 0x8;
        if (v0 == 0) {
            // 0x003ec1a8
            charge(ctx, 4);
            lw(v0, s0, 4);
            v0 = v0 & 0x1;
            if (v0 != 0) {
                goto L_003ec1b8;
            }
            // 0x003ec1e8
            charge(ctx, 1);
            v0 = si(-1);
            // 0x003ec1ec (the shared epilogue, written out on this path)
            charge(ctx, 7);
            ld(ra, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x40);
            return;
        }
    L_003ec1b8:
        charge(ctx, 12);
        lw(a0, gp, -18024);  // 0x7CE688
        jal(ctx, 0x3EC1BCu, gen::fn_nmObjPayloadWord12_003c5460);
        a0 = v0;
        a1 = 5;
        a2 = 1;
        jal(ctx, 0x3EC1D0u, gen::fn_sub_3E0C20_003e0c20);
        sw(zero, s1, 44);
        lw(v0, s0, 0);
        // 0x003ec1ec (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(ra, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
        return;
    }
L_003ec180:
    charge(ctx, 3);
    v0 = si(-1);
    // 0x003ec1ec (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003EC6F0 sub_3EC6F0 -- 188 bytes; frame 0x60: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Name-entry / menu sequence page (nm layer, the list object *0x7CE688): adds the page's step (table 0x6A7170).
void sub_3EC6F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x003ec6f0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a1 = 0x6A0000;
    a1 = addiu(a1, 29040);  // &0x6A7170
    a0 = addiu(sp, 0x30);
    v1 = 2;
    for (;;) {
        // 0x003ec714
        charge(ctx, 7);
        lq(v0, a1, 0);
        a1 = addiu(a1, 16);
        v1 = addiu(v1, -1);
        sq(v0, a0, 0);
        a0 = addiu(a0, 16);
        if (i64(v1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003ec730
    charge(ctx, 12);
    lwc1(f0, a1, 0);
    swc1(f0, a0, 0);
    lw(a0, gp, -18024);  // 0x7CE688
    a1 = 9;
    a2 = addiu(sp, 0x30);
    a3 = 0;
    t0 = 2;
    jal(ctx, 0x3EC74Cu, gen::fn_nmSequenceAddStep_003c5240);
    s1 = v0;
    if (s0 != 0) {
        // 0x003ec760
        charge(ctx, 1);
        sw(s1, s0, 48);
    }
    // 0x003ec764
    charge(ctx, 18);
    a0 = s1;
    jal(ctx, 0x3EC768u, gen::fn_sub_3C5470_003c5470);
    lw(a0, gp, -18024);  // 0x7CE688
    jal(ctx, 0x3EC774u, gen::fn_nmObjPayloadWord12_003c5460);
    a0 = v0;
    a1 = 5;
    a2 = 0;
    jal(ctx, 0x3EC788u, gen::fn_sub_3E0C20_003e0c20);
    v0 = s1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x003EC7B0 sub_3EC7B0 -- 184 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Name-entry / menu sequence page (nm layer, the list object *0x7CE688): the page's per-frame check.
void sub_3EC7B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ec7b0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(a0, a0, 48);
    if (a0 != 0) {
        // 0x003ec7d4
        charge(ctx, 3);
        lw(s2, a0, 20);
        if (s2 == 0) {
            goto L_003ec7e0;
        }
        // 0x003ec7ec
        charge(ctx, 7);
        jal(ctx, 0x3EC7ECu, gen::fn_sub_3C5470_003c5470);
        s0 = v0;
        lw(v0, s2, 20);
        v0 = v0 & 0x8;
        if (v0 == 0) {
            // 0x003ec808
            charge(ctx, 4);
            lw(v0, s0, 4);
            v0 = v0 & 0x1;
            if (v0 != 0) {
                goto L_003ec818;
            }
            // 0x003ec848
            charge(ctx, 1);
            v0 = si(-1);
            // 0x003ec84c (the shared epilogue, written out on this path)
            charge(ctx, 7);
            ld(ra, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x40);
            return;
        }
    L_003ec818:
        charge(ctx, 12);
        sw(zero, s1, 48);
        lw(a0, gp, -18024);  // 0x7CE688
        jal(ctx, 0x3EC820u, gen::fn_nmObjPayloadWord12_003c5460);
        a0 = v0;
        a1 = 5;
        a2 = 1;
        jal(ctx, 0x3EC834u, gen::fn_sub_3E0C20_003e0c20);
        lw(v0, s0, 0);
        // 0x003ec84c (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(ra, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
        return;
    }
L_003ec7e0:
    charge(ctx, 3);
    v0 = si(-1);
    // 0x003ec84c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003ECD30 sub_3ECD30 -- 188 bytes; frame 0x60: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Name-entry / menu sequence page (nm layer, the list object *0x7CE688): adds the page's step (table 0x6A71A0).
void sub_3ECD30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x003ecd30
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a1 = 0x6A0000;
    a1 = addiu(a1, 29088);  // &0x6A71A0
    a0 = addiu(sp, 0x30);
    v1 = 2;
    for (;;) {
        // 0x003ecd54
        charge(ctx, 7);
        lq(v0, a1, 0);
        a1 = addiu(a1, 16);
        v1 = addiu(v1, -1);
        sq(v0, a0, 0);
        a0 = addiu(a0, 16);
        if (i64(v1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003ecd70
    charge(ctx, 12);
    lwc1(f0, a1, 0);
    swc1(f0, a0, 0);
    lw(a0, gp, -18024);  // 0x7CE688
    a1 = 10;
    a2 = addiu(sp, 0x30);
    a3 = 0;
    t0 = 2;
    jal(ctx, 0x3ECD8Cu, gen::fn_nmSequenceAddStep_003c5240);
    s1 = v0;
    if (s0 != 0) {
        // 0x003ecda0
        charge(ctx, 1);
        sw(s1, s0, 52);
    }
    // 0x003ecda4
    charge(ctx, 18);
    a0 = s1;
    jal(ctx, 0x3ECDA8u, gen::fn_sub_3C5470_003c5470);
    lw(a0, gp, -18024);  // 0x7CE688
    jal(ctx, 0x3ECDB4u, gen::fn_nmObjPayloadWord12_003c5460);
    a0 = v0;
    a1 = 12;
    a2 = 0;
    jal(ctx, 0x3ECDC8u, gen::fn_sub_3E0C20_003e0c20);
    v0 = s1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x003ECDF0 sub_3ECDF0 -- 184 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Name-entry / menu sequence page (nm layer, the list object *0x7CE688): the page's per-frame check.
void sub_3ECDF0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ecdf0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(a0, a0, 52);
    if (a0 != 0) {
        // 0x003ece14
        charge(ctx, 3);
        lw(s2, a0, 20);
        if (s2 == 0) {
            goto L_003ece20;
        }
        // 0x003ece2c
        charge(ctx, 7);
        jal(ctx, 0x3ECE2Cu, gen::fn_sub_3C5470_003c5470);
        s0 = v0;
        lw(v0, s2, 20);
        v0 = v0 & 0x8;
        if (v0 == 0) {
            // 0x003ece48
            charge(ctx, 4);
            lw(v0, s0, 4);
            v0 = v0 & 0x1;
            if (v0 != 0) {
                goto L_003ece58;
            }
            // 0x003ece88
            charge(ctx, 1);
            v0 = si(-1);
            // 0x003ece8c (the shared epilogue, written out on this path)
            charge(ctx, 7);
            ld(ra, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x40);
            return;
        }
    L_003ece58:
        charge(ctx, 12);
        lw(a0, gp, -18024);  // 0x7CE688
        jal(ctx, 0x3ECE5Cu, gen::fn_nmObjPayloadWord12_003c5460);
        a0 = v0;
        a1 = 12;
        a2 = 1;
        jal(ctx, 0x3ECE70u, gen::fn_sub_3E0C20_003e0c20);
        sw(zero, s1, 52);
        lw(v0, s0, 0);
        // 0x003ece8c (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(ra, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
        return;
    }
L_003ece20:
    charge(ctx, 3);
    v0 = si(-1);
    // 0x003ece8c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003ED420 sub_3ED420 -- 184 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Name-entry / menu sequence page (nm layer, the list object *0x7CE688): the page's per-frame check.
void sub_3ED420(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ed420
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(a0, a0, 56);
    if (a0 != 0) {
        // 0x003ed444
        charge(ctx, 3);
        lw(s2, a0, 20);
        if (s2 == 0) {
            goto L_003ed450;
        }
        // 0x003ed45c
        charge(ctx, 7);
        jal(ctx, 0x3ED45Cu, gen::fn_sub_3C5470_003c5470);
        s0 = v0;
        lw(v0, s2, 20);
        v0 = v0 & 0x8;
        if (v0 == 0) {
            // 0x003ed478
            charge(ctx, 4);
            lw(v0, s0, 4);
            v0 = v0 & 0x1;
            if (v0 != 0) {
                goto L_003ed488;
            }
            // 0x003ed4b8
            charge(ctx, 1);
            v0 = si(-1);
            // 0x003ed4bc (the shared epilogue, written out on this path)
            charge(ctx, 7);
            ld(ra, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x40);
            return;
        }
    L_003ed488:
        charge(ctx, 12);
        lw(a0, gp, -18024);  // 0x7CE688
        jal(ctx, 0x3ED48Cu, gen::fn_nmObjPayloadWord12_003c5460);
        a0 = v0;
        a1 = 15;
        a2 = 1;
        jal(ctx, 0x3ED4A0u, gen::fn_sub_3E0C20_003e0c20);
        sw(zero, s1, 56);
        lw(v0, s0, 0);
        // 0x003ed4bc (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(ra, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
        return;
    }
L_003ed450:
    charge(ctx, 3);
    v0 = si(-1);
    // 0x003ed4bc (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003EDDD0 sub_3EDDD0 -- 176 bytes; frame 0x60: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Name-entry / menu sequence page (nm layer, the list object *0x7CE688): adds the page's step (table 0x6A7200).
void sub_3EDDD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x003eddd0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a1 = 0x6A0000;
    a1 = addiu(a1, 29184);  // &0x6A7200
    a0 = addiu(sp, 0x30);
    v1 = 2;
    for (;;) {
        // 0x003eddf4
        charge(ctx, 7);
        lq(v0, a1, 0);
        a1 = addiu(a1, 16);
        v1 = addiu(v1, -1);
        sq(v0, a0, 0);
        a0 = addiu(a0, 16);
        if (i64(v1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003ede10
    charge(ctx, 12);
    lwc1(f0, a1, 0);
    swc1(f0, a0, 0);
    lw(a0, gp, -18024);  // 0x7CE688
    a1 = 12;
    a2 = addiu(sp, 0x30);
    a3 = 0;
    t0 = 2;
    jal(ctx, 0x3EDE2Cu, gen::fn_nmSequenceAddStep_003c5240);
    s1 = v0;
    if (s0 != 0) {
        // 0x003ede40
        charge(ctx, 1);
        sw(s1, s0, 60);
    }
    // 0x003ede44
    charge(ctx, 15);
    lw(a0, gp, -18024);  // 0x7CE688
    jal(ctx, 0x3EDE48u, gen::fn_nmObjPayloadWord12_003c5460);
    a0 = v0;
    a1 = 5;
    a2 = 0;
    jal(ctx, 0x3EDE5Cu, gen::fn_sub_3E0C20_003e0c20);
    v0 = s1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x003EDE80 sub_3EDE80 -- 160 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Name-entry / menu sequence page (nm layer, the list object *0x7CE688): the page's per-frame check.
void sub_3EDE80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ede80
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(s0, a0, 60);
    if (s0 != 0) {
        // 0x003edea0
        charge(ctx, 3);
        lw(v0, s0, 20);
        if (v0 == 0) {
            goto L_003edeac;
        }
        // 0x003edeb8
        charge(ctx, 4);
        lw(v0, v0, 20);
        v0 = v0 & 0x8;
        if (v0 == 0) {
            // 0x003edf04
            charge(ctx, 1);
            v0 = si(-1);
        } else {
            // 0x003edec8
            charge(ctx, 15);
            lw(a0, gp, -18024);  // 0x7CE688
            jal(ctx, 0x3EDECCu, gen::fn_nmObjPayloadWord12_003c5460);
            a0 = v0;
            a1 = 5;
            a2 = 1;
            jal(ctx, 0x3EDEE0u, gen::fn_sub_3E0C20_003e0c20);
            a0 = s0;
            jal(ctx, 0x3EDEECu, gen::fn_sub_3C5470_003c5470);
            sw(zero, s1, 60);
            lw(v0, v0, 0);
        }
        // 0x003edf08 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(ra, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
L_003edeac:
    charge(ctx, 3);
    v0 = si(-1);
    // 0x003edf08 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003FC060 sub_3FC060 -- 1244 bytes; frame 0x90: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Facility panel text: formats and draws the panel lines (sprintf, sub_3B2CB0) for the selected entry.
void sub_3FC060(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x003fc060
    enter(ctx, 14);  // entry check point + this block's cycles
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
    lw(v0, a0, 4);
    v0 = v0 & 0x1;
    if (v0 != 0) {
        // 0x003fc0a4
        charge(ctx, 87);
        lh(s1, s4, 148);
        a0 = 0;
        a1 = 0;
        a2 = s1;
        a3 = 0;
        t0 = addiu(s4, 136);
        jal(ctx, 0x3FC0BCu, gen::fn_sub_3FCA00_003fca00);
        mtc1(zero, f12);
        a2 = s1 & 0xFF;
        a0 = 24;
        a1 = 75;
        a3 = 74;
        t0 = 0;
        jal(ctx, 0x3FC0DCu, gen::fn_sub_40E3C0_0040e3c0);
        mtc1(zero, f12);
        a2 = s1 & 0xFF;
        a0 = 24;
        a1 = 75;
        a3 = 76;
        t0 = 0;
        jal(ctx, 0x3FC0FCu, gen::fn_sub_40E3C0_0040e3c0);
        mtc1(zero, f12);
        a2 = s1 & 0xFF;
        a0 = 24;
        a1 = 75;
        a3 = 67;
        t0 = 0;
        jal(ctx, 0x3FC11Cu, gen::fn_sub_40E3C0_0040e3c0);
        mtc1(zero, f12);
        a2 = s1 & 0xFF;
        a0 = 55;
        a1 = 187;
        a3 = 73;
        t0 = 0;
        jal(ctx, 0x3FC13Cu, gen::fn_sub_40E3C0_0040e3c0);
        mtc1(zero, f12);
        a2 = s1 & 0xFF;
        a0 = 55;
        a1 = 187;
        a3 = 75;
        t0 = 0;
        jal(ctx, 0x3FC15Cu, gen::fn_sub_40E3C0_0040e3c0);
        mtc1(zero, f12);
        a2 = s1 & 0xFF;
        a0 = 55;
        a1 = 187;
        a3 = 68;
        t0 = 0;
        jal(ctx, 0x3FC17Cu, gen::fn_sub_40E3C0_0040e3c0);
        s0 = addiu(s4, 80);
        s2 = 200;
        mtc1(zero, f12);
        a2 = s1 & 0xFF;
        lbu(v0, s4, 84);
        t0 = sll(v0, 1);
        a0 = s2;
        a1 = 95;
        a3 = 0;
        jal(ctx, 0x3FC1A8u, gen::fn_sub_40E3C0_0040e3c0);
        v0 = si(-256);
        s5 = s1 | v0;
        lb(a1, s0, 8);
        lh(a0, s0, 0);
        jal(ctx, 0x3FC1C0u, gen::fn_sub_171110_00171110);
        mtc1(zero, f12);
        a0 = 232;
        a1 = 97;
        a2 = s5;
        a3 = 5;
        t0 = 1;
        t1 = v0;
        t2 = 0;
        t3 = 0;
        jal(ctx, 0x3FC1ECu, gen::fn_sub_3B2CB0_003b2cb0);
        s3 = 0;
        for (;;) {
            // 0x003fc340
            charge(ctx, 3);
            v0 = slti(s3, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003fc200
            charge(ctx, 6);
            v0 = sll(s3, 1);
            v0 = addu(s0, v0);
            s6 = addiu(v0, 16);
            lh(v0, v0, 16);
            if (v0 != 0) {
                // 0x003fc2a0
                charge(ctx, 38);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a0 = s2;
                a1 = 95;
                a3 = 69;
                t0 = 0;
                jal(ctx, 0x3FC2B8u, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a0 = s2;
                a1 = 95;
                a3 = 70;
                t0 = 0;
                jal(ctx, 0x3FC2D8u, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a0 = s2;
                a1 = 95;
                a3 = 78;
                t0 = s3;
                jal(ctx, 0x3FC2F8u, gen::fn_sub_40E3C0_0040e3c0);
                lh(a2, s6, 0);
                a0 = addiu(sp, 0x88);
                a1 = addiu(gp, -21488);  // "%d"
                jal(ctx, 0x3FC30Cu, gen::fn_sprintf_00523ac8);
                a0 = addiu(s2, 75);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a1 = 155;
                a3 = 2;
                t0 = addiu(sp, 0x88);
                t1 = 1;
                jal(ctx, 0x3FC330u, gen::fn_sub_40EB50_0040eb50);
            } else {
                // 0x003fc218
                charge(ctx, 34);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a0 = s2;
                a1 = 95;
                a3 = 71;
                t0 = 0;
                jal(ctx, 0x3FC230u, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a0 = s2;
                a1 = 95;
                a3 = 72;
                t0 = 0;
                jal(ctx, 0x3FC250u, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a0 = s2;
                a1 = 95;
                a3 = 77;
                t0 = s3;
                jal(ctx, 0x3FC270u, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a0 = s2;
                a1 = 95;
                a3 = 79;
                t0 = 0;
                jal(ctx, 0x3FC290u, gen::fn_sub_40E3C0_0040e3c0);
            }
            // 0x003fc338
            charge(ctx, 2);
            s2 = addiu(s2, 82);
            s3 = addiu(s3, 1);
        }
        // 0x003fc34c
        charge(ctx, 29);
        s0 = addiu(s4, 108);
        s2 = 200;
        mtc1(zero, f12);
        a2 = s1 & 0xFF;
        lbu(v0, s4, 112);
        t0 = sll(v0, 1);
        a0 = s2;
        a1 = 187;
        a3 = 0;
        jal(ctx, 0x3FC370u, gen::fn_sub_40E3C0_0040e3c0);
        lb(a1, s0, 8);
        lh(a0, s0, 0);
        jal(ctx, 0x3FC380u, gen::fn_sub_171110_00171110);
        mtc1(zero, f12);
        a0 = 232;
        a1 = 189;
        a2 = s5;
        a3 = 5;
        t0 = 1;
        t1 = v0;
        t2 = 0;
        t3 = 0;
        jal(ctx, 0x3FC3ACu, gen::fn_sub_3B2CB0_003b2cb0);
        s4 = 0;
        for (;;) {
            // 0x003fc500
            charge(ctx, 3);
            v0 = slti(s4, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003fc3c0
            charge(ctx, 6);
            v0 = sll(s4, 1);
            v0 = addu(s0, v0);
            s3 = addiu(v0, 16);
            lh(v0, v0, 16);
            if (v0 != 0) {
                // 0x003fc460
                charge(ctx, 38);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a0 = s2;
                a1 = 187;
                a3 = 69;
                t0 = 0;
                jal(ctx, 0x3FC478u, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a0 = s2;
                a1 = 187;
                a3 = 70;
                t0 = 0;
                jal(ctx, 0x3FC498u, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a0 = s2;
                a1 = 187;
                a3 = 78;
                t0 = s4;
                jal(ctx, 0x3FC4B8u, gen::fn_sub_40E3C0_0040e3c0);
                lh(a2, s3, 0);
                a0 = addiu(sp, 0x88);
                a1 = addiu(gp, -21488);  // "%d"
                jal(ctx, 0x3FC4CCu, gen::fn_sprintf_00523ac8);
                a0 = addiu(s2, 75);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a1 = 247;
                a3 = 2;
                t0 = addiu(sp, 0x88);
                t1 = 1;
                jal(ctx, 0x3FC4F0u, gen::fn_sub_40EB50_0040eb50);
            } else {
                // 0x003fc3d8
                charge(ctx, 34);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a0 = s2;
                a1 = 187;
                a3 = 71;
                t0 = 0;
                jal(ctx, 0x3FC3F0u, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a0 = s2;
                a1 = 187;
                a3 = 72;
                t0 = 0;
                jal(ctx, 0x3FC410u, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a0 = s2;
                a1 = 187;
                a3 = 77;
                t0 = s4;
                jal(ctx, 0x3FC430u, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a0 = s2;
                a1 = 187;
                a3 = 79;
                t0 = 0;
                jal(ctx, 0x3FC450u, gen::fn_sub_40E3C0_0040e3c0);
            }
            // 0x003fc4f8
            charge(ctx, 2);
            s2 = addiu(s2, 82);
            s4 = addiu(s4, 1);
        }
        // 0x003fc50c
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003fc098
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003fc510 (the shared epilogue, written out on this path)
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

// 0x003FC540 sub_3FC540 -- 1088 bytes; frame 0x90: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Facility panel text: as sub_3FC060 for the second panel.
void sub_3FC540(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x003fc540
    enter(ctx, 14);  // entry check point + this block's cycles
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
    lw(v0, a0, 4);
    v0 = v0 & 0x1;
    if (v0 != 0) {
        // 0x003fc584
        charge(ctx, 80);
        lh(s1, s4, 148);
        mtc1(zero, f12);
        a2 = s1 & 0xFF;
        a0 = 43;
        a1 = 28;
        a3 = 66;
        t0 = 0;
        jal(ctx, 0x3FC5A0u, gen::fn_sub_40E3C0_0040e3c0);
        mtc1(zero, f12);
        a2 = s1 & 0xFF;
        a0 = 43;
        a1 = 28;
        a3 = 68;
        t0 = 0;
        jal(ctx, 0x3FC5C0u, gen::fn_sub_40E3C0_0040e3c0);
        mtc1(zero, f12);
        a2 = s1 & 0xFF;
        a0 = 43;
        a1 = 28;
        a3 = 58;
        t0 = 0;
        jal(ctx, 0x3FC5E0u, gen::fn_sub_40E3C0_0040e3c0);
        mtc1(zero, f12);
        a2 = s1 & 0xFF;
        a0 = 43;
        a1 = 176;
        a3 = 65;
        t0 = 0;
        jal(ctx, 0x3FC600u, gen::fn_sub_40E3C0_0040e3c0);
        mtc1(zero, f12);
        a2 = s1 & 0xFF;
        a0 = 43;
        a1 = 176;
        a3 = 67;
        t0 = 0;
        jal(ctx, 0x3FC620u, gen::fn_sub_40E3C0_0040e3c0);
        mtc1(zero, f12);
        a2 = s1 & 0xFF;
        a0 = 43;
        a1 = 176;
        a3 = 59;
        t0 = 0;
        jal(ctx, 0x3FC640u, gen::fn_sub_40E3C0_0040e3c0);
        s0 = addiu(s4, 80);
        s2 = 78;
        mtc1(zero, f12);
        a2 = s1 & 0xFF;
        lbu(v0, s4, 84);
        t0 = sll(v0, 1);
        a0 = s2;
        a1 = 68;
        a3 = 0;
        jal(ctx, 0x3FC66Cu, gen::fn_sub_40E3C0_0040e3c0);
        v0 = si(-256);
        s5 = s1 | v0;
        lb(a1, s0, 8);
        lh(a0, s0, 0);
        jal(ctx, 0x3FC684u, gen::fn_sub_171110_00171110);
        mtc1(zero, f12);
        a0 = 110;
        a1 = 70;
        a2 = s5;
        a3 = 5;
        t0 = 1;
        t1 = v0;
        t2 = 0;
        t3 = 0;
        jal(ctx, 0x3FC6B0u, gen::fn_sub_3B2CB0_003b2cb0);
        s3 = 0;
        for (;;) {
            // 0x003fc7c4
            charge(ctx, 3);
            v0 = slti(s3, 5);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003fc6c4
            charge(ctx, 6);
            v0 = sll(s3, 1);
            v0 = addu(s0, v0);
            s6 = addiu(v0, 16);
            lh(v0, v0, 16);
            if (v0 != 0) {
                // 0x003fc744
                charge(ctx, 30);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a0 = s2;
                a1 = 68;
                a3 = 62;
                t0 = 0;
                jal(ctx, 0x3FC75Cu, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a0 = s2;
                a1 = 68;
                a3 = 70;
                t0 = s3;
                jal(ctx, 0x3FC77Cu, gen::fn_sub_40E3C0_0040e3c0);
                lh(a2, s6, 0);
                a0 = addiu(sp, 0x88);
                a1 = addiu(gp, -21488);  // "%d"
                jal(ctx, 0x3FC790u, gen::fn_sprintf_00523ac8);
                a0 = addiu(s2, 26);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a1 = 140;
                a3 = 2;
                t0 = addiu(sp, 0x88);
                t1 = 1;
                jal(ctx, 0x3FC7B4u, gen::fn_sub_40EB50_0040eb50);
            } else {
                // 0x003fc6dc
                charge(ctx, 26);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a0 = s2;
                a1 = 68;
                a3 = 64;
                t0 = 0;
                jal(ctx, 0x3FC6F4u, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a0 = s2;
                a1 = 68;
                a3 = 69;
                t0 = s3;
                jal(ctx, 0x3FC714u, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a0 = s2;
                a1 = 68;
                a3 = 71;
                t0 = 0;
                jal(ctx, 0x3FC734u, gen::fn_sub_40E3C0_0040e3c0);
            }
            // 0x003fc7bc
            charge(ctx, 2);
            s2 = addiu(s2, 66);
            s3 = addiu(s3, 1);
        }
        // 0x003fc7d0
        charge(ctx, 29);
        s0 = addiu(s4, 108);
        s2 = 78;
        mtc1(zero, f12);
        a2 = s1 & 0xFF;
        lbu(v0, s4, 112);
        t0 = sll(v0, 1);
        a0 = s2;
        a1 = 216;
        a3 = 0;
        jal(ctx, 0x3FC7F4u, gen::fn_sub_40E3C0_0040e3c0);
        lb(a1, s0, 8);
        lh(a0, s0, 0);
        jal(ctx, 0x3FC804u, gen::fn_sub_171110_00171110);
        mtc1(zero, f12);
        a0 = 110;
        a1 = 218;
        a2 = s5;
        a3 = 5;
        t0 = 1;
        t1 = v0;
        t2 = 0;
        t3 = 0;
        jal(ctx, 0x3FC830u, gen::fn_sub_3B2CB0_003b2cb0);
        s4 = 0;
        for (;;) {
            // 0x003fc944
            charge(ctx, 3);
            v0 = slti(s4, 5);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003fc844
            charge(ctx, 6);
            v0 = sll(s4, 1);
            v0 = addu(s0, v0);
            s3 = addiu(v0, 16);
            lh(v0, v0, 16);
            if (v0 != 0) {
                // 0x003fc8c4
                charge(ctx, 30);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a0 = s2;
                a1 = 216;
                a3 = 62;
                t0 = 0;
                jal(ctx, 0x3FC8DCu, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a0 = s2;
                a1 = 216;
                a3 = 70;
                t0 = s4;
                jal(ctx, 0x3FC8FCu, gen::fn_sub_40E3C0_0040e3c0);
                lh(a2, s3, 0);
                a0 = addiu(sp, 0x88);
                a1 = addiu(gp, -21488);  // "%d"
                jal(ctx, 0x3FC910u, gen::fn_sprintf_00523ac8);
                a0 = addiu(s2, 26);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a1 = 288;
                a3 = 2;
                t0 = addiu(sp, 0x88);
                t1 = 1;
                jal(ctx, 0x3FC934u, gen::fn_sub_40EB50_0040eb50);
            } else {
                // 0x003fc85c
                charge(ctx, 26);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a0 = s2;
                a1 = 216;
                a3 = 64;
                t0 = 0;
                jal(ctx, 0x3FC874u, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a0 = s2;
                a1 = 216;
                a3 = 69;
                t0 = s4;
                jal(ctx, 0x3FC894u, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a0 = s2;
                a1 = 216;
                a3 = 71;
                t0 = 0;
                jal(ctx, 0x3FC8B4u, gen::fn_sub_40E3C0_0040e3c0);
            }
            // 0x003fc93c
            charge(ctx, 2);
            s2 = addiu(s2, 66);
            s4 = addiu(s4, 1);
        }
        // 0x003fc950
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003fc578
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003fc954 (the shared epilogue, written out on this path)
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

// 0x003FD820 sub_3FD820 -- 120 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// nm step: sub_3C44D0, sub_3DFEB0, sub_3FD570.
void sub_3FD820(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003fd820
    enter(ctx, 30);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    a0 = 12;
    a1 = 0;
    a2 = 0x400000;
    a2 = addiu(a2, -10272);  // &sub_3FD7E0
    a3 = 0;
    jal(ctx, 0x3FD848u, gen::fn_sub_3C44D0_003c44d0);
    lw(s0, v0, 36);
    sw(v0, s0, 0);
    sw(s1, s0, 4);
    a0 = 0;
    jal(ctx, 0x3FD860u, gen::fn_sub_3DFEB0_003dfeb0);
    sw(v0, s0, 8);
    a0 = s1;
    a1 = s0;
    jal(ctx, 0x3FD874u, gen::fn_sub_3FD570_003fd570);
    v0 = s0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x004030B0 sub_4030B0 -- 64 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// nm page hook: sub_402C80 then sub_4037A0.
void sub_4030B0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004030b0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = dsll32(a0, 16);
    s0 = dsra32(s0, 16);
    a0 = s0;
    jal(ctx, 0x4030C8u, gen::fn_sub_402C80_00402c80);
    a0 = s0;
    jal(ctx, 0x4030D4u, gen::fn_sub_4037A0_004037a0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x004030F0 sub_4030F0 -- 64 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// nm page hook: sub_402C80 then sub_4037C0.
void sub_4030F0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004030f0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = dsll32(a0, 16);
    s0 = dsra32(s0, 16);
    a0 = s0;
    jal(ctx, 0x403108u, gen::fn_sub_402C80_00402c80);
    a0 = s0;
    jal(ctx, 0x403114u, gen::fn_sub_4037C0_004037c0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00403130 sub_403130 -- 236 bytes; frame 0x90: ra sp+0x80, s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// Opens a facility page: sets a game flag (datSetFlag), sub_402800, sub_403760, sub_3C7E20.
void sub_403130(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12}, f20{ctx, 20};
    // 0x00403130
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
    s3 = a2;
    s2 = a3;
    s1 = t0;
    s6 = t1;
    s0 = t2;
    a0 = 5156;
    a1 = 1;
    jal(ctx, 0x40317Cu, gen::fn_datSetFlag_0016f1f0);
    a0 = dsll32(s0, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x40318Cu, gen::fn_sub_402800_00402800);
    a0 = 5156;
    a1 = 0;
    jal(ctx, 0x40319Cu, gen::fn_datSetFlag_0016f1f0);
    mtc1(s3, f0);
    cvt_s_w(f20, f0);
    a0 = dsll32(s0, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x4031B8u, gen::fn_sub_403760_00403760);
    t2 = dsll32(v0, 16);
    t2 = dsra32(t2, 16);
    a0 = s5;
    a1 = s4;
    mov_s(f12, f20);
    a2 = s2;
    a3 = s1;
    t0 = s6;
    t1 = 6;
    jal(ctx, 0x4031E4u, gen::fn_sub_3C7E20_003c7e20);
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

// 0x00403220 sub_403220 -- 204 bytes; frame 0x90: ra sp+0x80, s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// Opens a facility page: sub_402800, sub_403780, sub_3C7E20.
void sub_403220(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12}, f20{ctx, 20};
    // 0x00403220
    enter(ctx, 51);  // entry check point + this block's cycles
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
    s3 = a2;
    s2 = a3;
    s1 = t0;
    s6 = t1;
    s0 = t2;
    a0 = dsll32(s0, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x40326Cu, gen::fn_sub_402800_00402800);
    mtc1(s3, f0);
    cvt_s_w(f20, f0);
    a0 = dsll32(s0, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x403288u, gen::fn_sub_403780_00403780);
    t2 = dsll32(v0, 16);
    t2 = dsra32(t2, 16);
    a0 = s5;
    a1 = s4;
    mov_s(f12, f20);
    a2 = s2;
    a3 = s1;
    t0 = s6;
    t1 = 6;
    jal(ctx, 0x4032B4u, gen::fn_sub_3C7E20_003c7e20);
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

// 0x00403E40 sub_403E40 -- 212 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// nm page hook: sub_17C670 then sub_403970.
void sub_403E40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00403e40
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s0 = 0;
    for (;;) {
        // 0x00403ee8
        charge(ctx, 3);
        v0 = slti(s0, 3);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00403e68
        charge(ctx, 5);
        a0 = s0;
        jal(ctx, 0x403E6Cu, gen::fn_sub_17C670_0017c670);
        if (v0 != 0) {
            // 0x00403e7c
            charge(ctx, 4);
            lh(a0, v0, 0);
            v1 = 0;
            for (;;) {
                // 0x00403eb0
                charge(ctx, 3);
                v0 = slt(v1, s1);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00403e8c
                charge(ctx, 5);
                v0 = sll(v1, 1);
                v0 = addu(s2, v0);
                lh(v0, v0, 0);
                if (a0 == v0) {
                    goto L_00403ea0_4;
                }
                // 0x00403eac
                charge(ctx, 1);
                v1 = addiu(v1, 1);
            }
            // 0x00403ebc
            charge(ctx, 1);
            v0 = 0;
        L_00403ec0:
            charge(ctx, 2);
            if (v0 != 0) {
                goto L_00403ee4;
            }
            // 0x00403ec8
            charge(ctx, 4);
            jal(ctx, 0x403EC8u, gen::fn_sub_403970_00403970);
            if (v0 == 0) {
                goto L_00403ee4;
            }
            goto L_00403ed8_10;
        }
    L_00403ee4:
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x00403ef4
    charge(ctx, 1);
    v0 = 0;
    // 0x00403ef8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
    return;
L_00403ea0_4:
    charge(ctx, 3);
    v0 = 1;
    goto L_00403ec0;
L_00403ed8_10:
    charge(ctx, 3);
    v0 = 1;
    // 0x00403ef8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00403F20 sub_403F20 -- 508 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Calendar / date step for a page: the date helpers sub_171250 .. sub_16E9B0.
void sub_403F20(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00403f20
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    v0 = dsll32(a0, 16);
    v0 = dsra32(v0, 16);
    v1 = sll(v0, 6);
    lw(v0, gp, -21504);  // 0x7CD8F0
    v0 = addu(v0, v1);
    s0 = addiu(v0, 32);
    lbu(v1, v0, 38);
    v0 = 3;
    if (v1 == v0) {
        // 0x004040cc
        charge(ctx, 2);
        if (s1 != 0) {
            // 0x004040f4
            charge(ctx, 3);
            lw(a0, s0, 8);
            jal(ctx, 0x4040F8u, gen::fn_sub_16E9B0_0016e9b0);
        L_00404100:
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x004040d4
            charge(ctx, 5);
            lw(a0, s0, 8);
            jal(ctx, 0x4040D8u, gen::fn_sub_16EA40_0016ea40);
            if (i64(v0) <= 0) {
                goto L_00404100;
            }
            // 0x004040e8
            charge(ctx, 3);
            v0 = 2;
        }
    } else {
        // 0x00403f5c
        charge(ctx, 3);
        v0 = 2;
        if (v1 == v0) {
            // 0x004040ac
            charge(ctx, 5);
            lhu(a0, s0, 8);
            jal(ctx, 0x4040B0u, gen::fn_sub_174E70_00174e70);
            if (v0 != 0) {
                goto L_00404100;
            }
            // 0x004040c0
            charge(ctx, 3);
            v0 = 3;
        } else {
            // 0x00403f68
            charge(ctx, 2);
            if (v1 != 0) {
                // 0x00403f70
                charge(ctx, 2);
                goto L_00404100;
            }
            // 0x00403f78
            charge(ctx, 6);
            lh(a0, s0, 8);
            jal(ctx, 0x403F7Cu, gen::fn_sub_171250_00171250);
            v1 = 4;
            if (v0 == v1) {
                // 0x00403f98
                charge(ctx, 2);
                if (s1 != 0) {
                    // 0x00403fa0
                    charge(ctx, 5);
                    lhu(a0, s0, 8);
                    jal(ctx, 0x403FA4u, gen::fn_sub_171360_00171360);
                    if (v0 == 0) {
                        // 0x00403fc8
                        charge(ctx, 7);
                        lbu(a2, s0, 7);
                        a0 = 1;
                        lh(a1, s0, 8);
                        jal(ctx, 0x403FD4u, gen::fn_sub_170C00_00170c00);
                    } else {
                        // 0x00403fb4
                        charge(ctx, 5);
                        lhu(a0, s0, 8);
                        jal(ctx, 0x403FB8u, gen::fn_sub_171390_00171390);
                    }
                }
                goto L_00404100;
            }
            // 0x00403f90
            charge(ctx, 2);
            // 0x00403fe4
            charge(ctx, 2);
            if (s1 != 0) {
                // 0x0040401c
                charge(ctx, 5);
                a2 = 0;
                lhu(v1, s0, 4);
                v0 = v1 & 0x1;
                if (v0 != 0) {
                    // 0x00404030
                    charge(ctx, 1);
                    a2 = a2 | 0x1;
                }
                // 0x00404034
                charge(ctx, 3);
                v0 = v1 & 0x2;
                if (v0 != 0) {
                    // 0x00404040
                    charge(ctx, 1);
                    a2 = a2 | 0x2;
                }
                // 0x00404044
                charge(ctx, 3);
                v0 = v1 & 0x4;
                if (v0 != 0) {
                    // 0x00404050
                    charge(ctx, 1);
                    a2 = a2 | 0x4;
                }
                // 0x00404054
                charge(ctx, 19);
                lb(v0, s0, 10);
                v0 = dsll32(v0, 28);
                v0 = dsra32(v0, 28);
                v0 = v0 & 0xF;
                v1 = sll(v0, 24);
                lh(v0, s0, 10);
                v0 = dsll32(v0, 20);
                v0 = dsra32(v0, 24);
                v0 = v0 & 0xFF;
                v0 = sll(v0, 16);
                v1 = v1 | v0;
                lh(v0, s0, 8);
                v0 = v0 & 0xFFFF;
                a0 = v0 | v1;
                lbu(a1, s0, 7);
                jal(ctx, 0x404090u, gen::fn_sub_4026B0_004026b0);
                if (v0 != 0) {
                    goto L_00404100;
                }
                // 0x004040a0
                charge(ctx, 3);
                v0 = 1;
            } else {
                // 0x00403fec
                charge(ctx, 9);
                a0 = 1;
                jal(ctx, 0x403FF0u, gen::fn_sub_16F490_0016f490);
                v1 = 300;
                v1 = subu(v1, v0);
                lbu(v0, s0, 7);
                at = slt(v1, v0);
                if (at == 0) {
                    goto L_00404100;
                }
                // 0x00404010
                charge(ctx, 3);
                v0 = 1;
            }
        }
    }
    // 0x00404104 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x004044C0 sub_4044C0 -- 268 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// "fclShopMisc.c": the shop page close / commit step (datSetFlag, sub_404120, sub_3F0D60).
void sub_4044C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004044c0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = dsll32(a0, 16);
    a0 = dsra32(a0, 16);
    s1 = sll(a0, 6);
    jal(ctx, 0x4044DCu, gen::fn_sub_17C610_0017c610);
    s0 = v0;
    if (s0 == 0) {
        // 0x004044f0
        charge(ctx, 5);
        a0 = 0x6B0000;
        a0 = addiu(a0, -4632);  // "fclShopMisc.c"
        a1 = 7824;
        jal(ctx, 0x4044FCu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00404504
    charge(ctx, 15);
    lh(a0, s0, 0);
    a1 = 1;
    jal(ctx, 0x40450Cu, gen::fn_sub_404120_00404120);
    lh(v0, s0, 0);
    a0 = addiu(v0, 4464);
    a1 = 1;
    jal(ctx, 0x404520u, gen::fn_datSetFlag_0016f1f0);
    lw(v0, gp, -21504);  // 0x7CD8F0
    v0 = addu(v0, s1);
    lhu(a0, v0, 20);
    v0 = 0xFFFF;
    if (a0 != v0) {
        // 0x00404540
        charge(ctx, 3);
        a1 = 0;
        jal(ctx, 0x404544u, gen::fn_datSetFlag_0016f1f0);
    }
    // 0x0040454c
    charge(ctx, 8);
    lh(v0, s0, 0);
    v1 = sll(v0, 6);
    lw(v0, gp, -21504);  // 0x7CD8F0
    v0 = addu(v0, v1);
    lhu(a0, v0, 22);
    v0 = 0xFFFF;
    if (a0 != v0) {
        // 0x0040456c
        charge(ctx, 3);
        a1 = 1;
        jal(ctx, 0x404570u, gen::fn_datSetFlag_0016f1f0);
    }
    // 0x00404578
    charge(ctx, 21);
    lh(a0, s0, 0);
    jal(ctx, 0x40457Cu, gen::fn_sub_17C590_0017c590);
    lw(v1, gp, -21504);  // 0x7CD8F0
    lh(v0, s0, 0);
    v0 = sll(v0, 6);
    v0 = addu(v0, v1);
    lh(s0, v0, 56);
    jal(ctx, 0x404598u, gen::fn_sub_3E6DC0_003e6dc0);
    a1 = dsll32(s0, 16);
    a1 = dsra32(a1, 16);
    a0 = v0;
    jal(ctx, 0x4045ACu, gen::fn_sub_3F0D60_003f0d60);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0040B3A0 sub_40B3A0 -- 648 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Facility menu draw callback (data-referenced): sub_40E3C0, sub_3C7E20, sub_3B32D0.
void sub_40B3A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x0040b3a0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lh(s1, a1, 20);
    lh(s0, a1, 22);
    lh(s3, a1, 38);
    if (s3 != 0) {
        // 0x0040b3d4
        charge(ctx, 4);
        lw(a0, a1, 16);
        v1 = 12;
        if (a0 == v1) {
            // 0x0040b52c
            charge(ctx, 53);
            lw(v0, a2, 16);
            lw(v0, v0, 20);
            lw(s2, v0, 28);
            mtc1(zero, f12);
            a2 = s3 & 0xFF;
            a0 = s1;
            a1 = s0;
            a3 = 158;
            t0 = 0;
            jal(ctx, 0x40B550u, gen::fn_sub_40E3C0_0040e3c0);
            mtc1(zero, f12);
            a2 = s3 & 0xFF;
            a0 = s1;
            a1 = s0;
            a3 = 159;
            t0 = 0;
            jal(ctx, 0x40B570u, gen::fn_sub_40E3C0_0040e3c0);
            a0 = addiu(s1, 349);
            a1 = addiu(s0, 77);
            mtc1(zero, f12);
            a2 = s3 & 0xFF;
            lw(v0, s2, 4);
            lhu(v1, v0, 2);
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v1 = sll(v0, 1);
            lw(v0, gp, -18640);  // 0x7CE420
            v0 = addu(v1, v0);
            lbu(v0, v0, 2);
            v0 = addiu(v0, -1);
            v0 = sll(v0, 1);
            t0 = addiu(v0, 1);
            a3 = 157;
            jal(ctx, 0x40B5B8u, gen::fn_sub_40E3C0_0040e3c0);
            a0 = addiu(s1, 431);
            a1 = addiu(s0, 72);
            mtc1(zero, f12);
            lw(v0, s2, 4);
            lhu(v1, v0, 2);
            v0 = sll(v1, 4);
            v1 = addu(v0, v1);
            lw(v0, gp, -18444);  // 0x7CE4E4
            t1 = addu(v0, v1);
            a2 = si(-1);
            a3 = 5;
            t0 = 1;
            t2 = 0;
            t3 = 120;
            jal(ctx, 0x40B5F8u, gen::fn_sub_3B32D0_003b32d0);
        } else {
            // 0x0040b3e4
            charge(ctx, 3);
            v1 = 11;
            if (a0 == v1) {
                // 0x0040b3f8
                charge(ctx, 22);
                lw(v0, a2, 16);
                lw(v0, v0, 20);
                lw(s2, v0, 28);
                mtc1(zero, f12);
                a2 = s3 & 0xFF;
                a0 = s1;
                a1 = s0;
                a3 = 160;
                t0 = 0;
                jal(ctx, 0x40B41Cu, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s3 & 0xFF;
                a0 = s1;
                a1 = s0;
                a3 = 161;
                t0 = 0;
                jal(ctx, 0x40B43Cu, gen::fn_sub_40E3C0_0040e3c0);
                s4 = 0;
                for (;;) {
                    // 0x0040b4a8
                    charge(ctx, 3);
                    v0 = slti(s4, 9);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0040b450
                    charge(ctx, 22);
                    v0 = sll(s4, 2);
                    v1 = addu(v0, s4);
                    v0 = sll(v1, 2);
                    v0 = addu(v1, v0);
                    s5 = addu(s0, v0);
                    mtc1(zero, f12);
                    a2 = s3 & 0xFF;
                    a0 = s1;
                    a1 = s5;
                    a3 = 162;
                    t0 = 0;
                    jal(ctx, 0x40B47Cu, gen::fn_sub_40E3C0_0040e3c0);
                    mtc1(zero, f12);
                    a2 = s3 & 0xFF;
                    a0 = s1;
                    a1 = s5;
                    a3 = 163;
                    t0 = 0;
                    jal(ctx, 0x40B49Cu, gen::fn_sub_40E3C0_0040e3c0);
                    s4 = addiu(s4, 1);
                }
                // 0x0040b4b4
                charge(ctx, 30);
                mtc1(zero, f12);
                a2 = s3 & 0xFF;
                a0 = s1;
                a1 = s0;
                a3 = 164;
                t0 = 0;
                jal(ctx, 0x40B4CCu, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s3 & 0xFF;
                a0 = s1;
                a1 = s0;
                a3 = 165;
                t0 = 0;
                jal(ctx, 0x40B4ECu, gen::fn_sub_40E3C0_0040e3c0);
                a0 = addiu(s1, 364);
                a1 = addiu(s0, 119);
                mtc1(zero, f12);
                v0 = si(-256);
                a2 = s3 | v0;
                lw(v0, s2, 4);
                lhu(t2, v0, 2);
                a3 = 1;
                t0 = 6;
                t1 = 4;
                jal(ctx, 0x40B51Cu, gen::fn_sub_3C7E20_003c7e20);
            } else {
                // 0x0040b3f0
                charge(ctx, 2);
            }
        }
    }
    // 0x0040b600 (the shared epilogue, written out on this path)
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

// 0x00414770 sub_414770 -- 308 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Facility menu draw callback (data-referenced): text line through sub_171110 / sub_3B2CB0.
void sub_414770(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x00414770
    enter(ctx, 77);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a2;
    s1 = a3;
    s4 = t0;
    s0 = t1;
    lw(s3, a1, 12);
    mtc1(s4, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s2, 313);
    a1 = addiu(s1, 39);
    a2 = s0 & 0xFF;
    a3 = 138;
    t0 = 0;
    jal(ctx, 0x4147C0u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(s4, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s2, 313);
    a1 = addiu(s1, 39);
    a2 = s0 & 0xFF;
    a3 = 139;
    t0 = 0;
    jal(ctx, 0x4147E8u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(s4, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s2, 313);
    a1 = addiu(s1, 39);
    a2 = s0 & 0xFF;
    a3 = 140;
    t0 = 0;
    jal(ctx, 0x414810u, gen::fn_sub_40E3C0_0040e3c0);
    a0 = addiu(s2, 362);
    a1 = addiu(s1, 42);
    mtc1(zero, f12);
    a2 = s0 & 0xFF;
    lbu(v0, s3, 124);
    v0 = sll(v0, 1);
    t0 = addiu(v0, 1);
    a3 = 0;
    jal(ctx, 0x414838u, gen::fn_sub_40E3C0_0040e3c0);
    lh(a0, s3, 120);
    a1 = 2;
    jal(ctx, 0x414848u, gen::fn_sub_171110_00171110);
    a0 = addiu(s2, 394);
    a1 = addiu(s1, 44);
    mtc1(zero, f12);
    v1 = si(-256);
    a2 = s0 | v1;
    a3 = 6;
    t0 = 1;
    t1 = v0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x414878u, gen::fn_sub_3B2CB0_003b2cb0);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00416240 sub_416240 -- 420 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Facility menu draw callback (data-referenced): text line through sub_171110 / sub_3B2CB0.
void sub_416240(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x00416240
    enter(ctx, 105);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s5 = a2;
    s6 = a3;
    s4 = t0;
    s3 = t1;
    lw(v0, a1, 12);
    s0 = addiu(v0, 80);
    s2 = addiu(s5, 56);
    s1 = addiu(s6, 43);
    mtc1(s4, f0);
    cvt_s_w(f12, f0);
    a2 = s3 & 0xFF;
    a0 = s2;
    a1 = s1;
    a3 = 164;
    t0 = 0;
    jal(ctx, 0x4162A4u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(s4, f0);
    cvt_s_w(f12, f0);
    a2 = s3 & 0xFF;
    a0 = s2;
    a1 = s1;
    a3 = 165;
    t0 = 0;
    jal(ctx, 0x4162CCu, gen::fn_sub_40E3C0_0040e3c0);
    a0 = addiu(s2, 11);
    a1 = addiu(s1, 18);
    mtc1(zero, f12);
    a2 = s3 & 0xFF;
    lbu(v0, s0, 4);
    t0 = sll(v0, 1);
    a3 = 0;
    jal(ctx, 0x4162F0u, gen::fn_sub_40E3C0_0040e3c0);
    lb(a1, s0, 8);
    lh(a0, s0, 0);
    jal(ctx, 0x416300u, gen::fn_sub_171110_00171110);
    a0 = addiu(s2, 43);
    a1 = addiu(s1, 20);
    mtc1(zero, f12);
    v1 = si(-256);
    a2 = s3 | v1;
    a3 = 5;
    t0 = 1;
    t1 = v0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x416330u, gen::fn_sub_3B2CB0_003b2cb0);
    s1 = addiu(s5, -21);
    s0 = addiu(s6, -26);
    mtc1(s4, f0);
    cvt_s_w(f12, f0);
    a2 = s3 & 0xFF;
    a0 = s1;
    a1 = s0;
    a3 = 161;
    t0 = 0;
    jal(ctx, 0x416360u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(s4, f0);
    cvt_s_w(f12, f0);
    a2 = s3 & 0xFF;
    a0 = s1;
    a1 = s0;
    a3 = 162;
    t0 = 0;
    jal(ctx, 0x416388u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(s4, f0);
    cvt_s_w(f12, f0);
    a2 = s3 & 0xFF;
    a0 = s1;
    a1 = s0;
    a3 = 163;
    t0 = 0;
    jal(ctx, 0x4163B0u, gen::fn_sub_40E3C0_0040e3c0);
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

// 0x004163F0 sub_4163F0 -- 728 bytes; frame 0x90: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Facility menu draw callback (data-referenced): formatted number (sprintf) through sub_40EB50 / sub_3B32D0.
void sub_4163F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x004163f0
    enter(ctx, 103);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s5 = a2;
    s6 = a3;
    s4 = t0;
    s3 = t1;
    lw(v0, a1, 12);
    s0 = addiu(v0, 108);
    s2 = addiu(s5, 334);
    s1 = addiu(s6, 43);
    mtc1(s4, f0);
    cvt_s_w(f12, f0);
    a2 = s3 & 0xFF;
    a0 = s2;
    a1 = s1;
    a3 = 169;
    t0 = 0;
    jal(ctx, 0x416454u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(s4, f0);
    cvt_s_w(f12, f0);
    a2 = s3 & 0xFF;
    a0 = s2;
    a1 = s1;
    a3 = 170;
    t0 = 0;
    jal(ctx, 0x41647Cu, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(s4, f0);
    cvt_s_w(f12, f0);
    a1 = addiu(s1, 1);
    a2 = s3 & 0xFF;
    a0 = s2;
    a3 = 171;
    t0 = 0;
    jal(ctx, 0x4164A4u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(s4, f0);
    cvt_s_w(f12, f0);
    a1 = addiu(s1, 1);
    a2 = s3 & 0xFF;
    a0 = s2;
    a3 = 172;
    t0 = 0;
    jal(ctx, 0x4164CCu, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(s4, f0);
    cvt_s_w(f12, f0);
    a2 = s3 & 0xFF;
    a0 = s2;
    a1 = s1;
    a3 = 173;
    t0 = 0;
    jal(ctx, 0x4164F4u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(s4, f0);
    cvt_s_w(f12, f0);
    a2 = s3 & 0xFF;
    a0 = s2;
    a1 = s1;
    a3 = 174;
    t0 = 0;
    jal(ctx, 0x41651Cu, gen::fn_sub_40E3C0_0040e3c0);
    a0 = addiu(s2, 88);
    a1 = addiu(s1, 7);
    mtc1(zero, f12);
    a2 = s3 & 0xFF;
    lhu(v1, s0, 2);
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    v1 = sll(v0, 1);
    lw(v0, gp, -18640);  // 0x7CE420
    v0 = addu(v1, v0);
    lbu(v0, v0, 2);
    v0 = addiu(v0, -1);
    v0 = sll(v0, 1);
    t0 = addiu(v0, 1);
    a3 = 3;
    jal(ctx, 0x416560u, gen::fn_sub_40E3C0_0040e3c0);
    lbu(a2, s0, 4);
    a0 = addiu(sp, 0x88);
    a1 = addiu(gp, -21152);  // "%d"
    jal(ctx, 0x416574u, gen::fn_sprintf_00523ac8);
    lbu(v0, s0, 4);
    at = slti(v0, 10);
    if (at == 0) {
        // 0x004165b8
        charge(ctx, 9);
        a0 = addiu(s2, 66);
        a1 = addiu(s1, 36);
        mtc1(zero, f12);
        a2 = s3 & 0xFF;
        a3 = 2;
        t0 = addiu(sp, 0x88);
        t1 = a3;
        jal(ctx, 0x4165D4u, gen::fn_sub_40EB50_0040eb50);
    } else {
        // 0x0041658c
        charge(ctx, 11);
        a0 = addiu(s2, 71);
        a1 = addiu(s1, 36);
        mtc1(zero, f12);
        a2 = s3 & 0xFF;
        a3 = 2;
        t0 = addiu(sp, 0x88);
        t1 = a3;
        jal(ctx, 0x4165A8u, gen::fn_sub_40EB50_0040eb50);
    }
    // 0x004165dc
    charge(ctx, 59);
    a0 = addiu(s2, 96);
    a1 = addiu(s1, 27);
    mtc1(zero, f12);
    v0 = si(-256);
    a2 = s3 | v0;
    lhu(v1, s0, 2);
    v0 = sll(v1, 4);
    v1 = addu(v0, v1);
    lw(v0, gp, -18444);  // 0x7CE4E4
    t1 = addu(v0, v1);
    a3 = 5;
    t0 = 1;
    t2 = 0;
    t3 = 120;
    jal(ctx, 0x416614u, gen::fn_sub_3B32D0_003b32d0);
    s1 = addiu(s5, 323);
    s0 = addiu(s6, 13);
    mtc1(s4, f0);
    cvt_s_w(f12, f0);
    a2 = s3 & 0xFF;
    a0 = s1;
    a1 = s0;
    a3 = 166;
    t0 = 0;
    jal(ctx, 0x416644u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(s4, f0);
    cvt_s_w(f12, f0);
    a2 = s3 & 0xFF;
    a0 = s1;
    a1 = s0;
    a3 = 167;
    t0 = 0;
    jal(ctx, 0x41666Cu, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(s4, f0);
    cvt_s_w(f12, f0);
    a2 = s3 & 0xFF;
    a0 = s1;
    a1 = s0;
    a3 = 168;
    t0 = 0;
    jal(ctx, 0x416694u, gen::fn_sub_40E3C0_0040e3c0);
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

// 0x004166D0 sub_4166D0 -- 244 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Facility menu draw callback (data-referenced): text line through sub_171110 / sub_3B2CB0.
void sub_4166D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x004166d0
    enter(ctx, 61);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a2;
    s1 = a3;
    s0 = t1;
    lw(v0, a1, 12);
    s3 = addiu(v0, 160);
    a0 = addiu(s2, 123);
    a1 = addiu(s1, 100);
    mtc1(zero, f12);
    a2 = s0 & 0xFF;
    a3 = 175;
    t0 = 0;
    jal(ctx, 0x416714u, gen::fn_sub_40E3C0_0040e3c0);
    a0 = addiu(s2, 123);
    a1 = addiu(s1, 100);
    mtc1(zero, f12);
    a2 = s0 & 0xFF;
    a3 = 176;
    t0 = 0;
    jal(ctx, 0x416734u, gen::fn_sub_40E3C0_0040e3c0);
    a0 = addiu(s2, 203);
    a1 = addiu(s1, 118);
    mtc1(zero, f12);
    a2 = s0 & 0xFF;
    lbu(v0, s3, 4);
    v0 = sll(v0, 1);
    t0 = addiu(v0, 1);
    a3 = 4;
    jal(ctx, 0x41675Cu, gen::fn_sub_40E3C0_0040e3c0);
    lh(a0, s3, 0);
    a1 = 2;
    jal(ctx, 0x41676Cu, gen::fn_sub_171110_00171110);
    a0 = addiu(s2, 237);
    a1 = addiu(s1, 121);
    mtc1(zero, f12);
    v1 = si(-256);
    a2 = s0 | v1;
    a3 = 6;
    t0 = 1;
    t1 = v0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x41679Cu, gen::fn_sub_3B2CB0_003b2cb0);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00416B90 sub_416B90 -- 400 bytes; frame 0x70: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// Facility menu draw callback (data-referenced): sub_40E3C0, sub_3C7E20.
void sub_416B90(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f20{ctx, 20};
    // 0x00416b90
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s4 = a2;
    s3 = a3;
    s2 = t0;
    s1 = t1;
    lw(v0, a1, 12);
    s0 = addiu(v0, 160);
    mtc1(s1, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, gp, -32256);  // 0x7CAEF0
    mul_s(f20, f0, f1);
    mtc1(s2, f0);
    cvt_s_w(f12, f0);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f20);
    if (cond(ctx)) {
        // 0x00416c18
        charge(ctx, 6);
        sub_s(f0, f20, f0);
        cvt_w_s(f0, f0);
        mfc1(a2, f0);
        v0 = lui(0x8000);
        a2 = a2 | v0;
        a2 = a2 & 0xFF;
    } else {
        // 0x00416c00
        charge(ctx, 6);
        cvt_w_s(f0, f20);
        mfc1(a2, f0);
        a2 = a2 & 0xFF;
    }
    // 0x00416c30
    charge(ctx, 15);
    a0 = addiu(s4, 294);
    a1 = addiu(s3, 245);
    a3 = 248;
    t0 = 0;
    jal(ctx, 0x416C40u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(s2, f0);
    cvt_s_w(f12, f0);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f20);
    if (cond(ctx)) {
        // 0x00416c84
        charge(ctx, 6);
        sub_s(f0, f20, f0);
        cvt_w_s(f0, f0);
        mfc1(a2, f0);
        v0 = lui(0x8000);
        a2 = a2 | v0;
        a2 = a2 & 0xFF;
    } else {
        // 0x00416c6c
        charge(ctx, 6);
        cvt_w_s(f0, f20);
        mfc1(a2, f0);
        a2 = a2 & 0xFF;
    }
    // 0x00416c9c
    charge(ctx, 33);
    a0 = addiu(s4, 294);
    a1 = addiu(s3, 245);
    a3 = 249;
    t0 = 0;
    jal(ctx, 0x416CACu, gen::fn_sub_40E3C0_0040e3c0);
    a0 = addiu(s4, 328);
    a1 = addiu(s3, 249);
    mtc1(zero, f12);
    v0 = si(-256);
    a2 = s1 | v0;
    lbu(v0, s0, 9);
    v1 = sll(v0, 16);
    v0 = lui(0xFFFF);
    v1 = v1 & v0;
    lh(v0, s0, 0);
    v0 = v0 & 0xFFFF;
    t2 = v0 | v1;
    a3 = 1;
    t0 = 5;
    t1 = a3;
    jal(ctx, 0x416CF0u, gen::fn_sub_3C7E20_003c7e20);
    ld(ra, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x00419730 sub_419730 -- 88 bytes; frame 0x10: ra sp+0x0
// Field effect callback (data-referenced): message id from (*a1)+12 (0xFFFF -> 1024, else (id & 0x3FF) | 0xC00) and
// the byte +20 to sub_3BB010; returns 1.
void sub_419730(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00419730
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a1, a1, 0);
    lw(a0, a1, 12);
    v1 = a0 & 0xFFFF;
    v0 = 0xFFFF;
    if (v1 == v0) {
        // 0x00419764
        charge(ctx, 1);
        a0 = 1024;
    } else {
        // 0x00419750
        charge(ctx, 5);
        v0 = a0 & 0x3FF;
        v0 = v0 | 0xC00;
        a0 = v0 & 0xFFFF;
    }
    // 0x00419768
    charge(ctx, 8);
    lbu(a1, a1, 20);
    jal(ctx, 0x41976Cu, gen::fn_sub_3BB010_003bb010);
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00419790 sub_419790 -- 344 bytes; frame 0xB0: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Field effect callback: camera (sub_198590), party data (sub_16BA00 .. sub_16BB80), RW frame transform.
void sub_419790(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x00419790
    enter(ctx, 86);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a1, 4);
    lhu(s1, a0, 34);
    v0 = 0x6B0000;
    ld(v1, v0, 11880);  // 0x6B2E68
    v0 = 0x6B0000;
    lwc1(f0, v0, 11888);  // 0x6B2E70
    sd(v1, sp, 0xA0);
    swc1(f0, sp, 0xA8);
    v0 = 0x6B0000;
    ld(v1, v0, 11896);  // 0x6B2E78
    v0 = 0x6B0000;
    lwc1(f0, v0, 11904);  // 0x6B2E80
    sd(v1, sp, 0x90);
    swc1(f0, sp, 0x98);
    jal(ctx, 0x4197DCu, gen::fn_sub_198590_00198590);
    lw(v0, v0, 4);
    s2 = addiu(v0, 16);
    a0 = 0;
    a1 = s1;
    jal(ctx, 0x4197F4u, gen::fn_sub_16BA00_0016ba00);
    swc1(f0, sp, 0x88);
    swc1(f0, sp, 0x84);
    swc1(f0, sp, 0x80);
    a0 = 0;
    a1 = s1;
    jal(ctx, 0x419810u, gen::fn_sub_16BA80_0016ba80);
    lwc1(f1, sp, 0xA0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0xA0);
    a0 = 0;
    a1 = s1;
    jal(ctx, 0x41982Cu, gen::fn_sub_16BB00_0016bb00);
    lwc1(f1, sp, 0xA4);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0xA4);
    a0 = 0;
    a1 = s1;
    jal(ctx, 0x419848u, gen::fn_sub_16BB80_0016bb80);
    lwc1(f1, sp, 0xA8);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0xA8);
    v0 = 0x43340000;
    mtc1(v0, f12);
    a0 = addiu(sp, 0x40);
    a1 = addiu(sp, 0x90);
    a2 = 0;
    jal(ctx, 0x419870u, gen::fn_sub_4C31B0_004c31b0);
    a0 = addiu(sp, 0x40);
    a1 = addiu(sp, 0xA0);
    a2 = 2;
    jal(ctx, 0x419884u, gen::fn_sub_4C35D0_004c35d0);
    a0 = addiu(sp, 0x40);
    a1 = a0;
    a2 = s2;
    jal(ctx, 0x419898u, gen::fn_sub_4C2F30_004c2f30);
    lw(a0, s0, 8);
    a1 = addiu(sp, 0x40);
    a2 = 0;
    jal(ctx, 0x4198ACu, gen::fn_sub_318A70_00318a70);
    lw(a0, s0, 8);
    a1 = addiu(sp, 0x80);
    a2 = 1;
    jal(ctx, 0x4198C0u, gen::fn_sub_318A90_00318a90);
    v0 = 1;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xB0);
}

// 0x004198F0 sub_4198F0 -- 308 bytes; frame 0x60: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Field effect callback: sub_16BC00, sub_3CDCD0, sub_3CDD80.
void sub_4198F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x004198f0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    lhu(s0, a0, 34);
    lw(v0, a1, 12);
    if (v0 == 0) {
        // 0x0041991c
        charge(ctx, 14);
        a0 = 0;
        a1 = s0;
        jal(ctx, 0x419924u, gen::fn_sub_16BC00_0016bc00);
        cvt_w_s(f0, f0);
        mfc1(v0, f0);
        a1 = dsll32(v0, 16);
        a1 = dsra32(a1, 16);
        lw(a0, s2, 24);
        a2 = 0;
        a3 = 0;
        jal(ctx, 0x41994Cu, gen::fn_sub_3CDCD0_003cdcd0);
    }
    // 0x00419954
    charge(ctx, 5);
    lw(a0, s2, 24);
    jal(ctx, 0x419958u, gen::fn_sub_3CDD80_003cdd80);
    if (v0 == 0) {
        // 0x004199f8
        charge(ctx, 4);
        lw(v0, s1, 12);
        v0 = addiu(v0, 1);
        sw(v0, s1, 12);
        v0 = 0;
    } else {
        // 0x00419968
        charge(ctx, 4);
        a1 = 0x6B0000;
        a1 = addiu(a1, 11920);  // &0x6B2E90
        a0 = addiu(sp, 0x40);
        v1 = 13;
        for (;;) {
            // 0x00419978
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
        // 0x00419994
        charge(ctx, 4);
        a0 = 0;
        v1 = s0 & 0xFFFF;
        for (;;) {
            // 0x004199c8
            charge(ctx, 3);
            v0 = sltiu(a0, 13);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x004199a4
            charge(ctx, 5);
            v0 = sll(a0, 1);
            v0 = addu(v0, sp);
            lhu(v0, v0, 64);
            if (v1 == v0) {
                goto L_004199b8_7;
            }
            // 0x004199c4
            charge(ctx, 1);
            a0 = addiu(a0, 1);
        }
        // 0x004199d4
        charge(ctx, 9);
        lw(a0, s2, 24);
        a1 = 0;
        a2 = 30;
        a3 = 1;
        jal(ctx, 0x4199E4u, gen::fn_sub_3CDCD0_003cdcd0);
        v0 = 1;
    }
    // 0x00419a08 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
L_004199b8_7:
    charge(ctx, 3);
    v0 = 1;
    // 0x00419a08 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00419F20 sub_419F20 -- 920 bytes; frame 0x140: ra sp+0x70, s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// Field effect callback: orbit motion with sinf / cosf around a node found by key (nmListFindByKey).
void sub_419F20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21};
    // 0x00419f20
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x140);
    sd(ra, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s4 = a0;
    s3 = a1;
    a2 = 0x6B0000;
    a2 = addiu(a2, 11952);  // &0x6B2EB0
    a1 = addiu(sp, 0xE0);
    a0 = 5;
    for (;;) {
        // 0x00419f60
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
    // 0x00419f84
    charge(ctx, 17);
    v0 = 0x6B0000;
    ld(v1, v0, 11992);  // 0x6B2ED8
    v0 = 0x6B0000;
    lwc1(f0, v0, 12000);  // 0x6B2EE0
    sd(v1, sp, 0x130);
    swc1(f0, sp, 0x138);
    lw(s1, s3, 0);
    v0 = 0x6B0000;
    ld(v1, v0, 12008);  // 0x6B2EE8
    v0 = 0x6B0000;
    lwc1(f0, v0, 12016);  // 0x6B2EF0
    sd(v1, sp, 0x120);
    swc1(f0, sp, 0x128);
    a1 = 0x6B0000;
    a1 = addiu(a1, 12032);  // &0x6B2F00
    a0 = addiu(sp, 0x80);
    v1 = 5;
    for (;;) {
        // 0x00419fc8
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
    // 0x00419fe4
    charge(ctx, 4);
    lb(v1, s1, 4);
    v0 = 64;
    if (v1 == v0) {
        // 0x00419ffc
        charge(ctx, 3);
        lb(v0, s1, 5);
        if (v0 == 0) {
            // 0x0041a008
            charge(ctx, 29);
            lwc1(f0, s3, 12);
            cvt_s_w(f1, f0);
            lwc1(f0, gp, -32496);  // 0x7CAE00
            mul_s(f1, f0, f1);
            lwc1(f0, s1, 8);
            cvt_s_w(f0, f0);
            div_s(f12, f1, f0);
            jal(ctx, 0x41A030u, gen::fn_sinf_0052e878);
            v0 = 0x41A00000;
            mtc1(v0, f3);
            v0 = 0x420C0000;
            mtc1(v0, f2);
            mtc1(zero, f1);
            adda_s(f1, f2);
            madd_s(f0, f3, f0);
            swc1(f0, gp, -21128);  // 0x7CDA68
            lw(v0, s4, 60);
            lw(a0, v0, 0);
            a1 = addiu(a0, 4);
            a2 = 4;
            jal(ctx, 0x41A06Cu, gen::fn_nmListFindByKey_003c4b50);
            if (v0 != 0) {
                // 0x0041a07c
                charge(ctx, 7);
                lw(v0, v0, 20);
                lw(s0, v0, 8);
                s2 = 0;
                lwc1(f21, sp, 0x134);
                lwc1(f20, sp, 0x138);
                for (;;) {
                    // 0x0041a1d4
                    charge(ctx, 4);
                    lw(v0, s0, 4);
                    v0 = slt(s2, v0);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0041a098
                    charge(ctx, 79);
                    v0 = sll(s2, 2);
                    v0 = addu(s0, v0);
                    lw(v0, v0, 8);
                    lw(s5, v0, 8);
                    lw(v0, s0, 4);
                    v0 = sll(v0, 3);
                    v0 = addu(v0, sp);
                    v0 = addiu(v0, 224);
                    mtc1(s2, f0);
                    cvt_s_w(f3, f0);
                    lwc1(f2, v0, -12);
                    lwc1(f1, v0, -16);
                    mtc1(zero, f0);
                    adda_s(f0, f1);
                    madd_s(f12, f3, f2);
                    jal(ctx, 0x41A0DCu, gen::fn_cosf_0052e6d8);
                    lw(v1, s0, 4);
                    v0 = sll(v1, 2);
                    v0 = addu(v0, sp);
                    lwc1(f1, v0, 120);
                    mul_s(f0, f1, f0);
                    swc1(f0, sp, 0x110);
                    v0 = sll(v1, 3);
                    v0 = addu(v0, sp);
                    v0 = addiu(v0, 224);
                    mtc1(s2, f0);
                    cvt_s_w(f3, f0);
                    lwc1(f2, v0, -12);
                    lwc1(f1, v0, -16);
                    mtc1(zero, f0);
                    adda_s(f0, f1);
                    madd_s(f12, f3, f2);
                    jal(ctx, 0x41A12Cu, gen::fn_sinf_0052e878);
                    lw(v0, s0, 4);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, sp);
                    lwc1(f1, v0, 120);
                    neg_s(f1, f1);
                    mul_s(f0, f1, f0);
                    swc1(f0, sp, 0x114);
                    sw(zero, sp, 0x118);
                    a0 = addiu(sp, 0xA0);
                    a1 = addiu(sp, 0x120);
                    lwc1(f12, gp, -21128);  // 0x7CDA68
                    a2 = 0;
                    jal(ctx, 0x41A164u, gen::fn_sub_4C31B0_004c31b0);
                    a0 = addiu(sp, 0x110);
                    a1 = a0;
                    a2 = addiu(sp, 0xA0);
                    jal(ctx, 0x41A178u, gen::fn_sub_4C6C60_004c6c60);
                    lwc1(f1, sp, 0x110);
                    lwc1(f0, sp, 0x130);
                    add_s(f0, f1, f0);
                    swc1(f0, sp, 0x110);
                    lwc1(f0, sp, 0x114);
                    add_s(f0, f0, f21);
                    swc1(f0, sp, 0x114);
                    lwc1(f0, sp, 0x118);
                    add_s(f0, f0, f20);
                    swc1(f0, sp, 0x118);
                    a0 = addiu(s5, 16);
                    a1 = addiu(sp, 0x120);
                    lwc1(f12, gp, -21128);  // 0x7CDA68
                    a2 = 0;
                    jal(ctx, 0x41A1B8u, gen::fn_sub_4BDDE0_004bdde0);
                    a0 = s5;
                    a1 = addiu(sp, 0x110);
                    jal(ctx, 0x41A1C8u, gen::fn_sub_20D650_0020d650);
                    s2 = addiu(s2, 1);
                }
            }
            // 0x0041a1e4
            charge(ctx, 8);
            lw(v0, s4, 60);
            lw(a0, v0, 0);
            a1 = addiu(a0, 4);
            a2 = 2;
            jal(ctx, 0x41A1F4u, gen::fn_nmListFindByKey_003c4b50);
            if (v0 != 0) {
                // 0x0041a204
                charge(ctx, 25);
                lw(s0, v0, 20);
                sw(zero, sp, 0x110);
                v0 = 0x41B80000;
                sw(v0, sp, 0x114);
                v0 = 550;
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                swc1(f0, sp, 0x118);
                a0 = addiu(sp, 0xA0);
                a1 = addiu(sp, 0x120);
                lwc1(f12, gp, -21128);  // 0x7CDA68
                a2 = 0;
                jal(ctx, 0x41A238u, gen::fn_sub_4C31B0_004c31b0);
                lw(a0, s0, 8);
                a1 = addiu(sp, 0xA0);
                a2 = 0;
                jal(ctx, 0x41A24Cu, gen::fn_sub_41BEE0_0041bee0);
                lw(a0, s0, 8);
                a1 = addiu(sp, 0x110);
                a2 = 2;
                jal(ctx, 0x41A260u, gen::fn_sub_41BEB0_0041beb0);
            }
        }
    } else {
        // 0x00419ff4
        charge(ctx, 2);
    }
    // 0x0041a268 (the shared epilogue, written out on this path)
    charge(ctx, 20);
    lw(v0, s4, 60);
    lw(v1, v0, 8);
    lw(v0, s1, 0);
    v1 = subu(v1, v0);
    sw(v1, s3, 12);
    lw(v0, s1, 8);
    v0 = slt(v1, v0);
    v0 = v0 ^ 0x1;
    ld(ra, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x140);
}

// 0x0041A3F0 sub_41A3F0 -- 832 bytes; frame 0x140: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// Field effect callback: as sub_419F20 for the free-standing variant.
void sub_41A3F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21};
    // 0x0041a3f0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x140);
    sd(ra, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s4 = a1;
    lw(v0, a1, 4);
    lw(s1, v0, 8);
    a2 = 0x6B0000;
    a2 = addiu(a2, 12096);  // &0x6B2F40
    a1 = addiu(sp, 0xD0);
    a0 = 5;
    for (;;) {
        // 0x0041a430
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
    // 0x0041a454
    charge(ctx, 22);
    v0 = 0x6B0000;
    ld(v1, v0, 12136);  // 0x6B2F68
    v0 = 0x6B0000;
    lwc1(f0, v0, 12144);  // 0x6B2F70
    sd(v1, sp, 0x130);
    swc1(f0, sp, 0x138);
    v0 = 0x6B0000;
    ld(v1, v0, 12152);  // 0x6B2F78
    v0 = 0x6B0000;
    lwc1(f0, v0, 12160);  // 0x6B2F80
    sd(v1, sp, 0x120);
    swc1(f0, sp, 0x128);
    v0 = 0x6B0000;
    ld(v1, v0, 12168);  // 0x6B2F88
    v0 = 0x6B0000;
    lwc1(f0, v0, 12176);  // 0x6B2F90
    sd(v1, sp, 0x110);
    swc1(f0, sp, 0x118);
    a1 = 0x6B0000;
    a1 = addiu(a1, 12192);  // &0x6B2FA0
    a0 = addiu(sp, 0x70);
    v1 = 5;
    for (;;) {
        // 0x0041a4ac
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
    // 0x0041a4c8
    charge(ctx, 3);
    lw(v0, s4, 12);
    if (v0 == 0) {
        // 0x0041a4d4
        charge(ctx, 12);
        a0 = 1;
        a1 = 10;
        a2 = 7;
        a3 = 0;
        jal(ctx, 0x41A4E4u, gen::fn_sub_10A4E0_0010a4e0);
        a0 = 1;
        a1 = 0;
        a2 = 6;
        a3 = a0;
        jal(ctx, 0x41A4FCu, gen::fn_sub_10A4E0_0010a4e0);
    }
    // 0x0041a504
    charge(ctx, 5);
    s2 = 0;
    lwc1(f21, sp, 0x114);
    lwc1(f20, sp, 0x118);
    for (;;) {
        // 0x0041a6d8
        charge(ctx, 4);
        lw(v0, s1, 4);
        v0 = slt(s2, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0041a518
        charge(ctx, 9);
        v0 = sll(s2, 2);
        v0 = addu(s1, v0);
        a0 = addiu(v0, 8);
        lw(v0, v0, 8);
        lw(s3, v0, 8);
        lw(v1, s4, 12);
        v0 = sll(s2, 1);
        if (v1 == v0) {
            // 0x0041a53c
            charge(ctx, 9);
            v0 = 1;
            v1 = sllv(v0, s2);
            lw(v0, s1, 0);
            v0 = v0 | v1;
            sw(v0, s1, 0);
            lw(v1, a0, 0);
            lh(v0, v1, 0);
            v0 = v0 | 0x1;
            sh(v0, v1, 0);
        }
        // 0x0041a560
        charge(ctx, 6);
        v0 = 1;
        s0 = sllv(v0, s2);
        lw(v0, s1, 0);
        v0 = v0 & s0;
        if (v0 != 0) {
            // 0x0041a578
            charge(ctx, 87);
            lw(v0, s1, 4);
            v0 = sll(v0, 3);
            v0 = addu(v0, sp);
            v0 = addiu(v0, 208);
            mtc1(s2, f0);
            cvt_s_w(f3, f0);
            lwc1(f2, v0, -12);
            lwc1(f1, v0, -16);
            mtc1(zero, f0);
            adda_s(f0, f1);
            madd_s(f12, f3, f2);
            jal(ctx, 0x41A5ACu, gen::fn_cosf_0052e6d8);
            lw(v1, s1, 4);
            v0 = sll(v1, 2);
            v0 = addu(v0, sp);
            lwc1(f1, v0, 104);
            mul_s(f0, f1, f0);
            swc1(f0, sp, 0x100);
            v0 = sll(v1, 3);
            v0 = addu(v0, sp);
            v0 = addiu(v0, 208);
            mtc1(s2, f0);
            cvt_s_w(f3, f0);
            lwc1(f2, v0, -12);
            lwc1(f1, v0, -16);
            mtc1(zero, f0);
            adda_s(f0, f1);
            madd_s(f12, f3, f2);
            jal(ctx, 0x41A5FCu, gen::fn_sinf_0052e878);
            lw(v0, s1, 4);
            v0 = sll(v0, 2);
            v0 = addu(v0, sp);
            lwc1(f1, v0, 104);
            neg_s(f1, f1);
            mul_s(f0, f1, f0);
            swc1(f0, sp, 0x104);
            sw(zero, sp, 0x108);
            v0 = 0x420C0000;
            mtc1(v0, f12);
            a0 = addiu(sp, 0x90);
            a1 = addiu(sp, 0x130);
            a2 = 0;
            jal(ctx, 0x41A638u, gen::fn_sub_4C31B0_004c31b0);
            a0 = addiu(sp, 0x100);
            a1 = a0;
            a2 = addiu(sp, 0x90);
            jal(ctx, 0x41A64Cu, gen::fn_sub_4C6C60_004c6c60);
            lwc1(f1, sp, 0x100);
            lwc1(f0, sp, 0x110);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x100);
            lwc1(f0, sp, 0x104);
            add_s(f0, f0, f21);
            swc1(f0, sp, 0x104);
            lwc1(f0, sp, 0x108);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0x108);
            v0 = lui(0xC20C);
            mtc1(v0, f12);
            a0 = addiu(s3, 16);
            a1 = addiu(sp, 0x130);
            a2 = 0;
            jal(ctx, 0x41A690u, gen::fn_sub_4BDDE0_004bdde0);
            v0 = 0x43340000;
            mtc1(v0, f12);
            a0 = addiu(s3, 16);
            a1 = addiu(sp, 0x120);
            a2 = 2;
            jal(ctx, 0x41A6ACu, gen::fn_sub_4BDDE0_004bdde0);
            a0 = s3;
            a1 = addiu(sp, 0x100);
            jal(ctx, 0x41A6BCu, gen::fn_sub_20D650_0020d650);
            v1 = nor(s0, 0);
            lw(v0, s1, 0);
            v0 = v0 & v1;
            sw(v0, s1, 0);
        }
        // 0x0041a6d4
        charge(ctx, 1);
        s2 = addiu(s2, 1);
    }
    // 0x0041a6e8
    charge(ctx, 18);
    lw(v0, s4, 12);
    v1 = addiu(v0, 1);
    sw(v1, s4, 12);
    lw(v0, s1, 4);
    v0 = sll(v0, 1);
    v0 = addiu(v0, 2);
    v0 = slt(v0, v1);
    ld(ra, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x140);
}

// 0x0041A730 sub_41A730 -- 452 bytes; frame 0x80: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Field effect callback: sub_10A4E0, sub_4BDDE0.
void sub_41A730(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12};
    // 0x0041a730
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s5 = a1;
    lw(v0, a1, 4);
    lw(s3, v0, 8);
    v0 = 0x6B0000;
    ld(v1, v0, 12216);  // 0x6B2FB8
    v0 = 0x6B0000;
    lwc1(f0, v0, 12224);  // 0x6B2FC0
    sd(v1, sp, 0x70);
    swc1(f0, sp, 0x78);
    lw(v0, a1, 12);
    if (v0 == 0) {
        // 0x0041a780
        charge(ctx, 6);
        a0 = 1;
        a1 = 10;
        a2 = 7;
        a3 = 0;
        jal(ctx, 0x41A790u, gen::fn_sub_10A4E0_0010a4e0);
    }
    // 0x0041a798
    charge(ctx, 3);
    s4 = 0;
    for (;;) {
        // 0x0041a870
        charge(ctx, 4);
        lw(v0, s3, 4);
        v0 = slt(s4, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0041a7a4
        charge(ctx, 8);
        v0 = sll(s4, 2);
        v0 = addu(s3, v0);
        lw(v0, v0, 8);
        lw(s2, v0, 8);
        s1 = sll(s4, 1);
        lw(v0, s5, 12);
        if (v0 == s1) {
            // 0x0041a7c4
            charge(ctx, 11);
            a0 = 1;
            v1 = sllv(a0, s4);
            lw(v0, s3, 0);
            v0 = v0 | v1;
            sw(v0, s3, 0);
            a1 = dsll32(s4, 16);
            a1 = dsra32(a1, 16);
            a2 = 6;
            a3 = 3;
            jal(ctx, 0x41A7E8u, gen::fn_sub_10A4E0_0010a4e0);
        }
        // 0x0041a7f0
        charge(ctx, 6);
        a2 = 1;
        s0 = sllv(a2, s4);
        lw(v0, s3, 0);
        v0 = v0 & s0;
        if (v0 != 0) {
            // 0x0041a808
            charge(ctx, 21);
            v0 = lui(0xC1F0);
            mtc1(v0, f12);
            a0 = addiu(s2, 16);
            a1 = addiu(sp, 0x70);
            jal(ctx, 0x41A818u, gen::fn_sub_4BDDE0_004bdde0);
            lwc1(f0, s5, 12);
            cvt_s_w(f2, f0);
            v0 = 0x40C00000;
            mtc1(v0, f1);
            mtc1(s1, f0);
            cvt_s_w(f0, f0);
            add_s(f1, f1, f0);
            v0 = 0x3F800000;
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            c_eq_s(f2, f0);
            if (cond(ctx)) {
                // 0x0041a85c
                charge(ctx, 4);
                v1 = nor(s0, 0);
                lw(v0, s3, 0);
                v0 = v0 & v1;
                sw(v0, s3, 0);
            }
        }
        // 0x0041a86c
        charge(ctx, 1);
        s4 = addiu(s4, 1);
    }
    // 0x0041a880
    charge(ctx, 18);
    lw(v0, s5, 12);
    v0 = addiu(v0, 1);
    sw(v0, s5, 12);
    lw(v0, s3, 4);
    v0 = sll(v0, 1);
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    v0 = 0x40C00000;
    mtc1(v0, f0);
    add_s(f1, f0, f1);
    lwc1(f0, s5, 12);
    cvt_s_w(f0, f0);
    c_le_s(f0, f1);
    v0 = 1;
    if (cond(ctx)) {
        // 0x0041a8c8
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x0041a8cc (the shared epilogue, written out on this path)
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

// 0x0041ABC0 sub_41ABC0 -- 524 bytes; frame 0xD0: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Field effect callback: attaches an effect to a node found by key and transforms it.
void sub_41ABC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x0041abc0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0xD0);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    lw(s0, a1, 0);
    v0 = 0x6B0000;
    ld(v1, v0, 12344);  // 0x6B3038
    v0 = 0x6B0000;
    lwc1(f0, v0, 12352);  // 0x6B3040
    sd(v1, sp, 0xB0);
    swc1(f0, sp, 0xB8);
    a1 = 0x6B0000;
    a1 = addiu(a1, 12368);  // &0x6B3050
    a0 = addiu(sp, 0x90);
    v1 = 5;
    for (;;) {
        // 0x0041ac0c
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
    // 0x0041ac28
    charge(ctx, 11);
    lw(v0, s3, 60);
    lw(a0, v0, 0);
    lh(v0, s3, 32);
    v0 = sll(v0, 2);
    v0 = addu(v0, sp);
    lh(a2, v0, 144);
    a1 = addiu(a0, 4);
    jal(ctx, 0x41AC44u, gen::fn_nmListFindByKey_003c4b50);
    if (v0 == 0) {
        // 0x0041ac60
        charge(ctx, 1);
        s1 = 0;
    } else {
        // 0x0041ac54
        charge(ctx, 3);
        lw(s1, v0, 20);
    }
    // 0x0041ac64
    charge(ctx, 65);
    jal(ctx, 0x41AC64u, gen::fn_sub_198590_00198590);
    lwc1(f0, sp, 0xB0);
    v1 = 0x43A00000;
    mtc1(v1, f2);
    sub_s(f0, f0, f2);
    neg_s(f1, f0);
    lwc1(f0, v0, 104);
    mul_s(f0, f1, f0);
    div_s(f0, f0, f2);
    swc1(f0, sp, 0xC0);
    lwc1(f0, sp, 0xB4);
    v1 = 0x43600000;
    mtc1(v1, f2);
    sub_s(f0, f0, f2);
    neg_s(f1, f0);
    lwc1(f0, v0, 108);
    mul_s(f0, f1, f0);
    div_s(f0, f0, f2);
    swc1(f0, sp, 0xC4);
    v0 = 0x3F800000;
    sw(v0, sp, 0xC8);
    a0 = addiu(sp, 0xC0);
    a1 = a0;
    jal(ctx, 0x41ACCCu, gen::fn_sub_4C69F0_004c69f0);
    lw(v0, s3, 56);
    s3 = addiu(v0, 16);
    a0 = addiu(sp, 0x50);
    a1 = s3;
    jal(ctx, 0x41ACE4u, gen::fn_sub_4C32A0_004c32a0);
    a0 = addiu(sp, 0xC0);
    a1 = a0;
    a2 = addiu(sp, 0x50);
    jal(ctx, 0x41ACF8u, gen::fn_sub_4C6C60_004c6c60);
    lwc1(f1, sp, 0xB8);
    lwc1(f0, sp, 0xC0);
    mul_s(f3, f0, f1);
    swc1(f3, sp, 0xC0);
    lwc1(f0, sp, 0xC4);
    mul_s(f2, f0, f1);
    swc1(f2, sp, 0xC4);
    lwc1(f0, sp, 0xC8);
    mul_s(f1, f0, f1);
    swc1(f1, sp, 0xC8);
    lwc1(f0, s3, 48);
    add_s(f0, f0, f3);
    swc1(f0, sp, 0xB0);
    lwc1(f0, s3, 52);
    add_s(f0, f0, f2);
    swc1(f0, sp, 0xB4);
    lwc1(f0, s3, 56);
    add_s(f0, f0, f1);
    swc1(f0, sp, 0xB8);
    lw(a0, s1, 8);
    a1 = addiu(sp, 0xB0);
    jal(ctx, 0x41AD54u, gen::fn_sub_34FDF0_0034fdf0);
    lw(v0, s2, 12);
    if (v0 == 0) {
        // 0x0041ad68
        charge(ctx, 6);
        lw(a0, s1, 8);
        jal(ctx, 0x41AD6Cu, gen::fn_sub_34FD10_0034fd10);
        lh(v0, s1, 0);
        v0 = v0 | 0x1;
        sh(v0, s1, 0);
    }
    // 0x0041ad80
    charge(ctx, 7);
    lw(v0, s2, 12);
    v1 = addiu(v0, 1);
    sw(v1, s2, 12);
    lw(v0, s0, 8);
    v0 = slt(v1, v0);
    if (v0 != 0) {
        // 0x0041ada8
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x0041ad9c
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x0041adac (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xD0);
}

// 0x0041AFF0 sub_41AFF0 -- 1336 bytes; frame 0x70: ra sp+0x20, s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// Field effect callback: pad-driven (gPadFlags) frame update.
void sub_41AFF0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21};
    // 0x0041aff0
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lw(s0, a0, 56);
    mtc1(zero, f20);
    v0 = 0x6B0000;
    ld(v1, v0, 12432);  // 0x6B3090
    v0 = 0x6B0000;
    lwc1(f0, v0, 12440);  // 0x6B3098
    sd(v1, sp, 0x60);
    swc1(f0, sp, 0x68);
    v0 = 0;
    a2 = addiu(sp, 0x30);
    v1 = 12;
    if (a2 != 0) {
        for (;;) {
            // 0x0041b038
            charge(ctx, 7);
            sb(zero, a2, 0);
            a2 = addiu(a2, 1);
            v1 = addiu(v1, -1);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0041b054
    charge(ctx, 5);
    v1 = 0x7E0000;
    lhu(v1, v1, 2382);  // gPadFlags
    v1 = v1 & 0x80;
    if (v1 == 0) {
        // 0x0041b068
        charge(ctx, 5);
        v1 = 0x7E0000;
        lhu(v1, v1, 2392);  // 0x7E0958
        v1 = v1 & 0x80;
        if (v1 != 0) {
            goto L_0041b07c;
        }
        goto L_0041b088;
    }
L_0041b07c:
    charge(ctx, 3);
    lw(v1, a1, 16);
    v1 = v1 ^ 0x1;
    sw(v1, a1, 16);
L_0041b088:
    charge(ctx, 3);
    lw(v1, a1, 16);
    if (v1 != 0) {
        // 0x0041b0ac
        charge(ctx, 9);
        lw(a1, a0, 60);
        lw(v1, a1, 8);
        v1 = addiu(v1, -1);
        sw(v1, a1, 8);
        v1 = 0x7E0000;
        lhu(v1, v1, 2382);  // gPadFlags
        v1 = v1 & 0x8;
        if (v1 == 0) {
            // 0x0041b0d0
            charge(ctx, 5);
            v1 = 0x7E0000;
            lhu(v1, v1, 2392);  // 0x7E0958
            v1 = v1 & 0x8;
            if (v1 != 0) {
                goto L_0041b0e4;
            }
            goto L_0041b0f0;
        }
    L_0041b0e4:
        charge(ctx, 3);
        a1 = 499;
        lw(v1, a0, 60);
        sw(a1, v1, 8);
    L_0041b0f0:
        charge(ctx, 4);
        v1 = 0x7E0000;
        lbu(v1, v1, 2398);  // 0x7E095E
        if (i64(v1) < 0) {
            // 0x0041b114
            charge(ctx, 7);
            a0 = srl(v1, 1);
            v1 = v1 & 0x1;
            a0 = a0 | v1;
            mtc1(a0, f0);
            cvt_s_w(f1, f0);
            add_s(f1, f1, f1);
        } else {
            // 0x0041b100
            charge(ctx, 5);
            mtc1(v1, f0);
            cvt_s_w(f1, f0);
        }
        // 0x0041b130
        charge(ctx, 10);
        v1 = 0x43000000;
        mtc1(v1, f0);
        sub_s(f2, f1, f0);
        v1 = lui(0xC240);
        mtc1(v1, f0);
        c_lt_s(f2, f0);
        if (!cond(ctx)) {
            // 0x0041b158
            charge(ctx, 6);
            v1 = 0x42400000;
            mtc1(v1, f0);
            c_le_s(f2, f0);
            if (!cond(ctx)) {
                goto L_0041b170;
            }
            goto L_0041b188;
        }
    L_0041b170:
        charge(ctx, 6);
        lwc1(f1, gp, -32052);  // 0x7CAFBC
        mtc1(zero, f0);
        adda_s(f0, f20);
        msub_s(f20, f1, f2);
        v0 = 1;
    L_0041b188:
        charge(ctx, 4);
        v1 = 0x7E0000;
        lbu(v1, v1, 2399);  // 0x7E095F
        if (i64(v1) < 0) {
            // 0x0041b1ac
            charge(ctx, 7);
            a0 = srl(v1, 1);
            v1 = v1 & 0x1;
            a0 = a0 | v1;
            mtc1(a0, f0);
            cvt_s_w(f1, f0);
            add_s(f1, f1, f1);
        } else {
            // 0x0041b198
            charge(ctx, 5);
            mtc1(v1, f0);
            cvt_s_w(f1, f0);
        }
        // 0x0041b1c8
        charge(ctx, 10);
        v1 = 0x43000000;
        mtc1(v1, f0);
        sub_s(f3, f1, f0);
        v1 = lui(0xC240);
        mtc1(v1, f0);
        c_lt_s(f3, f0);
        if (!cond(ctx)) {
            // 0x0041b1f0
            charge(ctx, 6);
            v1 = 0x42400000;
            mtc1(v1, f0);
            c_le_s(f3, f0);
            if (!cond(ctx)) {
                goto L_0041b208;
            }
            goto L_0041b238;
        }
    L_0041b208:
        charge(ctx, 12);
        lwc1(f2, s0, 16);
        lwc1(f1, s0, 20);
        lwc1(f0, s0, 24);
        swc1(f2, sp, 0x60);
        swc1(f1, sp, 0x64);
        swc1(f0, sp, 0x68);
        lwc1(f1, gp, -32052);  // 0x7CAFBC
        mtc1(zero, f0);
        adda_s(f0, f20);
        msub_s(f20, f1, f3);
        v0 = 1;
    L_0041b238:
        charge(ctx, 4);
        v1 = 0x7E0000;
        lbu(v1, v1, 2401);  // 0x7E0961
        if (i64(v1) < 0) {
            // 0x0041b25c
            charge(ctx, 7);
            a0 = srl(v1, 1);
            v1 = v1 & 0x1;
            a0 = a0 | v1;
            mtc1(a0, f0);
            cvt_s_w(f1, f0);
            add_s(f1, f1, f1);
        } else {
            // 0x0041b248
            charge(ctx, 5);
            mtc1(v1, f0);
            cvt_s_w(f1, f0);
        }
        // 0x0041b278
        charge(ctx, 10);
        v1 = 0x43000000;
        mtc1(v1, f0);
        sub_s(f21, f1, f0);
        v1 = lui(0xC240);
        mtc1(v1, f0);
        c_lt_s(f21, f0);
        if (!cond(ctx)) {
            // 0x0041b2a0
            charge(ctx, 6);
            v1 = 0x42400000;
            mtc1(v1, f0);
            c_le_s(f21, f0);
            if (!cond(ctx)) {
                goto L_0041b2b8;
            }
            goto L_0041b310;
        }
    L_0041b2b8:
        charge(ctx, 22);
        a0 = addiu(sp, 0x30);
        lwc1(f2, s0, 48);
        lwc1(f1, s0, 52);
        lwc1(f0, s0, 56);
        swc1(f2, sp, 0x30);
        swc1(f1, sp, 0x34);
        swc1(f0, sp, 0x38);
        a1 = a0;
        jal(ctx, 0x41B2D8u, gen::fn_sub_4C69F0_004c69f0);
        lwc1(f0, gp, -31960);  // 0x7CB018
        mul_s(f1, f0, f21);
        lwc1(f0, sp, 0x30);
        mul_s(f0, f0, f1);
        swc1(f0, sp, 0x30);
        lwc1(f0, sp, 0x34);
        mul_s(f0, f0, f1);
        swc1(f0, sp, 0x34);
        lwc1(f0, sp, 0x38);
        mul_s(f0, f0, f1);
        swc1(f0, sp, 0x38);
        v0 = 1;
    L_0041b310:
        charge(ctx, 4);
        v1 = 0x7E0000;
        lbu(v1, v1, 2400);  // 0x7E0960
        if (i64(v1) < 0) {
            // 0x0041b334
            charge(ctx, 7);
            a0 = srl(v1, 1);
            v1 = v1 & 0x1;
            a0 = a0 | v1;
            mtc1(a0, f0);
            cvt_s_w(f1, f0);
            add_s(f1, f1, f1);
        } else {
            // 0x0041b320
            charge(ctx, 5);
            mtc1(v1, f0);
            cvt_s_w(f1, f0);
        }
        // 0x0041b350
        charge(ctx, 10);
        v1 = 0x43000000;
        mtc1(v1, f0);
        sub_s(f21, f1, f0);
        v1 = lui(0xC240);
        mtc1(v1, f0);
        c_lt_s(f21, f0);
        if (!cond(ctx)) {
            // 0x0041b378
            charge(ctx, 6);
            v1 = 0x42400000;
            mtc1(v1, f0);
            c_le_s(f21, f0);
            if (!cond(ctx)) {
                goto L_0041b390;
            }
            goto L_0041b3e8;
        }
    L_0041b390:
        charge(ctx, 22);
        a0 = addiu(sp, 0x30);
        lwc1(f2, s0, 16);
        lwc1(f1, s0, 20);
        lwc1(f0, s0, 24);
        swc1(f2, sp, 0x30);
        swc1(f1, sp, 0x34);
        swc1(f0, sp, 0x38);
        a1 = a0;
        jal(ctx, 0x41B3B0u, gen::fn_sub_4C69F0_004c69f0);
        lwc1(f0, gp, -31960);  // 0x7CB018
        mul_s(f1, f0, f21);
        lwc1(f0, sp, 0x30);
        mul_s(f0, f0, f1);
        swc1(f0, sp, 0x30);
        lwc1(f0, sp, 0x34);
        mul_s(f0, f0, f1);
        swc1(f0, sp, 0x34);
        lwc1(f0, sp, 0x38);
        mul_s(f0, f0, f1);
        swc1(f0, sp, 0x38);
        v0 = 1;
    L_0041b3e8:
        charge(ctx, 5);
        v1 = 0x7E0000;
        lhu(a1, v1, 2380);  // 0x7E094C
        v1 = a1 & 0x4;
        if (v1 == 0) {
            // 0x0041b3fc
            charge(ctx, 5);
            v1 = 0x7E0000;
            lhu(a0, v1, 2390);  // 0x7E0956
            v1 = a0 & 0x4;
            if (v1 != 0) {
                goto L_0041b410;
            }
            // 0x0041b434
            charge(ctx, 3);
            v1 = a1 & 0x8;
            if (v1 == 0) {
                // 0x0041b440
                charge(ctx, 3);
                v1 = a0 & 0x8;
                if (v1 != 0) {
                    goto L_0041b44c;
                }
                goto L_0041b468;
            }
        L_0041b44c:
            charge(ctx, 7);
            lwc1(f1, sp, 0x34);
            v0 = 0x41200000;
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x34);
            v0 = 1;
            goto L_0041b468;
        }
    L_0041b410:
        charge(ctx, 9);
        lwc1(f1, sp, 0x34);
        v0 = 0x41200000;
        mtc1(v0, f0);
        sub_s(f0, f1, f0);
        swc1(f0, sp, 0x34);
        v0 = 1;
    L_0041b468:
        charge(ctx, 2);
        if (v0 != 0) {
            // 0x0041b470
            charge(ctx, 38);
            lwc1(f2, s0, 64);
            lwc1(f1, s0, 68);
            lwc1(f0, s0, 72);
            swc1(f2, sp, 0x50);
            swc1(f1, sp, 0x54);
            swc1(f0, sp, 0x58);
            v0 = lui(0xBF80);
            mtc1(v0, f1);
            lwc1(f0, sp, 0x50);
            mul_s(f0, f1, f0);
            swc1(f0, sp, 0x40);
            lwc1(f0, sp, 0x54);
            mul_s(f0, f1, f0);
            swc1(f0, sp, 0x44);
            lwc1(f0, sp, 0x58);
            mul_s(f0, f1, f0);
            swc1(f0, sp, 0x48);
            a0 = s0;
            a1 = addiu(sp, 0x40);
            a2 = 2;
            jal(ctx, 0x41B4C0u, gen::fn_sub_4CB750_004cb750);
            a0 = s0;
            a1 = addiu(sp, 0x60);
            mov_s(f12, f20);
            a2 = 2;
            jal(ctx, 0x41B4D8u, gen::fn_sub_4CB890_004cb890);
            a0 = s0;
            a1 = addiu(sp, 0x30);
            a2 = 2;
            jal(ctx, 0x41B4ECu, gen::fn_sub_4CB750_004cb750);
            a0 = s0;
            a1 = addiu(sp, 0x50);
            a2 = 2;
            jal(ctx, 0x41B500u, gen::fn_sub_4CB750_004cb750);
        }
        // 0x0041b508
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x0041b094
        charge(ctx, 6);
        lw(v0, a0, 60);
        lw(v0, v0, 16);
        v0 = v0 & 0x1;
        v0 = sltu(0, v0);
    }
    // 0x0041b50c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x0048D960 sub_48D960 -- 204 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Resource manager thread step (H_Resman_ThreadProc): streams an RW object in (sub_48D0E0, sub_4C1600 ..).
void sub_48D960(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0048d960
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    a2 = a0;
    sd(ra, sp, 0x20);
    a0 = 2;
    sq(s1, sp, 0x10);
    a1 = 1;
    sq(s0, sp, 0x0);
    s0 = 0;
    jal(ctx, 0x48D97Cu, gen::fn_sub_4C58A0_004c58a0);
    s1 = v0;
    if (s1 != 0) {
        // 0x0048d990
        charge(ctx, 7);
        a0 = s1;
        a1 = 12;
        a2 = 0;
        a3 = addiu(sp, 0x3C);
        jal(ctx, 0x48D99Cu, gen::fn_sub_4C1600_004c1600);
        if (v0 != 0) {
            // 0x0048d9ac
            charge(ctx, 6);
            lw(v1, sp, 0x3C);
            v0 = 0x30000;
            v0 = v0 | 0x5000;
            v0 = sltu(v1, v0);
            if (v0 == 0) {
                // 0x0048d9c4
                charge(ctx, 5);
                at = 0x30000;
                at = at | 0x7003;
                at = sltu(v1, at);
                if (at == 0) {
                    goto L_0048d9e8;
                }
                // 0x0048d9d8
                charge(ctx, 4);
                a0 = s1;
                jal(ctx, 0x48D9D8u, gen::fn_sub_48D0E0_0048d0e0);
                s0 = v0;
                goto L_0048da08;
            }
        L_0048d9e8:
            charge(ctx, 8);
            v1 = 258;
            v0 = lui(0x8000);
            sw(v1, sp, 0x30);
            a0 = v0 | 0x4;
            jal(ctx, 0x48D9F4u, gen::fn_sub_4C1D10_004c1d10);
            sw(v0, sp, 0x34);
            a0 = addiu(sp, 0x30);
            jal(ctx, 0x48DA00u, gen::fn_sub_4C1C50_004c1c50);
        }
    L_0048da08:
        charge(ctx, 3);
        a0 = s1;
        a1 = 0;
        jal(ctx, 0x48DA0Cu, gen::fn_sub_4C5780_004c5780);
    }
    // 0x0048da14 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = s0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x004906D0 j_RpClumpDestroy -- 8 bytes; leaf frame (no stack)
// Tail jump to RpClumpDestroy (sub_491EA0).
void j_RpClumpDestroy(EEContext& ctx) {
    using namespace hg;
    // 0x004906d0
    enter(ctx, 2);  // entry check point + this block's cycles
    gen::fn_sub_491EA0_00491ea0(ctx);  // tail call
}

// 0x004906E0 j_RpAtomicDestroy -- 8 bytes; leaf frame (no stack)
// Tail jump to RpAtomicDestroy (sub_491A80).
void j_RpAtomicDestroy(EEContext& ctx) {
    using namespace hg;
    // 0x004906e0
    enter(ctx, 2);  // entry check point + this block's cycles
    gen::fn_sub_491A80_00491a80(ctx);  // tail call
}

// 0x00490810 sub_490810 -- 80 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// RW wrapper over sub_491100.
void sub_490810(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00490810
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a0, 76);
    v0 = v0 & 0x2;
    s0 = a0;
    if (v0 != 0) {
        // 0x00490840
        charge(ctx, 4);
        jal(ctx, 0x490840u, gen::fn_sub_491100_00491100);
        lbu(v1, s0, 3);
        backedge(ctx);
    } else {
        // 0x0049082c
        charge(ctx, 1);
        lbu(v1, s0, 3);
    }
    // 0x00490830
    charge(ctx, 4);
    v0 = s0;
    v1 = v1 | 0x1;
    sb(v1, s0, 3);
    // 0x00490850
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x004AE070 sub_4AE070 -- 80 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
// RW wrapper over sub_4C33D0.
void sub_4AE070(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f13{ctx, 13};
    // 0x004ae070
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = 0x3F800000;
    sd(ra, sp, 0x10);
    a1 = addiu(sp, 0x20);
    sq(s0, sp, 0x0);
    a2 = 1;
    s0 = a0;
    sw(v0, sp, 0x28);
    swc1(f12, sp, 0x20);
    a0 = addiu(s0, 16);
    link(ctx, 0x4AE098u);  // $ra first: the delay slot below depends on it
    swc1(f13, sp, 0x24);
    call(ctx, gen::fn_sub_4C33D0_004c33d0);
    lw(v1, s0, 8);
    v0 = s0;
    v1 = v1 | 0x2;
    sw(v1, s0, 8);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x004AE0C0 sub_4AE0C0 -- 76 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
// RW wrapper over sub_4C35D0.
void sub_4AE0C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f13{ctx, 13};
    // 0x004ae0c0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    a2 = 1;
    sd(ra, sp, 0x10);
    a1 = addiu(sp, 0x20);
    sq(s0, sp, 0x0);
    s0 = a0;
    sw(zero, sp, 0x28);
    swc1(f12, sp, 0x20);
    a0 = addiu(s0, 16);
    link(ctx, 0x4AE0E4u);  // $ra first: the delay slot below depends on it
    swc1(f13, sp, 0x24);
    call(ctx, gen::fn_sub_4C35D0_004c35d0);
    lw(v1, s0, 8);
    v0 = s0;
    v1 = v1 | 0x2;
    sw(v1, s0, 8);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x004AEF60 sub_4AEF60 -- 452 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// RW frame hierarchy walk (recursive): per-frame matrix / object updates.
void sub_4AEF60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004aef60
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v0 = 2;
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a0, 8);
    v1 = v1 & 0x2;
    s1 = 0;
    if (v1 == v0) {
        // 0x004af038
        charge(ctx, 6);
        a0 = addiu(s3, 16);
        jal(ctx, 0x4AF038u, gen::fn_sub_4AAB40_004aab40);
        jal(ctx, 0x4AF040u, gen::fn_sub_4AB0C0_004ab0c0);
        a2 = addiu(s3, 80);
        a1 = 8;
        for (;;) {
            // 0x004af050
            charge(ctx, 8);
            lw(a0, v0, 0);
            a1 = addiu(a1, -1);
            lw(v1, v0, 4);
            sw(a0, a2, 0);
            v0 = addiu(v0, 8);
            sw(v1, a2, 4);
            a2 = addiu(a2, 8);
            if (i64(a1) <= 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004af070
        charge(ctx, 6);
        lw(v1, s3, 8);
        v0 = si(-3);
        s1 = 1;
        v0 = v1 & v0;
        sw(v0, s3, 8);
        backedge(ctx);
    } else {
        // 0x004aef90
        charge(ctx, 2);
        a0 = addiu(s3, 80);
        jal(ctx, 0x4AEF90u, gen::fn_sub_4AAC70_004aac70);
    }
    // 0x004aef98
    charge(ctx, 7);
    link(ctx, 0x4AEF98u);  // $ra first: the delay slot below depends on it
    lw(a0, s3, 184);
    call(ctx, gen::fn_sub_4C2090_004c2090);
    lw(v1, s3, 180);
    v1 = sll(v1, 3);
    s0 = addu(v0, v1);
    s2 = v0;
    if (v0 != s0) {
        for (;;) {
            // 0x004aefb4
            charge(ctx, 3);
            v0 = 1;
            if (s1 == v0) {
                // 0x004af088
                charge(ctx, 5);
                lw(v1, s2, 0);
                lw(v0, v1, 8);
                v0 = v0 | 0x2;
                sw(v0, v1, 8);
                backedge(ctx);
            }
            // 0x004aefc0
            charge(ctx, 5);
            lw(a0, s2, 0);
            v0 = 1;
            lw(v1, a0, 0);
            if (v1 == v0) {
                // 0x004af0a0
                charge(ctx, 4);
                jal(ctx, 0x4AF0A0u, gen::fn_sub_4AEF60_004aef60);
                backedge(ctx);
            } else {
                // 0x004aefd4
                charge(ctx, 5);
                lw(v1, a0, 8);
                v0 = 2;
                v1 = v1 & 0x2;
                if (v1 == v0) {
                    // 0x004af0b0
                    charge(ctx, 8);
                    a0 = addiu(a0, 16);
                    jal(ctx, 0x4AF0B0u, gen::fn_sub_4AAB40_004aab40);
                    jal(ctx, 0x4AF0B8u, gen::fn_sub_4AB0C0_004ab0c0);
                    lw(v1, s2, 0);
                    a1 = 8;
                    a2 = addiu(v1, 80);
                    for (;;) {
                        // 0x004af0d0
                        charge(ctx, 8);
                        lw(a0, v0, 0);
                        a1 = addiu(a1, -1);
                        lw(v1, v0, 4);
                        sw(a0, a2, 0);
                        v0 = addiu(v0, 8);
                        sw(v1, a2, 4);
                        a2 = addiu(a2, 8);
                        if (i64(a1) <= 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004af0f0
                    charge(ctx, 6);
                    lw(a0, s2, 0);
                    v0 = si(-3);
                    lw(v1, a0, 8);
                    v0 = v1 & v0;
                    sw(v0, a0, 8);
                    backedge(ctx);
                } else {
                    // 0x004aefe8
                    charge(ctx, 2);
                    a0 = addiu(a0, 80);
                    jal(ctx, 0x4AEFE8u, gen::fn_sub_4AAC70_004aac70);
                }
                // 0x004aeff0
                charge(ctx, 5);
                lw(a1, s2, 0);
                v0 = 3;
                lw(v1, a1, 0);
                if (v1 == v0) {
                    // 0x004af004
                    charge(ctx, 3);
                    a0 = addiu(a1, 208);
                    a1 = addiu(a1, 80);
                    jal(ctx, 0x4AF008u, gen::fn_sub_4C32A0_004c32a0);
                }
            }
            // 0x004af010
            charge(ctx, 5);
            jal(ctx, 0x4AF010u, gen::fn_sub_4AAD50_004aad50);
            s2 = addiu(s2, 8);
            if (s2 == s0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004af024
        charge(ctx, 1);
    }
    // 0x004af028
    charge(ctx, 4);
    jal(ctx, 0x4AF028u, gen::fn_sub_4AAD50_004aad50);
    v0 = s3;
    // 0x004af108
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x004B4C70 sub_4B4C70 -- 76 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// RW wrapper over sub_4B4A70.
void sub_4B4C70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b4c70
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a0, 8);
    s0 = a0;
    if (v0 != 0) {
        // 0x004b4c90
        charge(ctx, 6);
        a1 = 0x4B0000;
        a2 = 0;
        a1 = addiu(a1, 18320);  // &sub_4B4790
        jal(ctx, 0x4B4C98u, gen::fn_sub_4B4A70_004b4a70);
        if (v0 != 0) {
            backedge(ctx);
            goto L_004b4c88;
        }
        // 0x004b4ca8
        charge(ctx, 1);
        v0 = 0;
        // 0x004b4cac (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(ra, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x20);
        return;
    }
L_004b4c88:
    charge(ctx, 2);
    v0 = s0;
    // 0x004b4cac (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x004B4D60 sub_4B4D60 -- 8 bytes; leaf frame (no stack)
// RW getter: returns the word at a0+36.
void sub_4B4D60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x004b4d60
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, 36);
}

// 0x004B5000 sub_4B5000 -- 620 bytes; frame 0x70: ra sp+0x50, s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// RW plugin object build (sub_4B1A40 .. sub_4B3CC0, sub_4C21E0).
void sub_4B5000(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23};
    // 0x004b5000
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f23, sp, 0xC);
    s0 = a0;
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lw(a0, a0, 8);
    mtc1(zero, f22);
    mov_s(f23, f12);
    mov_s(f21, f22);
    mov_s(f20, f22);
    jal(ctx, 0x4B503Cu, gen::fn_sub_4C21E0_004c21e0);
    lw(a0, s0, 8);
    s1 = v0;
    jal(ctx, 0x4B5048u, gen::fn_sub_4C2090_004c2090);
    s2 = v0;
    if (s2 != s1) {
        for (;;) {
            // 0x004b505c
            charge(ctx, 4);
            lw(v0, s2, 0);
            v0 = v0 & 0x1;
            if (v0 == 0) {
                // 0x004b506c
                charge(ctx, 3);
                lw(v0, s2, 24);
                if (v0 != 0) {
                    goto L_004b50cc;
                }
                // 0x004b5078
                charge(ctx, 4);
                a0 = addiu(s2, 4);
                jal(ctx, 0x4B5078u, gen::fn_sub_4B1A80_004b1a80);
                if (i64(v0) <= 0) {
                    goto L_004b50b8;
                }
                goto L_004b5088_4;
            }
        L_004b50b8:
            charge(ctx, 3);
            s2 = addiu(s2, 60);
            if (s2 == s1) {
                break;
            }
            backedge(ctx);
        }
        // 0x004b50c4
        charge(ctx, 2);
    }
L_004b50f4:
    charge(ctx, 5);
    mtc1(zero, f0);
    c_eq_s(f20, f0);
    if (cond(ctx)) {
        // 0x004b51e0
        charge(ctx, 2);
        v0 = s0;
    } else {
        // 0x004b5108
        charge(ctx, 7);
        v0 = 0x38D10000;
        v0 = v0 | 0xB717;
        mtc1(v0, f0);
        c_le_s(f23, f0);
        if (!cond(ctx)) {
            for (;;) {
                // 0x004b5124
                charge(ctx, 4);
                sub_s(f0, f21, f22);
                c_le_s(f23, f0);
                if (cond(ctx)) {
                    // 0x004b5150
                    charge(ctx, 4);
                    s1 = 0;
                    swc1(f23, sp, 0x6C);
                    mtc1(zero, f23);
                } else {
                    // 0x004b5134
                    charge(ctx, 6);
                    sub_s(f23, f23, f0);
                    s1 = 1;
                    add_s(f22, f22, f0);
                    add_s(f21, f21, f20);
                    swc1(f0, sp, 0x6C);
                }
                // 0x004b5160
                charge(ctx, 7);
                a1 = 0x4B0000;
                a0 = s0;
                a1 = addiu(a1, 19824);  // &sub_4B4D70
                a2 = addiu(sp, 0x6C);
                jal(ctx, 0x4B516Cu, gen::fn_sub_4B4A70_004b4a70);
                if (v0 == 0) {
                    goto L_004b51e8;
                }
                // 0x004b517c
                charge(ctx, 2);
                if (s1 != 0) {
                    // 0x004b5184
                    charge(ctx, 5);
                    a0 = s0;
                    jal(ctx, 0x4B5184u, gen::fn_sub_4B3CC0_004b3cc0);
                    a0 = s0;
                    a1 = addiu(s0, 44);
                    jal(ctx, 0x4B5190u, gen::fn_sub_4B5380_004b5380);
                }
                // 0x004b5198
                charge(ctx, 5);
                link(ctx, 0x4B5198u);  // $ra first: the delay slot below depends on it
                lw(a0, s0, 8);
                call(ctx, gen::fn_sub_4C2120_004c2120);
                s1 = v0;
                if (i64(s1) <= 0) {
                    // 0x004b51ac
                    charge(ctx, 1);
                    goto L_004b51b0;
                }
                // 0x004b51f0
                charge(ctx, 6);
                link(ctx, 0x4B51F0u);  // $ra first: the delay slot below depends on it
                lw(a0, s0, 8);
                call(ctx, gen::fn_sub_4C2090_004c2090);
                at = slt(0, s1);
                s3 = v0;
                s2 = 0;
                if (at == 0) {
                    backedge(ctx);
                L_004b51b0:
                    charge(ctx, 2);
                    v0 = si(-1);
                    sw(v0, s0, 68);
                } else {
                    for (;;) {
                        // 0x004b5208
                        charge(ctx, 7);
                        a0 = s0;
                        a1 = s3;
                        a2 = 0;
                        link(ctx, 0x4B5214u);  // $ra first: the delay slot below depends on it
                        sw(s2, s0, 68);
                        call(ctx, gen::fn_sub_4B4EB0_004b4eb0);
                        if (v0 == s0) {
                            // 0x004b5224
                            charge(ctx, 4);
                            s2 = addiu(s2, 1);
                            v0 = slt(s2, s1);
                            s3 = addiu(s3, 60);
                            if (v0 == 0) {
                                goto L_004b5234_27;
                            }
                            backedge(ctx);
                            continue;
                        }
                        backedge(ctx);
                        break;
                    }
                }
                // 0x004b51b8
                charge(ctx, 7);
                v0 = 0x38D10000;
                v0 = v0 | 0xB717;
                mtc1(v0, f0);
                c_le_s(f23, f0);
                if (cond(ctx)) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004b51d4
            charge(ctx, 1);
        }
        // 0x004b51d8
        charge(ctx, 2);
        v0 = s0;
    }
    // 0x004b5240 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x50);
    lq(s3, sp, 0x40);
    lwc1(f23, sp, 0xC);
    lq(s2, sp, 0x30);
    lwc1(f22, sp, 0x8);
    lq(s1, sp, 0x20);
    lwc1(f21, sp, 0x4);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x70);
    return;
L_004b5088_4:
    charge(ctx, 12);
    a1 = addiu(v0, -1);
    a0 = addiu(s2, 4);
    jal(ctx, 0x4B508Cu, gen::fn_sub_4B1A40_004b1a40);
    lwc1(f20, v0, 0);
    a0 = addiu(s2, 4);
    jal(ctx, 0x4B5098u, gen::fn_sub_4B1AE0_004b1ae0);
    sub_s(f20, f0, f20);
    a0 = addiu(s2, 4);
    mov_s(f21, f0);
    jal(ctx, 0x4B50A8u, gen::fn_sub_4B1A60_004b1a60);
    sub_s(f22, f0, f20);
    goto L_004b50f4;
L_004b50cc:
    charge(ctx, 10);
    a0 = addiu(s2, 4);
    jal(ctx, 0x4B50CCu, gen::fn_sub_4B1AE0_004b1ae0);
    mov_s(f20, f0);
    a0 = addiu(s2, 4);
    jal(ctx, 0x4B50D8u, gen::fn_sub_4B1A60_004b1a60);
    a0 = addiu(s2, 4);
    mov_s(f22, f0);
    jal(ctx, 0x4B50E4u, gen::fn_sub_4B1B60_004b1b60);
    sub_s(f20, f0, f20);
    mov_s(f21, f0);
    goto L_004b50f4;
L_004b51e8:
    charge(ctx, 2);
    v0 = 0;
    // 0x004b5240 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x50);
    lq(s3, sp, 0x40);
    lwc1(f23, sp, 0xC);
    lq(s2, sp, 0x30);
    lwc1(f22, sp, 0x8);
    lq(s1, sp, 0x20);
    lwc1(f21, sp, 0x4);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x70);
    return;
L_004b5234_27:
    charge(ctx, 2);
    backedge(ctx);
    goto L_004b51b0;
}

// 0x004B78B0 sub_4B78B0 -- 284 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// RW object walk with two callbacks through function pointers (type_info names).
void sub_4B78B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b78b0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a0, 0);
    s0 = a0;
    v1 = addiu(v0, 20);
    lw(v0, v0, 20);
    if (s0 == v0) {
        // 0x004b798c
        charge(ctx, 2);
        sw(zero, v1, 0);
        backedge(ctx);
    }
    // 0x004b78dc
    charge(ctx, 8);
    lw(s1, s0, 0);
    link(ctx, 0x4B78E0u);  // $ra first: the delay slot below depends on it
    lw(a0, s1, 16);
    call(ctx, gen::fn_name__C9type_info_1_004c21d0);
    lw(a0, s1, 16);
    s2 = v0;
    jal(ctx, 0x4B78ECu, gen::fn_sub_4C21E0_004c21e0);
    if (s2 != v0) {
        for (;;) {
            // 0x004b78fc
            charge(ctx, 3);
            lw(v1, s2, 0);
            if (s0 == v1) {
                goto L_004b7908_3;
            }
            // 0x004b7938
            charge(ctx, 3);
            s2 = addiu(s2, 4);
            if (s2 == v0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004b7944
        charge(ctx, 1);
    }
L_004b7948:
    charge(ctx, 8);
    link(ctx, 0x4B7948u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 4);
    call(ctx, gen::fn_sub_4C21E0_004c21e0);
    lw(a0, s0, 4);
    s1 = v0;
    jal(ctx, 0x4B7954u, gen::fn_name__C9type_info_1_004c21d0);
    s2 = v0;
    if (s2 == s1) {
        // 0x004b7994
        charge(ctx, 1);
        lw(a0, s0, 4);
    } else {
        for (;;) {
            // 0x004b7968
            charge(ctx, 7);
            lw(v0, s0, 0);
            lw(a0, s2, 0);
            lw(v0, v0, 28);
            s2 = addiu(s2, 4);
            jalr(ctx, 0x4B7974u, v0.u());
            if (s2 == s1) {
                break;
            }
            backedge(ctx);
        }
        // 0x004b7984
        charge(ctx, 2);
        lw(a0, s0, 4);
    }
    // 0x004b7998
    charge(ctx, 13);
    jal(ctx, 0x4B7998u, gen::fn_sub_4C20B0_004c20b0);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    a0 = s0;
    jalr(ctx, 0x4B79A8u, v0.u());
    ld(ra, sp, 0x30);
    v0 = 1;
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
    return;
L_004b7908_3:
    charge(ctx, 12);
    link(ctx, 0x4B7908u);  // $ra first: the delay slot below depends on it
    lw(a0, s1, 16);
    call(ctx, gen::fn_sub_4C2120_004c2120);
    lw(a0, s1, 16);
    a1 = addiu(v0, -1);
    jal(ctx, 0x4B7914u, gen::fn_sub_4C21B0_004c21b0);
    lw(v0, v0, 0);
    sw(v0, s2, 0);
    lw(a0, s1, 16);
    a1 = 1;
    jal(ctx, 0x4B7928u, gen::fn_sub_4C2080_004c2080);
    goto L_004b7948;
}

// 0x004C0820 sub_4C0820 -- 8 bytes; leaf frame (no stack)
// RW getter: returns the word at a0+16.
void sub_4C0820(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x004c0820
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, 16);
}

// 0x004C3EE0 sub_4C3EE0 -- 412 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// RW free-list free (the retail RW memory slot 0x96018C holds it) [proposed name _rwFreeListFreeReal]: returns an
// entry to its block list.
void sub_4C3EE0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c3ee0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a0, 8);
    s0 = a0;
    t0 = addiu(s0, 16);
    lw(a0, a0, 16);
    if (a0 != t0) {
        for (;;) {
            // 0x004c3f04
            charge(ctx, 5);
            v0 = addu(a0, v1);
            a3 = addiu(v0, 8);
            v0 = sltu(a1, a3);
            if (v0 == 0) {
                // 0x004c3f18
                charge(ctx, 7);
                lw(a2, s0, 0);
                lw(v0, s0, 4);
                mult(v0, v0, a2);
                v0 = addu(a3, v0);
                at = sltu(v0, a1);
                if (at != 0) {
                    goto L_004c4058;
                }
                goto L_004c3f34_3;
            }
        L_004c4058:
            charge(ctx, 3);
            lw(a0, a0, 0);
            if (a0 == t0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004c4064
        charge(ctx, 1);
    }
    // 0x004c4068
    charge(ctx, 1);
    v0 = 0;
    // 0x004c406c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
    return;
L_004c3f34_3:
    charge(ctx, 21);
    v0 = subu(a1, a3);
    divu(v0, a2);
    a3 = 128;
    mflo(t0);
    v0 = addiu(a0, 8);
    a2 = srl(t0, 3);
    a1 = sll(a2, 3);
    t0 = subu(t0, a1);
    a2 = addu(v0, a2);
    lbu(a1, a2, 0);
    a3 = srav(a3, t0);
    a3 = a3 & 0xFF;
    a3 = nor(a3, 0);
    a3 = a3 & 0xFF;
    a1 = a1 & a3;
    sb(a1, a2, 0);
    lw(a1, s0, 24);
    a1 = a1 & 0x2;
    if (a1 != 0) {
        // 0x004c3f88
        charge(ctx, 4);
        at = sltu(0, v1);
        t5 = 0;
        a1 = 0;
        if (at != 0) {
            // 0x004c3f98
            charge(ctx, 3);
            at = sltiu(v1, 9);
            t7 = addiu(v1, -8);
            if (at == 0) {
                for (;;) {
                    // 0x004c3fa4
                    charge(ctx, 20);
                    t6 = addu(v0, a1);
                    lbu(t0, t6, 0);
                    a1 = addiu(a1, 8);
                    lbu(a3, t6, 1);
                    a2 = sltu(a1, t7);
                    lbu(t4, t6, 2);
                    lbu(t3, t6, 3);
                    lbu(t2, t6, 4);
                    lbu(t1, t6, 5);
                    t5 = addu(t5, t0);
                    t5 = addu(t5, a3);
                    lbu(t0, t6, 6);
                    lbu(a3, t6, 7);
                    t4 = addu(t5, t4);
                    t3 = addu(t4, t3);
                    t2 = addu(t3, t2);
                    t1 = addu(t2, t1);
                    t0 = addu(t1, t0);
                    t5 = addu(t0, a3);
                    if (a2 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004c3ff4
                charge(ctx, 1);
            }
            // 0x004c3ff8
            charge(ctx, 3);
            at = sltu(a1, v1);
            if (at != 0) {
                for (;;) {
                    // 0x004c4004
                    charge(ctx, 7);
                    a2 = addu(v0, a1);
                    lbu(a3, a2, 0);
                    a1 = addiu(a1, 1);
                    a2 = sltu(a1, v1);
                    t5 = addu(t5, a3);
                    if (a2 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
        }
        // 0x004c4020
        charge(ctx, 2);
        if (t5 == 0) {
            // 0x004c4028
            charge(ctx, 10);
            lw(a1, a0, 0);
            v0 = 0x960000;
            lw(v1, a0, 4);
            sw(a1, v1, 0);
            lw(a1, a0, 4);
            lw(v1, a0, 0);
            sw(a1, v1, 4);
            lw(v0, v0, 380);  // 0x96017C
            jalr(ctx, 0x4C4048u, v0.u());
        }
    }
    // 0x004c4050
    charge(ctx, 2);
    v0 = s0;
    // 0x004c406c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x004C5FC0 sub_4C5FC0 -- 64 bytes; leaf frame (no stack)
// RW: unlinks a0's pending entry (+56), then tail-calls the free slot *0x96018C(a1, a0).
void sub_4C5FC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x004c5fc0
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, 56);
    lw(v0, v1, 16);
    a2 = a0;
    if (v0 != 0) {
        // 0x004c5fd0
        charge(ctx, 6);
        lw(v0, v1, 4);
        sw(v0, v1, 0);
        lw(v0, a2, 56);
        sw(zero, v0, 16);
        lw(v0, a2, 56);
        sw(zero, v0, 20);
    }
    // 0x004c5fe8
    charge(ctx, 6);
    v0 = 0x960000;
    a0 = a1;
    lw(v0, v0, 396);  // 0x96018C
    a1 = a2;
    tail(ctx, v0.u());  // jr: the target's entry point
}

// 0x004C7100 sub_4C7100 -- 188 bytes; leaf frame (no stack)
// Case-insensitive string compare (A-Z lowered): 0 for a null argument, else the first difference (data-referenced).
void sub_4C7100(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x004c7100
    enter(ctx, 2);  // entry check point + this block's cycles
    if (a0 != 0) {
        // 0x004c7108
        charge(ctx, 2);
        if (a1 == 0) {
            goto L_004c71b0;
        }
        for (;;) {
            // 0x004c7110
            charge(ctx, 4);
            lb(a3, a0, 0);
            v0 = slti(a3, 65);
            lb(a2, a1, 0);
            if (v0 == 0) {
                // 0x004c7120
                charge(ctx, 3);
                at = slti(a3, 91);
                if (at != 0) {
                    // 0x004c712c
                    charge(ctx, 3);
                    v0 = addiu(a3, 32);
                    a3 = dsll32(v0, 24);
                    a3 = dsra32(a3, 24);
                }
            }
            // 0x004c7138
            charge(ctx, 5);
            v1 = dsll32(a2, 24);
            v1 = dsra32(v1, 24);
            v0 = slti(v1, 65);
            if (v0 == 0) {
                // 0x004c714c
                charge(ctx, 3);
                at = slti(v1, 91);
                if (at != 0) {
                    // 0x004c7158
                    charge(ctx, 4);
                    v0 = addiu(a2, 32);
                    a2 = dsll32(v0, 24);
                    a2 = dsra32(a2, 24);
                }
            }
            // 0x004c7168
            charge(ctx, 6);
            v1 = dsll32(a2, 24);
            v0 = dsll32(a3, 24);
            v1 = dsra32(v1, 24);
            v0 = dsra32(v0, 24);
            if (v0 != v1) {
                goto L_004c71a8;
            }
            // 0x004c7180
            charge(ctx, 3);
            a0 = addiu(a0, 1);
            a1 = addiu(a1, 1);
            if (a3 == 0) {
                goto L_004c7198;
            }
            // 0x004c718c
            charge(ctx, 2);
            if (a2 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004c7194
        charge(ctx, 1);
    L_004c7198:
        charge(ctx, 2);
        if (v0 == v1) {
            goto L_004c71b0;
        }
        // 0x004c71a0
        charge(ctx, 2);
        v0 = subu(v0, v1);
        // 0x004c71b4 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_004c71b0:
    charge(ctx, 1);
    v0 = 0;
    // 0x004c71b4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_004c71a8:
    charge(ctx, 2);
    v0 = subu(v0, v1);
    // 0x004c71b4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x004CA500 sub_4CA500 -- 8 bytes; leaf frame (no stack)
// RW getter: returns the global *0x7CE928.
void sub_4CA500(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, gp{ctx, 28};
    // 0x004ca500
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, gp, -17352);  // 0x7CE928
}

// 0x004CF5C0 sub_4CF5C0 -- 208 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// RW debug formatter: hex digits from "0123456789abcdef" through an output callback.
void sub_4CF5C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004cf5c0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = 109;
    sd(ra, sp, 0x20);
    v1 = 0;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    sb(v0, sp, 0x3C);
    v0 = a2 & 0xFF;
    s0 = a1;
    if (i64(v0) > 0) {
        // 0x004cf5e8
        charge(ctx, 3);
        at = slti(v0, 16);
        if (at != 0) {
            // 0x004cf5f4
            charge(ctx, 1);
            v1 = 1;
        }
    }
    // 0x004cf5f8
    charge(ctx, 2);
    if (v1 == 0) {
        // 0x004cf618
        charge(ctx, 1);
        v1 = 0;
    } else {
        // 0x004cf600
        charge(ctx, 6);
        v0 = 0x7C0000;
        v1 = a2 & 0xFF;
        v0 = addiu(v0, -13296);  // "0123456789abcdef"
        v0 = addu(v0, v1);
        lb(v1, v0, 0);
    }
    // 0x004cf61c
    charge(ctx, 6);
    v0 = addiu(sp, 0x3D);
    sb(v1, v0, 0);
    v0 = dsll32(v1, 24);
    v0 = dsra32(v0, 24);
    sb(zero, sp, 0x3E);
    if (v0 != 0) {
        // 0x004cf63c
        charge(ctx, 7);
        s1 = 0x960000;
        s1 = addiu(s1, 324);  // &0x960144
        lw(v0, s1, 0);  // 0x960144
        a1 = addiu(sp, 0x3C);
        jalr(ctx, 0x4CF648u, v0.u());
        if (s0 == 0) {
            backedge(ctx);
        } else {
            // 0x004cf658
            charge(ctx, 3);
            lb(v0, s0, 0);
            if (v0 == 0) {
                backedge(ctx);
            } else {
                // 0x004cf664
                charge(ctx, 6);
                lw(v0, s1, 0);
                a0 = s0;
                a1 = addiu(sp, 0x3C);
                jalr(ctx, 0x4CF66Cu, v0.u());
                backedge(ctx);
            }
        }
    }
    // 0x004cf634
    charge(ctx, 2);
    v0 = 1;
    // 0x004cf67c
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x004D09D0 sub_4D09D0 -- 228 bytes; leaf frame (no stack)
// Case-insensitive prefix match (a-z raised): 0 at the first difference, stops at either string's end.
void sub_4D09D0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    check_events(ctx);  // entry check point (the first block heads a loop)
    for (;;) {
        // 0x004d09d0
        charge(ctx, 5);
        lb(v1, a0, 0);
        v0 = sltu(0, v1);
        v0 = v0 ^ 0x1;
        if (v0 != 0) {
            goto L_004d0a90;
        }
        // 0x004d09e4
        charge(ctx, 3);
        lb(v0, a1, 0);
        if (v0 == 0) {
            goto L_004d0a90;
        }
        // 0x004d09f0
        charge(ctx, 6);
        a3 = dsll32(v1, 24);
        a2 = dsll32(v0, 24);
        a3 = dsra32(a3, 24);
        v0 = slti(a3, 97);
        a2 = dsra32(a2, 24);
        if (v0 == 0) {
            // 0x004d0a08
            charge(ctx, 3);
            at = slti(a3, 123);
            if (at != 0) {
                // 0x004d0a14
                charge(ctx, 3);
                v0 = addiu(a3, -32);
                a3 = dsll32(v0, 24);
                a3 = dsra32(a3, 24);
            }
        }
        // 0x004d0a20
        charge(ctx, 5);
        v1 = dsll32(a2, 24);
        v1 = dsra32(v1, 24);
        v0 = slti(v1, 97);
        if (v0 == 0) {
            // 0x004d0a34
            charge(ctx, 3);
            at = slti(v1, 123);
            if (at != 0) {
                // 0x004d0a40
                charge(ctx, 4);
                v0 = addiu(a2, -32);
                a2 = dsll32(v0, 24);
                a2 = dsra32(a2, 24);
            }
        }
        // 0x004d0a50
        charge(ctx, 6);
        v1 = dsll32(a3, 24);
        v0 = dsll32(a2, 24);
        v1 = dsra32(v1, 24);
        v0 = dsra32(v0, 24);
        if (v1 != v0) {
            break;
        }
        // 0x004d0a68
        charge(ctx, 3);
        a0 = addiu(a0, 1);
        a1 = addiu(a1, 1);
        backedge(ctx);
    }
    // 0x004d0a78
    charge(ctx, 2);
    v0 = 0;
    // 0x004d0aac (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_004d0a80:
    charge(ctx, 2);
    v0 = 1;
    // 0x004d0aac (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_004d0a88:
    charge(ctx, 2);
    v0 = 0;
    // 0x004d0aac (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_004d0a90:
    charge(ctx, 5);
    lb(v0, a1, 0);
    v1 = dsll32(v1, 24);
    v1 = dsra32(v1, 24);
    if (v1 != v0) {
        backedge(ctx);
        goto L_004d0a88;
    }
    // 0x004d0aa4
    charge(ctx, 2);
    backedge(ctx);
    goto L_004d0a80;
}

// 0x004D84A0 sub_4D84A0 -- 32 bytes; leaf frame (no stack)
// Returns 4 when a0 != 0 and *a0 != 0, else 0.
void sub_4D84A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x004d84a0
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
    if (a0 != 0) {
        // 0x004d84a8
        charge(ctx, 3);
        lw(v1, a0, 0);
        if (v1 != 0) {
            // 0x004d84b4
            charge(ctx, 1);
            v0 = 4;
        }
    }
    // 0x004d84b8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x004DB350 sub_4DB350 -- 6992 bytes; frame 0x260: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// RW PS2 driver: the large GIF / VIF packet builder of a pipeline (data-referenced).
void sub_4DB350(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, t8{ctx, 24}, t9{ctx, 25}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004db350
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x260);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a1;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, -16968);  // 0x7CEAA8
    s3 = addu(s4, v0);
    jal(ctx, 0x4DB384u, gen::fn_sub_4D9520_004d9520);
    if (v0 != 0) {
        // 0x004db394
        charge(ctx, 4);
        lbu(v0, s4, 35);
        v0 = v0 & 0x60;
        if (v0 == 0) {
            // 0x004db6cc
            charge(ctx, 4);
            lbu(v0, s4, 33);
            v0 = v0 & 0xBF;
            sb(v0, s4, 33);
            backedge(ctx);
        }
        // 0x004db3a4
        charge(ctx, 23);
        sw(zero, s4, 4);
        sw(zero, s4, 8);
        sb(zero, s3, 23);
        sb(zero, s3, 52);
        sw(zero, s3, 56);
        sw(zero, s3, 60);
        sw(zero, s3, 64);
        sw(zero, s3, 68);
        sw(zero, s3, 72);
        sw(zero, s3, 76);
        sw(zero, s3, 80);
        sw(zero, s3, 84);
        sw(zero, s3, 88);
        sb(zero, s3, 54);
        lw(v0, s4, 12);
        sw(v0, s4, 40);
        lw(v0, s4, 16);
        sw(v0, s4, 44);
        lw(v0, s4, 4);
        sw(v0, s4, 36);
        lw(v1, s4, 12);
        if (v1 != 0) {
            // 0x004db400
            charge(ctx, 3);
            lw(a2, s4, 16);
            if (a2 == 0) {
                goto L_004dce58;
            }
            // 0x004db40c
            charge(ctx, 4);
            lbu(a1, s4, 32);
            v0 = 2;
            if (a1 == v0) {
                // 0x004db600
                charge(ctx, 5);
                lw(a1, gp, -17120);  // 0x7CEA10
                lw(a0, a1, 0);
                at = slt(a0, v1);
                if (at == 0) {
                    // 0x004db614
                    charge(ctx, 4);
                    lw(v0, a1, 4);
                    at = slt(v0, a2);
                    if (at != 0) {
                        goto L_004db624;
                    }
                L_004db658:
                    charge(ctx, 16);
                    lw(v1, a1, 8);
                    v0 = addiu(a0, 63);
                    v0 = sra(v0, 6);
                    v1 = addiu(v1, 7);
                    v1 = sra(v1, 3);
                    mult(v1, v1, v0);
                    v1 = sll(v1, 6);
                    v0 = 128;
                    sw(v1, s4, 24);
                    sw(zero, s4, 4);
                    lw(v1, s4, 4);
                    sw(v1, s4, 36);
                    lw(v1, s4, 24);
                    sw(v1, s4, 48);
                    sb(v0, s4, 33);
                L_004db6a4:
                    charge(ctx, 8);
                    lw(v1, gp, -16968);  // 0x7CEAA8
                    v0 = 1;
                    v1 = addu(s4, v1);
                    sw(zero, v1, 0);
                    lw(v1, gp, -16968);  // 0x7CEAA8
                    v1 = addu(s4, v1);
                    sw(zero, v1, 4);
                    goto L_004dce70;
                }
            L_004db624:
                charge(ctx, 3);
                lbu(v0, gp, -17112);  // 0x7CEA18
                if (v0 != 0) {
                    goto L_004db658;
                }
                // 0x004db630
                charge(ctx, 10);
                v1 = 1;
                v0 = lui(0x8000);
                sw(v1, sp, 0x1F8);
                a0 = v0 | 0x10;
                jal(ctx, 0x4DB63Cu, gen::fn_sub_4C1D10_004c1d10);
                sw(v0, sp, 0x1FC);
                a0 = addiu(sp, 0x1F8);
                jal(ctx, 0x4DB648u, gen::fn_sub_4C1C50_004c1c50);
                v0 = 0;
                goto L_004dce70;
            }
            // 0x004db41c
            charge(ctx, 3);
            v0 = 1;
            if (a1 == v0) {
                // 0x004db5ac
                charge(ctx, 12);
                lw(a3, gp, -17120);  // 0x7CEA10
                v1 = addiu(v1, 63);
                v1 = sra(v1, 6);
                mult(a1, v1, a2);
                lw(a0, a3, 0);
                lw(v1, a3, 4);
                a0 = addiu(a0, 63);
                a0 = sra(a0, 6);
                mult1(v1, a0, v1);
                at = slt(v1, a1);
                if (at == 0) {
                    // 0x004db5dc
                    charge(ctx, 9);
                    sw(zero, s4, 24);
                    v0 = 128;
                    sw(zero, s4, 4);
                    sb(v0, s4, 33);
                    lw(v0, s4, 4);
                    sw(v0, s4, 36);
                    lw(v0, s4, 24);
                    sw(v0, s4, 48);
                    goto L_004db6a4;
                }
                // 0x004dce34
                charge(ctx, 9);
                sw(v0, sp, 0x200);
                v0 = lui(0x8000);
                a0 = v0 | 0x10;
                jal(ctx, 0x4DCE3Cu, gen::fn_sub_4C1D10_004c1d10);
                sw(v0, sp, 0x204);
                a0 = addiu(sp, 0x200);
                jal(ctx, 0x4DCE48u, gen::fn_sub_4C1C50_004c1c50);
                v0 = 0;
                goto L_004dce70;
            }
            // 0x004db428
            charge(ctx, 2);
            if (a1 == 0) {
                // 0x004db50c
                charge(ctx, 34);
                lw(a2, s4, 20);
                a0 = 0x7C0000;
                v0 = 0x7C0000;
                a0 = addiu(a0, -13028);  // &0x7BCD1C
                v0 = addiu(v0, -12900);  // &0x7BCD9C
                a1 = sll(a2, 2);
                a0 = addu(a0, a1);
                v0 = addu(v0, a1);
                lw(a1, v0, 0);
                lw(a0, a0, 0);
                mult(v0, a2, v1);
                v0 = sra(v0, 3);
                sw(v0, s4, 24);
                lw(v1, s4, 16);
                lw(v0, s4, 24);
                mult1(v1, v1, v0);
                sw(v1, s3, 40);
                v0 = addiu(a0, -1);
                lw(v1, s4, 12);
                v0 = addu(v1, v0);
                divu(v0, a0);
                lw(v1, s4, 16);
                v0 = addiu(a1, -1);
                mflo(a0);
                v0 = addu(v1, v0);
                divu(v0, a1);
                mflo(v0);
                mult(v0, a0, v0);
                v0 = sll(v0, 11);
                sw(v0, s3, 48);
                lbu(v0, s4, 33);
                v0 = v0 & 0x80;
                if (v0 != 0) {
                    // 0x004db594
                    charge(ctx, 1);
                    sw(zero, s4, 4);
                    goto L_004db598;
                }
                // 0x004dcde0
                charge(ctx, 10);
                v0 = 0x30000;
                a1 = v0 | 0x411;
                v0 = 0x960000;
                lw(v0, v0, 376);  // 0x960178
                jt = v0.u();  // the target, read before the delay slot
                link(ctx, 0x4DCDF0u);  // $ra = the return address
                lw(a0, s3, 40);
                call_ptr(ctx, jt);
                sw(v0, s4, 4);
                lw(v0, s4, 4);
                if (v0 != 0) {
                    backedge(ctx);
                L_004db598:
                    charge(ctx, 5);
                    lw(v0, s4, 4);
                    sw(v0, s4, 36);
                    lw(v0, s4, 24);
                    sw(v0, s4, 48);
                    goto L_004db6a4;
                }
                // 0x004dce08
                charge(ctx, 11);
                v1 = 1;
                v0 = lui(0x8000);
                sw(v1, sp, 0x208);
                lw(a1, s3, 40);
                a0 = v0 | 0x13;
                jal(ctx, 0x4DCE18u, gen::fn_sub_4C1D10_004c1d10);
                sw(v0, sp, 0x20C);
                a0 = addiu(sp, 0x208);
                jal(ctx, 0x4DCE24u, gen::fn_sub_4C1C50_004c1c50);
                v0 = 0;
                goto L_004dce70;
            }
            // 0x004db430
            charge(ctx, 3);
            a0 = 4;
            if (a1 != a0) {
                // 0x004db43c
                charge(ctx, 3);
                a0 = 5;
                if (a1 == a0) {
                    // 0x004db450
                    charge(ctx, 4);
                    lbu(a0, s4, 35);
                    a0 = a0 & 0x60;
                    if (a0 != 0) {
                        // 0x004db6dc
                        charge(ctx, 9);
                        sw(v0, sp, 0x248);
                        v0 = lui(0x8000);
                        a0 = v0 | 0xD;
                        jal(ctx, 0x4DB6E4u, gen::fn_sub_4C1D10_004c1d10);
                        sw(v0, sp, 0x24C);
                        a0 = addiu(sp, 0x248);
                        jal(ctx, 0x4DB6F0u, gen::fn_sub_4C1C50_004c1c50);
                        v0 = 0;
                    } else {
                        // 0x004db460
                        charge(ctx, 12);
                        lw(t0, gp, -17120);  // 0x7CEA10
                        a0 = addiu(v1, 63);
                        a0 = sra(a0, 6);
                        mult(a3, a0, a2);
                        lw(a1, t0, 0);
                        lw(a0, t0, 4);
                        a1 = addiu(a1, 63);
                        a1 = sra(a1, 6);
                        mult1(a0, a1, a0);
                        at = slt(a0, a3);
                        if (at == 0) {
                            goto L_004db4b4;
                        }
                        // 0x004db490
                        charge(ctx, 9);
                        sw(v0, sp, 0x240);
                        v0 = lui(0x8000);
                        a0 = v0 | 0xD;
                        jal(ctx, 0x4DB498u, gen::fn_sub_4C1D10_004c1d10);
                        sw(v0, sp, 0x244);
                        a0 = addiu(sp, 0x240);
                        jal(ctx, 0x4DB4A4u, gen::fn_sub_4C1C50_004c1c50);
                        v0 = 0;
                    }
                    goto L_004dce70;
                }
                // 0x004db448
                charge(ctx, 2);
                v0 = 0;
                // 0x004db69c
                charge(ctx, 2);
                ld(ra, sp, 0x90);
                // 0x004dce74 (the shared epilogue, written out on this path)
                charge(ctx, 11);
                lq(fp, sp, 0x80);
                lq(s7, sp, 0x70);
                lq(s6, sp, 0x60);
                lq(s5, sp, 0x50);
                lq(s4, sp, 0x40);
                lq(s3, sp, 0x30);
                lq(s2, sp, 0x20);
                lq(s1, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x260);
                return;
            }
        L_004db4b4:
            charge(ctx, 13);
            lw(a1, s4, 20);
            a0 = 0x7C0000;
            v0 = 0x7C0000;
            a0 = addiu(a0, -13028);  // &0x7BCD1C
            v0 = addiu(v0, -12900);  // &0x7BCD9C
            a3 = v1;
            a1 = sll(a1, 2);
            a0 = addu(a0, a1);
            v0 = addu(v0, a1);
            lw(a1, a0, 0);
            lw(a0, v0, 0);
            t1 = si(-1);
            if (v1 == 0) {
                // 0x004db700
                charge(ctx, 1);
                v0 = 1;
            } else {
                for (;;) {
                    // 0x004db4e8
                    charge(ctx, 7);
                    a3 = srl(a3, 1);
                    t1 = addiu(t1, 1);
                    if (a3 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004db504
                charge(ctx, 2);
                v0 = 1;
            }
            // 0x004db704
            charge(ctx, 4);
            v0 = sllv(v0, t1);
            at = slt(v0, v1);
            if (at != 0) {
                // 0x004db714
                charge(ctx, 1);
                t1 = addiu(t1, 1);
            }
            // 0x004db718
            charge(ctx, 3);
            v0 = a2;
            t0 = si(-1);
            if (a2 != 0) {
                for (;;) {
                    // 0x004db724
                    charge(ctx, 7);
                    v0 = srl(v0, 1);
                    t0 = addiu(t0, 1);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x004db740
            charge(ctx, 5);
            v0 = 1;
            v0 = sllv(v0, t0);
            at = slt(v0, a2);
            if (at != 0) {
                // 0x004db754
                charge(ctx, 1);
                t0 = addiu(t0, 1);
            }
            // 0x004db758
            charge(ctx, 3);
            at = sltu(a1, v1);
            if (at == 0) {
                // 0x004db76c
                charge(ctx, 1);
                a3 = srl(a1, 6);
            } else {
                // 0x004db764
                charge(ctx, 2);
                a3 = srl(v1, 6);
            }
            // 0x004db770
            charge(ctx, 21);
            v0 = t1 & 0xF;
            a2 = t0 & 0xF;
            v1 = sll(v0, 26);
            v0 = sll(a3, 14);
            v1 = v1 | v0;
            v0 = sll(a2, 30);
            v1 = v0 | v1;
            v0 = sra(a2, 2);
            sw(v1, s3, 8);
            v0 = dsll32(v0, 0);
            v1 = 32;
            v0 = dsra32(v0, 0);
            sw(v0, s3, 12);
            lw(a2, gp, -20252);  // 0x7CDDD4
            v0 = 1;
            sh(a2, s3, 20);
            sb(v0, s3, 52);
            lbu(t0, s4, 35);
            a3 = t0 & 0x60;
            if (a3 == v1) {
                // 0x004db920
                charge(ctx, 17);
                lw(t1, s3, 8);
                t0 = 0x1300000;
                s6 = 16;
                a3 = 0x20000000;
                a2 = 5;
                t0 = t1 | t0;
                sw(t0, s3, 8);
                lw(t0, s3, 12);
                t0 = t0 | 0x4;
                sw(t0, s3, 12);
                lw(t0, s3, 12);
                a3 = t0 | a3;
                sw(a3, s3, 12);
                lbu(a3, s4, 35);
                a3 = a3 & 0xF;
                s2 = s6;
                if (a3 == a2) {
                    // 0x004db994
                    charge(ctx, 3);
                    s0 = 4;
                    a2 = 64;
                L_004db9e8:
                    charge(ctx, 9);
                    lw(a3, s4, 20);
                    lw(v0, s4, 12);
                    mult(v0, a3, v0);
                    v0 = sra(v0, 3);
                    sw(v0, s4, 24);
                    lbu(v0, s4, 35);
                    v0 = v0 & 0x80;
                    if (v0 == 0) {
                        // 0x004dbf10
                        charge(ctx, 49);
                        lw(a3, s4, 16);
                        lw(v0, s4, 24);
                        mult(t0, a3, v0);
                        s5 = si(-16);
                        t0 = addiu(t0, 15);
                        v0 = 0x400000;
                        t0 = t0 & s5;
                        a3 = 16384;
                        sw(t0, s3, 40);
                        v0 = v0 | 0x4;  // &0x400004
                        sw(a3, s3, 24);
                        sw(v0, s3, 28);
                        sw(a3, s3, 32);
                        sw(v0, s3, 36);
                        sb(zero, s3, 22);
                        sd(zero, sp, 0x1C0);
                        lw(v0, s4, 12);
                        v0 = addu(v0, a1);
                        v0 = addiu(v0, -1);
                        divu(v0, a1);
                        mflo(a3);
                        v0 = srl(a1, 6);
                        mult1(v0, v0, a3);
                        sw(zero, sp, 0x160);
                        v0 = dsll32(v0, 0);
                        v0 = dsrl32(v0, 0);
                        sd(v0, sp, 0x180);
                        lw(v0, s4, 12);
                        lw(a3, s4, 16);
                        v0 = addu(v0, a1);
                        v0 = addiu(v0, -1);
                        divu(v0, a1);
                        v0 = addiu(a0, -1);
                        mflo(t1);
                        v0 = addu(a3, v0);
                        divu(v0, a0);
                        mflo(t0);
                        mult(a3, t1, t0);
                        v0 = si(-2048);
                        a3 = sll(a3, 11);
                        a3 = a3 & v0;
                        sw(a3, s3, 48);
                        mult1(a3, s6, s2);
                        mult(s7, s0, a3);
                        sw(s7, s3, 44);
                        lw(a3, s3, 44);
                        if (a3 == 0) {
                            // 0x004dc8a0
                            charge(ctx, 2);
                            sw(zero, s3, 16);
                            backedge(ctx);
                        } else {
                            // 0x004dbfd4
                            charge(ctx, 5);
                            mult(a3, t1, a1);
                            lw(a1, s4, 12);
                            at = slt(a1, a3);
                            if (at == 0) {
                                // 0x004dbfe8
                                charge(ctx, 5);
                                mult(a1, t0, a0);
                                lw(a0, s4, 16);
                                at = slt(a0, a1);
                                if (at != 0) {
                                    goto L_004dc88c;
                                }
                                // 0x004dbffc
                                charge(ctx, 17);
                                a0 = addiu(v1, -1);
                                lw(a1, s3, 48);
                                a0 = addu(s2, a0);
                                divu(a0, v1);
                                a1 = srl(a1, 6);
                                sw(a1, s3, 16);
                                mflo(a0);
                                v1 = addiu(a2, -1);
                                v1 = addu(s6, v1);
                                divu(v1, a2);
                                mflo(v1);
                                mult(a0, v1, a0);
                                lw(v1, s3, 48);
                                a0 = sll(a0, 11);
                                v1 = addu(v1, a0);
                                v0 = v1 & v0;
                                sw(v0, s3, 48);
                                goto L_004dc040;
                            }
                        L_004dc88c:
                            charge(ctx, 5);
                            lw(v0, s3, 48);
                            v0 = srl(v0, 6);
                            v0 = addiu(v0, -4);
                            sw(v0, s3, 16);
                            backedge(ctx);
                        }
                    } else {
                        // 0x004dba0c
                        charge(ctx, 36);
                        lw(t3, s4, 12);
                        v1 = addiu(sp, 0x1D0);
                        lw(t2, s4, 16);
                        v0 = 1;
                        s1 = 0;
                        t4 = 0;
                        s7 = 0;
                        t0 = 0;
                        at = sltu(a1, t3);
                        sd(zero, v1, 0);
                        v1 = addiu(sp, 0x1C8);
                        sw(zero, sp, 0x25C);
                        sd(zero, v1, 0);
                        v1 = addiu(sp, 0x1E8);
                        sd(zero, sp, 0x1C0);
                        sd(zero, v1, 0);
                        v1 = addiu(sp, 0x1E0);
                        sd(v0, sp, 0x180);
                        sd(zero, v1, 0);
                        v1 = addiu(sp, 0x1D8);
                        sd(zero, v1, 0);
                        v1 = addiu(sp, 0x1F0);
                        sd(zero, v1, 0);
                        v1 = addiu(sp, 0x190);
                        sd(v0, v1, 0);
                        v1 = addiu(sp, 0x188);
                        sd(v0, v1, 0);
                        v1 = addiu(sp, 0x1A8);
                        sd(v0, v1, 0);
                        v1 = addiu(sp, 0x1A0);
                        sd(v0, v1, 0);
                        v1 = addiu(sp, 0x198);
                        sd(v0, v1, 0);
                        v1 = addiu(sp, 0x1B0);
                        sd(v0, v1, 0);
                        if (at == 0) {
                            // 0x004dbaa4
                            charge(ctx, 1);
                            v0 = srl(a1, 6);
                        } else {
                            // 0x004dba9c
                            charge(ctx, 2);
                            v0 = srl(t3, 6);
                        }
                        // 0x004dbaa8
                        charge(ctx, 26);
                        t1 = dsll32(v0, 0);
                        lw(fp, gp, -20256);  // 0x7CDDD0
                        v0 = addiu(a1, -1);
                        t1 = dsrl32(t1, 0);
                        sq(v0, sp, 0xB0);
                        a3 = addiu(sp, 0x180);
                        v0 = addiu(a0, -1);
                        a2 = addiu(sp, 0x1C0);
                        sq(v0, sp, 0xA0);
                        s5 = si(-16);
                        v0 = 0x7C0000;
                        t9 = srl(a1, 6);
                        v0 = addiu(v0, -12640);  // &0x7BCEA0
                        sq(v0, sp, 0xF0);
                        v0 = 0x7C0000;
                        v0 = addiu(v0, -12672);  // &0x7BCE80
                        sq(v0, sp, 0x100);
                        v0 = 0x7C0000;
                        v0 = addiu(v0, -12704);  // &0x7BCE60
                        sq(v0, sp, 0x110);
                        v0 = 0x7C0000;
                        v0 = addiu(v0, -12736);  // &0x7BCE40
                        sq(v0, sp, 0x120);
                        v0 = 0x7C0000;
                        v0 = addiu(v0, -12768);  // &0x7BCE20
                        sq(v0, sp, 0x130);
                        for (;;) {
                            // 0x004dbb10
                            charge(ctx, 2);
                            if (t3 != 0) {
                                // 0x004dbb18
                                charge(ctx, 2);
                                if (t2 != 0) {
                                    // 0x004dbb20
                                    charge(ctx, 3);
                                    at = sltu(s1, fp);
                                    if (at != 0) {
                                        // 0x004dbb2c
                                        charge(ctx, 2);
                                        lw(v0, s4, 12);
                                        // 0x004dbd4c
                                        charge(ctx, 3);
                                        v0 = slti(v0, 8);
                                        if (v0 != 0) {
                                            backedge(ctx);
                                        } else {
                                            // 0x004dbd58
                                            charge(ctx, 4);
                                            lw(v0, s4, 16);
                                            v0 = slti(v0, 8);
                                            if (v0 != 0) {
                                                backedge(ctx);
                                                goto L_004dbb34;
                                            }
                                            // 0x004dbd68
                                            charge(ctx, 3);
                                            v0 = sltiu(t3, 8);
                                            if (v0 == 0) {
                                                // 0x004dbd74
                                                charge(ctx, 3);
                                                at = sltiu(t2, 8);
                                                if (at == 0) {
                                                    backedge(ctx);
                                                    goto L_004dbb34;
                                                }
                                            }
                                            break;
                                        }
                                    L_004dbb34:
                                        charge(ctx, 9);
                                        lw(v0, s4, 20);
                                        mult(v0, v0, t3);
                                        mult(v0, t2, v0);
                                        at = sltu(a1, t3);
                                        v0 = srl(v0, 3);
                                        v0 = addiu(v0, 15);
                                        v0 = v0 & s5;
                                        s7 = addu(s7, v0);
                                        if (at == 0) {
                                            // 0x004dbb60
                                            charge(ctx, 1);
                                            v0 = t9;
                                        } else {
                                            // 0x004dbb58
                                            charge(ctx, 2);
                                            v0 = srl(t3, 6);
                                        }
                                        // 0x004dbb64
                                        charge(ctx, 22);
                                        v0 = dsll32(v0, 0);
                                        v0 = dsrl32(v0, 0);
                                        sd(v0, a3, 0);
                                        ld(v1, a3, 0);
                                        lw(v0, s4, 20);
                                        t5 = dsll(v1, 6);
                                        t7 = dsll32(t5, 0);
                                        t7 = dsra32(t7, 0);
                                        multu(t6, v0, t7);
                                        mfhi(t8);
                                        t5 = dsra32(t5, 0);
                                        pextlw(t6, t8, t6);
                                        mult1(t5, t5, v0);
                                        v0 = dsra32(v0, 0);
                                        mult(v0, t7, v0);
                                        v0 = t5 + v0;
                                        v0 = dsll32(v0, 0);
                                        v0 = v0 + t6;
                                        v0 = dsrl(v0, 3);
                                        v0 = dsll32(v0, 0);
                                        v0 = dsra32(v0, 0);
                                        if (t1 != v1) {
                                            // 0x004dc840
                                            charge(ctx, 19);
                                            lw(v1, s4, 12);
                                            t1 = addiu(s1, -1);
                                            t4 = srav(v1, t1);
                                            lq(v1, sp, 0xB0);
                                            v1 = addu(v1, t4);
                                            divu(v1, a1);
                                            lw(t4, s4, 16);
                                            t4 = srav(t4, t1);
                                            lq(t1, sp, 0xA0);
                                            t1 = addu(t1, t4);
                                            mflo(v1);
                                            divu(t1, a0);
                                            mflo(t1);
                                            mult(v1, v1, t1);
                                            v1 = sll(v1, 11);
                                            t0 = addu(t0, v1);
                                            v1 = si(-2048);
                                            t4 = t0 & v1;
                                            backedge(ctx);
                                        }
                                        // 0x004dbbbc
                                        charge(ctx, 14);
                                        v1 = dsll32(t4, 0);
                                        v1 = dsra32(v1, 0);
                                        t5 = 20;
                                        t0 = addiu(v1, 63);
                                        v1 = si(-64);
                                        t0 = t0 & v1;
                                        v1 = t0 & 0x7FF;
                                        sw(t0, sp, 0x25C);
                                        t4 = srl(v1, 8);
                                        lw(v1, s3, 8);
                                        v1 = srl(v1, 20);
                                        v1 = v1 & 0x3F;
                                        ld(t1, a3, 0);
                                        if (v1 != t5) {
                                            // 0x004dbbf4
                                            charge(ctx, 3);
                                            t5 = 19;
                                            if (v1 == t5) {
                                                // 0x004dbcb8
                                                charge(ctx, 11);
                                                t5 = sll(t4, 2);
                                                v1 = srl(t0, 11);
                                                lq(t4, sp, 0x100);
                                                v1 = sll(v1, 5);
                                                t4 = addu(t4, t5);
                                                lw(t4, t4, 0);
                                                v1 = addu(v1, t4);
                                                v1 = dsll32(v1, 0);
                                                v1 = dsrl32(v1, 0);
                                                sd(v1, a2, 0);
                                                goto L_004dbd0c;
                                            }
                                            // 0x004dbc00
                                            charge(ctx, 3);
                                            t5 = 10;
                                            if (v1 == t5) {
                                                // 0x004dbc8c
                                                charge(ctx, 11);
                                                t5 = sll(t4, 2);
                                                v1 = srl(t0, 11);
                                                lq(t4, sp, 0x110);
                                                v1 = sll(v1, 5);
                                                t4 = addu(t4, t5);
                                                lw(t4, t4, 0);
                                                v1 = addu(v1, t4);
                                                v1 = dsll32(v1, 0);
                                                v1 = dsrl32(v1, 0);
                                                sd(v1, a2, 0);
                                                goto L_004dbd0c;
                                            }
                                            // 0x004dbc0c
                                            charge(ctx, 3);
                                            t5 = 2;
                                            if (v1 == t5) {
                                                // 0x004dbc60
                                                charge(ctx, 11);
                                                t5 = sll(t4, 2);
                                                v1 = srl(t0, 11);
                                                lq(t4, sp, 0x120);
                                                v1 = sll(v1, 5);
                                                t4 = addu(t4, t5);
                                                lw(t4, t4, 0);
                                                v1 = addu(v1, t4);
                                                v1 = dsll32(v1, 0);
                                                v1 = dsrl32(v1, 0);
                                                sd(v1, a2, 0);
                                                goto L_004dbd0c;
                                            }
                                            // 0x004dbc18
                                            charge(ctx, 3);
                                            t5 = 1;
                                            if (v1 != t5) {
                                                // 0x004dbc24
                                                charge(ctx, 2);
                                                if (v1 == 0) {
                                                    goto L_004dbc34;
                                                }
                                                // 0x004dbc2c
                                                charge(ctx, 2);
                                                mult(v1, t2, v0);
                                                goto L_004dbd10;
                                            }
                                        L_004dbc34:
                                            charge(ctx, 11);
                                            t5 = sll(t4, 2);
                                            v1 = srl(t0, 11);
                                            lq(t4, sp, 0x130);
                                            v1 = sll(v1, 5);
                                            t4 = addu(t4, t5);
                                            lw(t4, t4, 0);
                                            v1 = addu(v1, t4);
                                            v1 = dsll32(v1, 0);
                                            v1 = dsrl32(v1, 0);
                                            sd(v1, a2, 0);
                                            goto L_004dbd0c;
                                        }
                                        // 0x004dbce4
                                        charge(ctx, 10);
                                        t5 = sll(t4, 2);
                                        v1 = srl(t0, 11);
                                        lq(t4, sp, 0xF0);
                                        v1 = sll(v1, 5);
                                        t4 = addu(t4, t5);
                                        lw(t4, t4, 0);
                                        v1 = addu(v1, t4);
                                        v1 = dsll32(v1, 0);
                                        v1 = dsrl32(v1, 0);
                                        sd(v1, a2, 0);
                                    L_004dbd0c:
                                        charge(ctx, 1);
                                        mult(v1, t2, v0);
                                    L_004dbd10:
                                        charge(ctx, 14);
                                        a3 = addiu(a3, 8);
                                        a2 = addiu(a2, 8);
                                        s1 = addiu(s1, 1);
                                        t3 = srl(t3, 1);
                                        v0 = dsll32(t0, 0);
                                        v1 = srl(v1, 2);
                                        v0 = dsra32(v0, 0);
                                        t2 = srl(t2, 1);
                                        v0 = addu(v0, v1);
                                        v1 = addiu(v0, 63);
                                        v0 = si(-64);
                                        t4 = v1 & v0;
                                        sw(t4, sp, 0x25C);
                                        backedge(ctx);
                                        continue;
                                    }
                                }
                            }
                            break;
                        }
                        // 0x004dbd80
                        charge(ctx, 87);
                        lw(v0, s3, 8);
                        a3 = addiu(sp, 0x1C0);
                        lw(a0, s4, 12);
                        t0 = addiu(sp, 0x180);
                        lw(a1, s4, 16);
                        t1 = addiu(sp, 0x160);
                        t2 = addiu(sp, 0x25C);
                        t3 = addiu(sp, 0x258);
                        v0 = srl(v0, 20);
                        a2 = v0 & 0x3F;
                        jal(ctx, 0x4DBDA4u, gen::fn_sub_4D9BC0_004d9bc0);
                        v0 = addiu(s1, -1);
                        sw(s7, s3, 40);
                        v0 = sll(v0, 2);
                        sb(v0, s3, 22);
                        v0 = addiu(sp, 0x1C8);
                        ld(a3, v0, 0);
                        v0 = addiu(sp, 0x188);
                        a3 = a3 & 0x3FFF;
                        ld(a2, v0, 0);
                        v0 = addiu(sp, 0x1D0);
                        a2 = dsll(a2, 14);
                        ld(a1, v0, 0);
                        a2 = a3 | a2;
                        v0 = addiu(sp, 0x190);
                        a1 = a1 & 0x3FFF;
                        ld(a0, v0, 0);
                        a1 = dsll(a1, 20);
                        a1 = a1 | a2;
                        v0 = addiu(sp, 0x1D8);
                        a0 = dsll32(a0, 2);
                        ld(v1, v0, 0);
                        a0 = a0 | a1;
                        v0 = addiu(sp, 0x198);
                        v1 = v1 & 0x3FFF;
                        ld(v0, v0, 0);
                        v1 = dsll32(v1, 8);
                        v1 = v1 | a0;
                        v0 = dsll32(v0, 22);
                        v0 = v0 | v1;
                        v1 = dsll32(v0, 0);
                        v0 = dsrl32(v0, 0);
                        v1 = dsra32(v1, 0);
                        v0 = dsll32(v0, 0);
                        sw(v1, s3, 24);
                        v0 = dsra32(v0, 0);
                        sw(v0, s3, 28);
                        v0 = addiu(sp, 0x1E0);
                        ld(a3, v0, 0);
                        v0 = addiu(sp, 0x1A0);
                        a3 = a3 & 0x3FFF;
                        ld(a2, v0, 0);
                        v0 = addiu(sp, 0x1E8);
                        a2 = dsll(a2, 14);
                        ld(a1, v0, 0);
                        a2 = a3 | a2;
                        v0 = addiu(sp, 0x1A8);
                        a1 = a1 & 0x3FFF;
                        ld(a0, v0, 0);
                        a1 = dsll(a1, 20);
                        a1 = a1 | a2;
                        v0 = addiu(sp, 0x1F0);
                        a0 = dsll32(a0, 2);
                        ld(v1, v0, 0);
                        a0 = a0 | a1;
                        v0 = addiu(sp, 0x1B0);
                        v1 = v1 & 0x3FFF;
                        ld(v0, v0, 0);
                        v1 = dsll32(v1, 8);
                        v1 = v1 | a0;
                        v0 = dsll32(v0, 22);
                        v0 = v0 | v1;
                        v1 = dsll32(v0, 0);
                        v0 = dsrl32(v0, 0);
                        v1 = dsra32(v1, 0);
                        v0 = dsll32(v0, 0);
                        sw(v1, s3, 32);
                        v0 = dsra32(v0, 0);
                        sw(v0, s3, 36);
                        mult(v0, s6, s2);
                        mult(s7, s0, v0);
                        sw(s7, s3, 44);
                        lw(v0, sp, 0x25C);
                        sw(v0, s3, 48);
                        lw(v0, s3, 44);
                        if (v0 == 0) {
                            // 0x004dbf08
                            charge(ctx, 2);
                            sw(zero, s3, 16);
                        } else {
                            // 0x004dbedc
                            charge(ctx, 7);
                            lw(v0, sp, 0x258);
                            sw(v0, s3, 16);
                            lw(v1, sp, 0x258);
                            lw(v0, sp, 0x25C);
                            v1 = sll(v1, 6);
                            if (v1 == v0) {
                                // 0x004dbef8
                                charge(ctx, 4);
                                lw(v0, s3, 48);
                                v0 = addiu(v0, 2048);
                                sw(v0, s3, 48);
                            }
                        }
                    }
                L_004dc040:
                    charge(ctx, 7);
                    lw(v0, s3, 40);
                    v0 = addiu(v0, 15);
                    v0 = v0 & s5;
                    sw(v0, s3, 40);
                    lw(v0, gp, -17108);  // 0x7CEA1C
                    if (v0 == 0) {
                        // 0x004dc05c
                        charge(ctx, 4);
                        lbu(v0, s4, 33);
                        v0 = v0 & 0x80;
                        if (v0 != 0) {
                            goto L_004dcd04;
                        }
                        // 0x004dc06c
                        charge(ctx, 9);
                        lw(v1, s4, 16);
                        lw(v0, s4, 12);
                        mult(v1, v1, v0);
                        lw(v0, s4, 20);
                        mult(v0, v0, v1);
                        v0 = sra(v0, 7);
                        at = slti(v0, 32767);
                        if (at == 0) {
                            goto L_004dcd04;
                        }
                        // 0x004dc090
                        charge(ctx, 9);
                        lbu(v1, s3, 54);
                        v0 = 19;
                        v1 = v1 | 0x1;
                        sb(v1, s3, 54);
                        lw(v1, s3, 8);
                        v1 = srl(v1, 20);
                        v1 = v1 & 0x3F;
                        s5 = 0;
                        if (v1 == v0) {
                            // 0x004dc8a8
                            charge(ctx, 8);
                            lbu(v0, s3, 54);
                            v0 = v0 | 0x2;
                            sb(v0, s3, 54);
                            lw(v0, s3, 12);
                            v0 = srl(v0, 19);
                            v0 = v0 & 0xF;
                            if (v0 != 0) {
                                backedge(ctx);
                            } else {
                                // 0x004dc8c8
                                charge(ctx, 8);
                                lbu(a1, s3, 22);
                                v0 = 2;
                                v1 = sra(a1, 2);
                                v1 = sll(v1, 3);
                                a0 = addu(v1, sp);
                                ld(v1, a0, 384);
                                if (v1 != v0) {
                                    backedge(ctx);
                                } else {
                                    // 0x004dc8e8
                                    charge(ctx, 56);
                                    ld(v1, a0, 448);
                                    v0 = si(-4);
                                    a2 = si(-31);
                                    a0 = a1 & v0;
                                    a0 = addu(a0, sp);
                                    lw(v0, s3, 16);
                                    lw(t2, a0, 352);
                                    pcpyld(a0, zero, a2);
                                    a1 = v1 & a0;
                                    t1 = t2 & 0x7FF;
                                    a0 = v1 & 0x2;
                                    a3 = dsll(a0, 2);
                                    a0 = v0 & a2;
                                    a2 = a3 | a1;
                                    a1 = v1 & 0x4;
                                    a1 = dsrl(a1, 1);
                                    t0 = a1 | a2;
                                    a1 = srl(t2, 16);
                                    a3 = a1 & 0x7FF;
                                    a1 = srl(t1, 4);
                                    a2 = dsll32(a1, 0);
                                    a1 = srl(a3, 4);
                                    a2 = dsrl32(a2, 0);
                                    a3 = v1 & 0x8;
                                    a1 = sll(a1, 3);
                                    a3 = dsll(a3, 1);
                                    v1 = v1 & 0x10;
                                    a3 = a3 | t0;
                                    v1 = dsrl(v1, 2);
                                    v1 = v1 | a3;
                                    a1 = dsll32(a1, 0);
                                    a2 = v1 - a2;
                                    a1 = dsrl32(a1, 0);
                                    v1 = v0 & 0x2;
                                    a2 = a2 - a1;
                                    v1 = sll(v1, 2);
                                    a2 = dsll32(a2, 0);
                                    a1 = v1 | a0;
                                    a2 = dsra32(a2, 0);
                                    a0 = v0 & 0x4;
                                    v1 = v0 & 0x8;
                                    a0 = srl(a0, 1);
                                    v0 = v0 & 0x10;
                                    v1 = sll(v1, 1);
                                    a0 = a0 | a1;
                                    v1 = v1 | a0;
                                    v0 = srl(v0, 2);
                                    v0 = v0 | v1;
                                    v0 = subu(v0, a2);
                                    v0 = sll(v0, 3);
                                    v1 = v0 & 0x3F;
                                    v0 = srl(v0, 6);
                                    v0 = sll(v0, 3);
                                    at = sltiu(v0, 2048);
                                    if (at == 0) {
                                        backedge(ctx);
                                    } else {
                                        // 0x004dc9c8
                                        charge(ctx, 6);
                                        v0 = sll(v0, 16);
                                        v0 = v0 | v1;
                                        v0 = dsll32(v0, 0);
                                        v0 = dsrl32(v0, 0);
                                        s5 = dsll32(v0, 0);
                                        backedge(ctx);
                                    }
                                }
                            }
                        }
                        // 0x004dc0b4
                        charge(ctx, 6);
                        lw(v1, s3, 8);
                        v0 = 20;
                        v1 = srl(v1, 20);
                        v1 = v1 & 0x3F;
                        if (v1 == v0) {
                            // 0x004dc9e0
                            charge(ctx, 9);
                            lbu(v0, s3, 54);
                            a1 = 2;
                            v0 = v0 | 0x4;
                            sb(v0, s3, 54);
                            lw(v0, s3, 12);
                            v0 = srl(v0, 19);
                            v0 = v0 & 0xF;
                            if (v0 != a1) {
                                backedge(ctx);
                            } else {
                                // 0x004dca04
                                charge(ctx, 7);
                                lbu(a0, s3, 22);
                                v0 = sra(a0, 2);
                                v0 = sll(v0, 3);
                                v1 = addu(v0, sp);
                                ld(v0, v1, 384);
                                if (v0 != a1) {
                                    // 0x004dcb30
                                    charge(ctx, 2);
                                    s5 = 0;
                                    backedge(ctx);
                                } else {
                                    // 0x004dca20
                                    charge(ctx, 60);
                                    v0 = si(-4);
                                    ld(v1, v1, 448);
                                    a0 = a0 & v0;
                                    a3 = si(-32);
                                    a0 = addu(a0, sp);
                                    lw(v0, s3, 16);
                                    lw(t2, a0, 352);
                                    pcpyld(a0, zero, a3);
                                    a2 = v1 & a0;
                                    t1 = t2 & 0x7FF;
                                    a0 = v1 & 0x1;
                                    a1 = dsll(a0, 2);
                                    a2 = a2 | a1;
                                    a0 = v0 & a3;
                                    a1 = v1 & 0x2;
                                    a1 = dsrl(a1, 1);
                                    t0 = a1 | a2;
                                    a1 = srl(t2, 16);
                                    a3 = a1 & 0x7FF;
                                    a1 = srl(t1, 5);
                                    a2 = dsll32(a1, 0);
                                    a1 = srl(a3, 4);
                                    a2 = dsrl32(a2, 0);
                                    a3 = v1 & 0x4;
                                    a1 = sll(a1, 2);
                                    a3 = dsll(a3, 1);
                                    a1 = dsll32(a1, 0);
                                    t1 = a3 | t0;
                                    a1 = dsrl32(a1, 0);
                                    a3 = v1 & 0x8;
                                    t0 = dsrl(a3, 2);
                                    a3 = v1 & 0x10;
                                    t0 = t0 | t1;
                                    v1 = v0 & 0x1;
                                    a3 = a3 | t0;
                                    v1 = sll(v1, 2);
                                    a2 = a3 - a2;
                                    a0 = a0 | v1;
                                    a1 = a2 - a1;
                                    v1 = v0 & 0x2;
                                    a2 = dsll32(a1, 0);
                                    v1 = srl(v1, 1);
                                    a2 = dsra32(a2, 0);
                                    a1 = v1 | a0;
                                    v1 = v0 & 0x4;
                                    a0 = sll(v1, 1);
                                    v1 = v0 & 0x8;
                                    a0 = a0 | a1;
                                    v1 = srl(v1, 2);
                                    v0 = v0 & 0x10;
                                    v1 = v1 | a0;
                                    v0 = v0 | v1;
                                    v0 = subu(v0, a2);
                                    v0 = sll(v0, 4);
                                    v1 = v0 & 0x3F;
                                    v0 = srl(v0, 6);
                                    v0 = sll(v0, 3);
                                    at = sltiu(v0, 2048);
                                    if (at == 0) {
                                        // 0x004dcb28
                                        charge(ctx, 2);
                                        s5 = 0;
                                        backedge(ctx);
                                    } else {
                                        // 0x004dcb10
                                        charge(ctx, 6);
                                        v0 = sll(v0, 16);
                                        v0 = v0 | v1;
                                        v0 = dsll32(v0, 0);
                                        v0 = dsrl32(v0, 0);
                                        s5 = dsll32(v0, 0);
                                        backedge(ctx);
                                    }
                                }
                            }
                        }
                        // 0x004dc0cc
                        charge(ctx, 21);
                        lbu(v0, s3, 22);
                        a2 = addiu(sp, 0x254);
                        a3 = addiu(sp, 0x250);
                        v0 = sra(v0, 2);
                        v1 = addiu(v0, 1);
                        v0 = sll(v1, 2);
                        v0 = addu(v0, v1);
                        v0 = sll(v0, 4);
                        sw(v0, s3, 40);
                        lw(v0, s3, 8);
                        lbu(a1, s3, 54);
                        v0 = srl(v0, 20);
                        a0 = v0 & 0x3F;
                        jal(ctx, 0x4DC0FCu, gen::fn_sub_4DB200_004db200);
                        lbu(a1, s3, 22);
                        lw(a0, s4, 12);
                        lw(v1, s4, 16);
                        a1 = sra(a1, 2);
                        at = slt(a1, 0);
                        v0 = 0;
                        if (at == 0) {
                            // 0x004dc120
                            charge(ctx, 1);
                            a3 = si(-16);
                            for (;;) {
                                // 0x004dc124
                                charge(ctx, 4);
                                lw(t0, sp, 0x254);
                                at = slt(a0, t0);
                                if (at == 0) {
                                    // 0x004dc13c
                                    charge(ctx, 1);
                                    a2 = a0;
                                } else {
                                    // 0x004dc134
                                    charge(ctx, 2);
                                    a2 = t0;
                                }
                                // 0x004dc140
                                charge(ctx, 19);
                                lw(a1, sp, 0x250);
                                at = slt(v1, a1);
                                if (at == 0) t0 = v1;
                                mult(a2, a2, t0);
                                lw(a1, s4, 20);
                                mult(a2, a1, a2);
                                v0 = addiu(v0, 1);
                                a0 = sra(a0, 1);
                                lw(a1, s3, 40);
                                a2 = sra(a2, 3);
                                a2 = addiu(a2, 15);
                                a2 = a2 & a3;
                                a1 = addu(a1, a2);
                                sw(a1, s3, 40);
                                lbu(a1, s3, 22);
                                a1 = sra(a1, 2);
                                at = slt(a1, v0);
                                v1 = sra(v1, 1);
                                if (at != 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                        }
                        // 0x004dc18c
                        charge(ctx, 3);
                        lw(v0, s3, 44);
                        if (v0 != 0) {
                            // 0x004dc198
                            charge(ctx, 3);
                            v0 = 2;
                            if (s2 == v0) {
                                // 0x004dc1a4
                                charge(ctx, 1);
                                s2 = 3;
                            }
                            // 0x004dc1a8
                            charge(ctx, 4);
                            mult(v0, s6, s2);
                            mult(s7, s0, v0);
                            v0 = addiu(s7, 80);
                            sw(v0, s3, 44);
                        }
                        // 0x004dc1b8
                        charge(ctx, 7);
                        lbu(v0, s3, 22);
                        s0 = 16;
                        s1 = 0;
                        v1 = sra(v0, 2);
                        at = slt(v1, 0);
                        a0 = 0;
                        if (at != 0) {
                            // 0x004dcb38
                            charge(ctx, 1);
                            lw(a2, s3, 44);
                        } else {
                            // 0x004dc1d4
                            charge(ctx, 1);
                            a1 = addiu(sp, 0x160);
                            for (;;) {
                                // 0x004dc1d8
                                charge(ctx, 3);
                                lw(v0, a1, 0);
                                if (v0 == 0) {
                                    // 0x004dc1e4
                                    charge(ctx, 3);
                                    s0 = addiu(s0, 64);
                                    s1 = addiu(s1, 1);
                                }
                                // 0x004dc1f0
                                charge(ctx, 4);
                                a0 = addiu(a0, 1);
                                at = slt(v1, a0);
                                a1 = addiu(a1, 4);
                                if (at != 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004dc200
                            charge(ctx, 2);
                            lw(a2, s3, 44);
                        }
                        // 0x004dcb3c
                        charge(ctx, 2);
                        if (a2 == 0) {
                            backedge(ctx);
                        } else {
                            // 0x004dcb44
                            charge(ctx, 2);
                            s0 = addiu(s0, 64);
                            backedge(ctx);
                            // 0x004dc20c
                            charge(ctx, 1);
                            s1 = addiu(s1, 1);
                        }
                        // 0x004dc210
                        charge(ctx, 2);
                        if (a2 != 0) {
                            // 0x004dc218
                            charge(ctx, 2);
                            if (s5 != 0) {
                                goto L_004dcb4c;
                            }
                            // 0x004dc220
                            charge(ctx, 17);
                            lw(a3, s3, 40);
                            v1 = addiu(a2, 63);
                            v0 = si(-64);
                            a2 = si(-128);
                            a0 = v1 & v0;
                            sw(v0, sp, 0x140);
                            v0 = 0x960000;
                            v1 = 0x30000;
                            lw(v0, v0, 376);  // 0x960178
                            a1 = v1 | 0x411;
                            fp = addiu(s0, 0x70);
                            v1 = addiu(a3, 127);
                            v1 = v1 & a2;
                            v1 = addu(fp, v1);
                            a0 = addu(a0, v1);
                            jalr(ctx, 0x4DC258u, v0.u());
                            sw(v0, s4, 4);
                            goto L_004dc264;
                        }
                    L_004dcb4c:
                        charge(ctx, 16);
                        v0 = si(-64);
                        lw(a0, s3, 40);
                        sw(v0, sp, 0x140);
                        fp = addiu(s0, 0x70);
                        v0 = 0x30000;
                        a1 = v0 | 0x411;
                        v0 = 0x960000;
                        lw(v1, v0, 376);  // 0x960178
                        v0 = addu(a0, a2);
                        a0 = addiu(v0, 63);
                        lw(v0, sp, 0x140);
                        v0 = a0 & v0;
                        a0 = addu(fp, v0);
                        jalr(ctx, 0x4DCB7Cu, v1.u());
                        sw(v0, s4, 4);
                        backedge(ctx);
                    L_004dc264:
                        charge(ctx, 3);
                        lw(v0, s4, 4);
                        if (v0 != 0) {
                            // 0x004dc270
                            charge(ctx, 13);
                            sw(s1, v0, 0);
                            a0 = si(-128);
                            lw(a1, s4, 4);
                            v0 = sll(s1, 6);
                            v1 = addiu(a1, 143);
                            v0 = addu(v1, v0);
                            v0 = v0 & a0;
                            sw(v0, a1, 4);
                            lw(v0, s4, 4);
                            sw(s1, v0, 8);
                            lw(v0, s3, 44);
                            if (v0 != 0) {
                                // 0x004dc2a4
                                charge(ctx, 2);
                                if (s5 == 0) {
                                    // 0x004dc2ac
                                    charge(ctx, 12);
                                    lw(v1, s4, 4);
                                    lw(v0, s3, 40);
                                    v1 = addu(v1, s0);
                                    v1 = addiu(v1, 112);
                                    v0 = addiu(v0, 127);
                                    v1 = v1 & a0;
                                    v0 = v0 & a0;
                                    v0 = addu(v0, v1);
                                    sw(v0, s4, 8);
                                    lw(v0, s4, 8);
                                    v0 = addiu(v0, 80);
                                    sw(v0, s4, 8);
                                }
                            }
                            // 0x004dc2dc
                            charge(ctx, 19);
                            v1 = 0x10000000;
                            lw(t0, s4, 4);
                            a1 = dsll32(v1, 0);
                            v0 = 1;
                            a3 = 14;
                            v0 = v0 | a1;
                            pcpyld(t2, a3, v0);
                            lw(a2, s4, 12);
                            lbu(v0, s3, 22);
                            a0 = 3;
                            a0 = a0 | a1;
                            pcpyld(t3, a3, a0);
                            lw(a1, s4, 16);
                            lw(t5, t0, 4);
                            t4 = addiu(t0, 16);
                            a3 = sra(v0, 2);
                            at = slt(a3, 0);
                            a0 = 0;
                            if (at == 0) {
                                // 0x004dc328
                                charge(ctx, 5);
                                at = slt(a3, 0);
                                v0 = 83;
                                t6 = 0;
                                t9 = 0;
                                if (at == 0) {
                                    // 0x004dc33c
                                    charge(ctx, 19);
                                    pcpyld(fp, v0, t6);
                                    v0 = lui(0xFFFE);
                                    t7 = v1 | 0x2;
                                    v0 = v0 | 0xFFFE;
                                    v1 = 0x50000000;
                                    sq(v0, sp, 0xE0);
                                    v1 = v1 | 0x2;
                                    v0 = 0x2000000;
                                    v1 = dsll32(v1, 0);
                                    v0 = dsll32(v0, 0);
                                    t1 = addiu(sp, 0x160);
                                    sq(v0, sp, 0xC0);
                                    pcpyld(v1, v1, t7);
                                    v0 = 0x8000000;
                                    t0 = addiu(sp, 0x1C0);
                                    v0 = dsll32(v0, 0);
                                    a3 = addiu(sp, 0x180);
                                    sq(v1, sp, 0x150);
                                    sq(v0, sp, 0xD0);
                                    for (;;) {
                                        // 0x004dc388
                                        charge(ctx, 11);
                                        lw(v1, sp, 0x254);
                                        at = slt(a2, v1);
                                        if (at == 0) v1 = a2;
                                        lw(v0, sp, 0x250);
                                        at = slt(a1, v0);
                                        if (at == 0) v0 = a1;
                                        sq(t3, t5, 0);
                                        lbu(s1, s3, 54);
                                        t6 = s1 & 0x2;
                                        if (t6 == 0) {
                                            // 0x004dc3b4
                                            charge(ctx, 1);
                                            t6 = s1 & 0x4;
                                            goto L_004dc3b8;
                                        }
                                        // 0x004dcbdc
                                        charge(ctx, 6);
                                        lw(t6, s3, 8);
                                        t6 = srl(t6, 20);
                                        t7 = t6 & 0x3F;
                                        t6 = 19;
                                        if (t7 == t6) {
                                            backedge(ctx);
                                        L_004dc3d8:
                                            charge(ctx, 7);
                                            lw(t7, t1, 0);
                                            lq(t6, sp, 0xE0);
                                            t6 = t7 & t6;
                                            t6 = dsll32(t6, 0);
                                            t6 = dsrl32(t6, 0);
                                            t7 = dsll(t6, 31);
                                        } else {
                                            // 0x004dcbf4
                                            charge(ctx, 2);
                                            t6 = s1 & 0x4;
                                            backedge(ctx);
                                        L_004dc3b8:
                                            charge(ctx, 2);
                                            if (t6 != 0) {
                                                // 0x004dc3c0
                                                charge(ctx, 6);
                                                lw(t6, s3, 8);
                                                t6 = srl(t6, 20);
                                                t7 = t6 & 0x3F;
                                                t6 = 20;
                                                if (t7 != t6) {
                                                    goto L_004dc3f4;
                                                }
                                                goto L_004dc3d8;
                                            }
                                        L_004dc3f4:
                                            charge(ctx, 2);
                                            lwu(t6, t1, 0);
                                            t7 = dsll32(t6, 0);
                                        }
                                        // 0x004dc3fc
                                        charge(ctx, 7);
                                        t6 = 81;
                                        pcpyld(t6, t6, t7);
                                        sq(t6, t5, 16);
                                        lbu(s1, s3, 54);
                                        t6 = s1 & 0x2;
                                        if (t6 == 0) {
                                            // 0x004dc418
                                            charge(ctx, 1);
                                            t6 = s1 & 0x4;
                                            goto L_004dc41c;
                                        }
                                        // 0x004dcbfc
                                        charge(ctx, 6);
                                        lw(t6, s3, 8);
                                        t6 = srl(t6, 20);
                                        t7 = t6 & 0x3F;
                                        t6 = 19;
                                        if (t7 == t6) {
                                            backedge(ctx);
                                        L_004dc43c:
                                            charge(ctx, 9);
                                            t7 = dsll32(v0, 0);
                                            t6 = sra(v1, 1);
                                            t7 = dsra32(t7, 0);
                                            t6 = dsll32(t6, 0);
                                            t7 = dsra(t7, 1);
                                            t6 = dsra32(t6, 0);
                                            t7 = dsll32(t7, 0);
                                            t7 = t6 | t7;
                                        } else {
                                            // 0x004dcc14
                                            charge(ctx, 2);
                                            t6 = s1 & 0x4;
                                            backedge(ctx);
                                        L_004dc41c:
                                            charge(ctx, 2);
                                            if (t6 != 0) {
                                                // 0x004dc424
                                                charge(ctx, 6);
                                                lw(t6, s3, 8);
                                                t6 = srl(t6, 20);
                                                t7 = t6 & 0x3F;
                                                t6 = 20;
                                                if (t7 != t6) {
                                                    goto L_004dc460;
                                                }
                                                goto L_004dc43c;
                                            }
                                        L_004dc460:
                                            charge(ctx, 6);
                                            t7 = dsll32(v0, 0);
                                            t6 = dsll32(v1, 0);
                                            t7 = dsra32(t7, 0);
                                            t6 = dsra32(t6, 0);
                                            t7 = dsll32(t7, 0);
                                            t7 = t6 | t7;
                                        }
                                        // 0x004dc478
                                        charge(ctx, 22);
                                        t6 = 82;
                                        pcpyld(t6, t6, t7);
                                        sq(t6, t5, 32);
                                        sq(fp, t5, 48);
                                        mult(v1, v1, v0);
                                        lw(v0, s4, 20);
                                        mult(v1, v0, v1);
                                        v1 = sra(v1, 3);
                                        v0 = addiu(t5, 80);
                                        v1 = addiu(v1, 15);
                                        v1 = sra(v1, 4);
                                        t6 = dsll32(v1, 0);
                                        lq(v1, sp, 0xD0);
                                        t6 = dsra32(t6, 0);
                                        t6 = t6 | v1;
                                        v1 = t6 & 0x7FFF;
                                        pcpyld(t6, t9, t6);
                                        sq(t6, t5, 64);
                                        v1 = dsll32(v1, 0);
                                        lw(t5, t1, 0);
                                        v1 = dsra32(v1, 0);
                                        if (t5 != 0) {
                                            // 0x004dc5d4
                                            charge(ctx, 17);
                                            lhu(t5, t4, -16);
                                            t6 = addiu(v1, 5);
                                            t7 = dsll32(t6, 0);
                                            t7 = dsra32(t7, 0);
                                            t6 = t5 + t7;
                                            t5 = 0x30000000;
                                            t5 = t6 | t5;
                                            t5 = dsll32(t5, 0);
                                            t5 = dsra32(t5, 0);
                                            sw(t5, t4, -16);
                                            lhu(t5, t4, -4);
                                            t6 = t5 + t7;
                                            t5 = 0x50000000;
                                            t5 = t6 | t5;
                                            t5 = dsll32(t5, 0);
                                            t5 = dsra32(t5, 0);
                                            sw(t5, t4, -4);
                                        } else {
                                            // 0x004dc4d0
                                            charge(ctx, 7);
                                            lq(t5, sp, 0x150);
                                            sq(t5, t4, 0);
                                            sq(t2, t4, 16);
                                            lbu(t7, s3, 54);
                                            t5 = t7 & 0x2;
                                            if (t5 != 0) {
                                                // 0x004dcc1c
                                                charge(ctx, 6);
                                                lw(t5, s3, 8);
                                                t5 = srl(t5, 20);
                                                t6 = t5 & 0x3F;
                                                t5 = 19;
                                                if (t6 != t5) {
                                                    backedge(ctx);
                                                    goto L_004dc4ec;
                                                }
                                                // 0x004dcc34
                                                charge(ctx, 9);
                                                ld(t6, a3, 0);
                                                ld(t5, t0, 0);
                                                t7 = t6 & 0x3E;
                                                t5 = dsll32(t5, 0);
                                                t6 = dsll(t7, 15);
                                                t5 = t6 | t5;
                                                t6 = dsll32(t7, 15);
                                                t6 = t6 | t5;
                                                backedge(ctx);
                                                goto L_004dc584;
                                            }
                                        L_004dc4ec:
                                            charge(ctx, 3);
                                            t5 = t7 & 0x4;
                                            if (t5 != 0) {
                                                // 0x004dc4f8
                                                charge(ctx, 6);
                                                lw(t5, s3, 8);
                                                t5 = srl(t5, 20);
                                                t6 = t5 & 0x3F;
                                                t5 = 20;
                                                if (t6 != t5) {
                                                    goto L_004dc544;
                                                }
                                                // 0x004dc510
                                                charge(ctx, 13);
                                                ld(t6, a3, 0);
                                                ld(t5, t0, 0);
                                                s1 = t6 & 0x3E;
                                                t6 = dsll32(t5, 0);
                                                t7 = dsll(s1, 15);
                                                t5 = 0x2000000;
                                                t5 = t7 | t5;
                                                t7 = dsll32(s1, 15);
                                                t5 = t5 | t6;
                                                t6 = t7 | t5;
                                                lq(t5, sp, 0xC0);
                                                t6 = t6 | t5;
                                                goto L_004dc584;
                                            }
                                        L_004dc544:
                                            charge(ctx, 16);
                                            lw(t5, s3, 8);
                                            ld(s1, a3, 0);
                                            ld(t6, t0, 0);
                                            t5 = srl(t5, 20);
                                            t7 = dsll(s1, 16);
                                            t8 = dsll32(s1, 16);
                                            t5 = t5 & 0x3F;
                                            t6 = dsll32(t6, 0);
                                            s1 = sll(t5, 24);
                                            s1 = dsll32(s1, 0);
                                            t5 = dsll32(t5, 24);
                                            s1 = dsrl32(s1, 0);
                                            t7 = s1 | t7;
                                            t6 = t7 | t6;
                                            t6 = t8 | t6;
                                            t6 = t5 | t6;
                                        L_004dc584:
                                            charge(ctx, 20);
                                            t5 = 80;
                                            pcpyld(t5, t5, t6);
                                            sq(t5, t4, 32);
                                            t6 = 0x30000000;
                                            t5 = addiu(v1, 5);
                                            s1 = dsll32(t5, 0);
                                            t5 = addiu(v0, -80);
                                            s1 = dsra32(s1, 0);
                                            t5 = dsll32(t5, 0);
                                            t6 = s1 | t6;
                                            t5 = dsra32(t5, 0);
                                            t7 = dsll32(t5, 0);
                                            t5 = 0x50000000;
                                            t6 = t6 | t7;
                                            t5 = s1 | t5;
                                            t5 = dsll32(t5, 0);
                                            pcpyld(t5, t5, t6);
                                            sq(t5, t4, 48);
                                            t4 = addiu(t4, 64);
                                        }
                                        // 0x004dc618
                                        charge(ctx, 12);
                                        v1 = sll(v1, 4);
                                        a0 = addiu(a0, 1);
                                        t5 = addu(v0, v1);
                                        a2 = sra(a2, 1);
                                        lbu(v0, s3, 22);
                                        a1 = sra(a1, 1);
                                        t1 = addiu(t1, 4);
                                        t0 = addiu(t0, 8);
                                        v0 = sra(v0, 2);
                                        at = slt(v0, a0);
                                        a3 = addiu(a3, 8);
                                        if (at != 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                    }
                                }
                            }
                            // 0x004dc648
                            charge(ctx, 3);
                            lw(v0, s3, 44);
                            if (v0 != 0) {
                                // 0x004dc654
                                charge(ctx, 2);
                                if (s5 != 0) {
                                    // 0x004dcc58
                                    charge(ctx, 3);
                                    v0 = addiu(t5, 80);
                                    sw(v0, s4, 8);
                                    backedge(ctx);
                                }
                                // 0x004dc65c
                                charge(ctx, 41);
                                v0 = dsll32(s2, 0);
                                a0 = dsll32(s6, 0);
                                v0 = dsra32(v0, 0);
                                lw(a2, s4, 8);
                                v1 = dsll32(v0, 0);
                                a0 = dsra32(a0, 0);
                                v0 = addiu(s7, 15);
                                a1 = 81;
                                a0 = a0 | v1;
                                v0 = sra(v0, 4);
                                v1 = dsll32(v0, 0);
                                v0 = 82;
                                v1 = dsra32(v1, 0);
                                pcpyld(a3, v0, a0);
                                sq(t3, a2, -80);
                                pcpyld(t0, a1, s5);
                                v0 = 83;
                                a0 = 0;
                                pcpyld(a1, v0, a0);
                                sq(t0, a2, -64);
                                v0 = 0x8000000;
                                sq(a3, a2, -48);
                                v0 = dsll32(v0, 0);
                                sq(a1, a2, -32);
                                v1 = v1 | v0;
                                a1 = 0;
                                v0 = v1 & 0x7FFF;
                                a0 = addiu(a2, -80);
                                pcpyld(v1, a1, v1);
                                sq(v1, a2, -16);
                                a1 = 0x10000000;
                                v1 = dsll32(v0, 0);
                                a1 = a1 | 0x2;
                                v0 = 0x50000000;
                                v1 = dsra32(v1, 0);
                                a2 = v0 | 0x2;
                                a2 = dsll32(a2, 0);
                                pcpyld(a1, a2, a1);
                                sq(a1, t4, 0);
                                sq(t2, t4, 16);
                                if (s5 != 0) {
                                    // 0x004dcc64
                                    charge(ctx, 4);
                                    lbu(a1, s4, 33);
                                    a1 = a1 & 0x40;
                                    if (a1 != 0) {
                                        backedge(ctx);
                                        goto L_004dc700;
                                    }
                                    // 0x004dcc74
                                    charge(ctx, 24);
                                    lq(a2, t4, -32);
                                    a1 = addiu(v1, 5);
                                    a3 = dsll32(a1, 0);
                                    a3 = dsra32(a3, 0);
                                    a1 = 0x30000000;
                                    sq(a2, t4, 32);
                                    lw(t0, s4, 4);
                                    t4 = addiu(t4, 48);
                                    lw(a2, t0, 0);
                                    a2 = addiu(a2, -1);
                                    sw(a2, t0, 0);
                                    lhu(a2, t4, -64);
                                    a2 = a2 + a3;
                                    a1 = a2 | a1;
                                    a1 = dsll32(a1, 0);
                                    a1 = dsra32(a1, 0);
                                    sw(a1, t4, -64);
                                    lhu(a1, t4, -52);
                                    a1 = a1 + a3;
                                    v0 = a1 | v0;
                                    v0 = dsll32(v0, 0);
                                    v0 = dsra32(v0, 0);
                                    sw(v0, t4, -52);
                                    backedge(ctx);
                                    goto L_004dc754;
                                }
                            L_004dc700:
                                charge(ctx, 2);
                                if (s5 == 0) {
                                    // 0x004dc710
                                    charge(ctx, 15);
                                    lw(a3, s3, 12);
                                    t0 = 0x10000;
                                    lwu(a1, s3, 16);
                                    a2 = dsll32(t0, 0);
                                    v0 = 80;
                                    a3 = srl(a3, 19);
                                    t2 = a3 & 0xF;
                                    t1 = dsll(t2, 24);
                                    a3 = dsll32(a1, 0);
                                    t0 = t1 | t0;
                                    a1 = dsll32(t2, 24);
                                    a3 = t0 | a3;
                                    a2 = a3 | a2;
                                    a1 = a1 | a2;
                                    pcpyld(v0, v0, a1);
                                } else {
                                    // 0x004dc708
                                    charge(ctx, 2);
                                    lq(v0, t4, -32);
                                }
                                // 0x004dc74c
                                charge(ctx, 2);
                                sq(v0, t4, 32);
                                t4 = addiu(t4, 48);
                            L_004dc754:
                                charge(ctx, 4);
                                lbu(v0, s4, 33);
                                v0 = v0 & 0x40;
                                if (v0 == 0) {
                                    // 0x004dc7a0
                                    charge(ctx, 14);
                                    v0 = dsll32(a0, 0);
                                    v1 = addiu(v1, 5);
                                    a1 = dsll32(v1, 0);
                                    v0 = dsra32(v0, 0);
                                    v1 = dsll32(v0, 0);
                                    a1 = dsra32(a1, 0);
                                    a0 = 0x30000000;
                                    v0 = 0x50000000;
                                    a0 = a1 | a0;
                                    v0 = a1 | v0;
                                    v1 = a0 | v1;
                                    v0 = dsll32(v0, 0);
                                    pcpyld(v0, v0, v1);
                                    sq(v0, t4, 0);
                                } else {
                                    // 0x004dc764
                                    charge(ctx, 15);
                                    v0 = dsll32(a0, 0);
                                    v1 = addiu(v1, 5);
                                    a1 = dsll32(v1, 0);
                                    v0 = dsra32(v0, 0);
                                    v1 = dsll32(v0, 0);
                                    a1 = dsra32(a1, 0);
                                    a0 = 0x10000000;
                                    v0 = 0x50000000;
                                    a0 = a1 | a0;
                                    v0 = a1 | v0;
                                    v1 = a0 | v1;
                                    v0 = dsll32(v0, 0);
                                    pcpyld(v0, v0, v1);
                                    sq(v0, t4, 0);
                                }
                            }
                            // 0x004dc7d8
                            charge(ctx, 3);
                            lw(v1, s4, 8);
                            if (v1 == 0) {
                                // 0x004dccd4
                                charge(ctx, 12);
                                lw(a0, s4, 4);
                                a1 = si(-128);
                                lw(v1, s3, 40);
                                v0 = addu(a0, s0);
                                v1 = addiu(v1, 127);
                                v0 = addiu(v0, 112);
                                v1 = v1 & a1;
                                v0 = v0 & a1;
                                a1 = addu(v1, v0);
                                jal(ctx, 0x4DCCF4u, gen::fn_SyncDCache_00503a58);
                                lw(v0, s4, 4);
                                backedge(ctx);
                            } else {
                                // 0x004dc7e4
                                charge(ctx, 6);
                                lw(v0, s3, 44);
                                lw(a0, s4, 4);
                                v0 = addu(v1, v0);
                                v0 = addiu(v0, -80);
                                a1 = addiu(v0, 127);
                                jal(ctx, 0x4DC7F4u, gen::fn_SyncDCache_00503a58);
                            L_004dc7fc:
                                charge(ctx, 1);
                                lw(v0, s4, 4);
                            }
                            // 0x004dc800
                            charge(ctx, 7);
                            sw(v0, s4, 36);
                            lw(v0, s4, 24);
                            sw(v0, s4, 48);
                            lbu(v0, s3, 54);
                            v0 = v0 & 0x1;
                            if (v0 == 0) {
                                backedge(ctx);
                            } else {
                                // 0x004dc81c
                                charge(ctx, 4);
                                lbu(v0, s4, 33);
                                v0 = v0 & 0x80;
                                if (v0 != 0) {
                                    backedge(ctx);
                                } else {
                                    // 0x004dc82c
                                    charge(ctx, 5);
                                    lw(v0, s4, 4);
                                    lw(v0, v0, 4);
                                    v0 = addiu(v0, 80);
                                    sw(v0, s4, 4);
                                    backedge(ctx);
                                }
                            }
                            goto L_004db6a4;
                        }
                        // 0x004dcb8c
                        charge(ctx, 20);
                        v0 = 1;
                        v1 = si(-128);
                        sw(v0, sp, 0x218);
                        v0 = lui(0x8000);
                        lw(a1, s3, 40);
                        a0 = v0 | 0x13;
                        lw(v0, s3, 44);
                        a2 = addiu(v0, 63);
                        lw(v0, sp, 0x140);
                        a2 = a2 & v0;
                        v0 = addiu(a1, 127);
                        v0 = v0 & v1;
                        v0 = addu(fp, v0);
                        a1 = addu(a2, v0);
                        jal(ctx, 0x4DCBC0u, gen::fn_sub_4C1D10_004c1d10);
                        sw(v0, sp, 0x21C);
                        a0 = addiu(sp, 0x218);
                        jal(ctx, 0x4DCBCCu, gen::fn_sub_4C1C50_004c1c50);
                        v0 = 0;
                        goto L_004dce70;
                    }
                L_004dcd04:
                    charge(ctx, 7);
                    lbu(v0, s4, 33);
                    v0 = v0 & 0xBF;
                    sb(v0, s4, 33);
                    lbu(v0, s4, 33);
                    v0 = v0 & 0x80;
                    if (v0 != 0) {
                        // 0x004dcd20
                        charge(ctx, 4);
                        sw(zero, s4, 4);
                        sw(zero, s4, 8);
                        sw(zero, s4, 24);
                        backedge(ctx);
                        goto L_004dc7fc;
                    }
                    // 0x004dcd30
                    charge(ctx, 12);
                    v0 = 0x30000;
                    lw(a0, s3, 40);
                    a1 = v0 | 0x411;
                    lw(v1, s3, 44);
                    v0 = 0x960000;
                    lw(v0, v0, 376);  // 0x960178
                    a0 = addu(a0, v1);
                    jalr(ctx, 0x4DCD48u, v0.u());
                    sw(v0, s4, 4);
                    lw(v1, s4, 4);
                    if (v1 != 0) {
                        // 0x004dcd60
                        charge(ctx, 3);
                        lw(v0, s3, 44);
                        if (v0 != 0) {
                            // 0x004dcdc0
                            charge(ctx, 4);
                            lw(v0, s3, 40);
                            v0 = addu(v1, v0);
                            sw(v0, s4, 8);
                            backedge(ctx);
                        }
                        // 0x004dcd6c
                        charge(ctx, 4);
                        lw(v1, s4, 20);
                        v0 = 8;
                        if (v1 == v0) {
                            // 0x004dcdd0
                            charge(ctx, 4);
                            lbu(v0, s3, 54);
                            v0 = v0 | 0x2;
                            sb(v0, s3, 54);
                            backedge(ctx);
                        }
                        // 0x004dcd7c
                        charge(ctx, 4);
                        a0 = s4;
                        jal(ctx, 0x4DCD7Cu, gen::fn_sub_4EF1D0_004ef1d0);
                        backedge(ctx);
                        goto L_004dc7fc;
                    }
                    // 0x004dcd8c
                    charge(ctx, 13);
                    v1 = 1;
                    v0 = lui(0x8000);
                    sw(v1, sp, 0x210);
                    a0 = v0 | 0x13;
                    lw(v1, s3, 40);
                    lw(v0, s3, 44);
                    a1 = addu(v1, v0);
                    jal(ctx, 0x4DCDA4u, gen::fn_sub_4C1D10_004c1d10);
                    sw(v0, sp, 0x214);
                    a0 = addiu(sp, 0x210);
                    jal(ctx, 0x4DCDB0u, gen::fn_sub_4C1C50_004c1c50);
                    v0 = 0;
                } else {
                    // 0x004db964
                    charge(ctx, 2);
                    if (a3 == v0) {
                        // 0x004db974
                        charge(ctx, 8);
                        lw(a3, s3, 12);
                        v0 = 0x500000;
                        a2 = 64;
                        s0 = 2;
                        v1 = a2;
                        v0 = a3 | v0;
                        sw(v0, s3, 12);
                        goto L_004db9e8;
                    }
                    // 0x004db96c
                    charge(ctx, 2);
                    sw(v0, sp, 0x228);
                    // 0x004db9a4
                    charge(ctx, 8);
                    v0 = lui(0x8000);
                    a0 = v0 | 0xD;
                    jal(ctx, 0x4DB9A8u, gen::fn_sub_4C1D10_004c1d10);
                    sw(v0, sp, 0x22C);
                    a0 = addiu(sp, 0x228);
                    jal(ctx, 0x4DB9B4u, gen::fn_sub_4C1C50_004c1c50);
                    v0 = 0;
                }
            } else {
                // 0x004db7c4
                charge(ctx, 3);
                a2 = 64;
                if (a3 == a2) {
                    // 0x004db884
                    charge(ctx, 17);
                    lw(t2, s3, 8);
                    t1 = 0x1400000;
                    t0 = 0x20000000;
                    a3 = 5;
                    s6 = 8;
                    t1 = t2 | t1;
                    sw(t1, s3, 8);
                    lw(t1, s3, 12);
                    t1 = t1 | 0x4;
                    sw(t1, s3, 12);
                    lw(t1, s3, 12);
                    t0 = t1 | t0;
                    sw(t0, s3, 12);
                    lbu(t0, s4, 35);
                    t0 = t0 & 0xF;
                    s2 = 2;
                    if (t0 == a3) {
                        // 0x004db8f4
                        charge(ctx, 2);
                        s0 = 4;
                        goto L_004db9e8;
                    }
                    // 0x004db8c8
                    charge(ctx, 2);
                    if (t0 == v0) {
                        // 0x004db8d8
                        charge(ctx, 7);
                        lw(a3, s3, 12);
                        v0 = 0x500000;
                        s0 = s2;
                        v1 = a2;
                        v0 = a3 | v0;
                        sw(v0, s3, 12);
                        goto L_004db9e8;
                    }
                    // 0x004db8d0
                    charge(ctx, 2);
                    sw(v0, sp, 0x230);
                    // 0x004db900
                    charge(ctx, 8);
                    v0 = lui(0x8000);
                    a0 = v0 | 0xD;
                    jal(ctx, 0x4DB904u, gen::fn_sub_4C1D10_004c1d10);
                    sw(v0, sp, 0x234);
                    a0 = addiu(sp, 0x230);
                    jal(ctx, 0x4DB910u, gen::fn_sub_4C1C50_004c1c50);
                    v0 = 0;
                } else {
                    // 0x004db7d0
                    charge(ctx, 2);
                    if (a3 == 0) {
                        // 0x004db7e0
                        charge(ctx, 8);
                        t0 = t0 & 0xF;
                        a3 = 5;
                        s2 = 0;
                        s6 = 0;
                        s0 = 0;
                        v1 = 0;
                        a2 = 0;
                        if (t0 == a3) {
                            // 0x004db850
                            charge(ctx, 4);
                            lw(v0, s3, 12);
                            v0 = v0 | 0x4;
                            sw(v0, s3, 12);
                            goto L_004db9e8;
                        }
                        // 0x004db800
                        charge(ctx, 3);
                        a3 = 6;
                        if (t0 == a3) {
                            // 0x004db83c
                            charge(ctx, 5);
                            lw(a3, s3, 8);
                            v0 = 0x100000;
                            v0 = a3 | v0;
                            sw(v0, s3, 8);
                            goto L_004db9e8;
                        }
                        // 0x004db80c
                        charge(ctx, 2);
                        if (t0 == v0) {
                            // 0x004db81c
                            charge(ctx, 8);
                            lw(a3, s3, 8);
                            v0 = 0xA00000;
                            v0 = a3 | v0;
                            sw(v0, s3, 8);
                            lw(v0, s3, 12);
                            v0 = v0 | 0x4;
                            sw(v0, s3, 12);
                            goto L_004db9e8;
                        }
                        // 0x004db814
                        charge(ctx, 2);
                        sw(v0, sp, 0x238);
                        // 0x004db864
                        charge(ctx, 8);
                        v0 = lui(0x8000);
                        a0 = v0 | 0xD;
                        jal(ctx, 0x4DB868u, gen::fn_sub_4C1D10_004c1d10);
                        sw(v0, sp, 0x23C);
                        a0 = addiu(sp, 0x238);
                        jal(ctx, 0x4DB874u, gen::fn_sub_4C1C50_004c1c50);
                        v0 = 0;
                    } else {
                        // 0x004db7d8
                        charge(ctx, 2);
                        sw(v0, sp, 0x220);
                        // 0x004db9c8
                        charge(ctx, 8);
                        v0 = lui(0x8000);
                        a0 = v0 | 0xD;
                        jal(ctx, 0x4DB9CCu, gen::fn_sub_4C1D10_004c1d10);
                        sw(v0, sp, 0x224);
                        a0 = addiu(sp, 0x220);
                        jal(ctx, 0x4DB9D8u, gen::fn_sub_4C1C50_004c1c50);
                        v0 = 0;
                    }
                }
            }
            goto L_004dce70;
        }
    L_004dce58:
        charge(ctx, 6);
        v0 = 128;
        sb(v0, s4, 33);
        sw(zero, s4, 24);
        lw(v0, s4, 24);
        sw(v0, s4, 48);
        backedge(ctx);
        goto L_004db6a4;
    }
    // 0x004db6c4
    charge(ctx, 2);
    v0 = 0;
L_004dce70:
    charge(ctx, 1);
    ld(ra, sp, 0x90);
    // 0x004dce74 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    lq(fp, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x260);
}

// 0x004DD2E0 sub_4DD2E0 -- 408 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// RW PS2 driver: pipeline flush (sub_4F1780 / sub_4F1540, _rwDMAForceBufferSwap).
void sub_4DD2E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004dd2e0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    lw(v0, gp, -16968);  // 0x7CEAA8
    v0 = addu(s1, v0);
    lbu(v0, v0, 23);
    if (v0 != 0) {
        // 0x004dd30c
        charge(ctx, 3);
        a0 = s1;
        a1 = 0;
        jal(ctx, 0x4DD310u, gen::fn_sub_4F1780_004f1780);
    }
    // 0x004dd318
    charge(ctx, 6);
    a0 = s1;
    jal(ctx, 0x4DD318u, gen::fn_sub_4F1540_004f1540);
    lbu(v0, s1, 33);
    v0 = v0 & 0x80;
    if (v0 == 0) {
        // 0x004dd330
        charge(ctx, 5);
        lw(v0, gp, -16968);  // 0x7CEAA8
        s0 = addu(s1, v0);
        lw(v0, s0, 0);
        if (i64(v0) > 0) {
            for (;;) {
                // 0x004dd420
                charge(ctx, 9);
                jal(ctx, 0x4DD420u, gen::fn__rwDMAForceBufferSwap_004d4df0);
                jal(ctx, 0x4DD428u, gen::fn__rwDMAForceBufferSwap_004d4df0);
                lw(v0, s0, 0);
                if (i64(v0) <= 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004dd444
            charge(ctx, 2);
            sw(zero, s0, 0);
            backedge(ctx);
        } else {
            // 0x004dd344
            charge(ctx, 1);
            sw(zero, s0, 0);
        }
        // 0x004dd348
        charge(ctx, 3);
        lw(v0, s0, 0);
        if (v0 == 0) {
            // 0x004dd354
            charge(ctx, 3);
            lw(a0, s1, 36);
            if (a0 != 0) {
                // 0x004dd360
                charge(ctx, 4);
                v0 = 0x960000;
                lw(v0, v0, 380);  // 0x96017C
                jalr(ctx, 0x4DD368u, v0.u());
            }
        }
        // 0x004dd370
        charge(ctx, 3);
        lw(v0, s0, 0);
        if (v0 != 0) {
            // 0x004dd3e0
            charge(ctx, 3);
            lw(v0, s0, 56);
            if (v0 != 0) {
                // 0x004dd44c
                charge(ctx, 2);
                sw(zero, s0, 56);
                backedge(ctx);
            }
            // 0x004dd3ec
            charge(ctx, 1);
            v1 = 0;
            for (;;) {
                // 0x004dd3f0
                charge(ctx, 3);
                lw(v0, s0, 60);
                if (v0 != 0) {
                    // 0x004dd454
                    charge(ctx, 2);
                    sw(zero, s0, 60);
                    backedge(ctx);
                } else {
                    // 0x004dd3fc
                    charge(ctx, 1);
                }
                // 0x004dd400
                charge(ctx, 5);
                v1 = addiu(v1, 1);
                v0 = slti(v1, 7);
                s0 = addiu(s0, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004dd414
            charge(ctx, 1);
        } else {
            // 0x004dd37c
            charge(ctx, 3);
            lw(a0, s0, 56);
            if (a0 != 0) {
                // 0x004dd388
                charge(ctx, 5);
                v0 = 0x960000;
                lw(v0, v0, 380);  // 0x96017C
                jalr(ctx, 0x4DD390u, v0.u());
                sw(zero, s0, 56);
            }
            // 0x004dd39c
            charge(ctx, 3);
            s1 = 0x960000;
            s2 = 0;
            s1 = addiu(s1, 380);  // &0x96017C
            for (;;) {
                // 0x004dd3a8
                charge(ctx, 3);
                lw(a0, s0, 60);
                if (a0 != 0) {
                    // 0x004dd3b4
                    charge(ctx, 5);
                    lw(v0, s1, 0);
                    jalr(ctx, 0x4DD3B8u, v0.u());
                    sw(zero, s0, 60);
                }
                // 0x004dd3c8
                charge(ctx, 4);
                s2 = addiu(s2, 1);
                v0 = slti(s2, 7);
                s0 = addiu(s0, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004dd3d8
            charge(ctx, 2);
        }
    }
    // 0x004dd418
    charge(ctx, 2);
    v0 = 1;
    // 0x004dd460
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x004EBFB0 sub_4EBFB0 -- 336 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// RW PS2 driver: sub_4CDF30 .. sub_4CE200 sequence.
void sub_4EBFB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ebfb0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a1;
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    s1 = 0;
    lbu(v0, a0, 34);
    v0 = v0 & 0x4;
    s0 = 0;
    if (v0 != 0) {
        // 0x004ebfe4
        charge(ctx, 1);
        s1 = 1;
    }
    // 0x004ebfe8
    charge(ctx, 2);
    if (s1 == 0) {
        // 0x004ec0b4
        charge(ctx, 6);
        a0 = s2;
        a1 = 0;
        a2 = 1;
        jal(ctx, 0x4EC0BCu, gen::fn_sub_4CE200_004ce200);
        if (v0 != 0) {
            backedge(ctx);
            goto L_004ebff0;
        }
        // 0x004ec0cc
        charge(ctx, 2);
        v0 = 0;
        // 0x004ec0e4 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(ra, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        return;
    }
L_004ebff0:
    charge(ctx, 4);
    lbu(v0, s2, 35);
    v0 = v0 & 0x60;
    if (v0 != 0) {
        // 0x004ec000
        charge(ctx, 4);
        lbu(v0, s2, 34);
        v0 = v0 & 0x10;
        if (v0 != 0) {
            // 0x004ec010
            charge(ctx, 1);
            s0 = 1;
        }
        // 0x004ec014
        charge(ctx, 2);
        if (s0 != 0) {
            goto L_004ec038;
        }
        // 0x004ec01c
        charge(ctx, 5);
        a0 = s2;
        a1 = 1;
        jal(ctx, 0x4EC020u, gen::fn_sub_4CDF30_004cdf30);
        if (v0 != 0) {
            goto L_004ec038;
        }
        // 0x004ec030
        charge(ctx, 2);
        v0 = 0;
        // 0x004ec0e4 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(ra, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        return;
    }
L_004ec038:
    charge(ctx, 6);
    lbu(v1, s2, 35);
    v0 = 32;
    v1 = v1 & 0x60;
    v1 = v1 & 0xFF;
    if (v1 != v0) {
        // 0x004ec050
        charge(ctx, 3);
        v0 = 64;
        if (v1 == v0) {
            goto L_004ec064;
        }
        // 0x004ec05c
        charge(ctx, 2);
        a1 = s3;
        // 0x004ec078
        charge(ctx, 3);
        a0 = s2;
        jal(ctx, 0x4EC078u, gen::fn_sub_4EBB40_004ebb40);
        s3 = v0;
        goto L_004ec084;
    }
L_004ec064:
    charge(ctx, 5);
    a1 = s3;
    a0 = s2;
    jal(ctx, 0x4EC068u, gen::fn_sub_4EB8C0_004eb8c0);
    s3 = v0;
L_004ec084:
    charge(ctx, 4);
    lbu(v0, s2, 35);
    v0 = v0 & 0x60;
    if (v0 != 0) {
        // 0x004ec094
        charge(ctx, 2);
        if (s0 == 0) {
            // 0x004ec09c
            charge(ctx, 2);
            a0 = s2;
            jal(ctx, 0x4EC09Cu, gen::fn_sub_4CDE40_004cde40);
        }
    }
    // 0x004ec0a4
    charge(ctx, 2);
    if (s1 == 0) {
        // 0x004ec0d4
        charge(ctx, 4);
        a0 = s2;
        jal(ctx, 0x4EC0D4u, gen::fn_sub_4CDE00_004cde00);
        backedge(ctx);
    }
    // 0x004ec0ac
    charge(ctx, 2);
    v0 = s3;
    // 0x004ec0e4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x004FAFE0 _dualPrimeVector -- 388 bytes; leaf frame (no stack)
// libmpeg: the dual-prime motion vector derivation (leaf).
void _dualPrimeVector(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x004fafe0
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, 388);
    v0 = 3;
    if (v1 != v0) {
        // 0x004fb100
        charge(ctx, 2);
        lw(v1, a2, 0);
        if (i64(a3) <= 0) {
            // 0x004fb114
            charge(ctx, 1);
            v0 = sra(a3, 1);
        } else {
            // 0x004fb108
            charge(ctx, 3);
            v0 = addiu(a3, 1);
            v0 = sra(v0, 1);
        }
        // 0x004fb118
        charge(ctx, 4);
        v0 = addu(v0, v1);
        sw(v0, a1, 0);
        lw(a2, a2, 4);
        if (i64(t0) <= 0) {
            // 0x004fb134
            charge(ctx, 1);
            v0 = sra(t0, 1);
        } else {
            // 0x004fb128
            charge(ctx, 3);
            v0 = addiu(t0, 1);
            v0 = sra(v0, 1);
        }
        // 0x004fb138
        charge(ctx, 6);
        a2 = addu(v0, a2);
        sw(a2, a1, 4);
        v1 = 1;
        lw(v0, a0, 388);
        cc = v0 != v1;  // the condition, before the delay slot changes it
        v0 = addiu(a2, 1);
        if (cc) {
            // 0x004fb15c
            charge(ctx, 2);
            sw(v0, a1, 4);
            return;
        }
        // 0x004fb150
        charge(ctx, 3);
        v0 = addiu(a2, -1);
        sw(v0, a1, 4);
        return;
    }
    // 0x004faff0
    charge(ctx, 3);
    lw(v0, a0, 392);
    if (v0 != 0) {
        // 0x004faffc
        charge(ctx, 2);
        lw(v1, a2, 0);
        if (i64(a3) <= 0) {
            // 0x004fb010
            charge(ctx, 1);
            v0 = sra(a3, 1);
        } else {
            // 0x004fb004
            charge(ctx, 3);
            v0 = addiu(a3, 1);
            v0 = sra(v0, 1);
        }
        // 0x004fb014
        charge(ctx, 4);
        v0 = addu(v0, v1);
        sw(v0, a1, 0);
        lw(v1, a2, 4);
        if (i64(t0) <= 0) {
            // 0x004fb030
            charge(ctx, 1);
            v0 = sra(t0, 1);
        } else {
            // 0x004fb024
            charge(ctx, 3);
            v0 = addiu(t0, 1);
            v0 = sra(v0, 1);
        }
        // 0x004fb034
        charge(ctx, 7);
        v0 = addu(v0, v1);
        v0 = addiu(v0, -1);
        sw(v0, a1, 4);
        v0 = sll(a3, 1);
        v0 = addu(v0, a3);
        lw(v1, a2, 0);
        if (i64(a3) > 0) {
            // 0x004fb050
            charge(ctx, 1);
            v0 = addiu(v0, 1);
        }
        // 0x004fb054
        charge(ctx, 7);
        v0 = sra(v0, 1);
        v0 = addu(v0, v1);
        sw(v0, a1, 8);
        v0 = sll(t0, 1);
        v0 = addu(v0, t0);
        lw(a2, a2, 4);
        if (i64(t0) > 0) {
            // 0x004fb070
            charge(ctx, 1);
            v0 = addiu(v0, 1);
        }
        goto L_004fb074;
    }
    v0 = sll(a3, 1);
    // 0x004fb088
    charge(ctx, 3);
    lw(v1, a2, 0);
    v0 = addu(v0, a3);
    if (i64(a3) > 0) {
        // 0x004fb094
        charge(ctx, 1);
        v0 = addiu(v0, 1);
    }
    // 0x004fb098
    charge(ctx, 7);
    v0 = sra(v0, 1);
    v0 = addu(v0, v1);
    sw(v0, a1, 0);
    v0 = sll(t0, 1);
    v0 = addu(v0, t0);
    lw(v1, a2, 4);
    if (i64(t0) > 0) {
        // 0x004fb0b4
        charge(ctx, 1);
        v0 = addiu(v0, 1);
    }
    // 0x004fb0b8
    charge(ctx, 6);
    v0 = sra(v0, 1);
    v0 = addu(v0, v1);
    v0 = addiu(v0, -1);
    sw(v0, a1, 4);
    lw(v1, a2, 0);
    if (i64(a3) <= 0) {
        // 0x004fb0dc
        charge(ctx, 1);
        v0 = sra(a3, 1);
    } else {
        // 0x004fb0d0
        charge(ctx, 3);
        v0 = addiu(a3, 1);
        v0 = sra(v0, 1);
    }
    // 0x004fb0e0
    charge(ctx, 4);
    v0 = addu(v0, v1);
    sw(v0, a1, 8);
    lw(a2, a2, 4);
    if (i64(t0) <= 0) {
        // 0x004fb0f8
        charge(ctx, 2);
        v0 = sra(t0, 1);
        backedge(ctx);
    } else {
        // 0x004fb0f0
        charge(ctx, 2);
        v0 = addiu(t0, 1);
        backedge(ctx);
    L_004fb074:
        charge(ctx, 1);
        v0 = sra(v0, 1);
    }
    // 0x004fb078 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    v0 = addu(v0, a2);
    v0 = addiu(v0, 1);
    sw(v0, a1, 12);
}

// 0x00500858 _decodeOrSkipField -- 452 bytes; frame 0x80: s3 sp+0x50, s1 sp+0x30, ra sp+0x70, s4 sp+0x60, s2 sp+0x40, s0 sp+0x20
// libmpeg: decodes or skips one field (_decPicture / _updateRefImage / _sceMpegOutputFrame).
void _decodeOrSkipField(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00500858
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    v0 = si(-1);
    sd(s3, sp, 0x50);
    sd(s1, sp, 0x30);
    s3 = 0;
    sd(ra, sp, 0x70);
    s1 = a0;
    sd(s4, sp, 0x60);
    sd(s2, sp, 0x40);
    sd(s0, sp, 0x20);
    lw(s0, s1, 64);
    sw(zero, s0, 304);
    if (a2 != v0) {
        // 0x0050088c
        charge(ctx, 3);
        v0 = slt(a1, a2);
        if (v0 != 0) {
            goto L_00500898;
        }
        lw(v0, s0, 8);
        goto L_005008a0;
    }
L_00500898:
    charge(ctx, 2);
    s3 = 1;
    lw(v0, s0, 8);
L_005008a0:
    charge(ctx, 2);
    a0 = s0;
    if (v0 == 0) {
        // 0x005008a8
        charge(ctx, 3);
        sw(zero, s1, 8);
        v0 = 1;
        sw(v0, s0, 8);
    }
    // 0x005008b4
    charge(ctx, 4);
    a1 = 0;
    jal(ctx, 0x5008B4u, gen::fn__updateRefImage_00500430);
    if (v0 == 0) {
        lw(v0, s0, 2168);
    } else {
        // 0x005008c4
        charge(ctx, 2);
        if (s3 == 0) {
            lw(v0, s0, 2168);
        } else {
            // 0x005008cc
            charge(ctx, 3);
            a0 = s0;
            jal(ctx, 0x5008CCu, gen::fn__decPicture_00500f98);
            lw(v0, s0, 2168);
        }
    }
    // 0x005008d8
    charge(ctx, 2);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = 0;
    if (!cc) {
        // 0x005008e0
        charge(ctx, 6);
        s2 = 1;
        a0 = s0;
        link(ctx, 0x5008E8u);  // $ra first: the delay slot below depends on it
        sw(s2, s0, 304);
        call(ctx, gen::fn__sceMpegNextHeader_004ff9d8);
        if (v0 == 0) {
            // 0x005008f8
            charge(ctx, 5);
            a0 = s1;
            jal(ctx, 0x5008F8u, gen::fn__sceMpegFlush_00501ae8);
            sw(s2, s0, 0);
            v0 = 0;
            goto L_005009fc;
        }
        lw(v0, s0, 232);
        // 0x0050090c
        charge(ctx, 6);
        v1 = 2;
        lw(a0, s0, 388);
        v0 = v0 ^ 0x1;
        if (v0 != 0) v1 = s2;
        v0 = si(-1);
        if (a0 != v1) {
            goto L_005009fc;
        }
        // 0x00500924
        charge(ctx, 7);
        a0 = s0;
        a1 = 1;
        jal(ctx, 0x500928u, gen::fn__updateRefImage_00500430);
        v1 = 0;
        if (v0 != 0) v1 = s2;
        s4 = 0;
        if (v1 != 0) {
            // 0x00500940
            charge(ctx, 2);
            if (s3 != 0) {
                // 0x00500948
                charge(ctx, 3);
                a0 = s0;
                jal(ctx, 0x500948u, gen::fn__decPicture_00500f98);
                if (v0 != 0) s4 = s2;
                goto L_00500954;
            }
            lw(v0, s0, 2168);
            goto L_00500958;
        }
    L_00500954:
        charge(ctx, 1);
        lw(v0, s0, 2168);
    L_00500958:
        charge(ctx, 2);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = 0;
        if (cc) {
            goto L_005009fc;
        }
        // 0x00500960
        charge(ctx, 16);
        lw(a1, s0, 296);
        a0 = s0;
        link(ctx, 0x500968u);  // $ra first: the delay slot below depends on it
        lw(a2, s0, 4);
        call(ctx, gen::fn__sceMpegOutputFrame_00501ba8);
        lw(v0, s0, 296);
        lw(v1, s0, 192);
        sw(zero, s0, 304);
        v0 = subu(v0, v1);
        sw(v0, s1, 8);
        lw(v1, s0, 296);
        lw(v0, s0, 4);
        v1 = addiu(v1, 1);
        v0 = addiu(v0, 1);
        sw(v1, s0, 296);
        sw(v0, s0, 4);
        if (s3 == 0) {
            // 0x005009a0
            charge(ctx, 3);
            v0 = 1;
            sw(v0, sp, 0x0);
            if (s1 == 0) {
                goto L_005009f8;
            }
            // 0x005009ac
            charge(ctx, 3);
            lw(a2, s1, 64);
            v0 = s4;
            if (a2 == 0) {
                goto L_005009fc;
            }
            // 0x005009b8
            charge(ctx, 3);
            lw(a3, a2, 24);
            ld(ra, sp, 0x70);
            if (a3 != 0) {
                // 0x005009c4
                charge(ctx, 13);
                lw(v0, a2, 32);
                s0 = gp;
                gp = v0;
                lw(v1, sp, 0x0);
                v0 = 12;
                a0 = s1;
                a1 = sp;
                mult(t0, v1, v0);
                v1 = addu(t0, a2);
                jt = a3.u();  // the target, read before the delay slot
                link(ctx, 0x5009E8u);  // $ra = the return address
                lw(a2, v1, 16);
                call_ptr(ctx, jt);
                v1 = gp;
                gp = s0;
                goto L_005009f8;
            }
            // 0x00500a00 (the shared epilogue, written out on this path)
            charge(ctx, 7);
            ld(s4, sp, 0x60);
            ld(s3, sp, 0x50);
            ld(s2, sp, 0x40);
            ld(s1, sp, 0x30);
            ld(s0, sp, 0x20);
            sp = addiu(sp, 0x80);
            return;
        }
    L_005009f8:
        charge(ctx, 1);
        v0 = s4;
        goto L_005009fc;
    }
L_005009fc:
    charge(ctx, 1);
    ld(ra, sp, 0x70);
    // 0x00500a00 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s4, sp, 0x60);
    ld(s3, sp, 0x50);
    ld(s2, sp, 0x40);
    ld(s1, sp, 0x30);
    ld(s0, sp, 0x20);
    sp = addiu(sp, 0x80);
}

// 0x00513648 sceMc2UnformatAsync -- 176 bytes; frame 0x30: s0 sp+0x0, ra sp+0x20, s1 sp+0x10
// libmc2 async request (SCE memory-card library): takes the library semaphore, checks the open socket
// (_sceMcCoreChangeSocketTypeDbc2Mc), copies the path argument(s) into the request block and queues it, then signals
// the semaphore; returns the library result code.
void sceMc2UnformatAsync(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00513648
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v1 = 0x780000;
    sd(s0, sp, 0x0);
    lw(v0, v1, 10200);  // 0x7827D8
    s0 = a0;
    sd(ra, sp, 0x20);
    sd(s1, sp, 0x10);
    if (v0 != 0) {
        // 0x00513674
        charge(ctx, 5);
        a0 = s0;
        jal(ctx, 0x513674u, gen::fn__sceMcCoreChangeSocketTypeDbc2Mc_0051c2e8);
        s0 = v0;
        s1 = 0x970000;
        if (i64(s0) >= 0) {
            // 0x00513694
            charge(ctx, 7);
            link(ctx, 0x513694u);  // $ra first: the delay slot below depends on it
            lw(a0, s1, -2452);
            call(ctx, gen::fn__sceWaitSema_005031a0);
            a2 = 0x970000;
            a1 = addiu(a2, -3776);  // &0x96F140
            lw(v0, a1, 4);  // 0x96F144
            if (v0 == 0) {
                v0 = 0x970000;
                // 0x005136c4
                charge(ctx, 8);
                v1 = 4;
                lw(a0, v0, -2460);
                sw(s0, a2, -3776);
                link(ctx, 0x5136D0u);  // $ra first: the delay slot below depends on it
                sw(v1, a1, 4);
                call(ctx, gen::fn__sceSignalSema_00503180);
                link(ctx, 0x5136D8u);  // $ra first: the delay slot below depends on it
                lw(a0, s1, -2452);
                call(ctx, gen::fn__sceSignalSema_00503180);
                v0 = 0;
            } else {
                // 0x005136b0
                charge(ctx, 5);
                link(ctx, 0x5136B0u);  // $ra first: the delay slot below depends on it
                lw(a0, s1, -2452);
                call(ctx, gen::fn__sceSignalSema_00503180);
                v0 = lui(0x8101);
                v0 = v0 | 0x10;
            }
        } else {
            // 0x00513688
            charge(ctx, 3);
            v0 = lui(0x8101);
            v0 = v0 | 0x8002;
        }
    } else {
        // 0x00513668
        charge(ctx, 3);
        v0 = lui(0x8101);
        v0 = v0 | 0x8001;
    }
    // 0x005136e4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00513A88 sceMc2ReadFastFileAsync -- 288 bytes; frame 0x80: s6 sp+0x60, s5 sp+0x50, s4 sp+0x40, s3 sp+0x30, s1 sp+0x10, ra sp+0x70, s2 sp+0x20, s0 sp+0x0
// libmc2 async request (SCE memory-card library): takes the library semaphore, checks the open socket
// (_sceMcCoreChangeSocketTypeDbc2Mc), copies the path argument(s) into the request block and queues it, then signals
// the semaphore; returns the library result code.
void sceMc2ReadFastFileAsync(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00513a88
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    v0 = 0x780000;
    sd(s6, sp, 0x60);
    sd(s5, sp, 0x50);
    s6 = a3;
    sd(s4, sp, 0x40);
    s5 = a2;
    sd(s3, sp, 0x30);
    s4 = t0;
    sd(s1, sp, 0x10);
    s3 = a1;
    lw(v1, v0, 10200);  // 0x7827D8
    s1 = a0;
    sd(ra, sp, 0x70);
    sd(s2, sp, 0x20);
    sd(s0, sp, 0x0);
    if (v1 != 0) {
        // 0x00513ad8
        charge(ctx, 5);
        a0 = s1;
        jal(ctx, 0x513AD8u, gen::fn__sceMcCoreChangeSocketTypeDbc2Mc_0051c2e8);
        s1 = v0;
        if (i64(s1) >= 0) {
            // 0x00513af8
            charge(ctx, 5);
            a0 = s3;
            jal(ctx, 0x513AF8u, gen::fn_strlen_00524388);
            v0 = sltiu(v0, 128);
            s2 = 0x970000;
            if (v0 != 0) {
                // 0x00513b18
                charge(ctx, 7);
                link(ctx, 0x513B18u);  // $ra first: the delay slot below depends on it
                lw(a0, s2, -2452);
                call(ctx, gen::fn__sceWaitSema_005031a0);
                v1 = 0x970000;
                s0 = addiu(v1, -3776);  // &0x96F140
                lw(v0, s0, 4);  // 0x96F144
                if (v0 == 0) {
                    v0 = 32;
                    // 0x00513b48
                    charge(ctx, 14);
                    sw(s1, v1, -3776);
                    sw(v0, s0, 4);
                    a1 = s3;
                    a0 = addiu(s0, 1052);
                    jal(ctx, 0x513B54u, gen::fn_strcpy_00524270);
                    sw(s4, s0, 20);
                    v1 = 0x970000;
                    lw(a0, v1, -2460);  // 0x96F664
                    sw(s5, s0, 12);
                    link(ctx, 0x513B6Cu);  // $ra first: the delay slot below depends on it
                    sw(s6, s0, 16);
                    call(ctx, gen::fn__sceSignalSema_00503180);
                    link(ctx, 0x513B74u);  // $ra first: the delay slot below depends on it
                    lw(a0, s2, -2452);
                    call(ctx, gen::fn__sceSignalSema_00503180);
                    v0 = 0;
                } else {
                    // 0x00513b34
                    charge(ctx, 5);
                    link(ctx, 0x513B34u);  // $ra first: the delay slot below depends on it
                    lw(a0, s2, -2452);
                    call(ctx, gen::fn__sceSignalSema_00503180);
                    v0 = lui(0x8101);
                    v0 = v0 | 0x10;
                }
            } else {
                // 0x00513b0c
                charge(ctx, 3);
                v0 = lui(0x8101);
                v0 = v0 | 0x5B;
            }
        } else {
            // 0x00513aec
            charge(ctx, 3);
            v0 = lui(0x8101);
            v0 = v0 | 0x8002;
        }
    } else {
        // 0x00513acc
        charge(ctx, 3);
        v0 = lui(0x8101);
        v0 = v0 | 0x8001;
    }
    // 0x00513b80 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x70);
    ld(s6, sp, 0x60);
    ld(s5, sp, 0x50);
    ld(s4, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x00513BA8 sceMc2WriteFastFileAsync -- 288 bytes; frame 0x80: s6 sp+0x60, s5 sp+0x50, s4 sp+0x40, s3 sp+0x30, s1 sp+0x10, ra sp+0x70, s2 sp+0x20, s0 sp+0x0
// libmc2 async request (SCE memory-card library): takes the library semaphore, checks the open socket
// (_sceMcCoreChangeSocketTypeDbc2Mc), copies the path argument(s) into the request block and queues it, then signals
// the semaphore; returns the library result code.
void sceMc2WriteFastFileAsync(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00513ba8
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    v0 = 0x780000;
    sd(s6, sp, 0x60);
    sd(s5, sp, 0x50);
    s6 = a3;
    sd(s4, sp, 0x40);
    s5 = a2;
    sd(s3, sp, 0x30);
    s4 = t0;
    sd(s1, sp, 0x10);
    s3 = a1;
    lw(v1, v0, 10200);  // 0x7827D8
    s1 = a0;
    sd(ra, sp, 0x70);
    sd(s2, sp, 0x20);
    sd(s0, sp, 0x0);
    if (v1 != 0) {
        // 0x00513bf8
        charge(ctx, 5);
        a0 = s1;
        jal(ctx, 0x513BF8u, gen::fn__sceMcCoreChangeSocketTypeDbc2Mc_0051c2e8);
        s1 = v0;
        if (i64(s1) >= 0) {
            // 0x00513c18
            charge(ctx, 5);
            a0 = s3;
            jal(ctx, 0x513C18u, gen::fn_strlen_00524388);
            v0 = sltiu(v0, 128);
            s2 = 0x970000;
            if (v0 != 0) {
                // 0x00513c38
                charge(ctx, 7);
                link(ctx, 0x513C38u);  // $ra first: the delay slot below depends on it
                lw(a0, s2, -2452);
                call(ctx, gen::fn__sceWaitSema_005031a0);
                v1 = 0x970000;
                s0 = addiu(v1, -3776);  // &0x96F140
                lw(v0, s0, 4);  // 0x96F144
                if (v0 == 0) {
                    v0 = 33;
                    // 0x00513c68
                    charge(ctx, 14);
                    sw(s1, v1, -3776);
                    sw(v0, s0, 4);
                    a1 = s3;
                    a0 = addiu(s0, 1052);
                    jal(ctx, 0x513C74u, gen::fn_strcpy_00524270);
                    sw(s4, s0, 20);
                    v1 = 0x970000;
                    lw(a0, v1, -2460);  // 0x96F664
                    sw(s5, s0, 12);
                    link(ctx, 0x513C8Cu);  // $ra first: the delay slot below depends on it
                    sw(s6, s0, 16);
                    call(ctx, gen::fn__sceSignalSema_00503180);
                    link(ctx, 0x513C94u);  // $ra first: the delay slot below depends on it
                    lw(a0, s2, -2452);
                    call(ctx, gen::fn__sceSignalSema_00503180);
                    v0 = 0;
                } else {
                    // 0x00513c54
                    charge(ctx, 5);
                    link(ctx, 0x513C54u);  // $ra first: the delay slot below depends on it
                    lw(a0, s2, -2452);
                    call(ctx, gen::fn__sceSignalSema_00503180);
                    v0 = lui(0x8101);
                    v0 = v0 | 0x10;
                }
            } else {
                // 0x00513c2c
                charge(ctx, 3);
                v0 = lui(0x8101);
                v0 = v0 | 0x5B;
            }
        } else {
            // 0x00513c0c
            charge(ctx, 3);
            v0 = lui(0x8101);
            v0 = v0 | 0x8002;
        }
    } else {
        // 0x00513bec
        charge(ctx, 3);
        v0 = lui(0x8101);
        v0 = v0 | 0x8001;
    }
    // 0x00513ca0 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x70);
    ld(s6, sp, 0x60);
    ld(s5, sp, 0x50);
    ld(s4, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x00513EE0 sceMc2DeleteAsync -- 232 bytes; frame 0x40: s2 sp+0x20, s0 sp+0x0, ra sp+0x30, s1 sp+0x10
// libmc2 async request (SCE memory-card library): takes the library semaphore, checks the open socket
// (_sceMcCoreChangeSocketTypeDbc2Mc), copies the path argument(s) into the request block and queues it, then signals
// the semaphore; returns the library result code.
void sceMc2DeleteAsync(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00513ee0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = 0x780000;
    sd(s2, sp, 0x20);
    sd(s0, sp, 0x0);
    s2 = a1;
    lw(v1, v0, 10200);  // 0x7827D8
    s0 = a0;
    sd(ra, sp, 0x30);
    sd(s1, sp, 0x10);
    if (v1 != 0) {
        // 0x00513f14
        charge(ctx, 5);
        a0 = s0;
        jal(ctx, 0x513F14u, gen::fn__sceMcCoreChangeSocketTypeDbc2Mc_0051c2e8);
        s0 = v0;
        if (i64(s0) >= 0) {
            // 0x00513f34
            charge(ctx, 5);
            a0 = s2;
            jal(ctx, 0x513F34u, gen::fn_strlen_00524388);
            v0 = sltiu(v0, 128);
            s1 = 0x970000;
            if (v0 != 0) {
                // 0x00513f54
                charge(ctx, 7);
                link(ctx, 0x513F54u);  // $ra first: the delay slot below depends on it
                lw(a0, s1, -2452);
                call(ctx, gen::fn__sceWaitSema_005031a0);
                v1 = 0x970000;
                a0 = addiu(v1, -3776);  // &0x96F140
                lw(v0, a0, 4);  // 0x96F144
                if (v0 == 0) {
                    v0 = 8;
                    // 0x00513f84
                    charge(ctx, 11);
                    sw(s0, v1, -3776);
                    sw(v0, a0, 4);
                    a1 = s2;
                    a0 = addiu(a0, 1052);
                    jal(ctx, 0x513F90u, gen::fn_strcpy_00524270);
                    v1 = 0x970000;
                    link(ctx, 0x513F9Cu);  // $ra first: the delay slot below depends on it
                    lw(a0, v1, -2460);
                    call(ctx, gen::fn__sceSignalSema_00503180);
                    link(ctx, 0x513FA4u);  // $ra first: the delay slot below depends on it
                    lw(a0, s1, -2452);
                    call(ctx, gen::fn__sceSignalSema_00503180);
                    v0 = 0;
                } else {
                    // 0x00513f70
                    charge(ctx, 5);
                    link(ctx, 0x513F70u);  // $ra first: the delay slot below depends on it
                    lw(a0, s1, -2452);
                    call(ctx, gen::fn__sceSignalSema_00503180);
                    v0 = lui(0x8101);
                    v0 = v0 | 0x10;
                }
            } else {
                // 0x00513f48
                charge(ctx, 3);
                v0 = lui(0x8101);
                v0 = v0 | 0x5B;
            }
        } else {
            // 0x00513f28
            charge(ctx, 3);
            v0 = lui(0x8101);
            v0 = v0 | 0x8002;
        }
    } else {
        // 0x00513f08
        charge(ctx, 3);
        v0 = lui(0x8101);
        v0 = v0 | 0x8001;
    }
    // 0x00513fb0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00513FC8 sceMc2GetDirAsync -- 304 bytes; frame 0x90: s7 sp+0x70, s6 sp+0x60, s5 sp+0x50, s4 sp+0x40, s3 sp+0x30, s1 sp+0x10, ra sp+0x80, s2 sp+0x20, s0 sp+0x0
// libmc2 async request (SCE memory-card library): takes the library semaphore, checks the open socket
// (_sceMcCoreChangeSocketTypeDbc2Mc), copies the path argument(s) into the request block and queues it, then signals
// the semaphore; returns the library result code.
void sceMc2GetDirAsync(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00513fc8
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    v0 = 0x780000;
    sd(s7, sp, 0x70);
    sd(s6, sp, 0x60);
    s7 = t0;
    sd(s5, sp, 0x50);
    s6 = a3;
    sd(s4, sp, 0x40);
    s5 = a2;
    sd(s3, sp, 0x30);
    s4 = t1;
    sd(s1, sp, 0x10);
    s3 = a1;
    lw(v1, v0, 10200);  // 0x7827D8
    s1 = a0;
    sd(ra, sp, 0x80);
    sd(s2, sp, 0x20);
    sd(s0, sp, 0x0);
    if (v1 != 0) {
        // 0x00514020
        charge(ctx, 5);
        a0 = s1;
        jal(ctx, 0x514020u, gen::fn__sceMcCoreChangeSocketTypeDbc2Mc_0051c2e8);
        s1 = v0;
        if (i64(s1) >= 0) {
            // 0x00514040
            charge(ctx, 5);
            a0 = s3;
            jal(ctx, 0x514040u, gen::fn_strlen_00524388);
            v0 = sltiu(v0, 128);
            s2 = 0x970000;
            if (v0 != 0) {
                // 0x00514060
                charge(ctx, 7);
                link(ctx, 0x514060u);  // $ra first: the delay slot below depends on it
                lw(a0, s2, -2452);
                call(ctx, gen::fn__sceWaitSema_005031a0);
                v1 = 0x970000;
                s0 = addiu(v1, -3776);  // &0x96F140
                lw(v0, s0, 4);  // 0x96F144
                if (v0 == 0) {
                    v0 = 10;
                    // 0x00514090
                    charge(ctx, 15);
                    sw(s1, v1, -3776);
                    sw(v0, s0, 4);
                    a1 = s3;
                    a0 = addiu(s0, 1052);
                    jal(ctx, 0x51409Cu, gen::fn_strcpy_00524270);
                    sw(s4, s0, 24);
                    v1 = 0x970000;
                    lw(a0, v1, -2460);  // 0x96F664
                    sw(s5, s0, 12);
                    sw(s6, s0, 16);
                    link(ctx, 0x5140B8u);  // $ra first: the delay slot below depends on it
                    sw(s7, s0, 20);
                    call(ctx, gen::fn__sceSignalSema_00503180);
                    link(ctx, 0x5140C0u);  // $ra first: the delay slot below depends on it
                    lw(a0, s2, -2452);
                    call(ctx, gen::fn__sceSignalSema_00503180);
                    v0 = 0;
                } else {
                    // 0x0051407c
                    charge(ctx, 5);
                    link(ctx, 0x51407Cu);  // $ra first: the delay slot below depends on it
                    lw(a0, s2, -2452);
                    call(ctx, gen::fn__sceSignalSema_00503180);
                    v0 = lui(0x8101);
                    v0 = v0 | 0x10;
                }
            } else {
                // 0x00514054
                charge(ctx, 3);
                v0 = lui(0x8101);
                v0 = v0 | 0x5B;
            }
        } else {
            // 0x00514034
            charge(ctx, 3);
            v0 = lui(0x8101);
            v0 = v0 | 0x8002;
        }
    } else {
        // 0x00514014
        charge(ctx, 3);
        v0 = lui(0x8101);
        v0 = v0 | 0x8001;
    }
    // 0x005140cc (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x80);
    ld(s7, sp, 0x70);
    ld(s6, sp, 0x60);
    ld(s5, sp, 0x50);
    ld(s4, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x005141F0 sceMc2ChdirAsync -- 256 bytes; frame 0x60: s4 sp+0x40, s3 sp+0x30, s0 sp+0x0, ra sp+0x50, s2 sp+0x20, s1 sp+0x10
// libmc2 async request (SCE memory-card library): takes the library semaphore, checks the open socket
// (_sceMcCoreChangeSocketTypeDbc2Mc), copies the path argument(s) into the request block and queues it, then signals
// the semaphore; returns the library result code.
void sceMc2ChdirAsync(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005141f0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    v0 = 0x780000;
    sd(s4, sp, 0x40);
    sd(s3, sp, 0x30);
    s4 = a2;
    sd(s0, sp, 0x0);
    s3 = a1;
    lw(v1, v0, 10200);  // 0x7827D8
    s0 = a0;
    sd(ra, sp, 0x50);
    sd(s2, sp, 0x20);
    sd(s1, sp, 0x10);
    if (v1 != 0) {
        // 0x00514230
        charge(ctx, 5);
        a0 = s0;
        jal(ctx, 0x514230u, gen::fn__sceMcCoreChangeSocketTypeDbc2Mc_0051c2e8);
        s0 = v0;
        if (i64(s0) >= 0) {
            // 0x00514250
            charge(ctx, 5);
            a0 = s3;
            jal(ctx, 0x514250u, gen::fn_strlen_00524388);
            v0 = sltiu(v0, 128);
            s2 = 0x970000;
            if (v0 != 0) {
                // 0x00514270
                charge(ctx, 7);
                link(ctx, 0x514270u);  // $ra first: the delay slot below depends on it
                lw(a0, s2, -2452);
                call(ctx, gen::fn__sceWaitSema_005031a0);
                v1 = 0x970000;
                s1 = addiu(v1, -3776);  // &0x96F140
                lw(v0, s1, 4);  // 0x96F144
                if (v0 == 0) {
                    v0 = 12;
                    // 0x005142a0
                    charge(ctx, 12);
                    sw(s0, v1, -3776);
                    sw(v0, s1, 4);
                    a1 = s3;
                    a0 = addiu(s1, 1052);
                    jal(ctx, 0x5142ACu, gen::fn_strcpy_00524270);
                    sw(s4, s1, 12);
                    v1 = 0x970000;
                    link(ctx, 0x5142BCu);  // $ra first: the delay slot below depends on it
                    lw(a0, v1, -2460);
                    call(ctx, gen::fn__sceSignalSema_00503180);
                    link(ctx, 0x5142C4u);  // $ra first: the delay slot below depends on it
                    lw(a0, s2, -2452);
                    call(ctx, gen::fn__sceSignalSema_00503180);
                    v0 = 0;
                } else {
                    // 0x0051428c
                    charge(ctx, 5);
                    link(ctx, 0x51428Cu);  // $ra first: the delay slot below depends on it
                    lw(a0, s2, -2452);
                    call(ctx, gen::fn__sceSignalSema_00503180);
                    v0 = lui(0x8101);
                    v0 = v0 | 0x10;
                }
            } else {
                // 0x00514264
                charge(ctx, 3);
                v0 = lui(0x8101);
                v0 = v0 | 0x5B;
            }
        } else {
            // 0x00514244
            charge(ctx, 3);
            v0 = lui(0x8101);
            v0 = v0 | 0x8002;
        }
    } else {
        // 0x00514224
        charge(ctx, 3);
        v0 = lui(0x8101);
        v0 = v0 | 0x8001;
    }
    // 0x005142d0 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    ld(s4, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x005142F0 sceMc2ChmodAsync -- 256 bytes; frame 0x60: s4 sp+0x40, s3 sp+0x30, s0 sp+0x0, ra sp+0x50, s2 sp+0x20, s1 sp+0x10
// libmc2 async request (SCE memory-card library): takes the library semaphore, checks the open socket
// (_sceMcCoreChangeSocketTypeDbc2Mc), copies the path argument(s) into the request block and queues it, then signals
// the semaphore; returns the library result code.
void sceMc2ChmodAsync(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005142f0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    v0 = 0x780000;
    sd(s4, sp, 0x40);
    sd(s3, sp, 0x30);
    s4 = a2 & 0xFFFF;
    sd(s0, sp, 0x0);
    s3 = a1;
    lw(v1, v0, 10200);  // 0x7827D8
    s0 = a0;
    sd(ra, sp, 0x50);
    sd(s2, sp, 0x20);
    sd(s1, sp, 0x10);
    if (v1 != 0) {
        // 0x00514330
        charge(ctx, 5);
        a0 = s0;
        jal(ctx, 0x514330u, gen::fn__sceMcCoreChangeSocketTypeDbc2Mc_0051c2e8);
        s0 = v0;
        if (i64(s0) >= 0) {
            // 0x00514350
            charge(ctx, 5);
            a0 = s3;
            jal(ctx, 0x514350u, gen::fn_strlen_00524388);
            v0 = sltiu(v0, 128);
            s2 = 0x970000;
            if (v0 != 0) {
                // 0x00514370
                charge(ctx, 7);
                link(ctx, 0x514370u);  // $ra first: the delay slot below depends on it
                lw(a0, s2, -2452);
                call(ctx, gen::fn__sceWaitSema_005031a0);
                v1 = 0x970000;
                s1 = addiu(v1, -3776);  // &0x96F140
                lw(v0, s1, 4);  // 0x96F144
                if (v0 == 0) {
                    v0 = 13;
                    // 0x005143a0
                    charge(ctx, 12);
                    sw(s0, v1, -3776);
                    sw(v0, s1, 4);
                    a1 = s3;
                    a0 = addiu(s1, 1052);
                    jal(ctx, 0x5143ACu, gen::fn_strcpy_00524270);
                    sw(s4, s1, 12);
                    v1 = 0x970000;
                    link(ctx, 0x5143BCu);  // $ra first: the delay slot below depends on it
                    lw(a0, v1, -2460);
                    call(ctx, gen::fn__sceSignalSema_00503180);
                    link(ctx, 0x5143C4u);  // $ra first: the delay slot below depends on it
                    lw(a0, s2, -2452);
                    call(ctx, gen::fn__sceSignalSema_00503180);
                    v0 = 0;
                } else {
                    // 0x0051438c
                    charge(ctx, 5);
                    link(ctx, 0x51438Cu);  // $ra first: the delay slot below depends on it
                    lw(a0, s2, -2452);
                    call(ctx, gen::fn__sceSignalSema_00503180);
                    v0 = lui(0x8101);
                    v0 = v0 | 0x10;
                }
            } else {
                // 0x00514364
                charge(ctx, 3);
                v0 = lui(0x8101);
                v0 = v0 | 0x5B;
            }
        } else {
            // 0x00514344
            charge(ctx, 3);
            v0 = lui(0x8101);
            v0 = v0 | 0x8002;
        }
    } else {
        // 0x00514324
        charge(ctx, 3);
        v0 = lui(0x8101);
        v0 = v0 | 0x8001;
    }
    // 0x005143d0 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    ld(s4, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x005143F0 sceMc2RenameAsync -- 284 bytes; frame 0x60: s4 sp+0x40, s3 sp+0x30, s1 sp+0x10, ra sp+0x50, s2 sp+0x20, s0 sp+0x0
// libmc2 async request (SCE memory-card library): takes the library semaphore, checks the open socket
// (_sceMcCoreChangeSocketTypeDbc2Mc), copies the path argument(s) into the request block and queues it, then signals
// the semaphore; returns the library result code.
void sceMc2RenameAsync(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005143f0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    v0 = 0x780000;
    sd(s4, sp, 0x40);
    sd(s3, sp, 0x30);
    s4 = a2;
    sd(s1, sp, 0x10);
    s3 = a1;
    lw(v1, v0, 10200);  // 0x7827D8
    s1 = a0;
    sd(ra, sp, 0x50);
    sd(s2, sp, 0x20);
    sd(s0, sp, 0x0);
    if (v1 != 0) {
        // 0x00514430
        charge(ctx, 5);
        a0 = s1;
        jal(ctx, 0x514430u, gen::fn__sceMcCoreChangeSocketTypeDbc2Mc_0051c2e8);
        s1 = v0;
        if (i64(s1) >= 0) {
            // 0x00514450
            charge(ctx, 5);
            a0 = s3;
            jal(ctx, 0x514450u, gen::fn_strlen_00524388);
            v0 = sltiu(v0, 128);
            if (v0 != 0) {
                // 0x00514464
                charge(ctx, 5);
                a0 = s4;
                jal(ctx, 0x514464u, gen::fn_strlen_00524388);
                v0 = sltiu(v0, 128);
                s2 = 0x970000;
                if (v0 == 0) {
                    goto L_00514478;
                }
                // 0x00514484
                charge(ctx, 7);
                link(ctx, 0x514484u);  // $ra first: the delay slot below depends on it
                lw(a0, s2, -2452);
                call(ctx, gen::fn__sceWaitSema_005031a0);
                v1 = 0x970000;
                s0 = addiu(v1, -3776);  // &0x96F140
                lw(v0, s0, 4);  // 0x96F144
                if (v0 == 0) {
                    v0 = 9;
                    // 0x005144b4
                    charge(ctx, 14);
                    sw(s1, v1, -3776);
                    sw(v0, s0, 4);
                    a1 = s3;
                    a0 = addiu(s0, 1052);
                    jal(ctx, 0x5144C0u, gen::fn_strcpy_00524270);
                    a0 = addiu(s0, 1180);
                    a1 = s4;
                    jal(ctx, 0x5144CCu, gen::fn_strcpy_00524270);
                    v1 = 0x970000;
                    link(ctx, 0x5144D8u);  // $ra first: the delay slot below depends on it
                    lw(a0, v1, -2460);
                    call(ctx, gen::fn__sceSignalSema_00503180);
                    link(ctx, 0x5144E0u);  // $ra first: the delay slot below depends on it
                    lw(a0, s2, -2452);
                    call(ctx, gen::fn__sceSignalSema_00503180);
                    v0 = 0;
                } else {
                    // 0x005144a0
                    charge(ctx, 5);
                    link(ctx, 0x5144A0u);  // $ra first: the delay slot below depends on it
                    lw(a0, s2, -2452);
                    call(ctx, gen::fn__sceSignalSema_00503180);
                    v0 = lui(0x8101);
                    v0 = v0 | 0x10;
                }
                // 0x005144ec (the shared epilogue, written out on this path)
                charge(ctx, 8);
                ld(ra, sp, 0x50);
                ld(s4, sp, 0x40);
                ld(s3, sp, 0x30);
                ld(s2, sp, 0x20);
                ld(s1, sp, 0x10);
                ld(s0, sp, 0x0);
                sp = addiu(sp, 0x60);
                return;
            }
        L_00514478:
            charge(ctx, 3);
            v0 = lui(0x8101);
            v0 = v0 | 0x5B;
        } else {
            // 0x00514444
            charge(ctx, 3);
            v0 = lui(0x8101);
            v0 = v0 | 0x8002;
        }
    } else {
        // 0x00514424
        charge(ctx, 3);
        v0 = lui(0x8101);
        v0 = v0 | 0x8001;
    }
    // 0x005144ec (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    ld(s4, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00514510 sceMc2GetEntSpaceAsync -- 232 bytes; frame 0x40: s2 sp+0x20, s0 sp+0x0, ra sp+0x30, s1 sp+0x10
// libmc2 async request (SCE memory-card library): takes the library semaphore, checks the open socket
// (_sceMcCoreChangeSocketTypeDbc2Mc), copies the path argument(s) into the request block and queues it, then signals
// the semaphore; returns the library result code.
void sceMc2GetEntSpaceAsync(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00514510
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = 0x780000;
    sd(s2, sp, 0x20);
    sd(s0, sp, 0x0);
    s2 = a1;
    lw(v1, v0, 10200);  // 0x7827D8
    s0 = a0;
    sd(ra, sp, 0x30);
    sd(s1, sp, 0x10);
    if (v1 != 0) {
        // 0x00514544
        charge(ctx, 5);
        a0 = s0;
        jal(ctx, 0x514544u, gen::fn__sceMcCoreChangeSocketTypeDbc2Mc_0051c2e8);
        s0 = v0;
        if (i64(s0) >= 0) {
            // 0x00514564
            charge(ctx, 5);
            a0 = s2;
            jal(ctx, 0x514564u, gen::fn_strlen_00524388);
            v0 = sltiu(v0, 128);
            s1 = 0x970000;
            if (v0 != 0) {
                // 0x00514584
                charge(ctx, 7);
                link(ctx, 0x514584u);  // $ra first: the delay slot below depends on it
                lw(a0, s1, -2452);
                call(ctx, gen::fn__sceWaitSema_005031a0);
                v1 = 0x970000;
                a0 = addiu(v1, -3776);  // &0x96F140
                lw(v0, a0, 4);  // 0x96F144
                if (v0 == 0) {
                    v0 = 15;
                    // 0x005145b4
                    charge(ctx, 11);
                    sw(s0, v1, -3776);
                    sw(v0, a0, 4);
                    a1 = s2;
                    a0 = addiu(a0, 1052);
                    jal(ctx, 0x5145C0u, gen::fn_strcpy_00524270);
                    v1 = 0x970000;
                    link(ctx, 0x5145CCu);  // $ra first: the delay slot below depends on it
                    lw(a0, v1, -2460);
                    call(ctx, gen::fn__sceSignalSema_00503180);
                    link(ctx, 0x5145D4u);  // $ra first: the delay slot below depends on it
                    lw(a0, s1, -2452);
                    call(ctx, gen::fn__sceSignalSema_00503180);
                    v0 = 0;
                } else {
                    // 0x005145a0
                    charge(ctx, 5);
                    link(ctx, 0x5145A0u);  // $ra first: the delay slot below depends on it
                    lw(a0, s1, -2452);
                    call(ctx, gen::fn__sceSignalSema_00503180);
                    v0 = lui(0x8101);
                    v0 = v0 | 0x10;
                }
            } else {
                // 0x00514578
                charge(ctx, 3);
                v0 = lui(0x8101);
                v0 = v0 | 0x5B;
            }
        } else {
            // 0x00514558
            charge(ctx, 3);
            v0 = lui(0x8101);
            v0 = v0 | 0x8002;
        }
    } else {
        // 0x00514538
        charge(ctx, 3);
        v0 = lui(0x8101);
        v0 = v0 | 0x8001;
    }
    // 0x005145e0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0051BBD8 _sceMcCoreBlockErase -- 308 bytes; frame 0x80: s0 sp+0x10, s1 sp+0x20, s4 sp+0x50, s2 sp+0x30, ra sp+0x70, s5 sp+0x60, s3 sp+0x40
// libmc2 core: block erase request over the DBC connection (sceDbcSendData3, SyncDma).
void _sceMcCoreBlockErase(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051bbd8
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    v0 = 36;
    sd(s0, sp, 0x10);
    v1 = 0x980000;
    mult(s0, a0, v0);
    sd(s1, sp, 0x20);
    s1 = addiu(v1, 21768);  // &0x985508
    sd(s4, sp, 0x50);
    sd(s2, sp, 0x30);
    v0 = addiu(s1, 4);  // &0x98550C
    sd(ra, sp, 0x70);
    s4 = a1;
    sd(s5, sp, 0x60);
    s2 = addu(s0, v0);
    sd(s3, sp, 0x40);
    link(ctx, 0x51BC14u);  // $ra first: the delay slot below depends on it
    lw(a0, s2, 0);
    call(ctx, gen::fn_sceDbcGetConnection_0051cad0);
    v1 = 3;
    a0 = addu(s1, s0);
    if (v0 != v1) {
        // 0x0051bc30
        charge(ctx, 34);
        s3 = 0x980000;
        v0 = a0;
        lw(t1, a0, 16);
        v1 = v0;
        lw(a2, v0, 8);
        lw(t0, v1, 12);
        v0 = addiu(s3, 21888);  // &0x985580
        v1 = 1;
        sw(s4, v0, 32);  // 0x9855A0
        sw(a2, v0, 8);  // 0x985588
        a3 = 48;
        sw(v1, v0, 4);  // 0x985584
        s0 = 0x980000;
        sw(t0, v0, 12);  // 0x98558C
        s0 = addiu(s0, 21952);  // &0x9855C0
        sw(t1, v0, 16);  // 0x985590
        a0 = s0;
        sw(a3, sp, 0x0);
        a1 = 0;
        sw(zero, s3, 21888);  // 0x985580
        a2 = 256;
        sw(zero, v0, 20);  // 0x985594
        s1 = 0x780000;
        sw(zero, v0, 24);  // 0x985598
        s5 = 0x520000;
        sw(zero, v0, 28);  // 0x98559C
        s4 = 1;
        jal(ctx, 0x51BC98u, gen::fn_memset_00521408);
        a0 = s0;
        a1 = addiu(a0, 255);  // &0x9856BF
        jal(ctx, 0x51BCA4u, gen::fn_SyncDCache_00503a58);
        v0 = 9;
        sw(v0, s1, 10988);  // 0x782AEC
        lw(a0, s2, 0);
        for (;;) {
            // 0x0051bcb8
            charge(ctx, 7);
            a2 = sp;
            lw(a1, s1, 10988);
            a3 = addiu(s3, 21888);
            t0 = addiu(s5, -20936);
            jal(ctx, 0x51BCC4u, gen::fn_sceDbcSendData3_0051d308);
            if (v0 == s4) {
                break;
            }
            lw(a0, s2, 0);
            backedge(ctx);
        }
        // 0x0051bcd4
        charge(ctx, 5);
        jal(ctx, 0x51BCD4u, gen::fn_SyncDma_0051ad10);
        lw(v0, v0, 8);
        v0 = v0 ^ 0x1;
        v0 = sltiu(v0, 1);
    } else {
        // 0x0051bc28
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x0051bce8 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x70);
    ld(s5, sp, 0x60);
    ld(s4, sp, 0x50);
    ld(s3, sp, 0x40);
    ld(s2, sp, 0x30);
    ld(s1, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x80);
}

// 0x0051BD10 _sceMcCoreReadPageFast -- 560 bytes; frame 0xB0: s0 sp+0x10, s2 sp+0x30, s7 sp+0x80, s6 sp+0x70, s1 sp+0x20, ra sp+0xA0, fp sp+0x90, s5 sp+0x60, s4 sp+0x50, s3 sp+0x40
// libmc2 core: fast page read over the DBC connection (cache invalidate, memcpy of the result).
void _sceMcCoreReadPageFast(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0051bd10
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    v0 = 36;
    sw(a0, sp, 0x4);
    sd(s0, sp, 0x10);
    mult(s0, a0, v0);
    sd(s2, sp, 0x30);
    v0 = 0x980000;
    sd(s7, sp, 0x80);
    sd(s6, sp, 0x70);
    s2 = addiu(v0, 21768);  // &0x985508
    sd(s1, sp, 0x20);
    s6 = a2;
    sd(ra, sp, 0xA0);
    v0 = addu(s2, s0);
    sd(fp, sp, 0x90);
    s1 = a1;
    sd(s5, sp, 0x60);
    s7 = a3;
    sd(s4, sp, 0x50);
    sd(s3, sp, 0x40);
    link(ctx, 0x51BD60u);  // $ra first: the delay slot below depends on it
    lw(a0, v0, 4);
    call(ctx, gen::fn_sceDbcGetConnection_0051cad0);
    v1 = 3;
    cc = v0 != v1;  // the condition, before the delay slot changes it
    v1 = addu(s2, s0);
    if (cc) {
        // 0x0051bd7c
        charge(ctx, 8);
        a0 = 0x10000;
        lw(v0, v1, 8);
        s5 = s1;
        div(a0, v0);
        mflo(v1);
        sw(v1, sp, 0x8);
        if (v0 == 0) {
            brk(ctx, 0x51BD98u, 0x7u);
        }
        // 0x0051bd9c
        charge(ctx, 2);
        fp = 0x980000;
        if (i64(s7) > 0) {
            // 0x0051bda4
            charge(ctx, 1);
            lw(v1, sp, 0x4);
            for (;;) {
                // 0x0051bda8
                charge(ctx, 57);
                v0 = 0x980000;
                lw(s4, sp, 0x8);
                s2 = addiu(v0, 21768);  // &0x985508
                s1 = 36;
                s0 = addiu(fp, 0x5580);
                mult(s1, v1, s1);
                v0 = slt(s7, s4);
                if (v0 != 0) s4 = s7;
                t2 = 48;
                v0 = 0x980000;
                a1 = 0;
                s3 = addiu(v0, 21952);  // &0x9855C0
                v0 = addu(s2, s1);
                a0 = s3;
                v1 = v0;
                lw(t1, v0, 8);
                lw(a3, v1, 12);
                a2 = v0;
                t0 = v0;
                lw(v1, a2, 16);
                lw(v0, t0, 20);
                a2 = 128;
                sw(v1, s0, 16);
                sw(t1, s0, 8);
                v1 = 0x980000;
                sw(a3, s0, 12);
                v1 = addiu(v1, 24256);  // &0x985EC0
                sw(v0, s0, 36);
                sw(t2, sp, 0x0);
                sw(s6, fp, 0x5580);
                sw(s4, s0, 4);
                sw(zero, s0, 20);
                sw(zero, s0, 24);
                sw(zero, s0, 28);
                sw(zero, s0, 32);
                link(ctx, 0x51BE34u);  // $ra first: the delay slot below depends on it
                sw(v1, s0, 40);
                call(ctx, gen::fn_memset_00521408);
                a0 = s3;
                a1 = addiu(a0, 127);  // &0x98563F
                jal(ctx, 0x51BE40u, gen::fn_SyncDCache_00503a58);
                v0 = 0x520000;
                s2 = addu(s2, s1);
                t0 = addiu(v0, -20936);  // &sceMc2SifCallback
                lw(a0, s2, 4);
                v0 = 17;
                v1 = 0x780000;
                a3 = s0;
                a1 = 17;
                sw(v0, v1, 10988);  // 0x782AEC
                a2 = sp;
                jal(ctx, 0x51BE6Cu, gen::fn_sceDbcSendData3_0051d308);
                jal(ctx, 0x51BE74u, gen::fn_SyncDmaForRead_0051ade0);
                lw(v1, v0, 8);
                v0 = 1;
                a1 = 0x990000;
                if (v1 != v0) {
                    backedge(ctx);
                    goto L_0051bd74;
                }
                // 0x0051be8c
                charge(ctx, 7);
                s2 = 0x980000;
                s2 = addiu(s2, 24256);  // &0x985EC0
                a1 = addiu(a1, 26431);
                a0 = s2;
                jal(ctx, 0x51BE98u, gen::fn_InvalidDCache_00503b98);
                s1 = 0;
                if (i64(s4) <= 0) {
                    // 0x0051bef8
                    charge(ctx, 3);
                    s6 = addu(s6, s4);
                    s3 = subu(s7, s4);
                    s7 = s3;
                } else {
                    // 0x0051bea8
                    charge(ctx, 2);
                    s3 = subu(s7, s4);
                    s6 = addu(s6, s4);
                    for (;;) {
                        // 0x0051beb0
                        charge(ctx, 16);
                        s0 = addiu(fp, 0x5580);
                        a0 = s5;
                        lw(a2, s0, 8);
                        a1 = s2;
                        s1 = addiu(s1, 1);
                        jal(ctx, 0x51BEC0u, gen::fn_memcpy_00521250);
                        lw(a1, s0, 8);
                        a0 = s5;
                        a1 = addu(s5, a1);
                        a1 = addiu(a1, -1);
                        jal(ctx, 0x51BED4u, gen::fn_SyncDCache_00503a58);
                        lw(v0, s0, 8);
                        v1 = slt(s1, s4);
                        s5 = addu(s5, v0);
                        s2 = addu(s2, v0);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0051bef0
                    charge(ctx, 2);
                    s7 = s3;
                }
                // 0x0051bf04
                charge(ctx, 2);
                lw(v1, sp, 0x4);
                if (i64(s7) <= 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x0051bf0c
        charge(ctx, 1);
        v0 = 1;
        // 0x0051bf10 (the shared epilogue, written out on this path)
        charge(ctx, 12);
        ld(ra, sp, 0xA0);
        ld(fp, sp, 0x90);
        ld(s7, sp, 0x80);
        ld(s6, sp, 0x70);
        ld(s5, sp, 0x60);
        ld(s4, sp, 0x50);
        ld(s3, sp, 0x40);
        ld(s2, sp, 0x30);
        ld(s1, sp, 0x20);
        ld(s0, sp, 0x10);
        sp = addiu(sp, 0xB0);
        return;
    }
L_0051bd74:
    charge(ctx, 2);
    v0 = 0;
    // 0x0051bf10 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0xA0);
    ld(fp, sp, 0x90);
    ld(s7, sp, 0x80);
    ld(s6, sp, 0x70);
    ld(s5, sp, 0x60);
    ld(s4, sp, 0x50);
    ld(s3, sp, 0x40);
    ld(s2, sp, 0x30);
    ld(s1, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0xB0);
}

// 0x0051BF40 _sceMcCoreWritePageFast -- 384 bytes; frame 0x90: s0 sp+0x10, s1 sp+0x20, s6 sp+0x70, s5 sp+0x60, s4 sp+0x50, s3 sp+0x40, ra sp+0x80, s2 sp+0x30
// libmc2 core: fast page write over the DBC connection.
void _sceMcCoreWritePageFast(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051bf40
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    v0 = 36;
    sd(s0, sp, 0x10);
    v1 = 0x980000;
    mult(s0, a0, v0);
    sd(s1, sp, 0x20);
    s1 = addiu(v1, 21768);  // &0x985508
    sd(s6, sp, 0x70);
    sd(s5, sp, 0x60);
    v0 = addiu(s1, 4);  // &0x98550C
    sd(s4, sp, 0x50);
    s5 = a2;
    sd(s3, sp, 0x40);
    s6 = addu(s0, v0);
    sd(ra, sp, 0x80);
    s3 = a1;
    sd(s2, sp, 0x30);
    s4 = a3;
    link(ctx, 0x51BF88u);  // $ra first: the delay slot below depends on it
    lw(a0, s6, 0);
    call(ctx, gen::fn_sceDbcGetConnection_0051cad0);
    v1 = 3;
    a3 = addu(s1, s0);
    if (v0 != v1) {
        // 0x0051bfa4
        charge(ctx, 61);
        s2 = addiu(s1, 8);
        v0 = a3;
        s2 = addu(s0, s2);
        v1 = v0;
        lw(t2, v0, 12);
        lw(t4, v1, 16);
        a0 = v0;
        a1 = v0;
        lw(t3, a0, 32);
        lw(t1, a1, 28);
        a2 = 0x980000;
        lw(t0, a3, 20);
        v0 = 0x980000;
        lw(v1, s2, 0);
        s0 = addiu(a2, 21888);  // &0x985580
        sw(s5, a2, 21888);  // 0x985580
        v0 = addiu(v0, 24256);  // &0x985EC0
        a3 = 48;
        sw(v1, s0, 8);  // 0x985588
        sw(t2, s0, 12);  // 0x98558C
        s1 = 0x980000;
        sw(t4, s0, 16);  // 0x985590
        s1 = addiu(s1, 21952);  // &0x9855C0
        sw(t3, s0, 20);  // 0x985594
        a0 = s1;
        sw(t1, s0, 24);  // 0x985598
        a1 = 0;
        sw(t0, s0, 36);  // 0x9855A4
        a2 = 256;
        sw(v0, s0, 44);  // 0x9855AC
        sw(a3, sp, 0x0);
        sw(s4, s0, 4);  // 0x985584
        sw(zero, s0, 28);  // 0x98559C
        sw(zero, s0, 32);  // 0x9855A0
        link(ctx, 0x51C02Cu);  // $ra first: the delay slot below depends on it
        sw(s3, s0, 40);  // 0x9855A8
        call(ctx, gen::fn_memset_00521408);
        a0 = s1;
        a1 = addiu(a0, 127);  // &0x98563F
        jal(ctx, 0x51C038u, gen::fn_SyncDCache_00503a58);
        lw(a1, s2, 0);
        a0 = s3;
        mult(v0, a1, s4);
        a1 = addu(v0, s3);
        a1 = addiu(a1, -1);
        jal(ctx, 0x51C050u, gen::fn_SyncDCache_00503a58);
        lw(a0, s6, 0);
        v1 = 0x780000;
        v0 = 16;
        t0 = 0x520000;
        a3 = s0;
        sw(v0, v1, 10988);  // 0x782AEC
        t0 = addiu(t0, -20936);  // &sceMc2SifCallback
        a1 = 16;
        a2 = sp;
        jal(ctx, 0x51C078u, gen::fn_sceDbcSendData3_0051d308);
        jal(ctx, 0x51C080u, gen::fn_SyncDmaForRead_0051ade0);
        lw(v1, v0, 8);
        v0 = 0;
        v1 = v1 ^ 0x1;
        if (v1 == 0) v0 = s4;
    } else {
        // 0x0051bf9c
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x0051c098 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x80);
    ld(s6, sp, 0x70);
    ld(s5, sp, 0x60);
    ld(s4, sp, 0x50);
    ld(s3, sp, 0x40);
    ld(s2, sp, 0x30);
    ld(s1, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x90);
}

// 0x0051C280 _sceMcCoreDeleteSocket -- 104 bytes; frame 0x40: s2 sp+0x20, ra sp+0x30, s1 sp+0x10, s0 sp+0x0
// libmc2 core: checks then deletes a DBC socket.
void _sceMcCoreDeleteSocket(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051c280
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s2, sp, 0x20);
    s2 = a0;
    sd(ra, sp, 0x30);
    sd(s1, sp, 0x10);
    link(ctx, 0x51C294u);  // $ra first: the delay slot below depends on it
    sd(s0, sp, 0x0);
    call(ctx, gen::fn__sceMcCoreCheckSocket_0051c250);
    s1 = 36;
    if (v0 != 0) {
        // 0x0051c2ac
        charge(ctx, 9);
        s0 = 0x980000;
        mult(s1, s2, s1);
        s0 = addiu(s0, 21768);  // &0x985508
        v0 = addu(s0, s1);
        link(ctx, 0x51C2BCu);  // $ra first: the delay slot below depends on it
        lw(a0, v0, 4);
        call(ctx, gen::fn_sceDbcDeleteSocket_0051c8a0);
        s1 = addu(s1, s0);
        v0 = 1;
        sw(zero, s1, 0);
    } else {
        // 0x0051c2a4
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x0051c2d0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0051E150 calloc -- 40 bytes; frame 0x10: ra sp+0x0
// newlib calloc: _calloc_r(_impure_ptr, n, size).
void calloc(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, t6{ctx, 14}, t7{ctx, 15}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051e150
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    t7 = a0;
    sd(ra, sp, 0x0);
    t6 = 0x780000;
    a2 = a1;
    lw(a0, t6, 12080);  // 0x782F30
    ld(ra, sp, 0x0);
    a1 = t7;
    sp = addiu(sp, 0x10);
    gen::fn__calloc_r_0051e178(ctx);  // tail call
}

// 0x00522F98 realloc -- 40 bytes; frame 0x10: ra sp+0x0
// newlib realloc: _realloc_r(_impure_ptr, p, size).
void realloc(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, t6{ctx, 14}, t7{ctx, 15}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00522f98
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    t7 = a0;
    sd(ra, sp, 0x0);
    t6 = 0x780000;
    a2 = a1;
    lw(a0, t6, 12080);  // 0x782F30
    ld(ra, sp, 0x0);
    a1 = t7;
    sp = addiu(sp, 0x10);
    gen::fn__realloc_r_00522fc0(ctx);  // tail call
}

// 0x00535888 sub_535888 -- 80 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Library block 0x535000: record init (sub_539818, memset, sub_539830).
void sub_535888(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00535888
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    if (s0 == 0) {
        // 0x005358c8
        charge(ctx, 4);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0053589c
    charge(ctx, 10);
    jal(ctx, 0x53589Cu, gen::fn_sub_539818_00539818);
    a0 = s0;
    a1 = 0;
    a2 = 48;
    jal(ctx, 0x5358ACu, gen::fn_memset_00521408);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_539830_00539830(ctx);  // tail call
}

// 0x005358E0 sub_5358E0 -- 412 bytes; frame 0x40: s1 sp+0x18, s2 sp+0x20, s0 sp+0x10, s3 sp+0x28, ra sp+0x30
// Library block 0x535000: record init with a memset and eight calls through function pointers.
void sub_5358E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005358e0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s1, sp, 0x18);
    s1 = a0;
    sd(s2, sp, 0x20);
    s2 = 0;
    sd(s0, sp, 0x10);
    sd(s3, sp, 0x28);
    sd(ra, sp, 0x30);
    lb(v0, s1, 2);
    lbu(a0, s1, 2);
    if (i64(v0) > 0) {
        // 0x0053590c
        charge(ctx, 1);
        v1 = addiu(s1, 20);
        for (;;) {
            // 0x00535910
            charge(ctx, 7);
            sw(zero, v1, 0);
            v1 = addiu(v1, 4);
            s2 = addiu(s2, 1);
            lb(v0, s1, 2);
            v0 = slt(s2, v0);
            lbu(a0, s1, 2);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0053592c
    charge(ctx, 4);
    v0 = sll(a0, 24);
    sw(zero, s1, 44);
    s2 = 0;
    if (i64(v0) > 0) {
        // 0x0053593c
        charge(ctx, 1);
        s3 = addiu(s1, 4);
        for (;;) {
            // 0x00535940
            charge(ctx, 33);
            lw(s0, s3, 0);
            s3 = addiu(s3, 4);
            s2 = addiu(s2, 1);
            lw(v1, s0, 0);
            lw(v0, v1, 20);
            a0 = s0;
            jalr(ctx, 0x535954u, v0.u());
            lw(v1, s0, 0);
            a0 = s0;
            lw(v0, v1, 36);
            a1 = 0;
            jalr(ctx, 0x535968u, v0.u());
            lw(v1, s0, 0);
            a2 = v0;
            a3 = sp;
            lw(v0, v1, 24);
            a0 = s0;
            a1 = 0;
            jalr(ctx, 0x535984u, v0.u());
            a1 = 0;
            lw(a0, sp, 0x0);
            link(ctx, 0x535994u);  // $ra first: the delay slot below depends on it
            lw(a2, sp, 0x4);
            call(ctx, gen::fn_memset_00521408);
            lw(v1, s0, 0);
            a0 = s0;
            a1 = 0;
            lw(v0, v1, 28);
            a2 = sp;
            jalr(ctx, 0x5359ACu, v0.u());
            lb(v0, s1, 2);
            v0 = slt(s2, v0);
            lbu(a0, s1, 2);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x005359c4
        charge(ctx, 1);
        v0 = sll(a0, 24);
    }
    // 0x005359c8
    charge(ctx, 2);
    s2 = 0;
    if (i64(v0) > 0) {
        // 0x005359d0
        charge(ctx, 2);
        s3 = addiu(s1, 12);
        lw(s0, s3, 0);
        for (;;) {
            // 0x005359d8
            charge(ctx, 32);
            s3 = addiu(s3, 4);
            s2 = addiu(s2, 1);
            lw(v1, s0, 0);
            lw(v0, v1, 20);
            a0 = s0;
            jalr(ctx, 0x5359E8u, v0.u());
            lw(v1, s0, 0);
            a0 = s0;
            lw(v0, v1, 36);
            a1 = 0;
            jalr(ctx, 0x5359FCu, v0.u());
            lw(v1, s0, 0);
            a2 = v0;
            a3 = sp;
            lw(v0, v1, 24);
            a0 = s0;
            a1 = 0;
            jalr(ctx, 0x535A18u, v0.u());
            a1 = 0;
            lw(a0, sp, 0x0);
            link(ctx, 0x535A28u);  // $ra first: the delay slot below depends on it
            lw(a2, sp, 0x4);
            call(ctx, gen::fn_memset_00521408);
            lw(a2, s0, 0);
            a0 = s0;
            a1 = 0;
            lw(v1, a2, 28);
            a2 = sp;
            jalr(ctx, 0x535A40u, v1.u());
            lb(v0, s1, 2);
            v0 = slt(s2, v0);
            if (v0 == 0) {
                break;
            }
            lw(s0, s3, 0);
            backedge(ctx);
        }
    }
    // 0x00535a58 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    v0 = 2;
    ld(s0, sp, 0x10);
    sb(v0, s1, 1);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x18);
    ld(s3, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x00535A80 sub_535A80 -- 8 bytes; leaf frame (no stack)
// Library block 0x535000 leaf: clears the byte a0+1.
void sub_535A80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4};
    // 0x00535a80
    enter(ctx, 2);  // entry check point + this block's cycles
    sb(zero, a0, 1);
}

// 0x00535DA8 sub_535DA8 -- 8 bytes; leaf frame (no stack)
// Library block 0x535000 leaf: stores a1 at a0+32.
void sub_535DA8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5};
    // 0x00535da8
    enter(ctx, 2);  // entry check point + this block's cycles
    sw(a1, a0, 32);
}

// 0x00537CF0 sub_537CF0 -- 156 bytes; leaf frame (no stack)
// Library block 0x535000: fills a format record's defaults (+2 = 1, +20 = 48000, +13 = 16, +14 = 2, +24 = 0x7FFFFFFF,
// +15 = 127 ...).
void sub_537CF0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15};
    // 0x00537cf0
    enter(ctx, 39);  // entry check point + this block's cycles
    v0 = 0x7FFF0000;
    lhu(t4, a0, 154);
    lw(t7, a0, 60);
    t3 = 1024;
    lw(t6, a0, 64);
    t2 = 1;
    lw(t5, a0, 68);
    a3 = 0xBB80;
    v1 = 2;
    a1 = 16;
    v0 = v0 | 0xFFFF;
    a2 = 127;
    t0 = 2;
    t1 = 127;
    sh(t2, a0, 2);
    sw(a3, a0, 20);
    sb(v1, a0, 14);
    sb(a1, a0, 13);
    sw(v0, a0, 24);
    sb(a2, a0, 15);
    sh(t4, a0, 152);
    sw(t0, a0, 80);
    sw(t1, a0, 84);
    sw(t3, a0, 88);
    sw(t7, a0, 92);
    sw(t6, a0, 96);
    sw(t5, a0, 100);
    sw(zero, a0, 136);
    sw(t3, a0, 16);
    sw(zero, a0, 140);
    sh(zero, a0, 28);
    sh(zero, a0, 36);
    sh(zero, a0, 38);
    sw(zero, a0, 32);
    sw(zero, a0, 40);
    sw(zero, a0, 44);
    sw(zero, a0, 48);
    sw(zero, a0, 52);
}

// 0x00538040 sub_538040 -- 8 bytes; leaf frame (no stack)
// Library block 0x535000 getter: the s16 at a0+224.
void sub_538040(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00538040
    enter(ctx, 2);  // entry check point + this block's cycles
    lh(v0, a0, 224);
}

// 0x00538048 sub_538048 -- 16 bytes; leaf frame (no stack)
// Library block 0x535000 getter: the s16 at a0+226+2*a1.
void sub_538048(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00538048
    enter(ctx, 4);  // entry check point + this block's cycles
    a1 = sll(a1, 1);
    a1 = addu(a1, a0);
    lh(v0, a1, 226);
}

// 0x00541CC8 r_lock_def_free_0 -- 32 bytes; frame 0x10: ra sp+0x0
// Runtime lock release (sub_561640).
void r_lock_def_free_0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00541cc8
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x541CD0u, gen::fn_sub_561640_00561640);
    ld(ra, sp, 0x0);
    v0 = 0;
    sp = addiu(sp, 0x10);
}

// 0x00542A88 sub_542A88 -- 140 bytes; frame 0x30: s0 sp+0x0, s2 sp+0x10, s3 sp+0x18, ra sp+0x20, s1 sp+0x8
// C++ iostream helper: width (width__CQ24_STL8ios_base) then sub_5383E8 / sub_5383F0.
void sub_542A88(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00542a88
    enter(ctx, 35);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    sd(s2, sp, 0x10);
    s2 = a0;
    sd(s3, sp, 0x18);
    sd(ra, sp, 0x20);
    sd(s1, sp, 0x8);
    lw(s1, s2, 4);
    a0 = s1;
    jal(ctx, 0x542AA8u, gen::fn_width__CQ24_STL8ios_base_00537fe8);
    a0 = s1;
    s0 = v0;
    jal(ctx, 0x542AB4u, gen::fn_sub_5383E8_005383e8);
    a0 = s1;
    s3 = v0;
    jal(ctx, 0x542AC0u, gen::fn_sub_5383F0_005383f0);
    lw(a0, s2, 52);
    lw(a2, s2, 44);
    s0 = subu(s0, a0);
    lw(a1, s2, 48);
    v1 = slt(v0, s0);
    ld(s1, sp, 0x8);
    if (v1 != 0) s0 = v0;
    a1 = addu(a1, s3);
    a0 = addu(a0, s0);
    a2 = addu(a2, s0);
    sw(a0, s2, 52);
    sw(a2, s2, 44);
    sw(a1, s2, 48);
    ld(s0, sp, 0x0);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00542C70 sub_542C70 -- 332 bytes; frame 0x40: s1 sp+0x18, s2 sp+0x20, s3 sp+0x28, s0 sp+0x10, s4 sp+0x30, ra sp+0x38
// Library block 0x540000: memset then four calls through function pointers.
void sub_542C70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00542c70
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s1, sp, 0x18);
    sd(s2, sp, 0x20);
    s2 = a0;
    sd(s3, sp, 0x28);
    s3 = 0;
    sd(s0, sp, 0x10);
    sd(s4, sp, 0x30);
    sd(ra, sp, 0x38);
    lw(v0, s2, 160);
    lb(v1, s2, 2);
    s1 = sll(v0, 1);
    lbu(a0, s2, 2);
    if (i64(v1) > 0) {
        // 0x00542ca8
        charge(ctx, 2);
        s0 = addiu(s2, 12);
        for (;;) {
            // 0x00542cb0
            charge(ctx, 23);
            lw(a0, s0, 0);
            a2 = 0x7FFF0000;
            a3 = sp;
            a1 = 0;
            lw(v1, a0, 0);
            a2 = a2 | 0xFFFF;
            lw(v0, v1, 24);
            s3 = addiu(s3, 1);
            jalr(ctx, 0x542CCCu, v0.u());
            lw(a0, s0, 0);
            lw(t0, sp, 0x4);
            a1 = 0;
            lw(a3, a0, 0);
            a2 = sp;
            v0 = slt(s1, t0);
            s0 = addiu(s0, 4);
            lw(v1, a3, 28);
            if (v0 == 0) s1 = t0;
            jalr(ctx, 0x542CF4u, v1.u());
            lb(v0, s2, 2);
            v0 = slt(s3, v0);
            lbu(a0, s2, 2);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00542d0c
    charge(ctx, 6);
    v0 = srl(s1, 31);
    v0 = addu(s1, v0);
    s4 = sra(v0, 1);
    s1 = sll(s4, 1);
    ld(s0, sp, 0x10);
    if (i64(s1) > 0) {
        // 0x00542d24
        charge(ctx, 3);
        v0 = sll(a0, 24);
        s3 = 0;
        if (i64(v0) > 0) {
            // 0x00542d30
            charge(ctx, 2);
            s0 = addiu(s2, 12);
            lw(a0, s0, 0);
            for (;;) {
                // 0x00542d38
                charge(ctx, 22);
                a3 = sp;
                a1 = 0;
                a2 = s1;
                lw(v1, a0, 0);
                lw(v0, v1, 24);
                s3 = addiu(s3, 1);
                jalr(ctx, 0x542D4Cu, v0.u());
                a1 = 0;
                lw(a0, sp, 0x0);
                a2 = s1;
                jal(ctx, 0x542D5Cu, gen::fn_memset_00521408);
                lw(a0, s0, 0);
                a1 = 1;
                a2 = sp;
                lw(v0, a0, 0);
                lw(v1, v0, 32);
                s0 = addiu(s0, 4);
                jalr(ctx, 0x542D78u, v1.u());
                lb(v0, s2, 2);
                v0 = slt(s3, v0);
                if (v0 == 0) {
                    break;
                }
                lw(a0, s0, 0);
                backedge(ctx);
            }
        }
        // 0x00542d90
        charge(ctx, 4);
        lw(v0, s2, 160);
        v0 = subu(v0, s4);
        sw(v0, s2, 160);
        ld(s0, sp, 0x10);
    }
    // 0x00542da0 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
}

}  // namespace p3fes::game

// The recompiled program's entry points fn_<name>_<addr8> are generated from game/replaced.txt (game/forwarders.cmake).
