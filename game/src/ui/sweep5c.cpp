// Slice sweep5c: 149 functions taken by a reach-first work packet (game/include/p3fes/game/sweep5c.h lists the areas).
// The bodies are p3fes_handgen's from SLUS_216.21 and symbols/: every one keeps the recompiled body's registers, frame,
// spills, $ra links, cycle charges and check points (game/include/p3fes/game/hg_cpu.h). The readability pass on top:
// a role comment per function (a proposed name in brackets where the evidence is good, also symbols/deltas/sweep5c.sym)
// written from the instructions with IDA's pseudocode as a hint, and the MT_Scene record's offsets named
// (sweep5c::scene) in its accessors and load / poll bodies. Pair tests: tests/game/test_sweep5c.cpp.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/sweep5c.h"

namespace p3fes::recomp_gen {
void fn_ADXT_UpdateFsStat_0053e0b8(p3fes::EEContext&);
void fn_DIntr_0050d3a0(p3fes::EEContext&);
void fn_EIntr_0050d3f0(p3fes::EEContext&);
void fn_H_Cdvd_Request_00100d80(p3fes::EEContext&);
void fn_InvalidDCache_00503b98(p3fes::EEContext&);
void fn_K_Field_Get_001b9120(p3fes::EEContext&);
void fn_K_FldDungeon_GetCurrentFloor_001bff20(p3fes::EEContext&);
void fn_K_FldFrame_CreateCtlTask_001ad660(p3fes::EEContext&);
void fn_PS2RNA_Create_00560758(p3fes::EEContext&);
void fn_PS2RNA_ExecServer_00561138(p3fes::EEContext&);
void fn_RpSkyRenderStateSet_004d7f60(p3fes::EEContext&);
void fn_SRD_Create_00557a58(p3fes::EEContext&);
void fn_SRD_ExecServer_00558500(p3fes::EEContext&);
void fn_SRD_ReqRdDvd_00557b80(p3fes::EEContext&);
void fn_SRD_WaitComplete_00557e50(p3fes::EEContext&);
void fn_SyncDCache_00503a58(p3fes::EEContext&);
void fn_SyncDma_0051ad10(p3fes::EEContext&);
void fn__ErrMessage_005024f0(p3fes::EEContext&);
void fn___divdi3_0052eeb0(p3fes::EEContext&);
void fn___gthread_get_ee_key_use_0057f740(p3fes::EEContext&);
void fn___muldi3_0052ea78(p3fes::EEContext&);
void fn__execve_r_00520580(p3fes::EEContext&);
void fn__fs_version_00508378(p3fes::EEContext&);
void fn__sceCreateSema_00503160(p3fes::EEContext&);
void fn__sceDeleteSema_00503170(p3fes::EEContext&);
void fn__sceFsIobSemaMK_00507960(p3fes::EEContext&);
void fn__sceFsSigSema_00508078(p3fes::EEContext&);
void fn__sceFsWaitS_00508048(p3fes::EEContext&);
void fn__sceMpegDispatchMpegCallback_00500d10(p3fes::EEContext&);
void fn__sceMpegError_00502668(p3fes::EEContext&);
void fn__sceSignalSema_00503180(p3fes::EEContext&);
void fn__sceWaitSema_005031a0(p3fes::EEContext&);
void fn__write_r_00528970(p3fes::EEContext&);
void fn_atan2f_0052ea18(p3fes::EEContext&);
void fn_atomicGetWorldBoundingSphere_004912b0(p3fes::EEContext&);
void fn_dvCiCdSearchFile_00559dd8(p3fes::EEContext&);
void fn_dvci_conv_fname_0055a9b0(p3fes::EEContext&);
void fn_dvci_get_fstate_0055b220(p3fes::EEContext&);
void fn_frFontBuildGlyphList_003b0970(p3fes::EEContext&);
void fn_frFontDraw_003b1360(p3fes::EEContext&);
void fn_frFontGetStyleSize_003b35c0(p3fes::EEContext&);
void fn_frFontLineFadeStep_003b0ec0(p3fes::EEContext&);
void fn_get_iob_00507bc8(p3fes::EEContext&);
void fn_itfMesMngDestroyHandle_003a3060(p3fes::EEContext&);
void fn_itfMesMngInitialize_003a2d80(p3fes::EEContext&);
void fn_itfMesMngRequestMessage_003a30c0(p3fes::EEContext&);
void fn_itfMesMngSetSelectWord84_003a27c0(p3fes::EEContext&);
void fn_itfMesMngSetStateFlags_003a3e10(p3fes::EEContext&);
void fn_kwlnTaskCreate_00194b20(p3fes::EEContext&);
void fn_kwlnTaskDestroyWithHierarchy_00195020(p3fes::EEContext&);
void fn_kwlnTaskGetWorkData_00195540(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_new_iob_00507a50(p3fes::EEContext&);
void fn_printf_005225a8(p3fes::EEContext&);
void fn_sceCdBreak_00510f88(p3fes::EEContext&);
void fn_sceCdRead_00510b80(p3fes::EEContext&);
void fn_sceCdSync_00510148(p3fes::EEContext&);
void fn_sceDbcGetConnection_0051cad0(p3fes::EEContext&);
void fn_sceDbcSendData3_0051d308(p3fes::EEContext&);
void fn_sceDmaGetChan_004fa8f0(p3fes::EEContext&);
void fn_sceDmaRecvN_004fadc0(p3fes::EEContext&);
void fn_sceDmaSendN_004fac88(p3fes::EEContext&);
void fn_sceFsInit_00508170(p3fes::EEContext&);
void fn_sceFsSifCallRpc_00507ad8(p3fes::EEContext&);
void fn_scePrintf_00505e48(p3fes::EEContext&);
void fn_sceSifBindRpc_00507050(p3fes::EEContext&);
void fn_sceSifCallRpc_00507230(p3fes::EEContext&);
void fn_sceSifInitRpc_005068a8(p3fes::EEContext&);
void fn_sceSnprintf_00505d90(p3fes::EEContext&);
void fn_sinl_11_00585658(p3fes::EEContext&);
void fn_sprintf_00523ac8(p3fes::EEContext&);
void fn_srd_check_dvd_error_00557fe8(p3fes::EEContext&);
void fn_strcpy_00524270(p3fes::EEContext&);
void fn_strlen_00524388(p3fes::EEContext&);
void fn_strncat_005244c0(p3fes::EEContext&);
void fn_strncpy_00524828(p3fes::EEContext&);
void fn_sub_1052B0_001052b0(p3fes::EEContext&);
void fn_sub_109F60_00109f60(p3fes::EEContext&);
void fn_sub_1339A0_001339a0(p3fes::EEContext&);
void fn_sub_1948B0_001948b0(p3fes::EEContext&);
void fn_sub_198590_00198590(p3fes::EEContext&);
void fn_sub_19BEB0_0019beb0(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_1A0A90_001a0a90(p3fes::EEContext&);
void fn_sub_1A0EE0_001a0ee0(p3fes::EEContext&);
void fn_sub_1A23D0_001a23d0(p3fes::EEContext&);
void fn_sub_1A3B10_001a3b10(p3fes::EEContext&);
void fn_sub_1A3F20_001a3f20(p3fes::EEContext&);
void fn_sub_1A4050_001a4050(p3fes::EEContext&);
void fn_sub_1A4090_001a4090(p3fes::EEContext&);
void fn_sub_1A4110_001a4110(p3fes::EEContext&);
void fn_sub_1A41F0_001a41f0(p3fes::EEContext&);
void fn_sub_1A4260_001a4260(p3fes::EEContext&);
void fn_sub_1A4330_001a4330(p3fes::EEContext&);
void fn_sub_1B0870_001b0870(p3fes::EEContext&);
void fn_sub_1B0A20_001b0a20(p3fes::EEContext&);
void fn_sub_1B10F0_001b10f0(p3fes::EEContext&);
void fn_sub_1B3C90_001b3c90(p3fes::EEContext&);
void fn_sub_1B58B0_001b58b0(p3fes::EEContext&);
void fn_sub_1B8600_001b8600(p3fes::EEContext&);
void fn_sub_1B8870_001b8870(p3fes::EEContext&);
void fn_sub_1B8AE0_001b8ae0(p3fes::EEContext&);
void fn_sub_1C80C0_001c80c0(p3fes::EEContext&);
void fn_sub_20CA90_0020ca90(p3fes::EEContext&);
void fn_sub_20CCC0_0020ccc0(p3fes::EEContext&);
void fn_sub_20D500_0020d500(p3fes::EEContext&);
void fn_sub_21A3A0_0021a3a0(p3fes::EEContext&);
void fn_sub_21A410_0021a410(p3fes::EEContext&);
void fn_sub_21A480_0021a480(p3fes::EEContext&);
void fn_sub_21A590_0021a590(p3fes::EEContext&);
void fn_sub_21AFE0_0021afe0(p3fes::EEContext&);
void fn_sub_21B150_0021b150(p3fes::EEContext&);
void fn_sub_21B1F0_0021b1f0(p3fes::EEContext&);
void fn_sub_21B2D0_0021b2d0(p3fes::EEContext&);
void fn_sub_21B3A0_0021b3a0(p3fes::EEContext&);
void fn_sub_21B420_0021b420(p3fes::EEContext&);
void fn_sub_27C2B0_0027c2b0(p3fes::EEContext&);
void fn_sub_306610_00306610(p3fes::EEContext&);
void fn_sub_316690_00316690(p3fes::EEContext&);
void fn_sub_316970_00316970(p3fes::EEContext&);
void fn_sub_316F70_00316f70(p3fes::EEContext&);
void fn_sub_3170C0_003170c0(p3fes::EEContext&);
void fn_sub_3174E0_003174e0(p3fes::EEContext&);
void fn_sub_318A30_00318a30(p3fes::EEContext&);
void fn_sub_318B60_00318b60(p3fes::EEContext&);
void fn_sub_319840_00319840(p3fes::EEContext&);
void fn_sub_3198C0_003198c0(p3fes::EEContext&);
void fn_sub_319900_00319900(p3fes::EEContext&);
void fn_sub_319910_00319910(p3fes::EEContext&);
void fn_sub_31B220_0031b220(p3fes::EEContext&);
void fn_sub_31D4F0_0031d4f0(p3fes::EEContext&);
void fn_sub_31D530_0031d530(p3fes::EEContext&);
void fn_sub_31EBE0_0031ebe0(p3fes::EEContext&);
void fn_sub_324B50_00324b50(p3fes::EEContext&);
void fn_sub_3257E0_003257e0(p3fes::EEContext&);
void fn_sub_325C10_00325c10(p3fes::EEContext&);
void fn_sub_325D60_00325d60(p3fes::EEContext&);
void fn_sub_325E40_00325e40(p3fes::EEContext&);
void fn_sub_326030_00326030(p3fes::EEContext&);
void fn_sub_326190_00326190(p3fes::EEContext&);
void fn_sub_3261C0_003261c0(p3fes::EEContext&);
void fn_sub_326200_00326200(p3fes::EEContext&);
void fn_sub_326240_00326240(p3fes::EEContext&);
void fn_sub_326280_00326280(p3fes::EEContext&);
void fn_sub_3263B0_003263b0(p3fes::EEContext&);
void fn_sub_3299B0_003299b0(p3fes::EEContext&);
void fn_sub_329D60_00329d60(p3fes::EEContext&);
void fn_sub_32A120_0032a120(p3fes::EEContext&);
void fn_sub_32A540_0032a540(p3fes::EEContext&);
void fn_sub_3500E0_003500e0(p3fes::EEContext&);
void fn_sub_359110_00359110(p3fes::EEContext&);
void fn_sub_3A4010_003a4010(p3fes::EEContext&);
void fn_sub_3A4220_003a4220(p3fes::EEContext&);
void fn_sub_3A4360_003a4360(p3fes::EEContext&);
void fn_sub_3A5210_003a5210(p3fes::EEContext&);
void fn_sub_3B0030_003b0030(p3fes::EEContext&);
void fn_sub_3B4FC0_003b4fc0(p3fes::EEContext&);
void fn_sub_3B5020_003b5020(p3fes::EEContext&);
void fn_sub_3B50D0_003b50d0(p3fes::EEContext&);
void fn_sub_3B5430_003b5430(p3fes::EEContext&);
void fn_sub_3B54C0_003b54c0(p3fes::EEContext&);
void fn_sub_3B5550_003b5550(p3fes::EEContext&);
void fn_sub_3B5AB0_003b5ab0(p3fes::EEContext&);
void fn_sub_3B5D10_003b5d10(p3fes::EEContext&);
void fn_sub_3B5D50_003b5d50(p3fes::EEContext&);
void fn_sub_3B6030_003b6030(p3fes::EEContext&);
void fn_sub_3B63C0_003b63c0(p3fes::EEContext&);
void fn_sub_3B6440_003b6440(p3fes::EEContext&);
void fn_sub_3B7090_003b7090(p3fes::EEContext&);
void fn_sub_3B8FF0_003b8ff0(p3fes::EEContext&);
void fn_sub_3B9260_003b9260(p3fes::EEContext&);
void fn_sub_3B9500_003b9500(p3fes::EEContext&);
void fn_sub_3BAC40_003bac40(p3fes::EEContext&);
void fn_sub_3BB9B0_003bb9b0(p3fes::EEContext&);
void fn_sub_3BBA70_003bba70(p3fes::EEContext&);
void fn_sub_3BD0B0_003bd0b0(p3fes::EEContext&);
void fn_sub_3C7990_003c7990(p3fes::EEContext&);
void fn_sub_3C7D50_003c7d50(p3fes::EEContext&);
void fn_sub_3C7E50_003c7e50(p3fes::EEContext&);
void fn_sub_3C8FA0_003c8fa0(p3fes::EEContext&);
void fn_sub_3C9570_003c9570(p3fes::EEContext&);
void fn_sub_3CF440_003cf440(p3fes::EEContext&);
void fn_sub_461EA0_00461ea0(p3fes::EEContext&);
void fn_sub_463490_00463490(p3fes::EEContext&);
void fn_sub_463F20_00463f20(p3fes::EEContext&);
void fn_sub_491A80_00491a80(p3fes::EEContext&);
void fn_sub_492020_00492020(p3fes::EEContext&);
void fn_sub_492060_00492060(p3fes::EEContext&);
void fn_sub_494760_00494760(p3fes::EEContext&);
void fn_sub_4C1C50_004c1c50(p3fes::EEContext&);
void fn_sub_4C1D10_004c1d10(p3fes::EEContext&);
void fn_sub_4C2CC0_004c2cc0(p3fes::EEContext&);
void fn_sub_4C2D20_004c2d20(p3fes::EEContext&);
void fn_sub_4C2F10_004c2f10(p3fes::EEContext&);
void fn_sub_4C32A0_004c32a0(p3fes::EEContext&);
void fn_sub_4C3880_004c3880(p3fes::EEContext&);
void fn_sub_4C38C0_004c38c0(p3fes::EEContext&);
void fn_sub_4C43B0_004c43b0(p3fes::EEContext&);
void fn_sub_4C6560_004c6560(p3fes::EEContext&);
void fn_sub_4C6BE0_004c6be0(p3fes::EEContext&);
void fn_sub_4C6C20_004c6c20(p3fes::EEContext&);
void fn_sub_4C89A0_004c89a0(p3fes::EEContext&);
void fn_sub_4CA030_004ca030(p3fes::EEContext&);
void fn_sub_4CA560_004ca560(p3fes::EEContext&);
void fn_sub_4CA5B0_004ca5b0(p3fes::EEContext&);
void fn_sub_4CB1B0_004cb1b0(p3fes::EEContext&);
void fn_sub_4CB270_004cb270(p3fes::EEContext&);
void fn_sub_4CB2F0_004cb2f0(p3fes::EEContext&);
void fn_sub_4F1ED0_004f1ed0(p3fes::EEContext&);
void fn_sub_4F1F80_004f1f80(p3fes::EEContext&);
void fn_sub_4F1FD0_004f1fd0(p3fes::EEContext&);
void fn_sub_506430_00506430(p3fes::EEContext&);
void fn_sub_535F38_00535f38(p3fes::EEContext&);
void fn_sub_536440_00536440(p3fes::EEContext&);
void fn_sub_5365B8_005365b8(p3fes::EEContext&);
void fn_sub_536D28_00536d28(p3fes::EEContext&);
void fn_sub_536E90_00536e90(p3fes::EEContext&);
void fn_sub_5374E8_005374e8(p3fes::EEContext&);
void fn_sub_537858_00537858(p3fes::EEContext&);
void fn_sub_5379B0_005379b0(p3fes::EEContext&);
void fn_sub_5379F8_005379f8(p3fes::EEContext&);
void fn_sub_538C80_00538c80(p3fes::EEContext&);
void fn_sub_538EF0_00538ef0(p3fes::EEContext&);
void fn_sub_539148_00539148(p3fes::EEContext&);
void fn_sub_5396F8_005396f8(p3fes::EEContext&);
void fn_sub_53AE08_0053ae08(p3fes::EEContext&);
void fn_sub_53EA90_0053ea90(p3fes::EEContext&);
void fn_sub_53F5F0_0053f5f0(p3fes::EEContext&);
void fn_sub_541760_00541760(p3fes::EEContext&);
void fn_sub_542F88_00542f88(p3fes::EEContext&);
void fn_sub_5430B8_005430b8(p3fes::EEContext&);
void fn_sub_5430C8_005430c8(p3fes::EEContext&);
void fn_sub_5430D8_005430d8(p3fes::EEContext&);
void fn_sub_5431D8_005431d8(p3fes::EEContext&);
void fn_sub_5431F0_005431f0(p3fes::EEContext&);
void fn_sub_543220_00543220(p3fes::EEContext&);
void fn_sub_5433C0_005433c0(p3fes::EEContext&);
void fn_sub_5465A0_005465a0(p3fes::EEContext&);
void fn_sub_549EA0_00549ea0(p3fes::EEContext&);
void fn_sub_54CB78_0054cb78(p3fes::EEContext&);
void fn_sub_54CBC8_0054cbc8(p3fes::EEContext&);
void fn_sub_54CCE8_0054cce8(p3fes::EEContext&);
void fn_sub_54CE38_0054ce38(p3fes::EEContext&);
void fn_sub_54CE60_0054ce60(p3fes::EEContext&);
void fn_sub_552630_00552630(p3fes::EEContext&);
void fn_sub_554360_00554360(p3fes::EEContext&);
void fn_sub_5546F0_005546f0(p3fes::EEContext&);
void fn_sub_554708_00554708(p3fes::EEContext&);
void fn_sub_554720_00554720(p3fes::EEContext&);
void fn_sub_554940_00554940(p3fes::EEContext&);
void fn_sub_555898_00555898(p3fes::EEContext&);
void fn_sub_557AE0_00557ae0(p3fes::EEContext&);
void fn_sub_558610_00558610(p3fes::EEContext&);
void fn_sub_558988_00558988(p3fes::EEContext&);
void fn_sub_559DA8_00559da8(p3fes::EEContext&);
void fn_sub_55A198_0055a198(p3fes::EEContext&);
void fn_sub_55A1D0_0055a1d0(p3fes::EEContext&);
void fn_sub_55A898_0055a898(p3fes::EEContext&);
void fn_sub_55A8A8_0055a8a8(p3fes::EEContext&);
void fn_sub_55A8C8_0055a8c8(p3fes::EEContext&);
void fn_sub_55A8D0_0055a8d0(p3fes::EEContext&);
void fn_sub_560AF8_00560af8(p3fes::EEContext&);
void fn_sub_560C88_00560c88(p3fes::EEContext&);
void fn_sub_560D20_00560d20(p3fes::EEContext&);
void fn_sub_560F18_00560f18(p3fes::EEContext&);
void fn_sub_561258_00561258(p3fes::EEContext&);
void fn_sub_561390_00561390(p3fes::EEContext&);
void fn_sub_564978_00564978(p3fes::EEContext&);
void fn_sub_564990_00564990(p3fes::EEContext&);
void fn_sub_564AA8_00564aa8(p3fes::EEContext&);
void fn_sub_564DD0_00564dd0(p3fes::EEContext&);
void fn_sub_564F38_00564f38(p3fes::EEContext&);
void fn_sub_564FE8_00564fe8(p3fes::EEContext&);
void fn_sub_57D220_0057d220(p3fes::EEContext&);
void fn_sub_57FC60_0057fc60(p3fes::EEContext&);
void fn_sub_585590_00585590(p3fes::EEContext&);
void fn_sub_58BE40_0058be40(p3fes::EEContext&);
void fn_sub_58BEF0_0058bef0(p3fes::EEContext&);
void fn_sub_58C060_0058c060(p3fes::EEContext&);
void fn_sub_58C100_0058c100(p3fes::EEContext&);
void fn_sub_58C118_0058c118(p3fes::EEContext&);
void fn_sub_5940A0_005940a0(p3fes::EEContext&);
void fn_sub_594108_00594108(p3fes::EEContext&);
void fn_sub_5959D0_005959d0(p3fes::EEContext&);
void fn_sub_595BC0_00595bc0(p3fes::EEContext&);
void fn_sub_595D10_00595d10(p3fes::EEContext&);
void fn_sub_597330_00597330(p3fes::EEContext&);
void fn_sub_597368_00597368(p3fes::EEContext&);
void fn_sub_599408_00599408(p3fes::EEContext&);
void fn_sub_599B80_00599b80(p3fes::EEContext&);
void fn_sub_59BC20_0059bc20(p3fes::EEContext&);
void fn_sub_59BDD0_0059bdd0(p3fes::EEContext&);
void fn_sub_59C358_0059c358(p3fes::EEContext&);
void fn_sub_59C3B8_0059c3b8(p3fes::EEContext&);
void fn_sub_59C480_0059c480(p3fes::EEContext&);
void fn_sub_59C5E0_0059c5e0(p3fes::EEContext&);
void fn_sub_5A1CE0_005a1ce0(p3fes::EEContext&);
void fn_vsprintf_005288c8(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// 0x0017B860 sub_17B860 -- 732 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// g_data.c flag/value setter: a1 = party slot (1..10, else the g_data.c:5824 assert), a2 = kind. Kinds 425 / 415 map
// the slot through the word tables 0x5E3844 / 0x5E3840 (stride 8) to a flag number (<0x1600, else the :1933 assert;
// flag 4982 prints "hit") and set that bit in g_datFlagWords; any other kind resolves both slots to their unit
// records (slot 1 = 0x836224, others 0x834010 + 868*slot - 1732, :737 assert) and tail-forwards to sub_306610.
// [proposed name: gData_SetUnitFlag]
void sub_17B860(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0017b860
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s3 = a2;
    s2 = a3;
    s0 = dsll32(a1, 16);
    s0 = dsra32(s0, 16);
    if (s0 != 0) {
        // 0x0017b894
        charge(ctx, 3);
        v0 = slti(s0, 11);
        if (v0 == 0) {
            goto L_0017b8a0;
        }
        goto L_0017b8b4;
    }
L_0017b8a0:
    charge(ctx, 5);
    a0 = 0x5E0000;
    a0 = addiu(a0, 12440);  // "g_data.c"
    a1 = 5824;
    jal(ctx, 0x17B8ACu, gen::fn_sub_19D3F0_0019d3f0);
L_0017b8b4:
    charge(ctx, 4);
    v1 = s3 & 0xFFFF;
    v0 = 425;
    if (v1 == v0) {
        // 0x0017b988
        charge(ctx, 7);
        v1 = sll(s0, 3);
        v0 = 0x5E0000;
        v0 = addiu(v0, 14404);  // &0x5E3844
        v0 = addu(v0, v1);
        lw(s0, v0, 0);
        if (i64(s0) >= 0) {
            // 0x0017b9a4
            charge(ctx, 3);
            v0 = slti(s0, 5632);
            if (v0 == 0) {
                goto L_0017b9b0;
            }
            goto L_0017b9c4;
        }
    L_0017b9b0:
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 1933;
        jal(ctx, 0x17B9BCu, gen::fn_sub_19D3F0_0019d3f0);
    L_0017b9c4:
        charge(ctx, 3);
        v0 = 4982;
        if (s0 == v0) {
            // 0x0017b9d0
            charge(ctx, 3);
            a0 = addiu(gp, -27976);  // "hit \n"
            jal(ctx, 0x17B9D4u, gen::fn_printf_005225a8);
        }
        // 0x0017b9dc
        charge(ctx, 3);
        v1 = s0 & 0x1F;
        if (i64(s0) < 0) {
            // 0x0017b9e8
            charge(ctx, 2);
            if (v1 != 0) {
                // 0x0017b9f0
                charge(ctx, 1);
                v1 = addiu(v1, -32);
            }
        }
        // 0x0017b9f4
        charge(ctx, 5);
        v0 = 1;
        a0 = sllv(v0, v1);
        v0 = sra(s0, 5);
        if (i64(s0) < 0) {
            // 0x0017ba08
            charge(ctx, 2);
            v0 = addiu(s0, 31);
            v0 = sra(v0, 5);
        }
        // 0x0017ba10
        charge(ctx, 10);
        v1 = sll(v0, 2);
        v0 = 0x840000;
        v0 = addiu(v0, -24036);  // &g_datFlagWords
        v1 = addu(v0, v1);
        lw(v0, v1, 0);
        v0 = v0 | a0;
        sw(v0, v1, 0);
        v0 = 1;
    } else {
        // 0x0017b8c4
        charge(ctx, 3);
        v0 = 415;
        if (v1 == v0) {
            // 0x0017b8d8
            charge(ctx, 7);
            v1 = sll(s0, 3);
            v0 = 0x5E0000;
            v0 = addiu(v0, 14400);  // &0x5E3840
            v0 = addu(v0, v1);
            lw(s0, v0, 0);
            if (i64(s0) >= 0) {
                // 0x0017b8f4
                charge(ctx, 3);
                v0 = slti(s0, 5632);
                if (v0 == 0) {
                    goto L_0017b900;
                }
                goto L_0017b914;
            }
        L_0017b900:
            charge(ctx, 5);
            a0 = 0x5E0000;
            a0 = addiu(a0, 12440);  // "g_data.c"
            a1 = 1933;
            jal(ctx, 0x17B90Cu, gen::fn_sub_19D3F0_0019d3f0);
        L_0017b914:
            charge(ctx, 3);
            v0 = 4982;
            if (s0 == v0) {
                // 0x0017b920
                charge(ctx, 3);
                a0 = addiu(gp, -27976);  // "hit \n"
                jal(ctx, 0x17B924u, gen::fn_printf_005225a8);
            }
            // 0x0017b92c
            charge(ctx, 3);
            v1 = s0 & 0x1F;
            if (i64(s0) < 0) {
                // 0x0017b938
                charge(ctx, 2);
                if (v1 != 0) {
                    // 0x0017b940
                    charge(ctx, 1);
                    v1 = addiu(v1, -32);
                }
            }
            // 0x0017b944
            charge(ctx, 5);
            v0 = 1;
            a0 = sllv(v0, v1);
            v0 = sra(s0, 5);
            if (i64(s0) < 0) {
                // 0x0017b958
                charge(ctx, 2);
                v0 = addiu(s0, 31);
                v0 = sra(v0, 5);
            }
            // 0x0017b960
            charge(ctx, 10);
            v1 = sll(v0, 2);
            v0 = 0x840000;
            v0 = addiu(v0, -24036);  // &g_datFlagWords
            v1 = addu(v0, v1);
            lw(v0, v1, 0);
            v0 = v0 | a0;
            sw(v0, v1, 0);
            v0 = 1;
        } else {
            // 0x0017b8d0
            charge(ctx, 2);
            // 0x0017ba38
            charge(ctx, 5);
            s1 = dsll32(s1, 16);
            s1 = dsra32(s1, 16);
            v0 = 1;
            if (s1 != v0) {
                // 0x0017ba5c
                charge(ctx, 3);
                v0 = slti(s1, 11);
                if (v0 == 0) {
                    // 0x0017ba68
                    charge(ctx, 5);
                    a0 = 0x5E0000;
                    a0 = addiu(a0, 12440);  // "g_data.c"
                    a1 = 737;
                    jal(ctx, 0x17BA74u, gen::fn_sub_19D3F0_0019d3f0);
                }
                // 0x0017ba7c
                charge(ctx, 10);
                v1 = addiu(s1, -2);
                v0 = sll(v1, 5);
                v1 = subu(v0, v1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 2);
                v0 = 0x830000;
                v0 = addiu(v0, 16400);  // &0x834010
                v0 = addu(v0, v1);
                s1 = addiu(v0, 4);
            } else {
                // 0x0017ba4c
                charge(ctx, 4);
                s1 = 0x830000;
                s1 = addiu(s1, 25124);  // &0x836224
            }
            // 0x0017baa4
            charge(ctx, 3);
            v0 = 1;
            if (s0 != v0) {
                // 0x0017bac0
                charge(ctx, 3);
                v0 = slti(s0, 11);
                if (v0 == 0) {
                    // 0x0017bacc
                    charge(ctx, 5);
                    a0 = 0x5E0000;
                    a0 = addiu(a0, 12440);  // "g_data.c"
                    a1 = 737;
                    jal(ctx, 0x17BAD8u, gen::fn_sub_19D3F0_0019d3f0);
                }
                // 0x0017bae0
                charge(ctx, 10);
                v1 = addiu(s0, -2);
                v0 = sll(v1, 5);
                v1 = subu(v0, v1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 2);
                v0 = 0x830000;
                v0 = addiu(v0, 16400);  // &0x834010
                v0 = addu(v0, v1);
                a2 = addiu(v0, 4);
            } else {
                // 0x0017bab0
                charge(ctx, 4);
                a2 = 0x830000;
                a2 = addiu(a2, 25124);  // &0x836224
            }
            // 0x0017bb08
            charge(ctx, 5);
            a0 = s3;
            a1 = s1;
            a3 = s2;
            jal(ctx, 0x17BB14u, gen::fn_sub_306610_00306610);
        }
    }
    // 0x0017bb1c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x001A0D00 sub_1A0D00 -- 60 bytes; frame 0x10: ra sp+0x0
// Scene-manager sub-record 5 accessor: sub_3B5D50(5), plus 0x100 (null stays null).
void sub_1A0D00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a0d00
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 5;
    jal(ctx, 0x1A0D0Cu, gen::fn_sub_3B5D50_003b5d50);
    if (v0 == 0) {
        // 0x001a0d28
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x001a0d1c
        charge(ctx, 3);
        v0 = addiu(v0, 256);
    }
    // 0x001a0d2c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001A0D80 sub_1A0D80 -- 60 bytes; frame 0x10: ra sp+0x0
// Scene-manager sub-record 5 accessor: sub_3B5D50(5), plus 0x120 (null stays null).
void sub_1A0D80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a0d80
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 5;
    jal(ctx, 0x1A0D8Cu, gen::fn_sub_3B5D50_003b5d50);
    if (v0 == 0) {
        // 0x001a0da8
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x001a0d9c
        charge(ctx, 3);
        v0 = addiu(v0, 288);
    }
    // 0x001a0dac (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001A3AE0 sub_1A3AE0 -- 36 bytes; frame 0x10: ra sp+0x0
// Thin wrapper: sub_1A3B10(a0, a1, a2, 0) (the fourth argument forced to zero).
void sub_1A3AE0(EEContext& ctx) {
    using namespace hg;
    Gpr a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a3ae0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a3 = 0;
    jal(ctx, 0x1A3AECu, gen::fn_sub_1A3B10_001a3b10);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001A3BF0 sub_1A3BF0 -- 52 bytes; frame 0x10: ra sp+0x0
// Stores a1 at work+12 of the task in a0 (work = *(a0+60)); when work+40 is set, tail-calls sub_1A23D0 to refresh.
void sub_1A3BF0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a3bf0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, a0, 60);
    sw(a1, v1, 12);
    lw(a0, v1, 40);
    if (a0 != 0) {
        // 0x001a3c0c
        charge(ctx, 2);
        jal(ctx, 0x1A3C0Cu, gen::fn_sub_1A23D0_001a23d0);
    }
    // 0x001a3c14 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001A3DC0 sub_1A3DC0 -- 348 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Applies a table of a2 32-byte commands to the task in a0: per row, sub_1A3F20 resolves row[0], then row[1] selects
// 4 = sub_1A4260(row 3..5), 3 = sub_1A4110(row 3..6), 2 = sub_1A41F0(row 3), 1 = sub_1A4090(row 2); row[7] != 0 also
// calls sub_1A4050.
void sub_1A3DC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a3dc0
    enter(ctx, 13);  // entry check point + this block's cycles
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
    s1 = 0;
    for (;;) {
        // 0x001a3eec
        charge(ctx, 3);
        v1 = sltu(s1, s2);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001a3df4
        charge(ctx, 9);
        a0 = s4;
        lw(a1, s3, 0);
        jal(ctx, 0x1A3DFCu, gen::fn_sub_1A3F20_001a3f20);
        s0 = v0;
        lw(a0, s3, 4);
        v1 = 4;
        if (a0 == v1) {
            // 0x001a3eac
            charge(ctx, 7);
            a0 = s4;
            a1 = s0;
            lw(a2, s3, 12);
            lw(a3, s3, 16);
            lw(t0, s3, 20);
            jal(ctx, 0x1A3EC0u, gen::fn_sub_1A4260_001a4260);
        } else {
            // 0x001a3e18
            charge(ctx, 3);
            v1 = 3;
            if (a0 == v1) {
                // 0x001a3e84
                charge(ctx, 10);
                a0 = s4;
                a1 = s0;
                lw(a2, s3, 12);
                lw(a3, s3, 16);
                lw(t0, s3, 20);
                lw(t1, s3, 24);
                jal(ctx, 0x1A3E9Cu, gen::fn_sub_1A4110_001a4110);
            } else {
                // 0x001a3e24
                charge(ctx, 3);
                v1 = 2;
                if (a0 == v1) {
                    // 0x001a3e68
                    charge(ctx, 7);
                    a0 = s4;
                    a1 = s0;
                    lw(a2, s3, 12);
                    jal(ctx, 0x1A3E74u, gen::fn_sub_1A41F0_001a41f0);
                } else {
                    // 0x001a3e30
                    charge(ctx, 3);
                    v1 = 1;
                    if (a0 == v1) {
                        // 0x001a3e4c
                        charge(ctx, 7);
                        a0 = s4;
                        a1 = s0;
                        lw(a2, s3, 8);
                        jal(ctx, 0x1A3E58u, gen::fn_sub_1A4090_001a4090);
                    } else {
                        // 0x001a3e3c
                        charge(ctx, 2);
                        if (a0 != 0) {
                            // 0x001a3e44
                            charge(ctx, 2);
                        }
                    }
                }
            }
        }
        // 0x001a3ec8
        charge(ctx, 3);
        lw(a2, s3, 28);
        if (a2 != 0) {
            // 0x001a3ed4
            charge(ctx, 4);
            a0 = s4;
            a1 = s0;
            jal(ctx, 0x1A3EDCu, gen::fn_sub_1A4050_001a4050);
        }
        // 0x001a3ee4
        charge(ctx, 2);
        s1 = addiu(s1, 1);
        s3 = addiu(s3, 32);
    }
    // 0x001a3ef8
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x001A41B0 sub_1A41B0 -- 56 bytes; frame 0x10: ra sp+0x0
// Accessor: sub_1A4330() + 520 (null stays null).
void sub_1A41B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a41b0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x1A41B8u, gen::fn_sub_1A4330_001a4330);
    if (v0 != 0) {
        // 0x001a41d4
        charge(ctx, 1);
        v0 = addiu(v0, 520);
    } else {
        // 0x001a41c8
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001a41d8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001A4510 sub_1A4510 -- 100 bytes; leaf frame (no stack)
// Returns the first word of the list node at index (work+44 + work+48) of the task's work list (work = *(a0+60), head
// work+60, next at +552), or -1 when that index is not below the count at work+56.
void sub_1A4510(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x001a4510
    enter(ctx, 9);  // entry check point + this block's cycles
    lw(a0, a0, 60);
    lw(a1, a0, 60);
    lw(v1, a0, 48);
    lw(v0, a0, 44);
    v1 = addu(v0, v1);
    lw(v0, a0, 56);
    v0 = slt(v1, v0);
    if (v0 != 0) {
        // 0x001a4540
        charge(ctx, 3);
        a0 = 0;
        for (;;) {
            // 0x001a4554
            charge(ctx, 5);
            v0 = slt(a0, v1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001a454c
            charge(ctx, 2);
            lw(a1, a1, 552);
            a0 = addiu(a0, 1);
        }
        // 0x001a4568
        charge(ctx, 1);
        lw(v0, a1, 0);
    } else {
        // 0x001a4534
        charge(ctx, 3);
        v0 = si(-1);
    }
    // 0x001a456c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x001A4CD0 sub_1A4CD0 -- 232 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Creates the "position draw" task (priority 4174, update sub_1A4C10, draw sub_1A4CA0) under the parent a0 with an
// 80-byte work block from the 0x960184 allocator: identity scale (1.0f at +0/+20/+40), zero offsets, flags |=
// 0x20003, colour bytes ff,00,00,ff at +68. Returns the task or 0.
void sub_1A4CD0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a4cd0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    a0 = 1;
    a1 = 80;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x1A4CF8u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x001a4d18
        charge(ctx, 34);
        a0 = s1;
        a1 = 0x680000;
        a1 = addiu(a1, -29864);  // "position draw"
        a2 = 4174;
        a3 = 0x1A0000;
        a3 = addiu(a3, 19472);  // &sub_1A4C10
        t0 = 0x1A0000;
        t0 = addiu(t0, 19616);  // &sub_1A4CA0
        t1 = s0;
        jal(ctx, 0x1A4D3Cu, gen::fn_kwlnTaskCreate_00194b20);
        v1 = 0x3F800000;
        sw(v1, s0, 40);
        sw(v1, s0, 20);
        sw(v1, s0, 0);
        sw(zero, s0, 16);
        sw(zero, s0, 8);
        sw(zero, s0, 4);
        sw(zero, s0, 36);
        sw(zero, s0, 32);
        sw(zero, s0, 24);
        sw(zero, s0, 56);
        sw(zero, s0, 52);
        sw(zero, s0, 48);
        lw(a0, s0, 12);
        v1 = 0x20000;
        v1 = v1 | 0x3;
        v1 = a0 | v1;
        sw(v1, s0, 12);
        v1 = 255;
        sb(v1, s0, 68);
        sb(zero, s0, 69);
        sb(zero, s0, 70);
        sb(v1, s0, 71);
    } else {
        // 0x001a4d0c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001a4da0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001A4DC0 sub_1A4DC0 -- 44 bytes; leaf frame (no stack)
// Copies the 4 colour bytes at a1 into the position-draw work (+68..+71) of the task in a0.
void sub_1A4DC0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x001a4dc0
    enter(ctx, 11);  // entry check point + this block's cycles
    lw(t0, a0, 60);
    lbu(a3, a1, 0);
    lbu(a2, a1, 1);
    lbu(a0, a1, 2);
    lbu(v1, a1, 3);
    sb(a3, t0, 68);
    sb(a2, t0, 69);
    sb(a0, t0, 70);
    sb(v1, t0, 71);
}

// 0x001A4E60 sub_1A4E60 -- 100 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
// Sets the translation of the position-draw work (+48..+56 from the vector at a1) and rebuilds its matrix (sub_4C2CC0
// identity, sub_4C2D20 translate, sub_4C2F10 update).
void sub_1A4E60(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x001a4e60
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, 60);
    lwc1(f2, a1, 0);
    lwc1(f1, a1, 4);
    lwc1(f0, a1, 8);
    swc1(f2, s0, 48);
    swc1(f1, s0, 52);
    swc1(f0, s0, 56);
    a0 = addiu(sp, 0x20);
    jal(ctx, 0x1A4E8Cu, gen::fn_sub_4C2CC0_004c2cc0);
    a0 = s0;
    a1 = addiu(sp, 0x20);
    jal(ctx, 0x1A4E9Cu, gen::fn_sub_4C2D20_004c2d20);
    a0 = s0;
    jal(ctx, 0x1A4EA8u, gen::fn_sub_4C2F10_004c2f10);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0020B250 sub_20B250 -- 4292 bytes; frame 0x80: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// gc_model.c model colour/state update: a0 = model handle (+4 = kind 0..2, else the gc_model.c:678 assert; +224 = the
// material list). Pushes the handle's RGBA (+64..+67) into the kind's material slots through sub_20CCC0 (dirty bit 4
// of +0), scaling alpha by the per-kind fade floats, then renders the parts with the RW render-state hooks
// (pfn_RwRenderStateSet / RpSkyRenderStateSet) and the 0x21A3A0..0x21B420 helpers.
void sub_20B250(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x0020b250
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    lw(v0, a0, 4);
    if (i64(v0) >= 0) {
        // 0x0020b280
        charge(ctx, 3);
        v0 = slti(v0, 3);
        if (v0 == 0) {
            goto L_0020b28c;
        }
        goto L_0020b2a0;
    }
L_0020b28c:
    charge(ctx, 5);
    a0 = 0x690000;
    a0 = addiu(a0, -8032);  // "gc_model.c"
    a1 = 678;
    jal(ctx, 0x20B298u, gen::fn_sub_19D3F0_0019d3f0);
L_0020b2a0:
    charge(ctx, 4);
    lw(v1, s4, 4);
    v0 = 2;
    if (v1 == v0) {
        // 0x0020b2ec
        charge(ctx, 2);
        s0 = s4;
        s1 = addiu(s4, 224);
    } else {
        // 0x0020b2b0
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x0020b2dc
            charge(ctx, 4);
            s2 = s4;
            s1 = addiu(s4, 224);
        } else {
            // 0x0020b2b8
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                // 0x0020b2cc
                charge(ctx, 4);
                s5 = s4;
                s1 = addiu(s4, 224);
            } else {
                // 0x0020b2c4
                charge(ctx, 2);
            }
        }
    }
    // 0x0020b2f4
    charge(ctx, 11);
    jal(ctx, 0x20B2F4u, gen::fn_sub_4C38C0_004c38c0);
    s3 = v0;
    a0 = s3;
    a1 = s4;
    jal(ctx, 0x20B308u, gen::fn_sub_20CA90_0020ca90);
    lw(v0, s4, 0);
    v0 = v0 & 0x4;
    if (v0 != 0) {
        // 0x0020b320
        charge(ctx, 8);
        a0 = s1;
        a1 = addiu(s4, 64);
        jal(ctx, 0x20B328u, gen::fn_sub_20CCC0_0020ccc0);
        lw(v1, s4, 4);
        v0 = 2;
        if (v1 == v0) {
            // 0x0020b730
            charge(ctx, 4);
            a0 = addiu(s0, 368);
            a1 = addiu(s4, 64);
            jal(ctx, 0x20B738u, gen::fn_sub_20CCC0_0020ccc0);
        } else {
            // 0x0020b340
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                // 0x0020b634
                charge(ctx, 22);
                a0 = addiu(s5, 520);
                a1 = addiu(s4, 64);
                jal(ctx, 0x20B63Cu, gen::fn_sub_20CCC0_0020ccc0);
                a0 = addiu(s5, 376);
                a1 = addiu(s4, 64);
                jal(ctx, 0x20B64Cu, gen::fn_sub_20CCC0_0020ccc0);
                lbu(a1, s4, 64);
                lbu(a0, s4, 65);
                lbu(v1, s4, 66);
                lbu(v0, s4, 67);
                sb(a1, sp, 0x7C);
                sb(a0, sp, 0x7D);
                sb(v1, sp, 0x7E);
                sb(v0, sp, 0x7F);
                sb(zero, sp, 0x7C);
                sb(zero, sp, 0x7D);
                sb(zero, sp, 0x7E);
                lbu(v0, sp, 0x7F);
                if (i64(v0) < 0) {
                    // 0x0020b6a0
                    charge(ctx, 7);
                    v1 = srl(v0, 1);
                    v0 = v0 & 0x1;
                    v1 = v1 | v0;
                    mtc1(v1, f0);
                    cvt_s_w(f1, f0);
                    add_s(f1, f1, f1);
                } else {
                    // 0x0020b68c
                    charge(ctx, 5);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                }
                // 0x0020b6bc
                charge(ctx, 10);
                lwc1(f0, s5, 808);
                mul_s(f1, f1, f0);
                lwc1(f0, s5, 812);
                mul_s(f1, f0, f1);
                v0 = 0x4F000000;
                mtc1(v0, f0);
                c_le_s(f0, f1);
                if (cond(ctx)) {
                    // 0x0020b6fc
                    charge(ctx, 6);
                    sub_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    v0 = lui(0x8000);
                    v1 = v1 | v0;
                    v1 = v1 & 0xFF;
                } else {
                    // 0x0020b6e4
                    charge(ctx, 6);
                    cvt_w_s(f0, f1);
                    mfc1(v1, f0);
                    v1 = v1 & 0xFF;
                }
                // 0x0020b714
                charge(ctx, 7);
                sb(v1, sp, 0x7F);
                a0 = addiu(s5, 664);
                a1 = addiu(sp, 0x7C);
                jal(ctx, 0x20B720u, gen::fn_sub_20CCC0_0020ccc0);
            } else {
                // 0x0020b34c
                charge(ctx, 2);
                if (v1 == 0) {
                    // 0x0020b35c
                    charge(ctx, 19);
                    a0 = addiu(s2, 376);
                    a1 = addiu(s4, 64);
                    jal(ctx, 0x20B364u, gen::fn_sub_20CCC0_0020ccc0);
                    a0 = addiu(s2, 520);
                    a1 = addiu(s4, 64);
                    jal(ctx, 0x20B374u, gen::fn_sub_20CCC0_0020ccc0);
                    lbu(a1, s4, 64);
                    lbu(a0, s4, 65);
                    lbu(v1, s4, 66);
                    lbu(v0, s4, 67);
                    sb(a1, sp, 0x7C);
                    sb(a0, sp, 0x7D);
                    sb(v1, sp, 0x7E);
                    sb(v0, sp, 0x7F);
                    lbu(v0, s4, 67);
                    if (i64(v0) < 0) {
                        // 0x0020b3bc
                        charge(ctx, 7);
                        v1 = srl(v0, 1);
                        v0 = v0 & 0x1;
                        v1 = v1 | v0;
                        mtc1(v1, f0);
                        cvt_s_w(f1, f0);
                        add_s(f1, f1, f1);
                    } else {
                        // 0x0020b3a8
                        charge(ctx, 5);
                        mtc1(v0, f0);
                        cvt_s_w(f1, f0);
                    }
                    // 0x0020b3d8
                    charge(ctx, 14);
                    v0 = 0x41F00000;
                    mtc1(v0, f0);
                    mul_s(f1, f0, f1);
                    v0 = 0x42C80000;
                    mtc1(v0, f0);
                    div_s(f1, f1, f0);
                    v0 = 0x4F000000;
                    mtc1(v0, f0);
                    c_le_s(f0, f1);
                    if (cond(ctx)) {
                        // 0x0020b428
                        charge(ctx, 6);
                        sub_s(f0, f1, f0);
                        cvt_w_s(f0, f0);
                        mfc1(v1, f0);
                        v0 = lui(0x8000);
                        v1 = v1 | v0;
                        v1 = v1 & 0xFF;
                    } else {
                        // 0x0020b410
                        charge(ctx, 6);
                        cvt_w_s(f0, f1);
                        mfc1(v1, f0);
                        v1 = v1 & 0xFF;
                    }
                    // 0x0020b440
                    charge(ctx, 27);
                    sb(v1, sp, 0x7F);
                    a0 = addiu(s2, 664);
                    a1 = addiu(sp, 0x7C);
                    jal(ctx, 0x20B44Cu, gen::fn_sub_20CCC0_0020ccc0);
                    a0 = addiu(s2, 808);
                    a1 = addiu(sp, 0x7C);
                    jal(ctx, 0x20B45Cu, gen::fn_sub_20CCC0_0020ccc0);
                    lbu(a1, s4, 64);
                    lbu(a0, s4, 65);
                    lbu(v1, s4, 66);
                    lbu(v0, s4, 67);
                    sb(a1, sp, 0x7C);
                    sb(a0, sp, 0x7D);
                    sb(v1, sp, 0x7E);
                    sb(v0, sp, 0x7F);
                    v0 = 0x437F0000;
                    mtc1(v0, f1);
                    lwc1(f0, s2, 1532);
                    mul_s(f1, f1, f0);
                    v0 = 0x4F000000;
                    mtc1(v0, f0);
                    c_le_s(f0, f1);
                    if (cond(ctx)) {
                        // 0x0020b4c4
                        charge(ctx, 6);
                        sub_s(f0, f1, f0);
                        cvt_w_s(f0, f0);
                        mfc1(v1, f0);
                        v0 = lui(0x8000);
                        v1 = v1 | v0;
                        v1 = v1 & 0xFF;
                    } else {
                        // 0x0020b4ac
                        charge(ctx, 6);
                        cvt_w_s(f0, f1);
                        mfc1(v1, f0);
                        v1 = v1 & 0xFF;
                    }
                    // 0x0020b4dc
                    charge(ctx, 9);
                    sb(v1, sp, 0x7F);
                    a0 = addiu(s2, 952);
                    a1 = addiu(sp, 0x7C);
                    jal(ctx, 0x20B4E8u, gen::fn_sub_20CCC0_0020ccc0);
                    lw(v0, s2, 368);
                    v0 = v0 & 0x1;
                    if (v0 == 0) {
                        // 0x0020b544
                        charge(ctx, 4);
                        a0 = addiu(s2, 1096);
                        a1 = addiu(s4, 64);
                        jal(ctx, 0x20B54Cu, gen::fn_sub_20CCC0_0020ccc0);
                    } else {
                        // 0x0020b500
                        charge(ctx, 17);
                        a1 = addiu(sp, 0x7C);
                        lbu(a2, s4, 64);
                        lbu(a0, s4, 65);
                        lbu(v1, s4, 66);
                        lbu(v0, s4, 67);
                        sb(a2, sp, 0x7C);
                        sb(a0, sp, 0x7D);
                        sb(v1, sp, 0x7E);
                        sb(v0, sp, 0x7F);
                        sb(zero, sp, 0x7C);
                        sb(zero, sp, 0x7D);
                        sb(zero, sp, 0x7E);
                        a0 = addiu(s2, 1096);
                        jal(ctx, 0x20B534u, gen::fn_sub_20CCC0_0020ccc0);
                    }
                    // 0x0020b554
                    charge(ctx, 4);
                    lw(v0, s2, 368);
                    v0 = v0 & 0x1;
                    if (v0 == 0) {
                        // 0x0020b5a0
                        charge(ctx, 18);
                        lbu(a1, s4, 64);
                        lbu(a0, s4, 65);
                        lbu(v1, s4, 66);
                        lbu(v0, s4, 67);
                        sb(a1, sp, 0x7C);
                        sb(a0, sp, 0x7D);
                        sb(v1, sp, 0x7E);
                        sb(v0, sp, 0x7F);
                        v0 = 0x437F0000;
                        mtc1(v0, f1);
                        lwc1(f0, s2, 1528);
                        mul_s(f1, f1, f0);
                        v0 = 0x4F000000;
                        mtc1(v0, f0);
                        c_le_s(f0, f1);
                        if (cond(ctx)) {
                            // 0x0020b600
                            charge(ctx, 6);
                            sub_s(f0, f1, f0);
                            cvt_w_s(f0, f0);
                            mfc1(v1, f0);
                            v0 = lui(0x8000);
                            v1 = v1 | v0;
                            v1 = v1 & 0xFF;
                        } else {
                            // 0x0020b5e8
                            charge(ctx, 6);
                            cvt_w_s(f0, f1);
                            mfc1(v1, f0);
                            v1 = v1 & 0xFF;
                        }
                        // 0x0020b618
                        charge(ctx, 7);
                        sb(v1, sp, 0x7F);
                        a0 = addiu(s2, 1240);
                        a1 = addiu(sp, 0x7C);
                        jal(ctx, 0x20B624u, gen::fn_sub_20CCC0_0020ccc0);
                    } else {
                        // 0x0020b564
                        charge(ctx, 15);
                        a1 = addiu(sp, 0x7C);
                        lbu(a2, s4, 64);
                        lbu(a0, s4, 65);
                        lbu(v1, s4, 66);
                        lbu(v0, s4, 67);
                        sb(a2, sp, 0x7C);
                        sb(a0, sp, 0x7D);
                        sb(v1, sp, 0x7E);
                        sb(v0, sp, 0x7F);
                        sb(zero, sp, 0x7F);
                        a0 = addiu(s2, 1240);
                        jal(ctx, 0x20B590u, gen::fn_sub_20CCC0_0020ccc0);
                    }
                } else {
                    // 0x0020b354
                    charge(ctx, 2);
                }
            }
        }
        // 0x0020b740
        charge(ctx, 4);
        lw(v1, s4, 0);
        v0 = si(-5);
        v0 = v1 & v0;
        sw(v0, s4, 0);
    }
    // 0x0020b750
    charge(ctx, 3);
    lw(v0, s4, 4);
    if (v0 == 0) {
        // 0x0020b764
        charge(ctx, 15);
        lbu(a1, s4, 64);
        lbu(a0, s4, 65);
        lbu(v1, s4, 66);
        lbu(v0, s4, 67);
        sb(a1, sp, 0x7C);
        sb(a0, sp, 0x7D);
        sb(v1, sp, 0x7E);
        sb(v0, sp, 0x7F);
        v0 = 0x437F0000;
        mtc1(v0, f1);
        lwc1(f0, s2, 1532);
        mul_s(f1, f1, f0);
        lbu(v0, s4, 67);
        if (i64(v0) < 0) {
            // 0x0020b7b4
            charge(ctx, 7);
            v1 = srl(v0, 1);
            v0 = v0 & 0x1;
            v1 = v1 | v0;
            mtc1(v1, f0);
            cvt_s_w(f0, f0);
            add_s(f0, f0, f0);
        } else {
            // 0x0020b7a0
            charge(ctx, 5);
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
        }
        // 0x0020b7d0
        charge(ctx, 11);
        mul_s(f1, f1, f0);
        v0 = 0x437F0000;
        mtc1(v0, f0);
        div_s(f1, f1, f0);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f1);
        if (cond(ctx)) {
            // 0x0020b814
            charge(ctx, 6);
            sub_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x0020b7fc
            charge(ctx, 6);
            cvt_w_s(f0, f1);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x0020b82c
        charge(ctx, 17);
        sb(v1, sp, 0x7F);
        a0 = addiu(s2, 952);
        a1 = addiu(sp, 0x7C);
        jal(ctx, 0x20B838u, gen::fn_sub_20CCC0_0020ccc0);
        lbu(a1, s4, 64);
        lbu(a0, s4, 65);
        lbu(v1, s4, 66);
        lbu(v0, s4, 67);
        sb(a1, sp, 0x7C);
        sb(a0, sp, 0x7D);
        sb(v1, sp, 0x7E);
        sb(v0, sp, 0x7F);
        lw(v0, s2, 368);
        v0 = v0 & 0x1;
        if (v0 == 0) {
            // 0x0020b87c
            charge(ctx, 7);
            v0 = 0x437F0000;
            mtc1(v0, f1);
            lwc1(f0, s2, 1528);
            mul_s(f1, f1, f0);
            lbu(v0, s4, 67);
            if (i64(v0) < 0) {
                // 0x0020b8ac
                charge(ctx, 7);
                v1 = srl(v0, 1);
                v0 = v0 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f0, f0);
            } else {
                // 0x0020b898
                charge(ctx, 5);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
            }
            // 0x0020b8c8
            charge(ctx, 11);
            mul_s(f1, f1, f0);
            v0 = 0x437F0000;
            mtc1(v0, f0);
            div_s(f1, f1, f0);
            v0 = 0x4F000000;
            mtc1(v0, f0);
            c_le_s(f0, f1);
            if (cond(ctx)) {
                // 0x0020b90c
                charge(ctx, 6);
                sub_s(f0, f1, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFF;
            } else {
                // 0x0020b8f4
                charge(ctx, 6);
                cvt_w_s(f0, f1);
                mfc1(v1, f0);
                v1 = v1 & 0xFF;
            }
            // 0x0020b924
            charge(ctx, 1);
            sb(v1, sp, 0x7F);
        } else {
            // 0x0020b870
            charge(ctx, 3);
            sb(zero, sp, 0x7F);
        }
        // 0x0020b928
        charge(ctx, 4);
        a0 = addiu(s2, 1240);
        a1 = addiu(sp, 0x7C);
        jal(ctx, 0x20B930u, gen::fn_sub_20CCC0_0020ccc0);
    } else {
        // 0x0020b75c
        charge(ctx, 2);
    }
    // 0x0020b938
    charge(ctx, 21);
    s0 = 0x960000;
    s0 = addiu(s0, 144);  // &pfn_RwRenderStateSet
    a0 = 9;
    a1 = 2;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x20B94Cu, v0.u());
    a0 = 20;
    a1 = 2;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x20B960u, v0.u());
    a0 = 6;
    a1 = 0;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x20B974u, v0.u());
    lw(v1, s4, 4);
    v0 = 2;
    if (v1 == v0) {
        // 0x0020be20
        charge(ctx, 36);
        s5 = s0;
        a0 = 8;
        a1 = 0;
        lw(v0, s5, 0);
        jalr(ctx, 0x20BE30u, v0.u());
        a0 = 2;
        a1 = 68;
        jal(ctx, 0x20BE40u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 3;
        v0 = 0x30000;
        a1 = v0 | 0x17F3;
        jal(ctx, 0x20BE54u, gen::fn_RpSkyRenderStateSet_004d7f60);
        jal(ctx, 0x20BE5Cu, gen::fn_sub_21A410_0021a410);
        a0 = 1;
        a1 = v0;
        lw(v0, s5, 0);
        jalr(ctx, 0x20BE70u, v0.u());
        a0 = addiu(s4, 368);
        a1 = 4;
        a2 = s3;
        a3 = 3;
        jal(ctx, 0x20BE88u, gen::fn_sub_4F1ED0_004f1ed0);
        a0 = 3;
        a1 = 0x690000;
        a1 = addiu(a1, -8048);  // &0x68E090
        a2 = 6;
        jal(ctx, 0x20BEA0u, gen::fn_sub_4F1FD0_004f1fd0);
        jal(ctx, 0x20BEA8u, gen::fn_sub_4F1F80_004f1f80);
    } else {
        // 0x0020b98c
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x0020ba48
            charge(ctx, 208);
            s2 = s4;
            s5 = s0;
            a0 = 8;
            a1 = 0;
            lw(v0, s5, 0);
            jalr(ctx, 0x20BA5Cu, v0.u());
            a0 = 3;
            v0 = 0x30000;
            a1 = v0 | 0x17F3;
            jal(ctx, 0x20BA70u, gen::fn_RpSkyRenderStateSet_004d7f60);
            a0 = 3;
            a1 = 1;
            lw(v0, s5, 0);
            jalr(ctx, 0x20BA84u, v0.u());
            a0 = 4;
            a1 = 1;
            lw(v0, s5, 0);
            jalr(ctx, 0x20BA98u, v0.u());
            a0 = 0;
            jal(ctx, 0x20BAA4u, gen::fn_sub_21B3A0_0021b3a0);
            a0 = 1;
            a1 = v0;
            lw(v0, s5, 0);
            jalr(ctx, 0x20BAB8u, v0.u());
            a0 = 2;
            a1 = 68;
            jal(ctx, 0x20BAC8u, gen::fn_RpSkyRenderStateSet_004d7f60);
            a0 = addiu(s4, 376);
            a1 = 4;
            a2 = s3;
            a3 = 3;
            jal(ctx, 0x20BAE0u, gen::fn_sub_4F1ED0_004f1ed0);
            a0 = 3;
            a1 = 0x690000;
            a1 = addiu(a1, -8048);  // &0x68E090
            a2 = 6;
            jal(ctx, 0x20BAF8u, gen::fn_sub_4F1FD0_004f1fd0);
            jal(ctx, 0x20BB00u, gen::fn_sub_4F1F80_004f1f80);
            a0 = 2;
            a1 = 72;
            jal(ctx, 0x20BB10u, gen::fn_RpSkyRenderStateSet_004d7f60);
            a0 = 4;
            jal(ctx, 0x20BB1Cu, gen::fn_sub_21B3A0_0021b3a0);
            a0 = 1;
            a1 = v0;
            lw(v0, s5, 0);
            jalr(ctx, 0x20BB30u, v0.u());
            a0 = addiu(s4, 952);
            a1 = 4;
            a2 = s3;
            a3 = 3;
            jal(ctx, 0x20BB48u, gen::fn_sub_4F1ED0_004f1ed0);
            a0 = 3;
            a1 = 0x690000;
            a1 = addiu(a1, -8048);  // &0x68E090
            a2 = 6;
            jal(ctx, 0x20BB60u, gen::fn_sub_4F1FD0_004f1fd0);
            jal(ctx, 0x20BB68u, gen::fn_sub_4F1F80_004f1f80);
            a0 = 2;
            a1 = 68;
            jal(ctx, 0x20BB78u, gen::fn_RpSkyRenderStateSet_004d7f60);
            lhu(a0, s4, 372);
            jal(ctx, 0x20BB84u, gen::fn_sub_21A590_0021a590);
            a0 = 1;
            a1 = v0;
            lw(v0, s5, 0);
            jalr(ctx, 0x20BB98u, v0.u());
            a0 = addiu(s4, 1096);
            a1 = 4;
            a2 = s3;
            a3 = 3;
            jal(ctx, 0x20BBB0u, gen::fn_sub_4F1ED0_004f1ed0);
            a0 = 3;
            a1 = 0x690000;
            a1 = addiu(a1, -8048);  // &0x68E090
            a2 = 6;
            jal(ctx, 0x20BBC8u, gen::fn_sub_4F1FD0_004f1fd0);
            jal(ctx, 0x20BBD0u, gen::fn_sub_4F1F80_004f1f80);
            a0 = 2;
            a1 = 72;
            jal(ctx, 0x20BBE0u, gen::fn_RpSkyRenderStateSet_004d7f60);
            a0 = 3;
            jal(ctx, 0x20BBECu, gen::fn_sub_21B3A0_0021b3a0);
            a0 = 1;
            a1 = v0;
            lw(v0, s5, 0);
            jalr(ctx, 0x20BC00u, v0.u());
            a0 = addiu(s4, 808);
            a1 = 4;
            a2 = s3;
            a3 = 3;
            jal(ctx, 0x20BC18u, gen::fn_sub_4F1ED0_004f1ed0);
            a0 = 3;
            a1 = 0x690000;
            a1 = addiu(a1, -8048);  // &0x68E090
            a2 = 6;
            jal(ctx, 0x20BC30u, gen::fn_sub_4F1FD0_004f1fd0);
            jal(ctx, 0x20BC38u, gen::fn_sub_4F1F80_004f1f80);
            a0 = 2;
            a1 = 72;
            jal(ctx, 0x20BC48u, gen::fn_RpSkyRenderStateSet_004d7f60);
            a0 = 2;
            jal(ctx, 0x20BC54u, gen::fn_sub_21B3A0_0021b3a0);
            a0 = 1;
            a1 = v0;
            lw(v0, s5, 0);
            jalr(ctx, 0x20BC68u, v0.u());
            a0 = addiu(s4, 664);
            a1 = 4;
            a2 = s3;
            a3 = 3;
            jal(ctx, 0x20BC80u, gen::fn_sub_4F1ED0_004f1ed0);
            a0 = 3;
            a1 = 0x690000;
            a1 = addiu(a1, -8048);  // &0x68E090
            a2 = 6;
            jal(ctx, 0x20BC98u, gen::fn_sub_4F1FD0_004f1fd0);
            jal(ctx, 0x20BCA0u, gen::fn_sub_4F1F80_004f1f80);
            a0 = 2;
            a1 = 72;
            jal(ctx, 0x20BCB0u, gen::fn_RpSkyRenderStateSet_004d7f60);
            lhu(a0, s4, 372);
            jal(ctx, 0x20BCBCu, gen::fn_sub_21A590_0021a590);
            a0 = 1;
            a1 = v0;
            lw(v0, s5, 0);
            jalr(ctx, 0x20BCD0u, v0.u());
            a0 = addiu(s4, 1240);
            a1 = 4;
            a2 = s3;
            a3 = 3;
            jal(ctx, 0x20BCE8u, gen::fn_sub_4F1ED0_004f1ed0);
            a0 = 3;
            a1 = 0x690000;
            a1 = addiu(a1, -8048);  // &0x68E090
            a2 = 6;
            jal(ctx, 0x20BD00u, gen::fn_sub_4F1FD0_004f1fd0);
            jal(ctx, 0x20BD08u, gen::fn_sub_4F1F80_004f1f80);
            a0 = 2;
            a1 = 68;
            jal(ctx, 0x20BD18u, gen::fn_RpSkyRenderStateSet_004d7f60);
            a0 = 1;
            jal(ctx, 0x20BD24u, gen::fn_sub_21B3A0_0021b3a0);
            a0 = 1;
            a1 = v0;
            lw(v0, s5, 0);
            jalr(ctx, 0x20BD38u, v0.u());
            a0 = addiu(s4, 520);
            a1 = 4;
            a2 = s3;
            a3 = 3;
            jal(ctx, 0x20BD50u, gen::fn_sub_4F1ED0_004f1ed0);
            a0 = 3;
            a1 = 0x690000;
            a1 = addiu(a1, -8048);  // &0x68E090
            a2 = 6;
            jal(ctx, 0x20BD68u, gen::fn_sub_4F1FD0_004f1fd0);
            jal(ctx, 0x20BD70u, gen::fn_sub_4F1F80_004f1f80);
            lw(v0, s4, 0);
            v0 = v0 & 0x2;
            if (v0 != 0) {
                // 0x0020bd88
                charge(ctx, 38);
                a0 = 2;
                a1 = 72;
                jal(ctx, 0x20BD90u, gen::fn_RpSkyRenderStateSet_004d7f60);
                a0 = 3;
                a1 = a0;
                lw(v0, s5, 0);
                jalr(ctx, 0x20BDA4u, v0.u());
                a0 = 4;
                a1 = 3;
                lw(v0, s5, 0);
                jalr(ctx, 0x20BDB8u, v0.u());
                a0 = 5;
                jal(ctx, 0x20BDC4u, gen::fn_sub_21B3A0_0021b3a0);
                a0 = 1;
                a1 = v0;
                lw(v0, s5, 0);
                jalr(ctx, 0x20BDD8u, v0.u());
                a0 = addiu(s4, 1384);
                a1 = 4;
                a2 = s3;
                a3 = 3;
                jal(ctx, 0x20BDF0u, gen::fn_sub_4F1ED0_004f1ed0);
                a0 = 3;
                a1 = 0x690000;
                a1 = addiu(a1, -8048);  // &0x68E090
                a2 = 6;
                jal(ctx, 0x20BE08u, gen::fn_sub_4F1FD0_004f1fd0);
                jal(ctx, 0x20BE10u, gen::fn_sub_4F1F80_004f1f80);
            }
        } else {
            // 0x0020b994
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                // 0x0020b9a8
                charge(ctx, 40);
                s5 = s0;
                a0 = 8;
                a1 = 0;
                lw(v0, s5, 0);
                jalr(ctx, 0x20B9B8u, v0.u());
                a0 = 3;
                v0 = 0x30000;
                a1 = v0 | 0x17F3;
                jal(ctx, 0x20B9CCu, gen::fn_RpSkyRenderStateSet_004d7f60);
                lw(a0, s4, 368);
                lw(a1, s4, 372);
                jal(ctx, 0x20B9DCu, gen::fn_sub_21A480_0021a480);
                a0 = 1;
                a1 = v0;
                lw(v0, s5, 0);
                jalr(ctx, 0x20B9F0u, v0.u());
                a0 = 2;
                a1 = 68;
                jal(ctx, 0x20BA00u, gen::fn_RpSkyRenderStateSet_004d7f60);
                a0 = addiu(s4, 376);
                a1 = 4;
                a2 = s3;
                a3 = 3;
                jal(ctx, 0x20BA18u, gen::fn_sub_4F1ED0_004f1ed0);
                a0 = 3;
                a1 = 0x690000;
                a1 = addiu(a1, -8048);  // &0x68E090
                a2 = 6;
                jal(ctx, 0x20BA30u, gen::fn_sub_4F1FD0_004f1fd0);
                jal(ctx, 0x20BA38u, gen::fn_sub_4F1F80_004f1f80);
            } else {
                // 0x0020b9a0
                charge(ctx, 2);
            }
        }
    }
    // 0x0020beb0
    charge(ctx, 4);
    lw(v0, s4, 0);
    v0 = v0 & 0x1;
    if (v0 != 0) {
        // 0x0020bec0
        charge(ctx, 3);
        lw(v0, s4, 72);
        if (v0 == 0) {
            // 0x0020bed4
            charge(ctx, 4);
            lw(v1, s4, 4);
            v0 = 1;
            if (v1 == v0) {
                // 0x0020beec
                charge(ctx, 26);
                a0 = 2;
                a1 = 106;
                jal(ctx, 0x20BEF4u, gen::fn_RpSkyRenderStateSet_004d7f60);
                a0 = 1;
                jal(ctx, 0x20BF00u, gen::fn_sub_21B3A0_0021b3a0);
                a0 = 1;
                a1 = v0;
                lw(v0, s0, 0);
                jalr(ctx, 0x20BF14u, v0.u());
                a0 = addiu(s2, 520);
                a1 = 4;
                a2 = s3;
                a3 = 3;
                jal(ctx, 0x20BF2Cu, gen::fn_sub_4F1ED0_004f1ed0);
                a0 = 3;
                a1 = 0x690000;
                a1 = addiu(a1, -8048);  // &0x68E090
                a2 = 6;
                jal(ctx, 0x20BF44u, gen::fn_sub_4F1FD0_004f1fd0);
                jal(ctx, 0x20BF4Cu, gen::fn_sub_4F1F80_004f1f80);
            } else {
                // 0x0020bee4
                charge(ctx, 2);
            }
            // 0x0020bf54
            charge(ctx, 38);
            a0 = 2;
            a1 = 88;
            jal(ctx, 0x20BF5Cu, gen::fn_RpSkyRenderStateSet_004d7f60);
            s2 = 0x960000;
            s2 = addiu(s2, 144);  // &pfn_RwRenderStateSet
            a0 = 4;
            a1 = 3;
            lw(v0, s2, 0);  // pfn_RwRenderStateSet
            jalr(ctx, 0x20BF78u, v0.u());
            a0 = 6;
            jal(ctx, 0x20BF84u, gen::fn_sub_21B3A0_0021b3a0);
            a0 = 1;
            a1 = v0;
            lw(v0, s2, 0);  // pfn_RwRenderStateSet
            jalr(ctx, 0x20BF98u, v0.u());
            a0 = addiu(s4, 76);
            a1 = 4;
            a2 = s3;
            a3 = 3;
            jal(ctx, 0x20BFB0u, gen::fn_sub_4F1ED0_004f1ed0);
            a0 = 3;
            a1 = 0x690000;
            a1 = addiu(a1, -8048);  // &0x68E090
            a2 = 6;
            jal(ctx, 0x20BFC8u, gen::fn_sub_4F1FD0_004f1fd0);
            jal(ctx, 0x20BFD0u, gen::fn_sub_4F1F80_004f1f80);
            a0 = 4;
            a1 = 1;
            lw(v0, s2, 0);  // pfn_RwRenderStateSet
            jalr(ctx, 0x20BFE4u, v0.u());
        } else {
            // 0x0020becc
            charge(ctx, 2);
        }
    }
    // 0x0020bfec
    charge(ctx, 4);
    lw(v1, s4, 4);
    v0 = 1;
    if (v1 == v0) {
        // 0x0020c004
        charge(ctx, 43);
        s2 = 0x960000;
        s2 = addiu(s2, 144);  // &pfn_RwRenderStateSet
        a0 = 6;
        a1 = 0;
        lw(v0, s2, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x20C018u, v0.u());
        a0 = 8;
        a1 = 0;
        lw(v0, s2, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x20C02Cu, v0.u());
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x17FB;
        jal(ctx, 0x20C040u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 2;
        a1 = 68;
        jal(ctx, 0x20C050u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 1;
        jal(ctx, 0x20C05Cu, gen::fn_sub_21B420_0021b420);
        a0 = 1;
        a1 = v0;
        lw(v0, s2, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x20C070u, v0.u());
        a0 = addiu(s4, 664);
        a1 = 4;
        a2 = s3;
        a3 = 3;
        jal(ctx, 0x20C088u, gen::fn_sub_4F1ED0_004f1ed0);
        a0 = 3;
        a1 = 0x690000;
        a1 = addiu(a1, -8048);  // &0x68E090
        a2 = 6;
        jal(ctx, 0x20C0A0u, gen::fn_sub_4F1FD0_004f1fd0);
        jal(ctx, 0x20C0A8u, gen::fn_sub_4F1F80_004f1f80);
    } else {
        // 0x0020bffc
        charge(ctx, 2);
    }
    // 0x0020c0b0
    charge(ctx, 41);
    jal(ctx, 0x20C0B0u, gen::fn_sub_21A3A0_0021a3a0);
    s2 = 0x960000;
    s2 = addiu(s2, 144);  // &pfn_RwRenderStateSet
    a0 = 1;
    a1 = v0;
    lw(v0, s2, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x20C0CCu, v0.u());
    a0 = 2;
    a1 = 68;
    jal(ctx, 0x20C0DCu, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 6;
    a1 = 0;
    lw(v0, s2, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x20C0F0u, v0.u());
    a0 = 8;
    a1 = 0;
    lw(v0, s2, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x20C104u, v0.u());
    a0 = s1;
    a1 = 4;
    a2 = s3;
    a3 = 3;
    jal(ctx, 0x20C11Cu, gen::fn_sub_4F1ED0_004f1ed0);
    a0 = 3;
    a1 = 0x690000;
    a1 = addiu(a1, -8048);  // &0x68E090
    a2 = 6;
    jal(ctx, 0x20C134u, gen::fn_sub_4F1FD0_004f1fd0);
    jal(ctx, 0x20C13Cu, gen::fn_sub_4F1F80_004f1f80);
    lw(v0, s4, 0);
    v0 = v0 & 0x8;
    if (v0 != 0) {
        // 0x0020c154
        charge(ctx, 6);
        lw(v0, s4, 220);
        lw(v0, v0, 0);
        v0 = nor(v0, 0);
        v0 = v0 & 0x1;
        if (v0 == 0) {
            // 0x0020c2ac
            charge(ctx, 9);
            a0 = 3;
            v0 = 0x70000;
            a1 = v0 | 0x1801;
            jal(ctx, 0x20C2B8u, gen::fn_RpSkyRenderStateSet_004d7f60);
            a0 = 2;
            a1 = 72;
            jal(ctx, 0x20C2C8u, gen::fn_RpSkyRenderStateSet_004d7f60);
        } else {
            // 0x0020c16c
            charge(ctx, 19);
            s1 = s2;
            a0 = 6;
            a1 = 0;
            lw(v0, s1, 0);
            jalr(ctx, 0x20C17Cu, v0.u());
            a0 = 8;
            a1 = 0;
            lw(v0, s1, 0);
            jalr(ctx, 0x20C190u, v0.u());
            a0 = 2;
            a1 = 106;
            jal(ctx, 0x20C1A0u, gen::fn_RpSkyRenderStateSet_004d7f60);
            lw(v1, s4, 4);
            v0 = 2;
            if (v1 == v0) {
                // 0x0020c250
                charge(ctx, 9);
                a0 = 3;
                v0 = 0x70000;
                a1 = v0 | 0x1801;
                jal(ctx, 0x20C25Cu, gen::fn_RpSkyRenderStateSet_004d7f60);
                a0 = 2;
                a1 = 72;
                jal(ctx, 0x20C26Cu, gen::fn_RpSkyRenderStateSet_004d7f60);
            } else {
                // 0x0020c1b8
                charge(ctx, 3);
                a0 = 1;
                if (v1 == a0) {
                    // 0x0020c210
                    charge(ctx, 16);
                    a0 = 0;
                    jal(ctx, 0x20C214u, gen::fn_sub_21B420_0021b420);
                    a0 = 1;
                    a1 = v0;
                    lw(v0, s0, 0);
                    jalr(ctx, 0x20C228u, v0.u());
                    a0 = addiu(s4, 520);
                    a1 = 4;
                    a2 = s3;
                    a3 = 3;
                    jal(ctx, 0x20C240u, gen::fn_sub_4F1ED0_004f1ed0);
                } else {
                    // 0x0020c1c4
                    charge(ctx, 2);
                    if (v1 == 0) {
                        // 0x0020c1d4
                        charge(ctx, 15);
                        jal(ctx, 0x20C1D4u, gen::fn_sub_21B3A0_0021b3a0);
                        a0 = 1;
                        a1 = v0;
                        lw(v0, s0, 0);
                        jalr(ctx, 0x20C1E8u, v0.u());
                        a0 = addiu(s4, 520);
                        a1 = 4;
                        a2 = s3;
                        a3 = 3;
                        jal(ctx, 0x20C200u, gen::fn_sub_4F1ED0_004f1ed0);
                    } else {
                        // 0x0020c1cc
                        charge(ctx, 2);
                    }
                }
            }
            // 0x0020c274
            charge(ctx, 14);
            a0 = 3;
            a1 = 0x690000;
            a1 = addiu(a1, -8048);  // &0x68E090
            a2 = 6;
            jal(ctx, 0x20C284u, gen::fn_sub_4F1FD0_004f1fd0);
            jal(ctx, 0x20C28Cu, gen::fn_sub_4F1F80_004f1f80);
            a0 = 2;
            a1 = 88;
            jal(ctx, 0x20C29Cu, gen::fn_RpSkyRenderStateSet_004d7f60);
        }
        // 0x0020c2d0
        charge(ctx, 4);
        lw(a0, s4, 220);
        a1 = s3;
        jal(ctx, 0x20C2D8u, gen::fn_sub_20D500_0020d500);
    }
    // 0x0020c2e0
    charge(ctx, 13);
    a0 = s3;
    jal(ctx, 0x20C2E4u, gen::fn_sub_4C3880_004c3880);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x0020C400 sub_20C400 -- 244 bytes; frame 0x70: ra sp+0x40, s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// Screen to camera-plane projection: with the current camera's view window (sub_198590()+104) and the frame size
// (sub_4CA5B0 / sub_4CA560), maps the screen point a1 (pixels) to x,y at depth $f12 into a2; z = $f12.
void sub_20C400(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f20{ctx, 20};
    // 0x0020c400
    enter(ctx, 61);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s2 = a1;
    mov_s(f20, f12);
    s1 = a2;
    jal(ctx, 0x20C424u, gen::fn_sub_198590_00198590);
    s0 = addiu(v0, 104);
    jal(ctx, 0x20C430u, gen::fn_sub_4CA5B0_004ca5b0);
    a0 = addiu(sp, 0x50);
    a1 = v0;
    jal(ctx, 0x20C440u, gen::fn_sub_4CA560_004ca560);
    lwc1(f0, s2, 0);
    v1 = 0x3F000000;
    mtc1(v1, f3);
    sub_s(f0, f0, f3);
    neg_s(f1, f0);
    lw(v1, sp, 0x50);
    v1 = sra(v1, 1);
    mtc1(v1, f0);
    cvt_s_w(f0, f0);
    div_s(f0, f1, f0);
    v1 = 0x3F800000;
    mtc1(v1, f2);
    add_s(f1, f2, f0);
    lwc1(f0, s0, 0);
    mul_s(f0, f0, f1);
    mul_s(f0, f20, f0);
    swc1(f0, s1, 0);
    lwc1(f0, s2, 4);
    sub_s(f0, f0, f3);
    neg_s(f1, f0);
    lw(v1, sp, 0x54);
    v1 = sra(v1, 1);
    mtc1(v1, f0);
    cvt_s_w(f0, f0);
    div_s(f0, f1, f0);
    add_s(f1, f2, f0);
    lwc1(f0, s0, 4);
    mul_s(f0, f0, f1);
    mul_s(f0, f20, f0);
    swc1(f0, s1, 4);
    swc1(f20, s1, 8);
    ld(ra, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x0020C500 sub_20C500 -- 144 bytes; frame 0x60: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// Returns half of the current raster width (sub_4CA5B0 / sub_4CA560 frame size, >> 1).
void sub_20C500(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f20{ctx, 20};
    // 0x0020c500
    enter(ctx, 36);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s1 = a0;
    mov_s(f20, f12);
    jal(ctx, 0x20C51Cu, gen::fn_sub_198590_00198590);
    s0 = addiu(v0, 104);
    jal(ctx, 0x20C528u, gen::fn_sub_4CA5B0_004ca5b0);
    a0 = addiu(sp, 0x40);
    a1 = v0;
    jal(ctx, 0x20C538u, gen::fn_sub_4CA560_004ca560);
    v0 = 0x40C00000;
    mtc1(v0, f1);
    lwc1(f0, s1, 44);
    mul_s(f1, f1, f0);
    lw(v0, sp, 0x40);
    v0 = sra(v0, 1);
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    mul_s(f1, f1, f0);
    lwc1(f0, s0, 0);
    mul_s(f0, f20, f0);
    div_s(f0, f1, f0);
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x0021AB80 sub_21AB80 -- 264 bytes; frame 0x140: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// gc_res.c persona card texture request: when card a0 is not already loaded (sub_21AFE0), takes a free slot
// (sub_21B150), marks it, formats "card/persona/i_prc%03x.tmx" and starts H_Cdvd_Request on it; otherwise returns
// sub_21B1F0(a0). Asserts the resource root (gc_res.c:124).
void sub_21AB80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0021ab80
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x140);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(v0, gp, -18932);  // 0x7CE2FC
    if (v0 == 0) {
        // 0x0021aba4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7624);  // "gc_res.c"
        a1 = 124;
        jal(ctx, 0x21ABB0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0021abb8
    charge(ctx, 6);
    lw(s0, gp, -18932);  // 0x7CE2FC
    a0 = s2;
    jal(ctx, 0x21ABC0u, gen::fn_sub_21AFE0_0021afe0);
    if (v0 == 0) {
        // 0x0021abe4
        charge(ctx, 34);
        jal(ctx, 0x21ABE4u, gen::fn_sub_21B150_0021b150);
        s1 = v0;
        v0 = sll(s1, 4);
        v1 = addu(s0, v0);
        lw(v0, v1, 396);
        v0 = v0 | 0x1;
        sw(v0, v1, 396);
        sh(s2, v1, 400);
        sw(zero, v1, 404);
        v0 = 1;
        sw(v0, v1, 408);
        jal(ctx, 0x21AC14u, gen::fn_sub_21B2D0_0021b2d0);
        s0 = v0;
        v1 = 1;
        sw(v1, v0, 272);
        sw(s1, v0, 276);
        a2 = s2 & 0xFFFF;
        a0 = addiu(sp, 0x40);
        a1 = 0x690000;
        a1 = addiu(a1, -7504);  // "card/persona/i_prc%03x.tmx"
        jal(ctx, 0x21AC3Cu, gen::fn_sprintf_00523ac8);
        a0 = addiu(sp, 0x40);
        a1 = 0;
        jal(ctx, 0x21AC4Cu, gen::fn_H_Cdvd_Request_00100d80);
        sw(v0, s0, 8);
        v1 = 1;
        sw(v1, s0, 4);
        lw(v1, s0, 0);
        v1 = v1 | 0x1;
        sw(v1, s0, 0);
    } else {
        // 0x0021abd0
        charge(ctx, 5);
        a0 = s2;
        jal(ctx, 0x21ABD4u, gen::fn_sub_21B1F0_0021b1f0);
    }
    // 0x0021ac6c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x140);
}

// 0x002B94F0 sub_2B94F0 -- 148 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Releases an array of a0+84 (u16) entries at *(a0+88): each non-null entry goes through sub_3257E0; then frees a0
// through the 0x96017C free hook.
void sub_2B94F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002b94f0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lhu(s1, a0, 84);
    lw(s2, a0, 88);
    s3 = 0;
    for (;;) {
        // 0x002b9540
        charge(ctx, 4);
        v0 = s3 & 0xFFFF;
        v0 = slt(v0, s1);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002b9520
        charge(ctx, 3);
        lw(a0, s2, 0);
        if (a0 != 0) {
            // 0x002b952c
            charge(ctx, 2);
            jal(ctx, 0x2B952Cu, gen::fn_sub_3257E0_003257e0);
        }
        // 0x002b9534
        charge(ctx, 3);
        s2 = addiu(s2, 4);
        v0 = addiu(s3, 1);
        s3 = v0 & 0xFFFF;
    }
    // 0x002b9550
    charge(ctx, 13);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x2B955Cu, v0.u());
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00316E00 sub_316E00 -- 368 bytes; frame 0x150: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Field-unit model (re)load for (major a0, minor a1): looks up the record in the bucket list dword_9571F0[a0] (next
// at +1060, minor at +214); when found, re-binds it (sub_316690), flags +216 |= 0x2000 (and 0x4000 when a2 & 1) and
// runs sub_316F70; otherwise loads it first (sub_31D530) and does the same.
void sub_316E00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00316e00
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x150);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    s1 = a2;
    v0 = s3 & 0xFFFF;
    v1 = sll(v0, 2);
    v0 = 0x950000;
    v0 = addiu(v0, 29168);  // &0x9571F0
    v0 = addu(v0, v1);
    lw(a0, v0, 0);
    v1 = s2 & 0xFFFF;
    for (;;) {
        // 0x00316e58
        charge(ctx, 4);
        if (a0 != 0) {
            backedge(ctx);
            // 0x00316e48
            charge(ctx, 3);
            lhu(v0, a0, 214);
            if (v0 != v1) {
                // 0x00316e54
                charge(ctx, 1);
                lw(a0, a0, 1060);
                continue;
            }
        }
        break;
    }
    // 0x00316e68
    charge(ctx, 2);
    if (a0 != 0) {
        // 0x00316f08
        charge(ctx, 8);
        a0 = s3;
        a1 = s2;
        jal(ctx, 0x316F10u, gen::fn_sub_316690_00316690);
        s0 = v0;
        v0 = s1 & 0x1;
        if (v0 != 0) {
            // 0x00316f28
            charge(ctx, 3);
            lhu(v0, s0, 216);
            v0 = v0 | 0x4000;
            sh(v0, s0, 216);
        }
        // 0x00316f34
        charge(ctx, 6);
        lhu(v0, s0, 216);
        v0 = v0 | 0x2000;
        sh(v0, s0, 216);
        a0 = s0;
        jal(ctx, 0x316F44u, gen::fn_sub_316F70_00316f70);
    } else {
        // 0x00316e70
        charge(ctx, 13);
        a0 = s3;
        a1 = s2;
        a2 = addiu(sp, 0x50);
        jal(ctx, 0x316E7Cu, gen::fn_sub_31D530_0031d530);
        a0 = s3;
        a1 = s2;
        jal(ctx, 0x316E8Cu, gen::fn_sub_316690_00316690);
        s0 = v0;
        v0 = s1 & 0x1;
        if (v0 != 0) {
            // 0x00316ea4
            charge(ctx, 3);
            lhu(v0, s0, 216);
            v0 = v0 | 0x4000;
            sh(v0, s0, 216);
        }
        // 0x00316eb0
        charge(ctx, 16);
        a0 = s0;
        jal(ctx, 0x316EB4u, gen::fn_sub_319840_00319840);
        a0 = s0;
        a1 = addiu(sp, 0x50);
        jal(ctx, 0x316EC4u, gen::fn_sub_3198C0_003198c0);
        a0 = s0;
        jal(ctx, 0x316ED0u, gen::fn_sub_316F70_00316f70);
        a0 = s3;
        a1 = s2;
        jal(ctx, 0x316EE0u, gen::fn_sub_31D4F0_0031d4f0);
        if (v0 != 0) {
            // 0x00316ef0
            charge(ctx, 4);
            a0 = s0;
            a1 = 1;
            jal(ctx, 0x316EF8u, gen::fn_sub_319900_00319900);
        }
        // 0x00316f00
        charge(ctx, 2);
    }
    // 0x00316f4c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    v0 = s0;
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x150);
}

// 0x00316F70 sub_316F70 -- 336 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Field-unit model load step: for a record whose +216 has 0x2000 (load requested) and not 0x1000 (ready), polls the
// resource (sub_31EBE0 on +1016), then links the shared ready twin from dword_9571F0 or builds it (sub_31B220 /
// sub_319910 / sub_316970 / sub_3170C0). Returns 1 when ready, 0 while loading.
void sub_316F70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00316f70
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lhu(v1, a0, 216);
    v0 = v1 & 0x1000;
    if (v0 == 0) {
        // 0x00316f9c
        charge(ctx, 3);
        v0 = v1 & 0x2000;
        if (v0 != 0) {
            // 0x00317004
            charge(ctx, 5);
            a0 = addiu(s0, 1016);
            jal(ctx, 0x317008u, gen::fn_sub_31EBE0_0031ebe0);
            if (v0 != 0) {
                // 0x00317024
                charge(ctx, 9);
                lhu(a1, s0, 214);
                lhu(v0, s0, 212);
                v1 = sll(v0, 2);
                v0 = 0x950000;
                v0 = addiu(v0, 29168);  // &0x9571F0
                v0 = addu(v0, v1);
                lw(a0, v0, 0);
                for (;;) {
                    // 0x00317068
                    charge(ctx, 2);
                    if (a0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00317048
                    charge(ctx, 3);
                    lhu(v0, a0, 214);
                    if (v0 == a1) {
                        // 0x00317054
                        charge(ctx, 4);
                        lhu(v0, a0, 216);
                        v0 = v0 & 0x1000;
                        if (v0 != 0) {
                            break;
                        }
                        goto L_00317064;
                    }
                L_00317064:
                    charge(ctx, 1);
                    lw(a0, a0, 1060);
                }
                // 0x00317070
                charge(ctx, 2);
                if (a0 != 0) {
                    // 0x00317084
                    charge(ctx, 6);
                    a1 = s0;
                    jal(ctx, 0x317088u, gen::fn_sub_3170C0_003170c0);
                    lhu(v0, s0, 216);
                    v0 = v0 & 0xDFFF;
                    sh(v0, s0, 216);
                L_0031709c:
                    charge(ctx, 4);
                    lhu(v0, s0, 216);
                    v0 = v0 | 0x1000;
                    sh(v0, s0, 216);
                    v0 = 1;
                } else {
                    // 0x00317078
                    charge(ctx, 3);
                    v0 = 0;
                }
            } else {
                // 0x00317018
                charge(ctx, 3);
                v0 = 0;
            }
        } else {
            // 0x00316fa8
            charge(ctx, 4);
            jal(ctx, 0x316FA8u, gen::fn_sub_31B220_0031b220);
            if (v0 != 0) {
                // 0x00316fc4
                charge(ctx, 5);
                a0 = addiu(s0, 1016);
                jal(ctx, 0x316FC8u, gen::fn_sub_31EBE0_0031ebe0);
                if (v0 != 0) {
                    // 0x00316fe4
                    charge(ctx, 8);
                    a0 = s0;
                    jal(ctx, 0x316FE8u, gen::fn_sub_319910_00319910);
                    a0 = s0;
                    jal(ctx, 0x316FF4u, gen::fn_sub_316970_00316970);
                    goto L_0031709c;
                }
                // 0x00316fd8
                charge(ctx, 3);
                v0 = 0;
            } else {
                // 0x00316fb8
                charge(ctx, 3);
                v0 = 0;
            }
        }
    } else {
        // 0x00316f90
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x003170ac (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00324BD0 sub_324BD0 -- 1744 bytes; frame 0x110: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Builds an effect-instance node from a descriptor: zeroes it (memset), copies the name (strcpy), then sets up its
// parts through sub_324B50 / sub_3261C0 / sub_326240 / sub_326200 / sub_326190 / sub_325C10 / sub_325D60 / sub_325E40
// and the per-type hooks in off_69BE20.
void sub_324BD0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    Vf vf0{ctx, 0};
    // 0x00324bd0
    enter(ctx, 41);  // entry check point + this block's cycles
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
    s3 = a0;
    s6 = 0x960000;
    s6 = addiu(s6, 376);  // &0x960178
    a0 = 144;
    a1 = 0x40000;
    lw(v0, s6, 0);  // 0x960178
    jalr(ctx, 0x324C14u, v0.u());
    s2 = v0;
    a0 = s2;
    a1 = 0;
    a2 = 144;
    jal(ctx, 0x324C2Cu, gen::fn_memset_00521408);
    sw(zero, s2, 128);
    sw(zero, s2, 132);
    a0 = s2;
    jal(ctx, 0x324C40u, gen::fn_sub_324B50_00324b50);
    lq(v0, s3, 0);
    sq(v0, s2, 0);
    lq(v0, s3, 0);
    sq(v0, s2, 16);
    lwc1(f0, s3, 116);
    swc1(f0, s2, 116);
    lw(v0, s3, 104);
    sw(v0, s2, 104);
    lw(s4, s3, 140);
    if (s4 == 0) {
        // 0x00324eb0
        charge(ctx, 8);
        lw(v0, s3, 128);
        sq(v0, sp, 0xF0);
        lw(v0, s3, 136);
        fp = addu(s3, v0);
        s4 = fp;
        s7 = 0;
        for (;;) {
            // 0x00325210
            charge(ctx, 4);
            lq(v0, sp, 0xF0);
            v0 = slt(s7, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00324ed0
            charge(ctx, 29);
            a0 = 192;
            a1 = 0x40000;
            lw(v0, s6, 0);
            jalr(ctx, 0x324EDCu, v0.u());
            s0 = v0;
            a0 = s0;
            a1 = 0;
            a2 = 192;
            jal(ctx, 0x324EF4u, gen::fn_memset_00521408);
            a0 = s0;
            a1 = 0;
            a2 = 144;
            jal(ctx, 0x324F08u, gen::fn_memset_00521408);
            v0 = 1;
            sw(v0, s0, 132);
            v0 = 8;
            sb(v0, s0, 136);
            sb(zero, s0, 137);
            sb(zero, s0, 138);
            a0 = s0;
            jal(ctx, 0x324F2Cu, gen::fn_sub_324B50_00324b50);
            lw(v1, s4, 152);
            v0 = v1 & 0x1;
            if (v0 != 0) {
                // 0x00325108
                charge(ctx, 41);
                a0 = s2;
                lw(a1, s4, 144);
                jal(ctx, 0x325110u, gen::fn_sub_326200_00326200);
                lw(s5, v0, 144);
                lhu(v0, s5, 4);
                sq(v0, sp, 0xA0);
                a0 = 44;
                a1 = 0x40000;
                lw(v0, s6, 0);
                jalr(ctx, 0x325130u, v0.u());
                s1 = v0;
                a0 = s1;
                a1 = 0;
                a2 = 44;
                jal(ctx, 0x325148u, gen::fn_memset_00521408);
                v0 = 210;
                sw(v0, s1, 0);
                lq(v0, sp, 0xA0);
                sh(v0, s1, 4);
                lhu(v0, s5, 12);
                sh(v0, s1, 12);
                lhu(v0, s5, 28);
                sh(v0, s1, 28);
                lw(a0, s5, 8);
                lhu(v1, s1, 4);
                v0 = sll(v1, 1);
                v0 = addu(v0, v1);
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                v1 = sll(v0, 2);
                v0 = 0x6A0000;
                v0 = addiu(v0, -16864);  // "PF2"
                v0 = addu(v0, v1);
                lw(v0, v0, 20);
                jalr(ctx, 0x32519Cu, v0.u());
                sw(v0, s1, 8);
                sw(s1, s0, 144);
            } else {
                // 0x00324f44
                charge(ctx, 5);
                lw(v0, s4, 144);
                s1 = addu(s3, v0);
                v0 = v1 & 0x2;
                if (v0 == 0) {
                    // 0x00325070
                    charge(ctx, 38);
                    lhu(v0, s1, 4);
                    sq(v0, sp, 0xB0);
                    a0 = 44;
                    a1 = 0x40000;
                    lw(v0, s6, 0);
                    jalr(ctx, 0x325084u, v0.u());
                    s5 = v0;
                    a0 = s5;
                    a1 = 0;
                    a2 = 44;
                    jal(ctx, 0x32509Cu, gen::fn_memset_00521408);
                    v0 = 210;
                    sw(v0, s5, 0);
                    lq(v0, sp, 0xB0);
                    sh(v0, s5, 4);
                    lhu(v0, s1, 12);
                    sh(v0, s5, 12);
                    lhu(v0, s1, 28);
                    sh(v0, s5, 28);
                    a0 = s1;
                    lhu(v1, s5, 4);
                    v0 = sll(v1, 1);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, v1);
                    v1 = sll(v0, 2);
                    v0 = 0x6A0000;
                    v0 = addiu(v0, -16864);  // "PF2"
                    v0 = addu(v0, v1);
                    lw(v0, v0, 0);
                    jalr(ctx, 0x3250F0u, v0.u());
                    sw(v0, s5, 8);
                    sw(s5, s0, 144);
                } else {
                    // 0x00324f58
                    charge(ctx, 14);
                    lw(v1, s4, 148);
                    v0 = sll(v1, 1);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 6);
                    v0 = addu(fp, v0);
                    lw(v0, v0, 144);
                    v1 = addu(s3, v0);
                    v0 = addiu(s1, 36);
                    sq(v0, sp, 0xE0);
                    lw(v0, v1, 36);
                    sw(v0, s1, 36);
                    lw(v0, v1, 40);
                    if (v0 == 0) {
                        // 0x00324f9c
                        charge(ctx, 3);
                        lw(v0, v1, 32);
                        if (v0 == 0) {
                            // 0x00324fb4
                            charge(ctx, 1);
                            v1 = 0;
                        } else {
                            // 0x00324fa8
                            charge(ctx, 3);
                            v1 = addu(v1, v0);
                        }
                    } else {
                        // 0x00324f90
                        charge(ctx, 3);
                        lw(v1, v1, 32);
                    }
                    // 0x00324fb8
                    charge(ctx, 46);
                    v0 = addiu(s1, 32);
                    sq(v0, sp, 0xD0);
                    v0 = subu(v1, s1);
                    sw(v0, s1, 32);
                    lhu(v0, s1, 4);
                    sq(v0, sp, 0xC0);
                    a0 = 44;
                    a1 = 0x40000;
                    lw(v0, s6, 0);
                    jalr(ctx, 0x324FDCu, v0.u());
                    s5 = v0;
                    a0 = s5;
                    a1 = 0;
                    a2 = 44;
                    jal(ctx, 0x324FF4u, gen::fn_memset_00521408);
                    v0 = 210;
                    sw(v0, s5, 0);
                    lq(v0, sp, 0xC0);
                    sh(v0, s5, 4);
                    lhu(v0, s1, 12);
                    sh(v0, s5, 12);
                    lhu(v0, s1, 28);
                    sh(v0, s5, 28);
                    a0 = s1;
                    lhu(v1, s5, 4);
                    v0 = sll(v1, 1);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, v1);
                    v1 = sll(v0, 2);
                    v0 = 0x6A0000;
                    v0 = addiu(v0, -16864);  // "PF2"
                    v0 = addu(v0, v1);
                    lw(v0, v0, 0);
                    jalr(ctx, 0x325048u, v0.u());
                    sw(v0, s5, 8);
                    sw(s5, s0, 144);
                    lq(v0, sp, 0xE0);
                    sw(zero, v0, 0);
                    lq(v0, sp, 0xD0);
                    sw(zero, v0, 0);
                }
            }
            // 0x003251ac
            charge(ctx, 12);
            a0 = s0;
            a1 = s4;
            jal(ctx, 0x3251B4u, gen::fn_sub_326190_00326190);
            a0 = addiu(s0, 156);
            a1 = addiu(s4, 156);
            jal(ctx, 0x3251C4u, gen::fn_strcpy_00524270);
            sw(zero, s0, 172);
            lw(v0, s2, 136);
            if (v0 == 0) {
                // 0x003251f0
                charge(ctx, 2);
                sw(s0, s2, 140);
                sw(zero, s0, 176);
            } else {
                // 0x003251dc
                charge(ctx, 5);
                sw(s0, v0, 172);
                lw(v0, s2, 136);
                sw(v0, s0, 176);
            }
            // 0x003251f8
            charge(ctx, 6);
            sw(s0, s2, 136);
            lw(v0, s2, 128);
            v0 = addiu(v0, 1);
            sw(v0, s2, 128);
            s4 = addiu(s4, 192);
            s7 = addiu(s7, 1);
        }
    } else {
        // 0x00324c74
        charge(ctx, 2);
        for (;;) {
            // 0x00324ea0
            charge(ctx, 2);
            if (s4 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00324c7c
            charge(ctx, 29);
            a0 = 192;
            a1 = 0x40000;
            lw(v0, s6, 0);
            jalr(ctx, 0x324C88u, v0.u());
            s1 = v0;
            a0 = s1;
            a1 = 0;
            a2 = 192;
            jal(ctx, 0x324CA0u, gen::fn_memset_00521408);
            a0 = s1;
            a1 = 0;
            a2 = 144;
            jal(ctx, 0x324CB4u, gen::fn_memset_00521408);
            v0 = 1;
            sw(v0, s1, 132);
            v0 = 8;
            sb(v0, s1, 136);
            sb(zero, s1, 137);
            sb(zero, s1, 138);
            a0 = s1;
            jal(ctx, 0x324CD8u, gen::fn_sub_324B50_00324b50);
            lw(v0, s4, 152);
            v0 = v0 & 0x1;
            if (v0 != 0) {
                // 0x00324d84
                charge(ctx, 47);
                a0 = s3;
                lw(a1, s4, 144);
                jal(ctx, 0x324D8Cu, gen::fn_sub_3261C0_003261c0);
                a0 = s3;
                a1 = v0;
                jal(ctx, 0x324D9Cu, gen::fn_sub_326240_00326240);
                a0 = s2;
                a1 = v0;
                jal(ctx, 0x324DACu, gen::fn_sub_326200_00326200);
                lw(s5, v0, 144);
                lhu(s7, s5, 4);
                a0 = 44;
                a1 = 0x40000;
                lw(v0, s6, 0);
                jalr(ctx, 0x324DC8u, v0.u());
                s0 = v0;
                a0 = s0;
                a1 = 0;
                a2 = 44;
                jal(ctx, 0x324DE0u, gen::fn_memset_00521408);
                v0 = 210;
                sw(v0, s0, 0);
                sh(s7, s0, 4);
                lhu(v0, s5, 12);
                sh(v0, s0, 12);
                lhu(v0, s5, 28);
                sh(v0, s0, 28);
                lw(a0, s5, 8);
                lhu(v1, s0, 4);
                v0 = sll(v1, 1);
                v0 = addu(v0, v1);
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                v1 = sll(v0, 2);
                v0 = 0x6A0000;
                v0 = addiu(v0, -16864);  // "PF2"
                v0 = addu(v0, v1);
                lw(v0, v0, 20);
                jalr(ctx, 0x324E30u, v0.u());
                sw(v0, s0, 8);
                sw(s0, s1, 144);
            } else {
                // 0x00324cf0
                charge(ctx, 37);
                lw(s5, s4, 144);
                lhu(s7, s5, 4);
                a0 = 44;
                a1 = 0x40000;
                lw(v0, s6, 0);
                jalr(ctx, 0x324D04u, v0.u());
                s0 = v0;
                a0 = s0;
                a1 = 0;
                a2 = 44;
                jal(ctx, 0x324D1Cu, gen::fn_memset_00521408);
                v0 = 210;
                sw(v0, s0, 0);
                sh(s7, s0, 4);
                lhu(v0, s5, 12);
                sh(v0, s0, 12);
                lhu(v0, s5, 28);
                sh(v0, s0, 28);
                a0 = s5;
                lhu(v1, s0, 4);
                v0 = sll(v1, 1);
                v0 = addu(v0, v1);
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                v1 = sll(v0, 2);
                v0 = 0x6A0000;
                v0 = addiu(v0, -16864);  // "PF2"
                v0 = addu(v0, v1);
                lw(v0, v0, 0);
                jalr(ctx, 0x324D6Cu, v0.u());
                sw(v0, s0, 8);
                sw(s0, s1, 144);
            }
            // 0x00324e40
            charge(ctx, 12);
            a0 = s1;
            a1 = s4;
            jal(ctx, 0x324E48u, gen::fn_sub_326190_00326190);
            a0 = addiu(s1, 156);
            a1 = addiu(s4, 156);
            jal(ctx, 0x324E58u, gen::fn_strcpy_00524270);
            sw(zero, s1, 172);
            lw(v0, s2, 136);
            if (v0 == 0) {
                // 0x00324e84
                charge(ctx, 2);
                sw(s1, s2, 140);
                sw(zero, s1, 176);
            } else {
                // 0x00324e70
                charge(ctx, 5);
                sw(s1, v0, 172);
                lw(v0, s2, 136);
                sw(v0, s1, 176);
            }
            // 0x00324e8c
            charge(ctx, 5);
            sw(s1, s2, 136);
            lw(v0, s2, 128);
            v0 = addiu(v0, 1);
            sw(v0, s2, 128);
            lw(s4, s4, 172);
        }
        // 0x00324ea8
        charge(ctx, 2);
    }
    // 0x00325220
    charge(ctx, 32);
    a1 = addiu(sp, 0x100);
    sqc2(vf0, a1, 0);
    a0 = s2;
    jal(ctx, 0x32522Cu, gen::fn_sub_325C10_00325c10);
    a0 = s2;
    a1 = addiu(sp, 0x100);
    jal(ctx, 0x32523Cu, gen::fn_sub_325D60_00325d60);
    v0 = 0x3F800000;
    mtc1(v0, f12);
    a0 = s2;
    jal(ctx, 0x325250u, gen::fn_sub_325E40_00325e40);
    a0 = s2;
    a1 = si(-1);
    jal(ctx, 0x325260u, gen::fn_sub_326030_00326030);
    v0 = s2;
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
}

// 0x003252A0 sub_3252A0 -- 600 bytes; frame 0x90: ra sp+0x40, s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// Effect-instance tick: walks the instance's parts and calls their per-type hooks (off_69BE20) with sub_3263B0 /
// sub_325D60 / sub_326280, the frame step from dword_820280.
void sub_3252A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f20{ctx, 20}, f21{ctx, 21};
    Vf vf0{ctx, 0}, vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11};
    // 0x003252a0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s2 = a0;
    lqc2(vf10, s2, 64);
    lqc2(vf11, s2, 0);
    vadd(0xF, vf10, vf10, vf11);  // vadd.xyzw
    a1 = addiu(sp, 0x80);
    sqc2(vf10, a1, 0);
    lw(v1, a0, 104);
    v1 = v1 & 0x60;
    if (v1 != 0) {
        // 0x003252e4
        charge(ctx, 13);
        v1 = addiu(sp, 0x50);
        lq(v0, s2, 80);
        sq(v0, v1, 0);
        a2 = addiu(sp, 0x60);
        jal(ctx, 0x3252F4u, gen::fn_sub_3263B0_003263b0);
        a0 = s2;
        a1 = addiu(sp, 0x60);
        jal(ctx, 0x325304u, gen::fn_sub_325D60_00325d60);
        v0 = addiu(sp, 0x50);
        lq(v0, v0, 0);
        sq(v0, s2, 80);
    }
    // 0x00325318
    charge(ctx, 6);
    lw(s0, s2, 132);
    lw(s1, s2, 140);
    v1 = 0x40A00000;
    mtc1(v1, f20);
    for (;;) {
        // 0x003254b0
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00325330
        charge(ctx, 4);
        lw(v1, s1, 128);
        v1 = slt(s0, v1);
        if (v1 == 0) {
            // 0x00325340
            charge(ctx, 4);
            lw(v1, s1, 132);
            v1 = v1 & 0x2;
            if (v1 == 0) {
                // 0x00325350
                charge(ctx, 4);
                lw(v0, s1, 104);
                v0 = v0 & 0x18;
                if (v0 != 0) {
                    // 0x00325360
                    charge(ctx, 11);
                    a0 = s1;
                    a1 = addiu(sp, 0x80);
                    a2 = addiu(sp, 0x70);
                    jal(ctx, 0x32536Cu, gen::fn_sub_326280_00326280);
                    v0 = addiu(sp, 0x80);
                    lqc2(vf10, v0, 0);
                    lw(v1, s1, 104);
                    v0 = v1 & 0x4;
                    if (v0 != 0) {
                        // 0x0032538c
                        charge(ctx, 4);
                        mfc1(v0, f20);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vadd_bc(0x4, vf10, vf0, vf2, 0);  // vaddx.y
                    }
                    // 0x0032539c
                    charge(ctx, 5);
                    v0 = addiu(sp, 0x70);
                    lqc2(vf11, v0, 0);
                    v0 = v1 & 0x80;
                    if (v0 != 0) {
                        // 0x003253b0
                        charge(ctx, 4);
                        mfc1(v0, f21);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vmul_bc(0xF, vf11, vf11, vf2, 0);  // vmulx.xyzw
                    }
                    // 0x003253c0
                    charge(ctx, 16);
                    vadd(0xF, vf10, vf10, vf11);  // vadd.xyzw
                    a1 = addiu(sp, 0x70);
                    sqc2(vf10, a1, 0);
                    lw(a0, s1, 144);
                    lhu(v1, a0, 4);
                    v0 = sll(v1, 1);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, v1);
                    v1 = sll(v0, 2);
                    v0 = 0x6A0000;
                    v0 = addiu(v0, -16864);  // "PF2"
                    v0 = addu(v0, v1);
                    lw(v0, v0, 32);
                    if (v0 != 0) {
                        // 0x00325400
                        charge(ctx, 3);
                        lw(a0, a0, 8);
                        jalr(ctx, 0x325404u, v0.u());
                    }
                }
                // 0x0032540c
                charge(ctx, 4);
                lw(v0, s1, 104);
                v0 = v0 & 0x60;
                if (v0 != 0) {
                    // 0x0032541c
                    charge(ctx, 18);
                    a0 = s1;
                    a1 = addiu(sp, 0x80);
                    a2 = addiu(sp, 0x60);
                    jal(ctx, 0x325428u, gen::fn_sub_3263B0_003263b0);
                    lw(a0, s1, 144);
                    lhu(v1, a0, 4);
                    v0 = sll(v1, 1);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, v1);
                    v1 = sll(v0, 2);
                    v0 = 0x6A0000;
                    v0 = addiu(v0, -16864);  // "PF2"
                    v0 = addu(v0, v1);
                    lw(v0, v0, 36);
                    if (v0 != 0) {
                        // 0x00325464
                        charge(ctx, 4);
                        lw(a0, a0, 8);
                        a1 = addiu(sp, 0x60);
                        jalr(ctx, 0x32546Cu, v0.u());
                    }
                }
                // 0x00325474
                charge(ctx, 14);
                lw(v0, s1, 144);
                lw(a0, v0, 8);
                lhu(v1, v0, 4);
                v0 = sll(v1, 1);
                v0 = addu(v0, v1);
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                v1 = sll(v0, 2);
                v0 = 0x6A0000;
                v0 = addiu(v0, -16864);  // "PF2"
                v0 = addu(v0, v1);
                lw(v0, v0, 8);
                jalr(ctx, 0x3254A4u, v0.u());
            }
        }
        // 0x003254ac
        charge(ctx, 1);
        lw(s1, s1, 172);
    }
    // 0x003254b8
    charge(ctx, 16);
    lw(a0, s2, 104);
    v1 = lui(0x8000);
    v1 = a0 | v1;
    sw(v1, s2, 104);
    lw(v1, s2, 132);
    v1 = addiu(v1, 1);
    sw(v1, s2, 132);
    ld(ra, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x00325920 sub_325920 -- 604 bytes; frame 0x80: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Effect-instance (re)initialisation: zeroes the node (memset), sub_324B50, then the parts through sub_326190 /
// sub_325C10 / sub_325D60 / sub_325E40 / sub_326030 and the off_69BE20 hooks.
void sub_325920(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    Vf vf0{ctx, 0};
    // 0x00325920
    enter(ctx, 38);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    v0 = 0x960000;
    v0 = addiu(v0, 376);  // &0x960178
    a0 = 144;
    a1 = 0x40000;
    lw(v0, v0, 0);  // 0x960178
    jalr(ctx, 0x325958u, v0.u());
    s2 = v0;
    a0 = s2;
    a1 = 0;
    a2 = 144;
    jal(ctx, 0x325970u, gen::fn_memset_00521408);
    sw(zero, s2, 128);
    sw(zero, s2, 132);
    a0 = s2;
    jal(ctx, 0x325984u, gen::fn_sub_324B50_00324b50);
    lq(v0, s0, 0);
    sq(v0, s2, 0);
    lq(v0, s0, 16);
    sq(v0, s2, 16);
    lwc1(f0, s0, 116);
    swc1(f0, s2, 116);
    lw(v0, s0, 104);
    sw(v0, s2, 104);
    lw(s1, s0, 140);
    for (;;) {
        // 0x00325b00
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003259b8
        charge(ctx, 70);
        s5 = 0x960000;
        s5 = addiu(s5, 376);  // &0x960178
        a0 = 192;
        a1 = 0x40000;
        lw(v0, s5, 0);  // 0x960178
        jalr(ctx, 0x3259CCu, v0.u());
        s0 = v0;
        a0 = s0;
        a1 = 0;
        a2 = 192;
        jal(ctx, 0x3259E4u, gen::fn_memset_00521408);
        a0 = s0;
        a1 = 0;
        a2 = 144;
        jal(ctx, 0x3259F8u, gen::fn_memset_00521408);
        v0 = 1;
        sw(v0, s0, 132);
        v0 = 8;
        sb(v0, s0, 136);
        sb(zero, s0, 137);
        sb(zero, s0, 138);
        a0 = s0;
        jal(ctx, 0x325A1Cu, gen::fn_sub_324B50_00324b50);
        lw(s4, s1, 144);
        lhu(s3, s4, 4);
        a0 = 44;
        a1 = 0x40000;
        lw(v0, s5, 0);  // 0x960178
        jalr(ctx, 0x325A38u, v0.u());
        s5 = v0;
        a0 = s5;
        a1 = 0;
        a2 = 44;
        jal(ctx, 0x325A50u, gen::fn_memset_00521408);
        v0 = 210;
        sw(v0, s5, 0);
        sh(s3, s5, 4);
        lhu(v0, s4, 12);
        sh(v0, s5, 12);
        lhu(v0, s4, 28);
        sh(v0, s5, 28);
        lw(a0, s4, 8);
        lhu(v1, s5, 4);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        v1 = sll(v0, 2);
        v0 = 0x6A0000;
        v0 = addiu(v0, -16864);  // "PF2"
        v0 = addu(v0, v1);
        lw(v0, v0, 20);
        jalr(ctx, 0x325AA0u, v0.u());
        sw(v0, s5, 8);
        sw(s5, s0, 144);
        a0 = s0;
        a1 = s1;
        jal(ctx, 0x325AB8u, gen::fn_sub_326190_00326190);
        sw(zero, s0, 172);
        lw(v0, s2, 136);
        if (v0 == 0) {
            // 0x00325ae4
            charge(ctx, 2);
            sw(s0, s2, 140);
            sw(zero, s0, 176);
        } else {
            // 0x00325ad0
            charge(ctx, 5);
            sw(s0, v0, 172);
            lw(v0, s2, 136);
            sw(v0, s0, 176);
        }
        // 0x00325aec
        charge(ctx, 5);
        sw(s0, s2, 136);
        lw(v0, s2, 128);
        v0 = addiu(v0, 1);
        sw(v0, s2, 128);
        lw(s1, s1, 172);
    }
    // 0x00325b08
    charge(ctx, 29);
    a1 = addiu(sp, 0x70);
    sqc2(vf0, a1, 0);
    a0 = s2;
    jal(ctx, 0x325B14u, gen::fn_sub_325C10_00325c10);
    a0 = s2;
    a1 = addiu(sp, 0x70);
    jal(ctx, 0x325B24u, gen::fn_sub_325D60_00325d60);
    v0 = 0x3F800000;
    mtc1(v0, f12);
    a0 = s2;
    jal(ctx, 0x325B38u, gen::fn_sub_325E40_00325e40);
    a0 = s2;
    a1 = si(-1);
    jal(ctx, 0x325B48u, gen::fn_sub_326030_00326030);
    v0 = s2;
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x00329BA0 sub_329BA0 -- 444 bytes; frame 0x70: ra sp+0x10, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// Effect billboard setup: reads the current camera (sub_198590) and builds a facing matrix (sub_4C6BE0) from the axis
// constants at xmmword_69C4D0.
void sub_329BA0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    Vf vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11};
    // 0x00329ba0
    enter(ctx, 57);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x10);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    mov_s(f20, f12);
    v0 = addiu(sp, 0x30);
    sqc2(vf10, v0, 0);
    v0 = 0x6A0000;
    v0 = addiu(v0, -15152);  // &0x69C4D0
    sqc2(vf10, v0, 0);  // 0x69C4D0
    v0 = 0x6A0000;
    lwc1(f0, v0, -15152);  // 0x69C4D0
    swc1(f0, sp, 0x50);
    v0 = 0x6A0000;
    lwc1(f0, v0, -15148);  // 0x69C4D4
    swc1(f0, sp, 0x54);
    v0 = 0x6A0000;
    lwc1(f0, v0, -15144);  // 0x69C4D8
    swc1(f0, sp, 0x58);
    jal(ctx, 0x329BF0u, gen::fn_sub_198590_00198590);
    a2 = addiu(v0, 32);
    a0 = addiu(sp, 0x60);
    a1 = addiu(sp, 0x50);
    jal(ctx, 0x329C04u, gen::fn_sub_4C6BE0_004c6be0);
    lwc1(f22, sp, 0x68);
    lwc1(f0, sp, 0x60);
    div_s(f1, f0, f22);
    v0 = 0x44200000;
    mtc1(v0, f0);
    mul_s(f0, f0, f1);
    swc1(f0, sp, 0x20);
    lwc1(f0, sp, 0x64);
    div_s(f1, f0, f22);
    v0 = 0x43E00000;
    mtc1(v0, f0);
    mul_s(f0, f0, f1);
    swc1(f0, sp, 0x24);
    sw(zero, sp, 0x28);
    sw(zero, sp, 0x2C);
    v0 = addiu(sp, 0x20);
    lqc2(vf10, v0, 0);
    v0 = addiu(sp, 0x40);
    sqc2(vf10, v0, 0);
    jal(ctx, 0x329C60u, gen::fn_sub_198590_00198590);
    lwc1(f21, v0, 128);
    jal(ctx, 0x329C6Cu, gen::fn_sub_198590_00198590);
    lwc1(f0, v0, 132);
    c_le_s(f22, f21);
    if (!cond(ctx)) {
        // 0x00329c84
        charge(ctx, 3);
        c_lt_s(f22, f0);
        if (!cond(ctx)) {
            goto L_00329c90;
        }
        // 0x00329c9c
        charge(ctx, 40);
        jal(ctx, 0x329C9Cu, gen::fn_sub_198590_00198590);
        lw(v1, v0, 4);
        v0 = addiu(sp, 0x30);
        lqc2(vf10, v0, 0);
        lwc1(f0, v1, 64);
        v0 = 0x6A0000;
        swc1(f0, v0, -15152);  // 0x69C4D0
        lwc1(f0, v1, 68);
        v0 = 0x6A0000;
        swc1(f0, v0, -15148);  // 0x69C4D4
        lwc1(f0, v1, 72);
        v0 = 0x6A0000;
        swc1(f0, v0, -15144);  // 0x69C4D8
        v0 = 0x6A0000;
        v0 = addiu(v0, -15152);  // &0x69C4D0
        lqc2(vf11, v0, 0);  // 0x69C4D0
        vsub(0xF, vf10, vf10, vf11);  // vsub.xyzw
        vmul(0xE, vf2, vf10, vf10);  // vmul.xyz
        vadd_bc(0x8, vf2, vf2, vf2, 1);  // vaddy.x
        vadd_bc(0x8, vf2, vf2, vf2, 2);  // vaddz.x
        vsqrt(vf2, 0);  // vsqrt
        vwaitq(ctx);
        cfc2(v0, 22, false);  // cfc2
        mtc1(v0, f1);
        v0 = addiu(sp, 0x40);
        lqc2(vf10, v0, 0);
        v0 = 650;
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        mul_s(f0, f0, f20);
        div_s(f0, f0, f1);
        v0 = 1500;
        mtc1(v0, f1);
        cvt_s_w(f1, f1);
        c_le_s(f0, f1);
        if (!cond(ctx)) {
            // 0x00329d3c
            charge(ctx, 1);
            mov_s(f0, f1);
        }
        // 0x00329d40 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(ra, sp, 0x10);
        lwc1(f22, sp, 0x8);
        lwc1(f21, sp, 0x4);
        lwc1(f20, sp, 0x0);
        sp = addiu(sp, 0x70);
        return;
    }
L_00329c90:
    charge(ctx, 3);
    mtc1(zero, f0);
    // 0x00329d40 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x10);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x0032A770 sub_32A770 -- 276 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Effect key evaluation: +20 = sub_32A120 (position track), +24 = sub_32A540 (scale track); rotation +28 = atan2f of
// the projected direction for mode 2 (byte +156), else sub_32A540 on the rotation track.
void sub_32A770(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13};
    Vf vf10{ctx, 10}, vf11{ctx, 11};
    // 0x0032a770
    enter(ctx, 26);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s3 = a1;
    s2 = a2;
    s1 = a3;
    lw(a3, a1, 184);
    a0 = addiu(s3, 44);
    a1 = addiu(s3, 80);
    jal(ctx, 0x32A7A4u, gen::fn_sub_32A120_0032a120);
    sw(v0, s0, 20);
    lw(a2, s3, 184);
    a0 = addiu(s3, 96);
    a1 = s2;
    jal(ctx, 0x32A7BCu, gen::fn_sub_32A540_0032a540);
    swc1(f0, s0, 24);
    lbu(v1, s3, 156);
    v0 = 2;
    if (v1 == v0) {
        // 0x0032a7f8
        charge(ctx, 16);
        lqc2(vf10, s0, 0);
        jal(ctx, 0x32A7FCu, gen::fn_sub_3299B0_003299b0);
        vmove(0xF, vf11, vf10);  // vmove.xyzw
        lqc2(vf10, s1, 0);
        jal(ctx, 0x32A80Cu, gen::fn_sub_3299B0_003299b0);
        vsub(0xF, vf10, vf10, vf11);  // vsub.xyzw
        v1 = addiu(sp, 0x50);
        sqc2(vf10, v1, 0);
        lwc1(f13, sp, 0x50);
        mtc1(zero, f1);
        c_eq_s(f1, f13);
        if (cond(ctx)) {
            // 0x0032a838
            charge(ctx, 4);
            lwc1(f0, sp, 0x54);
            c_eq_s(f1, f0);
            if (!cond(ctx)) {
                goto L_0032a848;
            }
            // 0x0032a860
            charge(ctx, 1);
            swc1(f1, s0, 28);
            // 0x0032a864 (the shared epilogue, written out on this path)
            charge(ctx, 8);
            ld(ra, sp, 0x40);
            lq(s3, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x60);
            return;
        }
    L_0032a848:
        charge(ctx, 6);
        lwc1(f12, sp, 0x54);
        jal(ctx, 0x32A84Cu, gen::fn_atan2f_0052ea18);
        swc1(f0, s0, 28);
    } else {
        // 0x0032a7d8
        charge(ctx, 8);
        lw(a2, s3, 184);
        a0 = addiu(s3, 140);
        a1 = s2;
        jal(ctx, 0x32A7E4u, gen::fn_sub_32A540_0032a540);
        swc1(f0, s0, 28);
    }
    // 0x0032a864 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x0032A890 sub_32A890 -- 1692 bytes; frame 0x150: ra sp+0xB0, fp sp+0xA0 (sq), s7 sp+0x90 (sq), s6 sp+0x80 (sq), s5 sp+0x70 (sq), s4 sp+0x60 (sq), s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f26 sp+0x18, f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// Effect particle emitter update: copies the template (memcpy) and steps each particle through sub_329D60 (a large
// unrolled body with VU0 macro ops).
void sub_32A890(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25}, f26{ctx, 26};
    Vf vf0{ctx, 0}, vf2{ctx, 2}, vf3{ctx, 3}, vf10{ctx, 10}, vf11{ctx, 11};
    // 0x0032a890
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x150);
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
    s5 = a1;
    lw(v1, a0, 32);
    lw(s4, v1, 196);
    lw(s7, v1, 192);
    mult(s3, s7, s4);
    if (s3 != 0) {
        // 0x0032a8f4
        charge(ctx, 11);
        lw(s2, s5, 16);
        lw(a2, a0, 24);
        v0 = subu(s5, a2);
        v0 = srl(v0, 5);
        mult(v1, v0, s3);
        lw(v0, a0, 4);
        v0 = addu(v0, v1);
        v0 = sll(v0, 5);
        s0 = addu(a2, v0);
        if (s2 != 0) {
            // 0x0032a968
            charge(ctx, 6);
            v0 = addiu(s2, -1);
            sw(v0, s0, 16);
            v0 = 0x3F800000;
            mtc1(v0, f20);
            if (i64(s3) < 0) {
                // 0x0032a994
                charge(ctx, 7);
                v1 = srl(s3, 1);
                v0 = s3 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f0, f0);
            } else {
                // 0x0032a980
                charge(ctx, 5);
                mtc1(s3, f0);
                cvt_s_w(f0, f0);
            }
            // 0x0032a9b0
            charge(ctx, 8);
            div_s(f22, f20, f0);
            mtc1(zero, f23);
            lw(v0, s5, 20);
            v0 = srl(v0, 24);
            if (i64(v0) < 0) {
                // 0x0032a9e4
                charge(ctx, 7);
                v1 = srl(v0, 1);
                v0 = v0 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f0);
                cvt_s_w(f21, f0);
                add_s(f21, f21, f21);
            } else {
                // 0x0032a9d0
                charge(ctx, 5);
                mtc1(v0, f0);
                cvt_s_w(f21, f0);
            }
            // 0x0032aa00
            charge(ctx, 10);
            v0 = subu(s3, s4);
            sq(v0, sp, 0xC0);
            v0 = sll(s3, 5);
            v0 = addu(s0, v0);
            s3 = addiu(v0, -32);
            fp = sll(s4, 5);
            s1 = subu(s3, fp);
            s6 = 0;
            for (;;) {
                // 0x0032aaa4
                charge(ctx, 4);
                lq(v0, sp, 0xC0);
                v0 = sltu(s6, v0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0032aa28
                charge(ctx, 15);
                a0 = s3;
                a1 = s1;
                a2 = 32;
                jal(ctx, 0x32AA34u, gen::fn_memcpy_00521250);
                lw(v0, s1, 20);
                a0 = dsll32(v0, 8);
                a0 = dsrl32(a0, 8);
                mul_s(f1, f21, f23);
                v0 = 0x4F000000;
                mtc1(v0, f0);
                c_le_s(f0, f1);
                if (cond(ctx)) {
                    // 0x0032aa74
                    charge(ctx, 5);
                    sub_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    v0 = lui(0x8000);
                    v1 = v1 | v0;
                } else {
                    // 0x0032aa64
                    charge(ctx, 4);
                    cvt_w_s(f0, f1);
                    mfc1(v1, f0);
                }
                // 0x0032aa88
                charge(ctx, 7);
                v0 = sll(v1, 24);
                v0 = a0 | v0;
                sw(v0, s3, 20);
                add_s(f23, f23, f22);
                s3 = addiu(s3, -32);
                s1 = addiu(s1, -32);
                s6 = addiu(s6, 1);
            }
            // 0x0032aab4
            charge(ctx, 10);
            a0 = s0;
            a1 = s5;
            a2 = 32;
            jal(ctx, 0x32AAC0u, gen::fn_memcpy_00521250);
            v1 = si(-1);
            sw(v1, s0, 16);
            v1 = 1;
            if (s4 != v1) {
                // 0x0032aadc
                charge(ctx, 3);
                at = sltiu(s7, 2);
                if (at != 0) {
                    goto L_0032aae8;
                }
                // 0x0032aaf0
                charge(ctx, 3);
                v1 = slti(s2, 2);
                if (v1 == 0) {
                    // 0x0032aafc
                    charge(ctx, 3);
                    v1 = sltiu(s7, 3);
                    if (v1 != 0) {
                        goto L_0032ad0c;
                    }
                    // 0x0032ab08
                    charge(ctx, 5);
                    v1 = sll(s4, 6);
                    a0 = addu(v1, s0);
                    lw(v1, a0, 16);
                    if (i64(v1) >= 0) {
                        // 0x0032ab1c
                        charge(ctx, 19);
                        v1 = addiu(sp, 0xF0);
                        lq(v0, a0, 0);
                        sq(v0, v1, 0);
                        v1 = addiu(sp, 0x100);
                        v0 = sll(s4, 5);
                        a0 = addu(s0, v0);
                        lq(v0, a0, 0);
                        sq(v0, v1, 0);
                        v1 = addiu(sp, 0x110);
                        lq(v0, s0, 0);
                        sq(v0, v1, 0);
                        v1 = addiu(sp, 0x120);
                        lq(v0, s0, 0);
                        sq(v0, v1, 0);
                        s1 = addiu(a0, -32);
                        mtc1(zero, f21);
                        v0 = addiu(s4, 1);
                        if (i64(v0) < 0) {
                            // 0x0032ab7c
                            charge(ctx, 7);
                            v1 = srl(v0, 1);
                            v0 = v0 & 0x1;
                            v1 = v1 | v0;
                            mtc1(v1, f0);
                            cvt_s_w(f0, f0);
                            add_s(f0, f0, f0);
                        } else {
                            // 0x0032ab68
                            charge(ctx, 5);
                            mtc1(v0, f0);
                            cvt_s_w(f0, f0);
                        }
                        // 0x0032ab98
                        charge(ctx, 53);
                        div_s(f22, f20, f0);
                        lwc1(f20, a0, 24);
                        lwc1(f0, s0, 24);
                        sub_s(f26, f0, f20);
                        lwc1(f25, a0, 28);
                        lwc1(f0, s0, 28);
                        sub_s(f24, f0, f25);
                        lw(v0, s0, 20);
                        sw(v0, sp, 0x14C);
                        v0 = addiu(sp, 0x14C);
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
                        lw(v0, a0, 20);
                        sw(v0, sp, 0x148);
                        v0 = addiu(sp, 0x148);
                        lw(v0, v0, 0);
                        pextlb(v0, zero, v0);
                        pextlh(v0, zero, v0);
                        qmtc2(v0, vf10, false);  // qmtc2
                        vitof0(0xF, vf10, vf10);  // vitof0.xyzw
                        mfc1(v1, f0);
                        qmtc2(v1, vf2, false);  // qmtc2
                        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                        v1 = addiu(sp, 0xE0);
                        sqc2(vf10, v1, 0);
                        vsub(0xF, vf11, vf11, vf10);  // vsub.xyzw
                        vadd_bc(0xE, vf10, vf0, vf0, 3);  // vaddw.xyz
                        vmul_bc(0x1, vf10, vf0, vf0, 0);  // vmulx.w
                        mfc1(v1, f22);
                        qmtc2(v1, vf2, false);  // qmtc2
                        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                        vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
                        v1 = addiu(sp, 0xD0);
                        sqc2(vf10, v1, 0);
                        s3 = 0;
                        v1 = 0x437F0000;
                        mtc1(v1, f23);
                        s0 = si(-1);
                        for (;;) {
                            // 0x0032acf4
                            charge(ctx, 4);
                            v1 = addu(s4, s0);
                            v1 = sltu(s3, v1);
                            if (v1 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x0032ac6c
                            charge(ctx, 34);
                            add_s(f21, f21, f22);
                            a0 = addiu(sp, 0xF0);
                            mov_s(f12, f21);
                            jal(ctx, 0x32AC78u, gen::fn_sub_329D60_00329d60);
                            sqc2(vf10, s1, 0);
                            mtc1(zero, f0);
                            adda_s(f0, f20);
                            madd_s(f1, f26, f21);
                            swc1(f1, s1, 24);
                            adda_s(f0, f25);
                            madd_s(f0, f24, f21);
                            swc1(f0, s1, 28);
                            a0 = addiu(sp, 0xE0);
                            lqc2(vf10, a0, 0);
                            v1 = addiu(sp, 0xD0);
                            lqc2(vf11, v1, 0);
                            vadd(0xF, vf10, vf10, vf11);  // vadd.xyzw
                            sqc2(vf10, a0, 0);
                            mfc1(v1, f23);
                            qmtc2(v1, vf2, false);  // qmtc2
                            vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                            vftoi0(0xF, vf10, vf10);  // vftoi0.xyzw
                            qmfc2(v1, vf10, false);  // qmfc2
                            ppach(v1, zero, v1);
                            ppacb(v1, zero, v1);
                            sw(v1, sp, 0x144);
                            lw(v1, sp, 0x144);
                            sw(v1, s1, 20);
                            sw(s2, s1, 16);
                            s1 = addiu(s1, -32);
                            s3 = addiu(s3, 1);
                        }
                        // 0x0032ad04
                        charge(ctx, 2);
                    }
                    // 0x0032aedc (the shared epilogue, written out on this path)
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
                    sp = addiu(sp, 0x150);
                    return;
                }
            L_0032ad0c:
                charge(ctx, 2);
                if (i64(s2) > 0) {
                    // 0x0032ad14
                    charge(ctx, 4);
                    a3 = addu(fp, s0);
                    lw(v1, a3, 16);
                    if (i64(v1) >= 0) {
                        // 0x0032ad24
                        charge(ctx, 5);
                        s1 = addiu(a3, -32);
                        mtc1(zero, f6);
                        v0 = addiu(s4, 1);
                        if (i64(v0) < 0) {
                            // 0x0032ad4c
                            charge(ctx, 7);
                            v1 = srl(v0, 1);
                            v0 = v0 & 0x1;
                            v1 = v1 | v0;
                            mtc1(v1, f0);
                            cvt_s_w(f1, f0);
                            add_s(f1, f1, f1);
                        } else {
                            // 0x0032ad38
                            charge(ctx, 5);
                            mtc1(v0, f0);
                            cvt_s_w(f1, f0);
                        }
                        // 0x0032ad68
                        charge(ctx, 58);
                        v0 = 0x3F800000;
                        mtc1(v0, f0);
                        div_s(f7, f0, f1);
                        lwc1(f5, a3, 24);
                        lwc1(f0, s0, 24);
                        sub_s(f4, f0, f5);
                        lwc1(f3, a3, 28);
                        lwc1(f0, s0, 28);
                        sub_s(f2, f0, f3);
                        lw(v0, s0, 20);
                        sw(v0, sp, 0x140);
                        v0 = addiu(sp, 0x140);
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
                        lw(v0, a3, 20);
                        sw(v0, sp, 0x13C);
                        v0 = addiu(sp, 0x13C);
                        lw(v0, v0, 0);
                        pextlb(v0, zero, v0);
                        pextlh(v0, zero, v0);
                        qmtc2(v0, vf10, false);  // qmtc2
                        vitof0(0xF, vf10, vf10);  // vitof0.xyzw
                        mfc1(v1, f0);
                        qmtc2(v1, vf2, false);  // qmtc2
                        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                        a2 = addiu(sp, 0xE0);
                        sqc2(vf10, a2, 0);
                        vsub(0xF, vf11, vf11, vf10);  // vsub.xyzw
                        vadd_bc(0xE, vf10, vf0, vf0, 3);  // vaddw.xyz
                        vmul_bc(0x1, vf10, vf0, vf0, 0);  // vmulx.w
                        mfc1(v1, f7);
                        qmtc2(v1, vf2, false);  // qmtc2
                        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                        vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
                        a1 = addiu(sp, 0xD0);
                        sqc2(vf10, a1, 0);
                        t0 = 0;
                        v1 = 0x437F0000;
                        mtc1(v1, f0);
                        v1 = si(-1);
                        mtc1(zero, f1);
                        mfc1(t1, f0);
                        a0 = addu(s4, v1);
                        for (;;) {
                            // 0x0032aed0
                            charge(ctx, 3);
                            v1 = sltu(t0, a0);
                            if (v1 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x0032ae50
                            charge(ctx, 32);
                            add_s(f6, f6, f7);
                            lqc2(vf10, a3, 0);
                            lqc2(vf11, s0, 0);
                            mfc1(v1, f6);
                            qmtc2(v1, vf2, false);  // qmtc2
                            vsub_bc(0x1, vf3, vf0, vf2, 0);  // vsubx.w
                            vmula_bc(0xF, vf11, vf2, 0);  // vmulax.xyzw
                            vmadd_bc(0xF, vf10, vf10, vf3, 3);  // vmaddw.xyzw
                            sqc2(vf10, s1, 0);
                            adda_s(f1, f5);
                            madd_s(f0, f4, f6);
                            swc1(f0, s1, 24);
                            adda_s(f1, f3);
                            madd_s(f0, f2, f6);
                            swc1(f0, s1, 28);
                            lqc2(vf10, a2, 0);
                            lqc2(vf11, a1, 0);
                            vadd(0xF, vf10, vf10, vf11);  // vadd.xyzw
                            sqc2(vf10, a2, 0);
                            qmtc2(t1, vf2, false);  // qmtc2
                            vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                            vftoi0(0xF, vf10, vf10);  // vftoi0.xyzw
                            qmfc2(v1, vf10, false);  // qmfc2
                            ppach(v1, zero, v1);
                            ppacb(v1, zero, v1);
                            sw(v1, sp, 0x138);
                            lw(v1, sp, 0x138);
                            sw(v1, s1, 20);
                            sw(s2, s1, 16);
                            s1 = addiu(s1, -32);
                            t0 = addiu(t0, 1);
                        }
                    }
                }
                // 0x0032aedc (the shared epilogue, written out on this path)
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
                sp = addiu(sp, 0x150);
                return;
            }
        L_0032aae8:
            charge(ctx, 2);
        } else {
            // 0x0032a920
            charge(ctx, 9);
            a0 = s0;
            a2 = 32;
            jal(ctx, 0x32A928u, gen::fn_memcpy_00521250);
            s1 = s0;
            a1 = 0;
            a0 = si(-1);
            for (;;) {
                // 0x0032a950
                charge(ctx, 4);
                v1 = sltu(a1, s3);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0032a944
                charge(ctx, 3);
                sw(a0, s1, 16);
                s1 = addiu(s1, 32);
                a1 = addiu(a1, 1);
            }
            // 0x0032a960
            charge(ctx, 2);
        }
    }
    // 0x0032aedc (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0x150);
}

// 0x00358A30 sub_358A30 -- 1756 bytes; frame 0x1A0: ra sp+0x60, s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// Screen-space 2D overlay draw (RW Im2D): saves render states (pfn_RwRenderStateGet), sets blend / texture / z states
// (pfn_RwRenderStateSet, RpSkyRenderStateSet), builds the vertex list at near-screen z (g_rwIm2DNearScreenZ) and
// draws it with pfn_RwIm2DRenderPrimitive, then restores the states.
void sub_358A30(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24};
    // 0x00358a30
    enter(ctx, 36);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1A0);
    sd(ra, sp, 0x60);
    sq(s3, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    swc1(f24, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s0 = a0;
    s3 = a1;
    mov_s(f24, f12);
    s2 = a2;
    jal(ctx, 0x358A6Cu, gen::fn_sub_198590_00198590);
    a0 = addiu(sp, 0x190);
    a1 = s0;
    a2 = addiu(v0, 32);
    jal(ctx, 0x358A80u, gen::fn_sub_4C6BE0_004c6be0);
    v0 = 0x960000;
    lwc1(f20, v0, 140);  // 0x96008C
    v0 = 0x960000;
    lwc1(f22, v0, 136);  // g_rwIm2DNearScreenZ
    jal(ctx, 0x358A98u, gen::fn_sub_198590_00198590);
    lwc1(f21, v0, 132);
    jal(ctx, 0x358AA4u, gen::fn_sub_198590_00198590);
    lwc1(f4, v0, 128);
    lwc1(f3, sp, 0x198);
    c_le_s(f3, f4);
    if (!cond(ctx)) {
        // 0x00358ac0
        charge(ctx, 3);
        c_lt_s(f3, f21);
        if (cond(ctx)) {
            // 0x00358acc
            charge(ctx, 17);
            v0 = 0x3F000000;
            mtc1(v0, f0);
            mul_s(f24, f24, f0);
            sub_s(f1, f22, f20);
            sub_s(f0, f4, f21);
            div_s(f1, f1, f0);
            sub_s(f0, f3, f21);
            mul_s(f2, f0, f1);
            div_s(f1, f4, f3);
            mtc1(zero, f0);
            adda_s(f0, f20);
            madd_s(f23, f1, f2);
            c_lt_s(f23, f0);
            if (cond(ctx)) {
                // 0x00358b10
                charge(ctx, 1);
                mov_s(f23, f0);
            }
            // 0x00358b14
            charge(ctx, 19);
            v0 = 0x3F800000;
            mtc1(v0, f0);
            div_s(f22, f0, f23);
            lwc1(f2, sp, 0x198);
            lwc1(f0, sp, 0x190);
            div_s(f1, f0, f2);
            v0 = 0x44200000;
            mtc1(v0, f0);
            mul_s(f21, f0, f1);
            lwc1(f0, sp, 0x194);
            div_s(f1, f0, f2);
            v0 = 0x43E00000;
            mtc1(v0, f0);
            mul_s(f20, f0, f1);
            if (s2 != 0) {
                // 0x00358b60
                charge(ctx, 3);
                s1 = 0;
                for (;;) {
                    // 0x00358bb8
                    charge(ctx, 3);
                    v0 = sltiu(s1, 6);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00358b6c
                    charge(ctx, 19);
                    v1 = sll(s1, 3);
                    v0 = 0x6A0000;
                    v0 = addiu(v0, -12704);  // &0x69CE60
                    s0 = addu(v0, v1);
                    v0 = sll(s1, 2);
                    v0 = addu(v0, sp);
                    lw(a0, s0, 0);
                    a1 = addiu(v0, 112);
                    v0 = 0x960000;
                    lw(v0, v0, 148);  // pfn_RwRenderStateGet
                    jalr(ctx, 0x358B94u, v0.u());
                    lw(a0, s0, 0);
                    lw(a1, s0, 4);
                    v0 = 0x960000;
                    lw(v0, v0, 144);  // pfn_RwRenderStateSet
                    jalr(ctx, 0x358BACu, v0.u());
                    s1 = addiu(s1, 1);
                }
                // 0x00358bc4
                charge(ctx, 21);
                s0 = 0x960000;
                s0 = addiu(s0, 144);  // &pfn_RwRenderStateSet
                a0 = 6;
                a1 = 0;
                lw(v0, s0, 0);  // pfn_RwRenderStateSet
                jalr(ctx, 0x358BD8u, v0.u());
                a0 = 1;
                a1 = 0;
                lw(v0, s0, 0);  // pfn_RwRenderStateSet
                jalr(ctx, 0x358BECu, v0.u());
                a0 = 2;
                a1 = 72;
                jal(ctx, 0x358BFCu, gen::fn_RpSkyRenderStateSet_004d7f60);
                a0 = 3;
                v0 = 0x70000;
                a1 = v0 | 0x1801;
                jal(ctx, 0x358C10u, gen::fn_RpSkyRenderStateSet_004d7f60);
            }
            // 0x00358c18
            charge(ctx, 9);
            sub_s(f1, f21, f24);
            swc1(f1, sp, 0x90);
            sub_s(f3, f20, f24);
            swc1(f3, sp, 0x94);
            swc1(f23, sp, 0x98);
            swc1(f22, sp, 0xA8);
            lbu(v0, s3, 0);
            if (i64(v0) < 0) {
                // 0x00358c50
                charge(ctx, 7);
                v1 = srl(v0, 1);
                v0 = v0 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f0, f0);
            } else {
                // 0x00358c3c
                charge(ctx, 5);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
            }
            // 0x00358c6c
            charge(ctx, 4);
            swc1(f0, sp, 0xB0);
            lbu(v0, s3, 1);
            if (i64(v0) < 0) {
                // 0x00358c90
                charge(ctx, 7);
                v1 = srl(v0, 1);
                v0 = v0 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f0, f0);
            } else {
                // 0x00358c7c
                charge(ctx, 5);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
            }
            // 0x00358cac
            charge(ctx, 4);
            swc1(f0, sp, 0xB4);
            lbu(v0, s3, 2);
            if (i64(v0) < 0) {
                // 0x00358cd0
                charge(ctx, 7);
                v1 = srl(v0, 1);
                v0 = v0 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f0, f0);
            } else {
                // 0x00358cbc
                charge(ctx, 5);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
            }
            // 0x00358cec
            charge(ctx, 4);
            swc1(f0, sp, 0xB8);
            lbu(v0, s3, 3);
            if (i64(v0) < 0) {
                // 0x00358d10
                charge(ctx, 7);
                v1 = srl(v0, 1);
                v0 = v0 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f0, f0);
            } else {
                // 0x00358cfc
                charge(ctx, 5);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
            }
            // 0x00358d2c
            charge(ctx, 9);
            swc1(f0, sp, 0xBC);
            swc1(f1, sp, 0xD0);
            add_s(f1, f20, f24);
            swc1(f1, sp, 0xD4);
            swc1(f23, sp, 0xD8);
            swc1(f22, sp, 0xE8);
            lbu(v0, s3, 0);
            if (i64(v0) < 0) {
                // 0x00358d64
                charge(ctx, 7);
                v1 = srl(v0, 1);
                v0 = v0 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f0, f0);
            } else {
                // 0x00358d50
                charge(ctx, 5);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
            }
            // 0x00358d80
            charge(ctx, 4);
            swc1(f0, sp, 0xF0);
            lbu(v0, s3, 1);
            if (i64(v0) < 0) {
                // 0x00358da4
                charge(ctx, 7);
                v1 = srl(v0, 1);
                v0 = v0 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f0, f0);
            } else {
                // 0x00358d90
                charge(ctx, 5);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
            }
            // 0x00358dc0
            charge(ctx, 4);
            swc1(f0, sp, 0xF4);
            lbu(v0, s3, 2);
            if (i64(v0) < 0) {
                // 0x00358de4
                charge(ctx, 7);
                v1 = srl(v0, 1);
                v0 = v0 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f0, f0);
            } else {
                // 0x00358dd0
                charge(ctx, 5);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
            }
            // 0x00358e00
            charge(ctx, 4);
            swc1(f0, sp, 0xF8);
            lbu(v0, s3, 3);
            if (i64(v0) < 0) {
                // 0x00358e24
                charge(ctx, 7);
                v1 = srl(v0, 1);
                v0 = v0 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f0, f0);
            } else {
                // 0x00358e10
                charge(ctx, 5);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
            }
            // 0x00358e40
            charge(ctx, 9);
            swc1(f0, sp, 0xFC);
            add_s(f2, f21, f24);
            swc1(f2, sp, 0x110);
            swc1(f3, sp, 0x114);
            swc1(f23, sp, 0x118);
            swc1(f22, sp, 0x128);
            lbu(v0, s3, 0);
            if (i64(v0) < 0) {
                // 0x00358e78
                charge(ctx, 7);
                v1 = srl(v0, 1);
                v0 = v0 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f0, f0);
            } else {
                // 0x00358e64
                charge(ctx, 5);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
            }
            // 0x00358e94
            charge(ctx, 4);
            swc1(f0, sp, 0x130);
            lbu(v0, s3, 1);
            if (i64(v0) < 0) {
                // 0x00358eb8
                charge(ctx, 7);
                v1 = srl(v0, 1);
                v0 = v0 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f0, f0);
            } else {
                // 0x00358ea4
                charge(ctx, 5);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
            }
            // 0x00358ed4
            charge(ctx, 4);
            swc1(f0, sp, 0x134);
            lbu(v0, s3, 2);
            if (i64(v0) < 0) {
                // 0x00358ef8
                charge(ctx, 7);
                v1 = srl(v0, 1);
                v0 = v0 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f0, f0);
            } else {
                // 0x00358ee4
                charge(ctx, 5);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
            }
            // 0x00358f14
            charge(ctx, 4);
            swc1(f0, sp, 0x138);
            lbu(v0, s3, 3);
            if (i64(v0) < 0) {
                // 0x00358f38
                charge(ctx, 7);
                v1 = srl(v0, 1);
                v0 = v0 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f0, f0);
            } else {
                // 0x00358f24
                charge(ctx, 5);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
            }
            // 0x00358f54
            charge(ctx, 8);
            swc1(f0, sp, 0x13C);
            swc1(f2, sp, 0x150);
            swc1(f1, sp, 0x154);
            swc1(f23, sp, 0x158);
            swc1(f22, sp, 0x168);
            lbu(v0, s3, 0);
            if (i64(v0) < 0) {
                // 0x00358f88
                charge(ctx, 7);
                v1 = srl(v0, 1);
                v0 = v0 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f0, f0);
            } else {
                // 0x00358f74
                charge(ctx, 5);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
            }
            // 0x00358fa4
            charge(ctx, 4);
            swc1(f0, sp, 0x170);
            lbu(v0, s3, 1);
            if (i64(v0) < 0) {
                // 0x00358fc8
                charge(ctx, 7);
                v1 = srl(v0, 1);
                v0 = v0 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f0, f0);
            } else {
                // 0x00358fb4
                charge(ctx, 5);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
            }
            // 0x00358fe4
            charge(ctx, 4);
            swc1(f0, sp, 0x174);
            lbu(v0, s3, 2);
            if (i64(v0) < 0) {
                // 0x00359008
                charge(ctx, 7);
                v1 = srl(v0, 1);
                v0 = v0 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f0, f0);
            } else {
                // 0x00358ff4
                charge(ctx, 5);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
            }
            // 0x00359024
            charge(ctx, 4);
            swc1(f0, sp, 0x178);
            lbu(v0, s3, 3);
            if (i64(v0) < 0) {
                // 0x00359048
                charge(ctx, 7);
                v1 = srl(v0, 1);
                v0 = v0 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f0, f0);
            } else {
                // 0x00359034
                charge(ctx, 5);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
            }
            // 0x00359064
            charge(ctx, 10);
            swc1(f0, sp, 0x17C);
            a0 = 4;
            a1 = addiu(sp, 0x90);
            a2 = a0;
            v0 = 0x960000;
            lw(v0, v0, 160);  // pfn_RwIm2DRenderPrimitive
            jalr(ctx, 0x35907Cu, v0.u());
            if (s2 != 0) {
                // 0x0035908c
                charge(ctx, 3);
                s0 = 0;
                for (;;) {
                    // 0x003590cc
                    charge(ctx, 3);
                    v1 = sltiu(s0, 6);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00359098
                    charge(ctx, 13);
                    v1 = sll(s0, 3);
                    v0 = 0x6A0000;
                    v0 = addiu(v0, -12704);  // &0x69CE60
                    v1 = addu(v0, v1);
                    v0 = sll(s0, 2);
                    v0 = addu(v0, sp);
                    lw(a0, v1, 0);
                    lw(a1, v0, 112);
                    v0 = 0x960000;
                    lw(v0, v0, 144);  // pfn_RwRenderStateSet
                    jalr(ctx, 0x3590C0u, v0.u());
                    s0 = addiu(s0, 1);
                }
            }
        }
    }
    // 0x003590d8 (the shared epilogue, written out on this path)
    charge(ctx, 13);
    ld(ra, sp, 0x60);
    lq(s3, sp, 0x50);
    lq(s2, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    lwc1(f24, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x1A0);
}

// 0x00359380 sub_359380 -- 472 bytes; frame 0xA0: ra sp+0x50, s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// Screen fade / rectangle draw: sets the RW states (RpSkyRenderStateSet), builds the quad from dword_69CE90 /
// dword_69CEB8 via sub_359110 and restores the saved states.
void sub_359380(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12}, f20{ctx, 20};
    // 0x00359380
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s3 = a0;
    mov_s(f20, f12);
    s2 = a1;
    if (s2 != 0) {
        // 0x003593b0
        charge(ctx, 3);
        s1 = 0;
        for (;;) {
            // 0x00359408
            charge(ctx, 3);
            v0 = sltiu(s1, 6);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003593bc
            charge(ctx, 19);
            v1 = sll(s1, 3);
            v0 = 0x6A0000;
            v0 = addiu(v0, -12704);  // &0x69CE60
            s0 = addu(v0, v1);
            v0 = sll(s1, 2);
            v0 = addu(v0, sp);
            lw(a0, s0, 0);
            a1 = addiu(v0, 96);
            v0 = 0x960000;
            lw(v0, v0, 148);  // pfn_RwRenderStateGet
            jalr(ctx, 0x3593E4u, v0.u());
            lw(a0, s0, 0);
            lw(a1, s0, 4);
            v0 = 0x960000;
            lw(v0, v0, 144);  // pfn_RwRenderStateSet
            jalr(ctx, 0x3593FCu, v0.u());
            s1 = addiu(s1, 1);
        }
        // 0x00359414
        charge(ctx, 15);
        a0 = 1;
        a1 = 0;
        v0 = 0x960000;
        lw(v0, v0, 144);  // pfn_RwRenderStateSet
        jalr(ctx, 0x359424u, v0.u());
        a0 = 2;
        a1 = 72;
        jal(ctx, 0x359434u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x1801;
        jal(ctx, 0x359448u, gen::fn_RpSkyRenderStateSet_004d7f60);
    }
    // 0x00359450
    charge(ctx, 3);
    s0 = 0;
    for (;;) {
        // 0x003594d4
        charge(ctx, 3);
        v1 = sltiu(s0, 3);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0035945c
        charge(ctx, 30);
        v0 = sll(s0, 1);
        v0 = addu(v0, s0);
        v1 = sll(v0, 2);
        v0 = 0x6A0000;
        v0 = addiu(v0, -12656);  // &0x69CE90
        v0 = addu(v0, v1);
        lwc1(f0, v0, 0);
        mul_s(f0, f20, f0);
        swc1(f0, sp, 0x80);
        lwc1(f0, v0, 4);
        mul_s(f0, f20, f0);
        swc1(f0, sp, 0x84);
        lwc1(f0, v0, 8);
        mul_s(f0, f20, f0);
        swc1(f0, sp, 0x88);
        a0 = addiu(sp, 0x90);
        a1 = addiu(sp, 0x80);
        a2 = s3;
        jal(ctx, 0x3594A4u, gen::fn_sub_4C6BE0_004c6be0);
        v1 = sll(s0, 2);
        v0 = 0x6A0000;
        v0 = addiu(v0, -12616);  // &0x69CEB8
        a2 = addu(v0, v1);
        a0 = addiu(s3, 48);
        a1 = addiu(sp, 0x90);
        a3 = 0;
        jal(ctx, 0x3594C8u, gen::fn_sub_359110_00359110);
        s0 = addiu(s0, 1);
    }
    // 0x003594e0
    charge(ctx, 2);
    if (s2 != 0) {
        // 0x003594e8
        charge(ctx, 3);
        s0 = 0;
        for (;;) {
            // 0x00359528
            charge(ctx, 3);
            v1 = sltiu(s0, 6);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003594f4
            charge(ctx, 13);
            v1 = sll(s0, 3);
            v0 = 0x6A0000;
            v0 = addiu(v0, -12704);  // &0x69CE60
            v1 = addu(v0, v1);
            v0 = sll(s0, 2);
            v0 = addu(v0, sp);
            lw(a0, v1, 0);
            lw(a1, v0, 96);
            v0 = 0x960000;
            lw(v0, v0, 144);  // pfn_RwRenderStateSet
            jalr(ctx, 0x35951Cu, v0.u());
            s0 = addiu(s0, 1);
        }
    }
    // 0x00359534 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// 0x003A2090 sub_3A2090 -- 184 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Creates the "Card Effect" task (priority 16, update sub_3A1C00, draw sub_3A1F30) under a0 with a zeroed 252-byte
// work block: +4 = a1 (u16), +8 = a2, +12 = a3 (u16).
void sub_3A2090(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a2090
    enter(ctx, 46);  // entry check point + this block's cycles
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
    a0 = 252;
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x3A20CCu, v0.u());
    s4 = v0;
    a0 = s4;
    a1 = 0;
    a2 = 252;
    jal(ctx, 0x3A20E4u, gen::fn_memset_00521408);
    sh(s2, s4, 4);
    sw(s1, s4, 8);
    sh(s0, s4, 12);
    a0 = s3;
    a1 = 0x6A0000;
    a1 = addiu(a1, 6744);  // "Card Effect"
    a2 = 16;
    a3 = 0x3A0000;
    a3 = addiu(a3, 7168);  // &sub_3A1C00
    t0 = 0x3A0000;
    t0 = addiu(t0, 7984);  // &sub_3A1F30
    t1 = s4;
    jal(ctx, 0x3A211Cu, gen::fn_kwlnTaskCreate_00194b20);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x003B2F90 sub_3B2F90 -- 824 bytes; frame 0xA0: ra sp+0x90, s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// frFont text box draw (frFont.c / frFontEx.c): builds the glyph list (frFontBuildGlyphList), measures the style
// (frFontGetStyleSize), draws (frFontDraw) and steps the per-line fade (frFontLineFadeStep); asserts on a missing
// font.
void sub_3B2F90(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f20{ctx, 20};
    // 0x003b2f90
    enter(ctx, 24);  // entry check point + this block's cycles
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
    s4 = a0;
    s3 = a1;
    mov_s(f20, f12);
    s5 = a2;
    s6 = t0;
    s2 = t2;
    s7 = t3;
    s0 = 0;
    v1 = dsll32(a3, 24);
    v1 = dsra32(v1, 24);
    v0 = 10;
    if (v1 == v0) {
        // 0x003b2ff0
        charge(ctx, 4);
        a3 = 5;
        v0 = s5 & 0xFF;
        if (i64(v0) < 0) {
            // 0x003b3014
            charge(ctx, 7);
            v1 = srl(v0, 1);
            v0 = v0 & 0x1;
            v1 = v1 | v0;
            mtc1(v1, f0);
            cvt_s_w(f1, f0);
            add_s(f1, f1, f1);
        } else {
            // 0x003b3000
            charge(ctx, 5);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
        }
        // 0x003b3030
        charge(ctx, 7);
        lwc1(f0, gp, -32604);  // 0x7CAD94
        mul_s(f0, f0, f1);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = si(-256);
        v0 = s5 & v0;
        s5 = v0 | v1;
    }
    // 0x003b304c
    charge(ctx, 17);
    lh(v0, gp, -22512);  // 0x7CD500
    v0 = v0 | 0x1;
    v1 = dsll32(v0, 16);
    v1 = dsra32(v1, 16);
    v0 = si(-3);
    v0 = v1 & v0;
    sh(v0, gp, -22512);  // 0x7CD500
    a0 = t1;
    a1 = s6;
    a2 = a3;
    a3 = 0;
    t0 = 0;
    jal(ctx, 0x3B307Cu, gen::fn_frFontBuildGlyphList_003b0970);
    s1 = v0;
    if (s1 == 0) {
        // 0x003b3090
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 10032);  // "frFont.c"
        a1 = 2120;
        jal(ctx, 0x3B309Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003b30a4
    charge(ctx, 5);
    sb(s7, s1, 3);
    v1 = 0;
    lw(a0, s1, 28);
    for (;;) {
        // 0x003b30cc
        charge(ctx, 2);
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003b30b8
        charge(ctx, 5);
        lw(v0, a0, 12);
        v1 = addu(v1, v0);
        lb(v0, s1, 3);
        v1 = addu(v1, v0);
        lw(a0, a0, 40);
    }
    // 0x003b30d4
    charge(ctx, 11);
    sw(v1, s1, 12);
    lh(v1, gp, -22512);  // 0x7CD500
    v0 = si(-2);
    v0 = v1 & v0;
    v0 = dsll32(v0, 16);
    v0 = dsra32(v0, 16);
    v0 = v0 | 0x2;
    sh(v0, gp, -22512);  // 0x7CD500
    v0 = s2 & 0xB;
    if (v0 != 0) {
        // 0x003b3100
        charge(ctx, 4);
        s0 = 0;
        lw(a0, s1, 28);
        for (;;) {
            // 0x003b3124
            charge(ctx, 2);
            if (a0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003b3110
            charge(ctx, 5);
            lw(v0, a0, 12);
            v1 = addu(s0, v0);
            lb(v0, s1, 3);
            s0 = addu(v1, v0);
            lw(a0, a0, 40);
        }
    }
    // 0x003b312c
    charge(ctx, 3);
    v0 = s2 & 0x8;
    if (v0 == 0) {
        // 0x003b3148
        charge(ctx, 3);
        v0 = s2 & 0x2;
        if (v0 != 0) {
            // 0x003b3154
            charge(ctx, 1);
            s4 = subu(s4, s0);
        }
    } else {
        // 0x003b3138
        charge(ctx, 4);
        v0 = sra(s0, 1);
        s4 = subu(s4, v0);
    }
    // 0x003b3158
    charge(ctx, 3);
    v0 = s2 & 0x4;
    if (v0 == 0) {
        // 0x003b317c
        charge(ctx, 3);
        v0 = s2 & 0x10;
        if (v0 != 0) {
            // 0x003b3188
            charge(ctx, 16);
            a0 = s6;
            jal(ctx, 0x3B318Cu, gen::fn_frFontGetStyleSize_003b35c0);
            mtc1(v0, f0);
            cvt_s_w(f3, f0);
            lwc1(f2, gp, -32628);  // 0x7CAD7C
            mtc1(s3, f0);
            cvt_s_w(f1, f0);
            mtc1(zero, f0);
            adda_s(f0, f1);
            msub_s(f0, f2, f3);
            cvt_w_s(f0, f0);
            mfc1(s3, f0);
        }
    } else {
        // 0x003b3164
        charge(ctx, 6);
        a0 = s6;
        jal(ctx, 0x3B3168u, gen::fn_frFontGetStyleSize_003b35c0);
        s3 = subu(s3, v0);
    }
    // 0x003b31c8
    charge(ctx, 2);
    if (s1 == 0) {
        // 0x003b31d0
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 10032);  // "frFont.c"
        a1 = 2188;
        jal(ctx, 0x3B31DCu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003b31e4
    charge(ctx, 6);
    v0 = sll(s4, 4);
    sw(v0, s1, 4);
    v0 = sll(s3, 3);
    sw(v0, s1, 8);
    if (s1 == 0) {
        // 0x003b31fc
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 10376);  // "frFontEx.c"
        a1 = 19;
        jal(ctx, 0x3B3208u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003b3210
    charge(ctx, 4);
    swc1(f20, s1, 20);
    v1 = s1;
    for (;;) {
        // 0x003b324c
        charge(ctx, 2);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003b3220
        charge(ctx, 3);
        lw(v0, v1, 28);
        for (;;) {
            // 0x003b3234
            charge(ctx, 5);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003b322c
            charge(ctx, 2);
            sw(s5, v0, 16);
            lw(v0, v0, 40);
        }
        // 0x003b3248
        charge(ctx, 1);
        lw(v1, v1, 36);
    }
    // 0x003b3254
    charge(ctx, 12);
    a0 = s1;
    a1 = 1;
    a2 = 0;
    jal(ctx, 0x3B3260u, gen::fn_frFontDraw_003b1360);
    a0 = s1;
    jal(ctx, 0x3B326Cu, gen::fn_frFontLineFadeStep_003b0ec0);
    v0 = dsll32(v0, 24);
    v0 = dsra32(v0, 24);
    if (v0 == 0) {
        // 0x003b3284
        charge(ctx, 3);
        a0 = s1;
        jal(ctx, 0x3B3288u, gen::fn_sub_3B0030_003b0030);
    }
    // 0x003b3290 (the shared epilogue, written out on this path)
    charge(ctx, 14);
    v0 = s0;
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

// 0x003B5760 MT_Scene_Load -- 340 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Scene data load for (major a0, minor a1) into the scene manager (*0x7CD540): a cache hit (same pair and major
// outside 20..28) prints "Scene data cashe hit!!" and sets bit 0 of +12; otherwise unloads the old scene
// (sub_3B5AB0), loads the field data (sub_1B0870 / sub_1B0A20), creates the control task (+36 = sub_1B58B0(0)),
// records the pair (+0 / +4, +20 / +22) and the resource manager (+8 = sub_3B4FC0()), then initialises the
// sub-systems (sub_3B63C0, sub_1A0A90, sub_3B6440, sub_1A0EE0).
void MT_Scene_Load(EEContext& ctx) {
    using namespace hg;
    using namespace sweep5c;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b5760
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lw(v0, gp, kGpSceneRecord);  // -> MT_Scene's record
    sw(zero, v0, scene::kFlags);
    lw(v1, gp, kGpSceneRecord);  // -> MT_Scene's record
    lw(v0, v1, scene::kMajor);
    if (v0 == s1) {
        // 0x003b5790
        charge(ctx, 3);
        lw(v0, v1, scene::kMinor);
        if (v0 != s0) {
            goto L_003b57e4;
        }
        // 0x003b579c
        charge(ctx, 3);
        v0 = slti(s1, 20);
        if (v0 == 0) {
            // 0x003b57a8
            charge(ctx, 3);
            at = slti(s1, 29);
            if (at != 0) {
                goto L_003b57e4;
            }
            goto L_003b57b4;
        }
    L_003b57b4:
        charge(ctx, 12);
        a0 = 0x6A0000;
        a0 = addiu(a0, 11104);  // "Scene data cashe hit!! major=%d minor=%d\n"
        a1 = s1;
        a2 = s0;
        jal(ctx, 0x3B57C4u, gen::fn_printf_005225a8);
        lw(a0, gp, kGpSceneRecord);  // -> MT_Scene's record
        lw(v1, a0, scene::kFlags);
        v1 = v1 | 0x1;
        sw(v1, a0, scene::kFlags);
        // 0x003b589c (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(ra, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
L_003b57e4:
    charge(ctx, 46);
    jal(ctx, 0x3B57E4u, gen::fn_sub_3B5AB0_003b5ab0);
    a0 = dsll32(s1, 16);
    a0 = dsra32(a0, 16);
    a1 = dsll32(s0, 16);
    a1 = dsra32(a1, 16);
    jal(ctx, 0x3B57FCu, gen::fn_sub_1B0870_001b0870);
    a0 = dsll32(s1, 16);
    a0 = dsra32(a0, 16);
    a1 = dsll32(s0, 16);
    a1 = dsra32(a1, 16);
    jal(ctx, 0x3B5814u, gen::fn_sub_1B0A20_001b0a20);
    a0 = 0;
    jal(ctx, 0x3B5820u, gen::fn_sub_1B58B0_001b58b0);
    lw(v1, gp, kGpSceneRecord);  // -> MT_Scene's record
    sw(v0, v1, scene::kCtlTask);
    lw(v0, gp, kGpSceneRecord);  // -> MT_Scene's record
    sw(s1, v0, scene::kMajor);
    lw(v0, gp, kGpSceneRecord);  // -> MT_Scene's record
    sw(s0, v0, scene::kMinor);
    lw(v0, gp, kGpSceneRecord);  // -> MT_Scene's record
    sh(zero, v0, scene::kNpcSet);
    lw(v1, gp, kGpSceneRecord);  // -> MT_Scene's record
    lw(v0, v1, scene::kMinor);
    sh(v0, v1, scene::kEnvSub);
    jal(ctx, 0x3B5854u, gen::fn_sub_3B4FC0_003b4fc0);
    lw(v1, gp, kGpSceneRecord);  // -> MT_Scene's record
    sw(v0, v1, scene::kResMgr);
    a0 = 0;
    jal(ctx, 0x3B5868u, gen::fn_sub_3B63C0_003b63c0);
    jal(ctx, 0x3B5870u, gen::fn_sub_1A0A90_001a0a90);
    a0 = 0;
    jal(ctx, 0x3B587Cu, gen::fn_sub_3B6440_003b6440);
    jal(ctx, 0x3B5884u, gen::fn_sub_1A0EE0_001a0ee0);
    a0 = 0x6A0000;
    a0 = addiu(a0, 11152);  // "Scene data load...\n"
    jal(ctx, 0x3B5894u, gen::fn_printf_005225a8);
    // 0x003b589c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003B5A10 sub_3B5A10 -- 156 bytes; frame 0x10: ra sp+0x0
// Scene load poll: 1 when there is no resource manager (+8) or the cache hit stands (bit 0 of +12 without bits 1..2);
// otherwise 0 until sub_1B10F0 reports the field ready, then creates the scene task once (+32 = sub_3BD0B0()) and
// returns 1.
void sub_3B5A10(EEContext& ctx) {
    using namespace hg;
    using namespace sweep5c;
    Gpr v0{ctx, 2}, v1{ctx, 3}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b5a10
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpSceneRecord);  // -> MT_Scene's record
    lw(v0, v1, scene::kResMgr);
    if (v0 != 0) {
        // 0x003b5a34
        charge(ctx, 4);
        lw(v1, v1, scene::kFlags);
        v0 = v1 & 0x1;
        if (v0 != 0) {
            // 0x003b5a44
            charge(ctx, 3);
            v0 = v1 & 0x6;
            if (v0 != 0) {
                goto L_003b5a5c;
            }
            // 0x003b5a50
            charge(ctx, 3);
            v0 = 1;
            // 0x003b5a9c (the shared epilogue, written out on this path)
            charge(ctx, 4);
            ld(ra, sp, 0x0);
            sp = addiu(sp, 0x10);
            return;
        }
    L_003b5a5c:
        charge(ctx, 4);
        jal(ctx, 0x3B5A5Cu, gen::fn_sub_1B10F0_001b10f0);
        if (v0 != 0) {
            // 0x003b5a78
            charge(ctx, 4);
            lw(v0, gp, kGpSceneRecord);  // -> MT_Scene's record
            lw(v0, v0, scene::kSceneTask);
            if (v0 == 0) {
                // 0x003b5a88
                charge(ctx, 4);
                jal(ctx, 0x3B5A88u, gen::fn_sub_3BD0B0_003bd0b0);
                lw(v1, gp, kGpSceneRecord);  // -> MT_Scene's record
                sw(v0, v1, scene::kSceneTask);
            }
            // 0x003b5a98
            charge(ctx, 1);
            v0 = 1;
        } else {
            // 0x003b5a6c
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x003b5a28
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x003b5a9c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003B5AB0 sub_3B5AB0 -- 564 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Scene unload: destroys the scene task (+32) and the control task (+36, after sub_1948B0), releases every object of
// the 22 resource classes (sub_3B5430 lists, sub_3B7090), then the field-specific state (floor, unit, model helpers)
// and clears the manager.
void sub_3B5AB0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b5ab0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, -22448);  // 0x7CD540
    lw(s0, v0, 8);
    lw(a0, v0, 32);
    if (a0 != 0) {
        // 0x003b5ad8
        charge(ctx, 4);
        jal(ctx, 0x3B5AD8u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
        lw(v0, gp, -22448);  // 0x7CD540
        sw(zero, v0, 32);
    }
    // 0x003b5ae8
    charge(ctx, 4);
    lw(v0, gp, -22448);  // 0x7CD540
    lw(v0, v0, 36);
    if (v0 != 0) {
        // 0x003b5af8
        charge(ctx, 8);
        jal(ctx, 0x3B5AF8u, gen::fn_sub_1948B0_001948b0);
        lw(v0, gp, -22448);  // 0x7CD540
        lw(a0, v0, 36);
        jal(ctx, 0x3B5B08u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
        lw(v0, gp, -22448);  // 0x7CD540
        sw(zero, v0, 36);
    }
    // 0x003b5b18
    charge(ctx, 2);
    if (s0 != 0) {
        // 0x003b5b20
        charge(ctx, 3);
        s2 = 0;
        for (;;) {
            // 0x003b5b68
            charge(ctx, 3);
            v0 = slti(s2, 22);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003b5b2c
            charge(ctx, 6);
            a1 = s2 & 0xFF;
            a0 = s0;
            jal(ctx, 0x3B5B34u, gen::fn_sub_3B5430_003b5430);
            for (;;) {
                // 0x003b5b58
                charge(ctx, 3);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x003b5b44
                charge(ctx, 5);
                lw(s1, v0, 248);
                lhu(a0, v0, 0);
                jal(ctx, 0x3B5B4Cu, gen::fn_sub_3B7090_003b7090);
                v0 = s1;
            }
            // 0x003b5b64
            charge(ctx, 1);
            s2 = addiu(s2, 1);
        }
        // 0x003b5b74
        charge(ctx, 5);
        a0 = s0;
        jal(ctx, 0x3B5B78u, gen::fn_sub_3B5020_003b5020);
        lw(v0, gp, -22448);  // 0x7CD540
        sw(zero, v0, 8);
    }
    // 0x003b5b88
    charge(ctx, 5);
    jal(ctx, 0x3B5B88u, gen::fn_sub_27C2B0_0027c2b0);
    v1 = 5;
    if (v0 != v1) {
        // 0x003b5b9c
        charge(ctx, 3);
        lw(v0, gp, -19056);  // 0x7CE280
        if (v0 != 0) {
            // 0x003b5ba8
            charge(ctx, 4);
            jal(ctx, 0x3B5BA8u, gen::fn_K_FldDungeon_GetCurrentFloor_001bff20);
            if (v0 == 0) {
                // 0x003b5bb8
                charge(ctx, 4);
                lw(a0, gp, -19056);  // 0x7CE280
                jal(ctx, 0x3B5BBCu, gen::fn_sub_3174E0_003174e0);
                sw(zero, gp, -19056);  // 0x7CE280
            }
        }
        // 0x003b5bc8
        charge(ctx, 3);
        s1 = 0;
        for (;;) {
            // 0x003b5c00
            charge(ctx, 3);
            v0 = slti(s1, 9);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003b5bd4
            charge(ctx, 7);
            v1 = sll(s1, 2);
            v0 = 0x870000;
            v0 = addiu(v0, -16960);  // &0x86BDC0
            s0 = addu(v0, v1);
            lw(a0, s0, 0);
            if (a0 != 0) {
                // 0x003b5bf0
                charge(ctx, 3);
                jal(ctx, 0x3B5BF0u, gen::fn_sub_1B3C90_001b3c90);
                sw(zero, s0, 0);
            }
            // 0x003b5bfc
            charge(ctx, 1);
            s1 = addiu(s1, 1);
        }
    }
    // 0x003b5c0c
    charge(ctx, 5);
    jal(ctx, 0x3B5C0Cu, gen::fn_K_Field_Get_001b9120);
    lw(v0, v0, 4588);
    if (v0 != 0) {
        // 0x003b5c20
        charge(ctx, 8);
        jal(ctx, 0x3B5C20u, gen::fn_K_Field_Get_001b9120);
        lw(a0, v0, 4588);
        jal(ctx, 0x3B5C2Cu, gen::fn_sub_3174E0_003174e0);
        jal(ctx, 0x3B5C34u, gen::fn_K_Field_Get_001b9120);
        sw(zero, v0, 4588);
    }
    // 0x003b5c40
    charge(ctx, 5);
    jal(ctx, 0x3B5C40u, gen::fn_K_Field_Get_001b9120);
    lw(v0, v0, 4592);
    if (v0 != 0) {
        // 0x003b5c54
        charge(ctx, 8);
        jal(ctx, 0x3B5C54u, gen::fn_K_Field_Get_001b9120);
        lw(a0, v0, 4592);
        jal(ctx, 0x3B5C60u, gen::fn_sub_3174E0_003174e0);
        jal(ctx, 0x3B5C68u, gen::fn_K_Field_Get_001b9120);
        sw(zero, v0, 4592);
    }
    // 0x003b5c74
    charge(ctx, 28);
    jal(ctx, 0x3B5C74u, gen::fn_sub_1B8600_001b8600);
    jal(ctx, 0x3B5C7Cu, gen::fn_sub_1B8870_001b8870);
    jal(ctx, 0x3B5C84u, gen::fn_sub_1B8AE0_001b8ae0);
    jal(ctx, 0x3B5C8Cu, gen::fn_sub_1C80C0_001c80c0);
    v1 = si(-1);
    lw(v0, gp, -22448);  // 0x7CD540
    sw(v1, v0, 0);
    lw(v0, gp, -22448);  // 0x7CD540
    sw(v1, v0, 4);
    lw(v0, gp, -22448);  // 0x7CD540
    sh(zero, v0, 20);
    lw(v0, gp, -22448);  // 0x7CD540
    sh(zero, v0, 22);
    lw(v0, gp, -22448);  // 0x7CD540
    sw(zero, v0, 24);
    jal(ctx, 0x3B5CC0u, gen::fn_sub_4C43B0_004c43b0);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003B5CF0 sub_3B5CF0 -- 12 bytes; leaf frame (no stack)
// Returns the scene manager pointer (*0x7CD540).
void sub_3B5CF0(EEContext& ctx) {
    using namespace hg;
    using namespace sweep5c;
    Gpr v0{ctx, 2}, gp{ctx, 28};
    // 0x003b5cf0
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, gp, kGpSceneRecord);  // -> MT_Scene's record
}

// 0x003B5D00 sub_3B5D00 -- 16 bytes; leaf frame (no stack)
// Returns the scene manager's resource manager (+8).
void sub_3B5D00(EEContext& ctx) {
    using namespace hg;
    using namespace sweep5c;
    Gpr v0{ctx, 2}, gp{ctx, 28};
    // 0x003b5d00
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, gp, kGpSceneRecord);  // -> MT_Scene's record
    lw(v0, v0, scene::kResMgr);
}

// 0x003B5D10 sub_3B5D10 -- 64 bytes; frame 0x10: ra sp+0x0
// Returns sub_3B54C0() (the active camera / view record) when the scene has a resource manager, else 0.
void sub_3B5D10(EEContext& ctx) {
    using namespace hg;
    using namespace sweep5c;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b5d10
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a1 = a0;
    lw(v0, gp, kGpSceneRecord);  // -> MT_Scene's record
    lw(a0, v0, scene::kResMgr);
    if (a0 != 0) {
        // 0x003b5d38
        charge(ctx, 2);
        jal(ctx, 0x3B5D38u, gen::fn_sub_3B54C0_003b54c0);
    } else {
        // 0x003b5d2c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003b5d40 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003B5DF0 sub_3B5DF0 -- 152 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Counts the scene objects of resource class a0 (sub_3B5550 over the 22 classes, only class a0 counted); 0 without a
// resource manager.
void sub_3B5DF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b5df0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s2 = 0;
    lw(v0, gp, -22448);  // 0x7CD540
    lw(s1, v0, 8);
    if (s1 != 0) {
        // 0x003b5e2c
        charge(ctx, 3);
        s3 = 0;
        for (;;) {
            // 0x003b5e58
            charge(ctx, 3);
            v0 = slti(s3, 22);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003b5e38
            charge(ctx, 2);
            if (s3 == s0) {
                // 0x003b5e40
                charge(ctx, 5);
                a1 = s3 & 0xFF;
                a0 = s1;
                jal(ctx, 0x3B5E48u, gen::fn_sub_3B5550_003b5550);
                s2 = addu(s2, v0);
            }
            // 0x003b5e54
            charge(ctx, 1);
            s3 = addiu(s3, 1);
        }
        // 0x003b5e64
        charge(ctx, 1);
        v0 = s2;
    } else {
        // 0x003b5e20
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003b5e68 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x003B6000 sub_3B6000 -- 40 bytes; frame 0x10: ra sp+0x0
// Wrapper: sub_3B6030(a0, 0, a1).
void sub_3B6000(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b6000
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = a1;
    a1 = 0;
    jal(ctx, 0x3B6010u, gen::fn_sub_3B6030_003b6030);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003B6030 sub_3B6030 -- 332 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Scene object lookup by id (a0 & 0x3FF | 0x400): with a resource manager, finds the object (sub_3B50D0) and either
// returns it or fetches its model (sub_318A30 / sub_318B60), updates its frame (sub_4C2F10) and creates its control
// task (K_FldFrame_CreateCtlTask, sub_19BEB0); prints "not found active resmanager" without one.
void sub_3B6030(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x003b6030
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a1;
    s1 = a2;
    v1 = addiu(sp, 0x50);
    v0 = 12;
    if (v1 != 0) {
        for (;;) {
            // 0x003b6060
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
    // 0x003b607c
    charge(ctx, 8);
    v0 = a0 & 0xFFFF;
    v0 = v0 & 0x3FF;
    v0 = v0 | 0x400;
    s0 = v0 & 0xFFFF;
    lw(v0, gp, -22448);  // 0x7CD540
    lw(a0, v0, 8);
    if (a0 != 0) {
        // 0x003b60b8
        charge(ctx, 2);
        if (s1 != 0) {
            // 0x003b60cc
            charge(ctx, 6);
            a1 = s0;
            jal(ctx, 0x3B60D0u, gen::fn_sub_3B50D0_003b50d0);
            s3 = v0;
            if (s3 != 0) {
                // 0x003b60f0
                charge(ctx, 27);
                sw(s1, s3, 296);
                a0 = s1;
                a1 = addiu(sp, 0x50);
                a2 = 0;
                jal(ctx, 0x3B6100u, gen::fn_sub_318A30_00318a30);
                lw(a0, s3, 296);
                jal(ctx, 0x3B610Cu, gen::fn_sub_318B60_00318b60);
                a0 = v0;
                jal(ctx, 0x3B6118u, gen::fn_sub_4C2F10_004c2f10);
                a1 = s0 & 0xFFFF;
                v0 = 0x42700000;
                mtc1(v0, f12);
                a0 = 0;
                a2 = 0;
                jal(ctx, 0x3B6134u, gen::fn_K_FldFrame_CreateCtlTask_001ad660);
                sw(v0, s3, 480);
                a0 = v0;
                a1 = s0;
                a2 = s2;
                jal(ctx, 0x3B614Cu, gen::fn_sub_19BEB0_0019beb0);
                sw(v0, s3, 484);
                v0 = s0;
            } else {
                // 0x003b60e4
                charge(ctx, 3);
                v0 = 0;
            }
        } else {
            // 0x003b60c0
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x003b609c
        charge(ctx, 7);
        a0 = 0x6A0000;
        a0 = addiu(a0, 11184);  // "not found active resmanager\n"
        jal(ctx, 0x3B60A4u, gen::fn_printf_005225a8);
        v0 = 0;
    }
    // 0x003b615c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x003B6270 sub_3B6270 -- 332 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Twin of sub_3B6030 for the 0x800 id class (a0 & 0x3FF | 0x800).
void sub_3B6270(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x003b6270
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a1;
    s1 = a2;
    v1 = addiu(sp, 0x50);
    v0 = 12;
    if (v1 != 0) {
        for (;;) {
            // 0x003b62a0
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
    // 0x003b62bc
    charge(ctx, 8);
    v0 = a0 & 0xFFFF;
    v0 = v0 & 0x3FF;
    v0 = v0 | 0xC00;
    s0 = v0 & 0xFFFF;
    lw(v0, gp, -22448);  // 0x7CD540
    lw(a0, v0, 8);
    if (a0 != 0) {
        // 0x003b62f8
        charge(ctx, 2);
        if (s1 != 0) {
            // 0x003b630c
            charge(ctx, 6);
            a1 = s0;
            jal(ctx, 0x3B6310u, gen::fn_sub_3B50D0_003b50d0);
            s3 = v0;
            if (s3 != 0) {
                // 0x003b6330
                charge(ctx, 27);
                sw(s1, s3, 296);
                a0 = s1;
                a1 = addiu(sp, 0x50);
                a2 = 0;
                jal(ctx, 0x3B6340u, gen::fn_sub_318A30_00318a30);
                lw(a0, s3, 296);
                jal(ctx, 0x3B634Cu, gen::fn_sub_318B60_00318b60);
                a0 = v0;
                jal(ctx, 0x3B6358u, gen::fn_sub_4C2F10_004c2f10);
                a1 = s0 & 0xFFFF;
                v0 = 0x42700000;
                mtc1(v0, f12);
                a0 = 0;
                a2 = 0;
                jal(ctx, 0x3B6374u, gen::fn_K_FldFrame_CreateCtlTask_001ad660);
                sw(v0, s3, 488);
                a0 = v0;
                a1 = s0;
                a2 = s2;
                jal(ctx, 0x3B638Cu, gen::fn_sub_19BEB0_0019beb0);
                sw(v0, s3, 496);
                v0 = s0;
            } else {
                // 0x003b6324
                charge(ctx, 3);
                v0 = 0;
            }
        } else {
            // 0x003b6300
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x003b62dc
        charge(ctx, 7);
        a0 = 0x6A0000;
        a0 = addiu(a0, 11184);  // "not found active resmanager\n"
        jal(ctx, 0x3B62E4u, gen::fn_printf_005225a8);
        v0 = 0;
    }
    // 0x003b639c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x003B65D0 sub_3B65D0 -- 220 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Scene object lookup for the 0x2800 id class (a0 & 0x3FF | 0x2800): returns the object's record (sub_3B50D0) or
// prints "not found active resmanager".
void sub_3B65D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b65d0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    v1 = addiu(sp, 0x30);
    v0 = 12;
    if (v1 != 0) {
        for (;;) {
            // 0x003b65f4
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
    // 0x003b6610
    charge(ctx, 8);
    v0 = a0 & 0xFFFF;
    v0 = v0 & 0x3FF;
    v0 = v0 | 0x2800;
    s1 = v0 & 0xFFFF;
    lw(v0, gp, -22448);  // 0x7CD540
    lw(a0, v0, 8);
    if (a0 != 0) {
        // 0x003b664c
        charge(ctx, 2);
        if (s0 != 0) {
            // 0x003b6660
            charge(ctx, 5);
            a1 = s1;
            jal(ctx, 0x3B6664u, gen::fn_sub_3B50D0_003b50d0);
            if (v0 != 0) {
                // 0x003b6680
                charge(ctx, 5);
                sw(s0, v0, 260);
                lw(v1, v0, 40);
                v1 = v1 | 0x8;
                sw(v1, v0, 40);
                v0 = s1;
            } else {
                // 0x003b6674
                charge(ctx, 3);
                v0 = 0;
            }
        } else {
            // 0x003b6654
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x003b6630
        charge(ctx, 7);
        a0 = 0x6A0000;
        a0 = addiu(a0, 11184);  // "not found active resmanager\n"
        jal(ctx, 0x3B6638u, gen::fn_printf_005225a8);
        v0 = 0;
    }
    // 0x003b6694 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003B8B30 sub_3B8B30 -- 248 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Starts a camera move on the active camera record (sub_3B5D10): converts the vector a1 (sub_3BBA70 / sub_3BB9B0),
// flags +40 |= 4, saves the current point (+16..+24) to +100..+108 and the new one to +112..+120, then +124 = 0, +125
// = a3 (byte), +128 = a2, +132 = 0; returns 1 (0 without a camera).
void sub_3B8B30(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x003b8b30
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a1;
    s2 = a2;
    s1 = a3;
    jal(ctx, 0x3B8B54u, gen::fn_sub_3B5D10_003b5d10);
    s0 = v0;
    if (s0 != 0) {
        // 0x003b8b74
        charge(ctx, 8);
        lwc1(f2, s3, 0);
        lwc1(f1, s3, 4);
        lwc1(f0, s3, 8);
        swc1(f2, sp, 0x50);
        swc1(f1, sp, 0x54);
        swc1(f0, sp, 0x58);
        if (s0 != 0) {
            // 0x003b8ba0
            charge(ctx, 26);
            a0 = s0;
            jal(ctx, 0x3B8BA4u, gen::fn_sub_3BBA70_003bba70);
            a0 = addiu(sp, 0x50);
            jal(ctx, 0x3B8BB0u, gen::fn_sub_3BB9B0_003bb9b0);
            lw(v0, s0, 40);
            v0 = v0 | 0x4;
            sw(v0, s0, 40);
            lwc1(f2, s0, 16);
            lwc1(f1, s0, 20);
            lwc1(f0, s0, 24);
            swc1(f2, s0, 100);
            swc1(f1, s0, 104);
            swc1(f0, s0, 108);
            lwc1(f2, sp, 0x50);
            lwc1(f1, sp, 0x54);
            lwc1(f0, sp, 0x58);
            swc1(f2, s0, 112);
            swc1(f1, s0, 116);
            swc1(f0, s0, 120);
            sb(zero, s0, 124);
            sb(s1, s0, 125);
            sw(s2, s0, 128);
            sw(zero, s0, 132);
            v0 = 1;
        } else {
            // 0x003b8b94
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x003b8b68
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003b8c08 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x003B91C0 sub_3B91C0 -- 160 bytes; frame 0x70: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// Forwards to sub_3B8FF0(camera, a1..a5) on the active camera record (sub_3B5D10); 0 without one.
void sub_3B91C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f20{ctx, 20};
    // 0x003b91c0
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s4 = a1;
    s3 = a2;
    s2 = a3;
    s1 = t0;
    s0 = t1;
    mov_s(f20, f12);
    jal(ctx, 0x3B91F8u, gen::fn_sub_3B5D10_003b5d10);
    if (v0 == 0) {
        // 0x003b9234
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003b9208
        charge(ctx, 11);
        a0 = v0;
        a1 = s4;
        a2 = s3;
        a3 = s2;
        t0 = s1;
        t1 = s0;
        mov_s(f12, f20);
        jal(ctx, 0x3B9224u, gen::fn_sub_3B8FF0_003b8ff0);
    }
    // 0x003b9238 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x003B9320 sub_3B9320 -- 160 bytes; frame 0x70: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// Forwards to sub_3B9260(camera, a1..a5) on the active camera record (sub_3B5D10); 0 without one.
void sub_3B9320(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f20{ctx, 20};
    // 0x003b9320
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s4 = a1;
    s3 = a2;
    s2 = a3;
    s1 = t0;
    s0 = t1;
    mov_s(f20, f12);
    jal(ctx, 0x3B9358u, gen::fn_sub_3B5D10_003b5d10);
    if (v0 == 0) {
        // 0x003b9394
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003b9368
        charge(ctx, 11);
        a0 = v0;
        a1 = s4;
        a2 = s3;
        a3 = s2;
        t0 = s1;
        t1 = s0;
        mov_s(f12, f20);
        jal(ctx, 0x3B9384u, gen::fn_sub_3B9260_003b9260);
    }
    // 0x003b9398 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x003B9550 sub_3B9550 -- 80 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Forwards to sub_3B9500(camera, a1) on the active camera record (sub_3B5D10); 0 without one.
void sub_3B9550(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b9550
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    jal(ctx, 0x3B9560u, gen::fn_sub_3B5D10_003b5d10);
    if (v0 == 0) {
        // 0x003b9588
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003b9570
        charge(ctx, 6);
        a0 = v0;
        a1 = s0;
        jal(ctx, 0x3B9578u, gen::fn_sub_3B9500_003b9500);
    }
    // 0x003b958c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003BB010 sub_3BB010 -- 80 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Forwards to sub_3BAC40(camera, a1) on the active camera record (sub_3B5D10); 0 without one.
void sub_3BB010(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003bb010
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    jal(ctx, 0x3BB020u, gen::fn_sub_3B5D10_003b5d10);
    if (v0 == 0) {
        // 0x003bb048
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003bb030
        charge(ctx, 6);
        a0 = v0;
        a1 = s0;
        jal(ctx, 0x3BB038u, gen::fn_sub_3BAC40_003bac40);
    }
    // 0x003bb04c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003BB1D0 sub_3BB1D0 -- 176 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Fills the 10-byte block at camera+168 of the active camera record (sub_3B5D10): +0 = a1, +1 = 0, +2 = a2, +6 = a3,
// +8 = a4; returns 1 (0 without a camera).
void sub_3BB1D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003bb1d0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a1;
    s3 = a2;
    s2 = a3;
    s1 = t0;
    jal(ctx, 0x3BB1FCu, gen::fn_sub_3B5D10_003b5d10);
    if (v0 != 0) {
        // 0x003bb218
        charge(ctx, 2);
        if (v0 != 0) {
            // 0x003bb22c
            charge(ctx, 12);
            s0 = addiu(v0, 168);
            a0 = s0;
            a1 = 0;
            a2 = 10;
            jal(ctx, 0x3BB23Cu, gen::fn_memset_00521408);
            sb(s4, s0, 0);
            sb(zero, s0, 1);
            sb(s3, s0, 2);
            sh(s2, s0, 6);
            sh(s1, s0, 8);
            v0 = 1;
        } else {
            // 0x003bb220
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x003bb20c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003bb25c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x003BCC80 sub_3BCC80 -- 36 bytes; frame 0x10: ra sp+0x0
// Clears the u16 at 0x7CE658 and tail-calls sub_3500E0.
void sub_3BCC80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003bcc80
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    sh(zero, gp, -18072);  // 0x7CE658
    jal(ctx, 0x3BCC8Cu, gen::fn_sub_3500E0_003500e0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003C77A0 sub_3C77A0 -- 168 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// fclMisc.c fclDestroyMessage: logs "[fclMisc.c:344] fclDestroyMessage", then for the field message record
// (sub_3C7D50) destroys its message handle (itfMesMngDestroyHandle; handle = -1, bytes +4/+5 = 0) and calls
// sub_3CF440. Returns 1, or 0 without a record.
void sub_3C77A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c77a0
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x3C77ACu, gen::fn_sub_3C7D50_003c7d50);
    s0 = v0;
    a0 = addiu(gp, -22008);  // "[%s:%d]"
    a1 = 0x6A0000;
    a1 = addiu(a1, 15896);  // "fclMisc.c"
    a2 = 344;
    jal(ctx, 0x3C77C8u, gen::fn_printf_005225a8);
    a0 = 0x6A0000;
    a0 = addiu(a0, 15920);  // "fclDestroyMessage\n"
    jal(ctx, 0x3C77D8u, gen::fn_printf_005225a8);
    a0 = 0x6A0000;
    a0 = addiu(a0, 15920);  // "fclDestroyMessage\n"
    jal(ctx, 0x3C77E8u, gen::fn_sub_1052B0_001052b0);
    if (s0 != 0) {
        // 0x003c7804
        charge(ctx, 3);
        lw(a0, s0, 0);
        if (i64(a0) >= 0) {
            // 0x003c7810
            charge(ctx, 6);
            jal(ctx, 0x3C7810u, gen::fn_itfMesMngDestroyHandle_003a3060);
            v0 = si(-1);
            sw(v0, s0, 0);
            sb(zero, s0, 4);
            sb(zero, s0, 5);
        }
        // 0x003c7828
        charge(ctx, 3);
        jal(ctx, 0x3C7828u, gen::fn_sub_3CF440_003cf440);
        v0 = 1;
    } else {
        // 0x003c77f8
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003c7834 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003C7B90 sub_3C7B90 -- 36 bytes; frame 0x10: ra sp+0x0
// Wrapper: sub_3C7990(1).
void sub_3C7B90(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c7b90
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 1;
    jal(ctx, 0x3C7B9Cu, gen::fn_sub_3C7990_003c7990);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003C7BC0 sub_3C7BC0 -- 84 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Forwards to sub_3A4220(handle, a0, a1) on the field message record's handle (sub_3C7D50).
void sub_3C7BC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c7bc0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    jal(ctx, 0x3C7BD8u, gen::fn_sub_3C7D50_003c7d50);
    if (v0 != 0) {
        // 0x003c7be8
        charge(ctx, 5);
        lw(a0, v0, 0);
        a1 = s1;
        a2 = s0;
        jal(ctx, 0x3C7BF4u, gen::fn_sub_3A4220_003a4220);
    }
    // 0x003c7bfc (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003C7C20 sub_3C7C20 -- 100 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Forwards to sub_3A4010(handle, a0, a1, a2) on the field message record's handle (sub_3C7D50).
void sub_3C7C20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c7c20
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s0 = a2;
    jal(ctx, 0x3C7C40u, gen::fn_sub_3C7D50_003c7d50);
    if (v0 != 0) {
        // 0x003c7c50
        charge(ctx, 6);
        lw(a0, v0, 0);
        a1 = s2;
        a2 = s1;
        a3 = s0;
        jal(ctx, 0x3C7C60u, gen::fn_sub_3A4010_003a4010);
    }
    // 0x003c7c68 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003C7D80 sub_3C7D80 -- 68 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Initialises a message manager (itfMesMngInitialize(a1)) and stores its handle in slot a0 of dword_6A3E50.
void sub_3C7D80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c7d80
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = a1;
    jal(ctx, 0x3C7D94u, gen::fn_itfMesMngInitialize_003a2d80);
    a0 = sll(s0, 2);
    v1 = 0x6A0000;
    v1 = addiu(v1, 15952);  // &0x6A3E50
    v1 = addu(v1, a0);
    sw(v0, v1, 0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003C7E20 sub_3C7E20 -- 48 bytes; frame 0x10: ra sp+0x0
// Wrapper: sub_3C7E50(a0..a4, 1, a5, a6) (the sixth argument forced to 1).
void sub_3C7E20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c7e20
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v0 = t1;
    t3 = t2;
    t1 = 1;
    t2 = v0;
    jal(ctx, 0x3C7E38u, gen::fn_sub_3C7E50_003c7e50);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003C8F70 sub_3C8F70 -- 48 bytes; frame 0x10: ra sp+0x0
// sub_109F60(2, 0) then tail-calls sub_3C8FA0.
void sub_3C8F70(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c8f70
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 2;
    a1 = 0;
    jal(ctx, 0x3C8F80u, gen::fn_sub_109F60_00109f60);
    jal(ctx, 0x3C8F88u, gen::fn_sub_3C8FA0_003c8fa0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003C94E0 sub_3C94E0 -- 136 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Shuffle message window open: resets the record at 0x95BE90 (handle -1, flags) and, when no handle is open,
// initialises one (itfMesMngInitialize) with mode 6 (sub_3A4360). Returns 1 on a new handle, 0 when one exists.
void sub_3C94E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c94e0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = 0x960000;
    s0 = addiu(s0, -16752);  // &0x95BE90
    if (s0 != 0) {
        // 0x003c94fc
        charge(ctx, 8);
        v0 = si(-1);
        sw(v0, s0, 0);
        sb(zero, s0, 4);
        sb(zero, s0, 5);
        sw(v0, s0, 8);
        v0 = 1;
        sb(v0, s0, 12);
        sb(v0, s0, 13);
    }
    // 0x003c951c
    charge(ctx, 3);
    lw(v0, s0, 0);
    if (i64(v0) >= 0) {
        // 0x003c9550
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003c9528
        charge(ctx, 10);
        jal(ctx, 0x3C9528u, gen::fn_itfMesMngInitialize_003a2d80);
        sw(v0, s0, 0);
        a0 = v0;
        a1 = 6;
        jal(ctx, 0x3C953Cu, gen::fn_sub_3A4360_003a4360);
        v0 = 1;
    }
    // 0x003c9554 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003C9790 sub_3C9790 -- 176 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Shuffle message request: on the open handle (0x95BE90), sets the state flags, requests message a0
// (itfMesMngRequestMessage), positions the window (sub_3C9570, sub_3A5210(h, 0, 0, 32, 0)), marks it shown (0x95BE94
// = 1) and clears the select word (-1). Returns 1, or 0 without a handle.
void sub_3C9790(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c9790
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = 0x960000;
    s0 = addiu(s0, -16752);  // &0x95BE90
    lw(a0, s0, 0);  // 0x95BE90
    if (i64(a0) >= 0) {
        // 0x003c97c4
        charge(ctx, 25);
        a1 = 0x200000;
        jal(ctx, 0x3C97C8u, gen::fn_itfMesMngSetStateFlags_003a3e10);
        lw(a0, s0, 0);
        a1 = s1;
        a2 = 0;
        jal(ctx, 0x3C97DCu, gen::fn_itfMesMngRequestMessage_003a30c0);
        lw(a0, s0, 0);
        jal(ctx, 0x3C97E8u, gen::fn_sub_3C9570_003c9570);
        lw(a0, s0, 0);
        a1 = 0;
        a2 = 0;
        a3 = 32;
        t0 = 0;
        jal(ctx, 0x3C9804u, gen::fn_sub_3A5210_003a5210);
        v0 = 1;
        sb(v0, s0, 4);
        lw(a0, s0, 0);
        a1 = si(-1);
        jal(ctx, 0x3C981Cu, gen::fn_itfMesMngSetSelectWord84_003a27c0);
        v0 = 1;
    } else {
        // 0x003c97b8
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003c9828 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003C9850 fclMisc_CreatePsStatusTasks -- 596 bytes; frame 0xC0: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// fclMisc.c psStatus start: allocates and clears the status work (0x960178 allocator), copies the defaults from
// off_6A4040 / off_6A4060, creates the "psStatus" / "psStatusDrawLow" / "psStatusDrawHigh" tasks (kwlnTaskCreate with
// fclMisc_UpdatePsStatusTask, the draw tasks and sub_3CA6B0) and logs "psStatusStart".
void fclMisc_CreatePsStatusTasks(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x003c9850
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
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
    if (i64(s3) >= 0) {
        // 0x003c9884
        charge(ctx, 3);
        v0 = slti(s3, 5);
        if (v0 == 0) {
            goto L_003c9890;
        }
        goto L_003c98a4;
    }
L_003c9890:
    charge(ctx, 5);
    a0 = 0x6A0000;
    a0 = addiu(a0, 15896);  // "fclMisc.c"
    a1 = 1633;
    jal(ctx, 0x3C989Cu, gen::fn_sub_19D3F0_0019d3f0);
L_003c98a4:
    charge(ctx, 4);
    a1 = 0x6A0000;
    a1 = addiu(a1, 16448);  // &0x6A4040
    a0 = addiu(sp, 0xA0);
    v1 = 5;
    for (;;) {
        // 0x003c98b4
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
    // 0x003c98d0
    charge(ctx, 4);
    a1 = 0x6A0000;
    a1 = addiu(a1, 16480);  // &0x6A4060
    a0 = addiu(sp, 0x60);
    v1 = 15;
    for (;;) {
        // 0x003c98e0
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
    // 0x003c98fc
    charge(ctx, 33);
    a0 = 236;
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x3C990Cu, v0.u());
    s0 = v0;
    a0 = s0;
    a1 = 0;
    a2 = 236;
    jal(ctx, 0x3C9924u, gen::fn_memset_00521408);
    v0 = 1;
    sw(v0, s0, 4);
    sw(s3, s0, 0);
    v0 = sll(s3, 2);
    v0 = addu(v0, sp);
    lw(v0, v0, 160);
    sw(v0, s0, 204);
    v0 = sll(s3, 1);
    v0 = addu(v0, s3);
    v0 = sll(v0, 2);
    v0 = addu(v0, sp);
    a0 = addiu(s0, 220);
    a1 = addiu(v0, 96);
    a2 = 12;
    jal(ctx, 0x3C9964u, gen::fn_memcpy_00521250);
    sh(s2, s0, 12);
    sh(s1, s0, 14);
    lh(v0, s0, 12);
    if (i64(v0) <= 0) {
        // 0x003c9980
        charge(ctx, 2);
        v0 = 1;
        sh(v0, s0, 12);
    }
    // 0x003c9988
    charge(ctx, 3);
    lh(v0, s0, 14);
    if (i64(v0) <= 0) {
        // 0x003c9994
        charge(ctx, 2);
        v0 = 1;
        sh(v0, s0, 14);
    }
    // 0x003c999c
    charge(ctx, 66);
    v0 = si(-1);
    sw(v0, s0, 24);
    a0 = s4;
    a1 = 0x6A0000;
    a1 = addiu(a1, 16544);  // "psStatus"
    a2 = 10;
    a3 = 0x3D0000;
    a3 = addiu(a3, -24016);  // &fclMisc_UpdatePsStatusTask
    t0 = 0x3D0000;
    t0 = addiu(t0, -22864);  // &sub_3CA6B0
    t1 = s0;
    jal(ctx, 0x3C99C8u, gen::fn_kwlnTaskCreate_00194b20);
    s1 = v0;
    a0 = s1;
    a1 = 0x6A0000;
    a1 = addiu(a1, 16560);  // "psStatusDrawLow"
    a2 = 4208;
    a3 = 0x3D0000;
    a3 = addiu(a3, -23024);  // &fclMisc_UpdatePsStatusDrawLowTask
    t0 = 0;
    t1 = s0;
    jal(ctx, 0x3C99F4u, gen::fn_kwlnTaskCreate_00194b20);
    a0 = s1;
    a1 = 0x6A0000;
    a1 = addiu(a1, 16576);  // "psStatusDrawHigh"
    a2 = 6314;
    a3 = 0x3D0000;
    a3 = addiu(a3, -22944);  // &fclMisc_UpdatePsStatusDrawHighTask
    t0 = 0;
    t1 = s0;
    jal(ctx, 0x3C9A1Cu, gen::fn_kwlnTaskCreate_00194b20);
    mtc1(zero, f12);
    a0 = s1;
    a1 = 5256;
    a2 = 0;
    a3 = si(-1);
    jal(ctx, 0x3C9A38u, gen::fn_sub_1339A0_001339a0);
    sw(v0, s0, 196);
    a0 = addiu(gp, -22008);  // "[%s:%d]"
    a1 = 0x6A0000;
    a1 = addiu(a1, 15896);  // "fclMisc.c"
    a2 = 1660;
    jal(ctx, 0x3C9A54u, gen::fn_printf_005225a8);
    a0 = 0x6A0000;
    a0 = addiu(a0, 16600);  // "psStatusStart\n"
    jal(ctx, 0x3C9A64u, gen::fn_printf_005225a8);
    a0 = 0x6A0000;
    a0 = addiu(a0, 16600);  // "psStatusStart\n"
    jal(ctx, 0x3C9A74u, gen::fn_sub_1052B0_001052b0);
    v0 = s1;
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xC0);
}

// 0x003C9AB0 sub_3C9AB0 -- 80 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Returns bit 0x20 of the psStatus work flags (+8) of the task a0 (kwlnTaskGetWorkData; fclMisc.c:1667 assert on a
// null work).
void sub_3C9AB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c9ab0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x3C9ABCu, gen::fn_kwlnTaskGetWorkData_00195540);
    s0 = v0;
    if (s0 == 0) {
        // 0x003c9ad0
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 15896);  // "fclMisc.c"
        a1 = 1667;
        jal(ctx, 0x3C9ADCu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003c9ae4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v0, s0, 8);
    v0 = v0 & 0x20;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003C9D00 sub_3C9D00 -- 120 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// psStatusSetStateON: ORs a1 into the psStatus work flags (+8) of the task a0 and logs it ("[fclMisc.c:1715]").
void sub_3C9D00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c9d00
    enter(ctx, 30);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    jal(ctx, 0x3C9D10u, gen::fn_kwlnTaskGetWorkData_00195540);
    lw(v1, v0, 8);
    v1 = v1 | s0;
    sw(v1, v0, 8);
    a0 = addiu(gp, -22008);  // "[%s:%d]"
    a1 = 0x6A0000;
    a1 = addiu(a1, 15896);  // "fclMisc.c"
    a2 = 1715;
    jal(ctx, 0x3C9D34u, gen::fn_printf_005225a8);
    a0 = 0x6A0000;
    a0 = addiu(a0, 16624);  // "psStatusSetStateON %d\n"
    a1 = s0;
    jal(ctx, 0x3C9D48u, gen::fn_printf_005225a8);
    a0 = 0x6A0000;
    a0 = addiu(a0, 16624);  // "psStatusSetStateON %d\n"
    a1 = s0;
    jal(ctx, 0x3C9D5Cu, gen::fn_sub_1052B0_001052b0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00464120 sub_464120 -- 344 bytes; frame 0xD0: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Builds a bounding sphere / volume for a scene object by its kind (+24): kind 5 takes the atomic's world bounding
// sphere (atomicGetWorldBoundingSphere), 3 uses the record itself, others go through sub_4CB2F0 / sub_4C32A0 /
// sub_4C6C20 / sub_463490 / sub_461EA0; the result feeds sub_463F20.
void sub_464120(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x00464120
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0xD0);
    v0 = 5;
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    s2 = a1;
    sq(s0, sp, 0x0);
    s1 = a2;
    lw(v1, a1, 24);
    s0 = a3;
    if (v1 == v0) {
        // 0x00464214
        charge(ctx, 17);
        link(ctx, 0x464214u);  // $ra first: the delay slot below depends on it
        lw(a0, s2, 0);
        call(ctx, gen::fn_atomicGetWorldBoundingSphere_004912b0);
        lwc1(f3, v0, 0);
        a2 = s2;
        lwc1(f2, v0, 4);
        a3 = s1;
        lwc1(f1, v0, 8);
        t0 = s0;
        lwc1(f0, v0, 12);
        a1 = addiu(sp, 0xC0);
        a0 = s3;
        swc1(f3, sp, 0xC0);
        swc1(f2, sp, 0xC4);
        swc1(f1, sp, 0xC8);
        link(ctx, 0x46424Cu);  // $ra first: the delay slot below depends on it
        swc1(f0, sp, 0xCC);
        call(ctx, gen::fn_sub_463F20_00463f20);
        v0 = s3;
    L_00464258:
        charge(ctx, 1);
        ld(ra, sp, 0x50);
    } else {
        // 0x00464158
        charge(ctx, 3);
        v0 = 3;
        if (v1 == v0) {
            // 0x004641fc
            charge(ctx, 6);
            a2 = s2;
            a3 = s1;
            t0 = s0;
            jal(ctx, 0x464204u, gen::fn_sub_463F20_00463f20);
            v0 = s3;
            goto L_00464258;
        }
        // 0x00464164
        charge(ctx, 3);
        v0 = 1;
        if (v1 != v0) {
            // 0x00464170
            charge(ctx, 2);
            v0 = s3;
            goto L_00464258;
        }
        // 0x00464178
        charge(ctx, 15);
        lw(s4, s3, 24);
        link(ctx, 0x46417Cu);  // $ra first: the delay slot below depends on it
        lw(a0, s3, 4);
        call(ctx, gen::fn_sub_4CB2F0_004cb2f0);
        a1 = v0;
        a0 = addiu(sp, 0x80);
        jal(ctx, 0x464188u, gen::fn_sub_4C32A0_004c32a0);
        a0 = addiu(sp, 0x60);
        a1 = s2;
        a2 = 2;
        a3 = addiu(sp, 0x80);
        jal(ctx, 0x46419Cu, gen::fn_sub_4C6C20_004c6c20);
        lw(v0, s4, 24);
        at = slti(v0, 2);
        if (at != 0) {
            // 0x004641d8
            charge(ctx, 7);
            a0 = s4;
            a2 = s2;
            a3 = s1;
            t0 = s0;
            a1 = addiu(sp, 0x60);
            jal(ctx, 0x4641E8u, gen::fn_sub_461EA0_00461ea0);
            v0 = s3;
        } else {
            // 0x004641b4
            charge(ctx, 9);
            a0 = s4;
            a3 = s2;
            t0 = s1;
            t1 = s0;
            a1 = addiu(s3, 76);
            a2 = addiu(sp, 0x60);
            jal(ctx, 0x4641C8u, gen::fn_sub_463490_00463490);
            v0 = s3;
        }
        // 0x004641f4
        charge(ctx, 2);
        ld(ra, sp, 0x50);
    }
    // 0x0046425c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xD0);
}

// 0x0048EE80 sub_48EE80 -- 72 bytes; leaf frame (no stack)
// Counts the non-null entries (+12) of the plugin array attached to a0 (plugin offset at 0x7CE7E0; count at +0,
// 16-byte entries at *(+4)).
void sub_48EE80(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28};
    // 0x0048ee80
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(v1, gp, -17680);  // 0x7CE7E0
    v0 = 0;
    v1 = addu(a0, v1);
    lw(a0, v1, 0);
    at = slt(0, a0);
    a2 = 0;
    if (at != 0) {
        // 0x0048ee9c
        charge(ctx, 1);
        lw(a1, v1, 4);
        for (;;) {
            // 0x0048eea0
            charge(ctx, 3);
            lw(v1, a1, 12);
            if (v1 != 0) {
                // 0x0048eeac
                charge(ctx, 1);
                v0 = addiu(v0, 1);
            }
            // 0x0048eeb0
            charge(ctx, 4);
            a2 = addiu(a2, 1);
            v1 = slt(a2, a0);
            a1 = addiu(a1, 16);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0048eec0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0048EED0 sub_48EED0 -- 52 bytes; leaf frame (no stack)
// Returns the a1-th 16-byte entry of the plugin array attached to a0 (offset at 0x7CE7E0), or 0 when a1 is not below
// its count.
void sub_48EED0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x0048eed0
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v0, gp, -17680);  // 0x7CE7E0
    a0 = addu(a0, v0);
    lw(v0, a0, 0);
    at = slt(a1, v0);
    if (at == 0) {
        // 0x0048eef8
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x0048eee8
        charge(ctx, 4);
        lw(v0, a0, 4);
        v1 = sll(a1, 4);
        v0 = addu(v0, v1);
    }
    // 0x0048eefc (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x004916D0 sub_4916D0 -- 132 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// RpClump-style atomic iterator: walks the clump's atomic list (head a0+8, link at atomic+64) calling the callback
// a1(atomic, a2) until it returns 0; returns a0.
void sub_4916D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004916d0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    s3 = a1;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = addiu(s4, 8);
    lw(v0, a0, 8);
    s2 = a2;
    if (v0 != s1) {
        for (;;) {
            // 0x00491704
            charge(ctx, 6);
            lw(s0, v0, 0);
            a0 = addiu(v0, -64);
            a1 = s2;
            jalr(ctx, 0x49170Cu, s3.u());
            if (v0 == 0) {
                goto L_0049171c_2;
            }
            // 0x00491724
            charge(ctx, 2);
            v0 = s0;
            if (s0 == s1) {
                break;
            }
            backedge(ctx);
        }
        // 0x0049172c
        charge(ctx, 1);
    }
    // 0x00491730
    charge(ctx, 1);
    v0 = s4;
    // 0x00491734 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
L_0049171c_2:
    charge(ctx, 2);
    v0 = s4;
    // 0x00491734 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00491EA0 sub_491EA0 -- 328 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Clump destroy (j_RpClumpDestroy): runs the plugin destructors (sub_4C6560 on 0x77DD00), destroys every atomic
// (sub_491A80), light and camera in its lists, the frame hierarchy (sub_4CA030 / sub_4CB1B0) and frees the clump
// through the 0x96018C free list.
void sub_491EA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00491ea0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 0x780000;
    a1 = s0;
    a0 = addiu(a0, -8960);  // &0x77DD00
    jal(ctx, 0x491EC4u, gen::fn_sub_4C6560_004c6560);
    lw(s3, s0, 8);
    s2 = addiu(s0, 8);
    if (s3 != s2) {
        for (;;) {
            // 0x00491edc
            charge(ctx, 6);
            s1 = addiu(s3, -64);
            lw(s3, s3, 0);
            a0 = s1;
            jal(ctx, 0x491EE4u, gen::fn_sub_491A80_00491a80);
            if (s1 == 0) {
                break;
            }
            // 0x00491ef4
            charge(ctx, 2);
            if (s3 == s2) {
                goto L_00491efc_3;
            }
            backedge(ctx);
        }
    }
L_00491f00:
    charge(ctx, 4);
    lw(s3, s0, 16);
    s1 = addiu(s0, 16);
    if (s3 != s1) {
        for (;;) {
            // 0x00491f10
            charge(ctx, 12);
            lw(v1, gp, -17628);  // 0x7CE814
            v0 = addiu(s3, -4);
            lw(s3, s3, 0);
            s2 = subu(v0, v1);
            v0 = addu(s2, v1);
            lw(a0, v0, 0);
            a1 = s2;
            jal(ctx, 0x491F28u, gen::fn_sub_492020_00492020);
            a0 = s2;
            jal(ctx, 0x491F30u, gen::fn_sub_494760_00494760);
            if (s2 != 0) {
                // 0x00491f40
                charge(ctx, 2);
                if (s3 != s1) {
                    backedge(ctx);
                    continue;
                }
            }
            break;
        }
    }
    // 0x00491f48
    charge(ctx, 4);
    lw(s3, s0, 24);
    s1 = addiu(s0, 24);
    if (s3 != s1) {
        for (;;) {
            // 0x00491f58
            charge(ctx, 12);
            lw(v1, gp, -17632);  // 0x7CE810
            v0 = addiu(s3, -4);
            lw(s3, s3, 0);
            s2 = subu(v0, v1);
            v0 = addu(s2, v1);
            lw(a0, v0, 0);
            a1 = s2;
            jal(ctx, 0x491F70u, gen::fn_sub_492060_00492060);
            a0 = s2;
            jal(ctx, 0x491F78u, gen::fn_sub_4CA030_004ca030);
            if (s2 != 0) {
                // 0x00491f88
                charge(ctx, 2);
                if (s3 != s1) {
                    backedge(ctx);
                    continue;
                }
            }
            break;
        }
    }
    // 0x00491f90
    charge(ctx, 3);
    lw(a0, s0, 4);
    if (a0 != 0) {
        // 0x00491f9c
        charge(ctx, 2);
        jal(ctx, 0x491F9Cu, gen::fn_sub_4CB1B0_004cb1b0);
    }
    // 0x00491fa4
    charge(ctx, 17);
    lw(a0, gp, -17616);  // 0x7CE820
    v1 = 0x960000;
    v1 = addiu(v1, 112);  // &0x960070
    v0 = 0x960000;
    lw(v0, v0, 396);  // 0x96018C
    v1 = addu(v1, a0);
    lw(a0, v1, 4);
    a1 = s0;
    jalr(ctx, 0x491FC0u, v0.u());
    ld(ra, sp, 0x40);
    v0 = 1;
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
    return;
L_00491efc_3:
    charge(ctx, 1);
    goto L_00491f00;
}

// 0x004932C0 sub_4932C0 -- 168 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Array iterator: calls a1(entry, a2) for each of the a0+36 pointers at *(a0+32) until one returns 0; returns a0.
void sub_4932C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004932c0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    s4 = a1;
    sq(s2, sp, 0x20);
    s3 = a2;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, 36);
    v0 = slt(0, s0);
    s2 = 0;
    if (v0 != 0) {
        // 0x00493304
        charge(ctx, 1);
        s1 = 0;
        for (;;) {
            // 0x00493308
            charge(ctx, 7);
            lw(v0, s5, 32);
            v0 = addu(v0, s1);
            lw(a0, v0, 0);
            a1 = s3;
            jalr(ctx, 0x493314u, s4.u());
            if (v0 == 0) {
                goto L_00493324_4;
            }
            // 0x0049332c
            charge(ctx, 4);
            s2 = addiu(s2, 1);
            v0 = slt(s2, s0);
            s1 = addiu(s1, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0049333c
        charge(ctx, 2);
        backedge(ctx);
    }
    // 0x004932fc
    charge(ctx, 2);
    v0 = s5;
    // 0x00493344 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
    return;
L_00493324_4:
    charge(ctx, 2);
    v0 = s5;
    // 0x00493344 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x004AA410 sub_4AA410 -- 300 bytes; leaf frame (no stack)
// Sets the active immediate-mode camera (dword_95EF84) from a0: raster size from its frame buffer (+96), 2x the view
// window (+104 / +108), installs the begin-update hook sub_4A9BE0 (saving the old one in dword_95EFD0) and resets the
// batch state; a0 = 0 clears it.
void sub_4AA410(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x004aa410
    enter(ctx, 2);  // entry check point + this block's cycles
    if (a0 == 0) {
        // 0x004aa528
        charge(ctx, 3);
        v0 = 0x960000;
        sw(a0, v0, -4220);  // 0x95EF84
        backedge(ctx);
    L_004aa4fc:
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004aa418
        charge(ctx, 3);
        lw(v0, a0, 96);
        if (v0 == 0) {
            goto L_004aa4fc;
        }
        // 0x004aa424
        charge(ctx, 23);
        lwc1(f0, v0, 16);
        a3 = 0x4B0000;
        lwc1(f2, v0, 12);
        a1 = 0x960000;
        a2 = 0x960000;
        v1 = 0x960000;
        a3 = addiu(a3, -25632);  // &sub_4A9BE0
        cvt_s_w(f0, f0);
        v0 = 0x40000000;
        swc1(f0, a1, -4480);  // 0x95EE80
        cvt_s_w(f0, f2);
        swc1(f0, a2, -4484);  // 0x95EE7C
        lwc1(f0, a0, 104);
        mtc1(v0, f1);
        v0 = 0x960000;
        mul_s(f0, f1, f0);
        swc1(f0, v1, -4492);  // 0x95EE74
        lwc1(f0, a0, 108);
        mul_s(f0, f1, f0);
        swc1(f0, v0, -4488);  // 0x95EE78
        lw(v1, a0, 28);
        if (v1 != a3) {
            // 0x004aa480
            charge(ctx, 4);
            v0 = 0x960000;
            lw(v0, v0, -4220);  // 0x95EF84
            if (v0 != a0) {
                // 0x004aa490
                charge(ctx, 3);
                v0 = 0x960000;
                sw(v1, v0, -4144);  // 0x95EFD0
                sw(a3, a0, 28);
            }
        }
        // 0x004aa49c
        charge(ctx, 14);
        v0 = 0x960000;
        v1 = 0x960000;
        sw(a0, v0, -4220);  // 0x95EF84
        v0 = 0x960000;
        sw(zero, v1, -4272);  // 0x95EF50
        sw(zero, v0, -4240);  // 0x95EF70
        v1 = 0x960000;
        v0 = 0x960000;
        lwc1(f1, v0, -4488);  // 0x95EE78
        v0 = 0x960000;
        lwc1(f0, v0, -4492);  // 0x95EE74
        c_le_s(f0, f1);
        sw(zero, v1, -4236);  // 0x95EF74
        if (cond(ctx)) {
            // 0x004aa504
            charge(ctx, 9);
            div_s(f0, f1, f0);
            v0 = 0x960000;
            a0 = 0x3F800000;
            v1 = 0x960000;
            sw(a0, v1, -4232);  // 0x95EF78
            swc1(f0, v0, -4228);  // 0x95EF7C
            backedge(ctx);
        } else {
            // 0x004aa4d4
            charge(ctx, 8);
            div_s(f0, f0, f1);
            v1 = 0x960000;
            a0 = 0x3F800000;
            v0 = 0x960000;
            sw(a0, v0, -4228);  // 0x95EF7C
            swc1(f0, v1, -4232);  // 0x95EF78
        }
        // 0x004aa4f4
        charge(ctx, 2);
        v0 = 1;
    }
    // 0x004aa534 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x004AAA60 sub_4AAA60 -- 216 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Pushes the 8 x 8-byte matrix state onto the stack at dword_95EDF0 (depth dword_95EE70 < 31, allocating a level with
// sub_4C38C0 on first use); returns 1 when pushed.
void sub_4AAA60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004aaa60
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x960000;
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, v0, -4496);  // 0x95EE70
    s0 = slti(v0, 31);
    if (s0 != 0) {
        // 0x004aaa80
        charge(ctx, 10);
        v1 = addiu(v0, 1);
        v0 = 0x960000;
        sw(v1, v0, -4496);  // 0x95EE70
        v0 = 0x960000;
        v1 = sll(v1, 2);
        v0 = addiu(v0, -4624);  // &0x95EDF0
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        if (v0 == 0) {
            // 0x004aab00
            charge(ctx, 10);
            jal(ctx, 0x4AAB00u, gen::fn_sub_4C38C0_004c38c0);
            v1 = 0x960000;
            a0 = 0x960000;
            lw(v1, v1, -4496);  // 0x95EE70
            a0 = addiu(a0, -4624);  // &0x95EDF0
            v1 = sll(v1, 2);
            v1 = addu(a0, v1);
            sw(v0, v1, 0);
            backedge(ctx);
        }
        // 0x004aaaa8
        charge(ctx, 12);
        v0 = 0x960000;
        v1 = 0x960000;
        lw(a1, v0, -4496);  // 0x95EE70
        v1 = addiu(v1, -4628);  // &0x95EDEC
        a0 = 8;
        v0 = 0x960000;
        a1 = sll(a1, 2);
        v0 = addiu(v0, -4624);  // &0x95EDF0
        v1 = addu(v1, a1);
        v0 = addu(v0, a1);
        lw(a2, v1, 0);
        lw(a1, v0, 0);
        for (;;) {
            // 0x004aaad8
            charge(ctx, 8);
            lw(v1, a2, 0);
            a0 = addiu(a0, -1);
            lw(v0, a2, 4);
            sw(v1, a1, 0);
            a2 = addiu(a2, 8);
            sw(v0, a1, 4);
            a1 = addiu(a1, 8);
            if (i64(a0) <= 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004aaaf8
    charge(ctx, 2);
    v0 = s0;
    // 0x004aab28
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x004B3710 sub_4B3710 -- 8 bytes; leaf frame (no stack)
// Returns its second argument ($a1); a do-nothing plugin callback.
void sub_4B3710(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a1{ctx, 5};
    // 0x004b3710
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = a1;
}

// 0x004B6EB0 sub_4B6EB0 -- 16 bytes; leaf frame (no stack)
// Tail-calls the 0x96017C free hook.
void sub_4B6EB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x004b6eb0
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    tail(ctx, v0.u());  // jr: the target's entry point
}

// 0x004C1D50 sub_4C1D50 -- 272 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Creates a 20-byte-per-entry free list of a0 entries (0x960178 allocator, flags a1 | 0x1000000); on failure logs the
// RW out-of-memory error (sub_4C1D10 / sub_4C1C50), frees the header and returns 0.
void sub_4C1D50(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c1d50
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    s2 = a1;
    sq(s0, sp, 0x0);
    a0 = 16;
    s0 = 0x960000;
    s0 = addiu(s0, 376);  // &0x960178
    lw(v0, s0, 0);  // 0x960178
    a1 = 0x30000;
    jalr(ctx, 0x4C1D80u, v0.u());
    s1 = v0;
    if (s1 == 0) {
        // 0x004c1dd8
        charge(ctx, 11);
        v1 = 1;
        v0 = lui(0x8000);
        sw(v1, sp, 0x58);
        a0 = v0 | 0x13;
        a1 = 16;
        jal(ctx, 0x4C1DE8u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x5C);
        a0 = addiu(sp, 0x58);
        jal(ctx, 0x4C1DF4u, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
    } else {
        // 0x004c1d94
        charge(ctx, 15);
        sw(zero, s1, 4);
        v0 = 20;
        sw(v0, s1, 8);
        sw(s3, s1, 12);
        lw(v1, s1, 8);
        lw(v0, s1, 12);
        mult(a0, v1, v0);
        lw(v0, s0, 0);
        v1 = 0x1000000;
        a1 = s2 | v1;
        jalr(ctx, 0x4C1DB8u, v0.u());
        sw(v0, s1, 0);
        lw(v0, s1, 0);
        if (v0 == 0) {
            // 0x004c1e04
            charge(ctx, 16);
            v0 = 1;
            sw(v0, sp, 0x50);
            lw(v1, s1, 8);
            lw(v0, s1, 12);
            mult(a1, v1, v0);
            v0 = lui(0x8000);
            a0 = v0 | 0x13;
            jal(ctx, 0x4C1E1Cu, gen::fn_sub_4C1D10_004c1d10);
            sw(v0, sp, 0x54);
            a0 = addiu(sp, 0x50);
            jal(ctx, 0x4C1E28u, gen::fn_sub_4C1C50_004c1c50);
            v0 = 0x960000;
            lw(v0, v0, 380);  // 0x96017C
            a0 = s1;
            jalr(ctx, 0x4C1E38u, v0.u());
            v0 = 0;
        } else {
            // 0x004c1dd0
            charge(ctx, 2);
            v0 = s1;
        }
    }
    // 0x004c1e44 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x004C9D70 sub_4C9D70 -- 64 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Sets the camera far-plane value (+128 = $f12), updates the projection (sub_4C89A0) and, when the camera has a frame
// (+4), its frame (sub_4CB270). Returns a0.
void sub_4C9D70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x004c9d70
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    link(ctx, 0x4C9D80u);  // $ra first: the delay slot below depends on it
    swc1(f12, a0, 128);
    call(ctx, gen::fn_sub_4C89A0_004c89a0);
    lw(a0, s0, 4);
    if (a0 != 0) {
        // 0x004c9d94
        charge(ctx, 2);
        jal(ctx, 0x4C9D94u, gen::fn_sub_4CB270_004cb270);
    }
    // 0x004c9d9c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00502668 _sceMpegError -- 84 bytes; frame 0x20: ra sp+0x10
// libmpeg error dispatch: with a callback installed (+2152) and a decoder context (+12), calls
// _sceMpegDispatchMpegCallback with {0, message}; otherwise prints the message (_ErrMessage).
void _sceMpegError(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00502668
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    lw(v1, a0, 2152);
    if (v1 != 0) {
        // 0x0050267c
        charge(ctx, 2);
        if (a0 == 0) {
            goto L_005026a8;
        }
        // 0x00502684
        charge(ctx, 3);
        lw(v0, a0, 12);
        a0 = v1;
        if (v0 == 0) {
            goto L_005026a8;
        }
        // 0x00502690
        charge(ctx, 6);
        sw(a1, sp, 0x4);
        sw(zero, sp, 0x0);
        a1 = sp;
        jal(ctx, 0x502698u, gen::fn__sceMpegDispatchMpegCallback_00500d10);
        ld(ra, sp, 0x10);
        // 0x005026b4 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        sp = addiu(sp, 0x20);
        return;
    }
L_005026a8:
    charge(ctx, 3);
    a0 = a1;
    jal(ctx, 0x5026A8u, gen::fn__ErrMessage_005024f0);
    ld(ra, sp, 0x10);
    // 0x005026b4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x20);
}

// 0x005026C0 _sceMpegError1 -- 64 bytes; frame 0x120: s0 sp+0x100, ra sp+0x110
// libmpeg formatted error: sceSnprintf(buf[256], fmt a1, a2) then _sceMpegError(a0, buf).
void _sceMpegError1(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005026c0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x120);
    a3 = a2;
    sd(s0, sp, 0x100);
    a2 = a1;
    s0 = a0;
    a1 = 256;
    sd(ra, sp, 0x110);
    a0 = sp;
    jal(ctx, 0x5026DCu, gen::fn_sceSnprintf_00505d90);
    a0 = s0;
    a1 = sp;
    jal(ctx, 0x5026E8u, gen::fn__sceMpegError_00502668);
    ld(ra, sp, 0x110);
    ld(s0, sp, 0x100);
    sp = addiu(sp, 0x120);
}

// 0x00502E60 _sceRemoveIntcHandler -- 16 bytes; leaf frame (no stack)
// libkernel RemoveIntcHandler syscall wrapper.
void _sceRemoveIntcHandler(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00502e60
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 17;
    syscall(ctx, 0x502E64u);
}

// 0x00502FA0 _sceExitDeleteThread -- 16 bytes; leaf frame (no stack)
// libkernel ExitDeleteThread syscall wrapper.
void _sceExitDeleteThread(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00502fa0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 36;
    syscall(ctx, 0x502FA4u);
}

// 0x00508170 sceFsInit -- 520 bytes; frame 0x80: s0 sp+0x20, s1 sp+0x30, ra sp+0x70, s4 sp+0x60, s3 sp+0x50, s2 sp+0x40
// libfileio client init (sceFsInit): binds the IOP file server RPC (sceSifInitRpc / sceSifBindRpc with interrupts
// off), creates the iob semaphores (_sceFsIobSemaMK), installs the receive / power-off handlers and sends the init
// call (sceFsSifCallRpc).
void sceFsInit(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00508170
    enter(ctx, 30);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    a0 = 0;
    sd(s0, sp, 0x20);
    s0 = 0x970000;
    sd(s1, sp, 0x30);
    sd(ra, sp, 0x70);
    s1 = addiu(s0, -25472);  // &0x969C80
    sd(s4, sp, 0x60);
    sd(s3, sp, 0x50);
    link(ctx, 0x508194u);  // $ra first: the delay slot below depends on it
    sd(s2, sp, 0x40);
    call(ctx, gen::fn_sceSifInitRpc_005068a8);
    sw(zero, s0, -25472);  // 0x969C80
    link(ctx, 0x5081A0u);  // $ra first: the delay slot below depends on it
    sw(zero, s1, 4);  // 0x969C84
    call(ctx, gen::fn_DIntr_0050d3a0);
    a1 = 0x500000;
    a2 = 0x970000;
    a0 = lui(0x8000);
    s0 = v0;
    a1 = addiu(a1, 31800);  // &_sceFs_Rcv_Intr
    a2 = addiu(a2, -25536);  // &0x969C40
    a0 = a0 | 0x11;
    jal(ctx, 0x5081C0u, gen::fn_sub_506430_00506430);
    a1 = 0x510000;
    a0 = lui(0x8000);
    a1 = addiu(a1, -32472);  // &_sceFs_Poff_Intr
    a2 = s1;
    a0 = a0 | 0x13;
    jal(ctx, 0x5081D8u, gen::fn_sub_506430_00506430);
    s3 = 0x970000;
    if (s0 != 0) {
        // 0x005081e8
        charge(ctx, 4);
        s0 = addiu(s3, -25600);
        jal(ctx, 0x5081E8u, gen::fn_EIntr_0050d3f0);
        goto L_00508220;
    }
L_0050821c:
    charge(ctx, 1);
    s0 = addiu(s3, -25600);
L_00508220:
    charge(ctx, 7);
    a1 = lui(0x8000);
    a0 = s0;
    a1 = a1 | 0x1;
    a2 = 0;
    jal(ctx, 0x50822Cu, gen::fn_sceSifBindRpc_00507050);
    cc = i64(v0) < 0;  // the condition, before the delay slot changes it
    v0 = si(-22);
    if (!cc) {
        // 0x0050823c
        charge(ctx, 3);
        lw(v0, s0, 36);
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = 0x100000;
        if (cc) {
            backedge(ctx);
            // 0x005081f8
            charge(ctx, 2);
            v1 = si(-1);
            for (;;) {
                // 0x00508200
                charge(ctx, 7);
                v0 = addiu(v0, -1);
                if (v0 == v1) {
                    break;
                }
                backedge(ctx);
            }
            goto L_0050821c;
        }
        // 0x00508248
        charge(ctx, 10);
        s4 = 0x780000;
        jal(ctx, 0x508248u, gen::fn__sceFsIobSemaMK_00507960);
        link(ctx, 0x508250u);  // $ra first: the delay slot below depends on it
        lw(a0, s4, -2744);  // 0x77F548
        call(ctx, gen::fn__sceWaitSema_005031a0);
        v1 = 0x970000;
        v1 = addiu(v1, -26112);  // &0x969A00
        a0 = addiu(v1, 512);  // &0x969C00
        v0 = sltu(v1, a0);
        s2 = 0x970000;
        if (v0 == 0) {
            // 0x0050829c
            charge(ctx, 3);
            s1 = 0x970000;
            s0 = 0x970000;
            lw(a0, s4, -2744);
        } else {
            // 0x00508270
            charge(ctx, 2);
            s1 = 0x970000;
            s0 = 0x970000;
            for (;;) {
                // 0x00508278
                charge(ctx, 7);
                sw(zero, v1, 4);
                v1 = addiu(v1, 16);
                v0 = sltu(v1, a0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00508294
            charge(ctx, 2);
            lw(a0, s4, -2744);
        }
        // 0x005082a8
        charge(ctx, 19);
        s0 = addiu(s0, -28352);
        jal(ctx, 0x5082A8u, gen::fn__sceSignalSema_00503180);
        v1 = addiu(s1, -28288);
        a3 = addiu(s2, -31552);
        sw(v1, s2, -31552);
        a0 = addiu(s3, -25600);
        v1 = addiu(v1, 1088);
        a1 = 255;
        sw(v1, a3, 4);
        a2 = 0;
        sw(zero, sp, 0x0);
        t0 = 8;
        sw(zero, sp, 0x8);
        t1 = s0;
        t2 = 8;
        t3 = 0;
        jal(ctx, 0x5082E4u, gen::fn_sceFsSifCallRpc_00507ad8);
        a0 = 0x20000000;
        if (i64(v0) >= 0) {
            // 0x00508300
            charge(ctx, 22);
            v0 = addiu(s0, 4);
            v1 = s0 | a0;
            v0 = v0 | a0;
            a1 = 0x970000;
            t0 = addiu(a1, -25560);  // &0x969C28
            lwl(a0, v1, 3);
            lwr(a0, v1, 0);
            swl(a0, t0, 3);  // 0x969C2B
            swr(a0, t0, 0);  // 0x969C28
            lwl(v1, v0, 3);
            lwr(v1, v0, 0);
            swl(v1, sp, 0x13);
            swr(v1, sp, 0x10);
            a2 = 0x780000;
            a1 = 0x780000;
            lw(v1, sp, 0x10);
            a0 = 1;
            sw(a0, a1, -2756);  // 0x77F53C
            v0 = 0;
            v1 = v1 ^ 0x2;
            v1 = sltiu(v1, 1);
            sw(v1, a2, -2752);  // 0x77F540
        } else {
            // 0x005082f4
            charge(ctx, 3);
            v0 = lui(0xFFFE);
            v0 = v0 | 0xFFFF;
        }
    }
    // 0x00508358 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x70);
    ld(s4, sp, 0x60);
    ld(s3, sp, 0x50);
    ld(s2, sp, 0x40);
    ld(s1, sp, 0x30);
    ld(s0, sp, 0x20);
    sp = addiu(sp, 0x80);
}

// 0x00508670 sceOpen -- 656 bytes; frame 0x150: s0 sp+0x40, s7 sp+0xB0, fp sp+0xC0, s1 sp+0x50, ra sp+0xD0, s6 sp+0xA0, s5 sp+0x90, s4 sp+0x80, s3 sp+0x70, s2 sp+0x60
// libfileio sceOpen: initialises the client when needed, takes a free iob (new_iob), copies the path into the RPC
// buffer and calls the IOP open (sceFsSifCallRpc) under the "SceStdioOpenSema" semaphore; returns the fd or the IOP
// error.
void sceOpen(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00508670
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0x150);
    sd(s0, sp, 0x40);
    sd(s7, sp, 0xB0);
    s0 = a0;
    sd(fp, sp, 0xC0);
    s7 = a1;
    sd(s1, sp, 0x50);
    a0 = 0;
    sd(ra, sp, 0xD0);
    fp = 0x970000;
    sd(s6, sp, 0xA0);
    s1 = addiu(fp, -0x7B00);
    sd(s5, sp, 0x90);
    sd(s4, sp, 0x80);
    sd(s3, sp, 0x70);
    sd(s2, sp, 0x60);
    sd(a2, sp, 0x120);
    sd(a3, sp, 0x128);
    sd(t0, sp, 0x130);
    sd(t1, sp, 0x138);
    sd(t2, sp, 0x140);
    link(ctx, 0x5086C4u);  // $ra first: the delay slot below depends on it
    sd(t3, sp, 0x148);
    call(ctx, gen::fn__sceFsWaitS_00508048);
    v1 = 0x780000;
    lw(v0, v1, -2756);  // 0x77F53C
    if (v0 == 0) {
        // 0x005086dc
        charge(ctx, 2);
        jal(ctx, 0x5086DCu, gen::fn_sceFsInit_00508170);
    }
    // 0x005086e4
    charge(ctx, 4);
    jal(ctx, 0x5086E4u, gen::fn__fs_version_00508378);
    if (v0 == 0) {
        // 0x00508708
        charge(ctx, 5);
        jal(ctx, 0x508708u, gen::fn_new_iob_00507a50);
        s3 = v0;
        if (s3 != 0) {
            lbu(v1, s0, 0);
            // 0x0050872c
            charge(ctx, 5);
            a2 = 0;
            lw(t0, sp, 0x120);
            v0 = sll(v1, 24);
            sb(v1, s1, 20);
            if (v0 == 0) {
                // 0x00508784
                charge(ctx, 5);
                a3 = 0x970000;
                a1 = 0x7C0000;
                s2 = addiu(sp, 0x30);
                s6 = 0x970000;
                s4 = 0x970000;
            L_00508798:
                charge(ctx, 1);
                v0 = 1024;
            } else {
                // 0x00508740
                charge(ctx, 6);
                a3 = 0x970000;
                a1 = 0x7C0000;
                s2 = addiu(sp, 0x30);
                s6 = 0x970000;
                s4 = 0x970000;
                a2 = addiu(a2, 1);
                for (;;) {
                    // 0x00508758
                    charge(ctx, 3);
                    v0 = slti(a2, 1024);
                    cc = v0 == 0;  // the condition, before the delay slot changes it
                    v0 = addu(s0, a2);
                    if (cc) {
                        goto L_00508798;
                    }
                    // 0x00508764
                    charge(ctx, 6);
                    a0 = addu(s1, a2);
                    lbu(v1, v0, 0);
                    sb(v1, a0, 20);
                    v1 = sll(v1, 24);
                    if (v1 == 0) {
                        break;
                    }
                    a2 = addiu(a2, 1);
                    backedge(ctx);
                }
                // 0x0050877c
                charge(ctx, 2);
                v0 = 1024;
            }
            // 0x0050879c
            charge(ctx, 2);
            if (a2 == v0) {
                sb(zero, s1, 1043);
            }
            // 0x005087a4
            charge(ctx, 35);
            v0 = addiu(a3, -26112);
            v1 = 0x7FFF0000;
            v0 = subu(s3, v0);
            v1 = v1 | 0xFFFF;
            s5 = sra(v0, 4);
            v1 = s7 & v1;
            sw(v1, s1, 12);
            a1 = addiu(a1, -8736);
            sw(t0, s1, 16);
            v0 = 1;
            sw(v0, sp, 0x14);
            a0 = addiu(sp, 0x10);
            sw(a1, sp, 0x24);
            s4 = addiu(s4, -28352);
            sw(s5, s1, 1044);
            link(ctx, 0x5087E0u);  // $ra first: the delay slot below depends on it
            sw(zero, sp, 0x18);
            call(ctx, gen::fn__sceCreateSema_00503160);
            s0 = v0;
            sw(s2, s1, 4);
            v0 = 4;
            sw(s0, s1, 0);
            sw(v0, s1, 8);
            a0 = addiu(s6, -25600);
            a3 = addiu(fp, -0x7B00);
            a1 = 0;
            sw(zero, sp, 0x0);
            a2 = 0;
            sw(zero, sp, 0x8);
            t0 = 1048;
            t1 = s4;
            t2 = 4;
            t3 = 0;
            jal(ctx, 0x508820u, gen::fn_sceFsSifCallRpc_00507ad8);
            cc = i64(v0) >= 0;  // the condition, before the delay slot changes it
            v0 = 0x20000000;
            if (cc) {
                // 0x00508848
                charge(ctx, 5);
                v0 = s4 | v0;
                link(ctx, 0x50884Cu);  // $ra first: the delay slot below depends on it
                lw(s1, v0, 0);
                call(ctx, gen::fn__sceFsSigSema_00508078);
                if (s1 != 0) {
                    // 0x0050886c
                    charge(ctx, 7);
                    a0 = s0;
                    jal(ctx, 0x50886Cu, gen::fn__sceWaitSema_005031a0);
                    a0 = s0;
                    jal(ctx, 0x508874u, gen::fn__sceDeleteSema_00503170);
                    lw(v1, sp, 0x30);
                    s0 = 0x780000;
                    if (i64(v1) >= 0) {
                        // 0x005088a4
                        charge(ctx, 11);
                        s1 = s5;
                        link(ctx, 0x5088A8u);  // $ra first: the delay slot below depends on it
                        lw(a0, s0, -2744);
                        call(ctx, gen::fn__sceWaitSema_005031a0);
                        lw(v1, s3, 4);
                        lw(v0, sp, 0x30);
                        lw(a0, s0, -2744);
                        v1 = v1 | s7;
                        sw(v1, s3, 4);
                        link(ctx, 0x5088C4u);  // $ra first: the delay slot below depends on it
                        sw(v0, s3, 0);
                        call(ctx, gen::fn__sceSignalSema_00503180);
                        v0 = s1;
                    } else {
                        // 0x00508888
                        charge(ctx, 7);
                        link(ctx, 0x508888u);  // $ra first: the delay slot below depends on it
                        lw(a0, s0, -2744);
                        call(ctx, gen::fn__sceWaitSema_005031a0);
                        sw(zero, s3, 4);
                        link(ctx, 0x508894u);  // $ra first: the delay slot below depends on it
                        lw(a0, s0, -2744);
                        call(ctx, gen::fn__sceSignalSema_00503180);
                        lw(v0, sp, 0x30);
                    }
                } else {
                    // 0x0050885c
                    charge(ctx, 4);
                    a0 = s0;
                    jal(ctx, 0x50885Cu, gen::fn__sceDeleteSema_00503170);
                    v0 = si(-11);
                }
            } else {
                // 0x00508830
                charge(ctx, 6);
                a0 = s0;
                jal(ctx, 0x508830u, gen::fn__sceDeleteSema_00503170);
                jal(ctx, 0x508838u, gen::fn__sceFsSigSema_00508078);
                v0 = si(-11);
            }
        } else {
            // 0x0050871c
            charge(ctx, 4);
            jal(ctx, 0x50871Cu, gen::fn__sceFsSigSema_00508078);
            v0 = si(-19);
        }
    } else {
        // 0x005086f4
        charge(ctx, 5);
        jal(ctx, 0x5086F4u, gen::fn__sceFsSigSema_00508078);
        v0 = lui(0xFFFE);
        v0 = v0 | 0xFFFC;
    }
    // 0x005088d0 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0xD0);
    ld(fp, sp, 0xC0);
    ld(s7, sp, 0xB0);
    ld(s6, sp, 0xA0);
    ld(s5, sp, 0x90);
    ld(s4, sp, 0x80);
    ld(s3, sp, 0x70);
    ld(s2, sp, 0x60);
    ld(s1, sp, 0x50);
    ld(s0, sp, 0x40);
    sp = addiu(sp, 0x150);
}

// 0x00508900 sceClose -- 376 bytes; frame 0xA0: s4 sp+0x80, s2 sp+0x60, s0 sp+0x40, ra sp+0x90, s3 sp+0x70, s1 sp+0x50
// libfileio sceClose: releases the iob of fd a0 (get_iob) after the IOP close call (sceFsSifCallRpc) under the
// "SceStdioCloseSema" semaphore.
void sceClose(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00508900
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(s4, sp, 0x80);
    sd(s2, sp, 0x60);
    s4 = 0x970000;
    sd(s0, sp, 0x40);
    s2 = addiu(s4, -31488);  // &0x968500
    sd(ra, sp, 0x90);
    sd(s3, sp, 0x70);
    link(ctx, 0x508920u);  // $ra first: the delay slot below depends on it
    sd(s1, sp, 0x50);
    call(ctx, gen::fn_get_iob_00507bc8);
    s0 = v0;
    a0 = 1;
    jal(ctx, 0x50892Cu, gen::fn__sceFsWaitS_00508048);
    v1 = 0x780000;
    lw(v0, v1, -2756);  // 0x77F53C
    if (v0 != 0) {
        // 0x00508944
        charge(ctx, 2);
        if (s0 == 0) {
            goto L_00508958;
        }
        // 0x0050894c
        charge(ctx, 3);
        lw(v0, s0, 4);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = 0x970000;
        if (!cc) {
            goto L_00508958;
        }
        // 0x00508968
        charge(ctx, 36);
        lw(a0, s0, 0);
        v0 = addiu(v0, -26112);
        v1 = 0x7C0000;
        v0 = subu(s0, v0);
        sw(a0, s2, 12);
        v0 = sra(v0, 4);
        v1 = addiu(v1, -8712);  // "SceStdioCloseSema"
        sw(v0, s2, 16);
        a1 = 1;
        a0 = addiu(sp, 0x10);
        sw(a1, sp, 0x14);
        sw(v1, sp, 0x24);
        link(ctx, 0x508998u);  // $ra first: the delay slot below depends on it
        sw(zero, sp, 0x18);
        call(ctx, gen::fn__sceCreateSema_00503160);
        s1 = v0;
        v1 = addiu(sp, 0x30);
        v0 = 0x970000;
        sw(s1, s4, -31488);
        s3 = addiu(v0, -28352);  // &0x969140
        sw(v1, s2, 4);
        v0 = 4;
        a0 = 0x970000;
        sw(v0, s2, 8);
        a0 = addiu(a0, -25600);  // &0x969C00
        a3 = s2;
        a1 = 1;
        sw(zero, sp, 0x0);
        a2 = 0;
        sw(zero, sp, 0x8);
        t0 = 20;
        t1 = s3;
        t2 = 4;
        t3 = 0;
        jal(ctx, 0x5089E8u, gen::fn_sceFsSifCallRpc_00507ad8);
        if (i64(v0) >= 0) {
            sw(zero, s0, 4);
            // 0x00508a10
            charge(ctx, 6);
            v0 = 0x20000000;
            v0 = s3 | v0;
            link(ctx, 0x508A18u);  // $ra first: the delay slot below depends on it
            lw(s0, v0, 0);
            call(ctx, gen::fn__sceFsSigSema_00508078);
            if (s0 != 0) {
                // 0x00508a38
                charge(ctx, 8);
                a0 = s1;
                jal(ctx, 0x508A38u, gen::fn__sceWaitSema_005031a0);
                a0 = s1;
                jal(ctx, 0x508A40u, gen::fn__sceDeleteSema_00503170);
                lw(v0, sp, 0x30);
                v1 = si(-1);
                v1 = slt(v1, v0);
                if (v1 != 0) v0 = 0;
            } else {
                // 0x00508a28
                charge(ctx, 4);
                a0 = s1;
                jal(ctx, 0x508A28u, gen::fn__sceDeleteSema_00503170);
                v0 = si(-11);
            }
        } else {
            // 0x005089f8
            charge(ctx, 6);
            a0 = s1;
            jal(ctx, 0x5089F8u, gen::fn__sceDeleteSema_00503170);
            jal(ctx, 0x508A00u, gen::fn__sceFsSigSema_00508078);
            v0 = si(-11);
        }
        // 0x00508a58 (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(ra, sp, 0x90);
        ld(s4, sp, 0x80);
        ld(s3, sp, 0x70);
        ld(s2, sp, 0x60);
        ld(s1, sp, 0x50);
        ld(s0, sp, 0x40);
        sp = addiu(sp, 0xA0);
        return;
    }
L_00508958:
    charge(ctx, 4);
    jal(ctx, 0x508958u, gen::fn__sceFsSigSema_00508078);
    v0 = si(-9);
    // 0x00508a58 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x90);
    ld(s4, sp, 0x80);
    ld(s3, sp, 0x70);
    ld(s2, sp, 0x60);
    ld(s1, sp, 0x50);
    ld(s0, sp, 0x40);
    sp = addiu(sp, 0xA0);
}

// 0x00508A78 sceLseek -- 572 bytes; frame 0xC0: s5 sp+0x90, s3 sp+0x70, s4 sp+0x80, s1 sp+0x50, s0 sp+0x40, ra sp+0xB0, s6 sp+0xA0, s2 sp+0x60
// libfileio sceLseek: the IOP lseek call for fd a0 (offset a1, whence a2) under the "SceStdioLseekSema" semaphore;
// returns the new position.
void sceLseek(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00508a78
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(s5, sp, 0x90);
    sd(s3, sp, 0x70);
    s5 = a2;
    sd(s4, sp, 0x80);
    s3 = a1;
    sd(s1, sp, 0x50);
    s4 = 0x970000;
    sd(s0, sp, 0x40);
    s1 = addiu(s4, -31488);  // &0x968500
    sd(ra, sp, 0xB0);
    sd(s6, sp, 0xA0);
    link(ctx, 0x508AA8u);  // $ra first: the delay slot below depends on it
    sd(s2, sp, 0x60);
    call(ctx, gen::fn_get_iob_00507bc8);
    s0 = v0;
    a0 = 4;
    jal(ctx, 0x508AB4u, gen::fn__sceFsWaitS_00508048);
    v1 = 0x780000;
    lw(v0, v1, -2756);  // 0x77F53C
    if (v0 != 0) {
        // 0x00508acc
        charge(ctx, 2);
        if (s0 == 0) {
            goto L_00508ae0;
        }
        // 0x00508ad4
        charge(ctx, 3);
        lw(s2, s0, 4);
        v0 = 0x970000;
        if (s2 == 0) {
            goto L_00508ae0;
        }
        // 0x00508af0
        charge(ctx, 24);
        lw(a0, s0, 0);
        v0 = addiu(v0, -26112);
        v1 = 0x7C0000;
        v0 = subu(s0, v0);
        sw(a0, s1, 12);
        v0 = sra(v0, 4);
        sw(s3, s1, 16);
        sw(s5, s1, 20);
        v1 = addiu(v1, -8688);  // "SceStdioLseekSema"
        sw(v0, s1, 24);
        a1 = 1;
        a0 = addiu(sp, 0x10);
        sw(a1, sp, 0x14);
        sw(v1, sp, 0x24);
        s0 = s2 & 0x8000;
        link(ctx, 0x508B2Cu);  // $ra first: the delay slot below depends on it
        sw(zero, sp, 0x18);
        call(ctx, gen::fn__sceCreateSema_00503160);
        s3 = v0;
        v1 = 4;
        v0 = addiu(sp, 0x30);
        sw(v1, s1, 8);
        sw(v0, s1, 4);
        sw(s3, s4, -31488);
        if (s0 == 0) {
            // 0x00508be0
            charge(ctx, 4);
            s6 = 0x970000;
            s0 = 0x970000;
            s2 = 0;
            s0 = addiu(s0, -28352);  // &0x969140
        } else {
            // 0x00508b50
            charge(ctx, 9);
            s5 = 0x780000;
            link(ctx, 0x508B54u);  // $ra first: the delay slot below depends on it
            lw(a0, s5, -2740);  // 0x77F54C
            call(ctx, gen::fn__sceWaitSema_005031a0);
            a3 = 0x780000;
            a2 = 0;
            lw(v1, a3, -2888);  // 0x77F4B8
            v0 = si(-1);
            s2 = s0;
            if (v1 != v0) {
                // 0x00508b90
                charge(ctx, 3);
                s6 = 0x970000;
                s0 = 0x970000;
                a2 = addiu(a2, 1);
                for (;;) {
                    // 0x00508b9c
                    charge(ctx, 3);
                    v0 = slti(a2, 32);
                    cc = v0 == 0;  // the condition, before the delay slot changes it
                    v0 = sll(a2, 2);
                    if (cc) {
                        break;
                    }
                    // 0x00508ba8
                    charge(ctx, 6);
                    v1 = addiu(a3, -2888);
                    a1 = addu(v0, v1);
                    a0 = si(-1);
                    lw(v0, a1, 0);
                    a2 = addiu(a2, 1);
                    if (v0 == a0) {
                        goto L_00508bc0_10;
                    }
                    backedge(ctx);
                }
            } else {
                // 0x00508b74
                charge(ctx, 7);
                lw(v1, s4, -31488);
                s6 = 0x970000;
                s0 = 0x970000;
                v0 = subu(0, v1);
                sw(v1, a3, -2888);
                sw(v0, s4, -31488);
            }
        L_00508bd0:
            charge(ctx, 4);
            link(ctx, 0x508BD0u);  // $ra first: the delay slot below depends on it
            lw(a0, s5, -2740);
            call(ctx, gen::fn__sceSignalSema_00503180);
            s0 = addiu(s0, -28352);
        }
        // 0x00508bf0
        charge(ctx, 13);
        a0 = addiu(s6, -25600);
        a3 = addiu(s4, -31488);
        sw(zero, sp, 0x0);
        sw(s2, sp, 0x8);
        a1 = 4;
        a2 = 0;
        t0 = 28;
        t1 = s0;
        t2 = 4;
        t3 = 0;
        jal(ctx, 0x508C14u, gen::fn_sceFsSifCallRpc_00507ad8);
        cc = i64(v0) >= 0;  // the condition, before the delay slot changes it
        v0 = 0x20000000;
        if (cc) {
            // 0x00508c3c
            charge(ctx, 5);
            v0 = s0 | v0;
            link(ctx, 0x508C40u);  // $ra first: the delay slot below depends on it
            lw(s0, v0, 0);
            call(ctx, gen::fn__sceFsSigSema_00508078);
            if (s0 != 0) {
                // 0x00508c60
                charge(ctx, 2);
                if (s2 == 0) {
                    // 0x00508c78
                    charge(ctx, 5);
                    a0 = s3;
                    jal(ctx, 0x508C78u, gen::fn__sceWaitSema_005031a0);
                    a0 = s3;
                    jal(ctx, 0x508C80u, gen::fn__sceDeleteSema_00503170);
                    lw(v0, sp, 0x30);
                } else {
                    // 0x00508c68
                    charge(ctx, 4);
                    a0 = s3;
                    jal(ctx, 0x508C68u, gen::fn__sceDeleteSema_00503170);
                    v0 = 0;
                }
            } else {
                // 0x00508c50
                charge(ctx, 4);
                a0 = s3;
                jal(ctx, 0x508C50u, gen::fn__sceDeleteSema_00503170);
                v0 = si(-11);
            }
        } else {
            // 0x00508c24
            charge(ctx, 6);
            a0 = s3;
            jal(ctx, 0x508C24u, gen::fn__sceDeleteSema_00503170);
            jal(ctx, 0x508C2Cu, gen::fn__sceFsSigSema_00508078);
            v0 = si(-11);
        }
        // 0x00508c8c (the shared epilogue, written out on this path)
        charge(ctx, 10);
        ld(ra, sp, 0xB0);
        ld(s6, sp, 0xA0);
        ld(s5, sp, 0x90);
        ld(s4, sp, 0x80);
        ld(s3, sp, 0x70);
        ld(s2, sp, 0x60);
        ld(s1, sp, 0x50);
        ld(s0, sp, 0x40);
        sp = addiu(sp, 0xC0);
        return;
    }
L_00508ae0:
    charge(ctx, 4);
    jal(ctx, 0x508AE0u, gen::fn__sceFsSigSema_00508078);
    v0 = si(-9);
    // 0x00508c8c (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0xB0);
    ld(s6, sp, 0xA0);
    ld(s5, sp, 0x90);
    ld(s4, sp, 0x80);
    ld(s3, sp, 0x70);
    ld(s2, sp, 0x60);
    ld(s1, sp, 0x50);
    ld(s0, sp, 0x40);
    sp = addiu(sp, 0xC0);
    return;
L_00508bc0_10:
    charge(ctx, 4);
    lw(v0, s1, 0);
    v1 = subu(0, v0);
    sw(v0, a1, 0);
    sw(v1, s1, 0);
    goto L_00508bd0;
}

// 0x00509758 _sceCallCode -- 432 bytes; frame 0xD0: s6 sp+0xA0, s1 sp+0x50, s7 sp+0xB0, s3 sp+0x70, ra sp+0xC0, s5 sp+0x90, s4 sp+0x80, s2 sp+0x60, s0 sp+0x40
// libfileio _sceCallCode: the shared path-only IOP call (remove / rmdir / deldrv / dopen / chdir) with RPC function
// a1 on path a0 under the "SceStdioCCodeSema" semaphore.
void _sceCallCode(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00509758
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0xD0);
    sd(s6, sp, 0xA0);
    sd(s1, sp, 0x50);
    s6 = a1;
    s1 = a0;
    sd(s7, sp, 0xB0);
    sd(s3, sp, 0x70);
    a0 = s6;
    sd(ra, sp, 0xC0);
    s7 = 0x970000;
    sd(s5, sp, 0x90);
    s3 = addiu(s7, -31488);  // &0x968500
    sd(s4, sp, 0x80);
    sd(s2, sp, 0x60);
    link(ctx, 0x509790u);  // $ra first: the delay slot below depends on it
    sd(s0, sp, 0x40);
    call(ctx, gen::fn__sceFsWaitS_00508048);
    v0 = 0x780000;
    lw(v1, v0, -2756);  // 0x77F53C
    if (v1 != 0) {
        lbu(v0, s1, 0);
    } else {
        // 0x005097a8
        charge(ctx, 3);
        jal(ctx, 0x5097A8u, gen::fn_sceFsInit_00508170);
        lbu(v0, s1, 0);
    }
    // 0x005097b4
    charge(ctx, 4);
    s0 = 0;
    v1 = sll(v0, 24);
    sb(v0, s3, 12);
    if (v1 == 0) {
        // 0x00509804
        charge(ctx, 4);
        a1 = 0x7C0000;
        s2 = addiu(sp, 0x30);
        s5 = 0x970000;
        s4 = 0x970000;
    L_00509814:
        charge(ctx, 1);
        v0 = 1024;
    } else {
        // 0x005097c4
        charge(ctx, 5);
        a1 = 0x7C0000;
        s2 = addiu(sp, 0x30);
        s5 = 0x970000;
        s4 = 0x970000;
        s0 = addiu(s0, 1);
        for (;;) {
            // 0x005097d8
            charge(ctx, 3);
            v0 = slti(s0, 1024);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = addu(s1, s0);
            if (cc) {
                goto L_00509814;
            }
            // 0x005097e4
            charge(ctx, 6);
            a0 = addu(s3, s0);
            lbu(v1, v0, 0);
            sb(v1, a0, 12);
            v1 = sll(v1, 24);
            if (v1 == 0) {
                break;
            }
            s0 = addiu(s0, 1);
            backedge(ctx);
        }
        // 0x005097fc
        charge(ctx, 2);
        v0 = 1024;
    }
    // 0x00509818
    charge(ctx, 2);
    cc = s0 != v0;  // the condition, before the delay slot changes it
    v0 = addiu(a1, -8568);
    if (!cc) {
        // 0x00509820
        charge(ctx, 2);
        sb(zero, s3, 1035);
        s0 = 1023;
    }
    // 0x00509828
    charge(ctx, 25);
    v1 = 1;
    sw(v1, sp, 0x14);
    a0 = addiu(sp, 0x10);
    sw(v0, sp, 0x24);
    s4 = addiu(s4, -28352);
    link(ctx, 0x50983Cu);  // $ra first: the delay slot below depends on it
    sw(zero, sp, 0x18);
    call(ctx, gen::fn__sceCreateSema_00503160);
    s1 = v0;
    sw(s2, s3, 4);
    v0 = 4;
    sw(s1, s3, 0);
    sw(v0, s3, 8);
    a0 = addiu(s5, -25600);
    a1 = s6;
    a3 = addiu(s7, -31488);
    t0 = addiu(s0, 13);
    a2 = 0;
    sw(zero, sp, 0x0);
    t1 = s4;
    sw(zero, sp, 0x8);
    t2 = 4;
    t3 = 0;
    jal(ctx, 0x50987Cu, gen::fn_sceFsSifCallRpc_00507ad8);
    cc = i64(v0) >= 0;  // the condition, before the delay slot changes it
    v0 = 0x20000000;
    if (cc) {
        // 0x005098a4
        charge(ctx, 5);
        v0 = s4 | v0;
        link(ctx, 0x5098A8u);  // $ra first: the delay slot below depends on it
        lw(s0, v0, 0);
        call(ctx, gen::fn__sceFsSigSema_00508078);
        if (s0 != 0) {
            // 0x005098c8
            charge(ctx, 5);
            a0 = s1;
            jal(ctx, 0x5098C8u, gen::fn__sceWaitSema_005031a0);
            a0 = s1;
            jal(ctx, 0x5098D0u, gen::fn__sceDeleteSema_00503170);
            lw(v0, sp, 0x30);
        } else {
            // 0x005098b8
            charge(ctx, 4);
            a0 = s1;
            jal(ctx, 0x5098B8u, gen::fn__sceDeleteSema_00503170);
            v0 = si(-11);
        }
    } else {
        // 0x0050988c
        charge(ctx, 6);
        a0 = s1;
        jal(ctx, 0x50988Cu, gen::fn__sceDeleteSema_00503170);
        jal(ctx, 0x509894u, gen::fn__sceFsSigSema_00508078);
        v0 = si(-11);
    }
    // 0x005098dc (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0xC0);
    ld(s7, sp, 0xB0);
    ld(s6, sp, 0xA0);
    ld(s5, sp, 0x90);
    ld(s4, sp, 0x80);
    ld(s3, sp, 0x70);
    ld(s2, sp, 0x60);
    ld(s1, sp, 0x50);
    ld(s0, sp, 0x40);
    sp = addiu(sp, 0xD0);
}

// 0x0050E508 sub_50E508 -- 76 bytes; leaf frame (no stack)
// Reads the EE timer-1 count (T1_COUNT 0x10001000) widened with the software overflow count (qword_780B48, +1 when
// T1_MODE's overflow bit is set) and scaled by the timer's clock divider.
void sub_50E508(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0050e508
    enter(ctx, 9);  // entry check point + this block's cycles
    v1 = 0x10000000;
    a0 = 0x780000;
    v1 = v1 | 0x1000;
    lwu(v0, v1, 0);  // 0x10001000
    lw(t0, v1, 16);  // 0x10001010
    ld(t2, a0, 2888);  // 0x780B48
    t1 = t0 & 0x800;
    cc = t1 == 0;  // the condition, before the delay slot changes it
    t1 = 2;
    if (!cc) {
        // 0x0050e52c
        charge(ctx, 2);
        lwu(v0, v1, 0);
        t2 = daddiu(t2, 1);
    }
    // 0x0050e534 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    t0 = t0 & 0x3;
    t2 = dsll(t2, 16);
    if (t0 == 0) t1 = 0;
    v0 = v0 | t2;
    t1 = dsllv(t1, t0);
    v0 = dsllv(v0, t1);
}

// 0x0051B5F0 _sceMcCoreReadClock -- 276 bytes; frame 0x80: s5 sp+0x60, s2 sp+0x30, ra sp+0x70, s4 sp+0x50, s3 sp+0x40, s1 sp+0x20, s0 sp+0x10
// libmc _sceMcCoreReadClock: sends the read-clock command (0x30) to the memory-card DBC connection of port a0
// (sceDbcSendData3, retried) and copies the 8-byte clock result into a1; 0 on no connection or failure.
void _sceMcCoreReadClock(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051b5f0
    enter(ctx, 20);  // entry check point + this block's cycles
    v1 = 36;
    v0 = 0x980000;
    mult(a0, a0, v1);
    sp = addiu(sp, -0x80);
    v0 = addiu(v0, 21768);  // &0x985508
    sd(s5, sp, 0x60);
    sd(s2, sp, 0x30);
    v0 = addiu(v0, 4);  // &0x98550C
    sd(ra, sp, 0x70);
    s5 = a1;
    sd(s4, sp, 0x50);
    s2 = addu(a0, v0);
    sd(s3, sp, 0x40);
    sd(s1, sp, 0x20);
    sd(s0, sp, 0x10);
    link(ctx, 0x51B62Cu);  // $ra first: the delay slot below depends on it
    lw(a0, s2, 0);
    call(ctx, gen::fn_sceDbcGetConnection_0051cad0);
    v1 = 3;
    s3 = 0x980000;
    if (v0 != v1) {
        // 0x0051b640
        charge(ctx, 20);
        v0 = 48;
        v1 = addiu(s3, 21888);
        s0 = 0x980000;
        sw(zero, v1, 24);
        s0 = addiu(s0, 21952);  // &0x9855C0
        sw(v0, sp, 0x0);
        a0 = s0;
        sw(zero, v1, 20);
        a1 = 0;
        a2 = 256;
        s1 = 0x780000;
        jal(ctx, 0x51B668u, gen::fn_memset_00521408);
        s4 = 0x520000;
        a0 = s0;
        a1 = addiu(a0, 255);  // &0x9856BF
        s0 = 1;
        jal(ctx, 0x51B67Cu, gen::fn_SyncDCache_00503a58);
        v0 = 10;
        sw(v0, s1, 10988);  // 0x782AEC
        lw(a0, s2, 0);
        for (;;) {
            // 0x0051b690
            charge(ctx, 7);
            a2 = sp;
            lw(a1, s1, 10988);
            a3 = addiu(s3, 21888);
            t0 = addiu(s4, -20936);
            jal(ctx, 0x51B69Cu, gen::fn_sceDbcSendData3_0051d308);
            if (v0 == s0) {
                break;
            }
            lw(a0, s2, 0);
            backedge(ctx);
        }
        // 0x0051b6ac
        charge(ctx, 6);
        jal(ctx, 0x51B6ACu, gen::fn_SyncDma_0051ad10);
        v1 = v0;
        lw(v0, v1, 8);
        if (v0 == 0) {
            goto L_0051b6c4;
        }
        // 0x0051b6cc
        charge(ctx, 5);
        ldl(v0, v1, 19);
        ldr(v0, v1, 12);
        sdl(v0, s5, 7);
        sdr(v0, s5, 0);
        lw(v0, v1, 8);
        // 0x0051b6e0 (the shared epilogue, written out on this path)
        charge(ctx, 9);
        ld(ra, sp, 0x70);
        ld(s5, sp, 0x60);
        ld(s4, sp, 0x50);
        ld(s3, sp, 0x40);
        ld(s2, sp, 0x30);
        ld(s1, sp, 0x20);
        ld(s0, sp, 0x10);
        sp = addiu(sp, 0x80);
        return;
    }
L_0051b6c4:
    charge(ctx, 2);
    v0 = 0;
    // 0x0051b6e0 (the shared epilogue, written out on this path)
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

// 0x00523CC0 __swrite -- 128 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// newlib __swrite: seeks to the end first for append streams (flag 0x100), clears the offset-valid flag (0x1000) and
// writes through _write_r.
void __swrite(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00523cc0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    s0 = a0;
    sd(ra, sp, 0x18);
    s1 = a1;
    s2 = a2;
    lhu(t7, a0, 12);
    t7 = t7 & 0x100;
    a2 = 0;
    if (t7 != 0) {
        // 0x00523cf0
        charge(ctx, 4);
        lh(a1, a0, 14);
        a3 = 2;
        link(ctx, 0x523CF8u);  // $ra first: the delay slot below depends on it
        lw(a0, a0, 84);
        call(ctx, gen::fn__execve_r_00520580);
    }
    // 0x00523d00
    charge(ctx, 16);
    lhu(t7, s0, 12);
    a2 = s1;
    lh(a1, s0, 14);
    a3 = s2;
    t7 = t7 & 0xEFFF;
    lw(a0, s0, 84);
    link(ctx, 0x523D18u);  // $ra first: the delay slot below depends on it
    sh(t7, s0, 12);
    call(ctx, gen::fn__write_r_00528970);
    v0 = dsll32(v0, 0);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    v0 = dsra32(v0, 0);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00535DD8 sub_535DD8 -- 48 bytes; frame 0x10: ra sp+0x0
// Calls the 0x7836A8 hook on the handle at a0+192 when present.
void sub_535DD8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00535dd8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, 192);
    a0 = v0;
    if (v0 != 0) {
        // 0x00535dec
        charge(ctx, 4);
        v0 = 0x780000;
        lw(v1, v0, 13992);  // 0x7836A8
        jalr(ctx, 0x535DF4u, v1.u());
    }
    // 0x00535dfc (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00535E28 sub_535E28 -- 48 bytes; frame 0x10: ra sp+0x0
// Calls the 0x7836AC hook on the handle at a0+192 when present.
void sub_535E28(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00535e28
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, 192);
    a0 = v0;
    if (v0 != 0) {
        // 0x00535e3c
        charge(ctx, 4);
        v0 = 0x780000;
        lw(v1, v0, 13996);  // 0x7836AC
        jalr(ctx, 0x535E44u, v1.u());
    }
    // 0x00535e4c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00535FC0 sub_535FC0 -- 48 bytes; frame 0x10: ra sp+0x0
// Calls the 0x7836B8 hook on the handle at a0+180 when present.
void sub_535FC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00535fc0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, 180);
    a0 = v0;
    if (v0 != 0) {
        // 0x00535fd4
        charge(ctx, 4);
        v0 = 0x780000;
        lw(v1, v0, 14008);  // 0x7836B8
        jalr(ctx, 0x535FDCu, v1.u());
    }
    // 0x00535fe4 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00535FF0 sub_535FF0 -- 100 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Calls the 0x7836BC hook on the handle at a0+180 when present, stores a1 at +184 and a1 / 96 at +188; returns 96.
void sub_535FF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00535ff0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(ra, sp, 0x10);
    lw(v0, s1, 180);
    a0 = v0;
    if (v0 != 0) {
        // 0x00536014
        charge(ctx, 4);
        v0 = 0x780000;
        lw(v1, v0, 14012);  // 0x7836BC
        jalr(ctx, 0x53601Cu, v1.u());
    }
    // 0x00536024
    charge(ctx, 5);
    v0 = 96;
    sw(s0, s1, 184);
    div(s0, v0);
    if (v0 == 0) {
        brk(ctx, 0x536034u, 0x7u);
    }
    // 0x00536038
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x10);
    mflo(v1);
    sw(v1, s1, 188);
    ld(s1, sp, 0x8);
    sp = addiu(sp, 0x20);
}

// 0x00536080 sub_536080 -- 48 bytes; frame 0x10: ra sp+0x0
// Calls the 0x7836C0 hook on the handle at a0+180 when present.
void sub_536080(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00536080
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, 180);
    a0 = v0;
    if (v0 != 0) {
        // 0x00536094
        charge(ctx, 4);
        v0 = 0x780000;
        lw(v1, v0, 14016);  // 0x7836C0
        jalr(ctx, 0x53609Cu, v1.u());
    }
    // 0x005360a4 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00537790 my_malloc -- 72 bytes, 2 chunks; frame 0x10: ra sp+0x0
// CRI ADX heap init (my_malloc): sub_54CB78, sub_5374E8, clears the 4160-byte table at 0x7838F0 and its count;
// returns 0x780000.
void my_malloc(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00537790
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x537798u, gen::fn_sub_54CB78_0054cb78);
    jal(ctx, 0x5377A0u, gen::fn_sub_5374E8_005374e8);
    a0 = 0x780000;
    a1 = 0;
    a0 = addiu(a0, 14576);  // &0x7838F0
    a2 = 4160;
    jal(ctx, 0x5377B4u, gen::fn_memset_00521408);
    a0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x00537770
    charge(ctx, 3);
    v0 = 0x780000;
    sw(a0, v0, 14572);  // 0x7838EC
}

// 0x00537890 sub_537890 -- 284 bytes; frame 0x30: s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s0 sp+0x0, ra sp+0x28
// CRI ADX stream handle create: takes a free slot in the 0x7838F0 table, clears it, opens the stream (sub_54CBC8 /
// sub_5379B0) with the read callbacks sub_537808 / sub_537838 and links it (sub_537858).
void sub_537890(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00537890
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    t0 = 0x780000;
    sd(s1, sp, 0x8);
    s1 = a2;
    sd(s2, sp, 0x10);
    s2 = a3;
    sd(s3, sp, 0x18);
    s3 = a1;
    sd(s4, sp, 0x20);
    s4 = a0;
    sd(s0, sp, 0x0);
    v1 = addiu(t0, 14576);  // &0x7838F0
    sd(ra, sp, 0x28);
    lh(v0, v1, 0);  // 0x7838F0
    a1 = 0;
    if (v0 != 0) {
        // 0x005378d0
        charge(ctx, 2);
        a1 = addiu(a1, 1);
        for (;;) {
            // 0x005378d8
            charge(ctx, 3);
            v0 = slti(a1, 16);
            v1 = addiu(v1, 260);
            if (v0 != 0) {
                // 0x005378e4
                charge(ctx, 6);
                lh(v0, v1, 0);
                if (v0 != 0) {
                    a1 = addiu(a1, 1);
                    backedge(ctx);
                    continue;
                }
            }
            break;
        }
    }
    // 0x005378fc
    charge(ctx, 3);
    v1 = 16;
    v0 = 0;
    if (a1 != v1) {
        // 0x00537908
        charge(ctx, 14);
        v0 = sll(a1, 6);
        v1 = addiu(t0, 14576);
        v0 = addu(v0, a1);
        a1 = 0;
        v0 = sll(v0, 2);
        a2 = 260;
        s0 = addu(v0, v1);
        a0 = s0;
        jal(ctx, 0x537924u, gen::fn_memset_00521408);
        v1 = 1;
        link(ctx, 0x537930u);  // $ra first: the delay slot below depends on it
        sh(v1, s0, 0);
        call(ctx, gen::fn_sub_54CBC8_0054cbc8);
        sw(v0, s0, 8);
        if (v0 != 0) {
            // 0x00537950
            charge(ctx, 15);
            v0 = 0x530000;
            v1 = 0x530000;
            v0 = addiu(v0, 30728);  // &sub_537808
            v1 = addiu(v1, 30776);  // &sub_537838
            sw(v0, s0, 120);
            a0 = s0;
            sw(s4, s0, 56);
            sw(s3, s0, 60);
            sw(s1, s0, 64);
            sw(s2, s0, 68);
            sw(v1, s0, 128);
            sw(s0, s0, 124);
            link(ctx, 0x537980u);  // $ra first: the delay slot below depends on it
            sw(s0, s0, 132);
            call(ctx, gen::fn_sub_537858_00537858);
            v0 = s0;
        } else {
            // 0x00537940
            charge(ctx, 4);
            a0 = s0;
            jal(ctx, 0x537940u, gen::fn_sub_5379B0_005379b0);
            v0 = 0;
        }
    }
    // 0x0053798c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x00537D90 sub_537D90 -- 548 bytes, 2 chunks; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// CRI ADX stream server step: drives the handle's state machine (sub_537858, sub_5379F8, the decode / transfer
// helpers 0x536440..0x539148).
void sub_537D90(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00537d90
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x537DACu, gen::fn_sub_537858_00537858);
    lhu(v0, s0, 0);
    a0 = 0x8000;
    v1 = sll(v0, 8);
    v0 = srl(v0, 8);
    v0 = v0 | v1;
    v0 = v0 & 0xFFFF;
    a1 = s0;
    if (v0 == a0) {
        // 0x00537dd4
        charge(ctx, 8);
        a0 = s1;
        ld(s1, sp, 0x8);
        ld(s0, sp, 0x0);
        a2 = s2;
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_5379F8_005379f8(ctx);  // tail call
        return;
    }
    // 0x00537df8
    charge(ctx, 4);
    a0 = s0;
    jal(ctx, 0x537DF8u, gen::fn_sub_538EF0_00538ef0);
    a1 = s0;
    if (v0 != 0) {
        // 0x00537e08
        charge(ctx, 8);
        a0 = s1;
        ld(s1, sp, 0x8);
        ld(s0, sp, 0x0);
        a2 = s2;
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_538C80_00538c80(ctx);  // tail call
        return;
    }
    // 0x00537e28
    charge(ctx, 4);
    a0 = s0;
    jal(ctx, 0x537E28u, gen::fn_sub_5396F8_005396f8);
    a1 = s0;
    if (v0 != 0) {
        // 0x00537e38
        charge(ctx, 8);
        a0 = s1;
        ld(s1, sp, 0x8);
        ld(s0, sp, 0x0);
        a2 = s2;
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_539148_00539148(ctx);  // tail call
        return;
    }
    // 0x00537e58
    charge(ctx, 4);
    a0 = s0;
    jal(ctx, 0x537E58u, gen::fn_sub_536440_00536440);
    a1 = s0;
    if (v0 != 0) {
        // 0x00537e68
        charge(ctx, 8);
        a0 = s1;
        ld(s1, sp, 0x8);
        ld(s0, sp, 0x0);
        a2 = s2;
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_5365B8_005365b8(ctx);  // tail call
        return;
    }
    // 0x00537e88
    charge(ctx, 4);
    a0 = s0;
    jal(ctx, 0x537E88u, gen::fn_sub_536D28_00536d28);
    a1 = s0;
    if (v0 != 0) {
        // 0x00537e98
        charge(ctx, 8);
        a0 = s1;
        ld(s1, sp, 0x8);
        ld(s0, sp, 0x0);
        a2 = s2;
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_536E90_00536e90(ctx);  // tail call
        return;
    }
    // 0x00537eb8
    charge(ctx, 4);
    a0 = s0;
    jal(ctx, 0x537EB8u, gen::fn_sub_535F38_00535f38);
    a0 = s1;
    if (v0 == 0) {
        // 0x00537ee8
        charge(ctx, 7);
        ld(s0, sp, 0x0);
        v0 = si(-1);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x00537ec8
    charge(ctx, 8);
    ld(s1, sp, 0x8);
    a1 = s0;
    ld(s0, sp, 0x0);
    a2 = s2;
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    backedge(ctx);
    // 0x00535e88
    charge(ctx, 4);
    t6 = a0;
    lw(v1, t6, 192);
    v0 = 0;
    if (v1 != 0) {
        // 0x00535e98
        charge(ctx, 38);
        v1 = 0x7FFF0000;
        lw(t4, t6, 60);
        lw(t5, t6, 64);
        t2 = 1;
        lw(t3, t6, 68);
        t1 = 1536;
        a0 = 16;
        v1 = v1 | 0xFFFF;
        a1 = 127;
        a2 = 15;
        a3 = 1;
        t0 = 127;
        v0 = 0xBB80;
        sb(t2, t6, 14);
        sb(a0, t6, 13);
        sw(v1, t6, 24);
        sb(a1, t6, 15);
        sh(a2, t6, 152);
        sw(a3, t6, 80);
        sw(t0, t6, 84);
        sw(t1, t6, 88);
        sw(t4, t6, 92);
        sw(t5, t6, 96);
        sw(t3, t6, 100);
        sw(zero, t6, 136);
        sh(t2, t6, 2);
        sw(t1, t6, 16);
        sw(zero, t6, 140);
        sh(zero, t6, 28);
        sh(zero, t6, 36);
        sh(zero, t6, 38);
        sw(zero, t6, 32);
        sw(zero, t6, 40);
        sw(zero, t6, 44);
        sw(zero, t6, 48);
        sw(zero, t6, 52);
        sw(v0, t6, 20);
        v0 = 1;
    }
    // 0x00535f30 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00537F08 sub_537F08 -- 12 bytes; leaf frame (no stack)
// Stores a1 at +120 and a2 at +124 of the handle a0.
void sub_537F08(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00537f08
    enter(ctx, 3);  // entry check point + this block's cycles
    sw(a2, a0, 124);
    sw(a1, a0, 120);
}

// 0x00538060 sub_538060 -- 92 bytes, 2 chunks; frame 0x10: s0 sp+0x0, ra sp+0x8
// Refreshes the handle's stream info: sub_54CCE8(+8, +172, +176), then copies the three u16 fields 26..28 of the
// stream header into +166..+170.
void sub_538060(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00538060
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    a1 = addiu(s0, 172);
    a2 = addiu(s0, 176);
    link(ctx, 0x538078u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 8);
    call(ctx, gen::fn_sub_54CCE8_0054cce8);
    lw(a0, s0, 8);
    a3 = addiu(s0, 170);
    a1 = addiu(s0, 166);
    a2 = addiu(s0, 168);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    // 0x0054cd20
    charge(ctx, 7);
    lhu(v0, a0, 52);
    sh(v0, a1, 0);
    lhu(v1, a0, 54);
    sh(v1, a2, 0);
    lhu(v0, a0, 56);
    sh(v0, a3, 0);
}

// 0x005382C0 sub_5382C0 -- 8 bytes; leaf frame (no stack)
// Returns the word at a0+4 (the handle state).
void sub_5382C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x005382c0
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, 4);
}

// 0x005382C8 sub_5382C8 -- 124 bytes; leaf frame (no stack)
// CRI handle status mapping: translates the stream state (+4) and the underlying file state into the public status
// code.
void sub_5382C8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x005382c8
    enter(ctx, 4);  // entry check point + this block's cycles
    a3 = a0;
    lh(v0, a3, 152);
    t0 = a1;
    if (v0 != 0) {
        // 0x005382f8
        charge(ctx, 11);
        lb(v0, a3, 13);
        lb(a1, a3, 14);
        v1 = slti(v0, 0);
        a0 = addiu(v0, 7);
        if (v1 != 0) v0 = a0;
        sw(t0, a3, 72);
        v0 = sra(v0, 3);
        mult(v0, v0, a1);
        div1(a2, v0);
        if (v0 == 0) {
            brk(ctx, 0x538320u, 0x7u);
        }
        // 0x00538324
        charge(ctx, 2);
        sw(zero, a3, 116);
        mflo1(v1);
    } else {
        // 0x005382d8
        charge(ctx, 5);
        lb(v0, a3, 15);
        sw(t0, a3, 72);
        div(a2, v0);
        if (v0 == 0) {
            brk(ctx, 0x5382E8u, 0x7u);
        }
        // 0x005382ec
        charge(ctx, 3);
        mflo(v1);
        sw(zero, a3, 116);
    }
    // 0x0053832c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    sw(v1, a3, 76);
    sw(zero, a3, 244);
    sw(zero, a3, 144);
    sw(zero, a3, 148);
    sw(zero, a3, 248);
}

// 0x00538348 sub_538348 -- 24 bytes; leaf frame (no stack)
// Sets the handle state (+4) to 1 when it is 0; returns 1.
void sub_538348(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00538348
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, a0, 4);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = 1;
    if (!cc) {
        // 0x00538354
        charge(ctx, 1);
        sw(v0, a0, 4);
    }
    // 0x00538358 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00538360 sub_538360 -- 68 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Handle stop: calls the 0x7838E0 hook when +232 is set, stops the stream (sub_54CE38(+8)) and clears the state (+4).
void sub_538360(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00538360
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    lw(v0, s0, 232);
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = 0x780000;
    if (!cc) {
        // 0x0053837c
        charge(ctx, 3);
        lw(v1, v0, 14560);
        jalr(ctx, 0x538380u, v1.u());
    }
    // 0x00538388
    charge(ctx, 7);
    link(ctx, 0x538388u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 8);
    call(ctx, gen::fn_sub_54CE38_0054ce38);
    sw(zero, s0, 4);
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x005383A8 sub_5383A8 -- 64 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Handle reset after the end: when the state (+4) is 3, closes the stream (sub_54CE60(+8)) and clears +140 and the
// state.
void sub_5383A8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005383a8
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = 3;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    lw(v0, s0, 4);
    if (v0 != v1) {
        ld(s0, sp, 0x0);
    } else {
        // 0x005383c8
        charge(ctx, 5);
        link(ctx, 0x5383C8u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, 8);
        call(ctx, gen::fn_sub_54CE60_0054ce60);
        sw(zero, s0, 140);
        sw(zero, s0, 4);
        ld(s0, sp, 0x0);
    }
    // 0x005383dc (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0053AE08 sub_53AE08 -- 84 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// CRI error report: copies the message a0 (strncpy, 255) into the 0x784958 buffer, calls the user error callback
// (0x784950 with its object 0x784954) and logs it (sub_564AA8).
void sub_53AE08(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x0053ae08
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x780000;
    sd(s0, sp, 0x0);
    s0 = addiu(v0, 18776);  // &0x784958
    a1 = a0;
    a0 = s0;
    sd(ra, sp, 0x8);
    a2 = 255;
    jal(ctx, 0x53AE24u, gen::fn_strncpy_00524828);
    v1 = 0x780000;
    lw(v1, v1, 18768);  // 0x784950
    a1 = s0;
    if (v1 != 0) {
        // 0x0053ae3c
        charge(ctx, 3);
        v0 = 0x780000;
        jt = v1.u();  // the target, read before the delay slot
        link(ctx, 0x53AE40u);  // $ra = the return address
        lw(a0, v0, 18772);
        call_ptr(ctx, jt);
    }
    // 0x0053ae48
    charge(ctx, 5);
    a0 = s0;
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_564AA8_00564aa8(ctx);  // tail call
}

// 0x0053AE60 sub_53AE60 -- 112 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// CRI error report with two parts: strncpy a0 then strncat a1 into the 0x784958 buffer, the user error callback and
// sub_564AA8.
void sub_53AE60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x0053ae60
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x780000;
    sd(s1, sp, 0x8);
    s1 = addiu(v0, 18776);  // &0x784958
    sd(s0, sp, 0x0);
    s0 = a1;
    a2 = 255;
    a1 = a0;
    sd(ra, sp, 0x10);
    a0 = s1;
    jal(ctx, 0x53AE84u, gen::fn_strncpy_00524828);
    a0 = s1;
    a1 = s0;
    a2 = 255;
    jal(ctx, 0x53AE94u, gen::fn_strncat_005244c0);
    v1 = 0x780000;
    lw(v1, v1, 18768);  // 0x784950
    a1 = s1;
    if (v1 != 0) {
        // 0x0053aeac
        charge(ctx, 3);
        v0 = 0x780000;
        jt = v1.u();  // the target, read before the delay slot
        link(ctx, 0x53AEB0u);  // $ra = the return address
        lw(a0, v0, 18772);
        call_ptr(ctx, jt);
    }
    // 0x0053aeb8
    charge(ctx, 6);
    a0 = s1;
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_564AA8_00564aa8(ctx);  // tail call
}

// 0x0053EA30 sub_53EA30 -- 32 bytes; frame 0x10: ra sp+0x0
// sub_53F5F0(); returns 0.
void sub_53EA30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053ea30
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x53EA38u, gen::fn_sub_53F5F0_0053f5f0);
    ld(ra, sp, 0x0);
    v0 = 0;
    sp = addiu(sp, 0x10);
}

// 0x0053EA50 r_lock_def_free -- 32 bytes; frame 0x10: ra sp+0x0
// sub_549EA0(); returns 0.
void r_lock_def_free(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053ea50
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x53EA58u, gen::fn_sub_549EA0_00549ea0);
    ld(ra, sp, 0x0);
    v0 = 0;
    sp = addiu(sp, 0x10);
}

// 0x0053EA70 r_lock_def_get_free_item -- 32 bytes; frame 0x10: ra sp+0x0
// ADXT_UpdateFsStat(); returns 0.
void r_lock_def_get_free_item(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053ea70
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x53EA78u, gen::fn_ADXT_UpdateFsStat_0053e0b8);
    ld(ra, sp, 0x0);
    v0 = 0;
    sp = addiu(sp, 0x10);
}

// 0x005419F8 sub_5419F8 -- 20 bytes; frame 0x10: ra sp+0x0
// Tail call: PS2RNA_Create.
void sub_5419F8(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x005419f8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_PS2RNA_Create_00560758(ctx);  // tail call
}

// 0x00541A10 sub_541A10 -- 56 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// sub_560D20(a0, 0), sub_560C88(a0, 0), then tail-calls sub_560AF8(a0).
void sub_541A10(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00541a10
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = 0;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x541A20u, gen::fn_sub_560D20_00560d20);
    a0 = s0;
    a1 = 0;
    jal(ctx, 0x541A2Cu, gen::fn_sub_560C88_00560c88);
    a0 = s0;
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_560AF8_00560af8(ctx);  // tail call
}

// 0x00541AD8 sub_541AD8 -- 20 bytes; frame 0x10: ra sp+0x0
// Tail call: sub_560F18.
void sub_541AD8(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00541ad8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_560F18_00560f18(ctx);  // tail call
}

// 0x00541B28 sub_541B28 -- 20 bytes; frame 0x10: ra sp+0x0
// Tail call: PS2RNA_ExecServer.
void sub_541B28(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00541b28
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_PS2RNA_ExecServer_00561138(ctx);  // tail call
}

// 0x00541B58 sub_541B58 -- 64 bytes, 2 chunks; frame 0x10: ra sp+0x0
// Stores the byte a1 at a0+82 unless the PS2RNA lock is held (0x7A93F8 == 1 with 0x7A93F0 <= 0).
void sub_541B58(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00541b58
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x00561228
    charge(ctx, 5);
    v0 = 0x7B0000;
    a2 = 1;
    lw(v1, v0, -27656);  // 0x7A93F8
    if (v1 != a2) {
        sb(a1, a0, 82);
    } else {
        // 0x0056123c
        charge(ctx, 4);
        v0 = 0x7B0000;
        lw(v1, v0, -27664);  // 0x7A93F0
        if (i64(v1) > 0) {
            sb(a1, a0, 82);
        }
    }
    // 0x0056124c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00541B70 sub_541B70 -- 20 bytes; frame 0x10: ra sp+0x0
// Tail call: sub_561258.
void sub_541B70(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00541b70
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_561258_00561258(ctx);  // tail call
}

// 0x00541B88 sub_541B88 -- 84 bytes, 2 chunks; frame 0x10: ra sp+0x0
// Stores the volume a1 clamped to -999..0 at a0+56 unless the PS2RNA lock is held (0x7A93F8 == 1 with 0x7A93F0 <= 0).
void sub_541B88(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00541b88
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x005612d0
    charge(ctx, 6);
    v0 = 0x7B0000;
    a2 = 1;
    lw(v1, v0, -27656);  // 0x7A93F8
    v0 = slt(0, a1);
    if (v0 != 0) a1 = 0;
    if (v1 == a2) {
        // 0x005612e8
        charge(ctx, 4);
        v0 = 0x7B0000;
        lw(v1, v0, -27664);  // 0x7A93F0
        if (i64(v1) > 0) {
            goto L_005612f8;
        }
        // 0x00561308 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_005612f8:
    charge(ctx, 4);
    v1 = slti(a1, -999);
    v0 = si(-999);
    if (v1 != 0) a1 = v0;
    sw(a1, a0, 56);
    // 0x00561308 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00541BA0 sub_541BA0 -- 100 bytes, 2 chunks; frame 0x10: ra sp+0x0
// Stores the pan a2 clamped to -15..15 at a0+64+4*a1 unless the PS2RNA lock is held (0x7A93F8 == 1 with 0x7A93F0 <=
// 0).
void sub_541BA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00541ba0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x00561310
    charge(ctx, 6);
    v0 = 0x7B0000;
    a3 = 1;
    lw(v1, v0, -27656);  // 0x7A93F8
    t1 = slti(a2, -15);
    t0 = a0;
    if (v1 == a3) {
        // 0x00561328
        charge(ctx, 4);
        v0 = 0x7B0000;
        lw(v1, v0, -27664);  // 0x7A93F0
        if (i64(v1) > 0) {
            goto L_00561338;
        }
        // 0x00561358 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_00561338:
    charge(ctx, 8);
    v0 = si(-15);
    a0 = sll(a1, 2);
    if (t1 == 0) v0 = a2;
    a1 = 15;
    v1 = slti(v0, 16);
    a0 = addu(a0, t0);
    if (v1 == 0) v0 = a1;
    sw(v0, a0, 64);
    // 0x00561358 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00541BD0 sub_541BD0 -- 20 bytes; frame 0x10: ra sp+0x0
// Tail call: sub_561390.
void sub_541BD0(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00541bd0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_561390_00561390(ctx);  // tail call
}

// 0x00541CB8 __env_lock_7 -- 8 bytes; leaf frame (no stack)
// Empty function (returns).
void __env_lock_7(EEContext& ctx) {
    using namespace hg;
    // 0x00541cb8
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x00541CE8 r_lock_def_get_free_item_0 -- 24 bytes; leaf frame (no stack)
// Increments the counter at 0x78FF88 and returns it.
void r_lock_def_get_free_item_0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3};
    // 0x00541ce8
    enter(ctx, 6);  // entry check point + this block's cycles
    v1 = 0x790000;
    v1 = addiu(v1, -120);  // &0x78FF88
    lw(v0, v1, 0);  // 0x78FF88
    v0 = addiu(v0, 1);
    sw(v0, v1, 0);  // 0x78FF88
}

// 0x0054B748 sub_54B748 -- 408 bytes; frame 0x50: s1 sp+0x18, s3 sp+0x28, s4 sp+0x30, s5 sp+0x38, s0 sp+0x10, s2 sp+0x20, ra sp+0x40
// CRI SFD / ADX header parse: reads the chunk fields through the readers sub_5431D8 / sub_5431F0 / sub_543220 /
// sub_5430B8..sub_5430D8 / sub_542F88 / sub_5433C0, reporting "not enough data" (sub_53AE08) on a short buffer.
void sub_54B748(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x0054b748
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s1, sp, 0x18);
    s1 = a0;
    sd(s3, sp, 0x28);
    sd(s4, sp, 0x30);
    sd(s5, sp, 0x38);
    sd(s0, sp, 0x10);
    sd(s2, sp, 0x20);
    sd(ra, sp, 0x40);
    lw(s2, s1, 4);
    lw(s0, s1, 20);
    a0 = s2;
    jal(ctx, 0x54B774u, gen::fn_sub_5431D8_005431d8);
    a0 = s2;
    s3 = v0;
    jal(ctx, 0x54B780u, gen::fn_sub_5431F0_005431f0);
    a0 = s2;
    s5 = v0;
    jal(ctx, 0x54B78Cu, gen::fn_sub_543220_00543220);
    a0 = s0;
    s4 = v0;
    lbu(v0, s1, 2);
    a1 = 1;
    v0 = addiu(v0, -2);
    v0 = sltiu(v0, 2);
    a3 = sp;
    if (v0 == 0) {
        // 0x0054b7d8
        charge(ctx, 1);
        lw(v1, s0, 0);
    L_0054b7dc:
        charge(ctx, 9);
        lw(v0, v1, 24);
        jt = v0.u();  // the target, read before the delay slot
        link(ctx, 0x54B7E0u);  // $ra = the return address
        lw(a2, s1, 80);
        call_ptr(ctx, jt);
        a0 = 0x7C0000;
        lw(v0, sp, 0x4);
        lw(v1, s1, 80);
        v0 = slt(v0, v1);
        a0 = addiu(a0, 12352);  // "E8101201 adxt_trap_entry: not enough data"
        if (v0 != 0) {
            // 0x0054b800
            charge(ctx, 2);
            jal(ctx, 0x54B800u, gen::fn_sub_53AE08_0053ae08);
        }
        // 0x0054b808
        charge(ctx, 23);
        lw(v1, s0, 0);
        a2 = sp;
        a1 = 0;
        lw(v0, v1, 32);
        a0 = s0;
        jalr(ctx, 0x54B818u, v0.u());
        a0 = s2;
        a1 = 0;
        jal(ctx, 0x54B824u, gen::fn_sub_5430C8_005430c8);
        a1 = subu(s4, s3);
        sw(a1, s1, 144);
        a0 = s2;
        jal(ctx, 0x54B834u, gen::fn_sub_5430B8_005430b8);
        a0 = s2;
        a1 = s5;
        jal(ctx, 0x54B840u, gen::fn_sub_5430D8_005430d8);
        a0 = s2;
        a1 = s3;
        jal(ctx, 0x54B84Cu, gen::fn_sub_542F88_00542f88);
        lb(v1, s1, 2);
        v0 = 2;
        a0 = s0;
        if (v1 == v0) {
            // 0x0054b864
            charge(ctx, 17);
            lw(v0, s0, 0);
            lw(v1, v0, 20);
            jalr(ctx, 0x54B86Cu, v1.u());
            lw(v0, s0, 0);
            a2 = s5;
            a0 = s0;
            lw(v1, v0, 24);
            a1 = 1;
            a3 = sp;
            jalr(ctx, 0x54B888u, v1.u());
            lw(a2, s0, 0);
            a0 = s0;
            a1 = 0;
            lw(v0, a2, 32);
            a2 = sp;
            jalr(ctx, 0x54B8A0u, v0.u());
        }
        // 0x0054b8a8
        charge(ctx, 6);
        a0 = s2;
        jal(ctx, 0x54B8A8u, gen::fn_sub_5433C0_005433c0);
        lw(v0, s1, 76);
        v0 = addiu(v0, 1);
        sw(v0, s1, 76);
        ld(s0, sp, 0x10);
    } else {
        // 0x0054b7b4
        charge(ctx, 3);
        lb(v0, s1, 108);
        if (v0 != 0) {
            lw(v1, s0, 0);
            goto L_0054b7dc;
        }
        // 0x0054b7c0
        charge(ctx, 5);
        lw(a0, s1, 4);
        a1 = si(-1);
        jal(ctx, 0x54B7C4u, gen::fn_sub_5430B8_005430b8);
        ld(s0, sp, 0x10);
    }
    // 0x0054b8c0 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(s5, sp, 0x38);
    ld(ra, sp, 0x40);
    sp = addiu(sp, 0x50);
}

// 0x005526B0 sub_5526B0 -- 176 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// adxcs server init (ref-counted at 0x799964): on the first call, sub_53EA90, sub_554720, clears the 2480-byte state
// at 0x799978 and registers the "adxcs_dec_svr" / "adxcs_main_svr" servers (sub_564FE8 / sub_564DD0).
void sub_5526B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005526b0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x7A0000;
    sd(s0, sp, 0x0);
    s0 = addiu(v0, -26268);  // &0x799964
    sd(ra, sp, 0x8);
    v1 = 0x7A0000;
    lw(a0, s0, 0);  // 0x799964
    v1 = addiu(v1, -26272);  // &0x799960
    lw(v0, v1, 0);  // 0x799960
    v0 = addiu(a0, 1);
    if (a0 == 0) {
        // 0x005526dc
        charge(ctx, 28);
        jal(ctx, 0x5526DCu, gen::fn_sub_53EA90_0053ea90);
        jal(ctx, 0x5526E4u, gen::fn_sub_554720_00554720);
        a0 = 0x7A0000;
        a1 = 0;
        a0 = addiu(a0, -26248);  // &0x799978
        a2 = 2480;
        jal(ctx, 0x5526F8u, gen::fn_memset_00521408);
        a2 = 0x550000;
        t0 = 0x7C0000;
        a2 = addiu(a2, 9816);  // &sub_552658
        t0 = addiu(t0, 12760);  // "adxcs_dec_svr"
        a0 = 2;
        a1 = 0;
        a3 = 0;
        jal(ctx, 0x552718u, gen::fn_sub_564FE8_00564fe8);
        a1 = 0x550000;
        a3 = 0x7C0000;
        a0 = 5;
        a1 = addiu(a1, 9856);  // &sub_552680
        a3 = addiu(a3, 12776);  // "adxcs_main_svr"
        a2 = 0;
        jal(ctx, 0x552734u, gen::fn_sub_564DD0_00564dd0);
        v1 = 0x7A0000;
        sw(v0, v1, -26264);  // 0x799968
        lw(a0, s0, 0);
        v0 = addiu(a0, 1);
    }
    // 0x0055274c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x8);
    sw(v0, s0, 0);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x005530D0 sub_5530D0 -- 180 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// CRI ADX handle destroy: NULL check ("E2003050208"), stops the handle (sub_554360), releases its stream (+8,
// sub_5465A0 / sub_5546F0) and buffer (+4, sub_554940), calls the +144 object's release method for type 2 (+476),
// clears the fields and sub_554708.
void sub_5530D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005530d0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    if (s0 == 0) {
        // 0x005530e4
        charge(ctx, 6);
        a0 = 0x7C0000;
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        a0 = addiu(a0, 13176);  // "E2003050208 : NULL pointer is specified."
        sp = addiu(sp, 0x10);
        gen::fn_sub_552630_00552630(ctx);  // tail call
        return;
    }
    // 0x00553100
    charge(ctx, 5);
    jal(ctx, 0x553100u, gen::fn_sub_554360_00554360);
    lw(v0, s0, 8);
    a0 = v0;
    if (v0 != 0) {
        // 0x00553114
        charge(ctx, 2);
        jal(ctx, 0x553114u, gen::fn_sub_5465A0_005465a0);
    }
    // 0x0055311c
    charge(ctx, 5);
    jal(ctx, 0x55311Cu, gen::fn_sub_5546F0_005546f0);
    lw(v0, s0, 4);
    a0 = v0;
    if (v0 != 0) {
        // 0x00553130
        charge(ctx, 2);
        jal(ctx, 0x553130u, gen::fn_sub_554940_00554940);
    }
    // 0x00553138
    charge(ctx, 4);
    lw(v1, s0, 476);
    v0 = 2;
    if (v1 != v0) {
        sw(zero, s0, 428);
    } else {
        // 0x00553148
        charge(ctx, 4);
        lw(v0, s0, 144);
        sw(zero, s0, 144);
        a0 = v0;
        if (v0 != 0) {
            // 0x00553158
            charge(ctx, 4);
            lw(v0, v0, 0);
            lw(v1, v0, 12);
            jalr(ctx, 0x553160u, v1.u());
        }
        // 0x00553168
        charge(ctx, 1);
        sw(zero, s0, 428);
    }
    // 0x0055316c
    charge(ctx, 6);
    sw(zero, s0, 144);
    sb(zero, s0, 1);
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_554708_00554708(ctx);  // tail call
}

// 0x00558138 srd_exec_dvd -- 488 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, s2 sp+0x10, ra sp+0x18
// CRI SRD DVD request step: by the request state (jump table at 0x7C4750) issues sceCdRead, polls sceCdSync, breaks a
// request (sceCdBreak, logging "SRD: sceCdBreak is fail") and checks the drive error (srd_check_dvd_error).
void srd_exec_dvd(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00558138
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v1 = 1;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s0, sp, 0x0);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    lw(v0, s1, 4);
    lbu(a1, s1, 2);
    if (v0 == v1) {
        // 0x00558160
        charge(ctx, 4);
        lb(v1, s1, 2);
        v0 = sltiu(v1, 10);
        if (v0 == 0) {
            sw(zero, s1, 4);
        } else {
            // 0x00558170
            charge(ctx, 6);
            v0 = sll(v1, 2);
            v1 = 0x7C0000;
            v1 = addu(v1, v0);
            lw(v1, v1, 18256);
            switch (v1.u()) {
            case 0x558188u:  // table[2]
                // 0x00558188
                charge(ctx, 9);
                a0 = 5632;
                jal(ctx, 0x558188u, gen::fn_sub_558988_00558988);
                jal(ctx, 0x558190u, gen::fn_sceCdBreak_00510f88);
                s0 = v0;
                a0 = 5633;
                jal(ctx, 0x55819Cu, gen::fn_sub_558988_00558988);
                v0 = 0x7A0000;
                if (s0 == 0) {
                    // 0x005581ac
                    charge(ctx, 5);
                    a0 = 0x7C0000;
                    v0 = addiu(v0, 2308);
                    a0 = addiu(a0, 18216);  // "SRD: sceCdBreak is fail. %d\n"
                    link(ctx, 0x5581B8u);  // $ra first: the delay slot below depends on it
                    lw(a1, v0, 0);
                    call(ctx, gen::fn_scePrintf_00505e48);
                }
                // 0x005581c0
                charge(ctx, 15);
                a0 = 5888;
                jal(ctx, 0x5581C0u, gen::fn_sub_558988_00558988);
                a0 = 0;
                jal(ctx, 0x5581C8u, gen::fn_sceCdSync_00510148);
                a0 = 5889;
                jal(ctx, 0x5581D0u, gen::fn_sub_558988_00558988);
                sb(zero, s1, 2);
                v1 = 0x7A0000;
                a1 = 0;
                v1 = addiu(v1, 2316);  // &0x7A090C
                lw(v0, v1, 0);  // 0x7A090C
                v0 = addiu(v0, 1);
                sw(v0, v1, 0);  // 0x7A090C
                sw(zero, s1, 4);
                break;
            case 0x558200u:  // table[1, 3, 9]
                // 0x00558200
                charge(ctx, 2);
                sb(zero, s1, 2);
                a1 = 0;
            L_00558208:
                charge(ctx, 1);
                sw(zero, s1, 4);
                break;
            case 0x558208u:  // table[0, 4, 5, 6, 7, 8]
                goto L_00558208;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v1.u());
                return;
            }
        }
    }
    // 0x0055820c
    charge(ctx, 5);
    v0 = sll(a1, 24);
    v1 = 1;
    s2 = sra(v0, 24);
    if (s2 != v1) {
        v1 = 2;
    } else {
        // 0x00558220
        charge(ctx, 6);
        a0 = 6144;
        jal(ctx, 0x558220u, gen::fn_sub_558988_00558988);
        v0 = 0x7A0000;
        lw(v1, v0, 2344);  // 0x7A0928
        if (v1 != s2) {
            lw(a0, s1, 8);
        } else {
            // 0x00558238
            charge(ctx, 4);
            v0 = 0x7A0000;
            lbu(v1, v0, 2348);  // 0x7A092C
            sb(v1, s1, 21);
            lw(a0, s1, 8);
        }
        // 0x00558248
        charge(ctx, 9);
        a3 = addiu(s1, 20);
        lw(a1, s1, 12);
        link(ctx, 0x558250u);  // $ra first: the delay slot below depends on it
        lw(a2, s1, 16);
        call(ctx, gen::fn_sceCdRead_00510b80);
        a0 = 6145;
        s0 = v0;
        jal(ctx, 0x55825Cu, gen::fn_sub_558988_00558988);
        v0 = 9;
        if (s0 != s2) {
            // 0x00558290
            charge(ctx, 4);
            v1 = si(-1);
            sb(v0, s1, 2);
            a1 = 9;
            sw(v1, s1, 52);
        } else {
            // 0x0055826c
            charge(ctx, 9);
            v0 = 0x7A0000;
            a0 = 2;
            v0 = addiu(v0, 2312);  // &0x7A0908
            a1 = 2;
            lw(v1, v0, 0);  // 0x7A0908
            v1 = addiu(v1, 1);
            sw(v1, v0, 0);  // 0x7A0908
            sb(a0, s1, 2);
        }
        // 0x005582a0
        charge(ctx, 2);
        v0 = sll(a1, 24);
        v1 = 2;
    }
    // 0x005582a8
    charge(ctx, 3);
    v0 = sra(v0, 24);
    ld(s0, sp, 0x0);
    if (v0 == v1) {
        // 0x005582b4
        charge(ctx, 11);
        a0 = 6400;
        jal(ctx, 0x5582B4u, gen::fn_sub_558988_00558988);
        a0 = 1;
        jal(ctx, 0x5582BCu, gen::fn_sceCdSync_00510148);
        a0 = 6401;
        s0 = v0;
        jal(ctx, 0x5582C8u, gen::fn_sub_558988_00558988);
        a0 = s1;
        jal(ctx, 0x5582D0u, gen::fn_srd_check_dvd_error_00557fe8);
        v1 = v0;
        if (s0 == 0) {
            // 0x005582e0
            charge(ctx, 3);
            v0 = 1;
            if (v1 != v0) {
                v0 = 3;
            } else {
                // 0x005582ec
                charge(ctx, 1);
                v0 = 9;
            }
            // 0x005582f0
            charge(ctx, 6);
            sb(v0, s1, 2);
            v1 = 0x7A0000;
            v1 = addiu(v1, 2316);  // &0x7A090C
            lw(v0, v1, 0);  // 0x7A090C
            v0 = addiu(v0, 1);
            sw(v0, v1, 0);  // 0x7A090C
        }
        // 0x00558308
        charge(ctx, 1);
        ld(s0, sp, 0x0);
    }
    // 0x0055830c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x005584F0 __errno_4 -- 12 bytes; leaf frame (no stack)
// Returns the errno word at 0x7A08EC.
void __errno_4(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3};
    // 0x005584f0
    enter(ctx, 3);  // entry check point + this block's cycles
    v1 = 0x7A0000;
    lw(v0, v1, 2284);  // 0x7A08EC
}

// 0x00559588 dtx_create_rmt -- 108 bytes; frame 0x20: s0 sp+0x10, ra sp+0x18
// DTX remote create: packs a0..a3 into the RPC buffer at 0x9979C0 and calls DTX RPC function 2 (sceSifCallRpc);
// returns the IOP's reply word.
void dtx_create_rmt(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00559588
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x990000;
    sd(s0, sp, 0x10);
    s0 = 0x990000;
    v0 = addiu(v0, 31168);  // &0x9979C0
    sd(ra, sp, 0x18);
    s0 = addiu(s0, 31424);  // &0x997AC0
    v1 = 0x7A0000;
    sw(a0, v0, 0);  // 0x9979C0
    a0 = addiu(v1, 6624);  // &0x7A19E0
    sw(a1, v0, 4);  // 0x9979C4
    a1 = 2;
    sw(a2, v0, 8);  // 0x9979C8
    a2 = 0;
    sw(a3, v0, 12);  // 0x9979CC
    a3 = v0;
    t1 = s0;
    t0 = 16;
    t2 = 4;
    t3 = 0;
    link(ctx, 0x5595D8u);  // $ra first: the delay slot below depends on it
    sw(zero, sp, 0x0);
    call(ctx, gen::fn_sceSifCallRpc_00507230);
    ld(ra, sp, 0x18);
    lw(v0, s0, 0);  // 0x997AC0
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0055A198 sub_55A198 -- 52 bytes; leaf frame (no stack)
// Returns the last free entry (first byte 0) of the 40 x 72-byte dvCi handle table at 0x7A1DF0, or 0.
void sub_55A198(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0055a198
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0x7A0000;
    a1 = 0;
    v1 = addiu(v0, 7664);  // &0x7A1DF0
    a0 = 39;
    for (;;) {
        // 0x0055a1a8
        charge(ctx, 7);
        lb(v0, v1, 0);
        a0 = addiu(a0, -1);
        v0 = v0 ^ 0x0;
        if (v0 == 0) a1 = v1;
        v1 = addiu(v1, 72);
        if (i64(a0) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0055a1c4
    charge(ctx, 2);
    v0 = a1;
}

// 0x0055A1F0 dvCiOpen -- 376 bytes; frame 0x30: s2 sp+0x10, s0 sp+0x0, s1 sp+0x8, s3 sp+0x18, s4 sp+0x20, ra sp+0x28
// dvCi (CD file system) open: validates the name and mode, takes a free handle (sub_55A198), resolves the file's LSN
// / size (dvci_get_fstate, or dvci_conv_fname + dvCiCdSearchFile after sceCdSync on a cache miss) and fills the
// handle.
void dvCiOpen(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055a1f0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s2, sp, 0x10);
    s2 = a0;
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(s3, sp, 0x18);
    sd(s4, sp, 0x20);
    sd(ra, sp, 0x28);
    if (s2 == 0) {
        // 0x0055a214
        charge(ctx, 3);
        a1 = 0x7C0000;
        a1 = addiu(a1, 19664);  // "E0092908:fname is null.(dvCiOpen)"
        goto L_0055a258;
    }
    // 0x0055a220
    charge(ctx, 2);
    a1 = 0x7C0000;
    if (a2 != 0) {
        // 0x0055a228
        charge(ctx, 3);
        a0 = 0;
        a1 = addiu(a1, 19704);
        goto L_0055a258;
    }
    // 0x0055a238
    charge(ctx, 5);
    jal(ctx, 0x55A238u, gen::fn_sub_55A198_0055a198);
    s1 = v0;
    s3 = addiu(s1, 32);
    if (s1 != 0) {
        // 0x0055a268
        charge(ctx, 6);
        a0 = s2;
        a1 = s3;
        jal(ctx, 0x55A26Cu, gen::fn_dvci_get_fstate_0055b220);
        lw(a1, s1, 36);
        s4 = v0;
        if (a1 != 0) {
            // 0x0055a2f8
            charge(ctx, 2);
            v0 = 1;
            sb(v0, s1, 1);
        L_0055a300:
            charge(ctx, 14);
            v0 = addiu(a1, 2047);
            v1 = 1;
            v0 = srl(v0, 11);
            a0 = 1;
            sw(v0, s1, 8);
            sb(v1, s1, 0);
            sw(a1, s1, 4);
            sw(zero, s1, 12);
            sw(zero, s1, 24);
            sw(zero, s1, 16);
            sw(zero, s1, 20);
            sb(zero, s1, 2);
            sw(zero, s1, 28);
            if (s4 == a0) {
                // 0x0055a338
                charge(ctx, 3);
                v0 = 0x7FFF0000;
                v0 = v0 | 0xFFFF;
                sw(v0, s1, 8);
            }
            // 0x0055a344
            charge(ctx, 1);
            v0 = s1;
        } else {
            // 0x0055a280
            charge(ctx, 20);
            s0 = 0x7A0000;
            a0 = s2;
            s0 = addiu(s0, 10544);  // &0x7A2930
            a1 = s0;
            jal(ctx, 0x55A28Cu, gen::fn_dvci_conv_fname_0055a9b0);
            a0 = 0x7C0000;
            a1 = s0;
            a0 = addiu(a0, 19792);  // "DVCI: File cache was not hit. \"%s\"\n"
            jal(ctx, 0x55A29Cu, gen::fn_sub_541760_00541760);
            a0 = 0x8300;
            jal(ctx, 0x55A2A4u, gen::fn_sub_558988_00558988);
            a0 = 0;
            jal(ctx, 0x55A2ACu, gen::fn_sceCdSync_00510148);
            a0 = 0x8301;
            jal(ctx, 0x55A2B4u, gen::fn_sub_558988_00558988);
            a0 = s3;
            a1 = s0;
            jal(ctx, 0x55A2C0u, gen::fn_dvCiCdSearchFile_00559dd8);
            if (v0 != 0) {
                sb(zero, s1, 1);
                // 0x0055a2f0
                charge(ctx, 2);
                lw(a1, s1, 36);
                goto L_0055a300;
            }
            // 0x0055a2d0
            charge(ctx, 8);
            a1 = 0x7C0000;
            a0 = 0;
            a1 = addiu(a1, 19832);  // "E0092911:sceCdSearchFile fail.(dvCiOpen)"
            jal(ctx, 0x55A2D8u, gen::fn_sub_559DA8_00559da8);
            a0 = s1;
            jal(ctx, 0x55A2E0u, gen::fn_sub_55A1D0_0055a1d0);
            v0 = 0;
        }
    } else {
        // 0x0055a24c
        charge(ctx, 3);
        a1 = 0x7C0000;
        a0 = 0;
        a1 = addiu(a1, 19744);  // "E0092910:not enough handle resource.(dvCiOpen)"
    L_0055a258:
        charge(ctx, 4);
        jal(ctx, 0x55A258u, gen::fn_sub_559DA8_00559da8);
        v0 = 0;
    }
    // 0x0055a348 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x0055A3C0 dvCiSeek -- 148 bytes; frame 0x10: ra sp+0x0
// dvCi seek: sets the handle's sector position (+12) to a1 (whence a2: 0 set, 1 current, 2 from the size at +8),
// clamps it to 0..size, clears +20 and returns it; "handl is null" on a null handle.
void dvCiSeek(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0055a3c0
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a3 = a0;
    sd(ra, sp, 0x0);
    if (a3 != 0) {
        // 0x0055a3e8
        charge(ctx, 2);
        v0 = 2;
        if (a2 != 0) {
            // 0x0055a3f8
            charge(ctx, 2);
            cc = a2 != v0;  // the condition, before the delay slot changes it
            v0 = 1;
            if (cc) {
                // 0x0055a410
                charge(ctx, 2);
                lw(a0, a3, 8);
                if (a2 == v0) {
                    // 0x0055a418
                    charge(ctx, 4);
                    lw(v0, a3, 12);
                    v0 = addu(v0, a1);
                    sw(v0, a3, 12);
                }
            } else {
                // 0x0055a400
                charge(ctx, 4);
                lw(a0, a3, 8);
                v0 = addu(a0, a1);
                sw(v0, a3, 12);
            }
        } else {
            // 0x0055a3f0
            charge(ctx, 2);
            sw(a1, a3, 12);
            // 0x0055a428
            charge(ctx, 1);
            lw(a0, a3, 8);
        }
        // 0x0055a42c
        charge(ctx, 7);
        lw(v0, a3, 12);
        sw(zero, a3, 20);
        v1 = slt(v0, a0);
        if (v1 == 0) v0 = a0;
        a0 = slti(v0, 0);
        if (a0 != 0) v0 = 0;
        sw(v0, a3, 12);
    } else {
        // 0x0055a3d0
        charge(ctx, 5);
        a1 = 0x7C0000;
        a1 = addiu(a1, 19880);  // "E0092912:handl is null."
        jal(ctx, 0x55A3D4u, gen::fn_sub_559DA8_00559da8);
        v0 = 0;
    }
    // 0x0055a448 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0055A490 dvCiReqRd -- 420 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// dvCi read request: validates the handle, sector count and buffer, then reads through SRD (SRD_Create / SRD_ReqRdDvd
// / SRD_ExecServer / SRD_WaitComplete, InvalidDCache on the buffer) in the configured CD read mode.
void dvCiReqRd(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055a490
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a2;
    sd(s2, sp, 0x10);
    s2 = a1;
    sd(s3, sp, 0x18);
    sd(ra, sp, 0x20);
    if (s0 == 0) {
        // 0x0055a4b8
        charge(ctx, 3);
        a1 = 0x7C0000;
        a1 = addiu(a1, 19880);  // "E0092912:handl is null."
        goto L_0055a4e8;
    }
    // 0x0055a4c8
    charge(ctx, 2);
    a1 = 0x7C0000;
    if (i64(s2) < 0) {
        // 0x0055a4d0
        charge(ctx, 2);
        a1 = addiu(a1, 19904);
        goto L_0055a4e8;
    }
    // 0x0055a4d8
    charge(ctx, 2);
    if (s1 != 0) {
        lb(v1, s0, 2);
        // 0x0055a4f8
        charge(ctx, 3);
        s3 = 2;
        v0 = 0;
        if (v1 != s3) {
            // 0x0055a504
            charge(ctx, 2);
            v1 = 1;
            if (s2 != 0) {
                // 0x0055a518
                charge(ctx, 5);
                jal(ctx, 0x55A518u, gen::fn_SRD_Create_00557a58);
                v1 = v0;
                sw(v1, s0, 28);
                if (v1 != 0) {
                    // 0x0055a52c
                    charge(ctx, 31);
                    a2 = 0x7A0000;
                    lw(v0, s0, 12);
                    a2 = addiu(a2, 10864);  // &dvg_ci_cdrmode
                    lw(v1, s0, 8);
                    lbu(a1, a2, 0);  // dvg_ci_cdrmode
                    a3 = s2;
                    v1 = subu(v1, v0);
                    a0 = s1;
                    sb(a1, s0, 68);
                    v0 = slt(s2, v1);
                    if (v0 == 0) a3 = v1;
                    lbu(t0, a2, 1);  // 0x7A2A71
                    a1 = sll(a3, 11);
                    a1 = addu(s1, a1);
                    sb(t0, s0, 69);
                    a1 = addiu(a1, -1);
                    lbu(v0, a2, 2);  // 0x7A2A72
                    sw(a3, s0, 16);
                    sb(v0, s0, 70);
                    link(ctx, 0x55A578u);  // $ra first: the delay slot below depends on it
                    sw(s1, s0, 24);
                    call(ctx, gen::fn_InvalidDCache_00503b98);
                    lw(v0, s0, 32);
                    lw(a1, s0, 12);
                    t0 = addiu(s0, 68);
                    lw(a0, s0, 28);
                    lw(a2, s0, 16);
                    a1 = addu(v0, a1);
                    link(ctx, 0x55A598u);  // $ra first: the delay slot below depends on it
                    lw(a3, s0, 24);
                    call(ctx, gen::fn_SRD_ReqRdDvd_00557b80);
                    if (v0 != 0) {
                        v0 = 0x7A0000;
                        // 0x0055a5b8
                        charge(ctx, 4);
                        v1 = 1;
                        lw(s1, v0, 10868);
                        if (s1 != v1) {
                            sb(s3, s0, 2);
                            // 0x0055a610
                            charge(ctx, 1);
                            lw(v1, s0, 16);
                        } else {
                            // 0x0055a5c8
                            charge(ctx, 18);
                            a0 = 0;
                            jal(ctx, 0x55A5C8u, gen::fn_sceCdSync_00510148);
                            jal(ctx, 0x55A5D0u, gen::fn_sub_558610_00558610);
                            jal(ctx, 0x55A5D8u, gen::fn_SRD_ExecServer_00558500);
                            link(ctx, 0x55A5E0u);  // $ra first: the delay slot below depends on it
                            lw(a0, s0, 28);
                            call(ctx, gen::fn_SRD_WaitComplete_00557e50);
                            link(ctx, 0x55A5E8u);  // $ra first: the delay slot below depends on it
                            lw(a0, s0, 28);
                            call(ctx, gen::fn_sub_557AE0_00557ae0);
                            sw(zero, s0, 28);
                            lw(v0, s0, 12);
                            lw(v1, s0, 16);
                            sw(s2, s0, 20);
                            v0 = addu(v0, v1);
                            sb(s1, s0, 2);
                            sw(v0, s0, 12);
                        }
                        // 0x0055a614
                        charge(ctx, 1);
                        v0 = v1;
                    } else {
                        // 0x0055a5a8
                        charge(ctx, 4);
                        link(ctx, 0x55A5A8u);  // $ra first: the delay slot below depends on it
                        lw(a0, s0, 28);
                        call(ctx, gen::fn_sub_557AE0_00557ae0);
                        v0 = 0;
                    }
                }
            } else {
                // 0x0055a50c
                charge(ctx, 2);
                sb(v1, s0, 2);
            }
        }
    } else {
        // 0x0055a4e0
        charge(ctx, 2);
        a1 = 0x7C0000;
        a1 = addiu(a1, 19936);  // "E0092914:buf is null.(dvCiReqRd)"
    L_0055a4e8:
        charge(ctx, 4);
        jal(ctx, 0x55A4E8u, gen::fn_sub_559DA8_00559da8);
        v0 = 0;
    }
    // 0x0055a618 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0055A758 sub_55A758 -- 8 bytes; leaf frame (no stack)
// Returns 2048 (the dvCi sector size).
void sub_55A758(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0055a758
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 2048;
}

// 0x0055A760 sub_55A760 -- 76 bytes; frame 0x10: ra sp+0x0
// Returns the file size in bytes (sectors at +20 << 11) of an open dvCi handle (+2 == 1), else 0; "handl is null" on
// a null handle.
void sub_55A760(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055a760
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = a0;
    sd(ra, sp, 0x0);
    if (a1 != 0) {
        // 0x0055a788
        charge(ctx, 4);
        lb(v1, a1, 2);
        v0 = 1;
        if (v1 != v0) {
            v0 = 0;
        } else {
            // 0x0055a798
            charge(ctx, 2);
            lw(v0, a1, 20);
            v0 = sll(v0, 11);
        }
    } else {
        // 0x0055a770
        charge(ctx, 5);
        a1 = 0x7C0000;
        a1 = addiu(a1, 19880);  // "E0092912:handl is null."
        jal(ctx, 0x55A774u, gen::fn_sub_559DA8_00559da8);
        v0 = 0;
    }
    // 0x0055a7a0 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0055A898 sub_55A898 -- 16 bytes; leaf frame (no stack)
// Returns the handle's +20 >> 21.
void sub_55A898(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0055a898
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, a0, 20);
    v0 = dsll(v0, 11);
    v0 = dsra32(v0, 0);
}

// 0x0055A8A8 sub_55A8A8 -- 32 bytes; leaf frame (no stack)
// Returns the handle's +20 << 11 (the size in bytes).
void sub_55A8A8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0055a8a8
    enter(ctx, 8);  // entry check point + this block's cycles
    lw(v0, a0, 20);
    v1 = lui(0xFFFF);
    v1 = dsrl32(v1, 0);
    v0 = dsll(v0, 11);
    v0 = v0 & v1;
    v0 = dsll32(v0, 0);
    v0 = dsra32(v0, 0);
}

// 0x0055A8E8 sub_55A8E8 -- 196 bytes; frame 0x10: ra sp+0x0
// dvCi get-status dispatch: query a1 = 200 (sub_55A898), 201 (sub_55A8A8), 202 / 204 (sub_55A8C8), 203 / 205
// (sub_55A8D0), 299 (1); others 0.
void sub_55A8E8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0055a8e8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = 0;
    sd(ra, sp, 0x0);
    v0 = 0;
    if (a0 != 0) {
        // 0x0055a8fc
        charge(ctx, 3);
        v0 = 203;
        cc = a1 == v0;  // the condition, before the delay slot changes it
        v0 = slti(a1, 204);
        if (!cc) {
            // 0x0055a908
            charge(ctx, 2);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = 205;
            if (cc) {
                // 0x0055a938
                charge(ctx, 2);
                cc = a1 == v0;  // the condition, before the delay slot changes it
                v0 = slti(a1, 205);
                if (cc) {
                    goto L_0055a988;
                }
                // 0x0055a940
                charge(ctx, 2);
                cc = v0 != 0;  // the condition, before the delay slot changes it
                v0 = 299;
                if (cc) {
                L_0055a978:
                    charge(ctx, 4);
                    jal(ctx, 0x55A978u, gen::fn_sub_55A8C8_0055a8c8);
                    v1 = v0;
                L_0055a99c:
                    charge(ctx, 1);
                    v0 = v1;
                    goto L_0055a9a0;
                }
                // 0x0055a948
                charge(ctx, 2);
                cc = a1 == v0;  // the condition, before the delay slot changes it
                v0 = v1;
                if (cc) {
                    // 0x0055a998
                    charge(ctx, 1);
                    v1 = 1;
                    goto L_0055a99c;
                }
                // 0x0055a950
                charge(ctx, 2);
                ld(ra, sp, 0x0);
            } else {
                // 0x0055a910
                charge(ctx, 3);
                v0 = 201;
                cc = a1 == v0;  // the condition, before the delay slot changes it
                v0 = slti(a1, 202);
                if (cc) {
                    // 0x0055a968
                    charge(ctx, 4);
                    jal(ctx, 0x55A968u, gen::fn_sub_55A8A8_0055a8a8);
                    v1 = v0;
                    goto L_0055a99c;
                }
                // 0x0055a91c
                charge(ctx, 2);
                cc = v0 == 0;  // the condition, before the delay slot changes it
                v0 = 200;
                if (cc) {
                    goto L_0055a978;
                }
                // 0x0055a924
                charge(ctx, 2);
                cc = a1 == v0;  // the condition, before the delay slot changes it
                v0 = v1;
                if (cc) {
                    // 0x0055a958
                    charge(ctx, 4);
                    jal(ctx, 0x55A958u, gen::fn_sub_55A898_0055a898);
                    v1 = v0;
                    goto L_0055a99c;
                }
                // 0x0055a92c
                charge(ctx, 2);
                ld(ra, sp, 0x0);
            }
            // 0x0055a9a4 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            sp = addiu(sp, 0x10);
            return;
        }
    L_0055a988:
        charge(ctx, 4);
        jal(ctx, 0x55A988u, gen::fn_sub_55A8D0_0055a8d0);
        v1 = v0;
        goto L_0055a99c;
    }
L_0055a9a0:
    charge(ctx, 1);
    ld(ra, sp, 0x0);
    // 0x0055a9a4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x0055B120 dvci_is_lsn_access_fname -- 60 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// True when the name a0 is a 17-character "XXXXXXXX.YYYYYYYY" LSN-access name (a '.' at index 8).
void dvci_is_lsn_access_fname(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0055b120
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x55B12Cu, gen::fn_strlen_00524388);
    v1 = 17;
    cc = v0 != v1;  // the condition, before the delay slot changes it
    v0 = 0;
    if (!cc) {
        // 0x0055b140
        charge(ctx, 3);
        lb(v0, s0, 8);
        v0 = v0 ^ 0x2E;
        v0 = sltiu(v0, 1);
    }
    // 0x0055b14c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00564EF8 sub_564EF8 -- 60 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Locked call: sub_564978 (lock), sub_564F38(a0, a1), sub_564990 (unlock).
void sub_564EF8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00564ef8
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x564F0Cu, gen::fn_sub_564978_00564978);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x564F18u, gen::fn_sub_564F38_00564f38);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_564990_00564990(ctx);  // tail call
}

// 0x0057D518 sub_57D518 -- 152 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Middleware file open step: re-validates the file (sub_597368 on +60) and registers the completion callback
// (sub_58BEF0); on failure sets the error -303 (sub_57FC60) and reports the "E0203261" / "E0203262" message
// (sub_585590); returns 0 or -1.
void sub_57D518(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057d518
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    lw(s1, s0, 60);
    sw(zero, s0, 60);
    a0 = s1;
    jal(ctx, 0x57D534u, gen::fn_sub_597368_00597368);
    a1 = 0x580000;
    a0 = s1;
    a1 = addiu(a1, -648);  // &r_lock_def_get_free_item_2
    a2 = s0;
    if (v0 != 0) {
        // 0x0057d550
        charge(ctx, 3);
        a0 = 0x7C0000;
        a0 = addiu(a0, 32232);  // "E0203261: MWSFCRE_ResetSfdHn: SFD_Stop() failed."
        goto L_0057d580;
    }
    // 0x0057d560
    charge(ctx, 4);
    link(ctx, 0x57D560u);  // $ra first: the delay slot below depends on it
    sw(s1, s0, 60);
    call(ctx, gen::fn_sub_58BEF0_0058bef0);
    a0 = s0;
    if (v0 == 0) {
        // 0x0057d590
        charge(ctx, 3);
        jal(ctx, 0x57D590u, gen::fn_sub_57D220_0057d220);
        v0 = 0;
    } else {
        // 0x0057d570
        charge(ctx, 4);
        a0 = si(-303);
        jal(ctx, 0x57D570u, gen::fn_sub_57FC60_0057fc60);
        a0 = 0x7C0000;
        a0 = addiu(a0, 32288);  // "E0203262: MWSFCRE_ResetSfdHn: SFD_SetErrFn() failed."
    L_0057d580:
        charge(ctx, 4);
        jal(ctx, 0x57D580u, gen::fn_sub_585590_00585590);
        v0 = si(-1);
    }
    // 0x0057d59c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0057FC60 sub_57FC60 -- 44 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Stores the error code a0 in the current thread's key block (+104 of __gthread_get_ee_key_use()); returns a0.
void sub_57FC60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057fc60
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x57FC6Cu, gen::fn___gthread_get_ee_key_use_0057f740);
    sw(s0, v0, 104);
    v0 = s0;
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00580F10 sub_580F10 -- 100 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Starts a DMA receive on channel 8 (SPR from): tag +128 = a0, a1 / 16 quadwords into a2 (sceDmaRecvN).
void sub_580F10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00580f10
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    s1 = a0;
    a0 = 8;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x580F30u, gen::fn_sceDmaGetChan_004fa8f0);
    a0 = addiu(s0, 15);
    v1 = slti(s0, 0);
    sw(s1, v0, 128);
    if (v1 != 0) s0 = a0;
    a0 = v0;
    a1 = s2;
    a2 = sra(s0, 4);
    jal(ctx, 0x580F50u, gen::fn_sceDmaRecvN_004fadc0);
    v0 = 0;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00580FE8 sub_580FE8 -- 100 bytes; frame 0x20: s0 sp+0x0, s2 sp+0x10, s1 sp+0x8, ra sp+0x18
// Starts a DMA send on channel 9 (SPR to): tag +128 = a2, a1 / 16 quadwords from a0 (sceDmaSendN).
void sub_580FE8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00580fe8
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s2, sp, 0x10);
    s2 = a0;
    a0 = 9;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x18);
    s1 = a2;
    jal(ctx, 0x581008u, gen::fn_sceDmaGetChan_004fa8f0);
    a0 = addiu(s0, 15);
    v1 = slti(s0, 0);
    sw(s1, v0, 128);
    if (v1 != 0) s0 = a0;
    a0 = v0;
    a1 = s2;
    a2 = sra(s0, 4);
    jal(ctx, 0x581028u, gen::fn_sceDmaSendN_004fac88);
    v0 = 0;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00585590 sub_585590 -- 148 bytes; frame 0x80: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Middleware error print: formats a0, ... (vsprintf) into the cleared 0x9A6DC0 buffer and reports it (sinl_11).
void sub_585590(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15}, f16{ctx, 16}, f17{ctx, 17}, f18{ctx, 18}, f19{ctx, 19};
    // 0x00585590
    enter(ctx, 37);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(s0, sp, 0x0);
    s0 = 0x9A0000;
    s0 = addiu(s0, 28096);  // &0x9A6DC0
    sd(s1, sp, 0x8);
    sd(a1, sp, 0x48);
    a1 = 0;
    sd(a2, sp, 0x50);
    a2 = 256;
    s1 = a0;
    a0 = s0;
    sd(ra, sp, 0x10);
    sd(a3, sp, 0x58);
    sd(t0, sp, 0x60);
    sd(t1, sp, 0x68);
    sd(t2, sp, 0x70);
    sd(t3, sp, 0x78);
    swc1(f12, sp, 0x28);
    swc1(f13, sp, 0x2C);
    swc1(f14, sp, 0x30);
    swc1(f15, sp, 0x34);
    swc1(f16, sp, 0x38);
    swc1(f17, sp, 0x3C);
    swc1(f18, sp, 0x40);
    link(ctx, 0x5855F0u);  // $ra first: the delay slot below depends on it
    swc1(f19, sp, 0x44);
    call(ctx, gen::fn_memset_00521408);
    a2 = addiu(sp, 0x48);
    a1 = s1;
    a0 = s0;
    jal(ctx, 0x585600u, gen::fn_vsprintf_005288c8);
    a0 = s0;
    jal(ctx, 0x585608u, gen::fn_sinl_11_00585658);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x80);
}

// 0x00589BE0 sub_589BE0 -- 96 bytes; frame 0x10: ra sp+0x0
// Returns 0 when the stream slot a1 of a0 (+4884 + 116*a1) is busy, else sub_59BC20.
void sub_589BE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00589be0
    enter(ctx, 15);  // entry check point + this block's cycles
    v0 = sll(a1, 3);
    sp = addiu(sp, -0x10);
    v0 = subu(v0, a1);
    sd(ra, sp, 0x0);
    v0 = sll(v0, 2);
    t1 = addiu(a0, 4880);
    v0 = addu(v0, a1);
    v1 = a2;
    v0 = sll(v0, 2);
    t0 = a3;
    t1 = addu(t1, v0);
    a3 = v1;
    lw(v1, t1, 4);
    a2 = 11;
    if (v1 != 0) {
        // 0x00589c30
        charge(ctx, 4);
        ld(ra, sp, 0x0);
        v0 = 0;
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00589c1c
    charge(ctx, 4);
    lw(a1, t1, 76);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_59BC20_0059bc20(ctx);  // tail call
}

// 0x0058A108 sub_58A108 -- 184 bytes; frame 0x40: s1 sp+0x18, s0 sp+0x10, s2 sp+0x20, s3 sp+0x28, s4 sp+0x30, ra sp+0x38
// Queues the value a1 into the 32-entry ring at a0+3884 (write index +3876, read index +3880) under a lock
// (sub_58C100 / sub_58C118), storing a2 at +3868; returns 1 when queued, 0 when full.
void sub_58A108(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058a108
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s1, sp, 0x18);
    s1 = a0;
    sd(s0, sp, 0x10);
    s0 = addiu(s1, 3376);
    a0 = sp;
    sd(s2, sp, 0x20);
    sd(s3, sp, 0x28);
    s3 = a1;
    sd(s4, sp, 0x30);
    s4 = 0;
    sd(ra, sp, 0x38);
    s2 = a2;
    jal(ctx, 0x58A138u, gen::fn_sub_58C100_0058c100);
    lw(a3, s0, 500);
    lw(v1, s0, 504);
    a0 = sp;
    a2 = addiu(a3, 31);
    a1 = slti(a3, 0);
    v0 = a3;
    v1 = subu(a3, v1);
    if (a1 != 0) v0 = a2;
    v1 = slti(v1, 32);
    v0 = sra(v0, 5);
    if (v1 != 0) {
        // 0x0058a16c
        charge(ctx, 10);
        v0 = sll(v0, 5);
        sw(s2, s0, 492);
        v0 = subu(a3, v0);
        s4 = 1;
        v0 = sll(v0, 2);
        v0 = addu(v0, s1);
        sw(s3, v0, 3884);
        lw(v1, s0, 500);
        v1 = addiu(v1, 1);
        sw(v1, s0, 500);
    }
    // 0x0058a194
    charge(ctx, 11);
    jal(ctx, 0x58A194u, gen::fn_sub_58C118_0058c118);
    v0 = s4;
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
}

// 0x005941A8 sub_5941A8 -- 316 bytes; frame 0x20: s1 sp+0x8, s2 sp+0x10, s0 sp+0x0, ra sp+0x18
// Video-input buffer reset: clears the state words and every 24-byte buffer entry (tags -1), zeroes the IPU-side
// counters and stores to the IPU DMA registers (0x1000B410 / B420 / B430).
void sub_5941A8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005941a8
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 1;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = 0;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x18);
    sw(v0, s1, 68);
    lw(v1, s1, 84);
    sw(zero, s1, 12);
    sw(zero, s1, 16);
    sw(zero, s1, 20);
    sw(zero, s1, 88);
    sw(zero, s1, 92);
    if (i64(v1) > 0) {
        // 0x005941e8
        charge(ctx, 2);
        lw(v1, s1, 80);
        a0 = si(-1);
        for (;;) {
            // 0x005941f0
            charge(ctx, 9);
            sw(zero, v1, 16);
            s2 = addiu(s2, 1);
            sw(zero, v1, 20);
            sd(a0, v1, 0);
            lw(v0, s1, 84);
            sd(a0, v1, 8);
            v0 = slt(s2, v0);
            v1 = addiu(v1, 24);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00594214
    charge(ctx, 3);
    lw(v0, s1, 8);
    s2 = 0;
    if (i64(v0) > 0) {
        // 0x00594220
        charge(ctx, 4);
        s0 = 0xFFF0000;
        s0 = s0 | 0xFFFF;
        lw(v0, s1, 0);
        for (;;) {
            // 0x00594230
            charge(ctx, 14);
            a1 = sll(s2, 11);
            lw(v1, s1, 4);
            a0 = sll(s2, 4);
            a1 = addu(a1, v0);
            a2 = 3;
            a0 = addu(v1, a0);
            a1 = a1 & s0;
            a3 = 128;
            s2 = addiu(s2, 1);
            jal(ctx, 0x594250u, gen::fn_sub_594108_00594108);
            lw(v0, s1, 8);
            v0 = slt(s2, v0);
            if (v0 == 0) {
                break;
            }
            lw(v0, s1, 0);
            backedge(ctx);
        }
    }
    // 0x00594268
    charge(ctx, 31);
    lw(a1, s1, 4);
    s0 = 0xFFF0000;
    s0 = s0 | 0xFFFF;
    a0 = sll(s2, 4);
    a0 = addu(a1, a0);
    a1 = a1 & s0;
    a3 = 0;
    a2 = 2;
    jal(ctx, 0x594284u, gen::fn_sub_594108_00594108);
    a0 = 0x10000000;
    lw(a2, s1, 4);
    v1 = 0x10000000;
    lw(v0, s1, 0);
    a1 = 0x10000000;
    a2 = a2 & s0;
    v1 = v1 | 0xB410;
    v0 = v0 & s0;
    a1 = a1 | 0xB430;
    a0 = a0 | 0xB420;
    sw(zero, a0, 0);  // 0x1000B420
    a0 = 5;
    sw(v0, v1, 0);  // 0x1000B410
    link(ctx, 0x5942C0u);  // $ra first: the delay slot below depends on it
    sw(a2, a1, 0);
    call(ctx, gen::fn_sub_5940A0_005940a0);
    v0 = 1;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00594AC0 sub_594AC0 -- 88 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Video-input buffer destroy: sub_5940A0(5), clears the IPU DMA registers (0x1000B420 / B410 / B430) and deletes the
// buffer's semaphore (+64); returns 1.
void sub_594AC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00594ac0
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    a0 = 5;
    jal(ctx, 0x594AD0u, gen::fn_sub_5940A0_005940a0);
    v0 = 0x10000000;
    v1 = 0x10000000;
    a0 = 0x10000000;
    v1 = v1 | 0xB410;
    v0 = v0 | 0xB420;
    a0 = a0 | 0xB430;
    sw(zero, v0, 0);  // 0x1000B420
    sw(zero, v1, 0);  // 0x1000B410
    sw(zero, a0, 0);  // 0x1000B430
    link(ctx, 0x594AFCu);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 64);
    call(ctx, gen::fn__sceDeleteSema_00503170);
    v0 = 1;
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00595988 sub_595988 -- 72 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Middleware request: when busy (sub_58C060) reports error 0xFF000143 (sub_58BE40), else sub_5959D0(a0, 0xFF000143).
void sub_595988(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00595988
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x595994u, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = s0;
    a1 = a1 | 0x143;
    if (v0 == 0) {
        // 0x005959c0
        charge(ctx, 4);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        gen::fn_sub_5959D0_005959d0(ctx);  // tail call
        return;
    }
    // 0x005959ac
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    a0 = 0;
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_58BE40_0058be40(ctx);  // tail call
}

// 0x00595BA0 sub_595BA0 -- 20 bytes; frame 0x10: ra sp+0x0
// Tail call: sub_599B80.
void sub_595BA0(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00595ba0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_599B80_00599b80(ctx);  // tail call
}

// 0x00595BE8 sub_595BE8 -- 120 bytes; frame 0x20: s0 sp+0x0, ra sp+0x18, s1 sp+0x8, s2 sp+0x10
// Polls the 8 handles at 0x7B4774: for each idle one (sub_58C060 == 0) runs sub_595BC0, stopping with its result when
// that is 0; returns 1 after all 8.
void sub_595BE8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00595be8
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x7B0000;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x18);
    sd(s1, sp, 0x8);
    s1 = addiu(v0, 18292);  // &0x7B4774
    sd(s2, sp, 0x10);
    s2 = 0;
    lw(s0, s1, 0);  // 0x7B4774
    for (;;) {
        // 0x00595c10
        charge(ctx, 5);
        s1 = addiu(s1, 4);
        a0 = s0;
        jal(ctx, 0x595C14u, gen::fn_sub_58C060_0058c060);
        a0 = s0;
        if (v0 == 0) {
            // 0x00595c24
            charge(ctx, 4);
            jal(ctx, 0x595C24u, gen::fn_sub_595BC0_00595bc0);
            ld(s0, sp, 0x0);
            if (v0 == 0) {
                break;
            }
            goto L_00595c34;
        }
    L_00595c34:
        charge(ctx, 4);
        s2 = addiu(s2, 1);
        v0 = slti(s2, 8);
        if (v0 == 0) {
            goto L_00595c44_4;
        }
        lw(s0, s1, 0);
        backedge(ctx);
    }
    // 0x00595c4c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    return;
L_00595c44_4:
    charge(ctx, 2);
    v0 = 1;
    ld(s0, sp, 0x0);
    // 0x00595c4c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00595C60 sub_595C60 -- 84 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Middleware request: when busy (sub_58C060) reports error 0xFF000138 (sub_58BE40), else sub_595D10(a0, 0xFF000138)
// and returns 0.
void sub_595C60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00595c60
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x595C6Cu, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = s0;
    a1 = a1 | 0x138;
    if (v0 == 0) {
        // 0x00595c98
        charge(ctx, 7);
        jal(ctx, 0x595C98u, gen::fn_sub_595D10_00595d10);
        v0 = 0;
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00595c84
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    a0 = 0;
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_58BE40_0058be40(ctx);  // tail call
}

// 0x005972B0 sub_5972B0 -- 128 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Middleware stop request: when busy reports error 0xFF000132 (sub_58BE40); otherwise by sub_599408(a0, 47) stops
// through sub_5959D0 or sub_597330, then sets +68 = 1.
void sub_5972B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005972b0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x5972BCu, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = s0;
    a1 = a1 | 0x132;
    if (v0 != 0) {
        // 0x005972d4
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        a0 = 0;
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x005972e8
    charge(ctx, 5);
    a1 = 47;
    jal(ctx, 0x5972E8u, gen::fn_sub_599408_00599408);
    v1 = 1;
    a0 = s0;
    if (v0 != v1) {
        // 0x00597310
        charge(ctx, 3);
        jal(ctx, 0x597310u, gen::fn_sub_597330_00597330);
        v1 = 1;
    } else {
        // 0x005972fc
        charge(ctx, 4);
        jal(ctx, 0x5972FCu, gen::fn_sub_5959D0_005959d0);
        v1 = 1;
    }
    // 0x0059731c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x8);
    sw(v1, s0, 68);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0059BCF0 sub_59BCF0 -- 220 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Middleware timer / playback record init: clears the 448-byte record and sets its defaults (rate 1/10, 16683 us
// frame, 200000 / 1000000 limits) around sub_59BDD0 / sub_59C480.
void sub_59BCF0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059bcf0
    enter(ctx, 55);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = 0;
    a2 = 448;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x59BD04u, gen::fn_memset_00521408);
    v1 = 1;
    v0 = 10;
    sw(v1, s0, 12);
    sw(v0, s0, 16);
    a0 = s0;
    sw(v1, s0, 0);
    sw(zero, s0, 4);
    link(ctx, 0x59BD28u);  // $ra first: the delay slot below depends on it
    sw(zero, s0, 8);
    call(ctx, gen::fn_sub_59BDD0_0059bdd0);
    sd(zero, s0, 264);
    v1 = 0xF0000;
    v1 = v1 | 0x4240;
    v0 = 1;
    a0 = 16683;
    a1 = 0x30000;
    a1 = a1 | 0xD40;
    a2 = si(-1);
    sd(v0, s0, 304);
    sd(a0, s0, 312);
    sd(a1, s0, 328);
    sd(v1, s0, 368);
    sd(a2, s0, 376);
    sw(zero, s0, 440);
    sd(v0, s0, 272);
    sd(zero, s0, 280);
    sd(v0, s0, 288);
    sd(zero, s0, 296);
    sd(v1, s0, 320);
    sd(v1, s0, 336);
    sd(zero, s0, 344);
    sd(v1, s0, 352);
    sd(zero, s0, 360);
    sd(zero, s0, 384);
    sd(zero, s0, 392);
    sw(zero, s0, 400);
    sw(zero, s0, 404);
    sw(zero, s0, 408);
    sw(zero, s0, 412);
    sw(zero, s0, 416);
    sw(zero, s0, 420);
    sw(zero, s0, 424);
    sw(zero, s0, 428);
    sw(zero, s0, 432);
    sw(zero, s0, 436);
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_59C480_0059c480(ctx);  // tail call
}

// 0x0059BEF0 sub_59BEF0 -- 1128 bytes; frame 0x40: s0 sp+0x0, s3 sp+0x18, s5 sp+0x28, s6 sp+0x30, s1 sp+0x8, s2 sp+0x10, s4 sp+0x20, ra sp+0x38
// Middleware playback clock update: 64-bit time arithmetic (__muldi3 / __divdi3) on the record's counters with
// sub_59BDD0 / sub_59C358 / sub_59C3B8 / sub_59C5E0.
void sub_59BEF0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0059bef0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v1 = 1;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s3, sp, 0x18);
    s3 = a1;
    sd(s5, sp, 0x28);
    s5 = a2;
    sd(s6, sp, 0x30);
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(s4, sp, 0x20);
    sd(ra, sp, 0x38);
    ld(v0, s5, 8);
    s6 = a3;
    if (v0 == v1) {
        // 0x0059bf3c (the shared epilogue, written out on this path)
        charge(ctx, 14);
        ld(v0, s3, 0);
        ld(s0, sp, 0x0);
        sd(v0, s6, 0);
        ld(s1, sp, 0x8);
        ld(v1, s3, 8);
        ld(s2, sp, 0x10);
        sd(v1, s6, 8);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(s5, sp, 0x28);
        ld(s6, sp, 0x30);
        ld(ra, sp, 0x38);
        sp = addiu(sp, 0x40);
        return;
    }
    // 0x0059bf30
    charge(ctx, 3);
    lw(v0, s0, 0);
    if (v0 == 0) {
        // 0x0059bf3c (the shared epilogue, written out on this path)
        charge(ctx, 14);
        ld(v0, s3, 0);
        ld(s0, sp, 0x0);
        sd(v0, s6, 0);
        ld(s1, sp, 0x8);
        ld(v1, s3, 8);
        ld(s2, sp, 0x10);
        sd(v1, s6, 8);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(s5, sp, 0x28);
        ld(s6, sp, 0x30);
        ld(ra, sp, 0x38);
        sp = addiu(sp, 0x40);
        return;
    }
    ld(a1, s3, 0);
    // 0x0059bf78
    charge(ctx, 7);
    a3 = 1;
    ld(v0, s0, 392);
    lw(a0, s0, 4);
    v1 = slt(a1, v0);
    if (v1 != 0) a1 = v0;
    sd(a1, s3, 0);
    if (a0 == a3) {
        // 0x0059bf94
        charge(ctx, 3);
        sw(zero, s0, 8);
        s2 = 0;
        // 0x0059c040
        charge(ctx, 1);
        ld(a2, s0, 392);
        goto L_0059c044;
    }
    // 0x0059bfa0
    charge(ctx, 3);
    lw(s2, s0, 8);
    ld(a2, s0, 392);
    if (s2 != 0) {
    L_0059c044:
        charge(ctx, 1);
        ld(v0, s3, 0);
    } else {
        // 0x0059bfac
        charge(ctx, 3);
        v0 = slt(a2, a1);
        if (v0 != 0) {
            // 0x0059bfb8
            charge(ctx, 4);
            ld(v1, s0, 376);
            v0 = si(-1);
            sw(a3, s0, 8);
            if (v1 != v0) {
                // 0x0059bfe0
                charge(ctx, 4);
                ld(a1, s0, 360);
                link(ctx, 0x59BFE4u);  // $ra first: the delay slot below depends on it
                ld(a0, s3, 8);
                call(ctx, gen::fn___muldi3_0052ea78);
                ld(a1, s0, 368);
            } else {
                // 0x0059bfc8
                charge(ctx, 5);
                ld(a1, s0, 344);
                link(ctx, 0x59BFCCu);  // $ra first: the delay slot below depends on it
                ld(a0, s3, 8);
                call(ctx, gen::fn___muldi3_0052ea78);
                ld(a1, s0, 352);
            }
            // 0x0059bff0
            charge(ctx, 13);
            a0 = v0;
            jal(ctx, 0x59BFF0u, gen::fn___divdi3_0052eeb0);
            a1 = v0;
            ld(v1, s5, 0);
            a0 = s0;
            sd(v1, s0, 376);
            ld(v0, s3, 0);
            v0 = v0 + a1;
            link(ctx, 0x59C010u);  // $ra first: the delay slot below depends on it
            sd(v0, s0, 384);
            call(ctx, gen::fn_sub_59BDD0_0059bdd0);
            ld(a2, s0, 392);
            lw(s2, s0, 8);
            goto L_0059c044;
        }
        lw(v0, s0, 12);
        // 0x0059c028
        charge(ctx, 2);
        if (v0 == 0) {
            // 0x0059c030
            charge(ctx, 3);
            sw(a3, s0, 8);
            s2 = 1;
            goto L_0059c044;
        }
        ld(v0, s3, 0);
    }
    // 0x0059c048
    charge(ctx, 6);
    a0 = si(-1);
    ld(s1, s0, 376);
    v1 = slt(v0, a2);
    if (v1 != 0) v0 = a2;
    sd(v0, s0, 392);
    if (s1 == a0) {
        // 0x0059c088
        charge(ctx, 1);
        s4 = 0;
    } else {
        // 0x0059c060
        charge(ctx, 10);
        ld(a1, s5, 0);
        ld(a0, s3, 8);
        a1 = a1 - s1;
        jal(ctx, 0x59C068u, gen::fn___muldi3_0052ea78);
        ld(a1, s5, 8);
        a0 = v0;
        jal(ctx, 0x59C074u, gen::fn___divdi3_0052eeb0);
        ld(v1, s0, 384);
        s4 = v1 + v0;
    }
    // 0x0059c08c
    charge(ctx, 2);
    if (s2 != 0) {
        lw(v1, s0, 12);
        // 0x0059c0e0
        charge(ctx, 3);
        v0 = 1;
        cc = v1 != v0;  // the condition, before the delay slot changes it
        v0 = si(-1);
        if (!cc) {
            // 0x0059c0ec
            charge(ctx, 11);
            ld(a1, s0, 328);
            link(ctx, 0x59C0F0u);  // $ra first: the delay slot below depends on it
            ld(a0, s3, 8);
            call(ctx, gen::fn___muldi3_0052ea78);
            ld(a1, s0, 336);
            a0 = v0;
            jal(ctx, 0x59C0FCu, gen::fn___divdi3_0052eeb0);
            ld(a1, s3, 0);
            v1 = v0;
            v0 = a1 - s4;
            cc = i64(v0) < 0;  // the condition, before the delay slot changes it
            v0 = slt(v1, v0);
            if (!cc) {
                // 0x0059c118
                charge(ctx, 2);
                if (v0 != 0) {
                    ld(v0, s5, 0);
                    goto L_0059c13c;
                }
                // 0x0059c120
                charge(ctx, 2);
                a1 = a1 - s4;
                goto L_0059c168;
            }
            // 0x0059c128
            charge(ctx, 4);
            v0 = s4 - a1;
            v0 = slt(v1, v0);
            a1 = a1 - s4;
            if (v0 == 0) {
            L_0059c168:
                charge(ctx, 14);
                a1 = dsll32(a1, 0);
                a1 = dsra32(a1, 0);
                a0 = s0;
                jal(ctx, 0x59C170u, gen::fn_sub_59C358_0059c358);
                ld(a0, s3, 8);
                ld(a1, s0, 312);
                s1 = v0;
                jal(ctx, 0x59C180u, gen::fn___muldi3_0052ea78);
                ld(a1, s0, 320);
                a0 = v0;
                jal(ctx, 0x59C18Cu, gen::fn___divdi3_0052eeb0);
                s2 = v0;
                v0 = s1;
                if (i64(s1) < 0) {
                    // 0x0059c1a0
                    charge(ctx, 1);
                    v0 = 0 - v0;
                }
                // 0x0059c1a4
                charge(ctx, 3);
                v0 = slt(s2, v0);
                if (v0 == 0) {
                    lw(s2, s0, 8);
                } else {
                    // 0x0059c1b0
                    charge(ctx, 3);
                    v0 = slt(s2, s1);
                    a0 = dsll(s1, 1);
                    if (v0 == 0) {
                        // 0x0059c1e0
                        charge(ctx, 8);
                        a1 = s2;
                        jal(ctx, 0x59C1E0u, gen::fn___divdi3_0052eeb0);
                        lw(v1, s0, 408);
                        a0 = daddiu(v0, 1);
                        v0 = dsll32(a0, 0);
                        v0 = dsra32(v0, 0);
                        v1 = subu(v1, v0);
                        sw(v1, s0, 408);
                    } else {
                        // 0x0059c1bc
                        charge(ctx, 9);
                        a1 = s2;
                        jal(ctx, 0x59C1BCu, gen::fn___divdi3_0052eeb0);
                        lw(v1, s0, 404);
                        a0 = daddiu(v0, -1);
                        v0 = dsll32(a0, 0);
                        v0 = dsra32(v0, 0);
                        v1 = addu(v1, v0);
                        sw(v1, s0, 404);
                    }
                    // 0x0059c200
                    charge(ctx, 14);
                    a1 = s2;
                    jal(ctx, 0x59C200u, gen::fn___muldi3_0052ea78);
                    ld(v1, s5, 0);
                    a1 = dsrl32(v0, 31);
                    a0 = s0;
                    a1 = a1 + v0;
                    sd(v1, s0, 376);
                    a1 = dsra(a1, 1);
                    v0 = s4 + a1;
                    a1 = dsll32(a1, 0);
                    a1 = dsra32(a1, 0);
                    link(ctx, 0x59C22Cu);  // $ra first: the delay slot below depends on it
                    sd(v0, s0, 384);
                    call(ctx, gen::fn_sub_59C3B8_0059c3b8);
                    lw(s2, s0, 8);
                }
                // 0x0059c238
                charge(ctx, 1);
                ld(s1, s0, 376);
            } else {
                // 0x0059c138
                charge(ctx, 1);
                ld(v0, s5, 0);
            L_0059c13c:
                charge(ctx, 11);
                a0 = s0;
                sd(v0, s0, 376);
                ld(v1, s3, 0);
                link(ctx, 0x59C148u);  // $ra first: the delay slot below depends on it
                sd(v1, s0, 384);
                call(ctx, gen::fn_sub_59BDD0_0059bdd0);
                lw(v0, s0, 416);
                lw(s2, s0, 8);
                v0 = addiu(v0, 1);
                ld(s1, s0, 376);
                sw(v0, s0, 416);
            }
        L_0059c23c:
            charge(ctx, 1);
            v0 = si(-1);
        }
    } else {
        // 0x0059c094
        charge(ctx, 4);
        ld(v1, s0, 392);
        v0 = slt(v1, s4);
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = si(-1);
        if (!cc) {
            // 0x0059c0a4
            charge(ctx, 3);
            lw(v0, s0, 12);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            ld(v0, s5, 0);
            if (cc) {
                // 0x0059c0c0
                charge(ctx, 3);
                ld(v1, s0, 296);
                sd(v0, s0, 376);
                sd(v1, s0, 384);
            } else {
                // 0x0059c0b0
                charge(ctx, 3);
                sd(v1, s0, 384);
                sd(v0, s0, 376);
            }
            // 0x0059c0cc
            charge(ctx, 5);
            lw(v0, s0, 400);
            ld(s1, s0, 376);
            v0 = addiu(v0, 1);
            sw(v0, s0, 400);
            goto L_0059c23c;
        }
    }
    // 0x0059c240
    charge(ctx, 2);
    if (s1 == v0) {
        v1 = 0;
    } else {
        // 0x0059c248
        charge(ctx, 9);
        ld(a1, s5, 0);
        ld(a0, s3, 8);
        a1 = a1 - s1;
        jal(ctx, 0x59C250u, gen::fn___muldi3_0052ea78);
        ld(a1, s5, 8);
        a0 = v0;
        jal(ctx, 0x59C25Cu, gen::fn___divdi3_0052eeb0);
        ld(v1, s0, 384);
        v1 = v1 + v0;
    }
    // 0x0059c26c
    charge(ctx, 7);
    sd(v1, s6, 0);
    ld(v0, s3, 8);
    sd(v0, s6, 8);
    ld(a0, s0, 296);
    v0 = slt(v1, a0);
    if (v0 == 0) {
        ld(v0, s3, 0);
    } else {
        // 0x0059c288
        charge(ctx, 4);
        sd(a0, s6, 0);
        ld(v0, s0, 304);
        sd(v0, s6, 8);
        ld(v0, s3, 0);
    }
    // 0x0059c298
    charge(ctx, 18);
    sd(v0, s0, 264);
    ld(v1, s3, 8);
    sd(v1, s0, 272);
    ld(v0, s5, 0);
    sd(v0, s0, 280);
    ld(v1, s5, 8);
    sd(v1, s0, 288);
    ld(v0, s6, 0);
    sd(v0, s0, 296);
    ld(v1, s6, 8);
    sd(v1, s0, 304);
    ld(v0, s3, 0);
    ld(v1, s6, 0);
    v0 = v0 - v1;
    a3 = dsll32(v0, 0);
    a3 = dsra32(a3, 0);
    if (s2 != 0) {
        lw(v0, s0, 436);
        // 0x0059c308
        charge(ctx, 7);
        lw(v1, s0, 440);
        a0 = slt(a3, v0);
        a1 = slt(v1, a3);
        if (a0 == 0) v0 = a3;
        if (a1 == 0) v1 = a3;
        sw(v0, s0, 436);
        sw(v1, s0, 440);
    } else {
        // 0x0059c2e0
        charge(ctx, 9);
        lw(v0, s0, 428);
        lw(v1, s0, 432);
        a0 = slt(a3, v0);
        a1 = slt(v1, a3);
        if (a0 == 0) v0 = a3;
        if (a1 == 0) v1 = a3;
        sw(v0, s0, 428);
        sw(v1, s0, 432);
    }
    // 0x0059c324
    charge(ctx, 13);
    v0 = 0x7B0000;
    a0 = s0;
    sw(s0, v0, 18400);  // 0x7B47E0
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(s6, sp, 0x30);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
    gen::fn_sub_59C5E0_0059c5e0(ctx);  // tail call
}

// 0x0059FD10 sub_59FD10 -- 64 bytes; frame 0x10: ra sp+0x0
// Increments the call counter at 0x7B4930 and, when a hook is installed (0x7B4928), calls it with (0x7B492C, a2).
void sub_59FD10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059fd10
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x7B0000;
    sd(ra, sp, 0x0);
    v0 = addiu(v0, 18728);  // &0x7B4928
    a1 = a2;
    lw(v1, v0, 8);  // 0x7B4930
    lw(a2, v0, 0);  // 0x7B4928
    v1 = addiu(v1, 1);
    lw(a0, v0, 4);  // 0x7B492C
    sw(v1, v0, 8);  // 0x7B4930
    if (a2 != 0) {
        // 0x0059fd3c
        charge(ctx, 2);
        jalr(ctx, 0x59FD3Cu, a2.u());
    }
    // 0x0059fd44 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x005A1868 sub_5A1868 -- 340 bytes; frame 0x20: s0 sp+0x10, ra sp+0x18
// Middleware timer setup: reads the "TMR_CH" / "TMR_CLK" options (sub_555898; clock default 576000), sets the clock
// (sub_5A1CE0), saves the chosen timer channel's mode register (dword_7CAC20 table) in 0x7B5070 and starts it;
// ref-counted at 0x7B5068.
void sub_5A1868(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005a1868
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x7D0000;
    sd(s0, sp, 0x10);
    s0 = a0;
    a1 = sp;
    sd(ra, sp, 0x18);
    a0 = addiu(v0, -21440);  // "TMR_CH"
    jal(ctx, 0x5A1880u, gen::fn_sub_555898_00555898);
    a0 = 0x7B0000;
    lw(a1, sp, 0x0);
    a0 = addiu(a0, 20584);  // &0x7B5068
    lw(v1, a0, 0);  // 0x7B5068
    if (v0 == 0) s0 = a1;
    v1 = addiu(v1, 1);
    sw(v1, a0, 0);  // 0x7B5068
    lw(v0, a0, 0);  // 0x7B5068
    v0 = slti(v0, 2);
    v1 = 0x7B0000;
    if (v0 == 0) {
        // 0x005a18b4
        charge(ctx, 3);
        lw(v0, v1, 20588);
        cc = v0 == s0;  // the condition, before the delay slot changes it
        v0 = si(-1);
        if (cc) {
            goto L_005a19ac;
        }
        // 0x005a18c0
        charge(ctx, 2);
        goto L_005a18cc;
    }
    // 0x005a18c8
    charge(ctx, 1);
    v0 = si(-1);
L_005a18cc:
    charge(ctx, 2);
    sw(s0, v1, 20588);
    if (s0 != v0) {
        // 0x005a18e8
        charge(ctx, 20);
        a0 = 0x7D0000;
        a1 = sp;
        a0 = addiu(a0, -21432);  // "TMR_CLK"
        jal(ctx, 0x5A18F0u, gen::fn_sub_555898_00555898);
        a0 = 0x80000;
        a0 = a0 | 0xCA00;
        lwu(v1, sp, 0x0);
        v0 = v0 ^ 0x0;
        if (v0 == 0) a0 = v1;
        jal(ctx, 0x5A1908u, gen::fn_sub_5A1CE0_005a1ce0);
        a0 = 0x7B0000;
        a1 = sll(s0, 2);
        a3 = 130;
        a2 = 0x7D0000;
        a2 = addu(a2, a1);
        lw(a2, a2, -21472);
        lw(v0, a2, 0);
        v1 = v0 & 0xC7;
        sw(v0, a0, 20592);  // 0x7B5070
        if (v1 == a3) {
            // 0x005a1958
            charge(ctx, 2);
            v1 = 0x7D0000;
            v0 = addiu(v1, -21456);  // &0x7CAC30
        } else {
            // 0x005a1938
            charge(ctx, 8);
            v0 = 0x7D0000;
            v0 = addu(v0, a1);
            lw(v0, v0, -21456);
            v1 = 0x7D0000;
            sw(zero, v0, 0);
            sw(a3, a2, 0);
            v0 = addiu(v1, -21456);  // &0x7CAC30
        }
        // 0x005a1960
        charge(ctx, 19);
        a0 = 0x9B0000;
        v0 = addu(a1, v0);
        a1 = 0x9B0000;
        lw(v1, v0, 0);
        a0 = addiu(a0, -13320);  // &0x9ACBF8
        a1 = addiu(a1, -13304);  // &0x9ACC08
        a3 = 0x9B0000;
        lw(v0, v1, 0);
        a2 = 0x9B0000;
        a3 = addiu(a3, -13288);  // &0x9ACC18
        a2 = addiu(a2, -13284);  // &0x9ACC1C
        sh(v0, a0, 8);  // 0x9ACC00
        sd(zero, a0, 0);  // 0x9ACBF8
        ld(v0, a0, 0);  // 0x9ACBF8
        sd(v0, a1, 0);  // 0x9ACC08
        ld(v1, a0, 8);  // 0x9ACC00
        sd(v1, a1, 8);  // 0x9ACC10
        sw(a0, a3, 0);  // 0x9ACC18
        sw(zero, a2, 0);  // 0x9ACC1C
    L_005a19ac:
        charge(ctx, 1);
        ld(s0, sp, 0x10);
    } else {
        // 0x005a18d4
        charge(ctx, 4);
        a0 = 1;
        jal(ctx, 0x5A18D4u, gen::fn_sub_5A1CE0_005a1ce0);
        ld(s0, sp, 0x10);
    }
    // 0x005a19b0 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x005A19C0 sub_5A19C0 -- 112 bytes; leaf frame (no stack)
// Middleware timer release: decrements the ref count at 0x7B5068 and, at zero, restores the saved channel mode
// (0x7B5070 ^ 0xC00) unless it is already stopped; clamps the count at 0.
void sub_5A19C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x005a19c0
    enter(ctx, 9);  // entry check point + this block's cycles
    v1 = 0x7B0000;
    a0 = addiu(v1, 20584);  // &0x7B5068
    lw(v0, a0, 0);  // 0x7B5068
    a3 = a0;
    v0 = addiu(v0, -1);
    sw(v0, a0, 0);  // 0x7B5068
    lw(v1, a0, 0);  // 0x7B5068
    v0 = 0x7B0000;
    if (v1 == 0) {
        // 0x005a19e4
        charge(ctx, 4);
        v1 = si(-1);
        lw(a1, v0, 20588);
        v0 = 0x7B0000;
        if (a1 != v1) {
            // 0x005a19f4
            charge(ctx, 6);
            a0 = 130;
            lw(v1, v0, 20592);
            a2 = v1 ^ 0xC00;
            v1 = v1 & 0xC7;
            v0 = sll(a1, 2);
            if (v1 != a0) {
                // 0x005a1a0c
                charge(ctx, 4);
                v1 = 0x7D0000;
                v1 = addu(v1, v0);
                lw(v1, v1, -21472);
                sw(a2, v1, 0);
            }
        }
    }
    // 0x005a1a1c
    charge(ctx, 3);
    lw(v0, a3, 0);
    if (i64(v0) < 0) {
        sw(zero, a3, 0);
    }
    // 0x005a1a28
    charge(ctx, 2);
}

}  // namespace p3fes::game

// The recompiled program's entry points fn_<name>_<addr8> are generated from game/replaced.txt (game/forwarders.cmake).
