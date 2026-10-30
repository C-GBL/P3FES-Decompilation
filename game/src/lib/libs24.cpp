// Phase 5 slice libs24: the boot / IOP layer under the game. The kwln main loop and its boot init, the H_Cdvd and
// H_Sndcom glue, and the SDK libraries they stand on: libkernel syscall wrappers, cache and interrupt helpers,
// timers and alarms; libsif (DMA, commands, RPC, IOP heap, module load, IOP reboot); libcdvd; libpad; libsdr;
// libmc2 / libdbc; the Standard Kit sound binds; libmpeg / libipu (slice and macroblock decode, CSC); CRI ADXF
// (AFS partitions) and DTX / dvCi. Written by p3fes_handgen from SLUS_216.21 and symbols/: every body keeps the
// recompiled body's registers, frame, spills, $ra links, cycle charges and check points (hg_cpu.h); each has a
// role comment on top. Pair tests: tests/game/test_libs24.cpp.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/libs24.h"

namespace p3fes::recomp_gen {
void fn_ADXF_AddRofsVol_0053b2c0(p3fes::EEContext&);
void fn_ADXF_ExecServer_0053d708(p3fes::EEContext&);
void fn_ADXF_GetFsizeSct_0053d968(p3fes::EEContext&);
void fn_ADXF_GetStat_0053db90(p3fes::EEContext&);
void fn_ADXF_LoadPartitionNw_0053b868(p3fes::EEContext&);
void fn_ADXF_Open_0053c910(p3fes::EEContext&);
void fn_ADXF_ReadNw_0053d380(p3fes::EEContext&);
void fn_ADXF_SetupRofs_0053b220(p3fes::EEContext&);
void fn_ADXM_SetupThrd_00540588(p3fes::EEContext&);
void fn_ADXPS2_SetupDvdFs_00547668(p3fes::EEContext&);
void fn_DIntr_0050d3a0(p3fes::EEContext&);
void fn_DPRINT_0051d588(p3fes::EEContext&);
void fn_DTX_Init_00559aa8(p3fes::EEContext&);
void fn_DelayThread_005041d8(p3fes::EEContext&);
void fn_DisableDmac_00503d10(p3fes::EEContext&);
void fn_EIntr_0050d3f0(p3fes::EEContext&);
void fn_EnableDmac_00503d78(p3fes::EEContext&);
void fn_EnableIntc_00503ca8(p3fes::EEContext&);
void fn_H_Cdvd_BuildPathUppercase_00101010(p3fes::EEContext&);
void fn_H_Cdvd_CacheFindFile_001021c0(p3fes::EEContext&);
void fn_H_Cdvd_Destroy_00100ec0(p3fes::EEContext&);
void fn_H_Cdvd_InitCd_00100800(p3fes::EEContext&);
void fn_H_Cdvd_InitRtFS_00101c70(p3fes::EEContext&);
void fn_H_Cdvd_IsFileLoaded_001016b0(p3fes::EEContext&);
void fn_H_Cdvd_LoadAfsFile_001024a0(p3fes::EEContext&);
void fn_H_Cdvd_NormalizePath_001013f0(p3fes::EEContext&);
void fn_H_Cdvd_Request_00100d80(p3fes::EEContext&);
void fn_H_Cdvd_SetRofsDir_00101520(p3fes::EEContext&);
void fn_H_Cdvd_SplitPath_00101100(p3fes::EEContext&);
void fn_H_Cdvd_Update_00100980(p3fes::EEContext&);
void fn_H_Memcard_Init_0018f100(p3fes::EEContext&);
void fn_H_Pad_Init_00103000(p3fes::EEContext&);
void fn_H_ResrcMan_Init_0010c050(p3fes::EEContext&);
void fn_H_ResrcMan_MaybeResumeThread_0010bff0(p3fes::EEContext&);
void fn_H_ResrcMan_Update_0010c5f0(p3fes::EEContext&);
void fn_H_Sndcom_CopyToIop_0010cce0(p3fes::EEContext&);
void fn_H_Sndcom_Init_0010cac0(p3fes::EEContext&);
void fn_H_Sndcom_Update_0010cdd0(p3fes::EEContext&);
void fn_InitAlarm_0050db38(p3fes::EEContext&);
void fn_InitTimer_0050dcb0(p3fes::EEContext&);
void fn_InvalidDCache_00503b98(p3fes::EEContext&);
void fn_K_Data_LoadFldMainScript_001b7b10(p3fes::EEContext&);
void fn_K_Field_Init_001b90f0(p3fes::EEContext&);
void fn_PowerOffCB_0050fbc0(p3fes::EEContext&);
void fn_QueryIntrContext_00503c30(p3fes::EEContext&);
void fn_ROFS_Init_00567820(p3fes::EEContext&);
void fn_ROFS_SetDir_00566b08(p3fes::EEContext&);
void fn_RpRandomSeedMT_00488c70(p3fes::EEContext&);
void fn_RpRandomSeed_00488dd0(p3fes::EEContext&);
void fn_RwCameraShowRaster_004c9ed0(p3fes::EEContext&);
void fn_StartThread_005042a0(p3fes::EEContext&);
void fn_StartTimerSystemTime_0050def0(p3fes::EEContext&);
void fn_SyncDCache_00503a58(p3fes::EEContext&);
void fn_VSync_005035f0(p3fes::EEContext&);
void fn_Y_Misc_GetT0Count_004241d0(p3fes::EEContext&);
void fn__InitAlarm_0050efe0(p3fes::EEContext&);
void fn___env_lock_0053b598(p3fes::EEContext&);
void fn___env_unlock_0053b5a0(p3fes::EEContext&);
void fn__ch3dmaCSC_005022d0(p3fes::EEContext&);
void fn__clearEach_005001b0(p3fes::EEContext&);
void fn__copyAddRefImage_004fd968(p3fes::EEContext&);
void fn__decMB0_004fcca0(p3fes::EEContext&);
void fn__doCSC2_00501c38(p3fes::EEContext&);
void fn__doMC_004fbf48(p3fes::EEContext&);
void fn__extensionAndUserData_004ff7c8(p3fes::EEContext&);
void fn__getAllRefs_004fb168(p3fes::EEContext&);
void fn__initSeq_004febc8(p3fes::EEContext&);
void fn__isceSifSetDChain_00503550(p3fes::EEContext&);
void fn__isceSifSetDma_00503530(p3fes::EEContext&);
void fn__lf_bind_0050bae8(p3fes::EEContext&);
void fn__lf_version_0050bbe8(p3fes::EEContext&);
void fn__motionComp0_004fb870(p3fes::EEContext&);
void fn__motionVector_004fc6d8(p3fes::EEContext&);
void fn__motionVectors_004fcb00(p3fes::EEContext&);
void fn__request_end_00506ba8(p3fes::EEContext&);
void fn__sceAddDmacHandler_00502e70(p3fes::EEContext&);
void fn__sceAddDmacHandler_0_00502e80(p3fes::EEContext&);
void fn__sceAddIntcHandler_00502e40(p3fes::EEContext&);
void fn__sceAddIntcHandler_0_00502e50(p3fes::EEContext&);
void fn__sceCd_cd_callback_0050f698(p3fes::EEContext&);
void fn__sceCd_cd_read_intr_0050f8a8(p3fes::EEContext&);
void fn__sceCd_ncmd_prechk_0050ff58(p3fes::EEContext&);
void fn__sceCd_scmd_prechk_00510258(p3fes::EEContext&);
void fn__sceCopy_0050cc10(p3fes::EEContext&);
void fn__sceCopy_3_0050dae0(p3fes::EEContext&);
void fn__sceCreateSema_00503160(p3fes::EEContext&);
void fn__sceCreateThread_00502f60(p3fes::EEContext&);
void fn__sceDeleteSema_00503170(p3fes::EEContext&);
void fn__sceEndOfHeap_00503140(p3fes::EEContext&);
void fn__sceFindAddress_0050d500(p3fes::EEContext&);
void fn__sceFlushCache_005033e0(p3fes::EEContext&);
void fn__sceGetEntryAddress_0050cc58(p3fes::EEContext&);
void fn__sceGetEntryAddress_1_0050db28(p3fes::EEContext&);
void fn__sceGetOsdConfigParam_00503210(p3fes::EEContext&);
void fn__sceGetThreadId_00503050(p3fes::EEContext&);
void fn__sceGsPutIMR_005034a0(p3fes::EEContext&);
void fn__sceIDC_00503af0(p3fes::EEContext&);
void fn__sceMpegDispatchMpegCallback_00500d10(p3fes::EEContext&);
void fn__sceMpegDispatchMpegCbNodata_00500d88(p3fes::EEContext&);
void fn__sceMpegError1_005026c0(p3fes::EEContext&);
void fn__sceMpegErrorBdec_005025a0(p3fes::EEContext&);
void fn__sceMpegError_00502668(p3fes::EEContext&);
void fn__sceMpegFlushBuf_004fd7d0(p3fes::EEContext&);
void fn__sceMpegMbAddressIncrement_004fd1f8(p3fes::EEContext&);
void fn__sceMpegNextBit_004fd658(p3fes::EEContext&);
void fn__sceMpegPeepBit_004fd740(p3fes::EEContext&);
void fn__sceMpegSliceA0_004fea28(p3fes::EEContext&);
void fn__sceMpegStopIpuDma_00502500(p3fes::EEContext&);
void fn__sceMpegWaitIpuIdle64_004fd4d8(p3fes::EEContext&);
void fn__sceMpegWaitIpuIdle_004fd370(p3fes::EEContext&);
void fn__scePollSema_005031b0(p3fes::EEContext&);
void fn__sceRemoveDmacHandler_00502e90(p3fes::EEContext&);
void fn__sceRpcFreePacket_00506b18(p3fes::EEContext&);
void fn__sceRpcGetPacket_00506a70(p3fes::EEContext&);
void fn__sceSDC_005039b0(p3fes::EEContext&);
void fn__sceSetOsdConfigParam_00503200(p3fes::EEContext&);
void fn__sceSetSyscall_0050cc68(p3fes::EEContext&);
void fn__sceSetSyscall_0_0050d648(p3fes::EEContext&);
void fn__sceSetSyscall_3_0050dad0(p3fes::EEContext&);
void fn__sceSifDmaStat_00503500(p3fes::EEContext&);
void fn__sceSifGetReg_00503570(p3fes::EEContext&);
void fn__sceSifLoadModule_0050c2c0(p3fes::EEContext&);
void fn__sceSifSetDChain_00503540(p3fes::EEContext&);
void fn__sceSifSetDma_00503520(p3fes::EEContext&);
void fn__sceSifSetReg_00503560(p3fes::EEContext&);
void fn__sceSifStopDma_00503430(p3fes::EEContext&);
void fn__sceSignalSema_00503180(p3fes::EEContext&);
void fn__sceSleepThread_00503080(p3fes::EEContext&);
void fn__sceStartThread_00502f80(p3fes::EEContext&);
void fn__sceWaitSema_005031a0(p3fes::EEContext&);
void fn__sce_DisableDmac_00502ed0(p3fes::EEContext&);
void fn__sce_EnableDmac_00502ec0(p3fes::EEContext&);
void fn__sce_EnableIntc_00502ea0(p3fes::EEContext&);
void fn__sce_iWakeupThread_005030a0(p3fes::EEContext&);
void fn__sceiReferThreadStatus_00503070(p3fes::EEContext&);
void fn__sceiSignalSema_00503190(p3fes::EEContext&);
void fn__sdrCBThread_00512f80(p3fes::EEContext&);
void fn__sequenceHeader_004feee0(p3fes::EEContext&);
void fn__skipMB0_004fd8a8(p3fes::EEContext&);
void fn__slice0_004fc3a8(p3fes::EEContext&);
void fn__waitIpuIdle_004fd868(p3fes::EEContext&);
void fn__waitIpuIdle_0_004ff998(p3fes::EEContext&);
void fn_adxf_AddRofsVol_0053b318(p3fes::EEContext&);
void fn_adxf_ExecOne_0053d640(p3fes::EEContext&);
void fn_adxf_ExecServer_0053d730(p3fes::EEContext&);
void fn_adxf_GetFsizeSct_0053d9a0(p3fes::EEContext&);
void fn_adxf_GetStat_0053dbc8(p3fes::EEContext&);
void fn_adxf_LoadPartitionNw_0053b8d0(p3fes::EEContext&);
void fn_adxf_Open_0053c958(p3fes::EEContext&);
void fn_adxf_ReadNw32_0053d1f0(p3fes::EEContext&);
void fn_adxf_ReadNw_0053d3d8(p3fes::EEContext&);
void fn_adxf_SetDefDev_0053b528(p3fes::EEContext&);
void fn_adxf_SetFileInfoEx_0053c860(p3fes::EEContext&);
void fn_adxf_SetupRofs_0053b250(p3fes::EEContext&);
void fn_btlTableInit_0027e180(p3fes::EEContext&);
void fn_cbTimerHandler_0050e250(p3fes::EEContext&);
void fn_cdvd_exit_0050fa48(p3fes::EEContext&);
void fn_cmd_sem_init_0050f960(p3fes::EEContext&);
void fn_datClearFlagAll_0016f2e0(p3fes::EEContext&);
void fn_datGetFlag_0016f190(p3fes::EEContext&);
void fn_datSetDaysSinceApr5_0016ef70(p3fes::EEContext&);
void fn_datSetFlag_0016f1f0(p3fes::EEContext&);
void fn_dmaRefImage_004fdb18(p3fes::EEContext&);
void fn_dvCiCdSearchFile_00559dd8(p3fes::EEContext&);
void fn_effAfter_CreateAfterEffectRenderTask_001eef20(p3fes::EEContext&);
void fn_effMng_CreateEffectProgramTasks_00322010(p3fes::EEContext&);
void fn_flushBuf32_004ffb30(p3fes::EEContext&);
void fn_flushByteBoundary_004ffb38(p3fes::EEContext&);
void fn_frFontSystemStart_003b4ee0(p3fes::EEContext&);
void fn_j__sceMpegFlushBuf_0_004ff9d0(p3fes::EEContext&);
void fn_kwlnGsSyncVCallback_00197fe0(p3fes::EEContext&);
void fn_kwlnInitMain_00198010(p3fes::EEContext&);
void fn_kwlnInitPS2Systems_00197030(p3fes::EEContext&);
void fn_kwlnInitRenderer_00197350(p3fes::EEContext&);
void fn_kwlnMain_001984c0(p3fes::EEContext&);
void fn_kwlnRootCreateTask_00198940(p3fes::EEContext&);
void fn_kwlnRootUpdateShowRasterTask_00199140(p3fes::EEContext&);
void fn_kwlnSetFlags_00198610(p3fes::EEContext&);
void fn_kwlnT0OverflowHandler_00196fe0(p3fes::EEContext&);
void fn_kwlnTaskExists_00195460(p3fes::EEContext&);
void fn_kwlnTaskMain_001949e0(p3fes::EEContext&);
void fn_kwlnUpdate_001983a0(p3fes::EEContext&);
void fn_memcmp_005211b8(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_printf_005225a8(p3fes::EEContext&);
void fn_receiveDataFromIPU_004fe988(p3fes::EEContext&);
void fn_sbrk_00503860(p3fes::EEContext&);
void fn_sceCdDiskReady_00510960(p3fes::EEContext&);
void fn_sceCdDiskReady_old_00510748(p3fes::EEContext&);
void fn_sceCdGetError_00510ef0(p3fes::EEContext&);
void fn_sceCdInit_00510460(p3fes::EEContext&);
void fn_sceCdLayerSearchFile_0050fc38(p3fes::EEContext&);
void fn_sceCdMmode_00511040(p3fes::EEContext&);
void fn_sceCdNcmdDiskReady_005100b0(p3fes::EEContext&);
void fn_sceCdRead_00510b80(p3fes::EEContext&);
void fn_sceCdSyncS_005101e8(p3fes::EEContext&);
void fn_sceCdSync_00510148(p3fes::EEContext&);
void fn_sceDbcCreateSocket_0051c770(p3fes::EEContext&);
void fn_sceDbcGetModVersion_0051c360(p3fes::EEContext&);
void fn_sceDbcSendData3_0051d308(p3fes::EEContext&);
void fn_sceDbcSetWorkAddr_0051c700(p3fes::EEContext&);
void fn_sceGsSyncVCallback_004fa4b8(p3fes::EEContext&);
void fn_sceIpuInit_00502b08(p3fes::EEContext&);
void fn_sceMc2SifCallback_0051ae38(p3fes::EEContext&);
void fn_scePadGetModVersion_00512640(p3fes::EEContext&);
void fn_scePadInit2_005112d0(p3fes::EEContext&);
void fn_scePadSetActAlign_00512138(p3fes::EEContext&);
void fn_scePadSetMainMode_00511fb8(p3fes::EEContext&);
void fn_scePadSetReqState_00511b08(p3fes::EEContext&);
void fn_scePrintf_00505e48(p3fes::EEContext&);
void fn_sceResetttyinit_005035e0(p3fes::EEContext&);
void fn_sceSdRemoteCallbackInit_00512d48(p3fes::EEContext&);
void fn_sceSdRemote_005129c0(p3fes::EEContext&);
void fn_sceSifAllocIopHeap_0050b620(p3fes::EEContext&);
void fn_sceSifAllocSysMemory_0050b690(p3fes::EEContext&);
void fn_sceSifBindRpc_00507050(p3fes::EEContext&);
void fn_sceSifCallRpc_00507230(p3fes::EEContext&);
void fn_sceSifCheckStatRpc_00507430(p3fes::EEContext&);
void fn_sceSifExecNotifyHandler_0050f588(p3fes::EEContext&);
void fn_sceSifExecRequest_00507758(p3fes::EEContext&);
void fn_sceSifExitRpc_00506a48(p3fes::EEContext&);
void fn_sceSifFreeSysMemory_0050b710(p3fes::EEContext&);
void fn_sceSifGetNextRequest_00507700(p3fes::EEContext&);
void fn_sceSifGetSreg_00505f78(p3fes::EEContext&);
void fn_sceSifInitCmd_00506148(p3fes::EEContext&);
void fn_sceSifInitIopHeap_0050b598(p3fes::EEContext&);
void fn_sceSifInitRpc_005068a8(p3fes::EEContext&);
void fn_sceSifLoadModule_0050c4e8(p3fes::EEContext&);
void fn_sceSifRebootIop_0050ca18(p3fes::EEContext&);
void fn_sceSifRegisterRpc_00507508(p3fes::EEContext&);
void fn_sceSifResetIop_0050c848(p3fes::EEContext&);
void fn_sceSifRpcLoop_00507920(p3fes::EEContext&);
void fn_sceSifSetDmaInternal_00505fc0(p3fes::EEContext&);
void fn_sceSifSetDma_00506088(p3fes::EEContext&);
void fn_sceSifSetRpcQueue_00507470(p3fes::EEContext&);
void fn_sceSifSyncIop_0050c9c8(p3fes::EEContext&);
void fn_sceSkSsHSYNTH_Bind_0051dc70(p3fes::EEContext&);
void fn_sceSkSsHSYNTH_Unbind_0051dd48(p3fes::EEContext&);
void fn_sceSkSsSESQ_Bind_0051ddf0(p3fes::EEContext&);
void fn_sceSkSsSESQ_Unbind_0051deb0(p3fes::EEContext&);
void fn_sceSkSsSOUND_Send_0051dbc0(p3fes::EEContext&);
void fn_setD4_CHCR_0_00502a90(p3fes::EEContext&);
void fn_sprFontInit_00111f50(p3fes::EEContext&);
void fn_sprintf_00523ac8(p3fes::EEContext&);
void fn_strcmp_00524128(p3fes::EEContext&);
void fn_strncpy_00524828(p3fes::EEContext&);
void fn_sub_103580_00103580(p3fes::EEContext&);
void fn_sub_1042E0_001042e0(p3fes::EEContext&);
void fn_sub_1043B0_001043b0(p3fes::EEContext&);
void fn_sub_105800_00105800(p3fes::EEContext&);
void fn_sub_107020_00107020(p3fes::EEContext&);
void fn_sub_108740_00108740(p3fes::EEContext&);
void fn_sub_108BC0_00108bc0(p3fes::EEContext&);
void fn_sub_10BF70_0010bf70(p3fes::EEContext&);
void fn_sub_10E630_0010e630(p3fes::EEContext&);
void fn_sub_119A20_00119a20(p3fes::EEContext&);
void fn_sub_16C1D0_0016c1d0(p3fes::EEContext&);
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
void fn_sub_16E930_0016e930(p3fes::EEContext&);
void fn_sub_16E990_0016e990(p3fes::EEContext&);
void fn_sub_16F150_0016f150(p3fes::EEContext&);
void fn_sub_16F180_0016f180(p3fes::EEContext&);
void fn_sub_16F320_0016f320(p3fes::EEContext&);
void fn_sub_16F3E0_0016f3e0(p3fes::EEContext&);
void fn_sub_16F450_0016f450(p3fes::EEContext&);
void fn_sub_16FEA0_0016fea0(p3fes::EEContext&);
void fn_sub_170860_00170860(p3fes::EEContext&);
void fn_sub_170B20_00170b20(p3fes::EEContext&);
void fn_sub_170B90_00170b90(p3fes::EEContext&);
void fn_sub_175820_00175820(p3fes::EEContext&);
void fn_sub_175BE0_00175be0(p3fes::EEContext&);
void fn_sub_175C70_00175c70(p3fes::EEContext&);
void fn_sub_1773D0_001773d0(p3fes::EEContext&);
void fn_sub_1779A0_001779a0(p3fes::EEContext&);
void fn_sub_177CE0_00177ce0(p3fes::EEContext&);
void fn_sub_177D40_00177d40(p3fes::EEContext&);
void fn_sub_17ADF0_0017adf0(p3fes::EEContext&);
void fn_sub_17B160_0017b160(p3fes::EEContext&);
void fn_sub_17B1A0_0017b1a0(p3fes::EEContext&);
void fn_sub_17B2A0_0017b2a0(p3fes::EEContext&);
void fn_sub_17C190_0017c190(p3fes::EEContext&);
void fn_sub_17C280_0017c280(p3fes::EEContext&);
void fn_sub_17D3C0_0017d3c0(p3fes::EEContext&);
void fn_sub_17D7C0_0017d7c0(p3fes::EEContext&);
void fn_sub_17D800_0017d800(p3fes::EEContext&);
void fn_sub_182C50_00182c50(p3fes::EEContext&);
void fn_sub_1830C0_001830c0(p3fes::EEContext&);
void fn_sub_18BC80_0018bc80(p3fes::EEContext&);
void fn_sub_18E4A0_0018e4a0(p3fes::EEContext&);
void fn_sub_195DE0_00195de0(p3fes::EEContext&);
void fn_sub_196770_00196770(p3fes::EEContext&);
void fn_sub_198590_00198590(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_1B7BB0_001b7bb0(p3fes::EEContext&);
void fn_sub_1B7C40_001b7c40(p3fes::EEContext&);
void fn_sub_1B7D00_001b7d00(p3fes::EEContext&);
void fn_sub_1B7DC0_001b7dc0(p3fes::EEContext&);
void fn_sub_1B8B40_001b8b40(p3fes::EEContext&);
void fn_sub_1B8C40_001b8c40(p3fes::EEContext&);
void fn_sub_1CD7A0_001cd7a0(p3fes::EEContext&);
void fn_sub_1D4290_001d4290(p3fes::EEContext&);
void fn_sub_1D4560_001d4560(p3fes::EEContext&);
void fn_sub_1D7260_001d7260(p3fes::EEContext&);
void fn_sub_1DCA10_001dca10(p3fes::EEContext&);
void fn_sub_1E7720_001e7720(p3fes::EEContext&);
void fn_sub_1FA0D0_001fa0d0(p3fes::EEContext&);
void fn_sub_1FC1F0_001fc1f0(p3fes::EEContext&);
void fn_sub_20C8D0_0020c8d0(p3fes::EEContext&);
void fn_sub_25B440_0025b440(p3fes::EEContext&);
void fn_sub_267260_00267260(p3fes::EEContext&);
void fn_sub_27C8F0_0027c8f0(p3fes::EEContext&);
void fn_sub_31B470_0031b470(p3fes::EEContext&);
void fn_sub_3210A0_003210a0(p3fes::EEContext&);
void fn_sub_323240_00323240(p3fes::EEContext&);
void fn_sub_323FB0_00323fb0(p3fes::EEContext&);
void fn_sub_3243F0_003243f0(p3fes::EEContext&);
void fn_sub_324510_00324510(p3fes::EEContext&);
void fn_sub_342550_00342550(p3fes::EEContext&);
void fn_sub_343860_00343860(p3fes::EEContext&);
void fn_sub_396BF0_00396bf0(p3fes::EEContext&);
void fn_sub_3BD130_003bd130(p3fes::EEContext&);
void fn_sub_3BD280_003bd280(p3fes::EEContext&);
void fn_sub_4302B0_004302b0(p3fes::EEContext&);
void fn_sub_488F30_00488f30(p3fes::EEContext&);
void fn_sub_4C4D20_004c4d20(p3fes::EEContext&);
void fn_sub_4C7CF0_004c7cf0(p3fes::EEContext&);
void fn_sub_4CBF20_004cbf20(p3fes::EEContext&);
void fn_sub_4CDC70_004cdc70(p3fes::EEContext&);
void fn_sub_4CDE00_004cde00(p3fes::EEContext&);
void fn_sub_4CE200_004ce200(p3fes::EEContext&);
void fn_sub_4D5E90_004d5e90(p3fes::EEContext&);
void fn_sub_4D8300_004d8300(p3fes::EEContext&);
void fn_sub_4D8310_004d8310(p3fes::EEContext&);
void fn_sub_4FD8A0_004fd8a0(p3fes::EEContext&);
void fn_sub_506430_00506430(p3fes::EEContext&);
void fn_sub_506630_00506630(p3fes::EEContext&);
void fn_sub_5066B0_005066b0(p3fes::EEContext&);
void fn_sub_5067F8_005067f8(p3fes::EEContext&);
void fn_sub_50DC80_0050dc80(p3fes::EEContext&);
void fn_sub_50DC90_0050dc90(p3fes::EEContext&);
void fn_sub_50DCA0_0050dca0(p3fes::EEContext&);
void fn_sub_50E000_0050e000(p3fes::EEContext&);
void fn_sub_50E190_0050e190(p3fes::EEContext&);
void fn_sub_50E218_0050e218(p3fes::EEContext&);
void fn_sub_50E508_0050e508(p3fes::EEContext&);
void fn_sub_51F690_0051f690(p3fes::EEContext&);
void fn_sub_539818_00539818(p3fes::EEContext&);
void fn_sub_539830_00539830(p3fes::EEContext&);
void fn_sub_53AE08_0053ae08(p3fes::EEContext&);
void fn_sub_53B4F8_0053b4f8(p3fes::EEContext&);
void fn_sub_53B5A8_0053b5a8(p3fes::EEContext&);
void fn_sub_53B5D0_0053b5d0(p3fes::EEContext&);
void fn_sub_53B6B0_0053b6b0(p3fes::EEContext&);
void fn_sub_53BEF0_0053bef0(p3fes::EEContext&);
void fn_sub_53C198_0053c198(p3fes::EEContext&);
void fn_sub_53C2A0_0053c2a0(p3fes::EEContext&);
void fn_sub_53C7C8_0053c7c8(p3fes::EEContext&);
void fn_sub_53CAE0_0053cae0(p3fes::EEContext&);
void fn_sub_53CCC0_0053ccc0(p3fes::EEContext&);
void fn_sub_53CE00_0053ce00(p3fes::EEContext&);
void fn_sub_53DD98_0053dd98(p3fes::EEContext&);
void fn_sub_53E088_0053e088(p3fes::EEContext&);
void fn_sub_53E0A0_0053e0a0(p3fes::EEContext&);
void fn_sub_53EA90_0053ea90(p3fes::EEContext&);
void fn_sub_540570_00540570(p3fes::EEContext&);
void fn_sub_540EA8_00540ea8(p3fes::EEContext&);
void fn_sub_541760_00541760(p3fes::EEContext&);
void fn_sub_5417E0_005417e0(p3fes::EEContext&);
void fn_sub_54CFE8_0054cfe8(p3fes::EEContext&);
void fn_sub_558988_00558988(p3fes::EEContext&);
void fn_sub_569F60_00569f60(p3fes::EEContext&);
void fn_sub_57F768_0057f768(p3fes::EEContext&);
void fn_sub_5810F0_005810f0(p3fes::EEContext&);
void fn_sub_594038_00594038(p3fes::EEContext&);
void fn_sub_5940A0_005940a0(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// 0x00100800 H_Cdvd_InitCd -- 172 bytes; frame 0x10: ra sp+0x0
// Brings the disc layer up: sceCdInit(0), sceCdMmode(2 = DVD), sceCdDiskReady(0); then empties the request list
// (sCdvdListHead / sCdvdListFirst and the words beside them) and the first word of each of the 256 sCdvdCache entries (148 bytes each).
void H_Cdvd_InitCd(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00100800
    enter(ctx, 26);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x10080Cu, gen::fn_sceCdInit_00510460);
    a0 = 2;
    jal(ctx, 0x100818u, gen::fn_sceCdMmode_00511040);
    a0 = 0;
    jal(ctx, 0x100824u, gen::fn_sceCdDiskReady_00510960);
    v1 = 0x7E0000;
    sw(zero, v1, 896);  // sCdvdListHead
    v1 = 0x7E0000;
    sw(zero, v1, 900);  // sCdvdListFirst
    v1 = 0x7E0000;
    sw(zero, v1, 1168);  // 0x7E0490
    v1 = 0x7E0000;
    sw(zero, v1, 1176);  // 0x7E0498
    v1 = 0x7E0000;
    sw(zero, v1, 904);  // 0x7E0388
    a1 = 0;
    a0 = 0x7D0000;
    a0 = addiu(a0, 28544);  // &sCdvdCache
    for (;;) {
        // 0x00100888
        charge(ctx, 3);
        v1 = slti(a1, 256);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00100868
        charge(ctx, 8);
        v1 = sll(a1, 3);
        v1 = addu(v1, a1);
        v1 = sll(v1, 2);
        v1 = addu(v1, a1);
        v1 = sll(v1, 2);
        v1 = addu(a0, v1);
        sw(zero, v1, 0);
        a1 = addiu(a1, 1);
    }
    // 0x00100894
    charge(ctx, 6);
    v1 = 0x7E0000;
    sw(zero, v1, 1236);  // 0x7E04D4
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00101520 H_Cdvd_SetRofsDir -- 388 bytes; frame 0x130: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Points ROFS at a directory: the part after "VOL:" is compared with the BTL and VOL directory-name tables and
// ROFS_SetDir is retried until it succeeds (printing "SetDir Error" / the ROFS error on a failure).
void H_Cdvd_SetRofsDir(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00101520
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x130);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a1 = addiu(sp, 0x30);
    jal(ctx, 0x101534u, gen::fn_H_Cdvd_NormalizePath_001013f0);
    s1 = 0;
    for (;;) {
        // 0x001015bc
        charge(ctx, 5);
        a0 = dsll32(s1, 16);
        a0 = dsra32(a0, 16);
        v1 = slti(a0, 300);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00101548
        charge(ctx, 8);
        s0 = sll(a0, 2);
        v1 = 0x5D0000;
        v1 = addiu(v1, -8832);  // &g_tbl_rofsDirNames_BTL
        v1 = addu(v1, s0);
        lw(a0, v1, 0);
        lb(v1, a0, 0);
        if (v1 == 0) {
            break;
        }
        // 0x00101568
        charge(ctx, 5);
        a1 = addiu(sp, 0x34);
        jal(ctx, 0x10156Cu, gen::fn_strcmp_00524128);
        if (v0 == 0) {
            goto L_0010157c_3;
        }
        // 0x001015b0
        charge(ctx, 3);
        v1 = addiu(s1, 1);
        s1 = dsll32(v1, 16);
        s1 = dsra32(s1, 16);
    }
    // 0x001015d0
    charge(ctx, 3);
    s1 = 0;
    for (;;) {
        // 0x00101678
        charge(ctx, 5);
        a0 = dsll32(s1, 16);
        a0 = dsra32(a0, 16);
        v1 = slti(a0, 300);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001015dc
        charge(ctx, 8);
        s0 = sll(a0, 2);
        v0 = 0x5D0000;
        v0 = addiu(v0, -6768);  // &g_tbl_rofsDirNames_VOL
        v0 = addu(v0, s0);
        lw(a0, v0, 0);
        lb(v0, a0, 0);
        if (v0 == 0) {
            goto L_001015fc_10;
        }
        // 0x00101618
        charge(ctx, 5);
        a1 = addiu(sp, 0x34);
        jal(ctx, 0x10161Cu, gen::fn_strcmp_00524128);
        if (v0 == 0) {
            goto L_0010162c_12;
        }
        // 0x0010166c
        charge(ctx, 3);
        v1 = addiu(s1, 1);
        s1 = dsll32(v1, 16);
        s1 = dsra32(s1, 16);
    }
    // 0x0010168c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x130);
    return;
L_0010157c_3:
    charge(ctx, 3);
    v0 = 0x5D0000;
    v0 = addiu(v0, -8720);  // "0Cd"
    s0 = addu(v0, s0);
    for (;;) {
        // 0x00101588
        charge(ctx, 8);
        a0 = addiu(gp, -31416);  // "BTL"
        lw(a1, s0, 0);
        jal(ctx, 0x101590u, gen::fn_ROFS_SetDir_00566b08);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x001015a8
    charge(ctx, 2);
    // 0x0010168c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x130);
    return;
L_001015fc_10:
    charge(ctx, 7);
    a0 = 0x5D0000;
    a0 = addiu(a0, -5776);  // " SetDir Error [ %s ] \n"
    a1 = addiu(sp, 0x34);
    jal(ctx, 0x101608u, gen::fn_printf_005225a8);
    // 0x0010168c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x130);
    return;
L_0010162c_12:
    charge(ctx, 3);
    v0 = 0x5D0000;
    v0 = addiu(v0, -6272);  // "PQ^"
    s0 = addu(v0, s0);
    for (;;) {
        // 0x00101638
        charge(ctx, 7);
        a0 = addiu(gp, -31412);  // "VOL"
        lw(a1, s0, 0);
        jal(ctx, 0x101640u, gen::fn_ROFS_SetDir_00566b08);
        a1 = v0;
        if (a1 == 0) {
            break;
        }
        // 0x00101654
        charge(ctx, 6);
        a0 = 0x5D0000;
        a0 = addiu(a0, -5752);  // "rofs err %d\n"
        jal(ctx, 0x10165Cu, gen::fn_printf_005225a8);
        backedge(ctx);
    }
    // 0x0010168c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x130);
}

// 0x001024A0 H_Cdvd_LoadAfsFile -- 132 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Loads an AFS partition by its VOL: name through ADXF_LoadPartitionNw (non-blocking; H_Cdvd_Update polls it).
void H_Cdvd_LoadAfsFile(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001024a0
    enter(ctx, 33);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a3;
    a0 = a1;
    a1 = 0x7D0000;
    a1 = addiu(a1, -4480);  // &0x7CEE80
    jal(ctx, 0x1024C4u, gen::fn_H_Cdvd_BuildPathUppercase_00101010);
    a0 = 0x7D0000;
    a0 = addiu(a0, -4480);  // &0x7CEE80
    a1 = 0x7D0000;
    a1 = addiu(a1, -4224);  // &0x7CEF80
    a2 = 0x7D0000;
    a2 = addiu(a2, -3968);  // &0x7CF080
    jal(ctx, 0x1024E4u, gen::fn_H_Cdvd_SplitPath_00101100);
    a0 = s1;
    a1 = 0x7D0000;
    a1 = addiu(a1, -4224);  // &0x7CEF80
    a2 = 0x640000;
    a2 = addiu(a2, -31968);  // &tbl_DirLst_VOL_SOUND
    a3 = s0;
    jal(ctx, 0x102504u, gen::fn_ADXF_LoadPartitionNw_0053b868);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0010CCE0 H_Sndcom_CopyToIop -- 232 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Copies a block from EE RAM to IOP RAM for the sound banks: fills the SIF DMA request, flushes the data cache,
// queues it with sceSifSetDma and spins on sceSifDmaStat until the transfer is done (asserts when it cannot queue).
void H_Sndcom_CopyToIop(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0010cce0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a2;
    if (i64(s1) > 0) {
        // 0x0010cd08
        charge(ctx, 19);
        v0 = 0x830000;
        sw(a1, v0, 13888);  // g_sndcomSifDmaReq
        v0 = 0x830000;
        sw(a0, v0, 13892);  // g_sndcomSifDmaReq+0x4
        v0 = 0x830000;
        sw(s1, v0, 13896);  // g_sndcomSifDmaReq+0x8
        v0 = 0x830000;
        sw(zero, v0, 13900);  // g_sndcomSifDmaReq+0xC
        a0 = 0;
        jal(ctx, 0x10CD2Cu, gen::fn__sceFlushCache_005033e0);
        a0 = 0x830000;
        a0 = addiu(a0, 13888);  // &g_sndcomSifDmaReq
        a1 = 1;
        jal(ctx, 0x10CD40u, gen::fn_sceSifSetDma_00506088);
        s0 = v0;
        if (s0 == 0) {
            // 0x0010cd54
            charge(ctx, 5);
            a0 = 0x5D0000;
            a0 = addiu(a0, 21448);  // "h_sndcom.c"
            a1 = 263;
            jal(ctx, 0x10CD60u, gen::fn_sub_19D3F0_0019d3f0);
        }
        for (;;) {
            // 0x0010cd68
            charge(ctx, 8);
            a0 = s0;
            jal(ctx, 0x10CD6Cu, gen::fn__sceSifDmaStat_00503500);
            if (i64(v0) < 0) {
                break;
            }
            backedge(ctx);
        }
        for (;;) {
            // 0x0010cd88
            charge(ctx, 5);
            a0 = s0;
            jal(ctx, 0x10CD8Cu, gen::fn__sceSifDmaStat_00503500);
            if (i64(v0) > 0) {
                backedge(ctx);
                continue;
            }
            // 0x0010cd9c
            charge(ctx, 4);
            if (v0 != 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0010cdac
        charge(ctx, 1);
        v0 = s1;
    } else {
        // 0x0010ccfc
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0010cdb0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0010CDD0 H_Sndcom_Update -- 2324 bytes; frame 0xC0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// The per-frame sound-bank state machine: loads the hd / bd / sq files, stages them in IOP memory
// (sceSifAllocSysMemory + H_Sndcom_CopyToIop), uploads the bodies to SPU2 in chunks (sceSkSsSOUND_Send) and binds
// them (sceSkSsHSYNTH_Bind / sceSkSsSESQ_Bind); frees the IOP staging memory when a bank is done.
void H_Sndcom_Update(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x0010cdd0
    enter(ctx, 14);  // entry check point + this block's cycles
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
    s4 = 0;
    for (;;) {
        // 0x0010d69c
        charge(ctx, 5);
        a0 = dsll32(s4, 16);
        a0 = dsra32(a0, 16);
        v1 = slti(a0, 6);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0010ce08
        charge(ctx, 10);
        v1 = sll(a0, 4);
        v1 = addu(v1, a0);
        a0 = sll(v1, 2);
        v1 = 0x830000;
        v1 = addiu(v1, 14096);  // &0x833710
        s0 = addu(v1, a0);
        lh(a0, s0, 0);
        at = sltiu(a0, 9);
        if (at != 0) {
            // 0x0010ce30
            charge(ctx, 7);
            a1 = 0x7B0000;
            a1 = addiu(a1, 21216);  // &0x7B52E0
            a0 = sll(a0, 2);
            a0 = addu(a0, a1);
            lw(a0, a0, 0);
            switch (a0.u()) {
            case 0x10CE4Cu:  // table[0]
                // 0x0010ce4c
                charge(ctx, 4);
                v1 = 1;
                sh(v1, s0, 0);
                break;
            case 0x10CE5Cu:  // table[2]
                // 0x0010ce5c
                charge(ctx, 22);
                a0 = dsll32(s4, 16);
                a0 = dsra32(a0, 16);
                v0 = sll(a0, 4);
                v0 = addu(v0, a0);
                v0 = sll(v0, 2);
                s0 = addu(v1, v0);
                lh(v1, s0, 8);
                v0 = sll(v1, 1);
                v0 = addu(v0, v1);
                v1 = sll(v0, 2);
                v0 = 0x5D0000;
                v0 = addiu(v0, 21408);  // &tbl_H_Sndcom_BankFiles
                v0 = addu(v0, v1);
                lw(a0, v0, 0);
                a1 = 0;
                jal(ctx, 0x10CE98u, gen::fn_H_Cdvd_Request_00100d80);
                sw(v0, s0, 4);
                v1 = 3;
                sh(v1, s0, 0);
                break;
            case 0x10CEB4u:  // table[3]
                // 0x0010ceb4
                charge(ctx, 5);
                lw(a0, s0, 4);
                jal(ctx, 0x10CEB8u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
                if (v0 != 0) {
                    // 0x0010cec8
                    charge(ctx, 20);
                    lh(v1, s0, 8);
                    v0 = sll(v1, 1);
                    v0 = addu(v0, v1);
                    v1 = sll(v0, 2);
                    v0 = 0x5D0000;
                    v0 = addiu(v0, 21408);  // &tbl_H_Sndcom_BankFiles
                    v0 = addu(v0, v1);
                    lw(a0, v0, 0);
                    a1 = addiu(sp, 0xBC);
                    jal(ctx, 0x10CEECu, gen::fn_H_Cdvd_CacheFindFile_001021c0);
                    s0 = v0;
                    lw(a1, sp, 0xBC);
                    a0 = 0;
                    a2 = 0;
                    jal(ctx, 0x10CF04u, gen::fn_sceSifAllocSysMemory_0050b690);
                    s1 = v0;
                    if (s1 == 0) {
                        // 0x0010cf18
                        charge(ctx, 5);
                        a0 = 0x5D0000;
                        a0 = addiu(a0, 21448);  // "h_sndcom.c"
                        a1 = 324;
                        jal(ctx, 0x10CF24u, gen::fn_sub_19D3F0_0019d3f0);
                    }
                    // 0x0010cf2c
                    charge(ctx, 32);
                    lw(a2, sp, 0xBC);
                    a0 = 0x820000;
                    a0 = addiu(a0, 13904);  // &0x823650
                    a1 = s0;
                    jal(ctx, 0x10CF3Cu, gen::fn_memcpy_00521250);
                    a0 = s1;
                    a1 = 0x820000;
                    a1 = addiu(a1, 13904);  // &0x823650
                    lw(a2, sp, 0xBC);
                    jal(ctx, 0x10CF54u, gen::fn_H_Sndcom_CopyToIop_0010cce0);
                    v1 = dsll32(s4, 16);
                    v1 = dsra32(v1, 16);
                    v0 = sll(v1, 4);
                    v0 = addu(v0, v1);
                    v1 = sll(v0, 2);
                    v0 = 0x830000;
                    v0 = addiu(v0, 14096);  // &0x833710
                    s0 = addu(v0, v1);
                    s2 = addiu(s0, 4);
                    lw(a0, s0, 4);
                    jal(ctx, 0x10CF84u, gen::fn_H_Cdvd_Destroy_00100ec0);
                    sw(s1, s0, 28);
                    lw(v1, sp, 0xBC);
                    sw(v1, s0, 32);
                    sw(zero, s2, 0);
                    v1 = 4;
                    sh(v1, s0, 0);
                }
                break;
            case 0x10CFACu:  // table[4]
                // 0x0010cfac
                charge(ctx, 22);
                a0 = dsll32(s4, 16);
                a0 = dsra32(a0, 16);
                v0 = sll(a0, 4);
                v0 = addu(v0, a0);
                v0 = sll(v0, 2);
                s0 = addu(v1, v0);
                lh(v1, s0, 8);
                v0 = sll(v1, 1);
                v0 = addu(v0, v1);
                v1 = sll(v0, 2);
                v0 = 0x5D0000;
                v0 = addiu(v0, 21408);  // &tbl_H_Sndcom_BankFiles
                v0 = addu(v0, v1);
                lw(a0, v0, 4);
                a1 = 0;
                jal(ctx, 0x10CFE8u, gen::fn_H_Cdvd_Request_00100d80);
                sw(v0, s0, 4);
                v1 = 5;
                sh(v1, s0, 0);
                break;
            case 0x10D004u:  // table[5]
                // 0x0010d004
                charge(ctx, 5);
                lw(a0, s0, 4);
                jal(ctx, 0x10D008u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
                if (v0 != 0) {
                    // 0x0010d018
                    charge(ctx, 20);
                    lh(v1, s0, 8);
                    v0 = sll(v1, 1);
                    v0 = addu(v0, v1);
                    v1 = sll(v0, 2);
                    v0 = 0x5D0000;
                    v0 = addiu(v0, 21408);  // &tbl_H_Sndcom_BankFiles
                    v0 = addu(v0, v1);
                    lw(a0, v0, 4);
                    a1 = addiu(sp, 0xBC);
                    jal(ctx, 0x10D03Cu, gen::fn_H_Cdvd_CacheFindFile_001021c0);
                    s0 = v0;
                    a0 = 0;
                    a1 = 4096;
                    a2 = 0;
                    jal(ctx, 0x10D054u, gen::fn_sceSifAllocSysMemory_0050b690);
                    s1 = v0;
                    if (s1 == 0) {
                        // 0x0010d068
                        charge(ctx, 5);
                        a0 = 0x5D0000;
                        a0 = addiu(a0, 21448);  // "h_sndcom.c"
                        a1 = 375;
                        jal(ctx, 0x10D074u, gen::fn_sub_19D3F0_0019d3f0);
                    }
                    // 0x0010d07c
                    charge(ctx, 11);
                    v1 = dsll32(s4, 16);
                    v1 = dsra32(v1, 16);
                    v0 = sll(v1, 4);
                    v0 = addu(v0, v1);
                    v1 = sll(v0, 2);
                    v0 = 0x830000;
                    v0 = addiu(v0, 14096);  // &0x833710
                    v0 = addu(v0, v1);
                    lw(s3, v0, 36);
                    lw(s2, sp, 0xBC);
                    sw(s2, v0, 40);
                    for (;;) {
                        // 0x0010d0a8
                        charge(ctx, 3);
                        at = slti(s2, 4097);
                        if (at != 0) {
                            // 0x0010d0c8
                            charge(ctx, 2);
                            sw(s2, sp, 0xBC);
                            s2 = 0;
                        } else {
                            // 0x0010d0b4
                            charge(ctx, 5);
                            v0 = 4096;
                            sw(v0, sp, 0xBC);
                            s2 = addiu(s2, -4096);
                        }
                        // 0x0010d0d0
                        charge(ctx, 16);
                        a0 = s1;
                        a1 = s0;
                        lw(a2, sp, 0xBC);
                        jal(ctx, 0x10D0DCu, gen::fn_H_Sndcom_CopyToIop_0010cce0);
                        a0 = 1;
                        a1 = s1;
                        a2 = s3;
                        lw(a3, sp, 0xBC);
                        jal(ctx, 0x10D0F4u, gen::fn_sceSkSsSOUND_Send_0051dbc0);
                        lw(v0, sp, 0xBC);
                        s0 = addu(s0, v0);
                        s3 = addu(s3, v0);
                        if (s2 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0010d110
                    charge(ctx, 20);
                    v1 = dsll32(s4, 16);
                    v1 = dsra32(v1, 16);
                    v0 = sll(v1, 4);
                    v0 = addu(v0, v1);
                    v1 = sll(v0, 2);
                    v0 = 0x830000;
                    v0 = addiu(v0, 14096);  // &0x833710
                    s2 = addu(v0, v1);
                    s0 = addiu(s2, 4);
                    lw(a0, s2, 4);
                    jal(ctx, 0x10D138u, gen::fn_H_Cdvd_Destroy_00100ec0);
                    sw(zero, s0, 0);
                    a0 = s1;
                    jal(ctx, 0x10D148u, gen::fn_sceSifFreeSysMemory_0050b710);
                    v1 = 6;
                    sh(v1, s2, 0);
                }
                break;
            case 0x10D160u:  // table[6]
                // 0x0010d160
                charge(ctx, 22);
                a0 = dsll32(s4, 16);
                a0 = dsra32(a0, 16);
                v0 = sll(a0, 4);
                v0 = addu(v0, a0);
                v0 = sll(v0, 2);
                s0 = addu(v1, v0);
                lh(v1, s0, 8);
                v0 = sll(v1, 1);
                v0 = addu(v0, v1);
                v1 = sll(v0, 2);
                v0 = 0x5D0000;
                v0 = addiu(v0, 21408);  // &tbl_H_Sndcom_BankFiles
                v0 = addu(v0, v1);
                lw(a0, v0, 8);
                a1 = 0;
                jal(ctx, 0x10D19Cu, gen::fn_H_Cdvd_Request_00100d80);
                sw(v0, s0, 4);
                v1 = 7;
                sh(v1, s0, 0);
                break;
            case 0x10D1B8u:  // table[7]
                // 0x0010d1b8
                charge(ctx, 5);
                lw(a0, s0, 4);
                jal(ctx, 0x10D1BCu, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
                if (v0 != 0) {
                    // 0x0010d1cc
                    charge(ctx, 20);
                    lh(v1, s0, 8);
                    v0 = sll(v1, 1);
                    v0 = addu(v0, v1);
                    v1 = sll(v0, 2);
                    v0 = 0x5D0000;
                    v0 = addiu(v0, 21408);  // &tbl_H_Sndcom_BankFiles
                    v0 = addu(v0, v1);
                    lw(a0, v0, 8);
                    a1 = addiu(sp, 0xBC);
                    jal(ctx, 0x10D1F0u, gen::fn_H_Cdvd_CacheFindFile_001021c0);
                    s0 = v0;
                    lw(a1, sp, 0xBC);
                    a0 = 0;
                    a2 = 0;
                    jal(ctx, 0x10D208u, gen::fn_sceSifAllocSysMemory_0050b690);
                    s2 = v0;
                    if (s2 == 0) {
                        // 0x0010d21c
                        charge(ctx, 5);
                        a0 = 0x5D0000;
                        a0 = addiu(a0, 21448);  // "h_sndcom.c"
                        a1 = 418;
                        jal(ctx, 0x10D228u, gen::fn_sub_19D3F0_0019d3f0);
                    }
                    // 0x0010d230
                    charge(ctx, 35);
                    a0 = s2;
                    a1 = s0;
                    lw(a2, sp, 0xBC);
                    jal(ctx, 0x10D23Cu, gen::fn_H_Sndcom_CopyToIop_0010cce0);
                    v1 = dsll32(s4, 16);
                    v1 = dsra32(v1, 16);
                    v0 = sll(v1, 4);
                    v0 = addu(v0, v1);
                    v1 = sll(v0, 2);
                    v0 = 0x830000;
                    v0 = addiu(v0, 14096);  // &0x833710
                    s0 = addu(v0, v1);
                    s1 = addiu(s0, 4);
                    lw(a0, s0, 4);
                    jal(ctx, 0x10D26Cu, gen::fn_H_Cdvd_Destroy_00100ec0);
                    s3 = addiu(s0, 44);
                    sw(s2, s0, 44);
                    s2 = addiu(s0, 48);
                    lw(v0, sp, 0xBC);
                    sw(v0, s0, 48);
                    sw(zero, s1, 0);
                    s1 = addiu(s0, 12);
                    a0 = 3;
                    a1 = si(-1);
                    lw(a2, s0, 28);
                    lw(a3, s0, 32);
                    lw(t0, s0, 36);
                    lw(t1, s0, 40);
                    jal(ctx, 0x10D2A8u, gen::fn_sceSkSsHSYNTH_Bind_0051dc70);
                    sw(v0, s1, 0);
                    if (i64(v0) < 0) {
                        // 0x0010d2bc
                        charge(ctx, 5);
                        a0 = 0x5D0000;
                        a0 = addiu(a0, 21448);  // "h_sndcom.c"
                        a1 = 430;
                        jal(ctx, 0x10D2C8u, gen::fn_sub_19D3F0_0019d3f0);
                    }
                    // 0x0010d2d0
                    charge(ctx, 18);
                    v1 = dsll32(s4, 16);
                    v1 = dsra32(v1, 16);
                    v0 = sll(v1, 4);
                    v0 = addu(v0, v1);
                    v1 = sll(v0, 2);
                    v0 = 0x830000;
                    v0 = addiu(v0, 14096);  // &0x833710
                    v0 = addu(v0, v1);
                    s0 = addiu(v0, 16);
                    a0 = 5;
                    a1 = si(-1);
                    lw(a2, s1, 0);
                    a3 = 0;
                    jal(ctx, 0x10D304u, gen::fn_sceSkSsHSYNTH_Bind_0051dc70);
                    sw(v0, s0, 0);
                    if (i64(v0) < 0) {
                        // 0x0010d318
                        charge(ctx, 5);
                        a0 = 0x5D0000;
                        a0 = addiu(a0, 21448);  // "h_sndcom.c"
                        a1 = 435;
                        jal(ctx, 0x10D324u, gen::fn_sub_19D3F0_0019d3f0);
                    }
                    // 0x0010d32c
                    charge(ctx, 18);
                    v1 = dsll32(s4, 16);
                    v1 = dsra32(v1, 16);
                    v0 = sll(v1, 4);
                    v0 = addu(v0, v1);
                    v1 = sll(v0, 2);
                    v0 = 0x830000;
                    v0 = addiu(v0, 14096);  // &0x833710
                    v0 = addu(v0, v1);
                    s1 = addiu(v0, 20);
                    a0 = 0;
                    a1 = si(-1);
                    lw(a2, s3, 0);
                    lw(a3, s2, 0);
                    jal(ctx, 0x10D360u, gen::fn_sceSkSsSESQ_Bind_0051ddf0);
                    sw(v0, s1, 0);
                    if (i64(v0) < 0) {
                        // 0x0010d374
                        charge(ctx, 5);
                        a0 = 0x5D0000;
                        a0 = addiu(a0, 21448);  // "h_sndcom.c"
                        a1 = 439;
                        jal(ctx, 0x10D380u, gen::fn_sub_19D3F0_0019d3f0);
                    }
                    // 0x0010d388
                    charge(ctx, 19);
                    v1 = dsll32(s4, 16);
                    v1 = dsra32(v1, 16);
                    v0 = sll(v1, 4);
                    v0 = addu(v0, v1);
                    v1 = sll(v0, 2);
                    v0 = 0x830000;
                    v0 = addiu(v0, 14096);  // &0x833710
                    s2 = addu(v0, v1);
                    a0 = 5;
                    lw(a1, s0, 0);
                    lw(a2, s1, 0);
                    jal(ctx, 0x10D3B4u, gen::fn_sceSkSsSESQ_Bind_0051ddf0);
                    sw(v0, s2, 64);
                    v1 = 1;
                    sw(v1, s2, 24);
                    sh(v1, s2, 0);
                }
                break;
            case 0x10D3D4u:  // table[8]
                // 0x0010d3d4
                charge(ctx, 17);
                a0 = dsll32(s4, 16);
                a0 = dsra32(a0, 16);
                v0 = sll(a0, 4);
                v0 = addu(v0, a0);
                v0 = sll(v0, 2);
                v0 = addu(v1, v0);
                lw(s2, v0, 52);
                s5 = addiu(v0, 32);
                lw(a1, v0, 32);
                sw(a1, sp, 0xBC);
                a0 = 0;
                a2 = 0;
                jal(ctx, 0x10D404u, gen::fn_sceSifAllocSysMemory_0050b690);
                s1 = v0;
                if (s1 == 0) {
                    // 0x0010d418
                    charge(ctx, 5);
                    a0 = 0x5D0000;
                    a0 = addiu(a0, 21448);  // "h_sndcom.c"
                    a1 = 456;
                    jal(ctx, 0x10D424u, gen::fn_sub_19D3F0_0019d3f0);
                }
                // 0x0010d42c
                charge(ctx, 29);
                a0 = s1;
                a1 = s2;
                lw(a2, sp, 0xBC);
                jal(ctx, 0x10D438u, gen::fn_H_Sndcom_CopyToIop_0010cce0);
                v1 = dsll32(s4, 16);
                v1 = dsra32(v1, 16);
                v0 = sll(v1, 4);
                v0 = addu(v0, v1);
                v1 = sll(v0, 2);
                v0 = 0x830000;
                v0 = addiu(v0, 14096);  // &0x833710
                v1 = addu(v0, v1);
                s7 = addiu(v1, 28);
                sw(s1, v1, 28);
                lw(v0, sp, 0xBC);
                sw(v0, s5, 0);
                lw(s1, v1, 56);
                fp = addiu(v1, 0x28);
                lw(v0, v1, 40);
                sw(v0, sp, 0xBC);
                a0 = 0;
                a1 = 0x10000;
                a2 = 0;
                jal(ctx, 0x10D48Cu, gen::fn_sceSifAllocSysMemory_0050b690);
                s2 = v0;
                if (s2 == 0) {
                    // 0x0010d4a0
                    charge(ctx, 5);
                    a0 = 0x5D0000;
                    a0 = addiu(a0, 21448);  // "h_sndcom.c"
                    a1 = 479;
                    jal(ctx, 0x10D4ACu, gen::fn_sub_19D3F0_0019d3f0);
                }
                // 0x0010d4b4
                charge(ctx, 4);
                v0 = addiu(s0, 36);
                sq(v0, sp, 0xA0);
                lw(s0, s0, 36);
                lw(s3, sp, 0xBC);
                for (;;) {
                    // 0x0010d4c4
                    charge(ctx, 5);
                    at = 0x10000;
                    at = at | 0x1;
                    at = slt(s3, at);
                    if (at != 0) {
                        // 0x0010d4f0
                        charge(ctx, 5);
                        sw(s3, sp, 0xBC);
                        v1 = addiu(s3, 127);
                        v0 = sra(v1, 7);
                        if (i64(v1) < 0) {
                            // 0x0010d504
                            charge(ctx, 2);
                            v0 = addiu(v1, 127);
                            v0 = sra(v0, 7);
                        }
                        // 0x0010d50c
                        charge(ctx, 3);
                        v0 = sll(v0, 7);
                        sw(v0, sp, 0xBC);
                        s3 = 0;
                    } else {
                        // 0x0010d4d8
                        charge(ctx, 6);
                        v0 = 0x10000;
                        sw(v0, sp, 0xBC);
                        v0 = addiu(s3, -32768);
                        s3 = addiu(v0, -32768);
                    }
                    // 0x0010d518
                    charge(ctx, 16);
                    a0 = s2;
                    a1 = s1;
                    lw(a2, sp, 0xBC);
                    jal(ctx, 0x10D524u, gen::fn_H_Sndcom_CopyToIop_0010cce0);
                    a0 = 1;
                    a1 = s2;
                    a2 = s0;
                    lw(a3, sp, 0xBC);
                    jal(ctx, 0x10D53Cu, gen::fn_sceSkSsSOUND_Send_0051dbc0);
                    lw(v0, sp, 0xBC);
                    s1 = addu(s1, v0);
                    s0 = addu(s0, v0);
                    if (s3 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0010d558
                charge(ctx, 22);
                a0 = s2;
                jal(ctx, 0x10D55Cu, gen::fn_sceSifFreeSysMemory_0050b710);
                v1 = dsll32(s4, 16);
                v1 = dsra32(v1, 16);
                v0 = sll(v1, 4);
                v0 = addu(v0, v1);
                v1 = sll(v0, 2);
                v0 = 0x830000;
                v0 = addiu(v0, 14096);  // &0x833710
                v0 = addu(v0, v1);
                lw(s0, v0, 60);
                s1 = addiu(v0, 48);
                lw(a1, v0, 48);
                sw(a1, sp, 0xBC);
                a0 = 0;
                a2 = 0;
                jal(ctx, 0x10D59Cu, gen::fn_sceSifAllocSysMemory_0050b690);
                s2 = v0;
                if (s2 == 0) {
                    // 0x0010d5b0
                    charge(ctx, 5);
                    a0 = 0x5D0000;
                    a0 = addiu(a0, 21448);  // "h_sndcom.c"
                    a1 = 507;
                    jal(ctx, 0x10D5BCu, gen::fn_sub_19D3F0_0019d3f0);
                }
                // 0x0010d5c4
                charge(ctx, 51);
                a0 = s2;
                a1 = s0;
                lw(a2, sp, 0xBC);
                jal(ctx, 0x10D5D0u, gen::fn_H_Sndcom_CopyToIop_0010cce0);
                v1 = dsll32(s4, 16);
                v1 = dsra32(v1, 16);
                v0 = sll(v1, 4);
                v0 = addu(v0, v1);
                v1 = sll(v0, 2);
                v0 = 0x830000;
                v0 = addiu(v0, 14096);  // &0x833710
                s0 = addu(v0, v1);
                s6 = addiu(s0, 44);
                sw(s2, s0, 44);
                s2 = addiu(s0, 12);
                a0 = 3;
                a1 = si(-1);
                lw(a2, s7, 0);
                lw(a3, s5, 0);
                lq(v0, sp, 0xA0);
                lw(t0, v0, 0);
                lw(t1, fp, 0x0);
                jal(ctx, 0x10D620u, gen::fn_sceSkSsHSYNTH_Bind_0051dc70);
                sw(v0, s2, 0);
                s3 = addiu(s0, 16);
                a0 = 5;
                a1 = si(-1);
                a2 = v0;
                a3 = 0;
                jal(ctx, 0x10D640u, gen::fn_sceSkSsHSYNTH_Bind_0051dc70);
                sw(v0, s3, 0);
                s2 = addiu(s0, 20);
                a0 = 0;
                a1 = si(-1);
                lw(a2, s6, 0);
                lw(a3, s1, 0);
                jal(ctx, 0x10D660u, gen::fn_sceSkSsSESQ_Bind_0051ddf0);
                sw(v0, s2, 0);
                a0 = 5;
                lw(a1, s3, 0);
                a2 = v0;
                jal(ctx, 0x10D678u, gen::fn_sceSkSsSESQ_Bind_0051ddf0);
                sw(v0, s0, 64);
                v1 = 1;
                sw(v1, s0, 24);
                sh(v1, s0, 0);
                break;
            case 0x10D690u:  // table[1]
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, a0.u());
                return;
            }
        }
        // 0x0010d690
        charge(ctx, 3);
        v1 = addiu(s4, 1);
        s4 = dsll32(v1, 16);
        s4 = dsra32(s4, 16);
    }
    // 0x0010d6b0
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

// 0x0010E630 sub_10E630 -- 592 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Copies a3 bytes from a2 to a1 through the scratchpad with the SPR DMA channels (ch9 toSPR, then ch8 fromSPR),
// 16 KiB (1024 quadwords) per round and the rest last, waiting on each channel through the DMAC condition (bc0f).
void sub_10E630(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0010e630
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s0 = srl(a2, 4);
    jal(ctx, 0x10E650u, gen::fn_sub_4D5E90_004d5e90);
    v1 = 0x10010000;
    t2 = si(-1024);
    t1 = 512;
    t0 = 1024;
    a3 = 0x70000000;
    a2 = 257;
    a1 = 256;
    for (;;) {
        // 0x0010e75c
        charge(ctx, 3);
        at = sltiu(s0, 1025);
        if (at != 0) {
            break;
        }
        backedge(ctx);
        // 0x0010e67c
        charge(ctx, 14);
        sw(t2, v1, -8160);
        sw(t1, v1, -8176);
        sw(s1, v1, -11248);
        sw(t0, v1, -11232);
        sw(a3, v1, -11136);
        lw(a0, v1, -8160);
        a0 = a0 | 0x200;
        sw(a0, v1, -8160);
        sw(a2, v1, -11264);
        s1 = addiu(s1, 16384);
        lw(a0, v1, -11264);
        a0 = a0 & 0x100;
        if (a0 != 0) {
            // 0x0010e6b4
            charge(ctx, 3);
            sw(t1, v1, -8160);
            sync(ctx, 0);
            sync(ctx, 16);
            for (;;) {
                // 0x0010e6c0
                charge(ctx, 7);
                if (cop0_cond(ctx)) {
                    break;
                }
                backedge(ctx);
            }
            for (;;) {
                // 0x0010e6dc
                charge(ctx, 7);
                lw(a0, v1, -11264);
                a0 = a0 & 0x100;
                if (a0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x0010e6f8
        charge(ctx, 15);
        sw(t2, v1, -8160);
        sw(a1, v1, -8176);
        sw(s2, v1, -12272);
        sw(t0, v1, -12256);
        sw(a3, v1, -12160);
        lw(a0, v1, -8160);
        a0 = a0 | 0x100;
        sw(a0, v1, -8160);
        sw(a1, v1, -12288);
        s2 = addiu(s2, 16384);
        s0 = addiu(s0, -1024);
        lw(a0, v1, -12288);
        a0 = a0 & 0x100;
        if (a0 != 0) {
            // 0x0010e734
            charge(ctx, 3);
            sw(a1, v1, -8160);
            sync(ctx, 0);
            sync(ctx, 16);
            for (;;) {
                // 0x0010e740
                charge(ctx, 7);
                if (cop0_cond(ctx)) {
                    break;
                }
                backedge(ctx);
            }
        }
    }
    // 0x0010e768
    charge(ctx, 18);
    a0 = si(-1024);
    v1 = 0x10010000;
    sw(a0, v1, -8160);  // 0x1000E020
    a1 = 512;
    sw(a1, v1, -8176);  // 0x1000E010
    sw(s1, v1, -11248);  // 0x1000D410
    sw(s0, v1, -11232);  // 0x1000D420
    a0 = 0x70000000;
    sw(a0, v1, -11136);  // 0x1000D480
    lw(a0, v1, -8160);  // 0x1000E020
    a0 = a0 | 0x200;
    sw(a0, v1, -8160);  // 0x1000E020
    a0 = 257;
    sw(a0, v1, -11264);  // 0x1000D400
    lw(a0, v1, -11264);  // 0x1000D400
    a0 = a0 & 0x100;
    if (a0 != 0) {
        // 0x0010e7b0
        charge(ctx, 3);
        sw(a1, v1, -8160);
        sync(ctx, 0);
        sync(ctx, 16);
        for (;;) {
            // 0x0010e7bc
            charge(ctx, 7);
            if (cop0_cond(ctx)) {
                break;
            }
            backedge(ctx);
        }
        // 0x0010e7d8
        charge(ctx, 1);
        v1 = 0x10010000;
        for (;;) {
            // 0x0010e7dc
            charge(ctx, 7);
            lw(a0, v1, -11264);
            a0 = a0 & 0x100;
            if (a0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0010e7f8
    charge(ctx, 17);
    a0 = si(-1024);
    v1 = 0x10010000;
    sw(a0, v1, -8160);  // 0x1000E020
    a1 = 256;
    sw(a1, v1, -8176);  // 0x1000E010
    sw(s2, v1, -12272);  // 0x1000D010
    sw(s0, v1, -12256);  // 0x1000D020
    a0 = 0x70000000;
    sw(a0, v1, -12160);  // 0x1000D080
    lw(a0, v1, -8160);  // 0x1000E020
    a0 = a0 | 0x100;
    sw(a0, v1, -8160);  // 0x1000E020
    sw(a1, v1, -12288);  // 0x1000D000
    lw(a0, v1, -12288);  // 0x1000D000
    a0 = a0 & 0x100;
    if (a0 != 0) {
        // 0x0010e83c
        charge(ctx, 3);
        sw(a1, v1, -8160);
        sync(ctx, 0);
        sync(ctx, 16);
        for (;;) {
            // 0x0010e848
            charge(ctx, 7);
            if (cop0_cond(ctx)) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0010e864 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00196FE0 kwlnT0OverflowHandler -- 80 bytes; leaf frame (no stack)
// INTC 9 (timer 0) handler: on T0_MODE.OVFF adds 0x10000 to the 64-bit tick count at gp-0x4C58 and acknowledges.
void kwlnT0OverflowHandler(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x00196fe0
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 9;
    if (a0 == v0) {
        // 0x00196fec
        charge(ctx, 5);
        v0 = 0x10000000;
        lw(v1, v0, 16);  // 0x10000010
        v1 = v1 & 0x800;
        if (v1 != 0) {
            // 0x00197000
            charge(ctx, 7);
            lw(v1, v0, 16);
            v1 = v1 | 0x800;
            sw(v1, v0, 16);
            ld(v1, gp, -19544);  // g_kwlnT0Overflow64
            v0 = 0x10000;
            v0 = v1 + v0;
            sd(v0, gp, -19544);  // g_kwlnT0Overflow64
        }
    }
    // 0x0019701c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    sync(ctx, 0);
    ei(ctx);
    v0 = 0;
}

// 0x00197030 kwlnInitPS2Systems -- 796 bytes; frame 0x50: ra sp+0x0
// IOP bring-up at boot: SIF RPC / IOP heap / CD init, reboot of the IOP with IOPRP310.IMG (retried), SyncIop,
// the RPC re-init, the T0 time base and its INTC handler, then the 15 IOP modules (each retried while it fails),
// the pad and memory-card init, and the main thread id saved to gp-0x4C28.
void kwlnInitPS2Systems(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00197030
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x19703Cu, gen::fn_sceSifInitRpc_005068a8);
    jal(ctx, 0x197044u, gen::fn_sceSifInitIopHeap_0050b598);
    a0 = 0;
    jal(ctx, 0x197050u, gen::fn_sceCdInit_00510460);
    a0 = 2;
    jal(ctx, 0x19705Cu, gen::fn_sceCdMmode_00511040);
    a0 = addiu(sp, 0x10);
    a1 = 0x680000;
    a1 = addiu(a1, -31472);  // "cdrom0:\\LIB31\\%s;1"
    a2 = 0x680000;
    a2 = addiu(a2, -31448);  // "IOPRP310.IMG"
    jal(ctx, 0x197078u, gen::fn_sprintf_00523ac8);
    for (;;) {
        // 0x00197080
        charge(ctx, 8);
        a0 = addiu(sp, 0x10);
        jal(ctx, 0x197084u, gen::fn_sceSifRebootIop_0050ca18);
        v0 = sltu(0, v0);
        v0 = v0 ^ 0x1;
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    for (;;) {
        // 0x001970a0
        charge(ctx, 8);
        jal(ctx, 0x1970A0u, gen::fn_sceSifSyncIop_0050c9c8);
        v0 = sltu(0, v0);
        v0 = v0 ^ 0x1;
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x001970c0
    charge(ctx, 30);
    a0 = 0;
    jal(ctx, 0x1970C4u, gen::fn_sceSifInitRpc_005068a8);
    jal(ctx, 0x1970CCu, gen::fn_sceSifInitIopHeap_0050b598);
    a0 = 0;
    jal(ctx, 0x1970D8u, gen::fn_sceCdInit_00510460);
    a0 = 2;
    jal(ctx, 0x1970E4u, gen::fn_sceCdMmode_00511040);
    a0 = 9;
    a1 = 0x190000;
    a1 = addiu(a1, 28640);  // &kwlnT0OverflowHandler
    a2 = 0;
    jal(ctx, 0x1970FCu, gen::fn__sceAddIntcHandler_00502e40);
    sd(zero, gp, -19544);  // g_kwlnT0Overflow64
    v0 = 0x10000000;
    sw(zero, v0, 0);  // 0x10000000
    sw(zero, v0, 32);  // 0x10000020
    sw(zero, v0, 48);  // 0x10000030
    v1 = 641;
    sw(v1, v0, 16);  // 0x10000010
    sw(zero, v0, 2048);  // 0x10000800
    a0 = 9;
    jal(ctx, 0x197128u, gen::fn_EnableIntc_00503ca8);
    sw(zero, gp, -19432);  // g_kwlnFrameCounterB
    sw(zero, gp, -19428);  // g_kwlnFrameCounterA
    for (;;) {
        // 0x00197138
        charge(ctx, 8);
        a0 = 0x680000;
        a0 = addiu(a0, -31424);  // "cdrom0:\\LIB31\\SIO2MAN.IRX;1"
        a1 = 0;
        a2 = 0;
        jal(ctx, 0x197148u, gen::fn_sceSifLoadModule_0050c4e8);
        if (i64(v0) >= 0) {
            break;
        }
        backedge(ctx);
    }
    for (;;) {
        // 0x00197158
        charge(ctx, 8);
        a0 = 0x680000;
        a0 = addiu(a0, -31392);  // "cdrom0:\\LIB31\\SIO2D.IRX;1"
        a1 = 0;
        a2 = 0;
        jal(ctx, 0x197168u, gen::fn_sceSifLoadModule_0050c4e8);
        if (i64(v0) >= 0) {
            break;
        }
        backedge(ctx);
    }
    for (;;) {
        // 0x00197178
        charge(ctx, 8);
        a0 = 0x680000;
        a0 = addiu(a0, -31360);  // "cdrom0:\\LIB31\\PADMAN.IRX;1"
        a1 = 0;
        a2 = 0;
        jal(ctx, 0x197188u, gen::fn_sceSifLoadModule_0050c4e8);
        if (i64(v0) >= 0) {
            break;
        }
        backedge(ctx);
    }
    for (;;) {
        // 0x00197198
        charge(ctx, 8);
        a0 = 0x680000;
        a0 = addiu(a0, -31328);  // "cdrom0:\\LIB31\\DBCMAN.IRX;1"
        a1 = 0;
        a2 = 0;
        jal(ctx, 0x1971A8u, gen::fn_sceSifLoadModule_0050c4e8);
        if (i64(v0) >= 0) {
            break;
        }
        backedge(ctx);
    }
    for (;;) {
        // 0x001971b8
        charge(ctx, 8);
        a0 = 0x680000;
        a0 = addiu(a0, -31296);  // "cdrom0:\\LIB31\\MC2_S1.IRX;1"
        a1 = 0;
        a2 = 0;
        jal(ctx, 0x1971C8u, gen::fn_sceSifLoadModule_0050c4e8);
        if (i64(v0) >= 0) {
            break;
        }
        backedge(ctx);
    }
    for (;;) {
        // 0x001971d8
        charge(ctx, 8);
        a0 = 0x680000;
        a0 = addiu(a0, -31264);  // "cdrom0:\\LIB31\\LIBSD.IRX;1"
        a1 = 0;
        a2 = 0;
        jal(ctx, 0x1971E8u, gen::fn_sceSifLoadModule_0050c4e8);
        if (i64(v0) >= 0) {
            break;
        }
        backedge(ctx);
    }
    for (;;) {
        // 0x001971f8
        charge(ctx, 9);
        a0 = 0x680000;
        a0 = addiu(a0, -31232);  // "cdrom0:\\LIB31\\CRI_ADXI.IRX;1"
        a1 = 20;
        a2 = 0x680000;
        a2 = addiu(a2, -31200);  // "sdinit=0 spucore=1"
        jal(ctx, 0x19720Cu, gen::fn_sceSifLoadModule_0050c4e8);
        if (i64(v0) >= 0) {
            break;
        }
        backedge(ctx);
    }
    for (;;) {
        // 0x0019721c
        charge(ctx, 8);
        a0 = 0x680000;
        a0 = addiu(a0, -31168);  // "cdrom0:\\LIB31\\SDRDRV.IRX;1"
        a1 = 0;
        a2 = 0;
        jal(ctx, 0x19722Cu, gen::fn_sceSifLoadModule_0050c4e8);
        if (i64(v0) >= 0) {
            break;
        }
        backedge(ctx);
    }
    for (;;) {
        // 0x0019723c
        charge(ctx, 8);
        a0 = 0x680000;
        a0 = addiu(a0, -31136);  // "cdrom0:\\LIB31\\MODHSYN.IRX;1"
        a1 = 0;
        a2 = 0;
        jal(ctx, 0x19724Cu, gen::fn_sceSifLoadModule_0050c4e8);
        if (i64(v0) >= 0) {
            break;
        }
        backedge(ctx);
    }
    for (;;) {
        // 0x0019725c
        charge(ctx, 8);
        a0 = 0x680000;
        a0 = addiu(a0, -31104);  // "cdrom0:\\LIB31\\MODMSIN.IRX;1"
        a1 = 0;
        a2 = 0;
        jal(ctx, 0x19726Cu, gen::fn_sceSifLoadModule_0050c4e8);
        if (i64(v0) >= 0) {
            break;
        }
        backedge(ctx);
    }
    for (;;) {
        // 0x0019727c
        charge(ctx, 8);
        a0 = 0x680000;
        a0 = addiu(a0, -31072);  // "cdrom0:\\LIB31\\MODSESQ.IRX;1"
        a1 = 0;
        a2 = 0;
        jal(ctx, 0x19728Cu, gen::fn_sceSifLoadModule_0050c4e8);
        if (i64(v0) >= 0) {
            break;
        }
        backedge(ctx);
    }
    for (;;) {
        // 0x0019729c
        charge(ctx, 8);
        a0 = 0x680000;
        a0 = addiu(a0, -31040);  // "cdrom0:\\LIB31\\SKSOUND.IRX;1"
        a1 = 0;
        a2 = 0;
        jal(ctx, 0x1972ACu, gen::fn_sceSifLoadModule_0050c4e8);
        if (i64(v0) >= 0) {
            break;
        }
        backedge(ctx);
    }
    for (;;) {
        // 0x001972bc
        charge(ctx, 8);
        a0 = 0x680000;
        a0 = addiu(a0, -31008);  // "cdrom0:\\LIB31\\SKHSYNTH.IRX;1"
        a1 = 0;
        a2 = 0;
        jal(ctx, 0x1972CCu, gen::fn_sceSifLoadModule_0050c4e8);
        if (i64(v0) >= 0) {
            break;
        }
        backedge(ctx);
    }
    for (;;) {
        // 0x001972dc
        charge(ctx, 8);
        a0 = 0x680000;
        a0 = addiu(a0, -31008);  // "cdrom0:\\LIB31\\SKHSYNTH.IRX;1"
        a1 = 0;
        a2 = 0;
        jal(ctx, 0x1972ECu, gen::fn_sceSifLoadModule_0050c4e8);
        if (i64(v0) >= 0) {
            break;
        }
        backedge(ctx);
    }
    for (;;) {
        // 0x001972fc
        charge(ctx, 9);
        a0 = 0x680000;
        a0 = addiu(a0, -30976);  // "cdrom0:\\LIB31\\SKSESQ.IRX;1"
        a1 = 24;
        a2 = 0x680000;
        a2 = addiu(a2, -30944);  // "maxtrack=16"
        jal(ctx, 0x197310u, gen::fn_sceSifLoadModule_0050c4e8);
        if (i64(v0) >= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00197320
    charge(ctx, 11);
    jal(ctx, 0x197320u, gen::fn_H_Pad_Init_00103000);
    jal(ctx, 0x197328u, gen::fn_H_Memcard_Init_0018f100);
    jal(ctx, 0x197330u, gen::fn__sceGetThreadId_00503050);
    sw(v0, gp, -19496);  // g_kwlnMainThreadId
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00197FE0 kwlnGsSyncVCallback -- 44 bytes; frame 0x10: ra sp+0x0
// sceGsSyncVCallback handler: runs the ADX vsync work (sub_540EA8) and returns from the interrupt.
void kwlnGsSyncVCallback(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00197fe0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x197FE8u, gen::fn_sub_540EA8_00540ea8);
    sync(ctx, 0);
    ei(ctx);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00198010 kwlnInitMain -- 912 bytes; frame 0x10: ra sp+0x0
// Boot-time init of the CD layer, sound and ADX: the GS vsync callback, ROFS setup and the three CVM volumes.
void kwlnInitMain(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x00198010
    enter(ctx, 74);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x198018u, gen::fn_H_Cdvd_InitCd_00100800);
    jal(ctx, 0x198020u, gen::fn_H_Cdvd_InitRtFS_00101c70);
    jal(ctx, 0x198028u, gen::fn_sub_177D40_00177d40);
    jal(ctx, 0x198030u, gen::fn_sub_119A20_00119a20);
    jal(ctx, 0x198038u, gen::fn_H_Sndcom_Init_0010cac0);
    jal(ctx, 0x198040u, gen::fn_sub_108740_00108740);
    a0 = 0x840000;
    a0 = addiu(a0, 32528);  // &0x847F10
    a1 = 0;
    a2 = 20;
    jal(ctx, 0x198058u, gen::fn_memset_00521408);
    v1 = addiu(gp, -27596);  // &0x7CC124
    v0 = 0x840000;
    sw(v1, v0, 32528);  // 0x847F10
    v0 = 0x840000;
    sw(zero, v0, 32532);  // 0x847F14
    a0 = 0x840000;
    a0 = addiu(a0, 32528);  // &0x847F10
    jal(ctx, 0x19807Cu, gen::fn_ADXPS2_SetupDvdFs_00547668);
    a0 = 0;
    jal(ctx, 0x198088u, gen::fn_ADXM_SetupThrd_00540588);
    a0 = 5;
    a1 = a0;
    jal(ctx, 0x198098u, gen::fn_sub_5417E0_005417e0);
    jal(ctx, 0x1980A0u, gen::fn_sub_53EA90_0053ea90);
    jal(ctx, 0x1980A8u, gen::fn_sub_54CFE8_0054cfe8);
    a0 = 0x190000;
    a0 = addiu(a0, 32688);  // &kwlnAdxErrorCallback
    a1 = 0;
    jal(ctx, 0x1980BCu, gen::fn_sub_540570_00540570);
    a0 = 0x190000;
    a0 = addiu(a0, 32736);  // &kwlnGsSyncVCallback
    jal(ctx, 0x1980CCu, gen::fn_sceGsSyncVCallback_004fa4b8);
    v1 = 6;
    v0 = 0x840000;
    sw(v1, v0, 32512);  // 0x847F00
    v1 = 3;
    v0 = 0x840000;
    sw(v1, v0, 32516);  // 0x847F04
    v1 = 836;
    v0 = 0x840000;
    sw(v1, v0, 32520);  // 0x847F08
    v1 = 0x840000;
    v1 = addiu(v1, 32592);  // &0x847F50
    v0 = 0x840000;
    sw(v1, v0, 32524);  // 0x847F0C
    a0 = 0x840000;
    a0 = addiu(a0, 32512);  // &0x847F00
    jal(ctx, 0x198110u, gen::fn_ROFS_Init_00567820);
    a0 = 0;
    a1 = 0;
    a2 = 1;
    jal(ctx, 0x198124u, gen::fn_sub_569F60_00569f60);
    a0 = 0;
    jal(ctx, 0x198130u, gen::fn_ADXF_SetupRofs_0053b220);
    for (;;) {
        // 0x00198138
        charge(ctx, 8);
        a0 = addiu(gp, -27592);  // "VOL"
        a1 = 0x680000;
        a1 = addiu(a1, -30824);  // "CDV:data.cvm"
        a2 = 0;
        jal(ctx, 0x198148u, gen::fn_ADXF_AddRofsVol_0053b2c0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    for (;;) {
        // 0x00198158
        charge(ctx, 8);
        a0 = addiu(gp, -27588);  // "BGM"
        a1 = 0x680000;
        a1 = addiu(a1, -30808);  // "CDV:bgm.cvm"
        a2 = 0;
        jal(ctx, 0x198168u, gen::fn_ADXF_AddRofsVol_0053b2c0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    for (;;) {
        // 0x00198178
        charge(ctx, 8);
        a0 = addiu(gp, -27584);  // "BTL"
        a1 = 0x680000;
        a1 = addiu(a1, -30792);  // "CDV:btl.cvm"
        a2 = 0;
        jal(ctx, 0x198188u, gen::fn_ADXF_AddRofsVol_0053b2c0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00198198
    charge(ctx, 130);
    a0 = addiu(gp, -27592);  // "VOL"
    a1 = 0x5E0000;
    a1 = addiu(a1, 20816);  // &0x5E5150
    jal(ctx, 0x1981A4u, gen::fn_ROFS_SetDir_00566b08);
    a0 = addiu(gp, -27588);  // "BGM"
    a1 = 0x640000;
    a1 = addiu(a1, 6368);  // &0x6418E0
    jal(ctx, 0x1981B8u, gen::fn_ROFS_SetDir_00566b08);
    a0 = addiu(gp, -27584);  // "BTL"
    a1 = 0x640000;
    a1 = addiu(a1, 17200);  // &0x644330
    jal(ctx, 0x1981CCu, gen::fn_ROFS_SetDir_00566b08);
    a0 = addiu(gp, -27592);  // "VOL"
    jal(ctx, 0x1981D8u, gen::fn_sub_53B4F8_0053b4f8);
    a0 = 0x840000;
    a0 = addiu(a0, 32560);  // &0x847F30
    a1 = 0;
    a2 = 32;
    jal(ctx, 0x1981F0u, gen::fn_memset_00521408);
    lwc1(f0, gp, -32708);  // 0x7CAD2C
    v0 = 0x840000;
    swc1(f0, v0, 32560);  // 0x847F30
    v1 = 1;
    v0 = 0x840000;
    sw(v1, v0, 32564);  // 0x847F34
    v0 = 0x840000;
    sw(v1, v0, 32568);  // 0x847F38
    v0 = 0x840000;
    sw(zero, v0, 32572);  // 0x847F3C
    a0 = 0x840000;
    a0 = addiu(a0, 32560);  // &0x847F30
    jal(ctx, 0x198228u, gen::fn_sub_57F768_0057f768);
    a0 = 0x190000;
    a0 = addiu(a0, 32640);  // &sub_197F80
    a1 = 0;
    jal(ctx, 0x19823Cu, gen::fn_sub_540570_00540570);
    a0 = lui(0x8000);
    a1 = 1;
    jal(ctx, 0x19824Cu, gen::fn_kwlnSetFlags_00198610);
    jal(ctx, 0x198254u, gen::fn_sub_27C8F0_0027c8f0);
    jal(ctx, 0x19825Cu, gen::fn_sub_31B470_0031b470);
    lw(a0, gp, -19504);  // g_kwlnMainCamera
    jal(ctx, 0x198268u, gen::fn_sub_1042E0_001042e0);
    jal(ctx, 0x198270u, gen::fn_sub_105800_00105800);
    jal(ctx, 0x198278u, gen::fn_sub_196770_00196770);
    a0 = 1;
    jal(ctx, 0x198284u, gen::fn_sub_4D8300_004d8300);
    a0 = 1;
    jal(ctx, 0x198290u, gen::fn_sub_4D8310_004d8310);
    jal(ctx, 0x198298u, gen::fn_H_ResrcMan_Init_0010c050);
    jal(ctx, 0x1982A0u, gen::fn_effMng_CreateEffectProgramTasks_00322010);
    jal(ctx, 0x1982A8u, gen::fn_btlTableInit_0027e180);
    jal(ctx, 0x1982B0u, gen::fn_sub_3BD130_003bd130);
    jal(ctx, 0x1982B8u, gen::fn_frFontSystemStart_003b4ee0);
    a0 = 0;
    jal(ctx, 0x1982C4u, gen::fn_sub_396BF0_00396bf0);
    jal(ctx, 0x1982CCu, gen::fn_sub_3BD280_003bd280);
    jal(ctx, 0x1982D4u, gen::fn_sub_1D4560_001d4560);
    jal(ctx, 0x1982DCu, gen::fn_sub_1DCA10_001dca10);
    jal(ctx, 0x1982E4u, gen::fn_sub_1B7D00_001b7d00);
    jal(ctx, 0x1982ECu, gen::fn_K_Data_LoadFldMainScript_001b7b10);
    a0 = 0;
    jal(ctx, 0x1982F8u, gen::fn_sub_1B7C40_001b7c40);
    jal(ctx, 0x198300u, gen::fn_sub_1D7260_001d7260);
    jal(ctx, 0x198308u, gen::fn_sub_1B7BB0_001b7bb0);
    jal(ctx, 0x198310u, gen::fn_sub_1B7DC0_001b7dc0);
    jal(ctx, 0x198318u, gen::fn_sub_1D4290_001d4290);
    jal(ctx, 0x198320u, gen::fn_sub_1B8B40_001b8b40);
    jal(ctx, 0x198328u, gen::fn_sub_1B8C40_001b8c40);
    jal(ctx, 0x198330u, gen::fn_sub_107020_00107020);
    jal(ctx, 0x198338u, gen::fn_sprFontInit_00111f50);
    jal(ctx, 0x198340u, gen::fn_sub_18E4A0_0018e4a0);
    jal(ctx, 0x198348u, gen::fn_sub_18BC80_0018bc80);
    jal(ctx, 0x198350u, gen::fn_effAfter_CreateAfterEffectRenderTask_001eef20);
    a0 = 63;
    a1 = 0;
    jal(ctx, 0x198360u, gen::fn_sub_16F3E0_0016f3e0);
    jal(ctx, 0x198368u, gen::fn_sub_17C280_0017c280);
    jal(ctx, 0x198370u, gen::fn_sub_16C1D0_0016c1d0);
    jal(ctx, 0x198378u, gen::fn_sub_20C8D0_0020c8d0);
    jal(ctx, 0x198380u, gen::fn_sub_4302B0_004302b0);
    jal(ctx, 0x198388u, gen::fn_sub_267260_00267260);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001983A0 kwlnUpdate -- 284 bytes; frame 0x10: ra sp+0x0
// One game frame: the first call starts T0 (count 0, mode 0x83 = H-blank clock); the others take the frame-start
// T0 count, update the CD layer, sound and pads, run the task tree and step the frame counters.
void kwlnUpdate(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001983a0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, -27580);  // g_kwlnFirstFrame
    if (v0 != 0) {
        // 0x001983b4
        charge(ctx, 10);
        v0 = 0x960000;
        v0 = addiu(v0, 112);  // &0x960070
        sw(v0, gp, -19500);  // 0x7CE0C4
        sw(zero, gp, -27580);  // g_kwlnFirstFrame
        v0 = 0x10000000;
        sw(zero, v0, 0);  // 0x10000000
        v1 = 131;
        sw(v1, v0, 16);  // 0x10000010
        goto L_00198490;
    }
    // 0x001983dc
    charge(ctx, 21);
    jal(ctx, 0x1983DCu, gen::fn_Y_Misc_GetT0Count_004241d0);
    sw(v0, gp, -19444);  // g_kwlnFrameStartT0
    jal(ctx, 0x1983E8u, gen::fn_H_Cdvd_Update_00100980);
    jal(ctx, 0x1983F0u, gen::fn_H_Sndcom_Update_0010cdd0);
    jal(ctx, 0x1983F8u, gen::fn_sub_108BC0_00108bc0);
    jal(ctx, 0x198400u, gen::fn_sub_103580_00103580);
    lw(v1, gp, -19408);  // gKwlnFlags
    v0 = lui(0xBFFF);
    v0 = v0 | 0xFFFF;
    v0 = v1 & v0;
    sw(v0, gp, -19408);  // gKwlnFlags
    v0 = 0x7E0000;
    lhu(v1, v0, 2546);  // 0x7E09F2
    v0 = v1 & 0x4;
    if (v0 != 0) {
        // 0x00198430
        charge(ctx, 3);
        v0 = v1 & 0x100;
        if (v0 == 0) {
            goto L_00198460;
        }
        // 0x0019843c
        charge(ctx, 5);
        v0 = 0x7E0000;
        lhu(v0, v0, 2548);  // 0x7E09F4
        v0 = v0 & 0x800;
        if (v0 == 0) {
            goto L_00198460;
        }
        // 0x00198450
        charge(ctx, 4);
        jal(ctx, 0x198450u, gen::fn_sub_1E7720_001e7720);
    L_0019847c:
        charge(ctx, 5);
        jal(ctx, 0x19847Cu, gen::fn_sub_10BF70_0010bf70);
        a0 = 1;
        jal(ctx, 0x198488u, gen::fn_sub_4C7CF0_004c7cf0);
    L_00198490:
        charge(ctx, 7);
        lw(v0, gp, -19428);  // g_kwlnFrameCounterA
        v0 = addiu(v0, 1);
        sw(v0, gp, -19428);  // g_kwlnFrameCounterA
        lw(v0, gp, -19432);  // g_kwlnFrameCounterB
        v0 = addiu(v0, 1);
        sw(v0, gp, -19432);  // g_kwlnFrameCounterB
        v0 = 1;
        // 0x001984ac (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
L_00198460:
    charge(ctx, 4);
    jal(ctx, 0x198460u, gen::fn_kwlnTaskMain_001949e0);
    if (v0 != 0) {
        goto L_0019847c;
    }
    // 0x00198470
    charge(ctx, 3);
    v0 = 0;
    // 0x001984ac (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001984C0 kwlnMain -- 128 bytes; frame 0x10: ra sp+0x0
// The game's main loop: PS2 / renderer / main init, then for ever: create the root task, reset the game data,
// seed both RW random generators from T0 and run kwlnUpdate while the root task exists.
void kwlnMain(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001984c0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x1984C8u, gen::fn_kwlnInitPS2Systems_00197030);
    jal(ctx, 0x1984D0u, gen::fn_kwlnInitRenderer_00197350);
    jal(ctx, 0x1984D8u, gen::fn_kwlnInitMain_00198010);
    for (;;) {
        // 0x001984e0
        charge(ctx, 15);
        jal(ctx, 0x1984E0u, gen::fn_kwlnRootCreateTask_00198940);
        sw(v0, gp, -19488);  // g_kwlnRootTask
        jal(ctx, 0x1984ECu, gen::fn_sub_195DE0_00195de0);
        v0 = 0x10000000;
        lw(a0, v0, 0);  // 0x10000000
        jal(ctx, 0x1984FCu, gen::fn_RpRandomSeed_00488dd0);
        v0 = 0x10000000;
        lw(a0, v0, 0);  // 0x10000000
        jal(ctx, 0x19850Cu, gen::fn_RpRandomSeedMT_00488c70);
        for (;;) {
            // 0x00198524
            charge(ctx, 5);
            lw(a0, gp, -19488);  // g_kwlnRootTask
            jal(ctx, 0x198528u, gen::fn_kwlnTaskExists_00195460);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0019851c
            charge(ctx, 2);
            jal(ctx, 0x19851Cu, gen::fn_kwlnUpdate_001983a0);
        }
        // 0x00198538
        charge(ctx, 2);
        backedge(ctx);
    }
}

// 0x00199140 kwlnRootUpdateShowRasterTask -- 540 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// The last draw task of a frame: RwCameraShowRaster, then the frame's T0 delta and the CPU load percentage
// (delta * 100 / 520 H-lines) and T0 restarted from 0.
void kwlnRootUpdateShowRasterTask(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x00199140
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x199154u, gen::fn_sub_4C4D20_004c4d20);
    sw(v0, gp, -19424);  // 0x7CE110
    lw(v1, gp, -19448);  // 0x7CE0F8
    v0 = 1;
    if (v1 == v0) {
        // 0x00199170
        charge(ctx, 18);
        jal(ctx, 0x199170u, gen::fn_sub_198590_00198590);
        lw(s1, v0, 96);
        lw(s0, s1, 4);
        lw(v1, s1, 12);
        lw(v0, s1, 16);
        mult(v1, v1, v0);
        lw(v0, s1, 20);
        v0 = sra(v0, 3);
        mult(a0, v0, v1);
        a1 = 0x40000;
        v0 = 0x960000;
        lw(v0, v0, 376);  // 0x960178
        jalr(ctx, 0x1991A4u, v0.u());
        s2 = v0;
        if (s2 != 0) {
            // 0x001991b8
            charge(ctx, 8);
            sw(s2, s1, 4);
            a0 = s1;
            a1 = 0;
            a2 = 2;
            jal(ctx, 0x1991C8u, gen::fn_sub_4CE200_004ce200);
            if (v0 == 0) {
                // 0x001991d8
                charge(ctx, 6);
                sw(s0, s1, 4);
                a0 = s2;
                v0 = 0x960000;
                lw(v0, v0, 380);  // 0x96017C
                jalr(ctx, 0x1991E8u, v0.u());
            }
            // 0x001991f0
            charge(ctx, 16);
            lw(a0, gp, -19436);  // 0x7CE104
            jal(ctx, 0x1991F4u, gen::fn_sub_4CBF20_004cbf20);
            lw(a0, gp, -19436);  // 0x7CE104
            a1 = s1;
            jal(ctx, 0x199204u, gen::fn_sub_4CDC70_004cdc70);
            a0 = s1;
            jal(ctx, 0x199210u, gen::fn_sub_4CDE00_004cde00);
            sw(s0, s1, 4);
            a0 = s2;
            v0 = 0x960000;
            lw(v0, v0, 380);  // 0x96017C
            jalr(ctx, 0x199228u, v0.u());
        }
        // 0x00199230
        charge(ctx, 1);
        sw(zero, gp, -19448);  // 0x7CE0F8
    }
    // 0x00199234
    charge(ctx, 14);
    jal(ctx, 0x199234u, gen::fn_sub_198590_00198590);
    a0 = v0;
    a1 = 0;
    a2 = 0;
    jal(ctx, 0x199248u, gen::fn_RwCameraShowRaster_004c9ed0);
    jal(ctx, 0x199250u, gen::fn_Y_Misc_GetT0Count_004241d0);
    sw(v0, gp, -19440);  // g_kwlnFrameEndT0
    lw(v1, gp, -19444);  // g_kwlnFrameStartT0
    v1 = subu(v0, v1);
    if (i64(v1) < 0) {
        // 0x00199280
        charge(ctx, 7);
        a0 = srl(v1, 1);
        v1 = v1 & 0x1;
        a0 = a0 | v1;
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0019926c
        charge(ctx, 5);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0019929c
    charge(ctx, 3);
    swc1(f0, gp, -19364);  // g_kwlnFrameDeltaHsync
    if (i64(v0) < 0) {
        // 0x001992bc
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x001992a8
        charge(ctx, 5);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x001992d8
    charge(ctx, 33);
    swc1(f0, gp, -19368);  // g_kwlnFrameEndHsync
    v0 = 0x44020000;
    mtc1(v0, f1);
    lwc1(f0, gp, -19364);  // g_kwlnFrameDeltaHsync
    div_s(f1, f0, f1);
    v0 = 0x42C80000;
    mtc1(v0, f0);
    mul_s(f0, f0, f1);
    swc1(f0, gp, -19360);  // g_kwlnCpuLoadPct
    v0 = 0x10000000;
    sw(zero, v0, 0);  // 0x10000000
    v0 = 1;
    sw(v0, gp, -19392);  // 0x7CE130
    a0 = 0;
    jal(ctx, 0x199314u, gen::fn_sub_4C7CF0_004c7cf0);
    jal(ctx, 0x19931Cu, gen::fn_H_ResrcMan_MaybeResumeThread_0010bff0);
    jal(ctx, 0x199324u, gen::fn_H_ResrcMan_Update_0010c5f0);
    jal(ctx, 0x19932Cu, gen::fn_sub_5810F0_005810f0);
    jal(ctx, 0x199334u, gen::fn_sub_488F30_00488f30);
    v0 = 0;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x004241D0 Y_Misc_GetT0Count -- 16 bytes; leaf frame (no stack)
// Returns T0_COUNT (0x10000000).
void Y_Misc_GetT0Count(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x004241d0
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0x10000000;
    lw(v0, v0, 0);  // 0x10000000
}

// 0x004FB870 _motionComp0 -- 592 bytes; frame 0xB0: fp sp+0x90, s7 sp+0x80, s6 sp+0x70, s5 sp+0x60, s0 sp+0x10, ra sp+0xA0, s4 sp+0x50, s3 sp+0x40, s2 sp+0x30, s1 sp+0x20
// libmpeg: motion compensation of one macroblock: fetches the reference blocks (dmaRefImage) for the vectors.
void _motionComp0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x004fb870
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    sd(fp, sp, 0x90);
    sd(s7, sp, 0x80);
    fp = a2;
    sd(s6, sp, 0x70);
    sd(s5, sp, 0x60);
    sd(s0, sp, 0x10);
    s5 = a3;
    sd(ra, sp, 0xA0);
    s0 = a0;
    sd(s4, sp, 0x50);
    v1 = s5 & 0x1;
    sd(s3, sp, 0x40);
    sd(s2, sp, 0x30);
    sd(s1, sp, 0x20);
    lw(v0, s0, 316);
    sw(v1, sp, 0x0);
    div(a1, v0);
    if (v0 == 0) {
        brk(ctx, 0x4FB8BCu, 0x7u);
    }
    // 0x004fb8c0
    charge(ctx, 7);
    lw(v0, sp, 0x0);
    mfhi(v1);
    mflo(s7);
    s6 = v1;
    a2 = sll(s7, 4);
    a1 = sll(s6, 4);
    if (v0 != 0) {
        // 0x004fb8dc
        charge(ctx, 5);
        lw(a0, s0, 2080);
        s1 = addiu(s0, 1752);
        s2 = addiu(s0, 1748);
        s3 = addiu(s0, 1744);
        s4 = addiu(s0, 1736);
        for (;;) {
            // 0x004fb8f0
            charge(ctx, 7);
            v0 = 0x10000000;
            v0 = v0 | 0xD400;
            lw(v1, v0, 0);  // 0x1000D400
            v1 = srl(v1, 8);
            v1 = v1 & 0x1;
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004fb90c
        charge(ctx, 5);
        v0 = 320;
        mult(v1, a0, v0);
        v0 = addu(v1, s1);
        sw(zero, v0, 0);
        goto L_004fb9b4;
    }
    // 0x004fb920
    charge(ctx, 4);
    v0 = addiu(t0, -1);
    v0 = sltiu(v0, 3);
    a0 = s0;
    if (v0 != 0) {
        // 0x004fb954
        charge(ctx, 9);
        a3 = s5;
        jal(ctx, 0x4FB954u, gen::fn__getAllRefs_004fb168);
        v1 = 0x10000000;
        s1 = addiu(s0, 1752);
        s2 = addiu(s0, 1748);
        s3 = addiu(s0, 1744);
        s4 = addiu(s0, 1736);
        v1 = v1 | 0xD400;
        for (;;) {
            // 0x004fb978
            charge(ctx, 7);
            lw(v0, v1, 0);
            v0 = srl(v0, 8);
            v0 = v0 & 0x1;
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004fb994
        charge(ctx, 8);
        a0 = s0;
        jal(ctx, 0x4FB994u, gen::fn_dmaRefImage_004fdb18);
        lw(v0, s0, 2080);
        v1 = 320;
        a0 = 1;
        mult(a1, v0, v1);
        v0 = addu(a1, s1);
        sw(a0, v0, 0);
    L_004fb9b4:
        charge(ctx, 3);
        v0 = 1;
        if (fp != v0) {
            lw(v0, s0, 2080);
        } else {
            // 0x004fb9c0
            charge(ctx, 3);
            v0 = s5 & 0x2;
            v1 = 320;
            if (v0 == 0) {
                // 0x004fb9e0
                charge(ctx, 1);
                lw(v0, s0, 2080);
                goto L_004fb9e4;
            }
            // 0x004fb9cc
            charge(ctx, 5);
            lw(v0, s0, 2080);
            mult(a0, v0, v1);
            v0 = addu(a0, s2);
            sw(fp, v0, 0);
            goto L_004fb9f4;
        }
    L_004fb9e4:
        charge(ctx, 4);
        v1 = 320;
        mult(a0, v0, v1);
        v0 = addu(a0, s2);
        sw(zero, v0, 0);
    L_004fb9f4:
        charge(ctx, 10);
        lw(v0, s0, 2080);
        a3 = 320;
        lw(a1, sp, 0x0);
        v1 = 3;
        mult(a0, v0, a3);
        v0 = addu(a0, s3);
        sw(a1, v0, 0);
        lw(a0, s0, 388);
        v0 = 2;
        if (a0 != v1) {
            // 0x004fba50
            charge(ctx, 2);
            if (a0 != v0) {
                lw(v0, s0, 480);
            } else {
                // 0x004fba58
                charge(ctx, 1);
                lw(v0, s0, 496);
            }
            // 0x004fba5c
            charge(ctx, 12);
            lw(v1, v0, 16);
            a2 = 384;
            lw(a0, s0, 2080);
            a1 = 320;
            mult(a3, s6, v1);
            lw(v0, v0, 0);
            v1 = addu(a3, s7);
            mult(a3, a0, a1);
            mult(v1, v1, a2);
            a0 = addu(a3, s4);
            v0 = addu(v0, v1);
            sw(v0, a0, 0);
        } else {
            // 0x004fba1c
            charge(ctx, 13);
            lw(a0, s0, 2080);
            a2 = 384;
            lw(a1, s0, 464);
            mult(v1, a0, a3);
            lw(v0, a1, 16);
            a0 = addu(v1, s4);
            lw(v1, a1, 0);
            mult(a1, s6, v0);
            v0 = addu(a1, s7);
            mult(v0, v0, a2);
            v1 = addu(v1, v0);
            sw(v1, a0, 0);
        }
        // 0x004fba8c
        charge(ctx, 1);
        v0 = 1;
    } else {
        // 0x004fb930
        charge(ctx, 9);
        a1 = 0x7C0000;
        a2 = t0;
        a1 = addiu(a1, -10976);  // "Invalid modion type -- ignored(%d)"
        a0 = s0;
        jal(ctx, 0x4FB93Cu, gen::fn__sceMpegError1_005026c0);
        v1 = 1;
        v0 = 0;
        sw(v1, s0, 300);
    }
    // 0x004fba90 (the shared epilogue, written out on this path)
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

// 0x004FBF48 _doMC -- 732 bytes, 2 chunks; frame 0xB0: s4 sp+0x50, ra sp+0xA0, fp sp+0x90, s7 sp+0x80, s6 sp+0x70, s5 sp+0x60, s3 sp+0x40, s2 sp+0x30, s1 sp+0x20, s0 sp+0x10
// libmpeg: runs the motion compensation of the pending macroblocks through the IPU / the work buffers.
void _doMC(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, t9{ctx, 25}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x004fbf48
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    v0 = 320;
    sw(a1, sp, 0x0);
    sd(s4, sp, 0x50);
    mult(a1, a1, v0);
    sd(ra, sp, 0xA0);
    sd(fp, sp, 0x90);
    s4 = a0;
    sd(s7, sp, 0x80);
    sd(s6, sp, 0x70);
    sd(s5, sp, 0x60);
    v0 = addu(s4, a1);
    sd(s3, sp, 0x40);
    sd(s2, sp, 0x30);
    sd(s1, sp, 0x20);
    sd(s0, sp, 0x10);
    lw(v1, v0, 1752);
    v0 = addiu(s4, 1740);
    if (v1 == 0) {
        // 0x004fc02c
        charge(ctx, 4);
        v0 = addiu(s4, 1744);
        fp = addiu(s4, 0x6C8);
        sw(v0, sp, 0x8);
    L_004fc048:
        charge(ctx, 1);
        lw(v1, sp, 0x0);
    } else {
        // 0x004fbf94
        charge(ctx, 5);
        sw(v0, sp, 0x4);
        v0 = addu(v0, a1);
        lw(v1, v0, 0);
        s5 = 0;
        if (i64(v1) <= 0) {
            // 0x004fc03c
            charge(ctx, 3);
            v1 = addiu(s4, 1744);
            fp = addiu(s4, 0x6C8);
            sw(v1, sp, 0x8);
            goto L_004fc048;
        }
        // 0x004fbfa8
        charge(ctx, 6);
        v1 = addiu(s4, 1744);
        s7 = addiu(s4, 1480);
        sw(v1, sp, 0x8);
        s6 = addiu(s4, 1496);
        fp = addiu(s4, 0x6C8);
        lw(v0, sp, 0x0);
        for (;;) {
            // 0x004fbfc0
            charge(ctx, 25);
            s1 = 320;
            s3 = 28;
            s0 = sll(s5, 2);
            mult(s1, v0, s1);
            mult1(s3, s5, s3);
            s5 = addiu(s5, 1);
            s0 = addu(s0, s1);
            s2 = addiu(s1, 1440);
            v0 = addu(s7, s0);
            s2 = addu(s4, s2);
            a0 = addiu(s3, 72);
            lw(v1, v0, 0);
            a0 = addu(s2, a0);
            jalr(ctx, 0x4FBFF0u, v1.u());
            s0 = addu(s6, s0);
            s3 = addiu(s3, 184);
            lw(v0, s0, 0);
            a0 = addu(s2, s3);
            jalr(ctx, 0x4FC004u, v0.u());
            lw(v1, sp, 0x4);
            s1 = addu(v1, s1);
            lw(v0, s1, 0);
            v0 = slt(s5, v0);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            lw(v0, sp, 0x0);
            if (!cc) {
                break;
            }
            backedge(ctx);
        }
        // 0x004fc024
        charge(ctx, 2);
        lw(v1, sp, 0x0);
    }
    // 0x004fc04c
    charge(ctx, 7);
    v0 = 320;
    mult(a0, v1, v0);
    lw(v0, sp, 0x8);
    v1 = addu(v0, a0);
    lw(v0, v1, 0);
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = addu(s4, a0);
    if (!cc) {
        // 0x004fc068
        charge(ctx, 3);
        lw(v1, v0, 1756);
        a1 = 0x7C0000;
        if (v1 != 0) {
            // 0x004fc074
            charge(ctx, 3);
            a0 = s4;
            a1 = addiu(a1, -10936);
            jal(ctx, 0x4FC078u, gen::fn__sceMpegError_00502668);
        }
    }
    // 0x004fc080
    charge(ctx, 8);
    lw(v1, sp, 0x0);
    v0 = 320;
    mult(a1, v1, v0);
    lw(v0, sp, 0x8);
    v1 = addu(v0, a1);
    lw(v0, v1, 0);
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = addu(s4, a1);
    if (!cc) {
        // 0x004fc0a0
        charge(ctx, 16);
        v0 = addu(fp, a1);
        v1 = addu(s4, a1);
        lw(a0, v0, 0);
        lw(a1, v1, 1444);
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
        goto L_004fda58;
    }
    // 0x004fc0e0
    charge(ctx, 3);
    lw(v1, v0, 1756);
    v0 = addu(fp, a1);
    if (v1 == 0) {
        // 0x004fc124
        charge(ctx, 16);
        v1 = addu(s4, a1);
        lw(a1, s4, 2096);
        lw(a0, v0, 0);
        lw(a2, v1, 1444);
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
        gen::fn__copyAddRefImage_004fd968(ctx);  // tail call
        return;
    }
    // 0x004fc0ec
    charge(ctx, 14);
    ld(ra, sp, 0xA0);
    lw(a1, s4, 2096);
    lw(a0, v0, 0);
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
L_004fda58:
    charge(ctx, 4);
    v0 = 24;
    t2 = 0x500000;
    t2 = addiu(t2, -9472);  // &0x4FDB00
    lq(v1, t2, 0);  // 0x4FDB00
    for (;;) {
        // 0x004fda68
        charge(ctx, 37);
        lq(t0, a1, 0);
        v0 = addiu(v0, -4);
        t9 = a1;
        a1 = addiu(a1, 128);
        lq(t1, t9, 16);
        lq(t2, t9, 32);
        lq(t3, t9, 48);
        lq(t4, t9, 64);
        lq(t5, t9, 80);
        lq(t6, t9, 96);
        lq(t7, t9, 112);
        pminh(t0, t0, v1);
        pmaxh(t0, t0, zero);
        pminh(t1, t1, v1);
        pmaxh(t1, t1, zero);
        ppacb(t1, t1, t0);
        pminh(t2, t2, v1);
        pmaxh(t2, t2, zero);
        pminh(t3, t3, v1);
        pmaxh(t3, t3, zero);
        ppacb(t3, t3, t2);
        pminh(t4, t4, v1);
        pmaxh(t4, t4, zero);
        pminh(t5, t5, v1);
        pmaxh(t5, t5, zero);
        ppacb(t5, t5, t4);
        pminh(t6, t6, v1);
        pmaxh(t6, t6, zero);
        pminh(t7, t7, v1);
        pmaxh(t7, t7, zero);
        ppacb(t7, t7, t6);
        sq(t1, a0, 0);
        sq(t3, a0, 16);
        sq(t5, a0, 32);
        sq(t7, a0, 48);
        a0 = addiu(a0, 64);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004fdafc
    charge(ctx, 7);
}

// 0x004FC3A8 _slice0 -- 812 bytes; frame 0xE0: s6 sp+0xC0, s0 sp+0x60, ra sp+0xD0, s5 sp+0xB0, s4 sp+0xA0, s3 sp+0x90, s2 sp+0x80, s1 sp+0x70
// libmpeg: decodes one slice: the macroblock-address increments, each macroblock (_decMB0) and its motion
// compensation, until the next start code; errors go through _sceMpegError.
void _slice0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x004fc3a8
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0xE0);
    sd(s6, sp, 0xC0);
    a2 = addiu(sp, 0x40);
    sd(s0, sp, 0x60);
    s6 = a1;
    s0 = a0;
    sw(zero, sp, 0x40);
    sw(zero, sp, 0x44);
    a3 = addiu(sp, 0x44);
    t0 = sp;
    sd(ra, sp, 0xD0);
    sd(s5, sp, 0xB0);
    sd(s4, sp, 0xA0);
    sd(s3, sp, 0x90);
    sd(s2, sp, 0x80);
    link(ctx, 0x4FC3E4u);  // $ra first: the delay slot below depends on it
    sd(s1, sp, 0x70);
    call(ctx, gen::fn__sceMpegSliceA0_004fea28);
    ld(ra, sp, 0xD0);
    if (v0 == 0) {
        // 0x004fc3f4
        charge(ctx, 1);
        sw(zero, s0, 300);
        for (;;) {
        L_004fc3f8:
            charge(ctx, 4);
            lw(v0, sp, 0x40);
            v0 = slt(v0, s6);
            if (v0 == 0) {
                break;
            }
            lw(v0, s0, 2080);
            // 0x004fc410
            charge(ctx, 12);
            v1 = 320;
            a0 = s0;
            s5 = 1;
            mult(a1, v0, v1);
            v0 = addu(a1, s0);
            link(ctx, 0x4FC424u);  // $ra first: the delay slot below depends on it
            sw(zero, v0, 1756);
            call(ctx, gen::fn__waitIpuIdle_004fd868);
            v0 = 0x10000000;
            v0 = v0 | 0xB020;
            lw(v1, v0, 0);  // 0x1000B020
            v0 = 0x10000000;
            if (v1 != 0) {
                // 0x004fc440
                charge(ctx, 5);
                v0 = v0 | 0x2010;
                lw(v1, v0, 0);
                v1 = v1 & 0x4000;
                v0 = 0x10000000;
                if (v1 == 0) {
                    // 0x004fc454
                    charge(ctx, 9);
                    s4 = 0x10000000;
                    s3 = 0x10000000;
                    s2 = 0x10000000;
                    s1 = 0x10000000;
                    s4 = s4 | 0xB420;
                    s3 = s3 | 0xB400;
                    s2 = s2 | 0xB020;
                    s1 = s1 | 0x2010;
                    for (;;) {
                        // 0x004fc478
                        charge(ctx, 3);
                        lw(v0, s4, 0);
                        if (v0 != 0) {
                            lw(v0, s0, 2168);
                        } else {
                            // 0x004fc484
                            charge(ctx, 4);
                            lw(v0, s3, 0);
                            v0 = v0 & 0x100;
                            if (v0 != 0) {
                                lw(v0, s0, 2168);
                            } else {
                                // 0x004fc494
                                charge(ctx, 3);
                                link(ctx, 0x4FC494u);  // $ra first: the delay slot below depends on it
                                lw(a0, s0, 2152);
                                call(ctx, gen::fn__sceMpegDispatchMpegCbNodata_00500d88);
                                lw(v0, s0, 2168);
                            }
                        }
                        // 0x004fc4a0
                        charge(ctx, 2);
                        if (v0 != 0) {
                            goto L_004fc508;
                        }
                        // 0x004fc4a8
                        charge(ctx, 3);
                        lw(v0, s2, 0);
                        cc = v0 == 0;  // the condition, before the delay slot changes it
                        v0 = 0x10000000;
                        if (cc) {
                            goto L_004fc4c8;
                        }
                        // 0x004fc4b4
                        charge(ctx, 4);
                        lw(v0, s1, 0);
                        v0 = v0 & 0x4000;
                        if (v0 != 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    goto L_004fc4c4;
                }
            L_004fc4c8:
                charge(ctx, 9);
                v1 = 0x10000000;
                v0 = v0 | 0x2020;
                v1 = v1 | 0x2030;
                lw(a1, v0, 0);
                ld(a0, v1, 0);  // 0x10002030
                v0 = dsll32(a0, 0);
                v0 = dsra32(v0, 0);
                sw(v0, s0, 2120);
                if (i64(a0) >= 0) {
                    // 0x004fc518
                    charge(ctx, 1);
                    v0 = 32;
                } else {
                    // 0x004fc4ec
                    charge(ctx, 3);
                    v1 = a1 & 0x1F;
                    v0 = 32;
                    if (v1 == 0) {
                        // 0x004fc500
                        charge(ctx, 2);
                        v0 = 0;
                    } else {
                        // 0x004fc4f8
                        charge(ctx, 2);
                        v0 = subu(v0, v1);
                    }
                }
                // 0x004fc51c
                charge(ctx, 7);
                sw(v0, s0, 2124);
                v0 = 0x10000000;
                v0 = v0 | 0x2010;
                lw(v1, v0, 0);  // 0x10002010
                v1 = v1 & 0x4000;
                a0 = s0;
                if (v1 != 0) {
                    // 0x004fc538
                    charge(ctx, 2);
                    s5 = 0;
                    jal(ctx, 0x4FC538u, gen::fn__sceMpegErrorBdec_005025a0);
                }
                // 0x004fc540
                charge(ctx, 1);
                v0 = s5;
                goto L_004fc544;
            }
        L_004fc4c4:
            charge(ctx, 1);
            v0 = 0x10000000;
            goto L_004fc4c8;
        }
        // 0x004fc408
        charge(ctx, 2);
        v0 = 0;
    L_004fc6ac:
        charge(ctx, 1);
        ld(ra, sp, 0xD0);
    }
    // 0x004fc6b0 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(s6, sp, 0xC0);
    ld(s5, sp, 0xB0);
    ld(s4, sp, 0xA0);
    ld(s3, sp, 0x90);
    ld(s2, sp, 0x80);
    ld(s1, sp, 0x70);
    ld(s0, sp, 0x60);
    sp = addiu(sp, 0xE0);
    return;
L_004fc508:
    charge(ctx, 4);
    jal(ctx, 0x4FC508u, gen::fn__sceMpegStopIpuDma_00502500);
    v0 = 0;
L_004fc544:
    charge(ctx, 2);
    if (v0 == 0) {
        goto L_004fc54c_24;
    }
    lw(v0, sp, 0x44);
    // 0x004fc560
    charge(ctx, 2);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    lw(v0, sp, 0x40);
    if (!cc) {
        // 0x004fc568
        charge(ctx, 5);
        a0 = s0;
        a1 = 23;
        jal(ctx, 0x4FC56Cu, gen::fn__sceMpegPeepBit_004fd740);
        if (v0 == 0) {
            sw(zero, s0, 300);
            goto L_004fc58c;
        }
        // 0x004fc57c
        charge(ctx, 3);
        lw(v0, s0, 300);
        if (v0 != 0) {
            goto L_004fc588_28;
        }
        // 0x004fc594
        charge(ctx, 5);
        a0 = s0;
        jal(ctx, 0x4FC594u, gen::fn__sceMpegMbAddressIncrement_004fd1f8);
        lw(v1, s0, 300);
        sw(v0, sp, 0x44);
        if (v1 != 0) {
            goto L_004fc608;
        }
        // 0x004fc5a8
        charge(ctx, 1);
        lw(v0, sp, 0x40);
        goto L_004fc5ac;
    }
L_004fc5ac:
    charge(ctx, 3);
    v0 = slt(v0, s6);
    lw(v1, sp, 0x44);
    if (v0 == 0) {
        goto L_004fc5b8_33;
    }
    // 0x004fc5d0
    charge(ctx, 3);
    v0 = 1;
    s2 = addiu(sp, 0x20);
    if (v1 == v0) {
        // 0x004fc5dc
        charge(ctx, 11);
        s1 = addiu(sp, 0x30);
        a0 = s0;
        a1 = addiu(sp, 0x48);
        a2 = addiu(sp, 0x4C);
        a3 = addiu(sp, 0x50);
        t0 = sp;
        t1 = s2;
        t2 = s1;
        jal(ctx, 0x4FC5F8u, gen::fn__decMB0_004fcca0);
        lw(a1, sp, 0x40);
        if (v0 != 0) {
            goto L_004fc638;
        }
        goto L_004fc608;
    }
    // 0x004fc614
    charge(ctx, 8);
    a0 = s0;
    a1 = sp;
    a2 = addiu(sp, 0x4C);
    a3 = s2;
    t0 = addiu(sp, 0x48);
    jal(ctx, 0x4FC624u, gen::fn__skipMB0_004fd8a8);
    s1 = addiu(sp, 0x30);
    if (v0 == 0) {
        goto L_004fc660;
    }
    // 0x004fc634
    charge(ctx, 1);
    lw(a1, sp, 0x40);
L_004fc638:
    charge(ctx, 10);
    t2 = s2;
    lw(a2, sp, 0x44);
    t3 = s1;
    lw(a3, sp, 0x48);
    a0 = s0;
    lw(t0, sp, 0x4C);
    t1 = sp;
    jal(ctx, 0x4FC650u, gen::fn__motionComp0_004fb870);
    lw(a0, sp, 0x40);
    if (v0 == 0) {
        goto L_004fc660;
    }
    // 0x004fc66c
    charge(ctx, 2);
    if (a0 == 0) {
        lw(v0, s0, 2080);
    } else {
        // 0x004fc674
        charge(ctx, 6);
        lw(a1, s0, 2080);
        a0 = s0;
        a1 = a1 ^ 0x1;
        jal(ctx, 0x4FC67Cu, gen::fn__doMC_004fbf48);
        lw(a0, sp, 0x40);
        lw(v0, s0, 2080);
    }
    // 0x004fc68c
    charge(ctx, 8);
    a0 = addiu(a0, 1);
    lw(v1, sp, 0x44);
    v0 = v0 ^ 0x1;
    sw(a0, sp, 0x40);
    v1 = addiu(v1, -1);
    sw(v0, s0, 2080);
    sw(v1, sp, 0x44);
    backedge(ctx);
    goto L_004fc3f8;
L_004fc54c_24:
    charge(ctx, 5);
    lw(a0, s0, 2168);
    v1 = 4;
    v0 = 2;
    if (a0 != 0) v0 = v1;
    goto L_004fc6ac;
L_004fc588_28:
    charge(ctx, 1);
    sw(zero, s0, 300);
L_004fc58c:
    charge(ctx, 2);
    v0 = 3;
    goto L_004fc6ac;
L_004fc5b8_33:
    charge(ctx, 6);
    a1 = 0x7C0000;
    a0 = s0;
    a1 = addiu(a1, -10880);  // "Too many macroblocks in picture"
    jal(ctx, 0x4FC5C0u, gen::fn__sceMpegError_00502668);
    v0 = 2;
    goto L_004fc6ac;
L_004fc608:
    charge(ctx, 3);
    sw(zero, s0, 300);
    v0 = 1;
    goto L_004fc6ac;
L_004fc660:
    charge(ctx, 3);
    sw(zero, s0, 300);
    v0 = 2;
    goto L_004fc6ac;
}

// 0x004FC6D8 _motionVector -- 1064 bytes; frame 0xA0: s1 sp+0x10, fp sp+0x80, s7 sp+0x70, s6 sp+0x60, s5 sp+0x50, s4 sp+0x40, s3 sp+0x30, s2 sp+0x20, ra sp+0x90, s0 sp+0x0
// libmpeg: decodes one motion vector component pair with the IPU VDEC command (f_code and the predictors).
void _motionVector(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x004fc6d8
    enter(ctx, 40);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(s1, sp, 0x10);
    s1 = a0;
    sd(fp, sp, 0x80);
    sd(s7, sp, 0x70);
    fp = a2;
    sd(s6, sp, 0x60);
    s7 = t1;
    sd(s5, sp, 0x50);
    s6 = t2;
    sd(s4, sp, 0x40);
    s5 = t3;
    sd(s3, sp, 0x30);
    s4 = t0;
    sd(s2, sp, 0x20);
    s3 = a1;
    sd(ra, sp, 0x90);
    s2 = a3;
    link(ctx, 0x4FC720u);  // $ra first: the delay slot below depends on it
    sd(s0, sp, 0x0);
    call(ctx, gen::fn__waitIpuIdle_004fd868);
    v0 = 0x10000000;
    v1 = 0x38000000;
    v0 = v0 | 0x2000;
    a1 = 0x30000000;
    sw(v1, v0, 0);  // 0x10002000
    a0 = s1;
    sw(zero, s1, 2088);
    link(ctx, 0x4FC744u);  // $ra first: the delay slot below depends on it
    sw(a1, s1, 2092);
    call(ctx, gen::fn__sceMpegWaitIpuIdle64_004fd4d8);
    a2 = v0;
    v1 = 0x10000000;
    v0 = 0x10000000;
    v1 = v1 | 0x2030;
    v0 = v0 | 0x2020;
    lw(a1, v0, 0);  // 0x10002020
    ld(a0, v1, 0);  // 0x10002030
    v0 = dsll32(a0, 0);
    v0 = dsra32(v0, 0);
    sw(v0, s1, 2120);
    if (i64(a0) >= 0) {
        // 0x004fc788
        charge(ctx, 1);
        v0 = 32;
    } else {
        // 0x004fc778
        charge(ctx, 4);
        v0 = a1 & 0x1F;
        v0 = subu(0, v0);
        v0 = v0 & 0x1F;
    }
    // 0x004fc78c
    charge(ctx, 9);
    sw(v0, s1, 2124);
    v1 = a2 & 0xFFFF;
    v0 = dsll32(a2, 0);
    v0 = dsra32(v0, 0);
    v0 = sltiu(v0, 1);
    v1 = sll(v1, 16);
    sw(v0, s1, 300);
    s0 = sra(v1, 16);
    if (s2 == 0) {
        // 0x004fc7cc
        charge(ctx, 1);
        a1 = 0;
    } else {
        // 0x004fc7b0
        charge(ctx, 2);
        a1 = 0;
        if (s0 != 0) {
            // 0x004fc7b8
            charge(ctx, 5);
            a0 = s1;
            a1 = s2;
            jal(ctx, 0x4FC7BCu, gen::fn__sceMpegNextBit_004fd658);
            a1 = v0;
        }
    }
    // 0x004fc7d0
    charge(ctx, 6);
    lw(a0, s3, 0);
    v0 = 16;
    a2 = sllv(v0, s2);
    v1 = sra(a0, 1);
    if (s5 != 0) a0 = v1;
    if (i64(s0) <= 0) {
        // 0x004fc814
        charge(ctx, 2);
        v0 = sll(a0, 1);
        if (i64(s0) < 0) {
            // 0x004fc81c
            charge(ctx, 9);
            v0 = nor(0, s0);
            a0 = addiu(a0, -1);
            v0 = sllv(v0, s2);
            v1 = subu(0, a2);
            v0 = addu(v0, a1);
            a0 = subu(a0, v0);
            v1 = slt(a0, v1);
            v0 = sll(a2, 1);
            if (v1 != 0) {
                // 0x004fc840
                charge(ctx, 1);
                a0 = addu(a0, v0);
            }
        L_004fc844:
            charge(ctx, 1);
            v0 = sll(a0, 1);
        }
    } else {
        // 0x004fc7e8
        charge(ctx, 8);
        v0 = addiu(s0, -1);
        a0 = addiu(a0, 1);
        v0 = sllv(v0, s2);
        v0 = addu(v0, a1);
        a0 = addu(a0, v0);
        v1 = slt(a0, a2);
        v0 = sll(a0, 1);
        if (v1 == 0) {
            // 0x004fc808
            charge(ctx, 3);
            v0 = sll(a2, 1);
            a0 = subu(a0, v0);
            goto L_004fc844;
        }
    }
    // 0x004fc848
    charge(ctx, 3);
    if (s5 == 0) v0 = a0;
    sw(v0, s3, 0);
    if (s7 != 0) {
        // 0x004fc854
        charge(ctx, 22);
        a0 = s1;
        jal(ctx, 0x4FC854u, gen::fn__waitIpuIdle_004fd868);
        v0 = 0x10000000;
        v1 = 0x3C000000;
        v0 = v0 | 0x2000;
        a1 = 0x30000000;
        sw(v1, v0, 0);  // 0x10002000
        a0 = s1;
        sw(zero, s1, 2088);
        link(ctx, 0x4FC878u);  // $ra first: the delay slot below depends on it
        sw(a1, s1, 2092);
        call(ctx, gen::fn__sceMpegWaitIpuIdle64_004fd4d8);
        a2 = v0;
        v1 = 0x10000000;
        v0 = 0x10000000;
        v1 = v1 | 0x2030;
        v0 = v0 | 0x2020;
        lw(a1, v0, 0);  // 0x10002020
        ld(a0, v1, 0);  // 0x10002030
        v0 = dsll32(a0, 0);
        v0 = dsra32(v0, 0);
        sw(v0, s1, 2120);
        if (i64(a0) >= 0) {
            // 0x004fc8bc
            charge(ctx, 1);
            v0 = 32;
        } else {
            // 0x004fc8ac
            charge(ctx, 4);
            v0 = a1 & 0x1F;
            v0 = subu(0, v0);
            v0 = v0 & 0x1F;
        }
        // 0x004fc8c0
        charge(ctx, 9);
        sw(v0, s1, 2124);
        v1 = a2 & 0xFFFF;
        v0 = dsll32(a2, 0);
        v0 = dsra32(v0, 0);
        v0 = sltiu(v0, 1);
        v1 = sll(v1, 16);
        sw(v0, s1, 300);
        v1 = sra(v1, 16);
        sw(v1, fp, 0x0);
    }
    // 0x004fc8e4
    charge(ctx, 22);
    a0 = s1;
    jal(ctx, 0x4FC8E4u, gen::fn__waitIpuIdle_004fd868);
    v0 = 0x10000000;
    v1 = 0x38000000;
    v0 = v0 | 0x2000;
    a1 = 0x30000000;
    sw(v1, v0, 0);  // 0x10002000
    a0 = s1;
    sw(zero, s1, 2088);
    link(ctx, 0x4FC908u);  // $ra first: the delay slot below depends on it
    sw(a1, s1, 2092);
    call(ctx, gen::fn__sceMpegWaitIpuIdle64_004fd4d8);
    a2 = v0;
    v1 = 0x10000000;
    v0 = 0x10000000;
    v1 = v1 | 0x2030;
    v0 = v0 | 0x2020;
    lw(a1, v0, 0);  // 0x10002020
    ld(a0, v1, 0);  // 0x10002030
    v0 = dsll32(a0, 0);
    v0 = dsra32(v0, 0);
    sw(v0, s1, 2120);
    if (i64(a0) >= 0) {
        // 0x004fc94c
        charge(ctx, 1);
        v0 = 32;
    } else {
        // 0x004fc93c
        charge(ctx, 4);
        v0 = a1 & 0x1F;
        v0 = subu(0, v0);
        v0 = v0 & 0x1F;
    }
    // 0x004fc950
    charge(ctx, 9);
    sw(v0, s1, 2124);
    v1 = a2 & 0xFFFF;
    v0 = dsll32(a2, 0);
    v0 = dsra32(v0, 0);
    v0 = sltiu(v0, 1);
    v1 = sll(v1, 16);
    sw(v0, s1, 300);
    s0 = sra(v1, 16);
    if (s4 != 0) {
        // 0x004fc974
        charge(ctx, 2);
        a0 = s1;
        if (s0 == 0) {
            goto L_004fc98c;
        }
        // 0x004fc97c
        charge(ctx, 4);
        a1 = s4;
        jal(ctx, 0x4FC97Cu, gen::fn__sceMpegNextBit_004fd658);
        a1 = v0;
        goto L_004fc990;
    }
L_004fc98c:
    charge(ctx, 1);
    a1 = 0;
L_004fc990:
    charge(ctx, 2);
    if (s6 == 0) {
        lw(a0, s3, 4);
    } else {
        // 0x004fc998
        charge(ctx, 4);
        lw(v0, s3, 4);
        v0 = sra(v0, 1);
        sw(v0, s3, 4);
        lw(a0, s3, 4);
    }
    // 0x004fc9a8
    charge(ctx, 6);
    v0 = 16;
    a2 = sllv(v0, s4);
    a3 = addiu(s3, 4);
    v0 = sra(a0, 1);
    if (s5 != 0) a0 = v0;
    if (i64(s0) <= 0) {
        // 0x004fc9ec
        charge(ctx, 2);
        v0 = sll(a0, 1);
        if (i64(s0) < 0) {
            // 0x004fc9f4
            charge(ctx, 9);
            v0 = nor(0, s0);
            a0 = addiu(a0, -1);
            v0 = sllv(v0, s4);
            v1 = subu(0, a2);
            v0 = addu(v0, a1);
            a0 = subu(a0, v0);
            v1 = slt(a0, v1);
            v0 = sll(a2, 1);
            if (v1 != 0) {
                // 0x004fca18
                charge(ctx, 1);
                a0 = addu(a0, v0);
            }
        L_004fca1c:
            charge(ctx, 1);
            v0 = sll(a0, 1);
        }
    } else {
        // 0x004fc9c0
        charge(ctx, 8);
        v0 = addiu(s0, -1);
        a0 = addiu(a0, 1);
        v0 = sllv(v0, s4);
        v0 = addu(v0, a1);
        a0 = addu(a0, v0);
        v1 = slt(a0, a2);
        v0 = sll(a0, 1);
        if (v1 == 0) {
            // 0x004fc9e0
            charge(ctx, 3);
            v0 = sll(a2, 1);
            a0 = subu(a0, v0);
            goto L_004fca1c;
        }
    }
    // 0x004fca20
    charge(ctx, 3);
    if (s5 == 0) v0 = a0;
    sw(v0, a3, 0);
    if (s6 != 0) {
        // 0x004fca2c
        charge(ctx, 3);
        lw(v0, s3, 4);
        v0 = sll(v0, 1);
        sw(v0, s3, 4);
    }
    // 0x004fca38
    charge(ctx, 2);
    ld(ra, sp, 0x90);
    if (s7 != 0) {
        // 0x004fca40
        charge(ctx, 22);
        a0 = s1;
        jal(ctx, 0x4FCA40u, gen::fn__waitIpuIdle_004fd868);
        v0 = 0x10000000;
        v1 = 0x3C000000;
        v0 = v0 | 0x2000;
        a1 = 0x30000000;
        sw(v1, v0, 0);  // 0x10002000
        a0 = s1;
        sw(zero, s1, 2088);
        link(ctx, 0x4FCA64u);  // $ra first: the delay slot below depends on it
        sw(a1, s1, 2092);
        call(ctx, gen::fn__sceMpegWaitIpuIdle64_004fd4d8);
        a2 = v0;
        v1 = 0x10000000;
        v0 = 0x10000000;
        v1 = v1 | 0x2030;
        v0 = v0 | 0x2020;
        lw(a1, v0, 0);  // 0x10002020
        ld(a0, v1, 0);  // 0x10002030
        v0 = dsll32(a0, 0);
        v0 = dsra32(v0, 0);
        sw(v0, s1, 2120);
        if (i64(a0) >= 0) {
            // 0x004fcaa8
            charge(ctx, 1);
            v0 = 32;
        } else {
            // 0x004fca98
            charge(ctx, 4);
            v0 = a1 & 0x1F;
            v0 = subu(0, v0);
            v0 = v0 & 0x1F;
        }
        // 0x004fcaac
        charge(ctx, 10);
        sw(v0, s1, 2124);
        v1 = a2 & 0xFFFF;
        v0 = dsll32(a2, 0);
        v0 = dsra32(v0, 0);
        v0 = sltiu(v0, 1);
        v1 = sll(v1, 16);
        sw(v0, s1, 300);
        v1 = sra(v1, 16);
        sw(v1, fp, 0x4);
        ld(ra, sp, 0x90);
    }
    // 0x004fcad4 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(fp, sp, 0x80);
    ld(s7, sp, 0x70);
    ld(s6, sp, 0x60);
    ld(s5, sp, 0x50);
    ld(s4, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// 0x004FCCA0 _decMB0 -- 1368 bytes; frame 0xD0: s6 sp+0x90, s5 sp+0x80, s3 sp+0x60, s1 sp+0x40, s0 sp+0x30, ra sp+0xC0, fp sp+0xB0, s7 sp+0xA0, s4 sp+0x70, s2 sp+0x50
// libmpeg: decodes one macroblock: its type, quantiser scale, motion vectors, coded block pattern and the
// blocks (IPU IDEC / BDEC), receiving the result from the IPU.
void _decMB0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x004fcca0
    enter(ctx, 50);  // entry check point + this block's cycles
    sp = addiu(sp, -0xD0);
    t3 = 0x10000000;
    sd(s6, sp, 0x90);
    t3 = t3 | 0x2010;
    sd(s5, sp, 0x80);
    v0 = lui(0xF8FF);
    sd(s3, sp, 0x60);
    v0 = v0 | 0xFFFF;
    sd(s1, sp, 0x40);
    s3 = a1;
    sd(s0, sp, 0x30);
    s5 = a2;
    sd(ra, sp, 0xC0);
    s0 = a0;
    sd(fp, sp, 0xB0);
    s1 = t0;
    sd(s7, sp, 0xA0);
    s6 = t2;
    sd(s4, sp, 0x70);
    sd(s2, sp, 0x50);
    lw(a0, s0, 352);
    lw(v1, t3, 0);  // 0x10002010
    a0 = sll(a0, 24);
    v1 = v1 & v0;
    v1 = v1 | a0;
    sw(v1, t3, 0);  // 0x10002010
    a0 = s0;
    sw(a3, sp, 0x20);
    link(ctx, 0x4FCD10u);  // $ra first: the delay slot below depends on it
    sw(t1, sp, 0x24);
    call(ctx, gen::fn__waitIpuIdle_004fd868);
    v0 = 0x10000000;
    v1 = 0x34000000;
    v0 = v0 | 0x2000;
    a1 = 0x30000000;
    sw(v1, v0, 0);  // 0x10002000
    a0 = s0;
    sw(zero, s0, 2088);
    link(ctx, 0x4FCD34u);  // $ra first: the delay slot below depends on it
    sw(a1, s0, 2092);
    call(ctx, gen::fn__sceMpegWaitIpuIdle64_004fd4d8);
    a2 = v0;
    v1 = 0x10000000;
    v0 = 0x10000000;
    v1 = v1 | 0x2030;
    v0 = v0 | 0x2020;
    lw(a1, v0, 0);  // 0x10002020
    ld(a0, v1, 0);  // 0x10002030
    v0 = dsll32(a0, 0);
    v0 = dsra32(v0, 0);
    sw(v0, s0, 2120);
    if (i64(a0) >= 0) {
        // 0x004fcd78
        charge(ctx, 1);
        v0 = 32;
    } else {
        // 0x004fcd68
        charge(ctx, 4);
        v0 = a1 & 0x1F;
        v0 = subu(0, v0);
        v0 = v0 & 0x1F;
    }
    // 0x004fcd7c
    charge(ctx, 10);
    sw(v0, s0, 2124);
    v0 = a2 & 0xFFFF;
    v1 = dsll32(a2, 0);
    v1 = dsra32(v1, 0);
    v1 = sltiu(v1, 1);
    v0 = sll(v0, 16);
    a0 = sra(v0, 16);
    sw(v1, s0, 300);
    sw(a0, s3, 0);
    if (a0 != 0) {
        // 0x004fcdc4
        charge(ctx, 3);
        v0 = a0 & 0xC;
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = 3;
        if (!cc) {
            // 0x004fcdd0
            charge(ctx, 3);
            lw(v1, s0, 388);
            if (v1 != v0) {
                a0 = s0;
            } else {
                // 0x004fcddc
                charge(ctx, 3);
                lw(v0, s0, 396);
                cc = v0 == 0;  // the condition, before the delay slot changes it
                v0 = 2;
                if (cc) {
                    // 0x004fcdf0
                    charge(ctx, 1);
                    a0 = s0;
                    goto L_004fcdf4;
                }
                // 0x004fcde8
                charge(ctx, 2);
                sw(v0, s5, 0);
                goto L_004fce30;
            }
        L_004fcdf4:
            charge(ctx, 4);
            a1 = 2;
            jal(ctx, 0x4FCDF4u, gen::fn__sceMpegNextBit_004fd658);
            sw(v0, s5, 0);
            goto L_004fce30;
        }
        // 0x004fce04
        charge(ctx, 3);
        v0 = a0 & 0x1;
        if (v0 == 0) {
            lw(a2, s0, 388);
        } else {
            // 0x004fce10
            charge(ctx, 3);
            lw(v0, s0, 400);
            v1 = 1;
            if (v0 != 0) {
                // 0x004fce1c
                charge(ctx, 5);
                lw(v0, s0, 388);
                a0 = 2;
                v0 = v0 ^ 0x3;
                if (v0 == 0) v1 = a0;
                sw(v1, s5, 0);
            }
        L_004fce30:
            charge(ctx, 1);
            lw(a2, s0, 388);
        }
        // 0x004fce34
        charge(ctx, 3);
        v0 = 3;
        lw(a1, s5, 0);
        if (a2 != v0) {
            // 0x004fce5c
            charge(ctx, 5);
            v1 = 2;
            s2 = 1;
            s4 = 0;
            v0 = a1 ^ 0x2;
            if (v0 == 0) s2 = v1;
        } else {
            // 0x004fce40
            charge(ctx, 7);
            s2 = 1;
            v0 = 2;
            v1 = a1 ^ 0x1;
            a0 = a1 ^ 0x2;
            if (v1 == 0) s2 = v0;
            s4 = sltiu(a0, 1);
        }
        // 0x004fce70
        charge(ctx, 4);
        v0 = a1 ^ 0x3;
        s7 = 0;
        fp = sltiu(v0, 1);
        if (s4 == 0) {
            // 0x004fce80
            charge(ctx, 2);
            v0 = a2 ^ 0x3;
            s7 = sltiu(v0, 1);
        }
        // 0x004fce88
        charge(ctx, 3);
        v0 = 3;
        cc = a2 != v0;  // the condition, before the delay slot changes it
        v0 = 0;
        if (!cc) {
            // 0x004fce94
            charge(ctx, 3);
            lw(v0, s0, 396);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = 0;
            if (cc) {
                goto L_004fcec4;
            }
            // 0x004fcea0
            charge(ctx, 4);
            lw(v0, s3, 0);
            v0 = v0 & 0x3;
            a0 = s0;
            if (v0 == 0) {
                // 0x004fcec0
                charge(ctx, 1);
                v0 = 0;
                goto L_004fcec4;
            }
            // 0x004fceb0
            charge(ctx, 4);
            a1 = 1;
            jal(ctx, 0x4FCEB0u, gen::fn__sceMpegNextBit_004fd658);
            lw(v1, sp, 0x20);
            goto L_004fcec8;
        }
    L_004fcec4:
        charge(ctx, 1);
        lw(v1, sp, 0x20);
    L_004fcec8:
        charge(ctx, 5);
        sw(v0, v1, 0);
        lw(v1, s3, 0);
        v0 = v1 & 0x10;
        a0 = s0;
        if (v0 != 0) {
            // 0x004fcedc
            charge(ctx, 4);
            a1 = 5;
            jal(ctx, 0x4FCEDCu, gen::fn__sceMpegNextBit_004fd658);
            sw(v0, s0, 452);
            lw(v1, s3, 0);
        }
        // 0x004fceec
        charge(ctx, 3);
        v0 = v1 & 0x8;
        if (v0 != 0) {
            lw(v0, s0, 2136);
        } else {
            // 0x004fcef8
            charge(ctx, 3);
            v0 = v1 & 0x1;
            if (v0 == 0) {
                lw(v1, s0, 300);
            } else {
                // 0x004fcf04
                charge(ctx, 3);
                lw(v0, s0, 400);
                if (v0 != 0) {
                    // 0x004fcf10
                    charge(ctx, 1);
                    lw(v0, s0, 2136);
                    goto L_004fcf14;
                }
                lw(v1, s0, 300);
            }
            goto L_004fcf84;
        }
    L_004fcf14:
        charge(ctx, 2);
        a0 = s0;
        if (v0 == 0) {
            // 0x004fcf5c
            charge(ctx, 10);
            lw(a3, s0, 360);
            lw(t3, s0, 356);
            a1 = s1;
            a3 = addiu(a3, -1);
            a2 = s6;
            t1 = 0;
            t0 = a3;
            t2 = 0;
            jal(ctx, 0x4FCF78u, gen::fn__motionVector_004fc6d8);
            lw(v1, s0, 300);
        } else {
            // 0x004fcf1c
            charge(ctx, 16);
            lw(v0, s0, 376);
            lw(t3, s0, 372);
            a1 = s1;
            v0 = addiu(v0, -1);
            lw(a3, sp, 0x24);
            sw(fp, sp, 0x8);
            t3 = addiu(t3, -1);
            sw(v0, sp, 0x0);
            a2 = s6;
            sw(s7, sp, 0x10);
            t0 = 0;
            t1 = s2;
            t2 = s4;
            jal(ctx, 0x4FCF4Cu, gen::fn__motionVectors_004fcb00);
            lw(v1, s0, 300);
        }
    L_004fcf84:
        charge(ctx, 2);
        v0 = 0;
        if (v1 == 0) {
            // 0x004fcf8c
            charge(ctx, 4);
            lw(v0, s3, 0);
            v0 = v0 & 0x4;
            if (v0 != 0) {
                // 0x004fcf9c
                charge(ctx, 3);
                lw(v0, s0, 2136);
                a2 = s6;
                if (v0 == 0) {
                    // 0x004fcfe8
                    charge(ctx, 10);
                    lw(a3, s0, 368);
                    lw(t3, s0, 364);
                    a0 = s0;
                    a3 = addiu(a3, -1);
                    a1 = addiu(s1, 8);
                    t1 = 0;
                    t0 = a3;
                    t2 = 0;
                    jal(ctx, 0x4FD004u, gen::fn__motionVector_004fc6d8);
                    lw(v1, s0, 300);
                } else {
                    // 0x004fcfa8
                    charge(ctx, 16);
                    lw(v0, s0, 384);
                    lw(t3, s0, 380);
                    t1 = s2;
                    v0 = addiu(v0, -1);
                    lw(a3, sp, 0x24);
                    sw(s7, sp, 0x10);
                    t2 = s4;
                    sw(v0, sp, 0x0);
                    t3 = addiu(t3, -1);
                    sw(zero, sp, 0x8);
                    a0 = s0;
                    a1 = s1;
                    t0 = 1;
                    jal(ctx, 0x4FCFD8u, gen::fn__motionVectors_004fcb00);
                    lw(v1, s0, 300);
                }
            }
            // 0x004fd010
            charge(ctx, 2);
            v0 = 0;
            if (v1 == 0) {
                // 0x004fd018
                charge(ctx, 4);
                lw(v1, s3, 0);
                v0 = v1 & 0x1;
                cc = v0 == 0;  // the condition, before the delay slot changes it
                v0 = v1 & 0x3;
                if (!cc) {
                    // 0x004fd028
                    charge(ctx, 3);
                    lw(v0, s0, 400);
                    a0 = s0;
                    if (v0 != 0) {
                        // 0x004fd034
                        charge(ctx, 3);
                        a1 = 1;
                        jal(ctx, 0x4FD034u, gen::fn_sub_4FD8A0_004fd8a0);
                        lw(v1, s3, 0);
                    }
                    // 0x004fd040
                    charge(ctx, 1);
                    v0 = v1 & 0x3;
                }
                // 0x004fd044
                charge(ctx, 2);
                v1 = 320;
                if (v0 == 0) {
                    // 0x004fd0e8
                    charge(ctx, 5);
                    lw(v0, s0, 2080);
                    a0 = 1;
                    mult(a1, v0, v1);
                    v0 = addu(a1, s0);
                    sw(a0, v0, 1756);
                } else {
                    // 0x004fd04c
                    charge(ctx, 30);
                    lw(v0, s0, 2080);
                    a1 = 768;
                    mult(a0, v0, v1);
                    v0 = addu(a0, s0);
                    link(ctx, 0x4FD05Cu);  // $ra first: the delay slot below depends on it
                    lw(a0, v0, 1444);
                    call(ctx, gen::fn_receiveDataFromIPU_004fe988);
                    a0 = s0;
                    jal(ctx, 0x4FD064u, gen::fn__waitIpuIdle_004fd868);
                    lw(v0, sp, 0x20);
                    a3 = 0x20000000;
                    lw(a0, s0, 448);
                    a2 = 0x10000000;
                    lw(a1, v0, 0);
                    a2 = a2 | 0x2000;
                    lw(v0, s3, 0);
                    a0 = sll(a0, 26);
                    lw(v1, s0, 452);
                    a1 = sll(a1, 25);
                    v0 = v0 & 0x1;
                    a1 = a1 | a0;
                    v0 = sll(v0, 27);
                    v1 = sll(v1, 16);
                    v0 = v0 | a1;
                    v1 = v1 | a3;
                    v0 = v0 | v1;
                    v1 = lui(0xF000);
                    sw(v0, a2, 0);  // 0x10002000
                    a1 = v0 & v1;
                    sw(a1, s0, 2092);
                    if (a1 != a3) {
                        // 0x004fd0c4
                        charge(ctx, 3);
                        v0 = 0x30000000;
                        cc = a1 == v0;  // the condition, before the delay slot changes it
                        v0 = 0x40000000;
                        if (cc) {
                            goto L_004fd0d8;
                        }
                        // 0x004fd0d0
                        charge(ctx, 2);
                        cc = a1 != v0;  // the condition, before the delay slot changes it
                        v0 = 1;
                        if (!cc) {
                            goto L_004fd0d8;
                        }
                        // 0x004fd0e0
                        charge(ctx, 2);
                        sw(v0, s0, 2088);
                        goto L_004fd0fc;
                    }
                L_004fd0d8:
                    charge(ctx, 2);
                    sw(zero, s0, 2088);
                }
            L_004fd0fc:
                charge(ctx, 3);
                lw(v0, s0, 300);
                sw(zero, s0, 448);
                if (v0 == 0) {
                    // 0x004fd110
                    charge(ctx, 4);
                    lw(v0, s3, 0);
                    v0 = v0 & 0x1;
                    if (v0 != 0) {
                        lw(v0, s0, 400);
                    } else {
                        // 0x004fd120
                        charge(ctx, 6);
                        v1 = 1;
                        sw(v1, s0, 448);
                        lw(v0, s3, 0);
                        v0 = v0 & 0x1;
                        if (v0 != 0) {
                            // 0x004fd138
                            charge(ctx, 1);
                            lw(v0, s0, 400);
                            goto L_004fd13c;
                        }
                        lw(a0, s0, 352);
                        goto L_004fd168;
                    }
                L_004fd13c:
                    charge(ctx, 2);
                    if (v0 != 0) {
                        lw(a0, s0, 352);
                    } else {
                        // 0x004fd144
                        charge(ctx, 9);
                        sw(zero, s1, 20);
                        sw(zero, s1, 16);
                        sw(zero, s1, 4);
                        sw(zero, s1, 0);
                        sw(zero, s1, 28);
                        sw(zero, s1, 24);
                        sw(zero, s1, 12);
                        sw(zero, s1, 8);
                        lw(a0, s0, 352);
                    }
                L_004fd168:
                    charge(ctx, 3);
                    v0 = 2;
                    cc = a0 != v0;  // the condition, before the delay slot changes it
                    v0 = 1;
                    if (!cc) {
                        // 0x004fd174
                        charge(ctx, 4);
                        lw(v0, s3, 0);
                        v0 = v0 & 0x9;
                        cc = v0 != 0;  // the condition, before the delay slot changes it
                        v0 = 1;
                        if (!cc) {
                            // 0x004fd184
                            charge(ctx, 8);
                            sw(zero, s1, 0);
                            v1 = 3;
                            sw(zero, s1, 20);
                            sw(zero, s1, 16);
                            sw(zero, s1, 4);
                            lw(v0, s0, 388);
                            cc = v0 != v1;  // the condition, before the delay slot changes it
                            v1 = 1;
                            if (cc) {
                                // 0x004fd1ac
                                charge(ctx, 6);
                                sw(v1, s5, 0);
                                lw(v1, sp, 0x24);
                                lw(v0, s0, 388);
                                v0 = v0 ^ 0x2;
                                v0 = sltiu(v0, 1);
                                sw(v0, v1, 0);
                            } else {
                                // 0x004fd1a4
                                charge(ctx, 2);
                                sw(a0, s5, 0);
                            }
                            // 0x004fd1c4
                            charge(ctx, 1);
                            v0 = 1;
                        }
                    }
                } else {
                    // 0x004fd108
                    charge(ctx, 2);
                    v0 = 0;
                }
            }
        }
    } else {
        // 0x004fcda4
        charge(ctx, 8);
        a1 = 0x7C0000;
        a0 = s0;
        a1 = addiu(a1, -10800);  // "Invalid macroblock_type code: 0"
        jal(ctx, 0x4FCDACu, gen::fn__sceMpegError_00502668);
        v1 = 1;
        v0 = 0;
        sw(v1, s0, 300);
    }
    // 0x004fd1c8 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0xC0);
    ld(fp, sp, 0xB0);
    ld(s7, sp, 0xA0);
    ld(s6, sp, 0x90);
    ld(s5, sp, 0x80);
    ld(s4, sp, 0x70);
    ld(s3, sp, 0x60);
    ld(s2, sp, 0x50);
    ld(s1, sp, 0x40);
    ld(s0, sp, 0x30);
    sp = addiu(sp, 0xD0);
}

// 0x004FD1F8 _sceMpegMbAddressIncrement -- 376 bytes; frame 0x70: s5 sp+0x50, s4 sp+0x40, s3 sp+0x30, s2 sp+0x20, s1 sp+0x10, ra sp+0x60, s0 sp+0x0
// libmpeg: reads a macroblock-address increment (with the escape / stuffing codes) through the IPU.
void _sceMpegMbAddressIncrement(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x004fd1f8
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(s5, sp, 0x50);
    sd(s4, sp, 0x40);
    s5 = 0x7C0000;
    sd(s3, sp, 0x30);
    s4 = 0x30000000;
    sd(s2, sp, 0x20);
    s3 = 32;
    sd(s1, sp, 0x10);
    s2 = 0;
    sd(ra, sp, 0x60);
    s1 = a0;
    sd(s0, sp, 0x0);
    for (;;) {
        // 0x004fd230
        charge(ctx, 20);
        a0 = s1;
        jal(ctx, 0x4FD230u, gen::fn__waitIpuIdle_004fd868);
        v0 = 0x10000000;
        a0 = s1;
        v0 = v0 | 0x2000;
        sw(s4, v0, 0);  // 0x10002000
        sw(s4, s1, 2092);
        link(ctx, 0x4FD24Cu);  // $ra first: the delay slot below depends on it
        sw(zero, s1, 2088);
        call(ctx, gen::fn__sceMpegWaitIpuIdle64_004fd4d8);
        a2 = v0;
        v1 = 0x10000000;
        v0 = 0x10000000;
        v1 = v1 | 0x2030;
        v0 = v0 | 0x2020;
        lw(a1, v0, 0);  // 0x10002020
        ld(a0, v1, 0);  // 0x10002030
        v0 = dsll32(a0, 0);
        v0 = dsra32(v0, 0);
        sw(v0, s1, 2120);
        if (i64(a0) >= 0) {
            // 0x004fd294
            charge(ctx, 1);
            sw(s3, s1, 2124);
        } else {
            // 0x004fd280
            charge(ctx, 5);
            v0 = a1 & 0x1F;
            v0 = subu(s3, v0);
            v0 = v0 & 0x1F;
            sw(v0, s1, 2124);
        }
        // 0x004fd298
        charge(ctx, 9);
        v0 = a2 & 0xFFFF;
        v1 = dsll32(a2, 0);
        v1 = dsra32(v1, 0);
        v0 = sll(v0, 16);
        v1 = sltiu(v1, 1);
        s0 = sra(v0, 16);
        v0 = 34;
        sw(v1, s1, 300);
        if (s0 != v0) {
            // 0x004fd2bc
            charge(ctx, 3);
            v0 = sltiu(s0, 35);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = 35;
            if (!cc) {
                // 0x004fd2c8
                charge(ctx, 2);
                a0 = s1;
                if (s0 != 0) {
                    // 0x004fd2d0
                    charge(ctx, 2);
                    s2 = addu(s2, s0);
                    goto L_004fd340;
                }
                // 0x004fd2ec
                charge(ctx, 6);
                a1 = 11;
                jal(ctx, 0x4FD2ECu, gen::fn__sceMpegPeepBit_004fd740);
                v1 = v0;
                lw(v0, s1, 2136);
                cc = v0 == 0;  // the condition, before the delay slot changes it
                v0 = 15;
                if (cc) {
                    goto L_004fd320;
                }
                // 0x004fd304
                charge(ctx, 2);
                a1 = addiu(s5, -10768);
                if (v1 != v0) {
                    goto L_004fd324;
                }
                // 0x004fd30c
                charge(ctx, 3);
                a0 = s1;
                a1 = 11;
                jal(ctx, 0x4FD310u, gen::fn_sub_4FD8A0_004fd8a0);
                goto L_004fd318;
            }
            // 0x004fd2d8
            charge(ctx, 2);
            if (s0 != v0) {
                s2 = addu(s2, s0);
            L_004fd340:
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x004fd2e0
                charge(ctx, 3);
                v0 = 1;
                s2 = addiu(s2, 33);
            }
        L_004fd344:
            charge(ctx, 2);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = s2;
            if (cc) {
                backedge(ctx);
                continue;
            }
            break;
        }
    L_004fd318:
        charge(ctx, 2);
        v0 = 1;
        goto L_004fd344;
    }
    // 0x004fd34c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    ld(s5, sp, 0x50);
    ld(s4, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
    return;
L_004fd320:
    charge(ctx, 1);
    a1 = addiu(s5, -10768);
L_004fd324:
    charge(ctx, 7);
    a2 = s0;
    a0 = s1;
    jal(ctx, 0x4FD328u, gen::fn__sceMpegError1_005026c0);
    v1 = 1;
    v0 = 1;
    sw(v1, s1, 300);
    // 0x004fd34c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    ld(s5, sp, 0x50);
    ld(s4, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x004FD370 _sceMpegWaitIpuIdle -- 360 bytes; frame 0xA0: s0 sp+0x0, ra sp+0x90, fp sp+0x80, s7 sp+0x70, s6 sp+0x60, s5 sp+0x50, s4 sp+0x40, s3 sp+0x30, s2 sp+0x20, s1 sp+0x10
// libmpeg: waits for the IPU to go idle; on an IPU error stops the IPU DMA and reports it.
void _sceMpegWaitIpuIdle(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x004fd370
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    v0 = 0x10000000;
    sd(s0, sp, 0x0);
    v0 = v0 | 0x2010;
    sd(ra, sp, 0x90);
    a1 = lui(0x8000);
    sd(fp, sp, 0x80);
    a1 = a1 | 0x4000;
    sd(s7, sp, 0x70);
    s0 = a0;
    sd(s6, sp, 0x60);
    a2 = 0;
    sd(s5, sp, 0x50);
    sd(s4, sp, 0x40);
    sd(s3, sp, 0x30);
    sd(s2, sp, 0x20);
    sd(s1, sp, 0x10);
    lw(v1, v0, 0);  // 0x10002010
    v0 = lui(0x8000);
    v1 = v1 & a1;
    if (v1 != v0) {
        sw(zero, s0, 2092);
    } else {
        // 0x004fd3c8
        charge(ctx, 12);
        s4 = 0x10000000;
        s3 = 0x10000000;
        s2 = 0x10000000;
        s1 = lui(0x8000);
        s4 = s4 | 0x2020;
        fp = 0x20000000;
        s7 = 0x30000000;
        s6 = 0x40000000;
        s3 = s3 | 0xB420;
        s2 = s2 | 0x2010;
        s1 = s1 | 0x4000;
        s5 = lui(0x8000);
        for (;;) {
            // 0x004fd3f8
            charge(ctx, 11);
            lw(a0, s4, 0);
            a3 = 0x30000;
            lw(a1, s0, 2092);
            v1 = a0 & 0xFF00;
            v0 = a0 & a3;
            v0 = srl(v0, 9);
            v1 = srl(v1, 1);
            v1 = addu(v1, v0);
            a0 = a0 & 0x7F;
            v0 = subu(v1, a0);
            if (a1 != fp) {
                // 0x004fd424
                charge(ctx, 2);
                if (a1 != s7) {
                    // 0x004fd42c
                    charge(ctx, 2);
                    if (a1 == s6) {
                        goto L_004fd434;
                    }
                    v0 = a2;
                    goto L_004fd464;
                }
                v0 = sltiu(v0, 32);
            L_004fd438:
                charge(ctx, 2);
                cc = v0 == 0;  // the condition, before the delay slot changes it
                v0 = a2;
                if (!cc) {
                    // 0x004fd440
                    charge(ctx, 3);
                    lw(v0, s3, 0);
                    cc = v0 != 0;  // the condition, before the delay slot changes it
                    v0 = a2;
                    if (cc) {
                        goto L_004fd464;
                    }
                    // 0x004fd44c
                    charge(ctx, 5);
                    link(ctx, 0x4FD44Cu);  // $ra first: the delay slot below depends on it
                    lw(a0, s0, 2152);
                    call(ctx, gen::fn__sceMpegDispatchMpegCbNodata_00500d88);
                    lw(v1, s0, 2168);
                    a2 = 0;
                    if (v1 != 0) {
                        goto L_004fd484;
                    }
                    // 0x004fd460
                    charge(ctx, 1);
                    v0 = a2;
                    goto L_004fd464;
                }
            L_004fd464:
                charge(ctx, 3);
                v0 = slti(v0, 5001);
                a2 = addiu(a2, 1);
                if (v0 == 0) {
                    // 0x004fd470
                    charge(ctx, 5);
                    link(ctx, 0x4FD470u);  // $ra first: the delay slot below depends on it
                    lw(a0, s0, 2152);
                    call(ctx, gen::fn__sceMpegDispatchMpegCbNodata_00500d88);
                    lw(v1, s0, 2168);
                    a2 = 0;
                    if (v1 == 0) {
                        goto L_004fd494;
                    }
                    goto L_004fd484;
                }
            L_004fd494:
                charge(ctx, 4);
                lw(v0, s2, 0);
                v0 = v0 & s1;
                if (v0 != s5) {
                    break;
                }
                backedge(ctx);
                continue;
            }
        L_004fd434:
            charge(ctx, 1);
            v0 = sltiu(v0, 32);
            goto L_004fd438;
        }
        // 0x004fd4a4
        charge(ctx, 1);
        sw(zero, s0, 2092);
    }
    // 0x004fd4a8 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0x90);
    ld(fp, sp, 0x80);
    ld(s7, sp, 0x70);
    ld(s6, sp, 0x60);
    ld(s5, sp, 0x50);
    ld(s4, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
    return;
L_004fd484:
    charge(ctx, 4);
    jal(ctx, 0x4FD484u, gen::fn__sceMpegStopIpuDma_00502500);
    sw(zero, s0, 2092);
    // 0x004fd4a8 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0x90);
    ld(fp, sp, 0x80);
    ld(s7, sp, 0x70);
    ld(s6, sp, 0x60);
    ld(s5, sp, 0x50);
    ld(s4, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// 0x004FD4D8 _sceMpegWaitIpuIdle64 -- 384 bytes; frame 0xA0: s0 sp+0x0, ra sp+0x90, fp sp+0x80, s7 sp+0x70, s6 sp+0x60, s5 sp+0x50, s4 sp+0x40, s3 sp+0x30, s2 sp+0x20, s1 sp+0x10
// libmpeg: the 64-bit form of _sceMpegWaitIpuIdle (returns the IPU_CMD doubleword).
void _sceMpegWaitIpuIdle64(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x004fd4d8
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    v0 = 0x10000000;
    sd(s0, sp, 0x0);
    v0 = v0 | 0x2000;
    sd(ra, sp, 0x90);
    s0 = a0;
    sd(fp, sp, 0x80);
    a2 = 0;
    sd(s7, sp, 0x70);
    sd(s6, sp, 0x60);
    sd(s5, sp, 0x50);
    sd(s4, sp, 0x40);
    sd(s3, sp, 0x30);
    sd(s2, sp, 0x20);
    sd(s1, sp, 0x10);
    ld(s1, v0, 0);  // 0x10002000
    if (i64(s1) >= 0) {
        sw(zero, s0, 2092);
    } else {
        // 0x004fd520
        charge(ctx, 6);
        v0 = 0x10000000;
        v0 = v0 | 0x2010;
        lw(v1, v0, 0);  // 0x10002010
        v1 = v1 & 0x4000;
        if (v1 != 0) {
            sw(zero, s0, 2092);
        } else {
            // 0x004fd538
            charge(ctx, 12);
            s5 = 0x10000000;
            s4 = 0x10000000;
            s3 = 0x10000000;
            s2 = 0x10000000;
            s5 = s5 | 0x2020;
            fp = 0x20000000;
            s7 = 0x30000000;
            s6 = 0x40000000;
            s4 = s4 | 0xB420;
            s3 = s3 | 0x2000;
            s2 = s2 | 0x2010;
            for (;;) {
                // 0x004fd568
                charge(ctx, 11);
                lw(a0, s5, 0);
                a3 = 0x30000;
                lw(a1, s0, 2092);
                v1 = a0 & 0xFF00;
                v0 = a0 & a3;
                v0 = srl(v0, 9);
                v1 = srl(v1, 1);
                v1 = addu(v1, v0);
                a0 = a0 & 0x7F;
                v0 = subu(v1, a0);
                if (a1 != fp) {
                    // 0x004fd594
                    charge(ctx, 2);
                    if (a1 != s7) {
                        // 0x004fd59c
                        charge(ctx, 2);
                        if (a1 == s6) {
                            goto L_004fd5a4;
                        }
                        v0 = a2;
                        goto L_004fd5d4;
                    }
                    v0 = sltiu(v0, 32);
                L_004fd5a8:
                    charge(ctx, 2);
                    cc = v0 == 0;  // the condition, before the delay slot changes it
                    v0 = a2;
                    if (!cc) {
                        // 0x004fd5b0
                        charge(ctx, 3);
                        lw(v0, s4, 0);
                        cc = v0 != 0;  // the condition, before the delay slot changes it
                        v0 = a2;
                        if (cc) {
                            goto L_004fd5d4;
                        }
                        // 0x004fd5bc
                        charge(ctx, 5);
                        link(ctx, 0x4FD5BCu);  // $ra first: the delay slot below depends on it
                        lw(a0, s0, 2152);
                        call(ctx, gen::fn__sceMpegDispatchMpegCbNodata_00500d88);
                        lw(v1, s0, 2168);
                        a2 = 0;
                        if (v1 != 0) {
                            goto L_004fd5f4;
                        }
                        // 0x004fd5d0
                        charge(ctx, 1);
                        v0 = a2;
                        goto L_004fd5d4;
                    }
                L_004fd5d4:
                    charge(ctx, 3);
                    v0 = slti(v0, 501);
                    a2 = addiu(a2, 1);
                    if (v0 == 0) {
                        // 0x004fd5e0
                        charge(ctx, 5);
                        link(ctx, 0x4FD5E0u);  // $ra first: the delay slot below depends on it
                        lw(a0, s0, 2152);
                        call(ctx, gen::fn__sceMpegDispatchMpegCbNodata_00500d88);
                        lw(v1, s0, 2168);
                        a2 = 0;
                        if (v1 == 0) {
                            goto L_004fd604;
                        }
                        goto L_004fd5f4;
                    }
                L_004fd604:
                    charge(ctx, 3);
                    ld(s1, s3, 0);
                    if (i64(s1) < 0) {
                        // 0x004fd610
                        charge(ctx, 4);
                        lw(v0, s2, 0);
                        v0 = v0 & 0x4000;
                        if (v0 != 0) {
                            goto L_004fd620_16;
                        }
                        backedge(ctx);
                        continue;
                    }
                    sw(zero, s0, 2092);
                    break;
                }
            L_004fd5a4:
                charge(ctx, 1);
                v0 = sltiu(v0, 32);
                goto L_004fd5a8;
            }
        }
    }
    // 0x004fd624 (the shared epilogue, written out on this path)
    charge(ctx, 13);
    v0 = s1;
    ld(ra, sp, 0x90);
    ld(fp, sp, 0x80);
    ld(s7, sp, 0x70);
    ld(s6, sp, 0x60);
    ld(s5, sp, 0x50);
    ld(s4, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
    return;
L_004fd5f4:
    charge(ctx, 4);
    jal(ctx, 0x4FD5F4u, gen::fn__sceMpegStopIpuDma_00502500);
    sw(zero, s0, 2092);
    // 0x004fd624 (the shared epilogue, written out on this path)
    charge(ctx, 13);
    v0 = s1;
    ld(ra, sp, 0x90);
    ld(fp, sp, 0x80);
    ld(s7, sp, 0x70);
    ld(s6, sp, 0x60);
    ld(s5, sp, 0x50);
    ld(s4, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
    return;
L_004fd620_16:
    charge(ctx, 1);
    sw(zero, s0, 2092);
    // 0x004fd624 (the shared epilogue, written out on this path)
    charge(ctx, 13);
    v0 = s1;
    ld(ra, sp, 0x90);
    ld(fp, sp, 0x80);
    ld(s7, sp, 0x70);
    ld(s6, sp, 0x60);
    ld(s5, sp, 0x50);
    ld(s4, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// 0x004FD7D0 _sceMpegFlushBuf -- 148 bytes; frame 0x30: s1 sp+0x10, s0 sp+0x0, ra sp+0x20
// libmpeg: flushes the IPU input FIFO (waits idle, then BCLR at the current bit position).
void _sceMpegFlushBuf(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004fd7d0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x10);
    sd(s0, sp, 0x0);
    s1 = a0;
    sd(ra, sp, 0x20);
    s0 = a1;
    jal(ctx, 0x4FD7E4u, gen::fn__waitIpuIdle_004fd868);
    a0 = 0x40000000;
    v0 = 0x10000000;
    s0 = s0 | a0;
    v0 = v0 | 0x2000;
    sw(s0, v0, 0);  // 0x10002000
    v1 = lui(0xF000);
    s0 = s0 & v1;
    v0 = 0x20000000;
    sw(s0, s1, 2092);
    if (s0 != v0) {
        // 0x004fd814
        charge(ctx, 3);
        v0 = 0x30000000;
        if (s0 == v0) {
            sw(zero, s1, 2088);
        } else {
            // 0x004fd820
            charge(ctx, 2);
            v0 = 1;
            if (s0 == a0) {
                goto L_004fd828;
            }
            // 0x004fd830
            charge(ctx, 1);
            sw(v0, s1, 2088);
        }
        goto L_004fd834;
    }
L_004fd828:
    charge(ctx, 2);
    sw(zero, s1, 2088);
L_004fd834:
    charge(ctx, 12);
    a0 = s1;
    jal(ctx, 0x4FD834u, gen::fn__sceMpegWaitIpuIdle64_004fd4d8);
    v0 = dsll32(v0, 0);
    v0 = dsra32(v0, 0);
    v1 = 32;
    sw(v1, s1, 2124);
    sw(v0, s1, 2120);
    ld(ra, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x004FD868 _waitIpuIdle -- 52 bytes; leaf frame (no stack)
// libmpeg: a frameless wrapper of _sceMpegWaitIpuIdle.
void _waitIpuIdle(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a1{ctx, 5};
    // 0x004fd868
    enter(ctx, 9);  // entry check point + this block's cycles
    v0 = 0x10000000;
    a1 = lui(0x8000);
    v0 = v0 | 0x2010;
    a1 = a1 | 0x4000;
    lw(v1, v0, 0);  // 0x10002010
    v0 = lui(0x8000);
    v1 = v1 & a1;
    if (v1 != v0) {
        // 0x004fd894
        charge(ctx, 2);
        return;
    }
    // 0x004fd88c
    charge(ctx, 2);
    gen::fn__sceMpegWaitIpuIdle_004fd370(ctx);  // tail call
}

// 0x004FDB18 dmaRefImage -- 380 bytes; frame 0x40: s0 sp+0x0, ra sp+0x30, s2 sp+0x20, s1 sp+0x10
// libmpeg: DMAs one reference-image block to its work area (interrupts off around the channel setup).
void dmaRefImage(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, t8{ctx, 24}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004fdb18
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x30);
    s0 = a0;
    sd(s2, sp, 0x20);
    sd(s1, sp, 0x10);
    lw(v0, s0, 2172);
    ld(ra, sp, 0x30);
    if (v0 != 0) {
        // 0x004fdc80 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s2, sp, 0x20);
        ld(s1, sp, 0x10);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
        return;
    }
    // 0x004fdb3c
    charge(ctx, 14);
    lw(t8, s0, 2080);
    a0 = 320;
    s2 = 0x960000;
    v0 = 0xFFF0000;
    mult(v1, t8, a0);
    v0 = v0 | 0xFFFF;
    a1 = 0x20000000;
    t2 = 0;
    a0 = addu(v1, s0);
    v1 = addiu(s2, 23296);  // &0x965B00
    lw(t4, a0, 1740);
    v1 = v1 & v0;
    t3 = v1 | a1;
    if (i64(t4) <= 0) {
        // 0x004fdc08
        charge(ctx, 1);
        s1 = addiu(s0, 1440);
    } else {
        // 0x004fdb74
        charge(ctx, 5);
        t7 = addiu(s0, 1448);
        t6 = addiu(s0, 1464);
        t5 = addiu(t4, -1);
        s1 = addiu(s0, 1440);
        for (;;) {
            // 0x004fdb88
            charge(ctx, 30);
            a0 = 320;
            v0 = sll(t2, 2);
            mult(a0, t8, a0);
            v1 = t2 ^ t5;
            a1 = 3;
            a2 = 0xFFF0000;
            if (v1 == 0) a1 = 0;
            a2 = a2 | 0xFFFF;
            t1 = 0x30000000;
            a1 = dsll(a1, 28);
            v0 = addu(v0, a0);
            a3 = 48;
            a0 = addu(t6, v0);
            t2 = addiu(t2, 1);
            v0 = addu(t7, v0);
            t0 = slt(t2, t4);
            lw(v1, v0, 0);
            lw(v0, a0, 0);
            v1 = v1 & a2;
            v0 = v0 & a2;
            v1 = dsll32(v1, 0);
            v0 = dsll32(v0, 0);
            v1 = v1 | t1;
            v0 = v0 | a1;
            v1 = v1 | a3;
            v0 = v0 | a3;
            sd(v1, t3, 0);
            sd(v0, t3, 16);
            t3 = addiu(t3, 32);
            if (t0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004fdc00
        charge(ctx, 2);
    }
    // 0x004fdc0c
    charge(ctx, 24);
    jal(ctx, 0x4FDC0Cu, gen::fn_DIntr_0050d3a0);
    sync(ctx, 0);
    lw(a2, s0, 2080);
    v1 = 320;
    a3 = 0x10000000;
    t0 = 0x10000000;
    mult(a0, a2, v1);
    a3 = a3 | 0xD480;
    t2 = addiu(s2, 23296);
    t0 = t0 | 0xD430;
    v1 = 0x10000000;
    t1 = 261;
    v1 = v1 | 0xD420;
    a2 = addu(a0, s1);
    lw(a1, a2, 0);
    a0 = 0x10000000;
    a0 = a0 | 0xD400;
    sw(a1, a3, 0);  // 0x1000D480
    sw(t2, t0, 0);  // 0x1000D430
    sw(zero, v1, 0);  // 0x1000D420
    sw(t1, a0, 0);  // 0x1000D400
    ld(ra, sp, 0x30);
    if (v0 == 0) {
        // 0x004fdc80 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s2, sp, 0x20);
        ld(s1, sp, 0x10);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
        return;
    }
    // 0x004fdc6c
    charge(ctx, 5);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
    gen::fn_EIntr_0050d3f0(ctx);  // tail call
}

// 0x004FE988 receiveDataFromIPU -- 160 bytes; frame 0x30: s1 sp+0x10, s0 sp+0x0, ra sp+0x20
// libmpeg: starts the fromIPU (ch3) DMA of a decoded block into the work buffer (interrupts off around it).
void receiveDataFromIPU(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x004fe988
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x10);
    sd(s0, sp, 0x0);
    s1 = a1;
    sd(ra, sp, 0x20);
    s0 = a0;
    jal(ctx, 0x4FE99Cu, gen::fn_DIntr_0050d3a0);
    a1 = v0;
    v1 = srl(s0, 28);
    v0 = 7;
    cc = v1 != v0;  // the condition, before the delay slot changes it
    v0 = 0xFFF0000;
    if (cc) {
        // 0x004fe9cc
        charge(ctx, 2);
        v0 = v0 | 0xFFFF;
        s0 = s0 & v0;
    } else {
        // 0x004fe9b8
        charge(ctx, 5);
        v1 = lui(0x8000);
        v0 = v0 | 0xFFFF;
        s0 = s0 & v0;
        s0 = s0 | v1;
    }
    // 0x004fe9d4
    charge(ctx, 13);
    v0 = 0x10000000;
    v1 = 0x10000000;
    v0 = v0 | 0xB010;
    v1 = v1 | 0xB020;
    sw(s0, v0, 0);  // 0x1000B010
    a0 = sra(s1, 4);
    sw(a0, v1, 0);  // 0x1000B020
    v0 = 0x10000000;
    v0 = v0 | 0xB000;
    v1 = 256;
    sw(v1, v0, 0);  // 0x1000B000
    ld(ra, sp, 0x20);
    if (a1 == 0) {
        // 0x004fea18
        charge(ctx, 4);
        ld(s1, sp, 0x10);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
    // 0x004fea08
    charge(ctx, 4);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
    gen::fn_EIntr_0050d3f0(ctx);  // tail call
}

// 0x004FEA28 _sceMpegSliceA0 -- 416 bytes; frame 0x60: s0 sp+0x0, s4 sp+0x40, s3 sp+0x30, s2 sp+0x20, s1 sp+0x10, ra sp+0x50
// libmpeg: the decode loop of one slice for the A0 decode path (address increments and macroblocks).
void _sceMpegSliceA0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004fea28
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(s0, sp, 0x0);
    sd(s4, sp, 0x40);
    s0 = a0;
    sd(s3, sp, 0x30);
    s4 = a2;
    sd(s2, sp, 0x20);
    s3 = a3;
    sd(s1, sp, 0x10);
    sd(ra, sp, 0x50);
    s1 = t0;
    sw(zero, s0, 300);
    s2 = 1;
    jal(ctx, 0x4FEA58u, gen::fn_flushByteBoundary_004ffb38);
    a0 = s0;
    for (;;) {
        // 0x004fea74
        charge(ctx, 4);
        a1 = 24;
        jal(ctx, 0x4FEA74u, gen::fn__sceMpegPeepBit_004fd740);
        a0 = s0;
        if (v0 != s2) {
            // 0x004fea84
            charge(ctx, 3);
            lw(v0, s0, 2168);
            if (v0 == 0) {
                backedge(ctx);
                // 0x004fea68
                charge(ctx, 3);
                a1 = 8;
                jal(ctx, 0x4FEA68u, gen::fn_j__sceMpegFlushBuf_0_004ff9d0);
                a0 = s0;
                continue;
            }
        }
        break;
    }
    // 0x004fea90
    charge(ctx, 7);
    a1 = 32;
    jal(ctx, 0x4FEA90u, gen::fn__sceMpegPeepBit_004fd740);
    s2 = v0;
    v0 = addiu(s2, -257);
    v0 = sltiu(v0, 175);
    a1 = 0x7C0000;
    if (v0 != 0) {
        // 0x004feac4
        charge(ctx, 11);
        a0 = s0;
        jal(ctx, 0x4FEAC4u, gen::fn_flushBuf32_004ffb30);
        a0 = s0;
        a1 = 5;
        jal(ctx, 0x4FEAD0u, gen::fn__sceMpegNextBit_004fd658);
        sw(v0, s0, 452);
        a0 = s0;
        a1 = 1;
        jal(ctx, 0x4FEAE0u, gen::fn__sceMpegNextBit_004fd658);
        a0 = s0;
        if (v0 != 0) {
            // 0x004feaf0
            charge(ctx, 7);
            a1 = 1;
            jal(ctx, 0x4FEAF0u, gen::fn__sceMpegNextBit_004fd658);
            a0 = s0;
            a1 = 7;
            jal(ctx, 0x4FEAFCu, gen::fn_j__sceMpegFlushBuf_0_004ff9d0);
            a0 = s0;
            for (;;) {
                // 0x004feb1c
                charge(ctx, 4);
                a1 = 1;
                jal(ctx, 0x4FEB1Cu, gen::fn__sceMpegNextBit_004fd658);
                a0 = s0;
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x004feb10
                charge(ctx, 3);
                a1 = 8;
                jal(ctx, 0x4FEB10u, gen::fn_j__sceMpegFlushBuf_0_004ff9d0);
                a0 = s0;
            }
        }
        // 0x004feb2c
        charge(ctx, 7);
        a0 = s0;
        jal(ctx, 0x4FEB2Cu, gen::fn__sceMpegMbAddressIncrement_004fd1f8);
        a2 = v0;
        sw(a2, s3, 0);
        lw(v0, s0, 300);
        a1 = 0x7C0000;
        if (v0 == 0) {
            // 0x004feb5c
            charge(ctx, 19);
            lw(v0, s0, 316);
            v1 = s2 & 0xFF;
            v1 = addiu(v1, -1);
            a0 = 1;
            mult(a1, v1, v0);
            v0 = 0;
            v1 = addu(a1, a2);
            v1 = addiu(v1, -1);
            sw(v1, s4, 0);
            sw(a0, s3, 0);
            sw(a0, s0, 448);
            sw(zero, s1, 8);
            sw(zero, s1, 20);
            sw(zero, s1, 16);
            sw(zero, s1, 4);
            sw(zero, s1, 0);
            sw(zero, s1, 28);
            sw(zero, s1, 24);
            sw(zero, s1, 12);
        } else {
            // 0x004feb48
            charge(ctx, 5);
            a0 = s0;
            a1 = addiu(a1, -10672);
            jal(ctx, 0x4FEB4Cu, gen::fn__sceMpegError_00502668);
            v0 = 1;
        }
    } else {
        // 0x004feaac
        charge(ctx, 6);
        a0 = s0;
        a1 = addiu(a1, -10712);
        a2 = s2;
        jal(ctx, 0x4FEAB4u, gen::fn__sceMpegError1_005026c0);
        v0 = 2;
    }
    // 0x004feba8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    ld(s4, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x004FEEE0 _sequenceHeader -- 684 bytes; frame 0x60: s1 sp+0x30, ra sp+0x50, s2 sp+0x40, s0 sp+0x20
// libmpeg: parses a sequence header: picture size, aspect, frame rate, bit rate and the quantiser matrices
// (loaded into the IPU with interrupts off).
void _sequenceHeader(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x004feee0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    a1 = 32;
    sd(s1, sp, 0x30);
    s1 = a0;
    sd(ra, sp, 0x50);
    sd(s2, sp, 0x40);
    sd(s0, sp, 0x20);
    link(ctx, 0x4FEEFCu);  // $ra first: the delay slot below depends on it
    sw(zero, s1, 232);
    call(ctx, gen::fn__sceMpegNextBit_004fd658);
    v1 = v0;
    v0 = srl(v1, 8);
    v0 = v0 & 0xFFF;
    v1 = srl(v1, 20);
    sw(v1, s1, 308);
    a0 = slti(v0, 2801);
    sw(v0, s1, 312);
    if (a0 == 0) {
        // 0x004fef24
        charge(ctx, 4);
        a1 = 0x7C0000;
        a0 = s1;
        a1 = addiu(a1, -10632);  // "vertical size > 2800"
        jal(ctx, 0x4FEF2Cu, gen::fn__sceMpegError_00502668);
    }
    // 0x004fef34
    charge(ctx, 14);
    a0 = s1;
    a1 = 30;
    jal(ctx, 0x4FEF38u, gen::fn__sceMpegNextBit_004fd658);
    v1 = v0;
    a0 = s1;
    v0 = srl(v1, 1);
    a1 = 1;
    v1 = srl(v1, 12);
    v0 = v0 & 0x3FF;
    sw(v1, s1, 324);
    link(ctx, 0x4FEF5Cu);  // $ra first: the delay slot below depends on it
    sw(v0, s1, 328);
    call(ctx, gen::fn__sceMpegNextBit_004fd658);
    sw(v0, s1, 2128);
    if (v0 == 0) {
        // 0x004fefa0
        charge(ctx, 32);
        v0 = 2;
        lw(a0, s1, 2152);
        s0 = 0x780000;
        sw(v0, sp, 0x0);
        s0 = addiu(s0, -3264);  // &0x77F340
        a1 = sp;
        jal(ctx, 0x4FEFB4u, gen::fn__sceMpegDispatchMpegCallback_00500d10);
        s2 = 0x50000000;
        a0 = s1;
        jal(ctx, 0x4FEFC0u, gen::fn__waitIpuIdle_0_004ff998);
        v0 = 0x10000000;
        a0 = s1;
        v0 = v0 | 0x2000;
        link(ctx, 0x4FEFD4u);  // $ra first: the delay slot below depends on it
        sw(zero, v0, 0);
        call(ctx, gen::fn__waitIpuIdle_0_004ff998);
        jal(ctx, 0x4FEFDCu, gen::fn_DIntr_0050d3a0);
        v1 = 0xFFF0000;
        a0 = 0x10000000;
        v1 = v1 | 0xFFFF;
        a0 = a0 | 0xB410;
        s0 = s0 & v1;
        a1 = 0x10000000;
        sw(s0, a0, 0);  // 0x1000B410
        a1 = a1 | 0xB420;
        a0 = 4;
        v1 = 0x10000000;
        sw(a0, a1, 0);  // 0x1000B420
        v1 = v1 | 0xB400;
        a0 = 257;
        sw(a0, v1, 0);  // 0x1000B400
        if (v0 != 0) {
            // 0x004ff020
            charge(ctx, 2);
            jal(ctx, 0x4FF020u, gen::fn_EIntr_0050d3f0);
        }
        // 0x004ff028
        charge(ctx, 13);
        at = 0x10000000;
        sw(s2, at, 8192);  // 0x10002000
        v0 = 1;
        sw(s2, s1, 2092);
        a0 = s1;
        link(ctx, 0x4FF03Cu);  // $ra first: the delay slot below depends on it
        sw(v0, s1, 2088);
        call(ctx, gen::fn__waitIpuIdle_0_004ff998);
        v0 = 3;
        lw(a0, s1, 2152);
        sw(v0, sp, 0x0);
        a1 = sp;
        jal(ctx, 0x4FF050u, gen::fn__sceMpegDispatchMpegCallback_00500d10);
        a0 = s1;
    } else {
        // 0x004fef6c
        charge(ctx, 13);
        a0 = s1;
        jal(ctx, 0x4FEF6Cu, gen::fn__waitIpuIdle_0_004ff998);
        v0 = 0x10000000;
        v1 = 0x50000000;
        v0 = v0 | 0x2000;
        a1 = 1;
        sw(v1, v0, 0);  // 0x10002000
        a0 = s1;
        sw(v1, s1, 2092);
        link(ctx, 0x4FEF90u);  // $ra first: the delay slot below depends on it
        sw(a1, s1, 2088);
        call(ctx, gen::fn__waitIpuIdle_0_004ff998);
        a0 = s1;
    }
    // 0x004ff05c
    charge(ctx, 4);
    a1 = 1;
    jal(ctx, 0x4FF05Cu, gen::fn__sceMpegNextBit_004fd658);
    sw(v0, s1, 2132);
    if (v0 == 0) {
        // 0x004ff0a4
        charge(ctx, 32);
        v0 = 2;
        lw(a0, s1, 2152);
        s0 = 0x780000;
        sw(v0, sp, 0x0);
        s0 = addiu(s0, -3200);  // &0x77F380
        a1 = sp;
        jal(ctx, 0x4FF0B8u, gen::fn__sceMpegDispatchMpegCallback_00500d10);
        a0 = s1;
        jal(ctx, 0x4FF0C0u, gen::fn__waitIpuIdle_0_004ff998);
        v0 = 0x10000000;
        a0 = s1;
        v0 = v0 | 0x2000;
        link(ctx, 0x4FF0D4u);  // $ra first: the delay slot below depends on it
        sw(zero, v0, 0);
        call(ctx, gen::fn__waitIpuIdle_0_004ff998);
        jal(ctx, 0x4FF0DCu, gen::fn_DIntr_0050d3a0);
        v1 = 0xFFF0000;
        a0 = 0x10000000;
        v1 = v1 | 0xFFFF;
        a0 = a0 | 0xB410;
        s0 = s0 & v1;
        a1 = 0x10000000;
        sw(s0, a0, 0);  // 0x1000B410
        a1 = a1 | 0xB420;
        a0 = 4;
        v1 = 0x10000000;
        sw(a0, a1, 0);  // 0x1000B420
        v1 = v1 | 0xB400;
        a0 = 257;
        sw(a0, v1, 0);  // 0x1000B400
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = 0x58000000;
        if (!cc) {
            // 0x004ff124
            charge(ctx, 3);
            jal(ctx, 0x4FF124u, gen::fn_EIntr_0050d3f0);
            v0 = 0x58000000;
        }
        // 0x004ff130
        charge(ctx, 13);
        v1 = 0x50000000;
        at = 0x10000000;
        sw(v0, at, 8192);  // 0x10002000
        a0 = s1;
        v0 = 1;
        sw(v1, s1, 2092);
        link(ctx, 0x4FF148u);  // $ra first: the delay slot below depends on it
        sw(v0, s1, 2088);
        call(ctx, gen::fn__waitIpuIdle_0_004ff998);
        v0 = 3;
        lw(a0, s1, 2152);
        sw(v0, sp, 0x0);
        a1 = sp;
        jal(ctx, 0x4FF15Cu, gen::fn__sceMpegDispatchMpegCallback_00500d10);
    } else {
        // 0x004ff06c
        charge(ctx, 14);
        a0 = s1;
        jal(ctx, 0x4FF06Cu, gen::fn__waitIpuIdle_0_004ff998);
        v0 = 0x10000000;
        v1 = 0x58000000;
        v0 = v0 | 0x2000;
        a0 = 0x50000000;
        sw(v1, v0, 0);  // 0x10002000
        a1 = 1;
        sw(a0, s1, 2092);
        a0 = s1;
        link(ctx, 0x4FF094u);  // $ra first: the delay slot below depends on it
        sw(a1, s1, 2088);
        call(ctx, gen::fn__waitIpuIdle_0_004ff998);
    }
    // 0x004ff164
    charge(ctx, 10);
    a0 = s1;
    jal(ctx, 0x4FF164u, gen::fn__extensionAndUserData_004ff7c8);
    link(ctx, 0x4FF16Cu);  // $ra first: the delay slot below depends on it
    lw(a0, s1, 2152);
    call(ctx, gen::fn__initSeq_004febc8);
    ld(ra, sp, 0x50);
    ld(s2, sp, 0x40);
    ld(s1, sp, 0x30);
    ld(s0, sp, 0x20);
    sp = addiu(sp, 0x60);
}

// 0x004FF998 _waitIpuIdle_0 -- 52 bytes; leaf frame (no stack)
// libmpeg: the second frameless wrapper of _sceMpegWaitIpuIdle (used by the header parsers).
void _waitIpuIdle_0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a1{ctx, 5};
    // 0x004ff998
    enter(ctx, 9);  // entry check point + this block's cycles
    v0 = 0x10000000;
    a1 = lui(0x8000);
    v0 = v0 | 0x2010;
    a1 = a1 | 0x4000;
    lw(v1, v0, 0);  // 0x10002010
    v0 = lui(0x8000);
    v1 = v1 & a1;
    if (v1 != v0) {
        // 0x004ff9c4
        charge(ctx, 2);
        return;
    }
    // 0x004ff9bc
    charge(ctx, 2);
    gen::fn__sceMpegWaitIpuIdle_004fd370(ctx);  // tail call
}

// 0x005001B0 _clearEach -- 304 bytes, 2 chunks; frame 0x10: ra sp+0x0
// libmpeg: clears a decoder's per-stream state on sceMpegReset (with interrupts off).
void _clearEach(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005001b0
    enter(ctx, 30);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 1;
    sd(ra, sp, 0x0);
    sw(v0, a0, 2088);
    link(ctx, 0x5001C0u);  // $ra first: the delay slot below depends on it
    sw(zero, a0, 448);
    call(ctx, gen::fn_DIntr_0050d3a0);
    a2 = 0x10000000;
    a3 = 0x10000000;
    a2 = a2 | 0xF520;
    t0 = 0x10000;
    lw(v1, a2, 0);  // 0x1000F520
    a3 = a3 | 0xF590;
    a0 = 0x10000000;
    a1 = 0x10000000;
    v1 = v1 | t0;
    a0 = a0 | 0xB000;
    sw(v1, a3, 0);  // 0x1000F590
    a1 = a1 | 0xB400;
    sw(zero, a0, 0);  // 0x1000B000
    v1 = 0x10000000;
    sw(zero, a1, 0);  // 0x1000B400
    v1 = v1 | 0xD400;
    sw(zero, v1, 0);  // 0x1000D400
    a0 = lui(0xFFFE);
    a0 = a0 | 0xFFFF;
    lw(v1, a2, 0);  // 0x1000F520
    v1 = v1 & a0;
    sw(v1, a3, 0);  // 0x1000F590
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = 0x10000000;
    if (!cc) {
        // 0x00500228
        charge(ctx, 3);
        jal(ctx, 0x500228u, gen::fn_EIntr_0050d3f0);
        v0 = 0x10000000;
    }
    // 0x00500234
    charge(ctx, 17);
    a0 = 0x10000000;
    v0 = v0 | 0xB020;
    a0 = a0 | 0xB420;
    sw(zero, v0, 0);
    v1 = 0x10000000;
    sw(zero, a0, 0);  // 0x1000B420
    v1 = v1 | 0xD420;
    sw(zero, v1, 0);  // 0x1000D420
    v0 = 0x10000000;
    v0 = v0 | 0x2010;
    v1 = 0x40000000;
    ld(ra, sp, 0x0);
    a0 = 0;
    sw(v1, v0, 0);  // 0x10002010
    a1 = 0;
    sp = addiu(sp, 0x10);
    // 0x00502a28
    charge(ctx, 2);
    v1 = 0;
    if (a0 == 0) {
        // 0x00502a44
        charge(ctx, 3);
        v1 = 0x10000000;
        v1 = v1 | 0x2010;
        for (;;) {
            // 0x00502a50
            charge(ctx, 7);
            lw(v0, v1, 0);
            if (i64(v0) >= 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00502a6c
        charge(ctx, 2);
        v1 = 0;
    L_00502a84:
        charge(ctx, 1);
        v0 = v1;
    } else {
        // 0x00502a30
        charge(ctx, 3);
        v0 = 1;
        cc = a0 == v0;  // the condition, before the delay slot changes it
        v0 = v1;
        if (cc) {
            // 0x00502a74
            charge(ctx, 4);
            v0 = 0x10000000;
            v0 = v0 | 0x2010;
            lw(v1, v0, 0);  // 0x10002010
            v1 = srl(v1, 31);
            goto L_00502a84;
        }
        // 0x00502a3c
        charge(ctx, 2);
    }
    // 0x00502a88 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00501C38 _doCSC2 -- 448 bytes; frame 0x80: s0 sp+0x40, s1 sp+0x50, ra sp+0x70, s2 sp+0x60
// libmpeg: colour-space conversion of a picture through the IPU CSC command, with the ch3 DMAC handler installed
// for the duration.
void _doCSC2(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00501c38
    enter(ctx, 16);  // entry check point + this block's cycles
    a3 = 1023;
    sp = addiu(sp, -0x80);
    div(a2, a3);
    sd(s0, sp, 0x40);
    v0 = 0xF0000;
    s0 = a1;
    v0 = v0 | 0xFC00;
    v1 = 0xFFF0000;
    sd(s1, sp, 0x50);
    v1 = v1 | 0xFFFF;
    sd(ra, sp, 0x70);
    v0 = addu(s0, v0);
    sd(s2, sp, 0x60);
    v0 = v0 & v1;
    if (a3 == 0) {
        brk(ctx, 0x501C74u, 0x7u);
    }
    // 0x00501c78
    charge(ctx, 12);
    v1 = 0x10000000;
    sw(a2, sp, 0x28);
    s1 = a0;
    sw(v0, sp, 0x2C);
    a3 = addiu(sp, 0x20);
    sw(zero, sp, 0x24);
    v1 = v1 | 0x2010;
    sw(zero, sp, 0x20);
    mflo(t0);
    t0 = addiu(t0, 1);
    sw(t0, sp, 0x30);
    for (;;) {
        // 0x00501ca8
        charge(ctx, 7);
        lw(v0, v1, 0);
        if (i64(v0) >= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00501cc4
    charge(ctx, 30);
    a1 = 0x500000;
    a0 = 3;
    a1 = addiu(a1, 8912);  // &_ch3dmaCSC
    a2 = 0;
    jal(ctx, 0x501CD0u, gen::fn__sceAddDmacHandler_0_00502e80);
    s2 = v0;
    v1 = 8;
    v0 = 0x10000000;
    a0 = 3;
    v0 = v0 | 0xE010;
    link(ctx, 0x501CECu);  // $ra first: the delay slot below depends on it
    sw(v1, v0, 0);
    call(ctx, gen::fn_EnableDmac_00503d78);
    jal(ctx, 0x501CF4u, gen::fn_DIntr_0050d3a0);
    v1 = 0xFFF0000;
    a0 = 0x10000000;
    v1 = v1 | 0xFFFF;
    a0 = a0 | 0xB010;
    v1 = s0 & v1;
    a1 = 0x10000000;
    sw(v1, a0, 0);  // 0x1000B010
    a1 = a1 | 0xB020;
    v1 = 0xFFC0;
    a0 = 0x10000000;
    sw(v1, a1, 0);  // 0x1000B020
    a0 = a0 | 0xB000;
    v1 = 256;
    sw(v1, a0, 0);  // 0x1000B000
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = 0x10000000;
    if (!cc) {
        // 0x00501d3c
        charge(ctx, 3);
        jal(ctx, 0x501D3Cu, gen::fn_EIntr_0050d3f0);
        v0 = 0x10000000;
    }
    // 0x00501d48
    charge(ctx, 12);
    v1 = 0x70000000;
    v0 = v0 | 0x2000;
    v1 = v1 | 0x3FF;
    sw(v1, v0, 0);
    a2 = 4;
    lw(a0, s1, 2152);
    a1 = sp;
    link(ctx, 0x501D64u);  // $ra first: the delay slot below depends on it
    sw(a2, sp, 0x0);
    call(ctx, gen::fn__sceMpegDispatchMpegCallback_00500d10);
    lw(a0, sp, 0x24);
    lw(v1, sp, 0x30);
    for (;;) {
        // 0x00501d78
        charge(ctx, 7);
        lw(v0, sp, 0x20);
        v0 = slt(v0, v1);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00501d94
    charge(ctx, 2);
    cc = a0 == 0;  // the condition, before the delay slot changes it
    a0 = s1;
    if (!cc) {
        // 0x00501d9c
        charge(ctx, 3);
        a1 = 0x7C0000;
        a1 = addiu(a1, -9704);  // "CSC handler error\n"
        jal(ctx, 0x501DA0u, gen::fn__sceMpegError_00502668);
    }
    // 0x00501da8
    charge(ctx, 2);
    v1 = 0x10000000;
    v1 = v1 | 0x2010;
    for (;;) {
        // 0x00501db0
        charge(ctx, 7);
        lw(v0, v1, 0);
        if (i64(v0) >= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00501dcc
    charge(ctx, 11);
    a0 = 3;
    jal(ctx, 0x501DCCu, gen::fn_DisableDmac_00503d10);
    a1 = s2;
    a0 = 3;
    jal(ctx, 0x501DD8u, gen::fn__sceRemoveDmacHandler_00502e90);
    ld(ra, sp, 0x70);
    ld(s2, sp, 0x60);
    ld(s1, sp, 0x50);
    ld(s0, sp, 0x40);
    sp = addiu(sp, 0x80);
}

// 0x005022D0 _ch3dmaCSC -- 328 bytes; leaf frame (no stack)
// libmpeg: the ch3 (fromIPU) DMAC handler of the CSC: queues the next slice of the conversion or ends it.
void _ch3dmaCSC(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005022d0
    enter(ctx, 13);  // entry check point + this block's cycles
    v0 = 0x10000000;
    v1 = 8;
    v0 = v0 | 0xE010;
    t1 = a1;
    sw(v1, v0, 0);  // 0x1000E010
    a0 = 0x10000000;
    a0 = a0 | 0xB020;
    lw(v0, t1, 0);
    v0 = addiu(v0, 1);
    sw(v0, t1, 0);
    lw(v1, a0, 0);  // 0x1000B020
    v0 = 1;
    if (v1 != 0) {
        // 0x0050231c (the shared epilogue, written out on this path)
        charge(ctx, 5);
        sw(v0, t1, 4);
        sync(ctx, 0);
        ei(ctx);
        v0 = 0;
        return;
    }
    // 0x00502304
    charge(ctx, 6);
    v0 = 0x10000000;
    v0 = v0 | 0xB000;
    lw(v1, v0, 0);  // 0x1000B000
    v1 = v1 & 0x100;
    v0 = 1;
    if (v1 != 0) {
        // 0x0050231c (the shared epilogue, written out on this path)
        charge(ctx, 5);
        sw(v0, t1, 4);
        sync(ctx, 0);
        ei(ctx);
        v0 = 0;
        return;
    }
    // 0x00502330
    charge(ctx, 6);
    lw(v1, t1, 16);
    lw(v0, t1, 0);
    v1 = addiu(v1, -1);
    v0 = slt(v0, v1);
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = 0x10000000;
    if (cc) {
        // 0x005023a4
        charge(ctx, 3);
        lw(v0, t1, 0);
        t0 = 256;
        if (v0 == v1) {
            // 0x005023b0
            charge(ctx, 22);
            lw(a1, t1, 0);
            a0 = 0x10000000;
            lw(v1, t1, 8);
            a0 = a0 | 0xB010;
            v0 = sll(a1, 10);
            lw(a2, t1, 12);
            v0 = subu(v0, a1);
            v1 = subu(v1, v0);
            a1 = 0x10000000;
            sw(v1, t1, 8);
            a3 = 0x70000000;
            sw(a2, a0, 0);  // 0x1000B010
            a1 = a1 | 0x2000;
            lw(v0, t1, 8);
            v0 = sll(v0, 6);
            at = 0x10010000;
            sw(v0, at, -20448);  // 0x1000B020
            at = 0x10010000;
            sw(t0, at, -20480);  // 0x1000B000
            lw(v0, t1, 8);
            v0 = v0 | a3;
            sw(v0, a1, 0);  // 0x10002000
        }
    } else {
        // 0x00502348
        charge(ctx, 23);
        lw(v1, t1, 12);
        v0 = v0 | 0xB010;
        a0 = 0xFFC0;
        sw(v1, v0, 0);
        a1 = 256;
        at = 0x10010000;
        sw(a0, at, -20448);  // 0x1000B020
        v1 = 0x10000000;
        v0 = 0x70000000;
        at = 0x10010000;
        sw(a1, at, -20480);  // 0x1000B000
        v1 = v1 | 0x2000;
        v0 = v0 | 0x3FF;
        sw(v0, v1, 0);  // 0x10002000
        a0 = 0xF0000;
        a0 = a0 | 0xFC00;
        v1 = 0xFFF0000;
        lw(v0, t1, 12);
        v1 = v1 | 0xFFFF;
        v0 = addu(v0, a0);
        v0 = v0 & v1;
        sw(v0, t1, 12);
    }
    // 0x00502408 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    sync(ctx, 0);
    ei(ctx);
    v0 = 0;
}

// 0x00502A90 setD4_CHCR_0 -- 116 bytes; frame 0x20: s0 sp+0x0, ra sp+0x10
// libipu: writes the toIPU (ch4) CHCR with interrupts off.
void setD4_CHCR_0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00502a90
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    s0 = a0;
    jal(ctx, 0x502A9Cu, gen::fn_DIntr_0050d3a0);
    a2 = 0x10000000;
    a3 = 0x10000000;
    a2 = a2 | 0xF520;
    t0 = 0x10000;
    lw(v1, a2, 0);  // 0x1000F520
    a3 = a3 | 0xF590;
    a0 = 0x10000000;
    a1 = lui(0xFFFE);
    v1 = v1 | t0;
    a0 = a0 | 0xB400;
    sw(v1, a3, 0);  // 0x1000F590
    a1 = a1 | 0xFFFF;
    sw(s0, a0, 0);  // 0x1000B400
    lw(v1, a2, 0);  // 0x1000F520
    v1 = v1 & a1;
    sw(v1, a3, 0);  // 0x1000F590
    ld(ra, sp, 0x10);
    if (v0 == 0) {
        // 0x00502af8
        charge(ctx, 3);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x00502aec
    charge(ctx, 3);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
    gen::fn_EIntr_0050d3f0(ctx);  // tail call
}

// 0x00502B08 sceIpuInit -- 568 bytes; frame 0x10: ra sp+0x0
// libipu: resets the IPU and its two DMA channels and sets the decode defaults.
void sceIpuInit(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00502b08
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 1;
    jal(ctx, 0x502B10u, gen::fn_setD4_CHCR_0_00502a90);
    v0 = 0x10000000;
    v1 = 0x40000000;
    v0 = v0 | 0x2010;
    a0 = 0x10000000;
    sw(v1, v0, 0);  // 0x10002010
    a0 = a0 | 0x2010;
    for (;;) {
        // 0x00502b30
        charge(ctx, 7);
        lw(v0, a0, 0);
        if (i64(v0) >= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00502b4c
    charge(ctx, 5);
    v0 = 0x10000000;
    v1 = 0x10000000;
    v0 = v0 | 0x2000;
    v1 = v1 | 0x2010;
    sw(zero, v0, 0);  // 0x10002000
    for (;;) {
        // 0x00502b60
        charge(ctx, 7);
        lw(v0, v1, 0);
        if (i64(v0) >= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00502b7c
    charge(ctx, 27);
    a1 = 0x780000;
    a0 = 0x10000000;
    a1 = addiu(a1, -3056);  // &0x77F410
    a0 = a0 | 0x7010;
    lq(v0, a1, 0);  // 0x77F410
    a2 = 0x10000000;
    a3 = 0x50000000;
    a2 = a2 | 0x2000;
    sq(v0, a0, 0);  // 0x10007010
    t0 = 0x10000000;
    t0 = t0 | 0x2010;
    lq(v1, a1, 16);  // 0x77F420
    sq(v1, a0, 0);  // 0x10007010
    lq(v0, a1, 32);  // 0x77F430
    sq(v0, a0, 0);  // 0x10007010
    lq(v1, a1, 48);  // 0x77F440
    sq(v1, a0, 0);  // 0x10007010
    lq(v0, a1, 64);  // 0x77F450
    sq(v0, a0, 0);  // 0x10007010
    lq(v1, a1, 64);  // 0x77F450
    sq(v1, a0, 0);  // 0x10007010
    lq(v0, a1, 64);  // 0x77F450
    sq(v0, a0, 0);  // 0x10007010
    lq(v1, a1, 64);  // 0x77F450
    sq(v1, a0, 0);  // 0x10007010
    sw(a3, a2, 0);  // 0x10002000
    for (;;) {
        // 0x00502be8
        charge(ctx, 7);
        lw(v0, t0, 0);
        if (i64(v0) >= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00502c04
    charge(ctx, 7);
    v0 = 0x10000000;
    v1 = 0x58000000;
    v0 = v0 | 0x2000;
    a0 = 0x10000000;
    sw(v1, v0, 0);  // 0x10002000
    a0 = a0 | 0x2010;
    for (;;) {
        // 0x00502c20
        charge(ctx, 7);
        lw(v0, a0, 0);
        if (i64(v0) >= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00502c3c
    charge(ctx, 15);
    v1 = 0x780000;
    a0 = 0x10000000;
    v1 = addiu(v1, -2976);  // &0x77F460
    a0 = a0 | 0x7010;
    lq(v0, v1, 0);  // 0x77F460
    a1 = 0x10000000;
    a2 = 0x60000000;
    a1 = a1 | 0x2000;
    sq(v0, a0, 0);  // 0x10007010
    a3 = 0x10000000;
    a3 = a3 | 0x2010;
    lq(v0, v1, 16);  // 0x77F470
    sq(v0, a0, 0);  // 0x10007010
    sw(a2, a1, 0);  // 0x10002000
    for (;;) {
        // 0x00502c78
        charge(ctx, 7);
        lw(v0, a3, 0);
        if (i64(v0) >= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00502c94
    charge(ctx, 7);
    v0 = 0x10000000;
    v1 = lui(0x9000);
    v0 = v0 | 0x2000;
    a0 = 0x10000000;
    sw(v1, v0, 0);  // 0x10002000
    a0 = a0 | 0x2010;
    for (;;) {
        // 0x00502cb0
        charge(ctx, 7);
        lw(v0, a0, 0);
        if (i64(v0) >= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00502ccc
    charge(ctx, 7);
    v0 = 0x10000000;
    v1 = 0x40000000;
    v0 = v0 | 0x2010;
    a0 = 0x10000000;
    sw(v1, v0, 0);  // 0x10002010
    a0 = a0 | 0x2010;
    for (;;) {
        // 0x00502ce8
        charge(ctx, 7);
        lw(v0, a0, 0);
        if (i64(v0) >= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00502d04
    charge(ctx, 5);
    v0 = 0x10000000;
    v1 = 0x10000000;
    v0 = v0 | 0x2000;
    v1 = v1 | 0x2010;
    sw(zero, v0, 0);  // 0x10002000
    for (;;) {
        // 0x00502d18
        charge(ctx, 7);
        lw(v0, v1, 0);
        if (i64(v0) >= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00502d34
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00502E50 _sceAddIntcHandler_0 -- 16 bytes; leaf frame (no stack)
// Kernel syscall wrapper: AddIntcHandler (16).
void _sceAddIntcHandler_0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00502e50
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 16;
    syscall(ctx, 0x502E54u);
}

// 0x00502E70 _sceAddDmacHandler -- 16 bytes; leaf frame (no stack)
// Kernel syscall wrapper: AddDmacHandler (18).
void _sceAddDmacHandler(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00502e70
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 18;
    syscall(ctx, 0x502E74u);
}

// 0x00502E80 _sceAddDmacHandler_0 -- 16 bytes; leaf frame (no stack)
// Kernel syscall wrapper: AddDmacHandler (18), the second copy.
void _sceAddDmacHandler_0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00502e80
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 18;
    syscall(ctx, 0x502E84u);
}

// 0x00502EA0 _sce_EnableIntc -- 16 bytes; leaf frame (no stack)
// Kernel syscall wrapper: EnableIntc (20).
void _sce_EnableIntc(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00502ea0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 20;
    syscall(ctx, 0x502EA4u);
}

// 0x00502EC0 _sce_EnableDmac -- 16 bytes; leaf frame (no stack)
// Kernel syscall wrapper: EnableDmac (22).
void _sce_EnableDmac(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00502ec0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 22;
    syscall(ctx, 0x502EC4u);
}

// 0x00502ED0 _sce_DisableDmac -- 16 bytes; leaf frame (no stack)
// Kernel syscall wrapper: DisableDmac (23).
void _sce_DisableDmac(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00502ed0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 23;
    syscall(ctx, 0x502ED4u);
}

// 0x00502F80 _sceStartThread -- 16 bytes; leaf frame (no stack)
// Kernel syscall wrapper: StartThread (34).
void _sceStartThread(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00502f80
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 34;
    syscall(ctx, 0x502F84u);
}

// 0x00503070 _sceiReferThreadStatus -- 16 bytes; leaf frame (no stack)
// Kernel syscall wrapper: iReferThreadStatus (-49).
void _sceiReferThreadStatus(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503070
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = si(-49);
    syscall(ctx, 0x503074u);
}

// 0x005030A0 _sce_iWakeupThread -- 16 bytes; leaf frame (no stack)
// Kernel syscall wrapper: iWakeupThread (-52).
void _sce_iWakeupThread(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x005030a0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = si(-52);
    syscall(ctx, 0x5030A4u);
}

// 0x00503140 _sceEndOfHeap -- 16 bytes; leaf frame (no stack)
// Kernel syscall wrapper: EndOfHeap (62).
void _sceEndOfHeap(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503140
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 62;
    syscall(ctx, 0x503144u);
}

// 0x005031B0 _scePollSema -- 16 bytes; leaf frame (no stack)
// Kernel syscall wrapper: PollSema (69).
void _scePollSema(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x005031b0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 69;
    syscall(ctx, 0x5031B4u);
}

// 0x00503200 _sceSetOsdConfigParam -- 16 bytes; leaf frame (no stack)
// Kernel syscall wrapper: SetOsdConfigParam (74).
void _sceSetOsdConfigParam(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503200
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 74;
    syscall(ctx, 0x503204u);
}

// 0x00503210 _sceGetOsdConfigParam -- 16 bytes; leaf frame (no stack)
// Kernel syscall wrapper: GetOsdConfigParam (75).
void _sceGetOsdConfigParam(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503210
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 75;
    syscall(ctx, 0x503214u);
}

// 0x005033E0 _sceFlushCache -- 16 bytes; leaf frame (no stack)
// Kernel syscall wrapper: FlushCache (100).
void _sceFlushCache(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x005033e0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 100;
    syscall(ctx, 0x5033E4u);
}

// 0x00503430 _sceSifStopDma -- 16 bytes; leaf frame (no stack)
// Kernel syscall wrapper: SifStopDma (107).
void _sceSifStopDma(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503430
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 107;
    syscall(ctx, 0x503434u);
}

// 0x005034A0 _sceGsPutIMR -- 16 bytes; leaf frame (no stack)
// Kernel syscall wrapper: GsPutIMR (113).
void _sceGsPutIMR(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x005034a0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 113;
    syscall(ctx, 0x5034A4u);
}

// 0x00503500 _sceSifDmaStat -- 16 bytes; leaf frame (no stack)
// Kernel syscall wrapper: SifDmaStat (118).
void _sceSifDmaStat(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503500
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 118;
    syscall(ctx, 0x503504u);
}

// 0x00503520 _sceSifSetDma -- 16 bytes; leaf frame (no stack)
// Kernel syscall wrapper: SifSetDma (119).
void _sceSifSetDma(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503520
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 119;
    syscall(ctx, 0x503524u);
}

// 0x00503540 _sceSifSetDChain -- 16 bytes; leaf frame (no stack)
// Kernel syscall wrapper: SifSetDChain (120).
void _sceSifSetDChain(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503540
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 120;
    syscall(ctx, 0x503544u);
}

// 0x00503550 _isceSifSetDChain -- 16 bytes; leaf frame (no stack)
// Kernel syscall wrapper: iSifSetDChain (-120).
void _isceSifSetDChain(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503550
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = si(-120);
    syscall(ctx, 0x503554u);
}

// 0x00503560 _sceSifSetReg -- 16 bytes; leaf frame (no stack)
// Kernel syscall wrapper: SifSetReg (121).
void _sceSifSetReg(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503560
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 121;
    syscall(ctx, 0x503564u);
}

// 0x00503570 _sceSifGetReg -- 16 bytes; leaf frame (no stack)
// Kernel syscall wrapper: SifGetReg (122).
void _sceSifGetReg(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503570
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 122;
    syscall(ctx, 0x503574u);
}

// 0x005035F0 VSync -- 144 bytes; frame 0x10: ra sp+0x0
// Waits for the next V-blank start: acknowledges INTC bit 2, spins until it is set again, acknowledges it.
void VSync(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005035f0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x5035F8u, gen::fn_DIntr_0050d3a0);
    v1 = 0x10000000;
    a0 = 4;
    v1 = v1 | 0xF000;
    sw(a0, v1, 0);  // 0x1000F000
    sync(ctx, 0);
    v1 = 0x10000000;
    if (v0 != 0) {
        // 0x0050361c
        charge(ctx, 3);
        jal(ctx, 0x50361Cu, gen::fn_EIntr_0050d3f0);
        v1 = 0x10000000;
    }
    // 0x00503628
    charge(ctx, 2);
    v1 = v1 | 0xF000;
    for (;;) {
        // 0x00503630
        charge(ctx, 7);
        lw(v0, v1, 0);
        v0 = v0 & 0x4;
        if (v0 != 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0050364c
    charge(ctx, 9);
    jal(ctx, 0x50364Cu, gen::fn_DIntr_0050d3a0);
    v1 = 0x10000000;
    a0 = 4;
    v1 = v1 | 0xF000;
    sw(a0, v1, 0);  // 0x1000F000
    sync(ctx, 0);
    ld(ra, sp, 0x0);
    if (v0 == 0) {
        // 0x00503678
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00503670
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
    gen::fn_EIntr_0050d3f0(ctx);  // tail call
}

// 0x00503860 sbrk -- 172 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20, s1 sp+0x10, s0 sp+0x0
// newlib's sbrk: with interrupts off, moves the heap end (0x77F494) by a0 bytes when it stays within EndOfHeap;
// returns the old end, or -1 when it does not fit.
void sbrk(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00503860
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sd(s2, sp, 0x20);
    sd(s1, sp, 0x10);
    sd(s0, sp, 0x0);
    mfc0(s1, 12);
    v0 = 0x10000;
    s1 = s1 & v0;
    s2 = 0x780000;
    if (s1 == 0) {
        // 0x005038ac
        charge(ctx, 1);
        lw(v0, s2, -2924);
    } else {
        for (;;) {
            // 0x00503888
            charge(ctx, 7);
            di(ctx);
            sync(ctx, 16);
            mfc0(v0, 12);
            v1 = 0x10000;
            v0 = v0 & v1;
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x005038a4
        charge(ctx, 2);
        lw(v0, s2, -2924);
    }
    // 0x005038b0
    charge(ctx, 5);
    s0 = addu(v0, a0);
    jal(ctx, 0x5038B0u, gen::fn__sceEndOfHeap_00503140);
    v0 = sltu(v0, s0);
    cc = v0 == 0;  // the condition, before the delay slot changes it
    lw(v0, s2, -2924);
    if (cc) {
        // 0x005038e8
        charge(ctx, 2);
        sw(s0, s2, -2924);
        if (s1 != 0) {
            // 0x005038f0
            charge(ctx, 1);
            ei(ctx);
        }
    } else {
        // 0x005038c4
        charge(ctx, 5);
        jal(ctx, 0x5038C4u, gen::fn_sub_51F690_0051f690);
        v1 = 12;
        sw(v1, v0, 0);
        if (s1 != 0) {
            // 0x005038d8
            charge(ctx, 1);
            ei(ctx);
        }
        // 0x005038dc
        charge(ctx, 3);
        v0 = lui(0xFFFF);
        v0 = v0 | 0xFFFF;
    }
    // 0x005038f4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x005039B0 _sceSDC -- 164 bytes; leaf frame (no stack)
// Walks the data cache by index (both ways): each line whose tag address lies in [a0, a1] is written back and
// invalidated (DHWBIN); the caller holds interrupts off.
void _sceSDC(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x005039b0
    enter(ctx, 4);  // entry check point + this block's cycles
    a3 = lui(0xFFFF);
    a2 = 0;
    a3 = a3 | 0xF000;
    for (;;) {
        // 0x005039c0
        charge(ctx, 10);
        sync(ctx, 0);
        cache(ctx, 16, a2, 0);
        sync(ctx, 0);
        mfc0(v0, 28);
        v0 = v0 & a3;
        v0 = addu(v0, a2);
        v1 = sltu(a1, v0);
        v0 = sltu(v0, a0);
        if (v0 == 0) {
            // 0x005039e8
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x005039f0
                charge(ctx, 3);
                sync(ctx, 0);
                cache(ctx, 20, a2, 0);
                sync(ctx, 0);
            }
        }
        // 0x005039fc
        charge(ctx, 10);
        sync(ctx, 0);
        cache(ctx, 16, a2, 1);
        sync(ctx, 0);
        mfc0(v0, 28);
        v0 = v0 & a3;
        v0 = addu(v0, a2);
        v1 = sltu(a1, v0);
        v0 = sltu(v0, a0);
        if (v0 == 0) {
            // 0x00503a24
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x00503a2c
                charge(ctx, 3);
                sync(ctx, 0);
                cache(ctx, 20, a2, 1);
                sync(ctx, 0);
            }
        }
        // 0x00503a38
        charge(ctx, 5);
        sync(ctx, 0);
        a2 = addiu(a2, 64);
        v0 = slti(a2, 4096);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00503a4c
    charge(ctx, 2);
}

// 0x00503A58 SyncDCache -- 124 bytes; frame 0x40: s2 sp+0x20, s1 sp+0x10, ra sp+0x30, s0 sp+0x0
// SyncDCache: _sceSDC on the 64-byte aligned range with interrupts off (DIntr / EIntr).
void SyncDCache(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00503a58
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s2, sp, 0x20);
    sd(s1, sp, 0x10);
    s2 = a0;
    sd(ra, sp, 0x30);
    s1 = a1;
    sd(s0, sp, 0x0);
    mfc0(s0, 12);
    v0 = 0x10000;
    s0 = s0 & v0;
    if (s0 != 0) {
        // 0x00503a88
        charge(ctx, 2);
        jal(ctx, 0x503A88u, gen::fn_DIntr_0050d3a0);
    }
    // 0x00503a90
    charge(ctx, 7);
    a0 = lui(0xFFFF);
    a0 = a0 | 0xFFC0;
    a1 = s1 & a0;
    a0 = s2 & a0;
    jal(ctx, 0x503A9Cu, gen::fn__sceSDC_005039b0);
    ld(ra, sp, 0x30);
    if (s0 == 0) {
        // 0x00503ac0
        charge(ctx, 5);
        ld(s2, sp, 0x20);
        ld(s1, sp, 0x10);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
        return;
    }
    // 0x00503aac
    charge(ctx, 5);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
    gen::fn_EIntr_0050d3f0(ctx);  // tail call
}

// 0x00503AF0 _sceIDC -- 164 bytes; leaf frame (no stack)
// Walks the data cache by index (both ways): each line whose tag address lies in [a0, a1] is invalidated (DHIN);
// the caller holds interrupts off.
void _sceIDC(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x00503af0
    enter(ctx, 4);  // entry check point + this block's cycles
    a3 = lui(0xFFFF);
    a2 = 0;
    a3 = a3 | 0xF000;
    for (;;) {
        // 0x00503b00
        charge(ctx, 10);
        sync(ctx, 0);
        cache(ctx, 16, a2, 0);
        sync(ctx, 0);
        mfc0(v0, 28);
        v0 = v0 & a3;
        v0 = addu(v0, a2);
        v1 = sltu(a1, v0);
        v0 = sltu(v0, a0);
        if (v0 == 0) {
            // 0x00503b28
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x00503b30
                charge(ctx, 3);
                sync(ctx, 0);
                cache(ctx, 22, a2, 0);
                sync(ctx, 0);
            }
        }
        // 0x00503b3c
        charge(ctx, 10);
        sync(ctx, 0);
        cache(ctx, 16, a2, 1);
        sync(ctx, 0);
        mfc0(v0, 28);
        v0 = v0 & a3;
        v0 = addu(v0, a2);
        v1 = sltu(a1, v0);
        v0 = sltu(v0, a0);
        if (v0 == 0) {
            // 0x00503b64
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x00503b6c
                charge(ctx, 3);
                sync(ctx, 0);
                cache(ctx, 22, a2, 1);
                sync(ctx, 0);
            }
        }
        // 0x00503b78
        charge(ctx, 5);
        sync(ctx, 0);
        a2 = addiu(a2, 64);
        v0 = slti(a2, 4096);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00503b8c
    charge(ctx, 2);
}

// 0x00503B98 InvalidDCache -- 124 bytes; frame 0x40: s2 sp+0x20, s1 sp+0x10, ra sp+0x30, s0 sp+0x0
// InvalidDCache: _sceIDC on the 64-byte aligned range with interrupts off (DIntr / EIntr).
void InvalidDCache(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00503b98
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s2, sp, 0x20);
    sd(s1, sp, 0x10);
    s2 = a0;
    sd(ra, sp, 0x30);
    s1 = a1;
    sd(s0, sp, 0x0);
    mfc0(s0, 12);
    v0 = 0x10000;
    s0 = s0 & v0;
    if (s0 != 0) {
        // 0x00503bc8
        charge(ctx, 2);
        jal(ctx, 0x503BC8u, gen::fn_DIntr_0050d3a0);
    }
    // 0x00503bd0
    charge(ctx, 7);
    a0 = lui(0xFFFF);
    a0 = a0 | 0xFFC0;
    a1 = s1 & a0;
    a0 = s2 & a0;
    jal(ctx, 0x503BDCu, gen::fn__sceIDC_00503af0);
    ld(ra, sp, 0x30);
    if (s0 == 0) {
        // 0x00503c00
        charge(ctx, 5);
        ld(s2, sp, 0x20);
        ld(s1, sp, 0x10);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
        return;
    }
    // 0x00503bec
    charge(ctx, 5);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
    gen::fn_EIntr_0050d3f0(ctx);  // tail call
}

// 0x00503C30 QueryIntrContext -- 16 bytes; leaf frame (no stack)
// Returns (Status ^ 1) & 1: 1 while COP0 Status.IE is clear (an interrupt context).
void QueryIntrContext(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00503c30
    enter(ctx, 4);  // entry check point + this block's cycles
    mfc0(v0, 12);
    v0 = v0 ^ 0x1;
    v0 = v0 & 0x1;
}

// 0x00503D78 EnableDmac -- 104 bytes; frame 0x30: s1 sp+0x10, ra sp+0x20, s0 sp+0x0
// EnableDmac: the syscall with interrupts off (DIntr / EIntr).
void EnableDmac(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00503d78
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
        // 0x00503da0
        charge(ctx, 2);
        jal(ctx, 0x503DA0u, gen::fn_DIntr_0050d3a0);
    }
    // 0x00503da8
    charge(ctx, 6);
    a0 = s1;
    jal(ctx, 0x503DA8u, gen::fn__sce_EnableDmac_00502ec0);
    s1 = v0;
    sync(ctx, 0);
    v0 = s1;
    if (s0 != 0) {
        // 0x00503dc0
        charge(ctx, 3);
        jal(ctx, 0x503DC0u, gen::fn_EIntr_0050d3f0);
        v0 = s1;
    }
    // 0x00503dcc (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00505FC0 sceSifSetDmaInternal -- 200 bytes; frame 0x240: s1 sp+0x210, s2 sp+0x220, ra sp+0x230, s0 sp+0x200
// libsifcmd: builds the SIF DMA list (at most 32 entries) plus the trailing 16-byte packet that tells the IOP
// about it, and issues it (SifSetDma or iSifSetDma by a3).
void sceSifSetDmaInternal(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00505fc0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x240);
    sd(s1, sp, 0x210);
    sd(s2, sp, 0x220);
    s1 = a1;
    sd(ra, sp, 0x230);
    s2 = a2;
    v0 = slti(s1, 32);
    sd(s0, sp, 0x200);
    if (v0 == 0) {
        // 0x0050606c
        charge(ctx, 2);
        v0 = 0;
        ld(ra, sp, 0x230);
    } else {
        // 0x00505fe4
        charge(ctx, 24);
        s0 = sll(s1, 4);
        a1 = a0;
        a0 = sp;
        a2 = s0;
        jal(ctx, 0x505FF0u, gen::fn_memcpy_00521250);
        s1 = addiu(s1, 1);
        v0 = 0x960000;
        v1 = 0x7C0000;
        v1 = addiu(v1, -8960);  // &0x7BDD00
        lw(a1, v0, 27232);  // 0x966A60
        a0 = addu(sp, s0);
        v0 = addiu(sp, 0x4);
        sw(v1, a0, 0);
        v0 = addu(v0, s0);
        v1 = addiu(sp, 0x8);
        sw(a1, v0, 0);
        v1 = addu(v1, s0);
        a0 = 16;
        sw(a0, v1, 0);
        v0 = addiu(sp, 0xC);
        v0 = addu(v0, s0);
        v1 = 68;
        sw(v1, v0, 0);
        if (s2 != 0) {
            // 0x00506058
            charge(ctx, 5);
            a1 = s1;
            a0 = sp;
            jal(ctx, 0x50605Cu, gen::fn__isceSifSetDma_00503530);
            ld(ra, sp, 0x230);
        } else {
            // 0x00506044
            charge(ctx, 5);
            a1 = s1;
            a0 = sp;
            jal(ctx, 0x506048u, gen::fn__sceSifSetDma_00503520);
            ld(ra, sp, 0x230);
        }
    }
    // 0x00506074 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s2, sp, 0x220);
    ld(s1, sp, 0x210);
    ld(s0, sp, 0x200);
    sp = addiu(sp, 0x240);
}

// 0x00506088 sceSifSetDma -- 136 bytes; frame 0x30: s1 sp+0x10, s0 sp+0x0, ra sp+0x20
// libsifcmd's public sceSifSetDma: through sceSifSetDmaInternal when sifcmd is up, else the raw syscall
// (interrupts off around it).
void sceSifSetDma(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00506088
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x10);
    sd(s0, sp, 0x0);
    s1 = a1;
    sd(ra, sp, 0x20);
    s0 = a0;
    jal(ctx, 0x50609Cu, gen::fn_DIntr_0050d3a0);
    a0 = v0;
    v0 = 0x780000;
    lw(v1, v0, -2904);  // 0x77F4A8
    if (v1 == 0) {
        // 0x005060e0
        charge(ctx, 2);
        cc = a0 == 0;  // the condition, before the delay slot changes it
        a0 = s0;
        if (!cc) {
            // 0x005060e8
            charge(ctx, 3);
            jal(ctx, 0x5060E8u, gen::fn_EIntr_0050d3f0);
            a0 = s0;
        }
        // 0x005060f4
        charge(ctx, 3);
        a1 = s1;
        jal(ctx, 0x5060F4u, gen::fn__sceSifSetDma_00503520);
        ld(ra, sp, 0x20);
    } else {
        // 0x005060b8
        charge(ctx, 2);
        cc = a0 == 0;  // the condition, before the delay slot changes it
        a0 = s0;
        if (!cc) {
            // 0x005060c0
            charge(ctx, 3);
            jal(ctx, 0x5060C0u, gen::fn_EIntr_0050d3f0);
            a0 = s0;
        }
        // 0x005060cc
        charge(ctx, 5);
        a1 = s1;
        a2 = 0;
        jal(ctx, 0x5060D0u, gen::fn_sceSifSetDmaInternal_00505fc0);
        ld(ra, sp, 0x20);
    }
    // 0x00506100 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00506148 sceSifInitCmd -- 640 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40, s3 sp+0x30, s2 sp+0x20, s1 sp+0x10, s0 sp+0x0
// libsifcmd init: the command buffer and system handlers, the DMAC ch5 handler, and the EE / IOP buffer-address
// exchange through the SIF registers and command 0x80000002.
void sceSifInitCmd(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00506148
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sd(s4, sp, 0x40);
    sd(s3, sp, 0x30);
    sd(s2, sp, 0x20);
    sd(s1, sp, 0x10);
    link(ctx, 0x506160u);  // $ra first: the delay slot below depends on it
    sd(s0, sp, 0x0);
    call(ctx, gen::fn_DIntr_0050d3a0);
    t2 = 0x780000;
    lw(v0, t2, -2904);  // 0x77F4A8
    s3 = 0x960000;
    if (v0 != 0) {
        // 0x00506178
        charge(ctx, 8);
        ld(ra, sp, 0x50);
        ld(s4, sp, 0x40);
        ld(s3, sp, 0x30);
        ld(s2, sp, 0x20);
        ld(s1, sp, 0x10);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x60);
        gen::fn_EIntr_0050d3f0(ctx);  // tail call
        return;
    }
    // 0x00506198
    charge(ctx, 26);
    a1 = 0x960000;
    v0 = 0x20000000;
    a1 = addiu(a1, 27136);  // &0x966A00
    a2 = addiu(s3, 27008);
    s2 = 0x960000;
    a1 = a1 | v0;
    a2 = a2 | v0;
    v1 = 1;
    t1 = 0x960000;
    a0 = 0x960000;
    v0 = addiu(s2, 27224);  // &0x966A58
    sw(v1, t2, -2904);
    a0 = addiu(a0, 27648);  // &0x966C00
    t0 = addiu(t1, 27264);  // &0x966A80
    sw(a2, s2, 27224);  // 0x966A58
    a3 = 32;
    sw(a0, v0, 28);  // 0x966A74
    v1 = t0;
    sw(a1, v0, 4);  // 0x966A5C
    sw(a3, v0, 16);  // 0x966A68
    a0 = addiu(v1, 384);  // &0x966C00
    sw(zero, v0, 8);  // 0x966A60
    s4 = 0x960000;
    sw(t0, v0, 12);  // 0x966A64
    sw(zero, v0, 20);  // 0x966A6C
    sw(zero, v0, 24);  // 0x966A70
    for (;;) {
        // 0x00506200
        charge(ctx, 7);
        sw(zero, v1, 0);
        sw(zero, v1, 4);
        v1 = addiu(v1, 12);
        v0 = slt(v1, a0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0050621c
    charge(ctx, 5);
    v0 = 0x960000;
    s0 = 31;
    v0 = addiu(v0, 27648);  // &0x966C00
    v0 = addiu(v0, 124);  // &0x966C7C
    for (;;) {
        // 0x00506230
        charge(ctx, 7);
        sw(zero, v0, 0);
        s0 = addiu(s0, -1);
        v0 = addiu(v0, -4);
        if (i64(s0) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0050624c
    charge(ctx, 20);
    v0 = 0x500000;
    v1 = 0x500000;
    v0 = addiu(v0, 24424);  // &_change_addr
    a0 = addiu(t1, 27264);
    v1 = addiu(v1, 24392);  // &_set_sreg
    s1 = addiu(s2, 27224);
    sw(v0, t1, 27264);
    s0 = 32;
    sw(v1, a0, 12);
    sw(s1, a0, 16);
    link(ctx, 0x506274u);  // $ra first: the delay slot below depends on it
    sw(s1, a0, 4);
    call(ctx, gen::fn_EIntr_0050d3f0);
    a0 = 0;
    jal(ctx, 0x50627Cu, gen::fn__sceFlushCache_005033e0);
    v0 = 0x10000000;
    v0 = v0 | 0xE010;
    lw(v1, v0, 0);  // 0x1000E010
    v1 = v1 & 0x20;
    v0 = 0x10000000;
    if (v1 != 0) {
        // 0x0050629c
        charge(ctx, 3);
        at = 0x10010000;
        sw(s0, at, -8176);  // 0x1000E010
        v0 = 0x10000000;
    }
    // 0x005062a8
    charge(ctx, 5);
    v0 = v0 | 0xC000;
    lw(v1, v0, 0);
    v1 = v1 & 0x100;
    a1 = 0x500000;
    if (v1 == 0) {
        // 0x005062bc
        charge(ctx, 3);
        jal(ctx, 0x5062BCu, gen::fn__sceSifSetDChain_00503540);
        a1 = 0x500000;
    }
    // 0x005062c8
    charge(ctx, 13);
    a0 = 5;
    a1 = addiu(a1, 26288);
    a2 = 0;
    jal(ctx, 0x5062D0u, gen::fn__sceAddDmacHandler_00502e70);
    v1 = 0x960000;
    a0 = 5;
    link(ctx, 0x5062E0u);  // $ra first: the delay slot below depends on it
    sw(v0, v1, 27220);
    call(ctx, gen::fn_EnableDmac_00503d78);
    a0 = lui(0x8000);
    jal(ctx, 0x5062ECu, gen::fn__sceSifGetReg_00503570);
    sw(v0, s1, 8);
    if (v0 != 0) {
        // 0x005062fc
        charge(ctx, 16);
        a1 = addiu(s4, 27200);
        v0 = addiu(s3, 27008);
        ld(ra, sp, 0x50);
        a0 = lui(0x8000);
        ld(s4, sp, 0x40);
        a2 = 20;
        ld(s3, sp, 0x30);
        a3 = 0;
        ld(s2, sp, 0x20);
        t0 = 0;
        ld(s1, sp, 0x10);
        t1 = 0;
        ld(s0, sp, 0x0);
        sw(v0, a1, 16);
        sp = addiu(sp, 0x60);
        gen::fn_sub_506630_00506630(ctx);  // tail call
        return;
    }
    // 0x0050633c
    charge(ctx, 1);
    s0 = 0x20000;
    for (;;) {
        // 0x00506340
        charge(ctx, 5);
        a0 = 4;
        jal(ctx, 0x506340u, gen::fn__sceSifGetReg_00503570);
        v0 = v0 & s0;
        a0 = 2;
        if (v0 != 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00506354
    charge(ctx, 29);
    s0 = addiu(s2, 27224);
    jal(ctx, 0x506354u, gen::fn__sceSifGetReg_00503570);
    sw(v0, s0, 8);
    a0 = lui(0x8000);
    a1 = v0;
    jal(ctx, 0x506364u, gen::fn__sceSifSetReg_00503560);
    a0 = lui(0x8000);
    a1 = s0;
    a0 = a0 | 0x1;
    jal(ctx, 0x506374u, gen::fn__sceSifSetReg_00503560);
    v1 = addiu(s4, 27200);
    v0 = addiu(s3, 27008);
    a0 = lui(0x8000);
    ld(ra, sp, 0x50);
    ld(s4, sp, 0x40);
    a1 = v1;
    ld(s3, sp, 0x30);
    a0 = a0 | 0x2;
    ld(s2, sp, 0x20);
    a2 = 20;
    ld(s1, sp, 0x10);
    a3 = 0;
    ld(s0, sp, 0x0);
    t0 = 0;
    sw(v0, v1, 16);
    t1 = 0;
    sw(zero, v1, 12);
    sp = addiu(sp, 0x60);
    gen::fn_sub_506630_00506630(ctx);  // tail call
}

// 0x005066B0 sub_5066B0 -- 328 bytes; frame 0xA0: s1 sp+0x80, ra sp+0x90, s0 sp+0x70
// libsifcmd's ch5 (fromSIF0) DMAC handler (data reference): copies the received packet out of the command buffer,
// re-arms the channel (iSifSetDChain) and calls the registered command handler (system or user table).
void sub_5066B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005066b0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    v1 = 0x960000;
    sd(s1, sp, 0x80);
    sd(ra, sp, 0x90);
    s1 = addiu(v1, 27224);  // &0x966A58
    sd(s0, sp, 0x70);
    lw(a3, v1, 27224);  // 0x966A58
    lbu(v0, a3, 0);
    a1 = v0 & 0xFF;
    v0 = 0;
    if (a1 != 0) {
        // 0x005066dc
        charge(ctx, 10);
        v0 = addiu(a1, 15);
        v1 = si(-1);
        a0 = addiu(a1, 30);
        v1 = slt(v1, v0);
        if (v1 != 0) a0 = v0;
        a2 = a3;
        a1 = sra(a0, 4);
        sb(zero, a3, 0);
        a0 = a1;
        if (i64(a1) > 0) {
            // 0x00506704
            charge(ctx, 1);
            v1 = sp;
            for (;;) {
                // 0x00506708
                charge(ctx, 7);
                lq(v0, a2, 0);
                a0 = addiu(a0, -1);
                a2 = addiu(a2, 16);
                sq(v0, v1, 0);
                v1 = addiu(v1, 16);
                if (a0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x00506724
        charge(ctx, 5);
        jal(ctx, 0x506724u, gen::fn__isceSifSetDChain_00503550);
        lw(v1, sp, 0x8);
        if (i64(v1) >= 0) {
            // 0x00506784
            charge(ctx, 5);
            lw(a1, sp, 0x8);
            lw(v0, s1, 24);
            v0 = slt(a1, v0);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = 12;
            if (!cc) {
                // 0x00506798
                charge(ctx, 6);
                lw(v1, s1, 20);
                mult(a1, a1, v0);
                v0 = addu(a1, v1);
                lw(a2, v0, 0);
                if (a2 != 0) {
                    // 0x005067b0
                    charge(ctx, 4);
                    lw(v1, v0, 8);
                    s0 = gp;
                    gp = v1;
                    lw(v0, s1, 20);
                L_005067c0:
                    charge(ctx, 6);
                    a0 = sp;
                    v0 = addu(a1, v0);
                    jt = a2.u();  // the target, read before the delay slot
                    link(ctx, 0x5067C8u);  // $ra = the return address
                    lw(a1, v0, 4);
                    call_ptr(ctx, jt);
                    v0 = gp;
                    gp = s0;
                }
            }
        } else {
            // 0x00506738
            charge(ctx, 8);
            lw(v0, sp, 0x8);
            v1 = 0x7FFF0000;
            v1 = v1 | 0xFFFF;
            lw(a0, s1, 16);
            a1 = v0 & v1;
            a0 = slt(a1, a0);
            v0 = 12;
            if (a0 != 0) {
                // 0x00506758
                charge(ctx, 6);
                lw(v1, s1, 12);
                mult(a1, a1, v0);
                v0 = addu(a1, v1);
                lw(a2, v0, 0);
                if (a2 != 0) {
                    // 0x00506770
                    charge(ctx, 5);
                    lw(v1, v0, 8);
                    s0 = gp;
                    gp = v1;
                    lw(v0, s1, 12);
                    goto L_005067c0;
                }
            }
        }
        // 0x005067d8
        charge(ctx, 3);
        sync(ctx, 0);
        ei(ctx);
        v0 = 0;
    }
    // 0x005067e4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x90);
    ld(s1, sp, 0x80);
    ld(s0, sp, 0x70);
    sp = addiu(sp, 0xA0);
}

// 0x005068A8 sceSifInitRpc -- 412 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20, s1 sp+0x10, s0 sp+0x0
// libsifrpc init: sifcmd init, the RPC packet pools and the system command handlers; once only.
void sceSifInitRpc(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005068a8
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sd(s2, sp, 0x20);
    sd(s1, sp, 0x10);
    link(ctx, 0x5068B8u);  // $ra first: the delay slot below depends on it
    sd(s0, sp, 0x0);
    call(ctx, gen::fn_DIntr_0050d3a0);
    v1 = 0x780000;
    lw(v0, v1, -2896);  // 0x77F4B0
    s1 = 1;
    if (v0 != 0) {
        // 0x005068d0
        charge(ctx, 6);
        ld(ra, sp, 0x30);
        ld(s2, sp, 0x20);
        ld(s1, sp, 0x10);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
        gen::fn_EIntr_0050d3f0(ctx);  // tail call
        return;
    }
    // 0x005068e8
    charge(ctx, 60);
    link(ctx, 0x5068E8u);  // $ra first: the delay slot below depends on it
    sw(s1, v1, -2896);
    call(ctx, gen::fn_EIntr_0050d3f0);
    jal(ctx, 0x5068F0u, gen::fn_sceSifInitCmd_00506148);
    jal(ctx, 0x5068F8u, gen::fn_DIntr_0050d3a0);
    v1 = 0x960000;
    t0 = 0x970000;
    s2 = addiu(v1, 27776);  // &0x966C80
    a2 = 0x960000;
    a3 = 0x960000;
    s0 = addiu(t0, -31616);  // &0x968480
    v1 = 32;
    v0 = 0x20000000;
    a2 = addiu(a2, 29824);  // &0x967480
    a3 = addiu(a3, 31872);  // &0x967C80
    a2 = a2 | v0;
    a3 = a3 | v0;
    sw(v1, s0, 32);  // 0x9684A0
    v0 = s2 | v0;
    sw(s1, t0, -31616);  // 0x968480
    a1 = 0x500000;
    sw(a2, s0, 20);  // 0x968494
    a0 = lui(0x8000);
    sw(v0, s0, 4);  // 0x968484
    a1 = addiu(a1, 27560);  // &_request_end
    sw(a3, s0, 28);  // 0x96849C
    a0 = a0 | 0x8;
    a2 = s0;
    sw(v1, s0, 8);  // 0x968488
    sw(zero, s0, 12);  // 0x96848C
    sw(zero, s0, 16);  // 0x968490
    sw(v1, s0, 24);  // 0x968498
    link(ctx, 0x50696Cu);  // $ra first: the delay slot below depends on it
    sw(zero, s0, 36);  // 0x9684A4
    call(ctx, gen::fn_sub_506430_00506430);
    a1 = 0x500000;
    a0 = lui(0x8000);
    a1 = addiu(a1, 28544);  // &_request_bind
    a0 = a0 | 0x9;
    a2 = s0;
    jal(ctx, 0x506984u, gen::fn_sub_506430_00506430);
    a1 = 0x500000;
    a0 = lui(0x8000);
    a1 = addiu(a1, 29088);  // &_request_call
    a0 = a0 | 0xA;
    a2 = s0;
    jal(ctx, 0x50699Cu, gen::fn_sub_506430_00506430);
    a1 = 0x500000;
    a0 = lui(0x8000);
    a1 = addiu(a1, 27832);  // &_request_rdata
    a2 = s0;
    a0 = a0 | 0xC;
    jal(ctx, 0x5069B4u, gen::fn_sub_506430_00506430);
    jal(ctx, 0x5069BCu, gen::fn_EIntr_0050d3f0);
    a0 = lui(0x8000);
    a0 = a0 | 0x2;
    jal(ctx, 0x5069C8u, gen::fn__sceSifGetReg_00503570);
    ld(ra, sp, 0x30);
    if (v0 != 0) {
        // 0x00506a30
        charge(ctx, 5);
        ld(s2, sp, 0x20);
        ld(s1, sp, 0x10);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
        return;
    }
    // 0x005069d8
    charge(ctx, 10);
    a1 = addiu(s2, 64);
    a0 = lui(0x8000);
    sw(s1, a1, 12);
    a0 = a0 | 0x2;
    a2 = 16;
    a3 = 0;
    t0 = 0;
    t1 = 0;
    jal(ctx, 0x5069F4u, gen::fn_sub_506630_00506630);
    for (;;) {
        // 0x00506a00
        charge(ctx, 4);
        a0 = 0;
        jal(ctx, 0x506A00u, gen::fn_sceSifGetSreg_00505f78);
        ld(ra, sp, 0x30);
        if (v0 != 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00506a10
    charge(ctx, 8);
    a0 = lui(0x8000);
    ld(s2, sp, 0x20);
    a1 = 1;
    ld(s1, sp, 0x10);
    a0 = a0 | 0x2;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
    gen::fn__sceSifSetReg_00503560(ctx);  // tail call
}

// 0x00506BA8 _request_end -- 204 bytes; frame 0x40: s2 sp+0x20, ra sp+0x30, s1 sp+0x10, s0 sp+0x0
// libsifrpc's end-of-request command handler (data reference): copies the result state, runs the end callback or
// signals the waiting semaphore, and frees the packet.
void _request_end(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00506ba8
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = lui(0x8000);
    sd(s2, sp, 0x20);
    v0 = v0 | 0xA;
    sd(ra, sp, 0x30);
    s2 = a0;
    sd(s1, sp, 0x10);
    sd(s0, sp, 0x0);
    lw(v1, s2, 32);
    cc = v1 == v0;  // the condition, before the delay slot changes it
    v0 = sltu(v0, v1);
    if (cc) {
        // 0x00506bf4
        charge(ctx, 4);
        lw(s1, s2, 28);
        lw(v0, s1, 28);
        if (v0 == 0) {
            lw(a0, s1, 8);
        } else {
            // 0x00506c04
            charge(ctx, 10);
            lw(v0, s1, 24);
            s0 = gp;
            gp = v0;
            lw(v0, s1, 28);
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x506C14u);  // $ra = the return address
            lw(a0, s1, 32);
            call_ptr(ctx, jt);
            v1 = gp;
            gp = s0;
            lw(s1, s2, 28);
        L_00506c3c:
            charge(ctx, 1);
            lw(a0, s1, 8);
        }
    } else {
        // 0x00506bd4
        charge(ctx, 2);
        lw(s1, s2, 28);
        if (v0 != 0) {
            goto L_00506c3c;
        }
        // 0x00506bdc
        charge(ctx, 4);
        v0 = lui(0x8000);
        v0 = v0 | 0x9;
        if (v1 == v0) {
            // 0x00506c2c
            charge(ctx, 4);
            lw(v0, s2, 36);
            sw(v0, s1, 36);
            lw(v1, s2, 40);
            sw(v1, s1, 20);
            goto L_00506c3c;
        }
        // 0x00506bec
        charge(ctx, 2);
        lw(a0, s1, 8);
    }
    // 0x00506c40
    charge(ctx, 2);
    if (i64(a0) >= 0) {
        // 0x00506c48
        charge(ctx, 2);
        jal(ctx, 0x506C48u, gen::fn__sceiSignalSema_00503190);
    }
    // 0x00506c50
    charge(ctx, 9);
    link(ctx, 0x506C50u);  // $ra first: the delay slot below depends on it
    lw(a0, s1, 0);
    call(ctx, gen::fn__sceRpcFreePacket_00506b18);
    sw(zero, s1, 0);
    ld(ra, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00507050 sceSifBindRpc -- 332 bytes; frame 0x70: s1 sp+0x30, s3 sp+0x50, s2 sp+0x40, s0 sp+0x20, ra sp+0x60
// Binds a client to an IOP RPC server: sends the bind request and waits for it (unless SIF_RPCM_NOWAIT).
void sceSifBindRpc(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00507050
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(s1, sp, 0x30);
    sd(s3, sp, 0x50);
    s1 = a0;
    sd(s2, sp, 0x40);
    a0 = 0x970000;
    sd(s0, sp, 0x20);
    s3 = a1;
    sd(ra, sp, 0x60);
    s2 = a2;
    sw(zero, s1, 16);
    a0 = addiu(a0, -31616);  // &0x968480
    link(ctx, 0x507080u);  // $ra first: the delay slot below depends on it
    sw(zero, s1, 36);
    call(ctx, gen::fn__sceRpcGetPacket_00506a70);
    s0 = v0;
    v0 = si(-1);
    if (s0 != 0) {
        // 0x00507094
        charge(ctx, 8);
        lw(v0, s0, 24);
        v1 = s2 & 0x1;
        sw(s0, s1, 0);
        sw(v0, s1, 4);
        sw(s3, s0, 32);
        sw(s0, s0, 20);
        sw(s1, s0, 28);
        if (v1 != 0) {
            // 0x00507144
            charge(ctx, 12);
            v0 = si(-1);
            a0 = lui(0x8000);
            sw(v0, s1, 8);
            a0 = a0 | 0x9;
            a1 = s0;
            a2 = 64;
            a3 = 0;
            t0 = 0;
            t1 = 0;
            jal(ctx, 0x507164u, gen::fn_sub_506630_00506630);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = 0;
            if (!cc) {
                // 0x00507174
                charge(ctx, 3);
                a0 = s0;
                jal(ctx, 0x507174u, gen::fn__sceRpcFreePacket_00506b18);
                v0 = si(-2);
            }
        } else {
            // 0x005070b4
            charge(ctx, 10);
            v0 = 0x7C0000;
            v1 = 1;
            v0 = addiu(v0, -8928);  // "SceSifrpcBind"
            sw(v1, sp, 0x4);
            sw(v0, sp, 0x14);
            a0 = sp;
            link(ctx, 0x5070CCu);  // $ra first: the delay slot below depends on it
            sw(zero, sp, 0x8);
            call(ctx, gen::fn__sceCreateSema_00503160);
            sw(v0, s1, 8);
            if (i64(v0) >= 0) {
                // 0x005070ec
                charge(ctx, 10);
                a0 = lui(0x8000);
                a1 = s0;
                a0 = a0 | 0x9;
                a2 = 64;
                a3 = 0;
                t0 = 0;
                t1 = 0;
                jal(ctx, 0x507104u, gen::fn_sub_506630_00506630);
                if (v0 != 0) {
                    // 0x0050712c
                    charge(ctx, 6);
                    link(ctx, 0x50712Cu);  // $ra first: the delay slot below depends on it
                    lw(a0, s1, 8);
                    call(ctx, gen::fn__sceWaitSema_005031a0);
                    link(ctx, 0x507134u);  // $ra first: the delay slot below depends on it
                    lw(a0, s1, 8);
                    call(ctx, gen::fn__sceDeleteSema_00503170);
                    v0 = 0;
                } else {
                    // 0x00507114
                    charge(ctx, 6);
                    a0 = s0;
                    jal(ctx, 0x507114u, gen::fn__sceRpcFreePacket_00506b18);
                    link(ctx, 0x50711Cu);  // $ra first: the delay slot below depends on it
                    lw(a0, s1, 8);
                    call(ctx, gen::fn__sceDeleteSema_00503170);
                    v0 = si(-2);
                }
            } else {
                // 0x005070dc
                charge(ctx, 4);
                a0 = s0;
                jal(ctx, 0x5070DCu, gen::fn__sceRpcFreePacket_00506b18);
                v0 = si(-3);
            }
        }
    }
    // 0x00507180 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x60);
    ld(s3, sp, 0x50);
    ld(s2, sp, 0x40);
    ld(s1, sp, 0x30);
    ld(s0, sp, 0x20);
    sp = addiu(sp, 0x70);
}

// 0x00507230 sceSifCallRpc -- 512 bytes; frame 0xC0: s1 sp+0x30, fp sp+0xA0, s7 sp+0x90, s6 sp+0x80, s5 sp+0x70, s4 sp+0x60, s3 sp+0x50, s2 sp+0x40, s0 sp+0x20, ra sp+0xB0
// Calls an IOP RPC function: flushes the buffers, sends the request (with the send / receive DMA) and waits
// for the end (unless SIF_RPCM_NOWAIT).
void sceSifCallRpc(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00507230
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(s1, sp, 0x30);
    s1 = a0;
    sd(fp, sp, 0xA0);
    sd(s7, sp, 0x90);
    a0 = 0x970000;
    sd(s6, sp, 0x80);
    fp = a2;
    sd(s5, sp, 0x70);
    s6 = a1;
    sd(s4, sp, 0x60);
    s5 = a3;
    sd(s3, sp, 0x50);
    s4 = t1;
    sd(s2, sp, 0x40);
    s3 = t2;
    sd(s0, sp, 0x20);
    s2 = t0;
    sd(ra, sp, 0xB0);
    s7 = t3;
    a0 = addiu(a0, -31616);  // &0x968480
    jal(ctx, 0x507280u, gen::fn__sceRpcGetPacket_00506a70);
    s0 = v0;
    v0 = si(-1);
    if (s0 != 0) {
        // 0x00507294
        charge(ctx, 18);
        lw(v0, sp, 0xC0);
        lw(v1, s0, 24);
        sw(v0, s1, 32);
        sw(v1, s1, 4);
        sw(s0, s1, 0);
        sw(s7, s1, 28);
        v0 = gp;
        sw(v0, s1, 24);
        v1 = fp & 0x2;
        sw(s6, s0, 32);
        sw(s2, s0, 36);
        sw(s4, s0, 40);
        sw(s3, s0, 44);
        sw(s0, s0, 20);
        lw(v0, s1, 36);
        sw(s1, s0, 28);
        sw(v0, s0, 52);
        if (v1 == 0) {
            // 0x005072dc
            charge(ctx, 2);
            v0 = slt(s2, s3);
            if (s5 != s4) {
                // 0x005072fc
                charge(ctx, 2);
                a0 = s5;
                if (i64(s2) > 0) {
                    // 0x00507304
                    charge(ctx, 2);
                    a1 = s2;
                    jal(ctx, 0x507304u, gen::fn_sub_5067F8_005067f8);
                }
                // 0x0050730c
                charge(ctx, 2);
                a0 = s4;
                if (i64(s3) > 0) {
                    // 0x00507314
                    charge(ctx, 2);
                    a1 = s3;
                    jal(ctx, 0x507314u, gen::fn_sub_5067F8_005067f8);
                }
                goto L_0050731c;
            }
            // 0x005072e4
            charge(ctx, 6);
            a1 = s3;
            a0 = s5;
            if (v0 == 0) a1 = s2;
            jal(ctx, 0x5072ECu, gen::fn_sub_5067F8_005067f8);
            v0 = fp & 0x1;
            goto L_00507320;
        }
    L_0050731c:
        charge(ctx, 1);
        v0 = fp & 0x1;
    L_00507320:
        charge(ctx, 2);
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = 0x7C0000;
        if (cc) {
            // 0x00507374
            charge(ctx, 9);
            s3 = 1;
            v0 = addiu(v0, -8912);
            sw(zero, sp, 0x8);
            sw(v0, sp, 0x14);
            a0 = sp;
            link(ctx, 0x507388u);  // $ra first: the delay slot below depends on it
            sw(s3, sp, 0x4);
            call(ctx, gen::fn__sceCreateSema_00503160);
            sw(v0, s1, 8);
            if (i64(v0) >= 0) {
                // 0x005073a8
                charge(ctx, 11);
                sw(s3, s0, 48);
                a0 = lui(0x8000);
                a3 = s5;
                t1 = s2;
                lw(t0, s1, 20);
                a0 = a0 | 0xA;
                a1 = s0;
                a2 = 64;
                jal(ctx, 0x5073C4u, gen::fn_sub_506630_00506630);
                if (v0 != 0) {
                    // 0x005073ec
                    charge(ctx, 5);
                    link(ctx, 0x5073ECu);  // $ra first: the delay slot below depends on it
                    lw(a0, s1, 8);
                    call(ctx, gen::fn__sceWaitSema_005031a0);
                    link(ctx, 0x5073F4u);  // $ra first: the delay slot below depends on it
                    lw(a0, s1, 8);
                    call(ctx, gen::fn__sceDeleteSema_00503170);
                    v0 = 0;
                } else {
                    // 0x005073d4
                    charge(ctx, 2);
                    link(ctx, 0x5073D4u);  // $ra first: the delay slot below depends on it
                    lw(a0, s1, 8);
                    call(ctx, gen::fn__sceDeleteSema_00503170);
                L_005073dc:
                    charge(ctx, 4);
                    a0 = s0;
                    jal(ctx, 0x5073DCu, gen::fn__sceRpcFreePacket_00506b18);
                    v0 = si(-2);
                }
            } else {
                // 0x00507398
                charge(ctx, 4);
                a0 = s0;
                jal(ctx, 0x507398u, gen::fn__sceRpcFreePacket_00506b18);
                v0 = si(-3);
            }
        } else {
            // 0x00507328
            charge(ctx, 2);
            v0 = 1;
            if (s7 != 0) {
                // 0x00507338
                charge(ctx, 1);
                sw(v0, s0, 48);
            } else {
                // 0x00507330
                charge(ctx, 2);
                sw(zero, s0, 48);
            }
            // 0x0050733c
            charge(ctx, 12);
            v0 = si(-1);
            a0 = lui(0x8000);
            lw(t0, s1, 20);
            a3 = s5;
            sw(v0, s1, 8);
            t1 = s2;
            a0 = a0 | 0xA;
            a1 = s0;
            a2 = 64;
            jal(ctx, 0x50735Cu, gen::fn_sub_506630_00506630);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = 0;
            if (!cc) {
                // 0x0050736c
                charge(ctx, 2);
                goto L_005073dc;
            }
        }
    }
    // 0x00507400 (the shared epilogue, written out on this path)
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

// 0x00507920 sceSifRpcLoop -- 64 bytes; frame 0x20: s0 sp+0x0, ra sp+0x10
// An EE RPC server loop: executes the queued requests, sleeping while there are none.
void sceSifRpcLoop(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00507920
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    s0 = a0;
    for (;;) {
        // 0x00507940
        charge(ctx, 4);
        a0 = s0;
        jal(ctx, 0x507940u, gen::fn_sceSifGetNextRequest_00507700);
        a0 = v0;
        if (v0 != 0) {
            backedge(ctx);
            // 0x00507938
            charge(ctx, 2);
            jal(ctx, 0x507938u, gen::fn_sceSifExecRequest_00507758);
            continue;
        }
        // 0x00507950
        charge(ctx, 4);
        jal(ctx, 0x507950u, gen::fn__sceSleepThread_00503080);
        backedge(ctx);
    }
}

// 0x0050B598 sceSifInitIopHeap -- 136 bytes; frame 0x30: s1 sp+0x10, ra sp+0x20, s0 sp+0x0
// Binds the IOP heap RPC server (0x80000003), retrying until it is bound.
void sceSifInitIopHeap(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0050b598
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x10);
    sd(ra, sp, 0x20);
    s1 = 0x970000;
    sd(s0, sp, 0x0);
    for (;;) {
        // 0x0050b5d4
        charge(ctx, 8);
        s0 = addiu(s1, -25344);
        a1 = lui(0x8000);
        a0 = s0;
        a1 = a1 | 0x3;
        a2 = 0;
        jal(ctx, 0x50B5E4u, gen::fn_sceSifBindRpc_00507050);
        if (i64(v0) < 0) {
            goto L_0050b5f4_4;
        }
        lw(v0, s0, 36);
        // 0x0050b5fc
        charge(ctx, 2);
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = 0x780000;
        if (!cc) {
            break;
        }
        backedge(ctx);
        // 0x0050b5b0
        charge(ctx, 2);
        v0 = 0x100000;
        v1 = si(-1);
        for (;;) {
            // 0x0050b5b8
            charge(ctx, 7);
            v0 = addiu(v0, -1);
            if (v0 == v1) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0050b604
    charge(ctx, 2);
    sw(zero, v0, -2728);
    v0 = 0;
    // 0x0050b60c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
    return;
L_0050b5f4_4:
    charge(ctx, 2);
    v0 = si(-1);
    // 0x0050b60c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0050B620 sceSifAllocIopHeap -- 112 bytes; frame 0x30: ra sp+0x20, s0 sp+0x10
// Allocates IOP heap memory through the IOP heap RPC; returns the IOP address.
void sceSifAllocIopHeap(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0050b620
    enter(ctx, 7);  // entry check point + this block's cycles
    v1 = 0x780000;
    sp = addiu(sp, -0x30);
    lw(v0, v1, -2728);  // 0x77F558
    a1 = a0;
    sd(ra, sp, 0x20);
    sd(s0, sp, 0x10);
    if (i64(v0) >= 0) {
        // 0x0050b63c
        charge(ctx, 16);
        a3 = 0x970000;
        a0 = 0x970000;
        sw(a1, a3, -25216);  // 0x969D80
        s0 = 0x970000;
        a0 = addiu(a0, -25344);  // &heap_rpc_cd
        a3 = addiu(a3, -25216);  // &0x969D80
        sw(zero, sp, 0x0);
        a1 = 1;
        a2 = 0;
        t0 = 4;
        t1 = addiu(s0, -25280);  // &0x969D40
        t2 = 4;
        t3 = 0;
        jal(ctx, 0x50B66Cu, gen::fn_sceSifCallRpc_00507230);
        cc = i64(v0) >= 0;  // the condition, before the delay slot changes it
        lw(v0, s0, -25280);  // 0x969D40
        if (!cc) {
            goto L_0050b67c;
        }
        // 0x0050b680 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(ra, sp, 0x20);
        ld(s0, sp, 0x10);
        sp = addiu(sp, 0x30);
        return;
    }
L_0050b67c:
    charge(ctx, 1);
    v0 = 0;
    // 0x0050b680 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x30);
}

// 0x0050B690 sceSifAllocSysMemory -- 128 bytes; frame 0x30: ra sp+0x20, s0 sp+0x10
// Allocates IOP system memory (mode, size, address) through the IOP heap RPC.
void sceSifAllocSysMemory(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0050b690
    enter(ctx, 8);  // entry check point + this block's cycles
    v0 = 0x780000;
    sp = addiu(sp, -0x30);
    lw(v1, v0, -2728);  // 0x77F558
    a3 = a0;
    sd(ra, sp, 0x20);
    sd(s0, sp, 0x10);
    v0 = 0;
    if (i64(v1) >= 0) {
        // 0x0050b6b0
        charge(ctx, 19);
        v0 = 0x970000;
        a0 = 0x970000;
        v1 = addiu(v0, -25216);  // &0x969D80
        sw(a1, v0, -25216);  // 0x969D80
        sw(a3, v1, 4);  // 0x969D84
        s0 = 0x970000;
        sw(a2, v1, 8);  // 0x969D88
        a0 = addiu(a0, -25344);  // &heap_rpc_cd
        a3 = v1;
        a1 = 4;
        sw(zero, sp, 0x0);
        a2 = 0;
        t0 = 12;
        t1 = addiu(s0, -25280);  // &0x969D40
        t2 = 4;
        t3 = 0;
        jal(ctx, 0x50B6ECu, gen::fn_sceSifCallRpc_00507230);
        cc = i64(v0) >= 0;  // the condition, before the delay slot changes it
        lw(v0, s0, -25280);  // 0x969D40
        if (!cc) {
            // 0x0050b6fc
            charge(ctx, 1);
            v0 = 0;
        }
    }
    // 0x0050b700 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x30);
}

// 0x0050B710 sceSifFreeSysMemory -- 120 bytes; frame 0x30: ra sp+0x20, s0 sp+0x10
// Frees IOP memory through the IOP heap RPC.
void sceSifFreeSysMemory(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0050b710
    enter(ctx, 7);  // entry check point + this block's cycles
    v1 = 0x780000;
    sp = addiu(sp, -0x30);
    lw(v0, v1, -2728);  // 0x77F558
    a1 = a0;
    sd(ra, sp, 0x20);
    sd(s0, sp, 0x10);
    if (i64(v0) >= 0) {
        // 0x0050b734
        charge(ctx, 16);
        a3 = 0x970000;
        a0 = 0x970000;
        sw(a1, a3, -25216);  // 0x969D80
        s0 = 0x970000;
        a0 = addiu(a0, -25344);  // &heap_rpc_cd
        a3 = addiu(a3, -25216);  // &0x969D80
        sw(zero, sp, 0x0);
        a1 = 2;
        a2 = 0;
        t0 = 4;
        t1 = addiu(s0, -25280);  // &0x969D40
        t2 = 4;
        t3 = 0;
        jal(ctx, 0x50B764u, gen::fn_sceSifCallRpc_00507230);
        cc = i64(v0) >= 0;  // the condition, before the delay slot changes it
        lw(v0, s0, -25280);  // 0x969D40
        if (!cc) {
            // 0x0050b774
            charge(ctx, 1);
            v0 = si(-1);
        }
    } else {
        // 0x0050b72c
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x0050b778 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x30);
}

// 0x0050BAE8 _lf_bind -- 256 bytes; frame 0x50: s2 sp+0x30, ra sp+0x40, s1 sp+0x20, s0 sp+0x10
// Binds the loadfile RPC server (0x80000006) once, retrying until it is bound.
void _lf_bind(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050bae8
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s2, sp, 0x30);
    s2 = 0x780000;
    sd(ra, sp, 0x40);
    lw(v0, s2, -2720);  // 0x77F560
    sd(s1, sp, 0x20);
    sd(s0, sp, 0x10);
    if (i64(v0) >= 0) {
        // 0x0050bbcc
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x0050bb08
        charge(ctx, 2);
        s1 = 0x970000;
        s0 = addiu(s1, -24384);  // &lf_rpc_cd
        for (;;) {
            // 0x0050bb10
            charge(ctx, 7);
            a1 = lui(0x8000);
            a0 = s0;
            a1 = a1 | 0x6;
            a2 = 0;
            jal(ctx, 0x50BB1Cu, gen::fn_sceSifBindRpc_00507050);
            if (i64(v0) < 0) {
                break;
            }
            lw(v0, s0, 36);
            // 0x0050bb34
            charge(ctx, 2);
            a0 = s0;
            if (v0 != 0) {
                goto L_0050bb3c_5;
            }
            // 0x0050bb9c
            charge(ctx, 3);
            v0 = 0x100000;
            v1 = si(-1);
            for (;;) {
                // 0x0050bba8
                charge(ctx, 7);
                v0 = addiu(v0, -1);
                if (v0 == v1) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0050bbc4
            charge(ctx, 2);
            s0 = addiu(s1, -24384);
            backedge(ctx);
        }
        // 0x0050bb2c
        charge(ctx, 2);
        v0 = si(-1);
    }
    // 0x0050bbd0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x40);
    ld(s2, sp, 0x30);
    ld(s1, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x50);
    return;
L_0050bb3c_5:
    charge(ctx, 13);
    s1 = 0x970000;
    sw(zero, s2, -2720);
    sw(zero, sp, 0x0);
    a1 = 255;
    a2 = 0;
    a3 = 0;
    t0 = 0;
    t1 = addiu(s1, -24896);  // &0x969EC0
    t2 = 4;
    t3 = 0;
    jal(ctx, 0x50BB60u, gen::fn_sceSifCallRpc_00507230);
    v1 = 0x970000;
    if (i64(v0) >= 0) {
        // 0x0050bb7c
        charge(ctx, 8);
        a3 = addiu(s1, -24896);
        a2 = addiu(v1, -24344);
        lwl(a0, a3, 3);
        lwr(a0, a3, 0);
        swl(a0, a2, 3);
        swr(a0, a2, 0);
        v0 = 0;
    } else {
        // 0x0050bb70
        charge(ctx, 3);
        v0 = lui(0xFFFE);
        v0 = v0 | 0xFFFF;
    }
    // 0x0050bbd0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x40);
    ld(s2, sp, 0x30);
    ld(s1, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x50);
}

// 0x0050C2C0 _sceSifLoadModule -- 548 bytes; frame 0x80: s4 sp+0x50, s3 sp+0x40, s2 sp+0x30, s1 sp+0x20, s0 sp+0x10, ra sp+0x70, s5 sp+0x60
// Loads an IOP module (path, argument string) through the loadfile RPC; returns the module id or an error.
void _sceSifLoadModule(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0050c2c0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(s4, sp, 0x50);
    sd(s3, sp, 0x40);
    s4 = a3;
    sd(s2, sp, 0x30);
    s3 = t0;
    sd(s1, sp, 0x20);
    s2 = a1;
    sd(s0, sp, 0x10);
    s1 = a0;
    sd(ra, sp, 0x70);
    s0 = a2;
    link(ctx, 0x50C2F0u);  // $ra first: the delay slot below depends on it
    sd(s5, sp, 0x60);
    call(ctx, gen::fn__lf_bind_0050bae8);
    cc = i64(v0) < 0;  // the condition, before the delay slot changes it
    v0 = lui(0xFFFF);
    if (!cc) {
        // 0x0050c300
        charge(ctx, 4);
        jal(ctx, 0x50C300u, gen::fn__lf_version_0050bbe8);
        if (v0 == 0) {
            v0 = 0x970000;
            // 0x0050c31c
            charge(ctx, 8);
            a1 = s1;
            s1 = addiu(v0, -24888);
            a2 = 252;
            a0 = s1;
            jal(ctx, 0x50C328u, gen::fn_strncpy_00524828);
            v0 = addiu(s1, -8);
            sb(zero, v0, 259);
            if (s0 == 0) {
                // 0x0050c468
                charge(ctx, 3);
                sb(zero, v0, 260);
                s5 = 0x970000;
                sw(zero, s1, -8);
            L_0050c474:
                charge(ctx, 1);
                a1 = 0x970000;
            } else {
                // 0x0050c33c
                charge(ctx, 3);
                v0 = slti(s2, 253);
                a1 = s0;
                if (v0 != 0) {
                    // 0x0050c450
                    charge(ctx, 6);
                    a0 = addiu(s1, 252);
                    a2 = s2;
                    s5 = 0x970000;
                    jal(ctx, 0x50C458u, gen::fn_memcpy_00521250);
                    sw(s2, s1, -8);
                    goto L_0050c474;
                }
                // 0x0050c348
                charge(ctx, 5);
                a0 = addiu(s1, 252);
                v0 = s0 | a0;
                v0 = v0 & 0x7;
                v1 = s0;
                if (v0 == 0) {
                    // 0x0050c3c4
                    charge(ctx, 3);
                    v0 = addiu(s0, 224);
                    s5 = 0x970000;
                    a1 = 0x970000;
                    for (;;) {
                        // 0x0050c3d0
                        charge(ctx, 13);
                        ld(a2, v1, 0);
                        ld(a3, v1, 8);
                        ld(t0, v1, 16);
                        ld(t1, v1, 24);
                        sd(a2, a0, 0);
                        sd(a3, a0, 8);
                        sd(t0, a0, 16);
                        sd(t1, a0, 24);
                        v1 = addiu(v1, 32);
                        a0 = addiu(a0, 32);
                        if (v1 == v0) {
                            break;
                        }
                        backedge(ctx);
                    }
                } else {
                    // 0x0050c35c
                    charge(ctx, 3);
                    v0 = addiu(s0, 224);
                    s5 = 0x970000;
                    a1 = 0x970000;
                    for (;;) {
                        // 0x0050c368
                        charge(ctx, 21);
                        ldl(a2, v1, 7);
                        ldr(a2, v1, 0);
                        ldl(a3, v1, 15);
                        ldr(a3, v1, 8);
                        ldl(t0, v1, 23);
                        ldr(t0, v1, 16);
                        ldl(t1, v1, 31);
                        ldr(t1, v1, 24);
                        sdl(a2, a0, 7);
                        sdr(a2, a0, 0);
                        sdl(a3, a0, 15);
                        sdr(a3, a0, 8);
                        sdl(t0, a0, 23);
                        sdr(t0, a0, 16);
                        sdl(t1, a0, 31);
                        sdr(t1, a0, 24);
                        v1 = addiu(v1, 32);
                        a0 = addiu(a0, 32);
                        if (v1 == v0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0050c3bc
                    charge(ctx, 2);
                }
                // 0x0050c404
                charge(ctx, 19);
                ldl(a2, v1, 7);
                ldr(a2, v1, 0);
                ldl(a3, v1, 15);
                ldr(a3, v1, 8);
                ldl(t0, v1, 23);
                ldr(t0, v1, 16);
                lwl(t1, v1, 27);
                lwr(t1, v1, 24);
                sdl(a2, a0, 7);
                sdr(a2, a0, 0);
                sdl(a3, a0, 15);
                sdr(a3, a0, 8);
                sdl(t0, a0, 23);
                sdr(t0, a0, 16);
                swl(t1, a0, 27);
                v0 = 252;
                swr(t1, a0, 24);
                sw(v0, s5, -24896);
            }
            // 0x0050c478
            charge(ctx, 13);
            s0 = addiu(s5, -24896);
            a0 = addiu(a1, -24384);
            a1 = s3;
            sw(zero, sp, 0x0);
            a2 = 0;
            a3 = s0;
            t0 = 512;
            t1 = s0;
            t2 = 8;
            t3 = 0;
            jal(ctx, 0x50C49Cu, gen::fn_sceSifCallRpc_00507230);
            if (i64(v0) >= 0) {
                lw(v1, s0, 4);
                // 0x0050c4b8
                charge(ctx, 2);
                lw(v0, s5, -24896);
                sw(v1, s4, 0);
            } else {
                // 0x0050c4ac
                charge(ctx, 3);
                v0 = lui(0xFFFE);
                v0 = v0 | 0xFFFF;
            }
        } else {
            // 0x0050c310
            charge(ctx, 3);
            v0 = lui(0xFFFE);
            v0 = v0 | 0xFFFC;
        }
    }
    // 0x0050c4c0 (the shared epilogue, written out on this path)
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

// 0x0050C4E8 sceSifLoadModule -- 32 bytes; frame 0x20: ra sp+0x10
// sceSifLoadModule: _sceSifLoadModule with the plain-load mode.
void sceSifLoadModule(EEContext& ctx) {
    using namespace hg;
    Gpr a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050c4e8
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    t0 = 0;
    sd(ra, sp, 0x10);
    a3 = sp;
    jal(ctx, 0x50C4F4u, gen::fn__sceSifLoadModule_0050c2c0);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0050C848 sceSifResetIop -- 340 bytes; frame 0x40: s1 sp+0x20, s0 sp+0x10, ra sp+0x30
// Resets the IOP with a module image path: stops the SIF DMA, sends the reset packet and clears the sync flags.
void sceSifResetIop(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050c848
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s1, sp, 0x20);
    sd(s0, sp, 0x10);
    s1 = a0;
    s0 = a1;
    sd(ra, sp, 0x30);
    a0 = 0;
    a1 = 0;
    jal(ctx, 0x50C864u, gen::fn_sceSifExecNotifyHandler_0050f588);
    a0 = 1;
    a1 = 0;
    jal(ctx, 0x50C870u, gen::fn_sceSifExecNotifyHandler_0050f588);
    jal(ctx, 0x50C878u, gen::fn__sceSifStopDma_00503430);
    a0 = lui(0x8000);
    jal(ctx, 0x50C880u, gen::fn__sceSifGetReg_00503570);
    t2 = 0x970000;
    t3 = v0;
    v1 = addiu(t2, -24320);  // &0x96A100
    sw(s0, v1, 20);  // 0x96A114
    lb(v0, s1, 0);
    t1 = 0;
    if (v0 != 0) {
        // 0x0050c8a4
        charge(ctx, 3);
        v0 = s1;
        lbu(a0, v0, 0);
        for (;;) {
            // 0x0050c8b0
            charge(ctx, 8);
            v1 = addiu(t2, -24320);
            v1 = addu(v1, t1);
            t1 = addiu(t1, 1);
            sb(a0, v1, 24);
            v0 = addu(s1, t1);
            lb(v1, v0, 0);
            if (v1 == 0) {
                break;
            }
            lbu(a0, v0, 0);
            backedge(ctx);
        }
    }
    // 0x0050c8d0
    charge(ctx, 31);
    a2 = addiu(t2, -24320);
    v1 = lui(0x8000);
    sw(zero, a2, 4);
    a0 = si(-1);
    a0 = dsll32(a0, 0);
    a0 = a0 | 0xFF;
    v1 = v1 | 0x3;
    a1 = 104;
    ld(v0, t2, -24320);
    a3 = 104;
    sw(t1, a2, 16);
    t0 = 68;
    sw(v1, a2, 8);
    v0 = v0 & a0;
    sd(v0, t2, -24320);
    a0 = a2;
    sb(a1, t2, -24320);
    a1 = 104;
    sw(t3, sp, 0x4);
    sw(a3, sp, 0x8);
    sw(t0, sp, 0xC);
    link(ctx, 0x50C924u);  // $ra first: the delay slot below depends on it
    sw(a2, sp, 0x0);
    call(ctx, gen::fn_sub_5067F8_005067f8);
    a0 = 4;
    a1 = 0x40000;
    jal(ctx, 0x50C930u, gen::fn__sceSifSetReg_00503560);
    a0 = sp;
    a1 = 1;
    jal(ctx, 0x50C93Cu, gen::fn__sceSifSetDma_00503520);
    a0 = 4;
    if (v0 == 0) {
        // 0x0050c984
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x0050c94c
        charge(ctx, 14);
        a1 = 0x10000;
        jal(ctx, 0x50C94Cu, gen::fn__sceSifSetReg_00503560);
        a0 = 4;
        a1 = 0x20000;
        jal(ctx, 0x50C958u, gen::fn__sceSifSetReg_00503560);
        a0 = lui(0x8000);
        a1 = 0;
        a0 = a0 | 0x2;
        jal(ctx, 0x50C968u, gen::fn__sceSifSetReg_00503560);
        a0 = lui(0x8000);
        a1 = 0;
        jal(ctx, 0x50C974u, gen::fn__sceSifSetReg_00503560);
        v0 = 1;
    }
    // 0x0050c988 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x30);
    ld(s1, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x40);
}

// 0x0050C9C8 sceSifSyncIop -- 80 bytes; frame 0x10: ra sp+0x0
// Returns 1 once the IOP finished its reboot (SIF register 4, bit 0x40000), after resetting the tty and running
// the two SIF notify handlers; else 0.
void sceSifSyncIop(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0050c9c8
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 4;
    jal(ctx, 0x50C9D0u, gen::fn__sceSifGetReg_00503570);
    v1 = 0x40000;
    v0 = v0 & v1;
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = 0;
    if (!cc) {
        // 0x0050c9e8
        charge(ctx, 9);
        jal(ctx, 0x50C9E8u, gen::fn_sceResetttyinit_005035e0);
        a0 = 1;
        a1 = 1;
        jal(ctx, 0x50C9F4u, gen::fn_sceSifExecNotifyHandler_0050f588);
        a0 = 0;
        a1 = 1;
        jal(ctx, 0x50CA00u, gen::fn_sceSifExecNotifyHandler_0050f588);
        v0 = 1;
    }
    // 0x0050ca0c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0050CA18 sceSifRebootIop -- 272 bytes; frame 0x80: s1 sp+0x60, s0 sp+0x50, ra sp+0x70
// Reboots the IOP with an image ("rom0:UDNL <image>"): RPC init, reset and the wait for the IOP.
void sceSifRebootIop(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050ca18
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    v0 = 0x7C0000;
    sd(s1, sp, 0x60);
    sd(s0, sp, 0x50);
    sd(ra, sp, 0x70);
    s0 = a0;
    lb(v1, s0, 0);
    s1 = addiu(v0, -8192);  // "rom0:UDNL "
    if (v1 == 0) {
        // 0x0050ca64
        charge(ctx, 2);
        v1 = addiu(s0, -11);
        v0 = subu(a0, v1);
    } else {
        // 0x0050ca3c
        charge(ctx, 1);
        v1 = addiu(s0, -11);
        for (;;) {
            // 0x0050ca40
            charge(ctx, 7);
            a0 = addiu(a0, 1);
            lb(v0, a0, 0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0050ca5c
        charge(ctx, 2);
        v0 = subu(a0, v1);
    }
    // 0x0050ca6c
    charge(ctx, 3);
    v0 = sltiu(v0, 81);
    a0 = 0x7C0000;
    if (v0 != 0) {
        // 0x0050ca8c
        charge(ctx, 8);
        a0 = 0;
        jal(ctx, 0x50CA8Cu, gen::fn_sceSifInitRpc_005068a8);
        jal(ctx, 0x50CA94u, gen::fn_sceSifExitRpc_00506a48);
        lb(v0, s1, 0);
        v1 = sp;
        lbu(a0, s1, 0);
        if (v0 == 0) {
            // 0x0050cad4
            charge(ctx, 2);
            lbu(a1, s0, 0);
            a0 = a1;
        } else {
            // 0x0050caac
            charge(ctx, 1);
            lbu(a1, s0, 0);
            for (;;) {
                // 0x0050cab0
                charge(ctx, 7);
                sb(a0, v1, 0);
                s1 = addiu(s1, 1);
                v1 = addiu(v1, 1);
                lbu(a0, s1, 0);
                lb(v0, s1, 0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0050cacc
            charge(ctx, 2);
            a0 = a1;
        }
        // 0x0050cadc
        charge(ctx, 2);
        if (a0 == 0) {
            sb(zero, v1, 0);
        } else {
            // 0x0050cae4
            charge(ctx, 1);
            for (;;) {
                // 0x0050cae8
                charge(ctx, 7);
                sb(a0, v1, 0);
                s0 = addiu(s0, 1);
                v1 = addiu(v1, 1);
                lb(v0, s0, 0);
                a0 = v0;
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0050cb04
            charge(ctx, 1);
            sb(zero, v1, 0);
        }
        // 0x0050cb08
        charge(ctx, 3);
        a0 = sp;
        a1 = 0;
        jal(ctx, 0x50CB0Cu, gen::fn_sceSifResetIop_0050c848);
    } else {
        // 0x0050ca78
        charge(ctx, 5);
        a1 = s0;
        a0 = addiu(a0, -8176);
        jal(ctx, 0x50CA7Cu, gen::fn_scePrintf_00505e48);
        v0 = 0;
    }
    // 0x0050cb14 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x70);
    ld(s1, sp, 0x60);
    ld(s0, sp, 0x50);
    sp = addiu(sp, 0x80);
}

// 0x0050CC10 _sceCopy -- 16 bytes; leaf frame (no stack)
// Kernel syscall wrapper: Copy (90), used by InitTLBFunctions.
void _sceCopy(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x0050cc10
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 90;
    syscall(ctx, 0x50CC14u);
}

// 0x0050CC58 _sceGetEntryAddress -- 16 bytes; leaf frame (no stack)
// Kernel syscall wrapper: GetEntryAddress (91), used by InitTLBFunctions.
void _sceGetEntryAddress(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x0050cc58
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 91;
    syscall(ctx, 0x50CC5Cu);
}

// 0x0050CC68 _sceSetSyscall -- 16 bytes; leaf frame (no stack)
// Kernel syscall wrapper: SetSyscall (116), used by InitTLBFunctions.
void _sceSetSyscall(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x0050cc68
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 116;
    syscall(ctx, 0x50CC6Cu);
}

// 0x0050D3A0 DIntr -- 80 bytes; leaf frame (no stack)
// DIntr: disables interrupts (di until Status.EIE reads clear) and returns whether they were enabled.
void DIntr(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0050d3a0
    enter(ctx, 5);  // entry check point + this block's cycles
    mfc0(v1, 12);
    v0 = 0x10000;
    v1 = v1 & v0;
    a0 = sltu(0, v1);
    if (v1 == 0) {
        // 0x0050d3e4
        charge(ctx, 3);
        a0 = 0;
        v0 = a0;
        return;
    }
    // 0x0050d3b4
    charge(ctx, 1);
    for (;;) {
        // 0x0050d3b8
        charge(ctx, 9);
        di(ctx);
        sync(ctx, 16);
        mfc0(v0, 12);
        v1 = 0x10000;
        v0 = v0 & v1;
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0050d3dc
    charge(ctx, 2);
    v0 = a0;
}

// 0x0050D3F0 EIntr -- 24 bytes; leaf frame (no stack)
// EIntr: enables interrupts and returns whether they had been enabled.
void EIntr(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3};
    // 0x0050d3f0
    enter(ctx, 6);  // entry check point + this block's cycles
    mfc0(v0, 12);
    v1 = 0x10000;
    v0 = v0 & v1;
    ei(ctx);
    v0 = sltu(0, v0);
}

// 0x0050D500 _sceFindAddress -- 16 bytes; leaf frame (no stack)
// Kernel syscall wrapper: FindAddress (131), used by InitSystemCallTableAddress.
void _sceFindAddress(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x0050d500
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 131;
    syscall(ctx, 0x50D504u);
}

// 0x0050D648 _sceSetSyscall_0 -- 16 bytes; leaf frame (no stack)
// Kernel syscall wrapper: SetSyscall (116), used by InitSystemCallTableAddress.
void _sceSetSyscall_0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x0050d648
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 116;
    syscall(ctx, 0x50D64Cu);
}

// 0x0050DAD0 _sceSetSyscall_3 -- 16 bytes; leaf frame (no stack)
// Kernel syscall wrapper: SetSyscall (116), used by InitAlarm.
void _sceSetSyscall_3(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x0050dad0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 116;
    syscall(ctx, 0x50DAD4u);
}

// 0x0050DAE0 _sceCopy_3 -- 16 bytes; leaf frame (no stack)
// Kernel syscall wrapper: Copy (90), used by InitAlarm.
void _sceCopy_3(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x0050dae0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 90;
    syscall(ctx, 0x50DAE4u);
}

// 0x0050DB28 _sceGetEntryAddress_1 -- 16 bytes; leaf frame (no stack)
// Kernel syscall wrapper: GetEntryAddress (91), used by InitAlarm.
void _sceGetEntryAddress_1(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x0050db28
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 91;
    syscall(ctx, 0x50DB2Cu);
}

// 0x0050DB38 InitAlarm -- 212 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20, s1 sp+0x10, s0 sp+0x0
// libkernel InitAlarm: when the INTC mask bit 8 is clear installs the alarm kernel patch (SetSyscall / Copy /
// FlushCache) and its syscall table entries.
void InitAlarm(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050db38
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = 0x10000000;
    sd(ra, sp, 0x30);
    v0 = v0 | 0x1810;
    sd(s2, sp, 0x20);
    sd(s1, sp, 0x10);
    sd(s0, sp, 0x0);
    lw(v1, v0, 0);  // 0x10001810
    v1 = v1 & 0x100;
    ld(ra, sp, 0x30);
    if (v1 == 0) {
        // 0x0050db64
        charge(ctx, 27);
        v0 = 0x780000;
        s2 = 2;
        s0 = addiu(v0, 2824);  // &tbl_kpatch_alarm
        lw(a0, v0, 2824);  // tbl_kpatch_alarm
        lw(a1, s0, 4);  // tbl_kpatch_alarm+0x4
        s1 = addiu(s0, 16);  // &tbl_kpatch_alarm+0x10
        jal(ctx, 0x50DB78u, gen::fn__sceSetSyscall_3_0050dad0);
        a1 = 0x780000;
        a0 = lui(0x8007);
        a1 = addiu(a1, 928);  // &0x7803A0
        a0 = a0 | 0x6000;
        a2 = 1856;
        jal(ctx, 0x50DB90u, gen::fn__sceCopy_3_0050dae0);
        a1 = 0x780000;
        a0 = 0x80000;
        a1 = addiu(a1, 2784);  // &kpayload_alarm_vector_82000
        a0 = a0 | 0x2000;
        a2 = 40;
        jal(ctx, 0x50DBA8u, gen::fn__sceCopy_3_0050dae0);
        a0 = 0;
        jal(ctx, 0x50DBB0u, gen::fn__sceFlushCache_005033e0);
        a0 = 2;
        jal(ctx, 0x50DBB8u, gen::fn__sceFlushCache_005033e0);
        lw(a0, s0, 8);  // tbl_kpatch_alarm+0x8
        link(ctx, 0x50DBC4u);  // $ra first: the delay slot below depends on it
        lw(a1, s0, 12);  // tbl_kpatch_alarm+0xC
        call(ctx, gen::fn__sceSetSyscall_3_0050dad0);
        lw(a0, s1, 0);  // tbl_kpatch_alarm+0x10
        for (;;) {
            // 0x0050dbd0
            charge(ctx, 9);
            s2 = addiu(s2, 1);
            jal(ctx, 0x50DBD0u, gen::fn__sceGetEntryAddress_1_0050db28);
            lw(a0, s1, 0);
            a1 = v0;
            s1 = addiu(s1, 8);
            jal(ctx, 0x50DBE0u, gen::fn__sceSetSyscall_3_0050dad0);
            v0 = sltiu(s2, 8);
            if (v0 == 0) {
                break;
            }
            lw(a0, s1, 0);
            backedge(ctx);
        }
        // 0x0050dbf4
        charge(ctx, 1);
        ld(ra, sp, 0x30);
    }
    // 0x0050dbf8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0050DC80 sub_50DC80 -- 120 bytes, 2 chunks; leaf frame (no stack)
// Kernel-mode store of a0 to T2_COUNT (0xB0001000): interrupts off, Status EXL / ERL set, the store, eret to $ra.
void sub_50DC80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, ra{ctx, 31};
    // 0x0050dc80
    enter(ctx, 4);  // entry check point + this block's cycles
    a1 = a0;
    a0 = lui(0xB000);
    a0 = a0 | 0x1000;
    backedge(ctx);
    // 0x0050dc10
    charge(ctx, 5);
    mfc0(v1, 12);
    v0 = 0x10000;
    v1 = v1 & v0;
    a2 = 0x10000;
    if (v1 != 0) {
        // 0x0050dc24
        charge(ctx, 1);
        for (;;) {
            // 0x0050dc28
            charge(ctx, 9);
            di(ctx);
            sync(ctx, 16);
            mfc0(v0, 12);
            v0 = v0 & a2;
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0050dc4c
    charge(ctx, 11);
    mfc0(v0, 12);
    sync(ctx, 16);
    v0 = v0 | 0x6;
    v0 = v0 ^ 0x2;
    v0 = v0 | v1;
    mtc0(v0, 12);
    sync(ctx, 16);
    sw(a1, a0, 0);
    mtc0(ra, 30);
    sync(ctx, 16);
    rt::eret(ctx, 0x50DC74u);
}

// 0x0050DC90 sub_50DC90 -- 120 bytes, 2 chunks; leaf frame (no stack)
// Kernel-mode store of a0 to T2_MODE (0xB0001010): the same shared tail as sub_50DC80.
void sub_50DC90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, ra{ctx, 31};
    // 0x0050dc90
    enter(ctx, 4);  // entry check point + this block's cycles
    a1 = a0;
    a0 = lui(0xB000);
    a0 = a0 | 0x1010;
    backedge(ctx);
    // 0x0050dc10
    charge(ctx, 5);
    mfc0(v1, 12);
    v0 = 0x10000;
    v1 = v1 & v0;
    a2 = 0x10000;
    if (v1 != 0) {
        // 0x0050dc24
        charge(ctx, 1);
        for (;;) {
            // 0x0050dc28
            charge(ctx, 9);
            di(ctx);
            sync(ctx, 16);
            mfc0(v0, 12);
            v0 = v0 & a2;
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0050dc4c
    charge(ctx, 11);
    mfc0(v0, 12);
    sync(ctx, 16);
    v0 = v0 | 0x6;
    v0 = v0 ^ 0x2;
    v0 = v0 | v1;
    mtc0(v0, 12);
    sync(ctx, 16);
    sw(a1, a0, 0);
    mtc0(ra, 30);
    sync(ctx, 16);
    rt::eret(ctx, 0x50DC74u);
}

// 0x0050DCA0 sub_50DCA0 -- 120 bytes, 2 chunks; leaf frame (no stack)
// Kernel-mode store of a0 to T2_COMP (0xB0001020): the same shared tail as sub_50DC80.
void sub_50DCA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, ra{ctx, 31};
    // 0x0050dca0
    enter(ctx, 4);  // entry check point + this block's cycles
    a1 = a0;
    a0 = lui(0xB000);
    a0 = a0 | 0x1020;
    backedge(ctx);
    // 0x0050dc10
    charge(ctx, 5);
    mfc0(v1, 12);
    v0 = 0x10000;
    v1 = v1 & v0;
    a2 = 0x10000;
    if (v1 != 0) {
        // 0x0050dc24
        charge(ctx, 1);
        for (;;) {
            // 0x0050dc28
            charge(ctx, 9);
            di(ctx);
            sync(ctx, 16);
            mfc0(v0, 12);
            v0 = v0 & a2;
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0050dc4c
    charge(ctx, 11);
    mfc0(v0, 12);
    sync(ctx, 16);
    v0 = v0 | 0x6;
    v0 = v0 ^ 0x2;
    v0 = v0 | v1;
    mtc0(v0, 12);
    sync(ctx, 16);
    sw(a1, a0, 0);
    mtc0(ra, 30);
    sync(ctx, 16);
    rt::eret(ctx, 0x50DC74u);
}

// 0x0050DCB0 InitTimer -- 340 bytes; frame 0x60: s2 sp+0x20, s4 sp+0x40, s1 sp+0x10, ra sp+0x50, s3 sp+0x30, s0 sp+0x0
// libkernel InitTimer: once only: clears the alarm pool (0x96B3C0, 8 KiB) and links its 128 free entries,
// InitAlarm, installs cbTimerHandler on INTC 11 (timer 2) and sets timer 2 up (sub_50DC80..A0).
void InitTimer(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050dcb0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(s2, sp, 0x20);
    sd(s4, sp, 0x40);
    s2 = 0x780000;
    sd(s1, sp, 0x10);
    sd(ra, sp, 0x50);
    s1 = addiu(s2, 2888);  // &0x780B48
    sd(s3, sp, 0x30);
    sd(s0, sp, 0x0);
    lw(v0, s1, 8);  // 0x780B50
    s4 = a0;
    if (i64(v0) < 0) {
        // 0x0050dcec
        charge(ctx, 13);
        s3 = 0x970000;
        sd(zero, s2, 2888);
        s0 = addiu(s3, -19520);  // &0x96B3C0
        sw(zero, s1, 16);
        a0 = s0;
        a1 = 0;
        a2 = 8192;
        jal(ctx, 0x50DD04u, gen::fn_memset_00521408);
        sw(s0, s1, 20);
        v1 = addiu(s0, 8192);  // &0x96D3C0
        v0 = 127;
        s0 = addiu(s0, 8128);  // &0x96D380
        for (;;) {
            // 0x0050dd20
            charge(ctx, 7);
            sw(v1, s0, 0);
            v0 = addiu(v0, -1);
            s0 = addiu(s0, -64);
            v1 = addiu(v1, -64);
            if (i64(v0) < 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0050dd3c
        charge(ctx, 12);
        v0 = addiu(s3, -19520);
        link(ctx, 0x50DD40u);  // $ra first: the delay slot below depends on it
        sw(zero, v0, 8128);
        call(ctx, gen::fn__InitAlarm_0050efe0);
        a1 = 0x510000;
        a0 = 11;
        a1 = addiu(a1, -7600);  // &cbTimerHandler
        a2 = 0;
        a3 = 0;
        jal(ctx, 0x50DD58u, gen::fn__sceAddIntcHandler_0_00502e50);
        v1 = v0;
        if (i64(v1) >= 0) {
            v0 = addiu(s2, 2888);
            // 0x0050dd78
            charge(ctx, 14);
            link(ctx, 0x50DD78u);  // $ra first: the delay slot below depends on it
            sw(v1, v0, 8);
            call(ctx, gen::fn_DIntr_0050d3a0);
            v1 = 0x10000000;
            s1 = v0;
            v1 = v1 | 0x1010;
            v0 = lui(0xFFFF);
            lw(s0, v1, 0);  // 0x10001010
            v0 = v0 | 0xFFFC;
            v0 = s0 & v0;
            s0 = v0 | s4;
            s0 = s0 | 0x300;
            v0 = s0 & 0x80;
            a0 = 0;
            if (v0 == 0) {
                // 0x0050ddb0
                charge(ctx, 4);
                s0 = s0 | 0xC80;
                jal(ctx, 0x50DDB0u, gen::fn_sub_50DC80_0050dc80);
                a0 = 0xFFFF;
                jal(ctx, 0x50DDB8u, gen::fn_sub_50DCA0_0050dca0);
            }
            // 0x0050ddc0
            charge(ctx, 6);
            a0 = s0;
            jal(ctx, 0x50DDC0u, gen::fn_sub_50DC90_0050dc90);
            a0 = 11;
            jal(ctx, 0x50DDC8u, gen::fn_EnableIntc_00503ca8);
            v0 = 0;
            if (s1 != 0) {
                // 0x0050ddd8
                charge(ctx, 3);
                jal(ctx, 0x50DDD8u, gen::fn_EIntr_0050d3f0);
                v0 = 0;
            }
        } else {
            // 0x0050dd6c
            charge(ctx, 3);
            v0 = lui(0x8000);
            v0 = v0 | 0x9021;
        }
    } else {
        // 0x0050dce0
        charge(ctx, 3);
        v0 = lui(0x8000);
        v0 = v0 | 0x8001;
    }
    // 0x0050dde4 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    ld(s4, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x0050DEF0 StartTimerSystemTime -- 144 bytes; frame 0x20: s0 sp+0x0, ra sp+0x10
// libkernel StartTimerSystemTime: with interrupts off, when T2_MODE.CUE is clear sets it (sub_50DC90) and arms the
// next alarm (sub_50E000); returns 1 when it already ran, else 0.
void StartTimerSystemTime(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050def0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    jal(ctx, 0x50DEFCu, gen::fn_DIntr_0050d3a0);
    s0 = v0;
    v0 = 0x10000000;
    v0 = v0 | 0x1010;
    lw(v0, v0, 0);  // 0x10001010
    v1 = v0 & 0x80;
    if (v1 == 0) {
        // 0x0050df38
        charge(ctx, 11);
        a0 = lui(0xFFFF);
        a0 = a0 | 0xF3FF;
        a0 = v0 & a0;
        a0 = a0 | 0x80;
        jal(ctx, 0x50DF44u, gen::fn_sub_50DC90_0050dc90);
        jal(ctx, 0x50DF4Cu, gen::fn_sub_50E508_0050e508);
        a0 = v0;
        jal(ctx, 0x50DF54u, gen::fn_sub_50E000_0050e000);
        v0 = 0;
        if (s0 != 0) {
            // 0x0050df64
            charge(ctx, 3);
            jal(ctx, 0x50DF64u, gen::fn_EIntr_0050d3f0);
            v0 = 0;
        }
    } else {
        // 0x0050df20
        charge(ctx, 2);
        v0 = 1;
        if (s0 != 0) {
            // 0x0050df28
            charge(ctx, 4);
            jal(ctx, 0x50DF28u, gen::fn_EIntr_0050d3f0);
            v0 = 1;
        }
    }
    // 0x0050df70 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0050E250 cbTimerHandler -- 692 bytes; frame 0xA0: s6 sp+0x60, ra sp+0x90, fp sp+0x80, s7 sp+0x70, s5 sp+0x50, s4 sp+0x40, s3 sp+0x30, s2 sp+0x20, s1 sp+0x10, s0 sp+0x0
// libkernel's timer-2 interrupt handler: counts the overflows and runs the due alarm callbacks.
void cbTimerHandler(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0050e250
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    v1 = 0x10000000;
    sd(s6, sp, 0x60);
    v1 = v1 | 0x1010;
    sd(ra, sp, 0x90);
    s6 = a2;
    sd(fp, sp, 0x80);
    sd(s7, sp, 0x70);
    sd(s5, sp, 0x50);
    sd(s4, sp, 0x40);
    sd(s3, sp, 0x30);
    sd(s2, sp, 0x20);
    sd(s1, sp, 0x10);
    sd(s0, sp, 0x0);
    lw(v0, v1, 0);  // 0x10001010
    v0 = v0 & 0x400;
    s5 = 0x780000;
    if (v0 != 0) {
        // 0x0050e298
        charge(ctx, 4);
        v0 = addiu(s5, 2888);
        lw(s0, v0, 24);
        fp = s5;
        if (s0 == 0) {
            goto L_0050e40c;
        }
        // 0x0050e2a8
        charge(ctx, 4);
        s4 = s5;
        s7 = 14745;
        v0 = 0x10000000;
        for (;;) {
            // 0x0050e2b8
            charge(ctx, 12);
            v1 = 0x10000000;
            v0 = v0 | 0x1000;
            v1 = v1 | 0x1010;
            lw(a2, v0, 0);
            lw(s1, v1, 0);  // 0x10001010
            ld(a0, s0, 32);
            ld(v0, s0, 16);
            a1 = s1 & 0x800;
            ld(v1, s0, 24);
            a0 = a0 + v0;
            s3 = a0 - v1;
            if (a1 != 0) {
                // 0x0050e2e8
                charge(ctx, 9);
                ld(v0, s4, 2888);
                a0 = lui(0xFFFF);
                a0 = a0 | 0xFBFF;
                v0 = daddiu(v0, 1);
                a0 = s1 & a0;
                link(ctx, 0x50E2FCu);  // $ra first: the delay slot below depends on it
                sd(v0, s4, 2888);
                call(ctx, gen::fn_sub_50DC90_0050dc90);
                a2 = 0x10000000;
                lw(a2, a2, 4096);  // 0x10001000
            }
            // 0x0050e30c
            charge(ctx, 11);
            ld(a0, s4, 2888);
            v0 = dsll32(a2, 0);
            v0 = dsrl32(v0, 0);
            v1 = s1 & 0x3;
            a0 = dsll(a0, 16);
            v1 = sll(v1, 2);
            a0 = a0 | v0;
            s1 = dsllv(a0, v1);
            v0 = sltu(s1, s3);
            s2 = addiu(s4, 2888);
            if (v0 != 0) {
                goto L_0050e40c;
            }
            // 0x0050e338
            charge(ctx, 22);
            a0 = s0;
            jal(ctx, 0x50E338u, gen::fn_sub_50E218_0050e218);
            lw(v1, s0, 8);
            a3 = sll(s0, 4);
            ld(a2, s0, 24);
            ld(a0, s0, 16);
            v1 = a3 | v1;
            a2 = s1 + a2;
            sw(v1, s2, 28);
            a2 = a2 - a0;
            sw(v0, s2, 32);
            lw(gp, s0, 44);
            lw(a0, s0, 8);
            t0 = s6;
            lw(v0, s0, 40);
            a0 = a3 | a0;
            ld(a1, s0, 32);
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x50E37Cu);  // $ra = the return address
            lw(a3, s0, 48);
            call_ptr(ctx, jt);
            a1 = v0;
            v0 = si(-1);
            if (a1 == 0) {
                // 0x0050e390
                charge(ctx, 6);
                lw(v1, s0, 12);
                v0 = lui(0xFFFF);
                v0 = v0 | 0xFFFD;
                v1 = v1 & v0;
                sw(v1, s0, 12);
                goto L_0050e3f4;
            }
            // 0x0050e3a8
            charge(ctx, 2);
            cc = a1 != v0;  // the condition, before the delay slot changes it
            v0 = 14744;
            if (cc) {
                // 0x0050e3d8
                charge(ctx, 7);
                ld(v1, s0, 32);
                v0 = sltu(v0, a1);
                a0 = s0;
                if (v0 == 0) a1 = s7;
                v1 = v1 + a1;
                link(ctx, 0x50E3ECu);  // $ra first: the delay slot below depends on it
                sd(v1, s0, 32);
                call(ctx, gen::fn_sub_50E190_0050e190);
            L_0050e3f4:
                charge(ctx, 1);
                v0 = addiu(fp, 0xB48);
            } else {
                // 0x0050e3b0
                charge(ctx, 10);
                sw(zero, s0, 8);
                sw(zero, s0, 12);
                lw(v1, s2, 20);
                lw(v0, s2, 16);
                sw(v1, s0, 0);
                v0 = addiu(v0, -1);
                sw(s0, s2, 20);
                sw(v0, s2, 16);
                v0 = addiu(fp, 0xB48);
            }
            // 0x0050e3f8
            charge(ctx, 3);
            lw(s0, v0, 32);
            v0 = 0x10000000;
            if (s0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0050e404
        charge(ctx, 2);
        a0 = addiu(s5, 2888);
        goto L_0050e410;
    }
L_0050e40c:
    charge(ctx, 1);
    a0 = addiu(s5, 2888);
L_0050e410:
    charge(ctx, 11);
    v1 = si(-1);
    sw(v1, a0, 28);
    v0 = 0x10000000;
    v0 = v0 | 0x1000;
    v1 = 0x10000000;
    lw(a1, v0, 0);  // 0x10001000
    v1 = v1 | 0x1010;
    lw(s0, v1, 0);  // 0x10001010
    v0 = s0 & 0x800;
    sw(zero, a0, 32);
    if (v0 != 0) {
        // 0x0050e43c
        charge(ctx, 9);
        ld(v0, s5, 2888);
        a0 = lui(0xFFFF);
        a0 = a0 | 0xFBFF;
        v0 = daddiu(v0, 1);
        a0 = s0 & a0;
        link(ctx, 0x50E450u);  // $ra first: the delay slot below depends on it
        sd(v0, s5, 2888);
        call(ctx, gen::fn_sub_50DC90_0050dc90);
        a1 = 0x10000000;
        lw(a1, a1, 4096);  // 0x10001000
    }
    // 0x0050e460
    charge(ctx, 16);
    ld(v0, s5, 2888);
    v1 = dsll32(a1, 0);
    v1 = dsrl32(v1, 0);
    a0 = s0 & 0x3;
    v0 = dsll(v0, 16);
    a0 = sll(a0, 2);
    v0 = v0 | v1;
    a0 = dsllv(v0, a0);
    jal(ctx, 0x50E47Cu, gen::fn_sub_50E000_0050e000);
    v0 = 0x10000000;
    lw(v0, v0, 4096);  // 0x10001000
    v1 = 0x10000000;
    lw(v1, v1, 4112);  // 0x10001010
    v0 = v1 & 0x800;
    if (v0 != 0) {
        // 0x0050e4a0
        charge(ctx, 9);
        ld(v0, s5, 2888);
        a0 = lui(0xFFFF);
        a0 = a0 | 0xFBFF;
        v0 = daddiu(v0, 1);
        a0 = v1 & a0;
        link(ctx, 0x50E4B4u);  // $ra first: the delay slot below depends on it
        sd(v0, s5, 2888);
        call(ctx, gen::fn_sub_50DC90_0050dc90);
        v0 = 0x10000000;
        lw(v0, v0, 4096);  // 0x10001000
    }
    // 0x0050e4c4 (the shared epilogue, written out on this path)
    charge(ctx, 16);
    ld(v0, s5, 2888);
    sync(ctx, 0);
    ei(ctx);
    ld(ra, sp, 0x90);
    v0 = 0;
    ld(fp, sp, 0x80);
    ld(s7, sp, 0x70);
    ld(s6, sp, 0x60);
    ld(s5, sp, 0x50);
    ld(s4, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// 0x0050F8A8 _sceCd_cd_read_intr -- 184 bytes; leaf frame (no stack)
// libcdvd's read-end handler (data reference): copies the unaligned head and tail bytes the IOP sent back (the
// counts at +0 / +4, the data at +16 / +80) into the user buffer through both the cached and uncached views.
void _sceCd_cd_read_intr(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0050f8a8
    enter(ctx, 5);  // entry check point + this block's cycles
    a1 = 0x20000000;
    a3 = a0 | a1;
    lw(v0, a3, 0);
    a2 = 0;
    if (i64(v0) > 0) {
        // 0x0050f8bc
        charge(ctx, 3);
        lw(t1, a3, 8);
        t2 = t1 | a1;
        if (i64(v0) <= 0) {
            goto L_0050f908;
        }
        // 0x0050f8c8
        charge(ctx, 4);
        t0 = addiu(a3, 16);
        t3 = 0x780000;
        v0 = addu(t0, a2);
        for (;;) {
            // 0x0050f8d8
            charge(ctx, 10);
            a1 = addu(t2, a2);
            lbu(v1, v0, 0);
            a0 = addu(t1, a2);
            a2 = addiu(a2, 1);
            sb(v1, a1, 0);
            sb(v1, a0, 0);
            lw(v0, a3, 0);
            v0 = slt(a2, v0);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = addu(t0, a2);
            if (!cc) {
                break;
            }
            backedge(ctx);
        }
        // 0x0050f900
        charge(ctx, 2);
        lw(v1, a3, 4);
        goto L_0050f910;
    }
L_0050f908:
    charge(ctx, 2);
    t3 = 0x780000;
    lw(v1, a3, 4);
L_0050f910:
    charge(ctx, 2);
    v0 = 0x20000000;
    if (i64(v1) > 0) {
        // 0x0050f918
        charge(ctx, 4);
        lw(t1, a3, 12);
        a2 = 0;
        t2 = t1 | v0;
        if (i64(v1) > 0) {
            // 0x0050f928
            charge(ctx, 2);
            t0 = addiu(a3, 80);
            v0 = addu(t0, a2);
            for (;;) {
                // 0x0050f930
                charge(ctx, 10);
                a1 = addu(t2, a2);
                lbu(v1, v0, 0);
                a0 = addu(t1, a2);
                a2 = addiu(a2, 1);
                sb(v1, a1, 0);
                sb(v1, a0, 0);
                lw(v0, a3, 4);
                v0 = slt(a2, v0);
                cc = v0 != 0;  // the condition, before the delay slot changes it
                v0 = addu(t0, a2);
                if (!cc) {
                    break;
                }
                backedge(ctx);
            }
        }
    }
    // 0x0050f958
    charge(ctx, 2);
    a0 = addiu(t3, 3040);
    gen::fn__sceCd_cd_callback_0050f698(ctx);  // tail call
}

// 0x0050FC38 sceCdLayerSearchFile -- 764 bytes; frame 0xC0: s3 sp+0x50, s2 sp+0x40, s6 sp+0x80, ra sp+0xB0, fp sp+0xA0, s7 sp+0x90, s5 sp+0x70, s4 sp+0x60, s1 sp+0x30, s0 sp+0x20
// libcdvd: searches a file on a disc layer through the CD search RPC (with the command semaphore).
void sceCdLayerSearchFile(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0050fc38
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(s3, sp, 0x50);
    sd(s2, sp, 0x40);
    s3 = a0;
    sd(s6, sp, 0x80);
    s2 = a1;
    sd(ra, sp, 0xB0);
    s6 = 0x780000;
    sd(fp, sp, 0xA0);
    sd(s7, sp, 0x90);
    sd(s5, sp, 0x70);
    sd(s4, sp, 0x60);
    sd(s1, sp, 0x30);
    sd(s0, sp, 0x20);
    link(ctx, 0x50FC70u);  // $ra first: the delay slot below depends on it
    sw(a2, sp, 0x10);
    call(ctx, gen::fn_cmd_sem_init_0050f960);
    lw(a0, s6, 2984);  // sceCd_ncmd_semid
    jal(ctx, 0x50FC7Cu, gen::fn__scePollSema_005031b0);
    lw(v1, s6, 2984);  // sceCd_ncmd_semid
    cc = v1 != v0;  // the condition, before the delay slot changes it
    v0 = 0;
    if (!cc) {
        // 0x0050fc90
        charge(ctx, 7);
        v1 = 0x780000;
        v0 = 1;
        sw(v0, v1, 2972);  // 0x780B9C
        a0 = 1;
        jal(ctx, 0x50FC9Cu, gen::fn_sceCdSync_00510148);
        a0 = 0;
        if (v0 == 0) {
            // 0x0050fcac
            charge(ctx, 5);
            s1 = 0x780000;
            jal(ctx, 0x50FCACu, gen::fn_sceSifInitRpc_005068a8);
            lw(v0, s1, 3020);  // 0x780BCC
            s7 = 0x970000;
            if (i64(v0) >= 0) {
                // 0x0050fd6c
                charge(ctx, 3);
                s4 = 0x780000;
                s5 = 0x970000;
                fp = 0x970000;
            } else {
                // 0x0050fcc0
                charge(ctx, 4);
                s4 = 0x780000;
                s5 = 0x970000;
                fp = 0x970000;
                for (;;) {
                    // 0x0050fcf4
                    charge(ctx, 1);
                    s0 = addiu(s7, -9216);
                    for (;;) {
                        // 0x0050fcf8
                        charge(ctx, 7);
                        a1 = lui(0x8000);
                        a0 = s0;
                        a1 = a1 | 0x597;
                        a2 = 0;
                        jal(ctx, 0x50FD04u, gen::fn_sceSifBindRpc_00507050);
                        if (i64(v0) < 0) {
                            // 0x0050fd14
                            charge(ctx, 3);
                            lw(v0, s4, 2960);
                            cc = i64(v0) <= 0;  // the condition, before the delay slot changes it
                            v0 = 0x100000;
                            if (!cc) {
                                // 0x0050fd20
                                charge(ctx, 4);
                                a0 = 0x7C0000;
                                a0 = addiu(a0, -7840);  // "Libcdvd bind err CdSearchFile\n"
                                jal(ctx, 0x50FD24u, gen::fn_scePrintf_00505e48);
                                v0 = 0x100000;
                            }
                            // 0x0050fd30
                            charge(ctx, 2);
                            v1 = si(-1);
                            for (;;) {
                                // 0x0050fd38
                                charge(ctx, 7);
                                v0 = addiu(v0, -1);
                                if (v0 == v1) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x0050fd54
                            charge(ctx, 2);
                            s0 = addiu(s7, -9216);
                            backedge(ctx);
                            continue;
                        }
                        lw(v0, s0, 36);
                        break;
                    }
                    // 0x0050fd5c
                    charge(ctx, 2);
                    cc = v0 == 0;  // the condition, before the delay slot changes it
                    v0 = 0x100000;
                    if (!cc) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0050fcd0
                    charge(ctx, 2);
                    v1 = si(-1);
                    for (;;) {
                        // 0x0050fcd8
                        charge(ctx, 7);
                        v0 = addiu(v0, -1);
                        if (v0 == v1) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
                // 0x0050fd64
                charge(ctx, 2);
                sw(zero, s1, 3020);
            }
            // 0x0050fd78
            charge(ctx, 6);
            lbu(v1, s2, 0);
            a0 = addiu(s5, -9600);
            a1 = 0;
            v0 = sll(v1, 24);
            sb(v1, a0, 36);
            if (v0 != 0) {
                // 0x0050fd90
                charge(ctx, 2);
                a2 = addiu(a0, 36);
                a1 = addiu(a1, 1);
                for (;;) {
                    // 0x0050fd98
                    charge(ctx, 3);
                    v0 = slti(a1, 256);
                    cc = v0 == 0;  // the condition, before the delay slot changes it
                    v0 = addu(s2, a1);
                    if (!cc) {
                        // 0x0050fda4
                        charge(ctx, 6);
                        a0 = addu(a1, a2);
                        lbu(v1, v0, 0);
                        sb(v1, a0, 0);
                        v1 = sll(v1, 24);
                        if (v1 != 0) {
                            a1 = addiu(a1, 1);
                            backedge(ctx);
                            continue;
                        }
                    }
                    break;
                }
            }
            // 0x0050fdbc
            charge(ctx, 3);
            v0 = 256;
            cc = a1 != v0;  // the condition, before the delay slot changes it
            lw(v0, s4, 2960);
            if (!cc) {
                // 0x0050fdc8
                charge(ctx, 3);
                v0 = addiu(s5, -9600);
                sb(zero, v0, 291);
                lw(v0, s4, 2960);
            }
            // 0x0050fdd4
            charge(ctx, 2);
            a0 = 0x7C0000;
            if (i64(v0) > 0) {
                // 0x0050fddc
                charge(ctx, 4);
                a1 = 0x970000;
                a0 = addiu(a0, -7808);
                a1 = addiu(a1, -9564);  // &0x96DAA4
                jal(ctx, 0x50FDE4u, gen::fn_scePrintf_00505e48);
            }
            // 0x0050fdec
            charge(ctx, 19);
            lw(v0, sp, 0x10);
            s0 = addiu(s5, -9600);
            a1 = 300;
            a0 = s0;
            sw(v0, s0, 296);
            link(ctx, 0x50FE00u);  // $ra first: the delay slot below depends on it
            sw(s0, s0, 292);
            call(ctx, gen::fn_sub_5067F8_005067f8);
            a0 = addiu(s7, -9216);
            sw(zero, sp, 0x0);
            a1 = 0;
            a2 = 0;
            a3 = s0;
            t0 = 300;
            t1 = addiu(fp, -0x2440);
            t2 = 4;
            t3 = 0;
            jal(ctx, 0x50FE28u, gen::fn_sceSifCallRpc_00507230);
            cc = i64(v0) >= 0;  // the condition, before the delay slot changes it
            v0 = 0x20000000;
            if (!cc) {
                goto L_0050fe38;
            }
            // 0x0050fe4c
            charge(ctx, 24);
            v0 = s0 | v0;
            ldl(v1, v0, 7);
            ldr(v1, v0, 0);
            ldl(a0, v0, 15);
            ldr(a0, v0, 8);
            ldl(a1, v0, 23);
            ldr(a1, v0, 16);
            ldl(a2, v0, 31);
            ldr(a2, v0, 24);
            sdl(v1, s3, 7);
            sdr(v1, s3, 0);
            sdl(a0, s3, 15);
            sdr(a0, s3, 8);
            sdl(a1, s3, 23);
            sdr(a1, s3, 16);
            sdl(a2, s3, 31);
            sdr(a2, s3, 24);
            lwl(v1, v0, 35);
            lwr(v1, v0, 32);
            swl(v1, s3, 35);
            swr(v1, s3, 32);
            lw(v1, s4, 2960);
            a0 = 0x7C0000;
            if (i64(v1) > 0) {
                // 0x0050feac
                charge(ctx, 6);
                a1 = addiu(s3, 8);
                a0 = addiu(a0, -7784);
                jal(ctx, 0x50FEB0u, gen::fn_scePrintf_00505e48);
                lw(v0, s4, 2960);
                a0 = 0x7C0000;
                if (i64(v0) > 0) {
                    // 0x0050fec4
                    charge(ctx, 6);
                    lw(a1, s3, 4);
                    a0 = addiu(a0, -7768);
                    jal(ctx, 0x50FEC8u, gen::fn_scePrintf_00505e48);
                    lw(v0, s4, 2960);
                    a0 = 0x7C0000;
                    if (i64(v0) > 0) {
                        // 0x0050fedc
                        charge(ctx, 3);
                        lw(a1, s3, 0);
                        a0 = addiu(a0, -7752);
                        jal(ctx, 0x50FEE0u, gen::fn_scePrintf_00505e48);
                    }
                }
            }
            // 0x0050fee8
            charge(ctx, 7);
            v1 = 0x20000000;
            v0 = addiu(fp, -0x2440);
            v0 = v0 | v1;
            lw(a0, s6, 2984);
            link(ctx, 0x50FEF8u);  // $ra first: the delay slot below depends on it
            lw(s0, v0, 0);
            call(ctx, gen::fn__sceSignalSema_00503180);
            v0 = s0;
            // 0x0050ff04 (the shared epilogue, written out on this path)
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
        }
    L_0050fe38:
        charge(ctx, 5);
        lw(a0, s6, 2984);
        jal(ctx, 0x50FE3Cu, gen::fn__sceSignalSema_00503180);
        v0 = 0;
    }
    // 0x0050ff04 (the shared epilogue, written out on this path)
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

// 0x0050FF58 _sceCd_ncmd_prechk -- 344 bytes; frame 0x40: s1 sp+0x10, s0 sp+0x0, ra sp+0x30, s2 sp+0x20
// libcdvd: the N-command pre-check: binds the N-command RPC server on first use and takes the command semaphore
// (polls; fails when another command is running).
void _sceCd_ncmd_prechk(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0050ff58
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s1, sp, 0x10);
    sd(s0, sp, 0x0);
    s1 = a0;
    sd(ra, sp, 0x30);
    s0 = 0x780000;
    link(ctx, 0x50FF70u);  // $ra first: the delay slot below depends on it
    sd(s2, sp, 0x20);
    call(ctx, gen::fn_cmd_sem_init_0050f960);
    lw(a0, s0, 2984);  // sceCd_ncmd_semid
    jal(ctx, 0x50FF7Cu, gen::fn__scePollSema_005031b0);
    lw(v1, s0, 2984);  // sceCd_ncmd_semid
    cc = v1 == v0;  // the condition, before the delay slot changes it
    v0 = 0x780000;
    if (cc) {
        // 0x0050ffb8
        charge(ctx, 6);
        v0 = 0x780000;
        a0 = 1;
        link(ctx, 0x50FFC0u);  // $ra first: the delay slot below depends on it
        sw(s1, v0, 2972);
        call(ctx, gen::fn_sceCdSync_00510148);
        a0 = 0;
        if (v0 == 0) {
            // 0x0050ffe4
            charge(ctx, 5);
            s2 = 0x780000;
            jal(ctx, 0x50FFE4u, gen::fn_sceSifInitRpc_005068a8);
            lw(v0, s2, 3004);  // 0x780BBC
            cc = i64(v0) >= 0;  // the condition, before the delay slot changes it
            v0 = 1;
            if (!cc) {
                // 0x0050fff8
                charge(ctx, 2);
                s1 = 0x780000;
                for (;;) {
                    // 0x00510024
                    charge(ctx, 1);
                    s0 = addiu(s1, 7504);
                    for (;;) {
                        // 0x00510028
                        charge(ctx, 7);
                        a1 = lui(0x8000);
                        a0 = s0;
                        a1 = a1 | 0x595;
                        a2 = 0;
                        jal(ctx, 0x510034u, gen::fn_sceSifBindRpc_00507050);
                        if (i64(v0) < 0) {
                            // 0x00510044
                            charge(ctx, 4);
                            v0 = 0x780000;
                            lw(v1, v0, 2960);  // 0x780B90
                            v0 = 0x100000;
                            if (i64(v1) > 0) {
                                // 0x00510054
                                charge(ctx, 4);
                                a0 = 0x7C0000;
                                a0 = addiu(a0, -7688);  // "Libcdvd bind err N CMD\n"
                                jal(ctx, 0x510058u, gen::fn_scePrintf_00505e48);
                                v0 = 0x100000;
                            }
                            // 0x00510064
                            charge(ctx, 1);
                            v1 = si(-1);
                            for (;;) {
                                // 0x00510068
                                charge(ctx, 7);
                                v0 = addiu(v0, -1);
                                if (v0 == v1) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x00510084
                            charge(ctx, 2);
                            s0 = addiu(s1, 7504);
                            backedge(ctx);
                            continue;
                        }
                        lw(v0, s0, 36);
                        break;
                    }
                    // 0x0051008c
                    charge(ctx, 2);
                    cc = v0 == 0;  // the condition, before the delay slot changes it
                    v0 = 1;
                    if (!cc) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00510000
                    charge(ctx, 2);
                    v0 = 0x100000;
                    v1 = si(-1);
                    for (;;) {
                        // 0x00510008
                        charge(ctx, 7);
                        v0 = addiu(v0, -1);
                        if (v0 == v1) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
                // 0x00510094
                charge(ctx, 1);
                sw(zero, s2, 3004);
            }
        } else {
            // 0x0050ffd0
            charge(ctx, 3);
            lw(a0, s0, 2984);
            jal(ctx, 0x50FFD4u, gen::fn__sceSignalSema_00503180);
        L_0050ffdc:
            charge(ctx, 2);
            v0 = 0;
        }
    } else {
        // 0x0050ff90
        charge(ctx, 3);
        lw(v1, v0, 2960);
        v0 = 0x780000;
        if (i64(v1) <= 0) {
            goto L_0050ffdc;
        }
        // 0x0050ff9c
        charge(ctx, 7);
        a0 = 0x7C0000;
        lw(a2, v0, 2972);
        a0 = addiu(a0, -7728);  // "Ncmd fail sema cur_cmd:%d keep_cmd:%d\n"
        a1 = s1;
        jal(ctx, 0x50FFA8u, gen::fn_scePrintf_00505e48);
        v0 = 0;
    }
    // 0x00510098 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x005100B0 sceCdNcmdDiskReady -- 152 bytes; frame 0x30: ra sp+0x20, s0 sp+0x10
// libcdvd: the N-command form of DiskReady through the RPC.
void sceCdNcmdDiskReady(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005100b0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    a0 = 2;
    sd(ra, sp, 0x20);
    link(ctx, 0x5100BCu);  // $ra first: the delay slot below depends on it
    sd(s0, sp, 0x10);
    call(ctx, gen::fn__sceCd_ncmd_prechk_0050ff58);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = 0x780000;
    if (cc) {
        // 0x005100d4
        charge(ctx, 14);
        a0 = 0x780000;
        s0 = addiu(v0, 3072);
        a0 = addiu(a0, 7504);  // &0x781D50
        sw(zero, sp, 0x0);
        a1 = 14;
        a2 = 0;
        a3 = 0;
        t0 = 0;
        t1 = s0;
        t2 = 4;
        t3 = 0;
        jal(ctx, 0x5100FCu, gen::fn_sceSifCallRpc_00507230);
        v1 = 0x780000;
        if (i64(v0) >= 0) {
            // 0x00510120
            charge(ctx, 6);
            v0 = 0x20000000;
            v0 = s0 | v0;
            lw(a0, v1, 2984);
            link(ctx, 0x51012Cu);  // $ra first: the delay slot below depends on it
            lw(s0, v0, 0);
            call(ctx, gen::fn__sceSignalSema_00503180);
            v0 = s0;
        } else {
            // 0x0051010c
            charge(ctx, 5);
            v0 = 0x780000;
            link(ctx, 0x510110u);  // $ra first: the delay slot below depends on it
            lw(a0, v0, 2984);
            call(ctx, gen::fn__sceSignalSema_00503180);
            v0 = 0;
        }
    } else {
        // 0x005100cc
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x00510138 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x30);
}

// 0x00510148 sceCdSync -- 160 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10, s0 sp+0x0
// libcdvd: waits for (a0 == 0, DelayThread(4000) between checks) or polls (a0 != 0) the end of the N-command RPC.
void sceCdSync(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00510148
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sd(s1, sp, 0x10);
    sd(s0, sp, 0x0);
    if (a0 != 0) {
        // 0x005101ac
        charge(ctx, 4);
        v0 = 0x780000;
        lw(v1, v0, 2996);  // sceCd_c_cb_sem
        v0 = 1;
        if (v1 == 0) {
            // 0x005101bc
            charge(ctx, 5);
            a0 = 0x780000;
            a0 = addiu(a0, 7504);  // &0x781D50
            jal(ctx, 0x5101C0u, gen::fn_sceSifCheckStatRpc_00507430);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = 1;
            if (!cc) {
                // 0x005101d0
                charge(ctx, 1);
                v0 = 0;
            }
        }
        // 0x005101d4
        charge(ctx, 1);
        ld(ra, sp, 0x20);
    } else {
        // 0x0051015c
        charge(ctx, 4);
        v0 = 0x780000;
        lw(v1, v0, 2960);  // 0x780B90
        a0 = 0x7C0000;
        if (i64(v1) > 0) {
            // 0x0051016c
            charge(ctx, 2);
            a0 = addiu(a0, -7664);
            jal(ctx, 0x51016Cu, gen::fn_scePrintf_00505e48);
        }
        // 0x00510174
        charge(ctx, 3);
        s1 = 0x780000;
        s0 = 0x780000;
        for (;;) {
            // 0x00510188
            charge(ctx, 3);
            lw(v0, s1, 2996);
            if (v0 != 0) {
                backedge(ctx);
            } else {
                goto L_00510194_6;
            }
        L_00510180:
            charge(ctx, 2);
            a0 = 4000;
            jal(ctx, 0x510180u, gen::fn_DelayThread_005041d8);
        }
    L_005101a4_7:
        charge(ctx, 2);
        ld(ra, sp, 0x20);
    }
    // 0x005101d8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
    return;
L_00510194_6:
    charge(ctx, 4);
    a0 = addiu(s0, 7504);
    jal(ctx, 0x510194u, gen::fn_sceSifCheckStatRpc_00507430);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = 0;
    if (!cc) {
        goto L_005101a4_7;
    }
    backedge(ctx);
    goto L_00510180;
}

// 0x005101E8 sceCdSyncS -- 108 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0
// libcdvd: waits for or polls the end of the current S-command.
void sceCdSyncS(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005101e8
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sd(s0, sp, 0x0);
    if (a0 != 0) {
        // 0x00510238
        charge(ctx, 4);
        a0 = 0x780000;
        a0 = addiu(a0, 9984);  // &0x782700
        jal(ctx, 0x51023Cu, gen::fn_sceSifCheckStatRpc_00507430);
        ld(ra, sp, 0x10);
    } else {
        // 0x005101f8
        charge(ctx, 4);
        v0 = 0x780000;
        lw(v1, v0, 2960);  // 0x780B90
        a0 = 0x7C0000;
        if (i64(v1) > 0) {
            // 0x00510208
            charge(ctx, 2);
            a0 = addiu(a0, -7648);
            jal(ctx, 0x510208u, gen::fn_scePrintf_00505e48);
        }
        // 0x00510210
        charge(ctx, 2);
        s0 = 0x780000;
        for (;;) {
            // 0x00510220
            charge(ctx, 4);
            a0 = addiu(s0, 9984);
            jal(ctx, 0x510220u, gen::fn_sceSifCheckStatRpc_00507430);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = 0;
            if (!cc) {
                break;
            }
            backedge(ctx);
            // 0x00510218
            charge(ctx, 2);
            a0 = 4000;
            jal(ctx, 0x510218u, gen::fn_DelayThread_005041d8);
        }
        // 0x00510230
        charge(ctx, 2);
        ld(ra, sp, 0x10);
    }
    // 0x00510248 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00510258 _sceCd_scmd_prechk -- 344 bytes; frame 0x40: s1 sp+0x10, s0 sp+0x0, ra sp+0x30, s2 sp+0x20
// libcdvd: the S-command pre-check: binds the S-command RPC server on first use and takes the command semaphore.
void _sceCd_scmd_prechk(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00510258
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s1, sp, 0x10);
    sd(s0, sp, 0x0);
    s1 = a0;
    sd(ra, sp, 0x30);
    s0 = 0x780000;
    link(ctx, 0x510270u);  // $ra first: the delay slot below depends on it
    sd(s2, sp, 0x20);
    call(ctx, gen::fn_cmd_sem_init_0050f960);
    lw(a0, s0, 2988);  // 0x780BAC
    jal(ctx, 0x51027Cu, gen::fn__scePollSema_005031b0);
    lw(v1, s0, 2988);  // 0x780BAC
    cc = v1 == v0;  // the condition, before the delay slot changes it
    v0 = 0x780000;
    if (cc) {
        // 0x005102b8
        charge(ctx, 6);
        v0 = 0x780000;
        a0 = 1;
        link(ctx, 0x5102C0u);  // $ra first: the delay slot below depends on it
        sw(s1, v0, 2968);
        call(ctx, gen::fn_sceCdSyncS_005101e8);
        a0 = 0;
        if (v0 == 0) {
            // 0x005102e4
            charge(ctx, 5);
            s2 = 0x780000;
            jal(ctx, 0x5102E4u, gen::fn_sceSifInitRpc_005068a8);
            lw(v0, s2, 3028);  // 0x780BD4
            cc = i64(v0) >= 0;  // the condition, before the delay slot changes it
            v0 = 1;
            if (!cc) {
                // 0x005102f8
                charge(ctx, 2);
                s1 = 0x780000;
                for (;;) {
                    // 0x00510324
                    charge(ctx, 1);
                    s0 = addiu(s1, 9984);
                    for (;;) {
                        // 0x00510328
                        charge(ctx, 7);
                        a1 = lui(0x8000);
                        a0 = s0;
                        a1 = a1 | 0x593;
                        a2 = 0;
                        jal(ctx, 0x510334u, gen::fn_sceSifBindRpc_00507050);
                        if (i64(v0) < 0) {
                            // 0x00510344
                            charge(ctx, 4);
                            v0 = 0x780000;
                            lw(v1, v0, 2960);  // 0x780B90
                            v0 = 0x100000;
                            if (i64(v1) > 0) {
                                // 0x00510354
                                charge(ctx, 4);
                                a0 = 0x7C0000;
                                a0 = addiu(a0, -7592);  // "Libcdvd bind err S cmd\n"
                                jal(ctx, 0x510358u, gen::fn_scePrintf_00505e48);
                                v0 = 0x100000;
                            }
                            // 0x00510364
                            charge(ctx, 1);
                            v1 = si(-1);
                            for (;;) {
                                // 0x00510368
                                charge(ctx, 7);
                                v0 = addiu(v0, -1);
                                if (v0 == v1) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x00510384
                            charge(ctx, 2);
                            s0 = addiu(s1, 9984);
                            backedge(ctx);
                            continue;
                        }
                        lw(v0, s0, 36);
                        break;
                    }
                    // 0x0051038c
                    charge(ctx, 2);
                    cc = v0 == 0;  // the condition, before the delay slot changes it
                    v0 = 1;
                    if (!cc) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00510300
                    charge(ctx, 2);
                    v0 = 0x100000;
                    v1 = si(-1);
                    for (;;) {
                        // 0x00510308
                        charge(ctx, 7);
                        v0 = addiu(v0, -1);
                        if (v0 == v1) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
                // 0x00510394
                charge(ctx, 1);
                sw(zero, s2, 3028);
            }
        } else {
            // 0x005102d0
            charge(ctx, 3);
            lw(a0, s0, 2988);
            jal(ctx, 0x5102D4u, gen::fn__sceSignalSema_00503180);
        L_005102dc:
            charge(ctx, 2);
            v0 = 0;
        }
    } else {
        // 0x00510290
        charge(ctx, 3);
        lw(v1, v0, 2960);
        v0 = 0x780000;
        if (i64(v1) <= 0) {
            goto L_005102dc;
        }
        // 0x0051029c
        charge(ctx, 7);
        a0 = 0x7C0000;
        lw(a2, v0, 2968);
        a0 = addiu(a0, -7632);  // "Scmd fail sema cur_cmd:%d keep_cmd:%d\n"
        a1 = s1;
        jal(ctx, 0x5102A8u, gen::fn_scePrintf_00505e48);
        v0 = 0;
    }
    // 0x00510398 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00510460 sceCdInit -- 744 bytes; frame 0xB0: s3 sp+0x40, ra sp+0xA0, fp sp+0x90, s7 sp+0x80, s6 sp+0x70, s5 sp+0x60, s4 sp+0x50, s2 sp+0x30, s1 sp+0x20, s0 sp+0x10
// libcdvd sceCdInit: binds the init RPC, sends the init mode (or the exit), and resets the client state.
void sceCdInit(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00510460
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    sd(s3, sp, 0x40);
    s3 = a0;
    sd(ra, sp, 0xA0);
    sd(fp, sp, 0x90);
    a0 = 1;
    sd(s7, sp, 0x80);
    sd(s6, sp, 0x70);
    sd(s5, sp, 0x60);
    sd(s4, sp, 0x50);
    sd(s2, sp, 0x30);
    sd(s1, sp, 0x20);
    link(ctx, 0x510490u);  // $ra first: the delay slot below depends on it
    sd(s0, sp, 0x10);
    call(ctx, gen::fn_sceCdSyncS_005101e8);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = 0;
    if (!cc) {
        // 0x005104a0
        charge(ctx, 32);
        a0 = 0;
        s5 = 0x780000;
        jal(ctx, 0x5104A4u, gen::fn_sceSifInitRpc_005068a8);
        s4 = 0x780000;
        v0 = 1;
        v1 = 0x780000;
        sw(v0, v1, 2980);  // 0x780BA4
        a1 = 0x780000;
        lw(a0, s5, 3036);  // 0x780BDC
        v1 = si(-1);
        v0 = 0x780000;
        a2 = 0x780000;
        a0 = addiu(a0, 1);
        a3 = 0x780000;
        t1 = 0x780000;
        t0 = 0x780000;
        sw(v1, v0, 3016);  // 0x780BC8
        s0 = 0x970000;
        v0 = 0x970000;
        sw(v1, a1, 3020);  // 0x780BCC
        sw(v1, a2, 3004);  // 0x780BBC
        s1 = addiu(v0, -9176);  // &0x96DC28
        sw(v1, a3, 3028);  // 0x780BD4
        s2 = addiu(s0, -9088);  // &0x96DC80
        sw(v1, t1, 3024);  // 0x780BD0
        fp = 0x780000;
        sw(zero, t0, 3000);  // sceCd_ee_read_mode
        s7 = 0x780000;
        sw(a0, s5, 3036);  // 0x780BDC
        s6 = 0x7C0000;
        sw(v1, s4, 3032);  // 0x780BD8
        for (;;) {
            // 0x00510520
            charge(ctx, 8);
            a1 = lui(0x8000);
            a0 = s1;
            a1 = a1 | 0x592;
            a2 = 0;
            jal(ctx, 0x51052Cu, gen::fn_sceSifBindRpc_00507050);
            a1 = v0;
            if (i64(a1) < 0) {
                // 0x00510540
                charge(ctx, 3);
                lw(v0, s7, 2960);
                lw(a2, s5, 3036);
                if (i64(v0) > 0) {
                    // 0x0051054c
                    charge(ctx, 2);
                    a0 = addiu(s6, -7568);
                    jal(ctx, 0x51054Cu, gen::fn_scePrintf_00505e48);
                }
                // 0x00510554
                charge(ctx, 3);
                v0 = 0x100000;
                v1 = si(-1);
                for (;;) {
                    // 0x00510560
                    charge(ctx, 7);
                    v0 = addiu(v0, -1);
                    if (v0 == v1) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0051057c
                charge(ctx, 2);
                backedge(ctx);
                continue;
            }
            lw(v0, s1, 36);
            // 0x00510584
            charge(ctx, 2);
            a0 = s2;
            if (v0 != 0) {
                break;
            }
            // 0x005105dc
            charge(ctx, 3);
            v0 = 0x100000;
            v1 = si(-1);
            for (;;) {
                // 0x005105e8
                charge(ctx, 7);
                v0 = addiu(v0, -1);
                if (v0 == v1) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00510604
            charge(ctx, 2);
            backedge(ctx);
        }
        // 0x0051058c
        charge(ctx, 17);
        sw(s3, s0, -9088);
        sw(zero, s4, 3032);
        a1 = 4;
        jal(ctx, 0x510594u, gen::fn_sub_5067F8_005067f8);
        s0 = addiu(fp, 0x1D80);
        a0 = s1;
        a3 = s2;
        sw(zero, sp, 0x0);
        a1 = 0;
        a2 = 0;
        t0 = 4;
        t1 = s0;
        t2 = 16;
        t3 = 0;
        jal(ctx, 0x5105C0u, gen::fn_sceSifCallRpc_00507230);
        cc = i64(v0) >= 0;  // the condition, before the delay slot changes it
        v0 = 0x780000;
        if (cc) {
            // 0x0051060c
            charge(ctx, 13);
            a1 = 0x20000000;
            v0 = addiu(s0, 12);
            v0 = v0 | a1;
            v1 = addiu(s0, 4);
            a0 = addiu(s0, 8);
            lw(a2, v0, 0);
            a0 = a0 | a1;
            v1 = v1 | a1;
            lw(a1, v1, 0);
            s0 = 1;
            v0 = 255;
            lw(a0, a0, 0);
            if (a2 != v0) {
                // 0x00510640
                charge(ctx, 3);
                v0 = 254;
                cc = a2 != v0;  // the condition, before the delay slot changes it
                a2 = si(-1);
                if (!cc) {
                    // 0x0051064c
                    charge(ctx, 3);
                    v0 = 0x780000;
                    sw(s0, v0, 2960);  // 0x780B90
                    goto L_00510694;
                }
                // 0x00510658
                charge(ctx, 7);
                v0 = addiu(a1, 255);
                v1 = slt(a2, a1);
                if (v1 != 0) v0 = a1;
                v0 = sra(v0, 8);
                v0 = slti(v0, 2);
                if (v0 != 0) {
                    s0 = 2;
                    goto L_00510694;
                }
                // 0x00510674
                charge(ctx, 7);
                v1 = slt(a2, a0);
                v0 = addiu(a0, 255);
                if (v1 != 0) v0 = a0;
                v0 = sra(v0, 8);
                v0 = slti(v0, 2);
                v1 = 0x780000;
                if (v0 != 0) {
                    // 0x00510690
                    charge(ctx, 1);
                    s0 = 2;
                    goto L_00510694;
                }
                goto L_00510698;
            }
        L_00510694:
            charge(ctx, 1);
            v1 = 0x780000;
        L_00510698:
            charge(ctx, 3);
            sw(zero, v1, 2980);
            v0 = slti(s3, 2);
            if (i64(s3) >= 0) {
                // 0x005106a4
                charge(ctx, 2);
                cc = v0 != 0;  // the condition, before the delay slot changes it
                v0 = 5;
                if (cc) {
                    goto L_005106f8;
                }
                // 0x005106ac
                charge(ctx, 2);
                cc = s3 != v0;  // the condition, before the delay slot changes it
                v0 = 0x780000;
                if (cc) {
                    goto L_005106f8;
                }
                // 0x005106b4
                charge(ctx, 3);
                lw(v1, v0, 2960);
                a0 = 0x7C0000;
                if (i64(v1) > 0) {
                    // 0x005106c0
                    charge(ctx, 2);
                    a0 = addiu(a0, -7536);
                    jal(ctx, 0x5106C0u, gen::fn_scePrintf_00505e48);
                }
                // 0x005106c8
                charge(ctx, 12);
                jal(ctx, 0x5106C8u, gen::fn_cdvd_exit_0050fa48);
                a0 = si(-1);
                v0 = 0x780000;
                sw(a0, v0, 2984);  // sceCd_ncmd_semid
                v1 = 0x780000;
                sw(a0, v1, 2988);  // 0x780BAC
                v0 = 0x780000;
                v1 = 0x780000;
                sw(a0, v0, 2976);  // 0x780BA0
                sw(zero, v1, 3012);  // 0x780BC4
                goto L_00510714;
            }
        L_005106f8:
            charge(ctx, 7);
            jal(ctx, 0x5106F8u, gen::fn_cmd_sem_init_0050f960);
            jal(ctx, 0x510700u, gen::fn_PowerOffCB_0050fbc0);
            v1 = 0x780000;
            v0 = 1;
            sw(v0, v1, 3012);  // 0x780BC4
        L_00510714:
            charge(ctx, 1);
            v0 = s0;
        } else {
            // 0x005105d0
            charge(ctx, 3);
            sw(zero, v0, 2980);
            v0 = 0;
        }
    }
    // 0x00510718 (the shared epilogue, written out on this path)
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

// 0x00510960 sceCdDiskReady -- 544 bytes; frame 0x90: s6 sp+0x70, s2 sp+0x30, ra sp+0x80, s5 sp+0x60, s4 sp+0x50, s3 sp+0x40, s1 sp+0x20, s0 sp+0x10
// libcdvd sceCdDiskReady: asks the drive whether a disc is ready (mode 0 waits until it is).
void sceCdDiskReady(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00510960
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(s6, sp, 0x70);
    s6 = 0x780000;
    sd(s2, sp, 0x30);
    lw(v0, s6, 2960);  // 0x780B90
    s2 = a0;
    sd(ra, sp, 0x80);
    sd(s5, sp, 0x60);
    sd(s4, sp, 0x50);
    sd(s3, sp, 0x40);
    sd(s1, sp, 0x20);
    sd(s0, sp, 0x10);
    if (i64(v0) > 0) {
        // 0x00510994
        charge(ctx, 3);
        a0 = 0x7C0000;
        a0 = addiu(a0, -7440);  // "NEW DiskReady Call\n"
        jal(ctx, 0x510998u, gen::fn_scePrintf_00505e48);
    }
    // 0x005109a0
    charge(ctx, 8);
    s4 = 0x780000;
    jal(ctx, 0x5109A0u, gen::fn_cmd_sem_init_0050f960);
    lw(a0, s4, 2992);  // 0x780BB0
    jal(ctx, 0x5109ACu, gen::fn__scePollSema_005031b0);
    lw(v1, s4, 2992);  // 0x780BB0
    a0 = s2 ^ 0x8;
    if (v1 == v0) {
        // 0x005109c0
        charge(ctx, 6);
        a0 = 0;
        s3 = 0x780000;
        jal(ctx, 0x5109C4u, gen::fn_sceSifInitRpc_005068a8);
        lw(v0, s3, 3024);  // 0x780BD0
        s1 = 0;
        if (i64(v0) < 0) {
            // 0x005109d8
            charge(ctx, 2);
            s5 = 0x970000;
            for (;;) {
                // 0x00510a10
                charge(ctx, 1);
                s0 = addiu(s5, -9136);
                for (;;) {
                    // 0x00510a14
                    charge(ctx, 7);
                    a1 = lui(0x8000);
                    a0 = s0;
                    a1 = a1 | 0x59C;
                    a2 = 0;
                    jal(ctx, 0x510A20u, gen::fn_sceSifBindRpc_00507050);
                    if (i64(v0) < 0) {
                        // 0x00510a30
                        charge(ctx, 3);
                        lw(v0, s6, 2960);
                        v1 = 0x100000;
                        if (i64(v0) > 0) {
                            // 0x00510a3c
                            charge(ctx, 4);
                            a0 = 0x7C0000;
                            a0 = addiu(a0, -7496);  // "Libcdvd bind err CdDiskReady\n"
                            jal(ctx, 0x510A40u, gen::fn_scePrintf_00505e48);
                            v1 = 0x100000;
                        }
                        // 0x00510a4c
                        charge(ctx, 1);
                        v0 = si(-1);
                        for (;;) {
                            // 0x00510a50
                            charge(ctx, 7);
                            v1 = addiu(v1, -1);
                            if (v1 == v0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x00510a6c
                        charge(ctx, 2);
                        s0 = addiu(s5, -9136);
                        backedge(ctx);
                        continue;
                    }
                    lw(v0, s0, 36);
                    break;
                }
                // 0x00510a74
                charge(ctx, 2);
                cc = v0 == 0;  // the condition, before the delay slot changes it
                v0 = slti(s1, 17);
                if (!cc) {
                    break;
                }
                backedge(ctx);
                // 0x005109e0
                charge(ctx, 2);
                cc = v0 == 0;  // the condition, before the delay slot changes it
                v0 = addiu(s1, 1);
                if (cc) {
                    goto L_00510b14;
                }
                // 0x005109e8
                charge(ctx, 2);
                v1 = 0x100000;
                a0 = si(-1);
                for (;;) {
                    // 0x005109f0
                    charge(ctx, 7);
                    v1 = addiu(v1, -1);
                    if (v1 == a0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00510a0c
                charge(ctx, 1);
                s1 = v0;
            }
            // 0x00510a7c
            charge(ctx, 2);
            sw(zero, s3, 3024);
            goto L_00510a88;
        }
        // 0x00510a84
        charge(ctx, 1);
        s5 = 0x970000;
    L_00510a88:
        charge(ctx, 5);
        jal(ctx, 0x510A88u, gen::fn_DIntr_0050d3a0);
        v1 = 0x780000;
        sw(zero, v1, 3008);  // 0x780BC0
        if (v0 != 0) {
            // 0x00510a9c
            charge(ctx, 2);
            jal(ctx, 0x510A9Cu, gen::fn_EIntr_0050d3f0);
        }
        // 0x00510aa4
        charge(ctx, 20);
        v0 = 0x970000;
        a1 = 4;
        s0 = addiu(v0, -9072);  // &0x96DC90
        sw(s2, v0, -9072);  // 0x96DC90
        a0 = s0;
        jal(ctx, 0x510AB4u, gen::fn_sub_5067F8_005067f8);
        v0 = 0x780000;
        a0 = addiu(s5, -9136);
        s1 = addiu(v0, 9728);  // &0x782600
        a3 = s0;
        sw(zero, sp, 0x0);
        a1 = 0;
        a2 = 0;
        t0 = 4;
        t1 = s1;
        t2 = 4;
        t3 = 0;
        jal(ctx, 0x510AE4u, gen::fn_sceSifCallRpc_00507230);
        if (i64(v0) < 0) {
            // 0x00510af4
            charge(ctx, 4);
            lw(a0, s4, 2992);
            jal(ctx, 0x510AF8u, gen::fn__sceSignalSema_00503180);
            a0 = s2 ^ 0x8;
            goto L_00510b04;
        }
        lw(v0, s6, 2960);
        // 0x00510b30
        charge(ctx, 2);
        a0 = 0x7C0000;
        if (i64(v0) > 0) {
            // 0x00510b38
            charge(ctx, 2);
            a0 = addiu(a0, -7464);
            jal(ctx, 0x510B38u, gen::fn_scePrintf_00505e48);
        }
        // 0x00510b40
        charge(ctx, 6);
        v0 = 0x20000000;
        lw(a0, s4, 2992);
        v0 = s1 | v0;
        link(ctx, 0x510B4Cu);  // $ra first: the delay slot below depends on it
        lw(s0, v0, 0);
        call(ctx, gen::fn__sceSignalSema_00503180);
        v0 = s0;
    L_00510b58:
        charge(ctx, 1);
        ld(ra, sp, 0x80);
        // 0x00510b5c (the shared epilogue, written out on this path)
        charge(ctx, 9);
        ld(s6, sp, 0x70);
        ld(s5, sp, 0x60);
        ld(s4, sp, 0x50);
        ld(s3, sp, 0x40);
        ld(s2, sp, 0x30);
        ld(s1, sp, 0x20);
        ld(s0, sp, 0x10);
        sp = addiu(sp, 0x90);
        return;
    }
L_00510b04:
    charge(ctx, 4);
    v1 = si(-1);
    v0 = 6;
    if (a0 == 0) v0 = v1;
    goto L_00510b58;
L_00510b14:
    charge(ctx, 7);
    lw(a0, s4, 2992);
    jal(ctx, 0x510B18u, gen::fn__sceSignalSema_00503180);
    a0 = s2;
    jal(ctx, 0x510B20u, gen::fn_sceCdDiskReady_old_00510748);
    ld(ra, sp, 0x80);
    // 0x00510b5c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(s6, sp, 0x70);
    ld(s5, sp, 0x60);
    ld(s4, sp, 0x50);
    ld(s3, sp, 0x40);
    ld(s2, sp, 0x30);
    ld(s1, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x90);
}

// 0x00510B80 sceCdRead -- 480 bytes; frame 0x80: s5 sp+0x60, s4 sp+0x50, s3 sp+0x40, s2 sp+0x30, s1 sp+0x20, s0 sp+0x10, ra sp+0x70
// libcdvd sceCdRead: starts a sector read (lsn, count, buffer, mode) through the N-command RPC.
void sceCdRead(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00510b80
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    v1 = 0x780000;
    sd(s5, sp, 0x60);
    s5 = 0x780000;
    sd(s4, sp, 0x50);
    lw(v0, s5, 3000);  // sceCd_ee_read_mode
    s4 = a2;
    sd(s3, sp, 0x40);
    sd(s2, sp, 0x30);
    s3 = a0;
    sd(s1, sp, 0x20);
    s2 = addiu(v1, 3200);  // &sceCd_ncmdsdata
    sd(s0, sp, 0x10);
    s1 = a1;
    sd(ra, sp, 0x70);
    v0 = v0 & 0x1;
    s0 = a3;
    if (v0 == 0) {
        // 0x00510bc8
        charge(ctx, 5);
        jal(ctx, 0x510BC8u, gen::fn_sceCdNcmdDiskReady_005100b0);
        v1 = 6;
        cc = v0 == v1;  // the condition, before the delay slot changes it
        v0 = 0;
        if (!cc) {
            goto L_00510bdc;
        }
        // 0x00510d3c (the shared epilogue, written out on this path)
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
L_00510bdc:
    charge(ctx, 4);
    a0 = 4;
    jal(ctx, 0x510BDCu, gen::fn__sceCd_ncmd_prechk_0050ff58);
    t0 = 0x780000;
    if (v0 != 0) {
        // 0x00510bec
        charge(ctx, 18);
        sw(s3, s2, 0);
        sw(s1, s2, 4);
        s3 = 0x780000;
        sw(s4, s2, 8);
        a0 = addiu(s3, 7296);  // &0x781C80
        a1 = addiu(t0, 7488);
        a2 = 1;
        lbu(v0, s0, 0);
        sb(v0, s2, 12);
        lbu(v1, s0, 1);
        sb(v1, s2, 13);
        lbu(v0, s0, 2);
        sw(a0, s2, 16);
        sb(v0, s2, 14);
        sw(a1, s2, 20);
        lbu(a3, s0, 2);
        v0 = slti(a3, 2);
        if (a3 == a2) {
            // 0x00510c50
            charge(ctx, 3);
            v0 = 2328;
            mult(a1, s1, v0);
        } else {
            // 0x00510c34
            charge(ctx, 2);
            a1 = sll(s1, 11);
            if (v0 == 0) {
                // 0x00510c3c
                charge(ctx, 3);
                v0 = 2;
                cc = a3 == v0;  // the condition, before the delay slot changes it
                v0 = 2340;
                if (cc) {
                    // 0x00510c5c
                    charge(ctx, 1);
                    mult(a1, s1, v0);
                } else {
                    // 0x00510c48
                    charge(ctx, 2);
                }
            }
        }
        // 0x00510c60
        charge(ctx, 5);
        lw(v0, s5, 3000);
        s0 = addiu(t0, 7488);
        v0 = v0 & 0x2;
        sw(zero, t0, 7488);
        if (v0 == 0) {
            // 0x00510c74
            charge(ctx, 2);
            a0 = s4;
            jal(ctx, 0x510C74u, gen::fn_sub_5067F8_005067f8);
        }
        // 0x00510c7c
        charge(ctx, 14);
        s3 = addiu(s3, 7296);
        a1 = 144;
        a0 = s3;
        s4 = 0x780000;
        jal(ctx, 0x510C88u, gen::fn_sub_5067F8_005067f8);
        a0 = s2;
        a1 = 24;
        jal(ctx, 0x510C94u, gen::fn_sub_5067F8_005067f8);
        a0 = s0;
        a1 = 4;
        jal(ctx, 0x510CA0u, gen::fn_sub_5067F8_005067f8);
        lw(v0, s4, 2960);  // 0x780B90
        a0 = 0x7C0000;
        if (i64(v0) > 0) {
            // 0x00510cb4
            charge(ctx, 2);
            a0 = addiu(a0, -7416);
            jal(ctx, 0x510CB4u, gen::fn_scePrintf_00505e48);
        }
        // 0x00510cbc
        charge(ctx, 19);
        v0 = 1;
        s0 = 0x780000;
        sw(v0, s0, 3040);  // sceCdCbfunc_num
        s1 = 0x780000;
        a0 = 0x780000;
        t3 = 0x510000;
        sw(v0, s1, 2996);  // sceCd_c_cb_sem
        a0 = addiu(a0, 7504);  // &0x781D50
        sw(s3, sp, 0x0);
        a3 = s2;
        t3 = addiu(t3, -1880);  // &_sceCd_cd_read_intr
        a1 = 1;
        a2 = 1;
        t0 = 24;
        t1 = 0;
        t2 = 0;
        jal(ctx, 0x510CF8u, gen::fn_sceSifCallRpc_00507230);
        if (i64(v0) < 0) {
            // 0x00510d08
            charge(ctx, 5);
            sw(zero, s0, 3040);
            v0 = 0x780000;
            sw(zero, s1, 2996);
            link(ctx, 0x510D14u);  // $ra first: the delay slot below depends on it
            lw(a0, v0, 2984);
            call(ctx, gen::fn__sceSignalSema_00503180);
            goto L_00510d1c;
        }
        lw(v0, s4, 2960);
        // 0x00510d24
        charge(ctx, 2);
        cc = i64(v0) <= 0;  // the condition, before the delay slot changes it
        v0 = 1;
        if (!cc) {
            // 0x00510d2c
            charge(ctx, 4);
            a0 = 0x7C0000;
            a0 = addiu(a0, -7392);  // "cdread end\n"
            jal(ctx, 0x510D30u, gen::fn_scePrintf_00505e48);
            v0 = 1;
        }
        // 0x00510d3c (the shared epilogue, written out on this path)
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
L_00510d1c:
    charge(ctx, 2);
    v0 = 0;
    // 0x00510d3c (the shared epilogue, written out on this path)
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

// 0x00510EF0 sceCdGetError -- 152 bytes; frame 0x30: ra sp+0x20, s0 sp+0x10
// libcdvd sceCdGetError: the drive's last error through the S-command RPC.
void sceCdGetError(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00510ef0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    a0 = 3;
    sd(ra, sp, 0x20);
    link(ctx, 0x510EFCu);  // $ra first: the delay slot below depends on it
    sd(s0, sp, 0x10);
    call(ctx, gen::fn__sceCd_scmd_prechk_00510258);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = 0x780000;
    if (cc) {
        // 0x00510f14
        charge(ctx, 14);
        a0 = 0x780000;
        s0 = addiu(v0, 7552);
        a0 = addiu(a0, 9984);  // &0x782700
        sw(zero, sp, 0x0);
        a1 = 4;
        a2 = 0;
        a3 = 0;
        t0 = 0;
        t1 = s0;
        t2 = 4;
        t3 = 0;
        jal(ctx, 0x510F3Cu, gen::fn_sceSifCallRpc_00507230);
        v1 = 0x780000;
        if (i64(v0) >= 0) {
            // 0x00510f60
            charge(ctx, 6);
            v0 = 0x20000000;
            v0 = s0 | v0;
            lw(a0, v1, 2988);
            link(ctx, 0x510F6Cu);  // $ra first: the delay slot below depends on it
            lw(s0, v0, 0);
            call(ctx, gen::fn__sceSignalSema_00503180);
            v0 = s0;
        } else {
            // 0x00510f4c
            charge(ctx, 5);
            v0 = 0x780000;
            link(ctx, 0x510F50u);  // $ra first: the delay slot below depends on it
            lw(a0, v0, 2988);
            call(ctx, gen::fn__sceSignalSema_00503180);
            v0 = si(-1);
        }
    } else {
        // 0x00510f0c
        charge(ctx, 2);
        v0 = si(-1);
    }
    // 0x00510f78 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x30);
}

// 0x00511040 sceCdMmode -- 208 bytes; frame 0x50: s1 sp+0x20, s0 sp+0x10, s2 sp+0x30, ra sp+0x40
// libcdvd sceCdMmode: sets the media mode (CD / DVD) through the S-command RPC.
void sceCdMmode(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00511040
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s1, sp, 0x20);
    sd(s0, sp, 0x10);
    s1 = 0x780000;
    sd(s2, sp, 0x30);
    s0 = a0;
    sd(ra, sp, 0x40);
    s2 = addiu(s1, 8640);  // &0x7821C0
    a0 = 34;
    jal(ctx, 0x511060u, gen::fn__sceCd_scmd_prechk_00510258);
    if (v0 != 0) {
        sw(s0, s1, 8640);  // 0x7821C0
        // 0x00511078
        charge(ctx, 21);
        a0 = s2;
        a1 = 4;
        jal(ctx, 0x51107Cu, gen::fn_sub_5067F8_005067f8);
        a0 = 0x780000;
        a2 = 0x780000;
        v1 = 0x780000;
        v0 = 0x780000;
        lw(t0, a0, 10028);  // 0x78272C
        s0 = addiu(v0, 7552);  // &0x781D80
        a0 = 0x780000;
        lw(t2, a2, 10032);  // 0x782730
        lw(a1, v1, 10024);  // 0x782728
        a0 = addiu(a0, 9984);  // &0x782700
        a3 = s2;
        sw(zero, sp, 0x0);
        a2 = 0;
        t1 = s0;
        t3 = 0;
        jal(ctx, 0x5110BCu, gen::fn_sceSifCallRpc_00507230);
        v1 = 0x780000;
        if (i64(v0) >= 0) {
            // 0x005110e0
            charge(ctx, 6);
            v0 = 0x20000000;
            v0 = s0 | v0;
            lw(a0, v1, 2988);
            link(ctx, 0x5110ECu);  // $ra first: the delay slot below depends on it
            lw(s0, v0, 0);
            call(ctx, gen::fn__sceSignalSema_00503180);
            v0 = s0;
        } else {
            // 0x005110cc
            charge(ctx, 5);
            v0 = 0x780000;
            link(ctx, 0x5110D0u);  // $ra first: the delay slot below depends on it
            lw(a0, v0, 2988);
            call(ctx, gen::fn__sceSignalSema_00503180);
            v0 = 0;
        }
    } else {
        // 0x00511070
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x005110f8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x40);
    ld(s2, sp, 0x30);
    ld(s1, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x50);
}

// 0x005112D0 scePadInit2 -- 244 bytes; frame 0x40: ra sp+0x30, s1 sp+0x20, s0 sp+0x10
// libpad scePadInit2: clears the four ports' state, makes the init RPC call (function 16), then installs the pad
// SIF command handler with interrupts off.
void scePadInit2(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005112d0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = 0x970000;
    v0 = addiu(v0, -8944);  // &0x96DD10
    sd(ra, sp, 0x30);
    sd(s1, sp, 0x20);
    a1 = 0x970000;
    sd(s0, sp, 0x10);
    v0 = addiu(v0, 132);  // &0x96DD94
    v1 = 3;
    for (;;) {
        // 0x005112f8
        charge(ctx, 9);
        sw(zero, v0, -116);
        v1 = addiu(v1, -1);
        sw(zero, v0, -108);
        sw(zero, v0, -112);
        sw(zero, v0, -4);
        sw(zero, v0, 4);
        sw(zero, v0, 0);
        v0 = addiu(v0, 28);
        if (i64(v1) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0051131c
    charge(ctx, 20);
    v0 = 0x780000;
    s1 = addiu(a1, -8448);
    lw(v1, v0, 10068);  // 0x782754
    a0 = 0x970000;
    v0 = 16;
    sw(zero, s1, 16);
    sw(v0, a1, -8448);
    a0 = addiu(a0, -9024);  // &pad_rpc_cd0
    sw(v1, s1, 20);
    a1 = 1;
    a2 = 0;
    a3 = s1;
    sw(zero, sp, 0x0);
    t0 = 128;
    t1 = s1;
    t2 = 128;
    t3 = 0;
    jal(ctx, 0x51135Cu, gen::fn_sceSifCallRpc_00507230);
    cc = i64(v0) >= 0;  // the condition, before the delay slot changes it
    v0 = 0x780000;
    if (cc) {
        // 0x00511374
        charge(ctx, 12);
        link(ctx, 0x511374u);  // $ra first: the delay slot below depends on it
        sw(zero, v0, 10064);
        call(ctx, gen::fn_DIntr_0050d3a0);
        a1 = 0x510000;
        a0 = lui(0x8000);
        s0 = v0;
        a1 = addiu(a1, 4744);  // &_pad_intr_hdr
        a0 = a0 | 0x19;
        a2 = 0;
        jal(ctx, 0x511390u, gen::fn_sub_506430_00506430);
        v0 = 1;
        if (s0 != v0) {
            lw(v0, s1, 12);
        } else {
            // 0x005113a4
            charge(ctx, 3);
            jal(ctx, 0x5113A4u, gen::fn_EIntr_0050d3f0);
            lw(v0, s1, 12);
        }
    } else {
        // 0x0051136c
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x005113b0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x30);
    ld(s1, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x40);
}

// 0x00511FB8 scePadSetMainMode -- 180 bytes; frame 0x50: s0 sp+0x10, s2 sp+0x30, s1 sp+0x20, ra sp+0x40
// libpad scePadSetMainMode: sets the pad's main mode (digital / analog and lock) through the pad RPC.
void scePadSetMainMode(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00511fb8
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v1 = 0x970000;
    sd(s0, sp, 0x10);
    v0 = 6;
    s0 = addiu(v1, -8448);  // &pad_rpc_buf
    sd(s2, sp, 0x30);
    sd(s1, sp, 0x20);
    s2 = a0;
    sd(ra, sp, 0x40);
    s1 = a1;
    sw(a2, s0, 12);  // pad_rpc_buf+0xC
    a0 = 0x970000;
    sw(a3, s0, 16);  // pad_rpc_buf+0x10
    a0 = addiu(a0, -9024);  // &pad_rpc_cd0
    sw(v0, v1, -8448);  // pad_rpc_buf
    a1 = 1;
    sw(s2, s0, 4);  // pad_rpc_buf+0x4
    a2 = 0;
    sw(s1, s0, 8);  // pad_rpc_buf+0x8
    a3 = s0;
    sw(zero, sp, 0x0);
    t0 = 128;
    t1 = s0;
    t2 = 128;
    t3 = 0;
    jal(ctx, 0x512018u, gen::fn_sceSifCallRpc_00507230);
    if (i64(v0) >= 0) {
        lw(v1, s0, 20);  // pad_rpc_buf+0x14
        // 0x00512030
        charge(ctx, 3);
        v0 = 1;
        cc = v1 != v0;  // the condition, before the delay slot changes it
        v0 = v1;
        if (!cc) {
            // 0x0051203c
            charge(ctx, 6);
            a0 = s2;
            a1 = s1;
            a2 = 2;
            jal(ctx, 0x512044u, gen::fn_scePadSetReqState_00511b08);
            lw(v1, s0, 20);
            v0 = v1;
        }
    } else {
        // 0x00512028
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x00512054 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x40);
    ld(s2, sp, 0x30);
    ld(s1, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x50);
}

// 0x00512138 scePadSetActAlign -- 216 bytes; frame 0x50: s2 sp+0x30, s1 sp+0x20, s0 sp+0x10, ra sp+0x40
// libpad scePadSetActAlign: sets the actuator alignment through the pad RPC.
void scePadSetActAlign(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00512138
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v1 = 0x970000;
    sd(s2, sp, 0x30);
    v0 = 8;
    sd(s1, sp, 0x20);
    s2 = a0;
    sd(s0, sp, 0x10);
    s1 = a1;
    s0 = addiu(v1, -8448);  // &pad_rpc_buf
    sd(ra, sp, 0x40);
    sw(v0, v1, -8448);  // pad_rpc_buf
    a3 = addiu(s0, 12);  // &pad_rpc_buf+0xC
    sw(s2, s0, 4);  // pad_rpc_buf+0x4
    a1 = 0;
    sw(s1, s0, 8);  // pad_rpc_buf+0x8
    for (;;) {
        // 0x00512178
        charge(ctx, 8);
        v0 = addu(a2, a1);
        a0 = addu(a3, a1);
        lbu(v1, v0, 0);
        a1 = addiu(a1, 1);
        v0 = slti(a1, 6);
        sb(v1, a0, 0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00512198
    charge(ctx, 13);
    a0 = 0x970000;
    sw(zero, sp, 0x0);
    a0 = addiu(a0, -9024);  // &pad_rpc_cd0
    a1 = 1;
    a2 = 0;
    a3 = s0;
    t0 = 128;
    t1 = s0;
    t2 = 128;
    t3 = 0;
    jal(ctx, 0x5121BCu, gen::fn_sceSifCallRpc_00507230);
    if (i64(v0) >= 0) {
        lw(v1, s0, 20);
        // 0x005121d4
        charge(ctx, 3);
        v0 = 1;
        cc = v1 != v0;  // the condition, before the delay slot changes it
        v0 = v1;
        if (!cc) {
            // 0x005121e0
            charge(ctx, 6);
            a0 = s2;
            a1 = s1;
            a2 = 2;
            jal(ctx, 0x5121E8u, gen::fn_scePadSetReqState_00511b08);
            lw(v1, s0, 20);
            v0 = v1;
        }
    } else {
        // 0x005121cc
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x005121f8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x40);
    ld(s2, sp, 0x30);
    ld(s1, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x50);
}

// 0x00512640 scePadGetModVersion -- 100 bytes; frame 0x30: s0 sp+0x10, ra sp+0x20
// libpad scePadGetModVersion: the pad module version through the pad RPC.
void scePadGetModVersion(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00512640
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = 0x970000;
    sd(s0, sp, 0x10);
    v1 = 18;
    s0 = addiu(v0, -8448);  // &pad_rpc_buf
    a0 = 0x970000;
    sd(ra, sp, 0x20);
    a0 = addiu(a0, -9024);  // &pad_rpc_cd0
    sw(v1, v0, -8448);  // pad_rpc_buf
    a1 = 1;
    sw(zero, sp, 0x0);
    a2 = 0;
    a3 = s0;
    t0 = 128;
    t1 = s0;
    t2 = 128;
    t3 = 0;
    jal(ctx, 0x512680u, gen::fn_sceSifCallRpc_00507230);
    if (i64(v0) >= 0) {
        lw(v0, s0, 12);  // pad_rpc_buf+0xC
    } else {
        // 0x00512690
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x00512694 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x30);
}

// 0x00512D48 sceSdRemoteCallbackInit -- 252 bytes; frame 0x60: s1 sp+0x40, s0 sp+0x30, ra sp+0x50
// libsdr: once only: clears the callback table, tells the IOP (sceSdRemote), and creates and starts the
// callback thread _sdrCBThread (stack 0x96E080, 4 KiB, priority a0).
void sceSdRemoteCallbackInit(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00512d48
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(s1, sp, 0x40);
    s1 = 0x780000;
    sd(s0, sp, 0x30);
    lw(v0, s1, 10180);  // 0x7827C4
    s0 = a0;
    sd(ra, sp, 0x50);
    if (i64(v0) < 0) {
        // 0x00512d68
        charge(ctx, 40);
        a1 = 0x780000;
        v0 = 0x780000;
        v1 = 0x780000;
        a2 = 0x780000;
        a3 = 0x780000;
        t0 = 0x780000;
        t1 = 0x780000;
        t2 = 0x780000;
        t3 = 0x780000;
        sw(zero, a1, 10152);  // 0x7827A8
        sw(zero, v0, 10144);  // 0x7827A0
        a0 = 1;
        sw(zero, v1, 10148);  // 0x7827A4
        a1 = 0xE620;
        sw(zero, a2, 10156);  // 0x7827AC
        sw(zero, a3, 10160);  // 0x7827B0
        sw(zero, t0, 10164);  // 0x7827B4
        sw(zero, t1, 10168);  // 0x7827B8
        sw(zero, t2, 10172);  // 0x7827BC
        link(ctx, 0x512DB4u);  // $ra first: the delay slot below depends on it
        sw(zero, t3, 10176);
        call(ctx, gen::fn_sceSdRemote_005129c0);
        v1 = 0x510000;
        v0 = 0x970000;
        a1 = 0x7C0000;
        a2 = 0x7D0000;
        v1 = addiu(v1, 12160);  // &_sdrCBThread
        v0 = addiu(v0, -8064);  // &0x96E080
        a1 = addiu(a1, -6992);  // "SceSdrCallbackThread"
        a2 = addiu(a2, 11504);  // &gp_base
        a3 = 4096;
        sw(v1, sp, 0x4);
        sw(v0, sp, 0x8);
        a0 = sp;
        sw(a3, sp, 0xC);
        sw(s0, sp, 0x14);
        sw(a1, sp, 0x20);
        link(ctx, 0x512DF8u);  // $ra first: the delay slot below depends on it
        sw(a2, sp, 0x10);
        call(ctx, gen::fn__sceCreateThread_00502f60);
        sw(v0, s1, 10180);
        if (i64(v0) < 0) {
            goto L_00512e2c;
        }
        // 0x00512e08
        charge(ctx, 6);
        a0 = v0;
        sw(v0, sp, 0x20);
        a1 = 0;
        jal(ctx, 0x512E10u, gen::fn_StartThread_005042a0);
        cc = i64(v0) >= 0;  // the condition, before the delay slot changes it
        lw(v0, sp, 0x20);
        if (!cc) {
            // 0x00512e20
            charge(ctx, 3);
            a0 = 0x7C0000;
            a0 = addiu(a0, -6968);  // "Can't start thread for streaming.\n"
            jal(ctx, 0x512E24u, gen::fn_scePrintf_00505e48);
            goto L_00512e2c;
        }
        // 0x00512e30 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(ra, sp, 0x50);
        ld(s1, sp, 0x40);
        ld(s0, sp, 0x30);
        sp = addiu(sp, 0x60);
        return;
    }
L_00512e2c:
    charge(ctx, 1);
    v0 = si(-1);
    // 0x00512e30 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x50);
    ld(s1, sp, 0x40);
    ld(s0, sp, 0x30);
    sp = addiu(sp, 0x60);
}

// 0x00512F80 _sdrCBThread -- 112 bytes; frame 0x20: s0 sp+0x0, ra sp+0x10
// libsdr's callback thread: registers the EE-side RPC server for the IOP's libsd callbacks and runs its loop.
void _sdrCBThread(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00512f80
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    a0 = 0;
    jal(ctx, 0x512F8Cu, gen::fn_sceSifInitRpc_005068a8);
    s0 = 0x970000;
    s0 = addiu(s0, -3904);  // &0x96F0C0
    jal(ctx, 0x512F98u, gen::fn__sceGetThreadId_00503050);
    a0 = s0;
    a1 = v0;
    jal(ctx, 0x512FA4u, gen::fn_sceSifSetRpcQueue_00507470);
    a0 = 0x970000;
    a2 = 0x510000;
    a3 = 0x970000;
    a1 = lui(0x8000);
    t2 = s0;
    t0 = 0;
    t1 = 0;
    a2 = addiu(a2, 12272);  // &_sdrCB
    a3 = addiu(a3, -3968);  // &0x96F080
    a0 = addiu(a0, -3880);  // &0x96F0D8
    a1 = a1 | 0x704;
    jal(ctx, 0x512FD4u, gen::fn_sceSifRegisterRpc_00507508);
    a0 = s0;
    ld(ra, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
    gen::fn_sceSifRpcLoop_00507920(ctx);  // a tail call that does not return (the recompiled body falls through after it)
}

// 0x0051AE38 sceMc2SifCallback -- 44 bytes; frame 0x10: ra sp+0x0
// libmc2's SIF callback (data reference): signals the memory-card semaphore, then sync + ei.
void sceMc2SifCallback(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051ae38
    enter(ctx, 11);  // entry check point + this block's cycles
    v0 = 0x980000;
    sp = addiu(sp, -0x10);
    lw(a0, v0, 21760);  // 0x985500
    sd(ra, sp, 0x0);
    jal(ctx, 0x51AE48u, gen::fn__sceiSignalSema_00503190);
    sync(ctx, 0);
    ei(ctx);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0051C360 sceDbcGetModVersion -- 84 bytes; frame 0x30: s0 sp+0x10, ra sp+0x20
// libdbc: the DBC module version through its RPC.
void sceDbcGetModVersion(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051c360
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    a0 = 0x990000;
    sd(s0, sp, 0x10);
    a1 = lui(0x8000);
    s0 = 0x990000;
    sd(ra, sp, 0x20);
    a3 = addiu(s0, 26688);  // &0x996840
    a0 = addiu(a0, 26432);  // &0x996740
    sw(zero, sp, 0x0);
    a1 = a1 | 0x1363;
    a2 = 0;
    t0 = 144;
    t1 = a3;
    t2 = 144;
    t3 = 0;
    jal(ctx, 0x51C398u, gen::fn_sceSifCallRpc_00507230);
    lw(v0, s0, 26688);  // 0x996840
    ld(ra, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x30);
}

// 0x0051C700 sceDbcSetWorkAddr -- 108 bytes; frame 0x30: s0 sp+0x10, ra sp+0x20
// libdbc: hands the IOP the work address through the DBC RPC.
void sceDbcSetWorkAddr(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0051c700
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = 0x990000;
    sd(s0, sp, 0x10);
    a1 = lui(0x8000);
    s0 = 0x990000;
    sd(ra, sp, 0x20);
    a3 = addiu(s0, 26688);  // &0x996840
    a1 = a1 | 0x1304;
    sw(a0, a3, 4);  // 0x996844
    a2 = 0;
    a0 = addiu(v0, 26432);  // &0x996740
    sw(zero, sp, 0x0);
    t0 = 144;
    t1 = a3;
    t2 = 144;
    t3 = 0;
    jal(ctx, 0x51C73Cu, gen::fn_sceSifCallRpc_00507230);
    cc = i64(v0) >= 0;  // the condition, before the delay slot changes it
    lw(v0, s0, 26688);  // 0x996840
    if (!cc) {
        // 0x0051c74c
        charge(ctx, 4);
        a0 = 0x7C0000;
        a0 = addiu(a0, -6336);  // "sceDbcSetWorkAddr: rpc error\n"
        jal(ctx, 0x51C750u, gen::fn_DPRINT_0051d588);
        v0 = 0;
    }
    // 0x0051c75c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x30);
}

// 0x0051C770 sceDbcCreateSocket -- 304 bytes; frame 0x70: s3 sp+0x40, s2 sp+0x30, s0 sp+0x10, ra sp+0x60, s4 sp+0x50, s1 sp+0x20
// libdbc: creates a device socket through the DBC RPC (under the DBC semaphore).
void sceDbcCreateSocket(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051c770
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    v0 = 0x780000;
    sd(s3, sp, 0x40);
    sd(s2, sp, 0x30);
    s3 = a2;
    sd(s0, sp, 0x10);
    s2 = a1;
    lw(v1, v0, 11008);  // 0x782B00
    s0 = a0;
    sd(ra, sp, 0x60);
    sd(s4, sp, 0x50);
    sd(s1, sp, 0x20);
    if (v1 != 0) {
        // 0x0051c7ac
        charge(ctx, 21);
        s4 = 0x990000;
        link(ctx, 0x51C7B0u);  // $ra first: the delay slot below depends on it
        lw(a0, s4, 28672);  // 0x997000
        call(ctx, gen::fn__sceWaitSema_005031a0);
        lw(v0, s0, 0);
        a3 = 0x990000;
        s1 = addiu(a3, 26688);  // &0x996840
        a2 = addiu(s0, 20);
        sw(v0, a3, 26688);  // 0x996840
        t0 = addiu(s1, 20);  // &0x996854
        sw(s2, s1, 40);  // 0x996868
        a1 = 0;
        lw(v0, s0, 4);
        sw(s3, s1, 44);  // 0x99686C
        sw(v0, s1, 4);  // 0x996844
        lw(v1, s0, 8);
        sw(v1, s1, 8);  // 0x996848
        lw(v0, s0, 12);
        sw(v0, s1, 12);  // 0x99684C
        lw(v1, s0, 16);
        sw(v1, s1, 16);  // 0x996850
        for (;;) {
            // 0x0051c800
            charge(ctx, 8);
            v0 = addu(a2, a1);
            a0 = addu(t0, a1);
            lbu(v1, v0, 0);
            a1 = addiu(a1, 1);
            v0 = slti(a1, 16);
            sb(v1, a0, 0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0051c820
        charge(ctx, 14);
        a3 = addiu(a3, 26688);
        a1 = lui(0x8000);
        a0 = 0x990000;
        sw(zero, sp, 0x0);
        a0 = addiu(a0, 26432);  // &0x996740
        a1 = a1 | 0x1301;
        a2 = 0;
        t0 = 144;
        t1 = a3;
        t2 = 144;
        t3 = 0;
        jal(ctx, 0x51C848u, gen::fn_sceSifCallRpc_00507230);
        lw(a0, s4, 28672);
        if (i64(v0) >= 0) {
            // 0x0051c874
            charge(ctx, 3);
            link(ctx, 0x51C874u);  // $ra first: the delay slot below depends on it
            lw(s0, s1, 36);
            call(ctx, gen::fn__sceSignalSema_00503180);
            v0 = s0;
        } else {
            // 0x0051c858
            charge(ctx, 7);
            a0 = 0x7C0000;
            a0 = addiu(a0, -6304);  // "sceDbcCreateSocket: rpc error\n"
            jal(ctx, 0x51C85Cu, gen::fn_DPRINT_0051d588);
            link(ctx, 0x51C864u);  // $ra first: the delay slot below depends on it
            lw(a0, s4, 28672);
            call(ctx, gen::fn__sceSignalSema_00503180);
            v0 = 0;
        }
    } else {
        // 0x0051c7a4
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x0051c880 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x60);
    ld(s4, sp, 0x50);
    ld(s3, sp, 0x40);
    ld(s2, sp, 0x30);
    ld(s1, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x70);
}

// 0x0051D308 sceDbcSendData3 -- 344 bytes; frame 0x90: s5 sp+0x60, s4 sp+0x50, s3 sp+0x40, s1 sp+0x20, s0 sp+0x10, ra sp+0x80, s6 sp+0x70, s2 sp+0x30
// libdbc: sends data to a socket (the third send form) through the DBC RPC (under the DBC semaphore).
void sceDbcSendData3(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0051d308
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(s5, sp, 0x60);
    sd(s4, sp, 0x50);
    s5 = t0;
    sd(s3, sp, 0x40);
    s4 = a3;
    sd(s1, sp, 0x20);
    s3 = a0;
    sd(s0, sp, 0x10);
    sd(ra, sp, 0x80);
    s0 = a2;
    sd(s6, sp, 0x70);
    sd(s2, sp, 0x30);
    lw(v1, s0, 0);
    v0 = slti(v1, 1153);
    s1 = a1;
    if (v0 != 0) {
        // 0x0051d364
        charge(ctx, 9);
        s2 = 0x990000;
        s6 = 0x990000;
        link(ctx, 0x51D36Cu);  // $ra first: the delay slot below depends on it
        lw(a0, s2, 28672);  // 0x997000
        call(ctx, gen::fn__sceWaitSema_005031a0);
        a0 = addiu(s6, 26512);  // &0x996790
        jal(ctx, 0x51D374u, gen::fn_sceSifCheckStatRpc_00507430);
        v1 = 1;
        a3 = 0x990000;
        if (v0 == v1) {
            // 0x0051d388
            charge(ctx, 5);
            a0 = 0x7C0000;
            a0 = addiu(a0, -5880);  // "dbcman : SendData3 BUSY\n"
            jal(ctx, 0x51D38Cu, gen::fn_DPRINT_0051d588);
            goto L_0051d41c;
        }
        // 0x0051d39c
        charge(ctx, 8);
        sw(s3, a3, 26880);
        a0 = addiu(a3, 26880);
        sw(s1, a0, 4);
        lw(v0, s0, 0);
        sw(v0, a0, 8);
        lw(v1, s0, 0);
        a1 = 0;
        if (i64(v1) > 0) {
            // 0x0051d3bc
            charge(ctx, 3);
            a2 = addiu(a0, 12);
            v0 = addu(s4, a1);
            for (;;) {
                // 0x0051d3c8
                charge(ctx, 8);
                a0 = addu(a2, a1);
                lbu(v1, v0, 0);
                a1 = addiu(a1, 1);
                sb(v1, a0, 0);
                lw(v0, s0, 0);
                v0 = slt(a1, v0);
                cc = v0 != 0;  // the condition, before the delay slot changes it
                v0 = addu(s4, a1);
                if (!cc) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x0051d3e8
        charge(ctx, 13);
        a3 = addiu(a3, 26880);
        a1 = lui(0x8000);
        a0 = addiu(s6, 26512);
        t3 = s5;
        sw(zero, sp, 0x0);
        a1 = a1 | 0x131C;
        a2 = 1;
        t0 = 1168;
        t1 = a3;
        t2 = 1168;
        jal(ctx, 0x51D40Cu, gen::fn_sceSifCallRpc_00507230);
        if (i64(v0) >= 0) {
            // 0x0051d42c
            charge(ctx, 3);
            link(ctx, 0x51D42Cu);  // $ra first: the delay slot below depends on it
            lw(a0, s2, 28672);
            call(ctx, gen::fn__sceSignalSema_00503180);
            v0 = 1;
        } else {
        L_0051d41c:
            charge(ctx, 4);
            link(ctx, 0x51D41Cu);  // $ra first: the delay slot below depends on it
            lw(a0, s2, 28672);
            call(ctx, gen::fn__sceSignalSema_00503180);
            v0 = 0;
        }
    } else {
        // 0x0051d34c
        charge(ctx, 6);
        a0 = 0x7C0000;
        a1 = v1;
        a0 = addiu(a0, -5928);  // "libdbc: SendData3 data length too long [%d]\n"
        jal(ctx, 0x51D354u, gen::fn_DPRINT_0051d588);
        v0 = 0;
    }
    // 0x0051d438 (the shared epilogue, written out on this path)
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

// 0x0051DBC0 sceSkSsSOUND_Send -- 176 bytes; frame 0xC0: s1 sp+0x10, s2 sp+0x20, s0 sp+0x0, ra sp+0x30
// Standard Kit: SOUND Send (a transfer from IOP memory to SPU2) through sceSdRemote.
void sceSkSsSOUND_Send(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051dbc0
    enter(ctx, 44);  // entry check point + this block's cycles
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
    link(ctx, 0x51DC08u);  // $ra first: the delay slot below depends on it
    sd(t3, sp, 0xB8);
    call(ctx, gen::fn_memset_00521408);
    sw(zero, s1, 11136);  // sk_sound_cmdblk
    v0 = 10;
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
    lw(v0, sp, 0x98);
    s0 = addiu(s0, 4);  // &sk_sound_cmdblk+0x10
    sw(v1, s0, 0);  // sk_sound_cmdblk+0x10
    link(ctx, 0x51DC50u);  // $ra first: the delay slot below depends on it
    sw(v0, s0, 4);  // sk_sound_cmdblk+0x14
    call(ctx, gen::fn_sceSdRemote_005129c0);
    ld(ra, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0xC0);
}

// 0x0051DC70 sceSkSsHSYNTH_Bind -- 212 bytes; frame 0xD0: s2 sp+0x20, s3 sp+0x30, s0 sp+0x0, s1 sp+0x10, ra sp+0x40
// Standard Kit: HSYNTH Bind: a 64-byte block {0x1000000, 0, a1..a6} through sceSdRemote; returns the id.
void sceSkSsHSYNTH_Bind(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051dc70
    enter(ctx, 53);  // entry check point + this block's cycles
    sp = addiu(sp, -0xD0);
    sd(s2, sp, 0x20);
    s2 = 0x780000;
    sd(s3, sp, 0x30);
    sd(s0, sp, 0x0);
    s3 = a0;
    s0 = addiu(s2, 11200);  // &sk_hsynth_cmdblk
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
    s0 = addiu(s0, 4);  // &sk_hsynth_cmdblk+0x4
    sd(t1, sp, 0xB8);
    sd(t2, sp, 0xC0);
    link(ctx, 0x51DCC0u);  // $ra first: the delay slot below depends on it
    sd(t3, sp, 0xC8);
    call(ctx, gen::fn_memset_00521408);
    v0 = 0x1000000;
    lw(v1, sp, 0x98);
    sw(v0, s2, 11200);  // sk_hsynth_cmdblk
    a2 = s1;
    sw(zero, s0, 0);  // sk_hsynth_cmdblk+0x4
    a0 = 1;
    s0 = addiu(s0, 4);  // &sk_hsynth_cmdblk+0x8
    a1 = 0x90F0;
    lw(v0, sp, 0xA0);
    a3 = 64;
    sw(s3, s0, 0);  // sk_hsynth_cmdblk+0x8
    s0 = addiu(s0, 4);  // &sk_hsynth_cmdblk+0xC
    lw(t0, sp, 0xA8);
    sw(v1, s0, 0);  // sk_hsynth_cmdblk+0xC
    lw(v1, sp, 0xB0);
    s0 = addiu(s0, 4);  // &sk_hsynth_cmdblk+0x10
    sw(v0, s0, 0);  // sk_hsynth_cmdblk+0x10
    lw(v0, sp, 0xB8);
    s0 = addiu(s0, 4);  // &sk_hsynth_cmdblk+0x14
    sw(t0, s0, 0);  // sk_hsynth_cmdblk+0x14
    s0 = addiu(s0, 4);  // &sk_hsynth_cmdblk+0x18
    sw(v0, s0, 4);  // sk_hsynth_cmdblk+0x1C
    link(ctx, 0x51DD20u);  // $ra first: the delay slot below depends on it
    sw(v1, s0, 0);  // sk_hsynth_cmdblk+0x18
    call(ctx, gen::fn_sceSdRemote_005129c0);
    ld(ra, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0xD0);
}

// 0x0051DD48 sceSkSsHSYNTH_Unbind -- 168 bytes; frame 0xD0: s2 sp+0x20, s3 sp+0x30, s0 sp+0x0, s1 sp+0x10, ra sp+0x40
// Standard Kit: HSYNTH Unbind: the block {0x1000000, 1, kind, id} through sceSdRemote.
void sceSkSsHSYNTH_Unbind(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051dd48
    enter(ctx, 42);  // entry check point + this block's cycles
    sp = addiu(sp, -0xD0);
    sd(s2, sp, 0x20);
    s2 = 0x780000;
    sd(s3, sp, 0x30);
    sd(s0, sp, 0x0);
    s3 = a0;
    s0 = addiu(s2, 11200);  // &sk_hsynth_cmdblk
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
    s0 = addiu(s0, 4);  // &sk_hsynth_cmdblk+0x4
    sd(t1, sp, 0xB8);
    sd(t2, sp, 0xC0);
    link(ctx, 0x51DD98u);  // $ra first: the delay slot below depends on it
    sd(t3, sp, 0xC8);
    call(ctx, gen::fn_memset_00521408);
    v0 = 0x1000000;
    v1 = 1;
    sw(v0, s2, 11200);  // sk_hsynth_cmdblk
    a2 = s1;
    sw(v1, s0, 0);  // sk_hsynth_cmdblk+0x4
    a0 = 1;
    s0 = addiu(s0, 4);  // &sk_hsynth_cmdblk+0x8
    a1 = 0x90F0;
    lw(v0, sp, 0x98);
    a3 = 64;
    sw(s3, s0, 0);  // sk_hsynth_cmdblk+0x8
    link(ctx, 0x51DDCCu);  // $ra first: the delay slot below depends on it
    sw(v0, s0, 4);  // sk_hsynth_cmdblk+0xC
    call(ctx, gen::fn_sceSdRemote_005129c0);
    ld(ra, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0xD0);
}

// 0x0051DDF0 sceSkSsSESQ_Bind -- 188 bytes; frame 0xD0: s2 sp+0x20, s3 sp+0x30, s0 sp+0x0, s1 sp+0x10, ra sp+0x40
// Standard Kit: SESQ Bind: the block {0x4000000, 0, a1..a4} through sceSdRemote; returns the id.
void sceSkSsSESQ_Bind(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051ddf0
    enter(ctx, 47);  // entry check point + this block's cycles
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
    link(ctx, 0x51DE40u);  // $ra first: the delay slot below depends on it
    sd(t3, sp, 0xC8);
    call(ctx, gen::fn_memset_00521408);
    v0 = 0x4000000;
    lw(a3, sp, 0x98);
    sw(v0, s2, 11264);  // sk_sesq_cmdblk
    a2 = s1;
    sw(zero, s0, 0);  // sk_sesq_cmdblk+0x4
    a0 = 1;
    s0 = addiu(s0, 4);  // &sk_sesq_cmdblk+0x8
    a1 = 0x90F0;
    lw(v1, sp, 0xA0);
    sw(s3, s0, 0);  // sk_sesq_cmdblk+0x8
    s0 = addiu(s0, 4);  // &sk_sesq_cmdblk+0xC
    lw(v0, sp, 0xA8);
    sw(a3, s0, 0);  // sk_sesq_cmdblk+0xC
    s0 = addiu(s0, 4);  // &sk_sesq_cmdblk+0x10
    a3 = 64;
    sw(v0, s0, 4);  // sk_sesq_cmdblk+0x14
    link(ctx, 0x51DE88u);  // $ra first: the delay slot below depends on it
    sw(v1, s0, 0);  // sk_sesq_cmdblk+0x10
    call(ctx, gen::fn_sceSdRemote_005129c0);
    ld(ra, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0xD0);
}

// 0x0051DEB0 sceSkSsSESQ_Unbind -- 168 bytes; frame 0xD0: s2 sp+0x20, s3 sp+0x30, s0 sp+0x0, s1 sp+0x10, ra sp+0x40
// Standard Kit: SESQ Unbind: the block {0x4000000, 1, kind, id} through sceSdRemote.
void sceSkSsSESQ_Unbind(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051deb0
    enter(ctx, 42);  // entry check point + this block's cycles
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
    link(ctx, 0x51DF00u);  // $ra first: the delay slot below depends on it
    sd(t3, sp, 0xC8);
    call(ctx, gen::fn_memset_00521408);
    v0 = 0x4000000;
    v1 = 1;
    sw(v0, s2, 11264);  // sk_sesq_cmdblk
    a2 = s1;
    sw(v1, s0, 0);  // sk_sesq_cmdblk+0x4
    a0 = 1;
    s0 = addiu(s0, 4);  // &sk_sesq_cmdblk+0x8
    a1 = 0x90F0;
    lw(v0, sp, 0x98);
    a3 = 64;
    sw(s3, s0, 0);  // sk_sesq_cmdblk+0x8
    link(ctx, 0x51DF34u);  // $ra first: the delay slot below depends on it
    sw(v0, s0, 4);  // sk_sesq_cmdblk+0xC
    call(ctx, gen::fn_sceSdRemote_005129c0);
    ld(ra, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0xD0);
}

// 0x0053B220 ADXF_SetupRofs -- 44 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// ADXF_SetupRofs: the ROFS setup under the ADX environment lock.
void ADXF_SetupRofs(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053b220
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x53B22Cu, gen::fn___env_lock_0053b598);
    a0 = s0;
    jal(ctx, 0x53B234u, gen::fn_adxf_SetupRofs_0053b250);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn___env_unlock_0053b5a0(ctx);  // tail call
}

// 0x0053B2C0 ADXF_AddRofsVol -- 88 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// ADXF_AddRofsVol: adds a ROFS volume (name, image path) under the ADX environment lock.
void ADXF_AddRofsVol(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053b2c0
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x53B2DCu, gen::fn___env_lock_0053b598);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    jal(ctx, 0x53B2ECu, gen::fn_adxf_AddRofsVol_0053b318);
    s0 = v0;
    jal(ctx, 0x53B2F4u, gen::fn___env_unlock_0053b5a0);
    ld(s1, sp, 0x8);
    v0 = s0;
    ld(s2, sp, 0x10);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0053B4F8 sub_53B4F8 -- 44 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Sets the ADXF default device (adxf_SetDefDev) under the ADX environment lock.
void sub_53B4F8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053b4f8
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x53B504u, gen::fn___env_lock_0053b598);
    a0 = s0;
    jal(ctx, 0x53B50Cu, gen::fn_adxf_SetDefDev_0053b528);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn___env_unlock_0053b5a0(ctx);  // tail call
}

// 0x0053B868 ADXF_LoadPartitionNw -- 104 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// ADXF_LoadPartitionNw: starts loading an AFS partition (no wait) under the ADX environment lock.
void ADXF_LoadPartitionNw(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053b868
    enter(ctx, 26);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s3, sp, 0x18);
    sd(ra, sp, 0x20);
    s3 = a3;
    jal(ctx, 0x53B88Cu, gen::fn_sub_53E088_0053e088);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    a3 = s3;
    jal(ctx, 0x53B8A0u, gen::fn_adxf_LoadPartitionNw_0053b8d0);
    s0 = v0;
    jal(ctx, 0x53B8A8u, gen::fn_sub_53E0A0_0053e0a0);
    ld(s1, sp, 0x8);
    v0 = s0;
    ld(s2, sp, 0x10);
    ld(s0, sp, 0x0);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0053BEF0 sub_53BEF0 -- 676 bytes; frame 0x70: s4 sp+0x40, s0 sp+0x20, s2 sp+0x30, s3 sp+0x38, s5 sp+0x48, s7 sp+0x58, fp sp+0x60, s1 sp+0x28, s6 sp+0x50, ra sp+0x68
// Starts an AFS partition load: refuses a second load in parallel, checks the temporary buffer, opens the file,
// clears the partition record and starts reading the AFS header (adxf_ReadNw); errors through sub_53AE08.
void sub_53BEF0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x0053bef0
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    v0 = 0x780000;
    sd(s4, sp, 0x40);
    s4 = addiu(v0, 21464);  // &0x7853D8
    lw(v0, s4, 0);  // 0x7853D8
    v1 = 2;
    sd(s0, sp, 0x20);
    s0 = t3;
    sd(s2, sp, 0x30);
    s2 = a0;
    sd(s3, sp, 0x38);
    sd(s5, sp, 0x48);
    s5 = a3;
    sd(s7, sp, 0x58);
    s7 = a1;
    sd(fp, sp, 0x60);
    fp = a2;
    sd(s1, sp, 0x28);
    sd(s6, sp, 0x50);
    sd(ra, sp, 0x68);
    sw(t0, sp, 0x0);
    sw(t1, sp, 0xC);
    sw(t2, sp, 0x10);
    lw(s3, sp, 0x78);
    if (v0 != v1) {
        // 0x0053bf68
        charge(ctx, 5);
        t0 = 0x780000;
        s6 = addiu(t0, 21456);  // &0x7853D0
        lw(a0, s6, 0);  // 0x7853D0
        v0 = 0x780000;
        if (a0 != 0) {
            // 0x0053bf7c
            charge(ctx, 4);
            jal(ctx, 0x53BF7Cu, gen::fn_sub_53CE00_0053ce00);
            sw(zero, s6, 0);
            v0 = 0x780000;
        }
        // 0x0053bf8c
        charge(ctx, 8);
        a0 = si(-1);
        s1 = addiu(v0, 21460);
        v1 = 1;
        sw(a0, s1, 0);
        sw(v1, s4, 0);
        lw(v0, sp, 0x70);
        a0 = 0x7C0000;
        if (v0 == 0) {
            // 0x0053bfac
            charge(ctx, 2);
            a0 = addiu(a0, 7048);
            goto L_0053bfc8;
        }
        // 0x0053bfb8
        charge(ctx, 2);
        a0 = s2;
        if (i64(s3) > 0) {
            // 0x0053bfe0
            charge(ctx, 4);
            a1 = s0;
            jal(ctx, 0x53BFE0u, gen::fn_sub_53B6B0_0053b6b0);
            v1 = 4;
            if (i64(v0) >= 0) {
                // 0x0053bff0
                charge(ctx, 3);
                lw(v0, s1, 0);
                a0 = 0x7C0000;
                if (i64(v0) >= 0) {
                    // 0x0053bffc
                    charge(ctx, 2);
                    a0 = addiu(a0, 7136);
                    goto L_0053c0b4;
                }
                // 0x0053c008
                charge(ctx, 15);
                v1 = 2;
                v0 = 0x780000;
                sw(v1, s4, 0);
                a0 = s0;
                sw(s2, s1, 0);
                a1 = 0;
                a2 = 284;
                link(ctx, 0x53C024u);  // $ra first: the delay slot below depends on it
                sw(zero, v0, 21452);
                call(ctx, gen::fn_memset_00521408);
                v1 = sll(s2, 2);
                at = 0x780000;
                at = addu(at, v1);
                sw(s0, at, 20128);
                sw(zero, s0, 0);
                if (s5 == 0) {
                    // 0x0053c044
                    charge(ctx, 5);
                    a0 = s7;
                    a1 = fp;
                    jal(ctx, 0x53C048u, gen::fn_sub_53CCC0_0053ccc0);
                    sw(v0, s6, 0);
                    if (v0 == 0) {
                        goto L_0053c0ac;
                    }
                    // 0x0053c058
                    charge(ctx, 9);
                    a0 = s7;
                    a1 = fp;
                    a2 = addiu(s0, 16);
                    a3 = sp;
                    t0 = addiu(sp, 0x4);
                    t1 = addiu(sp, 0x8);
                    jal(ctx, 0x53C06Cu, gen::fn_sub_53DD98_0053dd98);
                    if (i64(v0) < 0) {
                        // 0x0053c07c
                        charge(ctx, 1);
                        v1 = 4;
                        goto L_0053c080;
                    }
                    lw(v0, sp, 0x4);
                    // 0x0053c088
                    charge(ctx, 2);
                    sw(v0, s0, 276);
                    goto L_0053c0e8;
                }
                // 0x0053c090
                charge(ctx, 7);
                lw(a1, sp, 0x0);
                a0 = s5;
                lw(a3, sp, 0x10);
                link(ctx, 0x53C09Cu);  // $ra first: the delay slot below depends on it
                lw(a2, sp, 0xC);
                call(ctx, gen::fn_sub_53CAE0_0053cae0);
                sw(v0, s6, 0);
                if (v0 != 0) {
                    // 0x0053c0d0
                    charge(ctx, 6);
                    a1 = s5;
                    a0 = addiu(s0, 16);
                    a2 = 256;
                    jal(ctx, 0x53C0D8u, gen::fn_strncpy_00524828);
                    lw(t0, sp, 0xC);
                    sw(t0, s0, 276);
                L_0053c0e8:
                    charge(ctx, 22);
                    lw(v0, sp, 0x80);
                    v1 = addiu(s3, 2047);
                    sb(zero, s0, 14);
                    sb(v0, s0, 15);
                    v0 = slti(s3, 0);
                    if (v0 != 0) s3 = v1;
                    v0 = 0x780000;
                    lw(a0, sp, 0x0);
                    s2 = addiu(v0, 21456);  // &0x7853D0
                    a3 = sra(s3, 11);
                    v1 = 0x780000;
                    sw(a0, s0, 272);
                    v0 = 0x780000;
                    a1 = a3;
                    lw(a0, s2, 0);  // 0x7853D0
                    lw(a2, sp, 0x70);
                    sw(a3, v1, 21476);  // 0x7853E4
                    link(ctx, 0x53C12Cu);  // $ra first: the delay slot below depends on it
                    sw(a2, v0, 21472);
                    call(ctx, gen::fn_adxf_ReadNw_0053d3d8);
                    s1 = v0;
                    if (i64(s1) >= 0) {
                        sw(zero, s0, 8);
                        // 0x0053c160
                        charge(ctx, 1);
                        v0 = 0;
                    } else {
                        // 0x0053c140
                        charge(ctx, 7);
                        link(ctx, 0x53C140u);  // $ra first: the delay slot below depends on it
                        lw(a0, s2, 0);
                        call(ctx, gen::fn_sub_53CE00_0053ce00);
                        v0 = 4;
                        v1 = 0x780000;
                        sw(v0, v1, 21464);  // 0x7853D8
                        v0 = s1;
                    }
                } else {
                L_0053c0ac:
                    charge(ctx, 2);
                    a0 = 0x7C0000;
                    a0 = addiu(a0, 7184);  // "E9040804:can't open file.(load partition)"
                L_0053c0b4:
                    charge(ctx, 6);
                    jal(ctx, 0x53C0B4u, gen::fn_sub_53AE08_0053ae08);
                    v0 = 4;
                    sw(v0, s4, 0);
                    v0 = si(-1);
                }
                // 0x0053c164 (the shared epilogue, written out on this path)
                charge(ctx, 12);
                ld(s0, sp, 0x20);
                ld(s1, sp, 0x28);
                ld(s2, sp, 0x30);
                ld(s3, sp, 0x38);
                ld(s4, sp, 0x40);
                ld(s5, sp, 0x48);
                ld(s6, sp, 0x50);
                ld(s7, sp, 0x58);
                ld(fp, sp, 0x60);
                ld(ra, sp, 0x68);
                sp = addiu(sp, 0x70);
                return;
            }
        L_0053c080:
            charge(ctx, 2);
            sw(v1, s4, 0);
        } else {
            // 0x0053bfc0
            charge(ctx, 2);
            a0 = 0x7C0000;
            a0 = addiu(a0, 7096);  // "E1110702:'tbsize' <= 0.(load partition)"
        L_0053bfc8:
            charge(ctx, 6);
            jal(ctx, 0x53BFC8u, gen::fn_sub_53AE08_0053ae08);
            v0 = 4;
            sw(v0, s4, 0);
            v0 = si(-3);
        }
    } else {
        // 0x0053bf54
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 6984);  // "E20040917 : It is impossible to load AFS files in parallel."
        jal(ctx, 0x53BF58u, gen::fn_sub_53AE08_0053ae08);
        v0 = si(-1);
    }
    // 0x0053c164 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(s0, sp, 0x20);
    ld(s1, sp, 0x28);
    ld(s2, sp, 0x30);
    ld(s3, sp, 0x38);
    ld(s4, sp, 0x40);
    ld(s5, sp, 0x48);
    ld(s6, sp, 0x50);
    ld(s7, sp, 0x58);
    ld(fp, sp, 0x60);
    ld(ra, sp, 0x68);
    sp = addiu(sp, 0x70);
}

// 0x0053C2A0 sub_53C2A0 -- 1148 bytes; frame 0x10: ra sp+0x0
// Steps an AFS partition load: checks the header ("AFS", the file count, the 128 MiB limit), then reads the file
// table into the partition record and ends the load.
void sub_53C2A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0053c2a0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x0053c2f0
    charge(ctx, 19);
    v0 = 0x780000;
    sp = addiu(sp, -0x60);
    lw(v1, v0, 21460);  // 0x7853D4
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(s4, sp, 0x30);
    s4 = 0;
    sd(s5, sp, 0x38);
    s5 = 0;
    sd(fp, sp, 0x50);
    fp = 0;
    sd(s1, sp, 0x18);
    sd(s2, sp, 0x20);
    sd(s3, sp, 0x28);
    sd(s6, sp, 0x40);
    sd(s7, sp, 0x48);
    sd(ra, sp, 0x58);
    sw(zero, sp, 0x0);
    if (s0 == v1) {
        // 0x0053c350
        charge(ctx, 4);
        v1 = 0x780000;
        lw(v0, v1, 21456);  // 0x7853D0
        a2 = 0x780000;
        if (v0 == 0) {
            // 0x0053c360
            charge(ctx, 3);
            v0 = si(-1);
            v1 = 0x780000;
            if (s0 == v0) {
                goto L_0053c378;
            }
            // 0x0053c36c
            charge(ctx, 2);
            lw(v0, v1, 21464);
            // 0x0053c6ec (the shared epilogue, written out on this path)
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
            return;
        }
    L_0053c378:
        charge(ctx, 7);
        s6 = 0x780000;
        link(ctx, 0x53C37Cu);  // $ra first: the delay slot below depends on it
        lw(a0, a2, 21456);
        call(ctx, gen::fn_adxf_GetStat_0053dbc8);
        a0 = 3;
        v1 = v0;
        sw(v1, s6, 21464);  // 0x7853D8
        if (v1 == a0) {
            // 0x0053c394
            charge(ctx, 8);
            v0 = sll(s0, 2);
            a0 = 1;
            s0 = 0x780000;
            s0 = addu(s0, v0);
            lw(s0, s0, 20128);
            lb(v1, s0, 15);
            v0 = addiu(s0, 282);
            if (v1 != a0) {
                // 0x0053c3c0
                charge(ctx, 2);
                s5 = addiu(s0, 280);
                sw(v0, sp, 0x0);
            } else {
                // 0x0053c3b4
                charge(ctx, 3);
                s4 = addiu(s0, 280);
                fp = addiu(s0, 0x11C);
            }
            // 0x0053c3c8
            charge(ctx, 3);
            lw(v0, s0, 8);
            s1 = 1;
            if (v0 != 0) {
                // 0x0053c560
                charge(ctx, 1);
                s7 = 0x780000;
            L_0053c564:
                charge(ctx, 6);
                v1 = 0x780000;
                lw(v0, v1, 21476);  // 0x7853E4
                s4 = sll(v0, 9);
                s3 = slt(s1, s4);
                v0 = 0x780000;
                if (s3 != 0) {
                    // 0x0053c57c
                    charge(ctx, 3);
                    s5 = 0x780000;
                    s2 = addiu(s5, 21452);  // &0x7853CC
                    lb(v1, s0, 15);
                    for (;;) {
                        // 0x0053c588
                        charge(ctx, 3);
                        v0 = 1;
                        cc = v1 != v0;  // the condition, before the delay slot changes it
                        lw(v1, s7, 21472);
                        if (!cc) {
                            // 0x0053c594
                            charge(ctx, 21);
                            v0 = sll(s1, 2);
                            v0 = addu(v0, v1);
                            lbu(a2, v0, 1);
                            lbu(a1, v0, 3);
                            lbu(a0, v0, 2);
                            a2 = sll(a2, 8);
                            lbu(v1, v0, 0);
                            a1 = sll(a1, 24);
                            a0 = sll(a0, 16);
                            v1 = v1 | a1;
                            a0 = a0 | a2;
                            a0 = v1 | a0;
                            jal(ctx, 0x53C5C0u, gen::fn_sub_53B5A8_0053b5a8);
                            a1 = s5;
                            lw(a0, s2, 0);
                            v1 = sll(a0, 2);
                            a0 = addiu(a0, 1);
                            v1 = addu(v1, fp);
                            sw(v0, v1, 0);
                            sw(a0, s2, 0);
                            goto L_0053c64c;
                        }
                        // 0x0053c5e8
                        charge(ctx, 18);
                        v0 = sll(s1, 2);
                        v0 = addu(v0, v1);
                        lbu(a2, v0, 1);
                        lbu(a1, v0, 3);
                        lbu(a0, v0, 2);
                        a2 = sll(a2, 8);
                        lbu(v1, v0, 0);
                        a1 = sll(a1, 24);
                        a0 = sll(a0, 16);
                        v1 = v1 | a1;
                        a0 = a0 | a2;
                        a0 = v1 | a0;
                        jal(ctx, 0x53C614u, gen::fn_sub_53B5A8_0053b5a8);
                        a0 = v0;
                        v0 = lui(0xFFFF);
                        v0 = a0 & v0;
                        a1 = s5;
                        if (v0 != 0) {
                            goto L_0053c6b0;
                        }
                        // 0x0053c630
                        charge(ctx, 7);
                        lw(v1, s2, 0);
                        lw(a2, sp, 0x0);
                        v0 = sll(v1, 1);
                        v1 = addiu(v1, 1);
                        v0 = addu(v0, a2);
                        sh(a0, v0, 0);
                        sw(v1, s2, 0);
                    L_0053c64c:
                        charge(ctx, 5);
                        lw(v0, a1, 21452);
                        lw(v1, s0, 8);
                        v0 = slt(v0, v1);
                        if (v0 == 0) {
                            v0 = 3;
                            backedge(ctx);
                            goto L_0053c550;
                        }
                        // 0x0053c660
                        charge(ctx, 4);
                        s1 = addiu(s1, 2);
                        s3 = slt(s1, s4);
                        if (s3 == 0) {
                            break;
                        }
                        lb(v1, s0, 15);
                        backedge(ctx);
                    }
                L_0053c670:
                    charge(ctx, 2);
                    lw(v0, s6, 21464);
                    if (s3 == 0) {
                        // 0x0053c678
                        charge(ctx, 2);
                        v0 = 0x780000;
                        v1 = 0x780000;
                        goto L_0053c680;
                    }
                    // 0x0053c6ec (the shared epilogue, written out on this path)
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
                    return;
                }
            L_0053c680:
                charge(ctx, 7);
                s1 = addiu(v0, 21456);
                lw(a1, v1, 21476);
                lw(a2, s7, 21472);
                link(ctx, 0x53C68Cu);  // $ra first: the delay slot below depends on it
                lw(a0, s1, 0);
                call(ctx, gen::fn_adxf_ReadNw_0053d3d8);
                if (i64(v0) >= 0) {
                    lw(v0, s1, 0);
                    // 0x0053c6e0
                    charge(ctx, 3);
                    lb(v1, v0, 1);
                    sw(v1, s6, 21464);
                    lw(v0, s6, 21464);
                } else {
                    // 0x0053c69c
                    charge(ctx, 5);
                    v0 = 4;
                    link(ctx, 0x53C6A0u);  // $ra first: the delay slot below depends on it
                    sw(v0, s6, 21464);
                    call(ctx, gen::fn_sub_53C198_0053c198);
                    lw(v0, s6, 21464);
                }
            } else {
                // 0x0053c3d4
                charge(ctx, 10);
                s7 = 0x780000;
                a1 = 0x7C0000;
                s1 = addiu(s7, 21472);  // &0x7853E0
                a1 = addiu(a1, 7288);  // "AFS"
                lw(a0, s1, 0);  // 0x7853E0
                a2 = 3;
                s3 = s7;
                jal(ctx, 0x53C3ECu, gen::fn_memcmp_005211b8);
                a0 = 0x7C0000;
                if (v0 != 0) {
                    // 0x0053c3fc
                    charge(ctx, 3);
                    s0 = addiu(s6, 21464);
                    a0 = addiu(a0, 7296);
                L_0053c6bc:
                    charge(ctx, 4);
                    jal(ctx, 0x53C6BCu, gen::fn_sub_53AE08_0053ae08);
                    v0 = 4;
                    sw(v0, s0, 0);
                    goto L_0053c6cc;
                }
                // 0x0053c408
                charge(ctx, 18);
                lw(v0, s1, 0);
                s2 = 4;
                a2 = 0x10000;
                t0 = addiu(v0, 5);
                lbu(a1, v0, 7);
                lbu(v1, v0, 6);
                a3 = addu(v0, s2);
                lbu(a0, t0, 0);
                a1 = sll(a1, 24);
                lbu(v0, a3, 0);
                v1 = sll(v1, 16);
                a0 = sll(a0, 8);
                v0 = v0 | a1;
                v1 = v1 | a0;
                v0 = v0 | v1;
                a2 = slt(a2, v0);
                s1 = 1;
                if (a2 == 0) {
                    // 0x0053c468
                    charge(ctx, 10);
                    lbu(v0, t0, 0);
                    lbu(v1, a3, 0);
                    v0 = sll(v0, 8);
                    lb(a0, s0, 15);
                    v1 = v1 | v0;
                    lbu(a1, s0, 15);
                    v0 = v1;
                    sh(v1, s0, 12);
                    sw(v0, s0, 8);
                    if (a0 != s1) {
                        // 0x0053c4a0
                        charge(ctx, 4);
                        v0 = sll(v0, 1);
                        v0 = addiu(v0, 284);
                        v0 = srl(v0, 2);
                        v0 = sll(v0, 2);
                    } else {
                        // 0x0053c490
                        charge(ctx, 3);
                        v0 = sll(v0, 2);
                        v0 = addiu(v0, 288);
                    }
                    // 0x0053c4b0
                    charge(ctx, 6);
                    sw(v0, s0, 4);
                    v0 = sll(a1, 24);
                    v1 = 1;
                    v0 = sra(v0, 24);
                    cc = v0 != v1;  // the condition, before the delay slot changes it
                    lw(v1, s3, 21472);
                    if (cc) {
                        // 0x0053c508
                        charge(ctx, 15);
                        lbu(a2, v1, 9);
                        lbu(a1, v1, 11);
                        lbu(a0, v1, 10);
                        a2 = sll(a2, 8);
                        lbu(v0, v1, 8);
                        a1 = sll(a1, 24);
                        a0 = sll(a0, 16);
                        v0 = v0 | a1;
                        a0 = a0 | a2;
                        v0 = v0 | a0;
                        a1 = addiu(v0, 2047);
                        v1 = slti(v0, 0);
                        if (v1 != 0) v0 = a1;
                        v0 = sra(v0, 11);
                        sh(v0, s5, 0);
                    } else {
                        // 0x0053c4c8
                        charge(ctx, 16);
                        lbu(a2, v1, 9);
                        lbu(a1, v1, 11);
                        lbu(a0, v1, 10);
                        a2 = sll(a2, 8);
                        lbu(v0, v1, 8);
                        a1 = sll(a1, 24);
                        a0 = sll(a0, 16);
                        v0 = v0 | a1;
                        a0 = a0 | a2;
                        v0 = v0 | a0;
                        a1 = addiu(v0, 2047);
                        v1 = slti(v0, 0);
                        if (v1 != 0) v0 = a1;
                        v0 = sra(v0, 11);
                        sw(v0, s4, 0);
                    }
                    // 0x0053c544
                    charge(ctx, 2);
                    s1 = 3;
                    goto L_0053c564;
                }
                // 0x0053c450
                charge(ctx, 6);
                a0 = 0x7C0000;
                s0 = addiu(s6, 21464);
                a0 = addiu(a0, 7352);  // "E0040702:Illigal number of file.(adxf_GetPtStat)"
                jal(ctx, 0x53C458u, gen::fn_sub_53AE08_0053ae08);
                sw(s2, s0, 0);
            L_0053c6cc:
                charge(ctx, 4);
                jal(ctx, 0x53C6CCu, gen::fn_sub_53C198_0053c198);
                lw(v0, s0, 0);
            }
        }
    } else {
        // 0x0053c33c
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 7232);  // "E0041303:illigal parameter 'ptid'.(adxf_GetPtStat)"
        jal(ctx, 0x53C340u, gen::fn_sub_53AE08_0053ae08);
        v0 = si(-3);
    }
    // 0x0053c6ec (the shared epilogue, written out on this path)
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
    return;
L_0053c550:
    charge(ctx, 4);
    link(ctx, 0x53C550u);  // $ra first: the delay slot below depends on it
    sw(v0, s6, 21464);
    call(ctx, gen::fn_sub_53C198_0053c198);
    goto L_0053c670;
L_0053c6b0:
    charge(ctx, 3);
    a0 = 0x7C0000;
    s0 = addiu(s6, 21464);
    a0 = addiu(a0, 7408);  // "E2122501:AFS file has 128MB or more of inside file.(adxf_GetPtStat)"
    goto L_0053c6bc;
}

// 0x0053C910 ADXF_Open -- 72 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// ADXF_Open: adxf_Open under the ADX environment lock.
void ADXF_Open(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053c910
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x53C924u, gen::fn_sub_53E088_0053e088);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x53C930u, gen::fn_adxf_Open_0053c958);
    s0 = v0;
    jal(ctx, 0x53C938u, gen::fn_sub_53E0A0_0053e0a0);
    ld(s1, sp, 0x8);
    v0 = s0;
    ld(ra, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0053C958 adxf_Open -- 160 bytes; frame 0x20: s1 sp+0x8, s2 sp+0x10, s0 sp+0x0, ra sp+0x18
// adxf_Open: takes a free ADXF handle and opens the file (by name or partition id) on it.
void adxf_Open(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053c958
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    t0 = si(-1);
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    s2 = a0;
    a1 = 0;
    a2 = s2;
    a0 = 1;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x18);
    a3 = s1;
    jal(ctx, 0x53C984u, gen::fn_sub_53B5D0_0053b5d0);
    jal(ctx, 0x53C98Cu, gen::fn_sub_53C7C8_0053c7c8);
    a1 = s2;
    s0 = v0;
    a2 = s1;
    a0 = s0;
    if (s0 != 0) {
        // 0x0053c9a8
        charge(ctx, 4);
        jal(ctx, 0x53C9A8u, gen::fn_adxf_SetFileInfoEx_0053c860);
        a2 = s2;
        if (i64(v0) < 0) {
            // 0x0053c9b8
            charge(ctx, 3);
            a0 = s0;
            s0 = 0;
            jal(ctx, 0x53C9BCu, gen::fn_sub_53CE00_0053ce00);
            goto L_0053c9c4;
        }
        goto L_0053c9c8;
    }
L_0053c9c4:
    charge(ctx, 1);
    a2 = s2;
L_0053c9c8:
    charge(ctx, 12);
    a3 = s1;
    a0 = 1;
    a1 = 1;
    t0 = si(-1);
    jal(ctx, 0x53C9D4u, gen::fn_sub_53B5D0_0053b5d0);
    v0 = s0;
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0053D380 ADXF_ReadNw -- 88 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// ADXF_ReadNw: adxf_ReadNw under the ADX environment lock (the buffer must be 64-byte aligned).
void ADXF_ReadNw(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053d380
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x53D39Cu, gen::fn_sub_53E088_0053e088);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    jal(ctx, 0x53D3ACu, gen::fn_adxf_ReadNw_0053d3d8);
    s0 = v0;
    jal(ctx, 0x53D3B4u, gen::fn_sub_53E0A0_0053e0a0);
    ld(s1, sp, 0x8);
    v0 = s0;
    ld(s2, sp, 0x10);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0053D3D8 adxf_ReadNw -- 60 bytes; frame 0x10: ra sp+0x0
// adxf_ReadNw: starts a read of n sectors into the buffer on the handle; errors through sub_53AE08.
void adxf_ReadNw(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053d3d8
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = a2 & 0x3F;
    sd(ra, sp, 0x0);
    if (v0 == 0) {
        // 0x0053d408
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        gen::fn_adxf_ReadNw32_0053d1f0(ctx);  // tail call
        return;
    }
    // 0x0053d3e8
    charge(ctx, 7);
    a0 = 0x7C0000;
    a0 = addiu(a0, 7960);  // "E0120401:'buf' isn't 64byte alignment.(adxf_ReadNw)"
    jal(ctx, 0x53D3ECu, gen::fn_sub_53AE08_0053ae08);
    v0 = si(-3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0053D708 ADXF_ExecServer -- 36 bytes; frame 0x10: ra sp+0x0
// ADXF_ExecServer: adxf_ExecServer under the ADX environment lock.
void ADXF_ExecServer(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0053d708
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x53D710u, gen::fn_sub_53E088_0053e088);
    jal(ctx, 0x53D718u, gen::fn_adxf_ExecServer_0053d730);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_53E0A0_0053e0a0(ctx);  // tail call
}

// 0x0053D730 adxf_ExecServer -- 96 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// adxf_ExecServer: inside sub_539818 / sub_539830 steps each of the 16 ADXF handles (68 bytes from 0x784A60)
// whose state byte is 1.
void adxf_ExecServer(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053d730
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s1 = 15;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = 1;
    jal(ctx, 0x53D748u, gen::fn_sub_539818_00539818);
    v0 = 0x780000;
    s0 = addiu(v0, 19040);  // &0x784A60
    for (;;) {
        // 0x0053d758
        charge(ctx, 3);
        lb(v0, s0, 0);
        if (v0 != s2) {
            s1 = addiu(s1, -1);
        } else {
            // 0x0053d764
            charge(ctx, 3);
            a0 = s0;
            jal(ctx, 0x53D764u, gen::fn_adxf_ExecOne_0053d640);
            s1 = addiu(s1, -1);
        }
        // 0x0053d770
        charge(ctx, 2);
        s0 = addiu(s0, 68);
        if (i64(s1) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0053d778
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_539830_00539830(ctx);  // tail call
}

// 0x0053D968 ADXF_GetFsizeSct -- 56 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// ADXF_GetFsizeSct: the file size in sectors, under the ADX environment lock.
void ADXF_GetFsizeSct(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053d968
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x53D974u, gen::fn_sub_53E088_0053e088);
    a0 = s0;
    jal(ctx, 0x53D97Cu, gen::fn_adxf_GetFsizeSct_0053d9a0);
    s0 = v0;
    jal(ctx, 0x53D984u, gen::fn_sub_53E0A0_0053e0a0);
    ld(ra, sp, 0x8);
    v0 = s0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0053DB90 ADXF_GetStat -- 56 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// ADXF_GetStat: the handle state (1 idle, 2 reading, 3 complete, 4 error), under the ADX environment lock.
void ADXF_GetStat(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053db90
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x53DB9Cu, gen::fn_sub_53E088_0053e088);
    a0 = s0;
    jal(ctx, 0x53DBA4u, gen::fn_adxf_GetStat_0053dbc8);
    s0 = v0;
    jal(ctx, 0x53DBACu, gen::fn_sub_53E0A0_0053e0a0);
    ld(ra, sp, 0x8);
    v0 = s0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00559AA8 DTX_Init -- 240 bytes; frame 0x30: s3 sp+0x18, s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s4 sp+0x20, ra sp+0x28
// CRI DTX init: on the first call binds the DTX RPC server (retrying with a delay loop; hangs after an error
// message when the bind fails); returns the init count.
void DTX_Init(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00559aa8
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s3, sp, 0x18);
    s3 = 0x7A0000;
    lw(v0, s3, 4444);  // 0x7A115C
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(s4, sp, 0x20);
    sd(ra, sp, 0x28);
    if (v0 != 0) {
        // 0x00559b68
        charge(ctx, 1);
        v1 = addiu(s3, 4444);
    } else {
        // 0x00559ad0
        charge(ctx, 6);
        s0 = 0x7A0000;
        s2 = 0x7A0000;
        s4 = 0x7C0000;
        s1 = addiu(s0, 6624);  // &0x7A19E0
        lw(a1, s2, 4420);  // 0x7A1144
        for (;;) {
            // 0x00559ae8
            charge(ctx, 5);
            a0 = addiu(s0, 6624);
            a2 = 0;
            jal(ctx, 0x559AECu, gen::fn_sceSifBindRpc_00507050);
            if (i64(v0) < 0) {
                goto L_00559afc_3;
            }
            lw(v0, s1, 36);
            // 0x00559b28
            charge(ctx, 2);
            v1 = addiu(s3, 4444);
            if (v0 != 0) {
                break;
            }
            // 0x00559b30
            charge(ctx, 4);
            v1 = si(-1);
            v0 = 0xFFFF;
            v0 = addiu(v0, -4);
            for (;;) {
                // 0x00559b40
                charge(ctx, 7);
                if (v0 == v1) {
                    break;
                }
                v0 = addiu(v0, -4);
                backedge(ctx);
            }
            // 0x00559b5c
            charge(ctx, 2);
            lw(a1, s2, 4420);
            backedge(ctx);
        }
    }
    // 0x00559b6c (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(s3, sp, 0x18);
    lw(v0, v1, 0);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    v0 = addiu(v0, 1);
    ld(s2, sp, 0x10);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sw(v0, v1, 0);
    sp = addiu(sp, 0x30);
    return;
L_00559afc_3:
    charge(ctx, 3);
    a0 = addiu(s4, 19384);
    jal(ctx, 0x559AFCu, gen::fn_sub_541760_00541760);
    for (;;) {
        // 0x00559b08
        charge(ctx, 7);
        backedge(ctx);
    }
}

// 0x00559DD8 dvCiCdSearchFile -- 88 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// CRI dvCi: sceCdLayerSearchFile on the configured layer (0x7A1D7C), bracketed by sub_558988(0x8000) / (0x8001).
void dvCiCdSearchFile(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00559dd8
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    a0 = 0x8000;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x559DF0u, gen::fn_sub_558988_00558988);
    v0 = 0x7A0000;
    lw(a2, v0, 7548);  // 0x7A1D7C
    a1 = s1;
    a0 = s0;
    jal(ctx, 0x559E04u, gen::fn_sceCdLayerSearchFile_0050fc38);
    a0 = 0x8001;
    s0 = v0;
    jal(ctx, 0x559E10u, gen::fn_sub_558988_00558988);
    ld(s1, sp, 0x8);
    v0 = s0;
    ld(ra, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00594038 sub_594038 -- 100 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Starts the fromIPU (ch3) DMA with interrupts off: suspends the DMAC (D_ENABLEW = D_ENABLER | 0x10000), writes
// D3_CHCR (0x1000B000) and resumes it (D_ENABLEW = D_ENABLER & ~0x10000).
void sub_594038(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00594038
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x594044u, gen::fn_DIntr_0050d3a0);
    a1 = 0x10000000;
    a3 = 0x10000;
    a1 = a1 | 0xF520;
    a2 = 0x10000000;
    lw(v0, a1, 0);  // 0x1000F520
    a0 = 0x10000000;
    a2 = a2 | 0xF590;
    a0 = a0 | 0xB000;
    v0 = v0 | a3;
    v1 = lui(0xFFFE);
    sw(v0, a2, 0);  // 0x1000F590
    v1 = v1 | 0xFFFF;
    sw(s0, a0, 0);  // 0x1000B000
    ld(ra, sp, 0x8);
    lw(v0, a1, 0);  // 0x1000F520
    ld(s0, sp, 0x0);
    v0 = v0 & v1;
    sw(v0, a2, 0);  // 0x1000F590
    sp = addiu(sp, 0x10);
    gen::fn_EIntr_0050d3f0(ctx);  // tail call
}

// 0x005940A0 sub_5940A0 -- 100 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Starts the toIPU (ch4) DMA with interrupts off: suspends the DMAC (D_ENABLEW = D_ENABLER | 0x10000), writes
// D4_CHCR (0x1000B400) and resumes it (D_ENABLEW = D_ENABLER & ~0x10000).
void sub_5940A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005940a0
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x5940ACu, gen::fn_DIntr_0050d3a0);
    a1 = 0x10000000;
    a3 = 0x10000;
    a1 = a1 | 0xF520;
    a2 = 0x10000000;
    lw(v0, a1, 0);  // 0x1000F520
    a0 = 0x10000000;
    a2 = a2 | 0xF590;
    a0 = a0 | 0xB400;
    v0 = v0 | a3;
    v1 = lui(0xFFFE);
    sw(v0, a2, 0);  // 0x1000F590
    v1 = v1 | 0xFFFF;
    sw(s0, a0, 0);  // 0x1000B400
    ld(ra, sp, 0x8);
    lw(v0, a1, 0);  // 0x1000F520
    ld(s0, sp, 0x0);
    v0 = v0 & v1;
    sw(v0, a2, 0);  // 0x1000F590
    sp = addiu(sp, 0x10);
    gen::fn_EIntr_0050d3f0(ctx);  // tail call
}

}  // namespace p3fes::game
