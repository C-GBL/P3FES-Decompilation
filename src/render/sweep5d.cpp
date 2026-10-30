// Slice sweep5d (Phase 5, wave 5): 138 still-recompiled functions picked by first-call reach across the whole binary --
// field / calendar / event glue (0x1A....), shuffle-time and card-graphics resources, the battle table and voice-bank
// loaders, battle table callbacks and camera shots, DatUnitGenus create / destroy, model clone / morph helpers, the
// resource-manager entry setters, the facility shop menu (fclShopMisc.c), RenderWare-side helpers (camera / clip
// setup of kwlnInitRenderer, MatFX slots, raster copy, free-list pages, stream reads), libmpeg's flush, the sceMc2
// async queue calls, newlib's _fwalk / __srefill, and CRI (ADX / Sofdec / DVCI) handle helpers.
// Every body is p3fes_handgen's faithful translation (game/include/p3fes/game/hg_cpu.h): register for register and
// block for block as the recompiled body (frame, spills, $ra links, cycle charges, check points). The comment above
// each body gives its role, read from the instructions (the pseudocode export was only a hint); names stay
// symbols/'s. Pair tests: tests/game/test_sweep5d.cpp.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/sweep5d.h"

namespace p3fes::recomp_gen {
void fn_DIntr_0050d3a0(p3fes::EEContext&);
void fn_EIntr_0050d3f0(p3fes::EEContext&);
void fn_H_Cdvd_Destroy_00100ec0(p3fes::EEContext&);
void fn_H_Cdvd_LoadAfsFile_001024a0(p3fes::EEContext&);
void fn_H_Cdvd_ReadSync_001023a0(p3fes::EEContext&);
void fn_H_Cdvd_Request_00100d80(p3fes::EEContext&);
void fn_SRD_ExecServer_00558500(p3fes::EEContext&);
void fn_SyncDCache_00503a58(p3fes::EEContext&);
void fn_SyncDma_0051ad10(p3fes::EEContext&);
void fn___sinit_0051fa20(p3fes::EEContext&);
void fn__dispRefImageField_005016c8(p3fes::EEContext&);
void fn__dispRefImage_00501408(p3fes::EEContext&);
void fn__fork_r_005205d8(p3fes::EEContext&);
void fn__free_r_0051fbb0(p3fes::EEContext&);
void fn__fwalk_00520410(p3fes::EEContext&);
void fn__sceCreateSema_00503160(p3fes::EEContext&);
void fn__sceDeleteSema_00503170(p3fes::EEContext&);
void fn__sceFsSigSema_00508078(p3fes::EEContext&);
void fn__sceFsWaitS_00508048(p3fes::EEContext&);
void fn__sceMcCoreChangeSocketTypeDbc2Mc_0051c2e8(p3fes::EEContext&);
void fn__sceMpegError_00502668(p3fes::EEContext&);
void fn__sceSignalSema_00503180(p3fes::EEContext&);
void fn__sceWaitSema_005031a0(p3fes::EEContext&);
void fn_atomicGetWorldBoundingSphere_004912b0(p3fes::EEContext&);
void fn_btlCountActiveUnits_002d4e10(p3fes::EEContext&);
void fn_btlTargetGetSideMask_002d1600(p3fes::EEContext&);
void fn_clndIsDateInRange_0017e480(p3fes::EEContext&);
void fn_clndIsHolidayOrSunday_0017dcf0(p3fes::EEContext&);
void fn_datCalcChkBadStatus_00300580(p3fes::EEContext&);
void fn_datGetEquipmentIdx_0016cb80(p3fes::EEContext&);
void fn_datGetFlag_0016f190(p3fes::EEContext&);
void fn_datGetUnit_0016cd60(p3fes::EEContext&);
void fn_datSetFlag_0016f1f0(p3fes::EEContext&);
void fn_datUnitInit_002ff890(p3fes::EEContext&);
void fn_dvCiCdSearchFile_00559dd8(p3fes::EEContext&);
void fn_dvCiExecServer_00559f48(p3fes::EEContext&);
void fn_dvCiGetStat_0055a720(p3fes::EEContext&);
void fn_dvci_conv_fname_0055a9b0(p3fes::EEContext&);
void fn_fflush_0051f728(p3fes::EEContext&);
void fn_geometryLock_00493370(p3fes::EEContext&);
void fn_get_iob_00507bc8(p3fes::EEContext&);
void fn_itfMesMngGetMessageCount_003a51a0(p3fes::EEContext&);
void fn_kwlnTaskAddChild_00195550(p3fes::EEContext&);
void fn_kwlnTaskCreateWithAutoPriority_00194b80(p3fes::EEContext&);
void fn_kwlnTaskDestroyWithHierarchy_00195020(p3fes::EEContext&);
void fn_kwlnTaskInitEx_00194e10(p3fes::EEContext&);
void fn_matfxSetAtomicPipeline_00469d60(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_nmCmdListDestroy_003c5a20(p3fes::EEContext&);
void fn_nmCmdListDraw_003c6380(p3fes::EEContext&);
void fn_nmCmdListSetDrawFunc_003c5e20(p3fes::EEContext&);
void fn_nmCmdListSetPosition_003c6d40(p3fes::EEContext&);
void fn_nmCmdListSetRowDrawFunc_003c5ee0(p3fes::EEContext&);
void fn_nmCmdListSetRowRemoveFunc_003c5f40(p3fes::EEContext&);
void fn_nmCmdListSetUpdateFunc_003c5e80(p3fes::EEContext&);
void fn_nmCmdListStatus28_003c6e10(p3fes::EEContext&);
void fn_nmObjPayloadWord12_003c5460(p3fes::EEContext&);
void fn_printf_005225a8(p3fes::EEContext&);
void fn_sceCdSync_00510148(p3fes::EEContext&);
void fn_sceDbcGetConnection_0051cad0(p3fes::EEContext&);
void fn_sceDbcSendData3_0051d308(p3fes::EEContext&);
void fn_sceFsInit_00508170(p3fes::EEContext&);
void fn_sceFsSifCallRpc_00507ad8(p3fes::EEContext&);
void fn_scePadSetReqState_00511b08(p3fes::EEContext&);
void fn_sceSifCallRpc_00507230(p3fes::EEContext&);
void fn_sprintf_00523ac8(p3fes::EEContext&);
void fn_strcpy_00524270(p3fes::EEContext&);
void fn_strlen_00524388(p3fes::EEContext&);
void fn_strncat_005244c0(p3fes::EEContext&);
void fn_strstr_00524a50(p3fes::EEContext&);
void fn_sub_1052B0_001052b0(p3fes::EEContext&);
void fn_sub_109180_00109180(p3fes::EEContext&);
void fn_sub_109AE0_00109ae0(p3fes::EEContext&);
void fn_sub_10A0E0_0010a0e0(p3fes::EEContext&);
void fn_sub_10A4E0_0010a4e0(p3fes::EEContext&);
void fn_sub_16DBA0_0016dba0(p3fes::EEContext&);
void fn_sub_16DD50_0016dd50(p3fes::EEContext&);
void fn_sub_16E9B0_0016e9b0(p3fes::EEContext&);
void fn_sub_16F630_0016f630(p3fes::EEContext&);
void fn_sub_16F900_0016f900(p3fes::EEContext&);
void fn_sub_16FEA0_0016fea0(p3fes::EEContext&);
void fn_sub_170760_00170760(p3fes::EEContext&);
void fn_sub_170C00_00170c00(p3fes::EEContext&);
void fn_sub_171060_00171060(p3fes::EEContext&);
void fn_sub_171250_00171250(p3fes::EEContext&);
void fn_sub_1717C0_001717c0(p3fes::EEContext&);
void fn_sub_172160_00172160(p3fes::EEContext&);
void fn_sub_172660_00172660(p3fes::EEContext&);
void fn_sub_1749A0_001749a0(p3fes::EEContext&);
void fn_sub_174A90_00174a90(p3fes::EEContext&);
void fn_sub_174B40_00174b40(p3fes::EEContext&);
void fn_sub_174E20_00174e20(p3fes::EEContext&);
void fn_sub_1752B0_001752b0(p3fes::EEContext&);
void fn_sub_175410_00175410(p3fes::EEContext&);
void fn_sub_1756F0_001756f0(p3fes::EEContext&);
void fn_sub_176990_00176990(p3fes::EEContext&);
void fn_sub_176D10_00176d10(p3fes::EEContext&);
void fn_sub_17C610_0017c610(p3fes::EEContext&);
void fn_sub_17C8C0_0017c8c0(p3fes::EEContext&);
void fn_sub_17CF00_0017cf00(p3fes::EEContext&);
void fn_sub_17D800_0017d800(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_1A4330_001a4330(p3fes::EEContext&);
void fn_sub_1A7170_001a7170(p3fes::EEContext&);
void fn_sub_1A7570_001a7570(p3fes::EEContext&);
void fn_sub_21AC90_0021ac90(p3fes::EEContext&);
void fn_sub_21AD40_0021ad40(p3fes::EEContext&);
void fn_sub_21AE30_0021ae30(p3fes::EEContext&);
void fn_sub_21AF30_0021af30(p3fes::EEContext&);
void fn_sub_21B080_0021b080(p3fes::EEContext&);
void fn_sub_21B2D0_0021b2d0(p3fes::EEContext&);
void fn_sub_21D8E0_0021d8e0(p3fes::EEContext&);
void fn_sub_21D950_0021d950(p3fes::EEContext&);
void fn_sub_21EA00_0021ea00(p3fes::EEContext&);
void fn_sub_21EAC0_0021eac0(p3fes::EEContext&);
void fn_sub_23C3A0_0023c3a0(p3fes::EEContext&);
void fn_sub_23D2A0_0023d2a0(p3fes::EEContext&);
void fn_sub_23D650_0023d650(p3fes::EEContext&);
void fn_sub_242840_00242840(p3fes::EEContext&);
void fn_sub_250A30_00250a30(p3fes::EEContext&);
void fn_sub_256F20_00256f20(p3fes::EEContext&);
void fn_sub_257D00_00257d00(p3fes::EEContext&);
void fn_sub_25D8A0_0025d8a0(p3fes::EEContext&);
void fn_sub_2A2290_002a2290(p3fes::EEContext&);
void fn_sub_2A3110_002a3110(p3fes::EEContext&);
void fn_sub_2A3E80_002a3e80(p3fes::EEContext&);
void fn_sub_2A4470_002a4470(p3fes::EEContext&);
void fn_sub_2A44F0_002a44f0(p3fes::EEContext&);
void fn_sub_2A4690_002a4690(p3fes::EEContext&);
void fn_sub_2AF960_002af960(p3fes::EEContext&);
void fn_sub_2B6070_002b6070(p3fes::EEContext&);
void fn_sub_2B8F90_002b8f90(p3fes::EEContext&);
void fn_sub_2B9030_002b9030(p3fes::EEContext&);
void fn_sub_2B96E0_002b96e0(p3fes::EEContext&);
void fn_sub_2D1DE0_002d1de0(p3fes::EEContext&);
void fn_sub_2D1F30_002d1f30(p3fes::EEContext&);
void fn_sub_2D1FD0_002d1fd0(p3fes::EEContext&);
void fn_sub_2D5E10_002d5e10(p3fes::EEContext&);
void fn_sub_2DDC10_002ddc10(p3fes::EEContext&);
void fn_sub_2E6130_002e6130(p3fes::EEContext&);
void fn_sub_2E6A20_002e6a20(p3fes::EEContext&);
void fn_sub_308860_00308860(p3fes::EEContext&);
void fn_sub_30C3A0_0030c3a0(p3fes::EEContext&);
void fn_sub_3143C0_003143c0(p3fes::EEContext&);
void fn_sub_3182D0_003182d0(p3fes::EEContext&);
void fn_sub_3185B0_003185b0(p3fes::EEContext&);
void fn_sub_31D700_0031d700(p3fes::EEContext&);
void fn_sub_31DED0_0031ded0(p3fes::EEContext&);
void fn_sub_31E0B0_0031e0b0(p3fes::EEContext&);
void fn_sub_31E310_0031e310(p3fes::EEContext&);
void fn_sub_31EE80_0031ee80(p3fes::EEContext&);
void fn_sub_323C20_00323c20(p3fes::EEContext&);
void fn_sub_34FCD0_0034fcd0(p3fes::EEContext&);
void fn_sub_34FDF0_0034fdf0(p3fes::EEContext&);
void fn_sub_34FF70_0034ff70(p3fes::EEContext&);
void fn_sub_3A5570_003a5570(p3fes::EEContext&);
void fn_sub_3A56F0_003a56f0(p3fes::EEContext&);
void fn_sub_3A5EA0_003a5ea0(p3fes::EEContext&);
void fn_sub_3B2CB0_003b2cb0(p3fes::EEContext&);
void fn_sub_3B32D0_003b32d0(p3fes::EEContext&);
void fn_sub_3B50D0_003b50d0(p3fes::EEContext&);
void fn_sub_3B5AB0_003b5ab0(p3fes::EEContext&);
void fn_sub_3B5D10_003b5d10(p3fes::EEContext&);
void fn_sub_3B5D50_003b5d50(p3fes::EEContext&);
void fn_sub_3B8540_003b8540(p3fes::EEContext&);
void fn_sub_3B88C0_003b88c0(p3fes::EEContext&);
void fn_sub_3B8CE0_003b8ce0(p3fes::EEContext&);
void fn_sub_3BE1C0_003be1c0(p3fes::EEContext&);
void fn_sub_3BE2A0_003be2a0(p3fes::EEContext&);
void fn_sub_3C58F0_003c58f0(p3fes::EEContext&);
void fn_sub_3C6EE0_003c6ee0(p3fes::EEContext&);
void fn_sub_3C77A0_003c77a0(p3fes::EEContext&);
void fn_sub_3C7DD0_003c7dd0(p3fes::EEContext&);
void fn_sub_3C8F20_003c8f20(p3fes::EEContext&);
void fn_sub_3CA780_003ca780(p3fes::EEContext&);
void fn_sub_3CF960_003cf960(p3fes::EEContext&);
void fn_sub_3D9820_003d9820(p3fes::EEContext&);
void fn_sub_3DFEB0_003dfeb0(p3fes::EEContext&);
void fn_sub_3DFF00_003dff00(p3fes::EEContext&);
void fn_sub_3DFF80_003dff80(p3fes::EEContext&);
void fn_sub_3E0680_003e0680(p3fes::EEContext&);
void fn_sub_3F4A90_003f4a90(p3fes::EEContext&);
void fn_sub_3F67E0_003f67e0(p3fes::EEContext&);
void fn_sub_3F6F20_003f6f20(p3fes::EEContext&);
void fn_sub_3F7390_003f7390(p3fes::EEContext&);
void fn_sub_3F7890_003f7890(p3fes::EEContext&);
void fn_sub_3F7A80_003f7a80(p3fes::EEContext&);
void fn_sub_3F7C60_003f7c60(p3fes::EEContext&);
void fn_sub_402510_00402510(p3fes::EEContext&);
void fn_sub_405F70_00405f70(p3fes::EEContext&);
void fn_sub_4064E0_004064e0(p3fes::EEContext&);
void fn_sub_406AA0_00406aa0(p3fes::EEContext&);
void fn_sub_40C1E0_0040c1e0(p3fes::EEContext&);
void fn_sub_40C310_0040c310(p3fes::EEContext&);
void fn_sub_40E360_0040e360(p3fes::EEContext&);
void fn_sub_40E3C0_0040e3c0(p3fes::EEContext&);
void fn_sub_40E3F0_0040e3f0(p3fes::EEContext&);
void fn_sub_40EB50_0040eb50(p3fes::EEContext&);
void fn_sub_40EC20_0040ec20(p3fes::EEContext&);
void fn_sub_45F930_0045f930(p3fes::EEContext&);
void fn_sub_4606B0_004606b0(p3fes::EEContext&);
void fn_sub_460EC0_00460ec0(p3fes::EEContext&);
void fn_sub_464020_00464020(p3fes::EEContext&);
void fn_sub_466480_00466480(p3fes::EEContext&);
void fn_sub_469B50_00469b50(p3fes::EEContext&);
void fn_sub_488F30_00488f30(p3fes::EEContext&);
void fn_sub_48B910_0048b910(p3fes::EEContext&);
void fn_sub_4916D0_004916d0(p3fes::EEContext&);
void fn_sub_491CC0_00491cc0(p3fes::EEContext&);
void fn_sub_493230_00493230(p3fes::EEContext&);
void fn_sub_4933D0_004933d0(p3fes::EEContext&);
void fn_sub_494D50_00494d50(p3fes::EEContext&);
void fn_sub_4A9D80_004a9d80(p3fes::EEContext&);
void fn_sub_4AA540_004aa540(p3fes::EEContext&);
void fn_sub_4AAA60_004aaa60(p3fes::EEContext&);
void fn_sub_4AAD50_004aad50(p3fes::EEContext&);
void fn_sub_4AAE60_004aae60(p3fes::EEContext&);
void fn_sub_4B2F10_004b2f10(p3fes::EEContext&);
void fn_sub_4B3160_004b3160(p3fes::EEContext&);
void fn_sub_4B3900_004b3900(p3fes::EEContext&);
void fn_sub_4B3AC0_004b3ac0(p3fes::EEContext&);
void fn_sub_4B4090_004b4090(p3fes::EEContext&);
void fn_sub_4B4230_004b4230(p3fes::EEContext&);
void fn_sub_4B4860_004b4860(p3fes::EEContext&);
void fn_sub_4B4BA0_004b4ba0(p3fes::EEContext&);
void fn_sub_4B4CC0_004b4cc0(p3fes::EEContext&);
void fn_sub_4B6EB0_004b6eb0(p3fes::EEContext&);
void fn_sub_4BE1E0_004be1e0(p3fes::EEContext&);
void fn_sub_4BFEA0_004bfea0(p3fes::EEContext&);
void fn_sub_4C00F0_004c00f0(p3fes::EEContext&);
void fn_sub_4C18B0_004c18b0(p3fes::EEContext&);
void fn_sub_4C1910_004c1910(p3fes::EEContext&);
void fn_sub_4C1C50_004c1c50(p3fes::EEContext&);
void fn_sub_4C1D10_004c1d10(p3fes::EEContext&);
void fn_sub_4C33D0_004c33d0(p3fes::EEContext&);
void fn_sub_4C35D0_004c35d0(p3fes::EEContext&);
void fn_sub_4C69F0_004c69f0(p3fes::EEContext&);
void fn_sub_4C6B20_004c6b20(p3fes::EEContext&);
void fn_sub_4C6BE0_004c6be0(p3fes::EEContext&);
void fn_sub_4C6C60_004c6c60(p3fes::EEContext&);
void fn_sub_4CB6E0_004cb6e0(p3fes::EEContext&);
void fn_sub_4CD260_004cd260(p3fes::EEContext&);
void fn_sub_4CDE90_004cde90(p3fes::EEContext&);
void fn_sub_5067F8_005067f8(p3fes::EEContext&);
void fn_sub_50D998_0050d998(p3fes::EEContext&);
void fn_sub_5397E8_005397e8(p3fes::EEContext&);
void fn_sub_539818_00539818(p3fes::EEContext&);
void fn_sub_539830_00539830(p3fes::EEContext&);
void fn_sub_539848_00539848(p3fes::EEContext&);
void fn_sub_539850_00539850(p3fes::EEContext&);
void fn_sub_53ADA8_0053ada8(p3fes::EEContext&);
void fn_sub_53AED0_0053aed0(p3fes::EEContext&);
void fn_sub_53B158_0053b158(p3fes::EEContext&);
void fn_sub_53C268_0053c268(p3fes::EEContext&);
void fn_sub_5416E8_005416e8(p3fes::EEContext&);
void fn_sub_541760_00541760(p3fes::EEContext&);
void fn_sub_5419D8_005419d8(p3fes::EEContext&);
void fn_sub_541DA0_00541da0(p3fes::EEContext&);
void fn_sub_545CC8_00545cc8(p3fes::EEContext&);
void fn_sub_546058_00546058(p3fes::EEContext&);
void fn_sub_5466B8_005466b8(p3fes::EEContext&);
void fn_sub_547F78_00547f78(p3fes::EEContext&);
void fn_sub_548250_00548250(p3fes::EEContext&);
void fn_sub_548768_00548768(p3fes::EEContext&);
void fn_sub_549000_00549000(p3fes::EEContext&);
void fn_sub_549568_00549568(p3fes::EEContext&);
void fn_sub_552630_00552630(p3fes::EEContext&);
void fn_sub_5530D0_005530d0(p3fes::EEContext&);
void fn_sub_5542E8_005542e8(p3fes::EEContext&);
void fn_sub_5546F0_005546f0(p3fes::EEContext&);
void fn_sub_554708_00554708(p3fes::EEContext&);
void fn_sub_5548D0_005548d0(p3fes::EEContext&);
void fn_sub_557F80_00557f80(p3fes::EEContext&);
void fn_sub_558988_00558988(p3fes::EEContext&);
void fn_sub_559DA8_00559da8(p3fes::EEContext&);
void fn_sub_559FD8_00559fd8(p3fes::EEContext&);
void fn_sub_55DBE8_0055dbe8(p3fes::EEContext&);
void fn_sub_55DD08_0055dd08(p3fes::EEContext&);
void fn_sub_5618F0_005618f0(p3fes::EEContext&);
void fn_sub_562308_00562308(p3fes::EEContext&);
void fn_sub_562F10_00562f10(p3fes::EEContext&);
void fn_sub_563E68_00563e68(p3fes::EEContext&);
void fn_sub_564EF8_00564ef8(p3fes::EEContext&);
void fn_sub_565590_00565590(p3fes::EEContext&);
void fn_sub_583848_00583848(p3fes::EEContext&);
void fn_sub_588F48_00588f48(p3fes::EEContext&);
void fn_sub_589CF0_00589cf0(p3fes::EEContext&);
void fn_sub_589D10_00589d10(p3fes::EEContext&);
void fn_sub_58BE40_0058be40(p3fes::EEContext&);
void fn_sub_58C060_0058c060(p3fes::EEContext&);
void fn_sub_594B18_00594b18(p3fes::EEContext&);
void fn_sub_599240_00599240(p3fes::EEContext&);
void fn_sub_599408_00599408(p3fes::EEContext&);
void fn_sub_59CC30_0059cc30(p3fes::EEContext&);
void fn_sub_59FE60_0059fe60(p3fes::EEContext&);
void fn_tanf_0052e930(p3fes::EEContext&);
void fn_vsprintf_005288c8(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// 0x001050E0 sub_1050E0 -- 296 bytes; frame 0xA0: ra sp+0x20, s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// Debug text line: allocates a 280-byte record through the allocator hook at 0x960184 (1, 280, 0x40000), vsprintf's the
// format ($a1 sp+0x68, va list on the stack) into record+16, stores the float position (a0 high word, $f12 at +272),
// the packed RGBA byte quad at +276..+279, and appends the record to the singly linked list headed at gp-20008
// (0x7CDEC8).
void sub_1050E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21};
    // 0x001050e0
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    sd(a0, sp, 0x38);
    mov_s(f21, f12);
    sw(a1, sp, 0x58);
    sw(a2, sp, 0x68);
    sd(a3, sp, 0x78);
    sd(t0, sp, 0x80);
    sd(t1, sp, 0x88);
    sd(t2, sp, 0x90);
    sd(t3, sp, 0x98);
    lwc1(f20, sp, 0x3C);
    a0 = 1;
    a1 = 280;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x105130u, v0.u());
    s0 = v0;
    v1 = 3;
    v0 = slti(v1, 8);
    if (v0 != 0) {
        // 0x00105158
        charge(ctx, 3);
        v0 = 8;
        v0 = subu(v0, v1);
        v1 = sll(v0, 3);
    } else {
        // 0x0010514c
        charge(ctx, 3);
        v1 = 0;
    }
    // 0x00105164
    charge(ctx, 22);
    v0 = addiu(sp, 0xA0);
    a2 = subu(v0, v1);
    a0 = addiu(s0, 16);
    lw(a1, sp, 0x68);
    jal(ctx, 0x105174u, gen::fn_vsprintf_005288c8);
    lwc1(f0, sp, 0x38);
    swc1(f0, s0, 4);
    swc1(f20, s0, 8);
    sw(zero, s0, 12);
    swc1(f21, s0, 272);
    lbu(a2, sp, 0x58);
    lbu(a1, sp, 0x59);
    lbu(a0, sp, 0x5A);
    lbu(v1, sp, 0x5B);
    sb(a2, s0, 276);
    sb(a1, s0, 277);
    sb(a0, s0, 278);
    sb(v1, s0, 279);
    lw(a0, gp, -20008);  // 0x7CDEC8
    if (a0 != 0) {
        for (;;) {
            // 0x001051c8
            charge(ctx, 3);
            lw(v1, a0, 0);
            if (v1 == 0) {
                break;
            }
            // 0x001051e0
            charge(ctx, 3);
            a0 = v1;
            backedge(ctx);
        }
        // 0x001051d4
        charge(ctx, 3);
        sw(s0, a0, 0);
    } else {
        // 0x001051bc
        charge(ctx, 3);
        sw(s0, gp, -20008);  // 0x7CDEC8
    }
    // 0x001051ec (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// 0x001A0D40 sub_1A0D40 -- 60 bytes; frame 0x10: ra sp+0x0
// Returns the payload (+272) of the resource-manager entry of kind 5 (sub_3B5D50), or 0 when there is none.
void sub_1A0D40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a0d40
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 5;
    jal(ctx, 0x1A0D4Cu, gen::fn_sub_3B5D50_003b5d50);
    if (v0 == 0) {
        // 0x001a0d68
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x001a0d5c
        charge(ctx, 3);
        v0 = addiu(v0, 272);
    }
    // 0x001a0d6c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001A11D0 sub_1A11D0 -- 64 bytes; frame 0x10: ra sp+0x0
// True when the resource-manager entry of kind 20 (sub_3B5D50) exists and its +256 word equals 1; otherwise 0 / the
// existence flag.
void sub_1A11D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a11d0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 20;
    jal(ctx, 0x1A11DCu, gen::fn_sub_3B5D50_003b5d50);
    v1 = sltu(0, v0);
    if (v1 != 0) {
        // 0x001a11f0
        charge(ctx, 3);
        lw(v0, v0, 256);
        v0 = v0 ^ 0x1;
        v1 = sltiu(v0, 1);
    }
    // 0x001a11fc (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = v1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001A42F0 sub_1A42F0 -- 56 bytes; frame 0x10: ra sp+0x0
// Returns sub_1A4330()'s record + 524, or 0 when it gives none.
void sub_1A42F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a42f0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x1A42F8u, gen::fn_sub_1A4330_001a4330);
    if (v0 != 0) {
        // 0x001a4314
        charge(ctx, 1);
        v0 = addiu(v0, 524);
    } else {
        // 0x001a4308
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001a4318 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001A46F0 sub_1A46F0 -- 128 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Creates the "draw point" kwlnTask (priority group 2109, update sub_1A4660, destroy sub_1A46C0) under task $a0 with a
// 20-byte work block from the 0x960184 allocator hook; returns the task or 0.
void sub_1A46F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a46f0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 1;
    a1 = 20;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x1A4714u, v0.u());
    if (v0 != 0) {
        // 0x001a4730
        charge(ctx, 11);
        a0 = s0;
        a1 = 2109;
        a2 = 0x680000;
        a2 = addiu(a2, -29928);  // "draw point"
        a3 = 0x1A0000;
        a3 = addiu(a3, 18016);  // &sub_1A4660
        t0 = 0x1A0000;
        t0 = addiu(t0, 18112);  // &sub_1A46C0
        t1 = v0;
        jal(ctx, 0x1A4754u, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
    } else {
        // 0x001a4724
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001a475c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001A5CD0 sub_1A5CD0 -- 268 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Sets the calendar day-off flags: flag 2696 = 1 / 2697 = 0 on a holiday or Sunday or inside the 7/27-8/2, 8/10-8/15
// and 11/17-11/20 ranges, else 2696 = 0 / 2697 = 1.
void sub_1A5CD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a5cd0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = 0;
    jal(ctx, 0x1A5CE0u, gen::fn_clndIsHolidayOrSunday_0017dcf0);
    v1 = 1;
    if (v0 != v1) {
        // 0x001a5d74
        charge(ctx, 1);
        s0 = v1;
    } else {
        // 0x001a5cf4
        charge(ctx, 9);
        a0 = 7;
        a1 = 27;
        a2 = 8;
        a3 = 2;
        jal(ctx, 0x1A5D04u, gen::fn_clndIsDateInRange_0017e480);
        v1 = 1;
        if (v0 == v1) {
            // 0x001a5d18
            charge(ctx, 1);
            s0 = v1;
        }
        // 0x001a5d1c
        charge(ctx, 9);
        a0 = 8;
        a1 = 10;
        a2 = a0;
        a3 = 15;
        jal(ctx, 0x1A5D2Cu, gen::fn_clndIsDateInRange_0017e480);
        v1 = 1;
        if (v0 == v1) {
            // 0x001a5d40
            charge(ctx, 1);
            s0 = v1;
        }
        // 0x001a5d44
        charge(ctx, 9);
        a0 = 11;
        a1 = 17;
        a2 = a0;
        a3 = 20;
        jal(ctx, 0x1A5D54u, gen::fn_clndIsDateInRange_0017e480);
        v1 = 1;
        if (v0 == v1) {
            // 0x001a5d68
            charge(ctx, 3);
            s0 = v1;
        }
    }
    // 0x001a5d78
    charge(ctx, 3);
    a1 = 1;
    if (s0 != a1) {
        // 0x001a5da8
        charge(ctx, 8);
        a0 = 2696;
        a1 = 0;
        jal(ctx, 0x1A5DB0u, gen::fn_datSetFlag_0016f1f0);
        a0 = 2697;
        a1 = 1;
        jal(ctx, 0x1A5DC0u, gen::fn_datSetFlag_0016f1f0);
    } else {
        // 0x001a5d84
        charge(ctx, 9);
        a0 = 2696;
        jal(ctx, 0x1A5D88u, gen::fn_datSetFlag_0016f1f0);
        a0 = 2697;
        a1 = 0;
        jal(ctx, 0x1A5D98u, gen::fn_datSetFlag_0016f1f0);
    }
    // 0x001a5dc8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001A62C0 sub_1A62C0 -- 144 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Creates the "script shutdown(kosaka)" kwlnTask (group 10, update sub_1A6260, destroy sub_1A6290) with a 4-byte work
// block holding $a0; returns the task or 0.
void sub_1A62C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a62c0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    a0 = 1;
    a1 = 4;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x1A62E8u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x001a6308
        charge(ctx, 12);
        a0 = 0;
        a1 = 10;
        a2 = 0x680000;
        a2 = addiu(a2, -29760);  // "script shutdown(kosaka)"
        a3 = 0x1A0000;
        a3 = addiu(a3, 25184);  // &sub_1A6260
        t0 = 0x1A0000;
        t0 = addiu(t0, 25232);  // &sub_1A6290
        t1 = s0;
        jal(ctx, 0x1A632Cu, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
        sw(s1, s0, 0);
    } else {
        // 0x001a62fc
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001a6338 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001A7020 sub_1A7020 -- 12 bytes; leaf frame (no stack)
// Constant stub: returns 0.
void sub_1A7020(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x001a7020
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x001A7060 sub_1A7060 -- 64 bytes; frame 0x10: ra sp+0x0
// Creates the "kill metrics" kwlnTask (group 10, update sub_1A7030, no destroy, no work block).
void sub_1A7060(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a7060
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0;
    a1 = 10;
    a2 = 0x680000;
    a2 = addiu(a2, -29720);  // "kill metrics"
    a3 = 0x1A0000;
    a3 = addiu(a3, 28720);  // &sub_1A7030
    t0 = 0;
    t1 = 0;
    jal(ctx, 0x1A7088u, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001A92D0 sub_1A92D0 -- 92 bytes; frame 0x10: ra sp+0x0
// Forwards to sub_34FDF0($a2) with the object of record $a0+60: its +20 word for an index $a1 < 0, else its slot +36 +
// 4 * $a1 when set (nothing otherwise).
void sub_1A92D0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a92d0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 60);
    if (i64(a1) < 0) {
        // 0x001a930c
        charge(ctx, 4);
        lw(a0, a0, 20);
        a1 = a2;
        jal(ctx, 0x1A9314u, gen::fn_sub_34FDF0_0034fdf0);
    } else {
        // 0x001a92e4
        charge(ctx, 5);
        v1 = sll(a1, 2);
        v1 = addu(v1, a0);
        lw(a0, v1, 36);
        if (a0 != 0) {
            // 0x001a92f8
            charge(ctx, 5);
            a1 = a2;
            jal(ctx, 0x1A92FCu, gen::fn_sub_34FDF0_0034fdf0);
        }
    }
    // 0x001a931c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0020E2C0 sub_20E2C0 -- 184 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Shuffle ground resource (sfl_res.c): asserts the work record of gp-table slot 22 exists, is not busy and not loaded,
// then queues "battle/shuffle/sfl_ground.bin" through H_Cdvd_Request into +100 and sets the loading bit.
void sub_20E2C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0020e2c0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, -18944);  // 0x7CE2F0
    if (v0 == 0) {
        // 0x0020e2d8
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7912);  // "sfl_res.c"
        a1 = 101;
        jal(ctx, 0x20E2E4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0020e2ec
    charge(ctx, 6);
    lw(s0, gp, -18944);  // 0x7CE2F0
    lw(v0, s0, 4);
    v0 = nor(v0, 0);
    v0 = v0 & 0x1;
    if (v0 == 0) {
        // 0x0020e304
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7912);  // "sfl_res.c"
        a1 = 394;
        jal(ctx, 0x20E310u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0020e318
    charge(ctx, 5);
    lw(v0, s0, 0);
    v0 = nor(v0, 0);
    v0 = v0 & 0x2;
    if (v0 == 0) {
        // 0x0020e32c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7912);  // "sfl_res.c"
        a1 = 395;
        jal(ctx, 0x20E338u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0020e340
    charge(ctx, 14);
    a0 = 0x690000;
    a0 = addiu(a0, -7856);  // "battle/shuffle/sfl_ground.bin"
    a1 = 0;
    jal(ctx, 0x20E34Cu, gen::fn_H_Cdvd_Request_00100d80);
    sw(v0, s0, 100);
    lw(v1, s0, 0);
    v1 = v1 | 0x2;
    sw(v1, s0, 0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0021A670 sub_21A670 -- 228 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Card-graphics release (gc_res.c): finds the entry for ($a0, $a1) with sub_21AD40, drops its reference count (+16); at
// zero frees its texture (+12, sub_4CDE90) and clears the loaded / used bits.
void sub_21A670(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0021a670
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lw(v0, gp, -18932);  // 0x7CE2FC
    if (v0 == 0) {
        // 0x0021a694
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7624);  // "gc_res.c"
        a1 = 124;
        jal(ctx, 0x21A6A0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0021a6a8
    charge(ctx, 8);
    a0 = s1;
    a1 = s0;
    jal(ctx, 0x21A6B0u, gen::fn_sub_21AD40_0021ad40);
    s0 = v0;
    lw(v1, v0, 16);
    if (v1 == 0) {
        // 0x0021a6c8
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7624);  // "gc_res.c"
        a1 = 375;
        jal(ctx, 0x21A6D4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0021a6dc
    charge(ctx, 5);
    lw(v1, s0, 16);
    v1 = addiu(v1, -1);
    sw(v1, s0, 16);
    if (v1 == 0) {
        // 0x0021a6f0
        charge(ctx, 4);
        lw(v0, s0, 0);
        v0 = v0 & 0x2;
        if (v0 == 0) {
            // 0x0021a700
            charge(ctx, 5);
            a0 = 0x690000;
            a0 = addiu(a0, -7624);  // "gc_res.c"
            a1 = 384;
            jal(ctx, 0x21A70Cu, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x0021a714
        charge(ctx, 10);
        lw(a0, s0, 12);
        jal(ctx, 0x21A718u, gen::fn_sub_4CDE90_004cde90);
        lw(a0, s0, 0);
        v1 = si(-3);
        a0 = a0 & v1;
        sw(a0, s0, 0);
        v1 = si(-2);
        v1 = a0 & v1;
        sw(v1, s0, 0);
    }
    // 0x0021a73c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0021A760 sub_21A760 -- 212 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Card-graphics release by id (gc_res.c): finds the entry with sub_21B080, drops its reference count (+12); at zero
// frees its texture (+8, sub_4CDE90) and clears the loaded / used bits.
void sub_21A760(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0021a760
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, gp, -18932);  // 0x7CE2FC
    if (v0 == 0) {
        // 0x0021a77c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7624);  // "gc_res.c"
        a1 = 124;
        jal(ctx, 0x21A788u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0021a790
    charge(ctx, 7);
    a0 = s0;
    jal(ctx, 0x21A794u, gen::fn_sub_21B080_0021b080);
    s0 = v0;
    lw(v1, v0, 12);
    if (v1 == 0) {
        // 0x0021a7ac
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7624);  // "gc_res.c"
        a1 = 398;
        jal(ctx, 0x21A7B8u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0021a7c0
    charge(ctx, 5);
    lw(v1, s0, 12);
    v1 = addiu(v1, -1);
    sw(v1, s0, 12);
    if (v1 == 0) {
        // 0x0021a7d4
        charge(ctx, 4);
        lw(v0, s0, 0);
        v0 = v0 & 0x2;
        if (v0 == 0) {
            // 0x0021a7e4
            charge(ctx, 5);
            a0 = 0x690000;
            a0 = addiu(a0, -7624);  // "gc_res.c"
            a1 = 407;
            jal(ctx, 0x21A7F0u, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x0021a7f8
        charge(ctx, 10);
        lw(a0, s0, 8);
        jal(ctx, 0x21A7FCu, gen::fn_sub_4CDE90_004cde90);
        lw(a0, s0, 0);
        v1 = si(-3);
        a0 = a0 & v1;
        sw(a0, s0, 0);
        v1 = si(-2);
        v1 = a0 & v1;
        sw(v1, s0, 0);
    }
    // 0x0021a820 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0021A920 sub_21A920 -- 596 bytes; frame 0x170: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Card-graphics request (gc_res.c): reuses an entry for (suit $a0, number $a1) when present, else fills a free 20-byte
// entry and a free load slot and requests "card/sarcana/<suit>_c<NN>.tmx" (or _c0<p/n/q/k> for 11..14) through
// H_Cdvd_Request.
void sub_21A920(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0021a920
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x170);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s3 = a1;
    lw(v0, gp, -18932);  // 0x7CE2FC
    if (v0 == 0) {
        // 0x0021a950
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7624);  // "gc_res.c"
        a1 = 124;
        jal(ctx, 0x21A95Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0021a964
    charge(ctx, 7);
    lw(s0, gp, -18932);  // 0x7CE2FC
    a0 = s4;
    a1 = s3;
    jal(ctx, 0x21A970u, gen::fn_sub_21AC90_0021ac90);
    if (v0 == 0) {
        // 0x0021a998
        charge(ctx, 24);
        jal(ctx, 0x21A998u, gen::fn_sub_21AF30_0021af30);
        s1 = v0;
        v0 = sll(s1, 2);
        v0 = addu(v0, s1);
        v0 = sll(v0, 2);
        v1 = addu(s0, v0);
        s0 = addiu(v1, 76);
        sw(s4, v1, 80);
        sw(s3, v1, 84);
        sw(zero, v1, 88);
        v0 = 1;
        sw(v0, v1, 92);
        lw(v0, v1, 76);
        v0 = v0 | 0x1;
        sw(v0, v1, 76);
        jal(ctx, 0x21A9D8u, gen::fn_sub_21B2D0_0021b2d0);
        s3 = v0;
        sw(zero, v0, 272);
        sw(s1, v0, 276);
        v0 = 3;
        if (s4 == v0) {
            // 0x0021aa68
            charge(ctx, 4);
            a0 = addiu(sp, 0x160);
            a1 = addiu(gp, -26800);  // "cup"
            jal(ctx, 0x21AA70u, gen::fn_strcpy_00524270);
        } else {
            // 0x0021a9f8
            charge(ctx, 3);
            v0 = 2;
            if (s4 == v0) {
                // 0x0021aa50
                charge(ctx, 6);
                a0 = addiu(sp, 0x160);
                a1 = addiu(gp, -26808);  // "wand"
                jal(ctx, 0x21AA58u, gen::fn_strcpy_00524270);
            } else {
                // 0x0021aa04
                charge(ctx, 3);
                v0 = 1;
                if (s4 == v0) {
                    // 0x0021aa38
                    charge(ctx, 6);
                    a0 = addiu(sp, 0x160);
                    a1 = addiu(gp, -26816);  // "coin"
                    jal(ctx, 0x21AA40u, gen::fn_strcpy_00524270);
                } else {
                    // 0x0021aa10
                    charge(ctx, 2);
                    if (s4 == 0) {
                        // 0x0021aa20
                        charge(ctx, 6);
                        a0 = addiu(sp, 0x160);
                        a1 = addiu(gp, -26824);  // "sord"
                        jal(ctx, 0x21AA28u, gen::fn_strcpy_00524270);
                    } else {
                        // 0x0021aa18
                        charge(ctx, 2);
                    }
                }
            }
        }
        // 0x0021aa78
        charge(ctx, 4);
        lw(a3, s0, 8);
        at = slti(a3, 11);
        if (at == 0) {
            // 0x0021aaa8
            charge(ctx, 3);
            v0 = 14;
            if (a3 == v0) {
                // 0x0021ab04
                charge(ctx, 1);
                s2 = 107;
            } else {
                // 0x0021aab4
                charge(ctx, 3);
                v0 = 13;
                if (a3 == v0) {
                    // 0x0021aaf8
                    charge(ctx, 3);
                    s2 = 113;
                } else {
                    // 0x0021aac0
                    charge(ctx, 3);
                    v0 = 12;
                    if (a3 == v0) {
                        // 0x0021aaec
                        charge(ctx, 3);
                        s2 = 110;
                    } else {
                        // 0x0021aacc
                        charge(ctx, 3);
                        v0 = 11;
                        if (a3 == v0) {
                            // 0x0021aae0
                            charge(ctx, 3);
                            s2 = 112;
                        } else {
                            // 0x0021aad8
                            charge(ctx, 2);
                        }
                    }
                }
            }
            // 0x0021ab08
            charge(ctx, 8);
            a3 = dsll32(s2, 24);
            a3 = dsra32(a3, 24);
            a0 = addiu(sp, 0x60);
            a1 = 0x690000;
            a1 = addiu(a1, -7536);  // "card/sarcana/%s_c0%c.tmx"
            a2 = addiu(sp, 0x160);
            jal(ctx, 0x21AB20u, gen::fn_sprintf_00523ac8);
        } else {
            // 0x0021aa88
            charge(ctx, 8);
            a0 = addiu(sp, 0x60);
            a1 = 0x690000;
            a1 = addiu(a1, -7568);  // "card/sarcana/%s_c%02d.tmx"
            a2 = addiu(sp, 0x160);
            jal(ctx, 0x21AA98u, gen::fn_sprintf_00523ac8);
        }
        // 0x0021ab28
        charge(ctx, 10);
        a0 = addiu(sp, 0x60);
        a1 = 0;
        jal(ctx, 0x21AB30u, gen::fn_H_Cdvd_Request_00100d80);
        sw(v0, s3, 8);
        v1 = 1;
        sw(v1, s3, 4);
        lw(v1, s3, 0);
        v1 = v1 | 0x1;
        sw(v1, s3, 0);
    } else {
        // 0x0021a980
        charge(ctx, 6);
        a0 = s4;
        a1 = s3;
        jal(ctx, 0x21A988u, gen::fn_sub_21AE30_0021ae30);
    }
    // 0x0021ab50 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x170);
}

// 0x0023C280 sub_23C280 -- 208 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Shuffle ground setup (sfl_ground.c): resets the six 512-byte panels at +272, runs sub_23D2A0 / sub_23D650, and marks
// the record started (+12 = 1, +4 / +8 cleared, bit 0).
void sub_23C280(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0023c280
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, -18908);  // 0x7CE314
    if (v0 == 0) {
        // 0x0023c29c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6224);  // "sfl_ground.c"
        a1 = 135;
        jal(ctx, 0x23C2A8u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0023c2b0
    charge(ctx, 6);
    lw(s0, gp, -18908);  // 0x7CE314
    lw(v0, s0, 0);
    v0 = nor(v0, 0);
    v0 = v0 & 0x1;
    if (v0 == 0) {
        // 0x0023c2c8
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6224);  // "sfl_ground.c"
        a1 = 1266;
        jal(ctx, 0x23C2D4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0023c2dc
    charge(ctx, 3);
    s1 = 0;
    for (;;) {
        // 0x0023c300
        charge(ctx, 3);
        v0 = slti(s1, 6);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0023c2e8
        charge(ctx, 6);
        v0 = sll(s1, 9);
        v0 = addu(s0, v0);
        a0 = addiu(v0, 272);
        jal(ctx, 0x23C2F4u, gen::fn_sub_23C3A0_0023c3a0);
        s1 = addiu(s1, 1);
    }
    // 0x0023c30c
    charge(ctx, 17);
    jal(ctx, 0x23C30Cu, gen::fn_sub_23D2A0_0023d2a0);
    jal(ctx, 0x23C314u, gen::fn_sub_23D650_0023d650);
    v1 = 1;
    sw(v1, s0, 12);
    sw(zero, s0, 4);
    sw(zero, s0, 8);
    lw(v1, s0, 0);
    v1 = v1 | 0x1;
    sw(v1, s0, 0);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00242720 sub_242720 -- 284 bytes; frame 0x130: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Battle damage-number setup (bi_main.c): stores |$a1| clamped to 99999 at +3376 (bit 0x80 for a negative value),
// formats it to count its digits (+3380, 1..5), sets bit 0x200, and lays out the five digits with sub_242840.
void sub_242720(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00242720
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x130);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    if (i64(a1) < 0) {
        // 0x00242748
        charge(ctx, 4);
        s1 = subu(0, a1);
        lw(v0, s0, 0);
        v0 = v0 | 0x80;
        sw(v0, s0, 0);
    } else {
        // 0x0024273c
        charge(ctx, 3);
        s1 = a1;
    }
    // 0x00242758
    charge(ctx, 2);
    if (i64(s1) < 0) {
        // 0x00242760
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6032);  // "bi_main.c"
        a1 = 1576;
        jal(ctx, 0x24276Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00242774
    charge(ctx, 5);
    at = 0x10000;
    at = at | 0x86A0;
    at = slt(s1, at);
    if (at == 0) {
        // 0x00242794
        charge(ctx, 3);
        v0 = 0x10000;
        v0 = v0 | 0x869F;
        sw(v0, s0, 3376);
    } else {
        // 0x00242788
        charge(ctx, 3);
        sw(s1, s0, 3376);
    }
    // 0x002427a0
    charge(ctx, 11);
    a0 = addiu(sp, 0x30);
    a1 = addiu(gp, -26764);  // "%d"
    lw(a2, s0, 3376);
    jal(ctx, 0x2427ACu, gen::fn_sprintf_00523ac8);
    a0 = addiu(sp, 0x30);
    jal(ctx, 0x2427B8u, gen::fn_strlen_00524388);
    s1 = v0;
    if (i64(s1) <= 0) {
        // 0x002427cc
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6032);  // "bi_main.c"
        a1 = 1589;
        jal(ctx, 0x2427D8u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002427e0
    charge(ctx, 3);
    at = slti(s1, 6);
    if (at == 0) {
        // 0x002427ec
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6032);  // "bi_main.c"
        a1 = 1590;
        jal(ctx, 0x2427F8u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00242800
    charge(ctx, 15);
    sw(s1, s0, 3380);
    lw(v0, s0, 0);
    v0 = v0 | 0x200;
    sw(v0, s0, 0);
    a0 = addiu(s0, 2096);
    a1 = 5;
    lw(a2, s0, 3376);
    jal(ctx, 0x24281Cu, gen::fn_sub_242840_00242840);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x130);
}

// 0x00255B20 sub_255B20 -- 1036 bytes; frame 0x90: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Shuffle card start (sfl_card.c): derives the shuffle span / frame counts from the speed (+75696), shuffles the card
// order table (+75708) with 256-257 random swaps, finds the card whose index is the first empty slot, and starts its
// move (sub_256F20, sub_257D00, sub_250A30) with the shuffle sound.
void sub_255B20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x00255b20
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, -18844);  // 0x7CE354
    if (v0 == 0) {
        // 0x00255b48
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x255B54u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00255b5c
    charge(ctx, 59);
    lw(s1, gp, -18844);  // 0x7CE354
    a0 = 0x690000;
    a0 = addiu(a0, -5568);  // "speed:%d\n"
    v0 = 0x10000;
    v0 = addu(s1, v0);
    lw(a1, v0, 10160);
    jal(ctx, 0x255B74u, gen::fn_printf_005225a8);
    v0 = 0x10000;
    v0 = addu(s1, v0);
    lw(v0, v0, 10160);
    v0 = addiu(v0, -4);
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    v0 = 0x41600000;
    mtc1(v0, f0);
    div_s(f3, f1, f0);
    v0 = 0x41200000;
    mtc1(v0, f0);
    v0 = 0x40400000;
    mtc1(v0, f2);
    mtc1(zero, f1);
    adda_s(f1, f2);
    madd_s(f0, f0, f3);
    cvt_w_s(f0, f0);
    mfc1(v1, f0);
    v0 = 0x10000;
    v0 = addu(s1, v0);
    sw(v1, v0, 10376);
    v0 = 0x40A00000;
    mtc1(v0, f0);
    adda_s(f1, f0);
    madd_s(f0, f2, f3);
    cvt_w_s(f0, f0);
    mfc1(v1, f0);
    v0 = 0x10000;
    v0 = addu(s1, v0);
    sw(v1, v0, 10380);
    a0 = 0x690000;
    a0 = addiu(a0, -5552);  // "span :%d\n"
    v0 = 0x10000;
    v0 = addu(s1, v0);
    lw(a1, v0, 10376);
    jal(ctx, 0x255C18u, gen::fn_printf_005225a8);
    a0 = 0x690000;
    a0 = addiu(a0, -5536);  // "frame:%d\n"
    v0 = 0x10000;
    v0 = addu(s1, v0);
    lw(a1, v0, 10380);
    jal(ctx, 0x255C34u, gen::fn_printf_005225a8);
    a0 = 0;
    for (;;) {
        // 0x00255c60
        charge(ctx, 6);
        v0 = 0x10000;
        v0 = addu(s1, v0);
        lw(v0, v0, 9852);
        v0 = slt(a0, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00255c48
        charge(ctx, 6);
        v0 = sll(a0, 2);
        v1 = addu(s1, v0);
        v0 = 0x10000;
        v0 = addu(v1, v0);
        sw(a0, v0, 10172);
        a0 = addiu(a0, 1);
    }
    // 0x00255c78
    charge(ctx, 8);
    s0 = 256;
    jal(ctx, 0x255C7Cu, gen::fn_sub_488F30_00488f30);
    v0 = v0 & 0x1;
    s0 = addu(s0, v0);
    s2 = 0;
    for (;;) {
        // 0x00255d30
        charge(ctx, 3);
        v0 = slt(s2, s0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00255c98
        charge(ctx, 18);
        jal(ctx, 0x255C98u, gen::fn_sub_488F30_00488f30);
        v1 = 0x10000;
        v1 = addu(s1, v1);
        lw(v1, v1, 9852);
        divu(v0, v1);
        mfhi(s4);
        jal(ctx, 0x255CB4u, gen::fn_sub_488F30_00488f30);
        v1 = 0x10000;
        v1 = addu(s1, v1);
        lw(v1, v1, 9852);
        v1 = addiu(v1, -1);
        divu(v0, v1);
        mfhi(v1);
        v0 = slt(v1, s4);
        if (v0 != 0) {
            // 0x00255cec
            charge(ctx, 2);
            a2 = s4;
            s4 = v1;
        } else {
            // 0x00255ce0
            charge(ctx, 3);
            a2 = addiu(v1, 1);
        }
        // 0x00255cf4
        charge(ctx, 15);
        v0 = sll(s4, 2);
        v0 = addu(s1, v0);
        at = 0x10000;
        at = at | 0x27BC;
        a1 = addu(v0, at);
        lw(a0, a1, 0);
        v0 = sll(a2, 2);
        v0 = addu(s1, v0);
        at = 0x10000;
        at = at | 0x27BC;
        v1 = addu(v0, at);
        lw(v0, v1, 0);
        sw(v0, a1, 0);
        sw(a0, v1, 0);
        s2 = addiu(s2, 1);
    }
    // 0x00255d3c
    charge(ctx, 3);
    lw(v0, gp, -18844);  // 0x7CE354
    if (v0 == 0) {
        // 0x00255d48
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x255D54u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00255d5c
    charge(ctx, 7);
    s2 = 0;
    lw(a1, gp, -18844);  // 0x7CE354
    v0 = 0x10000;
    v0 = addu(a1, v0);
    lw(v1, v0, 9820);
    for (;;) {
        // 0x00255d90
        charge(ctx, 2);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00255d78
        charge(ctx, 4);
        lw(v0, v1, 0);
        v0 = v0 & 0x2;
        if (v0 == 0) {
            // 0x00255d88
            charge(ctx, 1);
            s2 = addiu(s2, 1);
        }
        // 0x00255d8c
        charge(ctx, 1);
        lw(v1, v1, 4036);
    }
    // 0x00255d98
    charge(ctx, 6);
    s0 = 0;
    v0 = 0x10000;
    v0 = addu(s1, v0);
    lw(a0, v0, 9852);
    for (;;) {
        // 0x00255dd0
        charge(ctx, 3);
        v0 = slt(s0, a0);
        if (v0 != 0) {
            backedge(ctx);
            // 0x00255db0
            charge(ctx, 7);
            v0 = sll(s0, 2);
            v1 = addu(s1, v0);
            v0 = 0x10000;
            v0 = addu(v1, v0);
            lw(v0, v0, 10172);
            if (v0 != 0) {
                // 0x00255dcc
                charge(ctx, 1);
                s0 = addiu(s0, 1);
                continue;
            }
        }
        break;
    }
    // 0x00255ddc
    charge(ctx, 2);
    if (a1 == 0) {
        // 0x00255de4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x255DF0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00255df8
    charge(ctx, 6);
    lw(v1, gp, -18844);  // 0x7CE354
    v0 = 0x10000;
    v0 = addu(v1, v0);
    lw(v1, v0, 9820);
    for (;;) {
        // 0x00255e34
        charge(ctx, 2);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00255e10
        charge(ctx, 5);
        s3 = v1;
        lw(v0, v1, 0);
        v0 = v0 & 0x2;
        if (v0 == 0) {
            // 0x00255e24
            charge(ctx, 3);
            lw(v0, v1, 16);
            if (v0 == s0) {
                break;
            }
            goto L_00255e30;
        }
    L_00255e30:
        charge(ctx, 1);
        lw(v1, v1, 4036);
    }
    // 0x00255e3c
    charge(ctx, 2);
    if (v1 == 0) {
        // 0x00255e44
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 1146;
        jal(ctx, 0x255E50u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00255e58
    charge(ctx, 53);
    a0 = s3;
    a1 = addiu(sp, 0x60);
    a2 = addiu(sp, 0x8C);
    jal(ctx, 0x255E64u, gen::fn_sub_256F20_00256f20);
    a0 = addiu(sp, 0x80);
    a1 = s0;
    lw(a2, sp, 0x60);
    a3 = s2;
    jal(ctx, 0x255E7Cu, gen::fn_sub_257D00_00257d00);
    lwc1(f1, sp, 0x84);
    v0 = 0x43480000;
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x84);
    a0 = addiu(s3, 4244);
    a1 = addiu(sp, 0x80);
    v0 = 0x10000;
    v0 = addu(s1, v0);
    lw(a2, v0, 10380);
    jal(ctx, 0x255EB0u, gen::fn_sub_250A30_00250a30);
    a0 = 1;
    a1 = 0;
    a2 = 6;
    a3 = 2;
    jal(ctx, 0x255EC8u, gen::fn_sub_10A4E0_0010a4e0);
    lw(v1, s3, 0);
    v1 = v1 | 0x20;
    sw(v1, s3, 0);
    v1 = v1 | 0x40;
    sw(v1, s3, 0);
    v1 = 0x10000;
    v1 = addu(s1, v1);
    sw(zero, v1, 10164);
    v1 = 0x10000;
    v1 = addu(s1, v1);
    sw(zero, v1, 10168);
    lw(v1, s1, 0);
    v1 = v1 | 0x10;
    sw(v1, s1, 0);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x0025F370 brItem_CreateStockOverBgTask -- 292 bytes; frame 0x70: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// brItem_CreateStockOverBgTask: creates the "stock over bg" kwlnTask (2256-byte work, update
// brItem_UpdateStockOverBgTask, destroy sub_25F510) as a child of $a0, sets up its background panel (+784), and records
// the work and task in the gp table slots 54 / 55.
void brItem_CreateStockOverBgTask(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x0025f370
    enter(ctx, 73);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    a0 = 2256;
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x25F3A0u, v0.u());
    s1 = v0;
    a0 = 0x690000;
    a0 = addiu(a0, -5112);  // "stock over bg"
    a1 = 6325;
    a2 = 1;
    a3 = 2;
    t0 = 0x260000;
    t0 = addiu(t0, -2912);  // &brItem_UpdateStockOverBgTask
    t1 = 0x260000;
    t1 = addiu(t1, -2800);  // &sub_25F510
    t2 = s1;
    jal(ctx, 0x25F3D4u, gen::fn_kwlnTaskInitEx_00194e10);
    s0 = v0;
    a0 = s3;
    a1 = s0;
    jal(ctx, 0x25F3E8u, gen::fn_kwlnTaskAddChild_00195550);
    sw(zero, s1, 0);
    sw(zero, sp, 0x50);
    sw(zero, sp, 0x54);
    v0 = 0x44200000;
    sw(v0, sp, 0x58);
    v0 = 0x43E00000;
    sw(v0, sp, 0x5C);
    a0 = addiu(s1, 784);
    a1 = addiu(sp, 0x50);
    jal(ctx, 0x25F414u, gen::fn_sub_21D8E0_0021d8e0);
    a0 = 10;
    jal(ctx, 0x25F420u, gen::fn_sub_21EA00_0021ea00);
    a0 = addiu(s1, 784);
    mov_s(f12, f0);
    jal(ctx, 0x25F430u, gen::fn_sub_21EAC0_0021eac0);
    v0 = 255;
    sb(v0, sp, 0x6C);
    sb(v0, sp, 0x6D);
    sb(v0, sp, 0x6E);
    sb(zero, sp, 0x6F);
    a0 = addiu(s1, 784);
    a1 = addiu(sp, 0x6C);
    jal(ctx, 0x25F454u, gen::fn_sub_21D950_0021d950);
    sw(s1, gp, -18816);  // 0x7CE370
    a0 = s2;
    jal(ctx, 0x25F464u, gen::fn_sub_25D8A0_0025d8a0);
    sw(s0, gp, -18812);  // 0x7CE374
    v0 = s0;
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x00267120 sub_267120 -- 96 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Persona panel shutdown (bp_persona.c): destroys the task tree at +4 of gp-table slot 64's record and clears its
// active bit.
void sub_267120(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00267120
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, -18776);  // 0x7CE398
    if (v0 == 0) {
        // 0x00267138
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4920);  // "bp_persona.c"
        a1 = 36;
        jal(ctx, 0x267144u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0026714c
    charge(ctx, 13);
    lw(s0, gp, -18776);  // 0x7CE398
    lw(a0, s0, 4);
    jal(ctx, 0x267154u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
    lw(a0, s0, 0);
    v1 = si(-2);
    v1 = a0 & v1;
    sw(v1, s0, 0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00274030 sub_274030 -- 204 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Battle-result sequence step (brp_seq.c): checks the current / total counters, then queues the transition between the
// records named at +128 and +4 (sub_174E20, sub_1749A0, sub_176D10) and clears bit 2.
void sub_274030(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00274030
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, -18736);  // 0x7CE3C0
    if (v0 == 0) {
        // 0x0027404c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4728);  // "brp_seq.c"
        a1 = 176;
        jal(ctx, 0x274058u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00274060
    charge(ctx, 10);
    lw(s0, gp, -18736);  // 0x7CE3C0
    jal(ctx, 0x274064u, gen::fn_sub_1756F0_001756f0);
    s1 = v0 & 0xFFFF;
    jal(ctx, 0x274070u, gen::fn_sub_175410_00175410);
    v0 = v0 & 0xFFFF;
    v0 = slt(s1, v0);
    if (v0 == 0) {
        // 0x00274088
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4728);  // "brp_seq.c"
        a1 = 1095;
        jal(ctx, 0x274094u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027409c
    charge(ctx, 24);
    lhu(a0, s0, 128);
    jal(ctx, 0x2740A0u, gen::fn_sub_174E20_00174e20);
    lhu(a0, s0, 4);
    jal(ctx, 0x2740ACu, gen::fn_sub_1749A0_001749a0);
    s1 = v0;
    lhu(a0, s0, 128);
    jal(ctx, 0x2740BCu, gen::fn_sub_1749A0_001749a0);
    a0 = v0;
    a1 = s1;
    jal(ctx, 0x2740CCu, gen::fn_sub_176D10_00176d10);
    lw(a0, s0, 0);
    v1 = si(-5);
    v1 = a0 & v1;
    sw(v1, s0, 0);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002B6460 sub_2B6460 -- 40 bytes; frame 0x10: ra sp+0x0
// Tail forwarder to sub_2B6070.
void sub_2B6460(EEContext& ctx) {
    using namespace hg;
    Gpr gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f13{ctx, 13};
    // 0x002b6460
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lwc1(f12, gp, -32652);  // 0x7CAD64
    lwc1(f13, gp, -32648);  // 0x7CAD68
    jal(ctx, 0x2B6470u, gen::fn_sub_2B6070_002b6070);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002BC2F0 sub_2BC2F0 -- 304 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Battle model cache release: frees each of the 60 cached models at gBtl+3108 (with their +1588 buffers through the
// 0x96017C free hook when gBtl+20 bit 26 is set), else also destroys the H_Cdvd request at gBtl+3348; clears gBtl+12
// bit 18.
void sub_2BC2F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002bc2f0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, -18692);  // 0x7CE3EC
    lw(a0, v1, 20);
    v1 = 0x4000000;
    v1 = a0 & v1;
    if (v1 != 0) {
        // 0x002bc388
        charge(ctx, 3);
        s1 = 0;
        for (;;) {
            // 0x002bc3e4
            charge(ctx, 3);
            v1 = sltiu(s1, 60);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002bc394
            charge(ctx, 6);
            lw(v1, gp, -18692);  // 0x7CE3EC
            s0 = sll(s1, 2);
            v1 = addu(v1, s0);
            lw(v1, v1, 3108);
            if (v1 != 0) {
                // 0x002bc3ac
                charge(ctx, 13);
                lw(a0, v1, 1588);
                v0 = 0x960000;
                lw(v0, v0, 380);  // 0x96017C
                jalr(ctx, 0x2BC3B8u, v0.u());
                lw(v0, gp, -18692);  // 0x7CE3EC
                v0 = addu(v0, s0);
                lw(a0, v0, 3108);
                jal(ctx, 0x2BC3CCu, gen::fn_sub_2B9030_002b9030);
                lw(v1, gp, -18692);  // 0x7CE3EC
                v1 = addu(v1, s0);
                sw(zero, v1, 3108);
            }
            // 0x002bc3e0
            charge(ctx, 1);
            s1 = addiu(s1, 1);
        }
    } else {
        // 0x002bc318
        charge(ctx, 3);
        s0 = 0;
        for (;;) {
            // 0x002bc354
            charge(ctx, 3);
            v1 = sltiu(s0, 60);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002bc324
            charge(ctx, 6);
            lw(v1, gp, -18692);  // 0x7CE3EC
            s1 = sll(s0, 2);
            v1 = addu(v1, s1);
            lw(a0, v1, 3108);
            if (a0 != 0) {
                // 0x002bc33c
                charge(ctx, 5);
                jal(ctx, 0x2BC33Cu, gen::fn_sub_2B9030_002b9030);
                lw(v1, gp, -18692);  // 0x7CE3EC
                v1 = addu(v1, s1);
                sw(zero, v1, 3108);
            }
            // 0x002bc350
            charge(ctx, 1);
            s0 = addiu(s0, 1);
        }
        // 0x002bc360
        charge(ctx, 4);
        lw(v1, gp, -18692);  // 0x7CE3EC
        lw(a0, v1, 3348);
        if (a0 != 0) {
            // 0x002bc370
            charge(ctx, 6);
            jal(ctx, 0x2BC370u, gen::fn_H_Cdvd_Destroy_00100ec0);
            lw(v1, gp, -18692);  // 0x7CE3EC
            sw(zero, v1, 3348);
        }
    }
    // 0x002bc3f0 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    lw(a1, gp, -18692);  // 0x7CE3EC
    lw(a0, a1, 12);
    v1 = lui(0xFFFB);
    v1 = v1 | 0xFFFF;
    v1 = a0 & v1;
    sw(v1, a1, 12);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002BC6D0 sub_2BC6D0 -- 224 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// btlTableInit helper: loads the battle table file through H_Cdvd (request, read sync), copies it into a heap block and
// hands it to the table object sub_2B8F90(2) (sub_2B96E0), then destroys the request.
void sub_2BC6D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002bc6d0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = 0;
    for (;;) {
        // 0x002bc788
        charge(ctx, 2);
        if (s2 != 0) {
            break;
        }
        backedge(ctx);
        // 0x002bc6f4
        charge(ctx, 37);
        s0 = sll(s2, 2);
        v0 = addiu(gp, -26112);  // "@ii"
        v0 = addu(v0, s0);
        lw(a0, v0, 0);
        a1 = 0;
        jal(ctx, 0x2BC708u, gen::fn_H_Cdvd_Request_00100d80);
        s1 = v0;
        a0 = s1;
        jal(ctx, 0x2BC718u, gen::fn_H_Cdvd_ReadSync_001023a0);
        v0 = addiu(gp, -18428);  // &0x7CE4F4
        s0 = addu(v0, s0);
        a0 = 2;
        jal(ctx, 0x2BC72Cu, gen::fn_sub_2B8F90_002b8f90);
        sw(v0, s0, 0);
        lw(a0, s1, 280);
        a1 = 0x40000;
        v0 = 0x960000;
        lw(v0, v0, 376);  // 0x960178
        jalr(ctx, 0x2BC748u, v0.u());
        s3 = v0;
        lw(a2, s1, 280);
        a0 = s3;
        lw(a1, s1, 272);
        jal(ctx, 0x2BC760u, gen::fn_memcpy_00521250);
        lw(a0, s0, 0);
        a1 = s3;
        jal(ctx, 0x2BC770u, gen::fn_sub_2B96E0_002b96e0);
        a0 = s1;
        jal(ctx, 0x2BC77Cu, gen::fn_H_Cdvd_Destroy_00100ec0);
        s2 = addiu(s2, 1);
    }
    // 0x002bc790
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x002D3D70 sub_2D3D70 -- 132 bytes; leaf frame (no stack)
// btlCreate helper: resets gBtl's camera / range fields (+716, +720.., +1956, +2260 to -1.0 or NaN, the distances to
// 1750.0).
void sub_2D3D70(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x002d3d70
    enter(ctx, 33);  // entry check point + this block's cycles
    lw(v1, gp, -18692);  // 0x7CE3EC
    sw(zero, v1, 716);
    a0 = lui(0xBF80);
    lw(v1, gp, -18692);  // 0x7CE3EC
    sw(a0, v1, 1956);
    lw(v1, gp, -18692);  // 0x7CE3EC
    sw(a0, v1, 2260);
    v1 = si(-1750);
    mtc1(v1, f0);
    cvt_s_w(f1, f0);
    lw(v1, gp, -18692);  // 0x7CE3EC
    swc1(f1, v1, 720);
    lw(v1, gp, -18692);  // 0x7CE3EC
    swc1(f1, v1, 724);
    lw(v1, gp, -18692);  // 0x7CE3EC
    swc1(f1, v1, 1024);
    v1 = 1750;
    mtc1(v1, f0);
    cvt_s_w(f0, f0);
    lw(v1, gp, -18692);  // 0x7CE3EC
    swc1(f0, v1, 1028);
    lw(v1, gp, -18692);  // 0x7CE3EC
    swc1(f0, v1, 1328);
    lw(v1, gp, -18692);  // 0x7CE3EC
    swc1(f1, v1, 1332);
    lw(v1, gp, -18692);  // 0x7CE3EC
    swc1(f0, v1, 1632);
    lw(v1, gp, -18692);  // 0x7CE3EC
    swc1(f0, v1, 1636);
}

// 0x002D8610 sub_2D8610 -- 104 bytes; frame 0x10: ra sp+0x0
// Table callback: -1 when gBtl+2592 already holds 94; else 94 when two or more side-1 units are active
// (btlCountActiveUnits(1, 0x80000)), otherwise -1.
void sub_2D8610(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002d8610
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, -18692);  // 0x7CE3EC
    lw(v1, v0, 2592);
    v0 = 94;
    if (v1 != v0) {
        // 0x002d8638
        charge(ctx, 8);
        a0 = 1;
        a1 = 0x80000;
        jal(ctx, 0x2D8640u, gen::fn_btlCountActiveUnits_002d4e10);
        v0 = v0 & 0xFFFF;
        at = slti(v0, 2);
        if (at == 0) {
            // 0x002d8664
            charge(ctx, 1);
            v0 = 94;
        } else {
            // 0x002d8658
            charge(ctx, 3);
            v0 = si(-1);
        }
    } else {
        // 0x002d862c
        charge(ctx, 3);
        v0 = si(-1);
    }
    // 0x002d8668 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002D8780 sub_2D8780 -- 96 bytes; frame 0x10: ra sp+0x0
// Table callback: 108 - n for n = 1..4 active side-2 units (btlCountActiveUnits(2, 0x80000)), else -1.
void sub_2D8780(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002d8780
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 2;
    a1 = 0x80000;
    jal(ctx, 0x2D8790u, gen::fn_btlCountActiveUnits_002d4e10);
    v1 = v0 & 0xFFFF;
    v0 = slti(v1, 5);
    if (v0 != 0) {
        // 0x002d87b4
        charge(ctx, 2);
        if (v1 != 0) {
            // 0x002d87c8
            charge(ctx, 2);
            v0 = 108;
            v0 = subu(v0, v1);
        } else {
            // 0x002d87bc
            charge(ctx, 3);
            v0 = si(-1);
        }
    } else {
        // 0x002d87a8
        charge(ctx, 3);
        v0 = si(-1);
    }
    // 0x002d87d0 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002D87E0 sub_2D87E0 -- 100 bytes; frame 0x10: ra sp+0x0
// Table callback: 114 - n for n = 2..5 active side-2 units (btlCountActiveUnits(2, 0x80000)), else -1.
void sub_2D87E0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002d87e0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 2;
    a1 = 0x80000;
    jal(ctx, 0x2D87F0u, gen::fn_btlCountActiveUnits_002d4e10);
    v1 = v0 & 0xFFFF;
    at = slti(v1, 6);
    if (at != 0) {
        // 0x002d8814
        charge(ctx, 3);
        at = slti(v1, 2);
        if (at == 0) {
            // 0x002d882c
            charge(ctx, 2);
            v0 = 114;
            v0 = subu(v0, v1);
        } else {
            // 0x002d8820
            charge(ctx, 3);
            v0 = si(-1);
        }
    } else {
        // 0x002d8808
        charge(ctx, 3);
        v0 = si(-1);
    }
    // 0x002d8834 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002D89E0 sub_2D89E0 -- 148 bytes; leaf frame (no stack)
// Table callback: maps $a1 (2..5, 7..10) to 191..198, else -1.
void sub_2D89E0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a1{ctx, 5};
    // 0x002d89e0
    enter(ctx, 3);  // entry check point + this block's cycles
    at = sltiu(a1, 11);
    if (at != 0) {
        // 0x002d89ec
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, 32256);  // &0x7B7E00
        v0 = sll(a1, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x2D8A08u:  // table[2]
            // 0x002d8a08
            charge(ctx, 3);
            v0 = 191;
            break;
        case 0x2D8A14u:  // table[3]
            // 0x002d8a14
            charge(ctx, 3);
            v0 = 192;
            break;
        case 0x2D8A20u:  // table[4]
            // 0x002d8a20
            charge(ctx, 3);
            v0 = 193;
            break;
        case 0x2D8A2Cu:  // table[5]
            // 0x002d8a2c
            charge(ctx, 3);
            v0 = 194;
            break;
        case 0x2D8A38u:  // table[7]
            // 0x002d8a38
            charge(ctx, 3);
            v0 = 195;
            break;
        case 0x2D8A44u:  // table[8]
            // 0x002d8a44
            charge(ctx, 3);
            v0 = 196;
            break;
        case 0x2D8A50u:  // table[9]
            // 0x002d8a50
            charge(ctx, 3);
            v0 = 197;
            break;
        case 0x2D8A5Cu:  // table[10]
            // 0x002d8a5c
            charge(ctx, 3);
            v0 = 198;
            break;
        case 0x2D8A68u:  // table[0, 1, 6]
        L_002d8a68:
            charge(ctx, 1);
            v0 = si(-1);
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x002d8a6c (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
    goto L_002d8a68;
}

// 0x002D8CF0 sub_2D8CF0 -- 192 bytes; leaf frame (no stack)
// Table callback: -1 when the btlUnit at $a0+48 has its +162 byte set, else maps its +164 kind (1..5, 7..10) to
// 212..220.
void sub_2D8CF0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x002d8cf0
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, 48);
    lbu(v0, v1, 162);
    if (v0 == 0) {
        // 0x002d8d0c
        charge(ctx, 4);
        lhu(v0, v1, 164);
        at = sltiu(v0, 11);
        if (at != 0) {
            // 0x002d8d1c
            charge(ctx, 7);
            v1 = 0x7B0000;
            v1 = addiu(v1, 32304);  // &0x7B7E30
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x2D8D38u:  // table[1]
                // 0x002d8d38
                charge(ctx, 3);
                v0 = 212;
                break;
            case 0x2D8D44u:  // table[2]
                // 0x002d8d44
                charge(ctx, 3);
                v0 = 213;
                break;
            case 0x2D8D50u:  // table[3]
                // 0x002d8d50
                charge(ctx, 3);
                v0 = 214;
                break;
            case 0x2D8D5Cu:  // table[4]
                // 0x002d8d5c
                charge(ctx, 3);
                v0 = 215;
                break;
            case 0x2D8D68u:  // table[5]
                // 0x002d8d68
                charge(ctx, 3);
                v0 = 216;
                break;
            case 0x2D8D74u:  // table[7]
                // 0x002d8d74
                charge(ctx, 3);
                v0 = 217;
                break;
            case 0x2D8D80u:  // table[8]
                // 0x002d8d80
                charge(ctx, 3);
                v0 = 218;
                break;
            case 0x2D8D8Cu:  // table[9]
                // 0x002d8d8c
                charge(ctx, 3);
                v0 = 219;
                break;
            case 0x2D8D98u:  // table[10]
                // 0x002d8d98
                charge(ctx, 3);
                v0 = 220;
                break;
            case 0x2D8DA4u:  // table[0, 6]
            L_002d8da4:
                charge(ctx, 1);
                v0 = si(-1);
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
            // 0x002d8da8 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            return;
        }
        goto L_002d8da4;
    }
    // 0x002d8d00
    charge(ctx, 3);
    v0 = si(-1);
    // 0x002d8da8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x002D8DC0 sub_2D8DC0 -- 192 bytes; leaf frame (no stack)
// Table callback: -1 when the btlUnit at $a0+48 has its +162 byte set, else maps its +164 kind (1..5, 7..10) to
// 221..229.
void sub_2D8DC0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x002d8dc0
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, 48);
    lbu(v0, v1, 162);
    if (v0 == 0) {
        // 0x002d8ddc
        charge(ctx, 4);
        lhu(v0, v1, 164);
        at = sltiu(v0, 11);
        if (at != 0) {
            // 0x002d8dec
            charge(ctx, 7);
            v1 = 0x7B0000;
            v1 = addiu(v1, 32352);  // &0x7B7E60
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x2D8E08u:  // table[1]
                // 0x002d8e08
                charge(ctx, 3);
                v0 = 221;
                break;
            case 0x2D8E14u:  // table[2]
                // 0x002d8e14
                charge(ctx, 3);
                v0 = 222;
                break;
            case 0x2D8E20u:  // table[3]
                // 0x002d8e20
                charge(ctx, 3);
                v0 = 223;
                break;
            case 0x2D8E2Cu:  // table[4]
                // 0x002d8e2c
                charge(ctx, 3);
                v0 = 224;
                break;
            case 0x2D8E38u:  // table[5]
                // 0x002d8e38
                charge(ctx, 3);
                v0 = 225;
                break;
            case 0x2D8E44u:  // table[7]
                // 0x002d8e44
                charge(ctx, 3);
                v0 = 226;
                break;
            case 0x2D8E50u:  // table[8]
                // 0x002d8e50
                charge(ctx, 3);
                v0 = 227;
                break;
            case 0x2D8E5Cu:  // table[9]
                // 0x002d8e5c
                charge(ctx, 3);
                v0 = 228;
                break;
            case 0x2D8E68u:  // table[10]
                // 0x002d8e68
                charge(ctx, 3);
                v0 = 229;
                break;
            case 0x2D8E74u:  // table[0, 6]
            L_002d8e74:
                charge(ctx, 1);
                v0 = si(-1);
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
            // 0x002d8e78 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            return;
        }
        goto L_002d8e74;
    }
    // 0x002d8dd0
    charge(ctx, 3);
    v0 = si(-1);
    // 0x002d8e78 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x002D8E80 sub_2D8E80 -- 108 bytes; frame 0x10: ra sp+0x0
// Table callback: 232 when $a1 is set, 233 when $a0+24 has bits 0x1800, 231 when sub_2DDC10(6) is true, else 230.
void sub_2D8E80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002d8e80
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a1 == 0) {
        // 0x002d8e9c
        charge(ctx, 4);
        lhu(v0, a0, 24);
        v0 = v0 & 0x1800;
        if (v0 == 0) {
            // 0x002d8eb8
            charge(ctx, 5);
            a0 = 6;
            jal(ctx, 0x2D8EBCu, gen::fn_sub_2DDC10_002ddc10);
            if (v0 != 0) {
                // 0x002d8ed8
                charge(ctx, 1);
                v0 = 231;
            } else {
                // 0x002d8ecc
                charge(ctx, 3);
                v0 = 230;
            }
        } else {
            // 0x002d8eac
            charge(ctx, 3);
            v0 = 233;
        }
    } else {
        // 0x002d8e90
        charge(ctx, 3);
        v0 = 232;
    }
    // 0x002d8edc (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002D9B20 sub_2D9B20 -- 192 bytes; leaf frame (no stack)
// Table callback: -1 when the btlUnit at $a0+48 has its +162 byte set, else maps its +164 kind (1..5, 7..10) to
// 337..345.
void sub_2D9B20(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x002d9b20
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, 48);
    lbu(v0, v1, 162);
    if (v0 == 0) {
        // 0x002d9b3c
        charge(ctx, 4);
        lhu(v0, v1, 164);
        at = sltiu(v0, 11);
        if (at != 0) {
            // 0x002d9b4c
            charge(ctx, 7);
            v1 = 0x7B0000;
            v1 = addiu(v1, 32448);  // &0x7B7EC0
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x2D9B68u:  // table[1]
                // 0x002d9b68
                charge(ctx, 3);
                v0 = 337;
                break;
            case 0x2D9B74u:  // table[2]
                // 0x002d9b74
                charge(ctx, 3);
                v0 = 338;
                break;
            case 0x2D9B80u:  // table[3]
                // 0x002d9b80
                charge(ctx, 3);
                v0 = 339;
                break;
            case 0x2D9B8Cu:  // table[4]
                // 0x002d9b8c
                charge(ctx, 3);
                v0 = 340;
                break;
            case 0x2D9B98u:  // table[5]
                // 0x002d9b98
                charge(ctx, 3);
                v0 = 341;
                break;
            case 0x2D9BA4u:  // table[7]
                // 0x002d9ba4
                charge(ctx, 3);
                v0 = 342;
                break;
            case 0x2D9BB0u:  // table[8]
                // 0x002d9bb0
                charge(ctx, 3);
                v0 = 343;
                break;
            case 0x2D9BBCu:  // table[9]
                // 0x002d9bbc
                charge(ctx, 3);
                v0 = 344;
                break;
            case 0x2D9BC8u:  // table[10]
                // 0x002d9bc8
                charge(ctx, 3);
                v0 = 345;
                break;
            case 0x2D9BD4u:  // table[0, 6]
            L_002d9bd4:
                charge(ctx, 1);
                v0 = si(-1);
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
            // 0x002d9bd8 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            return;
        }
        goto L_002d9bd4;
    }
    // 0x002d9b30
    charge(ctx, 3);
    v0 = si(-1);
    // 0x002d9bd8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x002DA810 sub_2DA810 -- 284 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Table callback on btlAction $a0: only for gBtl's current action (gBtl+328) whose unit fails
// datCalcChkBadStatus(+2604, 1); returns 401 / 400 / 399 by the action's +108 kind (11 with sub_17D800 false; 2 aimed
// at side 2 with sub_308860(+110); 1 aimed at side 1), else -1.
void sub_2DA810(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002da810
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, gp, -18692);  // 0x7CE3EC
    lw(v0, v0, 328);
    if (v0 == s0) {
        // 0x002da83c
        charge(ctx, 7);
        lw(v0, s0, 48);
        lw(a0, v0, 2604);
        a1 = 1;
        jal(ctx, 0x2DA848u, gen::fn_datCalcChkBadStatus_00300580);
        if (v0 != 0) {
            // 0x002da864
            charge(ctx, 4);
            lhu(v1, s0, 108);
            v0 = 11;
            if (v1 == v0) {
                // 0x002da8f8
                charge(ctx, 4);
                jal(ctx, 0x2DA8F8u, gen::fn_sub_17D800_0017d800);
                if (v0 != 0) {
                L_002da914:
                    charge(ctx, 1);
                    v0 = si(-1);
                } else {
                    // 0x002da908
                    charge(ctx, 3);
                    v0 = 401;
                }
            } else {
                // 0x002da874
                charge(ctx, 3);
                v0 = 2;
                if (v1 == v0) {
                    // 0x002da8bc
                    charge(ctx, 7);
                    a0 = addiu(s0, 56);
                    jal(ctx, 0x2DA8C0u, gen::fn_btlTargetGetSideMask_002d1600);
                    v1 = v0 & 0xFFFF;
                    v0 = 2;
                    if (v1 != v0) {
                        goto L_002da914;
                    }
                    // 0x002da8d8
                    charge(ctx, 5);
                    lhu(a0, s0, 110);
                    jal(ctx, 0x2DA8DCu, gen::fn_sub_308860_00308860);
                    if (v0 == 0) {
                        goto L_002da914;
                    }
                    // 0x002da8ec
                    charge(ctx, 3);
                    v0 = 400;
                } else {
                    // 0x002da880
                    charge(ctx, 3);
                    v0 = 1;
                    if (v1 != v0) {
                        // 0x002da88c
                        charge(ctx, 2);
                        goto L_002da914;
                    }
                    // 0x002da894
                    charge(ctx, 7);
                    a0 = addiu(s0, 56);
                    jal(ctx, 0x2DA898u, gen::fn_btlTargetGetSideMask_002d1600);
                    v1 = v0 & 0xFFFF;
                    v0 = 1;
                    if (v1 != v0) {
                        goto L_002da914;
                    }
                    // 0x002da8b0
                    charge(ctx, 3);
                    v0 = 399;
                }
            }
        } else {
            // 0x002da858
            charge(ctx, 3);
            v0 = si(-1);
        }
    } else {
        // 0x002da830
        charge(ctx, 3);
        v0 = si(-1);
    }
    // 0x002da918 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002DA930 sub_2DA930 -- 228 bytes; leaf frame (no stack)
// Table callback: maps the id $a1 463..471 to gBtl+2580 (2, 3, 4, 5, 7, 8, 9, 10, 6); returns $a1.
void sub_2DA930(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a1{ctx, 5}, gp{ctx, 28};
    // 0x002da930
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = addiu(a1, -463);
    at = sltiu(v0, 9);
    if (at != 0) {
        // 0x002da940
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, 32688);  // &0x7B7FB0
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x2DA95Cu:  // table[0]
            // 0x002da95c
            charge(ctx, 5);
            v1 = 2;
            lw(v0, gp, -18692);  // 0x7CE3EC
            sh(v1, v0, 2580);
            break;
        case 0x2DA970u:  // table[1]
            // 0x002da970
            charge(ctx, 5);
            v1 = 3;
            lw(v0, gp, -18692);  // 0x7CE3EC
            sh(v1, v0, 2580);
            break;
        case 0x2DA984u:  // table[2]
            // 0x002da984
            charge(ctx, 5);
            v1 = 4;
            lw(v0, gp, -18692);  // 0x7CE3EC
            sh(v1, v0, 2580);
            break;
        case 0x2DA998u:  // table[3]
            // 0x002da998
            charge(ctx, 5);
            v1 = 5;
            lw(v0, gp, -18692);  // 0x7CE3EC
            sh(v1, v0, 2580);
            break;
        case 0x2DA9ACu:  // table[4]
            // 0x002da9ac
            charge(ctx, 5);
            v1 = 7;
            lw(v0, gp, -18692);  // 0x7CE3EC
            sh(v1, v0, 2580);
            break;
        case 0x2DA9C0u:  // table[5]
            // 0x002da9c0
            charge(ctx, 5);
            v1 = 8;
            lw(v0, gp, -18692);  // 0x7CE3EC
            sh(v1, v0, 2580);
            break;
        case 0x2DA9D4u:  // table[6]
            // 0x002da9d4
            charge(ctx, 5);
            v1 = 9;
            lw(v0, gp, -18692);  // 0x7CE3EC
            sh(v1, v0, 2580);
            break;
        case 0x2DA9E8u:  // table[7]
            // 0x002da9e8
            charge(ctx, 5);
            v1 = 10;
            lw(v0, gp, -18692);  // 0x7CE3EC
            sh(v1, v0, 2580);
            break;
        case 0x2DA9FCu:  // table[8]
            // 0x002da9fc
            charge(ctx, 3);
            v1 = 6;
            lw(v0, gp, -18692);  // 0x7CE3EC
            sh(v1, v0, 2580);
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
    }
    // 0x002daa08 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    v0 = a1;
}

// 0x002DB8D0 sub_2DB8D0 -- 144 bytes; frame 0x10: ra sp+0x0
// btlCreate helper: clears gBtl's 64-byte block at +2552 and resets its fields (+2588 0, +2592.. -1, +2580 = 6).
void sub_2DB8D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002db8d0
    enter(ctx, 36);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, -18692);  // 0x7CE3EC
    a0 = addiu(v0, 2552);
    a1 = 0;
    a2 = 64;
    jal(ctx, 0x2DB8E8u, gen::fn_memset_00521408);
    lw(v1, gp, -18692);  // 0x7CE3EC
    sw(zero, v1, 2588);
    a0 = si(-1);
    lw(v1, gp, -18692);  // 0x7CE3EC
    sw(a0, v1, 2592);
    lw(v1, gp, -18692);  // 0x7CE3EC
    sh(a0, v1, 2596);
    lw(v1, gp, -18692);  // 0x7CE3EC
    sw(a0, v1, 2600);
    lw(v1, gp, -18692);  // 0x7CE3EC
    sh(a0, v1, 2604);
    lw(v1, gp, -18692);  // 0x7CE3EC
    sw(a0, v1, 2608);
    lw(v1, gp, -18692);  // 0x7CE3EC
    sh(a0, v1, 2612);
    lw(v1, gp, -18692);  // 0x7CE3EC
    sh(zero, v1, 2584);
    lw(v1, gp, -18692);  // 0x7CE3EC
    sh(zero, v1, 2582);
    a0 = 6;
    lw(v1, gp, -18692);  // 0x7CE3EC
    sh(a0, v1, 2580);
    lw(v1, gp, -18692);  // 0x7CE3EC
    sh(zero, v1, 2614);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002DB980 sub_2DB980 -- 104 bytes; frame 0x10: ra sp+0x0
// Releases gBtl's H_Cdvd request at +2588 (clearing gBtl+12 bit 24), clears gBtl+2582 bit 0, then tail-calls
// sub_3C8F20.
void sub_2DB980(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002db980
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, -18692);  // 0x7CE3EC
    lw(a0, v0, 2588);
    if (a0 != 0) {
        // 0x002db998
        charge(ctx, 10);
        jal(ctx, 0x2DB998u, gen::fn_H_Cdvd_Destroy_00100ec0);
        lw(v0, gp, -18692);  // 0x7CE3EC
        sw(zero, v0, 2588);
        lw(a0, gp, -18692);  // 0x7CE3EC
        lw(v1, a0, 12);
        v0 = lui(0xFEFF);
        v0 = v0 | 0xFFFF;
        v0 = v1 & v0;
        sw(v0, a0, 12);
    }
    // 0x002db9c0
    charge(ctx, 10);
    lw(v1, gp, -18692);  // 0x7CE3EC
    lhu(v0, v1, 2582);
    v0 = v0 & 0xFFFE;
    sh(v0, v1, 2582);
    jal(ctx, 0x2DB9D0u, gen::fn_sub_3C8F20_003c8f20);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002DCFB0 sub_2DCFB0 -- 100 bytes; frame 0x10: ra sp+0x0
// Table callback on the record $a0 (u16 id, s16 pair): calls sub_10A0E0(1, id) when gBtl's 6-byte slot +2708 + 6 * id
// differs from the pair.
void sub_2DCFB0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002dcfb0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lhu(a3, a0, 0);
    v1 = sll(a3, 1);
    v1 = addu(v1, a3);
    a1 = sll(v1, 1);
    lw(v1, gp, -18692);  // 0x7CE3EC
    a2 = addu(a1, v1);
    lh(a1, a2, 2708);
    lhu(v1, a0, 2);
    if (a1 == v1) {
        // 0x002dcfe0
        charge(ctx, 4);
        lh(a1, a2, 2710);
        lhu(v1, a0, 4);
        if (a1 != v1) {
            goto L_002dcff0;
        }
        // 0x002dd004 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
L_002dcff0:
    charge(ctx, 5);
    a1 = dsll32(a3, 16);
    a1 = dsra32(a1, 16);
    a0 = 1;
    jal(ctx, 0x2DCFFCu, gen::fn_sub_10A0E0_0010a0e0);
    // 0x002dd004 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002DD9B0 sub_2DD9B0 -- 492 bytes; frame 0x130: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// btlTableInit helper: loads the voice banks sound/v450001.afs, v451001.afs and v452001.afs into heap blocks through
// H_Cdvd_LoadAfsFile (slots 3 / 4 / 5), polling sub_53C268 and retrying on status 4, then sets the ready flags at
// 0x7CE4FC / 0x7CE500.
void sub_2DD9B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002dd9b0
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0x130);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = 0x960000;
    s0 = addiu(s0, 376);  // &0x960178
    a0 = 2764;
    a1 = 0x40000;
    lw(v0, s0, 0);  // 0x960178
    jalr(ctx, 0x2DD9D4u, v0.u());
    s1 = v0;
    a0 = addiu(sp, 0x30);
    a1 = 0x690000;
    a1 = addiu(a1, 31680);  // "sound/v%03d%03d.afs"
    a2 = 450;
    a3 = 1;
    jal(ctx, 0x2DD9F4u, gen::fn_sprintf_00523ac8);
    a0 = 3;
    a1 = addiu(sp, 0x30);
    a2 = 0;
    a3 = s1;
    jal(ctx, 0x2DDA0Cu, gen::fn_H_Cdvd_LoadAfsFile_001024a0);
    for (;;) {
        // 0x002dda40
        charge(ctx, 6);
        a0 = 3;
        jal(ctx, 0x2DDA44u, gen::fn_sub_53C268_0053c268);
        v1 = 3;
        if (v0 == v1) {
            break;
        }
        backedge(ctx);
        // 0x002dda1c
        charge(ctx, 3);
        v1 = 4;
        if (v0 == v1) {
            // 0x002dda28
            charge(ctx, 6);
            a0 = 3;
            a1 = addiu(sp, 0x30);
            a2 = 0;
            a3 = s1;
            jal(ctx, 0x2DDA38u, gen::fn_H_Cdvd_LoadAfsFile_001024a0);
        }
    }
    // 0x002dda58
    charge(ctx, 23);
    v0 = 1;
    sw(v0, gp, -18420);  // 0x7CE4FC
    a0 = 1344;
    a1 = 0x40000;
    lw(v0, s0, 0);
    jalr(ctx, 0x2DDA6Cu, v0.u());
    s1 = v0;
    a0 = addiu(sp, 0x30);
    a1 = 0x690000;
    a1 = addiu(a1, 31680);  // "sound/v%03d%03d.afs"
    a2 = 451;
    a3 = 1;
    jal(ctx, 0x2DDA8Cu, gen::fn_sprintf_00523ac8);
    a0 = 4;
    a1 = addiu(sp, 0x30);
    a2 = 0;
    a3 = s1;
    jal(ctx, 0x2DDAA4u, gen::fn_H_Cdvd_LoadAfsFile_001024a0);
    for (;;) {
        // 0x002ddad4
        charge(ctx, 6);
        a0 = 4;
        jal(ctx, 0x2DDAD8u, gen::fn_sub_53C268_0053c268);
        v1 = 3;
        if (v0 == v1) {
            break;
        }
        backedge(ctx);
        // 0x002ddab4
        charge(ctx, 3);
        a0 = 4;
        if (v0 == a0) {
            // 0x002ddac0
            charge(ctx, 5);
            a1 = addiu(sp, 0x30);
            a2 = 0;
            a3 = s1;
            jal(ctx, 0x2DDACCu, gen::fn_H_Cdvd_LoadAfsFile_001024a0);
        }
    }
    // 0x002ddaec
    charge(ctx, 21);
    a0 = 2572;
    a1 = 0x40000;
    lw(v0, s0, 0);
    jalr(ctx, 0x2DDAF8u, v0.u());
    s0 = v0;
    a0 = addiu(sp, 0x30);
    a1 = 0x690000;
    a1 = addiu(a1, 31680);  // "sound/v%03d%03d.afs"
    a2 = 452;
    a3 = 1;
    jal(ctx, 0x2DDB18u, gen::fn_sprintf_00523ac8);
    a0 = 5;
    a1 = addiu(sp, 0x30);
    a2 = 0;
    a3 = s0;
    jal(ctx, 0x2DDB30u, gen::fn_H_Cdvd_LoadAfsFile_001024a0);
    for (;;) {
        // 0x002ddb64
        charge(ctx, 6);
        a0 = 5;
        jal(ctx, 0x2DDB68u, gen::fn_sub_53C268_0053c268);
        v1 = 3;
        if (v0 == v1) {
            break;
        }
        backedge(ctx);
        // 0x002ddb40
        charge(ctx, 3);
        v1 = 4;
        if (v0 == v1) {
            // 0x002ddb4c
            charge(ctx, 6);
            a0 = 5;
            a1 = addiu(sp, 0x30);
            a2 = 0;
            a3 = s0;
            jal(ctx, 0x2DDB5Cu, gen::fn_H_Cdvd_LoadAfsFile_001024a0);
        }
    }
    // 0x002ddb7c
    charge(ctx, 8);
    v1 = 1;
    sw(v1, gp, -18416);  // 0x7CE500
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x130);
}

// 0x002E2F30 sub_2E2F30 -- 76 bytes; frame 0x10: ra sp+0x0
// btlCreate helper: clears gBtl's 20-byte block at +2804 (+2808 = 3, +2818 = 0) and sets the word at gp-20028+124.
void sub_2E2F30(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e2f30
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, -18692);  // 0x7CE3EC
    a0 = addiu(v0, 2804);
    a1 = 0;
    a2 = 20;
    jal(ctx, 0x2E2F48u, gen::fn_memset_00521408);
    a0 = 3;
    lw(v1, gp, -18692);  // 0x7CE3EC
    sh(a0, v1, 2808);
    lw(v1, gp, -18692);  // 0x7CE3EC
    sh(zero, v1, 2818);
    v1 = 1;
    sw(v1, gp, -19940);  // 0x7CDF0C
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002E2F80 sub_2E2F80 -- 140 bytes; frame 0x10: ra sp+0x0
// Frees gBtl's buffers at +2812 / +2820 through the 0x96017C free hook (clearing their +2806 / +2816 bit 0) and clears
// the word at 0x7CDF0C.
void sub_2E2F80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e2f80
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, -18692);  // 0x7CE3EC
    lw(a0, v1, 2812);
    if (a0 != 0) {
        // 0x002e2f98
        charge(ctx, 10);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        jalr(ctx, 0x2E2FA0u, v0.u());
        lw(v1, gp, -18692);  // 0x7CE3EC
        sw(zero, v1, 2812);
        lw(a0, gp, -18692);  // 0x7CE3EC
        lhu(v1, a0, 2806);
        v1 = v1 & 0xFFFE;
        sh(v1, a0, 2806);
    }
    // 0x002e2fc0
    charge(ctx, 4);
    lw(v1, gp, -18692);  // 0x7CE3EC
    lw(a0, v1, 2820);
    if (a0 != 0) {
        // 0x002e2fd0
        charge(ctx, 10);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        jalr(ctx, 0x2E2FD8u, v0.u());
        lw(v1, gp, -18692);  // 0x7CE3EC
        sw(zero, v1, 2820);
        lw(a0, gp, -18692);  // 0x7CE3EC
        lhu(v1, a0, 2816);
        v1 = v1 & 0xFFFE;
        sh(v1, a0, 2816);
    }
    // 0x002e2ff8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    sw(zero, gp, -19940);  // 0x7CDF0C
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002E6A20 sub_2E6A20 -- 1672 bytes; frame 0x160: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// Battle camera shot: frames the attacker / target pair of the camera's action ($a0+224) -- computes the two positions,
// offsets and heights (tanf of the field of view), clamps the eye height to 22.5, picks a cut (51 / 3) by distance, and
// hands the eye / look-at to sub_2A3E80 / sub_2A2290 / sub_2A3110.
void sub_2E6A20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23};
    // 0x002e6a20
    enter(ctx, 45);  // entry check point + this block's cycles
    sp = addiu(sp, -0x160);
    sd(ra, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s4 = a0;
    mov_s(f23, f12);
    lw(v0, a0, 224);
    lw(s3, v0, 48);
    lw(v0, v0, 56);
    lw(s2, v0, 48);
    a0 = s3;
    a1 = s2;
    a2 = addiu(sp, 0x150);
    a3 = addiu(sp, 0x140);
    jal(ctx, 0x2E6A74u, gen::fn_sub_2E6130_002e6130);
    mov_s(f22, f0);
    lwc1(f1, s3, 144);
    lwc1(f0, s3, 44);
    mul_s(f21, f1, f0);
    lwc1(f1, s2, 144);
    lwc1(f0, s2, 44);
    mul_s(f20, f1, f0);
    lwc1(f1, s4, 156);
    lwc1(f0, sp, 0x150);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0xB8);
    lwc1(f1, s4, 164);
    lwc1(f0, sp, 0x158);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0xBC);
    a0 = addiu(sp, 0xB8);
    a1 = a0;
    jal(ctx, 0x2E6AC0u, gen::fn_sub_4C6B20_004c6b20);
    lbu(v0, s3, 162);
    if (v0 != 0) {
        // 0x002e6bf0
        charge(ctx, 69);
        a0 = addiu(sp, 0xD0);
        a1 = addiu(sp, 0x140);
        a2 = addiu(sp, 0x150);
        jal(ctx, 0x2E6BFCu, gen::fn_sub_2D1DE0_002d1de0);
        a0 = addiu(sp, 0x110);
        a1 = 0x690000;
        a1 = addiu(a1, 30880);  // &0x6978A0
        a2 = 1;
        a3 = addiu(sp, 0xD0);
        jal(ctx, 0x2E6C18u, gen::fn_sub_4BE1E0_004be1e0);
        lwc1(f0, sp, 0x110);
        mul_s(f3, f0, f21);
        swc1(f3, sp, 0x110);
        lwc1(f0, sp, 0x114);
        mul_s(f2, f0, f21);
        swc1(f2, sp, 0x114);
        lwc1(f0, sp, 0x118);
        mul_s(f1, f0, f21);
        swc1(f1, sp, 0x118);
        lwc1(f0, sp, 0x150);
        add_s(f3, f0, f3);
        swc1(f3, sp, 0x150);
        lwc1(f0, sp, 0x154);
        add_s(f2, f0, f2);
        swc1(f2, sp, 0x154);
        lwc1(f0, sp, 0x158);
        add_s(f1, f0, f1);
        swc1(f1, sp, 0x158);
        lwc1(f0, sp, 0x140);
        sub_s(f0, f3, f0);
        swc1(f0, sp, 0x100);
        lwc1(f0, sp, 0x144);
        sub_s(f0, f2, f0);
        swc1(f0, sp, 0x104);
        lwc1(f0, sp, 0x148);
        sub_s(f0, f1, f0);
        swc1(f0, sp, 0x108);
        a0 = addiu(sp, 0x100);
        a1 = a0;
        jal(ctx, 0x2E6C94u, gen::fn_sub_4C69F0_004c69f0);
        s0 = s2;
        s1 = s3;
        ld(v0, sp, 0x140);
        lwc1(f1, sp, 0x148);
        sd(v0, sp, 0x130);
        swc1(f1, sp, 0x138);
        lwc1(f2, s2, 144);
        lwc1(f1, s2, 44);
        mul_s(f2, f2, f1);
        v0 = 0x3F000000;
        mtc1(v0, f1);
        mul_s(f1, f1, f2);
        lwc1(f2, gp, -32672);  // 0x7CAD50
        mul_s(f3, f2, f0);
        lwc1(f0, sp, 0x100);
        mul_s(f2, f0, f3);
        swc1(f2, sp, 0x120);
        lwc1(f2, sp, 0x104);
        mul_s(f2, f2, f3);
        swc1(f2, sp, 0x124);
        lwc1(f5, sp, 0x108);
        mul_s(f2, f5, f3);
        swc1(f2, sp, 0x128);
        lwc1(f20, sp, 0x134);
        swc1(f20, sp, 0xF4);
    } else {
        // 0x002e6ad4
        charge(ctx, 71);
        a0 = addiu(sp, 0xD0);
        a1 = addiu(sp, 0x150);
        a2 = addiu(sp, 0x140);
        jal(ctx, 0x2E6AE0u, gen::fn_sub_2D1DE0_002d1de0);
        a0 = addiu(sp, 0x110);
        a1 = 0x690000;
        a1 = addiu(a1, 30880);  // &0x6978A0
        a2 = 1;
        a3 = addiu(sp, 0xD0);
        jal(ctx, 0x2E6AFCu, gen::fn_sub_4BE1E0_004be1e0);
        lwc1(f0, sp, 0x110);
        mul_s(f3, f0, f20);
        swc1(f3, sp, 0x110);
        lwc1(f0, sp, 0x114);
        mul_s(f2, f0, f20);
        swc1(f2, sp, 0x114);
        lwc1(f0, sp, 0x118);
        mul_s(f1, f0, f20);
        swc1(f1, sp, 0x118);
        lwc1(f0, sp, 0x140);
        add_s(f3, f0, f3);
        swc1(f3, sp, 0x140);
        lwc1(f0, sp, 0x144);
        add_s(f2, f0, f2);
        swc1(f2, sp, 0x144);
        lwc1(f0, sp, 0x148);
        add_s(f1, f0, f1);
        swc1(f1, sp, 0x148);
        lwc1(f0, sp, 0x150);
        sub_s(f0, f0, f3);
        swc1(f0, sp, 0x100);
        lwc1(f0, sp, 0x154);
        sub_s(f0, f0, f2);
        swc1(f0, sp, 0x104);
        lwc1(f0, sp, 0x158);
        sub_s(f0, f0, f1);
        swc1(f0, sp, 0x108);
        a0 = addiu(sp, 0x100);
        a1 = a0;
        jal(ctx, 0x2E6B78u, gen::fn_sub_4C69F0_004c69f0);
        s0 = s3;
        s1 = s2;
        ld(v0, sp, 0x150);
        lwc1(f1, sp, 0x158);
        sd(v0, sp, 0x130);
        swc1(f1, sp, 0x138);
        lwc1(f2, s3, 144);
        lwc1(f1, s3, 44);
        mul_s(f2, f2, f1);
        v0 = 0x3FA00000;
        mtc1(v0, f1);
        mul_s(f1, f1, f2);
        lwc1(f2, gp, -32616);  // 0x7CAD88
        mul_s(f3, f2, f0);
        lwc1(f0, sp, 0x100);
        mul_s(f2, f0, f3);
        swc1(f2, sp, 0x120);
        lwc1(f2, sp, 0x104);
        mul_s(f2, f2, f3);
        swc1(f2, sp, 0x124);
        lwc1(f5, sp, 0x108);
        mul_s(f2, f5, f3);
        swc1(f2, sp, 0x128);
        lwc1(f20, sp, 0x134);
        swc1(f20, sp, 0xF4);
    }
    // 0x002e6d04
    charge(ctx, 23);
    lwc1(f3, sp, 0x120);
    lwc1(f2, sp, 0x140);
    add_s(f2, f3, f2);
    swc1(f2, sp, 0x120);
    lwc1(f3, sp, 0x124);
    lwc1(f2, sp, 0x144);
    add_s(f2, f3, f2);
    swc1(f2, sp, 0x124);
    lwc1(f3, sp, 0x128);
    lwc1(f2, sp, 0x148);
    add_s(f2, f3, f2);
    swc1(f2, sp, 0x128);
    swc1(f5, sp, 0xB0);
    neg_s(f3, f0);
    swc1(f3, sp, 0xB4);
    lwc1(f4, sp, 0xB8);
    lwc1(f2, sp, 0xBC);
    mula_s(f3, f2);
    mtc1(zero, f3);
    madd_s(f2, f5, f4);
    c_lt_s(f2, f3);
    if (cond(ctx)) {
        // 0x002e6d88
        charge(ctx, 8);
        lwc1(f2, sp, 0x130);
        adda_s(f3, f2);
        msub_s(f2, f5, f1);
        swc1(f2, sp, 0xF0);
        lwc1(f21, sp, 0x138);
        adda_s(f3, f21);
        madd_s(f0, f0, f1);
        swc1(f0, sp, 0xF8);
    } else {
        // 0x002e6d60
        charge(ctx, 10);
        lwc1(f2, sp, 0x130);
        adda_s(f3, f2);
        madd_s(f2, f5, f1);
        swc1(f2, sp, 0xF0);
        lwc1(f21, sp, 0x138);
        adda_s(f3, f21);
        msub_s(f0, f0, f1);
        swc1(f0, sp, 0xF8);
    }
    // 0x002e6da8
    charge(ctx, 60);
    a0 = addiu(sp, 0x98);
    a1 = addiu(sp, 0xF0);
    a2 = addiu(sp, 0x120);
    a3 = 0x690000;
    a3 = addiu(a3, 30848);  // &0x697880
    jal(ctx, 0x2E6DBCu, gen::fn_sub_2A4690_002a4690);
    a0 = addiu(sp, 0x100);
    a1 = 0x690000;
    a1 = addiu(a1, 30880);  // &0x6978A0
    a2 = 1;
    a3 = addiu(sp, 0x98);
    jal(ctx, 0x2E6DD8u, gen::fn_sub_4BE1E0_004be1e0);
    lwc1(f0, sp, 0x120);
    swc1(f0, sp, 0xC0);
    lwc1(f0, sp, 0x128);
    swc1(f0, sp, 0xC4);
    lwc1(f0, sp, 0xF0);
    swc1(f0, sp, 0xC8);
    lwc1(f0, sp, 0xF8);
    swc1(f0, sp, 0xCC);
    lwc1(f0, sp, 0x130);
    swc1(f0, sp, 0xE8);
    swc1(f21, sp, 0xEC);
    a0 = addiu(sp, 0xC0);
    a1 = addiu(sp, 0xC8);
    a2 = addiu(sp, 0xE8);
    a3 = addiu(sp, 0xE0);
    jal(ctx, 0x2E6E1Cu, gen::fn_sub_2D1FD0_002d1fd0);
    lwc1(f2, s0, 144);
    lwc1(f1, s0, 44);
    mul_s(f2, f2, f1);
    mtc1(zero, f1);
    adda_s(f1, f0);
    madd_s(f21, f22, f2);
    lwc1(f0, sp, 0xE0);
    swc1(f0, sp, 0xF0);
    swc1(f20, sp, 0xF4);
    lwc1(f0, sp, 0xE4);
    swc1(f0, sp, 0xF8);
    v0 = 0x3F000000;
    mtc1(v0, f1);
    lwc1(f0, s4, 184);
    mul_s(f1, f1, f0);
    lwc1(f0, gp, -32656);  // 0x7CAD60
    mul_s(f12, f0, f1);
    jal(ctx, 0x2E6E6Cu, gen::fn_tanf_0052e930);
    div_s(f2, f21, f0);
    v0 = 0x42C80000;
    mtc1(v0, f0);
    c_lt_s(f2, f0);
    if (cond(ctx)) {
        // 0x002e6e98
        charge(ctx, 1);
        mov_s(f2, f0);
    }
    // 0x002e6e9c
    charge(ctx, 24);
    lwc1(f0, sp, 0x100);
    mul_s(f3, f0, f2);
    swc1(f3, sp, 0x100);
    lwc1(f0, sp, 0x104);
    mul_s(f1, f0, f2);
    swc1(f1, sp, 0x104);
    lwc1(f0, sp, 0x108);
    mul_s(f2, f0, f2);
    swc1(f2, sp, 0x108);
    lwc1(f0, sp, 0xF0);
    add_s(f0, f0, f3);
    swc1(f0, sp, 0x8C);
    lwc1(f0, sp, 0xF4);
    add_s(f1, f0, f1);
    swc1(f1, sp, 0x90);
    lwc1(f0, sp, 0xF8);
    add_s(f0, f0, f2);
    swc1(f0, sp, 0x94);
    v0 = 0x41B40000;
    mtc1(v0, f0);
    c_lt_s(f1, f0);
    if (cond(ctx)) {
        // 0x002e6efc
        charge(ctx, 1);
        swc1(f0, sp, 0x90);
    }
    // 0x002e6f00
    charge(ctx, 12);
    a0 = addiu(sp, 0x70);
    a1 = addiu(s4, 156);
    jal(ctx, 0x2E6F08u, gen::fn_sub_2A4470_002a4470);
    a0 = addiu(sp, 0x7C);
    a1 = addiu(sp, 0x98);
    jal(ctx, 0x2E6F18u, gen::fn_sub_2D1F30_002d1f30);
    lwc1(f1, gp, -32556);  // 0x7CADC4
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x002e6f4c
        charge(ctx, 1);
        a3 = 51;
    } else {
        // 0x002e6f30
        charge(ctx, 7);
        a0 = addiu(sp, 0x70);
        a1 = addiu(sp, 0x8C);
        jal(ctx, 0x2E6F38u, gen::fn_sub_2A44F0_002a44f0);
        a3 = 3;
    }
    // 0x002e6f50
    charge(ctx, 12);
    v0 = 0x42480000;
    mtc1(v0, f12);
    lw(a0, s4, 224);
    a1 = addiu(s1, 4);
    a2 = addiu(sp, 0x8C);
    jal(ctx, 0x2E6F64u, gen::fn_sub_2A3E80_002a3e80);
    mtc1(zero, f0);
    c_eq_s(f0, f23);
    if (!cond(ctx)) {
        // 0x002e704c
        charge(ctx, 10);
        a0 = s4;
        a1 = addiu(sp, 0x70);
        a2 = addiu(sp, 0x8C);
        a3 = 1;
        jal(ctx, 0x2E705Cu, gen::fn_sub_2A2290_002a2290);
        a0 = s4;
        mov_s(f12, f23);
        jal(ctx, 0x2E706Cu, gen::fn_sub_2A3110_002a3110);
    } else {
        // 0x002e6f80
        charge(ctx, 37);
        a0 = addiu(sp, 0x70);
        a1 = addiu(sp, 0x8C);
        jal(ctx, 0x2E6F88u, gen::fn_sub_2A44F0_002a44f0);
        a0 = addiu(sp, 0x100);
        a1 = 0x690000;
        a1 = addiu(a1, 30880);  // &0x6978A0
        a2 = 1;
        a3 = addiu(sp, 0x7C);
        jal(ctx, 0x2E6FA4u, gen::fn_sub_4BE1E0_004be1e0);
        v0 = 0x43160000;
        mtc1(v0, f2);
        lwc1(f0, sp, 0x100);
        mul_s(f3, f0, f2);
        swc1(f3, sp, 0x100);
        lwc1(f0, sp, 0x104);
        mul_s(f1, f0, f2);
        swc1(f1, sp, 0x104);
        lwc1(f0, sp, 0x108);
        mul_s(f2, f0, f2);
        swc1(f2, sp, 0x108);
        lwc1(f0, sp, 0x70);
        add_s(f0, f0, f3);
        swc1(f0, sp, 0x8C);
        lwc1(f0, sp, 0x74);
        add_s(f1, f0, f1);
        swc1(f1, sp, 0x90);
        lwc1(f0, sp, 0x78);
        add_s(f0, f0, f2);
        swc1(f0, sp, 0x94);
        v0 = 0x41B40000;
        mtc1(v0, f0);
        c_lt_s(f1, f0);
        if (cond(ctx)) {
            // 0x002e7014
            charge(ctx, 1);
            swc1(f0, sp, 0x90);
        }
        // 0x002e7018
        charge(ctx, 13);
        a0 = s4;
        a1 = addiu(sp, 0x70);
        a2 = addiu(sp, 0x8C);
        a3 = 1;
        jal(ctx, 0x2E7028u, gen::fn_sub_2A2290_002a2290);
        v0 = 0x40000000;
        mtc1(v0, f12);
        a0 = s4;
        jal(ctx, 0x2E703Cu, gen::fn_sub_2A3110_002a3110);
    }
    // 0x002e7074 (the shared epilogue, written out on this path)
    charge(ctx, 13);
    ld(ra, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x160);
}

// 0x002E70B0 sub_2E70B0 -- 272 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Battle camera shot selector: clears gBtl+2936, then by the action's side mask and the unit's flags either runs
// sub_2AF960 (setting gBtl+2936 = 1) or the framing shot sub_2E6A20.
void sub_2E70B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x002e70b0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, gp, -18692);  // 0x7CE3EC
    sh(zero, v0, 2936);
    lw(v0, a0, 224);
    lw(s0, v0, 48);
    a0 = addiu(v0, 56);
    jal(ctx, 0x2E70D8u, gen::fn_btlTargetGetSideMask_002d1600);
    a0 = v0 & 0xFFFF;
    lbu(v1, s0, 162);
    if (v1 != 0) {
        // 0x002e7150
        charge(ctx, 4);
        v1 = a0 & 0xFFFF;
        v1 = v1 & 0x2;
        if (v1 == 0) {
            // 0x002e7160
            charge(ctx, 5);
            lw(a0, s0, 2604);
            jal(ctx, 0x2E7164u, gen::fn_sub_30C3A0_0030c3a0);
            if (v0 == 0) {
                // 0x002e7190
                charge(ctx, 6);
                a0 = s1;
                jal(ctx, 0x2E7194u, gen::fn_sub_2AF960_002af960);
                a0 = 1;
                lw(v1, gp, -18692);  // 0x7CE3EC
                sh(a0, v1, 2936);
            } else {
                // 0x002e7174
                charge(ctx, 7);
                v0 = 0x3F800000;
                mtc1(v0, f12);
                a0 = s1;
                jal(ctx, 0x2E7180u, gen::fn_sub_2E6A20_002e6a20);
            }
        }
    } else {
        // 0x002e70f0
        charge(ctx, 4);
        v0 = a0 & 0xFFFF;
        v0 = v0 & 0x1;
        if (v0 != 0) {
            // 0x002e7130
            charge(ctx, 8);
            a0 = s1;
            jal(ctx, 0x2E7134u, gen::fn_sub_2AF960_002af960);
            a0 = 1;
            lw(v1, gp, -18692);  // 0x7CE3EC
            sh(a0, v1, 2936);
        } else {
            // 0x002e7100
            charge(ctx, 5);
            lw(a0, s1, 224);
            jal(ctx, 0x2E7104u, gen::fn_sub_2D5E10_002d5e10);
            if (v0 == 0) {
                // 0x002e7114
                charge(ctx, 7);
                v0 = 0x3F800000;
                mtc1(v0, f12);
                a0 = s1;
                jal(ctx, 0x2E7120u, gen::fn_sub_2E6A20_002e6a20);
            }
        }
    }
    // 0x002e71a8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002FF340 datUnitCreatePc -- 148 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// datUnitCreatePc: allocates a 12-byte DatUnitGenus (kind 0, count 1), points it at datGetUnit($a0) and initialises
// that unit (datUnitInit(unit, 0, id)).
void datUnitCreatePc(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002ff340
    enter(ctx, 37);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    a0 = 12;
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x2FF364u, v0.u());
    s0 = v0;
    a0 = s0;
    a1 = 0;
    a2 = 12;
    jal(ctx, 0x2FF37Cu, gen::fn_memset_00521408);
    sh(zero, s0, 0);
    v0 = 1;
    sh(v0, s0, 2);
    a0 = dsll32(s1, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x2FF398u, gen::fn_datGetUnit_0016cd60);
    sw(v0, s0, 4);
    a0 = v0;
    a1 = 0;
    a2 = s1;
    jal(ctx, 0x2FF3B0u, gen::fn_datUnitInit_002ff890);
    v0 = s0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002FF3E0 datUnitCreateEc -- 348 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// datUnitCreateEc: allocates a 372-byte DatUnitGenus (kind 1) for encounter $a0, counts the encounter's non-zero unit
// ids (gEncountTbl, 28-byte rows, five u16 at +8), and initialises one 60-byte unit per id.
void datUnitCreateEc(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002ff3e0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s0 = 0;
    a0 = 0;
    v1 = s2 & 0xFFFF;
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    s1 = sll(v0, 2);
    lw(v0, gp, -18504);  // gEncountTbl
    v1 = addu(v0, s1);
    for (;;) {
        // 0x002ff44c
        charge(ctx, 4);
        v0 = a0 & 0xFFFF;
        v0 = sltiu(v0, 5);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002ff424
        charge(ctx, 6);
        v0 = a0 & 0xFFFF;
        v0 = sll(v0, 1);
        v0 = addu(v1, v0);
        lhu(v0, v0, 8);
        if (v0 != 0) {
            // 0x002ff43c
            charge(ctx, 2);
            v0 = addiu(s0, 1);
            s0 = v0 & 0xFFFF;
        }
        // 0x002ff444
        charge(ctx, 2);
        v0 = addiu(a0, 1);
        a0 = v0 & 0xFFFF;
    }
    // 0x002ff45c
    charge(ctx, 22);
    a0 = 372;
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x2FF46Cu, v0.u());
    s3 = v0;
    a0 = s3;
    a1 = 0;
    a2 = 372;
    jal(ctx, 0x2FF484u, gen::fn_memset_00521408);
    v0 = 1;
    sh(v0, s3, 0);
    sh(s0, s3, 2);
    sh(s2, s3, 8);
    v0 = addiu(s3, 12);
    sw(v0, s3, 4);
    s2 = 0;
    s0 = 0;
    for (;;) {
        // 0x002ff508
        charge(ctx, 4);
        v0 = s0 & 0xFFFF;
        v0 = sltiu(v0, 5);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002ff4b4
        charge(ctx, 8);
        lw(v0, gp, -18504);  // gEncountTbl
        v1 = addu(s1, v0);
        v0 = s0 & 0xFFFF;
        v0 = sll(v0, 1);
        v0 = addu(v1, v0);
        lhu(a2, v0, 8);
        if (a2 != 0) {
            // 0x002ff4d4
            charge(ctx, 11);
            v1 = s2 & 0xFFFF;
            v0 = sll(v1, 4);
            v0 = subu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s3, 4);
            a0 = addu(v0, v1);
            a1 = 1;
            jal(ctx, 0x2FF4F0u, gen::fn_datUnitInit_002ff890);
            v0 = addiu(s2, 1);
            s2 = v0 & 0xFFFF;
        }
        // 0x002ff500
        charge(ctx, 2);
        v0 = addiu(s0, 1);
        s0 = v0 & 0xFFFF;
    }
    // 0x002ff518
    charge(ctx, 9);
    v0 = s3;
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x002FF760 datUnitDestroyGenus -- 40 bytes; frame 0x10: ra sp+0x0
// datUnitDestroyGenus: frees the genus through the 0x96017C free hook.
void datUnitDestroyGenus(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002ff760
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x2FF770u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003170C0 sub_3170C0 -- 904 bytes; frame 0xA0: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Model instance clone: copies the source model $a0 into $a1 -- the clump (+220/+224 through sub_491CC0 / sub_1A7570),
// the four 156-byte part slots (shared refs at +280 with their counters bumped, the per-part atomics at +268, the
// animation tables at +284 rebuilt in fresh heap blocks), the shared records at +860 / +892 / +1008 and the +1012 /
// +1016 attachments -- then refreshes part 0 (sub_3182D0).
void sub_3170C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003170c0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
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
    lw(a0, a0, 220);
    if (a0 != 0) {
        // 0x003170fc
        charge(ctx, 7);
        jal(ctx, 0x3170FCu, gen::fn_sub_491CC0_00491cc0);
        sw(v0, s4, 220);
        a0 = v0;
        jal(ctx, 0x31710Cu, gen::fn_sub_1A7570_001a7570);
        sw(v0, s4, 224);
    }
    // 0x00317118
    charge(ctx, 3);
    s3 = 0;
    for (;;) {
        // 0x0031732c
        charge(ctx, 3);
        v0 = sltiu(s3, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00317124
        charge(ctx, 6);
        a1 = s3 & 0xFFFF;
        a0 = s5;
        jal(ctx, 0x31712Cu, gen::fn_sub_3185B0_003185b0);
        if (v0 != 0) {
            // 0x0031713c
            charge(ctx, 16);
            v0 = sll(s3, 2);
            v0 = addu(v0, s3);
            v0 = sll(v0, 3);
            v0 = subu(v0, s3);
            a1 = sll(v0, 2);
            a0 = addu(s5, a1);
            lw(v1, a0, 280);
            lhu(v0, v1, 6);
            v0 = addiu(v0, 1);
            sh(v0, v1, 6);
            s0 = addu(s4, a1);
            sw(v1, s0, 280);
            lhu(v0, a0, 236);
            v0 = v0 & 0x2;
            if (v0 != 0) {
                // 0x003171fc
                charge(ctx, 10);
                lhu(v0, s0, 236);
                v0 = v0 | 0x2;
                sh(v0, s0, 236);
                lw(a0, s4, 268);
                lw(a2, a0, 0);
                a1 = 0;
                a3 = si(-1);
                jal(ctx, 0x317218u, gen::fn_sub_466480_00466480);
                sw(v0, s0, 268);
            } else {
                // 0x0031717c
                charge(ctx, 32);
                lw(s0, s4, 220);
                sw(zero, sp, 0x9C);
                lw(a0, s0, 4);
                a1 = 0x310000;
                a1 = addiu(a1, 5536);  // &sub_3115A0
                a2 = addiu(sp, 0x9C);
                jal(ctx, 0x317194u, gen::fn_sub_4CB6E0_004cb6e0);
                v0 = sll(s3, 2);
                v0 = addu(v0, s3);
                v0 = sll(v0, 3);
                v0 = subu(v0, s3);
                v0 = sll(v0, 2);
                v0 = addu(s4, v0);
                s1 = addiu(v0, 268);
                lw(a2, sp, 0x9C);
                sw(a2, v0, 268);
                a0 = s0;
                a1 = 0x310000;
                a1 = addiu(a1, 5648);  // &sub_311610
                jal(ctx, 0x3171CCu, gen::fn_sub_4916D0_004916d0);
                a0 = s0;
                lw(a1, s1, 0);
                jal(ctx, 0x3171DCu, gen::fn_sub_1A7170_001a7170);
                lw(v1, s1, 0);
                lw(v0, v1, 0);
                v0 = v0 | 0x3000;
                sw(v0, v1, 0);
            }
        }
        // 0x00317224
        charge(ctx, 9);
        v0 = sll(s3, 2);
        v0 = addu(v0, s3);
        v0 = sll(v0, 3);
        v0 = subu(v0, s3);
        s7 = sll(v0, 2);
        v0 = addu(s5, s7);
        lw(s0, v0, 284);
        if (s0 != 0) {
            // 0x00317248
            charge(ctx, 27);
            lhu(s6, s0, 0);
            v0 = 52;
            v1 = sll(s6, 2);
            v0 = addu(v0, v1);
            s2 = addu(v0, v1);
            a0 = s2;
            a1 = 0x40000;
            v0 = 0x960000;
            lw(v0, v0, 376);  // 0x960178
            jalr(ctx, 0x31726Cu, v0.u());
            s1 = v0;
            a0 = s1;
            a1 = 0;
            a2 = s2;
            jal(ctx, 0x317284u, gen::fn_memset_00521408);
            v0 = s6 & 0xFFFF;
            sw(v0, s1, 0);
            v1 = addiu(s1, 52);
            sw(v1, s1, 20);
            v0 = sll(v0, 2);
            v0 = addu(v1, v0);
            sw(v0, s1, 32);
            s2 = 0;
            for (;;) {
                // 0x00317310
                charge(ctx, 4);
                lw(v0, s1, 0);
                v0 = sltu(s2, v0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x003172b4
                charge(ctx, 6);
                lw(v0, s0, 20);
                s6 = sll(s2, 2);
                v0 = addu(v0, s6);
                lw(a0, v0, 0);
                if (a0 != 0) {
                    // 0x003172cc
                    charge(ctx, 5);
                    jal(ctx, 0x3172CCu, gen::fn_sub_31D700_0031d700);
                    lw(v1, s1, 20);
                    v1 = addu(v1, s6);
                    sw(v0, v1, 0);
                }
                // 0x003172e0
                charge(ctx, 5);
                lw(v0, s0, 32);
                v0 = addu(v0, s6);
                lw(a0, v0, 0);
                if (a0 != 0) {
                    // 0x003172f4
                    charge(ctx, 6);
                    s6 = sll(s2, 2);
                    jal(ctx, 0x3172F8u, gen::fn_sub_31E0B0_0031e0b0);
                    lw(v1, s1, 32);
                    v1 = addu(v1, s6);
                    sw(v0, v1, 0);
                }
                // 0x0031730c
                charge(ctx, 1);
                s2 = addiu(s2, 1);
            }
            // 0x00317320
            charge(ctx, 2);
            v0 = addu(s4, s7);
            sw(s1, v0, 284);
        }
        // 0x00317328
        charge(ctx, 1);
        s3 = addiu(s3, 1);
    }
    // 0x00317338
    charge(ctx, 3);
    lw(v1, s5, 860);
    if (v1 != 0) {
        // 0x00317344
        charge(ctx, 4);
        lhu(v0, v1, 6);
        v0 = addiu(v0, 1);
        sh(v0, v1, 6);
        sw(v1, s4, 860);
    }
    // 0x00317354
    charge(ctx, 3);
    lw(v1, s5, 892);
    if (v1 != 0) {
        // 0x00317360
        charge(ctx, 10);
        lhu(v0, v1, 14);
        v0 = addiu(v0, 1);
        sh(v0, v1, 14);
        sw(v1, s4, 892);
        a0 = addiu(s4, 868);
        lw(a1, s4, 220);
        jal(ctx, 0x317378u, gen::fn_sub_3143C0_003143c0);
        v0 = 1;
        sb(v0, s4, 870);
    }
    // 0x00317388
    charge(ctx, 3);
    lw(v1, s5, 1008);
    if (v1 != 0) {
        // 0x00317394
        charge(ctx, 4);
        lhu(v0, v1, 2);
        v0 = addiu(v0, 1);
        sh(v0, v1, 2);
        sw(v1, s4, 1008);
    }
    // 0x003173a4
    charge(ctx, 3);
    lw(a0, s5, 1012);
    if (a0 != 0) {
        // 0x003173b0
        charge(ctx, 6);
        jal(ctx, 0x3173B0u, gen::fn_sub_31D700_0031d700);
        sw(v0, s4, 1012);
        a0 = v0;
        jal(ctx, 0x3173C0u, gen::fn_sub_31DED0_0031ded0);
    }
    // 0x003173c8
    charge(ctx, 3);
    lw(v0, s5, 1016);
    if (v0 != 0) {
        // 0x003173d4
        charge(ctx, 4);
        a0 = addiu(s4, 1016);
        a1 = addiu(s5, 1016);
        jal(ctx, 0x3173DCu, gen::fn_sub_31EE80_0031ee80);
    }
    // 0x003173e4
    charge(ctx, 6);
    a0 = s4;
    a1 = 0;
    jal(ctx, 0x3173ECu, gen::fn_sub_3185B0_003185b0);
    if (v0 != 0) {
        // 0x003173fc
        charge(ctx, 7);
        a0 = s4;
        a1 = 0;
        a2 = 0;
        a3 = 0;
        t0 = 1;
        jal(ctx, 0x317410u, gen::fn_sub_3182D0_003182d0);
    }
    // 0x00317418 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0xA0);
}

// 0x0031E8D0 sub_31E8D0 -- 776 bytes; frame 0x190: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Animation slot load into *$a0: for kind 2 (except ids 226..231 / 278..280) builds a 32-byte record and binds three
// 256-byte headed blocks of $a3 through sub_31E310 / sub_109AE0 (flags 8 | 2); for kind 1 copies $a4 bytes of $a3 into
// a fresh heap block (flag 1).
void sub_31E8D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0031e8d0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x190);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    s1 = a2;
    s0 = a3;
    s5 = t0;
    a1 = s2 & 0xFFFF;
    v1 = 2;
    if (a1 == v1) {
        // 0x0031e914
        charge(ctx, 4);
        a0 = s1 & 0xFFFF;
        v1 = 231;
        if (a0 != v1) {
            // 0x0031e924
            charge(ctx, 3);
            v1 = 230;
            if (a0 == v1) {
                goto L_0031e98c;
            }
            // 0x0031e930
            charge(ctx, 3);
            v1 = 229;
            if (a0 == v1) {
                goto L_0031e98c;
            }
            // 0x0031e93c
            charge(ctx, 3);
            v1 = 228;
            if (a0 == v1) {
                goto L_0031e98c;
            }
            // 0x0031e948
            charge(ctx, 3);
            v1 = 227;
            if (a0 == v1) {
                goto L_0031e98c;
            }
            // 0x0031e954
            charge(ctx, 3);
            v1 = 226;
            if (a0 == v1) {
                goto L_0031e98c;
            }
            // 0x0031e960
            charge(ctx, 3);
            v1 = 280;
            if (a0 == v1) {
                goto L_0031e98c;
            }
            // 0x0031e96c
            charge(ctx, 3);
            v1 = 279;
            if (a0 == v1) {
                goto L_0031e98c;
            }
            // 0x0031e978
            charge(ctx, 3);
            v1 = 278;
            if (a0 == v1) {
                goto L_0031e98c;
            }
            // 0x0031e984
            charge(ctx, 2);
            goto L_0031e998;
        }
    L_0031e98c:
        charge(ctx, 3);
        v1 = 1;
        goto L_0031e99c;
    }
L_0031e998:
    charge(ctx, 1);
    v1 = 0;
L_0031e99c:
    charge(ctx, 2);
    if (v1 == 0) {
        // 0x0031e9a4
        charge(ctx, 3);
        lw(a0, s3, 0);
        if (a0 != 0) {
            // 0x0031e9b0
            charge(ctx, 4);
            lhu(v1, a0, 14);
            v1 = v1 & 0x1;
            if (v1 == 0) {
                goto L_0031e9c0;
            }
            // 0x0031ebb0 (the shared epilogue, written out on this path)
            charge(ctx, 10);
            ld(ra, sp, 0x60);
            lq(s5, sp, 0x50);
            lq(s4, sp, 0x40);
            lq(s3, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x190);
            return;
        }
    L_0031e9c0:
        charge(ctx, 3);
        v1 = 2;
        if (a1 == v1) {
            // 0x0031ea8c
            charge(ctx, 2);
            if (a0 == 0) {
                // 0x0031ea94
                charge(ctx, 19);
                a0 = 32;
                a1 = 0x40000;
                v0 = 0x960000;
                lw(v0, v0, 376);  // 0x960178
                jalr(ctx, 0x31EAA4u, v0.u());
                s4 = v0;
                a0 = s4;
                a1 = 0;
                a2 = 32;
                jal(ctx, 0x31EABCu, gen::fn_memset_00521408);
                v0 = 1;
                sw(v0, s4, 4);
                sh(s2, s4, 8);
                sh(s1, s4, 10);
                v0 = 2;
                sh(v0, s4, 12);
                sw(s4, s3, 0);
            }
            // 0x0031eae0
            charge(ctx, 11);
            lw(v0, s3, 0);
            sw(zero, v0, 16);
            a0 = s2;
            a1 = s1;
            jal(ctx, 0x31EAF0u, gen::fn_sub_31E310_0031e310);
            lw(v1, s3, 0);
            sw(v0, v1, 0);
            s1 = 0;
            for (;;) {
                // 0x0031eb5c
                charge(ctx, 3);
                v0 = slti(s1, 3);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0031eb0c
                charge(ctx, 15);
                a0 = addiu(sp, 0x70);
                a1 = s0;
                a2 = 256;
                jal(ctx, 0x31EB18u, gen::fn_memcpy_00521250);
                a0 = addiu(s0, 256);
                v0 = sll(s1, 2);
                v1 = addu(v0, sp);
                sw(a0, v1, 384);
                lw(v0, sp, 0x16C);
                sw(v0, v1, 368);
                v1 = addiu(v0, 63);
                v0 = sra(v1, 6);
                if (i64(v1) < 0) {
                    // 0x0031eb48
                    charge(ctx, 2);
                    v0 = addiu(v1, 63);
                    v0 = sra(v0, 6);
                }
                // 0x0031eb50
                charge(ctx, 3);
                v0 = sll(v0, 6);
                s0 = addu(a0, v0);
                s1 = addiu(s1, 1);
            }
            // 0x0031eb68
            charge(ctx, 18);
            lw(v0, s3, 0);
            lh(a0, v0, 0);
            lw(a1, sp, 0x180);
            lw(a2, sp, 0x170);
            lw(a3, sp, 0x184);
            lw(t0, sp, 0x174);
            lw(t1, sp, 0x188);
            lw(t2, sp, 0x178);
            jal(ctx, 0x31EB88u, gen::fn_sub_109AE0_00109ae0);
            lw(a0, s3, 0);
            lhu(v1, a0, 14);
            v1 = v1 | 0x8;
            sh(v1, a0, 14);
            lw(a0, s3, 0);
            lhu(v1, a0, 14);
            v1 = v1 | 0x2;
            sh(v1, a0, 14);
        } else {
            // 0x0031e9cc
            charge(ctx, 3);
            v1 = 1;
            if (a1 == v1) {
                // 0x0031e9e0
                charge(ctx, 2);
                if (a0 == 0) {
                    // 0x0031e9e8
                    charge(ctx, 18);
                    a0 = 32;
                    a1 = 0x40000;
                    v0 = 0x960000;
                    lw(v0, v0, 376);  // 0x960178
                    jalr(ctx, 0x31E9F8u, v0.u());
                    s4 = v0;
                    a0 = s4;
                    a1 = 0;
                    a2 = 32;
                    jal(ctx, 0x31EA10u, gen::fn_memset_00521408);
                    v0 = 1;
                    sw(v0, s4, 4);
                    sh(s2, s4, 8);
                    sh(s1, s4, 10);
                    sh(v0, s4, 12);
                    sw(s4, s3, 0);
                }
                // 0x0031ea30
                charge(ctx, 23);
                lw(s1, s3, 0);
                a0 = s5;
                a1 = 0x40000;
                v0 = 0x960000;
                lw(v0, v0, 376);  // 0x960178
                jalr(ctx, 0x31EA44u, v0.u());
                sw(v0, s1, 0);
                a0 = v0;
                a1 = s0;
                a2 = s5;
                jal(ctx, 0x31EA5Cu, gen::fn_memcpy_00521250);
                lw(a0, s3, 0);
                lhu(v1, a0, 14);
                v1 = v1 & 0xFFFD;
                sh(v1, a0, 14);
                lw(a0, s3, 0);
                lhu(v1, a0, 14);
                v1 = v1 | 0x1;
                sh(v1, a0, 14);
            } else {
                // 0x0031e9d8
                charge(ctx, 2);
            }
        }
    }
    // 0x0031ebb0 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x190);
}

// 0x00324160 sub_324160 -- 432 bytes; frame 0xA0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Morph mesh update: fetches the target record of $a0 (sub_323C20), refreshes its morph targets (sub_494D50), locks the
// source geometry and copies its vertex triplets ($a0+32 of them) into the target, re-applies each target (sub_493230),
// and unlocks (sub_4933D0); returns the target.
void sub_324160(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x00324160
    enter(ctx, 28);  // entry check point + this block's cycles
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
    lhu(v0, a0, 28);
    lhu(a1, a0, 8);
    lhu(a2, a0, 10);
    a0 = v0;
    lw(a3, s5, 4);
    jal(ctx, 0x3241A4u, gen::fn_sub_323C20_00323c20);
    s7 = v0;
    lw(s6, v0, 40);
    lw(v1, s5, 16);
    lw(s3, v1, 24);
    lw(v0, v0, 16);
    lw(s2, v0, 24);
    s0 = 0;
    for (;;) {
        // 0x00324200
        charge(ctx, 4);
        lh(v0, s5, 28);
        v0 = slt(s0, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003241d0
        charge(ctx, 7);
        v1 = sll(s0, 2);
        lw(v0, s5, 40);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        lw(a1, v0, 0);
        if (a1 != 0) {
            // 0x003241ec
            charge(ctx, 4);
            v0 = addu(s6, v1);
            lw(a0, v0, 0);
            jal(ctx, 0x3241F4u, gen::fn_sub_494D50_00494d50);
        }
        // 0x003241fc
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x00324210
    charge(ctx, 10);
    a0 = s3;
    a1 = 1;
    jal(ctx, 0x324218u, gen::fn_geometryLock_00493370);
    lw(a1, s3, 44);
    lw(a0, s2, 44);
    s1 = a0;
    v1 = 0;
    for (;;) {
        // 0x0032425c
        charge(ctx, 4);
        lh(v0, s5, 32);
        v0 = slt(v1, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00324238
        charge(ctx, 9);
        lhu(v0, a1, 0);
        sh(v0, a0, 0);
        lhu(v0, a1, 2);
        sh(v0, a0, 2);
        lhu(v0, a1, 4);
        sh(v0, a0, 4);
        a1 = addiu(a1, 8);
        a0 = addiu(a0, 8);
        v1 = addiu(v1, 1);
    }
    // 0x0032426c
    charge(ctx, 3);
    s4 = 0;
    for (;;) {
        // 0x003242bc
        charge(ctx, 4);
        lh(v0, s5, 28);
        v0 = slt(s4, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00324278
        charge(ctx, 5);
        s0 = 0;
        v0 = sll(s4, 2);
        fp = addu(s6, v0);
        for (;;) {
            // 0x003242a8
            charge(ctx, 4);
            lh(v0, s5, 10);
            v0 = slt(s0, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0032428c
            charge(ctx, 7);
            a0 = s2;
            a1 = s1;
            lw(a2, fp, 0x0);
            jal(ctx, 0x324298u, gen::fn_sub_493230_00493230);
            s1 = addiu(s1, 8);
            s0 = addiu(s0, 1);
        }
        // 0x003242b8
        charge(ctx, 1);
        s4 = addiu(s4, 1);
    }
    // 0x003242cc
    charge(ctx, 17);
    a0 = s3;
    jal(ctx, 0x3242D0u, gen::fn_sub_4933D0_004933d0);
    v0 = s7;
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

// 0x003A4270 sub_3A4270 -- 68 bytes; frame 0x10: ra sp+0x0
// Forwards entry $a0 of the 52-byte table at 0x959EEC to sub_3A5EA0.
void sub_3A4270(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a4270
    enter(ctx, 17);  // entry check point + this block's cycles
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
    lw(a0, v0, 0);
    jal(ctx, 0x3A429Cu, gen::fn_sub_3A5EA0_003a5ea0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003B55B0 sub_3B55B0 -- 24 bytes; leaf frame (no stack)
// Returns &0x6A2AF0[16 * $a0] (16-byte table entry).
void sub_3B55B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x003b55b0
    enter(ctx, 6);  // entry check point + this block's cycles
    v1 = sll(a0, 4);
    v0 = 0x6A0000;
    v0 = addiu(v0, 10992);  // &0x6A2AF0
    v0 = addu(v0, v1);
}

// 0x003B64C0 sub_3B64C0 -- 272 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Starts an effect of id ($a0 & 0x3FF) | 0x1800 from data $a1 with flag byte $a2 on the active resource manager: binds
// it (sub_34FCD0), sets its scale to (100, 0, 0) and starts it; prints "not found active resmanager" / "invalid efeect
// data!" and returns 0 on failure.
void sub_3B64C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x003b64c0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a1;
    s1 = a2;
    v0 = a0 & 0xFFFF;
    v0 = v0 & 0x3FF;
    v0 = v0 | 0x1800;
    s0 = v0 & 0xFFFF;
    lw(v0, gp, -22448);  // 0x7CD540
    lw(a0, v0, 8);
    if (a0 != 0) {
        // 0x003b651c
        charge(ctx, 2);
        if (s2 != 0) {
            // 0x003b6540
            charge(ctx, 6);
            a1 = s0;
            jal(ctx, 0x3B6544u, gen::fn_sub_3B50D0_003b50d0);
            s3 = v0;
            if (s3 != 0) {
                // 0x003b6564
                charge(ctx, 19);
                a0 = s2;
                jal(ctx, 0x3B6568u, gen::fn_sub_34FCD0_0034fcd0);
                sw(v0, s3, 260);
                sb(s1, s3, 256);
                v0 = 0x42C80000;
                sw(v0, sp, 0x50);
                sw(zero, sp, 0x54);
                sw(zero, sp, 0x58);
                lw(a0, s3, 260);
                a1 = addiu(sp, 0x50);
                jal(ctx, 0x3B6590u, gen::fn_sub_34FDF0_0034fdf0);
                v0 = 0x3FC00000;
                mtc1(v0, f12);
                lw(a0, s3, 260);
                jal(ctx, 0x3B65A4u, gen::fn_sub_34FF70_0034ff70);
                v0 = s0;
            } else {
                // 0x003b6558
                charge(ctx, 3);
                v0 = 0;
            }
        } else {
            // 0x003b6524
            charge(ctx, 7);
            a0 = 0x6A0000;
            a0 = addiu(a0, 11264);  // "invalid efeect data!\n"
            jal(ctx, 0x3B652Cu, gen::fn_printf_005225a8);
            v0 = 0;
        }
    } else {
        // 0x003b6500
        charge(ctx, 7);
        a0 = 0x6A0000;
        a0 = addiu(a0, 11184);  // "not found active resmanager\n"
        jal(ctx, 0x3B6508u, gen::fn_printf_005225a8);
        v0 = 0;
    }
    // 0x003b65b0 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x003B8310 sub_3B8310 -- 136 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Sets / clears bit 3 of the +40 flags of resource entry $a0 (sub_3B5D10) by $a1 == 1; 1 when found.
void sub_3B8310(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b8310
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    jal(ctx, 0x3B8320u, gen::fn_sub_3B5D10_003b5d10);
    if (v0 != 0) {
        // 0x003b833c
        charge(ctx, 2);
        if (v0 != 0) {
            // 0x003b8350
            charge(ctx, 3);
            v1 = 1;
            if (s0 != v1) {
                // 0x003b8370
                charge(ctx, 4);
                lw(a0, v0, 40);
                v1 = si(-9);
                v1 = a0 & v1;
                sw(v1, v0, 40);
            } else {
                // 0x003b835c
                charge(ctx, 5);
                lw(v1, v0, 40);
                v1 = v1 | 0x8;
                sw(v1, v0, 40);
            }
            // 0x003b8380
            charge(ctx, 1);
            v0 = 1;
        } else {
            // 0x003b8344
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x003b8330
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003b8384 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003B8690 sub_3B8690 -- 40 bytes; frame 0x20: ra sp+0x0
// Calls sub_3B8540($a0, $a1, a scratch out word on the stack, $a2).
void sub_3B8690(EEContext& ctx) {
    using namespace hg;
    Gpr a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b8690
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x0);
    a3 = a2;
    a2 = addiu(sp, 0x10);
    jal(ctx, 0x3B86A0u, gen::fn_sub_3B8540_003b8540);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003B87F0 sub_3B87F0 -- 204 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Starts a move of resource entry $a0: flags +40 bit 0 set / bit 6 clear, from = its +4 position, to = the vector $a1,
// duration $a2 at +96, mode byte $a3 at +81, the active byte +80 = 1, timer +92 = 0; 1 when found.
void sub_3B87F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x003b87f0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a1;
    s1 = a2;
    s0 = a3;
    jal(ctx, 0x3B8810u, gen::fn_sub_3B5D10_003b5d10);
    if (v0 != 0) {
        // 0x003b882c
        charge(ctx, 2);
        if (v0 != 0) {
            // 0x003b8840
            charge(ctx, 23);
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
            lwc1(f2, s2, 0);
            lwc1(f1, s2, 4);
            lwc1(f0, s2, 8);
            swc1(f2, v0, 56);
            swc1(f1, v0, 60);
            swc1(f0, v0, 64);
            sw(s1, v0, 96);
            v1 = 1;
            sb(v1, v0, 80);
            sb(s0, v0, 81);
            sw(zero, v0, 92);
        } else {
            // 0x003b8834
            charge(ctx, 3);
            v1 = 0;
        }
        // 0x003b889c
        charge(ctx, 1);
        v0 = v1;
    } else {
        // 0x003b8820
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003b88a0 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003B89F0 sub_3B89F0 -- 112 bytes; frame 0x40: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// Calls sub_3B88C0(entry, $a1, $a2) on resource entry $a0 (sub_3B5D10); 0 when absent.
void sub_3B89F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f20{ctx, 20};
    // 0x003b89f0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s1 = a1;
    mov_s(f20, f12);
    s0 = a2;
    jal(ctx, 0x3B8A10u, gen::fn_sub_3B5D10_003b5d10);
    if (v0 == 0) {
        // 0x003b8a40
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003b8a20
        charge(ctx, 8);
        a0 = v0;
        a1 = s1;
        mov_s(f12, f20);
        a2 = s0;
        jal(ctx, 0x3B8A30u, gen::fn_sub_3B88C0_003b88c0);
    }
    // 0x003b8a44 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003B8E10 sub_3B8E10 -- 112 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Calls sub_3B8CE0(entry, $a1, $a2, $a3) on resource entry $a0 (sub_3B5D10); 0 when absent.
void sub_3B8E10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b8e10
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a1;
    s1 = a2;
    s0 = a3;
    jal(ctx, 0x3B8E30u, gen::fn_sub_3B5D10_003b5d10);
    if (v0 == 0) {
        // 0x003b8e60
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003b8e40
        charge(ctx, 8);
        a0 = v0;
        a1 = s2;
        a2 = s1;
        a3 = s0;
        jal(ctx, 0x3B8E50u, gen::fn_sub_3B8CE0_003b8ce0);
    }
    // 0x003b8e64 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003B8F30 sub_3B8F30 -- 192 bytes; frame 0x10: ra sp+0x0
// Stops resource entry $a0: clears bits 0, 2, 6, 10..15 of its +40 flags one by one; 1 when found.
void sub_3B8F30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b8f30
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x3B8F38u, gen::fn_sub_3B5D10_003b5d10);
    if (v0 != 0) {
        // 0x003b8f54
        charge(ctx, 2);
        if (v0 != 0) {
            // 0x003b8f68
            charge(ctx, 30);
            lw(a0, v0, 40);
            v1 = si(-2);
            a0 = a0 & v1;
            sw(a0, v0, 40);
            v1 = si(-5);
            a0 = a0 & v1;
            sw(a0, v0, 40);
            v1 = lui(0xFFFF);
            v1 = v1 | 0x7FFF;
            a0 = a0 & v1;
            sw(a0, v0, 40);
            v1 = si(-65);
            a0 = a0 & v1;
            sw(a0, v0, 40);
            v1 = si(-1025);
            a0 = a0 & v1;
            sw(a0, v0, 40);
            v1 = si(-2049);
            a0 = a0 & v1;
            sw(a0, v0, 40);
            v1 = si(-4097);
            a0 = a0 & v1;
            sw(a0, v0, 40);
            v1 = si(-8193);
            a0 = a0 & v1;
            sw(a0, v0, 40);
            v1 = si(-16385);
            v1 = a0 & v1;
            sw(v1, v0, 40);
            v0 = 1;
        } else {
            // 0x003b8f5c
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x003b8f48
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003b8fe0 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003B95A0 sub_3B95A0 -- 104 bytes; frame 0x10: ra sp+0x0
// True when resource entry $a0 exists and its +40 bit 0 (moving) is set.
void sub_3B95A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b95a0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x3B95A8u, gen::fn_sub_3B5D10_003b5d10);
    if (v0 != 0) {
        // 0x003b95c4
        charge(ctx, 2);
        if (v0 != 0) {
            // 0x003b95d8
            charge(ctx, 4);
            lw(v0, v0, 40);
            v0 = v0 & 0x1;
            if (v0 == 0) {
                // 0x003b95f4
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x003b95e8
                charge(ctx, 3);
                v0 = 1;
            }
        } else {
            // 0x003b95cc
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x003b95b8
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003b95f8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003BB280 sub_3BB280 -- 180 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Selects resource entry $a0 when its type (+0 bits 10..15) is 7: clears +264 on every entry of the kind list
// (sub_3B5D50, linked by +248) and sets it on this one; 1 when done.
void sub_3BB280(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003bb280
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x3BB28Cu, gen::fn_sub_3B5D10_003b5d10);
    s0 = v0;
    if (s0 != 0) {
        // 0x003bb2ac
        charge(ctx, 2);
        if (s0 != 0) {
            // 0x003bb2c0
            charge(ctx, 8);
            lhu(v1, s0, 0);
            v0 = 0xF0000;
            v0 = v0 | 0xFC00;
            v0 = v1 & v0;
            v0 = sra(v0, 10);
            a0 = 7;
            if (v0 == a0) {
                // 0x003bb2ec
                charge(ctx, 4);
                jal(ctx, 0x3BB2ECu, gen::fn_sub_3B5D50_003b5d50);
                for (;;) {
                    // 0x003bb304
                    charge(ctx, 5);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x003bb2fc
                    charge(ctx, 2);
                    sw(zero, v0, 264);
                    lw(v0, v0, 248);
                }
                // 0x003bb318
                charge(ctx, 2);
                v0 = 1;
                sw(v0, s0, 264);
            } else {
                // 0x003bb2e0
                charge(ctx, 3);
                v0 = 0;
            }
        } else {
            // 0x003bb2b4
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x003bb2a0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003bb320 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003BB400 sub_3BB400 -- 80 bytes; frame 0x10: ra sp+0x0
// For a handle of type 7 ($a0 bits 10..15): clears the entry's +268 halfword and +260 word.
void sub_3BB400(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003bb400
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a1 = a0 & 0xFFFF;
    v1 = 0xF0000;
    v1 = v1 | 0xFC00;
    v1 = a1 & v1;
    a1 = sra(v1, 10);
    v1 = 7;
    if (a1 == v1) {
        // 0x003bb428
        charge(ctx, 4);
        jal(ctx, 0x3BB428u, gen::fn_sub_3B5D10_003b5d10);
        if (v0 != 0) {
            // 0x003bb438
            charge(ctx, 2);
            sh(zero, v0, 268);
            sw(zero, v0, 260);
        }
    }
    // 0x003bb440 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003BD880 sub_3BD880 -- 16 bytes; leaf frame (no stack)
// Returns &0x95B658.
void sub_3BD880(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x003bd880
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0x960000;
    v0 = addiu(v0, -18856);  // &0x95B658
}

// 0x003BD8B0 sub_3BD8B0 -- 236 bytes; leaf frame (no stack)
// Looks up (id $a0, sub $a1, variant $a2) in the 6-byte table at *0x95B71C (count *0x95B720; variant 255 = any) and
// returns its byte +4; else 0 for ids below 500 or in 990..999, -1 otherwise.
void sub_3BD8B0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11};
    // 0x003bd8b0
    enter(ctx, 8);  // entry check point + this block's cycles
    t3 = 0;
    v0 = 0x960000;
    lw(t2, v0, -18660);  // 0x95B71C
    v0 = 0x960000;
    lw(t1, v0, -18656);  // 0x95B720
    v1 = 255;
    for (;;) {
        // 0x003bd940
        charge(ctx, 3);
        v0 = slt(t3, t1);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003bd8d0
        charge(ctx, 7);
        v0 = sll(t3, 1);
        v0 = addu(v0, t3);
        v0 = sll(v0, 1);
        t0 = addu(t2, v0);
        lbu(a3, t0, 3);
        if (a3 == v1) {
            // 0x003bd8ec
            charge(ctx, 3);
            lhu(v0, t0, 0);
            if (a0 != v0) {
                goto L_003bd93c;
            }
            // 0x003bd8f8
            charge(ctx, 3);
            lbu(v0, t0, 2);
            if (a1 != v0) {
                goto L_003bd93c;
            }
            goto L_003bd904_4;
        }
        // 0x003bd910
        charge(ctx, 3);
        lhu(v0, t0, 0);
        if (a0 != v0) {
        L_003bd93c:
            charge(ctx, 1);
            t3 = addiu(t3, 1);
            continue;
        }
        // 0x003bd91c
        charge(ctx, 3);
        lbu(v0, t0, 2);
        if (a1 != v0) {
            goto L_003bd93c;
        }
        // 0x003bd928
        charge(ctx, 2);
        if (a2 != a3) {
            goto L_003bd93c;
        }
        goto L_003bd930_8;
    }
    // 0x003bd94c
    charge(ctx, 2);
    if (i64(a0) >= 0) {
        // 0x003bd954
        charge(ctx, 3);
        at = slti(a0, 500);
        if (at == 0) {
            goto L_003bd96c;
        }
        // 0x003bd960
        charge(ctx, 3);
        v0 = 0;
        // 0x003bd994 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_003bd96c:
    charge(ctx, 3);
    v0 = slti(a0, 990);
    if (v0 == 0) {
        // 0x003bd978
        charge(ctx, 3);
        at = slti(a0, 1000);
        if (at == 0) {
            goto L_003bd990;
        }
        // 0x003bd984
        charge(ctx, 3);
        v0 = 0;
        // 0x003bd994 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_003bd990:
    charge(ctx, 1);
    v0 = si(-1);
    // 0x003bd994 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_003bd904_4:
    charge(ctx, 3);
    lbu(v0, t0, 4);
    // 0x003bd994 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_003bd930_8:
    charge(ctx, 3);
    lbu(v0, t0, 4);
    // 0x003bd994 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x003BE8E0 sub_3BE8E0 -- 320 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Community-rank status (comuFunction.c): for social link $a0 (< 30) picks the status 0..5 (rank 10 = 5, sub_172160 =
// 4, sub_1717C0 = 3, sub_172660 with sub_3BE1C0 = 2 / 1) and shows it with sub_3BE2A0(0, 0, link, status, $a1). Returns
// 1.
void sub_3BE8E0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003be8e0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    at = slti(s2, 30);
    if (at != 0) {
        // 0x003be908
        charge(ctx, 2);
        if (i64(s2) < 0) {
            goto L_003be910;
        }
        goto L_003be924;
    }
L_003be910:
    charge(ctx, 5);
    a0 = 0x6A0000;
    a0 = addiu(a0, 12928);  // "comuFunction.c"
    a1 = 1000;
    jal(ctx, 0x3BE91Cu, gen::fn_sub_19D3F0_0019d3f0);
L_003be924:
    charge(ctx, 9);
    a0 = dsll32(s2, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x3BE92Cu, gen::fn_sub_16DBA0_0016dba0);
    s0 = dsll32(v0, 24);
    s0 = dsra32(s0, 24);
    v0 = 10;
    if (s0 != v0) {
        // 0x003be954
        charge(ctx, 6);
        a0 = s2;
        jal(ctx, 0x3BE958u, gen::fn_sub_172160_00172160);
        v1 = 1;
        if (v0 != v1) {
            // 0x003be978
            charge(ctx, 6);
            a0 = s2;
            jal(ctx, 0x3BE97Cu, gen::fn_sub_1717C0_001717c0);
            v1 = 1;
            if (v0 != v1) {
                // 0x003be99c
                charge(ctx, 6);
                a0 = s2;
                jal(ctx, 0x3BE9A0u, gen::fn_sub_172660_00172660);
                v1 = 1;
                if (v0 != v1) {
                    // 0x003be9e4
                    charge(ctx, 1);
                    a3 = 0;
                } else {
                    // 0x003be9b4
                    charge(ctx, 7);
                    a1 = addiu(s0, 1);
                    a0 = s2;
                    jal(ctx, 0x3BE9BCu, gen::fn_sub_3BE1C0_003be1c0);
                    a3 = 1;
                    if (v0 != a3) {
                        // 0x003be9dc
                        charge(ctx, 2);
                    } else {
                        // 0x003be9d0
                        charge(ctx, 3);
                        a3 = 2;
                    }
                }
            } else {
                // 0x003be990
                charge(ctx, 3);
                a3 = 3;
            }
        } else {
            // 0x003be96c
            charge(ctx, 3);
            a3 = 4;
        }
    } else {
        // 0x003be948
        charge(ctx, 3);
        a3 = 5;
    }
    // 0x003be9e8
    charge(ctx, 14);
    a0 = 0;
    a1 = 0;
    a2 = s2;
    t0 = s1;
    jal(ctx, 0x3BE9F8u, gen::fn_sub_3BE2A0_003be2a0);
    v0 = 1;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003C7E50 sub_3C7E50 -- 984 bytes; frame 0x110: ra sp+0xB0, fp sp+0xA0 (sq), s7 sp+0x90 (sq), s6 sp+0x80 (sq), s5 sp+0x70 (sq), s4 sp+0x60 (sq), s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f20 sp+0x10
// Message display by kind $a6 (0..2) and id $a7: resolves the message bank (0x6A3E50 table) and index through
// sub_171250 / sub_171060 / sub_16F630 / sub_16F900, checks the counts with itfMesMngGetMessageCount, and shows it with
// sub_3A56F0 (two-part) or sub_3A5570. Returns 0.
void sub_3C7E50(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f20{ctx, 20};
    // 0x003c7e50
    enter(ctx, 24);  // entry check point + this block's cycles
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
    swc1(f20, sp, 0x10);
    s5 = a0;
    s4 = a1;
    mov_s(f20, f12);
    s3 = a2;
    s2 = a3;
    s1 = t0;
    s7 = t1;
    s0 = t3;
    a2 = 0x6A0000;
    a2 = addiu(a2, 16016);  // &0x6A3E90
    a1 = addiu(sp, 0xF0);
    a0 = 3;
    for (;;) {
        // 0x003c7eb0
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
    // 0x003c7ed4
    charge(ctx, 4);
    a1 = 0x6A0000;
    a1 = addiu(a1, 16048);  // &0x6A3EB0
    a0 = addiu(sp, 0xC0);
    v1 = 9;
    for (;;) {
        // 0x003c7ee4
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
    // 0x003c7f00
    charge(ctx, 3);
    v0 = 2;
    if (t2 == v0) {
        // 0x003c8060
        charge(ctx, 29);
        a0 = 1;
        a1 = s0;
        jal(ctx, 0x3C8068u, gen::fn_sub_16F630_0016f630);
        s6 = v0 & 0xFFFF;
        a0 = dsll32(s6, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x3C807Cu, gen::fn_sub_171250_00171250);
        v0 = sll(v0, 2);
        v0 = addu(v0, sp);
        lw(v0, v0, 240);
        v1 = sll(v0, 2);
        v0 = 0x6A0000;
        v0 = addiu(v0, 15952);  // &0x6A3E50
        v0 = addu(v0, v1);
        lw(s7, v0, 0);
        a0 = dsll32(s6, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x3C80ACu, gen::fn_sub_171060_00171060);
        s6 = dsll32(v0, 16);
        s6 = dsra32(s6, 16);
        a0 = s7;
        jal(ctx, 0x3C80C0u, gen::fn_itfMesMngGetMessageCount_003a51a0);
        at = sltu(v0, s6);
        if (at == 0) {
            // 0x003c80e0
            charge(ctx, 13);
            v0 = 0x6A0000;
            lw(a0, v0, 15968);  // 0x6A3E60
            jal(ctx, 0x3C80E8u, gen::fn_itfMesMngGetMessageCount_003a51a0);
            fp = v0;
            a0 = 1;
            a1 = s0;
            jal(ctx, 0x3C80FCu, gen::fn_sub_16F900_0016f900);
            v0 = v0 & 0xFF;
            at = sltu(fp, v0);
            if (at == 0) {
                // 0x003c8120
                charge(ctx, 23);
                a0 = 1;
                a1 = s0;
                jal(ctx, 0x3C8128u, gen::fn_sub_16F900_0016f900);
                v1 = v0 & 0xFF;
                v0 = 0x6A0000;
                lw(v0, v0, 15968);  // 0x6A3E60
                sd(v0, sp, 0x0);
                sd(v1, sp, 0x8);
                a0 = s5;
                a1 = s4;
                mov_s(f12, f20);
                a2 = s3;
                a3 = s2;
                t0 = s1;
                t1 = 1;
                t2 = s7;
                t3 = s6;
                jal(ctx, 0x3C8168u, gen::fn_sub_3A56F0_003a56f0);
                v0 = 0;
            } else {
                // 0x003c8114
                charge(ctx, 3);
                v0 = 0;
            }
        } else {
            // 0x003c80d4
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x003c7f0c
        charge(ctx, 3);
        v0 = 1;
        if (t2 == v0) {
            // 0x003c7f7c
            charge(ctx, 25);
            s6 = s0 & 0xFFFF;
            a0 = dsll32(s6, 16);
            a0 = dsra32(a0, 16);
            jal(ctx, 0x3C7F88u, gen::fn_sub_171250_00171250);
            v0 = sll(v0, 2);
            v0 = addu(v0, sp);
            lw(v0, v0, 240);
            v1 = sll(v0, 2);
            v0 = 0x6A0000;
            v0 = addiu(v0, 15952);  // &0x6A3E50
            v0 = addu(v0, v1);
            lw(s7, v0, 0);
            a0 = dsll32(s6, 16);
            a0 = dsra32(a0, 16);
            jal(ctx, 0x3C7FB8u, gen::fn_sub_171060_00171060);
            s6 = dsll32(v0, 16);
            s6 = dsra32(s6, 16);
            a0 = s7;
            jal(ctx, 0x3C7FCCu, gen::fn_itfMesMngGetMessageCount_003a51a0);
            at = sltu(v0, s6);
            if (at == 0) {
                // 0x003c7fec
                charge(ctx, 8);
                s0 = sra(s0, 16);
                v0 = 0x6A0000;
                lw(a0, v0, 15968);  // 0x6A3E60
                jal(ctx, 0x3C7FF8u, gen::fn_itfMesMngGetMessageCount_003a51a0);
                at = sltu(v0, s0);
                if (at == 0) {
                    // 0x003c8018
                    charge(ctx, 18);
                    v0 = 0x6A0000;
                    lw(v0, v0, 15968);  // 0x6A3E60
                    sd(v0, sp, 0x0);
                    sd(s0, sp, 0x8);
                    a0 = s5;
                    a1 = s4;
                    mov_s(f12, f20);
                    a2 = s3;
                    a3 = s2;
                    t0 = s1;
                    t1 = 1;
                    t2 = s7;
                    t3 = s6;
                    jal(ctx, 0x3C804Cu, gen::fn_sub_3A56F0_003a56f0);
                    v0 = 0;
                } else {
                    // 0x003c800c
                    charge(ctx, 3);
                    v0 = 0;
                }
            } else {
                // 0x003c7fe0
                charge(ctx, 3);
                v0 = 0;
            }
        } else {
            // 0x003c7f18
            charge(ctx, 2);
            if (t2 == 0) {
                // 0x003c7f28
                charge(ctx, 3);
                v0 = slti(s0, 5000);
                if (v0 != 0) {
                    // 0x003c7f40
                    charge(ctx, 4);
                    a0 = dsll32(s0, 16);
                    a0 = dsra32(a0, 16);
                    jal(ctx, 0x3C7F48u, gen::fn_sub_171250_00171250);
                } else {
                    // 0x003c7f34
                    charge(ctx, 3);
                    v0 = 5;
                }
                // 0x003c7f50
                charge(ctx, 11);
                v0 = sll(v0, 2);
                v0 = addu(v0, sp);
                lw(s6, v0, 240);
                a0 = dsll32(s0, 16);
                a0 = dsra32(a0, 16);
                jal(ctx, 0x3C7F64u, gen::fn_sub_171060_00171060);
                s0 = dsll32(v0, 16);
                s0 = dsra32(s0, 16);
            } else {
                // 0x003c7f20
                charge(ctx, 2);
                // 0x003c817c
                charge(ctx, 3);
                v0 = sll(t2, 2);
                v0 = addu(v0, sp);
                lw(s6, v0, 192);
            }
            // 0x003c8188
            charge(ctx, 11);
            v1 = sll(s6, 2);
            v0 = 0x6A0000;
            v0 = addiu(v0, 15952);  // &0x6A3E50
            v0 = addu(v0, v1);
            lw(s6, v0, 0);
            a0 = s6;
            jal(ctx, 0x3C81A0u, gen::fn_itfMesMngGetMessageCount_003a51a0);
            at = sltu(v0, s0);
            if (at == 0) {
                // 0x003c81c0
                charge(ctx, 12);
                a0 = s5;
                a1 = s4;
                mov_s(f12, f20);
                a2 = s3;
                a3 = s2;
                t0 = s1;
                t1 = s7;
                t2 = s6;
                t3 = s0;
                jal(ctx, 0x3C81E4u, gen::fn_sub_3A5570_003a5570);
                v0 = 0;
            } else {
                // 0x003c81b4
                charge(ctx, 3);
                v0 = 0;
            }
        }
    }
    // 0x003c81f0 (the shared epilogue, written out on this path)
    charge(ctx, 14);
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
    lwc1(f20, sp, 0x10);
    sp = addiu(sp, 0x110);
}

// 0x003CB050 sub_3CB050 -- 172 bytes; frame 0x10: ra sp+0x0
// List draw callback: calls sub_3CA780 at the row position ($a1 + 4 * (row - first) or $a1 - 4 * first by $a3), colour
// byte $t3+18 | ~0xFF, $t0 + 2, and $t3+216.
void sub_3CB050(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15};
    // 0x003cb050
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a3 != 0) {
        // 0x003cb0a8
        charge(ctx, 17);
        v0 = subu(t2, t1);
        v0 = sll(v0, 2);
        a1 = addu(a1, v0);
        mtc1(zero, f12);
        lh(v1, t3, 18);
        v0 = si(-256);
        a2 = v1 | v0;
        a3 = addiu(t0, 2);
        v0 = 0x3F800000;
        mtc1(v0, f14);
        t0 = 0;
        t1 = 0;
        mov_s(f13, f12);
        mov_s(f15, f14);
        lw(t2, t3, 216);
        jal(ctx, 0x3CB0E4u, gen::fn_sub_3CA780_003ca780);
    } else {
        // 0x003cb060
        charge(ctx, 18);
        v0 = sll(t1, 2);
        a1 = subu(a1, v0);
        mtc1(zero, f12);
        lh(v1, t3, 18);
        v0 = si(-256);
        a2 = v1 | v0;
        a3 = addiu(t0, 2);
        v0 = 0x3F800000;
        mtc1(v0, f14);
        t0 = 0;
        t1 = 0;
        mov_s(f13, f12);
        mov_s(f15, f14);
        lw(t2, t3, 216);
        jal(ctx, 0x3CB098u, gen::fn_sub_3CA780_003ca780);
    }
    // 0x003cb0ec (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003E0A10 sub_3E0A10 -- 340 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Facility screen close: clears flag 5127 when flag 4639 is set, runs sub_40E360, stops the screen by its kind
// (sub_3C7DD0 / sub_3B5AB0), frees its H_Cdvd requests (+88 or the two at +96 / +104), and releases +152 (sub_3DFF00).
void sub_3E0A10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003e0a10
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x3E0A28u, gen::fn_nmObjPayloadWord12_003c5460);
    s0 = v0;
    a0 = 4639;
    jal(ctx, 0x3E0A38u, gen::fn_datGetFlag_0016f190);
    v1 = 1;
    if (v0 == v1) {
        // 0x003e0a4c
        charge(ctx, 4);
        a0 = 5127;
        a1 = 0;
        jal(ctx, 0x3E0A54u, gen::fn_datSetFlag_0016f1f0);
    }
    // 0x003e0a5c
    charge(ctx, 6);
    jal(ctx, 0x3E0A5Cu, gen::fn_sub_40E360_0040e360);
    lw(v1, s0, 0);
    a0 = 8;
    if (v1 == a0) {
        // 0x003e0ab8
        charge(ctx, 5);
        jal(ctx, 0x3E0AB8u, gen::fn_sub_3C7DD0_003c7dd0);
        a0 = 9;
        jal(ctx, 0x3E0AC4u, gen::fn_sub_3C7DD0_003c7dd0);
    } else {
        // 0x003e0a74
        charge(ctx, 3);
        v0 = 4;
        if (v1 != v0) {
            // 0x003e0a80
            charge(ctx, 3);
            v0 = 2;
            if (v1 == v0) {
                goto L_003e0aa8;
            }
            // 0x003e0a8c
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                goto L_003e0aa8;
            }
            // 0x003e0a98
            charge(ctx, 2);
            if (v1 == 0) {
                goto L_003e0aa8;
            }
            // 0x003e0aa0
            charge(ctx, 2);
            goto L_003e0acc;
        }
    L_003e0aa8:
        charge(ctx, 4);
        jal(ctx, 0x3E0AA8u, gen::fn_sub_3B5AB0_003b5ab0);
    }
L_003e0acc:
    charge(ctx, 5);
    jal(ctx, 0x3E0ACCu, gen::fn_sub_3C77A0_003c77a0);
    lw(a0, s0, 88);
    if (a0 == 0) {
        // 0x003e0af4
        charge(ctx, 3);
        s3 = 0;
        for (;;) {
            // 0x003e0b2c
            charge(ctx, 3);
            v0 = slti(s3, 2);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003e0b00
            charge(ctx, 6);
            v0 = sll(s3, 3);
            s2 = addu(s0, v0);
            s1 = addiu(s2, 96);
            lw(a0, s2, 96);
            if (a0 != 0) {
                // 0x003e0b18
                charge(ctx, 4);
                jal(ctx, 0x3E0B18u, gen::fn_H_Cdvd_Destroy_00100ec0);
                sw(zero, s1, 0);
                sw(zero, s2, 100);
            }
            // 0x003e0b28
            charge(ctx, 1);
            s3 = addiu(s3, 1);
        }
    } else {
        // 0x003e0ae0
        charge(ctx, 5);
        jal(ctx, 0x3E0AE0u, gen::fn_H_Cdvd_Destroy_00100ec0);
        sw(zero, s0, 88);
    }
    // 0x003e0b38
    charge(ctx, 11);
    lw(a0, s0, 152);
    jal(ctx, 0x3E0B3Cu, gen::fn_sub_3DFF00_003dff00);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x003F4DE0 sub_3F4DE0 -- 2000 bytes; frame 0x230: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// Facility menu panel draw callback (cmd-list $a3): picks the alpha from nmCmdListStatus28 (255 / $a2), then draws the
// panel by its layout kind (+6 of the layout at +36 -> +68: -5 .. ) through sub_3F4A90, the sprite helper sub_40E3F0
// and the panel painters sub_3F7390 / sub_3F7A80 / sub_3F7890 / sub_3F6F20 / sub_3F7C60 / sub_3F67E0.
void sub_3F4DE0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15}, f20{ctx, 20};
    // 0x003f4de0
    enter(ctx, 31);  // entry check point + this block's cycles
    sp = addiu(sp, -0x230);
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
    s4 = a1;
    s7 = a2;
    s3 = a3;
    s2 = 0;
    lw(s1, a3, 12);
    lw(v0, a3, 36);
    lw(s0, v0, 68);
    s6 = addiu(s0, 40);
    lh(v0, s0, 40);
    s5 = addu(s5, v0);
    lh(v0, s0, 42);
    s4 = addu(s4, v0);
    a0 = s3;
    jal(ctx, 0x3F4E48u, gen::fn_nmCmdListStatus28_003c6e10);
    v1 = 1;
    if (v0 == v1) {
        // 0x003f4e94
        charge(ctx, 1);
        s2 = 255;
    } else {
        // 0x003f4e5c
        charge(ctx, 3);
        v1 = 20;
        if (v0 == v1) {
            // 0x003f4e88
            charge(ctx, 3);
            s2 = s7;
        } else {
            // 0x003f4e68
            charge(ctx, 3);
            v1 = 12;
            if (v0 == v1) {
                // 0x003f4e7c
                charge(ctx, 3);
                s2 = 255;
            } else {
                // 0x003f4e74
                charge(ctx, 2);
            }
        }
    }
    // 0x003f4e98
    charge(ctx, 4);
    lh(v1, s0, 6);
    v0 = si(-5);
    if (v1 == v0) {
        // 0x003f530c
        charge(ctx, 12);
        a0 = s5;
        a1 = s4;
        a2 = s2;
        a3 = 3;
        t0 = s3;
        t1 = s6;
        jal(ctx, 0x3F5324u, gen::fn_sub_3F4A90_003f4a90);
        a1 = 0x6B0000;
        a1 = addiu(a1, -4448);  // &0x6AEEA0
        a0 = addiu(sp, 0x130);
        v1 = 15;
        for (;;) {
            // 0x003f533c
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
        // 0x003f5358
        charge(ctx, 47);
        lh(v0, s0, 72);
        s1 = addu(s5, v0);
        lh(v0, s0, 74);
        s4 = addu(s4, v0);
        lh(v0, s0, 84);
        mult(v1, s2, v0);
        v0 = 255;
        div(v1, v0);
        mflo(s2);
        lwc1(f20, s0, 80);
        lw(v0, s3, 36);
        lw(s0, v0, 40);
        mtc1(zero, f12);
        a2 = s2 & 0xFF;
        lw(a3, sp, 0x154);
        v0 = 0x3F800000;
        mtc1(v0, f14);
        a0 = s1;
        a1 = s4;
        t0 = 0;
        t1 = 0;
        t2 = 0;
        mov_s(f13, f12);
        mov_s(f15, f20);
        jal(ctx, 0x3F53B8u, gen::fn_sub_40E3F0_0040e3f0);
        lw(v0, sp, 0x15C);
        mult(v1, v0, s0);
        v0 = 0xFFFF;
        div(v1, v0);
        mflo(v0);
        a1 = addu(s4, v0);
        mtc1(zero, f12);
        a2 = s2 & 0xFF;
        lw(a3, sp, 0x158);
        v0 = 0x3F800000;
        mtc1(v0, f14);
        a0 = s1;
        t0 = 0;
        t1 = 0;
        t2 = 0;
        mov_s(f13, f12);
        mov_s(f15, f20);
        jal(ctx, 0x3F5404u, gen::fn_sub_40E3F0_0040e3f0);
    } else {
        // 0x003f4ea8
        charge(ctx, 3);
        v0 = si(-4);
        if (v1 == v0) {
            // 0x003f51a4
            charge(ctx, 12);
            a0 = s5;
            a1 = s4;
            a2 = s2;
            a3 = 2;
            t0 = s3;
            t1 = s6;
            jal(ctx, 0x3F51BCu, gen::fn_sub_3F4A90_003f4a90);
            a1 = 0x6B0000;
            a1 = addiu(a1, -4448);  // &0x6AEEA0
            a0 = addiu(sp, 0x170);
            v1 = 15;
            for (;;) {
                // 0x003f51d4
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
            // 0x003f51f0
            charge(ctx, 71);
            lh(v0, s0, 72);
            fp = addu(s5, v0);
            lh(v0, s0, 74);
            v0 = addu(s4, v0);
            sq(v0, sp, 0xC0);
            lh(v0, s0, 84);
            mult(v1, s2, v0);
            v0 = 255;
            div(v1, v0);
            mflo(s2);
            lwc1(f20, s0, 80);
            lw(v0, s3, 36);
            lw(s0, v0, 40);
            mtc1(zero, f12);
            a2 = s2 & 0xFF;
            lw(a3, sp, 0x188);
            v0 = 0x3F800000;
            mtc1(v0, f14);
            a0 = fp;
            lq(a1, sp, 0xC0);
            t0 = 0;
            t1 = 0;
            t2 = 0;
            mov_s(f13, f12);
            mov_s(f15, f20);
            jal(ctx, 0x3F5254u, gen::fn_sub_40E3F0_0040e3f0);
            lw(v0, sp, 0x190);
            mult(v1, v0, s0);
            v0 = 0xFFFF;
            div(v1, v0);
            mflo(v1);
            lq(v0, sp, 0xC0);
            a1 = addu(v0, v1);
            mtc1(zero, f12);
            a2 = s2 & 0xFF;
            lw(a3, sp, 0x18C);
            v0 = 0x3F800000;
            mtc1(v0, f14);
            a0 = fp;
            t0 = 0;
            t1 = 0;
            t2 = 0;
            mov_s(f13, f12);
            mov_s(f15, f20);
            jal(ctx, 0x3F52A4u, gen::fn_sub_40E3F0_0040e3f0);
            a0 = addiu(s5, 345);
            a1 = addiu(s4, 95);
            lh(a2, s6, 12);
            a3 = s3;
            t0 = s1;
            jal(ctx, 0x3F52C0u, gen::fn_sub_3F6F20_003f6f20);
            a0 = addiu(s5, 246);
            a1 = addiu(s4, 200);
            a2 = s7;
            a3 = s3;
            t0 = s1;
            jal(ctx, 0x3F52DCu, gen::fn_sub_3F7C60_003f7c60);
            a1 = addiu(s4, 40);
            lh(a2, s6, 12);
            a0 = s5;
            a3 = 0;
            t0 = s3;
            t1 = s1;
            jal(ctx, 0x3F52FCu, gen::fn_sub_3F7890_003f7890);
        } else {
            // 0x003f4eb4
            charge(ctx, 3);
            v0 = si(-3);
            if (v1 == v0) {
                // 0x003f503c
                charge(ctx, 12);
                a0 = s5;
                a1 = s4;
                a2 = s2;
                a3 = 1;
                t0 = s3;
                t1 = s6;
                jal(ctx, 0x3F5054u, gen::fn_sub_3F4A90_003f4a90);
                a1 = 0x6B0000;
                a1 = addiu(a1, -4448);  // &0x6AEEA0
                a0 = addiu(sp, 0x1B0);
                v1 = 15;
                for (;;) {
                    // 0x003f506c
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
                // 0x003f5088
                charge(ctx, 71);
                lh(v0, s0, 72);
                fp = addu(s5, v0);
                lh(v0, s0, 74);
                v0 = addu(s4, v0);
                sq(v0, sp, 0xD0);
                lh(v0, s0, 84);
                mult(v1, s2, v0);
                v0 = 255;
                div(v1, v0);
                mflo(s2);
                lwc1(f20, s0, 80);
                lw(v0, s3, 36);
                lw(s0, v0, 40);
                mtc1(zero, f12);
                a2 = s2 & 0xFF;
                lw(a3, sp, 0x1BC);
                v0 = 0x3F800000;
                mtc1(v0, f14);
                a0 = fp;
                lq(a1, sp, 0xD0);
                t0 = 0;
                t1 = 0;
                t2 = 0;
                mov_s(f13, f12);
                mov_s(f15, f20);
                jal(ctx, 0x3F50ECu, gen::fn_sub_40E3F0_0040e3f0);
                lw(v0, sp, 0x1C4);
                mult(v1, v0, s0);
                v0 = 0xFFFF;
                div(v1, v0);
                mflo(v1);
                lq(v0, sp, 0xD0);
                a1 = addu(v0, v1);
                mtc1(zero, f12);
                a2 = s2 & 0xFF;
                lw(a3, sp, 0x1C0);
                v0 = 0x3F800000;
                mtc1(v0, f14);
                a0 = fp;
                t0 = 0;
                t1 = 0;
                t2 = 0;
                mov_s(f13, f12);
                mov_s(f15, f20);
                jal(ctx, 0x3F513Cu, gen::fn_sub_40E3F0_0040e3f0);
                lh(a2, s6, 12);
                a0 = 129;
                a1 = 256;
                a3 = s3;
                t0 = s1;
                jal(ctx, 0x3F5158u, gen::fn_sub_3F7390_003f7390);
                a0 = addiu(s5, 285);
                a1 = addiu(s4, 94);
                a2 = s7;
                a3 = s3;
                t0 = s1;
                jal(ctx, 0x3F5174u, gen::fn_sub_3F7A80_003f7a80);
                a0 = s5;
                a1 = s4;
                a2 = s7;
                a3 = 1;
                t0 = s3;
                t1 = s1;
                jal(ctx, 0x3F5194u, gen::fn_sub_3F7890_003f7890);
            } else {
                // 0x003f4ec0
                charge(ctx, 3);
                v0 = si(-2);
                if (v1 == v0) {
                    // 0x003f4ed4
                    charge(ctx, 12);
                    a0 = s5;
                    a1 = s4;
                    a2 = s2;
                    a3 = 0;
                    t0 = s3;
                    t1 = s6;
                    jal(ctx, 0x3F4EECu, gen::fn_sub_3F4A90_003f4a90);
                    a1 = 0x6B0000;
                    a1 = addiu(a1, -4448);  // &0x6AEEA0
                    a0 = addiu(sp, 0x1F0);
                    v1 = 15;
                    for (;;) {
                        // 0x003f4f04
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
                    // 0x003f4f20
                    charge(ctx, 71);
                    lh(v0, s0, 72);
                    fp = addu(s5, v0);
                    lh(v0, s0, 74);
                    v0 = addu(s4, v0);
                    sq(v0, sp, 0xE0);
                    lh(v0, s0, 84);
                    mult(v1, s2, v0);
                    v0 = 255;
                    div(v1, v0);
                    mflo(s2);
                    lwc1(f20, s0, 80);
                    lw(v0, s3, 36);
                    lw(s0, v0, 40);
                    mtc1(zero, f12);
                    a2 = s2 & 0xFF;
                    lw(a3, sp, 0x1F0);
                    v0 = 0x3F800000;
                    mtc1(v0, f14);
                    a0 = fp;
                    lq(a1, sp, 0xE0);
                    t0 = 0;
                    t1 = 0;
                    t2 = 0;
                    mov_s(f13, f12);
                    mov_s(f15, f20);
                    jal(ctx, 0x3F4F84u, gen::fn_sub_40E3F0_0040e3f0);
                    lw(v0, sp, 0x1F8);
                    mult(v1, v0, s0);
                    v0 = 0xFFFF;
                    div(v1, v0);
                    mflo(v1);
                    lq(v0, sp, 0xE0);
                    a1 = addu(v0, v1);
                    mtc1(zero, f12);
                    a2 = s2 & 0xFF;
                    lw(a3, sp, 0x1F4);
                    v0 = 0x3F800000;
                    mtc1(v0, f14);
                    a0 = fp;
                    t0 = 0;
                    t1 = 0;
                    t2 = 0;
                    mov_s(f13, f12);
                    mov_s(f15, f20);
                    jal(ctx, 0x3F4FD4u, gen::fn_sub_40E3F0_0040e3f0);
                    lh(a2, s6, 12);
                    a0 = 122;
                    a1 = 255;
                    a3 = s3;
                    t0 = s1;
                    jal(ctx, 0x3F4FF0u, gen::fn_sub_3F7390_003f7390);
                    a0 = addiu(s5, 285);
                    a1 = addiu(s4, 94);
                    a2 = s7;
                    a3 = s3;
                    t0 = s1;
                    jal(ctx, 0x3F500Cu, gen::fn_sub_3F7A80_003f7a80);
                    a0 = s5;
                    a1 = s4;
                    a2 = s7;
                    a3 = 1;
                    t0 = s3;
                    t1 = s1;
                    jal(ctx, 0x3F502Cu, gen::fn_sub_3F7890_003f7890);
                } else {
                    // 0x003f4ecc
                    charge(ctx, 2);
                    // 0x003f5414
                    charge(ctx, 12);
                    a0 = s5;
                    a1 = s4;
                    a2 = s2;
                    a3 = 4;
                    t0 = s3;
                    t1 = s6;
                    jal(ctx, 0x3F542Cu, gen::fn_sub_3F4A90_003f4a90);
                    a1 = 0x6B0000;
                    a1 = addiu(a1, -4448);  // &0x6AEEA0
                    a0 = addiu(sp, 0xF0);
                    v1 = 15;
                    for (;;) {
                        // 0x003f5444
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
                    // 0x003f5460
                    charge(ctx, 70);
                    lh(v0, s0, 72);
                    fp = addu(s5, v0);
                    lh(v0, s0, 74);
                    v0 = addu(s4, v0);
                    sq(v0, sp, 0xB0);
                    lh(v0, s0, 84);
                    mult(v1, s2, v0);
                    v0 = 255;
                    div(v1, v0);
                    mflo(s2);
                    lwc1(f20, s0, 80);
                    lw(v0, s3, 36);
                    lw(s0, v0, 40);
                    mtc1(zero, f12);
                    a2 = s2 & 0xFF;
                    lw(a3, sp, 0x120);
                    v0 = 0x3F800000;
                    mtc1(v0, f14);
                    a0 = fp;
                    lq(a1, sp, 0xB0);
                    t0 = 0;
                    t1 = 0;
                    t2 = 0;
                    mov_s(f13, f12);
                    mov_s(f15, f20);
                    jal(ctx, 0x3F54C4u, gen::fn_sub_40E3F0_0040e3f0);
                    lw(v0, sp, 0x128);
                    mult(v1, v0, s0);
                    v0 = 0xFFFF;
                    div(v1, v0);
                    mflo(v1);
                    lq(v0, sp, 0xB0);
                    a1 = addu(v0, v1);
                    mtc1(zero, f12);
                    a2 = s2 & 0xFF;
                    lw(a3, sp, 0x124);
                    v0 = 0x3F800000;
                    mtc1(v0, f14);
                    a0 = fp;
                    t0 = 0;
                    t1 = 0;
                    t2 = 0;
                    mov_s(f13, f12);
                    mov_s(f15, f20);
                    jal(ctx, 0x3F5514u, gen::fn_sub_40E3F0_0040e3f0);
                    lh(a2, s6, 12);
                    a0 = 279;
                    a1 = 210;
                    a3 = 1;
                    t0 = s3;
                    t1 = s1;
                    jal(ctx, 0x3F5534u, gen::fn_sub_3F67E0_003f67e0);
                    a0 = 321;
                    a1 = 307;
                    a2 = s7;
                    a3 = s3;
                    t0 = s1;
                    jal(ctx, 0x3F5550u, gen::fn_sub_3F7A80_003f7a80);
                    lh(a2, s6, 12);
                    a0 = s5;
                    a1 = s4;
                    a3 = 0;
                    t0 = s3;
                    t1 = s1;
                    jal(ctx, 0x3F5570u, gen::fn_sub_3F7890_003f7890);
                }
            }
        }
    }
    // 0x003f5578 (the shared epilogue, written out on this path)
    charge(ctx, 14);
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
    sp = addiu(sp, 0x230);
}

// 0x00403970 sub_403970 -- 1232 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Shop item availability check (fclShopMisc.c): for the 64-byte shop row $a0 of the table at 0x7CD8F0, tests its
// condition by kind (+26: 4 a flag, 3 the money / count from sub_16DD50, 2 an item or persona with stock / level rules
// through sub_17C8C0 / sub_176990 / sub_1749A0, ...); returns 0 when the row is not available.
void sub_403970(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00403970
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    v0 = dsll32(a0, 16);
    v0 = dsra32(v0, 16);
    v1 = sll(v0, 6);
    lw(v0, gp, -21504);  // 0x7CD8F0
    v0 = addu(v0, v1);
    s0 = addiu(v0, 16);
    lbu(v1, v0, 26);
    v0 = 4;
    if (v1 == v0) {
        // 0x00403df4
        charge(ctx, 5);
        lw(a0, s0, 12);
        jal(ctx, 0x403DF8u, gen::fn_datGetFlag_0016f190);
        if (v0 != 0) {
        L_00403e14:
            charge(ctx, 1);
            v0 = 1;
        } else {
            // 0x00403e08
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x004039b8
        charge(ctx, 3);
        v0 = 3;
        if (v1 == v0) {
            // 0x00403dd0
            charge(ctx, 6);
            jal(ctx, 0x403DD0u, gen::fn_sub_16DD50_0016dd50);
            lw(v1, s0, 12);
            at = sltu(v0, v1);
            if (at == 0) {
                goto L_00403e14;
            }
            // 0x00403de8
            charge(ctx, 3);
            v0 = 0;
        } else {
            // 0x004039c4
            charge(ctx, 3);
            v0 = 2;
            if (v1 == v0) {
                // 0x00403b88
                charge(ctx, 4);
                lw(v0, s0, 0);
                v0 = v0 & 0x2;
                if (v0 == 0) {
                    // 0x00403c54
                    charge(ctx, 3);
                    lh(v0, s0, 12);
                    if (v0 != 0) {
                        // 0x00403d34
                        charge(ctx, 5);
                        a0 = v0 & 0xFFFF;
                        jal(ctx, 0x403D38u, gen::fn_sub_1749A0_001749a0);
                        if (v0 != 0) {
                            // 0x00403d54
                            charge(ctx, 4);
                            lhu(a1, s0, 8);
                            v1 = a1 & 0x8;
                            if (v1 != 0) {
                                // 0x00403d64
                                charge(ctx, 5);
                                lbu(a0, v0, 4);
                                lh(v1, s0, 14);
                                at = slt(a0, v1);
                                if (at == 0) {
                                    goto L_00403d84;
                                }
                                // 0x00403d78
                                charge(ctx, 3);
                                v0 = 0;
                                goto L_00403dbc;
                            }
                        L_00403d84:
                            charge(ctx, 3);
                            v1 = a1 & 0x10;
                            if (v1 != 0) {
                                // 0x00403d90
                                charge(ctx, 7);
                                lhu(a1, s0, 14);
                                a0 = v0;
                                jal(ctx, 0x403D98u, gen::fn_sub_176990_00176990);
                                v1 = si(-1);
                                if (v0 != v1) {
                                    goto L_00403db8;
                                }
                                // 0x00403dac
                                charge(ctx, 3);
                                v0 = 0;
                                goto L_00403dbc;
                            }
                        L_00403db8:
                            charge(ctx, 1);
                            v0 = 1;
                        L_00403dbc:
                            charge(ctx, 2);
                            if (v0 != 0) {
                                goto L_00403e14;
                            }
                            // 0x00403dc4
                            charge(ctx, 3);
                            v0 = 0;
                        } else {
                            // 0x00403d48
                            charge(ctx, 3);
                            v0 = 0;
                        }
                    } else {
                        // 0x00403c60
                        charge(ctx, 3);
                        s1 = 0;
                        for (;;) {
                            // 0x00403d04
                            charge(ctx, 6);
                            jal(ctx, 0x403D04u, gen::fn_sub_175410_00175410);
                            v0 = v0 & 0xFFFF;
                            v0 = slt(s1, v0);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x00403c6c
                            charge(ctx, 6);
                            a0 = dsll32(s1, 16);
                            a0 = dsra32(a0, 16);
                            jal(ctx, 0x403C74u, gen::fn_sub_174A90_00174a90);
                            if (v0 != 0) {
                                // 0x00403c84
                                charge(ctx, 4);
                                lhu(a1, s0, 8);
                                v1 = a1 & 0x8;
                                if (v1 != 0) {
                                    // 0x00403c94
                                    charge(ctx, 5);
                                    lbu(a0, v0, 4);
                                    lh(v1, s0, 14);
                                    at = slt(a0, v1);
                                    if (at == 0) {
                                        goto L_00403cb4;
                                    }
                                    // 0x00403ca8
                                    charge(ctx, 3);
                                    v0 = 0;
                                    goto L_00403cec;
                                }
                            L_00403cb4:
                                charge(ctx, 3);
                                v1 = a1 & 0x10;
                                if (v1 != 0) {
                                    // 0x00403cc0
                                    charge(ctx, 7);
                                    lhu(a1, s0, 14);
                                    a0 = v0;
                                    jal(ctx, 0x403CC8u, gen::fn_sub_176990_00176990);
                                    v1 = si(-1);
                                    if (v0 != v1) {
                                        goto L_00403ce8;
                                    }
                                    // 0x00403cdc
                                    charge(ctx, 3);
                                    v0 = 0;
                                    goto L_00403cec;
                                }
                            L_00403ce8:
                                charge(ctx, 1);
                                v0 = 1;
                            L_00403cec:
                                charge(ctx, 2);
                                if (v0 == 0) {
                                    goto L_00403d00;
                                }
                                goto L_00403cf4_54;
                            }
                        L_00403d00:
                            charge(ctx, 1);
                            s1 = addiu(s1, 1);
                        }
                        // 0x00403d1c
                        charge(ctx, 1);
                        v0 = 0;
                    L_00403d20:
                        charge(ctx, 2);
                        if (v0 != 0) {
                            goto L_00403e14;
                        }
                        // 0x00403d28
                        charge(ctx, 3);
                        v0 = 0;
                    }
                } else {
                    // 0x00403b98
                    charge(ctx, 3);
                    lh(v0, s0, 12);
                    if (v0 == 0) {
                        // 0x00403ba4
                        charge(ctx, 5);
                        a0 = 0x6B0000;
                        a0 = addiu(a0, -4632);  // "fclShopMisc.c"
                        a1 = 7603;
                        jal(ctx, 0x403BB0u, gen::fn_sub_19D3F0_0019d3f0);
                    }
                    // 0x00403bb8
                    charge(ctx, 5);
                    lh(a0, s0, 12);
                    jal(ctx, 0x403BBCu, gen::fn_sub_17C8C0_0017c8c0);
                    if (v0 != 0) {
                        // 0x00403bd8
                        charge(ctx, 4);
                        lhu(a1, s0, 8);
                        v1 = a1 & 0x8;
                        if (v1 != 0) {
                            // 0x00403be8
                            charge(ctx, 5);
                            lbu(a0, v0, 4);
                            lh(v1, s0, 14);
                            at = slt(a0, v1);
                            if (at == 0) {
                                goto L_00403c08;
                            }
                            // 0x00403bfc
                            charge(ctx, 3);
                            v0 = 0;
                            goto L_00403c40;
                        }
                    L_00403c08:
                        charge(ctx, 3);
                        v1 = a1 & 0x10;
                        if (v1 != 0) {
                            // 0x00403c14
                            charge(ctx, 7);
                            lhu(a1, s0, 14);
                            a0 = v0;
                            jal(ctx, 0x403C1Cu, gen::fn_sub_176990_00176990);
                            v1 = si(-1);
                            if (v0 != v1) {
                                goto L_00403c3c;
                            }
                            // 0x00403c30
                            charge(ctx, 3);
                            v0 = 0;
                            goto L_00403c40;
                        }
                    L_00403c3c:
                        charge(ctx, 1);
                        v0 = 1;
                    L_00403c40:
                        charge(ctx, 2);
                        if (v0 != 0) {
                            goto L_00403e14;
                        }
                        // 0x00403c48
                        charge(ctx, 3);
                        v0 = 0;
                    } else {
                        // 0x00403bcc
                        charge(ctx, 3);
                        v0 = 0;
                    }
                }
            } else {
                // 0x004039d0
                charge(ctx, 3);
                v0 = 1;
                if (v1 == v0) {
                    // 0x00403b4c
                    charge(ctx, 4);
                    jal(ctx, 0x403B4Cu, gen::fn_sub_17C610_0017c610);
                    if (v0 != 0) {
                        // 0x00403b68
                        charge(ctx, 5);
                        lh(v1, v0, 2);
                        lbu(v0, s0, 11);
                        at = slt(v1, v0);
                        if (at == 0) {
                            goto L_00403e14;
                        }
                        // 0x00403b7c
                        charge(ctx, 3);
                        v0 = 0;
                    } else {
                        // 0x00403b5c
                        charge(ctx, 3);
                        v0 = 0;
                    }
                } else {
                    // 0x004039dc
                    charge(ctx, 2);
                    if (v1 != 0) {
                        // 0x004039e4
                        charge(ctx, 2);
                        goto L_00403e14;
                    }
                    // 0x004039ec
                    charge(ctx, 5);
                    s1 = 0;
                    lhu(v1, s0, 8);
                    v0 = v1 & 0x1;
                    if (v0 != 0) {
                        // 0x00403a00
                        charge(ctx, 1);
                        s1 = s1 | 0x1;
                    }
                    // 0x00403a04
                    charge(ctx, 3);
                    v0 = v1 & 0x2;
                    if (v0 != 0) {
                        // 0x00403a10
                        charge(ctx, 1);
                        s1 = s1 | 0x2;
                    }
                    // 0x00403a14
                    charge(ctx, 3);
                    v0 = v1 & 0x4;
                    if (v0 != 0) {
                        // 0x00403a20
                        charge(ctx, 1);
                        s1 = s1 | 0x4;
                    }
                    // 0x00403a24
                    charge(ctx, 26);
                    lb(v0, s0, 14);
                    v0 = dsll32(v0, 28);
                    v0 = dsra32(v0, 28);
                    v0 = v0 & 0xF;
                    v1 = sll(v0, 24);
                    lh(v0, s0, 14);
                    v0 = dsll32(v0, 20);
                    v0 = dsra32(v0, 24);
                    v0 = v0 & 0xFF;
                    v0 = sll(v0, 16);
                    v1 = v1 | v0;
                    lh(v0, s0, 12);
                    v0 = v0 & 0xFFFF;
                    s5 = v0 | v1;
                    lbu(v0, s0, 11);
                    s0 = dsll32(v0, 16);
                    s0 = dsra32(s0, 16);
                    s3 = s5 & 0xFFFF;
                    a0 = dsll32(s3, 16);
                    a0 = dsra32(a0, 16);
                    jal(ctx, 0x403A74u, gen::fn_sub_171250_00171250);
                    s2 = v0;
                    v1 = 4;
                    if (v0 != v1) {
                        // 0x00403a8c
                        charge(ctx, 2);
                        // 0x00403acc
                        charge(ctx, 7);
                        s3 = 0;
                        s4 = 0;
                        s1 = s1 | 0x8;
                        s0 = dsll32(s0, 16);
                        s0 = dsra32(s0, 16);
                        for (;;) {
                            // 0x00403b28
                            charge(ctx, 3);
                            v0 = slti(s4, 300);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x00403ae8
                            charge(ctx, 8);
                            a0 = s5;
                            a1 = s2;
                            a2 = s1;
                            a3 = s4;
                            jal(ctx, 0x403AF8u, gen::fn_sub_402510_00402510);
                            if (v0 != 0) {
                                // 0x00403b08
                                charge(ctx, 4);
                                s3 = addiu(s3, 1);
                                v0 = slt(s3, s0);
                                if (v0 != 0) {
                                    goto L_00403b24;
                                }
                                goto L_00403b18_19;
                            }
                        L_00403b24:
                            charge(ctx, 1);
                            s4 = addiu(s4, 1);
                        }
                        goto L_00403b34;
                    }
                    // 0x00403a94
                    charge(ctx, 11);
                    a1 = dsll32(s3, 16);
                    a1 = dsra32(a1, 16);
                    a0 = 1;
                    jal(ctx, 0x403AA0u, gen::fn_sub_170760_00170760);
                    v1 = v0 & 0xFFFF;
                    v0 = dsll32(s0, 16);
                    v0 = dsra32(v0, 16);
                    v0 = slt(v1, v0);
                    if (v0 != 0) {
                    L_00403b34:
                        charge(ctx, 1);
                        v0 = 0;
                    } else {
                        // 0x00403ac0
                        charge(ctx, 3);
                        v0 = 1;
                    }
                L_00403b38:
                    charge(ctx, 2);
                    if (v0 != 0) {
                        goto L_00403e14;
                    }
                    // 0x00403b40
                    charge(ctx, 3);
                    v0 = 0;
                }
            }
        }
    }
    // 0x00403e18 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
    return;
L_00403b18_19:
    charge(ctx, 3);
    v0 = 1;
    goto L_00403b38;
L_00403cf4_54:
    charge(ctx, 3);
    v0 = 1;
    goto L_00403d20;
}

// 0x00404120 sub_404120 -- 836 bytes; frame 0x90: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Shop purchase commit (fclShopMisc.c): for the 64-byte shop row $a0, by its kind (+26: 3 pays the price through
// sub_16E9B0, 2 adds the persona through sub_174B40, ...) applies the purchase when $a1 is set, asserting the
// preconditions; returns 1 when it can be bought.
void sub_404120(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00404120
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
    s0 = a1;
    v0 = dsll32(a0, 16);
    v0 = dsra32(v0, 16);
    v1 = sll(v0, 6);
    lw(v0, gp, -21504);  // 0x7CD8F0
    v0 = addu(v0, v1);
    s1 = addiu(v0, 16);
    lw(v0, v0, 16);
    v0 = v0 & 0x1;
    if (v0 != 0) {
        // 0x00404180
        charge(ctx, 4);
        lbu(v1, s1, 10);
        v0 = 3;
        if (v1 == v0) {
            // 0x004043e0
            charge(ctx, 6);
            jal(ctx, 0x4043E0u, gen::fn_sub_16DD50_0016dd50);
            lw(v1, s1, 12);
            at = sltu(v0, v1);
            if (at != 0) {
                // 0x004043f8
                charge(ctx, 5);
                a0 = 0x6B0000;
                a0 = addiu(a0, -4632);  // "fclShopMisc.c"
                a1 = 7794;
                jal(ctx, 0x404404u, gen::fn_sub_19D3F0_0019d3f0);
            }
            // 0x0040440c
            charge(ctx, 2);
            if (s0 != 0) {
                // 0x00404420
                charge(ctx, 4);
                lw(v0, s1, 12);
                a0 = subu(0, v0);
                jal(ctx, 0x404428u, gen::fn_sub_16E9B0_0016e9b0);
            L_00404430:
                charge(ctx, 1);
                v0 = 1;
            } else {
                // 0x00404414
                charge(ctx, 3);
                v0 = 1;
            }
        } else {
            // 0x00404190
            charge(ctx, 3);
            v0 = 2;
            if (v1 == v0) {
                // 0x0040438c
                charge(ctx, 6);
                lh(s2, s1, 12);
                jal(ctx, 0x404390u, gen::fn_sub_1752B0_001752b0);
                v0 = v0 & 0xFFFF;
                if (s2 == v0) {
                    // 0x004043a4
                    charge(ctx, 5);
                    a0 = 0x6B0000;
                    a0 = addiu(a0, -4632);  // "fclShopMisc.c"
                    a1 = 7789;
                    jal(ctx, 0x4043B0u, gen::fn_sub_19D3F0_0019d3f0);
                }
                // 0x004043b8
                charge(ctx, 2);
                if (s0 != 0) {
                    // 0x004043cc
                    charge(ctx, 5);
                    lhu(a0, s1, 12);
                    jal(ctx, 0x4043D0u, gen::fn_sub_174B40_00174b40);
                    goto L_00404430;
                }
                // 0x004043c0
                charge(ctx, 3);
                v0 = 1;
            } else {
                // 0x0040419c
                charge(ctx, 3);
                v0 = 1;
                if (v1 == v0) {
                    // 0x00404384
                    charge(ctx, 2);
                } else {
                    // 0x004041a8
                    charge(ctx, 2);
                    if (v1 != 0) {
                        // 0x004041b0
                        charge(ctx, 2);
                        goto L_00404430;
                    }
                    // 0x004041b8
                    charge(ctx, 7);
                    lh(a0, s1, 12);
                    jal(ctx, 0x4041BCu, gen::fn_sub_171250_00171250);
                    s2 = v0;
                    v1 = 4;
                    if (v0 != v1) {
                        // 0x004041d4
                        charge(ctx, 2);
                        // 0x00404220
                        charge(ctx, 6);
                        a0 = 0;
                        s3 = 0;
                        lhu(v1, s1, 8);
                        v0 = v1 & 0x1;
                        if (v0 != 0) {
                            // 0x00404238
                            charge(ctx, 1);
                            a0 = a0 | 0x1;
                        }
                        // 0x0040423c
                        charge(ctx, 3);
                        v0 = v1 & 0x2;
                        if (v0 != 0) {
                            // 0x00404248
                            charge(ctx, 1);
                            a0 = a0 | 0x2;
                        }
                        // 0x0040424c
                        charge(ctx, 3);
                        v0 = v1 & 0x4;
                        if (v0 != 0) {
                            // 0x00404258
                            charge(ctx, 1);
                            a0 = a0 | 0x4;
                        }
                        // 0x0040425c
                        charge(ctx, 18);
                        lb(v0, s1, 14);
                        v0 = dsll32(v0, 28);
                        v0 = dsra32(v0, 28);
                        v0 = v0 & 0xF;
                        v1 = sll(v0, 24);
                        lh(v0, s1, 14);
                        v0 = dsll32(v0, 20);
                        v0 = dsra32(v0, 24);
                        v0 = v0 & 0xFF;
                        v0 = sll(v0, 16);
                        v1 = v1 | v0;
                        lh(v0, s1, 12);
                        v0 = v0 & 0xFFFF;
                        s7 = v0 | v1;
                        s5 = 0;
                        s6 = a0 | 0x8;
                        for (;;) {
                            // 0x0040435c
                            charge(ctx, 3);
                            v0 = slti(s5, 300);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x004042a4
                            charge(ctx, 8);
                            a0 = s7;
                            a1 = s2;
                            a2 = s6;
                            a3 = s5;
                            jal(ctx, 0x4042B4u, gen::fn_sub_402510_00402510);
                            if (v0 != 0) {
                                // 0x004042c4
                                charge(ctx, 3);
                                s4 = 0;
                                for (;;) {
                                    // 0x00404304
                                    charge(ctx, 3);
                                    v0 = slti(s4, 4);
                                    if (v0 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                    // 0x004042d0
                                    charge(ctx, 9);
                                    a1 = dsll32(s4, 16);
                                    a1 = dsra32(a1, 16);
                                    a0 = 1;
                                    jal(ctx, 0x4042DCu, gen::fn_datGetEquipmentIdx_0016cb80);
                                    v0 = dsll32(v0, 16);
                                    v0 = dsra32(v0, 16);
                                    if (s5 == v0) {
                                        goto L_004042f4_22;
                                    }
                                    // 0x00404300
                                    charge(ctx, 1);
                                    s4 = addiu(s4, 1);
                                }
                                // 0x00404310
                                charge(ctx, 2);
                                if (s0 == 0) {
                                    goto L_00404318_26;
                                }
                                // 0x00404324
                                charge(ctx, 10);
                                a0 = 1;
                                a1 = s5;
                                a2 = 0;
                                jal(ctx, 0x404330u, gen::fn_sub_16FEA0_0016fea0);
                                s3 = addiu(s3, 1);
                                lbu(v0, s1, 11);
                                v0 = slt(s3, v0);
                                if (v0 != 0) {
                                    goto L_00404358;
                                }
                                goto L_0040434c_28;
                            }
                        L_00404358:
                            charge(ctx, 1);
                            s5 = addiu(s5, 1);
                        }
                        // 0x00404368
                        charge(ctx, 7);
                        a0 = 0x6B0000;
                        a0 = addiu(a0, -4632);  // "fclShopMisc.c"
                        a1 = 7781;
                        jal(ctx, 0x404374u, gen::fn_sub_19D3F0_0019d3f0);
                        goto L_00404430;
                    }
                    // 0x004041dc
                    charge(ctx, 3);
                    lh(v0, s1, 12);
                    if (s0 != 0) {
                        // 0x004041f4
                        charge(ctx, 11);
                        a1 = dsll32(v0, 16);
                        a1 = dsra32(a1, 16);
                        lbu(v0, s1, 11);
                        v0 = subu(0, v0);
                        a2 = dsll32(v0, 16);
                        a2 = dsra32(a2, 16);
                        a0 = 1;
                        jal(ctx, 0x404210u, gen::fn_sub_170C00_00170c00);
                        goto L_00404430;
                    }
                    // 0x004041e8
                    charge(ctx, 3);
                    v0 = 1;
                }
            }
        }
    } else {
        // 0x00404174
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x00404434 (the shared epilogue, written out on this path)
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
    return;
L_004042f4_22:
    charge(ctx, 3);
    v0 = 0;
    // 0x00404434 (the shared epilogue, written out on this path)
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
    return;
L_00404318_26:
    charge(ctx, 3);
    v0 = 1;
    // 0x00404434 (the shared epilogue, written out on this path)
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
    return;
L_0040434c_28:
    charge(ctx, 3);
    v0 = 1;
    // 0x00404434 (the shared epilogue, written out on this path)
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

// 0x00406CA0 sub_406CA0 -- 1248 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Facility list row draw callback: places the row at the list origin ($a2) plus the row offset, scales the alpha by the
// row's +38 / 255, and draws its frame, icon and text (sub_40E3C0, sub_405F70, sub_406AA0, sub_4064E0, sub_40E3F0).
void sub_406CA0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15};
    // 0x00406ca0
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a3 = a1;
    v1 = a2;
    t2 = 0;
    lh(t0, a1, 20);
    lw(a0, a2, 0);
    s4 = addu(a0, t0);
    lh(t0, a1, 22);
    lw(a0, a2, 4);
    s3 = addu(a0, t0);
    lh(a2, a2, 8);
    lh(a0, a1, 38);
    mult(a1, a2, a0);
    a0 = 255;
    div(a1, a0);
    mflo(s2);
    if (s2 != 0) {
        // 0x00406d00
        charge(ctx, 4);
        lh(a0, v1, 10);
        a0 = a0 & 0x1;
        if (a0 != 0) {
            // 0x00406d10
            charge(ctx, 1);
            t2 = 1;
        }
        // 0x00406d14
        charge(ctx, 7);
        lw(t0, v1, 12);
        lw(t1, t0, 36);
        lw(a2, t1, 68);
        lw(a0, a3, 16);
        at = sltiu(a0, 8);
        if (at != 0) {
            // 0x00406d30
            charge(ctx, 7);
            a1 = 0x7C0000;
            a1 = addiu(a1, -16896);  // "Lm@"
            a0 = sll(a0, 2);
            a0 = addu(a0, a1);
            lw(a0, a0, 0);
            switch (a0.u()) {
            case 0x406D4Cu:  // table[0]
                // 0x00406d4c
                charge(ctx, 4);
                lw(v0, a2, 0);
                v0 = v0 & 0x1;
                if (v0 == 0) {
                    // 0x00406dc4
                    charge(ctx, 8);
                    a0 = s4;
                    a1 = s3;
                    a2 = s2;
                    lw(t1, v1, 16);
                    jal(ctx, 0x406DD4u, gen::fn_sub_405F70_00405f70);
                } else {
                    // 0x00406d5c
                    charge(ctx, 26);
                    lw(v0, v1, 16);
                    lw(v0, v0, 20);
                    lw(s1, v0, 28);
                    s0 = sll(t2, 2);
                    mtc1(zero, f12);
                    a2 = s2 & 0xFF;
                    lh(v0, s1, 6);
                    v0 = addu(v0, s0);
                    a3 = addiu(v0, 44);
                    a0 = s4;
                    a1 = s3;
                    t0 = 0;
                    jal(ctx, 0x406D8Cu, gen::fn_sub_40E3C0_0040e3c0);
                    mtc1(zero, f12);
                    a2 = s2 & 0xFF;
                    lh(v0, s1, 6);
                    v0 = addu(v0, s0);
                    a3 = addiu(v0, 52);
                    a0 = s4;
                    a1 = s3;
                    t0 = 0;
                    jal(ctx, 0x406DB4u, gen::fn_sub_40E3C0_0040e3c0);
                }
                break;
            case 0x406DE4u:  // table[1]
                // 0x00406de4
                charge(ctx, 4);
                lw(a0, a2, 0);
                a0 = a0 & 0x1;
                if (a0 != 0) {
                    // 0x00406df4
                    charge(ctx, 11);
                    mtc1(s2, f0);
                    cvt_s_w(f1, f0);
                    lwc1(f0, gp, -32636);  // 0x7CAD74
                    mul_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(s0, f0);
                    lw(a0, t0, 12);
                    lw(v0, v1, 16);
                    if (a0 != v0) {
                        // 0x00406e20
                        charge(ctx, 9);
                        mtc1(s0, f0);
                        cvt_s_w(f1, f0);
                        v0 = 0x3F000000;
                        mtc1(v0, f0);
                        mul_s(f0, f1, f0);
                        cvt_w_s(f0, f0);
                        mfc1(s0, f0);
                    }
                    // 0x00406e44
                    charge(ctx, 18);
                    mtc1(zero, f12);
                    a2 = s0 & 0xFF;
                    a0 = s4;
                    a1 = s3;
                    a3 = 79;
                    t0 = 0;
                    jal(ctx, 0x406E5Cu, gen::fn_sub_40E3C0_0040e3c0);
                    mtc1(zero, f12);
                    a2 = s0 & 0xFF;
                    a0 = s4;
                    a1 = s3;
                    a3 = 80;
                    t0 = 0;
                    jal(ctx, 0x406E7Cu, gen::fn_sub_40E3C0_0040e3c0);
                }
                break;
            case 0x406E8Cu:  // table[2]
                // 0x00406e8c
                charge(ctx, 58);
                mtc1(zero, f12);
                a2 = s2 & 0xFF;
                a0 = s4;
                a1 = s3;
                a3 = 34;
                t0 = 0;
                jal(ctx, 0x406EA4u, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s2 & 0xFF;
                a0 = s4;
                a1 = s3;
                a3 = 35;
                t0 = 0;
                jal(ctx, 0x406EC4u, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s2 & 0xFF;
                a0 = s4;
                a1 = s3;
                a3 = 36;
                t0 = 0;
                jal(ctx, 0x406EE4u, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s2 & 0xFF;
                a0 = s4;
                a1 = s3;
                a3 = 37;
                t0 = 0;
                jal(ctx, 0x406F04u, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s2 & 0xFF;
                a0 = s4;
                a1 = s3;
                a3 = 38;
                t0 = 0;
                jal(ctx, 0x406F24u, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s2 & 0xFF;
                a0 = s4;
                a1 = s3;
                a3 = 39;
                t0 = 0;
                jal(ctx, 0x406F44u, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s2 & 0xFF;
                a0 = s4;
                a1 = s3;
                a3 = 40;
                t0 = 0;
                jal(ctx, 0x406F64u, gen::fn_sub_40E3C0_0040e3c0);
                break;
            case 0x406F74u:  // table[4]
                // 0x00406f74
                charge(ctx, 7);
                a0 = s4;
                a1 = s3;
                a2 = s2;
                jal(ctx, 0x406F80u, gen::fn_sub_406AA0_00406aa0);
                break;
            case 0x406F90u:  // table[5]
                // 0x00406f90
                charge(ctx, 4);
                lw(v0, a2, 0);
                v0 = v0 & 0x2;
                if (v0 != 0) {
                    // 0x00406fe8
                    charge(ctx, 18);
                    mtc1(zero, f12);
                    a2 = s2 & 0xFF;
                    a0 = s4;
                    a1 = s3;
                    a3 = 105;
                    t0 = 0;
                    jal(ctx, 0x407000u, gen::fn_sub_40E3C0_0040e3c0);
                    mtc1(zero, f12);
                    a2 = s2 & 0xFF;
                    a0 = s4;
                    a1 = s3;
                    a3 = 106;
                    t0 = 0;
                    jal(ctx, 0x407020u, gen::fn_sub_40E3C0_0040e3c0);
                } else {
                    // 0x00406fa0
                    charge(ctx, 18);
                    mtc1(zero, f12);
                    a2 = s2 & 0xFF;
                    a0 = s4;
                    a1 = s3;
                    a3 = 28;
                    t0 = 0;
                    jal(ctx, 0x406FB8u, gen::fn_sub_40E3C0_0040e3c0);
                    mtc1(zero, f12);
                    a2 = s2 & 0xFF;
                    a0 = s4;
                    a1 = s3;
                    a3 = 29;
                    t0 = 0;
                    jal(ctx, 0x406FD8u, gen::fn_sub_40E3C0_0040e3c0);
                }
                break;
            case 0x407030u:  // table[3]
                // 0x00407030
                charge(ctx, 9);
                a0 = s4;
                a1 = s3;
                a2 = s2;
                a3 = t0;
                lw(t0, v1, 16);
                jal(ctx, 0x407044u, gen::fn_sub_4064E0_004064e0);
                break;
            case 0x407054u:  // table[6]
                // 0x00407054
                charge(ctx, 10);
                mtc1(zero, f12);
                a2 = s2 & 0xFF;
                a0 = 0;
                a1 = 0;
                a3 = 27;
                t0 = 0;
                jal(ctx, 0x40706Cu, gen::fn_sub_40E3C0_0040e3c0);
                break;
            case 0x40707Cu:  // table[7]
                // 0x0040707c
                charge(ctx, 5);
                lhu(a0, t0, 16);
                lw(v1, t1, 32);
                v1 = sltu(a0, v1);
                if (v1 == 0) {
                    // 0x00407090
                    charge(ctx, 51);
                    lw(s0, t1, 40);
                    mtc1(zero, f12);
                    a2 = s2 & 0xFF;
                    v0 = 0x3F800000;
                    mtc1(v0, f14);
                    a0 = 0;
                    a1 = 0;
                    a3 = 41;
                    t0 = 0;
                    t1 = 0;
                    t2 = 0;
                    mov_s(f13, f12);
                    mov_s(f15, f14);
                    jal(ctx, 0x4070C4u, gen::fn_sub_40E3F0_0040e3f0);
                    mtc1(zero, f12);
                    a2 = s2 & 0xFF;
                    v0 = 0x3F800000;
                    mtc1(v0, f14);
                    a0 = 0;
                    a1 = 0;
                    a3 = 42;
                    t0 = 0;
                    t1 = 0;
                    t2 = 0;
                    mov_s(f13, f12);
                    mov_s(f15, f14);
                    jal(ctx, 0x4070FCu, gen::fn_sub_40E3F0_0040e3f0);
                    v0 = sll(s0, 2);
                    v0 = addu(v0, s0);
                    v0 = sll(v0, 3);
                    v0 = subu(v0, s0);
                    v1 = sll(v0, 1);
                    v0 = 0xFFFF;
                    div(v1, v0);
                    mflo(v0);
                    a1 = addiu(v0, 101);
                    mtc1(zero, f12);
                    a2 = s2 & 0xFF;
                    v0 = 0x3F800000;
                    mtc1(v0, f14);
                    a0 = 617;
                    a3 = 43;
                    t0 = 0;
                    t1 = 0;
                    t2 = 0;
                    mov_s(f13, f12);
                    mov_s(f15, f14);
                    jal(ctx, 0x407154u, gen::fn_sub_40E3F0_0040e3f0);
                }
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, a0.u());
                return;
            }
        }
    }
    // 0x0040715c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x0040A7F0 sub_40A7F0 -- 2984 bytes; frame 0x120: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Facility shop detail panel draw callback: at the row origin ($a2) with the scaled alpha, draws the item detail panel
// -- labels, the numbers formatted with sprintf, icons (sub_3B32D0, sub_40EB50, sub_17CF00, sub_40EC20) through the
// sprite helpers sub_40E3C0 / sub_40E3F0.
void sub_40A7F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15};
    // 0x0040a7f0
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0x120);
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
    fp = a2;
    s2 = 0;
    lh(a0, a1, 20);
    lw(v1, a2, 0);
    s4 = addu(v1, a0);
    lh(a0, a1, 22);
    lw(v1, a2, 4);
    s3 = addu(v1, a0);
    lh(a0, a2, 8);
    lh(v1, a1, 38);
    mult(a0, a0, v1);
    v1 = 255;
    div(a0, v1);
    mflo(s1);
    if (s1 != 0) {
        // 0x0040a85c
        charge(ctx, 4);
        lh(v1, fp, 0xA);
        v1 = v1 & 0x1;
        if (v1 != 0) {
            // 0x0040a86c
            charge(ctx, 1);
            s2 = 1;
        }
        // 0x0040a870
        charge(ctx, 7);
        lw(a3, fp, 0xC);
        lw(a2, a3, 36);
        lw(s0, a2, 68);
        lw(v1, a1, 16);
        at = sltiu(v1, 14);
        if (at != 0) {
            // 0x0040a88c
            charge(ctx, 7);
            a0 = 0x7C0000;
            a0 = addiu(a0, -16864);  // &0x7BBE20
            v1 = sll(v1, 2);
            v1 = addu(v1, a0);
            lw(v1, v1, 0);
            switch (v1.u()) {
            case 0x40A8A8u:  // table[0]
                // 0x0040a8a8
                charge(ctx, 5);
                lw(s5, a2, 44);
                lw(a0, s0, 4);
                v1 = si(-9);
                if (a0 == v1) {
                    // 0x0040a8bc
                    charge(ctx, 2);
                    s4 = addiu(s4, 62);
                    s3 = addiu(s3, -28);
                }
                // 0x0040a8c4
                charge(ctx, 6);
                s6 = 0;
                v1 = si(-256);
                v1 = s1 | v1;
                sw(v1, sp, 0xB0);
                for (;;) {
                    // 0x0040aa68
                    charge(ctx, 6);
                    lw(a1, fp, 0xC);
                    lw(a0, a1, 36);
                    lw(v1, a0, 32);
                    v1 = slt(s6, v1);
                    if (v1 == 0) {
                        goto L_0040aa80_16;
                    }
                    backedge(ctx);
                    // 0x0040a8dc
                    charge(ctx, 4);
                    s7 = 0;
                    lw(v0, a1, 12);
                    if (s5 == v0) {
                        // 0x0040a8ec
                        charge(ctx, 1);
                        s7 = 1;
                    }
                    // 0x0040a8f0
                    charge(ctx, 7);
                    lw(v0, a0, 12);
                    mult(v0, s6, v0);
                    s2 = addu(s3, v0);
                    lw(v0, s0, 0);
                    v0 = v0 & 0x4;
                    if (v0 == 0) {
                        // 0x0040a954
                        charge(ctx, 65);
                        lwc1(f1, gp, -21264);  // 0x7CD9E0
                        lwc1(f0, gp, -21260);  // 0x7CD9E4
                        swc1(f1, sp, 0x118);
                        swc1(f0, sp, 0x11C);
                        lwc1(f1, gp, -21256);  // 0x7CD9E8
                        lwc1(f0, gp, -21252);  // 0x7CD9EC
                        swc1(f1, sp, 0x110);
                        swc1(f0, sp, 0x114);
                        lw(v0, s5, 20);
                        lw(v0, v0, 28);
                        sq(v0, sp, 0xA0);
                        mtc1(zero, f12);
                        a2 = s1 & 0xFF;
                        lw(v0, v0, 4);
                        lhu(v1, v0, 2);
                        v0 = sll(v1, 3);
                        v0 = subu(v0, v1);
                        v1 = sll(v0, 1);
                        lw(v0, gp, -18640);  // 0x7CE420
                        v0 = addu(v0, v1);
                        lbu(v0, v0, 2);
                        v0 = addiu(v0, -1);
                        v0 = sll(v0, 1);
                        t0 = addu(v0, s7);
                        a0 = s4;
                        a1 = s2;
                        a3 = 142;
                        jal(ctx, 0x40A9C0u, gen::fn_sub_40E3C0_0040e3c0);
                        s7 = sll(s7, 2);
                        a0 = addiu(s4, 163);
                        a1 = addiu(s2, 132);
                        mtc1(zero, f12);
                        v0 = addu(s7, sp);
                        lb(a3, v0, 280);
                        lq(v0, sp, 0xA0);
                        lw(v0, v0, 4);
                        lhu(v1, v0, 2);
                        v0 = sll(v1, 4);
                        v1 = addu(v0, v1);
                        lw(v0, gp, -18444);  // 0x7CE4E4
                        t1 = addu(v0, v1);
                        lw(a2, sp, 0xB0);
                        t0 = 1;
                        t2 = 16;
                        t3 = 110;
                        jal(ctx, 0x40AA0Cu, gen::fn_sub_3B32D0_003b32d0);
                        lq(v0, sp, 0xA0);
                        lw(v0, v0, 4);
                        lbu(a2, v0, 4);
                        a0 = addiu(sp, 0xF0);
                        a1 = addiu(gp, -21488);  // "%d"
                        jal(ctx, 0x40AA28u, gen::fn_sprintf_00523ac8);
                        a0 = addiu(s4, 372);
                        a1 = addiu(s2, 133);
                        mtc1(zero, f12);
                        a2 = s1 & 0xFF;
                        v0 = addu(s7, sp);
                        lw(a3, v0, 272);
                        t0 = addiu(sp, 0xF0);
                        t1 = 1;
                        jal(ctx, 0x40AA50u, gen::fn_sub_40EB50_0040eb50);
                    } else {
                        // 0x0040a90c
                        charge(ctx, 18);
                        mtc1(zero, f12);
                        a2 = s1 & 0xFF;
                        a0 = s4;
                        a1 = s2;
                        a3 = 141;
                        t0 = s7;
                        jal(ctx, 0x40A924u, gen::fn_sub_40E3C0_0040e3c0);
                        mtc1(zero, f12);
                        a2 = s1 & 0xFF;
                        a0 = s4;
                        a1 = s2;
                        a3 = 143;
                        t0 = 0;
                        jal(ctx, 0x40A944u, gen::fn_sub_40E3C0_0040e3c0);
                    }
                    // 0x0040aa58
                    charge(ctx, 3);
                    lw(s5, s5, 16);
                    if (s5 != 0) {
                        // 0x0040aa64
                        charge(ctx, 1);
                        s6 = addiu(s6, 1);
                        continue;
                    }
                    break;
                }
                break;
            case 0x40AA88u:  // table[1]
                // 0x0040aa88
                charge(ctx, 4);
                lw(s2, a2, 44);
                s5 = 0;
                for (;;) {
                    // 0x0040ab58
                    charge(ctx, 6);
                    lw(a1, fp, 0xC);
                    lw(a0, a1, 36);
                    lw(v1, a0, 32);
                    v1 = slt(s5, v1);
                    if (v1 == 0) {
                        goto L_0040ab70_26;
                    }
                    backedge(ctx);
                    // 0x0040aa98
                    charge(ctx, 4);
                    s6 = 0;
                    lw(v0, a1, 12);
                    if (s2 == v0) {
                        // 0x0040aaa8
                        charge(ctx, 1);
                        s6 = 1;
                    }
                    // 0x0040aaac
                    charge(ctx, 7);
                    lw(v0, a0, 12);
                    mult(v0, s5, v0);
                    s7 = addu(s3, v0);
                    lw(v0, s0, 0);
                    v0 = v0 & 0x4;
                    if (v0 == 0) {
                        // 0x0040aaf0
                        charge(ctx, 22);
                        lwc1(f1, gp, -21248);  // 0x7CD9F0
                        lwc1(f0, gp, -21244);  // 0x7CD9F4
                        swc1(f1, sp, 0x108);
                        swc1(f0, sp, 0x10C);
                        lw(v0, s2, 20);
                        lw(v0, v0, 28);
                        a0 = addiu(sp, 0xE0);
                        a1 = addiu(gp, -21488);  // "%d"
                        lw(a2, v0, 8);
                        jal(ctx, 0x40AB14u, gen::fn_sprintf_00523ac8);
                        a0 = addiu(s4, 517);
                        a1 = addiu(s7, 133);
                        mtc1(zero, f12);
                        a2 = s1 & 0xFF;
                        v0 = sll(s6, 2);
                        v0 = addu(v0, sp);
                        lw(a3, v0, 264);
                        t0 = addiu(sp, 0xE0);
                        t1 = 9;
                        jal(ctx, 0x40AB40u, gen::fn_sub_40EB50_0040eb50);
                    } else {
                        // 0x0040aac8
                        charge(ctx, 10);
                        mtc1(zero, f12);
                        a2 = s1 & 0xFF;
                        a0 = s4;
                        a1 = s7;
                        a3 = 144;
                        t0 = 0;
                        jal(ctx, 0x40AAE0u, gen::fn_sub_40E3C0_0040e3c0);
                    }
                    // 0x0040ab48
                    charge(ctx, 3);
                    lw(s2, s2, 16);
                    if (s2 != 0) {
                        // 0x0040ab54
                        charge(ctx, 1);
                        s5 = addiu(s5, 1);
                        continue;
                    }
                    break;
                }
                break;
            case 0x40AB78u:  // table[2]
                // 0x0040ab78
                charge(ctx, 4);
                lw(v1, s0, 0);
                v1 = v1 & 0x4;
                if (v1 != 0) {
                    // 0x0040ab88
                    charge(ctx, 4);
                    lw(v1, s0, 4);
                    v0 = si(-8);
                    if (v1 != v0) {
                        // 0x0040ac2c
                        charge(ctx, 2);
                        if (s2 == 0) {
                            // 0x0040ac34
                            charge(ctx, 7);
                            mtc1(s1, f0);
                            cvt_s_w(f1, f0);
                            lwc1(f0, gp, -32636);  // 0x7CAD74
                            mul_s(f0, f1, f0);
                            cvt_w_s(f0, f0);
                            mfc1(s1, f0);
                        }
                        // 0x0040ac50
                        charge(ctx, 2);
                        if (s2 != 0) {
                            // 0x0040ac58
                            charge(ctx, 8);
                            a0 = addiu(s4, 62);
                            a1 = addiu(s3, -28);
                            mtc1(zero, f12);
                            a2 = s1 & 0xFF;
                            a3 = 154;
                            t0 = 0;
                            jal(ctx, 0x40AC70u, gen::fn_sub_40E3C0_0040e3c0);
                        }
                        // 0x0040ac78
                        charge(ctx, 18);
                        a0 = addiu(s4, 62);
                        a1 = addiu(s3, -28);
                        mtc1(zero, f12);
                        a2 = s1 & 0xFF;
                        a3 = 146;
                        t0 = 0;
                        jal(ctx, 0x40AC90u, gen::fn_sub_40E3C0_0040e3c0);
                        a0 = addiu(s4, 62);
                        a1 = addiu(s3, -28);
                        mtc1(zero, f12);
                        a2 = s1 & 0xFF;
                        a3 = 155;
                        t0 = 0;
                        jal(ctx, 0x40ACB0u, gen::fn_sub_40E3C0_0040e3c0);
                    } else {
                        // 0x0040ab98
                        charge(ctx, 2);
                        if (s2 == 0) {
                            // 0x0040aba0
                            charge(ctx, 7);
                            mtc1(s1, f0);
                            cvt_s_w(f1, f0);
                            lwc1(f0, gp, -32636);  // 0x7CAD74
                            mul_s(f0, f1, f0);
                            cvt_w_s(f0, f0);
                            mfc1(s1, f0);
                        }
                        // 0x0040abbc
                        charge(ctx, 2);
                        if (s2 != 0) {
                            // 0x0040abc4
                            charge(ctx, 8);
                            mtc1(zero, f12);
                            a2 = s1 & 0xFF;
                            a0 = s4;
                            a1 = s3;
                            a3 = 148;
                            t0 = 0;
                            jal(ctx, 0x40ABDCu, gen::fn_sub_40E3C0_0040e3c0);
                        }
                        // 0x0040abe4
                        charge(ctx, 18);
                        mtc1(zero, f12);
                        a2 = s1 & 0xFF;
                        a0 = s4;
                        a1 = s3;
                        a3 = 146;
                        t0 = 0;
                        jal(ctx, 0x40ABFCu, gen::fn_sub_40E3C0_0040e3c0);
                        mtc1(zero, f12);
                        a2 = s1 & 0xFF;
                        a0 = s4;
                        a1 = s3;
                        a3 = 147;
                        t0 = 0;
                        jal(ctx, 0x40AC1Cu, gen::fn_sub_40E3C0_0040e3c0);
                    }
                }
                break;
            case 0x40ACC0u:  // table[8]
                // 0x0040acc0
                charge(ctx, 18);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a0 = s4;
                a1 = s3;
                a3 = 107;
                t0 = 0;
                jal(ctx, 0x40ACD8u, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a0 = s4;
                a1 = s3;
                a3 = 108;
                t0 = 0;
                jal(ctx, 0x40ACF8u, gen::fn_sub_40E3C0_0040e3c0);
                break;
            case 0x40AD08u:  // table[3]
                // 0x0040ad08
                charge(ctx, 45);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a0 = s4;
                a1 = s3;
                a3 = 117;
                t0 = 0;
                jal(ctx, 0x40AD20u, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a0 = s4;
                a1 = s3;
                a3 = 118;
                t0 = 0;
                jal(ctx, 0x40AD40u, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a0 = s4;
                a1 = s3;
                a3 = 119;
                t0 = 0;
                jal(ctx, 0x40AD60u, gen::fn_sub_40E3C0_0040e3c0);
                jal(ctx, 0x40AD68u, gen::fn_sub_17CF00_0017cf00);
                a0 = addiu(sp, 0xC0);
                a1 = addiu(gp, -21488);  // "%d"
                a2 = v0;
                jal(ctx, 0x40AD7Cu, gen::fn_sprintf_00523ac8);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a0 = s4;
                a1 = s3;
                a3 = 0;
                t0 = addiu(sp, 0xC0);
                t1 = 1;
                t2 = 38;
                t3 = 0x410000;
                t3 = addiu(t3, -22592);  // &sub_40A7C0
                jal(ctx, 0x40ADACu, gen::fn_sub_40EC20_0040ec20);
                break;
            case 0x40ADBCu:  // table[4]
                // 0x0040adbc
                charge(ctx, 4);
                lw(v0, s0, 0);
                v0 = v0 & 0x2;
                if (v0 != 0) {
                    // 0x0040adcc
                    charge(ctx, 1);
                    s2 = 1;
                }
                // 0x0040add0
                charge(ctx, 34);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a0 = s4;
                a1 = s3;
                a3 = 121;
                t0 = s2;
                jal(ctx, 0x40ADE8u, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a0 = s4;
                a1 = s3;
                a3 = 122;
                t0 = s2;
                jal(ctx, 0x40AE08u, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a0 = s4;
                a1 = s3;
                a3 = 125;
                t0 = 0;
                jal(ctx, 0x40AE28u, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a0 = s4;
                a1 = s3;
                a3 = 127;
                t0 = 0;
                jal(ctx, 0x40AE48u, gen::fn_sub_40E3C0_0040e3c0);
                break;
            case 0x40AE58u:  // table[5]
                // 0x0040ae58
                charge(ctx, 4);
                lw(v0, s0, 0);
                v0 = v0 & 0x2;
                if (v0 == 0) {
                    // 0x0040ae68
                    charge(ctx, 1);
                    s2 = 1;
                }
                // 0x0040ae6c
                charge(ctx, 34);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a0 = s4;
                a1 = s3;
                a3 = 123;
                t0 = s2;
                jal(ctx, 0x40AE84u, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a0 = s4;
                a1 = s3;
                a3 = 124;
                t0 = s2;
                jal(ctx, 0x40AEA4u, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a0 = s4;
                a1 = s3;
                a3 = 126;
                t0 = 0;
                jal(ctx, 0x40AEC4u, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a0 = s4;
                a1 = s3;
                a3 = 128;
                t0 = 0;
                jal(ctx, 0x40AEE4u, gen::fn_sub_40E3C0_0040e3c0);
                break;
            case 0x40AEF4u:  // table[6]
                // 0x0040aef4
                charge(ctx, 4);
                lw(v1, s0, 4);
                v0 = si(-8);
                if (v1 != v0) {
                    // 0x0040afcc
                    charge(ctx, 50);
                    a0 = addiu(s4, 62);
                    a1 = addiu(s3, -28);
                    mtc1(zero, f12);
                    a2 = s1 & 0xFF;
                    a3 = 129;
                    t0 = 0;
                    jal(ctx, 0x40AFE4u, gen::fn_sub_40E3C0_0040e3c0);
                    a0 = addiu(s4, 62);
                    a1 = addiu(s3, -28);
                    mtc1(zero, f12);
                    a2 = s1 & 0xFF;
                    a3 = 131;
                    t0 = 0;
                    jal(ctx, 0x40B004u, gen::fn_sub_40E3C0_0040e3c0);
                    a0 = addiu(s4, 62);
                    a1 = addiu(s3, -28);
                    mtc1(zero, f12);
                    a2 = s1 & 0xFF;
                    a3 = 132;
                    t0 = 0;
                    jal(ctx, 0x40B024u, gen::fn_sub_40E3C0_0040e3c0);
                    a0 = addiu(s4, 62);
                    a1 = addiu(s3, -28);
                    mtc1(zero, f12);
                    a2 = s1 & 0xFF;
                    a3 = 133;
                    t0 = 0;
                    jal(ctx, 0x40B044u, gen::fn_sub_40E3C0_0040e3c0);
                    a0 = addiu(s4, 62);
                    a1 = addiu(s3, -28);
                    mtc1(zero, f12);
                    a2 = s1 & 0xFF;
                    a3 = 135;
                    t0 = 0;
                    jal(ctx, 0x40B064u, gen::fn_sub_40E3C0_0040e3c0);
                    a0 = addiu(s4, 62);
                    a1 = addiu(s3, -28);
                    mtc1(zero, f12);
                    a2 = s1 & 0xFF;
                    a3 = 136;
                    t0 = 0;
                    jal(ctx, 0x40B084u, gen::fn_sub_40E3C0_0040e3c0);
                } else {
                    // 0x0040af04
                    charge(ctx, 50);
                    mtc1(zero, f12);
                    a2 = s1 & 0xFF;
                    a0 = s4;
                    a1 = s3;
                    a3 = 129;
                    t0 = 0;
                    jal(ctx, 0x40AF1Cu, gen::fn_sub_40E3C0_0040e3c0);
                    mtc1(zero, f12);
                    a2 = s1 & 0xFF;
                    a0 = s4;
                    a1 = s3;
                    a3 = 131;
                    t0 = 0;
                    jal(ctx, 0x40AF3Cu, gen::fn_sub_40E3C0_0040e3c0);
                    mtc1(zero, f12);
                    a2 = s1 & 0xFF;
                    a0 = s4;
                    a1 = s3;
                    a3 = 132;
                    t0 = 0;
                    jal(ctx, 0x40AF5Cu, gen::fn_sub_40E3C0_0040e3c0);
                    mtc1(zero, f12);
                    a2 = s1 & 0xFF;
                    a0 = s4;
                    a1 = s3;
                    a3 = 133;
                    t0 = 0;
                    jal(ctx, 0x40AF7Cu, gen::fn_sub_40E3C0_0040e3c0);
                    mtc1(zero, f12);
                    a2 = s1 & 0xFF;
                    a0 = s4;
                    a1 = s3;
                    a3 = 135;
                    t0 = 0;
                    jal(ctx, 0x40AF9Cu, gen::fn_sub_40E3C0_0040e3c0);
                    mtc1(zero, f12);
                    a2 = s1 & 0xFF;
                    a0 = s4;
                    a1 = s3;
                    a3 = 136;
                    t0 = 0;
                    jal(ctx, 0x40AFBCu, gen::fn_sub_40E3C0_0040e3c0);
                }
                break;
            case 0x40B094u:  // table[7]
                // 0x0040b094
                charge(ctx, 26);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a0 = s4;
                a1 = s3;
                a3 = 130;
                t0 = 0;
                jal(ctx, 0x40B0ACu, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a0 = s4;
                a1 = s3;
                a3 = 134;
                t0 = 0;
                jal(ctx, 0x40B0CCu, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a0 = s4;
                a1 = s3;
                a3 = 137;
                t0 = 0;
                jal(ctx, 0x40B0ECu, gen::fn_sub_40E3C0_0040e3c0);
                break;
            case 0x40B0FCu:  // table[9]
                // 0x0040b0fc
                charge(ctx, 18);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a0 = s4;
                a1 = s3;
                a3 = 149;
                t0 = 0;
                jal(ctx, 0x40B114u, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a0 = s4;
                a1 = s3;
                a3 = 150;
                t0 = 0;
                jal(ctx, 0x40B134u, gen::fn_sub_40E3C0_0040e3c0);
                break;
            case 0x40B144u:  // table[10]
                // 0x0040b144
                charge(ctx, 18);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a0 = s4;
                a1 = s3;
                a3 = 151;
                t0 = 0;
                jal(ctx, 0x40B15Cu, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                a0 = s4;
                a1 = s3;
                a3 = 152;
                t0 = 0;
                jal(ctx, 0x40B17Cu, gen::fn_sub_40E3C0_0040e3c0);
                break;
            case 0x40B18Cu:  // table[13]
                // 0x0040b18c
                charge(ctx, 4);
                lw(a0, s0, 4);
                v1 = si(-8);
                if (a0 != v1) {
                    // 0x0040b284
                    charge(ctx, 5);
                    lhu(a0, a3, 16);
                    lw(v1, a2, 32);
                    v1 = sltu(a0, v1);
                    if (v1 == 0) {
                        // 0x0040b298
                        charge(ctx, 51);
                        lw(s0, a2, 40);
                        a0 = addiu(s4, -84);
                        a1 = addiu(s3, -28);
                        mtc1(zero, f12);
                        a2 = s1 & 0xFF;
                        v0 = 0x3F800000;
                        mtc1(v0, f14);
                        a3 = 138;
                        t0 = 0;
                        t1 = 0;
                        t2 = 0;
                        mov_s(f13, f12);
                        mov_s(f15, f14);
                        jal(ctx, 0x40B2CCu, gen::fn_sub_40E3F0_0040e3f0);
                        a0 = addiu(s4, -84);
                        a1 = addiu(s3, -28);
                        mtc1(zero, f12);
                        a2 = s1 & 0xFF;
                        v0 = 0x3F800000;
                        mtc1(v0, f14);
                        a3 = 139;
                        t0 = 0;
                        t1 = 0;
                        t2 = 0;
                        mov_s(f13, f12);
                        mov_s(f15, f14);
                        jal(ctx, 0x40B304u, gen::fn_sub_40E3F0_0040e3f0);
                        a0 = addiu(s4, 446);
                        v0 = sll(s0, 5);
                        v0 = subu(v0, s0);
                        v0 = sll(v0, 2);
                        v1 = addu(v0, s0);
                        v0 = 0xFFFF;
                        div(v1, v0);
                        mflo(v1);
                        v0 = addiu(s3, 100);
                        a1 = addu(v0, v1);
                        mtc1(zero, f12);
                        a2 = s1 & 0xFF;
                        v0 = 0x3F800000;
                        mtc1(v0, f14);
                        a3 = 140;
                        t0 = 0;
                        t1 = 0;
                        t2 = 0;
                        mov_s(f13, f12);
                        mov_s(f15, f14);
                        jal(ctx, 0x40B35Cu, gen::fn_sub_40E3F0_0040e3f0);
                    }
                } else {
                    // 0x0040b19c
                    charge(ctx, 5);
                    lhu(a0, a3, 16);
                    lw(v1, a2, 32);
                    v1 = sltu(a0, v1);
                    if (v1 == 0) {
                        // 0x0040b1b0
                        charge(ctx, 53);
                        lw(s0, a2, 40);
                        mtc1(zero, f12);
                        a2 = s1 & 0xFF;
                        v0 = 0x3F800000;
                        mtc1(v0, f14);
                        a0 = s4;
                        a1 = s3;
                        a3 = 138;
                        t0 = 0;
                        t1 = 0;
                        t2 = 0;
                        mov_s(f13, f12);
                        mov_s(f15, f14);
                        jal(ctx, 0x40B1E4u, gen::fn_sub_40E3F0_0040e3f0);
                        mtc1(zero, f12);
                        a2 = s1 & 0xFF;
                        v0 = 0x3F800000;
                        mtc1(v0, f14);
                        a0 = s4;
                        a1 = s3;
                        a3 = 139;
                        t0 = 0;
                        t1 = 0;
                        t2 = 0;
                        mov_s(f13, f12);
                        mov_s(f15, f14);
                        jal(ctx, 0x40B21Cu, gen::fn_sub_40E3F0_0040e3f0);
                        a0 = addiu(s4, 530);
                        v0 = sll(s0, 5);
                        v0 = subu(v0, s0);
                        v0 = sll(v0, 2);
                        v1 = addu(v0, s0);
                        v0 = 0xFFFF;
                        div(v1, v0);
                        mflo(v1);
                        v0 = addiu(s3, 128);
                        a1 = addu(v0, v1);
                        mtc1(zero, f12);
                        a2 = s1 & 0xFF;
                        v0 = 0x3F800000;
                        mtc1(v0, f14);
                        a3 = 140;
                        t0 = 0;
                        t1 = 0;
                        t2 = 0;
                        mov_s(f13, f12);
                        mov_s(f15, f14);
                        jal(ctx, 0x40B274u, gen::fn_sub_40E3F0_0040e3f0);
                    }
                }
                break;
            case 0x40B364u:  // table[11, 12]
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v1.u());
                return;
            }
        }
    }
    // 0x0040b364 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0x120);
    return;
L_0040aa80_16:
    charge(ctx, 2);
    // 0x0040b364 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0x120);
    return;
L_0040ab70_26:
    charge(ctx, 2);
    // 0x0040b364 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0x120);
}

// 0x0040C6F0 sub_40C6F0 -- 676 bytes; frame 0x60: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Creates the facility shop menu (fclShopMisc.c, kind $a0 0..2): a 16-row nmCmdList (sub_3C58F0(0, 16, 7, 28)) with its
// work record (+4 kind, +8 sub_3DFEB0, +12 the list), fills the rows (sub_40C1E0 / sub_40C310), installs the update /
// draw / row callbacks, positions it, and enables its columns (sub_3D9820).
void sub_40C6F0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0040c6f0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    if (i64(s2) >= 0) {
        // 0x0040c710
        charge(ctx, 3);
        at = slti(s2, 3);
        if (at == 0) {
            goto L_0040c71c;
        }
        goto L_0040c730;
    }
L_0040c71c:
    charge(ctx, 5);
    a0 = 0x6B0000;
    a0 = addiu(a0, -4632);  // "fclShopMisc.c"
    a1 = 10157;
    jal(ctx, 0x40C728u, gen::fn_sub_19D3F0_0019d3f0);
L_0040c730:
    charge(ctx, 18);
    a0 = 0;
    a1 = 16;
    a2 = 7;
    a3 = 28;
    jal(ctx, 0x40C740u, gen::fn_sub_3C58F0_003c58f0);
    s1 = v0;
    lw(v0, v0, 36);
    lw(s0, v0, 68);
    sw(s1, s0, 12);
    a0 = s0;
    jal(ctx, 0x40C75Cu, gen::fn_sub_3DFEB0_003dfeb0);
    sw(v0, s0, 8);
    sw(s2, s0, 4);
    v0 = 2;
    if (s2 != v0) {
        // 0x0040c7e0
        charge(ctx, 8);
        v1 = sll(s2, 3);
        v0 = 0x6A0000;
        v0 = addiu(v0, 21392);  // "PQj"
        a1 = addu(v0, v1);
        a0 = s0;
        a2 = 0;
        jal(ctx, 0x40C7F8u, gen::fn_sub_40C1E0_0040c1e0);
    } else {
        // 0x0040c778
        charge(ctx, 4);
        a2 = 0x6B0000;
        a2 = addiu(a2, -1744);  // "\n"
        a1 = addiu(sp, 0x40);
        a0 = 4;
        for (;;) {
            // 0x0040c788
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
        // 0x0040c7ac
        charge(ctx, 13);
        v1 = sll(s2, 3);
        v0 = 0x6A0000;
        v0 = addiu(v0, 21392);  // "PQj"
        a1 = addu(v0, v1);
        a0 = s0;
        a2 = addiu(sp, 0x40);
        jal(ctx, 0x40C7C4u, gen::fn_sub_40C1E0_0040c1e0);
        a0 = s0;
        jal(ctx, 0x40C7D0u, gen::fn_sub_40C310_0040c310);
    }
    // 0x0040c800
    charge(ctx, 36);
    a0 = s1;
    jal(ctx, 0x40C804u, gen::fn_sub_3C6EE0_003c6ee0);
    a0 = s1;
    a1 = 0x410000;
    a1 = addiu(a1, -11472);  // &sub_40D330
    jal(ctx, 0x40C818u, gen::fn_nmCmdListSetUpdateFunc_003c5e80);
    a0 = s1;
    a1 = 0x410000;
    a1 = addiu(a1, -11344);  // &sub_40D3B0
    jal(ctx, 0x40C82Cu, gen::fn_nmCmdListSetDrawFunc_003c5e20);
    a0 = s1;
    a1 = 0x410000;
    a1 = addiu(a1, -11264);  // &nullsub_67
    jal(ctx, 0x40C840u, gen::fn_nmCmdListSetRowDrawFunc_003c5ee0);
    a0 = s1;
    a1 = 0x410000;
    a1 = addiu(a1, -15264);  // &sub_40C460
    jal(ctx, 0x40C854u, gen::fn_nmCmdListSetRowRemoveFunc_003c5f40);
    a0 = s1;
    a1 = 0;
    a2 = 0;
    jal(ctx, 0x40C868u, gen::fn_nmCmdListSetPosition_003c6d40);
    v1 = 10;
    lw(v0, s1, 36);
    sh(v1, v0, 6);
    lw(v0, s1, 36);
    sh(v1, v0, 8);
    v0 = 2;
    if (s2 != v0) {
        // 0x0040c8fc
        charge(ctx, 30);
        a0 = s0;
        a1 = 4;
        a2 = 0;
        jal(ctx, 0x40C908u, gen::fn_sub_3D9820_003d9820);
        a0 = s0;
        a1 = 0;
        a2 = 0;
        jal(ctx, 0x40C91Cu, gen::fn_sub_3D9820_003d9820);
        a0 = s0;
        a1 = 1;
        a2 = 0;
        jal(ctx, 0x40C930u, gen::fn_sub_3D9820_003d9820);
        a0 = s0;
        a1 = 2;
        a2 = 0;
        jal(ctx, 0x40C944u, gen::fn_sub_3D9820_003d9820);
        a0 = s0;
        a1 = 3;
        a2 = 0;
        jal(ctx, 0x40C958u, gen::fn_sub_3D9820_003d9820);
        a0 = s0;
        a1 = 7;
        a2 = 0;
        jal(ctx, 0x40C96Cu, gen::fn_sub_3D9820_003d9820);
    } else {
        // 0x0040c890
        charge(ctx, 27);
        a0 = s0;
        a1 = 4;
        a2 = 0;
        jal(ctx, 0x40C89Cu, gen::fn_sub_3D9820_003d9820);
        a0 = s0;
        a1 = 0;
        a2 = 0;
        jal(ctx, 0x40C8B0u, gen::fn_sub_3D9820_003d9820);
        a0 = s0;
        a1 = 1;
        a2 = 0;
        jal(ctx, 0x40C8C4u, gen::fn_sub_3D9820_003d9820);
        a0 = s0;
        a1 = 5;
        a2 = 0;
        jal(ctx, 0x40C8D8u, gen::fn_sub_3D9820_003d9820);
        a0 = s0;
        a1 = 6;
        a2 = 0;
        jal(ctx, 0x40C8ECu, gen::fn_sub_3D9820_003d9820);
    }
    // 0x0040c974 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    v0 = s0;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x0040C9A0 sub_40C9A0 -- 88 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Destroys the facility shop menu $a0 (fclShopMisc.c): releases +8 (sub_3DFF00) and the nmCmdList at +12.
void sub_40C9A0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0040c9a0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    if (s0 == 0) {
        // 0x0040c9b8
        charge(ctx, 5);
        a0 = 0x6B0000;
        a0 = addiu(a0, -4632);  // "fclShopMisc.c"
        a1 = 10194;
        jal(ctx, 0x40C9C4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0040c9cc
    charge(ctx, 11);
    lw(a0, s0, 8);
    jal(ctx, 0x40C9D0u, gen::fn_sub_3DFF00_003dff00);
    lw(a0, s0, 12);
    jal(ctx, 0x40C9DCu, gen::fn_nmCmdListDestroy_003c5a20);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0040CAD0 sub_40CAD0 -- 344 bytes; frame 0x80: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Draws the facility shop menu $a0: draws its nmCmdList, then each visible row except the cursor row through sub_3E0680
// with the row painter sub_40CC30, and finally the cursor row with the highlight bit.
void sub_40CAD0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0040cad0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = 0;
    lw(s2, a0, 12);
    a0 = s2;
    jal(ctx, 0x40CAF8u, gen::fn_nmCmdListDraw_003c6380);
    lw(v0, s2, 36);
    lw(s4, v0, 44);
    lw(s1, s2, 12);
    for (;;) {
        // 0x0040cb94
        charge(ctx, 2);
        if (s4 != 0) {
            backedge(ctx);
            // 0x0040cb14
            charge(ctx, 2);
            if (s4 != s1) {
                // 0x0040cb1c
                charge(ctx, 23);
                lw(v0, s4, 20);
                lw(s0, v0, 28);
                a0 = addiu(sp, 0x60);
                a1 = 0;
                a2 = 24;
                jal(ctx, 0x40CB30u, gen::fn_memset_00521408);
                lw(v1, s4, 20);
                lw(v0, v1, 0);
                sw(v0, sp, 0x60);
                lw(v0, v1, 4);
                sw(v0, sp, 0x64);
                lw(v0, s2, 36);
                lw(v0, v0, 28);
                sh(v0, sp, 0x68);
                sw(s2, sp, 0x6C);
                sw(s4, sp, 0x70);
                lw(a0, s0, 8);
                a1 = 0x410000;
                a1 = addiu(a1, -13264);  // &sub_40CC30
                a2 = addiu(sp, 0x60);
                jal(ctx, 0x40CB70u, gen::fn_sub_3E0680_003e0680);
            }
            // 0x0040cb78
            charge(ctx, 7);
            lw(s4, s4, 16);
            s3 = addiu(s3, 1);
            lw(v0, s2, 36);
            lw(v0, v0, 32);
            at = slt(s3, v0);
            if (at != 0) {
                continue;
            }
        }
        break;
    }
    // 0x0040cb9c
    charge(ctx, 35);
    lw(v0, s1, 20);
    lw(s0, v0, 28);
    a0 = addiu(sp, 0x60);
    a1 = 0;
    a2 = 24;
    jal(ctx, 0x40CBB0u, gen::fn_memset_00521408);
    lh(v0, sp, 0x6A);
    v0 = v0 | 0x1;
    sh(v0, sp, 0x6A);
    lw(v1, s1, 20);
    lw(v0, v1, 0);
    sw(v0, sp, 0x60);
    lw(v0, v1, 4);
    sw(v0, sp, 0x64);
    lw(v0, s2, 36);
    lw(v0, v0, 28);
    sh(v0, sp, 0x68);
    sw(s2, sp, 0x6C);
    sw(s1, sp, 0x70);
    lw(a0, s0, 8);
    a1 = 0x410000;
    a1 = addiu(a1, -13264);  // &sub_40CC30
    a2 = addiu(sp, 0x60);
    jal(ctx, 0x40CBFCu, gen::fn_sub_3E0680_003e0680);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x0040CC30 sub_40CC30 -- 1788 bytes; frame 0x80: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Facility shop row painter (sub_3E0680 callback): at the row origin with the scaled alpha, draws the row frame, name,
// price and icons (sub_40E3C0, sub_3B2CB0, sub_3DFF80, sub_406AA0, sub_40E3F0).
void sub_40CC30(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15};
    // 0x0040cc30
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a2;
    s0 = 0;
    lh(a3, a1, 20);
    lw(v1, a2, 0);
    s3 = addu(v1, a3);
    lh(a3, a1, 22);
    lw(v1, a2, 4);
    s2 = addu(v1, a3);
    lh(a2, a2, 8);
    lh(v1, a1, 38);
    mult(a2, a2, v1);
    v1 = 255;
    div(a2, v1);
    mflo(s1);
    if (s1 != 0) {
        // 0x0040cc90
        charge(ctx, 4);
        lh(v1, s4, 10);
        v1 = v1 & 0x1;
        if (v1 != 0) {
            // 0x0040cca0
            charge(ctx, 1);
            s0 = 1;
        }
        // 0x0040cca4
        charge(ctx, 7);
        lw(t0, s4, 12);
        lw(a3, t0, 36);
        lw(a2, a3, 68);
        lw(v1, a1, 16);
        at = sltiu(v1, 8);
        if (at != 0) {
            // 0x0040ccc0
            charge(ctx, 7);
            a1 = 0x7C0000;
            a1 = addiu(a1, -16752);  // &0x7BBE90
            v1 = sll(v1, 2);
            v1 = addu(v1, a1);
            lw(v1, v1, 0);
            switch (v1.u()) {
            case 0x40CCDCu:  // table[0]
                // 0x0040ccdc
                charge(ctx, 3);
                lw(a0, a2, 4);
                if (a0 == 0) {
                    // 0x0040cd58
                    charge(ctx, 18);
                    s5 = dsll32(s0, 16);
                    s5 = dsra32(s5, 16);
                    mtc1(zero, f12);
                    a2 = s1 & 0xFF;
                    a0 = s3;
                    a1 = s2;
                    a3 = 88;
                    t0 = s5;
                    jal(ctx, 0x40CD78u, gen::fn_sub_40E3C0_0040e3c0);
                    mtc1(zero, f12);
                    a2 = s1 & 0xFF;
                    a0 = s3;
                    a1 = s2;
                    a3 = 89;
                    t0 = s5;
                    jal(ctx, 0x40CD98u, gen::fn_sub_40E3C0_0040e3c0);
                } else {
                    // 0x0040cce8
                    charge(ctx, 3);
                    v1 = 2;
                    if (a0 != v1) {
                        // 0x0040ccf4
                        charge(ctx, 3);
                        v1 = 1;
                        if (a0 == v1) {
                            goto L_0040cd08;
                        }
                        // 0x0040cd00
                        charge(ctx, 2);
                        goto L_0040cda0;
                    }
                L_0040cd08:
                    charge(ctx, 20);
                    s5 = dsll32(s0, 16);
                    s5 = dsra32(s5, 16);
                    mtc1(zero, f12);
                    a2 = s1 & 0xFF;
                    a0 = s3;
                    a1 = s2;
                    a3 = 20;
                    t0 = s5;
                    jal(ctx, 0x40CD28u, gen::fn_sub_40E3C0_0040e3c0);
                    mtc1(zero, f12);
                    a2 = s1 & 0xFF;
                    a0 = s3;
                    a1 = s2;
                    a3 = 21;
                    t0 = s5;
                    jal(ctx, 0x40CD48u, gen::fn_sub_40E3C0_0040e3c0);
                }
            L_0040cda0:
                charge(ctx, 14);
                lwc1(f1, gp, -21240);  // 0x7CD9F8
                lwc1(f0, gp, -21236);  // 0x7CD9FC
                swc1(f1, sp, 0x78);
                swc1(f0, sp, 0x7C);
                lw(v1, s4, 12);
                lw(v1, v1, 36);
                lw(a1, v1, 68);
                lw(v1, s4, 16);
                lw(v1, v1, 20);
                lw(v1, v1, 28);
                lw(a0, v1, 0);
                a0 = a0 & 0x1;
                if (a0 != 0) {
                    // 0x0040cdd8
                    charge(ctx, 9);
                    mtc1(s1, f0);
                    cvt_s_w(f1, f0);
                    a0 = 0x3F000000;
                    mtc1(a0, f0);
                    mul_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(s1, f0);
                }
                // 0x0040cdfc
                charge(ctx, 3);
                lw(a1, a1, 4);
                if (a1 == 0) {
                    // 0x0040ce74
                    charge(ctx, 19);
                    a0 = addiu(s3, 64);
                    a1 = addiu(s2, 87);
                    mtc1(zero, f12);
                    v0 = si(-256);
                    a2 = s1 | v0;
                    v0 = dsll32(s0, 16);
                    v0 = dsra32(v0, 16);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, sp);
                    lb(a3, v0, 120);
                    lw(v0, v1, 4);
                    t0 = 1;
                    lw(t1, v0, 8);
                    t2 = 16;
                    t3 = 0;
                    jal(ctx, 0x40CEB0u, gen::fn_sub_3B2CB0_003b2cb0);
                } else {
                    // 0x0040ce08
                    charge(ctx, 3);
                    a0 = 2;
                    if (a1 != a0) {
                        // 0x0040ce14
                        charge(ctx, 3);
                        a0 = 1;
                        if (a1 == a0) {
                            goto L_0040ce28;
                        }
                        // 0x0040ce20
                        charge(ctx, 2);
                        break;
                    }
                L_0040ce28:
                    charge(ctx, 19);
                    a0 = addiu(s3, 64);
                    a1 = addiu(s2, 97);
                    mtc1(zero, f12);
                    v0 = si(-256);
                    a2 = s1 | v0;
                    v0 = dsll32(s0, 16);
                    v0 = dsra32(v0, 16);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, sp);
                    lb(a3, v0, 120);
                    lw(v0, v1, 4);
                    t0 = 1;
                    lw(t1, v0, 8);
                    t2 = 16;
                    t3 = 0;
                    jal(ctx, 0x40CE64u, gen::fn_sub_3B2CB0_003b2cb0);
                }
                break;
            case 0x40CEC0u:  // table[1]
                // 0x0040cec0
                charge(ctx, 5);
                a1 = 0;
                jal(ctx, 0x40CEC4u, gen::fn_sub_3DFF80_003dff80);
                if (v0 != 0) {
                    // 0x0040ced4
                    charge(ctx, 10);
                    lh(v1, v0, 22);
                    s0 = addu(s2, v1);
                    lh(v1, v0, 20);
                    s2 = addu(s3, v1);
                    lw(v1, s4, 12);
                    lw(v1, v1, 36);
                    lw(v1, v1, 68);
                    lw(a0, v1, 4);
                    if (a0 == 0) {
                        // 0x0040cf64
                        charge(ctx, 18);
                        mtc1(zero, f12);
                        a2 = s1 & 0xFF;
                        a0 = s2;
                        a1 = s0;
                        a3 = 93;
                        t0 = 0;
                        jal(ctx, 0x40CF7Cu, gen::fn_sub_40E3C0_0040e3c0);
                        mtc1(zero, f12);
                        a2 = s1 & 0xFF;
                        a0 = s2;
                        a1 = s0;
                        a3 = 94;
                        t0 = 0;
                        jal(ctx, 0x40CF9Cu, gen::fn_sub_40E3C0_0040e3c0);
                    } else {
                        // 0x0040cefc
                        charge(ctx, 3);
                        v1 = 2;
                        if (a0 != v1) {
                            // 0x0040cf08
                            charge(ctx, 3);
                            v1 = 1;
                            if (a0 == v1) {
                                goto L_0040cf1c;
                            }
                            // 0x0040cf14
                            charge(ctx, 2);
                            break;
                        }
                    L_0040cf1c:
                        charge(ctx, 18);
                        mtc1(zero, f12);
                        a2 = s1 & 0xFF;
                        a0 = s2;
                        a1 = s0;
                        a3 = 22;
                        t0 = 0;
                        jal(ctx, 0x40CF34u, gen::fn_sub_40E3C0_0040e3c0);
                        mtc1(zero, f12);
                        a2 = s1 & 0xFF;
                        a0 = s2;
                        a1 = s0;
                        a3 = 23;
                        t0 = 0;
                        jal(ctx, 0x40CF54u, gen::fn_sub_40E3C0_0040e3c0);
                    }
                }
                break;
            case 0x40CFACu:  // table[2]
                // 0x0040cfac
                charge(ctx, 3);
                lw(a0, a2, 4);
                if (a0 == 0) {
                    // 0x0040cff8
                    charge(ctx, 19);
                    v0 = 0x40000000;
                    mtc1(v0, f12);
                    a2 = s1 & 0xFF;
                    a0 = s3;
                    a1 = s2;
                    a3 = 84;
                    t0 = 0;
                    jal(ctx, 0x40D014u, gen::fn_sub_40E3C0_0040e3c0);
                    mtc1(zero, f12);
                    a2 = s1 & 0xFF;
                    a0 = s3;
                    a1 = s2;
                    a3 = 85;
                    t0 = 0;
                    jal(ctx, 0x40D034u, gen::fn_sub_40E3C0_0040e3c0);
                } else {
                    // 0x0040cfb8
                    charge(ctx, 3);
                    v1 = 1;
                    if (a0 == v1) {
                        // 0x0040cfcc
                        charge(ctx, 11);
                        v0 = 0x40000000;
                        mtc1(v0, f12);
                        a2 = s1 & 0xFF;
                        a0 = s3;
                        a1 = s2;
                        a3 = 18;
                        t0 = 0;
                        jal(ctx, 0x40CFE8u, gen::fn_sub_40E3C0_0040e3c0);
                    } else {
                        // 0x0040cfc4
                        charge(ctx, 2);
                    }
                }
                break;
            case 0x40D044u:  // table[3]
                // 0x0040d044
                charge(ctx, 3);
                lw(a0, a2, 4);
                if (a0 == 0) {
                    // 0x0040d08c
                    charge(ctx, 11);
                    v0 = 0x3F800000;
                    mtc1(v0, f12);
                    a2 = s1 & 0xFF;
                    a0 = s3;
                    a1 = s2;
                    a3 = 86;
                    t0 = 0;
                    jal(ctx, 0x40D0A8u, gen::fn_sub_40E3C0_0040e3c0);
                } else {
                    // 0x0040d050
                    charge(ctx, 3);
                    v1 = 1;
                    if (a0 == v1) {
                        // 0x0040d064
                        charge(ctx, 10);
                        mtc1(zero, f12);
                        a2 = s1 & 0xFF;
                        a0 = s3;
                        a1 = s2;
                        a3 = 19;
                        t0 = 0;
                        jal(ctx, 0x40D07Cu, gen::fn_sub_40E3C0_0040e3c0);
                    } else {
                        // 0x0040d05c
                        charge(ctx, 2);
                    }
                }
                break;
            case 0x40D0B8u:  // table[5]
                // 0x0040d0b8
                charge(ctx, 11);
                v0 = 0x3F800000;
                mtc1(v0, f12);
                a2 = s1 & 0xFF;
                a0 = s3;
                a1 = s2;
                a3 = 2;
                t0 = 0;
                jal(ctx, 0x40D0D4u, gen::fn_sub_40E3C0_0040e3c0);
                break;
            case 0x40D0E4u:  // table[4]
                // 0x0040d0e4
                charge(ctx, 3);
                lw(v1, a2, 4);
                if (v1 != 0) {
                    // 0x0040d0f0
                    charge(ctx, 11);
                    v0 = 0x41200000;
                    mtc1(v0, f12);
                    a2 = s1 & 0xFF;
                    a0 = s3;
                    a1 = s2;
                    a3 = 1;
                    t0 = 0;
                    jal(ctx, 0x40D10Cu, gen::fn_sub_40E3C0_0040e3c0);
                }
                break;
            case 0x40D11Cu:  // table[6]
                // 0x0040d11c
                charge(ctx, 7);
                a0 = s3;
                a1 = s2;
                a2 = s1;
                jal(ctx, 0x40D128u, gen::fn_sub_406AA0_00406aa0);
                break;
            case 0x40D138u:  // table[7]
                // 0x0040d138
                charge(ctx, 3);
                lw(v1, a2, 4);
                if (v1 != 0) {
                    // 0x0040d228
                    charge(ctx, 5);
                    lhu(a0, t0, 16);
                    lw(v1, a3, 32);
                    v1 = sltu(a0, v1);
                    if (v1 == 0) {
                        // 0x0040d23c
                        charge(ctx, 50);
                        lw(s0, a3, 40);
                        mtc1(zero, f12);
                        a2 = s1 & 0xFF;
                        v0 = 0x3F800000;
                        mtc1(v0, f14);
                        a0 = s3;
                        a1 = s2;
                        a3 = 24;
                        t0 = 0;
                        t1 = 0;
                        t2 = 0;
                        mov_s(f13, f12);
                        mov_s(f15, f14);
                        jal(ctx, 0x40D270u, gen::fn_sub_40E3F0_0040e3f0);
                        mtc1(zero, f12);
                        a2 = s1 & 0xFF;
                        v0 = 0x3F800000;
                        mtc1(v0, f14);
                        a0 = s3;
                        a1 = s2;
                        a3 = 25;
                        t0 = 0;
                        t1 = 0;
                        t2 = 0;
                        mov_s(f13, f12);
                        mov_s(f15, f14);
                        jal(ctx, 0x40D2A8u, gen::fn_sub_40E3F0_0040e3f0);
                        a0 = addiu(s3, 374);
                        v0 = sll(s0, 5);
                        v0 = subu(v0, s0);
                        v1 = sll(v0, 2);
                        v0 = 0xFFFF;
                        div(v1, v0);
                        mflo(v1);
                        v0 = addiu(s2, 84);
                        a1 = addu(v0, v1);
                        mtc1(zero, f12);
                        a2 = s1 & 0xFF;
                        v0 = 0x3F800000;
                        mtc1(v0, f14);
                        a3 = 26;
                        t0 = 0;
                        t1 = 0;
                        t2 = 0;
                        mov_s(f13, f12);
                        mov_s(f15, f14);
                        jal(ctx, 0x40D2FCu, gen::fn_sub_40E3F0_0040e3f0);
                    }
                } else {
                    // 0x0040d144
                    charge(ctx, 5);
                    lhu(a0, t0, 16);
                    lw(v1, a3, 32);
                    v1 = sltu(a0, v1);
                    if (v1 == 0) {
                        // 0x0040d158
                        charge(ctx, 52);
                        lw(s0, a3, 40);
                        mtc1(zero, f12);
                        a2 = s1 & 0xFF;
                        v0 = 0x3F800000;
                        mtc1(v0, f14);
                        a0 = s3;
                        a1 = s2;
                        a3 = 90;
                        t0 = 0;
                        t1 = 0;
                        t2 = 0;
                        mov_s(f13, f12);
                        mov_s(f15, f14);
                        jal(ctx, 0x40D18Cu, gen::fn_sub_40E3F0_0040e3f0);
                        mtc1(zero, f12);
                        a2 = s1 & 0xFF;
                        v0 = 0x3F800000;
                        mtc1(v0, f14);
                        a0 = s3;
                        a1 = s2;
                        a3 = 91;
                        t0 = 0;
                        t1 = 0;
                        t2 = 0;
                        mov_s(f13, f12);
                        mov_s(f15, f14);
                        jal(ctx, 0x40D1C4u, gen::fn_sub_40E3F0_0040e3f0);
                        a0 = addiu(s3, 374);
                        v0 = sll(s0, 5);
                        v0 = subu(v0, s0);
                        v1 = sll(v0, 2);
                        v0 = 0xFFFF;
                        div(v1, v0);
                        mflo(v1);
                        v0 = addiu(s2, 84);
                        a1 = addu(v0, v1);
                        mtc1(zero, f12);
                        a2 = s1 & 0xFF;
                        v0 = 0x3F800000;
                        mtc1(v0, f14);
                        a3 = 92;
                        t0 = 0;
                        t1 = 0;
                        t2 = 0;
                        mov_s(f13, f12);
                        mov_s(f15, f14);
                        jal(ctx, 0x40D218u, gen::fn_sub_40E3F0_0040e3f0);
                    }
                }
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v1.u());
                return;
            }
        }
    }
    // 0x0040d304 (the shared epilogue, written out on this path)
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

// 0x00464020 sub_464020 -- 248 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Collision query dispatch by the shape kind at $a1+24: 5 an atomic (its world bounding sphere, sub_460EC0), 4
// sub_4606B0, 3 a sphere (sub_460EC0), 1 sub_45F930; returns the world $a0.
void sub_464020(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x00464020
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    v0 = 5;
    sd(ra, sp, 0x40);
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
        // 0x004640b8
        charge(ctx, 17);
        link(ctx, 0x4640B8u);  // $ra first: the delay slot below depends on it
        lw(a0, s2, 0);
        call(ctx, gen::fn_atomicGetWorldBoundingSphere_004912b0);
        lwc1(f3, v0, 0);
        a2 = s2;
        lwc1(f2, v0, 4);
        a3 = s1;
        lwc1(f1, v0, 8);
        t0 = s0;
        lwc1(f0, v0, 12);
        a1 = addiu(sp, 0x50);
        a0 = s3;
        swc1(f3, sp, 0x50);
        swc1(f2, sp, 0x54);
        swc1(f1, sp, 0x58);
        link(ctx, 0x4640F0u);  // $ra first: the delay slot below depends on it
        swc1(f0, sp, 0x5C);
        call(ctx, gen::fn_sub_460EC0_00460ec0);
        v0 = s3;
    } else {
        // 0x00464054
        charge(ctx, 3);
        v0 = 4;
        if (v1 == v0) {
            // 0x004640a8
            charge(ctx, 4);
            jal(ctx, 0x4640A8u, gen::fn_sub_4606B0_004606b0);
            v0 = s3;
        } else {
            // 0x00464060
            charge(ctx, 3);
            v0 = 3;
            if (v1 == v0) {
                // 0x00464090
                charge(ctx, 6);
                a2 = s2;
                a3 = s1;
                t0 = s0;
                jal(ctx, 0x464098u, gen::fn_sub_460EC0_00460ec0);
                v0 = s3;
            } else {
                // 0x0046406c
                charge(ctx, 3);
                v0 = 1;
                if (v1 == v0) {
                    // 0x00464080
                    charge(ctx, 4);
                    jal(ctx, 0x464080u, gen::fn_sub_45F930_0045f930);
                    v0 = s3;
                } else {
                    // 0x00464078
                    charge(ctx, 2);
                    v0 = s3;
                }
            }
        }
    }
    // 0x004640fc (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x004663D0 sub_4663D0 -- 164 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Frees an animation-blend record $a0: its +12 / +16 buffers through the 0x96017C free hook unless owned (bits 0 / 1),
// clears +8..+16, releases +32 (sub_4B6EB0), returns the record to its free list (0x96018C hook, pool *0x7CE734), and
// clears the owner's plugin slot.
void sub_4663D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004663d0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a0, 0);
    lw(s0, a0, 20);
    v0 = v1 & 0x1;
    s1 = a0;
    if (v0 == 0) {
        // 0x004663f4
        charge(ctx, 3);
        v0 = v1 & 0x2;
        if (v0 == 0) {
            // 0x00466400
            charge(ctx, 4);
            v0 = 0x960000;
            lw(v0, v0, 380);  // 0x96017C
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x466408u);  // $ra = the return address
            lw(a0, s1, 12);
            call_ptr(ctx, jt);
        }
        // 0x00466410
        charge(ctx, 4);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        jt = v0.u();  // the target, read before the delay slot
        link(ctx, 0x466418u);  // $ra = the return address
        lw(a0, s1, 16);
        call_ptr(ctx, jt);
    }
    // 0x00466420
    charge(ctx, 12);
    sw(zero, s1, 12);
    sw(zero, s1, 8);
    sw(zero, s1, 16);
    link(ctx, 0x46642Cu);  // $ra first: the delay slot below depends on it
    lw(a0, s1, 32);
    call(ctx, gen::fn_sub_4B6EB0_004b6eb0);
    v0 = 0x960000;
    lw(a0, gp, -17852);  // 0x7CE734
    lw(v0, v0, 396);  // 0x96018C
    a1 = s1;
    jalr(ctx, 0x466440u, v0.u());
    if (s0 != 0) {
        // 0x00466450
        charge(ctx, 3);
        lw(v0, gp, -17856);  // 0x7CE730
        v0 = addu(s0, v0);
        sw(zero, v0, 4);
    }
    // 0x0046645c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    v0 = 0;
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00468DC0 sub_468DC0 -- 100 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Plugin-gated atomic setup: when the atomic's plugin word ($a0 + *0x7CE73C) is clear, installs the MatFX atomic
// pipeline and sets it; returns the atomic or 0 on failure.
void sub_468DC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00468dc0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, gp, -17844);  // 0x7CE73C
    s0 = addu(s1, v0);
    lw(v0, s0, 0);
    if (v0 == 0) {
        // 0x00468df0
        charge(ctx, 4);
        jal(ctx, 0x468DF0u, gen::fn_matfxSetAtomicPipeline_00469d60);
        if (v0 != 0) {
            // 0x00468e00
            charge(ctx, 3);
            v0 = 1;
            sw(v0, s0, 0);
            backedge(ctx);
            goto L_00468de8;
        }
        // 0x00468e0c
        charge(ctx, 1);
        v0 = 0;
        // 0x00468e10 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(ra, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
L_00468de8:
    charge(ctx, 2);
    v0 = s1;
    // 0x00468e10 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00469510 sub_469510 -- 124 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Sets the 2nd parameter on the first of the two 64-byte MatFX slots of type 2 (plugin offset *0x7CE738), then
// refreshes the material (sub_469B50); returns $a0.
void sub_469510(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00469510
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a2 = 0;
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, -17848);  // 0x7CE738
    s0 = a0;
    v0 = addu(s0, v0);
    lw(a0, v0, 0);
    v1 = 2;
    for (;;) {
        // 0x00469534
        charge(ctx, 6);
        v0 = a2 & 0xFF;
        v0 = sll(v0, 6);
        a3 = addu(a0, v0);
        lw(v0, a3, 32);
        if (v0 == v1) {
            goto L_0046954c_2;
        }
        // 0x00469554
        charge(ctx, 5);
        v0 = addiu(a2, 1);
        a2 = v0 & 0xFF;
        v0 = slti(a2, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00469568
    charge(ctx, 2);
    a3 = 0;
    sw(a1, a3, 12);  // 0xC
L_00469570:
    charge(ctx, 7);
    a0 = s0;
    jal(ctx, 0x469570u, gen::fn_sub_469B50_00469b50);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
    return;
L_0046954c_2:
    charge(ctx, 2);
    sw(a1, a3, 12);
    goto L_00469570;
}

// 0x0048DA30 sub_48DA30 -- 116 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Frees a record $a0 and its +20 / +16 buffers through the 0x96017C free hook; returns 1.
void sub_48DA30(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0048da30
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, a0, 20);
    if (a0 != 0) {
        // 0x0048da4c
        charge(ctx, 5);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        jalr(ctx, 0x48DA54u, v0.u());
        sw(zero, s0, 20);
    }
    // 0x0048da60
    charge(ctx, 3);
    lw(a0, s0, 16);
    if (a0 != 0) {
        // 0x0048da6c
        charge(ctx, 5);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        jalr(ctx, 0x48DA74u, v0.u());
        sw(zero, s0, 16);
    }
    // 0x0048da80
    charge(ctx, 9);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    a0 = s0;
    jalr(ctx, 0x48DA88u, v0.u());
    ld(ra, sp, 0x10);
    v0 = 1;
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0048DAB0 sub_48DAB0 -- 576 bytes; frame 0xA0: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Creates an n-vertex ($a0) spline / path object of kind $a1 (1 or 2): allocates the header with 12-byte points (+8
// count), fills it with sub_48B910 from the points $a2, and keeps a copy of them at +20; reports allocation errors
// through sub_4C1D10 / sub_4C1C50 and returns 0.
void sub_48DAB0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0048dab0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    v0 = 2;
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    s6 = a2;
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    s1 = a1;
    sq(s0, sp, 0x0);
    if (s1 == v0) {
        // 0x0048db48
        charge(ctx, 16);
        v0 = 0x30000;
        s3 = 0x960000;
        s4 = v0 | 0xC;
        v1 = addiu(s2, 2);
        v0 = sll(v1, 1);
        s3 = addiu(s3, 376);  // &0x960178
        v0 = addu(v0, v1);
        a1 = s4;
        v0 = sll(v0, 2);
        s5 = addiu(v0, 68);
        lw(v0, s3, 0);  // 0x960178
        a0 = s5;
        jalr(ctx, 0x48DB74u, v0.u());
        s0 = v0;
        if (s0 == 0) {
            // 0x0048dc4c
            charge(ctx, 11);
            v0 = 258;
            a1 = s5;
            sw(v0, sp, 0x90);
            v0 = lui(0x8000);
            a0 = v0 | 0x13;
            jal(ctx, 0x48DC5Cu, gen::fn_sub_4C1D10_004c1d10);
            sw(v0, sp, 0x94);
            a0 = addiu(sp, 0x90);
            jal(ctx, 0x48DC68u, gen::fn_sub_4C1C50_004c1c50);
            v0 = 0;
        } else {
            // 0x0048db88
            charge(ctx, 2);
            v0 = addiu(s2, 3);
            sw(v0, s0, 8);
        L_0048db90:
            charge(ctx, 10);
            sw(zero, s0, 16);
            v0 = 12;
            sb(zero, s0, 24);
            a0 = s0;
            sw(s1, s0, 12);
            a1 = s6;
            link(ctx, 0x48DBA8u);  // $ra first: the delay slot below depends on it
            sb(v0, s0, 0);
            call(ctx, gen::fn_sub_48B910_0048b910);
            if (v0 == 0) {
                // 0x0048dc78
                charge(ctx, 6);
                v0 = 0x960000;
                lw(v0, v0, 380);  // 0x96017C
                a0 = s0;
                jalr(ctx, 0x48DC80u, v0.u());
                v0 = 0;
            } else {
                // 0x0048dbb8
                charge(ctx, 11);
                v0 = 12;
                a1 = s4;
                sb(v0, s0, 0);
                v0 = sll(s2, 1);
                v1 = addu(v0, s2);
                lw(v0, s3, 0);
                s1 = sll(v1, 2);
                a0 = s1;
                jalr(ctx, 0x48DBD4u, v0.u());
                sw(v0, s0, 20);
                if (v0 == 0) {
                    // 0x0048dc90
                    charge(ctx, 14);
                    v0 = 0x960000;
                    lw(v0, v0, 380);  // 0x96017C
                    a0 = s0;
                    jalr(ctx, 0x48DC98u, v0.u());
                    v0 = 258;
                    a1 = s1;
                    sw(v0, sp, 0x80);
                    v0 = lui(0x8000);
                    a0 = v0 | 0x13;
                    jal(ctx, 0x48DCB0u, gen::fn_sub_4C1D10_004c1d10);
                    sw(v0, sp, 0x84);
                    a0 = addiu(sp, 0x80);
                    jal(ctx, 0x48DCBCu, gen::fn_sub_4C1C50_004c1c50);
                    v0 = 0;
                } else {
                    // 0x0048dbe4
                    charge(ctx, 8);
                    lw(a0, s0, 20);
                    v0 = sll(s2, 1);
                    v0 = addu(v0, s2);
                    a1 = s6;
                    a2 = sll(v0, 2);
                    jal(ctx, 0x48DBF4u, gen::fn_memcpy_00521250);
                    v0 = s0;
                }
            }
        }
    } else {
        // 0x0048dae8
        charge(ctx, 3);
        a0 = 1;
        if (s1 == a0) {
            // 0x0048dafc
            charge(ctx, 16);
            v0 = 0x30000;
            s3 = 0x960000;
            s4 = v0 | 0xC;
            v1 = addiu(s2, 1);
            v0 = sll(v1, 1);
            s3 = addiu(s3, 376);  // &0x960178
            v0 = addu(v0, v1);
            a1 = s4;
            v0 = sll(v0, 2);
            s5 = addiu(v0, 68);
            lw(v0, s3, 0);  // 0x960178
            a0 = s5;
            jalr(ctx, 0x48DB28u, v0.u());
            s0 = v0;
            if (s0 != 0) {
                // 0x0048db3c
                charge(ctx, 3);
                v0 = addiu(s2, 2);
                sw(v0, s0, 8);
                goto L_0048db90;
            }
            // 0x0048dc20
            charge(ctx, 11);
            v0 = 258;
            a1 = s5;
            sw(v0, sp, 0x98);
            v0 = lui(0x8000);
            a0 = v0 | 0x13;
            jal(ctx, 0x48DC30u, gen::fn_sub_4C1D10_004c1d10);
            sw(v0, sp, 0x9C);
            a0 = addiu(sp, 0x98);
            jal(ctx, 0x48DC3Cu, gen::fn_sub_4C1C50_004c1c50);
            v0 = 0;
        } else {
            // 0x0048daf4
            charge(ctx, 2);
            v0 = 258;
            // 0x0048dc04
            charge(ctx, 7);
            link(ctx, 0x48DC04u);  // $ra first: the delay slot below depends on it
            sw(v0, sp, 0x88);
            call(ctx, gen::fn_sub_4C1D10_004c1d10);
            sw(v0, sp, 0x8C);
            a0 = addiu(sp, 0x88);
            jal(ctx, 0x48DC10u, gen::fn_sub_4C1C50_004c1c50);
            v0 = 0;
        }
    }
    // 0x0048dcc8 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// 0x0048EF80 sub_48EF80 -- 20 bytes; leaf frame (no stack)
// Returns the $a1-th word of the array at $a0+12.
void sub_48EF80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0048ef80
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, a0, 12);
    v1 = sll(a1, 2);
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
}

// 0x004A9BF0 sub_4A9BF0 -- 396 bytes; frame 0x30: s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Resets the current camera matrix (0x95EDF0[*0x95EE70]) to identity, flags it (0x20003) and clears the projection-
// dirty words 0x95EF50 / 0x95EF64. Returns 1.
void sub_4A9BF0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29};
    // 0x004a9bf0
    enter(ctx, 99);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v1 = 0x960000;
    sq(s2, sp, 0x20);
    v0 = 0x960000;
    sq(s1, sp, 0x10);
    v1 = addiu(v1, -4624);  // &0x95EDF0
    sq(s0, sp, 0x0);
    a0 = 0x3F800000;
    lw(v0, v0, -4496);  // 0x95EE70
    s0 = 0x960000;
    t9 = 0x960000;
    t8 = 0x960000;
    t7 = 0x960000;
    t6 = 0x960000;
    t5 = 0x960000;
    t4 = 0x960000;
    t3 = 0x960000;
    t2 = 0x960000;
    t1 = 0x960000;
    t0 = 0x960000;
    v0 = sll(v0, 2);
    a3 = 0x960000;
    a1 = addu(v1, v0);
    a2 = 0x960000;
    lw(s2, a1, 0);
    v0 = 0x20000;
    s1 = v0 | 0x3;
    v0 = 1;
    sw(a0, s2, 40);
    a1 = 0x960000;
    lw(s0, s0, -4496);  // 0x95EE70
    s0 = sll(s0, 2);
    s0 = addu(v1, s0);
    lw(s0, s0, 0);
    sw(a0, s0, 20);
    lw(s0, t9, -4496);  // 0x95EE70
    s0 = sll(s0, 2);
    s0 = addu(v1, s0);
    lw(s0, s0, 0);
    sw(a0, s0, 0);
    lw(a0, t8, -4496);  // 0x95EE70
    a0 = sll(a0, 2);
    a0 = addu(v1, a0);
    lw(a0, a0, 0);
    sw(zero, a0, 16);
    lw(a0, t7, -4496);  // 0x95EE70
    a0 = sll(a0, 2);
    a0 = addu(v1, a0);
    lw(a0, a0, 0);
    sw(zero, a0, 8);
    lw(a0, t6, -4496);  // 0x95EE70
    a0 = sll(a0, 2);
    a0 = addu(v1, a0);
    lw(a0, a0, 0);
    sw(zero, a0, 4);
    lw(a0, t5, -4496);  // 0x95EE70
    a0 = sll(a0, 2);
    a0 = addu(v1, a0);
    lw(a0, a0, 0);
    sw(zero, a0, 36);
    lw(a0, t4, -4496);  // 0x95EE70
    a0 = sll(a0, 2);
    a0 = addu(v1, a0);
    lw(a0, a0, 0);
    sw(zero, a0, 32);
    lw(a0, t3, -4496);  // 0x95EE70
    a0 = sll(a0, 2);
    a0 = addu(v1, a0);
    lw(a0, a0, 0);
    sw(zero, a0, 24);
    lw(a0, t2, -4496);  // 0x95EE70
    a0 = sll(a0, 2);
    a0 = addu(v1, a0);
    lw(a0, a0, 0);
    sw(zero, a0, 56);
    lw(a0, t1, -4496);  // 0x95EE70
    a0 = sll(a0, 2);
    a0 = addu(v1, a0);
    lw(a0, a0, 0);
    sw(zero, a0, 52);
    lw(a0, t0, -4496);  // 0x95EE70
    a0 = sll(a0, 2);
    a0 = addu(v1, a0);
    lw(a0, a0, 0);
    sw(zero, a0, 48);
    lw(a0, a3, -4496);  // 0x95EE70
    a0 = sll(a0, 2);
    v1 = addu(v1, a0);
    lw(a0, v1, 0);
    lw(v1, a0, 12);
    v1 = v1 | s1;
    sw(v1, a0, 12);
    sw(zero, a2, -4272);  // 0x95EF50
    sw(zero, a1, -4252);  // 0x95EF64
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x004A9D80 sub_4A9D80 -- 416 bytes; frame 0xA0: ra sp+0x80, s5 sp+0x70 (sq), s4 sp+0x60 (sq), s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// Computes three 2D vectors for the view window ($a0 / $a1 / $a2) from the frustum extents at 0x95EE74.. through
// sub_4AAE60 and the view matrix at 0x95EED0. Returns 1.
void sub_4A9D80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24};
    // 0x004a9d80
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    v0 = 0x960000;
    sd(ra, sp, 0x80);
    v1 = 2;
    sq(s5, sp, 0x70);
    sq(s4, sp, 0x60);
    sq(s3, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    s2 = a0;
    sq(s0, sp, 0x20);
    s1 = a1;
    swc1(f24, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lw(v0, v0, -4220);  // 0x95EF84
    lw(v0, v0, 20);
    s0 = a2;
    if (v0 != v1) {
        // 0x004a9de4
        charge(ctx, 2);
        v0 = 0x960000;
        lwc1(f21, v0, -4264);  // 0x95EF58
    } else {
        // 0x004a9dd4
        charge(ctx, 4);
        v0 = 0x3F800000;
        mtc1(v0, f21);
    }
    // 0x004a9dec
    charge(ctx, 77);
    v1 = 0x960000;
    v0 = 0x960000;
    lwc1(f20, v1, -4492);  // 0x95EE74
    lwc1(f24, v0, -4488);  // 0x95EE78
    v1 = 0x960000;
    v0 = 0x960000;
    lwc1(f22, v0, -4480);  // 0x95EE80
    link(ctx, 0x4A9E08u);  // $ra first: the delay slot below depends on it
    lwc1(f23, v1, -4484);
    call(ctx, gen::fn_sub_4AAE60_004aae60);
    div_s(f0, f20, f23);
    s5 = 0x960000;
    s5 = addiu(s5, -4400);  // &0x95EED0
    a0 = addiu(sp, 0x90);
    s4 = addiu(sp, 0x94);
    s3 = addiu(sp, 0x98);
    a1 = a0;
    a2 = s5;
    sw(zero, s4, 0);
    sw(zero, s3, 0);
    neg_s(f1, f21);
    mul_s(f0, f1, f0);
    link(ctx, 0x4A9E48u);  // $ra first: the delay slot below depends on it
    swc1(f0, sp, 0x90);
    call(ctx, gen::fn_sub_4C6C60_004c6c60);
    div_s(f0, f24, f22);
    a0 = addiu(sp, 0x90);
    a2 = s5;
    a1 = a0;
    lwc1(f1, sp, 0x90);
    mul_s(f0, f21, f0);
    swc1(f1, s2, 0);
    lwc1(f1, s4, 0);
    swc1(f1, s2, 4);
    swc1(f0, s4, 0);
    sw(zero, sp, 0x90);
    link(ctx, 0x4A9E84u);  // $ra first: the delay slot below depends on it
    sw(zero, s3, 0);
    call(ctx, gen::fn_sub_4C6C60_004c6c60);
    v0 = 0x3F000000;
    a0 = addiu(sp, 0x90);
    lwc1(f3, sp, 0x90);
    a2 = s5;
    mtc1(v0, f2);
    a1 = a0;
    neg_s(f0, f24);
    mul_s(f1, f2, f20);
    mul_s(f0, f2, f0);
    swc1(f3, s1, 0);
    lwc1(f2, s4, 0);
    mul_s(f1, f1, f21);
    swc1(f2, s1, 4);
    mul_s(f0, f0, f21);
    sw(zero, s3, 0);
    swc1(f1, sp, 0x90);
    link(ctx, 0x4A9ECCu);  // $ra first: the delay slot below depends on it
    swc1(f0, s4, 0);
    call(ctx, gen::fn_sub_4C6BE0_004c6be0);
    lwc1(f0, sp, 0x90);
    v0 = 1;
    swc1(f0, s0, 0);
    lwc1(f0, s4, 0);
    swc1(f0, s0, 4);
    ld(ra, sp, 0x80);
    lwc1(f24, sp, 0x10);
    lq(s5, sp, 0x70);
    lwc1(f23, sp, 0xC);
    lq(s4, sp, 0x60);
    lwc1(f22, sp, 0x8);
    lq(s3, sp, 0x50);
    lwc1(f21, sp, 0x4);
    lq(s2, sp, 0x40);
    lwc1(f20, sp, 0x0);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    sp = addiu(sp, 0xA0);
}

// 0x004A9F20 sub_4A9F20 -- 924 bytes; frame 0xB0: ra sp+0x70, s4 sp+0x60 (sq), s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0, f25 sp+0x88
// kwlnInitRenderer: sets up the view: identity view and camera matrices, the window vectors from sub_4A9D80 scaled by
// the aspect ($f12 / $f13), translates / rotates the view matrix 0x95EDB0 (sub_4C35D0 / sub_4C33D0), stores the window
// at 0x95EF70.. and rebuilds the projection (sub_4AAD50). Returns 1.
void sub_4A9F20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25};
    // 0x004a9f20
    enter(ctx, 231);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    a0 = 0x3F800000;
    sd(ra, sp, 0x70);
    v0 = 0x960000;
    sq(s4, sp, 0x60);
    v1 = 0x960000;
    sq(s3, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    swc1(f25, sp, 0x14);
    swc1(f24, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    sw(a0, v0, -4648);  // 0x95EDD8
    mov_s(f23, f12);
    v0 = 0x960000;
    sw(a0, v1, -4668);  // 0x95EDC4
    sw(a0, v0, -4688);  // 0x95EDB0
    v1 = 0x960000;
    v0 = 0x960000;
    sw(zero, v1, -4672);  // 0x95EDC0
    sw(zero, v0, -4680);  // 0x95EDB8
    v1 = 0x960000;
    v0 = 0x960000;
    sw(zero, v1, -4684);  // 0x95EDB4
    sw(zero, v0, -4652);  // 0x95EDD4
    v1 = 0x960000;
    v0 = 0x960000;
    sw(zero, v1, -4656);  // 0x95EDD0
    sw(zero, v0, -4664);  // 0x95EDC8
    v1 = 0x960000;
    v0 = 0x960000;
    sw(zero, v1, -4632);  // 0x95EDE8
    sw(zero, v0, -4636);  // 0x95EDE4
    v1 = 0x960000;
    v0 = 0x960000;
    sw(zero, v1, -4640);  // 0x95EDE0
    lw(a0, v0, -4676);  // 0x95EDBC
    v1 = 0x20000;
    v1 = v1 | 0x3;
    mov_s(f22, f13);
    mov_s(f21, f14);
    mov_s(f20, f15);
    v0 = 0x960000;
    v1 = a0 | v1;
    link(ctx, 0x4A9FE0u);  // $ra first: the delay slot below depends on it
    sw(v1, v0, -4676);
    call(ctx, gen::fn_sub_4AAA60_004aaa60);
    v0 = 0x960000;
    v1 = 0x3F800000;
    lw(a0, v0, -4496);  // 0x95EE70
    s2 = 0x960000;
    s1 = 0x960000;
    s0 = 0x960000;
    t9 = 0x960000;
    t8 = 0x960000;
    t7 = 0x960000;
    t6 = 0x960000;
    t5 = 0x960000;
    t4 = 0x960000;
    t3 = 0x960000;
    t2 = 0x960000;
    v0 = 0x960000;
    a0 = sll(a0, 2);
    v0 = addiu(v0, -4624);  // &0x95EDF0
    t1 = 0x960000;
    a0 = addu(v0, a0);
    t0 = 0x960000;
    lw(s4, a0, 0);
    a3 = 0x960000;
    a1 = addiu(sp, 0xA0);
    a2 = addiu(sp, 0x98);
    sw(v1, s4, 40);
    a0 = 0x20000;
    lw(s2, s2, -4496);  // 0x95EE70
    s3 = a0 | 0x3;
    a0 = addiu(sp, 0xA8);
    s2 = sll(s2, 2);
    s2 = addu(v0, s2);
    lw(s2, s2, 0);
    sw(v1, s2, 20);
    lw(s1, s1, -4496);  // 0x95EE70
    s1 = sll(s1, 2);
    s1 = addu(v0, s1);
    lw(s1, s1, 0);
    sw(v1, s1, 0);
    lw(v1, s0, -4496);  // 0x95EE70
    v1 = sll(v1, 2);
    v1 = addu(v0, v1);
    lw(v1, v1, 0);
    sw(zero, v1, 16);
    lw(v1, t9, -4496);  // 0x95EE70
    v1 = sll(v1, 2);
    v1 = addu(v0, v1);
    lw(v1, v1, 0);
    sw(zero, v1, 8);
    lw(v1, t8, -4496);  // 0x95EE70
    v1 = sll(v1, 2);
    v1 = addu(v0, v1);
    lw(v1, v1, 0);
    sw(zero, v1, 4);
    lw(v1, t7, -4496);  // 0x95EE70
    v1 = sll(v1, 2);
    v1 = addu(v0, v1);
    lw(v1, v1, 0);
    sw(zero, v1, 36);
    lw(v1, t6, -4496);  // 0x95EE70
    v1 = sll(v1, 2);
    v1 = addu(v0, v1);
    lw(v1, v1, 0);
    sw(zero, v1, 32);
    lw(v1, t5, -4496);  // 0x95EE70
    v1 = sll(v1, 2);
    v1 = addu(v0, v1);
    lw(v1, v1, 0);
    sw(zero, v1, 24);
    lw(v1, t4, -4496);  // 0x95EE70
    v1 = sll(v1, 2);
    v1 = addu(v0, v1);
    lw(v1, v1, 0);
    sw(zero, v1, 56);
    lw(v1, t3, -4496);  // 0x95EE70
    v1 = sll(v1, 2);
    v1 = addu(v0, v1);
    lw(v1, v1, 0);
    sw(zero, v1, 52);
    lw(v1, t2, -4496);  // 0x95EE70
    v1 = sll(v1, 2);
    v1 = addu(v0, v1);
    lw(v1, v1, 0);
    sw(zero, v1, 48);
    lw(v1, t1, -4496);  // 0x95EE70
    v1 = sll(v1, 2);
    v0 = addu(v0, v1);
    lw(v1, v0, 0);
    lw(v0, v1, 12);
    v0 = v0 | s3;
    sw(v0, v1, 12);
    sw(zero, t0, -4272);  // 0x95EF50
    link(ctx, 0x4AA154u);  // $ra first: the delay slot below depends on it
    sw(zero, a3, -4252);
    call(ctx, gen::fn_sub_4A9D80_004a9d80);
    v1 = 0x960000;
    v0 = 0x960000;
    lwc1(f7, v1, -4484);  // 0x95EE7C
    s0 = addiu(sp, 0x90);
    lwc1(f6, v0, -4480);  // 0x95EE80
    a0 = 0x960000;
    lwc1(f1, sp, 0x98);
    s1 = addiu(sp, 0x8C);
    lwc1(f0, sp, 0x9C);
    sw(zero, s0, 0);
    lwc1(f5, sp, 0xA8);
    a0 = addiu(a0, -4688);  // &0x95EDB0
    lwc1(f3, sp, 0xA0);
    a1 = addiu(sp, 0x88);
    div_s(f7, f7, f21);
    v1 = addiu(sp, 0xAC);
    v0 = addiu(sp, 0xA4);
    a2 = 1;
    div_s(f6, f6, f20);
    swc1(f1, sp, 0x88);
    mul_s(f1, f5, f7);
    mul_s(f3, f3, f6);
    lwc1(f4, v1, 0);
    swc1(f0, s1, 0);
    lwc1(f2, v0, 0);
    swc1(f1, sp, 0xA8);
    swc1(f3, sp, 0xA0);
    mul_s(f0, f4, f7);
    mula_s(f0, f0);
    swc1(f0, v1, 0);
    mul_s(f0, f2, f6);
    madd_s(f1, f1, f1);
    swc1(f0, v0, 0);
    mula_s(f0, f0);
    madd_s(f0, f3, f3);
    sqrt_s(f25, f1);
    sqrt_s(f24, f0);
    jal(ctx, 0x4AA200u, gen::fn_sub_4C35D0_004c35d0);
    v0 = 0x3F800000;
    a0 = 0x960000;
    a0 = addiu(a0, -4688);  // &0x95EDB0
    sw(v0, s0, 0);
    a1 = addiu(sp, 0x88);
    a2 = 1;
    swc1(f25, sp, 0x88);
    link(ctx, 0x4AA224u);  // $ra first: the delay slot below depends on it
    swc1(f24, s1, 0);
    call(ctx, gen::fn_sub_4C33D0_004c33d0);
    neg_s(f0, f23);
    a0 = 0x960000;
    swc1(f0, sp, 0x88);
    a0 = addiu(a0, -4688);  // &0x95EDB0
    neg_s(f0, f22);
    a1 = addiu(sp, 0x88);
    swc1(f0, s1, 0);
    a2 = 1;
    link(ctx, 0x4AA24Cu);  // $ra first: the delay slot below depends on it
    sw(zero, s0, 0);
    call(ctx, gen::fn_sub_4C35D0_004c35d0);
    v1 = 0x960000;
    v0 = 0x960000;
    swc1(f23, v1, -4240);  // 0x95EF70
    swc1(f22, v0, -4236);  // 0x95EF74
    v1 = 0x960000;
    v0 = 0x960000;
    swc1(f21, v1, -4232);  // 0x95EF78
    link(ctx, 0x4AA270u);  // $ra first: the delay slot below depends on it
    swc1(f20, v0, -4228);
    call(ctx, gen::fn_sub_4AAD50_004aad50);
    v1 = 0x960000;
    v0 = 1;
    sw(zero, v1, -4272);  // 0x95EF50
    ld(ra, sp, 0x70);
    lwc1(f25, sp, 0x14);
    lq(s4, sp, 0x60);
    lwc1(f24, sp, 0x10);
    lq(s3, sp, 0x50);
    lwc1(f23, sp, 0xC);
    lq(s2, sp, 0x40);
    lwc1(f22, sp, 0x8);
    lq(s1, sp, 0x30);
    lwc1(f21, sp, 0x4);
    lq(s0, sp, 0x20);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0xB0);
}

// 0x004AA390 sub_4AA390 -- 56 bytes; leaf frame (no stack)
// Sets the far clip 0x95EF5C to $f12 when positive (clearing 0x95EF64); returns 1, else 0.
void sub_4AA390(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x004aa390
    enter(ctx, 5);  // entry check point + this block's cycles
    mtc1(zero, f0);
    c_le_s(f12, f0);
    if (!cond(ctx)) {
        // 0x004aa3ac
        charge(ctx, 5);
        v0 = 0x960000;
        v1 = 0x960000;
        sw(zero, v0, -4252);  // 0x95EF64
        swc1(f12, v1, -4260);  // 0x95EF5C
        v0 = 1;
    } else {
        // 0x004aa3a4
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004aa3c0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x004AA3D0 sub_4AA3D0 -- 56 bytes; leaf frame (no stack)
// Sets the near clip 0x95EF58 to $f12 when positive (clearing 0x95EF50); returns 1, else 0.
void sub_4AA3D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x004aa3d0
    enter(ctx, 5);  // entry check point + this block's cycles
    mtc1(zero, f0);
    c_le_s(f12, f0);
    if (!cond(ctx)) {
        // 0x004aa3ec
        charge(ctx, 5);
        v0 = 0x960000;
        v1 = 0x960000;
        sw(zero, v0, -4272);  // 0x95EF50
        swc1(f12, v1, -4264);  // 0x95EF58
        v0 = 1;
    } else {
        // 0x004aa3e4
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004aa400 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x004AE060 sub_4AE060 -- 16 bytes; leaf frame (no stack)
// Sets bit 1 of the flags at $a0+8.
void sub_4AE060(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x004ae060
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, 8);
    v1 = v1 | 0x2;
    sw(v1, a0, 8);
}

// 0x004AE110 sub_4AE110 -- 60 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Copies 16 bytes from $a1 to $a0+144 and sets bit 3 of $a0+8; returns $a0.
void sub_4AE110(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ae110
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a2 = 16;
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = addiu(s0, 144);
    jal(ctx, 0x4AE124u, gen::fn_memcpy_00521250);
    lw(v1, s0, 8);
    v0 = s0;
    v1 = v1 | 0x8;
    sw(v1, s0, 8);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x004B1A60 sub_4B1A60 -- 8 bytes; leaf frame (no stack)
// Returns the float at $a0+8 (in $f0).
void sub_4B1A60(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4};
    Fpr f0{ctx, 0};
    // 0x004b1a60
    enter(ctx, 2);  // entry check point + this block's cycles
    lwc1(f0, a0, 8);
}

// 0x004B1A70 sub_4B1A70 -- 12 bytes; leaf frame (no stack)
// Returns the float at *($a0+24) (in $f0).
void sub_4B1A70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    Fpr f0{ctx, 0};
    // 0x004b1a70
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, a0, 24);
    lwc1(f0, v0, 0);
}

// 0x004B3CC0 sub_4B3CC0 -- 276 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Runs the callback $a0+40 over the items of list $a0+32 (sub_4B4090) while it returns the item, guarded by bit 1 of
// $a0's flags; first caches the inverse raster size and aspect of the current camera (sub_4AA540) at +56..+64. Returns
// $a0, or 0 when the callback stopped.
void sub_4B3CC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x004b3cc0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a0, 0);
    v0 = v1 & 0x2;
    s0 = a0;
    if (v0 == 0) {
        // 0x004b3cec
        charge(ctx, 5);
        v0 = v1 | 0x2;
        link(ctx, 0x4B3CF0u);  // $ra first: the delay slot below depends on it
        sw(v0, s0, 0);
        call(ctx, gen::fn_sub_4AA540_004aa540);
        if (v0 == 0) {
            // 0x004b3dac
            charge(ctx, 4);
            sw(zero, s0, 60);
            sw(zero, s0, 56);
            sw(zero, s0, 64);
            backedge(ctx);
        } else {
            // 0x004b3d00
            charge(ctx, 15);
            lw(a0, v0, 96);
            v1 = 0x3F800000;
            mtc1(v1, f2);
            lwc1(f1, a0, 12);
            lwc1(f0, a0, 16);
            cvt_s_w(f1, f1);
            cvt_s_w(f0, f0);
            div_s(f1, f2, f1);
            div_s(f0, f2, f0);
            swc1(f1, s0, 60);
            swc1(f0, s0, 56);
            lwc1(f1, v0, 104);
            lwc1(f0, v0, 108);
            div_s(f0, f1, f0);
            swc1(f0, s0, 64);
        }
        // 0x004b3d3c
        charge(ctx, 6);
        lw(s1, s0, 32);
        a0 = s1;
        jal(ctx, 0x4B3D40u, gen::fn_sub_4B4090_004b4090);
        s2 = v0;
        if (s2 != 0) {
            for (;;) {
                // 0x004b3d54
                charge(ctx, 6);
                lw(v0, s0, 40);
                a0 = s0;
                a1 = s2;
                jalr(ctx, 0x4B3D5Cu, v0.u());
                if (v0 != s2) {
                    goto L_004b3d6c_6;
                }
                // 0x004b3d84
                charge(ctx, 5);
                a0 = s1;
                jal(ctx, 0x4B3D84u, gen::fn_sub_4B4090_004b4090);
                s2 = v0;
                if (s2 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x004b3d98
        charge(ctx, 5);
        lw(v1, s0, 0);
        v0 = si(-3);
        v0 = v1 & v0;
        sw(v0, s0, 0);
        backedge(ctx);
    }
    // 0x004b3ce4
    charge(ctx, 2);
    v0 = s0;
    // 0x004b3dbc (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
    return;
L_004b3d6c_6:
    charge(ctx, 6);
    lw(a0, s0, 0);
    v1 = si(-3);
    v0 = 0;
    v1 = a0 & v1;
    sw(v1, s0, 0);
    // 0x004b3dbc (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x004B45B0 sub_4B45B0 -- 368 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Resource-manager stream read: creates the object when $a0 is 0 (0x960188 hook, sub_4B4230), then reads its header and
// sections from stream $a1 (sub_4C1910, sub_4C18B0, sub_4B2F10, sub_4B4CC0, sub_4B3160, sub_4B3900, sub_4B3AC0,
// sub_4B4860) and walks it with sub_4B4BA0(sub_4B4450); 0 on a failed read.
void sub_4B45B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b45b0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    if (s1 == 0) {
        // 0x004b4698
        charge(ctx, 10);
        v0 = 0x30000;
        a0 = 0x960000;
        a1 = v0 | 0x1B1;
        v0 = 0x960000;
        lw(v0, v0, 392);  // 0x960188
        a0 = addiu(a0, -1384);  // &0x95FA98
        jalr(ctx, 0x4B46ACu, v0.u());
        s1 = v0;
        if (s1 == 0) {
            backedge(ctx);
        } else {
            // 0x004b46c0
            charge(ctx, 4);
            a0 = s1;
            jal(ctx, 0x4B46C0u, gen::fn_sub_4B4230_004b4230);
            backedge(ctx);
        }
    }
    // 0x004b45cc
    charge(ctx, 2);
    if (s1 != 0) {
        // 0x004b45d4
        charge(ctx, 6);
        a0 = s0;
        a1 = addiu(sp, 0x3C);
        a2 = 4;
        jal(ctx, 0x4B45DCu, gen::fn_sub_4C1910_004c1910);
        if (v0 == 0) {
            // 0x004b46d0
            charge(ctx, 2);
            v0 = 0;
        } else {
            // 0x004b45ec
            charge(ctx, 6);
            a0 = s0;
            a1 = addiu(s1, 72);
            a2 = 16;
            jal(ctx, 0x4B45F4u, gen::fn_sub_4C18B0_004c18b0);
            if (v0 == 0) {
                // 0x004b46d8
                charge(ctx, 2);
                v0 = 0;
            } else {
                // 0x004b4604
                charge(ctx, 5);
                a0 = s1;
                a1 = s0;
                jal(ctx, 0x4B4608u, gen::fn_sub_4B2F10_004b2f10);
                if (v0 == 0) {
                    // 0x004b46e0
                    charge(ctx, 2);
                    v0 = 0;
                } else {
                    // 0x004b4618
                    charge(ctx, 5);
                    a0 = s1;
                    a1 = s0;
                    jal(ctx, 0x4B461Cu, gen::fn_sub_4B4CC0_004b4cc0);
                    if (v0 == 0) {
                        // 0x004b46e8
                        charge(ctx, 2);
                        v0 = 0;
                    } else {
                        // 0x004b462c
                        charge(ctx, 5);
                        a0 = s1;
                        a1 = s0;
                        jal(ctx, 0x4B4630u, gen::fn_sub_4B3160_004b3160);
                        if (v0 == 0) {
                            // 0x004b46f0
                            charge(ctx, 2);
                            v0 = 0;
                        } else {
                            // 0x004b4640
                            charge(ctx, 5);
                            a0 = s1;
                            a1 = s0;
                            jal(ctx, 0x4B4644u, gen::fn_sub_4B3900_004b3900);
                            if (v0 == 0) {
                                // 0x004b46f8
                                charge(ctx, 2);
                                v0 = 0;
                            } else {
                                // 0x004b4654
                                charge(ctx, 5);
                                a0 = s1;
                                a1 = s0;
                                jal(ctx, 0x4B4658u, gen::fn_sub_4B3AC0_004b3ac0);
                                if (v0 == 0) {
                                    // 0x004b4700
                                    charge(ctx, 2);
                                    v0 = 0;
                                } else {
                                    // 0x004b4668
                                    charge(ctx, 5);
                                    a1 = s0;
                                    a0 = s1;
                                    jal(ctx, 0x4B466Cu, gen::fn_sub_4B4860_004b4860);
                                    if (v0 != 0) {
                                        // 0x004b467c
                                        charge(ctx, 5);
                                        a1 = 0x4B0000;
                                        a0 = s1;
                                        a1 = addiu(a1, 17488);  // &sub_4B4450
                                        a2 = 0;
                                        jal(ctx, 0x4B4688u, gen::fn_sub_4B4BA0_004b4ba0);
                                        goto L_004b4690;
                                    }
                                    // 0x004b4708
                                    charge(ctx, 1);
                                    v0 = 0;
                                }
                            }
                        }
                    }
                }
            }
        }
        // 0x004b470c (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(ra, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
        return;
    }
L_004b4690:
    charge(ctx, 2);
    v0 = s1;
    // 0x004b470c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x004B6980 sub_4B6980 -- 40 bytes; frame 0x10: ra sp+0x0
// Frees $a0 through the 0x96017C free hook; returns 1.
void sub_4B6980(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b6980
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x960000;
    sd(ra, sp, 0x0);
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x4B6990u, v0.u());
    ld(ra, sp, 0x0);
    v0 = 1;
    sp = addiu(sp, 0x10);
}

// 0x004C0240 sub_4C0240 -- 300 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Texture name flags: scans the name $a1 for the suffix tokens at 0x7CDD14 to build the raster format flags (1, 11, 6,
// 0xA, ...) and creates the texture for $a0 with them (sub_4C00F0, sub_4BFEA0).
void sub_4C0240(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c0240
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = 0;
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    s2 = a1;
    sq(s0, sp, 0x0);
    a0 = s2;
    a1 = addiu(gp, -20444);  // &0x7CDD14
    s1 = 0;
    s0 = 0;
    jal(ctx, 0x4C0274u, gen::fn_strstr_00524a50);
    if (v0 != 0) {
        // 0x004c0284
        charge(ctx, 1);
        s1 = 1;
    }
    // 0x004c0288
    charge(ctx, 5);
    a0 = s2;
    a1 = addiu(gp, -20440);  // &0x7CDD18
    jal(ctx, 0x4C028Cu, gen::fn_strstr_00524a50);
    if (v0 != 0) {
        // 0x004c029c
        charge(ctx, 1);
        s0 = 1;
    }
    // 0x004c02a0
    charge(ctx, 5);
    a0 = s2;
    a1 = addiu(gp, -20436);  // &0x7CDD1C
    jal(ctx, 0x4C02A4u, gen::fn_strstr_00524a50);
    if (v0 != 0) {
        // 0x004c02b4
        charge(ctx, 2);
        s4 = s4 | 0x1;
        if (s1 != 0) {
            // 0x004c02bc
            charge(ctx, 2);
            v0 = s4 | 0x2;
            s4 = v0 | 0x8;
        }
    }
    // 0x004c02c4
    charge(ctx, 5);
    a0 = s2;
    a1 = addiu(gp, -20432);  // &0x7CDD20
    jal(ctx, 0x4C02C8u, gen::fn_strstr_00524a50);
    if (v0 != 0) {
        // 0x004c02d8
        charge(ctx, 3);
        v0 = s4 | 0x2;
        s4 = v0 | 0x4;
        if (s1 != 0) {
            // 0x004c02e4
            charge(ctx, 1);
            s4 = s4 | 0x1;
        }
    }
    // 0x004c02e8
    charge(ctx, 5);
    a0 = s2;
    a1 = addiu(gp, -20428);  // &0x7CDD24
    jal(ctx, 0x4C02ECu, gen::fn_strstr_00524a50);
    if (v0 != 0) {
        // 0x004c02fc
        charge(ctx, 3);
        v0 = s4 | 0x2;
        s4 = v0 | 0x8;
        if (s1 != 0) {
            // 0x004c0308
            charge(ctx, 1);
            s4 = s4 | 0x1;
        }
        // 0x004c030c
        charge(ctx, 2);
        if (s0 != 0) {
            // 0x004c0314
            charge(ctx, 1);
            s4 = s4 | 0x4;
        }
    }
    // 0x004c0318
    charge(ctx, 4);
    a0 = s3;
    jal(ctx, 0x4C0318u, gen::fn_sub_4C00F0_004c00f0);
    if (v0 == 0) {
        // 0x004c0348
        charge(ctx, 2);
        v0 = 0;
        ld(ra, sp, 0x50);
    } else {
        // 0x004c0328
        charge(ctx, 8);
        a1 = s3;
        a2 = s4;
        a0 = v0;
        a3 = 0;
        t0 = 0;
        jal(ctx, 0x4C0338u, gen::fn_sub_4BFEA0_004bfea0);
        ld(ra, sp, 0x50);
    }
    // 0x004c0350 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x004C0370 sub_4C0370 -- 88 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Runs the destroy callback of the object $a0 (its +80 class, +44) under the semaphore at 0x7CE8C0, setting +56 = 1
// first. Returns 0.
void sub_4C0370(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c0370
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, a0, 80);
    lw(a0, gp, -17456);  // 0x7CE8C0
    s0 = addiu(v0, 40);
    jal(ctx, 0x4C038Cu, gen::fn__sceWaitSema_005031a0);
    v0 = 1;
    sw(v0, s1, 56);
    lw(v0, s0, 4);
    a0 = s1;
    jalr(ctx, 0x4C03A0u, v0.u());
    link(ctx, 0x4C03A8u);  // $ra first: the delay slot below depends on it
    lw(a0, gp, -17456);  // 0x7CE8C0
    call(ctx, gen::fn__sceSignalSema_00503180);
    ld(ra, sp, 0x20);
    v0 = 0;
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x004C3D10 sub_4C3D10 -- 460 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Free-list block allocator (data-referenced): scans the pool $a0's bitmap pages for a free slot of size $a0[0], else
// allocates a new page (header + bitmap + aligned slots) through the 0x960178 hook and links it in; returns the slot
// address or 0.
void sub_4C3D10(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c3d10
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v0 = 0;
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(s0, a0, 8);
    t0 = addiu(s1, 16);
    lw(t3, a0, 16);
    v1 = 128;
    a0 = 255;
    for (;;) {
        // 0x004c3d44
        charge(ctx, 2);
        if (t3 != t0) {
            // 0x004c3d4c
            charge(ctx, 2);
            if (v0 == 0) {
                // 0x004c3d54
                charge(ctx, 5);
                lw(t2, s1, 4);
                at = sltu(0, s0);
                a3 = addiu(t3, 8);
                t4 = 0;
                if (at != 0) {
                    // 0x004c3d68
                    charge(ctx, 2);
                    t1 = 0;
                    a2 = addu(t3, s0);
                    for (;;) {
                        // 0x004c3d70
                        charge(ctx, 4);
                        s2 = addu(a3, t4);
                        lbu(t7, s2, 0);
                        if (t7 == a0) {
                            // 0x004c3e18
                            charge(ctx, 2);
                            t2 = addiu(t2, -8);
                            backedge(ctx);
                        } else {
                            // 0x004c3d80
                            charge(ctx, 2);
                            s3 = 0;
                            for (;;) {
                                // 0x004c3d88
                                charge(ctx, 3);
                                at = sltiu(s3, 8);
                                if (at != 0) {
                                    // 0x004c3d94
                                    charge(ctx, 2);
                                    if (t2 != 0) {
                                        // 0x004c3d9c
                                        charge(ctx, 5);
                                        t5 = srav(v1, s3);
                                        t6 = t5 & 0xFF;
                                        t5 = t7 & t6;
                                        if (t5 == 0) {
                                            goto L_004c3de0;
                                        }
                                        // 0x004c3db0
                                        charge(ctx, 3);
                                        s3 = addiu(s3, 1);
                                        t2 = addiu(t2, -1);
                                        backedge(ctx);
                                        continue;
                                    }
                                }
                                break;
                            }
                        }
                    L_004c3dc0:
                        charge(ctx, 2);
                        if (v0 == 0) {
                            // 0x004c3dc8
                            charge(ctx, 4);
                            t4 = addiu(t4, 1);
                            t5 = sltu(t4, s0);
                            t1 = addiu(t1, 8);
                            if (t5 != 0) {
                                backedge(ctx);
                                continue;
                            }
                        }
                        break;
                    }
                }
                // 0x004c3dd8
                charge(ctx, 2);
                lw(t3, t3, 0);
                backedge(ctx);
                continue;
            }
        }
        break;
    }
    // 0x004c3e20
    charge(ctx, 2);
    if (v0 == 0) {
        // 0x004c3e30
        charge(ctx, 13);
        lw(v1, s1, 4);
        lw(v0, s1, 0);
        mult(a2, v1, v0);
        a0 = addiu(s0, 7);
        v0 = 0x960000;
        lw(v1, s1, 12);
        lw(v0, v0, 376);  // 0x960178
        a0 = addu(a0, a2);
        a0 = addu(v1, a0);
        jalr(ctx, 0x4C3E50u, v0.u());
        s3 = v0;
        if (s3 != 0) {
            // 0x004c3e64
            charge(ctx, 22);
            s2 = addiu(s3, 8);
            a1 = 0;
            a0 = s2;
            a2 = s0;
            jal(ctx, 0x4C3E70u, gen::fn_memset_00521408);
            lw(a1, s1, 16);
            a0 = addiu(s1, 16);
            v1 = 128;
            v0 = addu(s3, s0);
            sw(a1, s3, 0);
            sw(a0, s3, 4);
            lw(a0, s1, 16);
            sw(s3, a0, 4);
            sw(s3, s1, 16);
            sb(v1, s2, 0);
            lw(a0, s1, 12);
            v1 = addu(v0, a0);
            v0 = addiu(a0, -1);
            v1 = addiu(v1, 7);
            v0 = nor(v0, 0);
            v0 = v1 & v0;
            backedge(ctx);
            goto L_004c3e28;
        }
        // 0x004c3ebc
        charge(ctx, 2);
        v0 = 0;
        ld(ra, sp, 0x40);
        // 0x004c3ec4 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        return;
    }
L_004c3e28:
    charge(ctx, 2);
    ld(ra, sp, 0x40);
    // 0x004c3ec4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
    return;
L_004c3de0:
    charge(ctx, 13);
    v0 = t6 | t7;
    sb(v0, s2, 0);
    t5 = addu(t1, s3);
    lw(t6, s1, 12);
    lw(v0, s1, 0);
    t7 = addu(a2, t6);
    t6 = addiu(t6, -1);
    t7 = addiu(t7, 7);
    t6 = nor(t6, 0);
    t6 = t7 & t6;
    mult(v0, v0, t5);
    v0 = addu(t6, v0);
    backedge(ctx);
    goto L_004c3dc0;
}

// 0x004CD620 sub_4CD620 -- 304 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Raster / image copy: when $a0 and $a1 share the depth (+12), copies the palette (depth < 9) and each row ($a0+8 rows
// of the packed width) honouring the strides; otherwise converts through sub_4CD260; then copies bit 1 of $a1's flags.
// Returns $a0 or 0.
void sub_4CD620(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004cd620
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    lw(v1, a1, 12);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a0, 12);
    s4 = a1;
    if (v0 != v1) {
        // 0x004cd714
        charge(ctx, 4);
        jal(ctx, 0x4CD714u, gen::fn_sub_4CD260_004cd260);
        if (v0 != 0) {
            backedge(ctx);
        } else {
            // 0x004cd724
            charge(ctx, 2);
            s5 = 0;
            backedge(ctx);
        }
    } else {
        // 0x004cd654
        charge(ctx, 3);
        lw(a0, s5, 24);
        if (a0 != 0) {
            // 0x004cd660
            charge(ctx, 3);
            lw(a1, s4, 24);
            if (a1 != 0) {
                // 0x004cd66c
                charge(ctx, 3);
                at = slti(v1, 9);
                if (at != 0) {
                    // 0x004cd678
                    charge(ctx, 4);
                    v0 = 1;
                    v0 = sllv(v0, v1);
                    a2 = sll(v0, 2);
                    jal(ctx, 0x4CD680u, gen::fn_memcpy_00521250);
                }
            }
        }
        // 0x004cd688
        charge(ctx, 11);
        lw(v1, s5, 12);
        lw(v0, s5, 4);
        v1 = addiu(v1, 7);
        v1 = sra(v1, 3);
        mult(s0, v1, v0);
        lw(s2, s4, 20);
        lw(s1, s5, 20);
        lw(v0, s5, 8);
        at = slt(0, v0);
        s3 = 0;
        if (at != 0) {
            for (;;) {
                // 0x004cd6b4
                charge(ctx, 12);
                a0 = s1;
                a1 = s2;
                a2 = s0;
                jal(ctx, 0x4CD6BCu, gen::fn_memcpy_00521250);
                lw(v0, s5, 8);
                s3 = addiu(s3, 1);
                lw(a0, s5, 16);
                lw(v1, s4, 16);
                v0 = slt(s3, v0);
                s1 = addu(s1, a0);
                s2 = addu(s2, v1);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004cd6e4
            charge(ctx, 1);
        }
    }
    // 0x004cd6e8
    charge(ctx, 11);
    lw(v1, s4, 0);
    lw(a2, s5, 0);
    a1 = si(-3);
    v0 = s5;
    a0 = v1 & 0x2;
    v1 = a2 & a1;
    sw(v1, s5, 0);
    lw(v1, s5, 0);
    v1 = v1 | a0;
    sw(v1, s5, 0);
    // 0x004cd72c
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

// 0x004D0B60 sub_4D0B60 -- 28 bytes; leaf frame (no stack)
// Sets the word at plugin offset +28 of the global record 0x960070 + *0x7CE950. Returns 1.
void sub_4D0B60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x004d0b60
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(a1, gp, -17312);  // 0x7CE950
    v1 = 0x960000;
    v1 = addiu(v1, 112);  // &0x960070
    v0 = 1;
    v1 = addu(v1, a1);
    sw(a0, v1, 28);
}

// 0x004D0B80 sub_4D0B80 -- 24 bytes; leaf frame (no stack)
// Returns the word at plugin offset +28 of 0x960070 + *0x7CE950.
void sub_4D0B80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, gp{ctx, 28};
    // 0x004d0b80
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v1, gp, -17312);  // 0x7CE950
    v0 = 0x960000;
    v0 = addiu(v0, 112);  // &0x960070
    v0 = addu(v0, v1);
    lw(v0, v0, 28);
}

// 0x004D0BA0 sub_4D0BA0 -- 28 bytes; leaf frame (no stack)
// Sets the word at plugin offset +32 of 0x960070 + *0x7CE950. Returns 1.
void sub_4D0BA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x004d0ba0
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(a1, gp, -17312);  // 0x7CE950
    v1 = 0x960000;
    v1 = addiu(v1, 112);  // &0x960070
    v0 = 1;
    v1 = addu(v1, a1);
    sw(a0, v1, 32);
}

// 0x004D0BC0 sub_4D0BC0 -- 24 bytes; leaf frame (no stack)
// Returns the word at plugin offset +32 of 0x960070 + *0x7CE950.
void sub_4D0BC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, gp{ctx, 28};
    // 0x004d0bc0
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v1, gp, -17312);  // 0x7CE950
    v0 = 0x960000;
    v0 = addiu(v0, 112);  // &0x960070
    v0 = addu(v0, v1);
    lw(v0, v0, 32);
}

// 0x004DFCB0 sub_4DFCB0 -- 8 bytes; leaf frame (no stack)
// Constant stub (data-referenced): returns 0.
void sub_4DFCB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x004dfcb0
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x00501AE8 _sceMpegFlush -- 192 bytes; frame 0x30: s1 sp+0x10, ra sp+0x20, s0 sp+0x0
// _sceMpegFlush: when the decoder state ($a0+64) holds a pending picture, outputs the last reference image
// (_dispRefImage, or _dispRefImageField for field pictures; _sceMpegError "the second field is missing" when a field is
// pending), stores the picture count at $a0+8 and clears the pending flags. Returns 1 when it flushed.
void _sceMpegFlush(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00501ae8
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x10);
    sd(ra, sp, 0x20);
    s1 = a0;
    sd(s0, sp, 0x0);
    lw(s0, s1, 64);
    lw(v0, s0, 4);
    a0 = 0;
    if (v0 != 0) {
        // 0x00501b0c
        charge(ctx, 3);
        lw(v0, s0, 8);
        ld(ra, sp, 0x20);
        if (v0 != 0) {
            // 0x00501b18
            charge(ctx, 3);
            lw(v0, s0, 304);
            lw(a2, s0, 296);
            if (v0 == 0) {
                // 0x00501b3c
                charge(ctx, 4);
                lw(v1, s0, 388);
                v0 = 3;
                a3 = addiu(a2, -1);
                if (v1 != v0) {
                    // 0x00501b64
                    charge(ctx, 5);
                    lw(a1, s0, 476);
                    lw(a2, s0, 492);
                    a0 = s0;
                    jal(ctx, 0x501B6Cu, gen::fn__dispRefImageField_005016c8);
                    lw(v0, s0, 296);
                } else {
                    // 0x00501b4c
                    charge(ctx, 6);
                    lw(a1, s0, 460);
                    a2 = addiu(a2, -1);
                    a0 = s0;
                    jal(ctx, 0x501B54u, gen::fn__dispRefImage_00501408);
                    lw(v0, s0, 296);
                }
            } else {
                // 0x00501b24
                charge(ctx, 6);
                a1 = 0x7C0000;
                a0 = s0;
                a1 = addiu(a1, -9736);  // "the second field is missing"
                jal(ctx, 0x501B2Cu, gen::fn__sceMpegError_00502668);
                lw(v0, s0, 296);
            }
            // 0x00501b78
            charge(ctx, 6);
            a0 = 1;
            lw(v1, s0, 192);
            sw(zero, s0, 304);
            v0 = subu(v0, v1);
            sw(v0, s1, 8);
            sw(zero, s0, 4);
            goto L_00501b90;
        }
        // 0x00501b94 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        v0 = a0;
        ld(s1, sp, 0x10);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
L_00501b90:
    charge(ctx, 1);
    ld(ra, sp, 0x20);
    // 0x00501b94 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = a0;
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00513598 sceMc2FormatAsync -- 176 bytes; frame 0x30: s0 sp+0x0, ra sp+0x20, s1 sp+0x10
// sceMc2FormatAsync: checks the library is up (0x7827D8) and maps the socket (_sceMcCoreChangeSocketTypeDbc2Mc), then
// under the command semaphore queues command 3 (format) for the memory-card thread and signals it; returns 0 or the
// sceMc2 error codes (busy 0x81010010-style values).
void sceMc2FormatAsync(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00513598
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v1 = 0x780000;
    sd(s0, sp, 0x0);
    lw(v0, v1, 10200);  // 0x7827D8
    s0 = a0;
    sd(ra, sp, 0x20);
    sd(s1, sp, 0x10);
    if (v0 != 0) {
        // 0x005135c4
        charge(ctx, 5);
        a0 = s0;
        jal(ctx, 0x5135C4u, gen::fn__sceMcCoreChangeSocketTypeDbc2Mc_0051c2e8);
        s0 = v0;
        s1 = 0x970000;
        if (i64(s0) >= 0) {
            // 0x005135e4
            charge(ctx, 7);
            link(ctx, 0x5135E4u);  // $ra first: the delay slot below depends on it
            lw(a0, s1, -2452);
            call(ctx, gen::fn__sceWaitSema_005031a0);
            a2 = 0x970000;
            a1 = addiu(a2, -3776);  // &0x96F140
            lw(v0, a1, 4);  // 0x96F144
            if (v0 == 0) {
                v0 = 0x970000;
                // 0x00513614
                charge(ctx, 8);
                v1 = 3;
                lw(a0, v0, -2460);
                sw(s0, a2, -3776);
                link(ctx, 0x513620u);  // $ra first: the delay slot below depends on it
                sw(v1, a1, 4);
                call(ctx, gen::fn__sceSignalSema_00503180);
                link(ctx, 0x513628u);  // $ra first: the delay slot below depends on it
                lw(a0, s1, -2452);
                call(ctx, gen::fn__sceSignalSema_00503180);
                v0 = 0;
            } else {
                // 0x00513600
                charge(ctx, 5);
                link(ctx, 0x513600u);  // $ra first: the delay slot below depends on it
                lw(a0, s1, -2452);
                call(ctx, gen::fn__sceSignalSema_00503180);
                v0 = lui(0x8101);
                v0 = v0 | 0x10;
            }
        } else {
            // 0x005135d8
            charge(ctx, 3);
            v0 = lui(0x8101);
            v0 = v0 | 0x8002;
        }
    } else {
        // 0x005135b8
        charge(ctx, 3);
        v0 = lui(0x8101);
        v0 = v0 | 0x8001;
    }
    // 0x00513634 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00513CC8 sceMc2WriteFileAsync -- 288 bytes; frame 0x80: s6 sp+0x60, s5 sp+0x50, s4 sp+0x40, s3 sp+0x30, s1 sp+0x10, ra sp+0x70, s2 sp+0x20, s0 sp+0x0
// sceMc2WriteFileAsync: like sceMc2FormatAsync, queues command 6 (write file) with the path (< 128 chars), buffer,
// offset and size.
void sceMc2WriteFileAsync(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00513cc8
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
        // 0x00513d18
        charge(ctx, 5);
        a0 = s1;
        jal(ctx, 0x513D18u, gen::fn__sceMcCoreChangeSocketTypeDbc2Mc_0051c2e8);
        s1 = v0;
        if (i64(s1) >= 0) {
            // 0x00513d38
            charge(ctx, 5);
            a0 = s3;
            jal(ctx, 0x513D38u, gen::fn_strlen_00524388);
            v0 = sltiu(v0, 128);
            s2 = 0x970000;
            if (v0 != 0) {
                // 0x00513d58
                charge(ctx, 7);
                link(ctx, 0x513D58u);  // $ra first: the delay slot below depends on it
                lw(a0, s2, -2452);
                call(ctx, gen::fn__sceWaitSema_005031a0);
                v1 = 0x970000;
                s0 = addiu(v1, -3776);  // &0x96F140
                lw(v0, s0, 4);  // 0x96F144
                if (v0 == 0) {
                    v0 = 6;
                    // 0x00513d88
                    charge(ctx, 14);
                    sw(s1, v1, -3776);
                    sw(v0, s0, 4);
                    a1 = s3;
                    a0 = addiu(s0, 1052);
                    jal(ctx, 0x513D94u, gen::fn_strcpy_00524270);
                    sw(s4, s0, 20);
                    v1 = 0x970000;
                    lw(a0, v1, -2460);  // 0x96F664
                    sw(s5, s0, 12);
                    link(ctx, 0x513DACu);  // $ra first: the delay slot below depends on it
                    sw(s6, s0, 16);
                    call(ctx, gen::fn__sceSignalSema_00503180);
                    link(ctx, 0x513DB4u);  // $ra first: the delay slot below depends on it
                    lw(a0, s2, -2452);
                    call(ctx, gen::fn__sceSignalSema_00503180);
                    v0 = 0;
                } else {
                    // 0x00513d74
                    charge(ctx, 5);
                    link(ctx, 0x513D74u);  // $ra first: the delay slot below depends on it
                    lw(a0, s2, -2452);
                    call(ctx, gen::fn__sceSignalSema_00503180);
                    v0 = lui(0x8101);
                    v0 = v0 | 0x10;
                }
            } else {
                // 0x00513d4c
                charge(ctx, 3);
                v0 = lui(0x8101);
                v0 = v0 | 0x5B;
            }
        } else {
            // 0x00513d2c
            charge(ctx, 3);
            v0 = lui(0x8101);
            v0 = v0 | 0x8002;
        }
    } else {
        // 0x00513d0c
        charge(ctx, 3);
        v0 = lui(0x8101);
        v0 = v0 | 0x8001;
    }
    // 0x00513dc0 (the shared epilogue, written out on this path)
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

// 0x00513DE8 sceMc2CreateFileAsync -- 248 bytes; frame 0x50: s3 sp+0x30, s0 sp+0x0, ra sp+0x40, s2 sp+0x20, s1 sp+0x10
// sceMc2CreateFileAsync: queues command 7 (create file, mode 0x8417) with the path (< 128 chars).
void sceMc2CreateFileAsync(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00513de8
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v0 = 0x780000;
    sd(s3, sp, 0x30);
    sd(s0, sp, 0x0);
    s3 = a1;
    lw(v1, v0, 10200);  // 0x7827D8
    s0 = a0;
    sd(ra, sp, 0x40);
    sd(s2, sp, 0x20);
    sd(s1, sp, 0x10);
    if (v1 != 0) {
        // 0x00513e20
        charge(ctx, 5);
        a0 = s0;
        jal(ctx, 0x513E20u, gen::fn__sceMcCoreChangeSocketTypeDbc2Mc_0051c2e8);
        s0 = v0;
        if (i64(s0) >= 0) {
            // 0x00513e40
            charge(ctx, 5);
            a0 = s3;
            jal(ctx, 0x513E40u, gen::fn_strlen_00524388);
            v0 = sltiu(v0, 128);
            s2 = 0x970000;
            if (v0 != 0) {
                // 0x00513e60
                charge(ctx, 7);
                link(ctx, 0x513E60u);  // $ra first: the delay slot below depends on it
                lw(a0, s2, -2452);
                call(ctx, gen::fn__sceWaitSema_005031a0);
                v1 = 0x970000;
                s1 = addiu(v1, -3776);  // &0x96F140
                lw(v0, s1, 4);  // 0x96F144
                if (v0 == 0) {
                    v0 = 7;
                    // 0x00513e90
                    charge(ctx, 13);
                    sw(s0, v1, -3776);
                    sw(v0, s1, 4);
                    a1 = s3;
                    a0 = addiu(s1, 1052);
                    jal(ctx, 0x513E9Cu, gen::fn_strcpy_00524270);
                    v1 = 0x970000;
                    v0 = 0x8417;
                    lw(a0, v1, -2460);  // 0x96F664
                    link(ctx, 0x513EB0u);  // $ra first: the delay slot below depends on it
                    sw(v0, s1, 12);
                    call(ctx, gen::fn__sceSignalSema_00503180);
                    link(ctx, 0x513EB8u);  // $ra first: the delay slot below depends on it
                    lw(a0, s2, -2452);
                    call(ctx, gen::fn__sceSignalSema_00503180);
                    v0 = 0;
                } else {
                    // 0x00513e7c
                    charge(ctx, 5);
                    link(ctx, 0x513E7Cu);  // $ra first: the delay slot below depends on it
                    lw(a0, s2, -2452);
                    call(ctx, gen::fn__sceSignalSema_00503180);
                    v0 = lui(0x8101);
                    v0 = v0 | 0x10;
                }
            } else {
                // 0x00513e54
                charge(ctx, 3);
                v0 = lui(0x8101);
                v0 = v0 | 0x5B;
            }
        } else {
            // 0x00513e34
            charge(ctx, 3);
            v0 = lui(0x8101);
            v0 = v0 | 0x8002;
        }
    } else {
        // 0x00513e14
        charge(ctx, 3);
        v0 = lui(0x8101);
        v0 = v0 | 0x8001;
    }
    // 0x00513ec4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x005140F8 sceMc2MkdirAsync -- 248 bytes; frame 0x50: s3 sp+0x30, s0 sp+0x0, ra sp+0x40, s2 sp+0x20, s1 sp+0x10
// sceMc2MkdirAsync: queues command 11 (mkdir, mode 0x8427) with the path (< 128 chars).
void sceMc2MkdirAsync(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005140f8
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v0 = 0x780000;
    sd(s3, sp, 0x30);
    sd(s0, sp, 0x0);
    s3 = a1;
    lw(v1, v0, 10200);  // 0x7827D8
    s0 = a0;
    sd(ra, sp, 0x40);
    sd(s2, sp, 0x20);
    sd(s1, sp, 0x10);
    if (v1 != 0) {
        // 0x00514130
        charge(ctx, 5);
        a0 = s0;
        jal(ctx, 0x514130u, gen::fn__sceMcCoreChangeSocketTypeDbc2Mc_0051c2e8);
        s0 = v0;
        if (i64(s0) >= 0) {
            // 0x00514150
            charge(ctx, 5);
            a0 = s3;
            jal(ctx, 0x514150u, gen::fn_strlen_00524388);
            v0 = sltiu(v0, 128);
            s2 = 0x970000;
            if (v0 != 0) {
                // 0x00514170
                charge(ctx, 7);
                link(ctx, 0x514170u);  // $ra first: the delay slot below depends on it
                lw(a0, s2, -2452);
                call(ctx, gen::fn__sceWaitSema_005031a0);
                v1 = 0x970000;
                s1 = addiu(v1, -3776);  // &0x96F140
                lw(v0, s1, 4);  // 0x96F144
                if (v0 == 0) {
                    v0 = 11;
                    // 0x005141a0
                    charge(ctx, 13);
                    sw(s0, v1, -3776);
                    sw(v0, s1, 4);
                    a1 = s3;
                    a0 = addiu(s1, 1052);
                    jal(ctx, 0x5141ACu, gen::fn_strcpy_00524270);
                    v1 = 0x970000;
                    v0 = 0x8427;
                    lw(a0, v1, -2460);  // 0x96F664
                    link(ctx, 0x5141C0u);  // $ra first: the delay slot below depends on it
                    sw(v0, s1, 12);
                    call(ctx, gen::fn__sceSignalSema_00503180);
                    link(ctx, 0x5141C8u);  // $ra first: the delay slot below depends on it
                    lw(a0, s2, -2452);
                    call(ctx, gen::fn__sceSignalSema_00503180);
                    v0 = 0;
                } else {
                    // 0x0051418c
                    charge(ctx, 5);
                    link(ctx, 0x51418Cu);  // $ra first: the delay slot below depends on it
                    lw(a0, s2, -2452);
                    call(ctx, gen::fn__sceSignalSema_00503180);
                    v0 = lui(0x8101);
                    v0 = v0 | 0x10;
                }
            } else {
                // 0x00514164
                charge(ctx, 3);
                v0 = lui(0x8101);
                v0 = v0 | 0x5B;
            }
        } else {
            // 0x00514144
            charge(ctx, 3);
            v0 = lui(0x8101);
            v0 = v0 | 0x8002;
        }
    } else {
        // 0x00514124
        charge(ctx, 3);
        v0 = lui(0x8101);
        v0 = v0 | 0x8001;
    }
    // 0x005141d4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0051B8F0 _sceMcCoreWritePage -- 404 bytes; frame 0xB0: s0 sp+0x10, s2 sp+0x30, s7 sp+0x80, s6 sp+0x70, s4 sp+0x50, s3 sp+0x40, ra sp+0xA0, fp sp+0x90, s5 sp+0x60, s1 sp+0x20
// _sceMcCoreWritePage: fills the 9-word socket record's write-page request (page $a2, buffer $a1, count $a3), writes
// back the data cache over the buffers, and sends it through sceDbcSendData3 until accepted; waits for the reply
// (SyncDma) and returns the count on success, else 0 (3 when the socket is not connected).
void _sceMcCoreWritePage(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x0051b8f0
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    v0 = 36;
    sd(s0, sp, 0x10);
    v1 = 0x980000;
    mult(s0, a0, v0);
    sd(s2, sp, 0x30);
    s2 = addiu(v1, 21768);  // &0x985508
    sd(s7, sp, 0x80);
    sd(s6, sp, 0x70);
    v0 = addiu(s2, 4);  // &0x98550C
    sd(s4, sp, 0x50);
    s7 = a2;
    sd(s3, sp, 0x40);
    s6 = addu(s0, v0);
    sd(ra, sp, 0xA0);
    s3 = a1;
    sd(fp, sp, 0x90);
    s4 = a3;
    sd(s5, sp, 0x60);
    sd(s1, sp, 0x20);
    link(ctx, 0x51B940u);  // $ra first: the delay slot below depends on it
    lw(a0, s6, 0);
    call(ctx, gen::fn_sceDbcGetConnection_0051cad0);
    v1 = 3;
    a2 = addu(s2, s0);
    if (v0 != v1) {
        // 0x0051b95c
        charge(ctx, 49);
        s1 = addiu(s2, 8);
        v0 = a2;
        s1 = addu(s0, s1);
        v1 = v0;
        a0 = v0;
        lw(t0, v1, 16);
        a1 = v0;
        lw(t1, a0, 32);
        s5 = 0x980000;
        lw(t2, a1, 28);
        t4 = 48;
        lw(t3, a2, 20);
        s0 = 0x980000;
        lw(v1, s1, 0);
        s0 = addiu(s0, 21952);  // &0x9855C0
        lw(a3, v0, 12);
        a0 = s0;
        v0 = addiu(s5, 21888);  // &0x985580
        sw(s7, s5, 21888);  // 0x985580
        sw(v1, v0, 8);  // 0x985588
        a1 = 0;
        sw(a3, v0, 12);  // 0x98558C
        a2 = 256;
        sw(t0, v0, 16);  // 0x985590
        s2 = 0x780000;
        sw(t1, v0, 20);  // 0x985594
        fp = 0x520000;
        sw(t2, v0, 24);  // 0x985598
        s7 = 1;
        sw(t3, v0, 36);  // 0x9855A4
        sw(s3, v0, 40);  // 0x9855A8
        sw(t4, sp, 0x0);
        sw(s4, v0, 4);  // 0x985584
        sw(zero, v0, 28);  // 0x98559C
        link(ctx, 0x51B9E4u);  // $ra first: the delay slot below depends on it
        sw(zero, v0, 32);
        call(ctx, gen::fn_memset_00521408);
        a0 = s0;
        a1 = addiu(a0, 255);  // &0x9856BF
        jal(ctx, 0x51B9F0u, gen::fn_SyncDCache_00503a58);
        lw(a1, s1, 0);
        a0 = s3;
        mult(v0, a1, s4);
        a1 = addu(v0, s3);
        a1 = addiu(a1, -1);
        jal(ctx, 0x51BA08u, gen::fn_SyncDCache_00503a58);
        v0 = 2;
        sw(v0, s2, 10988);  // 0x782AEC
        lw(a0, s6, 0);
        for (;;) {
            // 0x0051ba20
            charge(ctx, 7);
            a2 = sp;
            lw(a1, s2, 10988);
            a3 = addiu(s5, 21888);
            t0 = addiu(fp, -0x51C8);
            jal(ctx, 0x51BA2Cu, gen::fn_sceDbcSendData3_0051d308);
            if (v0 == s7) {
                break;
            }
            lw(a0, s6, 0);
            backedge(ctx);
        }
        // 0x0051ba3c
        charge(ctx, 6);
        jal(ctx, 0x51BA3Cu, gen::fn_SyncDma_0051ad10);
        lw(v1, v0, 8);
        v0 = 0;
        v1 = v1 ^ 0x1;
        if (v1 == 0) v0 = s4;
    } else {
        // 0x0051b954
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x0051ba54 (the shared epilogue, written out on this path)
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

// 0x00520410 _fwalk -- 144 bytes; frame 0x30: s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s0 sp+0x0, s1 sp+0x8, ra sp+0x28
// _fwalk (newlib): calls the function $a1 on every open FILE (flags +12 non-zero, 88-byte records) of every glue block
// of the reent $a0 (+472), ORing the results.
void _fwalk(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00520410
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    sd(s4, sp, 0x20);
    s2 = addiu(a0, 472);
    sd(s0, sp, 0x0);
    s3 = 0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x28);
    s4 = a1;
    if (s2 != 0) {
        // 0x0052043c
        charge(ctx, 1);
        lw(s1, s2, 4);
        for (;;) {
            // 0x00520440
            charge(ctx, 3);
            s1 = addiu(s1, -1);
            lw(s0, s2, 8);
            if (i64(s1) >= 0) {
                for (;;) {
                    // 0x0052044c
                    charge(ctx, 3);
                    lh(t7, s0, 12);
                    if (t7 == 0) {
                        s1 = addiu(s1, -1);
                    } else {
                        // 0x00520458
                        charge(ctx, 4);
                        a0 = s0;
                        jalr(ctx, 0x520458u, s4.u());
                        s3 = s3 | v0;
                        s1 = addiu(s1, -1);
                    }
                    // 0x00520468
                    charge(ctx, 2);
                    s0 = addiu(s0, 88);
                    if (i64(s1) < 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x00520470
            charge(ctx, 3);
            lw(s2, s2, 0);
            if (s2 == 0) {
                break;
            }
            lw(s1, s2, 4);
            backedge(ctx);
        }
    }
    // 0x0052047c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    v0 = s3;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x00523580 __srefill -- 364 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// __srefill (newlib): refills the FILE $a0's read buffer -- initialises the reent (__sinit), handles the ungetc buffer,
// flushes line-buffered output (_fwalk lflush), allocates the buffer (_fork_r), and reads through the stream's read
// hook (+32); sets EOF (0x20) / error (0x40) on a short read. Returns 0 or -1.
void __srefill(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00523580
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    lw(a0, a0, 84);
    if (a0 != 0) {
        lw(t7, a0, 56);
    } else {
        // 0x0052359c
        charge(ctx, 5);
        t7 = 0x780000;
        lw(t6, t7, 12080);  // 0x782F30
        sw(t6, s0, 84);
        a0 = t6;
        lw(t7, a0, 56);
    }
    // 0x005235b0
    charge(ctx, 2);
    if (t7 != 0) {
        lhu(t6, s0, 12);
    } else {
        // 0x005235b8
        charge(ctx, 3);
        jal(ctx, 0x5235B8u, gen::fn___sinit_0051fa20);
        lhu(t6, s0, 12);
    }
    // 0x005235c4
    charge(ctx, 4);
    t5 = si(-1);
    t7 = t6 & 0x20;
    sw(zero, s0, 4);
    if (t7 == 0) {
        // 0x005235d4
        charge(ctx, 3);
        t7 = t6 & 0x4;
        if (t7 != 0) {
            lw(a1, s0, 48);
            // 0x005236b4
            charge(ctx, 2);
            t7 = addiu(s0, 64);
            if (a1 == 0) {
                backedge(ctx);
            L_00523624:
                charge(ctx, 3);
                lw(t7, s0, 16);
                if (t7 != 0) {
                    lhu(t7, s0, 12);
                } else {
                    // 0x00523630
                    charge(ctx, 3);
                    a0 = s0;
                    jal(ctx, 0x523630u, gen::fn__fork_r_005205d8);
                    lhu(t7, s0, 12);
                }
                // 0x0052363c
                charge(ctx, 3);
                t7 = t7 & 0x3;
                a1 = 0x520000;
                if (t7 != 0) {
                    // 0x00523648
                    charge(ctx, 3);
                    lw(a0, s0, 84);
                    a1 = addiu(a1, 13648);
                    jal(ctx, 0x52364Cu, gen::fn__fwalk_00520410);
                }
                // 0x00523654
                charge(ctx, 12);
                lw(a1, s0, 16);
                lw(v0, s0, 32);
                sw(a1, s0, 0);
                lw(a0, s0, 28);
                jt = v0.u();  // the target, read before the delay slot
                link(ctx, 0x523664u);  // $ra = the return address
                lw(a2, s0, 20);
                call_ptr(ctx, jt);
                lhu(t7, s0, 12);
                t5 = 0;
                sw(v0, s0, 4);
                t7 = t7 & 0xDFFF;
                sh(t7, s0, 12);
                if (i64(v0) <= 0) {
                    // 0x00523684
                    charge(ctx, 2);
                    if (v0 != 0) {
                        sw(zero, s0, 4);
                        // 0x005236ac
                        charge(ctx, 2);
                        t7 = t7 | 0x40;
                        backedge(ctx);
                    } else {
                        // 0x0052368c
                        charge(ctx, 1);
                        t7 = t7 | 0x20;
                    }
                    // 0x00523690
                    charge(ctx, 2);
                    sh(t7, s0, 12);
                    t5 = si(-1);
                }
            } else {
                // 0x005236bc
                charge(ctx, 2);
                if (a1 == t7) {
                    lw(t7, s0, 60);
                } else {
                    // 0x005236c4
                    charge(ctx, 3);
                    link(ctx, 0x5236C4u);  // $ra first: the delay slot below depends on it
                    lw(a0, s0, 84);
                    call(ctx, gen::fn__free_r_0051fbb0);
                    lw(t7, s0, 60);
                }
                // 0x005236d0
                charge(ctx, 3);
                sw(zero, s0, 48);
                sw(t7, s0, 4);
                if (t7 == 0) {
                    backedge(ctx);
                    goto L_00523624;
                }
                // 0x005236dc
                charge(ctx, 4);
                lw(t7, s0, 56);
                t5 = 0;
                sw(t7, s0, 0);
                backedge(ctx);
            }
        } else {
            // 0x005235e0
            charge(ctx, 3);
            t7 = t6 & 0x10;
            cc = t7 == 0;  // the condition, before the delay slot changes it
            t7 = t6 & 0x8;
            if (!cc) {
                // 0x005235ec
                charge(ctx, 2);
                cc = t7 == 0;  // the condition, before the delay slot changes it
                t7 = t6 | 0x4;
                if (!cc) {
                    // 0x005235f4
                    charge(ctx, 4);
                    a0 = s0;
                    jal(ctx, 0x5235F4u, gen::fn_fflush_0051f728);
                    t5 = si(-1);
                    if (v0 == 0) {
                        // 0x00523604
                        charge(ctx, 7);
                        lhu(t7, s0, 12);
                        sw(zero, s0, 8);
                        t7 = t7 & 0xFFF7;
                        sw(zero, s0, 24);
                        sh(t7, s0, 12);
                        t6 = t7;
                        t7 = t6 | 0x4;
                        goto L_00523620;
                    }
                    // 0x00523698 (the shared epilogue, written out on this path)
                    charge(ctx, 5);
                    ld(s0, sp, 0x0);
                    v0 = t5;
                    ld(ra, sp, 0x8);
                    sp = addiu(sp, 0x10);
                    return;
                }
            L_00523620:
                charge(ctx, 1);
                sh(t7, s0, 12);
                goto L_00523624;
            }
        }
    }
    // 0x00523698 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    v0 = t5;
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00537780 sceInsockGetErrnoMode -- 12 bytes; leaf frame (no stack)
// sceInsockGetErrnoMode: returns the word at 0x7838EC.
void sceInsockGetErrnoMode(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3};
    // 0x00537780
    enter(ctx, 3);  // entry check point + this block's cycles
    v1 = 0x780000;
    lw(v0, v1, 14572);  // 0x7838EC
}

// 0x0053AFD8 sub_53AFD8 -- 136 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Formats two numbers into $a2: sub_53AED0($a0) into the buffer of size $a3, appends the separator string at 0x7C1A80,
// then sub_53AED0($a1) into the rest (4 - length).
void sub_53AFD8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053afd8
    enter(ctx, 34);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a2;
    sd(s1, sp, 0x8);
    s1 = a3;
    sd(s2, sp, 0x10);
    s2 = a1;
    a2 = s1;
    sd(ra, sp, 0x18);
    a1 = s0;
    jal(ctx, 0x53AFFCu, gen::fn_sub_53AED0_0053aed0);
    a0 = s0;
    jal(ctx, 0x53B004u, gen::fn_strlen_00524388);
    a1 = 0x7C0000;
    s1 = subu(s1, v0);
    a1 = addiu(a1, 6784);  // &0x7C1A80
    a2 = addiu(s1, -1);
    a0 = s0;
    jal(ctx, 0x53B01Cu, gen::fn_strncat_005244c0);
    a0 = s0;
    jal(ctx, 0x53B024u, gen::fn_strlen_00524388);
    a0 = s0;
    s0 = addu(s0, v0);
    jal(ctx, 0x53B030u, gen::fn_strlen_00524388);
    ld(s1, sp, 0x8);
    a0 = s2;
    a1 = s0;
    ld(s0, sp, 0x0);
    a2 = 4;
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    a2 = subu(a2, v0);
    sp = addiu(sp, 0x20);
    gen::fn_sub_53AED0_0053aed0(ctx);  // tail call
}

// 0x0053EC20 sub_53EC20 -- 224 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// CRI middleware shutdown: drops the init count at 0x787550 and, at zero, finalises every subsystem (sub_548250 ..
// sub_5397E8, sub_564EF8 settings) between clearing and setting 0x7A114C. Returns 1, or the remaining count.
void sub_53EC20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053ec20
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = 0x780000;
    sd(s0, sp, 0x0);
    v1 = addiu(v1, 30032);  // &0x787550
    sd(ra, sp, 0x8);
    lw(v0, v1, 0);  // 0x787550
    v0 = addiu(v0, -1);
    sw(v0, v1, 0);  // 0x787550
    if (v0 == 0) {
        // 0x0053ec44
        charge(ctx, 43);
        s0 = 0x7A0000;
        s0 = addiu(s0, 4428);  // &0x7A114C
        link(ctx, 0x53EC4Cu);  // $ra first: the delay slot below depends on it
        sw(zero, s0, 0);  // 0x7A114C
        call(ctx, gen::fn_sub_548250_00548250);
        jal(ctx, 0x53EC54u, gen::fn_sub_5419D8_005419d8);
        jal(ctx, 0x53EC5Cu, gen::fn_sub_53B158_0053b158);
        jal(ctx, 0x53EC64u, gen::fn_sub_545CC8_00545cc8);
        jal(ctx, 0x53EC6Cu, gen::fn_sub_55DD08_0055dd08);
        jal(ctx, 0x53EC74u, gen::fn_sub_539818_00539818);
        a0 = 2;
        a1 = 1;
        jal(ctx, 0x53EC80u, gen::fn_sub_564EF8_00564ef8);
        v0 = 0x780000;
        lw(a1, v0, 30052);  // 0x787564
        a0 = 4;
        jal(ctx, 0x53EC90u, gen::fn_sub_564EF8_00564ef8);
        v0 = 0x780000;
        lw(a1, v0, 30040);  // 0x787558
        a0 = 5;
        jal(ctx, 0x53ECA0u, gen::fn_sub_564EF8_00564ef8);
        jal(ctx, 0x53ECA8u, gen::fn_sub_565590_00565590);
        jal(ctx, 0x53ECB0u, gen::fn_sub_541DA0_00541da0);
        jal(ctx, 0x53ECB8u, gen::fn_sub_53ADA8_0053ada8);
        jal(ctx, 0x53ECC0u, gen::fn_sub_5618F0_005618f0);
        jal(ctx, 0x53ECC8u, gen::fn_sub_562308_00562308);
        jal(ctx, 0x53ECD0u, gen::fn_sub_562F10_00562f10);
        jal(ctx, 0x53ECD8u, gen::fn_sub_539830_00539830);
        jal(ctx, 0x53ECE0u, gen::fn_sub_5397E8_005397e8);
        v0 = 1;
        sw(v0, s0, 0);  // 0x7A114C
    }
    // 0x0053ecf0 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00547F30 sub_547F30 -- 72 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Calls sub_547F78($a0, $a1) between the lock pair sub_539848 / sub_539850; returns its result.
void sub_547F30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00547f30
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x547F44u, gen::fn_sub_539848_00539848);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x547F50u, gen::fn_sub_547F78_00547f78);
    s0 = v0;
    jal(ctx, 0x547F58u, gen::fn_sub_539850_00539850);
    ld(s1, sp, 0x8);
    v0 = s0;
    ld(ra, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00548FC8 sub_548FC8 -- 56 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Calls sub_549000($a0) between the lock pair sub_539848 / sub_539850; returns its result.
void sub_548FC8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00548fc8
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x548FD4u, gen::fn_sub_539848_00539848);
    a0 = s0;
    jal(ctx, 0x548FDCu, gen::fn_sub_549000_00549000);
    s0 = v0;
    jal(ctx, 0x548FE4u, gen::fn_sub_539850_00539850);
    ld(ra, sp, 0x8);
    v0 = s0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00549530 sub_549530 -- 56 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Calls sub_549568($a0) between the lock pair sub_539848 / sub_539850; returns its result.
void sub_549530(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00549530
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x54953Cu, gen::fn_sub_539848_00539848);
    a0 = s0;
    jal(ctx, 0x549544u, gen::fn_sub_549568_00549568);
    s0 = v0;
    jal(ctx, 0x54954Cu, gen::fn_sub_539850_00539850);
    ld(ra, sp, 0x8);
    v0 = s0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0054A630 __env_lock_0 -- 8 bytes; leaf frame (no stack)
// __env_lock_0: empty lock hook (jr $ra).
void __env_lock_0(EEContext& ctx) {
    using namespace hg;
    // 0x0054a630
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x0054F708 sub_54F708 -- 40 bytes; frame 0x10: ra sp+0x0
// Calls the hook at 0x793B24 when it is set; returns it.
void sub_54F708(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054f708
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x790000;
    sp = addiu(sp, -0x10);
    lw(v0, v0, 15140);  // 0x793B24
    sd(ra, sp, 0x0);
    if (v0 != 0) {
        // 0x0054f71c
        charge(ctx, 2);
        jalr(ctx, 0x54F71Cu, v0.u());
    }
    // 0x0054f724 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00552BD0 sub_552BD0 -- 308 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, s2 sp+0x10, ra sp+0x18
// CRI handle destroy: on NULL reports "E2003050202 : NULL pointer"; otherwise stops it (sub_5530D0), releases its +8
// stream (sub_5466B8 / sub_546058) and +12 (sub_5542E8), calls the release method (+12 of the vtable) of each of its +3
// sub-objects at +148 and of +140, frees +4 (sub_5548D0), clears the 620-byte handle, and unlocks (sub_554708).
void sub_552BD0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00552bd0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s0, sp, 0x0);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    if (s1 == 0) {
        // 0x00552bec
        charge(ctx, 8);
        a0 = 0x7C0000;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a0 = addiu(a0, 12840);  // "E2003050202 : NULL pointer is specified."
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_552630_00552630(ctx);  // tail call
        return;
    }
    // 0x00552c10
    charge(ctx, 5);
    jal(ctx, 0x552C10u, gen::fn_sub_5530D0_005530d0);
    lw(s0, s1, 8);
    a1 = 0;
    if (s0 != 0) {
        // 0x00552c24
        charge(ctx, 6);
        sw(zero, s1, 8);
        a0 = s0;
        a2 = 0;
        jal(ctx, 0x552C2Cu, gen::fn_sub_5466B8_005466b8);
        a0 = s0;
        jal(ctx, 0x552C34u, gen::fn_sub_546058_00546058);
    }
    // 0x00552c3c
    charge(ctx, 3);
    lw(v0, s1, 12);
    if (v0 != 0) {
        // 0x00552c48
        charge(ctx, 2);
        a0 = s1;
        jal(ctx, 0x552C48u, gen::fn_sub_5542E8_005542e8);
    }
    // 0x00552c50
    charge(ctx, 5);
    s2 = 0;
    jal(ctx, 0x552C50u, gen::fn_sub_5546F0_005546f0);
    lb(v0, s1, 3);
    lbu(a1, s1, 3);
    if (i64(v0) > 0) {
        // 0x00552c64
        charge(ctx, 1);
        s0 = addiu(s1, 148);
        for (;;) {
            // 0x00552c68
            charge(ctx, 3);
            lw(v1, s0, 0);
            a0 = v1;
            if (v1 != 0) {
                // 0x00552c74
                charge(ctx, 6);
                lw(v1, v1, 0);
                sw(zero, s0, 0);
                lw(v0, v1, 12);
                jalr(ctx, 0x552C80u, v0.u());
                lbu(a1, s1, 3);
            }
            // 0x00552c8c
            charge(ctx, 6);
            v0 = sll(a1, 24);
            s2 = addiu(s2, 1);
            v0 = sra(v0, 24);
            v0 = slt(s2, v0);
            s0 = addiu(s0, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00552ca4
    charge(ctx, 3);
    lw(a0, s1, 140);
    if (a0 == 0) {
        lw(a0, s1, 4);
    } else {
        // 0x00552cb0
        charge(ctx, 6);
        lw(v1, a0, 0);
        sw(zero, s1, 140);
        lw(v0, v1, 12);
        jalr(ctx, 0x552CBCu, v0.u());
        lw(a0, s1, 4);
    }
    // 0x00552cc8
    charge(ctx, 2);
    if (a0 == 0) {
        a0 = s1;
    } else {
        // 0x00552cd0
        charge(ctx, 3);
        link(ctx, 0x552CD0u);  // $ra first: the delay slot below depends on it
        sw(zero, s1, 4);
        call(ctx, gen::fn_sub_5548D0_005548d0);
        a0 = s1;
    }
    // 0x00552cdc
    charge(ctx, 10);
    a1 = 0;
    a2 = 620;
    jal(ctx, 0x552CE0u, gen::fn_memset_00521408);
    sb(zero, s1, 0);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_554708_00554708(ctx);  // tail call
}

// 0x00553188 sub_553188 -- 48 bytes; frame 0x10: ra sp+0x0
// Returns the s8 at $a0+1, or reports "E2003050209 : NULL pointer" and returns -1.
void sub_553188(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00553188
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x005531a8
        charge(ctx, 1);
        lb(v0, a0, 1);
    } else {
        // 0x00553194
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 13224);  // "E2003050209 : NULL pointer is specified."
        jal(ctx, 0x553198u, gen::fn_sub_552630_00552630);
        v0 = si(-1);
    }
    // 0x005531ac (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00553230 sub_553230 -- 84 bytes; frame 0x10: ra sp+0x0
// Returns the word slot $a1 (< 33) at $a0+12, or reports the NULL pointer / 'trno' out of range error and returns 0.
void sub_553230(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00553230
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = slti(a1, 33);
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x00553240
        charge(ctx, 3);
        a0 = 0x7C0000;
        a0 = addiu(a0, 13320);  // "E2003050210 : NULL pointer is specified."
        goto L_00553260;
    }
    // 0x00553250
    charge(ctx, 2);
    v1 = sll(a1, 2);
    if (v0 != 0) {
        // 0x00553270
        charge(ctx, 2);
        v1 = addu(a0, v1);
        lw(v0, v1, 12);
    } else {
        // 0x00553258
        charge(ctx, 2);
        a0 = 0x7C0000;
        a0 = addiu(a0, 13368);  // "E2003052112 : The parameter 'trno' is out of range."
    L_00553260:
        charge(ctx, 4);
        jal(ctx, 0x553260u, gen::fn_sub_552630_00552630);
        v0 = 0;
    }
    // 0x00553278 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0055A1D0 sub_55A1D0 -- 28 bytes; frame 0x10: ra sp+0x0
// Clears the 72-byte record $a0 (memset).
void sub_55A1D0(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055a1d0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = 0;
    sd(ra, sp, 0x0);
    a2 = 72;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_memset_00521408(ctx);  // tail call
}

// 0x0055A638 dvCiStopTr -- 228 bytes; frame 0x30: s0 sp+0x0, s2 sp+0x10, s1 sp+0x8, s3 sp+0x18, s4 sp+0x20, ra sp+0x28
// dvCiStopTr: stops the transfer of the DVCI handle $a0 (state +2 >= 2): cancels it (sub_557F80) when +28 is set, then
// pumps SRD_ExecServer / dvCiExecServer / dvCiGetStat until the state leaves 2 or the 10 s spin limit, clears +20 and
// the state; reports a NULL handle.
void dvCiStopTr(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055a638
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s2, sp, 0x10);
    s2 = 0;
    sd(s1, sp, 0x8);
    sd(s3, sp, 0x18);
    sd(s4, sp, 0x20);
    sd(ra, sp, 0x28);
    if (s0 == 0) {
        // 0x0055a660
        charge(ctx, 10);
        a1 = 0x7C0000;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a1 = addiu(a1, 19880);  // "E0092912:handl is null."
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(ra, sp, 0x28);
        sp = addiu(sp, 0x30);
        gen::fn_sub_559DA8_00559da8(ctx);  // tail call
        return;
    }
    // 0x0055a688
    charge(ctx, 4);
    lbu(v0, s0, 2);
    v0 = sltiu(v0, 2);
    if (v0 != 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x0055a698
        charge(ctx, 3);
        lw(a0, s0, 28);
        s1 = 0x90000;
        if (a0 != 0) {
            // 0x0055a6a4
            charge(ctx, 2);
            jal(ctx, 0x55A6A4u, gen::fn_sub_557F80_00557f80);
        }
        // 0x0055a6ac
        charge(ctx, 3);
        s3 = 2;
        s1 = s1 | 0xFFFF;
        s4 = 0x7C0000;
        for (;;) {
            // 0x0055a6b8
            charge(ctx, 9);
            jal(ctx, 0x55A6B8u, gen::fn_SRD_ExecServer_00558500);
            jal(ctx, 0x55A6C0u, gen::fn_dvCiExecServer_00559f48);
            a0 = s0;
            jal(ctx, 0x55A6C8u, gen::fn_dvCiGetStat_0055a720);
            lb(v1, s0, 2);
            if (v1 == s3) {
                // 0x0055a6dc
                charge(ctx, 4);
                s2 = addiu(s2, 1);
                v0 = slt(s1, s2);
                if (v0 != 0) {
                    goto L_0055a6ec_8;
                }
                backedge(ctx);
                continue;
            }
            sw(zero, s0, 20);
            break;
        }
    L_0055a6f8:
        charge(ctx, 2);
        sb(zero, s0, 2);
        ld(s0, sp, 0x0);
    }
    // 0x0055a700 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
    return;
L_0055a6ec_8:
    charge(ctx, 3);
    a0 = addiu(s4, 19976);
    jal(ctx, 0x55A6ECu, gen::fn_sub_541760_00541760);
    sw(zero, s0, 20);
    goto L_0055a6f8;
}

// 0x0055AB80 dvci_analysis_flist -- 404 bytes; frame 0x60: s2 sp+0x20, s3 sp+0x28, s5 sp+0x38, s6 sp+0x40, s7 sp+0x48, s0 sp+0x10, s1 sp+0x18, s4 sp+0x30, fp sp+0x50, ra sp+0x58
// dvci_analysis_flist: splits the file list text $a1 (length $a2) into lines, copying each into the name table $a0
// (after $a3 8-byte entries, stride $t0 + 1) with sub_559FD8, and records the table at 0x7A2A60 on the first call;
// returns the line count.
void dvci_analysis_flist(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0055ab80
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(s2, sp, 0x20);
    s2 = 0;
    sd(s3, sp, 0x28);
    s3 = a1;
    sd(s5, sp, 0x38);
    s5 = 0;
    sd(s6, sp, 0x40);
    s6 = a3;
    sd(s7, sp, 0x48);
    s7 = t0;
    sw(a0, sp, 0x0);
    a0 = 0;
    sd(s0, sp, 0x10);
    sd(s1, sp, 0x18);
    sd(s4, sp, 0x30);
    sd(fp, sp, 0x50);
    sd(ra, sp, 0x58);
    lb(v0, s3, 0);
    sw(a2, sp, 0x4);
    if (v0 != 0) {
        // 0x0055abd4
        charge(ctx, 7);
        lw(v1, sp, 0x0);
        v0 = sll(s6, 3);
        s4 = 10;
        fp = 0xD;
        s0 = addu(v0, v1);
        lb(v0, a1, 0);
        for (;;) {
            // 0x0055abf0
            charge(ctx, 2);
            if (v0 == s4) {
                lb(v0, a1, 1);
            } else {
                // 0x0055abf8
                charge(ctx, 2);
                v1 = addiu(s2, 1);
                if (v0 == 0) {
                    // 0x0055ac00
                    charge(ctx, 1);
                    lb(v0, a1, 1);
                    goto L_0055ac04;
                }
            L_0055ac94:
                charge(ctx, 4);
                lw(a1, sp, 0x4);
                v0 = slt(a1, v1);
                s2 = v1;
                if (v0 == 0) {
                    // 0x0055aca4
                    charge(ctx, 5);
                    v0 = addu(s3, v1);
                    a1 = v0;
                    lb(v1, a1, 0);
                    if (v1 != 0) {
                        lb(v0, a1, 0);
                        backedge(ctx);
                        continue;
                    }
                }
                break;
            }
        L_0055ac04:
            charge(ctx, 2);
            if (v0 == s4) {
                s2 = addiu(s2, 1);
            } else {
                // 0x0055ac0c
                charge(ctx, 2);
                v1 = addiu(a1, -1);
                if (v0 == 0) {
                    // 0x0055ac14
                    charge(ctx, 1);
                    s2 = addiu(s2, 1);
                    goto L_0055ac18;
                }
                goto L_0055ac20;
            }
        L_0055ac18:
            charge(ctx, 2);
            a1 = addu(s3, s2);
            v1 = addiu(a1, -1);
        L_0055ac20:
            charge(ctx, 3);
            lb(v0, v1, 0);
            s1 = subu(s2, a0);
            if (v0 != s4) {
                // 0x0055ac2c
                charge(ctx, 2);
                cc = v0 != fp;  // the condition, before the delay slot changes it
                v0 = addiu(a1, -2);
                if (!cc) {
                    goto L_0055ac34;
                }
                goto L_0055ac3c;
            }
        L_0055ac34:
            charge(ctx, 2);
            sb(zero, v1, 0);
            v0 = addiu(a1, -2);
        L_0055ac3c:
            charge(ctx, 3);
            lb(v1, v0, 0);
            if (v1 == s4) {
                sb(zero, v0, 0);
            } else {
                // 0x0055ac48
                charge(ctx, 2);
                a1 = addu(s3, a0);
                if (v1 == fp) {
                    // 0x0055ac50
                    charge(ctx, 1);
                    sb(zero, v0, 0);
                    goto L_0055ac54;
                }
                goto L_0055ac58;
            }
        L_0055ac54:
            charge(ctx, 1);
            a1 = addu(s3, a0);
        L_0055ac58:
            charge(ctx, 9);
            a0 = s0;
            a2 = s1;
            jal(ctx, 0x55AC5Cu, gen::fn_memcpy_00521250);
            a0 = s0;
            jal(ctx, 0x55AC64u, gen::fn_sub_559FD8_00559fd8);
            a2 = addu(s0, s1);
            lb(v0, a2, -1);
            if (v0 != 0) {
                sb(zero, a2, 0);
            }
            // 0x0055ac7c
            charge(ctx, 6);
            v1 = addiu(s2, 1);
            v0 = addu(s7, s0);
            s5 = addiu(s5, 1);
            s0 = addiu(v0, 1);
            a0 = v1;
            if (s5 == s6) {
                break;
            }
            goto L_0055ac94;
        }
    }
    // 0x0055acb8
    charge(ctx, 5);
    v0 = 0x7A0000;
    v0 = addiu(v0, 10848);  // &0x7A2A60
    lw(v1, v0, 0);  // 0x7A2A60
    if (v1 != 0) {
        v0 = s5;
    } else {
        // 0x0055accc
        charge(ctx, 6);
        sw(s7, v0, 12);
        lw(v1, sp, 0x0);
        sw(s6, v0, 8);
        sw(v1, v0, 0);
        sw(s5, v0, 4);
        v0 = s5;
    }
    // 0x0055ace4 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(s5, sp, 0x38);
    ld(s6, sp, 0x40);
    ld(s7, sp, 0x48);
    ld(fp, sp, 0x50);
    ld(ra, sp, 0x58);
    sp = addiu(sp, 0x60);
}

// 0x0055B0F8 sub_55B0F8 -- 36 bytes; frame 0x10: ra sp+0x0
// Clears the 16-byte DVCI file-cache record at 0x7A2A60.
void sub_55B0F8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055b0f8
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = 0x7A0000;
    sd(ra, sp, 0x0);
    a1 = 0;
    a0 = addiu(a0, 10848);  // &0x7A2A60
    a2 = 16;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_memset_00521408(ctx);  // tail call
}

// 0x0055DA48 sub_55DA48 -- 100 bytes; frame 0x10: ra sp+0x0
// Sets the minimum value +20 of the LSC handle $a0 to $a1 (0..+24); reports "E2005012819: Illigal param" /
// "E2005012820" otherwise.
void sub_55DA48(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055da48
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = a1;
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x0055da58
        charge(ctx, 5);
        a0 = 0x7C0000;
        ld(ra, sp, 0x0);
        a0 = addiu(a0, 22624);  // "E2005012819: Illigal parameter lsc=NULL\n"
        sp = addiu(sp, 0x10);
        gen::fn_sub_55DBE8_0055dbe8(ctx);  // tail call
        return;
    }
    // 0x0055da70
    charge(ctx, 2);
    if (i64(v1) < 0) {
        a0 = 0x7C0000;
    } else {
        // 0x0055da78
        charge(ctx, 4);
        lw(v0, a0, 24);
        v0 = slt(v0, v1);
        ld(ra, sp, 0x0);
        if (v0 != 0) {
            // 0x0055da88
            charge(ctx, 1);
            a0 = 0x7C0000;
            goto L_0055da8c;
        }
        // 0x0055daa0
        charge(ctx, 3);
        sw(v1, a0, 20);
        sp = addiu(sp, 0x10);
        return;
    }
L_0055da8c:
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    a0 = addiu(a0, 22672);
    sp = addiu(sp, 0x10);
    gen::fn_sub_55DBE8_0055dbe8(ctx);  // tail call
}

// 0x005835F0 sub_5835F0 -- 332 bytes; frame 0x60: s0 sp+0x30, s1 sp+0x38, s2 sp+0x40, s3 sp+0x48, ra sp+0x50
// SFD "CRITAGS"/"CRITAGE" header read: reads the header block through the stream's method (+36), finds the CRI tag
// section (sub_563E68) and either copies it into the caller's buffer and rewinds the stream, or parses it with
// sub_583848; marks +404 done.
void sub_5835F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005835f0
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    a1 = 1;
    sd(s0, sp, 0x30);
    s0 = a0;
    sd(s1, sp, 0x38);
    s1 = addiu(s0, 404);
    sd(s2, sp, 0x40);
    sd(s3, sp, 0x48);
    sd(ra, sp, 0x50);
    lw(s2, s0, 380);
    lw(v1, s2, 0);
    lw(v0, v1, 36);
    a0 = s2;
    jalr(ctx, 0x583620u, v0.u());
    a1 = 0x7D0000;
    a2 = 0x7D0000;
    v1 = v0;
    a1 = addiu(a1, -27024);  // "CRITAGS"
    a2 = addiu(a2, -27016);  // "CRITAGE"
    a0 = sp;
    a3 = addiu(sp, 0x10);
    if (v1 != 0) {
        // 0x00583648
        charge(ctx, 6);
        lw(v0, s0, 384);
        sw(v1, sp, 0x4);
        link(ctx, 0x583650u);  // $ra first: the delay slot below depends on it
        sw(v0, sp, 0x0);
        call(ctx, gen::fn_sub_563E68_00563e68);
        s3 = addiu(s0, 392);
        if (v0 == 0) {
            goto L_00583660;
        }
        // 0x00583678
        charge(ctx, 3);
        lw(v0, s3, 0);
        a0 = v0;
        if (v0 == 0) {
            // 0x00583700
            charge(ctx, 8);
            lw(a1, sp, 0x14);
            v1 = 1;
            lw(v0, sp, 0x10);
            a0 = s0;
            sw(v1, s1, 0);
            sw(v0, s1, 4);
            link(ctx, 0x583718u);  // $ra first: the delay slot below depends on it
            sw(a1, s1, 8);
            call(ctx, gen::fn_sub_583848_00583848);
        L_00583720:
            charge(ctx, 1);
            ld(s0, sp, 0x30);
        } else {
            // 0x00583684
            charge(ctx, 30);
            lw(a1, sp, 0x10);
            link(ctx, 0x583688u);  // $ra first: the delay slot below depends on it
            lw(a2, sp, 0x14);
            call(ctx, gen::fn_memcpy_00521250);
            lw(v1, s3, 0);
            lw(a1, sp, 0x14);
            v0 = 1;
            lw(a3, s2, 0);
            s0 = addiu(sp, 0x20);
            sw(v0, s1, 0);
            a2 = 0x7FFF0000;
            lw(v0, a3, 24);
            a3 = s0;
            sw(v1, s1, 4);
            a0 = s2;
            sw(a1, s1, 8);
            a1 = 1;
            a2 = a2 | 0xFFFF;
            jalr(ctx, 0x5836C4u, v0.u());
            lw(v1, s2, 0);
            a0 = s2;
            a2 = s0;
            lw(v0, v1, 32);
            a1 = 0;
            jalr(ctx, 0x5836DCu, v0.u());
            lw(v1, s2, 0);
            lw(v0, v1, 20);
            a0 = s2;
            jalr(ctx, 0x5836ECu, v0.u());
            ld(s0, sp, 0x30);
        }
        // 0x00583724 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(s1, sp, 0x38);
        ld(s2, sp, 0x40);
        ld(s3, sp, 0x48);
        ld(ra, sp, 0x50);
        sp = addiu(sp, 0x60);
        return;
    }
L_00583660:
    charge(ctx, 5);
    v0 = 1;
    sw(zero, s1, 4);
    sw(v0, s1, 0);
    sw(zero, s1, 8);
    goto L_00583720;
}

// 0x005837A0 sub_5837A0 -- 168 bytes; frame 0x30: s0 sp+0x20, ra sp+0x28
// Finds the "SFXINFS"/"SFXINFE" section in the header at $a0+408 and passes it (or nothing) to sub_59FE60($a0+168).
void sub_5837A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005837a0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = a0;
    sd(s0, sp, 0x20);
    v1 = addiu(v0, 404);
    sd(ra, sp, 0x28);
    a0 = sp;
    lw(t0, v1, 4);
    lw(s0, v0, 168);
    if (t0 != 0) {
        // 0x005837e0
        charge(ctx, 13);
        lw(v0, v1, 8);
        a1 = 0x7D0000;
        a2 = 0x7D0000;
        a1 = addiu(a1, -26952);  // "SFXINFS"
        a2 = addiu(a2, -26944);  // "SFXINFE"
        a3 = addiu(sp, 0x10);
        sw(t0, sp, 0x0);
        link(ctx, 0x5837FCu);  // $ra first: the delay slot below depends on it
        sw(v0, sp, 0x4);
        call(ctx, gen::fn_sub_563E68_00563e68);
        a0 = s0;
        a1 = 0;
        a2 = 0;
        if (v0 != 0) {
            // 0x00583828
            charge(ctx, 5);
            lw(a1, sp, 0x10);
            a0 = s0;
            link(ctx, 0x583830u);  // $ra first: the delay slot below depends on it
            lw(a2, sp, 0x14);
            call(ctx, gen::fn_sub_59FE60_0059fe60);
            ld(s0, sp, 0x20);
        } else {
            // 0x00583814
            charge(ctx, 4);
            jal(ctx, 0x583814u, gen::fn_sub_59FE60_0059fe60);
            ld(s0, sp, 0x20);
        }
    } else {
        // 0x005837c4
        charge(ctx, 6);
        a0 = s0;
        a1 = 0;
        a2 = 0;
        jal(ctx, 0x5837CCu, gen::fn_sub_59FE60_0059fe60);
        ld(s0, sp, 0x20);
    }
    // 0x0058383c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x005876F0 sub_5876F0 -- 36 bytes; frame 0x10: ra sp+0x0
// True when sub_548768() returns 2 or more.
void sub_5876F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005876f0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x5876F8u, gen::fn_sub_548768_00548768);
    v0 = sltiu(v0, 2);
    ld(ra, sp, 0x0);
    v0 = sltiu(v0, 1);
    sp = addiu(sp, 0x10);
}

// 0x00589F70 sub_589F70 -- 92 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Raises error 0xFF000161 when sub_58C060() reports a bad state; otherwise sub_599240($a0, 49, 1). Returns 0.
void sub_589F70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00589f70
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x589F7Cu, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = s0;
    a2 = 1;
    a1 = a1 | 0x161;
    if (v0 != 0) {
        // 0x00589f98
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        a0 = 0;
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x00589fb0
    charge(ctx, 7);
    a1 = 49;
    jal(ctx, 0x589FB0u, gen::fn_sub_599240_00599240);
    v0 = 0;
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0058C228 sub_58C228 -- 176 bytes; frame 0x30: s1 sp+0x8, s0 sp+0x0, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, ra sp+0x28
// Handle setter: raises error 0xFF000171 on a bad state, else for ids 188..255 stores $a2 at slot +4 * id - 688 and $a3
// / $t0 at +336 / +340 of $a0+8060's record.
void sub_58C228(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058c228
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s3, sp, 0x18);
    s3 = a3;
    sd(s4, sp, 0x20);
    sd(ra, sp, 0x28);
    s4 = t0;
    jal(ctx, 0x58C254u, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    v1 = addiu(s1, -188);
    a0 = 0;
    a1 = a1 | 0x171;
    v1 = sltiu(v1, 68);
    if (v0 != 0) {
        // 0x0058c274
        charge(ctx, 8);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(ra, sp, 0x28);
        sp = addiu(sp, 0x30);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x0058c298
    charge(ctx, 2);
    if (v1 == 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x0058c2a0
        charge(ctx, 7);
        lw(a0, s0, 8060);
        v1 = sll(s1, 2);
        v1 = addu(v1, a0);
        sw(s3, a0, 336);
        sw(s2, v1, -688);
        sw(s4, a0, 340);
        ld(s0, sp, 0x0);
    }
    // 0x0058c2bc (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x00595208 sub_595208 -- 88 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Starts the timer record ($a0+8128 + 4392) unless already running: resets +4504 (sub_594B18), stores $a1 at +32 and
// sets +28 = 1.
void sub_595208(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00595208
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    s2 = 1;
    sd(ra, sp, 0x18);
    lw(a0, a0, 8128);
    s0 = addiu(a0, 4392);
    lw(v0, s0, 28);
    a0 = addiu(a0, 4504);
    if (v0 != s2) {
        // 0x00595238
        charge(ctx, 4);
        jal(ctx, 0x595238u, gen::fn_sub_594B18_00594b18);
        sw(s1, s0, 32);
        sw(s2, s0, 28);
    }
    // 0x00595248 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00597968 sub_597968 -- 144 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, s2 sp+0x10, ra sp+0x18
// Raises error 0xFF000135 on a bad state; otherwise marks the handle's stream (+8004) through sub_589CF0 when
// sub_589D10 says it is not ready, setting +68. Returns 0.
void sub_597968(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00597968
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    sd(s0, sp, 0x0);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s1 = a0;
    jal(ctx, 0x59797Cu, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = s1;
    a1 = a1 | 0x135;
    if (v0 != 0) {
        // 0x00597994
        charge(ctx, 7);
        ld(s0, sp, 0x0);
        a0 = 0;
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x005979b0
    charge(ctx, 8);
    lw(s0, s1, 8004);
    s2 = 1;
    a1 = s0;
    jal(ctx, 0x5979B8u, gen::fn_sub_589D10_00589d10);
    a0 = s1;
    a1 = s0;
    a2 = 1;
    if (v0 != s2) {
        // 0x005979d0
        charge(ctx, 3);
        jal(ctx, 0x5979D0u, gen::fn_sub_589CF0_00589cf0);
        sw(s2, s1, 68);
    }
    // 0x005979dc (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = 0;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00599368 sub_599368 -- 156 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Getter: for a handle $a0 reads value $a1 through sub_599408 (error 0xFF000113 on a bad state), else the default table
// 0x7B4570[$a1]; stores it at *$a2. Returns 0.
void sub_599368(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00599368
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(ra, sp, 0x18);
    v0 = sll(s1, 2);
    if (s0 == 0) {
        // 0x00599390
        charge(ctx, 5);
        at = 0x7B0000;
        at = addu(at, v0);
        lw(v0, at, 17776);
        sw(v0, s2, 0);
        // 0x005993e8 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(s0, sp, 0x0);
        v0 = 0;
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x005993a8
    charge(ctx, 5);
    jal(ctx, 0x5993A8u, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = 0;
    if (v0 != 0) {
        // 0x005993bc
        charge(ctx, 7);
        ld(s0, sp, 0x0);
        a1 = a1 | 0x113;
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x005993d8
    charge(ctx, 4);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x5993DCu, gen::fn_sub_599408_00599408);
    sw(v0, s2, 0);
    // 0x005993e8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    v0 = 0;
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x005994F0 sub_5994F0 -- 160 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Copies the 168-byte record at $a0+2384 to $a1 (error 0xFF000119 on a bad state). Returns 0.
void sub_5994F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005994f0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x599504u, gen::fn_sub_58C060_0058c060);
    a0 = 0;
    if (v0 != 0) {
        // 0x00599514
        charge(ctx, 7);
        a1 = lui(0xFF00);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        a1 = a1 | 0x119;
        sp = addiu(sp, 0x20);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x00599530
    charge(ctx, 3);
    a1 = s1;
    v0 = addiu(s0, 2544);
    a0 = addiu(s0, 2384);
    for (;;) {
        // 0x0059953c
        charge(ctx, 13);
        ld(v1, a0, 0);
        ld(a2, a0, 8);
        ld(a3, a0, 16);
        ld(t0, a0, 24);
        sd(v1, a1, 0);
        sd(a2, a1, 8);
        sd(a3, a1, 16);
        sd(t0, a1, 24);
        a0 = addiu(a0, 32);
        a1 = addiu(a1, 32);
        if (a0 == v0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00599570
    charge(ctx, 8);
    ld(v0, a0, 0);
    ld(s0, sp, 0x0);
    sd(v0, a1, 0);
    v0 = 0;
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0059C8E0 sub_59C8E0 -- 272 bytes; frame 0x40: s0 sp+0x0, s1 sp+0x8, s3 sp+0x18, s4 sp+0x20, s5 sp+0x28, s2 sp+0x10, ra sp+0x30
// Adds a 16-byte entry $a1 to the handle's table ($a0+8528): sets it up with sub_59CC30($a2, $a3) and registers it
// (sub_588F48); errors 0xFF000191 / a full table (8). Returns 0.
void sub_59C8E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059c8e0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s3, sp, 0x18);
    s3 = a2;
    sd(s4, sp, 0x20);
    s4 = a3;
    sd(s5, sp, 0x28);
    s5 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x30);
    s0 = addiu(s1, 8528);
    jal(ctx, 0x59C910u, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = 0;
    a1 = a1 | 0x191;
    v1 = 8;
    if (v0 != 0) {
        // 0x0059c92c
        charge(ctx, 9);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(s5, sp, 0x28);
        ld(ra, sp, 0x30);
        sp = addiu(sp, 0x40);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x0059c950
    charge(ctx, 3);
    lw(s2, s0, 16);
    lw(v0, s0, 8);
    if (s2 == v1) {
        // 0x0059c95c
        charge(ctx, 12);
        a0 = s1;
        ld(s1, sp, 0x8);
        a1 = lui(0xFF00);
        ld(s0, sp, 0x0);
        ld(s2, sp, 0x10);
        a1 = a1 | 0x602;
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(s5, sp, 0x28);
        ld(ra, sp, 0x30);
        sp = addiu(sp, 0x40);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x0059c990
    charge(ctx, 24);
    s0 = sll(s5, 4);
    a1 = s3;
    s0 = addu(v0, s0);
    a2 = s4;
    s0 = addiu(s0, 4);
    t0 = 0;
    a0 = s0;
    a3 = 0;
    jal(ctx, 0x59C9ACu, gen::fn_sub_59CC30_0059cc30);
    a0 = s1;
    a1 = s2;
    a2 = s5;
    a3 = s0;
    jal(ctx, 0x59C9C0u, gen::fn_sub_588F48_00588f48);
    v0 = 0;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x0059FEF8 sub_59FEF8 -- 48 bytes; leaf frame (no stack)
// Returns the record at $a0+20: when +20 is 1 its +24 / +28 go to *$a1 / *$a2, else both are cleared.
void sub_59FEF8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0059fef8
    enter(ctx, 5);  // entry check point + this block's cycles
    a0 = addiu(a0, 20);
    v1 = 1;
    lw(v0, a0, 0);
    if (v0 != v1) {
        // 0x0059ff0c
        charge(ctx, 3);
        sw(zero, a1, 0);
        sw(zero, a2, 0);
        return;
    }
    lw(v0, a0, 8);
    // 0x0059ff18
    charge(ctx, 4);
    lw(v1, a0, 4);
    sw(v0, a2, 0);
    sw(v1, a1, 0);
}

}  // namespace p3fes::game

// The recompiled program's entry points fn_<name>_<addr8> are generated from game/replaced.txt (game/forwarders.cmake).
