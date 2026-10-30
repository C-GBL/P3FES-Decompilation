// The battle code, fourth pass (slice battle4; docs/ANALYSIS/21_battle.md, game/include/p3fes/game/battle4.h for the
// layouts and the battle state a co-op server would own): the battle panel modules (battle info markers, unit panel
// entries, message window, dialog, the one-more banner and their registries), the unit geometry and screen projection,
// the colour fades, the effect instances / handles / archive, the boss set-up, sound paks, AI event scripts and reach,
// the AI think step, conditions, filters, target pick and skill / item pickers of btlAICommand.c, the grid path finder,
// the navigator and voice line pickers and the victory spoils. Every function the battle replay or the Tartarus climb
// reaches (a first-call probe) whose callees are hand-written. The bodies are p3fes_handgen's (frame, spills, $ra links,
// every register, cycle charges, check points); this file names their offsets and gives each its role -- proposed
// names in brackets (ADR-0009), symbols in code are functions.json's.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/battle4.h"

namespace p3fes::recomp_gen {
void fn_H_Cdvd_ArchiveGetFile_00102100(p3fes::EEContext&);
void fn_H_Cdvd_CacheFindFile_001021c0(p3fes::EEContext&);
void fn_H_Cdvd_Destroy_00100ec0(p3fes::EEContext&);
void fn_H_Cdvd_IsFileLoaded_001016b0(p3fes::EEContext&);
void fn_H_Cdvd_ReadSync_001023a0(p3fes::EEContext&);
void fn_H_Cdvd_Request_00100d80(p3fes::EEContext&);
void fn_RpSkyRenderStateSet_004d7f60(p3fes::EEContext&);
void fn_abs_0051e0e0(p3fes::EEContext&);
void fn_acosf_0052e9e8(p3fes::EEContext&);
void fn_btlActionSetState_00299d60(p3fes::EEContext&);
void fn_btlBossSetup_002f6e00(p3fes::EEContext&);
void fn_btlCommand_CreateBattleCommandCalcTasks_002bf3f0(p3fes::EEContext&);
void fn_btlCountActiveUnits_002d4e10(p3fes::EEContext&);
void fn_btlGetEncounterId_002d5550(p3fes::EEContext&);
void fn_btlGetMeanLevel_002d4cf0(p3fes::EEContext&);
void fn_cosf_0052e6d8(p3fes::EEContext&);
void fn_datCalcChkBadStatus_00300580(p3fes::EEContext&);
void fn_datCalcClearAllEffects_00301690(p3fes::EEContext&);
void fn_datCalcDamage_00303130(p3fes::EEContext&);
void fn_datCalcGetAffinityChecked_0030b4b0(p3fes::EEContext&);
void fn_datCalcGetAffinity_00306e80(p3fes::EEContext&);
void fn_datCalcGetBadStatus_00300550(p3fes::EEContext&);
void fn_datCalcGetEffectState_00301750(p3fes::EEContext&);
void fn_datCalcGetElementBit_003080c0(p3fes::EEContext&);
void fn_datCalcGetHeldWeaponType_00308c60(p3fes::EEContext&);
void fn_datCalcGetHp_002ffd70(p3fes::EEContext&);
void fn_datCalcGetLevel_002ffcc0(p3fes::EEContext&);
void fn_datCalcGetMaxHp_002ffdf0(p3fes::EEContext&);
void fn_datCalcGetSkillElement_003082f0(p3fes::EEContext&);
void fn_datCalcGetSkillList_00308bb0(p3fes::EEContext&);
void fn_datCalcGetSkillSlotCount_00308ba0(p3fes::EEContext&);
void fn_datCalcHasSkill_003005e0(p3fes::EEContext&);
void fn_datCalcIsDead_0030b5a0(p3fes::EEContext&);
void fn_datCalcIsLowHp_0030b5e0(p3fes::EEContext&);
void fn_datCalcRand_002ffbc0(p3fes::EEContext&);
void fn_datGetFlag_0016f190(p3fes::EEContext&);
void fn_datPersonaGetByPcId_00174800(p3fes::EEContext&);
void fn_datSetFlag_0016f1f0(p3fes::EEContext&);
void fn_dds3GetProcessWorkData_0035ae10(p3fes::EEContext&);
void fn_frFontChainCountLines_003b1a90(p3fes::EEContext&);
void fn_frFontDraw_003b1360(p3fes::EEContext&);
void fn_frFontLineGetWidth_003b19d0(p3fes::EEContext&);
void fn_frFontLineSetPos_003b0d70(p3fes::EEContext&);
void fn_frFontLineSetRgba_003b0e20(p3fes::EEContext&);
void fn_kwlnTaskAddChild_00195550(p3fes::EEContext&);
void fn_kwlnTaskCreate_00194b20(p3fes::EEContext&);
void fn_kwlnTaskGetTaskByName_00195340(p3fes::EEContext&);
void fn_kwlnTaskGetWorkData_00195540(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_scrCreateTaskFromHeader_0035bb40(p3fes::EEContext&);
void fn_scrFindPrcdIdxByName_0035c090(p3fes::EEContext&);
void fn_scrSetUserData_0035c1a0(p3fes::EEContext&);
void fn_sinf_0052e878(p3fes::EEContext&);
void fn_sprintf_00523ac8(p3fes::EEContext&);
void fn_strcpy_00524270(p3fes::EEContext&);
void fn_strlen_00524388(p3fes::EEContext&);
void fn_sub_16C4F0_0016c4f0(p3fes::EEContext&);
void fn_sub_16C5F0_0016c5f0(p3fes::EEContext&);
void fn_sub_16C920_0016c920(p3fes::EEContext&);
void fn_sub_16C970_0016c970(p3fes::EEContext&);
void fn_sub_16DD60_0016dd60(p3fes::EEContext&);
void fn_sub_170670_00170670(p3fes::EEContext&);
void fn_sub_1706C0_001706c0(p3fes::EEContext&);
void fn_sub_171110_00171110(p3fes::EEContext&);
void fn_sub_174A90_00174a90(p3fes::EEContext&);
void fn_sub_175360_00175360(p3fes::EEContext&);
void fn_sub_175CA0_00175ca0(p3fes::EEContext&);
void fn_sub_1778B0_001778b0(p3fes::EEContext&);
void fn_sub_17B170_0017b170(p3fes::EEContext&);
void fn_sub_17B260_0017b260(p3fes::EEContext&);
void fn_sub_17B2E0_0017b2e0(p3fes::EEContext&);
void fn_sub_17B3D0_0017b3d0(p3fes::EEContext&);
void fn_sub_17C750_0017c750(p3fes::EEContext&);
void fn_sub_17D800_0017d800(p3fes::EEContext&);
void fn_sub_198590_00198590(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_19FD40_0019fd40(p3fes::EEContext&);
void fn_sub_19FD70_0019fd70(p3fes::EEContext&);
void fn_sub_1C0070_001c0070(p3fes::EEContext&);
void fn_sub_1FDD40_001fdd40(p3fes::EEContext&);
void fn_sub_1FDD60_001fdd60(p3fes::EEContext&);
void fn_sub_1FDEC0_001fdec0(p3fes::EEContext&);
void fn_sub_1FE430_001fe430(p3fes::EEContext&);
void fn_sub_1FE9B0_001fe9b0(p3fes::EEContext&);
void fn_sub_1FECE0_001fece0(p3fes::EEContext&);
void fn_sub_1FED00_001fed00(p3fes::EEContext&);
void fn_sub_1FED20_001fed20(p3fes::EEContext&);
void fn_sub_1FED40_001fed40(p3fes::EEContext&);
void fn_sub_1FED60_001fed60(p3fes::EEContext&);
void fn_sub_1FED80_001fed80(p3fes::EEContext&);
void fn_sub_1FEDA0_001feda0(p3fes::EEContext&);
void fn_sub_1FEDC0_001fedc0(p3fes::EEContext&);
void fn_sub_1FEDE0_001fede0(p3fes::EEContext&);
void fn_sub_1FEE00_001fee00(p3fes::EEContext&);
void fn_sub_1FEE40_001fee40(p3fes::EEContext&);
void fn_sub_1FEE80_001fee80(p3fes::EEContext&);
void fn_sub_1FF430_001ff430(p3fes::EEContext&);
void fn_sub_21C3F0_0021c3f0(p3fes::EEContext&);
void fn_sub_21CCA0_0021cca0(p3fes::EEContext&);
void fn_sub_21CCE0_0021cce0(p3fes::EEContext&);
void fn_sub_21D3B0_0021d3b0(p3fes::EEContext&);
void fn_sub_21D890_0021d890(p3fes::EEContext&);
void fn_sub_21D8E0_0021d8e0(p3fes::EEContext&);
void fn_sub_21D950_0021d950(p3fes::EEContext&);
void fn_sub_21E380_0021e380(p3fes::EEContext&);
void fn_sub_21EAC0_0021eac0(p3fes::EEContext&);
void fn_sub_21EAE0_0021eae0(p3fes::EEContext&);
void fn_sub_241910_00241910(p3fes::EEContext&);
void fn_sub_242260_00242260(p3fes::EEContext&);
void fn_sub_242320_00242320(p3fes::EEContext&);
void fn_sub_242540_00242540(p3fes::EEContext&);
void fn_sub_242840_00242840(p3fes::EEContext&);
void fn_sub_2428F0_002428f0(p3fes::EEContext&);
void fn_sub_242950_00242950(p3fes::EEContext&);
void fn_sub_242A30_00242a30(p3fes::EEContext&);
void fn_sub_242A50_00242a50(p3fes::EEContext&);
void fn_sub_242A60_00242a60(p3fes::EEContext&);
void fn_sub_242AE0_00242ae0(p3fes::EEContext&);
void fn_sub_242B80_00242b80(p3fes::EEContext&);
void fn_sub_242C40_00242c40(p3fes::EEContext&);
void fn_sub_242C60_00242c60(p3fes::EEContext&);
void fn_sub_244120_00244120(p3fes::EEContext&);
void fn_sub_244E10_00244e10(p3fes::EEContext&);
void fn_sub_2453D0_002453d0(p3fes::EEContext&);
void fn_sub_245420_00245420(p3fes::EEContext&);
void fn_sub_245910_00245910(p3fes::EEContext&);
void fn_sub_245970_00245970(p3fes::EEContext&);
void fn_sub_245A00_00245a00(p3fes::EEContext&);
void fn_sub_245BF0_00245bf0(p3fes::EEContext&);
void fn_sub_248490_00248490(p3fes::EEContext&);
void fn_sub_2484A0_002484a0(p3fes::EEContext&);
void fn_sub_248620_00248620(p3fes::EEContext&);
void fn_sub_248BB0_00248bb0(p3fes::EEContext&);
void fn_sub_248FC0_00248fc0(p3fes::EEContext&);
void fn_sub_249180_00249180(p3fes::EEContext&);
void fn_sub_2491F0_002491f0(p3fes::EEContext&);
void fn_sub_249240_00249240(p3fes::EEContext&);
void fn_sub_24A6C0_0024a6c0(p3fes::EEContext&);
void fn_sub_24A6D0_0024a6d0(p3fes::EEContext&);
void fn_sub_251050_00251050(p3fes::EEContext&);
void fn_sub_251060_00251060(p3fes::EEContext&);
void fn_sub_251A70_00251a70(p3fes::EEContext&);
void fn_sub_251F20_00251f20(p3fes::EEContext&);
void fn_sub_251F30_00251f30(p3fes::EEContext&);
void fn_sub_252060_00252060(p3fes::EEContext&);
void fn_sub_252340_00252340(p3fes::EEContext&);
void fn_sub_252E60_00252e60(p3fes::EEContext&);
void fn_sub_252E80_00252e80(p3fes::EEContext&);
void fn_sub_252E90_00252e90(p3fes::EEContext&);
void fn_sub_252EE0_00252ee0(p3fes::EEContext&);
void fn_sub_252F30_00252f30(p3fes::EEContext&);
void fn_sub_25BDF0_0025bdf0(p3fes::EEContext&);
void fn_sub_25BE00_0025be00(p3fes::EEContext&);
void fn_sub_25C110_0025c110(p3fes::EEContext&);
void fn_sub_25C190_0025c190(p3fes::EEContext&);
void fn_sub_25C1E0_0025c1e0(p3fes::EEContext&);
void fn_sub_25C9C0_0025c9c0(p3fes::EEContext&);
void fn_sub_25CD30_0025cd30(p3fes::EEContext&);
void fn_sub_25CEB0_0025ceb0(p3fes::EEContext&);
void fn_sub_25CF00_0025cf00(p3fes::EEContext&);
void fn_sub_25CF10_0025cf10(p3fes::EEContext&);
void fn_sub_25D6C0_0025d6c0(p3fes::EEContext&);
void fn_sub_25D710_0025d710(p3fes::EEContext&);
void fn_sub_25FB60_0025fb60(p3fes::EEContext&);
void fn_sub_27EC10_0027ec10(p3fes::EEContext&);
void fn_sub_27ED20_0027ed20(p3fes::EEContext&);
void fn_sub_27F7C0_0027f7c0(p3fes::EEContext&);
void fn_sub_27F930_0027f930(p3fes::EEContext&);
void fn_sub_27FFB0_0027ffb0(p3fes::EEContext&);
void fn_sub_280050_00280050(p3fes::EEContext&);
void fn_sub_280130_00280130(p3fes::EEContext&);
void fn_sub_280580_00280580(p3fes::EEContext&);
void fn_sub_2806D0_002806d0(p3fes::EEContext&);
void fn_sub_2807A0_002807a0(p3fes::EEContext&);
void fn_sub_280870_00280870(p3fes::EEContext&);
void fn_sub_2812D0_002812d0(p3fes::EEContext&);
void fn_sub_2819D0_002819d0(p3fes::EEContext&);
void fn_sub_282C60_00282c60(p3fes::EEContext&);
void fn_sub_283510_00283510(p3fes::EEContext&);
void fn_sub_283BA0_00283ba0(p3fes::EEContext&);
void fn_sub_283C70_00283c70(p3fes::EEContext&);
void fn_sub_283E40_00283e40(p3fes::EEContext&);
void fn_sub_284200_00284200(p3fes::EEContext&);
void fn_sub_284DF0_00284df0(p3fes::EEContext&);
void fn_sub_284F30_00284f30(p3fes::EEContext&);
void fn_sub_284F50_00284f50(p3fes::EEContext&);
void fn_sub_284FE0_00284fe0(p3fes::EEContext&);
void fn_sub_285D30_00285d30(p3fes::EEContext&);
void fn_sub_288950_00288950(p3fes::EEContext&);
void fn_sub_288DA0_00288da0(p3fes::EEContext&);
void fn_sub_288FE0_00288fe0(p3fes::EEContext&);
void fn_sub_289030_00289030(p3fes::EEContext&);
void fn_sub_2890A0_002890a0(p3fes::EEContext&);
void fn_sub_289860_00289860(p3fes::EEContext&);
void fn_sub_28A780_0028a780(p3fes::EEContext&);
void fn_sub_28CE50_0028ce50(p3fes::EEContext&);
void fn_sub_28D560_0028d560(p3fes::EEContext&);
void fn_sub_28E7F0_0028e7f0(p3fes::EEContext&);
void fn_sub_296320_00296320(p3fes::EEContext&);
void fn_sub_299520_00299520(p3fes::EEContext&);
void fn_sub_299800_00299800(p3fes::EEContext&);
void fn_sub_29A1D0_0029a1d0(p3fes::EEContext&);
void fn_sub_29A320_0029a320(p3fes::EEContext&);
void fn_sub_29AD20_0029ad20(p3fes::EEContext&);
void fn_sub_29EA50_0029ea50(p3fes::EEContext&);
void fn_sub_29F150_0029f150(p3fes::EEContext&);
void fn_sub_29F760_0029f760(p3fes::EEContext&);
void fn_sub_2A2170_002a2170(p3fes::EEContext&);
void fn_sub_2A3590_002a3590(p3fes::EEContext&);
void fn_sub_2A3B40_002a3b40(p3fes::EEContext&);
void fn_sub_2A4690_002a4690(p3fes::EEContext&);
void fn_sub_2ADD10_002add10(p3fes::EEContext&);
void fn_sub_2B0280_002b0280(p3fes::EEContext&);
void fn_sub_2B1020_002b1020(p3fes::EEContext&);
void fn_sub_2B4DB0_002b4db0(p3fes::EEContext&);
void fn_sub_2B4FD0_002b4fd0(p3fes::EEContext&);
void fn_sub_2B5600_002b5600(p3fes::EEContext&);
void fn_sub_2B8F90_002b8f90(p3fes::EEContext&);
void fn_sub_2B90D0_002b90d0(p3fes::EEContext&);
void fn_sub_2B9220_002b9220(p3fes::EEContext&);
void fn_sub_2B93E0_002b93e0(p3fes::EEContext&);
void fn_sub_2B96E0_002b96e0(p3fes::EEContext&);
void fn_sub_2BAA20_002baa20(p3fes::EEContext&);
void fn_sub_2BAAD0_002baad0(p3fes::EEContext&);
void fn_sub_2BAF90_002baf90(p3fes::EEContext&);
void fn_sub_2BB6F0_002bb6f0(p3fes::EEContext&);
void fn_sub_2BB7D0_002bb7d0(p3fes::EEContext&);
void fn_sub_2BBC00_002bbc00(p3fes::EEContext&);
void fn_sub_2BC420_002bc420(p3fes::EEContext&);
void fn_sub_2BC480_002bc480(p3fes::EEContext&);
void fn_sub_2BD5F0_002bd5f0(p3fes::EEContext&);
void fn_sub_2BD6F0_002bd6f0(p3fes::EEContext&);
void fn_sub_2BD780_002bd780(p3fes::EEContext&);
void fn_sub_2BD850_002bd850(p3fes::EEContext&);
void fn_sub_2BED10_002bed10(p3fes::EEContext&);
void fn_sub_2BF9B0_002bf9b0(p3fes::EEContext&);
void fn_sub_2BFCB0_002bfcb0(p3fes::EEContext&);
void fn_sub_2BFF60_002bff60(p3fes::EEContext&);
void fn_sub_2C0070_002c0070(p3fes::EEContext&);
void fn_sub_2C0880_002c0880(p3fes::EEContext&);
void fn_sub_2C09F0_002c09f0(p3fes::EEContext&);
void fn_sub_2C1080_002c1080(p3fes::EEContext&);
void fn_sub_2C1710_002c1710(p3fes::EEContext&);
void fn_sub_2C17B0_002c17b0(p3fes::EEContext&);
void fn_sub_2C1CE0_002c1ce0(p3fes::EEContext&);
void fn_sub_2C1F60_002c1f60(p3fes::EEContext&);
void fn_sub_2C22D0_002c22d0(p3fes::EEContext&);
void fn_sub_2C2B20_002c2b20(p3fes::EEContext&);
void fn_sub_2C2BE0_002c2be0(p3fes::EEContext&);
void fn_sub_2C2D00_002c2d00(p3fes::EEContext&);
void fn_sub_2C2ED0_002c2ed0(p3fes::EEContext&);
void fn_sub_2C30F0_002c30f0(p3fes::EEContext&);
void fn_sub_2C3120_002c3120(p3fes::EEContext&);
void fn_sub_2C3430_002c3430(p3fes::EEContext&);
void fn_sub_2C3770_002c3770(p3fes::EEContext&);
void fn_sub_2C48A0_002c48a0(p3fes::EEContext&);
void fn_sub_2C4C80_002c4c80(p3fes::EEContext&);
void fn_sub_2C4E50_002c4e50(p3fes::EEContext&);
void fn_sub_2C5030_002c5030(p3fes::EEContext&);
void fn_sub_2C5380_002c5380(p3fes::EEContext&);
void fn_sub_2C59D0_002c59d0(p3fes::EEContext&);
void fn_sub_2C5FC0_002c5fc0(p3fes::EEContext&);
void fn_sub_2C6A00_002c6a00(p3fes::EEContext&);
void fn_sub_2C6BA0_002c6ba0(p3fes::EEContext&);
void fn_sub_2C6E30_002c6e30(p3fes::EEContext&);
void fn_sub_2C6F50_002c6f50(p3fes::EEContext&);
void fn_sub_2C70D0_002c70d0(p3fes::EEContext&);
void fn_sub_2C7250_002c7250(p3fes::EEContext&);
void fn_sub_2C7280_002c7280(p3fes::EEContext&);
void fn_sub_2D1570_002d1570(p3fes::EEContext&);
void fn_sub_2D15A0_002d15a0(p3fes::EEContext&);
void fn_sub_2D1A70_002d1a70(p3fes::EEContext&);
void fn_sub_2D1E70_002d1e70(p3fes::EEContext&);
void fn_sub_2D1ED0_002d1ed0(p3fes::EEContext&);
void fn_sub_2D1F30_002d1f30(p3fes::EEContext&);
void fn_sub_2D1FD0_002d1fd0(p3fes::EEContext&);
void fn_sub_2D20A0_002d20a0(p3fes::EEContext&);
void fn_sub_2D2470_002d2470(p3fes::EEContext&);
void fn_sub_2D25C0_002d25c0(p3fes::EEContext&);
void fn_sub_2D2990_002d2990(p3fes::EEContext&);
void fn_sub_2D2A00_002d2a00(p3fes::EEContext&);
void fn_sub_2D2C10_002d2c10(p3fes::EEContext&);
void fn_sub_2D2EE0_002d2ee0(p3fes::EEContext&);
void fn_sub_2D2F50_002d2f50(p3fes::EEContext&);
void fn_sub_2D32B0_002d32b0(p3fes::EEContext&);
void fn_sub_2D41C0_002d41c0(p3fes::EEContext&);
void fn_sub_2D4810_002d4810(p3fes::EEContext&);
void fn_sub_2D48C0_002d48c0(p3fes::EEContext&);
void fn_sub_2D5DC0_002d5dc0(p3fes::EEContext&);
void fn_sub_2D7560_002d7560(p3fes::EEContext&);
void fn_sub_2D7E20_002d7e20(p3fes::EEContext&);
void fn_sub_2D7FB0_002d7fb0(p3fes::EEContext&);
void fn_sub_2D8390_002d8390(p3fes::EEContext&);
void fn_sub_2D9BE0_002d9be0(p3fes::EEContext&);
void fn_sub_2D9D70_002d9d70(p3fes::EEContext&);
void fn_sub_2DC130_002dc130(p3fes::EEContext&);
void fn_sub_2DC5E0_002dc5e0(p3fes::EEContext&);
void fn_sub_2DD100_002dd100(p3fes::EEContext&);
void fn_sub_2DD270_002dd270(p3fes::EEContext&);
void fn_sub_2DD690_002dd690(p3fes::EEContext&);
void fn_sub_2DD8E0_002dd8e0(p3fes::EEContext&);
void fn_sub_2DD960_002dd960(p3fes::EEContext&);
void fn_sub_2E0620_002e0620(p3fes::EEContext&);
void fn_sub_2E0F70_002e0f70(p3fes::EEContext&);
void fn_sub_2E12D0_002e12d0(p3fes::EEContext&);
void fn_sub_2E1BF0_002e1bf0(p3fes::EEContext&);
void fn_sub_2E2410_002e2410(p3fes::EEContext&);
void fn_sub_2E2680_002e2680(p3fes::EEContext&);
void fn_sub_2E2BE0_002e2be0(p3fes::EEContext&);
void fn_sub_2E3120_002e3120(p3fes::EEContext&);
void fn_sub_2E32A0_002e32a0(p3fes::EEContext&);
void fn_sub_2E3350_002e3350(p3fes::EEContext&);
void fn_sub_2E35D0_002e35d0(p3fes::EEContext&);
void fn_sub_2E36F0_002e36f0(p3fes::EEContext&);
void fn_sub_2E37E0_002e37e0(p3fes::EEContext&);
void fn_sub_2E3C80_002e3c80(p3fes::EEContext&);
void fn_sub_2E4290_002e4290(p3fes::EEContext&);
void fn_sub_2E42E0_002e42e0(p3fes::EEContext&);
void fn_sub_2E4330_002e4330(p3fes::EEContext&);
void fn_sub_2E4430_002e4430(p3fes::EEContext&);
void fn_sub_2F9710_002f9710(p3fes::EEContext&);
void fn_sub_2FC5D0_002fc5d0(p3fes::EEContext&);
void fn_sub_2FD2E0_002fd2e0(p3fes::EEContext&);
void fn_sub_2FD500_002fd500(p3fes::EEContext&);
void fn_sub_2FD820_002fd820(p3fes::EEContext&);
void fn_sub_2FD8A0_002fd8a0(p3fes::EEContext&);
void fn_sub_2FE0B0_002fe0b0(p3fes::EEContext&);
void fn_sub_2FE780_002fe780(p3fes::EEContext&);
void fn_sub_300E90_00300e90(p3fes::EEContext&);
void fn_sub_301870_00301870(p3fes::EEContext&);
void fn_sub_301CA0_00301ca0(p3fes::EEContext&);
void fn_sub_3086F0_003086f0(p3fes::EEContext&);
void fn_sub_30BC20_0030bc20(p3fes::EEContext&);
void fn_sub_30BC50_0030bc50(p3fes::EEContext&);
void fn_sub_30BDE0_0030bde0(p3fes::EEContext&);
void fn_sub_316910_00316910(p3fes::EEContext&);
void fn_sub_317450_00317450(p3fes::EEContext&);
void fn_sub_3174E0_003174e0(p3fes::EEContext&);
void fn_sub_318B60_00318b60(p3fes::EEContext&);
void fn_sub_318ED0_00318ed0(p3fes::EEContext&);
void fn_sub_31D530_0031d530(p3fes::EEContext&);
void fn_sub_357FD0_00357fd0(p3fes::EEContext&);
void fn_sub_3A4220_003a4220(p3fes::EEContext&);
void fn_sub_3B0170_003b0170(p3fes::EEContext&);
void fn_sub_3B2C60_003b2c60(p3fes::EEContext&);
void fn_sub_4BE1E0_004be1e0(p3fes::EEContext&);
void fn_sub_4C31B0_004c31b0(p3fes::EEContext&);
void fn_sub_4C6AC0_004c6ac0(p3fes::EEContext&);
void fn_sub_4C6AF0_004c6af0(p3fes::EEContext&);
void fn_sub_4C6B20_004c6b20(p3fes::EEContext&);
void fn_sub_4C6BE0_004c6be0(p3fes::EEContext&);
void fn_sub_4C6C60_004c6c60(p3fes::EEContext&);
void fn_sub_4CB2F0_004cb2f0(p3fes::EEContext&);
void fn_sub_4E3630_004e3630(p3fes::EEContext&);
void fn_tanf_0052e930(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace b3;  // the record offsets and $gp slots of battle3.h
using namespace b4;  // this slice's additions (battle4.h)

// 0x00241910 sub_241910 -- 2380 bytes; frame 0x90: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [biDrawMarkers] Draw of the battle info markers (bi_main.c, work *$gp 0x7CE31C, 16 slots of 3,920 bytes): RW render
// states (z test / write off, no culling), then for every live slot (flag 1, not 8) with a kind set (flag 0x10) the
// sprite quads of its kind (0 / 1 / 2 / 3: textures 10/11, 18/19, 28..30, 34; flag 4 adds the two 64-word under-quads
// at +272 / +528), sub_2BF9B0, then the 5-quad digit strips +800 / +2096 of slots with flag 0x100 / 0x200 (texture
// 46). Quads go through the Im2D slot 0x96009C (two triangles each).
void sub_241910(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00241910
    enter(ctx, 13);  // entry check point + this block's cycles
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
    lw(v0, gp, kGpBiWork);  // the battle info work (bi_main.c; 16 slots of 3,920 bytes) 0x7CE31C
    if (v0 == 0) {
        // 0x00241944
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6032);  // "bi_main.c"
        a1 = 138;
        jal(ctx, 0x241950u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00241958
    charge(ctx, 30);
    lw(s7, gp, kGpBiWork);  // the battle info work (bi_main.c; 16 slots of 3,920 bytes) 0x7CE31C
    a0 = 1;
    jal(ctx, 0x241960u, gen::fn_sub_21C3F0_0021c3f0);
    s4 = v0;
    s1 = 0x960000;
    s1 = addiu(s1, 144);  // &pfn_RwRenderStateSet
    a0 = 9;
    a1 = 2;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x241980u, v0.u());
    a0 = 20;
    a1 = 2;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x241994u, v0.u());
    a0 = 8;
    a1 = 0;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x2419A8u, v0.u());
    a0 = 6;
    a1 = 0;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x2419BCu, v0.u());
    s5 = 0;
    for (;;) {
        // 0x0024202c
        charge(ctx, 3);
        v0 = slti(s5, 16);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002419d0
        charge(ctx, 8);
        v0 = 3920;
        mult(v0, s5, v0);
        s0 = addu(s7, v0);
        lw(v1, s0, 0);
        v0 = nor(v1, 0);
        v0 = v0 & 0x1;
        if (v0 == 0) {
            // 0x002419f0
            charge(ctx, 3);
            v0 = v1 & 0x8;
            if (v0 == 0) {
                // 0x002419fc
                charge(ctx, 3);
                v0 = v1 & 0x10;
                if (v0 != 0) {
                    // 0x00241a08
                    charge(ctx, 4);
                    lw(v1, s0, 4);
                    v0 = 2;
                    if (v1 == v0) {
                        // 0x00241e58
                        charge(ctx, 116);
                        s3 = addiu(s0, 16);
                        a0 = s4;
                        a1 = 29;
                        jal(ctx, 0x241E64u, gen::fn_sub_21CCA0_0021cca0);
                        s2 = 0x960000;
                        s2 = addiu(s2, 144);  // &pfn_RwRenderStateSet
                        a0 = v0;
                        jal(ctx, 0x241E78u, gen::fn_sub_21CCE0_0021cce0);
                        a0 = 1;
                        a1 = v0;
                        lw(v0, s2, 0);  // pfn_RwRenderStateSet
                        jalr(ctx, 0x241E8Cu, v0.u());
                        a0 = 3;
                        v0 = 0x70000;
                        a1 = v0 | 0x17FB;
                        jal(ctx, 0x241EA0u, gen::fn_RpSkyRenderStateSet_004d7f60);
                        a0 = 2;
                        a1 = 68;
                        jal(ctx, 0x241EB0u, gen::fn_RpSkyRenderStateSet_004d7f60);
                        s0 = 0x960000;
                        s0 = addiu(s0, 156);  // &0x96009C
                        a0 = addiu(s3, 256);
                        a1 = 4;
                        a2 = 0;
                        a3 = 1;
                        t0 = 2;
                        lw(v0, s0, 0);  // 0x96009C
                        jalr(ctx, 0x241ED8u, v0.u());
                        a0 = addiu(s3, 256);
                        a1 = 4;
                        a2 = 0;
                        a3 = 2;
                        t0 = 3;
                        lw(v0, s0, 0);  // 0x96009C
                        jalr(ctx, 0x241EF8u, v0.u());
                        a0 = s4;
                        a1 = 28;
                        jal(ctx, 0x241F08u, gen::fn_sub_21CCA0_0021cca0);
                        a0 = v0;
                        jal(ctx, 0x241F14u, gen::fn_sub_21CCE0_0021cce0);
                        a0 = 1;
                        a1 = v0;
                        lw(v0, s2, 0);  // pfn_RwRenderStateSet
                        jalr(ctx, 0x241F28u, v0.u());
                        a0 = 3;
                        v0 = 0x70000;
                        a1 = v0 | 0x17FB;
                        jal(ctx, 0x241F3Cu, gen::fn_RpSkyRenderStateSet_004d7f60);
                        a0 = 2;
                        a1 = 68;
                        jal(ctx, 0x241F4Cu, gen::fn_RpSkyRenderStateSet_004d7f60);
                        a0 = addiu(s3, 512);
                        a1 = 4;
                        a2 = 0;
                        a3 = 1;
                        t0 = 2;
                        lw(v0, s0, 0);  // 0x96009C
                        jalr(ctx, 0x241F6Cu, v0.u());
                        a0 = addiu(s3, 512);
                        a1 = 4;
                        a2 = 0;
                        a3 = 2;
                        t0 = 3;
                        lw(v0, s0, 0);  // 0x96009C
                        jalr(ctx, 0x241F8Cu, v0.u());
                        a0 = s4;
                        a1 = 30;
                        jal(ctx, 0x241F9Cu, gen::fn_sub_21CCA0_0021cca0);
                        a0 = v0;
                        jal(ctx, 0x241FA8u, gen::fn_sub_21CCE0_0021cce0);
                        a0 = 1;
                        a1 = v0;
                        lw(v0, s2, 0);  // pfn_RwRenderStateSet
                        jalr(ctx, 0x241FBCu, v0.u());
                        a0 = 3;
                        v0 = 0x70000;
                        a1 = v0 | 0x17FB;
                        jal(ctx, 0x241FD0u, gen::fn_RpSkyRenderStateSet_004d7f60);
                        a0 = 2;
                        a1 = 68;
                        jal(ctx, 0x241FE0u, gen::fn_RpSkyRenderStateSet_004d7f60);
                        a0 = s3;
                        a1 = 4;
                        a2 = 0;
                        a3 = 1;
                        t0 = 2;
                        lw(v0, s0, 0);  // 0x96009C
                        jalr(ctx, 0x242000u, v0.u());
                        a0 = s3;
                        a1 = 4;
                        a2 = 0;
                        a3 = 2;
                        t0 = 3;
                        lw(v0, s0, 0);  // 0x96009C
                        jalr(ctx, 0x242020u, v0.u());
                    } else {
                        // 0x00241a18
                        charge(ctx, 3);
                        v0 = 3;
                        if (v1 == v0) {
                            // 0x00241db0
                            charge(ctx, 42);
                            s2 = addiu(s0, 16);
                            a0 = s4;
                            a1 = 34;
                            jal(ctx, 0x241DBCu, gen::fn_sub_21CCA0_0021cca0);
                            a0 = v0;
                            jal(ctx, 0x241DC8u, gen::fn_sub_21CCE0_0021cce0);
                            a0 = 1;
                            a1 = v0;
                            lw(v0, s1, 0);
                            jalr(ctx, 0x241DDCu, v0.u());
                            a0 = 3;
                            v0 = 0x70000;
                            a1 = v0 | 0x17FB;
                            jal(ctx, 0x241DF0u, gen::fn_RpSkyRenderStateSet_004d7f60);
                            a0 = 2;
                            a1 = 68;
                            jal(ctx, 0x241E00u, gen::fn_RpSkyRenderStateSet_004d7f60);
                            s0 = 0x960000;
                            s0 = addiu(s0, 156);  // &0x96009C
                            a0 = s2;
                            a1 = 4;
                            a2 = 0;
                            a3 = 1;
                            t0 = 2;
                            lw(v0, s0, 0);  // 0x96009C
                            jalr(ctx, 0x241E28u, v0.u());
                            a0 = s2;
                            a1 = 4;
                            a2 = 0;
                            a3 = 2;
                            t0 = 3;
                            lw(v0, s0, 0);  // 0x96009C
                            jalr(ctx, 0x241E48u, v0.u());
                        } else {
                            // 0x00241a24
                            charge(ctx, 3);
                            v0 = 1;
                            if (v1 == v0) {
                                // 0x00241bf8
                                charge(ctx, 17);
                                s2 = addiu(s0, 16);
                                a0 = s4;
                                a1 = 18;
                                jal(ctx, 0x241C04u, gen::fn_sub_21CCA0_0021cca0);
                                a0 = v0;
                                jal(ctx, 0x241C10u, gen::fn_sub_21CCE0_0021cce0);
                                a0 = 1;
                                a1 = v0;
                                lw(v0, s1, 0);
                                jalr(ctx, 0x241C24u, v0.u());
                                lw(v0, s0, 0);
                                v0 = v0 & 0x4;
                                if (v0 != 0) {
                                    // 0x00241c3c
                                    charge(ctx, 52);
                                    a0 = 3;
                                    v0 = 0x70000;
                                    a1 = v0 | 0x17FB;
                                    jal(ctx, 0x241C48u, gen::fn_RpSkyRenderStateSet_004d7f60);
                                    a0 = 2;
                                    a1 = 68;
                                    jal(ctx, 0x241C58u, gen::fn_RpSkyRenderStateSet_004d7f60);
                                    s0 = 0x960000;
                                    s0 = addiu(s0, 156);  // &0x96009C
                                    a0 = addiu(s2, 256);
                                    a1 = 4;
                                    a2 = 0;
                                    a3 = 1;
                                    t0 = 2;
                                    lw(v0, s0, 0);  // 0x96009C
                                    jalr(ctx, 0x241C80u, v0.u());
                                    a0 = addiu(s2, 256);
                                    a1 = 4;
                                    a2 = 0;
                                    a3 = 2;
                                    t0 = 3;
                                    lw(v0, s0, 0);  // 0x96009C
                                    jalr(ctx, 0x241CA0u, v0.u());
                                    a0 = 3;
                                    v0 = 0x70000;
                                    a1 = v0 | 0x1801;
                                    jal(ctx, 0x241CB4u, gen::fn_RpSkyRenderStateSet_004d7f60);
                                    a0 = 2;
                                    a1 = 72;
                                    jal(ctx, 0x241CC4u, gen::fn_RpSkyRenderStateSet_004d7f60);
                                    a0 = addiu(s2, 512);
                                    a1 = 4;
                                    a2 = 0;
                                    a3 = 1;
                                    t0 = 2;
                                    lw(v0, s0, 0);  // 0x96009C
                                    jalr(ctx, 0x241CE4u, v0.u());
                                    a0 = addiu(s2, 512);
                                    a1 = 4;
                                    a2 = 0;
                                    a3 = 2;
                                    t0 = 3;
                                    lw(v0, s0, 0);  // 0x96009C
                                    jalr(ctx, 0x241D04u, v0.u());
                                }
                                // 0x00241d0c
                                charge(ctx, 41);
                                a0 = s4;
                                a1 = 19;
                                jal(ctx, 0x241D14u, gen::fn_sub_21CCA0_0021cca0);
                                a0 = v0;
                                jal(ctx, 0x241D20u, gen::fn_sub_21CCE0_0021cce0);
                                a0 = 1;
                                a1 = v0;
                                lw(v0, s1, 0);
                                jalr(ctx, 0x241D34u, v0.u());
                                a0 = 3;
                                v0 = 0x70000;
                                a1 = v0 | 0x17FB;
                                jal(ctx, 0x241D48u, gen::fn_RpSkyRenderStateSet_004d7f60);
                                a0 = 2;
                                a1 = 68;
                                jal(ctx, 0x241D58u, gen::fn_RpSkyRenderStateSet_004d7f60);
                                s0 = 0x960000;
                                s0 = addiu(s0, 156);  // &0x96009C
                                a0 = s2;
                                a1 = 4;
                                a2 = 0;
                                a3 = 1;
                                t0 = 2;
                                lw(v0, s0, 0);  // 0x96009C
                                jalr(ctx, 0x241D80u, v0.u());
                                a0 = s2;
                                a1 = 4;
                                a2 = 0;
                                a3 = 2;
                                t0 = 3;
                                lw(v0, s0, 0);  // 0x96009C
                                jalr(ctx, 0x241DA0u, v0.u());
                            } else {
                                // 0x00241a30
                                charge(ctx, 2);
                                if (v1 == 0) {
                                    // 0x00241a40
                                    charge(ctx, 17);
                                    s2 = addiu(s0, 16);
                                    a0 = s4;
                                    a1 = 10;
                                    jal(ctx, 0x241A4Cu, gen::fn_sub_21CCA0_0021cca0);
                                    a0 = v0;
                                    jal(ctx, 0x241A58u, gen::fn_sub_21CCE0_0021cce0);
                                    a0 = 1;
                                    a1 = v0;
                                    lw(v0, s1, 0);
                                    jalr(ctx, 0x241A6Cu, v0.u());
                                    lw(v0, s0, 0);
                                    v0 = v0 & 0x4;
                                    if (v0 != 0) {
                                        // 0x00241a84
                                        charge(ctx, 52);
                                        a0 = 3;
                                        v0 = 0x70000;
                                        a1 = v0 | 0x17FB;
                                        jal(ctx, 0x241A90u, gen::fn_RpSkyRenderStateSet_004d7f60);
                                        a0 = 2;
                                        a1 = 68;
                                        jal(ctx, 0x241AA0u, gen::fn_RpSkyRenderStateSet_004d7f60);
                                        s0 = 0x960000;
                                        s0 = addiu(s0, 156);  // &0x96009C
                                        a0 = addiu(s2, 256);
                                        a1 = 4;
                                        a2 = 0;
                                        a3 = 1;
                                        t0 = 2;
                                        lw(v0, s0, 0);  // 0x96009C
                                        jalr(ctx, 0x241AC8u, v0.u());
                                        a0 = addiu(s2, 256);
                                        a1 = 4;
                                        a2 = 0;
                                        a3 = 2;
                                        t0 = 3;
                                        lw(v0, s0, 0);  // 0x96009C
                                        jalr(ctx, 0x241AE8u, v0.u());
                                        a0 = 3;
                                        v0 = 0x70000;
                                        a1 = v0 | 0x1801;
                                        jal(ctx, 0x241AFCu, gen::fn_RpSkyRenderStateSet_004d7f60);
                                        a0 = 2;
                                        a1 = 72;
                                        jal(ctx, 0x241B0Cu, gen::fn_RpSkyRenderStateSet_004d7f60);
                                        a0 = addiu(s2, 512);
                                        a1 = 4;
                                        a2 = 0;
                                        a3 = 1;
                                        t0 = 2;
                                        lw(v0, s0, 0);  // 0x96009C
                                        jalr(ctx, 0x241B2Cu, v0.u());
                                        a0 = addiu(s2, 512);
                                        a1 = 4;
                                        a2 = 0;
                                        a3 = 2;
                                        t0 = 3;
                                        lw(v0, s0, 0);  // 0x96009C
                                        jalr(ctx, 0x241B4Cu, v0.u());
                                    }
                                    // 0x00241b54
                                    charge(ctx, 41);
                                    a0 = s4;
                                    a1 = 11;
                                    jal(ctx, 0x241B5Cu, gen::fn_sub_21CCA0_0021cca0);
                                    a0 = v0;
                                    jal(ctx, 0x241B68u, gen::fn_sub_21CCE0_0021cce0);
                                    a0 = 1;
                                    a1 = v0;
                                    lw(v0, s1, 0);
                                    jalr(ctx, 0x241B7Cu, v0.u());
                                    a0 = 3;
                                    v0 = 0x70000;
                                    a1 = v0 | 0x17FB;
                                    jal(ctx, 0x241B90u, gen::fn_RpSkyRenderStateSet_004d7f60);
                                    a0 = 2;
                                    a1 = 68;
                                    jal(ctx, 0x241BA0u, gen::fn_RpSkyRenderStateSet_004d7f60);
                                    s0 = 0x960000;
                                    s0 = addiu(s0, 156);  // &0x96009C
                                    a0 = s2;
                                    a1 = 4;
                                    a2 = 0;
                                    a3 = 1;
                                    t0 = 2;
                                    lw(v0, s0, 0);  // 0x96009C
                                    jalr(ctx, 0x241BC8u, v0.u());
                                    a0 = s2;
                                    a1 = 4;
                                    a2 = 0;
                                    a3 = 2;
                                    t0 = 3;
                                    lw(v0, s0, 0);  // 0x96009C
                                    jalr(ctx, 0x241BE8u, v0.u());
                                } else {
                                    // 0x00241a38
                                    charge(ctx, 2);
                                }
                            }
                        }
                    }
                }
            }
        }
        // 0x00242028
        charge(ctx, 1);
        s5 = addiu(s5, 1);
    }
    // 0x00242038
    charge(ctx, 5);
    jal(ctx, 0x242038u, gen::fn_sub_2BF9B0_002bf9b0);
    s2 = 0;
    for (;;) {
        // 0x00242220
        charge(ctx, 3);
        v1 = slti(s2, 16);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0024204c
        charge(ctx, 8);
        v1 = 3920;
        mult(v1, s2, v1);
        s0 = addu(s7, v1);
        lw(a0, s0, 0);
        v1 = nor(a0, 0);
        v1 = v1 & 0x1;
        if (v1 == 0) {
            // 0x0024206c
            charge(ctx, 3);
            v1 = a0 & 0x8;
            if (v1 == 0) {
                // 0x00242078
                charge(ctx, 3);
                v1 = a0 & 0x100;
                if (v1 != 0) {
                    // 0x00242084
                    charge(ctx, 24);
                    a0 = s4;
                    a1 = 46;
                    jal(ctx, 0x24208Cu, gen::fn_sub_21CCA0_0021cca0);
                    a0 = v0;
                    jal(ctx, 0x242098u, gen::fn_sub_21CCE0_0021cce0);
                    a0 = 1;
                    a1 = v0;
                    lw(v0, s1, 0);
                    jalr(ctx, 0x2420ACu, v0.u());
                    a0 = 3;
                    v0 = 0x70000;
                    a1 = v0 | 0x17FB;
                    jal(ctx, 0x2420C0u, gen::fn_RpSkyRenderStateSet_004d7f60);
                    a0 = 2;
                    a1 = 68;
                    jal(ctx, 0x2420D0u, gen::fn_RpSkyRenderStateSet_004d7f60);
                    s5 = 0;
                    for (;;) {
                        // 0x0024213c
                        charge(ctx, 3);
                        v1 = slti(s5, 5);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x002420e4
                        charge(ctx, 22);
                        v0 = sll(s5, 8);
                        v0 = addu(s0, v0);
                        s3 = addiu(v0, 800);
                        s6 = 0x960000;
                        s6 = addiu(s6, 156);  // &0x96009C
                        a0 = s3;
                        a1 = 4;
                        a2 = 0;
                        a3 = 1;
                        t0 = 2;
                        lw(v0, s6, 0);  // 0x96009C
                        jalr(ctx, 0x242110u, v0.u());
                        a0 = s3;
                        a1 = 4;
                        a2 = 0;
                        a3 = 2;
                        t0 = 3;
                        lw(v0, s6, 0);  // 0x96009C
                        jalr(ctx, 0x242130u, v0.u());
                        s5 = addiu(s5, 1);
                    }
                }
                // 0x00242148
                charge(ctx, 4);
                lw(v1, s0, 0);
                v1 = v1 & 0x200;
                if (v1 != 0) {
                    // 0x00242158
                    charge(ctx, 24);
                    a0 = s4;
                    a1 = 46;
                    jal(ctx, 0x242160u, gen::fn_sub_21CCA0_0021cca0);
                    a0 = v0;
                    jal(ctx, 0x24216Cu, gen::fn_sub_21CCE0_0021cce0);
                    a0 = 1;
                    a1 = v0;
                    lw(v0, s1, 0);
                    jalr(ctx, 0x242180u, v0.u());
                    a0 = 3;
                    v0 = 0x70000;
                    a1 = v0 | 0x17FB;
                    jal(ctx, 0x242194u, gen::fn_RpSkyRenderStateSet_004d7f60);
                    a0 = 2;
                    a1 = 68;
                    jal(ctx, 0x2421A4u, gen::fn_RpSkyRenderStateSet_004d7f60);
                    s3 = 0;
                    for (;;) {
                        // 0x00242210
                        charge(ctx, 3);
                        v1 = slti(s3, 5);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x002421b8
                        charge(ctx, 22);
                        v0 = sll(s3, 8);
                        v0 = addu(s0, v0);
                        s5 = addiu(v0, 2096);
                        s6 = 0x960000;
                        s6 = addiu(s6, 156);  // &0x96009C
                        a0 = s5;
                        a1 = 4;
                        a2 = 0;
                        a3 = 1;
                        t0 = 2;
                        lw(v0, s6, 0);  // 0x96009C
                        jalr(ctx, 0x2421E4u, v0.u());
                        a0 = s5;
                        a1 = 4;
                        a2 = 0;
                        a3 = 2;
                        t0 = 3;
                        lw(v0, s6, 0);  // 0x96009C
                        jalr(ctx, 0x242204u, v0.u());
                        s3 = addiu(s3, 1);
                    }
                }
            }
        }
        // 0x0024221c
        charge(ctx, 1);
        s2 = addiu(s2, 1);
    }
    // 0x0024222c
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

// 0x00242260 sub_242260 -- 180 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [biAllocSlot] Allocates a free battle info slot (first of the 16 without flag 1; K_Assert line 1411 when none),
// sets its flags to 1 and returns it.
void sub_242260(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00242260
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBiWork);  // the battle info work (bi_main.c; 16 slots of 3,920 bytes) 0x7CE31C
    if (v0 == 0) {
        // 0x00242278
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6032);  // "bi_main.c"
        a1 = 138;
        jal(ctx, 0x242284u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024228c
    charge(ctx, 5);
    lw(a0, gp, kGpBiWork);  // the battle info work (bi_main.c; 16 slots of 3,920 bytes) 0x7CE31C
    a1 = 0;
    v1 = 3920;
    for (;;) {
        // 0x002422c0
        charge(ctx, 3);
        v0 = slti(a1, 16);
        if (v0 != 0) {
            backedge(ctx);
            // 0x002422a0
            charge(ctx, 7);
            mult(v0, a1, v1);
            s0 = addu(a0, v0);
            lw(v0, s0, 0);
            v0 = nor(v0, 0);
            v0 = v0 & 0x1;
            if (v0 == 0) {
                // 0x002422bc
                charge(ctx, 1);
                a1 = addiu(a1, 1);
                continue;
            }
        }
        break;
    }
    // 0x002422cc
    charge(ctx, 3);
    v0 = slti(a1, 16);
    if (v0 == 0) {
        // 0x002422d8
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6032);  // "bi_main.c"
        a1 = 1411;
        jal(ctx, 0x2422E4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002422ec (the shared epilogue, written out on this path)
    charge(ctx, 10);
    sw(zero, s0, 0);
    v0 = 0;
    v0 = v0 | 0x1;
    sw(v0, s0, 0);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00242320 sub_242320 -- 536 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [biSetSlotKind] Sets a battle info slot's kind (a1 0..3) and builds its quads from the panel texture set
// (sub_21C3F0(1)): kind 0 textures 11 / 10 x2, 1 textures 19 / 18 x2, 2 textures 30 / 29 / 28, 3 texture 34; flag
// 0x10.
// Arguments: a0 slot, a1 kind.
void sub_242320(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00242320
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    a0 = 1;
    jal(ctx, 0x242348u, gen::fn_sub_21C3F0_0021c3f0);
    s2 = v0;
    jal(ctx, 0x242354u, gen::fn_sub_198590_00198590);
    v1 = 2;
    if (s0 == v1) {
        // 0x002424a0
        charge(ctx, 25);
        s3 = addiu(s1, 16);
        a0 = s2;
        a1 = 30;
        jal(ctx, 0x2424ACu, gen::fn_sub_21CCA0_0021cca0);
        a0 = s3;
        a1 = v0;
        jal(ctx, 0x2424BCu, gen::fn_sub_21D3B0_0021d3b0);
        a0 = s2;
        a1 = 29;
        jal(ctx, 0x2424CCu, gen::fn_sub_21CCA0_0021cca0);
        a0 = addiu(s3, 256);
        a1 = v0;
        jal(ctx, 0x2424DCu, gen::fn_sub_21D3B0_0021d3b0);
        a0 = s2;
        a1 = 28;
        jal(ctx, 0x2424ECu, gen::fn_sub_21CCA0_0021cca0);
        a0 = addiu(s3, 512);
        a1 = v0;
        jal(ctx, 0x2424FCu, gen::fn_sub_21D3B0_0021d3b0);
    } else {
        // 0x00242368
        charge(ctx, 3);
        v1 = 3;
        if (s0 == v1) {
            // 0x00242478
            charge(ctx, 10);
            a0 = s2;
            a1 = 34;
            jal(ctx, 0x242480u, gen::fn_sub_21CCA0_0021cca0);
            a0 = addiu(s1, 16);
            a1 = v0;
            jal(ctx, 0x242490u, gen::fn_sub_21D3B0_0021d3b0);
        } else {
            // 0x00242374
            charge(ctx, 3);
            v1 = 1;
            if (s0 == v1) {
                // 0x00242404
                charge(ctx, 17);
                s4 = addiu(s1, 16);
                a0 = s2;
                a1 = 19;
                jal(ctx, 0x242410u, gen::fn_sub_21CCA0_0021cca0);
                a0 = s4;
                a1 = v0;
                jal(ctx, 0x242420u, gen::fn_sub_21D3B0_0021d3b0);
                a0 = s2;
                a1 = 18;
                jal(ctx, 0x242430u, gen::fn_sub_21CCA0_0021cca0);
                s3 = v0;
                s2 = 0;
                for (;;) {
                    // 0x00242464
                    charge(ctx, 3);
                    v1 = slti(s2, 2);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00242448
                    charge(ctx, 7);
                    v0 = sll(s2, 8);
                    v0 = addu(s4, v0);
                    a0 = addiu(v0, 256);
                    a1 = s3;
                    jal(ctx, 0x242458u, gen::fn_sub_21D3B0_0021d3b0);
                    s2 = addiu(s2, 1);
                }
                // 0x00242470
                charge(ctx, 2);
            } else {
                // 0x00242380
                charge(ctx, 2);
                if (s0 == 0) {
                    // 0x00242390
                    charge(ctx, 17);
                    s4 = addiu(s1, 16);
                    a0 = s2;
                    a1 = 11;
                    jal(ctx, 0x24239Cu, gen::fn_sub_21CCA0_0021cca0);
                    a0 = s4;
                    a1 = v0;
                    jal(ctx, 0x2423ACu, gen::fn_sub_21D3B0_0021d3b0);
                    a0 = s2;
                    a1 = 10;
                    jal(ctx, 0x2423BCu, gen::fn_sub_21CCA0_0021cca0);
                    s2 = v0;
                    s3 = 0;
                    for (;;) {
                        // 0x002423f0
                        charge(ctx, 3);
                        v1 = slti(s3, 2);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x002423d4
                        charge(ctx, 7);
                        v0 = sll(s3, 8);
                        v0 = addu(s4, v0);
                        a0 = addiu(v0, 256);
                        a1 = s2;
                        jal(ctx, 0x2423E4u, gen::fn_sub_21D3B0_0021d3b0);
                        s3 = addiu(s3, 1);
                    }
                    // 0x002423fc
                    charge(ctx, 2);
                } else {
                    // 0x00242388
                    charge(ctx, 2);
                }
            }
        }
    }
    // 0x00242504 (the shared epilogue, written out on this path)
    charge(ctx, 13);
    sw(s0, s1, bi::kKind);
    lw(v1, s1, bi::kFlags);
    v1 = v1 | 0x10;
    sw(v1, s1, bi::kFlags);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00242540 sub_242540 -- 184 bytes; frame 0x40: ra sp+0x10, s0 sp+0x0 (sq)
// [biResetSlotDigits] Resets a battle info slot's two digit strips (+3392 / +3648: position 0, colour {255, 0, 0,
// 255}, sub_21EAC0), clears +784 and sets flag 2.
// Arguments: a0 slot.
void sub_242540(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x00242540
    enter(ctx, 46);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    v0 = 255;
    sb(v0, sp, 0x3C);
    sb(zero, sp, 0x3D);
    sb(zero, sp, 0x3E);
    sb(v0, sp, 0x3F);
    sw(zero, sp, 0x20);
    sw(zero, sp, 0x24);
    sw(zero, sp, 0x28);
    sw(zero, sp, 0x2C);
    a0 = addiu(s0, 3392);
    a1 = addiu(sp, 0x20);
    jal(ctx, 0x24257Cu, gen::fn_sub_21EAE0_0021eae0);
    a0 = addiu(s0, 3392);
    a1 = addiu(sp, 0x3C);
    jal(ctx, 0x24258Cu, gen::fn_sub_21D950_0021d950);
    mtc1(zero, f12);
    a0 = addiu(s0, 3392);
    jal(ctx, 0x24259Cu, gen::fn_sub_21EAC0_0021eac0);
    a0 = addiu(s0, 3648);
    a1 = addiu(sp, 0x20);
    jal(ctx, 0x2425ACu, gen::fn_sub_21EAE0_0021eae0);
    a0 = addiu(s0, 3648);
    a1 = addiu(sp, 0x3C);
    jal(ctx, 0x2425BCu, gen::fn_sub_21D950_0021d950);
    mtc1(zero, f12);
    a0 = addiu(s0, 3648);
    jal(ctx, 0x2425CCu, gen::fn_sub_21EAC0_0021eac0);
    sw(zero, s0, bi::kDigitsTimer);
    lw(v1, s0, bi::kFlags);
    v1 = v1 | 0x2;
    sw(v1, s0, bi::kFlags);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00242840 sub_242840 -- 176 bytes; frame 0x140: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [biSetDigits] Writes a number into a strip of digit quads: sprintf("%d"-style format 0x7CC464), asserts it fits a1
// digits (line 1605), then sub_2428F0 for each digit (256-byte quads).
// Arguments: a0 quads, a1 digits.
void sub_242840(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00242840
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x140);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s2 = a1;
    a0 = addiu(sp, 0x40);
    a1 = addiu(gp, -26764);  // "%d"
    jal(ctx, 0x242864u, gen::fn_sprintf_00523ac8);
    a0 = addiu(sp, 0x40);
    jal(ctx, 0x242870u, gen::fn_strlen_00524388);
    s1 = v0;
    at = slt(s2, s1);
    if (at != 0) {
        // 0x00242888
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6032);  // "bi_main.c"
        a1 = 1605;
        jal(ctx, 0x242894u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024289c
    charge(ctx, 3);
    s2 = 0;
    for (;;) {
        // 0x002428c8
        charge(ctx, 3);
        v1 = slt(s2, s1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002428a8
        charge(ctx, 8);
        v0 = sll(s2, 8);
        a0 = addu(s0, v0);
        v0 = addu(s2, sp);
        lb(v0, v0, 64);
        a1 = addiu(v0, -48);
        jal(ctx, 0x2428BCu, gen::fn_sub_2428F0_002428f0);
        s2 = addiu(s2, 1);
    }
    // 0x002428d4
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x140);
}

// 0x002428F0 sub_2428F0 -- 92 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [biSetDigitQuad] Sets one digit quad's texture: panel texture 46 + digit (sub_21CCA0 / sub_21D3B0).
// Arguments: a0 quad, a1 digit.
void sub_2428F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002428f0
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    a0 = 1;
    jal(ctx, 0x24290Cu, gen::fn_sub_21C3F0_0021c3f0);
    a1 = addiu(s0, 46);
    a0 = v0;
    jal(ctx, 0x24291Cu, gen::fn_sub_21CCA0_0021cca0);
    a0 = s1;
    a1 = v0;
    jal(ctx, 0x24292Cu, gen::fn_sub_21D3B0_0021d3b0);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00242950 sub_242950 -- 224 bytes; frame 0x130: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [biGetDigitsWidth] Width of a number drawn with the digit font: sprintf of a0, length 1..5 asserted (lines 1638 /
// 1639); returns (len - 1) * 28 + the texture-46 width (+12) as a float in $f0.
// Arguments: a0 number.
void sub_242950(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x00242950
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x130);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    a0 = 1;
    jal(ctx, 0x242968u, gen::fn_sub_21C3F0_0021c3f0);
    s0 = v0;
    a0 = addiu(sp, 0x30);
    a1 = addiu(gp, -26764);  // "%d"
    a2 = s1;
    jal(ctx, 0x242980u, gen::fn_sprintf_00523ac8);
    a0 = addiu(sp, 0x30);
    jal(ctx, 0x24298Cu, gen::fn_strlen_00524388);
    s1 = v0;
    a0 = s0;
    a1 = 46;
    jal(ctx, 0x2429A0u, gen::fn_sub_21CCA0_0021cca0);
    s0 = v0;
    if (i64(s1) <= 0) {
        // 0x002429b4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6032);  // "bi_main.c"
        a1 = 1638;
        jal(ctx, 0x2429C0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002429c8
    charge(ctx, 3);
    at = slti(s1, 6);
    if (at == 0) {
        // 0x002429d4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6032);  // "bi_main.c"
        a1 = 1639;
        jal(ctx, 0x2429E0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002429e8 (the shared epilogue, written out on this path)
    charge(ctx, 18);
    v0 = addiu(s1, -1);
    mtc1(v0, f0);
    cvt_s_w(f3, f0);
    v0 = 0x41E00000;
    mtc1(v0, f2);
    lwc1(f0, s0, 12);
    cvt_s_w(f1, f0);
    mtc1(zero, f0);
    adda_s(f0, f1);
    madd_s(f0, f2, f3);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x130);
}

// 0x00242A30 sub_242A30 -- 20 bytes; leaf frame (no stack)
// Sets flag 4 of a battle info slot (draw the under-quads).
// Arguments: a0 slot.
void sub_242A30(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x00242a30
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v1, a0, bi::kFlags);
    v1 = v1 | 0x4;
    sw(v1, a0, bi::kFlags);
}

// 0x00242A50 sub_242A50 -- 12 bytes; leaf frame (no stack)
// Stores a battle info slot's owner word (+788).
// Arguments: a0 slot, a1 owner.
void sub_242A50(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5};
    // 0x00242a50
    enter(ctx, 3);  // entry check point + this block's cycles
    sw(a1, a0, bi::kOwner);
}

// 0x00242A60 sub_242A60 -- 124 bytes; frame 0x10: ra sp+0x0
// [biHasFreeSlot] Whether a battle info slot is free (any of the 16 without flag 1).
void sub_242A60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00242a60
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpBiWork);  // the battle info work (bi_main.c; 16 slots of 3,920 bytes) 0x7CE31C
    if (v0 == 0) {
        // 0x00242a74
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6032);  // "bi_main.c"
        a1 = 138;
        jal(ctx, 0x242A80u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00242a88
    charge(ctx, 5);
    lw(a0, gp, kGpBiWork);  // the battle info work (bi_main.c; 16 slots of 3,920 bytes) 0x7CE31C
    a1 = 0;
    v1 = 3920;
    for (;;) {
        // 0x00242abc
        charge(ctx, 3);
        v0 = slti(a1, 16);
        if (v0 != 0) {
            backedge(ctx);
            // 0x00242a9c
            charge(ctx, 7);
            mult(v0, a1, v1);
            v0 = addu(a0, v0);
            lw(v0, v0, 0);
            v0 = nor(v0, 0);
            v0 = v0 & 0x1;
            if (v0 == 0) {
                // 0x00242ab8
                charge(ctx, 1);
                a1 = addiu(a1, 1);
                continue;
            }
        }
        break;
    }
    // 0x00242ac8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = slti(a1, 16);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00242AE0 sub_242AE0 -- 148 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [biFindOwner] Whether a live battle info slot belongs to an owner (+788 == a0).
// Arguments: a0 owner.
void sub_242AE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00242ae0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, gp, kGpBiWork);  // the battle info work (bi_main.c; 16 slots of 3,920 bytes) 0x7CE31C
    if (v0 == 0) {
        // 0x00242afc
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6032);  // "bi_main.c"
        a1 = 138;
        jal(ctx, 0x242B08u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00242b10
    charge(ctx, 5);
    lw(a1, gp, kGpBiWork);  // the battle info work (bi_main.c; 16 slots of 3,920 bytes) 0x7CE31C
    a2 = 0;
    a0 = 3920;
    for (;;) {
        // 0x00242b50
        charge(ctx, 3);
        v0 = slti(a2, 16);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00242b24
        charge(ctx, 7);
        mult(v0, a2, a0);
        v1 = addu(a1, v0);
        lw(v0, v1, 0);
        v0 = nor(v0, 0);
        v0 = v0 & 0x1;
        if (v0 == 0) {
            // 0x00242b40
            charge(ctx, 3);
            lw(v0, v1, 788);
            if (v0 == s0) {
                break;
            }
            goto L_00242b4c;
        }
    L_00242b4c:
        charge(ctx, 1);
        a2 = addiu(a2, 1);
    }
    // 0x00242b5c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = slti(a2, 16);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00242B80 sub_242B80 -- 152 bytes; frame 0x40: ra sp+0x10, s0 sp+0x0 (sq)
// [biGetUnitMarkerPos] Screen position of a unit's marker: the unit with uid a0 (sub_289030), its head point
// (sub_2806D0), projected (sub_2D20A0); y + 14. 0 when the unit or the projection fails.
// Arguments: a0 uid, a1 out f32[2].
void sub_242B80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x00242b80
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    a0 = a0 & 0xFFFF;
    jal(ctx, 0x242B94u, gen::fn_sub_289030_00289030);
    if (v0 != 0) {
        // 0x00242bb0
        charge(ctx, 10);
        a0 = v0;
        a1 = addiu(sp, 0x30);
        jal(ctx, 0x242BB8u, gen::fn_sub_2806D0_002806d0);
        a0 = addiu(sp, 0x30);
        a1 = addiu(sp, 0x28);
        jal(ctx, 0x242BC8u, gen::fn_sub_2D20A0_002d20a0);
        if (v0 != 0) {
            // 0x00242be4
            charge(ctx, 8);
            lwc1(f0, sp, 0x28);
            swc1(f0, s0, 0);
            v0 = 0x41600000;
            mtc1(v0, f1);
            lwc1(f0, sp, 0x2C);
            add_s(f0, f1, f0);
            swc1(f0, s0, 4);
            v0 = 1;
        } else {
            // 0x00242bd8
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x00242ba4
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00242c04 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00242C40 sub_242C40 -- 24 bytes; leaf frame (no stack)
// [bpcRegister] Registers the battle panel command work (bpc_main.c): clears +0 / +8 / +29396 and stores it in $gp
// slot 0x7CE320.
// Arguments: a0 work.
void sub_242C40(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, gp{ctx, 28};
    // 0x00242c40
    enter(ctx, 6);  // entry check point + this block's cycles
    sw(zero, a0, 0);
    sw(zero, a0, 8);
    sw(zero, a0, 29396);
    sw(a0, gp, kGpBpcWork);  // the battle panel command work (bpc_main.c) 0x7CE320
}

// 0x00242C60 sub_242C60 -- 92 bytes; frame 0x10: ra sp+0x0
// [bpcRelease] Releases the bpc work: its font line (+27840) through sub_3B0170 when flag 2, then clears the slot.
void sub_242C60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00242c60
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpBpcWork);  // the battle panel command work (bpc_main.c) 0x7CE320
    if (v1 == 0) {
        // 0x00242c74
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6016);  // "bpc_main.c"
        a1 = 151;
        jal(ctx, 0x242C80u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00242c88
    charge(ctx, 5);
    lw(a0, gp, kGpBpcWork);  // the battle panel command work (bpc_main.c) 0x7CE320
    lw(v1, a0, bpc::kFlags);
    v1 = v1 & 0x2;
    if (v1 != 0) {
        // 0x00242c9c
        charge(ctx, 3);
        lw(a0, a0, bpc::kFontLine);
        jal(ctx, 0x242CA0u, gen::fn_sub_3B0170_003b0170);
    }
    // 0x00242ca8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    sw(zero, gp, kGpBpcWork);  // the battle panel command work (bpc_main.c) 0x7CE320
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00244120 sub_244120 -- 144 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bpcAddUnit] Appends a unit uid to the bpc work's list (+16, count +8, at most 10: K_Assert line 593).
// Arguments: a0 uid.
void sub_244120(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00244120
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v1, gp, kGpBpcWork);  // the battle panel command work (bpc_main.c) 0x7CE320
    if (v1 == 0) {
        // 0x00244140
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6016);  // "bpc_main.c"
        a1 = 151;
        jal(ctx, 0x24414Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00244154
    charge(ctx, 5);
    lw(s0, gp, kGpBpcWork);  // the battle panel command work (bpc_main.c) 0x7CE320
    lw(v1, s0, bpc::kUidCount);
    v1 = slti(v1, 10);
    if (v1 == 0) {
        // 0x00244168
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6016);  // "bpc_main.c"
        a1 = 593;
        jal(ctx, 0x244174u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024417c (the shared epilogue, written out on this path)
    charge(ctx, 13);
    lw(v1, s0, bpc::kUidCount);
    v1 = sll(v1, 2);
    v1 = addu(v1, s0);
    sw(s1, v1, 16);
    lw(v1, s0, bpc::kUidCount);
    v1 = addiu(v1, 1);
    sw(v1, s0, bpc::kUidCount);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00244E10 sub_244E10 -- 108 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [bpcGetFirstUnit] The first uid of the bpc work's list (+16); asserts flag 2 (line 993).
void sub_244E10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00244e10
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBpcWork);  // the battle panel command work (bpc_main.c) 0x7CE320
    if (v0 == 0) {
        // 0x00244e28
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6016);  // "bpc_main.c"
        a1 = 151;
        jal(ctx, 0x244E34u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00244e3c
    charge(ctx, 5);
    lw(s0, gp, kGpBpcWork);  // the battle panel command work (bpc_main.c) 0x7CE320
    lw(v0, s0, bpc::kFlags);
    v0 = v0 & 0x2;
    if (v0 == 0) {
        // 0x00244e50
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6016);  // "bpc_main.c"
        a1 = 993;
        jal(ctx, 0x244E5Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00244e64 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    lw(v0, s0, bpc::kUids);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002453D0 sub_2453D0 -- 76 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Stores a halfword at the bpc work's +29392.
// Arguments: a0 value.
void sub_2453D0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002453d0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, gp, kGpBpcWork);  // the battle panel command work (bpc_main.c) 0x7CE320
    if (v1 == 0) {
        // 0x002453ec
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6016);  // "bpc_main.c"
        a1 = 151;
        jal(ctx, 0x2453F8u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00245400 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v1, gp, kGpBpcWork);  // the battle panel command work (bpc_main.c) 0x7CE320
    sh(s0, v1, bpc::kWord29392);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00245420 sub_245420 -- 1264 bytes; frame 0x90: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bpcBuildEntry] Builds a bpc entry for the unit with uid a1: clears its flags, stores the uid (+8), HP / max HP
// (+2608 / +2612), the projected centre (+2616, flag 0x40 when off screen, +20 on y), flag 0x400 for the work's first
// uid; in mode 2 (the enemy panel) the analysis mark 0x80 for enemies not seen yet with the three marker timers
// +2596; in mode 0 flag 1 when sub_300E90(unit, the work's skill +29392) and flag 2 for a known null / repel / drain
// affinity to that skill; then the entry's quads (panel textures 1..4, 44, 69, 55 / 57 / 8 / 61).
// Arguments: a0 entry, a1 uid.
void sub_245420(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x00245420
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
    s3 = a1;
    lw(v0, gp, kGpBpcWork);  // the battle panel command work (bpc_main.c) 0x7CE320
    if (v0 == 0) {
        // 0x00245458
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6016);  // "bpc_main.c"
        a1 = 151;
        jal(ctx, 0x245464u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024546c
    charge(ctx, 40);
    lw(s0, gp, kGpBpcWork);  // the battle panel command work (bpc_main.c) 0x7CE320
    a0 = 2;
    jal(ctx, 0x245474u, gen::fn_sub_21C3F0_0021c3f0);
    s5 = v0;
    a0 = 1;
    jal(ctx, 0x245484u, gen::fn_sub_21C3F0_0021c3f0);
    s2 = v0;
    a0 = 5;
    jal(ctx, 0x245494u, gen::fn_sub_21C3F0_0021c3f0);
    s6 = v0;
    sw(zero, s4, bpce::kFlags);
    sw(zero, s4, 4);
    sw(s3, s4, bpce::kUid);
    a0 = s3;
    jal(ctx, 0x2454B0u, gen::fn_sub_1FF430_001ff430);
    s1 = v0;
    lw(a0, v0, 2604);
    jal(ctx, 0x2454C0u, gen::fn_datCalcGetHp_002ffd70);
    v0 = v0 & 0xFFFF;
    sw(v0, s4, bpce::kHp);
    lw(a0, s1, 2604);
    jal(ctx, 0x2454D4u, gen::fn_datCalcGetMaxHp_002ffdf0);
    v0 = v0 & 0xFFFF;
    sw(v0, s4, bpce::kMaxHp);
    a0 = s1;
    a1 = addiu(sp, 0x80);
    jal(ctx, 0x2454ECu, gen::fn_sub_280580_00280580);
    a0 = addiu(sp, 0x80);
    a1 = addiu(s4, 2616);
    jal(ctx, 0x2454FCu, gen::fn_sub_2D20A0_002d20a0);
    if (v0 == 0) {
        // 0x0024550c
        charge(ctx, 3);
        lw(v0, s4, bpce::kFlags);
        v0 = v0 | 0x40;
        sw(v0, s4, bpce::kFlags);
    }
    // 0x00245518
    charge(ctx, 10);
    lwc1(f1, s4, bpce::kScreenPos + 4);
    v0 = 0x41A00000;
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, s4, bpce::kScreenPos + 4);
    lw(v0, s0, bpc::kFlags);
    v0 = v0 & 0x2;
    if (v0 != 0) {
        // 0x00245540
        charge(ctx, 4);
        lw(v1, s4, bpce::kUid);
        lw(v0, s0, bpc::kUids);
        if (v1 == v0) {
            // 0x00245550
            charge(ctx, 3);
            lw(v0, s4, bpce::kFlags);
            v0 = v0 | 0x400;
            sw(v0, s4, bpce::kFlags);
        }
    }
    // 0x0024555c
    charge(ctx, 4);
    lw(v1, s0, bpc::kMode);
    v0 = 2;
    if (v1 == v0) {
        // 0x0024567c
        charge(ctx, 6);
        lw(v0, s1, 2604);
        lhu(a0, v0, 2);
        jal(ctx, 0x245684u, gen::fn_sub_17B260_0017b260);
        if (v0 == 0) {
            // 0x00245694
            charge(ctx, 3);
            lw(v0, s4, bpce::kFlags);
            v0 = v0 | 0x80;
            sw(v0, s4, bpce::kFlags);
        }
        // 0x002456a0
        charge(ctx, 3);
        v1 = 0;
        for (;;) {
            // 0x002456bc
            charge(ctx, 3);
            v0 = slti(v1, 3);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002456ac
            charge(ctx, 4);
            v0 = sll(v1, 2);
            v0 = addu(s4, v0);
            sw(zero, v0, 2596);
            v1 = addiu(v1, 1);
        }
        // 0x002456c8
        charge(ctx, 4);
        lw(v0, s4, bpce::kFlags);
        v0 = v0 & 0x80;
        if (v0 != 0) {
            // 0x002456d8
            charge(ctx, 6);
            lw(a0, s0, bpc::kUids);
            jal(ctx, 0x2456DCu, gen::fn_sub_1FF430_001ff430);
            lw(v1, v0, 168);
            if (s3 != v1) {
                // 0x002456fc
                charge(ctx, 6);
                lw(v1, s1, 2604);
                lhu(v1, v1, 2);
                lw(v0, v0, 2604);
                lhu(v0, v0, 2);
                if (v1 != v0) {
                    // 0x00245724
                    charge(ctx, 2);
                    v0 = 2;
                    sw(v0, s4, bpce::kMarkIndex);
                } else {
                    // 0x00245714
                    charge(ctx, 4);
                    v0 = 1;
                    sw(v0, s4, bpce::kMarkIndex);
                }
            } else {
                // 0x002456f0
                charge(ctx, 3);
                sw(zero, s4, bpce::kMarkIndex);
            }
            // 0x0024572c
            charge(ctx, 5);
            v1 = 10;
            lw(v0, s4, bpce::kMarkIndex);
            v0 = sll(v0, 2);
            v0 = addu(v0, s4);
            sw(v1, v0, 2596);
        }
    } else {
        // 0x0024556c
        charge(ctx, 3);
        v0 = 1;
        if (v1 != v0) {
            // 0x00245578
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x00245588
                charge(ctx, 6);
                lw(a0, s1, 2604);
                lhu(a1, s0, bpc::kWord29392);
                jal(ctx, 0x245590u, gen::fn_sub_300E90_00300e90);
                if (v0 != 0) {
                    // 0x002455a0
                    charge(ctx, 3);
                    lw(v0, s4, bpce::kFlags);
                    v0 = v0 | 0x1;
                    sw(v0, s4, bpce::kFlags);
                }
                // 0x002455ac
                charge(ctx, 4);
                lw(v0, s0, bpc::kFlags);
                v0 = v0 & 0x8;
                if (v0 != 0) {
                    // 0x002455bc
                    charge(ctx, 5);
                    lw(v1, s1, 2604);
                    lhu(v0, v1, 0);
                    v0 = v0 & 0x4;
                    if (v0 != 0) {
                        // 0x002455d0
                        charge(ctx, 10);
                        lhu(v1, v1, 2);
                        v0 = sll(v1, 5);
                        v0 = subu(v0, v1);
                        v1 = sll(v0, 1);
                        lw(v0, gp, kGpEnemyTbl);  // gBtlEnemyTbl
                        v0 = addu(v1, v0);
                        lhu(v0, v0, 30);
                        v0 = v0 & 0x20;
                        if (v0 == 0) {
                            goto L_002455f8;
                        }
                        goto L_00245740;
                    }
                L_002455f8:
                    charge(ctx, 16);
                    a0 = 0;
                    lhu(a1, s0, bpc::kWord29392);
                    jal(ctx, 0x245600u, gen::fn_datCalcGetSkillElement_003082f0);
                    a1 = dsll32(v0, 16);
                    a1 = dsra32(a1, 16);
                    lw(a0, s1, 2604);
                    jal(ctx, 0x245614u, gen::fn_datCalcGetAffinity_00306e80);
                    s3 = v0;
                    lw(v0, s1, 2604);
                    lhu(a0, v0, 2);
                    jal(ctx, 0x245628u, gen::fn_sub_17B260_0017b260);
                    if (v0 != 0) {
                        // 0x00245638
                        charge(ctx, 4);
                        v0 = 0x1000000;
                        v0 = s3 & v0;
                        if (v0 == 0) {
                            // 0x00245648
                            charge(ctx, 4);
                            v0 = 0x2000000;
                            v0 = s3 & v0;
                            if (v0 != 0) {
                                goto L_00245668;
                            }
                            // 0x00245658
                            charge(ctx, 4);
                            v0 = 0x4000000;
                            v0 = s3 & v0;
                            if (v0 != 0) {
                                goto L_00245668;
                            }
                            goto L_00245740;
                        }
                    L_00245668:
                        charge(ctx, 5);
                        lw(v0, s4, bpce::kFlags);
                        v0 = v0 | 0x2;
                        sw(v0, s4, bpce::kFlags);
                    }
                }
            } else {
                // 0x00245580
                charge(ctx, 2);
            }
        }
    }
L_00245740:
    charge(ctx, 52);
    a0 = s2;
    a1 = 3;
    jal(ctx, 0x245748u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s4, 16);
    a1 = v0;
    jal(ctx, 0x245758u, gen::fn_sub_21D3B0_0021d3b0);
    a0 = s2;
    a1 = 2;
    jal(ctx, 0x245768u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s4, 528);
    a1 = v0;
    jal(ctx, 0x245778u, gen::fn_sub_21D3B0_0021d3b0);
    a0 = s2;
    a1 = 44;
    jal(ctx, 0x245788u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s4, 1296);
    a1 = v0;
    jal(ctx, 0x245798u, gen::fn_sub_21D3B0_0021d3b0);
    a0 = s2;
    a1 = 69;
    jal(ctx, 0x2457A8u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s4, 1552);
    a1 = v0;
    jal(ctx, 0x2457B8u, gen::fn_sub_21D3B0_0021d3b0);
    a0 = s2;
    a1 = 1;
    jal(ctx, 0x2457C8u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s4, 1040);
    a1 = v0;
    jal(ctx, 0x2457D8u, gen::fn_sub_21D3B0_0021d3b0);
    a0 = s6;
    a1 = 4;
    jal(ctx, 0x2457E8u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s4, 784);
    a1 = v0;
    jal(ctx, 0x2457F8u, gen::fn_sub_21D3B0_0021d3b0);
    lw(a0, s0, bpc::kMode);
    v1 = 2;
    if (a0 == v1) {
        // 0x00245854
        charge(ctx, 12);
        a0 = s5;
        a1 = 55;
        jal(ctx, 0x24585Cu, gen::fn_sub_21CCA0_0021cca0);
        a0 = addiu(s4, 272);
        a1 = v0;
        jal(ctx, 0x24586Cu, gen::fn_sub_21D3B0_0021d3b0);
        lw(v0, s4, bpce::kFlags);
        v0 = v0 & 0x80;
        if (v0 != 0) {
            // 0x00245884
            charge(ctx, 8);
            a0 = s5;
            a1 = 57;
            jal(ctx, 0x24588Cu, gen::fn_sub_21CCA0_0021cca0);
            a0 = addiu(s4, 1824);
            a1 = v0;
            jal(ctx, 0x24589Cu, gen::fn_sub_21D3B0_0021d3b0);
        }
        // 0x002458a4
        charge(ctx, 16);
        a0 = s2;
        a1 = 8;
        jal(ctx, 0x2458ACu, gen::fn_sub_21CCA0_0021cca0);
        a0 = addiu(s4, 2336);
        a1 = v0;
        jal(ctx, 0x2458BCu, gen::fn_sub_21D3B0_0021d3b0);
        a0 = s5;
        a1 = 61;
        jal(ctx, 0x2458CCu, gen::fn_sub_21CCA0_0021cca0);
        a0 = addiu(s4, 2080);
        a1 = v0;
        jal(ctx, 0x2458DCu, gen::fn_sub_21D3B0_0021d3b0);
    } else {
        // 0x00245810
        charge(ctx, 3);
        v1 = 1;
        if (a0 != v1) {
            // 0x0024581c
            charge(ctx, 2);
            if (a0 == 0) {
                goto L_0024582c;
            }
            // 0x00245824
            charge(ctx, 2);
            // 0x002458e4 (the shared epilogue, written out on this path)
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
            return;
        }
    L_0024582c:
        charge(ctx, 10);
        a0 = s2;
        a1 = 4;
        jal(ctx, 0x245834u, gen::fn_sub_21CCA0_0021cca0);
        a0 = addiu(s4, 272);
        a1 = v0;
        jal(ctx, 0x245844u, gen::fn_sub_21D3B0_0021d3b0);
    }
    // 0x002458e4 (the shared epilogue, written out on this path)
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

// 0x00245910 sub_245910 -- 92 bytes; leaf frame (no stack)
// Starts a bpc entry's slide-in (flag 0x10): reverses a running slide-out (flag 0x20: frame +1808 = 10 - frame,
// clears 0x20 / 0x200) or restarts it at 0.
// Arguments: a0 entry.
void sub_245910(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00245910
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, bpce::kFlags);
    v1 = v1 & 0x20;
    if (v1 == 0) {
        // 0x00245954
        charge(ctx, 1);
        sw(zero, a0, bpce::kSlide);
    } else {
        // 0x00245920
        charge(ctx, 13);
        lw(a1, a0, bpce::kSlide);
        v1 = 10;
        v1 = subu(v1, a1);
        sw(v1, a0, bpce::kSlide);
        lw(a1, a0, bpce::kFlags);
        v1 = si(-33);
        a1 = a1 & v1;
        sw(a1, a0, bpce::kFlags);
        v1 = si(-513);
        v1 = a1 & v1;
        sw(v1, a0, bpce::kFlags);
    }
    // 0x00245958 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    lw(v1, a0, bpce::kFlags);
    v1 = v1 | 0x10;
    sw(v1, a0, bpce::kFlags);
}

// 0x00245970 sub_245970 -- 92 bytes; leaf frame (no stack)
// Starts a bpc entry's slide-out (flag 0x20), the mirror of sub_245910.
// Arguments: a0 entry.
void sub_245970(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00245970
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, bpce::kFlags);
    v1 = v1 & 0x10;
    if (v1 == 0) {
        // 0x002459b4
        charge(ctx, 1);
        sw(zero, a0, bpce::kSlide);
    } else {
        // 0x00245980
        charge(ctx, 13);
        lw(a1, a0, bpce::kSlide);
        v1 = 10;
        v1 = subu(v1, a1);
        sw(v1, a0, bpce::kSlide);
        lw(a1, a0, bpce::kFlags);
        v1 = si(-17);
        a1 = a1 & v1;
        sw(a1, a0, bpce::kFlags);
        v1 = si(-513);
        v1 = a1 & v1;
        sw(v1, a0, bpce::kFlags);
    }
    // 0x002459b8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    lw(v1, a0, bpce::kFlags);
    v1 = v1 | 0x20;
    sw(v1, a0, bpce::kFlags);
}

// 0x00245A00 sub_245A00 -- 484 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bpcBuildEntries] Rebuilds the bpc entries (sub_245420) and their count (+12): mode 2 the enemies in the battle
// with a placed action, modes 0 / 1 the party then the enemies in the battle (unit flag 8), from the side lists'
// tails.
void sub_245A00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00245a00
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, kGpBpcWork);  // the battle panel command work (bpc_main.c) 0x7CE320
    if (v1 == 0) {
        // 0x00245a24
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6016);  // "bpc_main.c"
        a1 = 151;
        jal(ctx, 0x245A30u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00245a38
    charge(ctx, 4);
    lw(s1, gp, kGpBpcWork);  // the battle panel command work (bpc_main.c) 0x7CE320
    lw(s0, gp, kGpBtl);  // gBtl 0x7CE3EC
    if (s0 == 0) {
        // 0x00245a48
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6016);  // "bpc_main.c"
        a1 = 1305;
        jal(ctx, 0x245A54u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00245a5c
    charge(ctx, 5);
    s2 = 0;
    lw(a0, s1, bpc::kMode);
    v1 = 2;
    if (a0 == v1) {
        // 0x00245b44
        charge(ctx, 3);
        lw(s0, s0, gbtl4::kUnitTail1);
        for (;;) {
            // 0x00245bb8
            charge(ctx, 2);
            if (s0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00245b50
            charge(ctx, 5);
            lw(v1, s0, unit::kFlags);
            v1 = nor(v1, 0);
            v1 = v1 & 0x8;
            if (v1 == 0) {
                // 0x00245b64
                charge(ctx, 5);
                a0 = s0;
                jal(ctx, 0x245B68u, gen::fn_sub_29A1D0_0029a1d0);
                if (v0 != 0) {
                    // 0x00245b78
                    charge(ctx, 4);
                    lhu(v1, v0, 26);
                    v1 = v1 & 0x8;
                    if (v1 != 0) {
                        // 0x00245b88
                        charge(ctx, 11);
                        v0 = sll(s2, 2);
                        v0 = addu(v0, s2);
                        v0 = sll(v0, 3);
                        v0 = addu(v0, s2);
                        v0 = sll(v0, 6);
                        v0 = addu(s1, v0);
                        a0 = addiu(v0, 64);
                        lw(a1, s0, unit::kUid);
                        jal(ctx, 0x245BA8u, gen::fn_sub_245420_00245420);
                        s2 = addiu(s2, 1);
                    }
                }
            }
            // 0x00245bb4
            charge(ctx, 1);
            lw(s0, s0, unit::kPrev);
        }
    } else {
        // 0x00245a70
        charge(ctx, 3);
        v1 = 1;
        if (a0 != v1) {
            // 0x00245a7c
            charge(ctx, 2);
            if (a0 == 0) {
                goto L_00245a8c;
            }
            // 0x00245a84
            charge(ctx, 2);
            // 0x00245bc0 (the shared epilogue, written out on this path)
            charge(ctx, 9);
            sw(s2, s1, bpc::kEntryCount);
            ld(ra, sp, 0x40);
            lq(s3, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x50);
            return;
        }
    L_00245a8c:
        charge(ctx, 3);
        lw(s3, s0, 336);
        for (;;) {
            // 0x00245adc
            charge(ctx, 2);
            if (s3 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00245a98
            charge(ctx, 5);
            lw(v1, s3, 156);
            v1 = nor(v1, 0);
            v1 = v1 & 0x8;
            if (v1 == 0) {
                // 0x00245aac
                charge(ctx, 11);
                v0 = sll(s2, 2);
                v0 = addu(v0, s2);
                v0 = sll(v0, 3);
                v0 = addu(v0, s2);
                v0 = sll(v0, 6);
                v0 = addu(s1, v0);
                a0 = addiu(v0, 64);
                lw(a1, s3, 168);
                jal(ctx, 0x245ACCu, gen::fn_sub_245420_00245420);
                s2 = addiu(s2, 1);
            }
            // 0x00245ad8
            charge(ctx, 1);
            lw(s3, s3, 2612);
        }
        // 0x00245ae4
        charge(ctx, 3);
        lw(s0, s0, 344);
        for (;;) {
            // 0x00245b34
            charge(ctx, 2);
            if (s0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00245af0
            charge(ctx, 5);
            lw(v1, s0, 156);
            v1 = nor(v1, 0);
            v1 = v1 & 0x8;
            if (v1 == 0) {
                // 0x00245b04
                charge(ctx, 11);
                v0 = sll(s2, 2);
                v0 = addu(v0, s2);
                v0 = sll(v0, 3);
                v0 = addu(v0, s2);
                v0 = sll(v0, 6);
                v0 = addu(s1, v0);
                a0 = addiu(v0, 64);
                lw(a1, s0, 168);
                jal(ctx, 0x245B24u, gen::fn_sub_245420_00245420);
                s2 = addiu(s2, 1);
            }
            // 0x00245b30
            charge(ctx, 1);
            lw(s0, s0, 2612);
        }
        // 0x00245b3c
        charge(ctx, 2);
    }
    // 0x00245bc0 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    sw(s2, s1, 12);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00245BF0 sub_245BF0 -- 220 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bpcFindEntry] The bpc entry (2,624 bytes from +64) of a unit uid (+8); K_Assert line 1375 when absent.
// Arguments: a0 uid.
void sub_245BF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00245bf0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(v0, gp, kGpBpcWork);  // the battle panel command work (bpc_main.c) 0x7CE320
    if (v0 == 0) {
        // 0x00245c14
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6016);  // "bpc_main.c"
        a1 = 151;
        jal(ctx, 0x245C20u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00245c28
    charge(ctx, 5);
    lw(s0, gp, kGpBpcWork);  // the battle panel command work (bpc_main.c) 0x7CE320
    s1 = 0;
    lw(v1, s0, bpc::kEntryCount);
    for (;;) {
        // 0x00245c64
        charge(ctx, 3);
        v0 = slt(s1, v1);
        if (v0 != 0) {
            backedge(ctx);
            // 0x00245c3c
            charge(ctx, 9);
            v0 = sll(s1, 2);
            v0 = addu(v0, s1);
            v0 = sll(v0, 3);
            v0 = addu(v0, s1);
            v0 = sll(v0, 6);
            v0 = addu(s0, v0);
            lw(v0, v0, 72);
            if (v0 != s2) {
                // 0x00245c60
                charge(ctx, 1);
                s1 = addiu(s1, 1);
                continue;
            }
        }
        break;
    }
    // 0x00245c70
    charge(ctx, 4);
    lw(v0, s0, bpc::kEntryCount);
    v0 = slt(s1, v0);
    if (v0 == 0) {
        // 0x00245c80
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6016);  // "bpc_main.c"
        a1 = 1375;
        jal(ctx, 0x245C8Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00245c94 (the shared epilogue, written out on this path)
    charge(ctx, 14);
    v0 = sll(s1, 2);
    v0 = addu(v0, s1);
    v0 = sll(v0, 3);
    v0 = addu(v0, s1);
    v0 = sll(v0, 6);
    v0 = addu(s0, v0);
    v0 = addiu(v0, 64);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00248490 sub_248490 -- 16 bytes; leaf frame (no stack)
// Registers the battle panel message work (bpm_main.c, $gp slot 0x7CE324).
// Arguments: a0 work.
void sub_248490(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, gp{ctx, 28};
    // 0x00248490
    enter(ctx, 4);  // entry check point + this block's cycles
    sw(zero, a0, 0);
    sw(a0, gp, kGpBpmWork);  // the battle panel message work (bpm_main.c) 0x7CE324
}

// 0x002484A0 sub_2484A0 -- 88 bytes; frame 0x10: ra sp+0x0
// Unregisters the bpm work, releasing its font line first when open (flag 1).
void sub_2484A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002484a0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpBpmWork);  // the battle panel message work (bpm_main.c) 0x7CE324
    if (v1 == 0) {
        // 0x002484b4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6000);  // "bpm_main.c"
        a1 = 61;
        jal(ctx, 0x2484C0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002484c8
    charge(ctx, 5);
    lw(v1, gp, kGpBpmWork);  // the battle panel message work (bpm_main.c) 0x7CE324
    lw(v1, v1, bpm::kFlags);
    v1 = v1 & 0x1;
    if (v1 != 0) {
        // 0x002484dc
        charge(ctx, 2);
        jal(ctx, 0x2484DCu, gen::fn_sub_2491F0_002491f0);
    }
    // 0x002484e4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    sw(zero, gp, kGpBpmWork);  // the battle panel message work (bpm_main.c) 0x7CE324
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00248620 sub_248620 -- 1420 bytes; frame 0x90: ra sp+0x50, s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// Update of the bpm message window: width from the font line, slide and alpha.
void sub_248620(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23};
    // 0x00248620
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lw(v0, gp, kGpBpmWork);  // the battle panel message work (bpm_main.c) 0x7CE324
    if (v0 == 0) {
        // 0x00248654
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6000);  // "bpm_main.c"
        a1 = 61;
        jal(ctx, 0x248660u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00248668
    charge(ctx, 9);
    lw(s1, gp, kGpBpmWork);  // the battle panel message work (bpm_main.c) 0x7CE324
    a0 = 1;
    jal(ctx, 0x248670u, gen::fn_sub_21C3F0_0021c3f0);
    s2 = v0;
    lw(v1, s1, bpm::kFlags);
    v1 = v1 & 0x1;
    if (v1 != 0) {
        // 0x0024868c
        charge(ctx, 4);
        lw(v1, s1, bpm::kFrame);
        at = slti(v1, 45);
        if (at == 0) {
            // 0x002486ac
            charge(ctx, 6);
            jal(ctx, 0x2486ACu, gen::fn_sub_2491F0_002491f0);
            lw(a0, s1, bpm::kFlags);
            v1 = si(-2);
            v1 = a0 & v1;
            sw(v1, s1, bpm::kFlags);
        } else {
            // 0x0024869c
            charge(ctx, 4);
            v1 = addiu(v1, 1);
            sw(v1, s1, bpm::kFrame);
        }
    }
    // 0x002486c4
    charge(ctx, 5);
    lw(a0, s1, bpm::kFlags);
    v1 = nor(a0, 0);
    v1 = v1 & 0x1;
    if (v1 == 0) {
        // 0x002486d8
        charge(ctx, 6);
        v0 = a0 | 0x2;
        sw(v0, s1, bpm::kFlags);
        mtc1(zero, f22);
        lw(s0, s1, bpm::kFontLine);
        for (;;) {
            // 0x00248710
            charge(ctx, 2);
            if (s0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002486f0
            charge(ctx, 8);
            a0 = s0;
            jal(ctx, 0x2486F4u, gen::fn_frFontLineGetWidth_003b19d0);
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            add_s(f22, f22, f0);
            lw(s0, s0, 36);
        }
        // 0x00248718
        charge(ctx, 147);
        v0 = 0x40000000;
        mtc1(v0, f0);
        div_s(f20, f22, f0);
        v0 = 309;
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        sub_s(f21, f0, f20);
        v0 = 0x42640000;
        mtc1(v0, f0);
        sub_s(f23, f21, f0);
        a0 = s2;
        a1 = 67;
        jal(ctx, 0x248754u, gen::fn_sub_21CCA0_0021cca0);
        s0 = v0;
        swc1(f23, sp, 0x60);
        v1 = 0x42C80000;
        sw(v1, sp, 0x64);
        lwc1(f0, v0, 12);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x68);
        lwc1(f0, v0, 16);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x6C);
        a0 = addiu(s1, 16);
        a1 = addiu(sp, 0x60);
        jal(ctx, 0x24878Cu, gen::fn_sub_21D8E0_0021d8e0);
        v0 = 255;
        sb(v0, sp, 0x8C);
        sb(v0, sp, 0x8D);
        sb(v0, sp, 0x8E);
        sb(v0, sp, 0x8F);
        a0 = addiu(s1, 16);
        a1 = addiu(sp, 0x8C);
        jal(ctx, 0x2487B0u, gen::fn_sub_21D950_0021d950);
        lwc1(f0, s0, 12);
        cvt_s_w(f0, f0);
        add_s(f2, f0, f23);
        v0 = 309;
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        add_s(f20, f0, f20);
        v0 = 0x42640000;
        mtc1(v0, f0);
        add_s(f1, f0, f20);
        v0 = 0x41800000;
        mtc1(v0, f0);
        sub_s(f23, f1, f0);
        sub_s(f0, f23, f2);
        swc1(f2, sp, 0x60);
        v0 = 0x42C80000;
        sw(v0, sp, 0x64);
        swc1(f0, sp, 0x68);
        lwc1(f0, s0, 16);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x6C);
        a0 = addiu(s1, 272);
        a1 = addiu(sp, 0x60);
        jal(ctx, 0x248820u, gen::fn_sub_21D8E0_0021d8e0);
        v0 = 255;
        sb(v0, sp, 0x8C);
        sb(v0, sp, 0x8D);
        sb(v0, sp, 0x8E);
        sb(v0, sp, 0x8F);
        a0 = addiu(s1, 272);
        a1 = addiu(sp, 0x8C);
        jal(ctx, 0x248844u, gen::fn_sub_21D950_0021d950);
        a0 = s2;
        a1 = 68;
        jal(ctx, 0x248854u, gen::fn_sub_21CCA0_0021cca0);
        swc1(f23, sp, 0x60);
        v1 = 0x42C80000;
        sw(v1, sp, 0x64);
        lwc1(f0, v0, 12);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x68);
        lwc1(f0, v0, 16);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x6C);
        a0 = addiu(s1, 528);
        a1 = addiu(sp, 0x60);
        jal(ctx, 0x248888u, gen::fn_sub_21D8E0_0021d8e0);
        v0 = 255;
        sb(v0, sp, 0x8C);
        sb(v0, sp, 0x8D);
        sb(v0, sp, 0x8E);
        sb(v0, sp, 0x8F);
        a0 = addiu(s1, 528);
        a1 = addiu(sp, 0x8C);
        jal(ctx, 0x2488ACu, gen::fn_sub_21D950_0021d950);
        a0 = s2;
        a1 = 0;
        jal(ctx, 0x2488BCu, gen::fn_sub_21CCA0_0021cca0);
        v1 = 0x42AC0000;
        mtc1(v1, f0);
        sub_s(f1, f21, f0);
        swc1(f1, sp, 0x60);
        v1 = 0x42580000;
        sw(v1, sp, 0x64);
        add_s(f0, f0, f20);
        sub_s(f0, f0, f1);
        swc1(f0, sp, 0x68);
        lw(v1, v0, 16);
        v0 = sll(v1, 6);
        v1 = addu(v0, v1);
        v0 = sll(v1, 2);
        v0 = subu(v0, v1);
        v1 = sll(v0, 1);
        v0 = 100;
        div(v1, v0);
        mflo(v0);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x6C);
        a0 = addiu(s1, 784);
        a1 = addiu(sp, 0x60);
        jal(ctx, 0x248928u, gen::fn_sub_21D8E0_0021d8e0);
        v0 = 255;
        sb(v0, sp, 0x8C);
        sb(v0, sp, 0x8D);
        sb(v0, sp, 0x8E);
        sb(v0, sp, 0x8F);
        a0 = addiu(s1, 784);
        a1 = addiu(sp, 0x8C);
        jal(ctx, 0x24894Cu, gen::fn_sub_21D950_0021d950);
        mtc1(zero, f20);
        lw(s0, s1, bpm::kFontLine);
        for (;;) {
            // 0x00248984
            charge(ctx, 2);
            if (s0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00248964
            charge(ctx, 8);
            a0 = s0;
            jal(ctx, 0x248968u, gen::fn_frFontLineGetWidth_003b19d0);
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            add_s(f20, f20, f0);
            lw(s0, s0, 36);
        }
        // 0x0024898c
        charge(ctx, 8);
        lw(s0, s1, bpm::kFontLine);
        v0 = 0x44260000;
        mtc1(v0, f0);
        cvt_w_s(f0, f0);
        mfc1(s3, f0);
        for (;;) {
            // 0x002489f8
            charge(ctx, 2);
            if (s0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002489ac
            charge(ctx, 19);
            a0 = s0;
            jal(ctx, 0x2489B0u, gen::fn_frFontLineGetWidth_003b19d0);
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            sub_s(f20, f20, f0);
            add_s(f1, f21, f20);
            v0 = 0x41800000;
            mtc1(v0, f0);
            mul_s(f0, f0, f1);
            cvt_w_s(f0, f0);
            mfc1(a1, f0);
            a0 = s0;
            a2 = s3;
            jal(ctx, 0x2489ECu, gen::fn_frFontLineSetPos_003b0d70);
            lw(s0, s0, 36);
        }
        // 0x00248a00
        charge(ctx, 95);
        v0 = 200;
        sb(v0, sp, 0x8C);
        v0 = 230;
        sb(v0, sp, 0x8D);
        v0 = 255;
        sb(v0, sp, 0x8E);
        sb(v0, sp, 0x8F);
        lbu(v0, sp, 0x8C);
        v1 = sll(v0, 24);
        lbu(v0, sp, 0x8D);
        v0 = sll(v0, 16);
        v1 = v1 | v0;
        lbu(v0, sp, 0x8E);
        v0 = sll(v0, 8);
        v1 = v0 | v1;
        lbu(v0, sp, 0x8F);
        a1 = v0 | v1;
        lw(a0, s1, bpm::kFontLine);
        jal(ctx, 0x248A48u, gen::fn_frFontLineSetRgba_003b0e20);
        a0 = s2;
        a1 = 66;
        jal(ctx, 0x248A58u, gen::fn_sub_21CCA0_0021cca0);
        s0 = v0;
        v1 = 0x40000000;
        mtc1(v1, f0);
        div_s(f20, f22, f0);
        v1 = 309;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        sub_s(f1, f0, f20);
        v1 = 0x41E00000;
        mtc1(v1, f0);
        sub_s(f0, f1, f0);
        swc1(f0, sp, 0x60);
        v1 = 0x42B60000;
        sw(v1, sp, 0x64);
        lwc1(f0, v0, 12);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x68);
        lwc1(f0, v0, 16);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x6C);
        a0 = addiu(s1, 1040);
        a1 = addiu(sp, 0x60);
        jal(ctx, 0x248AC4u, gen::fn_sub_21D8E0_0021d8e0);
        v0 = 255;
        sb(v0, sp, 0x8C);
        sb(v0, sp, 0x8D);
        sb(v0, sp, 0x8E);
        sb(v0, sp, 0x8F);
        a0 = addiu(s1, 1040);
        a1 = addiu(sp, 0x8C);
        jal(ctx, 0x248AE8u, gen::fn_sub_21D950_0021d950);
        v0 = 309;
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        add_s(f1, f0, f20);
        v0 = 0x41E00000;
        mtc1(v0, f0);
        add_s(f1, f0, f1);
        v0 = 0x41800000;
        mtc1(v0, f0);
        sub_s(f0, f1, f0);
        swc1(f0, sp, 0x60);
        v0 = 0x42B60000;
        sw(v0, sp, 0x64);
        lwc1(f0, s0, 12);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x68);
        lwc1(f0, s0, 16);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x6C);
        a0 = addiu(s1, 1296);
        a1 = addiu(sp, 0x60);
        jal(ctx, 0x248B50u, gen::fn_sub_21D8E0_0021d8e0);
        v0 = 255;
        sb(v0, sp, 0x8C);
        sb(v0, sp, 0x8D);
        sb(v0, sp, 0x8E);
        sb(v0, sp, 0x8F);
        a0 = addiu(s1, 1296);
        a1 = addiu(sp, 0x8C);
        jal(ctx, 0x248B74u, gen::fn_sub_21D950_0021d950);
    }
    // 0x00248b7c (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x00248BB0 sub_248BB0 -- 900 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Draw of the bpm message window.
void sub_248BB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00248bb0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBpmWork);  // the battle panel message work (bpm_main.c) 0x7CE324
    if (v0 == 0) {
        // 0x00248bd4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6000);  // "bpm_main.c"
        a1 = 61;
        jal(ctx, 0x248BE0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00248be8
    charge(ctx, 10);
    lw(s2, gp, kGpBpmWork);  // the battle panel message work (bpm_main.c) 0x7CE324
    a0 = 1;
    jal(ctx, 0x248BF0u, gen::fn_sub_21C3F0_0021c3f0);
    s3 = v0;
    lw(v1, s2, bpm::kFlags);
    a0 = nor(v1, 0);
    v1 = a0 & 0x1;
    if (v1 == 0) {
        // 0x00248c10
        charge(ctx, 3);
        v0 = a0 & 0x2;
        if (v0 != 0) {
            // 0x00248c1c
            charge(ctx, 2);
            jal(ctx, 0x248C1Cu, gen::fn_sub_248620_00248620);
        }
        // 0x00248c24
        charge(ctx, 188);
        s1 = 0x960000;
        s1 = addiu(s1, 144);  // &pfn_RwRenderStateSet
        a0 = 9;
        a1 = 2;
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x248C38u, v0.u());
        a0 = 20;
        a1 = 2;
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x248C4Cu, v0.u());
        a0 = 8;
        a1 = 0;
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x248C60u, v0.u());
        a0 = 6;
        a1 = 0;
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x248C74u, v0.u());
        a0 = s3;
        a1 = 0;
        jal(ctx, 0x248C84u, gen::fn_sub_21CCA0_0021cca0);
        a0 = v0;
        jal(ctx, 0x248C90u, gen::fn_sub_21CCE0_0021cce0);
        a0 = 1;
        a1 = v0;
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x248CA4u, v0.u());
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x17FB;
        jal(ctx, 0x248CB8u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 2;
        a1 = 68;
        jal(ctx, 0x248CC8u, gen::fn_RpSkyRenderStateSet_004d7f60);
        s0 = 0x960000;
        s0 = addiu(s0, 156);  // &0x96009C
        a0 = addiu(s2, 784);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C
        jalr(ctx, 0x248CF0u, v0.u());
        a0 = addiu(s2, 784);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C
        jalr(ctx, 0x248D10u, v0.u());
        a0 = s3;
        a1 = 67;
        jal(ctx, 0x248D20u, gen::fn_sub_21CCA0_0021cca0);
        a0 = v0;
        jal(ctx, 0x248D2Cu, gen::fn_sub_21CCE0_0021cce0);
        a0 = 1;
        a1 = v0;
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x248D40u, v0.u());
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x17FB;
        jal(ctx, 0x248D54u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 2;
        a1 = 68;
        jal(ctx, 0x248D64u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = addiu(s2, 16);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C
        jalr(ctx, 0x248D84u, v0.u());
        a0 = addiu(s2, 16);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C
        jalr(ctx, 0x248DA4u, v0.u());
        a0 = addiu(s2, 272);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C
        jalr(ctx, 0x248DC4u, v0.u());
        a0 = addiu(s2, 272);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C
        jalr(ctx, 0x248DE4u, v0.u());
        a0 = addiu(s2, 528);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C
        jalr(ctx, 0x248E04u, v0.u());
        a0 = addiu(s2, 528);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C
        jalr(ctx, 0x248E24u, v0.u());
        lw(a0, s2, bpm::kFontLine);
        a1 = 1;
        a2 = 0;
        jal(ctx, 0x248E38u, gen::fn_frFontDraw_003b1360);
        a0 = s3;
        a1 = 66;
        jal(ctx, 0x248E48u, gen::fn_sub_21CCA0_0021cca0);
        a0 = v0;
        jal(ctx, 0x248E54u, gen::fn_sub_21CCE0_0021cce0);
        a0 = 1;
        a1 = v0;
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x248E68u, v0.u());
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x17FB;
        jal(ctx, 0x248E7Cu, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 2;
        a1 = 68;
        jal(ctx, 0x248E8Cu, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = addiu(s2, 1040);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C
        jalr(ctx, 0x248EACu, v0.u());
        a0 = addiu(s2, 1040);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C
        jalr(ctx, 0x248ECCu, v0.u());
        a0 = addiu(s2, 1296);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C
        jalr(ctx, 0x248EECu, v0.u());
        a0 = addiu(s2, 1296);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C
        jalr(ctx, 0x248F0Cu, v0.u());
    }
    // 0x00248f14 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00248FC0 sub_248FC0 -- 360 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bpmOpen] Opens the bpm message: its font line a0 at (1600, 800), white, kept at +4; quads +16 / +272 (texture 67),
// +528 (68), +784 (0), +1040 / +1296 (66); +8 = 0, flag 1 on, 2 off.
// Arguments: a0 font line.
void sub_248FC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x00248fc0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, gp, kGpBpmWork);  // the battle panel message work (bpm_main.c) 0x7CE324
    if (v0 == 0) {
        // 0x00248fe4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6000);  // "bpm_main.c"
        a1 = 61;
        jal(ctx, 0x248FF0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00248ff8
    charge(ctx, 76);
    lw(s0, gp, kGpBpmWork);  // the battle panel message work (bpm_main.c) 0x7CE324
    a0 = 1;
    jal(ctx, 0x249000u, gen::fn_sub_21C3F0_0021c3f0);
    s2 = v0;
    a0 = s1;
    a1 = 1600;
    a2 = 800;
    jal(ctx, 0x249018u, gen::fn_frFontLineSetPos_003b0d70);
    mtc1(zero, f12);
    a0 = s1;
    jal(ctx, 0x249028u, gen::fn_sub_3B2C60_003b2c60);
    a0 = s1;
    a1 = si(-1);
    jal(ctx, 0x249038u, gen::fn_frFontLineSetRgba_003b0e20);
    sw(s1, s0, bpm::kFontLine);
    a0 = s2;
    a1 = 67;
    jal(ctx, 0x24904Cu, gen::fn_sub_21CCA0_0021cca0);
    s1 = v0;
    a0 = addiu(s0, 16);
    a1 = s1;
    jal(ctx, 0x249060u, gen::fn_sub_21D3B0_0021d3b0);
    a0 = addiu(s0, 272);
    a1 = s1;
    a2 = 1;
    jal(ctx, 0x249074u, gen::fn_sub_21E380_0021e380);
    a0 = s2;
    a1 = 68;
    jal(ctx, 0x249084u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s0, 528);
    a1 = v0;
    jal(ctx, 0x249094u, gen::fn_sub_21D3B0_0021d3b0);
    a0 = s2;
    a1 = 0;
    jal(ctx, 0x2490A4u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s0, 784);
    a1 = v0;
    jal(ctx, 0x2490B4u, gen::fn_sub_21D3B0_0021d3b0);
    a0 = s2;
    a1 = 66;
    jal(ctx, 0x2490C4u, gen::fn_sub_21CCA0_0021cca0);
    s1 = v0;
    a0 = addiu(s0, 1040);
    a1 = s1;
    jal(ctx, 0x2490D8u, gen::fn_sub_21D3B0_0021d3b0);
    a0 = addiu(s0, 1296);
    a1 = s1;
    jal(ctx, 0x2490E8u, gen::fn_sub_21D3B0_0021d3b0);
    sw(zero, s0, bpm::kFrame);
    lw(v1, s0, bpm::kFlags);
    a0 = v1 | 0x1;
    sw(a0, s0, bpm::kFlags);
    v1 = si(-3);
    v1 = a0 & v1;
    sw(v1, s0, bpm::kFlags);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00249180 sub_249180 -- 108 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [bpmClose] Closes the bpm message (releases the font line, clears flag 1) when open.
void sub_249180(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00249180
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, kGpBpmWork);  // the battle panel message work (bpm_main.c) 0x7CE324
    if (v1 == 0) {
        // 0x00249198
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6000);  // "bpm_main.c"
        a1 = 61;
        jal(ctx, 0x2491A4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002491ac
    charge(ctx, 5);
    lw(s0, gp, kGpBpmWork);  // the battle panel message work (bpm_main.c) 0x7CE324
    lw(v1, s0, bpm::kFlags);
    v1 = v1 & 0x1;
    if (v1 != 0) {
        // 0x002491c0
        charge(ctx, 6);
        jal(ctx, 0x2491C0u, gen::fn_sub_2491F0_002491f0);
        lw(a0, s0, bpm::kFlags);
        v1 = si(-2);
        v1 = a0 & v1;
        sw(v1, s0, bpm::kFlags);
    }
    // 0x002491d8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002491F0 sub_2491F0 -- 72 bytes; frame 0x10: ra sp+0x0
// Releases the bpm message's font line (+4) through sub_3B0170.
void sub_2491F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002491f0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpBpmWork);  // the battle panel message work (bpm_main.c) 0x7CE324
    if (v0 == 0) {
        // 0x00249204
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6000);  // "bpm_main.c"
        a1 = 61;
        jal(ctx, 0x249210u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00249218
    charge(ctx, 8);
    lw(v0, gp, kGpBpmWork);  // the battle panel message work (bpm_main.c) 0x7CE324
    lw(a0, v0, bpm::kFontLine);
    jal(ctx, 0x249220u, gen::fn_sub_3B0170_003b0170);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00249240 sub_249240 -- 16 bytes; leaf frame (no stack)
// Registers the battle panel work of $gp slot 0x7CE328.
// Arguments: a0 work.
void sub_249240(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, gp{ctx, 28};
    // 0x00249240
    enter(ctx, 4);  // entry check point + this block's cycles
    sw(zero, a0, 0);
    sw(a0, gp, kGpBpWork328);  // a battle panel work (registered by sub_249240) 0x7CE328
}

// 0x0024A6C0 sub_24A6C0 -- 16 bytes; leaf frame (no stack)
// Registers the battle panel work of $gp slot 0x7CE32C.
// Arguments: a0 work.
void sub_24A6C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, gp{ctx, 28};
    // 0x0024a6c0
    enter(ctx, 4);  // entry check point + this block's cycles
    sw(zero, a0, 0);
    sw(a0, gp, kGpBpWork32C);  // a battle panel work (registered by sub_24A6C0) 0x7CE32C
}

// 0x0024A6D0 sub_24A6D0 -- 12 bytes; leaf frame (no stack)
// Clears $gp slot 0x7CE32C.
void sub_24A6D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, gp{ctx, 28};
    // 0x0024a6d0
    enter(ctx, 3);  // entry check point + this block's cycles
    sw(zero, gp, kGpBpWork32C);  // a battle panel work (registered by sub_24A6C0) 0x7CE32C
}

// 0x00251050 sub_251050 -- 16 bytes; leaf frame (no stack)
// Registers the battle tutorial work (bp_tut.c, $gp slot 0x7CE344).
// Arguments: a0 work.
void sub_251050(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, gp{ctx, 28};
    // 0x00251050
    enter(ctx, 4);  // entry check point + this block's cycles
    sw(zero, a0, 0);
    sw(a0, gp, kGpBpTutWork);  // the battle tutorial work (bp_tut.c) 0x7CE344
}

// 0x00251060 sub_251060 -- 104 bytes; frame 0x10: ra sp+0x0
// Unregisters the bp_tut work (K_Assert line 73 when still active).
void sub_251060(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00251060
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpBpTutWork);  // the battle tutorial work (bp_tut.c) 0x7CE344
    if (v1 == 0) {
        // 0x00251074
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5696);  // "bp_tut.c"
        a1 = 57;
        jal(ctx, 0x251080u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00251088
    charge(ctx, 6);
    lw(v1, gp, kGpBpTutWork);  // the battle tutorial work (bp_tut.c) 0x7CE344
    lw(v1, v1, 0);
    v1 = nor(v1, 0);
    v1 = v1 & 0x1;
    if (v1 == 0) {
        // 0x002510a0
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5696);  // "bp_tut.c"
        a1 = 73;
        jal(ctx, 0x2510ACu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002510b4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    sw(zero, gp, kGpBpTutWork);  // the battle tutorial work (bp_tut.c) 0x7CE344
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00251A70 sub_251A70 -- 16 bytes; leaf frame (no stack)
// Registers the battle panel work of $gp slot 0x7CE348.
// Arguments: a0 work.
void sub_251A70(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, gp{ctx, 28};
    // 0x00251a70
    enter(ctx, 4);  // entry check point + this block's cycles
    sw(zero, a0, 0);
    sw(a0, gp, kGpBpWork348);  // a battle panel work (registered by sub_251A70) 0x7CE348
}

// 0x00251F20 sub_251F20 -- 16 bytes; leaf frame (no stack)
// Registers the battle panel work of $gp slot 0x7CE34C (bpo_main.c).
// Arguments: a0 work.
void sub_251F20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, gp{ctx, 28};
    // 0x00251f20
    enter(ctx, 4);  // entry check point + this block's cycles
    sw(zero, a0, 0);
    sw(a0, gp, kGpBpoWork);  // the bpo work (bpo_main.c) 0x7CE34C
}

// 0x00251F30 sub_251F30 -- 12 bytes; leaf frame (no stack)
// Clears $gp slot 0x7CE34C.
void sub_251F30(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, gp{ctx, 28};
    // 0x00251f30
    enter(ctx, 3);  // entry check point + this block's cycles
    sw(zero, gp, kGpBpoWork);  // the bpo work (bpo_main.c) 0x7CE34C
}

// 0x00252060 sub_252060 -- 132 bytes; frame 0x10: ra sp+0x0
// [bpoUpdate] Update of the bpo work: while active (flag 1) counts +4 up to 30 (then clears flag 1) and rebuilds its
// quads (sub_252340).
void sub_252060(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00252060
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpBpoWork);  // the bpo work (bpo_main.c) 0x7CE34C
    if (v1 == 0) {
        // 0x00252074
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5664);  // "bpo_main.c"
        a1 = 54;
        jal(ctx, 0x252080u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00252088
    charge(ctx, 6);
    lw(a1, gp, kGpBpoWork);  // the bpo work (bpo_main.c) 0x7CE34C
    lw(a0, a1, bpo::kFlags);
    v1 = nor(a0, 0);
    v1 = v1 & 0x1;
    if (v1 == 0) {
        // 0x002520a0
        charge(ctx, 4);
        lw(v0, a1, bpo::kFrame);
        at = slti(v0, 30);
        if (at == 0) {
            // 0x002520c0
            charge(ctx, 3);
            v0 = si(-2);
            v0 = a0 & v0;
            sw(v0, a1, bpo::kFlags);
        } else {
            // 0x002520b0
            charge(ctx, 4);
            v0 = addiu(v0, 1);
            sw(v0, a1, bpo::kFrame);
        }
        // 0x002520cc
        charge(ctx, 2);
        jal(ctx, 0x2520CCu, gen::fn_sub_252340_00252340);
    }
    // 0x002520d4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00252340 sub_252340 -- 2836 bytes; frame 0xC0: ra sp+0x80, s5 sp+0x70 (sq), s4 sp+0x60 (sq), s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [bpoBuildQuads] Builds the bpo (one-more / down banner) quads for the current frame: texture 57 / 58 by +8, the
// frame count +4 drives the slide and the sinf / cosf wobble, the alpha of +528 from the fade.
void sub_252340(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24};
    // 0x00252340
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(ra, sp, 0x80);
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
    lw(v0, gp, kGpBpoWork);  // the bpo work (bpo_main.c) 0x7CE34C
    if (v0 == 0) {
        // 0x00252380
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5664);  // "bpo_main.c"
        a1 = 54;
        jal(ctx, 0x25238Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00252394
    charge(ctx, 9);
    lw(s0, gp, kGpBpoWork);  // the bpo work (bpo_main.c) 0x7CE34C
    a0 = 1;
    jal(ctx, 0x25239Cu, gen::fn_sub_21C3F0_0021c3f0);
    s3 = v0;
    lw(v1, s0, bpo::kKind);
    v0 = 1;
    if (v1 == v0) {
        // 0x002523e4
        charge(ctx, 5);
        a0 = s3;
        a1 = 58;
        jal(ctx, 0x2523ECu, gen::fn_sub_21CCA0_0021cca0);
        s2 = v0;
    } else {
        // 0x002523b8
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x002523c8
            charge(ctx, 7);
            a0 = s3;
            a1 = 57;
            jal(ctx, 0x2523D0u, gen::fn_sub_21CCA0_0021cca0);
            s2 = v0;
        } else {
            // 0x002523c0
            charge(ctx, 2);
        }
    }
    // 0x002523f8
    charge(ctx, 4);
    lw(v0, s0, bpo::kFrame);
    at = slti(v0, 3);
    if (at == 0) {
        // 0x00252438
        charge(ctx, 3);
        at = slti(v0, 20);
        if (at == 0) {
            // 0x00252454
            charge(ctx, 3);
            at = slti(v0, 30);
            if (at == 0) {
                // 0x00252498
                charge(ctx, 1);
                mtc1(zero, f20);
            } else {
                // 0x00252460
                charge(ctx, 14);
                v0 = addiu(v0, -20);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x41200000;
                mtc1(v0, f0);
                div_s(f1, f1, f0);
                v0 = 0x3F800000;
                mtc1(v0, f0);
                sub_s(f20, f0, f1);
            }
        } else {
            // 0x00252444
            charge(ctx, 4);
            v0 = 0x3F800000;
            mtc1(v0, f20);
        }
    } else {
        // 0x00252408
        charge(ctx, 12);
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        v0 = 0x40400000;
        mtc1(v0, f0);
        div_s(f20, f1, f0);
    }
    // 0x0025249c
    charge(ctx, 39);
    v0 = 0x3FC00000;
    mtc1(v0, f22);
    v0 = 0x3F000000;
    mtc1(v0, f0);
    neg_s(f5, f0);
    lwc1(f0, s2, 12);
    cvt_s_w(f4, f0);
    mul_s(f0, f4, f5);
    v0 = 0x40000000;
    mtc1(v0, f3);
    div_s(f1, f0, f3);
    v0 = 0x43050000;
    mtc1(v0, f0);
    add_s(f0, f0, f1);
    swc1(f0, sp, 0x90);
    lwc1(f0, s2, 16);
    cvt_s_w(f2, f0);
    mul_s(f0, f2, f5);
    div_s(f1, f0, f3);
    v0 = 0x43120000;
    mtc1(v0, f0);
    add_s(f0, f0, f1);
    swc1(f0, sp, 0x94);
    mul_s(f0, f4, f22);
    swc1(f0, sp, 0x98);
    mul_s(f0, f2, f22);
    swc1(f0, sp, 0x9C);
    a0 = addiu(s0, 16);
    a1 = addiu(sp, 0x90);
    jal(ctx, 0x252520u, gen::fn_sub_21D8E0_0021d8e0);
    lw(v1, s0, bpo::kKind);
    v0 = 1;
    if (v1 == v0) {
        // 0x00252568
        charge(ctx, 6);
        lbu(v0, s2, 28);
        sb(v0, sp, 0xBC);
        lbu(v0, s2, 29);
        sb(v0, sp, 0xBD);
        lbu(v0, s2, 30);
        sb(v0, sp, 0xBE);
    } else {
        // 0x00252538
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x00252548
            charge(ctx, 8);
            v0 = 102;
            sb(v0, sp, 0xBC);
            v0 = 153;
            sb(v0, sp, 0xBD);
            v0 = 255;
            sb(v0, sp, 0xBE);
        } else {
            // 0x00252540
            charge(ctx, 2);
        }
    }
    // 0x00252580
    charge(ctx, 10);
    v0 = 0x437F0000;
    mtc1(v0, f0);
    mul_s(f1, f0, f20);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x002525c0
        charge(ctx, 6);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x002525a8
        charge(ctx, 6);
        cvt_w_s(f0, f1);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x002525d8
    charge(ctx, 9);
    sb(v1, sp, 0xBF);
    a0 = addiu(s0, 16);
    a1 = addiu(sp, 0xBC);
    jal(ctx, 0x2525E4u, gen::fn_sub_21D950_0021d950);
    lw(v1, s0, bpo::kKind);
    v0 = 1;
    if (v1 == v0) {
        // 0x00252654
        charge(ctx, 12);
        lwc1(f0, s0, bpo::kFrame);
        cvt_s_w(f1, f0);
        v0 = 0x41F00000;
        mtc1(v0, f0);
        div_s(f3, f1, f0);
        lwc1(f2, gp, -32656);  // 0x7CAD60
        lwc1(f1, gp, -31776);  // 0x7CB0D0
        mtc1(zero, f0);
        adda_s(f0, f1);
        madd_s(f22, f2, f3);
    } else {
        // 0x002525fc
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x0025260c
            charge(ctx, 18);
            lwc1(f0, s0, bpo::kFrame);
            cvt_s_w(f1, f0);
            v0 = 0x41F00000;
            mtc1(v0, f0);
            div_s(f1, f1, f0);
            lwc1(f3, gp, -32656);  // 0x7CAD60
            v0 = 0x3F800000;
            mtc1(v0, f0);
            sub_s(f2, f0, f1);
            lwc1(f1, gp, -31776);  // 0x7CB0D0
            mtc1(zero, f0);
            adda_s(f0, f1);
            madd_s(f22, f3, f2);
        } else {
            // 0x00252604
            charge(ctx, 2);
        }
    }
    // 0x00252684
    charge(ctx, 3);
    v0 = 1;
    if (v1 == v0) {
        // 0x002526e0
        charge(ctx, 14);
        lwc1(f0, s0, bpo::kFrame);
        cvt_s_w(f1, f0);
        v0 = 0x41F00000;
        mtc1(v0, f0);
        div_s(f3, f1, f0);
        v0 = lui(0xC1A0);
        mtc1(v0, f2);
        v0 = 0x41200000;
        mtc1(v0, f1);
        mtc1(zero, f0);
        adda_s(f0, f1);
        madd_s(f21, f2, f3);
    } else {
        // 0x00252690
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x002526a0
            charge(ctx, 16);
            lwc1(f0, s0, bpo::kFrame);
            cvt_s_w(f1, f0);
            v0 = 0x41F00000;
            mtc1(v0, f0);
            div_s(f1, f1, f0);
            v0 = 0x41A00000;
            mtc1(v0, f0);
            mul_s(f1, f0, f1);
            v0 = 0x41200000;
            mtc1(v0, f0);
            sub_s(f21, f1, f0);
        } else {
            // 0x00252698
            charge(ctx, 2);
        }
    }
    // 0x00252718
    charge(ctx, 4);
    lw(v0, s0, bpo::kFrame);
    at = slti(v0, 3);
    if (at == 0) {
        // 0x00252758
        charge(ctx, 3);
        at = slti(v0, 20);
        if (at == 0) {
            // 0x00252774
            charge(ctx, 3);
            at = slti(v0, 30);
            if (at == 0) {
                // 0x002527b8
                charge(ctx, 1);
                mtc1(zero, f20);
            } else {
                // 0x00252780
                charge(ctx, 14);
                v0 = addiu(v0, -20);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x41200000;
                mtc1(v0, f0);
                div_s(f1, f1, f0);
                v0 = 0x3F800000;
                mtc1(v0, f0);
                sub_s(f20, f0, f1);
            }
        } else {
            // 0x00252764
            charge(ctx, 4);
            v0 = 0x3F800000;
            mtc1(v0, f20);
        }
    } else {
        // 0x00252728
        charge(ctx, 12);
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        v0 = 0x40400000;
        mtc1(v0, f0);
        div_s(f20, f1, f0);
    }
    // 0x002527bc
    charge(ctx, 19);
    sw(zero, sp, 0x90);
    sw(zero, sp, 0x94);
    lwc1(f0, s2, 12);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x98);
    sw(zero, sp, 0x9C);
    swc1(f0, sp, 0xA0);
    lwc1(f0, s2, 16);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xA4);
    sw(zero, sp, 0xA8);
    swc1(f0, sp, 0xAC);
    v1 = 0;
    v0 = 0x42FE0000;
    mtc1(v0, f2);
    v0 = 0x42740000;
    mtc1(v0, f1);
    for (;;) {
        // 0x00252830
        charge(ctx, 3);
        v0 = slti(v1, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00252808
        charge(ctx, 10);
        v0 = sll(v1, 3);
        v0 = addu(v0, sp);
        v0 = addiu(v0, 144);
        lwc1(f0, v0, 0);
        sub_s(f0, f0, f2);
        swc1(f0, v0, 0);
        lwc1(f0, v0, 4);
        sub_s(f0, f0, f1);
        swc1(f0, v0, 4);
        v1 = addiu(v1, 1);
    }
    // 0x0025283c
    charge(ctx, 3);
    v1 = 0;
    for (;;) {
        // 0x00252870
        charge(ctx, 3);
        v0 = slti(v1, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00252848
        charge(ctx, 10);
        v0 = sll(v1, 3);
        v0 = addu(v0, sp);
        v0 = addiu(v0, 144);
        lwc1(f0, v0, 0);
        mul_s(f0, f0, f22);
        swc1(f0, v0, 0);
        lwc1(f0, v0, 4);
        mul_s(f0, f0, f22);
        swc1(f0, v0, 4);
        v1 = addiu(v1, 1);
    }
    // 0x0025287c
    charge(ctx, 13);
    s1 = 0;
    v0 = 0x43B40000;
    mtc1(v0, f0);
    div_s(f1, f21, f0);
    v0 = 0x40000000;
    mtc1(v0, f0);
    mul_s(f1, f0, f1);
    lwc1(f0, gp, -32184);  // 0x7CAF38
    mul_s(f24, f0, f1);
    for (;;) {
        // 0x00252924
        charge(ctx, 3);
        v0 = slti(s1, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002528b0
        charge(ctx, 29);
        v0 = sll(s1, 3);
        v0 = addu(v0, sp);
        s5 = addiu(v0, 144);
        s4 = addiu(s5, 4);
        mov_s(f12, f24);
        jal(ctx, 0x2528C4u, gen::fn_sinf_0052e878);
        mov_s(f22, f0);
        lwc1(f21, s4, 0);
        mov_s(f12, f24);
        jal(ctx, 0x2528D8u, gen::fn_cosf_0052e6d8);
        lwc1(f1, s5, 0);
        mula_s(f1, f0);
        msub_s(f23, f21, f22);
        mov_s(f12, f24);
        jal(ctx, 0x2528F0u, gen::fn_sinf_0052e878);
        mov_s(f22, f0);
        lwc1(f21, s5, 0);
        mov_s(f12, f24);
        jal(ctx, 0x252904u, gen::fn_cosf_0052e6d8);
        lwc1(f1, s4, 0);
        mula_s(f1, f0);
        madd_s(f0, f21, f22);
        swc1(f23, s5, 0);
        swc1(f0, s4, 0);
        s1 = addiu(s1, 1);
    }
    // 0x00252930
    charge(ctx, 7);
    v1 = 0;
    v0 = 0x42FE0000;
    mtc1(v0, f2);
    v0 = 0x42740000;
    mtc1(v0, f1);
    for (;;) {
        // 0x00252974
        charge(ctx, 3);
        v0 = slti(v1, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0025294c
        charge(ctx, 10);
        v0 = sll(v1, 3);
        v0 = addu(v0, sp);
        v0 = addiu(v0, 144);
        lwc1(f0, v0, 0);
        add_s(f0, f0, f2);
        swc1(f0, v0, 0);
        lwc1(f0, v0, 4);
        add_s(f0, f0, f1);
        swc1(f0, v0, 4);
        v1 = addiu(v1, 1);
    }
    // 0x00252980
    charge(ctx, 7);
    v1 = 0;
    v0 = 0x43050000;
    mtc1(v0, f2);
    v0 = 0x43120000;
    mtc1(v0, f1);
    for (;;) {
        // 0x002529c4
        charge(ctx, 3);
        v0 = slti(v1, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0025299c
        charge(ctx, 10);
        v0 = sll(v1, 3);
        v0 = addu(v0, sp);
        v0 = addiu(v0, 144);
        lwc1(f0, v0, 0);
        add_s(f0, f0, f2);
        swc1(f0, v0, 0);
        lwc1(f0, v0, 4);
        add_s(f0, f0, f1);
        swc1(f0, v0, 4);
        v1 = addiu(v1, 1);
    }
    // 0x002529d0
    charge(ctx, 8);
    a0 = addiu(s0, 272);
    a1 = addiu(sp, 0x90);
    jal(ctx, 0x2529D8u, gen::fn_sub_21D890_0021d890);
    lw(v1, s0, bpo::kKind);
    v0 = 1;
    if (v1 == v0) {
        // 0x00252a18
        charge(ctx, 4);
        v0 = 153;
        sb(v0, sp, 0xBC);
        sb(zero, sp, 0xBD);
        sb(zero, sp, 0xBE);
    } else {
        // 0x002529f0
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x00252a00
            charge(ctx, 6);
            sb(zero, sp, 0xBC);
            sb(zero, sp, 0xBD);
            v0 = 204;
            sb(v0, sp, 0xBE);
        } else {
            // 0x002529f8
            charge(ctx, 2);
        }
    }
    // 0x00252a28
    charge(ctx, 13);
    v0 = 0x3F000000;
    mtc1(v0, f1);
    v0 = 0x437F0000;
    mtc1(v0, f0);
    mul_s(f0, f0, f20);
    mul_s(f1, f1, f0);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x00252a74
        charge(ctx, 6);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x00252a5c
        charge(ctx, 6);
        cvt_w_s(f0, f1);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x00252a8c
    charge(ctx, 9);
    sb(v1, sp, 0xBF);
    a0 = addiu(s0, 272);
    a1 = addiu(sp, 0xBC);
    jal(ctx, 0x252A98u, gen::fn_sub_21D950_0021d950);
    lw(v1, s0, bpo::kKind);
    v0 = 1;
    if (v1 == v0) {
        // 0x00252adc
        charge(ctx, 5);
        a0 = s3;
        a1 = 58;
        jal(ctx, 0x252AE4u, gen::fn_sub_21CCA0_0021cca0);
        s2 = v0;
    } else {
        // 0x00252ab0
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x00252ac0
            charge(ctx, 7);
            a0 = s3;
            a1 = 57;
            jal(ctx, 0x252AC8u, gen::fn_sub_21CCA0_0021cca0);
            s2 = v0;
        } else {
            // 0x00252ab8
            charge(ctx, 2);
        }
    }
    // 0x00252af0
    charge(ctx, 3);
    lw(a0, s0, bpo::kFrame);
    if (i64(a0) >= 0) {
        // 0x00252b08
        charge(ctx, 3);
        at = slti(a0, 4);
        if (at == 0) {
            // 0x00252b44
            charge(ctx, 3);
            at = slti(a0, 20);
            if (at == 0) {
                // 0x00252b60
                charge(ctx, 3);
                at = slti(a0, 30);
                if (at == 0) {
                    // 0x00252ba4
                    charge(ctx, 1);
                    mtc1(zero, f20);
                } else {
                    // 0x00252b6c
                    charge(ctx, 14);
                    v0 = addiu(a0, -20);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    v0 = 0x41200000;
                    mtc1(v0, f0);
                    div_s(f1, f1, f0);
                    v0 = 0x3F800000;
                    mtc1(v0, f0);
                    sub_s(f20, f0, f1);
                }
            } else {
                // 0x00252b50
                charge(ctx, 4);
                v0 = 0x3F800000;
                mtc1(v0, f20);
            }
        } else {
            // 0x00252b14
            charge(ctx, 12);
            mtc1(a0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x40800000;
            mtc1(v0, f0);
            div_s(f20, f1, f0);
        }
    } else {
        // 0x00252afc
        charge(ctx, 3);
        mtc1(zero, f20);
    }
    // 0x00252ba8
    charge(ctx, 5);
    mtc1(zero, f6);
    lw(v1, s0, bpo::kKind);
    v0 = 1;
    if (v1 == v0) {
        // 0x00252c40
        charge(ctx, 2);
        if (i64(a0) >= 0) {
            // 0x00252c58
            charge(ctx, 3);
            at = slti(a0, 4);
            if (at == 0) {
                // 0x00252cb4
                charge(ctx, 2);
                v0 = 0x3FC00000;
                mtc1(v0, f6);
            } else {
                // 0x00252c64
                charge(ctx, 20);
                mtc1(a0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x40800000;
                mtc1(v0, f0);
                div_s(f1, f1, f0);
                v0 = lui(0xBF80);
                mtc1(v0, f2);
                v0 = 0x3F800000;
                mtc1(v0, f0);
                sub_s(f1, f0, f1);
                v0 = 0x3FC00000;
                mtc1(v0, f0);
                adda_s(f6, f0);
                madd_s(f6, f2, f1);
            }
        } else {
            // 0x00252c48
            charge(ctx, 4);
            v0 = 0x3F800000;
            mtc1(v0, f6);
        }
    } else {
        // 0x00252bbc
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x00252bcc
            charge(ctx, 2);
            if (i64(a0) >= 0) {
                // 0x00252be4
                charge(ctx, 3);
                at = slti(a0, 4);
                if (at == 0) {
                    // 0x00252c30
                    charge(ctx, 4);
                    v0 = 0x3FC00000;
                    mtc1(v0, f6);
                } else {
                    // 0x00252bf0
                    charge(ctx, 16);
                    mtc1(a0, f0);
                    cvt_s_w(f1, f0);
                    v0 = 0x40800000;
                    mtc1(v0, f0);
                    div_s(f2, f1, f0);
                    v0 = 0x3FC00000;
                    mtc1(v0, f1);
                    v0 = 0x3F800000;
                    mtc1(v0, f0);
                    sub_s(f0, f0, f2);
                    add_s(f6, f1, f0);
                }
            } else {
                // 0x00252bd4
                charge(ctx, 4);
                v0 = 0x3F800000;
                mtc1(v0, f6);
            }
        } else {
            // 0x00252bc4
            charge(ctx, 2);
        }
    }
    // 0x00252cbc
    charge(ctx, 38);
    v0 = 0x3F800000;
    mtc1(v0, f0);
    sub_s(f0, f6, f0);
    neg_s(f5, f0);
    lwc1(f0, s2, 12);
    cvt_s_w(f4, f0);
    mul_s(f0, f4, f5);
    v0 = 0x40000000;
    mtc1(v0, f3);
    div_s(f1, f0, f3);
    v0 = 0x43050000;
    mtc1(v0, f0);
    add_s(f0, f0, f1);
    swc1(f0, sp, 0x90);
    lwc1(f0, s2, 16);
    cvt_s_w(f2, f0);
    mul_s(f0, f2, f5);
    div_s(f1, f0, f3);
    v0 = 0x43120000;
    mtc1(v0, f0);
    add_s(f0, f0, f1);
    swc1(f0, sp, 0x94);
    mul_s(f0, f4, f6);
    swc1(f0, sp, 0x98);
    mul_s(f0, f2, f6);
    swc1(f0, sp, 0x9C);
    a0 = addiu(s0, 528);
    a1 = addiu(sp, 0x90);
    jal(ctx, 0x252D3Cu, gen::fn_sub_21D8E0_0021d8e0);
    lw(v1, s0, bpo::kKind);
    v0 = 1;
    if (v1 == v0) {
        // 0x00252d84
        charge(ctx, 6);
        lbu(v0, s2, 28);
        sb(v0, sp, 0xBC);
        lbu(v0, s2, 29);
        sb(v0, sp, 0xBD);
        lbu(v0, s2, 30);
        sb(v0, sp, 0xBE);
    } else {
        // 0x00252d54
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x00252d64
            charge(ctx, 8);
            v0 = 102;
            sb(v0, sp, 0xBC);
            v0 = 153;
            sb(v0, sp, 0xBD);
            v0 = 255;
            sb(v0, sp, 0xBE);
        } else {
            // 0x00252d5c
            charge(ctx, 2);
        }
    }
    // 0x00252d9c
    charge(ctx, 10);
    v0 = 0x437F0000;
    mtc1(v0, f0);
    mul_s(f1, f0, f20);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x00252ddc
        charge(ctx, 6);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x00252dc4
        charge(ctx, 6);
        cvt_w_s(f0, f1);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x00252df4
    charge(ctx, 24);
    sb(v1, sp, 0xBF);
    a0 = addiu(s0, 528);
    a1 = addiu(sp, 0xBC);
    jal(ctx, 0x252E00u, gen::fn_sub_21D950_0021d950);
    lw(a0, s0, bpo::kFlags);
    v1 = si(-3);
    v1 = a0 & v1;
    sw(v1, s0, bpo::kFlags);
    ld(ra, sp, 0x80);
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
    sp = addiu(sp, 0xC0);
}

// 0x00252E60 sub_252E60 -- 20 bytes; leaf frame (no stack)
// Registers the battle panel work of $gp slot 0x7CE350 (bpd_main.c): clears +0 / +2900.
// Arguments: a0 work.
void sub_252E60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, gp{ctx, 28};
    // 0x00252e60
    enter(ctx, 5);  // entry check point + this block's cycles
    sw(zero, a0, 0);
    sw(zero, a0, 2900);
    sw(a0, gp, kGpBpdWork);  // the bpd work (bpd_main.c) 0x7CE350
}

// 0x00252E80 sub_252E80 -- 12 bytes; leaf frame (no stack)
// Clears $gp slot 0x7CE350.
void sub_252E80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, gp{ctx, 28};
    // 0x00252e80
    enter(ctx, 3);  // entry check point + this block's cycles
    sw(zero, gp, kGpBpdWork);  // the bpd work (bpd_main.c) 0x7CE350
}

// 0x00252E90 sub_252E90 -- 72 bytes; frame 0x10: ra sp+0x0
// Sets flag 1 of the bpd work.
void sub_252E90(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00252e90
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpBpdWork);  // the bpd work (bpd_main.c) 0x7CE350
    if (v1 == 0) {
        // 0x00252ea4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5648);  // "bpd_main.c"
        a1 = 37;
        jal(ctx, 0x252EB0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00252eb8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    lw(a0, gp, kGpBpdWork);  // the bpd work (bpd_main.c) 0x7CE350
    lw(v1, a0, bpd::kFlags);
    v1 = v1 | 0x1;
    sw(v1, a0, bpd::kFlags);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00252EE0 sub_252EE0 -- 76 bytes; frame 0x10: ra sp+0x0
// Clears flag 1 of the bpd work.
void sub_252EE0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00252ee0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpBpdWork);  // the bpd work (bpd_main.c) 0x7CE350
    if (v1 == 0) {
        // 0x00252ef4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5648);  // "bpd_main.c"
        a1 = 37;
        jal(ctx, 0x252F00u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00252f08 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    lw(a1, gp, kGpBpdWork);  // the bpd work (bpd_main.c) 0x7CE350
    lw(a0, a1, bpd::kFlags);
    v1 = si(-2);
    v1 = a0 & v1;
    sw(v1, a1, bpd::kFlags);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00252F30 sub_252F30 -- 892 bytes; frame 0xD0: ra sp+0x80, s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [bpdDraw] Draw of the bpd work: for each enemy unit, its head point (sub_2807A0), projected, and a marker quad
// (sinf bob) by its bad status.
void sub_252F30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23};
    // 0x00252f30
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0xD0);
    sd(ra, sp, 0x80);
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
    lw(v0, gp, kGpBpdWork);  // the bpd work (bpd_main.c) 0x7CE350
    if (v0 == 0) {
        // 0x00252f70
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5648);  // "bpd_main.c"
        a1 = 37;
        jal(ctx, 0x252F7Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00252f84
    charge(ctx, 11);
    lw(s0, gp, kGpBpdWork);  // the bpd work (bpd_main.c) 0x7CE350
    a0 = 1;
    jal(ctx, 0x252F8Cu, gen::fn_sub_21C3F0_0021c3f0);
    s4 = v0;
    lw(s5, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v1, s0, bpd::kFlags);
    a0 = nor(v1, 0);
    v1 = a0 & 0x2;
    if (v1 == 0) {
        // 0x00252fb0
        charge(ctx, 3);
        v1 = a0 & 0x1;
        if (v1 == 0) {
            // 0x00252fbc
            charge(ctx, 11);
            lw(v1, s0, 2900);
            a0 = addiu(v1, 1);
            sw(a0, s0, 2900);
            v1 = 15;
            div(a0, v1);
            mfhi(v1);
            sw(v1, s0, 2900);
            s1 = 0;
            s3 = 0;
            for (;;) {
                // 0x002530ec
                charge(ctx, 3);
                v1 = slti(s3, 4);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00252fe8
                charge(ctx, 5);
                v1 = sll(s3, 3);
                v1 = addu(s5, v1);
                lw(s2, v1, 336);
                for (;;) {
                    // 0x002530e0
                    charge(ctx, 2);
                    if (s2 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00252ffc
                    charge(ctx, 5);
                    lw(v1, s2, 156);
                    v1 = nor(v1, 0);
                    v1 = v1 & 0x8;
                    if (v1 == 0) {
                        // 0x00253010
                        charge(ctx, 10);
                        a0 = s2;
                        a1 = addiu(sp, 0xB0);
                        jal(ctx, 0x253018u, gen::fn_sub_2807A0_002807a0);
                        a0 = addiu(sp, 0xB0);
                        a1 = addiu(sp, 0xC0);
                        jal(ctx, 0x253028u, gen::fn_sub_2D20A0_002d20a0);
                        if (v0 != 0) {
                            // 0x00253038
                            charge(ctx, 6);
                            lw(a0, s2, 2604);
                            a1 = 0x100000;
                            jal(ctx, 0x253040u, gen::fn_datCalcChkBadStatus_00300580);
                            if (v0 != 0) {
                                // 0x00253050
                                charge(ctx, 17);
                                v0 = sll(s1, 3);
                                v0 = addu(v0, s1);
                                v0 = sll(v0, 5);
                                v1 = addu(s0, v0);
                                s6 = addiu(v1, 16);
                                lw(v0, s2, 168);
                                sw(v0, v1, 20);
                                lwc1(f0, sp, 0xC0);
                                swc1(f0, v1, 288);
                                lwc1(f0, sp, 0xC4);
                                swc1(f0, v1, 292);
                                a0 = s2;
                                jal(ctx, 0x253080u, gen::fn_sub_27F930_0027f930);
                                lbu(v1, v0, 3);
                                if (i64(v1) < 0) {
                                    // 0x002530a8
                                    charge(ctx, 7);
                                    a0 = srl(v1, 1);
                                    v1 = v1 & 0x1;
                                    a0 = a0 | v1;
                                    mtc1(a0, f0);
                                    cvt_s_w(f1, f0);
                                    add_s(f1, f1, f1);
                                } else {
                                    // 0x00253094
                                    charge(ctx, 5);
                                    mtc1(v1, f0);
                                    cvt_s_w(f1, f0);
                                }
                                // 0x002530c4
                                charge(ctx, 6);
                                v1 = 0x437F0000;
                                mtc1(v1, f0);
                                div_s(f0, f1, f0);
                                swc1(f0, s6, 280);
                                s1 = addiu(s1, 1);
                            }
                        }
                    }
                    // 0x002530dc
                    charge(ctx, 1);
                    lw(s2, s2, 2612);
                }
                // 0x002530e8
                charge(ctx, 1);
                s3 = addiu(s3, 1);
            }
            // 0x002530f8
            charge(ctx, 4);
            sw(s1, s0, 2896);
            s2 = 0;
            for (;;) {
                // 0x00253260
                charge(ctx, 4);
                lw(v1, s0, 2896);
                v1 = slt(s2, v1);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00253108
                charge(ctx, 68);
                v0 = sll(s2, 3);
                v0 = addu(v0, s2);
                v0 = sll(v0, 5);
                v0 = addu(s0, v0);
                s1 = addiu(v0, 16);
                lwc1(f21, v0, 288);
                lwc1(f20, v0, 292);
                lwc1(f22, v0, 296);
                lwc1(f0, s0, 2900);
                cvt_s_w(f1, f0);
                v0 = 0x41700000;
                mtc1(v0, f0);
                div_s(f1, f1, f0);
                v0 = 0x40000000;
                mtc1(v0, f0);
                mul_s(f1, f0, f1);
                lwc1(f0, gp, -32184);  // 0x7CAF38
                mul_s(f12, f0, f1);
                jal(ctx, 0x253158u, gen::fn_sinf_0052e878);
                v0 = 0x40400000;
                mtc1(v0, f1);
                mul_s(f23, f1, f0);
                a0 = s4;
                a1 = 76;
                jal(ctx, 0x253178u, gen::fn_sub_21CCA0_0021cca0);
                lwc1(f0, v0, 12);
                cvt_s_w(f3, f0);
                v1 = 0x40000000;
                mtc1(v1, f1);
                div_s(f0, f3, f1);
                sub_s(f0, f21, f0);
                swc1(f0, sp, 0x90);
                lwc1(f0, v0, 16);
                cvt_s_w(f2, f0);
                div_s(f0, f2, f1);
                sub_s(f1, f20, f0);
                v0 = 0x41200000;
                mtc1(v0, f0);
                sub_s(f0, f1, f0);
                add_s(f0, f23, f0);
                swc1(f0, sp, 0x94);
                swc1(f3, sp, 0x98);
                swc1(f2, sp, 0x9C);
                a0 = addiu(s1, 16);
                a1 = addiu(sp, 0x90);
                jal(ctx, 0x2531D8u, gen::fn_sub_21D8E0_0021d8e0);
                v0 = 255;
                sb(v0, sp, 0xCC);
                sb(v0, sp, 0xCD);
                sb(v0, sp, 0xCE);
                v0 = 0x437F0000;
                mtc1(v0, f0);
                mul_s(f1, f0, f22);
                v0 = 0x4F000000;
                mtc1(v0, f0);
                c_le_s(f0, f1);
                if (cond(ctx)) {
                    // 0x00253230
                    charge(ctx, 6);
                    sub_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    v0 = lui(0x8000);
                    v1 = v1 | v0;
                    v1 = v1 & 0xFF;
                } else {
                    // 0x00253218
                    charge(ctx, 6);
                    cvt_w_s(f0, f1);
                    mfc1(v1, f0);
                    v1 = v1 & 0xFF;
                }
                // 0x00253248
                charge(ctx, 6);
                sb(v1, sp, 0xCF);
                a0 = addiu(s1, 16);
                a1 = addiu(sp, 0xCC);
                jal(ctx, 0x253254u, gen::fn_sub_21D950_0021d950);
                s2 = addiu(s2, 1);
            }
        }
    }
    // 0x00253270 (the shared epilogue, written out on this path)
    charge(ctx, 15);
    ld(ra, sp, 0x80);
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
    sp = addiu(sp, 0xD0);
}

// 0x0025BDF0 sub_25BDF0 -- 16 bytes; leaf frame (no stack)
// Registers the battle dialog work (bp_dialog.c, $gp slot 0x7CE368).
// Arguments: a0 work.
void sub_25BDF0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, gp{ctx, 28};
    // 0x0025bdf0
    enter(ctx, 4);  // entry check point + this block's cycles
    sw(zero, a0, 0);
    sw(a0, gp, kGpBpDialogWork);  // the battle dialog work (bp_dialog.c) 0x7CE368
}

// 0x0025BE00 sub_25BE00 -- 92 bytes; frame 0x10: ra sp+0x0
// Unregisters the bp_dialog work, releasing its font line (+4) when open (flag 1).
void sub_25BE00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0025be00
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpBpDialogWork);  // the battle dialog work (bp_dialog.c) 0x7CE368
    if (v1 == 0) {
        // 0x0025be14
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5160);  // "bp_dialog.c"
        a1 = 60;
        jal(ctx, 0x25BE20u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0025be28
    charge(ctx, 5);
    lw(a0, gp, kGpBpDialogWork);  // the battle dialog work (bp_dialog.c) 0x7CE368
    lw(v1, a0, dlg::kFlags);
    v1 = v1 & 0x1;
    if (v1 != 0) {
        // 0x0025be3c
        charge(ctx, 3);
        lw(a0, a0, dlg::kLines);
        jal(ctx, 0x25BE40u, gen::fn_sub_3B0170_003b0170);
    }
    // 0x0025be48 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    sw(zero, gp, kGpBpDialogWork);  // the battle dialog work (bp_dialog.c) 0x7CE368
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0025C110 sub_25C110 -- 116 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Sets flag 8 of the open bp_dialog (K_Assert line 167 when not open).
void sub_25C110(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0025c110
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, kGpBpDialogWork);  // the battle dialog work (bp_dialog.c) 0x7CE368
    if (v1 == 0) {
        // 0x0025c128
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5160);  // "bp_dialog.c"
        a1 = 60;
        jal(ctx, 0x25C134u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0025c13c
    charge(ctx, 5);
    lw(s0, gp, kGpBpDialogWork);  // the battle dialog work (bp_dialog.c) 0x7CE368
    lw(v1, s0, dlg::kFlags);
    v1 = v1 & 0x1;
    if (v1 == 0) {
        // 0x0025c150
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5160);  // "bp_dialog.c"
        a1 = 167;
        jal(ctx, 0x25C15Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0025c164 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    lw(v1, s0, dlg::kFlags);
    v1 = v1 | 0x8;
    sw(v1, s0, dlg::kFlags);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0025C190 sub_25C190 -- 68 bytes; frame 0x10: ra sp+0x0
// The bp_dialog's flag 2.
void sub_25C190(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0025c190
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpBpDialogWork);  // the battle dialog work (bp_dialog.c) 0x7CE368
    if (v0 == 0) {
        // 0x0025c1a4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5160);  // "bp_dialog.c"
        a1 = 60;
        jal(ctx, 0x25C1B0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0025c1b8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v0, gp, kGpBpDialogWork);  // the battle dialog work (bp_dialog.c) 0x7CE368
    lw(v0, v0, dlg::kFlags);
    v0 = v0 & 0x2;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0025C1E0 sub_25C1E0 -- 64 bytes; frame 0x10: ra sp+0x0
// The bp_dialog's word +16 (the answer).
void sub_25C1E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0025c1e0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpBpDialogWork);  // the battle dialog work (bp_dialog.c) 0x7CE368
    if (v0 == 0) {
        // 0x0025c1f4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5160);  // "bp_dialog.c"
        a1 = 60;
        jal(ctx, 0x25C200u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0025c208 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    lw(v0, gp, kGpBpDialogWork);  // the battle dialog work (bp_dialog.c) 0x7CE368
    lw(v0, v0, dlg::kAnswer);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0025C9C0 sub_25C9C0 -- 868 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bpDialogDraw] Draw of the bp_dialog when open: render states, the window quads +32 / +288 (texture +800), +544
// (texture +804), +816 (89), +1072 (90) and the three font lines +4 / +8 / +12.
void sub_25C9C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0025c9c0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBpDialogWork);  // the battle dialog work (bp_dialog.c) 0x7CE368
    if (v0 == 0) {
        // 0x0025c9e4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5160);  // "bp_dialog.c"
        a1 = 60;
        jal(ctx, 0x25C9F0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0025c9f8
    charge(ctx, 10);
    lw(s2, gp, kGpBpDialogWork);  // the battle dialog work (bp_dialog.c) 0x7CE368
    a0 = 0;
    jal(ctx, 0x25CA00u, gen::fn_sub_21C3F0_0021c3f0);
    s3 = v0;
    lw(v1, s2, dlg::kFlags);
    v1 = nor(v1, 0);
    v1 = v1 & 0x1;
    if (v1 == 0) {
        // 0x0025ca20
        charge(ctx, 185);
        s1 = 0x960000;
        s1 = addiu(s1, 144);  // &pfn_RwRenderStateSet
        a0 = 9;
        a1 = 2;
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x25CA34u, v0.u());
        a0 = 20;
        a1 = 2;
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x25CA48u, v0.u());
        a0 = 8;
        a1 = 0;
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x25CA5Cu, v0.u());
        a0 = 6;
        a1 = 0;
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x25CA70u, v0.u());
        a0 = s3;
        lw(a1, s2, dlg::kTexA);
        jal(ctx, 0x25CA80u, gen::fn_sub_21CCA0_0021cca0);
        a0 = v0;
        jal(ctx, 0x25CA8Cu, gen::fn_sub_21CCE0_0021cce0);
        a0 = 1;
        a1 = v0;
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x25CAA0u, v0.u());
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x17FB;
        jal(ctx, 0x25CAB4u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 2;
        a1 = 68;
        jal(ctx, 0x25CAC4u, gen::fn_RpSkyRenderStateSet_004d7f60);
        s0 = 0x960000;
        s0 = addiu(s0, 156);  // &0x96009C
        a0 = addiu(s2, 32);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C
        jalr(ctx, 0x25CAECu, v0.u());
        a0 = addiu(s2, 32);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C
        jalr(ctx, 0x25CB0Cu, v0.u());
        a0 = addiu(s2, 288);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C
        jalr(ctx, 0x25CB2Cu, v0.u());
        a0 = addiu(s2, 288);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C
        jalr(ctx, 0x25CB4Cu, v0.u());
        a0 = s3;
        lw(a1, s2, dlg::kTexB);
        jal(ctx, 0x25CB5Cu, gen::fn_sub_21CCA0_0021cca0);
        a0 = v0;
        jal(ctx, 0x25CB68u, gen::fn_sub_21CCE0_0021cce0);
        a0 = 1;
        a1 = v0;
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x25CB7Cu, v0.u());
        a0 = addiu(s2, 544);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C
        jalr(ctx, 0x25CB9Cu, v0.u());
        a0 = addiu(s2, 544);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C
        jalr(ctx, 0x25CBBCu, v0.u());
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x17FB;
        jal(ctx, 0x25CBD0u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 2;
        a1 = 68;
        jal(ctx, 0x25CBE0u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = s3;
        a1 = 89;
        jal(ctx, 0x25CBF0u, gen::fn_sub_21CCA0_0021cca0);
        a0 = v0;
        jal(ctx, 0x25CBFCu, gen::fn_sub_21CCE0_0021cce0);
        a0 = 1;
        a1 = v0;
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x25CC10u, v0.u());
        a0 = addiu(s2, 816);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C
        jalr(ctx, 0x25CC30u, v0.u());
        a0 = addiu(s2, 816);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C
        jalr(ctx, 0x25CC50u, v0.u());
        a0 = s3;
        a1 = 90;
        jal(ctx, 0x25CC60u, gen::fn_sub_21CCA0_0021cca0);
        a0 = v0;
        jal(ctx, 0x25CC6Cu, gen::fn_sub_21CCE0_0021cce0);
        a0 = 1;
        a1 = v0;
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x25CC80u, v0.u());
        a0 = addiu(s2, 1072);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C
        jalr(ctx, 0x25CCA0u, v0.u());
        a0 = addiu(s2, 1072);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C
        jalr(ctx, 0x25CCC0u, v0.u());
        lw(a0, s2, dlg::kLines);
        a1 = 1;
        a2 = 0;
        jal(ctx, 0x25CCD4u, gen::fn_frFontDraw_003b1360);
        lw(a0, s2, dlg::kLines + 4);
        a1 = 1;
        a2 = 0;
        jal(ctx, 0x25CCE8u, gen::fn_frFontDraw_003b1360);
        lw(a0, s2, dlg::kLines + 8);
        a1 = 1;
        a2 = 0;
        jal(ctx, 0x25CCFCu, gen::fn_frFontDraw_003b1360);
    }
    // 0x0025cd04 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0025CD30 sub_25CD30 -- 120 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Releases the bp_dialog's three font lines and clears flag 4.
void sub_25CD30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0025cd30
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBpDialogWork);  // the battle dialog work (bp_dialog.c) 0x7CE368
    if (v0 == 0) {
        // 0x0025cd48
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5160);  // "bp_dialog.c"
        a1 = 60;
        jal(ctx, 0x25CD54u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0025cd5c
    charge(ctx, 19);
    lw(s0, gp, kGpBpDialogWork);  // the battle dialog work (bp_dialog.c) 0x7CE368
    lw(a0, s0, dlg::kLines);
    jal(ctx, 0x25CD64u, gen::fn_sub_3B0170_003b0170);
    lw(a0, s0, dlg::kLines + 4);
    jal(ctx, 0x25CD70u, gen::fn_sub_3B0170_003b0170);
    lw(a0, s0, dlg::kLines + 8);
    jal(ctx, 0x25CD7Cu, gen::fn_sub_3B0170_003b0170);
    lw(a0, s0, dlg::kFlags);
    v1 = si(-5);
    v1 = a0 & v1;
    sw(v1, s0, dlg::kFlags);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0025CEB0 sub_25CEB0 -- 72 bytes; frame 0x10: ra sp+0x0
// Lines of a font line chain: frFontChainCountLines of the last node (+36 links).
// Arguments: a0 font line.
void sub_25CEB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0025ceb0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v0 = 0;
    for (;;) {
        // 0x0025ced4
        charge(ctx, 2);
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0025cec4
        charge(ctx, 2);
        if (a0 != 0) {
            // 0x0025cecc
            charge(ctx, 1);
            v0 = a0;
        }
        // 0x0025ced0
        charge(ctx, 1);
        lw(a0, a0, 36);
    }
    // 0x0025cedc
    charge(ctx, 7);
    a0 = v0;
    jal(ctx, 0x25CEE0u, gen::fn_frFontChainCountLines_003b1a90);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0025CF00 sub_25CF00 -- 16 bytes; leaf frame (no stack)
// Registers the battle rush work (bp_rush.c, $gp slot 0x7CE36C).
// Arguments: a0 work.
void sub_25CF00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, gp{ctx, 28};
    // 0x0025cf00
    enter(ctx, 4);  // entry check point + this block's cycles
    sw(zero, a0, 0);
    sw(a0, gp, kGpBpRushWork);  // the battle rush work (bp_rush.c) 0x7CE36C
}

// 0x0025CF10 sub_25CF10 -- 12 bytes; leaf frame (no stack)
// Clears $gp slot 0x7CE36C.
void sub_25CF10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, gp{ctx, 28};
    // 0x0025cf10
    enter(ctx, 3);  // entry check point + this block's cycles
    sw(zero, gp, kGpBpRushWork);  // the battle rush work (bp_rush.c) 0x7CE36C
}

// 0x0025D6C0 sub_25D6C0 -- 72 bytes; frame 0x10: ra sp+0x0
// Sets flag 0x10 of the bp_rush work.
void sub_25D6C0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0025d6c0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpBpRushWork);  // the battle rush work (bp_rush.c) 0x7CE36C
    if (v1 == 0) {
        // 0x0025d6d4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5144);  // "bp_rush.c"
        a1 = 50;
        jal(ctx, 0x25D6E0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0025d6e8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    lw(a0, gp, kGpBpRushWork);  // the battle rush work (bp_rush.c) 0x7CE36C
    lw(v1, a0, rush::kFlags);
    v1 = v1 | 0x10;
    sw(v1, a0, rush::kFlags);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0025D710 sub_25D710 -- 76 bytes; frame 0x10: ra sp+0x0
// Clears flag 0x10 of the bp_rush work.
void sub_25D710(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0025d710
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpBpRushWork);  // the battle rush work (bp_rush.c) 0x7CE36C
    if (v1 == 0) {
        // 0x0025d724
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5144);  // "bp_rush.c"
        a1 = 50;
        jal(ctx, 0x25D730u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0025d738 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    lw(a1, gp, kGpBpRushWork);  // the battle rush work (bp_rush.c) 0x7CE36C
    lw(a0, a1, rush::kFlags);
    v1 = si(-17);
    v1 = a0 & v1;
    sw(v1, a1, rush::kFlags);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0025FB60 sub_25FB60 -- 240 bytes; frame 0x10
// [brItemGetCellUv] brItem: the UV rectangle of a sprite cell: the cell a1 of the record list (+388, 128-byte cells:
// +84 / +88 / +92 / +96 the pixel box, +20 the texture index into +260), divided by the texture's width (+12) and
// height (+16), into a2 = {u0, v0, u1, v1}.
// Arguments: a0 sprite set, a1 cell, a2 out f32[4].
void sub_25FB60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4};
    // 0x0025fb60
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = sll(a1, 7);
    lw(v1, a0, 388);
    a3 = addu(v1, a1);
    lw(v1, a3, 20);
    v1 = sll(v1, 2);
    v1 = addu(v1, a0);
    lw(a1, v1, 260);
    a0 = addiu(sp, 0x8);
    v1 = 8;
    if (a0 != 0) {
        for (;;) {
            // 0x0025fb90
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
    // 0x0025fbac
    charge(ctx, 10);
    lwc1(f0, a3, 84);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x8);
    lwc1(f0, a3, 92);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xC);
    a0 = addiu(sp, 0x0);
    v1 = 8;
    if (a0 != 0) {
        for (;;) {
            // 0x0025fbd4
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
    // 0x0025fbf0 (the shared epilogue, written out on this path)
    charge(ctx, 24);
    lwc1(f0, a3, 88);
    cvt_s_w(f4, f0);
    swc1(f4, sp, 0x0);
    lwc1(f0, a3, 96);
    cvt_s_w(f3, f0);
    swc1(f3, sp, 0x4);
    lwc1(f1, a1, 12);
    lwc1(f0, a1, 16);
    cvt_s_w(f2, f1);
    lwc1(f1, sp, 0x8);
    div_s(f1, f1, f2);
    swc1(f1, a2, 0);
    lwc1(f1, sp, 0xC);
    div_s(f1, f1, f2);
    swc1(f1, a2, 8);
    cvt_s_w(f1, f0);
    div_s(f0, f4, f1);
    swc1(f0, a2, 4);
    div_s(f0, f3, f1);
    swc1(f0, a2, 12);
    sp = addiu(sp, 0x10);
}

// 0x00280050 sub_280050 -- 224 bytes; frame 0x50: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlUnitGetCellCentre] A unit's centre on its grid cell: the offset +128..+136 scaled by +44 and rotated by the
// unit matrix (+28, sub_4BE1E0), plus (25 * cell x - 1750, +8, 25 * cell z - 1750) from the s16 cells +148 / +150.
// Arguments: a0 btlUnit, a1 out f32[3].
void sub_280050(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x00280050
    enter(ctx, 56);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lwc1(f0, a0, unit4::kCentreOff);
    lwc1(f1, a0, unit::kScale);
    mul_s(f0, f0, f1);
    swc1(f0, sp, 0x40);
    lwc1(f0, a0, unit4::kCentreOff + 4);
    mul_s(f0, f0, f1);
    swc1(f0, sp, 0x44);
    lwc1(f0, a0, unit4::kCentreOff + 8);
    mul_s(f0, f0, f1);
    swc1(f0, sp, 0x48);
    a0 = addiu(sp, 0x30);
    a1 = addiu(sp, 0x40);
    a2 = 1;
    a3 = addiu(s1, 28);
    jal(ctx, 0x2800A0u, gen::fn_sub_4BE1E0_004be1e0);
    lh(a0, s1, unit4::kCellX);
    v1 = sll(a0, 2);
    a0 = addu(v1, a0);
    v1 = sll(a0, 2);
    v1 = addu(a0, v1);
    v1 = addiu(v1, -1750);
    mtc1(v1, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, sp, 0x30);
    add_s(f0, f0, f1);
    swc1(f0, s0, 0);
    lwc1(f1, s1, unit4::kPos + 4);
    lwc1(f0, sp, 0x34);
    add_s(f0, f0, f1);
    swc1(f0, s0, 4);
    lh(a0, s1, unit4::kCellZ);
    v1 = sll(a0, 2);
    a0 = addu(v1, a0);
    v1 = sll(a0, 2);
    v1 = addu(a0, v1);
    v1 = addiu(v1, -1750);
    mtc1(v1, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, sp, 0x38);
    add_s(f0, f0, f1);
    swc1(f0, s0, 8);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00280130 sub_280130 -- 208 bytes; frame 0x50: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlUnitGetBonePoint] A unit's point of a model bone: the s16 offset of row 0 of its point table (sub_288DA0),
// scaled by +44, rotated by the unit's rotation (+28) and added to its position.
// Arguments: a0 btlUnit, a1 out f32[3].
void sub_280130(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x00280130
    enter(ctx, 52);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    a1 = 0;
    jal(ctx, 0x28014Cu, gen::fn_sub_288DA0_00288da0);
    lh(v1, v0, 2);
    mtc1(v1, f0);
    cvt_s_w(f3, f0);
    lh(v1, v0, 4);
    mtc1(v1, f0);
    cvt_s_w(f2, f0);
    lh(v0, v0, 0);
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    lwc1(f1, s1, unit::kScale);
    mul_s(f0, f0, f1);
    swc1(f0, sp, 0x40);
    mul_s(f0, f3, f1);
    swc1(f0, sp, 0x44);
    mul_s(f0, f2, f1);
    swc1(f0, sp, 0x48);
    a0 = addiu(sp, 0x30);
    a1 = addiu(sp, 0x40);
    a2 = 1;
    a3 = addiu(s1, 28);
    jal(ctx, 0x2801B0u, gen::fn_sub_4BE1E0_004be1e0);
    lwc1(f1, s1, unit4::kPos);
    lwc1(f0, sp, 0x30);
    add_s(f0, f0, f1);
    swc1(f0, s0, 0);
    lwc1(f1, s1, unit4::kPos + 4);
    lwc1(f0, sp, 0x34);
    add_s(f0, f0, f1);
    swc1(f0, s0, 4);
    lwc1(f1, s1, unit4::kPos + 8);
    lwc1(f0, sp, 0x38);
    add_s(f0, f0, f1);
    swc1(f0, s0, 8);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00280580 sub_280580 -- 324 bytes; frame 0x70: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlUnitGetCentre] A unit's centre: the model's bone point (sub_318ED0) when it has a model (+152 bit 1) and that
// succeeds, else the offset +128 scaled and rotated plus the position +4..+12.
// Arguments: a0 btlUnit, a1 out f32[3].
void sub_280580(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x00280580
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lw(v0, a0, unit::kModelFlags);
    v0 = v0 & 0x2;
    if (v0 != 0) {
        // 0x00280620
        charge(ctx, 7);
        lw(a0, s1, unit::kModel);
        a1 = 0;
        a2 = s0;
        jal(ctx, 0x28062Cu, gen::fn_sub_318ED0_00318ed0);
        if (v0 == 0) {
            // 0x0028063c
            charge(ctx, 28);
            lwc1(f0, s1, unit4::kCentreOff);
            lwc1(f1, s1, unit::kScale);
            mul_s(f0, f0, f1);
            swc1(f0, sp, 0x40);
            lwc1(f0, s1, unit4::kCentreOff + 4);
            mul_s(f0, f0, f1);
            swc1(f0, sp, 0x44);
            lwc1(f0, s1, unit4::kCentreOff + 8);
            mul_s(f0, f0, f1);
            swc1(f0, sp, 0x48);
            a0 = addiu(sp, 0x30);
            a1 = addiu(sp, 0x40);
            a2 = 1;
            a3 = addiu(s1, 28);
            jal(ctx, 0x280674u, gen::fn_sub_4BE1E0_004be1e0);
            lwc1(f1, s1, unit4::kPos);
            lwc1(f0, sp, 0x30);
            add_s(f0, f0, f1);
            swc1(f0, s0, 0);
            lwc1(f1, s1, unit4::kPos + 4);
            lwc1(f0, sp, 0x34);
            add_s(f0, f0, f1);
            swc1(f0, s0, 4);
            lwc1(f1, s1, unit4::kPos + 8);
            lwc1(f0, sp, 0x38);
            add_s(f0, f0, f1);
            swc1(f0, s0, 8);
        }
    } else {
        // 0x002805a8
        charge(ctx, 30);
        lwc1(f0, s1, unit4::kCentreOff);
        lwc1(f1, s1, unit::kScale);
        mul_s(f0, f0, f1);
        swc1(f0, sp, 0x60);
        lwc1(f0, s1, unit4::kCentreOff + 4);
        mul_s(f0, f0, f1);
        swc1(f0, sp, 0x64);
        lwc1(f0, s1, unit4::kCentreOff + 8);
        mul_s(f0, f0, f1);
        swc1(f0, sp, 0x68);
        a0 = addiu(sp, 0x50);
        a1 = addiu(sp, 0x60);
        a2 = 1;
        a3 = addiu(s1, 28);
        jal(ctx, 0x2805E0u, gen::fn_sub_4BE1E0_004be1e0);
        lwc1(f1, s1, unit4::kPos);
        lwc1(f0, sp, 0x50);
        add_s(f0, f0, f1);
        swc1(f0, s0, 0);
        lwc1(f1, s1, unit4::kPos + 4);
        lwc1(f0, sp, 0x54);
        add_s(f0, f0, f1);
        swc1(f0, s0, 4);
        lwc1(f1, s1, unit4::kPos + 8);
        lwc1(f0, sp, 0x58);
        add_s(f0, f0, f1);
        swc1(f0, s0, 8);
    }
    // 0x002806ac (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x002806D0 sub_2806D0 -- 200 bytes; frame 0x50: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlUnitGetHeadPoint] A unit's head point: the rotated offset plus the position, y raised by height (+140) * scale
// * the float 0x7CB0CC.
// Arguments: a0 btlUnit, a1 out f32[3].
void sub_2806D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x002806d0
    enter(ctx, 50);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lwc1(f0, a0, unit4::kCentreOff);
    lwc1(f1, a0, unit::kScale);
    mul_s(f0, f0, f1);
    swc1(f0, sp, 0x40);
    lwc1(f0, a0, unit4::kCentreOff + 4);
    mul_s(f0, f0, f1);
    swc1(f0, sp, 0x44);
    lwc1(f0, a0, unit4::kCentreOff + 8);
    mul_s(f0, f0, f1);
    swc1(f0, sp, 0x48);
    a0 = addiu(sp, 0x30);
    a1 = addiu(sp, 0x40);
    a2 = 1;
    a3 = addiu(s1, 28);
    jal(ctx, 0x280720u, gen::fn_sub_4BE1E0_004be1e0);
    lwc1(f1, s1, unit4::kPos);
    lwc1(f0, sp, 0x30);
    add_s(f0, f0, f1);
    swc1(f0, s0, 0);
    lwc1(f1, s1, unit4::kPos + 4);
    lwc1(f0, sp, 0x34);
    add_s(f0, f0, f1);
    swc1(f0, s0, 4);
    lwc1(f1, s1, unit4::kPos + 8);
    lwc1(f0, sp, 0x38);
    add_s(f0, f0, f1);
    swc1(f0, s0, 8);
    lwc1(f1, s1, unit4::kHeight);
    lwc1(f0, s1, unit::kScale);
    mul_s(f3, f1, f0);
    lwc1(f2, gp, -31780);  // 0x7CB0CC
    lwc1(f1, s0, 4);
    mtc1(zero, f0);
    adda_s(f0, f1);
    madd_s(f0, f2, f3);
    swc1(f0, s0, 4);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x002807A0 sub_2807A0 -- 204 bytes; frame 0x50: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlUnitGetQuarterPoint] As sub_2806D0 with the factor 0.25.
// Arguments: a0 btlUnit, a1 out f32[3].
void sub_2807A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x002807a0
    enter(ctx, 51);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lwc1(f0, a0, unit4::kCentreOff);
    lwc1(f1, a0, unit::kScale);
    mul_s(f0, f0, f1);
    swc1(f0, sp, 0x40);
    lwc1(f0, a0, unit4::kCentreOff + 4);
    mul_s(f0, f0, f1);
    swc1(f0, sp, 0x44);
    lwc1(f0, a0, unit4::kCentreOff + 8);
    mul_s(f0, f0, f1);
    swc1(f0, sp, 0x48);
    a0 = addiu(sp, 0x30);
    a1 = addiu(sp, 0x40);
    a2 = 1;
    a3 = addiu(s1, 28);
    jal(ctx, 0x2807F0u, gen::fn_sub_4BE1E0_004be1e0);
    lwc1(f1, s1, unit4::kPos);
    lwc1(f0, sp, 0x30);
    add_s(f0, f0, f1);
    swc1(f0, s0, 0);
    lwc1(f1, s1, unit4::kPos + 4);
    lwc1(f0, sp, 0x34);
    add_s(f0, f0, f1);
    swc1(f0, s0, 4);
    lwc1(f1, s1, unit4::kPos + 8);
    lwc1(f0, sp, 0x38);
    add_s(f0, f0, f1);
    swc1(f0, s0, 8);
    lwc1(f1, s1, unit4::kHeight);
    lwc1(f0, s1, unit::kScale);
    mul_s(f3, f1, f0);
    v1 = 0x3E800000;
    mtc1(v1, f2);
    lwc1(f1, s0, 4);
    mtc1(zero, f0);
    adda_s(f0, f1);
    madd_s(f0, f2, f3);
    swc1(f0, s0, 4);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00280870 sub_280870 -- 1316 bytes; frame 0x130: ra sp+0xB0, fp sp+0xA0 (sq), s7 sp+0x90 (sq), s6 sp+0x80 (sq), s5 sp+0x70 (sq), s4 sp+0x60 (sq), s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [btlUnitGroupBounds] Centre and extent of a group of units: over the side mask a0 (bits 0..3) every unit in the
// battle (+156 flag 8) without the flags a1, positions summed (cell centres when a5 bit 0); returns the last unit;
// writes the mean to a2, the highest top (y + height / 2 * scale) to a3, the lowest to a4 when given.
// Arguments: a0 side mask, a1 excluded flags, a2 / a3 / a4 outputs, a5 flags.
void sub_280870(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24};
    // 0x00280870
    enter(ctx, 40);  // entry check point + this block's cycles
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
    s1 = a1;
    s0 = a2;
    s5 = a3;
    s6 = t0;
    mtc1(zero, f23);
    v0 = 0x5F50000;
    v0 = v0 | 0xE100;
    mtc1(v0, f0);
    cvt_s_w(f22, f0);
    v0 = 0;
    s4 = 0;
    v1 = 0x950000;
    ld(a1, v1, 29056);  // 0x957180
    v1 = 0x950000;
    lwc1(f0, v1, 29064);  // 0x957188
    sd(a1, sp, 0x110);
    swc1(f0, sp, 0x118);
    s2 = 0;
    s7 = a0 & 0xFFFF;
    v1 = t1 & 0xFFFF;
    fp = v1 & 0x1;
    for (;;) {
        // 0x00280ab0
        charge(ctx, 3);
        v1 = sltiu(s2, 4);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00280910
        charge(ctx, 5);
        v1 = 1;
        v1 = sllv(v1, s2);
        v1 = s7 & v1;
        if (v1 != 0) {
            // 0x00280924
            charge(ctx, 6);
            a0 = sll(s2, 3);
            lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
            v1 = addu(v1, a0);
            lw(s3, v1, 336);
            for (;;) {
                // 0x00280aa4
                charge(ctx, 2);
                if (s3 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0028093c
                charge(ctx, 4);
                lw(a0, s3, 156);
                v1 = a0 & 0x8;
                if (v1 != 0) {
                    // 0x0028094c
                    charge(ctx, 3);
                    v1 = a0 & s1;
                    if (v1 == 0) {
                        // 0x00280958
                        charge(ctx, 2);
                        if (fp != 0) {
                            // 0x002809cc
                            charge(ctx, 25);
                            lh(v1, s3, 148);
                            v0 = sll(v1, 2);
                            v1 = addu(v0, v1);
                            v0 = sll(v1, 2);
                            v0 = addu(v1, v0);
                            v0 = addiu(v0, -1750);
                            mtc1(v0, f0);
                            cvt_s_w(f4, f0);
                            lwc1(f3, s3, 132);
                            lwc1(f2, s3, 44);
                            lwc1(f1, s3, 8);
                            mtc1(zero, f0);
                            adda_s(f0, f1);
                            madd_s(f3, f3, f2);
                            lh(v1, s3, 150);
                            v0 = sll(v1, 2);
                            v1 = addu(v0, v1);
                            v0 = sll(v1, 2);
                            v0 = addu(v1, v0);
                            v0 = addiu(v0, -1750);
                            mtc1(v0, f0);
                            cvt_s_w(f1, f0);
                        } else {
                            // 0x00280960
                            charge(ctx, 27);
                            lwc1(f0, s3, 128);
                            lwc1(f1, s3, 44);
                            mul_s(f0, f0, f1);
                            swc1(f0, sp, 0xF0);
                            lwc1(f0, s3, 132);
                            mul_s(f0, f0, f1);
                            swc1(f0, sp, 0xF4);
                            lwc1(f0, s3, 136);
                            mul_s(f0, f0, f1);
                            swc1(f0, sp, 0xF8);
                            a0 = addiu(sp, 0xE0);
                            a1 = addiu(sp, 0xF0);
                            a2 = 1;
                            a3 = addiu(s3, 28);
                            jal(ctx, 0x280998u, gen::fn_sub_4BE1E0_004be1e0);
                            lwc1(f1, s3, 4);
                            lwc1(f0, sp, 0xE0);
                            add_s(f4, f0, f1);
                            lwc1(f1, s3, 8);
                            lwc1(f0, sp, 0xE4);
                            add_s(f3, f0, f1);
                            lwc1(f1, s3, 12);
                            lwc1(f0, sp, 0xE8);
                            add_s(f1, f0, f1);
                        }
                        // 0x00280a30
                        charge(ctx, 21);
                        lwc1(f0, sp, 0x110);
                        add_s(f0, f0, f4);
                        swc1(f0, sp, 0x110);
                        lwc1(f0, sp, 0x114);
                        add_s(f0, f0, f3);
                        swc1(f0, sp, 0x114);
                        lwc1(f0, sp, 0x118);
                        add_s(f0, f0, f1);
                        swc1(f0, sp, 0x118);
                        lwc1(f1, s3, 140);
                        lwc1(f0, s3, 44);
                        mul_s(f2, f1, f0);
                        v0 = 0x3F000000;
                        mtc1(v0, f1);
                        mtc1(zero, f0);
                        adda_s(f0, f3);
                        madd_s(f0, f1, f2);
                        c_lt_s(f23, f0);
                        if (cond(ctx)) {
                            // 0x00280a84
                            charge(ctx, 1);
                            mov_s(f23, f0);
                        }
                        // 0x00280a88
                        charge(ctx, 3);
                        c_le_s(f22, f0);
                        if (!cond(ctx)) {
                            // 0x00280a94
                            charge(ctx, 1);
                            mov_s(f22, f0);
                        }
                        // 0x00280a98
                        charge(ctx, 2);
                        v0 = s3;
                        s4 = addiu(s4, 1);
                    }
                }
                // 0x00280aa0
                charge(ctx, 1);
                lw(s3, s3, 2612);
            }
        }
        // 0x00280aac
        charge(ctx, 1);
        s2 = addiu(s2, 1);
    }
    // 0x00280abc
    charge(ctx, 2);
    if (s4 != 0) {
        // 0x00280ad0
        charge(ctx, 3);
        v1 = 1;
        if (s4 != v1) {
            // 0x00280b28
            charge(ctx, 4);
            v0 = 0x3F800000;
            mtc1(v0, f1);
            if (i64(s4) < 0) {
                // 0x00280b4c
                charge(ctx, 7);
                v1 = srl(s4, 1);
                v0 = s4 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f0, f0);
            } else {
                // 0x00280b38
                charge(ctx, 5);
                mtc1(s4, f0);
                cvt_s_w(f0, f0);
            }
            // 0x00280b68
            charge(ctx, 16);
            div_s(f1, f1, f0);
            lwc1(f0, sp, 0x110);
            mul_s(f0, f0, f1);
            swc1(f0, sp, 0x120);
            lwc1(f0, sp, 0x114);
            mul_s(f21, f0, f1);
            swc1(f21, sp, 0x124);
            lwc1(f0, sp, 0x118);
            mul_s(f20, f0, f1);
            swc1(f20, sp, 0x128);
            mtc1(zero, f24);
            s3 = 0;
            for (;;) {
                // 0x00280d04
                charge(ctx, 3);
                v0 = sltiu(s3, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00280ba8
                charge(ctx, 5);
                v0 = 1;
                v0 = sllv(v0, s3);
                v0 = s7 & v0;
                if (v0 != 0) {
                    // 0x00280bbc
                    charge(ctx, 6);
                    v1 = sll(s3, 3);
                    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                    v0 = addu(v0, v1);
                    lw(s2, v0, 336);
                    for (;;) {
                        // 0x00280cf8
                        charge(ctx, 2);
                        if (s2 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x00280bd4
                        charge(ctx, 4);
                        lw(v1, s2, 156);
                        v0 = v1 & 0x8;
                        if (v0 != 0) {
                            // 0x00280be4
                            charge(ctx, 3);
                            v0 = v1 & s1;
                            if (v0 == 0) {
                                // 0x00280bf0
                                charge(ctx, 2);
                                if (fp != 0) {
                                    // 0x00280c58
                                    charge(ctx, 18);
                                    lh(v1, s2, 148);
                                    v0 = sll(v1, 2);
                                    v1 = addu(v0, v1);
                                    v0 = sll(v1, 2);
                                    v0 = addu(v1, v0);
                                    v0 = addiu(v0, -1750);
                                    mtc1(v0, f0);
                                    cvt_s_w(f2, f0);
                                    lh(v1, s2, 150);
                                    v0 = sll(v1, 2);
                                    v1 = addu(v0, v1);
                                    v0 = sll(v1, 2);
                                    v0 = addu(v1, v0);
                                    v0 = addiu(v0, -1750);
                                    mtc1(v0, f0);
                                    cvt_s_w(f1, f0);
                                } else {
                                    // 0x00280bf8
                                    charge(ctx, 24);
                                    lwc1(f0, s2, 128);
                                    lwc1(f1, s2, 44);
                                    mul_s(f0, f0, f1);
                                    swc1(f0, sp, 0xD0);
                                    lwc1(f0, s2, 132);
                                    mul_s(f0, f0, f1);
                                    swc1(f0, sp, 0xD4);
                                    lwc1(f0, s2, 136);
                                    mul_s(f0, f0, f1);
                                    swc1(f0, sp, 0xD8);
                                    a0 = addiu(sp, 0xC0);
                                    a1 = addiu(sp, 0xD0);
                                    a2 = 1;
                                    a3 = addiu(s2, 28);
                                    jal(ctx, 0x280C30u, gen::fn_sub_4BE1E0_004be1e0);
                                    lwc1(f1, s2, 4);
                                    lwc1(f0, sp, 0xC0);
                                    add_s(f2, f0, f1);
                                    lwc1(f1, s2, 12);
                                    lwc1(f0, sp, 0xC8);
                                    add_s(f1, f0, f1);
                                }
                                // 0x00280ca0
                                charge(ctx, 19);
                                lwc1(f0, sp, 0x120);
                                sub_s(f0, f2, f0);
                                swc1(f0, sp, 0x100);
                                sub_s(f0, f21, f21);
                                swc1(f0, sp, 0x104);
                                sub_s(f0, f1, f20);
                                swc1(f0, sp, 0x108);
                                a0 = addiu(sp, 0x100);
                                jal(ctx, 0x280CC0u, gen::fn_sub_4C6AC0_004c6ac0);
                                lwc1(f3, s2, 144);
                                lwc1(f2, s2, 44);
                                mtc1(zero, f1);
                                adda_s(f1, f0);
                                madd_s(f0, f3, f2);
                                c_le_s(f0, f24);
                                if (!cond(ctx)) {
                                    // 0x00280cec
                                    charge(ctx, 1);
                                    mov_s(f24, f0);
                                }
                                // 0x00280cf0
                                charge(ctx, 1);
                                s4 = addiu(s4, 1);
                            }
                        }
                        // 0x00280cf4
                        charge(ctx, 1);
                        lw(s2, s2, 2612);
                    }
                }
                // 0x00280d00
                charge(ctx, 1);
                s3 = addiu(s3, 1);
            }
        } else {
            // 0x00280adc
            charge(ctx, 16);
            ld(v1, sp, 0x110);
            lwc1(f0, sp, 0x118);
            sd(v1, sp, 0x120);
            swc1(f0, sp, 0x128);
            lwc1(f1, v0, 44);
            lwc1(f0, v0, 144);
            mul_s(f24, f0, f1);
            lwc1(f0, v0, 140);
            mul_s(f1, f0, f1);
            v0 = 0x3F000000;
            mtc1(v0, f0);
            mul_s(f0, f0, f1);
            c_le_s(f0, f24);
            if (!cond(ctx)) {
                // 0x00280b1c
                charge(ctx, 3);
                mov_s(f24, f0);
            }
        }
        // 0x00280d10
        charge(ctx, 2);
        if (s0 != 0) {
            // 0x00280d18
            charge(ctx, 6);
            lwc1(f2, sp, 0x120);
            lwc1(f1, sp, 0x124);
            lwc1(f0, sp, 0x128);
            swc1(f2, s0, 0);
            swc1(f1, s0, 4);
            swc1(f0, s0, 8);
        }
        // 0x00280d30
        charge(ctx, 2);
        if (s5 != 0) {
            // 0x00280d38
            charge(ctx, 1);
            swc1(f23, s5, 0);
        }
        // 0x00280d3c
        charge(ctx, 2);
        if (s6 != 0) {
            // 0x00280d44
            charge(ctx, 1);
            swc1(f22, s6, 0);
        }
        // 0x00280d48
        charge(ctx, 1);
        mov_s(f0, f24);
    } else {
        // 0x00280ac4
        charge(ctx, 3);
        mtc1(zero, f0);
    }
    // 0x00280d4c (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0x130);
}

// 0x002812D0 sub_2812D0 -- 256 bytes; frame 0x50: ra sp+0x40, s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [btlUnitGetApproachDistance] Approach distance of a unit's motion towards a target (returned in $f20 / $f0): the
// motion row (sub_283510) frames +6 * scale, plus the boss reach sub_2FC5D0 when it gives one (else the target's
// radius +144 * its scale), plus the unit's own offset +136 * scale.
// Arguments: a0 btlUnit, a1 target btlUnit, a2 motion.
void sub_2812D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f20{ctx, 20};
    // 0x002812d0
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s0 = a2;
    a1 = s0;
    jal(ctx, 0x2812F8u, gen::fn_sub_283510_00283510);
    a0 = dsll32(v0, 16);
    a0 = dsra32(a0, 16);
    lhu(v0, s2, unit::kMotionCount);
    at = slt(a0, v0);
    if (at == 0) {
        // 0x002813a8
        charge(ctx, 1);
        mtc1(zero, f20);
    } else {
        // 0x00281318
        charge(ctx, 21);
        lw(v1, s2, unit::kMotionTbl);
        v0 = sll(a0, 2);
        v0 = addu(v0, a0);
        v0 = sll(v0, 1);
        v0 = addu(v0, v1);
        lh(v0, v0, 6);
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, s2, unit::kScale);
        mul_s(f20, f0, f1);
        a0 = s2;
        a1 = s1;
        a2 = s0;
        jal(ctx, 0x281350u, gen::fn_sub_2FC5D0_002fc5d0);
        mtc1(zero, f2);
        c_lt_s(f0, f2);
        if (cond(ctx)) {
            // 0x00281378
            charge(ctx, 4);
            lwc1(f1, s1, unit::kRadius);
            lwc1(f0, s1, unit::kScale);
            adda_s(f2, f20);
            madd_s(f20, f1, f0);
        } else {
            // 0x0028136c
            charge(ctx, 3);
            add_s(f20, f20, f0);
        }
        // 0x00281388
        charge(ctx, 8);
        lwc1(f2, s2, unit4::kCentreOff + 8);
        lwc1(f1, s2, unit::kScale);
        mtc1(zero, f0);
        adda_s(f0, f20);
        madd_s(f20, f2, f1);
    }
    // 0x002813ac (the shared epilogue, written out on this path)
    charge(ctx, 9);
    mov_s(f0, f20);
    ld(ra, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00283C70 sub_283C70 -- 456 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlUnitGetAttackHitFrame] Hit frame of an attack motion (4 / 5 / 6 = the three attack hits): enemies only motion
// 4..6 -> column 0 of the enemy MODEL row (+26), party units by weapon type (hero +24 of the weapon row) or party row
// (+24), Koromaru's table 0x7CC518; 1 for other motions.
// Arguments: a0 btlUnit, a1 motion.
void sub_283C70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00283c70
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lbu(a2, a0, unit::kSide);
    v1 = 1;
    if (a2 != v1) {
        // 0x00283cc8
        charge(ctx, 4);
        a3 = a1 & 0xFFFF;
        v0 = 6;
        if (a3 == v0) {
            // 0x00283d14
            charge(ctx, 3);
            v0 = 2;
        } else {
            // 0x00283cd8
            charge(ctx, 3);
            v0 = 5;
            if (a3 == v0) {
                // 0x00283d04
                charge(ctx, 4);
                v0 = dsll32(v1, 16);
                v0 = dsra32(v0, 16);
            } else {
                // 0x00283ce4
                charge(ctx, 3);
                v0 = 4;
                if (a3 == v0) {
                    // 0x00283cf8
                    charge(ctx, 3);
                    v0 = 0;
                } else {
                    // 0x00283cf0
                    charge(ctx, 2);
                L_00283d20:
                    charge(ctx, 1);
                    v0 = si(-1);
                }
            }
        }
    } else {
        // 0x00283c8c
        charge(ctx, 4);
        a3 = a1 & 0xFFFF;
        v0 = 6;
        if (a3 != v0) {
            // 0x00283c9c
            charge(ctx, 3);
            v0 = 5;
            if (a3 == v0) {
                goto L_00283cbc;
            }
            // 0x00283ca8
            charge(ctx, 3);
            v0 = 4;
            if (a3 == v0) {
                goto L_00283cbc;
            }
            // 0x00283cb4
            charge(ctx, 2);
            goto L_00283d20;
        }
    L_00283cbc:
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00283d24
    charge(ctx, 5);
    s0 = dsll32(v0, 16);
    s0 = dsra32(s0, 16);
    v0 = si(-1);
    if (s0 != v0) {
        // 0x00283d44
        charge(ctx, 3);
        v1 = 1;
        if (a2 != v1) {
            // 0x00283d84
            charge(ctx, 4);
            lhu(a1, a0, 164);
            v0 = 4;
            if (a1 == v0) {
                // 0x00283de4
                charge(ctx, 6);
                v1 = sll(a3, 1);
                v0 = addiu(gp, -26584);  // &0x7CC518
                v0 = addu(v0, v1);
                lh(v0, v0, 0);
            } else {
                // 0x00283d94
                charge(ctx, 2);
                if (a1 == v1) {
                    // 0x00283da4
                    charge(ctx, 16);
                    lw(a0, a0, 2604);
                    jal(ctx, 0x283DA8u, gen::fn_datCalcGetHeldWeaponType_00308c60);
                    a0 = v0 & 0xFF;
                    lw(v1, gp, kGpModelWeapon);  // MODEL.TBL section 0 (296-byte rows by weapon type) 0x7CE408
                    v0 = sll(a0, 3);
                    v0 = addu(v0, a0);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, a0);
                    v0 = sll(v0, 3);
                    v1 = addu(v0, v1);
                    v0 = sll(s0, 2);
                    v0 = addu(v0, v1);
                    lh(v0, v0, 24);
                } else {
                    // 0x00283d9c
                    charge(ctx, 2);
                    // 0x00283dfc
                    charge(ctx, 10);
                    lw(v1, gp, kGpModelParty);  // MODEL.TBL section 1 (266-byte rows by party id) 0x7CE40C
                    v0 = sll(a1, 5);
                    v0 = addu(v0, a1);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, a1);
                    v0 = sll(v0, 1);
                    v1 = addu(v0, v1);
                    v0 = sll(s0, 2);
                    v0 = addu(v0, v1);
                    lh(v0, v0, 24);
                }
            }
        } else {
            // 0x00283d50
            charge(ctx, 13);
            lhu(v1, a0, 164);
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            v1 = sll(v0, 3);
            lw(v0, gp, kGpModelEnemy);  // MODEL.TBL section 2 (232-byte rows by enemy id) 0x7CE418
            v1 = addu(v1, v0);
            v0 = sll(s0, 2);
            v0 = addu(v0, v1);
            lh(v0, v0, 26);
        }
    } else {
        // 0x00283d38
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x00283e24 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00283E40 sub_283E40 -- 412 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlUnitGetAttackEndFrame] As sub_283C70 for the second column (+28 / +26): the attack's end frame; 0 for other
// motions.
// Arguments: a0 btlUnit, a1 motion.
void sub_283E40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00283e40
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lbu(a3, a0, unit::kSide);
    a2 = 1;
    if (a3 != a2) {
        // 0x00283e98
        charge(ctx, 4);
        v1 = a1 & 0xFFFF;
        v0 = 6;
        if (v1 == v0) {
            // 0x00283ee4
            charge(ctx, 3);
            v0 = 2;
        } else {
            // 0x00283ea8
            charge(ctx, 3);
            v0 = 5;
            if (v1 == v0) {
                // 0x00283ed4
                charge(ctx, 4);
                v0 = dsll32(a2, 16);
                v0 = dsra32(v0, 16);
            } else {
                // 0x00283eb4
                charge(ctx, 3);
                v0 = 4;
                if (v1 == v0) {
                    // 0x00283ec8
                    charge(ctx, 3);
                    v0 = 0;
                } else {
                    // 0x00283ec0
                    charge(ctx, 2);
                L_00283ef0:
                    charge(ctx, 1);
                    v0 = si(-1);
                }
            }
        }
    } else {
        // 0x00283e5c
        charge(ctx, 4);
        v1 = a1 & 0xFFFF;
        v0 = 6;
        if (v1 != v0) {
            // 0x00283e6c
            charge(ctx, 3);
            v0 = 5;
            if (v1 == v0) {
                goto L_00283e8c;
            }
            // 0x00283e78
            charge(ctx, 3);
            v0 = 4;
            if (v1 == v0) {
                goto L_00283e8c;
            }
            // 0x00283e84
            charge(ctx, 2);
            goto L_00283ef0;
        }
    L_00283e8c:
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00283ef4
    charge(ctx, 5);
    s0 = dsll32(v0, 16);
    s0 = dsra32(s0, 16);
    v0 = si(-1);
    if (s0 != v0) {
        // 0x00283f14
        charge(ctx, 3);
        v0 = 1;
        if (a3 != v0) {
            // 0x00283f54
            charge(ctx, 3);
            lhu(a1, a0, 164);
            if (a1 != v0) {
                // 0x00283fa0
                charge(ctx, 10);
                lw(v1, gp, kGpModelParty);  // MODEL.TBL section 1 (266-byte rows by party id) 0x7CE40C
                v0 = sll(a1, 5);
                v0 = addu(v0, a1);
                v0 = sll(v0, 2);
                v0 = addu(v0, a1);
                v0 = sll(v0, 1);
                v1 = addu(v0, v1);
                v0 = sll(s0, 2);
                v0 = addu(v0, v1);
                lh(v0, v0, 26);
            } else {
                // 0x00283f60
                charge(ctx, 16);
                lw(a0, a0, 2604);
                jal(ctx, 0x283F64u, gen::fn_datCalcGetHeldWeaponType_00308c60);
                a0 = v0 & 0xFF;
                lw(v1, gp, kGpModelWeapon);  // MODEL.TBL section 0 (296-byte rows by weapon type) 0x7CE408
                v0 = sll(a0, 3);
                v0 = addu(v0, a0);
                v0 = sll(v0, 2);
                v0 = addu(v0, a0);
                v0 = sll(v0, 3);
                v1 = addu(v0, v1);
                v0 = sll(s0, 2);
                v0 = addu(v0, v1);
                lh(v0, v0, 26);
            }
        } else {
            // 0x00283f20
            charge(ctx, 13);
            lhu(v1, a0, 164);
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            v1 = sll(v0, 3);
            lw(v0, gp, kGpModelEnemy);  // MODEL.TBL section 2 (232-byte rows by enemy id) 0x7CE418
            v1 = addu(v1, v0);
            v0 = sll(s0, 2);
            v0 = addu(v0, v1);
            lh(v0, v0, 28);
        }
    } else {
        // 0x00283f08
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00283fc8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00284DF0 sub_284DF0 -- 24 bytes; leaf frame (no stack)
// Hold callback of packet 259: the unit's busy count +1.
// Arguments: a0 packet data.
void sub_284DF0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x00284df0
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(a0, a0, 0);
    lhu(v1, a0, unit::kBusy);
    v1 = addiu(v1, 1);
    sh(v1, a0, unit::kBusy);
}

// 0x00284F30 sub_284F30 -- 24 bytes; leaf frame (no stack)
// Release callback of packet 259: busy -1.
// Arguments: a0 packet data.
void sub_284F30(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x00284f30
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(a0, a0, 0);
    lhu(v1, a0, unit::kBusy);
    v1 = addiu(v1, -1);
    sh(v1, a0, unit::kBusy);
}

// 0x00284F50 sub_284F50 -- 144 bytes; frame 0x50: ra sp+0x40, s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [btlUnitPktCreate259] Creates unit packet 259 (16 bytes: unit, u16 a1, f32 f12, u16 a2) with the callbacks
// sub_284DF0 / sub_284E10 / sub_284F30.
// Arguments: a0 btlUnit, a1, a2, f12.
void sub_284F50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f20{ctx, 20};
    // 0x00284f50
    enter(ctx, 36);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s2 = a0;
    s1 = a1;
    mov_s(f20, f12);
    s0 = a2;
    a0 = 259;
    a1 = 16;
    jal(ctx, 0x284F80u, gen::fn_sub_27EC10_0027ec10);
    v1 = 0x280000;
    v1 = addiu(v1, 19952);  // &sub_284DF0
    sw(v1, v0, pkt::kOnQueue);
    v1 = 0x280000;
    v1 = addiu(v1, 19984);  // &sub_284E10
    sw(v1, v0, pkt::kUpdate);
    v1 = 0x280000;
    v1 = addiu(v1, 20272);  // &sub_284F30
    sw(v1, v0, pkt::kOnEnd);
    lw(v1, v0, pkt::kData);
    sw(s2, v1, 0);
    sh(s1, v1, 4);
    swc1(f20, v1, 8);
    sh(s0, v1, 12);
    ld(ra, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00284FE0 sub_284FE0 -- 272 bytes; frame 0xB0: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlUnitPktHoldModel] Hold callback of unit packet 271: busy +1; keeps the unit's model when it matches the wanted
// (major, minor) pair (+212 / +214), else frees it (sub_3174E0), then takes a loaded model (sub_316910 / sub_317450:
// model flags 1 | 2) or requests its file (sub_31D530 name, H_Cdvd_Request, unless data flag 0x10).
// Arguments: a0 packet data {unit, u16 major, u16 minor, flags, request}.
void sub_284FE0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00284fe0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(s0, a0, 0);
    lhu(v1, s0, unit::kBusy);
    v1 = addiu(v1, 1);
    sh(v1, s0, unit::kBusy);
    lw(a0, s0, unit::kModel);
    if (a0 != 0) {
        // 0x00285010
        charge(ctx, 4);
        lhu(a1, s1, pdu4::kModelMajor);
        lhu(v1, a0, 212);
        if (a1 == v1) {
            // 0x00285020
            charge(ctx, 4);
            lhu(a1, s1, pdu4::kModelMinor);
            lhu(v1, a0, 214);
            if (a1 != v1) {
                goto L_00285030;
            }
            // 0x002850d8 (the shared epilogue, written out on this path)
            charge(ctx, 6);
            ld(ra, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0xB0);
            return;
        }
    L_00285030:
        charge(ctx, 3);
        jal(ctx, 0x285030u, gen::fn_sub_3174E0_003174e0);
        sw(zero, s0, 2548);
    }
    // 0x0028503c
    charge(ctx, 8);
    lhu(a0, s1, 4);
    lhu(a1, s1, 6);
    a2 = 0;
    jal(ctx, 0x285048u, gen::fn_sub_316910_00316910);
    a0 = v0;
    if (a0 == 0) {
        // 0x00285084
        charge(ctx, 4);
        lhu(v1, s1, 8);
        v1 = v1 & 0x10;
        if (v1 == 0) {
            // 0x00285094
            charge(ctx, 13);
            lhu(a0, s1, 4);
            lhu(a1, s1, 6);
            a2 = addiu(sp, 0x30);
            jal(ctx, 0x2850A0u, gen::fn_sub_31D530_0031d530);
            a0 = addiu(sp, 0x30);
            a1 = 0;
            jal(ctx, 0x2850B0u, gen::fn_H_Cdvd_Request_00100d80);
            sw(v0, s1, 12);
            lw(v1, s0, 152);
            v1 = v1 | 0x1;
            sw(v1, s0, 152);
        }
        // 0x002850c8
        charge(ctx, 4);
        lw(a0, s0, 152);
        v1 = si(-3);
        v1 = a0 & v1;
        sw(v1, s0, 152);
    } else {
        // 0x0028505c
        charge(ctx, 10);
        jal(ctx, 0x28505Cu, gen::fn_sub_317450_00317450);
        sw(v0, s0, 2548);
        lw(v1, s0, 152);
        v1 = v1 | 0x2;
        sw(v1, s0, 152);
        v1 = v1 | 0x1;
        sw(v1, s0, 152);
    }
    // 0x002850d8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xB0);
}

// 0x002890A0 sub_2890A0 -- 316 bytes; frame 0x70: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// [btlUnitCompareDepth] Comparison of two units by camera distance (a qsort callback): |unit1 - camera| - |unit2 -
// camera| as an int, positions from the units' frames (+296, sub_318B60) and the camera frame (sub_198590 +4,
// sub_4CB2F0).
// Arguments: a0 / a1 unit pointers.
void sub_2890A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f20{ctx, 20}, f21{ctx, 21};
    // 0x002890a0
    enter(ctx, 79);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s1 = a0;
    s0 = a1;
    jal(ctx, 0x2890C0u, gen::fn_sub_198590_00198590);
    lw(a0, v0, 4);
    jal(ctx, 0x2890CCu, gen::fn_sub_4CB2F0_004cb2f0);
    lwc1(f2, v0, 48);
    lwc1(f1, v0, 52);
    lwc1(f0, v0, 56);
    swc1(f2, sp, 0x40);
    swc1(f1, sp, 0x44);
    swc1(f0, sp, 0x48);
    lw(s1, s1, 0);
    lw(s0, s0, 0);
    lw(a0, s1, 296);
    jal(ctx, 0x2890F8u, gen::fn_sub_318B60_00318b60);
    lwc1(f1, v0, 48);
    lwc1(f0, sp, 0x40);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x60);
    lwc1(f21, sp, 0x44);
    lw(a0, s1, 296);
    jal(ctx, 0x289118u, gen::fn_sub_318B60_00318b60);
    lwc1(f0, v0, 52);
    sub_s(f0, f0, f21);
    swc1(f0, sp, 0x64);
    lwc1(f20, sp, 0x48);
    lw(a0, s1, 296);
    jal(ctx, 0x289134u, gen::fn_sub_318B60_00318b60);
    lwc1(f0, v0, 56);
    sub_s(f0, f0, f20);
    swc1(f0, sp, 0x68);
    lw(a0, s0, 296);
    jal(ctx, 0x28914Cu, gen::fn_sub_318B60_00318b60);
    lwc1(f1, v0, 48);
    lwc1(f0, sp, 0x40);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x50);
    lw(a0, s0, 296);
    jal(ctx, 0x289168u, gen::fn_sub_318B60_00318b60);
    lwc1(f0, v0, 52);
    sub_s(f0, f0, f21);
    swc1(f0, sp, 0x54);
    lw(a0, s0, 296);
    jal(ctx, 0x289180u, gen::fn_sub_318B60_00318b60);
    lwc1(f0, v0, 56);
    sub_s(f0, f0, f20);
    swc1(f0, sp, 0x58);
    a0 = addiu(sp, 0x60);
    jal(ctx, 0x289198u, gen::fn_sub_4C6AC0_004c6ac0);
    mov_s(f20, f0);
    a0 = addiu(sp, 0x50);
    jal(ctx, 0x2891A8u, gen::fn_sub_4C6AC0_004c6ac0);
    sub_s(f0, f20, f0);
    cvt_w_s(f0, f0);
    mfc1(v0, f0);
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x00289860 sub_289860 -- 384 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlActionIdleFidget] The idle fidget timer of an action's unit: a random wait 120..359 frames, then (unit visible,
// not down / ailing / low HP / dead, motion row < 4) plays motion 16 through sub_284200 and restarts; 1 while it may
// fidget.
// Arguments: a0 btlAction.
void sub_289860(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x00289860
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, a0, act4::kFidget);
    if (i64(v0) < 0) {
        // A new wait: 120 + effMiscRand(0) % 240 frames.
        // 0x0028987c
        charge(ctx, 8);
        a0 = 0;
        jal(ctx, 0x289880u, gen::fn_sub_357FD0_00357fd0);
        v1 = 240;
        divu(v0, v1);
        mfhi(v0);
        v0 = addiu(v0, 120);
        sw(v0, s0, act4::kFidget);
    }
    // 0x0028989c
    charge(ctx, 3);
    lw(v0, s0, act4::kFidget);
    if (v0 != 0) {
        // 0x002899c0
        charge(ctx, 3);
        v0 = addiu(v0, -1);
        sw(v0, s0, act4::kFidget);
        v0 = 0;
    } else {
        // The wait is over: fidget when the unit is visible (sub_282C60), not down (0x100000), without an ailment
        // (0xFFFFF), not at low HP and alive; motion 16 through sub_284200 when the current motion row is below 4.
        // 0x002898a8
        charge(ctx, 5);
        lw(a0, s0, act::kUnit);
        jal(ctx, 0x2898ACu, gen::fn_sub_282C60_00282c60);
        if (v0 != 0) {
            // 0x002898c8
            charge(ctx, 7);
            lw(v0, s0, act::kUnit);
            lw(a0, v0, unit::kDat);
            a1 = 0x100000;
            jal(ctx, 0x2898D4u, gen::fn_datCalcChkBadStatus_00300580);
            if (v0 == 0) {
                // 0x002898f0
                charge(ctx, 8);
                lw(v0, s0, act::kUnit);
                lw(a0, v0, unit::kDat);
                v0 = 0xF0000;
                a1 = v0 | 0xFFFF;
                jal(ctx, 0x289900u, gen::fn_datCalcChkBadStatus_00300580);
                if (v0 == 0) {
                    // 0x0028991c
                    charge(ctx, 6);
                    lw(v0, s0, act::kUnit);
                    lw(a0, v0, unit::kDat);
                    jal(ctx, 0x289924u, gen::fn_datCalcIsLowHp_0030b5e0);
                    if (v0 == 0) {
                        // 0x00289934
                        charge(ctx, 7);
                        lw(v0, s0, act::kUnit);
                        lw(a0, v0, unit::kDat);
                        a1 = 0;
                        jal(ctx, 0x289940u, gen::fn_datCalcIsDead_0030b5a0);
                        if (v0 != 0) {
                            goto L_00289950;
                        }
                        // 0x0028995c
                        charge(ctx, 8);
                        lw(a0, s0, act::kUnit);
                        jal(ctx, 0x289960u, gen::fn_sub_283BA0_00283ba0);
                        v0 = dsll32(v0, 16);
                        v0 = dsra32(v0, 16);
                        at = slti(v0, 4);
                        if (at != 0) {
                            // 0x0028997c
                            charge(ctx, 14);
                            v0 = 0x3F800000;
                            mtc1(v0, f12);
                            lw(a0, s0, act::kUnit);
                            a1 = 16;
                            a2 = 4;
                            a3 = 0;
                            jal(ctx, 0x289994u, gen::fn_sub_284200_00284200);
                            a0 = v0;
                            a1 = 1;
                            jal(ctx, 0x2899A4u, gen::fn_sub_27ED20_0027ed20);
                            v0 = si(-1);
                            sw(v0, s0, act4::kFidget);
                        }
                        // 0x002899b4
                        charge(ctx, 3);
                        v0 = 1;
                        // 0x002899cc (the shared epilogue, written out on this path)
                        charge(ctx, 5);
                        ld(ra, sp, 0x10);
                        lq(s0, sp, 0x0);
                        sp = addiu(sp, 0x20);
                        return;
                    }
                L_00289950:
                    charge(ctx, 3);
                    v0 = 0;
                } else {
                    // 0x00289910
                    charge(ctx, 3);
                    v0 = 0;
                }
            } else {
                // 0x002898e4
                charge(ctx, 3);
                v0 = 0;
            }
        } else {
            // 0x002898bc
            charge(ctx, 3);
            v0 = 0;
        }
    }
    // 0x002899cc (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0028CE50 sub_28CE50 -- 200 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlActionUpdateStateThink] Action state AI THINK (update): runs the AI wait (sub_2C7250 / sub_2C70D0 on the
// action's +56 record) and, once decided, marks the action ready (+24 bit 1; bit 0x4000 for a boss attack under the
// boss rules) and goes to state 12.
// Arguments: a0 btlAction.
void sub_28CE50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0028ce50
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = addiu(s0, 56);
    jal(ctx, 0x28CE64u, gen::fn_sub_2C7250_002c7250);
    if (v0 == 0) {
        // 0x0028ce74
        charge(ctx, 4);
        a0 = s0;
        a1 = addiu(s0, 56);
        jal(ctx, 0x28CE7Cu, gen::fn_sub_2C70D0_002c70d0);
    }
    // 0x0028ce84
    charge(ctx, 5);
    a0 = addiu(s0, 56);
    jal(ctx, 0x28CE88u, gen::fn_sub_2C7280_002c7280);
    if (v0 != 0) {
        // 0x0028ce98
        charge(ctx, 5);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(v1, v0, gbtl::kFlags);
        v0 = v1 & 0x2000;
        if (v0 != 0) {
            // 0x0028ceac
            charge(ctx, 4);
            v0 = 0x4000000;
            v0 = v1 & v0;
            if (v0 != 0) {
                // 0x0028cebc
                charge(ctx, 5);
                lw(v0, s0, act::kUnit);
                lbu(v0, v0, unit::kSide);
                v1 = 1;
                if (v0 == v1) {
                    // 0x0028ced0
                    charge(ctx, 3);
                    lhu(v0, s0, act::kCmdKind);
                    if (v0 == v1) {
                        // 0x0028cedc
                        charge(ctx, 3);
                        lhu(v0, s0, act::kFlags);
                        v0 = v0 | 0x4000;
                        sh(v0, s0, act::kFlags);
                    }
                }
            }
        }
        // 0x0028cee8
        charge(ctx, 7);
        lhu(v0, s0, act::kFlags);
        v0 = v0 | 0x2;
        sh(v0, s0, act::kFlags);
        a0 = s0;
        a1 = 12;
        jal(ctx, 0x28CEFCu, gen::fn_btlActionSetState_00299d60);
    }
    // 0x0028cf04 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0028D560 sub_28D560 -- 56 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Action state init (all-out attack join): sub_2DC5E0, then +1156 = 1, +1160 = 0.
// Arguments: a0 btlAction.
void sub_28D560(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0028d560
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x28D570u, gen::fn_sub_2DC5E0_002dc5e0);
    v1 = 1;
    sw(v1, s0, act::kAoaLeader);
    sw(zero, s0, act::kAoaPhase);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0028E7F0 sub_28E7F0 -- 664 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Action state init: walks to the target unless close (75) or the effect request is pending, then states 15 / 16 / 18
// by the command kind.
// Arguments: a0 btlAction.
void sub_28E7F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x0028ea70: the shared epilogue
    auto epilogue = [&] {
        charge(ctx, 6);
        ld(ra, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
    };
    // The next state by the command kind (+108): 9 -> 18, 2 / 3 -> 16, 1 -> 15, others 0 (into a1). The same blocks at
    // 0x28e830.. and 0x28ea00.. (the addresses in the comments are the first copy's).
    auto state_of_command = [&] {
        // 0x0028e830
        charge(ctx, 4);
        lhu(v1, s1, act::kCmdKind);
        v0 = 9;
        if (v1 == v0) {
            // 0x0028e884
            charge(ctx, 3);
            a1 = 18;
            return;
        }
        // 0x0028e840
        charge(ctx, 3);
        v0 = 3;
        bool magic = v1 == v0;
        if (!magic) {
            // 0x0028e84c
            charge(ctx, 3);
            v0 = 2;
            magic = v1 == v0;
            if (!magic) {
                // 0x0028e858
                charge(ctx, 3);
                v0 = 1;
                if (v1 == v0) {
                    // 0x0028e86c
                    charge(ctx, 3);
                    a1 = 15;
                } else {
                    // 0x0028e864
                    charge(ctx, 2);
                    // 0x0028e890
                    charge(ctx, 1);
                    a1 = 0;
                }
            }
        }
        if (magic) {
            // 0x0028e878
            charge(ctx, 3);
            a1 = 16;
        }
    };
    // 0x0028e7f0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;                    // s1 = the action
    lw(s0, a0, act::kUnit);     // s0 = its unit
    lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v1, a0, gbtl::kFlags);
    v0 = 0x400000;
    v0 = v1 & v0;
    bool pending = v0 != 0;     // effect requests pending (flag 0x400000) ...
    if (pending) {
        // 0x0028e820
        charge(ctx, 4);
        lhu(v0, a0, gbtl::kFxRequest);
        v0 = v0 & 0x2;
        pending = v0 != 0;      // ... with request bit 0x2: no walk, straight to the command's state
    }
    if (pending) {
        state_of_command();
        // 0x0028e894
        charge(ctx, 5);
        a0 = s1;
        jal(ctx, 0x28E898u, gen::fn_btlActionSetState_00299d60);
        epilogue();
        return;
    }
    // 0x0028e8a8: the approach point (sub_27F7C0) and its ground distance from the unit (+4)
    charge(ctx, 16);
    a0 = s0;
    a1 = addiu(sp, 0x30);
    a2 = 0;
    a3 = 0;
    jal(ctx, 0x28E8B8u, gen::fn_sub_27F7C0_0027f7c0);
    a0 = addiu(s0, unit4::kPos);
    a1 = addiu(sp, 0x30);
    jal(ctx, 0x28E8C8u, gen::fn_sub_2D1ED0_002d1ed0);
    v0 = 0x42960000;            // 75.0f
    mtc1(v0, f1);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // Close enough: the command's state.
        // 0x0028ea00
        state_of_command();
        // 0x0028ea64
        charge(ctx, 3);
        a0 = s1;
        jal(ctx, 0x28EA68u, gen::fn_btlActionSetState_00299d60);
    } else {
        // Walk there: flush the effect requests (sub_28A780), then the walk packet (sub_2819D0) at the speed of the
        // table 0x693300 for the motion row (enemies: their MODEL row's +36 column by the skill's kind bit 0x2) times
        // 0x7CB090, and the camera packet sub_2A3B40(action, 20), both owned by the action (+96 = its uid).
        // 0x0028e8e8
        charge(ctx, 24);
        a0 = s1;
        jal(ctx, 0x28E8ECu, gen::fn_sub_28A780_0028a780);
        a1 = 2;
        lhu(v1, s1, act::kCmdSkill);
        v0 = sll(v1, 2);
        v0 = addu(v0, v1);
        v0 = sll(v0, 1);
        v0 = addu(v0, v1);
        v1 = sll(v0, 2);
        lw(v0, gp, kGpSkillTbl);  // gBtlSkillTbl
        v0 = addu(v0, v1);
        lbu(v0, v0, 0);
        v0 = v0 & 0x2;
        v0 = sltu(0, v0);
        v0 = v0 ^ 0x1;
        a3 = v0 & 0xFFFF;
        lw(a0, s1, act::kUnit);
        lw(v0, a0, unit::kDat);
        lhu(a2, v0, dat::kId);
        lbu(v1, a0, unit::kSide);
        v0 = 1;
        if (v1 == v0) {
            // 0x0028e958
            charge(ctx, 12);
            lw(a1, gp, kGpModelEnemy);  // MODEL.TBL section 2 (232-byte rows by enemy id) 0x7CE418
            v1 = a2 & 0xFFFF;
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            v0 = sll(v0, 3);
            v1 = addu(v0, a1);
            v0 = a3 & 0xFFFF;
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lhu(a1, v0, 36);
        } else {
            // 0x0028e948
            charge(ctx, 2);
            if (v1 != 0) {
                // 0x0028e950
                charge(ctx, 2);
            }
        }
        // 0x0028e988
        charge(ctx, 30);
        v0 = a1 & 0xFFFF;
        v1 = sll(v0, 2);
        v0 = 0x690000;
        v0 = addiu(v0, 13056);  // &0x693300
        v0 = addu(v0, v1);
        lwc1(f1, v0, 0);
        lwc1(f0, gp, -31840);  // 0x7CB090
        mul_s(f12, f1, f0);
        a1 = addiu(sp, 0x30);
        a2 = 0;
        jal(ctx, 0x28E9B0u, gen::fn_sub_2819D0_002819d0);
        a0 = v0;
        ld(v1, s1, act::kUid);
        sd(v1, v0, pkt::kOwner);
        a1 = 1;
        jal(ctx, 0x28E9C8u, gen::fn_sub_27ED20_0027ed20);
        a0 = s1;
        a1 = 20;
        jal(ctx, 0x28E9D8u, gen::fn_sub_2A3B40_002a3b40);
        a0 = v0;
        ld(v1, s1, act::kUid);
        sd(v1, v0, pkt::kOwner);
        a1 = 0;
        jal(ctx, 0x28E9F0u, gen::fn_sub_27ED20_0027ed20);
    }
    epilogue();
}

// 0x00296320 sub_296320 -- 456 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Action state init for the commands 7 / 8 / 11 (guard / analyse / wait): for 7 the guard packets (camera, effect,
// motion, voice); then the action-done packet and state 25 (one more pending) or 30.
// Arguments: a0 btlAction.
void sub_296320(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00296320
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lhu(v1, a0, act::kCmdKind);
    v0 = 11;
    if (v1 != v0) {
        // 0x00296340
        charge(ctx, 3);
        v0 = 8;
        if (v1 != v0) {
            // 0x0029634c
            charge(ctx, 3);
            v0 = 7;
            if (v1 == v0) {
                // 0x00296360
                charge(ctx, 25);
                jal(ctx, 0x296360u, gen::fn_sub_28A780_0028a780);
                a0 = 0;
                a1 = 3;
                jal(ctx, 0x296370u, gen::fn_sub_288950_00288950);
                a0 = v0;
                ld(v1, s0, act::kUid);
                sd(v1, v0, 96);
                a1 = 0;
                jal(ctx, 0x296388u, gen::fn_sub_27ED20_0027ed20);
                a0 = s0;
                a1 = 9;
                jal(ctx, 0x296398u, gen::fn_sub_2A3B40_002a3b40);
                a0 = v0;
                ld(v1, s0, act::kUid);
                sd(v1, v0, 96);
                a1 = 0;
                jal(ctx, 0x2963B0u, gen::fn_sub_27ED20_0027ed20);
                lh(a1, s0, act4::kGuardKind);
                if (a1 == 0) {
                    // 0x002963f0
                    charge(ctx, 10);
                    lw(a0, s0, act::kUnit);
                    lhu(a1, s0, act::kCmdKind);
                    jal(ctx, 0x2963F8u, gen::fn_sub_2BD780_002bd780);
                    a0 = v0;
                    ld(v1, s0, act::kUid);
                    sd(v1, v0, 96);
                    a1 = 3;
                    jal(ctx, 0x296410u, gen::fn_sub_27ED20_0027ed20);
                } else {
                    // 0x002963c4
                    charge(ctx, 11);
                    lw(a0, s0, act::kUnit);
                    jal(ctx, 0x2963C8u, gen::fn_sub_2BD850_002bd850);
                    a0 = v0;
                    ld(v1, s0, act::kUid);
                    sd(v1, v0, 96);
                    a1 = 3;
                    jal(ctx, 0x2963E0u, gen::fn_sub_27ED20_0027ed20);
                }
                // 0x00296418
                charge(ctx, 15);
                a0 = s0;
                a1 = 26;
                a2 = 0;
                a3 = 0;
                t0 = 0;
                jal(ctx, 0x29642Cu, gen::fn_sub_2E2BE0_002e2be0);
                a0 = v0;
                ld(v1, s0, act::kUid);
                sd(v1, v0, 96);
                a1 = 1;
                jal(ctx, 0x296444u, gen::fn_sub_27ED20_0027ed20);
            } else {
                // 0x00296358
                charge(ctx, 2);
                // 0x00296454
                charge(ctx, 5);
                a0 = 0x690000;
                a0 = addiu(a0, 13080);  // "btlAction.c"
                a1 = 7086;
                jal(ctx, 0x296460u, gen::fn_sub_19D3F0_0019d3f0);
            }
        }
    }
    // 0x00296468
    charge(ctx, 13);
    a0 = s0;
    a1 = 0;
    jal(ctx, 0x296470u, gen::fn_sub_2D7FB0_002d7fb0);
    a0 = v0;
    a1 = 1;
    jal(ctx, 0x296480u, gen::fn_sub_27ED20_0027ed20);
    a0 = s0;
    jal(ctx, 0x29648Cu, gen::fn_sub_2DC130_002dc130);
    if (v0 != 0) {
        // 0x0029649c
        charge(ctx, 4);
        lhu(v1, s0, act::kCmdKind);
        v0 = 8;
        if (v1 == v0) {
            goto L_002964c4;
        }
        // 0x002964ac
        charge(ctx, 6);
        a0 = s0;
        a1 = 25;
        jal(ctx, 0x2964B4u, gen::fn_btlActionSetState_00299d60);
        // 0x002964d4 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(ra, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x20);
        return;
    }
L_002964c4:
    charge(ctx, 4);
    a0 = s0;
    a1 = 30;
    jal(ctx, 0x2964CCu, gen::fn_btlActionSetState_00299d60);
    // 0x002964d4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00299520 sub_299520 -- 568 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Action state init: dead or the hero's own action -> state 1; else walks back to its place when farther than 75.
// Arguments: a0 btlAction.
void sub_299520(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x00299520
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(s0, a0, act::kUnit);
    sw(zero, a0, act::kAoaLeader);
    lw(a0, s0, unit::kDat);
    a1 = 0;
    jal(ctx, 0x299544u, gen::fn_datCalcIsDead_0030b5a0);
    if (v0 == 0) {
        // 0x002995a0
        charge(ctx, 4);
        jal(ctx, 0x2995A0u, gen::fn_sub_29AD20_0029ad20);
        if (s1 != v0) {
            // 0x002995c8
            charge(ctx, 6);
            lw(a1, gp, kGpBtl);  // gBtl 0x7CE3EC
            lw(a0, a1, gbtl::kFlags);
            v1 = 0x400000;
            v1 = a0 & v1;
            if (v1 != 0) {
                // 0x002995e0
                charge(ctx, 4);
                lhu(v1, a1, gbtl::kFxRequest);
                v1 = v1 & 0x2;
                if (v1 == 0) {
                    goto L_002995f0;
                }
                // 0x00299740 (the shared epilogue, written out on this path)
                charge(ctx, 6);
                ld(ra, sp, 0x20);
                lq(s1, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x40);
                return;
            }
        L_002995f0:
            charge(ctx, 7);
            lw(v0, s1, 48);
            lw(a0, v0, 2604);
            a1 = 0x180000;
            jal(ctx, 0x2995FCu, gen::fn_datCalcChkBadStatus_00300580);
            if (v0 == 0) {
                // 0x0029960c
                charge(ctx, 10);
                a0 = s0;
                a1 = addiu(sp, 0x30);
                a2 = 0;
                a3 = 0;
                jal(ctx, 0x29961Cu, gen::fn_sub_27F7C0_0027f7c0);
                lw(v0, s1, 48);
                lbu(v0, v0, 162);
                if (v0 == 0) {
                    // 0x00299634
                    charge(ctx, 2);
                    v0 = 1;
                    sw(v0, s1, 1156);
                }
                // 0x0029963c
                charge(ctx, 10);
                a0 = addiu(s0, 4);
                a1 = addiu(sp, 0x30);
                jal(ctx, 0x299644u, gen::fn_sub_2D1ED0_002d1ed0);
                v1 = 0x42960000;
                mtc1(v1, f1);
                c_le_s(f0, f1);
                if (!cond(ctx)) {
                    // 0x00299664
                    charge(ctx, 21);
                    a1 = 2;
                    lhu(v1, s1, 110);
                    v0 = sll(v1, 2);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 1);
                    v0 = addu(v0, v1);
                    v1 = sll(v0, 2);
                    lw(v0, gp, kGpSkillTbl);  // gBtlSkillTbl
                    v0 = addu(v0, v1);
                    lbu(v0, v0, 0);
                    v0 = v0 & 0x2;
                    v0 = sltu(0, v0);
                    v0 = v0 ^ 0x1;
                    a3 = v0 & 0xFFFF;
                    lw(a0, s1, 48);
                    lw(v0, a0, 2604);
                    lhu(a2, v0, 2);
                    lbu(v1, a0, 162);
                    v0 = 1;
                    if (v1 == v0) {
                        // 0x002996c8
                        charge(ctx, 12);
                        lw(a1, gp, kGpModelEnemy);  // MODEL.TBL section 2 (232-byte rows by enemy id) 0x7CE418
                        v1 = a2 & 0xFFFF;
                        v0 = sll(v1, 3);
                        v0 = subu(v0, v1);
                        v0 = sll(v0, 2);
                        v0 = addu(v0, v1);
                        v0 = sll(v0, 3);
                        v1 = addu(v0, a1);
                        v0 = a3 & 0xFFFF;
                        v0 = sll(v0, 2);
                        v0 = addu(v0, v1);
                        lhu(a1, v0, 36);
                    } else {
                        // 0x002996b8
                        charge(ctx, 2);
                        if (v1 != 0) {
                            // 0x002996c0
                            charge(ctx, 2);
                        }
                    }
                    // 0x002996f8
                    charge(ctx, 18);
                    v0 = a1 & 0xFFFF;
                    v1 = sll(v0, 2);
                    v0 = 0x690000;
                    v0 = addiu(v0, 13056);  // &0x693300
                    v0 = addu(v0, v1);
                    a1 = addiu(sp, 0x30);
                    lwc1(f12, v0, 0);
                    a2 = 0;
                    jal(ctx, 0x299718u, gen::fn_sub_2819D0_002819d0);
                    a0 = v0;
                    ld(v1, s1, 0);
                    sd(v1, v0, 96);
                    a1 = 1;
                    jal(ctx, 0x299730u, gen::fn_sub_27ED20_0027ed20);
                    v1 = 1;
                    sw(v1, s1, 1156);
                }
            }
        } else {
            // 0x002995b0
            charge(ctx, 6);
            a0 = s1;
            a1 = 1;
            jal(ctx, 0x2995B8u, gen::fn_btlActionSetState_00299d60);
        }
    } else {
        // 0x00299554
        charge(ctx, 4);
        lw(v0, s0, unit::kFlags);
        v0 = v0 & 0x40;
        if (v0 != 0) {
            // 0x00299564
            charge(ctx, 9);
            lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
            lw(v1, a0, gbtl::kFlags);
            v0 = 0x400000;
            v0 = v1 | v0;
            sw(v0, a0, gbtl::kFlags);
            lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
            lhu(v0, v1, gbtl::kFxRequest);
            v0 = v0 | 0x6;
            sh(v0, v1, gbtl::kFxRequest);
        }
        // 0x00299588
        charge(ctx, 6);
        a0 = s1;
        a1 = 1;
        jal(ctx, 0x299590u, gen::fn_btlActionSetState_00299d60);
    }
    // 0x00299740 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00299800 sub_299800 -- 400 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Action state (DEAD init): enemy -> spoils (sub_2D7560), the fade-out packets; party -> clears the effects.
// Arguments: a0 btlAction.
void sub_299800(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00299800
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(s0, a0, act::kUnit);
    jal(ctx, 0x299818u, gen::fn_sub_29A320_0029a320);
    lbu(a0, s0, unit::kSide);
    v1 = 1;
    if (a0 == v1) {
        // 0x00299874
        charge(ctx, 10);
        lh(a0, s0, unit::kId);
        jal(ctx, 0x299878u, gen::fn_sub_17C750_0017c750);
        a0 = s1;
        jal(ctx, 0x299884u, gen::fn_sub_2D7560_002d7560);
        lw(a0, s0, unit::kFlags);
        v1 = a0 & 0x20;
        if (v1 == 0) {
            // 0x0029989c
            charge(ctx, 3);
            v1 = a0 & 0x100;
            if (v1 == 0) {
                // 0x002998a8
                charge(ctx, 40);
                a0 = s0;
                v0 = 0xFF0000;
                a1 = v0 | 0xFFFF;  // &0xFFFFFF
                a2 = 6;
                a3 = 0;
                t0 = 4;
                t1 = 0;
                jal(ctx, 0x2998C4u, gen::fn_sub_285D30_00285d30);
                a0 = v0;
                ld(v1, s1, act::kUid);
                sd(v1, v0, 96);
                a1 = 1;
                jal(ctx, 0x2998DCu, gen::fn_sub_27ED20_0027ed20);
                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                lw(a0, v0, gbtl4::kFxCommon);
                a1 = s0;
                a2 = s0;
                a3 = 0;
                t0 = 0;
                jal(ctx, 0x2998FCu, gen::fn_sub_2BAF90_002baf90);
                a0 = v0;
                ld(v1, s1, act::kUid);
                sd(v1, v0, 96);
                a1 = 2;
                jal(ctx, 0x299914u, gen::fn_sub_27ED20_0027ed20);
                a0 = 10;
                a1 = 2;
                a2 = 8;
                jal(ctx, 0x299928u, gen::fn_sub_2DD100_002dd100);
                a0 = v0;
                ld(v1, s1, act::kUid);
                sd(v1, v0, 96);
                a1 = 1;
                jal(ctx, 0x299940u, gen::fn_sub_27ED20_0027ed20);
            }
        }
        // 0x00299948
        charge(ctx, 4);
        lw(a0, s0, unit::kFlags);
        v1 = a0 & 0x40;
        if (v1 == 0) {
            // 0x00299958
            charge(ctx, 3);
            v1 = a0 & 0x8;
            if (v1 != 0) {
                // 0x00299964
                charge(ctx, 5);
                v0 = si(-9);
                v0 = a0 & v0;
                sw(v0, s0, unit::kFlags);
                jal(ctx, 0x299970u, gen::fn_sub_1FDD40_001fdd40);
            }
        }
    } else {
        // 0x00299830
        charge(ctx, 2);
        if (a0 == 0) {
            // 0x00299840
            charge(ctx, 9);
            lw(a0, s0, unit::kDat);
            jal(ctx, 0x299844u, gen::fn_datCalcClearAllEffects_00301690);
            lw(v1, s0, unit::kDat);
            a1 = addiu(v1, 16);
            lb(a0, v1, dat4::kTactic);
            v1 = 10;
            if (a0 == v1) {
                // 0x00299864
                charge(ctx, 4);
                v1 = 1;
                sb(v1, a1, 0);
            }
        } else {
            // 0x00299838
            charge(ctx, 2);
        }
    }
    // 0x00299978 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0029EA50 sub_29EA50 -- 16 bytes; leaf frame (no stack)
// Address of gBtl +548.
void sub_29EA50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, gp{ctx, 28};
    // 0x0029ea50
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    v0 = addiu(v0, 548);
}

// 0x0029F150 sub_29F150 -- 860 bytes; frame 0x40: ra sp+0x20, s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// [btlFadeUpdateScale] Update of the colour-fade packet: while the scene runs (gBtl flags 2 and 0x2000000) lerps the
// two scene colours (sub_19FD40 / sub_19FD70) from the values taken on frame 0 to start * scale (+0..+28) over +96
// frames; done (1) at the end or when the fades are off.
// Arguments: a0 fade data.
void sub_29F150(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f20{ctx, 20}, f21{ctx, 21};
    // 0x0029f150
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s0 = a0;
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v1, v0, gbtl::kFlags);
    v0 = v1 & 0x2;
    if (v0 != 0) {
        // 0x0029f188
        charge(ctx, 4);
        v0 = 0x2000000;
        v0 = v1 & v0;
        if (v0 != 0) {
            // 0x0029f1a4
            charge(ctx, 3);
            lw(v0, s0, 100);
            if (v0 == 0) {
                // 0x0029f1b0
                charge(ctx, 52);
                jal(ctx, 0x29F1B0u, gen::fn_sub_19FD40_0019fd40);
                lwc1(f3, v0, 0);
                lwc1(f2, v0, 4);
                lwc1(f1, v0, 8);
                lwc1(f0, v0, 12);
                swc1(f3, s0, 64);
                swc1(f2, s0, 68);
                swc1(f1, s0, 72);
                swc1(f0, s0, 76);
                jal(ctx, 0x29F1D8u, gen::fn_sub_19FD70_0019fd70);
                lwc1(f3, v0, 0);
                lwc1(f2, v0, 4);
                lwc1(f1, v0, 8);
                lwc1(f0, v0, 12);
                swc1(f3, s0, 80);
                swc1(f2, s0, 84);
                swc1(f1, s0, 88);
                swc1(f0, s0, 92);
                lwc1(f1, s0, 64);
                lwc1(f0, s0, 0);
                mul_s(f0, f1, f0);
                swc1(f0, s0, 32);
                lwc1(f1, s0, 68);
                lwc1(f0, s0, 4);
                mul_s(f0, f1, f0);
                swc1(f0, s0, 36);
                lwc1(f1, s0, 72);
                lwc1(f0, s0, 8);
                mul_s(f0, f1, f0);
                swc1(f0, s0, 40);
                lwc1(f1, s0, 76);
                lwc1(f0, s0, 12);
                mul_s(f0, f1, f0);
                swc1(f0, s0, 44);
                lwc1(f1, s0, 80);
                lwc1(f0, s0, 16);
                mul_s(f0, f1, f0);
                swc1(f0, s0, 48);
                lwc1(f1, s0, 84);
                lwc1(f0, s0, 20);
                mul_s(f0, f1, f0);
                swc1(f0, s0, 52);
                lwc1(f1, s0, 88);
                lwc1(f0, s0, 24);
                mul_s(f0, f1, f0);
                swc1(f0, s0, 56);
                lwc1(f1, s0, 92);
                lwc1(f0, s0, 28);
                mul_s(f0, f1, f0);
                swc1(f0, s0, 60);
            }
            // 0x0029f280
            charge(ctx, 5);
            lw(a0, s0, 96);
            lw(v0, s0, 100);
            at = sltu(v0, a0);
            if (at == 0) {
                // 0x0029f424
                charge(ctx, 23);
                jal(ctx, 0x29F424u, gen::fn_sub_19FD40_0019fd40);
                lwc1(f3, s0, 32);
                lwc1(f2, s0, 36);
                lwc1(f1, s0, 40);
                lwc1(f0, s0, 44);
                swc1(f3, v0, 0);
                swc1(f2, v0, 4);
                swc1(f1, v0, 8);
                swc1(f0, v0, 12);
                jal(ctx, 0x29F44Cu, gen::fn_sub_19FD70_0019fd70);
                lwc1(f3, s0, 48);
                lwc1(f2, s0, 52);
                lwc1(f1, s0, 56);
                lwc1(f0, s0, 60);
                swc1(f3, v0, 0);
                swc1(f2, v0, 4);
                swc1(f1, v0, 8);
                swc1(f0, v0, 12);
                v0 = 1;
            } else {
                // 0x0029f294
                charge(ctx, 2);
                if (i64(v0) < 0) {
                    // 0x0029f2b0
                    charge(ctx, 7);
                    v1 = srl(v0, 1);
                    v0 = v0 & 0x1;
                    v1 = v1 | v0;
                    mtc1(v1, f0);
                    cvt_s_w(f1, f0);
                    add_s(f1, f1, f1);
                } else {
                    // 0x0029f29c
                    charge(ctx, 5);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                }
                // 0x0029f2cc
                charge(ctx, 2);
                if (i64(a0) < 0) {
                    // 0x0029f2e8
                    charge(ctx, 7);
                    v1 = srl(a0, 1);
                    v0 = a0 & 0x1;
                    v1 = v1 | v0;
                    mtc1(v1, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f0, f0);
                } else {
                    // 0x0029f2d4
                    charge(ctx, 5);
                    mtc1(a0, f0);
                    cvt_s_w(f0, f0);
                }
                // 0x0029f304
                charge(ctx, 72);
                div_s(f21, f1, f0);
                v0 = 0x3F800000;
                mtc1(v0, f0);
                sub_s(f20, f0, f21);
                lwc1(f0, s0, 64);
                mul_s(f7, f0, f20);
                lwc1(f0, s0, 68);
                mul_s(f6, f0, f20);
                lwc1(f0, s0, 72);
                mul_s(f5, f0, f20);
                lwc1(f0, s0, 76);
                mula_s(f0, f20);
                lwc1(f0, s0, 32);
                mul_s(f4, f0, f21);
                lwc1(f0, s0, 36);
                mul_s(f3, f0, f21);
                lwc1(f0, s0, 40);
                mul_s(f2, f0, f21);
                lwc1(f1, s0, 44);
                add_s(f0, f7, f4);
                swc1(f0, sp, 0x30);
                add_s(f0, f6, f3);
                swc1(f0, sp, 0x34);
                add_s(f0, f5, f2);
                swc1(f0, sp, 0x38);
                madd_s(f0, f1, f21);
                swc1(f0, sp, 0x3C);
                jal(ctx, 0x29F37Cu, gen::fn_sub_19FD40_0019fd40);
                lwc1(f3, sp, 0x30);
                lwc1(f2, sp, 0x34);
                lwc1(f1, sp, 0x38);
                lwc1(f0, sp, 0x3C);
                swc1(f3, v0, 0);
                swc1(f2, v0, 4);
                swc1(f1, v0, 8);
                swc1(f0, v0, 12);
                lwc1(f1, s0, 80);
                lwc1(f0, s0, 48);
                mula_s(f0, f21);
                madd_s(f0, f1, f20);
                swc1(f0, sp, 0x30);
                lwc1(f1, s0, 84);
                lwc1(f0, s0, 52);
                mula_s(f0, f21);
                madd_s(f0, f1, f20);
                swc1(f0, sp, 0x34);
                lwc1(f1, s0, 88);
                lwc1(f0, s0, 56);
                mula_s(f0, f21);
                madd_s(f0, f1, f20);
                swc1(f0, sp, 0x38);
                lwc1(f1, s0, 92);
                lwc1(f0, s0, 60);
                mula_s(f0, f21);
                madd_s(f0, f1, f20);
                swc1(f0, sp, 0x3C);
                jal(ctx, 0x29F3F4u, gen::fn_sub_19FD70_0019fd70);
                lwc1(f3, sp, 0x30);
                lwc1(f2, sp, 0x34);
                lwc1(f1, sp, 0x38);
                lwc1(f0, sp, 0x3C);
                swc1(f3, v0, 0);
                swc1(f2, v0, 4);
                swc1(f1, v0, 8);
                swc1(f0, v0, 12);
                // 0x0029f480
                charge(ctx, 4);
                lw(v0, s0, 100);
                v0 = addiu(v0, 1);
                sw(v0, s0, 100);
                v0 = 0;
            }
        } else {
            // 0x0029f198
            charge(ctx, 3);
            v0 = 1;
        }
    } else {
        // 0x0029f17c
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x0029f490 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0029F760 sub_29F760 -- 748 bytes; frame 0x40: ra sp+0x20, s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// [btlFadeUpdateToBtl] As sub_29F150 towards gBtl's fade colours A / B (+404 / +420) over +32 frames.
// Arguments: a0 fade data.
void sub_29F760(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f20{ctx, 20}, f21{ctx, 21};
    // 0x0029f760
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s0 = a0;
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v1, v0, gbtl::kFlags);
    v0 = v1 & 0x2;
    if (v0 != 0) {
        // 0x0029f798
        charge(ctx, 4);
        v0 = 0x2000000;
        v0 = v1 & v0;
        if (v0 != 0) {
            // 0x0029f7b4
            charge(ctx, 3);
            lw(v0, s0, 36);
            if (v0 == 0) {
                // 0x0029f7c0
                charge(ctx, 20);
                jal(ctx, 0x29F7C0u, gen::fn_sub_19FD40_0019fd40);
                lwc1(f3, v0, 0);
                lwc1(f2, v0, 4);
                lwc1(f1, v0, 8);
                lwc1(f0, v0, 12);
                swc1(f3, s0, 0);
                swc1(f2, s0, 4);
                swc1(f1, s0, 8);
                swc1(f0, s0, 12);
                jal(ctx, 0x29F7E8u, gen::fn_sub_19FD70_0019fd70);
                lwc1(f3, v0, 0);
                lwc1(f2, v0, 4);
                lwc1(f1, v0, 8);
                lwc1(f0, v0, 12);
                swc1(f3, s0, 16);
                swc1(f2, s0, 20);
                swc1(f1, s0, 24);
                swc1(f0, s0, 28);
            }
            // 0x0029f810
            charge(ctx, 5);
            lw(a0, s0, 32);
            lw(v0, s0, 36);
            at = sltu(v0, a0);
            if (at == 0) {
                // 0x0029f9bc
                charge(ctx, 25);
                lw(s0, gp, kGpBtl);  // gBtl 0x7CE3EC
                jal(ctx, 0x29F9C0u, gen::fn_sub_19FD40_0019fd40);
                lwc1(f3, s0, gbtl::kFadeColA);
                lwc1(f2, s0, gbtl::kFadeColA + 4);
                lwc1(f1, s0, gbtl::kFadeColA + 8);
                lwc1(f0, s0, gbtl::kFadeColA + 12);
                swc1(f3, v0, 0);
                swc1(f2, v0, 4);
                swc1(f1, v0, 8);
                swc1(f0, v0, 12);
                lw(s0, gp, kGpBtl);  // gBtl 0x7CE3EC
                jal(ctx, 0x29F9ECu, gen::fn_sub_19FD70_0019fd70);
                lwc1(f3, s0, gbtl::kFadeColB);
                lwc1(f2, s0, gbtl::kFadeColB + 4);
                lwc1(f1, s0, gbtl::kFadeColB + 8);
                lwc1(f0, s0, gbtl::kFadeColB + 12);
                swc1(f3, v0, 0);
                swc1(f2, v0, 4);
                swc1(f1, v0, 8);
                swc1(f0, v0, 12);
                v0 = 1;
            } else {
                // 0x0029f824
                charge(ctx, 2);
                if (i64(v0) < 0) {
                    // 0x0029f840
                    charge(ctx, 7);
                    v1 = srl(v0, 1);
                    v0 = v0 & 0x1;
                    v1 = v1 | v0;
                    mtc1(v1, f0);
                    cvt_s_w(f1, f0);
                    add_s(f1, f1, f1);
                } else {
                    // 0x0029f82c
                    charge(ctx, 5);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                }
                // 0x0029f85c
                charge(ctx, 2);
                if (i64(a0) < 0) {
                    // 0x0029f878
                    charge(ctx, 7);
                    v1 = srl(a0, 1);
                    v0 = a0 & 0x1;
                    v1 = v1 | v0;
                    mtc1(v1, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f0, f0);
                } else {
                    // 0x0029f864
                    charge(ctx, 5);
                    mtc1(a0, f0);
                    cvt_s_w(f0, f0);
                }
                // 0x0029f894
                charge(ctx, 74);
                div_s(f21, f1, f0);
                v0 = 0x3F800000;
                mtc1(v0, f0);
                sub_s(f20, f0, f21);
                lwc1(f0, s0, 0);
                mul_s(f7, f0, f20);
                lwc1(f0, s0, 4);
                mul_s(f6, f0, f20);
                lwc1(f0, s0, 8);
                mul_s(f5, f0, f20);
                lwc1(f0, s0, 12);
                mula_s(f0, f20);
                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                lwc1(f0, v0, gbtl::kFadeColA);
                mul_s(f4, f0, f21);
                lwc1(f0, v0, gbtl::kFadeColA + 4);
                mul_s(f3, f0, f21);
                lwc1(f0, v0, gbtl::kFadeColA + 8);
                mul_s(f2, f0, f21);
                lwc1(f1, v0, gbtl::kFadeColA + 12);
                add_s(f0, f7, f4);
                swc1(f0, sp, 0x30);
                add_s(f0, f6, f3);
                swc1(f0, sp, 0x34);
                add_s(f0, f5, f2);
                swc1(f0, sp, 0x38);
                madd_s(f0, f1, f21);
                swc1(f0, sp, 0x3C);
                jal(ctx, 0x29F910u, gen::fn_sub_19FD40_0019fd40);
                lwc1(f3, sp, 0x30);
                lwc1(f2, sp, 0x34);
                lwc1(f1, sp, 0x38);
                lwc1(f0, sp, 0x3C);
                swc1(f3, v0, 0);
                swc1(f2, v0, 4);
                swc1(f1, v0, 8);
                swc1(f0, v0, 12);
                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                lwc1(f1, s0, 16);
                lwc1(f0, v0, gbtl::kFadeColB);
                mula_s(f0, f21);
                madd_s(f0, f1, f20);
                swc1(f0, sp, 0x30);
                lwc1(f1, s0, 20);
                lwc1(f0, v0, gbtl::kFadeColB + 4);
                mula_s(f0, f21);
                madd_s(f0, f1, f20);
                swc1(f0, sp, 0x34);
                lwc1(f1, s0, 24);
                lwc1(f0, v0, gbtl::kFadeColB + 8);
                mula_s(f0, f21);
                madd_s(f0, f1, f20);
                swc1(f0, sp, 0x38);
                lwc1(f1, s0, 28);
                lwc1(f0, v0, gbtl::kFadeColB + 12);
                mula_s(f0, f21);
                madd_s(f0, f1, f20);
                swc1(f0, sp, 0x3C);
                jal(ctx, 0x29F98Cu, gen::fn_sub_19FD70_0019fd70);
                lwc1(f3, sp, 0x30);
                lwc1(f2, sp, 0x34);
                lwc1(f1, sp, 0x38);
                lwc1(f0, sp, 0x3C);
                swc1(f3, v0, 0);
                swc1(f2, v0, 4);
                swc1(f1, v0, 8);
                swc1(f0, v0, 12);
                // 0x0029fa20
                charge(ctx, 4);
                lw(v0, s0, 36);
                v0 = addiu(v0, 1);
                sw(v0, s0, 36);
                v0 = 0;
            }
        } else {
            // 0x0029f7a8
            charge(ctx, 3);
            v0 = 1;
        }
    } else {
        // 0x0029f78c
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x0029fa30 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x002B1020 sub_2B1020 -- 48 bytes; frame 0x10: ra sp+0x0
// Camera shot callback: sub_2B0280(camera, 0, 0).
// Arguments: a0 camera.
void sub_2B1020(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x002b1020
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v0 = 0x42480000;
    mtc1(v0, f12);
    a1 = 0;
    a2 = 0;
    jal(ctx, 0x2B1038u, gen::fn_sub_2B0280_002b0280);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002B4DB0 sub_2B4DB0 -- 400 bytes; frame 0xB0: ra sp+0x20, s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// Camera shot: frames the whole party (sub_280870 of side mask 3) from the fixed direction 0x697880 / 0x697890.
// Arguments: a0 camera.
void sub_2B4DB0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21};
    // 0x002b4db0
    enter(ctx, 72);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    sd(ra, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s0 = a0;
    mov_s(f21, f12);
    a0 = 3;
    a1 = 0;
    a2 = addiu(sp, 0xA0);
    a3 = 0;
    t0 = 0;
    t1 = 1;
    jal(ctx, 0x2B4DE4u, gen::fn_sub_280870_00280870);
    mov_s(f20, f0);
    sw(zero, sp, 0xA4);
    v0 = lui(0xC18C);
    mtc1(v0, f12);
    a0 = addiu(sp, 0x30);
    a1 = 0x690000;
    a1 = addiu(a1, 30832);  // &0x697870
    a2 = 0;
    jal(ctx, 0x2B4E0Cu, gen::fn_sub_4C31B0_004c31b0);
    a0 = addiu(sp, 0x30);
    a1 = 0x690000;
    a1 = addiu(a1, 30848);  // &0x697880
    lwc1(f12, s0, 256);
    a2 = 2;
    jal(ctx, 0x2B4E28u, gen::fn_sub_4C31B0_004c31b0);
    a0 = addiu(sp, 0x90);
    a1 = 0x690000;
    a1 = addiu(a1, 30864);  // &0x697890
    a2 = addiu(sp, 0x30);
    jal(ctx, 0x2B4E40u, gen::fn_sub_4C6C60_004c6c60);
    v0 = 0x3F000000;
    mtc1(v0, f1);
    lwc1(f0, s0, 184);
    mul_s(f1, f1, f0);
    lwc1(f0, gp, -32656);  // 0x7CAD60
    mul_s(f12, f0, f1);
    jal(ctx, 0x2B4E60u, gen::fn_tanf_0052e930);
    mul_s(f1, f20, f21);
    div_s(f1, f1, f0);
    lwc1(f0, sp, 0x90);
    mul_s(f0, f0, f1);
    swc1(f0, sp, 0x70);
    lwc1(f0, sp, 0x94);
    mul_s(f0, f0, f1);
    swc1(f0, sp, 0x74);
    lwc1(f0, sp, 0x98);
    mul_s(f0, f0, f1);
    swc1(f0, sp, 0x78);
    a0 = addiu(sp, 0x7C);
    a1 = addiu(sp, 0x70);
    a2 = addiu(sp, 0xA0);
    a3 = 0x690000;
    a3 = addiu(a3, 30848);  // &0x697880
    jal(ctx, 0x2B4EACu, gen::fn_sub_2A4690_002a4690);
    lwc1(f1, sp, 0x74);
    v0 = 0x41C80000;
    mtc1(v0, f0);
    c_lt_s(f1, f0);
    if (cond(ctx)) {
        // 0x002b4ed0
        charge(ctx, 1);
        swc1(f0, sp, 0x74);
    }
    // 0x002b4ed4
    charge(ctx, 12);
    lwc1(f1, s0, 256);
    v0 = 0x3E800000;
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, s0, 256);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v1, v0, gbtl::kFlags);
    v0 = 0x200000;
    v0 = v1 & v0;
    if (v0 == 0) {
        // 0x002b4f04
        charge(ctx, 4);
        a0 = addiu(sp, 0x70);
        a1 = a0;
        jal(ctx, 0x2B4F0Cu, gen::fn_sub_2A3590_002a3590);
    }
    // 0x002b4f14
    charge(ctx, 11);
    a0 = s0;
    a1 = addiu(sp, 0x70);
    jal(ctx, 0x2B4F1Cu, gen::fn_sub_2A2170_002a2170);
    ld(ra, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0xB0);
}

// 0x002B4FD0 sub_2B4FD0 -- 36 bytes; frame 0x10: ra sp+0x0
// Camera shot callback: sub_2B4DB0.
// Arguments: a0 camera.
void sub_2B4FD0(EEContext& ctx) {
    using namespace hg;
    Gpr gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x002b4fd0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lwc1(f12, gp, -32604);  // 0x7CAD94
    jal(ctx, 0x2B4FDCu, gen::fn_sub_2B4DB0_002b4db0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002B5600 sub_2B5600 -- 72 bytes; frame 0x40: ra sp+0x10, s0 sp+0x0 (sq)
// Camera shot callback: the target from sub_2ADD10, applied with sub_2A2170.
// Arguments: a0 camera.
void sub_2B5600(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002b5600
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a1 = 0;
    a2 = 0;
    a3 = addiu(sp, 0x20);
    jal(ctx, 0x2B561Cu, gen::fn_sub_2ADD10_002add10);
    a0 = s0;
    a1 = addiu(sp, 0x20);
    jal(ctx, 0x2B562Cu, gen::fn_sub_2A2170_002a2170);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x002B93E0 sub_2B93E0 -- 272 bytes; frame 0x90: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlFxCreateInstance] Creates an effect instance record (RwMalloc 92 + 4 * count): the EFFECT bank a0, entry a1
// (788-byte rows from +8, count +16), the callbacks a2 / a3, user a4; +16 = -1; entry 1 rolls +20 = datCalcRand(100).
// Arguments: a0 bank, a1 entry, a2, a3, a4.
void sub_2B93E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002b93e0
    enter(ctx, 51);  // entry check point + this block's cycles
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
    s5 = a0;
    s4 = a1;
    s3 = a2;
    s6 = a3;
    s7 = t0;
    v1 = s4 & 0xFFFF;
    v0 = 788;
    mult(s0, v1, v0);
    v0 = addu(s0, s5);
    lhu(v0, v0, 16);
    v0 = sll(v0, 2);
    s1 = addiu(v0, 92);
    a0 = s1;
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x2B9448u, v0.u());
    s2 = v0;
    a0 = s2;
    a1 = 0;
    a2 = s1;
    jal(ctx, 0x2B9460u, gen::fn_memset_00521408);
    sw(s5, s2, 0);
    v0 = addu(s5, s0);
    v0 = addiu(v0, 8);
    sw(v0, s2, 4);
    lhu(v0, v0, 8);
    sh(v0, s2, 84);
    v0 = addiu(s2, 92);
    sw(v0, s2, 88);
    v0 = si(-1);
    sw(v0, s2, 16);
    sw(s3, s2, 24);
    sw(s6, s2, 28);
    sw(s7, s2, 8);
    v1 = s4 & 0xFFFF;
    v0 = 1;
    if (v1 == v0) {
        // 0x002b94ac
        charge(ctx, 4);
        a0 = 100;
        jal(ctx, 0x2B94B0u, gen::fn_datCalcRand_002ffbc0);
        sb(v0, s2, 20);
    }
    // 0x002b94bc (the shared epilogue, written out on this path)
    charge(ctx, 13);
    v0 = s2;
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

// 0x002BAA20 sub_2BAA20 -- 168 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlFxPktHoldFile] Hold callback of an effect-file packet: handle use count +1586 + 1 (re-binds on the second use
// with flag 8), requests the file unless flag 1, marks the handle loading (+1584 bit 0).
// Arguments: a0 packet data.
void sub_2BAA20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002baa20
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(s0, a0, 0);
    lhu(v1, s0, 1586);
    v1 = addiu(v1, 1);
    sh(v1, s0, 1586);
    lhu(v1, s0, 1584);
    v1 = v1 & 0x8;
    if (v1 != 0) {
        // 0x002baa54
        charge(ctx, 4);
        lhu(a0, s0, 1586);
        v1 = 2;
        if (a0 == v1) {
            // 0x002baa64
            charge(ctx, 4);
            a0 = s0;
            lw(a1, s0, 1588);
            jal(ctx, 0x2BAA6Cu, gen::fn_sub_2B90D0_002b90d0);
        }
    }
    // 0x002baa74
    charge(ctx, 4);
    lhu(v1, s1, 12);
    v1 = v1 & 0x1;
    if (v1 != 0) {
        // 0x002baaa0
        charge(ctx, 1);
        sw(zero, s1, 4);
    } else {
        // 0x002baa84
        charge(ctx, 7);
        lw(a0, s1, 8);
        a1 = 0;
        jal(ctx, 0x2BAA8Cu, gen::fn_H_Cdvd_Request_00100d80);
        sw(v0, s1, 4);
    }
    // 0x002baaa4 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    lhu(v1, s0, 1584);
    v1 = v1 | 0x1;
    sh(v1, s0, 1584);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002BAAD0 sub_2BAAD0 -- 300 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlFxPktUpdateFile] Update of the effect-file packet: requests the file if needed; once loaded binds it
// (sub_2B90D0), destroys the request, marks the handle loaded (bit 1), drops a use and frees the handle (slot
// 0x96017C) on the last one.
// Arguments: a0 packet data.
void sub_2BAAD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002baad0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(s0, a0, 0);
    lw(v0, a0, 4);
    if (v0 == 0) {
        // 0x002baaf4
        charge(ctx, 5);
        lw(a0, s1, 8);
        a1 = 0;
        jal(ctx, 0x2BAAFCu, gen::fn_H_Cdvd_Request_00100d80);
        sw(v0, s1, 4);
    }
    // 0x002bab08
    charge(ctx, 5);
    lw(a0, s1, 4);
    jal(ctx, 0x2BAB0Cu, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
    if (v0 == 0) {
        // 0x002babe0
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x002bab1c
        charge(ctx, 24);
        lw(a0, s1, 8);
        a1 = addiu(sp, 0x3C);
        jal(ctx, 0x2BAB24u, gen::fn_H_Cdvd_CacheFindFile_001021c0);
        a0 = s0;
        a1 = v0;
        jal(ctx, 0x2BAB34u, gen::fn_sub_2B90D0_002b90d0);
        lw(a0, s1, 4);
        jal(ctx, 0x2BAB40u, gen::fn_H_Cdvd_Destroy_00100ec0);
        lhu(v0, s0, 1584);
        v0 = v0 & 0xFFFE;
        sh(v0, s0, 1584);
        lhu(v0, s0, 1584);
        v0 = v0 | 0x2;
        sh(v0, s0, 1584);
        lhu(v0, s0, 1586);
        v0 = addiu(v0, -1);
        sh(v0, s0, 1586);
        lhu(v0, s0, 1584);
        v0 = v0 & 0x8;
        if (v0 != 0) {
            // 0x002bab7c
            charge(ctx, 4);
            lhu(v1, s0, 1586);
            v0 = 1;
            if (v1 == v0) {
                // 0x002bab8c
                charge(ctx, 3);
                a0 = s0;
                jal(ctx, 0x2BAB90u, gen::fn_sub_2B9220_002b9220);
            }
        }
        // 0x002bab98
        charge(ctx, 3);
        lhu(v0, s0, 1586);
        if (v0 == 0) {
            // 0x002baba4
            charge(ctx, 4);
            lhu(v0, s0, 1584);
            v0 = v0 & 0x2;
            if (v0 != 0) {
                // 0x002babb4
                charge(ctx, 3);
                a0 = s0;
                jal(ctx, 0x2BABB8u, gen::fn_sub_2B9220_002b9220);
            }
            // 0x002babc0
            charge(ctx, 5);
            a0 = s0;
            v0 = 0x960000;
            lw(v0, v0, 380);  // 0x96017C
            jalr(ctx, 0x2BABCCu, v0.u());
        }
        // 0x002babd4
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x002babe4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x002BB6F0 sub_2BB6F0 -- 100 bytes; frame 0x10: ra sp+0x0
// [btlFxGetBedName] Skill effect file name: "battle/BTL_TEST.BED" in test mode (gBtl +20 bit 0), else "%s%03X.BED"
// with "skill/" and the skill id.
// Arguments: a0 skill, a1 out buffer.
void sub_2BB6F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002bb6f0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v0, v0, gbtl4::kTestFlags);
    v0 = v0 & 0x1;
    if (v0 == 0) {
        // 0x002bb728
        charge(ctx, 7);
        a3 = a0 & 0xFFFF;
        a0 = a1;
        a1 = 0x690000;
        a1 = addiu(a1, 25832);  // "%s%03X.BED"
        a2 = addiu(gp, -26120);  // "skill/"
        jal(ctx, 0x2BB73Cu, gen::fn_sprintf_00523ac8);
    } else {
        // 0x002bb70c
        charge(ctx, 7);
        a0 = a1;
        a1 = 0x690000;
        a1 = addiu(a1, 25808);  // "battle/BTL_TEST.BED"
        jal(ctx, 0x2BB718u, gen::fn_sprintf_00523ac8);
    }
    // 0x002bb744 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002BB7D0 sub_2BB7D0 -- 280 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlFxAllocObjects] Allocates the effect-object array of a unit: 48 records of 36 bytes (u16 0x200, +4 -1, +8 20)
// linked at the head of gBtl's effect-object list (+400; +28 prev, +32 next).
void sub_2BB7D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002bb7d0
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = 0x960000;
    s0 = addiu(s0, 376);  // &0x960178
    a0 = 200;
    a1 = 0x40000;
    lw(v0, s0, 0);  // 0x960178
    jalr(ctx, 0x2BB7FCu, v0.u());
    s3 = v0;
    a0 = s3;
    a1 = 0;
    a2 = 200;
    jal(ctx, 0x2BB814u, gen::fn_memset_00521408);
    s2 = 0;
    for (;;) {
        // 0x002bb8b8
        charge(ctx, 3);
        v0 = sltiu(s2, 48);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002bb828
        charge(ctx, 23);
        a0 = 36;
        a1 = 0x40000;
        lw(v0, s0, 0);
        jalr(ctx, 0x2BB834u, v0.u());
        s1 = v0;
        a0 = s1;
        a1 = 0;
        a2 = 36;
        jal(ctx, 0x2BB84Cu, gen::fn_memset_00521408);
        v0 = si(-1);
        sw(v0, s1, 4);
        v0 = 20;
        sb(v0, s1, 8);
        sw(zero, s1, 12);
        v0 = 512;
        sh(v0, s1, 0);
        sw(zero, s1, 28);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(v0, v0, gbtl::kFxObjList);
        if (v0 == 0) {
            // 0x002bb89c
            charge(ctx, 1);
            sw(zero, s1, 32);
        } else {
            // 0x002bb884
            charge(ctx, 6);
            sw(s1, v0, 28);
            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
            lw(v0, v0, gbtl::kFxObjList);
            sw(v0, s1, 32);
        }
        // 0x002bb8a0
        charge(ctx, 6);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        sw(s1, v0, gbtl::kFxObjList);
        v0 = sll(s2, 2);
        v0 = addu(s3, v0);
        sw(s1, v0, 0);
        s2 = addiu(s2, 1);
    }
    // 0x002bb8c4
    charge(ctx, 9);
    v0 = s3;
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x002BBC00 sub_2BBC00 -- 244 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlFxAllocGroup] Allocates an effect-object group (24 bytes: +4 a0, +16 / +20 -1) with one effect object linked
// into gBtl's list.
// Arguments: a0.
void sub_2BBC00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002bbc00
    enter(ctx, 43);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s0 = 0x960000;
    s0 = addiu(s0, 376);  // &0x960178
    a0 = 24;
    a1 = 0x40000;
    lw(v0, s0, 0);  // 0x960178
    jalr(ctx, 0x2BBC2Cu, v0.u());
    s1 = v0;
    sw(s2, v0, 4);
    v1 = si(-1);
    sh(v1, v0, 16);
    sb(zero, v0, 0);
    sw(v1, v0, 20);
    sw(zero, v0, 12);
    a0 = 36;
    a1 = 0x40000;
    lw(v0, s0, 0);  // 0x960178
    jalr(ctx, 0x2BBC5Cu, v0.u());
    s0 = v0;
    a0 = s0;
    a1 = 0;
    a2 = 36;
    jal(ctx, 0x2BBC74u, gen::fn_memset_00521408);
    v0 = si(-1);
    sw(v0, s0, 4);
    v0 = 20;
    sb(v0, s0, 8);
    sw(zero, s0, 12);
    v0 = 512;
    sh(v0, s0, 0);
    sw(zero, s0, 28);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v0, v0, gbtl::kFxObjList);
    if (v0 == 0) {
        // 0x002bbcc4
        charge(ctx, 1);
        sw(zero, s0, 32);
    } else {
        // 0x002bbcac
        charge(ctx, 6);
        sw(s0, v0, 28);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(v0, v0, gbtl::kFxObjList);
        sw(v0, s0, 32);
    }
    // 0x002bbcc8 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    sw(s0, v0, gbtl::kFxObjList);
    sw(s0, s1, 8);
    v0 = s1;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x002BC420 sub_2BC420 -- 88 bytes; frame 0x10: ra sp+0x0
// Release callback of the battle effect archive packet: destroys the request (gBtl +3348) unless the test mode bit
// 0x4000000.
void sub_2BC420(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002bc420
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a1, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(a0, a1, gbtl4::kTestFlags);
    v1 = 0x4000000;
    v1 = a0 & v1;
    if (v1 != 0) {
        // 0x002bc464
        charge(ctx, 1);
        sw(zero, a1, gbtl4::kFxArchiveReq);
    } else {
        // 0x002bc440
        charge(ctx, 3);
        lw(a0, a1, gbtl4::kFxArchiveReq);
        if (a0 != 0) {
            // 0x002bc44c
            charge(ctx, 2);
            jal(ctx, 0x2BC44Cu, gen::fn_H_Cdvd_Destroy_00100ec0);
        }
        // 0x002bc454
        charge(ctx, 4);
        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
        sw(zero, v1, gbtl4::kFxArchiveReq);
    }
    // 0x002bc468 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002BC480 sub_2BC480 -- 504 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlFxLoadArchive] Update of the battle effect archive packet: loads "snd_benc/btleff.bin" (or, in test mode, 60
// single files read synchronously) and binds its 60 entries as effect handles (sub_2B8F90(2) + sub_2B96E0) at gBtl
// +3108; sets gBtl flag 0x40000.
void sub_2BC480(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002bc480
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v1, a0, gbtl4::kTestFlags);
    v0 = 0x4000000;
    v0 = v1 & v0;
    if (v0 != 0) {
        // 0x002bc588
        charge(ctx, 3);
        s2 = 0;
        for (;;) {
            // 0x002bc634
            charge(ctx, 3);
            v0 = sltiu(s2, 60);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002bc594
            charge(ctx, 40);
            s0 = sll(s2, 2);
            v0 = 0x690000;
            v0 = addiu(v0, 27776);  // &0x696C80
            v0 = addu(v0, s0);
            lw(a0, v0, 0);
            a1 = 0;
            jal(ctx, 0x2BC5ACu, gen::fn_H_Cdvd_Request_00100d80);
            s3 = v0;
            a0 = s3;
            jal(ctx, 0x2BC5BCu, gen::fn_H_Cdvd_ReadSync_001023a0);
            a0 = 2;
            jal(ctx, 0x2BC5C8u, gen::fn_sub_2B8F90_002b8f90);
            lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
            v1 = addu(v1, s0);
            sw(v0, v1, 3108);
            lw(a0, s3, 280);
            a1 = 0x40000;
            v0 = 0x960000;
            lw(v0, v0, 376);  // 0x960178
            jalr(ctx, 0x2BC5ECu, v0.u());
            s1 = v0;
            lw(a2, s3, 280);
            a0 = s1;
            lw(a1, s3, 272);
            jal(ctx, 0x2BC604u, gen::fn_memcpy_00521250);
            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
            v0 = addu(v0, s0);
            lw(a0, v0, 3108);
            a1 = s1;
            jal(ctx, 0x2BC61Cu, gen::fn_sub_2B96E0_002b96e0);
            a0 = s3;
            jal(ctx, 0x2BC628u, gen::fn_H_Cdvd_Destroy_00100ec0);
            s2 = addiu(s2, 1);
        }
        // 0x002bc640
        charge(ctx, 6);
        lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(v1, a0, gbtl::kFlags);
        v0 = 0x40000;
        v0 = v1 | v0;
        sw(v0, a0, gbtl::kFlags);
        v0 = 1;
    } else {
        // 0x002bc4b0
        charge(ctx, 3);
        lw(a0, a0, gbtl4::kFxArchiveReq);
        if (a0 == 0) {
            // 0x002bc4bc
            charge(ctx, 9);
            a0 = 0x690000;
            a0 = addiu(a0, 28016);  // "snd_benc/btleff.bin"
            a1 = 1;
            jal(ctx, 0x2BC4C8u, gen::fn_H_Cdvd_Request_00100d80);
            lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
            sw(v0, v1, gbtl4::kFxArchiveReq);
            goto L_002bc57c;
        }
        // 0x002bc4e0
        charge(ctx, 4);
        jal(ctx, 0x2BC4E0u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
        if (v0 == 0) {
        L_002bc57c:
            charge(ctx, 3);
            v0 = 0;
        } else {
            // 0x002bc4f0
            charge(ctx, 3);
            s2 = 0;
            for (;;) {
                // 0x002bc550
                charge(ctx, 3);
                v0 = sltiu(s2, 60);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x002bc4fc
                charge(ctx, 21);
                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                lw(a0, v0, gbtl4::kFxArchiveReq);
                a1 = s2;
                a2 = addiu(sp, 0x5C);
                jal(ctx, 0x2BC50Cu, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                s1 = v0;
                s0 = sll(s2, 2);
                a0 = 2;
                jal(ctx, 0x2BC520u, gen::fn_sub_2B8F90_002b8f90);
                lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                v1 = addu(v1, s0);
                sw(v0, v1, 3108);
                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                v0 = addu(v0, s0);
                lw(a0, v0, 3108);
                a1 = s1;
                jal(ctx, 0x2BC544u, gen::fn_sub_2B96E0_002b96e0);
                s2 = addiu(s2, 1);
            }
            // 0x002bc55c
            charge(ctx, 8);
            lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
            lw(v1, a0, gbtl::kFlags);
            v0 = 0x40000;
            v0 = v1 | v0;
            sw(v0, a0, gbtl::kFlags);
            v0 = 1;
        }
    }
    // 0x002bc658 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x002BD5F0 sub_2BD5F0 -- 148 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Update of the skill-name banner packet: while names are shown (gBtl flag 0x200) shows the skill's name (sub_171110
// -> sub_1FE9B0) on the first frame, done after 45 frames; at once otherwise.
// Arguments: a0 packet data {.., u16 skill +4, frames +8}.
void sub_2BD5F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002bd5f0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v0, v0, gbtl::kFlags);
    v0 = v0 & 0x200;
    if (v0 != 0) {
        // 0x002bd620
        charge(ctx, 3);
        lw(v0, s0, 8);
        if (v0 == 0) {
            // 0x002bd62c
            charge(ctx, 7);
            lh(a0, s0, 4);
            a1 = 0;
            jal(ctx, 0x2BD634u, gen::fn_sub_171110_00171110);
            a0 = v0;
            jal(ctx, 0x2BD640u, gen::fn_sub_1FE9B0_001fe9b0);
        }
        // 0x002bd648
        charge(ctx, 6);
        lw(v0, s0, 8);
        v0 = addiu(v0, 1);
        sw(v0, s0, 8);
        v0 = sltiu(v0, 45);
        if (v0 != 0) {
            // 0x002bd66c
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x002bd660
            charge(ctx, 3);
            v0 = 1;
        }
    } else {
        // 0x002bd614
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x002bd670 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002BD6F0 sub_2BD6F0 -- 140 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Update of the result pop-up packet: shows the message of table 0x696DCC[+4] once, then waits 45 frames.
// Arguments: a0 packet data.
void sub_2BD6F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002bd768: the shared epilogue (v0 = done)
    auto epilogue = [&] {
        charge(ctx, 5);
        ld(ra, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x20);
    };
    // 0x002bd6f0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;                    // s0 = the packet data {.., u16 message +4, u32 frames +8}
    lw(v0, a0, 8);
    if (v0 == 0) {
        // 0x002bd70c: the first frame
        charge(ctx, 3);
        lhu(v0, s0, 4);
        if (v0 == 0) {
            // 0x002bd718: no message -- done at once
            charge(ctx, 3);
            v0 = 1;
            epilogue();
            return;
        }
        // 0x002bd724: show the message of the table 0x696DCC
        charge(ctx, 7);
        v1 = sll(v0, 2);
        v0 = 0x690000;
        v0 = addiu(v0, 28108);  // &0x696DCC
        v0 = addu(v0, v1);
        lw(a0, v0, 0);
        jal(ctx, 0x2BD738u, gen::fn_sub_1FE9B0_001fe9b0);
    }
    // 0x002bd740: count the frames; done after 45
    charge(ctx, 6);
    lw(v0, s0, 8);
    v0 = addiu(v0, 1);
    sw(v0, s0, 8);
    v0 = sltiu(v0, 45);
    if (v0 != 0) {
        // 0x002bd764
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x002bd758
        charge(ctx, 3);
        v0 = 1;
    }
    epilogue();
}

// 0x002BED10 sub_2BED10 -- 188 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Closes the open "battle_command_calc" task's menu: in the test mode (gBtl +20 bit 0x2000000) state 3 -> 6, else the
// panel close call (sub_1FE430 for an item command 4, else sub_1FDEC0) and state 2.
void sub_2BED10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002bed10
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0x690000;
    a0 = addiu(a0, 28496);  // "battle_command_calc"
    jal(ctx, 0x2BED24u, gen::fn_kwlnTaskGetTaskByName_00195340);
    a0 = v0;
    if (v0 != 0) {
        // 0x002bed38
        charge(ctx, 9);
        jal(ctx, 0x2BED38u, gen::fn_kwlnTaskGetWorkData_00195540);
        s0 = v0;
        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(a0, v1, gbtl4::kTestFlags);
        v1 = 0x2000000;
        v1 = a0 & v1;
        if (v1 == 0) {
            // 0x002bed7c
            charge(ctx, 5);
            lw(v0, s0, 4);
            lhu(v1, v0, 108);
            v0 = 4;
            if (v1 == v0) {
                // 0x002bed98
                charge(ctx, 4);
                jal(ctx, 0x2BED98u, gen::fn_sub_1FE430_001fe430);
            } else {
                // 0x002bed90
                charge(ctx, 2);
                // 0x002beda8
                charge(ctx, 2);
                jal(ctx, 0x2BEDA8u, gen::fn_sub_1FDEC0_001fdec0);
            }
            // 0x002bedb0
            charge(ctx, 2);
            v1 = 2;
            sh(v1, s0, 0);
        } else {
            // 0x002bed5c
            charge(ctx, 4);
            lhu(a0, s0, 0);
            v1 = 3;
            if (a0 == v1) {
                // 0x002bed6c
                charge(ctx, 4);
                v1 = 6;
                sh(v1, s0, 0);
            }
        }
    }
    // 0x002bedb8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002BF3F0 btlCommand_CreateBattleCommandCalcTasks -- 596 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Creates the "battle_command_calc" / "battle_command_draw" tasks for an action's command menu and sets the panel's
// menu items by the unit's state (ailments 0x80060 / 0x80274, sub_2C1CE0, action flag 0x400).
// Arguments: a0 btlAction.
void btlCommand_CreateBattleCommandCalcTasks(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002bf3f0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    jal(ctx, 0x2BF40Cu, gen::fn_sub_2D1A70_002d1a70);
    v1 = 1;
    if (v0 == v1) {
        // 0x002bf420
        charge(ctx, 5);
        lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(v1, a0, gbtl::kFlags);
        v0 = si(-16385);
        v0 = v1 & v0;
        sw(v0, a0, gbtl::kFlags);
    }
    // 0x002bf434
    charge(ctx, 6);
    a0 = 0x690000;
    a0 = addiu(a0, 28496);  // "battle_command_calc"
    jal(ctx, 0x2BF43Cu, gen::fn_kwlnTaskGetTaskByName_00195340);
    if (v0 == 0) {
        // 0x002bf458
        charge(ctx, 59);
        a0 = 20;
        a1 = 0x40000;
        v0 = 0x960000;
        lw(v0, v0, 376);  // 0x960178
        jalr(ctx, 0x2BF468u, v0.u());
        s2 = v0;
        a0 = s2;
        a1 = 0;
        a2 = 20;
        jal(ctx, 0x2BF480u, gen::fn_memset_00521408);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(a0, v0, gbtl4::kTask);
        a1 = 0x690000;
        a1 = addiu(a1, 28496);  // "battle_command_calc"
        a2 = 10;
        a3 = 0x2C0000;
        a3 = addiu(a3, -4320);  // &btlCommand_UpdateBattleCommandCalcTask
        t0 = 0x2C0000;
        t0 = addiu(t0, -3216);  // &sub_2BF370
        t1 = s2;
        jal(ctx, 0x2BF4B0u, gen::fn_kwlnTaskCreate_00194b20);
        sw(v0, s2, 16);
        a0 = v0;
        a1 = 0x690000;
        a1 = addiu(a1, 28528);  // "battle_command_draw"
        a2 = 4207;
        a3 = 0x2C0000;
        a3 = addiu(a3, -3408);  // &btlCommand_UpdateBattleCommandDrawTask
        t0 = 0;
        t1 = s2;
        jal(ctx, 0x2BF4DCu, gen::fn_kwlnTaskCreate_00194b20);
        lw(v1, s2, 16);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        sw(v1, v0, gbtl::kCmdCalcTask);
        v0 = 0x690000;
        sw(zero, v0, 28208);  // 0x696E30
        v0 = 0x690000;
        sw(zero, v0, 28212);  // 0x696E34
        v0 = 0x690000;
        v0 = addiu(v0, 28176);  // &0x696E10
        sw(v0, s2, 8);
        sw(v0, s2, 12);
        sw(s3, s2, 4);
        v0 = 2;
        sh(v0, s2, 0);
        lw(v0, s3, act::kUnit);
        lw(a0, v0, unit::kDat);
        jal(ctx, 0x2BF524u, gen::fn_datCalcGetBadStatus_00300550);
        s1 = v0;
        v0 = 0x80000;
        v0 = v0 | 0x60;
        s0 = s1 & v0;
        if (s0 == 0) {
            // 0x002bf554
            charge(ctx, 2);
            jal(ctx, 0x2BF554u, gen::fn_sub_1FED00_001fed00);
        } else {
            // 0x002bf544
            charge(ctx, 4);
            jal(ctx, 0x2BF544u, gen::fn_sub_1FECE0_001fece0);
        }
        // 0x002bf55c
        charge(ctx, 6);
        a0 = s3;
        a1 = 0;
        jal(ctx, 0x2BF564u, gen::fn_sub_2C1CE0_002c1ce0);
        if (v0 != 0) {
            // 0x002bf584
            charge(ctx, 2);
            jal(ctx, 0x2BF584u, gen::fn_sub_1FEE00_001fee00);
        } else {
            // 0x002bf574
            charge(ctx, 4);
            jal(ctx, 0x2BF574u, gen::fn_sub_1FEDE0_001fede0);
        }
        // 0x002bf58c
        charge(ctx, 5);
        v0 = 0x80000;
        v0 = v0 | 0x274;
        v0 = s1 & v0;
        if (v0 == 0) {
            // 0x002bf5b0
            charge(ctx, 2);
            jal(ctx, 0x2BF5B0u, gen::fn_sub_1FED40_001fed40);
        } else {
            // 0x002bf5a0
            charge(ctx, 4);
            jal(ctx, 0x2BF5A0u, gen::fn_sub_1FED20_001fed20);
        }
        // 0x002bf5b8
        charge(ctx, 2);
        if (s0 == 0) {
            // 0x002bf5d0
            charge(ctx, 2);
            jal(ctx, 0x2BF5D0u, gen::fn_sub_1FED80_001fed80);
        } else {
            // 0x002bf5c0
            charge(ctx, 4);
            jal(ctx, 0x2BF5C0u, gen::fn_sub_1FED60_001fed60);
        }
        // 0x002bf5d8
        charge(ctx, 4);
        lhu(v0, s3, act::kFlags);
        v0 = v0 & 0x400;
        if (v0 != 0) {
            // 0x002bf5f8
            charge(ctx, 2);
            jal(ctx, 0x2BF5F8u, gen::fn_sub_1FEDC0_001fedc0);
        } else {
            // 0x002bf5e8
            charge(ctx, 4);
            jal(ctx, 0x2BF5E8u, gen::fn_sub_1FEDA0_001feda0);
        }
        // 0x002bf600
        charge(ctx, 9);
        jal(ctx, 0x2BF600u, gen::fn_sub_1FEE80_001fee80);
        jal(ctx, 0x2BF608u, gen::fn_sub_1FEE40_001fee40);
        jal(ctx, 0x2BF610u, gen::fn_sub_2FD820_002fd820);
        jal(ctx, 0x2BF618u, gen::fn_sub_1FDD60_001fdd60);
        lw(v0, s2, 16);
    } else {
        // 0x002bf44c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x002bf624 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x002C0070 sub_2C0070 -- 2060 bytes; frame 0x160: ra sp+0x70, s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// The target cursor's camera / pad handling (gPadFlags) over the AI target record.
// Arguments: a0, a1.
void sub_2C0070(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f20{ctx, 20};
    // 0x002c0070
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x160);
    sd(ra, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s4 = a1;
    lhu(a2, a1, 56);
    at = slti(a2, 2);
    if (at == 0) {
        // 0x002c00a8
        charge(ctx, 5);
        v1 = 0x7E0000;
        lhu(a3, v1, 2386);  // 0x7E0952
        v1 = a3 & 0x2000;
        if (v1 == 0) {
            // 0x002c00bc
            charge(ctx, 5);
            v1 = 0x7E0000;
            lhu(a1, v1, 2394);  // 0x7E095A
            v1 = a1 & 0x2000;
            if (v1 != 0) {
                goto L_002c00d0;
            }
            // 0x002c0104
            charge(ctx, 3);
            v1 = a3 & 0x8000;
            if (v1 == 0) {
                // 0x002c0110
                charge(ctx, 3);
                v1 = a1 & 0x8000;
                if (v1 != 0) {
                    goto L_002c011c;
                }
                // 0x002c0150
                charge(ctx, 3);
                v1 = a3 & 0x1000;
                if (v1 == 0) {
                    // 0x002c015c
                    charge(ctx, 3);
                    v1 = a1 & 0x1000;
                    if (v1 != 0) {
                        goto L_002c0168;
                    }
                    // 0x002c019c
                    charge(ctx, 3);
                    v1 = a3 & 0x4000;
                    if (v1 == 0) {
                        // 0x002c01a8
                        charge(ctx, 3);
                        v1 = a1 & 0x4000;
                        if (v1 != 0) {
                            goto L_002c01b4;
                        }
                        // 0x002c01e8
                        charge(ctx, 2);
                        // 0x002c0850 (the shared epilogue, written out on this path)
                        charge(ctx, 11);
                        ld(ra, sp, 0x70);
                        lq(s5, sp, 0x60);
                        lq(s4, sp, 0x50);
                        lq(s3, sp, 0x40);
                        lq(s2, sp, 0x30);
                        lq(s1, sp, 0x20);
                        lq(s0, sp, 0x10);
                        lwc1(f20, sp, 0x0);
                        sp = addiu(sp, 0x160);
                        return;
                    }
                L_002c01b4:
                    charge(ctx, 7);
                    v1 = 3;
                    a1 = 0x7E0000;
                    lhu(a1, a1, 2382);  // gPadFlags
                    a1 = a1 & 0x4000;
                    s2 = sltu(0, a1);
                    if (s2 == 0) {
                        // 0x002c01d0
                        charge(ctx, 4);
                        a1 = 0x7E0000;
                        lhu(a1, a1, 2392);  // 0x7E0958
                        a1 = a1 & 0x4000;
                        s2 = sltu(0, a1);
                    }
                    // 0x002c01e0
                    charge(ctx, 2);
                L_002c01f0:
                    charge(ctx, 4);
                    s0 = v1 & 0xFFFF;
                    v1 = 3;
                    if (s0 != v1) {
                        // 0x002c0200
                        charge(ctx, 3);
                        v1 = 2;
                        if (s0 == v1) {
                            goto L_002c05a8;
                        }
                        // 0x002c020c
                        charge(ctx, 2);
                        if (s0 != 0) {
                            // 0x002c0214
                            charge(ctx, 3);
                            v1 = 1;
                            if (s0 == v1) {
                                goto L_002c0228;
                            }
                            // 0x002c0220
                            charge(ctx, 2);
                            goto L_002c0830;
                        }
                    L_002c0228:
                        charge(ctx, 38);
                        lw(a0, a0, 48);
                        a1 = addiu(sp, 0x130);
                        jal(ctx, 0x2C0230u, gen::fn_sub_27FFB0_0027ffb0);
                        a0 = s4;
                        jal(ctx, 0x2C023Cu, gen::fn_sub_2C09F0_002c09f0);
                        a0 = v0 & 0xFFFF;
                        a1 = 0;
                        a2 = addiu(sp, 0x120);
                        a3 = 0;
                        t0 = 0;
                        t1 = 1;
                        jal(ctx, 0x2C025Cu, gen::fn_sub_280870_00280870);
                        lwc1(f3, sp, 0x130);
                        swc1(f3, sp, 0x110);
                        lwc1(f2, sp, 0x138);
                        swc1(f2, sp, 0x114);
                        lwc1(f1, sp, 0x120);
                        swc1(f1, sp, 0x118);
                        lwc1(f0, sp, 0x128);
                        swc1(f0, sp, 0x11C);
                        sub_s(f1, f3, f1);
                        swc1(f1, sp, 0x148);
                        sub_s(f0, f2, f0);
                        swc1(f0, sp, 0x14C);
                        swc1(f0, sp, 0x140);
                        neg_s(f0, f1);
                        swc1(f0, sp, 0x144);
                        a0 = addiu(sp, 0x140);
                        a1 = a0;
                        jal(ctx, 0x2C02A8u, gen::fn_sub_4C6B20_004c6b20);
                        s3 = 0;
                        s5 = 0;
                        for (;;) {
                            // 0x002c03d8
                            charge(ctx, 5);
                            v1 = s5 & 0xFFFF;
                            lhu(v0, s4, 56);
                            v0 = slt(v1, v0);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x002c02c0
                            charge(ctx, 41);
                            v0 = s5 & 0xFFFF;
                            v0 = sll(v0, 2);
                            v0 = addu(s4, v0);
                            lw(s1, v0, 0);
                            lw(a0, s1, 48);
                            a1 = addiu(sp, 0x130);
                            jal(ctx, 0x2C02D8u, gen::fn_sub_27FFB0_0027ffb0);
                            lwc1(f0, sp, 0x130);
                            swc1(f0, sp, 0x158);
                            lwc1(f0, sp, 0x138);
                            swc1(f0, sp, 0x15C);
                            a0 = addiu(sp, 0x110);
                            a1 = addiu(sp, 0x118);
                            a2 = addiu(sp, 0x158);
                            a3 = addiu(sp, 0x150);
                            jal(ctx, 0x2C0300u, gen::fn_sub_2D1FD0_002d1fd0);
                            mov_s(f20, f0);
                            lwc1(f1, sp, 0x158);
                            lwc1(f0, sp, 0x150);
                            sub_s(f0, f1, f0);
                            swc1(f0, sp, 0x148);
                            lwc1(f1, sp, 0x15C);
                            lwc1(f0, sp, 0x154);
                            sub_s(f0, f1, f0);
                            swc1(f0, sp, 0x14C);
                            a0 = addiu(sp, 0x148);
                            a1 = a0;
                            jal(ctx, 0x2C0334u, gen::fn_sub_4C6B20_004c6b20);
                            lwc1(f3, sp, 0x148);
                            lwc1(f2, sp, 0x140);
                            lwc1(f1, sp, 0x14C);
                            lwc1(f0, sp, 0x144);
                            mula_s(f1, f0);
                            mtc1(zero, f0);
                            madd_s(f1, f3, f2);
                            c_lt_s(f0, f1);
                            if (cond(ctx)) {
                                // 0x002c0388
                                charge(ctx, 8);
                                v1 = s3 & 0xFFFF;
                                v0 = sll(v1, 1);
                                v0 = addu(v0, v1);
                                v0 = sll(v0, 2);
                                v0 = addu(v0, sp);
                                v0 = addiu(v0, 128);
                                neg_s(f0, f20);
                                swc1(f0, v0, 8);
                            } else {
                                // 0x002c0364
                                charge(ctx, 9);
                                v1 = s3 & 0xFFFF;
                                v0 = sll(v1, 1);
                                v0 = addu(v0, v1);
                                v0 = sll(v0, 2);
                                v0 = addu(v0, sp);
                                v0 = addiu(v0, 128);
                                swc1(f20, v0, 8);
                            }
                            // 0x002c03a8
                            charge(ctx, 12);
                            v1 = s3 & 0xFFFF;
                            v0 = sll(v1, 1);
                            v0 = addu(v0, v1);
                            v0 = sll(v0, 2);
                            v0 = addu(v0, sp);
                            v0 = addiu(v0, 128);
                            sw(s1, v0, 0);
                            sh(s5, v0, 4);
                            v0 = addiu(s3, 1);
                            s3 = v0 & 0xFFFF;
                            v0 = addiu(s5, 1);
                            s5 = v0 & 0xFFFF;
                        }
                        // 0x002c03ec
                        charge(ctx, 3);
                        s1 = s3 & 0xFFFF;
                        v1 = addiu(s1, -1);
                        a2 = 1;
                        for (;;) {
                            // 0x002c03f8
                            charge(ctx, 4);
                            t2 = 0;
                            v0 = 0;
                            for (;;) {
                                // 0x002c0484
                                charge(ctx, 4);
                                a1 = v0 & 0xFFFF;
                                a0 = slt(a1, v1);
                                if (a0 == 0) {
                                    break;
                                }
                                backedge(ctx);
                                // 0x002c0408
                                charge(ctx, 17);
                                a0 = sll(a1, 1);
                                a0 = addu(a0, a1);
                                a0 = sll(a0, 2);
                                a0 = addu(a0, sp);
                                a3 = addiu(a0, 128);
                                a1 = v0 & 0xFFFF;
                                a0 = sll(a1, 1);
                                a0 = addu(a0, a1);
                                a0 = sll(a0, 2);
                                a0 = addu(a0, sp);
                                t1 = addiu(a0, 128);
                                t0 = addiu(t1, 8);
                                lwc1(f1, t1, 8);
                                lwc1(f0, a3, 20);
                                c_lt_s(f1, f0);
                                if (cond(ctx)) {
                                    // 0x002c044c
                                    charge(ctx, 12);
                                    lw(a3, t1, 0);
                                    lhu(a1, t1, 4);
                                    lw(a0, t1, 12);
                                    sw(a0, t1, 0);
                                    lhu(a0, t1, 16);
                                    sh(a0, t1, 4);
                                    lwc1(f0, t1, 20);
                                    swc1(f0, t0, 0);
                                    sw(a3, t1, 12);
                                    sh(a1, t1, 16);
                                    swc1(f1, t1, 20);
                                    t2 = a2;
                                }
                                // 0x002c047c
                                charge(ctx, 2);
                                v0 = addiu(v0, 1);
                                v0 = v0 & 0xFFFF;
                            }
                            // 0x002c0494
                            charge(ctx, 2);
                            if (t2 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x002c049c
                        charge(ctx, 6);
                        a0 = s4;
                        jal(ctx, 0x2C04A0u, gen::fn_sub_2C0880_002c0880);
                        a2 = 0;
                        for (;;) {
                            // 0x002c04dc
                            charge(ctx, 4);
                            a0 = a2 & 0xFFFF;
                            v1 = slt(a0, s1);
                            if (v1 != 0) {
                                backedge(ctx);
                                // 0x002c04b4
                                charge(ctx, 8);
                                a1 = a2 & 0xFFFF;
                                v1 = sll(a1, 1);
                                v1 = addu(v1, a1);
                                v1 = sll(v1, 2);
                                v1 = addu(v1, sp);
                                lw(v1, v1, 128);
                                if (v1 != v0) {
                                    // 0x002c04d4
                                    charge(ctx, 2);
                                    v1 = addiu(a2, 1);
                                    a2 = v1 & 0xFFFF;
                                    continue;
                                }
                            }
                            break;
                        }
                        // 0x002c04ec
                        charge(ctx, 3);
                        v1 = 1;
                        if (s0 != v1) {
                            // 0x002c0548
                            charge(ctx, 2);
                            if (a0 != 0) {
                                // 0x002c0584
                                charge(ctx, 9);
                                v1 = addiu(a0, -1);
                                a0 = v1 & 0xFFFF;
                                v1 = sll(a0, 1);
                                v1 = addu(v1, a0);
                                v1 = sll(v1, 2);
                                v1 = addu(v1, sp);
                                lhu(s3, v1, 132);
                            } else {
                                // 0x002c0550
                                charge(ctx, 2);
                                if (s2 == 0) {
                                    // 0x002c0574
                                    charge(ctx, 1);
                                    lhu(v1, s4, 58);
                                } else {
                                    // 0x002c0558
                                    charge(ctx, 7);
                                    v1 = sll(s1, 1);
                                    v1 = addu(v1, s1);
                                    v1 = sll(v1, 2);
                                    v1 = addu(v1, sp);
                                    lhu(v1, v1, 120);
                                }
                                // 0x002c0578
                                charge(ctx, 3);
                                s3 = v1 & 0xFFFF;
                            }
                        } else {
                            // 0x002c04f8
                            charge(ctx, 3);
                            v1 = addiu(a0, 1);
                            if (v1 != s1) {
                                // 0x002c0528
                                charge(ctx, 8);
                                a0 = v1 & 0xFFFF;
                                v1 = sll(a0, 1);
                                v1 = addu(v1, a0);
                                v1 = sll(v1, 2);
                                v1 = addu(v1, sp);
                                lhu(s3, v1, 132);
                            } else {
                                // 0x002c0504
                                charge(ctx, 2);
                                if (s2 == 0) {
                                    // 0x002c0518
                                    charge(ctx, 1);
                                    lhu(v1, s4, 58);
                                } else {
                                    // 0x002c050c
                                    charge(ctx, 3);
                                    lhu(v1, sp, 0x84);
                                }
                                // 0x002c051c
                                charge(ctx, 3);
                                s3 = v1 & 0xFFFF;
                            }
                        }
                    L_002c0830:
                        charge(ctx, 4);
                        lhu(a0, s4, 58);
                        v1 = s3 & 0xFFFF;
                        if (a0 != v1) {
                            // 0x002c0840
                            charge(ctx, 4);
                            sh(s3, s4, 58);
                            lbu(v1, s4, 60);
                            v1 = v1 | 0x1;
                            sb(v1, s4, 60);
                        }
                        // 0x002c0850 (the shared epilogue, written out on this path)
                        charge(ctx, 11);
                        ld(ra, sp, 0x70);
                        lq(s5, sp, 0x60);
                        lq(s4, sp, 0x50);
                        lq(s3, sp, 0x40);
                        lq(s2, sp, 0x30);
                        lq(s1, sp, 0x20);
                        lq(s0, sp, 0x10);
                        lwc1(f20, sp, 0x0);
                        sp = addiu(sp, 0x160);
                        return;
                    }
                L_002c05a8:
                    charge(ctx, 5);
                    a1 = 0;
                    a0 = 0;
                    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                    for (;;) {
                        // 0x002c0650
                        charge(ctx, 4);
                        a3 = a0 & 0xFFFF;
                        a3 = slt(a3, a2);
                        if (a3 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x002c05bc
                        charge(ctx, 8);
                        a3 = a0 & 0xFFFF;
                        a3 = sll(a3, 2);
                        a3 = addu(s4, a3);
                        lw(t1, a3, 0);
                        lhu(a3, t1, 26);
                        a3 = a3 & 0x1;
                        if (a3 != 0) {
                            // 0x002c05dc
                            charge(ctx, 4);
                            lw(t0, t1, 48);
                            lbu(a3, t0, 162);
                            if (a3 == 0) {
                                // 0x002c05ec
                                charge(ctx, 4);
                                t2 = 0;
                                lw(t3, v1, gbtl::kUnitHead0);
                                for (;;) {
                                    // 0x002c0610
                                    charge(ctx, 3);
                                    if (t3 != 0) {
                                        backedge(ctx);
                                        // 0x002c05fc
                                        charge(ctx, 2);
                                        if (t3 != t0) {
                                            // 0x002c0604
                                            charge(ctx, 3);
                                            a3 = addiu(t2, 1);
                                            t2 = a3 & 0xFFFF;
                                            lw(t3, t3, unit::kNext);
                                            continue;
                                        }
                                    }
                                    break;
                                }
                                // 0x002c061c
                                charge(ctx, 11);
                                t0 = a1 & 0xFFFF;
                                a3 = sll(t0, 1);
                                a3 = addu(a3, t0);
                                a3 = sll(a3, 2);
                                a3 = addu(a3, sp);
                                a3 = addiu(a3, 128);
                                sw(t1, a3, 0);
                                sh(a0, a3, 4);
                                sh(t2, a3, 6);
                                a1 = addiu(a1, 1);
                                a1 = a1 & 0xFFFF;
                            }
                        }
                        // 0x002c0648
                        charge(ctx, 2);
                        a0 = addiu(a0, 1);
                        a0 = a0 & 0xFFFF;
                    }
                    // 0x002c0660
                    charge(ctx, 3);
                    s1 = a1 & 0xFFFF;
                    if (s1 != 0) {
                        // 0x002c066c
                        charge(ctx, 3);
                        v0 = slti(s1, 2);
                        if (v0 == 0) {
                            // 0x002c0678
                            charge(ctx, 2);
                            a0 = addiu(s1, -1);
                            a3 = 1;
                            for (;;) {
                                // 0x002c0680
                                charge(ctx, 4);
                                v0 = 0;
                                v1 = 0;
                                for (;;) {
                                    // 0x002c070c
                                    charge(ctx, 4);
                                    a2 = v1 & 0xFFFF;
                                    a1 = slt(a2, a0);
                                    if (a1 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                    // 0x002c0690
                                    charge(ctx, 17);
                                    a1 = sll(a2, 1);
                                    a1 = addu(a1, a2);
                                    a1 = sll(a1, 2);
                                    a1 = addu(a1, sp);
                                    t2 = addiu(a1, 128);
                                    a2 = v1 & 0xFFFF;
                                    a1 = sll(a2, 1);
                                    a1 = addu(a1, a2);
                                    a1 = sll(a1, 2);
                                    a1 = addu(a1, sp);
                                    t1 = addiu(a1, 128);
                                    t0 = addiu(t1, 6);
                                    lhu(a2, t1, 6);
                                    lhu(a1, t2, 18);
                                    at = slt(a2, a1);
                                    if (at != 0) {
                                        // 0x002c06d4
                                        charge(ctx, 12);
                                        lw(a1, t1, 0);
                                        lhu(s3, t1, 4);
                                        lw(v0, t1, 12);
                                        sw(v0, t1, 0);
                                        lhu(v0, t1, 16);
                                        sh(v0, t1, 4);
                                        lhu(v0, t1, 18);
                                        sh(v0, t0, 0);
                                        sw(a1, t1, 12);
                                        sh(s3, t1, 16);
                                        sh(a2, t1, 18);
                                        v0 = a3;
                                    }
                                    // 0x002c0704
                                    charge(ctx, 2);
                                    v1 = addiu(v1, 1);
                                    v1 = v1 & 0xFFFF;
                                }
                                // 0x002c071c
                                charge(ctx, 2);
                                if (v0 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                        }
                        // 0x002c0724
                        charge(ctx, 6);
                        a0 = s4;
                        jal(ctx, 0x2C0728u, gen::fn_sub_2C0880_002c0880);
                        a2 = 0;
                        for (;;) {
                            // 0x002c0764
                            charge(ctx, 4);
                            a0 = a2 & 0xFFFF;
                            v1 = slt(a0, s1);
                            if (v1 != 0) {
                                backedge(ctx);
                                // 0x002c073c
                                charge(ctx, 8);
                                a1 = a2 & 0xFFFF;
                                v1 = sll(a1, 1);
                                v1 = addu(v1, a1);
                                v1 = sll(v1, 2);
                                v1 = addu(v1, sp);
                                lw(v1, v1, 128);
                                if (v1 != v0) {
                                    // 0x002c075c
                                    charge(ctx, 2);
                                    v1 = addiu(a2, 1);
                                    a2 = v1 & 0xFFFF;
                                    continue;
                                }
                            }
                            break;
                        }
                        // 0x002c0774
                        charge(ctx, 2);
                        if (a0 != s1) {
                            // 0x002c077c
                            charge(ctx, 3);
                            v1 = 2;
                            if (s0 != v1) {
                                // 0x002c07d8
                                charge(ctx, 2);
                                if (a0 != 0) {
                                    // 0x002c0814
                                    charge(ctx, 7);
                                    v1 = addiu(a0, -1);
                                    a0 = v1 & 0xFFFF;
                                    v1 = sll(a0, 1);
                                    v1 = addu(v1, a0);
                                    v1 = sll(v1, 2);
                                    v1 = addu(v1, sp);
                                    lhu(s3, v1, 132);
                                } else {
                                    // 0x002c07e0
                                    charge(ctx, 2);
                                    if (s2 == 0) {
                                        // 0x002c0804
                                        charge(ctx, 1);
                                        lhu(v1, s4, 58);
                                    } else {
                                        // 0x002c07e8
                                        charge(ctx, 7);
                                        v1 = sll(s1, 1);
                                        v1 = addu(v1, s1);
                                        v1 = sll(v1, 2);
                                        v1 = addu(v1, sp);
                                        lhu(v1, v1, 120);
                                    }
                                    // 0x002c0808
                                    charge(ctx, 3);
                                    s3 = v1 & 0xFFFF;
                                }
                            } else {
                                // 0x002c0788
                                charge(ctx, 3);
                                v1 = addiu(a0, 1);
                                if (v1 != s1) {
                                    // 0x002c07b8
                                    charge(ctx, 8);
                                    a0 = v1 & 0xFFFF;
                                    v1 = sll(a0, 1);
                                    v1 = addu(v1, a0);
                                    v1 = sll(v1, 2);
                                    v1 = addu(v1, sp);
                                    lhu(s3, v1, 132);
                                } else {
                                    // 0x002c0794
                                    charge(ctx, 2);
                                    if (s2 == 0) {
                                        // 0x002c07a8
                                        charge(ctx, 1);
                                        lhu(v1, s4, 58);
                                    } else {
                                        // 0x002c079c
                                        charge(ctx, 3);
                                        lhu(v1, sp, 0x84);
                                    }
                                    // 0x002c07ac
                                    charge(ctx, 3);
                                    s3 = v1 & 0xFFFF;
                                }
                            }
                        }
                        goto L_002c0830;
                    }
                    // 0x002c0850 (the shared epilogue, written out on this path)
                    charge(ctx, 11);
                    ld(ra, sp, 0x70);
                    lq(s5, sp, 0x60);
                    lq(s4, sp, 0x50);
                    lq(s3, sp, 0x40);
                    lq(s2, sp, 0x30);
                    lq(s1, sp, 0x20);
                    lq(s0, sp, 0x10);
                    lwc1(f20, sp, 0x0);
                    sp = addiu(sp, 0x160);
                    return;
                }
            L_002c0168:
                charge(ctx, 7);
                v1 = 2;
                a1 = 0x7E0000;
                lhu(a1, a1, 2382);  // gPadFlags
                a1 = a1 & 0x1000;
                s2 = sltu(0, a1);
                if (s2 == 0) {
                    // 0x002c0184
                    charge(ctx, 4);
                    a1 = 0x7E0000;
                    lhu(a1, a1, 2392);  // 0x7E0958
                    a1 = a1 & 0x1000;
                    s2 = sltu(0, a1);
                }
                // 0x002c0194
                charge(ctx, 2);
                goto L_002c01f0;
            }
        L_002c011c:
            charge(ctx, 7);
            v1 = 0;
            a1 = 0x7E0000;
            lhu(a1, a1, 2382);  // gPadFlags
            a1 = a1 & 0x8000;
            s2 = sltu(0, a1);
            if (s2 == 0) {
                // 0x002c0138
                charge(ctx, 4);
                a1 = 0x7E0000;
                lhu(a1, a1, 2392);  // 0x7E0958
                a1 = a1 & 0x8000;
                s2 = sltu(0, a1);
            }
            // 0x002c0148
            charge(ctx, 2);
            goto L_002c01f0;
        }
    L_002c00d0:
        charge(ctx, 7);
        v1 = 1;
        a1 = 0x7E0000;
        lhu(a1, a1, 2382);  // gPadFlags
        a1 = a1 & 0x2000;
        s2 = sltu(0, a1);
        if (s2 == 0) {
            // 0x002c00ec
            charge(ctx, 4);
            a1 = 0x7E0000;
            lhu(a1, a1, 2392);  // 0x7E0958
            a1 = a1 & 0x2000;
            s2 = sltu(0, a1);
        }
        // 0x002c00fc
        charge(ctx, 2);
        goto L_002c01f0;
    }
    // 0x002c0850 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x160);
}

// 0x002C1080 sub_2C1080 -- 612 bytes; frame 0xD0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlAIAnyUnit] AI condition over the battle's combatants: whether any active, placed action of the side mask a2
// passes the filters a4 (bit 0 downed, bit 1 not shielded against the skill element by the effect states 17 / 18,
// bits 2-3 a weakness the AI may know: sub_2E3350 / sub_17B260) and the status mask a3, and satisfies the predicate
// a5 (called through $t2 with the action and a1).
// Arguments: a0 btlAction, a1 skill / element, a2 side mask, a3 status mask, t0 filters, t1 predicate.
void sub_2C1080(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x002c1080
    enter(ctx, 28);  // entry check point + this block's cycles
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
    s1 = a1;
    s0 = a3;
    sw(t1, sp, 0xCC);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s5, v0, gbtl::kActionList);
    s4 = a2 & 0xFFFF;
    s3 = t0 & 0xFFFF;
    s6 = s3 & 0x1;
    s7 = s3 & 0x2;
    fp = s3 & 0xC;
    v0 = s3 & 0x4;
    sq(v0, sp, 0xB0);
    v0 = 0x80000;
    v0 = s0 & v0;
    sq(v0, sp, 0xA0);
    for (;;) {
        // 0x002c12a4
        charge(ctx, 2);
        if (s5 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002c10f0
        charge(ctx, 4);
        lhu(v1, s5, act::kFlags2);
        v0 = v1 & 0x1;
        if (v0 != 0) {
            // 0x002c1100
            charge(ctx, 3);
            v0 = v1 & 0x8;
            if (v0 == 0) {
                goto L_002c12a0;
            }
            // 0x002c110c
            charge(ctx, 7);
            lw(s2, s5, act::kUnit);
            lbu(v1, s2, unit::kSide);
            v0 = 1;
            v0 = sllv(v0, v1);
            v0 = s4 & v0;
            if (v0 == 0) {
                goto L_002c12a0;
            }
            // 0x002c1128
            charge(ctx, 2);
            if (s3 != 0) {
                // 0x002c1130
                charge(ctx, 2);
                if (s6 != 0) {
                    // 0x002c1138
                    charge(ctx, 6);
                    lw(a0, s2, unit::kDat);
                    a1 = 0x100000;
                    jal(ctx, 0x2C1140u, gen::fn_datCalcChkBadStatus_00300580);
                    if (v0 == 0) {
                        goto L_002c12a0;
                    }
                    goto L_002c1150;
                }
            L_002c1150:
                charge(ctx, 2);
                if (s7 != 0) {
                    // 0x002c1158
                    charge(ctx, 9);
                    a0 = dsll32(s1, 16);
                    a0 = dsra32(a0, 16);
                    jal(ctx, 0x2C1160u, gen::fn_datCalcGetElementBit_003080c0);
                    v1 = 0xE0000;
                    v1 = v1 | 0x1;
                    v1 = v0 & v1;
                    if (v1 != 0) {
                        goto L_002c11dc;
                    }
                    // 0x002c117c
                    charge(ctx, 3);
                    v1 = v0 & 0xE;
                    if (v1 != 0) {
                        // 0x002c1188
                        charge(ctx, 8);
                        lw(a0, s2, unit::kDat);
                        a1 = 17;
                        jal(ctx, 0x2C1190u, gen::fn_datCalcGetEffectState_00301750);
                        v0 = dsll32(v0, 24);
                        v0 = dsra32(v0, 24);
                        if (i64(v0) <= 0) {
                            goto L_002c11dc;
                        }
                        // 0x002c11a8
                        charge(ctx, 2);
                        goto L_002c12a0;
                    }
                    // 0x002c11b0
                    charge(ctx, 3);
                    v0 = v0 & 0x100;
                    if (v0 != 0) {
                        goto L_002c11dc;
                    }
                    // 0x002c11bc
                    charge(ctx, 8);
                    lw(a0, s2, unit::kDat);
                    a1 = 18;
                    jal(ctx, 0x2C11C4u, gen::fn_datCalcGetEffectState_00301750);
                    v0 = dsll32(v0, 24);
                    v0 = dsra32(v0, 24);
                    if (i64(v0) > 0) {
                        goto L_002c12a0;
                    }
                    goto L_002c11dc;
                }
            L_002c11dc:
                charge(ctx, 2);
                if (fp == 0) {
                    goto L_002c123c;
                }
                // 0x002c11e4
                charge(ctx, 4);
                lbu(v1, s2, unit::kSide);
                v0 = 1;
                if (v1 != v0) {
                    goto L_002c123c;
                }
                // 0x002c11f4
                charge(ctx, 7);
                a1 = dsll32(s1, 16);
                a1 = dsra32(a1, 16);
                a0 = s5;
                jal(ctx, 0x2C1200u, gen::fn_sub_2E3350_002e3350);
                if (v0 != 0) {
                    goto L_002c123c;
                }
                // 0x002c1210
                charge(ctx, 5);
                lhu(a0, s2, unit::kId);
                jal(ctx, 0x2C1214u, gen::fn_sub_17B260_0017b260);
                if (v0 != 0) {
                    goto L_002c123c;
                }
                // 0x002c1224
                charge(ctx, 3);
                lq(v0, sp, 0xB0);
                if (v0 != 0) {
                    goto L_002c12a0;
                }
                goto L_002c1230_19;
            }
        L_002c123c:
            charge(ctx, 3);
            lq(v0, sp, 0xA0);
            if (v0 != 0) {
                // 0x002c1248
                charge(ctx, 6);
                lw(a0, s2, unit::kDat);
                a1 = 0;
                jal(ctx, 0x2C1250u, gen::fn_datCalcIsDead_0030b5a0);
                if (v0 != 0) {
                    goto L_002c12a0;
                }
                goto L_002c1260;
            }
        L_002c1260:
            charge(ctx, 6);
            lw(a0, s2, unit::kDat);
            a1 = s0;
            jal(ctx, 0x2C1268u, gen::fn_datCalcChkBadStatus_00300580);
            if (v0 != 0) {
                goto L_002c12a0;
            }
            // 0x002c1278
            charge(ctx, 7);
            a0 = s5;
            a1 = s1;
            lw(v0, sp, 0xCC);
            jalr(ctx, 0x2C1284u, v0.u());
            if (v0 == 0) {
                goto L_002c12a0;
            }
            goto L_002c1294_24;
        }
    L_002c12a0:
        charge(ctx, 1);
        lw(s5, s5, act::kNext);
    }
    // 0x002c12ac
    charge(ctx, 1);
    v0 = 0;
    // 0x002c12b0 (the shared epilogue, written out on this path)
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
L_002c1230_19:
    charge(ctx, 3);
    v0 = 1;
    // 0x002c12b0 (the shared epilogue, written out on this path)
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
L_002c1294_24:
    charge(ctx, 3);
    v0 = 1;
    // 0x002c12b0 (the shared epilogue, written out on this path)
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
}

// 0x002C1710 sub_2C1710 -- 40 bytes; frame 0x10: ra sp+0x0
// AI predicate: the action's unit has the bad status a1 (datCalcChkBadStatus).
// Arguments: a0 btlAction, a1 mask.
void sub_2C1710(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c1710
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, act::kUnit);
    lw(a0, v0, unit::kDat);
    jal(ctx, 0x2C1720u, gen::fn_datCalcChkBadStatus_00300580);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C17B0 sub_2C17B0 -- 160 bytes; frame 0x10: ra sp+0x0
// AI condition: any combatant of the given sides with the given status (sub_2C1080 with the predicate sub_2C1710).
// Arguments: a0 btlAction, a1 parameter.
void sub_2C17B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c17b0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, act::kUnit);
    lbu(v0, v0, unit::kSide);
    if (v0 != 0) {
        // 0x002c17d4
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x002c17c8
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x002c17d8
    charge(ctx, 5);
    v1 = v0 & 0xFFFF;
    a3 = 0x80000;
    v0 = a1 & a3;
    if (v0 == 0) {
        // 0x002c181c
        charge(ctx, 9);
        v1 = v1 & 0xFFFF;
        v0 = 1;
        v0 = sllv(v0, v1);
        a2 = v0 & 0xFFFF;
        t0 = 0;
        t1 = 0x2C0000;
        t1 = addiu(t1, 5904);  // &sub_2C1710
        jal(ctx, 0x2C1838u, gen::fn_sub_2C1080_002c1080);
    } else {
        // 0x002c17ec
        charge(ctx, 12);
        v1 = v1 & 0xFFFF;
        v0 = 1;
        v0 = sllv(v0, v1);
        a2 = v0 & 0xFFFF;
        a3 = 0;
        t0 = 0;
        t1 = 0x2C0000;
        t1 = addiu(t1, 5904);  // &sub_2C1710
        jal(ctx, 0x2C180Cu, gen::fn_sub_2C1080_002c1080);
    }
    // 0x002c1840 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C1F60 sub_2C1F60 -- 96 bytes; frame 0x10: ra sp+0x0
// AI condition: any combatant weak to the element (sub_2C1080 with the predicate sub_2C1E10).
// Arguments: a0 btlAction, a1 element.
void sub_2C1F60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c1f60
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, act::kUnit);
    lbu(v0, v0, unit::kSide);
    if (v0 != 0) {
        // 0x002c1f84
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x002c1f78
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x002c1f88
    charge(ctx, 14);
    v1 = v0 & 0xFFFF;
    v0 = 1;
    v0 = sllv(v0, v1);
    a2 = v0 & 0xFFFF;
    a3 = 0x80000;
    t0 = 0;
    t1 = 0x2C0000;
    t1 = addiu(t1, 7696);  // &sub_2C1E10
    jal(ctx, 0x2C1FA8u, gen::fn_sub_2C1080_002c1080);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C22D0 sub_2C22D0 -- 60 bytes; leaf frame (no stack)
// AI predicate: the action's last command was a skill or attack (+124 kind 1 / 2) with the id a1 (+126).
// Arguments: a0 btlAction, a1 id.
void sub_2C22D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x002c22d0
    enter(ctx, 4);  // entry check point + this block's cycles
    lhu(v1, a0, 124);           // the action's last command kind
    v0 = 2;
    if (v1 != v0) {
        // 0x002c22e0
        charge(ctx, 3);
        v0 = 1;
        if (v1 != v0) {
            // 0x002c22ec: neither a skill (2) nor an attack (1)
            charge(ctx, 3);
            v0 = 0;
            // 0x002c2304 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            return;
        }
    }
    // 0x002c22f8: its id (+126) == a1
    charge(ctx, 3);
    lhu(v0, a0, 126);
    v0 = v0 ^ a1;
    v0 = sltiu(v0, 1);
    // 0x002c2304 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x002C2B20 sub_2C2B20 -- 184 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlAICanUseSkill] Whether a unit can use a skill now: not silenced / blocked (status mask 0x80274), knows it, and
// sub_3086F0 says it is affordable; K_Assert line 1128 for an id >= 624.
// Arguments: a0 btlAction, a1 skill.
void sub_2C2B20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c2b20
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s1 = a1 & 0xFFFF;
    v0 = slti(s1, 624);         // skill ids < 624 (K_Assert line 1128 otherwise)
    if (v0 == 0) {
        // 0x002c2b44
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, 28552);  // "btlAICommand.c"
        a1 = 1128;
        jal(ctx, 0x2C2B50u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002c2b58
    charge(ctx, 8);
    lw(s0, s0, act::kUnit);
    lw(a0, s0, unit::kDat);
    v0 = 0x80000;               // dead, and the ailments 0x274 that block skills
    a1 = v0 | 0x274;
    jal(ctx, 0x2C2B68u, gen::fn_datCalcChkBadStatus_00300580);
    if (v0 == 0) {
        // 0x002c2b84
        charge(ctx, 6);
        lw(a0, s0, unit::kDat);
        a1 = s1;
        jal(ctx, 0x2C2B8Cu, gen::fn_datCalcHasSkill_003005e0);
        if (v0 != 0) {
            // 0x002c2ba8
            charge(ctx, 6);
            lw(a0, s0, unit::kDat);
            a1 = s1;
            jal(ctx, 0x2C2BB0u, gen::fn_sub_3086F0_003086f0);
            // xor v0: a 64-bit move to itself (no effect)
            v0 = sltiu(v0, 1);  // sub_3086F0 == 0: affordable
        } else {
            // 0x002c2b9c
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x002c2b78
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x002c2bc0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002C2BE0 sub_2C2BE0 -- 96 bytes; frame 0x10: ra sp+0x0
// AI condition: any combatant that resists the element (sub_2C1080 with the predicate sub_2C1ED0).
// Arguments: a0 btlAction, a1 element.
void sub_2C2BE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c2be0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, act::kUnit);
    lbu(v0, v0, unit::kSide);
    if (v0 != 0) {
        // 0x002c2c04
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x002c2bf8
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x002c2c08
    charge(ctx, 14);
    v1 = v0 & 0xFFFF;
    v0 = 1;
    v0 = sllv(v0, v1);
    a2 = v0 & 0xFFFF;
    a3 = 0x80000;
    t0 = 6;
    t1 = 0x2C0000;
    t1 = addiu(t1, 7888);  // &sub_2C1ED0
    jal(ctx, 0x2C2C28u, gen::fn_sub_2C1080_002c1080);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C2D00 sub_2C2D00 -- 460 bytes; frame 0x90: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlAIHasSkillOfElement] Whether the unit has a usable skill (sub_2C2B20 rules) of the element a1, the normal
// attack counting as its own element.
// Arguments: a0 btlAction, a1 element.
void sub_2C2D00(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c2e9c: the shared epilogue (v0 = has one)
    auto epilogue = [&] {
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
    };
    // 0x002c2d00
    enter(ctx, 21);  // entry check point + this block's cycles
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
    s5 = a0;                    // s5 = the action
    s4 = a1;                    // s4 = the element
    // The normal attack (skill 0) counts with its own element.
    lw(s1, a0, act::kUnit);
    lw(a0, s1, unit::kDat);
    a1 = 0;
    jal(ctx, 0x2C2D3Cu, gen::fn_datCalcGetSkillElement_003082f0);
    v0 = dsll32(v0, 16);
    v0 = dsra32(v0, 16);
    if (v0 == s4) {
        // 0x002c2d54
        charge(ctx, 3);
        v0 = 1;
        epilogue();
        return;
    }
    // 0x002c2d60: every skill slot (ids 1..463) of that element that the unit can use now (sub_2C2B20's rules, inline)
    charge(ctx, 12);
    lw(a0, s1, unit::kDat);
    jal(ctx, 0x2C2D64u, gen::fn_datCalcGetSkillSlotCount_00308ba0);
    s0 = v0 & 0xFFFF;
    lw(a0, s1, unit::kDat);
    jal(ctx, 0x2C2D74u, gen::fn_datCalcGetSkillList_00308bb0);
    s6 = v0;                    // s6 = the skill list
    s3 = 0;                     // s3 = the slot
    s7 = s0 & 0xFFFF;           // s7 = the slot count
    for (;;) {
        // 0x002c2e88
        charge(ctx, 4);
        v0 = s3 & 0xFFFF;
        v0 = slt(v0, s7);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002c2d90
        charge(ctx, 6);
        v0 = s3 & 0xFFFF;
        v0 = sll(v0, 1);
        s0 = addu(s6, v0);
        lhu(a1, s0, 0);
        if (a1 != 0) {
            // 0x002c2da8
            charge(ctx, 3);
            at = slti(a1, 464);
            if (at != 0) {
                // 0x002c2db4
                charge(ctx, 7);
                lw(a0, s1, unit::kDat);
                jal(ctx, 0x2C2DB8u, gen::fn_datCalcGetSkillElement_003082f0);
                v0 = dsll32(v0, 16);
                v0 = dsra32(v0, 16);
                if (v0 == s4) {
                    // 0x002c2dd0
                    charge(ctx, 4);
                    lhu(s2, s0, 0);
                    v0 = slti(s2, 624);
                    if (v0 == 0) {
                        // 0x002c2de0
                        charge(ctx, 5);
                        a0 = 0x690000;
                        a0 = addiu(a0, 28552);  // "btlAICommand.c"
                        a1 = 1128;
                        jal(ctx, 0x2C2DECu, gen::fn_sub_19D3F0_0019d3f0);
                    }
                    // 0x002c2df4
                    charge(ctx, 8);
                    lw(s0, s5, act::kUnit);
                    lw(a0, s0, unit::kDat);
                    v0 = 0x80000;
                    a1 = v0 | 0x274;
                    jal(ctx, 0x2C2E04u, gen::fn_datCalcChkBadStatus_00300580);
                    if (v0 == 0) {
                        // 0x002c2e20
                        charge(ctx, 6);
                        lw(a0, s0, unit::kDat);
                        a1 = s2;
                        jal(ctx, 0x2C2E28u, gen::fn_datCalcHasSkill_003005e0);
                        if (v0 != 0) {
                            // 0x002c2e44
                            charge(ctx, 6);
                            lw(a0, s0, unit::kDat);
                            a1 = s2;
                            jal(ctx, 0x2C2E4Cu, gen::fn_sub_3086F0_003086f0);
                            if (v0 == 0) {
                                // 0x002c2e68
                                charge(ctx, 1);
                                v0 = 1;
                            } else {
                                // 0x002c2e5c
                                charge(ctx, 3);
                                v0 = 0;
                            }
                        } else {
                            // 0x002c2e38
                            charge(ctx, 3);
                            v0 = 0;
                        }
                    } else {
                        // 0x002c2e14
                        charge(ctx, 3);
                        v0 = 0;
                    }
                    // 0x002c2e6c
                    charge(ctx, 2);
                    if (v0 != 0) {
                        // 0x002c2e74: found one
                        charge(ctx, 3);
                        v0 = 1;
                        epilogue();
                        return;
                    }
                }
            }
        }
        // 0x002c2e80
        charge(ctx, 2);
        v0 = addiu(s3, 1);
        s3 = v0 & 0xFFFF;
    }
    // 0x002c2e98
    charge(ctx, 1);
    v0 = 0;
    epilogue();
}

// 0x002C2ED0 sub_2C2ED0 -- 540 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlAIElementUsable] Whether an element may be used against a unit: enemies whose weakness the party has not
// analysed always pass; else not when shielded (a2 == 1 and effect states 17 / 18), not against a physical-immune
// enemy (DatUnit flag 0x200) or a party unit with skills 544..546, and only when the affinity has no null / repel /
// drain bits (0x7000000).
// Arguments: a0 target btlAction, a1 element, a2 check shields.
void sub_2C2ED0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c30cc: the shared epilogue (v0 = the answer)
    auto epilogue = [&] {
        charge(ctx, 8);
        ld(ra, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
    };
    // 0x002c2ed0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a1;                    // s3 = the element
    s2 = a2;                    // s2 = check the shields
    lw(s1, a0, act::kUnit);     // s1 = the target's btlUnit
    lbu(v1, s1, unit::kSide);
    v0 = 1;
    if (v1 == v0) {
        // An enemy: when the party does not know its affinity to this element (sub_2E3350) and has not seen the enemy
        // before (sub_17B260), the AI may use the element freely.
        // 0x002c2f04
        charge(ctx, 6);
        a1 = dsll32(s3, 16);
        a1 = dsra32(a1, 16);
        jal(ctx, 0x2C2F0Cu, gen::fn_sub_2E3350_002e3350);
        if (v0 == 0) {
            // 0x002c2f1c
            charge(ctx, 5);
            lhu(a0, s1, unit::kId);
            jal(ctx, 0x2C2F20u, gen::fn_sub_17B260_0017b260);
            if (v0 == 0) {
                // 0x002c2f30
                charge(ctx, 3);
                v0 = 1;
                epilogue();
                return;
            }
        }
    }
    // 0x002c2f3c: the element's bits (datCalcGetElementBit)
    charge(ctx, 8);
    a0 = dsll32(s3, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x2C2F44u, gen::fn_datCalcGetElementBit_003080c0);
    s0 = v0;                    // s0 = the element bits
    v0 = 1;
    if (s2 == v0) {
        // The shields: a physical element (0xE) against a unit with effect state 17 > 0, a magic one (not 0x100, the
        // almighty / support bits 0xE0001 excluded) against effect state 18 > 0 -> not usable.
        // 0x002c2f5c
        charge(ctx, 5);
        v0 = 0xE0000;
        v0 = v0 | 0x1;
        v0 = s0 & v0;
        if (v0 == 0) {
            // 0x002c2f70
            charge(ctx, 3);
            v0 = s0 & 0xE;
            if (v0 == 0) {
                // 0x002c2fa8
                charge(ctx, 3);
                v0 = s0 & 0x100;
                if (v0 == 0) {
                    // 0x002c2fb4
                    charge(ctx, 8);
                    lw(a0, s1, unit::kDat);
                    a1 = 18;
                    jal(ctx, 0x2C2FBCu, gen::fn_datCalcGetEffectState_00301750);
                    v0 = dsll32(v0, 24);
                    v0 = dsra32(v0, 24);
                    if (i64(v0) > 0) {
                        // 0x002c2fd4
                        charge(ctx, 3);
                        v0 = 0;
                        epilogue();
                        return;
                    }
                }
            } else {
                // 0x002c2f7c
                charge(ctx, 8);
                lw(a0, s1, unit::kDat);
                a1 = 17;
                jal(ctx, 0x2C2F84u, gen::fn_datCalcGetEffectState_00301750);
                v0 = dsll32(v0, 24);
                v0 = dsra32(v0, 24);
                if (i64(v0) > 0) {
                    // 0x002c2f9c
                    charge(ctx, 3);
                    v0 = 0;
                    epilogue();
                    return;
                }
            }
        }
    }
    // 0x002c2fe0: physical elements against physical immunity
    charge(ctx, 3);
    v0 = s0 & 0xE;
    if (v0 != 0) {
        // 0x002c2fec
        charge(ctx, 4);
        lbu(v1, s1, unit::kSide);
        v0 = 1;
        if (v1 != v0) {
            // A party unit: not usable when it knows one of the skills 544 / 545 / 546 (the physical immunities).
            // 0x002c301c
            charge(ctx, 14);
            lw(a0, s1, unit::kDat);
            jal(ctx, 0x2C3020u, gen::fn_datCalcGetSkillSlotCount_00308ba0);
            s0 = v0 & 0xFFFF;
            lw(a0, s1, unit::kDat);
            jal(ctx, 0x2C3030u, gen::fn_datCalcGetSkillList_00308bb0);
            t0 = 0;                 // t0 = the slot
            a3 = s0 & 0xFFFF;       // a3 = the slot count, v0 = the skill list
            a2 = 546;
            a1 = 545;
            a0 = 544;
            for (;;) {
                // 0x002c3098
                charge(ctx, 4);
                v1 = t0 & 0xFFFF;
                v1 = slt(v1, a3);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x002c3054
                charge(ctx, 6);
                v1 = t0 & 0xFFFF;
                v1 = sll(v1, 1);
                v1 = addu(v0, v1);
                lhu(v1, v1, 0);
                bool immune = v1 == a2;
                if (!immune) {
                    // 0x002c306c
                    charge(ctx, 2);
                    immune = v1 == a1;
                }
                if (!immune) {
                    // 0x002c3074
                    charge(ctx, 2);
                    immune = v1 == a0;
                }
                if (immune) {
                    // 0x002c3084
                    charge(ctx, 3);
                    v0 = 0;
                    epilogue();
                    return;
                }
                // 0x002c307c
                charge(ctx, 2);
                // 0x002c3090
                charge(ctx, 2);
                v1 = addiu(t0, 1);
                t0 = v1 & 0xFFFF;
            }
        } else {
            // An enemy: not usable when its DatUnit flags have 0x200 (physical immunity).
            // 0x002c2ffc
            charge(ctx, 5);
            lw(v0, s1, unit::kDat);
            lhu(v0, v0, b3::dat::kFlags);
            v0 = v0 & 0x200;
            if (v0 != 0) {
                // 0x002c3010
                charge(ctx, 3);
                v0 = 0;
                epilogue();
                return;
            }
        }
    }
    // 0x002c30a8: usable unless the affinity nullifies, repels or drains (0x7000000)
    charge(ctx, 9);
    a1 = dsll32(s3, 16);
    a1 = dsra32(a1, 16);
    lw(a0, s1, unit::kDat);
    jal(ctx, 0x2C30B4u, gen::fn_datCalcGetAffinityChecked_0030b4b0);
    v1 = 0x7000000;
    v0 = v0 & v1;
    v0 = sltu(0, v0);
    v0 = v0 ^ 0x1;
    epilogue();
}

// 0x002C30F0 sub_2C30F0 -- 36 bytes; frame 0x10: ra sp+0x0
// AI predicate: sub_2C2ED0 with the shield check.
// Arguments: a0 btlAction, a1 element.
void sub_2C30F0(EEContext& ctx) {
    using namespace hg;
    Gpr a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c30f0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = 1;
    jal(ctx, 0x2C30FCu, gen::fn_sub_2C2ED0_002c2ed0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C3120 sub_2C3120 -- 36 bytes; frame 0x10: ra sp+0x0
// AI predicate: sub_2C2ED0 without the shield check.
// Arguments: a0 btlAction, a1 element.
void sub_2C3120(EEContext& ctx) {
    using namespace hg;
    Gpr a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c3120
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = 0;
    jal(ctx, 0x2C312Cu, gen::fn_sub_2C2ED0_002c2ed0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C3430 sub_2C3430 -- 824 bytes; frame 0x100: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlAIPickTarget] AI target pick: the candidate list of the action's skill (sub_2BFCB0 / sub_2BFF60 into the record
// +136; all-target skills take the whole list), filtered like sub_2C1080 plus 'has a usable attack' (sub_2C5030), the
// status mask a2 and the predicate a5 (!= a4); flag 4 keeps every match, else one at random; none -> the fallback
// selector sub_2C3770 unless flag 8.
// Arguments: a0 btlAction, a1 element, a2 status mask, a3 flags, t0 value, t1 predicate.
void sub_2C3430(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x002c3430
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x100);
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
    s6 = a1;
    sw(a2, sp, 0xCC);
    s0 = a3;
    sw(t0, sp, 0xC8);
    sw(t1, sp, 0xC4);
    s7 = s0 & 0xFFFF;
    v0 = s7 & 0x20;
    if (v0 != 0) {
        // 0x002c3484
        charge(ctx, 8);
        a1 = addiu(s5, 136);
        a2 = 2;
        a3 = 0;
        t0 = 0;
        jal(ctx, 0x2C3494u, gen::fn_sub_2BFCB0_002bfcb0);
        goto L_002c3510;
    }
    // 0x002c34a4
    charge(ctx, 8);
    a1 = addiu(s5, 136);
    lhu(a2, s5, act::kCmdSkill);
    a3 = 0;
    jal(ctx, 0x2C34B0u, gen::fn_sub_2BFF60_002bff60);
    v0 = v0 & 0xFFFF;
    if (v0 == 0) {
    L_002c3510:
        charge(ctx, 10);
        s2 = 0;
        s3 = 0;
        s1 = s0 & 0xFFFF;
        fp = s1 & 0x1;
        v0 = s1 & 0x2;
        sq(v0, sp, 0xB0);
        v0 = s1 & 0x10;
        sq(v0, sp, 0xA0);
        for (;;) {
            // 0x002c3654
            charge(ctx, 5);
            v1 = s3 & 0xFFFF;
            lhu(v0, s5, act::kTargetRecCount);
            v0 = slt(v1, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002c3538
            charge(ctx, 8);
            v0 = s3 & 0xFFFF;
            v0 = sll(v0, 2);
            v0 = addu(s5, v0);
            lw(s4, v0, 136);
            lhu(v0, s4, 26);
            v0 = v0 & 0x1;
            if (v0 != 0) {
                // 0x002c3558
                charge(ctx, 3);
                lw(s0, s4, 48);
                if (s1 != 0) {
                    // 0x002c3564
                    charge(ctx, 2);
                    if (fp != 0) {
                        // 0x002c356c
                        charge(ctx, 6);
                        lw(a0, s0, 2604);
                        a1 = 0x100000;
                        jal(ctx, 0x2C3574u, gen::fn_datCalcChkBadStatus_00300580);
                        if (v0 != 0) {
                            goto L_002c3584;
                        }
                        goto L_002c364c;
                    }
                L_002c3584:
                    charge(ctx, 3);
                    lq(v0, sp, 0xB0);
                    if (v0 != 0) {
                        // 0x002c3590
                        charge(ctx, 4);
                        lbu(v1, s0, 162);
                        v0 = 1;
                        if (v1 != v0) {
                            goto L_002c35d0;
                        }
                        // 0x002c35a0
                        charge(ctx, 7);
                        a1 = dsll32(s6, 16);
                        a1 = dsra32(a1, 16);
                        a0 = s4;
                        jal(ctx, 0x2C35ACu, gen::fn_sub_2E3350_002e3350);
                        if (v0 != 0) {
                            goto L_002c35d0;
                        }
                        // 0x002c35bc
                        charge(ctx, 5);
                        lhu(a0, s0, 164);
                        jal(ctx, 0x2C35C0u, gen::fn_sub_17B260_0017b260);
                        if (v0 != 0) {
                            goto L_002c35d0;
                        }
                        goto L_002c364c;
                    }
                L_002c35d0:
                    charge(ctx, 3);
                    lq(v0, sp, 0xA0);
                    if (v0 == 0) {
                        goto L_002c35fc;
                    }
                    // 0x002c35dc
                    charge(ctx, 8);
                    a0 = s5;
                    a1 = s4;
                    a2 = 0;
                    a3 = 0;
                    jal(ctx, 0x2C35ECu, gen::fn_sub_2C5030_002c5030);
                    if (i64(v0) >= 0) {
                        goto L_002c35fc;
                    }
                    goto L_002c364c;
                }
            L_002c35fc:
                charge(ctx, 6);
                lw(a0, s0, 2604);
                lw(a1, sp, 0xCC);
                jal(ctx, 0x2C3604u, gen::fn_datCalcChkBadStatus_00300580);
                if (v0 == 0) {
                    // 0x002c3614
                    charge(ctx, 8);
                    a0 = s4;
                    a1 = s6;
                    lw(v0, sp, 0xC4);
                    jalr(ctx, 0x2C3620u, v0.u());
                    lw(v1, sp, 0xC8);
                    if (v1 != v0) {
                        // 0x002c3634
                        charge(ctx, 6);
                        v0 = s2 & 0xFFFF;
                        v0 = sll(v0, 2);
                        v0 = addu(v0, sp);
                        sw(s4, v0, 208);
                        v0 = addiu(s2, 1);
                        s2 = v0 & 0xFFFF;
                    }
                }
            }
        L_002c364c:
            charge(ctx, 2);
            v0 = addiu(s3, 1);
            s3 = v0 & 0xFFFF;
        }
        // 0x002c3668
        charge(ctx, 3);
        a0 = s2 & 0xFFFF;
        if (a0 != 0) {
            // 0x002c36a4
            charge(ctx, 3);
            v0 = s7 & 0x4;
            if (v0 != 0) {
                // 0x002c36f0
                charge(ctx, 3);
                a2 = 0;
                for (;;) {
                    // 0x002c371c
                    charge(ctx, 4);
                    v0 = a2 & 0xFFFF;
                    v0 = slt(v0, a0);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x002c36fc
                    charge(ctx, 8);
                    v0 = a2 & 0xFFFF;
                    a1 = sll(v0, 2);
                    v0 = addu(a1, sp);
                    lw(v1, v0, 208);
                    v0 = addu(s5, a1);
                    sw(v1, v0, 56);
                    v0 = addiu(a2, 1);
                    a2 = v0 & 0xFFFF;
                }
                // 0x002c372c
                charge(ctx, 1);
                sh(s2, s5, act::kTargetCount);
            } else {
                // 0x002c36b0
                charge(ctx, 4);
                v0 = 0;
                at = slti(a0, 2);
                if (at == 0) {
                    // 0x002c36c0
                    charge(ctx, 3);
                    jal(ctx, 0x2C36C0u, gen::fn_datCalcRand_002ffbc0);
                    v0 = v0 & 0xFFFF;
                }
                // 0x002c36cc
                charge(ctx, 9);
                v0 = v0 & 0xFFFF;
                v0 = sll(v0, 2);
                v0 = addu(v0, sp);
                lw(v0, v0, 208);
                sw(v0, s5, act::kTargets);
                v0 = 1;
                sh(v0, s5, act::kTargetCount);
            }
            // 0x002c3730
            charge(ctx, 1);
            v0 = 1;
        } else {
            // 0x002c3674
            charge(ctx, 3);
            v0 = s7 & 0x8;
            if (v0 == 0) {
                // 0x002c368c
                charge(ctx, 4);
                a0 = s5;
                a1 = s6;
                jal(ctx, 0x2C3694u, gen::fn_sub_2C3770_002c3770);
            } else {
                // 0x002c3680
                charge(ctx, 3);
                v0 = 0;
            }
            // 0x002c369c
            charge(ctx, 2);
        }
    } else {
        // 0x002c34c4
        charge(ctx, 3);
        a0 = 0;
        for (;;) {
            // 0x002c34ec
            charge(ctx, 5);
            lhu(v1, s5, act::kTargetRecCount);
            v0 = a0 & 0xFFFF;
            v0 = slt(v0, v1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002c34d0
            charge(ctx, 7);
            v0 = a0 & 0xFFFF;
            v0 = sll(v0, 2);
            v1 = addu(s5, v0);
            lw(v0, v1, 136);
            sw(v0, v1, 56);
            v0 = addiu(a0, 1);
            a0 = v0 & 0xFFFF;
        }
        // 0x002c3500
        charge(ctx, 4);
        sh(v1, s5, act::kTargetCount);
        v0 = 1;
    }
    // 0x002c3734 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0x100);
}

// 0x002C4C80 sub_2C4C80 -- 460 bytes; frame 0xC0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlAIPickHealSkill] Healing skill closest to filling a unit's HP: over the skill list a2 (a3 entries, filtered by
// target kind a4 on SkillRecord +8), the one whose datCalcDamage brings HP + heal nearest to max HP (abs); -1 for
// none.
// Arguments: a0 btlAction, a1 target, a2 skill list, a3 count, t0 kind.
void sub_2C4C80(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x002c4c80
    enter(ctx, 36);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
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
    s4 = a0;
    s3 = a1;
    fp = a2;
    s6 = a3;
    s5 = t0;
    lw(v0, a1, act::kUnit);
    lw(a0, v0, unit::kDat);
    jal(ctx, 0x2C4CC8u, gen::fn_datCalcGetHp_002ffd70);
    v0 = v0 & 0xFFFF;
    sq(v0, sp, 0xB0);
    lw(v0, s3, act::kUnit);
    lw(a0, v0, unit::kDat);
    jal(ctx, 0x2C4CE0u, gen::fn_datCalcGetMaxHp_002ffdf0);
    v0 = v0 & 0xFFFF;
    sq(v0, sp, 0xA0);
    s1 = si(-1);
    v0 = 0xFF0000;
    s2 = v0 | 0xFFFF;  // &0xFFFFFF
    s0 = 0;
    s5 = s5 & 0xFFFF;
    s7 = s6 & 0xFFFF;
    for (;;) {
        // 0x002c4de4
        charge(ctx, 4);
        v0 = s0 & 0xFFFF;
        v0 = slt(v0, s7);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002c4d10
        charge(ctx, 6);
        v0 = s0 & 0xFFFF;
        v0 = sll(v0, 1);
        s6 = addu(fp, v0);
        lhu(a0, s6, 0);
        if (a0 != 0) {
            // 0x002c4d28
            charge(ctx, 3);
            at = slti(a0, 464);
            if (at != 0) {
                // 0x002c4d34
                charge(ctx, 10);
                v0 = sll(a0, 2);
                v0 = addu(v0, a0);
                v0 = sll(v0, 1);
                v0 = addu(v0, a0);
                v1 = sll(v0, 2);
                lw(v0, gp, kGpSkillTbl);  // gBtlSkillTbl
                v0 = addu(v0, v1);
                lbu(a1, v0, 8);
                // The kind filter (SkillRecord +8): t0 == 0 keeps only all-target skills (1), t0 == 1 only single-target
                // ones (0), other values every skill.
                bool fits = true;
                if (s5 == 0) {
                    // 0x002c4d5c
                    charge(ctx, 4);
                    v1 = a1 & 0xFF;
                    v0 = 1;
                    fits = v1 == v0;
                }
                if (fits) {
                    // 0x002c4d6c
                    charge(ctx, 3);
                    v0 = 1;
                    if (s5 == v0) {
                        // 0x002c4d78
                        charge(ctx, 3);
                        v0 = a1 & 0xFF;
                        fits = v0 == 0;
                    }
                }
                if (fits) {
                    // The heal on the target (datCalcDamage(skill, user, target, 1, 1, 1, item?, 1)): keep the skill whose
                    // HP + heal is nearest to max HP (abs; HP and max HP spilled at sp + 0xB0 / 0xA0).
                    // 0x002c4d84
                    charge(ctx, 20);
                    lw(v1, s4, act::kUnit);
                    lw(v0, s3, act::kUnit);
                    lw(a1, v1, unit::kDat);
                    lw(a2, v0, unit::kDat);
                    a3 = 1;
                    t0 = a3;
                    t1 = a3;
                    t2 = 0;
                    t3 = a3;
                    jal(ctx, 0x2C4DA8u, gen::fn_datCalcDamage_00303130);
                    lq(v1, sp, 0xB0);
                    v1 = addu(v1, v0);
                    lq(v0, sp, 0xA0);
                    a0 = subu(v0, v1);
                    jal(ctx, 0x2C4DC0u, gen::fn_abs_0051e0e0);
                    at = slt(v0, s2);
                    if (at != 0) {
                        // 0x002c4dd4
                        charge(ctx, 2);
                        lhu(s1, s6, 0);
                        s2 = v0;
                    }
                }
            }
        }
        // 0x002c4ddc
        charge(ctx, 2);
        v0 = addiu(s0, 1);
        s0 = v0 & 0xFFFF;
    }
    // 0x002c4df4
    charge(ctx, 22);
    lw(v0, s4, act::kUnit);
    lw(a0, v0, unit::kDat);
    jal(ctx, 0x2C4DFCu, gen::fn_sub_301870_00301870);
    lw(v0, s3, act::kUnit);
    lw(a0, v0, unit::kDat);
    jal(ctx, 0x2C4E0Cu, gen::fn_sub_301870_00301870);
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
    sp = addiu(sp, 0xC0);
}

// 0x002C4E50 sub_2C4E50 -- 472 bytes; frame 0xC0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlAIPickHealItem] As sub_2C4C80 over an item list (the item's skill through sub_30BC20): the healing item closest
// to max HP.
// Arguments: a0 btlAction, a1 target, a2 item list, a3 count, t0 kind.
void sub_2C4E50(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x002c4e50
    enter(ctx, 36);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
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
    s4 = a0;
    s3 = a1;
    fp = a2;
    s6 = a3;
    s5 = t0;
    lw(v0, a1, act::kUnit);
    lw(a0, v0, unit::kDat);
    jal(ctx, 0x2C4E98u, gen::fn_datCalcGetHp_002ffd70);
    v0 = v0 & 0xFFFF;
    sq(v0, sp, 0xB0);
    lw(v0, s3, act::kUnit);
    lw(a0, v0, unit::kDat);
    jal(ctx, 0x2C4EB0u, gen::fn_datCalcGetMaxHp_002ffdf0);
    v0 = v0 & 0xFFFF;
    sq(v0, sp, 0xA0);
    s1 = si(-1);
    v0 = 0xFF0000;
    s2 = v0 | 0xFFFF;  // &0xFFFFFF
    s0 = 0;
    s5 = s5 & 0xFFFF;
    s7 = s6 & 0xFFFF;
    for (;;) {
        // 0x002c4fc0
        charge(ctx, 4);
        v0 = s0 & 0xFFFF;
        v0 = slt(v0, s7);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002c4ee0
        charge(ctx, 9);
        v0 = s0 & 0xFFFF;
        v0 = sll(v0, 1);
        s6 = addu(fp, v0);
        lhu(a0, s6, 0);
        jal(ctx, 0x2C4EF0u, gen::fn_sub_30BC20_0030bc20);
        a0 = v0 & 0xFFFF;
        if (a0 != 0) {
            // 0x002c4f04
            charge(ctx, 3);
            at = slti(a0, 464);
            if (at != 0) {
                // 0x002c4f10
                charge(ctx, 10);
                v0 = sll(a0, 2);
                v0 = addu(v0, a0);
                v0 = sll(v0, 1);
                v0 = addu(v0, a0);
                v1 = sll(v0, 2);
                lw(v0, gp, kGpSkillTbl);  // gBtlSkillTbl
                v0 = addu(v0, v1);
                lbu(a1, v0, 8);
                // The kind filter (SkillRecord +8): t0 == 0 keeps only all-target skills (1), t0 == 1 only single-target
                // ones (0), other values every skill.
                bool fits = true;
                if (s5 == 0) {
                    // 0x002c4f38
                    charge(ctx, 4);
                    v1 = a1 & 0xFF;
                    v0 = 1;
                    fits = v1 == v0;
                }
                if (fits) {
                    // 0x002c4f48
                    charge(ctx, 3);
                    v0 = 1;
                    if (s5 == v0) {
                        // 0x002c4f54
                        charge(ctx, 3);
                        v0 = a1 & 0xFF;
                        fits = v0 == 0;
                    }
                }
                if (fits) {
                    // The heal on the target (datCalcDamage(skill, user, target, 1, 1, 1, item?, 1)): keep the skill whose
                    // HP + heal is nearest to max HP (abs; HP and max HP spilled at sp + 0xB0 / 0xA0).
                    // 0x002c4f60
                    charge(ctx, 20);
                    lw(v1, s4, act::kUnit);
                    lw(v0, s3, act::kUnit);
                    lw(a1, v1, unit::kDat);
                    lw(a2, v0, unit::kDat);
                    a3 = 1;
                    t0 = a3;
                    t1 = a3;
                    t2 = a3;
                    t3 = a3;
                    jal(ctx, 0x2C4F84u, gen::fn_datCalcDamage_00303130);
                    lq(v1, sp, 0xB0);
                    v1 = addu(v1, v0);
                    lq(v0, sp, 0xA0);
                    a0 = subu(v0, v1);
                    jal(ctx, 0x2C4F9Cu, gen::fn_abs_0051e0e0);
                    at = slt(v0, s2);
                    if (at != 0) {
                        // 0x002c4fb0
                        charge(ctx, 2);
                        lhu(s1, s6, 0);
                        s2 = v0;
                    }
                }
            }
        }
        // 0x002c4fb8
        charge(ctx, 2);
        v0 = addiu(s0, 1);
        s0 = v0 & 0xFFFF;
    }
    // 0x002c4fd0
    charge(ctx, 22);
    lw(v0, s4, act::kUnit);
    lw(a0, v0, unit::kDat);
    jal(ctx, 0x2C4FD8u, gen::fn_sub_301870_00301870);
    lw(v0, s3, act::kUnit);
    lw(a0, v0, unit::kDat);
    jal(ctx, 0x2C4FE8u, gen::fn_sub_301870_00301870);
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
    sp = addiu(sp, 0xC0);
}

// 0x002C5030 sub_2C5030 -- 840 bytes; frame 0xF0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlAIPickAttackSkill] The attack skills a unit could use on a target: the normal attack when its element passes
// sub_2C2ED0, then every usable skill (sub_2C2B20 rules) whose element is an attack element (0x1FE; a3 set: not
// physical) and passes sub_2C2ED0; returns one at random (datCalcRand) or -1.
// Arguments: a0 btlAction, a1 target, a2, a3 magic only.
void sub_2C5030(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x002c5030
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0xF0);
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
    fp = a2;
    sw(a3, sp, 0xDC);
    s2 = 0;
    lw(s0, a0, act::kUnit);
    lw(a0, s0, unit::kDat);
    a1 = 0;
    jal(ctx, 0x2C507Cu, gen::fn_datCalcGetSkillElement_003082f0);
    a1 = dsll32(v0, 16);
    a1 = dsra32(a1, 16);
    a0 = s4;
    a2 = 1;
    jal(ctx, 0x2C5094u, gen::fn_sub_2C2ED0_002c2ed0);
    if (v0 != 0) {
        // 0x002c50a4
        charge(ctx, 3);
        sh(zero, sp, 0xE0);
        v0 = addiu(s2, 1);
        s2 = v0 & 0xFFFF;
    }
    // 0x002c50b0
    charge(ctx, 13);
    lw(a0, s0, unit::kDat);
    jal(ctx, 0x2C50B4u, gen::fn_datCalcGetSkillSlotCount_00308ba0);
    s1 = v0 & 0xFFFF;
    lw(a0, s0, unit::kDat);
    jal(ctx, 0x2C50C4u, gen::fn_datCalcGetSkillList_00308bb0);
    sq(v0, sp, 0xC0);
    s3 = 0;
    v0 = s1 & 0xFFFF;
    sq(v0, sp, 0xB0);
    for (;;) {
        // 0x002c5254
        charge(ctx, 5);
        v1 = s3 & 0xFFFF;
        lq(v0, sp, 0xB0);
        v0 = slt(v1, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002c50e4
        charge(ctx, 7);
        v0 = s3 & 0xFFFF;
        v1 = sll(v0, 1);
        lq(v0, sp, 0xC0);
        s6 = addu(v0, v1);
        lhu(a1, s6, 0);
        if (a1 != 0) {
            // 0x002c5100
            charge(ctx, 3);
            at = slti(a1, 464);
            if (at != 0) {
                // 0x002c510c
                charge(ctx, 12);
                lw(a0, s0, unit::kDat);
                jal(ctx, 0x2C5110u, gen::fn_datCalcGetSkillElement_003082f0);
                v0 = dsll32(v0, 16);
                v0 = dsra32(v0, 16);
                sq(v0, sp, 0xA0);
                paddub(a0, v0, zero);
                jal(ctx, 0x2C5128u, gen::fn_datCalcGetElementBit_003080c0);
                lw(v1, sp, 0xDC);
                if (v1 != 0) {
                    // 0x002c5150
                    charge(ctx, 3);
                    v1 = v0 & 0x1FE;
                    if (v1 != 0) {
                        // 0x002c515c
                        charge(ctx, 3);
                        v0 = v0 & 0xE;
                        if (v0 == 0) {
                        L_002c5168:
                            charge(ctx, 4);
                            lhu(s1, s6, 0);
                            v0 = slti(s1, 624);
                            if (v0 == 0) {
                                // 0x002c5178
                                charge(ctx, 5);
                                a0 = 0x690000;
                                a0 = addiu(a0, 28552);  // "btlAICommand.c"
                                a1 = 1128;
                                jal(ctx, 0x2C5184u, gen::fn_sub_19D3F0_0019d3f0);
                            }
                            // 0x002c518c
                            charge(ctx, 8);
                            lw(s7, s5, act::kUnit);
                            lw(a0, s7, unit::kDat);
                            v0 = 0x80000;
                            a1 = v0 | 0x274;
                            jal(ctx, 0x2C519Cu, gen::fn_datCalcChkBadStatus_00300580);
                            if (v0 == 0) {
                                // 0x002c51b8
                                charge(ctx, 6);
                                lw(a0, s7, unit::kDat);
                                a1 = s1;
                                jal(ctx, 0x2C51C0u, gen::fn_datCalcHasSkill_003005e0);
                                if (v0 != 0) {
                                    // 0x002c51dc
                                    charge(ctx, 6);
                                    lw(a0, s7, unit::kDat);
                                    a1 = s1;
                                    jal(ctx, 0x2C51E4u, gen::fn_sub_3086F0_003086f0);
                                    if (v0 == 0) {
                                        // 0x002c5200
                                        charge(ctx, 1);
                                        v0 = 1;
                                    } else {
                                        // 0x002c51f4
                                        charge(ctx, 3);
                                        v0 = 0;
                                    }
                                } else {
                                    // 0x002c51d0
                                    charge(ctx, 3);
                                    v0 = 0;
                                }
                            } else {
                                // 0x002c51ac
                                charge(ctx, 3);
                                v0 = 0;
                            }
                            // 0x002c5204
                            charge(ctx, 2);
                            if (v0 != 0) {
                                // 0x002c520c
                                charge(ctx, 9);
                                lq(v0, sp, 0xA0);
                                a1 = dsll32(v0, 16);
                                a1 = dsra32(a1, 16);
                                a0 = s4;
                                a2 = 1;
                                jal(ctx, 0x2C5220u, gen::fn_sub_2C2ED0_002c2ed0);
                                if (v0 != 0) {
                                    // 0x002c5230
                                    charge(ctx, 7);
                                    lhu(v1, s6, 0);
                                    v0 = s2 & 0xFFFF;
                                    v0 = sll(v0, 1);
                                    v0 = addu(v0, sp);
                                    sh(v1, v0, 224);
                                    v0 = addiu(s2, 1);
                                    s2 = v0 & 0xFFFF;
                                }
                            }
                        }
                    }
                } else {
                    // 0x002c513c
                    charge(ctx, 3);
                    v0 = v0 & 0x1FE;
                    if (v0 != 0) {
                        goto L_002c5168;
                    }
                    // 0x002c5148
                    charge(ctx, 2);
                }
            }
        }
        // 0x002c524c
        charge(ctx, 2);
        v0 = addiu(s3, 1);
        s3 = v0 & 0xFFFF;
    }
    // 0x002c5268
    charge(ctx, 3);
    v0 = s2 & 0xFFFF;
    if (i64(v0) <= 0) {
        // 0x002c5340
        charge(ctx, 1);
        v0 = si(-1);
    } else {
        // 0x002c5274
        charge(ctx, 3);
        t0 = 1;
        if (fp == t0) {
            // 0x002c52d8
            charge(ctx, 8);
            a0 = s5;
            a1 = s4;
            a2 = addiu(sp, 0xE0);
            a3 = s2;
            jal(ctx, 0x2C52E8u, gen::fn_sub_2C48A0_002c48a0);
            if (i64(v0) < 0) {
                // 0x002c52f8
                charge(ctx, 9);
                a0 = s5;
                a1 = s4;
                a2 = addiu(sp, 0xE0);
                a3 = s2;
                t0 = 0;
                jal(ctx, 0x2C530Cu, gen::fn_sub_2C48A0_002c48a0);
            }
        } else {
            // 0x002c5280
            charge(ctx, 2);
            if (fp == 0) {
                // 0x002c5290
                charge(ctx, 9);
                a0 = s5;
                a1 = s4;
                a2 = addiu(sp, 0xE0);
                a3 = s2;
                t0 = 0;
                jal(ctx, 0x2C52A4u, gen::fn_sub_2C48A0_002c48a0);
                if (i64(v0) < 0) {
                    // 0x002c52b4
                    charge(ctx, 9);
                    a0 = s5;
                    a1 = s4;
                    a2 = addiu(sp, 0xE0);
                    a3 = s2;
                    t0 = 1;
                    jal(ctx, 0x2C52C8u, gen::fn_sub_2C48A0_002c48a0);
                }
            } else {
                // 0x002c5288
                charge(ctx, 2);
                // 0x002c531c
                charge(ctx, 7);
                a0 = s5;
                a1 = s4;
                a2 = addiu(sp, 0xE0);
                a3 = s2;
                t0 = 0xFFFF;
                jal(ctx, 0x2C5330u, gen::fn_sub_2C48A0_002c48a0);
            }
        }
        // 0x002c5338
        charge(ctx, 2);
    }
    // 0x002c5344 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0xF0);
}

// 0x002C5380 sub_2C5380 -- 1604 bytes; frame 0xC0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlAIPickRecoverySkill] Support AI's healing choice for a target: dead -> revive skills, HP <= 60 % with an
// ailment -> cure skills, HP below max -> heal (sub_2C4C80); the usable skill of that kind, or -1.
// Arguments: a0 btlAction, a1 target, a2, a3.
void sub_2C5380(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x002c5380
    enter(ctx, 32);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
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
    s4 = a0;
    s3 = a1;
    fp = a3;
    s0 = si(-1);
    s2 = 0;
    lw(s5, a0, act::kUnit);
    lw(a0, s5, unit::kDat);
    jal(ctx, 0x2C53C8u, gen::fn_datCalcGetSkillSlotCount_00308ba0);
    s1 = v0 & 0xFFFF;
    lw(a0, s5, unit::kDat);
    jal(ctx, 0x2C53D8u, gen::fn_datCalcGetSkillList_00308bb0);
    s7 = v0;
    lw(v0, s3, act::kUnit);
    lw(a0, v0, unit::kDat);
    a1 = 0;
    jal(ctx, 0x2C53F0u, gen::fn_datCalcIsDead_0030b5a0);
    if (v0 == 0) {
        // 0x002c540c
        charge(ctx, 17);
        lw(v0, s3, act::kUnit);
        lw(a0, v0, unit::kDat);
        lhu(s5, a0, dat::kHp);
        jal(ctx, 0x2C5418u, gen::fn_datCalcGetMaxHp_002ffdf0);
        a0 = v0 & 0xFFFF;
        v0 = sll(s5, 2);
        v1 = addu(v0, s5);
        v0 = sll(v1, 2);
        v0 = addu(v1, v0);
        v1 = sll(v0, 2);
        v0 = sll(a0, 4);
        v0 = subu(v0, a0);
        v0 = sll(v0, 2);
        at = sltu(v0, v1);
        if (at != 0) {
            // 0x002c545c
            charge(ctx, 7);
            lw(v0, s3, act::kUnit);
            lw(a0, v0, unit::kDat);
            a1 = 14;
            jal(ctx, 0x2C5468u, gen::fn_datCalcChkBadStatus_00300580);
            if (v0 == 0) {
                // 0x002c5484
                charge(ctx, 13);
                lw(v0, s3, act::kUnit);
                lw(a0, v0, unit::kDat);
                jal(ctx, 0x2C548Cu, gen::fn_datCalcGetHp_002ffd70);
                s5 = v0 & 0xFFFF;
                lw(v0, s3, act::kUnit);
                lw(a0, v0, unit::kDat);
                jal(ctx, 0x2C54A0u, gen::fn_datCalcGetMaxHp_002ffdf0);
                v0 = v0 & 0xFFFF;
                at = slt(s5, v0);
                if (at != 0) {
                    // 0x002c54b8
                    charge(ctx, 1);
                    s0 = 1;
                }
            } else {
                // 0x002c5478
                charge(ctx, 3);
                s0 = 2;
            }
        } else {
            // 0x002c5450
            charge(ctx, 3);
            s0 = 1;
        }
    } else {
        // 0x002c5400
        charge(ctx, 3);
        s0 = 0;
    }
    // 0x002c54bc
    charge(ctx, 5);
    v1 = dsll32(s0, 16);
    v1 = dsra32(v1, 16);
    v0 = 2;
    if (v1 == v0) {
        // 0x002c5838
        charge(ctx, 4);
        s3 = 0;
        s6 = s1 & 0xFFFF;
        for (;;) {
            // 0x002c5954
            charge(ctx, 4);
            v0 = s3 & 0xFFFF;
            v0 = slt(v0, s6);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002c5848
            charge(ctx, 6);
            v0 = s3 & 0xFFFF;
            v0 = sll(v0, 1);
            s1 = addu(s7, v0);
            lhu(v1, s1, 0);
            if (v1 != 0) {
                // 0x002c5860
                charge(ctx, 3);
                at = slti(v1, 464);
                if (at != 0) {
                    // 0x002c586c
                    charge(ctx, 3);
                    v0 = 200;
                    if (v1 != v0) {
                        // 0x002c5878
                        charge(ctx, 3);
                        v0 = 199;
                        if (v1 == v0) {
                            goto L_002c588c;
                        }
                        // 0x002c5884
                        charge(ctx, 2);
                        goto L_002c594c;
                    }
                L_002c588c:
                    charge(ctx, 4);
                    s5 = v1 & 0xFFFF;
                    v0 = slti(s5, 624);
                    if (v0 == 0) {
                        // 0x002c589c
                        charge(ctx, 5);
                        a0 = 0x690000;
                        a0 = addiu(a0, 28552);  // "btlAICommand.c"
                        a1 = 1128;
                        jal(ctx, 0x2C58A8u, gen::fn_sub_19D3F0_0019d3f0);
                    }
                    // 0x002c58b0
                    charge(ctx, 8);
                    lw(s0, s4, act::kUnit);
                    lw(a0, s0, unit::kDat);
                    v0 = 0x80000;
                    a1 = v0 | 0x274;
                    jal(ctx, 0x2C58C0u, gen::fn_datCalcChkBadStatus_00300580);
                    if (v0 == 0) {
                        // 0x002c58dc
                        charge(ctx, 6);
                        lw(a0, s0, unit::kDat);
                        a1 = s5;
                        jal(ctx, 0x2C58E4u, gen::fn_datCalcHasSkill_003005e0);
                        if (v0 != 0) {
                            // 0x002c5900
                            charge(ctx, 6);
                            lw(a0, s0, unit::kDat);
                            a1 = s5;
                            jal(ctx, 0x2C5908u, gen::fn_sub_3086F0_003086f0);
                            if (v0 == 0) {
                                // 0x002c5924
                                charge(ctx, 1);
                                v0 = 1;
                            } else {
                                // 0x002c5918
                                charge(ctx, 3);
                                v0 = 0;
                            }
                        } else {
                            // 0x002c58f4
                            charge(ctx, 3);
                            v0 = 0;
                        }
                    } else {
                        // 0x002c58d0
                        charge(ctx, 3);
                        v0 = 0;
                    }
                    // 0x002c5928
                    charge(ctx, 2);
                    if (v0 != 0) {
                        // 0x002c5930
                        charge(ctx, 7);
                        lhu(v1, s1, 0);
                        v0 = s2 & 0xFFFF;
                        v0 = sll(v0, 1);
                        v0 = addu(v0, sp);
                        sh(v1, v0, 176);
                        v0 = addiu(s2, 1);
                        s2 = v0 & 0xFFFF;
                    }
                }
            }
        L_002c594c:
            charge(ctx, 2);
            v0 = addiu(s3, 1);
            s3 = v0 & 0xFFFF;
        }
    L_002c5964:
        charge(ctx, 3);
        a0 = s2 & 0xFFFF;
        if (i64(a0) <= 0) {
            // 0x002c598c
            charge(ctx, 1);
            v0 = si(-1);
        } else {
            // 0x002c5970
            charge(ctx, 7);
            jal(ctx, 0x2C5970u, gen::fn_datCalcRand_002ffbc0);
            v0 = sll(v0, 1);
            v0 = addu(v0, sp);
            lhu(v0, v0, 176);
        }
    } else {
        // 0x002c54d0
        charge(ctx, 3);
        v0 = 1;
        if (v1 != v0) {
            // 0x002c54dc
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x002c54ec
                charge(ctx, 4);
                s0 = 0;
                s6 = s1 & 0xFFFF;
                for (;;) {
                    // 0x002c5608
                    charge(ctx, 4);
                    v0 = s0 & 0xFFFF;
                    v0 = slt(v0, s6);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x002c54fc
                    charge(ctx, 6);
                    v0 = s0 & 0xFFFF;
                    v0 = sll(v0, 1);
                    s3 = addu(s7, v0);
                    lhu(v1, s3, 0);
                    if (v1 != 0) {
                        // 0x002c5514
                        charge(ctx, 3);
                        at = slti(v1, 464);
                        if (at != 0) {
                            // 0x002c5520
                            charge(ctx, 3);
                            v0 = 205;
                            if (v1 != v0) {
                                // 0x002c552c
                                charge(ctx, 3);
                                v0 = 204;
                                if (v1 == v0) {
                                    goto L_002c5540;
                                }
                                // 0x002c5538
                                charge(ctx, 2);
                                goto L_002c5600;
                            }
                        L_002c5540:
                            charge(ctx, 4);
                            s5 = v1 & 0xFFFF;
                            v0 = slti(s5, 624);
                            if (v0 == 0) {
                                // 0x002c5550
                                charge(ctx, 5);
                                a0 = 0x690000;
                                a0 = addiu(a0, 28552);  // "btlAICommand.c"
                                a1 = 1128;
                                jal(ctx, 0x2C555Cu, gen::fn_sub_19D3F0_0019d3f0);
                            }
                            // 0x002c5564
                            charge(ctx, 8);
                            lw(s1, s4, act::kUnit);
                            lw(a0, s1, unit::kDat);
                            v0 = 0x80000;
                            a1 = v0 | 0x274;
                            jal(ctx, 0x2C5574u, gen::fn_datCalcChkBadStatus_00300580);
                            if (v0 == 0) {
                                // 0x002c5590
                                charge(ctx, 6);
                                lw(a0, s1, unit::kDat);
                                a1 = s5;
                                jal(ctx, 0x2C5598u, gen::fn_datCalcHasSkill_003005e0);
                                if (v0 != 0) {
                                    // 0x002c55b4
                                    charge(ctx, 6);
                                    lw(a0, s1, unit::kDat);
                                    a1 = s5;
                                    jal(ctx, 0x2C55BCu, gen::fn_sub_3086F0_003086f0);
                                    if (v0 == 0) {
                                        // 0x002c55d8
                                        charge(ctx, 1);
                                        v0 = 1;
                                    } else {
                                        // 0x002c55cc
                                        charge(ctx, 3);
                                        v0 = 0;
                                    }
                                } else {
                                    // 0x002c55a8
                                    charge(ctx, 3);
                                    v0 = 0;
                                }
                            } else {
                                // 0x002c5584
                                charge(ctx, 3);
                                v0 = 0;
                            }
                            // 0x002c55dc
                            charge(ctx, 2);
                            if (v0 != 0) {
                                // 0x002c55e4
                                charge(ctx, 7);
                                lhu(v1, s3, 0);
                                v0 = s2 & 0xFFFF;
                                v0 = sll(v0, 1);
                                v0 = addu(v0, sp);
                                sh(v1, v0, 176);
                                v0 = addiu(s2, 1);
                                s2 = v0 & 0xFFFF;
                            }
                        }
                    }
                L_002c5600:
                    charge(ctx, 2);
                    v0 = addiu(s0, 1);
                    s0 = v0 & 0xFFFF;
                }
                // 0x002c5618
                charge(ctx, 2);
            } else {
                // 0x002c54e4
                charge(ctx, 2);
            }
            goto L_002c5964;
        }
        // 0x002c5620
        charge(ctx, 5);
        s0 = 0;
        v0 = s1 & 0xFFFF;
        sq(v0, sp, 0xA0);
        for (;;) {
            // 0x002c574c
            charge(ctx, 5);
            v1 = s0 & 0xFFFF;
            lq(v0, sp, 0xA0);
            v0 = slt(v1, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002c5634
            charge(ctx, 6);
            v0 = s0 & 0xFFFF;
            v0 = sll(v0, 1);
            s6 = addu(s7, v0);
            lhu(a0, s6, 0);
            if (a0 != 0) {
                // 0x002c564c
                charge(ctx, 3);
                at = slti(a0, 464);
                if (at != 0) {
                    // 0x002c5658
                    charge(ctx, 4);
                    v0 = addiu(a0, -192);
                    at = sltiu(v0, 7);
                    if (at != 0) {
                        // 0x002c5668
                        charge(ctx, 7);
                        v1 = 0x7B0000;
                        v1 = addiu(v1, 32096);  // &0x7B7D60
                        v0 = sll(v0, 2);
                        v0 = addu(v0, v1);
                        lw(v0, v0, 0);
                        switch (v0.u()) {
                        case 0x2C5684u:  // table[0, 1, 2, 3, 4, 5, 6]
                            break;
                        default:  // not one of the table's targets: the dispatch table, as the recompiled body
                            tail(ctx, v0.u());
                            return;
                        }
                        // 0x002c5684
                        charge(ctx, 4);
                        s1 = a0 & 0xFFFF;
                        v0 = slti(s1, 624);
                        if (v0 == 0) {
                            // 0x002c5694
                            charge(ctx, 5);
                            a0 = 0x690000;
                            a0 = addiu(a0, 28552);  // "btlAICommand.c"
                            a1 = 1128;
                            jal(ctx, 0x2C56A0u, gen::fn_sub_19D3F0_0019d3f0);
                        }
                        // 0x002c56a8
                        charge(ctx, 8);
                        lw(s5, s4, act::kUnit);
                        lw(a0, s5, unit::kDat);
                        v0 = 0x80000;
                        a1 = v0 | 0x274;
                        jal(ctx, 0x2C56B8u, gen::fn_datCalcChkBadStatus_00300580);
                        if (v0 == 0) {
                            // 0x002c56d4
                            charge(ctx, 6);
                            lw(a0, s5, unit::kDat);
                            a1 = s1;
                            jal(ctx, 0x2C56DCu, gen::fn_datCalcHasSkill_003005e0);
                            if (v0 != 0) {
                                // 0x002c56f8
                                charge(ctx, 6);
                                lw(a0, s5, unit::kDat);
                                a1 = s1;
                                jal(ctx, 0x2C5700u, gen::fn_sub_3086F0_003086f0);
                                if (v0 == 0) {
                                    // 0x002c571c
                                    charge(ctx, 1);
                                    v0 = 1;
                                } else {
                                    // 0x002c5710
                                    charge(ctx, 3);
                                    v0 = 0;
                                }
                            } else {
                                // 0x002c56ec
                                charge(ctx, 3);
                                v0 = 0;
                            }
                        } else {
                            // 0x002c56c8
                            charge(ctx, 3);
                            v0 = 0;
                        }
                        // 0x002c5720
                        charge(ctx, 2);
                        if (v0 != 0) {
                            // 0x002c5728
                            charge(ctx, 7);
                            lhu(v1, s6, 0);
                            v0 = s2 & 0xFFFF;
                            v0 = sll(v0, 1);
                            v0 = addu(v0, sp);
                            sh(v1, v0, 176);
                            v0 = addiu(s2, 1);
                            s2 = v0 & 0xFFFF;
                        }
                    }
                }
            }
            // 0x002c5744
            charge(ctx, 2);
            v0 = addiu(s0, 1);
            s0 = v0 & 0xFFFF;
        }
        // 0x002c5760
        charge(ctx, 3);
        v0 = s2 & 0xFFFF;
        if (i64(v0) <= 0) {
            goto L_002c5964;
        }
        // 0x002c576c
        charge(ctx, 3);
        t0 = 1;
        if (fp == t0) {
            // 0x002c57d0
            charge(ctx, 8);
            a0 = s4;
            a1 = s3;
            a2 = addiu(sp, 0xB0);
            a3 = s2;
            jal(ctx, 0x2C57E0u, gen::fn_sub_2C4C80_002c4c80);
            if (i64(v0) < 0) {
                // 0x002c57f0
                charge(ctx, 9);
                a0 = s4;
                a1 = s3;
                a2 = addiu(sp, 0xB0);
                a3 = s2;
                t0 = 0;
                jal(ctx, 0x2C5804u, gen::fn_sub_2C4C80_002c4c80);
            }
        } else {
            // 0x002c5778
            charge(ctx, 2);
            if (fp == 0) {
                // 0x002c5788
                charge(ctx, 9);
                a0 = s4;
                a1 = s3;
                a2 = addiu(sp, 0xB0);
                a3 = s2;
                t0 = 0;
                jal(ctx, 0x2C579Cu, gen::fn_sub_2C4C80_002c4c80);
                if (i64(v0) < 0) {
                    // 0x002c57ac
                    charge(ctx, 9);
                    a0 = s4;
                    a1 = s3;
                    a2 = addiu(sp, 0xB0);
                    a3 = s2;
                    t0 = 1;
                    jal(ctx, 0x2C57C0u, gen::fn_sub_2C4C80_002c4c80);
                }
            } else {
                // 0x002c5780
                charge(ctx, 2);
                // 0x002c5814
                charge(ctx, 7);
                a0 = s4;
                a1 = s3;
                a2 = addiu(sp, 0xB0);
                a3 = s2;
                t0 = 0xFFFF;
                jal(ctx, 0x2C5828u, gen::fn_sub_2C4C80_002c4c80);
            }
        }
        // 0x002c5830
        charge(ctx, 2);
    }
    // 0x002c5990 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0xC0);
}

// 0x002C59D0 sub_2C59D0 -- 1512 bytes; frame 0xB0: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlAIPickRecoveryItem] Party member AI's item choice for a target (party ids 2..10 only): revive / cure / heal
// items from the item stock (sub_170670 / sub_1706C0, sub_2C4E50), or -1.
// Arguments: a0 btlAction, a1 target, a2, a3.
void sub_2C59D0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c59d0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    sd(ra, sp, 0x80);
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
    s7 = a3;
    s1 = si(-1);
    s3 = 0;
    lw(v1, a0, act::kUnit);
    lbu(v0, v1, unit::kSide);
    if (v0 == 0) {
        // 0x002c5a28
        charge(ctx, 5);
        lw(v0, v1, unit::kDat);
        lhu(s2, v0, dat::kId);
        v0 = 1;
        if (s2 != v0) {
            // 0x002c5a3c
            charge(ctx, 3);
            v0 = slti(s2, 11);
            if (v0 == 0) {
                goto L_002c5a48;
            }
            // 0x002c5a54
            charge(ctx, 7);
            lw(v0, s4, act::kUnit);
            lw(a0, v0, unit::kDat);
            a1 = 0;
            jal(ctx, 0x2C5A60u, gen::fn_datCalcIsDead_0030b5a0);
            if (v0 == 0) {
                // 0x002c5a7c
                charge(ctx, 17);
                lw(v0, s4, act::kUnit);
                lw(a0, v0, unit::kDat);
                lhu(s0, a0, dat::kHp);
                jal(ctx, 0x2C5A88u, gen::fn_datCalcGetMaxHp_002ffdf0);
                a0 = v0 & 0xFFFF;
                v0 = sll(s0, 2);
                v1 = addu(v0, s0);
                v0 = sll(v1, 2);
                v0 = addu(v1, v0);
                v1 = sll(v0, 2);
                v0 = sll(a0, 4);
                v0 = subu(v0, a0);
                v0 = sll(v0, 2);
                at = sltu(v0, v1);
                if (at != 0) {
                    // 0x002c5acc
                    charge(ctx, 8);
                    lw(v0, s4, act::kUnit);
                    lw(a0, v0, unit::kDat);
                    v0 = 0xF0000;
                    a1 = v0 | 0xFFFF;
                    jal(ctx, 0x2C5ADCu, gen::fn_datCalcChkBadStatus_00300580);
                    if (v0 == 0) {
                        // 0x002c5af8
                        charge(ctx, 13);
                        lw(v0, s4, act::kUnit);
                        lw(a0, v0, unit::kDat);
                        jal(ctx, 0x2C5B00u, gen::fn_datCalcGetHp_002ffd70);
                        s0 = v0 & 0xFFFF;
                        lw(v0, s4, act::kUnit);
                        lw(a0, v0, unit::kDat);
                        jal(ctx, 0x2C5B14u, gen::fn_datCalcGetMaxHp_002ffdf0);
                        v0 = v0 & 0xFFFF;
                        at = slt(s0, v0);
                        if (at != 0) {
                            // 0x002c5b2c
                            charge(ctx, 1);
                            s1 = 1;
                        }
                    } else {
                        // 0x002c5aec
                        charge(ctx, 3);
                        s1 = 2;
                    }
                } else {
                    // 0x002c5ac0
                    charge(ctx, 3);
                    s1 = 1;
                }
            } else {
                // 0x002c5a70
                charge(ctx, 3);
                s1 = 0;
            }
            // 0x002c5b30
            charge(ctx, 5);
            v1 = dsll32(s1, 16);
            v1 = dsra32(v1, 16);
            v0 = 2;
            if (v1 == v0) {
                // 0x002c5dbc
                charge(ctx, 5);
                s1 = 0;
                s2 = dsll32(s2, 16);
                s2 = dsra32(s2, 16);
                for (;;) {
                    // 0x002c5f4c
                    charge(ctx, 4);
                    v0 = s1 & 0xFFFF;
                    v0 = slti(v0, 12);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x002c5dd0
                    charge(ctx, 10);
                    s5 = dsll32(s1, 16);
                    s5 = dsra32(s5, 16);
                    a0 = s2;
                    a1 = s5;
                    jal(ctx, 0x2C5DE0u, gen::fn_sub_170670_00170670);
                    s0 = v0 & 0xFFFF;
                    at = slti(s0, 4001);
                    if (at == 0) {
                        // 0x002c5df8
                        charge(ctx, 3);
                        at = slti(s0, 4224);
                        if (at != 0) {
                            // 0x002c5e04
                            charge(ctx, 8);
                            a0 = s2;
                            a1 = s5;
                            jal(ctx, 0x2C5E0Cu, gen::fn_sub_1706C0_001706c0);
                            v0 = dsll32(v0, 16);
                            v0 = dsra32(v0, 16);
                            if (i64(v0) > 0) {
                                // 0x002c5e24
                                charge(ctx, 3);
                                v0 = 4011;
                                if (s0 == v0) {
                                    // 0x002c5f10
                                    charge(ctx, 7);
                                    lw(v0, s4, act::kUnit);
                                    lw(a0, v0, unit::kDat);
                                    a1 = 14;
                                    jal(ctx, 0x2C5F1Cu, gen::fn_datCalcChkBadStatus_00300580);
                                    if (v0 != 0) {
                                        // 0x002c5f2c
                                        charge(ctx, 6);
                                        v0 = s3 & 0xFFFF;
                                        v0 = sll(v0, 1);
                                        v0 = addu(v0, sp);
                                        sh(s0, v0, 144);
                                        v0 = addiu(s3, 1);
                                        s3 = v0 & 0xFFFF;
                                    }
                                } else {
                                    // 0x002c5e30
                                    charge(ctx, 3);
                                    v0 = 4020;
                                    if (s0 == v0) {
                                        // 0x002c5ed4
                                        charge(ctx, 7);
                                        lw(v0, s4, act::kUnit);
                                        lw(a0, v0, unit::kDat);
                                        a1 = 1;
                                        jal(ctx, 0x2C5EE0u, gen::fn_datCalcChkBadStatus_00300580);
                                        if (v0 != 0) {
                                            // 0x002c5ef0
                                            charge(ctx, 8);
                                            v0 = s3 & 0xFFFF;
                                            v0 = sll(v0, 1);
                                            v0 = addu(v0, sp);
                                            sh(s0, v0, 144);
                                            v0 = addiu(s3, 1);
                                            s3 = v0 & 0xFFFF;
                                        }
                                    } else {
                                        // 0x002c5e3c
                                        charge(ctx, 3);
                                        v0 = 4019;
                                        if (s0 == v0) {
                                            // 0x002c5e98
                                            charge(ctx, 7);
                                            lw(v0, s4, act::kUnit);
                                            lw(a0, v0, unit::kDat);
                                            a1 = 16;
                                            jal(ctx, 0x2C5EA4u, gen::fn_datCalcChkBadStatus_00300580);
                                            if (v0 != 0) {
                                                // 0x002c5eb4
                                                charge(ctx, 8);
                                                v0 = s3 & 0xFFFF;
                                                v0 = sll(v0, 1);
                                                v0 = addu(v0, sp);
                                                sh(s0, v0, 144);
                                                v0 = addiu(s3, 1);
                                                s3 = v0 & 0xFFFF;
                                            }
                                        } else {
                                            // 0x002c5e48
                                            charge(ctx, 3);
                                            v0 = 4008;
                                            if (s0 == v0) {
                                                // 0x002c5e5c
                                                charge(ctx, 7);
                                                lw(v0, s4, act::kUnit);
                                                lw(a0, v0, unit::kDat);
                                                a1 = 128;
                                                jal(ctx, 0x2C5E68u, gen::fn_datCalcChkBadStatus_00300580);
                                                if (v0 != 0) {
                                                    // 0x002c5e78
                                                    charge(ctx, 8);
                                                    v0 = s3 & 0xFFFF;
                                                    v0 = sll(v0, 1);
                                                    v0 = addu(v0, sp);
                                                    sh(s0, v0, 144);
                                                    v0 = addiu(s3, 1);
                                                    s3 = v0 & 0xFFFF;
                                                }
                                            } else {
                                                // 0x002c5e54
                                                charge(ctx, 2);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    // 0x002c5f44
                    charge(ctx, 2);
                    v0 = addiu(s1, 1);
                    s1 = v0 & 0xFFFF;
                }
            L_002c5f5c:
                charge(ctx, 3);
                a0 = s3 & 0xFFFF;
                if (i64(a0) <= 0) {
                    // 0x002c5f84
                    charge(ctx, 1);
                    v0 = si(-1);
                } else {
                    // 0x002c5f68
                    charge(ctx, 7);
                    jal(ctx, 0x2C5F68u, gen::fn_datCalcRand_002ffbc0);
                    v0 = sll(v0, 1);
                    v0 = addu(v0, sp);
                    lhu(v0, v0, 144);
                }
            } else {
                // 0x002c5b44
                charge(ctx, 3);
                v0 = 1;
                if (v1 != v0) {
                    // 0x002c5b50
                    charge(ctx, 2);
                    if (v1 == 0) {
                        // 0x002c5b60
                        charge(ctx, 5);
                        s4 = 0;
                        s2 = dsll32(s2, 16);
                        s2 = dsra32(s2, 16);
                        for (;;) {
                            // 0x002c5c08
                            charge(ctx, 4);
                            v0 = s4 & 0xFFFF;
                            v0 = slti(v0, 12);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x002c5b74
                            charge(ctx, 10);
                            s1 = dsll32(s4, 16);
                            s1 = dsra32(s1, 16);
                            a0 = s2;
                            a1 = s1;
                            jal(ctx, 0x2C5B84u, gen::fn_sub_170670_00170670);
                            s0 = v0 & 0xFFFF;
                            at = slti(s0, 4001);
                            if (at == 0) {
                                // 0x002c5b9c
                                charge(ctx, 3);
                                at = slti(s0, 4224);
                                if (at != 0) {
                                    // 0x002c5ba8
                                    charge(ctx, 3);
                                    v0 = 4010;
                                    if (s0 != v0) {
                                        // 0x002c5bb4
                                        charge(ctx, 3);
                                        v0 = 4009;
                                        if (s0 == v0) {
                                            goto L_002c5bc8;
                                        }
                                        // 0x002c5bc0
                                        charge(ctx, 2);
                                        goto L_002c5c00;
                                    }
                                L_002c5bc8:
                                    charge(ctx, 8);
                                    a0 = s2;
                                    a1 = s1;
                                    jal(ctx, 0x2C5BD0u, gen::fn_sub_1706C0_001706c0);
                                    v0 = dsll32(v0, 16);
                                    v0 = dsra32(v0, 16);
                                    if (i64(v0) > 0) {
                                        // 0x002c5be8
                                        charge(ctx, 6);
                                        v0 = s3 & 0xFFFF;
                                        v0 = sll(v0, 1);
                                        v0 = addu(v0, sp);
                                        sh(s0, v0, 144);
                                        v0 = addiu(s3, 1);
                                        s3 = v0 & 0xFFFF;
                                    }
                                }
                            }
                        L_002c5c00:
                            charge(ctx, 2);
                            v0 = addiu(s4, 1);
                            s4 = v0 & 0xFFFF;
                        }
                        // 0x002c5c18
                        charge(ctx, 2);
                    } else {
                        // 0x002c5b58
                        charge(ctx, 2);
                    }
                    goto L_002c5f5c;
                }
                // 0x002c5c20
                charge(ctx, 5);
                s1 = 0;
                s2 = dsll32(s2, 16);
                s2 = dsra32(s2, 16);
                for (;;) {
                    // 0x002c5cd4
                    charge(ctx, 4);
                    v0 = s1 & 0xFFFF;
                    v0 = slti(v0, 12);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x002c5c34
                    charge(ctx, 10);
                    s6 = dsll32(s1, 16);
                    s6 = dsra32(s6, 16);
                    a0 = s2;
                    a1 = s6;
                    jal(ctx, 0x2C5C44u, gen::fn_sub_170670_00170670);
                    s0 = v0 & 0xFFFF;
                    at = slti(s0, 4001);
                    if (at == 0) {
                        // 0x002c5c5c
                        charge(ctx, 3);
                        at = slti(s0, 4224);
                        if (at != 0) {
                            // 0x002c5c68
                            charge(ctx, 3);
                            v0 = 4003;
                            if (s0 != v0) {
                                // 0x002c5c74
                                charge(ctx, 3);
                                v0 = 4002;
                                if (s0 == v0) {
                                    goto L_002c5c94;
                                }
                                // 0x002c5c80
                                charge(ctx, 3);
                                v0 = 4001;
                                if (s0 == v0) {
                                    goto L_002c5c94;
                                }
                                // 0x002c5c8c
                                charge(ctx, 2);
                                goto L_002c5ccc;
                            }
                        L_002c5c94:
                            charge(ctx, 8);
                            a0 = s2;
                            a1 = s6;
                            jal(ctx, 0x2C5C9Cu, gen::fn_sub_1706C0_001706c0);
                            v0 = dsll32(v0, 16);
                            v0 = dsra32(v0, 16);
                            if (i64(v0) > 0) {
                                // 0x002c5cb4
                                charge(ctx, 6);
                                v0 = s3 & 0xFFFF;
                                v0 = sll(v0, 1);
                                v0 = addu(v0, sp);
                                sh(s0, v0, 144);
                                v0 = addiu(s3, 1);
                                s3 = v0 & 0xFFFF;
                            }
                        }
                    }
                L_002c5ccc:
                    charge(ctx, 2);
                    v0 = addiu(s1, 1);
                    s1 = v0 & 0xFFFF;
                }
                // 0x002c5ce4
                charge(ctx, 3);
                v0 = s3 & 0xFFFF;
                if (i64(v0) <= 0) {
                    goto L_002c5f5c;
                }
                // 0x002c5cf0
                charge(ctx, 3);
                t0 = 1;
                if (s7 == t0) {
                    // 0x002c5d54
                    charge(ctx, 8);
                    a0 = s5;
                    a1 = s4;
                    a2 = addiu(sp, 0x90);
                    a3 = s3;
                    jal(ctx, 0x2C5D64u, gen::fn_sub_2C4E50_002c4e50);
                    if (i64(v0) < 0) {
                        // 0x002c5d74
                        charge(ctx, 9);
                        a0 = s5;
                        a1 = s4;
                        a2 = addiu(sp, 0x90);
                        a3 = s3;
                        t0 = 0;
                        jal(ctx, 0x2C5D88u, gen::fn_sub_2C4E50_002c4e50);
                    }
                } else {
                    // 0x002c5cfc
                    charge(ctx, 2);
                    if (s7 == 0) {
                        // 0x002c5d0c
                        charge(ctx, 9);
                        a0 = s5;
                        a1 = s4;
                        a2 = addiu(sp, 0x90);
                        a3 = s3;
                        t0 = 0;
                        jal(ctx, 0x2C5D20u, gen::fn_sub_2C4E50_002c4e50);
                        if (i64(v0) < 0) {
                            // 0x002c5d30
                            charge(ctx, 9);
                            a0 = s5;
                            a1 = s4;
                            a2 = addiu(sp, 0x90);
                            a3 = s3;
                            t0 = 1;
                            jal(ctx, 0x2C5D44u, gen::fn_sub_2C4E50_002c4e50);
                        }
                    } else {
                        // 0x002c5d04
                        charge(ctx, 2);
                        // 0x002c5d98
                        charge(ctx, 7);
                        a0 = s5;
                        a1 = s4;
                        a2 = addiu(sp, 0x90);
                        a3 = s3;
                        t0 = 0xFFFF;
                        jal(ctx, 0x2C5DACu, gen::fn_sub_2C4E50_002c4e50);
                    }
                }
                // 0x002c5db4
                charge(ctx, 2);
            }
            // 0x002c5f88 (the shared epilogue, written out on this path)
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
            sp = addiu(sp, 0xB0);
            return;
        }
    L_002c5a48:
        charge(ctx, 3);
        v0 = si(-1);
    } else {
        // 0x002c5a1c
        charge(ctx, 3);
        v0 = s1;
    }
    // 0x002c5f88 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0xB0);
}

// 0x002C5FC0 sub_2C5FC0 -- 824 bytes; frame 0xF0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlAIPickSkillOfElement] A usable skill of the element a2 against a target (16 = recovery: sub_2C5380), the normal
// attack included; one at random or -1.
// Arguments: a0 btlAction, a1 target, a2 element, a3.
void sub_2C5FC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x002c5fc0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0xF0);
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
    sw(a3, sp, 0xDC);
    s6 = dsll32(a2, 16);
    s6 = dsra32(s6, 16);
    v0 = 16;
    if (s6 != v0) {
        // 0x002c601c
        charge(ctx, 10);
        s2 = 0;
        lw(s0, s5, act::kUnit);
        lw(a0, s0, unit::kDat);
        a1 = 0;
        jal(ctx, 0x2C602Cu, gen::fn_datCalcGetSkillElement_003082f0);
        a1 = dsll32(v0, 16);
        a1 = dsra32(a1, 16);
        if (a1 == s6) {
            // 0x002c6044
            charge(ctx, 6);
            a0 = s4;
            a2 = 1;
            jal(ctx, 0x2C604Cu, gen::fn_sub_2C2ED0_002c2ed0);
            if (v0 != 0) {
                // 0x002c605c
                charge(ctx, 3);
                sh(zero, sp, 0xE0);
                v0 = addiu(s2, 1);
                s2 = v0 & 0xFFFF;
            }
        }
        // 0x002c6068
        charge(ctx, 13);
        lw(a0, s0, unit::kDat);
        jal(ctx, 0x2C606Cu, gen::fn_datCalcGetSkillSlotCount_00308ba0);
        s1 = v0 & 0xFFFF;
        lw(a0, s0, unit::kDat);
        jal(ctx, 0x2C607Cu, gen::fn_datCalcGetSkillList_00308bb0);
        sq(v0, sp, 0xC0);
        s3 = 0;
        v0 = s1 & 0xFFFF;
        sq(v0, sp, 0xB0);
        for (;;) {
            // 0x002c61d0
            charge(ctx, 5);
            v1 = s3 & 0xFFFF;
            lq(v0, sp, 0xB0);
            v0 = slt(v1, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002c609c
            charge(ctx, 7);
            v0 = s3 & 0xFFFF;
            v1 = sll(v0, 1);
            lq(v0, sp, 0xC0);
            s7 = addu(v0, v1);
            lhu(a1, s7, 0);
            if (a1 != 0) {
                // 0x002c60b8
                charge(ctx, 3);
                at = slti(a1, 464);
                if (at != 0) {
                    // 0x002c60c4
                    charge(ctx, 8);
                    lw(a0, s0, unit::kDat);
                    jal(ctx, 0x2C60C8u, gen::fn_datCalcGetSkillElement_003082f0);
                    v0 = dsll32(v0, 16);
                    v0 = dsra32(v0, 16);
                    sq(v0, sp, 0xA0);
                    if (v0 == s6) {
                        // 0x002c60e4
                        charge(ctx, 4);
                        lhu(s1, s7, 0);
                        v0 = slti(s1, 624);
                        if (v0 == 0) {
                            // 0x002c60f4
                            charge(ctx, 5);
                            a0 = 0x690000;
                            a0 = addiu(a0, 28552);  // "btlAICommand.c"
                            a1 = 1128;
                            jal(ctx, 0x2C6100u, gen::fn_sub_19D3F0_0019d3f0);
                        }
                        // 0x002c6108
                        charge(ctx, 8);
                        lw(fp, s5, act::kUnit);
                        lw(a0, fp, unit::kDat);
                        v0 = 0x80000;
                        a1 = v0 | 0x274;
                        jal(ctx, 0x2C6118u, gen::fn_datCalcChkBadStatus_00300580);
                        if (v0 == 0) {
                            // 0x002c6134
                            charge(ctx, 6);
                            lw(a0, fp, unit::kDat);
                            a1 = s1;
                            jal(ctx, 0x2C613Cu, gen::fn_datCalcHasSkill_003005e0);
                            if (v0 != 0) {
                                // 0x002c6158
                                charge(ctx, 6);
                                lw(a0, fp, unit::kDat);
                                a1 = s1;
                                jal(ctx, 0x2C6160u, gen::fn_sub_3086F0_003086f0);
                                if (v0 == 0) {
                                    // 0x002c617c
                                    charge(ctx, 1);
                                    v0 = 1;
                                } else {
                                    // 0x002c6170
                                    charge(ctx, 3);
                                    v0 = 0;
                                }
                            } else {
                                // 0x002c614c
                                charge(ctx, 3);
                                v0 = 0;
                            }
                        } else {
                            // 0x002c6128
                            charge(ctx, 3);
                            v0 = 0;
                        }
                        // 0x002c6180
                        charge(ctx, 2);
                        if (v0 != 0) {
                            // 0x002c6188
                            charge(ctx, 9);
                            lq(v0, sp, 0xA0);
                            a1 = dsll32(v0, 16);
                            a1 = dsra32(a1, 16);
                            a0 = s4;
                            a2 = 1;
                            jal(ctx, 0x2C619Cu, gen::fn_sub_2C2ED0_002c2ed0);
                            if (v0 != 0) {
                                // 0x002c61ac
                                charge(ctx, 7);
                                lhu(v1, s7, 0);
                                v0 = s2 & 0xFFFF;
                                v0 = sll(v0, 1);
                                v0 = addu(v0, sp);
                                sh(v1, v0, 224);
                                v0 = addiu(s2, 1);
                                s2 = v0 & 0xFFFF;
                            }
                        }
                    }
                }
            }
            // 0x002c61c8
            charge(ctx, 2);
            v0 = addiu(s3, 1);
            s3 = v0 & 0xFFFF;
        }
        // 0x002c61e4
        charge(ctx, 3);
        v0 = s2 & 0xFFFF;
        if (i64(v0) <= 0) {
            // 0x002c62c0
            charge(ctx, 1);
            v0 = si(-1);
        } else {
            // 0x002c61f0
            charge(ctx, 4);
            t0 = 1;
            lw(v0, sp, 0xDC);
            if (v0 == t0) {
                // 0x002c6258
                charge(ctx, 8);
                a0 = s5;
                a1 = s4;
                a2 = addiu(sp, 0xE0);
                a3 = s2;
                jal(ctx, 0x2C6268u, gen::fn_sub_2C48A0_002c48a0);
                if (i64(v0) < 0) {
                    // 0x002c6278
                    charge(ctx, 9);
                    a0 = s5;
                    a1 = s4;
                    a2 = addiu(sp, 0xE0);
                    a3 = s2;
                    t0 = 0;
                    jal(ctx, 0x2C628Cu, gen::fn_sub_2C48A0_002c48a0);
                }
            } else {
                // 0x002c6200
                charge(ctx, 2);
                if (v0 == 0) {
                    // 0x002c6210
                    charge(ctx, 9);
                    a0 = s5;
                    a1 = s4;
                    a2 = addiu(sp, 0xE0);
                    a3 = s2;
                    t0 = 0;
                    jal(ctx, 0x2C6224u, gen::fn_sub_2C48A0_002c48a0);
                    if (i64(v0) < 0) {
                        // 0x002c6234
                        charge(ctx, 9);
                        a0 = s5;
                        a1 = s4;
                        a2 = addiu(sp, 0xE0);
                        a3 = s2;
                        t0 = 1;
                        jal(ctx, 0x2C6248u, gen::fn_sub_2C48A0_002c48a0);
                    }
                } else {
                    // 0x002c6208
                    charge(ctx, 2);
                    // 0x002c629c
                    charge(ctx, 9);
                    a0 = s5;
                    a1 = s4;
                    a2 = addiu(sp, 0xE0);
                    a3 = s2;
                    t0 = 0xFFFF;
                    jal(ctx, 0x2C62B0u, gen::fn_sub_2C48A0_002c48a0);
                }
            }
        }
    } else {
        // 0x002c600c
        charge(ctx, 4);
        jal(ctx, 0x2C600Cu, gen::fn_sub_2C5380_002c5380);
    }
    // 0x002c62c4 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0xF0);
}

// 0x002C6F50 sub_2C6F50 -- 372 bytes; frame 0x80: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlAIRunScript] Starts an AI script for an action: party units use the procedure "AI_PC_%03X_%03X" (tactic,
// persona) of the script a2, enemies the index a3; a script task with the action as user data and the unit's name in
// its message window, a child of the battle task; kept in the AI record +76.
// Arguments: a0 btlAction, a1 AI record, a2 script, a3 index.
void sub_2C6F50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c6f50
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    s2 = a2;
    lw(v1, a0, act::kUnit);
    lbu(v0, v1, unit::kSide);
    if (v0 != 0) {
        // 0x002c6fc4
        charge(ctx, 1);
        v0 = a3;
    } else {
        // 0x002c6f88
        charge(ctx, 15);
        lw(v0, v1, unit::kDat);
        lbu(v0, v0, dat4::kTactic);
        a0 = addiu(sp, 0x60);
        a1 = 0x690000;
        a1 = addiu(a1, 30480);  // "AI_PC_%03X_%03X"
        a2 = a3;
        a3 = v0;
        jal(ctx, 0x2C6FA4u, gen::fn_sprintf_00523ac8);
        a0 = s2;
        a1 = addiu(sp, 0x60);
        jal(ctx, 0x2C6FB4u, gen::fn_scrFindPrcdIdxByName_0035c090);
    }
    // 0x002c6fc8
    charge(ctx, 20);
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v1, v1, gbtl4::kTask);
    lw(v1, v1, 32);
    a0 = addiu(v1, -1);
    a1 = s2;
    a2 = v0;
    jal(ctx, 0x2C6FE0u, gen::fn_scrCreateTaskFromHeader_0035bb40);
    s4 = v0;
    a0 = s4;
    a1 = s1;
    jal(ctx, 0x2C6FF4u, gen::fn_scrSetUserData_0035c1a0);
    a0 = s4;
    jal(ctx, 0x2C7000u, gen::fn_dds3GetProcessWorkData_0035ae10);
    s2 = v0;
    lw(v0, v0, 204);
    if (i64(v0) >= 0) {
        // 0x002c7018
        charge(ctx, 5);
        lw(a0, s1, act::kUnit);
        lbu(v1, a0, unit::kSide);
        v0 = 1;
        if (v1 == v0) {
            // 0x002c7054
            charge(ctx, 7);
            lhu(v1, a0, unit::kId);
            v0 = sll(v1, 3);
            v0 = addu(v0, v1);
            v0 = sll(v0, 1);
            v1 = addu(v0, v1);
            lw(v0, gp, kGpEnemyNames);  // MSG.TBL section 2 0x7CE4E8
            s3 = addu(v0, v1);
        } else {
            // 0x002c702c
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x002c703c
                charge(ctx, 6);
                lh(a0, a0, unit::kId);
                jal(ctx, 0x2C7040u, gen::fn_sub_1778B0_001778b0);
                s3 = v0;
            } else {
                // 0x002c7034
                charge(ctx, 2);
            }
        }
        // 0x002c7070
        charge(ctx, 5);
        lw(a0, s2, 204);
        a1 = 0;
        a2 = s3;
        jal(ctx, 0x2C707Cu, gen::fn_sub_3A4220_003a4220);
    }
    // 0x002c7084
    charge(ctx, 16);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(a0, v0, gbtl4::kTask);
    a1 = s4;
    jal(ctx, 0x2C7090u, gen::fn_kwlnTaskAddChild_00195550);
    sw(s4, s0, 76);
    v0 = 1;
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x002C70D0 sub_2C70D0 -- 372 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlAIThink] AI think: clears the record, then for an enemy with an AI script (AICALC section 15 row +2) or a party
// member runs the script (sub_2C6F50); otherwise evaluates the AICALC row (sub_2C6BA0 / sub_2C6E30), decodes the
// command (sub_2C6A00) and calls the target selector of the table 0x6975E0 (falling back to row 0).
// Arguments: a0 btlAction, a1 AI record.
void sub_2C70D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c70d0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;                    // s4 = the action
    s3 = a1;                    // s3 = its command block (+56)
    lw(v0, a0, act::kUnit);
    lhu(s0, v0, unit::kId);
    a0 = s3;
    jal(ctx, 0x2C7100u, gen::fn_sub_2D15A0_002d15a0);
    lw(v0, s4, act::kUnit);
    lbu(v1, v0, unit::kSide);
    v0 = 1;
    if (v1 == v0) {
        // An enemy: the AI script index of its AICALC section-15 row (+2) in the boss AI script.
        // 0x002c713c
        charge(ctx, 10);
        lw(a0, gp, kGpAiBossRows);  // AICALC.TBL section 15: 164-byte AI rows by enemy id (sub_2C6BA0 / sub_2C6E30) 0x7CE41C
        v1 = s0 & 0xFFFF;
        v0 = sll(v1, 2);
        v0 = addu(v0, v1);
        v0 = sll(v0, 3);
        v0 = addu(v0, v1);
        v0 = sll(v0, 2);
        v0 = addu(v0, a0);
        lhu(s2, v0, 2);
        lw(s1, gp, kGpBossScript);  // the boss AI script 0x7CE4D0
    } else {
        // 0x002c711c
        charge(ctx, 2);
        if (v1 == 0) {
            // A party member: its party id in the party AI script.
            // 0x002c712c
            charge(ctx, 4);
            s2 = s0 & 0xFFFF;
            lw(s1, gp, kGpPartyAiScript);  // the party AI script 0x7CE4CC
        } else {
            // 0x002c7124
            charge(ctx, 2);
        }
    }
    // 0x002c7164
    charge(ctx, 3);
    a3 = s2 & 0xFFFF;
    if (i64(a3) <= 0) {
        // No script: the AICALC row (sub_2C6BA0 answer, sub_2C6E30 entry), its command (sub_2C6A00) and its target
        // selector -- entry +4 = selector index << 24 | parameter, through the table 0x6975E0 (8-byte rows); row 0
        // (the default selector sub_2C3770) when it finds nothing.
        // 0x002c7194
        charge(ctx, 29);
        a0 = s4;
        jal(ctx, 0x2C7198u, gen::fn_sub_2C6BA0_002c6ba0);
        a1 = v0 & 0xFFFF;
        a0 = s4;
        jal(ctx, 0x2C71A8u, gen::fn_sub_2C6E30_002c6e30);
        s0 = v0;
        a0 = s4;
        a1 = s3;
        lhu(a2, v0, 2);
        jal(ctx, 0x2C71C0u, gen::fn_sub_2C6A00_002c6a00);
        lw(v1, s0, 4);
        a1 = dsll32(v1, 8);
        a1 = dsrl32(a1, 8);
        a0 = s4;
        v0 = lui(0xFF00);
        v0 = v1 & v0;
        v0 = srl(v0, 24);
        v1 = sll(v0, 3);
        v0 = 0x690000;
        v0 = addiu(v0, 30176);  // the target selector table 0x6975E0
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        jalr(ctx, 0x2C71F8u, v0.u());
        if (v0 == 0) {
            // 0x002c7208
            charge(ctx, 6);
            a0 = s4;
            a1 = 0;
            v0 = 0x690000;
            lw(v0, v0, 30176);  // 0x6975E0
            jalr(ctx, 0x2C7218u, v0.u());
        }
    } else {
        // A script decides: run it (sub_2C6F50) and mark the command block (+48 = 1).
        // 0x002c7170
        charge(ctx, 9);
        a0 = s4;
        a1 = s3;
        a2 = s1;
        jal(ctx, 0x2C717Cu, gen::fn_sub_2C6F50_002c6f50);
        v1 = 1;
        sb(v1, s3, 48);         // act4::kCmdScript - 56
    }
    // 0x002c7220 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x002D1570 sub_2D1570 -- 40 bytes; frame 0x10: ra sp+0x0
// Clears an action's 80-byte record.
// Arguments: a0 record.
void sub_2D1570(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002d1570
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a1 = 0;
    a2 = 80;
    jal(ctx, 0x2D1580u, gen::fn_memset_00521408);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002D15A0 sub_2D15A0 -- 60 bytes; frame 0x10: ra sp+0x0
// Clears an action's target words (+50..+56) and the 6 bytes at +62.
// Arguments: a0 btlAction + n.
void sub_2D15A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002d15a0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    sh(zero, a0, 50);
    sh(zero, a0, 54);
    sh(zero, a0, 56);
    sh(zero, a0, 52);
    a0 = addiu(a0, 62);
    a1 = 0;
    a2 = 6;
    jal(ctx, 0x2D15C4u, gen::fn_memset_00521408);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002D1E70 sub_2D1E70 -- 84 bytes; frame 0x20: ra sp+0x0
// [btlVecDistance] Distance between two points (sub_4C6AC0 of the difference).
// Arguments: a0 / a1 f32[3].
void sub_2D1E70(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x002d1e70
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x0);
    lwc1(f1, a0, 0);
    lwc1(f0, a1, 0);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x10);
    lwc1(f1, a0, 4);
    lwc1(f0, a1, 4);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x14);
    lwc1(f1, a0, 8);
    lwc1(f0, a1, 8);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x18);
    a0 = addiu(sp, 0x10);
    jal(ctx, 0x2D1EACu, gen::fn_sub_4C6AC0_004c6ac0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002D1ED0 sub_2D1ED0 -- 88 bytes; frame 0x20: ra sp+0x0
// [btlVecDistanceXZ] Distance between two points on the ground plane (y ignored).
// Arguments: a0 / a1 f32[3].
void sub_2D1ED0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x002d1ed0
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x0);
    lwc1(f1, a0, 0);
    lwc1(f0, a1, 0);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x10);
    lwc1(f1, a0, 4);
    lwc1(f0, a1, 4);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x14);
    lwc1(f1, a0, 8);
    lwc1(f0, a1, 8);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x18);
    sw(zero, sp, 0x14);
    a0 = addiu(sp, 0x10);
    jal(ctx, 0x2D1F10u, gen::fn_sub_4C6AC0_004c6ac0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002D1F30 sub_2D1F30 -- 156 bytes; frame 0x10: ra sp+0x0
// [btlQuatAngle] Angle between two quaternions: 2 acos(|q1 . q2|).
// Arguments: a0 / a1 f32[4].
void sub_2D1F30(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f12{ctx, 12};
    // 0x002d1f30
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lwc1(f9, a1, 4);
    lwc1(f8, a0, 4);
    lwc1(f1, a1, 0);
    lwc1(f7, a0, 0);
    lwc1(f0, a1, 8);
    lwc1(f6, a0, 8);
    mula_s(f8, f9);
    mtc1(zero, f5);
    madda_s(f7, f1);
    madda_s(f6, f0);
    lwc1(f4, a1, 12);
    lwc1(f3, a0, 12);
    madd_s(f12, f3, f4);
    c_lt_s(f12, f5);
    if (cond(ctx)) {
        // 0x002d1f78
        charge(ctx, 11);
        neg_s(f2, f0);
        neg_s(f1, f1);
        neg_s(f0, f9);
        mul_s(f0, f8, f0);
        adda_s(f5, f0);
        madd_s(f0, f7, f1);
        adda_s(f5, f0);
        madd_s(f1, f6, f2);
        neg_s(f0, f4);
        adda_s(f5, f1);
        madd_s(f12, f3, f0);
    }
    // 0x002d1fa4
    charge(ctx, 10);
    jal(ctx, 0x2D1FA4u, gen::fn_acosf_0052e9e8);
    v0 = 0x40000000;
    mtc1(v0, f1);
    mul_s(f0, f1, f0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002D1FD0 sub_2D1FD0 -- 208 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Ground-plane direction from a1 to a0 normalised (sub_4C6B20); with a3, the point a2 rotated into that frame.
// Arguments: a0 / a1 / a2 vectors, a3 out.
void sub_2D1FD0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5};
    // 0x002d1fd0
    enter(ctx, 35);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a2;
    s0 = a3;
    lwc1(f1, a0, 0);
    lwc1(f0, a1, 0);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x48);
    lwc1(f1, a0, 4);
    lwc1(f0, a1, 4);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x4C);
    a0 = addiu(sp, 0x48);
    a1 = a0;
    jal(ctx, 0x2D2018u, gen::fn_sub_4C6B20_004c6b20);
    lwc1(f5, sp, 0x4C);
    lwc1(f4, s1, 0);
    lwc1(f0, s2, 0);
    sub_s(f3, f4, f0);
    lwc1(f1, s1, 4);
    lwc1(f0, s2, 4);
    sub_s(f1, f1, f0);
    lwc1(f0, sp, 0x48);
    neg_s(f0, f0);
    mula_s(f1, f0);
    mtc1(zero, f2);
    madd_s(f3, f3, f5);
    if (s0 != 0) {
        // 0x002d205c
        charge(ctx, 9);
        adda_s(f2, f4);
        msub_s(f0, f3, f5);
        swc1(f0, s0, 0);
        lwc1(f0, sp, 0x48);
        neg_s(f1, f0);
        lwc1(f0, s1, 4);
        adda_s(f2, f0);
        msub_s(f0, f3, f1);
        swc1(f0, s0, 4);
    }
    // 0x002d2080 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    abs_s(f0, f3);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x002D20A0 sub_2D20A0 -- 320 bytes; frame 0x50: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [btlWorldToScreen] Projects a world point to the screen: camera space (sub_4C6BE0 with the camera matrix sub_198590
// +32); inside the near / far range (+128 / +132), x = 640 x / z, y = 448 y / z, accepted within [-640, 1280] x
// [-448, 896].
// Arguments: a0 f32[3], a1 out f32[2].
void sub_2D20A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f20{ctx, 20};
    // 0x002d21c4: the shared epilogue (v0 = 1 when projected)
    auto epilogue = [&] {
        charge(ctx, 7);
        ld(ra, sp, 0x30);
        lq(s1, sp, 0x20);
        lq(s0, sp, 0x10);
        lwc1(f20, sp, 0x0);
        sp = addiu(sp, 0x50);
    };
    // 0x002d20a0
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s1 = a0;                    // s1 = the world point
    s0 = a1;                    // s0 = the screen point out
    // The point in camera space (sp + 0x40: x, y, z) through the camera matrix (the camera object +32).
    jal(ctx, 0x2D20BCu, gen::fn_sub_198590_00198590);
    a2 = addiu(v0, 32);
    a0 = addiu(sp, 0x40);
    a1 = s1;
    jal(ctx, 0x2D20D0u, gen::fn_sub_4C6BE0_004c6be0);
    jal(ctx, 0x2D20D8u, gen::fn_sub_198590_00198590);
    lwc1(f20, v0, 128);         // the near distance
    jal(ctx, 0x2D20E4u, gen::fn_sub_198590_00198590);
    lwc1(f0, v0, 132);          // the far distance
    lwc1(f3, sp, 0x48);         // z
    c_le_s(f3, f20);
    if (!cond(ctx)) {
        // 0x002d2100
        charge(ctx, 3);
        c_lt_s(f3, f0);
        if (cond(ctx)) {
            // Between near and far: x = 640 * x / z, y = 448 * y / z, kept within the guard band
            // [-640, 1280] x [-448, 896] (one screen around the 640 x 448 view).
            // 0x002d2118
            charge(ctx, 19);
            lwc1(f0, sp, 0x40);
            div_s(f1, f0, f3);
            v0 = 0x44200000;        // 640.0f
            mtc1(v0, f0);
            mul_s(f2, f0, f1);      // f2 = x
            lwc1(f0, sp, 0x44);
            div_s(f1, f0, f3);
            v0 = 0x43E00000;        // 448.0f
            mtc1(v0, f0);
            mul_s(f1, f0, f1);      // f1 = y
            v0 = lui(0xC420);       // -640.0f
            mtc1(v0, f0);
            c_lt_s(f2, f0);
            if (!cond(ctx)) {
                // 0x002d2164
                charge(ctx, 6);
                v0 = 0x44A00000;    // 1280.0f
                mtc1(v0, f0);
                c_le_s(f2, f0);
                if (cond(ctx)) {
                    // 0x002d217c
                    charge(ctx, 6);
                    v0 = lui(0xC3E0);   // -448.0f
                    mtc1(v0, f0);
                    c_lt_s(f1, f0);
                    if (!cond(ctx)) {
                        // 0x002d2194
                        charge(ctx, 6);
                        v0 = 0x44600000;    // 896.0f
                        mtc1(v0, f0);
                        c_le_s(f1, f0);
                        if (cond(ctx)) {
                            // 0x002d21b8
                            charge(ctx, 3);
                            swc1(f2, s0, 0);
                            swc1(f1, s0, 4);
                            v0 = 1;
                            epilogue();
                            return;
                        }
                    }
                }
            }
            // 0x002d21ac: outside the guard band
            charge(ctx, 3);
            v0 = 0;
            epilogue();
            return;
        }
    }
    // 0x002d210c: in front of the near plane or beyond the far one
    charge(ctx, 3);
    v0 = 0;
    epilogue();
}

// 0x002D2470 sub_2D2470 -- 336 bytes; frame 0x60: ra sp+0x40, s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// Whether the segment a0-a1 passes within a distance f12 of the point a2 (ground plane).
// Arguments: a0 / a1 / a2, f12.
void sub_2D2470(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f12{ctx, 12}, f20{ctx, 20};
    // 0x002d2470
    enter(ctx, 42);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s0 = a2;
    mov_s(f20, f12);
    lwc1(f1, a0, 0);
    lwc1(f0, a1, 0);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x58);
    lwc1(f1, a0, 4);
    lwc1(f0, a1, 4);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x5C);
    a0 = addiu(sp, 0x58);
    a1 = a0;
    jal(ctx, 0x2D24C0u, gen::fn_sub_4C6B20_004c6b20);
    lwc1(f8, s2, 0);
    lwc1(f6, s0, 0);
    sub_s(f5, f6, f8);
    lwc1(f7, s2, 4);
    lwc1(f4, s0, 4);
    sub_s(f3, f4, f7);
    lwc1(f0, sp, 0x58);
    neg_s(f2, f0);
    lwc1(f1, sp, 0x5C);
    mula_s(f3, f2);
    mtc1(zero, f0);
    madd_s(f5, f5, f1);
    adda_s(f0, f6);
    msub_s(f3, f5, f1);
    adda_s(f0, f4);
    msub_s(f1, f5, f2);
    c_lt_s(f8, f3);
    if (!cond(ctx)) {
        // 0x002d2518
        charge(ctx, 4);
        lwc1(f0, s1, 0);
        c_le_s(f0, f3);
        if (!cond(ctx)) {
            goto L_002d2528;
        }
    L_002d2544:
        charge(ctx, 3);
        c_lt_s(f7, f1);
        if (!cond(ctx)) {
            // 0x002d2550
            charge(ctx, 4);
            lwc1(f0, s1, 4);
            c_le_s(f0, f1);
            if (!cond(ctx)) {
                goto L_002d2560;
            }
        L_002d2588:
            charge(ctx, 5);
            abs_s(f0, f5);
            c_lt_s(f0, f20);
            v0 = 1;
            if (!cond(ctx)) {
                // 0x002d259c
                charge(ctx, 1);
                v0 = 0;
            }
            // 0x002d25a0 (the shared epilogue, written out on this path)
            charge(ctx, 8);
            ld(ra, sp, 0x40);
            lq(s2, sp, 0x30);
            lq(s1, sp, 0x20);
            lq(s0, sp, 0x10);
            lwc1(f20, sp, 0x0);
            sp = addiu(sp, 0x60);
            return;
        }
    L_002d2560:
        charge(ctx, 3);
        c_le_s(f7, f1);
        if (cond(ctx)) {
            // 0x002d256c
            charge(ctx, 4);
            lwc1(f0, s1, 4);
            c_lt_s(f0, f1);
            if (!cond(ctx)) {
                goto L_002d2588;
            }
            goto L_002d257c;
        }
    L_002d257c:
        charge(ctx, 3);
        v0 = 0;
        // 0x002d25a0 (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(ra, sp, 0x40);
        lq(s2, sp, 0x30);
        lq(s1, sp, 0x20);
        lq(s0, sp, 0x10);
        lwc1(f20, sp, 0x0);
        sp = addiu(sp, 0x60);
        return;
    }
L_002d2528:
    charge(ctx, 3);
    c_le_s(f8, f3);
    if (!cond(ctx)) {
        goto L_002d257c;
    }
    // 0x002d2534
    charge(ctx, 4);
    lwc1(f0, s1, 0);
    c_lt_s(f0, f3);
    if (cond(ctx)) {
        goto L_002d257c;
    }
    goto L_002d2544;
}

// 0x002D25C0 sub_2D25C0 -- 964 bytes; frame 0xB0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlPathSegmentBlocked] Whether the segment between two path nodes is blocked: by an edge of any other unit box's
// corner node, or by a box containing an end point (boxes from gBtl +716, corners +8 at stride 304, links +1228).
// Arguments: a0 / a1 nodes.
void sub_2D25C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x002d25c0
    enter(ctx, 18);  // entry check point + this block's cycles
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
    s1 = a0;
    s0 = a1;
    s4 = 0;
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s5, v0, gbtl::kGridList);
    for (;;) {
        // 0x002d293c
        charge(ctx, 2);
        if (s5 != 0) {
            // 0x002d2944
            charge(ctx, 2);
            if (s4 == 0) {
                backedge(ctx);
                // 0x002d2608
                charge(ctx, 3);
                s3 = 0;
                for (;;) {
                    // 0x002d27a4
                    charge(ctx, 3);
                    v0 = slti(s3, 4);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x002d2614
                    charge(ctx, 12);
                    v0 = sll(s3, 3);
                    v0 = addu(v0, s3);
                    v0 = sll(v0, 1);
                    v0 = addu(v0, s3);
                    v0 = sll(v0, 4);
                    v0 = addu(s5, v0);
                    lwc1(f1, v0, 28);
                    mtc1(zero, f0);
                    c_le_s(f1, f0);
                    if (!cond(ctx)) {
                        // 0x002d2644
                        charge(ctx, 3);
                        s6 = addiu(v0, 8);
                        if (s6 == s1) {
                            goto L_002d27a0;
                        }
                        // 0x002d2650
                        charge(ctx, 2);
                        if (s6 == s0) {
                            goto L_002d27a0;
                        }
                        // 0x002d2658
                        charge(ctx, 19);
                        s2 = addiu(v0, 16);
                        lwc1(f1, v0, 16);
                        lwc1(f0, s1, path::kPoint);
                        sub_s(f0, f1, f0);
                        swc1(f0, sp, 0xA8);
                        s7 = addiu(v0, 20);
                        lwc1(f1, v0, 20);
                        lwc1(f0, s1, path::kPoint + 4);
                        sub_s(f0, f1, f0);
                        swc1(f0, sp, 0xAC);
                        a0 = addiu(sp, 0xA8);
                        jal(ctx, 0x2D2684u, gen::fn_sub_4C6AF0_004c6af0);
                        v0 = 0x3F800000;
                        mtc1(v0, f1);
                        c_lt_s(f0, f1);
                        if (cond(ctx)) {
                            goto L_002d27a0;
                        }
                        // 0x002d26a4
                        charge(ctx, 17);
                        lwc1(f1, s2, 0);
                        lwc1(f0, s0, path::kPoint);
                        sub_s(f0, f1, f0);
                        swc1(f0, sp, 0xA8);
                        lwc1(f1, s7, 0);
                        lwc1(f0, s0, path::kPoint + 4);
                        sub_s(f0, f1, f0);
                        swc1(f0, sp, 0xAC);
                        a0 = addiu(sp, 0xA8);
                        jal(ctx, 0x2D26C8u, gen::fn_sub_4C6AF0_004c6af0);
                        v0 = 0x3F800000;
                        mtc1(v0, f1);
                        c_lt_s(f0, f1);
                        if (cond(ctx)) {
                            goto L_002d27a0;
                        }
                        // 0x002d26e8
                        charge(ctx, 21);
                        v0 = sll(s3, 3);
                        v0 = addu(v0, s3);
                        v0 = sll(v0, 1);
                        v0 = addu(v0, s3);
                        v0 = sll(v0, 4);
                        v0 = addu(s5, v0);
                        lw(s2, v0, 24);
                        s7 = addiu(v0, 8);
                        a0 = s7;
                        a1 = s2;
                        a2 = addiu(s1, 8);
                        jal(ctx, 0x2D2714u, gen::fn_sub_2D2990_002d2990);
                        fp = v0;
                        a0 = s7;
                        a1 = s2;
                        a2 = addiu(s0, 8);
                        jal(ctx, 0x2D272Cu, gen::fn_sub_2D2990_002d2990);
                        if (fp == v0) {
                            // 0x002d2788
                            charge(ctx, 1);
                            v0 = 0;
                        } else {
                            // 0x002d273c
                            charge(ctx, 13);
                            a0 = addiu(s1, 8);
                            a1 = addiu(s0, 8);
                            a2 = s6;
                            jal(ctx, 0x2D2748u, gen::fn_sub_2D2990_002d2990);
                            s6 = v0;
                            a0 = addiu(s1, 8);
                            a1 = addiu(s0, 8);
                            a2 = s2;
                            jal(ctx, 0x2D2760u, gen::fn_sub_2D2990_002d2990);
                            if (s6 == v0) {
                                // 0x002d277c
                                charge(ctx, 3);
                                v0 = 0;
                            } else {
                                // 0x002d2770
                                charge(ctx, 3);
                                v0 = 1;
                            }
                        }
                        // 0x002d278c
                        charge(ctx, 2);
                        if (v0 == 0) {
                            goto L_002d27a0;
                        }
                        goto L_002d2794_13;
                    }
                L_002d27a0:
                    charge(ctx, 1);
                    s3 = addiu(s3, 1);
                }
            L_002d27b0:
                charge(ctx, 2);
                if (s4 == 0) {
                    // 0x002d27b8
                    charge(ctx, 5);
                    lwc1(f2, s1, path::kPoint);
                    lwc1(f3, s5, 8);
                    c_lt_s(f3, f2);
                    if (cond(ctx)) {
                        // 0x002d27cc
                        charge(ctx, 5);
                        lwc1(f1, s1, path::kPoint + 4);
                        lwc1(f0, s5, 12);
                        c_lt_s(f0, f1);
                        if (!cond(ctx)) {
                            goto L_002d2800;
                        }
                        // 0x002d27e0
                        charge(ctx, 4);
                        lwc1(f0, s5, 616);
                        c_le_s(f0, f2);
                        if (cond(ctx)) {
                            goto L_002d2800;
                        }
                        // 0x002d27f0
                        charge(ctx, 4);
                        lwc1(f0, s5, 620);
                        c_le_s(f0, f1);
                        if (cond(ctx)) {
                            goto L_002d2800;
                        }
                        goto L_002d2938;
                    }
                L_002d2800:
                    charge(ctx, 4);
                    lwc1(f2, s0, path::kPoint);
                    c_lt_s(f3, f2);
                    if (cond(ctx)) {
                        // 0x002d2810
                        charge(ctx, 5);
                        lwc1(f1, s0, path::kPoint + 4);
                        lwc1(f0, s5, 12);
                        c_lt_s(f0, f1);
                        if (!cond(ctx)) {
                            goto L_002d2844;
                        }
                        // 0x002d2824
                        charge(ctx, 4);
                        lwc1(f0, s5, 616);
                        c_le_s(f0, f2);
                        if (cond(ctx)) {
                            goto L_002d2844;
                        }
                        // 0x002d2834
                        charge(ctx, 4);
                        lwc1(f0, s5, 620);
                        c_le_s(f0, f1);
                        if (cond(ctx)) {
                            goto L_002d2844;
                        }
                        goto L_002d2938;
                    }
                L_002d2844:
                    charge(ctx, 3);
                    s2 = 0;
                    for (;;) {
                        // 0x002d292c
                        charge(ctx, 3);
                        v0 = slti(s2, 4);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x002d2850
                        charge(ctx, 29);
                        v0 = addiu(s2, 1);
                        v1 = v0 & 0x3;
                        v0 = sll(v1, 3);
                        v0 = addu(v0, v1);
                        v0 = sll(v0, 1);
                        v0 = addu(v0, v1);
                        v0 = sll(v0, 4);
                        v0 = addu(s5, v0);
                        s3 = addiu(v0, 8);
                        v0 = sll(s2, 3);
                        v0 = addu(v0, s2);
                        v0 = sll(v0, 1);
                        v0 = addu(v0, s2);
                        v0 = sll(v0, 4);
                        v0 = addu(s5, v0);
                        s6 = addiu(v0, 8);
                        a0 = s6;
                        a1 = s3;
                        a2 = addiu(s1, 8);
                        jal(ctx, 0x2D289Cu, gen::fn_sub_2D2990_002d2990);
                        s7 = v0;
                        a0 = s6;
                        a1 = s3;
                        a2 = addiu(s0, 8);
                        jal(ctx, 0x2D28B4u, gen::fn_sub_2D2990_002d2990);
                        if (s7 == v0) {
                            // 0x002d2910
                            charge(ctx, 1);
                            v0 = 0;
                        } else {
                            // 0x002d28c4
                            charge(ctx, 13);
                            a0 = addiu(s1, 8);
                            a1 = addiu(s0, 8);
                            a2 = s6;
                            jal(ctx, 0x2D28D0u, gen::fn_sub_2D2990_002d2990);
                            s6 = v0;
                            a0 = addiu(s1, 8);
                            a1 = addiu(s0, 8);
                            a2 = s3;
                            jal(ctx, 0x2D28E8u, gen::fn_sub_2D2990_002d2990);
                            if (s6 == v0) {
                                // 0x002d2904
                                charge(ctx, 3);
                                v0 = 0;
                            } else {
                                // 0x002d28f8
                                charge(ctx, 3);
                                v0 = 1;
                            }
                        }
                        // 0x002d2914
                        charge(ctx, 2);
                        if (v0 != 0) {
                            goto L_002d291c_32;
                        }
                        // 0x002d2928
                        charge(ctx, 1);
                        s2 = addiu(s2, 1);
                    }
                }
            L_002d2938:
                charge(ctx, 1);
                lw(s5, s5, 1228);
                continue;
            }
        }
        break;
    }
    // 0x002d294c (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0xB0);
    return;
L_002d2794_13:
    charge(ctx, 3);
    s4 = 1;
    goto L_002d27b0;
L_002d291c_32:
    charge(ctx, 3);
    s4 = 1;
    goto L_002d2938;
}

// 0x002D2A00 sub_2D2A00 -- 520 bytes; frame 0x60: ra sp+0x50, s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// Whether any unit in the battle blocks the line between two units (sub_2D2990 / sub_2D2470).
// Arguments: a0 / a1 btlUnit.
void sub_2D2A00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f20{ctx, 20};
    // 0x002d2a00
    enter(ctx, 14);  // entry check point + this block's cycles
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
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s1, v0, gbtl::kGridList);
    for (;;) {
        // 0x002d2bd8
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002d2a38
        charge(ctx, 5);
        lwc1(f2, s3, 0);
        lwc1(f3, s1, 8);
        c_lt_s(f3, f2);
        if (cond(ctx)) {
            // 0x002d2a4c
            charge(ctx, 5);
            lwc1(f1, s3, unit4::kPos);
            lwc1(f0, s1, 12);
            c_lt_s(f0, f1);
            if (!cond(ctx)) {
                goto L_002d2a80;
            }
            // 0x002d2a60
            charge(ctx, 4);
            lwc1(f0, s1, 616);
            c_le_s(f0, f2);
            if (cond(ctx)) {
                goto L_002d2a80;
            }
            // 0x002d2a70
            charge(ctx, 4);
            lwc1(f0, s1, 620);
            c_le_s(f0, f1);
            if (cond(ctx)) {
                goto L_002d2a80;
            }
        L_002d2bd4:
            charge(ctx, 1);
            lw(s1, s1, 1228);
            continue;
        }
    L_002d2a80:
        charge(ctx, 4);
        lwc1(f2, s2, 0);
        c_lt_s(f3, f2);
        if (cond(ctx)) {
            // 0x002d2a90
            charge(ctx, 5);
            lwc1(f1, s2, unit4::kPos);
            lwc1(f0, s1, 12);
            c_lt_s(f0, f1);
            if (!cond(ctx)) {
                goto L_002d2ac4;
            }
            // 0x002d2aa4
            charge(ctx, 4);
            lwc1(f0, s1, 616);
            c_le_s(f0, f2);
            if (cond(ctx)) {
                goto L_002d2ac4;
            }
            // 0x002d2ab4
            charge(ctx, 4);
            lwc1(f0, s1, 620);
            c_le_s(f0, f1);
            if (!cond(ctx)) {
                goto L_002d2bd4;
            }
            goto L_002d2ac4;
        }
    L_002d2ac4:
        charge(ctx, 3);
        s0 = 0;
        for (;;) {
            // 0x002d2bc8
            charge(ctx, 3);
            v0 = slti(s0, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002d2ad0
            charge(ctx, 27);
            v0 = addiu(s0, 1);
            v1 = v0 & 0x3;
            v0 = sll(v1, 3);
            v0 = addu(v0, v1);
            v0 = sll(v0, 1);
            v0 = addu(v0, v1);
            v0 = sll(v0, 4);
            v0 = addu(s1, v0);
            t0 = addiu(v0, 8);
            v0 = sll(s0, 3);
            v0 = addu(v0, s0);
            v0 = sll(v0, 1);
            v0 = addu(v0, s0);
            v0 = sll(v0, 4);
            v0 = addu(s1, v0);
            a3 = addiu(v0, 8);
            a0 = a3;
            a1 = t0;
            a2 = s3;
            jal(ctx, 0x2D2B1Cu, gen::fn_sub_2D2990_002d2990);
            v1 = v0;
            a2 = s2;
            jal(ctx, 0x2D2B2Cu, gen::fn_sub_2D2990_002d2990);
            if (v1 == v0) {
                // 0x002d2b80
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x002d2b3c
                charge(ctx, 11);
                a0 = s3;
                a1 = s2;
                a2 = a3;
                jal(ctx, 0x2D2B48u, gen::fn_sub_2D2990_002d2990);
                v1 = v0;
                a2 = t0;
                jal(ctx, 0x2D2B58u, gen::fn_sub_2D2990_002d2990);
                if (v1 == v0) {
                    // 0x002d2b74
                    charge(ctx, 3);
                    v0 = 0;
                } else {
                    // 0x002d2b68
                    charge(ctx, 3);
                    v0 = 1;
                }
            }
            // 0x002d2b84
            charge(ctx, 2);
            if (v0 != 0) {
                goto L_002d2b8c_16;
            }
            // 0x002d2b98
            charge(ctx, 8);
            a0 = s3;
            a1 = s2;
            a2 = a3;
            mov_s(f12, f20);
            jal(ctx, 0x2D2BA8u, gen::fn_sub_2D2470_002d2470);
            if (v0 != 0) {
                goto L_002d2bb8_18;
            }
            // 0x002d2bc4
            charge(ctx, 1);
            s0 = addiu(s0, 1);
        }
        goto L_002d2bd4;
    }
    // 0x002d2be0
    charge(ctx, 1);
    v0 = 0;
    // 0x002d2be4 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
L_002d2b8c_16:
    charge(ctx, 3);
    v0 = 1;
    // 0x002d2be4 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
L_002d2bb8_18:
    charge(ctx, 3);
    v0 = 1;
    // 0x002d2be4 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x002D2C10 sub_2D2C10 -- 712 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Whether two nodes see each other across the box edges (sub_2D2EE0 side tests), the target node's own box excepted.
// Arguments: a0 / a1 nodes.
void sub_2D2C10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x002d2c10
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
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
    lw(v0, a1, 16);
    if (v0 != s4) {
        // 0x002d2c54
        charge(ctx, 4);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(s2, v0, gbtl::kGridList);
        for (;;) {
            // 0x002d2d7c
            charge(ctx, 2);
            if (s2 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002d2c64
            charge(ctx, 3);
            s1 = 0;
            for (;;) {
                // 0x002d2d6c
                charge(ctx, 3);
                v0 = slti(s1, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x002d2c70
                charge(ctx, 11);
                v0 = addiu(s1, 1);
                v1 = v0 & 0x3;
                v0 = sll(s1, 3);
                v0 = addu(v0, s1);
                v0 = sll(v0, 1);
                v0 = addu(v0, s1);
                v0 = sll(v0, 4);
                v0 = addu(s2, v0);
                s0 = addiu(v0, 8);
                if (s0 != s4) {
                    // 0x002d2c9c
                    charge(ctx, 2);
                    if (s0 == s3) {
                        goto L_002d2d68;
                    }
                    // 0x002d2ca4
                    charge(ctx, 9);
                    v0 = sll(v1, 3);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 1);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 4);
                    v0 = addu(s2, v0);
                    s5 = addiu(v0, 8);
                    if (s5 == s4) {
                        goto L_002d2d68;
                    }
                    // 0x002d2cc8
                    charge(ctx, 2);
                    if (s5 == s3) {
                        goto L_002d2d68;
                    }
                    // 0x002d2cd0
                    charge(ctx, 13);
                    a0 = s0;
                    a1 = s5;
                    a2 = s4;
                    jal(ctx, 0x2D2CDCu, gen::fn_sub_2D2EE0_002d2ee0);
                    s6 = v0;
                    a0 = s0;
                    a1 = s5;
                    a2 = s3;
                    jal(ctx, 0x2D2CF4u, gen::fn_sub_2D2EE0_002d2ee0);
                    if (s6 == v0) {
                        // 0x002d2d50
                        charge(ctx, 1);
                        v0 = 0;
                    } else {
                        // 0x002d2d04
                        charge(ctx, 13);
                        a0 = s4;
                        a1 = s3;
                        a2 = s0;
                        jal(ctx, 0x2D2D10u, gen::fn_sub_2D2EE0_002d2ee0);
                        s0 = v0;
                        a0 = s4;
                        a1 = s3;
                        a2 = s5;
                        jal(ctx, 0x2D2D28u, gen::fn_sub_2D2EE0_002d2ee0);
                        if (s0 == v0) {
                            // 0x002d2d44
                            charge(ctx, 3);
                            v0 = 0;
                        } else {
                            // 0x002d2d38
                            charge(ctx, 3);
                            v0 = 1;
                        }
                    }
                    // 0x002d2d54
                    charge(ctx, 2);
                    if (v0 == 0) {
                        goto L_002d2d68;
                    }
                    goto L_002d2d5c_14;
                }
            L_002d2d68:
                charge(ctx, 1);
                s1 = addiu(s1, 1);
            }
            // 0x002d2d78
            charge(ctx, 1);
            lw(s2, s2, 1228);
        }
        // 0x002d2d84
        charge(ctx, 4);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(s1, v0, gbtl::kGridList);
        for (;;) {
            // 0x002d2ea0
            charge(ctx, 2);
            if (s1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002d2d94
            charge(ctx, 3);
            s0 = 0;
            for (;;) {
                // 0x002d2e90
                charge(ctx, 3);
                v0 = slti(s0, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x002d2da0
                charge(ctx, 9);
                v0 = sll(s0, 3);
                v0 = addu(v0, s0);
                v0 = sll(v0, 1);
                v0 = addu(v0, s0);
                v0 = sll(v0, 4);
                v0 = addu(s1, v0);
                s2 = addiu(v0, 8);
                if (s2 == s4) {
                    goto L_002d2dc4_22;
                }
                // 0x002d2dd0
                charge(ctx, 6);
                lwc1(f1, v0, 28);
                mtc1(zero, f0);
                c_le_s(f1, f0);
                if (!cond(ctx)) {
                    // 0x002d2de8
                    charge(ctx, 3);
                    lw(s5, v0, 24);
                    if (s5 == 0) {
                        goto L_002d2e8c;
                    }
                    // 0x002d2df4
                    charge(ctx, 13);
                    a0 = s2;
                    a1 = s5;
                    a2 = s4;
                    jal(ctx, 0x2D2E00u, gen::fn_sub_2D2EE0_002d2ee0);
                    s6 = v0;
                    a0 = s2;
                    a1 = s5;
                    a2 = s3;
                    jal(ctx, 0x2D2E18u, gen::fn_sub_2D2EE0_002d2ee0);
                    if (s6 == v0) {
                        // 0x002d2e74
                        charge(ctx, 1);
                        v0 = 0;
                    } else {
                        // 0x002d2e28
                        charge(ctx, 13);
                        a0 = s4;
                        a1 = s3;
                        a2 = s2;
                        jal(ctx, 0x2D2E34u, gen::fn_sub_2D2EE0_002d2ee0);
                        s2 = v0;
                        a0 = s4;
                        a1 = s3;
                        a2 = s5;
                        jal(ctx, 0x2D2E4Cu, gen::fn_sub_2D2EE0_002d2ee0);
                        if (s2 == v0) {
                            // 0x002d2e68
                            charge(ctx, 3);
                            v0 = 0;
                        } else {
                            // 0x002d2e5c
                            charge(ctx, 3);
                            v0 = 1;
                        }
                    }
                    // 0x002d2e78
                    charge(ctx, 2);
                    if (v0 == 0) {
                        goto L_002d2e8c;
                    }
                    goto L_002d2e80_31;
                }
            L_002d2e8c:
                charge(ctx, 1);
                s0 = addiu(s0, 1);
            }
            // 0x002d2e9c
            charge(ctx, 1);
            lw(s1, s1, 1228);
        }
        // 0x002d2ea8
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x002d2c48
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x002d2eac (the shared epilogue, written out on this path)
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
L_002d2d5c_14:
    charge(ctx, 3);
    v0 = 1;
    // 0x002d2eac (the shared epilogue, written out on this path)
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
L_002d2dc4_22:
    charge(ctx, 3);
    v0 = 0;
    // 0x002d2eac (the shared epilogue, written out on this path)
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
L_002d2e80_31:
    charge(ctx, 3);
    v0 = 1;
    // 0x002d2eac (the shared epilogue, written out on this path)
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

// 0x002D2EE0 sub_2D2EE0 -- 108 bytes; leaf frame (no stack)
// [btlPathSide] Side of a point relative to a directed edge on the ground plane: -1 left, 1 right / on.
// Arguments: a0 / a1 edge, a2 point.
void sub_2D2EE0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4};
    // 0x002d2ee0
    enter(ctx, 16);  // entry check point + this block's cycles
    lwc1(f1, a0, 0);
    lwc1(f4, a0, 4);
    lwc1(f0, a1, 4);
    sub_s(f3, f0, f4);
    lwc1(f0, a2, 0);
    sub_s(f2, f0, f1);
    lwc1(f0, a1, 0);
    sub_s(f1, f0, f1);
    lwc1(f0, a2, 4);
    sub_s(f0, f0, f4);
    mula_s(f1, f0);
    mtc1(zero, f0);
    msub_s(f1, f3, f2);
    c_lt_s(f1, f0);
    if (cond(ctx)) {
        // 0x002d2f2c
        charge(ctx, 4);
        c_lt_s(f1, f0);
        v0 = 1;
        if (!cond(ctx)) {
            // 0x002d2f3c
            charge(ctx, 1);
            v0 = 0;
        }
        // 0x002d2f40
        charge(ctx, 1);
        v0 = subu(0, v0);
    } else {
        // 0x002d2f20
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x002d2f44 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x002D2F50 sub_2D2F50 -- 852 bytes; frame 0x90: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [btlPathBuildNeighbours] Builds a node's neighbour list: every visible corner node with clearance >= f12, the field
// corners (gBtl +720), the start (+1936) and goal (+2240) nodes, with their distances (+48 nodes, +176 distances, 0
// terminated); returns the count.
// Arguments: a0 node, f12 clearance.
void sub_2D2F50(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f20{ctx, 20};
    // 0x002d2f50
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s0 = a0;
    mov_s(f20, f12);
    s3 = 0;
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s4, v0, gbtl::kGridList);
    for (;;) {
        // 0x002d3080
        charge(ctx, 2);
        if (s4 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002d2f8c
        charge(ctx, 3);
        s2 = 0;
        for (;;) {
            // 0x002d306c
            charge(ctx, 4);
            v0 = s2 & 0xFFFF;
            v0 = slti(v0, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002d2f98
            charge(ctx, 10);
            v1 = s2 & 0xFFFF;
            v0 = sll(v1, 3);
            v0 = addu(v0, v1);
            v0 = sll(v0, 1);
            v0 = addu(v0, v1);
            v0 = sll(v0, 4);
            v0 = addu(s4, v0);
            s1 = addiu(v0, 8);
            if (s1 != s0) {
                // 0x002d2fc0
                charge(ctx, 6);
                lwc1(f1, v0, 28);
                mtc1(zero, f0);
                c_le_s(f1, f0);
                if (!cond(ctx)) {
                    // 0x002d2fd8
                    charge(ctx, 4);
                    lwc1(f0, v0, 32);
                    c_lt_s(f0, f20);
                    if (!cond(ctx)) {
                        // 0x002d2fe8
                        charge(ctx, 6);
                        a0 = s0;
                        a1 = s1;
                        jal(ctx, 0x2D2FF0u, gen::fn_sub_2D25C0_002d25c0);
                        if (v0 == 0) {
                            // 0x002d3000
                            charge(ctx, 25);
                            v1 = s2 & 0xFFFF;
                            v0 = sll(v1, 3);
                            v0 = addu(v0, v1);
                            v0 = sll(v0, 1);
                            v0 = addu(v0, v1);
                            v0 = sll(v0, 4);
                            v0 = addu(s4, v0);
                            lwc1(f1, s0, path::kPoint);
                            lwc1(f0, v0, 16);
                            sub_s(f0, f1, f0);
                            swc1(f0, sp, 0x88);
                            lwc1(f1, s0, path::kPoint + 4);
                            lwc1(f0, v0, 20);
                            sub_s(f0, f1, f0);
                            swc1(f0, sp, 0x8C);
                            a0 = addiu(sp, 0x88);
                            jal(ctx, 0x2D3040u, gen::fn_sub_4C6AF0_004c6af0);
                            v0 = s3 & 0xFFFF;
                            v0 = sll(v0, 2);
                            v0 = addu(s0, v0);
                            swc1(f0, v0, 176);
                            sw(s1, v0, 48);
                            v0 = addiu(s3, 1);
                            s3 = v0 & 0xFFFF;
                        }
                    }
                }
            }
            // 0x002d3064
            charge(ctx, 2);
            v0 = addiu(s2, 1);
            s2 = v0 & 0xFFFF;
        }
        // 0x002d307c
        charge(ctx, 1);
        lw(s4, s4, 1228);
    }
    // 0x002d3088
    charge(ctx, 3);
    s2 = 0;
    for (;;) {
        // 0x002d3168
        charge(ctx, 4);
        v0 = s2 & 0xFFFF;
        v0 = slti(v0, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002d3094
        charge(ctx, 11);
        v1 = s2 & 0xFFFF;
        v0 = sll(v1, 3);
        v0 = addu(v0, v1);
        v0 = sll(v0, 1);
        v0 = addu(v0, v1);
        v1 = sll(v0, 4);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        v0 = addu(v0, v1);
        a1 = addiu(v0, 720);
        if (a1 != s0) {
            // 0x002d30c0
            charge(ctx, 6);
            lwc1(f1, v0, 740);
            mtc1(zero, f0);
            c_le_s(f1, f0);
            if (!cond(ctx)) {
                // 0x002d30d8
                charge(ctx, 5);
                a0 = s0;
                jal(ctx, 0x2D30DCu, gen::fn_sub_2D25C0_002d25c0);
                if (v0 == 0) {
                    // 0x002d30ec
                    charge(ctx, 29);
                    v1 = s2 & 0xFFFF;
                    v0 = sll(v1, 3);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 1);
                    v0 = addu(v0, v1);
                    s1 = sll(v0, 4);
                    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                    v0 = addu(v0, s1);
                    lwc1(f1, s0, path::kPoint);
                    lwc1(f0, v0, 728);
                    sub_s(f0, f1, f0);
                    swc1(f0, sp, 0x80);
                    lwc1(f1, s0, path::kPoint + 4);
                    lwc1(f0, v0, 732);
                    sub_s(f0, f1, f0);
                    swc1(f0, sp, 0x84);
                    a0 = addiu(sp, 0x80);
                    jal(ctx, 0x2D3130u, gen::fn_sub_4C6AF0_004c6af0);
                    v0 = s3 & 0xFFFF;
                    v0 = sll(v0, 2);
                    v1 = addu(s0, v0);
                    swc1(f0, v1, 176);
                    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                    v0 = addu(v0, s1);
                    v0 = addiu(v0, 720);
                    sw(v0, v1, 48);
                    v0 = addiu(s3, 1);
                    s3 = v0 & 0xFFFF;
                }
            }
        }
        // 0x002d3160
        charge(ctx, 2);
        v0 = addiu(s2, 1);
        s2 = v0 & 0xFFFF;
    }
    // 0x002d3178
    charge(ctx, 4);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    a1 = addiu(v0, 1936);
    if (a1 != s0) {
        // 0x002d3188
        charge(ctx, 5);
        a0 = s0;
        jal(ctx, 0x2D318Cu, gen::fn_sub_2D25C0_002d25c0);
        if (v0 == 0) {
            // 0x002d319c
            charge(ctx, 21);
            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
            lwc1(f1, s0, path::kPoint);
            lwc1(f0, v0, gbtl4::kPathStart + 8);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x78);
            lwc1(f1, s0, path::kPoint + 4);
            lwc1(f0, v0, gbtl4::kPathStart + 12);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x7C);
            a0 = addiu(sp, 0x78);
            jal(ctx, 0x2D31C4u, gen::fn_sub_4C6AF0_004c6af0);
            v0 = s3 & 0xFFFF;
            v0 = sll(v0, 2);
            v1 = addu(v0, s0);
            swc1(f0, v1, 176);
            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
            v0 = addiu(v0, 1936);
            sw(v0, v1, 48);
            v0 = addiu(s3, 1);
            s3 = v0 & 0xFFFF;
        }
    }
    // 0x002d31f0
    charge(ctx, 4);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    a1 = addiu(v0, 2240);
    if (a1 != s0) {
        // 0x002d3200
        charge(ctx, 5);
        a0 = s0;
        jal(ctx, 0x2D3204u, gen::fn_sub_2D25C0_002d25c0);
        if (v0 == 0) {
            // 0x002d3214
            charge(ctx, 21);
            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
            lwc1(f1, s0, path::kPoint);
            lwc1(f0, v0, gbtl4::kPathGoal + 8);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x70);
            lwc1(f1, s0, path::kPoint + 4);
            lwc1(f0, v0, gbtl4::kPathGoal + 12);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x74);
            a0 = addiu(sp, 0x70);
            jal(ctx, 0x2D323Cu, gen::fn_sub_4C6AF0_004c6af0);
            v0 = s3 & 0xFFFF;
            v0 = sll(v0, 2);
            v1 = addu(v0, s0);
            swc1(f0, v1, 176);
            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
            v0 = addiu(v0, 2240);
            sw(v0, v1, 48);
            v0 = addiu(s3, 1);
            s3 = v0 & 0xFFFF;
        }
    }
    // 0x002d3268 (the shared epilogue, written out on this path)
    charge(ctx, 15);
    v0 = s3 & 0xFFFF;
    v0 = sll(v0, 2);
    v0 = addu(v0, s0);
    sw(zero, v0, 48);
    v0 = s3;
    ld(ra, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x002D32B0 sub_2D32B0 -- 2752 bytes; frame 0x100: ra sp+0xA0, s7 sp+0x90 (sq), s6 sp+0x80 (sq), s5 sp+0x70 (sq), s4 sp+0x60 (sq), s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f26 sp+0x18, f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [btlPathBuildGraph] Builds the path graph: the corner nodes of every unit box (from the grid cells, grown by the
// clearance) and the field corners, then their neighbour lists.
// Arguments: f12 clearance.
void sub_2D32B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25}, f26{ctx, 26};
    // 0x002d32b0
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x100);
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
    mov_s(f26, f12);
    a2 = 0;
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v0, v0, gbtl::kGridList);
    a1 = 1;
    for (;;) {
        // 0x002d344c
        charge(ctx, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002d3310
        charge(ctx, 2);
        if (a2 != 0) {
            // 0x002d3360
            charge(ctx, 6);
            lh(t0, v0, 0);
            lh(a3, v0, 2);
            lh(v1, sp, 0xC0);
            v1 = slt(v1, t0);
            if (v1 == 0) {
                // 0x002d3378
                charge(ctx, 6);
                lh(a0, sp, 0xC2);
                v1 = dsll32(a3, 16);
                v1 = dsra32(v1, 16);
                v1 = slt(a0, v1);
                if (v1 == 0) {
                    // 0x002d3390
                    charge(ctx, 4);
                    sh(t0, sp, 0xC0);
                    sh(a3, sp, 0xC2);
                    lwc1(f0, v0, 4);
                    swc1(f0, sp, 0xB0);
                }
            }
            // 0x002d33a0
            charge(ctx, 4);
            lh(v1, sp, 0xC4);
            at = slt(t0, v1);
            if (at == 0) {
                // 0x002d33b0
                charge(ctx, 6);
                lh(a0, sp, 0xC6);
                v1 = dsll32(a3, 16);
                v1 = dsra32(v1, 16);
                v1 = slt(a0, v1);
                if (v1 == 0) {
                    // 0x002d33c8
                    charge(ctx, 4);
                    sh(t0, sp, 0xC4);
                    sh(a3, sp, 0xC6);
                    lwc1(f0, v0, 4);
                    swc1(f0, sp, 0xB4);
                }
            }
            // 0x002d33d8
            charge(ctx, 4);
            lh(v1, sp, 0xC8);
            at = slt(t0, v1);
            if (at == 0) {
                // 0x002d33e8
                charge(ctx, 6);
                lh(a0, sp, 0xCA);
                v1 = dsll32(a3, 16);
                v1 = dsra32(v1, 16);
                at = slt(v1, a0);
                if (at == 0) {
                    // 0x002d3400
                    charge(ctx, 4);
                    sh(t0, sp, 0xC8);
                    sh(a3, sp, 0xCA);
                    lwc1(f0, v0, 4);
                    swc1(f0, sp, 0xB8);
                }
            }
            // 0x002d3410
            charge(ctx, 4);
            lh(v1, sp, 0xCC);
            v1 = slt(v1, t0);
            if (v1 == 0) {
                // 0x002d3420
                charge(ctx, 6);
                lh(a0, sp, 0xCE);
                v1 = dsll32(a3, 16);
                v1 = dsra32(v1, 16);
                at = slt(v1, a0);
                if (at == 0) {
                    // 0x002d3438
                    charge(ctx, 4);
                    sh(t0, sp, 0xCC);
                    sh(a3, sp, 0xCE);
                    lwc1(f0, v0, 4);
                    swc1(f0, sp, 0xBC);
                }
            }
        } else {
            // 0x002d3318
            charge(ctx, 18);
            lh(v1, v0, 0);
            sh(v1, sp, 0xCC);
            sh(v1, sp, 0xC8);
            sh(v1, sp, 0xC4);
            sh(v1, sp, 0xC0);
            lh(v1, v0, 2);
            sh(v1, sp, 0xCE);
            sh(v1, sp, 0xCA);
            sh(v1, sp, 0xC6);
            sh(v1, sp, 0xC2);
            lwc1(f0, v0, 4);
            swc1(f0, sp, 0xBC);
            swc1(f0, sp, 0xB8);
            swc1(f0, sp, 0xB4);
            swc1(f0, sp, 0xB0);
            a2 = a1;
        }
        // 0x002d3448
        charge(ctx, 1);
        lw(v0, v0, 1228);
    }
    // 0x002d3454
    charge(ctx, 9);
    t1 = 0;
    v1 = 1;
    a0 = 2;
    v0 = 0x43FA0000;
    mtc1(v0, f1);
    a2 = 25;
    a1 = 3;
    for (;;) {
        // 0x002d3688
        charge(ctx, 3);
        v0 = slti(t1, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002d3478
        charge(ctx, 15);
        v0 = sll(t1, 2);
        v0 = addu(v0, sp);
        lwc1(f0, v0, 176);
        add_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(t2, f0);
        div(t2, a2);
        mflo(v0);
        t3 = dsll32(v0, 16);
        t3 = dsra32(t3, 16);
        div(t2, a2);
        mfhi(v0);
        if (v0 != 0) {
            // 0x002d34b4
            charge(ctx, 3);
            v0 = addiu(t3, 1);
            t3 = dsll32(v0, 16);
            t3 = dsra32(t3, 16);
        }
        // 0x002d34c0
        charge(ctx, 2);
        if (t1 == a1) {
            // 0x002d35c8
            charge(ctx, 15);
            v0 = sll(t1, 2);
            v0 = addu(v0, sp);
            t2 = addiu(v0, 192);
            a3 = dsll32(t3, 16);
            a3 = dsra32(a3, 16);
            lh(v0, t2, 0);
            v0 = subu(v0, a3);
            t0 = dsll32(v0, 16);
            t0 = dsra32(t0, 16);
            lh(v0, t2, 2);
            v0 = addu(a3, v0);
            a3 = dsll32(v0, 16);
            a3 = dsra32(a3, 16);
            if (i64(t0) < 0) {
                // 0x002d3604
                charge(ctx, 1);
                t0 = 0;
            }
        } else {
            // 0x002d34c8
            charge(ctx, 2);
            if (t1 == a0) {
                // 0x002d358c
                charge(ctx, 15);
                v0 = sll(t1, 2);
                v0 = addu(v0, sp);
                t2 = addiu(v0, 192);
                a3 = dsll32(t3, 16);
                a3 = dsra32(a3, 16);
                lh(v0, t2, 0);
                v0 = addu(a3, v0);
                t0 = dsll32(v0, 16);
                t0 = dsra32(t0, 16);
                lh(v0, t2, 2);
                v0 = addu(a3, v0);
                a3 = dsll32(v0, 16);
                a3 = dsra32(a3, 16);
            } else {
                // 0x002d34d0
                charge(ctx, 2);
                if (t1 == v1) {
                    // 0x002d3544
                    charge(ctx, 15);
                    v0 = sll(t1, 2);
                    v0 = addu(v0, sp);
                    t2 = addiu(v0, 192);
                    a3 = dsll32(t3, 16);
                    a3 = dsra32(a3, 16);
                    lh(v0, t2, 0);
                    v0 = addu(a3, v0);
                    t0 = dsll32(v0, 16);
                    t0 = dsra32(t0, 16);
                    lh(v0, t2, 2);
                    v0 = subu(v0, a3);
                    a3 = dsll32(v0, 16);
                    a3 = dsra32(a3, 16);
                    if (i64(a3) < 0) {
                        // 0x002d3580
                        charge(ctx, 3);
                        a3 = 0;
                    }
                } else {
                    // 0x002d34d8
                    charge(ctx, 2);
                    if (t1 == 0) {
                        // 0x002d34e8
                        charge(ctx, 15);
                        v0 = sll(t1, 2);
                        v0 = addu(v0, sp);
                        t2 = addiu(v0, 192);
                        a3 = dsll32(t3, 16);
                        a3 = dsra32(a3, 16);
                        lh(v0, t2, 0);
                        v0 = subu(v0, a3);
                        t0 = dsll32(v0, 16);
                        t0 = dsra32(t0, 16);
                        lh(v0, t2, 2);
                        v0 = subu(v0, a3);
                        a3 = dsll32(v0, 16);
                        a3 = dsra32(a3, 16);
                        if (i64(t0) < 0) {
                            // 0x002d3524
                            charge(ctx, 1);
                            t0 = 0;
                        }
                        // 0x002d3528
                        charge(ctx, 4);
                        v0 = dsll32(a3, 16);
                        v0 = dsra32(v0, 16);
                        if (i64(v0) < 0) {
                            // 0x002d3538
                            charge(ctx, 3);
                            a3 = 0;
                        }
                    } else {
                        // 0x002d34e0
                        charge(ctx, 2);
                    }
                }
            }
        }
        // 0x002d3608
        charge(ctx, 32);
        v0 = sll(t1, 3);
        v0 = addu(v0, t1);
        v0 = sll(v0, 1);
        v0 = addu(v0, t1);
        v0 = sll(v0, 4);
        t3 = dsll32(t0, 16);
        t3 = dsra32(t3, 16);
        t2 = sll(t3, 2);
        t3 = addu(t2, t3);
        t2 = sll(t3, 2);
        t2 = addu(t3, t2);
        t2 = addiu(t2, -1750);
        mtc1(t2, f0);
        cvt_s_w(f0, f0);
        lw(t2, gp, kGpBtl);  // gBtl 0x7CE3EC
        t2 = addu(t2, v0);
        swc1(f0, t2, 720);
        t3 = dsll32(a3, 16);
        t3 = dsra32(t3, 16);
        t2 = sll(t3, 2);
        t3 = addu(t2, t3);
        t2 = sll(t3, 2);
        t2 = addu(t3, t2);
        t2 = addiu(t2, -1750);
        mtc1(t2, f0);
        cvt_s_w(f0, f0);
        lw(t2, gp, kGpBtl);  // gBtl 0x7CE3EC
        v0 = addu(t2, v0);
        swc1(f0, v0, 724);
        t1 = addiu(t1, 1);
    }
    // 0x002d3694
    charge(ctx, 4);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s1, v0, gbtl::kGridList);
    for (;;) {
        // 0x002d3a2c
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002d36a4
        charge(ctx, 3);
        s0 = 0;
        for (;;) {
            // 0x002d3a1c
            charge(ctx, 3);
            v0 = slti(s0, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002d36b0
            charge(ctx, 23);
            s5 = 0;
            v0 = 7000;
            mtc1(v0, f0);
            cvt_s_w(f24, f0);
            v1 = sll(s0, 3);
            v0 = addu(v1, s0);
            v0 = sll(v0, 1);
            v0 = addu(v0, s0);
            v0 = sll(v0, 4);
            s2 = addu(s1, v0);
            lwc1(f1, s2, 8);
            lwc1(f0, s2, 12);
            swc1(f1, sp, 0xF8);
            swc1(f0, sp, 0xFC);
            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
            lw(s4, v0, gbtl::kGridList);
            lwc1(f21, sp, 0xFC);
            v0 = 0x690000;
            v0 = addiu(v0, 30912);  // &0x6978C0
            s6 = addu(v0, v1);
            for (;;) {
                // 0x002d3828
                charge(ctx, 2);
                if (s4 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x002d370c
                charge(ctx, 2);
                if (s1 != s4) {
                    // 0x002d3714
                    charge(ctx, 3);
                    s3 = 0;
                    for (;;) {
                        // 0x002d3818
                        charge(ctx, 3);
                        v0 = slti(s3, 4);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x002d3720
                        charge(ctx, 28);
                        v0 = sll(s3, 3);
                        v0 = addu(v0, s3);
                        v0 = sll(v0, 1);
                        v0 = addu(v0, s3);
                        v0 = sll(v0, 4);
                        s7 = addu(s4, v0);
                        lwc1(f1, s7, 8);
                        lwc1(f0, sp, 0xF8);
                        sub_s(f0, f1, f0);
                        swc1(f0, sp, 0xE8);
                        lwc1(f0, s7, 12);
                        sub_s(f0, f0, f21);
                        swc1(f0, sp, 0xEC);
                        a0 = addiu(sp, 0xF0);
                        a1 = addiu(sp, 0xE8);
                        jal(ctx, 0x2D375Cu, gen::fn_sub_4C6B20_004c6b20);
                        mov_s(f20, f0);
                        lwc1(f3, sp, 0xF0);
                        lwc1(f2, s6, 0);
                        lwc1(f1, sp, 0xF4);
                        lwc1(f0, s6, 4);
                        mula_s(f1, f0);
                        madd_s(f1, f3, f2);
                        lwc1(f0, gp, -32132);  // 0x7CAF6C
                        c_le_s(f1, f0);
                        if (!cond(ctx)) {
                            // 0x002d3790
                            charge(ctx, 3);
                            c_lt_s(f20, f24);
                            if (cond(ctx)) {
                                // 0x002d379c
                                charge(ctx, 7);
                                s7 = addiu(s7, 8);
                                a0 = addiu(s2, 8);
                                a1 = s7;
                                jal(ctx, 0x2D37A8u, gen::fn_sub_2D2C10_002d2c10);
                                if (v0 == 0) {
                                    // 0x002d37b8
                                    charge(ctx, 23);
                                    ld(v0, sp, 0xF0);
                                    sd(v0, sp, 0xE0);
                                    s5 = s7;
                                    mov_s(f24, f20);
                                    lh(v1, s4, 0);
                                    v0 = sll(v1, 2);
                                    v1 = addu(v0, v1);
                                    v0 = sll(v1, 2);
                                    v0 = addu(v1, v0);
                                    v0 = addiu(v0, -1750);
                                    mtc1(v0, f0);
                                    cvt_s_w(f23, f0);
                                    lh(v1, s4, 2);
                                    v0 = sll(v1, 2);
                                    v1 = addu(v0, v1);
                                    v0 = sll(v1, 2);
                                    v0 = addu(v1, v0);
                                    v0 = addiu(v0, -1750);
                                    mtc1(v0, f0);
                                    cvt_s_w(f22, f0);
                                    lwc1(f25, s4, 4);
                                }
                            }
                        }
                        // 0x002d3814
                        charge(ctx, 1);
                        s3 = addiu(s3, 1);
                    }
                }
                // 0x002d3824
                charge(ctx, 1);
                lw(s4, s4, 1228);
            }
            // 0x002d3830
            charge(ctx, 3);
            s3 = 0;
            for (;;) {
                // 0x002d3918
                charge(ctx, 3);
                v0 = slti(s3, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x002d383c
                charge(ctx, 29);
                lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                v0 = sll(s3, 3);
                v0 = addu(v0, s3);
                v0 = sll(v0, 1);
                v0 = addu(v0, s3);
                s4 = sll(v0, 4);
                v0 = addu(v1, s4);
                lwc1(f1, v0, 720);
                lwc1(f0, sp, 0xF8);
                sub_s(f0, f1, f0);
                swc1(f0, sp, 0xE8);
                lwc1(f0, v0, 724);
                sub_s(f0, f0, f21);
                swc1(f0, sp, 0xEC);
                a0 = addiu(sp, 0xF0);
                a1 = addiu(sp, 0xE8);
                jal(ctx, 0x2D387Cu, gen::fn_sub_4C6B20_004c6b20);
                mov_s(f20, f0);
                lwc1(f3, sp, 0xF0);
                lwc1(f2, s6, 0);
                lwc1(f1, sp, 0xF4);
                lwc1(f0, s6, 4);
                mula_s(f1, f0);
                madd_s(f1, f3, f2);
                lwc1(f0, gp, -32132);  // 0x7CAF6C
                c_le_s(f1, f0);
                if (!cond(ctx)) {
                    // 0x002d38b0
                    charge(ctx, 3);
                    c_lt_s(f20, f24);
                    if (cond(ctx)) {
                        // 0x002d38bc
                        charge(ctx, 8);
                        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                        v0 = addu(v0, s4);
                        a0 = addiu(s2, 8);
                        a1 = addiu(v0, 720);
                        jal(ctx, 0x2D38CCu, gen::fn_sub_2D2C10_002d2c10);
                        if (v0 == 0) {
                            // 0x002d38dc
                            charge(ctx, 14);
                            ld(v0, sp, 0xF0);
                            sd(v0, sp, 0xE0);
                            v0 = sll(s3, 3);
                            v0 = addu(v0, s3);
                            v0 = sll(v0, 1);
                            v0 = addu(v0, s3);
                            v1 = sll(v0, 4);
                            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                            v0 = addu(v0, v1);
                            s5 = addiu(v0, 720);
                            mov_s(f24, f20);
                            lwc1(f23, v0, 720);
                            lwc1(f22, v0, 724);
                            mtc1(zero, f25);
                        }
                    }
                }
                // 0x002d3914
                charge(ctx, 1);
                s3 = addiu(s3, 1);
            }
            // 0x002d3924
            charge(ctx, 2);
            if (s5 == 0) {
                // 0x002d3a10
                charge(ctx, 2);
                v0 = lui(0xBF80);
                sw(v0, s2, 28);
            } else {
                // 0x002d392c
                charge(ctx, 57);
                v0 = 0x3F000000;
                mtc1(v0, f0);
                mul_s(f2, f0, f24);
                lwc1(f0, sp, 0xE0);
                mul_s(f1, f0, f2);
                swc1(f1, sp, 0xE0);
                lwc1(f0, sp, 0xE4);
                mul_s(f0, f0, f2);
                swc1(f0, sp, 0xE4);
                v0 = sll(s0, 3);
                v0 = addu(v0, s0);
                v0 = sll(v0, 1);
                v0 = addu(v0, s0);
                v0 = sll(v0, 4);
                s2 = addu(s1, v0);
                lwc1(f0, sp, 0xF8);
                add_s(f0, f0, f1);
                swc1(f0, s2, 16);
                lwc1(f0, sp, 0xE4);
                add_s(f0, f21, f0);
                swc1(f0, s2, 20);
                sw(s5, s2, 24);
                swc1(f24, s2, 28);
                lh(v1, s1, 0);
                v0 = sll(v1, 2);
                v1 = addu(v0, v1);
                v0 = sll(v1, 2);
                v0 = addu(v1, v0);
                v0 = addiu(v0, -1750);
                mtc1(v0, f0);
                cvt_s_w(f2, f0);
                swc1(f2, sp, 0xE8);
                lh(v1, s1, 2);
                v0 = sll(v1, 2);
                v1 = addu(v0, v1);
                v0 = sll(v1, 2);
                v0 = addu(v1, v0);
                v0 = addiu(v0, -1750);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                swc1(f1, sp, 0xEC);
                sub_s(f0, f2, f23);
                swc1(f0, sp, 0xE8);
                sub_s(f0, f1, f22);
                swc1(f0, sp, 0xEC);
                a0 = addiu(sp, 0xE8);
                jal(ctx, 0x2D39F0u, gen::fn_sub_4C6AF0_004c6af0);
                lwc1(f1, s1, 4);
                add_s(f1, f1, f25);
                sub_s(f0, f0, f1);
                swc1(f0, s2, 32);
            }
            // 0x002d3a18
            charge(ctx, 1);
            s0 = addiu(s0, 1);
        }
        // 0x002d3a28
        charge(ctx, 1);
        lw(s1, s1, 1228);
    }
    // 0x002d3a34
    charge(ctx, 3);
    s4 = 0;
    for (;;) {
        // 0x002d3bf0
        charge(ctx, 3);
        v0 = slti(s4, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002d3a40
        charge(ctx, 20);
        s3 = 0;
        v0 = 7000;
        mtc1(v0, f0);
        cvt_s_w(f20, f0);
        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
        v0 = sll(s4, 3);
        v0 = addu(v0, s4);
        v0 = sll(v0, 1);
        v0 = addu(v0, s4);
        s0 = sll(v0, 4);
        v0 = addu(v1, s0);
        lwc1(f1, v0, 720);
        lwc1(f0, v0, 724);
        swc1(f1, sp, 0xD8);
        swc1(f0, sp, 0xDC);
        lw(s2, v1, gbtl::kGridList);
        lwc1(f21, sp, 0xDC);
        for (;;) {
            // 0x002d3b18
            charge(ctx, 2);
            if (s2 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002d3a90
            charge(ctx, 3);
            s1 = 0;
            for (;;) {
                // 0x002d3b08
                charge(ctx, 3);
                v0 = slti(s1, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x002d3a9c
                charge(ctx, 20);
                v0 = sll(s1, 3);
                v0 = addu(v0, s1);
                v0 = sll(v0, 1);
                v0 = addu(v0, s1);
                v0 = sll(v0, 4);
                s5 = addu(s2, v0);
                lwc1(f1, s5, 8);
                lwc1(f0, sp, 0xD8);
                sub_s(f0, f1, f0);
                swc1(f0, sp, 0xE8);
                lwc1(f0, s5, 12);
                sub_s(f0, f0, f21);
                swc1(f0, sp, 0xEC);
                a0 = addiu(sp, 0xE8);
                jal(ctx, 0x2D3AD4u, gen::fn_sub_4C6AF0_004c6af0);
                mov_s(f22, f0);
                c_lt_s(f22, f20);
                if (cond(ctx)) {
                    // 0x002d3aec
                    charge(ctx, 6);
                    a0 = addiu(sp, 0xE0);
                    a1 = addiu(sp, 0xE8);
                    jal(ctx, 0x2D3AF4u, gen::fn_sub_4C6B20_004c6b20);
                    s3 = addiu(s5, 8);
                    mov_s(f20, f22);
                }
                // 0x002d3b04
                charge(ctx, 1);
                s1 = addiu(s1, 1);
            }
            // 0x002d3b14
            charge(ctx, 1);
            lw(s2, s2, 1228);
        }
        // 0x002d3b20
        charge(ctx, 2);
        if (s3 == 0) {
            // 0x002d3bdc
            charge(ctx, 4);
            v1 = lui(0xBF80);
            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
            v0 = addu(v0, s0);
            sw(v1, v0, 740);
        } else {
            // 0x002d3b28
            charge(ctx, 6);
            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
            a1 = addu(v0, s0);
            lw(v1, s3, 16);
            v0 = addiu(a1, 720);
            if (v1 == v0) {
                // 0x002d3bcc
                charge(ctx, 4);
                v0 = lui(0xBF80);
                sw(v0, a1, 740);
            } else {
                // 0x002d3b40
                charge(ctx, 35);
                v0 = 0x3F000000;
                mtc1(v0, f0);
                mul_s(f2, f0, f20);
                lwc1(f0, sp, 0xE0);
                mul_s(f1, f0, f2);
                swc1(f1, sp, 0xE0);
                lwc1(f0, sp, 0xE4);
                mul_s(f0, f0, f2);
                swc1(f0, sp, 0xE4);
                v0 = sll(s4, 3);
                v0 = addu(v0, s4);
                v0 = sll(v0, 1);
                v0 = addu(v0, s4);
                a0 = sll(v0, 4);
                lwc1(f0, sp, 0xD8);
                add_s(f0, f0, f1);
                swc1(f0, a1, 728);
                lwc1(f0, sp, 0xE4);
                add_s(f0, f21, f0);
                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                v0 = addu(v0, a0);
                swc1(f0, v0, 732);
                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                v0 = addu(v0, a0);
                sw(s3, v0, 736);
                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                v0 = addu(v0, a0);
                swc1(f20, v0, 740);
                v1 = 0x43FA0000;
                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                v0 = addu(v0, a0);
                sw(v1, v0, 744);
            }
        }
        // 0x002d3bec
        charge(ctx, 1);
        s4 = addiu(s4, 1);
    }
    // 0x002d3bfc
    charge(ctx, 4);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s1, v0, gbtl::kGridList);
    for (;;) {
        // 0x002d3c88
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002d3c0c
        charge(ctx, 3);
        s0 = 0;
        for (;;) {
            // 0x002d3c78
            charge(ctx, 3);
            v0 = slti(s0, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002d3c18
            charge(ctx, 13);
            v0 = sll(s0, 3);
            v0 = addu(v0, s0);
            v0 = sll(v0, 1);
            v0 = addu(v0, s0);
            v0 = sll(v0, 4);
            v0 = addu(s1, v0);
            a0 = addiu(v0, 8);
            lwc1(f1, v0, 28);
            mtc1(zero, f0);
            c_le_s(f1, f0);
            if (!cond(ctx)) {
                // 0x002d3c4c
                charge(ctx, 4);
                lwc1(f0, a0, 24);
                c_lt_s(f0, f26);
                if (cond(ctx)) {
                    goto L_002d3c70;
                }
                // 0x002d3c5c
                charge(ctx, 5);
                mov_s(f12, f26);
                jal(ctx, 0x2D3C60u, gen::fn_sub_2D2F50_002d2f50);
                goto L_002d3c74;
            }
        L_002d3c70:
            charge(ctx, 1);
            sw(zero, a0, 48);
        L_002d3c74:
            charge(ctx, 1);
            s0 = addiu(s0, 1);
        }
        // 0x002d3c84
        charge(ctx, 1);
        lw(s1, s1, 1228);
    }
    // 0x002d3c90
    charge(ctx, 3);
    s0 = 0;
    for (;;) {
        // 0x002d3cf0
        charge(ctx, 3);
        v0 = slti(s0, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002d3c9c
        charge(ctx, 14);
        v0 = sll(s0, 3);
        v0 = addu(v0, s0);
        v0 = sll(v0, 1);
        v0 = addu(v0, s0);
        v1 = sll(v0, 4);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        v0 = addu(v0, v1);
        a0 = addiu(v0, 720);
        lwc1(f1, v0, 740);
        mtc1(zero, f0);
        c_le_s(f1, f0);
        if (cond(ctx)) {
            // 0x002d3ce8
            charge(ctx, 1);
            sw(zero, a0, 48);
        } else {
            // 0x002d3cd4
            charge(ctx, 5);
            mov_s(f12, f26);
            jal(ctx, 0x2D3CD8u, gen::fn_sub_2D2F50_002d2f50);
        }
        // 0x002d3cec
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x002d3cfc
    charge(ctx, 29);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    a0 = addiu(v0, 1936);
    mov_s(f12, f26);
    jal(ctx, 0x2D3D08u, gen::fn_sub_2D2F50_002d2f50);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    a0 = addiu(v0, 2240);
    mov_s(f12, f26);
    jal(ctx, 0x2D3D1Cu, gen::fn_sub_2D2F50_002d2f50);
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
    sp = addiu(sp, 0x100);
}

// 0x002D41C0 sub_2D41C0 -- 1596 bytes; frame 0x4E0: ra sp+0x70, s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// [btlPathSmooth] Smooths a found path: drops the nodes a straight line can skip (sub_2D2A00) and writes the way
// points to the path record.
// Arguments: a0 path.
void sub_2D41C0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12}, f13{ctx, 13}, f20{ctx, 20}, f21{ctx, 21};
    // 0x002d41c0
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x4E0);
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
    s2 = 0;
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    s0 = addiu(v1, 2240);
    v0 = 0x3F000000;
    mtc1(v0, f0);
    mul_s(f20, f0, f12);
    a0 = addiu(v1, 1944);
    a1 = addiu(v1, 2248);
    mov_s(f12, f20);
    jal(ctx, 0x2D4214u, gen::fn_sub_2D2A00_002d2a00);
    if (v0 != 0) {
        // 0x002d4254
        charge(ctx, 2);
        for (;;) {
            // 0x002d4480
            charge(ctx, 2);
            if (s0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002d425c
            charge(ctx, 2);
            if (i64(s2) <= 0) {
                // 0x002d42b8
                charge(ctx, 4);
                lwc1(f1, s0, 8);
                lwc1(f0, s0, 12);
                swc1(f1, sp, 0x4C8);
                swc1(f0, sp, 0x4CC);
            } else {
                // 0x002d4264
                charge(ctx, 3);
                s1 = s0;
                for (;;) {
                    // 0x002d4294
                    charge(ctx, 2);
                    if (s0 != 0) {
                        backedge(ctx);
                        // 0x002d4270
                        charge(ctx, 7);
                        a0 = addiu(sp, 0x4C8);
                        a1 = addiu(s0, 8);
                        mov_s(f12, f20);
                        jal(ctx, 0x2D427Cu, gen::fn_sub_2D2A00_002d2a00);
                        if (v0 == 0) {
                            // 0x002d428c
                            charge(ctx, 2);
                            s1 = s0;
                            lw(s0, s0, 44);
                            continue;
                        }
                    }
                    break;
                }
                // 0x002d429c
                charge(ctx, 7);
                s0 = s1;
                lwc1(f1, s1, 8);
                lwc1(f0, s1, 12);
                swc1(f1, sp, 0x4C8);
                swc1(f0, sp, 0x4CC);
            }
            // 0x002d42c8
            charge(ctx, 20);
            a1 = addiu(sp, 0x4A8);
            lwc1(f1, sp, 0x4A8);
            lwc1(f0, sp, 0x4AC);
            swc1(f1, sp, 0x4A0);
            swc1(f0, sp, 0x4A4);
            lwc1(f1, sp, 0x4C8);
            lwc1(f0, sp, 0x4D8);
            sub_s(f3, f1, f0);
            swc1(f3, sp, 0x4A8);
            lwc1(f1, sp, 0x4CC);
            lwc1(f0, sp, 0x4DC);
            sub_s(f2, f1, f0);
            swc1(f2, sp, 0x4AC);
            lwc1(f1, sp, 0x4A0);
            lwc1(f0, sp, 0x4A4);
            mula_s(f0, f2);
            madd_s(f1, f1, f3);
            at = slti(s2, 2);
            if (at == 0) {
                // 0x002d4318
                charge(ctx, 4);
                lwc1(f0, gp, -32128);  // 0x7CAF70
                c_le_s(f1, f0);
                if (!cond(ctx)) {
                    goto L_002d4440;
                }
                // 0x002d4328
                charge(ctx, 14);
                a0 = addiu(sp, 0x4B0);
                jal(ctx, 0x2D432Cu, gen::fn_sub_4C6B20_004c6b20);
                mov_s(f21, f0);
                a0 = addiu(sp, 0x4B8);
                a1 = addiu(sp, 0x4A0);
                jal(ctx, 0x2D4340u, gen::fn_sub_4C6B20_004c6b20);
                v0 = 0x437A0000;
                mtc1(v0, f1);
                c_lt_s(f21, f1);
                if (cond(ctx)) {
                    // 0x002d4360
                    charge(ctx, 3);
                    c_lt_s(f0, f1);
                    if (!cond(ctx)) {
                        goto L_002d4378;
                    }
                    // 0x002d436c
                    charge(ctx, 3);
                    s2 = addiu(s2, -1);
                    goto L_002d4418;
                }
            L_002d4378:
                charge(ctx, 40);
                lwc1(f1, gp, -32124);  // 0x7CAF74
                mul_s(f2, f1, f21);
                lwc1(f1, sp, 0x4B0);
                mul_s(f3, f1, f2);
                swc1(f3, sp, 0x4D0);
                lwc1(f1, sp, 0x4B4);
                mul_s(f2, f1, f2);
                swc1(f2, sp, 0x4D4);
                v0 = sll(s2, 3);
                v0 = addu(v0, sp);
                v0 = addiu(v0, 128);
                lwc1(f1, v0, -8);
                add_s(f1, f3, f1);
                swc1(f1, sp, 0x4D0);
                lwc1(f1, v0, -4);
                add_s(f1, f2, f1);
                swc1(f1, sp, 0x4D4);
                lwc1(f2, sp, 0x4D0);
                lwc1(f1, sp, 0x4D4);
                swc1(f2, v0, 0);
                swc1(f1, v0, 4);
                lwc1(f1, gp, -32672);  // 0x7CAD50
                mul_s(f1, f1, f0);
                lwc1(f0, sp, 0x4B8);
                mul_s(f2, f0, f1);
                swc1(f2, sp, 0x4D0);
                lwc1(f0, sp, 0x4BC);
                mul_s(f1, f0, f1);
                swc1(f1, sp, 0x4D4);
                lwc1(f0, v0, -16);
                add_s(f0, f2, f0);
                swc1(f0, sp, 0x4D0);
                lwc1(f0, v0, -12);
                add_s(f0, f1, f0);
                swc1(f0, sp, 0x4D4);
                lwc1(f1, sp, 0x4D0);
                lwc1(f0, sp, 0x4D4);
                swc1(f1, v0, -8);
                swc1(f0, v0, -4);
                s2 = addiu(s2, 1);
            L_002d4418:
                charge(ctx, 10);
                v0 = sll(s2, 3);
                v0 = addu(v0, sp);
                v0 = addiu(v0, 128);
                lwc1(f1, sp, 0x4C8);
                lwc1(f0, sp, 0x4CC);
                swc1(f1, v0, 0);
                swc1(f0, v0, 4);
                s2 = addiu(s2, 1);
                goto L_002d4460;
            }
        L_002d4440:
            charge(ctx, 8);
            v0 = sll(s2, 3);
            v0 = addu(v0, sp);
            v0 = addiu(v0, 128);
            lwc1(f1, sp, 0x4C8);
            lwc1(f0, sp, 0x4CC);
            swc1(f1, v0, 0);
            swc1(f0, v0, 4);
            s2 = addiu(s2, 1);
        L_002d4460:
            charge(ctx, 8);
            v0 = sll(s2, 3);
            v0 = addu(v0, sp);
            v0 = addiu(v0, 120);
            lwc1(f1, v0, 0);
            lwc1(f0, v0, 4);
            swc1(f1, sp, 0x4D8);
            swc1(f0, sp, 0x4DC);
            lw(s0, s0, 44);
        }
    } else {
        // 0x002d4224
        charge(ctx, 12);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lwc1(f1, v0, gbtl4::kPathGoal + 8);
        lwc1(f0, v0, gbtl4::kPathGoal + 12);
        swc1(f1, sp, 0x80);
        swc1(f0, sp, 0x84);
        lwc1(f1, v0, gbtl4::kPathStart + 8);
        lwc1(f0, v0, gbtl4::kPathStart + 12);
        swc1(f1, sp, 0x88);
        swc1(f0, sp, 0x8C);
        s2 = 2;
    }
    // 0x002d4488
    charge(ctx, 3);
    at = slti(s2, 2);
    if (at == 0) {
        // 0x002d44a0
        charge(ctx, 3);
        at = slti(s2, 3);
        if (at == 0) {
            // 0x002d44dc
            charge(ctx, 6);
            s1 = 0;
            s3 = addiu(s2, -1);
            v0 = sll(s2, 3);
            v0 = addu(v0, sp);
            s5 = addiu(v0, 128);
            lwc1(f20, sp, 0x84);
            for (;;) {
                // 0x002d44f4
                charge(ctx, 4);
                v0 = addiu(s3, 1);
                v0 = slt(v0, s2);
                if (v0 != 0) {
                    // 0x002d451c
                    charge(ctx, 7);
                    v0 = sll(s3, 3);
                    v0 = addu(v0, sp);
                    v0 = addiu(v0, 136);
                    lwc1(f1, v0, 0);
                    lwc1(f0, v0, 4);
                    swc1(f1, sp, 0x480);
                    swc1(f0, sp, 0x484);
                } else {
                    // 0x002d4504
                    charge(ctx, 6);
                    lwc1(f1, s5, -8);
                    lwc1(f0, s5, -4);
                    swc1(f1, sp, 0x480);
                    swc1(f0, sp, 0x484);
                }
                // 0x002d4538
                charge(ctx, 10);
                v0 = sll(s3, 3);
                v0 = addu(v0, sp);
                s0 = addiu(v0, 128);
                lwc1(f1, s0, 0);
                lwc1(f0, s0, 4);
                swc1(f1, sp, 0x488);
                swc1(f0, sp, 0x48C);
                v0 = addiu(s3, -1);
                if (i64(v0) >= 0) {
                    // 0x002d45d8
                    charge(ctx, 4);
                    lwc1(f1, s0, -8);
                    lwc1(f0, s0, -4);
                    swc1(f1, sp, 0x490);
                    swc1(f0, sp, 0x494);
                } else {
                    // 0x002d4560
                    charge(ctx, 30);
                    lwc1(f1, sp, 0x80);
                    lwc1(f0, sp, 0x488);
                    sub_s(f0, f1, f0);
                    swc1(f0, sp, 0x4C0);
                    lwc1(f0, sp, 0x48C);
                    sub_s(f0, f20, f0);
                    swc1(f0, sp, 0x4C4);
                    a0 = addiu(sp, 0x4C0);
                    a1 = a0;
                    jal(ctx, 0x2D4584u, gen::fn_sub_4C6B20_004c6b20);
                    v0 = 0x43960000;
                    mtc1(v0, f1);
                    lwc1(f0, sp, 0x4C0);
                    mul_s(f2, f0, f1);
                    swc1(f2, sp, 0x4C0);
                    lwc1(f0, sp, 0x4C4);
                    mul_s(f1, f0, f1);
                    swc1(f1, sp, 0x4C4);
                    lwc1(f0, sp, 0x80);
                    add_s(f0, f2, f0);
                    swc1(f0, sp, 0x4C0);
                    add_s(f0, f1, f20);
                    swc1(f0, sp, 0x4C4);
                    lwc1(f1, sp, 0x4C0);
                    lwc1(f0, sp, 0x4C4);
                    swc1(f1, sp, 0x490);
                    swc1(f0, sp, 0x494);
                }
                // 0x002d45e8
                charge(ctx, 3);
                v0 = addiu(s3, -2);
                if (i64(v0) >= 0) {
                    // 0x002d466c
                    charge(ctx, 4);
                    lwc1(f1, s0, -16);
                    lwc1(f0, s0, -12);
                    swc1(f1, sp, 0x498);
                    swc1(f0, sp, 0x49C);
                } else {
                    // 0x002d45f4
                    charge(ctx, 30);
                    lwc1(f1, sp, 0x80);
                    lwc1(f0, sp, 0x488);
                    sub_s(f0, f1, f0);
                    swc1(f0, sp, 0x4C0);
                    lwc1(f0, sp, 0x48C);
                    sub_s(f0, f20, f0);
                    swc1(f0, sp, 0x4C4);
                    a0 = addiu(sp, 0x4C0);
                    a1 = a0;
                    jal(ctx, 0x2D4618u, gen::fn_sub_4C6B20_004c6b20);
                    v0 = 0x43FA0000;
                    mtc1(v0, f1);
                    lwc1(f0, sp, 0x4C0);
                    mul_s(f2, f0, f1);
                    swc1(f2, sp, 0x4C0);
                    lwc1(f0, sp, 0x4C4);
                    mul_s(f1, f0, f1);
                    swc1(f1, sp, 0x4C4);
                    lwc1(f0, sp, 0x80);
                    add_s(f0, f2, f0);
                    swc1(f0, sp, 0x4C0);
                    add_s(f0, f1, f20);
                    swc1(f0, sp, 0x4C4);
                    lwc1(f1, sp, 0x4C0);
                    lwc1(f0, sp, 0x4C4);
                    swc1(f1, sp, 0x498);
                    swc1(f0, sp, 0x49C);
                }
                // 0x002d467c
                charge(ctx, 75);
                v0 = sll(s1, 3);
                v1 = addu(s4, v0);
                lwc1(f1, s0, 0);
                lwc1(f0, s0, 4);
                swc1(f1, v1, 0);
                swc1(f0, v1, 4);
                lwc1(f13, sp, 0x488);
                lwc1(f12, sp, 0x490);
                lwc1(f11, sp, 0x498);
                v0 = lui(0xBCC0);
                mtc1(v0, f10);
                v0 = 0x3E680000;
                mtc1(v0, f1);
                v0 = lui(0xBD90);
                mtc1(v0, f9);
                lwc1(f8, sp, 0x480);
                v0 = 0x3F5E0000;
                mtc1(v0, f7);
                mula_s(f7, f13);
                madda_s(f9, f8);
                madda_s(f1, f12);
                madd_s(f0, f10, f11);
                swc1(f0, sp, 0x4D0);
                lwc1(f6, sp, 0x48C);
                lwc1(f5, sp, 0x484);
                lwc1(f4, sp, 0x494);
                lwc1(f3, sp, 0x49C);
                mula_s(f7, f6);
                madda_s(f9, f5);
                madda_s(f1, f4);
                madd_s(f0, f10, f3);
                swc1(f0, sp, 0x4D4);
                lwc1(f1, sp, 0x4D0);
                lwc1(f0, sp, 0x4D4);
                swc1(f1, v1, 8);
                swc1(f0, v1, 12);
                v0 = lui(0xBD80);
                mtc1(v0, f2);
                v0 = 0x3F100000;
                mtc1(v0, f1);
                mula_s(f1, f13);
                madda_s(f2, f8);
                madda_s(f1, f12);
                madd_s(f0, f2, f11);
                swc1(f0, sp, 0x4D0);
                mula_s(f1, f6);
                madda_s(f2, f5);
                madda_s(f1, f4);
                madd_s(f0, f2, f3);
                swc1(f0, sp, 0x4D4);
                lwc1(f1, sp, 0x4D0);
                lwc1(f0, sp, 0x4D4);
                swc1(f1, v1, 16);
                swc1(f0, v1, 20);
                lwc1(f1, gp, -32120);  // 0x7CAF78
                mula_s(f1, f13);
                madda_s(f10, f8);
                madda_s(f7, f12);
                madd_s(f0, f9, f11);
                swc1(f0, sp, 0x4D0);
                mula_s(f1, f6);
                madda_s(f10, f5);
                madda_s(f7, f4);
                madd_s(f0, f9, f3);
                swc1(f0, sp, 0x4D4);
                lwc1(f1, sp, 0x4D0);
                lwc1(f0, sp, 0x4D4);
                swc1(f1, v1, 24);
                swc1(f0, v1, 28);
                s1 = addiu(s1, 4);
                s3 = addiu(s3, -1);
                if (i64(s3) <= 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x002d47a8
            charge(ctx, 8);
            v0 = sll(s1, 3);
            v0 = addu(s4, v0);
            lwc1(f1, sp, 0x80);
            lwc1(f0, sp, 0x84);
            swc1(f1, v0, 0);
            swc1(f0, v0, 4);
            v0 = addiu(s1, 1);
            sh(v0, s4, 1024);
        } else {
            // 0x002d44ac
            charge(ctx, 12);
            lwc1(f1, sp, 0x88);
            lwc1(f0, sp, 0x8C);
            swc1(f1, s4, 0);
            swc1(f0, s4, 4);
            lwc1(f1, sp, 0x80);
            lwc1(f0, sp, 0x84);
            swc1(f1, s4, 8);
            swc1(f0, s4, 12);
            v0 = 2;
            sh(v0, s4, 1024);
        }
        // 0x002d47c8
        charge(ctx, 1);
        v0 = 1;
    } else {
        // 0x002d4494
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x002d47cc (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0x4E0);
}

// 0x002D4810 sub_2D4810 -- 172 bytes; leaf frame (no stack)
// [btlPathPopBest] Pops the open-list node with the lowest cost (+32) from gBtl +2544 (linked by +36).
void sub_2D4810(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x002d4810
    enter(ctx, 11);  // entry check point + this block's cycles
    // The best so far: 350000.0f (350,000 as an int converted).
    v1 = 0x50000;
    v1 = v1 | 0x5730;
    mtc1(v1, f0);
    cvt_s_w(f1, f0);
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    a0 = addiu(v1, 2544);
    lw(v1, v1, gbtl4::kPathOpen);
    a1 = v1;
    // Pass 1: the lowest cost on the open list (v0).
    for (;;) {
        // 0x002d4858
        charge(ctx, 2);
        if (a1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002d483c
        charge(ctx, 4);
        lwc1(f0, a1, path::kCost);
        c_le_s(f1, f0);
        if (!cond(ctx)) {
            // 0x002d484c
            charge(ctx, 2);
            v0 = a1;
            mov_s(f1, f0);
        }
        // 0x002d4854
        charge(ctx, 1);
        lw(a1, a1, path::kNextOpen);
    }
    // Pass 2: find its predecessor (a1) and unlink it (from the head word a0 = &gBtl +2544 when first).
    // 0x002d4860
    charge(ctx, 3);
    a1 = 0;
    for (;;) {
        // 0x002d487c
        charge(ctx, 4);
        if (v1 != 0) {
            backedge(ctx);
            // 0x002d486c
            charge(ctx, 2);
            if (v1 != v0) {
                // 0x002d4874
                charge(ctx, 2);
                a1 = v1;
                lw(v1, v1, path::kNextOpen);
                continue;
            }
        }
        break;
    }
    // 0x002d488c
    charge(ctx, 2);
    if (v1 != 0) {
        // 0x002d4894
        charge(ctx, 2);
        if (a1 == 0) {
            // 0x002d48ac
            charge(ctx, 2);
            lw(v1, v1, path::kNextOpen);
            sw(v1, a0, 0);
        } else {
            // 0x002d489c
            charge(ctx, 4);
            lw(v1, v1, path::kNextOpen);
            sw(v1, a1, 36);
        }
    }
    // 0x002d48b4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x002D48C0 sub_2D48C0 -- 1024 bytes; frame 0xB0: ra sp+0x90, s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [btlPathFind] Path query from a1 to a2 for a unit's walk: direct when nothing blocks (sub_2D2A00), else the graph
// (sub_2D32B0) and a lowest-cost search from the start node; the result in the path record a0 (+1024 count, +1028
// done).
// Arguments: a0 path record, a1 start, a2 goal.
void sub_2D48C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f20{ctx, 20};
    // 0x002d48c0
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
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
    s4 = a0;
    s1 = a1;
    s0 = a2;
    mov_s(f20, f12);
    v0 = 1;
    sb(v0, a0, 1028);
    v0 = 0x3F000000;
    mtc1(v0, f0);
    mul_s(f12, f0, f20);
    a0 = s1;
    a1 = s0;
    jal(ctx, 0x2D491Cu, gen::fn_sub_2D2A00_002d2a00);
    if (v0 != 0) {
        // 0x002d4964
        charge(ctx, 17);
        sh(zero, s4, 1024);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lwc1(f1, s1, 0);
        lwc1(f0, s1, 4);
        swc1(f1, v0, gbtl4::kPathStart + 8);
        swc1(f0, v0, gbtl4::kPathStart + 12);
        lwc1(f1, s0, 0);
        lwc1(f0, s0, 4);
        swc1(f1, v0, gbtl4::kPathGoal + 8);
        swc1(f0, v0, gbtl4::kPathGoal + 12);
        mov_s(f12, f20);
        jal(ctx, 0x2D4990u, gen::fn_sub_2D32B0_002d32b0);
        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(v0, v1, gbtl4::kPathStart + 48);
        if (v0 != 0) {
            // 0x002d49a8
            charge(ctx, 3);
            lw(v0, v1, gbtl4::kPathGoal + 48);
            if (v0 == 0) {
                goto L_002d49b4;
            }
            // 0x002d49c8
            charge(ctx, 30);
            sw(zero, v1, gbtl4::kPathOpen);
            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
            sw(zero, v0, gbtl4::kPathClosed);
            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
            sw(zero, v0, gbtl4::kPathStart + 28);
            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
            lwc1(f1, v0, gbtl4::kPathStart + 8);
            lwc1(f0, v0, gbtl4::kPathGoal + 8);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0xA8);
            lwc1(f1, v0, gbtl4::kPathStart + 12);
            lwc1(f0, v0, gbtl4::kPathGoal + 12);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0xAC);
            a0 = addiu(sp, 0xA8);
            jal(ctx, 0x2D4A04u, gen::fn_sub_4C6AF0_004c6af0);
            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
            swc1(f0, v0, gbtl4::kPathStart + 32);
            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
            sw(zero, v0, gbtl4::kPathStart + 44);
            lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
            lw(v0, v1, gbtl4::kPathOpen);
            sw(v0, v1, gbtl4::kPathStart + 36);
            lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
            v0 = addiu(v1, 1936);
            sw(v0, v1, gbtl4::kPathOpen);
            s2 = 0;
            for (;;) {
                // 0x002d4c48
                charge(ctx, 4);
                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                lw(v0, v0, gbtl4::kPathOpen);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x002d4a40
                charge(ctx, 7);
                jal(ctx, 0x2D4A40u, gen::fn_sub_2D4810_002d4810);
                s0 = v0;
                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                v0 = addiu(v0, 2240);
                if (s0 == v0) {
                    goto L_002d4a5c_7;
                }
                // 0x002d4a68
                charge(ctx, 3);
                s3 = 0;
                for (;;) {
                    // 0x002d4c18
                    charge(ctx, 7);
                    v0 = s3 & 0xFFFF;
                    v0 = sll(v0, 2);
                    v0 = addu(s0, v0);
                    s7 = addiu(v0, 48);
                    lw(v1, v0, 48);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x002d4a74
                    charge(ctx, 10);
                    v0 = s3 & 0xFFFF;
                    v0 = sll(v0, 2);
                    v0 = addu(s0, v0);
                    lwc1(f1, s0, 28);
                    lwc1(f0, v0, 176);
                    add_s(f0, f1, f0);
                    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                    lw(a0, v0, gbtl4::kPathOpen);
                    for (;;) {
                        // 0x002d4ab4
                        charge(ctx, 2);
                        if (a0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x002d4a9c
                        charge(ctx, 2);
                        if (a0 == v1) {
                            goto L_002d4aa4_11;
                        }
                        // 0x002d4ab0
                        charge(ctx, 1);
                        lw(a0, a0, path::kNextOpen);
                    }
                    // 0x002d4abc
                    charge(ctx, 1);
                    s1 = 0;
                L_002d4ac0:
                    charge(ctx, 3);
                    lw(v0, v0, 2548);
                    for (;;) {
                        // 0x002d4ae4
                        charge(ctx, 2);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x002d4acc
                        charge(ctx, 2);
                        if (v0 == v1) {
                            goto L_002d4ad4_17;
                        }
                        // 0x002d4ae0
                        charge(ctx, 1);
                        lw(v0, v0, 40);
                    }
                    // 0x002d4aec
                    charge(ctx, 1);
                    s5 = 0;
                L_002d4af0:
                    charge(ctx, 2);
                    if (s1 == 0) {
                        // 0x002d4af8
                        charge(ctx, 2);
                        if (s5 != 0) {
                            goto L_002d4b00;
                        }
                    L_002d4b0c:
                        charge(ctx, 28);
                        v0 = s3 & 0xFFFF;
                        v0 = sll(v0, 2);
                        a0 = addu(s0, v0);
                        s6 = addiu(a0, 48);
                        swc1(f0, v1, 28);
                        lw(v0, a0, 48);
                        swc1(f0, v0, 32);
                        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                        lw(v0, a0, 48);
                        lwc1(f1, v0, 8);
                        lwc1(f0, v1, gbtl4::kPathGoal + 8);
                        sub_s(f0, f1, f0);
                        swc1(f0, sp, 0xA0);
                        lwc1(f1, v0, 12);
                        lwc1(f0, v1, gbtl4::kPathGoal + 12);
                        sub_s(f0, f1, f0);
                        swc1(f0, sp, 0xA4);
                        a0 = addiu(sp, 0xA0);
                        jal(ctx, 0x2D4B54u, gen::fn_sub_4C6AF0_004c6af0);
                        lw(v0, s6, 0);
                        lwc1(f1, v0, 32);
                        add_s(f0, f1, f0);
                        swc1(f0, v0, 32);
                        lw(v0, s6, 0);
                        sw(s0, v0, 44);
                        if (s5 != 0) {
                            // 0x002d4b7c
                            charge(ctx, 7);
                            lw(a0, s7, 0);
                            a1 = 0;
                            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                            v1 = addiu(v0, 2548);
                            lw(v0, v0, gbtl4::kPathClosed);
                            for (;;) {
                                // 0x002d4ba8
                                charge(ctx, 4);
                                if (v0 != 0) {
                                    backedge(ctx);
                                    // 0x002d4b98
                                    charge(ctx, 2);
                                    if (v0 != a0) {
                                        // 0x002d4ba0
                                        charge(ctx, 2);
                                        a1 = v0;
                                        lw(v0, v0, 40);
                                        continue;
                                    }
                                }
                                break;
                            }
                            // 0x002d4bb8
                            charge(ctx, 2);
                            if (v0 != 0) {
                                // 0x002d4bc0
                                charge(ctx, 2);
                                if (a1 == 0) {
                                    // 0x002d4bd8
                                    charge(ctx, 2);
                                    lw(v0, v0, 40);
                                    sw(v0, v1, 0);
                                } else {
                                    // 0x002d4bc8
                                    charge(ctx, 4);
                                    lw(v0, v0, 40);
                                    sw(v0, a1, 40);
                                }
                            }
                        }
                        // 0x002d4be0
                        charge(ctx, 2);
                        if (s1 == 0) {
                            // 0x002d4be8
                            charge(ctx, 10);
                            v0 = s3 & 0xFFFF;
                            v0 = sll(v0, 2);
                            a0 = addu(s0, v0);
                            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                            lw(v1, v0, gbtl4::kPathOpen);
                            lw(v0, a0, 48);
                            sw(v1, v0, 36);
                            lw(v1, a0, 48);
                            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                            sw(v1, v0, gbtl4::kPathOpen);
                        }
                        goto L_002d4c10;
                    }
                L_002d4b00:
                    charge(ctx, 3);
                    c_le_s(f1, f0);
                    if (!cond(ctx)) {
                        goto L_002d4b0c;
                    }
                L_002d4c10:
                    charge(ctx, 2);
                    v0 = addiu(s3, 1);
                    s3 = v0 & 0xFFFF;
                }
                // 0x002d4c34
                charge(ctx, 5);
                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                lw(v0, v0, gbtl4::kPathClosed);
                sw(v0, s0, 40);
                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                sw(s0, v0, gbtl4::kPathClosed);
            }
        L_002d4c58:
            charge(ctx, 2);
            if (s2 == 0) {
                // 0x002d4c80
                charge(ctx, 2);
                v0 = 3;
                sb(v0, s4, 1028);
            } else {
                // 0x002d4c60
                charge(ctx, 8);
                a0 = s4;
                mov_s(f12, f20);
                jal(ctx, 0x2D4C68u, gen::fn_sub_2D41C0_002d41c0);
                v0 = 2;
                sb(v0, s4, 1028);
            }
            // 0x002d4c88
            charge(ctx, 1);
            v0 = s2;
            // 0x002d4c8c (the shared epilogue, written out on this path)
            charge(ctx, 13);
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
            sp = addiu(sp, 0xB0);
            return;
        }
    L_002d49b4:
        charge(ctx, 5);
        v0 = 3;
        sb(v0, s4, 1028);
        v0 = 0;
    } else {
        // 0x002d492c
        charge(ctx, 14);
        lwc1(f1, s1, 0);
        lwc1(f0, s1, 4);
        swc1(f1, s4, 0);
        swc1(f0, s4, 4);
        lwc1(f1, s0, 0);
        lwc1(f0, s0, 4);
        swc1(f1, s4, 8);
        swc1(f0, s4, 12);
        v0 = 2;
        sh(v0, s4, 1024);
        sb(v0, s4, 1028);
        v0 = 1;
    }
    // 0x002d4c8c (the shared epilogue, written out on this path)
    charge(ctx, 13);
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
    sp = addiu(sp, 0xB0);
    return;
L_002d4a5c_7:
    charge(ctx, 3);
    s2 = 1;
    goto L_002d4c58;
L_002d4aa4_11:
    charge(ctx, 3);
    s1 = 1;
    goto L_002d4ac0;
L_002d4ad4_17:
    charge(ctx, 3);
    s5 = 1;
    goto L_002d4af0;
}

// 0x002D5DC0 sub_2D5DC0 -- 60 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Clears a 28-byte result record and sets its byte +25 to -1.
// Arguments: a0 record.
void sub_2D5DC0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002d5dc0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a1 = 0;
    a2 = 28;
    jal(ctx, 0x2D5DD8u, gen::fn_memset_00521408);
    v1 = si(-1);
    sb(v1, s0, 25);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002D7560 sub_2D7560 -- 816 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlActionCollectSpoils] Victory book-keeping of a defeated enemy (once per action, flag 0x20): adds its experience
// (sub_30BC50 * sub_1C0070's factor) to gBtl +3068, collects its item drop (sub_30BDE0, or the action's stolen item
// +128 with the chance +130) into the three drop slots +3040, the rare flag of the enemy table (bit 0x40 -> gBtl
// +3036 bit 1), and the four special ids 193..196 -> gBtl +3104 bits.
// Arguments: a0 btlAction.
void sub_2D7560(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x002d7560
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lhu(v1, a0, act::kFlags2);
    v1 = v1 & 0x1;
    if (v1 != 0) {
        // 0x002d7588
        charge(ctx, 5);
        lw(s0, s2, act::kUnit);
        lbu(a0, s0, unit::kSide);
        v1 = 1;
        if (a0 == v1) {
            // 0x002d759c
            charge(ctx, 4);
            lhu(v1, s0, unit::kId);
            v1 = slti(v1, 336);
            if (v1 == 0) {
                // 0x002d75ac
                charge(ctx, 5);
                a0 = 0x690000;
                a0 = addiu(a0, 30944);  // "btlEfficacy.c"
                a1 = 894;
                jal(ctx, 0x2D75B8u, gen::fn_sub_19D3F0_0019d3f0);
            }
            // 0x002d75c0
            charge(ctx, 4);
            lhu(a0, s2, act::kFlags2);
            v1 = a0 & 0x20;
            if (v1 == 0) {
                // 0x002d75d0
                charge(ctx, 10);
                v0 = a0 | 0x20;
                sh(v0, s2, act::kFlags2);
                lw(a0, s0, unit::kDat);
                jal(ctx, 0x2D75DCu, gen::fn_sub_30BC50_0030bc50);
                s1 = v0;
                jal(ctx, 0x2D75E8u, gen::fn_sub_1C0070_001c0070);
                if (i64(s1) < 0) {
                    // 0x002d760c
                    charge(ctx, 7);
                    v1 = srl(s1, 1);
                    v0 = s1 & 0x1;
                    v1 = v1 | v0;
                    mtc1(v1, f1);
                    cvt_s_w(f1, f1);
                    add_s(f1, f1, f1);
                } else {
                    // 0x002d75f8
                    charge(ctx, 5);
                    mtc1(s1, f1);
                    cvt_s_w(f1, f1);
                }
                // 0x002d7628
                charge(ctx, 7);
                mul_s(f1, f1, f0);
                v0 = 0x4F000000;
                mtc1(v0, f0);
                c_le_s(f0, f1);
                if (cond(ctx)) {
                    // 0x002d7654
                    charge(ctx, 5);
                    sub_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(a0, f0);
                    v0 = lui(0x8000);
                    a0 = a0 | v0;
                } else {
                    // 0x002d7644
                    charge(ctx, 4);
                    cvt_w_s(f0, f1);
                    mfc1(a0, f0);
                }
                // 0x002d7668
                charge(ctx, 13);
                lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                lw(v0, v1, gbtl4::kExp);
                v0 = addu(v0, a0);
                sw(v0, v1, gbtl4::kExp);
                lw(a0, s0, unit::kDat);
                a1 = addiu(sp, 0x4C);
                jal(ctx, 0x2D7680u, gen::fn_sub_30BDE0_0030bde0);
                s1 = v0 & 0xFFFF;
                lw(a0, sp, 0x4C);
                v1 = 1;
                if (a0 != v1) {
                    // 0x002d769c
                    charge(ctx, 3);
                    lhu(v1, s2, act4::kStealItem);
                    if (v1 != 0) {
                        // 0x002d76a8
                        charge(ctx, 8);
                        a0 = 100;
                        jal(ctx, 0x2D76ACu, gen::fn_datCalcRand_002ffbc0);
                        a0 = v0 & 0xFF;
                        lbu(v1, s2, act4::kStealChance);
                        at = slt(a0, v1);
                        if (at != 0) {
                            // 0x002d76c8
                            charge(ctx, 1);
                            lhu(s1, s2, act4::kStealItem);
                        }
                    }
                }
                // 0x002d76cc
                charge(ctx, 3);
                a2 = s1 & 0xFFFF;
                if (a2 != 0) {
                    // 0x002d76d8
                    charge(ctx, 5);
                    a3 = 0;
                    t0 = 0;
                    lw(a1, gp, kGpBtl);  // gBtl 0x7CE3EC
                    for (;;) {
                        // 0x002d7724
                        charge(ctx, 4);
                        v1 = t0 & 0xFFFF;
                        v1 = slti(v1, 3);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x002d76ec
                        charge(ctx, 6);
                        v1 = t0 & 0xFFFF;
                        v1 = sll(v1, 3);
                        a0 = addu(a1, v1);
                        lhu(v1, a0, 3040);
                        if (v1 == a2) {
                            goto L_002d7704_18;
                        }
                        // 0x002d771c
                        charge(ctx, 2);
                        v1 = addiu(t0, 1);
                        t0 = v1 & 0xFFFF;
                    }
                L_002d7734:
                    charge(ctx, 2);
                    if (a3 == 0) {
                        // 0x002d773c
                        charge(ctx, 4);
                        t0 = 0;
                        lw(a3, gp, kGpBtl);  // gBtl 0x7CE3EC
                        for (;;) {
                            // 0x002d7794
                            charge(ctx, 4);
                            a0 = t0 & 0xFFFF;
                            v1 = slti(a0, 3);
                            if (v1 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x002d774c
                            charge(ctx, 6);
                            v1 = t0 & 0xFFFF;
                            a2 = sll(v1, 3);
                            a1 = addu(a3, a2);
                            lhu(v1, a1, 3040);
                            if (v1 == 0) {
                                goto L_002d7764_24;
                            }
                            // 0x002d778c
                            charge(ctx, 2);
                            v1 = addiu(t0, 1);
                            t0 = v1 & 0xFFFF;
                        }
                    }
                }
            L_002d77a4:
                charge(ctx, 10);
                lhu(a0, s0, unit::kId);
                v1 = sll(a0, 5);
                v1 = subu(v1, a0);
                a0 = sll(v1, 1);
                lw(v1, gp, kGpEnemyTbl);  // gBtlEnemyTbl
                v1 = addu(v1, a0);
                lhu(v1, v1, 0);
                v1 = v1 & 0x40;
                if (v1 != 0) {
                    // 0x002d77cc
                    charge(ctx, 4);
                    lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                    lw(v1, a0, gbtl4::kSpoilFlags);
                    v1 = v1 | 0x2;
                    sw(v1, a0, gbtl4::kSpoilFlags);
                }
                // 0x002d77dc
                charge(ctx, 5);
                lw(v1, s0, unit::kDat);
                lhu(a0, v1, dat::kId);
                v1 = 196;
                if (a0 == v1) {
                    // 0x002d7864
                    charge(ctx, 4);
                    lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                    lw(v1, a0, gbtl4::kSpecialDrops);
                    v1 = v1 | 0x8;
                    sw(v1, a0, gbtl4::kSpecialDrops);
                } else {
                    // 0x002d77f0
                    charge(ctx, 3);
                    v1 = 195;
                    if (a0 == v1) {
                        // 0x002d784c
                        charge(ctx, 6);
                        lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                        lw(v1, a0, gbtl4::kSpecialDrops);
                        v1 = v1 | 0x4;
                        sw(v1, a0, gbtl4::kSpecialDrops);
                    } else {
                        // 0x002d77fc
                        charge(ctx, 3);
                        v1 = 194;
                        if (a0 == v1) {
                            // 0x002d7834
                            charge(ctx, 6);
                            lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                            lw(v1, a0, gbtl4::kSpecialDrops);
                            v1 = v1 | 0x2;
                            sw(v1, a0, gbtl4::kSpecialDrops);
                        } else {
                            // 0x002d7808
                            charge(ctx, 3);
                            v1 = 193;
                            if (a0 == v1) {
                                // 0x002d781c
                                charge(ctx, 6);
                                lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                lw(v1, a0, gbtl4::kSpecialDrops);
                                v1 = v1 | 0x1;
                                sw(v1, a0, gbtl4::kSpecialDrops);
                            } else {
                                // 0x002d7814
                                charge(ctx, 2);
                            }
                        }
                    }
                }
            }
        }
    }
    // 0x002d7874 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
    return;
L_002d7704_18:
    charge(ctx, 6);
    lw(v1, a0, 3044);
    v1 = addiu(v1, 1);
    sw(v1, a0, 3044);
    a3 = 1;
    goto L_002d7734;
L_002d7764_24:
    charge(ctx, 10);
    sh(s1, a1, 3040);
    a1 = 1;
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    v1 = addu(a2, v1);
    sw(a1, v1, 3044);
    a0 = addiu(a0, 1);
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    sw(a0, v1, gbtl4::kDropCount);
    goto L_002d77a4;
}

// 0x002D7E20 sub_2D7E20 -- 200 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlPktCreateDamage] Creates the damage-number packet (kind 1792, 40 bytes: unit, target, 28-byte result, two
// halfwords) with callbacks sub_2D7970 / sub_2D79A0 / sub_2D7DF0.
// Arguments: a0, a1, a2 result, a3, t0.
void sub_2D7E20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002d7e20
    enter(ctx, 50);  // entry check point + this block's cycles
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
    s2 = a3;
    s1 = t0;
    a0 = 1792;
    a1 = 40;
    jal(ctx, 0x2D7E60u, gen::fn_sub_27EC10_0027ec10);
    s6 = v0;
    v1 = 0x2D0000;
    v1 = addiu(v1, 31088);  // &sub_2D7970
    sw(v1, v0, pkt::kOnQueue);
    v1 = 0x2D0000;
    v1 = addiu(v1, 31136);  // &sub_2D79A0
    sw(v1, v0, pkt::kUpdate);
    v1 = 0x2D0000;
    v1 = addiu(v1, 32240);  // &sub_2D7DF0
    sw(v1, v0, pkt::kOnEnd);
    lw(s0, v0, pkt::kData);
    sw(s5, s0, 0);
    sw(s4, s0, 4);
    a0 = addiu(s0, 8);
    a1 = s3;
    a2 = 28;
    jal(ctx, 0x2D7EA8u, gen::fn_memcpy_00521250);
    sh(s2, s0, 36);
    sh(s1, s0, 38);
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

// 0x002D8390 sub_2D8390 -- 628 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlSupportPickOpeningLine] The navigator's opening line: by the advantage (gBtl +26: 0 normal, 1 enemy strike, 2
// player strike), a strong enemy (enemy table bit 0x80), a rare one (0x40), the enemy count (< 6) and whether their
// mean level is 4 or more above the hero's (lines 0..11, 59..81, 81..93), with advantage 1 the +5 variants when an
// enemy sleeps (status 2); -1 for none or 6+ enemies.
void sub_2D8390(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002d8390
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 2;
    a1 = 0x80000;
    jal(ctx, 0x2D83B8u, gen::fn_btlCountActiveUnits_002d4e10);
    s0 = v0 & 0xFFFF;
    at = slti(s0, 6);
    if (at != 0) {
        // 0x002d83dc
        charge(ctx, 22);
        a0 = 2;
        a1 = 0x80000;
        jal(ctx, 0x2D83E4u, gen::fn_btlGetMeanLevel_002d4cf0);
        s1 = v0 & 0xFFFF;
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(v0, v0, gbtl::kPlayerAction);
        lw(v0, v0, act::kUnit);
        lw(a0, v0, unit::kDat);
        jal(ctx, 0x2D8400u, gen::fn_datCalcGetLevel_002ffcc0);
        v0 = v0 & 0xFF;
        v0 = subu(s1, v0);
        v0 = slti(v0, 4);
        s5 = v0 ^ 0x1;
        s3 = 0;
        s2 = 0;
        s1 = 0;
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(s4, v0, gbtl4::kUnitTail1);
        for (;;) {
            // 0x002d8490
            charge(ctx, 2);
            if (s4 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002d8434
            charge(ctx, 6);
            lw(a0, s4, unit::kDat);
            a1 = 2;
            jal(ctx, 0x2D843Cu, gen::fn_datCalcChkBadStatus_00300580);
            if (v0 != 0) {
                // 0x002d844c
                charge(ctx, 1);
                s3 = 1;
            }
            // 0x002d8450
            charge(ctx, 10);
            lw(a0, gp, kGpEnemyTbl);  // gBtlEnemyTbl
            lhu(v1, s4, unit::kId);
            v0 = sll(v1, 5);
            v0 = subu(v0, v1);
            v0 = sll(v0, 1);
            v0 = addu(a0, v0);
            lhu(v1, v0, 0);
            v0 = v1 & 0x40;
            if (v0 != 0) {
                // 0x002d8478
                charge(ctx, 1);
                s2 = 1;
            }
            // 0x002d847c
            charge(ctx, 3);
            v0 = v1 & 0x80;
            if (v0 != 0) {
                // 0x002d8488
                charge(ctx, 1);
                s1 = 1;
            }
            // 0x002d848c
            charge(ctx, 1);
            lw(s4, s4, unit::kPrev);
        }
        // 0x002d8498
        charge(ctx, 5);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lhu(v1, v0, gbtl::kAdvantage);
        v0 = 2;
        if (v1 == v0) {
            // 0x002d8590
            charge(ctx, 2);
            if (s1 == 0) {
                // 0x002d85a4
                charge(ctx, 2);
                if (s2 == 0) {
                    // 0x002d85b8
                    charge(ctx, 2);
                    if (s5 == 0) {
                        // 0x002d85cc
                        charge(ctx, 1);
                        v0 = addiu(s0, 81);
                    } else {
                        // 0x002d85c0
                        charge(ctx, 3);
                        v0 = addiu(s0, 86);
                    }
                    // 0x002d85d0
                    charge(ctx, 2);
                } else {
                    // 0x002d85ac
                    charge(ctx, 3);
                    v0 = 93;
                }
            } else {
                // 0x002d8598
                charge(ctx, 3);
                v0 = 92;
            }
        } else {
            // 0x002d84ac
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                // 0x002d8510
                charge(ctx, 2);
                if (s1 == 0) {
                    // 0x002d8524
                    charge(ctx, 2);
                    if (s2 == 0) {
                        // 0x002d8538
                        charge(ctx, 2);
                        if (s5 == 0) {
                            // 0x002d8568
                            charge(ctx, 2);
                            if (s3 == 0) {
                                // 0x002d857c
                                charge(ctx, 1);
                                v1 = 0;
                            } else {
                                // 0x002d8570
                                charge(ctx, 3);
                                v1 = 5;
                            }
                            // 0x002d8580
                            charge(ctx, 4);
                            v0 = addiu(s0, 59);
                            v0 = addu(v0, v1);
                        } else {
                            // 0x002d8540
                            charge(ctx, 2);
                            if (s3 == 0) {
                                // 0x002d8554
                                charge(ctx, 1);
                                v1 = 0;
                            } else {
                                // 0x002d8548
                                charge(ctx, 3);
                                v1 = 5;
                            }
                            // 0x002d8558
                            charge(ctx, 4);
                            v0 = addiu(s0, 69);
                            v0 = addu(v0, v1);
                        }
                    } else {
                        // 0x002d852c
                        charge(ctx, 3);
                        v0 = 81;
                    }
                } else {
                    // 0x002d8518
                    charge(ctx, 3);
                    v0 = 80;
                }
            } else {
                // 0x002d84b8
                charge(ctx, 2);
                if (v1 == 0) {
                    // 0x002d84c8
                    charge(ctx, 2);
                    if (s1 == 0) {
                        // 0x002d84dc
                        charge(ctx, 2);
                        if (s2 == 0) {
                            // 0x002d84f0
                            charge(ctx, 2);
                            if (s5 == 0) {
                                // 0x002d8504
                                charge(ctx, 1);
                                v0 = addiu(s0, -1);
                            } else {
                                // 0x002d84f8
                                charge(ctx, 3);
                                v0 = addiu(s0, 4);
                            }
                            // 0x002d8508
                            charge(ctx, 2);
                        } else {
                            // 0x002d84e4
                            charge(ctx, 3);
                            v0 = 11;
                        }
                    } else {
                        // 0x002d84d0
                        charge(ctx, 3);
                        v0 = 10;
                    }
                } else {
                    // 0x002d84c0
                    charge(ctx, 2);
                    // 0x002d85d8
                    charge(ctx, 1);
                    v0 = si(-1);
                }
            }
        }
    } else {
        // 0x002d83d0
        charge(ctx, 3);
        v0 = si(-1);
    }
    // 0x002d85dc (the shared epilogue, written out on this path)
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

// 0x002D9BE0 sub_2D9BE0 -- 192 bytes; leaf frame (no stack)
// A party unit's voice line of the table row 0x7B7EF0: party ids 1..5 -> 346..350, 7..10 -> 351..354 (no line for 6,
// the navigator); -1 for enemies and other ids.
// Arguments: a0 btlAction.
void sub_2D9BE0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x002d9be0
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, act::kUnit);
    lbu(v0, v1, unit::kSide);
    if (v0 == 0) {
        // 0x002d9bfc
        charge(ctx, 4);
        lhu(v0, v1, unit::kId);
        at = sltiu(v0, 11);
        if (at != 0) {
            // 0x002d9c0c
            charge(ctx, 7);
            v1 = 0x7B0000;
            v1 = addiu(v1, 32496);  // &0x7B7EF0
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x2D9C28u:  // table[1]
                // 0x002d9c28
                charge(ctx, 3);
                v0 = 346;
                break;
            case 0x2D9C34u:  // table[2]
                // 0x002d9c34
                charge(ctx, 3);
                v0 = 347;
                break;
            case 0x2D9C40u:  // table[3]
                // 0x002d9c40
                charge(ctx, 3);
                v0 = 348;
                break;
            case 0x2D9C4Cu:  // table[4]
                // 0x002d9c4c
                charge(ctx, 3);
                v0 = 349;
                break;
            case 0x2D9C58u:  // table[5]
                // 0x002d9c58
                charge(ctx, 3);
                v0 = 350;
                break;
            case 0x2D9C64u:  // table[7]
                // 0x002d9c64
                charge(ctx, 3);
                v0 = 351;
                break;
            case 0x2D9C70u:  // table[8]
                // 0x002d9c70
                charge(ctx, 3);
                v0 = 352;
                break;
            case 0x2D9C7Cu:  // table[9]
                // 0x002d9c7c
                charge(ctx, 3);
                v0 = 353;
                break;
            case 0x2D9C88u:  // table[10]
                // 0x002d9c88
                charge(ctx, 3);
                v0 = 354;
                break;
            case 0x2D9C94u:  // table[0, 6]
            L_002d9c94:
                charge(ctx, 1);
                v0 = si(-1);
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
            // 0x002d9c98 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            return;
        }
        goto L_002d9c94;
    }
    // 0x002d9bf0
    charge(ctx, 3);
    v0 = si(-1);
    // 0x002d9c98 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x002D9D70 sub_2D9D70 -- 2712 bytes; frame 0x160: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlSupportPickStatusLine] The navigator's status report line: collects candidate lines (party low HP 372, ailments
// 399 / 410 / 419 / 428 / 445 / 454, the hero's persona situation 390..392, member 3's charm 437, three or more low
// HP 381, members absent from the battle with HP <= 30 % 382..389, a rare enemy 397, the count of enemies left
// 393..396, the hero's buffs 438..440), picks one at random (datCalcRand), skips a repeat of the last (+2608), adds
// the speaker offset; -1 for none or for an enemy turn.
// Arguments: a0 btlAction.
void sub_2D9D70(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002d9d70
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x160);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a0, act::kUnit);
    lbu(v0, v0, unit::kSide);
    if (v0 == 0) {
        // 0x002d9da8
        charge(ctx, 6);
        s2 = 0;
        s1 = 0;
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(s3, v0, gbtl::kUnitTail0);
        for (;;) {
            // 0x002da168
            charge(ctx, 2);
            if (s3 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002d9dc0
            charge(ctx, 6);
            lw(a0, s3, unit::kDat);
            a1 = 0;
            jal(ctx, 0x2D9DC8u, gen::fn_datCalcIsDead_0030b5a0);
            if (v0 == 0) {
                // 0x002d9dd8
                charge(ctx, 5);
                a0 = s3;
                jal(ctx, 0x2D9DDCu, gen::fn_sub_29A1D0_0029a1d0);
                if (v0 != 0) {
                    // 0x002d9dec
                    charge(ctx, 4);
                    lhu(v0, v0, 24);
                    v0 = v0 & 0x20;
                    if (v0 == 0) {
                        goto L_002d9dfc;
                    }
                    goto L_002da164;
                }
            L_002d9dfc:
                charge(ctx, 5);
                lw(a0, s3, unit::kDat);
                jal(ctx, 0x2D9E00u, gen::fn_datCalcIsLowHp_0030b5e0);
                if (v0 != 0) {
                    // 0x002d9e10
                    charge(ctx, 12);
                    v0 = s2 & 0xFFFF;
                    v0 = sll(v0, 2);
                    v0 = addu(v0, sp);
                    v1 = addiu(v0, 96);
                    v0 = 372;
                    sh(v0, v1, 0);
                    lhu(v0, s3, unit::kId);
                    sh(v0, v1, 2);
                    v0 = addiu(s2, 1);
                    s2 = v0 & 0xFFFF;
                    v0 = addiu(s1, 1);
                    s1 = v0 & 0xFFFF;
                }
                // 0x002d9e40
                charge(ctx, 6);
                lw(a0, s3, unit::kDat);
                a1 = 1;
                jal(ctx, 0x2D9E48u, gen::fn_datCalcChkBadStatus_00300580);
                if (v0 == 0) {
                    // 0x002d9e88
                    charge(ctx, 6);
                    lw(a0, s3, unit::kDat);
                    a1 = 4;
                    jal(ctx, 0x2D9E90u, gen::fn_datCalcChkBadStatus_00300580);
                    if (v0 == 0) {
                        // 0x002d9ed0
                        charge(ctx, 6);
                        lw(a0, s3, unit::kDat);
                        a1 = 8;
                        jal(ctx, 0x2D9ED8u, gen::fn_datCalcChkBadStatus_00300580);
                        if (v0 == 0) {
                            // 0x002d9f18
                            charge(ctx, 6);
                            lw(a0, s3, unit::kDat);
                            a1 = 16;
                            jal(ctx, 0x2D9F20u, gen::fn_datCalcChkBadStatus_00300580);
                            if (v0 == 0) {
                                // 0x002d9f60
                                charge(ctx, 6);
                                lw(a0, s3, unit::kDat);
                                a1 = 32;
                                jal(ctx, 0x2D9F68u, gen::fn_datCalcChkBadStatus_00300580);
                                if (v0 == 0) {
                                    // 0x002d9fa8
                                    charge(ctx, 6);
                                    lw(a0, s3, unit::kDat);
                                    a1 = 64;
                                    jal(ctx, 0x2D9FB0u, gen::fn_datCalcChkBadStatus_00300580);
                                    if (v0 != 0) {
                                        // 0x002d9fc0
                                        charge(ctx, 10);
                                        v0 = s2 & 0xFFFF;
                                        v0 = sll(v0, 2);
                                        v0 = addu(v0, sp);
                                        v1 = addiu(v0, 96);
                                        v0 = 454;
                                        sh(v0, v1, 0);
                                        lhu(v0, s3, unit::kId);
                                        sh(v0, v1, 2);
                                        v0 = addiu(s2, 1);
                                        s2 = v0 & 0xFFFF;
                                    }
                                } else {
                                    // 0x002d9f78
                                    charge(ctx, 12);
                                    v0 = s2 & 0xFFFF;
                                    v0 = sll(v0, 2);
                                    v0 = addu(v0, sp);
                                    v1 = addiu(v0, 96);
                                    v0 = 445;
                                    sh(v0, v1, 0);
                                    lhu(v0, s3, unit::kId);
                                    sh(v0, v1, 2);
                                    v0 = addiu(s2, 1);
                                    s2 = v0 & 0xFFFF;
                                }
                            } else {
                                // 0x002d9f30
                                charge(ctx, 12);
                                v0 = s2 & 0xFFFF;
                                v0 = sll(v0, 2);
                                v0 = addu(v0, sp);
                                v1 = addiu(v0, 96);
                                v0 = 428;
                                sh(v0, v1, 0);
                                lhu(v0, s3, unit::kId);
                                sh(v0, v1, 2);
                                v0 = addiu(s2, 1);
                                s2 = v0 & 0xFFFF;
                            }
                        } else {
                            // 0x002d9ee8
                            charge(ctx, 12);
                            v0 = s2 & 0xFFFF;
                            v0 = sll(v0, 2);
                            v0 = addu(v0, sp);
                            v1 = addiu(v0, 96);
                            v0 = 419;
                            sh(v0, v1, 0);
                            lhu(v0, s3, unit::kId);
                            sh(v0, v1, 2);
                            v0 = addiu(s2, 1);
                            s2 = v0 & 0xFFFF;
                        }
                    } else {
                        // 0x002d9ea0
                        charge(ctx, 12);
                        v0 = s2 & 0xFFFF;
                        v0 = sll(v0, 2);
                        v0 = addu(v0, sp);
                        v1 = addiu(v0, 96);
                        v0 = 410;
                        sh(v0, v1, 0);
                        lhu(v0, s3, unit::kId);
                        sh(v0, v1, 2);
                        v0 = addiu(s2, 1);
                        s2 = v0 & 0xFFFF;
                    }
                } else {
                    // 0x002d9e58
                    charge(ctx, 12);
                    v0 = s2 & 0xFFFF;
                    v0 = sll(v0, 2);
                    v0 = addu(v0, sp);
                    v1 = addiu(v0, 96);
                    v0 = 399;
                    sh(v0, v1, 0);
                    lhu(v0, s3, unit::kId);
                    sh(v0, v1, 2);
                    v0 = addiu(s2, 1);
                    s2 = v0 & 0xFFFF;
                }
                // 0x002d9fe8
                charge(ctx, 4);
                lhu(a0, s3, unit::kId);
                v0 = 1;
                if (a0 != v0) {
                    // 0x002d9ff8
                    charge(ctx, 3);
                    at = slti(a0, 11);
                    if (at != 0) {
                        // 0x002da004
                        charge(ctx, 5);
                        jal(ctx, 0x2DA004u, gen::fn_datPersonaGetByPcId_00174800);
                        a0 = v0;
                        jal(ctx, 0x2DA010u, gen::fn_sub_175CA0_00175ca0);
                    }
                }
                // 0x002da018
                charge(ctx, 4);
                lhu(v1, s3, unit::kId);
                v0 = 1;
                if (v1 == v0) {
                    // 0x002da028
                    charge(ctx, 5);
                    jal(ctx, 0x2DA028u, gen::fn_sub_17B170_0017b170);
                    at = slti(v0, 2);
                    if (at == 0) {
                        goto L_002da114;
                    }
                    // 0x002da03c
                    charge(ctx, 13);
                    v0 = s2 & 0xFFFF;
                    v0 = sll(v0, 2);
                    v0 = addu(v0, sp);
                    s0 = addiu(v0, 96);
                    v0 = si(-1);
                    sh(v0, s0, 0);
                    lh(a0, s3, unit::kId);
                    jal(ctx, 0x2DA058u, gen::fn_sub_16C920_0016c920);
                    v1 = v0 & 0xFFFF;
                    v0 = 5;
                    if (v1 == v0) {
                        // 0x002da0e8
                        charge(ctx, 2);
                        v0 = 392;
                        sh(v0, s0, 0);
                    } else {
                        // 0x002da070
                        charge(ctx, 3);
                        v0 = 4;
                        if (v1 == v0) {
                            // 0x002da0d8
                            charge(ctx, 4);
                            v0 = si(-1);
                            sh(v0, s0, 0);
                        } else {
                            // 0x002da07c
                            charge(ctx, 3);
                            v0 = 3;
                            if (v1 == v0) {
                                // 0x002da0c8
                                charge(ctx, 4);
                                v0 = 391;
                                sh(v0, s0, 0);
                            } else {
                                // 0x002da088
                                charge(ctx, 3);
                                v0 = 1;
                                if (v1 == v0) {
                                    // 0x002da0b8
                                    charge(ctx, 4);
                                    v0 = si(-1);
                                    sh(v0, s0, 0);
                                } else {
                                    // 0x002da094
                                    charge(ctx, 3);
                                    v0 = 2;
                                    if (v1 == v0) {
                                        // 0x002da0a8
                                        charge(ctx, 4);
                                        v0 = 390;
                                        sh(v0, s0, 0);
                                    } else {
                                        // 0x002da0a0
                                        charge(ctx, 2);
                                    }
                                }
                            }
                        }
                    }
                    // 0x002da0f0
                    charge(ctx, 3);
                    lh(v0, s0, 0);
                    if (i64(v0) >= 0) {
                        // 0x002da0fc
                        charge(ctx, 6);
                        v0 = si(-1);
                        sh(v0, s0, 2);
                        v0 = addiu(s2, 1);
                        s2 = v0 & 0xFFFF;
                    }
                    goto L_002da164;
                }
            L_002da114:
                charge(ctx, 4);
                lhu(v1, s3, unit::kId);
                v0 = 3;
                if (v1 == v0) {
                    // 0x002da124
                    charge(ctx, 6);
                    lw(a0, s3, unit::kDat);
                    a1 = 512;
                    jal(ctx, 0x2DA12Cu, gen::fn_datCalcChkBadStatus_00300580);
                    if (v0 != 0) {
                        // 0x002da13c
                        charge(ctx, 10);
                        v0 = s2 & 0xFFFF;
                        v0 = sll(v0, 2);
                        v0 = addu(v0, sp);
                        v1 = addiu(v0, 96);
                        v0 = 437;
                        sh(v0, v1, 0);
                        v0 = si(-1);
                        sh(v0, v1, 2);
                        v0 = addiu(s2, 1);
                        s2 = v0 & 0xFFFF;
                    }
                }
            }
        L_002da164:
            charge(ctx, 1);
            lw(s3, s3, unit::kPrev);
        }
        // 0x002da170
        charge(ctx, 4);
        v0 = s1 & 0xFFFF;
        v0 = slti(v0, 3);
        if (v0 == 0) {
            // 0x002da180
            charge(ctx, 9);
            v0 = s2 & 0xFFFF;
            v1 = sll(v0, 2);
            v0 = 381;
            v1 = addu(v1, sp);
            sh(v0, v1, 96);
            v0 = si(-1);
            sh(v0, v1, 98);
            v0 = addiu(s2, 1);
            s2 = v0 & 0xFFFF;
        }
        // 0x002da1a4
        charge(ctx, 3);
        s1 = 0;
        for (;;) {
            // 0x002da448
            charge(ctx, 4);
            a0 = s1 & 0xFFFF;
            v0 = slti(a0, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002da1b0
            charge(ctx, 5);
            jal(ctx, 0x2DA1B0u, gen::fn_sub_16DD60_0016dd60);
            s0 = v0 & 0xFFFF;
            if (i64(s0) > 0) {
                // 0x002da1c4
                charge(ctx, 3);
                at = slti(s0, 11);
                if (at != 0) {
                    // 0x002da1d0
                    charge(ctx, 6);
                    a0 = 0;
                    a1 = s0;
                    jal(ctx, 0x2DA1D8u, gen::fn_sub_288FE0_00288fe0);
                    if (v0 == 0) {
                        // 0x002da1e8
                        charge(ctx, 4);
                        a1 = 0;
                        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                        for (;;) {
                            // 0x002da230
                            charge(ctx, 4);
                            a0 = a1 & 0xFFFF;
                            v1 = sltiu(a0, 4);
                            if (v1 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x002da1f8
                            charge(ctx, 6);
                            v1 = a1 & 0xFFFF;
                            v1 = sll(v1, 2);
                            v1 = addu(v0, v1);
                            lw(v1, v1, 2988);
                            if (v1 != 0) {
                                // 0x002da210
                                charge(ctx, 3);
                                lw(v1, v1, 4);
                                if (v1 == 0) {
                                    goto L_002da228;
                                }
                                // 0x002da21c
                                charge(ctx, 3);
                                lhu(v1, v1, 2);
                                if (v1 != s0) {
                                    goto L_002da228;
                                }
                                break;
                            }
                        L_002da228:
                            charge(ctx, 2);
                            v1 = addiu(a1, 1);
                            a1 = v1 & 0xFFFF;
                        }
                        // 0x002da240
                        charge(ctx, 3);
                        v1 = 4;
                        if (a0 == v1) {
                            // 0x002da24c
                            charge(ctx, 3);
                            a1 = 0;
                            for (;;) {
                                // 0x002da290
                                charge(ctx, 4);
                                a0 = a1 & 0xFFFF;
                                v1 = sltiu(a0, 3);
                                if (v1 == 0) {
                                    break;
                                }
                                backedge(ctx);
                                // 0x002da258
                                charge(ctx, 6);
                                v1 = a1 & 0xFFFF;
                                v1 = sll(v1, 3);
                                v1 = addu(v0, v1);
                                lw(v1, v1, 3012);
                                if (v1 != 0) {
                                    // 0x002da270
                                    charge(ctx, 3);
                                    lw(v1, v1, 4);
                                    if (v1 == 0) {
                                        goto L_002da288;
                                    }
                                    // 0x002da27c
                                    charge(ctx, 3);
                                    lhu(v1, v1, 2);
                                    if (v1 != s0) {
                                        goto L_002da288;
                                    }
                                    break;
                                }
                            L_002da288:
                                charge(ctx, 2);
                                v1 = addiu(a1, 1);
                                a1 = v1 & 0xFFFF;
                            }
                            // 0x002da2a0
                            charge(ctx, 3);
                            v0 = 3;
                            if (a0 == v0) {
                                // 0x002da2ac
                                charge(ctx, 12);
                                s4 = dsll32(s0, 16);
                                s4 = dsra32(s4, 16);
                                a0 = s4;
                                jal(ctx, 0x2DA2B8u, gen::fn_sub_16C4F0_0016c4f0);
                                s3 = v0 & 0xFFFF;
                                a0 = s4;
                                jal(ctx, 0x2DA2C8u, gen::fn_sub_16C970_0016c970);
                                s3 = s3 & 0xFFFF;
                                if (s3 != 0) {
                                    // 0x002da2dc
                                    charge(ctx, 4);
                                    v1 = 0x80000;
                                    v0 = v0 & v1;
                                    if (v0 == 0) {
                                        // 0x002da2ec
                                        charge(ctx, 14);
                                        a0 = s4;
                                        jal(ctx, 0x2DA2F0u, gen::fn_sub_16C5F0_0016c5f0);
                                        a0 = v0 & 0xFFFF;
                                        v0 = sll(s3, 2);
                                        v1 = addu(v0, s3);
                                        v0 = sll(v1, 2);
                                        v0 = addu(v1, v0);
                                        v0 = sll(v0, 2);
                                        div(v0, a0);
                                        mflo(v0);
                                        at = slti(v0, 31);
                                        if (at != 0) {
                                            // 0x002da324
                                            charge(ctx, 3);
                                            at = sltiu(s0, 11);
                                            if (at != 0) {
                                                // 0x002da330
                                                charge(ctx, 7);
                                                v1 = 0x7B0000;
                                                v1 = addiu(v1, 32640);  // &0x7B7F80
                                                v0 = sll(s0, 2);
                                                v0 = addu(v0, v1);
                                                lw(v0, v0, 0);
                                                switch (v0.u()) {
                                                case 0x2DA34Cu:  // table[2]
                                                    // 0x002da34c
                                                    charge(ctx, 7);
                                                    v1 = 382;
                                                    v0 = s2 & 0xFFFF;
                                                    v0 = sll(v0, 2);
                                                    v0 = addu(v0, sp);
                                                    sh(v1, v0, 96);
                                                    break;
                                                case 0x2DA368u:  // table[3]
                                                    // 0x002da368
                                                    charge(ctx, 7);
                                                    v1 = 383;
                                                    v0 = s2 & 0xFFFF;
                                                    v0 = sll(v0, 2);
                                                    v0 = addu(v0, sp);
                                                    sh(v1, v0, 96);
                                                    break;
                                                case 0x2DA384u:  // table[4]
                                                    // 0x002da384
                                                    charge(ctx, 7);
                                                    v1 = 384;
                                                    v0 = s2 & 0xFFFF;
                                                    v0 = sll(v0, 2);
                                                    v0 = addu(v0, sp);
                                                    sh(v1, v0, 96);
                                                    break;
                                                case 0x2DA3A0u:  // table[5]
                                                    // 0x002da3a0
                                                    charge(ctx, 7);
                                                    v1 = 385;
                                                    v0 = s2 & 0xFFFF;
                                                    v0 = sll(v0, 2);
                                                    v0 = addu(v0, sp);
                                                    sh(v1, v0, 96);
                                                    break;
                                                case 0x2DA3BCu:  // table[7]
                                                    // 0x002da3bc
                                                    charge(ctx, 7);
                                                    v1 = 386;
                                                    v0 = s2 & 0xFFFF;
                                                    v0 = sll(v0, 2);
                                                    v0 = addu(v0, sp);
                                                    sh(v1, v0, 96);
                                                    break;
                                                case 0x2DA3D8u:  // table[8]
                                                    // 0x002da3d8
                                                    charge(ctx, 7);
                                                    v1 = 387;
                                                    v0 = s2 & 0xFFFF;
                                                    v0 = sll(v0, 2);
                                                    v0 = addu(v0, sp);
                                                    sh(v1, v0, 96);
                                                    break;
                                                case 0x2DA3F4u:  // table[9]
                                                    // 0x002da3f4
                                                    charge(ctx, 7);
                                                    v1 = 388;
                                                    v0 = s2 & 0xFFFF;
                                                    v0 = sll(v0, 2);
                                                    v0 = addu(v0, sp);
                                                    sh(v1, v0, 96);
                                                    break;
                                                case 0x2DA410u:  // table[10]
                                                    // 0x002da410
                                                    charge(ctx, 5);
                                                    v1 = 389;
                                                    v0 = s2 & 0xFFFF;
                                                    v0 = sll(v0, 2);
                                                    v0 = addu(v0, sp);
                                                    sh(v1, v0, 96);
                                                    break;
                                                case 0x2DA424u:  // table[0, 1, 6]
                                                    break;
                                                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                                                    tail(ctx, v0.u());
                                                    return;
                                                }
                                            }
                                            // 0x002da424
                                            charge(ctx, 7);
                                            v1 = si(-1);
                                            v0 = s2 & 0xFFFF;
                                            v0 = sll(v0, 2);
                                            v0 = addu(v0, sp);
                                            sh(v1, v0, 98);
                                            v0 = addiu(s2, 1);
                                            s2 = v0 & 0xFFFF;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            // 0x002da440
            charge(ctx, 2);
            v0 = addiu(s1, 1);
            s1 = v0 & 0xFFFF;
        }
        // 0x002da458
        charge(ctx, 7);
        a3 = 0;
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(a2, v0, gbtl4::kUnitTail1);
        lw(a1, gp, kGpEnemyTbl);  // gBtlEnemyTbl
        v0 = 1;
        for (;;) {
            // 0x002da4a0
            charge(ctx, 2);
            if (a2 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002da474
            charge(ctx, 9);
            lhu(a0, a2, unit::kId);
            v1 = sll(a0, 5);
            v1 = subu(v1, a0);
            v1 = sll(v1, 1);
            v1 = addu(a1, v1);
            lhu(v1, v1, 0);
            v1 = v1 & 0x40;
            if (v1 != 0) {
                // 0x002da498
                charge(ctx, 1);
                a3 = v0;
            }
            // 0x002da49c
            charge(ctx, 1);
            lw(a2, a2, unit::kPrev);
        }
        // 0x002da4a8
        charge(ctx, 2);
        if (a3 != 0) {
            // 0x002da4b0
            charge(ctx, 9);
            v0 = s2 & 0xFFFF;
            v1 = sll(v0, 2);
            v0 = 397;
            v1 = addu(v1, sp);
            sh(v0, v1, 96);
            v0 = si(-1);
            sh(v0, v1, 98);
            v0 = addiu(s2, 1);
            s2 = v0 & 0xFFFF;
        }
        // 0x002da4d4
        charge(ctx, 10);
        a0 = 2;
        a1 = 0x80000;
        jal(ctx, 0x2DA4DCu, gen::fn_btlCountActiveUnits_002d4e10);
        a0 = v0 & 0xFFFF;
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        v1 = addiu(v0, 2612);
        lh(v0, v0, gbtl4::kEnemiesLeft);
        if (v0 != a0) {
            // 0x002da53c
            charge(ctx, 1);
            sh(a0, v1, 0);
        } else {
            // 0x002da4fc
            charge(ctx, 3);
            at = slti(a0, 5);
            if (at != 0) {
                // 0x002da508
                charge(ctx, 2);
                if (i64(a0) > 0) {
                    // 0x002da510
                    charge(ctx, 11);
                    v0 = s2 & 0xFFFF;
                    v1 = sll(v0, 2);
                    v0 = addiu(a0, 392);
                    v1 = addu(v1, sp);
                    sh(v0, v1, 96);
                    v0 = si(-1);
                    sh(v0, v1, 98);
                    v0 = addiu(s2, 1);
                    s2 = v0 & 0xFFFF;
                }
            }
        }
        // 0x002da540
        charge(ctx, 9);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(v0, v0, gbtl::kPlayerAction);
        lw(v0, v0, act::kUnit);
        lw(a0, v0, unit::kDat);
        a1 = 10;
        jal(ctx, 0x2DA554u, gen::fn_sub_301CA0_00301ca0);
        if (v0 != 0) {
            // 0x002da564
            charge(ctx, 9);
            v0 = s2 & 0xFFFF;
            v1 = sll(v0, 2);
            v0 = 438;
            v1 = addu(v1, sp);
            sh(v0, v1, 96);
            v0 = si(-1);
            sh(v0, v1, 98);
            v0 = addiu(s2, 1);
            s2 = v0 & 0xFFFF;
        }
        // 0x002da588
        charge(ctx, 9);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(v0, v0, gbtl::kPlayerAction);
        lw(v0, v0, act::kUnit);
        lw(a0, v0, unit::kDat);
        a1 = 128;
        jal(ctx, 0x2DA59Cu, gen::fn_sub_301CA0_00301ca0);
        if (v0 != 0) {
            // 0x002da5ac
            charge(ctx, 9);
            v0 = s2 & 0xFFFF;
            v1 = sll(v0, 2);
            v0 = 439;
            v1 = addu(v1, sp);
            sh(v0, v1, 96);
            v0 = si(-1);
            sh(v0, v1, 98);
            v0 = addiu(s2, 1);
            s2 = v0 & 0xFFFF;
        }
        // 0x002da5d0
        charge(ctx, 9);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(v0, v0, gbtl::kPlayerAction);
        lw(v0, v0, act::kUnit);
        lw(a0, v0, unit::kDat);
        a1 = 544;
        jal(ctx, 0x2DA5E4u, gen::fn_sub_301CA0_00301ca0);
        if (v0 != 0) {
            // 0x002da5f4
            charge(ctx, 9);
            v0 = s2 & 0xFFFF;
            v1 = sll(v0, 2);
            v0 = 440;
            v1 = addu(v1, sp);
            sh(v0, v1, 96);
            v0 = si(-1);
            sh(v0, v1, 98);
            v0 = addiu(s2, 1);
            s2 = v0 & 0xFFFF;
        }
        // 0x002da618
        charge(ctx, 11);
        jal(ctx, 0x2DA618u, gen::fn_sub_175360_00175360);
        a0 = v0;
        jal(ctx, 0x2DA624u, gen::fn_sub_174A90_00174a90);
        s0 = v0;
        jal(ctx, 0x2DA630u, gen::fn_btlGetEncounterId_002d5550);
        v1 = 429;
        if (v0 != v1) {
            // 0x002da644
            charge(ctx, 4);
            lhu(v1, s0, 2);
            v0 = 191;
            if (v1 != v0) {
                // 0x002da654
                charge(ctx, 9);
                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                lw(v0, v0, gbtl::kPlayerAction);
                lw(v0, v0, act::kUnit);
                lw(a0, v0, unit::kDat);
                a1 = 609;
                jal(ctx, 0x2DA668u, gen::fn_datCalcHasSkill_003005e0);
                if (v0 == 0) {
                    goto L_002da678;
                }
            }
            goto L_002da684;
        }
    L_002da678:
        charge(ctx, 3);
        a0 = s0;
        jal(ctx, 0x2DA67Cu, gen::fn_sub_175CA0_00175ca0);
    L_002da684:
        charge(ctx, 3);
        a0 = s2 & 0xFFFF;
        if (i64(a0) > 0) {
            // 0x002da69c
            charge(ctx, 12);
            jal(ctx, 0x2DA69Cu, gen::fn_datCalcRand_002ffbc0);
            v0 = v0 & 0xFFFF;
            v0 = sll(v0, 2);
            a0 = addu(v0, sp);
            v0 = addiu(a0, 96);
            lh(a1, v0, 0);
            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
            v1 = addiu(v0, 2608);
            lw(v0, v0, gbtl4::kLastStatusLine);
            if (v0 != a1) {
                // 0x002da6d8
                charge(ctx, 5);
                sw(a1, v1, 0);
                v0 = addiu(a0, 98);
                lh(a0, v0, 0);
                if (i64(a0) >= 0) {
                    // 0x002da6ec
                    charge(ctx, 3);
                    v0 = 399;
                    if (a1 == v0) {
                        // 0x002da6f8
                        charge(ctx, 3);
                        v0 = 1;
                        if (a0 == v0) {
                            // 0x002da718
                            charge(ctx, 1);
                            a1 = si(-1);
                        } else {
                            // 0x002da704
                            charge(ctx, 5);
                            v0 = addiu(a1, 2);
                            a1 = dsll32(v0, 16);
                            a1 = dsra32(a1, 16);
                        }
                    }
                    // 0x002da71c
                    charge(ctx, 3);
                    at = sltiu(a0, 11);
                    if (at != 0) {
                        // 0x002da728
                        charge(ctx, 7);
                        v1 = 0x7B0000;
                        v1 = addiu(v1, 32592);  // &0x7B7F50
                        v0 = sll(a0, 2);
                        v0 = addu(v0, v1);
                        lw(v0, v0, 0);
                        switch (v0.u()) {
                        case 0x2DA744u:  // table[2]
                            // 0x002da744
                            charge(ctx, 5);
                            v0 = addiu(a1, 1);
                            a1 = dsll32(v0, 16);
                            a1 = dsra32(a1, 16);
                            break;
                        case 0x2DA758u:  // table[3]
                            // 0x002da758
                            charge(ctx, 5);
                            v0 = addiu(a1, 2);
                            a1 = dsll32(v0, 16);
                            a1 = dsra32(a1, 16);
                            break;
                        case 0x2DA76Cu:  // table[4]
                            // 0x002da76c
                            charge(ctx, 5);
                            v0 = addiu(a1, 3);
                            a1 = dsll32(v0, 16);
                            a1 = dsra32(a1, 16);
                            break;
                        case 0x2DA780u:  // table[5]
                            // 0x002da780
                            charge(ctx, 5);
                            v0 = addiu(a1, 4);
                            a1 = dsll32(v0, 16);
                            a1 = dsra32(a1, 16);
                            break;
                        case 0x2DA794u:  // table[7]
                            // 0x002da794
                            charge(ctx, 5);
                            v0 = addiu(a1, 5);
                            a1 = dsll32(v0, 16);
                            a1 = dsra32(a1, 16);
                            break;
                        case 0x2DA7A8u:  // table[8]
                            // 0x002da7a8
                            charge(ctx, 5);
                            v0 = addiu(a1, 6);
                            a1 = dsll32(v0, 16);
                            a1 = dsra32(a1, 16);
                            break;
                        case 0x2DA7BCu:  // table[9]
                            // 0x002da7bc
                            charge(ctx, 5);
                            v0 = addiu(a1, 7);
                            a1 = dsll32(v0, 16);
                            a1 = dsra32(a1, 16);
                            break;
                        case 0x2DA7D0u:  // table[10]
                            // 0x002da7d0
                            charge(ctx, 3);
                            v0 = addiu(a1, 8);
                            a1 = dsll32(v0, 16);
                            a1 = dsra32(a1, 16);
                            break;
                        case 0x2DA7DCu:  // table[0, 1, 6]
                            break;
                        default:  // not one of the table's targets: the dispatch table, as the recompiled body
                            tail(ctx, v0.u());
                            return;
                        }
                    }
                }
                // 0x002da7dc
                charge(ctx, 2);
                v0 = dsll32(a1, 16);
                v0 = dsra32(v0, 16);
            } else {
                // 0x002da6cc
                charge(ctx, 3);
                v0 = si(-1);
            }
        } else {
            // 0x002da690
            charge(ctx, 3);
            v0 = si(-1);
        }
    } else {
        // 0x002d9d9c
        charge(ctx, 3);
        v0 = si(-1);
    }
    // 0x002da7e4 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x160);
}

// 0x002DD270 sub_2DD270 -- 124 bytes; frame 0xA0: ra sp+0x10, s0 sp+0x0 (sq)
// Hold callback of the skill sound packet: requests "skill/%03X.se" unless flag 1; +6 = 1.
// Arguments: a0 packet data.
void sub_2DD270(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002dd270
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lhu(v1, a0, 12);
    v1 = v1 & 0x1;
    if (v1 != 0) {
        // 0x002dd2c8
        charge(ctx, 1);
        sw(zero, s0, 8);
    } else {
        // 0x002dd290
        charge(ctx, 14);
        lhu(a3, s0, 4);
        a0 = addiu(sp, 0x20);
        a1 = 0x690000;
        a1 = addiu(a1, 31648);  // "%s%03X.se"
        a2 = addiu(gp, -25464);  // "skill/"
        jal(ctx, 0x2DD2A4u, gen::fn_sprintf_00523ac8);
        a0 = addiu(sp, 0x20);
        a1 = 0;
        jal(ctx, 0x2DD2B4u, gen::fn_H_Cdvd_Request_00100d80);
        sw(v0, s0, 8);
    }
    // 0x002dd2cc (the shared epilogue, written out on this path)
    charge(ctx, 8);
    v1 = 1;
    sh(v1, s0, 6);
    sw(zero, s0, 0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// 0x002DD690 sub_2DD690 -- 132 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlPktCreateMessage] Creates the message packet 2309 (the text copied after an 8-byte header: u16 a0, the text
// pointer) with the update sub_2DD630.
// Arguments: a0 id, a1 text.
void sub_2DD690(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002dd690
    enter(ctx, 33);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    a0 = s1;
    jal(ctx, 0x2DD6B0u, gen::fn_strlen_00524388);
    a1 = addiu(v0, 8);
    a0 = 2309;
    jal(ctx, 0x2DD6C0u, gen::fn_sub_27EC10_0027ec10);
    s0 = v0;
    v1 = 0x2E0000;
    v1 = addiu(v1, -10704);  // &sub_2DD630
    sw(v1, v0, pkt::kUpdate);
    lw(v0, v0, pkt::kData);
    sh(s2, v0, 0);
    a0 = addiu(v0, 8);
    sw(a0, v0, 4);
    a1 = s1;
    jal(ctx, 0x2DD6ECu, gen::fn_strcpy_00524270);
    v0 = s0;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x002DD8E0 sub_2DD8E0 -- 72 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Creates packet 2313 (4 bytes: a0) with the update sub_2DD8B0.
// Arguments: a0.
void sub_2DD8E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002dd8e0
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 2313;
    a1 = 4;
    jal(ctx, 0x2DD8F8u, gen::fn_sub_27EC10_0027ec10);
    v1 = 0x2E0000;
    v1 = addiu(v1, -10064);  // &sub_2DD8B0
    sw(v1, v0, pkt::kUpdate);
    lw(v1, v0, pkt::kData);
    sw(s0, v1, 0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002DD960 sub_2DD960 -- 72 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Creates packet 2314 (4 bytes: a0) with the update sub_2DD930.
// Arguments: a0.
void sub_2DD960(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002dd960
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 2314;
    a1 = 4;
    jal(ctx, 0x2DD978u, gen::fn_sub_27EC10_0027ec10);
    v1 = 0x2E0000;
    v1 = addiu(v1, -9936);  // &sub_2DD930
    sw(v1, v0, pkt::kUpdate);
    lw(v1, v0, pkt::kData);
    sw(s0, v1, 0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002E0620 sub_2E0620 -- 2384 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlVoicePickEventLine] A unit's voice line for an event (a1): the boss enemies 233..240 / 264 / 271 / 272 ... by
// their own tables (boss 234 by the event 192..211), party members by id and event, some once (datGetFlag /
// datSetFlag) or at random; -1 for none or without a camera object.
// Arguments: a0 btlAction, a1 event.
void sub_2E0620(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e0620
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lw(a0, a0, act::kUnit);
    lw(v0, a0, unit::kCamObj);
    if (v0 != 0) {
        // 0x002e0654
        charge(ctx, 4);
        lbu(v1, a0, unit::kSide);
        v0 = 1;
        if (v1 != v0) {
            // 0x002e08a0
            charge(ctx, 4);
            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
            lw(v0, v0, gbtl::kPlayerAction);
            if (v0 != s1) {
                // 0x002e0920
                charge(ctx, 4);
                lhu(v0, a0, unit::kId);
                at = sltiu(v0, 11);
                if (at != 0) {
                    // 0x002e0930
                    charge(ctx, 7);
                    v1 = 0x7C0000;
                    v1 = addiu(v1, -31600);  // &0x7B8490
                    v0 = sll(v0, 2);
                    v0 = addu(v0, v1);
                    lw(v0, v0, 0);
                    switch (v0.u()) {
                    case 0x2E094Cu:  // table[2]
                        // 0x002e094c
                        charge(ctx, 5);
                        a0 = 4951;
                        jal(ctx, 0x2E0950u, gen::fn_datGetFlag_0016f190);
                        if (v0 != 0) {
                            // 0x002e097c
                            charge(ctx, 6);
                            a0 = 100;
                            jal(ctx, 0x2E0980u, gen::fn_datCalcRand_002ffbc0);
                            v0 = sltiu(v0, 50);
                            if (v0 != 0) {
                                // 0x002e09dc
                                charge(ctx, 6);
                                lw(v0, s1, act::kUnit);
                                lw(v0, v0, unit::kCamObj);
                                lhu(v1, v0, 164);
                                v0 = 192;
                                if (v1 != v0) {
                                    // 0x002e0a00
                                    charge(ctx, 1);
                                    v0 = 170;
                                } else {
                                    // 0x002e09f4
                                    charge(ctx, 3);
                                    v0 = 169;
                                }
                                // 0x002e0a04
                                charge(ctx, 2);
                            } else {
                                // 0x002e0994
                                charge(ctx, 5);
                                v0 = 0x690000;
                                lw(a0, v0, 31712);  // 0x697BE0
                                v0 = si(-1);
                                if (a0 != v0) {
                                    // 0x002e09b4
                                    charge(ctx, 2);
                                    jal(ctx, 0x2E09B4u, gen::fn_datGetFlag_0016f190);
                                } else {
                                    // 0x002e09a8
                                    charge(ctx, 3);
                                    v0 = 0;
                                }
                                // 0x002e09bc
                                charge(ctx, 2);
                                if (v0 == 0) {
                                    // 0x002e09d0
                                    charge(ctx, 1);
                                    v0 = 166;
                                } else {
                                    // 0x002e09c4
                                    charge(ctx, 3);
                                    v0 = 167;
                                }
                                // 0x002e09d4
                                charge(ctx, 2);
                            }
                        } else {
                            // 0x002e0960
                            charge(ctx, 7);
                            a0 = 4951;
                            a1 = 1;
                            jal(ctx, 0x2E0968u, gen::fn_datSetFlag_0016f1f0);
                            v0 = 168;
                        }
                        break;
                    case 0x2E0A0Cu:  // table[3]
                        // 0x002e0a0c
                        charge(ctx, 5);
                        a0 = 4952;
                        jal(ctx, 0x2E0A10u, gen::fn_datGetFlag_0016f190);
                        if (v0 != 0) {
                            // 0x002e0a3c
                            charge(ctx, 6);
                            a0 = 100;
                            jal(ctx, 0x2E0A40u, gen::fn_datCalcRand_002ffbc0);
                            v0 = sltiu(v0, 50);
                            if (v0 != 0) {
                                // 0x002e0a9c
                                charge(ctx, 6);
                                lw(v0, s1, act::kUnit);
                                lw(v0, v0, unit::kCamObj);
                                lhu(v1, v0, 164);
                                v0 = 194;
                                if (v1 != v0) {
                                    // 0x002e0ac0
                                    charge(ctx, 1);
                                    v0 = 251;
                                } else {
                                    // 0x002e0ab4
                                    charge(ctx, 3);
                                    v0 = 250;
                                }
                                // 0x002e0ac4
                                charge(ctx, 2);
                            } else {
                                // 0x002e0a54
                                charge(ctx, 5);
                                v0 = 0x690000;
                                lw(a0, v0, 31716);  // 0x697BE4
                                v0 = si(-1);
                                if (a0 != v0) {
                                    // 0x002e0a74
                                    charge(ctx, 2);
                                    jal(ctx, 0x2E0A74u, gen::fn_datGetFlag_0016f190);
                                } else {
                                    // 0x002e0a68
                                    charge(ctx, 3);
                                    v0 = 0;
                                }
                                // 0x002e0a7c
                                charge(ctx, 2);
                                if (v0 == 0) {
                                    // 0x002e0a90
                                    charge(ctx, 1);
                                    v0 = 247;
                                } else {
                                    // 0x002e0a84
                                    charge(ctx, 3);
                                    v0 = 248;
                                }
                                // 0x002e0a94
                                charge(ctx, 2);
                            }
                        } else {
                            // 0x002e0a20
                            charge(ctx, 7);
                            a0 = 4952;
                            a1 = 1;
                            jal(ctx, 0x2E0A28u, gen::fn_datSetFlag_0016f1f0);
                            v0 = 249;
                        }
                        break;
                    case 0x2E0ACCu:  // table[4]
                        // 0x002e0acc
                        charge(ctx, 5);
                        a0 = 4953;
                        jal(ctx, 0x2E0AD0u, gen::fn_datGetFlag_0016f190);
                        if (v0 != 0) {
                            // 0x002e0afc
                            charge(ctx, 6);
                            a0 = 100;
                            jal(ctx, 0x2E0B00u, gen::fn_datCalcRand_002ffbc0);
                            v0 = sltiu(v0, 50);
                            if (v0 != 0) {
                                // 0x002e0b5c
                                charge(ctx, 6);
                                lw(v0, s1, act::kUnit);
                                lw(v0, v0, unit::kCamObj);
                                lhu(v1, v0, 164);
                                v0 = 196;
                                if (v1 != v0) {
                                    // 0x002e0b80
                                    charge(ctx, 1);
                                    v0 = 352;
                                } else {
                                    // 0x002e0b74
                                    charge(ctx, 3);
                                    v0 = 351;
                                }
                                // 0x002e0b84
                                charge(ctx, 2);
                            } else {
                                // 0x002e0b14
                                charge(ctx, 5);
                                v0 = 0x690000;
                                lw(a0, v0, 31720);  // 0x697BE8
                                v0 = si(-1);
                                if (a0 != v0) {
                                    // 0x002e0b34
                                    charge(ctx, 2);
                                    jal(ctx, 0x2E0B34u, gen::fn_datGetFlag_0016f190);
                                } else {
                                    // 0x002e0b28
                                    charge(ctx, 3);
                                    v0 = 0;
                                }
                                // 0x002e0b3c
                                charge(ctx, 2);
                                if (v0 == 0) {
                                    // 0x002e0b50
                                    charge(ctx, 1);
                                    v0 = 348;
                                } else {
                                    // 0x002e0b44
                                    charge(ctx, 3);
                                    v0 = 349;
                                }
                                // 0x002e0b54
                                charge(ctx, 2);
                            }
                        } else {
                            // 0x002e0ae0
                            charge(ctx, 7);
                            a0 = 4953;
                            a1 = 1;
                            jal(ctx, 0x2E0AE8u, gen::fn_datSetFlag_0016f1f0);
                            v0 = 350;
                        }
                        break;
                    case 0x2E0B8Cu:  // table[5]
                        // 0x002e0b8c
                        charge(ctx, 5);
                        a0 = 4954;
                        jal(ctx, 0x2E0B90u, gen::fn_datGetFlag_0016f190);
                        if (v0 != 0) {
                            // 0x002e0bbc
                            charge(ctx, 6);
                            a0 = 100;
                            jal(ctx, 0x2E0BC0u, gen::fn_datCalcRand_002ffbc0);
                            v0 = sltiu(v0, 50);
                            if (v0 != 0) {
                                // 0x002e0c1c
                                charge(ctx, 6);
                                lw(v0, s1, act::kUnit);
                                lw(v0, v0, unit::kCamObj);
                                lhu(v1, v0, 164);
                                v0 = 198;
                                if (v1 != v0) {
                                    // 0x002e0c40
                                    charge(ctx, 1);
                                    v0 = 425;
                                } else {
                                    // 0x002e0c34
                                    charge(ctx, 3);
                                    v0 = 424;
                                }
                                // 0x002e0c44
                                charge(ctx, 2);
                            } else {
                                // 0x002e0bd4
                                charge(ctx, 5);
                                v0 = 0x690000;
                                lw(a0, v0, 31724);  // 0x697BEC
                                v0 = si(-1);
                                if (a0 != v0) {
                                    // 0x002e0bf4
                                    charge(ctx, 2);
                                    jal(ctx, 0x2E0BF4u, gen::fn_datGetFlag_0016f190);
                                } else {
                                    // 0x002e0be8
                                    charge(ctx, 3);
                                    v0 = 0;
                                }
                                // 0x002e0bfc
                                charge(ctx, 2);
                                if (v0 == 0) {
                                    // 0x002e0c10
                                    charge(ctx, 1);
                                    v0 = 421;
                                } else {
                                    // 0x002e0c04
                                    charge(ctx, 3);
                                    v0 = 422;
                                }
                                // 0x002e0c14
                                charge(ctx, 2);
                            }
                        } else {
                            // 0x002e0ba0
                            charge(ctx, 7);
                            a0 = 4954;
                            a1 = 1;
                            jal(ctx, 0x2E0BA8u, gen::fn_datSetFlag_0016f1f0);
                            v0 = 423;
                        }
                        break;
                    case 0x2E0C4Cu:  // table[7]
                        // 0x002e0c4c
                        charge(ctx, 5);
                        a0 = 4955;
                        jal(ctx, 0x2E0C50u, gen::fn_datGetFlag_0016f190);
                        if (v0 != 0) {
                            // 0x002e0c7c
                            charge(ctx, 6);
                            a0 = 100;
                            jal(ctx, 0x2E0C80u, gen::fn_datCalcRand_002ffbc0);
                            v0 = sltiu(v0, 50);
                            if (v0 != 0) {
                                // 0x002e0cdc
                                charge(ctx, 6);
                                lw(v0, s1, act::kUnit);
                                lw(v0, v0, unit::kCamObj);
                                lhu(v1, v0, 164);
                                v0 = 202;
                                if (v1 != v0) {
                                    // 0x002e0d00
                                    charge(ctx, 1);
                                    v0 = 498;
                                } else {
                                    // 0x002e0cf4
                                    charge(ctx, 3);
                                    v0 = 497;
                                }
                                // 0x002e0d04
                                charge(ctx, 2);
                            } else {
                                // 0x002e0c94
                                charge(ctx, 5);
                                v0 = 0x690000;
                                lw(a0, v0, 31732);  // 0x697BF4
                                v0 = si(-1);
                                if (a0 != v0) {
                                    // 0x002e0cb4
                                    charge(ctx, 2);
                                    jal(ctx, 0x2E0CB4u, gen::fn_datGetFlag_0016f190);
                                } else {
                                    // 0x002e0ca8
                                    charge(ctx, 3);
                                    v0 = 0;
                                }
                                // 0x002e0cbc
                                charge(ctx, 2);
                                if (v0 == 0) {
                                    // 0x002e0cd0
                                    charge(ctx, 1);
                                    v0 = 494;
                                } else {
                                    // 0x002e0cc4
                                    charge(ctx, 3);
                                    v0 = 495;
                                }
                                // 0x002e0cd4
                                charge(ctx, 2);
                            }
                        } else {
                            // 0x002e0c60
                            charge(ctx, 7);
                            a0 = 4955;
                            a1 = 1;
                            jal(ctx, 0x2E0C68u, gen::fn_datSetFlag_0016f1f0);
                            v0 = 496;
                        }
                        break;
                    case 0x2E0D0Cu:  // table[8]
                        // 0x002e0d0c
                        charge(ctx, 5);
                        a0 = 4956;
                        jal(ctx, 0x2E0D10u, gen::fn_datGetFlag_0016f190);
                        if (v0 != 0) {
                            // 0x002e0d3c
                            charge(ctx, 6);
                            a0 = 100;
                            jal(ctx, 0x2E0D40u, gen::fn_datCalcRand_002ffbc0);
                            v0 = sltiu(v0, 50);
                            if (v0 != 0) {
                                // 0x002e0d9c
                                charge(ctx, 6);
                                lw(v0, s1, act::kUnit);
                                lw(v0, v0, unit::kCamObj);
                                lhu(v1, v0, 164);
                                v0 = 204;
                                if (v1 != v0) {
                                    // 0x002e0dc0
                                    charge(ctx, 1);
                                    v0 = 571;
                                } else {
                                    // 0x002e0db4
                                    charge(ctx, 3);
                                    v0 = 570;
                                }
                                // 0x002e0dc4
                                charge(ctx, 2);
                            } else {
                                // 0x002e0d54
                                charge(ctx, 5);
                                v0 = 0x690000;
                                lw(a0, v0, 31736);  // 0x697BF8
                                v0 = si(-1);
                                if (a0 != v0) {
                                    // 0x002e0d74
                                    charge(ctx, 2);
                                    jal(ctx, 0x2E0D74u, gen::fn_datGetFlag_0016f190);
                                } else {
                                    // 0x002e0d68
                                    charge(ctx, 3);
                                    v0 = 0;
                                }
                                // 0x002e0d7c
                                charge(ctx, 2);
                                if (v0 == 0) {
                                    // 0x002e0d90
                                    charge(ctx, 1);
                                    v0 = 567;
                                } else {
                                    // 0x002e0d84
                                    charge(ctx, 3);
                                    v0 = 568;
                                }
                                // 0x002e0d94
                                charge(ctx, 2);
                            }
                        } else {
                            // 0x002e0d20
                            charge(ctx, 7);
                            a0 = 4956;
                            a1 = 1;
                            jal(ctx, 0x2E0D28u, gen::fn_datSetFlag_0016f1f0);
                            v0 = 569;
                        }
                        break;
                    case 0x2E0DCCu:  // table[9]
                        // 0x002e0dcc
                        charge(ctx, 5);
                        a0 = 4957;
                        jal(ctx, 0x2E0DD0u, gen::fn_datGetFlag_0016f190);
                        if (v0 != 0) {
                            // 0x002e0e18
                            charge(ctx, 6);
                            a0 = 100;
                            jal(ctx, 0x2E0E1Cu, gen::fn_datCalcRand_002ffbc0);
                            v0 = sltiu(v0, 50);
                            if (v0 != 0) {
                                // 0x002e0e90
                                charge(ctx, 4);
                                jal(ctx, 0x2E0E90u, gen::fn_sub_17D800_0017d800);
                                if (v0 == 0) {
                                    // 0x002e0eac
                                    charge(ctx, 1);
                                    v0 = 637;
                                } else {
                                    // 0x002e0ea0
                                    charge(ctx, 3);
                                    v0 = 1134;
                                }
                                // 0x002e0eb0
                                charge(ctx, 2);
                            } else {
                                // 0x002e0e30
                                charge(ctx, 4);
                                jal(ctx, 0x2E0E30u, gen::fn_sub_17D800_0017d800);
                                if (v0 != 0) {
                                    // 0x002e0e68
                                    charge(ctx, 5);
                                    v0 = 0x690000;
                                    lw(a0, v0, 31740);  // 0x697BFC
                                    v0 = si(-1);
                                    if (a0 != v0) {
                                        // 0x002e0e7c
                                        charge(ctx, 2);
                                        jal(ctx, 0x2E0E7Cu, gen::fn_datGetFlag_0016f190);
                                    }
                                    // 0x002e0e84
                                    charge(ctx, 3);
                                    v0 = 1132;
                                } else {
                                    // 0x002e0e40
                                    charge(ctx, 5);
                                    v0 = 0x690000;
                                    lw(a0, v0, 31740);  // 0x697BFC
                                    v0 = si(-1);
                                    if (a0 != v0) {
                                        // 0x002e0e54
                                        charge(ctx, 2);
                                        jal(ctx, 0x2E0E54u, gen::fn_datGetFlag_0016f190);
                                    }
                                    // 0x002e0e5c
                                    charge(ctx, 3);
                                    v0 = 635;
                                }
                            }
                        } else {
                            // 0x002e0de0
                            charge(ctx, 8);
                            a0 = 4957;
                            a1 = 1;
                            jal(ctx, 0x2E0DE8u, gen::fn_datSetFlag_0016f1f0);
                            jal(ctx, 0x2E0DF0u, gen::fn_sub_17D800_0017d800);
                            if (v0 == 0) {
                                // 0x002e0e0c
                                charge(ctx, 1);
                                v0 = 636;
                            } else {
                                // 0x002e0e00
                                charge(ctx, 3);
                                v0 = 1133;
                            }
                            // 0x002e0e10
                            charge(ctx, 2);
                        }
                        break;
                    case 0x2E0EB8u:  // table[10]
                        // 0x002e0eb8
                        charge(ctx, 5);
                        a0 = 4958;
                        jal(ctx, 0x2E0EBCu, gen::fn_datGetFlag_0016f190);
                        if (v0 != 0) {
                            // 0x002e0ee8
                            charge(ctx, 6);
                            a0 = 100;
                            jal(ctx, 0x2E0EECu, gen::fn_datCalcRand_002ffbc0);
                            v0 = sltiu(v0, 50);
                            if (v0 != 0) {
                                // 0x002e0f48
                                charge(ctx, 3);
                                v0 = 708;
                            } else {
                                // 0x002e0f00
                                charge(ctx, 5);
                                v0 = 0x690000;
                                lw(a0, v0, 31744);  // 0x697C00
                                v0 = si(-1);
                                if (a0 != v0) {
                                    // 0x002e0f20
                                    charge(ctx, 2);
                                    jal(ctx, 0x2E0F20u, gen::fn_datGetFlag_0016f190);
                                } else {
                                    // 0x002e0f14
                                    charge(ctx, 3);
                                    v0 = 0;
                                }
                                // 0x002e0f28
                                charge(ctx, 2);
                                if (v0 == 0) {
                                    // 0x002e0f3c
                                    charge(ctx, 1);
                                    v0 = 705;
                                } else {
                                    // 0x002e0f30
                                    charge(ctx, 3);
                                    v0 = 706;
                                }
                                // 0x002e0f40
                                charge(ctx, 2);
                            }
                        } else {
                            // 0x002e0ecc
                            charge(ctx, 7);
                            a0 = 4958;
                            a1 = 1;
                            jal(ctx, 0x2E0ED4u, gen::fn_datSetFlag_0016f1f0);
                            v0 = 707;
                        }
                        break;
                    case 0x2E0F54u:  // table[0, 1, 6]
                    L_002e0f54:
                        charge(ctx, 1);
                        v0 = si(-1);
                        break;
                    default:  // not one of the table's targets: the dispatch table, as the recompiled body
                        tail(ctx, v0.u());
                        return;
                    }
                    // 0x002e0f58 (the shared epilogue, written out on this path)
                    charge(ctx, 6);
                    ld(ra, sp, 0x20);
                    lq(s1, sp, 0x10);
                    lq(s0, sp, 0x0);
                    sp = addiu(sp, 0x30);
                    return;
                }
                goto L_002e0f54;
            }
            // 0x002e08b0
            charge(ctx, 4);
            jal(ctx, 0x2E08B0u, gen::fn_sub_17D800_0017d800);
            if (v0 != 0) {
                // 0x002e08fc
                charge(ctx, 3);
                v0 = 169;
                if (s0 != v0) {
                    // 0x002e0914
                    charge(ctx, 1);
                    v0 = addiu(s0, 903);
                } else {
                    // 0x002e0908
                    charge(ctx, 3);
                    v0 = 904;
                }
                // 0x002e0918
                charge(ctx, 2);
            } else {
                // 0x002e08c0
                charge(ctx, 3);
                v0 = 169;
                if (s0 != v0) {
                    // 0x002e08d8
                    charge(ctx, 3);
                    at = slti(s0, 146);
                    if (at == 0) {
                        // 0x002e08ec
                        charge(ctx, 1);
                        s0 = addiu(s0, 718);
                    } else {
                        // 0x002e08e4
                        charge(ctx, 2);
                    }
                    // 0x002e08f0
                    charge(ctx, 3);
                    v0 = s0;
                } else {
                    // 0x002e08cc
                    charge(ctx, 3);
                    v0 = 1;
                }
            }
        } else {
            // 0x002e0664
            charge(ctx, 4);
            lhu(v1, a0, unit::kId);
            v0 = 240;
            if (v1 == v0) {
                // 0x002e0888
                charge(ctx, 3);
                v0 = 352;
            } else {
                // 0x002e0674
                charge(ctx, 3);
                v0 = 239;
                if (v1 == v0) {
                    // 0x002e087c
                    charge(ctx, 3);
                    v0 = 170;
                } else {
                    // 0x002e0680
                    charge(ctx, 3);
                    v0 = 238;
                    if (v1 == v0) {
                        // 0x002e0870
                        charge(ctx, 3);
                        v0 = 708;
                    } else {
                        // 0x002e068c
                        charge(ctx, 3);
                        v0 = 237;
                        if (v1 == v0) {
                            // 0x002e0864
                            charge(ctx, 3);
                            v0 = 425;
                        } else {
                            // 0x002e0698
                            charge(ctx, 3);
                            v0 = 236;
                            if (v1 == v0) {
                                // 0x002e0858
                                charge(ctx, 3);
                                v0 = 571;
                            } else {
                                // 0x002e06a4
                                charge(ctx, 3);
                                v0 = 235;
                                if (v1 == v0) {
                                    // 0x002e084c
                                    charge(ctx, 3);
                                    v0 = 498;
                                } else {
                                    // 0x002e06b0
                                    charge(ctx, 3);
                                    v0 = 234;
                                    if (v1 == v0) {
                                        // 0x002e0754
                                        charge(ctx, 4);
                                        v0 = addiu(s0, -192);
                                        at = sltiu(v0, 20);
                                        if (at == 0) {
                                        L_002e0894:
                                            charge(ctx, 3);
                                            v0 = si(-1);
                                        } else {
                                            // 0x002e0764
                                            charge(ctx, 7);
                                            v1 = 0x7C0000;
                                            v1 = addiu(v1, -31552);  // &0x7B84C0
                                            v0 = sll(v0, 2);
                                            v0 = addu(v0, v1);
                                            lw(v0, v0, 0);
                                            switch (v0.u()) {
                                            case 0x2E0780u:  // table[0]
                                                // 0x002e0780
                                                charge(ctx, 3);
                                                v0 = 887;
                                                break;
                                            case 0x2E078Cu:  // table[1]
                                                // 0x002e078c
                                                charge(ctx, 3);
                                                v0 = 888;
                                                break;
                                            case 0x2E0798u:  // table[2]
                                                // 0x002e0798
                                                charge(ctx, 3);
                                                v0 = 889;
                                                break;
                                            case 0x2E07A4u:  // table[3]
                                                // 0x002e07a4
                                                charge(ctx, 3);
                                                v0 = 890;
                                                break;
                                            case 0x2E07B0u:  // table[4]
                                                // 0x002e07b0
                                                charge(ctx, 3);
                                                v0 = 891;
                                                break;
                                            case 0x2E07BCu:  // table[5]
                                                // 0x002e07bc
                                                charge(ctx, 3);
                                                v0 = 892;
                                                break;
                                            case 0x2E07C8u:  // table[6]
                                                // 0x002e07c8
                                                charge(ctx, 3);
                                                v0 = 893;
                                                break;
                                            case 0x2E07D4u:  // table[7]
                                                // 0x002e07d4
                                                charge(ctx, 3);
                                                v0 = 894;
                                                break;
                                            case 0x2E07E0u:  // table[8]
                                                // 0x002e07e0
                                                charge(ctx, 3);
                                                v0 = 895;
                                                break;
                                            case 0x2E07ECu:  // table[9]
                                                // 0x002e07ec
                                                charge(ctx, 3);
                                                v0 = 896;
                                                break;
                                            case 0x2E07F8u:  // table[10]
                                                // 0x002e07f8
                                                charge(ctx, 3);
                                                v0 = 897;
                                                break;
                                            case 0x2E0804u:  // table[11]
                                                // 0x002e0804
                                                charge(ctx, 3);
                                                v0 = 898;
                                                break;
                                            case 0x2E0810u:  // table[12]
                                                // 0x002e0810
                                                charge(ctx, 3);
                                                v0 = 899;
                                                break;
                                            case 0x2E081Cu:  // table[13]
                                                // 0x002e081c
                                                charge(ctx, 3);
                                                v0 = 900;
                                                break;
                                            case 0x2E0828u:  // table[14]
                                                // 0x002e0828
                                                charge(ctx, 3);
                                                v0 = 901;
                                                break;
                                            case 0x2E0834u:  // table[15]
                                                // 0x002e0834
                                                charge(ctx, 3);
                                                v0 = 902;
                                                break;
                                            case 0x2E0840u:  // table[19]
                                                // 0x002e0840
                                                charge(ctx, 3);
                                                v0 = 903;
                                                break;
                                            case 0x2E0894u:  // table[16, 17, 18]
                                                goto L_002e0894;
                                            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                                                tail(ctx, v0.u());
                                                return;
                                            }
                                        }
                                    } else {
                                        // 0x002e06bc
                                        charge(ctx, 3);
                                        v0 = 233;
                                        if (v1 == v0) {
                                            // 0x002e0748
                                            charge(ctx, 3);
                                            v0 = 1134;
                                        } else {
                                            // 0x002e06c8
                                            charge(ctx, 3);
                                            v0 = 264;
                                            if (v1 == v0) {
                                                // 0x002e073c
                                                charge(ctx, 3);
                                                v0 = 801;
                                            } else {
                                                // 0x002e06d4
                                                charge(ctx, 3);
                                                v0 = 271;
                                                if (v1 == v0) {
                                                    // 0x002e0730
                                                    charge(ctx, 3);
                                                    v0 = 780;
                                                } else {
                                                    // 0x002e06e0
                                                    charge(ctx, 3);
                                                    v0 = 272;
                                                    if (v1 == v0) {
                                                        // 0x002e0724
                                                        charge(ctx, 3);
                                                        v0 = 760;
                                                    } else {
                                                        // 0x002e06ec
                                                        charge(ctx, 3);
                                                        v0 = 268;
                                                        if (v1 == v0) {
                                                            // 0x002e0718
                                                            charge(ctx, 3);
                                                            v0 = 779;
                                                        } else {
                                                            // 0x002e06f8
                                                            charge(ctx, 3);
                                                            v0 = 267;
                                                            if (v1 != v0) {
                                                                // 0x002e0704
                                                                charge(ctx, 2);
                                                                goto L_002e0894;
                                                            }
                                                            // 0x002e070c
                                                            charge(ctx, 3);
                                                            v0 = 759;
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
    } else {
        // 0x002e0648
        charge(ctx, 3);
        v0 = si(-1);
    }
    // 0x002e0f58 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002E0F70 sub_2E0F70 -- 860 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlVoicePickCountLine] A party member's line on an enemy count (1 / 2 / 3 / 4 / 5 enemies left), by party id; -1
// for the hero or enemies.
// Arguments: a0 btlAction.
void sub_2E0F70(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e0f70
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, a0, act::kUnit);
    lbu(v0, v0, unit::kSide);
    if (v0 == 0) {
        // 0x002e0f9c
        charge(ctx, 4);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(v0, v0, gbtl::kPlayerAction);
        if (v0 != s0) {
            // 0x002e0fb8
            charge(ctx, 8);
            a0 = 2;
            a1 = 0x80000;
            jal(ctx, 0x2E0FC0u, gen::fn_btlCountActiveUnits_002d4e10);
            v1 = v0 & 0xFFFF;
            v0 = 1;
            if (v1 == v0) {
                // 0x002e1208
                charge(ctx, 5);
                lw(v0, s0, act::kUnit);
                lhu(v0, v0, unit::kId);
                at = sltiu(v0, 11);
                if (at == 0) {
                L_002e12b4:
                    charge(ctx, 1);
                    v0 = si(-1);
                } else {
                    // 0x002e121c
                    charge(ctx, 7);
                    v1 = 0x7C0000;
                    v1 = addiu(v1, -31472);  // &0x7B8510
                    v0 = sll(v0, 2);
                    v0 = addu(v0, v1);
                    lw(v0, v0, 0);
                    switch (v0.u()) {
                    case 0x2E1238u:  // table[2]
                        // 0x002e1238
                        charge(ctx, 3);
                        v0 = 200;
                        break;
                    case 0x2E1244u:  // table[3]
                        // 0x002e1244
                        charge(ctx, 3);
                        v0 = 294;
                        break;
                    case 0x2E1250u:  // table[4]
                        // 0x002e1250
                        charge(ctx, 3);
                        v0 = 382;
                        break;
                    case 0x2E125Cu:  // table[5]
                        // 0x002e125c
                        charge(ctx, 3);
                        v0 = 455;
                        break;
                    case 0x2E1268u:  // table[7]
                        // 0x002e1268
                        charge(ctx, 3);
                        v0 = 528;
                        break;
                    case 0x2E1274u:  // table[8]
                        // 0x002e1274
                        charge(ctx, 3);
                        v0 = 601;
                        break;
                    case 0x2E1280u:  // table[9]
                        // 0x002e1280
                        charge(ctx, 4);
                        jal(ctx, 0x2E1280u, gen::fn_sub_17D800_0017d800);
                        if (v0 == 0) {
                            // 0x002e129c
                            charge(ctx, 1);
                            v0 = 666;
                        } else {
                            // 0x002e1290
                            charge(ctx, 3);
                            v0 = 1171;
                        }
                        // 0x002e12a0
                        charge(ctx, 2);
                        break;
                    case 0x2E12A8u:  // table[10]
                        // 0x002e12a8
                        charge(ctx, 3);
                        v0 = si(-1);
                        break;
                    case 0x2E12B4u:  // table[0, 1, 6]
                        goto L_002e12b4;
                    default:  // not one of the table's targets: the dispatch table, as the recompiled body
                        tail(ctx, v0.u());
                        return;
                    }
                }
            } else {
                // 0x002e0fd8
                charge(ctx, 3);
                v0 = 2;
                if (v1 == v0) {
                    // 0x002e115c
                    charge(ctx, 5);
                    lw(v0, s0, act::kUnit);
                    lhu(v0, v0, unit::kId);
                    at = sltiu(v0, 11);
                    if (at == 0) {
                        goto L_002e12b4;
                    }
                    // 0x002e1170
                    charge(ctx, 7);
                    v1 = 0x7C0000;
                    v1 = addiu(v1, -31424);  // &0x7B8540
                    v0 = sll(v0, 2);
                    v0 = addu(v0, v1);
                    lw(v0, v0, 0);
                    switch (v0.u()) {
                    case 0x2E118Cu:  // table[2]
                        // 0x002e118c
                        charge(ctx, 3);
                        v0 = 199;
                        break;
                    case 0x2E1198u:  // table[3]
                        // 0x002e1198
                        charge(ctx, 3);
                        v0 = 293;
                        break;
                    case 0x2E11A4u:  // table[4]
                        // 0x002e11a4
                        charge(ctx, 3);
                        v0 = 381;
                        break;
                    case 0x2E11B0u:  // table[5]
                        // 0x002e11b0
                        charge(ctx, 3);
                        v0 = 454;
                        break;
                    case 0x2E11BCu:  // table[7]
                        // 0x002e11bc
                        charge(ctx, 3);
                        v0 = 527;
                        break;
                    case 0x2E11C8u:  // table[8]
                        // 0x002e11c8
                        charge(ctx, 3);
                        v0 = 600;
                        break;
                    case 0x2E11D4u:  // table[9]
                        // 0x002e11d4
                        charge(ctx, 4);
                        jal(ctx, 0x2E11D4u, gen::fn_sub_17D800_0017d800);
                        if (v0 == 0) {
                            // 0x002e11f0
                            charge(ctx, 1);
                            v0 = 665;
                        } else {
                            // 0x002e11e4
                            charge(ctx, 3);
                            v0 = 1170;
                        }
                        // 0x002e11f4
                        charge(ctx, 2);
                        break;
                    case 0x2E11FCu:  // table[10]
                        // 0x002e11fc
                        charge(ctx, 3);
                        v0 = si(-1);
                        break;
                    case 0x2E12B4u:  // table[0, 1, 6]
                        goto L_002e12b4;
                    default:  // not one of the table's targets: the dispatch table, as the recompiled body
                        tail(ctx, v0.u());
                        return;
                    }
                } else {
                    // 0x002e0fe4
                    charge(ctx, 3);
                    v0 = 3;
                    if (v1 == v0) {
                        // 0x002e10b0
                        charge(ctx, 5);
                        lw(v0, s0, act::kUnit);
                        lhu(v0, v0, unit::kId);
                        at = sltiu(v0, 11);
                        if (at == 0) {
                            goto L_002e12b4;
                        }
                        // 0x002e10c4
                        charge(ctx, 7);
                        v1 = 0x7C0000;
                        v1 = addiu(v1, -31376);  // &0x7B8570
                        v0 = sll(v0, 2);
                        v0 = addu(v0, v1);
                        lw(v0, v0, 0);
                        switch (v0.u()) {
                        case 0x2E10E0u:  // table[2]
                            // 0x002e10e0
                            charge(ctx, 3);
                            v0 = 198;
                            break;
                        case 0x2E10ECu:  // table[3]
                            // 0x002e10ec
                            charge(ctx, 3);
                            v0 = 292;
                            break;
                        case 0x2E10F8u:  // table[4]
                            // 0x002e10f8
                            charge(ctx, 3);
                            v0 = 380;
                            break;
                        case 0x2E1104u:  // table[5]
                            // 0x002e1104
                            charge(ctx, 3);
                            v0 = 453;
                            break;
                        case 0x2E1110u:  // table[7]
                            // 0x002e1110
                            charge(ctx, 3);
                            v0 = 526;
                            break;
                        case 0x2E111Cu:  // table[8]
                            // 0x002e111c
                            charge(ctx, 3);
                            v0 = 599;
                            break;
                        case 0x2E1128u:  // table[9]
                            // 0x002e1128
                            charge(ctx, 4);
                            jal(ctx, 0x2E1128u, gen::fn_sub_17D800_0017d800);
                            if (v0 == 0) {
                                // 0x002e1144
                                charge(ctx, 1);
                                v0 = 664;
                            } else {
                                // 0x002e1138
                                charge(ctx, 3);
                                v0 = 1169;
                            }
                            // 0x002e1148
                            charge(ctx, 2);
                            break;
                        case 0x2E1150u:  // table[10]
                            // 0x002e1150
                            charge(ctx, 3);
                            v0 = si(-1);
                            break;
                        case 0x2E12B4u:  // table[0, 1, 6]
                            goto L_002e12b4;
                        default:  // not one of the table's targets: the dispatch table, as the recompiled body
                            tail(ctx, v0.u());
                            return;
                        }
                    } else {
                        // 0x002e0ff0
                        charge(ctx, 3);
                        v0 = 4;
                        if (v1 != v0) {
                            // 0x002e0ffc
                            charge(ctx, 2);
                            goto L_002e12b4;
                        }
                        // 0x002e1004
                        charge(ctx, 5);
                        lw(v0, s0, act::kUnit);
                        lhu(v0, v0, unit::kId);
                        at = sltiu(v0, 11);
                        if (at == 0) {
                            goto L_002e12b4;
                        }
                        // 0x002e1018
                        charge(ctx, 7);
                        v1 = 0x7C0000;
                        v1 = addiu(v1, -31328);  // &0x7B85A0
                        v0 = sll(v0, 2);
                        v0 = addu(v0, v1);
                        lw(v0, v0, 0);
                        switch (v0.u()) {
                        case 0x2E1034u:  // table[2]
                            // 0x002e1034
                            charge(ctx, 3);
                            v0 = 197;
                            break;
                        case 0x2E1040u:  // table[3]
                            // 0x002e1040
                            charge(ctx, 3);
                            v0 = 291;
                            break;
                        case 0x2E104Cu:  // table[4]
                            // 0x002e104c
                            charge(ctx, 3);
                            v0 = 379;
                            break;
                        case 0x2E1058u:  // table[5]
                            // 0x002e1058
                            charge(ctx, 3);
                            v0 = 452;
                            break;
                        case 0x2E1064u:  // table[7]
                            // 0x002e1064
                            charge(ctx, 3);
                            v0 = 525;
                            break;
                        case 0x2E1070u:  // table[8]
                            // 0x002e1070
                            charge(ctx, 3);
                            v0 = 598;
                            break;
                        case 0x2E107Cu:  // table[9]
                            // 0x002e107c
                            charge(ctx, 4);
                            jal(ctx, 0x2E107Cu, gen::fn_sub_17D800_0017d800);
                            if (v0 == 0) {
                                // 0x002e1098
                                charge(ctx, 1);
                                v0 = 663;
                            } else {
                                // 0x002e108c
                                charge(ctx, 3);
                                v0 = 1168;
                            }
                            // 0x002e109c
                            charge(ctx, 2);
                            break;
                        case 0x2E10A4u:  // table[10]
                            // 0x002e10a4
                            charge(ctx, 3);
                            v0 = si(-1);
                            break;
                        case 0x2E12B4u:  // table[0, 1, 6]
                            goto L_002e12b4;
                        default:  // not one of the table's targets: the dispatch table, as the recompiled body
                            tail(ctx, v0.u());
                            return;
                        }
                    }
                }
            }
        } else {
            // 0x002e0fac
            charge(ctx, 3);
            v0 = si(-1);
        }
    } else {
        // 0x002e0f90
        charge(ctx, 3);
        v0 = si(-1);
    }
    // 0x002e12b8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002E12D0 sub_2E12D0 -- 548 bytes; frame 0x10: ra sp+0x0
// [btlVoicePickAttackLine] A party member's attack line: one of two by a coin flip (datCalcRand(100) < 50), by party
// id; -1 under the boss rules or for enemies.
// Arguments: a0 btlAction.
void sub_2E12D0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e12d0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v1, v0, gbtl::kFlags);
    v0 = 0x200000;
    v0 = v1 & v0;
    if (v0 == 0) {
        // 0x002e12fc
        charge(ctx, 4);
        lw(v1, a0, act::kUnit);
        lbu(v0, v1, unit::kSide);
        if (v0 == 0) {
            // 0x002e1318
            charge(ctx, 4);
            lhu(v0, v1, unit::kId);
            at = sltiu(v0, 11);
            if (at != 0) {
                // 0x002e1328
                charge(ctx, 7);
                v1 = 0x7C0000;
                v1 = addiu(v1, -31280);  // &0x7B85D0
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                lw(v0, v0, 0);
                switch (v0.u()) {
                case 0x2E1344u:  // table[2]
                    // 0x002e1344
                    charge(ctx, 6);
                    a0 = 100;
                    jal(ctx, 0x2E1348u, gen::fn_datCalcRand_002ffbc0);
                    v0 = sltiu(v0, 50);
                    if (v0 != 0) {
                        // 0x002e1368
                        charge(ctx, 1);
                        v0 = 214;
                    } else {
                        // 0x002e135c
                        charge(ctx, 3);
                        v0 = 213;
                    }
                    // 0x002e136c
                    charge(ctx, 2);
                    break;
                case 0x2E1374u:  // table[3]
                    // 0x002e1374
                    charge(ctx, 6);
                    a0 = 100;
                    jal(ctx, 0x2E1378u, gen::fn_datCalcRand_002ffbc0);
                    v0 = sltiu(v0, 50);
                    if (v0 != 0) {
                        // 0x002e1398
                        charge(ctx, 1);
                        v0 = 308;
                    } else {
                        // 0x002e138c
                        charge(ctx, 3);
                        v0 = 307;
                    }
                    // 0x002e139c
                    charge(ctx, 2);
                    break;
                case 0x2E13A4u:  // table[4]
                    // 0x002e13a4
                    charge(ctx, 6);
                    a0 = 100;
                    jal(ctx, 0x2E13A8u, gen::fn_datCalcRand_002ffbc0);
                    v0 = sltiu(v0, 50);
                    if (v0 != 0) {
                        // 0x002e13c8
                        charge(ctx, 1);
                        v0 = 396;
                    } else {
                        // 0x002e13bc
                        charge(ctx, 3);
                        v0 = 395;
                    }
                    // 0x002e13cc
                    charge(ctx, 2);
                    break;
                case 0x2E13D4u:  // table[5]
                    // 0x002e13d4
                    charge(ctx, 6);
                    a0 = 100;
                    jal(ctx, 0x2E13D8u, gen::fn_datCalcRand_002ffbc0);
                    v0 = sltiu(v0, 50);
                    if (v0 != 0) {
                        // 0x002e13f8
                        charge(ctx, 1);
                        v0 = 469;
                    } else {
                        // 0x002e13ec
                        charge(ctx, 3);
                        v0 = 468;
                    }
                    // 0x002e13fc
                    charge(ctx, 2);
                    break;
                case 0x2E1404u:  // table[7]
                    // 0x002e1404
                    charge(ctx, 6);
                    a0 = 100;
                    jal(ctx, 0x2E1408u, gen::fn_datCalcRand_002ffbc0);
                    v0 = sltiu(v0, 50);
                    if (v0 != 0) {
                        // 0x002e1428
                        charge(ctx, 1);
                        v0 = 542;
                    } else {
                        // 0x002e141c
                        charge(ctx, 3);
                        v0 = 541;
                    }
                    // 0x002e142c
                    charge(ctx, 2);
                    break;
                case 0x2E1434u:  // table[8]
                    // 0x002e1434
                    charge(ctx, 6);
                    a0 = 100;
                    jal(ctx, 0x2E1438u, gen::fn_datCalcRand_002ffbc0);
                    v0 = sltiu(v0, 50);
                    if (v0 != 0) {
                        // 0x002e1458
                        charge(ctx, 1);
                        v0 = 615;
                    } else {
                        // 0x002e144c
                        charge(ctx, 3);
                        v0 = 614;
                    }
                    // 0x002e145c
                    charge(ctx, 2);
                    break;
                case 0x2E1464u:  // table[9]
                    // 0x002e1464
                    charge(ctx, 4);
                    jal(ctx, 0x2E1464u, gen::fn_sub_17D800_0017d800);
                    if (v0 != 0) {
                        // 0x002e14a4
                        charge(ctx, 6);
                        a0 = 100;
                        jal(ctx, 0x2E14A8u, gen::fn_datCalcRand_002ffbc0);
                        v0 = sltiu(v0, 50);
                        if (v0 != 0) {
                            // 0x002e14c8
                            charge(ctx, 1);
                            v0 = 1185;
                        } else {
                            // 0x002e14bc
                            charge(ctx, 3);
                            v0 = 1184;
                        }
                        // 0x002e14cc
                        charge(ctx, 2);
                    } else {
                        // 0x002e1474
                        charge(ctx, 6);
                        a0 = 100;
                        jal(ctx, 0x2E1478u, gen::fn_datCalcRand_002ffbc0);
                        v0 = sltiu(v0, 50);
                        if (v0 != 0) {
                            // 0x002e1498
                            charge(ctx, 1);
                            v0 = 680;
                        } else {
                            // 0x002e148c
                            charge(ctx, 3);
                            v0 = 679;
                        }
                        // 0x002e149c
                        charge(ctx, 2);
                    }
                    break;
                case 0x2E14D4u:  // table[10]
                    // 0x002e14d4
                    charge(ctx, 3);
                    v0 = si(-1);
                    break;
                case 0x2E14E0u:  // table[0, 1, 6]
                L_002e14e0:
                    charge(ctx, 1);
                    v0 = si(-1);
                    break;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, v0.u());
                    return;
                }
                // 0x002e14e4 (the shared epilogue, written out on this path)
                charge(ctx, 4);
                ld(ra, sp, 0x0);
                sp = addiu(sp, 0x10);
                return;
            }
            goto L_002e14e0;
        }
        // 0x002e130c
        charge(ctx, 3);
        v0 = si(-1);
    } else {
        // 0x002e12f0
        charge(ctx, 3);
        v0 = si(-1);
    }
    // 0x002e14e4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002E1BF0 sub_2E1BF0 -- 224 bytes; frame 0x10: ra sp+0x0
// A party member's line of the row 0x7B8810: by party id 2..10 (Koromaru's by sub_17D800).
// Arguments: a0 btlAction.
void sub_2E1BF0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e1bf0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, a0, act::kUnit);
    lbu(v0, v1, unit::kSide);
    if (v0 == 0) {
        // 0x002e1c14
        charge(ctx, 4);
        lhu(v0, v1, unit::kId);
        at = sltiu(v0, 11);
        if (at != 0) {
            // 0x002e1c24
            charge(ctx, 7);
            v1 = 0x7C0000;
            v1 = addiu(v1, -30704);  // &0x7B8810
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x2E1C40u:  // table[2]
                // 0x002e1c40
                charge(ctx, 3);
                v0 = 154;
                break;
            case 0x2E1C4Cu:  // table[3]
                // 0x002e1c4c
                charge(ctx, 3);
                v0 = 234;
                break;
            case 0x2E1C58u:  // table[4]
                // 0x002e1c58
                charge(ctx, 3);
                v0 = 336;
                break;
            case 0x2E1C64u:  // table[5]
                // 0x002e1c64
                charge(ctx, 3);
                v0 = 409;
                break;
            case 0x2E1C70u:  // table[7]
                // 0x002e1c70
                charge(ctx, 3);
                v0 = 482;
                break;
            case 0x2E1C7Cu:  // table[8]
                // 0x002e1c7c
                charge(ctx, 3);
                v0 = 555;
                break;
            case 0x2E1C88u:  // table[9]
                // 0x002e1c88
                charge(ctx, 4);
                jal(ctx, 0x2E1C88u, gen::fn_sub_17D800_0017d800);
                if (v0 == 0) {
                    // 0x002e1ca4
                    charge(ctx, 1);
                    v0 = 628;
                } else {
                    // 0x002e1c98
                    charge(ctx, 3);
                    v0 = 1125;
                }
                // 0x002e1ca8
                charge(ctx, 2);
                break;
            case 0x2E1CB0u:  // table[10]
                // 0x002e1cb0
                charge(ctx, 3);
                v0 = 693;
                break;
            case 0x2E1CBCu:  // table[0, 1, 6]
            L_002e1cbc:
                charge(ctx, 1);
                v0 = si(-1);
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
            // 0x002e1cc0 (the shared epilogue, written out on this path)
            charge(ctx, 4);
            ld(ra, sp, 0x0);
            sp = addiu(sp, 0x10);
            return;
        }
        goto L_002e1cbc;
    }
    // 0x002e1c08
    charge(ctx, 3);
    v0 = si(-1);
    // 0x002e1cc0 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002E2410 sub_2E2410 -- 328 bytes; frame 0x80: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlVoicePickBystanderLine] A random other party member (living, not the hero or the actor, not ailing, not
// Koromaru's partner id 10) comments: its count line sub_2E0F70; -1 for none.
// Arguments: a0 btlAction.
void sub_2E2410(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e2410
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    lw(v0, a0, act::kUnit);
    lbu(v0, v0, unit::kSide);
    if (v0 == 0) {
        // 0x002e2448
        charge(ctx, 5);
        s1 = 0;
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(s2, v0, gbtl::kActionList);
        for (;;) {
            // 0x002e24f4
            charge(ctx, 2);
            if (s2 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002e245c
            charge(ctx, 4);
            lhu(v0, s2, act::kFlags2);
            v0 = v0 & 0x1;
            if (v0 != 0) {
                // 0x002e246c
                charge(ctx, 4);
                lw(s0, s2, act::kUnit);
                lbu(v0, s0, unit::kSide);
                if (v0 == 0) {
                    // 0x002e247c
                    charge(ctx, 4);
                    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                    lw(v0, v0, gbtl::kPlayerAction);
                    if (v0 != s2) {
                        // 0x002e248c
                        charge(ctx, 2);
                        if (s3 != s2) {
                            // 0x002e2494
                            charge(ctx, 6);
                            lw(a0, s0, unit::kDat);
                            a1 = 0;
                            jal(ctx, 0x2E249Cu, gen::fn_datCalcIsDead_0030b5a0);
                            if (v0 == 0) {
                                // 0x002e24ac
                                charge(ctx, 7);
                                lw(a0, s0, unit::kDat);
                                v0 = 0x180000;
                                a1 = v0 | 0x375;  // &0x180375
                                jal(ctx, 0x2E24B8u, gen::fn_datCalcChkBadStatus_00300580);
                                if (v0 == 0) {
                                    // 0x002e24c8
                                    charge(ctx, 4);
                                    lhu(v1, s0, unit::kId);
                                    v0 = 10;
                                    if (v1 != v0) {
                                        // 0x002e24d8
                                        charge(ctx, 6);
                                        v0 = s1 & 0xFFFF;
                                        v0 = sll(v0, 2);
                                        v0 = addu(v0, sp);
                                        sw(s2, v0, 80);
                                        v0 = addiu(s1, 1);
                                        s1 = v0 & 0xFFFF;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            // 0x002e24f0
            charge(ctx, 1);
            lw(s2, s2, act::kNext);
        }
        // 0x002e24fc
        charge(ctx, 3);
        a0 = s1 & 0xFFFF;
        if (a0 != 0) {
            // 0x002e2514
            charge(ctx, 9);
            jal(ctx, 0x2E2514u, gen::fn_datCalcRand_002ffbc0);
            v0 = sll(v0, 2);
            v0 = addu(v0, sp);
            lw(a0, v0, 80);
            a1 = 0;
            a2 = 0;
            jal(ctx, 0x2E2530u, gen::fn_sub_2E0F70_002e0f70);
        } else {
            // 0x002e2508
            charge(ctx, 3);
            v0 = si(-1);
        }
    } else {
        // 0x002e243c
        charge(ctx, 3);
        v0 = si(-1);
    }
    // 0x002e2538 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x002E2680 sub_2E2680 -- 660 bytes; frame 0x10: ra sp+0x0
// [btlVoicePickLine1091] A party member's line by party id with a coin flip (some by the flag 0x697BE4); -1 for
// enemies, a missing DatUnit or persona state 9.
// Arguments: a0 btlAction.
void sub_2E2680(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e2680
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, act::kUnit);
    lbu(v0, a0, unit::kSide);
    if (v0 == 0) {
        // 0x002e26a4
        charge(ctx, 3);
        lw(v0, a0, unit::kDat);
        if (v0 != 0) {
            // 0x002e26bc
            charge(ctx, 4);
            lb(v1, v0, dat4::kTactic);
            v0 = 9;
            if (v1 != v0) {
                // 0x002e26d8
                charge(ctx, 4);
                lhu(v0, a0, unit::kId);
                at = sltiu(v0, 11);
                if (at != 0) {
                    // 0x002e26e8
                    charge(ctx, 7);
                    v1 = 0x7C0000;
                    v1 = addiu(v1, -30384);  // &0x7B8950
                    v0 = sll(v0, 2);
                    v0 = addu(v0, v1);
                    lw(v0, v0, 0);
                    switch (v0.u()) {
                    case 0x2E2704u:  // table[2]
                        // 0x002e2704
                        charge(ctx, 6);
                        a0 = 100;
                        jal(ctx, 0x2E2708u, gen::fn_datCalcRand_002ffbc0);
                        v0 = sltiu(v0, 50);
                        if (v0 != 0) {
                            // 0x002e2728
                            charge(ctx, 1);
                            v0 = 1092;
                        } else {
                            // 0x002e271c
                            charge(ctx, 3);
                            v0 = 1091;
                        }
                        // 0x002e272c
                        charge(ctx, 2);
                        break;
                    case 0x2E2734u:  // table[3]
                        // 0x002e2734
                        charge(ctx, 5);
                        v0 = 0x690000;
                        lw(a0, v0, 31716);  // 0x697BE4
                        v0 = si(-1);
                        if (a0 != v0) {
                            // 0x002e2754
                            charge(ctx, 2);
                            jal(ctx, 0x2E2754u, gen::fn_datGetFlag_0016f190);
                        } else {
                            // 0x002e2748
                            charge(ctx, 3);
                            v0 = 0;
                        }
                        // 0x002e275c
                        charge(ctx, 2);
                        if (v0 == 0) {
                            // 0x002e2794
                            charge(ctx, 6);
                            a0 = 100;
                            jal(ctx, 0x2E2798u, gen::fn_datCalcRand_002ffbc0);
                            v0 = sltiu(v0, 50);
                            if (v0 != 0) {
                                // 0x002e27b8
                                charge(ctx, 1);
                                v0 = 1096;
                            } else {
                                // 0x002e27ac
                                charge(ctx, 3);
                                v0 = 1095;
                            }
                            // 0x002e27bc
                            charge(ctx, 2);
                        } else {
                            // 0x002e2764
                            charge(ctx, 6);
                            a0 = 100;
                            jal(ctx, 0x2E2768u, gen::fn_datCalcRand_002ffbc0);
                            v0 = sltiu(v0, 50);
                            if (v0 != 0) {
                                // 0x002e2788
                                charge(ctx, 1);
                                v0 = 1098;
                            } else {
                                // 0x002e277c
                                charge(ctx, 3);
                                v0 = 1097;
                            }
                            // 0x002e278c
                            charge(ctx, 2);
                        }
                        break;
                    case 0x2E27C4u:  // table[4]
                        // 0x002e27c4
                        charge(ctx, 6);
                        a0 = 100;
                        jal(ctx, 0x2E27C8u, gen::fn_datCalcRand_002ffbc0);
                        v0 = sltiu(v0, 50);
                        if (v0 != 0) {
                            // 0x002e27e8
                            charge(ctx, 1);
                            v0 = 1102;
                        } else {
                            // 0x002e27dc
                            charge(ctx, 3);
                            v0 = 1101;
                        }
                        // 0x002e27ec
                        charge(ctx, 2);
                        break;
                    case 0x2E27F4u:  // table[5]
                        // 0x002e27f4
                        charge(ctx, 6);
                        a0 = 100;
                        jal(ctx, 0x2E27F8u, gen::fn_datCalcRand_002ffbc0);
                        v0 = sltiu(v0, 50);
                        if (v0 != 0) {
                            // 0x002e2818
                            charge(ctx, 1);
                            v0 = 1106;
                        } else {
                            // 0x002e280c
                            charge(ctx, 3);
                            v0 = 1105;
                        }
                        // 0x002e281c
                        charge(ctx, 2);
                        break;
                    case 0x2E2824u:  // table[7]
                        // 0x002e2824
                        charge(ctx, 6);
                        a0 = 100;
                        jal(ctx, 0x2E2828u, gen::fn_datCalcRand_002ffbc0);
                        v0 = sltiu(v0, 50);
                        if (v0 != 0) {
                            // 0x002e2848
                            charge(ctx, 1);
                            v0 = 1108;
                        } else {
                            // 0x002e283c
                            charge(ctx, 3);
                            v0 = 1107;
                        }
                        // 0x002e284c
                        charge(ctx, 2);
                        break;
                    case 0x2E2854u:  // table[8]
                        // 0x002e2854
                        charge(ctx, 6);
                        a0 = 100;
                        jal(ctx, 0x2E2858u, gen::fn_datCalcRand_002ffbc0);
                        v0 = sltiu(v0, 50);
                        if (v0 != 0) {
                            // 0x002e2878
                            charge(ctx, 1);
                            v0 = 1114;
                        } else {
                            // 0x002e286c
                            charge(ctx, 3);
                            v0 = 1113;
                        }
                        // 0x002e287c
                        charge(ctx, 2);
                        break;
                    case 0x2E2884u:  // table[9]
                        // 0x002e2884
                        charge(ctx, 4);
                        jal(ctx, 0x2E2884u, gen::fn_sub_17D800_0017d800);
                        if (v0 != 0) {
                            // 0x002e28c4
                            charge(ctx, 6);
                            a0 = 100;
                            jal(ctx, 0x2E28C8u, gen::fn_datCalcRand_002ffbc0);
                            v0 = sltiu(v0, 50);
                            if (v0 != 0) {
                                // 0x002e28e8
                                charge(ctx, 1);
                                v0 = 1204;
                            } else {
                                // 0x002e28dc
                                charge(ctx, 3);
                                v0 = 1203;
                            }
                            // 0x002e28ec
                            charge(ctx, 2);
                        } else {
                            // 0x002e2894
                            charge(ctx, 6);
                            a0 = 100;
                            jal(ctx, 0x2E2898u, gen::fn_datCalcRand_002ffbc0);
                            v0 = sltiu(v0, 50);
                            if (v0 != 0) {
                                // 0x002e28b8
                                charge(ctx, 1);
                                v0 = 1116;
                            } else {
                                // 0x002e28ac
                                charge(ctx, 3);
                                v0 = 1115;
                            }
                            // 0x002e28bc
                            charge(ctx, 2);
                        }
                        break;
                    case 0x2E28F4u:  // table[10]
                        // 0x002e28f4
                        charge(ctx, 3);
                        v0 = si(-1);
                        break;
                    case 0x2E2900u:  // table[0, 1, 6]
                    L_002e2900:
                        charge(ctx, 1);
                        v0 = si(-1);
                        break;
                    default:  // not one of the table's targets: the dispatch table, as the recompiled body
                        tail(ctx, v0.u());
                        return;
                    }
                    // 0x002e2904 (the shared epilogue, written out on this path)
                    charge(ctx, 4);
                    ld(ra, sp, 0x0);
                    sp = addiu(sp, 0x10);
                    return;
                }
                goto L_002e2900;
            }
            // 0x002e26cc
            charge(ctx, 3);
            v0 = si(-1);
        } else {
            // 0x002e26b0
            charge(ctx, 3);
            v0 = si(-1);
        }
    } else {
        // 0x002e2698
        charge(ctx, 3);
        v0 = si(-1);
    }
    // 0x002e2904 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002E3120 sub_2E3120 -- 376 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlAnalysisGetRecord] The analysed-enemy record of a unit: drops the 12 records (gBtl +2656: s8 side, u16 enemy
// id) whose enemy left the battle, then returns the unit's record, taking a free one when absent.
// Arguments: a0 btlAction.
void sub_2E3120(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e327c: the shared epilogue (v0 = the record)
    auto epilogue = [&] {
        charge(ctx, 7);
        ld(ra, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
    };
    // 0x002e3120
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    // Pass 1: drop the records (12 x {s8 side, u16 base id} at gBtl +2656) whose enemy is no longer on its side's list.
    t0 = 0;                     // t0 = the record
    a1 = si(-1);
    for (;;) {
        // 0x002e31c8
        charge(ctx, 4);
        v0 = t0 & 0xFFFF;
        v0 = sltiu(v0, 12);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002e3144
        charge(ctx, 8);
        lw(a3, gp, kGpBtl);  // gBtl 0x7CE3EC
        v0 = t0 & 0xFFFF;
        v0 = sll(v0, 2);
        v1 = addu(a3, v0);
        a2 = addiu(v1, gbtl4::kAnalysis);
        lb(v0, v1, gbtl4::kAnalysis);         // the side (-1: free)
        if (v0 != a1) {
            // 0x002e3164
            charge(ctx, 6);
            lhu(v1, v1, gbtl4::kAnalysis + 2);  // the enemy base id
            v0 = sll(v0, 3);
            v0 = addu(a3, v0);
            lw(a3, v0, gbtl::kUnitHead0);   // the side's first btlUnit
            for (;;) {
                // 0x002e3198
                charge(ctx, 2);
                if (a3 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x002e317c
                charge(ctx, 3);
                lw(v0, a3, unit::kDat);
                if (v0 != 0) {
                    // 0x002e3188
                    charge(ctx, 3);
                    lhu(v0, v0, dat::kBaseId);
                    if (v1 == v0) {
                        break;      // still in the battle
                    }
                }
                // 0x002e3194
                charge(ctx, 1);
                lw(a3, a3, unit::kNext);
            }
            // 0x002e31a0
            charge(ctx, 2);
            if (a3 == 0) {
                // 0x002e31a8: gone -- free the record
                charge(ctx, 6);
                v0 = t0 & 0xFFFF;
                v1 = sll(v0, 2);
                sb(a1, a2, 0);
                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                v0 = addu(v0, v1);
                sh(zero, v0, gbtl4::kAnalysis + 2);
            }
        }
        // 0x002e31c0
        charge(ctx, 2);
        v0 = addiu(t0, 1);
        t0 = v0 & 0xFFFF;
    }
    // Pass 2: the unit's record (same side and base id), else the first free one (s2).
    // 0x002e31d8
    charge(ctx, 10);
    lw(v0, a0, act::kUnit);
    s2 = 0;
    lb(s1, v0, unit::kSide);    // s1 = the side
    lw(v0, v0, unit::kDat);
    lhu(s0, v0, dat::kBaseId);  // s0 = the base id
    a3 = 0;
    lw(a2, gp, kGpBtl);  // gBtl 0x7CE3EC
    v1 = si(-1);
    for (;;) {
        // 0x002e324c
        charge(ctx, 4);
        v0 = a3 & 0xFFFF;
        v0 = sltiu(v0, 12);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002e3200
        charge(ctx, 7);
        v0 = a3 & 0xFFFF;
        v0 = sll(v0, 2);
        a0 = addu(a2, v0);
        v0 = addiu(a0, gbtl4::kAnalysis);
        lb(a1, a0, gbtl4::kAnalysis);
        if (a1 == s1) {
            // 0x002e321c
            charge(ctx, 3);
            lhu(a0, a0, gbtl4::kAnalysis + 2);
            if (a0 == s0) {
                // 0x002e3228: found (v0 = the record)
                charge(ctx, 2);
                epilogue();
                return;
            }
        }
        // 0x002e3230
        charge(ctx, 2);
        if (s2 == 0) {
            // 0x002e3238
            charge(ctx, 2);
            if (a1 == v1) {
                // 0x002e3240
                charge(ctx, 1);
                s2 = v0;
            }
        }
        // 0x002e3244
        charge(ctx, 2);
        v0 = addiu(a3, 1);
        a3 = v0 & 0xFFFF;
    }
    // 0x002e325c: take the free record (with no free record s2 is 0 and memset writes at 0, as the original does)
    charge(ctx, 8);
    a0 = s2;
    a1 = 0;
    a2 = 4;
    jal(ctx, 0x2E3268u, gen::fn_memset_00521408);
    sb(s1, s2, 0);
    sh(s0, s2, 2);
    v0 = s2;
    epilogue();
}

// 0x002E32A0 sub_2E32A0 -- 164 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlAnalysisLearnElement] Records that the party saw an enemy's affinity to the element of the skill a2 (sub_17B2E0
// on its analysis record), for enemies only.
// Arguments: a0 btlAction, a1 target btlAction, a2 skill.
void sub_2E32A0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e32a0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a2;
    lw(v1, a1, act::kUnit);
    lbu(a0, v1, unit::kSide);
    v1 = 1;
    if (a0 == v1) {
        // 0x002e32d0
        charge(ctx, 14);
        a0 = a1;
        jal(ctx, 0x2E32D4u, gen::fn_sub_2E3120_002e3120);
        s0 = v0;
        lw(v0, s2, act::kUnit);
        lw(a0, v0, unit::kDat);
        a1 = s1;
        jal(ctx, 0x2E32ECu, gen::fn_datCalcGetSkillElement_003082f0);
        a0 = dsll32(v0, 16);
        a0 = dsra32(a0, 16);
        v1 = si(-1);
        if (a0 != v1) {
            // 0x002e3308
            charge(ctx, 3);
            at = slti(a0, 10);
            if (at != 0) {
                // 0x002e3314
                charge(ctx, 5);
                a1 = a0 & 0xFFFF;
                lhu(a0, s0, 2);
                a2 = 1;
                jal(ctx, 0x2E3320u, gen::fn_sub_17B2E0_0017b2e0);
            }
        }
    }
    // 0x002e3328 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x002E3350 sub_2E3350 -- 156 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlAnalysisKnowsElement] Whether the party knows an enemy's affinity to an element (1 for party units, the
// almighty / unknown / physical-7 elements): the analysis record's bits (sub_17B3D0).
// Arguments: a0 btlAction, a1 element.
void sub_2E3350(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e33d8: the shared epilogue (v0 = known)
    auto epilogue = [&] {
        charge(ctx, 5);
        ld(ra, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x20);
    };
    // 0x002e3350
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;                    // s0 = the element
    lw(v0, a0, act::kUnit);
    lbu(v1, v0, unit::kSide);
    v0 = 1;                     // party units: always known
    if (v1 == v0) {
        // An enemy: its analysis record (sub_2E3120, v0) -- the elements -1, >= 10 and 7 count as known, the others
        // as the record's bit for the element (sub_17B3D0(base id, element)).
        // 0x002e337c
        charge(ctx, 7);
        jal(ctx, 0x2E337Cu, gen::fn_sub_2E3120_002e3120);
        a0 = dsll32(s0, 16);
        a0 = dsra32(a0, 16);
        v1 = si(-1);
        bool plain = a0 == v1;  // -1: no element
        if (!plain) {
            // 0x002e3398
            charge(ctx, 3);
            v1 = slti(a0, 10);
            plain = v1 == 0;    // 10 and above
        }
        if (!plain) {
            // 0x002e33b0
            charge(ctx, 3);
            v1 = 7;
            if (a0 != v1) {
                // 0x002e33c8
                charge(ctx, 4);
                a1 = s0 & 0xFFFF;
                lhu(a0, v0, 2);     // the record's enemy base id
                jal(ctx, 0x2E33D0u, gen::fn_sub_17B3D0_0017b3d0);
            } else {
                // 0x002e33bc
                charge(ctx, 3);
                v0 = 1;
            }
            epilogue();
            return;
        }
        // 0x002e33a4
        charge(ctx, 3);
        v0 = 1;
    } else {
        // 0x002e3374
        charge(ctx, 2);
    }
    epilogue();
}

// 0x002E35D0 sub_2E35D0 -- 116 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Creates packet 3072 (6 bytes: two halfwords and 0) with the hold / update callbacks sub_2E3560 / sub_2E35A0.
// Arguments: a0, a1.
void sub_2E35D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e35d0
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    a0 = 3072;
    a1 = 6;
    jal(ctx, 0x2E35F0u, gen::fn_sub_27EC10_0027ec10);
    lbu(v1, v0, pkt::kFlags);
    v1 = v1 & 0xEE;
    sb(v1, v0, pkt::kFlags);
    v1 = 0x2E0000;
    v1 = addiu(v1, 13664);  // &sub_2E3560
    sw(v1, v0, pkt::kOnQueue);
    v1 = 0x2E0000;
    v1 = addiu(v1, 13728);  // &sub_2E35A0
    sw(v1, v0, pkt::kUpdate);
    lw(v1, v0, pkt::kData);
    sh(s1, v1, 0);
    sh(s0, v1, 2);
    sh(zero, v1, 4);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002E36F0 sub_2E36F0 -- 76 bytes; frame 0x10: ra sp+0x0
// Creates packet 3073 (8 bytes zeroed) with the update sub_2E3650.
void sub_2E36F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e36f0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 3073;
    a1 = 8;
    jal(ctx, 0x2E3700u, gen::fn_sub_27EC10_0027ec10);
    lbu(v1, v0, pkt::kFlags);
    v1 = v1 & 0xEE;
    sb(v1, v0, pkt::kFlags);
    v1 = 0x2E0000;
    v1 = addiu(v1, 13904);  // &sub_2E3650
    sw(v1, v0, pkt::kUpdate);
    lw(v1, v0, pkt::kData);
    sw(zero, v1, 4);
    sh(zero, v1, 0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002E37E0 sub_2E37E0 -- 76 bytes; frame 0x10: ra sp+0x0
// Creates packet 3074 (8 bytes zeroed) with the update sub_2E3740.
void sub_2E37E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e37e0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 3074;
    a1 = 8;
    jal(ctx, 0x2E37F0u, gen::fn_sub_27EC10_0027ec10);
    lbu(v1, v0, pkt::kFlags);
    v1 = v1 & 0xEE;
    sb(v1, v0, pkt::kFlags);
    v1 = 0x2E0000;
    v1 = addiu(v1, 14144);  // &sub_2E3740
    sw(v1, v0, pkt::kUpdate);
    lw(v1, v0, pkt::kData);
    sw(zero, v1, 4);
    sh(zero, v1, 0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002E3C80 sub_2E3C80 -- 76 bytes; frame 0x10: ra sp+0x0
// Creates packet 3079 (8 bytes zeroed) with the update sub_2E3BE0.
void sub_2E3C80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e3c80
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 3079;
    a1 = 8;
    jal(ctx, 0x2E3C90u, gen::fn_sub_27EC10_0027ec10);
    lbu(v1, v0, pkt::kFlags);
    v1 = v1 & 0xEE;
    sb(v1, v0, pkt::kFlags);
    v1 = 0x2E0000;
    v1 = addiu(v1, 15328);  // &sub_2E3BE0
    sw(v1, v0, pkt::kUpdate);
    lw(v1, v0, pkt::kData);
    sw(zero, v1, 4);
    sh(zero, v1, 0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002E4290 sub_2E4290 -- 36 bytes; frame 0x10: ra sp+0x0
// Boss AI event: battle start (sub_2FD2E0 kind 0).
// Arguments: a0.
void sub_2E4290(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e4290
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a1 = 0;
    jal(ctx, 0x2E429Cu, gen::fn_sub_2FD2E0_002fd2e0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002E42E0 sub_2E42E0 -- 36 bytes; frame 0x10: ra sp+0x0
// Boss AI event: action start (sub_2FD2E0 kind 1).
// Arguments: a0.
void sub_2E42E0(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e42e0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a1 = 1;
    jal(ctx, 0x2E42ECu, gen::fn_sub_2FD2E0_002fd2e0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002E4330 sub_2E4330 -- 108 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Boss AI event: action end -- the pending boss callback (gBtl +2824 with +2832) when set and sub_2FD500 is 0, else
// sub_2FD2E0 kind 2.
// Arguments: a0.
void sub_2E4330(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e4388: the shared epilogue
    auto epilogue = [&] {
        charge(ctx, 5);
        ld(ra, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x20);
    };
    // 0x002e4330
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;                    // s0 = the action
    jal(ctx, 0x2E4340u, gen::fn_sub_2FD500_002fd500);
    if (v0 == 0) {
        // 0x002e4350: a pending boss callback runs instead of the ACTEND script
        charge(ctx, 4);
        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(v0, v1, gbtl4::kBossActEndFn);
        if (v0 != 0) {
            // 0x002e4360
            charge(ctx, 6);
            lw(a0, v1, gbtl4::kBossActEndArg);
            jalr(ctx, 0x2E4364u, v0.u());
            v0 = 1;
            epilogue();
            return;
        }
    }
    // 0x002e4378: the boss event script, kind 2 (action end)
    charge(ctx, 4);
    a0 = s0;
    a1 = 2;
    jal(ctx, 0x2E4380u, gen::fn_sub_2FD2E0_002fd2e0);
    epilogue();
}

// 0x002E4430 sub_2E4430 -- 240 bytes; frame 0x70: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlSkillCheckTargets] Whether a skill finds targets now: for a targeted skill (skill record bit 0x8) the
// candidates (sub_2BFCB0 with the record's +9 / +10 / +12): none -> 2; target type 6 (+36) without sub_2C1CE0 -> 6;
// else 0 (also 0 for skills <= 0 or untargeted ones).
// Arguments: a0 btlAction, a1 skill.
void sub_2E4430(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e4430
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;                    // s1 = the action
    if (i64(a1) > 0) {
        // 0x002e4458: the skill's record (44 bytes in gBtlSkillTbl)
        charge(ctx, 11);
        v0 = sll(a1, 2);
        v0 = addu(v0, a1);
        v0 = sll(v0, 1);
        v0 = addu(v0, a1);
        s0 = sll(v0, 2);        // s0 = 44 * skill
        lw(v0, gp, kGpSkillTbl);  // gBtlSkillTbl
        v1 = addu(v0, s0);
        lbu(v0, v1, 0);
        v0 = v0 & 0x8;
        if (v0 != 0) {
            // A targeted skill: its candidates (sub_2BFCB0 into the stack record sp + 0x30 with the record's target
            // side +9, filter +10 and status +12; the count at record +56 = sp + 0x68).
            // 0x002e4490
            charge(ctx, 9);
            lhu(t0, v1, 12);
            a1 = addiu(sp, 0x30);
            lbu(a2, v1, 9);
            lbu(a3, v1, 10);
            jal(ctx, 0x2E44A0u, gen::fn_sub_2BFCB0_002bfcb0);
            lhu(v0, sp, 0x68);
            if (v0 != 0) {
                // 0x002e44c0: target type 6 (+36) needs sub_2C1CE0(action, 0)
                charge(ctx, 6);
                lw(v0, gp, kGpSkillTbl);  // gBtlSkillTbl
                v0 = addu(s0, v0);
                lbu(v1, v0, 36);
                v0 = 6;
                bool usable = v1 != v0;
                if (usable) {
                    // 0x002e44d8
                    charge(ctx, 2);
                } else {
                    // 0x002e44e0
                    charge(ctx, 6);
                    a0 = s1;
                    a1 = 0;
                    jal(ctx, 0x2E44E8u, gen::fn_sub_2C1CE0_002c1ce0);
                    usable = v0 != 0;
                    if (!usable) {
                        // 0x002e44f8
                        charge(ctx, 3);
                        v0 = 6;
                    }
                }
                if (usable) {
                    // 0x002e4504
                    charge(ctx, 1);
                    v0 = 0;
                }
            } else {
                // 0x002e44b4: no candidate
                charge(ctx, 3);
                v0 = 2;
            }
        } else {
            // 0x002e4484
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x002e444c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x002e4508 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x002F6E00 btlBossSetup -- 4020 bytes; frame 0x50: ra sp+0x0
// Boss battle set-up at the battle start: clears the boss block (gBtl +2836, 116 bytes), and for the boss encounters
// 416..436 / 456 sets the boss rule flags (gBtl +12 / +16), the boss AI table (+2840 = section base + 1,044 * index)
// and the boss mode word (+2948); finds the boss script's AI_EVENT_%03X_BTLSTART / ACTSTART / ACTEND procedures
// (+2844 / +2848 / +2852).
void btlBossSetup(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002f6e00
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    a0 = addiu(v0, 2836);
    a1 = 0;
    a2 = 116;
    jal(ctx, 0x2F6E18u, gen::fn_memset_00521408);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    sh(zero, v0, gbtl4::kBossMode);
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v0, v1, gbtl::kSetupEnemies);
    lhu(v0, v0, 8);
    a0 = 436;
    if (v0 == a0) {
        // encounter 436 (0x1B4): boss rules
        // 0x002f7c50
        charge(ctx, 41);
        lw(a0, v1, gbtl::kFlags);
        v0 = lui(0xFFFE);
        v0 = v0 | 0xFFFF;
        v0 = a0 & v0;
        sw(v0, v1, gbtl::kFlags);
        lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(v1, a0, gbtl::kFlags);
        v0 = lui(0xFBFF);
        v0 = v0 | 0xFFFF;
        v0 = v1 & v0;
        sw(v0, a0, gbtl::kFlags);
        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(v0, v1, gbtl4::kRules);
        v0 = v0 | 0x1;
        sw(v0, v1, gbtl4::kRules);
        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(v0, v1, gbtl4::kRules);
        v0 = v0 | 0x2;
        sw(v0, v1, gbtl4::kRules);
        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(v0, v1, gbtl4::kRules);
        v0 = v0 | 0x8;
        sw(v0, v1, gbtl4::kRules);
        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(v0, v1, gbtl4::kRules);
        v0 = v0 | 0x10;
        sw(v0, v1, gbtl4::kRules);
        lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(v1, a0, gbtl::kFlags);
        v0 = si(-1025);
        v0 = v1 & v0;
        sw(v0, a0, gbtl::kFlags);
        lw(v0, gp, kGpBossAiTbl);  // the boss AI table (1,044-byte rows) 0x7CE4BC
        v1 = addiu(v0, 21924);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        sw(v1, v0, gbtl4::kBossAiRows);
        lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(v1, a0, gbtl::kFlags);
        v0 = 0x200000;
        v0 = v1 | v0;
        sw(v0, a0, gbtl::kFlags);
    } else {
        // 0x002f6e40
        charge(ctx, 3);
        a0 = 435;
        if (v0 == a0) {
            // encounter 435 (0x1B3): boss rules
            // 0x002f7bb8
            charge(ctx, 38);
            lw(a0, v1, gbtl::kFlags);
            v0 = lui(0xFFFE);
            v0 = v0 | 0xFFFF;
            v0 = a0 & v0;
            sw(v0, v1, gbtl::kFlags);
            lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
            lw(v1, a0, gbtl::kFlags);
            v0 = lui(0xFBFF);
            v0 = v0 | 0xFFFF;
            v0 = v1 & v0;
            sw(v0, a0, gbtl::kFlags);
            lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
            lw(v0, v1, gbtl4::kRules);
            v0 = v0 | 0x1;
            sw(v0, v1, gbtl4::kRules);
            lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
            lw(v0, v1, gbtl4::kRules);
            v0 = v0 | 0x2;
            sw(v0, v1, gbtl4::kRules);
            lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
            lw(v0, v1, gbtl4::kRules);
            v0 = v0 | 0x8;
            sw(v0, v1, gbtl4::kRules);
            lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
            lw(v0, v1, gbtl4::kRules);
            v0 = v0 | 0x10;
            sw(v0, v1, gbtl4::kRules);
            lw(v0, gp, kGpBossAiTbl);  // the boss AI table (1,044-byte rows) 0x7CE4BC
            v1 = addiu(v0, 20880);
            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
            sw(v1, v0, gbtl4::kBossAiRows);
            lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
            lw(v1, a0, gbtl::kFlags);
            v0 = 0x200000;
            v0 = v1 | v0;
            sw(v0, a0, gbtl::kFlags);
        } else {
            // 0x002f6e4c
            charge(ctx, 3);
            a0 = 434;
            if (v0 == a0) {
                // encounter 434 (0x1B2): boss rules
                // 0x002f7b20
                charge(ctx, 38);
                lw(a0, v1, gbtl::kFlags);
                v0 = lui(0xFFFE);
                v0 = v0 | 0xFFFF;
                v0 = a0 & v0;
                sw(v0, v1, gbtl::kFlags);
                lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                lw(v1, a0, gbtl::kFlags);
                v0 = lui(0xFBFF);
                v0 = v0 | 0xFFFF;
                v0 = v1 & v0;
                sw(v0, a0, gbtl::kFlags);
                lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                lw(v0, v1, gbtl4::kRules);
                v0 = v0 | 0x1;
                sw(v0, v1, gbtl4::kRules);
                lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                lw(v0, v1, gbtl4::kRules);
                v0 = v0 | 0x2;
                sw(v0, v1, gbtl4::kRules);
                lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                lw(v0, v1, gbtl4::kRules);
                v0 = v0 | 0x8;
                sw(v0, v1, gbtl4::kRules);
                lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                lw(v0, v1, gbtl4::kRules);
                v0 = v0 | 0x10;
                sw(v0, v1, gbtl4::kRules);
                lw(v0, gp, kGpBossAiTbl);  // the boss AI table (1,044-byte rows) 0x7CE4BC
                v1 = addiu(v0, 19836);
                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                sw(v1, v0, gbtl4::kBossAiRows);
                lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                lw(v1, a0, gbtl::kFlags);
                v0 = 0x200000;
                v0 = v1 | v0;
                sw(v0, a0, gbtl::kFlags);
            } else {
                // 0x002f6e58
                charge(ctx, 3);
                a0 = 433;
                if (v0 == a0) {
                    // encounter 433 (0x1B1): boss rules
                    // 0x002f7a88
                    charge(ctx, 38);
                    lw(a0, v1, gbtl::kFlags);
                    v0 = lui(0xFFFE);
                    v0 = v0 | 0xFFFF;
                    v0 = a0 & v0;
                    sw(v0, v1, gbtl::kFlags);
                    lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                    lw(v1, a0, gbtl::kFlags);
                    v0 = lui(0xFBFF);
                    v0 = v0 | 0xFFFF;
                    v0 = v1 & v0;
                    sw(v0, a0, gbtl::kFlags);
                    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                    lw(v0, v1, gbtl4::kRules);
                    v0 = v0 | 0x1;
                    sw(v0, v1, gbtl4::kRules);
                    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                    lw(v0, v1, gbtl4::kRules);
                    v0 = v0 | 0x2;
                    sw(v0, v1, gbtl4::kRules);
                    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                    lw(v0, v1, gbtl4::kRules);
                    v0 = v0 | 0x8;
                    sw(v0, v1, gbtl4::kRules);
                    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                    lw(v0, v1, gbtl4::kRules);
                    v0 = v0 | 0x10;
                    sw(v0, v1, gbtl4::kRules);
                    lw(v0, gp, kGpBossAiTbl);  // the boss AI table (1,044-byte rows) 0x7CE4BC
                    v1 = addiu(v0, 18792);
                    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                    sw(v1, v0, gbtl4::kBossAiRows);
                    lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                    lw(v1, a0, gbtl::kFlags);
                    v0 = 0x200000;
                    v0 = v1 | v0;
                    sw(v0, a0, gbtl::kFlags);
                } else {
                    // 0x002f6e64
                    charge(ctx, 3);
                    a0 = 432;
                    if (v0 == a0) {
                        // encounter 432 (0x1B0): boss rules
                        // 0x002f79e0
                        charge(ctx, 42);
                        lw(a0, v1, gbtl::kFlags);
                        v0 = lui(0xFFFE);
                        v0 = v0 | 0xFFFF;
                        v0 = a0 & v0;
                        sw(v0, v1, gbtl::kFlags);
                        lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                        lw(v1, a0, gbtl::kFlags);
                        v0 = lui(0xFBFF);
                        v0 = v0 | 0xFFFF;
                        v0 = v1 & v0;
                        sw(v0, a0, gbtl::kFlags);
                        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                        lw(v0, v1, gbtl4::kRules);
                        v0 = v0 | 0x1;
                        sw(v0, v1, gbtl4::kRules);
                        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                        lw(v0, v1, gbtl4::kRules);
                        v0 = v0 | 0x2;
                        sw(v0, v1, gbtl4::kRules);
                        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                        lw(v0, v1, gbtl4::kRules);
                        v0 = v0 | 0x8;
                        sw(v0, v1, gbtl4::kRules);
                        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                        lw(v0, v1, gbtl4::kRules);
                        v0 = v0 | 0x10;
                        sw(v0, v1, gbtl4::kRules);
                        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                        lw(v0, v1, gbtl4::kRules);
                        v0 = v0 | 0x80;
                        sw(v0, v1, gbtl4::kRules);
                        lw(v0, gp, kGpBossAiTbl);  // the boss AI table (1,044-byte rows) 0x7CE4BC
                        v1 = addiu(v0, 17748);
                        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                        sw(v1, v0, gbtl4::kBossAiRows);
                        lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                        lw(v1, a0, gbtl::kFlags);
                        v0 = 0x200000;
                        v0 = v1 | v0;
                        sw(v0, a0, gbtl::kFlags);
                    } else {
                        // 0x002f6e70
                        charge(ctx, 3);
                        a0 = 431;
                        if (v0 == a0) {
                            // encounter 431 (0x1AF): boss rules
                            // 0x002f7938
                            charge(ctx, 42);
                            lw(a0, v1, gbtl::kFlags);
                            v0 = lui(0xFFFE);
                            v0 = v0 | 0xFFFF;
                            v0 = a0 & v0;
                            sw(v0, v1, gbtl::kFlags);
                            lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                            lw(v1, a0, gbtl::kFlags);
                            v0 = lui(0xFBFF);
                            v0 = v0 | 0xFFFF;
                            v0 = v1 & v0;
                            sw(v0, a0, gbtl::kFlags);
                            lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                            lw(v0, v1, gbtl4::kRules);
                            v0 = v0 | 0x1;
                            sw(v0, v1, gbtl4::kRules);
                            lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                            lw(v0, v1, gbtl4::kRules);
                            v0 = v0 | 0x2;
                            sw(v0, v1, gbtl4::kRules);
                            lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                            lw(v0, v1, gbtl4::kRules);
                            v0 = v0 | 0x8;
                            sw(v0, v1, gbtl4::kRules);
                            lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                            lw(v0, v1, gbtl4::kRules);
                            v0 = v0 | 0x10;
                            sw(v0, v1, gbtl4::kRules);
                            lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                            lw(v0, v1, gbtl4::kRules);
                            v0 = v0 | 0x80;
                            sw(v0, v1, gbtl4::kRules);
                            lw(v0, gp, kGpBossAiTbl);  // the boss AI table (1,044-byte rows) 0x7CE4BC
                            v1 = addiu(v0, 16704);
                            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                            sw(v1, v0, gbtl4::kBossAiRows);
                            lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                            lw(v1, a0, gbtl::kFlags);
                            v0 = 0x200000;
                            v0 = v1 | v0;
                            sw(v0, a0, gbtl::kFlags);
                        } else {
                            // 0x002f6e7c
                            charge(ctx, 3);
                            a0 = 430;
                            if (v0 == a0) {
                                // encounter 430 (0x1AE): boss rules
                                // 0x002f7890
                                charge(ctx, 42);
                                lw(a0, v1, gbtl::kFlags);
                                v0 = lui(0xFFFE);
                                v0 = v0 | 0xFFFF;
                                v0 = a0 & v0;
                                sw(v0, v1, gbtl::kFlags);
                                lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                lw(v1, a0, gbtl::kFlags);
                                v0 = lui(0xFBFF);
                                v0 = v0 | 0xFFFF;
                                v0 = v1 & v0;
                                sw(v0, a0, gbtl::kFlags);
                                lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                lw(v0, v1, gbtl4::kRules);
                                v0 = v0 | 0x1;
                                sw(v0, v1, gbtl4::kRules);
                                lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                lw(v0, v1, gbtl4::kRules);
                                v0 = v0 | 0x2;
                                sw(v0, v1, gbtl4::kRules);
                                lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                lw(v0, v1, gbtl4::kRules);
                                v0 = v0 | 0x8;
                                sw(v0, v1, gbtl4::kRules);
                                lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                lw(v0, v1, gbtl4::kRules);
                                v0 = v0 | 0x10;
                                sw(v0, v1, gbtl4::kRules);
                                lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                lw(v0, v1, gbtl4::kRules);
                                v0 = v0 | 0x80;
                                sw(v0, v1, gbtl4::kRules);
                                lw(v0, gp, kGpBossAiTbl);  // the boss AI table (1,044-byte rows) 0x7CE4BC
                                v1 = addiu(v0, 15660);
                                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                sw(v1, v0, gbtl4::kBossAiRows);
                                lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                lw(v1, a0, gbtl::kFlags);
                                v0 = 0x200000;
                                v0 = v1 | v0;
                                sw(v0, a0, gbtl::kFlags);
                            } else {
                                // 0x002f6e88
                                charge(ctx, 3);
                                a0 = 429;
                                if (v0 == a0) {
                                    // encounter 429 (0x1AD): boss rules
                                    // 0x002f77c8
                                    charge(ctx, 50);
                                    lw(a0, v1, gbtl::kFlags);
                                    v0 = lui(0xFFFE);
                                    v0 = v0 | 0xFFFF;
                                    v0 = a0 & v0;
                                    sw(v0, v1, gbtl::kFlags);
                                    lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                    lw(v1, a0, gbtl::kFlags);
                                    v0 = lui(0xFBFF);
                                    v0 = v0 | 0xFFFF;
                                    v0 = v1 & v0;
                                    sw(v0, a0, gbtl::kFlags);
                                    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                    lw(v0, v1, gbtl4::kRules);
                                    v0 = v0 | 0x1;
                                    sw(v0, v1, gbtl4::kRules);
                                    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                    lw(v0, v1, gbtl4::kRules);
                                    v0 = v0 | 0x2;
                                    sw(v0, v1, gbtl4::kRules);
                                    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                    lw(v0, v1, gbtl4::kRules);
                                    v0 = v0 | 0x8;
                                    sw(v0, v1, gbtl4::kRules);
                                    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                    lw(v0, v1, gbtl4::kRules);
                                    v0 = v0 | 0x10;
                                    sw(v0, v1, gbtl4::kRules);
                                    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                    lw(v0, v1, gbtl4::kRules);
                                    v0 = v0 | 0x20;
                                    sw(v0, v1, gbtl4::kRules);
                                    lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                    lw(v1, a0, gbtl::kFlags);
                                    v0 = si(-1025);
                                    v0 = v1 & v0;
                                    sw(v0, a0, gbtl::kFlags);
                                    lw(v0, gp, kGpBossAiTbl);  // the boss AI table (1,044-byte rows) 0x7CE4BC
                                    v1 = addiu(v0, 14616);
                                    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                    sw(v1, v0, gbtl4::kBossAiRows);
                                    v1 = 2;
                                    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                    sh(v1, v0, gbtl4::kBossMode);
                                    lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                    lw(v1, a0, gbtl::kFlags);
                                    v0 = 0x200000;
                                    v0 = v1 | v0;
                                    sw(v0, a0, gbtl::kFlags);
                                } else {
                                    // 0x002f6e94
                                    charge(ctx, 3);
                                    a0 = 428;
                                    if (v0 == a0) {
                                        // encounter 428 (0x1AC): boss rules
                                        // 0x002f7730
                                        charge(ctx, 38);
                                        lw(a0, v1, gbtl::kFlags);
                                        v0 = lui(0xFFFE);
                                        v0 = v0 | 0xFFFF;
                                        v0 = a0 & v0;
                                        sw(v0, v1, gbtl::kFlags);
                                        lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                        lw(v1, a0, gbtl::kFlags);
                                        v0 = lui(0xFBFF);
                                        v0 = v0 | 0xFFFF;
                                        v0 = v1 & v0;
                                        sw(v0, a0, gbtl::kFlags);
                                        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                        lw(v0, v1, gbtl4::kRules);
                                        v0 = v0 | 0x1;
                                        sw(v0, v1, gbtl4::kRules);
                                        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                        lw(v0, v1, gbtl4::kRules);
                                        v0 = v0 | 0x2;
                                        sw(v0, v1, gbtl4::kRules);
                                        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                        lw(v0, v1, gbtl4::kRules);
                                        v0 = v0 | 0x8;
                                        sw(v0, v1, gbtl4::kRules);
                                        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                        lw(v0, v1, gbtl4::kRules);
                                        v0 = v0 | 0x10;
                                        sw(v0, v1, gbtl4::kRules);
                                        lw(v0, gp, kGpBossAiTbl);  // the boss AI table (1,044-byte rows) 0x7CE4BC
                                        v1 = addiu(v0, 13572);
                                        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                        sw(v1, v0, gbtl4::kBossAiRows);
                                        lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                        lw(v1, a0, gbtl::kFlags);
                                        v0 = 0x200000;
                                        v0 = v1 | v0;
                                        sw(v0, a0, gbtl::kFlags);
                                    } else {
                                        // 0x002f6ea0
                                        charge(ctx, 3);
                                        a0 = 427;
                                        if (v0 == a0) {
                                            // encounter 427 (0x1AB): boss rules
                                            // 0x002f7688
                                            charge(ctx, 42);
                                            lw(a0, v1, gbtl::kFlags);
                                            v0 = lui(0xFFFE);
                                            v0 = v0 | 0xFFFF;
                                            v0 = a0 & v0;
                                            sw(v0, v1, gbtl::kFlags);
                                            lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                            lw(v1, a0, gbtl::kFlags);
                                            v0 = lui(0xFBFF);
                                            v0 = v0 | 0xFFFF;
                                            v0 = v1 & v0;
                                            sw(v0, a0, gbtl::kFlags);
                                            lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                            lw(v0, v1, gbtl4::kRules);
                                            v0 = v0 | 0x1;
                                            sw(v0, v1, gbtl4::kRules);
                                            lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                            lw(v0, v1, gbtl4::kRules);
                                            v0 = v0 | 0x2;
                                            sw(v0, v1, gbtl4::kRules);
                                            lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                            lw(v0, v1, gbtl4::kRules);
                                            v0 = v0 | 0x8;
                                            sw(v0, v1, gbtl4::kRules);
                                            lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                            lw(v0, v1, gbtl4::kRules);
                                            v0 = v0 | 0x10;
                                            sw(v0, v1, gbtl4::kRules);
                                            lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                            lw(v0, v1, gbtl4::kRules);
                                            v0 = v0 | 0x80;
                                            sw(v0, v1, gbtl4::kRules);
                                            lw(v0, gp, kGpBossAiTbl);  // the boss AI table (1,044-byte rows) 0x7CE4BC
                                            v1 = addiu(v0, 12528);
                                            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                            sw(v1, v0, gbtl4::kBossAiRows);
                                            lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                            lw(v1, a0, gbtl::kFlags);
                                            v0 = 0x200000;
                                            v0 = v1 | v0;
                                            sw(v0, a0, gbtl::kFlags);
                                        } else {
                                            // 0x002f6eac
                                            charge(ctx, 3);
                                            a0 = 426;
                                            if (v0 == a0) {
                                                // encounter 426 (0x1AA): boss rules
                                                // 0x002f75e0
                                                charge(ctx, 42);
                                                lw(a0, v1, gbtl::kFlags);
                                                v0 = lui(0xFFFE);
                                                v0 = v0 | 0xFFFF;
                                                v0 = a0 & v0;
                                                sw(v0, v1, gbtl::kFlags);
                                                lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                lw(v1, a0, gbtl::kFlags);
                                                v0 = lui(0xFBFF);
                                                v0 = v0 | 0xFFFF;
                                                v0 = v1 & v0;
                                                sw(v0, a0, gbtl::kFlags);
                                                lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                lw(v0, v1, gbtl4::kRules);
                                                v0 = v0 | 0x1;
                                                sw(v0, v1, gbtl4::kRules);
                                                lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                lw(v0, v1, gbtl4::kRules);
                                                v0 = v0 | 0x2;
                                                sw(v0, v1, gbtl4::kRules);
                                                lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                lw(v0, v1, gbtl4::kRules);
                                                v0 = v0 | 0x8;
                                                sw(v0, v1, gbtl4::kRules);
                                                lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                lw(v0, v1, gbtl4::kRules);
                                                v0 = v0 | 0x10;
                                                sw(v0, v1, gbtl4::kRules);
                                                lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                lw(v0, v1, gbtl4::kRules);
                                                v0 = v0 | 0x80;
                                                sw(v0, v1, gbtl4::kRules);
                                                lw(v0, gp, kGpBossAiTbl);  // the boss AI table (1,044-byte rows) 0x7CE4BC
                                                v1 = addiu(v0, 11484);
                                                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                sw(v1, v0, gbtl4::kBossAiRows);
                                                lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                lw(v1, a0, gbtl::kFlags);
                                                v0 = 0x200000;
                                                v0 = v1 | v0;
                                                sw(v0, a0, gbtl::kFlags);
                                            } else {
                                                // 0x002f6eb8
                                                charge(ctx, 3);
                                                a0 = 425;
                                                if (v0 == a0) {
                                                    // encounter 425 (0x1A9): boss rules
                                                    // 0x002f7538
                                                    charge(ctx, 42);
                                                    lw(a0, v1, gbtl::kFlags);
                                                    v0 = lui(0xFFFE);
                                                    v0 = v0 | 0xFFFF;
                                                    v0 = a0 & v0;
                                                    sw(v0, v1, gbtl::kFlags);
                                                    lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                    lw(v1, a0, gbtl::kFlags);
                                                    v0 = lui(0xFBFF);
                                                    v0 = v0 | 0xFFFF;
                                                    v0 = v1 & v0;
                                                    sw(v0, a0, gbtl::kFlags);
                                                    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                    lw(v0, v1, gbtl4::kRules);
                                                    v0 = v0 | 0x1;
                                                    sw(v0, v1, gbtl4::kRules);
                                                    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                    lw(v0, v1, gbtl4::kRules);
                                                    v0 = v0 | 0x2;
                                                    sw(v0, v1, gbtl4::kRules);
                                                    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                    lw(v0, v1, gbtl4::kRules);
                                                    v0 = v0 | 0x8;
                                                    sw(v0, v1, gbtl4::kRules);
                                                    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                    lw(v0, v1, gbtl4::kRules);
                                                    v0 = v0 | 0x10;
                                                    sw(v0, v1, gbtl4::kRules);
                                                    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                    lw(v0, v1, gbtl4::kRules);
                                                    v0 = v0 | 0x80;
                                                    sw(v0, v1, gbtl4::kRules);
                                                    lw(v0, gp, kGpBossAiTbl);  // the boss AI table (1,044-byte rows) 0x7CE4BC
                                                    v1 = addiu(v0, 10440);
                                                    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                    sw(v1, v0, gbtl4::kBossAiRows);
                                                    lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                    lw(v1, a0, gbtl::kFlags);
                                                    v0 = 0x200000;
                                                    v0 = v1 | v0;
                                                    sw(v0, a0, gbtl::kFlags);
                                                } else {
                                                    // 0x002f6ec4
                                                    charge(ctx, 3);
                                                    a0 = 424;
                                                    if (v0 == a0) {
                                                        // encounter 424 (0x1A8): boss rules
                                                        // 0x002f7490
                                                        charge(ctx, 42);
                                                        lw(a0, v1, gbtl::kFlags);
                                                        v0 = lui(0xFFFE);
                                                        v0 = v0 | 0xFFFF;
                                                        v0 = a0 & v0;
                                                        sw(v0, v1, gbtl::kFlags);
                                                        lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                        lw(v1, a0, gbtl::kFlags);
                                                        v0 = lui(0xFBFF);
                                                        v0 = v0 | 0xFFFF;
                                                        v0 = v1 & v0;
                                                        sw(v0, a0, gbtl::kFlags);
                                                        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                        lw(v0, v1, gbtl4::kRules);
                                                        v0 = v0 | 0x1;
                                                        sw(v0, v1, gbtl4::kRules);
                                                        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                        lw(v0, v1, gbtl4::kRules);
                                                        v0 = v0 | 0x2;
                                                        sw(v0, v1, gbtl4::kRules);
                                                        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                        lw(v0, v1, gbtl4::kRules);
                                                        v0 = v0 | 0x8;
                                                        sw(v0, v1, gbtl4::kRules);
                                                        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                        lw(v0, v1, gbtl4::kRules);
                                                        v0 = v0 | 0x10;
                                                        sw(v0, v1, gbtl4::kRules);
                                                        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                        lw(v0, v1, gbtl4::kRules);
                                                        v0 = v0 | 0x80;
                                                        sw(v0, v1, gbtl4::kRules);
                                                        lw(v0, gp, kGpBossAiTbl);  // the boss AI table (1,044-byte rows) 0x7CE4BC
                                                        v1 = addiu(v0, 9396);
                                                        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                        sw(v1, v0, gbtl4::kBossAiRows);
                                                        lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                        lw(v1, a0, gbtl::kFlags);
                                                        v0 = 0x200000;
                                                        v0 = v1 | v0;
                                                        sw(v0, a0, gbtl::kFlags);
                                                    } else {
                                                        // 0x002f6ed0
                                                        charge(ctx, 3);
                                                        a0 = 423;
                                                        if (v0 == a0) {
                                                            // encounter 423 (0x1A7): boss rules
                                                            // 0x002f73f8
                                                            charge(ctx, 38);
                                                            lw(a0, v1, gbtl::kFlags);
                                                            v0 = lui(0xFFFE);
                                                            v0 = v0 | 0xFFFF;
                                                            v0 = a0 & v0;
                                                            sw(v0, v1, gbtl::kFlags);
                                                            lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                            lw(v1, a0, gbtl::kFlags);
                                                            v0 = lui(0xFBFF);
                                                            v0 = v0 | 0xFFFF;
                                                            v0 = v1 & v0;
                                                            sw(v0, a0, gbtl::kFlags);
                                                            lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                            lw(v0, v1, gbtl4::kRules);
                                                            v0 = v0 | 0x1;
                                                            sw(v0, v1, gbtl4::kRules);
                                                            lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                            lw(v0, v1, gbtl4::kRules);
                                                            v0 = v0 | 0x2;
                                                            sw(v0, v1, gbtl4::kRules);
                                                            lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                            lw(v0, v1, gbtl4::kRules);
                                                            v0 = v0 | 0x8;
                                                            sw(v0, v1, gbtl4::kRules);
                                                            lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                            lw(v0, v1, gbtl4::kRules);
                                                            v0 = v0 | 0x10;
                                                            sw(v0, v1, gbtl4::kRules);
                                                            lw(v0, gp, kGpBossAiTbl);  // the boss AI table (1,044-byte rows) 0x7CE4BC
                                                            v1 = addiu(v0, 8352);
                                                            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                            sw(v1, v0, gbtl4::kBossAiRows);
                                                            lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                            lw(v1, a0, gbtl::kFlags);
                                                            v0 = 0x200000;
                                                            v0 = v1 | v0;
                                                            sw(v0, a0, gbtl::kFlags);
                                                        } else {
                                                            // 0x002f6edc
                                                            charge(ctx, 3);
                                                            a0 = 422;
                                                            if (v0 == a0) {
                                                                // encounter 422 (0x1A6): boss rules
                                                                // 0x002f7360
                                                                charge(ctx, 38);
                                                                lw(a0, v1, gbtl::kFlags);
                                                                v0 = lui(0xFFFE);
                                                                v0 = v0 | 0xFFFF;
                                                                v0 = a0 & v0;
                                                                sw(v0, v1, gbtl::kFlags);
                                                                lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                lw(v1, a0, gbtl::kFlags);
                                                                v0 = lui(0xFBFF);
                                                                v0 = v0 | 0xFFFF;
                                                                v0 = v1 & v0;
                                                                sw(v0, a0, gbtl::kFlags);
                                                                lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                lw(v0, v1, gbtl4::kRules);
                                                                v0 = v0 | 0x1;
                                                                sw(v0, v1, gbtl4::kRules);
                                                                lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                lw(v0, v1, gbtl4::kRules);
                                                                v0 = v0 | 0x2;
                                                                sw(v0, v1, gbtl4::kRules);
                                                                lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                lw(v0, v1, gbtl4::kRules);
                                                                v0 = v0 | 0x8;
                                                                sw(v0, v1, gbtl4::kRules);
                                                                lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                lw(v0, v1, gbtl4::kRules);
                                                                v0 = v0 | 0x10;
                                                                sw(v0, v1, gbtl4::kRules);
                                                                lw(v0, gp, kGpBossAiTbl);  // the boss AI table (1,044-byte rows) 0x7CE4BC
                                                                v1 = addiu(v0, 7308);
                                                                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                sw(v1, v0, gbtl4::kBossAiRows);
                                                                lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                lw(v1, a0, gbtl::kFlags);
                                                                v0 = 0x200000;
                                                                v0 = v1 | v0;
                                                                sw(v0, a0, gbtl::kFlags);
                                                            } else {
                                                                // 0x002f6ee8
                                                                charge(ctx, 3);
                                                                a0 = 421;
                                                                if (v0 == a0) {
                                                                    // encounter 421 (0x1A5): boss rules
                                                                    // 0x002f72c8
                                                                    charge(ctx, 38);
                                                                    lw(a0, v1, gbtl::kFlags);
                                                                    v0 = lui(0xFFFE);
                                                                    v0 = v0 | 0xFFFF;
                                                                    v0 = a0 & v0;
                                                                    sw(v0, v1, gbtl::kFlags);
                                                                    lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                    lw(v1, a0, gbtl::kFlags);
                                                                    v0 = lui(0xFBFF);
                                                                    v0 = v0 | 0xFFFF;
                                                                    v0 = v1 & v0;
                                                                    sw(v0, a0, gbtl::kFlags);
                                                                    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                    lw(v0, v1, gbtl4::kRules);
                                                                    v0 = v0 | 0x1;
                                                                    sw(v0, v1, gbtl4::kRules);
                                                                    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                    lw(v0, v1, gbtl4::kRules);
                                                                    v0 = v0 | 0x2;
                                                                    sw(v0, v1, gbtl4::kRules);
                                                                    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                    lw(v0, v1, gbtl4::kRules);
                                                                    v0 = v0 | 0x8;
                                                                    sw(v0, v1, gbtl4::kRules);
                                                                    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                    lw(v0, v1, gbtl4::kRules);
                                                                    v0 = v0 | 0x10;
                                                                    sw(v0, v1, gbtl4::kRules);
                                                                    lw(v0, gp, kGpBossAiTbl);  // the boss AI table (1,044-byte rows) 0x7CE4BC
                                                                    v1 = addiu(v0, 6264);
                                                                    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                    sw(v1, v0, gbtl4::kBossAiRows);
                                                                    lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                    lw(v1, a0, gbtl::kFlags);
                                                                    v0 = 0x200000;
                                                                    v0 = v1 | v0;
                                                                    sw(v0, a0, gbtl::kFlags);
                                                                } else {
                                                                    // 0x002f6ef4
                                                                    charge(ctx, 3);
                                                                    a0 = 420;
                                                                    if (v0 == a0) {
                                                                        // encounter 420 (0x1A4): boss rules
                                                                        // 0x002f7230
                                                                        charge(ctx, 38);
                                                                        lw(a0, v1, gbtl::kFlags);
                                                                        v0 = lui(0xFFFE);
                                                                        v0 = v0 | 0xFFFF;
                                                                        v0 = a0 & v0;
                                                                        sw(v0, v1, gbtl::kFlags);
                                                                        lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                        lw(v1, a0, gbtl::kFlags);
                                                                        v0 = lui(0xFBFF);
                                                                        v0 = v0 | 0xFFFF;
                                                                        v0 = v1 & v0;
                                                                        sw(v0, a0, gbtl::kFlags);
                                                                        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                        lw(v0, v1, gbtl4::kRules);
                                                                        v0 = v0 | 0x1;
                                                                        sw(v0, v1, gbtl4::kRules);
                                                                        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                        lw(v0, v1, gbtl4::kRules);
                                                                        v0 = v0 | 0x2;
                                                                        sw(v0, v1, gbtl4::kRules);
                                                                        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                        lw(v0, v1, gbtl4::kRules);
                                                                        v0 = v0 | 0x8;
                                                                        sw(v0, v1, gbtl4::kRules);
                                                                        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                        lw(v0, v1, gbtl4::kRules);
                                                                        v0 = v0 | 0x10;
                                                                        sw(v0, v1, gbtl4::kRules);
                                                                        lw(v0, gp, kGpBossAiTbl);  // the boss AI table (1,044-byte rows) 0x7CE4BC
                                                                        v1 = addiu(v0, 5220);
                                                                        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                        sw(v1, v0, gbtl4::kBossAiRows);
                                                                        lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                        lw(v1, a0, gbtl::kFlags);
                                                                        v0 = 0x200000;
                                                                        v0 = v1 | v0;
                                                                        sw(v0, a0, gbtl::kFlags);
                                                                    } else {
                                                                        // 0x002f6f00
                                                                        charge(ctx, 3);
                                                                        a0 = 419;
                                                                        if (v0 == a0) {
                                                                            // encounter 419 (0x1A3): boss rules
                                                                            // 0x002f7198
                                                                            charge(ctx, 38);
                                                                            lw(a0, v1, gbtl::kFlags);
                                                                            v0 = lui(0xFFFE);
                                                                            v0 = v0 | 0xFFFF;
                                                                            v0 = a0 & v0;
                                                                            sw(v0, v1, gbtl::kFlags);
                                                                            lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                            lw(v1, a0, gbtl::kFlags);
                                                                            v0 = lui(0xFBFF);
                                                                            v0 = v0 | 0xFFFF;
                                                                            v0 = v1 & v0;
                                                                            sw(v0, a0, gbtl::kFlags);
                                                                            lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                            lw(v0, v1, gbtl4::kRules);
                                                                            v0 = v0 | 0x1;
                                                                            sw(v0, v1, gbtl4::kRules);
                                                                            lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                            lw(v0, v1, gbtl4::kRules);
                                                                            v0 = v0 | 0x2;
                                                                            sw(v0, v1, gbtl4::kRules);
                                                                            lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                            lw(v0, v1, gbtl4::kRules);
                                                                            v0 = v0 | 0x8;
                                                                            sw(v0, v1, gbtl4::kRules);
                                                                            lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                            lw(v0, v1, gbtl4::kRules);
                                                                            v0 = v0 | 0x10;
                                                                            sw(v0, v1, gbtl4::kRules);
                                                                            lw(v0, gp, kGpBossAiTbl);  // the boss AI table (1,044-byte rows) 0x7CE4BC
                                                                            v1 = addiu(v0, 4176);
                                                                            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                            sw(v1, v0, gbtl4::kBossAiRows);
                                                                            lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                            lw(v1, a0, gbtl::kFlags);
                                                                            v0 = 0x200000;
                                                                            v0 = v1 | v0;
                                                                            sw(v0, a0, gbtl::kFlags);
                                                                        } else {
                                                                            // 0x002f6f0c
                                                                            charge(ctx, 3);
                                                                            a0 = 418;
                                                                            if (v0 == a0) {
                                                                                // encounter 418 (0x1A2): boss rules
                                                                                // 0x002f7100
                                                                                charge(ctx, 38);
                                                                                lw(a0, v1, gbtl::kFlags);
                                                                                v0 = lui(0xFFFE);
                                                                                v0 = v0 | 0xFFFF;
                                                                                v0 = a0 & v0;
                                                                                sw(v0, v1, gbtl::kFlags);
                                                                                lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                                lw(v1, a0, gbtl::kFlags);
                                                                                v0 = lui(0xFBFF);
                                                                                v0 = v0 | 0xFFFF;
                                                                                v0 = v1 & v0;
                                                                                sw(v0, a0, gbtl::kFlags);
                                                                                lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                                lw(v0, v1, gbtl4::kRules);
                                                                                v0 = v0 | 0x1;
                                                                                sw(v0, v1, gbtl4::kRules);
                                                                                lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                                lw(v0, v1, gbtl4::kRules);
                                                                                v0 = v0 | 0x2;
                                                                                sw(v0, v1, gbtl4::kRules);
                                                                                lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                                lw(v0, v1, gbtl4::kRules);
                                                                                v0 = v0 | 0x8;
                                                                                sw(v0, v1, gbtl4::kRules);
                                                                                lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                                lw(v0, v1, gbtl4::kRules);
                                                                                v0 = v0 | 0x10;
                                                                                sw(v0, v1, gbtl4::kRules);
                                                                                lw(v0, gp, kGpBossAiTbl);  // the boss AI table (1,044-byte rows) 0x7CE4BC
                                                                                v1 = addiu(v0, 3132);
                                                                                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                                sw(v1, v0, gbtl4::kBossAiRows);
                                                                                lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                                lw(v1, a0, gbtl::kFlags);
                                                                                v0 = 0x200000;
                                                                                v0 = v1 | v0;
                                                                                sw(v0, a0, gbtl::kFlags);
                                                                            } else {
                                                                                // 0x002f6f18
                                                                                charge(ctx, 3);
                                                                                a0 = 417;
                                                                                if (v0 == a0) {
                                                                                    // encounter 417 (0x1A1): boss rules
                                                                                    // 0x002f7068
                                                                                    charge(ctx, 38);
                                                                                    lw(a0, v1, gbtl::kFlags);
                                                                                    v0 = lui(0xFFFE);
                                                                                    v0 = v0 | 0xFFFF;
                                                                                    v0 = a0 & v0;
                                                                                    sw(v0, v1, gbtl::kFlags);
                                                                                    lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                                    lw(v1, a0, gbtl::kFlags);
                                                                                    v0 = lui(0xFBFF);
                                                                                    v0 = v0 | 0xFFFF;
                                                                                    v0 = v1 & v0;
                                                                                    sw(v0, a0, gbtl::kFlags);
                                                                                    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                                    lw(v0, v1, gbtl4::kRules);
                                                                                    v0 = v0 | 0x1;
                                                                                    sw(v0, v1, gbtl4::kRules);
                                                                                    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                                    lw(v0, v1, gbtl4::kRules);
                                                                                    v0 = v0 | 0x2;
                                                                                    sw(v0, v1, gbtl4::kRules);
                                                                                    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                                    lw(v0, v1, gbtl4::kRules);
                                                                                    v0 = v0 | 0x8;
                                                                                    sw(v0, v1, gbtl4::kRules);
                                                                                    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                                    lw(v0, v1, gbtl4::kRules);
                                                                                    v0 = v0 | 0x10;
                                                                                    sw(v0, v1, gbtl4::kRules);
                                                                                    lw(v0, gp, kGpBossAiTbl);  // the boss AI table (1,044-byte rows) 0x7CE4BC
                                                                                    v1 = addiu(v0, 2088);
                                                                                    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                                    sw(v1, v0, gbtl4::kBossAiRows);
                                                                                    lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                                    lw(v1, a0, gbtl::kFlags);
                                                                                    v0 = 0x200000;
                                                                                    v0 = v1 | v0;
                                                                                    sw(v0, a0, gbtl::kFlags);
                                                                                } else {
                                                                                    // 0x002f6f24
                                                                                    charge(ctx, 3);
                                                                                    a0 = 416;
                                                                                    if (v0 == a0) {
                                                                                        // encounter 416 (0x1A0): boss rules
                                                                                        // 0x002f6fc0
                                                                                        charge(ctx, 42);
                                                                                        lw(a0, v1, gbtl::kFlags);
                                                                                        v0 = lui(0xFFFE);
                                                                                        v0 = v0 | 0xFFFF;
                                                                                        v0 = a0 & v0;
                                                                                        sw(v0, v1, gbtl::kFlags);
                                                                                        lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                                        lw(v1, a0, gbtl::kFlags);
                                                                                        v0 = lui(0xFBFF);
                                                                                        v0 = v0 | 0xFFFF;
                                                                                        v0 = v1 & v0;
                                                                                        sw(v0, a0, gbtl::kFlags);
                                                                                        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                                        lw(v0, v1, gbtl4::kRules);
                                                                                        v0 = v0 | 0x1;
                                                                                        sw(v0, v1, gbtl4::kRules);
                                                                                        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                                        lw(v0, v1, gbtl4::kRules);
                                                                                        v0 = v0 | 0x2;
                                                                                        sw(v0, v1, gbtl4::kRules);
                                                                                        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                                        lw(v0, v1, gbtl4::kRules);
                                                                                        v0 = v0 | 0x8;
                                                                                        sw(v0, v1, gbtl4::kRules);
                                                                                        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                                        lw(v0, v1, gbtl4::kRules);
                                                                                        v0 = v0 | 0x10;
                                                                                        sw(v0, v1, gbtl4::kRules);
                                                                                        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                                        lw(v0, v1, gbtl4::kRules);
                                                                                        v0 = v0 | 0x80;
                                                                                        sw(v0, v1, gbtl4::kRules);
                                                                                        lw(v0, gp, kGpBossAiTbl);  // the boss AI table (1,044-byte rows) 0x7CE4BC
                                                                                        v1 = addiu(v0, 1044);
                                                                                        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                                        sw(v1, v0, gbtl4::kBossAiRows);
                                                                                        lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                                        lw(v1, a0, gbtl::kFlags);
                                                                                        v0 = 0x200000;
                                                                                        v0 = v1 | v0;
                                                                                        sw(v0, a0, gbtl::kFlags);
                                                                                    } else {
                                                                                        // 0x002f6f30
                                                                                        charge(ctx, 3);
                                                                                        a0 = 456;
                                                                                        if (v0 == a0) {
                                                                                            // encounter 456 (0x1C8): boss rules
                                                                                            // 0x002f6f44
                                                                                            charge(ctx, 31);
                                                                                            lw(a0, v1, gbtl::kFlags);
                                                                                            v0 = lui(0xFFFE);
                                                                                            v0 = v0 | 0xFFFF;
                                                                                            v0 = a0 & v0;
                                                                                            sw(v0, v1, gbtl::kFlags);
                                                                                            lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                                            lw(v1, a0, gbtl::kFlags);
                                                                                            v0 = lui(0xFBFF);
                                                                                            v0 = v0 | 0xFFFF;
                                                                                            v0 = v1 & v0;
                                                                                            sw(v0, a0, gbtl::kFlags);
                                                                                            lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                                            lw(v0, v1, gbtl4::kRules);
                                                                                            v0 = v0 | 0x40;
                                                                                            sw(v0, v1, gbtl4::kRules);
                                                                                            lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                                            lw(v0, v1, gbtl4::kRules);
                                                                                            v0 = v0 | 0x1;
                                                                                            sw(v0, v1, gbtl4::kRules);
                                                                                            lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                                            lw(v0, v1, gbtl4::kRules);
                                                                                            v0 = v0 | 0x10;
                                                                                            sw(v0, v1, gbtl4::kRules);
                                                                                            lw(v1, gp, kGpBossAiTbl);  // the boss AI table (1,044-byte rows) 0x7CE4BC
                                                                                            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                                            sw(v1, v0, gbtl4::kBossAiRows);
                                                                                            v1 = 1;
                                                                                            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                                            sh(v1, v0, gbtl4::kBossMode);
                                                                                        } else {
                                                                                            // 0x002f6f3c
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
                        }
                    }
                }
            }
        }
    }
    // 0x002f7cf4
    charge(ctx, 48);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v0, v0, gbtl::kSetupEnemies);
    lhu(a2, v0, 8);
    a0 = addiu(sp, 0x10);
    a1 = 0x6A0000;
    a1 = addiu(a1, -22768);  // "AI_EVENT_%03X_BTLSTART"
    jal(ctx, 0x2F7D0Cu, gen::fn_sprintf_00523ac8);
    lw(a0, gp, kGpBossScript);  // the boss AI script 0x7CE4D0
    a1 = addiu(sp, 0x10);
    jal(ctx, 0x2F7D1Cu, gen::fn_scrFindPrcdIdxByName_0035c090);
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    sw(v0, v1, gbtl4::kBossEvtStart);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v0, v0, gbtl::kSetupEnemies);
    lhu(a2, v0, 8);
    a0 = addiu(sp, 0x10);
    a1 = 0x6A0000;
    a1 = addiu(a1, -22736);  // "AI_EVENT_%03X_ACTSTART"
    jal(ctx, 0x2F7D44u, gen::fn_sprintf_00523ac8);
    lw(a0, gp, kGpBossScript);  // the boss AI script 0x7CE4D0
    a1 = addiu(sp, 0x10);
    jal(ctx, 0x2F7D54u, gen::fn_scrFindPrcdIdxByName_0035c090);
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    sw(v0, v1, gbtl4::kBossEvtActStart);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v0, v0, gbtl::kSetupEnemies);
    lhu(a2, v0, 8);
    a0 = addiu(sp, 0x10);
    a1 = 0x6A0000;
    a1 = addiu(a1, -22704);  // "AI_EVENT_%03X_ACTEND"
    jal(ctx, 0x2F7D7Cu, gen::fn_sprintf_00523ac8);
    lw(a0, gp, kGpBossScript);  // the boss AI script 0x7CE4D0
    a1 = addiu(sp, 0x10);
    jal(ctx, 0x2F7D8Cu, gen::fn_scrFindPrcdIdxByName_0035c090);
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    sw(v0, v1, gbtl4::kBossEvtActEnd);
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    sw(zero, v1, gbtl::kBossTask);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x002F9710 sub_2F9710 -- 1092 bytes; frame 0x10: ra sp+0x0
// [btlBossRequestSound] Hold callback of the boss sound packet: requests the encounter's "snd_benc/boss/eXXX.pak"
// (416..436, 456) into gBtl +2836.
void sub_2F9710(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002f9710
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v1, v1, gbtl::kSetupEnemies);
    lhu(v1, v1, 8);
    a0 = 436;
    if (v1 == a0) {
        // 0x002f9b28
        charge(ctx, 7);
        a0 = 0x6A0000;
        a0 = addiu(a0, -22000);  // "snd_benc/boss/e1B4.pak"
        a1 = 1;
        jal(ctx, 0x2F9B34u, gen::fn_H_Cdvd_Request_00100d80);
        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
        sw(v0, v1, gbtl4::kBossBlock);
    } else {
        // 0x002f9730
        charge(ctx, 3);
        a0 = 435;
        if (v1 == a0) {
            // 0x002f9b04
            charge(ctx, 9);
            a0 = 0x6A0000;
            a0 = addiu(a0, -22032);  // "snd_benc/boss/e1B3.pak"
            a1 = 1;
            jal(ctx, 0x2F9B10u, gen::fn_H_Cdvd_Request_00100d80);
            lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
            sw(v0, v1, gbtl4::kBossBlock);
        } else {
            // 0x002f973c
            charge(ctx, 3);
            a0 = 434;
            if (v1 == a0) {
                // 0x002f9ae0
                charge(ctx, 9);
                a0 = 0x6A0000;
                a0 = addiu(a0, -22064);  // "snd_benc/boss/e1B2.pak"
                a1 = 1;
                jal(ctx, 0x2F9AECu, gen::fn_H_Cdvd_Request_00100d80);
                lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                sw(v0, v1, gbtl4::kBossBlock);
            } else {
                // 0x002f9748
                charge(ctx, 3);
                a0 = 433;
                if (v1 == a0) {
                    // 0x002f9abc
                    charge(ctx, 9);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, -22096);  // "snd_benc/boss/e1B1.pak"
                    a1 = 1;
                    jal(ctx, 0x2F9AC8u, gen::fn_H_Cdvd_Request_00100d80);
                    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                    sw(v0, v1, gbtl4::kBossBlock);
                } else {
                    // 0x002f9754
                    charge(ctx, 3);
                    a0 = 432;
                    if (v1 == a0) {
                        // 0x002f9a98
                        charge(ctx, 9);
                        a0 = 0x6A0000;
                        a0 = addiu(a0, -22128);  // "snd_benc/boss/e1B0.pak"
                        a1 = 1;
                        jal(ctx, 0x2F9AA4u, gen::fn_H_Cdvd_Request_00100d80);
                        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                        sw(v0, v1, gbtl4::kBossBlock);
                    } else {
                        // 0x002f9760
                        charge(ctx, 3);
                        a0 = 431;
                        if (v1 == a0) {
                            // 0x002f9a74
                            charge(ctx, 9);
                            a0 = 0x6A0000;
                            a0 = addiu(a0, -22160);  // "snd_benc/boss/e1AF.pak"
                            a1 = 1;
                            jal(ctx, 0x2F9A80u, gen::fn_H_Cdvd_Request_00100d80);
                            lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                            sw(v0, v1, gbtl4::kBossBlock);
                        } else {
                            // 0x002f976c
                            charge(ctx, 3);
                            a0 = 430;
                            if (v1 == a0) {
                                // 0x002f9a50
                                charge(ctx, 9);
                                a0 = 0x6A0000;
                                a0 = addiu(a0, -22192);  // "snd_benc/boss/e1AE.pak"
                                a1 = 1;
                                jal(ctx, 0x2F9A5Cu, gen::fn_H_Cdvd_Request_00100d80);
                                lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                sw(v0, v1, gbtl4::kBossBlock);
                            } else {
                                // 0x002f9778
                                charge(ctx, 3);
                                a0 = 429;
                                if (v1 == a0) {
                                    // 0x002f9a2c
                                    charge(ctx, 9);
                                    a0 = 0x6A0000;
                                    a0 = addiu(a0, -22224);  // "snd_benc/boss/e1AD.pak"
                                    a1 = 1;
                                    jal(ctx, 0x2F9A38u, gen::fn_H_Cdvd_Request_00100d80);
                                    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                    sw(v0, v1, gbtl4::kBossBlock);
                                } else {
                                    // 0x002f9784
                                    charge(ctx, 3);
                                    a0 = 428;
                                    if (v1 == a0) {
                                        // 0x002f9a08
                                        charge(ctx, 9);
                                        a0 = 0x6A0000;
                                        a0 = addiu(a0, -22256);  // "snd_benc/boss/e1AC.pak"
                                        a1 = 1;
                                        jal(ctx, 0x2F9A14u, gen::fn_H_Cdvd_Request_00100d80);
                                        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                        sw(v0, v1, gbtl4::kBossBlock);
                                    } else {
                                        // 0x002f9790
                                        charge(ctx, 3);
                                        a0 = 427;
                                        if (v1 == a0) {
                                            // 0x002f99e4
                                            charge(ctx, 9);
                                            a0 = 0x6A0000;
                                            a0 = addiu(a0, -22288);  // "snd_benc/boss/e1AB.pak"
                                            a1 = 1;
                                            jal(ctx, 0x2F99F0u, gen::fn_H_Cdvd_Request_00100d80);
                                            lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                            sw(v0, v1, gbtl4::kBossBlock);
                                        } else {
                                            // 0x002f979c
                                            charge(ctx, 3);
                                            a0 = 426;
                                            if (v1 == a0) {
                                                // 0x002f99c0
                                                charge(ctx, 9);
                                                a0 = 0x6A0000;
                                                a0 = addiu(a0, -22320);  // "snd_benc/boss/e1AA.pak"
                                                a1 = 1;
                                                jal(ctx, 0x2F99CCu, gen::fn_H_Cdvd_Request_00100d80);
                                                lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                sw(v0, v1, gbtl4::kBossBlock);
                                            } else {
                                                // 0x002f97a8
                                                charge(ctx, 3);
                                                a0 = 425;
                                                if (v1 == a0) {
                                                    // 0x002f999c
                                                    charge(ctx, 9);
                                                    a0 = 0x6A0000;
                                                    a0 = addiu(a0, -22352);  // "snd_benc/boss/e1A9.pak"
                                                    a1 = 1;
                                                    jal(ctx, 0x2F99A8u, gen::fn_H_Cdvd_Request_00100d80);
                                                    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                    sw(v0, v1, gbtl4::kBossBlock);
                                                } else {
                                                    // 0x002f97b4
                                                    charge(ctx, 3);
                                                    a0 = 424;
                                                    if (v1 == a0) {
                                                        // 0x002f9978
                                                        charge(ctx, 9);
                                                        a0 = 0x6A0000;
                                                        a0 = addiu(a0, -22384);  // "snd_benc/boss/e1A8.pak"
                                                        a1 = 1;
                                                        jal(ctx, 0x2F9984u, gen::fn_H_Cdvd_Request_00100d80);
                                                        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                        sw(v0, v1, gbtl4::kBossBlock);
                                                    } else {
                                                        // 0x002f97c0
                                                        charge(ctx, 3);
                                                        a0 = 423;
                                                        if (v1 == a0) {
                                                            // 0x002f9954
                                                            charge(ctx, 9);
                                                            a0 = 0x6A0000;
                                                            a0 = addiu(a0, -22416);  // "snd_benc/boss/e1A7.pak"
                                                            a1 = 1;
                                                            jal(ctx, 0x2F9960u, gen::fn_H_Cdvd_Request_00100d80);
                                                            lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                            sw(v0, v1, gbtl4::kBossBlock);
                                                        } else {
                                                            // 0x002f97cc
                                                            charge(ctx, 3);
                                                            a0 = 422;
                                                            if (v1 == a0) {
                                                                // 0x002f9930
                                                                charge(ctx, 9);
                                                                a0 = 0x6A0000;
                                                                a0 = addiu(a0, -22448);  // "snd_benc/boss/e1A6.pak"
                                                                a1 = 1;
                                                                jal(ctx, 0x2F993Cu, gen::fn_H_Cdvd_Request_00100d80);
                                                                lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                sw(v0, v1, gbtl4::kBossBlock);
                                                            } else {
                                                                // 0x002f97d8
                                                                charge(ctx, 3);
                                                                a0 = 421;
                                                                if (v1 == a0) {
                                                                    // 0x002f990c
                                                                    charge(ctx, 9);
                                                                    a0 = 0x6A0000;
                                                                    a0 = addiu(a0, -22480);  // "snd_benc/boss/e1A5.pak"
                                                                    a1 = 1;
                                                                    jal(ctx, 0x2F9918u, gen::fn_H_Cdvd_Request_00100d80);
                                                                    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                    sw(v0, v1, gbtl4::kBossBlock);
                                                                } else {
                                                                    // 0x002f97e4
                                                                    charge(ctx, 3);
                                                                    a0 = 420;
                                                                    if (v1 == a0) {
                                                                        // 0x002f98e8
                                                                        charge(ctx, 9);
                                                                        a0 = 0x6A0000;
                                                                        a0 = addiu(a0, -22512);  // "snd_benc/boss/e1A4.pak"
                                                                        a1 = 1;
                                                                        jal(ctx, 0x2F98F4u, gen::fn_H_Cdvd_Request_00100d80);
                                                                        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                        sw(v0, v1, gbtl4::kBossBlock);
                                                                    } else {
                                                                        // 0x002f97f0
                                                                        charge(ctx, 3);
                                                                        a0 = 419;
                                                                        if (v1 == a0) {
                                                                            // 0x002f98c4
                                                                            charge(ctx, 9);
                                                                            a0 = 0x6A0000;
                                                                            a0 = addiu(a0, -22544);  // "snd_benc/boss/e1A3.pak"
                                                                            a1 = 1;
                                                                            jal(ctx, 0x2F98D0u, gen::fn_H_Cdvd_Request_00100d80);
                                                                            lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                            sw(v0, v1, gbtl4::kBossBlock);
                                                                        } else {
                                                                            // 0x002f97fc
                                                                            charge(ctx, 3);
                                                                            a0 = 418;
                                                                            if (v1 == a0) {
                                                                                // 0x002f98a0
                                                                                charge(ctx, 9);
                                                                                a0 = 0x6A0000;
                                                                                a0 = addiu(a0, -22576);  // "snd_benc/boss/e1A2.pak"
                                                                                a1 = 1;
                                                                                jal(ctx, 0x2F98ACu, gen::fn_H_Cdvd_Request_00100d80);
                                                                                lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                                sw(v0, v1, gbtl4::kBossBlock);
                                                                            } else {
                                                                                // 0x002f9808
                                                                                charge(ctx, 3);
                                                                                a0 = 417;
                                                                                if (v1 == a0) {
                                                                                    // 0x002f987c
                                                                                    charge(ctx, 9);
                                                                                    a0 = 0x6A0000;
                                                                                    a0 = addiu(a0, -22608);  // "snd_benc/boss/e1A1.pak"
                                                                                    a1 = 1;
                                                                                    jal(ctx, 0x2F9888u, gen::fn_H_Cdvd_Request_00100d80);
                                                                                    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                                    sw(v0, v1, gbtl4::kBossBlock);
                                                                                } else {
                                                                                    // 0x002f9814
                                                                                    charge(ctx, 3);
                                                                                    a0 = 416;
                                                                                    if (v1 == a0) {
                                                                                        // 0x002f9858
                                                                                        charge(ctx, 9);
                                                                                        a0 = 0x6A0000;
                                                                                        a0 = addiu(a0, -22640);  // "snd_benc/boss/e1A0.pak"
                                                                                        a1 = 1;
                                                                                        jal(ctx, 0x2F9864u, gen::fn_H_Cdvd_Request_00100d80);
                                                                                        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                                        sw(v0, v1, gbtl4::kBossBlock);
                                                                                    } else {
                                                                                        // 0x002f9820
                                                                                        charge(ctx, 3);
                                                                                        a0 = 456;
                                                                                        if (v1 == a0) {
                                                                                            // 0x002f9834
                                                                                            charge(ctx, 9);
                                                                                            a0 = 0x6A0000;
                                                                                            a0 = addiu(a0, -22672);  // "snd_benc/boss/e1C8.pak"
                                                                                            a1 = 1;
                                                                                            jal(ctx, 0x2F9840u, gen::fn_H_Cdvd_Request_00100d80);
                                                                                            lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                                                                            sw(v0, v1, gbtl4::kBossBlock);
                                                                                        } else {
                                                                                            // 0x002f982c
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
                        }
                    }
                }
            }
        }
    }
    // 0x002f9b44 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002FC5D0 sub_2FC5D0 -- 1228 bytes; leaf frame (no stack)
// [btlBossGetReach] Boss reach (in $f0): with the boss rules on, the distance a unit stops at before boss 241 and the
// other big bosses for attack / skill motions 4 / 5 / 6 / 11 (radius * scale + a per-boss constant); -1.0 when none.
// Arguments: a0 btlUnit, a1 target btlUnit, a2 motion.
void sub_2FC5D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x002fc5d0
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v1, v0, gbtl::kFlags);
    v0 = 0x200000;
    v0 = v1 & v0;
    if (v0 != 0) {
        // 0x002fc5f8
        charge(ctx, 4);
        lbu(v1, a1, unit::kSide);
        v0 = 1;
        if (v1 == v0) {
            // 0x002fc618
            charge(ctx, 4);
            lbu(v0, a0, unit::kSide);
            a0 = 2;
            if (v0 == a0) {
                // 0x002fc628
                charge(ctx, 4);
                lhu(v1, a1, unit::kId);
                v0 = 241;
                if (v1 != v0) {
                    // 0x002fc638
                    charge(ctx, 2);
                    goto L_002fc68c;
                }
                // 0x002fc640
                charge(ctx, 3);
                v0 = a2 & 0xFFFF;
                if (v0 != a0) {
                    // 0x002fc64c
                    charge(ctx, 2);
                    if (v0 == 0) {
                        goto L_002fc664;
                    }
                    // 0x002fc654
                    charge(ctx, 4);
                    v0 = lui(0xBF80);
                    mtc1(v0, f0);
                    // 0x002fca94 (the shared epilogue, written out on this path)
                    charge(ctx, 2);
                    return;
                }
            L_002fc664:
                charge(ctx, 10);
                lwc1(f3, a1, 144);
                lwc1(f2, a1, 44);
                v0 = 0x43FA0000;
                mtc1(v0, f1);
                mtc1(zero, f0);
                adda_s(f0, f1);
                madd_s(f0, f3, f2);
                // 0x002fca94 (the shared epilogue, written out on this path)
                charge(ctx, 2);
                return;
            }
        L_002fc68c:
            charge(ctx, 4);
            v1 = a2 & 0xFFFF;
            v0 = 11;
            if (v1 != v0) {
                // 0x002fc69c
                charge(ctx, 3);
                v0 = 6;
                if (v1 == v0) {
                    goto L_002fc6d0;
                }
                // 0x002fc6a8
                charge(ctx, 3);
                v0 = 5;
                if (v1 == v0) {
                    goto L_002fc6d0;
                }
                // 0x002fc6b4
                charge(ctx, 3);
                v0 = 4;
                if (v1 == v0) {
                    goto L_002fc6d0;
                }
                // 0x002fc6c0
                charge(ctx, 4);
                v0 = lui(0xBF80);
                mtc1(v0, f0);
                // 0x002fca94 (the shared epilogue, written out on this path)
                charge(ctx, 2);
                return;
            }
        L_002fc6d0:
            charge(ctx, 4);
            lhu(v0, a1, 164);
            v1 = 241;
            if (v0 == v1) {
                // 0x002fca54
                charge(ctx, 14);
                lwc1(f3, a1, 144);
                lwc1(f2, a1, 44);
                v0 = 0x43E10000;
                mtc1(v0, f1);
                mtc1(zero, f0);
                adda_s(f0, f1);
                madd_s(f1, f3, f2);
                v0 = 0x42C80000;
                mtc1(v0, f0);
                add_s(f0, f0, f1);
            } else {
                // 0x002fc6e0
                charge(ctx, 3);
                v1 = 431;
                if (v0 != v1) {
                    // 0x002fc6ec
                    charge(ctx, 3);
                    v1 = 294;
                    if (v0 == v1) {
                        goto L_002fca8c;
                    }
                    // 0x002fc6f8
                    charge(ctx, 3);
                    v1 = 274;
                    if (v0 == v1) {
                        goto L_002fca8c;
                    }
                    // 0x002fc704
                    charge(ctx, 3);
                    v1 = 296;
                    if (v0 != v1) {
                        // 0x002fc710
                        charge(ctx, 3);
                        v1 = 293;
                        if (v0 == v1) {
                            goto L_002fca24;
                        }
                        // 0x002fc71c
                        charge(ctx, 3);
                        v1 = 292;
                        if (v0 == v1) {
                            goto L_002fca24;
                        }
                        // 0x002fc728
                        charge(ctx, 3);
                        v1 = 291;
                        if (v0 == v1) {
                            goto L_002fca24;
                        }
                        // 0x002fc734
                        charge(ctx, 3);
                        v1 = 290;
                        if (v0 == v1) {
                            goto L_002fca24;
                        }
                        // 0x002fc740
                        charge(ctx, 3);
                        v1 = 289;
                        if (v0 == v1) {
                            goto L_002fca24;
                        }
                        // 0x002fc74c
                        charge(ctx, 3);
                        v1 = 288;
                        if (v0 == v1) {
                            goto L_002fca24;
                        }
                        // 0x002fc758
                        charge(ctx, 3);
                        v1 = 287;
                        if (v0 == v1) {
                            goto L_002fca24;
                        }
                        // 0x002fc764
                        charge(ctx, 3);
                        v1 = 286;
                        if (v0 == v1) {
                            goto L_002fca24;
                        }
                        // 0x002fc770
                        charge(ctx, 3);
                        v1 = 285;
                        if (v0 == v1) {
                            goto L_002fca24;
                        }
                        // 0x002fc77c
                        charge(ctx, 3);
                        v1 = 284;
                        if (v0 == v1) {
                            goto L_002fca24;
                        }
                        // 0x002fc788
                        charge(ctx, 3);
                        v1 = 283;
                        if (v0 == v1) {
                            goto L_002fca24;
                        }
                        // 0x002fc794
                        charge(ctx, 3);
                        v1 = 282;
                        if (v0 == v1) {
                            goto L_002fca24;
                        }
                        // 0x002fc7a0
                        charge(ctx, 3);
                        v1 = 273;
                        if (v0 == v1) {
                            goto L_002fca24;
                        }
                        // 0x002fc7ac
                        charge(ctx, 3);
                        v1 = 272;
                        if (v0 == v1) {
                            goto L_002fca8c;
                        }
                        // 0x002fc7b8
                        charge(ctx, 3);
                        v1 = 271;
                        if (v0 == v1) {
                            goto L_002fca8c;
                        }
                        // 0x002fc7c4
                        charge(ctx, 3);
                        v1 = 269;
                        if (v0 == v1) {
                            // 0x002fc9fc
                            charge(ctx, 10);
                            lwc1(f3, a1, 144);
                            lwc1(f2, a1, 44);
                            v0 = 0x42C80000;
                            mtc1(v0, f1);
                            mtc1(zero, f0);
                            adda_s(f0, f1);
                            madd_s(f0, f3, f2);
                        } else {
                            // 0x002fc7d0
                            charge(ctx, 3);
                            v1 = 268;
                            if (v0 == v1) {
                                goto L_002fca8c;
                            }
                            // 0x002fc7dc
                            charge(ctx, 3);
                            v1 = 267;
                            if (v0 == v1) {
                                goto L_002fca8c;
                            }
                            // 0x002fc7e8
                            charge(ctx, 3);
                            v1 = 266;
                            if (v0 == v1) {
                                // 0x002fc9d4
                                charge(ctx, 10);
                                lwc1(f3, a1, 144);
                                lwc1(f2, a1, 44);
                                v0 = 0x43480000;
                                mtc1(v0, f1);
                                mtc1(zero, f0);
                                adda_s(f0, f1);
                                madd_s(f0, f3, f2);
                            } else {
                                // 0x002fc7f4
                                charge(ctx, 3);
                                v1 = 265;
                                if (v0 == v1) {
                                    // 0x002fc9c0
                                    charge(ctx, 5);
                                    lwc1(f1, a1, 144);
                                    lwc1(f0, a1, 44);
                                    mul_s(f0, f1, f0);
                                } else {
                                    // 0x002fc800
                                    charge(ctx, 3);
                                    v1 = 264;
                                    if (v0 == v1) {
                                        goto L_002fca8c;
                                    }
                                    // 0x002fc80c
                                    charge(ctx, 3);
                                    v1 = 263;
                                    if (v0 == v1) {
                                        // 0x002fc998
                                        charge(ctx, 10);
                                        lwc1(f3, a1, 144);
                                        lwc1(f2, a1, 44);
                                        v0 = 0x42FA0000;
                                        mtc1(v0, f1);
                                        mtc1(zero, f0);
                                        adda_s(f0, f1);
                                        madd_s(f0, f3, f2);
                                    } else {
                                        // 0x002fc818
                                        charge(ctx, 3);
                                        v1 = 277;
                                        if (v0 == v1) {
                                            // 0x002fc970
                                            charge(ctx, 10);
                                            lwc1(f3, a1, 144);
                                            lwc1(f2, a1, 44);
                                            v0 = 0x42480000;
                                            mtc1(v0, f1);
                                            mtc1(zero, f0);
                                            adda_s(f0, f1);
                                            madd_s(f0, f3, f2);
                                        } else {
                                            // 0x002fc824
                                            charge(ctx, 3);
                                            v1 = 262;
                                            if (v0 == v1) {
                                                // 0x002fc948
                                                charge(ctx, 10);
                                                lwc1(f3, a1, 144);
                                                lwc1(f2, a1, 44);
                                                v0 = 0x432F0000;
                                                mtc1(v0, f1);
                                                mtc1(zero, f0);
                                                adda_s(f0, f1);
                                                madd_s(f0, f3, f2);
                                            } else {
                                                // 0x002fc830
                                                charge(ctx, 3);
                                                v1 = 261;
                                                if (v0 == v1) {
                                                    // 0x002fc920
                                                    charge(ctx, 10);
                                                    lwc1(f3, a1, 144);
                                                    lwc1(f2, a1, 44);
                                                    v0 = 0x43160000;
                                                    mtc1(v0, f1);
                                                    mtc1(zero, f0);
                                                    adda_s(f0, f1);
                                                    madd_s(f0, f3, f2);
                                                } else {
                                                    // 0x002fc83c
                                                    charge(ctx, 3);
                                                    v1 = 260;
                                                    if (v0 == v1) {
                                                        // 0x002fc8f8
                                                        charge(ctx, 10);
                                                        lwc1(f3, a1, 144);
                                                        lwc1(f2, a1, 44);
                                                        v0 = 0x43160000;
                                                        mtc1(v0, f1);
                                                        mtc1(zero, f0);
                                                        adda_s(f0, f1);
                                                        madd_s(f0, f3, f2);
                                                    } else {
                                                        // 0x002fc848
                                                        charge(ctx, 3);
                                                        v1 = 259;
                                                        if (v0 == v1) {
                                                            // 0x002fc8d0
                                                            charge(ctx, 10);
                                                            lwc1(f3, a1, 144);
                                                            lwc1(f2, a1, 44);
                                                            v0 = 0x42C80000;
                                                            mtc1(v0, f1);
                                                            mtc1(zero, f0);
                                                            adda_s(f0, f1);
                                                            madd_s(f0, f3, f2);
                                                        } else {
                                                            // 0x002fc854
                                                            charge(ctx, 3);
                                                            v1 = 258;
                                                            if (v0 != v1) {
                                                                // 0x002fc860
                                                                charge(ctx, 3);
                                                                v1 = 257;
                                                                if (v0 == v1) {
                                                                    goto L_002fc8a8;
                                                                }
                                                                // 0x002fc86c
                                                                charge(ctx, 3);
                                                                v1 = 256;
                                                                if (v0 != v1) {
                                                                    // 0x002fc878
                                                                    charge(ctx, 2);
                                                                    goto L_002fca8c;
                                                                }
                                                                // 0x002fc880
                                                                charge(ctx, 10);
                                                                lwc1(f3, a1, 144);
                                                                lwc1(f2, a1, 44);
                                                                v0 = 0x43160000;
                                                                mtc1(v0, f1);
                                                                mtc1(zero, f0);
                                                                adda_s(f0, f1);
                                                                madd_s(f0, f3, f2);
                                                                // 0x002fca94 (the shared epilogue, written out on this path)
                                                                charge(ctx, 2);
                                                                return;
                                                            }
                                                        L_002fc8a8:
                                                            charge(ctx, 10);
                                                            lwc1(f3, a1, 144);
                                                            lwc1(f2, a1, 44);
                                                            v0 = 0x42C80000;
                                                            mtc1(v0, f1);
                                                            mtc1(zero, f0);
                                                            adda_s(f0, f1);
                                                            madd_s(f0, f3, f2);
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        // 0x002fca94 (the shared epilogue, written out on this path)
                        charge(ctx, 2);
                        return;
                    }
                L_002fca24:
                    charge(ctx, 12);
                    lwc1(f3, a1, 144);
                    lwc1(f2, a1, 44);
                    v0 = 375;
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    mtc1(zero, f0);
                    adda_s(f0, f1);
                    madd_s(f0, f3, f2);
                    // 0x002fca94 (the shared epilogue, written out on this path)
                    charge(ctx, 2);
                    return;
                }
            L_002fca8c:
                charge(ctx, 2);
                v0 = lui(0xBF80);
                mtc1(v0, f0);
            }
        } else {
            // 0x002fc608
            charge(ctx, 4);
            v0 = lui(0xBF80);
            mtc1(v0, f0);
        }
    } else {
        // 0x002fc5e8
        charge(ctx, 4);
        v0 = lui(0xBF80);
        mtc1(v0, f0);
    }
    // 0x002fca94 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x002FD2E0 sub_2FD2E0 -- 448 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlBossRunEvent] Starts a boss AI event script (kind a1: 0 battle start, 1 action start, 2 action end) once per
// action / turn pair: a script task from the boss header with the hero's action as user data, its message window, as
// a child of the battle task; remembers it in gBtl +2856.
// Arguments: a0 btlAction, a1 kind.
void sub_2FD2E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002fd480: the shared epilogue (v0 = 1 when a script started)
    auto epilogue = [&] {
        charge(ctx, 8);
        ld(ra, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
    };
    // 0x002fd2e0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;                    // s2 = the action
    s1 = a1;                    // s1 = the event kind (0 battle start, 1 action start, 2 action end)
    v0 = s1 & 0xFFFF;
    v0 = sll(v0, 2);
    lw(a3, gp, kGpBtl);  // gBtl 0x7CE3EC
    a1 = addu(v0, a3);
    // Once per action and turn: the kind's last (serial, turns) pair.
    lw(v1, a1, gbtl4::kBossEvtOwner);
    lw(v0, a0, act::kSerial);
    if (v1 == v0) {
        // 0x002fd320
        charge(ctx, 4);
        lw(v1, a1, gbtl4::kBossEvtTurn);
        lw(v0, s2, act::kTurnsTaken);
        if (v1 == v0) {
            // 0x002fd330: already ran
            charge(ctx, 3);
            v0 = 0;
            epilogue();
            return;
        }
    }
    // 0x002fd33c: the kind's procedure (-1: the boss script has none)
    charge(ctx, 4);
    v1 = s1 & 0xFFFF;
    v0 = 2;
    bool run = false;
    if (v1 == v0) {
        // 0x002fd3b0
        charge(ctx, 4);
        lw(a2, a3, gbtl4::kBossEvtActEnd);
        v0 = si(-1);
        if (a2 != v0) {
            run = true;
        } else {
            // 0x002fd3c0
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x002fd34c
        charge(ctx, 3);
        v0 = 1;
        if (v1 == v0) {
            // 0x002fd38c
            charge(ctx, 4);
            lw(a2, a3, gbtl4::kBossEvtActStart);
            v0 = si(-1);
            if (a2 != v0) {
                // 0x002fd3a8
                charge(ctx, 2);
                run = true;
            } else {
                // 0x002fd39c
                charge(ctx, 3);
                v0 = 0;
            }
        } else {
            // 0x002fd358
            charge(ctx, 2);
            if (v1 != 0) {
                // 0x002fd360: another kind runs with whatever a2 holds
                charge(ctx, 2);
                run = true;
            } else {
                // 0x002fd368
                charge(ctx, 4);
                lw(a2, a3, gbtl4::kBossEvtStart);
                v0 = si(-1);
                if (a2 != v0) {
                    // 0x002fd384
                    charge(ctx, 2);
                    run = true;
                } else {
                    // 0x002fd378
                    charge(ctx, 3);
                    v0 = 0;
                }
            }
        }
    }
    if (run) {
        // A script task from the boss script header at procedure a2, one priority below the battle task, with the
        // hero's action as its user data and a message window (sub_3A4220 with sub_1778B0(1)) when it has one (+204);
        // a child of the battle task, remembered in kBossTask; the kind's (serial, turns) pair updated.
        // 0x002fd3cc
        charge(ctx, 19);
        lw(v0, a3, gbtl4::kTask);
        lw(v0, v0, 32);
        a0 = addiu(v0, -1);
        lw(a1, gp, kGpBossScript);  // the boss AI script 0x7CE4D0
        jal(ctx, 0x2FD3DCu, gen::fn_scrCreateTaskFromHeader_0035bb40);
        s0 = v0;                // s0 = the script task
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        a0 = s0;
        lw(a1, v0, gbtl::kPlayerAction);
        jal(ctx, 0x2FD3F4u, gen::fn_scrSetUserData_0035c1a0);
        a0 = s0;
        jal(ctx, 0x2FD400u, gen::fn_dds3GetProcessWorkData_0035ae10);
        s3 = v0;
        lw(v0, v0, 204);
        if (i64(v0) >= 0) {
            // 0x002fd418
            charge(ctx, 8);
            a0 = 1;
            jal(ctx, 0x2FD41Cu, gen::fn_sub_1778B0_001778b0);
            lw(a0, s3, 204);
            a1 = 0;
            a2 = v0;
            jal(ctx, 0x2FD430u, gen::fn_sub_3A4220_003a4220);
        }
        // 0x002fd438
        charge(ctx, 18);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(a0, v0, gbtl4::kTask);
        a1 = s0;
        jal(ctx, 0x2FD444u, gen::fn_kwlnTaskAddChild_00195550);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        sw(s0, v0, gbtl::kBossTask);
        v0 = s1 & 0xFFFF;
        a0 = sll(v0, 2);
        lw(v1, s2, act::kSerial);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        v0 = addu(a0, v0);
        sw(v1, v0, gbtl4::kBossEvtOwner);
        lw(v1, s2, act::kTurnsTaken);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        v0 = addu(a0, v0);
        sw(v1, v0, gbtl4::kBossEvtTurn);
        v0 = 1;
    }
    epilogue();
}

// 0x002FD8A0 sub_2FD8A0 -- 716 bytes; frame 0x10: ra sp+0x0
// Boss rule for encounters 0x1A7..0x1B3: lets the listed boss enemies fidget (sub_289860).
// Arguments: a0 btlAction.
void sub_2FD8A0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002fd8a0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v1, v1, gbtl::kSetupEnemies);
    lhu(v1, v1, 8);
    v1 = addiu(v1, -423);
    at = sltiu(v1, 13);
    if (at != 0) {
        // 0x002fd8c4
        charge(ctx, 7);
        a1 = 0x7C0000;
        a1 = addiu(a1, -29136);  // &0x7B8E30
        v1 = sll(v1, 2);
        v1 = addu(v1, a1);
        lw(v1, v1, 0);
        switch (v1.u()) {
        case 0x2FD8E0u:  // table[0]
            // 0x002fd8e0
            charge(ctx, 4);
            lhu(v1, a0, act::kFlags2);
            v1 = v1 & 0x1;
            if (v1 != 0) {
                // 0x002fd8f0
                charge(ctx, 5);
                lw(a2, a0, act::kUnit);
                lbu(a1, a2, unit::kSide);
                v1 = 1;
                if (a1 == v1) {
                    // 0x002fd904
                    charge(ctx, 4);
                    lhu(a1, a2, unit::kId);
                    v1 = 268;
                    if (a1 != v1) {
                        // 0x002fd914
                        charge(ctx, 3);
                        v1 = 267;
                        if (a1 == v1) {
                            goto L_002fd928;
                        }
                        // 0x002fd920
                        charge(ctx, 2);
                        break;
                    }
                L_002fd928:
                    charge(ctx, 4);
                    jal(ctx, 0x2FD928u, gen::fn_sub_289860_00289860);
                }
            }
            break;
        case 0x2FD938u:  // table[2]
            // 0x002fd938
            charge(ctx, 4);
            lhu(v1, a0, act::kFlags2);
            v1 = v1 & 0x1;
            if (v1 != 0) {
                // 0x002fd948
                charge(ctx, 5);
                lw(a2, a0, act::kUnit);
                lbu(a1, a2, unit::kSide);
                v1 = 1;
                if (a1 == v1) {
                    // 0x002fd95c
                    charge(ctx, 4);
                    lhu(a1, a2, unit::kId);
                    v1 = 264;
                    if (a1 == v1) {
                        // 0x002fd974
                        charge(ctx, 4);
                        jal(ctx, 0x2FD974u, gen::fn_sub_289860_00289860);
                    } else {
                        // 0x002fd96c
                        charge(ctx, 2);
                    }
                }
            }
            break;
        case 0x2FD984u:  // table[3]
            // 0x002fd984
            charge(ctx, 4);
            lhu(v1, a0, act::kFlags2);
            v1 = v1 & 0x1;
            if (v1 != 0) {
                // 0x002fd994
                charge(ctx, 5);
                lw(a2, a0, act::kUnit);
                lbu(a1, a2, unit::kSide);
                v1 = 1;
                if (a1 == v1) {
                    // 0x002fd9a8
                    charge(ctx, 4);
                    lhu(a1, a2, unit::kId);
                    v1 = 271;
                    if (a1 == v1) {
                        // 0x002fd9c0
                        charge(ctx, 4);
                        jal(ctx, 0x2FD9C0u, gen::fn_sub_289860_00289860);
                    } else {
                        // 0x002fd9b8
                        charge(ctx, 2);
                    }
                }
            }
            break;
        case 0x2FD9D0u:  // table[4]
            // 0x002fd9d0
            charge(ctx, 4);
            lhu(v1, a0, act::kFlags2);
            v1 = v1 & 0x1;
            if (v1 != 0) {
                // 0x002fd9e0
                charge(ctx, 5);
                lw(a2, a0, act::kUnit);
                lbu(a1, a2, unit::kSide);
                v1 = 1;
                if (a1 == v1) {
                    // 0x002fd9f4
                    charge(ctx, 4);
                    lhu(a1, a2, unit::kId);
                    v1 = 272;
                    if (a1 == v1) {
                        // 0x002fda0c
                        charge(ctx, 4);
                        jal(ctx, 0x2FDA0Cu, gen::fn_sub_289860_00289860);
                    } else {
                        // 0x002fda04
                        charge(ctx, 2);
                    }
                }
            }
            break;
        case 0x2FDA1Cu:  // table[7]
            // 0x002fda1c
            charge(ctx, 4);
            lhu(v1, a0, act::kFlags2);
            v1 = v1 & 0x1;
            if (v1 != 0) {
                // 0x002fda2c
                charge(ctx, 5);
                lw(a2, a0, act::kUnit);
                lbu(a1, a2, unit::kSide);
                v1 = 1;
                if (a1 == v1) {
                    // 0x002fda40
                    charge(ctx, 4);
                    lhu(a1, a2, unit::kId);
                    v1 = 294;
                    if (a1 == v1) {
                        // 0x002fda58
                        charge(ctx, 4);
                        jal(ctx, 0x2FDA58u, gen::fn_sub_289860_00289860);
                    } else {
                        // 0x002fda50
                        charge(ctx, 2);
                    }
                }
            }
            break;
        case 0x2FDA68u:  // table[8]
            // 0x002fda68
            charge(ctx, 4);
            lhu(v1, a0, act::kFlags2);
            v1 = v1 & 0x1;
            if (v1 != 0) {
                // 0x002fda78
                charge(ctx, 5);
                lw(a2, a0, act::kUnit);
                lbu(a1, a2, unit::kSide);
                v1 = 1;
                if (a1 == v1) {
                    // 0x002fda8c
                    charge(ctx, 4);
                    lhu(a1, a2, unit::kId);
                    v1 = 233;
                    if (a1 == v1) {
                        // 0x002fdaa4
                        charge(ctx, 4);
                        jal(ctx, 0x2FDAA4u, gen::fn_sub_289860_00289860);
                    } else {
                        // 0x002fda9c
                        charge(ctx, 2);
                    }
                }
            }
            break;
        case 0x2FDAB4u:  // table[9]
            // 0x002fdab4
            charge(ctx, 4);
            lhu(v1, a0, act::kFlags2);
            v1 = v1 & 0x1;
            if (v1 != 0) {
                // 0x002fdac4
                charge(ctx, 5);
                lw(a2, a0, act::kUnit);
                lbu(a1, a2, unit::kSide);
                v1 = 1;
                if (a1 == v1) {
                    // 0x002fdad8
                    charge(ctx, 4);
                    lhu(a1, a2, unit::kId);
                    v1 = 234;
                    if (a1 == v1) {
                        // 0x002fdaf0
                        charge(ctx, 4);
                        jal(ctx, 0x2FDAF0u, gen::fn_sub_289860_00289860);
                    } else {
                        // 0x002fdae8
                        charge(ctx, 2);
                    }
                }
            }
            break;
        case 0x2FDB00u:  // table[10, 11, 12]
            // 0x002fdb00
            charge(ctx, 4);
            lhu(v1, a0, act::kFlags2);
            v1 = v1 & 0x1;
            if (v1 != 0) {
                // 0x002fdb10
                charge(ctx, 5);
                lw(a2, a0, act::kUnit);
                lbu(a1, a2, unit::kSide);
                v1 = 1;
                if (a1 == v1) {
                    // 0x002fdb24
                    charge(ctx, 5);
                    lhu(v1, a2, unit::kId);
                    v1 = addiu(v1, -235);
                    at = sltiu(v1, 6);
                    if (at != 0) {
                        // 0x002fdb38
                        charge(ctx, 7);
                        a1 = 0x7C0000;
                        a1 = addiu(a1, -29168);  // &0x7B8E10
                        v1 = sll(v1, 2);
                        v1 = addu(v1, a1);
                        lw(v1, v1, 0);
                        switch (v1.u()) {
                        case 0x2FDB54u:  // table[0, 1, 2, 3, 4, 5]
                            break;
                        default:  // not one of the table's targets: the dispatch table, as the recompiled body
                            tail(ctx, v1.u());
                            return;
                        }
                        // 0x002fdb54
                        charge(ctx, 2);
                        jal(ctx, 0x2FDB54u, gen::fn_sub_289860_00289860);
                    }
                }
            }
            break;
        case 0x2FDB5Cu:  // table[1, 5, 6]
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
    }
    // 0x002fdb5c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002FE0B0 sub_2FE0B0 -- 1732 bytes; frame 0x1A0: ra sp+0x90, s6 sp+0x80 (sq), s5 sp+0x70 (sq), s4 sp+0x60 (sq), s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f26 sp+0x18, f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// Draws a boss gauge ring segment (Im2D through the RW slots).
void sub_2FE0B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25}, f26{ctx, 26};
    // 0x002fe0b0
    enter(ctx, 45);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1A0);
    sd(ra, sp, 0x90);
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
    mov_s(f26, f12);
    s4 = a0;
    s3 = a1;
    s2 = a2;
    s1 = a3;
    jal(ctx, 0x2FE104u, gen::fn_sub_198590_00198590);
    s6 = v0;
    jal(ctx, 0x2FE110u, gen::fn_sub_4E3630_004e3630);
    s0 = v0;
    lwc1(f0, v0, 12);
    cvt_s_w(f0, f0);
    v1 = 0x44200000;
    mtc1(v1, f21);
    div_s(f25, f21, f0);
    lwc1(f0, v0, 16);
    cvt_s_w(f0, f0);
    v0 = 0x43E00000;
    mtc1(v0, f20);
    div_s(f24, f20, f0);
    mtc1(zero, f5);
    c_eq_s(f5, f26);
    if (!cond(ctx)) {
        // 0x002fe174
        charge(ctx, 18);
        v0 = 0x43A00000;
        mtc1(v0, f4);
        neg_s(f0, f4);
        lwc1(f3, gp, -32148);  // 0x7CAF5C
        adda_s(f5, f3);
        madd_s(f23, f0, f26);
        v0 = 0x43600000;
        mtc1(v0, f2);
        neg_s(f1, f2);
        lwc1(f0, gp, -32144);  // 0x7CAF60
        adda_s(f5, f0);
        madd_s(f22, f1, f26);
        adda_s(f5, f3);
        madd_s(f21, f4, f26);
        adda_s(f5, f0);
        madd_s(f20, f2, f26);
    } else {
        // 0x002fe164
        charge(ctx, 4);
        mov_s(f23, f5);
        mov_s(f22, f5);
    }
    // 0x002fe1bc
    charge(ctx, 62);
    s5 = 0x960000;
    s5 = addiu(s5, 144);  // &pfn_RwRenderStateSet
    a0 = 7;
    a1 = 2;
    lw(v0, s5, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x2FE1D0u, v0.u());
    a0 = 20;
    a1 = 1;
    lw(v0, s5, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x2FE1E4u, v0.u());
    a0 = 14;
    a1 = 0;
    lw(v0, s5, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x2FE1F8u, v0.u());
    a0 = 6;
    a1 = 0;
    lw(v0, s5, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x2FE20Cu, v0.u());
    a0 = 8;
    a1 = 0;
    lw(v0, s5, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x2FE220u, v0.u());
    a0 = 9;
    a1 = s1;
    lw(v0, s5, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x2FE234u, v0.u());
    a0 = 12;
    a1 = 1;
    lw(v0, s5, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x2FE248u, v0.u());
    a0 = 1;
    a1 = s0;
    lw(v0, s5, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x2FE25Cu, v0.u());
    a0 = 2;
    a1 = s3;
    jal(ctx, 0x2FE26Cu, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 3;
    a1 = s2;
    jal(ctx, 0x2FE27Cu, gen::fn_RpSkyRenderStateSet_004d7f60);
    v0 = 0x960000;
    lwc1(f1, v0, 140);  // 0x96008C
    v0 = 0x3F800000;
    mtc1(v0, f2);
    lwc1(f0, s6, 132);
    div_s(f0, f2, f0);
    swc1(f23, sp, 0xA0);
    swc1(f22, sp, 0xA4);
    swc1(f1, sp, 0xA8);
    lbu(v0, s4, 0);
    if (i64(v0) < 0) {
        // 0x002fe2c8
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f2);
        cvt_s_w(f2, f2);
        add_s(f2, f2, f2);
    } else {
        // 0x002fe2b4
        charge(ctx, 5);
        mtc1(v0, f2);
        cvt_s_w(f2, f2);
    }
    // 0x002fe2e4
    charge(ctx, 4);
    swc1(f2, sp, 0xC0);
    lbu(v0, s4, 1);
    if (i64(v0) < 0) {
        // 0x002fe308
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f2);
        cvt_s_w(f2, f2);
        add_s(f2, f2, f2);
    } else {
        // 0x002fe2f4
        charge(ctx, 5);
        mtc1(v0, f2);
        cvt_s_w(f2, f2);
    }
    // 0x002fe324
    charge(ctx, 4);
    swc1(f2, sp, 0xC4);
    lbu(v0, s4, 2);
    if (i64(v0) < 0) {
        // 0x002fe348
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f2);
        cvt_s_w(f2, f2);
        add_s(f2, f2, f2);
    } else {
        // 0x002fe334
        charge(ctx, 5);
        mtc1(v0, f2);
        cvt_s_w(f2, f2);
    }
    // 0x002fe364
    charge(ctx, 4);
    swc1(f2, sp, 0xC8);
    lbu(v0, s4, 3);
    if (i64(v0) < 0) {
        // 0x002fe388
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f2);
        cvt_s_w(f2, f2);
        add_s(f2, f2, f2);
    } else {
        // 0x002fe374
        charge(ctx, 5);
        mtc1(v0, f2);
        cvt_s_w(f2, f2);
    }
    // 0x002fe3a4
    charge(ctx, 10);
    swc1(f2, sp, 0xCC);
    swc1(f0, sp, 0xB8);
    sw(zero, sp, 0xB0);
    sw(zero, sp, 0xB4);
    swc1(f23, sp, 0xE0);
    swc1(f20, sp, 0xE4);
    swc1(f1, sp, 0xE8);
    lbu(v0, s4, 0);
    if (i64(v0) < 0) {
        // 0x002fe3e0
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f2);
        cvt_s_w(f2, f2);
        add_s(f2, f2, f2);
    } else {
        // 0x002fe3cc
        charge(ctx, 5);
        mtc1(v0, f2);
        cvt_s_w(f2, f2);
    }
    // 0x002fe3fc
    charge(ctx, 4);
    swc1(f2, sp, 0x100);
    lbu(v0, s4, 1);
    if (i64(v0) < 0) {
        // 0x002fe420
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f2);
        cvt_s_w(f2, f2);
        add_s(f2, f2, f2);
    } else {
        // 0x002fe40c
        charge(ctx, 5);
        mtc1(v0, f2);
        cvt_s_w(f2, f2);
    }
    // 0x002fe43c
    charge(ctx, 4);
    swc1(f2, sp, 0x104);
    lbu(v0, s4, 2);
    if (i64(v0) < 0) {
        // 0x002fe460
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f2);
        cvt_s_w(f2, f2);
        add_s(f2, f2, f2);
    } else {
        // 0x002fe44c
        charge(ctx, 5);
        mtc1(v0, f2);
        cvt_s_w(f2, f2);
    }
    // 0x002fe47c
    charge(ctx, 4);
    swc1(f2, sp, 0x108);
    lbu(v0, s4, 3);
    if (i64(v0) < 0) {
        // 0x002fe4a0
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f2);
        cvt_s_w(f2, f2);
        add_s(f2, f2, f2);
    } else {
        // 0x002fe48c
        charge(ctx, 5);
        mtc1(v0, f2);
        cvt_s_w(f2, f2);
    }
    // 0x002fe4bc
    charge(ctx, 10);
    swc1(f2, sp, 0x10C);
    swc1(f0, sp, 0xF8);
    sw(zero, sp, 0xF0);
    swc1(f24, sp, 0xF4);
    swc1(f21, sp, 0x120);
    swc1(f22, sp, 0x124);
    swc1(f1, sp, 0x128);
    lbu(v0, s4, 0);
    if (i64(v0) < 0) {
        // 0x002fe4f8
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f2);
        cvt_s_w(f2, f2);
        add_s(f2, f2, f2);
    } else {
        // 0x002fe4e4
        charge(ctx, 5);
        mtc1(v0, f2);
        cvt_s_w(f2, f2);
    }
    // 0x002fe514
    charge(ctx, 4);
    swc1(f2, sp, 0x140);
    lbu(v0, s4, 1);
    if (i64(v0) < 0) {
        // 0x002fe538
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f2);
        cvt_s_w(f2, f2);
        add_s(f2, f2, f2);
    } else {
        // 0x002fe524
        charge(ctx, 5);
        mtc1(v0, f2);
        cvt_s_w(f2, f2);
    }
    // 0x002fe554
    charge(ctx, 4);
    swc1(f2, sp, 0x144);
    lbu(v0, s4, 2);
    if (i64(v0) < 0) {
        // 0x002fe578
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f2);
        cvt_s_w(f2, f2);
        add_s(f2, f2, f2);
    } else {
        // 0x002fe564
        charge(ctx, 5);
        mtc1(v0, f2);
        cvt_s_w(f2, f2);
    }
    // 0x002fe594
    charge(ctx, 4);
    swc1(f2, sp, 0x148);
    lbu(v0, s4, 3);
    if (i64(v0) < 0) {
        // 0x002fe5b8
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f2);
        cvt_s_w(f2, f2);
        add_s(f2, f2, f2);
    } else {
        // 0x002fe5a4
        charge(ctx, 5);
        mtc1(v0, f2);
        cvt_s_w(f2, f2);
    }
    // 0x002fe5d4
    charge(ctx, 10);
    swc1(f2, sp, 0x14C);
    swc1(f0, sp, 0x138);
    swc1(f25, sp, 0x130);
    sw(zero, sp, 0x134);
    swc1(f21, sp, 0x160);
    swc1(f20, sp, 0x164);
    swc1(f1, sp, 0x168);
    lbu(v0, s4, 0);
    if (i64(v0) < 0) {
        // 0x002fe610
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f1);
        cvt_s_w(f1, f1);
        add_s(f1, f1, f1);
    } else {
        // 0x002fe5fc
        charge(ctx, 5);
        mtc1(v0, f1);
        cvt_s_w(f1, f1);
    }
    // 0x002fe62c
    charge(ctx, 4);
    swc1(f1, sp, 0x180);
    lbu(v0, s4, 1);
    if (i64(v0) < 0) {
        // 0x002fe650
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f1);
        cvt_s_w(f1, f1);
        add_s(f1, f1, f1);
    } else {
        // 0x002fe63c
        charge(ctx, 5);
        mtc1(v0, f1);
        cvt_s_w(f1, f1);
    }
    // 0x002fe66c
    charge(ctx, 4);
    swc1(f1, sp, 0x184);
    lbu(v0, s4, 2);
    if (i64(v0) < 0) {
        // 0x002fe690
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f1);
        cvt_s_w(f1, f1);
        add_s(f1, f1, f1);
    } else {
        // 0x002fe67c
        charge(ctx, 5);
        mtc1(v0, f1);
        cvt_s_w(f1, f1);
    }
    // 0x002fe6ac
    charge(ctx, 4);
    swc1(f1, sp, 0x188);
    lbu(v0, s4, 3);
    if (i64(v0) < 0) {
        // 0x002fe6d0
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f1);
        cvt_s_w(f1, f1);
        add_s(f1, f1, f1);
    } else {
        // 0x002fe6bc
        charge(ctx, 5);
        mtc1(v0, f1);
        cvt_s_w(f1, f1);
    }
    // 0x002fe6ec
    charge(ctx, 34);
    swc1(f1, sp, 0x18C);
    swc1(f0, sp, 0x178);
    swc1(f25, sp, 0x170);
    swc1(f24, sp, 0x174);
    a0 = 4;
    a1 = addiu(sp, 0xA0);
    a2 = a0;
    v0 = 0x960000;
    lw(v0, v0, 160);  // pfn_RwIm2DRenderPrimitive
    jalr(ctx, 0x2FE710u, v0.u());
    a0 = 1;
    a1 = 0;
    lw(v0, s5, 0);
    jalr(ctx, 0x2FE724u, v0.u());
    ld(ra, sp, 0x90);
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
    sp = addiu(sp, 0x1A0);
}

// 0x002FE780 sub_2FE780 -- 1416 bytes; frame 0xB10: ra sp+0x80, s5 sp+0x70 (sq), s4 sp+0x60 (sq), s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0, f21 sp+0x98, f20 sp+0xA8
// Draws a boss gauge arc (Im2D, sinf / cosf).
void sub_2FE780(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24};
    // 0x002fe780
    enter(ctx, 87);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB10);
    sd(ra, sp, 0x80);
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
    mov_s(f22, f12);
    s4 = a0;
    s3 = a1;
    s2 = a2;
    s1 = a3;
    jal(ctx, 0x2FE7C8u, gen::fn_sub_198590_00198590);
    s5 = v0;
    s0 = 0x960000;
    s0 = addiu(s0, 144);  // &pfn_RwRenderStateSet
    a0 = 7;
    a1 = 2;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x2FE7E8u, v0.u());
    a0 = 20;
    a1 = 1;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x2FE7FCu, v0.u());
    a0 = 14;
    a1 = 0;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x2FE810u, v0.u());
    a0 = 6;
    a1 = 0;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x2FE824u, v0.u());
    a0 = 8;
    a1 = 0;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x2FE838u, v0.u());
    a0 = 12;
    a1 = 1;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x2FE84Cu, v0.u());
    a0 = 1;
    a1 = 0;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x2FE860u, v0.u());
    a0 = 2;
    a1 = s2;
    jal(ctx, 0x2FE870u, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 3;
    a1 = s1;
    jal(ctx, 0x2FE880u, gen::fn_RpSkyRenderStateSet_004d7f60);
    v0 = 0x960000;
    lwc1(f21, v0, 140);  // 0x96008C
    v0 = 0x3F800000;
    mtc1(v0, f1);
    lwc1(f0, s5, 132);
    div_s(f20, f1, f0);
    v0 = 0x48150000;
    mtc1(v0, f0);
    sqrt_s(f0, f0);
    mul_s(f22, f22, f0);
    mtc1(zero, f23);
    v0 = 0x43A00000;
    sw(v0, sp, 0x90);
    v0 = 0x43600000;
    sw(v0, sp, 0x94);
    swc1(f21, sp, 0x98);
    swc1(f20, sp, 0xA8);
    lbu(v0, s4, 0);
    if (i64(v0) < 0) {
        // 0x002fe8f0
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x002fe8dc
        charge(ctx, 5);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x002fe90c
    charge(ctx, 4);
    swc1(f0, sp, 0xB0);
    lbu(v0, s4, 1);
    if (i64(v0) < 0) {
        // 0x002fe930
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x002fe91c
        charge(ctx, 5);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x002fe94c
    charge(ctx, 4);
    swc1(f0, sp, 0xB4);
    lbu(v0, s4, 2);
    if (i64(v0) < 0) {
        // 0x002fe970
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x002fe95c
        charge(ctx, 5);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x002fe98c
    charge(ctx, 4);
    swc1(f0, sp, 0xB8);
    lbu(v0, s4, 3);
    if (i64(v0) < 0) {
        // 0x002fe9b0
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x002fe99c
        charge(ctx, 5);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x002fe9cc
    charge(ctx, 5);
    swc1(f0, sp, 0xBC);
    s0 = 1;
    s1 = 0;
    for (;;) {
        // 0x002feb60
        charge(ctx, 4);
        v0 = s1 & 0xFFFF;
        v0 = slti(v0, 40);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002fe9e0
        charge(ctx, 29);
        mov_s(f12, f23);
        jal(ctx, 0x2FE9E4u, gen::fn_cosf_0052e6d8);
        v0 = 0x43A00000;
        mtc1(v0, f2);
        mtc1(zero, f1);
        adda_s(f1, f2);
        madd_s(f24, f22, f0);
        mov_s(f12, f23);
        jal(ctx, 0x2FEA08u, gen::fn_sinf_0052e878);
        v0 = 0x43600000;
        mtc1(v0, f2);
        mtc1(zero, f1);
        adda_s(f1, f2);
        madd_s(f0, f22, f0);
        v0 = s0 & 0xFFFF;
        v0 = sll(v0, 6);
        v0 = addu(v0, sp);
        a0 = addiu(v0, 144);
        swc1(f24, a0, 0);
        swc1(f0, a0, 4);
        swc1(f21, a0, 8);
        swc1(f20, a0, 24);
        lbu(v0, s3, 0);
        if (i64(v0) < 0) {
            // 0x002fea68
            charge(ctx, 7);
            v1 = srl(v0, 1);
            v0 = v0 & 0x1;
            v1 = v1 | v0;
            mtc1(v1, f0);
            cvt_s_w(f0, f0);
            add_s(f0, f0, f0);
        } else {
            // 0x002fea54
            charge(ctx, 5);
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
        }
        // 0x002fea84
        charge(ctx, 4);
        swc1(f0, a0, 32);
        lbu(v0, s3, 1);
        if (i64(v0) < 0) {
            // 0x002feaa8
            charge(ctx, 7);
            v1 = srl(v0, 1);
            v0 = v0 & 0x1;
            v1 = v1 | v0;
            mtc1(v1, f0);
            cvt_s_w(f0, f0);
            add_s(f0, f0, f0);
        } else {
            // 0x002fea94
            charge(ctx, 5);
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
        }
        // 0x002feac4
        charge(ctx, 4);
        swc1(f0, a0, 36);
        lbu(v0, s3, 2);
        if (i64(v0) < 0) {
            // 0x002feae8
            charge(ctx, 7);
            v1 = srl(v0, 1);
            v0 = v0 & 0x1;
            v1 = v1 | v0;
            mtc1(v1, f0);
            cvt_s_w(f0, f0);
            add_s(f0, f0, f0);
        } else {
            // 0x002fead4
            charge(ctx, 5);
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
        }
        // 0x002feb04
        charge(ctx, 4);
        swc1(f0, a0, 40);
        lbu(v0, s3, 3);
        if (i64(v0) < 0) {
            // 0x002feb28
            charge(ctx, 7);
            v1 = srl(v0, 1);
            v0 = v0 & 0x1;
            v1 = v1 | v0;
            mtc1(v1, f0);
            cvt_s_w(f0, f0);
            add_s(f0, f0, f0);
        } else {
            // 0x002feb14
            charge(ctx, 5);
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
        }
        // 0x002feb44
        charge(ctx, 7);
        swc1(f0, a0, 44);
        v0 = addiu(s0, 1);
        s0 = v0 & 0xFFFF;
        lwc1(f0, gp, -32152);  // 0x7CAF58
        add_s(f23, f23, f0);
        v0 = addiu(s1, 1);
        s1 = v0 & 0xFFFF;
    }
    // 0x002feb70
    charge(ctx, 15);
    v0 = s0 & 0xFFFF;
    a0 = sll(v0, 6);
    lwc1(f0, sp, 0xD0);
    v1 = addu(a0, sp);
    swc1(f0, v1, 144);
    lwc1(f0, sp, 0xD4);
    swc1(f0, v1, 148);
    v0 = addiu(v1, 152);
    lwc1(f0, sp, 0xD8);
    swc1(f0, v0, 0);
    swc1(f21, v0, 0);
    swc1(f20, v1, 168);
    lbu(v0, s3, 0);
    if (i64(v0) < 0) {
        // 0x002febc0
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x002febac
        charge(ctx, 5);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x002febdc
    charge(ctx, 5);
    v0 = addu(a0, sp);
    swc1(f0, v0, 176);
    lbu(v0, s3, 1);
    if (i64(v0) < 0) {
        // 0x002fec04
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x002febf0
        charge(ctx, 5);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x002fec20
    charge(ctx, 5);
    v0 = addu(a0, sp);
    swc1(f0, v0, 180);
    lbu(v0, s3, 2);
    if (i64(v0) < 0) {
        // 0x002fec48
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x002fec34
        charge(ctx, 5);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x002fec64
    charge(ctx, 5);
    v0 = addu(a0, sp);
    swc1(f0, v0, 184);
    lbu(v0, s3, 3);
    if (i64(v0) < 0) {
        // 0x002fec8c
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x002fec78
        charge(ctx, 5);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x002feca8
    charge(ctx, 24);
    v0 = addu(a0, sp);
    swc1(f0, v0, 188);
    a0 = 5;
    a1 = addiu(sp, 0x90);
    a2 = 42;
    v0 = 0x960000;
    lw(v0, v0, 160);  // pfn_RwIm2DRenderPrimitive
    jalr(ctx, 0x2FECC4u, v0.u());
    ld(ra, sp, 0x80);
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
    sp = addiu(sp, 0xB10);
}

}  // namespace p3fes::game
