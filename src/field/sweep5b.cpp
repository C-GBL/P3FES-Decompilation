// Slice sweep5b: 134 functions (43,504 bytes) taken from p3fes_handgen's faithful bodies (SLUS_216.21, symbols/).
// Every body keeps the recompiled body's registers, frame, spills, $ra links, cycle charges and check points
// (game/include/p3fes/game/hg_cpu.h). Made readable by a role comment per function, named offsets from
// sweep5b.h's sweep5b_layout (L::), and the structured control flow p3fes_handgen writes (if / for instead of the
// branch graph). Pair tests: tests/game/test_sweep5b.cpp. Sixteen packet functions stay recompiled: other slices' tests
// need them as they are (docs/INTEGRATION_LOG.md, sweep5b). Groups, in address order: the crt0 entry; the memory-card
// boot check; field objects, camera, model and encounter helpers; shop / facility menus; libmpeg; libkernel / libsif
// wrappers and the timer; libpad, libsdr, libmc2 / libdbc, libspu2 / libsk; newlib; CRI ADX / LSC / MWSFD.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/sweep5b.h"

namespace p3fes::recomp_gen {
void fn_DIntr_0050d3a0(p3fes::EEContext&);
void fn_DPRINT_0051d588(p3fes::EEContext&);
void fn_DisableDmac_00503d10(p3fes::EEContext&);
void fn_EIntr_0050d3f0(p3fes::EEContext&);
void fn_EnableDmac_00503d78(p3fes::EEContext&);
void fn_H_Memcard_Check_0018f190(p3fes::EEContext&);
void fn_InvalidDCache_00503b98(p3fes::EEContext&);
void fn_K_Field_Init_001b90f0(p3fes::EEContext&);
void fn_K_FldDungeon_GetFloorKind_001c0040(p3fes::EEContext&);
void fn_K_FldFrame_IsPointInTriangle_001aaad0(p3fes::EEContext&);
void fn_K_Scene_IsRandomFloor_001a0250(p3fes::EEContext&);
void fn_StartThread_005042a0(p3fes::EEContext&);
void fn_SyncDCache_00503a58(p3fes::EEContext&);
void fn_SyncDmaForRead_0051ade0(p3fes::EEContext&);
void fn_SyncDma_0051ad10(p3fes::EEContext&);
void fn___ieee754_pow_005296f0(p3fes::EEContext&);
void fn__clearEach_005001b0(p3fes::EEContext&);
void fn__clearOnce_004ffda8(p3fes::EEContext&);
void fn__dispRefImageField_005016c8(p3fes::EEContext&);
void fn__dispRefImage_00501408(p3fes::EEContext&);
void fn__doCSC2_00501c38(p3fes::EEContext&);
void fn__doMC_004fbf48(p3fes::EEContext&);
void fn__free_r_0051fbb0(p3fes::EEContext&);
void fn__get_free_slot_0051c0f8(p3fes::EEContext&);
void fn__groupOfPicturesHeader_004ff190(p3fes::EEContext&);
void fn__isceSifSetDma_00503530(p3fes::EEContext&);
void fn__malloc_r_005209c0(p3fes::EEContext&);
void fn__pictureHeader_004ff230(p3fes::EEContext&);
void fn__sceAddDmacHandler_0_00502e80(p3fes::EEContext&);
void fn__sceChangeThreadPriority_00502ff0(p3fes::EEContext&);
void fn__sceCreateSema_00503160(p3fes::EEContext&);
void fn__sceCreateThread_00502f60(p3fes::EEContext&);
void fn__sceDeci2Call_00503590(p3fes::EEContext&);
void fn__sceFlushCache_005033e0(p3fes::EEContext&);
void fn__sceGetThreadId_00503050(p3fes::EEContext&);
void fn__sceMcCoreChangeSocketTypeDbc2Mc_0051c2e8(p3fes::EEContext&);
void fn__sceMcCoreChangeSocketTypeMc2Dbc_0051c330(p3fes::EEContext&);
void fn__sceMcCoreCreateSocket_0051c130(p3fes::EEContext&);
void fn__sceMcCoreInit_0051ae68(p3fes::EEContext&);
void fn__sceMcFatInit2_00515400(p3fes::EEContext&);
void fn__sceMcFatInit_005153a0(p3fes::EEContext&);
void fn__sceMcpInit_0051a140(p3fes::EEContext&);
void fn__sceMpegAlalcAlloc_005010a0(p3fes::EEContext&);
void fn__sceMpegAlalcInit_00501068(p3fes::EEContext&);
void fn__sceMpegAlalcSetDynamic_00501080(p3fes::EEContext&);
void fn__sceMpegDispatchMpegCallback_00500d10(p3fes::EEContext&);
void fn__sceMpegDispatchMpegCbNodata_00500d88(p3fes::EEContext&);
void fn__sceMpegError1_005026c0(p3fes::EEContext&);
void fn__sceMpegErrorBdec_005025a0(p3fes::EEContext&);
void fn__sceMpegError_00502668(p3fes::EEContext&);
void fn__sceMpegFlushBuf_004fd7d0(p3fes::EEContext&);
void fn__sceMpegNextBit_004fd658(p3fes::EEContext&);
void fn__sceMpegPeepBit_004fd740(p3fes::EEContext&);
void fn__sceMpegStopIpuDma_00502500(p3fes::EEContext&);
void fn__sceMpegWaitIpuIdle64_004fd4d8(p3fes::EEContext&);
void fn__sceRemoveDmacHandler_00502e90(p3fes::EEContext&);
void fn__sceSifDmaStat_00503500(p3fes::EEContext&);
void fn__sceSifSetDma_00503520(p3fes::EEContext&);
void fn__sceSignalSema_00503180(p3fes::EEContext&);
void fn__sceWaitSema_005031a0(p3fes::EEContext&);
void fn__sce_DisableDmac_00502ed0(p3fes::EEContext&);
void fn__sce_EnableIntc_00502ea0(p3fes::EEContext&);
void fn__sce_iWakeupThread_005030a0(p3fes::EEContext&);
void fn__sceiSignalSema_00503190(p3fes::EEContext&);
void fn__sequenceHeader_004feee0(p3fes::EEContext&);
void fn__slice0_004fc3a8(p3fes::EEContext&);
void fn__waitIpuIdle_004fd868(p3fes::EEContext&);
void fn__waitIpuIdle_0_004ff998(p3fes::EEContext&);
void fn_adxstm_Create_00546010(p3fes::EEContext&);
void fn_atanf_0052e408(p3fes::EEContext&);
void fn_clndGetCurrentDay_0017da40(p3fes::EEContext&);
void fn_clndGetCurrentMonth_0017d920(p3fes::EEContext&);
void fn_clndIsDateInRange_0017e480(p3fes::EEContext&);
void fn_coshl_2_00545c38(p3fes::EEContext&);
void fn_crt_init_runtime_0050d658(p3fes::EEContext&);
void fn_datClearFlagAll_0016f2e0(p3fes::EEContext&);
void fn_datGetFlag_0016f190(p3fes::EEContext&);
void fn_datGetTime_0016ef30(p3fes::EEContext&);
void fn_datPersonaGetByPcId_00174800(p3fes::EEContext&);
void fn_datSetDaysSinceApr5_0016ef70(p3fes::EEContext&);
void fn_datSetFlag_0016f1f0(p3fes::EEContext&);
void fn_datUnitCreateEc_002ff3e0(p3fes::EEContext&);
void fn_datUnitIsGenusDead_002ff790(p3fes::EEContext&);
void fn_flushByteBoundary_004ffb38(p3fes::EEContext&);
void fn_j__sceMpegFlushBuf_0_004ff9d0(p3fes::EEContext&);
void fn_kwlnTaskCreateWithAutoPriority_00194b80(p3fes::EEContext&);
void fn_kwlnTaskCreate_00194b20(p3fes::EEContext&);
void fn_kwlnTaskDestroyWithHierarchy_00195020(p3fes::EEContext&);
void fn_main_00193980(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_name__C9type_info_0_0048ef10(p3fes::EEContext&);
void fn_nmCmdListAddRow_003c5a40(p3fes::EEContext&);
void fn_nmCmdListDestroy_003c5a20(p3fes::EEContext&);
void fn_nmCmdListSetDrawFunc_003c5e20(p3fes::EEContext&);
void fn_nmCmdListSetPosition_003c6d40(p3fes::EEContext&);
void fn_nmCmdListSetRowDrawFunc_003c5ee0(p3fes::EEContext&);
void fn_nmCmdListSetUpdateFunc_003c5e80(p3fes::EEContext&);
void fn_nmCmdListSort_003c7000(p3fes::EEContext&);
void fn_printf_005225a8(p3fes::EEContext&);
void fn_sceDbcCreateSocket_0051c770(p3fes::EEContext&);
void fn_sceDbcGetConnection_0051cad0(p3fes::EEContext&);
void fn_sceDbcGetModVersion_0051c360(p3fes::EEContext&);
void fn_sceDbcSendData3_0051d308(p3fes::EEContext&);
void fn_sceDbcSetWorkAddr_0051c700(p3fes::EEContext&);
void fn_sceDmaGetChan_004fa8f0(p3fes::EEContext&);
void fn_sceDmaSync_004faec0(p3fes::EEContext&);
void fn_sceInsockBind_2_00548b38(p3fes::EEContext&);
void fn_sceIpuInit_00502b08(p3fes::EEContext&);
void fn_sceMc2End_00513290(p3fes::EEContext&);
void fn_sceMc2GetInfoAsync_005136f8(p3fes::EEContext&);
void fn_sceMc2SearchFileAsync_005137b8(p3fes::EEContext&);
void fn_sceMc2Sync2_00514858(p3fes::EEContext&);
void fn_sceMpegClearRefBuff_00500e48(p3fes::EEContext&);
void fn_sceMpegReset_00500bb8(p3fes::EEContext&);
void fn_scePadGetModVersion_00512640(p3fes::EEContext&);
void fn_scePadInit2_005112d0(p3fes::EEContext&);
void fn_scePrintf_00505e48(p3fes::EEContext&);
void fn_sceSdRemoteCallbackInit_00512d48(p3fes::EEContext&);
void fn_sceSdRemoteInit_00512868(p3fes::EEContext&);
void fn_sceSdRemote_005129c0(p3fes::EEContext&);
void fn_sceSifBindRpc_00507050(p3fes::EEContext&);
void fn_sceSifCallRpc_00507230(p3fes::EEContext&);
void fn_sceSifInitRpc_005068a8(p3fes::EEContext&);
void fn_sceSifSetDma_00506088(p3fes::EEContext&);
void fn_sprintf_00523ac8(p3fes::EEContext&);
void fn_strcat_00523e68(p3fes::EEContext&);
void fn_strcmp_00524128(p3fes::EEContext&);
void fn_strcpy_00524270(p3fes::EEContext&);
void fn_strlen_00524388(p3fes::EEContext&);
void fn_sub_1043B0_001043b0(p3fes::EEContext&);
void fn_sub_10A4E0_0010a4e0(p3fes::EEContext&);
void fn_sub_16C470_0016c470(p3fes::EEContext&);
void fn_sub_16C5F0_0016c5f0(p3fes::EEContext&);
void fn_sub_16C670_0016c670(p3fes::EEContext&);
void fn_sub_16CDF0_0016cdf0(p3fes::EEContext&);
void fn_sub_16CEF0_0016cef0(p3fes::EEContext&);
void fn_sub_16CF40_0016cf40(p3fes::EEContext&);
void fn_sub_16CF90_0016cf90(p3fes::EEContext&);
void fn_sub_16CFE0_0016cfe0(p3fes::EEContext&);
void fn_sub_16D090_0016d090(p3fes::EEContext&);
void fn_sub_16D160_0016d160(p3fes::EEContext&);
void fn_sub_16D230_0016d230(p3fes::EEContext&);
void fn_sub_16D6B0_0016d6b0(p3fes::EEContext&);
void fn_sub_16D8B0_0016d8b0(p3fes::EEContext&);
void fn_sub_16D930_0016d930(p3fes::EEContext&);
void fn_sub_16D980_0016d980(p3fes::EEContext&);
void fn_sub_16DA50_0016da50(p3fes::EEContext&);
void fn_sub_16DB70_0016db70(p3fes::EEContext&);
void fn_sub_16DD60_0016dd60(p3fes::EEContext&);
void fn_sub_16E930_0016e930(p3fes::EEContext&);
void fn_sub_16E990_0016e990(p3fes::EEContext&);
void fn_sub_16F150_0016f150(p3fes::EEContext&);
void fn_sub_16F180_0016f180(p3fes::EEContext&);
void fn_sub_16F320_0016f320(p3fes::EEContext&);
void fn_sub_16F450_0016f450(p3fes::EEContext&);
void fn_sub_16FEA0_0016fea0(p3fes::EEContext&);
void fn_sub_170860_00170860(p3fes::EEContext&);
void fn_sub_170B20_00170b20(p3fes::EEContext&);
void fn_sub_170B90_00170b90(p3fes::EEContext&);
void fn_sub_175820_00175820(p3fes::EEContext&);
void fn_sub_175BE0_00175be0(p3fes::EEContext&);
void fn_sub_175C70_00175c70(p3fes::EEContext&);
void fn_sub_175CE0_00175ce0(p3fes::EEContext&);
void fn_sub_176100_00176100(p3fes::EEContext&);
void fn_sub_1761B0_001761b0(p3fes::EEContext&);
void fn_sub_1764B0_001764b0(p3fes::EEContext&);
void fn_sub_176840_00176840(p3fes::EEContext&);
void fn_sub_1768E0_001768e0(p3fes::EEContext&);
void fn_sub_1773D0_001773d0(p3fes::EEContext&);
void fn_sub_1779A0_001779a0(p3fes::EEContext&);
void fn_sub_177CE0_00177ce0(p3fes::EEContext&);
void fn_sub_17ADF0_0017adf0(p3fes::EEContext&);
void fn_sub_17B160_0017b160(p3fes::EEContext&);
void fn_sub_17B1A0_0017b1a0(p3fes::EEContext&);
void fn_sub_17B2A0_0017b2a0(p3fes::EEContext&);
void fn_sub_17C190_0017c190(p3fes::EEContext&);
void fn_sub_17C280_0017c280(p3fes::EEContext&);
void fn_sub_17D3C0_0017d3c0(p3fes::EEContext&);
void fn_sub_17D610_0017d610(p3fes::EEContext&);
void fn_sub_17D6D0_0017d6d0(p3fes::EEContext&);
void fn_sub_17D700_0017d700(p3fes::EEContext&);
void fn_sub_17D7C0_0017d7c0(p3fes::EEContext&);
void fn_sub_17D800_0017d800(p3fes::EEContext&);
void fn_sub_182C50_00182c50(p3fes::EEContext&);
void fn_sub_1830C0_001830c0(p3fes::EEContext&);
void fn_sub_188860_00188860(p3fes::EEContext&);
void fn_sub_198590_00198590(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_19D400_0019d400(p3fes::EEContext&);
void fn_sub_1A01C0_001a01c0(p3fes::EEContext&);
void fn_sub_1A0310_001a0310(p3fes::EEContext&);
void fn_sub_1A4580_001a4580(p3fes::EEContext&);
void fn_sub_1A7710_001a7710(p3fes::EEContext&);
void fn_sub_1ACB70_001acb70(p3fes::EEContext&);
void fn_sub_1AFD40_001afd40(p3fes::EEContext&);
void fn_sub_1B0220_001b0220(p3fes::EEContext&);
void fn_sub_1C71F0_001c71f0(p3fes::EEContext&);
void fn_sub_1CD7A0_001cd7a0(p3fes::EEContext&);
void fn_sub_1DE630_001de630(p3fes::EEContext&);
void fn_sub_1DED40_001ded40(p3fes::EEContext&);
void fn_sub_1FA0D0_001fa0d0(p3fes::EEContext&);
void fn_sub_1FB4B0_001fb4b0(p3fes::EEContext&);
void fn_sub_1FC1F0_001fc1f0(p3fes::EEContext&);
void fn_sub_21C3F0_0021c3f0(p3fes::EEContext&);
void fn_sub_21CCA0_0021cca0(p3fes::EEContext&);
void fn_sub_21D3B0_0021d3b0(p3fes::EEContext&);
void fn_sub_21E380_0021e380(p3fes::EEContext&);
void fn_sub_25B440_0025b440(p3fes::EEContext&);
void fn_sub_25CD30_0025cd30(p3fes::EEContext&);
void fn_sub_25CEB0_0025ceb0(p3fes::EEContext&);
void fn_sub_316E00_00316e00(p3fes::EEContext&);
void fn_sub_3174E0_003174e0(p3fes::EEContext&);
void fn_sub_318540_00318540(p3fes::EEContext&);
void fn_sub_318990_00318990(p3fes::EEContext&);
void fn_sub_318A90_00318a90(p3fes::EEContext&);
void fn_sub_318AD0_00318ad0(p3fes::EEContext&);
void fn_sub_318B60_00318b60(p3fes::EEContext&);
void fn_sub_318B80_00318b80(p3fes::EEContext&);
void fn_sub_319190_00319190(p3fes::EEContext&);
void fn_sub_31C1D0_0031c1d0(p3fes::EEContext&);
void fn_sub_3210A0_003210a0(p3fes::EEContext&);
void fn_sub_323FB0_00323fb0(p3fes::EEContext&);
void fn_sub_3243F0_003243f0(p3fes::EEContext&);
void fn_sub_324510_00324510(p3fes::EEContext&);
void fn_sub_343860_00343860(p3fes::EEContext&);
void fn_sub_34FCF0_0034fcf0(p3fes::EEContext&);
void fn_sub_3A52C0_003a52c0(p3fes::EEContext&);
void fn_sub_3B54C0_003b54c0(p3fes::EEContext&);
void fn_sub_3B5D50_003b5d50(p3fes::EEContext&);
void fn_sub_3B7090_003b7090(p3fes::EEContext&);
void fn_sub_3C44D0_003c44d0(p3fes::EEContext&);
void fn_sub_3C58F0_003c58f0(p3fes::EEContext&);
void fn_sub_3C6D60_003c6d60(p3fes::EEContext&);
void fn_sub_3C6EE0_003c6ee0(p3fes::EEContext&);
void fn_sub_3F00D0_003f00d0(p3fes::EEContext&);
void fn_sub_3F03E0_003f03e0(p3fes::EEContext&);
void fn_sub_3F2320_003f2320(p3fes::EEContext&);
void fn_sub_3F25E0_003f25e0(p3fes::EEContext&);
void fn_sub_3F2940_003f2940(p3fes::EEContext&);
void fn_sub_3F3970_003f3970(p3fes::EEContext&);
void fn_sub_3F39A0_003f39a0(p3fes::EEContext&);
void fn_sub_3F3DC0_003f3dc0(p3fes::EEContext&);
void fn_sub_3F3E60_003f3e60(p3fes::EEContext&);
void fn_sub_3FFBB0_003ffbb0(p3fes::EEContext&);
void fn_sub_4353F0_004353f0(p3fes::EEContext&);
void fn_sub_488F30_00488f30(p3fes::EEContext&);
void fn_sub_48EDE0_0048ede0(p3fes::EEContext&);
void fn_sub_48EE30_0048ee30(p3fes::EEContext&);
void fn_sub_48EE80_0048ee80(p3fes::EEContext&);
void fn_sub_48EED0_0048eed0(p3fes::EEContext&);
void fn_sub_48EF20_0048ef20(p3fes::EEContext&);
void fn_sub_48EF30_0048ef30(p3fes::EEContext&);
void fn_sub_48EF40_0048ef40(p3fes::EEContext&);
void fn_sub_4916D0_004916d0(p3fes::EEContext&);
void fn_sub_4BDDE0_004bdde0(p3fes::EEContext&);
void fn_sub_4C2CC0_004c2cc0(p3fes::EEContext&);
void fn_sub_4C2D20_004c2d20(p3fes::EEContext&);
void fn_sub_4C2F10_004c2f10(p3fes::EEContext&);
void fn_sub_4C69F0_004c69f0(p3fes::EEContext&);
void fn_sub_4CB270_004cb270(p3fes::EEContext&);
void fn_sub_4CB6E0_004cb6e0(p3fes::EEContext&);
void fn_sub_4CB7F0_004cb7f0(p3fes::EEContext&);
void fn_sub_4D0F00_004d0f00(p3fes::EEContext&);
void fn_sub_4D1170_004d1170(p3fes::EEContext&);
void fn_sub_4D11F0_004d11f0(p3fes::EEContext&);
void fn_sub_5067F8_005067f8(p3fes::EEContext&);
void fn_sub_50DC90_0050dc90(p3fes::EEContext&);
void fn_sub_50DCA0_0050dca0(p3fes::EEContext&);
void fn_sub_532F60_00532f60(p3fes::EEContext&);
void fn_sub_5331A8_005331a8(p3fes::EEContext&);
void fn_sub_535E58_00535e58(p3fes::EEContext&);
void fn_sub_536058_00536058(p3fes::EEContext&);
void fn_sub_5369E8_005369e8(p3fes::EEContext&);
void fn_sub_537450_00537450(p3fes::EEContext&);
void fn_sub_538860_00538860(p3fes::EEContext&);
void fn_sub_538D78_00538d78(p3fes::EEContext&);
void fn_sub_539760_00539760(p3fes::EEContext&);
void fn_sub_5397B8_005397b8(p3fes::EEContext&);
void fn_sub_539818_00539818(p3fes::EEContext&);
void fn_sub_539830_00539830(p3fes::EEContext&);
void fn_sub_539848_00539848(p3fes::EEContext&);
void fn_sub_539850_00539850(p3fes::EEContext&);
void fn_sub_53AD70_0053ad70(p3fes::EEContext&);
void fn_sub_53AE08_0053ae08(p3fes::EEContext&);
void fn_sub_53B080_0053b080(p3fes::EEContext&);
void fn_sub_53DD98_0053dd98(p3fes::EEContext&);
void fn_sub_53E088_0053e088(p3fes::EEContext&);
void fn_sub_53E0A0_0053e0a0(p3fes::EEContext&);
void fn_sub_53F640_0053f640(p3fes::EEContext&);
void fn_sub_5400B0_005400b0(p3fes::EEContext&);
void fn_sub_540118_00540118(p3fes::EEContext&);
void fn_sub_540ED8_00540ed8(p3fes::EEContext&);
void fn_sub_540FE0_00540fe0(p3fes::EEContext&);
void fn_sub_5414E0_005414e0(p3fes::EEContext&);
void fn_sub_5419C0_005419c0(p3fes::EEContext&);
void fn_sub_5419F0_005419f0(p3fes::EEContext&);
void fn_sub_541D48_00541d48(p3fes::EEContext&);
void fn_sub_543100_00543100(p3fes::EEContext&);
void fn_sub_543130_00543130(p3fes::EEContext&);
void fn_sub_543178_00543178(p3fes::EEContext&);
void fn_sub_545C40_00545c40(p3fes::EEContext&);
void fn_sub_545C78_00545c78(p3fes::EEContext&);
void fn_sub_546088_00546088(p3fes::EEContext&);
void fn_sub_546150_00546150(p3fes::EEContext&);
void fn_sub_5465D0_005465d0(p3fes::EEContext&);
void fn_sub_546708_00546708(p3fes::EEContext&);
void fn_sub_5489A0_005489a0(p3fes::EEContext&);
void fn_sub_548AD0_00548ad0(p3fes::EEContext&);
void fn_sub_5491B0_005491b0(p3fes::EEContext&);
void fn_sub_5497B0_005497b0(p3fes::EEContext&);
void fn_sub_54CD40_0054cd40(p3fes::EEContext&);
void fn_sub_553FA8_00553fa8(p3fes::EEContext&);
void fn_sub_555658_00555658(p3fes::EEContext&);
void fn_sub_559DA8_00559da8(p3fes::EEContext&);
void fn_sub_559FD8_00559fd8(p3fes::EEContext&);
void fn_sub_55D240_0055d240(p3fes::EEContext&);
void fn_sub_55D3A8_0055d3a8(p3fes::EEContext&);
void fn_sub_55D668_0055d668(p3fes::EEContext&);
void fn_sub_55DB88_0055db88(p3fes::EEContext&);
void fn_sub_55DBA8_0055dba8(p3fes::EEContext&);
void fn_sub_55DBC0_0055dbc0(p3fes::EEContext&);
void fn_sub_55DBE8_0055dbe8(p3fes::EEContext&);
void fn_sub_55DC88_0055dc88(p3fes::EEContext&);
void fn_sub_560C88_00560c88(p3fes::EEContext&);
void fn_sub_560D20_00560d20(p3fes::EEContext&);
void fn_sub_560EB0_00560eb0(p3fes::EEContext&);
void fn_sub_561870_00561870(p3fes::EEContext&);
void fn_sub_562288_00562288(p3fes::EEContext&);
void fn_sub_562E10_00562e10(p3fes::EEContext&);
void fn_sub_562E90_00562e90(p3fes::EEContext&);
void fn_sub_563C28_00563c28(p3fes::EEContext&);
void fn_sub_564978_00564978(p3fes::EEContext&);
void fn_sub_564990_00564990(p3fes::EEContext&);
void fn_sub_564DD0_00564dd0(p3fes::EEContext&);
void fn_sub_564FE8_00564fe8(p3fes::EEContext&);
void fn_sub_565058_00565058(p3fes::EEContext&);
void fn_sub_565550_00565550(p3fes::EEContext&);
void fn_sub_5656C0_005656c0(p3fes::EEContext&);
void fn_sub_5656F0_005656f0(p3fes::EEContext&);
void fn_sub_577FC8_00577fc8(p3fes::EEContext&);
void fn_sub_578160_00578160(p3fes::EEContext&);
void fn_sub_57BFB8_0057bfb8(p3fes::EEContext&);
void fn_sub_57D380_0057d380(p3fes::EEContext&);
void fn_sub_57E210_0057e210(p3fes::EEContext&);
void fn_sub_57E290_0057e290(p3fes::EEContext&);
void fn_sub_57FC60_0057fc60(p3fes::EEContext&);
void fn_sub_580628_00580628(p3fes::EEContext&);
void fn_sub_582810_00582810(p3fes::EEContext&);
void fn_sub_583470_00583470(p3fes::EEContext&);
void fn_sub_585100_00585100(p3fes::EEContext&);
void fn_sub_585590_00585590(p3fes::EEContext&);
void fn_sub_5864C0_005864c0(p3fes::EEContext&);
void fn_sub_589EC8_00589ec8(p3fes::EEContext&);
void fn_sub_589F00_00589f00(p3fes::EEContext&);
void fn_sub_58BE40_0058be40(p3fes::EEContext&);
void fn_sub_58C060_0058c060(p3fes::EEContext&);
void fn_sub_593FE8_00593fe8(p3fes::EEContext&);
void fn_sub_594038_00594038(p3fes::EEContext&);
void fn_sub_5940A0_005940a0(p3fes::EEContext&);
void fn_sub_594108_00594108(p3fes::EEContext&);
void fn_sub_5973C0_005973c0(p3fes::EEContext&);
void fn_sub_597E20_00597e20(p3fes::EEContext&);
void fn_width__CQ24_STL8ios_base_0_00562218(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
namespace L = sweep5b_layout;

// 0x00100008 start -- 520 bytes; leaf frame (no stack)
// The ELF entry (crt0): clears every GPR (128-bit), HI/LO, SA, the FPRs and FCR31; zeroes .bss (bytes up to a 16-byte
// boundary, then quadwords, then the tail bytes); SetupThread (syscall 60, $gp = gp_base, stack at 0x1F60000) and
// SetupHeap (syscall 61); crt_init_runtime, FlushCache(0), ei, then main(argc, argv) from crt0_args. Never returns.
void start(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, t8{ctx, 24}, t9{ctx, 25}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15}, f16{ctx, 16}, f17{ctx, 17}, f18{ctx, 18}, f19{ctx, 19}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25}, f26{ctx, 26}, f27{ctx, 27}, f28{ctx, 28}, f29{ctx, 29}, f30{ctx, 30}, f31{ctx, 31};
    // 0x00100008
    enter(ctx, 73);  // entry check point + this block's cycles
    padduw(at, zero, zero);
    padduw(v0, zero, zero);
    padduw(v1, zero, zero);
    padduw(a0, zero, zero);
    padduw(a1, zero, zero);
    padduw(a2, zero, zero);
    padduw(a3, zero, zero);
    padduw(t0, zero, zero);
    padduw(t1, zero, zero);
    padduw(t2, zero, zero);
    padduw(t3, zero, zero);
    padduw(t4, zero, zero);
    padduw(t5, zero, zero);
    padduw(t6, zero, zero);
    padduw(t7, zero, zero);
    padduw(s0, zero, zero);
    padduw(s1, zero, zero);
    padduw(s2, zero, zero);
    padduw(s3, zero, zero);
    padduw(s4, zero, zero);
    padduw(s5, zero, zero);
    padduw(s6, zero, zero);
    padduw(s7, zero, zero);
    padduw(t8, zero, zero);
    padduw(t9, zero, zero);
    padduw(gp, zero, zero);
    padduw(sp, zero, zero);
    padduw(fp, zero, zero);
    padduw(ra, zero, zero);
    mthi(zero);
    mthi1(zero);
    mtlo(zero);
    mtlo1(zero);
    mtsah(zero, 0);
    mtc1(zero, f0);
    mtc1(zero, f1);
    mtc1(zero, f2);
    mtc1(zero, f3);
    mtc1(zero, f4);
    mtc1(zero, f5);
    mtc1(zero, f6);
    mtc1(zero, f7);
    mtc1(zero, f8);
    mtc1(zero, f9);
    mtc1(zero, f10);
    mtc1(zero, f11);
    mtc1(zero, f12);
    mtc1(zero, f13);
    mtc1(zero, f14);
    mtc1(zero, f15);
    mtc1(zero, f16);
    mtc1(zero, f17);
    mtc1(zero, f18);
    mtc1(zero, f19);
    mtc1(zero, f20);
    mtc1(zero, f21);
    mtc1(zero, f22);
    mtc1(zero, f23);
    mtc1(zero, f24);
    mtc1(zero, f25);
    mtc1(zero, f26);
    mtc1(zero, f27);
    mtc1(zero, f28);
    mtc1(zero, f29);
    mtc1(zero, f30);
    mtc1(zero, f31);
    adda_s(f0, f1);
    sync(ctx, 16);
    ctc1(zero, 31);
    v0 = 0x7D0000;
    v1 = 0x9B0000;
    v0 = addiu(v0, -8576);  // &bss_start
    v1 = addiu(v1, -13184);  // &0x9ACC80
    for (;;) {
        // 0x0010012c
        charge(ctx, 3);
        a0 = v0 & 0xF;
        if (a0 == 0) {
            break;
        }
        // 0x00100138
        charge(ctx, 5);
        sb(zero, v0, 0);
        v0 = addiu(v0, 1);
        backedge(ctx);
    }
    // 0x0010014c
    charge(ctx, 3);
    a0 = lui(0xFFFF);
    a0 = a0 | 0xFFF0;
    a0 = v1 & a0;
    for (;;) {
        // 0x00100158
        charge(ctx, 2);
        if (v0 == a0) {
            break;
        }
        // 0x00100160
        charge(ctx, 6);
        sq(zero, v0, 0);
        v0 = addiu(v0, 16);
        backedge(ctx);
    }
    for (;;) {
        // 0x00100178
        charge(ctx, 2);
        if (v0 == v1) {
            break;
        }
        // 0x00100180
        charge(ctx, 6);
        sb(zero, v0, 0);
        v0 = addiu(v0, 1);
        backedge(ctx);
    }
    // 0x00100198
    charge(ctx, 30);
    a0 = 0x7D0000;
    a1 = 0x1F60000;
    a2 = 0xA0000;
    a3 = 0x960000;
    t0 = 0x100000;
    a0 = addiu(a0, 11504);  // &gp_base
    a1 = addiu(a1, 0);  // &0x1F60000
    a2 = addiu(a2, 0);
    a3 = addiu(a3, -15744);  // &crt0_args
    t0 = addiu(t0, 544);  // &_sceExitThread
    gp = a0;
    v1 = 60;
    syscall(ctx, 0x1001C8u);
    sp = v0;
    a0 = 0x9B0000;
    a1 = 0x0;
    a0 = addiu(a0, -13184);  // &0x9ACC80
    a1 = addiu(a1, -1);
    v1 = 61;
    syscall(ctx, 0x1001E4u);
    jal(ctx, 0x1001E8u, gen::fn_crt_init_runtime_0050d658);
    a0 = 0;
    jal(ctx, 0x1001F0u, gen::fn__sceFlushCache_005033e0);
    ei(ctx);
    v0 = 0x960000;
    v0 = addiu(v0, -15744);  // &crt0_args
    lw(a0, v0, 0);  // crt0_args
    a1 = addiu(v0, 4);  // &0x95C284
    jal(ctx, 0x100208u, gen::fn_main_00193980);  // does not return
}

// 0x00191260 H_Memcard_UpdateChkAreaSeq -- 988 bytes; frame 0x20: ra sp+0x0
// The boot-up memory-card area check, one step per call ($gp state +232 = 0..3): builds the save-folder search path
// (FES "BASLUS-21621SaveG%d" / "BASLUS-21621Save%d" / the Journey "BASLUS-21569Save%d") and drives
// sceMc2GetInfoAsync / sceMc2SearchFileAsync through H_Memcard_Check; the result goes back to the state words.
void H_Memcard_UpdateChkAreaSeq(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00191260
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x0);
    a0 = 0x5E0000;
    a0 = addiu(a0, 19472);  // " ### ChkMemcardAreaSeq = %d ###\n"
    lw(a1, gp, -19636);  // 0x7CE03C
    jal(ctx, 0x191274u, gen::fn_printf_005225a8);
    lw(a0, gp, -19636);  // 0x7CE03C
    v0 = 3;
    if (a0 == v0) {
        // 0x0019151c
        charge(ctx, 8);
        a0 = addiu(sp, 0x1C);
        a1 = addiu(sp, 0x18);
        a2 = addiu(sp, 0x14);
        jal(ctx, 0x191528u, gen::fn_H_Memcard_Check_0018f190);
        a0 = 1;
        if (v0 != a0) {
        L_00191628:
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x0019153c
            charge(ctx, 3);
            lw(v0, sp, 0x14);
            if (v0 != 0) {
                // 0x00191618
                charge(ctx, 4);
                sw(a0, gp, -19672);  // 0x7CE018
                v0 = 100;
            } else {
                // 0x00191548
                charge(ctx, 4);
                lw(v1, sp, 0x18);
                v0 = 2;
                if (v1 == v0) {
                    // 0x001915c0
                    charge(ctx, 6);
                    lw(v0, gp, -19644);  // 0x7CE034
                    v1 = addiu(v0, 1);
                    sw(v1, gp, -19644);  // 0x7CE034
                    v0 = 16;
                    if (v1 == v0) {
                        // 0x001915d8
                        charge(ctx, 3);
                        lw(v0, gp, -19680);  // 0x7CE010
                        if (v0 != a0) {
                            // 0x00191600
                            charge(ctx, 2);
                            sw(zero, gp, -19644);  // 0x7CE034
                            sw(a0, gp, -19680);  // 0x7CE010
                            goto L_00191608;
                        }
                        // 0x001915e4
                        charge(ctx, 4);
                        lw(v1, gp, -19676);  // 0x7CE014
                        v0 = 100;
                        if (v1 != v0) {
                            // 0x001915f4
                            charge(ctx, 1);
                            v0 = si(-6);
                        }
                        // 0x001915f8
                        charge(ctx, 2);
                        // 0x0019162c (the shared epilogue, written out on this path)
                        charge(ctx, 4);
                        ld(ra, sp, 0x0);
                        sp = addiu(sp, 0x20);
                        return;
                    }
                L_00191608:
                    charge(ctx, 4);
                    v0 = 2;
                    sw(v0, gp, -19636);  // 0x7CE03C
                    goto L_00191628;
                }
                // 0x00191558
                charge(ctx, 3);
                v0 = 19;
                if (v1 == v0) {
                    // 0x001915b4
                    charge(ctx, 3);
                    v0 = si(-5);
                } else {
                    // 0x00191564
                    charge(ctx, 3);
                    v0 = 22;
                    if (v1 == v0) {
                        // 0x001915a8
                        charge(ctx, 3);
                        v0 = si(-5);
                    } else {
                        // 0x00191570
                        charge(ctx, 3);
                        v0 = 111;
                        if (v1 == v0) {
                            // 0x0019159c
                            charge(ctx, 3);
                            v0 = si(-5);
                        } else {
                            // 0x0019157c
                            charge(ctx, 3);
                            v0 = 0x9003;
                            if (v1 != v0) {
                                // 0x00191588
                                charge(ctx, 2);
                                goto L_00191628;
                            }
                            // 0x00191590
                            charge(ctx, 3);
                            v0 = si(-5);
                        }
                    }
                }
            }
        }
    } else {
        // 0x0019128c
        charge(ctx, 3);
        v0 = 2;
        if (a0 == v0) {
            // 0x00191448
            charge(ctx, 8);
            a0 = addiu(sp, 0x1C);
            a1 = addiu(sp, 0x18);
            a2 = addiu(sp, 0x14);
            jal(ctx, 0x191454u, gen::fn_H_Memcard_Check_0018f190);
            v1 = si(-1);
            if (v0 == v1) {
                // 0x00191468
                charge(ctx, 3);
                lw(v0, gp, -19684);  // 0x7CE00C
                if (v0 == 0) {
                    // 0x0019149c
                    charge(ctx, 3);
                    lw(v0, gp, -19680);  // 0x7CE010
                    if (v0 != 0) {
                        // 0x001914d0
                        charge(ctx, 8);
                        lw(a2, gp, -19644);  // 0x7CE034
                        a0 = 0x840000;
                        a0 = addiu(a0, 28064);  // &0x846DA0
                        a1 = 0x5E0000;
                        a1 = addiu(a1, 18592);  // "/BASLUS-21621Save%d/BASLUS-21621Save%d"
                        a3 = a2;
                        jal(ctx, 0x1914E8u, gen::fn_sprintf_00523ac8);
                    } else {
                        // 0x001914a8
                        charge(ctx, 10);
                        lw(a2, gp, -19644);  // 0x7CE034
                        a0 = 0x840000;
                        a0 = addiu(a0, 28064);  // &0x846DA0
                        a1 = 0x5E0000;
                        a1 = addiu(a1, 18544);  // "/BASLUS-21621SaveG%d/BASLUS-21621SaveG%d"
                        a3 = a2;
                        jal(ctx, 0x1914C0u, gen::fn_sprintf_00523ac8);
                    }
                } else {
                    // 0x00191474
                    charge(ctx, 10);
                    lw(a2, gp, -19644);  // 0x7CE034
                    a0 = 0x840000;
                    a0 = addiu(a0, 28064);  // &0x846DA0
                    a1 = 0x5E0000;
                    a1 = addiu(a1, 18496);  // "/BASLUS-21569Save%d/BASLUS-21569Save%d"
                    a3 = a2;
                    jal(ctx, 0x19148Cu, gen::fn_sprintf_00523ac8);
                }
                // 0x001914f0
                charge(ctx, 11);
                lw(a0, gp, -19660);  // 0x7CE024
                a1 = 0x840000;
                a1 = addiu(a1, 28064);  // &0x846DA0
                a2 = 0x840000;
                a2 = addiu(a2, 27776);  // &0x846C80
                jal(ctx, 0x191504u, gen::fn_sceMc2SearchFileAsync_005137b8);
                v0 = 3;
                sw(v0, gp, -19636);  // 0x7CE03C
            }
            goto L_00191628;
        }
        // 0x00191298
        charge(ctx, 3);
        v1 = 1;
        if (a0 != v1) {
            // 0x001912a4
            charge(ctx, 2);
            if (a0 == 0) {
                // 0x001912b4
                charge(ctx, 14);
                v0 = si(-1);
                sw(v0, gp, -19676);  // 0x7CE014
                sw(v1, gp, -19672);  // 0x7CE018
                sw(zero, sp, 0x1C);
                sw(zero, sp, 0x18);
                sw(zero, gp, -19680);  // 0x7CE010
                a0 = addiu(sp, 0x1C);
                a1 = addiu(sp, 0x18);
                a2 = addiu(sp, 0x14);
                jal(ctx, 0x1912D8u, gen::fn_H_Memcard_Check_0018f190);
                v1 = si(-1);
                if (v0 == v1) {
                    // 0x001912ec
                    charge(ctx, 9);
                    lw(a0, gp, -19660);  // 0x7CE024
                    a1 = 0x840000;
                    a1 = addiu(a1, 28320);  // &0x846EA0
                    jal(ctx, 0x1912F8u, gen::fn_sceMc2GetInfoAsync_005136f8);
                    v0 = 1;
                    sw(v0, gp, -19636);  // 0x7CE03C
                }
            } else {
                // 0x001912ac
                charge(ctx, 2);
            }
            goto L_00191628;
        }
        // 0x00191310
        charge(ctx, 8);
        a0 = addiu(sp, 0x1C);
        a1 = addiu(sp, 0x18);
        a2 = addiu(sp, 0x14);
        jal(ctx, 0x19131Cu, gen::fn_H_Memcard_Check_0018f190);
        v1 = 1;
        if (v0 != v1) {
            goto L_00191628;
        }
        // 0x00191330
        charge(ctx, 3);
        lw(v0, sp, 0x14);
        if (v0 != 0) {
            // 0x001913dc
            charge(ctx, 5);
            v0 = 0x840000;
            lw(v0, v0, 28320);  // 0x846EA0
            v1 = 2;
            if (v0 != v1) {
                // 0x0019143c
                charge(ctx, 3);
                v0 = si(-1);
            } else {
                // 0x001913f0
                charge(ctx, 5);
                v0 = 0x840000;
                lw(v0, v0, 28328);  // 0x846EA8
                v0 = slti(v0, 78);
                if (v0 != 0) {
                    // 0x00191430
                    charge(ctx, 3);
                    sw(v1, gp, -19636);  // 0x7CE03C
                    goto L_00191628;
                }
                // 0x00191404
                charge(ctx, 3);
                lw(v0, gp, -19672);  // 0x7CE018
                if (v0 == 0) {
                    // 0x0019141c
                    charge(ctx, 5);
                    v0 = 100;
                    sw(v0, gp, -19676);  // 0x7CE014
                    sw(v1, gp, -19636);  // 0x7CE03C
                    goto L_00191628;
                }
                // 0x00191410
                charge(ctx, 3);
                v0 = 100;
            }
        } else {
            // 0x0019133c
            charge(ctx, 4);
            lw(v1, sp, 0x18);
            v0 = 47;
            if (v1 == v0) {
                // 0x001913c4
                charge(ctx, 3);
                v0 = 100;
            } else {
                // 0x0019134c
                charge(ctx, 3);
                v0 = 0x9001;
                if (v1 == v0) {
                    // 0x001913b8
                    charge(ctx, 3);
                    v0 = si(-4);
                } else {
                    // 0x00191358
                    charge(ctx, 3);
                    v0 = 0x9003;
                    if (v1 == v0) {
                        // 0x0019139c
                        charge(ctx, 7);
                        lw(a0, gp, -19660);  // 0x7CE024
                        a1 = 0x840000;
                        a1 = addiu(a1, 28320);  // &0x846EA0
                        jal(ctx, 0x1913A8u, gen::fn_sceMc2GetInfoAsync_005136f8);
                        goto L_00191628;
                    }
                    // 0x00191364
                    charge(ctx, 3);
                    v0 = 19;
                    if (v1 == v0) {
                        // 0x00191390
                        charge(ctx, 3);
                        v0 = si(-5);
                    } else {
                        // 0x00191370
                        charge(ctx, 3);
                        v0 = 111;
                        if (v1 == v0) {
                            // 0x00191384
                            charge(ctx, 3);
                            v0 = si(-5);
                        } else {
                            // 0x0019137c
                            charge(ctx, 2);
                            // 0x001913d0
                            charge(ctx, 3);
                            v0 = si(-9);
                        }
                    }
                }
            }
        }
    }
    // 0x0019162c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0019D320 kwlnVsyncFieldGate -- 64 bytes; leaf frame (no stack)
// [proposed role: VBLANK_START gate] INTC 2 handler: sync; ei; reads GS CSR (0x12001000) bit 13 (FIELD) and returns
// 0 for the odd field, -1 for the even one, so RenderWare's flip runs on one field only.
void kwlnVsyncFieldGate(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0019d320
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x12000000;
    ld(v0, v0, 4096);  // 0x12001000
    v0 = dsrl(v0, 13);
    v0 = v0 & 0x1;
    if (v0 != 0) {
        // 0x0019d34c
        charge(ctx, 3);
        sync(ctx, 0);
        ei(ctx);
        v0 = 0;
    } else {
        // 0x0019d338
        charge(ctx, 5);
        sync(ctx, 0);
        ei(ctx);
        v0 = si(-1);
    }
    // 0x0019d358 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x001A0430 sub_1A0430 -- 352 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [proposed name: K_FldObj_SetFlag31ById] Set or clear bit 31 of +40 of a field object by its id (a0: kind in bits 10..15, 1 / 2 / 3; a1 = 1
// sets it), the object looked up through sub_3B54C0 in the current scene's (*(0x7CD540)+8) object table.
void sub_1A0430(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a0430
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a2 = a0;
    s0 = a1;
    a0 = a2 & 0xFFFF;
    v1 = 0xF0000;
    v1 = v1 | 0xFC00;
    v1 = a0 & v1;
    a0 = sra(v1, 10);
    v1 = 1;
    if (a0 != v1) {
        // 0x001a04bc
        charge(ctx, 3);
        v1 = 3;
        if (a0 != v1) {
            // 0x001a0520
            charge(ctx, 3);
            v1 = 2;
            if (a0 == v1) {
                // 0x001a052c
                charge(ctx, 7);
                lw(v0, gp, -22448);  // 0x7CD540: the current scene
                lw(a0, v0, 8);
                a1 = a2;
                jal(ctx, 0x1A0538u, gen::fn_sub_3B54C0_003b54c0);
                if (v0 != 0) {
                    // 0x001a0548
                    charge(ctx, 3);
                    v1 = 1;
                    if (s0 != v1) {
                        // 0x001a056c
                        charge(ctx, 4);
                        lw(v1, v0, L::kObjFlags);
                        v1 = dsll32(v1, 1);
                        v1 = dsrl32(v1, 1);
                        sw(v1, v0, L::kObjFlags);
                    } else {
                        // 0x001a0554
                        charge(ctx, 6);
                        lw(a0, v0, L::kObjFlags);
                        v1 = lui(0x8000);  // bit 31
                        v1 = a0 | v1;
                        sw(v1, v0, L::kObjFlags);
                    }
                }
            }
        } else {
            // 0x001a04c8
            charge(ctx, 7);
            lw(v0, gp, -22448);  // 0x7CD540: the current scene
            lw(a0, v0, 8);
            a1 = a2;
            jal(ctx, 0x1A04D4u, gen::fn_sub_3B54C0_003b54c0);
            if (v0 != 0) {
                // 0x001a04e4
                charge(ctx, 3);
                v1 = 1;
                if (s0 != v1) {
                    // 0x001a0508
                    charge(ctx, 6);
                    lw(v1, v0, L::kObjFlags);
                    v1 = dsll32(v1, 1);
                    v1 = dsrl32(v1, 1);
                    sw(v1, v0, L::kObjFlags);
                } else {
                    // 0x001a04f0
                    charge(ctx, 6);
                    lw(a0, v0, L::kObjFlags);
                    v1 = lui(0x8000);  // bit 31
                    v1 = a0 | v1;
                    sw(v1, v0, L::kObjFlags);
                }
            }
        }
    } else {
        // 0x001a0464
        charge(ctx, 7);
        lw(v0, gp, -22448);  // 0x7CD540: the current scene
        lw(a0, v0, 8);
        a1 = a2;
        jal(ctx, 0x1A0470u, gen::fn_sub_3B54C0_003b54c0);
        if (v0 != 0) {
            // 0x001a0480
            charge(ctx, 3);
            v1 = 1;
            if (s0 != v1) {
                // 0x001a04a4
                charge(ctx, 6);
                lw(v1, v0, L::kObjFlags);
                v1 = dsll32(v1, 1);
                v1 = dsrl32(v1, 1);
                sw(v1, v0, L::kObjFlags);
            } else {
                // 0x001a048c
                charge(ctx, 6);
                lw(a0, v0, L::kObjFlags);
                v1 = lui(0x8000);  // bit 31
                v1 = a0 | v1;
                sw(v1, v0, L::kObjFlags);
            }
        }
    }
    // 0x001a057c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001A0700 sub_1A0700 -- 232 bytes; frame 0x10: ra sp+0x0
// [proposed name: K_FldObj_GetVecAById] A field object's position block by id: sub_3B54C0 on the scene table, then +300 (kinds 1 and 3) or +284 (kind 2);
// 0 when the object or the kind is missing.
void sub_1A0700(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a0700
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a1 = a0;
    v1 = a1 & 0xFFFF;
    v0 = 0xF0000;
    v0 = v0 | 0xFC00;
    v0 = v1 & v0;
    v1 = sra(v0, L::kObjKindShift);  // the id's kind
    v0 = 1;
    if (v1 != v0) {
        // 0x001a075c
        charge(ctx, 3);
        v0 = 3;
        if (v1 != v0) {
            // 0x001a0798
            charge(ctx, 3);
            v0 = 2;
            if (v1 != v0) {
                // 0x001a07d4
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x001a07a4
                charge(ctx, 6);
                lw(v0, gp, -22448);  // 0x7CD540
                lw(a0, v0, 8);
                jal(ctx, 0x1A07ACu, gen::fn_sub_3B54C0_003b54c0);
                if (v0 != 0) {
                    // 0x001a07c8
                    charge(ctx, 1);
                    v0 = addiu(v0, L::kObjVecAKind2);  // kind 2
                } else {
                    // 0x001a07bc
                    charge(ctx, 3);
                    v0 = 0;
                }
                // 0x001a07cc
                charge(ctx, 2);
            }
        } else {
            // 0x001a0768
            charge(ctx, 6);
            lw(v0, gp, -22448);  // 0x7CD540
            lw(a0, v0, 8);
            jal(ctx, 0x1A0770u, gen::fn_sub_3B54C0_003b54c0);
            if (v0 != 0) {
                // 0x001a078c
                charge(ctx, 1);
                v0 = addiu(v0, L::kObjVecA);  // kinds 1 and 3
            } else {
                // 0x001a0780
                charge(ctx, 3);
                v0 = 0;
            }
            // 0x001a0790
            charge(ctx, 2);
        }
    } else {
        // 0x001a072c
        charge(ctx, 6);
        lw(v0, gp, -22448);  // 0x7CD540
        lw(a0, v0, 8);
        jal(ctx, 0x1A0734u, gen::fn_sub_3B54C0_003b54c0);
        if (v0 != 0) {
            // 0x001a0750
            charge(ctx, 1);
            v0 = addiu(v0, L::kObjVecA);  // kinds 1 and 3
        } else {
            // 0x001a0744
            charge(ctx, 3);
            v0 = 0;
        }
        // 0x001a0754
        charge(ctx, 2);
    }
    // 0x001a07d8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001A07F0 sub_1A07F0 -- 232 bytes; frame 0x10: ra sp+0x0
// [proposed name: K_FldObj_GetVecBById] A field object's second vector by id: as sub_1A0700 with +400 (kinds 1 and 3) or +384 (kind 2).
void sub_1A07F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a07f0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a1 = a0;
    v1 = a1 & 0xFFFF;
    v0 = 0xF0000;
    v0 = v0 | 0xFC00;
    v0 = v1 & v0;
    v1 = sra(v0, L::kObjKindShift);  // the id's kind
    v0 = 1;
    if (v1 != v0) {
        // 0x001a084c
        charge(ctx, 3);
        v0 = 3;
        if (v1 != v0) {
            // 0x001a0888
            charge(ctx, 3);
            v0 = 2;
            if (v1 != v0) {
                // 0x001a08c4
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x001a0894
                charge(ctx, 6);
                lw(v0, gp, -22448);  // 0x7CD540
                lw(a0, v0, 8);
                jal(ctx, 0x1A089Cu, gen::fn_sub_3B54C0_003b54c0);
                if (v0 != 0) {
                    // 0x001a08b8
                    charge(ctx, 1);
                    v0 = addiu(v0, L::kObjVecBKind2);  // kind 2
                } else {
                    // 0x001a08ac
                    charge(ctx, 3);
                    v0 = 0;
                }
                // 0x001a08bc
                charge(ctx, 2);
            }
        } else {
            // 0x001a0858
            charge(ctx, 6);
            lw(v0, gp, -22448);  // 0x7CD540
            lw(a0, v0, 8);
            jal(ctx, 0x1A0860u, gen::fn_sub_3B54C0_003b54c0);
            if (v0 != 0) {
                // 0x001a087c
                charge(ctx, 1);
                v0 = addiu(v0, L::kObjVecB);  // kinds 1 and 3
            } else {
                // 0x001a0870
                charge(ctx, 3);
                v0 = 0;
            }
            // 0x001a0880
            charge(ctx, 2);
        }
    } else {
        // 0x001a081c
        charge(ctx, 6);
        lw(v0, gp, -22448);  // 0x7CD540
        lw(a0, v0, 8);
        jal(ctx, 0x1A0824u, gen::fn_sub_3B54C0_003b54c0);
        if (v0 != 0) {
            // 0x001a0840
            charge(ctx, 1);
            v0 = addiu(v0, L::kObjVecB);  // kinds 1 and 3
        } else {
            // 0x001a0834
            charge(ctx, 3);
            v0 = 0;
        }
        // 0x001a0844
        charge(ctx, 2);
    }
    // 0x001a08c8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001A08E0 sub_1A08E0 -- 232 bytes; frame 0x10: ra sp+0x0
// [proposed name: K_FldObj_GetVecCById] A field object's third vector by id: as sub_1A0700 with +416 (kinds 1 and 3) or +400 (kind 2).
void sub_1A08E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a08e0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a1 = a0;
    v1 = a1 & 0xFFFF;
    v0 = 0xF0000;
    v0 = v0 | 0xFC00;
    v0 = v1 & v0;
    v1 = sra(v0, L::kObjKindShift);  // the id's kind
    v0 = 1;
    if (v1 != v0) {
        // 0x001a093c
        charge(ctx, 3);
        v0 = 3;
        if (v1 != v0) {
            // 0x001a0978
            charge(ctx, 3);
            v0 = 2;
            if (v1 != v0) {
                // 0x001a09b4
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x001a0984
                charge(ctx, 6);
                lw(v0, gp, -22448);  // 0x7CD540
                lw(a0, v0, 8);
                jal(ctx, 0x1A098Cu, gen::fn_sub_3B54C0_003b54c0);
                if (v0 != 0) {
                    // 0x001a09a8
                    charge(ctx, 1);
                    v0 = addiu(v0, L::kObjVecCKind2);  // kind 2
                } else {
                    // 0x001a099c
                    charge(ctx, 3);
                    v0 = 0;
                }
                // 0x001a09ac
                charge(ctx, 2);
            }
        } else {
            // 0x001a0948
            charge(ctx, 6);
            lw(v0, gp, -22448);  // 0x7CD540
            lw(a0, v0, 8);
            jal(ctx, 0x1A0950u, gen::fn_sub_3B54C0_003b54c0);
            if (v0 != 0) {
                // 0x001a096c
                charge(ctx, 1);
                v0 = addiu(v0, L::kObjVecC);  // kinds 1 and 3
            } else {
                // 0x001a0960
                charge(ctx, 3);
                v0 = 0;
            }
            // 0x001a0970
            charge(ctx, 2);
        }
    } else {
        // 0x001a090c
        charge(ctx, 6);
        lw(v0, gp, -22448);  // 0x7CD540
        lw(a0, v0, 8);
        jal(ctx, 0x1A0914u, gen::fn_sub_3B54C0_003b54c0);
        if (v0 != 0) {
            // 0x001a0930
            charge(ctx, 1);
            v0 = addiu(v0, L::kObjVecC);  // kinds 1 and 3
        } else {
            // 0x001a0924
            charge(ctx, 3);
            v0 = 0;
        }
        // 0x001a0934
        charge(ctx, 2);
    }
    // 0x001a09b8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001A1150 sub_1A1150 -- 56 bytes; frame 0x10: ra sp+0x0
// [proposed name: K_FldCamera_GetWord264] The field camera record (sub_3B5D50(20)) +264 word, or 0 without a camera.
void sub_1A1150(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a1150
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 20;
    jal(ctx, 0x1A115Cu, gen::fn_sub_3B5D50_003b5d50);
    v1 = 0;
    if (v0 != 0) {
        // 0x001a1170
        charge(ctx, 1);
        lw(v1, v0, L::kCamWord264);
    }
    // 0x001a1174 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = v1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001A1190 sub_1A1190 -- 52 bytes; frame 0x10: ra sp+0x0
// The field camera record (sub_3B5D50(20)) +260 float (in $f0), or 0.0 without a camera.
void sub_1A1190(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x001a1190
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 20;
    jal(ctx, 0x1A119Cu, gen::fn_sub_3B5D50_003b5d50);
    mtc1(zero, f0);
    if (v0 != 0) {
        // 0x001a11b0
        charge(ctx, 1);
        lwc1(f0, v0, L::kCamFloat260);
    }
    // 0x001a11b4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001A1210 sub_1A1210 -- 404 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Aim a field camera (a0+4 -> camera block): eye = *a1 (+64..+72), direction = *a2 - eye normalised (+48..+56), the
// up vector a3 (or the default (0x678AB8)) crossed in to build the basis (sub_4C69F0 / sub_4C2F10 / sub_4CB270).
void sub_1A1210(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4};
    // 0x001a1210
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = addiu(sp, 0x40);
    v0 = 0x680000;
    ld(v1, v0, -30024);  // 0x678AB8
    v0 = 0x680000;
    lwc1(f0, v0, -30016);  // 0x678AC0
    sd(v1, sp, 0x40);
    swc1(f0, sp, 0x48);
    if (a3 != 0) {
        // 0x001a1250
        charge(ctx, 1);
        s0 = a3;
    } else {
        // 0x001a1248
        charge(ctx, 2);
    }
    // 0x001a1254
    charge(ctx, 84);
    lw(s2, a0, 4);
    s1 = addiu(s2, 16);
    lwc1(f2, a1, 0);
    lwc1(f1, a1, 4);
    lwc1(f0, a1, 8);
    swc1(f2, s2, 64);
    swc1(f1, s2, 68);
    swc1(f0, s2, 72);
    lwc1(f1, a2, 0);
    lwc1(f0, s2, 64);
    sub_s(f0, f1, f0);
    swc1(f0, s2, 48);
    lwc1(f1, a2, 4);
    lwc1(f0, s2, 68);
    sub_s(f0, f1, f0);
    swc1(f0, s2, 52);
    lwc1(f1, a2, 8);
    lwc1(f0, s2, 72);
    sub_s(f0, f1, f0);
    swc1(f0, s2, 56);
    a0 = addiu(s1, 32);
    a1 = a0;
    jal(ctx, 0x1A12ACu, gen::fn_sub_4C69F0_004c69f0);
    lwc1(f1, s1, 40);
    lwc1(f4, s0, 4);
    lwc1(f0, s1, 36);
    lwc1(f3, s0, 8);
    mula_s(f0, f3);
    msub_s(f0, f1, f4);
    swc1(f0, s1, 0);
    lwc1(f1, s1, 32);
    lwc1(f0, s1, 40);
    lwc1(f2, s0, 0);
    mula_s(f0, f2);
    msub_s(f0, f1, f3);
    swc1(f0, s1, 4);
    lwc1(f1, s1, 36);
    lwc1(f0, s1, 32);
    mula_s(f0, f4);
    msub_s(f0, f1, f2);
    swc1(f0, s1, 8);
    a0 = s1;
    a1 = s1;
    jal(ctx, 0x1A1304u, gen::fn_sub_4C69F0_004c69f0);
    lwc1(f3, s1, 40);
    lwc1(f2, s1, 4);
    lwc1(f1, s1, 36);
    lwc1(f0, s1, 8);
    mula_s(f1, f0);
    msub_s(f0, f3, f2);
    swc1(f0, s1, 16);
    lwc1(f3, s1, 32);
    lwc1(f2, s1, 8);
    lwc1(f1, s1, 40);
    lwc1(f0, s1, 0);
    mula_s(f1, f0);
    msub_s(f0, f3, f2);
    swc1(f0, s1, 20);
    lwc1(f3, s1, 36);
    lwc1(f2, s1, 0);
    lwc1(f1, s1, 32);
    lwc1(f0, s1, 4);
    mula_s(f1, f0);
    msub_s(f0, f3, f2);
    swc1(f0, s1, 24);
    a0 = addiu(s1, 16);
    a1 = a0;
    jal(ctx, 0x1A1368u, gen::fn_sub_4C69F0_004c69f0);
    a0 = s1;
    jal(ctx, 0x1A1374u, gen::fn_sub_4C2F10_004c2f10);
    a0 = s2;
    jal(ctx, 0x1A1380u, gen::fn_sub_4CB270_004cb270);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x001A14C0 sub_1A14C0 -- 124 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Free a +64-linked chain of render objects: for each node detach it (sub_4D11F0 / sub_4D1170 / sub_4D0F00) and hand
// it to the free hook *(0x96017C).
void sub_1A14C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a14c0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    for (;;) {
        // 0x001a151c
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001a14dc
        charge(ctx, 16);
        lw(s1, s0, 64);
        jal(ctx, 0x1A14E0u, gen::fn_sub_4D11F0_004d11f0);
        a0 = v0;
        a1 = s0;
        jal(ctx, 0x1A14F0u, gen::fn_sub_4D1170_004d1170);
        a0 = v0;
        jal(ctx, 0x1A14FCu, gen::fn_sub_4D0F00_004d0f00);
        a0 = s0;
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        jalr(ctx, 0x1A1510u, v0.u());
        s0 = s1;
    }
    // 0x001a1524
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001A4600 sub_1A4600 -- 84 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Two atanf calls on the field camera globals (0x7CAEA8); returns 0x40000000 in $v0.
void sub_1A4600(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x001a4600
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = addiu(a0, 104);
    lwc1(f12, a0, 104);
    jal(ctx, 0x1A4614u, gen::fn_atanf_0052e408);
    lwc1(f12, s0, 4);
    jal(ctx, 0x1A4620u, gen::fn_atanf_0052e408);
    v0 = 0x40000000;
    mtc1(v0, f1);
    mul_s(f1, f1, f0);
    lwc1(f0, gp, -32328);  // 0x7CAEA8
    mul_s(f0, f0, f1);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001A4860 sub_1A4860 -- 128 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Create the "field camera cylinder" task (priority 2109) with a 24-byte work block from the alloc hook *(0x960184);
// returns the task or 0.
void sub_1A4860(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a4860
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 1;
    a1 = 24;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x1A4884u, v0.u());
    if (v0 != 0) {
        // 0x001a48a0
        charge(ctx, 11);
        a0 = s0;
        a1 = 2109;
        a2 = 0x680000;
        a2 = addiu(a2, -29904);  // "field camera cylinder"
        a3 = 0x1A0000;
        a3 = addiu(a3, 18400);  // &sub_1A47E0
        t0 = 0x1A0000;
        t0 = addiu(t0, 18480);  // &sub_1A4830
        t1 = v0;
        jal(ctx, 0x1A48C4u, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
    } else {
        // 0x001a4894
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001a48cc (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001A5EA0 sub_1A5EA0 -- 144 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Create a "delay model free" task (priority 10) for model a0 (work +4), 8-byte work from *(0x960184); returns the
// task or 0.
void sub_1A5EA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a5ea0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    a0 = 1;
    a1 = 8;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x1A5EC8u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x001a5ee8
        charge(ctx, 12);
        a0 = 0;
        a1 = 10;
        a2 = 0x680000;
        a2 = addiu(a2, -29824);  // "delay model free"
        a3 = 0x1A0000;
        a3 = addiu(a3, 24032);  // &sub_1A5DE0
        t0 = 0x1A0000;
        t0 = addiu(t0, 24176);  // &sub_1A5E70
        t1 = s0;
        jal(ctx, 0x1A5F0Cu, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
        sw(s1, s0, 4);
    } else {
        // 0x001a5edc
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001a5f18 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001A6400 sub_1A6400 -- 228 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Find a named frame in a model's frame list: walks sub_48EE80(a0) entries, the first whose type name equals a1 and
// whose kind (sub_48EF20) is 1 gives sub_48EF40(entry, 0); else 0.
void sub_1A6400(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a6400
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s4 = 0;
    s0 = 0;
    for (;;) {
        // 0x001a64a4
        charge(ctx, 6);
        a0 = s2;
        jal(ctx, 0x1A64A8u, gen::fn_sub_48EE80_0048ee80);
        v0 = slt(s0, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001a6434
        charge(ctx, 14);
        a0 = s2;
        a1 = s0;
        jal(ctx, 0x1A643Cu, gen::fn_sub_48EED0_0048eed0);
        s3 = v0;
        a0 = s3;
        jal(ctx, 0x1A644Cu, gen::fn_name__C9type_info_0_0048ef10);
        a0 = v0;
        a1 = s1;
        jal(ctx, 0x1A645Cu, gen::fn_strcmp_00524128);
        if (v0 == 0) {
            // 0x001a646c
            charge(ctx, 6);
            a0 = s3;
            jal(ctx, 0x1A6470u, gen::fn_sub_48EF20_0048ef20);
            v1 = 1;
            if (v0 != v1) {
                goto L_001a64a0;
            }
            goto L_001a6484_3;
        }
    L_001a64a0:
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x001a64bc (the shared epilogue, written out on this path)
    charge(ctx, 10);
    v0 = s4;
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
L_001a6484_3:
    charge(ctx, 7);
    a0 = s3;
    a1 = 0;
    jal(ctx, 0x1A648Cu, gen::fn_sub_48EF40_0048ef40);
    s4 = v0;
    // 0x001a64bc (the shared epilogue, written out on this path)
    charge(ctx, 10);
    v0 = s4;
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x001A6860 sub_1A6860 -- 312 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Frame-list callback: when entry a1's name matches and one of its ids equals a1+68, stores the owner a0 at a1+64
// and stops the walk (returns 0); else returns a0.
void sub_1A6860(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a6860
    enter(ctx, 13);  // entry check point + this block's cycles
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
    s2 = 0;
    for (;;) {
        // 0x001a693c
        charge(ctx, 6);
        a0 = s4;
        jal(ctx, 0x1A6940u, gen::fn_sub_48EDE0_0048ede0);
        v0 = slt(s2, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001a6894
        charge(ctx, 14);
        a0 = s4;
        a1 = s2;
        jal(ctx, 0x1A689Cu, gen::fn_sub_48EE30_0048ee30);
        s0 = v0;
        a0 = s0;
        jal(ctx, 0x1A68ACu, gen::fn_name__C9type_info_0_0048ef10);
        a0 = v0;
        a1 = s3;
        jal(ctx, 0x1A68BCu, gen::fn_strcmp_00524128);
        if (v0 == 0) {
            // 0x001a68cc
            charge(ctx, 3);
            s1 = 0;
            for (;;) {
                // 0x001a6920
                charge(ctx, 6);
                a0 = s0;
                jal(ctx, 0x1A6924u, gen::fn_sub_48EF30_0048ef30);
                v0 = slt(s1, v0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001a68d8
                charge(ctx, 6);
                a0 = s0;
                jal(ctx, 0x1A68DCu, gen::fn_sub_48EF20_0048ef20);
                v1 = 1;
                if (v0 == v1) {
                    // 0x001a68f0
                    charge(ctx, 7);
                    lw(s5, s3, 68);
                    a0 = s0;
                    a1 = s1;
                    jal(ctx, 0x1A68FCu, gen::fn_sub_48EF40_0048ef40);
                    if (s5 != v0) {
                        goto L_001a691c;
                    }
                    goto L_001a690c_5;
                }
            L_001a691c:
                charge(ctx, 1);
                s1 = addiu(s1, 1);
            }
        }
        // 0x001a6938
        charge(ctx, 1);
        s2 = addiu(s2, 1);
    }
    // 0x001a6954
    charge(ctx, 7);
    a0 = s4;
    a1 = 0x1A0000;
    a1 = addiu(a1, 26720);  // &sub_1A6860
    a2 = s3;
    jal(ctx, 0x1A6964u, gen::fn_sub_4CB6E0_004cb6e0);
    v0 = s4;
    // 0x001a6970 (the shared epilogue, written out on this path)
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
L_001a690c_5:
    charge(ctx, 4);
    sw(s4, s3, 64);
    v0 = 0;
    // 0x001a6970 (the shared epilogue, written out on this path)
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

// 0x001A6C00 sub_1A6C00 -- 276 bytes; frame 0xA0: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Count the kind-1 entries named like the model's root (a0+4) and walk its children with sub_1A6AF0 (sub_4CB6E0);
// the name is copied to a stack buffer first.
void sub_1A6C00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a6c00
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s1, a0, 4);
    a0 = addiu(sp, 0x50);
    jal(ctx, 0x1A6C20u, gen::fn_strcpy_00524270);
    sw(zero, sp, 0x90);
    s3 = 0;
    for (;;) {
        // 0x001a6cc0
        charge(ctx, 6);
        a0 = s1;
        jal(ctx, 0x1A6CC4u, gen::fn_sub_48EDE0_0048ede0);
        v0 = slt(s3, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001a6c38
        charge(ctx, 14);
        a0 = s1;
        a1 = s3;
        jal(ctx, 0x1A6C40u, gen::fn_sub_48EE30_0048ee30);
        s0 = v0;
        a0 = s0;
        jal(ctx, 0x1A6C50u, gen::fn_name__C9type_info_0_0048ef10);
        a0 = v0;
        a1 = addiu(sp, 0x50);
        jal(ctx, 0x1A6C60u, gen::fn_strcmp_00524128);
        if (v0 == 0) {
            // 0x001a6c70
            charge(ctx, 3);
            s2 = 0;
            for (;;) {
                // 0x001a6ca4
                charge(ctx, 6);
                a0 = s0;
                jal(ctx, 0x1A6CA8u, gen::fn_sub_48EF30_0048ef30);
                v0 = slt(s2, v0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001a6c7c
                charge(ctx, 6);
                a0 = s0;
                jal(ctx, 0x1A6C80u, gen::fn_sub_48EF20_0048ef20);
                v1 = 1;
                if (v0 == v1) {
                    // 0x001a6c94
                    charge(ctx, 3);
                    lw(v0, sp, 0x90);
                    v0 = addiu(v0, 1);
                    sw(v0, sp, 0x90);
                }
                // 0x001a6ca0
                charge(ctx, 1);
                s2 = addiu(s2, 1);
            }
        }
        // 0x001a6cbc
        charge(ctx, 1);
        s3 = addiu(s3, 1);
    }
    // 0x001a6cd8
    charge(ctx, 15);
    a0 = s1;
    a1 = 0x1A0000;
    a1 = addiu(a1, 27376);  // &sub_1A6AF0
    a2 = addiu(sp, 0x50);
    jal(ctx, 0x1A6CE8u, gen::fn_sub_4CB6E0_004cb6e0);
    lw(v0, sp, 0x90);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// 0x001A7170 sub_1A7170 -- 44 bytes; frame 0x10: ra sp+0x0
// Walk a clump's atomics (sub_4916D0) with callback sub_1A70A0 and data a1.
void sub_1A7170(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a7170
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = a1;
    a1 = 0x1A0000;
    a1 = addiu(a1, 28832);  // &sub_1A70A0
    jal(ctx, 0x1A7184u, gen::fn_sub_4916D0_004916d0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001A7570 sub_1A7570 -- 240 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Collect a clump's material groups into a 44-byte record (alloc hook *(0x960184)) through sub_4916D0(sub_1A74E0);
// when nothing was collected, frees it (sub_1A7710) and returns 0.
void sub_1A7570(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a7570
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    a0 = 1;
    a1 = 44;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x1A7598u, v0.u());
    s0 = v0;
    a0 = s1;
    a1 = 0x1A0000;
    a1 = addiu(a1, 29920);  // &sub_1A74E0
    a2 = s0;
    jal(ctx, 0x1A75B4u, gen::fn_sub_4916D0_004916d0);
    lw(v0, s0, 4);
    if (v0 == 0) {
        // 0x001a75c8
        charge(ctx, 3);
        lw(v0, s0, 0);
        if (v0 != 0) {
            // 0x001a75d4
            charge(ctx, 3);
            lw(v0, s0, 16);
            if (v0 == 0) {
                // 0x001a75e0
                charge(ctx, 3);
                lw(v0, s0, 12);
                if (v0 == 0) {
                    // 0x001a75ec
                    charge(ctx, 3);
                    lw(v0, s0, 20);
                    if (v0 == 0) {
                        // 0x001a75f8
                        charge(ctx, 3);
                        lw(v0, s0, 36);
                        if (v0 == 0) {
                            // 0x001a7604
                            charge(ctx, 3);
                            lw(v0, s0, 40);
                            if (v0 == 0) {
                                // 0x001a7610
                                charge(ctx, 3);
                                lw(v0, s0, 24);
                                if (v0 == 0) {
                                    // 0x001a761c
                                    charge(ctx, 3);
                                    lw(v0, s0, 28);
                                    if (v0 == 0) {
                                        // 0x001a7628
                                        charge(ctx, 3);
                                        lw(v0, s0, 32);
                                        if (v0 == 0) {
                                            goto L_001a7634;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            // 0x001a7644 (the shared epilogue, written out on this path)
            charge(ctx, 7);
            v0 = s0;
            ld(ra, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x30);
            return;
        }
    L_001a7634:
        charge(ctx, 4);
        a0 = s0;
        jal(ctx, 0x1A7638u, gen::fn_sub_1A7710_001a7710);
        s0 = 0;
    }
    // 0x001a7644 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = s0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001A7710 sub_1A7710 -- 504 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Free sub_1A7570's record a0: each of its lists (+8, +24, +28, ...) popped node by node (+40 next) into the
// free hook *(0x96017C), then the record itself.
void sub_1A7710(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001a7710
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    if (s0 != 0) {
        for (;;) {
            // 0x001a7750
            charge(ctx, 3);
            lw(v0, s0, 8);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001a7734
            charge(ctx, 7);
            lw(a0, s0, 8);
            lw(s1, a0, 40);
            v0 = 0x960000;
            lw(v0, v0, 380);  // 0x96017C
            jalr(ctx, 0x1A7744u, v0.u());
            sw(s1, s0, 8);
        }
        // 0x001a775c
        charge(ctx, 2);
        for (;;) {
            // 0x001a7780
            charge(ctx, 3);
            lw(v0, s0, 24);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001a7764
            charge(ctx, 7);
            lw(a0, s0, 24);
            lw(s1, a0, 40);
            v0 = 0x960000;
            lw(v0, v0, 380);  // 0x96017C
            jalr(ctx, 0x1A7774u, v0.u());
            sw(s1, s0, 24);
        }
        // 0x001a778c
        charge(ctx, 2);
        for (;;) {
            // 0x001a77b0
            charge(ctx, 3);
            lw(v0, s0, 28);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001a7794
            charge(ctx, 7);
            lw(a0, s0, 28);
            lw(s1, a0, 40);
            v0 = 0x960000;
            lw(v0, v0, 380);  // 0x96017C
            jalr(ctx, 0x1A77A4u, v0.u());
            sw(s1, s0, 28);
        }
        // 0x001a77bc
        charge(ctx, 2);
        for (;;) {
            // 0x001a77e0
            charge(ctx, 3);
            lw(v0, s0, 12);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001a77c4
            charge(ctx, 7);
            lw(a0, s0, 12);
            lw(s1, a0, 40);
            v0 = 0x960000;
            lw(v0, v0, 380);  // 0x96017C
            jalr(ctx, 0x1A77D4u, v0.u());
            sw(s1, s0, 12);
        }
        // 0x001a77ec
        charge(ctx, 2);
        for (;;) {
            // 0x001a7810
            charge(ctx, 3);
            lw(v0, s0, 16);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001a77f4
            charge(ctx, 7);
            lw(a0, s0, 16);
            lw(s1, a0, 40);
            v0 = 0x960000;
            lw(v0, v0, 380);  // 0x96017C
            jalr(ctx, 0x1A7804u, v0.u());
            sw(s1, s0, 16);
        }
        // 0x001a781c
        charge(ctx, 2);
        for (;;) {
            // 0x001a7840
            charge(ctx, 3);
            lw(v0, s0, 32);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001a7824
            charge(ctx, 7);
            lw(a0, s0, 32);
            lw(s1, a0, 40);
            v0 = 0x960000;
            lw(v0, v0, 380);  // 0x96017C
            jalr(ctx, 0x1A7834u, v0.u());
            sw(s1, s0, 32);
        }
        // 0x001a784c
        charge(ctx, 2);
        for (;;) {
            // 0x001a7870
            charge(ctx, 3);
            lw(v0, s0, 20);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001a7854
            charge(ctx, 7);
            lw(a0, s0, 20);
            lw(s1, a0, 40);
            v0 = 0x960000;
            lw(v0, v0, 380);  // 0x96017C
            jalr(ctx, 0x1A7864u, v0.u());
            sw(s1, s0, 20);
        }
        // 0x001a787c
        charge(ctx, 2);
        for (;;) {
            // 0x001a78a0
            charge(ctx, 3);
            lw(v0, s0, 36);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001a7884
            charge(ctx, 7);
            lw(a0, s0, 36);
            lw(s1, a0, 40);
            v0 = 0x960000;
            lw(v0, v0, 380);  // 0x96017C
            jalr(ctx, 0x1A7894u, v0.u());
            sw(s1, s0, 36);
        }
        // 0x001a78ac
        charge(ctx, 2);
        for (;;) {
            // 0x001a78d0
            charge(ctx, 3);
            lw(v0, s0, 40);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001a78b4
            charge(ctx, 7);
            lw(a0, s0, 40);
            lw(s1, a0, 40);
            v0 = 0x960000;
            lw(v0, v0, 380);  // 0x96017C
            jalr(ctx, 0x1A78C4u, v0.u());
            sw(s1, s0, 40);
        }
        // 0x001a78dc
        charge(ctx, 5);
        a0 = s0;
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        jalr(ctx, 0x1A78E8u, v0.u());
    } else {
        // 0x001a772c
        charge(ctx, 2);
    }
    // 0x001a78f0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001AD9E0 sub_1AD9E0 -- 564 bytes; frame 0x80: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Battle-camera (kosaka) helper on the owner a0 (+60 record): when +16 is set, the tracked model's (sub_318B60)
// position feeds the vector maths sub_4C2CC0 / sub_4C2D20 / sub_4C2F10 / sub_318A90 with a1.
void sub_1AD9E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x001ad9e0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    lw(s0, a0, 60);
    a0 = addiu(sp, 0x60);
    v1 = 12;
    if (a0 != 0) {
        for (;;) {
            // 0x001ada08
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
    // 0x001ada24
    charge(ctx, 3);
    lw(a0, s0, 16);
    if (a0 != 0) {
        // 0x001ada30
        charge(ctx, 79);
        jal(ctx, 0x1ADA30u, gen::fn_sub_318B60_00318b60);
        lwc1(f2, v0, 48);
        lwc1(f1, v0, 52);
        lwc1(f0, v0, 56);
        swc1(f2, sp, 0x70);
        swc1(f1, sp, 0x74);
        swc1(f0, sp, 0x78);
        lw(a0, s0, 16);
        jal(ctx, 0x1ADA54u, gen::fn_sub_318B60_00318b60);
        lwc1(f2, sp, 0x60);
        lwc1(f1, sp, 0x64);
        lwc1(f0, sp, 0x68);
        swc1(f2, v0, 48);
        swc1(f1, v0, 52);
        swc1(f0, v0, 56);
        a0 = addiu(sp, 0x50);
        jal(ctx, 0x1ADA78u, gen::fn_sub_4C2CC0_004c2cc0);
        lw(a0, s0, 16);
        jal(ctx, 0x1ADA84u, gen::fn_sub_318B60_00318b60);
        a0 = v0;
        a1 = addiu(sp, 0x50);
        jal(ctx, 0x1ADA94u, gen::fn_sub_4C2D20_004c2d20);
        lw(a0, s0, 16);
        jal(ctx, 0x1ADAA0u, gen::fn_sub_318B60_00318b60);
        a0 = v0;
        jal(ctx, 0x1ADAACu, gen::fn_sub_4C2F10_004c2f10);
        lw(a0, s0, 16);
        jal(ctx, 0x1ADAB8u, gen::fn_sub_318B60_00318b60);
        lwc1(f2, s1, 0);
        lwc1(f1, s1, 4);
        lwc1(f0, s1, 8);
        swc1(f2, v0, 0);
        swc1(f1, v0, 4);
        swc1(f0, v0, 8);
        lw(a0, s0, 16);
        jal(ctx, 0x1ADADCu, gen::fn_sub_318B60_00318b60);
        lwc1(f2, s1, 16);
        lwc1(f1, s1, 20);
        lwc1(f0, s1, 24);
        swc1(f2, v0, 16);
        swc1(f1, v0, 20);
        swc1(f0, v0, 24);
        lw(a0, s0, 16);
        jal(ctx, 0x1ADB00u, gen::fn_sub_318B60_00318b60);
        lwc1(f2, s1, 32);
        lwc1(f1, s1, 36);
        lwc1(f0, s1, 40);
        swc1(f2, v0, 32);
        swc1(f1, v0, 36);
        swc1(f0, v0, 40);
        a0 = addiu(sp, 0x40);
        jal(ctx, 0x1ADB24u, gen::fn_sub_4C2CC0_004c2cc0);
        lw(a0, s0, 16);
        jal(ctx, 0x1ADB30u, gen::fn_sub_318B60_00318b60);
        a0 = v0;
        a1 = addiu(sp, 0x40);
        jal(ctx, 0x1ADB40u, gen::fn_sub_4C2D20_004c2d20);
        lw(a0, s0, 16);
        jal(ctx, 0x1ADB4Cu, gen::fn_sub_318B60_00318b60);
        a0 = v0;
        jal(ctx, 0x1ADB58u, gen::fn_sub_4C2F10_004c2f10);
        lw(v0, s0, 12);
        if (v0 != 0) {
            // 0x001adb6c
            charge(ctx, 11);
            lw(v1, v0, 400);
            v0 = sll(v1, 1);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            v0 = 0x680000;
            v0 = addiu(v0, 14208);  // &0x683780
            a1 = addu(v0, v1);
            lw(a0, s0, 16);
            a2 = 2;
            jal(ctx, 0x1ADB90u, gen::fn_sub_318A90_00318a90);
        }
        // 0x001adb98
        charge(ctx, 25);
        lw(a0, s0, 16);
        jal(ctx, 0x1ADB9Cu, gen::fn_sub_318B60_00318b60);
        lwc1(f2, sp, 0x70);
        lwc1(f1, sp, 0x74);
        lwc1(f0, sp, 0x78);
        swc1(f2, v0, 48);
        swc1(f1, v0, 52);
        swc1(f0, v0, 56);
        a0 = addiu(sp, 0x30);
        jal(ctx, 0x1ADBC0u, gen::fn_sub_4C2CC0_004c2cc0);
        lw(a0, s0, 16);
        jal(ctx, 0x1ADBCCu, gen::fn_sub_318B60_00318b60);
        a0 = v0;
        a1 = addiu(sp, 0x30);
        jal(ctx, 0x1ADBDCu, gen::fn_sub_4C2D20_004c2d20);
        lw(a0, s0, 16);
        jal(ctx, 0x1ADBE8u, gen::fn_sub_318B60_00318b60);
        a0 = v0;
        jal(ctx, 0x1ADBF4u, gen::fn_sub_4C2F10_004c2f10);
    }
    // 0x001adbfc (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x001CD9A0 sub_1CD9A0 -- 3800 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Field event selection for id a0 (a jump over the ids; 13 checks floor 14 / block 5): uses the three active
// ids sub_16DD60(0..2), the time (datGetTime), the calendar month / day and the flags; writes the result to
// 0x871EA0 / 0x871EA2 / 0x871EA4.
void sub_1CD9A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001cd9a0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = 0;
    s2 = 0;
    for (;;) {
        // 0x001cd9fc
        charge(ctx, 3);
        v0 = slti(s2, 3);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001cd9d0
        charge(ctx, 7);
        a0 = s2;
        jal(ctx, 0x1CD9D4u, gen::fn_sub_16DD60_0016dd60);
        v0 = dsll32(v0, 16);
        v0 = dsra32(v0, 16);
        if (s1 == v0) {
            goto L_001cd9ec_2;
        }
        // 0x001cd9f8
        charge(ctx, 1);
        s2 = addiu(s2, 1);
    }
L_001cda08:
    charge(ctx, 3);
    v0 = 13;
    if (s1 == v0) {
        // 0x001ce61c
        charge(ctx, 5);
        lw(a0, gp, -22448);  // 0x7CD540
        lw(v1, a0, 0);
        v0 = 14;
        if (v1 == v0) {
            // 0x001ce630
            charge(ctx, 4);
            lw(v1, a0, 4);
            v0 = 5;
            if (v1 != v0) {
                goto L_001ce650;
            }
            // 0x001ce640
            charge(ctx, 4);
            a0 = 9;
            a1 = 3328;
            goto L_001ce658;
        }
    L_001ce650:
        charge(ctx, 2);
        a0 = 1;
        a1 = s1 & 0xFFFF;
    L_001ce658:
        charge(ctx, 8);
        s4 = sll(s0, 3);
        v0 = 0x870000;
        v0 = addiu(v0, 7840);  // &0x871EA0
        s3 = addu(v0, s4);
        s2 = a0 & 0xFFFF;
        lhu(v0, s3, 0);
        if (s2 == v0) {
            // 0x001ce678
            charge(ctx, 7);
            v1 = a1 & 0xFFFF;
            v0 = 0x870000;
            v0 = addiu(v0, 7842);  // &0x871EA2
            v0 = addu(v0, s4);
            lhu(v0, v0, 0);
            if (v1 != v0) {
                goto L_001ce6ac;
            }
            // 0x001ce694
            charge(ctx, 6);
            v0 = 0x870000;
            v0 = addiu(v0, 7844);  // &0x871EA4
            v0 = addu(v0, s4);
            lw(s1, v0, 0);
            goto L_001ce6b0;
        }
    L_001ce6ac:
        charge(ctx, 1);
        s1 = 0;
    L_001ce6b0:
        charge(ctx, 2);
        if (s1 != 0) {
            // 0x001ce748
            charge(ctx, 5);
            a0 = s1;
            jal(ctx, 0x1CE74Cu, gen::fn_sub_319190_00319190);
        } else {
            // 0x001ce6b8
            charge(ctx, 7);
            a2 = 0;
            jal(ctx, 0x1CE6BCu, gen::fn_sub_316E00_00316e00);
            s1 = v0;
            v0 = 1;
            if (s2 == v0) {
                // 0x001ce6d4
                charge(ctx, 3);
                a0 = s1;
                jal(ctx, 0x1CE6D8u, gen::fn_sub_31C1D0_0031c1d0);
            }
            // 0x001ce6e0
            charge(ctx, 6);
            v1 = 0x870000;
            v1 = addiu(v1, 7844);  // &0x871EA4
            v0 = addu(v1, s4);
            lw(a0, v0, 0);
            if (a0 != 0) {
                // 0x001ce6f8
                charge(ctx, 5);
                v0 = sll(s0, 3);
                s2 = addu(v1, v0);
                jal(ctx, 0x1CE700u, gen::fn_sub_3174E0_003174e0);
                sw(zero, s2, 0);
            }
            // 0x001ce70c
            charge(ctx, 15);
            a0 = sll(s0, 3);
            v0 = 0x870000;
            v0 = addiu(v0, 7844);  // &0x871EA4
            v1 = addu(v0, a0);
            sw(s1, v1, 0);
            lhu(v0, s1, 212);
            sh(v0, s3, 0);
            lw(v0, v1, 0);
            lhu(v1, v0, 214);
            v0 = 0x870000;
            v0 = addiu(v0, 7842);  // &0x871EA2
            v0 = addu(v0, a0);
            sh(v1, v0, 0);
        }
    } else {
        // 0x001cda14
        charge(ctx, 3);
        v0 = 10;
        if (s1 == v0) {
            // 0x001ce4dc
            charge(ctx, 5);
            lw(a0, gp, -22448);  // 0x7CD540
            lw(v1, a0, 0);
            v0 = 14;
            if (v1 == v0) {
                // 0x001ce4f0
                charge(ctx, 4);
                lw(v1, a0, 4);
                v0 = 5;
                if (v1 != v0) {
                    goto L_001ce510;
                }
                // 0x001ce500
                charge(ctx, 4);
                a0 = 9;
                a1 = 3328;
                goto L_001ce518;
            }
        L_001ce510:
            charge(ctx, 2);
            a0 = 1;
            a1 = s1 & 0xFFFF;
        L_001ce518:
            charge(ctx, 8);
            s4 = sll(s0, 3);
            v0 = 0x870000;
            v0 = addiu(v0, 7840);  // &0x871EA0
            s3 = addu(v0, s4);
            s2 = a0 & 0xFFFF;
            lhu(v0, s3, 0);
            if (s2 == v0) {
                // 0x001ce538
                charge(ctx, 7);
                v1 = a1 & 0xFFFF;
                v0 = 0x870000;
                v0 = addiu(v0, 7842);  // &0x871EA2
                v0 = addu(v0, s4);
                lhu(v0, v0, 0);
                if (v1 != v0) {
                    goto L_001ce56c;
                }
                // 0x001ce554
                charge(ctx, 6);
                v0 = 0x870000;
                v0 = addiu(v0, 7844);  // &0x871EA4
                v0 = addu(v0, s4);
                lw(s1, v0, 0);
                goto L_001ce570;
            }
        L_001ce56c:
            charge(ctx, 1);
            s1 = 0;
        L_001ce570:
            charge(ctx, 2);
            if (s1 != 0) {
                // 0x001ce608
                charge(ctx, 5);
                a0 = s1;
                jal(ctx, 0x1CE60Cu, gen::fn_sub_319190_00319190);
            } else {
                // 0x001ce578
                charge(ctx, 7);
                a2 = 0;
                jal(ctx, 0x1CE57Cu, gen::fn_sub_316E00_00316e00);
                s1 = v0;
                v0 = 1;
                if (s2 == v0) {
                    // 0x001ce594
                    charge(ctx, 3);
                    a0 = s1;
                    jal(ctx, 0x1CE598u, gen::fn_sub_31C1D0_0031c1d0);
                }
                // 0x001ce5a0
                charge(ctx, 6);
                v1 = 0x870000;
                v1 = addiu(v1, 7844);  // &0x871EA4
                v0 = addu(v1, s4);
                lw(a0, v0, 0);
                if (a0 != 0) {
                    // 0x001ce5b8
                    charge(ctx, 5);
                    v0 = sll(s0, 3);
                    s2 = addu(v1, v0);
                    jal(ctx, 0x1CE5C0u, gen::fn_sub_3174E0_003174e0);
                    sw(zero, s2, 0);
                }
                // 0x001ce5cc
                charge(ctx, 15);
                a0 = sll(s0, 3);
                v0 = 0x870000;
                v0 = addiu(v0, 7844);  // &0x871EA4
                v1 = addu(v0, a0);
                sw(s1, v1, 0);
                lhu(v0, s1, 212);
                sh(v0, s3, 0);
                lw(v0, v1, 0);
                lhu(v1, v0, 214);
                v0 = 0x870000;
                v0 = addiu(v0, 7842);  // &0x871EA2
                v0 = addu(v0, a0);
                sh(v1, v0, 0);
            }
        } else {
            // 0x001cda20
            charge(ctx, 3);
            a0 = 7;
            if (s1 == a0) {
                // 0x001ce380
                charge(ctx, 5);
                lw(v1, gp, -22448);  // 0x7CD540
                lw(a0, v1, 0);
                v0 = 14;
                if (a0 == v0) {
                    // 0x001ce394
                    charge(ctx, 4);
                    lw(v1, v1, 4);
                    v0 = 5;
                    if (v1 != v0) {
                        goto L_001ce3b4;
                    }
                    // 0x001ce3a4
                    charge(ctx, 4);
                    a0 = 9;
                    a1 = 1792;
                    goto L_001ce3d8;
                }
            L_001ce3b4:
                charge(ctx, 3);
                v0 = 33;
                if (a0 != v0) {
                    // 0x001ce3d0
                    charge(ctx, 2);
                    a0 = 1;
                    a1 = s1 & 0xFFFF;
                } else {
                    // 0x001ce3c0
                    charge(ctx, 4);
                    a0 = 9;
                    a1 = 1793;
                }
            L_001ce3d8:
                charge(ctx, 8);
                s4 = sll(s0, 3);
                v0 = 0x870000;
                v0 = addiu(v0, 7840);  // &0x871EA0
                s3 = addu(v0, s4);
                s2 = a0 & 0xFFFF;
                lhu(v0, s3, 0);
                if (s2 == v0) {
                    // 0x001ce3f8
                    charge(ctx, 7);
                    v1 = a1 & 0xFFFF;
                    v0 = 0x870000;
                    v0 = addiu(v0, 7842);  // &0x871EA2
                    v0 = addu(v0, s4);
                    lhu(v0, v0, 0);
                    if (v1 != v0) {
                        goto L_001ce42c;
                    }
                    // 0x001ce414
                    charge(ctx, 6);
                    v0 = 0x870000;
                    v0 = addiu(v0, 7844);  // &0x871EA4
                    v0 = addu(v0, s4);
                    lw(s1, v0, 0);
                    goto L_001ce430;
                }
            L_001ce42c:
                charge(ctx, 1);
                s1 = 0;
            L_001ce430:
                charge(ctx, 2);
                if (s1 != 0) {
                    // 0x001ce4c8
                    charge(ctx, 5);
                    a0 = s1;
                    jal(ctx, 0x1CE4CCu, gen::fn_sub_319190_00319190);
                } else {
                    // 0x001ce438
                    charge(ctx, 7);
                    a2 = 0;
                    jal(ctx, 0x1CE43Cu, gen::fn_sub_316E00_00316e00);
                    s1 = v0;
                    v0 = 1;
                    if (s2 == v0) {
                        // 0x001ce454
                        charge(ctx, 3);
                        a0 = s1;
                        jal(ctx, 0x1CE458u, gen::fn_sub_31C1D0_0031c1d0);
                    }
                    // 0x001ce460
                    charge(ctx, 6);
                    v1 = 0x870000;
                    v1 = addiu(v1, 7844);  // &0x871EA4
                    v0 = addu(v1, s4);
                    lw(a0, v0, 0);
                    if (a0 != 0) {
                        // 0x001ce478
                        charge(ctx, 5);
                        v0 = sll(s0, 3);
                        s2 = addu(v1, v0);
                        jal(ctx, 0x1CE480u, gen::fn_sub_3174E0_003174e0);
                        sw(zero, s2, 0);
                    }
                    // 0x001ce48c
                    charge(ctx, 15);
                    a0 = sll(s0, 3);
                    v0 = 0x870000;
                    v0 = addiu(v0, 7844);  // &0x871EA4
                    v1 = addu(v0, a0);
                    sw(s1, v1, 0);
                    lhu(v0, s1, 212);
                    sh(v0, s3, 0);
                    lw(v0, v1, 0);
                    lhu(v1, v0, 214);
                    v0 = 0x870000;
                    v0 = addiu(v0, 7842);  // &0x871EA2
                    v0 = addu(v0, a0);
                    sh(v1, v0, 0);
                }
            } else {
                // 0x001cda2c
                charge(ctx, 3);
                a1 = 5;
                if (s1 == a1) {
                    // 0x001ce1f8
                    charge(ctx, 5);
                    lw(a0, gp, -22448);  // 0x7CD540
                    lw(v1, a0, 0);
                    v0 = 14;
                    if (v1 == v0) {
                        // 0x001ce20c
                        charge(ctx, 3);
                        lw(v0, a0, 4);
                        if (v0 != a1) {
                            goto L_001ce228;
                        }
                        // 0x001ce218
                        charge(ctx, 4);
                        a0 = 9;
                        a1 = 1282;
                        goto L_001ce27c;
                    }
                L_001ce228:
                    charge(ctx, 6);
                    a0 = 3119;
                    jal(ctx, 0x1CE22Cu, gen::fn_datGetFlag_0016f190);
                    a0 = 1;
                    if (v0 != a0) {
                        // 0x001ce250
                        charge(ctx, 5);
                        lw(v0, gp, -22448);  // 0x7CD540
                        lw(v1, v0, 0);
                        v0 = 33;
                        if (v1 != v0) {
                            // 0x001ce274
                            charge(ctx, 2);
                            a0 = a0 & 0xFFFF;
                            a1 = s1 & 0xFFFF;
                        } else {
                            // 0x001ce264
                            charge(ctx, 4);
                            a0 = 9;
                            a1 = 1281;
                        }
                    } else {
                        // 0x001ce240
                        charge(ctx, 4);
                        a0 = 9;
                        a1 = 1280;
                    }
                L_001ce27c:
                    charge(ctx, 8);
                    s4 = sll(s0, 3);
                    v0 = 0x870000;
                    v0 = addiu(v0, 7840);  // &0x871EA0
                    s3 = addu(v0, s4);
                    s2 = a0 & 0xFFFF;
                    lhu(v0, s3, 0);
                    if (s2 == v0) {
                        // 0x001ce29c
                        charge(ctx, 7);
                        v1 = a1 & 0xFFFF;
                        v0 = 0x870000;
                        v0 = addiu(v0, 7842);  // &0x871EA2
                        v0 = addu(v0, s4);
                        lhu(v0, v0, 0);
                        if (v1 != v0) {
                            goto L_001ce2d0;
                        }
                        // 0x001ce2b8
                        charge(ctx, 6);
                        v0 = 0x870000;
                        v0 = addiu(v0, 7844);  // &0x871EA4
                        v0 = addu(v0, s4);
                        lw(s1, v0, 0);
                        goto L_001ce2d4;
                    }
                L_001ce2d0:
                    charge(ctx, 1);
                    s1 = 0;
                L_001ce2d4:
                    charge(ctx, 2);
                    if (s1 != 0) {
                        // 0x001ce36c
                        charge(ctx, 5);
                        a0 = s1;
                        jal(ctx, 0x1CE370u, gen::fn_sub_319190_00319190);
                    } else {
                        // 0x001ce2dc
                        charge(ctx, 7);
                        a2 = 0;
                        jal(ctx, 0x1CE2E0u, gen::fn_sub_316E00_00316e00);
                        s1 = v0;
                        v0 = 1;
                        if (s2 == v0) {
                            // 0x001ce2f8
                            charge(ctx, 3);
                            a0 = s1;
                            jal(ctx, 0x1CE2FCu, gen::fn_sub_31C1D0_0031c1d0);
                        }
                        // 0x001ce304
                        charge(ctx, 6);
                        v1 = 0x870000;
                        v1 = addiu(v1, 7844);  // &0x871EA4
                        v0 = addu(v1, s4);
                        lw(a0, v0, 0);
                        if (a0 != 0) {
                            // 0x001ce31c
                            charge(ctx, 5);
                            v0 = sll(s0, 3);
                            s2 = addu(v1, v0);
                            jal(ctx, 0x1CE324u, gen::fn_sub_3174E0_003174e0);
                            sw(zero, s2, 0);
                        }
                        // 0x001ce330
                        charge(ctx, 15);
                        a0 = sll(s0, 3);
                        v0 = 0x870000;
                        v0 = addiu(v0, 7844);  // &0x871EA4
                        v1 = addu(v0, a0);
                        sw(s1, v1, 0);
                        lhu(v0, s1, 212);
                        sh(v0, s3, 0);
                        lw(v0, v1, 0);
                        lhu(v1, v0, 214);
                        v0 = 0x870000;
                        v0 = addiu(v0, 7842);  // &0x871EA2
                        v0 = addu(v0, a0);
                        sh(v1, v0, 0);
                    }
                } else {
                    // 0x001cda38
                    charge(ctx, 3);
                    v0 = 2;
                    if (s1 == v0) {
                        // 0x001ce0c0
                        charge(ctx, 5);
                        lw(v0, gp, -22448);  // 0x7CD540
                        lw(v1, v0, 0);
                        v0 = 6;
                        if (v1 != v0) {
                            // 0x001ce0d4
                            charge(ctx, 2);
                            if (v1 == a0) {
                                goto L_001ce0dc;
                            }
                            // 0x001ce0ec
                            charge(ctx, 2);
                            a0 = 1;
                            a1 = s1 & 0xFFFF;
                            goto L_001ce0f4;
                        }
                    L_001ce0dc:
                        charge(ctx, 4);
                        a0 = 9;
                        a1 = 512;
                    L_001ce0f4:
                        charge(ctx, 8);
                        s4 = sll(s0, 3);
                        v0 = 0x870000;
                        v0 = addiu(v0, 7840);  // &0x871EA0
                        s3 = addu(v0, s4);
                        s2 = a0 & 0xFFFF;
                        lhu(v0, s3, 0);
                        if (s2 == v0) {
                            // 0x001ce114
                            charge(ctx, 7);
                            v1 = a1 & 0xFFFF;
                            v0 = 0x870000;
                            v0 = addiu(v0, 7842);  // &0x871EA2
                            v0 = addu(v0, s4);
                            lhu(v0, v0, 0);
                            if (v1 != v0) {
                                goto L_001ce148;
                            }
                            // 0x001ce130
                            charge(ctx, 6);
                            v0 = 0x870000;
                            v0 = addiu(v0, 7844);  // &0x871EA4
                            v0 = addu(v0, s4);
                            lw(s1, v0, 0);
                            goto L_001ce14c;
                        }
                    L_001ce148:
                        charge(ctx, 1);
                        s1 = 0;
                    L_001ce14c:
                        charge(ctx, 2);
                        if (s1 != 0) {
                            // 0x001ce1e4
                            charge(ctx, 5);
                            a0 = s1;
                            jal(ctx, 0x1CE1E8u, gen::fn_sub_319190_00319190);
                        } else {
                            // 0x001ce154
                            charge(ctx, 7);
                            a2 = 0;
                            jal(ctx, 0x1CE158u, gen::fn_sub_316E00_00316e00);
                            s1 = v0;
                            v0 = 1;
                            if (s2 == v0) {
                                // 0x001ce170
                                charge(ctx, 3);
                                a0 = s1;
                                jal(ctx, 0x1CE174u, gen::fn_sub_31C1D0_0031c1d0);
                            }
                            // 0x001ce17c
                            charge(ctx, 6);
                            v1 = 0x870000;
                            v1 = addiu(v1, 7844);  // &0x871EA4
                            v0 = addu(v1, s4);
                            lw(a0, v0, 0);
                            if (a0 != 0) {
                                // 0x001ce194
                                charge(ctx, 5);
                                v0 = sll(s0, 3);
                                s2 = addu(v1, v0);
                                jal(ctx, 0x1CE19Cu, gen::fn_sub_3174E0_003174e0);
                                sw(zero, s2, 0);
                            }
                            // 0x001ce1a8
                            charge(ctx, 15);
                            a0 = sll(s0, 3);
                            v0 = 0x870000;
                            v0 = addiu(v0, 7844);  // &0x871EA4
                            v1 = addu(v0, a0);
                            sw(s1, v1, 0);
                            lhu(v0, s1, 212);
                            sh(v0, s3, 0);
                            lw(v0, v1, 0);
                            lhu(v1, v0, 214);
                            v0 = 0x870000;
                            v0 = addiu(v0, 7842);  // &0x871EA2
                            v0 = addu(v0, a0);
                            sh(v1, v0, 0);
                        }
                    } else {
                        // 0x001cda44
                        charge(ctx, 3);
                        v1 = 1;
                        if (s1 == v1) {
                            // 0x001cda58
                            charge(ctx, 5);
                            jal(ctx, 0x1CDA58u, gen::fn_sub_17D800_0017d800);
                            v1 = 1;
                            if (v0 == v1) {
                                // 0x001cda6c
                                charge(ctx, 5);
                                lw(v0, gp, -22448);  // 0x7CD540
                                lw(v1, v0, 0);
                                v0 = 4;
                                if (v1 != v0) {
                                    // 0x001cda80
                                    charge(ctx, 3);
                                    v0 = 5;
                                    if (v1 != v0) {
                                        goto L_001cda9c;
                                    }
                                    goto L_001cda8c;
                                }
                            L_001cda8c:
                                charge(ctx, 4);
                                a0 = 9;
                                a1 = 5120;
                                goto L_001cdfbc;
                            }
                        L_001cda9c:
                            charge(ctx, 5);
                            jal(ctx, 0x1CDA9Cu, gen::fn_sub_1A0310_001a0310);
                            v1 = 1;
                            if (v0 != v1) {
                                // 0x001cdac0
                                charge(ctx, 5);
                                lw(a0, gp, -22448);  // 0x7CD540
                                lw(v1, a0, 0);
                                v0 = 7;
                                if (v1 == v0) {
                                    // 0x001cdad4
                                    charge(ctx, 4);
                                    lw(v1, a0, 4);
                                    v0 = 6;
                                    if (v1 != v0) {
                                        goto L_001cdafc;
                                    }
                                    // 0x001cdae4
                                    charge(ctx, 6);
                                    jal(ctx, 0x1CDAE4u, gen::fn_datGetTime_0016ef30);
                                    v1 = v0 & 0xFF;
                                    v0 = 8;
                                    if (v1 != v0) {
                                        goto L_001cdafc;
                                    }
                                L_001cdb74:
                                    charge(ctx, 4);
                                    a0 = 9;
                                    a1 = 260;
                                    goto L_001cdfbc;
                                }
                            L_001cdafc:
                                charge(ctx, 5);
                                lw(a0, gp, -22448);  // 0x7CD540
                                lw(v1, a0, 0);
                                v0 = 8;
                                if (v1 == v0) {
                                    // 0x001cdb10
                                    charge(ctx, 4);
                                    lw(v1, a0, 4);
                                    v0 = 1;
                                    if (v1 != v0) {
                                        goto L_001cdb38;
                                    }
                                    // 0x001cdb20
                                    charge(ctx, 6);
                                    jal(ctx, 0x1CDB20u, gen::fn_datGetTime_0016ef30);
                                    v1 = v0 & 0xFF;
                                    v0 = 8;
                                    if (v1 == v0) {
                                        goto L_001cdb74;
                                    }
                                    goto L_001cdb38;
                                }
                            L_001cdb38:
                                charge(ctx, 5);
                                lw(a0, gp, -22448);  // 0x7CD540
                                lw(v1, a0, 0);
                                v0 = 9;
                                if (v1 == v0) {
                                    // 0x001cdb4c
                                    charge(ctx, 4);
                                    lw(v1, a0, 4);
                                    v0 = 1;
                                    if (v1 != v0) {
                                        goto L_001cdb84;
                                    }
                                    // 0x001cdb5c
                                    charge(ctx, 6);
                                    jal(ctx, 0x1CDB5Cu, gen::fn_datGetTime_0016ef30);
                                    v1 = v0 & 0xFF;
                                    v0 = 8;
                                    if (v1 != v0) {
                                        goto L_001cdb84;
                                    }
                                    goto L_001cdb74;
                                }
                            L_001cdb84:
                                charge(ctx, 5);
                                lw(v0, gp, -22448);  // 0x7CD540
                                lw(v1, v0, 0);
                                v0 = 33;
                                if (v1 != v0) {
                                    // 0x001cdba8
                                    charge(ctx, 5);
                                    jal(ctx, 0x1CDBA8u, gen::fn_sub_1A01C0_001a01c0);
                                    v1 = 1;
                                    if (v0 != v1) {
                                        // 0x001cdbbc
                                        charge(ctx, 5);
                                        lw(v1, gp, -22448);  // 0x7CD540
                                        lw(v0, v1, 0);
                                        a0 = 21;
                                        if (v0 == a0) {
                                            // 0x001cdbd0
                                            charge(ctx, 4);
                                            lw(a1, v1, 4);
                                            a0 = 50;
                                            if (a1 == a0) {
                                                goto L_001cddf4;
                                            }
                                            goto L_001cdbe0;
                                        }
                                    L_001cdbe0:
                                        charge(ctx, 3);
                                        a0 = 22;
                                        if (v0 == a0) {
                                            // 0x001cdbec
                                            charge(ctx, 4);
                                            lw(a1, v1, 4);
                                            a0 = 50;
                                            if (a1 == a0) {
                                                goto L_001cddf4;
                                            }
                                            goto L_001cdbfc;
                                        }
                                    L_001cdbfc:
                                        charge(ctx, 3);
                                        a0 = 22;
                                        if (v0 == a0) {
                                            // 0x001cdc08
                                            charge(ctx, 4);
                                            lw(a1, v1, 4);
                                            a0 = 51;
                                            if (a1 == a0) {
                                                goto L_001cddf4;
                                            }
                                            goto L_001cdc18;
                                        }
                                    L_001cdc18:
                                        charge(ctx, 3);
                                        a0 = 23;
                                        if (v0 == a0) {
                                            // 0x001cdc24
                                            charge(ctx, 4);
                                            lw(a1, v1, 4);
                                            a0 = 50;
                                            if (a1 == a0) {
                                                goto L_001cddf4;
                                            }
                                            goto L_001cdc34;
                                        }
                                    L_001cdc34:
                                        charge(ctx, 3);
                                        a0 = 23;
                                        if (v0 == a0) {
                                            // 0x001cdc40
                                            charge(ctx, 4);
                                            lw(a1, v1, 4);
                                            a0 = 51;
                                            if (a1 == a0) {
                                                goto L_001cddf4;
                                            }
                                            goto L_001cdc50;
                                        }
                                    L_001cdc50:
                                        charge(ctx, 3);
                                        a0 = 24;
                                        if (v0 == a0) {
                                            // 0x001cdc5c
                                            charge(ctx, 4);
                                            lw(a1, v1, 4);
                                            a0 = 50;
                                            if (a1 == a0) {
                                                goto L_001cddf4;
                                            }
                                            goto L_001cdc6c;
                                        }
                                    L_001cdc6c:
                                        charge(ctx, 3);
                                        a0 = 24;
                                        if (v0 == a0) {
                                            // 0x001cdc78
                                            charge(ctx, 4);
                                            lw(a1, v1, 4);
                                            a0 = 51;
                                            if (a1 == a0) {
                                                goto L_001cddf4;
                                            }
                                            goto L_001cdc88;
                                        }
                                    L_001cdc88:
                                        charge(ctx, 3);
                                        a0 = 25;
                                        if (v0 == a0) {
                                            // 0x001cdc94
                                            charge(ctx, 4);
                                            lw(a1, v1, 4);
                                            a0 = 50;
                                            if (a1 == a0) {
                                                goto L_001cddf4;
                                            }
                                            goto L_001cdca4;
                                        }
                                    L_001cdca4:
                                        charge(ctx, 3);
                                        a0 = 26;
                                        if (v0 == a0) {
                                            // 0x001cdcb0
                                            charge(ctx, 4);
                                            lw(a1, v1, 4);
                                            a0 = 50;
                                            if (a1 == a0) {
                                                goto L_001cddf4;
                                            }
                                            goto L_001cdcc0;
                                        }
                                    L_001cdcc0:
                                        charge(ctx, 3);
                                        a0 = 27;
                                        if (v0 == a0) {
                                            // 0x001cdccc
                                            charge(ctx, 4);
                                            lw(a1, v1, 4);
                                            a0 = 50;
                                            if (a1 == a0) {
                                                goto L_001cddf4;
                                            }
                                            goto L_001cdcdc;
                                        }
                                    L_001cdcdc:
                                        charge(ctx, 3);
                                        a0 = 41;
                                        if (v0 == a0) {
                                            // 0x001cdce8
                                            charge(ctx, 4);
                                            lw(a1, v1, 4);
                                            a0 = 50;
                                            if (a1 == a0) {
                                                goto L_001cddf4;
                                            }
                                            goto L_001cdcf8;
                                        }
                                    L_001cdcf8:
                                        charge(ctx, 3);
                                        a0 = 42;
                                        if (v0 == a0) {
                                            // 0x001cdd04
                                            charge(ctx, 4);
                                            lw(a1, v1, 4);
                                            a0 = 50;
                                            if (a1 == a0) {
                                                goto L_001cddf4;
                                            }
                                            goto L_001cdd14;
                                        }
                                    L_001cdd14:
                                        charge(ctx, 3);
                                        a0 = 43;
                                        if (v0 == a0) {
                                            // 0x001cdd20
                                            charge(ctx, 4);
                                            lw(a1, v1, 4);
                                            a0 = 50;
                                            if (a1 == a0) {
                                                goto L_001cddf4;
                                            }
                                            goto L_001cdd30;
                                        }
                                    L_001cdd30:
                                        charge(ctx, 3);
                                        a0 = 44;
                                        if (v0 == a0) {
                                            // 0x001cdd3c
                                            charge(ctx, 4);
                                            lw(a1, v1, 4);
                                            a0 = 50;
                                            if (a1 == a0) {
                                                goto L_001cddf4;
                                            }
                                            goto L_001cdd4c;
                                        }
                                    L_001cdd4c:
                                        charge(ctx, 3);
                                        a0 = 45;
                                        if (v0 == a0) {
                                            // 0x001cdd58
                                            charge(ctx, 4);
                                            lw(a1, v1, 4);
                                            a0 = 50;
                                            if (a1 == a0) {
                                                goto L_001cddf4;
                                            }
                                            goto L_001cdd68;
                                        }
                                    L_001cdd68:
                                        charge(ctx, 3);
                                        a0 = 46;
                                        if (v0 == a0) {
                                            // 0x001cdd74
                                            charge(ctx, 4);
                                            lw(a1, v1, 4);
                                            a0 = 50;
                                            if (a1 == a0) {
                                                goto L_001cddf4;
                                            }
                                            goto L_001cdd84;
                                        }
                                    L_001cdd84:
                                        charge(ctx, 3);
                                        a0 = 47;
                                        if (v0 == a0) {
                                            // 0x001cdd90
                                            charge(ctx, 4);
                                            lw(a1, v1, 4);
                                            a0 = 50;
                                            if (a1 == a0) {
                                                goto L_001cddf4;
                                            }
                                            goto L_001cdda0;
                                        }
                                    L_001cdda0:
                                        charge(ctx, 3);
                                        a0 = 39;
                                        if (v0 == a0) {
                                            // 0x001cddac
                                            charge(ctx, 4);
                                            lw(a1, v1, 4);
                                            a0 = 1;
                                            if (a1 == a0) {
                                                goto L_001cddf4;
                                            }
                                            goto L_001cddbc;
                                        }
                                    L_001cddbc:
                                        charge(ctx, 3);
                                        a0 = 39;
                                        if (v0 == a0) {
                                            // 0x001cddc8
                                            charge(ctx, 4);
                                            lw(a1, v1, 4);
                                            a0 = 2;
                                            if (a1 == a0) {
                                                goto L_001cddf4;
                                            }
                                            goto L_001cddd8;
                                        }
                                    L_001cddd8:
                                        charge(ctx, 3);
                                        a0 = 39;
                                        if (v0 == a0) {
                                            // 0x001cdde4
                                            charge(ctx, 4);
                                            lw(a0, v1, 4);
                                            v1 = 3;
                                            if (a0 != v1) {
                                                goto L_001cde04;
                                            }
                                            goto L_001cddf4;
                                        }
                                    L_001cde04:
                                        charge(ctx, 3);
                                        v1 = 7;
                                        if (v0 == v1) {
                                            // 0x001cde10
                                            charge(ctx, 6);
                                            a0 = 3584;
                                            jal(ctx, 0x1CDE14u, gen::fn_datGetFlag_0016f190);
                                            v1 = 1;
                                            if (v0 != v1) {
                                                goto L_001cde38;
                                            }
                                            // 0x001cde28
                                            charge(ctx, 4);
                                            a0 = 9;
                                            a1 = 261;
                                            goto L_001cdfbc;
                                        }
                                    L_001cde38:
                                        charge(ctx, 5);
                                        lw(v0, gp, -22448);  // 0x7CD540
                                        lw(v1, v0, 0);
                                        v0 = 6;
                                        if (v1 == v0) {
                                            // 0x001cde4c
                                            charge(ctx, 6);
                                            a0 = 3680;
                                            jal(ctx, 0x1CDE50u, gen::fn_datGetFlag_0016f190);
                                            v1 = 1;
                                            if (v0 != v1) {
                                                goto L_001cde74;
                                            }
                                            // 0x001cde64
                                            charge(ctx, 4);
                                            a0 = 9;
                                            a1 = 260;
                                            goto L_001cdfbc;
                                        }
                                    L_001cde74:
                                        charge(ctx, 5);
                                        lw(v1, gp, -22448);  // 0x7CD540
                                        lw(a0, v1, 0);
                                        v0 = 14;
                                        if (a0 == v0) {
                                            // 0x001cde88
                                            charge(ctx, 4);
                                            lw(v1, v1, 4);
                                            v0 = 5;
                                            if (v1 != v0) {
                                                goto L_001cdea8;
                                            }
                                            // 0x001cde98
                                            charge(ctx, 4);
                                            a0 = 9;
                                            a1 = 263;
                                            goto L_001cdfbc;
                                        }
                                    L_001cdea8:
                                        charge(ctx, 3);
                                        v0 = 14;
                                        if (a0 == v0) {
                                            // 0x001cdeb4
                                            charge(ctx, 6);
                                            jal(ctx, 0x1CDEB4u, gen::fn_datGetTime_0016ef30);
                                            v1 = v0 & 0xFF;
                                            v0 = 6;
                                            if (v1 != v0) {
                                                goto L_001cdf2c;
                                            }
                                            // 0x001cdecc
                                            charge(ctx, 5);
                                            jal(ctx, 0x1CDECCu, gen::fn_clndGetCurrentMonth_0017d920);
                                            v1 = 11;
                                            if (v0 == v1) {
                                                // 0x001cdee0
                                                charge(ctx, 5);
                                                jal(ctx, 0x1CDEE0u, gen::fn_clndGetCurrentDay_0017da40);
                                                v1 = 18;
                                                if (v0 != v1) {
                                                    goto L_001cdef4;
                                                }
                                            L_001cdf1c:
                                                charge(ctx, 4);
                                                a0 = 9;
                                                a1 = 264;
                                                goto L_001cdfbc;
                                            }
                                        L_001cdef4:
                                            charge(ctx, 5);
                                            jal(ctx, 0x1CDEF4u, gen::fn_clndGetCurrentMonth_0017d920);
                                            v1 = 11;
                                            if (v0 != v1) {
                                                goto L_001cdf2c;
                                            }
                                            // 0x001cdf08
                                            charge(ctx, 5);
                                            jal(ctx, 0x1CDF08u, gen::fn_clndGetCurrentDay_0017da40);
                                            v1 = 19;
                                            if (v0 != v1) {
                                                goto L_001cdf2c;
                                            }
                                            goto L_001cdf1c;
                                        }
                                    L_001cdf2c:
                                        charge(ctx, 6);
                                        a0 = 2697;
                                        jal(ctx, 0x1CDF30u, gen::fn_datGetFlag_0016f190);
                                        a1 = 1;
                                        if (v0 != a1) {
                                            // 0x001cdf84
                                            charge(ctx, 8);
                                            a0 = 6;
                                            a2 = 9;
                                            a3 = 30;
                                            jal(ctx, 0x1CDF90u, gen::fn_clndIsDateInRange_0017e480);
                                            v1 = 1;
                                            if (v0 != v1) {
                                                // 0x001cdfb4
                                                charge(ctx, 2);
                                                a0 = 9;
                                                a1 = 256;
                                            } else {
                                                // 0x001cdfa4
                                                charge(ctx, 4);
                                                a0 = 9;
                                                a1 = 257;
                                            }
                                        } else {
                                            // 0x001cdf44
                                            charge(ctx, 8);
                                            a0 = 6;
                                            a2 = 9;
                                            a3 = 30;
                                            jal(ctx, 0x1CDF50u, gen::fn_clndIsDateInRange_0017e480);
                                            v1 = 1;
                                            if (v0 != v1) {
                                                // 0x001cdf74
                                                charge(ctx, 4);
                                                a0 = 9;
                                                a1 = 258;
                                            } else {
                                                // 0x001cdf64
                                                charge(ctx, 4);
                                                a0 = 9;
                                                a1 = 259;
                                            }
                                        }
                                        goto L_001cdfbc;
                                    }
                                L_001cddf4:
                                    charge(ctx, 4);
                                    a0 = 1;
                                    a1 = s1 & 0xFFFF;
                                } else {
                                    // 0x001cdb98
                                    charge(ctx, 4);
                                    a0 = 9;
                                    a1 = 262;
                                }
                            } else {
                                // 0x001cdab0
                                charge(ctx, 4);
                                a0 = 9;
                                a1 = 260;
                            }
                        L_001cdfbc:
                            charge(ctx, 8);
                            s4 = sll(s0, 3);
                            v0 = 0x870000;
                            v0 = addiu(v0, 7840);  // &0x871EA0
                            s3 = addu(v0, s4);
                            s2 = a0 & 0xFFFF;
                            lhu(v0, s3, 0);
                            if (s2 == v0) {
                                // 0x001cdfdc
                                charge(ctx, 7);
                                v1 = a1 & 0xFFFF;
                                v0 = 0x870000;
                                v0 = addiu(v0, 7842);  // &0x871EA2
                                v0 = addu(v0, s4);
                                lhu(v0, v0, 0);
                                if (v1 != v0) {
                                    goto L_001ce010;
                                }
                                // 0x001cdff8
                                charge(ctx, 6);
                                v0 = 0x870000;
                                v0 = addiu(v0, 7844);  // &0x871EA4
                                v0 = addu(v0, s4);
                                lw(s1, v0, 0);
                                goto L_001ce014;
                            }
                        L_001ce010:
                            charge(ctx, 1);
                            s1 = 0;
                        L_001ce014:
                            charge(ctx, 2);
                            if (s1 != 0) {
                                // 0x001ce0ac
                                charge(ctx, 5);
                                a0 = s1;
                                jal(ctx, 0x1CE0B0u, gen::fn_sub_319190_00319190);
                            } else {
                                // 0x001ce01c
                                charge(ctx, 7);
                                a2 = 0;
                                jal(ctx, 0x1CE020u, gen::fn_sub_316E00_00316e00);
                                s1 = v0;
                                v0 = 1;
                                if (s2 == v0) {
                                    // 0x001ce038
                                    charge(ctx, 3);
                                    a0 = s1;
                                    jal(ctx, 0x1CE03Cu, gen::fn_sub_31C1D0_0031c1d0);
                                }
                                // 0x001ce044
                                charge(ctx, 6);
                                v1 = 0x870000;
                                v1 = addiu(v1, 7844);  // &0x871EA4
                                v0 = addu(v1, s4);
                                lw(a0, v0, 0);
                                if (a0 != 0) {
                                    // 0x001ce05c
                                    charge(ctx, 5);
                                    v0 = sll(s0, 3);
                                    s2 = addu(v1, v0);
                                    jal(ctx, 0x1CE064u, gen::fn_sub_3174E0_003174e0);
                                    sw(zero, s2, 0);
                                }
                                // 0x001ce070
                                charge(ctx, 15);
                                a0 = sll(s0, 3);
                                v0 = 0x870000;
                                v0 = addiu(v0, 7844);  // &0x871EA4
                                v1 = addu(v0, a0);
                                sw(s1, v1, 0);
                                lhu(v0, s1, 212);
                                sh(v0, s3, 0);
                                lw(v0, v1, 0);
                                lhu(v1, v0, 214);
                                v0 = 0x870000;
                                v0 = addiu(v0, 7842);  // &0x871EA2
                                v0 = addu(v0, a0);
                                sh(v1, v0, 0);
                            }
                        } else {
                            // 0x001cda50
                            charge(ctx, 2);
                            // 0x001ce75c
                            charge(ctx, 8);
                            a1 = s1 & 0xFFFF;
                            s3 = sll(s0, 3);
                            v0 = 0x870000;
                            v0 = addiu(v0, 7840);  // &0x871EA0
                            s2 = addu(v0, s3);
                            lhu(v0, s2, 0);
                            if (v0 == v1) {
                                // 0x001ce77c
                                charge(ctx, 7);
                                v1 = a1 & 0xFFFF;
                                v0 = 0x870000;
                                v0 = addiu(v0, 7842);  // &0x871EA2
                                v0 = addu(v0, s3);
                                lhu(v0, v0, 0);
                                if (v1 != v0) {
                                    goto L_001ce7b0;
                                }
                                // 0x001ce798
                                charge(ctx, 6);
                                v0 = 0x870000;
                                v0 = addiu(v0, 7844);  // &0x871EA4
                                v0 = addu(v0, s3);
                                lw(s1, v0, 0);
                                goto L_001ce7b4;
                            }
                        L_001ce7b0:
                            charge(ctx, 1);
                            s1 = 0;
                        L_001ce7b4:
                            charge(ctx, 2);
                            if (s1 != 0) {
                                // 0x001ce844
                                charge(ctx, 3);
                                a0 = s1;
                                jal(ctx, 0x1CE848u, gen::fn_sub_319190_00319190);
                            } else {
                                // 0x001ce7bc
                                charge(ctx, 14);
                                a0 = 1;
                                a2 = 0;
                                jal(ctx, 0x1CE7C4u, gen::fn_sub_316E00_00316e00);
                                s1 = v0;
                                a0 = s1;
                                jal(ctx, 0x1CE7D4u, gen::fn_sub_31C1D0_0031c1d0);
                                v1 = 0x870000;
                                v1 = addiu(v1, 7844);  // &0x871EA4
                                v0 = addu(v1, s3);
                                lw(a0, v0, 0);
                                if (a0 != 0) {
                                    // 0x001ce7f4
                                    charge(ctx, 5);
                                    v0 = sll(s0, 3);
                                    s3 = addu(v1, v0);
                                    jal(ctx, 0x1CE7FCu, gen::fn_sub_3174E0_003174e0);
                                    sw(zero, s3, 0);
                                }
                                // 0x001ce808
                                charge(ctx, 15);
                                a0 = sll(s0, 3);
                                v0 = 0x870000;
                                v0 = addiu(v0, 7844);  // &0x871EA4
                                v1 = addu(v0, a0);
                                sw(s1, v1, 0);
                                lhu(v0, s1, 212);
                                sh(v0, s2, 0);
                                lw(v0, v1, 0);
                                lhu(v1, v0, 214);
                                v0 = 0x870000;
                                v0 = addiu(v0, 7842);  // &0x871EA2
                                v0 = addu(v0, a0);
                                sh(v1, v0, 0);
                            }
                        }
                    }
                }
            }
        }
    }
    // 0x001ce850 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    v0 = s1;
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
L_001cd9ec_2:
    charge(ctx, 3);
    s0 = addiu(s2, 1);
    goto L_001cda08;
}

// 0x001D78C0 K_Encount_PickEncounter -- 680 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Pick the encounter group for floor a0 / block a1 / variant a2: floors 20..28 and 40..48 (block 0), 51..58 and
// 71..78 index the variant table 0x7CE4B0 by a2; floors 31..39 index 0x7CE4B4 by a0 / a1; any other floor gives 0.
// The row (180 bytes in *(0x7CE4B8)) is then picked from with sub_488F30, by the floor kind (K_FldDungeon_GetFloorKind).
void K_Encount_PickEncounter(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001d78c0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = 0;
    v1 = a0 & 0xFFFF;
    v0 = slti(v1, 20);
    if (v0 == 0) {
        // 0x001d78ec
        charge(ctx, 3);
        at = slti(v1, 29);
        if (at == 0) {
            goto L_001d7904;
        }
        // 0x001d78f8
        charge(ctx, 3);
        v0 = a1 & 0xFFFF;
        if (v0 != 0) {
            goto L_001d7904;
        }
    L_001d7958:
        charge(ctx, 16);
        lw(a0, gp, -18496);  // 0x7CE4B0
        v1 = a2 & 0xFFFF;
        v0 = sll(v1, 2);
        v0 = addu(v0, v1);
        v0 = sll(v0, 1);
        v0 = addu(v0, a0);
        lhu(v1, v0, 6);
        v0 = sll(v1, 4);
        v1 = subu(v0, v1);
        v0 = sll(v1, 2);
        v0 = subu(v0, v1);
        v1 = sll(v0, 2);
        lw(v0, gp, -18488);  // 0x7CE4B8
        s2 = addu(v0, v1);
    L_001d7a14:
        charge(ctx, 6);
        s0 = 1;
        jal(ctx, 0x1D7A18u, gen::fn_K_FldDungeon_GetFloorKind_001c0040);
        v1 = 2;
        if (v0 == v1) {
            // 0x001d7a2c
            charge(ctx, 1);
            s0 = v1;
        }
        // 0x001d7a30
        charge(ctx, 4);
        a0 = 0;
        s1 = 0;
        for (;;) {
            // 0x001d7a8c
            charge(ctx, 3);
            v0 = slti(a0, 15);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001d7a40
            charge(ctx, 7);
            v0 = sll(a0, 1);
            v0 = addu(v0, a0);
            v0 = sll(v0, 2);
            v1 = addu(s2, v0);
            lhu(v0, v1, 2);
            if (v0 != 0) {
                // 0x001d7a5c
                charge(ctx, 4);
                lbu(v0, v1, 7);
                v0 = v0 & 0x1;
                if (v0 == 0) {
                    // 0x001d7a80
                    charge(ctx, 2);
                    lhu(v0, v1, 0);
                    s1 = addu(s1, v0);
                } else {
                    // 0x001d7a6c
                    charge(ctx, 5);
                    lhu(v0, v1, 0);
                    mult(v0, s0, v0);
                    s1 = addu(s1, v0);
                }
            }
            // 0x001d7a88
            charge(ctx, 1);
            a0 = addiu(a0, 1);
        }
        // 0x001d7a98
        charge(ctx, 2);
        if (s1 == 0) {
            // 0x001d7aa0
            charge(ctx, 5);
            a0 = 0x680000;
            a0 = addiu(a0, 15144);  // "k_encount.c"
            a1 = 327;
            jal(ctx, 0x1D7AACu, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x001d7ab4
        charge(ctx, 8);
        jal(ctx, 0x1D7AB4u, gen::fn_sub_488F30_00488f30);
        divu(v0, s1);
        mfhi(v1);
        a0 = 0;
        a2 = 0;
        for (;;) {
            // 0x001d7b38
            charge(ctx, 3);
            v0 = slti(a0, 15);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001d7ad4
            charge(ctx, 7);
            v0 = sll(a0, 1);
            v0 = addu(v0, a0);
            v0 = sll(v0, 2);
            a1 = addu(s2, v0);
            lhu(v0, a1, 2);
            if (v0 != 0) {
                // 0x001d7af0
                charge(ctx, 4);
                lbu(v0, a1, 7);
                v0 = v0 & 0x1;
                if (v0 == 0) {
                    // 0x001d7b14
                    charge(ctx, 2);
                    lhu(v0, a1, 0);
                    a2 = addu(a2, v0);
                } else {
                    // 0x001d7b00
                    charge(ctx, 5);
                    lhu(v0, a1, 0);
                    mult(v0, s0, v0);
                    a2 = addu(a2, v0);
                }
                // 0x001d7b1c
                charge(ctx, 3);
                at = slt(v1, a2);
                if (at == 0) {
                    goto L_001d7b34;
                }
                goto L_001d7b28_32;
            }
        L_001d7b34:
            charge(ctx, 1);
            a0 = addiu(a0, 1);
        }
    L_001d7b44:
        charge(ctx, 1);
        v0 = s3;
        // 0x001d7b48 (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(ra, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        return;
    }
L_001d7904:
    charge(ctx, 3);
    v0 = slti(v1, 40);
    if (v0 == 0) {
        // 0x001d7910
        charge(ctx, 3);
        at = slti(v1, 49);
        if (at == 0) {
            goto L_001d7928;
        }
        // 0x001d791c
        charge(ctx, 3);
        v0 = a1 & 0xFFFF;
        if (v0 == 0) {
            goto L_001d7958;
        }
        goto L_001d7928;
    }
L_001d7928:
    charge(ctx, 3);
    v0 = slti(v1, 51);
    if (v0 == 0) {
        // 0x001d7934
        charge(ctx, 3);
        at = slti(v1, 59);
        if (at != 0) {
            goto L_001d7958;
        }
        goto L_001d7940;
    }
L_001d7940:
    charge(ctx, 3);
    v0 = slti(v1, 71);
    if (v0 == 0) {
        // 0x001d794c
        charge(ctx, 3);
        at = slti(v1, 79);
        if (at == 0) {
            goto L_001d7998;
        }
        goto L_001d7958;
    }
L_001d7998:
    charge(ctx, 3);
    v0 = slti(v1, 31);
    if (v0 == 0) {
        // 0x001d79a4
        charge(ctx, 3);
        at = slti(v1, 40);
        if (at == 0) {
            goto L_001d7a08;
        }
        // 0x001d79b0
        charge(ctx, 22);
        lw(a0, gp, -18492);  // 0x7CE4B4
        v0 = sll(v1, 2);
        v1 = addu(v0, v1);
        v0 = sll(v1, 2);
        v0 = addu(v1, v0);
        v0 = sll(v0, 3);
        a0 = addu(v0, a0);
        v1 = a1 & 0xFFFF;
        v0 = sll(v1, 2);
        v0 = addu(v0, v1);
        v0 = sll(v0, 1);
        v0 = addu(v0, a0);
        lhu(v1, v0, -6204);
        v0 = sll(v1, 4);
        v1 = subu(v0, v1);
        v0 = sll(v1, 2);
        v0 = subu(v0, v1);
        v1 = sll(v0, 2);
        lw(v0, gp, -18488);  // 0x7CE4B8
        s2 = addu(v0, v1);
        goto L_001d7a14;
    }
L_001d7a08:
    charge(ctx, 3);
    v0 = 0;
    // 0x001d7b48 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
    return;
L_001d7b28_32:
    charge(ctx, 3);
    s3 = a1;
    goto L_001d7b44;
}

// 0x001DA020 sub_1DA020 -- 9936 bytes; frame 0xD0: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// K_FldFrame_UpdateCtlTask's per-unit step (a0 a field unit, a1 / a2 its inputs): on fields below 200 the
// floor table 0x67EF00 and the triangle tests (K_FldFrame_IsPointInTriangle), two jump tables (0x7B6CB0 /
// 0x7B6C80) over the unit's modes; 9,936 bytes.
void sub_1DA020(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f20{ctx, 20};
    // 0x001da020
    enter(ctx, 31);  // entry check point + this block's cycles
    sp = addiu(sp, -0xD0);
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
    s4 = a0;
    s7 = a1;
    s3 = a2;
    lhu(s5, a0, 212);
    lhu(fp, a0, 214);
    a1 = 0;
    jal(ctx, 0x1DA068u, gen::fn_sub_318540_00318540);
    s0 = v0 & 0xFFFF;
    a0 = s4;
    a1 = 0;
    jal(ctx, 0x1DA07Cu, gen::fn_sub_318990_00318990);
    mov_s(f20, f0);
    lw(v1, gp, -22448);  // 0x7CD540
    lw(v1, v1, 0);
    at = slti(v1, 200);
    if (at != 0) {
        // 0x001da09c
        charge(ctx, 14);
        a0 = s4;
        jal(ctx, 0x1DA0A0u, gen::fn_sub_318B60_00318b60);
        s6 = addiu(v0, 48);
        a0 = 21;
        jal(ctx, 0x1DA0B0u, gen::fn_sub_3B5D50_003b5d50);
        s1 = v0;
        lw(v1, gp, -22448);  // 0x7CD540
        lw(a0, v1, 0);
        lw(a1, v1, 4);
        v1 = sltiu(a0, 20);
        if (v1 == 0) {
            // 0x001da0d4
            charge(ctx, 3);
            at = sltiu(a0, 29);
            if (at != 0) {
                // 0x001da0e0
                charge(ctx, 3);
                v1 = sltiu(a1, 50);
                if (v1 == 0) {
                    // 0x001da0ec
                    charge(ctx, 1);
                    a1 = addiu(a1, -49);
                }
            }
        }
        // 0x001da0f0
        charge(ctx, 7);
        a0 = sll(a0, 2);
        v1 = 0x680000;
        v1 = addiu(v1, -4352);  // &0x67EF00
        v1 = addu(v1, a0);
        lw(v1, v1, 0);
        if (v1 != 0) {
            // 0x001da118
            charge(ctx, 4);
            v1 = addu(v1, a1);
            lbu(s2, v1, 0);
            for (;;) {
                // 0x001da23c
                charge(ctx, 2);
                if (s1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001da128
                charge(ctx, 20);
                a2 = addiu(sp, 0xB0);
                v0 = 0x680000;
                ld(v1, v0, 15288);  // 0x683BB8
                v0 = 0x680000;
                lwc1(f0, v0, 15296);  // 0x683BC0
                sd(v1, sp, 0xB0);
                swc1(f0, sp, 0xB8);
                v0 = addiu(s1, 284);
                sw(v0, sp, 0xC0);
                v0 = addiu(s1, 296);
                sw(v0, sp, 0xC4);
                v0 = addiu(s1, 308);
                sw(v0, sp, 0xC8);
                a0 = s6;
                a1 = addiu(sp, 0xC0);
                jal(ctx, 0x1DA164u, gen::fn_K_FldFrame_IsPointInTriangle_001aaad0);
                v1 = 1;
                if (v0 == v1) {
                    // 0x001da178
                    charge(ctx, 10);
                    lw(v1, sp, 0xC0);
                    lwc1(f3, v1, 4);
                    lwc1(f2, s6, 4);
                    v1 = 0x42C80000;
                    mtc1(v1, f1);
                    add_s(f0, f1, f3);
                    c_lt_s(f2, f0);
                    if (!cond(ctx)) {
                        goto L_001da1bc;
                    }
                    // 0x001da1a0
                    charge(ctx, 4);
                    sub_s(f0, f3, f1);
                    c_le_s(f2, f0);
                    if (cond(ctx)) {
                        goto L_001da1bc;
                    }
                    goto L_001da1b0_11;
                }
            L_001da1bc:
                charge(ctx, 14);
                v0 = addiu(s1, 296);
                sw(v0, sp, 0xC0);
                v0 = addiu(s1, 308);
                sw(v0, sp, 0xC4);
                v0 = addiu(s1, 320);
                sw(v0, sp, 0xC8);
                a0 = s6;
                a1 = addiu(sp, 0xC0);
                a2 = addiu(sp, 0xB0);
                jal(ctx, 0x1DA1E0u, gen::fn_K_FldFrame_IsPointInTriangle_001aaad0);
                v1 = 1;
                if (v0 == v1) {
                    // 0x001da1f4
                    charge(ctx, 10);
                    lw(v1, sp, 0xC0);
                    lwc1(f3, v1, 4);
                    lwc1(f2, s6, 4);
                    v1 = 0x42C80000;
                    mtc1(v1, f1);
                    add_s(f0, f1, f3);
                    c_lt_s(f2, f0);
                    if (!cond(ctx)) {
                        goto L_001da238;
                    }
                    // 0x001da21c
                    charge(ctx, 4);
                    sub_s(f0, f3, f1);
                    c_le_s(f2, f0);
                    if (cond(ctx)) {
                        goto L_001da238;
                    }
                    goto L_001da22c_15;
                }
            L_001da238:
                charge(ctx, 1);
                lw(s1, s1, 248);
            }
        } else {
            // 0x001da10c
            charge(ctx, 3);
            s2 = 0;
        }
    L_001da244:
        charge(ctx, 4);
        s1 = s7 & 0xFFFF;
        at = sltiu(s1, 14);
        if (at != 0) {
            // 0x001da254
            charge(ctx, 7);
            a0 = 0x7B0000;
            a0 = addiu(a0, 27824);  // &0x7B6CB0
            v1 = sll(s1, 2);
            v1 = addu(v1, a0);
            lw(v1, v1, 0);
            switch (v1.u()) {
            case 0x1DA270u:  // table[1]
                // 0x001da270
                charge(ctx, 4);
                jal(ctx, 0x1DA270u, gen::fn_sub_17D800_0017d800);
                if (v0 != 0) {
                    // 0x001da818
                    charge(ctx, 4);
                    a0 = s5 & 0xFFFF;
                    v1 = 9;
                    if (a0 != v1) {
                        // 0x001da9ec
                        charge(ctx, 3);
                        v1 = 1;
                        if (a0 == v1) {
                            // 0x001da9f8
                            charge(ctx, 6);
                            s0 = s0 & 0xFFFF;
                            a0 = s1;
                            jal(ctx, 0x1DAA00u, gen::fn_sub_1DED40_001ded40);
                            if (s0 == v0) {
                                // 0x001daa10
                                charge(ctx, 6);
                                v1 = 0x40A00000;
                                mtc1(v1, f0);
                                c_le_s(f20, f0);
                                if (!cond(ctx)) {
                                    // 0x001daa28
                                    charge(ctx, 6);
                                    v1 = 0x40C00000;
                                    mtc1(v1, f0);
                                    c_lt_s(f20, f0);
                                    if (!cond(ctx)) {
                                        goto L_001daa40;
                                    }
                                L_001daa70:
                                    charge(ctx, 24);
                                    v0 = s3 & 0xFFFF;
                                    a0 = v0 & 0x3FF;
                                    v1 = sll(a0, 2);
                                    v0 = 0x870000;
                                    v0 = addiu(v0, 23120);  // &0x875A50
                                    s0 = addu(v0, v1);
                                    v0 = addiu(a0, 1);
                                    a1 = dsll32(v0, 16);
                                    a1 = dsra32(a1, 16);
                                    v1 = sll(s2, 2);
                                    lw(v0, s0, 0);
                                    v0 = addu(v1, v0);
                                    a3 = dsll32(v0, 16);
                                    a3 = dsra32(a3, 16);
                                    a0 = 0;
                                    a2 = 1;
                                    jal(ctx, 0x1DAAB0u, gen::fn_sub_10A4E0_0010a4e0);
                                    lw(v1, s0, 0);
                                    v1 = addiu(v1, 1);
                                    sw(v1, s0, 0);
                                    v1 = slti(v1, 4);
                                    if (v1 == 0) {
                                        // 0x001daad0
                                        charge(ctx, 3);
                                        sw(zero, s0, 0);
                                    }
                                    break;
                                }
                            L_001daa40:
                                charge(ctx, 6);
                                v1 = 0x41500000;
                                mtc1(v1, f0);
                                c_le_s(f20, f0);
                                if (!cond(ctx)) {
                                    // 0x001daa58
                                    charge(ctx, 6);
                                    v1 = 0x41600000;
                                    mtc1(v1, f0);
                                    c_lt_s(f20, f0);
                                    if (cond(ctx)) {
                                        goto L_001daa70;
                                    }
                                }
                            }
                        }
                    } else {
                        // 0x001da828
                        charge(ctx, 6);
                        s0 = s0 & 0xFFFF;
                        a0 = s1;
                        jal(ctx, 0x1DA830u, gen::fn_sub_1DE630_001de630);
                        if (s0 != v0) {
                            // 0x001da90c
                            charge(ctx, 5);
                            a0 = s1;
                            jal(ctx, 0x1DA910u, gen::fn_sub_1DED40_001ded40);
                            if (s0 == v0) {
                                // 0x001da920
                                charge(ctx, 6);
                                v1 = 0x40A00000;
                                mtc1(v1, f0);
                                c_le_s(f20, f0);
                                if (!cond(ctx)) {
                                    // 0x001da938
                                    charge(ctx, 6);
                                    v1 = 0x40C00000;
                                    mtc1(v1, f0);
                                    c_lt_s(f20, f0);
                                    if (!cond(ctx)) {
                                        goto L_001da950;
                                    }
                                L_001da980:
                                    charge(ctx, 24);
                                    v0 = s3 & 0xFFFF;
                                    a0 = v0 & 0x3FF;
                                    v1 = sll(a0, 2);
                                    v0 = 0x870000;
                                    v0 = addiu(v0, 23120);  // &0x875A50
                                    s0 = addu(v0, v1);
                                    v0 = addiu(a0, 1);
                                    a1 = dsll32(v0, 16);
                                    a1 = dsra32(a1, 16);
                                    v1 = sll(s2, 2);
                                    lw(v0, s0, 0);
                                    v0 = addu(v1, v0);
                                    a3 = dsll32(v0, 16);
                                    a3 = dsra32(a3, 16);
                                    a0 = 0;
                                    a2 = 1;
                                    jal(ctx, 0x1DA9C0u, gen::fn_sub_10A4E0_0010a4e0);
                                    lw(v1, s0, 0);
                                    v1 = addiu(v1, 1);
                                    sw(v1, s0, 0);
                                    v1 = slti(v1, 4);
                                    if (v1 == 0) {
                                        // 0x001da9e0
                                        charge(ctx, 3);
                                        sw(zero, s0, 0);
                                    }
                                    break;
                                }
                            L_001da950:
                                charge(ctx, 6);
                                v1 = 0x41500000;
                                mtc1(v1, f0);
                                c_le_s(f20, f0);
                                if (!cond(ctx)) {
                                    // 0x001da968
                                    charge(ctx, 6);
                                    v1 = 0x41600000;
                                    mtc1(v1, f0);
                                    c_lt_s(f20, f0);
                                    if (cond(ctx)) {
                                        goto L_001da980;
                                    }
                                }
                            }
                        } else {
                            // 0x001da840
                            charge(ctx, 6);
                            v1 = 0x41400000;
                            mtc1(v1, f0);
                            c_le_s(f20, f0);
                            if (!cond(ctx)) {
                                // 0x001da858
                                charge(ctx, 6);
                                v1 = 0x41500000;
                                mtc1(v1, f0);
                                c_lt_s(f20, f0);
                                if (!cond(ctx)) {
                                    goto L_001da870;
                                }
                            L_001da8a0:
                                charge(ctx, 24);
                                v0 = s3 & 0xFFFF;
                                a0 = v0 & 0x3FF;
                                v1 = sll(a0, 2);
                                v0 = 0x870000;
                                v0 = addiu(v0, 23120);  // &0x875A50
                                s0 = addu(v0, v1);
                                v0 = addiu(a0, 1);
                                a1 = dsll32(v0, 16);
                                a1 = dsra32(a1, 16);
                                v1 = sll(s2, 2);
                                lw(v0, s0, 0);
                                v0 = addu(v1, v0);
                                a3 = dsll32(v0, 16);
                                a3 = dsra32(a3, 16);
                                a0 = 0;
                                a2 = 1;
                                jal(ctx, 0x1DA8E0u, gen::fn_sub_10A4E0_0010a4e0);
                                lw(v1, s0, 0);
                                v1 = addiu(v1, 1);
                                sw(v1, s0, 0);
                                v1 = slti(v1, 4);
                                if (v1 == 0) {
                                    // 0x001da900
                                    charge(ctx, 3);
                                    sw(zero, s0, 0);
                                }
                                break;
                            }
                        L_001da870:
                            charge(ctx, 6);
                            v1 = 0x41C00000;
                            mtc1(v1, f0);
                            c_le_s(f20, f0);
                            if (!cond(ctx)) {
                                // 0x001da888
                                charge(ctx, 6);
                                v1 = 0x41C80000;
                                mtc1(v1, f0);
                                c_lt_s(f20, f0);
                                if (cond(ctx)) {
                                    goto L_001da8a0;
                                }
                            }
                        }
                    }
                } else {
                    // 0x001da280
                    charge(ctx, 4);
                    a0 = s5 & 0xFFFF;
                    v1 = 9;
                    if (a0 != v1) {
                        // 0x001da728
                        charge(ctx, 3);
                        v1 = 1;
                        if (a0 == v1) {
                            // 0x001da734
                            charge(ctx, 6);
                            s0 = s0 & 0xFFFF;
                            a0 = s1;
                            jal(ctx, 0x1DA73Cu, gen::fn_sub_1DED40_001ded40);
                            if (s0 == v0) {
                                // 0x001da74c
                                charge(ctx, 6);
                                v1 = 0x41000000;
                                mtc1(v1, f0);
                                c_le_s(f20, f0);
                                if (!cond(ctx)) {
                                    // 0x001da764
                                    charge(ctx, 6);
                                    v1 = 0x41100000;
                                    mtc1(v1, f0);
                                    c_lt_s(f20, f0);
                                    if (!cond(ctx)) {
                                        goto L_001da77c;
                                    }
                                L_001da7ac:
                                    charge(ctx, 24);
                                    v0 = s3 & 0xFFFF;
                                    a0 = v0 & 0x3FF;
                                    v1 = sll(a0, 2);
                                    v0 = 0x870000;
                                    v0 = addiu(v0, 23120);  // &0x875A50
                                    s0 = addu(v0, v1);
                                    v0 = addiu(a0, 1);
                                    a1 = dsll32(v0, 16);
                                    a1 = dsra32(a1, 16);
                                    v1 = sll(s2, 2);
                                    lw(v0, s0, 0);
                                    v0 = addu(v1, v0);
                                    a3 = dsll32(v0, 16);
                                    a3 = dsra32(a3, 16);
                                    a0 = 0;
                                    a2 = 1;
                                    jal(ctx, 0x1DA7ECu, gen::fn_sub_10A4E0_0010a4e0);
                                    lw(v1, s0, 0);
                                    v1 = addiu(v1, 1);
                                    sw(v1, s0, 0);
                                    v1 = slti(v1, 4);
                                    if (v1 == 0) {
                                        // 0x001da80c
                                        charge(ctx, 3);
                                        sw(zero, s0, 0);
                                    }
                                    break;
                                }
                            L_001da77c:
                                charge(ctx, 6);
                                v1 = 0x41900000;
                                mtc1(v1, f0);
                                c_le_s(f20, f0);
                                if (!cond(ctx)) {
                                    // 0x001da794
                                    charge(ctx, 6);
                                    v1 = 0x41980000;
                                    mtc1(v1, f0);
                                    c_lt_s(f20, f0);
                                    if (cond(ctx)) {
                                        goto L_001da7ac;
                                    }
                                }
                            }
                        }
                    } else {
                        // 0x001da290
                        charge(ctx, 4);
                        v1 = fp & 0xFF;
                        at = sltiu(v1, 9);
                        if (at != 0) {
                            // 0x001da2a0
                            charge(ctx, 7);
                            a0 = 0x7B0000;
                            a0 = addiu(a0, 27776);  // &0x7B6C80
                            v1 = sll(v1, 2);
                            v1 = addu(v1, a0);
                            lw(v1, v1, 0);
                            switch (v1.u()) {
                            case 0x1DA2BCu:  // table[0, 1, 2, 3, 5, 7, 8]
                                // 0x001da2bc
                                charge(ctx, 6);
                                s0 = s0 & 0xFFFF;
                                a0 = s1;
                                jal(ctx, 0x1DA2C4u, gen::fn_sub_1DE630_001de630);
                                if (s0 != v0) {
                                    // 0x001da3a0
                                    charge(ctx, 5);
                                    a0 = s1;
                                    jal(ctx, 0x1DA3A4u, gen::fn_sub_1DED40_001ded40);
                                    if (s0 == v0) {
                                        // 0x001da3b4
                                        charge(ctx, 6);
                                        v1 = 0x41000000;
                                        mtc1(v1, f0);
                                        c_le_s(f20, f0);
                                        if (!cond(ctx)) {
                                            // 0x001da3cc
                                            charge(ctx, 6);
                                            v1 = 0x41100000;
                                            mtc1(v1, f0);
                                            c_lt_s(f20, f0);
                                            if (!cond(ctx)) {
                                                goto L_001da3e4;
                                            }
                                        L_001da414:
                                            charge(ctx, 24);
                                            v0 = s3 & 0xFFFF;
                                            a0 = v0 & 0x3FF;
                                            v1 = sll(a0, 2);
                                            v0 = 0x870000;
                                            v0 = addiu(v0, 23120);  // &0x875A50
                                            s0 = addu(v0, v1);
                                            v0 = addiu(a0, 1);
                                            a1 = dsll32(v0, 16);
                                            a1 = dsra32(a1, 16);
                                            v1 = sll(s2, 2);
                                            lw(v0, s0, 0);
                                            v0 = addu(v1, v0);
                                            a3 = dsll32(v0, 16);
                                            a3 = dsra32(a3, 16);
                                            a0 = 0;
                                            a2 = 1;
                                            jal(ctx, 0x1DA454u, gen::fn_sub_10A4E0_0010a4e0);
                                            lw(v1, s0, 0);
                                            v1 = addiu(v1, 1);
                                            sw(v1, s0, 0);
                                            v1 = slti(v1, 4);
                                            if (v1 == 0) {
                                                // 0x001da474
                                                charge(ctx, 3);
                                                sw(zero, s0, 0);
                                            }
                                            break;
                                        }
                                    L_001da3e4:
                                        charge(ctx, 6);
                                        v1 = 0x41900000;
                                        mtc1(v1, f0);
                                        c_le_s(f20, f0);
                                        if (!cond(ctx)) {
                                            // 0x001da3fc
                                            charge(ctx, 6);
                                            v1 = 0x41980000;
                                            mtc1(v1, f0);
                                            c_lt_s(f20, f0);
                                            if (cond(ctx)) {
                                                goto L_001da414;
                                            }
                                        }
                                    }
                                } else {
                                    // 0x001da2d4
                                    charge(ctx, 6);
                                    v1 = 0x41200000;
                                    mtc1(v1, f0);
                                    c_le_s(f20, f0);
                                    if (!cond(ctx)) {
                                        // 0x001da2ec
                                        charge(ctx, 6);
                                        v1 = 0x41300000;
                                        mtc1(v1, f0);
                                        c_lt_s(f20, f0);
                                        if (!cond(ctx)) {
                                            goto L_001da304;
                                        }
                                    L_001da334:
                                        charge(ctx, 24);
                                        v0 = s3 & 0xFFFF;
                                        a0 = v0 & 0x3FF;
                                        v1 = sll(a0, 2);
                                        v0 = 0x870000;
                                        v0 = addiu(v0, 23120);  // &0x875A50
                                        s0 = addu(v0, v1);
                                        v0 = addiu(a0, 1);
                                        a1 = dsll32(v0, 16);
                                        a1 = dsra32(a1, 16);
                                        v1 = sll(s2, 2);
                                        lw(v0, s0, 0);
                                        v0 = addu(v1, v0);
                                        a3 = dsll32(v0, 16);
                                        a3 = dsra32(a3, 16);
                                        a0 = 0;
                                        a2 = 1;
                                        jal(ctx, 0x1DA374u, gen::fn_sub_10A4E0_0010a4e0);
                                        lw(v1, s0, 0);
                                        v1 = addiu(v1, 1);
                                        sw(v1, s0, 0);
                                        v1 = slti(v1, 4);
                                        if (v1 == 0) {
                                            // 0x001da394
                                            charge(ctx, 3);
                                            sw(zero, s0, 0);
                                        }
                                        break;
                                    }
                                L_001da304:
                                    charge(ctx, 6);
                                    v1 = 0x41C80000;
                                    mtc1(v1, f0);
                                    c_le_s(f20, f0);
                                    if (!cond(ctx)) {
                                        // 0x001da31c
                                        charge(ctx, 6);
                                        v1 = 0x41D00000;
                                        mtc1(v1, f0);
                                        c_lt_s(f20, f0);
                                        if (cond(ctx)) {
                                            goto L_001da334;
                                        }
                                    }
                                }
                                break;
                            case 0x1DA480u:  // table[4]
                                // 0x001da480
                                charge(ctx, 6);
                                s0 = s0 & 0xFFFF;
                                a0 = s1;
                                jal(ctx, 0x1DA488u, gen::fn_sub_1DE630_001de630);
                                if (s0 != v0) {
                                    // 0x001da564
                                    charge(ctx, 5);
                                    a0 = s1;
                                    jal(ctx, 0x1DA568u, gen::fn_sub_1DED40_001ded40);
                                    if (s0 == v0) {
                                        // 0x001da578
                                        charge(ctx, 6);
                                        v1 = 0x41000000;
                                        mtc1(v1, f0);
                                        c_le_s(f20, f0);
                                        if (!cond(ctx)) {
                                            // 0x001da590
                                            charge(ctx, 6);
                                            v1 = 0x41100000;
                                            mtc1(v1, f0);
                                            c_lt_s(f20, f0);
                                            if (!cond(ctx)) {
                                                goto L_001da5a8;
                                            }
                                        L_001da5d8:
                                            charge(ctx, 24);
                                            v0 = s3 & 0xFFFF;
                                            a0 = v0 & 0x3FF;
                                            v1 = sll(a0, 2);
                                            v0 = 0x870000;
                                            v0 = addiu(v0, 23120);  // &0x875A50
                                            s0 = addu(v0, v1);
                                            v0 = addiu(a0, 1);
                                            a1 = dsll32(v0, 16);
                                            a1 = dsra32(a1, 16);
                                            v1 = sll(s2, 2);
                                            lw(v0, s0, 0);
                                            v0 = addu(v1, v0);
                                            a3 = dsll32(v0, 16);
                                            a3 = dsra32(a3, 16);
                                            a0 = 0;
                                            a2 = 1;
                                            jal(ctx, 0x1DA618u, gen::fn_sub_10A4E0_0010a4e0);
                                            lw(v1, s0, 0);
                                            v1 = addiu(v1, 1);
                                            sw(v1, s0, 0);
                                            v1 = slti(v1, 4);
                                            if (v1 == 0) {
                                                // 0x001da638
                                                charge(ctx, 3);
                                                sw(zero, s0, 0);
                                            }
                                            break;
                                        }
                                    L_001da5a8:
                                        charge(ctx, 6);
                                        v1 = 0x41900000;
                                        mtc1(v1, f0);
                                        c_le_s(f20, f0);
                                        if (!cond(ctx)) {
                                            // 0x001da5c0
                                            charge(ctx, 6);
                                            v1 = 0x41980000;
                                            mtc1(v1, f0);
                                            c_lt_s(f20, f0);
                                            if (cond(ctx)) {
                                                goto L_001da5d8;
                                            }
                                        }
                                    }
                                } else {
                                    // 0x001da498
                                    charge(ctx, 6);
                                    v1 = 0x41000000;
                                    mtc1(v1, f0);
                                    c_le_s(f20, f0);
                                    if (!cond(ctx)) {
                                        // 0x001da4b0
                                        charge(ctx, 6);
                                        v1 = 0x41100000;
                                        mtc1(v1, f0);
                                        c_lt_s(f20, f0);
                                        if (!cond(ctx)) {
                                            goto L_001da4c8;
                                        }
                                    L_001da4f8:
                                        charge(ctx, 24);
                                        v0 = s3 & 0xFFFF;
                                        a0 = v0 & 0x3FF;
                                        v1 = sll(a0, 2);
                                        v0 = 0x870000;
                                        v0 = addiu(v0, 23120);  // &0x875A50
                                        s0 = addu(v0, v1);
                                        v0 = addiu(a0, 1);
                                        a1 = dsll32(v0, 16);
                                        a1 = dsra32(a1, 16);
                                        v1 = sll(s2, 2);
                                        lw(v0, s0, 0);
                                        v0 = addu(v1, v0);
                                        a3 = dsll32(v0, 16);
                                        a3 = dsra32(a3, 16);
                                        a0 = 0;
                                        a2 = 1;
                                        jal(ctx, 0x1DA538u, gen::fn_sub_10A4E0_0010a4e0);
                                        lw(v1, s0, 0);
                                        v1 = addiu(v1, 1);
                                        sw(v1, s0, 0);
                                        v1 = slti(v1, 4);
                                        if (v1 == 0) {
                                            // 0x001da558
                                            charge(ctx, 3);
                                            sw(zero, s0, 0);
                                        }
                                        break;
                                    }
                                L_001da4c8:
                                    charge(ctx, 6);
                                    v1 = 0x41B80000;
                                    mtc1(v1, f0);
                                    c_le_s(f20, f0);
                                    if (!cond(ctx)) {
                                        // 0x001da4e0
                                        charge(ctx, 6);
                                        v1 = 0x41C00000;
                                        mtc1(v1, f0);
                                        c_lt_s(f20, f0);
                                        if (cond(ctx)) {
                                            goto L_001da4f8;
                                        }
                                    }
                                }
                                break;
                            case 0x1DA644u:  // table[6]
                                // 0x001da644
                                charge(ctx, 6);
                                s0 = s0 & 0xFFFF;
                                a0 = s1;
                                jal(ctx, 0x1DA64Cu, gen::fn_sub_1DED40_001ded40);
                                if (s0 == v0) {
                                    // 0x001da65c
                                    charge(ctx, 6);
                                    v1 = 0x41100000;
                                    mtc1(v1, f0);
                                    c_le_s(f20, f0);
                                    if (!cond(ctx)) {
                                        // 0x001da674
                                        charge(ctx, 6);
                                        v1 = 0x41200000;
                                        mtc1(v1, f0);
                                        c_lt_s(f20, f0);
                                        if (!cond(ctx)) {
                                            goto L_001da68c;
                                        }
                                    L_001da6bc:
                                        charge(ctx, 24);
                                        v0 = s3 & 0xFFFF;
                                        a0 = v0 & 0x3FF;
                                        v1 = sll(a0, 2);
                                        v0 = 0x870000;
                                        v0 = addiu(v0, 23120);  // &0x875A50
                                        s0 = addu(v0, v1);
                                        v0 = addiu(a0, 1);
                                        a1 = dsll32(v0, 16);
                                        a1 = dsra32(a1, 16);
                                        v1 = sll(s2, 2);
                                        lw(v0, s0, 0);
                                        v0 = addu(v1, v0);
                                        a3 = dsll32(v0, 16);
                                        a3 = dsra32(a3, 16);
                                        a0 = 0;
                                        a2 = 1;
                                        jal(ctx, 0x1DA6FCu, gen::fn_sub_10A4E0_0010a4e0);
                                        lw(v1, s0, 0);
                                        v1 = addiu(v1, 1);
                                        sw(v1, s0, 0);
                                        v1 = slti(v1, 4);
                                        if (v1 == 0) {
                                            // 0x001da71c
                                            charge(ctx, 3);
                                            sw(zero, s0, 0);
                                        }
                                        break;
                                    }
                                L_001da68c:
                                    charge(ctx, 6);
                                    v1 = 0x41980000;
                                    mtc1(v1, f0);
                                    c_le_s(f20, f0);
                                    if (!cond(ctx)) {
                                        // 0x001da6a4
                                        charge(ctx, 6);
                                        v1 = 0x41A00000;
                                        mtc1(v1, f0);
                                        c_lt_s(f20, f0);
                                        if (cond(ctx)) {
                                            goto L_001da6bc;
                                        }
                                    }
                                }
                                break;
                            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                                tail(ctx, v1.u());
                                return;
                            }
                        }
                    }
                }
                break;
            case 0x1DAADCu:  // table[2]
                // 0x001daadc
                charge(ctx, 4);
                a0 = s5 & 0xFFFF;
                v1 = 9;
                if (a0 != v1) {
                    // 0x001dabd0
                    charge(ctx, 3);
                    v1 = 1;
                    if (a0 == v1) {
                        // 0x001dabdc
                        charge(ctx, 16);
                        a0 = s4;
                        jal(ctx, 0x1DABE0u, gen::fn_sub_318B60_00318b60);
                        s4 = v0;
                        v0 = 0x870000;
                        lw(a0, v0, 6128);  // 0x8717F0
                        jal(ctx, 0x1DABF4u, gen::fn_sub_318B60_00318b60);
                        v1 = 0x44C80000;
                        mtc1(v1, f12);
                        a0 = addiu(s4, 48);
                        a1 = addiu(v0, 48);
                        jal(ctx, 0x1DAC0Cu, gen::fn_sub_1C71F0_001c71f0);
                        if (v0 != 0) {
                            // 0x001dac1c
                            charge(ctx, 6);
                            s0 = s0 & 0xFFFF;
                            a0 = s1;
                            jal(ctx, 0x1DAC24u, gen::fn_sub_1DED40_001ded40);
                            if (s0 == v0) {
                                // 0x001dac34
                                charge(ctx, 6);
                                v1 = 0x41000000;
                                mtc1(v1, f0);
                                c_le_s(f20, f0);
                                if (!cond(ctx)) {
                                    // 0x001dac4c
                                    charge(ctx, 6);
                                    v1 = 0x41100000;
                                    mtc1(v1, f0);
                                    c_lt_s(f20, f0);
                                    if (!cond(ctx)) {
                                        goto L_001dac64;
                                    }
                                L_001dac94:
                                    charge(ctx, 24);
                                    v0 = s3 & 0xFFFF;
                                    a0 = v0 & 0x3FF;
                                    v1 = sll(a0, 2);
                                    v0 = 0x870000;
                                    v0 = addiu(v0, 23120);  // &0x875A50
                                    s0 = addu(v0, v1);
                                    v0 = addiu(a0, 1);
                                    a1 = dsll32(v0, 16);
                                    a1 = dsra32(a1, 16);
                                    v1 = sll(s2, 2);
                                    lw(v0, s0, 0);
                                    v0 = addu(v1, v0);
                                    a3 = dsll32(v0, 16);
                                    a3 = dsra32(a3, 16);
                                    a0 = 0;
                                    a2 = 5;
                                    jal(ctx, 0x1DACD4u, gen::fn_sub_10A4E0_0010a4e0);
                                    lw(v1, s0, 0);
                                    v1 = addiu(v1, 1);
                                    sw(v1, s0, 0);
                                    v1 = slti(v1, 4);
                                    if (v1 == 0) {
                                        // 0x001dacf4
                                        charge(ctx, 3);
                                        sw(zero, s0, 0);
                                    }
                                    break;
                                }
                            L_001dac64:
                                charge(ctx, 6);
                                v1 = 0x41900000;
                                mtc1(v1, f0);
                                c_le_s(f20, f0);
                                if (!cond(ctx)) {
                                    // 0x001dac7c
                                    charge(ctx, 6);
                                    v1 = 0x41980000;
                                    mtc1(v1, f0);
                                    c_lt_s(f20, f0);
                                    if (cond(ctx)) {
                                        goto L_001dac94;
                                    }
                                }
                            }
                        }
                    }
                } else {
                    // 0x001daaec
                    charge(ctx, 6);
                    s0 = s0 & 0xFFFF;
                    a0 = s1;
                    jal(ctx, 0x1DAAF4u, gen::fn_sub_1DED40_001ded40);
                    if (s0 == v0) {
                        // 0x001dab04
                        charge(ctx, 6);
                        v1 = 0x41000000;
                        mtc1(v1, f0);
                        c_le_s(f20, f0);
                        if (!cond(ctx)) {
                            // 0x001dab1c
                            charge(ctx, 6);
                            v1 = 0x41100000;
                            mtc1(v1, f0);
                            c_lt_s(f20, f0);
                            if (!cond(ctx)) {
                                goto L_001dab34;
                            }
                        L_001dab64:
                            charge(ctx, 24);
                            v0 = s3 & 0xFFFF;
                            a0 = v0 & 0x3FF;
                            v1 = sll(a0, 2);
                            v0 = 0x870000;
                            v0 = addiu(v0, 23120);  // &0x875A50
                            s0 = addu(v0, v1);
                            v0 = addiu(a0, 1);
                            a1 = dsll32(v0, 16);
                            a1 = dsra32(a1, 16);
                            v1 = sll(s2, 2);
                            lw(v0, s0, 0);
                            v0 = addu(v1, v0);
                            a3 = dsll32(v0, 16);
                            a3 = dsra32(a3, 16);
                            a0 = 0;
                            a2 = 5;
                            jal(ctx, 0x1DABA4u, gen::fn_sub_10A4E0_0010a4e0);
                            lw(v1, s0, 0);
                            v1 = addiu(v1, 1);
                            sw(v1, s0, 0);
                            v1 = slti(v1, 4);
                            if (v1 == 0) {
                                // 0x001dabc4
                                charge(ctx, 3);
                                sw(zero, s0, 0);
                            }
                            break;
                        }
                    L_001dab34:
                        charge(ctx, 6);
                        v1 = 0x41900000;
                        mtc1(v1, f0);
                        c_le_s(f20, f0);
                        if (!cond(ctx)) {
                            // 0x001dab4c
                            charge(ctx, 6);
                            v1 = 0x41980000;
                            mtc1(v1, f0);
                            c_lt_s(f20, f0);
                            if (cond(ctx)) {
                                goto L_001dab64;
                            }
                        }
                    }
                }
                break;
            case 0x1DAD00u:  // table[3]
                // 0x001dad00
                charge(ctx, 4);
                a0 = s5 & 0xFFFF;
                v1 = 9;
                if (a0 != v1) {
                    // 0x001dadf4
                    charge(ctx, 3);
                    v1 = 1;
                    if (a0 == v1) {
                        // 0x001dae00
                        charge(ctx, 16);
                        a0 = s4;
                        jal(ctx, 0x1DAE04u, gen::fn_sub_318B60_00318b60);
                        s4 = v0;
                        v0 = 0x870000;
                        lw(a0, v0, 6128);  // 0x8717F0
                        jal(ctx, 0x1DAE18u, gen::fn_sub_318B60_00318b60);
                        v1 = 0x44C80000;
                        mtc1(v1, f12);
                        a0 = addiu(s4, 48);
                        a1 = addiu(v0, 48);
                        jal(ctx, 0x1DAE30u, gen::fn_sub_1C71F0_001c71f0);
                        if (v0 != 0) {
                            // 0x001dae40
                            charge(ctx, 6);
                            s0 = s0 & 0xFFFF;
                            a0 = s1;
                            jal(ctx, 0x1DAE48u, gen::fn_sub_1DED40_001ded40);
                            if (s0 == v0) {
                                // 0x001dae58
                                charge(ctx, 6);
                                v1 = 0x41000000;
                                mtc1(v1, f0);
                                c_le_s(f20, f0);
                                if (!cond(ctx)) {
                                    // 0x001dae70
                                    charge(ctx, 6);
                                    v1 = 0x41100000;
                                    mtc1(v1, f0);
                                    c_lt_s(f20, f0);
                                    if (!cond(ctx)) {
                                        goto L_001dae88;
                                    }
                                L_001daeb8:
                                    charge(ctx, 24);
                                    v0 = s3 & 0xFFFF;
                                    a0 = v0 & 0x3FF;
                                    v1 = sll(a0, 2);
                                    v0 = 0x870000;
                                    v0 = addiu(v0, 23120);  // &0x875A50
                                    s0 = addu(v0, v1);
                                    v0 = addiu(a0, 1);
                                    a1 = dsll32(v0, 16);
                                    a1 = dsra32(a1, 16);
                                    v1 = sll(s2, 2);
                                    lw(v0, s0, 0);
                                    v0 = addu(v1, v0);
                                    a3 = dsll32(v0, 16);
                                    a3 = dsra32(a3, 16);
                                    a0 = 0;
                                    a2 = 5;
                                    jal(ctx, 0x1DAEF8u, gen::fn_sub_10A4E0_0010a4e0);
                                    lw(v1, s0, 0);
                                    v1 = addiu(v1, 1);
                                    sw(v1, s0, 0);
                                    v1 = slti(v1, 4);
                                    if (v1 == 0) {
                                        // 0x001daf18
                                        charge(ctx, 3);
                                        sw(zero, s0, 0);
                                    }
                                    break;
                                }
                            L_001dae88:
                                charge(ctx, 6);
                                v1 = 0x41900000;
                                mtc1(v1, f0);
                                c_le_s(f20, f0);
                                if (!cond(ctx)) {
                                    // 0x001daea0
                                    charge(ctx, 6);
                                    v1 = 0x41980000;
                                    mtc1(v1, f0);
                                    c_lt_s(f20, f0);
                                    if (cond(ctx)) {
                                        goto L_001daeb8;
                                    }
                                }
                            }
                        }
                    }
                } else {
                    // 0x001dad10
                    charge(ctx, 6);
                    s0 = s0 & 0xFFFF;
                    a0 = s1;
                    jal(ctx, 0x1DAD18u, gen::fn_sub_1DED40_001ded40);
                    if (s0 == v0) {
                        // 0x001dad28
                        charge(ctx, 6);
                        v1 = 0x41000000;
                        mtc1(v1, f0);
                        c_le_s(f20, f0);
                        if (!cond(ctx)) {
                            // 0x001dad40
                            charge(ctx, 6);
                            v1 = 0x41100000;
                            mtc1(v1, f0);
                            c_lt_s(f20, f0);
                            if (!cond(ctx)) {
                                goto L_001dad58;
                            }
                        L_001dad88:
                            charge(ctx, 24);
                            v0 = s3 & 0xFFFF;
                            a0 = v0 & 0x3FF;
                            v1 = sll(a0, 2);
                            v0 = 0x870000;
                            v0 = addiu(v0, 23120);  // &0x875A50
                            s0 = addu(v0, v1);
                            v0 = addiu(a0, 1);
                            a1 = dsll32(v0, 16);
                            a1 = dsra32(a1, 16);
                            v1 = sll(s2, 2);
                            lw(v0, s0, 0);
                            v0 = addu(v1, v0);
                            a3 = dsll32(v0, 16);
                            a3 = dsra32(a3, 16);
                            a0 = 0;
                            a2 = 5;
                            jal(ctx, 0x1DADC8u, gen::fn_sub_10A4E0_0010a4e0);
                            lw(v1, s0, 0);
                            v1 = addiu(v1, 1);
                            sw(v1, s0, 0);
                            v1 = slti(v1, 4);
                            if (v1 == 0) {
                                // 0x001dade8
                                charge(ctx, 3);
                                sw(zero, s0, 0);
                            }
                            break;
                        }
                    L_001dad58:
                        charge(ctx, 6);
                        v1 = 0x41900000;
                        mtc1(v1, f0);
                        c_le_s(f20, f0);
                        if (!cond(ctx)) {
                            // 0x001dad70
                            charge(ctx, 6);
                            v1 = 0x41980000;
                            mtc1(v1, f0);
                            c_lt_s(f20, f0);
                            if (cond(ctx)) {
                                goto L_001dad88;
                            }
                        }
                    }
                }
                break;
            case 0x1DAF24u:  // table[4]
                // 0x001daf24
                charge(ctx, 4);
                a0 = s5 & 0xFFFF;
                v1 = 9;
                if (a0 != v1) {
                    // 0x001db018
                    charge(ctx, 3);
                    v1 = 1;
                    if (a0 == v1) {
                        // 0x001db024
                        charge(ctx, 16);
                        a0 = s4;
                        jal(ctx, 0x1DB028u, gen::fn_sub_318B60_00318b60);
                        s4 = v0;
                        v0 = 0x870000;
                        lw(a0, v0, 6128);  // 0x8717F0
                        jal(ctx, 0x1DB03Cu, gen::fn_sub_318B60_00318b60);
                        v1 = 0x44C80000;
                        mtc1(v1, f12);
                        a0 = addiu(s4, 48);
                        a1 = addiu(v0, 48);
                        jal(ctx, 0x1DB054u, gen::fn_sub_1C71F0_001c71f0);
                        if (v0 != 0) {
                            // 0x001db064
                            charge(ctx, 6);
                            s0 = s0 & 0xFFFF;
                            a0 = s1;
                            jal(ctx, 0x1DB06Cu, gen::fn_sub_1DED40_001ded40);
                            if (s0 == v0) {
                                // 0x001db07c
                                charge(ctx, 6);
                                v1 = 0x41000000;
                                mtc1(v1, f0);
                                c_le_s(f20, f0);
                                if (!cond(ctx)) {
                                    // 0x001db094
                                    charge(ctx, 6);
                                    v1 = 0x41100000;
                                    mtc1(v1, f0);
                                    c_lt_s(f20, f0);
                                    if (!cond(ctx)) {
                                        goto L_001db0ac;
                                    }
                                L_001db0dc:
                                    charge(ctx, 24);
                                    v0 = s3 & 0xFFFF;
                                    a0 = v0 & 0x3FF;
                                    v1 = sll(a0, 2);
                                    v0 = 0x870000;
                                    v0 = addiu(v0, 23120);  // &0x875A50
                                    s0 = addu(v0, v1);
                                    v0 = addiu(a0, 1);
                                    a1 = dsll32(v0, 16);
                                    a1 = dsra32(a1, 16);
                                    v1 = sll(s2, 2);
                                    lw(v0, s0, 0);
                                    v0 = addu(v1, v0);
                                    a3 = dsll32(v0, 16);
                                    a3 = dsra32(a3, 16);
                                    a0 = 0;
                                    a2 = 5;
                                    jal(ctx, 0x1DB11Cu, gen::fn_sub_10A4E0_0010a4e0);
                                    lw(v1, s0, 0);
                                    v1 = addiu(v1, 1);
                                    sw(v1, s0, 0);
                                    v1 = slti(v1, 4);
                                    if (v1 == 0) {
                                        // 0x001db13c
                                        charge(ctx, 3);
                                        sw(zero, s0, 0);
                                    }
                                    break;
                                }
                            L_001db0ac:
                                charge(ctx, 6);
                                v1 = 0x41900000;
                                mtc1(v1, f0);
                                c_le_s(f20, f0);
                                if (!cond(ctx)) {
                                    // 0x001db0c4
                                    charge(ctx, 6);
                                    v1 = 0x41980000;
                                    mtc1(v1, f0);
                                    c_lt_s(f20, f0);
                                    if (cond(ctx)) {
                                        goto L_001db0dc;
                                    }
                                }
                            }
                        }
                    }
                } else {
                    // 0x001daf34
                    charge(ctx, 6);
                    s0 = s0 & 0xFFFF;
                    a0 = s1;
                    jal(ctx, 0x1DAF3Cu, gen::fn_sub_1DED40_001ded40);
                    if (s0 == v0) {
                        // 0x001daf4c
                        charge(ctx, 6);
                        v1 = 0x41000000;
                        mtc1(v1, f0);
                        c_le_s(f20, f0);
                        if (!cond(ctx)) {
                            // 0x001daf64
                            charge(ctx, 6);
                            v1 = 0x41100000;
                            mtc1(v1, f0);
                            c_lt_s(f20, f0);
                            if (!cond(ctx)) {
                                goto L_001daf7c;
                            }
                        L_001dafac:
                            charge(ctx, 24);
                            v0 = s3 & 0xFFFF;
                            a0 = v0 & 0x3FF;
                            v1 = sll(a0, 2);
                            v0 = 0x870000;
                            v0 = addiu(v0, 23120);  // &0x875A50
                            s0 = addu(v0, v1);
                            v0 = addiu(a0, 1);
                            a1 = dsll32(v0, 16);
                            a1 = dsra32(a1, 16);
                            v1 = sll(s2, 2);
                            lw(v0, s0, 0);
                            v0 = addu(v1, v0);
                            a3 = dsll32(v0, 16);
                            a3 = dsra32(a3, 16);
                            a0 = 0;
                            a2 = 5;
                            jal(ctx, 0x1DAFECu, gen::fn_sub_10A4E0_0010a4e0);
                            lw(v1, s0, 0);
                            v1 = addiu(v1, 1);
                            sw(v1, s0, 0);
                            v1 = slti(v1, 4);
                            if (v1 == 0) {
                                // 0x001db00c
                                charge(ctx, 3);
                                sw(zero, s0, 0);
                            }
                            break;
                        }
                    L_001daf7c:
                        charge(ctx, 6);
                        v1 = 0x41900000;
                        mtc1(v1, f0);
                        c_le_s(f20, f0);
                        if (!cond(ctx)) {
                            // 0x001daf94
                            charge(ctx, 6);
                            v1 = 0x41980000;
                            mtc1(v1, f0);
                            c_lt_s(f20, f0);
                            if (cond(ctx)) {
                                goto L_001dafac;
                            }
                        }
                    }
                }
                break;
            case 0x1DB148u:  // table[5]
                // 0x001db148
                charge(ctx, 4);
                a0 = s5 & 0xFFFF;
                v1 = 9;
                if (a0 != v1) {
                    // 0x001db23c
                    charge(ctx, 3);
                    v1 = 1;
                    if (a0 == v1) {
                        // 0x001db248
                        charge(ctx, 16);
                        a0 = s4;
                        jal(ctx, 0x1DB24Cu, gen::fn_sub_318B60_00318b60);
                        s4 = v0;
                        v0 = 0x870000;
                        lw(a0, v0, 6128);  // 0x8717F0
                        jal(ctx, 0x1DB260u, gen::fn_sub_318B60_00318b60);
                        v1 = 0x44C80000;
                        mtc1(v1, f12);
                        a0 = addiu(s4, 48);
                        a1 = addiu(v0, 48);
                        jal(ctx, 0x1DB278u, gen::fn_sub_1C71F0_001c71f0);
                        if (v0 != 0) {
                            // 0x001db288
                            charge(ctx, 6);
                            s0 = s0 & 0xFFFF;
                            a0 = s1;
                            jal(ctx, 0x1DB290u, gen::fn_sub_1DED40_001ded40);
                            if (s0 == v0) {
                                // 0x001db2a0
                                charge(ctx, 6);
                                v1 = 0x41000000;
                                mtc1(v1, f0);
                                c_le_s(f20, f0);
                                if (!cond(ctx)) {
                                    // 0x001db2b8
                                    charge(ctx, 6);
                                    v1 = 0x41100000;
                                    mtc1(v1, f0);
                                    c_lt_s(f20, f0);
                                    if (!cond(ctx)) {
                                        goto L_001db2d0;
                                    }
                                L_001db300:
                                    charge(ctx, 24);
                                    v0 = s3 & 0xFFFF;
                                    a0 = v0 & 0x3FF;
                                    v1 = sll(a0, 2);
                                    v0 = 0x870000;
                                    v0 = addiu(v0, 23120);  // &0x875A50
                                    s0 = addu(v0, v1);
                                    v0 = addiu(a0, 1);
                                    a1 = dsll32(v0, 16);
                                    a1 = dsra32(a1, 16);
                                    v1 = sll(s2, 2);
                                    lw(v0, s0, 0);
                                    v0 = addu(v1, v0);
                                    a3 = dsll32(v0, 16);
                                    a3 = dsra32(a3, 16);
                                    a0 = 0;
                                    a2 = 5;
                                    jal(ctx, 0x1DB340u, gen::fn_sub_10A4E0_0010a4e0);
                                    lw(v1, s0, 0);
                                    v1 = addiu(v1, 1);
                                    sw(v1, s0, 0);
                                    v1 = slti(v1, 4);
                                    if (v1 == 0) {
                                        // 0x001db360
                                        charge(ctx, 3);
                                        sw(zero, s0, 0);
                                    }
                                    break;
                                }
                            L_001db2d0:
                                charge(ctx, 6);
                                v1 = 0x41900000;
                                mtc1(v1, f0);
                                c_le_s(f20, f0);
                                if (!cond(ctx)) {
                                    // 0x001db2e8
                                    charge(ctx, 6);
                                    v1 = 0x41980000;
                                    mtc1(v1, f0);
                                    c_lt_s(f20, f0);
                                    if (cond(ctx)) {
                                        goto L_001db300;
                                    }
                                }
                            }
                        }
                    }
                } else {
                    // 0x001db158
                    charge(ctx, 6);
                    s0 = s0 & 0xFFFF;
                    a0 = s1;
                    jal(ctx, 0x1DB160u, gen::fn_sub_1DED40_001ded40);
                    if (s0 == v0) {
                        // 0x001db170
                        charge(ctx, 6);
                        v1 = 0x41000000;
                        mtc1(v1, f0);
                        c_le_s(f20, f0);
                        if (!cond(ctx)) {
                            // 0x001db188
                            charge(ctx, 6);
                            v1 = 0x41100000;
                            mtc1(v1, f0);
                            c_lt_s(f20, f0);
                            if (!cond(ctx)) {
                                goto L_001db1a0;
                            }
                        L_001db1d0:
                            charge(ctx, 24);
                            v0 = s3 & 0xFFFF;
                            a0 = v0 & 0x3FF;
                            v1 = sll(a0, 2);
                            v0 = 0x870000;
                            v0 = addiu(v0, 23120);  // &0x875A50
                            s0 = addu(v0, v1);
                            v0 = addiu(a0, 1);
                            a1 = dsll32(v0, 16);
                            a1 = dsra32(a1, 16);
                            v1 = sll(s2, 2);
                            lw(v0, s0, 0);
                            v0 = addu(v1, v0);
                            a3 = dsll32(v0, 16);
                            a3 = dsra32(a3, 16);
                            a0 = 0;
                            a2 = 5;
                            jal(ctx, 0x1DB210u, gen::fn_sub_10A4E0_0010a4e0);
                            lw(v1, s0, 0);
                            v1 = addiu(v1, 1);
                            sw(v1, s0, 0);
                            v1 = slti(v1, 4);
                            if (v1 == 0) {
                                // 0x001db230
                                charge(ctx, 3);
                                sw(zero, s0, 0);
                            }
                            break;
                        }
                    L_001db1a0:
                        charge(ctx, 6);
                        v1 = 0x41900000;
                        mtc1(v1, f0);
                        c_le_s(f20, f0);
                        if (!cond(ctx)) {
                            // 0x001db1b8
                            charge(ctx, 6);
                            v1 = 0x41980000;
                            mtc1(v1, f0);
                            c_lt_s(f20, f0);
                            if (cond(ctx)) {
                                goto L_001db1d0;
                            }
                        }
                    }
                }
                break;
            case 0x1DB36Cu:  // table[6]
                // 0x001db36c
                charge(ctx, 4);
                a0 = s5 & 0xFFFF;
                v1 = 9;
                if (a0 != v1) {
                    // 0x001db460
                    charge(ctx, 3);
                    v1 = 1;
                    if (a0 == v1) {
                        // 0x001db46c
                        charge(ctx, 16);
                        a0 = s4;
                        jal(ctx, 0x1DB470u, gen::fn_sub_318B60_00318b60);
                        s4 = v0;
                        v0 = 0x870000;
                        lw(a0, v0, 6128);  // 0x8717F0
                        jal(ctx, 0x1DB484u, gen::fn_sub_318B60_00318b60);
                        v1 = 0x44C80000;
                        mtc1(v1, f12);
                        a0 = addiu(s4, 48);
                        a1 = addiu(v0, 48);
                        jal(ctx, 0x1DB49Cu, gen::fn_sub_1C71F0_001c71f0);
                        if (v0 != 0) {
                            // 0x001db4ac
                            charge(ctx, 6);
                            s0 = s0 & 0xFFFF;
                            a0 = s1;
                            jal(ctx, 0x1DB4B4u, gen::fn_sub_1DED40_001ded40);
                            if (s0 == v0) {
                                // 0x001db4c4
                                charge(ctx, 6);
                                v1 = 0x41000000;
                                mtc1(v1, f0);
                                c_le_s(f20, f0);
                                if (!cond(ctx)) {
                                    // 0x001db4dc
                                    charge(ctx, 6);
                                    v1 = 0x41100000;
                                    mtc1(v1, f0);
                                    c_lt_s(f20, f0);
                                    if (!cond(ctx)) {
                                        goto L_001db4f4;
                                    }
                                L_001db524:
                                    charge(ctx, 24);
                                    v0 = s3 & 0xFFFF;
                                    a0 = v0 & 0x3FF;
                                    v1 = sll(a0, 2);
                                    v0 = 0x870000;
                                    v0 = addiu(v0, 23120);  // &0x875A50
                                    s0 = addu(v0, v1);
                                    v0 = addiu(a0, 1);
                                    a1 = dsll32(v0, 16);
                                    a1 = dsra32(a1, 16);
                                    v1 = sll(s2, 2);
                                    lw(v0, s0, 0);
                                    v0 = addu(v1, v0);
                                    a3 = dsll32(v0, 16);
                                    a3 = dsra32(a3, 16);
                                    a0 = 0;
                                    a2 = 5;
                                    jal(ctx, 0x1DB564u, gen::fn_sub_10A4E0_0010a4e0);
                                    lw(v1, s0, 0);
                                    v1 = addiu(v1, 1);
                                    sw(v1, s0, 0);
                                    v1 = slti(v1, 4);
                                    if (v1 == 0) {
                                        // 0x001db584
                                        charge(ctx, 3);
                                        sw(zero, s0, 0);
                                    }
                                    break;
                                }
                            L_001db4f4:
                                charge(ctx, 6);
                                v1 = 0x41900000;
                                mtc1(v1, f0);
                                c_le_s(f20, f0);
                                if (!cond(ctx)) {
                                    // 0x001db50c
                                    charge(ctx, 6);
                                    v1 = 0x41980000;
                                    mtc1(v1, f0);
                                    c_lt_s(f20, f0);
                                    if (cond(ctx)) {
                                        goto L_001db524;
                                    }
                                }
                            }
                        }
                    }
                } else {
                    // 0x001db37c
                    charge(ctx, 6);
                    s0 = s0 & 0xFFFF;
                    a0 = s1;
                    jal(ctx, 0x1DB384u, gen::fn_sub_1DED40_001ded40);
                    if (s0 == v0) {
                        // 0x001db394
                        charge(ctx, 6);
                        v1 = 0x41000000;
                        mtc1(v1, f0);
                        c_le_s(f20, f0);
                        if (!cond(ctx)) {
                            // 0x001db3ac
                            charge(ctx, 6);
                            v1 = 0x41100000;
                            mtc1(v1, f0);
                            c_lt_s(f20, f0);
                            if (!cond(ctx)) {
                                goto L_001db3c4;
                            }
                        L_001db3f4:
                            charge(ctx, 24);
                            v0 = s3 & 0xFFFF;
                            a0 = v0 & 0x3FF;
                            v1 = sll(a0, 2);
                            v0 = 0x870000;
                            v0 = addiu(v0, 23120);  // &0x875A50
                            s0 = addu(v0, v1);
                            v0 = addiu(a0, 1);
                            a1 = dsll32(v0, 16);
                            a1 = dsra32(a1, 16);
                            v1 = sll(s2, 2);
                            lw(v0, s0, 0);
                            v0 = addu(v1, v0);
                            a3 = dsll32(v0, 16);
                            a3 = dsra32(a3, 16);
                            a0 = 0;
                            a2 = 5;
                            jal(ctx, 0x1DB434u, gen::fn_sub_10A4E0_0010a4e0);
                            lw(v1, s0, 0);
                            v1 = addiu(v1, 1);
                            sw(v1, s0, 0);
                            v1 = slti(v1, 4);
                            if (v1 == 0) {
                                // 0x001db454
                                charge(ctx, 3);
                                sw(zero, s0, 0);
                            }
                            break;
                        }
                    L_001db3c4:
                        charge(ctx, 6);
                        v1 = 0x41900000;
                        mtc1(v1, f0);
                        c_le_s(f20, f0);
                        if (!cond(ctx)) {
                            // 0x001db3dc
                            charge(ctx, 6);
                            v1 = 0x41980000;
                            mtc1(v1, f0);
                            c_lt_s(f20, f0);
                            if (cond(ctx)) {
                                goto L_001db3f4;
                            }
                        }
                    }
                }
                break;
            case 0x1DB590u:  // table[7]
                // 0x001db590
                charge(ctx, 4);
                a0 = s5 & 0xFFFF;
                v1 = 9;
                if (a0 != v1) {
                    // 0x001db684
                    charge(ctx, 3);
                    v1 = 1;
                    if (a0 == v1) {
                        // 0x001db690
                        charge(ctx, 16);
                        a0 = s4;
                        jal(ctx, 0x1DB694u, gen::fn_sub_318B60_00318b60);
                        s4 = v0;
                        v0 = 0x870000;
                        lw(a0, v0, 6128);  // 0x8717F0
                        jal(ctx, 0x1DB6A8u, gen::fn_sub_318B60_00318b60);
                        v1 = 0x44C80000;
                        mtc1(v1, f12);
                        a0 = addiu(s4, 48);
                        a1 = addiu(v0, 48);
                        jal(ctx, 0x1DB6C0u, gen::fn_sub_1C71F0_001c71f0);
                        if (v0 != 0) {
                            // 0x001db6d0
                            charge(ctx, 6);
                            s0 = s0 & 0xFFFF;
                            a0 = s1;
                            jal(ctx, 0x1DB6D8u, gen::fn_sub_1DED40_001ded40);
                            if (s0 == v0) {
                                // 0x001db6e8
                                charge(ctx, 6);
                                v1 = 0x41000000;
                                mtc1(v1, f0);
                                c_le_s(f20, f0);
                                if (!cond(ctx)) {
                                    // 0x001db700
                                    charge(ctx, 6);
                                    v1 = 0x41100000;
                                    mtc1(v1, f0);
                                    c_lt_s(f20, f0);
                                    if (!cond(ctx)) {
                                        goto L_001db718;
                                    }
                                L_001db748:
                                    charge(ctx, 24);
                                    v0 = s3 & 0xFFFF;
                                    a0 = v0 & 0x3FF;
                                    v1 = sll(a0, 2);
                                    v0 = 0x870000;
                                    v0 = addiu(v0, 23120);  // &0x875A50
                                    s0 = addu(v0, v1);
                                    v0 = addiu(a0, 1);
                                    a1 = dsll32(v0, 16);
                                    a1 = dsra32(a1, 16);
                                    v1 = sll(s2, 2);
                                    lw(v0, s0, 0);
                                    v0 = addu(v1, v0);
                                    a3 = dsll32(v0, 16);
                                    a3 = dsra32(a3, 16);
                                    a0 = 0;
                                    a2 = 5;
                                    jal(ctx, 0x1DB788u, gen::fn_sub_10A4E0_0010a4e0);
                                    lw(v1, s0, 0);
                                    v1 = addiu(v1, 1);
                                    sw(v1, s0, 0);
                                    v1 = slti(v1, 4);
                                    if (v1 == 0) {
                                        // 0x001db7a8
                                        charge(ctx, 3);
                                        sw(zero, s0, 0);
                                    }
                                    break;
                                }
                            L_001db718:
                                charge(ctx, 6);
                                v1 = 0x41900000;
                                mtc1(v1, f0);
                                c_le_s(f20, f0);
                                if (!cond(ctx)) {
                                    // 0x001db730
                                    charge(ctx, 6);
                                    v1 = 0x41980000;
                                    mtc1(v1, f0);
                                    c_lt_s(f20, f0);
                                    if (cond(ctx)) {
                                        goto L_001db748;
                                    }
                                }
                            }
                        }
                    }
                } else {
                    // 0x001db5a0
                    charge(ctx, 6);
                    s0 = s0 & 0xFFFF;
                    a0 = s1;
                    jal(ctx, 0x1DB5A8u, gen::fn_sub_1DED40_001ded40);
                    if (s0 == v0) {
                        // 0x001db5b8
                        charge(ctx, 6);
                        v1 = 0x41000000;
                        mtc1(v1, f0);
                        c_le_s(f20, f0);
                        if (!cond(ctx)) {
                            // 0x001db5d0
                            charge(ctx, 6);
                            v1 = 0x41100000;
                            mtc1(v1, f0);
                            c_lt_s(f20, f0);
                            if (!cond(ctx)) {
                                goto L_001db5e8;
                            }
                        L_001db618:
                            charge(ctx, 24);
                            v0 = s3 & 0xFFFF;
                            a0 = v0 & 0x3FF;
                            v1 = sll(a0, 2);
                            v0 = 0x870000;
                            v0 = addiu(v0, 23120);  // &0x875A50
                            s0 = addu(v0, v1);
                            v0 = addiu(a0, 1);
                            a1 = dsll32(v0, 16);
                            a1 = dsra32(a1, 16);
                            v1 = sll(s2, 2);
                            lw(v0, s0, 0);
                            v0 = addu(v1, v0);
                            a3 = dsll32(v0, 16);
                            a3 = dsra32(a3, 16);
                            a0 = 0;
                            a2 = 5;
                            jal(ctx, 0x1DB658u, gen::fn_sub_10A4E0_0010a4e0);
                            lw(v1, s0, 0);
                            v1 = addiu(v1, 1);
                            sw(v1, s0, 0);
                            v1 = slti(v1, 4);
                            if (v1 == 0) {
                                // 0x001db678
                                charge(ctx, 3);
                                sw(zero, s0, 0);
                            }
                            break;
                        }
                    L_001db5e8:
                        charge(ctx, 6);
                        v1 = 0x41900000;
                        mtc1(v1, f0);
                        c_le_s(f20, f0);
                        if (!cond(ctx)) {
                            // 0x001db600
                            charge(ctx, 6);
                            v1 = 0x41980000;
                            mtc1(v1, f0);
                            c_lt_s(f20, f0);
                            if (cond(ctx)) {
                                goto L_001db618;
                            }
                        }
                    }
                }
                break;
            case 0x1DB7B4u:  // table[8]
                // 0x001db7b4
                charge(ctx, 4);
                a0 = s5 & 0xFFFF;
                v1 = 9;
                if (a0 != v1) {
                    // 0x001db8a8
                    charge(ctx, 3);
                    v1 = 1;
                    if (a0 == v1) {
                        // 0x001db8b4
                        charge(ctx, 16);
                        a0 = s4;
                        jal(ctx, 0x1DB8B8u, gen::fn_sub_318B60_00318b60);
                        s4 = v0;
                        v0 = 0x870000;
                        lw(a0, v0, 6128);  // 0x8717F0
                        jal(ctx, 0x1DB8CCu, gen::fn_sub_318B60_00318b60);
                        v1 = 0x44C80000;
                        mtc1(v1, f12);
                        a0 = addiu(s4, 48);
                        a1 = addiu(v0, 48);
                        jal(ctx, 0x1DB8E4u, gen::fn_sub_1C71F0_001c71f0);
                        if (v0 != 0) {
                            // 0x001db8f4
                            charge(ctx, 6);
                            s0 = s0 & 0xFFFF;
                            a0 = s1;
                            jal(ctx, 0x1DB8FCu, gen::fn_sub_1DED40_001ded40);
                            if (s0 == v0) {
                                // 0x001db90c
                                charge(ctx, 6);
                                v1 = 0x40C00000;
                                mtc1(v1, f0);
                                c_le_s(f20, f0);
                                if (!cond(ctx)) {
                                    // 0x001db924
                                    charge(ctx, 6);
                                    v1 = 0x40E00000;
                                    mtc1(v1, f0);
                                    c_lt_s(f20, f0);
                                    if (!cond(ctx)) {
                                        goto L_001db93c;
                                    }
                                L_001db96c:
                                    charge(ctx, 24);
                                    v0 = s3 & 0xFFFF;
                                    a0 = v0 & 0x3FF;
                                    v1 = sll(a0, 2);
                                    v0 = 0x870000;
                                    v0 = addiu(v0, 23120);  // &0x875A50
                                    s0 = addu(v0, v1);
                                    v0 = addiu(a0, 1);
                                    a1 = dsll32(v0, 16);
                                    a1 = dsra32(a1, 16);
                                    v1 = sll(s2, 2);
                                    lw(v0, s0, 0);
                                    v0 = addu(v1, v0);
                                    a3 = dsll32(v0, 16);
                                    a3 = dsra32(a3, 16);
                                    a0 = 0;
                                    a2 = 5;
                                    jal(ctx, 0x1DB9ACu, gen::fn_sub_10A4E0_0010a4e0);
                                    lw(v1, s0, 0);
                                    v1 = addiu(v1, 1);
                                    sw(v1, s0, 0);
                                    v1 = slti(v1, 4);
                                    if (v1 == 0) {
                                        // 0x001db9cc
                                        charge(ctx, 3);
                                        sw(zero, s0, 0);
                                    }
                                    break;
                                }
                            L_001db93c:
                                charge(ctx, 6);
                                v1 = 0x41600000;
                                mtc1(v1, f0);
                                c_le_s(f20, f0);
                                if (!cond(ctx)) {
                                    // 0x001db954
                                    charge(ctx, 6);
                                    v1 = 0x41700000;
                                    mtc1(v1, f0);
                                    c_lt_s(f20, f0);
                                    if (cond(ctx)) {
                                        goto L_001db96c;
                                    }
                                }
                            }
                        }
                    }
                } else {
                    // 0x001db7c4
                    charge(ctx, 6);
                    s0 = s0 & 0xFFFF;
                    a0 = s1;
                    jal(ctx, 0x1DB7CCu, gen::fn_sub_1DED40_001ded40);
                    if (s0 == v0) {
                        // 0x001db7dc
                        charge(ctx, 6);
                        v1 = 0x40C00000;
                        mtc1(v1, f0);
                        c_le_s(f20, f0);
                        if (!cond(ctx)) {
                            // 0x001db7f4
                            charge(ctx, 6);
                            v1 = 0x40E00000;
                            mtc1(v1, f0);
                            c_lt_s(f20, f0);
                            if (!cond(ctx)) {
                                goto L_001db80c;
                            }
                        L_001db83c:
                            charge(ctx, 24);
                            v0 = s3 & 0xFFFF;
                            a0 = v0 & 0x3FF;
                            v1 = sll(a0, 2);
                            v0 = 0x870000;
                            v0 = addiu(v0, 23120);  // &0x875A50
                            s0 = addu(v0, v1);
                            v0 = addiu(a0, 1);
                            a1 = dsll32(v0, 16);
                            a1 = dsra32(a1, 16);
                            v1 = sll(s2, 2);
                            lw(v0, s0, 0);
                            v0 = addu(v1, v0);
                            a3 = dsll32(v0, 16);
                            a3 = dsra32(a3, 16);
                            a0 = 0;
                            a2 = 5;
                            jal(ctx, 0x1DB87Cu, gen::fn_sub_10A4E0_0010a4e0);
                            lw(v1, s0, 0);
                            v1 = addiu(v1, 1);
                            sw(v1, s0, 0);
                            v1 = slti(v1, 4);
                            if (v1 == 0) {
                                // 0x001db89c
                                charge(ctx, 3);
                                sw(zero, s0, 0);
                            }
                            break;
                        }
                    L_001db80c:
                        charge(ctx, 6);
                        v1 = 0x41600000;
                        mtc1(v1, f0);
                        c_le_s(f20, f0);
                        if (!cond(ctx)) {
                            // 0x001db824
                            charge(ctx, 6);
                            v1 = 0x41700000;
                            mtc1(v1, f0);
                            c_lt_s(f20, f0);
                            if (cond(ctx)) {
                                goto L_001db83c;
                            }
                        }
                    }
                }
                break;
            case 0x1DB9D8u:  // table[9]
                // 0x001db9d8
                charge(ctx, 4);
                jal(ctx, 0x1DB9D8u, gen::fn_sub_17D800_0017d800);
                if (v0 != 0) {
                    // 0x001dbc0c
                    charge(ctx, 4);
                    a0 = s5 & 0xFFFF;
                    v1 = 9;
                    if (a0 != v1) {
                        // 0x001dbd00
                        charge(ctx, 3);
                        v1 = 1;
                        if (a0 == v1) {
                            // 0x001dbd0c
                            charge(ctx, 16);
                            a0 = s4;
                            jal(ctx, 0x1DBD10u, gen::fn_sub_318B60_00318b60);
                            s4 = v0;
                            v0 = 0x870000;
                            lw(a0, v0, 6128);  // 0x8717F0
                            jal(ctx, 0x1DBD24u, gen::fn_sub_318B60_00318b60);
                            v1 = 0x44C80000;
                            mtc1(v1, f12);
                            a0 = addiu(s4, 48);
                            a1 = addiu(v0, 48);
                            jal(ctx, 0x1DBD3Cu, gen::fn_sub_1C71F0_001c71f0);
                            if (v0 != 0) {
                                // 0x001dbd4c
                                charge(ctx, 6);
                                s0 = s0 & 0xFFFF;
                                a0 = s1;
                                jal(ctx, 0x1DBD54u, gen::fn_sub_1DED40_001ded40);
                                if (s0 == v0) {
                                    // 0x001dbd64
                                    charge(ctx, 6);
                                    v1 = 0x40C00000;
                                    mtc1(v1, f0);
                                    c_le_s(f20, f0);
                                    if (!cond(ctx)) {
                                        // 0x001dbd7c
                                        charge(ctx, 6);
                                        v1 = 0x40E00000;
                                        mtc1(v1, f0);
                                        c_lt_s(f20, f0);
                                        if (!cond(ctx)) {
                                            goto L_001dbd94;
                                        }
                                    L_001dbdc4:
                                        charge(ctx, 24);
                                        v0 = s3 & 0xFFFF;
                                        a0 = v0 & 0x3FF;
                                        v1 = sll(a0, 2);
                                        v0 = 0x870000;
                                        v0 = addiu(v0, 23120);  // &0x875A50
                                        s0 = addu(v0, v1);
                                        v0 = addiu(a0, 1);
                                        a1 = dsll32(v0, 16);
                                        a1 = dsra32(a1, 16);
                                        v1 = sll(s2, 2);
                                        lw(v0, s0, 0);
                                        v0 = addu(v1, v0);
                                        a3 = dsll32(v0, 16);
                                        a3 = dsra32(a3, 16);
                                        a0 = 0;
                                        a2 = 5;
                                        jal(ctx, 0x1DBE04u, gen::fn_sub_10A4E0_0010a4e0);
                                        lw(v1, s0, 0);
                                        v1 = addiu(v1, 1);
                                        sw(v1, s0, 0);
                                        v1 = slti(v1, 4);
                                        if (v1 == 0) {
                                            // 0x001dbe24
                                            charge(ctx, 3);
                                            sw(zero, s0, 0);
                                        }
                                        break;
                                    }
                                L_001dbd94:
                                    charge(ctx, 6);
                                    v1 = 0x41600000;
                                    mtc1(v1, f0);
                                    c_le_s(f20, f0);
                                    if (!cond(ctx)) {
                                        // 0x001dbdac
                                        charge(ctx, 6);
                                        v1 = 0x41700000;
                                        mtc1(v1, f0);
                                        c_lt_s(f20, f0);
                                        if (cond(ctx)) {
                                            goto L_001dbdc4;
                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        // 0x001dbc1c
                        charge(ctx, 6);
                        s0 = s0 & 0xFFFF;
                        a0 = s1;
                        jal(ctx, 0x1DBC24u, gen::fn_sub_1DED40_001ded40);
                        if (s0 == v0) {
                            // 0x001dbc34
                            charge(ctx, 6);
                            v1 = 0x41000000;
                            mtc1(v1, f0);
                            c_le_s(f20, f0);
                            if (!cond(ctx)) {
                                // 0x001dbc4c
                                charge(ctx, 6);
                                v1 = 0x41100000;
                                mtc1(v1, f0);
                                c_lt_s(f20, f0);
                                if (!cond(ctx)) {
                                    goto L_001dbc64;
                                }
                            L_001dbc94:
                                charge(ctx, 24);
                                v0 = s3 & 0xFFFF;
                                a0 = v0 & 0x3FF;
                                v1 = sll(a0, 2);
                                v0 = 0x870000;
                                v0 = addiu(v0, 23120);  // &0x875A50
                                s0 = addu(v0, v1);
                                v0 = addiu(a0, 1);
                                a1 = dsll32(v0, 16);
                                a1 = dsra32(a1, 16);
                                v1 = sll(s2, 2);
                                lw(v0, s0, 0);
                                v0 = addu(v1, v0);
                                a3 = dsll32(v0, 16);
                                a3 = dsra32(a3, 16);
                                a0 = 0;
                                a2 = 5;
                                jal(ctx, 0x1DBCD4u, gen::fn_sub_10A4E0_0010a4e0);
                                lw(v1, s0, 0);
                                v1 = addiu(v1, 1);
                                sw(v1, s0, 0);
                                v1 = slti(v1, 4);
                                if (v1 == 0) {
                                    // 0x001dbcf4
                                    charge(ctx, 3);
                                    sw(zero, s0, 0);
                                }
                                break;
                            }
                        L_001dbc64:
                            charge(ctx, 6);
                            v1 = 0x41900000;
                            mtc1(v1, f0);
                            c_le_s(f20, f0);
                            if (!cond(ctx)) {
                                // 0x001dbc7c
                                charge(ctx, 6);
                                v1 = 0x41980000;
                                mtc1(v1, f0);
                                c_lt_s(f20, f0);
                                if (cond(ctx)) {
                                    goto L_001dbc94;
                                }
                            }
                        }
                    }
                } else {
                    // 0x001db9e8
                    charge(ctx, 4);
                    a0 = s5 & 0xFFFF;
                    v1 = 9;
                    if (a0 != v1) {
                        // 0x001dbadc
                        charge(ctx, 3);
                        v1 = 1;
                        if (a0 == v1) {
                            // 0x001dbae8
                            charge(ctx, 16);
                            a0 = s4;
                            jal(ctx, 0x1DBAECu, gen::fn_sub_318B60_00318b60);
                            s4 = v0;
                            v0 = 0x870000;
                            lw(a0, v0, 6128);  // 0x8717F0
                            jal(ctx, 0x1DBB00u, gen::fn_sub_318B60_00318b60);
                            v1 = 0x44C80000;
                            mtc1(v1, f12);
                            a0 = addiu(s4, 48);
                            a1 = addiu(v0, 48);
                            jal(ctx, 0x1DBB18u, gen::fn_sub_1C71F0_001c71f0);
                            if (v0 != 0) {
                                // 0x001dbb28
                                charge(ctx, 6);
                                s0 = s0 & 0xFFFF;
                                a0 = s1;
                                jal(ctx, 0x1DBB30u, gen::fn_sub_1DED40_001ded40);
                                if (s0 == v0) {
                                    // 0x001dbb40
                                    charge(ctx, 6);
                                    v1 = 0x41000000;
                                    mtc1(v1, f0);
                                    c_le_s(f20, f0);
                                    if (!cond(ctx)) {
                                        // 0x001dbb58
                                        charge(ctx, 6);
                                        v1 = 0x41100000;
                                        mtc1(v1, f0);
                                        c_lt_s(f20, f0);
                                        if (!cond(ctx)) {
                                            goto L_001dbb70;
                                        }
                                    L_001dbba0:
                                        charge(ctx, 24);
                                        v0 = s3 & 0xFFFF;
                                        a0 = v0 & 0x3FF;
                                        v1 = sll(a0, 2);
                                        v0 = 0x870000;
                                        v0 = addiu(v0, 23120);  // &0x875A50
                                        s0 = addu(v0, v1);
                                        v0 = addiu(a0, 1);
                                        a1 = dsll32(v0, 16);
                                        a1 = dsra32(a1, 16);
                                        v1 = sll(s2, 2);
                                        lw(v0, s0, 0);
                                        v0 = addu(v1, v0);
                                        a3 = dsll32(v0, 16);
                                        a3 = dsra32(a3, 16);
                                        a0 = 0;
                                        a2 = 5;
                                        jal(ctx, 0x1DBBE0u, gen::fn_sub_10A4E0_0010a4e0);
                                        lw(v1, s0, 0);
                                        v1 = addiu(v1, 1);
                                        sw(v1, s0, 0);
                                        v1 = slti(v1, 4);
                                        if (v1 == 0) {
                                            // 0x001dbc00
                                            charge(ctx, 3);
                                            sw(zero, s0, 0);
                                        }
                                        break;
                                    }
                                L_001dbb70:
                                    charge(ctx, 6);
                                    v1 = 0x41900000;
                                    mtc1(v1, f0);
                                    c_le_s(f20, f0);
                                    if (!cond(ctx)) {
                                        // 0x001dbb88
                                        charge(ctx, 6);
                                        v1 = 0x41980000;
                                        mtc1(v1, f0);
                                        c_lt_s(f20, f0);
                                        if (cond(ctx)) {
                                            goto L_001dbba0;
                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        // 0x001db9f8
                        charge(ctx, 6);
                        s0 = s0 & 0xFFFF;
                        a0 = s1;
                        jal(ctx, 0x1DBA00u, gen::fn_sub_1DED40_001ded40);
                        if (s0 == v0) {
                            // 0x001dba10
                            charge(ctx, 6);
                            v1 = 0x41000000;
                            mtc1(v1, f0);
                            c_le_s(f20, f0);
                            if (!cond(ctx)) {
                                // 0x001dba28
                                charge(ctx, 6);
                                v1 = 0x41100000;
                                mtc1(v1, f0);
                                c_lt_s(f20, f0);
                                if (!cond(ctx)) {
                                    goto L_001dba40;
                                }
                            L_001dba70:
                                charge(ctx, 24);
                                v0 = s3 & 0xFFFF;
                                a0 = v0 & 0x3FF;
                                v1 = sll(a0, 2);
                                v0 = 0x870000;
                                v0 = addiu(v0, 23120);  // &0x875A50
                                s0 = addu(v0, v1);
                                v0 = addiu(a0, 1);
                                a1 = dsll32(v0, 16);
                                a1 = dsra32(a1, 16);
                                v1 = sll(s2, 2);
                                lw(v0, s0, 0);
                                v0 = addu(v1, v0);
                                a3 = dsll32(v0, 16);
                                a3 = dsra32(a3, 16);
                                a0 = 0;
                                a2 = 5;
                                jal(ctx, 0x1DBAB0u, gen::fn_sub_10A4E0_0010a4e0);
                                lw(v1, s0, 0);
                                v1 = addiu(v1, 1);
                                sw(v1, s0, 0);
                                v1 = slti(v1, 4);
                                if (v1 == 0) {
                                    // 0x001dbad0
                                    charge(ctx, 3);
                                    sw(zero, s0, 0);
                                }
                                break;
                            }
                        L_001dba40:
                            charge(ctx, 6);
                            v1 = 0x41900000;
                            mtc1(v1, f0);
                            c_le_s(f20, f0);
                            if (!cond(ctx)) {
                                // 0x001dba58
                                charge(ctx, 6);
                                v1 = 0x41980000;
                                mtc1(v1, f0);
                                c_lt_s(f20, f0);
                                if (cond(ctx)) {
                                    goto L_001dba70;
                                }
                            }
                        }
                    }
                }
                break;
            case 0x1DBE30u:  // table[10]
                // 0x001dbe30
                charge(ctx, 4);
                a0 = s5 & 0xFFFF;
                v1 = 9;
                if (a0 != v1) {
                    // 0x001dbf24
                    charge(ctx, 3);
                    v1 = 1;
                    if (a0 == v1) {
                        // 0x001dbf30
                        charge(ctx, 16);
                        a0 = s4;
                        jal(ctx, 0x1DBF34u, gen::fn_sub_318B60_00318b60);
                        s4 = v0;
                        v0 = 0x870000;
                        lw(a0, v0, 6128);  // 0x8717F0
                        jal(ctx, 0x1DBF48u, gen::fn_sub_318B60_00318b60);
                        v1 = 0x44C80000;
                        mtc1(v1, f12);
                        a0 = addiu(s4, 48);
                        a1 = addiu(v0, 48);
                        jal(ctx, 0x1DBF60u, gen::fn_sub_1C71F0_001c71f0);
                        if (v0 != 0) {
                            // 0x001dbf70
                            charge(ctx, 6);
                            s0 = s0 & 0xFFFF;
                            a0 = s1;
                            jal(ctx, 0x1DBF78u, gen::fn_sub_1DED40_001ded40);
                            if (s0 == v0) {
                                // 0x001dbf88
                                charge(ctx, 6);
                                v1 = 0x41000000;
                                mtc1(v1, f0);
                                c_le_s(f20, f0);
                                if (!cond(ctx)) {
                                    // 0x001dbfa0
                                    charge(ctx, 6);
                                    v1 = 0x41100000;
                                    mtc1(v1, f0);
                                    c_lt_s(f20, f0);
                                    if (!cond(ctx)) {
                                        goto L_001dbfb8;
                                    }
                                L_001dbfe8:
                                    charge(ctx, 24);
                                    v0 = s3 & 0xFFFF;
                                    a0 = v0 & 0x3FF;
                                    v1 = sll(a0, 2);
                                    v0 = 0x870000;
                                    v0 = addiu(v0, 23120);  // &0x875A50
                                    s0 = addu(v0, v1);
                                    v0 = addiu(a0, 1);
                                    a1 = dsll32(v0, 16);
                                    a1 = dsra32(a1, 16);
                                    v1 = sll(s2, 2);
                                    lw(v0, s0, 0);
                                    v0 = addu(v1, v0);
                                    a3 = dsll32(v0, 16);
                                    a3 = dsra32(a3, 16);
                                    a0 = 0;
                                    a2 = 5;
                                    jal(ctx, 0x1DC028u, gen::fn_sub_10A4E0_0010a4e0);
                                    lw(v1, s0, 0);
                                    v1 = addiu(v1, 1);
                                    sw(v1, s0, 0);
                                    v1 = slti(v1, 4);
                                    if (v1 == 0) {
                                        // 0x001dc048
                                        charge(ctx, 3);
                                        sw(zero, s0, 0);
                                    }
                                    break;
                                }
                            L_001dbfb8:
                                charge(ctx, 6);
                                v1 = 0x41900000;
                                mtc1(v1, f0);
                                c_le_s(f20, f0);
                                if (!cond(ctx)) {
                                    // 0x001dbfd0
                                    charge(ctx, 6);
                                    v1 = 0x41980000;
                                    mtc1(v1, f0);
                                    c_lt_s(f20, f0);
                                    if (cond(ctx)) {
                                        goto L_001dbfe8;
                                    }
                                }
                            }
                        }
                    }
                } else {
                    // 0x001dbe40
                    charge(ctx, 6);
                    s0 = s0 & 0xFFFF;
                    a0 = s1;
                    jal(ctx, 0x1DBE48u, gen::fn_sub_1DED40_001ded40);
                    if (s0 == v0) {
                        // 0x001dbe58
                        charge(ctx, 6);
                        v1 = 0x41000000;
                        mtc1(v1, f0);
                        c_le_s(f20, f0);
                        if (!cond(ctx)) {
                            // 0x001dbe70
                            charge(ctx, 6);
                            v1 = 0x41100000;
                            mtc1(v1, f0);
                            c_lt_s(f20, f0);
                            if (!cond(ctx)) {
                                goto L_001dbe88;
                            }
                        L_001dbeb8:
                            charge(ctx, 24);
                            v0 = s3 & 0xFFFF;
                            a0 = v0 & 0x3FF;
                            v1 = sll(a0, 2);
                            v0 = 0x870000;
                            v0 = addiu(v0, 23120);  // &0x875A50
                            s0 = addu(v0, v1);
                            v0 = addiu(a0, 1);
                            a1 = dsll32(v0, 16);
                            a1 = dsra32(a1, 16);
                            v1 = sll(s2, 2);
                            lw(v0, s0, 0);
                            v0 = addu(v1, v0);
                            a3 = dsll32(v0, 16);
                            a3 = dsra32(a3, 16);
                            a0 = 0;
                            a2 = 5;
                            jal(ctx, 0x1DBEF8u, gen::fn_sub_10A4E0_0010a4e0);
                            lw(v1, s0, 0);
                            v1 = addiu(v1, 1);
                            sw(v1, s0, 0);
                            v1 = slti(v1, 4);
                            if (v1 == 0) {
                                // 0x001dbf18
                                charge(ctx, 3);
                                sw(zero, s0, 0);
                            }
                            break;
                        }
                    L_001dbe88:
                        charge(ctx, 6);
                        v1 = 0x41900000;
                        mtc1(v1, f0);
                        c_le_s(f20, f0);
                        if (!cond(ctx)) {
                            // 0x001dbea0
                            charge(ctx, 6);
                            v1 = 0x41980000;
                            mtc1(v1, f0);
                            c_lt_s(f20, f0);
                            if (cond(ctx)) {
                                goto L_001dbeb8;
                            }
                        }
                    }
                }
                break;
            case 0x1DC054u:  // table[11]
                // 0x001dc054
                charge(ctx, 4);
                a0 = s5 & 0xFFFF;
                v1 = 9;
                if (a0 != v1) {
                    // 0x001dc148
                    charge(ctx, 3);
                    v1 = 1;
                    if (a0 == v1) {
                        // 0x001dc154
                        charge(ctx, 16);
                        a0 = s4;
                        jal(ctx, 0x1DC158u, gen::fn_sub_318B60_00318b60);
                        s4 = v0;
                        v0 = 0x870000;
                        lw(a0, v0, 6128);  // 0x8717F0
                        jal(ctx, 0x1DC16Cu, gen::fn_sub_318B60_00318b60);
                        v1 = 0x44C80000;
                        mtc1(v1, f12);
                        a0 = addiu(s4, 48);
                        a1 = addiu(v0, 48);
                        jal(ctx, 0x1DC184u, gen::fn_sub_1C71F0_001c71f0);
                        if (v0 != 0) {
                            // 0x001dc194
                            charge(ctx, 6);
                            s0 = s0 & 0xFFFF;
                            a0 = s1;
                            jal(ctx, 0x1DC19Cu, gen::fn_sub_1DED40_001ded40);
                            if (s0 == v0) {
                                // 0x001dc1ac
                                charge(ctx, 6);
                                v1 = 0x41000000;
                                mtc1(v1, f0);
                                c_le_s(f20, f0);
                                if (!cond(ctx)) {
                                    // 0x001dc1c4
                                    charge(ctx, 6);
                                    v1 = 0x41100000;
                                    mtc1(v1, f0);
                                    c_lt_s(f20, f0);
                                    if (!cond(ctx)) {
                                        goto L_001dc1dc;
                                    }
                                L_001dc20c:
                                    charge(ctx, 24);
                                    v0 = s3 & 0xFFFF;
                                    a0 = v0 & 0x3FF;
                                    v1 = sll(a0, 2);
                                    v0 = 0x870000;
                                    v0 = addiu(v0, 23120);  // &0x875A50
                                    s0 = addu(v0, v1);
                                    v0 = addiu(a0, 1);
                                    a1 = dsll32(v0, 16);
                                    a1 = dsra32(a1, 16);
                                    v1 = sll(s2, 2);
                                    lw(v0, s0, 0);
                                    v0 = addu(v1, v0);
                                    a3 = dsll32(v0, 16);
                                    a3 = dsra32(a3, 16);
                                    a0 = 0;
                                    a2 = 5;
                                    jal(ctx, 0x1DC24Cu, gen::fn_sub_10A4E0_0010a4e0);
                                    lw(v1, s0, 0);
                                    v1 = addiu(v1, 1);
                                    sw(v1, s0, 0);
                                    v1 = slti(v1, 4);
                                    if (v1 == 0) {
                                        // 0x001dc26c
                                        charge(ctx, 3);
                                        sw(zero, s0, 0);
                                    }
                                    break;
                                }
                            L_001dc1dc:
                                charge(ctx, 6);
                                v1 = 0x41900000;
                                mtc1(v1, f0);
                                c_le_s(f20, f0);
                                if (!cond(ctx)) {
                                    // 0x001dc1f4
                                    charge(ctx, 6);
                                    v1 = 0x41980000;
                                    mtc1(v1, f0);
                                    c_lt_s(f20, f0);
                                    if (cond(ctx)) {
                                        goto L_001dc20c;
                                    }
                                }
                            }
                        }
                    }
                } else {
                    // 0x001dc064
                    charge(ctx, 6);
                    s0 = s0 & 0xFFFF;
                    a0 = s1;
                    jal(ctx, 0x1DC06Cu, gen::fn_sub_1DED40_001ded40);
                    if (s0 == v0) {
                        // 0x001dc07c
                        charge(ctx, 6);
                        v1 = 0x41000000;
                        mtc1(v1, f0);
                        c_le_s(f20, f0);
                        if (!cond(ctx)) {
                            // 0x001dc094
                            charge(ctx, 6);
                            v1 = 0x41100000;
                            mtc1(v1, f0);
                            c_lt_s(f20, f0);
                            if (!cond(ctx)) {
                                goto L_001dc0ac;
                            }
                        L_001dc0dc:
                            charge(ctx, 24);
                            v0 = s3 & 0xFFFF;
                            a0 = v0 & 0x3FF;
                            v1 = sll(a0, 2);
                            v0 = 0x870000;
                            v0 = addiu(v0, 23120);  // &0x875A50
                            s0 = addu(v0, v1);
                            v0 = addiu(a0, 1);
                            a1 = dsll32(v0, 16);
                            a1 = dsra32(a1, 16);
                            v1 = sll(s2, 2);
                            lw(v0, s0, 0);
                            v0 = addu(v1, v0);
                            a3 = dsll32(v0, 16);
                            a3 = dsra32(a3, 16);
                            a0 = 0;
                            a2 = 5;
                            jal(ctx, 0x1DC11Cu, gen::fn_sub_10A4E0_0010a4e0);
                            lw(v1, s0, 0);
                            v1 = addiu(v1, 1);
                            sw(v1, s0, 0);
                            v1 = slti(v1, 4);
                            if (v1 == 0) {
                                // 0x001dc13c
                                charge(ctx, 3);
                                sw(zero, s0, 0);
                            }
                            break;
                        }
                    L_001dc0ac:
                        charge(ctx, 6);
                        v1 = 0x41900000;
                        mtc1(v1, f0);
                        c_le_s(f20, f0);
                        if (!cond(ctx)) {
                            // 0x001dc0c4
                            charge(ctx, 6);
                            v1 = 0x41980000;
                            mtc1(v1, f0);
                            c_lt_s(f20, f0);
                            if (cond(ctx)) {
                                goto L_001dc0dc;
                            }
                        }
                    }
                }
                break;
            case 0x1DC278u:  // table[12]
                // 0x001dc278
                charge(ctx, 4);
                a0 = s5 & 0xFFFF;
                v1 = 9;
                if (a0 != v1) {
                    // 0x001dc36c
                    charge(ctx, 3);
                    v1 = 1;
                    if (a0 == v1) {
                        // 0x001dc378
                        charge(ctx, 16);
                        a0 = s4;
                        jal(ctx, 0x1DC37Cu, gen::fn_sub_318B60_00318b60);
                        s4 = v0;
                        v0 = 0x870000;
                        lw(a0, v0, 6128);  // 0x8717F0
                        jal(ctx, 0x1DC390u, gen::fn_sub_318B60_00318b60);
                        v1 = 0x44C80000;
                        mtc1(v1, f12);
                        a0 = addiu(s4, 48);
                        a1 = addiu(v0, 48);
                        jal(ctx, 0x1DC3A8u, gen::fn_sub_1C71F0_001c71f0);
                        if (v0 != 0) {
                            // 0x001dc3b8
                            charge(ctx, 6);
                            s0 = s0 & 0xFFFF;
                            a0 = s1;
                            jal(ctx, 0x1DC3C0u, gen::fn_sub_1DED40_001ded40);
                            if (s0 == v0) {
                                // 0x001dc3d0
                                charge(ctx, 6);
                                v1 = 0x41000000;
                                mtc1(v1, f0);
                                c_le_s(f20, f0);
                                if (!cond(ctx)) {
                                    // 0x001dc3e8
                                    charge(ctx, 6);
                                    v1 = 0x41100000;
                                    mtc1(v1, f0);
                                    c_lt_s(f20, f0);
                                    if (!cond(ctx)) {
                                        goto L_001dc400;
                                    }
                                L_001dc430:
                                    charge(ctx, 24);
                                    v0 = s3 & 0xFFFF;
                                    a0 = v0 & 0x3FF;
                                    v1 = sll(a0, 2);
                                    v0 = 0x870000;
                                    v0 = addiu(v0, 23120);  // &0x875A50
                                    s0 = addu(v0, v1);
                                    v0 = addiu(a0, 1);
                                    a1 = dsll32(v0, 16);
                                    a1 = dsra32(a1, 16);
                                    v1 = sll(s2, 2);
                                    lw(v0, s0, 0);
                                    v0 = addu(v1, v0);
                                    a3 = dsll32(v0, 16);
                                    a3 = dsra32(a3, 16);
                                    a0 = 0;
                                    a2 = 5;
                                    jal(ctx, 0x1DC470u, gen::fn_sub_10A4E0_0010a4e0);
                                    lw(v1, s0, 0);
                                    v1 = addiu(v1, 1);
                                    sw(v1, s0, 0);
                                    v1 = slti(v1, 4);
                                    if (v1 == 0) {
                                        // 0x001dc490
                                        charge(ctx, 3);
                                        sw(zero, s0, 0);
                                    }
                                    break;
                                }
                            L_001dc400:
                                charge(ctx, 6);
                                v1 = 0x41900000;
                                mtc1(v1, f0);
                                c_le_s(f20, f0);
                                if (!cond(ctx)) {
                                    // 0x001dc418
                                    charge(ctx, 6);
                                    v1 = 0x41980000;
                                    mtc1(v1, f0);
                                    c_lt_s(f20, f0);
                                    if (cond(ctx)) {
                                        goto L_001dc430;
                                    }
                                }
                            }
                        }
                    }
                } else {
                    // 0x001dc288
                    charge(ctx, 6);
                    s0 = s0 & 0xFFFF;
                    a0 = s1;
                    jal(ctx, 0x1DC290u, gen::fn_sub_1DED40_001ded40);
                    if (s0 == v0) {
                        // 0x001dc2a0
                        charge(ctx, 6);
                        v1 = 0x41000000;
                        mtc1(v1, f0);
                        c_le_s(f20, f0);
                        if (!cond(ctx)) {
                            // 0x001dc2b8
                            charge(ctx, 6);
                            v1 = 0x41100000;
                            mtc1(v1, f0);
                            c_lt_s(f20, f0);
                            if (!cond(ctx)) {
                                goto L_001dc2d0;
                            }
                        L_001dc300:
                            charge(ctx, 24);
                            v0 = s3 & 0xFFFF;
                            a0 = v0 & 0x3FF;
                            v1 = sll(a0, 2);
                            v0 = 0x870000;
                            v0 = addiu(v0, 23120);  // &0x875A50
                            s0 = addu(v0, v1);
                            v0 = addiu(a0, 1);
                            a1 = dsll32(v0, 16);
                            a1 = dsra32(a1, 16);
                            v1 = sll(s2, 2);
                            lw(v0, s0, 0);
                            v0 = addu(v1, v0);
                            a3 = dsll32(v0, 16);
                            a3 = dsra32(a3, 16);
                            a0 = 0;
                            a2 = 5;
                            jal(ctx, 0x1DC340u, gen::fn_sub_10A4E0_0010a4e0);
                            lw(v1, s0, 0);
                            v1 = addiu(v1, 1);
                            sw(v1, s0, 0);
                            v1 = slti(v1, 4);
                            if (v1 == 0) {
                                // 0x001dc360
                                charge(ctx, 3);
                                sw(zero, s0, 0);
                            }
                            break;
                        }
                    L_001dc2d0:
                        charge(ctx, 6);
                        v1 = 0x41900000;
                        mtc1(v1, f0);
                        c_le_s(f20, f0);
                        if (!cond(ctx)) {
                            // 0x001dc2e8
                            charge(ctx, 6);
                            v1 = 0x41980000;
                            mtc1(v1, f0);
                            c_lt_s(f20, f0);
                            if (cond(ctx)) {
                                goto L_001dc300;
                            }
                        }
                    }
                }
                break;
            case 0x1DC49Cu:  // table[13]
                // 0x001dc49c
                charge(ctx, 4);
                a0 = s5 & 0xFFFF;
                v1 = 9;
                if (a0 != v1) {
                    // 0x001dc590
                    charge(ctx, 3);
                    v1 = 1;
                    if (a0 == v1) {
                        // 0x001dc59c
                        charge(ctx, 16);
                        a0 = s4;
                        jal(ctx, 0x1DC5A0u, gen::fn_sub_318B60_00318b60);
                        s4 = v0;
                        v0 = 0x870000;
                        lw(a0, v0, 6128);  // 0x8717F0
                        jal(ctx, 0x1DC5B4u, gen::fn_sub_318B60_00318b60);
                        v1 = 0x44C80000;
                        mtc1(v1, f12);
                        a0 = addiu(s4, 48);
                        a1 = addiu(v0, 48);
                        jal(ctx, 0x1DC5CCu, gen::fn_sub_1C71F0_001c71f0);
                        if (v0 != 0) {
                            // 0x001dc5dc
                            charge(ctx, 6);
                            s0 = s0 & 0xFFFF;
                            a0 = s1;
                            jal(ctx, 0x1DC5E4u, gen::fn_sub_1DED40_001ded40);
                            if (s0 == v0) {
                                // 0x001dc5f4
                                charge(ctx, 6);
                                v1 = 0x41000000;
                                mtc1(v1, f0);
                                c_le_s(f20, f0);
                                if (!cond(ctx)) {
                                    // 0x001dc60c
                                    charge(ctx, 6);
                                    v1 = 0x41100000;
                                    mtc1(v1, f0);
                                    c_lt_s(f20, f0);
                                    if (!cond(ctx)) {
                                        goto L_001dc624;
                                    }
                                L_001dc654:
                                    charge(ctx, 24);
                                    v0 = s3 & 0xFFFF;
                                    a0 = v0 & 0x3FF;
                                    v1 = sll(a0, 2);
                                    v0 = 0x870000;
                                    v0 = addiu(v0, 23120);  // &0x875A50
                                    s0 = addu(v0, v1);
                                    v0 = addiu(a0, 1);
                                    a1 = dsll32(v0, 16);
                                    a1 = dsra32(a1, 16);
                                    v1 = sll(s2, 2);
                                    lw(v0, s0, 0);
                                    v0 = addu(v1, v0);
                                    a3 = dsll32(v0, 16);
                                    a3 = dsra32(a3, 16);
                                    a0 = 0;
                                    a2 = 5;
                                    jal(ctx, 0x1DC694u, gen::fn_sub_10A4E0_0010a4e0);
                                    lw(v1, s0, 0);
                                    v1 = addiu(v1, 1);
                                    sw(v1, s0, 0);
                                    v1 = slti(v1, 4);
                                    if (v1 == 0) {
                                        // 0x001dc6b4
                                        charge(ctx, 1);
                                        sw(zero, s0, 0);
                                    }
                                    break;
                                }
                            L_001dc624:
                                charge(ctx, 6);
                                v1 = 0x41900000;
                                mtc1(v1, f0);
                                c_le_s(f20, f0);
                                if (!cond(ctx)) {
                                    // 0x001dc63c
                                    charge(ctx, 6);
                                    v1 = 0x41980000;
                                    mtc1(v1, f0);
                                    c_lt_s(f20, f0);
                                    if (cond(ctx)) {
                                        goto L_001dc654;
                                    }
                                }
                            }
                        }
                    }
                } else {
                    // 0x001dc4ac
                    charge(ctx, 6);
                    s0 = s0 & 0xFFFF;
                    a0 = s1;
                    jal(ctx, 0x1DC4B4u, gen::fn_sub_1DED40_001ded40);
                    if (s0 == v0) {
                        // 0x001dc4c4
                        charge(ctx, 6);
                        v1 = 0x41000000;
                        mtc1(v1, f0);
                        c_le_s(f20, f0);
                        if (!cond(ctx)) {
                            // 0x001dc4dc
                            charge(ctx, 6);
                            v1 = 0x41100000;
                            mtc1(v1, f0);
                            c_lt_s(f20, f0);
                            if (!cond(ctx)) {
                                goto L_001dc4f4;
                            }
                        L_001dc524:
                            charge(ctx, 24);
                            v0 = s3 & 0xFFFF;
                            a0 = v0 & 0x3FF;
                            v1 = sll(a0, 2);
                            v0 = 0x870000;
                            v0 = addiu(v0, 23120);  // &0x875A50
                            s0 = addu(v0, v1);
                            v0 = addiu(a0, 1);
                            a1 = dsll32(v0, 16);
                            a1 = dsra32(a1, 16);
                            v1 = sll(s2, 2);
                            lw(v0, s0, 0);
                            v0 = addu(v1, v0);
                            a3 = dsll32(v0, 16);
                            a3 = dsra32(a3, 16);
                            a0 = 0;
                            a2 = 5;
                            jal(ctx, 0x1DC564u, gen::fn_sub_10A4E0_0010a4e0);
                            lw(v1, s0, 0);
                            v1 = addiu(v1, 1);
                            sw(v1, s0, 0);
                            v1 = slti(v1, 4);
                            if (v1 == 0) {
                                // 0x001dc584
                                charge(ctx, 3);
                                sw(zero, s0, 0);
                            }
                            break;
                        }
                    L_001dc4f4:
                        charge(ctx, 6);
                        v1 = 0x41900000;
                        mtc1(v1, f0);
                        c_le_s(f20, f0);
                        if (!cond(ctx)) {
                            // 0x001dc50c
                            charge(ctx, 6);
                            v1 = 0x41980000;
                            mtc1(v1, f0);
                            c_lt_s(f20, f0);
                            if (cond(ctx)) {
                                goto L_001dc524;
                            }
                        }
                    }
                }
                break;
            case 0x1DC6B8u:  // table[0]
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v1.u());
                return;
            }
        }
    }
    // 0x001dc6b8 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0xD0);
    return;
L_001da1b0_11:
    charge(ctx, 3);
    lw(s2, s1, 332);
    goto L_001da244;
L_001da22c_15:
    charge(ctx, 3);
    lw(s2, s1, 332);
    goto L_001da244;
}

// 0x001F9E90 sub_1F9E90 -- 564 bytes; frame 0x90: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Social-link ("br_friend.c") level effect for link a0 (2..10) at level a1: prints "friend %d", then adds or removes
// the persona skills and raises the persona levels the link grants (jump table 0x7B7110).
void sub_1F9E90(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001f9e90
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    if (i64(s1) < 0) {
        // 0x001f9ebc
        charge(ctx, 5);
        a0 = 0x680000;
        a0 = addiu(a0, 19368);  // "br_friend.c"
        a1 = 94;
        jal(ctx, 0x1F9EC8u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x001f9ed0
    charge(ctx, 9);
    s0 = s2 & 0xFFFF;
    a0 = 0x680000;
    a0 = addiu(a0, 19384);  // "friend %d\n"
    a1 = s0;
    jal(ctx, 0x1F9EE0u, gen::fn_printf_005225a8);
    at = sltiu(s0, 11);
    if (at != 0) {
        // 0x001f9ef4
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, 28944);  // &0x7B7110
        v0 = sll(s0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x1F9F10u:  // table[0, 1]
        L_001f9f10:
            charge(ctx, 5);
            a0 = 0x680000;
            a0 = addiu(a0, 19368);  // "br_friend.c"
            a1 = 111;
            jal(ctx, 0x1F9F1Cu, gen::fn_sub_19D3F0_0019d3f0);
            break;
        case 0x1F9F24u:  // table[2, 3, 4, 5, 6, 7, 8, 9, 10]
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        goto L_001f9f24;
    }
    goto L_001f9f10;
L_001f9f24:
    charge(ctx, 11);
    a0 = dsll32(s2, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x1F9F2Cu, gen::fn_sub_16C470_0016c470);
    s3 = v0 & 0xFF;
    a0 = s2;
    jal(ctx, 0x1F9F3Cu, gen::fn_datPersonaGetByPcId_00174800);
    s4 = v0;
    if (s4 == 0) {
        // 0x001f9f50
        charge(ctx, 5);
        a0 = 0x680000;
        a0 = addiu(a0, 19368);  // "br_friend.c"
        a1 = 117;
        jal(ctx, 0x1F9F5Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x001f9f64
    charge(ctx, 9);
    a0 = s4;
    a1 = s1;
    jal(ctx, 0x1F9F6Cu, gen::fn_sub_1764B0_001764b0);
    a0 = s4;
    jal(ctx, 0x1F9F78u, gen::fn_sub_1761B0_001761b0);
    if (v0 != 0) {
        // 0x001f9f88
        charge(ctx, 29);
        a0 = s4;
        a1 = addiu(sp, 0x60);
        jal(ctx, 0x1F9F90u, gen::fn_sub_175CE0_00175ce0);
        lhu(v0, s4, 2);
        v1 = addiu(v0, -192);
        v0 = 622;
        mult(v1, v1, v0);
        lw(v0, gp, -18624);  // 0x7CE430
        s1 = addu(v0, v1);
        lbu(a2, s4, 4);
        lbu(a3, sp, 0x60);
        a0 = addiu(s1, 4);
        a1 = 32;
        t0 = addiu(sp, 0x8C);
        t1 = addiu(sp, 0x88);
        jal(ctx, 0x1F9FC8u, gen::fn_sub_1FB4B0_001fb4b0);
        lw(v0, sp, 0x8C);
        v0 = sll(v0, 2);
        v0 = addu(s1, v0);
        s1 = addiu(v0, 4);
        a0 = s4;
        a1 = addiu(sp, 0x60);
        jal(ctx, 0x1F9FE8u, gen::fn_sub_176100_00176100);
        s2 = 0;
        for (;;) {
            // 0x001fa078
            charge(ctx, 4);
            lw(v0, sp, 0x88);
            v0 = slt(s2, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001f9ffc
            charge(ctx, 4);
            lb(v1, s1, 1);
            v0 = 2;
            if (v1 == v0) {
                // 0x001fa04c
                charge(ctx, 9);
                lhu(a1, s1, 2);
                a0 = 0x680000;
                a0 = addiu(a0, 19424);  // "remove skill %x\n"
                jal(ctx, 0x1FA058u, gen::fn_printf_005225a8);
                a0 = s4;
                lhu(a1, s1, 2);
                jal(ctx, 0x1FA068u, gen::fn_sub_1768E0_001768e0);
            } else {
                // 0x001fa00c
                charge(ctx, 3);
                v0 = 1;
                if (v1 == v0) {
                    // 0x001fa020
                    charge(ctx, 11);
                    lhu(a1, s1, 2);
                    a0 = 0x680000;
                    a0 = addiu(a0, 19400);  // "add skill %x\n"
                    jal(ctx, 0x1FA02Cu, gen::fn_printf_005225a8);
                    a0 = s4;
                    lhu(a1, s1, 2);
                    jal(ctx, 0x1FA03Cu, gen::fn_sub_176840_00176840);
                } else {
                    // 0x001fa018
                    charge(ctx, 2);
                }
            }
            // 0x001fa070
            charge(ctx, 2);
            s2 = addiu(s2, 1);
            s1 = addiu(s1, 4);
        }
        // 0x001fa088
        charge(ctx, 6);
        a0 = 0x680000;
        a0 = addiu(a0, 19448);  // "f%x lv up %d\n"
        a1 = s0;
        a2 = s3;
        jal(ctx, 0x1FA098u, gen::fn_printf_005225a8);
    }
    // 0x001fa0a0 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x0025BE60 sub_25BE60 -- 676 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Battle dialog ("bp_dialog.c"): on the dialog record *(0x7CE368) creates three windows (sub_3A52C0) for the
// texts a0 / a1 / a2 (+4 / +8 / +12), sets +808 from sub_25CEB0's kind (2 -> 1, 1 -> 0) and the rest of the
// setup through sub_21C3F0 / sub_21CCA0 / sub_21D3B0 / sub_21E380.
void sub_25BE60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x0025be60
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s0 = a2;
    lw(v0, gp, -18824);  // 0x7CE368
    if (v0 == 0) {
        // 0x0025be98
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5160);  // "bp_dialog.c"
        a1 = 60;
        jal(ctx, 0x25BEA4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0025beac
    charge(ctx, 10);
    lw(s4, gp, -18824);  // 0x7CE368
    lw(s3, gp, -18692);  // 0x7CE3EC
    a0 = 0;
    jal(ctx, 0x25BEB8u, gen::fn_sub_21C3F0_0021c3f0);
    s5 = v0;
    lw(v0, s4, 0);
    v0 = v0 & 0x4;
    if (v0 != 0) {
        // 0x0025bed4
        charge(ctx, 2);
        jal(ctx, 0x25BED4u, gen::fn_sub_25CD30_0025cd30);
    }
    // 0x0025bedc
    charge(ctx, 39);
    mtc1(zero, f12);
    a0 = 100;
    a1 = a0;
    a2 = si(-1);
    a3 = 0;
    t0 = 6;
    lw(t1, s3, 2976);
    t2 = s2;
    jal(ctx, 0x25BEFCu, gen::fn_sub_3A52C0_003a52c0);
    sw(v0, s4, 4);
    mtc1(zero, f12);
    a0 = 100;
    a1 = a0;
    a2 = si(-1);
    a3 = 0;
    t0 = 0;
    lw(t1, s3, 2976);
    t2 = s1;
    jal(ctx, 0x25BF28u, gen::fn_sub_3A52C0_003a52c0);
    sw(v0, s4, 8);
    mtc1(zero, f12);
    a0 = 100;
    a1 = a0;
    a2 = si(-1);
    a3 = 0;
    t0 = 0;
    lw(t1, s3, 2976);
    t2 = s0;
    jal(ctx, 0x25BF54u, gen::fn_sub_3A52C0_003a52c0);
    sw(v0, s4, 12);
    lw(a0, s4, 4);
    jal(ctx, 0x25BF64u, gen::fn_sub_25CEB0_0025ceb0);
    v1 = 2;
    if (v0 == v1) {
        // 0x0025bf98
        charge(ctx, 4);
        v0 = 1;
        sw(v0, s4, 808);
    } else {
        // 0x0025bf78
        charge(ctx, 3);
        v1 = 1;
        if (v0 == v1) {
            // 0x0025bf8c
            charge(ctx, 3);
            sw(zero, s4, 808);
        } else {
            // 0x0025bf84
            charge(ctx, 2);
            // 0x0025bfa8
            charge(ctx, 5);
            a0 = 0x690000;
            a0 = addiu(a0, -5160);  // "bp_dialog.c"
            a1 = 123;
            jal(ctx, 0x25BFB4u, gen::fn_sub_19D3F0_0019d3f0);
        }
    }
    // 0x0025bfbc
    charge(ctx, 4);
    lw(v1, s4, 808);
    v0 = 1;
    if (v1 == v0) {
        // 0x0025bff4
        charge(ctx, 4);
        v0 = 87;
        sw(v0, s4, 800);
        v0 = 88;
        sw(v0, s4, 804);
    } else {
        // 0x0025bfcc
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x0025bfdc
            charge(ctx, 6);
            v0 = 85;
            sw(v0, s4, 800);
            v0 = 86;
            sw(v0, s4, 804);
        } else {
            // 0x0025bfd4
            charge(ctx, 2);
        }
    }
    // 0x0025c004
    charge(ctx, 64);
    a0 = s5;
    lw(a1, s4, 800);
    jal(ctx, 0x25C00Cu, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s4, 32);
    a1 = v0;
    jal(ctx, 0x25C01Cu, gen::fn_sub_21D3B0_0021d3b0);
    a0 = s5;
    lw(a1, s4, 800);
    jal(ctx, 0x25C02Cu, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s4, 288);
    a1 = v0;
    a2 = 1;
    jal(ctx, 0x25C040u, gen::fn_sub_21E380_0021e380);
    a0 = s5;
    lw(a1, s4, 804);
    jal(ctx, 0x25C050u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s4, 544);
    a1 = v0;
    jal(ctx, 0x25C060u, gen::fn_sub_21D3B0_0021d3b0);
    a0 = s5;
    a1 = 89;
    jal(ctx, 0x25C070u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s4, 816);
    a1 = v0;
    jal(ctx, 0x25C080u, gen::fn_sub_21D3B0_0021d3b0);
    a0 = s5;
    a1 = 90;
    jal(ctx, 0x25C090u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s4, 1072);
    a1 = v0;
    jal(ctx, 0x25C0A0u, gen::fn_sub_21D3B0_0021d3b0);
    sw(zero, s4, 20);
    sw(zero, s4, 24);
    lw(a0, s4, 0);
    v1 = si(-3);
    a0 = a0 & v1;
    sw(a0, s4, 0);
    v1 = si(-9);
    v1 = a0 & v1;
    sw(v1, s4, 0);
    v1 = v1 | 0x4;
    sw(v1, s4, 0);
    v1 = v1 | 0x1;
    sw(v1, s4, 0);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x00351C20 sub_351C20 -- 124 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Create the "effect_crossfade" task (priority 4185, update sub_351A10) with a zeroed 16-byte work block.
void sub_351C20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00351c20
    enter(ctx, 31);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 16;
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x351C3Cu, v0.u());
    s0 = v0;
    a0 = s0;
    a1 = 0;
    a2 = 16;
    jal(ctx, 0x351C54u, gen::fn_memset_00521408);
    sb(zero, s0, 0);
    a0 = 0;
    a1 = 0x6A0000;
    a1 = addiu(a1, -13152);  // "effect_crossfade"
    a2 = 4185;
    a3 = 0x350000;
    a3 = addiu(a3, 6672);  // &sub_351A10
    t0 = 0;
    t1 = s0;
    jal(ctx, 0x351C80u, gen::fn_kwlnTaskCreate_00194b20);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003580F0 sub_3580F0 -- 112 bytes; leaf frame (no stack)
// [proposed name: effMng_SeedScrambler] Seed a 16-byte scrambler state (a0, or the default 0x957BF0): w0 = a1 ^ 0x0AED1A0C, w1 = rotr8(w0),
// w2 = rotr8(w1 ^ 0xAA5A02FE), w3 = rotr8(w2 ^ 0x11BE81C7).
void sub_3580F0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x003580f0
    enter(ctx, 2);  // entry check point + this block's cycles
    if (a0 == 0) {
        // 0x003580f8
        charge(ctx, 2);
        a0 = 0x950000;
        a0 = addiu(a0, 31728);  // &0x957BF0
    }
    // 0x00358100 (the shared epilogue, written out on this path)
    charge(ctx, 24);
    v1 = 0xAED0000;
    v1 = v1 | 0x1A0C;  // L::kScr0
    v1 = a1 ^ v1;
    sw(v1, a0, 0);
    a1 = sll(v1, 24);
    v1 = srl(v1, 8);
    a1 = a1 | v1;
    sw(a1, a0, 4);
    v1 = lui(0xAA5A);
    v1 = v1 | 0x2FE;  // L::kScr1
    v1 = a1 ^ v1;
    a1 = sll(v1, 24);
    v1 = srl(v1, 8);
    a1 = a1 | v1;
    sw(a1, a0, 8);
    v1 = 0x11BE0000;
    v1 = v1 | 0x81C7;  // L::kScr2
    v1 = a1 ^ v1;
    a1 = sll(v1, 24);
    v1 = srl(v1, 8);
    v1 = a1 | v1;
    sw(v1, a0, 12);
}

// 0x003F33D0 sub_3F33D0 -- 1432 bytes; frame 0x140: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Shop misc ("fclShopMisc.c") menu open for shop a0 (0..8; 3 has 4 rows): the 88-wide list window, its rows from
// the shop table (0x6AC9D0, the FES half when sub_17D800), the a1 flags (1 = 0x400, 2 = 0x800) and the item rows
// built by sub_3F39A0.
void sub_3F33D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003f33d0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x140);
    sd(ra, sp, 0x80);
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
    s1 = 0;
    s2 = 5;
    v0 = 3;
    if (s4 == v0) {
        // 0x003f3414
        charge(ctx, 1);
        s2 = 4;
    }
    // 0x003f3418
    charge(ctx, 3);
    v0 = s3 & 0x1;
    if (v0 != 0) {
        // 0x003f3424
        charge(ctx, 1);
        s1 = s1 | 0x400;
    }
    // 0x003f3428
    charge(ctx, 3);
    v0 = s3 & 0x2;
    if (v0 != 0) {
        // 0x003f3434
        charge(ctx, 1);
        s1 = s1 | 0x800;
    }
    // 0x003f3438
    charge(ctx, 2);
    if (i64(s4) >= 0) {
        // 0x003f3440
        charge(ctx, 3);
        v0 = slti(s4, 9);
        if (v0 == 0) {
            goto L_003f344c;
        }
        goto L_003f3460;
    }
L_003f344c:
    charge(ctx, 5);
    a0 = 0x6B0000;
    a0 = addiu(a0, -4632);  // "fclShopMisc.c"
    a1 = 185;
    jal(ctx, 0x3F3458u, gen::fn_sub_19D3F0_0019d3f0);
L_003f3460:
    charge(ctx, 4);
    jal(ctx, 0x3F3460u, gen::fn_sub_17D800_0017d800);
    if (v0 != 0) {
        // 0x003f3490
        charge(ctx, 7);
        v1 = addiu(s4, 9);
        v0 = sll(v1, 3);
        v0 = addu(v0, v1);
        v1 = sll(v0, 2);
        v0 = 0x6B0000;
        v0 = addiu(v0, -13872);  // &0x6AC9D0
        s0 = addu(v0, v1);
    } else {
        // 0x003f3470
        charge(ctx, 8);
        v0 = sll(s4, 3);
        v0 = addu(v0, s4);
        v1 = sll(v0, 2);
        v0 = 0x6B0000;
        v0 = addiu(v0, -13872);  // &0x6AC9D0
        s0 = addu(v0, v1);
    }
    // 0x003f34ac
    charge(ctx, 18);
    a0 = 0;
    a1 = 88;
    a2 = s2;
    a3 = 26;
    jal(ctx, 0x3F34BCu, gen::fn_sub_3C58F0_003c58f0);
    s2 = v0;
    lw(v0, v0, 36);
    lw(v0, v0, 68);
    sh(s4, v0, 4);
    sh(s4, v0, 6);
    a0 = s0;
    a1 = 1;
    a2 = addiu(sp, 0x138);
    jal(ctx, 0x3F34E4u, gen::fn_sub_3F00D0_003f00d0);
    if (v0 == 0) {
        // 0x003f34f4
        charge(ctx, 6);
        sw(zero, sp, 0x138);
        a0 = s0;
        a1 = 0;
        a2 = addiu(sp, 0x138);
        jal(ctx, 0x3F3504u, gen::fn_sub_3F00D0_003f00d0);
    }
    // 0x003f350c
    charge(ctx, 2);
    if (v0 != 0) {
        // 0x003f3514
        charge(ctx, 7);
        lbu(v1, sp, 0x138);
        sh(v1, gp, -18008);  // 0x7CE698
        a2 = s1 | 0x2000;
        a0 = s2;
        a1 = v0;
        jal(ctx, 0x3F3528u, gen::fn_sub_3F25E0_003f25e0);
    }
    // 0x003f3530
    charge(ctx, 4);
    sw(zero, sp, 0x134);
    s6 = s1 | 0x2000;
    for (;;) {
        // 0x003f3584
        charge(ctx, 5);
        lw(v1, sp, 0x134);
        lw(v0, s0, 24);
        v0 = slt(v1, v0);
        if (v0 != 0) {
            // 0x003f35a4
            charge(ctx, 7);
            v0 = addiu(v1, 1);
            sw(v0, sp, 0x134);
            v0 = sll(v1, 1);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s0, 28);
            s5 = addu(v0, v1);
        } else {
            // 0x003f3598
            charge(ctx, 3);
            s5 = 0;
        }
        // 0x003f35c0
        charge(ctx, 2);
        if (s5 != 0) {
            backedge(ctx);
            // 0x003f3540
            charge(ctx, 8);
            lw(s7, s5, 0);
            a0 = 1;
            jal(ctx, 0x3F3548u, gen::fn_sub_16C470_0016c470);
            v0 = v0 & 0xFF;
            at = slt(v0, s7);
            if (at == 0) {
                // 0x003f3560
                charge(ctx, 9);
                lbu(v0, sp, 0x134);
                v0 = v0 | 0x100;
                sh(v0, gp, -18008);  // 0x7CE698
                a0 = s2;
                lw(a1, s5, 8);
                lw(a2, s5, 4);
                a3 = s6;
                jal(ctx, 0x3F357Cu, gen::fn_sub_3F2940_003f2940);
                continue;
            }
        }
        break;
    }
    // 0x003f35c8
    charge(ctx, 4);
    sw(zero, sp, 0x13C);
    s1 = s1 | 0x2001;
    for (;;) {
        // 0x003f35f4
        charge(ctx, 7);
        a0 = addiu(s0, 16);
        a1 = 0;
        a2 = addiu(sp, 0x13C);
        jal(ctx, 0x3F3600u, gen::fn_sub_3F00D0_003f00d0);
        if (v0 == 0) {
            // 0x003f3628
            charge(ctx, 1);
            a1 = 0;
        } else {
            // 0x003f3610
            charge(ctx, 6);
            lw(v1, sp, 0x13C);
            v1 = addiu(v1, 1);
            sw(v1, sp, 0x13C);
            a1 = v0;
        }
        // 0x003f362c
        charge(ctx, 2);
        if (a1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003f35d8
        charge(ctx, 7);
        lbu(v0, sp, 0x13C);
        v0 = v0 | 0x200;
        sh(v0, gp, -18008);  // 0x7CE698
        a0 = s2;
        a2 = s1;
        jal(ctx, 0x3F35ECu, gen::fn_sub_3F25E0_003f25e0);
    }
    // 0x003f3634
    charge(ctx, 8);
    a0 = s4;
    jal(ctx, 0x3F3638u, gen::fn_sub_3F03E0_003f03e0);
    s1 = v0;
    v0 = 1;
    sw(v0, sp, 0x13C);
    for (;;) {
        // 0x003f369c
        charge(ctx, 4);
        lw(v0, sp, 0x13C);
        at = slt(s1, v0);
        if (at != 0) {
            break;
        }
        backedge(ctx);
        // 0x003f3654
        charge(ctx, 6);
        lw(v1, s0, 32);
        a0 = sll(v0, 5);
        lw(v1, v1, 8);
        v1 = addu(v1, a0);
        if (v1 != 0) {
            // 0x003f366c
            charge(ctx, 9);
            v0 = v0 & 0xFF;
            v0 = v0 | 0x300;
            sh(v0, gp, -18008);  // 0x7CE698
            a0 = s2;
            lw(a1, v1, 8);
            lw(a2, v1, 4);
            a3 = s6;
            jal(ctx, 0x3F3688u, gen::fn_sub_3F2940_003f2940);
        }
        // 0x003f3690
        charge(ctx, 3);
        lw(v0, sp, 0x13C);
        v0 = addiu(v0, 1);
        sw(v0, sp, 0x13C);
    }
    // 0x003f36ac
    charge(ctx, 7);
    a0 = addiu(s0, 8);
    a1 = 1;
    a2 = 0;
    jal(ctx, 0x3F36B8u, gen::fn_sub_3F00D0_003f00d0);
    if (v0 == 0) {
        // 0x003f36c8
        charge(ctx, 5);
        a0 = addiu(s0, 8);
        a1 = 0;
        a2 = 0;
        jal(ctx, 0x3F36D4u, gen::fn_sub_3F00D0_003f00d0);
    }
    // 0x003f36dc
    charge(ctx, 2);
    if (v0 != 0) {
        // 0x003f36e4
        charge(ctx, 4);
        a0 = s2;
        a1 = v0;
        jal(ctx, 0x3F36ECu, gen::fn_sub_3F2320_003f2320);
    }
    // 0x003f36f4
    charge(ctx, 3);
    v0 = 3;
    if (s4 != v0) {
        // 0x003f3700
        charge(ctx, 3);
        v0 = s3 & 0x4;
        if (v0 == 0) {
            // 0x003f3768
            charge(ctx, 10);
            a0 = s4;
            jal(ctx, 0x3F376Cu, gen::fn_sub_17D610_0017d610);
            a0 = s4;
            a1 = s3;
            jal(ctx, 0x3F377Cu, gen::fn_sub_3F3970_003f3970);
            s0 = v0;
            if (v0 != 0) {
                // 0x003f3790
                charge(ctx, 7);
                a0 = s2;
                a1 = s0;
                jal(ctx, 0x3F3798u, gen::fn_sub_3F3DC0_003f3dc0);
                a0 = s0;
                jal(ctx, 0x3F37A4u, gen::fn_nmCmdListDestroy_003c5a20);
            }
            goto L_003f37ac;
        }
        // 0x003f370c
        charge(ctx, 9);
        s0 = 0;
        a0 = s4;
        a1 = 1;
        a2 = s3;
        jal(ctx, 0x3F371Cu, gen::fn_sub_3F39A0_003f39a0);
        s1 = v0;
        if (v0 != 0) {
            // 0x003f3730
            charge(ctx, 8);
            a0 = s2;
            a1 = s1;
            jal(ctx, 0x3F3738u, gen::fn_sub_3F3E60_003f3e60);
            s0 = v0;
            a0 = s1;
            jal(ctx, 0x3F3748u, gen::fn_nmCmdListDestroy_003c5a20);
        }
        // 0x003f3750
        charge(ctx, 6);
        a0 = s2;
        jal(ctx, 0x3F3754u, gen::fn_nmCmdListDestroy_003c5a20);
        v0 = s0;
        // 0x003f3938 (the shared epilogue, written out on this path)
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
        sp = addiu(sp, 0x140);
        return;
    }
L_003f37ac:
    charge(ctx, 13);
    a0 = s2;
    a1 = 0x3F0000;
    a1 = addiu(a1, 12928);  // &sub_3F3280
    a2 = 0;
    jal(ctx, 0x3F37BCu, gen::fn_nmCmdListSort_003c7000);
    a0 = s2;
    jal(ctx, 0x3F37C8u, gen::fn_sub_3C6EE0_003c6ee0);
    a2 = 0x6B0000;
    a2 = addiu(a2, -4608);  // &0x6AEE00
    a1 = addiu(sp, 0x110);
    a0 = 4;
    for (;;) {
        // 0x003f37e0
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
    // 0x003f3804
    charge(ctx, 4);
    a2 = 0x6B0000;
    a2 = addiu(a2, -4576);  // &0x6AEE20
    a1 = addiu(sp, 0xF0);
    a0 = 4;
    for (;;) {
        // 0x003f3814
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
    // 0x003f3838
    charge(ctx, 4);
    a2 = 0x6B0000;
    a2 = addiu(a2, -4544);  // &0x6AEE40
    a1 = addiu(sp, 0xD0);
    a0 = 4;
    for (;;) {
        // 0x003f3848
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
    // 0x003f386c
    charge(ctx, 4);
    a2 = 0x6B0000;
    a2 = addiu(a2, -4512);  // &0x6AEE60
    a1 = addiu(sp, 0x90);
    a0 = 8;
    for (;;) {
        // 0x003f387c
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
    // 0x003f38a0
    charge(ctx, 26);
    s0 = sll(s4, 2);
    v0 = addu(s0, sp);
    a0 = s2;
    lw(a1, v0, 272);
    jal(ctx, 0x3F38B0u, gen::fn_nmCmdListSetUpdateFunc_003c5e80);
    v0 = addu(s0, sp);
    a0 = s2;
    lw(a1, v0, 240);
    jal(ctx, 0x3F38C4u, gen::fn_nmCmdListSetDrawFunc_003c5e20);
    v0 = addu(s0, sp);
    a0 = s2;
    lw(a1, v0, 208);
    jal(ctx, 0x3F38D8u, gen::fn_nmCmdListSetRowDrawFunc_003c5ee0);
    v0 = sll(s4, 3);
    v0 = addu(v0, sp);
    a0 = s2;
    lw(a1, v0, 144);
    lw(a2, v0, 148);
    jal(ctx, 0x3F38F4u, gen::fn_nmCmdListSetPosition_003c6d40);
    v0 = 4;
    if (s4 != v0) {
        // 0x003f391c
        charge(ctx, 3);
        v1 = 20;
        lw(v0, s2, 36);
        sh(v1, v0, 6);
    } else {
        // 0x003f3908
        charge(ctx, 5);
        v1 = 10;
        lw(v0, s2, 36);
        sh(v1, v0, 6);
    }
    // 0x003f3928
    charge(ctx, 4);
    v1 = 10;
    lw(v0, s2, 36);
    sh(v1, v0, 8);
    v0 = s2;
    // 0x003f3938 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0x140);
}

// 0x003F39A0 sub_3F39A0 -- 1044 bytes; frame 0x80: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Shop misc row builder: the eight item slots of 0x6ACC60 enabled by their flags (slot 6 also in FES), the date
// window from sub_17D6D0 / sub_17D700, the rows added and the visit flag set.
void sub_3F39A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003f39a0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a2;
    s1 = 0;
    if (a1 != 0) {
        // 0x003f39e8
        charge(ctx, 4);
        a1 = 0;
        a2 = addiu(sp, 0x70);
        jal(ctx, 0x3F39F0u, gen::fn_sub_17D700_0017d700);
    } else {
        // 0x003f39d4
        charge(ctx, 5);
        a1 = addiu(sp, 0x70);
        jal(ctx, 0x3F39D8u, gen::fn_sub_17D6D0_0017d6d0);
    }
    // 0x003f39f8
    charge(ctx, 4);
    s0 = 0;
    s4 = 0;
    for (;;) {
        // 0x003f3a88
        charge(ctx, 3);
        v0 = sltiu(s4, 8);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003f3a08
        charge(ctx, 8);
        v1 = sll(s4, 1);
        v0 = 0x6B0000;
        v0 = addiu(v0, -13216);  // &0x6ACC60
        v0 = addu(v0, v1);
        lh(a0, v0, 0);
        v0 = si(-1);
        if (a0 != v0) {
            // 0x003f3a28
            charge(ctx, 4);
            jal(ctx, 0x3F3A28u, gen::fn_datGetFlag_0016f190);
            if (v0 == 0) {
                goto L_003f3a54;
            }
            // 0x003f3a38
            charge(ctx, 7);
            v0 = 1;
            v0 = sllv(v0, s4);
            v0 = v0 & 0xFFFF;
            v0 = s0 | v0;
            s0 = v0 & 0xFFFF;
            goto L_003f3a84;
        }
    L_003f3a54:
        charge(ctx, 3);
        v0 = 6;
        if (s4 == v0) {
            // 0x003f3a60
            charge(ctx, 4);
            jal(ctx, 0x3F3A60u, gen::fn_sub_17D800_0017d800);
            if (v0 != 0) {
                // 0x003f3a70
                charge(ctx, 5);
                v0 = 1;
                v0 = sllv(v0, s4);
                v0 = v0 & 0xFFFF;
                v0 = s0 | v0;
                s0 = v0 & 0xFFFF;
            }
        }
    L_003f3a84:
        charge(ctx, 1);
        s4 = addiu(s4, 1);
    }
    // 0x003f3a94
    charge(ctx, 4);
    lhu(s4, sp, 0x72);
    s5 = 0;
    for (;;) {
        // 0x003f3b14
        charge(ctx, 3);
        v0 = sltiu(s5, 8);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003f3aa4
        charge(ctx, 3);
        v0 = 6;
        if (s5 == v0) {
            // 0x003f3ab0
            charge(ctx, 4);
            jal(ctx, 0x3F3AB0u, gen::fn_sub_17D800_0017d800);
            if (v0 == 0) {
                goto L_003f3ac0;
            }
            goto L_003f3b10;
        }
    L_003f3ac0:
        charge(ctx, 8);
        v1 = sll(s5, 1);
        v0 = 0x6B0000;
        v0 = addiu(v0, -13216);  // &0x6ACC60
        v0 = addu(v0, v1);
        lh(a0, v0, 0);
        v0 = si(-1);
        if (a0 != v0) {
            // 0x003f3ae0
            charge(ctx, 5);
            a1 = 1;
            v0 = sllv(a1, s5);
            v0 = s4 & v0;
            if (v0 == 0) {
                // 0x003f3b04
                charge(ctx, 3);
                a1 = 0;
                jal(ctx, 0x3F3B08u, gen::fn_datSetFlag_0016f1f0);
            } else {
                // 0x003f3af4
                charge(ctx, 4);
                jal(ctx, 0x3F3AF4u, gen::fn_datSetFlag_0016f1f0);
            }
        }
    L_003f3b10:
        charge(ctx, 1);
        s5 = addiu(s5, 1);
    }
    // 0x003f3b20
    charge(ctx, 3);
    v0 = s2 & 0x1;
    if (v0 != 0) {
        // 0x003f3b2c
        charge(ctx, 1);
        s1 = s1 | 0x400;
    }
    // 0x003f3b30
    charge(ctx, 3);
    v0 = s2 & 0x2;
    if (v0 != 0) {
        // 0x003f3b3c
        charge(ctx, 1);
        s1 = s1 | 0x800;
    }
    // 0x003f3b40
    charge(ctx, 2);
    if (i64(s3) >= 0) {
        // 0x003f3b48
        charge(ctx, 3);
        v0 = slti(s3, 9);
        if (v0 == 0) {
            goto L_003f3b54;
        }
        goto L_003f3b68;
    }
L_003f3b54:
    charge(ctx, 5);
    a0 = 0x6B0000;
    a0 = addiu(a0, -4632);  // "fclShopMisc.c"
    a1 = 185;
    jal(ctx, 0x3F3B60u, gen::fn_sub_19D3F0_0019d3f0);
L_003f3b68:
    charge(ctx, 4);
    jal(ctx, 0x3F3B68u, gen::fn_sub_17D800_0017d800);
    if (v0 != 0) {
        // 0x003f3b98
        charge(ctx, 7);
        v1 = addiu(s3, 9);
        v0 = sll(v1, 3);
        v0 = addu(v0, v1);
        v1 = sll(v0, 2);
        v0 = 0x6B0000;
        v0 = addiu(v0, -13872);  // &0x6AC9D0
        s3 = addu(v0, v1);
    } else {
        // 0x003f3b78
        charge(ctx, 8);
        v0 = sll(s3, 3);
        v0 = addu(v0, s3);
        v1 = sll(v0, 2);
        v0 = 0x6B0000;
        v0 = addiu(v0, -13872);  // &0x6AC9D0
        s3 = addu(v0, v1);
    }
    // 0x003f3bb4
    charge(ctx, 12);
    a0 = 0;
    a1 = 88;
    a2 = 5;
    a3 = 26;
    jal(ctx, 0x3F3BC4u, gen::fn_sub_3C58F0_003c58f0);
    s2 = v0;
    lw(v1, sp, 0x74);
    lw(v0, s3, 0);
    at = sltu(v1, v0);
    if (at != 0) {
        // 0x003f3bf0
        charge(ctx, 5);
        v0 = sll(v1, 2);
        v0 = addu(v0, v1);
        v1 = sll(v0, 2);
        lw(v0, s3, 4);
        a1 = addu(v0, v1);
    } else {
        // 0x003f3be4
        charge(ctx, 3);
        a1 = 0;
    }
    // 0x003f3c04
    charge(ctx, 2);
    if (a1 != 0) {
        // 0x003f3c0c
        charge(ctx, 4);
        a2 = s1 | 0x6000;
        a0 = s2;
        jal(ctx, 0x3F3C14u, gen::fn_sub_3F25E0_003f25e0);
    }
    // 0x003f3c1c
    charge(ctx, 4);
    sw(zero, sp, 0x7C);
    s4 = s1 | 0x6000;
    for (;;) {
        // 0x003f3c58
        charge(ctx, 5);
        lw(v1, sp, 0x7C);
        lw(v0, s3, 24);
        v0 = slt(v1, v0);
        if (v0 != 0) {
            // 0x003f3c78
            charge(ctx, 7);
            v0 = addiu(v1, 1);
            sw(v0, sp, 0x7C);
            v0 = sll(v1, 1);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s3, 28);
            a2 = addu(v0, v1);
        } else {
            // 0x003f3c6c
            charge(ctx, 3);
            a2 = 0;
        }
        // 0x003f3c94
        charge(ctx, 2);
        if (a2 != 0) {
            backedge(ctx);
            // 0x003f3c2c
            charge(ctx, 5);
            lw(v1, sp, 0x7C);
            lbu(v0, sp, 0x70);
            at = slt(v0, v1);
            if (at == 0) {
                // 0x003f3c40
                charge(ctx, 6);
                a0 = s2;
                lw(a1, a2, 8);
                lw(a2, a2, 4);
                a3 = s4;
                jal(ctx, 0x3F3C50u, gen::fn_sub_3F2940_003f2940);
                continue;
            }
        }
        break;
    }
    // 0x003f3c9c
    charge(ctx, 5);
    lbu(s1, sp, 0x71);
    v0 = 1;
    sw(v0, sp, 0x7C);
    for (;;) {
        // 0x003f3cec
        charge(ctx, 4);
        lw(v0, sp, 0x7C);
        at = slt(s1, v0);
        if (at != 0) {
            break;
        }
        backedge(ctx);
        // 0x003f3cb0
        charge(ctx, 6);
        lw(a0, s3, 32);
        v1 = sll(v0, 5);
        lw(v0, a0, 8);
        v0 = addu(v0, v1);
        if (v0 != 0) {
            // 0x003f3cc8
            charge(ctx, 6);
            a0 = s2;
            lw(a1, v0, 8);
            lw(a2, v0, 4);
            a3 = s4;
            jal(ctx, 0x3F3CD8u, gen::fn_sub_3F2940_003f2940);
        }
        // 0x003f3ce0
        charge(ctx, 3);
        lw(v0, sp, 0x7C);
        v0 = addiu(v0, 1);
        sw(v0, sp, 0x7C);
    }
    // 0x003f3cfc
    charge(ctx, 4);
    s1 = 0;
    s0 = s0 & 0xFFFF;
    for (;;) {
        // 0x003f3d7c
        charge(ctx, 3);
        v0 = sltiu(s1, 8);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003f3d0c
        charge(ctx, 3);
        v0 = 6;
        if (s1 == v0) {
            // 0x003f3d18
            charge(ctx, 4);
            jal(ctx, 0x3F3D18u, gen::fn_sub_17D800_0017d800);
            if (v0 == 0) {
                goto L_003f3d28;
            }
            goto L_003f3d78;
        }
    L_003f3d28:
        charge(ctx, 8);
        v1 = sll(s1, 1);
        v0 = 0x6B0000;
        v0 = addiu(v0, -13216);  // &0x6ACC60
        v0 = addu(v0, v1);
        lh(a0, v0, 0);
        v0 = si(-1);
        if (a0 != v0) {
            // 0x003f3d48
            charge(ctx, 5);
            a1 = 1;
            v0 = sllv(a1, s1);
            v0 = s0 & v0;
            if (v0 == 0) {
                // 0x003f3d6c
                charge(ctx, 3);
                a1 = 0;
                jal(ctx, 0x3F3D70u, gen::fn_datSetFlag_0016f1f0);
            } else {
                // 0x003f3d5c
                charge(ctx, 4);
                jal(ctx, 0x3F3D5Cu, gen::fn_datSetFlag_0016f1f0);
            }
        }
    L_003f3d78:
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x003f3d88
    charge(ctx, 11);
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

// 0x003FFE60 sub_3FFE60 -- 1336 bytes; frame 0x100: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Build one of the facility menus by kind a0 (jump table 0x7BBDB0): its position, row count and labels from the
// 0x7CD980.. tables, the rows added with nmCmdListAddRow and the handlers sub_4006C0 / sub_400740 / sub_4008F0 /
// sub_400B90.
void sub_3FFE60(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x003ffe60
    enter(ctx, 19);  // entry check point + this block's cycles
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
    s6 = 0x400000;
    s6 = addiu(s6, 1728);  // &sub_4006C0
    fp = 0x400000;
    fp = addiu(fp, 0xB90);
    at = sltiu(s5, 9);
    if (at != 0) {
        // 0x003ffeac
        charge(ctx, 7);
        v1 = 0x7C0000;
        v1 = addiu(v1, -16976);  // &0x7BBDB0
        v0 = sll(s5, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x3FFEC8u:  // table[0]
            // 0x003ffec8
            charge(ctx, 7);
            s1 = 154;
            s0 = 129;
            s3 = 102;
            s2 = 5;
            a2 = addiu(gp, -21360);  // &0x7CD980
            a1 = addiu(sp, 0xF0);
            a0 = 4;
            for (;;) {
                // 0x003ffee4
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
            // 0x003fff08
            charge(ctx, 4);
            ld(v0, sp, 0xF0);
            sd(v0, sp, 0xF8);
            break;
        case 0x3FFF18u:  // table[2]
            // 0x003fff18
            charge(ctx, 7);
            s1 = 215;
            s0 = 100;
            s3 = 112;
            s2 = 4;
            a2 = addiu(gp, -21352);  // &0x7CD988
            a1 = addiu(sp, 0xE8);
            a0 = s2;
            for (;;) {
                // 0x003fff34
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
            // 0x003fff58
            charge(ctx, 6);
            ld(v0, sp, 0xE8);
            sd(v0, sp, 0xF8);
            s6 = 0x400000;
            s6 = addiu(s6, 1856);  // &sub_400740
            break;
        case 0x3FFF70u:  // table[4]
            // 0x003fff70
            charge(ctx, 6);
            s4 = 0;
            a0 = 368;
            jal(ctx, 0x3FFF78u, gen::fn_datGetFlag_0016f190);
            if (v0 != 0) {
                // 0x003fff88
                charge(ctx, 1);
                s4 = s4 | 0x2;
            }
            // 0x003fff8c
            charge(ctx, 4);
            s3 = 98;
            v0 = 3;
            if (s4 == v0) {
                // 0x004000a8
                charge(ctx, 6);
                s1 = 70;
                s0 = 108;
                s2 = 6;
                a2 = addiu(gp, -21320);  // &0x7CD9A8
                a1 = addiu(sp, 0xC8);
                a0 = 4;
                for (;;) {
                    // 0x004000c0
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
                // 0x004000e4
                charge(ctx, 2);
                ld(v0, sp, 0xC8);
                sd(v0, sp, 0xF8);
            } else {
                // 0x003fff9c
                charge(ctx, 3);
                v0 = 2;
                if (s4 == v0) {
                    // 0x0040005c
                    charge(ctx, 6);
                    s1 = 119;
                    s0 = 108;
                    s2 = 5;
                    a2 = addiu(gp, -21328);  // &0x7CD9A0
                    a1 = addiu(sp, 0xD0);
                    a0 = 4;
                    for (;;) {
                        // 0x00400074
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
                    // 0x00400098
                    charge(ctx, 4);
                    ld(v0, sp, 0xD0);
                    sd(v0, sp, 0xF8);
                } else {
                    // 0x003fffa8
                    charge(ctx, 3);
                    v0 = 1;
                    if (s4 == v0) {
                        // 0x00400010
                        charge(ctx, 6);
                        s1 = 119;
                        s0 = 108;
                        s2 = 5;
                        a2 = addiu(gp, -21336);  // &0x7CD998
                        a1 = addiu(sp, 0xD8);
                        a0 = 4;
                        for (;;) {
                            // 0x00400028
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
                        // 0x0040004c
                        charge(ctx, 4);
                        ld(v0, sp, 0xD8);
                        sd(v0, sp, 0xF8);
                    } else {
                        // 0x003fffb4
                        charge(ctx, 2);
                        if (s4 == 0) {
                            // 0x003fffc4
                            charge(ctx, 6);
                            s1 = 168;
                            s0 = 108;
                            s2 = 4;
                            a2 = addiu(gp, -21344);  // &0x7CD990
                            a1 = addiu(sp, 0xE0);
                            a0 = s2;
                            for (;;) {
                                // 0x003fffdc
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
                            // 0x00400000
                            charge(ctx, 4);
                            ld(v0, sp, 0xE0);
                            sd(v0, sp, 0xF8);
                        } else {
                            // 0x003fffbc
                            charge(ctx, 2);
                        }
                    }
                }
            }
            // 0x004000ec
            charge(ctx, 4);
            s6 = 0x400000;
            s6 = addiu(s6, 2288);  // &sub_4008F0
            break;
        case 0x4000FCu:  // table[8]
            // 0x004000fc
            charge(ctx, 12);
            s1 = 40;
            s0 = 365;
            a0 = 4612;
            jal(ctx, 0x400108u, gen::fn_datGetFlag_0016f190);
            a0 = 4614;
            jal(ctx, 0x400114u, gen::fn_datGetFlag_0016f190);
            s2 = 6;
            a2 = addiu(gp, -21312);  // &0x7CD9B0
            a1 = addiu(sp, 0xC0);
            a0 = 4;
            for (;;) {
                // 0x0040012c
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
            // 0x00400150
            charge(ctx, 4);
            ld(v0, sp, 0xC0);
            sd(v0, sp, 0xF8);
            break;
        case 0x400160u:  // table[3]
            // 0x00400160
            charge(ctx, 7);
            s1 = 93;
            s0 = 85;
            s3 = 113;
            s2 = 3;
            a2 = addiu(gp, -21304);  // &0x7CD9B8
            a1 = addiu(sp, 0xB8);
            a0 = 4;
            for (;;) {
                // 0x0040017c
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
            // 0x004001a0
            charge(ctx, 4);
            ld(v0, sp, 0xB8);
            sd(v0, sp, 0xF8);
            break;
        case 0x4001B0u:  // table[6]
            // 0x004001b0
            charge(ctx, 7);
            s1 = 230;
            s0 = 365;
            s3 = 112;
            s2 = 3;
            a2 = addiu(gp, -21296);  // &0x7CD9C0
            a1 = addiu(sp, 0xB0);
            a0 = 4;
            for (;;) {
                // 0x004001cc
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
            // 0x004001f0
            charge(ctx, 4);
            ld(v0, sp, 0xB0);
            sd(v0, sp, 0xF8);
            break;
        case 0x400200u:  // table[1, 5, 7]
        L_00400200:
            charge(ctx, 7);
            s1 = 230;
            s0 = 365;
            s3 = 112;
            s2 = 4;
            a2 = addiu(gp, -21288);  // &0x7CD9C8
            a1 = addiu(sp, 0xA8);
            a0 = s2;
            for (;;) {
                // 0x0040021c
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
            // 0x00400240
            charge(ctx, 2);
            ld(v0, sp, 0xA8);
            sd(v0, sp, 0xF8);
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        goto L_00400248;
    }
    goto L_00400200;
L_00400248:
    charge(ctx, 23);
    a0 = 0;
    a1 = 12;
    a2 = 10;
    a3 = s3;
    jal(ctx, 0x400258u, gen::fn_sub_3C58F0_003c58f0);
    s3 = v0;
    lw(v0, v0, 36);
    lw(s4, v0, 68);
    sw(s3, s4, 0);
    a0 = 4;
    a1 = 0;
    a2 = 0;
    a3 = 0;
    jal(ctx, 0x400280u, gen::fn_sub_3C44D0_003c44d0);
    lw(v1, v0, 36);
    sw(s5, v1, 0);
    sw(v0, s4, 4);
    sw(s5, s4, 8);
    s5 = 0;
    for (;;) {
        // 0x004002f0
        charge(ctx, 3);
        v0 = slt(s5, s2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x004002a4
        charge(ctx, 19);
        v0 = addu(s5, sp);
        v0 = addiu(v0, 248);
        lb(s7, v0, 0);
        a0 = s3;
        a1 = s7;
        a2 = 8;
        a3 = 0;
        jal(ctx, 0x4002C0u, gen::fn_nmCmdListAddRow_003c5a40);
        a1 = v0;
        v1 = dsll32(s7, 24);
        v1 = dsra32(v1, 24);
        lw(v0, v0, 20);
        lw(v0, v0, 28);
        sw(v1, v0, 4);
        a0 = s3;
        jal(ctx, 0x4002E4u, gen::fn_sub_3FFBB0_003ffbb0);
        s5 = addiu(s5, 1);
    }
    // 0x004002fc
    charge(ctx, 39);
    a0 = s3;
    a1 = 2048;
    jal(ctx, 0x400304u, gen::fn_sub_3C6D60_003c6d60);
    a0 = s3;
    a1 = s1;
    a2 = s0;
    jal(ctx, 0x400318u, gen::fn_nmCmdListSetPosition_003c6d40);
    a0 = s3;
    jal(ctx, 0x400324u, gen::fn_sub_3C6EE0_003c6ee0);
    a0 = s3;
    a1 = s6;
    jal(ctx, 0x400334u, gen::fn_nmCmdListSetDrawFunc_003c5e20);
    a0 = s3;
    a1 = fp;
    jal(ctx, 0x400344u, gen::fn_nmCmdListSetRowDrawFunc_003c5ee0);
    v1 = 10;
    lw(v0, s3, 36);
    sh(v1, v0, 6);
    lw(v0, s3, 36);
    sh(v1, v0, 8);
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
    sp = addiu(sp, 0x100);
}

// 0x00418C10 sub_418C10 -- 92 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Task callback: sub_1A4580 on the current root (sub_198590); returns 1.
void sub_418C10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x00418c10
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    jal(ctx, 0x418C20u, gen::fn_sub_198590_00198590);
    lw(v1, s0, 0);
    lw(a0, v1, 12);
    v1 = 0xFFFF;
    div(a0, v1);
    mflo(v1);
    mtc1(v1, f0);
    cvt_s_w(f12, f0);
    a0 = v0;
    jal(ctx, 0x418C4Cu, gen::fn_sub_1A4580_001a4580);
    v0 = 1;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00419B80 sub_419B80 -- 140 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Task callback: when a0+56 has a clump, re-parent it to the field camera's frame (sub_4CB7F0 on +264), then
// sub_1A4580 on the root; returns 1.
void sub_419B80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x00419b80
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, a0, 56);
    if (v0 != 0) {
        // 0x00419bac
        charge(ctx, 6);
        a0 = 20;
        jal(ctx, 0x419BB0u, gen::fn_sub_3B5D50_003b5d50);
        s0 = v0;
        if (s0 != 0) {
            // 0x00419bc4
            charge(ctx, 11);
            lw(a0, s1, 56);
            lw(a1, s0, 264);
            a2 = 0;
            jal(ctx, 0x419BD0u, gen::fn_sub_4CB7F0_004cb7f0);
            jal(ctx, 0x419BD8u, gen::fn_sub_198590_00198590);
            a0 = v0;
            lwc1(f12, s0, 260);
            jal(ctx, 0x419BE8u, gen::fn_sub_1A4580_001a4580);
        }
        // 0x00419bf0
        charge(ctx, 1);
        v0 = 1;
    } else {
        // 0x00419ba0
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x00419bf4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0041A310 sub_41A310 -- 212 bytes; frame 0x60: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// For each atomic of the clump a1+4 -> +8, set two material colours (0x6B2F18 / 0x6B2F28) through sub_4BDDE0;
// returns 1.
void sub_41A310(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x0041a310
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a1, 4);
    lw(s0, v0, 8);
    v0 = 0x6B0000;
    ld(v1, v0, 12056);  // 0x6B2F18
    v0 = 0x6B0000;
    lwc1(f0, v0, 12064);  // 0x6B2F20
    sd(v1, sp, 0x50);
    swc1(f0, sp, 0x58);
    v0 = 0x6B0000;
    ld(v1, v0, 12072);  // 0x6B2F28
    v0 = 0x6B0000;
    lwc1(f0, v0, 12080);  // 0x6B2F30
    sd(v1, sp, 0x40);
    swc1(f0, sp, 0x48);
    s1 = 0;
    for (;;) {
        // 0x0041a3b4
        charge(ctx, 4);
        lw(v0, s0, 4);
        v0 = slt(s1, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0041a368
        charge(ctx, 19);
        v0 = sll(s1, 2);
        v0 = addu(s0, v0);
        lw(v0, v0, 8);
        lw(s2, v0, 8);
        v0 = 0x420C0000;
        mtc1(v0, f12);
        a0 = addiu(s2, 16);
        a1 = addiu(sp, 0x50);
        a2 = 0;
        jal(ctx, 0x41A38Cu, gen::fn_sub_4BDDE0_004bdde0);
        v0 = 0x43340000;
        mtc1(v0, f12);
        a0 = addiu(s2, 16);
        a1 = addiu(sp, 0x40);
        a2 = 1;
        jal(ctx, 0x41A3A8u, gen::fn_sub_4BDDE0_004bdde0);
        s1 = addiu(s1, 1);
    }
    // 0x0041a3c4
    charge(ctx, 8);
    v0 = 1;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x004FC168 _sceMpegPictureData0 -- 576 bytes; frame 0x80: s3 sp+0x30, s2 sp+0x20, s1 sp+0x10, s0 sp+0x0, ra sp+0x70, s6 sp+0x60, s5 sp+0x50, s4 sp+0x40
// libmpeg: decode a picture's slices on the IPU (the slice loop, motion compensation by _doMC, the CSC / DMA hand-off
// and the "Skip to the next picture" error path).
void _sceMpegPictureData0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x004fc168
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(s3, sp, 0x30);
    sd(s2, sp, 0x20);
    s3 = 1;
    sd(s1, sp, 0x10);
    s2 = 3;
    sd(s0, sp, 0x0);
    s1 = a0;
    sd(ra, sp, 0x70);
    sd(s6, sp, 0x60);
    sd(s5, sp, 0x50);
    sd(s4, sp, 0x40);
    sw(zero, s1, 2080);
    lw(v0, s1, 320);
    lw(a0, s1, 316);
    lw(v1, s1, 388);
    mult(s0, a0, v0);
    sw(zero, s1, 2084);
    v1 = v1 ^ 0x3;
    v0 = sra(s0, 1);
    if (v1 != 0) s0 = v0;
    for (;;) {
        // 0x004fc1c0
        charge(ctx, 1);
        a0 = s1;
        for (;;) {
            // 0x004fc1c4
            charge(ctx, 5);
            a1 = s0;
            jal(ctx, 0x4FC1C4u, gen::fn__slice0_004fc3a8);
            s5 = v0;
            a0 = s1;
            if (s5 != s3) {
                break;
            }
            backedge(ctx);
        }
        // 0x004fc1d8
        charge(ctx, 2);
        if (s5 != s2) {
            break;
        }
        backedge(ctx);
    }
    // 0x004fc1e0
    charge(ctx, 9);
    s6 = 1;
    jal(ctx, 0x4FC1E0u, gen::fn__waitIpuIdle_004fd868);
    a0 = s1;
    jal(ctx, 0x4FC1E8u, gen::fn__waitIpuIdle_004fd868);
    v0 = 0x10000000;
    v0 = v0 | 0xB020;
    lw(v1, v0, 0);  // 0x1000B020
    v0 = 0x10000000;
    if (v1 != 0) {
        // 0x004fc204
        charge(ctx, 5);
        v0 = v0 | 0x2010;
        lw(v1, v0, 0);
        v1 = v1 & 0x4000;
        v0 = 0x10000000;
        if (v1 == 0) {
            // 0x004fc218
            charge(ctx, 8);
            s4 = 0x10000000;
            s3 = 0x10000000;
            s2 = 0x10000000;
            s0 = 0x10000000;
            s4 = s4 | 0xB420;
            s3 = s3 | 0xB400;
            s2 = s2 | 0xB020;
            s0 = s0 | 0x2010;
            for (;;) {
                // 0x004fc238
                charge(ctx, 3);
                lw(v0, s4, 0);
                if (v0 != 0) {
                    lw(v0, s1, 2168);
                } else {
                    // 0x004fc244
                    charge(ctx, 4);
                    lw(v0, s3, 0);
                    v0 = v0 & 0x100;
                    if (v0 != 0) {
                        lw(v0, s1, 2168);
                    } else {
                        // 0x004fc254
                        charge(ctx, 3);
                        link(ctx, 0x4FC254u);  // $ra first: the delay slot below depends on it
                        lw(a0, s1, 2152);
                        call(ctx, gen::fn__sceMpegDispatchMpegCbNodata_00500d88);
                        lw(v0, s1, 2168);
                    }
                }
                // 0x004fc260
                charge(ctx, 2);
                if (v0 != 0) {
                    goto L_004fc2c8;
                }
                // 0x004fc268
                charge(ctx, 3);
                lw(v0, s2, 0);
                cc = v0 == 0;  // the condition, before the delay slot changes it
                v0 = 0x10000000;
                if (cc) {
                    goto L_004fc288;
                }
                // 0x004fc274
                charge(ctx, 4);
                lw(v0, s0, 0);
                v0 = v0 & 0x4000;
                if (v0 != 0) {
                    break;
                }
                backedge(ctx);
            }
            goto L_004fc284;
        }
    L_004fc288:
        charge(ctx, 9);
        v1 = 0x10000000;
        v0 = v0 | 0x2020;
        v1 = v1 | 0x2030;
        lw(a1, v0, 0);
        ld(a0, v1, 0);  // 0x10002030
        v0 = dsll32(a0, 0);
        v0 = dsra32(v0, 0);
        sw(v0, s1, 2120);
        if (i64(a0) >= 0) {
            // 0x004fc2d8
            charge(ctx, 1);
            v0 = 32;
        } else {
            // 0x004fc2ac
            charge(ctx, 3);
            v1 = a1 & 0x1F;
            v0 = 32;
            if (v1 == 0) {
                // 0x004fc2c0
                charge(ctx, 2);
                v0 = 0;
            } else {
                // 0x004fc2b8
                charge(ctx, 2);
                v0 = subu(v0, v1);
            }
        }
        // 0x004fc2dc
        charge(ctx, 7);
        sw(v0, s1, 2124);
        v0 = 0x10000000;
        v0 = v0 | 0x2010;
        lw(v1, v0, 0);  // 0x10002010
        v1 = v1 & 0x4000;
        a0 = s1;
        if (v1 != 0) {
            // 0x004fc2f8
            charge(ctx, 2);
            s6 = 0;
            jal(ctx, 0x4FC2F8u, gen::fn__sceMpegErrorBdec_005025a0);
        }
        // 0x004fc300
        charge(ctx, 1);
        v0 = s6;
        goto L_004fc304;
    }
L_004fc284:
    charge(ctx, 1);
    v0 = 0x10000000;
    goto L_004fc288;
L_004fc2c8:
    charge(ctx, 4);
    jal(ctx, 0x4FC2C8u, gen::fn__sceMpegStopIpuDma_00502500);
    v0 = 0;
L_004fc304:
    charge(ctx, 2);
    v1 = 0x10000000;
    if (v0 == 0) {
        // 0x004fc30c
        charge(ctx, 3);
        lw(v0, s1, 2168);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = 4;
        if (!cc) {
            // 0x004fc318
            charge(ctx, 2);
            s5 = 2;
            v1 = 0x10000000;
            goto L_004fc320;
        }
        // 0x004fc380 (the shared epilogue, written out on this path)
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
        return;
    }
L_004fc320:
    charge(ctx, 4);
    s0 = addiu(s5, -1);
    s2 = sltiu(s5, 1);
    v1 = v1 | 0xD400;
    for (;;) {
        // 0x004fc330
        charge(ctx, 7);
        lw(v0, v1, 0);
        v0 = srl(v0, 8);
        v0 = v0 & 0x1;
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004fc34c
    charge(ctx, 2);
    v0 = sltiu(s0, 2);
    if (s5 == 0) {
        // 0x004fc354
        charge(ctx, 5);
        lw(a1, s1, 2080);
        a0 = s1;
        a1 = sltiu(a1, 1);
        jal(ctx, 0x4FC35Cu, gen::fn__doMC_004fbf48);
        v0 = sltiu(s0, 2);
    }
    // 0x004fc368
    charge(ctx, 2);
    a0 = s1;
    if (v0 != 0) {
        // 0x004fc370
        charge(ctx, 3);
        a1 = 0x7C0000;
        a1 = addiu(a1, -10912);  // "= Skip to the next picture ="
        jal(ctx, 0x4FC374u, gen::fn__sceMpegError_00502668);
    }
    // 0x004fc37c
    charge(ctx, 1);
    v0 = s2;
    // 0x004fc380 (the shared epilogue, written out on this path)
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

// 0x004FD740 _sceMpegPeepBit -- 140 bytes; frame 0x30: s1 sp+0x10, s0 sp+0x0, ra sp+0x20
// libmpeg: peek a1 bits of the IPU bitstream (IPU_TOP, waiting while the IPU is busy).
void _sceMpegPeepBit(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004fd740
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x20);
    s0 = a0;
    lw(v0, s0, 2088);
    s1 = a1;
    if (v0 == 0) {
        // 0x004fd760
        charge(ctx, 4);
        lw(v0, s0, 2124);
        v0 = slt(v0, s1);
        if (v0 != 0) {
            goto L_004fd770;
        }
        lw(v1, s0, 2120);
        // 0x004fd7b0 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        v0 = subu(0, s1);
        ld(ra, sp, 0x20);
        ld(s1, sp, 0x10);
        v0 = srlv(v1, v0);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
L_004fd770:
    charge(ctx, 16);
    a0 = s0;
    jal(ctx, 0x4FD770u, gen::fn__waitIpuIdle_004fd868);
    v0 = 0x10000000;
    v1 = 0x40000000;
    v0 = v0 | 0x2000;
    a0 = s0;
    sw(v1, v0, 0);  // 0x10002000
    sw(zero, s0, 2088);
    link(ctx, 0x4FD790u);  // $ra first: the delay slot below depends on it
    sw(v1, s0, 2092);
    call(ctx, gen::fn__sceMpegWaitIpuIdle64_004fd4d8);
    v0 = dsll32(v0, 0);
    v0 = dsra32(v0, 0);
    v1 = 32;
    sw(v0, s0, 2120);
    sw(v1, s0, 2124);
    lw(v1, s0, 2120);
    // 0x004fd7b0 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = subu(0, s1);
    ld(ra, sp, 0x20);
    ld(s1, sp, 0x10);
    v0 = srlv(v1, v0);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x004FF9D0 j__sceMpegFlushBuf_0 -- 8 bytes; leaf frame (no stack)
// libmpeg: tail jump to _sceMpegFlushBuf.
void j__sceMpegFlushBuf_0(EEContext& ctx) {
    using namespace hg;
    // 0x004ff9d0
    enter(ctx, 2);  // entry check point + this block's cycles
    gen::fn__sceMpegFlushBuf_004fd7d0(ctx);  // tail call
}

// 0x004FF9D8 _sceMpegNextHeader -- 340 bytes; frame 0xB0: s7 sp+0x90, s6 sp+0x80, s5 sp+0x70, s4 sp+0x60, s3 sp+0x50, s2 sp+0x40, s0 sp+0x20, ra sp+0xA0, s1 sp+0x30
// libmpeg: find the next start code and parse the header it opens (sequence, GOP, picture, extension / user data).
void _sceMpegNextHeader(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x004ff9d8
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    sd(s7, sp, 0x90);
    sd(s6, sp, 0x80);
    s7 = 435;
    sd(s5, sp, 0x70);
    s6 = 5;
    sd(s4, sp, 0x60);
    s5 = 256;
    sd(s3, sp, 0x50);
    s4 = 439;
    sd(s2, sp, 0x40);
    s3 = 440;
    sd(s0, sp, 0x20);
    s2 = si(-1);
    sd(ra, sp, 0xA0);
    s0 = a0;
    sd(s1, sp, 0x30);
    lw(v0, s0, 2168);
    for (;;) {
        // 0x004ffa20
        charge(ctx, 2);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = si(-1);
        if (!cc) {
            // 0x004ffa28
            charge(ctx, 5);
            a0 = s0;
            s1 = 1;
            jal(ctx, 0x4FFA2Cu, gen::fn_flushByteBoundary_004ffb38);
            a0 = s0;
            for (;;) {
                // 0x004ffa4c
                charge(ctx, 4);
                a1 = 24;
                jal(ctx, 0x4FFA4Cu, gen::fn__sceMpegPeepBit_004fd740);
                a0 = s0;
                if (v0 != s1) {
                    // 0x004ffa5c
                    charge(ctx, 3);
                    lw(v0, s0, 2168);
                    if (v0 == 0) {
                        backedge(ctx);
                        // 0x004ffa40
                        charge(ctx, 3);
                        a1 = 8;
                        jal(ctx, 0x4FFA40u, gen::fn_j__sceMpegFlushBuf_0_004ff9d0);
                        a0 = s0;
                        continue;
                    }
                }
                break;
            }
            // 0x004ffa68
            charge(ctx, 5);
            a1 = 32;
            jal(ctx, 0x4FFA68u, gen::fn__sceMpegNextBit_004fd658);
            v1 = v0;
            v0 = sltiu(v1, 436);
            if (v1 == s7) {
                // 0x004ffaac
                charge(ctx, 4);
                a0 = s0;
                jal(ctx, 0x4FFAACu, gen::fn__sequenceHeader_004feee0);
                lw(v0, s0, 2168);
                backedge(ctx);
                continue;
            }
            // 0x004ffa7c
            charge(ctx, 2);
            if (v0 != 0) {
                // 0x004ffa84
                charge(ctx, 2);
                if (v1 == s5) {
                    goto L_004ffacc;
                }
                // 0x004ffa8c
                charge(ctx, 2);
                lw(v0, s0, 2168);
                backedge(ctx);
                continue;
            }
            // 0x004ffa94
            charge(ctx, 2);
            v0 = 0;
            if (v1 != s4) {
                // 0x004ffa9c
                charge(ctx, 2);
                if (v1 == s3) {
                    // 0x004ffabc
                    charge(ctx, 4);
                    a0 = s0;
                    jal(ctx, 0x4FFABCu, gen::fn__groupOfPicturesHeader_004ff190);
                    lw(v0, s0, 2168);
                    backedge(ctx);
                } else {
                    // 0x004ffaa4
                    charge(ctx, 2);
                    lw(v0, s0, 2168);
                    backedge(ctx);
                }
                continue;
            }
        }
        break;
    }
    // 0x004ffb00 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0xA0);
    ld(s7, sp, 0x90);
    ld(s6, sp, 0x80);
    ld(s5, sp, 0x70);
    ld(s4, sp, 0x60);
    ld(s3, sp, 0x50);
    ld(s2, sp, 0x40);
    ld(s1, sp, 0x30);
    ld(s0, sp, 0x20);
    sp = addiu(sp, 0xB0);
    return;
L_004ffacc:
    charge(ctx, 13);
    a0 = s0;
    jal(ctx, 0x4FFACCu, gen::fn__pictureHeader_004ff230);
    lw(a0, s0, 2152);
    a1 = sp;
    sw(s6, sp, 0x0);
    sd(s2, sp, 0x10);
    link(ctx, 0x4FFAE4u);  // $ra first: the delay slot below depends on it
    sd(s2, sp, 0x8);
    call(ctx, gen::fn__sceMpegDispatchMpegCallback_00500d10);
    ld(v0, sp, 0x10);
    ld(v1, sp, 0x8);
    sd(v0, s0, 2112);
    sd(v1, s0, 2104);
    lw(v0, s0, 352);
    // 0x004ffb00 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0xA0);
    ld(s7, sp, 0x90);
    ld(s6, sp, 0x80);
    ld(s5, sp, 0x70);
    ld(s4, sp, 0x60);
    ld(s3, sp, 0x50);
    ld(s2, sp, 0x40);
    ld(s1, sp, 0x30);
    ld(s0, sp, 0x20);
    sp = addiu(sp, 0xB0);
}

// 0x004FFB38 flushByteBoundary -- 80 bytes; frame 0x20: s0 sp+0x0, ra sp+0x10
// libmpeg: flush to the next byte boundary (IPU_BP & 7).
void flushByteBoundary(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ffb38
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    s0 = a0;
    jal(ctx, 0x4FFB44u, gen::fn__waitIpuIdle_0_004ff998);
    v0 = 0x10000000;
    v0 = v0 | 0x2020;
    lw(v1, v0, 0);  // 0x10002020
    v1 = v1 & 0x7;
    v1 = subu(0, v1);
    a1 = v1 & 0x7;
    ld(ra, sp, 0x10);
    if (a1 == 0) {
        // 0x004ffb7c
        charge(ctx, 3);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x004ffb6c
    charge(ctx, 4);
    a0 = s0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
    gen::fn_j__sceMpegFlushBuf_0_004ff9d0(ctx);  // tail call
}

// 0x004FFDA8 _clearOnce -- 204 bytes; leaf frame (no stack)
// libmpeg: per-buffer-type setup of the decoder ("Unknown buff type." otherwise).
void _clearOnce(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x004ffda8
    enter(ctx, 13);  // entry check point + this block's cycles
    a1 = 0x10000000;
    v1 = lui(0xFF7F);
    a1 = a1 | 0x2010;
    v1 = v1 | 0xFFFF;
    lw(v0, a1, 0);  // 0x10002010
    a2 = 0x800000;
    a3 = a0;
    v0 = v0 & v1;
    v0 = v0 | a2;
    sw(v0, a1, 0);  // 0x10002010
    lw(v1, a3, 2172);
    v0 = 1;
    if (v1 == 0) {
        // 0x004ffddc
        charge(ctx, 16);
        v0 = 0x70000000;
        v1 = 0x70000000;
        a0 = 0x70000000;
        a1 = 0x70000000;
        a2 = 0x70000000;
        v0 = v0 | 0x3600;
        v1 = v1 | 0x1800;
        a0 = a0 | 0x1B00;
        a1 = a1 | 0x3300;
        sw(v0, a3, 2096);
        sw(a2, a3, 1440);
        sw(v1, a3, 1444);
        sw(a0, a3, 1760);
        sw(a1, a3, 1764);
        sw(zero, a3, 2080);
        return;
    }
    // 0x004ffe1c
    charge(ctx, 2);
    a1 = 0x7C0000;
    if (v1 != v0) {
        // 0x004ffe68
        charge(ctx, 3);
        a0 = a3;
        a1 = addiu(a1, -10208);
        gen::fn__sceMpegError_00502668(ctx);  // tail call
        return;
    }
    // 0x004ffe24
    charge(ctx, 17);
    v0 = 0xFFF0000;
    a0 = addiu(a3, 2176);
    v0 = v0 | 0xFFFF;
    v1 = addiu(a3, 2944);
    v1 = v1 & v0;
    a0 = a0 & v0;
    a1 = 0x30000000;
    v0 = addiu(a3, 3712);
    v1 = v1 | a1;
    a0 = a0 | a1;
    sw(v0, a3, 2096);
    sw(a0, a3, 1444);
    sw(v1, a3, 1764);
    sw(zero, a3, 2080);
    sw(zero, a3, 1440);
    sw(zero, a3, 1760);
}

// 0x004FFE78 sceMpegCreate -- 568 bytes; frame 0x50: s3 sp+0x30, s1 sp+0x10, s0 sp+0x0, s2 sp+0x20, ra sp+0x40
// libmpeg: create a decoder in the work area a1 (size a2): clears it, lays out the bitstream / IDCT / reference
// buffers ("internal alignment error" checks), installs the default DMA stop / restart hooks and resets it.
void sceMpegCreate(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ffe78
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s3, sp, 0x30);
    sd(s1, sp, 0x10);
    s3 = a0;
    sd(s0, sp, 0x0);
    s1 = a2;
    s0 = a1;
    sd(s2, sp, 0x20);
    a0 = s0;
    sd(ra, sp, 0x40);
    a1 = 0;
    jal(ctx, 0x4FFEA0u, gen::fn_memset_00521408);
    v1 = addiu(s0, 3);
    v1 = srl(v1, 2);
    s2 = sll(v1, 2);
    s0 = subu(s2, s0);
    a2 = subu(s1, s0);
    v0 = slti(a2, 6560);
    a1 = 0x7C0000;
    if (v0 == 0) {
        // 0x004ffedc
        charge(ctx, 97);
        s1 = addiu(s2, 280);
        sw(s2, s3, 64);
        a2 = addiu(a2, -6560);
        a0 = s1;
        a1 = addiu(s2, 6560);
        s0 = si(-1);
        jal(ctx, 0x4FFEF0u, gen::fn__sceMpegAlalcInit_00501068);
        sw(zero, s3, 0);
        v0 = si(-1);
        sw(zero, s3, 4);
        v1 = 0x500000;
        sw(zero, s3, 8);
        t0 = 0x500000;
        v1 = addiu(v1, 4392);  // &_sceMpegDefaultStopDMA
        t0 = addiu(t0, 4432);  // &_sceMpegDefaultRestartDMA
        sd(v0, s3, 16);
        a3 = 8;
        sd(v0, s3, 24);
        a0 = s2;
        sd(zero, s3, 32);
        a1 = s1;
        sd(v0, s3, 40);
        a2 = 2048;
        sd(v0, s3, 48);
        sd(zero, s3, 56);
        sw(zero, s2, 200);
        sw(zero, s2, 204);
        sw(zero, s2, 208);
        sw(zero, s2, 212);
        sw(zero, s2, 216);
        sw(zero, s2, 220);
        sw(zero, s2, 224);
        sw(zero, s2, 228);
        sw(zero, s2, 232);
        sw(zero, s2, 236);
        sw(zero, s2, 240);
        sw(zero, s2, 244);
        sw(zero, s2, 248);
        sw(zero, s2, 252);
        sw(zero, s2, 264);
        sw(zero, s2, 12);
        sw(zero, s2, 24);
        sw(zero, s2, 60);
        sw(zero, s2, 72);
        sw(zero, s2, 84);
        sd(v0, s2, 256);
        sw(v1, s2, 36);
        link(ctx, 0x4FFF98u);  // $ra first: the delay slot below depends on it
        sw(t0, s2, 48);
        call(ctx, gen::fn__sceMpegAlalcAlloc_005010a0);
        v1 = 1;
        sw(zero, s2, 100);
        sw(zero, s2, 268);
        a0 = s2;
        sw(zero, s2, 272);
        sw(zero, s2, 276);
        sw(zero, s2, 140);
        sd(zero, s2, 144);
        sw(s0, s2, 152);
        sd(zero, s2, 160);
        sw(zero, s2, 156);
        sw(zero, s2, 192);
        sw(s0, s2, 168);
        sw(s0, s2, 172);
        sw(s0, s2, 176);
        sw(s3, s2, 2152);
        sw(v0, s2, 96);
        link(ctx, 0x4FFFE4u);  // $ra first: the delay slot below depends on it
        sw(v1, s2, 196);
        call(ctx, gen::fn__clearOnce_004ffda8);
        a0 = s3;
        jal(ctx, 0x4FFFECu, gen::fn_sceMpegReset_00500bb8);
        a0 = s3;
        jal(ctx, 0x4FFFF4u, gen::fn_sceMpegClearRefBuff_00500e48);
        v1 = addiu(s2, 504);
        v0 = addiu(s2, 608);
        a1 = addiu(s2, 712);
        a2 = addiu(s2, 816);
        a3 = addiu(s2, 920);
        t0 = addiu(s2, 1024);
        t1 = addiu(s2, 1128);
        t2 = addiu(s2, 1232);
        t3 = addiu(s2, 1336);
        sw(v1, s2, 456);
        sw(v0, s2, 460);
        a0 = s1;
        sw(a1, s2, 468);
        sw(a2, s2, 472);
        sw(a3, s2, 476);
        sw(t0, s2, 484);
        sw(t1, s2, 488);
        sw(t2, s2, 492);
        link(ctx, 0x500044u);  // $ra first: the delay slot below depends on it
        sw(t3, s2, 500);
        call(ctx, gen::fn__sceMpegAlalcSetDynamic_00501080);
        sw(s0, s2, 2144);
        a2 = s2 & 0x3C;
        sw(zero, s2, 2140);
        sw(zero, s2, 2148);
        if (a2 != 0) {
            // 0x00500060
            charge(ctx, 4);
            a1 = 0x7C0000;
            a0 = s2;
            a1 = addiu(a1, -10184);  // "internal alignment error. _bstag:%d"
            goto L_00500080;
        }
        // 0x00500070
        charge(ctx, 2);
        a1 = 0x7C0000;
        if (a2 == 0) {
            // 0x00500090
            charge(ctx, 1);
            v0 = 1;
        } else {
            // 0x00500078
            charge(ctx, 2);
            a0 = s2;
            a1 = addiu(a1, -10144);
        L_00500080:
            charge(ctx, 4);
            jal(ctx, 0x500080u, gen::fn__sceMpegError1_005026c0);
            v0 = 0;
        }
    } else {
        // 0x004ffec8
        charge(ctx, 5);
        a0 = s2;
        a1 = addiu(a1, -10104);
        jal(ctx, 0x4FFECCu, gen::fn__sceMpegError_00502668);
        v0 = 0;
    }
    // 0x00500094 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00500A20 sceMpegInit -- 176 bytes; frame 0x10: ra sp+0x0
// libmpeg: one-time IPU / DMA channel 3 and 4 setup with interrupts off (DIntr / sceIpuInit / EIntr).
void sceMpegInit(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00500a20
    enter(ctx, 31);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x500A28u, gen::fn_DIntr_0050d3a0);
    t1 = 0x10000000;
    a0 = 0x10000;
    t1 = t1 | 0xF520;
    t2 = 0x10000000;
    lw(v1, t1, 0);  // 0x1000F520
    t2 = t2 | 0xF590;
    a2 = 0x10000000;
    t0 = lui(0xFFFF);
    v1 = v1 | a0;
    a2 = a2 | 0xB000;
    sw(v1, t2, 0);  // 0x1000F590
    t0 = t0 | 0xFEFF;
    a1 = 0x10000000;
    a3 = lui(0xFFFE);
    lw(a0, a2, 0);  // 0x1000B000
    a1 = a1 | 0xB400;
    a3 = a3 | 0xFFFF;
    a0 = a0 & t0;
    sw(a0, a2, 0);  // 0x1000B000
    lw(v1, a1, 0);  // 0x1000B400
    v1 = v1 & t0;
    sw(v1, a1, 0);  // 0x1000B400
    lw(a0, t1, 0);  // 0x1000F520
    a0 = a0 & a3;
    sw(a0, t2, 0);  // 0x1000F590
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = 0x10000000;
    if (!cc) {
        // 0x00500a9c
        charge(ctx, 3);
        jal(ctx, 0x500A9Cu, gen::fn_EIntr_0050d3f0);
        v0 = 0x10000000;
    }
    // 0x00500aa8
    charge(ctx, 10);
    v1 = 0x10000000;
    v0 = v0 | 0xB020;
    v1 = v1 | 0xB420;
    sw(zero, v0, 0);
    link(ctx, 0x500AB8u);  // $ra first: the delay slot below depends on it
    sw(zero, v1, 0);
    call(ctx, gen::fn_sceIpuInit_00502b08);
    ld(ra, sp, 0x0);
    v0 = 1;
    sp = addiu(sp, 0x10);
}

// 0x00500BB8 sceMpegReset -- 124 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0
// libmpeg: reset a decoder (_clearEach, the IPU control word).
void sceMpegReset(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00500bb8
    enter(ctx, 31);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = a0;
    sd(ra, sp, 0x10);
    v1 = si(-1);
    sd(s0, sp, 0x0);
    lw(s0, v0, 64);
    sw(zero, s0, 2168);
    a0 = s0;
    sw(zero, s0, 0);
    sw(zero, s0, 4);
    sw(zero, s0, 8);
    sw(zero, v0, 8);
    sw(zero, s0, 192);
    link(ctx, 0x500BECu);  // $ra first: the delay slot below depends on it
    sw(v1, s0, 152);
    call(ctx, gen::fn__clearEach_005001b0);
    sw(zero, s0, 2136);
    a1 = 0x10000000;
    sw(zero, s0, 296);
    a1 = a1 | 0x2010;
    a0 = lui(0xFF7F);
    a2 = 0x800000;
    lw(v1, a1, 0);  // 0x10002010
    a0 = a0 | 0xFFFF;
    ld(ra, sp, 0x10);
    v0 = 1;
    v1 = v1 & a0;
    ld(s0, sp, 0x0);
    v1 = v1 | a2;
    sw(v1, a1, 0);  // 0x10002010
    sp = addiu(sp, 0x20);
}

// 0x00501090 _sceMpegAlalcFree -- 12 bytes; leaf frame (no stack)
// libmpeg: allocator free (returns 0).
void _sceMpegAlalcFree(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00501090
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, a0, 12);
    sw(v0, a0, 8);
}

// 0x005010A0 _sceMpegAlalcAlloc -- 108 bytes; frame 0x10: ra sp+0x0
// libmpeg: bump allocator on the work area ("work area is too small" when it runs out).
void _sceMpegAlalcAlloc(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005010a0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    t0 = a0;
    sd(ra, sp, 0x0);
    if (a3 == 0) {
        brk(ctx, 0x5010B0u, 0x7u);
    }
    // 0x005010b4
    charge(ctx, 13);
    lw(v0, a1, 8);
    lw(a0, a1, 4);
    v0 = addu(v0, a3);
    lw(v1, a1, 0);
    v0 = addiu(v0, -1);
    divu(v0, a3);
    v1 = addu(v1, a0);
    mflo(v0);
    mult(v0, v0, a3);
    a0 = addu(v0, a2);
    v1 = sltu(v1, a0);
    if (v1 != 0) {
        a1 = 0x7C0000;
        // 0x005010f0
        charge(ctx, 4);
        a0 = t0;
        a1 = addiu(a1, -9816);
        jal(ctx, 0x5010F4u, gen::fn__sceMpegError_00502668);
        v0 = 0;
    } else {
        // 0x005010e8
        charge(ctx, 2);
        sw(a0, a1, 8);
    }
    // 0x00501100 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00501BA8 _sceMpegOutputFrame -- 144 bytes; frame 0x20: s0 sp+0x0, ra sp+0x10
// libmpeg: output a decoded frame (frame or field picture: _dispRefImage / _dispRefImageField).
void _sceMpegOutputFrame(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00501ba8
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a3 = a1;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    s0 = a0;
    if (a2 != 0) {
        // 0x00501bc0
        charge(ctx, 4);
        lw(v0, s0, 388);
        v1 = 3;
        cc = v0 != v1;  // the condition, before the delay slot changes it
        lw(v0, s0, 352);
        if (cc) {
            // 0x00501bf0
            charge(ctx, 2);
            if (v0 != v1) {
                lw(a1, s0, 472);
                // 0x00501c04
                charge(ctx, 1);
                lw(a2, s0, 488);
            } else {
                // 0x00501bf8
                charge(ctx, 3);
                lw(a1, s0, 484);
                lw(a2, s0, 500);
            }
            // 0x00501c08
            charge(ctx, 3);
            a3 = addiu(a3, -1);
            a0 = s0;
            jal(ctx, 0x501C0Cu, gen::fn__dispRefImageField_005016c8);
            goto L_00501c14;
        }
        // 0x00501bd0
        charge(ctx, 2);
        if (v0 != v1) {
            lw(a1, s0, 456);
        } else {
            // 0x00501bd8
            charge(ctx, 1);
            lw(a1, s0, 468);
        }
        // 0x00501bdc
        charge(ctx, 5);
        a2 = addiu(a3, -1);
        a0 = s0;
        jal(ctx, 0x501BE0u, gen::fn__dispRefImage_00501408);
        lw(v1, s0, 264);
        goto L_00501c18;
    }
L_00501c14:
    charge(ctx, 1);
    lw(v1, s0, 264);
L_00501c18:
    charge(ctx, 3);
    v0 = 1;
    ld(ra, sp, 0x10);
    if (v1 == v0) {
        // 0x00501c24
        charge(ctx, 2);
        v0 = 2;
        sw(v0, s0, 264);
    }
    // 0x00501c2c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00501DF8 _sceMpegCscStoreRefImage -- 1240 bytes; frame 0xD0: s3 sp+0x80, s2 sp+0x70, s0 sp+0x50, ra sp+0xC0, s6 sp+0xB0, s5 sp+0xA0, s4 sp+0x90, s1 sp+0x60
// libmpeg: colour-convert a reference picture to the output buffer through the IPU CSC and DMA channel 4, with its
// DMAC handler installed and removed around it.
void _sceMpegCscStoreRefImage(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00501df8
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0xD0);
    a2 = 2;
    sd(s3, sp, 0x80);
    sd(s2, sp, 0x70);
    sd(s0, sp, 0x50);
    s2 = a1;
    sd(ra, sp, 0xC0);
    s0 = a0;
    sd(s6, sp, 0xB0);
    a1 = sp;
    sd(s5, sp, 0xA0);
    sd(s4, sp, 0x90);
    sd(s1, sp, 0x60);
    lw(v1, s2, 12);
    lw(v0, s2, 16);
    lw(a0, s0, 2152);
    mult(s3, v1, v0);
    link(ctx, 0x501E3Cu);  // $ra first: the delay slot below depends on it
    sw(a2, sp, 0x0);
    call(ctx, gen::fn__sceMpegDispatchMpegCallback_00500d10);
    v1 = 0x10000000;
    v1 = v1 | 0x2010;
    lw(v0, v1, 0);  // 0x10002010
    v0 = v0 & 0x4000;
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = 0x40000000;
    if (!cc) {
        // 0x00501e5c
        charge(ctx, 2);
        at = 0x10000000;
        sw(v0, at, 8208);  // 0x10002010
    }
    // 0x00501e64
    charge(ctx, 3);
    v1 = 0x10000000;
    s5 = slti(s3, 1024);
    v1 = v1 | 0x2010;
    for (;;) {
        // 0x00501e70
        charge(ctx, 7);
        lw(v0, v1, 0);
        if (i64(v0) >= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00501e8c
    charge(ctx, 9);
    v0 = 0x10000000;
    v1 = 1;
    v0 = v0 | 0x2000;
    a0 = 0x10000000;
    sw(zero, v0, 0);  // 0x10002000
    a0 = a0 | 0x2010;
    sw(v1, s0, 2088);
    sw(zero, s0, 2092);
    for (;;) {
        // 0x00501eb0
        charge(ctx, 7);
        lw(v0, a0, 0);
        if (i64(v0) >= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00501ecc
    charge(ctx, 13);
    a0 = 0;
    s1 = 0xFFF0000;
    jal(ctx, 0x501ED0u, gen::fn__sceFlushCache_005033e0);
    s1 = s1 | 0xFFFF;
    v1 = 24;
    lw(v0, s2, 0);
    mult(v1, s3, v1);
    s4 = 0xFFFF;
    v0 = v0 & s1;
    sw(v0, sp, 0x24);
    a0 = sltu(s4, v1);
    sw(v1, sp, 0x20);
    if (a0 == 0) {
        // 0x00502100
        charge(ctx, 16);
        jal(ctx, 0x502100u, gen::fn_DIntr_0050d3a0);
        lw(a1, s2, 0);
        v1 = 0x10000000;
        v1 = v1 | 0xB410;
        a2 = 0x10000000;
        a1 = a1 & s1;
        a2 = a2 | 0xB420;
        sw(a1, v1, 0);  // 0x1000B410
        a0 = 0x10000000;
        a0 = a0 | 0xB400;
        a1 = 257;
        lw(v1, sp, 0x20);
        sw(v1, a2, 0);  // 0x1000B420
        sw(a1, a0, 0);  // 0x1000B400
        if (v0 != 0) {
            // 0x00502140
            charge(ctx, 2);
            jal(ctx, 0x502140u, gen::fn_EIntr_0050d3f0);
        }
        // 0x00502148
        charge(ctx, 2);
        sw(zero, sp, 0x20);
        if (s5 == 0) {
            // 0x00502284
            charge(ctx, 5);
            lw(a1, s0, 236);
            a2 = s3;
            a0 = s0;
            jal(ctx, 0x50228Cu, gen::fn__doCSC2_00501c38);
            lw(a0, s0, 2152);
        } else {
            // 0x00502150
            charge(ctx, 6);
            v1 = 0x10000000;
            lw(s1, s0, 236);
            s4 = addiu(sp, 0x30);
            s2 = sll(s3, 6);
            v1 = v1 | 0x2010;
            for (;;) {
                // 0x00502168
                charge(ctx, 7);
                lw(v0, v1, 0);
                if (i64(v0) >= 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00502184
            charge(ctx, 17);
            jal(ctx, 0x502184u, gen::fn_DIntr_0050d3a0);
            v1 = 0xFFF0000;
            a1 = 0x10000000;
            v1 = v1 | 0xFFFF;
            a1 = a1 | 0xB010;
            v1 = s1 & v1;
            a0 = 0x10000000;
            sw(v1, a1, 0);  // 0x1000B010
            a0 = a0 | 0xB020;
            sw(s2, a0, 0);  // 0x1000B020
            v1 = 0x10000000;
            v1 = v1 | 0xB000;
            a0 = 256;
            sw(a0, v1, 0);  // 0x1000B000
            v1 = 0x70000000;
            if (v0 != 0) {
                // 0x005021c8
                charge(ctx, 3);
                jal(ctx, 0x5021C8u, gen::fn_EIntr_0050d3f0);
                v1 = 0x70000000;
            }
            // 0x005021d4
            charge(ctx, 9);
            v0 = 0x10000000;
            v1 = s3 | v1;
            v0 = v0 | 0x2000;
            sw(v1, v0, 0);  // 0x10002000
            a0 = lui(0xF000);
            v1 = v1 & a0;
            v0 = 0x20000000;
            sw(v1, s0, 2092);
            if (v1 != v0) {
                // 0x005021f8
                charge(ctx, 3);
                v0 = 0x30000000;
                cc = v1 == v0;  // the condition, before the delay slot changes it
                v0 = 0x40000000;
                if (cc) {
                    goto L_0050220c;
                }
                // 0x00502204
                charge(ctx, 2);
                cc = v1 != v0;  // the condition, before the delay slot changes it
                v0 = 1;
                if (!cc) {
                    goto L_0050220c;
                }
                // 0x00502214
                charge(ctx, 1);
                sw(v0, s0, 2088);
                goto L_00502218;
            }
        L_0050220c:
            charge(ctx, 2);
            sw(zero, s0, 2088);
        L_00502218:
            charge(ctx, 8);
            v0 = 4;
            lw(a0, s0, 2152);
            sw(v0, s4, 0);
            a1 = addiu(sp, 0x30);
            jal(ctx, 0x502224u, gen::fn__sceMpegDispatchMpegCallback_00500d10);
            v1 = 0x10000000;
            v1 = v1 | 0xB000;
            for (;;) {
                // 0x00502238
                charge(ctx, 7);
                lw(v0, v1, 0);
                v0 = srl(v0, 8);
                v0 = v0 & 0x1;
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00502254
            charge(ctx, 3);
            v1 = 0x10000000;
            v1 = v1 | 0x2010;
            for (;;) {
                // 0x00502260
                charge(ctx, 7);
                lw(v0, v1, 0);
                if (i64(v0) >= 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0050227c
            charge(ctx, 2);
            lw(a0, s0, 2152);
        }
    } else {
        // 0x00501f00
        charge(ctx, 28);
        a1 = 0x500000;
        a0 = 4;
        a1 = addiu(a1, 9240);  // &_ch4dma
        a2 = 0;
        a3 = addiu(sp, 0x20);
        jal(ctx, 0x501F10u, gen::fn__sceAddDmacHandler_0_00502e80);
        s6 = v0;
        v1 = 16;
        v0 = 0x10000000;
        a0 = 4;
        v0 = v0 | 0xE010;
        link(ctx, 0x501F2Cu);  // $ra first: the delay slot below depends on it
        sw(v1, v0, 0);
        call(ctx, gen::fn_EnableDmac_00503d78);
        jal(ctx, 0x501F34u, gen::fn_DIntr_0050d3a0);
        lw(a1, sp, 0x24);
        v1 = 0x10000000;
        v1 = v1 | 0xB410;
        a0 = 0x10000000;
        sw(a1, v1, 0);  // 0x1000B410
        a0 = a0 | 0xB420;
        sw(s4, a0, 0);  // 0x1000B420
        v1 = 0x10000000;
        v1 = v1 | 0xB400;
        a0 = 257;
        sw(a0, v1, 0);  // 0x1000B400
        cc = v0 == 0;  // the condition, before the delay slot changes it
        lw(v0, sp, 0x24);
        if (!cc) {
            // 0x00501f70
            charge(ctx, 3);
            jal(ctx, 0x501F70u, gen::fn_EIntr_0050d3f0);
            lw(v0, sp, 0x24);
        }
        // 0x00501f7c
        charge(ctx, 9);
        v1 = 0xF0000;
        lw(a0, sp, 0x20);
        v1 = v1 | 0xFFF0;
        v0 = addu(v0, v1);
        v0 = v0 & s1;
        a0 = subu(a0, s4);
        sw(v0, sp, 0x24);
        sw(a0, sp, 0x20);
        if (s5 == 0) {
            // 0x005020d4
            charge(ctx, 4);
            lw(a1, s0, 236);
            a2 = s3;
            a0 = s0;
            jal(ctx, 0x5020DCu, gen::fn__doCSC2_00501c38);
        } else {
            // 0x00501fa0
            charge(ctx, 6);
            v1 = 0x10000000;
            lw(s1, s0, 236);
            s4 = addiu(sp, 0x30);
            s2 = sll(s3, 6);
            v1 = v1 | 0x2010;
            for (;;) {
                // 0x00501fb8
                charge(ctx, 7);
                lw(v0, v1, 0);
                if (i64(v0) >= 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00501fd4
            charge(ctx, 17);
            jal(ctx, 0x501FD4u, gen::fn_DIntr_0050d3a0);
            v1 = 0xFFF0000;
            a1 = 0x10000000;
            v1 = v1 | 0xFFFF;
            a1 = a1 | 0xB010;
            v1 = s1 & v1;
            a0 = 0x10000000;
            sw(v1, a1, 0);  // 0x1000B010
            a0 = a0 | 0xB020;
            sw(s2, a0, 0);  // 0x1000B020
            v1 = 0x10000000;
            v1 = v1 | 0xB000;
            a0 = 256;
            sw(a0, v1, 0);  // 0x1000B000
            v1 = 0x70000000;
            if (v0 != 0) {
                // 0x00502018
                charge(ctx, 3);
                jal(ctx, 0x502018u, gen::fn_EIntr_0050d3f0);
                v1 = 0x70000000;
            }
            // 0x00502024
            charge(ctx, 9);
            v0 = 0x10000000;
            v1 = s3 | v1;
            v0 = v0 | 0x2000;
            sw(v1, v0, 0);  // 0x10002000
            a0 = lui(0xF000);
            v1 = v1 & a0;
            v0 = 0x20000000;
            sw(v1, s0, 2092);
            if (v1 != v0) {
                // 0x00502048
                charge(ctx, 3);
                v0 = 0x30000000;
                cc = v1 == v0;  // the condition, before the delay slot changes it
                v0 = 0x40000000;
                if (cc) {
                    goto L_0050205c;
                }
                // 0x00502054
                charge(ctx, 2);
                cc = v1 != v0;  // the condition, before the delay slot changes it
                v0 = 1;
                if (!cc) {
                    goto L_0050205c;
                }
                // 0x00502064
                charge(ctx, 1);
                sw(v0, s0, 2088);
                goto L_00502068;
            }
        L_0050205c:
            charge(ctx, 2);
            sw(zero, s0, 2088);
        L_00502068:
            charge(ctx, 8);
            v0 = 4;
            lw(a0, s0, 2152);
            sw(v0, s4, 0);
            a1 = addiu(sp, 0x30);
            jal(ctx, 0x502074u, gen::fn__sceMpegDispatchMpegCallback_00500d10);
            v1 = 0x10000000;
            v1 = v1 | 0xB000;
            for (;;) {
                // 0x00502088
                charge(ctx, 7);
                lw(v0, v1, 0);
                v0 = srl(v0, 8);
                v0 = v0 & 0x1;
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x005020a4
            charge(ctx, 3);
            v1 = 0x10000000;
            v1 = v1 | 0x2010;
            for (;;) {
                // 0x005020b0
                charge(ctx, 7);
                lw(v0, v1, 0);
                if (i64(v0) >= 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x005020cc
            charge(ctx, 2);
        }
        // 0x005020e4
        charge(ctx, 7);
        a0 = 4;
        jal(ctx, 0x5020E4u, gen::fn_DisableDmac_00503d10);
        a1 = s6;
        a0 = 4;
        jal(ctx, 0x5020F0u, gen::fn__sceRemoveDmacHandler_00502e90);
        lw(a0, s0, 2152);
    }
    // 0x00502298
    charge(ctx, 14);
    v0 = 3;
    sw(v0, sp, 0x0);
    a1 = sp;
    jal(ctx, 0x5022A0u, gen::fn__sceMpegDispatchMpegCallback_00500d10);
    ld(ra, sp, 0xC0);
    ld(s6, sp, 0xB0);
    ld(s5, sp, 0xA0);
    ld(s4, sp, 0x90);
    ld(s3, sp, 0x80);
    ld(s2, sp, 0x70);
    ld(s1, sp, 0x60);
    ld(s0, sp, 0x50);
    sp = addiu(sp, 0xD0);
}

// 0x00502E40 _sceAddIntcHandler -- 16 bytes; leaf frame (no stack)
// libkernel: AddIntcHandler syscall wrapper.
void _sceAddIntcHandler(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00502e40
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 16;
    syscall(ctx, 0x502E44u);
}

// 0x00502E90 _sceRemoveDmacHandler -- 16 bytes; leaf frame (no stack)
// libkernel: RemoveDmacHandler syscall wrapper.
void _sceRemoveDmacHandler(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00502e90
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 19;
    syscall(ctx, 0x502E94u);
}

// 0x00503080 _sceSleepThread -- 16 bytes; leaf frame (no stack)
// libkernel: SleepThread syscall wrapper.
void _sceSleepThread(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503080
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 50;
    syscall(ctx, 0x503084u);
}

// 0x00503CA8 EnableIntc -- 104 bytes; frame 0x30: s1 sp+0x10, ra sp+0x20, s0 sp+0x0
// libkernel: EnableIntc with interrupts off (DIntr / _sce_EnableIntc / EIntr when they were on).
void EnableIntc(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00503ca8
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x10);
    sd(ra, sp, 0x20);
    s1 = a0;
    sd(s0, sp, 0x0);
    mfc0(s0, 12);
    v0 = 0x10000;
    s0 = s0 & v0;
    if (s0 != 0) {
        // 0x00503cd0
        charge(ctx, 2);
        jal(ctx, 0x503CD0u, gen::fn_DIntr_0050d3a0);
    }
    // 0x00503cd8
    charge(ctx, 6);
    a0 = s1;
    jal(ctx, 0x503CD8u, gen::fn__sce_EnableIntc_00502ea0);
    s1 = v0;
    sync(ctx, 0);
    v0 = s1;
    if (s0 != 0) {
        // 0x00503cf0
        charge(ctx, 3);
        jal(ctx, 0x503CF0u, gen::fn_EIntr_0050d3f0);
        v0 = s1;
    }
    // 0x00503cfc (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00503D10 DisableDmac -- 104 bytes; frame 0x30: s1 sp+0x10, ra sp+0x20, s0 sp+0x0
// libkernel: DisableDmac with interrupts off (DIntr / _sce_DisableDmac / EIntr when they were on).
void DisableDmac(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00503d10
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x10);
    sd(ra, sp, 0x20);
    s1 = a0;
    sd(s0, sp, 0x0);
    mfc0(s0, 12);
    v0 = 0x10000;
    s0 = s0 & v0;
    if (s0 != 0) {
        // 0x00503d38
        charge(ctx, 2);
        jal(ctx, 0x503D38u, gen::fn_DIntr_0050d3a0);
    }
    // 0x00503d40
    charge(ctx, 6);
    a0 = s1;
    jal(ctx, 0x503D40u, gen::fn__sce_DisableDmac_00502ed0);
    s1 = v0;
    sync(ctx, 0);
    v0 = s1;
    if (s0 != 0) {
        // 0x00503d58
        charge(ctx, 3);
        jal(ctx, 0x503D58u, gen::fn_EIntr_0050d3f0);
        v0 = s1;
    }
    // 0x00503d64 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00504028 iWakeupThread -- 148 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0
// libkernel: iWakeupThread; for the calling thread's own semaphore-backed id it posts the wake-up ring
// (0x966100..) and signals instead of the syscall.
void iWakeupThread(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00504028
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sd(s0, sp, 0x0);
    v1 = si(-47);
    syscall(ctx, 0x504038u);
    s0 = v0;
    v0 = sltiu(s0, 256);
    if (s0 == a0) {
        // 0x00504058
        charge(ctx, 2);
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = 0x780000;
        if (!cc) {
            // 0x00504060
            charge(ctx, 3);
            lw(v1, v0, -2920);
            cc = v1 != 0;  // the condition, before the delay slot changes it
            v1 = 0x960000;
            if (!cc) {
                goto L_0050406c;
            }
            // 0x00504074
            charge(ctx, 14);
            a1 = 0x960000;
            v1 = addiu(v1, 24840);
            lw(a0, a1, 24832);  // 0x966100
            lw(v0, v1, 4);
            v0 = v0 & 0x1FF;
            a2 = sll(v0, 1);
            v0 = addiu(v0, 1);
            a1 = addu(v1, a2);
            sw(v0, v1, 4);
            v1 = a1;
            sb(zero, a1, 8);
            link(ctx, 0x5040A0u);  // $ra first: the delay slot below depends on it
            sb(s0, v1, 9);
            call(ctx, gen::fn__sceiSignalSema_00503190);
            v0 = s0;
            goto L_005040ac;
        }
    L_0050406c:
        charge(ctx, 2);
        v0 = si(-1);
    L_005040ac:
        charge(ctx, 1);
        ld(ra, sp, 0x10);
    } else {
        // 0x00504048
        charge(ctx, 4);
        jal(ctx, 0x504048u, gen::fn__sce_iWakeupThread_005030a0);
        ld(ra, sp, 0x10);
    }
    // 0x005040b0 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x005064F8 sub_5064F8 -- 308 bytes; frame 0x80: s1 sp+0x30, s4 sp+0x60, s3 sp+0x50, s0 sp+0x20, ra sp+0x70, s2 sp+0x40
// libsif: queue one SIF DMA transfer descriptor (size 16..112 bytes) into the ring 0x966A60 and kick it
// (_sceSifSetDma / _isceSifSetDma).
void sub_5064F8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005064f8
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(s1, sp, 0x30);
    sd(s4, sp, 0x60);
    s1 = a3;
    sd(s3, sp, 0x50);
    s4 = a0;
    sd(s0, sp, 0x20);
    v0 = addiu(s1, -16);
    s3 = a1;
    sd(ra, sp, 0x70);
    sd(s2, sp, 0x40);
    s0 = a2;
    a0 = t0;
    v0 = sltiu(v0, 97);
    a1 = t2;
    if (v0 == 0) {
        // 0x00506538
        charge(ctx, 2);
        v0 = 0;
        goto L_0050660c;
    }
    // 0x00506540
    charge(ctx, 2);
    s2 = 0;
    if (i64(a1) <= 0) {
        // 0x00506588
        charge(ctx, 3);
        lbu(v0, s0, 0);
        sw(zero, s0, 4);
        sw(v0, s0, 0);
    L_00506594:
        charge(ctx, 1);
        a1 = sll(s2, 4);
    } else {
        // 0x00506548
        charge(ctx, 12);
        lbu(v0, s0, 0);
        v1 = sll(a1, 8);
        sw(t1, s0, 4);
        s2 = 1;
        v0 = v0 | v1;
        sw(a0, sp, 0x0);
        sw(v0, s0, 0);
        v1 = s3 & 0x4;
        sw(t1, sp, 0x4);
        sw(a1, sp, 0x8);
        sw(zero, sp, 0xC);
        if (v1 == 0) {
            goto L_00506594;
        }
        // 0x00506578
        charge(ctx, 4);
        jal(ctx, 0x506578u, gen::fn_sub_5067F8_005067f8);
        a1 = sll(s2, 4);
    }
    // 0x00506598
    charge(ctx, 23);
    v0 = 0x960000;
    lw(a0, v0, 27232);  // 0x966A60
    v1 = addu(sp, a1);
    sw(s0, v1, 0);
    v0 = addiu(sp, 0x4);
    v0 = addu(v0, a1);
    v1 = addiu(sp, 0x8);
    sw(a0, v0, 0);
    v1 = addu(v1, a1);
    sw(s1, v1, 0);
    a0 = addiu(sp, 0xC);
    a0 = addu(a0, a1);
    sw(s4, s0, 8);
    sb(s1, s0, 0);
    v0 = 68;
    sw(v0, a0, 0);
    a1 = s1;
    a0 = s0;
    s2 = addiu(s2, 1);
    jal(ctx, 0x5065E0u, gen::fn_sub_5067F8_005067f8);
    v0 = s3 & 0x1;
    a1 = s2;
    if (v0 == 0) {
        // 0x00506604
        charge(ctx, 2);
        a0 = sp;
        jal(ctx, 0x506604u, gen::fn__sceSifSetDma_00503520);
    L_0050660c:
        charge(ctx, 1);
        ld(ra, sp, 0x70);
    } else {
        // 0x005065f4
        charge(ctx, 4);
        a0 = sp;
        jal(ctx, 0x5065F4u, gen::fn__isceSifSetDma_00503530);
        ld(ra, sp, 0x70);
    }
    // 0x00506610 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s4, sp, 0x60);
    ld(s3, sp, 0x50);
    ld(s2, sp, 0x40);
    ld(s1, sp, 0x30);
    ld(s0, sp, 0x20);
    sp = addiu(sp, 0x80);
}

// 0x0050E000 sub_50E000 -- 400 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20, s1 sp+0x10, s0 sp+0x0
// libkernel timer: advance the system-time alarms from T0_COUNT (0x10001000 / 0x10001010) and the overflow count.
void sub_50E000(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0050e000
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = 0x780000;
    sd(ra, sp, 0x30);
    v0 = addiu(v0, 2888);  // &0x780B48
    sd(s2, sp, 0x20);
    a3 = a0;
    sd(s1, sp, 0x10);
    sd(s0, sp, 0x0);
    lw(v1, v0, 28);  // 0x780B64
    lw(a2, v0, 24);  // 0x780B60
    if (i64(v1) >= 0) {
        // 0x0050e178
        charge(ctx, 6);
        ld(ra, sp, 0x30);
        ld(s2, sp, 0x20);
        ld(s1, sp, 0x10);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
        return;
    }
    // 0x0050e02c
    charge(ctx, 5);
    v0 = 0x10000000;
    v0 = v0 | 0x1010;
    lw(s2, v0, 0);  // 0x10001010
    if (a2 == 0) {
        // 0x0050e040
        charge(ctx, 11);
        a0 = 0;
        jal(ctx, 0x50E040u, gen::fn_sub_50DCA0_0050dca0);
        a0 = lui(0xFFFF);
        ld(ra, sp, 0x30);
        a0 = a0 | 0xF7FF;
        ld(s1, sp, 0x10);
        a0 = s2 & a0;
        ld(s0, sp, 0x0);
        ld(s2, sp, 0x20);
        sp = addiu(sp, 0x40);
        gen::fn_sub_50DC90_0050dc90(ctx);  // tail call
        return;
    }
    ld(v0, a2, 32);
    // 0x0050e06c
    charge(ctx, 6);
    ld(v1, a2, 16);
    ld(a0, a2, 24);
    v0 = v0 + v1;
    lw(a2, a2, 0);
    s0 = v0 - a0;
    if (a2 != 0) {
        // 0x0050e084
        charge(ctx, 9);
        ld(v0, a2, 32);
        v1 = daddiu(s0, 29491);
        ld(a0, a2, 16);
        ld(a1, a2, 24);
        v0 = v0 + a0;
        v0 = v0 - a1;
        v1 = sltu(v0, v1);
        s1 = s2 & 0x3;
        if (v1 == 0) {
            goto L_0050e0e4;
        }
        // 0x0050e0a8
        charge(ctx, 2);
        s0 = v0;
        for (;;) {
            // 0x0050e0b0
            charge(ctx, 3);
            lw(a2, a2, 0);
            v1 = daddiu(s0, 29491);
            if (a2 == 0) {
                goto L_0050e0e8;
            }
            // 0x0050e0bc
            charge(ctx, 8);
            ld(v0, a2, 32);
            ld(a0, a2, 16);
            ld(a1, a2, 24);
            v0 = v0 + a0;
            v0 = v0 - a1;
            v1 = sltu(v0, v1);
            if (v1 != 0) {
                // 0x0050e0dc
                charge(ctx, 2);
                s0 = v0;
                backedge(ctx);
                continue;
            }
            v0 = s0 - a3;
            break;
        }
        goto L_0050e0ec;
    }
L_0050e0e4:
    charge(ctx, 1);
    s1 = s2 & 0x3;
L_0050e0e8:
    charge(ctx, 1);
    v0 = s0 - a3;
L_0050e0ec:
    charge(ctx, 3);
    v0 = slti(v0, 29491);
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = 0x10000000;
    if (cc) {
        // 0x0050e140
        charge(ctx, 14);
        a0 = lui(0xFFFF);
        a0 = a0 | 0xF7FF;
        a0 = s2 & a0;
        jal(ctx, 0x50E148u, gen::fn_sub_50DC90_0050dc90);
        a0 = sll(s1, 2);
        ld(ra, sp, 0x30);
        a0 = dsrlv(s0, a0);
        ld(s2, sp, 0x20);
        ld(s1, sp, 0x10);
        a0 = dsll32(a0, 0);
        a0 = dsra32(a0, 0);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
        gen::fn_sub_50DCA0_0050dca0(ctx);  // tail call
        return;
    }
    // 0x0050e0f8
    charge(ctx, 18);
    a1 = sll(s1, 2);
    v0 = v0 | 0x1000;
    a0 = 29491;
    a0 = dsrlv(a0, a1);
    lw(v1, v0, 0);
    a0 = dsll32(a0, 0);
    a0 = dsra32(a0, 0);
    a0 = addu(v1, a0);
    jal(ctx, 0x50E114u, gen::fn_sub_50DCA0_0050dca0);
    a0 = lui(0xFFFF);
    ld(ra, sp, 0x30);
    a0 = a0 | 0xF7FF;
    ld(s1, sp, 0x10);
    a0 = s2 & a0;
    ld(s0, sp, 0x0);
    ld(s2, sp, 0x20);
    sp = addiu(sp, 0x40);
    gen::fn_sub_50DC90_0050dc90(ctx);  // tail call
}

// 0x00511478 _send_to_iop -- 276 bytes; frame 0x150: s2 sp+0x120, s0 sp+0x100, s3 sp+0x130, ra sp+0x140, s1 sp+0x110
// libpad: send a port's actuator block to the IOP by SIF DMA ("sceSifSetDma faild").
void _send_to_iop(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00511478
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x150);
    v1 = 28;
    sd(s2, sp, 0x120);
    sd(s0, sp, 0x100);
    s2 = a0;
    s0 = a1;
    a0 = 112;
    mult1(a0, s2, a0);
    mult(v1, s0, v1);
    sd(s3, sp, 0x130);
    s3 = 0x970000;
    sd(ra, sp, 0x140);
    sd(s1, sp, 0x110);
    v0 = addiu(s3, -8944);  // &0x96DD10
    v1 = addu(v1, a0);
    a1 = addu(v0, v1);
    v0 = a1;
    lw(a0, a1, 12);
    lw(s1, v0, 4);
    if (a0 != 0) {
        // 0x005114c8
        charge(ctx, 4);
        jal(ctx, 0x5114C8u, gen::fn__sceSifDmaStat_00503500);
        cc = i64(v0) >= 0;  // the condition, before the delay slot changes it
        v0 = 0x780000;
        if (!cc) {
            goto L_005114d8;
        }
    L_0051154c:
        charge(ctx, 3);
        lw(v1, v0, 10060);
        a0 = 0x7C0000;
        if (v1 != 0) {
            // 0x00511558
            charge(ctx, 2);
            a0 = addiu(a0, -7256);
            jal(ctx, 0x511558u, gen::fn_scePrintf_00505e48);
        }
        // 0x00511560
        charge(ctx, 2);
        v0 = 0;
        // 0x00511570 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(ra, sp, 0x140);
        ld(s3, sp, 0x130);
        ld(s2, sp, 0x120);
        ld(s1, sp, 0x110);
        ld(s0, sp, 0x100);
        sp = addiu(sp, 0x150);
        return;
    }
L_005114d8:
    charge(ctx, 28);
    a3 = 28;
    v1 = 112;
    mult(a3, s0, a3);
    mult1(v1, s2, v1);
    lw(a2, s1, 0);
    s3 = addiu(s3, -8944);
    a0 = s1;
    a1 = addiu(s1, 31);
    a2 = addiu(a2, 1);
    s2 = addu(a3, v1);
    v0 = a2 & 0x1;
    v1 = addu(s3, s2);
    v0 = sll(v0, 5);
    lw(s0, v1, 8);
    sw(a2, s1, 0);
    s0 = addu(s0, v0);
    jal(ctx, 0x511514u, gen::fn_SyncDCache_00503a58);
    v0 = 32;
    sw(s0, sp, 0x4);
    sw(s1, sp, 0x0);
    a0 = sp;
    sw(v0, sp, 0x8);
    a1 = 1;
    link(ctx, 0x511534u);  // $ra first: the delay slot below depends on it
    sw(zero, sp, 0xC);
    call(ctx, gen::fn_sceSifSetDma_00506088);
    a0 = v0;
    v1 = addu(s3, s2);
    if (a0 == 0) {
        // 0x00511548
        charge(ctx, 1);
        v0 = 0x780000;
        goto L_0051154c;
    }
    // 0x00511568
    charge(ctx, 2);
    v0 = 1;
    sw(a0, v1, 12);
    // 0x00511570 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x140);
    ld(s3, sp, 0x130);
    ld(s2, sp, 0x120);
    ld(s1, sp, 0x110);
    ld(s0, sp, 0x100);
    sp = addiu(sp, 0x150);
}

// 0x00512868 sceSdRemoteInit -- 176 bytes; frame 0x40: s0 sp+0x0, s2 sp+0x20, s1 sp+0x10, ra sp+0x30
// libsdr: sceSdRemoteInit: bind the sdrdrv RPC server (retrying until bound) and flush the cache.
void sceSdRemoteInit(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00512868
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    a0 = 0;
    sd(s0, sp, 0x0);
    sd(s2, sp, 0x20);
    s0 = 0x970000;
    sd(s1, sp, 0x10);
    s2 = addiu(s0, -8128);  // &sdr_rpc_cd
    sd(ra, sp, 0x30);
    s1 = 0x7C0000;
    jal(ctx, 0x512888u, gen::fn_sceSifInitRpc_005068a8);
    for (;;) {
        // 0x00512890
        charge(ctx, 7);
        a1 = lui(0x8000);
        a0 = addiu(s0, -8128);
        a1 = a1 | 0x701;
        a2 = 0;
        jal(ctx, 0x51289Cu, gen::fn_sceSifBindRpc_00507050);
        cc = i64(v0) >= 0;  // the condition, before the delay slot changes it
        v0 = 10000;
        if (!cc) {
            goto L_005128ac_2;
        }
        // 0x005128bc
        charge(ctx, 1);
        v1 = si(-1);
        for (;;) {
            // 0x005128c0
            charge(ctx, 7);
            v0 = addiu(v0, -1);
            if (v0 == v1) {
                break;
            }
            backedge(ctx);
        }
        // 0x005128dc
        charge(ctx, 3);
        lw(v0, s2, 36);
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = 0x780000;
        if (!cc) {
            break;
        }
        backedge(ctx);
    }
    // 0x005128e8
    charge(ctx, 6);
    v1 = 0x780000;
    sw(zero, v0, 10120);
    a0 = 0;
    link(ctx, 0x5128F4u);  // $ra first: the delay slot below depends on it
    sw(zero, v1, 10124);
    call(ctx, gen::fn__sceFlushCache_005033e0);
    v0 = 0;
    // 0x00512900 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
    return;
L_005128ac_2:
    charge(ctx, 4);
    a0 = addiu(s1, -7032);
    jal(ctx, 0x5128ACu, gen::fn_scePrintf_00505e48);
    v0 = si(-1);
    // 0x00512900 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x005130E8 sceMc2Init -- 424 bytes; frame 0x100: s4 sp+0xC0, s2 sp+0xA0, ra sp+0xF0, s6 sp+0xE0, s5 sp+0xD0, s3 sp+0xB0, s1 sp+0x90, s0 sp+0x80
// libmc2: sceMc2Init: the three semaphores, the basic thread, the core / mcp / fat layers.
void sceMc2Init(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005130e8
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x100);
    sd(s4, sp, 0xC0);
    s4 = 0x780000;
    sd(s2, sp, 0xA0);
    lw(v0, s4, 10200);  // 0x7827D8
    s2 = 1;
    sd(ra, sp, 0xF0);
    sd(s6, sp, 0xE0);
    sd(s5, sp, 0xD0);
    sd(s3, sp, 0xB0);
    sd(s1, sp, 0x90);
    sd(s0, sp, 0x80);
    if (v0 == s2) {
        // 0x0051311c
        charge(ctx, 2);
        jal(ctx, 0x51311Cu, gen::fn_sceMc2End_00513290);
    }
    // 0x00513124
    charge(ctx, 19);
    v1 = 0x7C0000;
    v0 = si(-1);
    s6 = 0x970000;
    v1 = addiu(v1, -6928);  // "sceMc2_sema_main"
    s0 = 0x970000;
    sw(v1, sp, 0x74);
    sw(v0, s0, -2452);  // 0x96F66C
    s5 = addiu(s6, -2464);  // &0x96F660
    sw(v0, s6, -2464);  // 0x96F660
    s1 = addiu(sp, 0x60);
    sw(v0, s5, 4);  // 0x96F664
    s3 = 127;
    sw(v0, s5, 8);  // 0x96F668
    a0 = s1;
    sw(s2, sp, 0x68);
    link(ctx, 0x513160u);  // $ra first: the delay slot below depends on it
    sw(s3, sp, 0x64);
    call(ctx, gen::fn__sceCreateSema_00503160);
    sw(v0, s0, -2452);  // 0x96F66C
    if (i64(v0) >= 0) {
        // 0x00513170
        charge(ctx, 9);
        v0 = 0x7C0000;
        sw(zero, sp, 0x68);
        v0 = addiu(v0, -6904);  // "sceMc2_sema_start"
        sw(s3, sp, 0x64);
        sw(v0, sp, 0x74);
        a0 = s1;
        jal(ctx, 0x513184u, gen::fn__sceCreateSema_00503160);
        sw(v0, s5, 4);
        if (i64(v0) < 0) {
            goto L_00513230;
        }
        // 0x00513194
        charge(ctx, 9);
        v0 = 0x7C0000;
        sw(s3, sp, 0x64);
        v0 = addiu(v0, -6880);  // "sceMc2_sema_end"
        a0 = s1;
        sw(v0, sp, 0x74);
        link(ctx, 0x5131A8u);  // $ra first: the delay slot below depends on it
        sw(zero, sp, 0x68);
        call(ctx, gen::fn__sceCreateSema_00503160);
        sw(v0, s5, 8);
        if (i64(v0) < 0) {
            goto L_00513230;
        }
        // 0x005131b8
        charge(ctx, 21);
        v1 = 0x510000;
        a1 = 0x970000;
        a2 = 0x7D0000;
        a3 = 0x7C0000;
        v1 = addiu(v1, 17912);  // &basic_thread
        a1 = addiu(a1, -2432);  // &0x96F680
        a2 = addiu(a2, 11504);  // &gp_base
        a3 = addiu(a3, -6864);  // "sceMc2_basic_thread"
        v0 = 0x970000;
        t0 = 0xC000;
        sw(zero, v0, -3772);  // 0x96F144
        a0 = sp;
        sw(v1, sp, 0x4);
        sw(a1, sp, 0x8);
        sw(t0, sp, 0xC);
        sw(a2, sp, 0x10);
        sw(a3, sp, 0x20);
        link(ctx, 0x5131FCu);  // $ra first: the delay slot below depends on it
        sw(s2, sp, 0x14);
        call(ctx, gen::fn__sceCreateThread_00502f60);
        sw(v0, s6, -2464);
        if (i64(v0) >= 0) {
            // 0x00513220
            charge(ctx, 4);
            jal(ctx, 0x513220u, gen::fn__sceMcCoreInit_0051ae68);
            if (v0 == 0) {
                goto L_00513230;
            }
            // 0x00513244
            charge(ctx, 9);
            jal(ctx, 0x513244u, gen::fn__sceMcpInit_0051a140);
            jal(ctx, 0x51324Cu, gen::fn__sceMcFatInit_005153a0);
            lw(a0, s6, -2464);
            a1 = 0;
            jal(ctx, 0x513258u, gen::fn_StartThread_005042a0);
            sw(s2, s4, 10200);
            v0 = 0;
        } else {
            // 0x0051320c
            charge(ctx, 5);
            link(ctx, 0x51320Cu);  // $ra first: the delay slot below depends on it
            sw(s2, s4, 10200);
            call(ctx, gen::fn_sceMc2End_00513290);
            v0 = lui(0x8101);
            v0 = v0 | 0x8004;
        }
        // 0x00513268 (the shared epilogue, written out on this path)
        charge(ctx, 10);
        ld(ra, sp, 0xF0);
        ld(s6, sp, 0xE0);
        ld(s5, sp, 0xD0);
        ld(s4, sp, 0xC0);
        ld(s3, sp, 0xB0);
        ld(s2, sp, 0xA0);
        ld(s1, sp, 0x90);
        ld(s0, sp, 0x80);
        sp = addiu(sp, 0x100);
        return;
    }
L_00513230:
    charge(ctx, 5);
    link(ctx, 0x513230u);  // $ra first: the delay slot below depends on it
    sw(s2, s4, 10200);
    call(ctx, gen::fn_sceMc2End_00513290);
    v0 = lui(0x8101);
    v0 = v0 | 0x8003;
    // 0x00513268 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0xF0);
    ld(s6, sp, 0xE0);
    ld(s5, sp, 0xD0);
    ld(s4, sp, 0xC0);
    ld(s3, sp, 0xB0);
    ld(s2, sp, 0xA0);
    ld(s1, sp, 0x90);
    ld(s0, sp, 0x80);
    sp = addiu(sp, 0x100);
}

// 0x005137B8 sceMc2SearchFileAsync -- 256 bytes; frame 0x260: s4 sp+0x240, s3 sp+0x230, s0 sp+0x200, ra sp+0x250, s2 sp+0x220, s1 sp+0x210
// libmc2: start an asynchronous search for file a1 on card a0 (under the main semaphore).
void sceMc2SearchFileAsync(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005137b8
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x260);
    v0 = 0x780000;
    sd(s4, sp, 0x240);
    sd(s3, sp, 0x230);
    s4 = a2;
    sd(s0, sp, 0x200);
    s3 = a1;
    lw(v1, v0, 10200);  // 0x7827D8
    s0 = a0;
    sd(ra, sp, 0x250);
    sd(s2, sp, 0x220);
    sd(s1, sp, 0x210);
    if (v1 != 0) {
        // 0x005137f8
        charge(ctx, 5);
        a0 = s0;
        jal(ctx, 0x5137F8u, gen::fn__sceMcCoreChangeSocketTypeDbc2Mc_0051c2e8);
        s0 = v0;
        if (i64(s0) >= 0) {
            // 0x00513818
            charge(ctx, 5);
            a0 = s3;
            jal(ctx, 0x513818u, gen::fn_strlen_00524388);
            v0 = sltiu(v0, 128);
            s2 = 0x970000;
            if (v0 != 0) {
                // 0x00513838
                charge(ctx, 7);
                link(ctx, 0x513838u);  // $ra first: the delay slot below depends on it
                lw(a0, s2, -2452);
                call(ctx, gen::fn__sceWaitSema_005031a0);
                v1 = 0x970000;
                s1 = addiu(v1, -3776);  // &0x96F140
                lw(v0, s1, 4);  // 0x96F144
                if (v0 == 0) {
                    v0 = 14;
                    // 0x00513868
                    charge(ctx, 12);
                    sw(s0, v1, -3776);
                    sw(v0, s1, 4);
                    a1 = s3;
                    a0 = addiu(s1, 1052);
                    jal(ctx, 0x513874u, gen::fn_strcpy_00524270);
                    sw(s4, s1, 12);
                    v1 = 0x970000;
                    link(ctx, 0x513884u);  // $ra first: the delay slot below depends on it
                    lw(a0, v1, -2460);
                    call(ctx, gen::fn__sceSignalSema_00503180);
                    link(ctx, 0x51388Cu);  // $ra first: the delay slot below depends on it
                    lw(a0, s2, -2452);
                    call(ctx, gen::fn__sceSignalSema_00503180);
                    v0 = 0;
                } else {
                    // 0x00513854
                    charge(ctx, 5);
                    link(ctx, 0x513854u);  // $ra first: the delay slot below depends on it
                    lw(a0, s2, -2452);
                    call(ctx, gen::fn__sceSignalSema_00503180);
                    v0 = lui(0x8101);
                    v0 = v0 | 0x10;
                }
            } else {
                // 0x0051382c
                charge(ctx, 3);
                v0 = lui(0x8101);
                v0 = v0 | 0x5B;
            }
        } else {
            // 0x0051380c
            charge(ctx, 3);
            v0 = lui(0x8101);
            v0 = v0 | 0x8002;
        }
    } else {
        // 0x005137ec
        charge(ctx, 3);
        v0 = lui(0x8101);
        v0 = v0 | 0x8001;
    }
    // 0x00513898 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x250);
    ld(s4, sp, 0x240);
    ld(s3, sp, 0x230);
    ld(s2, sp, 0x220);
    ld(s1, sp, 0x210);
    ld(s0, sp, 0x200);
    sp = addiu(sp, 0x260);
}

// 0x00513968 sceMc2ReadFileAsync -- 288 bytes; frame 0x80: s6 sp+0x60, s5 sp+0x50, s4 sp+0x40, s3 sp+0x30, s1 sp+0x10, ra sp+0x70, s2 sp+0x20, s0 sp+0x0
// libmc2: start an asynchronous read of file a1 on card a0 (offset / size / buffer arguments).
void sceMc2ReadFileAsync(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00513968
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
        // 0x005139b8
        charge(ctx, 5);
        a0 = s1;
        jal(ctx, 0x5139B8u, gen::fn__sceMcCoreChangeSocketTypeDbc2Mc_0051c2e8);
        s1 = v0;
        if (i64(s1) >= 0) {
            // 0x005139d8
            charge(ctx, 5);
            a0 = s3;
            jal(ctx, 0x5139D8u, gen::fn_strlen_00524388);
            v0 = sltiu(v0, 128);
            s2 = 0x970000;
            if (v0 != 0) {
                // 0x005139f8
                charge(ctx, 7);
                link(ctx, 0x5139F8u);  // $ra first: the delay slot below depends on it
                lw(a0, s2, -2452);
                call(ctx, gen::fn__sceWaitSema_005031a0);
                v1 = 0x970000;
                s0 = addiu(v1, -3776);  // &0x96F140
                lw(v0, s0, 4);  // 0x96F144
                if (v0 == 0) {
                    v0 = 5;
                    // 0x00513a28
                    charge(ctx, 14);
                    sw(s1, v1, -3776);
                    sw(v0, s0, 4);
                    a1 = s3;
                    a0 = addiu(s0, 1052);
                    jal(ctx, 0x513A34u, gen::fn_strcpy_00524270);
                    sw(s4, s0, 20);
                    v1 = 0x970000;
                    lw(a0, v1, -2460);  // 0x96F664
                    sw(s5, s0, 12);
                    link(ctx, 0x513A4Cu);  // $ra first: the delay slot below depends on it
                    sw(s6, s0, 16);
                    call(ctx, gen::fn__sceSignalSema_00503180);
                    link(ctx, 0x513A54u);  // $ra first: the delay slot below depends on it
                    lw(a0, s2, -2452);
                    call(ctx, gen::fn__sceSignalSema_00503180);
                    v0 = 0;
                } else {
                    // 0x00513a14
                    charge(ctx, 5);
                    link(ctx, 0x513A14u);  // $ra first: the delay slot below depends on it
                    lw(a0, s2, -2452);
                    call(ctx, gen::fn__sceSignalSema_00503180);
                    v0 = lui(0x8101);
                    v0 = v0 | 0x10;
                }
            } else {
                // 0x005139ec
                charge(ctx, 3);
                v0 = lui(0x8101);
                v0 = v0 | 0x5B;
            }
        } else {
            // 0x005139cc
            charge(ctx, 3);
            v0 = lui(0x8101);
            v0 = v0 | 0x8002;
        }
    } else {
        // 0x005139ac
        charge(ctx, 3);
        v0 = lui(0x8101);
        v0 = v0 | 0x8001;
    }
    // 0x00513a60 (the shared epilogue, written out on this path)
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

// 0x00514900 sceMc2CheckAsync -- 36 bytes; frame 0x10: ra sp+0x0
// libmc2: sceMc2CheckAsync = sceMc2Sync2.
void sceMc2CheckAsync(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00514900
    enter(ctx, 9);  // entry check point + this block's cycles
    a2 = a1;
    sp = addiu(sp, -0x10);
    a1 = a0;
    sd(ra, sp, 0x0);
    a0 = 1;
    jal(ctx, 0x514910u, gen::fn_sceMc2Sync2_00514858);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0051AFD8 _sceMcCoreGetCardSpec -- 468 bytes; frame 0xB0: s6 sp+0x70, fp sp+0x90, s7 sp+0x80, s2 sp+0x30, ra sp+0xA0, s5 sp+0x60, s4 sp+0x50, s3 sp+0x40, s1 sp+0x20, s0 sp+0x10
// libmc2 core: card spec request (dbc send, DMA sync, the result copied out).
void _sceMcCoreGetCardSpec(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x0051afd8
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    v1 = 36;
    sd(s6, sp, 0x70);
    s6 = a0;
    sd(fp, sp, 0x90);
    mult(v1, s6, v1);
    fp = 0x980000;
    v0 = addiu(fp, 0x5508);
    sd(s7, sp, 0x80);
    sd(s2, sp, 0x30);
    v0 = addiu(v0, 4);
    sw(a1, sp, 0x4);
    s7 = 3;
    sd(ra, sp, 0xA0);
    s2 = addu(v1, v0);
    sd(s5, sp, 0x60);
    sd(s4, sp, 0x50);
    sd(s3, sp, 0x40);
    sd(s1, sp, 0x20);
    sd(s0, sp, 0x10);
    link(ctx, 0x51B028u);  // $ra first: the delay slot below depends on it
    lw(a0, s2, 0);
    call(ctx, gen::fn_sceDbcGetConnection_0051cad0);
    s3 = 0x980000;
    if (v0 != s7) {
        // 0x0051b038
        charge(ctx, 26);
        v1 = 48;
        v0 = addiu(s3, 21888);
        s0 = 0x980000;
        sw(zero, v0, 36);
        s0 = addiu(s0, 21952);  // &0x9855C0
        sw(v1, sp, 0x0);
        a0 = s0;
        sw(zero, v0, 8);
        a1 = 0;
        sw(zero, v0, 12);
        a2 = 256;
        sw(zero, v0, 16);
        s1 = 0x780000;
        sw(zero, v0, 20);
        s5 = 0x520000;
        sw(zero, v0, 24);
        s4 = 1;
        sw(zero, v0, 28);
        link(ctx, 0x51B080u);  // $ra first: the delay slot below depends on it
        sw(zero, v0, 32);
        call(ctx, gen::fn_memset_00521408);
        a0 = s0;
        a1 = addiu(a0, 255);  // &0x9856BF
        jal(ctx, 0x51B08Cu, gen::fn_SyncDCache_00503a58);
        sw(s7, s1, 10988);  // 0x782AEC
        lw(a0, s2, 0);
        for (;;) {
            // 0x0051b0a0
            charge(ctx, 7);
            a2 = sp;
            lw(a1, s1, 10988);
            a3 = addiu(s3, 21888);
            t0 = addiu(s5, -20936);
            jal(ctx, 0x51B0ACu, gen::fn_sceDbcSendData3_0051d308);
            if (v0 == s4) {
                break;
            }
            lw(a0, s2, 0);
            backedge(ctx);
        }
        // 0x0051b0bc
        charge(ctx, 7);
        jal(ctx, 0x51B0BCu, gen::fn_SyncDma_0051ad10);
        t3 = v0;
        lw(t4, t3, 8);
        v0 = 1;
        a3 = 36;
        if (t4 != v0) {
            goto L_0051b0d8;
        }
        // 0x0051b0e0
        charge(ctx, 39);
        lbu(v0, t3, 13);
        mult(a3, s6, a3);
        lbu(v1, t3, 12);
        a0 = addiu(fp, 0x5508);
        v0 = sll(v0, 8);
        v1 = addu(v1, v0);
        v0 = 1;
        a1 = addu(a0, a3);
        sw(v1, a1, 8);
        a3 = addu(a3, a0);
        t0 = a1;
        t1 = a1;
        lbu(v1, t3, 15);
        t2 = a1;
        lbu(a0, t3, 14);
        v1 = sll(v1, 8);
        a0 = addu(a0, v1);
        sw(a0, t0, 12);
        lbu(a2, t3, 17);
        lbu(a1, t3, 19);
        lbu(a0, t3, 18);
        a2 = sll(a2, 8);
        lbu(v1, t3, 16);
        a1 = sll(a1, 24);
        a0 = sll(a0, 16);
        v1 = addu(v1, a1);
        a0 = addu(a0, a2);
        v1 = addu(v1, a0);
        sw(v1, t1, 16);
        sw(t4, t2, 20);
        lw(v1, sp, 0x4);
        ldl(a0, a3, 15);
        ldr(a0, a3, 8);
        ldl(a1, a3, 23);
        ldr(a1, a3, 16);
        sdl(a0, v1, 7);
        sdr(a0, v1, 0);
        sdl(a1, v1, 15);
        sdr(a1, v1, 8);
        // 0x0051b17c (the shared epilogue, written out on this path)
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
L_0051b0d8:
    charge(ctx, 2);
    v0 = 0;
    // 0x0051b17c (the shared epilogue, written out on this path)
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

// 0x0051B1B0 _sceMcCoreCheckNewCard -- 272 bytes; frame 0x70: s0 sp+0x10, s1 sp+0x20, s2 sp+0x30, ra sp+0x60, s4 sp+0x50, s3 sp+0x40
// libmc2 core: new-card check request.
void _sceMcCoreCheckNewCard(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051b1b0
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    v0 = 36;
    sd(s0, sp, 0x10);
    v1 = 0x980000;
    mult(s0, a0, v0);
    sd(s1, sp, 0x20);
    s1 = addiu(v1, 21768);  // &0x985508
    sd(s2, sp, 0x30);
    sd(ra, sp, 0x60);
    v0 = addiu(s1, 4);  // &0x98550C
    sd(s4, sp, 0x50);
    sd(s3, sp, 0x40);
    s2 = addu(s0, v0);
    link(ctx, 0x51B1E4u);  // $ra first: the delay slot below depends on it
    lw(a0, s2, 0);
    call(ctx, gen::fn_sceDbcGetConnection_0051cad0);
    v1 = 3;
    a0 = addu(s1, s0);
    if (v0 != v1) {
        // 0x0051b200
        charge(ctx, 30);
        s3 = 0x980000;
        v0 = a0;
        a3 = 48;
        v1 = v0;
        lw(a1, v0, 8);
        lw(a2, v1, 12);
        v0 = addiu(s3, 21888);  // &0x985580
        lw(v1, a0, 16);
        s0 = 0x980000;
        sw(a1, v0, 8);  // 0x985588
        s0 = addiu(s0, 21952);  // &0x9855C0
        sw(a2, v0, 12);  // 0x98558C
        a0 = s0;
        sw(v1, v0, 16);  // 0x985590
        a1 = 0;
        sw(zero, v0, 24);  // 0x985598
        a2 = 256;
        sw(a3, sp, 0x0);
        s1 = 0x780000;
        sw(zero, v0, 20);  // 0x985594
        s4 = 0x520000;
        jal(ctx, 0x51B250u, gen::fn_memset_00521408);
        a0 = s0;
        a1 = addiu(a0, 255);  // &0x9856BF
        s0 = 1;
        jal(ctx, 0x51B260u, gen::fn_SyncDCache_00503a58);
        v0 = 4;
        sw(v0, s1, 10988);  // 0x782AEC
        lw(a0, s2, 0);
        for (;;) {
            // 0x0051b278
            charge(ctx, 7);
            a2 = sp;
            lw(a1, s1, 10988);
            a3 = addiu(s3, 21888);
            t0 = addiu(s4, -20936);
            jal(ctx, 0x51B284u, gen::fn_sceDbcSendData3_0051d308);
            if (v0 == s0) {
                break;
            }
            lw(a0, s2, 0);
            backedge(ctx);
        }
        // 0x0051b294
        charge(ctx, 3);
        jal(ctx, 0x51B294u, gen::fn_SyncDma_0051ad10);
        lw(v0, v0, 8);
    } else {
        // 0x0051b1f8
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x0051b2a0 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x60);
    ld(s4, sp, 0x50);
    ld(s3, sp, 0x40);
    ld(s2, sp, 0x30);
    ld(s1, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x70);
}

// 0x0051B2C0 _sceMcCoreClearNewCardFlag -- 240 bytes; frame 0x70: s2 sp+0x30, ra sp+0x60, s4 sp+0x50, s3 sp+0x40, s1 sp+0x20, s0 sp+0x10
// libmc2 core: clear the new-card flag.
void _sceMcCoreClearNewCardFlag(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051b2c0
    enter(ctx, 18);  // entry check point + this block's cycles
    v1 = 36;
    v0 = 0x980000;
    mult(a0, a0, v1);
    sp = addiu(sp, -0x70);
    v0 = addiu(v0, 21768);  // &0x985508
    sd(s2, sp, 0x30);
    sd(ra, sp, 0x60);
    v0 = addiu(v0, 4);  // &0x98550C
    sd(s4, sp, 0x50);
    sd(s3, sp, 0x40);
    s2 = addu(a0, v0);
    sd(s1, sp, 0x20);
    sd(s0, sp, 0x10);
    link(ctx, 0x51B2F4u);  // $ra first: the delay slot below depends on it
    lw(a0, s2, 0);
    call(ctx, gen::fn_sceDbcGetConnection_0051cad0);
    v1 = 3;
    s3 = 0x980000;
    if (v0 != v1) {
        // 0x0051b310
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
        jal(ctx, 0x51B338u, gen::fn_memset_00521408);
        s4 = 0x520000;
        a0 = s0;
        a1 = addiu(a0, 255);  // &0x9856BF
        s0 = 1;
        jal(ctx, 0x51B34Cu, gen::fn_SyncDCache_00503a58);
        v0 = 13;
        sw(v0, s1, 10988);  // 0x782AEC
        lw(a0, s2, 0);
        for (;;) {
            // 0x0051b360
            charge(ctx, 7);
            a2 = sp;
            lw(a1, s1, 10988);
            a3 = addiu(s3, 21888);
            t0 = addiu(s4, -20936);
            jal(ctx, 0x51B36Cu, gen::fn_sceDbcSendData3_0051d308);
            if (v0 == s0) {
                break;
            }
            lw(a0, s2, 0);
            backedge(ctx);
        }
        // 0x0051b37c
        charge(ctx, 5);
        jal(ctx, 0x51B37Cu, gen::fn_SyncDma_0051ad10);
        lw(v0, v0, 8);
        v0 = v0 ^ 0x1;
        v0 = sltiu(v0, 1);
    } else {
        // 0x0051b308
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x0051b390 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x60);
    ld(s4, sp, 0x50);
    ld(s3, sp, 0x40);
    ld(s2, sp, 0x30);
    ld(s1, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x70);
}

// 0x0051B3B0 _sceMcCoreAuthentication -- 240 bytes; frame 0x70: s2 sp+0x30, ra sp+0x60, s4 sp+0x50, s3 sp+0x40, s1 sp+0x20, s0 sp+0x10
// libmc2 core: authentication request.
void _sceMcCoreAuthentication(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051b3b0
    enter(ctx, 18);  // entry check point + this block's cycles
    v1 = 36;
    v0 = 0x980000;
    mult(a0, a0, v1);
    sp = addiu(sp, -0x70);
    v0 = addiu(v0, 21768);  // &0x985508
    sd(s2, sp, 0x30);
    sd(ra, sp, 0x60);
    v0 = addiu(v0, 4);  // &0x98550C
    sd(s4, sp, 0x50);
    sd(s3, sp, 0x40);
    s2 = addu(a0, v0);
    sd(s1, sp, 0x20);
    sd(s0, sp, 0x10);
    link(ctx, 0x51B3E4u);  // $ra first: the delay slot below depends on it
    lw(a0, s2, 0);
    call(ctx, gen::fn_sceDbcGetConnection_0051cad0);
    v1 = 3;
    s3 = 0x980000;
    if (v0 != v1) {
        // 0x0051b400
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
        jal(ctx, 0x51B428u, gen::fn_memset_00521408);
        s4 = 0x520000;
        a0 = s0;
        a1 = addiu(a0, 255);  // &0x9856BF
        s0 = 1;
        jal(ctx, 0x51B43Cu, gen::fn_SyncDCache_00503a58);
        v0 = 12;
        sw(v0, s1, 10988);  // 0x782AEC
        lw(a0, s2, 0);
        for (;;) {
            // 0x0051b450
            charge(ctx, 7);
            a2 = sp;
            lw(a1, s1, 10988);
            a3 = addiu(s3, 21888);
            t0 = addiu(s4, -20936);
            jal(ctx, 0x51B45Cu, gen::fn_sceDbcSendData3_0051d308);
            if (v0 == s0) {
                break;
            }
            lw(a0, s2, 0);
            backedge(ctx);
        }
        // 0x0051b46c
        charge(ctx, 5);
        jal(ctx, 0x51B46Cu, gen::fn_SyncDma_0051ad10);
        lw(v0, v0, 8);
        v0 = v0 ^ 0x1;
        v0 = sltiu(v0, 1);
    } else {
        // 0x0051b3f8
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x0051b480 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x60);
    ld(s4, sp, 0x50);
    ld(s3, sp, 0x40);
    ld(s2, sp, 0x30);
    ld(s1, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x70);
}

// 0x0051B4A0 _sceMcCoreWriteBack -- 332 bytes; frame 0x80: s0 sp+0x10, s1 sp+0x20, s2 sp+0x30, ra sp+0x70, s5 sp+0x60, s4 sp+0x50, s3 sp+0x40
// libmc2 core: write-back request ("** PANIC!" on a bad state).
void _sceMcCoreWriteBack(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0051b4a0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    v0 = 36;
    sd(s0, sp, 0x10);
    v1 = 0x980000;
    mult(s0, a0, v0);
    sd(s1, sp, 0x20);
    s1 = addiu(v1, 21768);  // &0x985508
    sd(s2, sp, 0x30);
    sd(ra, sp, 0x70);
    v0 = addiu(s1, 4);  // &0x98550C
    sd(s5, sp, 0x60);
    sd(s4, sp, 0x50);
    s2 = addu(s0, v0);
    sd(s3, sp, 0x40);
    link(ctx, 0x51B4D8u);  // $ra first: the delay slot below depends on it
    lw(a0, s2, 0);
    call(ctx, gen::fn_sceDbcGetConnection_0051cad0);
    v1 = 3;
    cc = v0 != v1;  // the condition, before the delay slot changes it
    v0 = addu(s1, s0);
    if (cc) {
        // 0x0051b4f4
        charge(ctx, 3);
        lw(t2, v0, 8);
        a0 = 0x7C0000;
        if (t2 != 0) {
            // 0x0051b500
            charge(ctx, 3);
            lw(t3, v0, 12);
            a1 = addu(s1, s0);
            if (t3 == 0) {
                // 0x0051b50c
                charge(ctx, 1);
                a0 = 0x7C0000;
                goto L_0051b510;
            }
            // 0x0051b520
            charge(ctx, 32);
            s4 = 0x980000;
            v0 = a1;
            s0 = 0x980000;
            v1 = v0;
            a0 = v0;
            lw(t0, v1, 32);
            s0 = addiu(s0, 21952);  // &0x9855C0
            lw(t1, a0, 28);
            a3 = 48;
            lw(v1, a1, 20);
            a0 = s0;
            lw(a2, v0, 16);
            a1 = 0;
            v0 = addiu(s4, 21888);  // &0x985580
            s1 = 0x780000;
            sw(a2, v0, 16);  // 0x985590
            s5 = 0x520000;
            sw(t2, v0, 8);  // 0x985588
            a2 = 256;
            sw(v1, v0, 36);  // 0x9855A4
            s3 = 1;
            sw(t3, v0, 12);  // 0x98558C
            sw(t0, v0, 20);  // 0x985594
            sw(t1, v0, 24);  // 0x985598
            link(ctx, 0x51B580u);  // $ra first: the delay slot below depends on it
            sw(a3, sp, 0x0);
            call(ctx, gen::fn_memset_00521408);
            a0 = s0;
            a1 = addiu(a0, 255);  // &0x9856BF
            jal(ctx, 0x51B58Cu, gen::fn_SyncDCache_00503a58);
            v0 = 6;
            sw(v0, s1, 10988);  // 0x782AEC
            lw(a0, s2, 0);
            for (;;) {
                // 0x0051b5a0
                charge(ctx, 7);
                a2 = sp;
                lw(a1, s1, 10988);
                a3 = addiu(s4, 21888);
                t0 = addiu(s5, -20936);
                jal(ctx, 0x51B5ACu, gen::fn_sceDbcSendData3_0051d308);
                if (v0 == s3) {
                    break;
                }
                lw(a0, s2, 0);
                backedge(ctx);
            }
            // 0x0051b5bc
            charge(ctx, 3);
            jal(ctx, 0x51B5BCu, gen::fn_SyncDma_0051ad10);
            lw(v0, v0, 8);
            // 0x0051b5c8 (the shared epilogue, written out on this path)
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
    L_0051b510:
        charge(ctx, 4);
        a0 = addiu(a0, -6528);
        jal(ctx, 0x51B510u, gen::fn_scePrintf_00505e48);
        v0 = 0;
    } else {
        // 0x0051b4ec
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x0051b5c8 (the shared epilogue, written out on this path)
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

// 0x0051B708 _sceMcCoreReadPage2 -- 452 bytes; frame 0xA0: s0 sp+0x10, s1 sp+0x20, s7 sp+0x80, s6 sp+0x70, s5 sp+0x60, s4 sp+0x50, s2 sp+0x30, ra sp+0x90, s3 sp+0x40
// libmc2 core: read one page (dbc send, DMA sync for read, cache invalidate, memcpy out).
void _sceMcCoreReadPage2(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0051b708
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    v0 = 36;
    sd(s0, sp, 0x10);
    v1 = 0x980000;
    mult(s0, a0, v0);
    sd(s1, sp, 0x20);
    s1 = addiu(v1, 21768);  // &0x985508
    sd(s7, sp, 0x80);
    sd(s6, sp, 0x70);
    v0 = addiu(s1, 4);  // &0x98550C
    sd(s5, sp, 0x60);
    s7 = a1;
    sd(s4, sp, 0x50);
    s5 = addu(s0, v0);
    sd(s2, sp, 0x30);
    s6 = a2;
    sd(ra, sp, 0x90);
    s4 = a3;
    sd(s3, sp, 0x40);
    s2 = t0;
    link(ctx, 0x51B758u);  // $ra first: the delay slot below depends on it
    lw(a0, s5, 0);
    call(ctx, gen::fn_sceDbcGetConnection_0051cad0);
    v1 = 3;
    a0 = addu(s1, s0);
    if (v0 != v1) {
        // 0x0051b76c
        charge(ctx, 35);
        s3 = 0x980000;
        v0 = a0;
        lw(a3, a0, 16);
        lw(a1, v0, 8);
        v1 = v0;
        lw(a2, v1, 12);
        v0 = addiu(s3, 21888);  // &0x985580
        sw(s2, v0, 36);  // 0x9855A4
        v1 = 48;
        sw(s6, s3, 21888);  // 0x985580
        s0 = 0x980000;
        sw(a1, v0, 8);  // 0x985588
        s0 = addiu(s0, 21952);  // &0x9855C0
        sw(a2, v0, 12);  // 0x98558C
        a0 = s0;
        sw(a3, v0, 16);  // 0x985590
        a1 = 0;
        sw(v1, sp, 0x0);
        a2 = 256;
        sw(s4, v0, 4);  // 0x985584
        s1 = 0x780000;
        sw(zero, v0, 20);  // 0x985594
        s2 = s5;
        sw(zero, v0, 24);  // 0x985598
        s6 = 0x520000;
        sw(zero, v0, 28);  // 0x98559C
        s5 = 1;
        link(ctx, 0x51B7D8u);  // $ra first: the delay slot below depends on it
        sw(zero, v0, 32);
        call(ctx, gen::fn_memset_00521408);
        a0 = s0;
        a1 = addiu(a0, 255);  // &0x9856BF
        jal(ctx, 0x51B7E4u, gen::fn_SyncDCache_00503a58);
        v0 = 1;
        sw(v0, s1, 10988);  // 0x782AEC
        lw(a0, s2, 0);
        for (;;) {
            // 0x0051b7f8
            charge(ctx, 7);
            a2 = sp;
            lw(a1, s1, 10988);
            a3 = addiu(s3, 21888);
            t0 = addiu(s6, -20936);
            jal(ctx, 0x51B804u, gen::fn_sceDbcSendData3_0051d308);
            if (v0 == s5) {
                break;
            }
            lw(a0, s2, 0);
            backedge(ctx);
        }
        // 0x0051b814
        charge(ctx, 6);
        jal(ctx, 0x51B814u, gen::fn_SyncDmaForRead_0051ade0);
        lw(v1, v0, 8);
        v0 = 1;
        cc = v1 == v0;  // the condition, before the delay slot changes it
        v0 = 0x980000;
        if (!cc) {
            goto L_0051b82c;
        }
        // 0x0051b834
        charge(ctx, 3);
        s0 = s7;
        s1 = addiu(v0, 22080);
        if (i64(s4) > 0) {
            // 0x0051b840
            charge(ctx, 4);
            v0 = 0x980000;
            s3 = s4;
            s2 = addiu(v0, 21888);  // &0x985580
            for (;;) {
                // 0x0051b850
                charge(ctx, 19);
                lw(a1, s2, 8);
                a0 = s1;
                s3 = addiu(s3, -1);
                a1 = addu(s1, a1);
                a1 = addiu(a1, -1);
                jal(ctx, 0x51B860u, gen::fn_InvalidDCache_00503b98);
                lw(a1, s2, 8);
                a0 = s0;
                a1 = addu(s0, a1);
                a1 = addiu(a1, -1);
                jal(ctx, 0x51B874u, gen::fn_SyncDCache_00503a58);
                lw(a2, s2, 8);
                a0 = s0;
                a1 = s1;
                jal(ctx, 0x51B884u, gen::fn_memcpy_00521250);
                lw(v1, s2, 8);
                s0 = addu(s0, v1);
                s1 = addu(s1, v1);
                if (s3 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x0051b89c
        charge(ctx, 1);
        v0 = s4;
        // 0x0051b8a0 (the shared epilogue, written out on this path)
        charge(ctx, 11);
        ld(ra, sp, 0x90);
        ld(s7, sp, 0x80);
        ld(s6, sp, 0x70);
        ld(s5, sp, 0x60);
        ld(s4, sp, 0x50);
        ld(s3, sp, 0x40);
        ld(s2, sp, 0x30);
        ld(s1, sp, 0x20);
        ld(s0, sp, 0x10);
        sp = addiu(sp, 0xA0);
        return;
    }
L_0051b82c:
    charge(ctx, 2);
    v0 = 0;
    // 0x0051b8a0 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x90);
    ld(s7, sp, 0x80);
    ld(s6, sp, 0x70);
    ld(s5, sp, 0x60);
    ld(s4, sp, 0x50);
    ld(s3, sp, 0x40);
    ld(s2, sp, 0x30);
    ld(s1, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0xA0);
}

// 0x0051C0C0 _sceMcCoreGetConnection -- 56 bytes; frame 0x10: ra sp+0x0
// libmc2 core: the socket's dbc connection state (sceDbcGetConnection).
void _sceMcCoreGetConnection(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051c0c0
    enter(ctx, 14);  // entry check point + this block's cycles
    v1 = 36;
    sp = addiu(sp, -0x10);
    mult(a0, a0, v1);
    v0 = 0x980000;
    sd(ra, sp, 0x0);
    v0 = addiu(v0, 21768);  // &0x985508
    v0 = addu(v0, a0);
    link(ctx, 0x51C0DCu);  // $ra first: the delay slot below depends on it
    lw(a0, v0, 4);
    call(ctx, gen::fn_sceDbcGetConnection_0051cad0);
    v0 = v0 ^ 0x3;
    ld(ra, sp, 0x0);
    v0 = sltu(0, v0);
    sp = addiu(sp, 0x10);
}

// 0x0051C130 _sceMcCoreCreateSocket -- 288 bytes; frame 0x70: s1 sp+0x40, s2 sp+0x50, ra sp+0x60, s0 sp+0x30
// libmc2 core: create a socket in a free slot ("MC2SOCKET" record, sceDbcCreateSocket).
void _sceMcCoreCreateSocket(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051c130
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(s1, sp, 0x40);
    sd(s2, sp, 0x50);
    s1 = a0;
    sd(ra, sp, 0x60);
    link(ctx, 0x51C144u);  // $ra first: the delay slot below depends on it
    sd(s0, sp, 0x30);
    call(ctx, gen::fn__get_free_slot_0051c0f8);
    s2 = v0;
    v0 = si(-1);
    if (i64(s2) >= 0) {
        // 0x0051c158
        charge(ctx, 38);
        lw(v0, s1, 0);
        t1 = 0x7C0000;
        lw(a2, s1, 8);
        s0 = 0x980000;
        lw(t0, s1, 12);
        s0 = addiu(s0, 21952);  // &0x9855C0
        lw(v1, s1, 4);
        a3 = 2;
        sw(v0, sp, 0x0);
        a0 = s0;
        sw(a2, sp, 0xC);
        a1 = 0;
        sw(v1, sp, 0x8);
        a2 = 256;
        sw(t0, sp, 0x10);
        t2 = addiu(t1, -6512);  // "MC2SOCKET"
        ldl(v0, t2, 7);  // 0x7BE697
        ldr(v0, t2, 0);  // 0x7BE690
        lh(v1, t2, 8);  // 0x7BE698
        sdl(v0, sp, 0x1B);
        sdr(v0, sp, 0x14);
        sh(v1, sp, 0x1C);
        sw(a3, sp, 0x4);
        lw(v0, sp, 0x0);
        v0 = v0 | 0x1;
        link(ctx, 0x51C1BCu);  // $ra first: the delay slot below depends on it
        sw(v0, sp, 0x0);
        call(ctx, gen::fn_memset_00521408);
        a1 = s0;
        a0 = sp;
        a2 = addiu(a1, 128);  // &0x985640
        jal(ctx, 0x51C1CCu, gen::fn_sceDbcCreateSocket_0051c770);
        v1 = 36;
        a0 = 0x980000;
        mult(a2, s2, v1);
        a3 = addiu(a0, 21768);  // &0x985508
        v1 = addu(a3, a2);
        sw(v0, v1, 4);
        if (i64(v0) >= 0) {
            // 0x0051c1f8
            charge(ctx, 16);
            a0 = addu(a2, a3);
            v0 = 1;
            sw(v0, a0, 0);
            v1 = addu(a3, a2);
            sw(zero, v1, 28);
            v0 = v1;
            sw(zero, v0, 32);
            a0 = v0;
            v1 = 512;
            a1 = v0;
            sw(v1, a0, 8);
            v0 = 16;
            sw(v0, a1, 12);
            v1 = 16384;
            sw(v1, a0, 16);
            v0 = s2;
        } else {
            // 0x0051c1f0
            charge(ctx, 2);
            v0 = si(-1);
        }
    }
    // 0x0051c238 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x60);
    ld(s2, sp, 0x50);
    ld(s1, sp, 0x40);
    ld(s0, sp, 0x30);
    sp = addiu(sp, 0x70);
}

// 0x0051C3B8 sceDbcInit -- 672 bytes; frame 0xC0: fp sp+0xA0, ra sp+0xB0, s7 sp+0x90, s6 sp+0x80, s5 sp+0x70, s4 sp+0x60, s3 sp+0x50, s2 sp+0x40, s1 sp+0x30, s0 sp+0x20
// libdbc: sceDbcInit: bind the dbcman RPC server, check its version, create the semaphore, set the work address.
void sceDbcInit(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0051c3b8
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    v1 = 1;
    sd(fp, sp, 0xA0);
    sd(ra, sp, 0xB0);
    fp = 0x780000;
    sd(s7, sp, 0x90);
    sd(s6, sp, 0x80);
    sd(s5, sp, 0x70);
    sd(s4, sp, 0x60);
    sd(s3, sp, 0x50);
    sd(s2, sp, 0x40);
    sd(s1, sp, 0x30);
    sd(s0, sp, 0x20);
    lw(v0, fp, 0x2B00);
    s7 = 0x990000;
    if (v0 != v1) {
        // 0x0051c400
        charge(ctx, 5);
        a0 = 0;
        link(ctx, 0x51C404u);  // $ra first: the delay slot below depends on it
        sw(zero, s7, 28672);
        call(ctx, gen::fn_sceSifInitRpc_005068a8);
        s1 = 0x990000;
        for (;;) {
            // 0x0051c43c
            charge(ctx, 8);
            s0 = addiu(s1, 26432);
            a1 = lui(0x8000);
            a0 = s0;
            a1 = a1 | 0x1300;
            a2 = 0;
            jal(ctx, 0x51C44Cu, gen::fn_sceSifBindRpc_00507050);
            a0 = 0x7C0000;
            if (i64(v0) < 0) {
                goto L_0051c5c0;
            }
            // 0x0051c45c
            charge(ctx, 3);
            lw(v0, s0, 36);
            v1 = 0x10000;
            if (v0 != 0) {
                break;
            }
            backedge(ctx);
            // 0x0051c418
            charge(ctx, 2);
            v0 = si(-1);
            for (;;) {
                // 0x0051c420
                charge(ctx, 7);
                v1 = addiu(v1, -1);
                if (v1 == v0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x0051c468
        charge(ctx, 7);
        jal(ctx, 0x51C468u, gen::fn_sceDbcGetModVersion_0051c360);
        s0 = v0;
        v1 = 50;
        v0 = sra(s0, 4);
        a0 = 0x7C0000;
        if (v0 == v1) {
            // 0x0051c4b0
            charge(ctx, 2);
            s1 = 0x990000;
            for (;;) {
                // 0x0051c4dc
                charge(ctx, 8);
                s0 = addiu(s1, 26512);
                a1 = lui(0x8000);
                a0 = s0;
                a1 = a1 | 0x131C;
                a2 = 0;
                jal(ctx, 0x51C4ECu, gen::fn_sceSifBindRpc_00507050);
                a0 = 0x7C0000;
                if (i64(v0) < 0) {
                    goto L_0051c5c0;
                }
                // 0x0051c4fc
                charge(ctx, 3);
                lw(v0, s0, 36);
                cc = v0 == 0;  // the condition, before the delay slot changes it
                v0 = 0x990000;
                if (!cc) {
                    break;
                }
                backedge(ctx);
                // 0x0051c4b8
                charge(ctx, 2);
                v1 = 0x10000;
                v0 = si(-1);
                for (;;) {
                    // 0x0051c4c0
                    charge(ctx, 7);
                    v1 = addiu(v1, -1);
                    if (v1 == v0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x0051c508
            charge(ctx, 6);
            s3 = lui(0x8000);
            s6 = addiu(v0, 26552);
            s2 = 0;
            s3 = s3 | 0x131E;
            s5 = addiu(s6, 36);
            s4 = 0;
            for (;;) {
                // 0x0051c520
                charge(ctx, 3);
                s1 = s4;
                s0 = s5;
                for (;;) {
                    // 0x0051c554
                    charge(ctx, 6);
                    a0 = addu(s1, s6);
                    a1 = addu(s2, s3);
                    a2 = 0;
                    jal(ctx, 0x51C55Cu, gen::fn_sceSifBindRpc_00507050);
                    a0 = 0x7C0000;
                    if (i64(v0) < 0) {
                        goto L_0051c5c0;
                    }
                    // 0x0051c56c
                    charge(ctx, 3);
                    lw(v0, s0, 0);
                    v1 = 0x10000;
                    if (v0 != 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0051c530
                    charge(ctx, 2);
                    v0 = si(-1);
                    for (;;) {
                        // 0x0051c538
                        charge(ctx, 7);
                        v1 = addiu(v1, -1);
                        if (v1 == v0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
                // 0x0051c578
                charge(ctx, 5);
                s2 = addiu(s2, 1);
                s5 = addiu(s5, 40);
                v0 = slti(s2, 2);
                s4 = addiu(s4, 40);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0051c58c
            charge(ctx, 11);
            v0 = 0x7C0000;
            v1 = 1;
            v0 = addiu(v0, -6384);  // "sceDbc_sema"
            a1 = 127;
            sw(v1, sp, 0x8);
            a0 = sp;
            sw(a1, sp, 0x4);
            link(ctx, 0x51C5A8u);  // $ra first: the delay slot below depends on it
            sw(v0, sp, 0x14);
            call(ctx, gen::fn__sceCreateSema_00503160);
            sw(v0, s7, 28672);
            if (i64(v0) >= 0) {
                // 0x0051c5d0
                charge(ctx, 4);
                v0 = 0x990000;
                v1 = 15;
                v0 = addiu(v0, 28608);  // &0x996FC0
                v0 = addiu(v0, 60);  // &0x996FFC
                for (;;) {
                    // 0x0051c5e0
                    charge(ctx, 7);
                    sw(zero, v0, 0);
                    v1 = addiu(v1, -1);
                    v0 = addiu(v0, -4);
                    if (i64(v1) < 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0051c5fc
                charge(ctx, 11);
                s0 = 0x990000;
                a0 = 0x7C0000;
                s0 = addiu(s0, 28480);  // &0x996F40
                a0 = addiu(a0, -6368);  // "libdbc: SifDmaAddr %08x\n"
                a1 = s0;
                jal(ctx, 0x51C60Cu, gen::fn_DPRINT_0051d588);
                a0 = s0;
                jal(ctx, 0x51C614u, gen::fn_sceDbcSetWorkAddr_0051c700);
                v1 = 1;
                v0 = 1;
                sw(v1, fp, 0x2B00);
            } else {
                // 0x0051c5b8
                charge(ctx, 2);
                v0 = 0;
            }
        } else {
            // 0x0051c484
            charge(ctx, 11);
            a0 = addiu(a0, -6472);
            jal(ctx, 0x51C484u, gen::fn_scePrintf_00505e48);
            a0 = 0x7C0000;
            t0 = s0 & 0xFF;
            a0 = addiu(a0, -6432);  // "[libdbc.a = %d.%02x, dbcman.irx = %d.%02x]\n"
            a1 = 3;
            a2 = 32;
            a3 = sra(s0, 8);
            jal(ctx, 0x51C4A0u, gen::fn_scePrintf_00505e48);
            v0 = 0;
        }
    } else {
        // 0x0051c3f8
        charge(ctx, 2);
        v0 = 1;
    }
    // 0x0051c628 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0xB0);
    ld(fp, sp, 0xA0);
    ld(s7, sp, 0x90);
    ld(s6, sp, 0x80);
    ld(s5, sp, 0x70);
    ld(s4, sp, 0x60);
    ld(s3, sp, 0x50);
    ld(s2, sp, 0x40);
    ld(s1, sp, 0x30);
    ld(s0, sp, 0x20);
    sp = addiu(sp, 0xC0);
    return;
L_0051c5c0:
    charge(ctx, 4);
    a0 = addiu(a0, -6496);
    jal(ctx, 0x51C5C0u, gen::fn_DPRINT_0051d588);
    v0 = 0;
    // 0x0051c628 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0xB0);
    ld(fp, sp, 0xA0);
    ld(s7, sp, 0x90);
    ld(s6, sp, 0x80);
    ld(s5, sp, 0x70);
    ld(s4, sp, 0x60);
    ld(s3, sp, 0x50);
    ld(s2, sp, 0x40);
    ld(s1, sp, 0x30);
    ld(s0, sp, 0x20);
    sp = addiu(sp, 0xC0);
}

// 0x0051D6F8 sceSpu2MemAllocate -- 528 bytes; leaf frame (no stack)
// libspu2: sceSpu2MemAllocate: first-fit allocation (16-byte rounded) in the SPU2 memory block table.
void sceSpu2MemAllocate(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0051d6f8
    enter(ctx, 9);  // entry check point + this block's cycles
    t4 = 0x780000;
    v0 = lui(0xFFFF);
    a0 = addiu(a0, 15);
    v0 = v0 | 0xFFF0;
    lw(t0, t4, 11032);  // 0x782B18
    t3 = a0 & v0;
    t1 = 0;
    t5 = 0x780000;
    for (;;) {
        // 0x0051d728
        charge(ctx, 3);
        lw(a1, t0, 0);
        a2 = t0;
        if (i64(a1) < 0) {
            // 0x0051d734
            charge(ctx, 3);
            lw(a2, t0, 4);
            v0 = sltu(t3, a2);
            if (a2 != t3) {
                // 0x0051d748
                charge(ctx, 2);
                t2 = si(-1);
                if (v0 != 0) {
                    // 0x0051d750
                    charge(ctx, 5);
                    t1 = 0x780000;
                    lw(v0, t1, 11044);  // 0x782B24
                    v0 = addiu(v0, -1);
                    a3 = 0;
                    if (i64(v0) > 0) {
                        // 0x0051d764
                        charge(ctx, 4);
                        lw(v0, t4, 11032);
                        lw(v1, v0, 0);
                        if (v1 != 0) {
                            for (;;) {
                                // 0x0051d780
                                charge(ctx, 6);
                                lw(v0, t1, 11044);
                                a3 = addiu(a3, 1);
                                v0 = addiu(v0, -1);
                                v0 = slt(a3, v0);
                                cc = v0 == 0;  // the condition, before the delay slot changes it
                                v0 = 12;
                                if (cc) {
                                    break;
                                }
                                // 0x0051d798
                                charge(ctx, 6);
                                lw(a0, t4, 11032);
                                mult(v0, a3, v0);
                                v0 = addu(v0, a0);
                                lw(v1, v0, 0);
                                if (v1 == 0) {
                                    goto L_0051d7b0_11;
                                }
                                backedge(ctx);
                            }
                        } else {
                            // 0x0051d774
                            charge(ctx, 2);
                            t2 = 0;
                        }
                    }
                L_0051d7b4:
                    charge(ctx, 2);
                    a0 = 12;
                    if (i64(t2) < 0) {
                        // 0x0051d7f8
                        charge(ctx, 2);
                        t1 = t0;
                        sw(t3, t1, 4);
                    } else {
                        // 0x0051d7bc
                        charge(ctx, 15);
                        lw(v1, t4, 11032);
                        mult(a0, t2, a0);
                        lw(a3, t0, 8);
                        a1 = addu(a1, t3);
                        v0 = lui(0x8000);
                        a1 = a1 | v0;
                        a2 = subu(a2, t3);
                        t1 = t0;
                        v1 = addu(v1, a0);
                        sw(a1, v1, 0);
                        sw(a2, v1, 4);
                        sw(a3, v1, 8);
                        sw(v1, t0, 8);
                        sw(t3, t0, 4);
                    }
                }
            } else {
                // 0x0051d740
                charge(ctx, 2);
                t1 = t0;
            }
            // 0x0051d800
            charge(ctx, 1);
            a2 = t0;
        }
        // 0x0051d804
        charge(ctx, 2);
        lw(t0, a2, 8);
        if (t1 == 0) {
            backedge(ctx);
            // 0x0051d720
            charge(ctx, 2);
            if (t0 != 0) {
                continue;
            }
        }
        break;
    }
    // 0x0051d80c
    charge(ctx, 2);
    if (t1 != 0) {
        lw(v1, t1, 0);
    } else {
        // 0x0051d814
        charge(ctx, 5);
        v1 = addiu(t5, 11064);
        lw(v0, v1, 4);
        v0 = sltu(v0, t3);
        a1 = 0x780000;
        if (v0 != 0) {
            // 0x0051d8b8 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            v0 = si(-1);
            return;
        }
        // 0x0051d828
        charge(ctx, 6);
        t2 = si(-1);
        lw(v0, a1, 11044);
        v0 = addiu(v0, -1);
        v0 = slt(t1, v0);
        a3 = 0;
        if (v0 != 0) {
            // 0x0051d840
            charge(ctx, 4);
            lw(v0, t4, 11032);
            lw(v1, v0, 0);
            if (v1 != 0) {
                for (;;) {
                    // 0x0051d858
                    charge(ctx, 6);
                    lw(v0, a1, 11044);
                    a3 = addiu(a3, 1);
                    v0 = addiu(v0, -1);
                    v0 = slt(a3, v0);
                    cc = v0 == 0;  // the condition, before the delay slot changes it
                    v0 = 12;
                    if (cc) {
                        break;
                    }
                    // 0x0051d870
                    charge(ctx, 6);
                    lw(a0, t4, 11032);
                    mult(v0, a3, v0);
                    v0 = addu(v0, a0);
                    lw(v1, v0, 0);
                    if (v1 == 0) {
                        goto L_0051d888_24;
                    }
                    backedge(ctx);
                }
            } else {
                // 0x0051d850
                charge(ctx, 2);
                t2 = 0;
            }
        }
    L_0051d88c:
        charge(ctx, 2);
        v0 = 12;
        if (i64(t2) < 0) {
            // 0x0051d8b8 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            v0 = si(-1);
            return;
        }
        // 0x0051d894
        charge(ctx, 9);
        lw(v1, t4, 11032);
        mult(v0, t2, v0);
        lw(a1, t5, 11064);
        t1 = addu(v1, v0);
        sw(zero, t1, 8);
        sw(a1, t1, 0);
        sw(t3, t1, 4);
        sw(t1, a2, 8);
        // 0x0051d8c0
        charge(ctx, 1);
        lw(v1, t1, 0);
        goto L_0051d8c4;
    }
L_0051d8c4:
    charge(ctx, 10);
    v0 = 0x7FFF0000;
    v0 = v0 | 0xFFFF;
    lw(a0, t1, 4);
    v1 = v1 & v0;
    sw(v1, t1, 0);
    a0 = addu(v1, a0);
    lw(v0, t5, 11064);
    v0 = sltu(v0, a0);
    a1 = addiu(t5, 11064);
    if (v0 != 0) {
        // 0x0051d8ec
        charge(ctx, 5);
        v1 = 0x780000;
        sw(a0, t5, 11064);
        lw(v0, v1, 11056);  // 0x782B30
        v0 = subu(v0, a0);
        sw(v0, a1, 4);
    }
    // 0x0051d900 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    lw(v0, t1, 0);
    return;
L_0051d7b0_11:
    charge(ctx, 1);
    t2 = a3;
    goto L_0051d7b4;
L_0051d888_24:
    charge(ctx, 1);
    t2 = a3;
    goto L_0051d88c;
}

// 0x0051DA48 sceSkInit -- 8 bytes; leaf frame (no stack)
// libsk: sceSkInit returns 0.
void sceSkInit(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0051da48
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x0051DA50 sceSkSsInit -- 132 bytes; frame 0x20: s0 sp+0x0, ra sp+0x10
// libsk: sceSkSsInit: sceSdRemoteInit, the callback init and the init remote call.
void sceSkSsInit(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051da50
    enter(ctx, 33);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    s0 = a0;
    jal(ctx, 0x51DA5Cu, gen::fn_sceSdRemoteInit_00512868);
    a0 = s0;
    jal(ctx, 0x51DA64u, gen::fn_sceSdRemoteCallbackInit_00512d48);
    s0 = v0;
    a0 = 1;
    a1 = 0x8010;
    a2 = 2432;
    a3 = 16383;
    jal(ctx, 0x51DA7Cu, gen::fn_sceSdRemote_005129c0);
    a0 = 1;
    a1 = 0x8010;
    a2 = 2688;
    a3 = 16383;
    jal(ctx, 0x51DA90u, gen::fn_sceSdRemote_005129c0);
    a0 = 1;
    a1 = 0x8010;
    a2 = 2433;
    a3 = 0;
    jal(ctx, 0x51DAA4u, gen::fn_sceSdRemote_005129c0);
    a0 = 1;
    a1 = 0x8010;
    a2 = 2689;
    a3 = 0;
    jal(ctx, 0x51DAB8u, gen::fn_sceSdRemote_005129c0);
    v0 = s0;
    ld(ra, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0051DB00 sceSkSsSOUND_Control -- 188 bytes; frame 0xC0: s1 sp+0x10, s2 sp+0x20, s0 sp+0x0, ra sp+0x30
// libsk: sceSkSsSOUND_Control: fill the sound command block (0x782B80) and send it with sceSdRemote.
void sceSkSsSOUND_Control(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051db00
    enter(ctx, 47);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(s1, sp, 0x10);
    s1 = 0x780000;
    sd(s2, sp, 0x20);
    sd(s0, sp, 0x0);
    s2 = a0;
    s0 = addiu(s1, 11136);  // &sk_sound_cmdblk
    sd(a1, sp, 0x88);
    sd(a2, sp, 0x90);
    a0 = s0;
    sd(ra, sp, 0x30);
    a1 = 0;
    sd(a3, sp, 0x98);
    a2 = 64;
    sd(t0, sp, 0xA0);
    s0 = addiu(s0, 4);  // &sk_sound_cmdblk+0x4
    sd(t1, sp, 0xA8);
    sd(t2, sp, 0xB0);
    link(ctx, 0x51DB48u);  // $ra first: the delay slot below depends on it
    sd(t3, sp, 0xB8);
    call(ctx, gen::fn_memset_00521408);
    sw(zero, s1, 11136);  // sk_sound_cmdblk
    v0 = 2;
    sw(v0, s0, 0);  // sk_sound_cmdblk+0x4
    a2 = addiu(s1, 11136);  // &sk_sound_cmdblk
    lw(v0, sp, 0x88);
    s0 = addiu(s0, 4);  // &sk_sound_cmdblk+0x8
    sw(s2, s0, 0);  // sk_sound_cmdblk+0x8
    a0 = 1;
    s0 = addiu(s0, 4);  // &sk_sound_cmdblk+0xC
    a1 = 0x90F0;
    lw(v1, sp, 0x90);
    a3 = 64;
    sw(v0, s0, 0);  // sk_sound_cmdblk+0xC
    s0 = addiu(s0, 4);  // &sk_sound_cmdblk+0x10
    lw(t0, sp, 0x98);
    sw(v1, s0, 0);  // sk_sound_cmdblk+0x10
    s0 = addiu(s0, 4);  // &sk_sound_cmdblk+0x14
    lw(v0, sp, 0xA0);
    sw(t0, s0, 0);  // sk_sound_cmdblk+0x14
    link(ctx, 0x51DB9Cu);  // $ra first: the delay slot below depends on it
    sw(v0, s0, 4);  // sk_sound_cmdblk+0x18
    call(ctx, gen::fn_sceSdRemote_005129c0);
    ld(ra, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0xC0);
}

// 0x0051DF58 sceSkSsSESQ_Control -- 204 bytes; frame 0xD0: s2 sp+0x20, s3 sp+0x30, s0 sp+0x0, s1 sp+0x10, ra sp+0x40
// libsk: sceSkSsSESQ_Control: fill the SE-sequence command block (0x782C00) and send it.
void sceSkSsSESQ_Control(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051df58
    enter(ctx, 51);  // entry check point + this block's cycles
    sp = addiu(sp, -0xD0);
    sd(s2, sp, 0x20);
    s2 = 0x780000;
    sd(s3, sp, 0x30);
    sd(s0, sp, 0x0);
    s3 = a0;
    s0 = addiu(s2, 11264);  // &sk_sesq_cmdblk
    sd(a1, sp, 0x98);
    sd(a2, sp, 0xA0);
    a0 = s0;
    sd(s1, sp, 0x10);
    a1 = 0;
    sd(ra, sp, 0x40);
    a2 = 64;
    sd(a3, sp, 0xA8);
    s1 = s0;
    sd(t0, sp, 0xB0);
    s0 = addiu(s0, 4);  // &sk_sesq_cmdblk+0x4
    sd(t1, sp, 0xB8);
    sd(t2, sp, 0xC0);
    link(ctx, 0x51DFA8u);  // $ra first: the delay slot below depends on it
    sd(t3, sp, 0xC8);
    call(ctx, gen::fn_memset_00521408);
    v0 = 0x4000000;
    v1 = 2;
    sw(v0, s2, 11264);  // sk_sesq_cmdblk
    a2 = s1;
    sw(v1, s0, 0);  // sk_sesq_cmdblk+0x4
    a0 = 1;
    s0 = addiu(s0, 4);  // &sk_sesq_cmdblk+0x8
    a1 = 0x90F0;
    lw(v0, sp, 0x98);
    a3 = 64;
    sw(s3, s0, 0);  // sk_sesq_cmdblk+0x8
    s0 = addiu(s0, 4);  // &sk_sesq_cmdblk+0xC
    lw(t0, sp, 0xA0);
    sw(v0, s0, 0);  // sk_sesq_cmdblk+0xC
    s0 = addiu(s0, 4);  // &sk_sesq_cmdblk+0x10
    lw(v1, sp, 0xA8);
    sw(t0, s0, 0);  // sk_sesq_cmdblk+0x10
    s0 = addiu(s0, 4);  // &sk_sesq_cmdblk+0x14
    lw(v0, sp, 0xB0);
    sw(v1, s0, 0);  // sk_sesq_cmdblk+0x14
    link(ctx, 0x51E000u);  // $ra first: the delay slot below depends on it
    sw(v0, s0, 4);  // sk_sesq_cmdblk+0x18
    call(ctx, gen::fn_sceSdRemote_005129c0);
    ld(ra, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0xD0);
}

// 0x0051E028 sceSkSsSESQ_Status -- 180 bytes; frame 0xD0: s2 sp+0x20, s3 sp+0x30, s0 sp+0x0, s1 sp+0x10, ra sp+0x40
// libsk: sceSkSsSESQ_Status: SE-sequence status query through the command block.
void sceSkSsSESQ_Status(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051e028
    enter(ctx, 45);  // entry check point + this block's cycles
    sp = addiu(sp, -0xD0);
    sd(s2, sp, 0x20);
    s2 = 0x780000;
    sd(s3, sp, 0x30);
    sd(s0, sp, 0x0);
    s3 = a0;
    s0 = addiu(s2, 11264);  // &sk_sesq_cmdblk
    sd(a1, sp, 0x98);
    sd(a2, sp, 0xA0);
    a0 = s0;
    sd(s1, sp, 0x10);
    a1 = 0;
    sd(ra, sp, 0x40);
    a2 = 64;
    sd(a3, sp, 0xA8);
    s1 = s0;
    sd(t0, sp, 0xB0);
    s0 = addiu(s0, 4);  // &sk_sesq_cmdblk+0x4
    sd(t1, sp, 0xB8);
    sd(t2, sp, 0xC0);
    link(ctx, 0x51E078u);  // $ra first: the delay slot below depends on it
    sd(t3, sp, 0xC8);
    call(ctx, gen::fn_memset_00521408);
    v0 = 0x4000000;
    v1 = 3;
    sw(v0, s2, 11264);  // sk_sesq_cmdblk
    a2 = s1;
    sw(v1, s0, 0);  // sk_sesq_cmdblk+0x4
    a0 = 1;
    lw(v1, sp, 0x98);
    s0 = addiu(s0, 4);  // &sk_sesq_cmdblk+0x8
    sw(s3, s0, 0);  // sk_sesq_cmdblk+0x8
    a1 = 0x90F0;
    s0 = addiu(s0, 4);  // &sk_sesq_cmdblk+0xC
    a3 = 64;
    lw(v0, sp, 0xA0);
    sw(v1, s0, 0);  // sk_sesq_cmdblk+0xC
    link(ctx, 0x51E0B8u);  // $ra first: the delay slot below depends on it
    sw(v0, s0, 4);  // sk_sesq_cmdblk+0x10
    call(ctx, gen::fn_sceSdRemote_005129c0);
    ld(ra, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0xD0);
}

// 0x00520728 malloc -- 32 bytes; frame 0x10: ra sp+0x0
// newlib: malloc(n) = _malloc_r(_impure_ptr, n).
void malloc(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, t7{ctx, 15}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00520728
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = a0;
    sd(ra, sp, 0x0);
    t7 = 0x780000;
    lw(a0, t7, 12080);  // 0x782F30
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn__malloc_r_005209c0(ctx);  // tail call
}

// 0x00520748 cfree -- 32 bytes; frame 0x10: ra sp+0x0
// newlib: cfree(p) = _free_r(_impure_ptr, p).
void cfree(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, t7{ctx, 15}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00520748
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = a0;
    sd(ra, sp, 0x0);
    t7 = 0x780000;
    lw(a0, t7, 12080);  // 0x782F30
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn__free_r_0051fbb0(ctx);  // tail call
}

// 0x0052E9D0 pow -- 20 bytes; frame 0x10: ra sp+0x0
// libm: pow = __ieee754_pow.
void pow(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0052e9d0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn___ieee754_pow_005296f0(ctx);  // tail call
}

// 0x005379B0 sub_5379B0 -- 68 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// CRI: release a handle: free its +8 resource (sub_54CD40) and clear the 260-byte record.
void sub_5379B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005379b0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    if (s0 != 0) {
        // 0x005379c4
        charge(ctx, 8);
        lw(a0, s0, 8);
        link(ctx, 0x5379C8u);  // $ra first: the delay slot below depends on it
        sw(zero, s0, 8);
        call(ctx, gen::fn_sub_54CD40_0054cd40);
        a0 = s0;
        a1 = 0;
        a2 = 260;
        jal(ctx, 0x5379D8u, gen::fn_memset_00521408);
        sh(zero, s0, 0);
    }
    // 0x005379e4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00537F30 sub_537F30 -- 8 bytes; leaf frame (no stack)
// CRI: a handle's +152 halfword (status).
void sub_537F30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00537f30
    enter(ctx, 2);  // entry check point + this block's cycles
    lh(v0, a0, L::kCriStatus);
}

// 0x00537F40 sub_537F40 -- 44 bytes; leaf frame (no stack)
// CRI: a handle's state byte +14, with 2 for state 1 when +232 is set.
void sub_537F40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00537f40
    enter(ctx, 4);  // entry check point + this block's cycles
    lb(v0, a0, L::kCriState);
    v1 = 1;
    lbu(a1, a0, L::kCriState);
    if (v0 == v1) {
        // 0x00537f50
        charge(ctx, 3);
        lw(v1, a0, L::kCriFlag232);  // state 1 reads as 2 while this is set
        v0 = 2;
        if (v1 == 0) {
            goto L_00537f5c;
        }
        // 0x00537f64 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_00537f5c:
    charge(ctx, 2);
    v0 = sll(a1, 24);
    v0 = sra(v0, 24);
    // 0x00537f64 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00537FE8 width__CQ24_STL8ios_base -- 8 bytes; leaf frame (no stack)
// CRI: a handle's +24 word.
void width__CQ24_STL8ios_base(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00537fe8
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, L::kCriWord24);
}

// 0x00538038 sub_538038 -- 8 bytes; leaf frame (no stack)
// CRI: a handle's +204 word.
void sub_538038(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00538038
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, L::kCriWord204);
}

// 0x005383E8 sub_5383E8 -- 8 bytes; leaf frame (no stack)
// CRI: a handle's +148 word.
void sub_5383E8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x005383e8
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, L::kCriWord148);
}

// 0x005383F0 sub_5383F0 -- 8 bytes; leaf frame (no stack)
// CRI: a handle's +144 word.
void sub_5383F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x005383f0
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, L::kCriWord144);
}

// 0x005389B0 sub_5389B0 -- 332 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// CRI ADXT: the per-status dispatch of a handle's +152 status (jump through its callbacks).
void sub_5389B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005389b0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    lh(v1, s0, 152);
    if (v1 != 0) {
        v0 = 10;
        // 0x005389e0
        charge(ctx, 2);
        if (v1 != v0) {
            v0 = 2;
            // 0x005389f8
            charge(ctx, 2);
            if (v1 != v0) {
                v0 = 3;
                // 0x00538a10
                charge(ctx, 2);
                if (v1 != v0) {
                    v0 = 4;
                    // 0x00538a28
                    charge(ctx, 2);
                    if (v1 != v0) {
                        v0 = 1;
                        // 0x00538a40
                        charge(ctx, 2);
                        if (v1 != v0) {
                            v0 = 15;
                            // 0x00538a58
                            charge(ctx, 2);
                            if (v1 != v0) {
                                lw(v0, s0, 252);
                            } else {
                                // 0x00538a60
                                charge(ctx, 3);
                                jal(ctx, 0x538A60u, gen::fn_sub_535E58_00535e58);
                                lw(v0, s0, 252);
                            }
                        } else {
                            // 0x00538a48
                            charge(ctx, 4);
                            jal(ctx, 0x538A48u, gen::fn_sub_539760_00539760);
                            lw(v0, s0, 252);
                        }
                    } else {
                        // 0x00538a30
                        charge(ctx, 4);
                        jal(ctx, 0x538A30u, gen::fn_sub_537450_00537450);
                        lw(v0, s0, 252);
                    }
                } else {
                    // 0x00538a18
                    charge(ctx, 4);
                    jal(ctx, 0x538A18u, gen::fn_sub_5369E8_005369e8);
                    lw(v0, s0, 252);
                }
            } else {
                // 0x00538a00
                charge(ctx, 4);
                jal(ctx, 0x538A00u, gen::fn_sub_538D78_00538d78);
                lw(v0, s0, 252);
            }
        } else {
            // 0x005389e8
            charge(ctx, 4);
            jal(ctx, 0x5389E8u, gen::fn_sub_536058_00536058);
            lw(v0, s0, 252);
        }
    } else {
        // 0x005389cc
        charge(ctx, 4);
        jal(ctx, 0x5389CCu, gen::fn_sub_538860_00538860);
        lw(v0, s0, 252);
    }
    // 0x00538a6c
    charge(ctx, 2);
    a0 = s0;
    if (v0 == 0) {
        // 0x00538a88
        charge(ctx, 4);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00538a74
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    // 0x00538a98
    charge(ctx, 25);
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    lb(v0, s0, 14);
    lw(a2, s0, 144);
    lw(v1, s0, 244);
    lw(a1, s0, 148);
    mult(a2, a2, v0);
    lw(a3, s0, 252);
    a1 = subu(a1, v1);
    lw(a0, s0, 256);
    v1 = 0x7FFF0000;
    v1 = v1 | 0xFFFF;
    v1 = addu(v1, a1);
    v0 = slti(a1, 0);
    if (v0 != 0) a1 = v1;
    a2 = sll(a2, 1);
    jalr(ctx, 0x538ADCu, a3.u());
    lw(v0, s0, 148);
    ld(ra, sp, 0x8);
    sw(v0, s0, 244);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0053DD10 sub_53DD10 -- 136 bytes; frame 0x40: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s5 sp+0x28, ra sp+0x30
// CRI: sub_53DD98 with six arguments, bracketed by sub_53E088 / sub_53E0A0.
void sub_53DD10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053dd10
    enter(ctx, 34);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s3, sp, 0x18);
    s3 = a3;
    sd(s4, sp, 0x20);
    s4 = t0;
    sd(s5, sp, 0x28);
    sd(ra, sp, 0x30);
    s5 = t1;
    jal(ctx, 0x53DD44u, gen::fn_sub_53E088_0053e088);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    a3 = s3;
    t0 = s4;
    t1 = s5;
    jal(ctx, 0x53DD60u, gen::fn_sub_53DD98_0053dd98);
    s0 = v0;
    jal(ctx, 0x53DD68u, gen::fn_sub_53E0A0_0053e0a0);
    ld(s1, sp, 0x8);
    v0 = s0;
    ld(s2, sp, 0x10);
    ld(s0, sp, 0x0);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x0053EA90 sub_53EA90 -- 368 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// CRI ADXT init ("ADXT/PS2EE Ver.9.44"): the first call initialises the libraries, the lock hooks and the server
// threads; counts the users.
void sub_53EA90(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053ea90
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = 0x780000;
    sd(s0, sp, 0x0);
    s0 = addiu(a0, 30032);  // &0x787550
    v1 = 0x990000;
    v0 = 0x7C0000;
    lw(a0, s0, 0);  // 0x787550
    v1 = addiu(v1, 28720);  // &0x997030
    v0 = addiu(v0, 8808);  // "\nADXT/PS2EE Ver.9.44 Build:Feb 28 2005 19:25:20\n"
    sd(ra, sp, 0x8);
    sw(v0, v1, 0);  // 0x997030
    if (a0 != 0) {
        v0 = addiu(a0, 1);
    } else {
        // 0x0053eac4
        charge(ctx, 74);
        jal(ctx, 0x53EAC4u, gen::fn_sub_5397B8_005397b8);
        jal(ctx, 0x53EACCu, gen::fn_sub_539818_00539818);
        jal(ctx, 0x53EAD4u, gen::fn_sub_562E90_00562e90);
        jal(ctx, 0x53EADCu, gen::fn_sub_562288_00562288);
        jal(ctx, 0x53EAE4u, gen::fn_sub_561870_00561870);
        jal(ctx, 0x53EAECu, gen::fn_sub_53AD70_0053ad70);
        jal(ctx, 0x53EAF4u, gen::fn_sub_545C78_00545c78);
        jal(ctx, 0x53EAFCu, gen::fn_sub_541D48_00541d48);
        jal(ctx, 0x53EB04u, gen::fn_sub_53B080_0053b080);
        jal(ctx, 0x53EB0Cu, gen::fn_sub_5419C0_005419c0);
        jal(ctx, 0x53EB14u, gen::fn_sub_55DC88_0055dc88);
        jal(ctx, 0x53EB1Cu, gen::fn_sub_565550_00565550);
        a0 = 0x540000;
        a1 = 0;
        a0 = addiu(a0, -5672);  // &sub_53E9D8
        jal(ctx, 0x53EB2Cu, gen::fn_sub_5419F0_005419f0);
        a0 = 0x540000;
        a0 = addiu(a0, -5648);  // &sub_53E9F0
        a1 = 0;
        jal(ctx, 0x53EB3Cu, gen::fn_sub_55DBC0_0055dbc0);
        a0 = 0x780000;
        a0 = addiu(a0, 30064);  // &0x787570
        a1 = 0;
        a2 = 3200;
        jal(ctx, 0x53EB50u, gen::fn_memset_00521408);
        a2 = 0x540000;
        t0 = 0x7C0000;
        a2 = addiu(a2, -5552);  // &r_lock_def_free
        t0 = addiu(t0, 8888);  // "adxt_exec_tsvr"
        a0 = 2;
        a1 = 1;
        a3 = 0;
        jal(ctx, 0x53EB70u, gen::fn_sub_564FE8_00564fe8);
        a1 = 0x540000;
        a3 = 0x7C0000;
        a1 = addiu(a1, -5520);  // &r_lock_def_get_free_item
        a3 = addiu(a3, 8904);  // "adxt_exec_fssvr"
        a0 = 4;
        a2 = 0;
        jal(ctx, 0x53EB8Cu, gen::fn_sub_564DD0_00564dd0);
        v1 = 0x780000;
        a1 = 0x540000;
        a3 = 0x7C0000;
        a3 = addiu(a3, 8920);  // "adxt_exec_main_thrd"
        a1 = addiu(a1, -5584);  // &sub_53EA30
        a2 = 0;
        a0 = 5;
        link(ctx, 0x53EBB0u);  // $ra first: the delay slot below depends on it
        sw(v0, v1, 30052);
        call(ctx, gen::fn_sub_564DD0_00564dd0);
        v1 = 0x780000;
        a1 = 0x780000;
        v1 = addiu(v1, 30056);  // &0x787568
        sw(v0, a1, 30040);  // 0x787558
        sw(zero, v1, 0);  // 0x787568
        a0 = 60;
        a2 = 0x780000;
        link(ctx, 0x53EBD4u);  // $ra first: the delay slot below depends on it
        sw(zero, a2, 30048);
        call(ctx, gen::fn_sub_5497B0_005497b0);
        jal(ctx, 0x53EBDCu, gen::fn_sub_539830_00539830);
        lw(a0, s0, 0);
        v0 = addiu(a0, 1);
    }
    // 0x0053ebec (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x8);
    sw(v0, s0, 0);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0053F8B8 sub_53F8B8 -- 132 bytes; frame 0x20: s2 sp+0x10, s0 sp+0x0, s1 sp+0x8, ra sp+0x18
// CRI: enter the ADX critical section: on the first entry raise the thread priority and suspend the server thread.
void sub_53F8B8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053f8b8
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x790000;
    sd(s2, sp, 0x10);
    s2 = addiu(v0, -31104);  // &0x788680
    lw(v0, s2, 0);  // 0x788680
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x18);
    if (v0 == 0) {
        // 0x0053f8dc
        charge(ctx, 16);
        s0 = 0x790000;
        jal(ctx, 0x53F8DCu, gen::fn__sceGetThreadId_00503050);
        s1 = v0;
        v0 = 0x790000;
        lw(a1, v0, -31152);  // 0x788650
        a0 = s1;
        s0 = addiu(s0, -31016);  // &0x7886D8
        jal(ctx, 0x53F8F4u, gen::fn__sceChangeThreadPriority_00502ff0);
        v1 = 0x790000;
        sw(v0, v1, -144);  // 0x78FF70
        a1 = 0x790000;
        lw(a0, s0, 0);  // 0x7886D8
        link(ctx, 0x53F90Cu);  // $ra first: the delay slot below depends on it
        sw(s1, a1, -140);
        call(ctx, gen::fn_sub_5400B0_005400b0);
        lw(v1, s0, 0);  // 0x7886D8
        lw(v0, s2, 0);
    }
    // 0x0053f91c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    v0 = addiu(v0, 1);
    ld(s0, sp, 0x0);
    sw(v0, s2, 0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0053F940 sub_53F940 -- 112 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// CRI: leave the ADX critical section: on the last exit resume the server thread and restore the priority.
void sub_53F940(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053f940
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v1 = 0x790000;
    sd(s1, sp, 0x8);
    s1 = addiu(v1, -31104);  // &0x788680
    lw(v0, s1, 0);  // 0x788680
    sd(s0, sp, 0x0);
    v0 = addiu(v0, -1);
    sd(ra, sp, 0x10);
    sw(v0, s1, 0);  // 0x788680
    if (v0 == 0) {
        // 0x0053f968
        charge(ctx, 10);
        s0 = 0x790000;
        s0 = addiu(s0, -31016);  // &0x7886D8
        link(ctx, 0x53F970u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, 0);  // 0x7886D8
        call(ctx, gen::fn_sub_540118_00540118);
        link(ctx, 0x53F978u);  // $ra first: the delay slot below depends on it
        lw(v1, s0, 0);  // 0x7886D8
        call(ctx, gen::fn__sceGetThreadId_00503050);
        v1 = 0x790000;
        lw(a1, v1, -144);  // 0x78FF70
        a0 = v0;
        jal(ctx, 0x53F988u, gen::fn__sceChangeThreadPriority_00502ff0);
    }
    // 0x0053f990
    charge(ctx, 3);
    lw(v0, s1, 0);
    if (i64(v0) < 0) {
        sw(zero, s1, 0);
    }
    // 0x0053f99c
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00540EC0 ADXM_ExecMain -- 20 bytes; frame 0x10: ra sp+0x0
// CRI: ADXM_ExecMain = sub_53F640.
void ADXM_ExecMain(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00540ec0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_53F640_0053f640(ctx);  // tail call
}

// 0x00541008 sub_541008 -- 52 bytes; frame 0x10: ra sp+0x0
// CRI: sub_540ED8, sub_5414E0, sub_540FE0, bracketed by sub_5656C0 / sub_5656F0.
void sub_541008(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00541008
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x541010u, gen::fn_sub_5656C0_005656c0);
    jal(ctx, 0x541018u, gen::fn_sub_540ED8_00540ed8);
    jal(ctx, 0x541020u, gen::fn_sub_5414E0_005414e0);
    jal(ctx, 0x541028u, gen::fn_sub_540FE0_00540fe0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5656F0_005656f0(ctx);  // tail call
}

// 0x00541A78 cosl_1 -- 20 bytes; frame 0x10: ra sp+0x0
// CRI: tail call to sub_560C88.
void cosl_1(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00541a78
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_560C88_00560c88(ctx);  // tail call
}

// 0x00541A90 coshl_1 -- 20 bytes; frame 0x10: ra sp+0x0
// CRI: tail call to sub_560D20 (unlock helper).
void coshl_1(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00541a90
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_560D20_00560d20(ctx);  // tail call
}

// 0x00541AC0 hypotf_1 -- 20 bytes; frame 0x10: ra sp+0x0
// CRI: tail call to sub_560EB0.
void hypotf_1(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00541ac0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_560EB0_00560eb0(ctx);  // tail call
}

// 0x00545FC8 sub_545FC8 -- 72 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// CRI: adxstm_Create, bracketed by coshl_2 / sub_545C40.
void sub_545FC8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00545fc8
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x545FDCu, gen::fn_coshl_2_00545c38);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x545FE8u, gen::fn_adxstm_Create_00546010);
    s0 = v0;
    jal(ctx, 0x545FF0u, gen::fn_sub_545C40_00545c40);
    ld(s1, sp, 0x8);
    v0 = s0;
    ld(ra, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00546058 sub_546058 -- 44 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// CRI: sub_546088, bracketed by coshl_2 / sub_545C40.
void sub_546058(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00546058
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x546064u, gen::fn_coshl_2_00545c38);
    a0 = s0;
    jal(ctx, 0x54606Cu, gen::fn_sub_546088_00546088);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_545C40_00545c40(ctx);  // tail call
}

// 0x005460E0 sub_5460E0 -- 108 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, ra sp+0x28
// CRI: sub_546150 (five arguments), bracketed by coshl_2 / sub_545C40.
void sub_5460E0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005460e0
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s3, sp, 0x18);
    s3 = a3;
    sd(s4, sp, 0x20);
    sd(ra, sp, 0x28);
    s4 = t0;
    jal(ctx, 0x54610Cu, gen::fn_coshl_2_00545c38);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    a3 = s3;
    t0 = s4;
    jal(ctx, 0x546124u, gen::fn_sub_546150_00546150);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
    gen::fn_sub_545C40_00545c40(ctx);  // tail call
}

// 0x005465A0 sub_5465A0 -- 44 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// CRI: sub_5465D0, bracketed by coshl_2 / sub_545C40.
void sub_5465A0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005465a0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x5465ACu, gen::fn_coshl_2_00545c38);
    a0 = s0;
    jal(ctx, 0x5465B4u, gen::fn_sub_5465D0_005465d0);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_545C40_00545c40(ctx);  // tail call
}

// 0x005466B8 sub_5466B8 -- 76 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// CRI: sub_546708, bracketed by coshl_2 / sub_545C40.
void sub_5466B8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005466b8
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x5466D4u, gen::fn_coshl_2_00545c38);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    jal(ctx, 0x5466E4u, gen::fn_sub_546708_00546708);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_545C40_00545c40(ctx);  // tail call
}

// 0x00548B38 sceInsockBind_2 -- 756 bytes; frame 0x50: s2 sp+0x20, s3 sp+0x28, s5 sp+0x38, s0 sp+0x10, s1 sp+0x18, s4 sp+0x30, s6 sp+0x40, ra sp+0x48
// CRI ADXT: the play-time query ("adxt_GetTime: parameter error" on null arguments).
void sceInsockBind_2(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00548b38
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s2, sp, 0x20);
    s2 = a0;
    sd(s3, sp, 0x28);
    s3 = a1;
    sd(s5, sp, 0x38);
    s5 = a2;
    sd(s0, sp, 0x10);
    sd(s1, sp, 0x18);
    sd(s4, sp, 0x30);
    sd(s6, sp, 0x40);
    sd(ra, sp, 0x48);
    if (s2 != 0) {
        // 0x00548b6c
        charge(ctx, 2);
        if (s3 == 0) {
            a0 = 0x7C0000;
        L_00548b80:
            charge(ctx, 4);
            a0 = addiu(a0, 10336);
            jal(ctx, 0x548B80u, gen::fn_sub_53AE08_0053ae08);
            ld(s0, sp, 0x10);
        } else {
            // 0x00548b74
            charge(ctx, 2);
            s0 = 0x790000;
            if (s5 == 0) {
                goto L_00548b7c;
            }
            // 0x00548b90
            charge(ctx, 3);
            lw(v0, s0, 15124);
            s1 = 0x790000;
            if (v0 != 0) {
                // 0x00548bb0
                charge(ctx, 6);
                sw(zero, s1, 15204);
                lbu(v1, s2, 1);
                v0 = addiu(v1, -3);
                v0 = sltiu(v0, 2);
                cc = v0 == 0;  // the condition, before the delay slot changes it
                v0 = sll(v1, 24);
                if (!cc) {
                    // 0x00548bc8
                    charge(ctx, 3);
                    lb(v0, s2, 114);
                    if (v0 != 0) {
                        lw(v0, s2, 156);
                    } else {
                        // 0x00548bd4
                        charge(ctx, 11);
                        v0 = 0x780000;
                        lw(a0, s2, 160);
                        lw(v1, v0, 30056);  // 0x787568
                        lw(a1, s2, 156);
                        v1 = subu(v1, a0);
                        v0 = sll(v1, 1);
                        v0 = addu(v0, v1);
                        v0 = sll(v0, 3);
                        v0 = addu(v0, v1);
                        v0 = sll(v0, 2);
                        v0 = addu(v0, a1);
                    }
                    // 0x00548c00
                    charge(ctx, 33);
                    sw(v0, s3, 0);
                    a1 = sp;
                    a2 = addiu(sp, 0x4);
                    a0 = s2;
                    s6 = 0x790000;
                    jal(ctx, 0x548C10u, gen::fn_sub_5489A0_005489a0);
                    lwc1(f1, s3, 0);
                    cvt_s_w(f1, f1);
                    s4 = addiu(s6, 15200);  // &0x793B60
                    lw(a1, sp, 0x0);
                    lw(a2, sp, 0x4);
                    lw(a3, s4, 0);  // 0x793B60
                    mtc1(a1, f0);
                    cvt_s_w(f0, f0);
                    mtc1(a2, f3);
                    cvt_s_w(f3, f3);
                    at = 0x447A0000;
                    mtc1(at, f5);
                    mtc1(a3, f2);
                    cvt_s_w(f2, f2);
                    at = 0x42700000;
                    mtc1(at, f4);
                    div_s(f0, f0, f3);
                    div_s(f1, f1, f2);
                    sub_s(f0, f0, f1);
                    mul_s(f1, f0, f5);
                    c_lt_s(f4, f1);
                    swc1(f1, s1, 15204);
                    if (!cond(ctx)) {
                        // 0x00548c84
                        charge(ctx, 5);
                        at = lui(0xC270);
                        mtc1(at, f0);
                        c_lt_s(f1, f0);
                        if (cond(ctx)) {
                            goto L_00548c98;
                        }
                        lw(v0, s2, 136);
                        goto L_00548df0;
                    }
                L_00548c98:
                    charge(ctx, 5);
                    v0 = 0x790000;
                    a0 = 1;
                    lw(v1, v0, 15160);  // 0x793B38
                    s0 = addiu(s0, 15124);
                    if (v1 == a0) {
                        // 0x00548cac
                        charge(ctx, 11);
                        a1 = sp;
                        lw(s1, s0, 0);
                        a2 = addiu(sp, 0x4);
                        sw(zero, s0, 0);
                        a0 = s2;
                        jal(ctx, 0x548CBCu, gen::fn_sceInsockBind_2_00548b38);
                        link(ctx, 0x548CC4u);  // $ra first: the delay slot below depends on it
                        sw(s1, s0, 0);
                        call(ctx, gen::fn_sub_548AD0_00548ad0);
                        lw(a3, s4, 0);
                        lw(a1, sp, 0x0);
                        lw(a2, sp, 0x4);
                    }
                    // 0x00548cd8
                    charge(ctx, 17);
                    mtc1(a2, f1);
                    cvt_s_w(f1, f1);
                    at = 0x4F000000;
                    mtc1(at, f3);
                    mtc1(a1, f0);
                    cvt_s_w(f0, f0);
                    mtc1(a3, f2);
                    cvt_s_w(f2, f2);
                    div_s(f0, f0, f1);
                    mul_s(f0, f0, f2);
                    c_le_s(f3, f0);
                    cvt_w_s(f1, f0);
                    mfc1(v1, f1);
                    if (!cond(ctx)) {
                        sw(v1, s2, 156);
                    } else {
                        // 0x00548d1c
                        charge(ctx, 6);
                        sub_s(f0, f0, f3);
                        v0 = lui(0x8000);
                        cvt_w_s(f1, f0);
                        mfc1(v1, f1);
                        v1 = v1 | v0;
                        sw(v1, s2, 156);
                    }
                    // 0x00548d34
                    charge(ctx, 4);
                    v1 = 0x780000;
                    lw(v0, v1, 30056);  // 0x787568
                    sw(v0, s2, 160);
                    goto L_00548dec;
                }
                // 0x00548d48
                charge(ctx, 4);
                v1 = 5;
                v0 = sra(v0, 24);
                if (v0 != v1) {
                    sw(zero, s3, 0);
                    // 0x00548de8
                    charge(ctx, 1);
                    s6 = 0x790000;
                } else {
                    // 0x00548d58
                    charge(ctx, 13);
                    lw(a0, s2, 4);
                    s6 = 0x790000;
                    jal(ctx, 0x548D5Cu, gen::fn_sub_543178_00543178);
                    lw(a0, s2, 4);
                    link(ctx, 0x548D68u);  // $ra first: the delay slot below depends on it
                    sw(v0, sp, 0x0);
                    call(ctx, gen::fn_sub_543100_00543100);
                    lw(a0, s2, 4);
                    link(ctx, 0x548D74u);  // $ra first: the delay slot below depends on it
                    sw(v0, sp, 0x4);
                    call(ctx, gen::fn_sub_543130_00543130);
                    v1 = 16;
                    div(v1, v0);
                    if (v0 == 0) {
                        brk(ctx, 0x548D88u, 0x7u);
                    }
                    // 0x00548d8c
                    charge(ctx, 22);
                    lw(v0, sp, 0x0);
                    lwc1(f2, sp, 0x4);
                    cvt_s_w(f2, f2);
                    lwc1(f1, s6, 15200);
                    cvt_s_w(f1, f1);
                    mflo(v1);
                    mult(a1, v0, v1);
                    mtc1(a1, f0);
                    cvt_s_w(f0, f0);
                    sw(a1, sp, 0x0);
                    div_s(f0, f0, f2);
                    mul_s(f0, f0, f1);
                    cvt_w_s(f1, f0);
                    mfc1(v1, f1);
                    sw(v1, s3, 0);
                    lw(v0, s2, 156);
                    v0 = addiu(v0, 1);
                    v1 = addu(v1, v0);
                    sw(v1, s3, 0);
                }
            L_00548dec:
                charge(ctx, 1);
                lw(v0, s2, 136);
            L_00548df0:
                charge(ctx, 6);
                lw(v1, s3, 0);
                v1 = addu(v1, v0);
                sw(v1, s3, 0);
                lw(v0, s6, 15200);
                sw(v0, s5, 0);
                ld(s0, sp, 0x10);
            } else {
                // 0x00548b9c
                charge(ctx, 4);
                jal(ctx, 0x548B9Cu, gen::fn_sub_5489A0_005489a0);
                ld(s0, sp, 0x10);
            }
        }
        // 0x00548e08 (the shared epilogue, written out on this path)
        charge(ctx, 9);
        ld(s1, sp, 0x18);
        ld(s2, sp, 0x20);
        ld(s3, sp, 0x28);
        ld(s4, sp, 0x30);
        ld(s5, sp, 0x38);
        ld(s6, sp, 0x40);
        ld(ra, sp, 0x48);
        sp = addiu(sp, 0x50);
        return;
    }
L_00548b7c:
    charge(ctx, 1);
    a0 = 0x7C0000;
    goto L_00548b80;
}

// 0x00549160 sceInsockListen_2 -- 76 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// CRI: sub_5491B0, bracketed by sub_539848 / sub_539850.
void sceInsockListen_2(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00549160
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x54917Cu, gen::fn_sub_539848_00539848);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    jal(ctx, 0x54918Cu, gen::fn_sub_5491B0_005491b0);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_539850_00539850(ctx);  // tail call
}

// 0x0054D148 expl_4 -- 20 bytes; frame 0x10: ra sp+0x0
// CRI: tail call to sub_5331A8.
void expl_4(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d148
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5331A8_005331a8(ctx);  // tail call
}

// 0x00552658 sub_552658 -- 40 bytes; frame 0x10: ra sp+0x0
// CRI: shutdown step (sub_553FA8, sub_555658); returns 0.
void sub_552658(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00552658
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x552660u, gen::fn_sub_553FA8_00553fa8);
    jal(ctx, 0x552668u, gen::fn_sub_555658_00555658);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00552680 sub_552680 -- 8 bytes; leaf frame (no stack)
// Returns 0.
void sub_552680(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00552680
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x0055A720 dvCiGetStat -- 56 bytes; frame 0x10: ra sp+0x0
// CRI dvCi: a handle's status byte +2 ("handl is null." error for a null handle).
void dvCiGetStat(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055a720
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = a0;
    sd(ra, sp, 0x0);
    if (v0 != 0) {
        // 0x0055a748
        charge(ctx, 1);
        lb(v0, v0, 2);
    } else {
        // 0x0055a730
        charge(ctx, 5);
        a1 = 0x7C0000;
        a1 = addiu(a1, 19880);  // "E0092912:handl is null."
        jal(ctx, 0x55A734u, gen::fn_sub_559DA8_00559da8);
        v0 = 0;
    }
    // 0x0055a74c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0055A9B0 dvci_conv_fname -- 164 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// CRI dvCi: build the CD file name: root + separator + name + ";1", '/' turned into '\\' and upper-cased.
void dvci_conv_fname(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055a9b0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    s1 = a1;
    a1 = 0x7A0000;
    sd(s0, sp, 0x0);
    a1 = addiu(a1, 10880);  // &dvg_ci_root_dir
    s0 = a0;
    sd(ra, sp, 0x10);
    a0 = s1;
    jal(ctx, 0x55A9D0u, gen::fn_strcpy_00524270);
    lb(v1, s0, 0);
    v0 = 47;
    a0 = 92;
    if (v1 != v0) {
        // 0x0055a9e8
        charge(ctx, 2);
        a1 = 0x7C0000;
        if (v1 != a0) {
            // 0x0055a9f0
            charge(ctx, 3);
            a0 = s1;
            a1 = addiu(a1, 20016);
            jal(ctx, 0x55A9F4u, gen::fn_strcat_00523e68);
        }
    }
    // 0x0055a9fc
    charge(ctx, 14);
    a1 = s0;
    s0 = 0x7C0000;
    a0 = s1;
    s0 = addiu(s0, 20024);  // ";1"
    jal(ctx, 0x55AA08u, gen::fn_strcat_00523e68);
    a0 = s1;
    jal(ctx, 0x55AA10u, gen::fn_strlen_00524388);
    a1 = s0;
    v0 = addu(s1, v0);
    a0 = addiu(v0, -2);
    jal(ctx, 0x55AA20u, gen::fn_strcmp_00524128);
    a0 = s1;
    a1 = s0;
    if (v0 != 0) {
        // 0x0055aa34
        charge(ctx, 3);
        jal(ctx, 0x55AA34u, gen::fn_strcat_00523e68);
        a0 = s1;
    }
    // 0x0055aa40
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_559FD8_00559fd8(ctx);  // tail call
}

// 0x0055D2A0 sub_55D2A0 -- 264 bytes; frame 0x30: s1 sp+0x18, s0 sp+0x10, s2 sp+0x20, ra sp+0x28
// CRI LSC_Create: take a free LSC instance for stream a0 ("Illigal parameter", "Not enough instance").
void sub_55D2A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055d2a0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x18);
    s1 = a0;
    sd(s0, sp, 0x10);
    sd(s2, sp, 0x20);
    sd(ra, sp, 0x28);
    if (s1 != 0) {
        // 0x0055d2d0
        charge(ctx, 7);
        a0 = sp;
        jal(ctx, 0x55D2D0u, gen::fn_sub_55DB88_0055db88);
        jal(ctx, 0x55D2D8u, gen::fn_sub_55D240_0055d240);
        s2 = v0;
        if (s2 != 0) {
            sb(zero, s2, 1);
            // 0x0055d300
            charge(ctx, 20);
            a0 = s1;
            sw(s1, s2, 8);
            lw(v1, s1, 0);
            lw(v0, v1, 36);
            a1 = 0;
            jalr(ctx, 0x55D310u, v0.u());
            lw(v1, s1, 0);
            s0 = v0;
            a0 = s1;
            lw(v0, v1, 36);
            a1 = 1;
            jalr(ctx, 0x55D328u, v0.u());
            v1 = 10;
            s0 = addu(s0, v0);
            a0 = 15;
            v0 = sll(s0, 3);
            sw(s0, s2, 24);
            div(v0, v1);
            if (v1 == 0) {
                brk(ctx, 0x55D34Cu, 0x7u);
            }
            // 0x0055d350
            charge(ctx, 4);
            v1 = addiu(s2, 560);
            mflo(v0);
            sw(v0, s2, 20);
            for (;;) {
                // 0x0055d360
                charge(ctx, 7);
                a0 = addiu(a0, -1);
                sw(zero, v1, 0);
                v1 = addiu(v1, -32);
                if (i64(a0) < 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0055d37c
            charge(ctx, 2);
            v0 = 1;
            sb(v0, s2, 0);
        } else {
            // 0x0055d2ec
            charge(ctx, 5);
            a0 = 0x7C0000;
            a0 = addiu(a0, 21816);  // "E2005012802: Not enough instance (LSC_Create)\n"
            jal(ctx, 0x55D2F0u, gen::fn_sub_55DBE8_0055dbe8);
        }
        // 0x0055d384
        charge(ctx, 3);
        a0 = sp;
        jal(ctx, 0x55D384u, gen::fn_sub_55DBA8_0055dba8);
        v0 = s2;
    } else {
        // 0x0055d2bc
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 21768);  // "E2005012801: Illigal parameter=sj (LSC_Create)\n"
        jal(ctx, 0x55D2C0u, gen::fn_sub_55DBE8_0055dbe8);
        v0 = 0;
    }
    // 0x0055d390 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x0055D3A8 sub_55D3A8 -- 80 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// CRI LSC: destroy an instance (stop, then clear its 568 bytes).
void sub_55D3A8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055d3a8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    if (s0 == 0) {
        // 0x0055d3e8
        charge(ctx, 4);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0055d3bc
    charge(ctx, 10);
    jal(ctx, 0x55D3BCu, gen::fn_sub_55D668_0055d668);
    a1 = 0;
    sb(zero, s0, 0);
    a0 = s0;
    ld(ra, sp, 0x8);
    a2 = 568;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_memset_00521408(ctx);  // tail call
}

// 0x0055D3F8 sub_55D3F8 -- 8 bytes; leaf frame (no stack)
// CRI: store a1 at a0+40.
void sub_55D3F8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5};
    // 0x0055d3f8
    enter(ctx, 2);  // entry check point + this block's cycles
    sw(a1, a0, 40);
}

// 0x0055D790 sub_55D790 -- 48 bytes; frame 0x10: ra sp+0x0
// CRI LSC: an instance's status byte +1 (-1 and an error for a null handle).
void sub_55D790(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055d790
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x0055d7b0
        charge(ctx, 1);
        lb(v0, a0, 1);
    } else {
        // 0x0055d79c
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 22152);  // "E2005012809: Illigal parameter lsc=NULL\n"
        jal(ctx, 0x55D7A0u, gen::fn_sub_55DBE8_0055dbe8);
        v0 = si(-1);
    }
    // 0x0055d7b4 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0055D7C0 sub_55D7C0 -- 48 bytes; frame 0x10: ra sp+0x0
// CRI LSC: an instance's +36 word (-1 and an error for a null handle).
void sub_55D7C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055d7c0
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x0055d7e0
        charge(ctx, 1);
        lw(v0, a0, 36);
    } else {
        // 0x0055d7cc
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 22200);  // "E2005012810: Illigal parameter lsc=NULL\n"
        jal(ctx, 0x55D7D0u, gen::fn_sub_55DBE8_0055dbe8);
        v0 = si(-1);
    }
    // 0x0055d7e4 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00560DB8 sub_560DB8 -- 44 bytes; leaf frame (no stack)
// CRI: set a handle's +91 byte, gated by the mode words 0x7A93F8 / 0x7A93F0.
void sub_560DB8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00560db8
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    a2 = 1;
    lw(v1, v0, -27656);  // 0x7A93F8
    if (v1 != a2) {
        sb(a1, a0, 91);
    } else {
        // 0x00560dcc
        charge(ctx, 4);
        v0 = 0x7B0000;
        lw(v1, v0, -27664);  // 0x7A93F0
        if (i64(v1) > 0) {
            sb(a1, a0, 91);
        }
    }
    // 0x00560ddc (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00564FE8 sub_564FE8 -- 108 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, ra sp+0x28
// CRI: sub_565058 (five arguments), bracketed by sub_564978 / sub_564990.
void sub_564FE8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00564fe8
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s3, sp, 0x18);
    s3 = a3;
    sd(s4, sp, 0x20);
    sd(ra, sp, 0x28);
    s4 = t0;
    jal(ctx, 0x565014u, gen::fn_sub_564978_00564978);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    a3 = s3;
    t0 = s4;
    jal(ctx, 0x56502Cu, gen::fn_sub_565058_00565058);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
    gen::fn_sub_564990_00564990(ctx);  // tail call
}

// 0x0057AC68 sub_57AC68 -- 344 bytes; frame 0x50: s0 sp+0x20, s3 sp+0x38, s1 sp+0x28, s2 sp+0x30, ra sp+0x40
// CRI MWSFD: drain a stream's supply chunks (its +24 get callback) and parse the headers found (sub_578160 /
// sub_577FC8).
void sub_57AC68(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057ac68
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s0, sp, 0x20);
    s0 = a0;
    sd(s3, sp, 0x38);
    s3 = addiu(sp, 0x10);
    sd(s1, sp, 0x28);
    sd(s2, sp, 0x30);
    sd(ra, sp, 0x40);
    // 0x0057ad50
    charge(ctx, 1);
    lw(v1, s0, 0);
    for (;;) {
        // 0x0057ad54
        charge(ctx, 12);
        a2 = 0x7FFF0000;
        a1 = 1;
        a2 = a2 | 0xFFFF;
        lw(v0, v1, 24);
        a0 = s0;
        a3 = sp;
        jalr(ctx, 0x57AD68u, v0.u());
        lw(v0, sp, 0x4);
        a1 = v0;
        v0 = slti(v0, 4);
        a2 = si(-1);
        if (v0 != 0) {
            break;
        }
        backedge(ctx);
        // 0x0057ac90
        charge(ctx, 7);
        link(ctx, 0x57AC90u);  // $ra first: the delay slot below depends on it
        lw(a0, sp, 0x0);
        call(ctx, gen::fn_sub_578160_00578160);
        a3 = s3;
        s1 = v0;
        a0 = sp;
        a2 = sp;
        if (s1 != 0) {
            goto L_0057acf0;
        }
        // 0x0057acac
        charge(ctx, 17);
        lw(a1, sp, 0x4);
        a1 = addiu(a1, -3);
        jal(ctx, 0x57ACB0u, gen::fn_sub_563C28_00563c28);
        lw(v1, s0, 0);
        a0 = s0;
        a1 = 0;
        lw(v0, v1, 32);
        a2 = sp;
        jalr(ctx, 0x57ACC8u, v0.u());
        lw(v1, s0, 0);
        a0 = s0;
        a1 = 1;
        lw(v0, v1, 28);
        a2 = s3;
        jalr(ctx, 0x57ACE0u, v0.u());
        lw(v1, s0, 0);
    }
    // 0x0057ad84
    charge(ctx, 8);
    lw(v1, s0, 0);
    a0 = s0;
    a1 = 1;
    a2 = sp;
    lw(v0, v1, 28);
    s2 = 0;
    jalr(ctx, 0x57AD98u, v0.u());
    v0 = s2;
    // 0x0057ada4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x20);
    ld(s1, sp, 0x28);
    ld(s2, sp, 0x30);
    ld(s3, sp, 0x38);
    ld(ra, sp, 0x40);
    sp = addiu(sp, 0x50);
    return;
L_0057acf0:
    charge(ctx, 23);
    a0 = s1;
    jal(ctx, 0x57ACF0u, gen::fn_sub_577FC8_00577fc8);
    a3 = s3;
    lw(a1, sp, 0x0);
    a0 = sp;
    a2 = sp;
    s2 = v0;
    a1 = subu(s1, a1);
    jal(ctx, 0x57AD0Cu, gen::fn_sub_563C28_00563c28);
    lw(v1, s0, 0);
    a0 = s0;
    a1 = 0;
    lw(v0, v1, 32);
    a2 = sp;
    jalr(ctx, 0x57AD24u, v0.u());
    lw(v1, s0, 0);
    a0 = s0;
    a2 = s3;
    lw(v0, v1, 28);
    a1 = 1;
    jalr(ctx, 0x57AD3Cu, v0.u());
    v0 = s2;
    // 0x0057ada4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x20);
    ld(s1, sp, 0x28);
    ld(s2, sp, 0x30);
    ld(s3, sp, 0x38);
    ld(ra, sp, 0x40);
    sp = addiu(sp, 0x50);
}

// 0x0057AE90 sub_57AE90 -- 88 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, ra sp+0x20
// CRI: get then put back a stream chunk through its +24 / +32 callbacks; returns the chunk's size.
void sub_57AE90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057ae90
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(s1, sp, 0x18);
    s1 = sltiu(a1, 1);
    sd(ra, sp, 0x20);
    lw(v1, s0, 0);
    lw(v0, v1, 24);
    a3 = sp;
    jalr(ctx, 0x57AEB0u, v0.u());
    lw(v1, s0, 0);
    a0 = s0;
    a1 = s1;
    lw(v0, v1, 32);
    a2 = sp;
    jalr(ctx, 0x57AEC8u, v0.u());
    lw(v0, sp, 0x4);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0057C730 sub_57C730 -- 208 bytes; frame 0x30: ra sp+0x20
// CRI MWSFCRE_SetSupplySj: attach the supply stream joint ("E20010703B" errors).
void sub_57C730(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057c730
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    lw(a2, a0, 444);
    lw(a3, a0, 60);
    if (a2 != 0) {
        // 0x0057c744
        charge(ctx, 3);
        lw(v0, a0, 480);
        if (a2 != v0) {
            lw(v0, a0, 448);
            // 0x0057c778
            charge(ctx, 2);
            if (a2 != v0) {
                lw(v0, a0, 464);
                // 0x0057c7a8
                charge(ctx, 8);
                lw(a1, a0, 476);
                lw(v1, a0, 468);
                lw(a0, a0, 472);
                sw(v0, sp, 0x0);
                sw(a2, sp, 0x4);
                sw(v1, sp, 0x8);
                sw(a0, sp, 0xC);
                sw(a1, sp, 0x10);
            } else {
                // 0x0057c780
                charge(ctx, 9);
                lw(v0, a0, 460);
                lw(v1, a0, 452);
                lw(a0, a0, 456);
                sw(a2, sp, 0x4);
                sw(v1, sp, 0x8);
                sw(a0, sp, 0xC);
                sw(v0, sp, 0x10);
                sw(zero, sp, 0x0);
            }
        } else {
            // 0x0057c750
            charge(ctx, 9);
            lw(v0, a0, 488);
            v1 = 1;
            lw(a0, a0, 484);
            sw(a2, sp, 0x4);
            sw(v1, sp, 0x0);
            sw(a0, sp, 0x8);
            sw(v0, sp, 0xC);
            sw(zero, sp, 0x10);
        }
        // 0x0057c7c8
        charge(ctx, 6);
        sw(zero, sp, 0x14);
        a0 = a3;
        a1 = sp;
        jal(ctx, 0x57C7D0u, gen::fn_sub_597E20_00597e20);
        a0 = si(-312);
        if (v0 != 0) {
            // 0x0057c7e0
            charge(ctx, 5);
            jal(ctx, 0x57C7E0u, gen::fn_sub_57FC60_0057fc60);
            a0 = 0x7C0000;
            a0 = addiu(a0, 31768);  // "E20010703B MWSFCRE_SetSupplySj: "
            jal(ctx, 0x57C7ECu, gen::fn_sub_585590_00585590);
        }
    }
    // 0x0057c7f4 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0057DB58 sub_57DB58 -- 296 bytes; frame 0x10: ra sp+0x0
// CRI MWSFD: destroy a playback handle and free everything it holds ("forgot free." check).
void sub_57DB58(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057db58
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x0057db70
    charge(ctx, 5);
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    if (s0 != 0) {
        // 0x0057db84
        charge(ctx, 8);
        jal(ctx, 0x57DB84u, gen::fn_sub_580628_00580628);
        sw(zero, s0, 0);
        a0 = s0;
        jal(ctx, 0x57DB90u, gen::fn_sub_583470_00583470);
        lw(a0, s0, 168);
        if (a0 == 0) {
            lw(a0, s0, 72);
        } else {
            // 0x0057dba4
            charge(ctx, 3);
            jal(ctx, 0x57DBA4u, gen::fn_sub_582810_00582810);
            lw(a0, s0, 72);
        }
        // 0x0057dbb0
        charge(ctx, 2);
        if (a0 == 0) {
            lw(a0, s0, 64);
        } else {
            // 0x0057dbb8
            charge(ctx, 3);
            jal(ctx, 0x57DBB8u, gen::fn_sub_55D3A8_0055d3a8);
            lw(a0, s0, 64);
        }
        // 0x0057dbc4
        charge(ctx, 2);
        if (a0 == 0) {
            lw(a0, s0, 448);
        } else {
            // 0x0057dbcc
            charge(ctx, 3);
            jal(ctx, 0x57DBCCu, gen::fn_sub_5864C0_005864c0);
            lw(a0, s0, 448);
        }
        // 0x0057dbd8
        charge(ctx, 2);
        if (a0 == 0) {
            lw(a0, s0, 480);
        } else {
            // 0x0057dbe0
            charge(ctx, 5);
            lw(v1, a0, 0);
            lw(v0, v1, 12);
            jalr(ctx, 0x57DBE8u, v0.u());
            lw(a0, s0, 480);
        }
        // 0x0057dbf4
        charge(ctx, 2);
        if (a0 == 0) {
            lw(a0, s0, 676);
        } else {
            // 0x0057dbfc
            charge(ctx, 5);
            lw(v1, a0, 0);
            lw(v0, v1, 12);
            jalr(ctx, 0x57DC04u, v0.u());
            lw(a0, s0, 676);
        }
        // 0x0057dc10
        charge(ctx, 2);
        if (a0 == 0) {
            lw(a0, s0, 60);
        } else {
            // 0x0057dc18
            charge(ctx, 3);
            jal(ctx, 0x57DC18u, gen::fn_sub_57BFB8_0057bfb8);
            lw(a0, s0, 60);
        }
        // 0x0057dc24
        charge(ctx, 2);
        if (a0 != 0) {
            // 0x0057dc2c
            charge(ctx, 2);
            jal(ctx, 0x57DC2Cu, gen::fn_sub_57D380_0057d380);
        }
        // 0x0057dc34
        charge(ctx, 8);
        a0 = addiu(s0, 640);
        jal(ctx, 0x57DC34u, gen::fn_sub_585100_00585100);
        a0 = s0;
        jal(ctx, 0x57DC3Cu, gen::fn_sub_57E210_0057e210);
        a0 = s0;
        jal(ctx, 0x57DC44u, gen::fn_sub_57E290_0057e290);
        a0 = 0x7D0000;
        if (v0 != 0) {
            // 0x0057dc54
            charge(ctx, 2);
            a0 = addiu(a0, -32592);
            jal(ctx, 0x57DC54u, gen::fn_sub_585590_00585590);
        }
        // 0x0057dc5c
        charge(ctx, 5);
        a0 = s0;
        a1 = 0;
        a2 = 684;
        jal(ctx, 0x57DC64u, gen::fn_memset_00521408);
        sw(zero, s0, 0);
    }
    // 0x0057dc70 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00581070 my_malloc_0 -- 68 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// CRI: wait until the DMA channel is idle (sceDmaSync loop).
void my_malloc_0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00581070
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    jal(ctx, 0x58107Cu, gen::fn_sceDmaGetChan_004fa8f0);
    s0 = v0;
    a0 = s0;
    for (;;) {
        // 0x00581090
        charge(ctx, 5);
        a1 = 1;
        a2 = 30;
        jal(ctx, 0x581094u, gen::fn_sceDmaSync_004faec0);
        a0 = s0;
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x005810a4
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00588F48 sub_588F48 -- 72 bytes; leaf frame (no stack)
// [proposed name: criChan_SetVec] CRI: store a 16-byte value at a0 + 116 * a1 + 4896 + 16 * a2.
void sub_588F48(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x00588f48
    enter(ctx, 18);  // entry check point + this block's cycles
    v0 = sll(a1, 3);
    a2 = sll(a2, 4);
    v0 = subu(v0, a1);
    v0 = sll(v0, 2);
    v0 = addu(v0, a1);
    v0 = sll(v0, 2);
    a0 = addu(a0, v0);
    a0 = addiu(a0, L::kChanVec);  // + 116 * a1 (L::kChanStride), then + 16 * a2
    a0 = addu(a0, a2);
    ldl(v0, a3, 7);
    ldr(v0, a3, 0);
    ldl(v1, a3, 15);
    ldr(v1, a3, 8);
    sdl(v0, a0, 7);
    sdr(v0, a0, 0);
    sdl(v1, a0, 15);
    sdr(v1, a0, 8);
}

// 0x005895F0 sub_5895F0 -- 96 bytes; frame 0x10: ra sp+0x0
// [proposed name: criChan_GetValue] CRI: read channel a1's +4900 word into *a2 when its +4884 is set (else an error).
void sub_5895F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005895f0
    enter(ctx, 15);  // entry check point + this block's cycles
    v1 = a1;
    a1 = lui(0xFF00);
    v0 = sll(v1, 3);
    sp = addiu(sp, -0x10);
    v0 = subu(v0, v1);
    sd(ra, sp, 0x0);
    v0 = sll(v0, 2);
    a3 = addiu(a0, L::kChanBase);  // + 116 * a1: +4 open (4884), +20 value (4900)
    v0 = addu(v0, v1);
    v0 = sll(v0, 2);
    sw(zero, a2, 0);
    a3 = addu(a3, v0);
    lw(v1, a3, 4);
    a1 = a1 | 0x401;
    if (v1 == 0) {
        // 0x0058962c
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x00589638
    charge(ctx, 6);
    lw(v1, a3, 20);
    v0 = 0;
    ld(ra, sp, 0x0);
    sw(v1, a2, 0);
    sp = addiu(sp, 0x10);
}

// 0x00589CB0 sub_589CB0 -- 32 bytes; leaf frame (no stack)
// [proposed name: criChan_SetWord] CRI: channel a1's +4888 word = a2.
void sub_589CB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00589cb0
    enter(ctx, 8);  // entry check point + this block's cycles
    v0 = sll(a1, 3);
    v0 = subu(v0, a1);
    v0 = sll(v0, 2);
    v0 = addu(v0, a1);
    v0 = sll(v0, 2);
    a0 = addu(a0, v0);
    sw(a2, a0, L::kChanWord);  // a0 + 116 * a1 (L::kChanStride)
}

// 0x00589CD0 sub_589CD0 -- 32 bytes; leaf frame (no stack)
// [proposed name: criChan_GetWord] CRI: channel a1's +4888 word.
void sub_589CD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00589cd0
    enter(ctx, 8);  // entry check point + this block's cycles
    v0 = sll(a1, 3);
    v0 = subu(v0, a1);
    v0 = sll(v0, 2);
    v0 = addu(v0, a1);
    v0 = sll(v0, 2);
    a0 = addu(a0, v0);
    lw(v0, a0, L::kChanWord);  // a0 + 116 * a1 (L::kChanStride)
}

// 0x00589D80 sub_589D80 -- 184 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// CRI: fetch the two sizes of a handle (sub_562E10, or the fallback through sub_589F00).
void sub_589D80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00589d80
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x589D9Cu, gen::fn_sub_589EC8_00589ec8);
    a0 = s0;
    a1 = 1;
    a2 = 1;
    if (v0 == 0) {
        // 0x00589dd8
        charge(ctx, 4);
        a0 = s0;
        jal(ctx, 0x589DD8u, gen::fn_sub_589F00_00589f00);
        a0 = s0;
        if (v0 == 0) {
            // 0x00589e18
            charge(ctx, 2);
            sw(zero, s1, 0);
            sw(zero, s2, 0);
        } else {
            // 0x00589de8
            charge(ctx, 12);
            jal(ctx, 0x589DE8u, gen::fn_width__CQ24_STL8ios_base_0_00562218);
            a1 = 1;
            lw(v1, s0, 0);
            sw(v0, s1, 0);
            lw(v0, v1, 36);
            a0 = s0;
            jalr(ctx, 0x589E00u, v0.u());
            lw(v1, s1, 0);
            v1 = subu(v1, v0);
            sw(v1, s2, 0);
        }
    } else {
        // 0x00589db4
        charge(ctx, 9);
        jal(ctx, 0x589DB4u, gen::fn_sub_562E10_00562e10);
        a0 = s0;
        sw(v0, s1, 0);
        a1 = 0;
        a2 = 1;
        jal(ctx, 0x589DC8u, gen::fn_sub_562E10_00562e10);
        sw(v0, s2, 0);
    }
    // 0x00589e20 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00589F38 sub_589F38 -- 52 bytes; leaf frame (no stack)
// [proposed name: u64_SetLowWithCarry] 64-bit counter update: the low word becomes a1 and the high word of a0 goes up by one when a1 is below a0's
// sign-extended low word (it wrapped).
void sub_589F38(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00589f38
    enter(ctx, 13);  // entry check point + this block's cycles
    v0 = a0;
    v1 = dsll32(v0, 0);
    v1 = dsra32(v1, 0);
    v0 = dsra32(v0, 0);
    v1 = sltu(a1, v1);
    a1 = dsll32(a1, 0);
    v1 = dsll32(v1, 0);
    a1 = dsrl32(a1, 0);
    v1 = dsrl32(v1, 0);
    v0 = v0 + v1;
    v0 = dsll32(v0, 0);
    v0 = v0 | a1;
}

// 0x005944A8 sub_5944A8 -- 508 bytes; frame 0x50: s1 sp+0x8, s7 sp+0x38, s0 sp+0x0, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s5 sp+0x28, s6 sp+0x30, ra sp+0x40
// CRI MPEG on the IPU: suspend a decode (semaphore, IPU state saved, the bit position recomputed).
void sub_5944A8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005944a8
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s7, sp, 0x38);
    s7 = 0;
    sd(s0, sp, 0x0);
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    sd(s4, sp, 0x20);
    sd(s5, sp, 0x28);
    sd(s6, sp, 0x30);
    sd(ra, sp, 0x40);
    link(ctx, 0x5944D8u);  // $ra first: the delay slot below depends on it
    lw(a0, s1, 64);
    call(ctx, gen::fn__sceWaitSema_005031a0);
    lw(v1, s1, 68);
    if (v1 != 0) {
        // 0x00594500
        charge(ctx, 15);
        a0 = 5;
        jal(ctx, 0x594500u, gen::fn_sub_5940A0_005940a0);
        v0 = 0x10000000;
        v1 = 0x10000000;
        v0 = v0 | 0xB400;
        v1 = v1 | 0xB410;
        lw(s5, v0, 0);  // 0x1000B400
        lw(a1, v1, 0);  // 0x1000B410
        a0 = s1;
        jal(ctx, 0x594520u, gen::fn_sub_593FE8_00593fe8);
        lw(a2, s1, 8);
        lw(v1, s1, 12);
        v0 = addu(v0, a2);
        if (a2 == 0) {
            brk(ctx, 0x594538u, 0x7u);
        }
        // 0x0059453c
        charge(ctx, 23);
        v0 = subu(v0, v1);
        div(v0, a2);
        lw(v0, s1, 16);
        mfhi(a0);
        v1 = addu(v1, a0);
        v0 = subu(v0, a0);
        div(v1, a2);
        sw(v0, s1, 16);
        mfhi(a1);
        a3 = addu(a1, v0);
        sw(a1, s1, 12);
        div(a3, a2);
        lw(a0, s1, 20);
        v1 = slti(a0, 0);
        a1 = addiu(a0, 2047);
        v0 = a0;
        if (v1 != 0) v0 = a1;
        s3 = sra(v0, 11);
        v1 = sll(s3, 11);
        a0 = subu(a0, v1);
        mfhi(s0);
        sw(a0, s1, 20);
        if (i64(s3) > 0) {
            // 0x00594598
            charge(ctx, 5);
            v0 = addu(a3, a2);
            a3 = 128;
            v0 = addiu(v0, -1);
            if (a2 == 0) {
                brk(ctx, 0x5945A8u, 0x7u);
            }
            // 0x005945ac
            charge(ctx, 11);
            div(v0, a2);
            a2 = 3;
            lw(t0, s1, 4);
            s7 = 1;
            lw(v1, s1, 0);
            mfhi(a0);
            a1 = sll(a0, 11);
            a0 = sll(a0, 4);
            a0 = addu(t0, a0);
            a1 = addu(v1, a1);
            jal(ctx, 0x5945D0u, gen::fn_sub_594108_00594108);
        }
        // 0x005945d8
        charge(ctx, 2);
        s2 = 0;
        if (i64(s3) > 0) {
            // 0x005945e0
            charge(ctx, 2);
            s4 = addiu(s3, -1);
            s6 = 3;
            for (;;) {
                // 0x005945e8
                charge(ctx, 18);
                lw(v1, s1, 4);
                a3 = s2 ^ s4;
                lw(v0, s1, 0);
                a0 = sll(s0, 4);
                a1 = sll(s0, 11);
                a2 = 0;
                a0 = addu(v1, a0);
                a1 = addu(v0, a1);
                if (a3 != 0) a2 = s6;
                a3 = 128;
                jal(ctx, 0x59460Cu, gen::fn_sub_594108_00594108);
                v1 = addiu(s0, 1);
                lw(v0, s1, 8);
                s2 = addiu(s2, 1);
                a1 = slt(s2, s3);
                div(v1, v0);
                if (v0 == 0) {
                    brk(ctx, 0x59462Cu, 0x7u);
                }
                // 0x00594630
                charge(ctx, 3);
                mfhi(a0);
                s0 = a0;
                if (a1 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x0059463c
        charge(ctx, 4);
        lw(v0, s1, 16);
        v0 = addu(v0, s3);
        sw(v0, s1, 16);
        if (v0 != 0) {
            // 0x0059464c
            charge(ctx, 2);
            v0 = 0xFFF0000;
            if (s7 != 0) {
                // 0x00594654
                charge(ctx, 4);
                v1 = 0x30000000;
                v0 = v0 | 0xFFFF;
                v0 = s5 & v0;
                s5 = v0 | v1;
            }
            // 0x00594664
            charge(ctx, 2);
            a0 = s5 | 0x100;
            jal(ctx, 0x594664u, gen::fn_sub_5940A0_005940a0);
        }
        // 0x0059466c
        charge(ctx, 3);
        link(ctx, 0x59466Cu);  // $ra first: the delay slot below depends on it
        lw(a0, s1, 64);
        call(ctx, gen::fn__sceSignalSema_00503180);
        v0 = 1;
    } else {
        // 0x005944ec
        charge(ctx, 4);
        link(ctx, 0x5944ECu);  // $ra first: the delay slot below depends on it
        lw(a0, s1, 64);
        call(ctx, gen::fn__sceSignalSema_00503180);
        v0 = 0;
    }
    // 0x00594678 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(s6, sp, 0x30);
    ld(s7, sp, 0x38);
    ld(ra, sp, 0x40);
    sp = addiu(sp, 0x50);
}

// 0x005946A8 sub_5946A8 -- 256 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// CRI MPEG on the IPU: save the IPU / DMA channel state into the handle (+28..+40).
void sub_5946A8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005946a8
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    link(ctx, 0x5946B8u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 64);
    call(ctx, gen::fn__sceWaitSema_005031a0);
    sw(zero, s0, 68);
    a0 = 5;
    jal(ctx, 0x5946C4u, gen::fn_sub_5940A0_005940a0);
    v0 = 0x10000000;
    v0 = v0 | 0xB410;
    a0 = 0x10000000;
    lw(v1, v0, 0);  // 0x1000B410
    a0 = a0 | 0xB430;
    a1 = 0x10000000;
    a2 = 0x10000000;
    sw(v1, s0, 28);
    a1 = a1 | 0xB420;
    a2 = a2 | 0xB400;
    a3 = 0x10000000;
    lw(v1, a0, 0);  // 0x1000B430
    a3 = a3 | 0x2010;
    sw(v1, s0, 32);
    lw(v0, a1, 0);  // 0x1000B420
    sw(v0, s0, 36);
    lw(v1, a2, 0);  // 0x1000B400
    sw(v1, s0, 40);
    for (;;) {
        // 0x00594718
        charge(ctx, 7);
        lw(v0, a3, 0);
        v0 = v0 & 0xF0;
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00594734
    charge(ctx, 29);
    a0 = 0;
    jal(ctx, 0x594734u, gen::fn_sub_594038_00594038);
    v0 = 0x10000000;
    v0 = v0 | 0xB010;
    v1 = 0x10000000;
    lw(a0, v0, 0);  // 0x1000B010
    v1 = v1 | 0xB020;
    a2 = 0x10000000;
    a3 = 0x10000000;
    sw(a0, s0, 44);
    a2 = a2 | 0xB000;
    a3 = a3 | 0x2020;
    a1 = 0x10000000;
    lw(t0, v1, 0);  // 0x1000B020
    a1 = a1 | 0x2010;
    lw(a0, s0, 64);
    sw(t0, s0, 48);
    lw(v0, a2, 0);  // 0x1000B000
    sw(v0, s0, 52);
    lw(v1, a3, 0);  // 0x10002020
    sw(v1, s0, 56);
    lw(v0, a1, 0);  // 0x10002010
    link(ctx, 0x59478Cu);  // $ra first: the delay slot below depends on it
    sw(v0, s0, 60);
    call(ctx, gen::fn__sceSignalSema_00503180);
    v0 = 1;
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x005947A8 sub_5947A8 -- 788 bytes; frame 0x40: s0 sp+0x0, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s5 sp+0x28, s6 sp+0x30, s1 sp+0x8, ra sp+0x38
// CRI MPEG on the IPU: restore the IPU / DMA state saved by sub_5946A8 and restart the transfer.
void sub_5947A8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005947a8
    enter(ctx, 30);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    sd(s4, sp, 0x20);
    sd(s5, sp, 0x28);
    sd(s6, sp, 0x30);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x38);
    link(ctx, 0x5947D0u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 64);
    call(ctx, gen::fn__sceWaitSema_005031a0);
    lw(a0, s0, 56);
    lw(t1, s0, 28);
    v0 = srl(a0, 8);
    v1 = srl(a0, 16);
    v0 = v0 & 0xF;
    v1 = v1 & 0x3;
    v1 = addu(v1, v0);
    lw(a3, s0, 0);
    v0 = sll(v1, 4);
    lw(a1, s0, 36);
    s2 = subu(t1, v0);
    lw(t2, s0, 40);
    v0 = sltu(s2, a3);
    s5 = addu(a1, v1);
    s6 = a0 & 0x7F;
    lw(s4, s0, 32);
    s3 = t2 | 0x100;
    if (v0 == 0) {
        // 0x005948c8
        charge(ctx, 10);
        a1 = t1;
        a0 = s0;
        jal(ctx, 0x5948CCu, gen::fn_sub_593FE8_00593fe8);
        a0 = s0;
        a1 = s2;
        s1 = v0;
        jal(ctx, 0x5948DCu, gen::fn_sub_593FE8_00593fe8);
        t6 = v0;
        t1 = 0xFFF0000;
        if (s1 != t6) {
            // 0x005948f0
            charge(ctx, 7);
            lw(t4, s0, 8);
            lw(t0, s0, 0);
            t3 = 3;
            lw(v0, s0, 28);
            v1 = sll(t4, 11);
            if (v1 == 0) {
                brk(ctx, 0x594908u, 0x7u);
            }
            // 0x0059490c
            charge(ctx, 32);
            lw(a0, s0, 12);
            v0 = subu(v0, t0);
            lw(t5, s0, 16);
            divu(v0, v1);
            v1 = sll(s1, 11);
            v0 = addu(a0, t5);
            a1 = addu(t6, t4);
            a1 = subu(a1, a0);
            v1 = addu(t0, v1);
            lw(a0, s0, 40);
            lw(t2, s0, 4);
            t1 = t1 | 0xFFFF;
            a0 = a0 & t1;
            v1 = subu(v1, s2);
            s5 = srl(v1, 4);
            mfhi(a2);
            div(v0, t4);
            a2 = addu(t0, a2);
            v0 = sll(s1, 4);
            v0 = addu(v0, t2);
            s4 = v0 & t1;
            mfhi(a3);
            div(a1, t4);
            a3 = sll(a3, 11);
            t0 = addu(t0, a3);
            a2 = a2 ^ t0;
            if (a2 == 0) t3 = 0;
            t3 = sll(t3, 28);
            a0 = a0 | t3;
            mfhi(v0);
            s3 = a0 | 0x100;
            if (i64(v0) >= 0) {
                // 0x0059498c
                charge(ctx, 3);
                v0 = slt(v0, t5);
                if (t4 == 0) {
                    brk(ctx, 0x594994u, 0x7u);
                }
                // 0x00594998
                charge(ctx, 2);
                if (v0 == 0) {
                    goto L_005949a0;
                }
                lw(v1, s0, 44);
                goto L_005949b0;
            }
        L_005949a0:
            charge(ctx, 3);
            v0 = addiu(t5, 1);
            sw(t6, s0, 12);
            sw(v0, s0, 16);
            goto L_005949ac;
        }
    L_005949ac:
        charge(ctx, 1);
        lw(v1, s0, 44);
    } else {
        // 0x00594820
        charge(ctx, 10);
        lw(a2, s0, 8);
        v0 = 0xFFF0000;
        lw(v1, s0, 4);
        a0 = subu(a3, s2);
        t0 = sll(a2, 11);
        v0 = v0 | 0xFFFF;
        s4 = v1 & v0;
        s5 = srl(a0, 4);
        s2 = addu(s2, t0);
        if (t1 != a3) {
            // 0x00594848
            charge(ctx, 3);
            v0 = addu(a3, t0);
            a0 = 3;
            if (t1 == v0) {
                goto L_00594854;
            }
            goto L_00594858;
        }
    L_00594854:
        charge(ctx, 1);
        a0 = 0;
    L_00594858:
        charge(ctx, 11);
        lw(v1, s0, 12);
        v0 = 0xFFF0000;
        v0 = v0 | 0xFFFF;
        a0 = sll(a0, 28);
        v1 = subu(a2, v1);
        v0 = t2 & v0;
        div(v1, a2);
        v0 = v0 | a0;
        s3 = v0 | 0x100;
        if (a2 == 0) {
            brk(ctx, 0x594880u, 0x7u);
        }
        // 0x00594884
        charge(ctx, 3);
        mfhi(a1);
        if (i64(a1) < 0) {
            lw(v1, s0, 16);
            // 0x005948b0
            charge(ctx, 1);
            v0 = addiu(a2, -1);
        L_005948b4:
            charge(ctx, 4);
            v1 = addiu(v1, 1);
            sw(v0, s0, 12);
            sw(v1, s0, 16);
            goto L_005949ac;
        }
        // 0x00594890
        charge(ctx, 2);
        if (a2 == 0) {
            brk(ctx, 0x594894u, 0x7u);
        }
        // 0x00594898
        charge(ctx, 4);
        lw(v1, s0, 16);
        v0 = slt(a1, v1);
        if (v0 == 0) {
            // 0x005948a8
            charge(ctx, 2);
            v0 = addiu(a2, -1);
            goto L_005948b4;
        }
        lw(v1, s0, 44);
    }
L_005949b0:
    charge(ctx, 2);
    if (v1 == 0) {
        v1 = 0x10000000;
    } else {
        // 0x005949b8
        charge(ctx, 3);
        lw(v0, s0, 48);
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = 0x10000000;
        if (!cc) {
            // 0x005949c4
            charge(ctx, 9);
            a0 = 0x10000000;
            v0 = v0 | 0xB010;
            a0 = a0 | 0xB020;
            sw(v1, v0, 0);
            lw(v1, s0, 48);
            sw(v1, a0, 0);  // 0x1000B020
            lw(a0, s0, 52);
            a0 = a0 | 0x100;
            jal(ctx, 0x5949E0u, gen::fn_sub_594038_00594038);
        }
        // 0x005949e8
        charge(ctx, 1);
        v1 = 0x10000000;
    }
    // 0x005949ec
    charge(ctx, 1);
    v1 = v1 | 0x2010;
    for (;;) {
        // 0x005949f0
        charge(ctx, 7);
        lw(v0, v1, 0);
        cc = i64(v0) < 0;  // the condition, before the delay slot changes it
        v0 = 0x10000000;
        if (!cc) {
            break;
        }
        backedge(ctx);
    }
    // 0x00594a0c
    charge(ctx, 5);
    v1 = 0x10000000;
    v0 = v0 | 0x2000;
    v1 = v1 | 0x2010;
    sw(s6, v0, 0);
    for (;;) {
        // 0x00594a20
        charge(ctx, 7);
        lw(v0, v1, 0);
        cc = i64(v0) < 0;  // the condition, before the delay slot changes it
        v0 = 0x10000000;
        if (!cc) {
            break;
        }
        backedge(ctx);
    }
    // 0x00594a3c
    charge(ctx, 11);
    v1 = 0x10000000;
    a0 = 0x10000000;
    v0 = v0 | 0xB410;
    v1 = v1 | 0xB430;
    a0 = a0 | 0xB420;
    sw(s2, v0, 0);
    sw(s4, v1, 0);  // 0x1000B430
    sw(s5, a0, 0);  // 0x1000B420
    lw(v0, s0, 16);
    if (v0 == 0) {
        lw(v0, s0, 60);
    } else {
        // 0x00594a68
        charge(ctx, 3);
        a0 = s3;
        jal(ctx, 0x594A68u, gen::fn_sub_5940A0_005940a0);
        lw(v0, s0, 60);
    }
    // 0x00594a74
    charge(ctx, 18);
    v1 = 0x10000000;
    v1 = v1 | 0x2010;
    a0 = 1;
    sw(v0, v1, 0);  // 0x10002010
    sw(a0, s0, 68);
    link(ctx, 0x594A88u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 64);
    call(ctx, gen::fn__sceSignalSema_00503180);
    v0 = 1;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(s6, sp, 0x30);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
}

// 0x00595BC0 sub_595BC0 -- 36 bytes; leaf frame (no stack)
// [proposed name: criHandle_IsIdle] CRI: 1 unless the handle's state +72 is 1..4, then +68 == 0.
void sub_595BC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00595bc0
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v1, a0, 72);
    v1 = addiu(v1, -1);
    v1 = sltiu(v1, 4);
    v0 = 1;
    if (v1 != 0) {
        // 0x00595bd4
        charge(ctx, 2);
        lw(v0, a0, 68);
        v0 = sltiu(v0, 1);
    }
    // 0x00595bdc (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00597368 sub_597368 -- 88 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// CRI: start a handle (sub_5973C0) and mark it running (+68 = 1); error when sub_58C060 says not ready.
void sub_597368(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00597368
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x597374u, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = s0;
    a1 = a1 | 0x133;
    if (v0 != 0) {
        // 0x0059738c
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        a0 = 0;
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x005973a0
    charge(ctx, 8);
    jal(ctx, 0x5973A0u, gen::fn_sub_5973C0_005973c0);
    v1 = 1;
    sw(v1, s0, 68);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00597438 sceInsockGetErrnoMode_1 -- 12 bytes; leaf frame (no stack)
// Returns the errno mode word 0x7B476C.
void sceInsockGetErrnoMode_1(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3};
    // 0x00597438
    enter(ctx, 3);  // entry check point + this block's cycles
    v1 = 0x7B0000;
    lw(v0, v1, 18284);  // 0x7B476C
}

// 0x005990C0 sub_5990C0 -- 64 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// CRI: a handle's +72 state (error first when sub_58C060 says not ready).
void sub_5990C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005990c0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x5990CCu, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = 0;
    a1 = a1 | 0x111;
    if (v0 != 0) {
        // 0x005990e4
        charge(ctx, 2);
        jal(ctx, 0x5990E4u, gen::fn_sub_58BE40_0058be40);
    }
    // 0x005990ec (the shared epilogue, written out on this path)
    charge(ctx, 5);
    lw(v0, s0, 72);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x005A1A30 sub_5A1A30 -- 292 bytes; leaf frame (no stack)
// When enabled (0x7B5068 > 0 and the slot 0x7B506C set): counts the nesting at 0x9ACC1C and, on the first level,
// copies the 0x9ACBF8 / 0x9ACC00 records and checks the slot's record *(0x7CAC30)[slot].
void sub_5A1A30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005a1a30
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    v0 = addiu(v0, 20584);  // &0x7B5068
    lw(v1, v0, 0);  // 0x7B5068
    cc = i64(v1) <= 0;  // the condition, before the delay slot changes it
    v1 = si(-1);
    if (cc) {
        // 0x005a1a54 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        v0 = 0;
        return;
    }
    // 0x005a1a44
    charge(ctx, 4);
    v0 = 0x7B0000;
    lw(a2, v0, 20588);  // 0x7B506C
    t1 = 0x9B0000;
    if (a2 == v1) {
        // 0x005a1a54 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        v0 = 0;
        return;
    }
    // 0x005a1a60
    charge(ctx, 8);
    a1 = 1;
    v1 = addiu(t1, -13284);
    lw(v0, v1, 0);
    v0 = addiu(v0, 1);
    sw(v0, v1, 0);
    lw(a0, v1, 0);
    v1 = sll(a2, 2);
    if (a0 == a1) {
        // 0x005a1a80
        charge(ctx, 21);
        v0 = 0x9B0000;
        v1 = 0x9B0000;
        a3 = addiu(v0, -13320);  // &0x9ACBF8
        v0 = 0x9B0000;
        ld(a1, a3, 0);  // 0x9ACBF8
        v1 = addiu(v1, -13304);  // &0x9ACC08
        t0 = addiu(v0, -13288);  // &0x9ACC18
        a0 = sll(a2, 2);
        sd(a1, v1, 0);  // 0x9ACC08
        ld(v0, a3, 8);  // 0x9ACC00
        a2 = 0x7D0000;
        a2 = addu(a2, a0);
        lw(a2, a2, -21456);
        sd(v0, v1, 8);  // 0x9ACC10
        sw(v1, t0, 0);  // 0x9ACC18
        lw(a0, a2, 0);
        lhu(v0, a3, 8);  // 0x9ACC00
        a2 = a0 & 0xFFFF;
        v0 = sltu(a2, v0);
        if (v0 != 0) {
            // 0x005a1ad4
            charge(ctx, 4);
            ld(v0, a3, 0);
            v1 = 0x10000;
            v0 = v0 + v1;
            sd(v0, a3, 0);
        }
        // 0x005a1ae4
        charge(ctx, 5);
        sh(a2, a3, 8);
        ld(v0, a3, 0);
        sw(a3, t0, 0);
        a1 = a2 + v0;
        goto L_005a1b3c;
    }
    // 0x005a1af8
    charge(ctx, 15);
    v0 = 0x9B0000;
    a0 = 0x7D0000;
    a0 = addu(a0, v1);
    lw(a0, a0, -21456);
    v0 = addiu(v0, -13288);  // &0x9ACC18
    lw(v1, a0, 0);
    lw(a1, v0, 0);  // 0x9ACC18
    a2 = v1 & 0xFFFF;
    ld(a0, a1, 0);
    lw(v1, v0, 0);  // 0x9ACC18
    a1 = a2 + a0;
    lhu(v0, v1, 8);
    v0 = sltu(a2, v0);
    a0 = addiu(t1, -13284);
    if (v0 != 0) {
        // 0x005a1b34
        charge(ctx, 2);
        v0 = 0x10000;
        a1 = a1 + v0;
    L_005a1b3c:
        charge(ctx, 1);
        a0 = addiu(t1, -13284);
    }
    // 0x005a1b40 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = a1;
    lw(v1, a0, 0);
    v1 = addiu(v1, -1);
    sw(v1, a0, 0);
}

}  // namespace p3fes::game

// The recompiled program's entry points fn_<name>_<addr8> are generated from game/replaced.txt (game/forwarders.cmake).
