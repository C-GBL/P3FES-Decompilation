// Slice libs25 (Phase 5): 150 bodies made by p3fes_handgen from SLUS_216.21 and symbols/, one statement per
// instruction on hg_cpu.h's register view; they keep the recompiled body's registers, frame, spills, $ra links, cycle
// charges and check points (docs/PHASE5_AGENT_BRIEF.md "Using p3fes_handgen"). Each function carries a role comment;
// the hardware-register addresses carry their public PS2 names (DMAC channel registers Dn CHCR / MADR / QWC / TADR /
// SADR, D_CTRL / D_STAT / D_PCR / D_ENABLER / D_ENABLEW, GIF / VIF / IPU status, the GS privileged registers) and the
// scratchpad addresses their SPR offsets. Contents, by address:
//   0x100220-0x1934F0  the ExitThread stub, the DVD-check test screen's draw task
//   0x344EB0-0x4C0E70  node records, the G3 2D stroke / font / fill nodes, the scratchpad DMA kernels (toSPR D9 in,
//                      fromSPR D8 out), the file-system device (sceOpen / sceRead / sceLseek / sceIoctl)
//   0x4C72E0-0x4F0990  the RW Sky DMA ring (handlers, packet open / close / swap, hook / unhook, open / close) and the
//                      Sky driver start (video mode, render state, pipelines)
//   0x4F8EB0-0x5028D8  libgraph (sceGs*), libdma (sceDma*, WaitDma), libmpeg / libipu DMA helpers
//   0x502DB0-0x51C8A0  kernel stubs (syscall wrappers), VSync2, DisableIntc, DelayThread, SIF RPC / loadfile, sceCd /
//                      sceDbc RPC wrappers
//   0x53E0E0-0x56CBB8  CRI: ADXT / ADXM file servers, SRD, DTR / DTX, PS2RNA, ROFS (RFHN / RFMAI / RFDIR) and ROCI
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/libs25.h"

namespace p3fes::recomp_gen {
void fn_ADXF_ExecServer_0053d708(p3fes::EEContext&);
void fn_CVMH_AnalyCvmHdr_0056b240(p3fes::EEContext&);
void fn_CVMH_AnalyZoneHdr_0056b300(p3fes::EEContext&);
void fn_CheckAddress_004fa890(p3fes::EEContext&);
void fn_DIntr_0050d3a0(p3fes::EEContext&);
void fn_DPRINT_0051d588(p3fes::EEContext&);
void fn_DTR_ExecServer_00559140(p3fes::EEContext&);
void fn_DTR_Stop_005593a8(p3fes::EEContext&);
void fn_DTX_CallUrpc_00559c10(p3fes::EEContext&);
void fn_DTX_Init_00559aa8(p3fes::EEContext&);
void fn_DelayThread_005041d8(p3fes::EEContext&);
void fn_DisableIntc_00503c40(p3fes::EEContext&);
void fn_EIntr_0050d3f0(p3fes::EEContext&);
void fn_EnableDmac_00503d78(p3fes::EEContext&);
void fn_EnableIntc_00503ca8(p3fes::EEContext&);
void fn_H_Cursor_UpdateDrawTask_00100230(p3fes::EEContext&);
void fn_H_FileSetup_UpdateTstDvdChkDrawTask_001934f0(p3fes::EEContext&);
void fn_InvalidDCache_00503b98(p3fes::EEContext&);
void fn_PS2RNA_InitIopSnd_00560298(p3fes::EEContext&);
void fn_PS2RNA_Init_0055ff70(p3fes::EEContext&);
void fn_RFDIR_GetDirEnt_0056c0f8(p3fes::EEContext&);
void fn_RFDIR_SearchName_0056c5b0(p3fes::EEContext&);
void fn_RFHN_CreateDirhn_00565ac0(p3fes::EEContext&);
void fn_RFHN_CreateHnG_00565a20(p3fes::EEContext&);
void fn_RFHN_GetStatG_00565fe8(p3fes::EEContext&);
void fn_RFHN_IsUseImgHn_00565b18(p3fes::EEContext&);
void fn_RFHN_ReopenHn_00565a78(p3fes::EEContext&);
void fn_RFHN_WaitCompleteReq_005658b8(p3fes::EEContext&);
void fn_RFMAI_ExecServerG_00568938(p3fes::EEContext&);
void fn_RFMAI_MountG_00567c58(p3fes::EEContext&);
void fn_RFMAI_OpenG_00568388(p3fes::EEContext&);
void fn_RFMAI_ReadWG_00569538(p3fes::EEContext&);
void fn_RFMAI_SetDefVolumeG_00568280(p3fes::EEContext&);
void fn_RFMAI_SetDirG_00569058(p3fes::EEContext&);
void fn_RFMAI_ToUpperStr_00569848(p3fes::EEContext&);
void fn_RFPFS_PfsLock_0056ab90(p3fes::EEContext&);
void fn_RFPFS_PfsWait_0056ab78(p3fes::EEContext&);
void fn_ROCI_ExecServer_0056c8c8(p3fes::EEContext&);
void fn_ROCI_GetStat_0056c9b8(p3fes::EEContext&);
void fn_ROCI_Open_0056c900(p3fes::EEContext&);
void fn_ROCI_OptFn1_0056cbb8(p3fes::EEContext&);
void fn_ROCI_ReqRd_0056c988(p3fes::EEContext&);
void fn_ROFS_AddVolume_005663d8(p3fes::EEContext&);
void fn_ROFS_Close_005666e0(p3fes::EEContext&);
void fn_ROFS_ExecServer_00566778(p3fes::EEContext&);
void fn_ROFS_GetFileSiz_005667d0(p3fes::EEContext&);
void fn_ROFS_GetStat_005667a8(p3fes::EEContext&);
void fn_ROFS_GetVolumeInf_005669d8(p3fes::EEContext&);
void fn_ROFS_Open_005665d0(p3fes::EEContext&);
void fn_ROFS_ReqRd_00566708(p3fes::EEContext&);
void fn_ROFS_Seek_00565c10(p3fes::EEContext&);
void fn_ROFS_Tell_00565d78(p3fes::EEContext&);
void fn_RSU_GenerateFixedKey_0056d780(p3fes::EEContext&);
void fn_SRD_ExecServer_00558500(p3fes::EEContext&);
void fn_SRD_ReqRdDvd_00557b80(p3fes::EEContext&);
void fn_SVM_ExecSvrFs_00565420(p3fes::EEContext&);
void fn_SetTimerAlarm_0050f090(p3fes::EEContext&);
void fn_SkyOpen_004e01b0(p3fes::EEContext&);
void fn_SkyStart_004e1060(p3fes::EEContext&);
void fn_SyncDCache_00503a58(p3fes::EEContext&);
void fn_VSync2_00503680(p3fes::EEContext&);
void fn_VSync_005035f0(p3fes::EEContext&);
void fn_WaitDma_004fa798(p3fes::EEContext&);
void fn_WatchDma_004fa808(p3fes::EEContext&);
void fn_Y_Misc_CreateMCWNDProcTasks_004214e0(p3fes::EEContext&);
void fn___floatdisf_0052eb60(p3fes::EEContext&);
void fn__ch4dma_00502418(p3fes::EEContext&);
void fn__dispRefImageField_0_004c72e0(p3fes::EEContext&);
void fn__isceSifSetDma_00503530(p3fes::EEContext&);
void fn__kDebugException_0050d280(p3fes::EEContext&);
void fn__lf_bind_0050bae8(p3fes::EEContext&);
void fn__lf_version_0050bbe8(p3fes::EEContext&);
void fn__motionVector_004fc6d8(p3fes::EEContext&);
void fn__motionVectors_004fcb00(p3fes::EEContext&);
void fn__pictureTemporalScalableExtension_004ff7b8(p3fes::EEContext&);
void fn__rwDMAAddPURef_004d51c0(p3fes::EEContext&);
void fn__rwDMAAddPkt_004d5000(p3fes::EEContext&);
void fn__rwDMAClosePkt_004d4a60(p3fes::EEContext&);
void fn__rwDMADmaClose_004d6a50(p3fes::EEContext&);
void fn__rwDMADmaOpen_004d67b0(p3fes::EEContext&);
void fn__rwDMAForceBufferSwap_004d4df0(p3fes::EEContext&);
void fn__rwDMAHandler_004d4350(p3fes::EEContext&);
void fn__rwDMAHook_004d6470(p3fes::EEContext&);
void fn__rwDMAOpenGIFPkt_004d54e0(p3fes::EEContext&);
void fn__rwDMAOpenVIFPkt_004d59d0(p3fes::EEContext&);
void fn__rwDMAPreAlloc_004d6ab0(p3fes::EEContext&);
void fn__rwDMAUnhook_004d65a0(p3fes::EEContext&);
void fn__rwDMAVSYNCHandler_004d47f0(p3fes::EEContext&);
void fn__rwSkyInitConfigSystem_004d6b10(p3fes::EEContext&);
void fn__rwSkyOverloadPipelines_004eebc0(p3fes::EEContext&);
void fn__rwSkySetRenderState_004d6b90(p3fes::EEContext&);
void fn__sceAddDmacHandler_00502e70(p3fes::EEContext&);
void fn__sceAddIntcHandler_00502e40(p3fes::EEContext&);
void fn__sceCd_scmd_prechk_00510258(p3fes::EEContext&);
void fn__sceCreateSema_00503160(p3fes::EEContext&);
void fn__sceDeleteSema_00503170(p3fes::EEContext&);
void fn__sceDeleteThread_00502f70(p3fes::EEContext&);
void fn__sceExitDeleteThread_00502fa0(p3fes::EEContext&);
void fn__sceExitThread_00100220(p3fes::EEContext&);
void fn__sceFlushCache_005033e0(p3fes::EEContext&);
void fn__sceGetMemorySize_005035c0(p3fes::EEContext&);
void fn__sceGsGetIMR_00503480(p3fes::EEContext&);
void fn__sceGsPutIMR_005034a0(p3fes::EEContext&);
void fn__sceMpegDispatchMpegCallback_00500d10(p3fes::EEContext&);
void fn__sceMpegErrorBdec_005025a0(p3fes::EEContext&);
void fn__sceMpegError_00502668(p3fes::EEContext&);
void fn__sceMpegFlushBuf_004fd7d0(p3fes::EEContext&);
void fn__sceMpegNextBit_004fd658(p3fes::EEContext&);
void fn__sceMpegStopIpuDma_00502500(p3fes::EEContext&);
void fn__sceRemoveDmacHandler_00502e90(p3fes::EEContext&);
void fn__sceRemoveIntcHandler_00502e60(p3fes::EEContext&);
void fn__sceRotateThreadReadyQueue_00503010(p3fes::EEContext&);
void fn__sceRpcGetFPacket2_00506b68(p3fes::EEContext&);
void fn__sceRpcGetFPacket_00506b38(p3fes::EEContext&);
void fn__sceSetVSyncFlag_005034d0(p3fes::EEContext&);
void fn__sceSifDmaStat_00503500(p3fes::EEContext&);
void fn__sceSifLoadElfPart_0050c528(p3fes::EEContext&);
void fn__sceSifLoadModuleBuffer_0050bcb0(p3fes::EEContext&);
void fn__sceSignalSema_00503180(p3fes::EEContext&);
void fn__sceTerminateThread_00502fb0(p3fes::EEContext&);
void fn__sceWaitSema_005031a0(p3fes::EEContext&);
void fn__sce_DisableIntc_00502eb0(p3fes::EEContext&);
void fn__sce_ExecPS2_00502db0(p3fes::EEContext&);
void fn__sce_InitTLB_005035d0(p3fes::EEContext&);
void fn__sce_iDisableDmac_00502f30(p3fes::EEContext&);
void fn__sce_iDisableIntc_00502f10(p3fes::EEContext&);
void fn__sce_iEnableDmac_00502f20(p3fes::EEContext&);
void fn__sce_iEnableIntc_00502f00(p3fes::EEContext&);
void fn__sce_iSuspendThread_005030e0(p3fes::EEContext&);
void fn__sceiChangeThreadPriority_00503000(p3fes::EEContext&);
void fn_adxm_fs_proc_0053fcf8(p3fes::EEContext&);
void fn_adxt_ExecFsSvr_0053e0e0(p3fes::EEContext&);
void fn_cosf_0052e6d8(p3fes::EEContext&);
void fn_cvFsAddDev_00555b10(p3fes::EEContext&);
void fn_memclr_004fa8b8(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_openVU1SetupPktNew_004ec2b0(p3fes::EEContext&);
void fn_powf_0052ea48(p3fes::EEContext&);
void fn_printf_005225a8(p3fes::EEContext&);
void fn_rfdir_getDirEnt_0056bdc0(p3fes::EEContext&);
void fn_rfmai_addVolList_005672c8(p3fes::EEContext&);
void fn_rfmai_checkMedia_00566f30(p3fes::EEContext&);
void fn_rfmai_copyStructCdVd_0056a0a8(p3fes::EEContext&);
void fn_rfmai_decipherSectors_00569c00(p3fes::EEContext&);
void fn_rfmai_delVolume_00567430(p3fes::EEContext&);
void fn_rfmai_divideFname_00566f78(p3fes::EEContext&);
void fn_rfmai_getCvmfInfo_005674c0(p3fes::EEContext&);
void fn_rfmai_getDirBufAdr_00567188(p3fes::EEContext&);
void fn_rfmai_getEntryFromFname_00568c18(p3fes::EEContext&);
void fn_rfmai_getVolume_005671f0(p3fes::EEContext&);
void fn_rfmai_isDvdRomAccess_00567478(p3fes::EEContext&);
void fn_rfmai_readPvd_005676b0(p3fes::EEContext&);
void fn_rfmai_readRootDirRec_00567750(p3fes::EEContext&);
void fn_rfmai_setCvmfInfo_005675c8(p3fes::EEContext&);
void fn_rfmai_updateHnStat_00568710(p3fes::EEContext&);
void fn_roci_optAddVolume_0056cab0(p3fes::EEContext&);
void fn_sceCdGetDiskType2_00510e30(p3fes::EEContext&);
void fn_sceCdGetError_00510ef0(p3fes::EEContext&);
void fn_sceCdSync_00510148(p3fes::EEContext&);
void fn_sceClose_00508900(p3fes::EEContext&);
void fn_sceDbcDeleteSocket_0051c8a0(p3fes::EEContext&);
void fn_sceDclose_00509f98(p3fes::EEContext&);
void fn_sceDmaGetChan_004fa8f0(p3fes::EEContext&);
void fn_sceDmaPause_004faf30(p3fes::EEContext&);
void fn_sceDmaPutEnv_004fa9f8(p3fes::EEContext&);
void fn_sceDmaRecvN_004fadc0(p3fes::EEContext&);
void fn_sceDmaReset_004fa918(p3fes::EEContext&);
void fn_sceDmaSendN_004fac88(p3fes::EEContext&);
void fn_sceDmaSend_004fac20(p3fes::EEContext&);
void fn_sceDmaSync_004faec0(p3fes::EEContext&);
void fn_sceDopen_00509ed0(p3fes::EEContext&);
void fn_sceDread_0050a100(p3fes::EEContext&);
void fn_sceFsSifCallRpc_00507ad8(p3fes::EEContext&);
void fn_sceGsExecStoreImage_004f9e28(p3fes::EEContext&);
void fn_sceGsGetGParam_004f9040(p3fes::EEContext&);
void fn_sceGsPutDispEnv_004f94e0(p3fes::EEContext&);
void fn_sceGsPutDrawEnv_004f9850(p3fes::EEContext&);
void fn_sceGsResetGraph_004f8eb0(p3fes::EEContext&);
void fn_sceGsResetPath_004f9050(p3fes::EEContext&);
void fn_sceGsSetDefDispEnv_004f9168(p3fes::EEContext&);
void fn_sceGsSetDefDrawEnv2_004fa558(p3fes::EEContext&);
void fn_sceGsSetDefDrawEnv_004f9668(p3fes::EEContext&);
void fn_sceGsSwapDBuffDc_004fa738(p3fes::EEContext&);
void fn_sceGsSyncPath_004f99d0(p3fes::EEContext&);
void fn_sceGsSyncVCallback_004fa4b8(p3fes::EEContext&);
void fn_sceGsSyncV_004f9938(p3fes::EEContext&);
void fn_sceIoctl_005091e8(p3fes::EEContext&);
void fn_sceIpuRestartDMA_005028d8(p3fes::EEContext&);
void fn_sceIpuStopDMA_005027f0(p3fes::EEContext&);
void fn_sceLseek_00508a78(p3fes::EEContext&);
void fn_sceOpen_00508670(p3fes::EEContext&);
void fn_scePrintf_00505e48(p3fes::EEContext&);
void fn_sceRead_00508cb8(p3fes::EEContext&);
void fn_sceSifAllocIopHeap_0050b620(p3fes::EEContext&);
void fn_sceSifCallRpc_00507230(p3fes::EEContext&);
void fn_sceSifFreeIopHeap_0050b788(p3fes::EEContext&);
void fn_sceSifFreeSysMemory_0050b710(p3fes::EEContext&);
void fn_sceSifSetDma_00506088(p3fes::EEContext&);
void fn_sceWrite_00508f28(p3fes::EEContext&);
void fn_setD3_CHCR_00502700(p3fes::EEContext&);
void fn_setD4_CHCR_00502778(p3fes::EEContext&);
void fn_setInitialRenderState_004dfdd0(p3fes::EEContext&);
void fn_sinf_0052e878(p3fes::EEContext&);
void fn_skyCustomModeIsOk_004e0c10(p3fes::EEContext&);
void fn_srd_check_dvd_error_00557fe8(p3fes::EEContext&);
void fn_strcmp_00524128(p3fes::EEContext&);
void fn_strlen_00524388(p3fes::EEContext&);
void fn_strncpy_00524828(p3fes::EEContext&);
void fn_sub_3210A0_003210a0(p3fes::EEContext&);
void fn_sub_323FB0_00323fb0(p3fes::EEContext&);
void fn_sub_324160_00324160(p3fes::EEContext&);
void fn_sub_3243F0_003243f0(p3fes::EEContext&);
void fn_sub_324510_00324510(p3fes::EEContext&);
void fn_sub_344B70_00344b70(p3fes::EEContext&);
void fn_sub_344EB0_00344eb0(p3fes::EEContext&);
void fn_sub_344FC0_00344fc0(p3fes::EEContext&);
void fn_sub_4215B0_004215b0(p3fes::EEContext&);
void fn_sub_421650_00421650(p3fes::EEContext&);
void fn_sub_46F400_0046f400(p3fes::EEContext&);
void fn_sub_470200_00470200(p3fes::EEContext&);
void fn_sub_470E10_00470e10(p3fes::EEContext&);
void fn_sub_473FB0_00473fb0(p3fes::EEContext&);
void fn_sub_4748C0_004748c0(p3fes::EEContext&);
void fn_sub_4749A0_004749a0(p3fes::EEContext&);
void fn_sub_474A80_00474a80(p3fes::EEContext&);
void fn_sub_474D30_00474d30(p3fes::EEContext&);
void fn_sub_476490_00476490(p3fes::EEContext&);
void fn_sub_476980_00476980(p3fes::EEContext&);
void fn_sub_47A510_0047a510(p3fes::EEContext&);
void fn_sub_47A710_0047a710(p3fes::EEContext&);
void fn_sub_47C240_0047c240(p3fes::EEContext&);
void fn_sub_47C8C0_0047c8c0(p3fes::EEContext&);
void fn_sub_47CFD0_0047cfd0(p3fes::EEContext&);
void fn_sub_47DE30_0047de30(p3fes::EEContext&);
void fn_sub_47E9E0_0047e9e0(p3fes::EEContext&);
void fn_sub_47FB10_0047fb10(p3fes::EEContext&);
void fn_sub_480C30_00480c30(p3fes::EEContext&);
void fn_sub_481860_00481860(p3fes::EEContext&);
void fn_sub_482A50_00482a50(p3fes::EEContext&);
void fn_sub_483170_00483170(p3fes::EEContext&);
void fn_sub_4838E0_004838e0(p3fes::EEContext&);
void fn_sub_485750_00485750(p3fes::EEContext&);
void fn_sub_490D40_00490d40(p3fes::EEContext&);
void fn_sub_492060_00492060(p3fes::EEContext&);
void fn_sub_49CAB0_0049cab0(p3fes::EEContext&);
void fn_sub_49CC30_0049cc30(p3fes::EEContext&);
void fn_sub_4BF7E0_004bf7e0(p3fes::EEContext&);
void fn_sub_4BF880_004bf880(p3fes::EEContext&);
void fn_sub_4BFB20_004bfb20(p3fes::EEContext&);
void fn_sub_4C08A0_004c08a0(p3fes::EEContext&);
void fn_sub_4C0A70_004c0a70(p3fes::EEContext&);
void fn_sub_4C0A80_004c0a80(p3fes::EEContext&);
void fn_sub_4C0C50_004c0c50(p3fes::EEContext&);
void fn_sub_4C0CF0_004c0cf0(p3fes::EEContext&);
void fn_sub_4C0E70_004c0e70(p3fes::EEContext&);
void fn_sub_4C2090_004c2090(p3fes::EEContext&);
void fn_sub_4CA030_004ca030(p3fes::EEContext&);
void fn_sub_4D4280_004d4280(p3fes::EEContext&);
void fn_sub_4D5E90_004d5e90(p3fes::EEContext&);
void fn_sub_4D5FE0_004d5fe0(p3fes::EEContext&);
void fn_sub_4D6250_004d6250(p3fes::EEContext&);
void fn_sub_4D6700_004d6700(p3fes::EEContext&);
void fn_sub_4E0540_004e0540(p3fes::EEContext&);
void fn_sub_4E3630_004e3630(p3fes::EEContext&);
void fn_sub_4EC510_004ec510(p3fes::EEContext&);
void fn_sub_4F0990_004f0990(p3fes::EEContext&);
void fn_sub_4F0AD0_004f0ad0(p3fes::EEContext&);
void fn_sub_4FD8A0_004fd8a0(p3fes::EEContext&);
void fn_sub_50EEE0_0050eee0(p3fes::EEContext&);
void fn_sub_539818_00539818(p3fes::EEContext&);
void fn_sub_539830_00539830(p3fes::EEContext&);
void fn_sub_540098_00540098(p3fes::EEContext&);
void fn_sub_541760_00541760(p3fes::EEContext&);
void fn_sub_546D90_00546d90(p3fes::EEContext&);
void fn_sub_546E38_00546e38(p3fes::EEContext&);
void fn_sub_555D70_00555d70(p3fes::EEContext&);
void fn_sub_558988_00558988(p3fes::EEContext&);
void fn_sub_558DD0_00558dd0(p3fes::EEContext&);
void fn_sub_559718_00559718(p3fes::EEContext&);
void fn_sub_559918_00559918(p3fes::EEContext&);
void fn_sub_559928_00559928(p3fes::EEContext&);
void fn_sub_559938_00559938(p3fes::EEContext&);
void fn_sub_559D18_00559d18(p3fes::EEContext&);
void fn_sub_55F748_0055f748(p3fes::EEContext&);
void fn_sub_562F90_00562f90(p3fes::EEContext&);
void fn_sub_563C28_00563c28(p3fes::EEContext&);
void fn_sub_563FE0_00563fe0(p3fes::EEContext&);
void fn_sub_5642D0_005642d0(p3fes::EEContext&);
void fn_sub_564528_00564528(p3fes::EEContext&);
void fn_sub_564738_00564738(p3fes::EEContext&);
void fn_sub_5649A8_005649a8(p3fes::EEContext&);
void fn_sub_5649D8_005649d8(p3fes::EEContext&);
void fn_sub_564A20_00564a20(p3fes::EEContext&);
void fn_sub_564A50_00564a50(p3fes::EEContext&);
void fn_sub_565BC0_00565bc0(p3fes::EEContext&);
void fn_sub_5660F0_005660f0(p3fes::EEContext&);
void fn_sub_5664F8_005664f8(p3fes::EEContext&);
void fn_sub_566848_00566848(p3fes::EEContext&);
void fn_sub_566938_00566938(p3fes::EEContext&);
void fn_sub_566D28_00566d28(p3fes::EEContext&);
void fn_sub_567AF0_00567af0(p3fes::EEContext&);
void fn_sub_568098_00568098(p3fes::EEContext&);
void fn_sub_568A78_00568a78(p3fes::EEContext&);
void fn_sub_568AC0_00568ac0(p3fes::EEContext&);
void fn_sub_568BC8_00568bc8(p3fes::EEContext&);
void fn_sub_568DB0_00568db0(p3fes::EEContext&);
void fn_sub_569730_00569730(p3fes::EEContext&);
void fn_sub_569BD0_00569bd0(p3fes::EEContext&);
void fn_sub_56A040_0056a040(p3fes::EEContext&);
void fn_sub_56ABE0_0056abe0(p3fes::EEContext&);
void fn_sub_56ABF8_0056abf8(p3fes::EEContext&);
void fn_sub_56AC10_0056ac10(p3fes::EEContext&);
void fn_sub_56C8E8_0056c8e8(p3fes::EEContext&);
void fn_sub_56C918_0056c918(p3fes::EEContext&);
void fn_sub_56C930_0056c930(p3fes::EEContext&);
void fn_sub_56C970_0056c970(p3fes::EEContext&);
void fn_sub_56CB58_0056cb58(p3fes::EEContext&);
void fn_sub_56D740_0056d740(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// 0x00100220 _sceExitThread -- 16 bytes; leaf frame (no stack)
// Kernel stub: ExitThread (syscall 35). The syscall does not return, so the body falls through into the next symbol
// (a tail call in the recompiled body).
void _sceExitThread(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00100220
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 35;
    syscall(ctx, 0x100224u);
    gen::fn_H_Cursor_UpdateDrawTask_00100230(ctx);  // tail call
}

// 0x001934F0 H_FileSetup_UpdateTstDvdChkDrawTask -- 956 bytes; frame 0x2E0: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Draw task of the DVD-check test screen: a 6-state machine (table 0x7B6A10) that opens a message window, polls
// sceCdGetDiskType2 for a DVD (type 20 / 5), lists the disc root (sceDopen / sceDread) and closes.
void H_FileSetup_UpdateTstDvdChkDrawTask(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001934f0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x2E0);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, 60);
    lw(v0, s0, 0);
    at = sltiu(v0, 6);
    if (at != 0) {
        // 0x00193518
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, 27152);  // &0x7B6A10
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x193534u:  // table[0]
            // 0x00193534
            charge(ctx, 10);
            a1 = 1;
            jal(ctx, 0x193538u, gen::fn_Y_Misc_CreateMCWNDProcTasks_004214e0);
            sw(v0, s0, 5148);
            v0 = 1;
            sw(v0, s0, 0);
            sw(zero, s0, 16);
            sw(zero, s0, 20);
        L_0019388c:
            charge(ctx, 1);
            v0 = 0;
            break;
        case 0x19355Cu:  // table[1]
            // 0x0019355c
            charge(ctx, 10);
            lw(a0, s0, 5148);
            a1 = 22;
            jal(ctx, 0x193564u, gen::fn_sub_4215B0_004215b0);
            v0 = 3;
            sw(v0, s0, 0);
            sw(zero, s0, 16);
            sw(zero, s0, 24);
            goto L_0019388c;
        case 0x193584u:  // table[3]
            // 0x00193584
            charge(ctx, 3);
            lw(v0, s0, 16);
            if (v0 == 0) {
                // 0x00193590
                charge(ctx, 4);
                jal(ctx, 0x193590u, gen::fn_sceCdGetDiskType2_00510e30);
                if (v0 != 0) {
                    // 0x001935b0
                    charge(ctx, 3);
                    lw(v1, s0, 24);
                    if (v1 != 0) {
                        // 0x001935bc
                        charge(ctx, 3);
                        v1 = 20;
                        if (v0 != v1) {
                            // 0x001936a0
                            charge(ctx, 3);
                            v1 = 5;
                            if (v0 != v1) {
                                // 0x001936ac
                                charge(ctx, 3);
                                v1 = 16;
                                if (v0 == v1) {
                                    goto L_001936ec;
                                }
                                // 0x001936b8
                                charge(ctx, 3);
                                v1 = 17;
                                if (v0 == v1) {
                                    goto L_001936ec;
                                }
                                // 0x001936c4
                                charge(ctx, 3);
                                v1 = 18;
                                if (v0 == v1) {
                                    goto L_001936ec;
                                }
                                // 0x001936d0
                                charge(ctx, 3);
                                v1 = 19;
                                if (v0 == v1) {
                                    goto L_001936ec;
                                }
                                // 0x001936dc
                                charge(ctx, 4);
                                v0 = addiu(v0, -253);
                                at = sltiu(v0, 3);
                                if (at != 0) {
                                    goto L_001936ec;
                                }
                                goto L_0019388c;
                            }
                        L_001936ec:
                            charge(ctx, 7);
                            lw(a0, s0, 5148);
                            a1 = 26;
                            jal(ctx, 0x1936F4u, gen::fn_sub_4215B0_004215b0);
                            sw(zero, s0, 24);
                        } else {
                            // 0x001935c8
                            charge(ctx, 8);
                            sw(zero, s0, 24);
                            a0 = 0x5E0000;
                            a0 = addiu(a0, 20024);  // "cdrom0:\\"
                            jal(ctx, 0x1935D4u, gen::fn_sceDopen_00509ed0);
                            s2 = v0;
                            if (i64(s2) >= 0) {
                                // 0x001935e8
                                charge(ctx, 4);
                                sw(zero, s0, 4);
                                s1 = 0;
                                for (;;) {
                                    // 0x00193644
                                    charge(ctx, 3);
                                    v0 = slti(s1, 20);
                                    if (v0 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                    // 0x001935f8
                                    charge(ctx, 6);
                                    a0 = s2;
                                    a1 = addiu(sp, 0x190);
                                    jal(ctx, 0x193600u, gen::fn_sceDread_0050a100);
                                    if (i64(v0) > 0) {
                                        // 0x00193610
                                        charge(ctx, 10);
                                        lw(v0, s0, 4);
                                        v0 = addiu(v0, 1);
                                        sw(v0, s0, 4);
                                        a0 = 0x5E0000;
                                        a0 = addiu(a0, 20040);  // "SLPM_664.45;1"
                                        a1 = addiu(sp, 0x1D0);
                                        jal(ctx, 0x193628u, gen::fn_strcmp_00524128);
                                        if (v0 == 0) {
                                            // 0x00193638
                                            charge(ctx, 2);
                                            v0 = 1;
                                            sw(v0, s0, 20);
                                        }
                                    }
                                    // 0x00193640
                                    charge(ctx, 1);
                                    s1 = addiu(s1, 1);
                                }
                                // 0x00193650
                                charge(ctx, 3);
                                a0 = s2;
                                jal(ctx, 0x193654u, gen::fn_sceDclose_00509f98);
                            }
                            // 0x0019365c
                            charge(ctx, 3);
                            lw(v0, s0, 20);
                            if (v0 == 0) {
                                // 0x00193688
                                charge(ctx, 6);
                                lw(a0, s0, 5148);
                                a1 = 26;
                                jal(ctx, 0x193690u, gen::fn_sub_4215B0_004215b0);
                            } else {
                                // 0x00193668
                                charge(ctx, 8);
                                lw(a0, s0, 5148);
                                a1 = 24;
                                jal(ctx, 0x193670u, gen::fn_sub_4215B0_004215b0);
                                v0 = 4;
                                sw(v0, s0, 0);
                            }
                        }
                    }
                } else {
                    // 0x001935a0
                    charge(ctx, 4);
                    v0 = 1;
                    sw(v0, s0, 24);
                }
            }
            goto L_0019388c;
        case 0x193708u:  // table[4]
            // 0x00193708
            charge(ctx, 6);
            v0 = 5;
            sw(v0, s0, 0);
            sw(zero, s0, 20);
            sw(zero, s0, 16);
            goto L_0019388c;
        case 0x193720u:  // table[5]
            // 0x00193720
            charge(ctx, 4);
            jal(ctx, 0x193720u, gen::fn_sceCdGetDiskType2_00510e30);
            if (v0 == 0) {
                // 0x00193730
                charge(ctx, 4);
                v0 = 1;
                sw(v0, s0, 24);
                goto L_0019388c;
            }
            // 0x00193740
            charge(ctx, 3);
            lw(v1, s0, 24);
            if (v1 == 0) {
                goto L_0019388c;
            }
            // 0x0019374c
            charge(ctx, 3);
            v1 = 20;
            if (v0 != v1) {
                // 0x0019382c
                charge(ctx, 3);
                v1 = 5;
                if (v0 != v1) {
                    // 0x00193838
                    charge(ctx, 3);
                    v1 = 16;
                    if (v0 == v1) {
                        goto L_00193878;
                    }
                    // 0x00193844
                    charge(ctx, 3);
                    v1 = 17;
                    if (v0 == v1) {
                        goto L_00193878;
                    }
                    // 0x00193850
                    charge(ctx, 3);
                    v1 = 18;
                    if (v0 == v1) {
                        goto L_00193878;
                    }
                    // 0x0019385c
                    charge(ctx, 3);
                    v1 = 19;
                    if (v0 == v1) {
                        goto L_00193878;
                    }
                    // 0x00193868
                    charge(ctx, 4);
                    v0 = addiu(v0, -253);
                    at = sltiu(v0, 3);
                    if (at != 0) {
                        goto L_00193878;
                    }
                    goto L_0019388c;
                }
            L_00193878:
                charge(ctx, 5);
                lw(a0, s0, 5148);
                a1 = 27;
                jal(ctx, 0x193880u, gen::fn_sub_4215B0_004215b0);
                sw(zero, s0, 24);
                goto L_0019388c;
            }
            // 0x00193758
            charge(ctx, 8);
            sw(zero, s0, 24);
            a0 = 0x5E0000;
            a0 = addiu(a0, 20024);  // "cdrom0:\\"
            jal(ctx, 0x193764u, gen::fn_sceDopen_00509ed0);
            s2 = v0;
            if (i64(s2) >= 0) {
                // 0x00193778
                charge(ctx, 4);
                sw(zero, s0, 4);
                s1 = 0;
                for (;;) {
                    // 0x001937d4
                    charge(ctx, 3);
                    v0 = slti(s1, 20);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00193788
                    charge(ctx, 6);
                    a0 = s2;
                    a1 = addiu(sp, 0x40);
                    jal(ctx, 0x193790u, gen::fn_sceDread_0050a100);
                    if (i64(v0) > 0) {
                        // 0x001937a0
                        charge(ctx, 10);
                        lw(v0, s0, 4);
                        v0 = addiu(v0, 1);
                        sw(v0, s0, 4);
                        a0 = 0x5E0000;
                        a0 = addiu(a0, 20056);  // "SLPM_666.89;1"
                        a1 = addiu(sp, 0x80);
                        jal(ctx, 0x1937B8u, gen::fn_strcmp_00524128);
                        if (v0 == 0) {
                            // 0x001937c8
                            charge(ctx, 2);
                            v0 = 1;
                            sw(v0, s0, 20);
                        }
                    }
                    // 0x001937d0
                    charge(ctx, 1);
                    s1 = addiu(s1, 1);
                }
                // 0x001937e0
                charge(ctx, 3);
                a0 = s2;
                jal(ctx, 0x1937E4u, gen::fn_sceDclose_00509f98);
            }
            // 0x001937ec
            charge(ctx, 3);
            lw(v0, s0, 20);
            if (v0 == 0) {
                // 0x00193810
                charge(ctx, 7);
                lw(a0, s0, 5148);
                a1 = 27;
                jal(ctx, 0x193818u, gen::fn_sub_4215B0_004215b0);
                sw(zero, s0, 24);
                goto L_0019388c;
            }
            // 0x001937f8
            charge(ctx, 6);
            lw(a0, s0, 5148);
            jal(ctx, 0x1937FCu, gen::fn_sub_421650_00421650);
            v0 = si(-1);
            break;
        case 0x19388Cu:  // table[2]
            goto L_0019388c;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x00193890 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(ra, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x2E0);
        return;
    }
    goto L_0019388c;
}

// 0x00344EB0 sub_344EB0 -- 260 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Creates a node record (44 bytes per child + 12) through the allocator hook 0x960178, builds its list (sub_323FB0,
// minimum 3 entries) and links it to the parent (sub_344B70).
void sub_344EB0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00344eb0
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lw(v1, a0, 56);
    v0 = sll(v1, 2);
    v0 = addu(v0, v1);
    v0 = sll(v0, 1);
    v0 = addu(v0, v1);
    v0 = sll(v0, 2);
    a0 = addiu(v0, 12);
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x344EF4u, v0.u());
    s2 = v0;
    v1 = addiu(s2, 12);
    sw(v1, v0, 0);
    sw(s2, v0, 8);
    lw(v0, s1, 140);
    at = sltiu(v0, 3);
    if (at != 0) {
        // 0x00344f1c
        charge(ctx, 2);
        v0 = 3;
        sw(v0, s1, 140);
    }
    // 0x00344f24
    charge(ctx, 11);
    lhu(a0, s1, 56);
    lhu(a1, s1, 140);
    a2 = 0x6A0000;
    a2 = addiu(a2, -17168);  // &0x69BCF0
    a3 = 4;
    t0 = 76;
    jal(ctx, 0x344F3Cu, gen::fn_sub_323FB0_00323fb0);
    sw(v0, s2, 4);
    if (s0 != 0) {
        // 0x00344f74
        charge(ctx, 4);
        lw(a0, s2, 4);
        a1 = s0;
        jal(ctx, 0x344F7Cu, gen::fn_sub_324510_00324510);
    } else {
        // 0x00344f50
        charge(ctx, 9);
        a0 = 20;
        jal(ctx, 0x344F54u, gen::fn_sub_3210A0_003210a0);
        lw(a0, s2, 4);
        a1 = v0;
        jal(ctx, 0x344F64u, gen::fn_sub_3243F0_003243f0);
    }
    // 0x00344f84
    charge(ctx, 12);
    a0 = s2;
    a1 = s1;
    jal(ctx, 0x344F8Cu, gen::fn_sub_344B70_00344b70);
    v0 = s2;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00344FC0 sub_344FC0 -- 180 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Companion of sub_344EB0: frees the node's list (sub_324160) through the allocator hook 0x960178 and unlinks it
// (sub_344B70).
void sub_344FC0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00344fc0
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, 60);
    lw(s1, a0, 64);
    lw(v1, s1, 56);
    v0 = sll(v1, 2);
    v0 = addu(v0, v1);
    v0 = sll(v0, 1);
    v0 = addu(v0, v1);
    v0 = sll(v0, 2);
    a0 = addiu(v0, 12);
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x345004u, v0.u());
    s2 = v0;
    v1 = addiu(s2, 12);
    sw(v1, v0, 0);
    sw(s2, v0, 8);
    lw(v0, s1, 140);
    at = sltiu(v0, 3);
    if (at != 0) {
        // 0x0034502c
        charge(ctx, 2);
        v0 = 3;
        sw(v0, s1, 140);
    }
    // 0x00345034
    charge(ctx, 16);
    lw(a0, s0, 4);
    jal(ctx, 0x345038u, gen::fn_sub_324160_00324160);
    sw(v0, s2, 4);
    a0 = s2;
    a1 = s1;
    jal(ctx, 0x34504Cu, gen::fn_sub_344B70_00344b70);
    v0 = s2;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0046F400 sub_46F400 -- 1904 bytes; frame 0xA0: ra sp+0x0
// G3_2DStroke_Node: builds the VIF/GIF packet of a 2D stroke (line strip) node through _rwDMAOpenVIFPkt; prints "DMA
// memory failure" when the packet cannot be opened.
void sub_46F400(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5};
    // 0x0046f400
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    v0 = 0x960000;
    sd(ra, sp, 0x0);
    lw(a3, v0, -4200);  // 0x95EF98
    v0 = 0x960000;
    lw(t0, v0, -4156);  // 0x95EFC4
    v0 = 0x960000;
    lw(v0, v0, -4152);  // 0x95EFC8
    at = slt(0, v0);
    t1 = 0;
    if (at != 0) {
        // 0x0046f42c
        charge(ctx, 1);
        v0 = 0x960000;
        for (;;) {
            // 0x0046f430
            charge(ctx, 2);
            t2 = 0;
            for (;;) {
                // 0x0046f438
                charge(ctx, 77);
                t2 = addiu(t2, 7);
                lwc1(f0, a3, 4);
                a2 = addiu(a3, 168);
                v1 = slti(t2, 32);
                swc1(f0, a0, 0);
                lwc1(f0, a3, 8);
                swc1(f0, a0, 4);
                lwc1(f0, a3, 12);
                swc1(f0, a1, 0);
                lwc1(f0, a3, 16);
                swc1(f0, a1, 4);
                lwc1(f0, a3, 20);
                swc1(f0, a1, 8);
                lwc1(f0, a3, 28);
                swc1(f0, a0, 8);
                lwc1(f0, a3, 32);
                swc1(f0, a0, 12);
                lwc1(f0, a3, 36);
                swc1(f0, a1, 12);
                lwc1(f0, a3, 40);
                swc1(f0, a1, 16);
                lwc1(f0, a3, 44);
                swc1(f0, a1, 20);
                lwc1(f0, a3, 52);
                swc1(f0, a0, 16);
                lwc1(f0, a3, 56);
                swc1(f0, a0, 20);
                lwc1(f0, a3, 60);
                swc1(f0, a1, 24);
                lwc1(f0, a3, 64);
                swc1(f0, a1, 28);
                lwc1(f0, a3, 68);
                swc1(f0, a1, 32);
                lwc1(f0, a3, 76);
                swc1(f0, a0, 24);
                lwc1(f0, a3, 80);
                swc1(f0, a0, 28);
                lwc1(f0, a3, 84);
                swc1(f0, a1, 36);
                lwc1(f0, a3, 88);
                swc1(f0, a1, 40);
                lwc1(f0, a3, 92);
                swc1(f0, a1, 44);
                lwc1(f0, a3, 100);
                swc1(f0, a0, 32);
                lwc1(f0, a3, 104);
                swc1(f0, a0, 36);
                lwc1(f0, a3, 108);
                swc1(f0, a1, 48);
                lwc1(f0, a3, 112);
                swc1(f0, a1, 52);
                lwc1(f0, a3, 116);
                swc1(f0, a1, 56);
                lwc1(f0, a3, 124);
                swc1(f0, a0, 40);
                lwc1(f0, a3, 128);
                swc1(f0, a0, 44);
                lwc1(f0, a3, 132);
                swc1(f0, a1, 60);
                lwc1(f0, a3, 136);
                swc1(f0, a1, 64);
                lwc1(f0, a3, 140);
                swc1(f0, a1, 68);
                lwc1(f0, a3, 148);
                swc1(f0, a0, 48);
                lwc1(f0, a3, 152);
                swc1(f0, a0, 52);
                lwc1(f0, a3, 156);
                a0 = addiu(a0, 56);
                swc1(f0, a1, 72);
                lwc1(f0, a3, 160);
                swc1(f0, a1, 76);
                lwc1(f0, a3, 164);
                swc1(f0, a1, 80);
                a3 = a2;
                a1 = addiu(a1, 84);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0046f56c
            charge(ctx, 58);
            lwc1(f0, a2, 4);
            t1 = addiu(t1, 1);
            a3 = addiu(a2, 96);
            t0 = addiu(t0, -40);
            swc1(f0, a0, 0);
            lwc1(f0, a2, 8);
            swc1(f0, a0, 4);
            lwc1(f0, a2, 12);
            swc1(f0, a1, 0);
            lwc1(f0, a2, 16);
            swc1(f0, a1, 4);
            lwc1(f0, a2, 20);
            swc1(f0, a1, 8);
            lwc1(f0, a2, 28);
            swc1(f0, a0, 8);
            lwc1(f0, a2, 32);
            swc1(f0, a0, 12);
            lwc1(f0, a2, 36);
            swc1(f0, a1, 12);
            lwc1(f0, a2, 40);
            swc1(f0, a1, 16);
            lwc1(f0, a2, 44);
            swc1(f0, a1, 20);
            lwc1(f0, a2, 52);
            swc1(f0, a0, 16);
            lwc1(f0, a2, 56);
            swc1(f0, a0, 20);
            lwc1(f0, a2, 60);
            swc1(f0, a1, 24);
            lwc1(f0, a2, 64);
            swc1(f0, a1, 28);
            lwc1(f0, a2, 68);
            swc1(f0, a1, 32);
            lwc1(f0, a2, 76);
            swc1(f0, a0, 24);
            lwc1(f0, a2, 80);
            swc1(f0, a0, 28);
            lwc1(f0, a2, 84);
            swc1(f0, a1, 36);
            lwc1(f0, a2, 88);
            swc1(f0, a1, 40);
            lwc1(f0, a2, 92);
            swc1(f0, a1, 44);
            lwc1(f0, a2, 100);
            swc1(f0, a0, 32);
            lwc1(f0, a2, 104);
            swc1(f0, a0, 36);
            lwc1(f0, a2, 108);
            a0 = addiu(a0, 40);
            swc1(f0, a1, 48);
            lwc1(f0, a2, 112);
            swc1(f0, a1, 52);
            lwc1(f0, a2, 116);
            swc1(f0, a1, 56);
            lw(v1, v0, -4152);
            v1 = slt(t1, v1);
            a1 = addiu(a1, 60);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0046f654
        charge(ctx, 1);
    }
    // 0x0046f658
    charge(ctx, 3);
    at = slt(0, t0);
    a2 = 0;
    if (at != 0) {
        // 0x0046f664
        charge(ctx, 3);
        at = slti(t0, 9);
        v1 = addiu(t0, -8);
        if (at == 0) {
            // 0x0046f670
            charge(ctx, 3);
            at = slt(t0, 0);
            v0 = 0;
            if (at == 0) {
                // 0x0046f67c
                charge(ctx, 5);
                at = 0x7FFF0000;
                at = at | 0xFFFF;
                at = slt(t0, at);
                if (at != 0) {
                    // 0x0046f690
                    charge(ctx, 1);
                    v0 = 1;
                }
            }
            // 0x0046f694
            charge(ctx, 2);
            if (v0 != 0) {
                for (;;) {
                    // 0x0046f69c
                    charge(ctx, 86);
                    lwc1(f0, a3, 4);
                    a2 = addiu(a2, 8);
                    v0 = slt(a2, v1);
                    swc1(f0, a0, 0);
                    lwc1(f0, a3, 8);
                    swc1(f0, a0, 4);
                    lwc1(f0, a3, 12);
                    swc1(f0, a1, 0);
                    lwc1(f0, a3, 16);
                    swc1(f0, a1, 4);
                    lwc1(f0, a3, 20);
                    swc1(f0, a1, 8);
                    lwc1(f0, a3, 28);
                    swc1(f0, a0, 8);
                    lwc1(f0, a3, 32);
                    swc1(f0, a0, 12);
                    lwc1(f0, a3, 36);
                    swc1(f0, a1, 12);
                    lwc1(f0, a3, 40);
                    swc1(f0, a1, 16);
                    lwc1(f0, a3, 44);
                    swc1(f0, a1, 20);
                    lwc1(f0, a3, 52);
                    swc1(f0, a0, 16);
                    lwc1(f0, a3, 56);
                    swc1(f0, a0, 20);
                    lwc1(f0, a3, 60);
                    swc1(f0, a1, 24);
                    lwc1(f0, a3, 64);
                    swc1(f0, a1, 28);
                    lwc1(f0, a3, 68);
                    swc1(f0, a1, 32);
                    lwc1(f0, a3, 76);
                    swc1(f0, a0, 24);
                    lwc1(f0, a3, 80);
                    swc1(f0, a0, 28);
                    lwc1(f0, a3, 84);
                    swc1(f0, a1, 36);
                    lwc1(f0, a3, 88);
                    swc1(f0, a1, 40);
                    lwc1(f0, a3, 92);
                    swc1(f0, a1, 44);
                    lwc1(f0, a3, 100);
                    swc1(f0, a0, 32);
                    lwc1(f0, a3, 104);
                    swc1(f0, a0, 36);
                    lwc1(f0, a3, 108);
                    swc1(f0, a1, 48);
                    lwc1(f0, a3, 112);
                    swc1(f0, a1, 52);
                    lwc1(f0, a3, 116);
                    swc1(f0, a1, 56);
                    lwc1(f0, a3, 124);
                    swc1(f0, a0, 40);
                    lwc1(f0, a3, 128);
                    swc1(f0, a0, 44);
                    lwc1(f0, a3, 132);
                    swc1(f0, a1, 60);
                    lwc1(f0, a3, 136);
                    swc1(f0, a1, 64);
                    lwc1(f0, a3, 140);
                    swc1(f0, a1, 68);
                    lwc1(f0, a3, 148);
                    swc1(f0, a0, 48);
                    lwc1(f0, a3, 152);
                    swc1(f0, a0, 52);
                    lwc1(f0, a3, 156);
                    swc1(f0, a1, 72);
                    lwc1(f0, a3, 160);
                    swc1(f0, a1, 76);
                    lwc1(f0, a3, 164);
                    swc1(f0, a1, 80);
                    lwc1(f0, a3, 172);
                    swc1(f0, a0, 56);
                    lwc1(f0, a3, 176);
                    swc1(f0, a0, 60);
                    lwc1(f0, a3, 180);
                    a0 = addiu(a0, 64);
                    swc1(f0, a1, 84);
                    lwc1(f0, a3, 184);
                    swc1(f0, a1, 88);
                    lwc1(f0, a3, 188);
                    swc1(f0, a1, 92);
                    a3 = addiu(a3, 192);
                    a1 = addiu(a1, 96);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0046f7f4
                charge(ctx, 1);
            }
        }
        // 0x0046f7f8
        charge(ctx, 3);
        at = slt(a2, t0);
        if (at != 0) {
            for (;;) {
                // 0x0046f804
                charge(ctx, 16);
                lwc1(f0, a3, 4);
                a2 = addiu(a2, 1);
                v0 = slt(a2, t0);
                swc1(f0, a0, 0);
                lwc1(f0, a3, 8);
                swc1(f0, a0, 4);
                lwc1(f0, a3, 12);
                a0 = addiu(a0, 8);
                swc1(f0, a1, 0);
                lwc1(f0, a3, 16);
                swc1(f0, a1, 4);
                lwc1(f0, a3, 20);
                swc1(f0, a1, 8);
                a3 = addiu(a3, 24);
                a1 = addiu(a1, 12);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0046f844
            charge(ctx, 1);
        }
    }
    // 0x0046f848
    charge(ctx, 5);
    a0 = 0;
    a1 = 11;
    jal(ctx, 0x46F84Cu, gen::fn__rwDMAOpenVIFPkt_004d59d0);
    if (v0 == 0) {
        // 0x0046fb44
        charge(ctx, 8);
        a0 = 0x6B0000;
        a1 = 0x6B0000;
        a0 = addiu(a0, 22352);  // "%s(%d): DMA memory failure\n"
        a1 = addiu(a1, 22384);  // "G3_2DStroke_Node.c"
        a2 = 266;
        jal(ctx, 0x46FB54u, gen::fn_printf_005225a8);
        backedge(ctx);
    } else {
        // 0x0046f85c
        charge(ctx, 39);
        v1 = 0x6C090000;
        v0 = 0x1000000;
        v1 = v1 | 0x3CF;
        v0 = v0 | 0x101;  // &0x1000101
        ppacw(a2, v1, v0);
        v1 = 0x10000000;
        a1 = 0;
        a0 = v1 | 0x9;
        lw(v0, gp, -17148);  // 0x7CE9F4
        ppacw(a0, a1, a0);
        ppacw(a0, a2, a0);
        sq(a0, v0, 0);
        v1 = 0x960000;
        v0 = 0x960000;
        lw(a0, gp, -17148);  // 0x7CE9F4
        lwc1(f2, v0, -4192);  // 0x95EFA0
        lw(v1, v1, -4216);  // 0x95EF88
        t0 = addiu(a0, 16);
        v0 = 0x960000;
        sw(t0, gp, -17148);  // 0x7CE9F4
        lwc1(f1, v0, -4264);  // 0x95EF58
        swc1(f2, sp, 0x94);
        v0 = 0x960000;
        lwc1(f0, v0, -4188);  // 0x95EFA4
        swc1(f1, sp, 0x98);
        swc1(f0, sp, 0x9C);
        v0 = 0x960000;
        lwc1(f0, v1, 112);
        swc1(f0, sp, 0x90);
        lw(v1, gp, -17148);  // 0x7CE9F4
        lq(a0, sp, 0x90);
        sq(a0, v1, 0);
        lw(v1, v0, -4216);  // 0x95EF88
        lw(v0, gp, -17148);  // 0x7CE9F4
        t0 = addiu(v0, 16);
        sw(t0, gp, -17148);  // 0x7CE9F4
        lw(v0, v1, 104);
        if (v0 == 0) {
            // 0x0046f90c
            charge(ctx, 3);
            v0 = 0x3F800000;
            mtc1(v0, f0);
            lwc1(f4, v1, 0);
        } else {
            // 0x0046f8f8
            charge(ctx, 5);
            v0 = 0x3F000000;
            v0 = v0 | 0x9A34;
            mtc1(v0, f0);
            lwc1(f4, v1, 0);
        }
        // 0x0046f918
        charge(ctx, 137);
        t1 = dsll32(t0, 0);
        lwc1(f3, v1, 4);
        v0 = 0x3F000000;
        lwc1(f2, v1, 8);
        t2 = v0 | 0x9A34;
        lwc1(f1, v1, 12);
        t1 = dsra32(t1, 0);
        mtc1(t2, f5);
        t0 = 0x960000;
        a3 = 0x960000;
        a2 = 0x960000;
        mul_s(f4, f4, f0);
        a1 = 0x960000;
        sw(zero, sp, 0x48);
        a0 = 0x960000;
        sw(zero, sp, 0x4C);
        v0 = 0x960000;
        sw(zero, sp, 0x38);
        v1 = 0x960000;
        sw(zero, sp, 0x3C);
        mul_s(f3, f3, f0);
        sw(zero, sp, 0x28);
        sw(zero, sp, 0x2C);
        sw(zero, sp, 0x18);
        sw(zero, sp, 0x1C);
        mul_s(f2, f2, f0);
        mul_s(f1, f5, f1);
        swc1(f4, sp, 0x80);
        swc1(f3, sp, 0x84);
        swc1(f2, sp, 0x88);
        swc1(f1, sp, 0x8C);
        lq(t2, sp, 0x80);
        sq(t2, t1, 0);
        lw(t1, t0, -4216);  // 0x95EF88
        lw(t0, gp, -17148);  // 0x7CE9F4
        t0 = addiu(t0, 16);
        sw(t0, gp, -17148);  // 0x7CE9F4
        lwc1(f4, t1, 24);
        lw(t0, gp, -17148);  // 0x7CE9F4
        lwc1(f3, t1, 28);
        lwc1(f2, t1, 32);
        lwc1(f1, t1, 36);
        mul_s(f4, f4, f0);
        mul_s(f3, f3, f0);
        mul_s(f2, f2, f0);
        mul_s(f1, f5, f1);
        swc1(f4, sp, 0x70);
        swc1(f3, sp, 0x74);
        swc1(f2, sp, 0x78);
        swc1(f1, sp, 0x7C);
        lq(t1, sp, 0x70);
        sq(t1, t0, 0);
        lw(t1, a3, -4216);  // 0x95EF88
        lw(a3, gp, -17148);  // 0x7CE9F4
        t0 = addiu(a3, 16);
        sw(t0, gp, -17148);  // 0x7CE9F4
        lwc1(f4, t1, 48);
        lw(a3, gp, -17148);  // 0x7CE9F4
        lwc1(f3, t1, 52);
        lwc1(f2, t1, 56);
        lwc1(f1, t1, 60);
        mul_s(f4, f4, f0);
        mul_s(f3, f3, f0);
        mul_s(f2, f2, f0);
        mul_s(f1, f5, f1);
        swc1(f4, sp, 0x60);
        swc1(f3, sp, 0x64);
        swc1(f2, sp, 0x68);
        swc1(f1, sp, 0x6C);
        lq(t0, sp, 0x60);
        sq(t0, a3, 0);
        lw(a3, a2, -4216);  // 0x95EF88
        lw(a2, gp, -17148);  // 0x7CE9F4
        t0 = addiu(a2, 16);
        sw(t0, gp, -17148);  // 0x7CE9F4
        lwc1(f1, a3, 84);
        lw(a2, gp, -17148);  // 0x7CE9F4
        lwc1(f4, a3, 72);
        lwc1(f3, a3, 76);
        lwc1(f2, a3, 80);
        mul_s(f1, f5, f1);
        swc1(f1, sp, 0x5C);
        mul_s(f4, f4, f0);
        mul_s(f1, f3, f0);
        mul_s(f0, f2, f0);
        swc1(f4, sp, 0x50);
        swc1(f1, sp, 0x54);
        swc1(f0, sp, 0x58);
        lq(a3, sp, 0x50);
        sq(a3, a2, 0);
        lw(a2, a1, -4216);  // 0x95EF88
        lw(a1, gp, -17148);  // 0x7CE9F4
        t0 = addiu(a1, 16);
        sw(t0, gp, -17148);  // 0x7CE9F4
        lwc1(f1, a2, 16);
        lw(a1, gp, -17148);  // 0x7CE9F4
        lwc1(f0, a2, 20);
        swc1(f1, sp, 0x40);
        swc1(f0, sp, 0x44);
        lq(a2, sp, 0x40);
        sq(a2, a1, 0);
        lw(a1, a0, -4216);  // 0x95EF88
        lw(a0, gp, -17148);  // 0x7CE9F4
        t0 = addiu(a0, 16);
        sw(t0, gp, -17148);  // 0x7CE9F4
        lwc1(f1, a1, 40);
        lw(a0, gp, -17148);  // 0x7CE9F4
        lwc1(f0, a1, 44);
        swc1(f1, sp, 0x30);
        swc1(f0, sp, 0x34);
        lq(a1, sp, 0x30);
        sq(a1, a0, 0);
        lw(a0, v1, -4216);  // 0x95EF88
        lw(v1, gp, -17148);  // 0x7CE9F4
        t0 = addiu(v1, 16);
        sw(t0, gp, -17148);  // 0x7CE9F4
        lwc1(f1, a0, 64);
        lw(v1, gp, -17148);  // 0x7CE9F4
        lwc1(f0, a0, 68);
        swc1(f1, sp, 0x20);
        swc1(f0, sp, 0x24);
        lq(a0, sp, 0x20);
        sq(a0, v1, 0);
        lw(v1, v0, -4216);  // 0x95EF88
        lw(v0, gp, -17148);  // 0x7CE9F4
        t0 = addiu(v0, 16);
        sw(t0, gp, -17148);  // 0x7CE9F4
        lwc1(f1, v1, 88);
        lw(v0, gp, -17148);  // 0x7CE9F4
        lwc1(f0, v1, 92);
        swc1(f1, sp, 0x10);
        swc1(f0, sp, 0x14);
        lq(v1, sp, 0x10);
        sq(v1, v0, 0);
        lw(v0, gp, -17148);  // 0x7CE9F4
        t0 = addiu(v0, 16);
        sw(t0, gp, -17148);  // 0x7CE9F4
    }
    // 0x0046fb3c
    charge(ctx, 2);
    v0 = 1;
    // 0x0046fb64
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// 0x00470200 sub_470200 -- 1396 bytes; frame 0xB0: ra sp+0x40, s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// G3_2DFont_Node: builds the VIF/GIF packet of a 2D font (glyph quads) node; same failure message.
void sub_470200(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, t8{ctx, 24}, t9{ctx, 25}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f20{ctx, 20};
    // 0x00470200
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    v0 = 0x960000;
    sd(ra, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    s2 = a0;
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    lw(s0, v0, -4212);  // 0x95EF8C
    lw(a0, s0, 308);
    s1 = a1;
    jal(ctx, 0x470228u, gen::fn_sub_4C2090_004c2090);
    lw(v1, s0, 16);
    v1 = v1 & 0x2;
    if (v1 == 0) {
        // 0x00470250
        charge(ctx, 3);
        t0 = 1;
        a2 = 0;
        a3 = 0;
    } else {
        // 0x00470240
        charge(ctx, 4);
        t0 = 2;
        a2 = 255;
        a3 = 1;
    }
    // 0x0047025c
    charge(ctx, 8);
    v1 = 0x960000;
    lw(t1, v1, -4156);  // 0x95EFC4
    mtc1(zero, f20);
    v1 = 0x960000;
    lw(v1, v1, -4152);  // 0x95EFC8
    at = slt(0, v1);
    t2 = 0;
    if (at != 0) {
        // 0x0047027c
        charge(ctx, 8);
        a0 = sll(t0, 1);
        v1 = a2 & 0xFF;
        a0 = addu(a0, t0);
        t7 = si(-1);
        a0 = sll(a0, 2);
        t4 = 0x960000;
        t6 = 0x960000;
        t5 = 0x960000;
        for (;;) {
            // 0x0047029c
            charge(ctx, 5);
            lw(a1, t6, -4204);
            t3 = 0;
            a1 = addu(a1, a0);
            sw(a1, t5, -4204);
            a1 = subu(a1, t0);
            for (;;) {
                // 0x004702b0
                charge(ctx, 9);
                t8 = addu(a3, a1);
                lbu(t9, t8, 0);
                lbu(t8, a1, 0);
                t9 = v1 & t9;
                t9 = sll(t9, 8);
                t9 = t8 | t9;
                t8 = slti(t9, 128);
                if (t8 != 0) {
                    // 0x00470308
                    charge(ctx, 4);
                    t8 = sll(t9, 1);
                    t8 = addu(s0, t8);
                    lh(t8, t8, 36);
                } else {
                    // 0x004702d4
                    charge(ctx, 4);
                    lw(t8, s0, 292);
                    t9 = subu(t9, t8);
                    if (i64(t9) >= 0) {
                        // 0x004702e4
                        charge(ctx, 4);
                        lw(t8, s0, 296);
                        at = slt(t9, t8);
                        if (at == 0) {
                            goto L_004706d8;
                        }
                        // 0x004702f4
                        charge(ctx, 5);
                        lw(t8, s0, 300);
                        t9 = sll(t9, 1);
                        t8 = addu(t8, t9);
                        lh(t8, t8, 0);
                        goto L_00470318;
                    }
                L_004706d8:
                    charge(ctx, 2);
                    t8 = t7;
                    backedge(ctx);
                }
            L_00470318:
                charge(ctx, 2);
                if (i64(t8) < 0) {
                    // 0x004706e0
                    charge(ctx, 10);
                    sw(zero, s2, 0);
                    sw(zero, s2, 4);
                    sw(zero, s2, 8);
                    sw(zero, s1, 0);
                    s2 = addiu(s2, 12);
                    sw(zero, s1, 4);
                    lwc1(f0, s0, 12);
                    s1 = addiu(s1, 8);
                    add_s(f20, f20, f0);
                    backedge(ctx);
                } else {
                    // 0x00470320
                    charge(ctx, 18);
                    t8 = sll(t8, 5);
                    t8 = addu(v0, t8);
                    lwc1(f0, t8, 8);
                    swc1(f0, s2, 0);
                    lwc1(f0, t8, 12);
                    swc1(f0, s2, 4);
                    lwc1(f0, t8, 0);
                    swc1(f0, s2, 8);
                    lwc1(f0, t8, 16);
                    s2 = addiu(s2, 12);
                    swc1(f0, s1, 0);
                    lwc1(f0, t8, 20);
                    swc1(f0, s1, 4);
                    lwc1(f1, t8, 0);
                    s1 = addiu(s1, 8);
                    lwc1(f0, s0, 12);
                    add_s(f0, f1, f0);
                    add_s(f20, f20, f0);
                }
                // 0x00470368
                charge(ctx, 4);
                t3 = addiu(t3, 1);
                t8 = slti(t3, 12);
                a1 = subu(a1, t0);
                if (t8 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00470378
            charge(ctx, 5);
            lw(a1, t4, -4152);
            t2 = addiu(t2, 1);
            a1 = slt(t2, a1);
            t1 = addiu(t1, -12);
            if (a1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0047038c
        charge(ctx, 1);
    }
    // 0x00470390
    charge(ctx, 10);
    mult(t2, t1, t0);
    v1 = 0x960000;
    lw(a1, v1, -4204);  // 0x95EF94
    at = slt(0, t1);
    a0 = 0;
    v1 = 0x960000;
    a1 = addu(a1, t2);
    sw(a1, v1, -4204);  // 0x95EF94
    a1 = subu(a1, t0);
    if (at != 0) {
        // 0x004703b8
        charge(ctx, 2);
        v1 = a2 & 0xFF;
        a2 = si(-1);
        for (;;) {
            // 0x004703c0
            charge(ctx, 9);
            t3 = addu(a3, a1);
            lbu(t2, a1, 0);
            lbu(t3, t3, 0);
            t3 = v1 & t3;
            t3 = sll(t3, 8);
            t3 = t2 | t3;
            t2 = slti(t3, 128);
            if (t2 != 0) {
                // 0x00470418
                charge(ctx, 4);
                t2 = sll(t3, 1);
                t2 = addu(s0, t2);
                lh(t2, t2, 36);
            } else {
                // 0x004703e4
                charge(ctx, 4);
                lw(t2, s0, 292);
                t3 = subu(t3, t2);
                if (i64(t3) >= 0) {
                    // 0x004703f4
                    charge(ctx, 4);
                    lw(t2, s0, 296);
                    at = slt(t3, t2);
                    if (at == 0) {
                        goto L_00470708;
                    }
                    // 0x00470404
                    charge(ctx, 5);
                    lw(t2, s0, 300);
                    t3 = sll(t3, 1);
                    t2 = addu(t2, t3);
                    lh(t2, t2, 0);
                    goto L_00470428;
                }
            L_00470708:
                charge(ctx, 2);
                t2 = a2;
                backedge(ctx);
            }
        L_00470428:
            charge(ctx, 2);
            if (i64(t2) < 0) {
                // 0x00470710
                charge(ctx, 10);
                sw(zero, s2, 0);
                sw(zero, s2, 4);
                sw(zero, s2, 8);
                sw(zero, s1, 0);
                s2 = addiu(s2, 12);
                sw(zero, s1, 4);
                lwc1(f0, s0, 12);
                s1 = addiu(s1, 8);
                add_s(f20, f20, f0);
                backedge(ctx);
            } else {
                // 0x00470430
                charge(ctx, 18);
                t2 = sll(t2, 5);
                t2 = addu(v0, t2);
                lwc1(f0, t2, 8);
                swc1(f0, s2, 0);
                lwc1(f0, t2, 12);
                swc1(f0, s2, 4);
                lwc1(f0, t2, 0);
                swc1(f0, s2, 8);
                lwc1(f0, t2, 16);
                s2 = addiu(s2, 12);
                swc1(f0, s1, 0);
                lwc1(f0, t2, 20);
                swc1(f0, s1, 4);
                lwc1(f1, t2, 0);
                s1 = addiu(s1, 8);
                lwc1(f0, s0, 12);
                add_s(f0, f1, f0);
                add_s(f20, f20, f0);
            }
            // 0x00470478
            charge(ctx, 4);
            a0 = addiu(a0, 1);
            t2 = slt(a0, t1);
            a1 = subu(a1, t0);
            if (t2 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00470488
    charge(ctx, 5);
    a0 = 0;
    a1 = 9;
    jal(ctx, 0x47048Cu, gen::fn__rwDMAOpenVIFPkt_004d59d0);
    if (v0 == 0) {
        // 0x00470738
        charge(ctx, 8);
        a0 = 0x6B0000;
        a1 = 0x6B0000;
        a0 = addiu(a0, 22688);  // "%s(%d): DMA memory failure\n"
        a1 = addiu(a1, 22720);  // "G3_2DFont_Node.c"
        a2 = 330;
        jal(ctx, 0x470748u, gen::fn_printf_005225a8);
        backedge(ctx);
    } else {
        // 0x0047049c
        charge(ctx, 139);
        v0 = 0x6C070000;
        v1 = 0x10000000;
        a0 = v0 | 0x3CF;
        a1 = 0;
        v0 = 0x1000000;
        t1 = 1042;
        v0 = v0 | 0x101;  // &0x1000101
        t0 = 0x960000;
        ppacw(a2, a0, v0);
        sw(zero, sp, 0x58);
        sw(zero, sp, 0x5C);
        a0 = v1 | 0x7;
        lw(v0, gp, -17148);  // 0x7CE9F4
        ppacw(a0, a1, a0);
        ppacw(a0, a2, a0);
        sq(a0, v0, 0);
        v1 = 0x960000;
        v0 = 0x960000;
        lw(a0, gp, -17148);  // 0x7CE9F4
        lwc1(f0, v0, -4192);  // 0x95EFA0
        lw(v1, v1, -4216);  // 0x95EF88
        a3 = 0x960000;
        a2 = 0x960000;
        a1 = 0x960000;
        v0 = 0x960000;
        lwc1(f2, v0, -4264);  // 0x95EF58
        swc1(f0, sp, 0xA4);
        v0 = 0x960000;
        lwc1(f1, v0, -4188);  // 0x95EFA4
        swc1(f2, sp, 0xA8);
        v0 = 0x3F000000;
        v0 = v0 | 0x9A34;
        mtc1(v0, f0);
        swc1(f1, sp, 0xAC);
        v0 = addiu(a0, 16);
        sw(v0, gp, -17148);  // 0x7CE9F4
        a0 = 0x960000;
        lwc1(f2, v1, 112);
        v0 = 0x302D0000;
        v0 = v0 | 0xC000;
        lw(t2, gp, -17148);  // 0x7CE9F4
        v0 = dsll32(v0, 0);
        pcpyld(v0, t1, v0);
        swc1(f2, sp, 0xA0);
        v1 = 0x960000;
        lq(t1, sp, 0xA0);
        sq(t1, t2, 0);
        lw(t1, t0, -4216);  // 0x95EF88
        lw(t0, gp, -17148);  // 0x7CE9F4
        t0 = addiu(t0, 16);
        sw(t0, gp, -17148);  // 0x7CE9F4
        lwc1(f4, t1, 0);
        lw(t0, gp, -17148);  // 0x7CE9F4
        lwc1(f3, t1, 4);
        lwc1(f2, t1, 8);
        lwc1(f1, t1, 12);
        mul_s(f4, f0, f4);
        mul_s(f3, f0, f3);
        mul_s(f2, f0, f2);
        mul_s(f1, f0, f1);
        swc1(f4, sp, 0x90);
        swc1(f3, sp, 0x94);
        swc1(f2, sp, 0x98);
        swc1(f1, sp, 0x9C);
        lq(t1, sp, 0x90);
        sq(t1, t0, 0);
        lw(t0, a3, -4216);  // 0x95EF88
        lw(a3, gp, -17148);  // 0x7CE9F4
        a3 = addiu(a3, 16);
        sw(a3, gp, -17148);  // 0x7CE9F4
        lwc1(f4, t0, 24);
        lw(a3, gp, -17148);  // 0x7CE9F4
        lwc1(f3, t0, 28);
        lwc1(f2, t0, 32);
        lwc1(f1, t0, 36);
        mul_s(f4, f0, f4);
        mul_s(f3, f0, f3);
        mul_s(f2, f0, f2);
        mul_s(f1, f0, f1);
        swc1(f4, sp, 0x80);
        swc1(f3, sp, 0x84);
        swc1(f2, sp, 0x88);
        swc1(f1, sp, 0x8C);
        lq(t0, sp, 0x80);
        sq(t0, a3, 0);
        lw(a3, a2, -4216);  // 0x95EF88
        lw(a2, gp, -17148);  // 0x7CE9F4
        a2 = addiu(a2, 16);
        sw(a2, gp, -17148);  // 0x7CE9F4
        lwc1(f4, a3, 48);
        lw(a2, gp, -17148);  // 0x7CE9F4
        lwc1(f3, a3, 52);
        lwc1(f2, a3, 56);
        lwc1(f1, a3, 60);
        mul_s(f4, f0, f4);
        mul_s(f3, f0, f3);
        mul_s(f2, f0, f2);
        mul_s(f1, f0, f1);
        swc1(f4, sp, 0x70);
        swc1(f3, sp, 0x74);
        swc1(f2, sp, 0x78);
        swc1(f1, sp, 0x7C);
        lq(a3, sp, 0x70);
        sq(a3, a2, 0);
        lw(a2, a1, -4216);  // 0x95EF88
        lw(a1, gp, -17148);  // 0x7CE9F4
        a1 = addiu(a1, 16);
        sw(a1, gp, -17148);  // 0x7CE9F4
        lwc1(f4, a2, 72);
        lw(a1, gp, -17148);  // 0x7CE9F4
        lwc1(f3, a2, 76);
        lwc1(f2, a2, 80);
        lwc1(f1, a2, 84);
        mul_s(f4, f0, f4);
        mul_s(f3, f0, f3);
        mul_s(f2, f0, f2);
        mul_s(f0, f0, f1);
        swc1(f4, sp, 0x60);
        swc1(f3, sp, 0x64);
        swc1(f2, sp, 0x68);
        swc1(f0, sp, 0x6C);
        lq(a2, sp, 0x60);
        sq(a2, a1, 0);
        lwc1(f0, v1, -4184);  // 0x95EFA8
        lw(a0, a0, -4212);  // 0x95EF8C
        lw(v1, gp, -17148);  // 0x7CE9F4
        swc1(f0, sp, 0x54);
        v1 = addiu(v1, 16);
        sw(v1, gp, -17148);  // 0x7CE9F4
        lwc1(f0, a0, 12);
        swc1(f0, sp, 0x50);
        lw(a0, gp, -17148);  // 0x7CE9F4
        lq(v1, sp, 0x50);
        sq(v1, a0, 0);
        sq(v0, a0, 16);
        lw(v0, gp, -17148);  // 0x7CE9F4
        v0 = addiu(v0, 32);
        sw(v0, gp, -17148);  // 0x7CE9F4
    }
    // 0x004706c8
    charge(ctx, 4);
    v1 = 0x960000;
    v0 = 1;
    swc1(f20, v1, -4184);  // 0x95EFA8
    // 0x00470758
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lwc1(f20, sp, 0x0);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0xB0);
}

// 0x00470E10 sub_470E10 -- 1016 bytes; frame 0xB0: ra sp+0x0
// G3_2DFill_Node: builds the VIF/GIF packet of a 2D filled-shape node; same failure message.
void sub_470E10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5};
    // 0x00470e10
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    v0 = 0x960000;
    sd(ra, sp, 0x0);
    lw(a3, v0, -4200);  // 0x95EF98
    v0 = 0x960000;
    lw(a2, v0, -4196);  // 0x95EF9C
    v0 = 0x960000;
    lw(v0, v0, -4156);  // 0x95EFC4
    v0 = sra(v0, 1);
    at = slt(0, v0);
    t0 = 0;
    if (at != 0) {
        // 0x00470e40
        charge(ctx, 1);
        v0 = 0x960000;
        for (;;) {
            // 0x00470e44
            charge(ctx, 25);
            lwc1(f0, a3, 4);
            t0 = addiu(t0, 1);
            swc1(f0, a0, 0);
            lwc1(f0, a3, 8);
            swc1(f0, a0, 4);
            lwc1(f0, a3, 12);
            swc1(f0, a1, 0);
            lwc1(f0, a3, 16);
            swc1(f0, a1, 4);
            a3 = addiu(a3, 24);
            lwc1(f0, a2, 4);
            swc1(f0, a0, 8);
            lwc1(f0, a2, 8);
            swc1(f0, a0, 12);
            lwc1(f0, a2, 12);
            a0 = addiu(a0, 16);
            swc1(f0, a1, 8);
            lwc1(f0, a2, 16);
            swc1(f0, a1, 12);
            a2 = addiu(a2, -24);
            lw(v1, v0, -4156);
            v1 = sra(v1, 1);
            v1 = slt(t0, v1);
            a1 = addiu(a1, 16);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00470ea8
    charge(ctx, 5);
    a0 = 0;
    a1 = 12;
    jal(ctx, 0x470EACu, gen::fn__rwDMAOpenVIFPkt_004d59d0);
    if (v0 == 0) {
        // 0x004711dc
        charge(ctx, 8);
        a0 = 0x6B0000;
        a1 = 0x6B0000;
        a0 = addiu(a0, 23024);  // "%s(%d): DMA memory failure\n"
        a1 = addiu(a1, 23056);  // "G3_2DFill_Node.c"
        a2 = 243;
        jal(ctx, 0x4711ECu, gen::fn_printf_005225a8);
        backedge(ctx);
    } else {
        // 0x00470ebc
        charge(ctx, 39);
        v1 = 0x6C0A0000;
        v0 = 0x1000000;
        v1 = v1 | 0x3CF;
        v0 = v0 | 0x101;  // &0x1000101
        ppacw(a2, v1, v0);
        v1 = 0x10000000;
        a1 = 0;
        a0 = v1 | 0xA;
        lw(v0, gp, -17148);  // 0x7CE9F4
        ppacw(a0, a1, a0);
        ppacw(a0, a2, a0);
        sq(a0, v0, 0);
        v1 = 0x960000;
        v0 = 0x960000;
        lw(a0, gp, -17148);  // 0x7CE9F4
        lwc1(f2, v0, -4192);  // 0x95EFA0
        lw(v1, v1, -4216);  // 0x95EF88
        t4 = addiu(a0, 16);
        v0 = 0x960000;
        sw(t4, gp, -17148);  // 0x7CE9F4
        lwc1(f1, v0, -4264);  // 0x95EF58
        swc1(f2, sp, 0xA4);
        v0 = 0x960000;
        lwc1(f0, v0, -4188);  // 0x95EFA4
        swc1(f1, sp, 0xA8);
        swc1(f0, sp, 0xAC);
        v0 = 0x960000;
        lwc1(f0, v1, 112);
        swc1(f0, sp, 0xA0);
        lw(v1, gp, -17148);  // 0x7CE9F4
        lq(a0, sp, 0xA0);
        sq(a0, v1, 0);
        lw(v1, v0, -4216);  // 0x95EF88
        lw(v0, gp, -17148);  // 0x7CE9F4
        t4 = addiu(v0, 16);
        sw(t4, gp, -17148);  // 0x7CE9F4
        lw(v0, v1, 104);
        if (v0 == 0) {
            // 0x00470f6c
            charge(ctx, 3);
            v0 = 0x3F800000;
            mtc1(v0, f0);
            lwc1(f4, v1, 0);
        } else {
            // 0x00470f58
            charge(ctx, 5);
            v0 = 0x3F000000;
            v0 = v0 | 0x9A34;
            mtc1(v0, f0);
            lwc1(f4, v1, 0);
        }
        // 0x00470f78
        charge(ctx, 151);
        t5 = dsll32(t4, 0);
        lwc1(f3, v1, 4);
        v0 = 0x3F000000;
        lwc1(f2, v1, 8);
        t6 = v0 | 0x9A34;
        lwc1(f1, v1, 12);
        t5 = dsra32(t5, 0);
        mtc1(t6, f5);
        t4 = 0x960000;
        t3 = 0x960000;
        t2 = 0x960000;
        mul_s(f4, f4, f0);
        t1 = 0x960000;
        sw(zero, sp, 0x58);
        t0 = 0x960000;
        sw(zero, sp, 0x5C);
        a3 = 0x960000;
        sw(zero, sp, 0x48);
        a2 = 0x960000;
        sw(zero, sp, 0x4C);
        a1 = 0x960000;
        mul_s(f3, f3, f0);
        sw(zero, sp, 0x38);
        sw(zero, sp, 0x3C);
        a0 = 0x960000;
        sw(zero, sp, 0x28);
        v1 = 0x960000;
        sw(zero, sp, 0x2C);
        v0 = 0x960000;
        mul_s(f2, f2, f0);
        mul_s(f1, f5, f1);
        swc1(f4, sp, 0x90);
        swc1(f3, sp, 0x94);
        swc1(f2, sp, 0x98);
        swc1(f1, sp, 0x9C);
        lq(t6, sp, 0x90);
        sq(t6, t5, 0);
        lw(t5, t4, -4216);  // 0x95EF88
        lw(t4, gp, -17148);  // 0x7CE9F4
        t4 = addiu(t4, 16);
        sw(t4, gp, -17148);  // 0x7CE9F4
        lwc1(f4, t5, 24);
        lw(t4, gp, -17148);  // 0x7CE9F4
        lwc1(f3, t5, 28);
        lwc1(f2, t5, 32);
        lwc1(f1, t5, 36);
        mul_s(f4, f4, f0);
        mul_s(f3, f3, f0);
        mul_s(f2, f2, f0);
        mul_s(f1, f5, f1);
        swc1(f4, sp, 0x80);
        swc1(f3, sp, 0x84);
        swc1(f2, sp, 0x88);
        swc1(f1, sp, 0x8C);
        lq(t5, sp, 0x80);
        sq(t5, t4, 0);
        lw(t5, t3, -4216);  // 0x95EF88
        lw(t3, gp, -17148);  // 0x7CE9F4
        t4 = addiu(t3, 16);
        sw(t4, gp, -17148);  // 0x7CE9F4
        lwc1(f4, t5, 48);
        lw(t3, gp, -17148);  // 0x7CE9F4
        lwc1(f3, t5, 52);
        lwc1(f2, t5, 56);
        lwc1(f1, t5, 60);
        mul_s(f4, f4, f0);
        mul_s(f3, f3, f0);
        mul_s(f2, f2, f0);
        mul_s(f1, f5, f1);
        swc1(f4, sp, 0x70);
        swc1(f3, sp, 0x74);
        swc1(f2, sp, 0x78);
        swc1(f1, sp, 0x7C);
        lq(t4, sp, 0x70);
        sq(t4, t3, 0);
        lw(t3, t2, -4216);  // 0x95EF88
        lw(t2, gp, -17148);  // 0x7CE9F4
        t4 = addiu(t2, 16);
        sw(t4, gp, -17148);  // 0x7CE9F4
        lwc1(f1, t3, 84);
        lw(t2, gp, -17148);  // 0x7CE9F4
        lwc1(f4, t3, 72);
        lwc1(f3, t3, 76);
        lwc1(f2, t3, 80);
        mul_s(f1, f5, f1);
        swc1(f1, sp, 0x6C);
        mul_s(f4, f4, f0);
        mul_s(f1, f3, f0);
        mul_s(f0, f2, f0);
        swc1(f4, sp, 0x60);
        swc1(f1, sp, 0x64);
        swc1(f0, sp, 0x68);
        lq(t3, sp, 0x60);
        sq(t3, t2, 0);
        lw(t2, t1, -4216);  // 0x95EF88
        lw(t1, gp, -17148);  // 0x7CE9F4
        t4 = addiu(t1, 16);
        sw(t4, gp, -17148);  // 0x7CE9F4
        lwc1(f1, t2, 16);
        lw(t1, gp, -17148);  // 0x7CE9F4
        lwc1(f0, t2, 20);
        swc1(f1, sp, 0x50);
        swc1(f0, sp, 0x54);
        lq(t2, sp, 0x50);
        sq(t2, t1, 0);
        lw(t1, t0, -4216);  // 0x95EF88
        lw(t0, gp, -17148);  // 0x7CE9F4
        t4 = addiu(t0, 16);
        sw(t4, gp, -17148);  // 0x7CE9F4
        lwc1(f1, t1, 40);
        lw(t0, gp, -17148);  // 0x7CE9F4
        lwc1(f0, t1, 44);
        swc1(f1, sp, 0x40);
        swc1(f0, sp, 0x44);
        lq(t1, sp, 0x40);
        sq(t1, t0, 0);
        lw(t0, a3, -4216);  // 0x95EF88
        lw(a3, gp, -17148);  // 0x7CE9F4
        t4 = addiu(a3, 16);
        sw(t4, gp, -17148);  // 0x7CE9F4
        lwc1(f1, t0, 64);
        lw(a3, gp, -17148);  // 0x7CE9F4
        lwc1(f0, t0, 68);
        swc1(f1, sp, 0x30);
        swc1(f0, sp, 0x34);
        lq(t0, sp, 0x30);
        sq(t0, a3, 0);
        lw(a3, gp, -17148);  // 0x7CE9F4
        lw(a2, a2, -4216);  // 0x95EF88
        t4 = addiu(a3, 16);
        sw(t4, gp, -17148);  // 0x7CE9F4
        lwc1(f1, a2, 88);
        lw(a3, gp, -17148);  // 0x7CE9F4
        lwc1(f0, a2, 92);
        swc1(f1, sp, 0x20);
        swc1(f0, sp, 0x24);
        lq(a2, sp, 0x20);
        sq(a2, a3, 0);
        lwc1(f3, a1, -4180);  // 0x95EFAC
        lwc1(f2, a0, -4176);  // 0x95EFB0
        lwc1(f1, v1, -4164);  // 0x95EFBC
        lwc1(f0, v0, -4160);  // 0x95EFC0
        swc1(f3, sp, 0x10);
        swc1(f2, sp, 0x14);
        swc1(f1, sp, 0x18);
        swc1(f0, sp, 0x1C);
        lq(v0, sp, 0x10);
        sq(v0, a3, 16);
        lw(v0, gp, -17148);  // 0x7CE9F4
        t4 = addiu(v0, 32);
        sw(t4, gp, -17148);  // 0x7CE9F4
    }
    // 0x004711d4
    charge(ctx, 2);
    v0 = 1;
    // 0x004711fc
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0xB0);
}

// 0x00473FB0 sub_473FB0 -- 428 bytes; leaf frame (no stack)
// Normalises a 2D render-state flag word: when two flags of an exclusive pair are both set, keeps one (0x8000 /
// 0x20000 / 0x40000 / 0x80000 / 0x100000 groups, bits 0 / 2 against bit 3). Leaf.
void sub_473FB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, t8{ctx, 24};
    // 0x00473fb0
    enter(ctx, 42);  // entry check point + this block's cycles
    v0 = a0 & 0x1;
    t6 = 0x20000;
    v1 = v0 ^ 0x1;
    t4 = a0 & t6;
    v0 = a0 & 0x4;
    t6 = t4 ^ t6;
    v0 = v0 ^ 0x4;
    t5 = 0x40000;
    t2 = sltiu(v0, 1);
    t4 = a0 & t5;
    t3 = sltiu(v1, 1);
    v0 = a0 & 0x8;
    v1 = v0 ^ 0x8;
    t4 = t4 ^ t5;
    v0 = a0 & 0x20;
    t8 = sltiu(t6, 1);
    v0 = v0 ^ 0x20;
    t1 = sltiu(v1, 1);
    t0 = sltiu(v0, 1);
    t7 = sltiu(t4, 1);
    v0 = a0 & 0x40;
    t6 = 0x80000;
    v1 = v0 ^ 0x40;
    t4 = a0 & t6;
    v0 = a0 & 0x80;
    t6 = t4 ^ t6;
    v0 = v0 ^ 0x80;
    t5 = 0x100000;
    a2 = sltiu(v0, 1);
    t4 = a0 & t5;
    v0 = a0 & 0x100;
    a3 = sltiu(v1, 1);
    v0 = v0 ^ 0x100;
    t4 = t4 ^ t5;
    t5 = sltiu(t4, 1);
    v1 = a0 & 0x8000;
    a1 = sltiu(v0, 1);
    t4 = 1;
    v0 = v1 ^ 0x8000;
    t6 = sltiu(t6, 1);
    v0 = sltiu(v0, 1);
    if (t1 == t4) {
        // 0x00474058
        charge(ctx, 2);
        if (v0 == t4) {
            // 0x00474060
            charge(ctx, 1);
            a0 = v1;
        }
    }
    // 0x00474064
    charge(ctx, 3);
    v0 = 1;
    if (t0 == v0) {
        // 0x00474070
        charge(ctx, 2);
        if (t8 == v0) {
            // 0x00474078
            charge(ctx, 2);
            v0 = 0x20000;
            a0 = a0 & v0;
        }
    }
    // 0x00474080
    charge(ctx, 3);
    v0 = 1;
    if (a3 == v0) {
        // 0x0047408c
        charge(ctx, 2);
        if (t7 == v0) {
            // 0x00474094
            charge(ctx, 2);
            v0 = 0x40000;
            a0 = a0 & v0;
        }
    }
    // 0x0047409c
    charge(ctx, 3);
    v0 = 1;
    if (a2 == v0) {
        // 0x004740a8
        charge(ctx, 2);
        if (t6 == v0) {
            // 0x004740b0
            charge(ctx, 2);
            v0 = 0x80000;
            a0 = a0 & v0;
        }
    }
    // 0x004740b8
    charge(ctx, 3);
    v0 = 1;
    if (a1 == v0) {
        // 0x004740c4
        charge(ctx, 2);
        if (t5 == v0) {
            // 0x004740cc
            charge(ctx, 2);
            v0 = 0x100000;
            a0 = a0 & v0;
        }
    }
    // 0x004740d4
    charge(ctx, 3);
    v0 = 1;
    if (t1 == v0) {
        // 0x004740e0
        charge(ctx, 2);
        if (t3 == v0) {
            // 0x004740e8
            charge(ctx, 2);
            v0 = si(-2);
            a0 = a0 & v0;
        }
    }
    // 0x004740f0
    charge(ctx, 3);
    v0 = 1;
    if (t1 == v0) {
        // 0x004740fc
        charge(ctx, 2);
        if (t2 == v0) {
            // 0x00474104
            charge(ctx, 2);
            v0 = si(-5);
            a0 = a0 & v0;
        }
    }
    // 0x0047410c
    charge(ctx, 3);
    v0 = 1;
    if (t1 == v0) {
        // 0x00474118
        charge(ctx, 2);
        if (t0 == v0) {
            // 0x00474120
            charge(ctx, 2);
            v0 = si(-33);
            a0 = a0 & v0;
        }
    }
    // 0x00474128
    charge(ctx, 2);
    if (t1 == 0) {
        // 0x00474130
        charge(ctx, 2);
        if (t3 == 0) {
            // 0x00474138
            charge(ctx, 1);
            a0 = a0 | 0x1;
        }
    }
    // 0x0047413c
    charge(ctx, 4);
    v0 = 0x30000000;
    v0 = a0 & v0;
    if (v0 == 0) {
        // 0x0047414c
        charge(ctx, 2);
        v0 = 0x10000000;
        a0 = a0 | v0;
    }
    // 0x00474154 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = a0;
}

// 0x00474D30 sub_474D30 -- 484 bytes; frame 0x90: fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Leaf quadword routine of the 2D node code: loads the record's quadwords (+0x40..+0x80) and walks its 32-byte
// entries (count at +292).
void sub_474D30(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29}, fp{ctx, 30};
    // 0x00474d30
    enter(ctx, 77);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    v1 = sll(a1, 5);
    sq(fp, sp, 0x80);
    v1 = addu(v1, a0);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(t7, v1, 4);
    lw(s3, v1, 4);
    lw(s4, a0, 292);
    lw(a1, a0, 252);
    lw(s2, a0, 304);
    lq(t6, a0, 64);
    lq(t5, a0, 80);
    lw(v1, a0, 296);
    s0 = addiu(s4, -1);
    lq(t4, a0, 96);
    lq(t3, a0, 112);
    lq(s1, a0, 128);
    s5 = addu(s2, s3);
    ld(t2, a0, 144);
    ld(t1, a0, 152);
    ld(t0, a0, 160);
    ld(a3, a0, 168);
    ld(a2, a0, 176);
    lw(a1, a1, 24);
    mult(s4, s4, v1);
    s6 = 0x30000000;
    s2 = 0x10000000;
    s6 = dsll32(s6, 0);
    s7 = 0x4000000;
    fp = 0x5;
    s5 = addu(s5, s4);
    v1 = 0x14000000;
    s4 = 0x1000000;
    s3 = dsll32(v1, 0);
    s4 = s4 | 0x101;  // &0x1000101
    v1 = 0x17000000;
    s5 = addiu(s5, -16);
    s6 = s4 | s6;
    s4 = dsll32(s5, 0);
    v1 = dsll32(v1, 0);
    s4 = dsrl32(s4, 0);
    s5 = s2 | 0x2;
    s4 = dsll32(s4, 0);
    s2 = s4 | s2;
    pcpyld(t9, s3, s2);
    pcpyld(t8, v1, s2);
    s4 = 0x4B000000;
    v1 = 0x11000000;
    s2 = dsll32(s4, 0);
    v1 = dsll32(v1, 0);
    s2 = s4 | s2;
    s3 = t5 + t1;
    pcpyld(s5, s6, s5);
    sq(s5, t7, 0);
    pcpyld(s2, s2, s2);
    sq(s2, t7, 16);
    s4 = t6 + t2;
    lw(s6, a0, 252);
    s2 = t4 + t0;
    s5 = addiu(t7, 112);
    lwu(s6, s6, 16);
    a0 = t3 + a3;
    s6 = s6 | s7;
    pcpyld(s6, v1, s6);
    sq(s6, t7, 32);
    sq(t6, t7, 48);
    sq(t5, t7, 64);
    sq(t4, t7, 80);
    sq(t3, t7, 96);
    if (a1 == fp) {
        // 0x00474ec8
        charge(ctx, 4);
        sq(s1, s5, 0);
        s5 = addiu(s5, 16);
        s1 = s1 + a2;
        backedge(ctx);
    }
    // 0x00474e64
    charge(ctx, 4);
    sq(t9, s5, 0);
    t5 = addiu(s0, -1);
    s5 = addiu(s5, 16);
    if (s0 != 0) {
        // 0x00474e74
        charge(ctx, 1);
        t4 = 5;
        for (;;) {
            // 0x00474e78
            charge(ctx, 10);
            sq(s4, s5, 0);
            sq(s3, s5, 16);
            s4 = s4 + t2;
            sq(s2, s5, 32);
            s3 = s3 + t1;
            sq(a0, s5, 48);
            s2 = s2 + t0;
            s5 = addiu(s5, 64);
            a0 = a0 + a3;
            if (a1 == t4) {
                // 0x00474ed8
                charge(ctx, 4);
                sq(s1, s5, 0);
                s5 = addiu(s5, 16);
                s1 = s1 + a2;
                backedge(ctx);
            }
            // 0x00474ea0
            charge(ctx, 5);
            sq(t8, s5, 0);
            t3 = t5;
            s5 = addiu(s5, 16);
            t5 = addiu(t5, -1);
            if (t3 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00474eb4
        charge(ctx, 1);
    }
    // 0x00474eb8
    charge(ctx, 4);
    a0 = 0x60000000;
    pcpyld(v1, v1, a0);
    sq(v1, s5, 0);
    // 0x00474ee8
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
    sp = addiu(sp, 0x90);
}

// 0x00476490 sub_476490 -- 644 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Fills a buffer with one 64-bit pattern: writes 2 KiB of the pattern to the scratchpad, then copies it out with
// fromSPR DMA (D8) in 1024-quadword blocks, the tail with plain stores.
void sub_476490(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00476490
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    s2 = a2;
    sq(s0, sp, 0x0);
    s1 = sra(a1, 4);
    if (i64(a1) < 0) {
        // 0x004764b8
        charge(ctx, 2);
        v0 = addiu(a1, 15);
        s1 = sra(v0, 4);
    }
    // 0x004764c0
    charge(ctx, 9);
    v0 = sll(s1, 4);
    a0 = 0;
    s0 = subu(a1, v0);
    jal(ctx, 0x4764C8u, gen::fn__sceFlushCache_005033e0);
    v1 = 0x10010000;
    lw(a0, v1, -12288);  // 0x1000D000 D8 fromSPR CHCR
    a0 = a0 & 0x100;
    if (a0 != 0) {
        // 0x004765e8
        charge(ctx, 4);
        a0 = 256;
        sw(a0, v1, -8160);
        sync(ctx, 0);
        sync(ctx, 16);
        for (;;) {
            // 0x004765f8
            charge(ctx, 7);
            if (cop0_cond(ctx)) {
                break;
            }
            backedge(ctx);
        }
        // 0x00476614
        charge(ctx, 2);
        v1 = 0x10010000;
        backedge(ctx);
    } else {
        // 0x004764e4
        charge(ctx, 1);
        v1 = 0x10010000;
    }
    // 0x004764e8
    charge(ctx, 4);
    lw(a0, v1, -11264);
    a0 = a0 & 0x100;
    if (a0 != 0) {
        // 0x0047661c
        charge(ctx, 4);
        a0 = 512;
        sw(a0, v1, -8160);
        sync(ctx, 0);
        sync(ctx, 16);
        for (;;) {
            // 0x0047662c
            charge(ctx, 7);
            if (cop0_cond(ctx)) {
                break;
            }
            backedge(ctx);
        }
        // 0x00476648
        charge(ctx, 1);
        v1 = 0x10010000;
        for (;;) {
            // 0x0047664c
            charge(ctx, 7);
            lw(a0, v1, -11264);
            a0 = a0 & 0x100;
            if (a0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00476668
        charge(ctx, 2);
        ld(v1, s2, 0);
        backedge(ctx);
    } else {
        // 0x004764f8
        charge(ctx, 1);
        ld(v1, s2, 0);
    }
    // 0x004764fc
    charge(ctx, 5);
    a1 = 0x70000000;
    a2 = 0;
    sd(v1, sp, 0x50);
    sd(v1, sp, 0x58);
    lq(a0, sp, 0x50);
    for (;;) {
        // 0x00476510
        charge(ctx, 12);
        sq(a0, a1, 0);
        a2 = addiu(a2, 8);
        sq(a0, a1, 16);
        v1 = slti(a2, 1024);
        sq(a0, a1, 32);
        sq(a0, a1, 48);
        sq(a0, a1, 64);
        sq(a0, a1, 80);
        sq(a0, a1, 96);
        sq(a0, a1, 112);
        a1 = addiu(a1, 128);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00476540
    charge(ctx, 3);
    at = slti(s1, 1025);
    if (at == 0) {
        // 0x0047654c
        charge(ctx, 3);
        a1 = 256;
        v1 = 0x10010000;
        a0 = 1024;
        for (;;) {
            // 0x00476558
            charge(ctx, 4);
            lw(a2, v1, -12288);
            a2 = a2 & 0x100;
            if (a2 != 0) {
                // 0x00476670
                charge(ctx, 4);
                sw(a1, v1, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x00476680
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0047669c
                charge(ctx, 2);
                backedge(ctx);
            }
            // 0x00476568
            charge(ctx, 11);
            sw(a1, v1, -8176);
            sw(zero, v1, -12160);
            sw(s3, v1, -12272);
            sw(a0, v1, -12256);
            sw(a1, v1, -12288);
            sync(ctx, 0);
            sync(ctx, 16);
            s1 = addiu(s1, -1024);
            at = slti(s1, 1025);
            s3 = addiu(s3, 16384);
            if (at != 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00476594
        charge(ctx, 2);
    }
    // 0x004766a8
    charge(ctx, 2);
    if (s1 == 0) {
        backedge(ctx);
    } else {
        // 0x004766b0
        charge(ctx, 2);
        v1 = 0x10010000;
        backedge(ctx);
        // 0x0047659c
        charge(ctx, 4);
        lw(a0, v1, -12288);
        a0 = a0 & 0x100;
        if (a0 != 0) {
            // 0x004766b8
            charge(ctx, 4);
            a0 = 256;
            sw(a0, v1, -8160);
            sync(ctx, 0);
            sync(ctx, 16);
            for (;;) {
                // 0x004766c8
                charge(ctx, 7);
                if (cop0_cond(ctx)) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004766e4
            charge(ctx, 2);
            a0 = 256;
            backedge(ctx);
        } else {
            // 0x004765ac
            charge(ctx, 1);
            a0 = 256;
        }
        // 0x004765b0
        charge(ctx, 10);
        v1 = 0x10010000;
        sw(a0, v1, -8176);  // 0x1000E010 D_STAT
        sw(zero, v1, -12160);  // 0x1000D080 D8 fromSPR SADR
        sw(s3, v1, -12272);  // 0x1000D010 D8 fromSPR MADR
        sw(s1, v1, -12256);  // 0x1000D020 D8 fromSPR QWC
        sw(a0, v1, -12288);  // 0x1000D000 D8 fromSPR CHCR
        sync(ctx, 0);
        sync(ctx, 16);
        v1 = sll(s1, 4);
        s3 = addu(s3, v1);
    }
    // 0x004765d8
    charge(ctx, 2);
    if (s0 != 0) {
        // 0x004766ec
        charge(ctx, 4);
        v1 = 0x70000000;
        ld(v1, v1, 0);  // 0x70000000 SPR+0x0
        sd(v1, s3, 0);
        backedge(ctx);
    }
    // 0x004765e0
    charge(ctx, 2);
    ld(ra, sp, 0x40);
    // 0x004766fc
    charge(ctx, 6);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00476980 sub_476980 -- 664 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Copy through the scratchpad: toSPR (D9) in, fromSPR (D8) out, 1024-quadword blocks.
void sub_476980(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00476980
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    s1 = a2;
    s0 = sra(a1, 4);
    if (i64(a1) < 0) {
        // 0x004769a4
        charge(ctx, 2);
        v0 = addiu(a1, 15);
        s0 = sra(v0, 4);
    }
    // 0x004769ac
    charge(ctx, 7);
    a0 = 0;
    jal(ctx, 0x4769ACu, gen::fn__sceFlushCache_005033e0);
    v1 = 0x10010000;
    lw(a0, v1, -11264);  // 0x1000D400 D9 toSPR CHCR
    a0 = a0 & 0x100;
    if (a0 != 0) {
        // 0x00476b44
        charge(ctx, 4);
        a0 = 512;
        sw(a0, v1, -8160);
        sync(ctx, 0);
        sync(ctx, 16);
        for (;;) {
            // 0x00476b54
            charge(ctx, 7);
            if (cop0_cond(ctx)) {
                break;
            }
            backedge(ctx);
        }
        // 0x00476b70
        charge(ctx, 1);
        v1 = 0x10010000;
        for (;;) {
            // 0x00476b74
            charge(ctx, 7);
            lw(a0, v1, -11264);
            a0 = a0 & 0x100;
            if (a0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00476b90
        charge(ctx, 2);
        v1 = 0x10010000;
        backedge(ctx);
    } else {
        // 0x004769c8
        charge(ctx, 1);
        v1 = 0x10010000;
    }
    // 0x004769cc
    charge(ctx, 4);
    lw(a0, v1, -12288);
    a0 = a0 & 0x100;
    if (a0 != 0) {
        // 0x00476b98
        charge(ctx, 4);
        a0 = 256;
        sw(a0, v1, -8160);
        sync(ctx, 0);
        sync(ctx, 16);
        for (;;) {
            // 0x00476ba8
            charge(ctx, 7);
            if (cop0_cond(ctx)) {
                break;
            }
            backedge(ctx);
        }
        // 0x00476bc4
        charge(ctx, 2);
        a1 = 0x70000000;
        backedge(ctx);
    } else {
        // 0x004769dc
        charge(ctx, 1);
        a1 = 0x70000000;
    }
    // 0x004769e0
    charge(ctx, 1);
    a2 = 0;
    for (;;) {
        // 0x004769e4
        charge(ctx, 36);
        lq(a0, s1, 0);
        a2 = addiu(a2, 8);
        v1 = slti(a2, 512);
        sq(a0, a1, 0);
        lq(a0, s1, 16);
        sq(a0, a1, 16);
        lq(a0, s1, 0);
        sq(a0, a1, 32);
        lq(a0, s1, 16);
        sq(a0, a1, 48);
        lq(a0, s1, 0);
        sq(a0, a1, 64);
        lq(a0, s1, 16);
        sq(a0, a1, 80);
        lq(a0, s1, 0);
        sq(a0, a1, 96);
        lq(a0, s1, 16);
        sq(a0, a1, 112);
        lq(a0, s1, 0);
        sq(a0, a1, 128);
        lq(a0, s1, 16);
        sq(a0, a1, 144);
        lq(a0, s1, 0);
        sq(a0, a1, 160);
        lq(a0, s1, 16);
        sq(a0, a1, 176);
        lq(a0, s1, 0);
        sq(a0, a1, 192);
        lq(a0, s1, 16);
        sq(a0, a1, 208);
        lq(a0, s1, 0);
        sq(a0, a1, 224);
        lq(a0, s1, 16);
        sq(a0, a1, 240);
        a1 = addiu(a1, 256);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00476a74
    charge(ctx, 3);
    at = slti(s0, 1025);
    if (at == 0) {
        // 0x00476a80
        charge(ctx, 3);
        a1 = 256;
        v1 = 0x10010000;
        a0 = 1024;
        for (;;) {
            // 0x00476a8c
            charge(ctx, 4);
            lw(a2, v1, -12288);
            a2 = a2 & 0x100;
            if (a2 != 0) {
                // 0x00476bcc
                charge(ctx, 3);
                sw(a1, v1, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x00476bd8
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00476bf4
                charge(ctx, 2);
                backedge(ctx);
            } else {
                // 0x00476a9c
                charge(ctx, 1);
            }
            // 0x00476aa0
            charge(ctx, 11);
            sw(a1, v1, -8176);
            sw(zero, v1, -12160);
            sw(s2, v1, -12272);
            sw(a0, v1, -12256);
            sw(a1, v1, -12288);
            sync(ctx, 0);
            sync(ctx, 16);
            s0 = addiu(s0, -1024);
            at = slti(s0, 1025);
            s2 = addiu(s2, 16384);
            if (at != 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00476acc
        charge(ctx, 1);
    }
    // 0x00476ad0
    charge(ctx, 2);
    if (s0 != 0) {
        // 0x00476ad8
        charge(ctx, 5);
        v1 = 0x10010000;
        lw(a0, v1, -12288);  // 0x1000D000 D8 fromSPR CHCR
        a0 = a0 & 0x100;
        if (a0 != 0) {
            // 0x00476aec
            charge(ctx, 4);
            a0 = 256;
            sw(a0, v1, -8160);
            sync(ctx, 0);
            sync(ctx, 16);
            for (;;) {
                // 0x00476afc
                charge(ctx, 7);
                if (cop0_cond(ctx)) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x00476b18
        charge(ctx, 11);
        a0 = 256;
        v1 = 0x10010000;
        sw(a0, v1, -8176);  // 0x1000E010 D_STAT
        sw(zero, v1, -12160);  // 0x1000D080 D8 fromSPR SADR
        sw(s2, v1, -12272);  // 0x1000D010 D8 fromSPR MADR
        sw(s0, v1, -12256);  // 0x1000D020 D8 fromSPR QWC
        sw(a0, v1, -12288);  // 0x1000D000 D8 fromSPR CHCR
        sync(ctx, 0);
        sync(ctx, 16);
    }
    // 0x00476c00 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0047A510 sub_47A510 -- 512 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Accumulates a 2D node's dirty flags in its ring of flag words, copies the parameters (memcpy) and re-derives the
// state (sub_474A80).
void sub_47A510(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x0047a510
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = 1;
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    lw(a0, a1, 76);
    lw(v1, a0, 224);
    s0 = a3;
    if (v1 == v0) {
        // 0x0047a538
        charge(ctx, 5);
        lw(v1, a0, 228);
        lw(v0, a0, 232);
        at = slt(v1, v0);
        if (at == 0) {
            // 0x0047a6e4
            charge(ctx, 2);
            v0 = 0;
            backedge(ctx);
        } else {
            // 0x0047a54c
            charge(ctx, 1);
            v0 = addiu(v1, 1);
        }
        // 0x0047a550
        charge(ctx, 12);
        v0 = sll(v0, 2);
        v1 = addu(v0, a0);
        lw(v0, v1, 236);
        v0 = v0 | s0;
        sw(v0, v1, 236);
        lw(v0, a0, 228);
        v0 = sll(v0, 2);
        v0 = addu(v0, a0);
        v1 = addiu(v0, 236);
        lw(v0, v0, 236);
        if (v0 != 0) {
            // 0x0047a580
            charge(ctx, 2);
            sw(zero, v1, 0);
            s0 = s0 | v0;
        }
    }
    // 0x0047a588
    charge(ctx, 2);
    if (s0 != 0) {
        // 0x0047a590
        charge(ctx, 4);
        v0 = 0x10000000;
        v0 = s0 & v0;
        if (v0 != 0) {
            // 0x0047a6ec
            charge(ctx, 4);
            a0 = s1;
            jal(ctx, 0x47A6ECu, gen::fn_sub_474A80_00474a80);
            v1 = 0x80000;
            backedge(ctx);
        } else {
            // 0x0047a5a0
            charge(ctx, 1);
            v1 = 0x80000;
        }
        // 0x0047a5a4
        charge(ctx, 3);
        v0 = s0 & v1;
        if (v0 != 0) {
            // 0x0047a5b0
            charge(ctx, 4);
            lw(v0, s1, 88);
            v0 = v0 & v1;
            if (v0 != 0) {
                // 0x0047a5c0
                charge(ctx, 4);
                lw(a0, s1, 60);
                a1 = addiu(s1, 144);
                a2 = 16;
                jal(ctx, 0x47A5C8u, gen::fn_memcpy_00521250);
            }
        }
        // 0x0047a5d0
        charge(ctx, 4);
        v1 = 0x100000;
        v0 = s0 & v1;
        if (v0 != 0) {
            // 0x0047a5e0
            charge(ctx, 4);
            lw(v0, s1, 88);
            v0 = v0 & v1;
            if (v0 != 0) {
                // 0x0047a5f0
                charge(ctx, 4);
                lw(a0, s1, 68);
                a1 = addiu(s1, 144);
                a2 = 32;
                jal(ctx, 0x47A5F8u, gen::fn_memcpy_00521250);
            }
        }
        // 0x0047a600
        charge(ctx, 3);
        v0 = s0 & 0x2000;
        if (v0 != 0) {
            // 0x0047a60c
            charge(ctx, 6);
            lw(v1, s1, 88);
            v0 = 0x40000;
            v0 = v0 | 0x42;
            v0 = v1 & v0;
            if (v0 == 0) {
                // 0x0047a624
                charge(ctx, 9);
                lw(a2, s1, 36);
                lbu(a1, s1, 124);
                lbu(a0, s1, 125);
                lbu(v1, s1, 126);
                lbu(v0, s1, 127);
                sb(a1, a2, 0);
                sb(a0, a2, 1);
                sb(v1, a2, 2);
                sb(v0, a2, 3);
            }
        }
        // 0x0047a648
        charge(ctx, 4);
        v1 = 0x40000;
        v0 = s0 & v1;
        if (v0 != 0) {
            // 0x0047a658
            charge(ctx, 4);
            lw(v0, s1, 88);
            v0 = v0 & v1;
            if (v0 != 0) {
                // 0x0047a668
                charge(ctx, 4);
                lw(a0, s1, 44);
                a1 = addiu(s1, 128);
                a2 = 16;
                jal(ctx, 0x47A670u, gen::fn_memcpy_00521250);
            }
        }
        // 0x0047a678
        charge(ctx, 4);
        v1 = 0x20000;
        v0 = s0 & v1;
        if (v0 != 0) {
            // 0x0047a688
            charge(ctx, 4);
            lw(v0, s1, 88);
            v0 = v0 & v1;
            if (v0 != 0) {
                // 0x0047a698
                charge(ctx, 5);
                lw(v0, s1, 52);
                lwc1(f0, s1, 120);
                swc1(f0, v0, 0);
                lwc1(f0, s1, 120);
                swc1(f0, v0, 4);
            }
        }
        // 0x0047a6ac
        charge(ctx, 3);
        v0 = s0 & 0x4000;
        if (v0 != 0) {
            // 0x0047a6b8
            charge(ctx, 4);
            lw(v0, s1, 88);
            v0 = v0 & 0x4;
            if (v0 == 0) {
                // 0x0047a6c8
                charge(ctx, 5);
                lw(v0, s1, 28);
                lwc1(f1, s1, 112);
                lwc1(f0, s1, 116);
                swc1(f1, v0, 0);
                swc1(f0, v0, 4);
            }
        }
    }
    // 0x0047a6dc
    charge(ctx, 2);
    v0 = 1;
    // 0x0047a6fc
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0047A710 sub_47A710 -- 1116 bytes; frame 0xE0: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Opens a VU1 packet for a 2D batch (openVU1SetupPktNew, _rwDMAOpenVIFPkt), adds the code / data references
// (_rwDMAAddPURef) with interrupts held off (DIntr / EIntr).
void sub_47A710(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f12{ctx, 12};
    // 0x0047a710
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0xE0);
    v0 = 0x960000;
    sd(ra, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s2, v0, 112);  // 0x960070
    lw(s0, a1, 0);
    lw(v1, gp, -17792);  // 0x7CE770
    lw(s6, s2, 96);
    v0 = addu(s0, v1);
    lw(v0, v0, 0);
    lw(s3, v0, 156);
    s4 = addiu(v0, 80);
    lw(a0, v0, 4);
    lw(v1, s3, 252);
    v0 = addiu(a0, -1);
    lw(v1, v1, 16);
    divu(v0, v1);
    mflo(s1);
    mult(v1, s1, v1);
    lw(v0, s3, 220);
    s7 = subu(a0, v1);
    if (v0 != 0) {
        // 0x0047aa94
        charge(ctx, 31);
        lw(a0, s3, 228);
        v1 = 0x10000000;
        v0 = sll(s1, 4);
        a0 = sll(a0, 5);
        a0 = addu(a0, s3);
        lw(a0, a0, 24);
        sw(v1, a0, 0);
        sw(zero, a0, 8);
        lw(v1, s3, 252);
        lw(a0, s3, 228);
        lw(v1, v1, 24);
        a0 = sll(a0, 5);
        a0 = addu(a0, s3);
        v1 = addiu(v1, 1);
        mult(a2, v1, v0);
        lw(a1, a0, 28);
        v1 = dsll32(s7, 0);
        v0 = 0x4000000;
        v1 = dsrl32(v1, 0);
        v0 = v1 | v0;
        a0 = 0x20000000;
        v0 = dsll32(v0, 0);
        v1 = addu(a1, a2);
        v0 = dsra32(v0, 0);
        sw(a0, v1, 0);
        sw(v0, v1, 8);
        lw(v0, s3, 228);
        v0 = sll(v0, 5);
        v0 = addu(v0, s3);
        sw(v1, v0, 24);
        backedge(ctx);
    }
    // 0x0047a784
    charge(ctx, 5);
    a0 = 0;
    jal(ctx, 0x47A784u, gen::fn__sceFlushCache_005033e0);
    a2 = addiu(s2, 32);
    a1 = addiu(sp, 0xA0);
    a0 = 8;
    for (;;) {
        // 0x0047a798
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
    // 0x0047a7b8
    charge(ctx, 19);
    a0 = addiu(sp, 0xA0);
    a1 = 0;
    a2 = 0;
    jal(ctx, 0x47A7C0u, gen::fn_openVU1SetupPktNew_004ec2b0);
    lw(v0, s0, 24);
    a0 = s4;
    lw(v0, v0, 32);
    lw(s5, v0, 0);
    lw(s0, s5, 0);
    a1 = s0;
    jal(ctx, 0x47A7DCu, gen::fn_sub_4749A0_004749a0);
    a0 = s4;
    a1 = s0;
    jal(ctx, 0x47A7E8u, gen::fn_sub_4748C0_004748c0);
    a0 = 0;
    a1 = 18;
    jal(ctx, 0x47A7F4u, gen::fn__rwDMAOpenVIFPkt_004d59d0);
    if (v0 == 0) {
        // 0x0047ab10
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x0047a804
        charge(ctx, 71);
        lw(a2, gp, -17148);  // 0x7CE9F4
        v1 = 0x6C050000;
        v0 = 0x1000000;
        v1 = v1 | 0x3EB;
        a1 = v0 | 0x101;  // &0x1000101
        v1 = dsll32(v1, 0);
        v0 = 0x10000000;
        a3 = 0x40000000;
        v1 = a1 | v1;
        v0 = v0 | 0xF;
        pcpyld(v0, v1, v0);
        sq(v0, a2, 0);
        mtc1(a3, f1);
        lbu(t1, s3, 244);
        a0 = addiu(sp, 0x94);
        lbu(t5, s3, 245);
        a3 = lui(0xBE80);
        mtc1(a3, f4);
        lbu(t4, s3, 246);
        v1 = addiu(sp, 0x98);
        lbu(t3, s3, 247);
        v0 = addiu(sp, 0x9C);
        t2 = addiu(s1, 1);
        t0 = 0x960000;
        a3 = 0x960000;
        sw(t1, sp, 0x90);
        t1 = 0x6C020000;
        sw(t5, a0, 0);
        t1 = t1 | 0x3FA;
        sw(t4, v1, 0);
        t1 = dsll32(t1, 0);
        sw(t3, v0, 0);
        a1 = a1 | t1;
        t3 = 0;
        lq(t1, sp, 0x90);
        pcpyld(t3, a1, t3);
        sq(t1, a2, 16);
        lwc1(f0, s4, 104);
        lwc1(f2, s4, 108);
        swc1(f0, sp, 0x90);
        mul_s(f0, f1, f0);
        swc1(f0, v1, 0);
        mul_s(f0, f1, f2);
        swc1(f2, a0, 0);
        swc1(f0, v0, 0);
        lq(a1, sp, 0x90);
        sq(a1, a2, 32);
        lwc1(f3, s6, 12);
        sw(t2, v1, 0);
        lwc1(f1, s6, 16);
        sw(s7, v0, 0);
        lwc1(f2, s2, 112);
        lwc1(f0, s2, 116);
        cvt_s_w(f3, f3);
        cvt_s_w(f1, f1);
        mul_s(f3, f4, f3);
        mul_s(f1, f4, f1);
        mul_s(f2, f3, f2);
        mul_s(f0, f1, f0);
        swc1(f2, sp, 0x90);
        swc1(f0, a0, 0);
        lq(v0, sp, 0x90);
        sq(v0, a2, 48);
        lq(v0, t0, 22800);  // 0x965910
        sq(v0, a2, 64);
        lq(v0, a3, 22816);  // 0x965920
        sq(v0, a2, 80);
        sq(t3, a2, 96);
        lw(v1, s3, 252);
        ld(a0, v1, 0);
        if (s0 != 0) {
            // 0x0047a920
            charge(ctx, 4);
            v0 = 0x80000;
            v0 = dsll32(v0, 0);
            a0 = a0 | v0;
        }
        // 0x0047ab18
        charge(ctx, 4);
        ld(v0, gp, -20272);  // 0x7CDDC0
        v0 = v0 & 0x20;
        if (v0 == 0) {
            backedge(ctx);
        } else {
            // 0x0047ab28
            charge(ctx, 2);
            v0 = 0x100000;
            backedge(ctx);
            // 0x0047a930
            charge(ctx, 2);
            v0 = dsll32(v0, 0);
            a0 = a0 | v0;
        }
        // 0x0047a938
        charge(ctx, 3);
        lw(v0, s4, 100);
        if (v0 != 0) {
            // 0x0047a944
            charge(ctx, 3);
            v0 = 0x200000;
            v0 = dsll32(v0, 0);
            a0 = a0 | v0;
        }
        // 0x0047a950
        charge(ctx, 4);
        ld(v0, v1, 8);
        pcpyld(v0, v0, a0);
        sq(v0, a2, 112);
        if (s0 == 0) {
            // 0x0047a974
            charge(ctx, 4);
            v0 = 0x3B800000;
            v0 = v0 | 0x8081;
            mtc1(v0, f12);
            v0 = addiu(a2, 128);
        } else {
            // 0x0047a960
            charge(ctx, 5);
            v0 = 0x3B010000;
            v0 = v0 | 0x1B50;
            mtc1(v0, f12);
            v0 = addiu(a2, 128);
        }
        // 0x0047a984
        charge(ctx, 41);
        a0 = addiu(s5, 4);
        link(ctx, 0x47A988u);  // $ra first: the delay slot below depends on it
        sw(v0, gp, -17148);  // 0x7CE9F4
        call(ctx, gen::fn_sub_49CAB0_0049cab0);
        v0 = 0x50000000;
        lw(t2, gp, -17148);  // 0x7CE9F4
        v1 = v0 | 0x6;
        a0 = 0;
        v1 = dsll32(v1, 0);
        a1 = 14;
        pcpyld(a2, v1, a0);
        a0 = 0x10000000;
        v1 = 0x8005;
        a0 = dsll32(a0, 0);
        t1 = 67;
        v1 = v1 | a0;
        sq(a2, t2, 0);
        pcpyld(v1, a1, v1);
        sq(v1, t2, 16);
        t0 = 9;
        ld(a0, s3, 184);
        a3 = 72;
        a2 = 21;
        a1 = 79;
        pcpyld(a0, t1, a0);
        sq(a0, t2, 32);
        ld(a0, s3, 192);
        pcpyld(a0, t0, a0);
        sq(a0, t2, 48);
        ld(a0, s3, 200);
        pcpyld(a0, a3, a0);
        sq(a0, t2, 64);
        ld(a0, s3, 208);
        pcpyld(a0, a2, a0);
        sq(a0, t2, 80);
        ld(a0, gp, -17088);  // 0x7CEA30
        pcpyld(a0, a1, a0);
        sq(a0, t2, 96);
        lw(a1, s3, 248);
        lw(a0, gp, -16888);  // 0x7CEAF8
        v1 = addiu(t2, 112);
        if (a0 != a1) {
            // 0x0047aa28
            charge(ctx, 9);
            a0 = dsll32(a1, 0);
            sw(a1, gp, -16888);  // 0x7CEAF8
            a0 = dsrl32(a0, 0);
            a1 = 0;
            a0 = dsll32(a0, 0);
            v0 = a0 | v0;
            pcpyld(v0, a1, v0);
            sq(v0, v1, 0);
            v1 = addiu(v1, 16);
        }
        // 0x0047aa4c
        charge(ctx, 16);
        lw(a0, s3, 228);
        v0 = addiu(v1, 16);
        a0 = sll(a0, 5);
        s0 = addu(s3, a0);
        lq(a0, s0, 0);
        sq(a0, v1, 0);
        link(ctx, 0x47AA64u);  // $ra first: the delay slot below depends on it
        sw(v0, gp, -17148);  // 0x7CE9F4
        call(ctx, gen::fn_DIntr_0050d3a0);
        lw(v0, s0, 16);
        v0 = addiu(v0, 1);
        link(ctx, 0x47AA74u);  // $ra first: the delay slot below depends on it
        sw(v0, s0, 16);
        call(ctx, gen::fn_EIntr_0050d3f0);
        lw(v1, s0, 20);
        v0 = addiu(v1, 1);
        sw(v0, s0, 20);
        if (v1 == 0) {
            // 0x0047ab30
            charge(ctx, 4);
            a0 = addiu(s0, 16);
            jal(ctx, 0x47AB30u, gen::fn__rwDMAAddPURef_004d51c0);
            backedge(ctx);
        }
        // 0x0047aa8c
        charge(ctx, 2);
        v0 = 1;
    }
    // 0x0047ab40 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x80);
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

// 0x0047C240 sub_47C240 -- 1664 bytes; frame 0x60: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Scratchpad DMA kernel (function table): streams vertices in with toSPR (D9), transforms them on the scratchpad,
// writes them back with fromSPR (D8), double buffered, waiting on D_STAT.
void sub_47C240(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, t8{ctx, 24}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7};
    Vf vf1{ctx, 1}, vf2{ctx, 2}, vf3{ctx, 3}, vf4{ctx, 4}, vf5{ctx, 5}, vf6{ctx, 6}, vf7{ctx, 7};
    // 0x0047c240
    enter(ctx, 35);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    v1 = 0x3F000000;
    sd(ra, sp, 0x30);
    mtc1(v1, f7);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a3;
    sq(s0, sp, 0x0);
    lwc1(f2, t0, 112);
    lw(a3, t0, 8);
    lwc1(f1, t0, 116);
    lw(v1, a0, 4);
    lwc1(f5, a1, 0);
    lw(s1, t0, 4);
    lwc1(f3, a1, 8);
    lw(s0, a0, 0);
    lwc1(f0, a2, 0);
    lwc1(f4, a1, 4);
    mul_s(f6, f7, f2);
    mul_s(f2, f7, f1);
    mul_s(f1, f5, f6);
    swc1(f1, sp, 0x50);
    mul_s(f1, f3, f6);
    mul_s(f0, f0, f2);
    swc1(f1, sp, 0x58);
    swc1(f0, sp, 0x40);
    lwc1(f1, a2, 4);
    lwc1(f0, a2, 8);
    mul_s(f4, f4, f6);
    mul_s(f1, f1, f2);
    mul_s(f0, f0, f2);
    swc1(f4, sp, 0x54);
    swc1(f1, sp, 0x44);
    swc1(f0, sp, 0x48);
    if (a3 != v1) {
        // 0x0047c83c
        charge(ctx, 3);
        at = slt(0, s2);
        t0 = 0;
        if (at != 0) {
            // 0x0047c848
            charge(ctx, 3);
            a0 = sll(v1, 2);
            a2 = addiu(sp, 0x50);
            a1 = addiu(sp, 0x40);
            for (;;) {
                // 0x0047c854
                charge(ctx, 20);
                lqc2(vf1, s1, 0);
                lqc2(vf2, a2, 0);
                lqc2(vf3, a1, 0);
                vsub(0xE, vf4, vf1, vf2);  // vsub.xyz
                vadd(0xE, vf5, vf1, vf2);  // vadd.xyz
                vadd(0xE, vf6, vf1, vf2);  // vadd.xyz
                vsub(0xE, vf7, vf1, vf2);  // vsub.xyz
                vsub(0xE, vf4, vf4, vf3);  // vsub.xyz
                vsub(0xE, vf5, vf5, vf3);  // vsub.xyz
                vadd(0xE, vf6, vf6, vf3);  // vadd.xyz
                vadd(0xE, vf7, vf7, vf3);  // vadd.xyz
                sqc2(vf4, s0, 0);
                sqc2(vf5, s0, 16);
                sqc2(vf6, s0, 32);
                sqc2(vf7, s0, 48);
                t0 = addiu(t0, 1);
                s0 = addu(s0, a0);
                v1 = slt(t0, s2);
                s1 = addu(s1, a3);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0047c8a4
            charge(ctx, 1);
        }
    } else {
        // 0x0047c2cc
        charge(ctx, 7);
        a0 = 0;
        jal(ctx, 0x47C2CCu, gen::fn__sceFlushCache_005033e0);
        v1 = 0x10010000;
        lw(a0, v1, -12288);  // 0x1000D000 D8 fromSPR CHCR
        a0 = a0 & 0x100;
        if (a0 != 0) {
            // 0x0047c2e8
            charge(ctx, 4);
            a0 = 256;
            sw(a0, v1, -8160);
            sync(ctx, 0);
            sync(ctx, 16);
            for (;;) {
                // 0x0047c2f8
                charge(ctx, 7);
                if (cop0_cond(ctx)) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x0047c314
        charge(ctx, 5);
        v1 = 0x10010000;
        lw(a0, v1, -12288);  // 0x1000D000 D8 fromSPR CHCR
        a0 = a0 & 0x100;
        if (a0 != 0) {
            // 0x0047c328
            charge(ctx, 4);
            a0 = 256;
            sw(a0, v1, -8160);
            sync(ctx, 0);
            sync(ctx, 16);
            for (;;) {
                // 0x0047c338
                charge(ctx, 7);
                if (cop0_cond(ctx)) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x0047c354
        charge(ctx, 3);
        at = slti(s2, 205);
        if (at == 0) {
            // 0x0047c360
            charge(ctx, 10);
            t5 = 0x70000000;
            a2 = 0x10010000;
            t3 = addiu(sp, 0x50);
            t2 = addiu(sp, 0x40);
            a1 = 256;
            a0 = 512;
            v1 = 204;
            t0 = 3264;
            t4 = t5 | 0xCC0;
            a3 = 816;
            for (;;) {
                // 0x0047c388
                charge(ctx, 4);
                lw(t1, a2, -12288);
                t1 = t1 & 0x100;
                if (t1 != 0) {
                    // 0x0047c398
                    charge(ctx, 4);
                    sw(a1, a2, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x0047c3a8
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047c3c4
                    charge(ctx, 1);
                }
                // 0x0047c3c8
                charge(ctx, 4);
                lw(t1, a2, -11264);
                t1 = t1 & 0x100;
                if (t1 != 0) {
                    // 0x0047c3d8
                    charge(ctx, 4);
                    sw(a0, a2, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x0047c3e8
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047c404
                    charge(ctx, 1);
                    for (;;) {
                        // 0x0047c408
                        charge(ctx, 7);
                        lw(t1, a2, -11264);
                        t1 = t1 & 0x100;
                        if (t1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047c424
                    charge(ctx, 1);
                }
                // 0x0047c428
                charge(ctx, 11);
                sw(a0, a2, -8176);
                sw(zero, a2, -11136);
                sw(s1, a2, -11248);
                sw(v1, a2, -11232);
                sw(a1, a2, -11264);
                sync(ctx, 0);
                sync(ctx, 16);
                lw(t1, a2, -11264);
                t1 = t1 & 0x100;
                if (t1 != 0) {
                    // 0x0047c454
                    charge(ctx, 3);
                    sw(a0, a2, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x0047c460
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047c47c
                    charge(ctx, 1);
                    for (;;) {
                        // 0x0047c480
                        charge(ctx, 7);
                        lw(t1, a2, -11264);
                        t1 = t1 & 0x100;
                        if (t1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047c49c
                    charge(ctx, 1);
                }
                // 0x0047c4a0
                charge(ctx, 4);
                t7 = t5;
                t6 = t4;
                t8 = 0;
                for (;;) {
                    // 0x0047c4b0
                    charge(ctx, 20);
                    lqc2(vf1, t7, 0);
                    lqc2(vf2, t3, 0);
                    lqc2(vf3, t2, 0);
                    vsub(0xE, vf4, vf1, vf2);  // vsub.xyz
                    vadd(0xE, vf5, vf1, vf2);  // vadd.xyz
                    vadd(0xE, vf6, vf1, vf2);  // vadd.xyz
                    vsub(0xE, vf7, vf1, vf2);  // vsub.xyz
                    vsub(0xE, vf4, vf4, vf3);  // vsub.xyz
                    vsub(0xE, vf5, vf5, vf3);  // vsub.xyz
                    vadd(0xE, vf6, vf6, vf3);  // vadd.xyz
                    vadd(0xE, vf7, vf7, vf3);  // vadd.xyz
                    sqc2(vf4, t6, 0);
                    sqc2(vf5, t6, 16);
                    sqc2(vf6, t6, 32);
                    sqc2(vf7, t6, 48);
                    t8 = addiu(t8, 1);
                    t6 = addiu(t6, 64);
                    t1 = slti(t8, 204);
                    t7 = addiu(t7, 16);
                    if (t1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0047c500
                charge(ctx, 4);
                lw(t1, a2, -12288);
                t1 = t1 & 0x100;
                if (t1 != 0) {
                    // 0x0047c510
                    charge(ctx, 4);
                    sw(a1, a2, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x0047c520
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047c53c
                    charge(ctx, 1);
                }
                // 0x0047c540
                charge(ctx, 4);
                lw(t1, a2, -11264);
                t1 = t1 & 0x100;
                if (t1 != 0) {
                    // 0x0047c550
                    charge(ctx, 4);
                    sw(a0, a2, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x0047c560
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047c57c
                    charge(ctx, 1);
                    for (;;) {
                        // 0x0047c580
                        charge(ctx, 7);
                        lw(t1, a2, -11264);
                        t1 = t1 & 0x100;
                        if (t1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047c59c
                    charge(ctx, 1);
                }
                // 0x0047c5a0
                charge(ctx, 12);
                sw(a1, a2, -8176);
                sw(t0, a2, -12160);
                sw(s0, a2, -12272);
                sw(a3, a2, -12256);
                sw(a1, a2, -12288);
                sync(ctx, 0);
                sync(ctx, 16);
                s2 = addiu(s2, -204);
                s1 = addiu(s1, 3264);
                at = slti(s2, 205);
                s0 = addiu(s0, 13056);
                if (at != 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x0047c5d0
        charge(ctx, 2);
        if (s2 != 0) {
            // 0x0047c5d8
            charge(ctx, 5);
            v1 = 0x10010000;
            lw(a0, v1, -12288);  // 0x1000D000 D8 fromSPR CHCR
            a0 = a0 & 0x100;
            if (a0 != 0) {
                // 0x0047c5ec
                charge(ctx, 4);
                a0 = 256;
                sw(a0, v1, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x0047c5fc
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x0047c618
            charge(ctx, 5);
            v1 = 0x10010000;
            lw(a0, v1, -11264);  // 0x1000D400 D9 toSPR CHCR
            a0 = a0 & 0x100;
            if (a0 != 0) {
                // 0x0047c62c
                charge(ctx, 4);
                a0 = 512;
                sw(a0, v1, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x0047c63c
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0047c658
                charge(ctx, 1);
                v1 = 0x10010000;
                for (;;) {
                    // 0x0047c65c
                    charge(ctx, 7);
                    lw(a0, v1, -11264);
                    a0 = a0 & 0x100;
                    if (a0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x0047c678
            charge(ctx, 14);
            a1 = 512;
            v1 = 0x10010000;
            a0 = 256;
            sw(a1, v1, -8176);  // 0x1000E010 D_STAT
            sw(zero, v1, -11136);  // 0x1000D480 D9 toSPR SADR
            sw(s1, v1, -11248);  // 0x1000D410 D9 toSPR MADR
            sw(s2, v1, -11232);  // 0x1000D420 D9 toSPR QWC
            sw(a0, v1, -11264);  // 0x1000D400 D9 toSPR CHCR
            sync(ctx, 0);
            sync(ctx, 16);
            lw(a0, v1, -11264);  // 0x1000D400 D9 toSPR CHCR
            a0 = a0 & 0x100;
            if (a0 != 0) {
                // 0x0047c6b0
                charge(ctx, 3);
                sw(a1, v1, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x0047c6bc
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0047c6d8
                charge(ctx, 1);
                v1 = 0x10010000;
                for (;;) {
                    // 0x0047c6dc
                    charge(ctx, 7);
                    lw(a0, v1, -11264);
                    a0 = a0 & 0x100;
                    if (a0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x0047c6f8
            charge(ctx, 5);
            t7 = 0x70000000;
            at = slt(0, s2);
            t6 = t7 | 0xCC0;
            a2 = 0;
            if (at != 0) {
                // 0x0047c70c
                charge(ctx, 2);
                a1 = addiu(sp, 0x50);
                a0 = addiu(sp, 0x40);
                for (;;) {
                    // 0x0047c714
                    charge(ctx, 20);
                    lqc2(vf1, t7, 0);
                    lqc2(vf2, a1, 0);
                    lqc2(vf3, a0, 0);
                    vsub(0xE, vf4, vf1, vf2);  // vsub.xyz
                    vadd(0xE, vf5, vf1, vf2);  // vadd.xyz
                    vadd(0xE, vf6, vf1, vf2);  // vadd.xyz
                    vsub(0xE, vf7, vf1, vf2);  // vsub.xyz
                    vsub(0xE, vf4, vf4, vf3);  // vsub.xyz
                    vsub(0xE, vf5, vf5, vf3);  // vsub.xyz
                    vadd(0xE, vf6, vf6, vf3);  // vadd.xyz
                    vadd(0xE, vf7, vf7, vf3);  // vadd.xyz
                    sqc2(vf4, t6, 0);
                    sqc2(vf5, t6, 16);
                    sqc2(vf6, t6, 32);
                    sqc2(vf7, t6, 48);
                    a2 = addiu(a2, 1);
                    t6 = addiu(t6, 64);
                    v1 = slt(a2, s2);
                    t7 = addiu(t7, 16);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0047c764
                charge(ctx, 1);
            }
            // 0x0047c768
            charge(ctx, 5);
            v1 = 0x10010000;
            lw(a0, v1, -12288);  // 0x1000D000 D8 fromSPR CHCR
            a0 = a0 & 0x100;
            if (a0 != 0) {
                // 0x0047c77c
                charge(ctx, 4);
                a0 = 256;
                sw(a0, v1, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x0047c78c
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x0047c7a8
            charge(ctx, 5);
            v1 = 0x10010000;
            lw(a0, v1, -11264);  // 0x1000D400 D9 toSPR CHCR
            a0 = a0 & 0x100;
            if (a0 != 0) {
                // 0x0047c7bc
                charge(ctx, 4);
                a0 = 512;
                sw(a0, v1, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x0047c7cc
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0047c7e8
                charge(ctx, 1);
                v1 = 0x10010000;
                for (;;) {
                    // 0x0047c7ec
                    charge(ctx, 7);
                    lw(a0, v1, -11264);
                    a0 = a0 & 0x100;
                    if (a0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x0047c808
            charge(ctx, 13);
            a2 = 256;
            v1 = 0x10010000;
            a1 = 3264;
            sw(a2, v1, -8176);  // 0x1000E010 D_STAT
            a0 = sll(s2, 2);
            sw(a1, v1, -12160);  // 0x1000D080 D8 fromSPR SADR
            sw(s0, v1, -12272);  // 0x1000D010 D8 fromSPR MADR
            sw(a0, v1, -12256);  // 0x1000D020 D8 fromSPR QWC
            sw(a2, v1, -12288);  // 0x1000D000 D8 fromSPR CHCR
            sync(ctx, 0);
            sync(ctx, 16);
        }
    }
    // 0x0047c8a8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x0047C8C0 sub_47C8C0 -- 1808 bytes; frame 0x70: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Scratchpad DMA kernel, variant of sub_47C240 (another vertex format).
void sub_47C8C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9};
    Vf vf1{ctx, 1}, vf2{ctx, 2}, vf3{ctx, 3}, vf4{ctx, 4}, vf5{ctx, 5}, vf6{ctx, 6}, vf7{ctx, 7}, vf8{ctx, 8};
    // 0x0047c8c0
    enter(ctx, 46);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    v1 = 0x3F000000;
    sd(ra, sp, 0x30);
    mtc1(v1, f2);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a3;
    sq(s0, sp, 0x0);
    lwc1(f1, t0, 112);
    lw(t1, t0, 8);
    lwc1(f0, t0, 116);
    lw(v1, a0, 4);
    lwc1(f9, a1, 0);
    lw(s1, t0, 4);
    lwc1(f8, a1, 4);
    lw(s0, a0, 0);
    lwc1(f7, a1, 8);
    lwc1(f5, a2, 0);
    mul_s(f1, f2, f1);
    mul_s(f6, f2, f0);
    mul_s(f0, f9, f1);
    swc1(f0, sp, 0x60);
    mul_s(f0, f8, f1);
    swc1(f0, sp, 0x64);
    mul_s(f0, f7, f1);
    swc1(f0, sp, 0x68);
    mul_s(f0, f5, f6);
    lwc1(f4, a2, 4);
    swc1(f0, sp, 0x50);
    lwc1(f1, t0, 108);
    lwc1(f3, a2, 8);
    lwc1(f2, t0, 104);
    mul_s(f0, f4, f6);
    swc1(f0, sp, 0x54);
    mul_s(f0, f3, f6);
    mula_s(f1, f5);
    swc1(f0, sp, 0x58);
    madd_s(f0, f2, f9);
    swc1(f0, sp, 0x40);
    mula_s(f1, f4);
    madd_s(f0, f2, f8);
    mula_s(f1, f3);
    swc1(f0, sp, 0x44);
    madd_s(f0, f2, f7);
    swc1(f0, sp, 0x48);
    if (t1 != v1) {
        // 0x0047cf34
        charge(ctx, 3);
        at = slt(0, s2);
        t0 = 0;
        if (at != 0) {
            // 0x0047cf40
            charge(ctx, 4);
            a0 = sll(v1, 2);
            a3 = addiu(sp, 0x60);
            a2 = addiu(sp, 0x50);
            a1 = addiu(sp, 0x40);
            for (;;) {
                // 0x0047cf50
                charge(ctx, 25);
                lqc2(vf1, s1, 0);
                lqc2(vf2, a3, 0);
                lqc2(vf3, a2, 0);
                lqc2(vf8, a1, 0);
                vsub(0xE, vf4, vf1, vf2);  // vsub.xyz
                vadd(0xE, vf5, vf1, vf2);  // vadd.xyz
                vadd(0xE, vf6, vf1, vf2);  // vadd.xyz
                vsub(0xE, vf7, vf1, vf2);  // vsub.xyz
                vsub(0xE, vf4, vf4, vf3);  // vsub.xyz
                vsub(0xE, vf5, vf5, vf3);  // vsub.xyz
                vadd(0xE, vf6, vf6, vf3);  // vadd.xyz
                vadd(0xE, vf7, vf7, vf3);  // vadd.xyz
                vadd(0xE, vf4, vf4, vf8);  // vadd.xyz
                vadd(0xE, vf5, vf5, vf8);  // vadd.xyz
                vadd(0xE, vf6, vf6, vf8);  // vadd.xyz
                vadd(0xE, vf7, vf7, vf8);  // vadd.xyz
                sqc2(vf4, s0, 0);
                sqc2(vf5, s0, 16);
                sqc2(vf6, s0, 32);
                sqc2(vf7, s0, 48);
                t0 = addiu(t0, 1);
                s0 = addu(s0, a0);
                v1 = slt(t0, s2);
                s1 = addu(s1, t1);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0047cfb4
            charge(ctx, 1);
        }
    } else {
        // 0x0047c978
        charge(ctx, 7);
        a0 = 0;
        jal(ctx, 0x47C978u, gen::fn__sceFlushCache_005033e0);
        v1 = 0x10010000;
        lw(a0, v1, -12288);  // 0x1000D000 D8 fromSPR CHCR
        a0 = a0 & 0x100;
        if (a0 != 0) {
            // 0x0047c994
            charge(ctx, 4);
            a0 = 256;
            sw(a0, v1, -8160);
            sync(ctx, 0);
            sync(ctx, 16);
            for (;;) {
                // 0x0047c9a4
                charge(ctx, 7);
                if (cop0_cond(ctx)) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x0047c9c0
        charge(ctx, 5);
        v1 = 0x10010000;
        lw(a0, v1, -11264);  // 0x1000D400 D9 toSPR CHCR
        a0 = a0 & 0x100;
        if (a0 != 0) {
            // 0x0047c9d4
            charge(ctx, 4);
            a0 = 512;
            sw(a0, v1, -8160);
            sync(ctx, 0);
            sync(ctx, 16);
            for (;;) {
                // 0x0047c9e4
                charge(ctx, 7);
                if (cop0_cond(ctx)) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0047ca00
            charge(ctx, 1);
            v1 = 0x10010000;
            for (;;) {
                // 0x0047ca04
                charge(ctx, 7);
                lw(a0, v1, -11264);
                a0 = a0 & 0x100;
                if (a0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x0047ca20
        charge(ctx, 3);
        at = slti(s2, 205);
        if (at == 0) {
            // 0x0047ca2c
            charge(ctx, 11);
            t6 = 0x70000000;
            a2 = 0x10010000;
            t4 = addiu(sp, 0x60);
            t3 = addiu(sp, 0x50);
            t2 = addiu(sp, 0x40);
            a1 = 256;
            a0 = 512;
            v1 = 204;
            t5 = t6 | 0xCC0;
            t0 = 3264;
            a3 = 816;
            for (;;) {
                // 0x0047ca58
                charge(ctx, 4);
                lw(t1, a2, -12288);
                t1 = t1 & 0x100;
                if (t1 != 0) {
                    // 0x0047ca68
                    charge(ctx, 4);
                    sw(a1, a2, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x0047ca78
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047ca94
                    charge(ctx, 1);
                }
                // 0x0047ca98
                charge(ctx, 4);
                lw(t1, a2, -11264);
                t1 = t1 & 0x100;
                if (t1 != 0) {
                    // 0x0047caa8
                    charge(ctx, 4);
                    sw(a0, a2, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x0047cab8
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047cad4
                    charge(ctx, 1);
                    for (;;) {
                        // 0x0047cad8
                        charge(ctx, 7);
                        lw(t1, a2, -11264);
                        t1 = t1 & 0x100;
                        if (t1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047caf4
                    charge(ctx, 1);
                }
                // 0x0047caf8
                charge(ctx, 11);
                sw(a0, a2, -8176);
                sw(zero, a2, -11136);
                sw(s1, a2, -11248);
                sw(v1, a2, -11232);
                sw(a1, a2, -11264);
                sync(ctx, 0);
                sync(ctx, 16);
                lw(t1, a2, -11264);
                t1 = t1 & 0x100;
                if (t1 != 0) {
                    // 0x0047cb24
                    charge(ctx, 3);
                    sw(a0, a2, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x0047cb30
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047cb4c
                    charge(ctx, 1);
                    for (;;) {
                        // 0x0047cb50
                        charge(ctx, 7);
                        lw(t1, a2, -11264);
                        t1 = t1 & 0x100;
                        if (t1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047cb6c
                    charge(ctx, 1);
                }
                // 0x0047cb70
                charge(ctx, 4);
                t8 = t6;
                t7 = t5;
                t9 = 0;
                for (;;) {
                    // 0x0047cb80
                    charge(ctx, 25);
                    lqc2(vf1, t8, 0);
                    lqc2(vf2, t4, 0);
                    lqc2(vf3, t3, 0);
                    lqc2(vf8, t2, 0);
                    vsub(0xE, vf4, vf1, vf2);  // vsub.xyz
                    vadd(0xE, vf5, vf1, vf2);  // vadd.xyz
                    vadd(0xE, vf6, vf1, vf2);  // vadd.xyz
                    vsub(0xE, vf7, vf1, vf2);  // vsub.xyz
                    vsub(0xE, vf4, vf4, vf3);  // vsub.xyz
                    vsub(0xE, vf5, vf5, vf3);  // vsub.xyz
                    vadd(0xE, vf6, vf6, vf3);  // vadd.xyz
                    vadd(0xE, vf7, vf7, vf3);  // vadd.xyz
                    vadd(0xE, vf4, vf4, vf8);  // vadd.xyz
                    vadd(0xE, vf5, vf5, vf8);  // vadd.xyz
                    vadd(0xE, vf6, vf6, vf8);  // vadd.xyz
                    vadd(0xE, vf7, vf7, vf8);  // vadd.xyz
                    sqc2(vf4, t7, 0);
                    sqc2(vf5, t7, 16);
                    sqc2(vf6, t7, 32);
                    sqc2(vf7, t7, 48);
                    t9 = addiu(t9, 1);
                    t7 = addiu(t7, 64);
                    t1 = slti(t9, 204);
                    t8 = addiu(t8, 16);
                    if (t1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0047cbe4
                charge(ctx, 4);
                lw(t1, a2, -12288);
                t1 = t1 & 0x100;
                if (t1 != 0) {
                    // 0x0047cbf4
                    charge(ctx, 3);
                    sw(a1, a2, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x0047cc00
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047cc1c
                    charge(ctx, 1);
                }
                // 0x0047cc20
                charge(ctx, 4);
                lw(t1, a2, -11264);
                t1 = t1 & 0x100;
                if (t1 != 0) {
                    // 0x0047cc30
                    charge(ctx, 4);
                    sw(a0, a2, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x0047cc40
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047cc5c
                    charge(ctx, 1);
                    for (;;) {
                        // 0x0047cc60
                        charge(ctx, 7);
                        lw(t1, a2, -11264);
                        t1 = t1 & 0x100;
                        if (t1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047cc7c
                    charge(ctx, 1);
                }
                // 0x0047cc80
                charge(ctx, 12);
                sw(a1, a2, -8176);
                sw(t0, a2, -12160);
                sw(s0, a2, -12272);
                sw(a3, a2, -12256);
                sw(a1, a2, -12288);
                sync(ctx, 0);
                sync(ctx, 16);
                s2 = addiu(s2, -204);
                s1 = addiu(s1, 3264);
                at = slti(s2, 205);
                s0 = addiu(s0, 13056);
                if (at != 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x0047ccb0
        charge(ctx, 2);
        if (s2 != 0) {
            // 0x0047ccb8
            charge(ctx, 5);
            v1 = 0x10010000;
            lw(a0, v1, -12288);  // 0x1000D000 D8 fromSPR CHCR
            a0 = a0 & 0x100;
            if (a0 != 0) {
                // 0x0047cccc
                charge(ctx, 4);
                a0 = 256;
                sw(a0, v1, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x0047ccdc
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x0047ccf8
            charge(ctx, 5);
            v1 = 0x10010000;
            lw(a0, v1, -11264);  // 0x1000D400 D9 toSPR CHCR
            a0 = a0 & 0x100;
            if (a0 != 0) {
                // 0x0047cd0c
                charge(ctx, 4);
                a0 = 512;
                sw(a0, v1, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x0047cd1c
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0047cd38
                charge(ctx, 1);
                v1 = 0x10010000;
                for (;;) {
                    // 0x0047cd3c
                    charge(ctx, 7);
                    lw(a0, v1, -11264);
                    a0 = a0 & 0x100;
                    if (a0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x0047cd58
            charge(ctx, 14);
            a1 = 512;
            v1 = 0x10010000;
            a0 = 256;
            sw(a1, v1, -8176);  // 0x1000E010 D_STAT
            sw(zero, v1, -11136);  // 0x1000D480 D9 toSPR SADR
            sw(s1, v1, -11248);  // 0x1000D410 D9 toSPR MADR
            sw(s2, v1, -11232);  // 0x1000D420 D9 toSPR QWC
            sw(a0, v1, -11264);  // 0x1000D400 D9 toSPR CHCR
            sync(ctx, 0);
            sync(ctx, 16);
            lw(a0, v1, -11264);  // 0x1000D400 D9 toSPR CHCR
            a0 = a0 & 0x100;
            if (a0 != 0) {
                // 0x0047cd90
                charge(ctx, 3);
                sw(a1, v1, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x0047cd9c
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0047cdb8
                charge(ctx, 1);
                v1 = 0x10010000;
                for (;;) {
                    // 0x0047cdbc
                    charge(ctx, 7);
                    lw(a0, v1, -11264);
                    a0 = a0 & 0x100;
                    if (a0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x0047cdd8
            charge(ctx, 5);
            t8 = 0x70000000;
            at = slt(0, s2);
            t7 = t8 | 0xCC0;
            a3 = 0;
            if (at != 0) {
                // 0x0047cdec
                charge(ctx, 3);
                a2 = addiu(sp, 0x60);
                a1 = addiu(sp, 0x50);
                a0 = addiu(sp, 0x40);
                for (;;) {
                    // 0x0047cdf8
                    charge(ctx, 25);
                    lqc2(vf1, t8, 0);
                    lqc2(vf2, a2, 0);
                    lqc2(vf3, a1, 0);
                    lqc2(vf8, a0, 0);
                    vsub(0xE, vf4, vf1, vf2);  // vsub.xyz
                    vadd(0xE, vf5, vf1, vf2);  // vadd.xyz
                    vadd(0xE, vf6, vf1, vf2);  // vadd.xyz
                    vsub(0xE, vf7, vf1, vf2);  // vsub.xyz
                    vsub(0xE, vf4, vf4, vf3);  // vsub.xyz
                    vsub(0xE, vf5, vf5, vf3);  // vsub.xyz
                    vadd(0xE, vf6, vf6, vf3);  // vadd.xyz
                    vadd(0xE, vf7, vf7, vf3);  // vadd.xyz
                    vadd(0xE, vf4, vf4, vf8);  // vadd.xyz
                    vadd(0xE, vf5, vf5, vf8);  // vadd.xyz
                    vadd(0xE, vf6, vf6, vf8);  // vadd.xyz
                    vadd(0xE, vf7, vf7, vf8);  // vadd.xyz
                    sqc2(vf4, t7, 0);
                    sqc2(vf5, t7, 16);
                    sqc2(vf6, t7, 32);
                    sqc2(vf7, t7, 48);
                    a3 = addiu(a3, 1);
                    t7 = addiu(t7, 64);
                    v1 = slt(a3, s2);
                    t8 = addiu(t8, 16);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0047ce5c
                charge(ctx, 1);
            }
            // 0x0047ce60
            charge(ctx, 5);
            v1 = 0x10010000;
            lw(a0, v1, -12288);  // 0x1000D000 D8 fromSPR CHCR
            a0 = a0 & 0x100;
            if (a0 != 0) {
                // 0x0047ce74
                charge(ctx, 4);
                a0 = 256;
                sw(a0, v1, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x0047ce84
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x0047cea0
            charge(ctx, 5);
            v1 = 0x10010000;
            lw(a0, v1, -11264);  // 0x1000D400 D9 toSPR CHCR
            a0 = a0 & 0x100;
            if (a0 != 0) {
                // 0x0047ceb4
                charge(ctx, 4);
                a0 = 512;
                sw(a0, v1, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x0047cec4
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0047cee0
                charge(ctx, 1);
                v1 = 0x10010000;
                for (;;) {
                    // 0x0047cee4
                    charge(ctx, 7);
                    lw(a0, v1, -11264);
                    a0 = a0 & 0x100;
                    if (a0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x0047cf00
            charge(ctx, 13);
            a2 = 256;
            v1 = 0x10010000;
            a1 = 3264;
            sw(a2, v1, -8176);  // 0x1000E010 D_STAT
            a0 = sll(s2, 2);
            sw(a1, v1, -12160);  // 0x1000D080 D8 fromSPR SADR
            sw(s0, v1, -12272);  // 0x1000D010 D8 fromSPR MADR
            sw(a0, v1, -12256);  // 0x1000D020 D8 fromSPR QWC
            sw(a2, v1, -12288);  // 0x1000D000 D8 fromSPR CHCR
            sync(ctx, 0);
            sync(ctx, 16);
        }
    }
    // 0x0047cfb8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x0047CFD0 sub_47CFD0 -- 3668 bytes; frame 0xD0: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// Scratchpad DMA kernel with a rotation (sinf / cosf) and a matrix kept at SPR 0x3F00.
void sub_47CFD0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, t8{ctx, 24}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    Vf vf0{ctx, 0}, vf1{ctx, 1}, vf2{ctx, 2}, vf3{ctx, 3}, vf4{ctx, 4}, vf5{ctx, 5}, vf6{ctx, 6}, vf7{ctx, 7}, vf8{ctx, 8}, vf9{ctx, 9}, vf10{ctx, 10}, vf11{ctx, 11}, vf12{ctx, 12}, vf13{ctx, 13}, vf16{ctx, 16}, vf17{ctx, 17}, vf18{ctx, 18}, vf19{ctx, 19}, vf20{ctx, 20}, vf21{ctx, 21}, vf22{ctx, 22}, vf23{ctx, 23}, vf24{ctx, 24}, vf25{ctx, 25}, vf26{ctx, 26}, vf27{ctx, 27}, vf28{ctx, 28}, vf29{ctx, 29}, vf30{ctx, 30}, vf31{ctx, 31};
    // 0x0047cfd0
    enter(ctx, 31);  // entry check point + this block's cycles
    sp = addiu(sp, -0xD0);
    v1 = 0x3F000000;
    sd(ra, sp, 0xA0);
    mtc1(v1, f2);
    sq(fp, sp, 0x90);
    sq(s7, sp, 0x80);
    sq(s6, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    s5 = a1;
    sq(s3, sp, 0x40);
    s4 = a2;
    sq(s2, sp, 0x30);
    s3 = a3;
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lwc1(f1, t0, 112);
    lw(v1, t0, 56);
    lwc1(f0, t0, 116);
    lw(fp, t0, 8);
    lw(s6, a0, 4);
    lw(s2, t0, 4);
    lw(s1, t0, 52);
    lw(s0, a0, 0);
    mul_s(f22, f2, f1);
    sq(v1, sp, 0xB0);
    mul_s(f21, f2, f0);
    if (fp != s6) {
        // 0x0047dc70
        charge(ctx, 3);
        at = slt(0, s3);
        s7 = 0;
        if (at != 0) {
            for (;;) {
                // 0x0047dc7c
                charge(ctx, 91);
                link(ctx, 0x47DC7Cu);  // $ra first: the delay slot below depends on it
                lwc1(f12, s1, 0);
                call(ctx, gen::fn_sinf_0052e878);
                lwc1(f12, s1, 0);
                mov_s(f20, f0);
                jal(ctx, 0x47DC88u, gen::fn_cosf_0052e6d8);
                lwc1(f9, s4, 0);
                a2 = addu(s0, s6);
                lwc1(f2, s5, 0);
                a1 = addu(a2, s6);
                neg_s(f3, f20);
                lq(v1, sp, 0xB0);
                lwc1(f8, s4, 4);
                a0 = addu(a1, s6);
                lwc1(f7, s5, 4);
                s7 = addiu(s7, 1);
                lwc1(f5, s4, 8);
                mula_s(f3, f9);
                madd_s(f1, f0, f2);
                mul_s(f6, f1, f22);
                s1 = addu(s1, v1);
                v1 = slt(s7, s3);
                mula_s(f3, f8);
                madd_s(f1, f0, f7);
                lwc1(f4, s5, 8);
                mula_s(f3, f5);
                mul_s(f10, f1, f22);
                madd_s(f3, f0, f4);
                mula_s(f0, f9);
                madd_s(f2, f20, f2);
                mula_s(f0, f8);
                madd_s(f1, f20, f7);
                mula_s(f0, f5);
                mul_s(f7, f1, f21);
                madd_s(f0, f20, f4);
                mul_s(f5, f2, f21);
                mul_s(f8, f0, f21);
                neg_s(f2, f6);
                sub_s(f0, f2, f5);
                lwc1(f1, s2, 0);
                mul_s(f9, f3, f22);
                add_s(f0, f1, f0);
                swc1(f0, s0, 0);
                neg_s(f1, f10);
                sub_s(f0, f1, f7);
                lwc1(f3, s2, 4);
                add_s(f2, f2, f5);
                add_s(f1, f1, f7);
                add_s(f0, f3, f0);
                swc1(f0, s0, 4);
                neg_s(f0, f9);
                sub_s(f3, f0, f8);
                lwc1(f4, s2, 8);
                add_s(f0, f0, f8);
                add_s(f3, f4, f3);
                swc1(f3, s0, 8);
                sub_s(f3, f6, f5);
                s0 = addu(a0, s6);
                lwc1(f4, s2, 0);
                add_s(f5, f6, f5);
                add_s(f3, f4, f3);
                swc1(f3, a2, 0);
                lwc1(f6, s2, 4);
                sub_s(f3, f10, f7);
                add_s(f4, f10, f7);
                add_s(f3, f6, f3);
                swc1(f3, a2, 4);
                lwc1(f7, s2, 8);
                sub_s(f6, f9, f8);
                add_s(f3, f9, f8);
                add_s(f6, f7, f6);
                swc1(f6, a2, 8);
                lwc1(f6, s2, 0);
                add_s(f5, f6, f5);
                swc1(f5, a1, 0);
                lwc1(f5, s2, 4);
                add_s(f4, f5, f4);
                swc1(f4, a1, 4);
                lwc1(f4, s2, 8);
                add_s(f3, f4, f3);
                swc1(f3, a1, 8);
                lwc1(f3, s2, 0);
                add_s(f2, f3, f2);
                swc1(f2, a0, 0);
                lwc1(f2, s2, 4);
                add_s(f1, f2, f1);
                swc1(f1, a0, 4);
                lwc1(f1, s2, 8);
                add_s(f0, f1, f0);
                s2 = addu(s2, fp);
                swc1(f0, a0, 8);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
    } else {
        // 0x0047d04c
        charge(ctx, 7);
        a0 = 0;
        jal(ctx, 0x47D04Cu, gen::fn__sceFlushCache_005033e0);
        v1 = 0x10010000;
        lw(a0, v1, -12288);  // 0x1000D000 D8 fromSPR CHCR
        a0 = a0 & 0x100;
        if (a0 != 0) {
            // 0x0047d068
            charge(ctx, 4);
            a0 = 256;
            sw(a0, v1, -8160);
            sync(ctx, 0);
            sync(ctx, 16);
            for (;;) {
                // 0x0047d078
                charge(ctx, 7);
                if (cop0_cond(ctx)) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x0047d094
        charge(ctx, 5);
        v1 = 0x10010000;
        lw(a0, v1, -11264);  // 0x1000D400 D9 toSPR CHCR
        a0 = a0 & 0x100;
        if (a0 != 0) {
            // 0x0047d0a8
            charge(ctx, 4);
            a0 = 512;
            sw(a0, v1, -8160);
            sync(ctx, 0);
            sync(ctx, 16);
            for (;;) {
                // 0x0047d0b8
                charge(ctx, 7);
                if (cop0_cond(ctx)) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0047d0d4
            charge(ctx, 1);
            v1 = 0x10010000;
            for (;;) {
                // 0x0047d0d8
                charge(ctx, 7);
                lw(a0, v1, -11264);
                a0 = a0 & 0x100;
                if (a0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0047d0f4
            charge(ctx, 1);
        }
        // 0x0047d0f8
        charge(ctx, 19);
        a0 = 0x70000000;
        lwc1(f2, s5, 0);
        t1 = a0 | 0x3F00;
        lwc1(f1, s5, 4);
        t0 = a0 | 0x3F10;
        lwc1(f0, s5, 8);
        v1 = a0 | 0x3F20;
        a3 = a0 | 0x3F30;
        a2 = a0 | 0x3F40;
        a0 = 0x10000;
        swc1(f2, t1, 0);  // 0x70003F00 SPR+0x3F00
        swc1(f1, t1, 4);  // 0x70003F04 SPR+0x3F04
        swc1(f0, t1, 8);  // 0x70003F08 SPR+0x3F08
        lwc1(f2, s4, 0);
        lwc1(f1, s4, 4);
        lwc1(f0, s4, 8);
        swc1(f2, t0, 0);  // 0x70003F10 SPR+0x3F10
        swc1(f1, t0, 4);  // 0x70003F14 SPR+0x3F14
        swc1(f0, t0, 8);  // 0x70003F18 SPR+0x3F18
        for (;;) {
            // 0x0047d144
            charge(ctx, 7);
            di(ctx);
            sync(ctx, 16);
            mfc0(a1, 12);
            a1 = a1 & a0;
            if (a1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0047d160
        charge(ctx, 88);
        at = 0x3FC90000;
        a0 = at | 0xFDB;
        mtc1(a0, f0);
        mfc1(a0, f0);
        ctc2(a0, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x8, vf10, vf0);  // vaddi.x
        at = 0x40490000;
        a1 = at | 0xFDB;
        mtc1(a1, f0);
        mfc1(a0, f0);
        ctc2(a0, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x4, vf10, vf0);  // vaddi.y
        at = 0x40090000;
        a0 = at | 0xFDB;
        mtc1(a0, f0);
        mfc1(a0, f0);
        ctc2(a0, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x2, vf10, vf0);  // vaddi.z
        mtc1(a1, f0);
        neg_s(f0, f0);
        mfc1(a0, f0);
        ctc2(a0, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x8, vf11, vf0);  // vaddi.x
        at = 0x40840000;
        a0 = at | 0x87ED;
        mtc1(a0, f0);
        neg_s(f0, f0);
        mfc1(a0, f0);
        ctc2(a0, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x4, vf11, vf0);  // vaddi.y
        a0 = 0x0;
        a0 = dsll(a0, 16);
        a0 = dsll(a0, 16);
        a0 = a0 | 0xB94F;
        a0 = dsll(a0, 16);
        a0 = a0 | 0xB21F;
        ctc2(a0, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x2, vf11, vf0);  // vaddi.z
        a0 = 0x0;
        a0 = dsll(a0, 16);
        a0 = dsll(a0, 16);
        a0 = a0 | 0xBE2A;
        a0 = dsll(a0, 16);
        a0 = a0 | 0xAAA4;
        ctc2(a0, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x8, vf12, vf0);  // vaddi.x
        at = 0x3C080000;
        a0 = at | 0x873E;
        ctc2(a0, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x4, vf12, vf0);  // vaddi.y
        at = 0x362E0000;
        a0 = at | 0x9C14;
        ctc2(a0, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x2, vf12, vf0);  // vaddi.z
        a0 = 0x3F800000;
        ctc2(a0, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x8, vf13, vf0);  // vaddi.x
        ei(ctx);
        a0 = 0x70000000;
        swc1(f22, a0, 16188);  // 0x70003F3C SPR+0x3F3C
        a1 = 0x10000;
        swc1(f22, a0, 16184);  // 0x70003F38 SPR+0x3F38
        swc1(f22, a0, 16180);  // 0x70003F34 SPR+0x3F34
        swc1(f22, a0, 16176);  // 0x70003F30 SPR+0x3F30
        swc1(f21, a0, 16204);  // 0x70003F4C SPR+0x3F4C
        swc1(f21, a0, 16200);  // 0x70003F48 SPR+0x3F48
        swc1(f21, a0, 16196);  // 0x70003F44 SPR+0x3F44
        swc1(f21, a0, 16192);  // 0x70003F40 SPR+0x3F40
        for (;;) {
            // 0x0047d2c0
            charge(ctx, 7);
            di(ctx);
            sync(ctx, 16);
            mfc0(a0, 12);
            a0 = a0 & a1;
            if (a0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0047d2dc
        charge(ctx, 13);
        lqc2(vf2, t1, 0);
        lqc2(vf4, a3, 0);
        lqc2(vf3, t0, 0);
        lqc2(vf5, a2, 0);
        vnop(ctx);
        vmul(0xF, vf8, vf2, vf4);  // vmul.xyzw
        vmul(0xF, vf16, vf3, vf4);  // vmul.xyzw
        vmul(0xF, vf9, vf2, vf5);  // vmul.xyzw
        vmul(0xF, vf17, vf3, vf5);  // vmul.xyzw
        ei(ctx);
        a0 = slti(s3, 192);
        if (a0 == 0) {
            // 0x0047d310
            charge(ctx, 11);
            t6 = 0x70000000;
            t0 = 0x10010000;
            t3 = 0x10000;
            t8 = 256;
            s7 = 512;
            s5 = 48;
            s4 = 768;
            t7 = 192;
            t5 = t6 | 0x300;
            t4 = t6 | 0xF00;
            t1 = 3840;
            for (;;) {
                // 0x0047d33c
                charge(ctx, 4);
                lw(a0, t0, -12288);
                a0 = a0 & 0x100;
                if (a0 != 0) {
                    // 0x0047d34c
                    charge(ctx, 3);
                    sw(t8, t0, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x0047d358
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047d374
                    charge(ctx, 1);
                }
                // 0x0047d378
                charge(ctx, 4);
                lw(a0, t0, -11264);
                a0 = a0 & 0x100;
                if (a0 != 0) {
                    // 0x0047d388
                    charge(ctx, 4);
                    sw(s7, t0, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x0047d398
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047d3b4
                    charge(ctx, 1);
                    for (;;) {
                        // 0x0047d3b8
                        charge(ctx, 7);
                        lw(a0, t0, -11264);
                        a0 = a0 & 0x100;
                        if (a0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047d3d4
                    charge(ctx, 1);
                }
                // 0x0047d3d8
                charge(ctx, 11);
                sw(s7, t0, -8176);
                sw(zero, t0, -11136);
                sw(s1, t0, -11248);
                sw(s5, t0, -11232);
                sw(t8, t0, -11264);
                sync(ctx, 0);
                sync(ctx, 16);
                lw(a0, t0, -11264);
                a0 = a0 & 0x100;
                if (a0 != 0) {
                    // 0x0047d404
                    charge(ctx, 3);
                    sw(s7, t0, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x0047d410
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047d42c
                    charge(ctx, 1);
                    for (;;) {
                        // 0x0047d430
                        charge(ctx, 7);
                        lw(a0, t0, -11264);
                        a0 = a0 & 0x100;
                        if (a0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047d44c
                    charge(ctx, 1);
                }
                // 0x0047d450
                charge(ctx, 11);
                sw(s7, t0, -8176);
                sw(s4, t0, -11136);
                sw(s2, t0, -11248);
                sw(t7, t0, -11232);
                sw(t8, t0, -11264);
                sync(ctx, 0);
                sync(ctx, 16);
                lw(a0, t0, -11264);
                a0 = a0 & 0x100;
                if (a0 != 0) {
                    // 0x0047d47c
                    charge(ctx, 3);
                    sw(s7, t0, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x0047d488
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047d4a4
                    charge(ctx, 1);
                    for (;;) {
                        // 0x0047d4a8
                        charge(ctx, 7);
                        lw(a0, t0, -11264);
                        a0 = a0 & 0x100;
                        if (a0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047d4c4
                    charge(ctx, 1);
                }
                // 0x0047d4c8
                charge(ctx, 4);
                a2 = t6;
                a1 = t5;
                a0 = t4;
                a3 = 0;
                for (;;) {
                    // 0x0047d4d8
                    charge(ctx, 8);
                    lwc1(f0, a2, 0);
                    swc1(f0, v1, 0);
                    lwc1(f0, a2, 4);
                    swc1(f0, v1, 4);
                    lwc1(f0, a2, 0);
                    swc1(f0, v1, 8);
                    lwc1(f0, a2, 4);
                    swc1(f0, v1, 12);
                    for (;;) {
                        // 0x0047d4f8
                        charge(ctx, 7);
                        di(ctx);
                        sync(ctx, 16);
                        mfc0(t2, 12);
                        t2 = t2 & t3;
                        if (t2 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047d514
                    charge(ctx, 70);
                    lqc2(vf1, v1, 0);
                    lqc2(vf20, a1, 0);
                    lqc2(vf27, a1, 16);
                    vabs(0xC, vf7, vf1);  // vabs.xy
                    vadda_bc(0xF, vf0, vf10, 0);  // vaddax.xyzw
                    vmsub_bc(0xC, vf7, vf7, vf0, 3);  // vmsubw.xy
                    vadda_bc(0xE, vf0, vf10, 1);  // vadday.xyz
                    vadda_bc(0x1, vf0, vf10, 2);  // vaddaz.w
                    vmsub_bc(0x3, vf2, vf1, vf0, 3);  // vmsubw.zw
                    vadda_bc(0xE, vf0, vf11, 0);  // vaddax.xyz
                    vadda_bc(0x1, vf0, vf11, 1);  // vadday.w
                    vmsub_bc(0x3, vf3, vf1, vf0, 3);  // vmsubw.zw
                    vmini(0x3, vf2, vf1, vf2);  // vmini.zw
                    vmax(0x3, vf7, vf2, vf3);  // vmax.zw
                    vmul(0xF, vf2, vf7, vf7);  // vmul.xyzw
                    vmul_bc(0xF, vf6, vf7, vf11, 2);  // vmulz.xyzw
                    vmul_bc(0xF, vf4, vf7, vf12, 0);  // vmulx.xyzw
                    vmul_bc(0xF, vf5, vf7, vf12, 1);  // vmuly.xyzw
                    vmul(0xF, vf3, vf2, vf2);  // vmul.xyzw
                    vmul(0xF, vf6, vf6, vf2);  // vmul.xyzw
                    vmula(0xF, vf4, vf2);  // vmula.xyzw
                    vmul_bc(0xF, vf4, vf7, vf12, 2);  // vmulz.xyzw
                    vmul(0xF, vf2, vf3, vf3);  // vmul.xyzw
                    vmadda(0xF, vf6, vf3);  // vmadda.xyzw
                    vmadda(0xF, vf5, vf3);  // vmadda.xyzw
                    vmadda_bc(0xF, vf7, vf13, 0);  // vmaddax.xyzw
                    vmadd(0xF, vf7, vf4, vf2);  // vmadd.xyzw
                    vmul_bc(0xE, vf2, vf8, vf7, 0);  // vmulx.xyz
                    vmul_bc(0xE, vf3, vf16, vf7, 2);  // vmulz.xyz
                    vmul_bc(0xE, vf4, vf9, vf7, 2);  // vmulz.xyz
                    vmul_bc(0xE, vf5, vf17, vf7, 0);  // vmulx.xyz
                    vsub(0xF, vf18, vf2, vf3);  // vsub.xyzw
                    vadd(0xF, vf19, vf4, vf5);  // vadd.xyzw
                    vmul_bc(0xE, vf2, vf8, vf7, 1);  // vmuly.xyz
                    vmul_bc(0xE, vf3, vf16, vf7, 3);  // vmulw.xyz
                    vmul_bc(0xE, vf4, vf9, vf7, 3);  // vmulw.xyz
                    vmul_bc(0xE, vf5, vf17, vf7, 1);  // vmuly.xyz
                    vsub(0xF, vf25, vf2, vf3);  // vsub.xyzw
                    vadd(0xF, vf26, vf4, vf5);  // vadd.xyzw
                    vsub(0xF, vf21, vf20, vf18);  // vsub.xyzw
                    vadd(0xF, vf22, vf20, vf18);  // vadd.xyzw
                    vadd(0xF, vf23, vf20, vf18);  // vadd.xyzw
                    vsub(0xF, vf24, vf20, vf18);  // vsub.xyzw
                    vsub(0xF, vf21, vf21, vf19);  // vsub.xyzw
                    vsub(0xF, vf22, vf22, vf19);  // vsub.xyzw
                    vadd(0xF, vf23, vf23, vf19);  // vadd.xyzw
                    vadd(0xF, vf24, vf24, vf19);  // vadd.xyzw
                    vsub(0xF, vf28, vf27, vf25);  // vsub.xyzw
                    vadd(0xF, vf29, vf27, vf25);  // vadd.xyzw
                    vadd(0xF, vf30, vf27, vf25);  // vadd.xyzw
                    vsub(0xF, vf31, vf27, vf25);  // vsub.xyzw
                    vsub(0xF, vf28, vf28, vf26);  // vsub.xyzw
                    vsub(0xF, vf29, vf29, vf26);  // vsub.xyzw
                    vadd(0xF, vf30, vf30, vf26);  // vadd.xyzw
                    vadd(0xF, vf31, vf31, vf26);  // vadd.xyzw
                    sqc2(vf21, a0, 0);
                    sqc2(vf22, a0, 16);
                    sqc2(vf23, a0, 32);
                    sqc2(vf24, a0, 48);
                    sqc2(vf28, a0, 64);
                    sqc2(vf29, a0, 80);
                    sqc2(vf30, a0, 96);
                    sqc2(vf31, a0, 112);
                    ei(ctx);
                    a3 = addiu(a3, 2);
                    t2 = slti(a3, 192);
                    a1 = addiu(a1, 32);
                    a2 = addiu(a2, 8);
                    a0 = addiu(a0, 128);
                    if (t2 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0047d62c
                charge(ctx, 4);
                lw(a0, t0, -12288);
                a0 = a0 & 0x100;
                if (a0 != 0) {
                    // 0x0047d63c
                    charge(ctx, 3);
                    sw(t8, t0, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x0047d648
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047d664
                    charge(ctx, 1);
                }
                // 0x0047d668
                charge(ctx, 4);
                lw(a0, t0, -11264);
                a0 = a0 & 0x100;
                if (a0 != 0) {
                    // 0x0047d678
                    charge(ctx, 4);
                    sw(s7, t0, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x0047d688
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047d6a4
                    charge(ctx, 1);
                    for (;;) {
                        // 0x0047d6a8
                        charge(ctx, 7);
                        lw(a0, t0, -11264);
                        a0 = a0 & 0x100;
                        if (a0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047d6c4
                    charge(ctx, 1);
                }
                // 0x0047d6c8
                charge(ctx, 13);
                sw(t8, t0, -8176);
                sw(t1, t0, -12160);
                sw(s0, t0, -12272);
                sw(s4, t0, -12256);
                sw(t8, t0, -12288);
                sync(ctx, 0);
                sync(ctx, 16);
                s3 = addiu(s3, -192);
                s2 = addiu(s2, 3072);
                at = slti(s3, 192);
                s0 = addiu(s0, 12288);
                s1 = addiu(s1, 768);
                if (at != 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0047d6fc
            charge(ctx, 1);
        }
        // 0x0047d700
        charge(ctx, 3);
        at = slti(s3, 4);
        if (at == 0) {
            // 0x0047d70c
            charge(ctx, 2);
            a0 = sra(s3, 2);
            if (i64(s3) < 0) {
                // 0x0047d714
                charge(ctx, 2);
                a0 = addiu(s3, 3);
                a0 = sra(a0, 2);
            }
            // 0x0047d71c
            charge(ctx, 6);
            a2 = sll(a0, 2);
            a0 = 0x10010000;
            lw(a1, a0, -12288);  // 0x1000D000 D8 fromSPR CHCR
            a1 = a1 & 0x100;
            if (a1 != 0) {
                // 0x0047d734
                charge(ctx, 4);
                a1 = 256;
                sw(a1, a0, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x0047d744
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x0047d760
            charge(ctx, 5);
            a0 = 0x10010000;
            lw(a1, a0, -11264);  // 0x1000D400 D9 toSPR CHCR
            a1 = a1 & 0x100;
            if (a1 != 0) {
                // 0x0047d774
                charge(ctx, 4);
                a1 = 512;
                sw(a1, a0, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x0047d784
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0047d7a0
                charge(ctx, 1);
                a0 = 0x10010000;
                for (;;) {
                    // 0x0047d7a4
                    charge(ctx, 7);
                    lw(a1, a0, -11264);
                    a1 = a1 & 0x100;
                    if (a1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x0047d7c0
            charge(ctx, 7);
            a1 = 512;
            a0 = 0x10010000;
            a3 = sra(a2, 2);
            sw(a1, a0, -8176);  // 0x1000E010 D_STAT
            sw(zero, a0, -11136);  // 0x1000D480 D9 toSPR SADR
            sw(s1, a0, -11248);  // 0x1000D410 D9 toSPR MADR
            if (i64(a2) < 0) {
                // 0x0047d7dc
                charge(ctx, 2);
                a0 = addiu(a2, 3);
                a3 = sra(a0, 2);
            }
            // 0x0047d7e4
            charge(ctx, 10);
            a0 = 0x10010000;
            a1 = 256;
            sw(a3, a0, -11232);  // 0x1000D420 D9 toSPR QWC
            sw(a1, a0, -11264);  // 0x1000D400 D9 toSPR CHCR
            sync(ctx, 0);
            sync(ctx, 16);
            lw(a1, a0, -11264);  // 0x1000D400 D9 toSPR CHCR
            a1 = a1 & 0x100;
            if (a1 != 0) {
                // 0x0047d80c
                charge(ctx, 4);
                a1 = 512;
                sw(a1, a0, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x0047d81c
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0047d838
                charge(ctx, 1);
                a0 = 0x10010000;
                for (;;) {
                    // 0x0047d83c
                    charge(ctx, 7);
                    lw(a1, a0, -11264);
                    a1 = a1 & 0x100;
                    if (a1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x0047d858
            charge(ctx, 15);
            t0 = sll(a3, 4);
            a3 = 512;
            a0 = 0x10010000;
            sw(a3, a0, -8176);  // 0x1000E010 D_STAT
            a1 = 256;
            sw(t0, a0, -11136);  // 0x1000D480 D9 toSPR SADR
            sw(s2, a0, -11248);  // 0x1000D410 D9 toSPR MADR
            sw(a2, a0, -11232);  // 0x1000D420 D9 toSPR QWC
            sw(a1, a0, -11264);  // 0x1000D400 D9 toSPR CHCR
            sync(ctx, 0);
            sync(ctx, 16);
            lw(a1, a0, -11264);  // 0x1000D400 D9 toSPR CHCR
            a1 = a1 & 0x100;
            if (a1 != 0) {
                // 0x0047d894
                charge(ctx, 3);
                sw(a3, a0, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x0047d8a0
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0047d8bc
                charge(ctx, 1);
                a0 = 0x10010000;
                for (;;) {
                    // 0x0047d8c0
                    charge(ctx, 7);
                    lw(a1, a0, -11264);
                    a1 = a1 & 0x100;
                    if (a1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0047d8dc
                charge(ctx, 1);
            }
            // 0x0047d8e0
            charge(ctx, 3);
            t2 = 0x70000000;
            a0 = sra(a2, 2);
            if (i64(a2) < 0) {
                // 0x0047d8ec
                charge(ctx, 2);
                a0 = addiu(a2, 3);
                a0 = sra(a0, 2);
            }
            // 0x0047d8f4
            charge(ctx, 8);
            a0 = addu(a2, a0);
            a3 = 0x70000000;
            a0 = sll(a0, 4);
            at = slt(0, a2);
            a1 = t0 | a3;
            a0 = a0 | a3;
            t1 = 0;
            if (at != 0) {
                // 0x0047d914
                charge(ctx, 1);
                t0 = 0x10000;
                for (;;) {
                    // 0x0047d918
                    charge(ctx, 8);
                    lwc1(f0, t2, 0);
                    swc1(f0, v1, 0);
                    lwc1(f0, t2, 4);
                    swc1(f0, v1, 4);
                    lwc1(f0, t2, 0);
                    swc1(f0, v1, 8);
                    lwc1(f0, t2, 4);
                    swc1(f0, v1, 12);
                    for (;;) {
                        // 0x0047d938
                        charge(ctx, 7);
                        di(ctx);
                        sync(ctx, 16);
                        mfc0(a3, 12);
                        a3 = a3 & t0;
                        if (a3 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047d954
                    charge(ctx, 70);
                    lqc2(vf1, v1, 0);
                    lqc2(vf20, a1, 0);
                    lqc2(vf27, a1, 16);
                    vabs(0xC, vf7, vf1);  // vabs.xy
                    vadda_bc(0xF, vf0, vf10, 0);  // vaddax.xyzw
                    vmsub_bc(0xC, vf7, vf7, vf0, 3);  // vmsubw.xy
                    vadda_bc(0xE, vf0, vf10, 1);  // vadday.xyz
                    vadda_bc(0x1, vf0, vf10, 2);  // vaddaz.w
                    vmsub_bc(0x3, vf2, vf1, vf0, 3);  // vmsubw.zw
                    vadda_bc(0xE, vf0, vf11, 0);  // vaddax.xyz
                    vadda_bc(0x1, vf0, vf11, 1);  // vadday.w
                    vmsub_bc(0x3, vf3, vf1, vf0, 3);  // vmsubw.zw
                    vmini(0x3, vf2, vf1, vf2);  // vmini.zw
                    vmax(0x3, vf7, vf2, vf3);  // vmax.zw
                    vmul(0xF, vf2, vf7, vf7);  // vmul.xyzw
                    vmul_bc(0xF, vf6, vf7, vf11, 2);  // vmulz.xyzw
                    vmul_bc(0xF, vf4, vf7, vf12, 0);  // vmulx.xyzw
                    vmul_bc(0xF, vf5, vf7, vf12, 1);  // vmuly.xyzw
                    vmul(0xF, vf3, vf2, vf2);  // vmul.xyzw
                    vmul(0xF, vf6, vf6, vf2);  // vmul.xyzw
                    vmula(0xF, vf4, vf2);  // vmula.xyzw
                    vmul_bc(0xF, vf4, vf7, vf12, 2);  // vmulz.xyzw
                    vmul(0xF, vf2, vf3, vf3);  // vmul.xyzw
                    vmadda(0xF, vf6, vf3);  // vmadda.xyzw
                    vmadda(0xF, vf5, vf3);  // vmadda.xyzw
                    vmadda_bc(0xF, vf7, vf13, 0);  // vmaddax.xyzw
                    vmadd(0xF, vf7, vf4, vf2);  // vmadd.xyzw
                    vmul_bc(0xE, vf2, vf8, vf7, 0);  // vmulx.xyz
                    vmul_bc(0xE, vf3, vf16, vf7, 2);  // vmulz.xyz
                    vmul_bc(0xE, vf4, vf9, vf7, 2);  // vmulz.xyz
                    vmul_bc(0xE, vf5, vf17, vf7, 0);  // vmulx.xyz
                    vsub(0xF, vf18, vf2, vf3);  // vsub.xyzw
                    vadd(0xF, vf19, vf4, vf5);  // vadd.xyzw
                    vmul_bc(0xE, vf2, vf8, vf7, 1);  // vmuly.xyz
                    vmul_bc(0xE, vf3, vf16, vf7, 3);  // vmulw.xyz
                    vmul_bc(0xE, vf4, vf9, vf7, 3);  // vmulw.xyz
                    vmul_bc(0xE, vf5, vf17, vf7, 1);  // vmuly.xyz
                    vsub(0xF, vf25, vf2, vf3);  // vsub.xyzw
                    vadd(0xF, vf26, vf4, vf5);  // vadd.xyzw
                    vsub(0xF, vf21, vf20, vf18);  // vsub.xyzw
                    vadd(0xF, vf22, vf20, vf18);  // vadd.xyzw
                    vadd(0xF, vf23, vf20, vf18);  // vadd.xyzw
                    vsub(0xF, vf24, vf20, vf18);  // vsub.xyzw
                    vsub(0xF, vf21, vf21, vf19);  // vsub.xyzw
                    vsub(0xF, vf22, vf22, vf19);  // vsub.xyzw
                    vadd(0xF, vf23, vf23, vf19);  // vadd.xyzw
                    vadd(0xF, vf24, vf24, vf19);  // vadd.xyzw
                    vsub(0xF, vf28, vf27, vf25);  // vsub.xyzw
                    vadd(0xF, vf29, vf27, vf25);  // vadd.xyzw
                    vadd(0xF, vf30, vf27, vf25);  // vadd.xyzw
                    vsub(0xF, vf31, vf27, vf25);  // vsub.xyzw
                    vsub(0xF, vf28, vf28, vf26);  // vsub.xyzw
                    vsub(0xF, vf29, vf29, vf26);  // vsub.xyzw
                    vadd(0xF, vf30, vf30, vf26);  // vadd.xyzw
                    vadd(0xF, vf31, vf31, vf26);  // vadd.xyzw
                    sqc2(vf21, a0, 0);
                    sqc2(vf22, a0, 16);
                    sqc2(vf23, a0, 32);
                    sqc2(vf24, a0, 48);
                    sqc2(vf28, a0, 64);
                    sqc2(vf29, a0, 80);
                    sqc2(vf30, a0, 96);
                    sqc2(vf31, a0, 112);
                    ei(ctx);
                    t1 = addiu(t1, 2);
                    a3 = slt(t1, a2);
                    a1 = addiu(a1, 32);
                    t2 = addiu(t2, 8);
                    a0 = addiu(a0, 128);
                    if (a3 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0047da6c
                charge(ctx, 1);
            }
            // 0x0047da70
            charge(ctx, 5);
            v1 = 0x10010000;
            lw(a0, v1, -12288);  // 0x1000D000 D8 fromSPR CHCR
            a0 = a0 & 0x100;
            if (a0 != 0) {
                // 0x0047da84
                charge(ctx, 4);
                a0 = 256;
                sw(a0, v1, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x0047da94
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x0047dab0
            charge(ctx, 5);
            v1 = 0x10010000;
            lw(a0, v1, -11264);  // 0x1000D400 D9 toSPR CHCR
            a0 = a0 & 0x100;
            if (a0 != 0) {
                // 0x0047dac4
                charge(ctx, 4);
                a0 = 512;
                sw(a0, v1, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x0047dad4
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0047daf0
                charge(ctx, 1);
                v1 = 0x10010000;
                for (;;) {
                    // 0x0047daf4
                    charge(ctx, 7);
                    lw(a0, v1, -11264);
                    a0 = a0 & 0x100;
                    if (a0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x0047db10
            charge(ctx, 5);
            a0 = 256;
            v1 = 0x10010000;
            a3 = sra(a2, 2);
            sw(a0, v1, -8176);  // 0x1000E010 D_STAT
            if (i64(a2) < 0) {
                // 0x0047db24
                charge(ctx, 2);
                v1 = addiu(a2, 3);
                a3 = sra(v1, 2);
            }
            // 0x0047db2c
            charge(ctx, 18);
            a0 = addu(a2, a3);
            v1 = 0x10010000;
            a0 = sll(a0, 4);
            a1 = sll(a2, 2);
            sw(a0, v1, -12160);  // 0x1000D080 D8 fromSPR SADR
            sw(s0, v1, -12272);  // 0x1000D010 D8 fromSPR MADR
            a0 = 256;
            sw(a1, v1, -12256);  // 0x1000D020 D8 fromSPR QWC
            sw(a0, v1, -12288);  // 0x1000D000 D8 fromSPR CHCR
            sync(ctx, 0);
            sync(ctx, 16);
            v1 = sll(a3, 4);
            a0 = sll(a1, 4);
            s1 = addu(s1, v1);
            s0 = addu(s0, a0);
            v1 = sll(a2, 4);
            s3 = subu(s3, a2);
            s2 = addu(s2, v1);
        }
        // 0x0047db74
        charge(ctx, 3);
        at = slt(0, s3);
        a3 = 0;
        if (at != 0) {
            // 0x0047db80
            charge(ctx, 3);
            a2 = addiu(sp, 0xC8);
            a0 = sll(s6, 2);
            a1 = addiu(sp, 0xC0);
            for (;;) {
                // 0x0047db8c
                charge(ctx, 55);
                lwc1(f0, s1, 0);
                swc1(f0, sp, 0xC0);
                swc1(f0, a2, 0);
                lqc2(vf1, a1, 0);
                lqc2(vf20, s2, 0);
                vabs(0xC, vf7, vf1);  // vabs.xy
                vadda_bc(0xF, vf0, vf10, 0);  // vaddax.xyzw
                vmsub_bc(0xC, vf7, vf7, vf0, 3);  // vmsubw.xy
                vadda_bc(0xE, vf0, vf10, 1);  // vadday.xyz
                vadda_bc(0x1, vf0, vf10, 2);  // vaddaz.w
                vmsub_bc(0x3, vf2, vf1, vf0, 3);  // vmsubw.zw
                vadda_bc(0xE, vf0, vf11, 0);  // vaddax.xyz
                vadda_bc(0x1, vf0, vf11, 1);  // vadday.w
                vmsub_bc(0x3, vf3, vf1, vf0, 3);  // vmsubw.zw
                vmini(0x3, vf2, vf1, vf2);  // vmini.zw
                vmax(0x3, vf7, vf2, vf3);  // vmax.zw
                vmul(0xF, vf2, vf7, vf7);  // vmul.xyzw
                vmul_bc(0xF, vf6, vf7, vf11, 2);  // vmulz.xyzw
                vmul_bc(0xF, vf4, vf7, vf12, 0);  // vmulx.xyzw
                vmul_bc(0xF, vf5, vf7, vf12, 1);  // vmuly.xyzw
                vmul(0xF, vf3, vf2, vf2);  // vmul.xyzw
                vmul(0xF, vf6, vf6, vf2);  // vmul.xyzw
                vmula(0xF, vf4, vf2);  // vmula.xyzw
                vmul_bc(0xF, vf4, vf7, vf12, 2);  // vmulz.xyzw
                vmul(0xF, vf2, vf3, vf3);  // vmul.xyzw
                vmadda(0xF, vf6, vf3);  // vmadda.xyzw
                vmadda(0xF, vf5, vf3);  // vmadda.xyzw
                vmadda_bc(0xF, vf7, vf13, 0);  // vmaddax.xyzw
                vmadd(0xF, vf7, vf4, vf2);  // vmadd.xyzw
                vmul_bc(0xE, vf2, vf8, vf7, 0);  // vmulx.xyz
                vmul_bc(0xE, vf3, vf16, vf7, 2);  // vmulz.xyz
                vmul_bc(0xE, vf4, vf9, vf7, 2);  // vmulz.xyz
                vmul_bc(0xE, vf5, vf17, vf7, 0);  // vmulx.xyz
                vsub(0xF, vf18, vf2, vf3);  // vsub.xyzw
                vadd(0xF, vf19, vf4, vf5);  // vadd.xyzw
                vsub(0xF, vf21, vf20, vf18);  // vsub.xyzw
                vadd(0xF, vf22, vf20, vf18);  // vadd.xyzw
                vadd(0xF, vf23, vf20, vf18);  // vadd.xyzw
                vsub(0xF, vf24, vf20, vf18);  // vsub.xyzw
                vsub(0xF, vf21, vf21, vf19);  // vsub.xyzw
                vsub(0xF, vf22, vf22, vf19);  // vsub.xyzw
                vadd(0xF, vf23, vf23, vf19);  // vadd.xyzw
                vadd(0xF, vf24, vf24, vf19);  // vadd.xyzw
                sqc2(vf21, s0, 0);
                sqc2(vf22, s0, 16);
                sqc2(vf23, s0, 32);
                sqc2(vf24, s0, 48);
                ei(ctx);
                a3 = addiu(a3, 1);
                lq(v1, sp, 0xB0);
                s2 = addu(s2, fp);
                s1 = addu(s1, v1);
                v1 = slt(a3, s3);
                s0 = addu(s0, a0);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0047dc68
            charge(ctx, 2);
        }
    }
    // 0x0047dde8 (the shared epilogue, written out on this path)
    charge(ctx, 15);
    ld(ra, sp, 0xA0);
    lq(fp, sp, 0x90);
    lwc1(f22, sp, 0x8);
    lq(s7, sp, 0x80);
    lwc1(f21, sp, 0x4);
    lq(s6, sp, 0x70);
    lwc1(f20, sp, 0x0);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0xD0);
}

// 0x0047DE30 sub_47DE30 -- 2984 bytes; frame 0xE0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Scratchpad DMA kernel with a matrix block copied to SPR 0x3F50 (memcpy).
void sub_47DE30(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    Vf vf1{ctx, 1}, vf2{ctx, 2}, vf3{ctx, 3}, vf4{ctx, 4}, vf5{ctx, 5}, vf6{ctx, 6}, vf7{ctx, 7}, vf8{ctx, 8}, vf9{ctx, 9}, vf10{ctx, 10}, vf11{ctx, 11}, vf12{ctx, 12}, vf13{ctx, 13}, vf14{ctx, 14}, vf15{ctx, 15}, vf16{ctx, 16}, vf17{ctx, 17}, vf18{ctx, 18}, vf19{ctx, 19}, vf20{ctx, 20}, vf21{ctx, 21}, vf22{ctx, 22}, vf23{ctx, 23}, vf24{ctx, 24}, vf25{ctx, 25}, vf26{ctx, 26}, vf27{ctx, 27}, vf28{ctx, 28}, vf29{ctx, 29}, vf30{ctx, 30}, vf31{ctx, 31};
    // 0x0047de30
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0xE0);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a1;
    sq(s3, sp, 0x30);
    s4 = a2;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s6, t0, 8);
    lw(fp, a0, 4);
    lw(s2, t0, 4);
    lw(s1, t0, 28);
    lw(s7, t0, 32);
    lw(s0, a0, 0);
    s3 = a3;
    if (s6 != fp) {
        // 0x0047e890
        charge(ctx, 8);
        a0 = addiu(sp, 0xC0);
        a2 = 12;
        jal(ctx, 0x47E894u, gen::fn_memcpy_00521250);
        a1 = s4;
        a0 = addiu(sp, 0xB0);
        a2 = 12;
        jal(ctx, 0x47E8A4u, gen::fn_memcpy_00521250);
        v1 = 0x10000;
        for (;;) {
            // 0x0047e8b0
            charge(ctx, 7);
            di(ctx);
            sync(ctx, 16);
            mfc0(a0, 12);
            a0 = a0 & v1;
            if (a0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0047e8cc
        charge(ctx, 16);
        v1 = 0x3F000000;
        a1 = addiu(sp, 0xC0);
        mtc1(v1, f0);
        a0 = addiu(sp, 0xB0);
        mfc1(v1, f0);
        ctc2(v1, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        lqc2(vf1, a1, 0);
        lqc2(vf2, a0, 0);
        vmuli(0xF, vf1, vf1);  // vmuli.xyzw
        vmuli(0xF, vf2, vf2);  // vmuli.xyzw
        ei(ctx);
        at = slt(0, s3);
        t0 = 0;
        if (at != 0) {
            // 0x0047e90c
            charge(ctx, 4);
            a3 = addiu(sp, 0xA4);
            a0 = sll(fp, 2);
            a1 = addiu(sp, 0xA0);
            a2 = 0x10000;
            for (;;) {
                // 0x0047e91c
                charge(ctx, 5);
                lwc1(f1, s1, 0);
                lwc1(f0, s1, 4);
                swc1(f1, sp, 0xA0);
                swc1(f0, a3, 0);
                for (;;) {
                    // 0x0047e930
                    charge(ctx, 7);
                    di(ctx);
                    sync(ctx, 16);
                    mfc0(v1, 12);
                    v1 = v1 & a2;
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0047e94c
                charge(ctx, 23);
                lqc2(vf3, a1, 0);
                vmul_bc(0xE, vf4, vf1, vf3, 0);  // vmulx.xyz
                vmul_bc(0xE, vf5, vf2, vf3, 1);  // vmuly.xyz
                lqc2(vf6, s2, 0);
                vsub(0xE, vf7, vf6, vf4);  // vsub.xyz
                vadd(0xE, vf8, vf6, vf4);  // vadd.xyz
                vadd(0xE, vf9, vf6, vf4);  // vadd.xyz
                vsub(0xE, vf10, vf6, vf4);  // vsub.xyz
                vsub(0xE, vf7, vf7, vf5);  // vsub.xyz
                vsub(0xE, vf8, vf8, vf5);  // vsub.xyz
                vadd(0xE, vf9, vf9, vf5);  // vadd.xyz
                vadd(0xE, vf10, vf10, vf5);  // vadd.xyz
                sqc2(vf7, s0, 0);
                sqc2(vf8, s0, 16);
                sqc2(vf9, s0, 32);
                sqc2(vf10, s0, 48);
                ei(ctx);
                t0 = addiu(t0, 1);
                v1 = slt(t0, s3);
                s1 = addu(s1, s7);
                s0 = addu(s0, a0);
                s2 = addu(s2, s6);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
    } else {
        // 0x0047de84
        charge(ctx, 7);
        a0 = 0;
        jal(ctx, 0x47DE84u, gen::fn__sceFlushCache_005033e0);
        v1 = 0x10010000;
        lw(a0, v1, -12288);  // 0x1000D000 D8 fromSPR CHCR
        a0 = a0 & 0x100;
        if (a0 != 0) {
            // 0x0047dea0
            charge(ctx, 4);
            a0 = 256;
            sw(a0, v1, -8160);
            sync(ctx, 0);
            sync(ctx, 16);
            for (;;) {
                // 0x0047deb0
                charge(ctx, 7);
                if (cop0_cond(ctx)) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x0047decc
        charge(ctx, 5);
        v1 = 0x10010000;
        lw(a0, v1, -11264);  // 0x1000D400 D9 toSPR CHCR
        a0 = a0 & 0x100;
        if (a0 != 0) {
            // 0x0047dee0
            charge(ctx, 4);
            a0 = 512;
            sw(a0, v1, -8160);
            sync(ctx, 0);
            sync(ctx, 16);
            for (;;) {
                // 0x0047def0
                charge(ctx, 7);
                if (cop0_cond(ctx)) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0047df0c
            charge(ctx, 1);
            v1 = 0x10010000;
            for (;;) {
                // 0x0047df10
                charge(ctx, 7);
                lw(a0, v1, -11264);
                a0 = a0 & 0x100;
                if (a0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0047df2c
            charge(ctx, 1);
        }
        // 0x0047df30
        charge(ctx, 16);
        v1 = 0x70000000;
        lwc1(f2, s5, 0);
        a1 = v1 | 0x3F50;
        lwc1(f1, s5, 4);
        a0 = v1 | 0x3F60;
        lwc1(f0, s5, 8);
        v1 = 0x10000;
        swc1(f2, a1, 0);  // 0x70003F50 SPR+0x3F50
        swc1(f1, a1, 4);  // 0x70003F54 SPR+0x3F54
        swc1(f0, a1, 8);  // 0x70003F58 SPR+0x3F58
        lwc1(f2, s4, 0);
        lwc1(f1, s4, 4);
        lwc1(f0, s4, 8);
        swc1(f2, a0, 0);  // 0x70003F60 SPR+0x3F60
        swc1(f1, a0, 4);  // 0x70003F64 SPR+0x3F64
        swc1(f0, a0, 8);  // 0x70003F68 SPR+0x3F68
        for (;;) {
            // 0x0047df70
            charge(ctx, 7);
            di(ctx);
            sync(ctx, 16);
            mfc0(a2, 12);
            a2 = a2 & v1;
            if (a2 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0047df8c
        charge(ctx, 14);
        v1 = 0x3F000000;
        mtc1(v1, f0);
        mfc1(v1, f0);
        ctc2(v1, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        lqc2(vf1, a1, 0);
        lqc2(vf2, a0, 0);
        vmuli(0xF, vf1, vf1);  // vmuli.xyzw
        vmuli(0xF, vf2, vf2);  // vmuli.xyzw
        ei(ctx);
        v1 = slti(s3, 184);
        if (v1 == 0) {
            // 0x0047dfc4
            charge(ctx, 12);
            t6 = 0x70000000;
            a3 = 0x10010000;
            t3 = 0x10000;
            t9 = 256;
            t8 = 512;
            s5 = 92;
            s4 = 1472;
            t7 = 184;
            t5 = t6 | 0x5C0;
            t4 = t6 | 0x1140;
            t1 = 4416;
            t0 = 736;
            for (;;) {
                // 0x0047dff4
                charge(ctx, 4);
                lw(v1, a3, -12288);
                v1 = v1 & 0x100;
                if (v1 != 0) {
                    // 0x0047e004
                    charge(ctx, 3);
                    sw(t9, a3, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x0047e010
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047e02c
                    charge(ctx, 1);
                }
                // 0x0047e030
                charge(ctx, 4);
                lw(v1, a3, -11264);
                v1 = v1 & 0x100;
                if (v1 != 0) {
                    // 0x0047e040
                    charge(ctx, 4);
                    sw(t8, a3, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x0047e050
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047e06c
                    charge(ctx, 1);
                    for (;;) {
                        // 0x0047e070
                        charge(ctx, 7);
                        lw(v1, a3, -11264);
                        v1 = v1 & 0x100;
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047e08c
                    charge(ctx, 1);
                }
                // 0x0047e090
                charge(ctx, 11);
                sw(t8, a3, -8176);
                sw(zero, a3, -11136);
                sw(s1, a3, -11248);
                sw(s5, a3, -11232);
                sw(t9, a3, -11264);
                sync(ctx, 0);
                sync(ctx, 16);
                lw(v1, a3, -11264);
                v1 = v1 & 0x100;
                if (v1 != 0) {
                    // 0x0047e0bc
                    charge(ctx, 3);
                    sw(t8, a3, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x0047e0c8
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047e0e4
                    charge(ctx, 1);
                    for (;;) {
                        // 0x0047e0e8
                        charge(ctx, 7);
                        lw(v1, a3, -11264);
                        v1 = v1 & 0x100;
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047e104
                    charge(ctx, 1);
                }
                // 0x0047e108
                charge(ctx, 11);
                sw(t8, a3, -8176);
                sw(s4, a3, -11136);
                sw(s2, a3, -11248);
                sw(t7, a3, -11232);
                sw(t9, a3, -11264);
                sync(ctx, 0);
                sync(ctx, 16);
                lw(v1, a3, -11264);
                v1 = v1 & 0x100;
                if (v1 != 0) {
                    // 0x0047e134
                    charge(ctx, 3);
                    sw(t8, a3, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x0047e140
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047e15c
                    charge(ctx, 1);
                    for (;;) {
                        // 0x0047e160
                        charge(ctx, 7);
                        lw(v1, a3, -11264);
                        v1 = v1 & 0x100;
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047e17c
                    charge(ctx, 1);
                }
                // 0x0047e180
                charge(ctx, 4);
                a1 = t6;
                a0 = t5;
                v1 = t4;
                a2 = 0;
                for (;;) {
                    // 0x0047e190
                    charge(ctx, 7);
                    di(ctx);
                    sync(ctx, 16);
                    mfc0(t2, 12);
                    t2 = t2 & t3;
                    if (t2 != 0) {
                        backedge(ctx);
                        continue;
                    }
                    // 0x0047e1ac
                    charge(ctx, 69);
                    lqc2(vf3, a1, 0);
                    vmul_bc(0xE, vf4, vf1, vf3, 0);  // vmulx.xyz
                    vmul_bc(0xE, vf5, vf2, vf3, 1);  // vmuly.xyz
                    vmul_bc(0xE, vf11, vf1, vf3, 2);  // vmulz.xyz
                    vmul_bc(0xE, vf12, vf2, vf3, 3);  // vmulw.xyz
                    lqc2(vf6, a0, 0);
                    lqc2(vf13, a0, 16);
                    lqc2(vf20, a0, 32);
                    lqc2(vf3, a1, 16);
                    lqc2(vf27, a0, 48);
                    vmul_bc(0xE, vf18, vf1, vf3, 0);  // vmulx.xyz
                    vmul_bc(0xE, vf19, vf2, vf3, 1);  // vmuly.xyz
                    vmul_bc(0xE, vf25, vf1, vf3, 2);  // vmulz.xyz
                    vmul_bc(0xE, vf26, vf2, vf3, 3);  // vmulw.xyz
                    vsub(0xE, vf7, vf6, vf4);  // vsub.xyz
                    vadd(0xE, vf8, vf6, vf4);  // vadd.xyz
                    vadd(0xE, vf9, vf6, vf4);  // vadd.xyz
                    vsub(0xE, vf10, vf6, vf4);  // vsub.xyz
                    vsub(0xE, vf7, vf7, vf5);  // vsub.xyz
                    vsub(0xE, vf8, vf8, vf5);  // vsub.xyz
                    vadd(0xE, vf9, vf9, vf5);  // vadd.xyz
                    vadd(0xE, vf10, vf10, vf5);  // vadd.xyz
                    vsub(0xE, vf14, vf13, vf11);  // vsub.xyz
                    vadd(0xE, vf15, vf13, vf11);  // vadd.xyz
                    vadd(0xE, vf16, vf13, vf11);  // vadd.xyz
                    vsub(0xE, vf17, vf13, vf11);  // vsub.xyz
                    vsub(0xE, vf14, vf14, vf12);  // vsub.xyz
                    vsub(0xE, vf15, vf15, vf12);  // vsub.xyz
                    vadd(0xE, vf16, vf16, vf12);  // vadd.xyz
                    vadd(0xE, vf17, vf17, vf12);  // vadd.xyz
                    vsub(0xE, vf21, vf20, vf18);  // vsub.xyz
                    vadd(0xE, vf22, vf20, vf18);  // vadd.xyz
                    vadd(0xE, vf23, vf20, vf18);  // vadd.xyz
                    vsub(0xE, vf24, vf20, vf18);  // vsub.xyz
                    vsub(0xE, vf21, vf21, vf19);  // vsub.xyz
                    vsub(0xE, vf22, vf22, vf19);  // vsub.xyz
                    vadd(0xE, vf23, vf23, vf19);  // vadd.xyz
                    vadd(0xE, vf24, vf24, vf19);  // vadd.xyz
                    vsub(0xE, vf28, vf27, vf25);  // vsub.xyz
                    vadd(0xE, vf29, vf27, vf25);  // vadd.xyz
                    vadd(0xE, vf30, vf27, vf25);  // vadd.xyz
                    vsub(0xE, vf31, vf27, vf25);  // vsub.xyz
                    vsub(0xE, vf28, vf28, vf26);  // vsub.xyz
                    vsub(0xE, vf29, vf29, vf26);  // vsub.xyz
                    vadd(0xE, vf30, vf30, vf26);  // vadd.xyz
                    vadd(0xE, vf31, vf31, vf26);  // vadd.xyz
                    sqc2(vf7, v1, 0);
                    sqc2(vf8, v1, 16);
                    sqc2(vf9, v1, 32);
                    sqc2(vf10, v1, 48);
                    sqc2(vf14, v1, 64);
                    sqc2(vf15, v1, 80);
                    sqc2(vf16, v1, 96);
                    sqc2(vf17, v1, 112);
                    sqc2(vf21, v1, 128);
                    sqc2(vf22, v1, 144);
                    sqc2(vf23, v1, 160);
                    sqc2(vf24, v1, 176);
                    sqc2(vf28, v1, 192);
                    sqc2(vf29, v1, 208);
                    sqc2(vf30, v1, 224);
                    sqc2(vf31, v1, 240);
                    ei(ctx);
                    a2 = addiu(a2, 4);
                    t2 = slti(a2, 184);
                    a1 = addiu(a1, 32);
                    v1 = addiu(v1, 256);
                    a0 = addiu(a0, 64);
                    if (t2 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0047e2c0
                charge(ctx, 4);
                lw(v1, a3, -12288);
                v1 = v1 & 0x100;
                if (v1 != 0) {
                    // 0x0047e2d0
                    charge(ctx, 4);
                    sw(t9, a3, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x0047e2e0
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047e2fc
                    charge(ctx, 1);
                }
                // 0x0047e300
                charge(ctx, 4);
                lw(v1, a3, -11264);
                v1 = v1 & 0x100;
                if (v1 != 0) {
                    // 0x0047e310
                    charge(ctx, 4);
                    sw(t8, a3, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x0047e320
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047e33c
                    charge(ctx, 1);
                    for (;;) {
                        // 0x0047e340
                        charge(ctx, 7);
                        lw(v1, a3, -11264);
                        v1 = v1 & 0x100;
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047e35c
                    charge(ctx, 1);
                }
                // 0x0047e360
                charge(ctx, 13);
                sw(t9, a3, -8176);
                sw(t1, a3, -12160);
                sw(s0, a3, -12272);
                sw(t0, a3, -12256);
                sw(t9, a3, -12288);
                sync(ctx, 0);
                sync(ctx, 16);
                s3 = addiu(s3, -184);
                s2 = addiu(s2, 2944);
                at = slti(s3, 184);
                s0 = addiu(s0, 11776);
                s1 = addiu(s1, 1472);
                if (at != 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0047e394
            charge(ctx, 1);
        }
        // 0x0047e398
        charge(ctx, 3);
        at = slti(s3, 4);
        if (at == 0) {
            // 0x0047e3a4
            charge(ctx, 2);
            v1 = sra(s3, 2);
            if (i64(s3) < 0) {
                // 0x0047e3ac
                charge(ctx, 2);
                v1 = addiu(s3, 3);
                v1 = sra(v1, 2);
            }
            // 0x0047e3b4
            charge(ctx, 6);
            a2 = sll(v1, 2);
            v1 = 0x10010000;
            lw(a0, v1, -12288);  // 0x1000D000 D8 fromSPR CHCR
            a0 = a0 & 0x100;
            if (a0 != 0) {
                // 0x0047e3cc
                charge(ctx, 4);
                a0 = 256;
                sw(a0, v1, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x0047e3dc
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x0047e3f8
            charge(ctx, 5);
            v1 = 0x10010000;
            lw(a0, v1, -11264);  // 0x1000D400 D9 toSPR CHCR
            a0 = a0 & 0x100;
            if (a0 != 0) {
                // 0x0047e40c
                charge(ctx, 4);
                a0 = 512;
                sw(a0, v1, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x0047e41c
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0047e438
                charge(ctx, 1);
                v1 = 0x10010000;
                for (;;) {
                    // 0x0047e43c
                    charge(ctx, 7);
                    lw(a0, v1, -11264);
                    a0 = a0 & 0x100;
                    if (a0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x0047e458
            charge(ctx, 7);
            a0 = 512;
            v1 = 0x10010000;
            a1 = sra(a2, 1);
            sw(a0, v1, -8176);  // 0x1000E010 D_STAT
            sw(zero, v1, -11136);  // 0x1000D480 D9 toSPR SADR
            sw(s1, v1, -11248);  // 0x1000D410 D9 toSPR MADR
            if (i64(a2) < 0) {
                // 0x0047e474
                charge(ctx, 2);
                v1 = addiu(a2, 1);
                a1 = sra(v1, 1);
            }
            // 0x0047e47c
            charge(ctx, 10);
            v1 = 0x10010000;
            a0 = 256;
            sw(a1, v1, -11232);  // 0x1000D420 D9 toSPR QWC
            sw(a0, v1, -11264);  // 0x1000D400 D9 toSPR CHCR
            sync(ctx, 0);
            sync(ctx, 16);
            lw(a0, v1, -11264);  // 0x1000D400 D9 toSPR CHCR
            a0 = a0 & 0x100;
            if (a0 != 0) {
                // 0x0047e4a4
                charge(ctx, 4);
                a0 = 512;
                sw(a0, v1, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x0047e4b4
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0047e4d0
                charge(ctx, 1);
                v1 = 0x10010000;
                for (;;) {
                    // 0x0047e4d4
                    charge(ctx, 7);
                    lw(a0, v1, -11264);
                    a0 = a0 & 0x100;
                    if (a0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x0047e4f0
            charge(ctx, 15);
            t0 = sll(a1, 4);
            a1 = 512;
            v1 = 0x10010000;
            sw(a1, v1, -8176);  // 0x1000E010 D_STAT
            a0 = 256;
            sw(t0, v1, -11136);  // 0x1000D480 D9 toSPR SADR
            sw(s2, v1, -11248);  // 0x1000D410 D9 toSPR MADR
            sw(a2, v1, -11232);  // 0x1000D420 D9 toSPR QWC
            sw(a0, v1, -11264);  // 0x1000D400 D9 toSPR CHCR
            sync(ctx, 0);
            sync(ctx, 16);
            lw(a0, v1, -11264);  // 0x1000D400 D9 toSPR CHCR
            a0 = a0 & 0x100;
            if (a0 != 0) {
                // 0x0047e52c
                charge(ctx, 3);
                sw(a1, v1, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x0047e538
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0047e554
                charge(ctx, 1);
                v1 = 0x10010000;
                for (;;) {
                    // 0x0047e558
                    charge(ctx, 7);
                    lw(a0, v1, -11264);
                    a0 = a0 & 0x100;
                    if (a0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0047e574
                charge(ctx, 1);
            }
            // 0x0047e578
            charge(ctx, 3);
            a1 = 0x70000000;
            v1 = sra(a2, 1);
            if (i64(a2) < 0) {
                // 0x0047e584
                charge(ctx, 2);
                v1 = addiu(a2, 1);
                v1 = sra(v1, 1);
            }
            // 0x0047e58c
            charge(ctx, 8);
            v1 = addu(a2, v1);
            a3 = 0x70000000;
            v1 = sll(v1, 4);
            at = slt(0, a2);
            a0 = t0 | a3;
            v1 = v1 | a3;
            t1 = 0;
            if (at != 0) {
                // 0x0047e5ac
                charge(ctx, 1);
                t0 = 0x10000;
                for (;;) {
                    // 0x0047e5b0
                    charge(ctx, 7);
                    di(ctx);
                    sync(ctx, 16);
                    mfc0(a3, 12);
                    a3 = a3 & t0;
                    if (a3 != 0) {
                        backedge(ctx);
                        continue;
                    }
                    // 0x0047e5cc
                    charge(ctx, 69);
                    lqc2(vf3, a1, 0);
                    vmul_bc(0xE, vf4, vf1, vf3, 0);  // vmulx.xyz
                    vmul_bc(0xE, vf5, vf2, vf3, 1);  // vmuly.xyz
                    vmul_bc(0xE, vf11, vf1, vf3, 2);  // vmulz.xyz
                    vmul_bc(0xE, vf12, vf2, vf3, 3);  // vmulw.xyz
                    lqc2(vf6, a0, 0);
                    lqc2(vf13, a0, 16);
                    lqc2(vf20, a0, 32);
                    lqc2(vf3, a1, 16);
                    lqc2(vf27, a0, 48);
                    vmul_bc(0xE, vf18, vf1, vf3, 0);  // vmulx.xyz
                    vmul_bc(0xE, vf19, vf2, vf3, 1);  // vmuly.xyz
                    vmul_bc(0xE, vf25, vf1, vf3, 2);  // vmulz.xyz
                    vmul_bc(0xE, vf26, vf2, vf3, 3);  // vmulw.xyz
                    vsub(0xE, vf7, vf6, vf4);  // vsub.xyz
                    vadd(0xE, vf8, vf6, vf4);  // vadd.xyz
                    vadd(0xE, vf9, vf6, vf4);  // vadd.xyz
                    vsub(0xE, vf10, vf6, vf4);  // vsub.xyz
                    vsub(0xE, vf7, vf7, vf5);  // vsub.xyz
                    vsub(0xE, vf8, vf8, vf5);  // vsub.xyz
                    vadd(0xE, vf9, vf9, vf5);  // vadd.xyz
                    vadd(0xE, vf10, vf10, vf5);  // vadd.xyz
                    vsub(0xE, vf14, vf13, vf11);  // vsub.xyz
                    vadd(0xE, vf15, vf13, vf11);  // vadd.xyz
                    vadd(0xE, vf16, vf13, vf11);  // vadd.xyz
                    vsub(0xE, vf17, vf13, vf11);  // vsub.xyz
                    vsub(0xE, vf14, vf14, vf12);  // vsub.xyz
                    vsub(0xE, vf15, vf15, vf12);  // vsub.xyz
                    vadd(0xE, vf16, vf16, vf12);  // vadd.xyz
                    vadd(0xE, vf17, vf17, vf12);  // vadd.xyz
                    vsub(0xE, vf21, vf20, vf18);  // vsub.xyz
                    vadd(0xE, vf22, vf20, vf18);  // vadd.xyz
                    vadd(0xE, vf23, vf20, vf18);  // vadd.xyz
                    vsub(0xE, vf24, vf20, vf18);  // vsub.xyz
                    vsub(0xE, vf21, vf21, vf19);  // vsub.xyz
                    vsub(0xE, vf22, vf22, vf19);  // vsub.xyz
                    vadd(0xE, vf23, vf23, vf19);  // vadd.xyz
                    vadd(0xE, vf24, vf24, vf19);  // vadd.xyz
                    vsub(0xE, vf28, vf27, vf25);  // vsub.xyz
                    vadd(0xE, vf29, vf27, vf25);  // vadd.xyz
                    vadd(0xE, vf30, vf27, vf25);  // vadd.xyz
                    vsub(0xE, vf31, vf27, vf25);  // vsub.xyz
                    vsub(0xE, vf28, vf28, vf26);  // vsub.xyz
                    vsub(0xE, vf29, vf29, vf26);  // vsub.xyz
                    vadd(0xE, vf30, vf30, vf26);  // vadd.xyz
                    vadd(0xE, vf31, vf31, vf26);  // vadd.xyz
                    sqc2(vf7, v1, 0);
                    sqc2(vf8, v1, 16);
                    sqc2(vf9, v1, 32);
                    sqc2(vf10, v1, 48);
                    sqc2(vf14, v1, 64);
                    sqc2(vf15, v1, 80);
                    sqc2(vf16, v1, 96);
                    sqc2(vf17, v1, 112);
                    sqc2(vf21, v1, 128);
                    sqc2(vf22, v1, 144);
                    sqc2(vf23, v1, 160);
                    sqc2(vf24, v1, 176);
                    sqc2(vf28, v1, 192);
                    sqc2(vf29, v1, 208);
                    sqc2(vf30, v1, 224);
                    sqc2(vf31, v1, 240);
                    ei(ctx);
                    t1 = addiu(t1, 4);
                    a3 = slt(t1, a2);
                    a1 = addiu(a1, 32);
                    v1 = addiu(v1, 256);
                    a0 = addiu(a0, 64);
                    if (a3 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x0047e6e0
            charge(ctx, 5);
            v1 = 0x10010000;
            lw(a0, v1, -12288);  // 0x1000D000 D8 fromSPR CHCR
            a0 = a0 & 0x100;
            if (a0 != 0) {
                // 0x0047e6f4
                charge(ctx, 4);
                a0 = 256;
                sw(a0, v1, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x0047e704
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x0047e720
            charge(ctx, 5);
            v1 = 0x10010000;
            lw(a0, v1, -11264);  // 0x1000D400 D9 toSPR CHCR
            a0 = a0 & 0x100;
            if (a0 != 0) {
                // 0x0047e734
                charge(ctx, 4);
                a0 = 512;
                sw(a0, v1, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x0047e744
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0047e760
                charge(ctx, 1);
                v1 = 0x10010000;
                for (;;) {
                    // 0x0047e764
                    charge(ctx, 7);
                    lw(a0, v1, -11264);
                    a0 = a0 & 0x100;
                    if (a0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x0047e780
            charge(ctx, 5);
            a0 = 256;
            v1 = 0x10010000;
            a3 = sra(a2, 1);
            sw(a0, v1, -8176);  // 0x1000E010 D_STAT
            if (i64(a2) < 0) {
                // 0x0047e794
                charge(ctx, 2);
                v1 = addiu(a2, 1);
                a3 = sra(v1, 1);
            }
            // 0x0047e79c
            charge(ctx, 18);
            a0 = addu(a2, a3);
            v1 = 0x10010000;
            a0 = sll(a0, 4);
            a1 = sll(a2, 2);
            sw(a0, v1, -12160);  // 0x1000D080 D8 fromSPR SADR
            sw(s0, v1, -12272);  // 0x1000D010 D8 fromSPR MADR
            a0 = 256;
            sw(a1, v1, -12256);  // 0x1000D020 D8 fromSPR QWC
            sw(a0, v1, -12288);  // 0x1000D000 D8 fromSPR CHCR
            sync(ctx, 0);
            sync(ctx, 16);
            v1 = sll(a3, 4);
            a0 = sll(a1, 4);
            s1 = addu(s1, v1);
            s0 = addu(s0, a0);
            v1 = sll(a2, 4);
            s3 = subu(s3, a2);
            s2 = addu(s2, v1);
        }
        // 0x0047e7e4
        charge(ctx, 3);
        at = slt(0, s3);
        t0 = 0;
        if (at != 0) {
            // 0x0047e7f0
            charge(ctx, 4);
            a3 = addiu(sp, 0xD4);
            a0 = sll(fp, 2);
            a1 = addiu(sp, 0xD0);
            a2 = 0x10000;
            for (;;) {
                // 0x0047e800
                charge(ctx, 4);
                lwc1(f1, s1, 0);
                lwc1(f0, s1, 4);
                swc1(f1, sp, 0xD0);
                swc1(f0, a3, 0);
                for (;;) {
                    // 0x0047e810
                    charge(ctx, 7);
                    di(ctx);
                    sync(ctx, 16);
                    mfc0(v1, 12);
                    v1 = v1 & a2;
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0047e82c
                charge(ctx, 23);
                lqc2(vf3, a1, 0);
                vmul_bc(0xE, vf4, vf1, vf3, 0);  // vmulx.xyz
                vmul_bc(0xE, vf5, vf2, vf3, 1);  // vmuly.xyz
                lqc2(vf6, s2, 0);
                vsub(0xE, vf7, vf6, vf4);  // vsub.xyz
                vadd(0xE, vf8, vf6, vf4);  // vadd.xyz
                vadd(0xE, vf9, vf6, vf4);  // vadd.xyz
                vsub(0xE, vf10, vf6, vf4);  // vsub.xyz
                vsub(0xE, vf7, vf7, vf5);  // vsub.xyz
                vsub(0xE, vf8, vf8, vf5);  // vsub.xyz
                vadd(0xE, vf9, vf9, vf5);  // vadd.xyz
                vadd(0xE, vf10, vf10, vf5);  // vadd.xyz
                sqc2(vf7, s0, 0);
                sqc2(vf8, s0, 16);
                sqc2(vf9, s0, 32);
                sqc2(vf10, s0, 48);
                ei(ctx);
                t0 = addiu(t0, 1);
                v1 = slt(t0, s3);
                s1 = addu(s1, s7);
                s0 = addu(s0, a0);
                s2 = addu(s2, s6);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0047e888
            charge(ctx, 2);
        }
    }
    // 0x0047e9a8 (the shared epilogue, written out on this path)
    charge(ctx, 12);
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

// 0x0047E9E0 sub_47E9E0 -- 4392 bytes; frame 0x110: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Scratchpad DMA kernel using the SPR matrices at 0x3F40 / 0x3F50 / 0x3F60.
void sub_47E9E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6};
    Vf vf0{ctx, 0}, vf1{ctx, 1}, vf2{ctx, 2}, vf3{ctx, 3}, vf4{ctx, 4}, vf5{ctx, 5}, vf6{ctx, 6}, vf7{ctx, 7}, vf8{ctx, 8}, vf9{ctx, 9}, vf10{ctx, 10}, vf11{ctx, 11}, vf12{ctx, 12}, vf13{ctx, 13}, vf14{ctx, 14}, vf18{ctx, 18}, vf19{ctx, 19}, vf20{ctx, 20}, vf21{ctx, 21}, vf22{ctx, 22}, vf23{ctx, 23}, vf24{ctx, 24}, vf25{ctx, 25}, vf26{ctx, 26}, vf27{ctx, 27}, vf28{ctx, 28}, vf29{ctx, 29}, vf30{ctx, 30}, vf31{ctx, 31};
    // 0x0047e9e0
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x110);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    s6 = a2;
    sq(s4, sp, 0x40);
    s5 = a1;
    sq(s3, sp, 0x30);
    s4 = a3;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, t0, 8);
    lw(s1, a0, 0);
    lw(s3, t0, 4);
    lw(s2, t0, 52);
    lw(s0, t0, 28);
    sq(v1, sp, 0xD0);
    lw(v1, t0, 56);
    sq(v1, sp, 0xC0);
    lw(v1, t0, 32);
    sq(v1, sp, 0xB0);
    lw(v1, a0, 4);
    lq(a0, sp, 0xD0);
    sq(v1, sp, 0xA0);
    if (a0 != v1) {
        // 0x0047f7c0
        charge(ctx, 21);
        lwc1(f5, s5, 0);
        a0 = 0x3F000000;
        lwc1(f4, s5, 4);
        v1 = 0x10000;
        lwc1(f3, s5, 8);
        lwc1(f2, s6, 0);
        mtc1(a0, f6);
        lwc1(f1, s6, 4);
        lwc1(f0, s6, 8);
        mul_s(f5, f6, f5);
        mul_s(f4, f6, f4);
        mul_s(f3, f6, f3);
        mul_s(f2, f6, f2);
        mul_s(f1, f6, f1);
        mul_s(f0, f6, f0);
        swc1(f5, sp, 0x100);
        swc1(f4, sp, 0x104);
        swc1(f3, sp, 0x108);
        swc1(f2, sp, 0xF0);
        swc1(f1, sp, 0xF4);
        swc1(f0, sp, 0xF8);
        for (;;) {
            // 0x0047f814
            charge(ctx, 7);
            di(ctx);
            sync(ctx, 16);
            mfc0(a0, 12);
            a0 = a0 & v1;
            if (a0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0047f830
        charge(ctx, 79);
        at = 0x3FC90000;
        v1 = at | 0xFDB;
        mtc1(v1, f0);
        mfc1(v1, f0);
        ctc2(v1, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x8, vf10, vf0);  // vaddi.x
        at = 0x40490000;
        a0 = at | 0xFDB;
        mtc1(a0, f0);
        mfc1(v1, f0);
        ctc2(v1, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x4, vf10, vf0);  // vaddi.y
        at = 0x40090000;
        v1 = at | 0xFDB;
        mtc1(v1, f0);
        mfc1(v1, f0);
        ctc2(v1, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x2, vf10, vf0);  // vaddi.z
        mtc1(a0, f0);
        neg_s(f0, f0);
        mfc1(v1, f0);
        ctc2(v1, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x8, vf11, vf0);  // vaddi.x
        at = 0x40840000;
        v1 = at | 0x87ED;
        mtc1(v1, f0);
        neg_s(f0, f0);
        mfc1(v1, f0);
        ctc2(v1, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x4, vf11, vf0);  // vaddi.y
        v1 = 0x0;
        v1 = dsll(v1, 16);
        v1 = dsll(v1, 16);
        v1 = v1 | 0xB94F;
        v1 = dsll(v1, 16);
        v1 = v1 | 0xB21F;
        ctc2(v1, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x2, vf11, vf0);  // vaddi.z
        v1 = 0x0;
        v1 = dsll(v1, 16);
        v1 = dsll(v1, 16);
        v1 = v1 | 0xBE2A;
        v1 = dsll(v1, 16);
        v1 = v1 | 0xAAA4;
        ctc2(v1, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x8, vf12, vf0);  // vaddi.x
        at = 0x3C080000;
        v1 = at | 0x873E;
        ctc2(v1, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x4, vf12, vf0);  // vaddi.y
        at = 0x362E0000;
        v1 = at | 0x9C14;
        ctc2(v1, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x2, vf12, vf0);  // vaddi.z
        v1 = 0x3F800000;
        ctc2(v1, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x8, vf13, vf0);  // vaddi.x
        ei(ctx);
        v1 = 0x10000;
        for (;;) {
            // 0x0047f96c
            charge(ctx, 7);
            di(ctx);
            sync(ctx, 16);
            mfc0(a0, 12);
            a0 = a0 & v1;
            if (a0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0047f988
        charge(ctx, 8);
        a0 = addiu(sp, 0x100);
        v1 = addiu(sp, 0xF0);
        lqc2(vf8, a0, 0);
        lqc2(vf9, v1, 0);
        ei(ctx);
        at = slt(0, s4);
        t2 = 0;
        if (at != 0) {
            // 0x0047f9a8
            charge(ctx, 7);
            lq(v1, sp, 0xA0);
            t1 = addiu(sp, 0xE4);
            t0 = addiu(sp, 0xE8);
            a3 = addiu(sp, 0xEC);
            a1 = addiu(sp, 0xE0);
            a2 = 0x10000;
            a0 = sll(v1, 2);
            for (;;) {
                // 0x0047f9c4
                charge(ctx, 7);
                lwc1(f2, s2, 0);
                lwc1(f1, s0, 0);
                lwc1(f0, s0, 4);
                swc1(f2, sp, 0xE0);
                swc1(f2, t0, 0);
                swc1(f1, t1, 0);
                swc1(f0, a3, 0);
                for (;;) {
                    // 0x0047f9e0
                    charge(ctx, 7);
                    di(ctx);
                    sync(ctx, 16);
                    mfc0(v1, 12);
                    v1 = v1 & a2;
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0047f9fc
                charge(ctx, 55);
                lqc2(vf1, a1, 0);
                vabs(0xC, vf7, vf1);  // vabs.xy
                vadda_bc(0xF, vf0, vf10, 0);  // vaddax.xyzw
                vmsub_bc(0xC, vf7, vf7, vf0, 3);  // vmsubw.xy
                vadda_bc(0xE, vf0, vf10, 1);  // vadday.xyz
                vadda_bc(0x1, vf0, vf10, 2);  // vaddaz.w
                vmsub_bc(0x3, vf2, vf1, vf0, 3);  // vmsubw.zw
                vadda_bc(0xE, vf0, vf11, 0);  // vaddax.xyz
                vadda_bc(0x1, vf0, vf11, 1);  // vadday.w
                vmsub_bc(0x3, vf3, vf1, vf0, 3);  // vmsubw.zw
                vmini(0x3, vf2, vf1, vf2);  // vmini.zw
                vmax(0x3, vf7, vf2, vf3);  // vmax.zw
                vmul(0xF, vf2, vf7, vf7);  // vmul.xyzw
                vmul_bc(0xF, vf6, vf7, vf11, 2);  // vmulz.xyzw
                vmul_bc(0xF, vf4, vf7, vf12, 0);  // vmulx.xyzw
                vmul_bc(0xF, vf5, vf7, vf12, 1);  // vmuly.xyzw
                vmul(0xF, vf3, vf2, vf2);  // vmul.xyzw
                vmul(0xF, vf6, vf6, vf2);  // vmul.xyzw
                vmula(0xF, vf4, vf2);  // vmula.xyzw
                vmul_bc(0xF, vf4, vf7, vf12, 2);  // vmulz.xyzw
                vmul(0xF, vf2, vf3, vf3);  // vmul.xyzw
                vmadda(0xF, vf6, vf3);  // vmadda.xyzw
                vmadda(0xF, vf5, vf3);  // vmadda.xyzw
                vmadda_bc(0xF, vf7, vf13, 0);  // vmaddax.xyzw
                vmadd(0xF, vf7, vf4, vf2);  // vmadd.xyzw
                lqc2(vf20, s3, 0);
                vmula_bc(0xF, vf8, vf7, 0);  // vmulax.xyzw
                vmsub_bc(0xF, vf18, vf9, vf7, 2);  // vmsubz.xyzw
                vmul_bc(0xF, vf18, vf18, vf1, 1);  // vmuly.xyzw
                vmula_bc(0xF, vf9, vf7, 0);  // vmulax.xyzw
                vmadd_bc(0xF, vf19, vf8, vf7, 2);  // vmaddz.xyzw
                vmul_bc(0xF, vf19, vf19, vf1, 3);  // vmulw.xyzw
                vsub(0xF, vf21, vf20, vf18);  // vsub.xyzw
                vadd(0xF, vf22, vf20, vf18);  // vadd.xyzw
                vadd(0xF, vf23, vf20, vf18);  // vadd.xyzw
                vsub(0xF, vf24, vf20, vf18);  // vsub.xyzw
                vsub(0xF, vf21, vf21, vf19);  // vsub.xyzw
                vsub(0xF, vf22, vf22, vf19);  // vsub.xyzw
                vadd(0xF, vf23, vf23, vf19);  // vadd.xyzw
                vadd(0xF, vf24, vf24, vf19);  // vadd.xyzw
                sqc2(vf21, s1, 0);
                sqc2(vf22, s1, 16);
                sqc2(vf23, s1, 32);
                sqc2(vf24, s1, 48);
                ei(ctx);
                t2 = addiu(t2, 1);
                lq(v1, sp, 0xD0);
                s3 = addu(s3, v1);
                lq(v1, sp, 0xB0);
                s0 = addu(s0, v1);
                lq(v1, sp, 0xC0);
                s2 = addu(s2, v1);
                v1 = slt(t2, s4);
                s1 = addu(s1, a0);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
    } else {
        // 0x0047ea50
        charge(ctx, 7);
        a0 = 0;
        jal(ctx, 0x47EA50u, gen::fn__sceFlushCache_005033e0);
        v1 = 0x10010000;
        lw(a0, v1, -12288);  // 0x1000D000 D8 fromSPR CHCR
        a0 = a0 & 0x100;
        if (a0 != 0) {
            // 0x0047ea6c
            charge(ctx, 4);
            a0 = 256;
            sw(a0, v1, -8160);
            sync(ctx, 0);
            sync(ctx, 16);
            for (;;) {
                // 0x0047ea7c
                charge(ctx, 7);
                if (cop0_cond(ctx)) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x0047ea98
        charge(ctx, 5);
        v1 = 0x10010000;
        lw(a0, v1, -11264);  // 0x1000D400 D9 toSPR CHCR
        a0 = a0 & 0x100;
        if (a0 != 0) {
            // 0x0047eaac
            charge(ctx, 4);
            a0 = 512;
            sw(a0, v1, -8160);
            sync(ctx, 0);
            sync(ctx, 16);
            for (;;) {
                // 0x0047eabc
                charge(ctx, 7);
                if (cop0_cond(ctx)) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0047ead8
            charge(ctx, 1);
            v1 = 0x10010000;
            for (;;) {
                // 0x0047eadc
                charge(ctx, 7);
                lw(a0, v1, -11264);
                a0 = a0 & 0x100;
                if (a0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x0047eaf8
        charge(ctx, 25);
        a0 = 0x70000000;
        lwc1(f0, s5, 0);
        v1 = 0x3F000000;
        mtc1(v1, f1);
        a2 = a0 | 0x3F40;
        a1 = a0 | 0x3F50;
        t6 = a0 | 0x3F60;
        v1 = 0x10000;
        mul_s(f0, f1, f0);
        swc1(f0, a0, 16192);  // 0x70003F40 SPR+0x3F40
        lwc1(f0, s5, 4);
        mul_s(f0, f1, f0);
        swc1(f0, a0, 16196);  // 0x70003F44 SPR+0x3F44
        lwc1(f0, s5, 8);
        mul_s(f0, f1, f0);
        swc1(f0, a0, 16200);  // 0x70003F48 SPR+0x3F48
        lwc1(f0, s6, 0);
        mul_s(f0, f1, f0);
        swc1(f0, a0, 16208);  // 0x70003F50 SPR+0x3F50
        lwc1(f0, s6, 4);
        mul_s(f0, f1, f0);
        swc1(f0, a0, 16212);  // 0x70003F54 SPR+0x3F54
        lwc1(f0, s6, 8);
        mul_s(f0, f1, f0);
        swc1(f0, a0, 16216);  // 0x70003F58 SPR+0x3F58
        for (;;) {
            // 0x0047eb5c
            charge(ctx, 7);
            di(ctx);
            sync(ctx, 16);
            mfc0(a0, 12);
            a0 = a0 & v1;
            if (a0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0047eb78
        charge(ctx, 79);
        at = 0x3FC90000;
        v1 = at | 0xFDB;
        mtc1(v1, f0);
        mfc1(v1, f0);
        ctc2(v1, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x8, vf10, vf0);  // vaddi.x
        at = 0x40490000;
        a0 = at | 0xFDB;
        mtc1(a0, f0);
        mfc1(v1, f0);
        ctc2(v1, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x4, vf10, vf0);  // vaddi.y
        at = 0x40090000;
        v1 = at | 0xFDB;
        mtc1(v1, f0);
        mfc1(v1, f0);
        ctc2(v1, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x2, vf10, vf0);  // vaddi.z
        mtc1(a0, f0);
        neg_s(f0, f0);
        mfc1(v1, f0);
        ctc2(v1, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x8, vf11, vf0);  // vaddi.x
        at = 0x40840000;
        v1 = at | 0x87ED;
        mtc1(v1, f0);
        neg_s(f0, f0);
        mfc1(v1, f0);
        ctc2(v1, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x4, vf11, vf0);  // vaddi.y
        v1 = 0x0;
        v1 = dsll(v1, 16);
        v1 = dsll(v1, 16);
        v1 = v1 | 0xB94F;
        v1 = dsll(v1, 16);
        v1 = v1 | 0xB21F;
        ctc2(v1, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x2, vf11, vf0);  // vaddi.z
        v1 = 0x0;
        v1 = dsll(v1, 16);
        v1 = dsll(v1, 16);
        v1 = v1 | 0xBE2A;
        v1 = dsll(v1, 16);
        v1 = v1 | 0xAAA4;
        ctc2(v1, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x8, vf12, vf0);  // vaddi.x
        at = 0x3C080000;
        v1 = at | 0x873E;
        ctc2(v1, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x4, vf12, vf0);  // vaddi.y
        at = 0x362E0000;
        v1 = at | 0x9C14;
        ctc2(v1, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x2, vf12, vf0);  // vaddi.z
        v1 = 0x3F800000;
        ctc2(v1, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x8, vf13, vf0);  // vaddi.x
        ei(ctx);
        v1 = 0x10000;
        for (;;) {
            // 0x0047ecb4
            charge(ctx, 7);
            di(ctx);
            sync(ctx, 16);
            mfc0(a0, 12);
            a0 = a0 & v1;
            if (a0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0047ecd0
        charge(ctx, 6);
        lqc2(vf8, a2, 0);
        lqc2(vf9, a1, 0);
        ei(ctx);
        v1 = slti(s4, 176);
        if (v1 == 0) {
            // 0x0047ece8
            charge(ctx, 11);
            t0 = 0x70000000;
            a0 = 0x10010000;
            t4 = 256;
            t3 = 512;
            t2 = 44;
            t1 = 704;
            s7 = 88;
            fp = 0x840;
            a3 = t0 | 0x2C0;
            a2 = t0 | 0x840;
            a1 = t0 | 0x1340;
            for (;;) {
                // 0x0047ed14
                charge(ctx, 4);
                lw(v1, a0, -12288);
                v1 = v1 & 0x100;
                if (v1 != 0) {
                    // 0x0047ed24
                    charge(ctx, 3);
                    sw(t4, a0, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x0047ed30
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047ed4c
                    charge(ctx, 1);
                }
                // 0x0047ed50
                charge(ctx, 4);
                lw(v1, a0, -11264);
                v1 = v1 & 0x100;
                if (v1 != 0) {
                    // 0x0047ed60
                    charge(ctx, 4);
                    sw(t3, a0, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x0047ed70
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047ed8c
                    charge(ctx, 1);
                    for (;;) {
                        // 0x0047ed90
                        charge(ctx, 7);
                        lw(v1, a0, -11264);
                        v1 = v1 & 0x100;
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047edac
                    charge(ctx, 1);
                }
                // 0x0047edb0
                charge(ctx, 11);
                sw(t3, a0, -8176);
                sw(zero, a0, -11136);
                sw(s2, a0, -11248);
                sw(t2, a0, -11232);
                sw(t4, a0, -11264);
                sync(ctx, 0);
                sync(ctx, 16);
                lw(v1, a0, -11264);
                v1 = v1 & 0x100;
                if (v1 != 0) {
                    // 0x0047eddc
                    charge(ctx, 3);
                    sw(t3, a0, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x0047ede8
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047ee04
                    charge(ctx, 1);
                    for (;;) {
                        // 0x0047ee08
                        charge(ctx, 7);
                        lw(v1, a0, -11264);
                        v1 = v1 & 0x100;
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047ee24
                    charge(ctx, 1);
                }
                // 0x0047ee28
                charge(ctx, 11);
                sw(t3, a0, -8176);
                sw(t1, a0, -11136);
                sw(s0, a0, -11248);
                sw(s7, a0, -11232);
                sw(t4, a0, -11264);
                sync(ctx, 0);
                sync(ctx, 16);
                lw(v1, a0, -11264);
                v1 = v1 & 0x100;
                if (v1 != 0) {
                    // 0x0047ee54
                    charge(ctx, 3);
                    sw(t3, a0, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x0047ee60
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047ee7c
                    charge(ctx, 1);
                    for (;;) {
                        // 0x0047ee80
                        charge(ctx, 7);
                        lw(v1, a0, -11264);
                        v1 = v1 & 0x100;
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047ee9c
                    charge(ctx, 1);
                }
                // 0x0047eea0
                charge(ctx, 12);
                sw(t3, a0, -8176);
                sw(fp, a0, -11136);
                v1 = 176;
                sw(s3, a0, -11248);
                sw(v1, a0, -11232);
                sw(t4, a0, -11264);
                sync(ctx, 0);
                sync(ctx, 16);
                lw(v1, a0, -11264);
                v1 = v1 & 0x100;
                if (v1 != 0) {
                    // 0x0047eed0
                    charge(ctx, 4);
                    sw(t3, a0, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x0047eee0
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047eefc
                    charge(ctx, 1);
                    for (;;) {
                        // 0x0047ef00
                        charge(ctx, 7);
                        lw(v1, a0, -11264);
                        v1 = v1 & 0x100;
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047ef1c
                    charge(ctx, 1);
                }
                // 0x0047ef20
                charge(ctx, 6);
                s5 = t0;
                t9 = a3;
                t8 = a2;
                t7 = a1;
                s6 = 0;
                for (;;) {
                    // 0x0047ef38
                    charge(ctx, 8);
                    lwc1(f0, s5, 0);
                    swc1(f0, t6, 0);
                    lwc1(f0, s5, 4);
                    swc1(f0, t6, 4);
                    lwc1(f0, s5, 0);
                    swc1(f0, t6, 8);
                    lwc1(f0, s5, 4);
                    swc1(f0, t6, 12);
                    for (;;) {
                        // 0x0047ef58
                        charge(ctx, 8);
                        di(ctx);
                        sync(ctx, 16);
                        mfc0(t5, 12);
                        v1 = 0x10000;
                        t5 = t5 & v1;
                        if (t5 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047ef78
                    charge(ctx, 72);
                    lqc2(vf1, t6, 0);
                    vabs(0xC, vf7, vf1);  // vabs.xy
                    vadda_bc(0xF, vf0, vf10, 0);  // vaddax.xyzw
                    vmsub_bc(0xC, vf7, vf7, vf0, 3);  // vmsubw.xy
                    vadda_bc(0xE, vf0, vf10, 1);  // vadday.xyz
                    vadda_bc(0x1, vf0, vf10, 2);  // vaddaz.w
                    vmsub_bc(0x3, vf2, vf1, vf0, 3);  // vmsubw.zw
                    vadda_bc(0xE, vf0, vf11, 0);  // vaddax.xyz
                    vadda_bc(0x1, vf0, vf11, 1);  // vadday.w
                    vmsub_bc(0x3, vf3, vf1, vf0, 3);  // vmsubw.zw
                    vmini(0x3, vf2, vf1, vf2);  // vmini.zw
                    vmax(0x3, vf7, vf2, vf3);  // vmax.zw
                    vmul(0xF, vf2, vf7, vf7);  // vmul.xyzw
                    vmul_bc(0xF, vf6, vf7, vf11, 2);  // vmulz.xyzw
                    vmul_bc(0xF, vf4, vf7, vf12, 0);  // vmulx.xyzw
                    vmul_bc(0xF, vf5, vf7, vf12, 1);  // vmuly.xyzw
                    vmul(0xF, vf3, vf2, vf2);  // vmul.xyzw
                    vmul(0xF, vf6, vf6, vf2);  // vmul.xyzw
                    vmula(0xF, vf4, vf2);  // vmula.xyzw
                    vmul_bc(0xF, vf4, vf7, vf12, 2);  // vmulz.xyzw
                    vmul(0xF, vf2, vf3, vf3);  // vmul.xyzw
                    vmadda(0xF, vf6, vf3);  // vmadda.xyzw
                    vmadda(0xF, vf5, vf3);  // vmadda.xyzw
                    vmadda_bc(0xF, vf7, vf13, 0);  // vmaddax.xyzw
                    vmadd(0xF, vf7, vf4, vf2);  // vmadd.xyzw
                    lqc2(vf20, t8, 0);
                    lqc2(vf27, t8, 16);
                    lqc2(vf14, t9, 0);
                    vmula_bc(0xF, vf8, vf7, 0);  // vmulax.xyzw
                    vmsub_bc(0xF, vf18, vf9, vf7, 2);  // vmsubz.xyzw
                    vmula_bc(0xF, vf9, vf7, 0);  // vmulax.xyzw
                    vmadd_bc(0xF, vf19, vf8, vf7, 2);  // vmaddz.xyzw
                    vmula_bc(0xF, vf8, vf7, 1);  // vmulay.xyzw
                    vmsub_bc(0xF, vf25, vf9, vf7, 3);  // vmsubw.xyzw
                    vmula_bc(0xF, vf9, vf7, 1);  // vmulay.xyzw
                    vmadd_bc(0xF, vf26, vf8, vf7, 3);  // vmaddw.xyzw
                    vmul_bc(0xF, vf18, vf18, vf14, 0);  // vmulx.xyzw
                    vmul_bc(0xF, vf19, vf19, vf14, 1);  // vmuly.xyzw
                    vmul_bc(0xF, vf25, vf25, vf14, 2);  // vmulz.xyzw
                    vmul_bc(0xF, vf26, vf26, vf14, 3);  // vmulw.xyzw
                    vsub(0xF, vf21, vf20, vf18);  // vsub.xyzw
                    vadd(0xF, vf22, vf20, vf18);  // vadd.xyzw
                    vadd(0xF, vf23, vf20, vf18);  // vadd.xyzw
                    vsub(0xF, vf24, vf20, vf18);  // vsub.xyzw
                    vsub(0xF, vf21, vf21, vf19);  // vsub.xyzw
                    vsub(0xF, vf22, vf22, vf19);  // vsub.xyzw
                    vadd(0xF, vf23, vf23, vf19);  // vadd.xyzw
                    vadd(0xF, vf24, vf24, vf19);  // vadd.xyzw
                    vsub(0xF, vf28, vf27, vf25);  // vsub.xyzw
                    vadd(0xF, vf29, vf27, vf25);  // vadd.xyzw
                    vadd(0xF, vf30, vf27, vf25);  // vadd.xyzw
                    vsub(0xF, vf31, vf27, vf25);  // vsub.xyzw
                    vsub(0xF, vf28, vf28, vf26);  // vsub.xyzw
                    vsub(0xF, vf29, vf29, vf26);  // vsub.xyzw
                    vadd(0xF, vf30, vf30, vf26);  // vadd.xyzw
                    vadd(0xF, vf31, vf31, vf26);  // vadd.xyzw
                    sqc2(vf21, t7, 0);
                    sqc2(vf22, t7, 16);
                    sqc2(vf23, t7, 32);
                    sqc2(vf24, t7, 48);
                    sqc2(vf28, t7, 64);
                    sqc2(vf29, t7, 80);
                    sqc2(vf30, t7, 96);
                    sqc2(vf31, t7, 112);
                    ei(ctx);
                    s6 = addiu(s6, 2);
                    v1 = slti(s6, 176);
                    t8 = addiu(t8, 32);
                    t9 = addiu(t9, 16);
                    s5 = addiu(s5, 8);
                    t7 = addiu(t7, 128);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0047f098
                charge(ctx, 4);
                lw(v1, a0, -12288);
                v1 = v1 & 0x100;
                if (v1 != 0) {
                    // 0x0047f0a8
                    charge(ctx, 4);
                    sw(t4, a0, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x0047f0b8
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047f0d4
                    charge(ctx, 1);
                }
                // 0x0047f0d8
                charge(ctx, 4);
                lw(v1, a0, -11264);
                v1 = v1 & 0x100;
                if (v1 != 0) {
                    // 0x0047f0e8
                    charge(ctx, 4);
                    sw(t3, a0, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x0047f0f8
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047f114
                    charge(ctx, 1);
                    for (;;) {
                        // 0x0047f118
                        charge(ctx, 7);
                        lw(v1, a0, -11264);
                        v1 = v1 & 0x100;
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047f134
                    charge(ctx, 1);
                }
                // 0x0047f138
                charge(ctx, 15);
                sw(t4, a0, -8176);
                v1 = 4928;
                sw(v1, a0, -12160);
                sw(s1, a0, -12272);
                sw(t1, a0, -12256);
                sw(t4, a0, -12288);
                sync(ctx, 0);
                sync(ctx, 16);
                s4 = addiu(s4, -176);
                s3 = addiu(s3, 2816);
                at = slti(s4, 176);
                s1 = addiu(s1, 11264);
                s2 = addiu(s2, 704);
                s0 = addiu(s0, 1408);
                if (at != 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0047f174
            charge(ctx, 1);
        }
        // 0x0047f178
        charge(ctx, 3);
        at = slti(s4, 4);
        if (at == 0) {
            // 0x0047f184
            charge(ctx, 2);
            v1 = sra(s4, 2);
            if (i64(s4) < 0) {
                // 0x0047f18c
                charge(ctx, 2);
                v1 = addiu(s4, 3);
                v1 = sra(v1, 2);
            }
            // 0x0047f194
            charge(ctx, 5);
            a0 = 0x10010000;
            lw(a1, a0, -12288);  // 0x1000D000 D8 fromSPR CHCR
            a1 = a1 & 0x100;
            v1 = sll(v1, 2);
            if (a1 != 0) {
                // 0x0047f1a8
                charge(ctx, 4);
                a1 = 256;
                sw(a1, a0, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x0047f1b8
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x0047f1d4
            charge(ctx, 5);
            a0 = 0x10010000;
            lw(a1, a0, -11264);  // 0x1000D400 D9 toSPR CHCR
            a1 = a1 & 0x100;
            if (a1 != 0) {
                // 0x0047f1e8
                charge(ctx, 4);
                a1 = 512;
                sw(a1, a0, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x0047f1f8
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0047f214
                charge(ctx, 1);
                a0 = 0x10010000;
                for (;;) {
                    // 0x0047f218
                    charge(ctx, 7);
                    lw(a1, a0, -11264);
                    a1 = a1 & 0x100;
                    if (a1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0047f234
                charge(ctx, 1);
            }
            // 0x0047f238
            charge(ctx, 7);
            a1 = 512;
            a0 = 0x10010000;
            a2 = sra(v1, 2);
            sw(a1, a0, -8176);  // 0x1000E010 D_STAT
            sw(zero, a0, -11136);  // 0x1000D480 D9 toSPR SADR
            sw(s2, a0, -11248);  // 0x1000D410 D9 toSPR MADR
            if (i64(v1) < 0) {
                // 0x0047f254
                charge(ctx, 2);
                a0 = addiu(v1, 3);
                a2 = sra(a0, 2);
            }
            // 0x0047f25c
            charge(ctx, 10);
            a0 = 0x10010000;
            a1 = 256;
            sw(a2, a0, -11232);  // 0x1000D420 D9 toSPR QWC
            sw(a1, a0, -11264);  // 0x1000D400 D9 toSPR CHCR
            sync(ctx, 0);
            sync(ctx, 16);
            lw(a1, a0, -11264);  // 0x1000D400 D9 toSPR CHCR
            a1 = a1 & 0x100;
            if (a1 != 0) {
                // 0x0047f284
                charge(ctx, 4);
                a1 = 512;
                sw(a1, a0, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x0047f294
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0047f2b0
                charge(ctx, 1);
                a0 = 0x10010000;
                for (;;) {
                    // 0x0047f2b4
                    charge(ctx, 7);
                    lw(a1, a0, -11264);
                    a1 = a1 & 0x100;
                    if (a1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x0047f2d0
            charge(ctx, 8);
            a2 = 512;
            a0 = 0x10010000;
            a1 = 704;
            sw(a2, a0, -8176);  // 0x1000E010 D_STAT
            sw(a1, a0, -11136);  // 0x1000D480 D9 toSPR SADR
            a2 = sra(v1, 1);
            sw(s0, a0, -11248);  // 0x1000D410 D9 toSPR MADR
            if (i64(v1) < 0) {
                // 0x0047f2f0
                charge(ctx, 2);
                a0 = addiu(v1, 1);
                a2 = sra(a0, 1);
            }
            // 0x0047f2f8
            charge(ctx, 10);
            a0 = 0x10010000;
            a1 = 256;
            sw(a2, a0, -11232);  // 0x1000D420 D9 toSPR QWC
            sw(a1, a0, -11264);  // 0x1000D400 D9 toSPR CHCR
            sync(ctx, 0);
            sync(ctx, 16);
            lw(a1, a0, -11264);  // 0x1000D400 D9 toSPR CHCR
            a1 = a1 & 0x100;
            if (a1 != 0) {
                // 0x0047f320
                charge(ctx, 4);
                a1 = 512;
                sw(a1, a0, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x0047f330
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0047f34c
                charge(ctx, 1);
                a0 = 0x10010000;
                for (;;) {
                    // 0x0047f350
                    charge(ctx, 7);
                    lw(a1, a0, -11264);
                    a1 = a1 & 0x100;
                    if (a1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0047f36c
                charge(ctx, 1);
            }
            // 0x0047f370
            charge(ctx, 15);
            a3 = 512;
            a0 = 0x10010000;
            a2 = 2112;
            sw(a3, a0, -8176);  // 0x1000E010 D_STAT
            a1 = 256;
            sw(a2, a0, -11136);  // 0x1000D480 D9 toSPR SADR
            sw(s3, a0, -11248);  // 0x1000D410 D9 toSPR MADR
            sw(v1, a0, -11232);  // 0x1000D420 D9 toSPR QWC
            sw(a1, a0, -11264);  // 0x1000D400 D9 toSPR CHCR
            sync(ctx, 0);
            sync(ctx, 16);
            lw(a1, a0, -11264);  // 0x1000D400 D9 toSPR CHCR
            a1 = a1 & 0x100;
            if (a1 != 0) {
                // 0x0047f3ac
                charge(ctx, 3);
                sw(a3, a0, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x0047f3b8
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0047f3d4
                charge(ctx, 1);
                a0 = 0x10010000;
                for (;;) {
                    // 0x0047f3d8
                    charge(ctx, 7);
                    lw(a1, a0, -11264);
                    a1 = a1 & 0x100;
                    if (a1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0047f3f4
                charge(ctx, 1);
            }
            // 0x0047f3f8
            charge(ctx, 7);
            a3 = 0x70000000;
            at = slt(0, v1);
            t9 = a3 | 0x2C0;
            t8 = a3 | 0x840;
            t7 = a3 | 0x1340;
            a2 = 0;
            if (at != 0) {
                // 0x0047f414
                charge(ctx, 1);
                a1 = 0x10000;
                for (;;) {
                    // 0x0047f418
                    charge(ctx, 8);
                    lwc1(f0, a3, 0);
                    swc1(f0, t6, 0);
                    lwc1(f0, a3, 4);
                    swc1(f0, t6, 4);
                    lwc1(f0, a3, 0);
                    swc1(f0, t6, 8);
                    lwc1(f0, a3, 4);
                    swc1(f0, t6, 12);
                    for (;;) {
                        // 0x0047f438
                        charge(ctx, 7);
                        di(ctx);
                        sync(ctx, 16);
                        mfc0(a0, 12);
                        a0 = a0 & a1;
                        if (a0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047f454
                    charge(ctx, 72);
                    lqc2(vf1, t6, 0);
                    vabs(0xC, vf7, vf1);  // vabs.xy
                    vadda_bc(0xF, vf0, vf10, 0);  // vaddax.xyzw
                    vmsub_bc(0xC, vf7, vf7, vf0, 3);  // vmsubw.xy
                    vadda_bc(0xE, vf0, vf10, 1);  // vadday.xyz
                    vadda_bc(0x1, vf0, vf10, 2);  // vaddaz.w
                    vmsub_bc(0x3, vf2, vf1, vf0, 3);  // vmsubw.zw
                    vadda_bc(0xE, vf0, vf11, 0);  // vaddax.xyz
                    vadda_bc(0x1, vf0, vf11, 1);  // vadday.w
                    vmsub_bc(0x3, vf3, vf1, vf0, 3);  // vmsubw.zw
                    vmini(0x3, vf2, vf1, vf2);  // vmini.zw
                    vmax(0x3, vf7, vf2, vf3);  // vmax.zw
                    vmul(0xF, vf2, vf7, vf7);  // vmul.xyzw
                    vmul_bc(0xF, vf6, vf7, vf11, 2);  // vmulz.xyzw
                    vmul_bc(0xF, vf4, vf7, vf12, 0);  // vmulx.xyzw
                    vmul_bc(0xF, vf5, vf7, vf12, 1);  // vmuly.xyzw
                    vmul(0xF, vf3, vf2, vf2);  // vmul.xyzw
                    vmul(0xF, vf6, vf6, vf2);  // vmul.xyzw
                    vmula(0xF, vf4, vf2);  // vmula.xyzw
                    vmul_bc(0xF, vf4, vf7, vf12, 2);  // vmulz.xyzw
                    vmul(0xF, vf2, vf3, vf3);  // vmul.xyzw
                    vmadda(0xF, vf6, vf3);  // vmadda.xyzw
                    vmadda(0xF, vf5, vf3);  // vmadda.xyzw
                    vmadda_bc(0xF, vf7, vf13, 0);  // vmaddax.xyzw
                    vmadd(0xF, vf7, vf4, vf2);  // vmadd.xyzw
                    lqc2(vf20, t8, 0);
                    lqc2(vf27, t8, 16);
                    lqc2(vf14, t9, 0);
                    vmula_bc(0xF, vf8, vf7, 0);  // vmulax.xyzw
                    vmsub_bc(0xF, vf18, vf9, vf7, 2);  // vmsubz.xyzw
                    vmula_bc(0xF, vf9, vf7, 0);  // vmulax.xyzw
                    vmadd_bc(0xF, vf19, vf8, vf7, 2);  // vmaddz.xyzw
                    vmula_bc(0xF, vf8, vf7, 1);  // vmulay.xyzw
                    vmsub_bc(0xF, vf25, vf9, vf7, 3);  // vmsubw.xyzw
                    vmula_bc(0xF, vf9, vf7, 1);  // vmulay.xyzw
                    vmadd_bc(0xF, vf26, vf8, vf7, 3);  // vmaddw.xyzw
                    vmul_bc(0xF, vf18, vf18, vf14, 0);  // vmulx.xyzw
                    vmul_bc(0xF, vf19, vf19, vf14, 1);  // vmuly.xyzw
                    vmul_bc(0xF, vf25, vf25, vf14, 2);  // vmulz.xyzw
                    vmul_bc(0xF, vf26, vf26, vf14, 3);  // vmulw.xyzw
                    vsub(0xF, vf21, vf20, vf18);  // vsub.xyzw
                    vadd(0xF, vf22, vf20, vf18);  // vadd.xyzw
                    vadd(0xF, vf23, vf20, vf18);  // vadd.xyzw
                    vsub(0xF, vf24, vf20, vf18);  // vsub.xyzw
                    vsub(0xF, vf21, vf21, vf19);  // vsub.xyzw
                    vsub(0xF, vf22, vf22, vf19);  // vsub.xyzw
                    vadd(0xF, vf23, vf23, vf19);  // vadd.xyzw
                    vadd(0xF, vf24, vf24, vf19);  // vadd.xyzw
                    vsub(0xF, vf28, vf27, vf25);  // vsub.xyzw
                    vadd(0xF, vf29, vf27, vf25);  // vadd.xyzw
                    vadd(0xF, vf30, vf27, vf25);  // vadd.xyzw
                    vsub(0xF, vf31, vf27, vf25);  // vsub.xyzw
                    vsub(0xF, vf28, vf28, vf26);  // vsub.xyzw
                    vsub(0xF, vf29, vf29, vf26);  // vsub.xyzw
                    vadd(0xF, vf30, vf30, vf26);  // vadd.xyzw
                    vadd(0xF, vf31, vf31, vf26);  // vadd.xyzw
                    sqc2(vf21, t7, 0);
                    sqc2(vf22, t7, 16);
                    sqc2(vf23, t7, 32);
                    sqc2(vf24, t7, 48);
                    sqc2(vf28, t7, 64);
                    sqc2(vf29, t7, 80);
                    sqc2(vf30, t7, 96);
                    sqc2(vf31, t7, 112);
                    ei(ctx);
                    a2 = addiu(a2, 2);
                    a0 = slt(a2, v1);
                    t8 = addiu(t8, 32);
                    t9 = addiu(t9, 16);
                    a3 = addiu(a3, 8);
                    t7 = addiu(t7, 128);
                    if (a0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0047f574
                charge(ctx, 1);
            }
            // 0x0047f578
            charge(ctx, 5);
            a0 = 0x10010000;
            lw(a1, a0, -12288);  // 0x1000D000 D8 fromSPR CHCR
            a1 = a1 & 0x100;
            if (a1 != 0) {
                // 0x0047f58c
                charge(ctx, 4);
                a1 = 256;
                sw(a1, a0, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x0047f59c
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x0047f5b8
            charge(ctx, 5);
            a0 = 0x10010000;
            lw(a1, a0, -11264);  // 0x1000D400 D9 toSPR CHCR
            a1 = a1 & 0x100;
            if (a1 != 0) {
                // 0x0047f5cc
                charge(ctx, 4);
                a1 = 512;
                sw(a1, a0, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x0047f5dc
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0047f5f8
                charge(ctx, 1);
                a0 = 0x10010000;
                for (;;) {
                    // 0x0047f5fc
                    charge(ctx, 7);
                    lw(a1, a0, -11264);
                    a1 = a1 & 0x100;
                    if (a1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x0047f618
            charge(ctx, 17);
            a3 = 256;
            a0 = 0x10010000;
            a2 = 4928;
            sw(a3, a0, -8176);  // 0x1000E010 D_STAT
            a1 = sll(v1, 2);
            sw(a2, a0, -12160);  // 0x1000D080 D8 fromSPR SADR
            sw(s1, a0, -12272);  // 0x1000D010 D8 fromSPR MADR
            sw(a1, a0, -12256);  // 0x1000D020 D8 fromSPR QWC
            sw(a3, a0, -12288);  // 0x1000D000 D8 fromSPR CHCR
            sync(ctx, 0);
            sync(ctx, 16);
            a0 = sll(a1, 4);
            a1 = sll(v1, 4);
            s1 = addu(s1, a0);
            s3 = addu(s3, a1);
            a0 = sra(v1, 2);
            if (i64(v1) < 0) {
                // 0x0047f65c
                charge(ctx, 2);
                a0 = addiu(v1, 3);
                a0 = sra(a0, 2);
            }
            // 0x0047f664
            charge(ctx, 4);
            a1 = sll(a0, 4);
            a0 = sra(v1, 1);
            s2 = addu(s2, a1);
            if (i64(v1) < 0) {
                // 0x0047f674
                charge(ctx, 2);
                a0 = addiu(v1, 1);
                a0 = sra(a0, 1);
            }
            // 0x0047f67c
            charge(ctx, 3);
            a0 = sll(a0, 4);
            s4 = subu(s4, v1);
            s0 = addu(s0, a0);
        }
        // 0x0047f688
        charge(ctx, 3);
        at = slt(0, s4);
        a2 = 0;
        if (at != 0) {
            // 0x0047f694
            charge(ctx, 3);
            lq(v1, sp, 0xA0);
            a1 = 0x10000;
            a0 = sll(v1, 2);
            for (;;) {
                // 0x0047f6a0
                charge(ctx, 8);
                lwc1(f0, s2, 0);
                swc1(f0, t6, 0);
                lwc1(f0, s0, 0);
                swc1(f0, t6, 4);
                lwc1(f0, s2, 0);
                swc1(f0, t6, 8);
                lwc1(f0, s0, 4);
                swc1(f0, t6, 12);
                for (;;) {
                    // 0x0047f6c0
                    charge(ctx, 7);
                    di(ctx);
                    sync(ctx, 16);
                    mfc0(v1, 12);
                    v1 = v1 & a1;
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0047f6dc
                charge(ctx, 55);
                lqc2(vf1, t6, 0);
                vabs(0xC, vf7, vf1);  // vabs.xy
                vadda_bc(0xF, vf0, vf10, 0);  // vaddax.xyzw
                vmsub_bc(0xC, vf7, vf7, vf0, 3);  // vmsubw.xy
                vadda_bc(0xE, vf0, vf10, 1);  // vadday.xyz
                vadda_bc(0x1, vf0, vf10, 2);  // vaddaz.w
                vmsub_bc(0x3, vf2, vf1, vf0, 3);  // vmsubw.zw
                vadda_bc(0xE, vf0, vf11, 0);  // vaddax.xyz
                vadda_bc(0x1, vf0, vf11, 1);  // vadday.w
                vmsub_bc(0x3, vf3, vf1, vf0, 3);  // vmsubw.zw
                vmini(0x3, vf2, vf1, vf2);  // vmini.zw
                vmax(0x3, vf7, vf2, vf3);  // vmax.zw
                vmul(0xF, vf2, vf7, vf7);  // vmul.xyzw
                vmul_bc(0xF, vf6, vf7, vf11, 2);  // vmulz.xyzw
                vmul_bc(0xF, vf4, vf7, vf12, 0);  // vmulx.xyzw
                vmul_bc(0xF, vf5, vf7, vf12, 1);  // vmuly.xyzw
                vmul(0xF, vf3, vf2, vf2);  // vmul.xyzw
                vmul(0xF, vf6, vf6, vf2);  // vmul.xyzw
                vmula(0xF, vf4, vf2);  // vmula.xyzw
                vmul_bc(0xF, vf4, vf7, vf12, 2);  // vmulz.xyzw
                vmul(0xF, vf2, vf3, vf3);  // vmul.xyzw
                vmadda(0xF, vf6, vf3);  // vmadda.xyzw
                vmadda(0xF, vf5, vf3);  // vmadda.xyzw
                vmadda_bc(0xF, vf7, vf13, 0);  // vmaddax.xyzw
                vmadd(0xF, vf7, vf4, vf2);  // vmadd.xyzw
                lqc2(vf20, s3, 0);
                vmula_bc(0xF, vf8, vf7, 0);  // vmulax.xyzw
                vmsub_bc(0xF, vf18, vf9, vf7, 2);  // vmsubz.xyzw
                vmul_bc(0xF, vf18, vf18, vf1, 1);  // vmuly.xyzw
                vmula_bc(0xF, vf9, vf7, 0);  // vmulax.xyzw
                vmadd_bc(0xF, vf19, vf8, vf7, 2);  // vmaddz.xyzw
                vmul_bc(0xF, vf19, vf19, vf1, 3);  // vmulw.xyzw
                vsub(0xF, vf21, vf20, vf18);  // vsub.xyzw
                vadd(0xF, vf22, vf20, vf18);  // vadd.xyzw
                vadd(0xF, vf23, vf20, vf18);  // vadd.xyzw
                vsub(0xF, vf24, vf20, vf18);  // vsub.xyzw
                vsub(0xF, vf21, vf21, vf19);  // vsub.xyzw
                vsub(0xF, vf22, vf22, vf19);  // vsub.xyzw
                vadd(0xF, vf23, vf23, vf19);  // vadd.xyzw
                vadd(0xF, vf24, vf24, vf19);  // vadd.xyzw
                sqc2(vf21, s1, 0);
                sqc2(vf22, s1, 16);
                sqc2(vf23, s1, 32);
                sqc2(vf24, s1, 48);
                ei(ctx);
                a2 = addiu(a2, 1);
                lq(v1, sp, 0xD0);
                s3 = addu(s3, v1);
                lq(v1, sp, 0xB0);
                s0 = addu(s0, v1);
                lq(v1, sp, 0xC0);
                s2 = addu(s2, v1);
                v1 = slt(a2, s4);
                s1 = addu(s1, a0);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0047f7b8
            charge(ctx, 2);
        }
    }
    // 0x0047fad8 (the shared epilogue, written out on this path)
    charge(ctx, 12);
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

// 0x0047FB10 sub_47FB10 -- 4376 bytes; frame 0x120: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// Scratchpad DMA kernel using the SPR matrices at 0x3F00 / 0x3F70 (memcpy of the parameters).
void sub_47FB10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, t8{ctx, 24}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23};
    Vf vf0{ctx, 0}, vf1{ctx, 1}, vf2{ctx, 2}, vf3{ctx, 3}, vf4{ctx, 4}, vf5{ctx, 5}, vf6{ctx, 6}, vf7{ctx, 7}, vf8{ctx, 8}, vf9{ctx, 9}, vf10{ctx, 10}, vf11{ctx, 11}, vf12{ctx, 12}, vf13{ctx, 13}, vf14{ctx, 14}, vf16{ctx, 16}, vf17{ctx, 17}, vf18{ctx, 18}, vf19{ctx, 19}, vf20{ctx, 20}, vf21{ctx, 21}, vf22{ctx, 22}, vf23{ctx, 23}, vf24{ctx, 24}, vf25{ctx, 25}, vf26{ctx, 26}, vf27{ctx, 27}, vf28{ctx, 28}, vf29{ctx, 29}, vf30{ctx, 30}, vf31{ctx, 31};
    // 0x0047fb10
    enter(ctx, 33);  // entry check point + this block's cycles
    sp = addiu(sp, -0x120);
    v0 = 0x3F000000;
    sd(ra, sp, 0xA0);
    mtc1(v0, f2);
    sq(fp, sp, 0x90);
    sq(s7, sp, 0x80);
    sq(s6, sp, 0x70);
    sq(s5, sp, 0x60);
    s6 = a1;
    sq(s4, sp, 0x50);
    s5 = a2;
    sq(s3, sp, 0x40);
    s4 = a3;
    sq(s2, sp, 0x30);
    s3 = t0;
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lwc1(f1, t0, 112);
    lw(v0, a0, 4);
    lwc1(f0, t0, 116);
    lw(s7, t0, 8);
    lw(s2, t0, 4);
    lw(s1, t0, 52);
    lw(fp, t0, 56);
    lw(s0, a0, 0);
    mul_s(f23, f2, f1);
    sq(v0, sp, 0xB0);
    mul_s(f22, f2, f0);
    if (s7 != v0) {
        // 0x00480860
        charge(ctx, 36);
        v0 = 0x3F800000;
        s6 = addiu(sp, 0x114);
        mtc1(v0, f1);
        a0 = addiu(sp, 0x100);
        lwc1(f0, s3, 104);
        a2 = 12;
        div_s(f21, f1, f23);
        mul_s(f0, f0, f21);
        swc1(f0, sp, 0x110);
        div_s(f20, f1, f22);
        lwc1(f0, s3, 108);
        mul_s(f0, f0, f20);
        link(ctx, 0x480890u);  // $ra first: the delay slot below depends on it
        swc1(f0, s6, 0);
        call(ctx, gen::fn_memcpy_00521250);
        a1 = s5;
        a0 = addiu(sp, 0xF0);
        a2 = 12;
        jal(ctx, 0x4808A0u, gen::fn_memcpy_00521250);
        lwc1(f1, s3, 104);
        v1 = 0x3F800000;
        mtc1(v1, f3);
        mtc1(zero, f0);
        lwc1(f2, s3, 108);
        v1 = 0x10000;
        adda_s(f0, f3);
        mul_s(f4, f1, f21);
        madd_s(f1, f1, f21);
        adda_s(f0, f3);
        sub_s(f0, f4, f3);
        swc1(f0, sp, 0x110);
        mul_s(f0, f2, f20);
        sub_s(f0, f0, f3);
        swc1(f0, s6, 0);
        madd_s(f0, f2, f20);
        swc1(f1, sp, 0x118);
        swc1(f0, sp, 0x11C);
        for (;;) {
            // 0x004808f0
            charge(ctx, 7);
            di(ctx);
            sync(ctx, 16);
            mfc0(a0, 12);
            a0 = a0 & v1;
            if (a0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0048090c
        charge(ctx, 87);
        at = 0x3FC90000;
        v1 = at | 0xFDB;
        mtc1(v1, f0);
        mfc1(v1, f0);
        ctc2(v1, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x8, vf10, vf0);  // vaddi.x
        at = 0x40490000;
        a0 = at | 0xFDB;
        mtc1(a0, f0);
        mfc1(v1, f0);
        ctc2(v1, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x4, vf10, vf0);  // vaddi.y
        at = 0x40090000;
        v1 = at | 0xFDB;
        mtc1(v1, f0);
        mfc1(v1, f0);
        ctc2(v1, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x2, vf10, vf0);  // vaddi.z
        mtc1(a0, f0);
        neg_s(f0, f0);
        mfc1(v1, f0);
        ctc2(v1, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x8, vf11, vf0);  // vaddi.x
        at = 0x40840000;
        v1 = at | 0x87ED;
        mtc1(v1, f0);
        neg_s(f0, f0);
        mfc1(v1, f0);
        ctc2(v1, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x4, vf11, vf0);  // vaddi.y
        v1 = 0x0;
        v1 = dsll(v1, 16);
        v1 = dsll(v1, 16);
        v1 = v1 | 0xB94F;
        v1 = dsll(v1, 16);
        v1 = v1 | 0xB21F;
        ctc2(v1, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x2, vf11, vf0);  // vaddi.z
        v1 = 0x0;
        v1 = dsll(v1, 16);
        v1 = dsll(v1, 16);
        v1 = v1 | 0xBE2A;
        v1 = dsll(v1, 16);
        v1 = v1 | 0xAAA4;
        ctc2(v1, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x8, vf12, vf0);  // vaddi.x
        at = 0x3C080000;
        v1 = at | 0x873E;
        ctc2(v1, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x4, vf12, vf0);  // vaddi.y
        at = 0x362E0000;
        v1 = at | 0x9C14;
        ctc2(v1, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x2, vf12, vf0);  // vaddi.z
        v1 = 0x3F800000;
        ctc2(v1, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x8, vf13, vf0);  // vaddi.x
        ei(ctx);
        v1 = 0x10000;
        swc1(f23, sp, 0xEC);
        swc1(f23, sp, 0xE8);
        swc1(f23, sp, 0xE4);
        swc1(f23, sp, 0xE0);
        swc1(f22, sp, 0xDC);
        swc1(f22, sp, 0xD8);
        swc1(f22, sp, 0xD4);
        swc1(f22, sp, 0xD0);
        for (;;) {
            // 0x00480a68
            charge(ctx, 7);
            di(ctx);
            sync(ctx, 16);
            mfc0(a0, 12);
            a0 = a0 & v1;
            if (a0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00480a84
        charge(ctx, 18);
        a3 = addiu(sp, 0x100);
        a2 = addiu(sp, 0xF0);
        a1 = addiu(sp, 0xE0);
        a0 = addiu(sp, 0xD0);
        v1 = addiu(sp, 0x110);
        lqc2(vf2, a3, 0);
        lqc2(vf4, a1, 0);
        lqc2(vf3, a2, 0);
        lqc2(vf5, a0, 0);
        lqc2(vf14, v1, 0);
        vmul(0xF, vf8, vf2, vf4);  // vmul.xyzw
        vmul(0xF, vf16, vf3, vf4);  // vmul.xyzw
        vmul(0xF, vf9, vf2, vf5);  // vmul.xyzw
        vmul(0xF, vf17, vf3, vf5);  // vmul.xyzw
        ei(ctx);
        at = slt(0, s4);
        t0 = 0;
        if (at != 0) {
            // 0x00480acc
            charge(ctx, 5);
            lq(v1, sp, 0xB0);
            a3 = addiu(sp, 0xC8);
            a1 = addiu(sp, 0xC0);
            a2 = 0x10000;
            a0 = sll(v1, 2);
            for (;;) {
                // 0x00480ae0
                charge(ctx, 4);
                lwc1(f0, s1, 0);
                swc1(f0, sp, 0xC0);
                swc1(f0, a3, 0);
                for (;;) {
                    // 0x00480af0
                    charge(ctx, 7);
                    di(ctx);
                    sync(ctx, 16);
                    mfc0(v1, 12);
                    v1 = v1 & a2;
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00480b0c
                charge(ctx, 55);
                lqc2(vf1, a1, 0);
                lqc2(vf20, s2, 0);
                vabs(0xC, vf7, vf1);  // vabs.xy
                vadda_bc(0xF, vf0, vf10, 0);  // vaddax.xyzw
                vmsub_bc(0xC, vf7, vf7, vf0, 3);  // vmsubw.xy
                vadda_bc(0xE, vf0, vf10, 1);  // vadday.xyz
                vadda_bc(0x1, vf0, vf10, 2);  // vaddaz.w
                vmsub_bc(0x3, vf2, vf1, vf0, 3);  // vmsubw.zw
                vadda_bc(0xE, vf0, vf11, 0);  // vaddax.xyz
                vadda_bc(0x1, vf0, vf11, 1);  // vadday.w
                vmsub_bc(0x3, vf3, vf1, vf0, 3);  // vmsubw.zw
                vmini(0x3, vf2, vf1, vf2);  // vmini.zw
                vmax(0x3, vf7, vf2, vf3);  // vmax.zw
                vmul(0xF, vf2, vf7, vf7);  // vmul.xyzw
                vmul_bc(0xF, vf6, vf7, vf11, 2);  // vmulz.xyzw
                vmul_bc(0xF, vf4, vf7, vf12, 0);  // vmulx.xyzw
                vmul_bc(0xF, vf5, vf7, vf12, 1);  // vmuly.xyzw
                vmul(0xF, vf3, vf2, vf2);  // vmul.xyzw
                vmul(0xF, vf6, vf6, vf2);  // vmul.xyzw
                vmula(0xF, vf4, vf2);  // vmula.xyzw
                vmul_bc(0xF, vf4, vf7, vf12, 2);  // vmulz.xyzw
                vmul(0xF, vf2, vf3, vf3);  // vmul.xyzw
                vmadda(0xF, vf6, vf3);  // vmadda.xyzw
                vmadda(0xF, vf5, vf3);  // vmadda.xyzw
                vmadda_bc(0xF, vf7, vf13, 0);  // vmaddax.xyzw
                vmadd(0xF, vf7, vf4, vf2);  // vmadd.xyzw
                vmul_bc(0xE, vf2, vf8, vf7, 0);  // vmulx.xyz
                vmul_bc(0xE, vf3, vf16, vf7, 2);  // vmulz.xyz
                vmul_bc(0xE, vf4, vf9, vf7, 2);  // vmulz.xyz
                vmul_bc(0xE, vf5, vf17, vf7, 0);  // vmulx.xyz
                vsub(0xF, vf18, vf2, vf3);  // vsub.xyzw
                vadd(0xF, vf19, vf4, vf5);  // vadd.xyzw
                vmula_bc(0xF, vf19, vf14, 1);  // vmulay.xyzw
                vmadda_bc(0xF, vf18, vf14, 0);  // vmaddax.xyzw
                vmadd_bc(0xF, vf21, vf20, vf0, 3);  // vmaddw.xyzw
                vmula_bc(0xF, vf19, vf14, 1);  // vmulay.xyzw
                vmadda_bc(0xF, vf18, vf14, 2);  // vmaddaz.xyzw
                vmadd_bc(0xF, vf22, vf20, vf0, 3);  // vmaddw.xyzw
                vmula_bc(0xF, vf19, vf14, 3);  // vmulaw.xyzw
                vmadda_bc(0xF, vf18, vf14, 2);  // vmaddaz.xyzw
                vmadd_bc(0xF, vf23, vf20, vf0, 3);  // vmaddw.xyzw
                vmula_bc(0xF, vf19, vf14, 3);  // vmulaw.xyzw
                vmadda_bc(0xF, vf18, vf14, 0);  // vmaddax.xyzw
                vmadd_bc(0xF, vf24, vf20, vf0, 3);  // vmaddw.xyzw
                sqc2(vf21, s0, 0);
                sqc2(vf22, s0, 16);
                sqc2(vf23, s0, 32);
                sqc2(vf24, s0, 48);
                ei(ctx);
                t0 = addiu(t0, 1);
                v1 = slt(t0, s4);
                s2 = addu(s2, s7);
                s1 = addu(s1, fp);
                s0 = addu(s0, a0);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
    } else {
        // 0x0047fb94
        charge(ctx, 7);
        a0 = 0;
        jal(ctx, 0x47FB94u, gen::fn__sceFlushCache_005033e0);
        v1 = 0x10010000;
        lw(a0, v1, -12288);  // 0x1000D000 D8 fromSPR CHCR
        a0 = a0 & 0x100;
        if (a0 != 0) {
            // 0x0047fbb0
            charge(ctx, 4);
            a0 = 256;
            sw(a0, v1, -8160);
            sync(ctx, 0);
            sync(ctx, 16);
            for (;;) {
                // 0x0047fbc0
                charge(ctx, 7);
                if (cop0_cond(ctx)) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x0047fbdc
        charge(ctx, 5);
        v1 = 0x10010000;
        lw(a0, v1, -11264);  // 0x1000D400 D9 toSPR CHCR
        a0 = a0 & 0x100;
        if (a0 != 0) {
            // 0x0047fbf0
            charge(ctx, 4);
            a0 = 512;
            sw(a0, v1, -8160);
            sync(ctx, 0);
            sync(ctx, 16);
            for (;;) {
                // 0x0047fc00
                charge(ctx, 7);
                if (cop0_cond(ctx)) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0047fc1c
            charge(ctx, 1);
            v1 = 0x10010000;
            for (;;) {
                // 0x0047fc20
                charge(ctx, 7);
                lw(a0, v1, -11264);
                a0 = a0 & 0x100;
                if (a0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0047fc3c
            charge(ctx, 1);
        }
        // 0x0047fc40
        charge(ctx, 42);
        v1 = 0x3F800000;
        mtc1(v1, f4);
        t0 = 0x70000000;
        lwc1(f0, s3, 104);
        a2 = t0 | 0x3F00;
        div_s(f3, f4, f23);
        a1 = t0 | 0x3F10;
        a0 = t0 | 0x3F70;
        v1 = t0 | 0x3F20;
        t2 = t0 | 0x3F30;
        t1 = t0 | 0x3F40;
        a3 = 0x10000;
        mul_s(f0, f0, f3);
        sub_s(f0, f0, f4);
        swc1(f0, t0, 16240);  // 0x70003F70 SPR+0x3F70
        div_s(f2, f4, f22);
        lwc1(f1, s3, 108);
        mtc1(zero, f0);
        adda_s(f0, f4);
        mul_s(f1, f1, f2);
        sub_s(f1, f1, f4);
        swc1(f1, t0, 16244);  // 0x70003F74 SPR+0x3F74
        lwc1(f1, s3, 104);
        madd_s(f1, f1, f3);
        adda_s(f0, f4);
        swc1(f1, t0, 16248);  // 0x70003F78 SPR+0x3F78
        lwc1(f0, s3, 108);
        madd_s(f0, f0, f2);
        swc1(f0, t0, 16252);  // 0x70003F7C SPR+0x3F7C
        lwc1(f2, s6, 0);
        lwc1(f1, s6, 4);
        lwc1(f0, s6, 8);
        swc1(f2, a2, 0);  // 0x70003F00 SPR+0x3F00
        swc1(f1, a2, 4);  // 0x70003F04 SPR+0x3F04
        swc1(f0, a2, 8);  // 0x70003F08 SPR+0x3F08
        lwc1(f2, s5, 0);
        lwc1(f1, s5, 4);
        lwc1(f0, s5, 8);
        swc1(f2, a1, 0);  // 0x70003F10 SPR+0x3F10
        swc1(f1, a1, 4);  // 0x70003F14 SPR+0x3F14
        swc1(f0, a1, 8);  // 0x70003F18 SPR+0x3F18
        for (;;) {
            // 0x0047fce8
            charge(ctx, 7);
            di(ctx);
            sync(ctx, 16);
            mfc0(t0, 12);
            t0 = t0 & a3;
            if (t0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0047fd04
        charge(ctx, 88);
        at = 0x3FC90000;
        a3 = at | 0xFDB;
        mtc1(a3, f0);
        mfc1(a3, f0);
        ctc2(a3, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x8, vf10, vf0);  // vaddi.x
        at = 0x40490000;
        t0 = at | 0xFDB;
        mtc1(t0, f0);
        mfc1(a3, f0);
        ctc2(a3, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x4, vf10, vf0);  // vaddi.y
        at = 0x40090000;
        a3 = at | 0xFDB;
        mtc1(a3, f0);
        mfc1(a3, f0);
        ctc2(a3, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x2, vf10, vf0);  // vaddi.z
        mtc1(t0, f0);
        neg_s(f0, f0);
        mfc1(a3, f0);
        ctc2(a3, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x8, vf11, vf0);  // vaddi.x
        at = 0x40840000;
        a3 = at | 0x87ED;
        mtc1(a3, f0);
        neg_s(f0, f0);
        mfc1(a3, f0);
        ctc2(a3, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x4, vf11, vf0);  // vaddi.y
        a3 = 0x0;
        a3 = dsll(a3, 16);
        a3 = dsll(a3, 16);
        a3 = a3 | 0xB94F;
        a3 = dsll(a3, 16);
        a3 = a3 | 0xB21F;
        ctc2(a3, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x2, vf11, vf0);  // vaddi.z
        a3 = 0x0;
        a3 = dsll(a3, 16);
        a3 = dsll(a3, 16);
        a3 = a3 | 0xBE2A;
        a3 = dsll(a3, 16);
        a3 = a3 | 0xAAA4;
        ctc2(a3, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x8, vf12, vf0);  // vaddi.x
        at = 0x3C080000;
        a3 = at | 0x873E;
        ctc2(a3, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x4, vf12, vf0);  // vaddi.y
        at = 0x362E0000;
        a3 = at | 0x9C14;
        ctc2(a3, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x2, vf12, vf0);  // vaddi.z
        a3 = 0x3F800000;
        ctc2(a3, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x8, vf13, vf0);  // vaddi.x
        ei(ctx);
        a3 = 0x70000000;
        swc1(f23, a3, 16188);  // 0x70003F3C SPR+0x3F3C
        t0 = 0x10000;
        swc1(f23, a3, 16184);  // 0x70003F38 SPR+0x3F38
        swc1(f23, a3, 16180);  // 0x70003F34 SPR+0x3F34
        swc1(f23, a3, 16176);  // 0x70003F30 SPR+0x3F30
        swc1(f22, a3, 16204);  // 0x70003F4C SPR+0x3F4C
        swc1(f22, a3, 16200);  // 0x70003F48 SPR+0x3F48
        swc1(f22, a3, 16196);  // 0x70003F44 SPR+0x3F44
        swc1(f22, a3, 16192);  // 0x70003F40 SPR+0x3F40
        for (;;) {
            // 0x0047fe64
            charge(ctx, 7);
            di(ctx);
            sync(ctx, 16);
            mfc0(a3, 12);
            a3 = a3 & t0;
            if (a3 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0047fe80
        charge(ctx, 13);
        lqc2(vf2, a2, 0);
        lqc2(vf4, t2, 0);
        lqc2(vf3, a1, 0);
        lqc2(vf5, t1, 0);
        lqc2(vf14, a0, 0);
        vmul(0xF, vf8, vf2, vf4);  // vmul.xyzw
        vmul(0xF, vf16, vf3, vf4);  // vmul.xyzw
        vmul(0xF, vf9, vf2, vf5);  // vmul.xyzw
        vmul(0xF, vf17, vf3, vf5);  // vmul.xyzw
        ei(ctx);
        a0 = slti(s4, 192);
        if (a0 == 0) {
            // 0x0047feb4
            charge(ctx, 11);
            t6 = 0x70000000;
            t0 = 0x10010000;
            t3 = 0x10000;
            t8 = 256;
            s6 = 512;
            s5 = 48;
            s3 = 768;
            t7 = 192;
            t5 = t6 | 0x300;
            t4 = t6 | 0xF00;
            t1 = 3840;
            for (;;) {
                // 0x0047fee0
                charge(ctx, 4);
                lw(a0, t0, -12288);
                a0 = a0 & 0x100;
                if (a0 != 0) {
                    // 0x0047fef0
                    charge(ctx, 4);
                    sw(t8, t0, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x0047ff00
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047ff1c
                    charge(ctx, 1);
                }
                // 0x0047ff20
                charge(ctx, 4);
                lw(a0, t0, -11264);
                a0 = a0 & 0x100;
                if (a0 != 0) {
                    // 0x0047ff30
                    charge(ctx, 4);
                    sw(s6, t0, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x0047ff40
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047ff5c
                    charge(ctx, 1);
                    for (;;) {
                        // 0x0047ff60
                        charge(ctx, 7);
                        lw(a0, t0, -11264);
                        a0 = a0 & 0x100;
                        if (a0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047ff7c
                    charge(ctx, 1);
                }
                // 0x0047ff80
                charge(ctx, 11);
                sw(s6, t0, -8176);
                sw(zero, t0, -11136);
                sw(s1, t0, -11248);
                sw(s5, t0, -11232);
                sw(t8, t0, -11264);
                sync(ctx, 0);
                sync(ctx, 16);
                lw(a0, t0, -11264);
                a0 = a0 & 0x100;
                if (a0 != 0) {
                    // 0x0047ffac
                    charge(ctx, 3);
                    sw(s6, t0, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x0047ffb8
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047ffd4
                    charge(ctx, 1);
                    for (;;) {
                        // 0x0047ffd8
                        charge(ctx, 7);
                        lw(a0, t0, -11264);
                        a0 = a0 & 0x100;
                        if (a0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047fff4
                    charge(ctx, 1);
                }
                // 0x0047fff8
                charge(ctx, 11);
                sw(s6, t0, -8176);
                sw(s3, t0, -11136);
                sw(s2, t0, -11248);
                sw(t7, t0, -11232);
                sw(t8, t0, -11264);
                sync(ctx, 0);
                sync(ctx, 16);
                lw(a0, t0, -11264);
                a0 = a0 & 0x100;
                if (a0 != 0) {
                    // 0x00480024
                    charge(ctx, 3);
                    sw(s6, t0, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x00480030
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0048004c
                    charge(ctx, 1);
                    for (;;) {
                        // 0x00480050
                        charge(ctx, 7);
                        lw(a0, t0, -11264);
                        a0 = a0 & 0x100;
                        if (a0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0048006c
                    charge(ctx, 1);
                }
                // 0x00480070
                charge(ctx, 4);
                a2 = t6;
                a1 = t5;
                a0 = t4;
                a3 = 0;
                for (;;) {
                    // 0x00480080
                    charge(ctx, 8);
                    lwc1(f0, a2, 0);
                    swc1(f0, v1, 0);
                    lwc1(f0, a2, 4);
                    swc1(f0, v1, 4);
                    lwc1(f0, a2, 0);
                    swc1(f0, v1, 8);
                    lwc1(f0, a2, 4);
                    swc1(f0, v1, 12);
                    for (;;) {
                        // 0x004800a0
                        charge(ctx, 7);
                        di(ctx);
                        sync(ctx, 16);
                        mfc0(t2, 12);
                        t2 = t2 & t3;
                        if (t2 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004800bc
                    charge(ctx, 78);
                    lqc2(vf1, v1, 0);
                    lqc2(vf20, a1, 0);
                    lqc2(vf27, a1, 16);
                    vabs(0xC, vf7, vf1);  // vabs.xy
                    vadda_bc(0xF, vf0, vf10, 0);  // vaddax.xyzw
                    vmsub_bc(0xC, vf7, vf7, vf0, 3);  // vmsubw.xy
                    vadda_bc(0xE, vf0, vf10, 1);  // vadday.xyz
                    vadda_bc(0x1, vf0, vf10, 2);  // vaddaz.w
                    vmsub_bc(0x3, vf2, vf1, vf0, 3);  // vmsubw.zw
                    vadda_bc(0xE, vf0, vf11, 0);  // vaddax.xyz
                    vadda_bc(0x1, vf0, vf11, 1);  // vadday.w
                    vmsub_bc(0x3, vf3, vf1, vf0, 3);  // vmsubw.zw
                    vmini(0x3, vf2, vf1, vf2);  // vmini.zw
                    vmax(0x3, vf7, vf2, vf3);  // vmax.zw
                    vmul(0xF, vf2, vf7, vf7);  // vmul.xyzw
                    vmul_bc(0xF, vf6, vf7, vf11, 2);  // vmulz.xyzw
                    vmul_bc(0xF, vf4, vf7, vf12, 0);  // vmulx.xyzw
                    vmul_bc(0xF, vf5, vf7, vf12, 1);  // vmuly.xyzw
                    vmul(0xF, vf3, vf2, vf2);  // vmul.xyzw
                    vmul(0xF, vf6, vf6, vf2);  // vmul.xyzw
                    vmula(0xF, vf4, vf2);  // vmula.xyzw
                    vmul_bc(0xF, vf4, vf7, vf12, 2);  // vmulz.xyzw
                    vmul(0xF, vf2, vf3, vf3);  // vmul.xyzw
                    vmadda(0xF, vf6, vf3);  // vmadda.xyzw
                    vmadda(0xF, vf5, vf3);  // vmadda.xyzw
                    vmadda_bc(0xF, vf7, vf13, 0);  // vmaddax.xyzw
                    vmadd(0xF, vf7, vf4, vf2);  // vmadd.xyzw
                    vmul_bc(0xE, vf2, vf8, vf7, 0);  // vmulx.xyz
                    vmul_bc(0xE, vf3, vf16, vf7, 2);  // vmulz.xyz
                    vmul_bc(0xE, vf4, vf9, vf7, 2);  // vmulz.xyz
                    vmul_bc(0xE, vf5, vf17, vf7, 0);  // vmulx.xyz
                    vsub(0xF, vf18, vf2, vf3);  // vsub.xyzw
                    vmul_bc(0xE, vf2, vf8, vf7, 1);  // vmuly.xyz
                    vmul_bc(0xE, vf3, vf16, vf7, 3);  // vmulw.xyz
                    vadd(0xF, vf19, vf4, vf5);  // vadd.xyzw
                    vmul_bc(0xE, vf4, vf9, vf7, 3);  // vmulw.xyz
                    vmul_bc(0xE, vf5, vf17, vf7, 1);  // vmuly.xyz
                    vsub(0xF, vf25, vf2, vf3);  // vsub.xyzw
                    vmula_bc(0xF, vf19, vf14, 1);  // vmulay.xyzw
                    vmadda_bc(0xF, vf18, vf14, 0);  // vmaddax.xyzw
                    vmadd_bc(0xF, vf21, vf20, vf0, 3);  // vmaddw.xyzw
                    vadd(0xF, vf26, vf4, vf5);  // vadd.xyzw
                    vmula_bc(0xF, vf19, vf14, 1);  // vmulay.xyzw
                    vmadda_bc(0xF, vf18, vf14, 2);  // vmaddaz.xyzw
                    vmadd_bc(0xF, vf22, vf20, vf0, 3);  // vmaddw.xyzw
                    vmula_bc(0xF, vf19, vf14, 3);  // vmulaw.xyzw
                    vmadda_bc(0xF, vf18, vf14, 2);  // vmaddaz.xyzw
                    vmadd_bc(0xF, vf23, vf20, vf0, 3);  // vmaddw.xyzw
                    vmula_bc(0xF, vf19, vf14, 3);  // vmulaw.xyzw
                    vmadda_bc(0xF, vf18, vf14, 0);  // vmaddax.xyzw
                    vmadd_bc(0xF, vf24, vf20, vf0, 3);  // vmaddw.xyzw
                    vmula_bc(0xF, vf26, vf14, 1);  // vmulay.xyzw
                    vmadda_bc(0xF, vf25, vf14, 0);  // vmaddax.xyzw
                    vmadd_bc(0xF, vf28, vf27, vf0, 3);  // vmaddw.xyzw
                    vmula_bc(0xF, vf26, vf14, 1);  // vmulay.xyzw
                    vmadda_bc(0xF, vf25, vf14, 2);  // vmaddaz.xyzw
                    vmadd_bc(0xF, vf29, vf27, vf0, 3);  // vmaddw.xyzw
                    vmula_bc(0xF, vf26, vf14, 3);  // vmulaw.xyzw
                    vmadda_bc(0xF, vf25, vf14, 2);  // vmaddaz.xyzw
                    vmadd_bc(0xF, vf30, vf27, vf0, 3);  // vmaddw.xyzw
                    vmula_bc(0xF, vf26, vf14, 3);  // vmulaw.xyzw
                    vmadda_bc(0xF, vf25, vf14, 0);  // vmaddax.xyzw
                    vmadd_bc(0xF, vf31, vf27, vf0, 3);  // vmaddw.xyzw
                    sqc2(vf21, a0, 0);
                    sqc2(vf22, a0, 16);
                    sqc2(vf23, a0, 32);
                    sqc2(vf24, a0, 48);
                    sqc2(vf28, a0, 64);
                    sqc2(vf29, a0, 80);
                    sqc2(vf30, a0, 96);
                    sqc2(vf31, a0, 112);
                    ei(ctx);
                    a3 = addiu(a3, 2);
                    t2 = slti(a3, 192);
                    a1 = addiu(a1, 32);
                    a2 = addiu(a2, 8);
                    a0 = addiu(a0, 128);
                    if (t2 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004801f4
                charge(ctx, 4);
                lw(a0, t0, -12288);
                a0 = a0 & 0x100;
                if (a0 != 0) {
                    // 0x00480204
                    charge(ctx, 3);
                    sw(t8, t0, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x00480210
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0048022c
                    charge(ctx, 1);
                }
                // 0x00480230
                charge(ctx, 4);
                lw(a0, t0, -11264);
                a0 = a0 & 0x100;
                if (a0 != 0) {
                    // 0x00480240
                    charge(ctx, 4);
                    sw(s6, t0, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x00480250
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0048026c
                    charge(ctx, 1);
                    for (;;) {
                        // 0x00480270
                        charge(ctx, 7);
                        lw(a0, t0, -11264);
                        a0 = a0 & 0x100;
                        if (a0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0048028c
                    charge(ctx, 1);
                }
                // 0x00480290
                charge(ctx, 13);
                sw(t8, t0, -8176);
                sw(t1, t0, -12160);
                sw(s0, t0, -12272);
                sw(s3, t0, -12256);
                sw(t8, t0, -12288);
                sync(ctx, 0);
                sync(ctx, 16);
                s4 = addiu(s4, -192);
                s2 = addiu(s2, 3072);
                at = slti(s4, 192);
                s0 = addiu(s0, 12288);
                s1 = addiu(s1, 768);
                if (at != 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004802c4
            charge(ctx, 1);
        }
        // 0x004802c8
        charge(ctx, 3);
        at = slti(s4, 4);
        if (at == 0) {
            // 0x004802d4
            charge(ctx, 2);
            a0 = sra(s4, 2);
            if (i64(s4) < 0) {
                // 0x004802dc
                charge(ctx, 2);
                a0 = addiu(s4, 3);
                a0 = sra(a0, 2);
            }
            // 0x004802e4
            charge(ctx, 6);
            a2 = sll(a0, 2);
            a0 = 0x10010000;
            lw(a1, a0, -12288);  // 0x1000D000 D8 fromSPR CHCR
            a1 = a1 & 0x100;
            if (a1 != 0) {
                // 0x004802fc
                charge(ctx, 4);
                a1 = 256;
                sw(a1, a0, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x0048030c
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x00480328
            charge(ctx, 5);
            a0 = 0x10010000;
            lw(a1, a0, -11264);  // 0x1000D400 D9 toSPR CHCR
            a1 = a1 & 0x100;
            if (a1 != 0) {
                // 0x0048033c
                charge(ctx, 4);
                a1 = 512;
                sw(a1, a0, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x0048034c
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00480368
                charge(ctx, 1);
                a0 = 0x10010000;
                for (;;) {
                    // 0x0048036c
                    charge(ctx, 7);
                    lw(a1, a0, -11264);
                    a1 = a1 & 0x100;
                    if (a1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x00480388
            charge(ctx, 7);
            a1 = 512;
            a0 = 0x10010000;
            a3 = sra(a2, 2);
            sw(a1, a0, -8176);  // 0x1000E010 D_STAT
            sw(zero, a0, -11136);  // 0x1000D480 D9 toSPR SADR
            sw(s1, a0, -11248);  // 0x1000D410 D9 toSPR MADR
            if (i64(a2) < 0) {
                // 0x004803a4
                charge(ctx, 2);
                a0 = addiu(a2, 3);
                a3 = sra(a0, 2);
            }
            // 0x004803ac
            charge(ctx, 10);
            a0 = 0x10010000;
            a1 = 256;
            sw(a3, a0, -11232);  // 0x1000D420 D9 toSPR QWC
            sw(a1, a0, -11264);  // 0x1000D400 D9 toSPR CHCR
            sync(ctx, 0);
            sync(ctx, 16);
            lw(a1, a0, -11264);  // 0x1000D400 D9 toSPR CHCR
            a1 = a1 & 0x100;
            if (a1 != 0) {
                // 0x004803d4
                charge(ctx, 4);
                a1 = 512;
                sw(a1, a0, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x004803e4
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00480400
                charge(ctx, 1);
                a0 = 0x10010000;
                for (;;) {
                    // 0x00480404
                    charge(ctx, 7);
                    lw(a1, a0, -11264);
                    a1 = a1 & 0x100;
                    if (a1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x00480420
            charge(ctx, 15);
            t0 = 512;
            a0 = 0x10010000;
            a3 = 768;
            sw(t0, a0, -8176);  // 0x1000E010 D_STAT
            a1 = 256;
            sw(a3, a0, -11136);  // 0x1000D480 D9 toSPR SADR
            sw(s2, a0, -11248);  // 0x1000D410 D9 toSPR MADR
            sw(a2, a0, -11232);  // 0x1000D420 D9 toSPR QWC
            sw(a1, a0, -11264);  // 0x1000D400 D9 toSPR CHCR
            sync(ctx, 0);
            sync(ctx, 16);
            lw(a1, a0, -11264);  // 0x1000D400 D9 toSPR CHCR
            a1 = a1 & 0x100;
            if (a1 != 0) {
                // 0x0048045c
                charge(ctx, 3);
                sw(t0, a0, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x00480468
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00480484
                charge(ctx, 1);
                a0 = 0x10010000;
                for (;;) {
                    // 0x00480488
                    charge(ctx, 7);
                    lw(a1, a0, -11264);
                    a1 = a1 & 0x100;
                    if (a1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004804a4
                charge(ctx, 1);
            }
            // 0x004804a8
            charge(ctx, 6);
            t2 = 0x70000000;
            at = slt(0, a2);
            a1 = t2 | 0x300;
            a0 = t2 | 0xF00;
            t1 = 0;
            if (at != 0) {
                // 0x004804c0
                charge(ctx, 1);
                t0 = 0x10000;
                for (;;) {
                    // 0x004804c4
                    charge(ctx, 9);
                    lwc1(f0, t2, 0);
                    swc1(f0, v1, 0);
                    lwc1(f0, t2, 4);
                    swc1(f0, v1, 4);
                    lwc1(f0, t2, 0);
                    swc1(f0, v1, 8);
                    lwc1(f0, t2, 4);
                    swc1(f0, v1, 12);
                    for (;;) {
                        // 0x004804e8
                        charge(ctx, 7);
                        di(ctx);
                        sync(ctx, 16);
                        mfc0(a3, 12);
                        a3 = a3 & t0;
                        if (a3 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00480504
                    charge(ctx, 78);
                    lqc2(vf1, v1, 0);
                    lqc2(vf20, a1, 0);
                    lqc2(vf27, a1, 16);
                    vabs(0xC, vf7, vf1);  // vabs.xy
                    vadda_bc(0xF, vf0, vf10, 0);  // vaddax.xyzw
                    vmsub_bc(0xC, vf7, vf7, vf0, 3);  // vmsubw.xy
                    vadda_bc(0xE, vf0, vf10, 1);  // vadday.xyz
                    vadda_bc(0x1, vf0, vf10, 2);  // vaddaz.w
                    vmsub_bc(0x3, vf2, vf1, vf0, 3);  // vmsubw.zw
                    vadda_bc(0xE, vf0, vf11, 0);  // vaddax.xyz
                    vadda_bc(0x1, vf0, vf11, 1);  // vadday.w
                    vmsub_bc(0x3, vf3, vf1, vf0, 3);  // vmsubw.zw
                    vmini(0x3, vf2, vf1, vf2);  // vmini.zw
                    vmax(0x3, vf7, vf2, vf3);  // vmax.zw
                    vmul(0xF, vf2, vf7, vf7);  // vmul.xyzw
                    vmul_bc(0xF, vf6, vf7, vf11, 2);  // vmulz.xyzw
                    vmul_bc(0xF, vf4, vf7, vf12, 0);  // vmulx.xyzw
                    vmul_bc(0xF, vf5, vf7, vf12, 1);  // vmuly.xyzw
                    vmul(0xF, vf3, vf2, vf2);  // vmul.xyzw
                    vmul(0xF, vf6, vf6, vf2);  // vmul.xyzw
                    vmula(0xF, vf4, vf2);  // vmula.xyzw
                    vmul_bc(0xF, vf4, vf7, vf12, 2);  // vmulz.xyzw
                    vmul(0xF, vf2, vf3, vf3);  // vmul.xyzw
                    vmadda(0xF, vf6, vf3);  // vmadda.xyzw
                    vmadda(0xF, vf5, vf3);  // vmadda.xyzw
                    vmadda_bc(0xF, vf7, vf13, 0);  // vmaddax.xyzw
                    vmadd(0xF, vf7, vf4, vf2);  // vmadd.xyzw
                    vmul_bc(0xE, vf2, vf8, vf7, 0);  // vmulx.xyz
                    vmul_bc(0xE, vf3, vf16, vf7, 2);  // vmulz.xyz
                    vmul_bc(0xE, vf4, vf9, vf7, 2);  // vmulz.xyz
                    vmul_bc(0xE, vf5, vf17, vf7, 0);  // vmulx.xyz
                    vsub(0xF, vf18, vf2, vf3);  // vsub.xyzw
                    vmul_bc(0xE, vf2, vf8, vf7, 1);  // vmuly.xyz
                    vmul_bc(0xE, vf3, vf16, vf7, 3);  // vmulw.xyz
                    vadd(0xF, vf19, vf4, vf5);  // vadd.xyzw
                    vmul_bc(0xE, vf4, vf9, vf7, 3);  // vmulw.xyz
                    vmul_bc(0xE, vf5, vf17, vf7, 1);  // vmuly.xyz
                    vsub(0xF, vf25, vf2, vf3);  // vsub.xyzw
                    vmula_bc(0xF, vf19, vf14, 1);  // vmulay.xyzw
                    vmadda_bc(0xF, vf18, vf14, 0);  // vmaddax.xyzw
                    vmadd_bc(0xF, vf21, vf20, vf0, 3);  // vmaddw.xyzw
                    vadd(0xF, vf26, vf4, vf5);  // vadd.xyzw
                    vmula_bc(0xF, vf19, vf14, 1);  // vmulay.xyzw
                    vmadda_bc(0xF, vf18, vf14, 2);  // vmaddaz.xyzw
                    vmadd_bc(0xF, vf22, vf20, vf0, 3);  // vmaddw.xyzw
                    vmula_bc(0xF, vf19, vf14, 3);  // vmulaw.xyzw
                    vmadda_bc(0xF, vf18, vf14, 2);  // vmaddaz.xyzw
                    vmadd_bc(0xF, vf23, vf20, vf0, 3);  // vmaddw.xyzw
                    vmula_bc(0xF, vf19, vf14, 3);  // vmulaw.xyzw
                    vmadda_bc(0xF, vf18, vf14, 0);  // vmaddax.xyzw
                    vmadd_bc(0xF, vf24, vf20, vf0, 3);  // vmaddw.xyzw
                    vmula_bc(0xF, vf26, vf14, 1);  // vmulay.xyzw
                    vmadda_bc(0xF, vf25, vf14, 0);  // vmaddax.xyzw
                    vmadd_bc(0xF, vf28, vf27, vf0, 3);  // vmaddw.xyzw
                    vmula_bc(0xF, vf26, vf14, 1);  // vmulay.xyzw
                    vmadda_bc(0xF, vf25, vf14, 2);  // vmaddaz.xyzw
                    vmadd_bc(0xF, vf29, vf27, vf0, 3);  // vmaddw.xyzw
                    vmula_bc(0xF, vf26, vf14, 3);  // vmulaw.xyzw
                    vmadda_bc(0xF, vf25, vf14, 2);  // vmaddaz.xyzw
                    vmadd_bc(0xF, vf30, vf27, vf0, 3);  // vmaddw.xyzw
                    vmula_bc(0xF, vf26, vf14, 3);  // vmulaw.xyzw
                    vmadda_bc(0xF, vf25, vf14, 0);  // vmaddax.xyzw
                    vmadd_bc(0xF, vf31, vf27, vf0, 3);  // vmaddw.xyzw
                    sqc2(vf21, a0, 0);
                    sqc2(vf22, a0, 16);
                    sqc2(vf23, a0, 32);
                    sqc2(vf24, a0, 48);
                    sqc2(vf28, a0, 64);
                    sqc2(vf29, a0, 80);
                    sqc2(vf30, a0, 96);
                    sqc2(vf31, a0, 112);
                    ei(ctx);
                    t1 = addiu(t1, 2);
                    a3 = slt(t1, a2);
                    a1 = addiu(a1, 32);
                    t2 = addiu(t2, 8);
                    a0 = addiu(a0, 128);
                    if (a3 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0048063c
                charge(ctx, 1);
            }
            // 0x00480640
            charge(ctx, 5);
            a0 = 0x10010000;
            lw(a1, a0, -12288);  // 0x1000D000 D8 fromSPR CHCR
            a1 = a1 & 0x100;
            if (a1 != 0) {
                // 0x00480654
                charge(ctx, 4);
                a1 = 256;
                sw(a1, a0, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x00480664
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x00480680
            charge(ctx, 5);
            a0 = 0x10010000;
            lw(a1, a0, -11264);  // 0x1000D400 D9 toSPR CHCR
            a1 = a1 & 0x100;
            if (a1 != 0) {
                // 0x00480694
                charge(ctx, 4);
                a1 = 512;
                sw(a1, a0, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x004806a4
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004806c0
                charge(ctx, 1);
                a0 = 0x10010000;
                for (;;) {
                    // 0x004806c4
                    charge(ctx, 7);
                    lw(a1, a0, -11264);
                    a1 = a1 & 0x100;
                    if (a1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x004806e0
            charge(ctx, 17);
            t0 = 256;
            a0 = 0x10010000;
            a3 = 3840;
            sw(t0, a0, -8176);  // 0x1000E010 D_STAT
            a1 = sll(a2, 2);
            sw(a3, a0, -12160);  // 0x1000D080 D8 fromSPR SADR
            sw(s0, a0, -12272);  // 0x1000D010 D8 fromSPR MADR
            sw(a1, a0, -12256);  // 0x1000D020 D8 fromSPR QWC
            sw(t0, a0, -12288);  // 0x1000D000 D8 fromSPR CHCR
            sync(ctx, 0);
            sync(ctx, 16);
            a0 = sll(a1, 4);
            a1 = sll(a2, 4);
            s0 = addu(s0, a0);
            s2 = addu(s2, a1);
            a0 = sra(a2, 2);
            if (i64(a2) < 0) {
                // 0x00480724
                charge(ctx, 2);
                a0 = addiu(a2, 3);
                a0 = sra(a0, 2);
            }
            // 0x0048072c
            charge(ctx, 3);
            a0 = sll(a0, 4);
            s4 = subu(s4, a2);
            s1 = addu(s1, a0);
        }
        // 0x00480738
        charge(ctx, 3);
        at = slt(0, s4);
        a3 = 0;
        if (at != 0) {
            // 0x00480744
            charge(ctx, 3);
            lq(a0, sp, 0xB0);
            a2 = 0x10000;
            a1 = sll(a0, 2);
            for (;;) {
                // 0x00480750
                charge(ctx, 4);
                lwc1(f0, s1, 0);
                swc1(f0, v1, 0);
                lwc1(f0, s1, 0);
                swc1(f0, v1, 8);
                for (;;) {
                    // 0x00480760
                    charge(ctx, 7);
                    di(ctx);
                    sync(ctx, 16);
                    mfc0(a0, 12);
                    a0 = a0 & a2;
                    if (a0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0048077c
                charge(ctx, 55);
                lqc2(vf1, v1, 0);
                lqc2(vf20, s2, 0);
                vabs(0xC, vf7, vf1);  // vabs.xy
                vadda_bc(0xF, vf0, vf10, 0);  // vaddax.xyzw
                vmsub_bc(0xC, vf7, vf7, vf0, 3);  // vmsubw.xy
                vadda_bc(0xE, vf0, vf10, 1);  // vadday.xyz
                vadda_bc(0x1, vf0, vf10, 2);  // vaddaz.w
                vmsub_bc(0x3, vf2, vf1, vf0, 3);  // vmsubw.zw
                vadda_bc(0xE, vf0, vf11, 0);  // vaddax.xyz
                vadda_bc(0x1, vf0, vf11, 1);  // vadday.w
                vmsub_bc(0x3, vf3, vf1, vf0, 3);  // vmsubw.zw
                vmini(0x3, vf2, vf1, vf2);  // vmini.zw
                vmax(0x3, vf7, vf2, vf3);  // vmax.zw
                vmul(0xF, vf2, vf7, vf7);  // vmul.xyzw
                vmul_bc(0xF, vf6, vf7, vf11, 2);  // vmulz.xyzw
                vmul_bc(0xF, vf4, vf7, vf12, 0);  // vmulx.xyzw
                vmul_bc(0xF, vf5, vf7, vf12, 1);  // vmuly.xyzw
                vmul(0xF, vf3, vf2, vf2);  // vmul.xyzw
                vmul(0xF, vf6, vf6, vf2);  // vmul.xyzw
                vmula(0xF, vf4, vf2);  // vmula.xyzw
                vmul_bc(0xF, vf4, vf7, vf12, 2);  // vmulz.xyzw
                vmul(0xF, vf2, vf3, vf3);  // vmul.xyzw
                vmadda(0xF, vf6, vf3);  // vmadda.xyzw
                vmadda(0xF, vf5, vf3);  // vmadda.xyzw
                vmadda_bc(0xF, vf7, vf13, 0);  // vmaddax.xyzw
                vmadd(0xF, vf7, vf4, vf2);  // vmadd.xyzw
                vmul_bc(0xE, vf2, vf8, vf7, 0);  // vmulx.xyz
                vmul_bc(0xE, vf3, vf16, vf7, 2);  // vmulz.xyz
                vmul_bc(0xE, vf4, vf9, vf7, 2);  // vmulz.xyz
                vmul_bc(0xE, vf5, vf17, vf7, 0);  // vmulx.xyz
                vsub(0xF, vf18, vf2, vf3);  // vsub.xyzw
                vadd(0xF, vf19, vf4, vf5);  // vadd.xyzw
                vmula_bc(0xF, vf19, vf14, 1);  // vmulay.xyzw
                vmadda_bc(0xF, vf18, vf14, 0);  // vmaddax.xyzw
                vmadd_bc(0xF, vf21, vf20, vf0, 3);  // vmaddw.xyzw
                vmula_bc(0xF, vf19, vf14, 1);  // vmulay.xyzw
                vmadda_bc(0xF, vf18, vf14, 2);  // vmaddaz.xyzw
                vmadd_bc(0xF, vf22, vf20, vf0, 3);  // vmaddw.xyzw
                vmula_bc(0xF, vf19, vf14, 3);  // vmulaw.xyzw
                vmadda_bc(0xF, vf18, vf14, 2);  // vmaddaz.xyzw
                vmadd_bc(0xF, vf23, vf20, vf0, 3);  // vmaddw.xyzw
                vmula_bc(0xF, vf19, vf14, 3);  // vmulaw.xyzw
                vmadda_bc(0xF, vf18, vf14, 0);  // vmaddax.xyzw
                vmadd_bc(0xF, vf24, vf20, vf0, 3);  // vmaddw.xyzw
                sqc2(vf21, s0, 0);
                sqc2(vf22, s0, 16);
                sqc2(vf23, s0, 32);
                sqc2(vf24, s0, 48);
                ei(ctx);
                a3 = addiu(a3, 1);
                a0 = slt(a3, s4);
                s2 = addu(s2, s7);
                s1 = addu(s1, fp);
                s0 = addu(s0, a1);
                if (a0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00480858
            charge(ctx, 2);
        }
    }
    // 0x00480be8 (the shared epilogue, written out on this path)
    charge(ctx, 16);
    ld(ra, sp, 0xA0);
    lq(fp, sp, 0x90);
    lwc1(f23, sp, 0xC);
    lq(s7, sp, 0x80);
    lwc1(f22, sp, 0x8);
    lq(s6, sp, 0x70);
    lwc1(f21, sp, 0x4);
    lq(s5, sp, 0x60);
    lwc1(f20, sp, 0x0);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0x120);
}

// 0x00480C30 sub_480C30 -- 3120 bytes; frame 0x100: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Scratchpad DMA kernel using the SPR blocks at 0x3F50 / 0x3F60 / 0x3F90.
void sub_480C30(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, t8{ctx, 24}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    Vf vf0{ctx, 0}, vf1{ctx, 1}, vf2{ctx, 2}, vf3{ctx, 3}, vf4{ctx, 4}, vf5{ctx, 5}, vf6{ctx, 6}, vf7{ctx, 7}, vf8{ctx, 8}, vf9{ctx, 9}, vf10{ctx, 10}, vf11{ctx, 11}, vf12{ctx, 12}, vf13{ctx, 13}, vf14{ctx, 14}, vf15{ctx, 15}, vf16{ctx, 16}, vf17{ctx, 17}, vf18{ctx, 18}, vf19{ctx, 19}, vf20{ctx, 20}, vf21{ctx, 21}, vf25{ctx, 25}, vf26{ctx, 26}, vf27{ctx, 27};
    // 0x00480c30
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x100);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    s6 = t0;
    sq(s4, sp, 0x40);
    s5 = a1;
    sq(s3, sp, 0x30);
    s4 = a2;
    sq(s2, sp, 0x20);
    s3 = a3;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a0, 4);
    lw(s7, t0, 8);
    lw(s2, t0, 4);
    lw(s1, t0, 28);
    lw(fp, t0, 32);
    lw(s0, a0, 0);
    sq(v0, sp, 0xA0);
    if (s7 != v0) {
        // 0x004816ec
        charge(ctx, 12);
        a0 = addiu(sp, 0xD0);
        a2 = 12;
        jal(ctx, 0x4816F0u, gen::fn_memcpy_00521250);
        a1 = s4;
        a0 = addiu(sp, 0xC0);
        a2 = 12;
        jal(ctx, 0x481700u, gen::fn_memcpy_00521250);
        lwc1(f1, s6, 104);
        v1 = 0x10000;
        lwc1(f0, s6, 108);
        swc1(f1, sp, 0xE0);
        swc1(f0, sp, 0xE4);
        for (;;) {
            // 0x0048171c
            charge(ctx, 7);
            di(ctx);
            sync(ctx, 16);
            mfc0(a0, 12);
            a0 = a0 & v1;
            if (a0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00481738
        charge(ctx, 21);
        v1 = 0x3F000000;
        a2 = addiu(sp, 0xD0);
        mtc1(v1, f0);
        a1 = addiu(sp, 0xC0);
        a0 = addiu(sp, 0xE0);
        mfc1(v1, f0);
        ctc2(v1, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        lqc2(vf1, a2, 0);
        lqc2(vf2, a1, 0);
        lqc2(vf3, a0, 0);
        vmula_bc(0xF, vf1, vf3, 0);  // vmulax.xyzw
        vmadda_bc(0xF, vf2, vf3, 1);  // vmadday.xyzw
        vmadd(0xF, vf21, vf0, vf0);  // vmadd.xyzw
        vmuli(0xF, vf1, vf1);  // vmuli.xyzw
        vmuli(0xF, vf2, vf2);  // vmuli.xyzw
        ei(ctx);
        at = slt(0, s3);
        t0 = 0;
        if (at != 0) {
            // 0x0048178c
            charge(ctx, 5);
            lq(v1, sp, 0xA0);
            a3 = addiu(sp, 0xB4);
            a1 = addiu(sp, 0xB0);
            a2 = 0x10000;
            a0 = sll(v1, 2);
            for (;;) {
                // 0x004817a0
                charge(ctx, 4);
                lwc1(f1, s1, 0);
                lwc1(f0, s1, 4);
                swc1(f1, sp, 0xB0);
                swc1(f0, a3, 0);
                for (;;) {
                    // 0x004817b0
                    charge(ctx, 7);
                    di(ctx);
                    sync(ctx, 16);
                    mfc0(v1, 12);
                    v1 = v1 & a2;
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004817cc
                charge(ctx, 24);
                lqc2(vf3, a1, 0);
                vmul_bc(0xE, vf4, vf1, vf3, 0);  // vmulx.xyz
                vmul_bc(0xE, vf5, vf2, vf3, 1);  // vmuly.xyz
                lqc2(vf6, s2, 0);
                vadd(0xF, vf6, vf6, vf21);  // vadd.xyzw
                vsub(0xE, vf7, vf6, vf4);  // vsub.xyz
                vadd(0xE, vf8, vf6, vf4);  // vadd.xyz
                vadd(0xE, vf9, vf6, vf4);  // vadd.xyz
                vsub(0xE, vf10, vf6, vf4);  // vsub.xyz
                vsub(0xE, vf7, vf7, vf5);  // vsub.xyz
                vsub(0xE, vf8, vf8, vf5);  // vsub.xyz
                vadd(0xE, vf9, vf9, vf5);  // vadd.xyz
                vadd(0xE, vf10, vf10, vf5);  // vadd.xyz
                sqc2(vf7, s0, 0);
                sqc2(vf8, s0, 16);
                sqc2(vf9, s0, 32);
                sqc2(vf10, s0, 48);
                ei(ctx);
                t0 = addiu(t0, 1);
                v1 = slt(t0, s3);
                s1 = addu(s1, fp);
                s0 = addu(s0, a0);
                s2 = addu(s2, s7);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0048182c
            charge(ctx, 1);
        }
    } else {
        // 0x00480c8c
        charge(ctx, 7);
        a0 = 0;
        jal(ctx, 0x480C8Cu, gen::fn__sceFlushCache_005033e0);
        v1 = 0x10010000;
        lw(a0, v1, -12288);  // 0x1000D000 D8 fromSPR CHCR
        a0 = a0 & 0x100;
        if (a0 != 0) {
            // 0x00480ca8
            charge(ctx, 4);
            a0 = 256;
            sw(a0, v1, -8160);
            sync(ctx, 0);
            sync(ctx, 16);
            for (;;) {
                // 0x00480cb8
                charge(ctx, 7);
                if (cop0_cond(ctx)) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x00480cd4
        charge(ctx, 5);
        v1 = 0x10010000;
        lw(a0, v1, -11264);  // 0x1000D400 D9 toSPR CHCR
        a0 = a0 & 0x100;
        if (a0 != 0) {
            // 0x00480ce8
            charge(ctx, 4);
            a0 = 512;
            sw(a0, v1, -8160);
            sync(ctx, 0);
            sync(ctx, 16);
            for (;;) {
                // 0x00480cf8
                charge(ctx, 7);
                if (cop0_cond(ctx)) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00480d14
            charge(ctx, 1);
            v1 = 0x10010000;
            for (;;) {
                // 0x00480d18
                charge(ctx, 7);
                lw(a0, v1, -11264);
                a0 = a0 & 0x100;
                if (a0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00480d34
            charge(ctx, 1);
        }
        // 0x00480d38
        charge(ctx, 21);
        a2 = 0x70000000;
        lwc1(f2, s5, 0);
        a3 = a2 | 0x3F50;
        lwc1(f1, s5, 4);
        a1 = a2 | 0x3F60;
        lwc1(f0, s5, 8);
        a0 = a2 | 0x3F90;
        v1 = 0x10000;
        swc1(f2, a3, 0);  // 0x70003F50 SPR+0x3F50
        swc1(f1, a3, 4);  // 0x70003F54 SPR+0x3F54
        swc1(f0, a3, 8);  // 0x70003F58 SPR+0x3F58
        lwc1(f2, s4, 0);
        lwc1(f1, s4, 4);
        lwc1(f0, s4, 8);
        swc1(f2, a1, 0);  // 0x70003F60 SPR+0x3F60
        swc1(f1, a1, 4);  // 0x70003F64 SPR+0x3F64
        swc1(f0, a1, 8);  // 0x70003F68 SPR+0x3F68
        lwc1(f0, s6, 104);
        swc1(f0, a2, 16272);  // 0x70003F90 SPR+0x3F90
        lwc1(f0, s6, 108);
        swc1(f0, a2, 16276);  // 0x70003F94 SPR+0x3F94
        for (;;) {
            // 0x00480d8c
            charge(ctx, 7);
            di(ctx);
            sync(ctx, 16);
            mfc0(a2, 12);
            a2 = a2 & v1;
            if (a2 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00480da8
        charge(ctx, 18);
        v1 = 0x3F000000;
        mtc1(v1, f0);
        mfc1(v1, f0);
        ctc2(v1, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        lqc2(vf1, a3, 0);
        lqc2(vf2, a1, 0);
        lqc2(vf3, a0, 0);
        vmula_bc(0xF, vf1, vf3, 0);  // vmulax.xyzw
        vmadda_bc(0xF, vf2, vf3, 1);  // vmadday.xyzw
        vmadd(0xF, vf21, vf0, vf0);  // vmadd.xyzw
        vmuli(0xF, vf1, vf1);  // vmuli.xyzw
        vmuli(0xF, vf2, vf2);  // vmuli.xyzw
        ei(ctx);
        v1 = slti(s3, 184);
        if (v1 == 0) {
            // 0x00480df0
            charge(ctx, 12);
            t6 = 0x70000000;
            a3 = 0x10010000;
            t3 = 0x10000;
            t8 = 256;
            s6 = 512;
            s5 = 92;
            s4 = 1472;
            t7 = 184;
            t5 = t6 | 0x5C0;
            t4 = t6 | 0x1140;
            t1 = 4416;
            t0 = 736;
            for (;;) {
                // 0x00480e20
                charge(ctx, 4);
                lw(v1, a3, -12288);
                v1 = v1 & 0x100;
                if (v1 != 0) {
                    // 0x00480e30
                    charge(ctx, 4);
                    sw(t8, a3, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x00480e40
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00480e5c
                    charge(ctx, 1);
                }
                // 0x00480e60
                charge(ctx, 4);
                lw(v1, a3, -11264);
                v1 = v1 & 0x100;
                if (v1 != 0) {
                    // 0x00480e70
                    charge(ctx, 4);
                    sw(s6, a3, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x00480e80
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00480e9c
                    charge(ctx, 1);
                    for (;;) {
                        // 0x00480ea0
                        charge(ctx, 7);
                        lw(v1, a3, -11264);
                        v1 = v1 & 0x100;
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00480ebc
                    charge(ctx, 1);
                }
                // 0x00480ec0
                charge(ctx, 11);
                sw(s6, a3, -8176);
                sw(zero, a3, -11136);
                sw(s1, a3, -11248);
                sw(s5, a3, -11232);
                sw(t8, a3, -11264);
                sync(ctx, 0);
                sync(ctx, 16);
                lw(v1, a3, -11264);
                v1 = v1 & 0x100;
                if (v1 != 0) {
                    // 0x00480eec
                    charge(ctx, 3);
                    sw(s6, a3, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x00480ef8
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00480f14
                    charge(ctx, 1);
                    for (;;) {
                        // 0x00480f18
                        charge(ctx, 7);
                        lw(v1, a3, -11264);
                        v1 = v1 & 0x100;
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00480f34
                    charge(ctx, 1);
                }
                // 0x00480f38
                charge(ctx, 11);
                sw(s6, a3, -8176);
                sw(s4, a3, -11136);
                sw(s2, a3, -11248);
                sw(t7, a3, -11232);
                sw(t8, a3, -11264);
                sync(ctx, 0);
                sync(ctx, 16);
                lw(v1, a3, -11264);
                v1 = v1 & 0x100;
                if (v1 != 0) {
                    // 0x00480f64
                    charge(ctx, 3);
                    sw(s6, a3, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x00480f70
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00480f8c
                    charge(ctx, 1);
                    for (;;) {
                        // 0x00480f90
                        charge(ctx, 7);
                        lw(v1, a3, -11264);
                        v1 = v1 & 0x100;
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00480fac
                    charge(ctx, 1);
                }
                // 0x00480fb0
                charge(ctx, 4);
                a1 = t6;
                a0 = t5;
                v1 = t4;
                a2 = 0;
                for (;;) {
                    // 0x00480fc0
                    charge(ctx, 7);
                    di(ctx);
                    sync(ctx, 16);
                    mfc0(t2, 12);
                    t2 = t2 & t3;
                    if (t2 != 0) {
                        backedge(ctx);
                        continue;
                    }
                    // 0x00480fdc
                    charge(ctx, 73);
                    lqc2(vf3, a1, 0);
                    vmul_bc(0xE, vf4, vf1, vf3, 0);  // vmulx.xyz
                    vmul_bc(0xE, vf5, vf2, vf3, 1);  // vmuly.xyz
                    vmul_bc(0xE, vf11, vf1, vf3, 2);  // vmulz.xyz
                    vmul_bc(0xE, vf12, vf2, vf3, 3);  // vmulw.xyz
                    lqc2(vf6, a0, 0);
                    vadd(0xF, vf6, vf6, vf21);  // vadd.xyzw
                    lqc2(vf13, a0, 16);
                    vadd(0xF, vf13, vf13, vf21);  // vadd.xyzw
                    lqc2(vf20, a0, 32);
                    vadd(0xF, vf20, vf20, vf21);  // vadd.xyzw
                    lqc2(vf3, a1, 16);
                    lqc2(vf27, a0, 48);
                    vadd(0xF, vf27, vf27, vf21);  // vadd.xyzw
                    vmul_bc(0xE, vf18, vf1, vf3, 0);  // vmulx.xyz
                    vmul_bc(0xE, vf19, vf2, vf3, 1);  // vmuly.xyz
                    vmul_bc(0xE, vf25, vf1, vf3, 2);  // vmulz.xyz
                    vmul_bc(0xE, vf26, vf2, vf3, 3);  // vmulw.xyz
                    vsub(0xE, vf7, vf6, vf4);  // vsub.xyz
                    vadd(0xE, vf8, vf6, vf4);  // vadd.xyz
                    vadd(0xE, vf9, vf6, vf4);  // vadd.xyz
                    vsub(0xE, vf10, vf6, vf4);  // vsub.xyz
                    vsub(0xE, vf7, vf7, vf5);  // vsub.xyz
                    vsub(0xE, vf8, vf8, vf5);  // vsub.xyz
                    vadd(0xE, vf9, vf9, vf5);  // vadd.xyz
                    vadd(0xE, vf10, vf10, vf5);  // vadd.xyz
                    vsub(0xE, vf14, vf13, vf11);  // vsub.xyz
                    vadd(0xE, vf15, vf13, vf11);  // vadd.xyz
                    vadd(0xE, vf16, vf13, vf11);  // vadd.xyz
                    vsub(0xE, vf17, vf13, vf11);  // vsub.xyz
                    vsub(0xE, vf14, vf14, vf12);  // vsub.xyz
                    vsub(0xE, vf15, vf15, vf12);  // vsub.xyz
                    vadd(0xE, vf16, vf16, vf12);  // vadd.xyz
                    vadd(0xE, vf17, vf17, vf12);  // vadd.xyz
                    sqc2(vf7, v1, 0);
                    sqc2(vf8, v1, 16);
                    sqc2(vf9, v1, 32);
                    sqc2(vf10, v1, 48);
                    sqc2(vf14, v1, 64);
                    sqc2(vf15, v1, 80);
                    sqc2(vf16, v1, 96);
                    sqc2(vf17, v1, 112);
                    vsub(0xE, vf7, vf20, vf18);  // vsub.xyz
                    vadd(0xE, vf8, vf20, vf18);  // vadd.xyz
                    vadd(0xE, vf9, vf20, vf18);  // vadd.xyz
                    vsub(0xE, vf10, vf20, vf18);  // vsub.xyz
                    vsub(0xE, vf7, vf7, vf19);  // vsub.xyz
                    vsub(0xE, vf8, vf8, vf19);  // vsub.xyz
                    vadd(0xE, vf9, vf9, vf19);  // vadd.xyz
                    vadd(0xE, vf10, vf10, vf19);  // vadd.xyz
                    vsub(0xE, vf14, vf27, vf25);  // vsub.xyz
                    vadd(0xE, vf15, vf27, vf25);  // vadd.xyz
                    vadd(0xE, vf16, vf27, vf25);  // vadd.xyz
                    vsub(0xE, vf17, vf27, vf25);  // vsub.xyz
                    vsub(0xE, vf14, vf14, vf26);  // vsub.xyz
                    vsub(0xE, vf15, vf15, vf26);  // vsub.xyz
                    vadd(0xE, vf16, vf16, vf26);  // vadd.xyz
                    vadd(0xE, vf17, vf17, vf26);  // vadd.xyz
                    sqc2(vf7, v1, 128);
                    sqc2(vf8, v1, 144);
                    sqc2(vf9, v1, 160);
                    sqc2(vf10, v1, 176);
                    sqc2(vf14, v1, 192);
                    sqc2(vf15, v1, 208);
                    sqc2(vf16, v1, 224);
                    sqc2(vf17, v1, 240);
                    ei(ctx);
                    a2 = addiu(a2, 4);
                    t2 = slti(a2, 184);
                    a1 = addiu(a1, 32);
                    v1 = addiu(v1, 256);
                    a0 = addiu(a0, 64);
                    if (t2 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00481100
                charge(ctx, 4);
                lw(v1, a3, -12288);
                v1 = v1 & 0x100;
                if (v1 != 0) {
                    // 0x00481110
                    charge(ctx, 4);
                    sw(t8, a3, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x00481120
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0048113c
                    charge(ctx, 1);
                }
                // 0x00481140
                charge(ctx, 4);
                lw(v1, a3, -11264);
                v1 = v1 & 0x100;
                if (v1 != 0) {
                    // 0x00481150
                    charge(ctx, 4);
                    sw(s6, a3, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x00481160
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0048117c
                    charge(ctx, 1);
                    for (;;) {
                        // 0x00481180
                        charge(ctx, 7);
                        lw(v1, a3, -11264);
                        v1 = v1 & 0x100;
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0048119c
                    charge(ctx, 1);
                }
                // 0x004811a0
                charge(ctx, 13);
                sw(t8, a3, -8176);
                sw(t1, a3, -12160);
                sw(s0, a3, -12272);
                sw(t0, a3, -12256);
                sw(t8, a3, -12288);
                sync(ctx, 0);
                sync(ctx, 16);
                s3 = addiu(s3, -184);
                s2 = addiu(s2, 2944);
                at = slti(s3, 184);
                s0 = addiu(s0, 11776);
                s1 = addiu(s1, 1472);
                if (at != 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004811d4
            charge(ctx, 1);
        }
        // 0x004811d8
        charge(ctx, 3);
        at = slti(s3, 4);
        if (at == 0) {
            // 0x004811e4
            charge(ctx, 2);
            v1 = sra(s3, 2);
            if (i64(s3) < 0) {
                // 0x004811ec
                charge(ctx, 2);
                v1 = addiu(s3, 3);
                v1 = sra(v1, 2);
            }
            // 0x004811f4
            charge(ctx, 6);
            a2 = sll(v1, 2);
            v1 = 0x10010000;
            lw(a0, v1, -12288);  // 0x1000D000 D8 fromSPR CHCR
            a0 = a0 & 0x100;
            if (a0 != 0) {
                // 0x0048120c
                charge(ctx, 4);
                a0 = 256;
                sw(a0, v1, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x0048121c
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x00481238
            charge(ctx, 5);
            v1 = 0x10010000;
            lw(a0, v1, -11264);  // 0x1000D400 D9 toSPR CHCR
            a0 = a0 & 0x100;
            if (a0 != 0) {
                // 0x0048124c
                charge(ctx, 4);
                a0 = 512;
                sw(a0, v1, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x0048125c
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00481278
                charge(ctx, 1);
                v1 = 0x10010000;
                for (;;) {
                    // 0x0048127c
                    charge(ctx, 7);
                    lw(a0, v1, -11264);
                    a0 = a0 & 0x100;
                    if (a0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x00481298
            charge(ctx, 7);
            a0 = 512;
            v1 = 0x10010000;
            a1 = sra(a2, 1);
            sw(a0, v1, -8176);  // 0x1000E010 D_STAT
            sw(zero, v1, -11136);  // 0x1000D480 D9 toSPR SADR
            sw(s1, v1, -11248);  // 0x1000D410 D9 toSPR MADR
            if (i64(a2) < 0) {
                // 0x004812b4
                charge(ctx, 2);
                v1 = addiu(a2, 1);
                a1 = sra(v1, 1);
            }
            // 0x004812bc
            charge(ctx, 10);
            v1 = 0x10010000;
            a0 = 256;
            sw(a1, v1, -11232);  // 0x1000D420 D9 toSPR QWC
            sw(a0, v1, -11264);  // 0x1000D400 D9 toSPR CHCR
            sync(ctx, 0);
            sync(ctx, 16);
            lw(a0, v1, -11264);  // 0x1000D400 D9 toSPR CHCR
            a0 = a0 & 0x100;
            if (a0 != 0) {
                // 0x004812e4
                charge(ctx, 4);
                a0 = 512;
                sw(a0, v1, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x004812f4
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00481310
                charge(ctx, 1);
                v1 = 0x10010000;
                for (;;) {
                    // 0x00481314
                    charge(ctx, 7);
                    lw(a0, v1, -11264);
                    a0 = a0 & 0x100;
                    if (a0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x00481330
            charge(ctx, 15);
            t0 = sll(a1, 4);
            a1 = 512;
            v1 = 0x10010000;
            sw(a1, v1, -8176);  // 0x1000E010 D_STAT
            a0 = 256;
            sw(t0, v1, -11136);  // 0x1000D480 D9 toSPR SADR
            sw(s2, v1, -11248);  // 0x1000D410 D9 toSPR MADR
            sw(a2, v1, -11232);  // 0x1000D420 D9 toSPR QWC
            sw(a0, v1, -11264);  // 0x1000D400 D9 toSPR CHCR
            sync(ctx, 0);
            sync(ctx, 16);
            lw(a0, v1, -11264);  // 0x1000D400 D9 toSPR CHCR
            a0 = a0 & 0x100;
            if (a0 != 0) {
                // 0x0048136c
                charge(ctx, 3);
                sw(a1, v1, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x00481378
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00481394
                charge(ctx, 1);
                v1 = 0x10010000;
                for (;;) {
                    // 0x00481398
                    charge(ctx, 7);
                    lw(a0, v1, -11264);
                    a0 = a0 & 0x100;
                    if (a0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004813b4
                charge(ctx, 1);
            }
            // 0x004813b8
            charge(ctx, 3);
            a1 = 0x70000000;
            v1 = sra(a2, 1);
            if (i64(a2) < 0) {
                // 0x004813c4
                charge(ctx, 2);
                v1 = addiu(a2, 1);
                v1 = sra(v1, 1);
            }
            // 0x004813cc
            charge(ctx, 8);
            v1 = addu(a2, v1);
            a3 = 0x70000000;
            v1 = sll(v1, 4);
            at = slt(0, a2);
            a0 = t0 | a3;
            v1 = v1 | a3;
            t1 = 0;
            if (at != 0) {
                // 0x004813ec
                charge(ctx, 1);
                t0 = 0x10000;
                for (;;) {
                    // 0x004813f0
                    charge(ctx, 7);
                    di(ctx);
                    sync(ctx, 16);
                    mfc0(a3, 12);
                    a3 = a3 & t0;
                    if (a3 != 0) {
                        backedge(ctx);
                        continue;
                    }
                    // 0x0048140c
                    charge(ctx, 73);
                    lqc2(vf3, a1, 0);
                    vmul_bc(0xE, vf4, vf1, vf3, 0);  // vmulx.xyz
                    vmul_bc(0xE, vf5, vf2, vf3, 1);  // vmuly.xyz
                    vmul_bc(0xE, vf11, vf1, vf3, 2);  // vmulz.xyz
                    vmul_bc(0xE, vf12, vf2, vf3, 3);  // vmulw.xyz
                    lqc2(vf6, a0, 0);
                    vadd(0xF, vf6, vf6, vf21);  // vadd.xyzw
                    lqc2(vf13, a0, 16);
                    vadd(0xF, vf13, vf13, vf21);  // vadd.xyzw
                    lqc2(vf20, a0, 32);
                    vadd(0xF, vf20, vf20, vf21);  // vadd.xyzw
                    lqc2(vf3, a1, 16);
                    lqc2(vf27, a0, 48);
                    vadd(0xF, vf27, vf27, vf21);  // vadd.xyzw
                    vmul_bc(0xE, vf18, vf1, vf3, 0);  // vmulx.xyz
                    vmul_bc(0xE, vf19, vf2, vf3, 1);  // vmuly.xyz
                    vmul_bc(0xE, vf25, vf1, vf3, 2);  // vmulz.xyz
                    vmul_bc(0xE, vf26, vf2, vf3, 3);  // vmulw.xyz
                    vsub(0xE, vf7, vf6, vf4);  // vsub.xyz
                    vadd(0xE, vf8, vf6, vf4);  // vadd.xyz
                    vadd(0xE, vf9, vf6, vf4);  // vadd.xyz
                    vsub(0xE, vf10, vf6, vf4);  // vsub.xyz
                    vsub(0xE, vf7, vf7, vf5);  // vsub.xyz
                    vsub(0xE, vf8, vf8, vf5);  // vsub.xyz
                    vadd(0xE, vf9, vf9, vf5);  // vadd.xyz
                    vadd(0xE, vf10, vf10, vf5);  // vadd.xyz
                    vsub(0xE, vf14, vf13, vf11);  // vsub.xyz
                    vadd(0xE, vf15, vf13, vf11);  // vadd.xyz
                    vadd(0xE, vf16, vf13, vf11);  // vadd.xyz
                    vsub(0xE, vf17, vf13, vf11);  // vsub.xyz
                    vsub(0xE, vf14, vf14, vf12);  // vsub.xyz
                    vsub(0xE, vf15, vf15, vf12);  // vsub.xyz
                    vadd(0xE, vf16, vf16, vf12);  // vadd.xyz
                    vadd(0xE, vf17, vf17, vf12);  // vadd.xyz
                    sqc2(vf7, v1, 0);
                    sqc2(vf8, v1, 16);
                    sqc2(vf9, v1, 32);
                    sqc2(vf10, v1, 48);
                    sqc2(vf14, v1, 64);
                    sqc2(vf15, v1, 80);
                    sqc2(vf16, v1, 96);
                    sqc2(vf17, v1, 112);
                    vsub(0xE, vf7, vf20, vf18);  // vsub.xyz
                    vadd(0xE, vf8, vf20, vf18);  // vadd.xyz
                    vadd(0xE, vf9, vf20, vf18);  // vadd.xyz
                    vsub(0xE, vf10, vf20, vf18);  // vsub.xyz
                    vsub(0xE, vf7, vf7, vf19);  // vsub.xyz
                    vsub(0xE, vf8, vf8, vf19);  // vsub.xyz
                    vadd(0xE, vf9, vf9, vf19);  // vadd.xyz
                    vadd(0xE, vf10, vf10, vf19);  // vadd.xyz
                    vsub(0xE, vf14, vf27, vf25);  // vsub.xyz
                    vadd(0xE, vf15, vf27, vf25);  // vadd.xyz
                    vadd(0xE, vf16, vf27, vf25);  // vadd.xyz
                    vsub(0xE, vf17, vf27, vf25);  // vsub.xyz
                    vsub(0xE, vf14, vf14, vf26);  // vsub.xyz
                    vsub(0xE, vf15, vf15, vf26);  // vsub.xyz
                    vadd(0xE, vf16, vf16, vf26);  // vadd.xyz
                    vadd(0xE, vf17, vf17, vf26);  // vadd.xyz
                    sqc2(vf7, v1, 128);
                    sqc2(vf8, v1, 144);
                    sqc2(vf9, v1, 160);
                    sqc2(vf10, v1, 176);
                    sqc2(vf14, v1, 192);
                    sqc2(vf15, v1, 208);
                    sqc2(vf16, v1, 224);
                    sqc2(vf17, v1, 240);
                    ei(ctx);
                    t1 = addiu(t1, 4);
                    a3 = slt(t1, a2);
                    a1 = addiu(a1, 32);
                    v1 = addiu(v1, 256);
                    a0 = addiu(a0, 64);
                    if (a3 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x00481530
            charge(ctx, 5);
            v1 = 0x10010000;
            lw(a0, v1, -12288);  // 0x1000D000 D8 fromSPR CHCR
            a0 = a0 & 0x100;
            if (a0 != 0) {
                // 0x00481544
                charge(ctx, 4);
                a0 = 256;
                sw(a0, v1, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x00481554
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x00481570
            charge(ctx, 5);
            v1 = 0x10010000;
            lw(a0, v1, -11264);  // 0x1000D400 D9 toSPR CHCR
            a0 = a0 & 0x100;
            if (a0 != 0) {
                // 0x00481584
                charge(ctx, 4);
                a0 = 512;
                sw(a0, v1, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x00481594
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004815b0
                charge(ctx, 1);
                v1 = 0x10010000;
                for (;;) {
                    // 0x004815b4
                    charge(ctx, 7);
                    lw(a0, v1, -11264);
                    a0 = a0 & 0x100;
                    if (a0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x004815d0
            charge(ctx, 5);
            a0 = 256;
            v1 = 0x10010000;
            a3 = sra(a2, 1);
            sw(a0, v1, -8176);  // 0x1000E010 D_STAT
            if (i64(a2) < 0) {
                // 0x004815e4
                charge(ctx, 2);
                v1 = addiu(a2, 1);
                a3 = sra(v1, 1);
            }
            // 0x004815ec
            charge(ctx, 18);
            a0 = addu(a2, a3);
            v1 = 0x10010000;
            a0 = sll(a0, 4);
            a1 = sll(a2, 2);
            sw(a0, v1, -12160);  // 0x1000D080 D8 fromSPR SADR
            sw(s0, v1, -12272);  // 0x1000D010 D8 fromSPR MADR
            a0 = 256;
            sw(a1, v1, -12256);  // 0x1000D020 D8 fromSPR QWC
            sw(a0, v1, -12288);  // 0x1000D000 D8 fromSPR CHCR
            sync(ctx, 0);
            sync(ctx, 16);
            v1 = sll(a3, 4);
            a0 = sll(a1, 4);
            s1 = addu(s1, v1);
            s0 = addu(s0, a0);
            v1 = sll(a2, 4);
            s3 = subu(s3, a2);
            s2 = addu(s2, v1);
        }
        // 0x00481634
        charge(ctx, 3);
        at = slt(0, s3);
        t0 = 0;
        if (at != 0) {
            // 0x00481640
            charge(ctx, 5);
            lq(v1, sp, 0xA0);
            a3 = addiu(sp, 0xF4);
            a1 = addiu(sp, 0xF0);
            a2 = 0x10000;
            a0 = sll(v1, 2);
            for (;;) {
                // 0x00481654
                charge(ctx, 5);
                lwc1(f1, s1, 0);
                lwc1(f0, s1, 4);
                swc1(f1, sp, 0xF0);
                swc1(f0, a3, 0);
                for (;;) {
                    // 0x00481668
                    charge(ctx, 7);
                    di(ctx);
                    sync(ctx, 16);
                    mfc0(v1, 12);
                    v1 = v1 & a2;
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00481684
                charge(ctx, 24);
                lqc2(vf3, a1, 0);
                vmul_bc(0xE, vf4, vf1, vf3, 0);  // vmulx.xyz
                vmul_bc(0xE, vf5, vf2, vf3, 1);  // vmuly.xyz
                lqc2(vf6, s2, 0);
                vadd(0xF, vf6, vf6, vf21);  // vadd.xyzw
                vsub(0xE, vf7, vf6, vf4);  // vsub.xyz
                vadd(0xE, vf8, vf6, vf4);  // vadd.xyz
                vadd(0xE, vf9, vf6, vf4);  // vadd.xyz
                vsub(0xE, vf10, vf6, vf4);  // vsub.xyz
                vsub(0xE, vf7, vf7, vf5);  // vsub.xyz
                vsub(0xE, vf8, vf8, vf5);  // vsub.xyz
                vadd(0xE, vf9, vf9, vf5);  // vadd.xyz
                vadd(0xE, vf10, vf10, vf5);  // vadd.xyz
                sqc2(vf7, s0, 0);
                sqc2(vf8, s0, 16);
                sqc2(vf9, s0, 32);
                sqc2(vf10, s0, 48);
                ei(ctx);
                t0 = addiu(t0, 1);
                v1 = slt(t0, s3);
                s1 = addu(s1, fp);
                s0 = addu(s0, a0);
                s2 = addu(s2, s7);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004816e4
            charge(ctx, 2);
        }
    }
    // 0x00481830 (the shared epilogue, written out on this path)
    charge(ctx, 12);
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

// 0x00481860 sub_481860 -- 4592 bytes; frame 0x130: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Scratchpad DMA kernel using the SPR blocks at 0x3F40..0x3F6C.
void sub_481860(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5};
    Vf vf0{ctx, 0}, vf1{ctx, 1}, vf2{ctx, 2}, vf3{ctx, 3}, vf4{ctx, 4}, vf5{ctx, 5}, vf6{ctx, 6}, vf7{ctx, 7}, vf8{ctx, 8}, vf9{ctx, 9}, vf10{ctx, 10}, vf11{ctx, 11}, vf12{ctx, 12}, vf13{ctx, 13}, vf14{ctx, 14}, vf15{ctx, 15}, vf18{ctx, 18}, vf19{ctx, 19}, vf20{ctx, 20}, vf21{ctx, 21}, vf22{ctx, 22}, vf23{ctx, 23}, vf24{ctx, 24}, vf25{ctx, 25}, vf26{ctx, 26}, vf27{ctx, 27}, vf28{ctx, 28}, vf29{ctx, 29}, vf30{ctx, 30}, vf31{ctx, 31};
    // 0x00481860
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x130);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    s7 = a3;
    sq(s5, sp, 0x50);
    s6 = a2;
    sq(s4, sp, 0x40);
    s5 = a1;
    sq(s3, sp, 0x30);
    s4 = t0;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, t0, 8);
    lw(s1, a0, 0);
    lw(s3, t0, 4);
    lw(s2, t0, 52);
    lw(s0, t0, 28);
    sq(v1, sp, 0xD0);
    lw(v1, t0, 56);
    sq(v1, sp, 0xC0);
    lw(v1, t0, 32);
    sq(v1, sp, 0xB0);
    lw(v1, a0, 4);
    lq(a0, sp, 0xD0);
    sq(v1, sp, 0xA0);
    if (a0 != v1) {
        // 0x004826c8
        charge(ctx, 30);
        lwc1(f2, s5, 0);
        a0 = 0x3F000000;
        lwc1(f1, s5, 4);
        v1 = addiu(sp, 0x104);
        lwc1(f0, s5, 8);
        mtc1(a0, f3);
        lwc1(f5, s4, 104);
        lwc1(f4, s4, 108);
        a0 = 0x10000;
        mul_s(f2, f3, f2);
        mul_s(f1, f3, f1);
        mul_s(f0, f3, f0);
        add_s(f5, f5, f5);
        add_s(f4, f4, f4);
        swc1(f2, sp, 0x120);
        swc1(f1, sp, 0x124);
        swc1(f0, sp, 0x128);
        lwc1(f2, s6, 0);
        lwc1(f1, s6, 4);
        lwc1(f0, s6, 8);
        swc1(f5, sp, 0x100);
        swc1(f5, sp, 0x108);
        swc1(f4, sp, 0x10C);
        mul_s(f2, f3, f2);
        mul_s(f1, f3, f1);
        mul_s(f0, f3, f0);
        swc1(f4, v1, 0);
        swc1(f2, sp, 0x110);
        swc1(f1, sp, 0x114);
        swc1(f0, sp, 0x118);
        for (;;) {
            // 0x00482740
            charge(ctx, 7);
            di(ctx);
            sync(ctx, 16);
            mfc0(a1, 12);
            a1 = a1 & a0;
            if (a1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0048275c
        charge(ctx, 79);
        at = 0x3FC90000;
        a0 = at | 0xFDB;
        mtc1(a0, f0);
        mfc1(a0, f0);
        ctc2(a0, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x8, vf10, vf0);  // vaddi.x
        at = 0x40490000;
        a1 = at | 0xFDB;
        mtc1(a1, f0);
        mfc1(a0, f0);
        ctc2(a0, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x4, vf10, vf0);  // vaddi.y
        at = 0x40090000;
        a0 = at | 0xFDB;
        mtc1(a0, f0);
        mfc1(a0, f0);
        ctc2(a0, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x2, vf10, vf0);  // vaddi.z
        mtc1(a1, f0);
        neg_s(f0, f0);
        mfc1(a0, f0);
        ctc2(a0, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x8, vf11, vf0);  // vaddi.x
        at = 0x40840000;
        a0 = at | 0x87ED;
        mtc1(a0, f0);
        neg_s(f0, f0);
        mfc1(a0, f0);
        ctc2(a0, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x4, vf11, vf0);  // vaddi.y
        a0 = 0x0;
        a0 = dsll(a0, 16);
        a0 = dsll(a0, 16);
        a0 = a0 | 0xB94F;
        a0 = dsll(a0, 16);
        a0 = a0 | 0xB21F;
        ctc2(a0, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x2, vf11, vf0);  // vaddi.z
        a0 = 0x0;
        a0 = dsll(a0, 16);
        a0 = dsll(a0, 16);
        a0 = a0 | 0xBE2A;
        a0 = dsll(a0, 16);
        a0 = a0 | 0xAAA4;
        ctc2(a0, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x8, vf12, vf0);  // vaddi.x
        at = 0x3C080000;
        a0 = at | 0x873E;
        ctc2(a0, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x4, vf12, vf0);  // vaddi.y
        at = 0x362E0000;
        a0 = at | 0x9C14;
        ctc2(a0, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x2, vf12, vf0);  // vaddi.z
        a0 = 0x3F800000;
        ctc2(a0, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x8, vf13, vf0);  // vaddi.x
        ei(ctx);
        a0 = 0x10000;
        for (;;) {
            // 0x00482898
            charge(ctx, 7);
            di(ctx);
            sync(ctx, 16);
            mfc0(a1, 12);
            a1 = a1 & a0;
            if (a1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004828b4
        charge(ctx, 10);
        a1 = addiu(sp, 0x120);
        a0 = addiu(sp, 0x110);
        t1 = addiu(sp, 0x100);
        lqc2(vf8, a1, 0);
        lqc2(vf9, a0, 0);
        lqc2(vf15, t1, 0);
        ei(ctx);
        at = slt(0, s7);
        t2 = 0;
        if (at != 0) {
            // 0x004828dc
            charge(ctx, 5);
            lq(a0, sp, 0xA0);
            t0 = addiu(sp, 0xF8);
            a2 = addiu(sp, 0xF0);
            a3 = 0x10000;
            a1 = sll(a0, 2);
            for (;;) {
                // 0x004828f0
                charge(ctx, 8);
                lwc1(f2, s2, 0);
                lwc1(f1, s0, 0);
                lwc1(f0, s0, 4);
                swc1(f2, sp, 0xF0);
                swc1(f2, t0, 0);
                swc1(f1, sp, 0x100);
                swc1(f0, v1, 0);
                for (;;) {
                    // 0x00482910
                    charge(ctx, 7);
                    di(ctx);
                    sync(ctx, 16);
                    mfc0(a0, 12);
                    a0 = a0 & a3;
                    if (a0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0048292c
                charge(ctx, 60);
                lqc2(vf1, a2, 0);
                vabs(0xC, vf7, vf1);  // vabs.xy
                vadda_bc(0xF, vf0, vf10, 0);  // vaddax.xyzw
                vmsub_bc(0xC, vf7, vf7, vf0, 3);  // vmsubw.xy
                vadda_bc(0xE, vf0, vf10, 1);  // vadday.xyz
                vadda_bc(0x1, vf0, vf10, 2);  // vaddaz.w
                vmsub_bc(0x3, vf2, vf1, vf0, 3);  // vmsubw.zw
                vadda_bc(0xE, vf0, vf11, 0);  // vaddax.xyz
                vadda_bc(0x1, vf0, vf11, 1);  // vadday.w
                vmsub_bc(0x3, vf3, vf1, vf0, 3);  // vmsubw.zw
                vmini(0x3, vf2, vf1, vf2);  // vmini.zw
                vmax(0x3, vf7, vf2, vf3);  // vmax.zw
                vmul(0xF, vf2, vf7, vf7);  // vmul.xyzw
                vmul_bc(0xF, vf6, vf7, vf11, 2);  // vmulz.xyzw
                vmul_bc(0xF, vf4, vf7, vf12, 0);  // vmulx.xyzw
                vmul_bc(0xF, vf5, vf7, vf12, 1);  // vmuly.xyzw
                vmul(0xF, vf3, vf2, vf2);  // vmul.xyzw
                vmul(0xF, vf6, vf6, vf2);  // vmul.xyzw
                vmula(0xF, vf4, vf2);  // vmula.xyzw
                vmul_bc(0xF, vf4, vf7, vf12, 2);  // vmulz.xyzw
                vmul(0xF, vf2, vf3, vf3);  // vmul.xyzw
                vmadda(0xF, vf6, vf3);  // vmadda.xyzw
                vmadda(0xF, vf5, vf3);  // vmadda.xyzw
                vmadda_bc(0xF, vf7, vf13, 0);  // vmaddax.xyzw
                vmadd(0xF, vf7, vf4, vf2);  // vmadd.xyzw
                lqc2(vf20, s3, 0);
                lqc2(vf14, t1, 0);
                vmula_bc(0xF, vf8, vf7, 0);  // vmulax.xyzw
                vmsub_bc(0xF, vf18, vf9, vf7, 2);  // vmsubz.xyzw
                vadd(0xF, vf2, vf15, vf14);  // vadd.xyzw
                vsub(0xF, vf3, vf15, vf14);  // vsub.xyzw
                vmula_bc(0xF, vf9, vf7, 0);  // vmulax.xyzw
                vmadd_bc(0xF, vf19, vf8, vf7, 2);  // vmaddz.xyzw
                vmula_bc(0xF, vf18, vf3, 0);  // vmulax.xyzw
                vmadd_bc(0xF, vf21, vf19, vf3, 1);  // vmaddy.xyzw
                vmula_bc(0xF, vf18, vf2, 0);  // vmulax.xyzw
                vmadd_bc(0xF, vf22, vf19, vf3, 1);  // vmaddy.xyzw
                vmula_bc(0xF, vf18, vf2, 0);  // vmulax.xyzw
                vmadd_bc(0xF, vf23, vf19, vf2, 1);  // vmaddy.xyzw
                vmula_bc(0xF, vf18, vf3, 0);  // vmulax.xyzw
                vmadd_bc(0xF, vf24, vf19, vf2, 1);  // vmaddy.xyzw
                vadd(0xF, vf21, vf21, vf20);  // vadd.xyzw
                vadd(0xF, vf22, vf22, vf20);  // vadd.xyzw
                vadd(0xF, vf23, vf23, vf20);  // vadd.xyzw
                vadd(0xF, vf24, vf24, vf20);  // vadd.xyzw
                sqc2(vf21, s1, 0);
                sqc2(vf22, s1, 16);
                sqc2(vf23, s1, 32);
                sqc2(vf24, s1, 48);
                ei(ctx);
                t2 = addiu(t2, 1);
                lq(a0, sp, 0xD0);
                s3 = addu(s3, a0);
                lq(a0, sp, 0xB0);
                s0 = addu(s0, a0);
                lq(a0, sp, 0xC0);
                s2 = addu(s2, a0);
                a0 = slt(t2, s7);
                s1 = addu(s1, a1);
                if (a0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00482a1c
            charge(ctx, 1);
        }
    } else {
        // 0x004818d4
        charge(ctx, 7);
        a0 = 0;
        jal(ctx, 0x4818D4u, gen::fn__sceFlushCache_005033e0);
        v1 = 0x10010000;
        lw(a0, v1, -12288);  // 0x1000D000 D8 fromSPR CHCR
        a0 = a0 & 0x100;
        if (a0 != 0) {
            // 0x004818f0
            charge(ctx, 4);
            a0 = 256;
            sw(a0, v1, -8160);
            sync(ctx, 0);
            sync(ctx, 16);
            for (;;) {
                // 0x00481900
                charge(ctx, 7);
                if (cop0_cond(ctx)) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x0048191c
        charge(ctx, 5);
        v1 = 0x10010000;
        lw(a0, v1, -11264);  // 0x1000D400 D9 toSPR CHCR
        a0 = a0 & 0x100;
        if (a0 != 0) {
            // 0x00481930
            charge(ctx, 4);
            a0 = 512;
            sw(a0, v1, -8160);
            sync(ctx, 0);
            sync(ctx, 16);
            for (;;) {
                // 0x00481940
                charge(ctx, 7);
                if (cop0_cond(ctx)) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0048195c
            charge(ctx, 1);
            v1 = 0x10010000;
            for (;;) {
                // 0x00481960
                charge(ctx, 7);
                lw(a0, v1, -11264);
                a0 = a0 & 0x100;
                if (a0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0048197c
            charge(ctx, 1);
        }
        // 0x00481980
        charge(ctx, 35);
        a0 = 0x70000000;
        lwc1(f0, s4, 104);
        v1 = a0 | 0x3F60;
        sw(v1, sp, 0xE0);
        a2 = a0 | 0x3F40;
        v1 = 0x3F000000;
        a1 = a0 | 0x3F50;
        mtc1(v1, f1);
        t7 = a0 | 0x3FA0;
        v1 = 0x10000;
        swc1(f0, a0, 16224);  // 0x70003F60 SPR+0x3F60
        lwc1(f0, s4, 108);
        swc1(f0, a0, 16228);  // 0x70003F64 SPR+0x3F64
        lwc1(f0, s4, 104);
        swc1(f0, a0, 16232);  // 0x70003F68 SPR+0x3F68
        lwc1(f0, s4, 108);
        swc1(f0, a0, 16236);  // 0x70003F6C SPR+0x3F6C
        lwc1(f0, s5, 0);
        mul_s(f0, f1, f0);
        swc1(f0, a0, 16192);  // 0x70003F40 SPR+0x3F40
        lwc1(f0, s5, 4);
        mul_s(f0, f1, f0);
        swc1(f0, a0, 16196);  // 0x70003F44 SPR+0x3F44
        lwc1(f0, s5, 8);
        mul_s(f0, f1, f0);
        swc1(f0, a0, 16200);  // 0x70003F48 SPR+0x3F48
        lwc1(f0, s6, 0);
        mul_s(f0, f1, f0);
        swc1(f0, a0, 16208);  // 0x70003F50 SPR+0x3F50
        lwc1(f0, s6, 4);
        mul_s(f0, f1, f0);
        swc1(f0, a0, 16212);  // 0x70003F54 SPR+0x3F54
        lwc1(f0, s6, 8);
        mul_s(f0, f1, f0);
        swc1(f0, a0, 16216);  // 0x70003F58 SPR+0x3F58
        for (;;) {
            // 0x00481a0c
            charge(ctx, 7);
            di(ctx);
            sync(ctx, 16);
            mfc0(a0, 12);
            a0 = a0 & v1;
            if (a0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00481a28
        charge(ctx, 79);
        at = 0x3FC90000;
        v1 = at | 0xFDB;
        mtc1(v1, f0);
        mfc1(v1, f0);
        ctc2(v1, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x8, vf10, vf0);  // vaddi.x
        at = 0x40490000;
        a0 = at | 0xFDB;
        mtc1(a0, f0);
        mfc1(v1, f0);
        ctc2(v1, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x4, vf10, vf0);  // vaddi.y
        at = 0x40090000;
        v1 = at | 0xFDB;
        mtc1(v1, f0);
        mfc1(v1, f0);
        ctc2(v1, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x2, vf10, vf0);  // vaddi.z
        mtc1(a0, f0);
        neg_s(f0, f0);
        mfc1(v1, f0);
        ctc2(v1, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x8, vf11, vf0);  // vaddi.x
        at = 0x40840000;
        v1 = at | 0x87ED;
        mtc1(v1, f0);
        neg_s(f0, f0);
        mfc1(v1, f0);
        ctc2(v1, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x4, vf11, vf0);  // vaddi.y
        v1 = 0x0;
        v1 = dsll(v1, 16);
        v1 = dsll(v1, 16);
        v1 = v1 | 0xB94F;
        v1 = dsll(v1, 16);
        v1 = v1 | 0xB21F;
        ctc2(v1, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x2, vf11, vf0);  // vaddi.z
        v1 = 0x0;
        v1 = dsll(v1, 16);
        v1 = dsll(v1, 16);
        v1 = v1 | 0xBE2A;
        v1 = dsll(v1, 16);
        v1 = v1 | 0xAAA4;
        ctc2(v1, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x8, vf12, vf0);  // vaddi.x
        at = 0x3C080000;
        v1 = at | 0x873E;
        ctc2(v1, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x4, vf12, vf0);  // vaddi.y
        at = 0x362E0000;
        v1 = at | 0x9C14;
        ctc2(v1, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x2, vf12, vf0);  // vaddi.z
        v1 = 0x3F800000;
        ctc2(v1, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        vaddi(0x8, vf13, vf0);  // vaddi.x
        ei(ctx);
        v1 = 0x10000;
        for (;;) {
            // 0x00481b64
            charge(ctx, 7);
            di(ctx);
            sync(ctx, 16);
            mfc0(a0, 12);
            a0 = a0 & v1;
            if (a0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00481b80
        charge(ctx, 8);
        lqc2(vf8, a2, 0);
        lqc2(vf9, a1, 0);
        lw(v1, sp, 0xE0);
        lqc2(vf15, v1, 0);
        ei(ctx);
        v1 = slti(s7, 176);
        if (v1 == 0) {
            // 0x00481ba0
            charge(ctx, 11);
            t0 = 0x70000000;
            a0 = 0x10010000;
            t5 = 256;
            t4 = 512;
            t3 = 44;
            t2 = 704;
            t1 = 88;
            fp = 0x840;
            a3 = t0 | 0x2C0;
            a2 = t0 | 0x840;
            a1 = t0 | 0x1340;
            for (;;) {
                // 0x00481bcc
                charge(ctx, 4);
                lw(v1, a0, -12288);
                v1 = v1 & 0x100;
                if (v1 != 0) {
                    // 0x00481bdc
                    charge(ctx, 3);
                    sw(t5, a0, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x00481be8
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00481c04
                    charge(ctx, 1);
                }
                // 0x00481c08
                charge(ctx, 4);
                lw(v1, a0, -11264);
                v1 = v1 & 0x100;
                if (v1 != 0) {
                    // 0x00481c18
                    charge(ctx, 4);
                    sw(t4, a0, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x00481c28
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00481c44
                    charge(ctx, 1);
                    for (;;) {
                        // 0x00481c48
                        charge(ctx, 7);
                        lw(v1, a0, -11264);
                        v1 = v1 & 0x100;
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00481c64
                    charge(ctx, 1);
                }
                // 0x00481c68
                charge(ctx, 11);
                sw(t4, a0, -8176);
                sw(zero, a0, -11136);
                sw(s2, a0, -11248);
                sw(t3, a0, -11232);
                sw(t5, a0, -11264);
                sync(ctx, 0);
                sync(ctx, 16);
                lw(v1, a0, -11264);
                v1 = v1 & 0x100;
                if (v1 != 0) {
                    // 0x00481c94
                    charge(ctx, 3);
                    sw(t4, a0, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x00481ca0
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00481cbc
                    charge(ctx, 1);
                    for (;;) {
                        // 0x00481cc0
                        charge(ctx, 7);
                        lw(v1, a0, -11264);
                        v1 = v1 & 0x100;
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00481cdc
                    charge(ctx, 1);
                }
                // 0x00481ce0
                charge(ctx, 11);
                sw(t4, a0, -8176);
                sw(t2, a0, -11136);
                sw(s0, a0, -11248);
                sw(t1, a0, -11232);
                sw(t5, a0, -11264);
                sync(ctx, 0);
                sync(ctx, 16);
                lw(v1, a0, -11264);
                v1 = v1 & 0x100;
                if (v1 != 0) {
                    // 0x00481d0c
                    charge(ctx, 3);
                    sw(t4, a0, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x00481d18
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00481d34
                    charge(ctx, 1);
                    for (;;) {
                        // 0x00481d38
                        charge(ctx, 7);
                        lw(v1, a0, -11264);
                        v1 = v1 & 0x100;
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00481d54
                    charge(ctx, 1);
                }
                // 0x00481d58
                charge(ctx, 12);
                sw(t4, a0, -8176);
                sw(fp, a0, -11136);
                v1 = 176;
                sw(s3, a0, -11248);
                sw(v1, a0, -11232);
                sw(t5, a0, -11264);
                sync(ctx, 0);
                sync(ctx, 16);
                lw(v1, a0, -11264);
                v1 = v1 & 0x100;
                if (v1 != 0) {
                    // 0x00481d88
                    charge(ctx, 4);
                    sw(t4, a0, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x00481d98
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00481db4
                    charge(ctx, 1);
                    for (;;) {
                        // 0x00481db8
                        charge(ctx, 7);
                        lw(v1, a0, -11264);
                        v1 = v1 & 0x100;
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00481dd4
                    charge(ctx, 1);
                }
                // 0x00481dd8
                charge(ctx, 6);
                s5 = t0;
                s4 = a3;
                t9 = a2;
                t8 = a1;
                s6 = 0;
                for (;;) {
                    // 0x00481df0
                    charge(ctx, 8);
                    lwc1(f0, s5, 0);
                    swc1(f0, t7, 0);
                    lwc1(f0, s5, 4);
                    swc1(f0, t7, 4);
                    lwc1(f0, s5, 0);
                    swc1(f0, t7, 8);
                    lwc1(f0, s5, 4);
                    swc1(f0, t7, 12);
                    for (;;) {
                        // 0x00481e10
                        charge(ctx, 8);
                        di(ctx);
                        sync(ctx, 16);
                        mfc0(t6, 12);
                        v1 = 0x10000;
                        t6 = t6 & v1;
                        if (t6 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00481e30
                    charge(ctx, 78);
                    lqc2(vf1, t7, 0);
                    vabs(0xC, vf7, vf1);  // vabs.xy
                    vadda_bc(0xF, vf0, vf10, 0);  // vaddax.xyzw
                    vmsub_bc(0xC, vf7, vf7, vf0, 3);  // vmsubw.xy
                    vadda_bc(0xE, vf0, vf10, 1);  // vadday.xyz
                    vadda_bc(0x1, vf0, vf10, 2);  // vaddaz.w
                    vmsub_bc(0x3, vf2, vf1, vf0, 3);  // vmsubw.zw
                    vadda_bc(0xE, vf0, vf11, 0);  // vaddax.xyz
                    vadda_bc(0x1, vf0, vf11, 1);  // vadday.w
                    vmsub_bc(0x3, vf3, vf1, vf0, 3);  // vmsubw.zw
                    vmini(0x3, vf2, vf1, vf2);  // vmini.zw
                    vmax(0x3, vf7, vf2, vf3);  // vmax.zw
                    vmul(0xF, vf2, vf7, vf7);  // vmul.xyzw
                    vmul_bc(0xF, vf6, vf7, vf11, 2);  // vmulz.xyzw
                    vmul_bc(0xF, vf4, vf7, vf12, 0);  // vmulx.xyzw
                    vmul_bc(0xF, vf5, vf7, vf12, 1);  // vmuly.xyzw
                    vmul(0xF, vf3, vf2, vf2);  // vmul.xyzw
                    vmul(0xF, vf6, vf6, vf2);  // vmul.xyzw
                    vmula(0xF, vf4, vf2);  // vmula.xyzw
                    vmul_bc(0xF, vf4, vf7, vf12, 2);  // vmulz.xyzw
                    vmul(0xF, vf2, vf3, vf3);  // vmul.xyzw
                    vmadda(0xF, vf6, vf3);  // vmadda.xyzw
                    vmadda(0xF, vf5, vf3);  // vmadda.xyzw
                    vmadda_bc(0xF, vf7, vf13, 0);  // vmaddax.xyzw
                    vmadd(0xF, vf7, vf4, vf2);  // vmadd.xyzw
                    lqc2(vf20, t9, 0);
                    lqc2(vf27, t9, 16);
                    lqc2(vf14, s4, 0);
                    vmula_bc(0xF, vf8, vf7, 0);  // vmulax.xyzw
                    vmsub_bc(0xF, vf18, vf9, vf7, 2);  // vmsubz.xyzw
                    vadd(0xF, vf2, vf15, vf14);  // vadd.xyzw
                    vsub(0xF, vf3, vf15, vf14);  // vsub.xyzw
                    vmula_bc(0xF, vf9, vf7, 0);  // vmulax.xyzw
                    vmadd_bc(0xF, vf19, vf8, vf7, 2);  // vmaddz.xyzw
                    vmula_bc(0xF, vf8, vf7, 1);  // vmulay.xyzw
                    vmsub_bc(0xF, vf25, vf9, vf7, 3);  // vmsubw.xyzw
                    vmula_bc(0xF, vf9, vf7, 1);  // vmulay.xyzw
                    vmadd_bc(0xF, vf26, vf8, vf7, 3);  // vmaddw.xyzw
                    vmula_bc(0xF, vf18, vf3, 0);  // vmulax.xyzw
                    vmadd_bc(0xF, vf21, vf19, vf3, 1);  // vmaddy.xyzw
                    vmula_bc(0xF, vf18, vf2, 0);  // vmulax.xyzw
                    vmadd_bc(0xF, vf22, vf19, vf3, 1);  // vmaddy.xyzw
                    vmula_bc(0xF, vf18, vf2, 0);  // vmulax.xyzw
                    vmadd_bc(0xF, vf23, vf19, vf2, 1);  // vmaddy.xyzw
                    vmula_bc(0xF, vf18, vf3, 0);  // vmulax.xyzw
                    vmadd_bc(0xF, vf24, vf19, vf2, 1);  // vmaddy.xyzw
                    vmula_bc(0xF, vf25, vf3, 2);  // vmulaz.xyzw
                    vmadd_bc(0xF, vf28, vf26, vf3, 3);  // vmaddw.xyzw
                    vmula_bc(0xF, vf25, vf2, 2);  // vmulaz.xyzw
                    vmadd_bc(0xF, vf29, vf26, vf3, 3);  // vmaddw.xyzw
                    vmula_bc(0xF, vf25, vf2, 2);  // vmulaz.xyzw
                    vmadd_bc(0xF, vf30, vf26, vf2, 3);  // vmaddw.xyzw
                    vmula_bc(0xF, vf25, vf3, 2);  // vmulaz.xyzw
                    vmadd_bc(0xF, vf31, vf26, vf2, 3);  // vmaddw.xyzw
                    vadd(0xF, vf21, vf21, vf20);  // vadd.xyzw
                    vadd(0xF, vf22, vf22, vf20);  // vadd.xyzw
                    vadd(0xF, vf23, vf23, vf20);  // vadd.xyzw
                    vadd(0xF, vf24, vf24, vf20);  // vadd.xyzw
                    vadd(0xF, vf28, vf28, vf27);  // vadd.xyzw
                    vadd(0xF, vf29, vf29, vf27);  // vadd.xyzw
                    vadd(0xF, vf30, vf30, vf27);  // vadd.xyzw
                    vadd(0xF, vf31, vf31, vf27);  // vadd.xyzw
                    sqc2(vf21, t8, 0);
                    sqc2(vf22, t8, 16);
                    sqc2(vf23, t8, 32);
                    sqc2(vf24, t8, 48);
                    sqc2(vf28, t8, 64);
                    sqc2(vf29, t8, 80);
                    sqc2(vf30, t8, 96);
                    sqc2(vf31, t8, 112);
                    ei(ctx);
                    s6 = addiu(s6, 2);
                    v1 = slti(s6, 176);
                    t9 = addiu(t9, 32);
                    s4 = addiu(s4, 16);
                    s5 = addiu(s5, 8);
                    t8 = addiu(t8, 128);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00481f68
                charge(ctx, 4);
                lw(v1, a0, -12288);
                v1 = v1 & 0x100;
                if (v1 != 0) {
                    // 0x00481f78
                    charge(ctx, 4);
                    sw(t5, a0, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x00481f88
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00481fa4
                    charge(ctx, 1);
                }
                // 0x00481fa8
                charge(ctx, 4);
                lw(v1, a0, -11264);
                v1 = v1 & 0x100;
                if (v1 != 0) {
                    // 0x00481fb8
                    charge(ctx, 4);
                    sw(t4, a0, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x00481fc8
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00481fe4
                    charge(ctx, 1);
                    for (;;) {
                        // 0x00481fe8
                        charge(ctx, 7);
                        lw(v1, a0, -11264);
                        v1 = v1 & 0x100;
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00482004
                    charge(ctx, 1);
                }
                // 0x00482008
                charge(ctx, 15);
                sw(t5, a0, -8176);
                v1 = 4928;
                sw(v1, a0, -12160);
                sw(s1, a0, -12272);
                sw(t2, a0, -12256);
                sw(t5, a0, -12288);
                sync(ctx, 0);
                sync(ctx, 16);
                s7 = addiu(s7, -176);
                s3 = addiu(s3, 2816);
                at = slti(s7, 176);
                s1 = addiu(s1, 11264);
                s2 = addiu(s2, 704);
                s0 = addiu(s0, 1408);
                if (at != 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00482044
            charge(ctx, 1);
        }
        // 0x00482048
        charge(ctx, 3);
        at = slti(s7, 4);
        if (at == 0) {
            // 0x00482054
            charge(ctx, 2);
            v1 = sra(s7, 2);
            if (i64(s7) < 0) {
                // 0x0048205c
                charge(ctx, 2);
                v1 = addiu(s7, 3);
                v1 = sra(v1, 2);
            }
            // 0x00482064
            charge(ctx, 5);
            a0 = 0x10010000;
            lw(a1, a0, -12288);  // 0x1000D000 D8 fromSPR CHCR
            a1 = a1 & 0x100;
            v1 = sll(v1, 2);
            if (a1 != 0) {
                // 0x00482078
                charge(ctx, 4);
                a1 = 256;
                sw(a1, a0, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x00482088
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x004820a4
            charge(ctx, 5);
            a0 = 0x10010000;
            lw(a1, a0, -11264);  // 0x1000D400 D9 toSPR CHCR
            a1 = a1 & 0x100;
            if (a1 != 0) {
                // 0x004820b8
                charge(ctx, 4);
                a1 = 512;
                sw(a1, a0, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x004820c8
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004820e4
                charge(ctx, 1);
                a0 = 0x10010000;
                for (;;) {
                    // 0x004820e8
                    charge(ctx, 7);
                    lw(a1, a0, -11264);
                    a1 = a1 & 0x100;
                    if (a1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00482104
                charge(ctx, 1);
            }
            // 0x00482108
            charge(ctx, 7);
            a1 = 512;
            a0 = 0x10010000;
            a2 = sra(v1, 2);
            sw(a1, a0, -8176);  // 0x1000E010 D_STAT
            sw(zero, a0, -11136);  // 0x1000D480 D9 toSPR SADR
            sw(s2, a0, -11248);  // 0x1000D410 D9 toSPR MADR
            if (i64(v1) < 0) {
                // 0x00482124
                charge(ctx, 2);
                a0 = addiu(v1, 3);
                a2 = sra(a0, 2);
            }
            // 0x0048212c
            charge(ctx, 10);
            a0 = 0x10010000;
            a1 = 256;
            sw(a2, a0, -11232);  // 0x1000D420 D9 toSPR QWC
            sw(a1, a0, -11264);  // 0x1000D400 D9 toSPR CHCR
            sync(ctx, 0);
            sync(ctx, 16);
            lw(a1, a0, -11264);  // 0x1000D400 D9 toSPR CHCR
            a1 = a1 & 0x100;
            if (a1 != 0) {
                // 0x00482154
                charge(ctx, 4);
                a1 = 512;
                sw(a1, a0, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x00482164
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00482180
                charge(ctx, 1);
                a0 = 0x10010000;
                for (;;) {
                    // 0x00482184
                    charge(ctx, 7);
                    lw(a1, a0, -11264);
                    a1 = a1 & 0x100;
                    if (a1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x004821a0
            charge(ctx, 8);
            a2 = 512;
            a0 = 0x10010000;
            a1 = 704;
            sw(a2, a0, -8176);  // 0x1000E010 D_STAT
            sw(a1, a0, -11136);  // 0x1000D480 D9 toSPR SADR
            a2 = sra(v1, 1);
            sw(s0, a0, -11248);  // 0x1000D410 D9 toSPR MADR
            if (i64(v1) < 0) {
                // 0x004821c0
                charge(ctx, 2);
                a0 = addiu(v1, 1);
                a2 = sra(a0, 1);
            }
            // 0x004821c8
            charge(ctx, 10);
            a0 = 0x10010000;
            a1 = 256;
            sw(a2, a0, -11232);  // 0x1000D420 D9 toSPR QWC
            sw(a1, a0, -11264);  // 0x1000D400 D9 toSPR CHCR
            sync(ctx, 0);
            sync(ctx, 16);
            lw(a1, a0, -11264);  // 0x1000D400 D9 toSPR CHCR
            a1 = a1 & 0x100;
            if (a1 != 0) {
                // 0x004821f0
                charge(ctx, 4);
                a1 = 512;
                sw(a1, a0, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x00482200
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0048221c
                charge(ctx, 1);
                a0 = 0x10010000;
                for (;;) {
                    // 0x00482220
                    charge(ctx, 7);
                    lw(a1, a0, -11264);
                    a1 = a1 & 0x100;
                    if (a1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0048223c
                charge(ctx, 1);
            }
            // 0x00482240
            charge(ctx, 15);
            a3 = 512;
            a0 = 0x10010000;
            a2 = 2112;
            sw(a3, a0, -8176);  // 0x1000E010 D_STAT
            a1 = 256;
            sw(a2, a0, -11136);  // 0x1000D480 D9 toSPR SADR
            sw(s3, a0, -11248);  // 0x1000D410 D9 toSPR MADR
            sw(v1, a0, -11232);  // 0x1000D420 D9 toSPR QWC
            sw(a1, a0, -11264);  // 0x1000D400 D9 toSPR CHCR
            sync(ctx, 0);
            sync(ctx, 16);
            lw(a1, a0, -11264);  // 0x1000D400 D9 toSPR CHCR
            a1 = a1 & 0x100;
            if (a1 != 0) {
                // 0x0048227c
                charge(ctx, 3);
                sw(a3, a0, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x00482288
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004822a4
                charge(ctx, 1);
                a0 = 0x10010000;
                for (;;) {
                    // 0x004822a8
                    charge(ctx, 7);
                    lw(a1, a0, -11264);
                    a1 = a1 & 0x100;
                    if (a1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004822c4
                charge(ctx, 1);
            }
            // 0x004822c8
            charge(ctx, 7);
            a3 = 0x70000000;
            at = slt(0, v1);
            s4 = a3 | 0x2C0;
            t9 = a3 | 0x840;
            t8 = a3 | 0x1340;
            a2 = 0;
            if (at != 0) {
                // 0x004822e4
                charge(ctx, 1);
                a1 = 0x10000;
                for (;;) {
                    // 0x004822e8
                    charge(ctx, 8);
                    lwc1(f0, a3, 0);
                    swc1(f0, t7, 0);
                    lwc1(f0, a3, 4);
                    swc1(f0, t7, 4);
                    lwc1(f0, a3, 0);
                    swc1(f0, t7, 8);
                    lwc1(f0, a3, 4);
                    swc1(f0, t7, 12);
                    for (;;) {
                        // 0x00482308
                        charge(ctx, 7);
                        di(ctx);
                        sync(ctx, 16);
                        mfc0(a0, 12);
                        a0 = a0 & a1;
                        if (a0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00482324
                    charge(ctx, 78);
                    lqc2(vf1, t7, 0);
                    vabs(0xC, vf7, vf1);  // vabs.xy
                    vadda_bc(0xF, vf0, vf10, 0);  // vaddax.xyzw
                    vmsub_bc(0xC, vf7, vf7, vf0, 3);  // vmsubw.xy
                    vadda_bc(0xE, vf0, vf10, 1);  // vadday.xyz
                    vadda_bc(0x1, vf0, vf10, 2);  // vaddaz.w
                    vmsub_bc(0x3, vf2, vf1, vf0, 3);  // vmsubw.zw
                    vadda_bc(0xE, vf0, vf11, 0);  // vaddax.xyz
                    vadda_bc(0x1, vf0, vf11, 1);  // vadday.w
                    vmsub_bc(0x3, vf3, vf1, vf0, 3);  // vmsubw.zw
                    vmini(0x3, vf2, vf1, vf2);  // vmini.zw
                    vmax(0x3, vf7, vf2, vf3);  // vmax.zw
                    vmul(0xF, vf2, vf7, vf7);  // vmul.xyzw
                    vmul_bc(0xF, vf6, vf7, vf11, 2);  // vmulz.xyzw
                    vmul_bc(0xF, vf4, vf7, vf12, 0);  // vmulx.xyzw
                    vmul_bc(0xF, vf5, vf7, vf12, 1);  // vmuly.xyzw
                    vmul(0xF, vf3, vf2, vf2);  // vmul.xyzw
                    vmul(0xF, vf6, vf6, vf2);  // vmul.xyzw
                    vmula(0xF, vf4, vf2);  // vmula.xyzw
                    vmul_bc(0xF, vf4, vf7, vf12, 2);  // vmulz.xyzw
                    vmul(0xF, vf2, vf3, vf3);  // vmul.xyzw
                    vmadda(0xF, vf6, vf3);  // vmadda.xyzw
                    vmadda(0xF, vf5, vf3);  // vmadda.xyzw
                    vmadda_bc(0xF, vf7, vf13, 0);  // vmaddax.xyzw
                    vmadd(0xF, vf7, vf4, vf2);  // vmadd.xyzw
                    lqc2(vf20, t9, 0);
                    lqc2(vf27, t9, 16);
                    lqc2(vf14, s4, 0);
                    vmula_bc(0xF, vf8, vf7, 0);  // vmulax.xyzw
                    vmsub_bc(0xF, vf18, vf9, vf7, 2);  // vmsubz.xyzw
                    vadd(0xF, vf2, vf15, vf14);  // vadd.xyzw
                    vsub(0xF, vf3, vf15, vf14);  // vsub.xyzw
                    vmula_bc(0xF, vf9, vf7, 0);  // vmulax.xyzw
                    vmadd_bc(0xF, vf19, vf8, vf7, 2);  // vmaddz.xyzw
                    vmula_bc(0xF, vf8, vf7, 1);  // vmulay.xyzw
                    vmsub_bc(0xF, vf25, vf9, vf7, 3);  // vmsubw.xyzw
                    vmula_bc(0xF, vf9, vf7, 1);  // vmulay.xyzw
                    vmadd_bc(0xF, vf26, vf8, vf7, 3);  // vmaddw.xyzw
                    vmula_bc(0xF, vf18, vf3, 0);  // vmulax.xyzw
                    vmadd_bc(0xF, vf21, vf19, vf3, 1);  // vmaddy.xyzw
                    vmula_bc(0xF, vf18, vf2, 0);  // vmulax.xyzw
                    vmadd_bc(0xF, vf22, vf19, vf3, 1);  // vmaddy.xyzw
                    vmula_bc(0xF, vf18, vf2, 0);  // vmulax.xyzw
                    vmadd_bc(0xF, vf23, vf19, vf2, 1);  // vmaddy.xyzw
                    vmula_bc(0xF, vf18, vf3, 0);  // vmulax.xyzw
                    vmadd_bc(0xF, vf24, vf19, vf2, 1);  // vmaddy.xyzw
                    vmula_bc(0xF, vf25, vf3, 2);  // vmulaz.xyzw
                    vmadd_bc(0xF, vf28, vf26, vf3, 3);  // vmaddw.xyzw
                    vmula_bc(0xF, vf25, vf2, 2);  // vmulaz.xyzw
                    vmadd_bc(0xF, vf29, vf26, vf3, 3);  // vmaddw.xyzw
                    vmula_bc(0xF, vf25, vf2, 2);  // vmulaz.xyzw
                    vmadd_bc(0xF, vf30, vf26, vf2, 3);  // vmaddw.xyzw
                    vmula_bc(0xF, vf25, vf3, 2);  // vmulaz.xyzw
                    vmadd_bc(0xF, vf31, vf26, vf2, 3);  // vmaddw.xyzw
                    vadd(0xF, vf21, vf21, vf20);  // vadd.xyzw
                    vadd(0xF, vf22, vf22, vf20);  // vadd.xyzw
                    vadd(0xF, vf23, vf23, vf20);  // vadd.xyzw
                    vadd(0xF, vf24, vf24, vf20);  // vadd.xyzw
                    vadd(0xF, vf28, vf28, vf27);  // vadd.xyzw
                    vadd(0xF, vf29, vf29, vf27);  // vadd.xyzw
                    vadd(0xF, vf30, vf30, vf27);  // vadd.xyzw
                    vadd(0xF, vf31, vf31, vf27);  // vadd.xyzw
                    sqc2(vf21, t8, 0);
                    sqc2(vf22, t8, 16);
                    sqc2(vf23, t8, 32);
                    sqc2(vf24, t8, 48);
                    sqc2(vf28, t8, 64);
                    sqc2(vf29, t8, 80);
                    sqc2(vf30, t8, 96);
                    sqc2(vf31, t8, 112);
                    ei(ctx);
                    a2 = addiu(a2, 2);
                    a0 = slt(a2, v1);
                    t9 = addiu(t9, 32);
                    s4 = addiu(s4, 16);
                    a3 = addiu(a3, 8);
                    t8 = addiu(t8, 128);
                    if (a0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0048245c
                charge(ctx, 1);
            }
            // 0x00482460
            charge(ctx, 5);
            a0 = 0x10010000;
            lw(a1, a0, -12288);  // 0x1000D000 D8 fromSPR CHCR
            a1 = a1 & 0x100;
            if (a1 != 0) {
                // 0x00482474
                charge(ctx, 4);
                a1 = 256;
                sw(a1, a0, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x00482484
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x004824a0
            charge(ctx, 5);
            a0 = 0x10010000;
            lw(a1, a0, -11264);  // 0x1000D400 D9 toSPR CHCR
            a1 = a1 & 0x100;
            if (a1 != 0) {
                // 0x004824b4
                charge(ctx, 4);
                a1 = 512;
                sw(a1, a0, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x004824c4
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004824e0
                charge(ctx, 1);
                a0 = 0x10010000;
                for (;;) {
                    // 0x004824e4
                    charge(ctx, 7);
                    lw(a1, a0, -11264);
                    a1 = a1 & 0x100;
                    if (a1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x00482500
            charge(ctx, 17);
            a3 = 256;
            a0 = 0x10010000;
            a2 = 4928;
            sw(a3, a0, -8176);  // 0x1000E010 D_STAT
            a1 = sll(v1, 2);
            sw(a2, a0, -12160);  // 0x1000D080 D8 fromSPR SADR
            sw(s1, a0, -12272);  // 0x1000D010 D8 fromSPR MADR
            sw(a1, a0, -12256);  // 0x1000D020 D8 fromSPR QWC
            sw(a3, a0, -12288);  // 0x1000D000 D8 fromSPR CHCR
            sync(ctx, 0);
            sync(ctx, 16);
            a0 = sll(a1, 4);
            a1 = sll(v1, 4);
            s1 = addu(s1, a0);
            s3 = addu(s3, a1);
            a0 = sra(v1, 2);
            if (i64(v1) < 0) {
                // 0x00482544
                charge(ctx, 2);
                a0 = addiu(v1, 3);
                a0 = sra(a0, 2);
            }
            // 0x0048254c
            charge(ctx, 4);
            a1 = sll(a0, 4);
            a0 = sra(v1, 1);
            s2 = addu(s2, a1);
            if (i64(v1) < 0) {
                // 0x0048255c
                charge(ctx, 2);
                a0 = addiu(v1, 1);
                a0 = sra(a0, 1);
            }
            // 0x00482564
            charge(ctx, 3);
            a0 = sll(a0, 4);
            s7 = subu(s7, v1);
            s0 = addu(s0, a0);
        }
        // 0x00482570
        charge(ctx, 3);
        at = slt(0, s7);
        a2 = 0;
        if (at != 0) {
            // 0x0048257c
            charge(ctx, 3);
            lq(v1, sp, 0xA0);
            a1 = 0x10000;
            a0 = sll(v1, 2);
            for (;;) {
                // 0x00482588
                charge(ctx, 10);
                lwc1(f0, s2, 0);
                lw(v1, sp, 0xE0);
                swc1(f0, t7, 0);
                lwc1(f0, s2, 0);
                swc1(f0, t7, 8);
                lwc1(f0, s0, 0);
                swc1(f0, v1, 0);
                lwc1(f0, s0, 4);
                swc1(f0, v1, 4);
                for (;;) {
                    // 0x004825b0
                    charge(ctx, 7);
                    di(ctx);
                    sync(ctx, 16);
                    mfc0(v1, 12);
                    v1 = v1 & a1;
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004825cc
                charge(ctx, 61);
                lqc2(vf1, t7, 0);
                vabs(0xC, vf7, vf1);  // vabs.xy
                vadda_bc(0xF, vf0, vf10, 0);  // vaddax.xyzw
                vmsub_bc(0xC, vf7, vf7, vf0, 3);  // vmsubw.xy
                vadda_bc(0xE, vf0, vf10, 1);  // vadday.xyz
                vadda_bc(0x1, vf0, vf10, 2);  // vaddaz.w
                vmsub_bc(0x3, vf2, vf1, vf0, 3);  // vmsubw.zw
                vadda_bc(0xE, vf0, vf11, 0);  // vaddax.xyz
                vadda_bc(0x1, vf0, vf11, 1);  // vadday.w
                vmsub_bc(0x3, vf3, vf1, vf0, 3);  // vmsubw.zw
                vmini(0x3, vf2, vf1, vf2);  // vmini.zw
                vmax(0x3, vf7, vf2, vf3);  // vmax.zw
                vmul(0xF, vf2, vf7, vf7);  // vmul.xyzw
                vmul_bc(0xF, vf6, vf7, vf11, 2);  // vmulz.xyzw
                vmul_bc(0xF, vf4, vf7, vf12, 0);  // vmulx.xyzw
                vmul_bc(0xF, vf5, vf7, vf12, 1);  // vmuly.xyzw
                vmul(0xF, vf3, vf2, vf2);  // vmul.xyzw
                vmul(0xF, vf6, vf6, vf2);  // vmul.xyzw
                vmula(0xF, vf4, vf2);  // vmula.xyzw
                vmul_bc(0xF, vf4, vf7, vf12, 2);  // vmulz.xyzw
                vmul(0xF, vf2, vf3, vf3);  // vmul.xyzw
                vmadda(0xF, vf6, vf3);  // vmadda.xyzw
                vmadda(0xF, vf5, vf3);  // vmadda.xyzw
                vmadda_bc(0xF, vf7, vf13, 0);  // vmaddax.xyzw
                vmadd(0xF, vf7, vf4, vf2);  // vmadd.xyzw
                lqc2(vf20, s3, 0);
                lw(v1, sp, 0xE0);
                lqc2(vf14, v1, 0);
                vmula_bc(0xF, vf8, vf7, 0);  // vmulax.xyzw
                vmsub_bc(0xF, vf18, vf9, vf7, 2);  // vmsubz.xyzw
                vadd(0xF, vf2, vf15, vf14);  // vadd.xyzw
                vsub(0xF, vf3, vf15, vf14);  // vsub.xyzw
                vmula_bc(0xF, vf9, vf7, 0);  // vmulax.xyzw
                vmadd_bc(0xF, vf19, vf8, vf7, 2);  // vmaddz.xyzw
                vmula_bc(0xF, vf18, vf3, 0);  // vmulax.xyzw
                vmadd_bc(0xF, vf21, vf19, vf3, 1);  // vmaddy.xyzw
                vmula_bc(0xF, vf18, vf2, 0);  // vmulax.xyzw
                vmadd_bc(0xF, vf22, vf19, vf3, 1);  // vmaddy.xyzw
                vmula_bc(0xF, vf18, vf2, 0);  // vmulax.xyzw
                vmadd_bc(0xF, vf23, vf19, vf2, 1);  // vmaddy.xyzw
                vmula_bc(0xF, vf18, vf3, 0);  // vmulax.xyzw
                vmadd_bc(0xF, vf24, vf19, vf2, 1);  // vmaddy.xyzw
                vadd(0xF, vf21, vf21, vf20);  // vadd.xyzw
                vadd(0xF, vf22, vf22, vf20);  // vadd.xyzw
                vadd(0xF, vf23, vf23, vf20);  // vadd.xyzw
                vadd(0xF, vf24, vf24, vf20);  // vadd.xyzw
                sqc2(vf21, s1, 0);
                sqc2(vf22, s1, 16);
                sqc2(vf23, s1, 32);
                sqc2(vf24, s1, 48);
                ei(ctx);
                a2 = addiu(a2, 1);
                lq(v1, sp, 0xD0);
                s3 = addu(s3, v1);
                lq(v1, sp, 0xB0);
                s0 = addu(s0, v1);
                lq(v1, sp, 0xC0);
                s2 = addu(s2, v1);
                v1 = slt(a2, s7);
                s1 = addu(s1, a0);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004826c0
            charge(ctx, 2);
        }
    }
    // 0x00482a20 (the shared epilogue, written out on this path)
    charge(ctx, 12);
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
}

// 0x00482A50 sub_482A50 -- 1824 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Scratchpad DMA kernel, plain variant (no SPR parameter block).
void sub_482A50(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    Vf vf1{ctx, 1}, vf2{ctx, 2}, vf3{ctx, 3}, vf4{ctx, 4}, vf6{ctx, 6}, vf7{ctx, 7}, vf8{ctx, 8}, vf10{ctx, 10}, vf11{ctx, 11}, vf12{ctx, 12}, vf13{ctx, 13};
    // 0x00482a50
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s2, a0, 0);
    s0 = a3;
    lw(a3, t0, 16);
    lw(a0, a0, 4);
    v1 = sll(a0, 2);
    lw(s1, t0, 12);
    if (a3 != v1) {
        // 0x0048308c
        charge(ctx, 1);
        v1 = 0x10000;
        for (;;) {
            // 0x00483090
            charge(ctx, 7);
            di(ctx);
            sync(ctx, 16);
            mfc0(a1, 12);
            a1 = a1 & v1;
            if (a1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004830ac
        charge(ctx, 10);
        v1 = 0x3F000000;
        mtc1(v1, f0);
        mfc1(v1, f0);
        ctc2(v1, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        ei(ctx);
        at = slt(0, s0);
        a2 = 0;
        if (at != 0) {
            // 0x004830d4
            charge(ctx, 2);
            a0 = sll(a0, 2);
            a1 = 0x10000;
            for (;;) {
                // 0x004830dc
                charge(ctx, 1);
                for (;;) {
                    // 0x004830e0
                    charge(ctx, 7);
                    di(ctx);
                    sync(ctx, 16);
                    mfc0(v1, 12);
                    v1 = v1 & a1;
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004830fc
                charge(ctx, 22);
                lqc2(vf1, s1, 0);
                lqc2(vf2, s1, 16);
                lqc2(vf3, s1, 32);
                lqc2(vf4, s1, 48);
                vmuli(0xF, vf6, vf1);  // vmuli.xyzw
                vmuli(0xF, vf7, vf2);  // vmuli.xyzw
                vadd(0xF, vf8, vf4, vf7);  // vadd.xyzw
                vadd(0xF, vf10, vf8, vf6);  // vadd.xyzw
                vsub(0xF, vf11, vf10, vf1);  // vsub.xyzw
                vsub(0xF, vf12, vf10, vf2);  // vsub.xyzw
                vsub(0xF, vf13, vf11, vf2);  // vsub.xyzw
                sqc2(vf10, s2, 48);
                sqc2(vf11, s2, 32);
                sqc2(vf12, s2, 0);
                sqc2(vf13, s2, 16);
                s1 = addu(s1, a3);
                s2 = addu(s2, a0);
                ei(ctx);
                a2 = addiu(a2, 1);
                v1 = slt(a2, s0);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00483154
            charge(ctx, 1);
        }
    } else {
        // 0x00482a80
        charge(ctx, 7);
        a0 = 0;
        jal(ctx, 0x482A80u, gen::fn__sceFlushCache_005033e0);
        v1 = 0x10010000;
        lw(a0, v1, -12288);  // 0x1000D000 D8 fromSPR CHCR
        a0 = a0 & 0x100;
        if (a0 != 0) {
            // 0x00482a9c
            charge(ctx, 4);
            a0 = 256;
            sw(a0, v1, -8160);
            sync(ctx, 0);
            sync(ctx, 16);
            for (;;) {
                // 0x00482aac
                charge(ctx, 7);
                if (cop0_cond(ctx)) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x00482ac8
        charge(ctx, 5);
        v1 = 0x10010000;
        lw(a0, v1, -11264);  // 0x1000D400 D9 toSPR CHCR
        a0 = a0 & 0x100;
        if (a0 != 0) {
            // 0x00482adc
            charge(ctx, 4);
            a0 = 512;
            sw(a0, v1, -8160);
            sync(ctx, 0);
            sync(ctx, 16);
            for (;;) {
                // 0x00482aec
                charge(ctx, 7);
                if (cop0_cond(ctx)) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00482b08
            charge(ctx, 1);
            v1 = 0x10010000;
            for (;;) {
                // 0x00482b0c
                charge(ctx, 7);
                lw(a0, v1, -11264);
                a0 = a0 & 0x100;
                if (a0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x00482b28
        charge(ctx, 1);
        v1 = 0x10000;
        for (;;) {
            // 0x00482b2c
            charge(ctx, 7);
            di(ctx);
            sync(ctx, 16);
            mfc0(a0, 12);
            a0 = a0 & v1;
            if (a0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00482b48
        charge(ctx, 10);
        v1 = 0x3F000000;
        mtc1(v1, f0);
        mfc1(v1, f0);
        ctc2(v1, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        ei(ctx);
        v1 = slti(s0, 127);
        if (v1 == 0) {
            // 0x00482b70
            charge(ctx, 8);
            t4 = 0x70000000;
            a3 = 0x10010000;
            t2 = 0x10000;
            a1 = 256;
            a0 = 512;
            v1 = 508;
            t3 = t4 | 0x1FC0;
            t0 = 8128;
            for (;;) {
                // 0x00482b90
                charge(ctx, 4);
                lw(a2, a3, -12288);
                a2 = a2 & 0x100;
                if (a2 != 0) {
                    // 0x00482ba0
                    charge(ctx, 4);
                    sw(a1, a3, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x00482bb0
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00482bcc
                    charge(ctx, 1);
                }
                // 0x00482bd0
                charge(ctx, 4);
                lw(a2, a3, -11264);
                a2 = a2 & 0x100;
                if (a2 != 0) {
                    // 0x00482be0
                    charge(ctx, 4);
                    sw(a0, a3, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x00482bf0
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00482c0c
                    charge(ctx, 1);
                    for (;;) {
                        // 0x00482c10
                        charge(ctx, 7);
                        lw(a2, a3, -11264);
                        a2 = a2 & 0x100;
                        if (a2 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00482c2c
                    charge(ctx, 1);
                }
                // 0x00482c30
                charge(ctx, 11);
                sw(a0, a3, -8176);
                sw(zero, a3, -11136);
                sw(s1, a3, -11248);
                sw(v1, a3, -11232);
                sw(a1, a3, -11264);
                sync(ctx, 0);
                sync(ctx, 16);
                lw(a2, a3, -11264);
                a2 = a2 & 0x100;
                if (a2 != 0) {
                    // 0x00482c5c
                    charge(ctx, 3);
                    sw(a0, a3, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x00482c68
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00482c84
                    charge(ctx, 1);
                    for (;;) {
                        // 0x00482c88
                        charge(ctx, 7);
                        lw(a2, a3, -11264);
                        a2 = a2 & 0x100;
                        if (a2 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00482ca4
                    charge(ctx, 1);
                }
                // 0x00482ca8
                charge(ctx, 4);
                t6 = t4;
                t5 = t3;
                a2 = 0;
                for (;;) {
                    // 0x00482cb8
                    charge(ctx, 7);
                    di(ctx);
                    sync(ctx, 16);
                    mfc0(t1, 12);
                    t1 = t1 & t2;
                    if (t1 != 0) {
                        backedge(ctx);
                        continue;
                    }
                    // 0x00482cd4
                    charge(ctx, 22);
                    lqc2(vf1, t6, 0);
                    lqc2(vf2, t6, 16);
                    lqc2(vf3, t6, 32);
                    lqc2(vf4, t6, 48);
                    vmuli(0xF, vf6, vf1);  // vmuli.xyzw
                    vmuli(0xF, vf7, vf2);  // vmuli.xyzw
                    vadd(0xF, vf8, vf4, vf7);  // vadd.xyzw
                    vadd(0xF, vf10, vf8, vf6);  // vadd.xyzw
                    vsub(0xF, vf11, vf10, vf1);  // vsub.xyzw
                    vsub(0xF, vf12, vf10, vf2);  // vsub.xyzw
                    vsub(0xF, vf13, vf11, vf2);  // vsub.xyzw
                    sqc2(vf10, t5, 48);
                    sqc2(vf11, t5, 32);
                    sqc2(vf12, t5, 0);
                    sqc2(vf13, t5, 16);
                    t6 = addiu(t6, 64);
                    t5 = addiu(t5, 64);
                    ei(ctx);
                    a2 = addiu(a2, 1);
                    t1 = slti(a2, 127);
                    if (t1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00482d2c
                charge(ctx, 4);
                lw(a2, a3, -12288);
                a2 = a2 & 0x100;
                if (a2 != 0) {
                    // 0x00482d3c
                    charge(ctx, 3);
                    sw(a1, a3, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x00482d48
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00482d64
                    charge(ctx, 1);
                }
                // 0x00482d68
                charge(ctx, 4);
                lw(a2, a3, -11264);
                a2 = a2 & 0x100;
                if (a2 != 0) {
                    // 0x00482d78
                    charge(ctx, 4);
                    sw(a0, a3, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x00482d88
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00482da4
                    charge(ctx, 1);
                    for (;;) {
                        // 0x00482da8
                        charge(ctx, 7);
                        lw(a2, a3, -11264);
                        a2 = a2 & 0x100;
                        if (a2 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00482dc4
                    charge(ctx, 1);
                }
                // 0x00482dc8
                charge(ctx, 12);
                sw(a1, a3, -8176);
                sw(t0, a3, -12160);
                sw(s2, a3, -12272);
                sw(v1, a3, -12256);
                sw(a1, a3, -12288);
                sync(ctx, 0);
                sync(ctx, 16);
                s0 = addiu(s0, -127);
                s1 = addiu(s1, 8128);
                at = slti(s0, 127);
                s2 = addiu(s2, 8128);
                if (at != 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x00482df8
        charge(ctx, 2);
        if (s0 != 0) {
            // 0x00482e00
            charge(ctx, 5);
            v1 = 0x10010000;
            lw(a0, v1, -12288);  // 0x1000D000 D8 fromSPR CHCR
            a0 = a0 & 0x100;
            if (a0 != 0) {
                // 0x00482e14
                charge(ctx, 4);
                a0 = 256;
                sw(a0, v1, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x00482e24
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x00482e40
            charge(ctx, 5);
            v1 = 0x10010000;
            lw(a0, v1, -11264);  // 0x1000D400 D9 toSPR CHCR
            a0 = a0 & 0x100;
            if (a0 != 0) {
                // 0x00482e54
                charge(ctx, 4);
                a0 = 512;
                sw(a0, v1, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x00482e64
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00482e80
                charge(ctx, 1);
                v1 = 0x10010000;
                for (;;) {
                    // 0x00482e84
                    charge(ctx, 7);
                    lw(a0, v1, -11264);
                    a0 = a0 & 0x100;
                    if (a0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x00482ea0
            charge(ctx, 15);
            a2 = 512;
            v1 = 0x10010000;
            a1 = sll(s0, 2);
            sw(a2, v1, -8176);  // 0x1000E010 D_STAT
            a0 = 256;
            sw(zero, v1, -11136);  // 0x1000D480 D9 toSPR SADR
            sw(s1, v1, -11248);  // 0x1000D410 D9 toSPR MADR
            sw(a1, v1, -11232);  // 0x1000D420 D9 toSPR QWC
            sw(a0, v1, -11264);  // 0x1000D400 D9 toSPR CHCR
            sync(ctx, 0);
            sync(ctx, 16);
            lw(a0, v1, -11264);  // 0x1000D400 D9 toSPR CHCR
            a0 = a0 & 0x100;
            if (a0 != 0) {
                // 0x00482edc
                charge(ctx, 3);
                sw(a2, v1, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x00482ee8
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00482f04
                charge(ctx, 1);
                v1 = 0x10010000;
                for (;;) {
                    // 0x00482f08
                    charge(ctx, 7);
                    lw(a0, v1, -11264);
                    a0 = a0 & 0x100;
                    if (a0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00482f24
                charge(ctx, 1);
            }
            // 0x00482f28
            charge(ctx, 5);
            t6 = 0x70000000;
            at = slt(0, s0);
            t5 = t6 | 0x1FC0;
            a2 = 0;
            if (at != 0) {
                // 0x00482f3c
                charge(ctx, 1);
                a0 = 0x10000;
                for (;;) {
                    // 0x00482f40
                    charge(ctx, 7);
                    di(ctx);
                    sync(ctx, 16);
                    mfc0(v1, 12);
                    v1 = v1 & a0;
                    if (v1 != 0) {
                        backedge(ctx);
                        continue;
                    }
                    // 0x00482f5c
                    charge(ctx, 22);
                    lqc2(vf1, t6, 0);
                    lqc2(vf2, t6, 16);
                    lqc2(vf3, t6, 32);
                    lqc2(vf4, t6, 48);
                    vmuli(0xF, vf6, vf1);  // vmuli.xyzw
                    vmuli(0xF, vf7, vf2);  // vmuli.xyzw
                    vadd(0xF, vf8, vf4, vf7);  // vadd.xyzw
                    vadd(0xF, vf10, vf8, vf6);  // vadd.xyzw
                    vsub(0xF, vf11, vf10, vf1);  // vsub.xyzw
                    vsub(0xF, vf12, vf10, vf2);  // vsub.xyzw
                    vsub(0xF, vf13, vf11, vf2);  // vsub.xyzw
                    sqc2(vf10, t5, 48);
                    sqc2(vf11, t5, 32);
                    sqc2(vf12, t5, 0);
                    sqc2(vf13, t5, 16);
                    t6 = addiu(t6, 64);
                    t5 = addiu(t5, 64);
                    ei(ctx);
                    a2 = addiu(a2, 1);
                    v1 = slt(a2, s0);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00482fb4
                charge(ctx, 1);
            }
            // 0x00482fb8
            charge(ctx, 5);
            v1 = 0x10010000;
            lw(a0, v1, -12288);  // 0x1000D000 D8 fromSPR CHCR
            a0 = a0 & 0x100;
            if (a0 != 0) {
                // 0x00482fcc
                charge(ctx, 4);
                a0 = 256;
                sw(a0, v1, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x00482fdc
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x00482ff8
            charge(ctx, 5);
            v1 = 0x10010000;
            lw(a0, v1, -11264);  // 0x1000D400 D9 toSPR CHCR
            a0 = a0 & 0x100;
            if (a0 != 0) {
                // 0x0048300c
                charge(ctx, 4);
                a0 = 512;
                sw(a0, v1, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x0048301c
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00483038
                charge(ctx, 1);
                v1 = 0x10010000;
                for (;;) {
                    // 0x0048303c
                    charge(ctx, 7);
                    lw(a0, v1, -11264);
                    a0 = a0 & 0x100;
                    if (a0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x00483058
            charge(ctx, 13);
            a2 = 256;
            v1 = 0x10010000;
            a1 = 8128;
            sw(a2, v1, -8176);  // 0x1000E010 D_STAT
            a0 = sll(s0, 2);
            sw(a1, v1, -12160);  // 0x1000D080 D8 fromSPR SADR
            sw(s2, v1, -12272);  // 0x1000D010 D8 fromSPR MADR
            sw(a0, v1, -12256);  // 0x1000D020 D8 fromSPR QWC
            sw(a2, v1, -12288);  // 0x1000D000 D8 fromSPR CHCR
            sync(ctx, 0);
            sync(ctx, 16);
        }
    }
    // 0x00483158 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00483170 sub_483170 -- 1892 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Scratchpad DMA kernel using the SPR words 0x3FB0 / 0x3FB4.
void sub_483170(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    Vf vf1{ctx, 1}, vf2{ctx, 2}, vf3{ctx, 3}, vf4{ctx, 4}, vf5{ctx, 5}, vf6{ctx, 6}, vf7{ctx, 7}, vf8{ctx, 8}, vf10{ctx, 10}, vf11{ctx, 11}, vf12{ctx, 12}, vf13{ctx, 13};
    // 0x00483170
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a3;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a1, a0, 4);
    lw(a2, t0, 16);
    lw(s1, a0, 0);
    lw(s0, t0, 12);
    v1 = sll(a1, 2);
    s2 = t0;
    if (a2 != v1) {
        // 0x004837d4
        charge(ctx, 5);
        lwc1(f1, s2, 104);
        v1 = 0x10000;
        lwc1(f0, s2, 108);
        swc1(f1, sp, 0x50);
        swc1(f0, sp, 0x54);
        for (;;) {
            // 0x004837e8
            charge(ctx, 7);
            di(ctx);
            sync(ctx, 16);
            mfc0(a0, 12);
            a0 = a0 & v1;
            if (a0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00483804
        charge(ctx, 13);
        v1 = 0x3F000000;
        a0 = addiu(sp, 0x50);
        mtc1(v1, f0);
        mfc1(v1, f0);
        ctc2(v1, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        lqc2(vf1, a0, 0);
        vaddi(0xF, vf5, vf1);  // vaddi.xyzw
        ei(ctx);
        at = slt(0, s3);
        a3 = 0;
        if (at != 0) {
            // 0x00483838
            charge(ctx, 2);
            a0 = sll(a1, 2);
            a1 = 0x10000;
            for (;;) {
                // 0x00483840
                charge(ctx, 7);
                di(ctx);
                sync(ctx, 16);
                mfc0(v1, 12);
                v1 = v1 & a1;
                if (v1 != 0) {
                    backedge(ctx);
                    continue;
                }
                // 0x0048385c
                charge(ctx, 22);
                lqc2(vf1, s0, 0);
                lqc2(vf2, s0, 16);
                lqc2(vf3, s0, 32);
                lqc2(vf4, s0, 48);
                vmul_bc(0xF, vf6, vf1, vf5, 0);  // vmulx.xyzw
                vmul_bc(0xF, vf7, vf2, vf5, 1);  // vmuly.xyzw
                vadd(0xF, vf8, vf4, vf7);  // vadd.xyzw
                vadd(0xF, vf10, vf8, vf6);  // vadd.xyzw
                vsub(0xF, vf11, vf10, vf1);  // vsub.xyzw
                vsub(0xF, vf12, vf10, vf2);  // vsub.xyzw
                vsub(0xF, vf13, vf11, vf2);  // vsub.xyzw
                sqc2(vf10, s1, 48);
                sqc2(vf11, s1, 32);
                sqc2(vf12, s1, 0);
                sqc2(vf13, s1, 16);
                s0 = addu(s0, a2);
                s1 = addu(s1, a0);
                ei(ctx);
                a3 = addiu(a3, 1);
                v1 = slt(a3, s3);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004838b4
            charge(ctx, 1);
        }
    } else {
        // 0x004831a8
        charge(ctx, 7);
        a0 = 0;
        jal(ctx, 0x4831A8u, gen::fn__sceFlushCache_005033e0);
        v1 = 0x10010000;
        lw(a0, v1, -12288);  // 0x1000D000 D8 fromSPR CHCR
        a0 = a0 & 0x100;
        if (a0 != 0) {
            // 0x004831c4
            charge(ctx, 4);
            a0 = 256;
            sw(a0, v1, -8160);
            sync(ctx, 0);
            sync(ctx, 16);
            for (;;) {
                // 0x004831d4
                charge(ctx, 7);
                if (cop0_cond(ctx)) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x004831f0
        charge(ctx, 5);
        v1 = 0x10010000;
        lw(a0, v1, -11264);  // 0x1000D400 D9 toSPR CHCR
        a0 = a0 & 0x100;
        if (a0 != 0) {
            // 0x00483204
            charge(ctx, 4);
            a0 = 512;
            sw(a0, v1, -8160);
            sync(ctx, 0);
            sync(ctx, 16);
            for (;;) {
                // 0x00483214
                charge(ctx, 7);
                if (cop0_cond(ctx)) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00483230
            charge(ctx, 1);
            v1 = 0x10010000;
            for (;;) {
                // 0x00483234
                charge(ctx, 7);
                lw(a0, v1, -11264);
                a0 = a0 & 0x100;
                if (a0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x00483250
        charge(ctx, 7);
        a1 = 0x70000000;
        lwc1(f0, s2, 104);
        a0 = a1 | 0x3FB0;
        v1 = 0x10000;
        swc1(f0, a1, 16304);  // 0x70003FB0 SPR+0x3FB0
        lwc1(f0, s2, 108);
        swc1(f0, a1, 16308);  // 0x70003FB4 SPR+0x3FB4
        for (;;) {
            // 0x0048326c
            charge(ctx, 7);
            di(ctx);
            sync(ctx, 16);
            mfc0(a1, 12);
            a1 = a1 & v1;
            if (a1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00483288
        charge(ctx, 12);
        v1 = 0x3F000000;
        mtc1(v1, f0);
        mfc1(v1, f0);
        ctc2(v1, 21, false);  // ctc2
        vnop(ctx);
        vnop(ctx);
        lqc2(vf1, a0, 0);
        vaddi(0xF, vf5, vf1);  // vaddi.xyzw
        ei(ctx);
        v1 = slti(s3, 127);
        if (v1 == 0) {
            // 0x004832b8
            charge(ctx, 8);
            t2 = 0x70000000;
            a1 = 0x10010000;
            t0 = 0x10000;
            a0 = 256;
            v1 = 512;
            t3 = 508;
            t1 = t2 | 0x1FC0;
            a2 = 8128;
            for (;;) {
                // 0x004832d8
                charge(ctx, 4);
                lw(a3, a1, -12288);
                a3 = a3 & 0x100;
                if (a3 != 0) {
                    // 0x004832e8
                    charge(ctx, 4);
                    sw(a0, a1, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x004832f8
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00483314
                    charge(ctx, 1);
                }
                // 0x00483318
                charge(ctx, 4);
                lw(a3, a1, -11264);
                a3 = a3 & 0x100;
                if (a3 != 0) {
                    // 0x00483328
                    charge(ctx, 4);
                    sw(v1, a1, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x00483338
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00483354
                    charge(ctx, 1);
                    for (;;) {
                        // 0x00483358
                        charge(ctx, 7);
                        lw(a3, a1, -11264);
                        a3 = a3 & 0x100;
                        if (a3 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00483374
                    charge(ctx, 1);
                }
                // 0x00483378
                charge(ctx, 11);
                sw(v1, a1, -8176);
                sw(zero, a1, -11136);
                sw(s0, a1, -11248);
                sw(t3, a1, -11232);
                sw(a0, a1, -11264);
                sync(ctx, 0);
                sync(ctx, 16);
                lw(a3, a1, -11264);
                a3 = a3 & 0x100;
                if (a3 != 0) {
                    // 0x004833a4
                    charge(ctx, 3);
                    sw(v1, a1, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x004833b0
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004833cc
                    charge(ctx, 1);
                    for (;;) {
                        // 0x004833d0
                        charge(ctx, 7);
                        lw(a3, a1, -11264);
                        a3 = a3 & 0x100;
                        if (a3 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004833ec
                    charge(ctx, 1);
                }
                // 0x004833f0
                charge(ctx, 4);
                t5 = t2;
                t4 = t1;
                t6 = 0;
                for (;;) {
                    // 0x00483400
                    charge(ctx, 7);
                    di(ctx);
                    sync(ctx, 16);
                    mfc0(a3, 12);
                    a3 = a3 & t0;
                    if (a3 != 0) {
                        backedge(ctx);
                        continue;
                    }
                    // 0x0048341c
                    charge(ctx, 22);
                    lqc2(vf1, t5, 0);
                    lqc2(vf2, t5, 16);
                    lqc2(vf3, t5, 32);
                    lqc2(vf4, t5, 48);
                    vmul_bc(0xF, vf6, vf1, vf5, 0);  // vmulx.xyzw
                    vmul_bc(0xF, vf7, vf2, vf5, 1);  // vmuly.xyzw
                    vadd(0xF, vf8, vf4, vf7);  // vadd.xyzw
                    vadd(0xF, vf10, vf8, vf6);  // vadd.xyzw
                    vsub(0xF, vf11, vf10, vf1);  // vsub.xyzw
                    vsub(0xF, vf12, vf10, vf2);  // vsub.xyzw
                    vsub(0xF, vf13, vf11, vf2);  // vsub.xyzw
                    sqc2(vf10, t4, 48);
                    sqc2(vf11, t4, 32);
                    sqc2(vf12, t4, 0);
                    sqc2(vf13, t4, 16);
                    t5 = addiu(t5, 64);
                    t4 = addiu(t4, 64);
                    ei(ctx);
                    t6 = addiu(t6, 1);
                    a3 = slti(t6, 127);
                    if (a3 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00483474
                charge(ctx, 4);
                lw(a3, a1, -12288);
                a3 = a3 & 0x100;
                if (a3 != 0) {
                    // 0x00483484
                    charge(ctx, 3);
                    sw(a0, a1, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x00483490
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004834ac
                    charge(ctx, 1);
                }
                // 0x004834b0
                charge(ctx, 4);
                lw(a3, a1, -11264);
                a3 = a3 & 0x100;
                if (a3 != 0) {
                    // 0x004834c0
                    charge(ctx, 4);
                    sw(v1, a1, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x004834d0
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004834ec
                    charge(ctx, 1);
                    for (;;) {
                        // 0x004834f0
                        charge(ctx, 7);
                        lw(a3, a1, -11264);
                        a3 = a3 & 0x100;
                        if (a3 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0048350c
                    charge(ctx, 1);
                }
                // 0x00483510
                charge(ctx, 12);
                sw(a0, a1, -8176);
                sw(a2, a1, -12160);
                sw(s1, a1, -12272);
                sw(t3, a1, -12256);
                sw(a0, a1, -12288);
                sync(ctx, 0);
                sync(ctx, 16);
                s3 = addiu(s3, -127);
                s0 = addiu(s0, 8128);
                at = slti(s3, 127);
                s1 = addiu(s1, 8128);
                if (at != 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x00483540
        charge(ctx, 2);
        if (s3 != 0) {
            // 0x00483548
            charge(ctx, 5);
            v1 = 0x10010000;
            lw(a0, v1, -12288);  // 0x1000D000 D8 fromSPR CHCR
            a0 = a0 & 0x100;
            if (a0 != 0) {
                // 0x0048355c
                charge(ctx, 4);
                a0 = 256;
                sw(a0, v1, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x0048356c
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x00483588
            charge(ctx, 5);
            v1 = 0x10010000;
            lw(a0, v1, -11264);  // 0x1000D400 D9 toSPR CHCR
            a0 = a0 & 0x100;
            if (a0 != 0) {
                // 0x0048359c
                charge(ctx, 4);
                a0 = 512;
                sw(a0, v1, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x004835ac
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004835c8
                charge(ctx, 1);
                v1 = 0x10010000;
                for (;;) {
                    // 0x004835cc
                    charge(ctx, 7);
                    lw(a0, v1, -11264);
                    a0 = a0 & 0x100;
                    if (a0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x004835e8
            charge(ctx, 15);
            a2 = 512;
            v1 = 0x10010000;
            a1 = sll(s3, 2);
            sw(a2, v1, -8176);  // 0x1000E010 D_STAT
            a0 = 256;
            sw(zero, v1, -11136);  // 0x1000D480 D9 toSPR SADR
            sw(s0, v1, -11248);  // 0x1000D410 D9 toSPR MADR
            sw(a1, v1, -11232);  // 0x1000D420 D9 toSPR QWC
            sw(a0, v1, -11264);  // 0x1000D400 D9 toSPR CHCR
            sync(ctx, 0);
            sync(ctx, 16);
            lw(a0, v1, -11264);  // 0x1000D400 D9 toSPR CHCR
            a0 = a0 & 0x100;
            if (a0 != 0) {
                // 0x00483624
                charge(ctx, 3);
                sw(a2, v1, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x00483630
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0048364c
                charge(ctx, 1);
                v1 = 0x10010000;
                for (;;) {
                    // 0x00483650
                    charge(ctx, 7);
                    lw(a0, v1, -11264);
                    a0 = a0 & 0x100;
                    if (a0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0048366c
                charge(ctx, 1);
            }
            // 0x00483670
            charge(ctx, 5);
            t5 = 0x70000000;
            at = slt(0, s3);
            t4 = t5 | 0x1FC0;
            a1 = 0;
            if (at != 0) {
                // 0x00483684
                charge(ctx, 1);
                a0 = 0x10000;
                for (;;) {
                    // 0x00483688
                    charge(ctx, 7);
                    di(ctx);
                    sync(ctx, 16);
                    mfc0(v1, 12);
                    v1 = v1 & a0;
                    if (v1 != 0) {
                        backedge(ctx);
                        continue;
                    }
                    // 0x004836a4
                    charge(ctx, 22);
                    lqc2(vf1, t5, 0);
                    lqc2(vf2, t5, 16);
                    lqc2(vf3, t5, 32);
                    lqc2(vf4, t5, 48);
                    vmul_bc(0xF, vf6, vf1, vf5, 0);  // vmulx.xyzw
                    vmul_bc(0xF, vf7, vf2, vf5, 1);  // vmuly.xyzw
                    vadd(0xF, vf8, vf4, vf7);  // vadd.xyzw
                    vadd(0xF, vf10, vf8, vf6);  // vadd.xyzw
                    vsub(0xF, vf11, vf10, vf1);  // vsub.xyzw
                    vsub(0xF, vf12, vf10, vf2);  // vsub.xyzw
                    vsub(0xF, vf13, vf11, vf2);  // vsub.xyzw
                    sqc2(vf10, t4, 48);
                    sqc2(vf11, t4, 32);
                    sqc2(vf12, t4, 0);
                    sqc2(vf13, t4, 16);
                    t5 = addiu(t5, 64);
                    t4 = addiu(t4, 64);
                    ei(ctx);
                    a1 = addiu(a1, 1);
                    v1 = slt(a1, s3);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004836fc
                charge(ctx, 1);
            }
            // 0x00483700
            charge(ctx, 5);
            v1 = 0x10010000;
            lw(a0, v1, -12288);  // 0x1000D000 D8 fromSPR CHCR
            a0 = a0 & 0x100;
            if (a0 != 0) {
                // 0x00483714
                charge(ctx, 4);
                a0 = 256;
                sw(a0, v1, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x00483724
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x00483740
            charge(ctx, 5);
            v1 = 0x10010000;
            lw(a0, v1, -11264);  // 0x1000D400 D9 toSPR CHCR
            a0 = a0 & 0x100;
            if (a0 != 0) {
                // 0x00483754
                charge(ctx, 4);
                a0 = 512;
                sw(a0, v1, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x00483764
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00483780
                charge(ctx, 1);
                v1 = 0x10010000;
                for (;;) {
                    // 0x00483784
                    charge(ctx, 7);
                    lw(a0, v1, -11264);
                    a0 = a0 & 0x100;
                    if (a0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x004837a0
            charge(ctx, 13);
            a2 = 256;
            v1 = 0x10010000;
            a1 = 8128;
            sw(a2, v1, -8176);  // 0x1000E010 D_STAT
            a0 = sll(s3, 2);
            sw(a1, v1, -12160);  // 0x1000D080 D8 fromSPR SADR
            sw(s1, v1, -12272);  // 0x1000D010 D8 fromSPR MADR
            sw(a0, v1, -12256);  // 0x1000D020 D8 fromSPR QWC
            sw(a2, v1, -12288);  // 0x1000D000 D8 fromSPR CHCR
            sync(ctx, 0);
            sync(ctx, 16);
        }
    }
    // 0x004838b8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x004838E0 sub_4838E0 -- 6032 bytes; frame 0x1F0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Scratchpad DMA kernel, the largest variant (unrolled per-format paths).
void sub_4838E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x004838e0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1F0);
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
    lw(v1, a0, 4);
    lw(s6, a2, 40);
    lw(s0, a0, 0);
    lw(s1, a2, 36);
    s2 = a1;
    if (s6 == v1) {
        // 0x00483c28
        charge(ctx, 7);
        a0 = 0;
        jal(ctx, 0x483C28u, gen::fn__sceFlushCache_005033e0);
        v1 = 0x10010000;
        lw(a0, v1, -12288);  // 0x1000D000 D8 fromSPR CHCR
        a0 = a0 & 0x100;
        if (a0 != 0) {
            // 0x00484ce0
            charge(ctx, 4);
            a0 = 256;
            sw(a0, v1, -8160);
            sync(ctx, 0);
            sync(ctx, 16);
            for (;;) {
                // 0x00484cf0
                charge(ctx, 7);
                if (cop0_cond(ctx)) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00484d0c
            charge(ctx, 2);
            v1 = 0x10010000;
            backedge(ctx);
        } else {
            // 0x00483c44
            charge(ctx, 1);
            v1 = 0x10010000;
        }
        // 0x00483c48
        charge(ctx, 4);
        lw(a0, v1, -11264);
        a0 = a0 & 0x100;
        if (a0 != 0) {
            // 0x00484d14
            charge(ctx, 4);
            a0 = 512;
            sw(a0, v1, -8160);
            sync(ctx, 0);
            sync(ctx, 16);
            for (;;) {
                // 0x00484d24
                charge(ctx, 7);
                if (cop0_cond(ctx)) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00484d40
            charge(ctx, 1);
            v1 = 0x10010000;
            for (;;) {
                // 0x00484d44
                charge(ctx, 7);
                lw(a0, v1, -11264);
                a0 = a0 & 0x100;
                if (a0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00484d60
            charge(ctx, 2);
            at = slti(s2, 817);
            backedge(ctx);
        } else {
            // 0x00483c58
            charge(ctx, 1);
            at = slti(s2, 817);
        }
        // 0x00483c5c
        charge(ctx, 2);
        if (at == 0) {
            // 0x00483c64
            charge(ctx, 8);
            a0 = 0x70000000;
            t3 = 0x10010000;
            a3 = 512;
            a1 = 256;
            a2 = 204;
            t5 = 3264;
            v1 = a0 | 0xCC0;
            t4 = 816;
            for (;;) {
                // 0x00483c84
                charge(ctx, 4);
                lw(t0, t3, -12288);
                t0 = t0 & 0x100;
                if (t0 != 0) {
                    // 0x00484d68
                    charge(ctx, 4);
                    sw(a1, t3, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x00484d78
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00484d94
                    charge(ctx, 2);
                    backedge(ctx);
                } else {
                    // 0x00483c94
                    charge(ctx, 1);
                }
                // 0x00483c98
                charge(ctx, 4);
                lw(t0, t3, -11264);
                t0 = t0 & 0x100;
                if (t0 != 0) {
                    // 0x00484da0
                    charge(ctx, 4);
                    sw(a3, t3, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x00484db0
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00484dcc
                    charge(ctx, 1);
                    for (;;) {
                        // 0x00484dd0
                        charge(ctx, 7);
                        lw(t0, t3, -11264);
                        t0 = t0 & 0x100;
                        if (t0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00484dec
                    charge(ctx, 2);
                    backedge(ctx);
                }
                // 0x00483ca8
                charge(ctx, 11);
                sw(a3, t3, -8176);
                sw(zero, t3, -11136);
                sw(s1, t3, -11248);
                sw(a2, t3, -11232);
                sw(a1, t3, -11264);
                sync(ctx, 0);
                sync(ctx, 16);
                lw(t0, t3, -11264);
                t0 = t0 & 0x100;
                if (t0 != 0) {
                    // 0x00484df8
                    charge(ctx, 4);
                    sw(a3, t3, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x00484e08
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00484e24
                    charge(ctx, 1);
                    for (;;) {
                        // 0x00484e28
                        charge(ctx, 7);
                        lw(t0, t3, -11264);
                        t0 = t0 & 0x100;
                        if (t0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00484e44
                    charge(ctx, 2);
                    backedge(ctx);
                } else {
                    // 0x00483cd4
                    charge(ctx, 1);
                }
                // 0x00483cd8
                charge(ctx, 4);
                t1 = a0;
                t0 = v1;
                t2 = 0;
                for (;;) {
                    // 0x00483ce8
                    charge(ctx, 261);
                    lbu(s5, t1, 0);
                    lbu(s4, t1, 1);
                    t2 = addiu(t2, 8);
                    lbu(s3, t1, 2);
                    t6 = slti(t2, 816);
                    lbu(t7, t1, 3);
                    sb(s5, t0, 0);
                    sb(s4, t0, 1);
                    sb(s3, t0, 2);
                    sb(t7, t0, 3);
                    lbu(s5, t1, 0);
                    lbu(s4, t1, 1);
                    lbu(s3, t1, 2);
                    lbu(t7, t1, 3);
                    sb(s5, t0, 4);
                    sb(s4, t0, 5);
                    sb(s3, t0, 6);
                    sb(t7, t0, 7);
                    lbu(s5, t1, 0);
                    lbu(s4, t1, 1);
                    lbu(s3, t1, 2);
                    lbu(t7, t1, 3);
                    sb(s5, t0, 8);
                    sb(s4, t0, 9);
                    sb(s3, t0, 10);
                    sb(t7, t0, 11);
                    lbu(s5, t1, 0);
                    lbu(s4, t1, 1);
                    lbu(s3, t1, 2);
                    lbu(t7, t1, 3);
                    sb(s5, t0, 12);
                    sb(s4, t0, 13);
                    sb(s3, t0, 14);
                    sb(t7, t0, 15);
                    lbu(s5, t1, 4);
                    lbu(s4, t1, 5);
                    lbu(s3, t1, 6);
                    lbu(t7, t1, 7);
                    sb(s5, t0, 16);
                    sb(s4, t0, 17);
                    sb(s3, t0, 18);
                    sb(t7, t0, 19);
                    lbu(s5, t1, 4);
                    lbu(s4, t1, 5);
                    lbu(s3, t1, 6);
                    lbu(t7, t1, 7);
                    sb(s5, t0, 20);
                    sb(s4, t0, 21);
                    sb(s3, t0, 22);
                    sb(t7, t0, 23);
                    lbu(s5, t1, 4);
                    lbu(s4, t1, 5);
                    lbu(s3, t1, 6);
                    lbu(t7, t1, 7);
                    sb(s5, t0, 24);
                    sb(s4, t0, 25);
                    sb(s3, t0, 26);
                    sb(t7, t0, 27);
                    lbu(s5, t1, 4);
                    lbu(s4, t1, 5);
                    lbu(s3, t1, 6);
                    lbu(t7, t1, 7);
                    sb(s5, t0, 28);
                    sb(s4, t0, 29);
                    sb(s3, t0, 30);
                    sb(t7, t0, 31);
                    lbu(s5, t1, 8);
                    lbu(s4, t1, 9);
                    lbu(s3, t1, 10);
                    lbu(t7, t1, 11);
                    sb(s5, t0, 32);
                    sb(s4, t0, 33);
                    sb(s3, t0, 34);
                    sb(t7, t0, 35);
                    lbu(s5, t1, 8);
                    lbu(s4, t1, 9);
                    lbu(s3, t1, 10);
                    lbu(t7, t1, 11);
                    sb(s5, t0, 36);
                    sb(s4, t0, 37);
                    sb(s3, t0, 38);
                    sb(t7, t0, 39);
                    lbu(s5, t1, 8);
                    lbu(s4, t1, 9);
                    lbu(s3, t1, 10);
                    lbu(t7, t1, 11);
                    sb(s5, t0, 40);
                    sb(s4, t0, 41);
                    sb(s3, t0, 42);
                    sb(t7, t0, 43);
                    lbu(s5, t1, 8);
                    lbu(s4, t1, 9);
                    lbu(s3, t1, 10);
                    lbu(t7, t1, 11);
                    sb(s5, t0, 44);
                    sb(s4, t0, 45);
                    sb(s3, t0, 46);
                    sb(t7, t0, 47);
                    lbu(s5, t1, 12);
                    lbu(s4, t1, 13);
                    lbu(s3, t1, 14);
                    lbu(t7, t1, 15);
                    sb(s5, t0, 48);
                    sb(s4, t0, 49);
                    sb(s3, t0, 50);
                    sb(t7, t0, 51);
                    lbu(s5, t1, 12);
                    lbu(s4, t1, 13);
                    lbu(s3, t1, 14);
                    lbu(t7, t1, 15);
                    sb(s5, t0, 52);
                    sb(s4, t0, 53);
                    sb(s3, t0, 54);
                    sb(t7, t0, 55);
                    lbu(s5, t1, 12);
                    lbu(s4, t1, 13);
                    lbu(s3, t1, 14);
                    lbu(t7, t1, 15);
                    sb(s5, t0, 56);
                    sb(s4, t0, 57);
                    sb(s3, t0, 58);
                    sb(t7, t0, 59);
                    lbu(s5, t1, 12);
                    lbu(s4, t1, 13);
                    lbu(s3, t1, 14);
                    lbu(t7, t1, 15);
                    sb(s5, t0, 60);
                    sb(s4, t0, 61);
                    sb(s3, t0, 62);
                    sb(t7, t0, 63);
                    lbu(s5, t1, 16);
                    lbu(s4, t1, 17);
                    lbu(s3, t1, 18);
                    lbu(t7, t1, 19);
                    sb(s5, t0, 64);
                    sb(s4, t0, 65);
                    sb(s3, t0, 66);
                    sb(t7, t0, 67);
                    lbu(s5, t1, 16);
                    lbu(s4, t1, 17);
                    lbu(s3, t1, 18);
                    lbu(t7, t1, 19);
                    sb(s5, t0, 68);
                    sb(s4, t0, 69);
                    sb(s3, t0, 70);
                    sb(t7, t0, 71);
                    lbu(s5, t1, 16);
                    lbu(s4, t1, 17);
                    lbu(s3, t1, 18);
                    lbu(t7, t1, 19);
                    sb(s5, t0, 72);
                    sb(s4, t0, 73);
                    sb(s3, t0, 74);
                    sb(t7, t0, 75);
                    lbu(s5, t1, 16);
                    lbu(s4, t1, 17);
                    lbu(s3, t1, 18);
                    lbu(t7, t1, 19);
                    sb(s5, t0, 76);
                    sb(s4, t0, 77);
                    sb(s3, t0, 78);
                    sb(t7, t0, 79);
                    lbu(s5, t1, 20);
                    lbu(s4, t1, 21);
                    lbu(s3, t1, 22);
                    lbu(t7, t1, 23);
                    sb(s5, t0, 80);
                    sb(s4, t0, 81);
                    sb(s3, t0, 82);
                    sb(t7, t0, 83);
                    lbu(s5, t1, 20);
                    lbu(s4, t1, 21);
                    lbu(s3, t1, 22);
                    lbu(t7, t1, 23);
                    sb(s5, t0, 84);
                    sb(s4, t0, 85);
                    sb(s3, t0, 86);
                    sb(t7, t0, 87);
                    lbu(s5, t1, 20);
                    lbu(s4, t1, 21);
                    lbu(s3, t1, 22);
                    lbu(t7, t1, 23);
                    sb(s5, t0, 88);
                    sb(s4, t0, 89);
                    sb(s3, t0, 90);
                    sb(t7, t0, 91);
                    lbu(s5, t1, 20);
                    lbu(s4, t1, 21);
                    lbu(s3, t1, 22);
                    lbu(t7, t1, 23);
                    sb(s5, t0, 92);
                    sb(s4, t0, 93);
                    sb(s3, t0, 94);
                    sb(t7, t0, 95);
                    lbu(s5, t1, 24);
                    lbu(s4, t1, 25);
                    lbu(s3, t1, 26);
                    lbu(t7, t1, 27);
                    sb(s5, t0, 96);
                    sb(s4, t0, 97);
                    sb(s3, t0, 98);
                    sb(t7, t0, 99);
                    lbu(s5, t1, 24);
                    lbu(s4, t1, 25);
                    lbu(s3, t1, 26);
                    lbu(t7, t1, 27);
                    sb(s5, t0, 100);
                    sb(s4, t0, 101);
                    sb(s3, t0, 102);
                    sb(t7, t0, 103);
                    lbu(s5, t1, 24);
                    lbu(s4, t1, 25);
                    lbu(s3, t1, 26);
                    lbu(t7, t1, 27);
                    sb(s5, t0, 104);
                    sb(s4, t0, 105);
                    sb(s3, t0, 106);
                    sb(t7, t0, 107);
                    lbu(s5, t1, 24);
                    lbu(s4, t1, 25);
                    lbu(s3, t1, 26);
                    lbu(t7, t1, 27);
                    sb(s5, t0, 108);
                    sb(s4, t0, 109);
                    sb(s3, t0, 110);
                    sb(t7, t0, 111);
                    lbu(s5, t1, 28);
                    lbu(s4, t1, 29);
                    lbu(s3, t1, 30);
                    lbu(t7, t1, 31);
                    sb(s5, t0, 112);
                    sb(s4, t0, 113);
                    sb(s3, t0, 114);
                    sb(t7, t0, 115);
                    lbu(s5, t1, 28);
                    lbu(s4, t1, 29);
                    lbu(s3, t1, 30);
                    lbu(t7, t1, 31);
                    sb(s5, t0, 116);
                    sb(s4, t0, 117);
                    sb(s3, t0, 118);
                    sb(t7, t0, 119);
                    lbu(s5, t1, 28);
                    lbu(s4, t1, 29);
                    lbu(s3, t1, 30);
                    lbu(t7, t1, 31);
                    sb(s5, t0, 120);
                    sb(s4, t0, 121);
                    sb(s3, t0, 122);
                    sb(t7, t0, 123);
                    lbu(s5, t1, 28);
                    lbu(s4, t1, 29);
                    lbu(s3, t1, 30);
                    lbu(t7, t1, 31);
                    sb(s5, t0, 124);
                    t1 = addiu(t1, 32);
                    sb(s4, t0, 125);
                    sb(s3, t0, 126);
                    sb(t7, t0, 127);
                    t0 = addiu(t0, 128);
                    if (t6 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004840fc
                charge(ctx, 4);
                lw(t0, t3, -12288);
                t0 = t0 & 0x100;
                if (t0 != 0) {
                    // 0x00484e50
                    charge(ctx, 4);
                    sw(a1, t3, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x00484e60
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00484e7c
                    charge(ctx, 2);
                    backedge(ctx);
                } else {
                    // 0x0048410c
                    charge(ctx, 1);
                }
                // 0x00484110
                charge(ctx, 4);
                lw(t0, t3, -11264);
                t0 = t0 & 0x100;
                if (t0 != 0) {
                    // 0x00484e88
                    charge(ctx, 4);
                    sw(a3, t3, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x00484e98
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00484eb4
                    charge(ctx, 1);
                    for (;;) {
                        // 0x00484eb8
                        charge(ctx, 7);
                        lw(t0, t3, -11264);
                        t0 = t0 & 0x100;
                        if (t0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00484ed4
                    charge(ctx, 2);
                    backedge(ctx);
                }
                // 0x00484120
                charge(ctx, 12);
                sw(a1, t3, -8176);
                sw(t5, t3, -12160);
                sw(s0, t3, -12272);
                sw(t4, t3, -12256);
                sw(a1, t3, -12288);
                sync(ctx, 0);
                sync(ctx, 16);
                s2 = addiu(s2, -816);
                s1 = addiu(s1, 3264);
                at = slti(s2, 817);
                s0 = addiu(s0, 13056);
                if (at != 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x00484150
        charge(ctx, 3);
        at = slti(s2, 4);
        if (at == 0) {
            // 0x0048415c
            charge(ctx, 2);
            v1 = sra(s2, 2);
            if (i64(s2) < 0) {
                // 0x00484164
                charge(ctx, 2);
                v1 = addiu(s2, 3);
                v1 = sra(v1, 2);
            }
            // 0x0048416c
            charge(ctx, 6);
            a0 = sll(v1, 2);
            v1 = 0x10010000;
            lw(a1, v1, -12288);  // 0x1000D000 D8 fromSPR CHCR
            a1 = a1 & 0x100;
            if (a1 != 0) {
                // 0x00484ee0
                charge(ctx, 4);
                a1 = 256;
                sw(a1, v1, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x00484ef0
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00484f0c
                charge(ctx, 2);
                v1 = 0x10010000;
                backedge(ctx);
            } else {
                // 0x00484184
                charge(ctx, 1);
                v1 = 0x10010000;
            }
            // 0x00484188
            charge(ctx, 4);
            lw(a1, v1, -11264);
            a1 = a1 & 0x100;
            if (a1 != 0) {
                // 0x00484f14
                charge(ctx, 4);
                a1 = 512;
                sw(a1, v1, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x00484f24
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00484f40
                charge(ctx, 1);
                v1 = 0x10010000;
                for (;;) {
                    // 0x00484f44
                    charge(ctx, 7);
                    lw(a1, v1, -11264);
                    a1 = a1 & 0x100;
                    if (a1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00484f60
                charge(ctx, 2);
                backedge(ctx);
            }
            // 0x00484198
            charge(ctx, 17);
            mtc1(a0, f0);
            a1 = 512;
            v1 = 0x10010000;
            cvt_s_w(f0, f0);
            sw(a1, v1, -8176);  // 0x1000E010 D_STAT
            a1 = 0x3E800000;
            sw(zero, v1, -11136);  // 0x1000D480 D9 toSPR SADR
            sw(s1, v1, -11248);  // 0x1000D410 D9 toSPR MADR
            v1 = 0x4F000000;
            mtc1(a1, f1);
            mul_s(f1, f1, f0);
            mtc1(v1, f0);
            c_le_s(f0, f1);
            if (cond(ctx)) {
                // 0x004841ec
                charge(ctx, 7);
                sub_s(f0, f1, f0);
                v1 = lui(0x8000);
                cvt_w_s(f0, f0);
                mfc1(a2, f0);
                a2 = a2 | v1;
                v1 = 0x10010000;
            } else {
                // 0x004841dc
                charge(ctx, 4);
                cvt_w_s(f0, f1);
                mfc1(a2, f0);
                v1 = 0x10010000;
            }
            // 0x00484208
            charge(ctx, 9);
            a1 = 256;
            sw(a2, v1, -11232);
            sw(a1, v1, -11264);
            sync(ctx, 0);
            sync(ctx, 16);
            lw(a1, v1, -11264);
            a1 = a1 & 0x100;
            if (a1 != 0) {
                // 0x00484f68
                charge(ctx, 4);
                a1 = 512;
                sw(a1, v1, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x00484f78
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00484f94
                charge(ctx, 1);
                v1 = 0x10010000;
                for (;;) {
                    // 0x00484f98
                    charge(ctx, 7);
                    lw(a1, v1, -11264);
                    a1 = a1 & 0x100;
                    if (a1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00484fb4
                charge(ctx, 2);
                a3 = 0x70000000;
                backedge(ctx);
            } else {
                // 0x0048422c
                charge(ctx, 1);
                a3 = 0x70000000;
            }
            // 0x00484230
            charge(ctx, 4);
            at = slt(0, a0);
            a1 = 0;
            a2 = a3 | 0xCC0;
            if (at != 0) {
                // 0x00484240
                charge(ctx, 3);
                at = slti(a0, 9);
                v1 = addiu(a0, -8);
                if (at == 0) {
                    // 0x0048424c
                    charge(ctx, 3);
                    at = slt(a0, 0);
                    t0 = 0;
                    if (at == 0) {
                        // 0x00484258
                        charge(ctx, 5);
                        at = 0x7FFF0000;
                        at = at | 0xFFFF;
                        at = slt(a0, at);
                        if (at != 0) {
                            // 0x0048426c
                            charge(ctx, 1);
                            t0 = 1;
                        }
                    }
                    // 0x00484270
                    charge(ctx, 2);
                    if (t0 != 0) {
                        for (;;) {
                            // 0x00484278
                            charge(ctx, 261);
                            lbu(t4, a3, 0);
                            a1 = addiu(a1, 8);
                            lbu(t3, a3, 1);
                            t0 = slt(a1, v1);
                            lbu(t2, a3, 2);
                            lbu(t1, a3, 3);
                            sb(t4, a2, 0);
                            sb(t3, a2, 1);
                            sb(t2, a2, 2);
                            sb(t1, a2, 3);
                            lbu(t4, a3, 0);
                            lbu(t3, a3, 1);
                            lbu(t2, a3, 2);
                            lbu(t1, a3, 3);
                            sb(t4, a2, 4);
                            sb(t3, a2, 5);
                            sb(t2, a2, 6);
                            sb(t1, a2, 7);
                            lbu(t4, a3, 0);
                            lbu(t3, a3, 1);
                            lbu(t2, a3, 2);
                            lbu(t1, a3, 3);
                            sb(t4, a2, 8);
                            sb(t3, a2, 9);
                            sb(t2, a2, 10);
                            sb(t1, a2, 11);
                            lbu(t4, a3, 0);
                            lbu(t3, a3, 1);
                            lbu(t2, a3, 2);
                            lbu(t1, a3, 3);
                            sb(t4, a2, 12);
                            sb(t3, a2, 13);
                            sb(t2, a2, 14);
                            sb(t1, a2, 15);
                            lbu(t4, a3, 4);
                            lbu(t3, a3, 5);
                            lbu(t2, a3, 6);
                            lbu(t1, a3, 7);
                            sb(t4, a2, 16);
                            sb(t3, a2, 17);
                            sb(t2, a2, 18);
                            sb(t1, a2, 19);
                            lbu(t4, a3, 4);
                            lbu(t3, a3, 5);
                            lbu(t2, a3, 6);
                            lbu(t1, a3, 7);
                            sb(t4, a2, 20);
                            sb(t3, a2, 21);
                            sb(t2, a2, 22);
                            sb(t1, a2, 23);
                            lbu(t4, a3, 4);
                            lbu(t3, a3, 5);
                            lbu(t2, a3, 6);
                            lbu(t1, a3, 7);
                            sb(t4, a2, 24);
                            sb(t3, a2, 25);
                            sb(t2, a2, 26);
                            sb(t1, a2, 27);
                            lbu(t4, a3, 4);
                            lbu(t3, a3, 5);
                            lbu(t2, a3, 6);
                            lbu(t1, a3, 7);
                            sb(t4, a2, 28);
                            sb(t3, a2, 29);
                            sb(t2, a2, 30);
                            sb(t1, a2, 31);
                            lbu(t4, a3, 8);
                            lbu(t3, a3, 9);
                            lbu(t2, a3, 10);
                            lbu(t1, a3, 11);
                            sb(t4, a2, 32);
                            sb(t3, a2, 33);
                            sb(t2, a2, 34);
                            sb(t1, a2, 35);
                            lbu(t4, a3, 8);
                            lbu(t3, a3, 9);
                            lbu(t2, a3, 10);
                            lbu(t1, a3, 11);
                            sb(t4, a2, 36);
                            sb(t3, a2, 37);
                            sb(t2, a2, 38);
                            sb(t1, a2, 39);
                            lbu(t4, a3, 8);
                            lbu(t3, a3, 9);
                            lbu(t2, a3, 10);
                            lbu(t1, a3, 11);
                            sb(t4, a2, 40);
                            sb(t3, a2, 41);
                            sb(t2, a2, 42);
                            sb(t1, a2, 43);
                            lbu(t4, a3, 8);
                            lbu(t3, a3, 9);
                            lbu(t2, a3, 10);
                            lbu(t1, a3, 11);
                            sb(t4, a2, 44);
                            sb(t3, a2, 45);
                            sb(t2, a2, 46);
                            sb(t1, a2, 47);
                            lbu(t4, a3, 12);
                            lbu(t3, a3, 13);
                            lbu(t2, a3, 14);
                            lbu(t1, a3, 15);
                            sb(t4, a2, 48);
                            sb(t3, a2, 49);
                            sb(t2, a2, 50);
                            sb(t1, a2, 51);
                            lbu(t4, a3, 12);
                            lbu(t3, a3, 13);
                            lbu(t2, a3, 14);
                            lbu(t1, a3, 15);
                            sb(t4, a2, 52);
                            sb(t3, a2, 53);
                            sb(t2, a2, 54);
                            sb(t1, a2, 55);
                            lbu(t4, a3, 12);
                            lbu(t3, a3, 13);
                            lbu(t2, a3, 14);
                            lbu(t1, a3, 15);
                            sb(t4, a2, 56);
                            sb(t3, a2, 57);
                            sb(t2, a2, 58);
                            sb(t1, a2, 59);
                            lbu(t4, a3, 12);
                            lbu(t3, a3, 13);
                            lbu(t2, a3, 14);
                            lbu(t1, a3, 15);
                            sb(t4, a2, 60);
                            sb(t3, a2, 61);
                            sb(t2, a2, 62);
                            sb(t1, a2, 63);
                            lbu(t4, a3, 16);
                            lbu(t3, a3, 17);
                            lbu(t2, a3, 18);
                            lbu(t1, a3, 19);
                            sb(t4, a2, 64);
                            sb(t3, a2, 65);
                            sb(t2, a2, 66);
                            sb(t1, a2, 67);
                            lbu(t4, a3, 16);
                            lbu(t3, a3, 17);
                            lbu(t2, a3, 18);
                            lbu(t1, a3, 19);
                            sb(t4, a2, 68);
                            sb(t3, a2, 69);
                            sb(t2, a2, 70);
                            sb(t1, a2, 71);
                            lbu(t4, a3, 16);
                            lbu(t3, a3, 17);
                            lbu(t2, a3, 18);
                            lbu(t1, a3, 19);
                            sb(t4, a2, 72);
                            sb(t3, a2, 73);
                            sb(t2, a2, 74);
                            sb(t1, a2, 75);
                            lbu(t4, a3, 16);
                            lbu(t3, a3, 17);
                            lbu(t2, a3, 18);
                            lbu(t1, a3, 19);
                            sb(t4, a2, 76);
                            sb(t3, a2, 77);
                            sb(t2, a2, 78);
                            sb(t1, a2, 79);
                            lbu(t4, a3, 20);
                            lbu(t3, a3, 21);
                            lbu(t2, a3, 22);
                            lbu(t1, a3, 23);
                            sb(t4, a2, 80);
                            sb(t3, a2, 81);
                            sb(t2, a2, 82);
                            sb(t1, a2, 83);
                            lbu(t4, a3, 20);
                            lbu(t3, a3, 21);
                            lbu(t2, a3, 22);
                            lbu(t1, a3, 23);
                            sb(t4, a2, 84);
                            sb(t3, a2, 85);
                            sb(t2, a2, 86);
                            sb(t1, a2, 87);
                            lbu(t4, a3, 20);
                            lbu(t3, a3, 21);
                            lbu(t2, a3, 22);
                            lbu(t1, a3, 23);
                            sb(t4, a2, 88);
                            sb(t3, a2, 89);
                            sb(t2, a2, 90);
                            sb(t1, a2, 91);
                            lbu(t4, a3, 20);
                            lbu(t3, a3, 21);
                            lbu(t2, a3, 22);
                            lbu(t1, a3, 23);
                            sb(t4, a2, 92);
                            sb(t3, a2, 93);
                            sb(t2, a2, 94);
                            sb(t1, a2, 95);
                            lbu(t4, a3, 24);
                            lbu(t3, a3, 25);
                            lbu(t2, a3, 26);
                            lbu(t1, a3, 27);
                            sb(t4, a2, 96);
                            sb(t3, a2, 97);
                            sb(t2, a2, 98);
                            sb(t1, a2, 99);
                            lbu(t4, a3, 24);
                            lbu(t3, a3, 25);
                            lbu(t2, a3, 26);
                            lbu(t1, a3, 27);
                            sb(t4, a2, 100);
                            sb(t3, a2, 101);
                            sb(t2, a2, 102);
                            sb(t1, a2, 103);
                            lbu(t4, a3, 24);
                            lbu(t3, a3, 25);
                            lbu(t2, a3, 26);
                            lbu(t1, a3, 27);
                            sb(t4, a2, 104);
                            sb(t3, a2, 105);
                            sb(t2, a2, 106);
                            sb(t1, a2, 107);
                            lbu(t4, a3, 24);
                            lbu(t3, a3, 25);
                            lbu(t2, a3, 26);
                            lbu(t1, a3, 27);
                            sb(t4, a2, 108);
                            sb(t3, a2, 109);
                            sb(t2, a2, 110);
                            sb(t1, a2, 111);
                            lbu(t4, a3, 28);
                            lbu(t3, a3, 29);
                            lbu(t2, a3, 30);
                            lbu(t1, a3, 31);
                            sb(t4, a2, 112);
                            sb(t3, a2, 113);
                            sb(t2, a2, 114);
                            sb(t1, a2, 115);
                            lbu(t4, a3, 28);
                            lbu(t3, a3, 29);
                            lbu(t2, a3, 30);
                            lbu(t1, a3, 31);
                            sb(t4, a2, 116);
                            sb(t3, a2, 117);
                            sb(t2, a2, 118);
                            sb(t1, a2, 119);
                            lbu(t4, a3, 28);
                            lbu(t3, a3, 29);
                            lbu(t2, a3, 30);
                            lbu(t1, a3, 31);
                            sb(t4, a2, 120);
                            sb(t3, a2, 121);
                            sb(t2, a2, 122);
                            sb(t1, a2, 123);
                            lbu(t4, a3, 28);
                            lbu(t3, a3, 29);
                            lbu(t2, a3, 30);
                            lbu(t1, a3, 31);
                            sb(t4, a2, 124);
                            a3 = addiu(a3, 32);
                            sb(t3, a2, 125);
                            sb(t2, a2, 126);
                            sb(t1, a2, 127);
                            a2 = addiu(a2, 128);
                            if (t0 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x0048468c
                        charge(ctx, 1);
                    }
                }
                // 0x00484690
                charge(ctx, 3);
                at = slt(a1, a0);
                if (at != 0) {
                    for (;;) {
                        // 0x0048469c
                        charge(ctx, 37);
                        lbu(t3, a3, 0);
                        a1 = addiu(a1, 1);
                        lbu(t2, a3, 1);
                        v1 = slt(a1, a0);
                        lbu(t1, a3, 2);
                        lbu(t0, a3, 3);
                        sb(t3, a2, 0);
                        sb(t2, a2, 1);
                        sb(t1, a2, 2);
                        sb(t0, a2, 3);
                        lbu(t3, a3, 0);
                        lbu(t2, a3, 1);
                        lbu(t1, a3, 2);
                        lbu(t0, a3, 3);
                        sb(t3, a2, 4);
                        sb(t2, a2, 5);
                        sb(t1, a2, 6);
                        sb(t0, a2, 7);
                        lbu(t3, a3, 0);
                        lbu(t2, a3, 1);
                        lbu(t1, a3, 2);
                        lbu(t0, a3, 3);
                        sb(t3, a2, 8);
                        sb(t2, a2, 9);
                        sb(t1, a2, 10);
                        sb(t0, a2, 11);
                        lbu(t3, a3, 0);
                        lbu(t2, a3, 1);
                        lbu(t1, a3, 2);
                        lbu(t0, a3, 3);
                        sb(t3, a2, 12);
                        a3 = addiu(a3, 4);
                        sb(t2, a2, 13);
                        sb(t1, a2, 14);
                        sb(t0, a2, 15);
                        a2 = addiu(a2, 16);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
            }
            // 0x00484730
            charge(ctx, 5);
            v1 = 0x10010000;
            lw(a1, v1, -12288);  // 0x1000D000 D8 fromSPR CHCR
            a1 = a1 & 0x100;
            if (a1 != 0) {
                // 0x00484fbc
                charge(ctx, 4);
                a1 = 256;
                sw(a1, v1, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x00484fcc
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00484fe8
                charge(ctx, 2);
                v1 = 0x10010000;
                backedge(ctx);
            } else {
                // 0x00484744
                charge(ctx, 1);
                v1 = 0x10010000;
            }
            // 0x00484748
            charge(ctx, 4);
            lw(a1, v1, -11264);
            a1 = a1 & 0x100;
            if (a1 != 0) {
                // 0x00484ff0
                charge(ctx, 4);
                a1 = 512;
                sw(a1, v1, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x00485000
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0048501c
                charge(ctx, 1);
                v1 = 0x10010000;
                for (;;) {
                    // 0x00485020
                    charge(ctx, 7);
                    lw(a1, v1, -11264);
                    a1 = a1 & 0x100;
                    if (a1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0048503c
                charge(ctx, 2);
                a2 = 256;
                backedge(ctx);
            } else {
                // 0x00484758
                charge(ctx, 1);
                a2 = 256;
            }
            // 0x0048475c
            charge(ctx, 15);
            v1 = 0x10010000;
            sw(a2, v1, -8176);  // 0x1000E010 D_STAT
            a1 = 3264;
            sw(a1, v1, -12160);  // 0x1000D080 D8 fromSPR SADR
            sw(s0, v1, -12272);  // 0x1000D010 D8 fromSPR MADR
            sw(a0, v1, -12256);  // 0x1000D020 D8 fromSPR QWC
            sw(a2, v1, -12288);  // 0x1000D000 D8 fromSPR CHCR
            sync(ctx, 0);
            sync(ctx, 16);
            v1 = 0x4F000000;
            mtc1(v1, f0);
            c_le_s(f0, f1);
            if (cond(ctx)) {
                // 0x004847a8
                charge(ctx, 7);
                sub_s(f0, f1, f0);
                v1 = lui(0x8000);
                cvt_w_s(f0, f0);
                mfc1(a1, f0);
                a1 = a1 | v1;
                a1 = sll(a1, 4);
            } else {
                // 0x00484798
                charge(ctx, 4);
                cvt_w_s(f0, f1);
                mfc1(a1, f0);
                a1 = sll(a1, 4);
            }
            // 0x004847c4
            charge(ctx, 4);
            v1 = sll(a0, 4);
            s1 = addu(s1, a1);
            s0 = addu(s0, v1);
            s2 = subu(s2, a0);
        }
        // 0x004847d4
        charge(ctx, 2);
        if (s2 == 0) {
            backedge(ctx);
        } else {
            // 0x004847dc
            charge(ctx, 3);
            at = slt(0, s2);
            a0 = 0;
            if (at == 0) {
                backedge(ctx);
            } else {
                // 0x004847e8
                charge(ctx, 3);
                at = slti(s2, 9);
                v1 = addiu(s2, -8);
                if (at == 0) {
                    // 0x004847f4
                    charge(ctx, 3);
                    at = slt(s2, 0);
                    a1 = 0;
                    if (at == 0) {
                        // 0x00484800
                        charge(ctx, 5);
                        at = 0x7FFF0000;
                        at = at | 0xFFFF;
                        at = slt(s2, at);
                        if (at != 0) {
                            // 0x00484814
                            charge(ctx, 1);
                            a1 = 1;
                        }
                    }
                    // 0x00484818
                    charge(ctx, 2);
                    if (a1 != 0) {
                        for (;;) {
                            // 0x00484820
                            charge(ctx, 261);
                            lbu(t1, s1, 0);
                            a0 = addiu(a0, 8);
                            lbu(t0, s1, 1);
                            a1 = slt(a0, v1);
                            lbu(a3, s1, 2);
                            lbu(a2, s1, 3);
                            sb(t1, s0, 0);
                            sb(t0, s0, 1);
                            sb(a3, s0, 2);
                            sb(a2, s0, 3);
                            lbu(t1, s1, 0);
                            lbu(t0, s1, 1);
                            lbu(a3, s1, 2);
                            lbu(a2, s1, 3);
                            sb(t1, s0, 4);
                            sb(t0, s0, 5);
                            sb(a3, s0, 6);
                            sb(a2, s0, 7);
                            lbu(t1, s1, 0);
                            lbu(t0, s1, 1);
                            lbu(a3, s1, 2);
                            lbu(a2, s1, 3);
                            sb(t1, s0, 8);
                            sb(t0, s0, 9);
                            sb(a3, s0, 10);
                            sb(a2, s0, 11);
                            lbu(t1, s1, 0);
                            lbu(t0, s1, 1);
                            lbu(a3, s1, 2);
                            lbu(a2, s1, 3);
                            sb(t1, s0, 12);
                            sb(t0, s0, 13);
                            sb(a3, s0, 14);
                            sb(a2, s0, 15);
                            lbu(t1, s1, 4);
                            lbu(t0, s1, 5);
                            lbu(a3, s1, 6);
                            lbu(a2, s1, 7);
                            sb(t1, s0, 16);
                            sb(t0, s0, 17);
                            sb(a3, s0, 18);
                            sb(a2, s0, 19);
                            lbu(t1, s1, 4);
                            lbu(t0, s1, 5);
                            lbu(a3, s1, 6);
                            lbu(a2, s1, 7);
                            sb(t1, s0, 20);
                            sb(t0, s0, 21);
                            sb(a3, s0, 22);
                            sb(a2, s0, 23);
                            lbu(t1, s1, 4);
                            lbu(t0, s1, 5);
                            lbu(a3, s1, 6);
                            lbu(a2, s1, 7);
                            sb(t1, s0, 24);
                            sb(t0, s0, 25);
                            sb(a3, s0, 26);
                            sb(a2, s0, 27);
                            lbu(t1, s1, 4);
                            lbu(t0, s1, 5);
                            lbu(a3, s1, 6);
                            lbu(a2, s1, 7);
                            sb(t1, s0, 28);
                            sb(t0, s0, 29);
                            sb(a3, s0, 30);
                            sb(a2, s0, 31);
                            lbu(t1, s1, 8);
                            lbu(t0, s1, 9);
                            lbu(a3, s1, 10);
                            lbu(a2, s1, 11);
                            sb(t1, s0, 32);
                            sb(t0, s0, 33);
                            sb(a3, s0, 34);
                            sb(a2, s0, 35);
                            lbu(t1, s1, 8);
                            lbu(t0, s1, 9);
                            lbu(a3, s1, 10);
                            lbu(a2, s1, 11);
                            sb(t1, s0, 36);
                            sb(t0, s0, 37);
                            sb(a3, s0, 38);
                            sb(a2, s0, 39);
                            lbu(t1, s1, 8);
                            lbu(t0, s1, 9);
                            lbu(a3, s1, 10);
                            lbu(a2, s1, 11);
                            sb(t1, s0, 40);
                            sb(t0, s0, 41);
                            sb(a3, s0, 42);
                            sb(a2, s0, 43);
                            lbu(t1, s1, 8);
                            lbu(t0, s1, 9);
                            lbu(a3, s1, 10);
                            lbu(a2, s1, 11);
                            sb(t1, s0, 44);
                            sb(t0, s0, 45);
                            sb(a3, s0, 46);
                            sb(a2, s0, 47);
                            lbu(t1, s1, 12);
                            lbu(t0, s1, 13);
                            lbu(a3, s1, 14);
                            lbu(a2, s1, 15);
                            sb(t1, s0, 48);
                            sb(t0, s0, 49);
                            sb(a3, s0, 50);
                            sb(a2, s0, 51);
                            lbu(t1, s1, 12);
                            lbu(t0, s1, 13);
                            lbu(a3, s1, 14);
                            lbu(a2, s1, 15);
                            sb(t1, s0, 52);
                            sb(t0, s0, 53);
                            sb(a3, s0, 54);
                            sb(a2, s0, 55);
                            lbu(t1, s1, 12);
                            lbu(t0, s1, 13);
                            lbu(a3, s1, 14);
                            lbu(a2, s1, 15);
                            sb(t1, s0, 56);
                            sb(t0, s0, 57);
                            sb(a3, s0, 58);
                            sb(a2, s0, 59);
                            lbu(t1, s1, 12);
                            lbu(t0, s1, 13);
                            lbu(a3, s1, 14);
                            lbu(a2, s1, 15);
                            sb(t1, s0, 60);
                            sb(t0, s0, 61);
                            sb(a3, s0, 62);
                            sb(a2, s0, 63);
                            lbu(t1, s1, 16);
                            lbu(t0, s1, 17);
                            lbu(a3, s1, 18);
                            lbu(a2, s1, 19);
                            sb(t1, s0, 64);
                            sb(t0, s0, 65);
                            sb(a3, s0, 66);
                            sb(a2, s0, 67);
                            lbu(t1, s1, 16);
                            lbu(t0, s1, 17);
                            lbu(a3, s1, 18);
                            lbu(a2, s1, 19);
                            sb(t1, s0, 68);
                            sb(t0, s0, 69);
                            sb(a3, s0, 70);
                            sb(a2, s0, 71);
                            lbu(t1, s1, 16);
                            lbu(t0, s1, 17);
                            lbu(a3, s1, 18);
                            lbu(a2, s1, 19);
                            sb(t1, s0, 72);
                            sb(t0, s0, 73);
                            sb(a3, s0, 74);
                            sb(a2, s0, 75);
                            lbu(t1, s1, 16);
                            lbu(t0, s1, 17);
                            lbu(a3, s1, 18);
                            lbu(a2, s1, 19);
                            sb(t1, s0, 76);
                            sb(t0, s0, 77);
                            sb(a3, s0, 78);
                            sb(a2, s0, 79);
                            lbu(t1, s1, 20);
                            lbu(t0, s1, 21);
                            lbu(a3, s1, 22);
                            lbu(a2, s1, 23);
                            sb(t1, s0, 80);
                            sb(t0, s0, 81);
                            sb(a3, s0, 82);
                            sb(a2, s0, 83);
                            lbu(t1, s1, 20);
                            lbu(t0, s1, 21);
                            lbu(a3, s1, 22);
                            lbu(a2, s1, 23);
                            sb(t1, s0, 84);
                            sb(t0, s0, 85);
                            sb(a3, s0, 86);
                            sb(a2, s0, 87);
                            lbu(t1, s1, 20);
                            lbu(t0, s1, 21);
                            lbu(a3, s1, 22);
                            lbu(a2, s1, 23);
                            sb(t1, s0, 88);
                            sb(t0, s0, 89);
                            sb(a3, s0, 90);
                            sb(a2, s0, 91);
                            lbu(t1, s1, 20);
                            lbu(t0, s1, 21);
                            lbu(a3, s1, 22);
                            lbu(a2, s1, 23);
                            sb(t1, s0, 92);
                            sb(t0, s0, 93);
                            sb(a3, s0, 94);
                            sb(a2, s0, 95);
                            lbu(t1, s1, 24);
                            lbu(t0, s1, 25);
                            lbu(a3, s1, 26);
                            lbu(a2, s1, 27);
                            sb(t1, s0, 96);
                            sb(t0, s0, 97);
                            sb(a3, s0, 98);
                            sb(a2, s0, 99);
                            lbu(t1, s1, 24);
                            lbu(t0, s1, 25);
                            lbu(a3, s1, 26);
                            lbu(a2, s1, 27);
                            sb(t1, s0, 100);
                            sb(t0, s0, 101);
                            sb(a3, s0, 102);
                            sb(a2, s0, 103);
                            lbu(t1, s1, 24);
                            lbu(t0, s1, 25);
                            lbu(a3, s1, 26);
                            lbu(a2, s1, 27);
                            sb(t1, s0, 104);
                            sb(t0, s0, 105);
                            sb(a3, s0, 106);
                            sb(a2, s0, 107);
                            lbu(t1, s1, 24);
                            lbu(t0, s1, 25);
                            lbu(a3, s1, 26);
                            lbu(a2, s1, 27);
                            sb(t1, s0, 108);
                            sb(t0, s0, 109);
                            sb(a3, s0, 110);
                            sb(a2, s0, 111);
                            lbu(t1, s1, 28);
                            lbu(t0, s1, 29);
                            lbu(a3, s1, 30);
                            lbu(a2, s1, 31);
                            sb(t1, s0, 112);
                            sb(t0, s0, 113);
                            sb(a3, s0, 114);
                            sb(a2, s0, 115);
                            lbu(t1, s1, 28);
                            lbu(t0, s1, 29);
                            lbu(a3, s1, 30);
                            lbu(a2, s1, 31);
                            sb(t1, s0, 116);
                            sb(t0, s0, 117);
                            sb(a3, s0, 118);
                            sb(a2, s0, 119);
                            lbu(t1, s1, 28);
                            lbu(t0, s1, 29);
                            lbu(a3, s1, 30);
                            lbu(a2, s1, 31);
                            sb(t1, s0, 120);
                            sb(t0, s0, 121);
                            sb(a3, s0, 122);
                            sb(a2, s0, 123);
                            lbu(t1, s1, 28);
                            lbu(t0, s1, 29);
                            lbu(a3, s1, 30);
                            lbu(a2, s1, 31);
                            sb(t1, s0, 124);
                            s1 = addiu(s1, 32);
                            sb(t0, s0, 125);
                            sb(a3, s0, 126);
                            sb(a2, s0, 127);
                            s0 = addiu(s0, 128);
                            if (a1 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x00484c34
                        charge(ctx, 1);
                    }
                }
                // 0x00484c38
                charge(ctx, 3);
                at = slt(a0, s2);
                if (at == 0) {
                    backedge(ctx);
                } else {
                    for (;;) {
                        // 0x00484c44
                        charge(ctx, 37);
                        lbu(t0, s1, 0);
                        a0 = addiu(a0, 1);
                        lbu(a3, s1, 1);
                        v1 = slt(a0, s2);
                        lbu(a2, s1, 2);
                        lbu(a1, s1, 3);
                        sb(t0, s0, 0);
                        sb(a3, s0, 1);
                        sb(a2, s0, 2);
                        sb(a1, s0, 3);
                        lbu(t0, s1, 0);
                        lbu(a3, s1, 1);
                        lbu(a2, s1, 2);
                        lbu(a1, s1, 3);
                        sb(t0, s0, 4);
                        sb(a3, s0, 5);
                        sb(a2, s0, 6);
                        sb(a1, s0, 7);
                        lbu(t0, s1, 0);
                        lbu(a3, s1, 1);
                        lbu(a2, s1, 2);
                        lbu(a1, s1, 3);
                        sb(t0, s0, 8);
                        sb(a3, s0, 9);
                        sb(a2, s0, 10);
                        sb(a1, s0, 11);
                        lbu(t0, s1, 0);
                        lbu(a3, s1, 1);
                        lbu(a2, s1, 2);
                        lbu(a1, s1, 3);
                        sb(t0, s0, 12);
                        s1 = addiu(s1, 4);
                        sb(a3, s0, 13);
                        sb(a2, s0, 14);
                        sb(a1, s0, 15);
                        s0 = addiu(s0, 16);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00484cd8
                    charge(ctx, 2);
                    backedge(ctx);
                }
            }
        }
    } else {
        // 0x00483924
        charge(ctx, 3);
        at = slt(0, s2);
        s7 = 0;
        if (at != 0) {
            // 0x00483930
            charge(ctx, 4);
            a0 = addiu(s2, -8);
            at = slti(s2, 9);
            sq(a0, sp, 0x1E0);
            if (at == 0) {
                // 0x00483940
                charge(ctx, 3);
                at = slt(s2, 0);
                a0 = 0;
                if (at == 0) {
                    // 0x0048394c
                    charge(ctx, 5);
                    at = 0x7FFF0000;
                    at = at | 0xFFFF;
                    at = slt(s2, at);
                    if (at != 0) {
                        // 0x00483960
                        charge(ctx, 1);
                        a0 = 1;
                    }
                }
                // 0x00483964
                charge(ctx, 2);
                if (a0 != 0) {
                    for (;;) {
                        // 0x0048396c
                        charge(ctx, 153);
                        t2 = addu(s0, v1);
                        lw(a1, s1, 0);
                        a3 = addu(t2, v1);
                        s4 = addu(s1, s6);
                        a0 = addu(a3, v1);
                        t6 = addu(s4, s6);
                        s5 = addu(a0, v1);
                        t3 = addu(t6, s6);
                        s3 = addu(s5, v1);
                        t1 = addu(t3, s6);
                        t9 = addu(s3, v1);
                        t0 = addu(t1, s6);
                        t8 = addu(t9, v1);
                        sw(a1, s0, 0);
                        t7 = addu(t8, v1);
                        lw(fp, s1, 0);
                        t5 = addu(t7, v1);
                        a2 = addu(t0, s6);
                        t4 = addu(t5, v1);
                        s7 = addiu(s7, 8);
                        s0 = addu(t4, v1);
                        a1 = addu(a2, s6);
                        sq(s0, sp, 0x1C0);
                        s0 = addu(s0, v1);
                        sq(s0, sp, 0x1B0);
                        lq(s0, sp, 0x1E0);
                        sw(fp, t2, 0);
                        lw(fp, s1, 0);
                        s0 = slt(s7, s0);
                        sq(s0, sp, 0xB0);
                        lq(s0, sp, 0x1B0);
                        sw(fp, a3, 0);
                        s0 = addu(s0, v1);
                        paddub(t2, s0, zero);
                        sq(s0, sp, 0x1A0);
                        t2 = addu(t2, v1);
                        s0 = addu(t2, v1);
                        sq(s0, sp, 0x190);
                        s0 = addu(s0, v1);
                        sq(s0, sp, 0x180);
                        s0 = addu(s0, v1);
                        sq(s0, sp, 0x170);
                        s0 = addu(s0, v1);
                        sq(s0, sp, 0x160);
                        s0 = addu(s0, v1);
                        sq(s0, sp, 0x150);
                        s0 = addu(s0, v1);
                        paddub(a3, s0, zero);
                        sq(s0, sp, 0x140);
                        lw(s0, s1, 0);
                        a3 = addu(a3, v1);
                        s1 = addu(a3, v1);
                        sw(s0, a0, 0);
                        sq(s1, sp, 0x130);
                        s1 = addu(s1, v1);
                        sq(s1, sp, 0x120);
                        s1 = addu(s1, v1);
                        sq(s1, sp, 0x110);
                        s1 = addu(s1, v1);
                        sq(s1, sp, 0x100);
                        s1 = addu(s1, v1);
                        sq(s1, sp, 0xF0);
                        s1 = addu(s1, v1);
                        paddub(a0, s1, zero);
                        sq(s1, sp, 0xE0);
                        fp = addu(a0, v1);
                        s1 = addu(a1, s6);
                        lw(a0, s4, 0);
                        sq(a0, sp, 0x1D0);
                        a0 = addu(fp, v1);
                        sq(a0, sp, 0xA0);
                        a0 = addu(a0, v1);
                        sq(a0, sp, 0xD0);
                        a0 = addu(a0, v1);
                        sq(a0, sp, 0xC0);
                        s0 = addu(a0, v1);
                        lq(a0, sp, 0x1D0);
                        sw(a0, s5, 0);
                        lw(a0, s4, 0);
                        sw(a0, s3, 0);
                        lw(a0, s4, 0);
                        sw(a0, t9, 0);
                        lw(a0, s4, 0);
                        sw(a0, t8, 0);
                        lw(a0, t6, 0);
                        sw(a0, t7, 0);
                        lw(a0, t6, 0);
                        sw(a0, t5, 0);
                        lw(a0, t6, 0);
                        sw(a0, t4, 0);
                        lw(t4, t6, 0);
                        lq(a0, sp, 0x1C0);
                        sw(t4, a0, 0);
                        lw(t4, t3, 0);
                        lq(a0, sp, 0x1B0);
                        sw(t4, a0, 0);
                        lw(t4, t3, 0);
                        lq(a0, sp, 0x1A0);
                        sw(t4, a0, 0);
                        lw(a0, t3, 0);
                        sw(a0, t2, 0);
                        lw(t2, t3, 0);
                        lq(a0, sp, 0x190);
                        sw(t2, a0, 0);
                        lw(t2, t1, 0);
                        lq(a0, sp, 0x180);
                        sw(t2, a0, 0);
                        lw(t2, t1, 0);
                        lq(a0, sp, 0x170);
                        sw(t2, a0, 0);
                        lw(t2, t1, 0);
                        lq(a0, sp, 0x160);
                        sw(t2, a0, 0);
                        lw(t1, t1, 0);
                        lq(a0, sp, 0x150);
                        sw(t1, a0, 0);
                        lw(t1, t0, 0);
                        lq(a0, sp, 0x140);
                        sw(t1, a0, 0);
                        lw(a0, t0, 0);
                        sw(a0, a3, 0);
                        lw(a3, t0, 0);
                        lq(a0, sp, 0x130);
                        sw(a3, a0, 0);
                        lw(a3, t0, 0);
                        lq(a0, sp, 0x120);
                        sw(a3, a0, 0);
                        lw(a3, a2, 0);
                        lq(a0, sp, 0x110);
                        sw(a3, a0, 0);
                        lw(a3, a2, 0);
                        lq(a0, sp, 0x100);
                        sw(a3, a0, 0);
                        lw(a3, a2, 0);
                        lq(a0, sp, 0xF0);
                        sw(a3, a0, 0);
                        lw(a2, a2, 0);
                        lq(a0, sp, 0xE0);
                        sw(a2, a0, 0);
                        lw(a0, a1, 0);
                        sw(a0, fp, 0x0);
                        lw(a2, a1, 0);
                        lq(a0, sp, 0xA0);
                        sw(a2, a0, 0);
                        lw(a2, a1, 0);
                        lq(a0, sp, 0xD0);
                        sw(a2, a0, 0);
                        lw(a1, a1, 0);
                        lq(a0, sp, 0xC0);
                        sw(a1, a0, 0);
                        lq(a0, sp, 0xB0);
                        if (a0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
            }
            // 0x00483bd0
            charge(ctx, 3);
            at = slt(s7, s2);
            if (at != 0) {
                for (;;) {
                    // 0x00483bdc
                    charge(ctx, 16);
                    lw(a1, s1, 0);
                    t0 = addu(s0, v1);
                    a3 = addu(t0, v1);
                    s7 = addiu(s7, 1);
                    a2 = addu(a3, v1);
                    a0 = slt(s7, s2);
                    sw(a1, s0, 0);
                    lw(a1, s1, 0);
                    s0 = addu(a2, v1);
                    sw(a1, t0, 0);
                    lw(a1, s1, 0);
                    sw(a1, a3, 0);
                    lw(a1, s1, 0);
                    sw(a1, a2, 0);
                    s1 = addu(s1, s6);
                    if (a0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00483c1c
                charge(ctx, 1);
            }
        }
    }
    // 0x00483c20
    charge(ctx, 2);
    ld(ra, sp, 0x90);
    // 0x00485044
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
    sp = addiu(sp, 0x1F0);
}

// 0x00485750 sub_485750 -- 1740 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Scratchpad DMA kernel, plain variant (no SPR parameter block).
void sub_485750(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, t8{ctx, 24}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x00485750
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(t1, a0, 4);
    lw(t0, a2, 64);
    lw(s1, a0, 0);
    lw(s0, a2, 60);
    v1 = sll(t1, 1);
    s2 = a1;
    if (t0 == v1) {
        // 0x00485800
        charge(ctx, 7);
        a0 = 0;
        jal(ctx, 0x485800u, gen::fn__sceFlushCache_005033e0);
        v1 = 0x10010000;
        lw(a0, v1, -12288);  // 0x1000D000 D8 fromSPR CHCR
        a0 = a0 & 0x100;
        if (a0 != 0) {
            // 0x00485a50
            charge(ctx, 4);
            a0 = 256;
            sw(a0, v1, -8160);
            sync(ctx, 0);
            sync(ctx, 16);
            for (;;) {
                // 0x00485a60
                charge(ctx, 7);
                if (cop0_cond(ctx)) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00485a7c
            charge(ctx, 2);
            v1 = 0x10010000;
            backedge(ctx);
        } else {
            // 0x0048581c
            charge(ctx, 1);
            v1 = 0x10010000;
        }
        // 0x00485820
        charge(ctx, 4);
        lw(a0, v1, -11264);
        a0 = a0 & 0x100;
        if (a0 != 0) {
            // 0x00485a84
            charge(ctx, 4);
            a0 = 512;
            sw(a0, v1, -8160);
            sync(ctx, 0);
            sync(ctx, 16);
            for (;;) {
                // 0x00485a94
                charge(ctx, 7);
                if (cop0_cond(ctx)) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00485ab0
            charge(ctx, 1);
            v1 = 0x10010000;
            for (;;) {
                // 0x00485ab4
                charge(ctx, 7);
                lw(a0, v1, -11264);
                a0 = a0 & 0x100;
                if (a0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00485ad0
            charge(ctx, 2);
            at = slti(s2, 342);
            backedge(ctx);
        } else {
            // 0x00485830
            charge(ctx, 1);
            at = slti(s2, 342);
        }
        // 0x00485834
        charge(ctx, 2);
        if (at == 0) {
            // 0x0048583c
            charge(ctx, 8);
            a0 = 0x70000000;
            t0 = 0x10010000;
            a3 = 512;
            a1 = 256;
            a2 = 341;
            t3 = 5456;
            v1 = a0 | 0x1550;
            t2 = 682;
            for (;;) {
                // 0x0048585c
                charge(ctx, 4);
                lw(t1, t0, -12288);
                t1 = t1 & 0x100;
                if (t1 != 0) {
                    // 0x00485ad8
                    charge(ctx, 4);
                    sw(a1, t0, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x00485ae8
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00485b04
                    charge(ctx, 2);
                    backedge(ctx);
                } else {
                    // 0x0048586c
                    charge(ctx, 1);
                }
                // 0x00485870
                charge(ctx, 4);
                lw(t1, t0, -11264);
                t1 = t1 & 0x100;
                if (t1 != 0) {
                    // 0x00485b10
                    charge(ctx, 4);
                    sw(a3, t0, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x00485b20
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00485b3c
                    charge(ctx, 1);
                    for (;;) {
                        // 0x00485b40
                        charge(ctx, 7);
                        lw(t1, t0, -11264);
                        t1 = t1 & 0x100;
                        if (t1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00485b5c
                    charge(ctx, 2);
                    backedge(ctx);
                }
                // 0x00485880
                charge(ctx, 11);
                sw(a3, t0, -8176);
                sw(zero, t0, -11136);
                sw(s0, t0, -11248);
                sw(a2, t0, -11232);
                sw(a1, t0, -11264);
                sync(ctx, 0);
                sync(ctx, 16);
                lw(t1, t0, -11264);
                t1 = t1 & 0x100;
                if (t1 != 0) {
                    // 0x00485b68
                    charge(ctx, 4);
                    sw(a3, t0, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x00485b78
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00485b94
                    charge(ctx, 1);
                    for (;;) {
                        // 0x00485b98
                        charge(ctx, 7);
                        lw(t1, t0, -11264);
                        t1 = t1 & 0x100;
                        if (t1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00485bb4
                    charge(ctx, 2);
                    backedge(ctx);
                } else {
                    // 0x004858ac
                    charge(ctx, 1);
                }
                // 0x004858b0
                charge(ctx, 4);
                t6 = a0;
                t5 = v1;
                t8 = 0;
                for (;;) {
                    // 0x004858c0
                    charge(ctx, 23);
                    t7 = t6;
                    lwc1(f0, t7, 0);
                    t4 = addiu(t6, 8);
                    t8 = addiu(t8, 1);
                    t6 = addiu(t6, 16);
                    t1 = slti(t8, 341);
                    swc1(f0, t5, 0);
                    lwc1(f0, t4, 4);
                    swc1(f0, t5, 4);
                    lwc1(f0, t4, 0);
                    swc1(f0, t5, 8);
                    lwc1(f0, t4, 4);
                    swc1(f0, t5, 12);
                    lwc1(f0, t4, 0);
                    swc1(f0, t5, 16);
                    lwc1(f0, t7, 4);
                    swc1(f0, t5, 20);
                    lwc1(f0, t7, 0);
                    swc1(f0, t5, 24);
                    lwc1(f0, t7, 4);
                    swc1(f0, t5, 28);
                    t5 = addiu(t5, 32);
                    if (t1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0048591c
                charge(ctx, 4);
                lw(t1, t0, -12288);
                t1 = t1 & 0x100;
                if (t1 != 0) {
                    // 0x00485bc0
                    charge(ctx, 4);
                    sw(a1, t0, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x00485bd0
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00485bec
                    charge(ctx, 2);
                    backedge(ctx);
                } else {
                    // 0x0048592c
                    charge(ctx, 1);
                }
                // 0x00485930
                charge(ctx, 4);
                lw(t1, t0, -11264);
                t1 = t1 & 0x100;
                if (t1 != 0) {
                    // 0x00485bf8
                    charge(ctx, 4);
                    sw(a3, t0, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x00485c08
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00485c24
                    charge(ctx, 1);
                    for (;;) {
                        // 0x00485c28
                        charge(ctx, 7);
                        lw(t1, t0, -11264);
                        t1 = t1 & 0x100;
                        if (t1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00485c44
                    charge(ctx, 2);
                    backedge(ctx);
                }
                // 0x00485940
                charge(ctx, 12);
                sw(a1, t0, -8176);
                sw(t3, t0, -12160);
                sw(s1, t0, -12272);
                sw(t2, t0, -12256);
                sw(a1, t0, -12288);
                sync(ctx, 0);
                sync(ctx, 16);
                s2 = addiu(s2, -341);
                s0 = addiu(s0, 5456);
                at = slti(s2, 342);
                s1 = addiu(s1, 10912);
                if (at != 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x00485970
        charge(ctx, 2);
        if (s2 == 0) {
            backedge(ctx);
        } else {
            // 0x00485978
            charge(ctx, 5);
            v1 = 0x10010000;
            lw(a0, v1, -12288);  // 0x1000D000 D8 fromSPR CHCR
            a0 = a0 & 0x100;
            if (a0 != 0) {
                // 0x00485c50
                charge(ctx, 4);
                a0 = 256;
                sw(a0, v1, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x00485c60
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00485c7c
                charge(ctx, 2);
                v1 = 0x10010000;
                backedge(ctx);
            } else {
                // 0x0048598c
                charge(ctx, 1);
                v1 = 0x10010000;
            }
            // 0x00485990
            charge(ctx, 4);
            lw(a0, v1, -11264);
            a0 = a0 & 0x100;
            if (a0 != 0) {
                // 0x00485c84
                charge(ctx, 4);
                a0 = 512;
                sw(a0, v1, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x00485c94
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00485cb0
                charge(ctx, 1);
                v1 = 0x10010000;
                for (;;) {
                    // 0x00485cb4
                    charge(ctx, 7);
                    lw(a0, v1, -11264);
                    a0 = a0 & 0x100;
                    if (a0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00485cd0
                charge(ctx, 2);
                a1 = 512;
                backedge(ctx);
            } else {
                // 0x004859a0
                charge(ctx, 1);
                a1 = 512;
            }
            // 0x004859a4
            charge(ctx, 13);
            v1 = 0x10010000;
            sw(a1, v1, -8176);  // 0x1000E010 D_STAT
            a0 = 256;
            sw(zero, v1, -11136);  // 0x1000D480 D9 toSPR SADR
            sw(s0, v1, -11248);  // 0x1000D410 D9 toSPR MADR
            sw(s2, v1, -11232);  // 0x1000D420 D9 toSPR QWC
            sw(a0, v1, -11264);  // 0x1000D400 D9 toSPR CHCR
            sync(ctx, 0);
            sync(ctx, 16);
            lw(a0, v1, -11264);  // 0x1000D400 D9 toSPR CHCR
            a0 = a0 & 0x100;
            if (a0 != 0) {
                // 0x00485cd8
                charge(ctx, 3);
                sw(a1, v1, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x00485ce4
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00485d00
                charge(ctx, 1);
                v1 = 0x10010000;
                for (;;) {
                    // 0x00485d04
                    charge(ctx, 7);
                    lw(a0, v1, -11264);
                    a0 = a0 & 0x100;
                    if (a0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00485d20
                charge(ctx, 2);
                t0 = 0x70000000;
                backedge(ctx);
            } else {
                // 0x004859d8
                charge(ctx, 1);
                t0 = 0x70000000;
            }
            // 0x004859dc
            charge(ctx, 4);
            at = slt(0, s2);
            a2 = 0;
            a3 = t0 | 0x1550;
            if (at == 0) {
                // 0x00485d28
                charge(ctx, 1);
                v1 = 0x10010000;
            } else {
                for (;;) {
                    // 0x004859ec
                    charge(ctx, 23);
                    a1 = t0;
                    a0 = addiu(t0, 8);
                    lwc1(f0, a1, 0);
                    a2 = addiu(a2, 1);
                    v1 = slt(a2, s2);
                    t0 = addiu(t0, 16);
                    swc1(f0, a3, 0);
                    lwc1(f0, a0, 4);
                    swc1(f0, a3, 4);
                    lwc1(f0, a0, 0);
                    swc1(f0, a3, 8);
                    lwc1(f0, a0, 4);
                    swc1(f0, a3, 12);
                    lwc1(f0, a0, 0);
                    swc1(f0, a3, 16);
                    lwc1(f0, a1, 4);
                    swc1(f0, a3, 20);
                    lwc1(f0, a1, 0);
                    swc1(f0, a3, 24);
                    lwc1(f0, a1, 4);
                    swc1(f0, a3, 28);
                    a3 = addiu(a3, 32);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00485a48
                charge(ctx, 2);
                v1 = 0x10010000;
            }
            // 0x00485d2c
            charge(ctx, 4);
            lw(a0, v1, -12288);
            a0 = a0 & 0x100;
            if (a0 != 0) {
                // 0x00485dd4
                charge(ctx, 4);
                a0 = 256;
                sw(a0, v1, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x00485de4
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00485e00
                charge(ctx, 2);
                v1 = 0x10010000;
                backedge(ctx);
            } else {
                // 0x00485d3c
                charge(ctx, 1);
                v1 = 0x10010000;
            }
            // 0x00485d40
            charge(ctx, 4);
            lw(a0, v1, -11264);
            a0 = a0 & 0x100;
            if (a0 != 0) {
                // 0x00485d50
                charge(ctx, 4);
                a0 = 512;
                sw(a0, v1, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x00485d60
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00485d7c
                charge(ctx, 1);
                v1 = 0x10010000;
                for (;;) {
                    // 0x00485d80
                    charge(ctx, 7);
                    lw(a0, v1, -11264);
                    a0 = a0 & 0x100;
                    if (a0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00485d9c
                charge(ctx, 1);
            }
            // 0x00485da0
            charge(ctx, 13);
            a2 = 256;
            v1 = 0x10010000;
            a1 = 5456;
            sw(a2, v1, -8176);  // 0x1000E010 D_STAT
            a0 = sll(s2, 1);
            sw(a1, v1, -12160);  // 0x1000D080 D8 fromSPR SADR
            sw(s1, v1, -12272);  // 0x1000D010 D8 fromSPR MADR
            sw(a0, v1, -12256);  // 0x1000D020 D8 fromSPR QWC
            sw(a2, v1, -12288);  // 0x1000D000 D8 fromSPR CHCR
            sync(ctx, 0);
            sync(ctx, 16);
            backedge(ctx);
        }
    } else {
        // 0x00485780
        charge(ctx, 3);
        at = slt(0, s2);
        t3 = 0;
        if (at != 0) {
            for (;;) {
                // 0x0048578c
                charge(ctx, 26);
                t2 = s0;
                a3 = addiu(s0, 8);
                lwc1(f0, t2, 0);
                a2 = addu(s1, t1);
                a1 = addu(a2, t1);
                t3 = addiu(t3, 1);
                a0 = addu(a1, t1);
                v1 = slt(t3, s2);
                s0 = addu(s0, t0);
                swc1(f0, s1, 0);
                lwc1(f0, a3, 4);
                swc1(f0, s1, 4);
                lwc1(f0, a3, 0);
                s1 = addu(a0, t1);
                swc1(f0, a2, 0);
                lwc1(f0, a3, 4);
                swc1(f0, a2, 4);
                lwc1(f0, a3, 0);
                swc1(f0, a1, 0);
                lwc1(f0, t2, 4);
                swc1(f0, a1, 4);
                lwc1(f0, t2, 0);
                swc1(f0, a0, 0);
                lwc1(f0, t2, 4);
                swc1(f0, a0, 4);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004857f4
            charge(ctx, 1);
        }
    }
    // 0x004857f8
    charge(ctx, 2);
    ld(ra, sp, 0x30);
    // 0x00485e08
    charge(ctx, 5);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00490D40 sub_490D40 -- 64 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Object destructor hook (8 data refs): releases the plugin data at the offset in 0x7CE810's table (sub_492060), then
// the object (sub_4CA030); returns the object.
void sub_490D40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00490d40
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, -17632);  // 0x7CE810
    s0 = a0;
    v0 = addu(s0, v0);
    lw(a0, v0, 0);
    a1 = s0;
    jal(ctx, 0x490D5Cu, gen::fn_sub_492060_00492060);
    a0 = s0;
    jal(ctx, 0x490D64u, gen::fn_sub_4CA030_004ca030);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0049CC30 sub_49CC30 -- 60 bytes; frame 0x10: ra sp+0x0
// When the record's word +24 is set, forces two DMA buffer swaps (flushes both halves of the RW DMA ring).
void sub_49CC30(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0049cc30
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, a0, 24);
    if (v1 != 0) {
        // 0x0049cc4c
        charge(ctx, 6);
        jal(ctx, 0x49CC4Cu, gen::fn__rwDMAForceBufferSwap_004d4df0);
        jal(ctx, 0x49CC54u, gen::fn__rwDMAForceBufferSwap_004d4df0);
        backedge(ctx);
    }
    // 0x0049cc44
    charge(ctx, 2);
    ld(ra, sp, 0x0);
    // 0x0049cc64
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x004C08A0 sub_4C08A0 -- 452 bytes; frame 0x150: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// File-system device open: sceOpen, size by sceLseek to the end and back, sceClose on failure; fills the file record
// (sub_4BF7E0 / sub_4BF880) and calls its hook through $jalr.
void sub_4C08A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c08a0
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x150);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a2;
    sq(s1, sp, 0x10);
    s2 = a1;
    sq(s0, sp, 0x0);
    s1 = a3;
    lw(v0, a0, 28);
    s0 = 0;
    jalr(ctx, 0x4C08C8u, v0.u());
    a0 = s3;
    s3 = v0;
    jal(ctx, 0x4C08D4u, gen::fn_sub_4BF7E0_004bf7e0);
    a2 = s3;
    a0 = addiu(sp, 0x50);
    a1 = 256;
    a3 = v0;
    t0 = 47;
    jal(ctx, 0x4C08ECu, gen::fn_sub_4BF880_004bf880);
    if (v0 == 0) {
        // 0x004c0974
        charge(ctx, 2);
        v0 = 5;
    } else {
        // 0x004c08fc
        charge(ctx, 3);
        v0 = s1 & 0x1;
        if (v0 != 0) {
            // 0x004c097c
            charge(ctx, 3);
            v1 = s1 & 0x2;
            if (v1 == 0) {
                backedge(ctx);
                goto L_004c0908;
            }
            // 0x004c0988
            charge(ctx, 2);
            s0 = s0 | 0x3;
            backedge(ctx);
            goto L_004c0924;
        }
    L_004c0908:
        charge(ctx, 2);
        if (v0 != 0) {
            // 0x004c0910
            charge(ctx, 1);
            s0 = s0 | 0x1;
        }
        // 0x004c0914
        charge(ctx, 3);
        v1 = s1 & 0x2;
        if (v1 != 0) {
            // 0x004c0920
            charge(ctx, 1);
            s0 = s0 | 0x2;
        }
    L_004c0924:
        charge(ctx, 3);
        v0 = s1 & 0x4;
        if (v0 != 0) {
            // 0x004c0930
            charge(ctx, 1);
            s0 = s0 | 0x200;
        }
        // 0x004c0934
        charge(ctx, 2);
        if (v1 != 0) {
            // 0x004c093c
            charge(ctx, 3);
            v0 = s1 & 0x8;
            if (v0 == 0) {
                // 0x004c0948
                charge(ctx, 1);
                s0 = s0 | 0x400;
            }
        }
        // 0x004c094c
        charge(ctx, 8);
        a0 = addiu(sp, 0x50);
        a1 = s0;
        link(ctx, 0x4C0954u);  // $ra first: the delay slot below depends on it
        sw(zero, s2, 48);
        call(ctx, gen::fn_sceOpen_00508670);
        sw(v0, s2, 96);
        lw(a0, s2, 96);
        if (i64(a0) >= 0) {
            // 0x004c0990
            charge(ctx, 8);
            a1 = 0;
            a2 = 2;
            jal(ctx, 0x4C0994u, gen::fn_sceLseek_00508a78);
            v1 = dsll32(v0, 0);
            v1 = dsra32(v1, 0);
            v0 = s1 & 0x8;
            sd(v1, s2, 0);
            if (v0 == 0) {
                // 0x004c09e4
                charge(ctx, 6);
                lw(a0, s2, 96);
                a1 = 0;
                a2 = 0;
                jal(ctx, 0x4C09ECu, gen::fn_sceLseek_00508a78);
                sd(zero, s2, 16);
                backedge(ctx);
            } else {
                // 0x004c09b0
                charge(ctx, 2);
                ld(v0, s2, 0);
                sd(v0, s2, 16);
            }
            // 0x004c09b8
            charge(ctx, 3);
            v0 = s1 & 0x10;
            if (v0 != 0) {
                // 0x004c09fc
                charge(ctx, 9);
                link(ctx, 0x4C09FCu);  // $ra first: the delay slot below depends on it
                lw(a0, s2, 96);
                call(ctx, gen::fn_sceClose_00508900);
                a1 = s0 | 0x8000;
                a0 = addiu(sp, 0x50);
                jal(ctx, 0x4C0A08u, gen::fn_sceOpen_00508670);
                sw(v0, s2, 96);
                lw(v0, s2, 96);
                if (i64(v0) >= 0) {
                    // 0x004c0a20
                    charge(ctx, 5);
                    v1 = 1;
                    v0 = 3;
                    sw(v1, s2, 48);
                    sw(v0, s2, 56);
                    backedge(ctx);
                    goto L_004c09c4;
                }
                // 0x004c0a34
                charge(ctx, 2);
                v0 = 3;
                // 0x004c0a48 (the shared epilogue, written out on this path)
                charge(ctx, 7);
                ld(ra, sp, 0x40);
                lq(s3, sp, 0x30);
                lq(s2, sp, 0x20);
                lq(s1, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x150);
                return;
            }
        L_004c09c4:
            charge(ctx, 5);
            lw(v0, s2, 108);
            sw(v0, s2, 100);
            lw(v0, s2, 48);
            if (v0 == 0) {
                // 0x004c0a3c
                charge(ctx, 3);
                v0 = 2;
                sw(v0, s2, 56);
                backedge(ctx);
            }
            // 0x004c09d8
            charge(ctx, 3);
            v0 = 1;
            sw(v0, s2, 60);
        } else {
            // 0x004c096c
            charge(ctx, 2);
            v0 = 3;
        }
    }
    // 0x004c0a48 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x150);
}

// 0x004C0A70 sub_4C0A70 -- 16 bytes; leaf frame (no stack)
// File-system device close: sceClose on the record's descriptor.
void sub_4C0A70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x004c0a70
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 1;
    sw(v0, a0, 56);
    lw(a0, a0, 96);
    gen::fn_sceClose_00508900(ctx);  // tail call
}

// 0x004C0A80 sub_4C0A80 -- 452 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// File-system device read: clamps the length to the file size, reads with sceRead (or memcpy from a memory image) and
// advances the position.
void sub_4C0A80(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c0a80
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    s2 = a1;
    sq(s0, sp, 0x0);
    s1 = a2;
    ld(a1, a0, 16);
    ld(v1, a0, 0);
    sd(a1, a0, 32);
    lw(v0, a0, 48);
    s0 = 0;
    if (v0 != 0) {
        // 0x004c0ba4
        charge(ctx, 3);
        v0 = 5;
        sw(v0, s3, 64);
        backedge(ctx);
    }
    // 0x004c0abc
    charge(ctx, 8);
    v0 = dsll32(a1, 0);
    v0 = dsra32(v0, 0);
    v0 = addu(v0, s1);
    v0 = dsll32(v0, 0);
    v0 = dsrl32(v0, 0);
    at = slt(v1, v0);
    if (at != 0) {
        // 0x004c0adc
        charge(ctx, 3);
        v0 = v1 - a1;
        s1 = dsll32(v0, 0);
        s1 = dsra32(s1, 0);
    }
    // 0x004c0ae8
    charge(ctx, 2);
    if (s1 == 0) {
        // 0x004c0bb0
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004c0af0
        charge(ctx, 3);
        lw(v0, s3, 48);
        if (v0 != 0) {
            // 0x004c0bb8
            charge(ctx, 6);
            lw(a0, s3, 96);
            a1 = s2;
            a2 = s1;
            jal(ctx, 0x4C0BC0u, gen::fn_sceRead_00508cb8);
            if (i64(v0) < 0) {
                // 0x004c0bf4
                charge(ctx, 2);
                v0 = 0;
            } else {
                // 0x004c0bd0
                charge(ctx, 9);
                v0 = 3;
                a0 = dsll32(s1, 0);
                sw(v0, s3, 56);
                a0 = dsrl32(a0, 0);
                ld(v1, s3, 16);
                v0 = s1;
                v1 = v1 + a0;
                sd(v1, s3, 16);
            }
        } else {
            // 0x004c0afc
            charge(ctx, 5);
            lw(v0, s3, 108);
            lw(v1, s3, 100);
            at = slt(v1, v0);
            if (at != 0) {
                // 0x004c0b10
                charge(ctx, 4);
                s0 = subu(v0, v1);
                at = sltu(s1, s0);
                if (at != 0) {
                    // 0x004c0b20
                    charge(ctx, 1);
                    s0 = s1;
                }
                // 0x004c0b24
                charge(ctx, 9);
                lw(v0, s3, 104);
                a0 = s2;
                a2 = s0;
                a1 = addu(v0, v1);
                jal(ctx, 0x4C0B30u, gen::fn_memcpy_00521250);
                lw(v0, s3, 100);
                s2 = addu(s2, s0);
                v0 = addu(v0, s0);
                sw(v0, s3, 100);
            }
            // 0x004c0b48
            charge(ctx, 3);
            s1 = subu(s1, s0);
            if (s1 != 0) {
                // 0x004c0b54
                charge(ctx, 6);
                v0 = 3;
                sw(v0, s3, 56);
                lw(a2, s3, 108);
                v0 = slt(s1, a2);
                if (v0 != 0) {
                    // 0x004c0bfc
                    charge(ctx, 11);
                    lw(a1, s3, 104);
                    link(ctx, 0x4C0C00u);  // $ra first: the delay slot below depends on it
                    lw(a0, s3, 96);
                    call(ctx, gen::fn_sceRead_00508cb8);
                    sw(s1, s3, 100);
                    a0 = s2;
                    lw(a2, s3, 100);
                    lw(a1, s3, 104);
                    s0 = addu(s0, a2);
                    jal(ctx, 0x4C0C18u, gen::fn_memcpy_00521250);
                    v0 = 2;
                    backedge(ctx);
                } else {
                    // 0x004c0b6c
                    charge(ctx, 6);
                    lw(a0, s3, 96);
                    a1 = s2;
                    a2 = s1;
                    jal(ctx, 0x4C0B74u, gen::fn_sceRead_00508cb8);
                    s0 = addu(s0, v0);
                    v0 = 2;
                }
                // 0x004c0b84
                charge(ctx, 1);
                sw(v0, s3, 56);
            }
            // 0x004c0b88
            charge(ctx, 7);
            ld(v1, s3, 16);
            a0 = dsll32(s0, 0);
            a0 = dsra32(a0, 0);
            v0 = s0;
            v1 = v1 + a0;
            sd(v1, s3, 16);
        }
    }
    // 0x004c0c28 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x004C0C50 sub_4C0C50 -- 160 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// File-system device write: sceWrite.
void sub_4C0C50(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c0c50
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = 3;
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    sw(v0, a0, 56);
    lw(a0, a0, 96);
    s1 = a2;
    jal(ctx, 0x4C0C70u, gen::fn_sceWrite_00508f28);
    lw(v1, s0, 48);
    if (v1 != 0) {
        // 0x004c0c84
        charge(ctx, 2);
        if (i64(v0) < 0) {
            // 0x004c0c8c
            charge(ctx, 1);
            s1 = 0;
        }
        // 0x004c0c90
        charge(ctx, 1);
        v0 = s1;
    }
    // 0x004c0c94
    charge(ctx, 3);
    v1 = 2;
    sw(v1, s0, 56);
    if (i64(v0) <= 0) {
        // 0x004c0cd8
        charge(ctx, 2);
        v0 = 0;
        ld(ra, sp, 0x20);
    } else {
        // 0x004c0ca0
        charge(ctx, 10);
        ld(v1, s0, 16);
        a0 = dsll32(v0, 0);
        a0 = dsra32(a0, 0);
        v1 = v1 + a0;
        sd(v1, s0, 16);
        ld(a0, s0, 16);
        ld(v1, s0, 0);
        at = slt(v1, a0);
        if (at != 0) {
            // 0x004c0cd0
            charge(ctx, 2);
            sd(a0, s0, 0);
            backedge(ctx);
        }
        // 0x004c0cc8
        charge(ctx, 2);
        ld(ra, sp, 0x20);
    }
    // 0x004c0ce0 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x004C0CF0 sub_4C0CF0 -- 372 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// File-system device seek: sceLseek with the record's position bookkeeping (sub_4BFB20).
void sub_4C0CF0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c0cf0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v1 = 3;
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    ld(t0, a1, 16);
    ld(a0, a1, 0);
    s0 = a1;
    if (a3 == v1) {
        // 0x004c0d54
        charge(ctx, 4);
        v0 = dsll32(a2, 0);
        v0 = dsra32(v0, 0);
        a3 = a0 - v0;
    L_004c0d74:
        charge(ctx, 3);
        at = slt(a0, a3);
        if (at == 0) {
            // 0x004c0d88
            charge(ctx, 2);
            if (i64(a3) < 0) {
                // 0x004c0d90
                charge(ctx, 1);
                a3 = 0;
            }
        } else {
            // 0x004c0d80
            charge(ctx, 2);
            a3 = a0;
        }
        // 0x004c0d94
        charge(ctx, 5);
        lw(v0, s0, 108);
        lw(v1, s0, 100);
        at = slt(v1, v0);
        if (at != 0) {
            // 0x004c0da8
            charge(ctx, 10);
            v0 = subu(v0, v1);
            v1 = dsll32(v1, 0);
            v0 = dsll32(v0, 0);
            v1 = dsra32(v1, 0);
            v0 = dsra32(v0, 0);
            a0 = t0 - v1;
            v1 = t0 + v0;
            v0 = slt(a3, a0);
            if (v0 != 0) {
                goto L_004c0e04;
            }
            // 0x004c0dd0
            charge(ctx, 3);
            at = slt(v1, a3);
            if (at != 0) {
                goto L_004c0e04;
            }
            // 0x004c0ddc
            charge(ctx, 10);
            v0 = a3 - a0;
            v0 = dsll32(v0, 0);
            a0 = s0;
            v0 = dsra32(v0, 0);
            sw(v0, s0, 100);
            link(ctx, 0x4C0DF0u);  // $ra first: the delay slot below depends on it
            sd(a3, s0, 16);
            call(ctx, gen::fn_sub_4BFB20_004bfb20);
            lq(v1, s0, 16);
            sq(v1, s1, 0);
            // 0x004c0e50 (the shared epilogue, written out on this path)
            charge(ctx, 5);
            ld(ra, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x40);
            return;
        }
    L_004c0e04:
        charge(ctx, 13);
        v0 = 3;
        a1 = dsll32(a3, 0);
        sw(v0, s0, 56);
        a1 = dsra32(a1, 0);
        lw(v0, s0, 108);
        sw(v0, s0, 100);
        sd(a3, s0, 16);
        lw(a0, s0, 96);
        a2 = 0;
        jal(ctx, 0x4C0E24u, gen::fn_sceLseek_00508a78);
        lw(v1, s0, 48);
        if (v1 == 0) {
            // 0x004c0e44
            charge(ctx, 3);
            v1 = 2;
            sw(v1, s0, 56);
            backedge(ctx);
        }
        // 0x004c0e38
        charge(ctx, 3);
        lq(v1, s0, 16);
        sq(v1, s1, 0);
    } else {
        // 0x004c0d18
        charge(ctx, 3);
        v1 = 2;
        if (a3 == v1) {
            // 0x004c0d44
            charge(ctx, 4);
            v0 = dsll32(a2, 0);
            v0 = dsra32(v0, 0);
            a3 = t0 + v0;
            goto L_004c0d74;
        }
        // 0x004c0d24
        charge(ctx, 3);
        v1 = 1;
        if (a3 == v1) {
            // 0x004c0d38
            charge(ctx, 3);
            a3 = dsll32(a2, 0);
            a3 = dsra32(a3, 0);
            goto L_004c0d74;
        }
        // 0x004c0d30
        charge(ctx, 2);
        v1 = si(-1);
        // 0x004c0d64
        charge(ctx, 4);
        sd(v1, sp, 0x30);
        lq(v1, sp, 0x30);
        sq(v1, s1, 0);
    }
    // 0x004c0e50 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x004C0E70 sub_4C0E70 -- 236 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// File-system device ioctl: sceIoctl on the record's descriptor (sub_4BFB20 resolves it).
void sub_4C0E70(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c0e70
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v0 = 3;
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    s1 = a1;
    lw(v1, a0, 56);
    s0 = 2;
    if (v1 == v0) {
        // 0x004c0e9c
        charge(ctx, 4);
        lw(v1, s2, 64);
        v0 = 4;
        if (v1 != v0) {
            for (;;) {
                // 0x004c0ed0
                charge(ctx, 7);
                lw(a0, s2, 96);
                a1 = 1;
                a2 = addiu(sp, 0x4C);
                jal(ctx, 0x4C0ED8u, gen::fn_sceIoctl_005091e8);
                lw(v0, sp, 0x4C);
                if (v0 == 0) {
                    // 0x004c0ef8
                    charge(ctx, 6);
                    s0 = 2;
                    sw(s0, s2, 56);
                    v0 = 5;
                    lw(v1, s2, 64);
                    if (v1 == v0) {
                        // 0x004c0f10
                        charge(ctx, 6);
                        ld(v1, s2, 16);
                        ld(v0, s2, 32);
                        v0 = v1 - v0;
                        v0 = dsll32(v0, 0);
                        v0 = dsra32(v0, 0);
                        sw(v0, s2, 68);
                    }
                } else {
                    // 0x004c0eec
                    charge(ctx, 3);
                    sw(zero, s2, 68);
                    s0 = 3;
                }
                // 0x004c0f28
                charge(ctx, 2);
                if (s1 == 0) {
                    backedge(ctx);
                    goto L_004c0eb0;
                }
                // 0x004c0f30
                charge(ctx, 3);
                v0 = 3;
                if (s0 != v0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004c0f3c
            charge(ctx, 2);
            lw(v1, s2, 56);
            backedge(ctx);
        } else {
            // 0x004c0eac
            charge(ctx, 1);
            sw(s0, s2, 56);
        L_004c0eb0:
            charge(ctx, 1);
            lw(v1, s2, 56);
        }
        // 0x004c0eb4
        charge(ctx, 3);
        v0 = 2;
        if (v1 == v0) {
            // 0x004c0ec0
            charge(ctx, 2);
            a0 = s2;
            jal(ctx, 0x4C0EC0u, gen::fn_sub_4BFB20_004bfb20);
        }
    }
    // 0x004c0ec8
    charge(ctx, 2);
    v0 = s0;
    // 0x004c0f44
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x004C72E0 _dispRefImageField_0 -- 280 bytes; leaf frame (no stack)
// Fills the C-string function table at 0x960134 (sprintf, vsprintf, strcpy, ..., strlen). Leaf.
void _dispRefImageField_0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x004c72e0
    enter(ctx, 70);  // entry check point + this block's cycles
    a0 = 0x520000;
    v1 = 0x530000;
    a0 = addiu(a0, 15048);  // &sprintf
    v0 = 0x960000;
    sw(a0, v0, 308);  // 0x960134
    v1 = addiu(v1, -30520);  // &vsprintf
    v0 = 0x960000;
    a0 = 0x520000;
    sw(v1, v0, 312);  // 0x960138
    a0 = addiu(a0, 17008);  // &strcpy
    v0 = 0x960000;
    v1 = 0x520000;
    sw(a0, v0, 316);  // 0x96013C
    v1 = addiu(v1, 18472);  // &strncpy
    v0 = 0x960000;
    a0 = 0x520000;
    sw(v1, v0, 320);  // 0x960140
    a0 = addiu(a0, 15976);  // &strcat
    v0 = 0x960000;
    v1 = 0x520000;
    sw(a0, v0, 324);  // 0x960144
    v1 = addiu(v1, 17600);  // &strncat
    v0 = 0x960000;
    a0 = 0x4C0000;
    sw(v1, v0, 328);  // 0x960148
    a0 = addiu(a0, 29344);  // &sub_4C72A0
    v0 = 0x960000;
    v1 = 0x4C0000;
    sw(a0, v0, 332);  // 0x96014C
    v1 = addiu(v1, 29280);  // &sub_4C7260
    v0 = 0x960000;
    a0 = 0x520000;
    sw(v1, v0, 336);  // 0x960150
    a0 = addiu(a0, 19024);  // &strstr
    v0 = 0x960000;
    v1 = 0x520000;
    sw(a0, v0, 340);  // 0x960154
    v1 = addiu(v1, 16680);  // &strcmp
    v0 = 0x960000;
    a0 = 0x520000;
    sw(v1, v0, 344);  // 0x960158
    a0 = addiu(a0, 18032);  // &strncmp
    v0 = 0x960000;
    v1 = 0x4C0000;
    sw(a0, v0, 348);  // 0x96015C
    v1 = addiu(v1, 28928);  // &sub_4C7100
    v0 = 0x960000;
    a0 = 0x520000;
    sw(v1, v0, 352);  // 0x960160
    a0 = addiu(a0, 17288);  // &strlen
    v0 = 0x960000;
    v1 = 0x4C0000;
    sw(a0, v0, 356);  // 0x960164
    v1 = addiu(v1, 29120);  // &sub_4C71C0
    v0 = 0x960000;
    a0 = 0x4C0000;
    sw(v1, v0, 360);  // 0x960168
    a0 = addiu(a0, 29200);  // &sub_4C7210
    v0 = 0x960000;
    v1 = 0x520000;
    sw(a0, v0, 364);  // 0x96016C
    v1 = addiu(v1, 22872);  // &strtok
    v0 = 0x960000;
    a0 = 0x520000;
    sw(v1, v0, 368);  // 0x960170
    a0 = addiu(a0, 15168);  // &sscanf
    v1 = 0x960000;
    v0 = 1;
    sw(a0, v1, 372);  // 0x960174
}

// 0x004D4350 _rwDMAHandler -- 1184 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// RW Sky DMA interrupt handler: completes the finished packet, starts the next queued one on the DMA channel, calls
// the packet's callback through $jalr.
void _rwDMAHandler(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004d4350
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v0 = si(-1);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    s2 = 0;
    sq(s0, sp, 0x0);
    if (s3 != v0) {
        // 0x004d4378
        charge(ctx, 3);
        v0 = addiu(gp, -17272);  // &0x7CE978
        s2 = gp & gp;
        lw(gp, v0, 0);  // 0x7CE978
    }
    // 0x004d4384
    charge(ctx, 4);
    v0 = addiu(s3, -1);
    at = sltiu(v0, 2);
    if (at != 0) {
        // 0x004d4394
        charge(ctx, 3);
        lbu(v0, gp, -17216);  // g_rwDMABusyCount
        if (v0 != 0) {
            // 0x004d43a0
            charge(ctx, 3);
            lbu(v0, gp, -17216);  // g_rwDMABusyCount
            v0 = addiu(v0, -1);
            sb(v0, gp, -17216);  // g_rwDMABusyCount
        }
    }
    // 0x004d43ac
    charge(ctx, 5);
    v1 = 0x6000000;
    v0 = nor(s3, 0);
    s0 = v1 | 0x8000;
    s1 = sltu(0, v0);
    for (;;) {
        // 0x004d478c
        charge(ctx, 3);
        lbu(v0, gp, -17216);  // g_rwDMABusyCount
        if (v0 == 0) {
            // 0x004d4798
            charge(ctx, 4);
            lw(v1, gp, -17232);  // 0x7CE9A0
            lw(v0, gp, -17236);  // g_rwDMAQueueRead
            if (v1 != v0) {
                // 0x004d47a8
                charge(ctx, 3);
                lbu(v0, gp, -17220);  // g_rwDMAFlipPending
                if (v0 != 0) {
                    goto L_004d47b4_43;
                }
                backedge(ctx);
                // 0x004d43c0
                charge(ctx, 5);
                lw(a1, v1, 0);
                v0 = 67;
                a0 = a1 & 0xFF;
                if (a0 != v0) {
                    // 0x004d43d4
                    charge(ctx, 3);
                    v0 = 79;
                    if (a0 == v0) {
                        // 0x004d4768
                        charge(ctx, 6);
                        lw(v0, v1, 4);
                        a0 = s1;
                        jalr(ctx, 0x4D476Cu, v0.u());
                        v0 = sltu(0, v0);
                        v0 = v0 ^ 0x1;
                        sb(v0, gp, -17216);  // g_rwDMABusyCount
                        goto L_004d4780;
                    }
                    // 0x004d43e0
                    charge(ctx, 3);
                    v0 = 65;
                    if (a0 == v0) {
                        // 0x004d4744
                        charge(ctx, 9);
                        lw(v1, v1, 4);
                        v0 = 1;
                        sb(v0, gp, -17224);  // g_rwDMAFlipBuf
                        sb(v0, gp, -17220);  // g_rwDMAFlipPending
                        lbu(v0, gp, -17248);  // 0x7CE990
                        sw(v1, gp, -17228);  // g_rwDMAFlipData
                        v0 = addiu(v0, -1);
                        sb(v0, gp, -17248);  // 0x7CE990
                        goto L_004d4780;
                    }
                    // 0x004d43ec
                    charge(ctx, 3);
                    v0 = 64;
                    if (a0 == v0) {
                        // 0x004d4720
                        charge(ctx, 9);
                        lw(v1, v1, 4);
                        v0 = 1;
                        sb(v0, gp, -17220);  // g_rwDMAFlipPending
                        lbu(v0, gp, -17248);  // 0x7CE990
                        sw(v1, gp, -17228);  // g_rwDMAFlipData
                        sb(zero, gp, -17224);  // g_rwDMAFlipBuf
                        v0 = addiu(v0, -1);
                        sb(v0, gp, -17248);  // 0x7CE990
                        goto L_004d4780;
                    }
                    // 0x004d43f8
                    charge(ctx, 3);
                    v0 = 66;
                    if (a0 == v0) {
                        // 0x004d46e0
                        charge(ctx, 5);
                        v0 = 0xFFF0000;
                        v0 = v0 | 0xF000;
                        v0 = a1 & v0;
                        if (v0 == 0) {
                            // 0x004d470c
                            charge(ctx, 5);
                            lw(v1, v1, 4);
                            lw(v0, v1, 0);
                            v0 = addiu(v0, -1);
                            sw(v0, v1, 0);
                        } else {
                            // 0x004d46f4
                            charge(ctx, 6);
                            lw(a0, v1, 4);
                            v0 = srl(v0, 12);
                            lw(v1, a0, 0);
                            v0 = subu(v1, v0);
                            sw(v0, a0, 0);
                        }
                        goto L_004d4780;
                    }
                    // 0x004d4404
                    charge(ctx, 3);
                    v0 = 127;
                    if (a0 == v0) {
                        // 0x004d46d4
                        charge(ctx, 3);
                        lw(v0, v1, 4);
                        sw(v0, gp, -17232);  // 0x7CE9A0
                    } else {
                        // 0x004d4410
                        charge(ctx, 3);
                        v0 = 1;
                        if (a0 == v0) {
                            // 0x004d4658
                            charge(ctx, 3);
                            v0 = a1 & 0x300;
                            if (v0 == 0) {
                                // 0x004d4690
                                charge(ctx, 12);
                                lw(a1, v1, 4);
                                v0 = 0x10010000;
                                a0 = 0xFFF0000;
                                a0 = a0 | 0xF000;
                                sw(a1, v0, -28656);  // 0x10009010 D1 VIF1 MADR
                                v1 = 257;
                                lw(a1, gp, -17232);  // 0x7CE9A0
                                lw(a1, a1, 0);
                                a0 = a1 & a0;
                                a0 = srl(a0, 12);
                                sw(a0, v0, -28640);  // 0x10009020 D1 VIF1 QWC
                                sw(v1, v0, -28672);  // 0x10009000 D1 VIF1 CHCR
                            } else {
                                // 0x004d4664
                                charge(ctx, 11);
                                lw(v1, v1, 4);
                                v0 = 0x10010000;
                                sw(v1, v0, -28624);  // 0x10009030 D1 VIF1 TADR
                                sw(zero, v0, -28640);  // 0x10009020 D1 VIF1 QWC
                                lw(v1, gp, -17232);  // 0x7CE9A0
                                lw(v1, v1, 0);
                                v1 = v1 & 0x1300;
                                v1 = srl(v1, 6);
                                v1 = v1 | 0x101;
                                sw(v1, v0, -28672);  // 0x10009000 D1 VIF1 CHCR
                            }
                            // 0x004d46c0
                            charge(ctx, 5);
                            sync(ctx, 0);
                            lbu(v0, gp, -17216);  // g_rwDMABusyCount
                            v0 = addiu(v0, 1);
                            sb(v0, gp, -17216);  // g_rwDMABusyCount
                            goto L_004d4780;
                        }
                        // 0x004d441c
                        charge(ctx, 3);
                        v0 = 2;
                        if (a0 == v0) {
                            for (;;) {
                                // 0x004d4564
                                charge(ctx, 29);
                                v1 = 0x1F000000;
                                a0 = 0x10000000;
                                t1 = v1 | 0x3;
                                lw(t3, a0, 12320);  // 0x10003020 GIF_STAT
                                v1 = 0x10010000;
                                lw(t2, a0, 15360);  // 0x10003C00 VIF1_STAT
                                lw(a3, v1, -28672);  // 0x10009000 D1 VIF1 CHCR
                                a1 = 2;
                                lw(a2, v1, -24576);  // 0x1000A000 D2 GIF CHCR
                                v0 = 16;
                                t0 = 4;
                                t3 = t3 & 0xC00;
                                t1 = t2 & t1;
                                if (t3 == 0) v0 = 0;
                                a3 = a3 & 0x100;
                                if (t1 == 0) t0 = 0;
                                a2 = a2 & 0x100;
                                a3 = sltu(0, a3);
                                if (a2 == 0) a1 = 0;
                                cfc2(a2, 29, false);  // cfc2
                                a1 = a3 | a1;
                                a3 = a2 & 0x100;
                                a1 = t0 | a1;
                                a2 = 8;
                                if (a3 == 0) a2 = 0;
                                a1 = a1 | a2;
                                v0 = v0 | a1;
                                if (v0 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004d45d8
                            charge(ctx, 6);
                            sw(zero, a0, 12304);
                            lw(a0, gp, -17232);  // 0x7CE9A0
                            lw(v0, a0, 0);
                            v0 = v0 & 0x300;
                            if (v0 == 0) {
                                // 0x004d4618
                                charge(ctx, 11);
                                lw(a1, a0, 4);
                                v0 = 0xFFF0000;
                                sw(a1, v1, -24560);
                                a0 = v0 | 0xF000;
                                lw(a1, gp, -17232);  // 0x7CE9A0
                                v0 = 256;
                                lw(a1, a1, 0);
                                a0 = a1 & a0;
                                a0 = srl(a0, 12);
                                sw(a0, v1, -24544);
                                sw(v0, v1, -24576);
                            } else {
                                // 0x004d45f0
                                charge(ctx, 10);
                                lw(v0, a0, 4);
                                sw(v0, v1, -24528);
                                sw(zero, v1, -24544);
                                lw(v0, gp, -17232);  // 0x7CE9A0
                                lw(v0, v0, 0);
                                v0 = v0 & 0x1300;
                                v0 = srl(v0, 6);
                                v0 = v0 | 0x100;
                                sw(v0, v1, -24576);
                            }
                            // 0x004d4644
                            charge(ctx, 5);
                            sync(ctx, 0);
                            lbu(v0, gp, -17216);  // g_rwDMABusyCount
                            v0 = addiu(v0, 1);
                            sb(v0, gp, -17216);  // g_rwDMABusyCount
                            goto L_004d4780;
                        }
                        // 0x004d4428
                        charge(ctx, 3);
                        v0 = 33;
                        if (a0 == v0) {
                            for (;;) {
                                // 0x004d4440
                                charge(ctx, 29);
                                v1 = 0x1F000000;
                                t0 = v1 | 0x3;
                                a0 = 0x10000000;
                                v1 = 0x10010000;
                                lw(t2, a0, 12320);  // 0x10003020 GIF_STAT
                                lw(t1, a0, 15360);  // 0x10003C00 VIF1_STAT
                                a3 = 4;
                                lw(a2, v1, -28672);  // 0x10009000 D1 VIF1 CHCR
                                a1 = 2;
                                v0 = 16;
                                t2 = t2 & 0xC00;
                                t0 = t1 & t0;
                                if (t2 == 0) v0 = 0;
                                lw(v1, v1, -24576);  // 0x1000A000 D2 GIF CHCR
                                a2 = a2 & 0x100;
                                if (t0 == 0) a3 = 0;
                                a2 = sltu(0, a2);
                                v1 = v1 & 0x100;
                                if (v1 == 0) a1 = 0;
                                cfc2(t0, 29, false);  // cfc2
                                v1 = a2 | a1;
                                a2 = t0 & 0x100;
                                a1 = 8;
                                v1 = a3 | v1;
                                if (a2 == 0) a1 = 0;
                                v1 = v1 | a1;
                                v0 = v0 | v1;
                                if (v0 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004d44b4
                            charge(ctx, 4);
                            v0 = 0;
                            pcpyld(v0, v0, s0);
                            sq(v0, a0, 20480);
                            sync(ctx, 0);
                            for (;;) {
                                // 0x004d44c4
                                charge(ctx, 7);
                                lw(v0, a0, 12320);
                                v0 = v0 & 0x2;
                                v0 = sltu(0, v0);
                                v0 = v0 ^ 0x1;
                                if (v0 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004d44e0
                            charge(ctx, 16);
                            v1 = 4;
                            v0 = 0x10010000;
                            sw(v1, a0, 12304);
                            lw(a0, gp, -17232);  // 0x7CE9A0
                            v1 = 260;
                            lw(a0, a0, 12);
                            sw(a0, v0, -24528);  // 0x1000A030 D2 GIF TADR
                            sw(zero, v0, -24544);  // 0x1000A020 D2 GIF QWC
                            sw(v1, v0, -24576);  // 0x1000A000 D2 GIF CHCR
                            lw(v1, gp, -17232);  // 0x7CE9A0
                            lw(v1, v1, 4);
                            sw(v1, v0, -28624);  // 0x10009030 D1 VIF1 TADR
                            sw(zero, v0, -28640);  // 0x10009020 D1 VIF1 QWC
                            sync(ctx, 0);
                            v0 = 0x10000000;
                            a0 = 0x1F000000;
                            for (;;) {
                                // 0x004d4520
                                charge(ctx, 7);
                                lw(v1, v0, 12320);
                                v1 = v1 & a0;
                                v1 = sltu(0, v1);
                                v1 = v1 ^ 0x1;
                                if (v1 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004d453c
                            charge(ctx, 10);
                            v1 = 325;
                            v0 = 0x10010000;
                            sw(v1, v0, -28672);  // 0x10009000 D1 VIF1 CHCR
                            lw(v1, gp, -17232);  // 0x7CE9A0
                            lbu(v0, gp, -17216);  // g_rwDMABusyCount
                            v1 = addiu(v1, 8);
                            v0 = addiu(v0, 2);
                            sw(v1, gp, -17232);  // 0x7CE9A0
                            sb(v0, gp, -17216);  // g_rwDMABusyCount
                            goto L_004d4780;
                        }
                        // 0x004d4434
                        charge(ctx, 2);
                        lw(v0, gp, -17232);  // 0x7CE9A0
                    L_004d4784:
                        charge(ctx, 2);
                        v0 = addiu(v0, 8);
                        sw(v0, gp, -17232);  // 0x7CE9A0
                    }
                    continue;
                }
            L_004d4780:
                charge(ctx, 1);
                lw(v0, gp, -17232);  // 0x7CE9A0
                goto L_004d4784;
            }
        }
        break;
    }
L_004d47b8:
    charge(ctx, 3);
    v0 = si(-1);
    if (s3 != v0) {
        // 0x004d47c4
        charge(ctx, 3);
        gp = s2 & s2;
        sync(ctx, 0);
        ei(ctx);
    }
    // 0x004d47d0 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    v0 = si(-1);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
    return;
L_004d47b4_43:
    charge(ctx, 1);
    goto L_004d47b8;
}

// 0x004D47F0 _rwDMAVSYNCHandler -- 616 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// RW Sky VSYNC interrupt handler: flips the display buffers (sceGsPutDispEnv) when a flip is pending, then kicks the
// DMA handler.
void _rwDMAVSYNCHandler(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004d47f0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = addiu(gp, -17272);  // &0x7CE978
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = gp & gp;
    lw(gp, v0, 0);  // 0x7CE978
    lbu(v1, gp, -17296);
    lbu(v0, gp, -17256);
    at = slt(v0, v1);
    if (at == 0) {
        // 0x004d4850
        charge(ctx, 3);
        v0 = 2;
        if (a0 == v0) {
            // 0x004d485c
            charge(ctx, 3);
            lbu(v0, gp, -17220);  // g_rwDMAFlipPending
            if (v0 != 0) {
                // 0x004d4868
                charge(ctx, 10);
                v0 = 1;
                sb(zero, gp, -17220);  // g_rwDMAFlipPending
                sb(v0, gp, -17256);  // 0x7CE988
                v0 = 0x12000000;
                ld(v0, v0, 4096);  // 0x12001000 GS CSR
                v0 = dsrl(v0, 12);
                v0 = v0 & 0x2;
                s0 = v0 & 0xFF;
                lw(s1, gp, -17228);  // g_rwDMAFlipData
                if (s0 == 0) {
                    // 0x004d48b8
                    charge(ctx, 8);
                    lbu(v0, gp, -17224);  // g_rwDMAFlipBuf
                    v1 = v0 & 0x1;
                    v0 = sll(v1, 2);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 3);
                    a0 = addu(s1, v0);
                    jal(ctx, 0x4D48CCu, gen::fn_sceGsPutDispEnv_004f94e0);
                    lbu(v0, gp, -17224);  // g_rwDMAFlipBuf
                } else {
                    // 0x004d4890
                    charge(ctx, 10);
                    lbu(v0, gp, -17224);  // g_rwDMAFlipBuf
                    v1 = v0 & 0x1;
                    v0 = sll(v1, 2);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 3);
                    v0 = addu(s1, v0);
                    a0 = addiu(v0, 848);
                    jal(ctx, 0x4D48A8u, gen::fn_sceGsPutDispEnv_004f94e0);
                    lbu(v0, gp, -17224);  // g_rwDMAFlipBuf
                }
                // 0x004d48d8
                charge(ctx, 2);
                if (v0 == 0) {
                    // 0x004d4918
                    charge(ctx, 2);
                    if (s0 == 0) {
                        // 0x004d4938
                        charge(ctx, 5);
                        ld(a0, s1, 816);
                        v1 = 0x12000000;
                        sd(a0, v1, 112);  // 0x12000070 GS DISPFB1
                        ld(a0, s1, 824);
                        sd(a0, v1, 128);  // 0x12000080 GS DISPLAY1
                    } else {
                        // 0x004d4920
                        charge(ctx, 6);
                        ld(a0, s1, 928);
                        v1 = 0x12000000;
                        sd(a0, v1, 112);  // 0x12000070 GS DISPFB1
                        ld(a0, s1, 936);
                        sd(a0, v1, 128);  // 0x12000080 GS DISPLAY1
                    }
                } else {
                    // 0x004d48e0
                    charge(ctx, 2);
                    if (s0 == 0) {
                        // 0x004d4900
                        charge(ctx, 6);
                        ld(a0, s1, 832);
                        v1 = 0x12000000;
                        sd(a0, v1, 112);  // 0x12000070 GS DISPFB1
                        ld(a0, s1, 840);
                        sd(a0, v1, 128);  // 0x12000080 GS DISPLAY1
                    } else {
                        // 0x004d48e8
                        charge(ctx, 6);
                        ld(a0, s1, 944);
                        v1 = 0x12000000;
                        sd(a0, v1, 112);  // 0x12000070 GS DISPFB1
                        ld(a0, s1, 952);
                        sd(a0, v1, 128);  // 0x12000080 GS DISPLAY1
                    }
                }
                // 0x004d494c
                charge(ctx, 3);
                lbu(v1, gp, -17240);  // g_rwDMAFsaaEnabled
                if (v1 != 0) {
                    // 0x004d4958
                    charge(ctx, 2);
                    if (s0 == 0) {
                        // 0x004d4968
                        charge(ctx, 2);
                        v1 = 1;
                        sb(v1, gp, -17244);  // 0x7CE994
                    } else {
                        // 0x004d4960
                        charge(ctx, 2);
                        sb(zero, gp, -17244);  // 0x7CE994
                    }
                    // 0x004d4970
                    charge(ctx, 2);
                    if (v0 == 0) {
                        // 0x004d49ac
                        charge(ctx, 12);
                        lw(v1, s1, 132);
                        a0 = s0 & 0xFF;
                        a1 = a0 ^ 0x2;
                        a0 = si(-9);
                        a1 = sll(a1, 2);
                        v1 = v1 & a0;
                        v1 = v1 | a1;
                        sw(v1, s1, 132);
                        lw(v1, s1, 260);
                        v1 = v1 & a0;
                        v1 = v1 | a1;
                        sw(v1, s1, 260);
                    } else {
                        // 0x004d4978
                        charge(ctx, 13);
                        lw(v1, s1, 500);
                        a0 = s0 & 0xFF;
                        a1 = a0 ^ 0x2;
                        a0 = si(-9);
                        a1 = sll(a1, 2);
                        v1 = v1 & a0;
                        v1 = v1 | a1;
                        sw(v1, s1, 500);
                        lw(v1, s1, 628);
                        v1 = v1 & a0;
                        v1 = v1 | a1;
                        sw(v1, s1, 628);
                    }
                }
                // 0x004d49dc
                charge(ctx, 9);
                v1 = v0 & 0xFF;
                v0 = s0 & 0xFF;
                v1 = v1 & 0x1;
                v0 = v1 | v0;
                v0 = sll(v0, 2);
                v0 = addu(v0, s1);
                lw(a0, v0, 960);
                if (a0 == 0) {
                    // 0x004d4a28
                    charge(ctx, 2);
                    a0 = si(-1);
                    jal(ctx, 0x4D4A28u, gen::fn__rwDMAHandler_004d4350);
                } else {
                    // 0x004d4a00
                    charge(ctx, 10);
                    v0 = 0x10010000;
                    v1 = 260;
                    sw(a0, v0, -24528);  // 0x1000A030 D2 GIF TADR
                    sw(zero, v0, -24544);  // 0x1000A020 D2 GIF QWC
                    sw(v1, v0, -24576);  // 0x1000A000 D2 GIF CHCR
                    sync(ctx, 0);
                    lbu(v0, gp, -17216);  // g_rwDMABusyCount
                    v0 = addiu(v0, 1);
                    sb(v0, gp, -17216);  // g_rwDMABusyCount
                }
            }
        }
        // 0x004d4a30
        charge(ctx, 4);
        gp = s2 & s2;
        sync(ctx, 0);
        ei(ctx);
        v0 = 0;
    } else {
        // 0x004d4824
        charge(ctx, 3);
        at = slti(v1, 255);
        if (at != 0) {
            // 0x004d4830
            charge(ctx, 3);
            lbu(v0, gp, -17256);  // 0x7CE988
            v0 = addiu(v0, 1);
            sb(v0, gp, -17256);  // 0x7CE988
        }
        // 0x004d483c
        charge(ctx, 5);
        gp = s2 & s2;
        sync(ctx, 0);
        ei(ctx);
        v0 = 0;
    }
    // 0x004d4a40 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x004D4A60 _rwDMAClosePkt -- 900 bytes; frame 0x10: ra sp+0x0
// Closes the currently open DMA packet: writes the end tag, queues it for the DMA handler.
void _rwDMAClosePkt(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004d4a60
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, gp, -17212);  // 0x7CE9B4
    if (a0 == 0) {
        // 0x004d4d2c
        charge(ctx, 4);
        lhu(a0, gp, -17264);  // 0x7CE980
        lhu(v1, gp, -17268);  // 0x7CE97C
        if (a0 != v1) {
            // 0x004d4d44
            charge(ctx, 4);
            jal(ctx, 0x4D4D44u, gen::fn_sub_4D4280_004d4280);
            backedge(ctx);
        }
        // 0x004d4d3c
        charge(ctx, 2);
        // 0x004d4dd8
        charge(ctx, 1);
        ld(ra, sp, 0x0);
    } else {
        // 0x004d4a74
        charge(ctx, 4);
        v1 = lui(0x8000);
        v1 = a0 & v1;
        if (v1 != 0) {
            // 0x004d4a84
            charge(ctx, 11);
            lw(a3, gp, -17204);  // 0x7CE9BC
            lw(a2, gp, -17128);  // 0x7CEA08
            lw(a0, gp, -17148);  // 0x7CE9F4
            lw(v1, gp, -17124);  // g_rwDMASprBase
            a1 = subu(a2, a3);
            v1 = subu(a0, v1);
            v1 = addu(a1, v1);
            v1 = srl(v1, 4);
            a1 = addiu(v1, -1);
            if (a1 == 0) {
                // 0x004d4d54
                charge(ctx, 3);
                v1 = addiu(a2, -16);
                sw(v1, gp, -17128);  // 0x7CEA08
                backedge(ctx);
            } else {
                // 0x004d4ab0
                charge(ctx, 13);
                a0 = 0x50000000;
                v1 = 0x10000000;
                a0 = a1 | a0;
                v1 = a1 | v1;
                a0 = dsll32(a0, 0);
                v1 = dsll32(v1, 0);
                a0 = dsrl32(a0, 0);
                v1 = dsrl32(v1, 0);
                a0 = dsll32(a0, 0);
                pcpyld(a0, a0, v1);
                v1 = 0x20000000;
                v1 = a3 | v1;
                sq(a0, v1, 0);
            }
            // 0x004d4ae4
            charge(ctx, 5);
            lw(v1, gp, -17212);  // 0x7CE9B4
            sw(zero, gp, -17204);  // 0x7CE9BC
            v1 = dsll32(v1, 1);
            v1 = dsrl32(v1, 1);
            sw(v1, gp, -17212);  // 0x7CE9B4
        }
        // 0x004d4af8
        charge(ctx, 3);
        lw(a1, gp, -17152);  // 0x7CE9F0
        if (a1 == 0) {
            // 0x004d4d60
            charge(ctx, 9);
            a0 = 0x6000000;
            v1 = 0x70000000;
            pcpyld(a0, a0, v1);
            lw(v1, gp, -17148);  // 0x7CE9F4
            sq(a0, v1, 0);
            lw(v1, gp, -17148);  // 0x7CE9F4
            v1 = addiu(v1, 16);
            sw(v1, gp, -17148);  // 0x7CE9F4
            backedge(ctx);
        } else {
            // 0x004d4b04
            charge(ctx, 4);
            lw(a0, gp, -17212);  // 0x7CE9B4
            v1 = 258;
            if (a0 == v1) {
                // 0x004d4b94
                charge(ctx, 8);
                a0 = 0;
                v1 = 0x70000000;
                pcpyld(a0, a0, v1);
                lw(v1, gp, -17148);  // 0x7CE9F4
                sq(a0, v1, 0);
                lw(v1, gp, -17148);  // 0x7CE9F4
                v1 = addiu(v1, 16);
                sw(v1, gp, -17148);  // 0x7CE9F4
            } else {
                // 0x004d4b14
                charge(ctx, 32);
                a0 = 0;
                v1 = 0x70000000;
                pcpyld(a0, a0, v1);
                sq(a0, a1, 0);
                v1 = v1 | 0x3;
                a1 = 0x50000000;
                a0 = 0x11000000;
                a1 = a1 | 0x2;
                a1 = dsll32(a1, 0);
                a0 = a0 | a1;
                pcpyld(a3, a0, v1);
                lw(a2, gp, -17148);  // 0x7CE9F4
                v1 = 0x10000000;
                a1 = 14;
                a0 = dsll32(v1, 0);
                v1 = 0x8001;
                v1 = v1 | a0;
                sq(a3, a2, 0);
                pcpyld(v1, a1, v1);
                sq(v1, a2, 16);
                a0 = 0;
                v1 = 127;
                pcpyld(v1, v1, a0);
                sq(v1, a2, 32);
                a0 = 0x6000000;
                v1 = 0x13000000;
                pcpyld(v1, a0, v1);
                sq(v1, a2, 48);
                lw(v1, gp, -17148);  // 0x7CE9F4
                v1 = addiu(v1, 64);
                sw(v1, gp, -17148);  // 0x7CE9F4
            }
        }
        // 0x004d4bb4
        charge(ctx, 5);
        a0 = dsll32(v1, 0);
        sw(zero, gp, -17208);  // 0x7CE9B8
        a0 = dsra32(a0, 0);
        v1 = 0;
        if (a0 != 0) {
            // 0x004d4bc8
            charge(ctx, 3);
            lw(v1, gp, -17124);  // g_rwDMASprBase
            v1 = subu(a0, v1);
        }
        // 0x004d4d84
        charge(ctx, 2);
        if (v1 == 0) {
            backedge(ctx);
        } else {
            // 0x004d4d8c
            charge(ctx, 2);
            a0 = 0x10010000;
            backedge(ctx);
            // 0x004d4bd4
            charge(ctx, 4);
            lw(a1, a0, -12288);
            a1 = a1 & 0x100;
            if (a1 != 0) {
                // 0x004d4d94
                charge(ctx, 4);
                a1 = 256;
                sw(a1, a0, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x004d4da4
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004d4dc0
                charge(ctx, 2);
                a3 = 256;
                backedge(ctx);
            } else {
                // 0x004d4be4
                charge(ctx, 1);
                a3 = 256;
            }
            // 0x004d4be8
            charge(ctx, 14);
            a0 = 0x10010000;
            sw(a3, a0, -8176);  // 0x1000E010 D_STAT
            a1 = srl(v1, 4);
            lw(a2, gp, -17124);  // g_rwDMASprBase
            sw(a2, a0, -12160);  // 0x1000D080 D8 fromSPR SADR
            lw(a2, gp, -17128);  // 0x7CEA08
            sw(a2, a0, -12272);  // 0x1000D010 D8 fromSPR MADR
            sw(a1, a0, -12256);  // 0x1000D020 D8 fromSPR QWC
            sw(a3, a0, -12288);  // 0x1000D000 D8 fromSPR CHCR
            sync(ctx, 0);
            sync(ctx, 16);
            lw(a3, gp, -17208);  // 0x7CE9B8
            if (a3 != 0) {
                // 0x004d4c20
                charge(ctx, 5);
                a1 = si(-16384);
                a0 = 0x70000000;
                a1 = a3 & a1;
                if (a1 == a0) {
                    // 0x004d4c34
                    charge(ctx, 7);
                    lw(a1, gp, -17124);  // g_rwDMASprBase
                    a0 = 0x20000000;
                    lw(a2, gp, -17128);  // 0x7CEA08
                    a1 = subu(a3, a1);
                    a1 = addu(a2, a1);
                    a0 = a1 | a0;
                    sw(a0, gp, -17208);  // 0x7CE9B8
                }
            }
            // 0x004d4c50
            charge(ctx, 6);
            lw(a1, gp, -17128);  // 0x7CEA08
            lw(a0, gp, -17124);  // g_rwDMASprBase
            v1 = addu(a1, v1);
            sw(v1, gp, -17128);  // 0x7CEA08
            v1 = a0 ^ 0x2000;
            sw(v1, gp, -17124);  // g_rwDMASprBase
        }
        // 0x004d4c68
        charge(ctx, 3);
        lw(a0, gp, -17140);  // 0x7CE9FC
        if (a0 != 0) {
            // 0x004d4c74
            charge(ctx, 3);
            lw(v1, gp, -17136);  // 0x7CEA00
            if (v1 == 0) {
                // 0x004d4cbc
                charge(ctx, 5);
                lw(v1, gp, -17144);  // 0x7CE9F8
                sw(a0, v1, 0);
                lw(a0, gp, -17132);  // 0x7CEA04
                lw(v1, gp, -17144);  // 0x7CE9F8
                sw(a0, v1, 4);
            } else {
                // 0x004d4c80
                charge(ctx, 15);
                lw(a0, gp, -17144);  // 0x7CE9F8
                a1 = 4385;
                v1 = 290;
                sw(a1, a0, 0);
                lw(a1, gp, -17132);  // 0x7CEA04
                lw(a0, gp, -17144);  // 0x7CE9F8
                sw(a1, a0, 4);
                lw(a1, gp, -17144);  // 0x7CE9F8
                a0 = addiu(a1, 8);
                sw(a0, gp, -17144);  // 0x7CE9F8
                sw(v1, a1, 8);
                lw(a0, gp, -17136);  // 0x7CEA00
                lw(v1, gp, -17144);  // 0x7CE9F8
                sw(a0, v1, 4);
            }
        }
        // 0x004d4cd0
        charge(ctx, 11);
        lw(v1, gp, -17192);  // 0x7CE9C8
        lw(a2, gp, -17196);  // 0x7CE9C4
        lw(a1, gp, -17200);  // 0x7CE9C0
        lw(a0, gp, -17212);  // 0x7CE9B4
        sw(v1, gp, -17144);  // 0x7CE9F8
        v1 = addiu(v1, 8);
        sw(a2, gp, -17132);  // 0x7CEA04
        sw(a1, gp, -17136);  // 0x7CEA00
        sw(a0, gp, -17140);  // 0x7CE9FC
        sw(v1, gp, -17192);  // 0x7CE9C8
        if (a1 != 0) {
            // 0x004d4cfc
            charge(ctx, 2);
            v1 = addiu(v1, 8);
            sw(v1, gp, -17192);  // 0x7CE9C8
        }
        // 0x004d4d04
        charge(ctx, 8);
        lhu(a0, gp, -17264);  // 0x7CE980
        lhu(v1, gp, -17268);  // 0x7CE97C
        sw(zero, gp, -17152);  // 0x7CE9F0
        sw(zero, gp, -17148);  // 0x7CE9F4
        sw(zero, gp, -17196);  // 0x7CE9C4
        sw(zero, gp, -17200);  // 0x7CE9C0
        sw(zero, gp, -17212);  // 0x7CE9B4
        if (a0 != v1) {
            // 0x004d4dc8
            charge(ctx, 4);
            jal(ctx, 0x4D4DC8u, gen::fn_sub_4D4280_004d4280);
            backedge(ctx);
        }
        // 0x004d4d24
        charge(ctx, 2);
        ld(ra, sp, 0x0);
    }
    // 0x004d4ddc (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x004D4DF0 _rwDMAForceBufferSwap -- 516 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Forces a swap of the RW DMA double buffer: closes the open packet, waits for the other half (InvalidDCache),
// restarts the handler.
void _rwDMAForceBufferSwap(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004d4df0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    link(ctx, 0x4D4DFCu);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn__rwDMAClosePkt_004d4a60);
    lw(v0, gp, -17140);  // 0x7CE9FC
    if (v0 != 0) {
        // 0x004d4e10
        charge(ctx, 5);
        v0 = 0x10010000;
        lw(v1, v0, -12288);  // 0x1000D000 D8 fromSPR CHCR
        v1 = v1 & 0x100;
        if (v1 != 0) {
            // 0x004d4f98
            charge(ctx, 4);
            v1 = 256;
            sw(v1, v0, -8160);
            sync(ctx, 0);
            sync(ctx, 16);
            for (;;) {
                // 0x004d4fa8
                charge(ctx, 7);
                if (cop0_cond(ctx)) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004d4fc4
            charge(ctx, 2);
            lw(v0, gp, -17136);  // 0x7CEA00
            backedge(ctx);
        } else {
            // 0x004d4e24
            charge(ctx, 1);
            lw(v0, gp, -17136);  // 0x7CEA00
        }
        // 0x004d4e28
        charge(ctx, 2);
        if (v0 == 0) {
            // 0x004d4e6c
            charge(ctx, 6);
            lw(v1, gp, -17140);  // 0x7CE9FC
            lw(v0, gp, -17144);  // 0x7CE9F8
            sw(v1, v0, 0);
            lw(v1, gp, -17132);  // 0x7CEA04
            lw(v0, gp, -17144);  // 0x7CE9F8
            sw(v1, v0, 4);
        } else {
            // 0x004d4e30
            charge(ctx, 15);
            lw(v1, gp, -17144);  // 0x7CE9F8
            a0 = 4385;
            v0 = 290;
            sw(a0, v1, 0);
            lw(a0, gp, -17132);  // 0x7CEA04
            lw(v1, gp, -17144);  // 0x7CE9F8
            sw(a0, v1, 4);
            lw(a0, gp, -17144);  // 0x7CE9F8
            v1 = addiu(a0, 8);
            sw(v1, gp, -17144);  // 0x7CE9F8
            sw(v0, a0, 8);
            lw(v1, gp, -17136);  // 0x7CEA00
            lw(v0, gp, -17144);  // 0x7CE9F8
            sw(v1, v0, 4);
        }
        // 0x004d4e84
        charge(ctx, 4);
        sw(zero, gp, -17132);  // 0x7CEA04
        sw(zero, gp, -17136);  // 0x7CEA00
        sw(zero, gp, -17140);  // 0x7CE9FC
        sw(zero, gp, -17144);  // 0x7CE9F8
    }
    // 0x004d4e94
    charge(ctx, 3);
    lw(v1, gp, -17180);  // 0x7CE9D4
    lw(v0, gp, -17184);  // 0x7CE9D0
    s0 = subu(v1, v0);
    for (;;) {
        // 0x004d4ea0
        charge(ctx, 6);
        lw(v1, gp, -17232);  // 0x7CE9A0
        lw(v0, gp, -17236);  // g_rwDMAQueueRead
        s1 = v1 ^ v0;
        s1 = sltu(0, s1);
        if (s1 == 0) {
            // 0x004d4eb8
            charge(ctx, 2);
            lbu(v0, gp, -17216);  // g_rwDMABusyCount
            s1 = sltu(0, v0);
        }
        // 0x004d4ec0
        charge(ctx, 3);
        lw(v0, gp, -17300);  // g_rwDMAWaitCallback
        if (v0 != 0) {
            // 0x004d4fcc
            charge(ctx, 5);
            a0 = s1;
            a1 = s0;
            jalr(ctx, 0x4D4FD0u, v0.u());
            backedge(ctx);
        } else {
            // 0x004d4ecc
            charge(ctx, 1);
        }
        // 0x004d4ed0
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004d4ed8
    charge(ctx, 1);
    v0 = 0x10000;
    for (;;) {
        // 0x004d4edc
        charge(ctx, 7);
        di(ctx);
        sync(ctx, 16);
        mfc0(v1, 12);
        v1 = v1 & v0;
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004d4ef8
    charge(ctx, 29);
    lbu(a1, gp, -17168);  // 0x7CE9E0
    a0 = addiu(gp, -17160);  // &0x7CE9E8
    lw(v0, gp, -17192);  // 0x7CE9C8
    v1 = sll(a1, 2);
    sw(v0, gp, -17236);  // g_rwDMAQueueRead
    v0 = addu(a0, v1);
    lw(v0, v0, 0);
    sw(v0, gp, -17232);  // 0x7CE9A0
    ei(ctx);
    v0 = a1 ^ 0x1;
    sb(v0, gp, -17168);  // 0x7CE9E0
    lbu(v1, gp, -17168);  // 0x7CE9E0
    lw(v0, gp, -17164);  // 0x7CE9E4
    sw(zero, gp, -17148);  // 0x7CE9F4
    sw(zero, gp, -17152);  // 0x7CE9F0
    v1 = sll(v1, 2);
    v1 = addu(a0, v1);
    lw(a0, v1, 0);
    v1 = addiu(a0, 128);
    v0 = addu(a0, v0);
    sw(v1, gp, -17184);  // 0x7CE9D0
    a1 = addiu(v0, -1);
    v1 = addiu(v1, -8);
    sw(a0, gp, -17192);  // 0x7CE9C8
    sw(v0, gp, -17180);  // 0x7CE9D4
    sw(v1, gp, -17188);  // 0x7CE9CC
    link(ctx, 0x4D4F60u);  // $ra first: the delay slot below depends on it
    sw(v0, gp, -17172);  // 0x7CE9DC
    call(ctx, gen::fn_InvalidDCache_00503b98);
    v0 = 0x10000;
    for (;;) {
        // 0x004d4f6c
        charge(ctx, 7);
        di(ctx);
        sync(ctx, 16);
        mfc0(v1, 12);
        v1 = v1 & v0;
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004d4f88
    charge(ctx, 4);
    a0 = si(-1);
    jal(ctx, 0x4D4F88u, gen::fn__rwDMAHandler_004d4350);
    ei(ctx);
    // 0x004d4fe0
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x004D5000 _rwDMAAddPkt -- 448 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Adds a prebuilt packet to the DMA queue (closing the open one, swapping when full).
void _rwDMAAddPkt(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004d5000
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(a0, gp, -17148);  // 0x7CE9F4
    lw(v1, gp, -17152);  // 0x7CE9F0
    v1 = a0 | v1;
    s0 = a1;
    if (v1 != 0) {
        // 0x004d5130
        charge(ctx, 4);
        jal(ctx, 0x4D5130u, gen::fn__rwDMAClosePkt_004d4a60);
        lw(v1, gp, -17140);  // 0x7CE9FC
        backedge(ctx);
    } else {
        // 0x004d5028
        charge(ctx, 1);
        lw(v1, gp, -17140);  // 0x7CE9FC
    }
    // 0x004d502c
    charge(ctx, 2);
    if (v1 != 0) {
        // 0x004d5034
        charge(ctx, 5);
        v1 = 0x10010000;
        lw(a0, v1, -12288);  // 0x1000D000 D8 fromSPR CHCR
        a0 = a0 & 0x100;
        if (a0 != 0) {
            // 0x004d5140
            charge(ctx, 4);
            a0 = 256;
            sw(a0, v1, -8160);
            sync(ctx, 0);
            sync(ctx, 16);
            for (;;) {
                // 0x004d5150
                charge(ctx, 7);
                if (cop0_cond(ctx)) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004d516c
            charge(ctx, 2);
            lw(v1, gp, -17136);  // 0x7CEA00
            backedge(ctx);
        } else {
            // 0x004d5048
            charge(ctx, 1);
            lw(v1, gp, -17136);  // 0x7CEA00
        }
        // 0x004d504c
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x004d5090
            charge(ctx, 6);
            lw(a0, gp, -17140);  // 0x7CE9FC
            lw(v1, gp, -17144);  // 0x7CE9F8
            sw(a0, v1, 0);
            lw(a0, gp, -17132);  // 0x7CEA04
            lw(v1, gp, -17144);  // 0x7CE9F8
            sw(a0, v1, 4);
        } else {
            // 0x004d5054
            charge(ctx, 15);
            lw(a0, gp, -17144);  // 0x7CE9F8
            a1 = 4385;
            v1 = 290;
            sw(a1, a0, 0);
            lw(a1, gp, -17132);  // 0x7CEA04
            lw(a0, gp, -17144);  // 0x7CE9F8
            sw(a1, a0, 4);
            lw(a1, gp, -17144);  // 0x7CE9F8
            a0 = addiu(a1, 8);
            sw(a0, gp, -17144);  // 0x7CE9F8
            sw(v1, a1, 8);
            lw(a0, gp, -17136);  // 0x7CEA00
            lw(v1, gp, -17144);  // 0x7CE9F8
            sw(a0, v1, 4);
        }
        // 0x004d50a8
        charge(ctx, 4);
        sw(zero, gp, -17132);  // 0x7CEA04
        sw(zero, gp, -17136);  // 0x7CEA00
        sw(zero, gp, -17140);  // 0x7CE9FC
        sw(zero, gp, -17144);  // 0x7CE9F8
    }
    // 0x004d50b8
    charge(ctx, 5);
    lw(a2, gp, -17192);  // 0x7CE9C8
    lw(v1, gp, -17188);  // 0x7CE9CC
    v1 = sltu(a2, v1);
    if (v1 != 0) {
        // 0x004d5174
        charge(ctx, 7);
        sw(s0, a2, 0);
        lw(v1, gp, -17192);  // 0x7CE9C8
        sw(s1, v1, 4);
        lw(v1, gp, -17192);  // 0x7CE9C8
        v1 = addiu(v1, 8);
        sw(v1, gp, -17192);  // 0x7CE9C8
    } else {
        // 0x004d50cc
        charge(ctx, 9);
        lw(a1, gp, -17184);  // 0x7CE9D0
        a0 = si(-64);
        lw(v1, gp, -17180);  // 0x7CE9D4
        a1 = addiu(a1, 63);
        a1 = a1 & a0;
        a0 = addiu(a1, 128);
        at = sltu(v1, a0);
        if (at != 0) {
            // 0x004d5190
            charge(ctx, 7);
            sw(s0, a2, 0);
            lw(v0, gp, -17192);  // 0x7CE9C8
            sw(s1, v0, 4);
            lw(v0, gp, -17192);  // 0x7CE9C8
            v0 = addiu(v0, 8);
            link(ctx, 0x4D51A4u);  // $ra first: the delay slot below depends on it
            sw(v0, gp, -17192);  // 0x7CE9C8
            call(ctx, gen::fn__rwDMAForceBufferSwap_004d4df0);
        } else {
            // 0x004d50f0
            charge(ctx, 16);
            a0 = addiu(a1, 120);
            v1 = 127;
            sw(a0, gp, -17188);  // 0x7CE9CC
            a0 = addiu(a0, 8);
            sw(a0, gp, -17184);  // 0x7CE9D0
            sw(v1, a2, 0);
            lw(v1, gp, -17192);  // 0x7CE9C8
            sw(a1, v1, 4);
            sw(a1, gp, -17192);  // 0x7CE9C8
            sw(s0, a1, 0);
            lw(v1, gp, -17192);  // 0x7CE9C8
            sw(s1, v1, 4);
            lw(v1, gp, -17192);  // 0x7CE9C8
            v1 = addiu(v1, 8);
            sw(v1, gp, -17192);  // 0x7CE9C8
        }
    }
    // 0x004d51ac (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x004D51C0 _rwDMAAddPURef -- 168 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Adds a reference to a persistent upload (code / data) to the open packet.
void _rwDMAAddPURef(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004d51c0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lhu(a1, gp, -17268);  // 0x7CE97C
    lw(v1, gp, -17260);  // 0x7CE984
    a1 = sll(a1, 2);
    v1 = addu(v1, a1);
    sw(a0, v1, 0);
    lhu(v1, gp, -17268);  // 0x7CE97C
    lhu(a1, gp, -20292);  // 0x7CDDAC
    v1 = addiu(v1, 1);
    sh(v1, gp, -17268);  // 0x7CE97C
    lhu(a0, gp, -17268);  // 0x7CE97C
    if (a0 == a1) {
        // 0x004d5248
        charge(ctx, 3);
        sh(zero, gp, -17268);  // 0x7CE97C
        v1 = 0;
        backedge(ctx);
    }
    // 0x004d5200
    charge(ctx, 4);
    s0 = v1 & 0xFFFF;
    lhu(v1, gp, -17264);  // 0x7CE980
    if (v1 != s0) {
        // 0x004d5254
        charge(ctx, 1);
        ld(ra, sp, 0x20);
    } else {
        // 0x004d5210
        charge(ctx, 6);
        v0 = sra(a1, 1);
        v1 = addu(v1, v0);
        a0 = v1 & 0xFFFF;
        v0 = slt(a0, a1);
        sh(v1, gp, -17268);  // 0x7CE97C
        if (v0 == 0) {
            // 0x004d5228
            charge(ctx, 2);
            v1 = subu(a0, a1);
            sh(v1, gp, -17268);  // 0x7CE97C
        }
        // 0x004d5230
        charge(ctx, 6);
        s1 = v1 & 0xFFFF;
        jal(ctx, 0x4D5230u, gen::fn__rwDMAClosePkt_004d4a60);
        sh(s1, gp, -17264);  // 0x7CE980
        sh(s0, gp, -17268);  // 0x7CE97C
        ld(ra, sp, 0x20);
    }
    // 0x004d5258 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x004D54E0 _rwDMAOpenGIFPkt -- 1256 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Opens a GIF packet of the requested size in the DMA ring (closing / swapping as needed).
void _rwDMAOpenGIFPkt(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004d54e0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, gp, -17212);  // 0x7CE9B4
    if (a0 != 0) {
        // 0x004d54fc
        charge(ctx, 3);
        v0 = 258;
        if (a0 == v0) {
            // 0x004d5508
            charge(ctx, 12);
            v0 = addiu(s0, 1);
            lw(t0, gp, -17124);  // g_rwDMASprBase
            v1 = sll(v0, 4);
            lw(a3, gp, -17148);  // 0x7CE9F4
            lw(v0, gp, -17128);  // 0x7CEA08
            lw(a1, gp, -17180);  // 0x7CE9D4
            a2 = subu(a3, t0);
            v0 = addu(v0, a2);
            v0 = addu(v1, v0);
            at = sltu(v0, a1);
            if (at == 0) {
                goto L_004d5618;
            }
            // 0x004d5538
            charge(ctx, 4);
            v0 = addu(v1, a2);
            at = sltiu(v0, 8193);
            if (at == 0) {
                // 0x004d5548
                charge(ctx, 2);
                v0 = 0;
                if (a3 != 0) {
                    // 0x004d5550
                    charge(ctx, 1);
                    v0 = a2;
                }
                // 0x004d5554
                charge(ctx, 2);
                if (v0 != 0) {
                    // 0x004d555c
                    charge(ctx, 5);
                    a0 = 0x10010000;
                    lw(a1, a0, -12288);  // 0x1000D000 D8 fromSPR CHCR
                    a1 = a1 & 0x100;
                    if (a1 != 0) {
                        // 0x004d583c
                        charge(ctx, 4);
                        a1 = 256;
                        sw(a1, a0, -8160);
                        sync(ctx, 0);
                        sync(ctx, 16);
                        for (;;) {
                            // 0x004d584c
                            charge(ctx, 7);
                            if (cop0_cond(ctx)) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004d5868
                        charge(ctx, 2);
                        a3 = 256;
                        backedge(ctx);
                    } else {
                        // 0x004d5570
                        charge(ctx, 1);
                        a3 = 256;
                    }
                    // 0x004d5574
                    charge(ctx, 14);
                    a0 = 0x10010000;
                    sw(a3, a0, -8176);  // 0x1000E010 D_STAT
                    a1 = srl(v0, 4);
                    lw(a2, gp, -17124);  // g_rwDMASprBase
                    sw(a2, a0, -12160);  // 0x1000D080 D8 fromSPR SADR
                    lw(a2, gp, -17128);  // 0x7CEA08
                    sw(a2, a0, -12272);  // 0x1000D010 D8 fromSPR MADR
                    sw(a1, a0, -12256);  // 0x1000D020 D8 fromSPR QWC
                    sw(a3, a0, -12288);  // 0x1000D000 D8 fromSPR CHCR
                    sync(ctx, 0);
                    sync(ctx, 16);
                    lw(a3, gp, -17208);  // 0x7CE9B8
                    if (a3 != 0) {
                        // 0x004d55ac
                        charge(ctx, 5);
                        a1 = si(-16384);
                        a0 = 0x70000000;
                        a1 = a3 & a1;
                        if (a1 == a0) {
                            // 0x004d55c0
                            charge(ctx, 7);
                            lw(a1, gp, -17124);  // g_rwDMASprBase
                            a0 = 0x20000000;
                            lw(a2, gp, -17128);  // 0x7CEA08
                            a1 = subu(a3, a1);
                            a1 = addu(a2, a1);
                            a0 = a1 | a0;
                            sw(a0, gp, -17208);  // 0x7CE9B8
                        }
                    }
                    // 0x004d55dc
                    charge(ctx, 7);
                    lw(a1, gp, -17128);  // 0x7CEA08
                    lw(a0, gp, -17124);  // g_rwDMASprBase
                    v0 = addu(a1, v0);
                    t0 = a0 ^ 0x2000;
                    sw(v0, gp, -17128);  // 0x7CEA08
                    sw(t0, gp, -17124);  // g_rwDMASprBase
                    sw(t0, gp, -17148);  // 0x7CE9F4
                }
            }
            // 0x004d55f8
            charge(ctx, 8);
            lw(a0, gp, -17128);  // 0x7CEA08
            v0 = 1;
            lw(a1, gp, -17148);  // 0x7CE9F4
            v1 = addu(a0, v1);
            v1 = addu(a1, v1);
            v1 = subu(v1, t0);
            sw(v1, gp, -17184);  // 0x7CE9D0
            // 0x004d59b8 (the shared epilogue, written out on this path)
            charge(ctx, 4);
            ld(ra, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x20);
            return;
        }
    L_004d5618:
        charge(ctx, 3);
        lw(v0, gp, -17152);  // 0x7CE9F0
        if (v0 != 0) {
            // 0x004d5624
            charge(ctx, 15);
            lw(v0, gp, -17124);  // g_rwDMASprBase
            v1 = addiu(s0, 1);
            lw(a3, gp, -17148);  // 0x7CE9F4
            a2 = si(-128);
            lw(t0, gp, -17128);  // 0x7CEA08
            v1 = sll(v1, 4);
            lw(a1, gp, -17180);  // 0x7CE9D4
            t1 = subu(a3, v0);
            a3 = addu(t0, t1);
            a3 = addiu(a3, 255);
            a2 = a3 & a2;
            a2 = addu(v1, a2);
            at = sltu(a1, a2);
            if (at != 0) {
                goto L_004d58b0;
            }
            // 0x004d5660
            charge(ctx, 4);
            a1 = lui(0x8000);
            a0 = a0 & a1;
            if (a0 != 0) {
                // 0x004d5670
                charge(ctx, 7);
                lw(a3, gp, -17204);  // 0x7CE9BC
                a0 = subu(t0, a3);
                a0 = addu(a0, t1);
                a0 = srl(a0, 4);
                a2 = addiu(a0, -1);
                if (a2 == 0) {
                    // 0x004d5870
                    charge(ctx, 3);
                    a0 = addiu(t0, -16);
                    sw(a0, gp, -17128);  // 0x7CEA08
                    backedge(ctx);
                } else {
                    // 0x004d568c
                    charge(ctx, 13);
                    a1 = 0x50000000;
                    a0 = 0x10000000;
                    a1 = a2 | a1;
                    a0 = a2 | a0;
                    a2 = dsll32(a1, 0);
                    a1 = dsll32(a0, 0);
                    a2 = dsrl32(a2, 0);
                    a0 = 0x20000000;
                    a1 = dsrl32(a1, 0);
                    a2 = dsll32(a2, 0);
                    a0 = a3 | a0;
                    pcpyld(a1, a2, a1);
                    sq(a1, a0, 0);
                }
                // 0x004d56c0
                charge(ctx, 1);
                sw(zero, gp, -17204);  // 0x7CE9BC
            }
            // 0x004d56c4
            charge(ctx, 30);
            a0 = 0x50000000;
            a1 = 0x11000000;
            a2 = a0 | 0x2;
            lw(a3, gp, -17148);  // 0x7CE9F4
            a0 = 0x70000000;
            a2 = dsll32(a2, 0);
            a1 = a1 | a2;
            a0 = a0 | 0x3;
            pcpyld(t0, a1, a0);
            a0 = 0x10000000;
            a2 = 14;
            a1 = dsll32(a0, 0);
            a0 = 0x8001;
            sq(t0, a3, 0);
            a1 = a0 | a1;
            pcpyld(a2, a2, a1);
            a0 = 127;
            a1 = 0;
            pcpyld(a0, a0, a1);
            sq(a2, a3, 16);
            a2 = 0x6000000;
            a1 = 0x13000000;
            sq(a0, a3, 32);
            pcpyld(a1, a2, a1);
            sq(a1, a3, 48);
            a0 = 0;
            lw(a1, gp, -17148);  // 0x7CE9F4
            a1 = addiu(a1, 64);
            sw(a1, gp, -17148);  // 0x7CE9F4
            if (a1 != 0) {
                // 0x004d573c
                charge(ctx, 1);
                a0 = subu(a1, v0);
            }
            // 0x004d5740
            charge(ctx, 2);
            if (a0 != 0) {
                // 0x004d5748
                charge(ctx, 5);
                v0 = 0x10010000;
                lw(a1, v0, -12288);  // 0x1000D000 D8 fromSPR CHCR
                a1 = a1 & 0x100;
                if (a1 != 0) {
                    // 0x004d587c
                    charge(ctx, 4);
                    a1 = 256;
                    sw(a1, v0, -8160);
                    sync(ctx, 0);
                    sync(ctx, 16);
                    for (;;) {
                        // 0x004d588c
                        charge(ctx, 7);
                        if (cop0_cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004d58a8
                    charge(ctx, 2);
                    a3 = 256;
                    backedge(ctx);
                } else {
                    // 0x004d575c
                    charge(ctx, 1);
                    a3 = 256;
                }
                // 0x004d5760
                charge(ctx, 14);
                v0 = 0x10010000;
                sw(a3, v0, -8176);  // 0x1000E010 D_STAT
                a1 = srl(a0, 4);
                lw(a2, gp, -17124);  // g_rwDMASprBase
                sw(a2, v0, -12160);  // 0x1000D080 D8 fromSPR SADR
                lw(a2, gp, -17128);  // 0x7CEA08
                sw(a2, v0, -12272);  // 0x1000D010 D8 fromSPR MADR
                sw(a1, v0, -12256);  // 0x1000D020 D8 fromSPR QWC
                sw(a3, v0, -12288);  // 0x1000D000 D8 fromSPR CHCR
                sync(ctx, 0);
                sync(ctx, 16);
                lw(a3, gp, -17208);  // 0x7CE9B8
                if (a3 != 0) {
                    // 0x004d5798
                    charge(ctx, 5);
                    a1 = si(-16384);
                    v0 = 0x70000000;
                    a1 = a3 & a1;
                    if (a1 == v0) {
                        // 0x004d57ac
                        charge(ctx, 7);
                        lw(a1, gp, -17124);  // g_rwDMASprBase
                        v0 = 0x20000000;
                        lw(a2, gp, -17128);  // 0x7CEA08
                        a1 = subu(a3, a1);
                        a1 = addu(a2, a1);
                        v0 = a1 | v0;
                        sw(v0, gp, -17208);  // 0x7CE9B8
                    }
                }
                // 0x004d57c8
                charge(ctx, 6);
                lw(a1, gp, -17128);  // 0x7CEA08
                lw(v0, gp, -17124);  // g_rwDMASprBase
                a0 = addu(a1, a0);
                v0 = v0 ^ 0x2000;
                sw(a0, gp, -17128);  // 0x7CEA08
                sw(v0, gp, -17124);  // g_rwDMASprBase
            }
            // 0x004d57e0
            charge(ctx, 23);
            lw(t0, gp, -17128);  // 0x7CEA08
            a3 = si(-128);
            lw(a1, gp, -17152);  // 0x7CE9F0
            a2 = 0x20000000;
            t1 = 0;
            a0 = 258;
            v0 = 1;
            t0 = addiu(t0, 207);
            a3 = t0 & a3;
            t0 = addiu(a3, -16);
            a3 = addu(t0, v1);
            v1 = dsll32(t0, 0);
            sw(a3, gp, -17184);  // 0x7CE9D0
            v1 = dsrl32(v1, 0);
            v1 = dsll32(v1, 0);
            v1 = v1 | a2;
            pcpyld(v1, t1, v1);
            sq(v1, a1, 0);
            lw(v1, gp, -17124);  // g_rwDMASprBase
            sw(a0, gp, -17212);  // 0x7CE9B4
            sw(t0, gp, -17128);  // 0x7CEA08
            sw(v1, gp, -17148);  // 0x7CE9F4
            // 0x004d59b8 (the shared epilogue, written out on this path)
            charge(ctx, 4);
            ld(ra, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x20);
            return;
        }
    L_004d58b0:
        charge(ctx, 2);
        jal(ctx, 0x4D58B0u, gen::fn__rwDMAClosePkt_004d4a60);
    }
    // 0x004d58b8
    charge(ctx, 4);
    lw(a1, gp, -17192);  // 0x7CE9C8
    lw(v0, gp, -17188);  // 0x7CE9CC
    if (a1 == v0) {
        // 0x004d592c
        charge(ctx, 9);
        lw(a0, gp, -17184);  // 0x7CE9D0
        v1 = si(-64);
        lw(v0, gp, -17180);  // 0x7CE9D4
        a0 = addiu(a0, 63);
        a0 = a0 & v1;
        v1 = addiu(a0, 128);
        v0 = sltu(v1, v0);
        if (v0 != 0) {
            // 0x004d5958
            charge(ctx, 11);
            v1 = addiu(a0, 120);
            v0 = 127;
            sw(v1, gp, -17188);  // 0x7CE9CC
            v1 = addiu(v1, 8);
            sw(v1, gp, -17184);  // 0x7CE9D0
            sw(v0, a1, 0);
            lw(v0, gp, -17192);  // 0x7CE9C8
            sw(a0, v0, 4);
            lw(v0, gp, -17184);  // 0x7CE9D0
            sw(a0, gp, -17192);  // 0x7CE9C8
            backedge(ctx);
        } else {
            // 0x004d5950
            charge(ctx, 2);
            v0 = 0;
            backedge(ctx);
        }
    } else {
        // 0x004d58c8
        charge(ctx, 1);
        lw(v0, gp, -17184);  // 0x7CE9D0
    }
    // 0x004d58cc
    charge(ctx, 2);
    if (v0 != 0) {
        // 0x004d58d4
        charge(ctx, 9);
        v1 = addiu(v0, 143);
        v0 = si(-128);
        a0 = v1 & v0;
        v0 = sll(s0, 4);
        v1 = addu(a0, v0);
        lw(v0, gp, -17180);  // 0x7CE9D4
        at = sltu(v0, v1);
        if (at != 0) {
            goto L_004d5984;
        }
        // 0x004d58f8
        charge(ctx, 13);
        v0 = addiu(s0, 1);
        v1 = addiu(a0, -16);
        v0 = sll(v0, 4);
        sw(v1, gp, -17196);  // 0x7CE9C4
        v0 = addu(v1, v0);
        sw(v1, gp, -17128);  // 0x7CEA08
        lw(v1, gp, -17124);  // g_rwDMASprBase
        sw(v0, gp, -17184);  // 0x7CE9D0
        v0 = 258;
        sw(v0, gp, -17212);  // 0x7CE9B4
        v0 = 1;
        sw(v1, gp, -17148);  // 0x7CE9F4
        // 0x004d59b8 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(ra, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x20);
        return;
    }
L_004d5984:
    charge(ctx, 7);
    lw(v0, gp, -17164);  // 0x7CE9E4
    v1 = addiu(s0, 9);
    v1 = sll(v1, 4);
    v1 = addiu(v1, 176);
    at = sltu(v0, v1);
    if (at == 0) {
        // 0x004d59a8
        charge(ctx, 4);
        jal(ctx, 0x4D59A8u, gen::fn__rwDMAForceBufferSwap_004d4df0);
        a0 = s0;
        jal(ctx, 0x4D59B0u, gen::fn__rwDMAOpenGIFPkt_004d54e0);
    } else {
        // 0x004d59a0
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004d59b8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x004D59D0 _rwDMAOpenVIFPkt -- 1208 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Opens a VIF packet of the requested size in the DMA ring (closing / swapping as needed).
void _rwDMAOpenVIFPkt(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004d59d0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = lui(0x8000);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    s0 = a0;
    lw(a0, gp, -17212);  // 0x7CE9B4
    v1 = nor(a0, 0);
    v0 = v1 & v0;
    t0 = s0 & v0;
    s1 = addiu(s1, 4);
    if (t0 != 0) {
        // 0x004d5a04
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x004d5a08
    charge(ctx, 2);
    if (a0 != 0) {
        // 0x004d5a10
        charge(ctx, 5);
        v1 = dsll32(a0, 1);
        v0 = 4353;
        v1 = dsrl32(v1, 1);
        if (v1 == v0) {
            // 0x004d5a24
            charge(ctx, 11);
            lw(a0, gp, -17124);  // g_rwDMASprBase
            v1 = sll(s1, 4);
            lw(a3, gp, -17148);  // 0x7CE9F4
            lw(v0, gp, -17128);  // 0x7CEA08
            lw(a1, gp, -17180);  // 0x7CE9D4
            a2 = subu(a3, a0);
            v0 = addu(v0, a2);
            v0 = addu(v1, v0);
            at = sltu(v0, a1);
            if (at == 0) {
                goto L_004d5ca4;
            }
            // 0x004d5a50
            charge(ctx, 4);
            v0 = addu(v1, a2);
            at = sltiu(v0, 8193);
            if (at == 0) {
                // 0x004d5a60
                charge(ctx, 2);
                v0 = 0;
                if (a3 != 0) {
                    // 0x004d5a68
                    charge(ctx, 1);
                    v0 = a2;
                }
                // 0x004d5a6c
                charge(ctx, 2);
                if (v0 != 0) {
                    // 0x004d5a74
                    charge(ctx, 5);
                    a0 = 0x10010000;
                    lw(a1, a0, -12288);  // 0x1000D000 D8 fromSPR CHCR
                    a1 = a1 & 0x100;
                    if (a1 != 0) {
                        // 0x004d5d4c
                        charge(ctx, 4);
                        a1 = 256;
                        sw(a1, a0, -8160);
                        sync(ctx, 0);
                        sync(ctx, 16);
                        for (;;) {
                            // 0x004d5d5c
                            charge(ctx, 7);
                            if (cop0_cond(ctx)) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004d5d78
                        charge(ctx, 2);
                        a3 = 256;
                        backedge(ctx);
                    } else {
                        // 0x004d5a88
                        charge(ctx, 1);
                        a3 = 256;
                    }
                    // 0x004d5a8c
                    charge(ctx, 14);
                    a0 = 0x10010000;
                    sw(a3, a0, -8176);  // 0x1000E010 D_STAT
                    a1 = srl(v0, 4);
                    lw(a2, gp, -17124);  // g_rwDMASprBase
                    sw(a2, a0, -12160);  // 0x1000D080 D8 fromSPR SADR
                    lw(a2, gp, -17128);  // 0x7CEA08
                    sw(a2, a0, -12272);  // 0x1000D010 D8 fromSPR MADR
                    sw(a1, a0, -12256);  // 0x1000D020 D8 fromSPR QWC
                    sw(a3, a0, -12288);  // 0x1000D000 D8 fromSPR CHCR
                    sync(ctx, 0);
                    sync(ctx, 16);
                    lw(a3, gp, -17208);  // 0x7CE9B8
                    if (a3 != 0) {
                        // 0x004d5ac4
                        charge(ctx, 5);
                        a1 = si(-16384);
                        a0 = 0x70000000;
                        a1 = a3 & a1;
                        if (a1 == a0) {
                            // 0x004d5ad8
                            charge(ctx, 7);
                            lw(a1, gp, -17124);  // g_rwDMASprBase
                            a0 = 0x20000000;
                            lw(a2, gp, -17128);  // 0x7CEA08
                            a1 = subu(a3, a1);
                            a1 = addu(a2, a1);
                            a0 = a1 | a0;
                            sw(a0, gp, -17208);  // 0x7CE9B8
                        }
                    }
                    // 0x004d5af4
                    charge(ctx, 7);
                    lw(a1, gp, -17128);  // 0x7CEA08
                    lw(a0, gp, -17124);  // g_rwDMASprBase
                    v0 = addu(a1, v0);
                    a0 = a0 ^ 0x2000;
                    sw(v0, gp, -17128);  // 0x7CEA08
                    sw(a0, gp, -17124);  // g_rwDMASprBase
                    sw(a0, gp, -17148);  // 0x7CE9F4
                }
            }
            // 0x004d5b10
            charge(ctx, 10);
            lw(t0, gp, -17128);  // 0x7CEA08
            a1 = lui(0x8000);
            lw(v0, gp, -17148);  // 0x7CE9F4
            lw(a2, gp, -17212);  // 0x7CE9B4
            v1 = addu(t0, v1);
            v1 = addu(v0, v1);
            v1 = subu(v1, a0);
            a1 = a2 & a1;
            sw(v1, gp, -17184);  // 0x7CE9D0
            if (a1 == s0) {
                // 0x004d5d80
                charge(ctx, 2);
                v0 = 1;
            } else {
                // 0x004d5b38
                charge(ctx, 4);
                v1 = nor(s0, 0);
                v1 = a1 & v1;
                if (v1 != 0) {
                    // 0x004d5b48
                    charge(ctx, 8);
                    lw(a3, gp, -17204);  // 0x7CE9BC
                    v1 = subu(v0, a0);
                    a1 = subu(t0, a3);
                    v1 = addu(a1, v1);
                    v1 = srl(v1, 4);
                    a2 = addiu(v1, -1);
                    if (a2 == 0) {
                        // 0x004d5d88
                        charge(ctx, 3);
                        v1 = addiu(t0, -16);
                        sw(v1, gp, -17128);  // 0x7CEA08
                        backedge(ctx);
                    } else {
                        // 0x004d5b68
                        charge(ctx, 13);
                        a1 = 0x50000000;
                        v1 = 0x10000000;
                        a1 = a2 | a1;
                        v1 = a2 | v1;
                        a2 = dsll32(a1, 0);
                        a1 = dsll32(v1, 0);
                        a2 = dsrl32(a2, 0);
                        v1 = 0x20000000;
                        a1 = dsrl32(a1, 0);
                        a2 = dsll32(a2, 0);
                        v1 = a3 | v1;
                        pcpyld(a1, a2, a1);
                        sq(a1, v1, 0);
                    }
                    // 0x004d5b9c
                    charge(ctx, 5);
                    lw(v1, gp, -17212);  // 0x7CE9B4
                    sw(zero, gp, -17204);  // 0x7CE9BC
                    v1 = dsll32(v1, 1);
                    v1 = dsrl32(v1, 1);
                    sw(v1, gp, -17212);  // 0x7CE9B4
                }
                // 0x004d5bb0
                charge(ctx, 7);
                lw(a1, gp, -17212);  // 0x7CE9B4
                v1 = lui(0x8000);
                a1 = nor(a1, 0);
                v1 = a1 & v1;
                v1 = v1 & s0;
                if (v1 != 0) {
                    // 0x004d5bcc
                    charge(ctx, 2);
                    v1 = 0;
                    if (v0 != 0) {
                        // 0x004d5bd4
                        charge(ctx, 1);
                        v1 = subu(v0, a0);
                    }
                    // 0x004d5bd8
                    charge(ctx, 2);
                    if (v1 != 0) {
                        // 0x004d5be0
                        charge(ctx, 5);
                        v0 = 0x10010000;
                        lw(a0, v0, -12288);  // 0x1000D000 D8 fromSPR CHCR
                        a0 = a0 & 0x100;
                        if (a0 != 0) {
                            // 0x004d5d94
                            charge(ctx, 4);
                            a0 = 256;
                            sw(a0, v0, -8160);
                            sync(ctx, 0);
                            sync(ctx, 16);
                            for (;;) {
                                // 0x004d5da4
                                charge(ctx, 7);
                                if (cop0_cond(ctx)) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004d5dc0
                            charge(ctx, 2);
                            a2 = 256;
                            backedge(ctx);
                        } else {
                            // 0x004d5bf4
                            charge(ctx, 1);
                            a2 = 256;
                        }
                        // 0x004d5bf8
                        charge(ctx, 14);
                        v0 = 0x10010000;
                        sw(a2, v0, -8176);  // 0x1000E010 D_STAT
                        a0 = srl(v1, 4);
                        lw(a1, gp, -17124);  // g_rwDMASprBase
                        sw(a1, v0, -12160);  // 0x1000D080 D8 fromSPR SADR
                        lw(a1, gp, -17128);  // 0x7CEA08
                        sw(a1, v0, -12272);  // 0x1000D010 D8 fromSPR MADR
                        sw(a0, v0, -12256);  // 0x1000D020 D8 fromSPR QWC
                        sw(a2, v0, -12288);  // 0x1000D000 D8 fromSPR CHCR
                        sync(ctx, 0);
                        sync(ctx, 16);
                        lw(a2, gp, -17208);  // 0x7CE9B8
                        if (a2 != 0) {
                            // 0x004d5c30
                            charge(ctx, 5);
                            a0 = si(-16384);
                            v0 = 0x70000000;
                            a0 = a2 & a0;
                            if (a0 == v0) {
                                // 0x004d5c44
                                charge(ctx, 7);
                                lw(a0, gp, -17124);  // g_rwDMASprBase
                                v0 = 0x20000000;
                                lw(a1, gp, -17128);  // 0x7CEA08
                                a0 = subu(a2, a0);
                                a0 = addu(a1, a0);
                                v0 = a0 | v0;
                                sw(v0, gp, -17208);  // 0x7CE9B8
                            }
                        }
                        // 0x004d5c60
                        charge(ctx, 7);
                        lw(a0, gp, -17128);  // 0x7CEA08
                        lw(v0, gp, -17124);  // g_rwDMASprBase
                        v1 = addu(a0, v1);
                        v0 = v0 ^ 0x2000;
                        sw(v1, gp, -17128);  // 0x7CEA08
                        sw(v0, gp, -17124);  // g_rwDMASprBase
                        sw(v0, gp, -17148);  // 0x7CE9F4
                    }
                    // 0x004d5c7c
                    charge(ctx, 8);
                    lw(a0, gp, -17128);  // 0x7CEA08
                    v0 = lui(0x8000);
                    lw(v1, gp, -17212);  // 0x7CE9B4
                    sw(a0, gp, -17204);  // 0x7CE9BC
                    a0 = addiu(a0, 16);
                    v0 = v1 | v0;
                    sw(a0, gp, -17128);  // 0x7CEA08
                    sw(v0, gp, -17212);  // 0x7CE9B4
                }
                // 0x004d5c9c
                charge(ctx, 2);
                v0 = 1;
            }
            // 0x004d5e74 (the shared epilogue, written out on this path)
            charge(ctx, 5);
            ld(ra, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x30);
            return;
        }
    L_004d5ca4:
        charge(ctx, 2);
        if (t0 != 0) {
            // 0x004d5cac
            charge(ctx, 1);
            s1 = addiu(s1, -1);
        }
        // 0x004d5cb0
        charge(ctx, 4);
        jal(ctx, 0x4D5CB0u, gen::fn__rwDMAClosePkt_004d4a60);
        lw(v0, gp, -17188);  // 0x7CE9CC
        goto L_004d5dcc;
    }
    // 0x004d5dc8
    charge(ctx, 1);
    lw(v0, gp, -17188);  // 0x7CE9CC
L_004d5dcc:
    charge(ctx, 5);
    lw(a0, gp, -17192);  // 0x7CE9C8
    v0 = addiu(v0, -8);
    v0 = sltu(a0, v0);
    if (v0 != 0) {
        backedge(ctx);
        // 0x004d5ce8
        charge(ctx, 1);
        lw(v0, gp, -17184);  // 0x7CE9D0
    } else {
        // 0x004d5de0
        charge(ctx, 2);
        lw(a1, gp, -17184);  // 0x7CE9D0
        backedge(ctx);
        // 0x004d5cc0
        charge(ctx, 8);
        v1 = si(-64);
        lw(v0, gp, -17180);  // 0x7CE9D4
        a1 = addiu(a1, 63);
        a1 = a1 & v1;
        v1 = addiu(a1, 128);
        v0 = sltu(v1, v0);
        if (v0 != 0) {
            // 0x004d5de8
            charge(ctx, 11);
            v1 = addiu(a1, 120);
            v0 = 127;
            sw(v1, gp, -17188);  // 0x7CE9CC
            v1 = addiu(v1, 8);
            sw(v1, gp, -17184);  // 0x7CE9D0
            sw(v0, a0, 0);
            lw(v0, gp, -17192);  // 0x7CE9C8
            sw(a1, v0, 4);
            lw(v0, gp, -17184);  // 0x7CE9D0
            sw(a1, gp, -17192);  // 0x7CE9C8
            backedge(ctx);
        } else {
            // 0x004d5ce0
            charge(ctx, 2);
            v0 = 0;
        }
    }
    // 0x004d5cec
    charge(ctx, 2);
    if (s0 != 0) {
        // 0x004d5cf4
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x004d5cf8
    charge(ctx, 2);
    if (v0 != 0) {
        // 0x004d5d00
        charge(ctx, 9);
        a0 = addiu(v0, 127);
        v1 = si(-128);
        lw(v0, gp, -17180);  // 0x7CE9D4
        a1 = sll(s1, 4);
        a0 = a0 & v1;
        v1 = addu(a0, a1);
        at = sltu(v0, v1);
        if (at != 0) {
            goto L_004d5e30;
        }
        // 0x004d5d24
        charge(ctx, 8);
        lw(v0, gp, -17124);  // g_rwDMASprBase
        sw(v1, gp, -17184);  // 0x7CE9D0
        v1 = 4353;
        sw(a0, gp, -17196);  // 0x7CE9C4
        sw(a0, gp, -17128);  // 0x7CEA08
        sw(v1, gp, -17212);  // 0x7CE9B4
        sw(v0, gp, -17148);  // 0x7CE9F4
        if (s0 != 0) {
            // 0x004d5e14
            charge(ctx, 7);
            v0 = addiu(a0, 16);
            sw(a0, gp, -17204);  // 0x7CE9BC
            sw(v0, gp, -17128);  // 0x7CEA08
            v0 = lui(0x8000);
            v0 = v1 | v0;
            sw(v0, gp, -17212);  // 0x7CE9B4
            backedge(ctx);
        }
        // 0x004d5d44
        charge(ctx, 2);
        v0 = 1;
        // 0x004d5e74 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(ra, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
L_004d5e30:
    charge(ctx, 2);
    if (s0 != 0) {
        // 0x004d5e38
        charge(ctx, 1);
        s1 = addiu(s1, -1);
    }
    // 0x004d5e3c
    charge(ctx, 7);
    lw(v0, gp, -17164);  // 0x7CE9E4
    v1 = addiu(s1, 8);
    v1 = sll(v1, 4);
    v1 = addiu(v1, 64);
    at = sltu(v0, v1);
    if (at == 0) {
        // 0x004d5e60
        charge(ctx, 5);
        jal(ctx, 0x4D5E60u, gen::fn__rwDMAForceBufferSwap_004d4df0);
        a0 = s0;
        a1 = s1;
        jal(ctx, 0x4D5E6Cu, gen::fn__rwDMAOpenVIFPkt_004d59d0);
    } else {
        // 0x004d5e58
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004d5e74 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x004D5E90 sub_4D5E90 -- 328 bytes; leaf frame (no stack)
// Waits for the scratchpad DMA and flushes the SPR packet staging area (g_rwDMASprBase) to main memory with fromSPR
// (D8).
void sub_4D5E90(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28};
    // 0x004d5e90
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(a0, gp, -17148);  // 0x7CE9F4
    v1 = 0;
    if (a0 != 0) {
        // 0x004d5e9c
        charge(ctx, 3);
        lw(v1, gp, -17124);  // g_rwDMASprBase
        v1 = subu(a0, v1);
    }
    // 0x004d5f8c
    charge(ctx, 2);
    if (v1 == 0) {
        backedge(ctx);
    } else {
        // 0x004d5f94
        charge(ctx, 2);
        a0 = 0x10010000;
        backedge(ctx);
        // 0x004d5eac
        charge(ctx, 4);
        lw(a1, a0, -12288);
        a1 = a1 & 0x100;
        if (a1 != 0) {
            // 0x004d5f9c
            charge(ctx, 4);
            a1 = 256;
            sw(a1, a0, -8160);
            sync(ctx, 0);
            sync(ctx, 16);
            for (;;) {
                // 0x004d5fac
                charge(ctx, 7);
                if (cop0_cond(ctx)) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004d5fc8
            charge(ctx, 2);
            a3 = 256;
            backedge(ctx);
        } else {
            // 0x004d5ebc
            charge(ctx, 1);
            a3 = 256;
        }
        // 0x004d5ec0
        charge(ctx, 14);
        a0 = 0x10010000;
        sw(a3, a0, -8176);  // 0x1000E010 D_STAT
        a1 = srl(v1, 4);
        lw(a2, gp, -17124);  // g_rwDMASprBase
        sw(a2, a0, -12160);  // 0x1000D080 D8 fromSPR SADR
        lw(a2, gp, -17128);  // 0x7CEA08
        sw(a2, a0, -12272);  // 0x1000D010 D8 fromSPR MADR
        sw(a1, a0, -12256);  // 0x1000D020 D8 fromSPR QWC
        sw(a3, a0, -12288);  // 0x1000D000 D8 fromSPR CHCR
        sync(ctx, 0);
        sync(ctx, 16);
        lw(a3, gp, -17208);  // 0x7CE9B8
        if (a3 != 0) {
            // 0x004d5ef8
            charge(ctx, 5);
            a1 = si(-16384);
            a0 = 0x70000000;
            a1 = a3 & a1;
            if (a1 == a0) {
                // 0x004d5f0c
                charge(ctx, 7);
                lw(a1, gp, -17124);  // g_rwDMASprBase
                a0 = 0x20000000;
                lw(a2, gp, -17128);  // 0x7CEA08
                a1 = subu(a3, a1);
                a1 = addu(a2, a1);
                a0 = a1 | a0;
                sw(a0, gp, -17208);  // 0x7CE9B8
            }
        }
        // 0x004d5f28
        charge(ctx, 7);
        lw(a1, gp, -17128);  // 0x7CEA08
        lw(a0, gp, -17124);  // g_rwDMASprBase
        v1 = addu(a1, v1);
        sw(v1, gp, -17128);  // 0x7CEA08
        v1 = a0 ^ 0x2000;
        sw(v1, gp, -17124);  // g_rwDMASprBase
        sw(v1, gp, -17148);  // 0x7CE9F4
    }
    // 0x004d5f44
    charge(ctx, 5);
    v1 = 0x10010000;
    lw(a0, v1, -12288);  // 0x1000D000 D8 fromSPR CHCR
    a0 = a0 & 0x100;
    if (a0 != 0) {
        // 0x004d5f58
        charge(ctx, 4);
        a0 = 256;
        sw(a0, v1, -8160);
        sync(ctx, 0);
        sync(ctx, 16);
        for (;;) {
            // 0x004d5f68
            charge(ctx, 7);
            if (cop0_cond(ctx)) {
                break;
            }
            backedge(ctx);
        }
        // 0x004d5f84
        charge(ctx, 2);
    }
    // 0x004d5fd0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x004D5FE0 sub_4D5FE0 -- 612 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Reopens the current packet after an SPR flush: closes it and reopens it as a GIF or VIF packet of the same kind
// (recursive for a split packet).
void sub_4D5FE0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004d5fe0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    s2 = a1;
    sq(s0, sp, 0x0);
    if (s2 != 0) {
        // 0x004d6004
        charge(ctx, 3);
        lw(v1, gp, -17148);  // 0x7CE9F4
        v0 = 0;
        if (v1 != 0) {
            // 0x004d6010
            charge(ctx, 3);
            lw(v0, gp, -17124);  // g_rwDMASprBase
            v0 = subu(v1, v0);
        }
        // 0x004d6168
        charge(ctx, 2);
        if (v0 == 0) {
            backedge(ctx);
        } else {
            // 0x004d6170
            charge(ctx, 2);
            v1 = 0x10010000;
            backedge(ctx);
            // 0x004d601c
            charge(ctx, 4);
            lw(a0, v1, -12288);
            a0 = a0 & 0x100;
            if (a0 != 0) {
                // 0x004d6178
                charge(ctx, 4);
                a0 = 256;
                sw(a0, v1, -8160);
                sync(ctx, 0);
                sync(ctx, 16);
                for (;;) {
                    // 0x004d6188
                    charge(ctx, 7);
                    if (cop0_cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004d61a4
                charge(ctx, 2);
                a2 = 256;
                backedge(ctx);
            } else {
                // 0x004d602c
                charge(ctx, 1);
                a2 = 256;
            }
            // 0x004d6030
            charge(ctx, 14);
            v1 = 0x10010000;
            sw(a2, v1, -8176);  // 0x1000E010 D_STAT
            a0 = srl(v0, 4);
            lw(a1, gp, -17124);  // g_rwDMASprBase
            sw(a1, v1, -12160);  // 0x1000D080 D8 fromSPR SADR
            lw(a1, gp, -17128);  // 0x7CEA08
            sw(a1, v1, -12272);  // 0x1000D010 D8 fromSPR MADR
            sw(a0, v1, -12256);  // 0x1000D020 D8 fromSPR QWC
            sw(a2, v1, -12288);  // 0x1000D000 D8 fromSPR CHCR
            sync(ctx, 0);
            sync(ctx, 16);
            lw(a2, gp, -17208);  // 0x7CE9B8
            if (a2 != 0) {
                // 0x004d6068
                charge(ctx, 5);
                a0 = si(-16384);
                v1 = 0x70000000;
                a0 = a2 & a0;
                if (a0 == v1) {
                    // 0x004d607c
                    charge(ctx, 7);
                    lw(a0, gp, -17124);  // g_rwDMASprBase
                    v1 = 0x20000000;
                    lw(a1, gp, -17128);  // 0x7CEA08
                    a0 = subu(a2, a0);
                    a0 = addu(a1, a0);
                    v1 = a0 | v1;
                    sw(v1, gp, -17208);  // 0x7CE9B8
                }
            }
            // 0x004d6098
            charge(ctx, 7);
            lw(a0, gp, -17128);  // 0x7CEA08
            lw(v1, gp, -17124);  // g_rwDMASprBase
            v0 = addu(a0, v0);
            sw(v0, gp, -17128);  // 0x7CEA08
            v0 = v1 ^ 0x2000;
            sw(v0, gp, -17124);  // g_rwDMASprBase
            sw(v0, gp, -17148);  // 0x7CE9F4
        }
        // 0x004d60b4
        charge(ctx, 5);
        v0 = 0x10010000;
        lw(v1, v0, -12288);  // 0x1000D000 D8 fromSPR CHCR
        v1 = v1 & 0x100;
        if (v1 != 0) {
            // 0x004d60c8
            charge(ctx, 4);
            v1 = 256;
            sw(v1, v0, -8160);
            sync(ctx, 0);
            sync(ctx, 16);
            for (;;) {
                // 0x004d60d8
                charge(ctx, 7);
                if (cop0_cond(ctx)) {
                    break;
                }
                backedge(ctx);
            }
        }
    }
    // 0x004d60f4
    charge(ctx, 3);
    at = sltiu(s3, 128);
    if (at == 0) {
        // 0x004d6108
        charge(ctx, 1);
        v0 = 127;
    } else {
        // 0x004d6100
        charge(ctx, 2);
        v0 = 63;
    }
    // 0x004d610c
    charge(ctx, 10);
    lw(v1, gp, -17180);  // 0x7CE9D4
    a0 = nor(v0, 0);
    v0 = addu(s3, v0);
    lw(a2, gp, -17184);  // 0x7CE9D0
    s3 = a0 & v0;
    v0 = v1 & a0;
    v0 = subu(v0, s3);
    at = sltu(a2, v0);
    if (at != 0) {
        // 0x004d61ac
        charge(ctx, 3);
        sw(v1, gp, -17172);  // 0x7CE9DC
        sw(v0, gp, -17180);  // 0x7CE9D4
    L_004d6228:
        charge(ctx, 1);
        ld(ra, sp, 0x40);
    } else {
        // 0x004d6134
        charge(ctx, 11);
        lw(a1, gp, -17128);  // 0x7CEA08
        a0 = si(-128);
        lw(v0, gp, -17164);  // 0x7CE9E4
        v1 = addiu(s3, 128);
        a1 = subu(a2, a1);
        a1 = addiu(a1, 159);
        s1 = a1 & a0;
        v1 = addu(v1, s1);
        at = sltu(v0, v1);
        if (at != 0) {
            // 0x004d6160
            charge(ctx, 2);
            v0 = 0;
            goto L_004d6228;
        }
        // 0x004d61b8
        charge(ctx, 10);
        link(ctx, 0x4D61B8u);  // $ra first: the delay slot below depends on it
        lw(s0, gp, -17212);  // 0x7CE9B4
        call(ctx, gen::fn__rwDMAClosePkt_004d4a60);
        lbu(a0, gp, -17168);  // 0x7CE9E0
        v1 = addiu(gp, -17160);  // &0x7CE9E8
        lw(v0, gp, -17192);  // 0x7CE9C8
        a0 = sll(a0, 2);
        v1 = addu(v1, a0);
        lw(v1, v1, 0);
        if (v1 != v0) {
            // 0x004d61e0
            charge(ctx, 2);
            jal(ctx, 0x4D61E0u, gen::fn__rwDMAForceBufferSwap_004d4df0);
        }
        // 0x004d61e8
        charge(ctx, 3);
        v0 = 258;
        if (s0 == v0) {
            // 0x004d6218
            charge(ctx, 4);
            a0 = srl(s1, 4);
            jal(ctx, 0x4D6218u, gen::fn__rwDMAOpenGIFPkt_004d54e0);
            a0 = s3;
            backedge(ctx);
        } else {
            // 0x004d61f4
            charge(ctx, 5);
            v0 = lui(0x8000);
            a1 = srl(s1, 4);
            a0 = s0 & v0;
            jal(ctx, 0x4D61FCu, gen::fn__rwDMAOpenVIFPkt_004d59d0);
            a0 = s3;
        }
        // 0x004d6208
        charge(ctx, 4);
        a1 = s2;
        jal(ctx, 0x4D6208u, gen::fn_sub_4D5FE0_004d5fe0);
        ld(ra, sp, 0x40);
    }
    // 0x004d622c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x004D6250 sub_4D6250 -- 536 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Builds the flip packet (rwDMAFlipData) for the display swap and queues it.
void sub_4D6250(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004d6250
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    a0 = 0;
    a1 = 2;
    jal(ctx, 0x4D626Cu, gen::fn__rwDMAOpenVIFPkt_004d59d0);
    if (v0 == 0) {
        // 0x004d63f8
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004d627c
        charge(ctx, 3);
        lw(a0, gp, -17152);  // 0x7CE9F0
        if (a0 != 0) {
            // 0x004d6288
            charge(ctx, 7);
            lw(v1, gp, -17176);  // 0x7CE9D8
            v0 = addiu(s0, 4);
            v0 = sll(v0, 4);
            v1 = subu(v1, a0);
            v0 = sltu(v1, v0);
            if (v0 != 0) {
                goto L_004d6400;
            }
            // 0x004d62a4
            charge(ctx, 4);
            v0 = lui(0xCFFF);
            v1 = addiu(a0, 16);
            v0 = v0 | 0xFFFF;
            v0 = v1 & v0;
        L_004d62b4:
            charge(ctx, 3);
            lw(a2, gp, -17152);  // 0x7CE9F0
            if (a2 == 0) {
                // 0x004d632c
                charge(ctx, 1);
                sw(v0, gp, -17200);  // 0x7CE9C0
            } else {
                // 0x004d62c0
                charge(ctx, 27);
                lw(a0, gp, -17304);  // 0x7CE958
                v1 = 0x50000000;
                v1 = v1 | 0x3;
                a1 = 0;
                a0 = addiu(a0, 1008);
                a0 = dsll32(a0, 0);
                a0 = dsrl32(a0, 0);
                a0 = dsll32(a0, 0);
                v1 = a0 | v1;
                pcpyld(v1, a1, v1);
                sq(v1, a2, -48);
                a0 = 0x10000000;
                v1 = 64;
                a0 = dsll32(a0, 0);
                a1 = 14;
                v1 = v1 | a0;
                pcpyld(v1, a1, v1);
                a0 = dsll32(v0, 0);
                sq(v1, a2, 0);
                a0 = dsrl32(a0, 0);
                v1 = 0x20000000;
                a0 = dsll32(a0, 0);
                a1 = 0;
                v1 = a0 | v1;
                pcpyld(v1, a1, v1);
                sq(v1, a2, 16);
            }
            // 0x004d6330
            charge(ctx, 4);
            v1 = 0x30000000;
            v0 = v0 | v1;
            sw(v0, gp, -17152);  // 0x7CE9F0
            if (s1 != 0) {
                // 0x004d6340
                charge(ctx, 3);
                lw(a0, gp, -17208);  // 0x7CE9B8
                if (a0 == 0) {
                    goto L_004d6434;
                }
                // 0x004d634c
                charge(ctx, 5);
                v1 = si(-16384);
                v0 = 0x70000000;
                v1 = a0 & v1;
                if (v1 != v0) {
                    // 0x004d6360
                    charge(ctx, 5);
                    v0 = 0x10010000;
                    lw(v1, v0, -12288);  // 0x1000D000 D8 fromSPR CHCR
                    v1 = v1 & 0x100;
                    if (v1 != 0) {
                        // 0x004d6374
                        charge(ctx, 4);
                        v1 = 256;
                        sw(v1, v0, -8160);
                        sync(ctx, 0);
                        sync(ctx, 16);
                        for (;;) {
                            // 0x004d6384
                            charge(ctx, 7);
                            if (cop0_cond(ctx)) {
                                break;
                            }
                            backedge(ctx);
                        }
                    }
                }
                // 0x004d63a0
                charge(ctx, 11);
                v0 = 0x960000;
                lw(v1, gp, -17208);  // 0x7CE9B8
                lq(a0, v0, 19856);  // rwDMAFlipData+0x400
                v0 = 0x960000;
                sq(a0, v1, 0);
                lq(v1, v0, 19840);  // rwDMAFlipData+0x3F0
                lw(v0, gp, -17148);  // 0x7CE9F4
                sq(v1, v0, 0);
                lw(v0, gp, -17148);  // 0x7CE9F4
                v1 = addiu(v0, 16);
                sw(v1, gp, -17148);  // 0x7CE9F4
                goto L_004d63cc;
            }
        L_004d6434:
            charge(ctx, 8);
            v0 = 0x960000;
            lw(v1, gp, -17148);  // 0x7CE9F4
            lq(v0, v0, 19824);  // rwDMAFlipData+0x3E0
            sq(v0, v1, 0);
            lw(v0, gp, -17148);  // 0x7CE9F4
            v1 = addiu(v0, 16);
            sw(v1, gp, -17148);  // 0x7CE9F4
            backedge(ctx);
        L_004d63cc:
            charge(ctx, 11);
            a0 = dsll32(v1, 0);
            v0 = 0x960000;
            lq(v1, v0, 19808);  // rwDMAFlipData+0x3D0
            a0 = dsra32(a0, 0);
            sq(v1, a0, 0);
            v0 = 1;
            lw(v1, gp, -17148);  // 0x7CE9F4
            sw(a0, gp, -17208);  // 0x7CE9B8
            v1 = addiu(v1, 16);
            sw(v1, gp, -17148);  // 0x7CE9F4
            // 0x004d6454 (the shared epilogue, written out on this path)
            charge(ctx, 5);
            ld(ra, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x30);
            return;
        }
    L_004d6400:
        charge(ctx, 6);
        v0 = addiu(s0, 3);
        a1 = 0;
        a0 = sll(v0, 4);
        jal(ctx, 0x4D6408u, gen::fn_sub_4D5FE0_004d5fe0);
        if (v0 != 0) {
            // 0x004d6418
            charge(ctx, 5);
            lw(a0, gp, -17172);  // 0x7CE9DC
            v1 = 0x30000000;
            v1 = a0 | v1;
            sw(v1, gp, -17176);  // 0x7CE9D8
            backedge(ctx);
            goto L_004d62b4;
        }
        // 0x004d642c
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004d6454 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x004D6470 _rwDMAHook -- 304 bytes; frame 0x10: ra sp+0x0
// Installs the RW DMA interrupt handlers (DMAC channel and VBLANK) and enables them.
void _rwDMAHook(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004d6470
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = addiu(gp, -17272);  // &0x7CE978
    sd(ra, sp, 0x0);
    sw(gp, v0, 0);  // 0x7CE978
    a1 = 0x4D0000;
    a0 = 2;
    a1 = addiu(a1, 18416);  // &_rwDMAVSYNCHandler
    a2 = 0;
    jal(ctx, 0x4D648Cu, gen::fn__sceAddIntcHandler_00502e40);
    v1 = si(-1);
    sw(v0, gp, -20288);  // 0x7CDDB0
    if (v0 != v1) {
        // 0x004d64a8
        charge(ctx, 8);
        a1 = 0x4D0000;
        a0 = 1;
        a1 = addiu(a1, 17232);  // &_rwDMAHandler
        a2 = 0;
        jal(ctx, 0x4D64B4u, gen::fn__sceAddDmacHandler_00502e70);
        v1 = si(-1);
        sw(v0, gp, -20284);  // 0x7CDDB4
        if (v0 == v1) {
            // 0x004d657c
            charge(ctx, 6);
            lw(a1, gp, -20288);  // 0x7CDDB0
            a0 = 2;
            jal(ctx, 0x4D6580u, gen::fn__sceRemoveIntcHandler_00502e60);
            v1 = si(-1);
            v0 = 0;
            sw(v1, gp, -20288);  // 0x7CDDB0
        } else {
            // 0x004d64c8
            charge(ctx, 8);
            a1 = 0x4D0000;
            a0 = 2;
            a1 = addiu(a1, 17232);  // &_rwDMAHandler
            a2 = 0;
            jal(ctx, 0x4D64D4u, gen::fn__sceAddDmacHandler_00502e70);
            v1 = si(-1);
            sw(v0, gp, -20280);  // 0x7CDDB8
            if (v0 != v1) {
                // 0x004d6518
                charge(ctx, 25);
                v0 = 1;
                a0 = 2;
                link(ctx, 0x4D6520u);  // $ra first: the delay slot below depends on it
                sb(v0, gp, -17256);  // 0x7CE988
                call(ctx, gen::fn_EnableIntc_00503ca8);
                sb(v0, gp, -17284);  // 0x7CE96C
                a0 = 1;
                jal(ctx, 0x4D652Cu, gen::fn_EnableDmac_00503d78);
                sb(v0, gp, -17280);  // 0x7CE970
                a0 = 2;
                jal(ctx, 0x4D6538u, gen::fn_EnableDmac_00503d78);
                sb(v0, gp, -17276);  // 0x7CE974
                a0 = 0x10000000;
                lw(a2, a0, 14368);  // 0x10003820 VIF0_ERR
                v1 = 0x10010000;
                a1 = si(-1795);
                v0 = 1;
                a2 = a2 | 0x2;
                sw(a2, a0, 14368);  // 0x10003820 VIF0_ERR
                lw(a2, a0, 14368);  // 0x10003820 VIF0_ERR
                a2 = a2 | 0x2;
                sw(a2, a0, 15392);  // 0x10003C20 VIF1_ERR
                lw(a0, v1, -8192);  // 0x1000E000 D_CTRL
                a0 = a0 & a1;
                sw(a0, v1, -8192);  // 0x1000E000 D_CTRL
            } else {
                // 0x004d64e8
                charge(ctx, 12);
                lw(a1, gp, -20284);  // 0x7CDDB4
                a0 = 1;
                jal(ctx, 0x4D64ECu, gen::fn__sceRemoveDmacHandler_00502e90);
                lw(a1, gp, -20288);  // 0x7CDDB0
                v0 = si(-1);
                a0 = 2;
                link(ctx, 0x4D6500u);  // $ra first: the delay slot below depends on it
                sw(v0, gp, -20284);  // 0x7CDDB4
                call(ctx, gen::fn__sceRemoveIntcHandler_00502e60);
                v1 = si(-1);
                v0 = 0;
                sw(v1, gp, -20288);  // 0x7CDDB0
            }
        }
    } else {
        // 0x004d64a0
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004d6594 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x004D65A0 _rwDMAUnhook -- 340 bytes; frame 0x10: ra sp+0x0
// Removes the RW DMA interrupt handlers after draining the queue.
void _rwDMAUnhook(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004d65a0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x4D65A8u, gen::fn__rwDMAClosePkt_004d4a60);
    lw(v0, gp, -17140);  // 0x7CE9FC
    if (v0 != 0) {
        // 0x004d65bc
        charge(ctx, 5);
        v0 = 0x10010000;
        lw(v1, v0, -12288);  // 0x1000D000 D8 fromSPR CHCR
        v1 = v1 & 0x100;
        if (v1 != 0) {
            // 0x004d6678
            charge(ctx, 4);
            v1 = 256;
            sw(v1, v0, -8160);
            sync(ctx, 0);
            sync(ctx, 16);
            for (;;) {
                // 0x004d6688
                charge(ctx, 7);
                if (cop0_cond(ctx)) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004d66a4
            charge(ctx, 2);
            lw(v0, gp, -17136);  // 0x7CEA00
            backedge(ctx);
        } else {
            // 0x004d65d0
            charge(ctx, 1);
            lw(v0, gp, -17136);  // 0x7CEA00
        }
        // 0x004d65d4
        charge(ctx, 2);
        if (v0 == 0) {
            // 0x004d6618
            charge(ctx, 6);
            lw(v1, gp, -17140);  // 0x7CE9FC
            lw(v0, gp, -17144);  // 0x7CE9F8
            sw(v1, v0, 0);
            lw(v1, gp, -17132);  // 0x7CEA04
            lw(v0, gp, -17144);  // 0x7CE9F8
            sw(v1, v0, 4);
        } else {
            // 0x004d65dc
            charge(ctx, 15);
            lw(v1, gp, -17144);  // 0x7CE9F8
            a0 = 4385;
            v0 = 290;
            sw(a0, v1, 0);
            lw(a0, gp, -17132);  // 0x7CEA04
            lw(v1, gp, -17144);  // 0x7CE9F8
            sw(a0, v1, 4);
            lw(a0, gp, -17144);  // 0x7CE9F8
            v1 = addiu(a0, 8);
            sw(v1, gp, -17144);  // 0x7CE9F8
            sw(v0, a0, 8);
            lw(v1, gp, -17136);  // 0x7CEA00
            lw(v0, gp, -17144);  // 0x7CE9F8
            sw(v1, v0, 4);
        }
        // 0x004d6630
        charge(ctx, 4);
        sw(zero, gp, -17132);  // 0x7CEA04
        sw(zero, gp, -17136);  // 0x7CEA00
        sw(zero, gp, -17140);  // 0x7CE9FC
        sw(zero, gp, -17144);  // 0x7CE9F8
    }
    // 0x004d6640
    charge(ctx, 10);
    jal(ctx, 0x4D6640u, gen::fn_sub_4D4280_004d4280);
    lbu(a0, gp, -17168);  // 0x7CE9E0
    v1 = addiu(gp, -17160);  // &0x7CE9E8
    lw(v0, gp, -17192);  // 0x7CE9C8
    a0 = sll(a0, 2);
    v1 = addu(v1, a0);
    lw(v1, v1, 0);
    if (v1 != v0) {
        // 0x004d6668
        charge(ctx, 4);
        jal(ctx, 0x4D6668u, gen::fn__rwDMAForceBufferSwap_004d4df0);
        lbu(v0, gp, -17216);  // g_rwDMABusyCount
        goto L_004d66b0;
    }
L_004d66ac:
    charge(ctx, 1);
    lbu(v0, gp, -17216);  // g_rwDMABusyCount
L_004d66b0:
    charge(ctx, 6);
    if (v0 != 0) {
        backedge(ctx);
        goto L_004d66ac;
    }
    // 0x004d66c8
    charge(ctx, 3);
    lbu(v0, gp, -17220);  // g_rwDMAFlipPending
    if (v0 != 0) {
        backedge(ctx);
        goto L_004d66ac;
    }
    // 0x004d66d4
    charge(ctx, 3);
    lbu(v0, gp, -17216);  // g_rwDMABusyCount
    if (v0 != 0) {
        backedge(ctx);
        goto L_004d66ac;
    }
    // 0x004d66e0
    charge(ctx, 5);
    jal(ctx, 0x4D66E0u, gen::fn_sub_4D6700_004d6700);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x004D67B0 _rwDMADmaOpen -- 664 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Opens the RW DMA system: allocates the packet ring, hooks the handlers, calls the init callbacks through $jalr.
void _rwDMADmaOpen(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004d67b0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, gp, -17288);  // 0x7CE968
    if (s0 == 0) {
        // 0x004d6804
        charge(ctx, 2);
        s0 = 0x100000;
        backedge(ctx);
    }
    // 0x004d67cc
    charge(ctx, 3);
    lw(v0, gp, -17292);  // 0x7CE964
    if (v0 == 0) {
        // 0x004d680c
        charge(ctx, 8);
        v0 = 0x40000;
        a1 = v0 | 0x411;
        v0 = 0x960000;
        lw(v0, v0, 376);  // 0x960178
        a0 = addiu(s0, 128);
        jalr(ctx, 0x4D681Cu, v0.u());
        sw(v0, gp, -17292);  // 0x7CE964
        if (v0 != 0) {
            // 0x004d682c
            charge(ctx, 2);
            sw(zero, gp, -17288);  // 0x7CE968
            backedge(ctx);
            goto L_004d67d8;
        }
        // 0x004d6834
        charge(ctx, 2);
        v0 = 0;
        // 0x004d6a34 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(ra, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
L_004d67d8:
    charge(ctx, 6);
    v1 = addiu(v0, 127);
    v0 = si(-128);
    s1 = v1 & v0;
    jal(ctx, 0x4D67E0u, gen::fn__rwDMAHook_004d6470);
    if (v0 != 0) {
        // 0x004d6854
        charge(ctx, 35);
        a0 = addiu(s1, 2048);
        a2 = 0;
        v1 = addiu(a0, 128);
        a1 = si(-128);
        v0 = addiu(v1, -8);
        sw(v1, gp, -17184);  // 0x7CE9D0
        sw(v0, gp, -17188);  // 0x7CE9CC
        t0 = 0;
        v0 = 0;
        sw(s1, gp, -17304);  // 0x7CE958
        pcpyld(a3, a2, v0);
        sb(zero, gp, -17168);  // 0x7CE9E0
        lhu(v0, gp, -20292);  // 0x7CDDAC
        a2 = s1;
        sw(a0, gp, -17160);  // 0x7CE9E8
        sh(zero, gp, -17264);  // 0x7CE980
        sh(zero, gp, -17268);  // 0x7CE97C
        sw(a0, gp, -17192);  // 0x7CE9C8
        sw(zero, gp, -17148);  // 0x7CE9F4
        v0 = sll(v0, 2);
        sw(zero, gp, -17152);  // 0x7CE9F0
        v0 = addiu(v0, 2048);
        sw(zero, gp, -17196);  // 0x7CE9C4
        v0 = subu(s0, v0);
        sw(zero, gp, -17204);  // 0x7CE9BC
        v0 = srl(v0, 1);
        sw(zero, gp, -17212);  // 0x7CE9B4
        a1 = v0 & a1;
        v1 = addu(a0, a1);
        sw(a1, gp, -17164);  // 0x7CE9E4
        v0 = addu(v1, a1);
        sw(v1, gp, -17156);  // 0x7CE9EC
        sw(v0, gp, -17260);  // 0x7CE984
        sw(v1, gp, -17180);  // 0x7CE9D4
        sw(v1, gp, -17172);  // 0x7CE9DC
        for (;;) {
            // 0x004d68e0
            charge(ctx, 12);
            sq(a3, a2, 0);
            t0 = addiu(t0, 8);
            sq(a3, a2, 16);
            v0 = slti(t0, 128);
            sq(a3, a2, 32);
            sq(a3, a2, 48);
            sq(a3, a2, 64);
            sq(a3, a2, 80);
            sq(a3, a2, 96);
            sq(a3, a2, 112);
            a2 = addiu(a2, 128);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004d6910
        charge(ctx, 23);
        v0 = 0x6000000;
        v1 = 0x11000000;
        a0 = dsll32(v0, 0);
        pcpyld(a0, a0, v1);
        sq(a0, s1, 112);
        v0 = v0 | 0x8000;
        a0 = 0;
        pcpyld(v0, a0, v0);
        sq(v0, s1, 512);
        v0 = 0x13000000;
        v0 = dsll32(v0, 0);
        t0 = v1 | v0;
        v0 = 0x60000000;
        v1 = v0 | 0x40;
        pcpyld(a0, a0, v1);
        pcpyld(v1, t0, t0);
        sq(v1, s1, 528);
        v0 = 127;
        v1 = 0;
        sq(a0, s1, 1008);
        pcpyld(a2, v0, v1);
        v1 = 64;
        a0 = addiu(s1, 1024);
        for (;;) {
            // 0x004d696c
            charge(ctx, 12);
            sq(a2, a0, 0);
            v1 = addiu(v1, 8);
            sq(a2, a0, 16);
            v0 = slti(v1, 128);
            sq(a2, a0, 32);
            sq(a2, a0, 48);
            sq(a2, a0, 64);
            sq(a2, a0, 80);
            sq(a2, a0, 96);
            sq(a2, a0, 112);
            a0 = addiu(a0, 128);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004d699c
        charge(ctx, 38);
        v1 = dsll32(s1, 0);
        v0 = sll(a1, 1);
        v1 = dsrl32(v1, 0);
        v0 = addu(s1, v0);
        a3 = dsll32(v1, 0);
        a1 = addiu(v0, 2047);
        v1 = 0x30000000;
        v0 = 0x960000;
        a2 = v1 | 0x21;
        a0 = s1;
        a2 = a3 | a2;
        v1 = v1 | 0x22;
        pcpyld(a2, t0, a2);
        sq(a2, v0, 19856);  // rwDMAFlipData+0x400
        v1 = a3 | v1;
        pcpyld(a2, t0, v1);
        v0 = 0x960000;
        v1 = 0x10000000;
        sq(a2, v0, 19824);  // rwDMAFlipData+0x3E0
        pcpyld(a3, t0, v1);
        v0 = 0x960000;
        a2 = 0;
        sq(a3, v0, 19840);  // rwDMAFlipData+0x3F0
        pcpyld(v1, a2, v1);
        v0 = 0x960000;
        link(ctx, 0x4D6A00u);  // $ra first: the delay slot below depends on it
        sq(v1, v0, 19808);
        call(ctx, gen::fn_SyncDCache_00503a58);
        v0 = 0x70000000;
        sb(zero, gp, -17216);  // g_rwDMABusyCount
        sw(v0, gp, -17124);  // g_rwDMASprBase
        sw(zero, gp, -17128);  // 0x7CEA08
        v0 = 1;
        sw(zero, gp, -17132);  // 0x7CEA04
        sw(zero, gp, -17136);  // 0x7CEA00
        sw(zero, gp, -17140);  // 0x7CE9FC
        sb(zero, gp, -17220);  // g_rwDMAFlipPending
        sw(zero, gp, -17208);  // 0x7CE9B8
        sb(zero, gp, -17252);  // 0x7CE98C
    } else {
        // 0x004d67f0
        charge(ctx, 3);
        lw(v0, gp, -17288);  // 0x7CE968
        if (v0 == 0) {
            // 0x004d683c
            charge(ctx, 6);
            v0 = 0x960000;
            lw(v0, v0, 380);  // 0x96017C
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x4D6844u);  // $ra = the return address
            lw(a0, gp, -17292);  // 0x7CE964
            call_ptr(ctx, jt);
            backedge(ctx);
        }
        // 0x004d67fc
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004d6a34 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x004D6A50 _rwDMADmaClose -- 84 bytes; frame 0x10: ra sp+0x0
// Closes the RW DMA system: unhooks and calls the close callback through $jalr.
void _rwDMADmaClose(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004d6a50
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x4D6A58u, gen::fn__rwDMAUnhook_004d65a0);
    lw(v1, gp, -17288);  // 0x7CE968
    sw(zero, gp, -17304);  // 0x7CE958
    if (v1 == 0) {
        // 0x004d6a80
        charge(ctx, 6);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        jt = v0.u();  // the target, read before the delay slot
        link(ctx, 0x4D6A88u);  // $ra = the return address
        lw(a0, gp, -17292);  // 0x7CE964
        call_ptr(ctx, jt);
        sw(zero, gp, -17292);  // 0x7CE964
        backedge(ctx);
    } else {
        // 0x004d6a6c
        charge(ctx, 1);
        sw(zero, gp, -17292);  // 0x7CE964
    }
    // 0x004d6a70
    charge(ctx, 4);
    sw(zero, gp, -17288);  // 0x7CE968
    sw(zero, gp, -17300);  // g_rwDMAWaitCallback
    sb(zero, gp, -17296);  // 0x7CE960
    // 0x004d6a98
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x004D6AB0 _rwDMAPreAlloc -- 84 bytes; leaf frame (no stack)
// Sets the DMA pre-allocation (buffer, size, alignment); refuses (0) when the DMA system is open or the size is not
// 128-byte aligned. Leaf.
void _rwDMAPreAlloc(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28};
    // 0x004d6ab0
    enter(ctx, 2);  // entry check point + this block's cycles
    if (a1 == 0) {
        // 0x004d6ab8
        charge(ctx, 1);
        lhu(a1, gp, -20292);  // 0x7CDDAC
    }
    // 0x004d6abc
    charge(ctx, 3);
    lw(v0, gp, -17304);  // 0x7CE958
    if (v0 != 0) {
        // 0x004d6ae4
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004d6ac8
        charge(ctx, 2);
        if (a2 != 0) {
            // 0x004d6ad0
            charge(ctx, 3);
            v0 = a2 & 0x7F;
            if (v0 == 0) {
                // 0x004d6aec
                charge(ctx, 1);
                sw(a2, gp, -17292);  // 0x7CE964
                goto L_004d6af0;
            }
            // 0x004d6adc
            charge(ctx, 2);
            v0 = 0;
            // 0x004d6afc (the shared epilogue, written out on this path)
            charge(ctx, 2);
            return;
        }
    L_004d6af0:
        charge(ctx, 3);
        sw(a0, gp, -17288);  // 0x7CE968
        v0 = 1;
        sh(a1, gp, -20292);  // 0x7CDDAC
    }
    // 0x004d6afc (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x004D6B10 _rwSkyInitConfigSystem -- 80 bytes; frame 0x10: ra sp+0x0
// Sky system configuration: sceGsResetPath and sceDmaReset.
void _rwSkyInitConfigSystem(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004d6b10
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    cfc2(v1, 28, false);  // cfc2
    sd(ra, sp, 0x0);
    a0 = 1;
    v0 = 0x10000000;
    v1 = v1 | 0x200;
    sw(a0, v0, 15376);  // 0x10003C10 VIF1_FBRST
    sw(a0, v0, 14352);  // 0x10003810 VIF0_FBRST
    sw(a0, v0, 12288);  // 0x10003000 GIF_CTRL
    ctc2(v1, 28, false);  // ctc2
    cfc2(v0, 28, false);  // cfc2
    v0 = v0 | 0x2;
    ctc2(v0, 28, false);  // ctc2
    jal(ctx, 0x4D6B44u, gen::fn_sceGsResetPath_004f9050);
    a0 = 1;
    jal(ctx, 0x4D6B4Cu, gen::fn_sceDmaReset_004fa918);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x004DFDD0 setInitialRenderState -- 332 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Sky driver: uploads the initial GS render state in one VIF packet.
void setInitialRenderState(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004dfdd0
    enter(ctx, 83);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    v0 = 3;
    sd(ra, sp, 0x70);
    v1 = 2;
    sq(s6, sp, 0x60);
    a0 = 14;
    sq(s5, sp, 0x50);
    a1 = 8;
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    sw(v0, gp, -20260);  // 0x7CDDCC
    v0 = 0x780000;
    sw(v1, gp, -20264);  // 0x7CDDC8
    lw(a2, v0, -4144);  // 0x77EFD0
    sw(v1, gp, -16964);  // 0x7CEAAC
    sd(a1, gp, -20272);  // 0x7CDDC0
    sw(zero, gp, -16956);  // 0x7CEAB4
    sw(zero, gp, -16952);  // 0x7CEAB8
    sw(zero, gp, -16948);  // 0x7CEABC
    v0 = 96;
    sd(a2, gp, -17032);  // 0x7CEA68
    sd(v0, gp, -17040);  // 0x7CEA60
    v0 = 0x10000000;
    sd(zero, gp, -17048);  // 0x7CEA58
    v1 = dsll32(v0, 0);
    v0 = 0x8006;
    v1 = v0 | v1;
    v0 = 66;
    pcpyld(s4, a0, v1);
    pcpyld(s3, v0, a2);
    v1 = 0;
    v0 = 73;
    pcpyld(s1, v0, v1);
    pcpyld(s2, a1, v1);
    v0 = 128;
    a1 = 59;
    v1 = dsll32(v0, 0);
    a0 = 68;
    pcpyld(s0, a1, v1);
    v0 = 0x60710000;
    a1 = 7;
    v1 = v0 | 0x2435;
    v0 = 0x71600000;
    v1 = dsll32(v1, 0);
    v0 = v0 | 0x3524;
    v0 = v0 | v1;
    pcpyld(s5, a0, v0);
    v1 = 1;
    v0 = 70;
    sw(v1, gp, -16960);  // 0x7CEAB0
    a0 = lui(0x8000);
    pcpyld(s6, v0, v1);
    jal(ctx, 0x4DFEA8u, gen::fn__rwDMAOpenVIFPkt_004d59d0);
    lw(v0, gp, -17148);  // 0x7CE9F4
    a0 = 6;
    a1 = 1;
    sq(s4, v0, 0);
    sq(s3, v0, 16);
    sq(s2, v0, 32);
    sq(s1, v0, 48);
    sq(s0, v0, 64);
    sq(s5, v0, 80);
    sq(s6, v0, 96);
    lw(v0, gp, -17148);  // 0x7CE9F4
    v0 = addiu(v0, 112);
    link(ctx, 0x4DFEE0u);  // $ra first: the delay slot below depends on it
    sw(v0, gp, -17148);  // 0x7CE9F4
    call(ctx, gen::fn__rwSkySetRenderState_004d6b90);
    a0 = 8;
    a1 = 1;
    jal(ctx, 0x4DFEECu, gen::fn__rwSkySetRenderState_004d6b90);
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

// 0x004E01B0 SkyOpen -- 912 bytes; frame 0x40: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// Sky driver open: fills the device / video-mode tables (SyncDCache on the uploaded blocks).
void SkyOpen(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f12{ctx, 12}, f13{ctx, 13}, f20{ctx, 20};
    // 0x004e01b0
    enter(ctx, 55);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    mfc0(v1, 12);
    sd(ra, sp, 0x30);
    v0 = 0x40000000;
    sq(s1, sp, 0x20);
    v1 = v0 | v1;
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    mtc0(v1, 12);
    v0 = 0x5000000;
    s1 = 0;
    a0 = dsll32(v0, 0);
    v0 = 0x1000000;
    v1 = v0 | 0x102;  // &0x1000102
    v0 = 0xF000;
    a0 = v1 | a0;
    v0 = dsll(v0, 16);
    v1 = v0 | 0xD;
    v0 = 0x960000;
    pcpyld(v1, a0, v1);
    sq(v1, v0, 21360);  // 0x965370
    v0 = 0x960000;
    sq(v1, v0, 21584);  // 0x965450
    v0 = 0x960000;
    sq(v1, v0, 21808);  // 0x965530
    v0 = 0x960000;
    sq(v1, v0, 22032);  // 0x965610
    v0 = 0x71300000;
    a2 = v0 | 0x4001;
    v0 = v0 | 0x4202;
    a0 = dsll32(v0, 0);
    v0 = 0x3F3F0000;
    v1 = v0 | 0x3F3F;
    a1 = dsll32(v1, 0);
    v0 = 0x20000000;
    a1 = v0 | a1;
    v1 = 0x960000;
    pcpyld(a1, a2, a1);
    sq(a1, v1, 21376);  // 0x965380
    v0 = 0x960000;
    v1 = 0x960000;
    sq(a1, v0, 21600);  // 0x965460
    sq(a1, v1, 21824);  // 0x965540
    v0 = 0x960000;
    v1 = 0;
    sq(a1, v0, 22048);  // 0x965620
    pcpyld(a0, a0, v1);
    v1 = 0x960000;
    v0 = 0x960000;
    sq(a0, v1, 21472);  // 0x9653E0
    sq(a0, v0, 21696);  // 0x9654C0
    v1 = 0x960000;
    v0 = 0x960000;
    sq(a0, v1, 21920);  // 0x9655A0
    sq(a0, v0, 22144);  // 0x965680
    for (;;) {
        // 0x004e028c
        charge(ctx, 4);
        v0 = 95;
        a1 = subu(v0, s1);
        v0 = a1 & 0x1;
        if (i64(a1) < 0) {
            // 0x004e029c
            charge(ctx, 2);
            if (v0 != 0) {
                // 0x004e02a4
                charge(ctx, 1);
                v0 = addiu(v0, -2);
            }
        }
        // 0x004e02a8
        charge(ctx, 2);
        if (v0 != 0) {
            // 0x004e0398
            charge(ctx, 56);
            v0 = 0x402B0000;
            v0 = v0 | 0xC9EF;
            v1 = 0x437F0000;
            mtc1(v0, f3);
            mtc1(s1, f2);
            v0 = si(-2);
            s0 = a1 & v0;
            v0 = 0x960000;
            mtc1(v1, f1);
            v0 = addiu(v0, 22032);  // &0x965610
            cvt_s_w(f2, f2);
            v1 = addu(v0, s0);
            v0 = 0x42BE0000;
            mtc1(v0, f0);
            div_s(f20, f2, f0);
            v0 = 0x43800000;
            mtc1(zero, f0);
            mtc1(v0, f12);
            adda_s(f0, f1);
            msub_s(f0, f3, f2);
            cvt_w_s(f0, f0);
            mfc1(v0, f0);
            mov_s(f13, f20);
            v0 = v0 & 0xFFFF;
            v0 = sll(v0, 4);
            link(ctx, 0x4E0400u);  // $ra first: the delay slot below depends on it
            sh(v0, v1, 128);
            call(ctx, gen::fn_powf_0052ea48);
            a0 = 0x437F0000;
            v0 = 0x43800000;
            mtc1(a0, f1);
            v1 = 0x960000;
            v1 = addiu(v1, 21808);  // &0x965530
            div_s(f0, f1, f0);
            v1 = addu(v1, s0);
            cvt_w_s(f0, f0);
            mtc1(v0, f12);
            mul_s(f13, f20, f20);
            mfc1(v0, f0);
            v0 = v0 & 0xFFFF;
            v0 = sll(v0, 4);
            link(ctx, 0x4E0440u);  // $ra first: the delay slot below depends on it
            sh(v0, v1, 128);
            call(ctx, gen::fn_powf_0052ea48);
            v1 = 0x437F0000;
            v0 = 0x960000;
            mtc1(v1, f1);
            v0 = addiu(v0, 21584);  // &0x965450
            v0 = addu(v0, s0);
            div_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v1 = v1 & 0xFFFF;
            v1 = sll(v1, 4);
            sh(v1, v0, 128);
        } else {
            // 0x004e02b0
            charge(ctx, 57);
            v0 = 0x402B0000;
            a0 = 0x437F0000;
            v1 = v0 | 0xC9EF;
            v0 = si(-2);
            mtc1(s1, f3);
            s0 = a1 & v0;
            v0 = 0x960000;
            mtc1(v1, f4);
            v0 = addiu(v0, 22032);  // &0x965610
            cvt_s_w(f3, f3);
            v1 = addu(v0, s0);
            v0 = 0x42BE0000;
            mtc1(v0, f0);
            mtc1(a0, f2);
            div_s(f20, f3, f0);
            v0 = 0x43800000;
            mtc1(zero, f1);
            mtc1(v0, f12);
            adda_s(f1, f2);
            msub_s(f1, f4, f3);
            cvt_w_s(f0, f1);
            mfc1(v0, f0);
            mov_s(f13, f20);
            v0 = v0 & 0xFFFF;
            v0 = sll(v0, 4);
            link(ctx, 0x4E0318u);  // $ra first: the delay slot below depends on it
            sh(v0, v1, 28);
            call(ctx, gen::fn_powf_0052ea48);
            a0 = 0x437F0000;
            v0 = 0x43800000;
            mtc1(a0, f1);
            v1 = 0x960000;
            v1 = addiu(v1, 21808);  // &0x965530
            div_s(f0, f1, f0);
            v1 = addu(v1, s0);
            cvt_w_s(f0, f0);
            mtc1(v0, f12);
            mul_s(f13, f20, f20);
            mfc1(v0, f0);
            v0 = v0 & 0xFFFF;
            v0 = sll(v0, 4);
            link(ctx, 0x4E0358u);  // $ra first: the delay slot below depends on it
            sh(v0, v1, 28);
            call(ctx, gen::fn_powf_0052ea48);
            v1 = 0x437F0000;
            v0 = 0x960000;
            mtc1(v1, f1);
            v0 = addiu(v0, 21584);  // &0x965450
            v0 = addu(v0, s0);
            div_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v1 = v1 & 0xFFFF;
            v1 = sll(v1, 4);
            sh(v1, v0, 28);
        }
        // 0x004e0478
        charge(ctx, 4);
        s1 = addiu(s1, 1);
        v0 = slti(s1, 96);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004e0488
    charge(ctx, 34);
    v0 = 0x960000;
    a0 = 0x960000;
    v0 = addiu(v0, 22256);  // &0x9656F0
    a0 = addiu(a0, 22032);  // &0x965610
    a1 = addiu(v0, 127);  // &0x96576F
    jal(ctx, 0x4E0498u, gen::fn_SyncDCache_00503a58);
    v0 = 0x960000;
    a0 = 0x960000;
    v0 = addiu(v0, 22032);  // &0x965610
    a0 = addiu(a0, 21808);  // &0x965530
    a1 = addiu(v0, 127);  // &0x96568F
    jal(ctx, 0x4E04B0u, gen::fn_SyncDCache_00503a58);
    v0 = 0x960000;
    a0 = 0x960000;
    v0 = addiu(v0, 21808);  // &0x965530
    a0 = addiu(a0, 21584);  // &0x965450
    a1 = addiu(v0, 127);  // &0x9655AF
    jal(ctx, 0x4E04C8u, gen::fn_SyncDCache_00503a58);
    v0 = 0x960000;
    a0 = 0x960000;
    v0 = addiu(v0, 21584);  // &0x965450
    a0 = addiu(a0, 21360);  // &0x965370
    a1 = addiu(v0, 127);  // &0x9654CF
    jal(ctx, 0x4E04E0u, gen::fn_SyncDCache_00503a58);
    v0 = 0x960000;
    v0 = addiu(v0, 22032);  // &0x965610
    sw(v0, gp, -16924);  // 0x7CEAD4
    v0 = 89;
    sw(v0, gp, -16928);  // 0x7CEAD0
    v0 = 0x780000;
    lw(v1, v0, -4240);  // videoModes+0x860
    v0 = 32;
    sw(zero, gp, -16936);  // 0x7CEAC8
    if (v1 != v0) {
        // 0x004e051c
        charge(ctx, 2);
        v0 = 256;
        sw(v0, gp, -16932);  // 0x7CEACC
    } else {
        // 0x004e0510
        charge(ctx, 3);
        v0 = 1280;
        sw(v0, gp, -16932);  // 0x7CEACC
    }
    // 0x004e0524 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lwc1(f20, sp, 0x0);
    lq(s1, sp, 0x20);
    v0 = 1;
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0x40);
}

// 0x004E0540 sub_4E0540 -- 1740 bytes; frame 0x100: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// SkyStart helper: computes the display mode (customMode, g_skyDisplayMode) and the frame-buffer layout.
void sub_4E0540(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4};
    // 0x004e0540
    enter(ctx, 31);  // entry check point + this block's cycles
    sp = addiu(sp, -0x100);
    v0 = 0x41000000;
    sd(ra, sp, 0x90);
    mtc1(v0, f4);
    sq(fp, sp, 0x80);
    v1 = 0x960000;
    sq(s7, sp, 0x70);
    v0 = 0x960000;
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lwc1(f3, v1, 22320);  // customMode
    lwc1(f2, v0, 22344);  // g_skyDisplayMode
    cvt_s_w(f3, f3);
    v1 = 0x3F000000;
    v0 = 0x4F000000;
    cvt_s_w(f2, f2);
    mul_s(f3, f4, f3);
    div_s(f2, f3, f2);
    mtc1(v1, f1);
    mtc1(v0, f0);
    add_s(f1, f1, f2);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x004e05cc
        charge(ctx, 6);
        sub_s(f0, f1, f0);
        v0 = lui(0x8000);
        cvt_w_s(f0, f0);
        mfc1(s5, f0);
        s5 = s5 | v0;
    } else {
        // 0x004e05bc
        charge(ctx, 4);
        cvt_w_s(f0, f1);
        mfc1(s5, f0);
    }
    // 0x004e05e4
    charge(ctx, 22);
    v0 = 0x960000;
    v1 = 0x960000;
    lw(a0, v0, 22324);  // customMode+0x4
    lw(a2, v1, 22348);  // g_skyDisplayMode+0x4
    mtc1(a0, f3);
    v0 = 0x4F000000;
    v1 = 0x41000000;
    cvt_s_w(f3, f3);
    mtc1(v1, f4);
    mtc1(a2, f2);
    mul_s(f3, f4, f3);
    v1 = 0x3F000000;
    cvt_s_w(f2, f2);
    div_s(f2, f3, f2);
    mtc1(v1, f1);
    mtc1(v0, f0);
    add_s(f1, f1, f2);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x004e064c
        charge(ctx, 6);
        sub_s(f0, f1, f0);
        v0 = lui(0x8000);
        cvt_w_s(f0, f0);
        mfc1(s1, f0);
        s1 = s1 | v0;
    } else {
        // 0x004e063c
        charge(ctx, 4);
        cvt_w_s(f0, f1);
        mfc1(s1, f0);
    }
    // 0x004e0664
    charge(ctx, 18);
    mtc1(a0, f0);
    v0 = 0x41800000;
    mtc1(v0, f1);
    v1 = 0x3F000000;
    cvt_s_w(f0, f0);
    v0 = 0x4F000000;
    mul_s(f2, f1, f0);
    mtc1(a2, f1);
    mtc1(v1, f0);
    cvt_s_w(f1, f1);
    div_s(f1, f2, f1);
    add_s(f1, f0, f1);
    mtc1(v0, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x004e06bc
        charge(ctx, 7);
        sub_s(f0, f1, f0);
        v0 = lui(0x8000);
        cvt_w_s(f0, f0);
        mfc1(s0, f0);
        s0 = s0 | v0;
        v0 = 0x70000000;
    } else {
        // 0x004e06ac
        charge(ctx, 4);
        cvt_w_s(f0, f1);
        mfc1(s0, f0);
        v0 = 0x70000000;
    }
    // 0x004e06d8
    charge(ctx, 27);
    a0 = dsll32(s5, 0);
    v0 = v0 | 0x13;
    a0 = dsrl32(a0, 0);
    sq(v0, sp, 0xD0);
    s2 = 0;
    v0 = 0x10000000;
    s7 = 0;
    v1 = dsll32(v0, 0);
    fp = 0;
    v0 = 0x8012;
    sd(zero, sp, 0xE8);
    v0 = v0 | v1;
    sq(v0, sp, 0xC0);
    v1 = 0x7FFF0000;
    v0 = dsll32(v1, 0);
    v0 = v1 | v0;
    sq(v0, sp, 0xB0);
    v0 = 0x3F800000;
    v0 = dsll32(v0, 0);
    link(ctx, 0x4E0724u);  // $ra first: the delay slot below depends on it
    sq(v0, sp, 0xA0);
    call(ctx, gen::fn___floatdisf_0052eb60);
    v0 = 0x46800000;
    sd(zero, sp, 0xE0);
    mtc1(v0, f1);
    div_s(f0, f0, f1);
    swc1(f0, sp, 0xFC);
    for (;;) {
        // 0x004e0744
        charge(ctx, 2);
        if (s2 == 0) {
            // 0x004e0bc4
            charge(ctx, 3);
            s3 = 0x960000;
            s3 = addiu(s3, 19904);  // &rwDMAFlipData+0x430
            backedge(ctx);
        } else {
            // 0x004e074c
            charge(ctx, 3);
            v0 = 1;
            if (s2 == v0) {
                // 0x004e0bd0
                charge(ctx, 3);
                s3 = 0x960000;
                s3 = addiu(s3, 20224);  // &0x964F00
                backedge(ctx);
            } else {
                // 0x004e0758
                charge(ctx, 3);
                v0 = 2;
                if (s2 != v0) {
                    // 0x004e0770
                    charge(ctx, 2);
                    s3 = 0x960000;
                    s3 = addiu(s3, 20864);  // &0x965180
                } else {
                    // 0x004e0764
                    charge(ctx, 3);
                    s3 = 0x960000;
                    s3 = addiu(s3, 20544);  // &0x965040
                }
            }
        }
        // 0x004e0778
        charge(ctx, 5);
        v0 = 0x960000;
        lw(v0, v0, 22356);  // g_skyDisplayMode+0xC
        v0 = v0 & 0x2;
        if (v0 == 0) {
            // 0x004e0794
            charge(ctx, 2);
            v0 = s2 & 0x2;
            s6 = sltu(0, v0);
        } else {
            // 0x004e078c
            charge(ctx, 2);
            s6 = 0;
        }
        // 0x004e079c
        charge(ctx, 8);
        lq(v0, sp, 0xD0);
        v1 = 14;
        pcpyld(v0, s7, v0);
        sq(v0, s3, 0);
        lq(v0, sp, 0xC0);
        pcpyld(v0, v1, v0);
        sq(v0, s3, 16);
        if (s6 == 0) {
            // 0x004e07f4
            charge(ctx, 13);
            lw(a2, s4, 16);
            v0 = 0x960000;
            lw(v1, v0, 22344);  // g_skyDisplayMode
            a0 = dsll32(a2, 12);
            a0 = dsrl32(a0, 27);
            v1 = sra(v1, 6);
            a0 = sll(a0, 24);
            v1 = sll(v1, 16);
            v0 = a2 & 0x1FF;
            v1 = a0 | v1;
            v0 = v0 | v1;
            v1 = dsll32(v0, 0);
            v1 = dsrl32(v1, 0);
        } else {
            // 0x004e07bc
            charge(ctx, 14);
            lw(a2, s4, 864);
            v0 = 0x960000;
            lw(v1, v0, 22344);  // g_skyDisplayMode
            a0 = dsll32(a2, 12);
            a0 = dsrl32(a0, 27);
            v1 = sra(v1, 6);
            a0 = sll(a0, 24);
            v1 = sll(v1, 16);
            v0 = a2 & 0x1FF;
            v1 = a0 | v1;
            v0 = v0 | v1;
            v1 = dsll32(v0, 0);
            v1 = dsrl32(v1, 0);
        }
        // 0x004e0828
        charge(ctx, 48);
        v0 = 76;
        a0 = 0x960000;
        pcpyld(v0, v0, v1);
        sq(v0, s3, 32);
        v1 = 64;
        v0 = 24;
        pcpyld(v0, v0, fp);
        sq(v0, s3, 48);
        lq(v0, sp, 0xB0);
        pcpyld(v0, v1, v0);
        sq(v0, s3, 64);
        v1 = 71;
        v0 = 0x30000;
        pcpyld(v0, v1, v0);
        sq(v0, s3, 80);
        ld(v1, s4, 480);
        v0 = 1;
        a2 = dsll32(v0, 0);
        a3 = dsll32(v1, 4);
        a3 = dsrl32(a3, 28);
        v1 = v1 & 0x1FF;
        a3 = dsll(a3, 24);
        a2 = a3 | a2;
        a2 = a2 | v1;
        v1 = 78;
        pcpyld(v1, v1, a2);
        sq(v1, s3, 96);
        lw(v1, a0, 22352);  // g_skyDisplayMode+0x8
        at = sltiu(v1, 24);
        if (at == 0) v0 = 0;
        v1 = 69;
        pcpyld(v0, v1, v0);
        sq(v0, s3, 112);
        v1 = s2 & 0x1;
        v0 = 0x960000;
        lw(a0, v0, 22324);  // customMode+0x4
        v0 = 0x960000;
        a0 = daddiu(a0, -1);
        lw(v0, v0, 22320);  // customMode
        a0 = dsll32(a0, 2);
        v0 = daddiu(v0, -1);
        v0 = dsll(v0, 14);
        v0 = a0 | v0;
        a0 = v0 | 0xA;
        v0 = 8;
        pcpyld(v0, v0, a0);
        sq(v0, s3, 128);
        if (v1 == 0) {
            // 0x004e0948
            charge(ctx, 23);
            v0 = 10;
            ld(a3, s4, 96);
            a0 = dsll32(v0, 0);
            v0 = 0xA800;
            v1 = dsll(v0, 16);
            v0 = 0x960000;
            a0 = v1 | a0;
            lw(v1, v0, 22320);  // customMode
            a2 = dsll32(a3, 2);
            a2 = dsrl32(a2, 26);
            a2 = dsll(a2, 20);
            a0 = a2 | a0;
            v0 = a3 & 0x1FF;
            v1 = srl(v1, 6);
            v0 = dsll32(v0, 0);
            v1 = sll(v1, 14);
            v0 = dsra32(v0, 0);
            v1 = dsll32(v1, 0);
            v0 = sll(v0, 5);
            v1 = dsrl32(v1, 0);
            v0 = v0 & 0x3FFF;
            v1 = a0 | v1;
            v1 = v0 | v1;
        } else {
            // 0x004e08e8
            charge(ctx, 24);
            v0 = 10;
            ld(a3, s4, 464);
            a0 = dsll32(v0, 0);
            v0 = 0xA800;
            v1 = dsll(v0, 16);
            v0 = 0x960000;
            a0 = v1 | a0;
            lw(v1, v0, 22320);  // customMode
            a2 = dsll32(a3, 2);
            a2 = dsrl32(a2, 26);
            a2 = dsll(a2, 20);
            a0 = a2 | a0;
            v0 = a3 & 0x1FF;
            v1 = srl(v1, 6);
            v0 = dsll32(v0, 0);
            v1 = sll(v1, 14);
            v0 = dsra32(v0, 0);
            v1 = dsll32(v1, 0);
            v0 = sll(v0, 5);
            v1 = dsrl32(v1, 0);
            v0 = v0 & 0x3FFF;
            v1 = a0 | v1;
            v1 = v0 | v1;
        }
        // 0x004e09a4
        charge(ctx, 16);
        v0 = 6;
        pcpyld(v0, v0, v1);
        sq(v0, s3, 144);
        v1 = 97;
        v0 = 20;
        pcpyld(v0, v0, v1);
        ld(v1, sp, 0xE8);
        sq(v0, s3, 160);
        v0 = 22;
        pcpyld(v0, v1, v0);
        sq(v0, s3, 176);
        v1 = 1;
        lq(v0, sp, 0xA0);
        pcpyld(v0, v1, v0);
        sq(v0, s3, 192);
        if (s6 == 0) {
            // 0x004e09ec
            charge(ctx, 1);
            v0 = s1;
        } else {
            // 0x004e09e4
            charge(ctx, 2);
            v0 = s0;
        }
        // 0x004e09f0
        charge(ctx, 24);
        a0 = dsll32(v0, 0);
        a0 = dsrl32(a0, 0);
        jal(ctx, 0x4E09F4u, gen::fn___floatdisf_0052eb60);
        v0 = 0x46800000;
        v1 = 5;
        mtc1(v0, f1);
        a0 = 0x960000;
        div_s(f0, f0, f1);
        ld(v0, sp, 0xE0);
        pcpyld(a1, v1, v0);
        swc1(f0, sp, 0xF8);
        lwu(v1, sp, 0xF8);
        lwu(v0, sp, 0xFC);
        v1 = dsll32(v1, 0);
        v1 = v1 | v0;
        v0 = 2;
        pcpyld(v0, v0, v1);
        sq(v0, s3, 208);
        sq(a1, s3, 224);
        lw(v0, a0, 22320);  // customMode
        v0 = sll(v0, 4);
        v0 = addu(v0, s5);
        if (i64(v0) < 0) {
            // 0x004e0a5c
            charge(ctx, 7);
            v1 = srl(v0, 1);
            v0 = v0 & 0x1;
            v1 = v1 | v0;
            mtc1(v1, f0);
            cvt_s_w(f1, f0);
            add_s(f1, f1, f1);
        } else {
            // 0x004e0a50
            charge(ctx, 3);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
        }
        // 0x004e0a78
        charge(ctx, 8);
        v0 = 0x46800000;
        mtc1(v0, f0);
        div_s(f0, f1, f0);
        swc1(f0, sp, 0xF4);
        if (s6 == 0) {
            // 0x004e0aa0
            charge(ctx, 1);
            v1 = s1;
        } else {
            // 0x004e0a98
            charge(ctx, 2);
            v1 = s0;
        }
        // 0x004e0aa4
        charge(ctx, 6);
        v0 = 0x960000;
        lw(v0, v0, 22324);  // customMode+0x4
        v0 = sll(v0, 4);
        v0 = addu(v0, v1);
        if (i64(v0) < 0) {
            // 0x004e0ac8
            charge(ctx, 7);
            v1 = srl(v0, 1);
            v0 = v0 & 0x1;
            v1 = v1 | v0;
            mtc1(v1, f0);
            cvt_s_w(f1, f0);
            add_s(f1, f1, f1);
        } else {
            // 0x004e0abc
            charge(ctx, 3);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
        }
        // 0x004e0ae4
        charge(ctx, 43);
        v0 = 0x46800000;
        a2 = 0x960000;
        mtc1(v0, f0);
        v1 = 0x960000;
        a0 = s3;
        div_s(f0, f1, f0);
        v0 = addiu(s3, 320);
        a1 = addiu(v0, 127);
        swc1(f0, sp, 0xF0);
        lwu(a3, sp, 0xF0);
        lwu(v0, sp, 0xF4);
        a3 = dsll32(a3, 0);
        a3 = a3 | v0;
        v0 = 2;
        pcpyld(v0, v0, a3);
        sq(v0, s3, 240);
        lw(v0, v1, 22344);  // g_skyDisplayMode
        lw(a2, a2, 22348);  // g_skyDisplayMode+0x4
        v0 = sll(v0, 4);
        v1 = sll(a2, 20);
        v0 = v1 | v0;
        v1 = dsll32(v0, 0);
        v1 = dsra32(v1, 0);
        v0 = 5;
        pcpyld(v0, v0, v1);
        sq(v0, s3, 256);
        ld(v1, gp, -17064);  // 0x7CEA48
        v0 = 24;
        pcpyld(v0, v0, v1);
        sq(v0, s3, 272);
        ld(v1, s4, 96);
        v0 = 76;
        pcpyld(v0, v0, v1);
        sq(v0, s3, 288);
        ld(v1, s4, 112);
        v0 = 78;
        pcpyld(v0, v0, v1);
        link(ctx, 0x4E0B78u);  // $ra first: the delay slot below depends on it
        sq(v0, s3, 304);
        call(ctx, gen::fn_SyncDCache_00503a58);
        s2 = addiu(s2, 1);
        v1 = sltiu(s2, 4);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004e0b90
    charge(ctx, 13);
    a0 = 0x960000;
    v1 = 0x960000;
    a0 = addiu(a0, 19904);  // &rwDMAFlipData+0x430
    v1 = addiu(v1, 20224);  // &0x964F00
    sw(a0, s4, 960);
    a0 = 0x960000;
    sw(v1, s4, 964);
    a0 = addiu(a0, 20544);  // &0x965040
    v1 = 0x960000;
    v1 = addiu(v1, 20864);  // &0x965180
    sw(a0, s4, 968);
    sw(v1, s4, 972);
    // 0x004e0bdc
    charge(ctx, 12);
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

// 0x004E1060 SkyStart -- 6928 bytes; frame 0xD0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Sky driver start: video mode, frame buffers, DMA open, the initial render state, the pipelines.
void SkyStart(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, t8{ctx, 24}, t9{ctx, 25}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5};
    // 0x004e1060
    enter(ctx, 215);  // entry check point + this block's cycles
    sp = addiu(sp, -0xD0);
    t4 = 1;
    sd(ra, sp, 0x90);
    v0 = 0x960000;
    sq(fp, sp, 0x80);
    a2 = si(-32768);
    sq(s7, sp, 0x70);
    v1 = 0;
    sq(s6, sp, 0x60);
    a0 = si(-1);
    sq(s5, sp, 0x50);
    a3 = 0xFFFF;
    sq(s4, sp, 0x40);
    t3 = dsll(t4, 15);
    sq(s3, sp, 0x30);
    a1 = 1;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    ld(t0, v0, 22384);  // skyInitialClear
    v0 = lui(0xFFFF);
    a2 = t0 & a2;
    t2 = v0 | 0x7FFF;
    t5 = v0 | 0xFFF;
    v0 = 0;
    t0 = dsll32(v1, 0);
    v1 = a2 | t4;
    t1 = dsll(v0, 16);
    v0 = dsll32(a0, 0);
    t2 = v1 & t2;
    v1 = dsll(a3, 16);
    a2 = a3 | v0;
    a3 = t2 | t3;
    v1 = v1 | 0xFFFF;
    a3 = a3 & a2;
    t4 = si(-16);
    a2 = si(-16384);
    t1 = a3 | t1;
    a2 = dsll32(a2, 0);
    a3 = v1 | a2;
    a3 = t1 & a3;
    a2 = 0;
    t1 = dsll32(a2, 14);
    t2 = a3 | t0;
    a2 = si(-16385);
    a3 = dsll32(a2, 0);
    a2 = 0;
    a3 = v1 | a3;
    t0 = dsll32(a2, 15);
    a3 = t2 & a3;
    a2 = lui(0xFC00);
    t2 = a3 | t1;
    a2 = a2 | 0x7FFF;
    a3 = dsll32(a2, 0);
    a2 = 0;
    a3 = v1 | a3;
    t1 = dsll32(a2, 26);
    a3 = t2 & a3;
    a2 = lui(0xF3FF);
    t2 = a3 | t0;
    a2 = a2 | 0xFFFF;
    a3 = dsll32(a2, 0);
    a2 = 12;
    a3 = v1 | a3;
    t0 = dsll32(a2, 28);
    a3 = t2 & a3;
    a2 = 0xFFF0000;
    t1 = a3 | t1;
    a2 = a2 | 0xFFFF;
    t2 = si(-241);
    a3 = a2 | v0;
    v0 = dsll32(a2, 0);
    v0 = v1 | v0;
    a2 = 0x960000;
    pcpyld(v0, a0, v0);
    a0 = t1 & v0;
    a0 = a0 | t0;
    v0 = 0x960000;
    ld(t0, v0, 22392);  // skyInitialClear+0x8
    t1 = si(-3841);
    sd(a0, a2, 22384);  // skyInitialClear
    a0 = lui(0xFFF0);
    a2 = a0 | 0xFFFF;
    a0 = dsll32(t4, 0);
    v0 = 14;
    t0 = t0 & t4;
    t0 = t0 | v0;
    t4 = v1 | a0;
    s0 = dsll(v0, 4);
    t0 = t0 & t2;
    t0 = t0 | s0;
    a0 = dsll32(t2, 0);
    t2 = v1 | a0;
    t7 = dsll(v0, 8);
    t0 = t0 & t1;
    a0 = dsll32(t1, 0);
    t0 = t0 | t7;
    t6 = dsll(v0, 12);
    t1 = t0 & t5;
    t3 = dsll(v0, 16);
    t0 = v1 | a0;
    t1 = t1 | t6;
    a0 = dsll32(t5, 0);
    t1 = t1 & a2;
    a2 = v1 | a0;
    t5 = t1 | t3;
    v1 = lui(0xFF0F);
    t3 = dsll(v0, 20);
    a0 = v1 | 0xFFFF;
    t1 = dsll(v0, 24);
    a0 = t5 & a0;
    v1 = lui(0xF0FF);
    a0 = a0 | t3;
    v1 = v1 | 0xFFFF;
    v1 = a0 & v1;
    t5 = dsll(v0, 28);
    v1 = v1 | t1;
    a0 = dsll32(v0, 0);
    v1 = v1 & a3;
    t3 = dsll32(v0, 4);
    t1 = dsll32(v0, 8);
    v1 = v1 | t5;
    a3 = dsll32(v0, 12);
    v0 = v1 & t4;
    a0 = v0 | a0;
    v1 = 0x960000;
    v0 = 0x960000;
    a0 = a0 & t2;
    sd(zero, v0, 22400);  // skyInitialClear+0x10
    v0 = a0 | t3;
    t0 = v0 & t0;
    a0 = 66;
    v0 = 0x960000;
    sd(a0, v0, 22408);  // skyInitialClear+0x18
    v0 = t0 | t1;
    a0 = 0x100000;
    v0 = v0 & a2;
    a2 = v0 | a3;
    sd(a2, v1, 22392);  // skyInitialClear+0x8
    v0 = 0x960000;
    sd(a0, v0, 22416);  // skyInitialClear+0x20
    v1 = 76;
    v0 = 0x960000;
    a0 = 26;
    sd(v1, v0, 22424);  // skyInitialClear+0x28
    a2 = dsll32(a1, 0);
    v0 = 0x960000;
    v1 = 0x3FF0000;
    sd(a1, v0, 22432);  // skyInitialClear+0x30
    v0 = 0x960000;
    sd(a0, v0, 22440);  // skyInitialClear+0x38
    v0 = dsll32(v1, 0);
    a0 = 64;
    v1 = v1 | v0;
    v0 = 0x960000;
    sd(v1, v0, 22448);  // skyInitialClear+0x40
    v0 = 0x960000;
    v1 = 0x30000;
    sd(a0, v0, 22456);  // skyInitialClear+0x48
    v0 = 0x960000;
    a0 = 71;
    sd(v1, v0, 22464);  // skyInitialClear+0x50
    v1 = 0x960000;
    v0 = 0x960000;
    sd(a0, v1, 22472);  // skyInitialClear+0x58
    sd(zero, v0, 22480);  // skyInitialClear+0x60
    v1 = 24;
    v0 = 0x960000;
    a0 = 78;
    sd(v1, v0, 22488);  // skyInitialClear+0x68
    v0 = 0xA000000;
    v1 = 0x960000;
    v0 = v0 | 0x100;
    a2 = v0 | a2;
    sd(a2, v1, 22496);  // skyInitialClear+0x70
    v0 = 0x960000;
    sd(a0, v0, 22504);  // skyInitialClear+0x78
    v1 = 6;
    v0 = 0x960000;
    a2 = 5;
    sd(v1, v0, 22512);  // skyInitialClear+0x80
    v0 = 0x960000;
    v1 = 0x960000;
    sd(zero, v0, 22520);  // skyInitialClear+0x88
    v0 = 0x960000;
    sd(zero, v1, 22560);  // skyInitialClear+0xB0
    sd(zero, v0, 22528);  // skyInitialClear+0x90
    v1 = 0x960000;
    v0 = 0x960000;
    sd(a1, v0, 22536);  // skyInitialClear+0x98
    v0 = 0x960000;
    sd(zero, v0, 22544);  // skyInitialClear+0xA0
    v0 = 0x960000;
    sd(a2, v0, 22552);  // skyInitialClear+0xA8
    v0 = 0x960000;
    sd(a1, v0, 22568);  // skyInitialClear+0xB8
    v0 = 0x3FFF0000;
    a0 = v0 | 0x3FFF;
    sd(a0, v1, 22576);  // skyInitialClear+0xC0
    v0 = 0x960000;
    v1 = 0x960000;
    a0 = 0x960000;
    v1 = addiu(v1, 22592);  // &0x965840
    sd(a2, v0, 22584);  // skyInitialClear+0xC8
    a1 = addiu(v1, 127);  // &0x9658BF
    a0 = addiu(a0, 22384);  // &skyInitialClear
    jal(ctx, 0x4E1394u, gen::fn_SyncDCache_00503a58);
    jal(ctx, 0x4E139Cu, gen::fn__rwSkyInitConfigSystem_004d6b10);
    a0 = 0;
    jal(ctx, 0x4E13A4u, gen::fn_sceGsSyncV_004f9938);
    lw(a0, gp, -16928);  // 0x7CEAD0
    v0 = si(-1);
    if (a0 != v0) {
        // 0x004e27dc
        charge(ctx, 46);
        v1 = sll(a0, 1);
        v0 = 0x780000;
        v1 = addu(v1, a0);
        v0 = addiu(v0, -6384);  // &videoModes
        v1 = sll(v1, 3);
        a1 = 0x960000;
        v0 = addu(v0, v1);
        t0 = 0x960000;
        lwc1(f2, v0, 12);
        a3 = 0x960000;
        lwc1(f5, v0, 0);
        t2 = 0x960000;
        lwc1(f4, v0, 4);
        t1 = 0x960000;
        lwc1(f1, v0, 16);
        a2 = 0x960000;
        lwc1(f0, v0, 20);
        a0 = 0x960000;
        lwc1(f3, v0, 8);
        v1 = 0x960000;
        swc1(f2, sp, 0xBC);
        lwc1(f2, sp, 0xBC);
        swc1(f5, sp, 0xB0);
        swc1(f1, sp, 0xC0);
        swc1(f0, sp, 0xC4);
        swc1(f4, sp, 0xB4);
        ld(t3, sp, 0xC0);
        lwc1(f1, sp, 0xB0);
        v0 = 0x960000;
        lwc1(f0, sp, 0xB4);
        swc1(f3, sp, 0xB8);
        swc1(f2, a1, 22356);  // g_skyDisplayMode+0xC
        lq(t4, sp, 0xB0);
        lw(v0, v0, 22356);  // g_skyDisplayMode+0xC
        lwc1(f3, sp, 0xB8);
        sd(t3, t1, 22336);  // customMode+0x10
        swc1(f1, t0, 22344);  // g_skyDisplayMode
        swc1(f0, a3, 22348);  // g_skyDisplayMode+0x4
        lwc1(f1, sp, 0xC0);
        lwc1(f0, sp, 0xC4);
        sq(t4, t2, 22320);  // customMode
        v0 = v0 & 0x100;
        swc1(f3, a2, 22352);  // g_skyDisplayMode+0x8
        swc1(f1, a0, 22360);  // g_skyDisplayMode+0x10
        swc1(f0, v1, 22364);  // g_skyDisplayMode+0x14
        if (v0 == 0) {
            // 0x004e28d8
            charge(ctx, 8);
            v1 = 2;
            v0 = 0x960000;
            sb(v1, v0, 22368);  // 0x965760
            v0 = 0x960000;
            sb(v1, v0, 22369);  // 0x965761
            v1 = 1;
            v0 = 0x960000;
            sb(v1, v0, 22371);  // 0x965763
        } else {
            // 0x004e2894
            charge(ctx, 12);
            v1 = 1;
            v0 = 0x960000;
            sb(v1, v0, 22368);  // 0x965760
            v0 = 0x960000;
            sb(v1, v0, 22369);  // 0x965761
            v0 = 0x960000;
            lw(v1, gp, -16992);  // 0x7CEA90
            lw(a0, v0, 22348);  // g_skyDisplayMode+0x4
            v0 = 0x960000;
            a0 = sra(a0, 1);
            sw(a0, v0, 22348);  // g_skyDisplayMode+0x4
            if (v1 == 0) {
                // 0x004e2904
                charge(ctx, 4);
                v0 = 0x960000;
                lw(v0, v0, 22344);  // g_skyDisplayMode
                sw(v0, gp, -16992);  // 0x7CEA90
                backedge(ctx);
            } else {
                // 0x004e28c4
                charge(ctx, 2);
                v0 = 0x960000;
                sw(v1, v0, 22344);  // g_skyDisplayMode
            }
            // 0x004e28cc
            charge(ctx, 3);
            v0 = 0x960000;
            sb(zero, v0, 22371);  // 0x965763
        }
        // 0x004e28f8
        charge(ctx, 3);
        v0 = 0x960000;
        sb(zero, v0, 22370);  // 0x965762
        backedge(ctx);
    }
    // 0x004e13bc
    charge(ctx, 4);
    jal(ctx, 0x4E13BCu, gen::fn_skyCustomModeIsOk_004e0c10);
    if (v0 == 0) {
        // 0x004e2914
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004e13cc
        charge(ctx, 8);
        v0 = 0x960000;
        v1 = 0x960000;
        lbu(a2, v0, 22370);  // 0x965762
        v1 = addiu(v1, 22320);  // &customMode
        sw(v1, gp, -17120);  // 0x7CEA10
        v1 = 80;
        if (a2 == v1) {
            // 0x004e291c
            charge(ctx, 7);
            a2 = v1;
            a0 = 0;
            a1 = 0;
            a3 = 1;
            jal(ctx, 0x4E2928u, gen::fn_sceGsResetGraph_004f8eb0);
            backedge(ctx);
        L_004e1440:
            charge(ctx, 1);
            a0 = 2;
        } else {
            // 0x004e13ec
            charge(ctx, 5);
            v0 = 0x960000;
            lw(v1, v0, 22356);  // g_skyDisplayMode+0xC
            v0 = v1 & 0x4;
            if (v0 != 0) {
                // 0x004e2938
                charge(ctx, 6);
                a1 = 1;
                a0 = 0;
                a3 = a1;
                jal(ctx, 0x4E2940u, gen::fn_sceGsResetGraph_004f8eb0);
                backedge(ctx);
                goto L_004e1440;
            }
            // 0x004e1400
            charge(ctx, 3);
            v0 = v1 & 0x2;
            if (v0 != 0) {
                // 0x004e2950
                charge(ctx, 6);
                a0 = 0;
                a1 = 1;
                a3 = 0;
                jal(ctx, 0x4E2958u, gen::fn_sceGsResetGraph_004f8eb0);
                backedge(ctx);
                goto L_004e1440;
            }
            // 0x004e140c
            charge(ctx, 3);
            v0 = v1 & 0x100;
            if (v0 == 0) {
                // 0x004e1430
                charge(ctx, 4);
                a0 = 0;
                a1 = 0;
                a3 = 1;
                jal(ctx, 0x4E1438u, gen::fn_sceGsResetGraph_004f8eb0);
                goto L_004e1440;
            }
            // 0x004e1418
            charge(ctx, 6);
            a1 = 1;
            a0 = 0;
            a3 = a1;
            jal(ctx, 0x4E1420u, gen::fn_sceGsResetGraph_004f8eb0);
            a0 = 2;
        }
        // 0x004e1444
        charge(ctx, 7);
        jal(ctx, 0x4E1444u, gen::fn_sceDmaGetChan_004fa8f0);
        a1 = 0x960000;
        a0 = v0;
        a1 = addiu(a1, 22384);  // &skyInitialClear
        a2 = 13;
        jal(ctx, 0x4E1458u, gen::fn_sceDmaSendN_004fac88);
        for (;;) {
            // 0x004e1460
            charge(ctx, 7);
            a0 = 1;
            a1 = 0;
            jal(ctx, 0x4E1464u, gen::fn_sceGsSyncPath_004f99d0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004e147c
        charge(ctx, 8);
        v1 = 4;
        v0 = 0x10010000;
        sw(v1, v0, -8176);  // 0x1000E010 D_STAT
        v0 = 0x960000;
        lw(v1, v0, 22352);  // g_skyDisplayMode+0x8
        v0 = 16;
        if (v1 != v0) {
            // 0x004e14a4
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x004e149c
            charge(ctx, 2);
            v0 = 10;
        }
        // 0x004e14a8
        charge(ctx, 16);
        a1 = dsll32(v0, 16);
        a0 = 0x960000;
        v0 = 0x960000;
        a1 = dsra32(a1, 16);
        lh(a2, v0, 22344);  // g_skyDisplayMode
        a0 = addiu(a0, 18832);  // &rwDMAFlipData
        t0 = 0;
        v0 = 0x960000;
        lh(a3, v0, 22348);  // g_skyDisplayMode+0x4
        t1 = 0;
        jal(ctx, 0x4E14CCu, gen::fn_sceGsSetDefDispEnv_004f9168);
        v0 = 0x960000;
        v1 = 16;
        lw(v0, v0, 22352);  // g_skyDisplayMode+0x8
        if (v0 != v1) {
            // 0x004e14f0
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x004e14e8
            charge(ctx, 2);
            v0 = 10;
        }
        // 0x004e14f4
        charge(ctx, 15);
        a1 = dsll32(v0, 16);
        a0 = 0x960000;
        v0 = 0x960000;
        a1 = dsra32(a1, 16);
        lh(a2, v0, 22344);  // g_skyDisplayMode
        a0 = addiu(a0, 18872);  // &rwDMAFlipData+0x28
        t0 = 0;
        v0 = 0x960000;
        lh(a3, v0, 22348);  // g_skyDisplayMode+0x4
        t1 = 0;
        jal(ctx, 0x4E1518u, gen::fn_sceGsSetDefDispEnv_004f9168);
        lw(v1, gp, -20248);  // g_skyZBufferDepth
        v0 = 16;
        if (v1 != v0) {
            // 0x004e1538
            charge(ctx, 1);
            a0 = 49;
        } else {
            // 0x004e1530
            charge(ctx, 2);
            a0 = 58;
        }
        // 0x004e153c
        charge(ctx, 5);
        v0 = 0x960000;
        v1 = 16;
        lw(v0, v0, 22328);  // customMode+0x8
        if (v0 != v1) {
            // 0x004e1558
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x004e1550
            charge(ctx, 2);
            v0 = 10;
        }
        // 0x004e155c
        charge(ctx, 16);
        a1 = dsll32(v0, 16);
        t1 = dsll32(a0, 16);
        v1 = 0x960000;
        v0 = 0x960000;
        lh(a2, v1, 22320);  // customMode
        a0 = 0x960000;
        lh(a3, v0, 22324);  // customMode+0x4
        a1 = dsra32(a1, 16);
        t1 = dsra32(t1, 16);
        a0 = addiu(a0, 18928);  // &rwDMAFlipData+0x60
        t0 = 2;
        jal(ctx, 0x4E1584u, gen::fn_sceGsSetDefDrawEnv_004f9668);
        lw(v1, gp, -20248);  // g_skyZBufferDepth
        v0 = 16;
        if (v1 != v0) {
            // 0x004e15a4
            charge(ctx, 1);
            a0 = 49;
        } else {
            // 0x004e159c
            charge(ctx, 2);
            a0 = 58;
        }
        // 0x004e15a8
        charge(ctx, 5);
        v0 = 0x960000;
        v1 = 16;
        lw(v0, v0, 22328);  // customMode+0x8
        if (v0 != v1) {
            // 0x004e15c4
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x004e15bc
            charge(ctx, 2);
            v0 = 10;
        }
        // 0x004e15c8
        charge(ctx, 16);
        a1 = dsll32(v0, 16);
        t1 = dsll32(a0, 16);
        v1 = 0x960000;
        v0 = 0x960000;
        lh(a2, v1, 22320);  // customMode
        a0 = 0x960000;
        lh(a3, v0, 22324);  // customMode+0x4
        a1 = dsra32(a1, 16);
        t1 = dsra32(t1, 16);
        a0 = addiu(a0, 19056);  // &rwDMAFlipData+0xE0
        t0 = 2;
        jal(ctx, 0x4E15F0u, gen::fn_sceGsSetDefDrawEnv2_004fa558);
        lw(v1, gp, -20248);  // g_skyZBufferDepth
        v0 = 16;
        if (v1 != v0) {
            // 0x004e1610
            charge(ctx, 1);
            a0 = 49;
        } else {
            // 0x004e1608
            charge(ctx, 2);
            a0 = 58;
        }
        // 0x004e1614
        charge(ctx, 5);
        v0 = 0x960000;
        v1 = 16;
        lw(v0, v0, 22328);  // customMode+0x8
        if (v0 != v1) {
            // 0x004e1630
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x004e1628
            charge(ctx, 2);
            v0 = 10;
        }
        // 0x004e1634
        charge(ctx, 16);
        a1 = dsll32(v0, 16);
        t1 = dsll32(a0, 16);
        v1 = 0x960000;
        v0 = 0x960000;
        lh(a2, v1, 22320);  // customMode
        a0 = 0x960000;
        lh(a3, v0, 22324);  // customMode+0x4
        a1 = dsra32(a1, 16);
        t1 = dsra32(t1, 16);
        a0 = addiu(a0, 19296);  // &rwDMAFlipData+0x1D0
        t0 = 2;
        jal(ctx, 0x4E165Cu, gen::fn_sceGsSetDefDrawEnv_004f9668);
        lw(v1, gp, -20248);  // g_skyZBufferDepth
        v0 = 16;
        if (v1 != v0) {
            // 0x004e167c
            charge(ctx, 1);
            a0 = 49;
        } else {
            // 0x004e1674
            charge(ctx, 2);
            a0 = 58;
        }
        // 0x004e1680
        charge(ctx, 5);
        v0 = 0x960000;
        v1 = 16;
        lw(v0, v0, 22328);  // customMode+0x8
        if (v0 != v1) {
            // 0x004e169c
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x004e1694
            charge(ctx, 2);
            v0 = 10;
        }
        // 0x004e16a0
        charge(ctx, 73);
        a1 = dsll32(v0, 16);
        t1 = dsll32(a0, 16);
        v1 = 0x960000;
        v0 = 0x960000;
        lh(a2, v1, 22320);  // customMode
        a0 = 0x960000;
        lh(a3, v0, 22324);  // customMode+0x4
        a1 = dsra32(a1, 16);
        t1 = dsra32(t1, 16);
        a0 = addiu(a0, 19424);  // &rwDMAFlipData+0x250
        t0 = 2;
        jal(ctx, 0x4E16C8u, gen::fn_sceGsSetDefDrawEnv2_004fa558);
        v1 = 0;
        v0 = 0;
        pcpyld(t3, v1, v0);
        v0 = 0x960000;
        t0 = si(-32768);
        sq(t3, v0, 18912);  // rwDMAFlipData+0x50
        t1 = 16;
        v0 = 0x960000;
        a0 = si(-1);
        ld(t4, v0, 18912);  // rwDMAFlipData+0x50
        t6 = 0x960000;
        t5 = 0x960000;
        t2 = 16;
        v0 = 1;
        t4 = t4 & t0;
        a3 = dsll(v0, 15);
        a1 = dsll32(v0, 28);
        v0 = lui(0xFFFF);
        t4 = t4 | t1;
        a2 = v0 | 0x7FFF;
        v0 = 0xFFF0000;
        t4 = t4 & a2;
        v1 = v0 | 0xFFFF;
        v0 = 0xFFFF;
        v1 = dsll32(v1, 0);
        v0 = dsll(v0, 16);
        v0 = v0 | 0xFFFF;
        v0 = v0 | v1;
        v1 = t4 | a3;
        pcpyld(a0, a0, v0);
        v0 = v1 & a0;
        t4 = v0 | a1;
        v1 = 0x960000;
        sd(t4, v1, 18912);  // rwDMAFlipData+0x50
        v0 = 0x960000;
        t4 = 0x960000;
        ld(s1, v0, 18920);  // rwDMAFlipData+0x58
        sq(t3, t4, 19280);  // rwDMAFlipData+0x1C0
        v1 = 14;
        t3 = 0x960000;
        t4 = 0x960000;
        ld(s0, t3, 19280);  // rwDMAFlipData+0x1C0
        v0 = si(-16);
        s1 = s1 & v0;
        s1 = s1 | v1;
        t3 = 0x960000;
        t0 = s0 & t0;
        ld(t7, t3, 19288);  // rwDMAFlipData+0x1C8
        t0 = t0 | t1;
        a2 = t0 & a2;
        sd(s1, t6, 18920);  // rwDMAFlipData+0x58
        a2 = a2 | a3;
        t3 = 0x960000;
        v0 = t7 & v0;
        lbu(t3, t3, 22371);  // 0x965763
        v0 = v0 | v1;
        sd(v0, t4, 19288);  // rwDMAFlipData+0x1C8
        v0 = a2 & a0;
        v0 = v0 | a1;
        sd(v0, t5, 19280);  // rwDMAFlipData+0x1C0
        if (t3 == 0) {
            // 0x004e1880
            charge(ctx, 4);
            v0 = 0x960000;
            lw(a2, v0, 22352);  // g_skyDisplayMode+0x8
            if (a2 != t2) {
                // 0x004e18a8
                charge(ctx, 5);
                v0 = 0x960000;
                v1 = si(-32);
                lw(v0, v0, 22348);  // g_skyDisplayMode+0x4
                v0 = addiu(v0, 31);
                a0 = v0 & v1;
            } else {
                // 0x004e1890
                charge(ctx, 6);
                v0 = 0x960000;
                v1 = si(-64);
                lw(v0, v0, 22348);  // g_skyDisplayMode+0x4
                v0 = addiu(v0, 63);
                a0 = v0 & v1;
            }
            // 0x004e18bc
            charge(ctx, 14);
            v0 = 0x960000;
            v1 = si(-64);
            lw(v0, v0, 22344);  // g_skyDisplayMode
            v0 = addiu(v0, 63);
            v0 = v0 & v1;
            mult(a1, v0, a0);
            v0 = a2 ^ 0x10;
            a0 = sltiu(v0, 1);
            v0 = 0x960000;
            a0 = srlv(a1, a0);
            lbu(v1, v0, 22369);  // 0x965761
            v0 = 2;
            a1 = srl(a0, 11);
            if (v1 == v0) {
                // 0x004e2968
                charge(ctx, 10);
                v0 = 0x960000;
                a0 = a1 & 0x1FF;
                lw(a2, v0, 18888);  // rwDMAFlipData+0x38
                v1 = si(-512);
                a1 = sll(a1, 1);
                v1 = a2 & v1;
                v0 = 0x960000;
                v1 = v1 | a0;
                sw(v1, v0, 18888);  // rwDMAFlipData+0x38
                backedge(ctx);
            }
            // 0x004e18f4
            charge(ctx, 18);
            v0 = 0x960000;
            t1 = si(-512);
            ld(t3, v0, 19296);  // rwDMAFlipData+0x1D0
            t2 = a1 & 0x1FF;
            a0 = 0x960000;
            v1 = 0x960000;
            a2 = 16;
            v0 = 0x960000;
            ld(t0, v0, 19424);  // rwDMAFlipData+0x250
            v0 = 0x960000;
            lw(a3, v0, 22328);  // customMode+0x8
            v0 = t3 & t1;
            v0 = v0 | t2;
            sd(v0, a0, 19296);  // rwDMAFlipData+0x1D0
            v0 = t0 & t1;
            v0 = v0 | t2;
            sd(v0, v1, 19424);  // rwDMAFlipData+0x250
            if (a3 != a2) {
                // 0x004e1954
                charge(ctx, 5);
                v0 = 0x960000;
                v1 = si(-32);
                lw(a0, v0, 22324);  // customMode+0x4
                v0 = addiu(a0, 31);
                a2 = v0 & v1;
            } else {
                // 0x004e193c
                charge(ctx, 6);
                v0 = 0x960000;
                v1 = si(-64);
                lw(a0, v0, 22324);  // customMode+0x4
                v0 = addiu(a0, 63);
                a2 = v0 & v1;
            }
            // 0x004e1968
            charge(ctx, 13);
            v0 = 0x960000;
            v1 = si(-64);
            lw(v0, v0, 22320);  // customMode
            v0 = addiu(v0, 63);
            v1 = v0 & v1;
            mult(t0, v1, a2);
            v0 = a3 ^ 0x10;
            a3 = sltiu(v0, 1);
            v0 = 0x960000;
            lbu(a2, v0, 22368);  // 0x965760
            v0 = 2;
            a3 = srlv(t0, a3);
            if (a2 == v0) {
                // 0x004e199c
                charge(ctx, 2);
                v0 = srl(a3, 11);
                a1 = addu(a1, v0);
            }
            // 0x004e19a4
            charge(ctx, 16);
            v0 = 0x960000;
            a2 = srl(a3, 11);
            ld(t0, v0, 18928);  // rwDMAFlipData+0x60
            t2 = a1 & 0x1FF;
            t1 = si(-512);
            a1 = addu(a1, a2);
            a2 = 0x960000;
            v0 = 0x960000;
            t0 = t0 & t1;
            ld(a3, v0, 19056);  // rwDMAFlipData+0xE0
            t0 = t0 | t2;
            sd(t0, a2, 18928);  // rwDMAFlipData+0x60
            a2 = a3 & t1;
            v0 = 0x960000;
            a2 = a2 | t2;
            sd(a2, v0, 19056);  // rwDMAFlipData+0xE0
        } else {
            // 0x004e17c4
            charge(ctx, 4);
            v0 = 0x960000;
            lw(a1, v0, 22328);  // customMode+0x8
            if (a1 != t2) {
                // 0x004e17ec
                charge(ctx, 5);
                v0 = 0x960000;
                v1 = si(-32);
                lw(a0, v0, 22324);  // customMode+0x4
                v0 = addiu(a0, 31);
                a2 = v0 & v1;
            } else {
                // 0x004e17d4
                charge(ctx, 6);
                v0 = 0x960000;
                v1 = si(-64);
                lw(a0, v0, 22324);  // customMode+0x4
                v0 = addiu(a0, 63);
                a2 = v0 & v1;
            }
            // 0x004e1800
            charge(ctx, 32);
            v0 = 0x960000;
            v1 = si(-64);
            lw(v0, v0, 22320);  // customMode
            v0 = addiu(v0, 63);
            v1 = v0 & v1;
            mult(a2, v1, a2);
            v0 = a1 ^ 0x10;
            a1 = sltiu(v0, 1);
            t3 = si(-512);
            v0 = 0x960000;
            t0 = 0x960000;
            lw(t2, v0, 18888);  // rwDMAFlipData+0x38
            a3 = 0x960000;
            a1 = srlv(a2, a1);
            a2 = 0x960000;
            ld(a2, a2, 19056);  // rwDMAFlipData+0xE0
            v0 = 0x960000;
            t2 = t2 & t3;
            ld(t1, v0, 18928);  // rwDMAFlipData+0x60
            a2 = a2 & t3;
            v0 = srl(a1, 11);
            t4 = v0 & 0x1FF;
            a1 = sll(v0, 1);
            t2 = t2 | t4;
            v0 = 0x960000;
            sw(t2, t0, 18888);  // rwDMAFlipData+0x38
            a2 = a2 | t4;
            t0 = t1 & t3;
            sd(a2, v0, 19056);  // rwDMAFlipData+0xE0
            t0 = t0 | t4;
            sd(t0, a3, 18928);  // rwDMAFlipData+0x60
        }
        // 0x004e19e4
        charge(ctx, 29);
        a2 = 0x960000;
        s0 = si(-512);
        ld(t2, a2, 18944);  // rwDMAFlipData+0x70
        v0 = a1 & 0x1FF;
        t1 = 0x960000;
        lw(t3, gp, -20248);  // g_skyZBufferDepth
        t0 = 0x960000;
        a3 = 0x960000;
        a2 = 0x960000;
        t2 = t2 & s0;
        ld(t6, a2, 19072);  // rwDMAFlipData+0xF0
        t7 = t2 | v0;
        sd(t7, t1, 18944);  // rwDMAFlipData+0x70
        t2 = 16;
        a2 = 0x960000;
        t1 = t6 & s0;
        ld(t5, a2, 19312);  // rwDMAFlipData+0x1E0
        t1 = t1 | v0;
        sd(t1, t0, 19072);  // rwDMAFlipData+0xF0
        a2 = 0x960000;
        t1 = t5 & s0;
        ld(t4, a2, 19440);  // rwDMAFlipData+0x260
        t1 = t1 | v0;
        sd(t1, a3, 19312);  // rwDMAFlipData+0x1E0
        t0 = t4 & s0;
        a2 = 0x960000;
        v0 = t0 | v0;
        sd(v0, a2, 19440);  // rwDMAFlipData+0x260
        if (t3 != t2) {
            // 0x004e1a68
            charge(ctx, 3);
            a0 = addiu(a0, 31);
            v0 = si(-32);
            v0 = a0 & v0;
        } else {
            // 0x004e1a58
            charge(ctx, 4);
            a0 = addiu(a0, 63);
            v0 = si(-64);
            v0 = a0 & v0;
        }
        // 0x004e1a74
        charge(ctx, 13);
        mult(a2, v1, v0);
        v0 = t3 ^ 0x10;
        a0 = sltiu(v0, 1);
        v0 = 0x960000;
        lw(v1, v0, 22356);  // g_skyDisplayMode+0xC
        v0 = srlv(a2, a0);
        v0 = srl(v0, 11);
        v0 = addu(a1, v0);
        v0 = sll(v0, 11);
        sw(v0, gp, -16980);  // g_skyTexCacheStartWord
        v0 = v1 & 0x2;
        if (v0 != 0) {
            // 0x004e1aa8
            charge(ctx, 3);
            v0 = v1 & 0x200;
            if (v0 != 0) {
                // 0x004e2990
                charge(ctx, 99);
                v0 = 0x960000;
                v1 = 0x960000;
                lwc1(f2, v0, 18860);  // rwDMAFlipData+0x1C
                a2 = 0x960000;
                lwc1(f3, v1, 18856);  // rwDMAFlipData+0x18
                a3 = 0x960000;
                a0 = 0x960000;
                a1 = 0x960000;
                t2 = 2048;
                t4 = 0x960000;
                v0 = 0x960000;
                lwc1(f0, v0, 18852);  // rwDMAFlipData+0x14
                v1 = 0x960000;
                swc1(f2, a2, 19660);  // rwDMAFlipData+0x33C
                lwc1(f1, v1, 18848);  // rwDMAFlipData+0x10
                a2 = 0x960000;
                lwc1(f2, a0, 18900);  // rwDMAFlipData+0x44
                swc1(f3, a3, 19656);  // rwDMAFlipData+0x338
                a3 = 0x960000;
                v0 = 0x960000;
                lwc1(f3, v0, 18896);  // rwDMAFlipData+0x40
                v1 = 0x960000;
                swc1(f1, v1, 19648);  // rwDMAFlipData+0x330
                a0 = 0x960000;
                swc1(f0, a1, 19652);  // rwDMAFlipData+0x334
                v1 = 0x960000;
                lwc1(f0, v1, 18892);  // rwDMAFlipData+0x3C
                a1 = 0x960000;
                swc1(f2, a2, 19676);  // rwDMAFlipData+0x34C
                v0 = 0x960000;
                lwc1(f1, v0, 18888);  // rwDMAFlipData+0x38
                swc1(f3, a3, 19672);  // rwDMAFlipData+0x348
                a3 = 0x8000;
                swc1(f0, a0, 19668);  // rwDMAFlipData+0x344
                v1 = 0x960000;
                v0 = 0x960000;
                lw(t0, v0, 18852);  // rwDMAFlipData+0x14
                swc1(f1, a1, 19664);  // rwDMAFlipData+0x340
                v0 = lui(0xFFC0);
                t1 = v0 | 0x7FF;
                v0 = 0x960000;
                a0 = t0 & t1;
                lw(a2, v0, 18860);  // rwDMAFlipData+0x1C
                a0 = a0 | t2;
                sw(a0, v1, 18852);  // rwDMAFlipData+0x14
                v1 = 0x960000;
                v0 = lui(0xFF80);
                t0 = v0 | 0xFFF;
                v0 = 0x960000;
                a0 = a2 & t0;
                lw(t3, v0, 18832);  // rwDMAFlipData
                v0 = dsll32(a2, 9);
                v0 = dsrl32(v0, 21);
                a1 = addiu(v0, -1);
                v0 = lui(0xFFFF);
                a1 = a1 & 0x7FF;
                a2 = v0 | 0xFF;
                v0 = sll(a1, 12);
                v0 = a0 | v0;
                a1 = 1;
                sw(v0, v1, 18860);  // rwDMAFlipData+0x1C
                a0 = si(-2);
                v0 = t3 & a2;
                v1 = 2;
                v0 = v0 | a3;
                t3 = v0 & a0;
                v0 = si(-3);
                t3 = t3 | a1;
                t5 = t3 & v0;
                t3 = 0x960000;
                t5 = t5 | v1;
                lw(s0, t3, 18892);  // rwDMAFlipData+0x3C
                sw(t5, t4, 18832);  // rwDMAFlipData
                t5 = 0x960000;
                t4 = 0x960000;
                t3 = 0x960000;
                t1 = s0 & t1;
                lw(t7, t3, 18900);  // rwDMAFlipData+0x44
                t1 = t1 | t2;
                sw(t1, t5, 18892);  // rwDMAFlipData+0x3C
                t3 = 0x960000;
                t1 = dsll32(t7, 9);
                lw(t6, t3, 18872);  // rwDMAFlipData+0x28
                t1 = dsrl32(t1, 21);
                t0 = t7 & t0;
                a2 = t6 & a2;
                t3 = 0x960000;
                a2 = a2 | a3;
                a0 = a2 & a0;
                a3 = addiu(t1, -1);
                a0 = a0 | a1;
                a2 = a3 & 0x7FF;
                a1 = sll(a2, 12);
                v0 = a0 & v0;
                a1 = t0 | a1;
                v0 = v0 | v1;
                sw(a1, t4, 18900);  // rwDMAFlipData+0x44
                sw(v0, t3, 18872);  // rwDMAFlipData+0x28
                backedge(ctx);
            }
            // 0x004e1ab4
            charge(ctx, 6);
            v0 = 0x960000;
            a0 = 0x960000;
            v0 = addiu(v0, 19808);  // &rwDMAFlipData+0x3D0
            a0 = addiu(a0, 18832);  // &rwDMAFlipData
            a1 = addiu(v0, 127);  // &rwDMAFlipData+0x44F
            jal(ctx, 0x4E1AC4u, gen::fn_SyncDCache_00503a58);
        }
        // 0x004e1acc
        charge(ctx, 13);
        lw(a0, gp, -16980);  // g_skyTexCacheStartWord
        v0 = 0x100000;
        a1 = subu(v0, a0);
        jal(ctx, 0x4E1AD4u, gen::fn_sub_4F0990_004f0990);
        a0 = 1;
        sw(zero, gp, -16988);  // 0x7CEA94
        sw(a0, gp, -17116);  // 0x7CEA14
        link(ctx, 0x4E1AE8u);  // $ra first: the delay slot below depends on it
        sw(zero, gp, -17092);  // 0x7CEA2C
        call(ctx, gen::fn_sceDmaGetChan_004fa8f0);
        a1 = 0x7B0000;
        a0 = v0;
        a1 = addiu(a1, 20608);  // &gs_set_up
        jal(ctx, 0x4E1AF8u, gen::fn_sceDmaSend_004fac20);
        for (;;) {
            // 0x004e1b00
            charge(ctx, 7);
            a0 = 1;
            a1 = 0;
            jal(ctx, 0x4E1B04u, gen::fn_sceGsSyncPath_004f99d0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004e1b1c
        charge(ctx, 748);
        v1 = 2;
        v0 = 0x10010000;
        sw(v1, v0, -8176);  // 0x1000E010 D_STAT
        s3 = lui(0xFF00);
        v0 = 0x960000;
        s3 = s3 | 0xFFFF;
        ld(t1, v0, 18960);  // rwDMAFlipData+0x80
        a2 = 0x960000;
        v1 = 0x960000;
        a1 = 0x960000;
        a0 = 0x960000;
        s1 = si(-2);
        t3 = si(-4096);
        sq(s3, sp, 0xA0);
        s7 = 0x960000;
        s6 = 0x960000;
        fp = 0x960000;
        v0 = 0x960000;
        sd(t1, a2, 19328);  // rwDMAFlipData+0x1F0
        ld(t0, v0, 19040);  // rwDMAFlipData+0xD0
        lw(a2, v1, 19680);  // rwDMAFlipData+0x350
        v0 = 0x960000;
        ld(a3, v0, 19408);  // rwDMAFlipData+0x240
        v1 = t0 | 0x140B;
        sd(v1, a1, 19040);  // rwDMAFlipData+0xD0
        a1 = a2 & s1;
        v0 = 0x960000;
        v1 = a3 | 0x140B;
        lw(v0, v0, 18832);  // rwDMAFlipData
        sd(v1, a0, 19408);  // rwDMAFlipData+0x240
        v1 = dsll32(v0, 30);
        a3 = v0 & 0x1;
        v1 = dsrl32(v1, 31);
        a1 = a1 | a3;
        v1 = v1 & 0x1;
        a0 = dsll32(v0, 27);
        a2 = sll(v1, 1);
        v1 = si(-3);
        a1 = a1 & v1;
        v1 = dsrl32(a0, 29);
        a1 = a1 | a2;
        v1 = v1 & 0x7;
        a0 = sll(v1, 2);
        v1 = si(-29);
        v1 = a1 & v1;
        a0 = v1 | a0;
        v1 = dsll32(v0, 26);
        a1 = dsrl32(v1, 31);
        v1 = si(-33);
        a1 = a1 & 0x1;
        a0 = a0 & v1;
        a1 = sll(a1, 5);
        v1 = dsll32(v0, 25);
        a1 = a0 | a1;
        v1 = dsrl32(v1, 31);
        v1 = v1 & 0x1;
        a0 = sll(v1, 6);
        v1 = si(-65);
        v1 = a1 & v1;
        a0 = v1 | a0;
        v1 = dsll32(v0, 24);
        v1 = dsrl32(v1, 31);
        a1 = v1 & 0x1;
        v1 = si(-129);
        a1 = sll(a1, 7);
        a0 = a0 & v1;
        v1 = dsll32(v0, 16);
        a1 = a0 | a1;
        v1 = dsrl32(v1, 24);
        v0 = dsll32(v0, 0);
        v1 = v1 & 0xFF;
        v0 = dsrl32(v0, 16);
        a0 = sll(v1, 8);
        v0 = v0 & 0xFFFF;
        v1 = lui(0xFFFF);
        a2 = sll(v0, 16);
        s0 = v1 | 0xFF;
        v0 = si(-1);
        v1 = a1 & s0;
        v0 = dsll32(v0, 0);
        a1 = v1 | a0;
        v1 = 0xFFFF;
        a0 = 0x960000;
        t9 = v1 | v0;
        v1 = 0x960000;
        a1 = a1 & t9;
        lw(a3, v1, 18836);  // rwDMAFlipData+0x4
        v1 = a1 | a2;
        sw(v1, a0, 19680);  // rwDMAFlipData+0x350
        a1 = 0x960000;
        a0 = 0x960000;
        sw(a3, a1, 19684);  // rwDMAFlipData+0x354
        lw(t0, a0, 19688);  // rwDMAFlipData+0x358
        v1 = 0x960000;
        lw(v1, v1, 18840);  // rwDMAFlipData+0x8
        a1 = 0x960000;
        a2 = 0x960000;
        a0 = 15;
        t0 = t0 & s1;
        t8 = a0 | v0;
        t2 = v1 & 0x1;
        a0 = 0x960000;
        t0 = t0 | t2;
        lw(a3, a0, 18844);  // rwDMAFlipData+0xC
        a0 = 0x960000;
        sw(a3, a1, 19692);  // rwDMAFlipData+0x35C
        lw(t1, a0, 18848);  // rwDMAFlipData+0x10
        a0 = dsll32(v1, 30);
        a0 = dsrl32(a0, 31);
        t2 = a0 & 0x1;
        a0 = si(-3);
        t2 = sll(t2, 1);
        t0 = t0 & a0;
        a0 = dsll32(v1, 28);
        a3 = t0 | t2;
        a1 = dsrl32(a0, 30);
        v1 = dsll32(v1, 0);
        a0 = si(-13);
        a1 = a1 & 0x3;
        v1 = dsrl32(v1, 4);
        a0 = a3 & a0;
        a1 = sll(a1, 2);
        v1 = dsll32(v1, 4);
        a1 = a0 | a1;
        v1 = dsrl32(v1, 4);
        a0 = sll(v1, 4);
        t0 = t1 & 0x1FF;
        v1 = a1 & t8;
        v1 = v1 | a0;
        sw(v1, a2, 19688);  // rwDMAFlipData+0x358
        v1 = 0x960000;
        lw(a1, v1, 19696);  // rwDMAFlipData+0x360
        v1 = dsll32(t1, 17);
        a0 = dsrl32(v1, 26);
        v1 = dsll32(t1, 12);
        a0 = a0 & 0x3F;
        v1 = dsrl32(v1, 27);
        a3 = sll(a0, 9);
        v1 = v1 & 0x1F;
        a0 = dsll32(t1, 0);
        a2 = sll(v1, 15);
        v1 = si(-512);
        a1 = a1 & v1;
        v1 = dsrl32(a0, 20);
        a1 = a1 | t0;
        a0 = v1 & 0xFFF;
        v1 = si(-32257);
        v1 = a1 & v1;
        a1 = sll(a0, 20);
        a0 = v1 | a3;
        v1 = lui(0xFFF0);
        t7 = v1 | 0x7FFF;
        v1 = 0xF0000;
        a0 = a0 & t7;
        v1 = v1 | 0xFFFF;
        a0 = a0 | a2;
        t6 = v1 | v0;
        a2 = 0x960000;
        v1 = a0 & t6;
        a1 = v1 | a1;
        a0 = 0x960000;
        sw(a1, a0, 19696);  // rwDMAFlipData+0x360
        v1 = 0x960000;
        a0 = 0x960000;
        a1 = 0x960000;
        lw(t0, a0, 19700);  // rwDMAFlipData+0x364
        lw(a3, a1, 19704);  // rwDMAFlipData+0x368
        lw(v1, v1, 18852);  // rwDMAFlipData+0x14
        a0 = lui(0xFFC0);
        a1 = si(-2048);
        t5 = a0 | 0x7FF;
        t0 = t0 & a1;
        a0 = 0x3F0000;
        t1 = v1 & 0x7FF;
        a1 = dsll32(v1, 10);
        a0 = a0 | 0xFFFF;  // &0x3FFFFF
        v1 = dsll32(v1, 0);
        t4 = a0 | v0;
        t1 = t0 | t1;
        a1 = dsrl32(a1, 21);
        a0 = 0x960000;
        t0 = a1 & 0x7FF;
        lw(a0, a0, 18856);  // rwDMAFlipData+0x18
        a1 = t1 & t5;
        t0 = sll(t0, 11);
        t0 = a1 | t0;
        v1 = dsrl32(v1, 22);
        a1 = v1 & 0x3FF;
        v1 = t0 & t4;
        t0 = sll(a1, 22);
        v1 = v1 | t0;
        a1 = a0 & 0xFFF;
        sw(v1, a2, 19700);  // rwDMAFlipData+0x364
        v1 = a3 & t3;
        a2 = v1 | a1;
        v1 = dsll32(a0, 9);
        a1 = dsrl32(v1, 21);
        v1 = lui(0xFF80);
        a1 = a1 & 0x7FF;
        t2 = v1 | 0xFFF;
        a1 = sll(a1, 12);
        v1 = a2 & t2;
        a2 = v1 | a1;
        v1 = dsll32(a0, 5);
        a1 = dsrl32(v1, 28);
        v1 = lui(0xF87F);
        a1 = a1 & 0xF;
        t1 = v1 | 0xFFFF;
        a1 = sll(a1, 23);
        v1 = a2 & t1;
        v1 = v1 | a1;
        a1 = dsll32(a0, 3);
        a1 = dsrl32(a1, 30);
        a0 = dsll32(a0, 0);
        a1 = a1 & 0x3;
        a0 = dsrl32(a0, 29);
        a3 = sll(a1, 27);
        a0 = a0 & 0x7;
        a1 = sll(a0, 29);
        a0 = lui(0xE7FF);
        t0 = a0 | 0xFFFF;
        a0 = 0x1FFF0000;
        a2 = v1 & t0;
        v1 = a0 | 0xFFFF;
        a0 = a2 | a3;
        a3 = v1 | v0;
        a0 = a0 & a3;
        v1 = 0x960000;
        a1 = a0 | a1;
        sw(a1, v1, 19704);  // rwDMAFlipData+0x368
        a0 = 0x960000;
        lw(s4, a0, 18860);  // rwDMAFlipData+0x1C
        v1 = 0x960000;
        lw(s2, v1, 19708);  // rwDMAFlipData+0x36C
        a1 = 0x960000;
        lw(a1, a1, 18864);  // rwDMAFlipData+0x20
        a0 = 0x7F0000;
        s3 = s4 & 0xFFF;
        v1 = a0 | 0xFFFF;  // &0x7FFFFF
        s2 = s2 & t3;
        a0 = 0x960000;
        s5 = dsll32(s4, 9);
        s2 = s2 | s3;
        lw(a0, a0, 19712);  // rwDMAFlipData+0x370
        s3 = dsrl32(s5, 21);
        a2 = v1 | v0;
        s5 = s3 & 0x7FF;
        v1 = 0x960000;
        s3 = s2 & t2;
        s5 = sll(s5, 12);
        s2 = dsll32(s4, 0);
        s3 = s3 | s5;
        s2 = dsrl32(s2, 23);
        s3 = s3 & a2;
        s2 = s2 & 0x1FF;
        s4 = sll(s2, 23);
        s2 = si(-256);
        s3 = s3 | s4;
        a0 = a0 & s2;
        sw(s3, v1, 19708);  // rwDMAFlipData+0x36C
        s2 = a1 & 0xFF;
        s3 = 0x960000;
        v1 = a0 | s2;
        a0 = v1 & s0;
        v1 = dsll32(a1, 16);
        s2 = dsrl32(v1, 24);
        v1 = dsll32(a1, 8);
        s2 = s2 & 0xFF;
        v1 = dsrl32(v1, 24);
        s2 = sll(s2, 8);
        v1 = v1 & 0xFF;
        a0 = a0 | s2;
        s2 = sll(v1, 16);
        lq(v1, sp, 0xA0);
        a0 = a0 & v1;
        v1 = dsll32(a1, 0);
        a0 = a0 | s2;
        a1 = 0xFF0000;
        v1 = dsrl32(v1, 24);
        a1 = a1 | 0xFFFF;  // &0xFFFFFF
        v1 = v1 & 0xFF;
        a1 = a1 | v0;
        v1 = sll(v1, 24);
        a0 = a0 & a1;
        v0 = 0x960000;
        v1 = a0 | v1;
        lw(s2, v0, 18868);  // rwDMAFlipData+0x24
        sw(v1, s3, 19712);  // rwDMAFlipData+0x370
        a0 = 0x960000;
        s3 = 0x960000;
        v1 = 0x960000;
        lw(s4, s3, 18876);  // rwDMAFlipData+0x2C
        lw(a0, a0, 18872);  // rwDMAFlipData+0x28
        sw(s2, v1, 19716);  // rwDMAFlipData+0x374
        v0 = 0x960000;
        v1 = 0x960000;
        lw(v0, v0, 19720);  // rwDMAFlipData+0x378
        v1 = addiu(v1, 18880);  // &rwDMAFlipData+0x30
        lw(s3, v1, 0);  // rwDMAFlipData+0x30
        sw(s4, s7, 19724);  // rwDMAFlipData+0x37C
        s5 = dsll32(a0, 30);
        s5 = dsrl32(s5, 31);
        s4 = si(-3);
        s7 = si(-512);
        v0 = v0 & s1;
        v1 = 0x960000;
        lw(s2, v1, 19728);  // rwDMAFlipData+0x380
        v1 = a0 & 0x1;
        s1 = s2 & s1;
        v1 = v0 | v1;
        s2 = si(-29);
        v0 = s5 & 0x1;
        v1 = v1 & s4;
        s4 = sll(v0, 1);
        v0 = dsll32(a0, 27);
        v1 = v1 | s4;
        v1 = v1 & s2;
        v0 = dsrl32(v0, 29);
        s2 = v0 & 0x7;
        v0 = dsll32(a0, 26);
        s2 = sll(s2, 2);
        v0 = dsrl32(v0, 31);
        v1 = v1 | s2;
        v0 = v0 & 0x1;
        s2 = si(-33);
        v1 = v1 & s2;
        v0 = sll(v0, 5);
        v1 = v1 | v0;
        s2 = dsll32(a0, 25);
        v0 = si(-65);
        v1 = v1 & v0;
        v0 = dsrl32(s2, 31);
        s2 = v0 & 0x1;
        v0 = dsll32(a0, 24);
        s2 = sll(s2, 6);
        v0 = dsrl32(v0, 31);
        v1 = v1 | s2;
        v0 = v0 & 0x1;
        s2 = si(-129);
        v1 = v1 & s2;
        v0 = sll(v0, 7);
        v1 = v1 | v0;
        v0 = dsll32(a0, 16);
        v1 = v1 & s0;
        v0 = dsrl32(v0, 24);
        s2 = v0 & 0xFF;
        v0 = dsll32(a0, 0);
        a0 = sll(s2, 8);
        v0 = dsrl32(v0, 16);
        a0 = v1 | a0;
        s2 = 0x960000;
        v1 = v0 & 0xFFFF;
        v0 = a0 & t9;
        v1 = sll(v1, 16);
        v1 = v0 | v1;
        v0 = s3 & 0x1;
        sw(v1, s6, 19720);  // rwDMAFlipData+0x378
        v1 = s1 | v0;
        v0 = si(-3);
        s1 = 0x960000;
        v1 = v1 & v0;
        lw(s5, s1, 19736);  // rwDMAFlipData+0x388
        v0 = dsll32(s3, 30);
        a0 = dsrl32(v0, 31);
        v0 = dsll32(s3, 28);
        a0 = a0 & 0x1;
        v0 = dsrl32(v0, 30);
        a0 = sll(a0, 1);
        v0 = v0 & 0x3;
        v1 = v1 | a0;
        a0 = sll(v0, 2);
        s1 = 0x960000;
        v0 = si(-13);
        s1 = addiu(s1, 18892);  // &rwDMAFlipData+0x3C
        v1 = v1 & v0;
        lw(s4, s1, 0);  // rwDMAFlipData+0x3C
        v0 = dsll32(s3, 0);
        v1 = v1 | a0;
        v0 = dsrl32(v0, 4);
        v1 = v1 & t8;
        v0 = dsll32(v0, 4);
        s5 = s5 & s7;
        v0 = dsrl32(v0, 4);
        t8 = 0x960000;
        a0 = sll(v0, 4);
        a0 = v1 | a0;
        v0 = 0x960000;
        lw(v1, v0, 18884);  // rwDMAFlipData+0x34
        s1 = 0x960000;
        lw(s3, s1, 19740);  // rwDMAFlipData+0x38C
        sw(a0, fp, 0x4D10);
        a0 = 0x960000;
        v0 = 0x960000;
        sw(v1, s2, 19732);  // rwDMAFlipData+0x384
        v0 = addiu(v0, 18888);  // &rwDMAFlipData+0x38
        s1 = 0x960000;
        lw(v0, v0, 0);  // rwDMAFlipData+0x38
        s1 = addiu(s1, 18896);  // &rwDMAFlipData+0x40
        lw(s2, s1, 0);  // rwDMAFlipData+0x40
        v1 = 0x960000;
        s6 = v0 & 0x1FF;
        s7 = dsll32(v0, 17);
        s5 = s5 | s6;
        s1 = 0x960000;
        s6 = dsrl32(s7, 26);
        lw(s1, s1, 19744);  // rwDMAFlipData+0x390
        s7 = si(-32257);
        s6 = s6 & 0x3F;
        s5 = s5 & s7;
        s6 = sll(s6, 9);
        s7 = si(-2048);
        s3 = s3 & s7;
        s7 = s5 | s6;
        s5 = dsll32(v0, 12);
        s6 = dsrl32(s5, 27);
        v0 = dsll32(v0, 0);
        s6 = s6 & 0x1F;
        v0 = dsrl32(v0, 20);
        s5 = s7 & t7;
        s6 = sll(s6, 15);
        s6 = s5 | s6;
        v0 = v0 & 0xFFF;
        s5 = sll(v0, 20);
        v0 = s6 & t6;
        s5 = v0 | s5;
        sw(s5, a0, 19736);  // rwDMAFlipData+0x388
        v0 = s1 & t3;
        a0 = s4 & 0x7FF;
        s1 = s3 | a0;
        a0 = dsll32(s4, 10);
        s1 = s1 & t5;
        a0 = dsrl32(a0, 21);
        s3 = a0 & 0x7FF;
        a0 = dsll32(s4, 0);
        s3 = sll(s3, 11);
        a0 = dsrl32(a0, 22);
        s3 = s1 | s3;
        a0 = a0 & 0x3FF;
        s1 = sll(a0, 22);
        a0 = s3 & t4;
        s1 = a0 | s1;
        a0 = s2 & 0xFFF;
        sw(s1, v1, 19740);  // rwDMAFlipData+0x38C
        v0 = v0 | a0;
        s1 = 0x960000;
        v1 = v0 & t2;
        v0 = dsll32(s2, 9);
        a0 = dsrl32(v0, 21);
        v0 = dsll32(s2, 5);
        a0 = a0 & 0x7FF;
        v0 = dsrl32(v0, 28);
        a0 = sll(a0, 12);
        v1 = v1 | a0;
        v0 = v0 & 0xF;
        a0 = sll(v0, 23);
        v1 = v1 & t1;
        v0 = dsll32(s2, 3);
        v1 = v1 | a0;
        v0 = dsrl32(v0, 30);
        v1 = v1 & t0;
        v0 = v0 & 0x3;
        a0 = sll(v0, 27);
        v0 = dsll32(s2, 0);
        v1 = v1 | a0;
        v0 = dsrl32(v0, 29);
        v1 = v1 & a3;
        v0 = v0 & 0x7;
        s2 = 0x960000;
        a0 = sll(v0, 29);
        a0 = v1 | a0;
        v0 = 0x960000;
        sw(a0, v0, 19744);  // rwDMAFlipData+0x390
        v1 = 0x960000;
        a0 = 0x960000;
        v1 = addiu(v1, 18900);  // &rwDMAFlipData+0x44
        a0 = addiu(a0, 18904);  // &rwDMAFlipData+0x48
        v0 = 0x960000;
        lw(s6, a0, 0);  // rwDMAFlipData+0x48
        lw(v1, v1, 0);  // rwDMAFlipData+0x44
        lw(v0, v0, 19748);  // rwDMAFlipData+0x394
        a0 = 0x960000;
        lw(s5, a0, 19752);  // rwDMAFlipData+0x398
        s7 = v1 & 0xFFF;
        v0 = v0 & t3;
        v0 = v0 | s7;
        v0 = v0 & t2;
        a0 = 0x960000;
        lw(s4, a0, 18908);  // rwDMAFlipData+0x4C
        a0 = 0x960000;
        sw(s4, t8, 19756);  // rwDMAFlipData+0x39C
        lw(s3, a0, 19648);  // rwDMAFlipData+0x330
        a0 = dsll32(v1, 9);
        s7 = dsrl32(a0, 21);
        a0 = si(-256);
        a0 = s5 & a0;
        s5 = s7 & 0x7FF;
        s5 = sll(s5, 12);
        s4 = v0 | s5;
        v0 = dsll32(v1, 0);
        s4 = s4 & a2;
        v1 = dsrl32(v0, 23);
        v0 = s6 & 0xFF;
        v0 = a0 | v0;
        a0 = v1 & 0x1FF;
        v1 = v0 & s0;
        v0 = sll(a0, 23);
        s0 = si(-512);
        a0 = s4 | v0;
        v0 = dsll32(s6, 16);
        sw(a0, s2, 19748);  // rwDMAFlipData+0x394
        v0 = dsrl32(v0, 24);
        a0 = v0 & 0xFF;
        v0 = dsll32(s6, 8);
        a0 = sll(a0, 8);
        v0 = dsrl32(v0, 24);
        a0 = v1 | a0;
        v1 = v0 & 0xFF;
        lq(v0, sp, 0xA0);
        v1 = sll(v1, 16);
        v0 = a0 & v0;
        v1 = v0 | v1;
        v0 = dsll32(s6, 0);
        v1 = v1 & a1;
        v0 = dsrl32(v0, 24);
        a1 = s3 & 0x1FF;
        v0 = v0 & 0xFF;
        a0 = sll(v0, 24);
        v1 = v1 | a0;
        v0 = 0x960000;
        lw(a0, v0, 19760);  // rwDMAFlipData+0x3A0
        sw(v1, s1, 19752);  // rwDMAFlipData+0x398
        s1 = dsll32(s3, 0);
        s0 = a0 & s0;
        v0 = dsll32(s3, 17);
        v1 = dsrl32(v0, 26);
        a0 = dsrl32(s1, 20);
        s0 = s0 | a1;
        v1 = v1 & 0x3F;
        a1 = a0 & 0xFFF;
        v1 = sll(v1, 9);
        a0 = si(-32257);
        v0 = dsll32(s3, 12);
        a0 = s0 & a0;
        v0 = dsrl32(v0, 27);
        v1 = a0 | v1;
        v0 = v0 & 0x1F;
        s0 = v1 & t7;
        v0 = sll(v0, 15);
        v1 = 0x960000;
        v0 = s0 | v0;
        lw(s1, v1, 19652);  // rwDMAFlipData+0x334
        a1 = sll(a1, 20);
        a0 = 0x960000;
        v1 = v0 & t6;
        s2 = dsll32(s1, 10);
        v1 = v1 | a1;
        v0 = 0x960000;
        sw(v1, a0, 19760);  // rwDMAFlipData+0x3A0
        s4 = s1 & 0x7FF;
        v1 = 0x960000;
        lw(s3, v0, 19764);  // rwDMAFlipData+0x3A4
        lw(s0, v1, 19768);  // rwDMAFlipData+0x3A8
        s1 = dsll32(s1, 0);
        a0 = 0x960000;
        a1 = 0x960000;
        v0 = 0x960000;
        v1 = si(-2048);
        lw(v0, v0, 19656);  // rwDMAFlipData+0x338
        s3 = s3 & v1;
        v1 = dsrl32(s2, 21);
        s3 = s3 | s4;
        v1 = v1 & 0x7FF;
        s2 = sll(v1, 11);
        v1 = s3 & t5;
        s2 = v1 | s2;
        v1 = dsrl32(s1, 22);
        v1 = v1 & 0x3FF;
        s1 = s2 & t4;
        s2 = sll(v1, 22);
        v1 = s0 & t3;
        s1 = s1 | s2;
        s0 = v0 & 0xFFF;
        sw(s1, a0, 19764);  // rwDMAFlipData+0x3A4
        v1 = v1 | s0;
        a0 = v1 & t2;
        v1 = dsll32(v0, 9);
        s0 = dsrl32(v1, 21);
        v1 = dsll32(v0, 5);
        s0 = s0 & 0x7FF;
        v1 = dsrl32(v1, 28);
        s0 = sll(s0, 12);
        a0 = a0 | s0;
        v1 = v1 & 0xF;
        s0 = sll(v1, 23);
        a0 = a0 & t1;
        v1 = dsll32(v0, 3);
        s0 = a0 | s0;
        v1 = dsrl32(v1, 30);
        v0 = dsll32(v0, 0);
        a0 = v1 & 0x3;
        v0 = dsrl32(v0, 29);
        v1 = s0 & t0;
        a0 = sll(a0, 27);
        v1 = v1 | a0;
        v0 = v0 & 0x7;
        a0 = sll(v0, 29);
        v1 = v1 & a3;
        v1 = v1 | a0;
        v0 = 0x960000;
        lw(a0, v0, 19660);  // rwDMAFlipData+0x33C
        s0 = 0x960000;
        sw(v1, a1, 19768);  // rwDMAFlipData+0x3A8
        v1 = 0x960000;
        a1 = 0x960000;
        lw(v1, v1, 19664);  // rwDMAFlipData+0x340
        v0 = 0x960000;
        s5 = a0 & 0xFFF;
        lw(s4, v0, 19772);  // rwDMAFlipData+0x3AC
        s3 = dsll32(a0, 9);
        s2 = dsll32(a0, 0);
        a0 = dsrl32(s3, 21);
        a0 = a0 & 0x7FF;
        s3 = sll(a0, 12);
        v0 = 0x960000;
        s4 = s4 & t3;
        lw(s1, v0, 19776);  // rwDMAFlipData+0x3B0
        s4 = s4 | s5;
        a0 = s4 & t2;
        s3 = a0 | s3;
        a0 = si(-512);
        a0 = s1 & a0;
        v0 = 0x960000;
        s1 = dsrl32(s2, 23);
        lw(v0, v0, 19668);  // rwDMAFlipData+0x344
        s2 = s3 & a2;
        s3 = s1 & 0x1FF;
        s1 = v1 & 0x1FF;
        s1 = a0 | s1;
        a0 = sll(s3, 23);
        s2 = s2 | a0;
        a0 = si(-32257);
        sw(s2, s0, 19772);  // rwDMAFlipData+0x3AC
        s1 = s1 & a0;
        a0 = dsll32(v1, 17);
        s0 = dsrl32(a0, 26);
        a0 = dsll32(v1, 12);
        s0 = s0 & 0x3F;
        a0 = dsrl32(a0, 27);
        s0 = sll(s0, 9);
        a0 = a0 & 0x1F;
        s1 = s1 | s0;
        s0 = sll(a0, 15);
        v1 = dsll32(v1, 0);
        a0 = s1 & t7;
        t7 = a0 | s0;
        s1 = 0x960000;
        a0 = dsrl32(v1, 20);
        s0 = 0x960000;
        v1 = t7 & t6;
        a0 = a0 & 0xFFF;
        a0 = sll(a0, 20);
        t7 = si(-2048);
        a0 = v1 | a0;
        t6 = v0 & 0x7FF;
        sw(a0, a1, 19776);  // rwDMAFlipData+0x3B0
        v1 = 0x960000;
        lw(a1, v1, 19780);  // rwDMAFlipData+0x3B4
        a0 = dsll32(v0, 10);
        v0 = dsll32(v0, 0);
        v0 = dsrl32(v0, 22);
        v0 = v0 & 0x3FF;
        a1 = a1 & t7;
        v1 = dsrl32(a0, 21);
        a1 = a1 | t6;
        v1 = v1 & 0x7FF;
        a0 = sll(v1, 11);
        t5 = a1 & t5;
        a0 = t5 | a0;
        v1 = sll(v0, 22);
        t4 = a0 & t4;
        v0 = 0x960000;
        t4 = t4 | v1;
        a0 = 0x960000;
        lw(v0, v0, 19672);  // rwDMAFlipData+0x348
        a1 = 0x960000;
        lw(v1, a0, 19788);  // rwDMAFlipData+0x3BC
        t6 = 0x960000;
        lw(t7, s0, 19784);  // rwDMAFlipData+0x3B8
        sw(t4, s1, 19780);  // rwDMAFlipData+0x3B4
        lw(a1, a1, 19676);  // rwDMAFlipData+0x34C
        t5 = v0 & 0xFFF;
        a0 = dsll32(v0, 9);
        v1 = v1 & t3;
        t4 = t7 & t3;
        a0 = dsrl32(a0, 21);
        t4 = t4 | t5;
        a0 = a0 & 0x7FF;
        t5 = sll(a0, 12);
        t4 = t4 & t2;
        a0 = dsll32(v0, 5);
        t4 = t4 | t5;
        a0 = dsrl32(a0, 28);
        t1 = t4 & t1;
        t3 = a0 & 0xF;
        a0 = dsll32(v0, 3);
        t3 = sll(t3, 23);
        v0 = dsll32(v0, 0);
        a0 = dsrl32(a0, 30);
        t3 = t1 | t3;
        v0 = dsrl32(v0, 29);
        t1 = a0 & 0x3;
        a0 = t3 & t0;
        t0 = sll(t1, 27);
        a0 = a0 | t0;
        a0 = a0 & a3;
        a3 = v0 & 0x7;
        v0 = a1 & 0xFFF;
        v0 = v1 | v0;
        v1 = sll(a3, 29);
        a0 = a0 | v1;
        v1 = v0 & t2;
        sw(a0, t6, 19784);  // rwDMAFlipData+0x3B8
        v0 = dsll32(a1, 9);
        a0 = dsrl32(v0, 21);
        v0 = dsll32(a1, 0);
        a0 = a0 & 0x7FF;
        v0 = dsrl32(v0, 23);
        a0 = sll(a0, 12);
        v1 = v1 | a0;
        v0 = v0 & 0x1FF;
        a0 = sll(v0, 23);
        v1 = v1 & a2;
        a0 = v1 | a0;
        v0 = 0x960000;
        v1 = 0x960000;
        sw(a0, v0, 19788);  // rwDMAFlipData+0x3BC
        v1 = addiu(v1, 19808);  // &rwDMAFlipData+0x3D0
        a0 = 0x960000;
        a1 = addiu(v1, 127);  // &rwDMAFlipData+0x44F
        a0 = addiu(a0, 18832);  // &rwDMAFlipData
        jal(ctx, 0x4E26A8u, gen::fn_SyncDCache_00503a58);
        sw(zero, gp, -17016);  // g_skyFrameCount
        a0 = 0x960000;
        lw(a1, gp, -17016);  // g_skyFrameCount
        a0 = addiu(a0, 18832);  // &rwDMAFlipData
        v0 = addiu(a1, 1);
        link(ctx, 0x4E26C4u);  // $ra first: the delay slot below depends on it
        sw(v0, gp, -17016);  // g_skyFrameCount
        call(ctx, gen::fn_sceGsSwapDBuffDc_004fa738);
        for (;;) {
            // 0x004e26cc
            charge(ctx, 7);
            a0 = 1;
            a1 = 0;
            jal(ctx, 0x4E26D0u, gen::fn_sceGsSyncPath_004f99d0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004e26e8
        charge(ctx, 15);
        v1 = 4;
        v0 = 0x10010000;
        sw(v1, v0, -8176);  // 0x1000E010 D_STAT
        v0 = 0x960000;
        sw(zero, v0, 19804);  // rwDMAFlipData+0x3CC
        v0 = 0x960000;
        sw(zero, v0, 19800);  // rwDMAFlipData+0x3C8
        v0 = 0x960000;
        sw(zero, v0, 19796);  // rwDMAFlipData+0x3C4
        v0 = 0x960000;
        link(ctx, 0x4E2710u);  // $ra first: the delay slot below depends on it
        sw(zero, v0, 19792);
        call(ctx, gen::fn__rwDMADmaOpen_004d67b0);
        s0 = v0;
        if (s0 == 0) {
            // 0x004e2b1c
            charge(ctx, 4);
            jal(ctx, 0x4E2B1Cu, gen::fn_sub_4F0AD0_004f0ad0);
            backedge(ctx);
        } else {
            // 0x004e2724
            charge(ctx, 33);
            v1 = 0x960000;
            v0 = 0x960000;
            ld(t0, v1, 18928);  // rwDMAFlipData+0x60
            ld(a3, v0, 18944);  // rwDMAFlipData+0x70
            v1 = 0x960000;
            sd(t0, gp, -17080);  // 0x7CEA38
            ld(a2, v1, 19040);  // rwDMAFlipData+0xD0
            v0 = 0x960000;
            ld(a1, v0, 18960);  // rwDMAFlipData+0x80
            sd(a3, gp, -17088);  // 0x7CEA30
            v1 = si(-9);
            sd(a2, gp, -17072);  // 0x7CEA40
            a0 = dsll32(v1, 0);
            v0 = 1;
            v1 = 0xFFFF;
            sw(v0, gp, -16860);  // 0x7CEB14
            v0 = dsll(v1, 16);
            v0 = v0 | 0xFFFF;
            v0 = v0 | a0;
            a0 = a1 & v0;
            v0 = dsra(a0, 4);
            sd(a0, gp, -17064);  // 0x7CEA48
            v1 = v0 & 0xFFF;
            v0 = dsra32(a0, 4);
            sd(v1, gp, -17008);  // 0x7CEA80
            v0 = v0 & 0xFFF;
            link(ctx, 0x4E278Cu);  // $ra first: the delay slot below depends on it
            sd(v0, gp, -17000);  // 0x7CEA88
            call(ctx, gen::fn_setInitialRenderState_004dfdd0);
            v0 = 0x960000;
            lw(v0, v0, 22332);  // customMode+0xC
            v0 = v0 & 0x4;
            if (v0 == 0) {
                // 0x004e27b4
                charge(ctx, 1);
                sb(zero, gp, -17240);  // g_rwDMAFsaaEnabled
            } else {
                // 0x004e27a8
                charge(ctx, 3);
                v0 = 1;
                sb(v0, gp, -17240);  // g_rwDMAFsaaEnabled
            }
            // 0x004e27b8
            charge(ctx, 5);
            v0 = 0x960000;
            lw(v0, v0, 22356);  // g_skyDisplayMode+0xC
            v0 = v0 & 0x100;
            if (v0 != 0) {
                // 0x004e2b2c
                charge(ctx, 5);
                a0 = 0x960000;
                a0 = addiu(a0, 18832);  // &rwDMAFlipData
                jal(ctx, 0x4E2B30u, gen::fn_sub_4E0540_004e0540);
                v0 = 1;
                backedge(ctx);
            } else {
                // 0x004e27cc
                charge(ctx, 1);
                v0 = 1;
            }
            // 0x004e27d0
            charge(ctx, 1);
            sw(v0, gp, -16936);  // 0x7CEAC8
        }
        // 0x004e27d4
        charge(ctx, 2);
        v0 = s0;
    }
    // 0x004e2b40 (the shared epilogue, written out on this path)
    charge(ctx, 12);
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

// 0x004E3630 sub_4E3630 -- 8 bytes; leaf frame (no stack)
// Returns the word at 0x7CEA70. Leaf.
void sub_4E3630(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, gp{ctx, 28};
    // 0x004e3630
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, gp, -17024);  // 0x7CEA70
}

// 0x004EC510 sub_4EC510 -- 912 bytes; frame 0x140: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Builds the overloaded Sky pipeline descriptors (the xmmword tables at 0x965850..0x965A10).
void sub_4EC510(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, t8{ctx, 24}, t9{ctx, 25}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x004ec510
    enter(ctx, 154);  // entry check point + this block's cycles
    sp = addiu(sp, -0x140);
    v0 = 0x6C0D0000;
    sd(ra, sp, 0x90);
    v0 = v0 | 0x3F0;
    sq(fp, sp, 0x80);
    t2 = 0x10000000;
    sq(s7, sp, 0x70);
    v1 = dsll32(v0, 0);
    sq(s6, sp, 0x60);
    v0 = t2 | 0xD;
    sq(s5, sp, 0x50);
    pcpyld(a0, v1, v0);
    sq(s4, sp, 0x40);
    v0 = 0x960000;
    sq(s3, sp, 0x30);
    v1 = 0x6C030000;
    sq(s2, sp, 0x20);
    t0 = 0x960000;
    sq(s1, sp, 0x10);
    t5 = 0;
    sq(s0, sp, 0x0);
    t3 = t2 | 0x1;
    sq(a0, v0, 23056);  // 0x965A10
    pcpyld(s4, t5, t3);
    v0 = v1 | 0x3F9;
    lw(t4, gp, -17120);  // 0x7CEA10
    v1 = dsll32(v0, 0);
    t7 = 0;
    v0 = t2 | 0x3;
    a3 = 0x960000;
    pcpyld(a0, v1, v0);
    v0 = 0x960000;
    v1 = 0;
    sq(a0, v0, 23040);  // 0x965A00
    a2 = 0x960000;
    v0 = 0;
    a1 = 0x960000;
    pcpyld(a0, v1, v0);
    v0 = 0x960000;
    v1 = 0x44FF0000;
    sq(a0, v0, 22784);  // 0x965900
    s6 = 0x960000;
    v0 = v1 | 0xFDFF;
    lw(t1, t4, 0);
    mtc1(v0, f2);
    a0 = 1042;
    s7 = 0x960000;
    fp = 0x960000;
    v0 = 0x30000000;
    v1 = v0 | 0x4000;
    v0 = 1;
    v1 = dsll32(v1, 0);
    v0 = v0 | v1;
    pcpyld(s5, a0, v0);
    v0 = sra(t1, 1);
    v1 = 0;
    mtc1(v0, f1);
    a0 = 0x960000;
    mtc1(t1, f0);
    cvt_s_w(f1, f1);
    v0 = 0x60000000;
    t1 = t2 | 0xA;
    v0 = v0 | 0x1;
    pcpyld(s2, t5, t1);
    pcpyld(s3, v1, v0);
    t5 = 0x15000000;
    t1 = 0x11000000;
    t5 = dsll32(t5, 0);
    v0 = 0x960000;
    cvt_s_w(f0, f0);
    t6 = t1 | t5;
    pcpyld(t9, t1, t7);
    t1 = 0x960000;
    t5 = 0;
    sq(t1, sp, 0x130);
    pcpyld(s1, t7, t6);
    t6 = 0x17000000;
    t1 = 0x2000000;
    t6 = dsll32(t6, 0);
    t1 = t1 | 0x1E1;
    sub_s(f1, f2, f1);
    t6 = t2 | t6;
    pcpyld(t8, t5, t2);
    t2 = dsll32(t1, 0);
    v1 = 0x960000;
    t1 = 0x960000;
    div_s(f0, f0, f1);
    sq(t1, sp, 0x120);
    pcpyld(s0, t5, t6);
    t6 = 0x3000000;
    t1 = t6 | t2;
    pcpyld(t7, t5, t1);
    t1 = 0x960000;
    t2 = 0x3F000000;
    sq(t1, sp, 0x110);
    t5 = 0x960000;
    t1 = 0x960000;
    sq(t5, sp, 0xD0);
    sq(t1, sp, 0x100);
    t5 = 0x960000;
    t1 = 0x960000;
    sq(t5, sp, 0xC0);
    sq(t1, sp, 0xF0);
    t5 = 0x960000;
    t1 = 0x960000;
    sq(t5, sp, 0xB0);
    sq(t1, sp, 0xE0);
    t5 = 0x960000;
    sq(t5, sp, 0xA0);
    t1 = 0x3F800000;
    t2 = t2 | 0x8312;
    t1 = t1 | 0x149;
    t6 = 0;
    t5 = 0;
    swc1(f0, t0, 22896);  // 0x965970
    lw(t0, t4, 4);
    sq(s2, v0, 22624);  // 0x965860
    mtc1(t0, f0);
    lq(v0, sp, 0x130);
    sq(s3, a0, 22672);  // 0x965890
    cvt_s_w(f0, f0);
    a0 = sra(t0, 1);
    sq(s5, a2, 22688);  // 0x9658A0
    sq(s1, s6, 22752);  // 0x9658E0
    sq(s0, s7, 22608);  // 0x965850
    sq(t9, fp, 0x59C0);
    sq(t8, v0, 22992);
    lq(v0, sp, 0x120);
    mtc1(a0, f1);
    sq(s4, a1, 22640);  // 0x965870
    cvt_s_w(f1, f1);
    sq(s4, v1, 22656);  // 0x965880
    sq(t7, v0, 22960);
    lq(v0, sp, 0x110);
    sub_s(f1, f2, f1);
    div_s(f0, f0, f1);
    sw(t2, v0, 23024);
    lq(v0, sp, 0x100);
    sw(t2, v0, 23028);
    lq(v0, sp, 0xF0);
    sw(t2, v0, 23032);
    lq(v0, sp, 0xE0);
    sw(t2, v0, 23036);
    lq(v0, sp, 0xA0);
    sw(t2, v0, 23020);
    lq(v0, sp, 0xD0);
    swc1(f0, a3, 22900);  // 0x965974
    sw(t1, v0, 23008);
    lq(v0, sp, 0xC0);
    sw(t1, v0, 23012);
    lq(v0, sp, 0xB0);
    sw(t1, v0, 23016);
    a0 = 32;
    for (;;) {
        // 0x004ec778
        charge(ctx, 11);
        t6 = addiu(t6, 1);
        t5 = addiu(t5, 12);
        v0 = addiu(t6, 15);
        v1 = srl(v0, 4);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v0 = addu(a0, v0);
        v0 = addu(v0, t5);
        v0 = sltiu(v0, 511);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004ec7a4
    charge(ctx, 5);
    v0 = addiu(t6, -1);
    a2 = 0;
    sw(v0, gp, -16868);  // 0x7CEB0C
    a1 = 0;
    a0 = 32;
    for (;;) {
        // 0x004ec7b8
        charge(ctx, 11);
        a2 = addiu(a2, 1);
        a1 = addiu(a1, 12);
        v0 = addiu(a2, 15);
        v1 = srl(v0, 4);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v0 = addu(a0, v0);
        v0 = addu(v0, a1);
        v0 = sltiu(v0, 511);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004ec7e4
    charge(ctx, 47);
    v0 = addiu(a2, -1);
    a0 = 0x11000000;
    sw(v0, gp, -16872);  // 0x7CEB08
    v0 = dsll32(a0, 0);
    v1 = a0 | v0;
    v0 = 0x960000;
    pcpyld(v1, a0, v1);
    sq(v1, v0, 22704);  // 0x9658B0
    v0 = 0;
    v1 = 0x960000;
    pcpyld(a0, v0, a0);
    sw(zero, v1, 22736);  // 0x9658D0
    v0 = 0x960000;
    v1 = 0x960000;
    sq(a0, v0, 22768);  // 0x9658F0
    v0 = 0x960000;
    sw(zero, v1, 22744);  // 0x9658D8
    sw(zero, v0, 22740);  // 0x9658D4
    v1 = 0x6C010000;
    v0 = 0x960000;
    sw(zero, v0, 22748);  // 0x9658DC
    v0 = v1 | 0x3D4;
    a0 = dsll32(v0, 0);
    v0 = 0x1000000;
    v1 = v0 | 0x404;  // &0x1000404
    a0 = v1 | a0;
    v0 = 0x960000;
    pcpyld(a0, a0, t3);
    v1 = 0x960000;
    sq(a0, v0, 22720);  // 0x9658C0
    v1 = addiu(v1, 22752);  // &0x9658E0
    a0 = 0x960000;
    a1 = addiu(v1, 127);  // &0x96595F
    a0 = addiu(a0, 22720);  // &0x9658C0
    jal(ctx, 0x4EC868u, gen::fn_SyncDCache_00503a58);
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
    sp = addiu(sp, 0x140);
}

// 0x004EEBC0 _rwSkyOverloadPipelines -- 68 bytes; leaf frame (no stack)
// Overloads the Sky render pipelines (sub_4EC510).
void _rwSkyOverloadPipelines(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x004eebc0
    enter(ctx, 17);  // entry check point + this block's cycles
    a0 = 0x4F0000;
    v1 = 0x4F0000;
    a0 = addiu(a0, -13728);  // &SkyIm2DRenderLine
    v0 = 0x960000;
    sw(a0, v0, 152);  // 0x960098
    v1 = addiu(v1, -13088);  // &SkyIm2DRenderTriangle
    v0 = 0x960000;
    a0 = 0x4F0000;
    sw(v1, v0, 156);  // 0x96009C
    a0 = addiu(a0, -9312);  // &SkyIm2DRenderPrimitive
    v0 = 0x960000;
    v1 = 0x4F0000;
    sw(a0, v0, 160);  // pfn_RwIm2DRenderPrimitive
    v1 = addiu(v1, -5296);  // &SkyIm2DRenderIndexedPrimitive
    v0 = 0x960000;
    sw(v1, v0, 164);  // 0x9600A4
    gen::fn_sub_4EC510_004ec510(ctx);  // tail call
}

// 0x004F0990 sub_4F0990 -- 308 bytes; frame 0x10: ra sp+0x0
// SkyStart helper: fills the camera / raster callback table (0x77F200..) and calls one hook through $jalr.
void sub_4F0990(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f0990
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x780000;
    sd(ra, sp, 0x0);
    v1 = 0x780000;
    sw(a0, v0, -3532);  // 0x77F234
    v0 = 0x780000;
    sw(a0, v1, -3560);  // 0x77F218
    lw(v0, v0, -3584);  // 0x77F200
    v1 = 0x780000;
    sw(zero, gp, -16856);  // 0x7CEB18
    sw(a1, v1, -3556);  // 0x77F21C
    if (v0 == 0) {
        // 0x004f09c0
        charge(ctx, 4);
        v1 = 0x4F0000;
        v0 = 0x780000;
        v1 = addiu(v1, -1552);  // &sub_4EF9F0
        sw(v1, v0, -3552);  // 0x77F220
        goto L_004f09d0;
    }
    // 0x004f0a2c
    charge(ctx, 12);
    lw(a0, gp, -20228);  // 0x7CDDEC
    v0 = 0x40000;
    a1 = v0 | 0x411;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    v1 = sll(a0, 1);
    v1 = addu(v1, a0);
    a0 = sll(v1, 2);
    jalr(ctx, 0x4F0A48u, v0.u());
    v1 = 0x780000;
    sw(v0, v1, -3564);  // 0x77F214
    if (v0 != 0) {
        // 0x004f0a64
        charge(ctx, 21);
        a3 = si(-1);
        v0 = 0x780000;
        sw(a3, v0, -3580);  // 0x77F204
        a1 = 0x4F0000;
        v0 = 0x780000;
        a1 = addiu(a1, 736);  // &sub_4F02E0
        sw(a3, v0, -3576);  // 0x77F208
        a0 = 0x780000;
        v0 = 0x780000;
        lw(a2, gp, -20228);  // 0x7CDDEC
        sw(a1, v0, -3552);  // 0x77F220
        v1 = 0x780000;
        v0 = 0x780000;
        sw(zero, v0, -3548);  // 0x77F224
        v0 = 0x780000;
        sw(a3, v0, -3540);  // 0x77F22C
        v0 = 0x780000;
        sw(a2, a0, -3572);  // 0x77F20C
        sw(a3, v0, -3536);  // 0x77F230
        sw(a2, v1, -3568);  // 0x77F210
        backedge(ctx);
    L_004f09d0:
        charge(ctx, 23);
        v0 = 0x10000000;
        a0 = 14;
        v1 = dsll32(v0, 0);
        v0 = 0x8005;
        v1 = v0 | v1;
        pcpyld(v1, a0, v1);
        v0 = 0x960000;
        a0 = 0;
        sq(v1, v0, 23152);  // 0x965A70
        v1 = 63;
        v0 = 0x960000;
        pcpyld(v1, v1, a0);
        sq(v1, v0, 23104);  // 0x965A40
        v1 = 81;
        v0 = 0x960000;
        pcpyld(v1, v1, a0);
        sq(v1, v0, 23120);  // 0x965A50
        v1 = 83;
        v0 = 0x960000;
        pcpyld(v1, v1, a0);
        sq(v1, v0, 23136);  // 0x965A60
        v0 = 1;
    } else {
        // 0x004f0a5c
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004f0ab8 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x004F8EB0 sceGsResetGraph -- 416 bytes, 2 chunks; frame 0x50: s3 sp+0x30, s2 sp+0x20, s1 sp+0x10, ra sp+0x40, s0 sp+0x0
// sceGsResetGraph: resets the GS (CSR), sets SMODE2 / PMODE / IMR for the requested mode and field.
void sceGsResetGraph(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f8eb0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    a0 = sll(a0, 16);
    sd(s3, sp, 0x30);
    a1 = sll(a1, 16);
    sd(s2, sp, 0x20);
    a2 = sll(a2, 16);
    sd(s1, sp, 0x10);
    a3 = sll(a3, 16);
    sd(ra, sp, 0x40);
    a0 = sra(a0, 16);
    sd(s0, sp, 0x0);
    s1 = sra(a1, 16);
    s2 = sra(a2, 16);
    v0 = 1;
    s3 = sra(a3, 16);
    if (a0 == v0) {
        // 0x004f8fb0
        charge(ctx, 6);
        v0 = 0x12000000;
        v1 = 256;
        v0 = v0 | 0x1000;
        sd(v1, v0, 0);  // 0x12001000 GS CSR
        ld(ra, sp, 0x40);
        // 0x004f9028
        charge(ctx, 1);
        ld(s3, sp, 0x30);
        // 0x004f902c (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s2, sp, 0x20);
        ld(s1, sp, 0x10);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        return;
    }
    // 0x004f8ef0
    charge(ctx, 3);
    v0 = slti(a0, 2);
    if (v0 == 0) {
        v0 = 5;
        // 0x004f8f0c
        charge(ctx, 2);
        ld(ra, sp, 0x40);
        if (a0 != v0) {
            // 0x004f8f14
            charge(ctx, 2);
            ld(s3, sp, 0x30);
            // 0x004f902c (the shared epilogue, written out on this path)
            charge(ctx, 5);
            ld(s2, sp, 0x20);
            ld(s1, sp, 0x10);
            ld(s0, sp, 0x0);
            sp = addiu(sp, 0x50);
            return;
        }
        // 0x004f8fc8
        charge(ctx, 24);
        jal(ctx, 0x4F8FC8u, gen::fn_sceGsGetGParam_004f9040);
        v1 = 0x12000000;
        s0 = v0;
        v1 = v1 | 0x1000;
        a2 = sltu(0, s3);
        ld(v0, v1, 0);  // 0x12001000 GS CSR
        a0 = s1 & 0x1;
        sh(a2, s0, 4);
        a1 = s2 & 0xFF;
        v0 = dsrl(v0, 16);
        sh(s1, s0, 0);
        v0 = v0 & 0xFF;
        sh(s2, s0, 2);
        v0 = v0 & 0xFFFF;
        a2 = s3 & 0x1;
        sh(v0, s0, 6);
        ld(ra, sp, 0x40);
        ld(s3, sp, 0x30);
        ld(s2, sp, 0x20);
        ld(s1, sp, 0x10);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        // 0x00502d60 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        v1 = 2;
        syscall(ctx, 0x502D64u);
        return;
    }
    // 0x004f8efc
    charge(ctx, 2);
    ld(ra, sp, 0x40);
    if (a0 != 0) {
        // 0x004f8f04
        charge(ctx, 2);
        ld(s3, sp, 0x30);
        // 0x004f902c (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s2, sp, 0x20);
        ld(s1, sp, 0x10);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        return;
    }
    // 0x004f8f1c
    charge(ctx, 20);
    jal(ctx, 0x4F8F1Cu, gen::fn_sceGsGetGParam_004f9040);
    v1 = 0x12000000;
    a0 = 512;
    v1 = v1 | 0x1000;
    s0 = v0;
    sd(a0, v1, 0);  // 0x12001000 GS CSR
    sh(s1, s0, 0);
    a0 = 0xFF00;
    ld(v0, v1, 0);  // 0x12001000 GS CSR
    sh(s2, s0, 2);
    v0 = dsrl(v0, 16);
    v0 = v0 & 0xFF;
    v0 = v0 & 0xFFFF;
    link(ctx, 0x4F8F54u);  // $ra first: the delay slot below depends on it
    sh(v0, s0, 6);
    call(ctx, gen::fn__sceGsPutIMR_005034a0);
    v1 = sltu(0, s3);
    lw(v0, s0, 8);
    sh(v1, s0, 4);
    if (v0 != 0) {
        // 0x004f8f6c
        charge(ctx, 7);
        a0 = 2;
        jal(ctx, 0x4F8F6Cu, gen::fn_DisableIntc_00503c40);
        lw(a1, s0, 12);
        a0 = 2;
        jal(ctx, 0x4F8F78u, gen::fn__sceRemoveIntcHandler_00502e60);
        sw(zero, s0, 12);
        sw(zero, s0, 8);
    }
    // 0x004f8f88
    charge(ctx, 10);
    a0 = s1 & 0x1;
    a1 = s2 & 0xFF;
    a2 = s3 & 0x1;
    ld(ra, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
    // 0x00502d60 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    v1 = 2;
    syscall(ctx, 0x502D64u);
}

// 0x004F9050 sceGsResetPath -- 104 bytes; leaf frame (no stack)
// sceGsResetPath: resets VIF1 / GIF and the PATH3 masks.
void sceGsResetPath(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x004f9050
    enter(ctx, 26);  // entry check point + this block's cycles
    v0 = 0x10000000;
    a3 = 1;
    v0 = v0 | 0x3C10;
    v1 = 0x10000000;
    sw(a3, v0, 0);  // 0x10003C10 VIF1_FBRST
    v1 = v1 | 0x3C20;
    v0 = 2;
    a0 = 0;
    sw(v0, v1, 0);  // 0x10003C20 VIF1_ERR
    sync(ctx, 0);
    cfc2(a0, 28, false);  // cfc2
    a0 = a0 | 0x200;
    ctc2(a0, 28, false);  // ctc2
    sync(ctx, 16);
    a1 = 0x780000;
    a2 = 0x10000000;
    a1 = addiu(a1, -3440);  // &0x77F290
    a2 = a2 | 0x5000;
    lq(a0, a1, 0);  // 0x77F290
    v1 = 0x10000000;
    v1 = v1 | 0x3000;
    sq(a0, a2, 0);  // 0x10005000 VIF1 FIFO
    lq(v0, a1, 16);  // 0x77F2A0
    sq(v0, a2, 0);  // 0x10005000 VIF1 FIFO
    sw(a3, v1, 0);  // 0x10003000 GIF_CTRL
}

// 0x004F94E0 sceGsPutDispEnv -- 188 bytes; frame 0x20: s0 sp+0x0, ra sp+0x10
// sceGsPutDispEnv: writes the display environment to PMODE / SMODE2 / DISPFB / DISPLAY / BGCOLOR.
void sceGsPutDispEnv(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f94e0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    s0 = a0;
    jal(ctx, 0x4F94ECu, gen::fn_sceGsGetGParam_004f9040);
    lh(v1, v0, 6);
    v0 = 1;
    ld(a0, s0, 0);
    if (v1 != v0) {
        // 0x004f9544
        charge(ctx, 19);
        v1 = 0x12000000;
        v0 = 0x12000000;
        a2 = 0x12000000;
        sd(a0, v1, 0);  // 0x12000000 GS PMODE
        v0 = v0 | 0x20;
        a2 = a2 | 0x90;
        a1 = 0x12000000;
        ld(v1, s0, 8);
        a1 = a1 | 0xA0;
        a0 = 0x12000000;
        sd(v1, v0, 0);  // 0x12000020 GS SMODE2
        a0 = a0 | 0xE0;
        ld(v0, s0, 16);
        sd(v0, a2, 0);  // 0x12000090 GS DISPFB2
        ld(v1, s0, 24);
        sd(v1, a1, 0);  // 0x120000A0 GS DISPLAY2
        ld(v0, s0, 32);
        sd(v0, a0, 0);  // 0x120000E0 GS BGCOLOR
        ld(ra, sp, 0x10);
    } else {
        // 0x004f9504
        charge(ctx, 16);
        v0 = 0x12000000;
        v1 = 0x12000000;
        a2 = 0x12000000;
        sd(a0, v0, 0);  // 0x12000000 GS PMODE
        v1 = v1 | 0x70;
        a2 = a2 | 0x80;
        a0 = 0x12000000;
        ld(a1, s0, 16);
        a0 = a0 | 0xC0;
        sd(a1, v1, 0);  // 0x12000070 GS DISPFB1
        ld(v0, s0, 24);
        sd(v0, a2, 0);  // 0x12000080 GS DISPLAY1
        ld(v1, s0, 32);
        sd(v1, a0, 0);  // 0x120000C0 GS EXTDATA
        ld(ra, sp, 0x10);
    }
    // 0x004f9590 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x004F9850 sceGsPutDrawEnv -- 232 bytes; frame 0x10: ra sp+0x0
// sceGsPutDrawEnv: sends the drawing environment through GIF (D2), with an error print on misuse.
void sceGsPutDrawEnv(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x004f9850
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = 0x10000000;
    sd(ra, sp, 0x0);
    v1 = v1 | 0xA000;
    a2 = a0;
    lw(v0, v1, 0);  // 0x1000A000 D2 GIF CHCR
    v0 = v0 & 0x100;
    a0 = 0;
    if (v0 != 0) {
        // 0x004f9874
        charge(ctx, 5);
        v1 = 0x10000000;
        a1 = 0x1000000;
        v1 = v1 | 0xA000;
        v0 = a0;
        for (;;) {
            // 0x004f9888
            charge(ctx, 3);
            v0 = sltu(a1, v0);
            a0 = addiu(a0, 1);
            if (v0 != 0) {
                goto L_004f98f0;
            }
            // 0x004f9894
            charge(ctx, 4);
            lw(v0, v1, 0);
            v0 = v0 & 0x100;
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = a0;
            if (!cc) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004f98a4
    charge(ctx, 12);
    ld(v0, a2, 0);
    v1 = 0x10000000;
    v1 = v1 | 0xA020;
    a0 = 0x70000000;
    v0 = v0 & 0x7FFF;
    a1 = a2 & a0;
    v0 = dsll32(v0, 0);
    v0 = dsra32(v0, 0);
    v0 = addiu(v0, 1);
    sw(v0, v1, 0);  // 0x1000A020 D2 GIF QWC
    v0 = 0xFFF0000;
    if (a1 != a0) {
        // 0x004f9904
        charge(ctx, 4);
        v1 = 0x10000000;
        v0 = v0 | 0xFFFF;
        v1 = v1 | 0xA010;
        v0 = a2 & v0;
    } else {
        // 0x004f98d4
        charge(ctx, 7);
        v1 = 0x10000000;
        v0 = v0 | 0xFFFF;
        a0 = lui(0x8000);
        v0 = a2 & v0;
        v1 = v1 | 0xA010;
        v0 = v0 | a0;
    }
    // 0x004f9914
    charge(ctx, 6);
    sw(v0, v1, 0);
    v1 = 0x10000000;
    a0 = 257;
    v1 = v1 | 0xA000;
    v0 = 0;
    sw(a0, v1, 0);  // 0x1000A000 D2 GIF CHCR
    // 0x004f992c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    return;
L_004f98f0:
    charge(ctx, 5);
    a0 = 0x7C0000;
    a0 = addiu(a0, -12104);  // &0x7BD0B8
    jal(ctx, 0x4F98F4u, gen::fn_scePrintf_00505e48);
    v0 = si(-1);
    // 0x004f992c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x004F9938 sceGsSyncV -- 148 bytes; frame 0x20: s0 sp+0x0, ra sp+0x10
// sceGsSyncV: waits for the next vertical blank (VSync2 / VSync) and returns the field.
void sceGsSyncV(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f9938
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    jal(ctx, 0x4F9944u, gen::fn_sceGsGetGParam_004f9040);
    s0 = v0;
    lw(v0, s0, 8);
    if (v0 != 0) {
        // 0x004f9998
        charge(ctx, 8);
        jal(ctx, 0x4F9998u, gen::fn_VSync2_00503680);
        v0 = dsra(v0, 13);
        lh(v1, s0, 0);
        a0 = v0 & 0x1;
        v0 = 1;
        ld(ra, sp, 0x10);
        if (v1 == v0) {
            // 0x004f99b8
            charge(ctx, 2);
            v0 = dsll32(a0, 0);
            v0 = dsra32(v0, 0);
        }
    L_004f99c0:
        charge(ctx, 1);
        ld(s0, sp, 0x0);
    } else {
        // 0x004f995c
        charge(ctx, 6);
        jal(ctx, 0x4F995Cu, gen::fn_VSync_005035f0);
        lh(v1, s0, 0);
        v0 = 1;
        ld(ra, sp, 0x10);
        if (v1 != v0) {
            goto L_004f99c0;
        }
        // 0x004f9974
        charge(ctx, 9);
        v1 = 0x12000000;
        v1 = v1 | 0x1000;
        ld(v0, v1, 0);  // 0x12001000 GS CSR
        v0 = dsrl(v0, 13);
        v0 = v0 & 0x1;
        v0 = dsll32(v0, 0);
        v0 = dsra32(v0, 0);
        ld(s0, sp, 0x0);
    }
    // 0x004f99c4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x20);
}

// 0x004F99D0 sceGsSyncPath -- 788 bytes; frame 0x10: ra sp+0x0
// sceGsSyncPath: waits (with a timeout and a print) until the VIF1 / GIF DMA and the paths are idle.
void sceGsSyncPath(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x004f99d0
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = 0;
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x004f9c64
        charge(ctx, 29);
        v1 = 0x10000000;
        a1 = 0x10000000;
        v1 = v1 | 0x9000;
        a1 = a1 | 0xA000;
        lw(v0, v1, 0);  // 0x10009000 D1 VIF1 CHCR
        a0 = 0x10000000;
        lw(a2, a1, 0);  // 0x1000A000 D2 GIF CHCR
        a0 = a0 | 0x3C00;
        v0 = v0 & 0x100;
        lw(a1, a0, 0);  // 0x10003C00 VIF1_STAT
        v0 = sltu(0, v0);
        a2 = a2 & 0x100;
        a0 = v0 | 0x2;
        v1 = 0x1F000000;
        if (a2 != 0) v0 = a0;
        v1 = v1 | 0x3;
        a1 = a1 & v1;
        a0 = v0 | 0x4;
        if (a1 != 0) v0 = a0;
        cfc2(a2, 29, false);  // cfc2
        v1 = 0x10000000;
        a2 = a2 & 0x100;
        v1 = v1 | 0x3020;
        a1 = v0 | 0x8;
        lw(a0, v1, 0);  // 0x10003020 GIF_STAT
        if (a2 != 0) v0 = a1;
        v1 = v0 | 0x10;
        a0 = a0 & 0xC00;
        if (a0 != 0) v0 = v1;
    } else {
        // 0x004f99e0
        charge(ctx, 6);
        v0 = 0x10000000;
        v0 = v0 | 0x9000;
        lw(v1, v0, 0);  // 0x10009000 D1 VIF1 CHCR
        v1 = v1 & 0x100;
        cc = v1 == 0;  // the condition, before the delay slot changes it
        v1 = 0x10000000;
        if (!cc) {
            // 0x004f99f8
            charge(ctx, 4);
            a0 = 0x1000000;
            v1 = v1 | 0x9000;
            v0 = a1;
            for (;;) {
                // 0x004f9a08
                charge(ctx, 3);
                v0 = sltu(a0, v0);
                a1 = addiu(a1, 1);
                if (v0 != 0) {
                    goto L_004f9b2c;
                }
                // 0x004f9a14
                charge(ctx, 4);
                lw(v0, v1, 0);
                v0 = v0 & 0x100;
                cc = v0 != 0;  // the condition, before the delay slot changes it
                v0 = a1;
                if (!cc) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x004f9a24
        charge(ctx, 6);
        v0 = 0x10000000;
        v0 = v0 | 0xA000;
        lw(v1, v0, 0);  // 0x1000A000 D2 GIF CHCR
        v1 = v1 & 0x100;
        cc = v1 == 0;  // the condition, before the delay slot changes it
        v1 = 0x10000000;
        if (!cc) {
            // 0x004f9a3c
            charge(ctx, 3);
            a0 = 0x1000000;
            v1 = v1 | 0xA000;
            v0 = a1;
            for (;;) {
                // 0x004f9a48
                charge(ctx, 3);
                v0 = sltu(a0, v0);
                a1 = addiu(a1, 1);
                if (v0 != 0) {
                    goto L_004f9b38;
                }
                // 0x004f9a54
                charge(ctx, 4);
                lw(v0, v1, 0);
                v0 = v0 & 0x100;
                cc = v0 != 0;  // the condition, before the delay slot changes it
                v0 = a1;
                if (!cc) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x004f9a64
        charge(ctx, 8);
        v0 = 0x10000000;
        a0 = 0x1F000000;
        v0 = v0 | 0x3C00;
        a0 = a0 | 0x3;
        lw(v1, v0, 0);  // 0x10003C00 VIF1_STAT
        v1 = v1 & a0;
        cc = v1 == 0;  // the condition, before the delay slot changes it
        v1 = 0x1F000000;
        if (!cc) {
            // 0x004f9a84
            charge(ctx, 5);
            a0 = 0x10000000;
            a2 = 0x1000000;
            a0 = a0 | 0x3C00;
            v1 = v1 | 0x3;
            v0 = a1;
            for (;;) {
                // 0x004f9a98
                charge(ctx, 3);
                v0 = sltu(a2, v0);
                a1 = addiu(a1, 1);
                if (v0 != 0) {
                    goto L_004f9b44;
                }
                // 0x004f9aa4
                charge(ctx, 4);
                lw(v0, a0, 0);
                v0 = v0 & v1;
                cc = v0 != 0;  // the condition, before the delay slot changes it
                v0 = a1;
                if (!cc) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x004f9ab4
        charge(ctx, 4);
        cfc2(a2, 29, false);  // cfc2
        v0 = a2 & 0x100;
        v1 = 0x1000000;
        if (v0 != 0) {
            // 0x004f9ac4
            charge(ctx, 1);
            v0 = a1;
            for (;;) {
                // 0x004f9ac8
                charge(ctx, 3);
                v0 = sltu(v1, v0);
                a1 = addiu(a1, 1);
                if (v0 != 0) {
                    goto L_004f9b50;
                }
                // 0x004f9ad4
                charge(ctx, 4);
                cfc2(a2, 29, false);  // cfc2
                v0 = a2 & 0x100;
                cc = v0 != 0;  // the condition, before the delay slot changes it
                v0 = a1;
                if (!cc) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x004f9ae4
        charge(ctx, 6);
        v0 = 0x10000000;
        v0 = v0 | 0x3020;
        lw(v1, v0, 0);  // 0x10003020 GIF_STAT
        v1 = v1 & 0xC00;
        cc = v1 == 0;  // the condition, before the delay slot changes it
        v1 = 0x10000000;
        if (!cc) {
            // 0x004f9afc
            charge(ctx, 3);
            a0 = 0x1000000;
            v1 = v1 | 0x3020;
            v0 = a1;
            for (;;) {
                // 0x004f9b08
                charge(ctx, 3);
                v0 = sltu(a0, v0);
                a1 = addiu(a1, 1);
                if (v0 != 0) {
                    goto L_004f9b5c;
                }
                // 0x004f9b14
                charge(ctx, 4);
                lw(v0, v1, 0);
                v0 = v0 & 0xC00;
                cc = v0 != 0;  // the condition, before the delay slot changes it
                v0 = a1;
                if (!cc) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x004f9b24
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004f9cd8 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    return;
L_004f9b2c:
    charge(ctx, 3);
    a0 = 0x7C0000;
    a0 = addiu(a0, -12056);  // &0x7BD0E8
L_004f9b64:
    charge(ctx, 64);
    jal(ctx, 0x4F9B64u, gen::fn_scePrintf_00505e48);
    v0 = 0x10000000;
    a0 = 0x7C0000;
    v0 = v0 | 0x9000;
    a0 = addiu(a0, -12008);  // "\t<D1_CHCR=%08x:"
    link(ctx, 0x4F9B7Cu);  // $ra first: the delay slot below depends on it
    lw(a1, v0, 0);
    call(ctx, gen::fn_scePrintf_00505e48);
    v0 = 0x10000000;
    a0 = 0x7C0000;
    v0 = v0 | 0x9030;
    a0 = addiu(a0, -11992);  // "D1_TADR=%08x:"
    link(ctx, 0x4F9B94u);  // $ra first: the delay slot below depends on it
    lw(a1, v0, 0);
    call(ctx, gen::fn_scePrintf_00505e48);
    v0 = 0x10000000;
    a0 = 0x7C0000;
    v0 = v0 | 0x9010;
    a0 = addiu(a0, -11976);  // "D1_MADR=%08x:"
    link(ctx, 0x4F9BACu);  // $ra first: the delay slot below depends on it
    lw(a1, v0, 0);
    call(ctx, gen::fn_scePrintf_00505e48);
    v0 = 0x10000000;
    a0 = 0x7C0000;
    v0 = v0 | 0x9020;
    a0 = addiu(a0, -11960);  // &0x7BD148
    link(ctx, 0x4F9BC4u);  // $ra first: the delay slot below depends on it
    lw(a1, v0, 0);
    call(ctx, gen::fn_scePrintf_00505e48);
    v0 = 0x10000000;
    a0 = 0x7C0000;
    v0 = v0 | 0xA000;
    a0 = addiu(a0, -11944);  // "\t<D2_CHCR=%08x:"
    link(ctx, 0x4F9BDCu);  // $ra first: the delay slot below depends on it
    lw(a1, v0, 0);
    call(ctx, gen::fn_scePrintf_00505e48);
    v0 = 0x10000000;
    a0 = 0x7C0000;
    v0 = v0 | 0xA030;
    a0 = addiu(a0, -11928);  // "D2_TADR=%08x:"
    link(ctx, 0x4F9BF4u);  // $ra first: the delay slot below depends on it
    lw(a1, v0, 0);
    call(ctx, gen::fn_scePrintf_00505e48);
    v0 = 0x10000000;
    a0 = 0x7C0000;
    v0 = v0 | 0xA010;
    a0 = addiu(a0, -11912);  // "D2_MADR=%08x:"
    link(ctx, 0x4F9C0Cu);  // $ra first: the delay slot below depends on it
    lw(a1, v0, 0);
    call(ctx, gen::fn_scePrintf_00505e48);
    v0 = 0x10000000;
    a0 = 0x7C0000;
    v0 = v0 | 0xA020;
    a0 = addiu(a0, -11896);  // &0x7BD188
    link(ctx, 0x4F9C24u);  // $ra first: the delay slot below depends on it
    lw(a1, v0, 0);
    call(ctx, gen::fn_scePrintf_00505e48);
    v0 = 0x10000000;
    a0 = 0x7C0000;
    v0 = v0 | 0x3C00;
    a0 = addiu(a0, -11880);  // "\t<VIF1_STAT=%08x:"
    link(ctx, 0x4F9C3Cu);  // $ra first: the delay slot below depends on it
    lw(a1, v0, 0);
    call(ctx, gen::fn_scePrintf_00505e48);
    v0 = 0x10000000;
    a0 = 0x7C0000;
    v0 = v0 | 0x3020;
    a0 = addiu(a0, -11856);  // &0x7BD1B0
    link(ctx, 0x4F9C54u);  // $ra first: the delay slot below depends on it
    lw(a1, v0, 0);
    call(ctx, gen::fn_scePrintf_00505e48);
    v0 = si(-1);
    // 0x004f9cd8 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    return;
L_004f9b38:
    charge(ctx, 3);
    a0 = 0x7C0000;
    a0 = addiu(a0, -11832);  // &0x7BD1C8
    goto L_004f9b64;
L_004f9b44:
    charge(ctx, 3);
    a0 = 0x7C0000;
    a0 = addiu(a0, -11784);  // &0x7BD1F8
    goto L_004f9b64;
L_004f9b50:
    charge(ctx, 3);
    a0 = 0x7C0000;
    a0 = addiu(a0, -11736);  // &0x7BD228
    goto L_004f9b64;
L_004f9b5c:
    charge(ctx, 2);
    a0 = 0x7C0000;
    a0 = addiu(a0, -11696);  // &0x7BD250
    goto L_004f9b64;
}

// 0x004F9E28 sceGsExecStoreImage -- 1676 bytes; frame 0x90: s6 sp+0x70, s5 sp+0x60, s4 sp+0x50, s3 sp+0x40, s2 sp+0x30, s1 sp+0x20, s0 sp+0x10, ra sp+0x80
// sceGsExecStoreImage: GS-to-memory transfer (BUSDIR flip, VIF1 FIFO read, IMR saved and restored).
void sceGsExecStoreImage(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x004f9e28
    enter(ctx, 32);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(s6, sp, 0x70);
    sd(s5, sp, 0x60);
    s6 = 0;
    sd(s4, sp, 0x50);
    s5 = a1;
    sd(s3, sp, 0x40);
    s4 = a0;
    sd(s2, sp, 0x30);
    s3 = 0;
    sd(s1, sp, 0x20);
    s2 = 0;
    sd(s0, sp, 0x10);
    s1 = 0;
    sd(ra, sp, 0x80);
    s0 = 0;
    ld(t1, s4, 64);
    ld(v0, s4, 32);
    a0 = t1 & 0xFFF;
    v1 = dsrl32(t1, 0);
    v0 = dsrl(v0, 24);
    t0 = dsll32(a0, 0);
    t0 = dsra32(t0, 0);
    v0 = v0 & 0x3F;
    v1 = v1 & 0xFFF;
    a0 = dsll32(v0, 0);
    a0 = dsra32(a0, 0);
    a3 = dsll32(v1, 0);
    a3 = dsra32(a3, 0);
    v0 = sltiu(a0, 59);
    a1 = 0;
    if (v0 != 0) {
        // 0x004f9ea8
        charge(ctx, 7);
        v0 = 0x7C0000;
        v1 = sll(a0, 2);
        v0 = addiu(v0, -11424);  // &0x7BD360
        v1 = addu(v1, v0);
        lw(a0, v1, 0);
        switch (a0.u()) {
        case 0x4F9EC4u:  // table[0, 48]
            // 0x004f9ec4
            charge(ctx, 9);
            mult(a0, t0, a3);
            v0 = lui(0xFFFF);
            v0 = v0 | 0xFFF8;
            a2 = sll(a0, 2);
            v1 = sra(a2, 4);
            s3 = a2 & 0xF;
            s2 = v1 & v0;
            s1 = v1 & 0x7;
            if (s3 == 0) {
            L_004f9fdc:
                charge(ctx, 3);
                a1 = a3;
                s6 = 0;
            } else {
                // 0x004f9ee8
                charge(ctx, 5);
                v0 = addiu(a3, 3);
                a1 = v0 & 0x1FFC;
                mult(v1, t0, a1);
                v0 = sra(v1, 2);
            L_004f9ff8:
                charge(ctx, 3);
                v0 = subu(v0, s2);
                v0 = subu(v0, s1);
                s6 = addiu(v0, -1);
            }
            break;
        case 0x4F9EFCu:  // table[1, 49]
            // 0x004f9efc
            charge(ctx, 10);
            mult(a1, t0, a3);
            v1 = lui(0xFFFF);
            v1 = v1 | 0xFFF8;
            v0 = sll(a1, 1);
            a2 = addu(v0, a1);
            a0 = sra(a2, 4);
            s3 = a2 & 0xF;
            s2 = a0 & v1;
            s1 = a0 & 0x7;
            if (s3 == 0) {
                goto L_004f9fdc;
            }
            // 0x004f9f24
            charge(ctx, 10);
            v0 = addiu(a3, 15);
            a1 = v0 & 0x1FF0;
            mult(v1, t0, a1);
            v0 = sll(v1, 1);
            v0 = addu(v0, v1);
            v0 = sra(v0, 4);
            v1 = subu(v0, s2);
            v1 = subu(v1, s1);
            s6 = addiu(v1, -1);
            break;
        case 0x4F9F4Cu:  // table[2, 10, 50, 58]
            // 0x004f9f4c
            charge(ctx, 9);
            mult(v1, t0, a3);
            a1 = lui(0xFFFF);
            a1 = a1 | 0xFFF8;
            a2 = sll(v1, 1);
            v0 = sra(a2, 4);
            s3 = a2 & 0xF;
            s2 = v0 & a1;
            s1 = v0 & 0x7;
            if (s3 == 0) {
                goto L_004f9fdc;
            }
            // 0x004f9f70
            charge(ctx, 5);
            v0 = addiu(a3, 7);
            a1 = v0 & a1;
            mult(v1, t0, a1);
            v0 = sra(v1, 3);
            goto L_004f9ff8;
        case 0x4F9F84u:  // table[19, 27]
            // 0x004f9f84
            charge(ctx, 8);
            mult(a2, t0, a3);
            v1 = lui(0xFFFF);
            v1 = v1 | 0xFFF8;
            v0 = sra(a2, 4);
            s3 = a2 & 0xF;
            s2 = v0 & v1;
            s1 = v0 & 0x7;
            if (s3 == 0) {
                goto L_004f9fdc;
            }
            // 0x004f9fa4
            charge(ctx, 5);
            v0 = addiu(a3, 7);
            a1 = v0 & v1;
            mult(v1, t0, a1);
            v0 = sra(v1, 4);
            goto L_004f9ff8;
        case 0x4F9FB8u:  // table[20, 36, 44]
            // 0x004f9fb8
            charge(ctx, 9);
            mult(v0, t0, a3);
            a1 = lui(0xFFFF);
            a1 = a1 | 0xFFF8;
            v1 = sra(v0, 5);
            a2 = sra(v0, 1);
            s3 = a2 & 0xF;
            s2 = v1 & a1;
            s1 = v1 & 0x7;
            if (s3 == 0) {
                goto L_004f9fdc;
            }
            // 0x004f9fe8
            charge(ctx, 4);
            v0 = addiu(a3, 7);
            a1 = v0 & a1;
            mult(v1, t0, a1);
            v0 = sra(v1, 5);
            goto L_004f9ff8;
        case 0x4FA004u:  // table[3, 4, 5, 6, 7, 8, 9, 11, 12, 13, 14, 15, 16, 17, 18, 21, 22, 23, 24, 25, 26, 28, 29, 30, 31, 32, 33, 34, 35, 37, 38, 39, 40, 41, 42, 43, 45, 46, 47, 51, 52, 53, 54, 55, 56, 57]
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, a0.u());
            return;
        }
    }
    // 0x004fa004
    charge(ctx, 2);
    v1 = t1 & 0xFFF;
    if (s3 != 0) {
        // 0x004fa00c
        charge(ctx, 8);
        a1 = dsll32(a1, 0);
        v1 = dsll32(v1, 0);
        v1 = dsra32(v1, 0);
        v0 = addiu(s4, 64);
        a0 = 0x20000000;
        v1 = v1 | a1;
        v0 = v0 | a0;
        sd(v1, v0, 0);
    }
    // 0x004fa02c
    charge(ctx, 6);
    v0 = 0x10000000;
    v0 = v0 | 0x9000;
    lw(v1, v0, 0);  // 0x10009000 D1 VIF1 CHCR
    v1 = v1 & 0x100;
    cc = v1 == 0;  // the condition, before the delay slot changes it
    v1 = 0x10000000;
    if (!cc) {
        // 0x004fa044
        charge(ctx, 3);
        a0 = 0x1000000;
        v1 = v1 | 0x9000;
        v0 = s0;
        for (;;) {
            // 0x004fa050
            charge(ctx, 3);
            v0 = sltu(a0, v0);
            s0 = addiu(s0, 1);
            if (v0 != 0) {
                goto L_004fa1d0;
            }
            // 0x004fa05c
            charge(ctx, 4);
            lw(v0, v1, 0);
            v0 = v0 & 0x100;
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = s0;
            if (!cc) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004fa06c
    charge(ctx, 17);
    jal(ctx, 0x4FA06Cu, gen::fn__sceGsGetIMR_00503480);
    a0 = v0 | 0x200;
    jal(ctx, 0x4FA074u, gen::fn__sceGsPutIMR_005034a0);
    t3 = v0;
    a0 = 2;
    v0 = 0x12000000;
    v1 = 0x10000000;
    v0 = v0 | 0x1000;
    v1 = v1 | 0x9020;
    sd(a0, v0, 0);  // 0x12001000 GS CSR
    a1 = 0x70000000;
    a0 = 7;
    v0 = s4 & a1;
    sw(a0, v1, 0);  // 0x10009020 D1 VIF1 QWC
    cc = v0 != a1;  // the condition, before the delay slot changes it
    v0 = 0xFFF0000;
    if (cc) {
        // 0x004fa0cc
        charge(ctx, 4);
        v1 = 0x10000000;
        v0 = v0 | 0xFFFF;
        v1 = v1 | 0x9010;
        v0 = s4 & v0;
    } else {
        // 0x004fa0b0
        charge(ctx, 7);
        v1 = 0x10000000;
        v0 = v0 | 0xFFFF;
        a0 = lui(0x8000);
        v0 = s4 & v0;
        v1 = v1 | 0x9010;
        v0 = v0 | a0;
    }
    // 0x004fa0dc
    charge(ctx, 9);
    sw(v0, v1, 0);
    v0 = 0x10000000;
    a0 = 257;
    v0 = v0 | 0x9000;
    sw(a0, v0, 0);  // 0x10009000 D1 VIF1 CHCR
    lw(v1, v0, 0);  // 0x10009000 D1 VIF1 CHCR
    v1 = v1 & 0x100;
    cc = v1 == 0;  // the condition, before the delay slot changes it
    v1 = 0x10000000;
    if (!cc) {
        // 0x004fa100
        charge(ctx, 4);
        a0 = 0x1000000;
        v1 = v1 | 0x9000;
        v0 = s0;
        for (;;) {
            // 0x004fa110
            charge(ctx, 3);
            v0 = sltu(a0, v0);
            s0 = addiu(s0, 1);
            if (v0 != 0) {
                goto L_004fa1d0;
            }
            // 0x004fa11c
            charge(ctx, 4);
            lw(v0, v1, 0);
            v0 = v0 & 0x100;
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = s0;
            if (!cc) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004fa12c
    charge(ctx, 6);
    v0 = 0x12000000;
    v0 = v0 | 0x1000;
    ld(v1, v0, 0);  // 0x12001000 GS CSR
    v1 = v1 & 0x2;
    v0 = 0x10000000;
    if (v1 == 0) {
        // 0x004fa144
        charge(ctx, 5);
        v1 = 0x12000000;
        a0 = 0x1000000;
        v1 = v1 | 0x1000;
        v0 = s0;
        for (;;) {
            // 0x004fa158
            charge(ctx, 3);
            v0 = sltu(a0, v0);
            s0 = addiu(s0, 1);
            if (v0 != 0) {
                goto L_004fa1e4;
            }
            // 0x004fa164
            charge(ctx, 4);
            ld(v0, v1, 0);
            v0 = v0 & 0x2;
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = s0;
            if (!cc) {
                break;
            }
            backedge(ctx);
        }
        // 0x004fa174
        charge(ctx, 1);
        v0 = 0x10000000;
    }
    // 0x004fa178
    charge(ctx, 9);
    a0 = 0x800000;
    v0 = v0 | 0x3C00;
    v1 = 0x12000000;
    sw(a0, v0, 0);
    v1 = v1 | 0x1040;
    v0 = 1;
    sd(v0, v1, 0);  // 0x12001040 GS BUSDIR
    v0 = 0x10000000;
    if (s2 != 0) {
        // 0x004fa19c
        charge(ctx, 6);
        a0 = 0x70000000;
        v0 = v0 | 0x9020;
        v1 = s5 & a0;
        sw(s2, v0, 0);
        v0 = 0xFFF0000;
        if (v1 != a0) {
            // 0x004fa274
            charge(ctx, 4);
            v1 = 0x10000000;
            v0 = v0 | 0xFFFF;
            v1 = v1 | 0x9010;
            v0 = s5 & v0;
        } else {
            // 0x004fa1b4
            charge(ctx, 7);
            v1 = 0x10000000;
            v0 = v0 | 0xFFFF;
            a0 = lui(0x8000);
            v0 = s5 & v0;
            v1 = v1 | 0x9010;
            v0 = v0 | a0;
        }
        // 0x004fa284
        charge(ctx, 9);
        sw(v0, v1, 0);
        v0 = 0x10000000;
        a0 = 256;
        v0 = v0 | 0x9000;
        sw(a0, v0, 0);  // 0x10009000 D1 VIF1 CHCR
        lw(v1, v0, 0);  // 0x10009000 D1 VIF1 CHCR
        v1 = v1 & 0x100;
        v0 = s0;
        if (v1 == 0) {
            goto L_004fa2d4;
        }
        // 0x004fa2a8
        charge(ctx, 4);
        v1 = 0x10000000;
        a0 = 0x1000000;
        v1 = v1 | 0x9000;
        for (;;) {
            // 0x004fa2b8
            charge(ctx, 3);
            v0 = sltu(a0, v0);
            s0 = addiu(s0, 1);
            if (v0 != 0) {
                backedge(ctx);
                goto L_004fa214;
            }
            // 0x004fa2c4
            charge(ctx, 4);
            lw(v0, v1, 0);
            v0 = v0 & 0x100;
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = s0;
            if (!cc) {
                break;
            }
            backedge(ctx);
        }
        goto L_004fa2d4;
    }
L_004fa2d4:
    charge(ctx, 2);
    a1 = 0;
    if (s1 != 0) {
        // 0x004fa2dc
        charge(ctx, 7);
        t1 = 0x10000000;
        t0 = 0x10000000;
        v0 = sll(s2, 4);
        t1 = t1 | 0x3C00;
        a2 = addu(v0, s5);
        t2 = 0x1F000000;
        t0 = t0 | 0x5000;
        for (;;) {
            // 0x004fa2f8
            charge(ctx, 4);
            lw(v0, t1, 0);
            v0 = v0 & t2;
            v1 = 0x10000000;
            if (v0 == 0) {
                // 0x004fa308
                charge(ctx, 4);
                a3 = 0x1000000;
                v1 = v1 | 0x3C00;
                a0 = 0x1F000000;
                v0 = s0;
                for (;;) {
                    // 0x004fa318
                    charge(ctx, 3);
                    v0 = sltu(a3, v0);
                    s0 = addiu(s0, 1);
                    if (v0 != 0) {
                        backedge(ctx);
                        goto L_004fa220;
                    }
                    // 0x004fa324
                    charge(ctx, 4);
                    lw(v0, v1, 0);
                    v0 = v0 & a0;
                    cc = v0 == 0;  // the condition, before the delay slot changes it
                    v0 = s0;
                    if (!cc) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x004fa334
            charge(ctx, 6);
            lq(v0, t0, 0);
            a1 = addiu(a1, 1);
            v1 = slt(a1, s1);
            sq(v0, a2, 0);
            a2 = addiu(a2, 16);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004fa34c
    charge(ctx, 2);
    v0 = 0x10000000;
    if (s3 != 0) {
        // 0x004fa354
        charge(ctx, 6);
        a0 = 0x1F000000;
        v0 = v0 | 0x3C00;
        lw(v1, v0, 0);
        v1 = v1 & a0;
        cc = v1 != 0;  // the condition, before the delay slot changes it
        v1 = 0x10000000;
        if (!cc) {
            // 0x004fa36c
            charge(ctx, 3);
            a1 = 0x1000000;
            v1 = v1 | 0x3C00;
            v0 = s0;
            for (;;) {
                // 0x004fa378
                charge(ctx, 3);
                v0 = sltu(a1, v0);
                s0 = addiu(s0, 1);
                if (v0 != 0) {
                    backedge(ctx);
                    goto L_004fa220;
                }
                // 0x004fa384
                charge(ctx, 4);
                lw(v0, v1, 0);
                v0 = v0 & a0;
                cc = v0 == 0;  // the condition, before the delay slot changes it
                v0 = s0;
                if (!cc) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004fa394
            charge(ctx, 1);
            v1 = 0x10000000;
        }
        // 0x004fa398
        charge(ctx, 5);
        a1 = 0;
        v1 = v1 | 0x5000;
        lq(v0, v1, 0);
        sq(v0, sp, 0x0);
        if (s3 != 0) {
            // 0x004fa3ac
            charge(ctx, 1);
            a2 = addu(s2, s1);
            for (;;) {
                // 0x004fa3b0
                charge(ctx, 9);
                v1 = sll(a2, 4);
                v0 = addu(sp, a1);
                v1 = addu(v1, s5);
                lbu(a0, v0, 0);
                v1 = addu(v1, a1);
                a1 = addiu(a1, 1);
                v0 = slt(a1, s3);
                sb(a0, v1, 0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x004fa3d4
        charge(ctx, 2);
        a1 = 0;
        if (i64(s6) <= 0) {
            goto L_004fa440;
        }
        // 0x004fa3dc
        charge(ctx, 5);
        t0 = 0x10000000;
        a3 = 0x10000000;
        t0 = t0 | 0x3C00;
        t1 = 0x1F000000;
        a3 = a3 | 0x5000;
        for (;;) {
            // 0x004fa3f0
            charge(ctx, 4);
            lw(v0, t0, 0);
            v0 = v0 & t1;
            v1 = 0x10000000;
            if (v0 == 0) {
                // 0x004fa400
                charge(ctx, 4);
                a2 = 0x1000000;
                v1 = v1 | 0x3C00;
                a0 = 0x1F000000;
                v0 = s0;
                for (;;) {
                    // 0x004fa410
                    charge(ctx, 3);
                    v0 = sltu(a2, v0);
                    s0 = addiu(s0, 1);
                    if (v0 != 0) {
                        backedge(ctx);
                        goto L_004fa220;
                    }
                    // 0x004fa41c
                    charge(ctx, 4);
                    lw(v0, v1, 0);
                    v0 = v0 & a0;
                    cc = v0 == 0;  // the condition, before the delay slot changes it
                    v0 = s0;
                    if (!cc) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x004fa42c
            charge(ctx, 5);
            lq(v0, a3, 0);
            a1 = addiu(a1, 1);
            v1 = slt(a1, s6);
            sq(v0, sp, 0x0);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
        goto L_004fa440;
    }
L_004fa440:
    charge(ctx, 19);
    v0 = 0x10000000;
    v1 = 0x12000000;
    v0 = v0 | 0x3C00;
    v1 = v1 | 0x1040;
    sw(zero, v0, 0);  // 0x10003C00 VIF1_STAT
    a0 = t3;
    link(ctx, 0x4FA458u);  // $ra first: the delay slot below depends on it
    sd(zero, v1, 0);
    call(ctx, gen::fn__sceGsPutIMR_005034a0);
    v1 = 0x780000;
    v0 = 0x12000000;
    v1 = addiu(v1, -3408);  // &0x77F2B0
    v0 = v0 | 0x1000;
    lq(a1, v1, 0);  // 0x77F2B0
    a0 = 2;
    v1 = 0x10000000;
    sd(a0, v0, 0);  // 0x12001000 GS CSR
    v1 = v1 | 0x5000;
    v0 = 0;
    sq(a1, v1, 0);  // 0x10005000 VIF1 FIFO
L_004fa48c:
    charge(ctx, 1);
    ld(ra, sp, 0x80);
    // 0x004fa490 (the shared epilogue, written out on this path)
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
L_004fa1d0:
    charge(ctx, 5);
    a0 = 0x7C0000;
    a0 = addiu(a0, -11648);  // &0x7BD280
    jal(ctx, 0x4FA1D4u, gen::fn_scePrintf_00505e48);
    v0 = si(-1);
    goto L_004fa48c;
L_004fa1e4:
    charge(ctx, 12);
    a0 = 0x7C0000;
    a0 = addiu(a0, -11592);  // &0x7BD2B8
    jal(ctx, 0x4FA1E8u, gen::fn_scePrintf_00505e48);
    v0 = 0x780000;
    a0 = 0x10000000;
    v0 = addiu(v0, -3408);  // &0x77F2B0
    a0 = a0 | 0x5000;
    lq(v1, v0, 0);  // 0x77F2B0
    v0 = si(-1);
    sq(v1, a0, 0);  // 0x10005000 VIF1 FIFO
    ld(ra, sp, 0x80);
    // 0x004fa490 (the shared epilogue, written out on this path)
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
L_004fa214:
    charge(ctx, 3);
    a0 = 0x7C0000;
    a0 = addiu(a0, -11544);  // &0x7BD2E8
L_004fa228:
    charge(ctx, 19);
    jal(ctx, 0x4FA228u, gen::fn_scePrintf_00505e48);
    v0 = 0x12000000;
    a0 = 256;
    v0 = v0 | 0x1000;
    v1 = 0x12000000;
    sd(a0, v0, 0);  // 0x12001000 GS CSR
    v1 = v1 | 0x1040;
    sd(zero, v1, 0);  // 0x12001040 GS BUSDIR
    v0 = 0x10000000;
    a0 = 1;
    v0 = v0 | 0x3000;
    v1 = 0x10000000;
    sw(a0, v0, 0);  // 0x10003000 GIF_CTRL
    v1 = v1 | 0x3C10;
    v0 = si(-1);
    sw(a0, v1, 0);  // 0x10003C10 VIF1_FBRST
    ld(ra, sp, 0x80);
    // 0x004fa490 (the shared epilogue, written out on this path)
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
L_004fa220:
    charge(ctx, 2);
    a0 = 0x7C0000;
    a0 = addiu(a0, -11480);  // "sceGsExecStoreImage: Enough data does not reach VIF1\n"
    goto L_004fa228;
}

// 0x004FA4B8 sceGsSyncVCallback -- 160 bytes; frame 0x40: s1 sp+0x10, s2 sp+0x20, s0 sp+0x0, ra sp+0x30
// sceGsSyncVCallback: installs (or removes) the VBLANK interrupt callback; returns the old one.
void sceGsSyncVCallback(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004fa4b8
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s1, sp, 0x10);
    sd(s2, sp, 0x20);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x30);
    s1 = a0;
    jal(ctx, 0x4FA4CCu, gen::fn_sceGsGetGParam_004f9040);
    s0 = v0;
    lw(s2, s0, 8);
    if (s1 != 0) {
        // 0x004fa500
        charge(ctx, 2);
        if (s2 == 0) {
            sw(s1, s0, 8);
        } else {
            // 0x004fa508
            charge(ctx, 6);
            a0 = 2;
            jal(ctx, 0x4FA508u, gen::fn_DisableIntc_00503c40);
            lw(a1, s0, 12);
            a0 = 2;
            jal(ctx, 0x4FA514u, gen::fn__sceRemoveIntcHandler_00502e60);
            sw(s1, s0, 8);
        }
        // 0x004fa520
        charge(ctx, 7);
        a1 = s1;
        a0 = 2;
        a2 = si(-1);
        jal(ctx, 0x4FA528u, gen::fn__sceAddIntcHandler_00502e40);
        sw(v0, s0, 12);
        a0 = 2;
        jal(ctx, 0x4FA534u, gen::fn_EnableIntc_00503ca8);
    } else {
        // 0x004fa4e0
        charge(ctx, 8);
        a0 = 2;
        jal(ctx, 0x4FA4E0u, gen::fn_DisableIntc_00503c40);
        lw(a1, s0, 12);
        a0 = 2;
        jal(ctx, 0x4FA4ECu, gen::fn__sceRemoveIntcHandler_00502e60);
        sw(zero, s0, 8);
        sw(zero, s0, 12);
    }
    // 0x004fa53c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = s2;
    ld(ra, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x004FA738 sceGsSwapDBuffDc -- 92 bytes; frame 0x30: s1 sp+0x10, s0 sp+0x0, ra sp+0x20
// sceGsSwapDBuffDc: puts the display and draw environments of the given buffer half.
void sceGsSwapDBuffDc(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004fa738
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x10);
    s1 = a0;
    sd(s0, sp, 0x0);
    s0 = a1 & 0x1;
    a0 = 40;
    mult(v0, s0, a0);
    sd(ra, sp, 0x20);
    a0 = addu(v0, s1);
    jal(ctx, 0x4FA758u, gen::fn_sceGsPutDispEnv_004f94e0);
    if (s0 == 0) {
        // 0x004fa778
        charge(ctx, 3);
        a0 = addiu(s1, 80);
        jal(ctx, 0x4FA778u, gen::fn_sceGsPutDrawEnv_004f9850);
        ld(ra, sp, 0x20);
    } else {
        // 0x004fa768
        charge(ctx, 4);
        a0 = addiu(s1, 448);
        jal(ctx, 0x4FA768u, gen::fn_sceGsPutDrawEnv_004f9850);
        ld(ra, sp, 0x20);
    }
    // 0x004fa784 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x004FA798 WaitDma -- 112 bytes; frame 0x40: s1 sp+0x10, s0 sp+0x0, ra sp+0x30, s2 sp+0x20
// WaitDma: waits for a DMA channel to stop (with a timeout print and sceDmaPause).
void WaitDma(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004fa798
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s1, sp, 0x10);
    sd(s0, sp, 0x0);
    s1 = 0x1000000;
    sd(ra, sp, 0x30);
    s0 = a0;
    sd(s2, sp, 0x20);
    lw(v0, s0, 0);
    v0 = v0 & 0x100;
    s2 = 0x7C0000;
    if (v0 != 0) {
        // 0x004fa7c4
        charge(ctx, 1);
        s1 = addiu(s1, -1);
        for (;;) {
            // 0x004fa7c8
            charge(ctx, 2);
            if (i64(s1) < 0) {
                // 0x004fa7d0
                charge(ctx, 4);
                a0 = addiu(s2, -11184);
                jal(ctx, 0x4FA7D0u, gen::fn_scePrintf_00505e48);
                a0 = s0;
                jal(ctx, 0x4FA7D8u, gen::fn_sceDmaPause_004faf30);
            }
            // 0x004fa7e0
            charge(ctx, 4);
            lw(v0, s0, 0);
            v0 = v0 & 0x100;
            s1 = addiu(s1, -1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004fa7f0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x004FA808 WatchDma -- 132 bytes; frame 0x50: s2 sp+0x20, s1 sp+0x10, s0 sp+0x0, ra sp+0x40, s3 sp+0x30
// WatchDma: one check of a DMA channel's busy state (with a print and sceDmaPause).
void WatchDma(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004fa808
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s2, sp, 0x20);
    sd(s1, sp, 0x10);
    s2 = a1;
    sd(s0, sp, 0x0);
    s1 = a0;
    sd(ra, sp, 0x40);
    s0 = 0x1000000;
    sd(s3, sp, 0x30);
    if (a2 != 0) s0 = a2;
    lw(v0, s1, 16);
    v0 = sltu(v0, s2);
    s3 = 0x7C0000;
    if (v0 != 0) {
        // 0x004fa840
        charge(ctx, 2);
        s0 = addiu(s0, -1);
        for (;;) {
            // 0x004fa848
            charge(ctx, 2);
            if (i64(s0) < 0) {
                // 0x004fa850
                charge(ctx, 4);
                a0 = addiu(s3, -11184);
                jal(ctx, 0x4FA850u, gen::fn_scePrintf_00505e48);
                a0 = s1;
                jal(ctx, 0x4FA858u, gen::fn_sceDmaPause_004faf30);
            }
            // 0x004fa860
            charge(ctx, 4);
            lw(v0, s1, 16);
            v0 = sltu(v0, s2);
            s0 = addiu(s0, -1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004fa870 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x004FA918 sceDmaReset -- 220 bytes; frame 0x50: s1 sp+0x30, s0 sp+0x20, ra sp+0x40
// sceDmaReset: resets the DMAC (D_CTRL, D_STAT, D_PCR, the channels) and puts the default environment.
void sceDmaReset(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004fa918
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v0 = 0x10000000;
    sd(s1, sp, 0x30);
    v0 = v0 | 0xE000;
    sd(s0, sp, 0x20);
    a2 = 0x7C0000;
    sd(ra, sp, 0x40);
    v1 = 0x780000;
    s0 = a0;
    v1 = addiu(v1, -3376);  // &0x77F2D0
    lw(a1, v0, 0);  // 0x1000E000 D_CTRL
    a2 = addiu(a2, -11160);  // &0x7BD468
    a0 = 9;
    s1 = a1 & 0x1;
    for (;;) {
        // 0x004fa950
        charge(ctx, 3);
        lw(v0, a2, 0);
        if (v0 == 0) {
            v1 = addiu(v1, 4);
        } else {
            // 0x004fa95c
            charge(ctx, 8);
            lw(v0, v1, 0);
            sw(zero, v0, 128);
            sw(zero, v0, 0);
            sw(zero, v0, 48);
            sw(zero, v0, 16);
            sw(zero, v0, 80);
            sw(zero, v0, 64);
            v1 = addiu(v1, 4);
        }
        // 0x004fa97c
        charge(ctx, 3);
        a0 = addiu(a0, -1);
        a2 = addiu(a2, 4);
        if (i64(a0) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004fa988
    charge(ctx, 16);
    v1 = 0x10000000;
    v0 = 0xFF1F;
    v1 = v1 | 0xE010;
    a2 = lui(0xFF1F);
    sw(v0, v1, 0);  // 0x1000E010 D_STAT
    a0 = sp;
    a1 = 20;
    lw(v0, v1, 0);  // 0x1000E010 D_STAT
    v0 = v0 & a2;
    link(ctx, 0x4FA9ACu);  // $ra first: the delay slot below depends on it
    sw(v0, v1, 0);
    call(ctx, gen::fn_memclr_004fa8b8);
    a0 = sp;
    jal(ctx, 0x4FA9B4u, gen::fn_sceDmaPutEnv_004fa9f8);
    v1 = 1;
    v0 = s1;
    if (s0 == v1) {
        // 0x004fa9c8
        charge(ctx, 6);
        v1 = 0x10000000;
        v1 = v1 | 0xE000;
        lw(v0, v1, 0);  // 0x1000E000 D_CTRL
        v0 = v0 | 0x1;
        sw(v0, v1, 0);  // 0x1000E000 D_CTRL
        v0 = s1;
    }
    // 0x004fa9e0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x40);
    ld(s1, sp, 0x30);
    ld(s0, sp, 0x20);
    sp = addiu(sp, 0x50);
}

// 0x004FA9F8 sceDmaPutEnv -- 472 bytes; leaf frame (no stack)
// sceDmaPutEnv: writes the DMAC environment (D_CTRL, D_PCR, D_SQWC, D_RBSR / D_RBOR, D_STADR).
void sceDmaPutEnv(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x004fa9f8
    enter(ctx, 20);  // entry check point + this block's cycles
    v0 = 0x10000000;
    v1 = 0x10000000;
    v0 = v0 | 0xE000;
    v1 = v1 | 0xE020;
    lw(t2, v0, 0);  // 0x1000E000 D_CTRL
    a1 = 0x10000000;
    lw(a2, v1, 0);  // 0x1000E020 D_PCR
    t1 = a0;
    a1 = a1 | 0xE030;
    v1 = 0x10000000;
    lw(a1, a1, 0);  // 0x1000E030 D_SQWC
    v1 = v1 | 0xE050;
    v0 = 0x10000000;
    lbu(a0, t1, 0);
    lw(a2, v1, 0);  // 0x1000E050 D_RBOR
    v0 = v0 | 0xE040;
    lw(t0, v0, 0);  // 0x1000E040 D_RBSR
    a0 = sltiu(a0, 10);
    if (a0 == 0) {
        // 0x004faa48
        charge(ctx, 2);
        v0 = si(-1);
        return;
    }
    lbu(v0, t1, 1);
    // 0x004faa50
    charge(ctx, 3);
    v0 = sltiu(v0, 10);
    if (v0 == 0) {
        // 0x004faa5c
        charge(ctx, 2);
        v0 = si(-2);
        return;
    }
    lbu(v0, t1, 2);
    // 0x004faa64
    charge(ctx, 3);
    v0 = sltiu(v0, 10);
    if (v0 == 0) {
        // 0x004faa70
        charge(ctx, 2);
        v0 = si(-3);
        return;
    }
    lbu(t3, t1, 3);
    // 0x004faa78
    charge(ctx, 3);
    v0 = sltiu(t3, 7);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = 0x7C0000;
    if (!cc) {
        // 0x004faa84
        charge(ctx, 2);
        v0 = si(-4);
        return;
    }
    // 0x004faa8c
    charge(ctx, 30);
    lbu(v1, t1, 0);
    v0 = addiu(v0, -11120);
    a0 = 0x7C0000;
    lbu(a1, t1, 1);
    v1 = addu(v1, v0);
    a0 = addiu(a0, -11104);  // &0x7BD4A0
    lbu(t0, v1, 0);
    a1 = addu(a1, a0);
    v0 = lui(0xFFFF);
    v0 = v0 | 0xFFCF;
    a0 = 0x7C0000;
    lbu(a3, t1, 2);
    v0 = t2 & v0;
    a0 = addiu(a0, -11088);  // &0x7BD4B0
    t0 = sll(t0, 4);
    lbu(a2, a1, 0);
    v1 = lui(0xFFFF);
    t2 = v0 | t0;
    a3 = addu(a3, a0);
    v1 = v1 | 0xFF3F;
    a2 = sll(a2, 6);
    v1 = t2 & v1;
    lbu(a0, a3, 0);
    v0 = lui(0xFFFF);
    t2 = v1 | a2;
    v0 = v0 | 0xFFF3;
    a0 = sll(a0, 2);
    v0 = t2 & v0;
    t2 = v0 | a0;
    if (t3 == 0) {
        // 0x004fab28
        charge(ctx, 3);
        v0 = lui(0xFFFF);
        v0 = v0 | 0xFFFD;
        t2 = t2 & v0;
    } else {
        // 0x004fab04
        charge(ctx, 9);
        lbu(v1, t1, 3);
        v0 = lui(0xFFFF);
        t2 = t2 | 0x2;
        v0 = v0 | 0xFCFF;
        v1 = addiu(v1, -1);
        v0 = t2 & v0;
        v1 = sll(v1, 8);
        t2 = v0 | v1;
    }
    // 0x004fab34
    charge(ctx, 39);
    lhu(v0, t1, 4);
    a0 = 0x10000000;
    lhu(a2, t1, 6);
    a0 = a0 | 0xE000;
    lhu(a1, t1, 10);
    v0 = sll(v0, 16);
    lw(t0, t1, 16);
    a2 = v0 | a2;
    lhu(a3, t1, 8);
    v1 = 0x10000000;
    sw(t2, a0, 0);  // 0x1000E000 D_CTRL
    v1 = v1 | 0xE020;
    a1 = sll(a1, 16);
    v0 = 0x10000000;
    sw(a2, v1, 0);  // 0x1000E020 D_PCR
    a1 = a1 | a3;
    v0 = v0 | 0xE030;
    lw(a2, t1, 12);
    sw(a1, v0, 0);  // 0x1000E030 D_SQWC
    v1 = 0x10000000;
    v1 = v1 | 0xE050;
    v0 = 0x10000000;
    sw(a2, v1, 0);  // 0x1000E050 D_RBOR
    v0 = v0 | 0xE040;
    sw(t0, v0, 0);  // 0x1000E040 D_RBSR
    v1 = 0x960000;
    a2 = addiu(v1, 23240);  // &0x965AC8
    ldl(v0, t1, 7);
    ldr(v0, t1, 0);
    ldl(a0, t1, 15);
    ldr(a0, t1, 8);
    lw(a1, t1, 16);
    sdl(v0, a2, 7);  // 0x965ACF
    sdr(v0, a2, 0);  // 0x965AC8
    sdl(a0, a2, 15);  // 0x965AD7
    sdr(a0, a2, 8);  // 0x965AD0
    sw(a1, a2, 16);  // 0x965AD8
    v0 = 0;
}

// 0x004FAC20 sceDmaSend -- 104 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x10, ra sp+0x20
// sceDmaSend: starts a normal-mode transfer on a channel after WaitDma.
void sceDmaSend(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004fac20
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x10);
    sd(ra, sp, 0x20);
    a0 = a1;
    jal(ctx, 0x4FAC34u, gen::fn_CheckAddress_004fa890);
    s1 = v0;
    a0 = s0;
    jal(ctx, 0x4FAC40u, gen::fn_WaitDma_004fa798);
    v0 = lui(0xFFFF);
    lw(v1, s0, 48);
    v0 = v0 | 0xFFFF;
    if (v1 != v0) {
        sw(s1, s0, 48);
    }
    // 0x004fac5c
    charge(ctx, 11);
    lw(v0, s0, 0);
    v1 = si(-13);
    sw(zero, s0, 32);
    v0 = v0 & v1;
    ld(ra, sp, 0x20);
    v0 = v0 | 0x105;
    ld(s1, sp, 0x10);
    sw(v0, s0, 0);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x004FAC88 sceDmaSendN -- 116 bytes; frame 0x40: s0 sp+0x0, s2 sp+0x20, s1 sp+0x10, ra sp+0x30
// sceDmaSendN: starts a normal-mode transfer of n quadwords.
void sceDmaSendN(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004fac88
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s2, sp, 0x20);
    sd(s1, sp, 0x10);
    s2 = a2;
    sd(ra, sp, 0x30);
    a0 = a1;
    jal(ctx, 0x4FACA4u, gen::fn_CheckAddress_004fa890);
    s1 = v0;
    a0 = s0;
    jal(ctx, 0x4FACB0u, gen::fn_WaitDma_004fa798);
    v0 = lui(0xFFFF);
    lw(v1, s0, 16);
    v0 = v0 | 0xFFFF;
    if (v1 != v0) {
        sw(s1, s0, 16);
    }
    // 0x004faccc
    charge(ctx, 12);
    lw(v0, s0, 0);
    v1 = si(-13);
    sw(s2, s0, 32);
    v0 = v0 & v1;
    ld(ra, sp, 0x30);
    v0 = v0 | 0x101;
    ld(s2, sp, 0x20);
    sw(v0, s0, 0);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x004FADC0 sceDmaRecvN -- 124 bytes; frame 0x40: s0 sp+0x0, s2 sp+0x20, s1 sp+0x10, ra sp+0x30
// sceDmaRecvN: starts a receive transfer of n quadwords.
void sceDmaRecvN(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004fadc0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s2, sp, 0x20);
    sd(s1, sp, 0x10);
    s2 = a2;
    sd(ra, sp, 0x30);
    a0 = a1;
    jal(ctx, 0x4FADDCu, gen::fn_CheckAddress_004fa890);
    s1 = v0;
    a0 = s0;
    jal(ctx, 0x4FADE8u, gen::fn_WaitDma_004fa798);
    v0 = lui(0xFFFF);
    lw(v1, s0, 16);
    v0 = v0 | 0xFFFF;
    if (v1 != v0) {
        sw(s1, s0, 16);
    }
    // 0x004fae04
    charge(ctx, 14);
    lw(v0, s0, 0);
    v1 = si(-13);
    a0 = si(-2);
    sw(s2, s0, 32);
    v0 = v0 & v1;
    ld(ra, sp, 0x30);
    v0 = v0 & a0;
    ld(s2, sp, 0x20);
    v0 = v0 | 0x100;
    ld(s1, sp, 0x10);
    sw(v0, s0, 0);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x004FAEC0 sceDmaSync -- 56 bytes; frame 0x10: ra sp+0x0
// sceDmaSync: blocks until a channel is idle (WaitDma).
void sceDmaSync(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004faec0
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 1;
    sd(ra, sp, 0x0);
    if (a1 != v0) {
        // 0x004faee0
        charge(ctx, 3);
        jal(ctx, 0x4FAEE0u, gen::fn_WaitDma_004fa798);
        v0 = 0;
    } else {
        // 0x004faed0
        charge(ctx, 4);
        lw(v0, a0, 0);
        v0 = srl(v0, 8);
        v0 = v0 & 0x1;
    }
    // 0x004faeec (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x004FAF30 sceDmaPause -- 152 bytes; frame 0x30: s1 sp+0x10, ra sp+0x20, s0 sp+0x0
// sceDmaPause: suspends the DMAC (D_ENABLEW) with interrupts held off; returns the old state.
void sceDmaPause(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004faf30
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x10);
    sd(ra, sp, 0x20);
    s1 = a0;
    link(ctx, 0x4FAF40u);  // $ra first: the delay slot below depends on it
    sd(s0, sp, 0x0);
    call(ctx, gen::fn_DIntr_0050d3a0);
    a3 = v0;
    a0 = 0x10000;
    v0 = 0x10000000;
    v0 = v0 | 0xF520;
    lw(a2, v0, 0);  // 0x1000F520 D_ENABLER
    v1 = a2 & a0;
    v0 = 0x10000000;
    if (v1 == 0) {
        // 0x004faf68
        charge(ctx, 4);
        v1 = a2 | a0;
        v0 = v0 | 0xF590;
        sw(v1, v0, 0);
        v0 = 0x10000000;
    }
    // 0x004faf78
    charge(ctx, 12);
    a0 = lui(0xFFFF);
    v0 = v0 | 0xE000;
    a0 = a0 | 0xFEFF;
    lw(a1, v0, 0);
    v1 = 0x10000000;
    lw(s0, s1, 0);
    v1 = v1 | 0xF590;
    a0 = s0 & a0;
    sw(a0, s1, 0);
    sw(a2, v1, 0);  // 0x1000F590 D_ENABLEW
    v0 = s0;
    if (a3 != 0) {
        // 0x004fafa8
        charge(ctx, 3);
        jal(ctx, 0x4FAFA8u, gen::fn_EIntr_0050d3f0);
        v0 = s0;
    }
    // 0x004fafb4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x004FCB00 _motionVectors -- 412 bytes; frame 0xB0: fp sp+0x90, s7 sp+0x80, s6 sp+0x70, s5 sp+0x60, s4 sp+0x50, s3 sp+0x40, s2 sp+0x30, s0 sp+0x10, ra sp+0xA0, s1 sp+0x20
// libmpeg: decodes the motion vectors of a macroblock (_motionVector per component).
void _motionVectors(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x004fcb00
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    v0 = 1;
    sd(fp, sp, 0x90);
    sd(s7, sp, 0x80);
    sd(s6, sp, 0x70);
    s7 = a2;
    sd(s5, sp, 0x60);
    sd(s4, sp, 0x50);
    s5 = t3;
    sd(s3, sp, 0x40);
    s4 = a1;
    sd(s2, sp, 0x30);
    sd(s0, sp, 0x10);
    s2 = a0;
    sd(ra, sp, 0xA0);
    s0 = t0;
    sd(s1, sp, 0x20);
    sw(a3, sp, 0x0);
    lw(s6, sp, 0xB0);
    lw(s3, sp, 0xB8);
    lw(fp, sp, 0xC0);
    if (t1 != v0) {
        // 0x004fcb88
        charge(ctx, 42);
        a0 = s2;
        a1 = 1;
        jal(ctx, 0x4FCB8Cu, gen::fn__sceMpegNextBit_004fd658);
        s1 = sll(s0, 3);
        lw(v1, sp, 0x0);
        s0 = sll(s0, 2);
        a1 = addu(s4, s1);
        a0 = s2;
        s0 = addu(s0, v1);
        a2 = s7;
        sw(v0, s0, 0);
        a3 = s5;
        t0 = s6;
        t1 = s3;
        t2 = fp;
        t3 = 0;
        jal(ctx, 0x4FCBC4u, gen::fn__motionVector_004fc6d8);
        a0 = s2;
        a1 = 1;
        jal(ctx, 0x4FCBD0u, gen::fn__sceMpegNextBit_004fd658);
        s1 = addiu(s1, 16);
        sw(v0, s0, 8);
        a1 = addu(s4, s1);
        a0 = s2;
        a2 = s7;
        a3 = s5;
        t0 = s6;
        t1 = s3;
        t2 = fp;
        ld(ra, sp, 0xA0);
        ld(fp, sp, 0x90);
        t3 = 0;
        ld(s7, sp, 0x80);
        ld(s6, sp, 0x70);
        ld(s5, sp, 0x60);
        ld(s4, sp, 0x50);
        ld(s3, sp, 0x40);
        ld(s2, sp, 0x30);
        ld(s1, sp, 0x20);
        ld(s0, sp, 0x10);
        sp = addiu(sp, 0xB0);
        gen::fn__motionVector_004fc6d8(ctx);  // tail call
        return;
    }
    // 0x004fcb58
    charge(ctx, 2);
    if (t2 != 0) {
        s0 = sll(s0, 3);
    } else {
        // 0x004fcb60
        charge(ctx, 2);
        if (s3 != 0) {
            s0 = sll(s0, 3);
        } else {
            // 0x004fcb68
            charge(ctx, 8);
            a1 = 1;
            jal(ctx, 0x4FCB68u, gen::fn__sceMpegNextBit_004fd658);
            lw(a0, sp, 0x0);
            v1 = sll(s0, 2);
            v1 = addu(v1, a0);
            sw(v0, v1, 8);
            sw(v0, v1, 0);
            // 0x004fcc30
            charge(ctx, 1);
            s0 = sll(s0, 3);
        }
    }
    // 0x004fcc34
    charge(ctx, 26);
    a0 = s2;
    s0 = addu(s4, s0);
    a2 = s7;
    a3 = s5;
    t0 = s6;
    t1 = s3;
    t2 = fp;
    a1 = s0;
    t3 = 0;
    jal(ctx, 0x4FCC54u, gen::fn__motionVector_004fc6d8);
    lw(v0, s0, 0);
    lw(v1, s0, 4);
    sw(v0, s0, 16);
    sw(v1, s0, 20);
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

// 0x004FD8A0 sub_4FD8A0 -- 8 bytes; leaf frame (no stack)
// libmpeg: tail call into _sceMpegFlushBuf.
void sub_4FD8A0(EEContext& ctx) {
    using namespace hg;
    // 0x004fd8a0
    enter(ctx, 2);  // entry check point + this block's cycles
    gen::fn__sceMpegFlushBuf_004fd7d0(ctx);  // tail call
}

// 0x004FF7B8 _pictureTemporalScalableExtension -- 12 bytes; leaf frame (no stack)
// libmpeg: picture temporal scalable extension (unsupported: reports an error).
void _pictureTemporalScalableExtension(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5};
    // 0x004ff7b8
    enter(ctx, 3);  // entry check point + this block's cycles
    a1 = 0x7C0000;
    a1 = addiu(a1, -10320);  // "_pictureTemporalScalableExtension is not supported"
    gen::fn__sceMpegError_00502668(ctx);  // tail call
}

// 0x00502418 _ch4dma -- 212 bytes; leaf frame (no stack)
// libmpeg: starts the toIPU (D4) chain for the bitstream buffer.
void _ch4dma(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x00502418
    enter(ctx, 8);  // entry check point + this block's cycles
    v0 = 0x10000000;
    v1 = 16;
    v0 = v0 | 0xE010;
    a2 = a1;
    sw(v1, v0, 0);  // 0x1000E010 D_STAT
    lw(v0, a2, 0);
    a3 = 0xFFFF;
    if (v0 == 0) {
        // 0x00502438
        charge(ctx, 4);
        sync(ctx, 0);
        ei(ctx);
        v0 = 1;
        return;
    }
    // 0x00502448
    charge(ctx, 3);
    v0 = sltu(a3, v0);
    v1 = 0x10000000;
    if (v0 == 0) {
        // 0x005024ac
        charge(ctx, 12);
        lw(a0, a2, 4);
        v0 = 0x10000000;
        v0 = v0 | 0xB410;
        sw(a0, v0, 0);  // 0x1000B410 D4 toIPU MADR
        v1 = v1 | 0xB420;
        v0 = 0x10000000;
        a1 = 257;
        lw(a0, a2, 0);
        v0 = v0 | 0xB400;
        sw(a0, v1, 0);
        sw(a1, v0, 0);  // 0x1000B400 D4 toIPU CHCR
        sw(zero, a2, 0);
    } else {
        // 0x00502454
        charge(ctx, 22);
        lw(a0, a2, 4);
        v0 = 0x10000000;
        v0 = v0 | 0xB410;
        sw(a0, v0, 0);  // 0x1000B410 D4 toIPU MADR
        v1 = v1 | 0xB420;
        sw(a3, v1, 0);
        v0 = 0x10000000;
        v0 = v0 | 0xB400;
        v1 = 257;
        sw(v1, v0, 0);  // 0x1000B400 D4 toIPU CHCR
        a1 = 0xF0000;
        a1 = a1 | 0xFFF0;
        a0 = 0xFFF0000;
        lw(v1, a2, 4);
        a0 = a0 | 0xFFFF;
        lw(v0, a2, 0);
        v1 = addu(v1, a1);
        v1 = v1 & a0;
        v0 = subu(v0, a3);
        sw(v0, a2, 0);
        sw(v1, a2, 4);
    }
    // 0x005024dc (the shared epilogue, written out on this path)
    charge(ctx, 4);
    sync(ctx, 0);
    ei(ctx);
    v0 = 0;
}

// 0x00502500 _sceMpegStopIpuDma -- 160 bytes; frame 0x10: ra sp+0x0
// libmpeg: stops the IPU DMA channels (fromIPU D3, toIPU D4) with interrupts held off.
void _sceMpegStopIpuDma(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00502500
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x502508u, gen::fn_DIntr_0050d3a0);
    a3 = 0x10000000;
    a0 = 0x10000;
    a3 = a3 | 0xF520;
    t0 = 0x10000000;
    lw(v1, a3, 0);  // 0x1000F520 D_ENABLER
    t0 = t0 | 0xF590;
    a1 = 0x10000000;
    a2 = 0x10000000;
    v1 = v1 | a0;
    a1 = a1 | 0xB000;
    sw(v1, t0, 0);  // 0x1000F590 D_ENABLEW
    a2 = a2 | 0xB400;
    sw(zero, a1, 0);  // 0x1000B000 D3 fromIPU CHCR
    a0 = lui(0xFFFE);
    sw(zero, a2, 0);  // 0x1000B400 D4 toIPU CHCR
    a0 = a0 | 0xFFFF;
    lw(v1, a3, 0);  // 0x1000F520 D_ENABLER
    v1 = v1 & a0;
    sw(v1, t0, 0);  // 0x1000F590 D_ENABLEW
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = 0x10000000;
    if (!cc) {
        // 0x00502564
        charge(ctx, 3);
        jal(ctx, 0x502564u, gen::fn_EIntr_0050d3f0);
        v0 = 0x10000000;
    }
    // 0x00502570 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    a0 = 0x10000000;
    v0 = v0 | 0xB020;
    a0 = a0 | 0xB420;
    sw(zero, v0, 0);
    v1 = 0x10000000;
    sw(zero, a0, 0);  // 0x1000B420 D4 toIPU QWC
    v1 = v1 | 0x2010;
    v0 = 0x40000000;
    ld(ra, sp, 0x0);
    sw(v0, v1, 0);  // 0x10002010 IPU_CTRL
    sp = addiu(sp, 0x10);
}

// 0x005025A0 _sceMpegErrorBdec -- 200 bytes; frame 0x40: s0 sp+0x20, ra sp+0x30
// libmpeg: error path of the block decoder (stops the DMA, records the error).
void _sceMpegErrorBdec(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005025a0
    enter(ctx, 41);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    a1 = 0x7C0000;
    sd(s0, sp, 0x20);
    a1 = addiu(a1, -9680);  // "Error code detected(BDEC)"
    sd(ra, sp, 0x30);
    s0 = a0;
    jal(ctx, 0x5025B4u, gen::fn__sceMpegError_00502668);
    v0 = 2;
    lw(a0, s0, 2152);
    sw(v0, sp, 0x0);
    a1 = sp;
    jal(ctx, 0x5025C8u, gen::fn__sceMpegDispatchMpegCallback_00500d10);
    v1 = 0x10000000;
    a1 = 0x40000000;
    v1 = v1 | 0x2010;
    lw(a0, s0, 2152);
    sw(a1, v1, 0);  // 0x10002010 IPU_CTRL
    v0 = 3;
    sw(v0, sp, 0x0);
    a1 = sp;
    jal(ctx, 0x5025ECu, gen::fn__sceMpegDispatchMpegCallback_00500d10);
    jal(ctx, 0x5025F4u, gen::fn_DIntr_0050d3a0);
    a2 = 0x10000000;
    a3 = 0x10000000;
    a2 = a2 | 0xF520;
    t0 = 0x10000;
    lw(v1, a2, 0);  // 0x1000F520 D_ENABLER
    a3 = a3 | 0xF590;
    a0 = 0x10000000;
    a1 = lui(0xFFFE);
    v1 = v1 | t0;
    a0 = a0 | 0xB000;
    sw(v1, a3, 0);  // 0x1000F590 D_ENABLEW
    a1 = a1 | 0xFFFF;
    sw(zero, a0, 0);  // 0x1000B000 D3 fromIPU CHCR
    lw(v1, a2, 0);  // 0x1000F520 D_ENABLER
    v1 = v1 & a1;
    sw(v1, a3, 0);  // 0x1000F590 D_ENABLEW
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = 0x10000000;
    if (!cc) {
        // 0x00502644
        charge(ctx, 3);
        jal(ctx, 0x502644u, gen::fn_EIntr_0050d3f0);
        v0 = 0x10000000;
    }
    // 0x00502650 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    v0 = v0 | 0xB020;
    ld(s0, sp, 0x20);
    sw(zero, v0, 0);
    sp = addiu(sp, 0x40);
}

// 0x00502700 setD3_CHCR -- 116 bytes; frame 0x20: s0 sp+0x0, ra sp+0x10
// Writes the fromIPU (D3) CHCR with interrupts held off.
void setD3_CHCR(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00502700
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    s0 = a0;
    jal(ctx, 0x50270Cu, gen::fn_DIntr_0050d3a0);
    a2 = 0x10000000;
    a3 = 0x10000000;
    a2 = a2 | 0xF520;
    t0 = 0x10000;
    lw(v1, a2, 0);  // 0x1000F520 D_ENABLER
    a3 = a3 | 0xF590;
    a0 = 0x10000000;
    a1 = lui(0xFFFE);
    v1 = v1 | t0;
    a0 = a0 | 0xB000;
    sw(v1, a3, 0);  // 0x1000F590 D_ENABLEW
    a1 = a1 | 0xFFFF;
    sw(s0, a0, 0);  // 0x1000B000 D3 fromIPU CHCR
    lw(v1, a2, 0);  // 0x1000F520 D_ENABLER
    v1 = v1 & a1;
    sw(v1, a3, 0);  // 0x1000F590 D_ENABLEW
    ld(ra, sp, 0x10);
    if (v0 == 0) {
        // 0x00502768
        charge(ctx, 3);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0050275c
    charge(ctx, 3);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
    gen::fn_EIntr_0050d3f0(ctx);  // tail call
}

// 0x00502778 setD4_CHCR -- 116 bytes; frame 0x20: s0 sp+0x0, ra sp+0x10
// Writes the toIPU (D4) CHCR with interrupts held off.
void setD4_CHCR(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00502778
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    s0 = a0;
    jal(ctx, 0x502784u, gen::fn_DIntr_0050d3a0);
    a2 = 0x10000000;
    a3 = 0x10000000;
    a2 = a2 | 0xF520;
    t0 = 0x10000;
    lw(v1, a2, 0);  // 0x1000F520 D_ENABLER
    a3 = a3 | 0xF590;
    a0 = 0x10000000;
    a1 = lui(0xFFFE);
    v1 = v1 | t0;
    a0 = a0 | 0xB400;
    sw(v1, a3, 0);  // 0x1000F590 D_ENABLEW
    a1 = a1 | 0xFFFF;
    sw(s0, a0, 0);  // 0x1000B400 D4 toIPU CHCR
    lw(v1, a2, 0);  // 0x1000F520 D_ENABLER
    v1 = v1 & a1;
    sw(v1, a3, 0);  // 0x1000F590 D_ENABLEW
    ld(ra, sp, 0x10);
    if (v0 == 0) {
        // 0x005027e0
        charge(ctx, 3);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x005027d4
    charge(ctx, 3);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
    gen::fn_EIntr_0050d3f0(ctx);  // tail call
}

// 0x005027F0 sceIpuStopDMA -- 228 bytes; frame 0x20: s0 sp+0x0, ra sp+0x10
// sceIpuStopDMA: stops D3 / D4 and saves their state for sceIpuRestartDMA.
void sceIpuStopDMA(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005027f0
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x10);
    a0 = 1;
    jal(ctx, 0x502800u, gen::fn_setD4_CHCR_00502778);
    v0 = 0x10000000;
    a2 = 0x10000000;
    v0 = v0 | 0xB410;
    a2 = a2 | 0xB430;
    lw(v1, v0, 0);  // 0x1000B410 D4 toIPU MADR
    a0 = 0x10000000;
    a0 = a0 | 0xB420;
    a1 = 0x10000000;
    sw(v1, s0, 0);
    a1 = a1 | 0xB400;
    a3 = 0x10000000;
    lw(v1, a2, 0);  // 0x1000B430 D4 toIPU TADR
    a3 = a3 | 0x2010;
    sw(v1, s0, 4);
    lw(v0, a0, 0);  // 0x1000B420 D4 toIPU QWC
    sw(v0, s0, 8);
    lw(v1, a1, 0);  // 0x1000B400 D4 toIPU CHCR
    sw(v1, s0, 12);
    for (;;) {
        // 0x00502850
        charge(ctx, 7);
        lw(v0, a3, 0);
        v0 = v0 & 0xF0;
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0050286c
    charge(ctx, 26);
    a0 = 0;
    jal(ctx, 0x50286Cu, gen::fn_setD3_CHCR_00502700);
    v0 = 0x10000000;
    a3 = 0x10000000;
    v0 = v0 | 0xB010;
    a3 = a3 | 0xB020;
    lw(v1, v0, 0);  // 0x1000B010 D3 fromIPU MADR
    a1 = 0x10000000;
    a1 = a1 | 0xB000;
    a2 = 0x10000000;
    sw(v1, s0, 16);
    a2 = a2 | 0x2020;
    a0 = 0x10000000;
    ld(ra, sp, 0x10);
    lw(v1, a3, 0);  // 0x1000B020 D3 fromIPU QWC
    a0 = a0 | 0x2010;
    sw(v1, s0, 20);
    lw(v0, a1, 0);  // 0x1000B000 D3 fromIPU CHCR
    sw(v0, s0, 24);
    lw(v1, a2, 0);  // 0x10002020 IPU_BP
    sw(v1, s0, 28);
    lw(v0, a0, 0);  // 0x10002010 IPU_CTRL
    sw(v0, s0, 32);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x005028D8 sceIpuRestartDMA -- 336 bytes; frame 0x50: s3 sp+0x30, s2 sp+0x20, s1 sp+0x10, s0 sp+0x0, ra sp+0x40
// sceIpuRestartDMA: restarts D3 / D4 from the saved state.
void sceIpuRestartDMA(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005028d8
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s3, sp, 0x30);
    sd(s2, sp, 0x20);
    sd(s1, sp, 0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x40);
    s0 = a0;
    lw(v0, s0, 28);
    lw(a0, s0, 8);
    v1 = srl(v0, 8);
    s3 = v0 & 0x7F;
    v0 = srl(v0, 16);
    v1 = v1 & 0xF;
    v0 = v0 & 0x3;
    lw(a1, s0, 0);
    v0 = addu(v0, v1);
    lw(a2, s0, 16);
    s2 = addu(a0, v0);
    v0 = sll(v0, 4);
    s1 = subu(a1, v0);
    if (a2 != 0) {
        // 0x0050292c
        charge(ctx, 3);
        lw(v0, s0, 20);
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = 0x10000000;
        if (!cc) {
            // 0x00502938
            charge(ctx, 9);
            a0 = 0x10000000;
            v0 = v0 | 0xB010;
            a0 = a0 | 0xB020;
            sw(a2, v0, 0);
            lw(v1, s0, 20);
            sw(v1, a0, 0);  // 0x1000B020 D3 fromIPU QWC
            lw(a0, s0, 24);
            a0 = a0 | 0x100;
            jal(ctx, 0x502954u, gen::fn_setD3_CHCR_00502700);
        }
    }
    // 0x0050295c
    charge(ctx, 3);
    v1 = 0x10000000;
    v1 = v1 | 0x2010;
    for (;;) {
        // 0x00502968
        charge(ctx, 7);
        lw(v0, v1, 0);
        if (i64(v0) >= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00502984
    charge(ctx, 5);
    v0 = 0x10000000;
    v1 = 0x10000000;
    v0 = v0 | 0x2000;
    v1 = v1 | 0x2010;
    sw(s3, v0, 0);  // 0x10002000 IPU_CMD
    for (;;) {
        // 0x00502998
        charge(ctx, 7);
        lw(v0, v1, 0);
        if (i64(v0) >= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x005029b4
    charge(ctx, 2);
    ld(ra, sp, 0x40);
    if (s1 == 0) {
        // 0x00502a10
        charge(ctx, 1);
        ld(s3, sp, 0x30);
        // 0x00502a14 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s2, sp, 0x20);
        ld(s1, sp, 0x10);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        return;
    }
    // 0x005029bc
    charge(ctx, 2);
    ld(s3, sp, 0x30);
    if (s2 == 0) {
        // 0x00502a14 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s2, sp, 0x20);
        ld(s1, sp, 0x10);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        return;
    }
    // 0x005029c4
    charge(ctx, 19);
    v0 = 0x10000000;
    a0 = 0x10000000;
    v0 = v0 | 0xB410;
    a0 = a0 | 0xB430;
    sw(s1, v0, 0);  // 0x1000B410 D4 toIPU MADR
    v1 = 0x10000000;
    v1 = v1 | 0xB420;
    ld(ra, sp, 0x40);
    lw(v0, s0, 4);
    ld(s3, sp, 0x30);
    sw(v0, a0, 0);  // 0x1000B430 D4 toIPU TADR
    sw(s2, v1, 0);  // 0x1000B420 D4 toIPU QWC
    ld(s2, sp, 0x20);
    lw(a0, s0, 12);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    a0 = a0 | 0x100;
    sp = addiu(sp, 0x50);
    gen::fn_setD4_CHCR_00502778(ctx);  // tail call
}

// 0x00502DB0 _sce_ExecPS2 -- 16 bytes; leaf frame (no stack)
// Kernel stub: ExecPS2 (syscall).
void _sce_ExecPS2(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00502db0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 7;
    syscall(ctx, 0x502DB4u);
}

// 0x00502EB0 _sce_DisableIntc -- 16 bytes; leaf frame (no stack)
// Kernel stub: DisableIntc (syscall).
void _sce_DisableIntc(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00502eb0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 21;
    syscall(ctx, 0x502EB4u);
}

// 0x00502F00 _sce_iEnableIntc -- 16 bytes; leaf frame (no stack)
// Kernel stub: iEnableIntc (syscall).
void _sce_iEnableIntc(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00502f00
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = si(-26);
    syscall(ctx, 0x502F04u);
}

// 0x00502F10 _sce_iDisableIntc -- 16 bytes; leaf frame (no stack)
// Kernel stub: iDisableIntc (syscall).
void _sce_iDisableIntc(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00502f10
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = si(-27);
    syscall(ctx, 0x502F14u);
}

// 0x00502F20 _sce_iEnableDmac -- 16 bytes; leaf frame (no stack)
// Kernel stub: iEnableDmac (syscall).
void _sce_iEnableDmac(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00502f20
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = si(-28);
    syscall(ctx, 0x502F24u);
}

// 0x00502F30 _sce_iDisableDmac -- 16 bytes; leaf frame (no stack)
// Kernel stub: iDisableDmac (syscall).
void _sce_iDisableDmac(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00502f30
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = si(-29);
    syscall(ctx, 0x502F34u);
}

// 0x00502F70 _sceDeleteThread -- 16 bytes; leaf frame (no stack)
// Kernel stub: DeleteThread (syscall).
void _sceDeleteThread(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00502f70
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 33;
    syscall(ctx, 0x502F74u);
}

// 0x00502FB0 _sceTerminateThread -- 16 bytes; leaf frame (no stack)
// Kernel stub: TerminateThread (syscall).
void _sceTerminateThread(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00502fb0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 37;
    syscall(ctx, 0x502FB4u);
}

// 0x00503000 _sceiChangeThreadPriority -- 16 bytes; leaf frame (no stack)
// Kernel stub: iChangeThreadPriority (syscall).
void _sceiChangeThreadPriority(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503000
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = si(-42);
    syscall(ctx, 0x503004u);
}

// 0x00503010 _sceRotateThreadReadyQueue -- 16 bytes; leaf frame (no stack)
// Kernel stub: RotateThreadReadyQueue (syscall).
void _sceRotateThreadReadyQueue(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503010
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 43;
    syscall(ctx, 0x503014u);
}

// 0x005030E0 _sce_iSuspendThread -- 16 bytes; leaf frame (no stack)
// Kernel stub: iSuspendThread (syscall).
void _sce_iSuspendThread(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x005030e0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = si(-56);
    syscall(ctx, 0x5030E4u);
}

// 0x00503480 _sceGsGetIMR -- 16 bytes; leaf frame (no stack)
// Kernel stub: GsGetIMR (syscall).
void _sceGsGetIMR(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503480
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 112;
    syscall(ctx, 0x503484u);
}

// 0x005034D0 _sceSetVSyncFlag -- 16 bytes; leaf frame (no stack)
// Kernel stub: SetVSyncFlag (syscall).
void _sceSetVSyncFlag(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x005034d0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 115;
    syscall(ctx, 0x5034D4u);
}

// 0x00503530 _isceSifSetDma -- 16 bytes; leaf frame (no stack)
// Kernel stub: isceSifSetDma (syscall).
void _isceSifSetDma(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503530
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = si(-119);
    syscall(ctx, 0x503534u);
}

// 0x005035C0 _sceGetMemorySize -- 16 bytes; leaf frame (no stack)
// Kernel stub: GetMemorySize (syscall).
void _sceGetMemorySize(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x005035c0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 127;
    syscall(ctx, 0x5035C4u);
}

// 0x005035D0 _sce_InitTLB -- 16 bytes; leaf frame (no stack)
// Kernel stub: InitTLB (syscall).
void _sce_InitTLB(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x005035d0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 130;
    syscall(ctx, 0x5035D4u);
}

// 0x00503680 VSync2 -- 164 bytes; frame 0x20: ra sp+0x10
// VSync2: waits for the next vertical blank through the kernel V-sync flag (_sceSetVSyncFlag).
void VSync2(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00503680
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    a0 = sp;
    sw(zero, sp, 0x0);
    a1 = sp | 0x8;
    jal(ctx, 0x503690u, gen::fn__sceSetVSyncFlag_005034d0);
    jal(ctx, 0x503698u, gen::fn_DIntr_0050d3a0);
    v1 = 0x10000000;
    a0 = 4;
    v1 = v1 | 0xF000;
    sw(a0, v1, 0);  // 0x1000F000 I_STAT
    sync(ctx, 0);
    v1 = 0x10000000;
    if (v0 != 0) {
        // 0x005036bc
        charge(ctx, 3);
        jal(ctx, 0x5036BCu, gen::fn_EIntr_0050d3f0);
        v1 = 0x10000000;
    }
    // 0x005036c8
    charge(ctx, 2);
    v1 = v1 | 0xF000;
    for (;;) {
        // 0x005036d0
        charge(ctx, 4);
        lw(v0, v1, 0);
        v0 = v0 & 0x4;
        if (v0 == 0) {
            // 0x005036e0
            charge(ctx, 3);
            lw(v0, sp, 0x0);
            if (v0 == 0) {
                backedge(ctx);
                continue;
            }
        }
        break;
    }
    // 0x005036ec
    charge(ctx, 8);
    jal(ctx, 0x5036ECu, gen::fn_DIntr_0050d3a0);
    v1 = 4;
    at = 0x10010000;
    sw(v1, at, -4096);  // 0x1000F000 I_STAT
    sync(ctx, 0);
    if (v0 != 0) {
        // 0x0050370c
        charge(ctx, 2);
        jal(ctx, 0x50370Cu, gen::fn_EIntr_0050d3f0);
    }
    // 0x00503714 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(v0, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00503C40 DisableIntc -- 104 bytes; frame 0x30: s1 sp+0x10, ra sp+0x20, s0 sp+0x0
// DisableIntc wrapper: disables an INTC cause with interrupts held off; returns whether it was enabled.
void DisableIntc(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00503c40
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
        // 0x00503c68
        charge(ctx, 2);
        jal(ctx, 0x503C68u, gen::fn_DIntr_0050d3a0);
    }
    // 0x00503c70
    charge(ctx, 6);
    a0 = s1;
    jal(ctx, 0x503C70u, gen::fn__sce_DisableIntc_00502eb0);
    s1 = v0;
    sync(ctx, 0);
    v0 = s1;
    if (s0 != 0) {
        // 0x00503c88
        charge(ctx, 3);
        jal(ctx, 0x503C88u, gen::fn_EIntr_0050d3f0);
        v0 = s1;
    }
    // 0x00503c94 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x005041D8 DelayThread -- 200 bytes; frame 0x50: s1 sp+0x30, ra sp+0x40, s0 sp+0x20
// DelayThread: sleeps the calling thread for a number of microseconds (alarm + semaphore).
void DelayThread(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005041d8
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s1, sp, 0x30);
    sd(ra, sp, 0x40);
    s1 = a0;
    sd(s0, sp, 0x20);
    mfc0(v0, 12);
    v1 = 0x10000;
    v0 = v0 & v1;
    if (v0 != 0) {
        v0 = 0x7C0000;
        // 0x0050420c
        charge(ctx, 10);
        v1 = 1;
        v0 = addiu(v0, -9568);
        sw(v1, sp, 0x4);
        sw(v0, sp, 0x14);
        a0 = sp;
        link(ctx, 0x504220u);  // $ra first: the delay slot below depends on it
        sw(zero, sp, 0x8);
        call(ctx, gen::fn__sceCreateSema_00503160);
        s0 = v0;
        a1 = s1;
        if (i64(s0) >= 0) {
            // 0x00504240
            charge(ctx, 10);
            a0 = 0;
            jal(ctx, 0x504240u, gen::fn_sub_50EEE0_0050eee0);
            a1 = 0x500000;
            a0 = v0;
            a1 = addiu(a1, 17432);  // &_DelayThreadHandler
            a2 = s0;
            jal(ctx, 0x504254u, gen::fn_SetTimerAlarm_0050f090);
            s1 = v0;
            if (i64(s1) >= 0) {
                // 0x00504278
                charge(ctx, 5);
                a0 = s0;
                jal(ctx, 0x504278u, gen::fn__sceWaitSema_005031a0);
                a0 = s0;
                jal(ctx, 0x504280u, gen::fn__sceDeleteSema_00503170);
                v0 = 0;
            } else {
                // 0x00504268
                charge(ctx, 4);
                a0 = s0;
                jal(ctx, 0x504268u, gen::fn__sceDeleteSema_00503170);
                v0 = s1;
            }
        } else {
            // 0x00504234
            charge(ctx, 3);
            v0 = lui(0x8000);
            v0 = v0 | 0x8003;
        }
    } else {
        // 0x00504200
        charge(ctx, 3);
        v0 = lui(0x8000);
        v0 = v0 | 0x8008;
    }
    // 0x0050428c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x40);
    ld(s1, sp, 0x30);
    ld(s0, sp, 0x20);
    sp = addiu(sp, 0x50);
}

// 0x00506B68 _sceRpcGetFPacket2 -- 64 bytes; frame 0x10: ra sp+0x0
// SIF RPC: returns packet n of the client's pool (64 bytes each), or a free packet from _sceRpcGetFPacket when n is
// out of range.
void _sceRpcGetFPacket2(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00506b68
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (i64(a1) >= 0) {
        // 0x00506b74
        charge(ctx, 4);
        lw(v0, a0, 32);
        v0 = slt(a1, v0);
        if (v0 == 0) {
            goto L_00506b84;
        }
        lw(v1, a0, 28);
        // 0x00506b94
        charge(ctx, 3);
        v0 = sll(a1, 6);
        v0 = addu(v1, v0);
        ld(ra, sp, 0x0);
        // 0x00506ba0 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        return;
    }
L_00506b84:
    charge(ctx, 4);
    jal(ctx, 0x506B84u, gen::fn__sceRpcGetFPacket_00506b38);
    ld(ra, sp, 0x0);
    // 0x00506ba0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x00507AD8 sceFsSifCallRpc -- 236 bytes; frame 0xC0: fp sp+0xA0, s7 sp+0x90, s6 sp+0x80, s5 sp+0x70, s4 sp+0x60, s3 sp+0x50, s2 sp+0x40, s1 sp+0x30, ra sp+0xB0, s0 sp+0x20
// File-system RPC call: sceSifCallRpc, retrying with DelayThread while the IOP is busy.
void sceFsSifCallRpc(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00507ad8
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(fp, sp, 0xA0);
    sd(s7, sp, 0x90);
    fp = a2;
    sd(s6, sp, 0x80);
    s7 = a3;
    sd(s5, sp, 0x70);
    s6 = t0;
    sd(s4, sp, 0x60);
    s5 = t1;
    sd(s3, sp, 0x50);
    s4 = t2;
    sd(s2, sp, 0x40);
    s3 = t3;
    sd(s1, sp, 0x30);
    s2 = 0;
    sd(ra, sp, 0xB0);
    s1 = 1;
    sd(s0, sp, 0x20);
    sw(a0, sp, 0x10);
    sw(a1, sp, 0x14);
    lw(v0, sp, 0xC0);
    for (;;) {
        // 0x00507b30
        charge(ctx, 13);
        a2 = fp;
        lw(a0, sp, 0x10);
        a3 = s7;
        lw(a1, sp, 0x14);
        t0 = s6;
        sw(v0, sp, 0x0);
        t1 = s5;
        t2 = s4;
        t3 = s3;
        jal(ctx, 0x507B50u, gen::fn_sceSifCallRpc_00507230);
        s0 = srl(v0, 31);
        lw(v0, sp, 0xC8);
        if (s0 != 0) {
            // 0x00507b64
            charge(ctx, 2);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = 1000;
            if (!cc) {
                // 0x00507b6c
                charge(ctx, 5);
                mult(a0, s1, v0);
                jal(ctx, 0x507B6Cu, gen::fn_DelayThread_005041d8);
                v1 = slti(s1, 127);
                if (v1 != 0) {
                    s1 = sll(s1, 1);
                }
                // 0x00507b80
                charge(ctx, 4);
                s2 = addiu(s2, 1);
                v0 = slti(s2, 101);
                cc = v0 != 0;  // the condition, before the delay slot changes it
                lw(v0, sp, 0xC0);
                if (cc) {
                    backedge(ctx);
                    continue;
                }
            }
        }
        break;
    }
    // 0x00507b90 (the shared epilogue, written out on this path)
    charge(ctx, 13);
    v0 = s0;
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

// 0x0050B788 sceSifFreeIopHeap -- 28 bytes; frame 0x10: ra sp+0x0
// sceSifFreeIopHeap: frees IOP memory (sceSifFreeSysMemory).
void sceSifFreeIopHeap(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0050b788
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x50B790u, gen::fn_sceSifFreeSysMemory_0050b710);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0050BCB0 _sceSifLoadModuleBuffer -- 520 bytes; frame 0x90: s6 sp+0x70, s3 sp+0x40, s1 sp+0x20, s0 sp+0x10, ra sp+0x80, s5 sp+0x60, s4 sp+0x50, s2 sp+0x30
// Loads an IOP module from an EE buffer through the loadfile RPC (binds the server first).
void _sceSifLoadModuleBuffer(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0050bcb0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(s6, sp, 0x70);
    sd(s3, sp, 0x40);
    s6 = a3;
    sd(s1, sp, 0x20);
    s3 = a0;
    sd(s0, sp, 0x10);
    s1 = a1;
    sd(ra, sp, 0x80);
    s0 = a2;
    sd(s5, sp, 0x60);
    sd(s4, sp, 0x50);
    link(ctx, 0x50BCE0u);  // $ra first: the delay slot below depends on it
    sd(s2, sp, 0x30);
    call(ctx, gen::fn__lf_bind_0050bae8);
    cc = i64(v0) < 0;  // the condition, before the delay slot changes it
    v0 = lui(0xFFFF);
    if (!cc) {
        // 0x0050bcf0
        charge(ctx, 4);
        jal(ctx, 0x50BCF0u, gen::fn__lf_version_0050bbe8);
        s4 = 0x970000;
        if (v0 == 0) {
            // 0x0050bd0c
            charge(ctx, 4);
            s5 = s4;
            s2 = addiu(s4, -24896);
            sw(s3, s4, -24896);
            if (s0 == 0) {
                // 0x0050be40
                charge(ctx, 1);
                sw(zero, s2, 4);
            L_0050be44:
                charge(ctx, 1);
                a1 = 0x970000;
            } else {
                // 0x0050bd1c
                charge(ctx, 3);
                v0 = slti(s1, 253);
                a1 = s0;
                if (v0 != 0) {
                    // 0x0050be2c
                    charge(ctx, 5);
                    a0 = addiu(s2, 260);
                    a2 = s1;
                    jal(ctx, 0x50BE30u, gen::fn_memcpy_00521250);
                    sw(s1, s2, 4);
                    goto L_0050be44;
                }
                // 0x0050bd28
                charge(ctx, 5);
                a0 = addiu(s2, 260);
                v0 = s0 | a0;
                v0 = v0 & 0x7;
                a3 = s0;
                if (v0 == 0) {
                    // 0x0050bda0
                    charge(ctx, 2);
                    v0 = addiu(s0, 224);
                    a1 = 0x970000;
                    for (;;) {
                        // 0x0050bda8
                        charge(ctx, 13);
                        ld(t2, a3, 0);
                        ld(v1, a3, 8);
                        ld(a2, a3, 16);
                        ld(t0, a3, 24);
                        sd(t2, a0, 0);
                        sd(v1, a0, 8);
                        sd(a2, a0, 16);
                        sd(t0, a0, 24);
                        a3 = addiu(a3, 32);
                        a0 = addiu(a0, 32);
                        if (a3 == v0) {
                            break;
                        }
                        backedge(ctx);
                    }
                } else {
                    // 0x0050bd3c
                    charge(ctx, 2);
                    v0 = addiu(s0, 224);
                    a1 = 0x970000;
                    for (;;) {
                        // 0x0050bd44
                        charge(ctx, 21);
                        ldl(v1, a3, 7);
                        ldr(v1, a3, 0);
                        ldl(a2, a3, 15);
                        ldr(a2, a3, 8);
                        ldl(t0, a3, 23);
                        ldr(t0, a3, 16);
                        ldl(t1, a3, 31);
                        ldr(t1, a3, 24);
                        sdl(v1, a0, 7);
                        sdr(v1, a0, 0);
                        sdl(a2, a0, 15);
                        sdr(a2, a0, 8);
                        sdl(t0, a0, 23);
                        sdr(t0, a0, 16);
                        sdl(t1, a0, 31);
                        sdr(t1, a0, 24);
                        a3 = addiu(a3, 32);
                        a0 = addiu(a0, 32);
                        if (a3 == v0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0050bd98
                    charge(ctx, 2);
                }
                // 0x0050bddc
                charge(ctx, 20);
                ldl(t1, a3, 7);
                ldr(t1, a3, 0);
                ldl(t2, a3, 15);
                ldr(t2, a3, 8);
                ldl(a2, a3, 23);
                ldr(a2, a3, 16);
                lwl(t0, a3, 27);
                lwr(t0, a3, 24);
                sdl(t1, a0, 7);
                sdr(t1, a0, 0);
                sdl(t2, a0, 15);
                sdr(t2, a0, 8);
                sdl(a2, a0, 23);
                sdr(a2, a0, 16);
                swl(t0, a0, 27);
                v1 = addiu(s5, -24896);
                v0 = 252;
                swr(t0, a0, 24);
                sw(v0, v1, 4);
            }
            // 0x0050be48
            charge(ctx, 13);
            s0 = addiu(s5, -24896);
            a0 = addiu(a1, -24384);
            sw(zero, sp, 0x0);
            a1 = 6;
            a2 = 0;
            a3 = s0;
            t0 = 512;
            t1 = s0;
            t2 = 8;
            t3 = 0;
            jal(ctx, 0x50BE6Cu, gen::fn_sceSifCallRpc_00507230);
            if (i64(v0) >= 0) {
                lw(v1, s0, 4);
                // 0x0050be88
                charge(ctx, 2);
                lw(v0, s4, -24896);
                sw(v1, s6, 0);
            } else {
                // 0x0050be7c
                charge(ctx, 3);
                v0 = lui(0xFFFE);
                v0 = v0 | 0xFFFF;
            }
        } else {
            // 0x0050bd00
            charge(ctx, 3);
            v0 = lui(0xFFFE);
            v0 = v0 | 0xFFFC;
        }
    }
    // 0x0050be90 (the shared epilogue, written out on this path)
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

// 0x0050C528 _sceSifLoadElfPart -- 260 bytes; frame 0x70: s4 sp+0x50, s3 sp+0x40, s2 sp+0x30, s0 sp+0x10, ra sp+0x60, s1 sp+0x20
// Loads an ELF section from the IOP through the loadfile RPC.
void _sceSifLoadElfPart(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0050c528
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(s4, sp, 0x50);
    sd(s3, sp, 0x40);
    s4 = a2;
    sd(s2, sp, 0x30);
    s3 = a3;
    sd(s0, sp, 0x10);
    s2 = a1;
    sd(ra, sp, 0x60);
    s0 = a0;
    link(ctx, 0x50C550u);  // $ra first: the delay slot below depends on it
    sd(s1, sp, 0x20);
    call(ctx, gen::fn__lf_bind_0050bae8);
    cc = i64(v0) < 0;  // the condition, before the delay slot changes it
    v0 = lui(0xFFFF);
    if (!cc) {
        // 0x0050c560
        charge(ctx, 4);
        jal(ctx, 0x50C560u, gen::fn__lf_version_0050bbe8);
        if (v0 == 0) {
            v0 = 0x970000;
            // 0x0050c57c
            charge(ctx, 25);
            a1 = s0;
            s1 = addiu(v0, -24888);
            a2 = 252;
            a0 = s1;
            s0 = addiu(s1, -8);
            jal(ctx, 0x50C58Cu, gen::fn_strncpy_00524828);
            a1 = s2;
            sb(zero, s0, 259);
            a0 = addiu(s1, 252);
            a2 = 252;
            jal(ctx, 0x50C5A0u, gen::fn_strncpy_00524828);
            a0 = 0x970000;
            sb(zero, s0, 511);
            a1 = s3;
            a0 = addiu(a0, -24384);  // &lf_rpc_cd
            sw(zero, sp, 0x0);
            a2 = 0;
            a3 = s0;
            t0 = 512;
            t1 = s0;
            t2 = 16;
            t3 = 0;
            jal(ctx, 0x50C5D0u, gen::fn_sceSifCallRpc_00507230);
            if (i64(v0) >= 0) {
                lw(v0, s1, -8);
                // 0x0050c5ec
                charge(ctx, 2);
                if (v0 != 0) {
                    sw(v0, s4, 0);
                    // 0x0050c600
                    charge(ctx, 3);
                    v0 = 0;
                    lw(v1, s0, 4);
                    sw(v1, s4, 4);
                } else {
                    // 0x0050c5f4
                    charge(ctx, 3);
                    v0 = lui(0xFFFE);
                    v0 = v0 | 0xFFFD;
                }
            } else {
                // 0x0050c5e0
                charge(ctx, 3);
                v0 = lui(0xFFFE);
                v0 = v0 | 0xFFFF;
            }
        } else {
            // 0x0050c570
            charge(ctx, 3);
            v0 = lui(0xFFFE);
            v0 = v0 | 0xFFFC;
        }
    }
    // 0x0050c60c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x60);
    ld(s4, sp, 0x50);
    ld(s3, sp, 0x40);
    ld(s2, sp, 0x30);
    ld(s1, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x70);
}

// 0x0050D280 _kDebugException -- 252 bytes; leaf frame (no stack)
// Kernel debug exception handler: prints the exception state.
void _kDebugException(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, t8{ctx, 24}, t9{ctx, 25}, k0{ctx, 26}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x0050d280
    enter(ctx, 63);  // entry check point + this block's cycles
    k0 = 0x970000;
    k0 = addiu(k0, -20096);  // &0x96B180
    sq(at, k0, 16);  // 0x96B190
    sq(v0, k0, 32);  // 0x96B1A0
    sq(v1, k0, 48);  // 0x96B1B0
    sq(a0, k0, 64);  // 0x96B1C0
    sq(a1, k0, 80);  // 0x96B1D0
    sq(a2, k0, 96);  // 0x96B1E0
    sq(a3, k0, 112);  // 0x96B1F0
    sq(t0, k0, 128);  // 0x96B200
    sq(t1, k0, 144);  // 0x96B210
    sq(t2, k0, 160);  // 0x96B220
    sq(t3, k0, 176);  // 0x96B230
    sq(t4, k0, 192);  // 0x96B240
    sq(t5, k0, 208);  // 0x96B250
    sq(t6, k0, 224);  // 0x96B260
    sq(t7, k0, 240);  // 0x96B270
    sq(s0, k0, 256);  // 0x96B280
    sq(s1, k0, 272);  // 0x96B290
    sq(s2, k0, 288);  // 0x96B2A0
    sq(s3, k0, 304);  // 0x96B2B0
    sq(s4, k0, 320);  // 0x96B2C0
    sq(s5, k0, 336);  // 0x96B2D0
    sq(s6, k0, 352);  // 0x96B2E0
    sq(s7, k0, 368);  // 0x96B2F0
    sq(t8, k0, 384);  // 0x96B300
    sq(t9, k0, 400);  // 0x96B310
    sq(gp, k0, 448);  // 0x96B340
    sq(sp, k0, 464);  // 0x96B350
    sq(fp, k0, 480);  // 0x96B360
    sq(ra, k0, 496);  // 0x96B370
    mfhi(v0);
    at = 0x970000;
    sd(v0, at, -19584);  // 0x96B380
    mfhi1(v0);
    at = 0x970000;
    sd(v0, at, -19576);  // 0x96B388
    mflo(v0);
    at = 0x970000;
    sd(v0, at, -19568);  // 0x96B390
    mflo1(v0);
    at = 0x970000;
    sd(v0, at, -19560);  // 0x96B398
    mfsa(v0);
    at = 0x970000;
    sd(v0, at, -19552);  // 0x96B3A0
    mfc0(a0, 12);
    mfc0(a1, 13);
    mfc0(a2, 14);
    mfc0(a3, 8);
    mfc0(t0, 23);
    t1 = 0x970000;
    t1 = addiu(t1, -20096);  // &0x96B180
    at = 0x510000;
    at = addiu(at, -11396);  // &sub_50D37C
    mtc0(at, 14);
    sync(ctx, 16);
    mfc0(at, 12);
    v0 = si(-2);
    at = at & v0;
    mtc0(at, 12);
    sync(ctx, 16);
    rt::eret(ctx, 0x50D378u);
}

// 0x00510E30 sceCdGetDiskType2 -- 152 bytes; frame 0x30: ra sp+0x20, s0 sp+0x10
// sceCdGetDiskType2: the disc type through the CD/DVD S-command RPC.
void sceCdGetDiskType2(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00510e30
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    a0 = 1;
    sd(ra, sp, 0x20);
    link(ctx, 0x510E3Cu);  // $ra first: the delay slot below depends on it
    sd(s0, sp, 0x10);
    call(ctx, gen::fn__sceCd_scmd_prechk_00510258);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = 0x780000;
    if (cc) {
        // 0x00510e54
        charge(ctx, 14);
        a0 = 0x780000;
        s0 = addiu(v0, 7552);
        a0 = addiu(a0, 9984);  // &0x782700
        sw(zero, sp, 0x0);
        a1 = 3;
        a2 = 0;
        a3 = 0;
        t0 = 0;
        t1 = s0;
        t2 = 4;
        t3 = 0;
        jal(ctx, 0x510E7Cu, gen::fn_sceSifCallRpc_00507230);
        v1 = 0x780000;
        if (i64(v0) >= 0) {
            // 0x00510ea0
            charge(ctx, 6);
            v0 = 0x20000000;
            v0 = s0 | v0;
            lw(a0, v1, 2988);
            link(ctx, 0x510EACu);  // $ra first: the delay slot below depends on it
            lw(s0, v0, 0);
            call(ctx, gen::fn__sceSignalSema_00503180);
            v0 = s0;
        } else {
            // 0x00510e8c
            charge(ctx, 5);
            v0 = 0x780000;
            link(ctx, 0x510E90u);  // $ra first: the delay slot below depends on it
            lw(a0, v0, 2988);
            call(ctx, gen::fn__sceSignalSema_00503180);
            v0 = si(-1);
        }
    } else {
        // 0x00510e4c
        charge(ctx, 2);
        v0 = si(-1);
    }
    // 0x00510eb8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x30);
}

// 0x0051C8A0 sceDbcDeleteSocket -- 188 bytes; frame 0x50: s1 sp+0x20, ra sp+0x40, s2 sp+0x30, s0 sp+0x10
// sceDbcDeleteSocket: closes a DBC socket through its RPC, under the DBC semaphore.
void sceDbcDeleteSocket(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051c8a0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v1 = 0x780000;
    sd(s1, sp, 0x20);
    lw(v0, v1, 11008);  // 0x782B00
    s1 = a0;
    sd(ra, sp, 0x40);
    sd(s2, sp, 0x30);
    sd(s0, sp, 0x10);
    if (v0 != 0) {
        // 0x0051c8cc
        charge(ctx, 20);
        s2 = 0x990000;
        link(ctx, 0x51C8D0u);  // $ra first: the delay slot below depends on it
        lw(a0, s2, 28672);  // 0x997000
        call(ctx, gen::fn__sceWaitSema_005031a0);
        v1 = 0x990000;
        a0 = 0x990000;
        s0 = addiu(v1, 26688);  // &0x996840
        a1 = lui(0x8000);
        sw(s1, v1, 26688);  // 0x996840
        a0 = addiu(a0, 26432);  // &0x996740
        sw(zero, sp, 0x0);
        a1 = a1 | 0x1302;
        a2 = 0;
        a3 = s0;
        t0 = 144;
        t1 = s0;
        t2 = 144;
        t3 = 0;
        jal(ctx, 0x51C90Cu, gen::fn_sceSifCallRpc_00507230);
        lw(a0, s2, 28672);  // 0x997000
        if (i64(v0) >= 0) {
            // 0x0051c938
            charge(ctx, 3);
            link(ctx, 0x51C938u);  // $ra first: the delay slot below depends on it
            lw(s0, s0, 4);
            call(ctx, gen::fn__sceSignalSema_00503180);
            v0 = s0;
        } else {
            // 0x0051c91c
            charge(ctx, 7);
            a0 = 0x7C0000;
            a0 = addiu(a0, -6272);  // "sceDbcDeleteSocket: rpc error\n"
            jal(ctx, 0x51C920u, gen::fn_DPRINT_0051d588);
            link(ctx, 0x51C928u);  // $ra first: the delay slot below depends on it
            lw(a0, s2, 28672);
            call(ctx, gen::fn__sceSignalSema_00503180);
            v0 = 0;
        }
    } else {
        // 0x0051c8c4
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x0051c944 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x40);
    ld(s2, sp, 0x30);
    ld(s1, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x50);
}

// 0x0053E0E0 adxt_ExecFsSvr -- 172 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// ADXT file-system server: runs ADXF_ExecServer under the ADXT lock.
void adxt_ExecFsSvr(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053e0e0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    jal(ctx, 0x53E0ECu, gen::fn_sub_539818_00539818);
    v0 = 0x780000;
    s0 = addiu(v0, 30008);  // &0x787538
    lw(v1, s0, 0);  // 0x787538
    ld(ra, sp, 0x8);
    if (v1 != 0) {
        // 0x0053e108
        charge(ctx, 3);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x10);
        gen::fn_sub_539830_00539830(ctx);  // tail call
        return;
    }
    // 0x0053e118
    charge(ctx, 29);
    v0 = 1;
    link(ctx, 0x53E11Cu);  // $ra first: the delay slot below depends on it
    sw(v0, s0, 0);
    call(ctx, gen::fn_sub_539830_00539830);
    v0 = 2;
    link(ctx, 0x53E128u);  // $ra first: the delay slot below depends on it
    sw(v0, s0, 0);
    call(ctx, gen::fn_SRD_ExecServer_00558500);
    v0 = 3;
    link(ctx, 0x53E134u);  // $ra first: the delay slot below depends on it
    sw(v0, s0, 0);
    call(ctx, gen::fn_sub_546E38_00546e38);
    v0 = 4;
    link(ctx, 0x53E140u);  // $ra first: the delay slot below depends on it
    sw(v0, s0, 0);
    call(ctx, gen::fn_sub_546D90_00546d90);
    v0 = 5;
    link(ctx, 0x53E14Cu);  // $ra first: the delay slot below depends on it
    sw(v0, s0, 0);
    call(ctx, gen::fn_ADXF_ExecServer_0053d708);
    v0 = 6;
    link(ctx, 0x53E158u);  // $ra first: the delay slot below depends on it
    sw(v0, s0, 0);
    call(ctx, gen::fn_sub_546D90_00546d90);
    v0 = 7;
    link(ctx, 0x53E164u);  // $ra first: the delay slot below depends on it
    sw(v0, s0, 0);
    call(ctx, gen::fn_sub_546E38_00546e38);
    v0 = 8;
    link(ctx, 0x53E170u);  // $ra first: the delay slot below depends on it
    sw(v0, s0, 0);
    call(ctx, gen::fn_SRD_ExecServer_00558500);
    sw(zero, s0, 0);
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0053FCF8 adxm_fs_proc -- 240 bytes; frame 0x40: s5 sp+0x28, s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s6 sp+0x30, ra sp+0x38
// ADXM file-system thread body: loops on the server callback until told to exit.
void adxm_fs_proc(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0053fcf8
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s5, sp, 0x28);
    s5 = 0x790000;
    sd(s0, sp, 0x0);
    v0 = addiu(s5, -30936);  // &0x788728
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    sd(s4, sp, 0x20);
    sd(s6, sp, 0x30);
    sd(ra, sp, 0x38);
    ld(v1, v0, 0);  // 0x788728
    v0 = 0x790000;
    if (v1 == 0) {
        // 0x0053fd30
        charge(ctx, 10);
        v0 = 0x790000;
        v1 = 0x790000;
        a0 = 0x790000;
        s2 = 0x12000000;
        s4 = addiu(v0, -31048);  // &0x7886B8
        s3 = addiu(v1, -31088);  // &0x788690
        s1 = addiu(a0, -30876);  // &0x788764
        s6 = 1;
        s2 = s2 | 0xE0;
        for (;;) {
            // 0x0053fd58
            charge(ctx, 6);
            ld(v0, s4, 0);
            lhu(v1, s1, 0);
            v0 = daddiu(v0, 1);
            sd(v0, s4, 0);
            sw(s6, s3, 0);
            if (v1 != 0) {
                // 0x0053fd70
                charge(ctx, 2);
                lhu(v0, s1, 0);
                sd(v0, s2, 0);
            }
            // 0x0053fd78
            charge(ctx, 5);
            jal(ctx, 0x53FD78u, gen::fn_SVM_ExecSvrFs_00565420);
            lhu(v1, s1, 0);
            if (v1 != 0) {
                sd(zero, s2, 0);
            }
            // 0x0053fd8c
            charge(ctx, 5);
            sw(zero, s3, 0);
            s0 = addiu(s5, -30936);
            ld(v0, s0, 0);
            if (v0 != 0) {
                v0 = 0x790000;
            } else {
                // 0x0053fda0
                charge(ctx, 5);
                jal(ctx, 0x53FDA0u, gen::fn_sub_540098_00540098);
                ld(v0, s0, 0);
                cc = v0 == 0;  // the condition, before the delay slot changes it
                v0 = 0x790000;
                if (cc) {
                    backedge(ctx);
                    continue;
                }
            }
            break;
        }
    }
    // 0x0053fdb4
    charge(ctx, 13);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    v1 = 1;
    ld(s2, sp, 0x10);
    v0 = addiu(v0, -30928);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(s6, sp, 0x30);
    ld(ra, sp, 0x38);
    sd(v1, v0, 0);
    sp = addiu(sp, 0x40);
    gen::fn__sceExitDeleteThread_00502fa0(ctx);  // tail call
}

// 0x00557B80 SRD_ReqRdDvd -- 236 bytes; frame 0x40: s1 sp+0x8, s0 sp+0x0, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s5 sp+0x28, s6 sp+0x30, ra sp+0x38
// SRD: requests a DVD read (checks sceCdSync first).
void SRD_ReqRdDvd(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00557b80
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s1, sp, 0x8);
    s1 = a0;
    a0 = 4608;
    sd(s0, sp, 0x0);
    sd(s2, sp, 0x10);
    s2 = t0;
    sd(s3, sp, 0x18);
    s3 = a1;
    sd(s4, sp, 0x20);
    s4 = 0;
    sd(s5, sp, 0x28);
    s5 = a2;
    sd(s6, sp, 0x30);
    sd(ra, sp, 0x38);
    s6 = a3;
    jal(ctx, 0x557BBCu, gen::fn_sub_558988_00558988);
    a0 = 1;
    jal(ctx, 0x557BC4u, gen::fn_sceCdSync_00510148);
    a0 = 4609;
    s0 = v0;
    jal(ctx, 0x557BD0u, gen::fn_sub_558988_00558988);
    v1 = 1;
    v0 = 0;
    if (s0 != v1) {
        // 0x00557be4
        charge(ctx, 6);
        jal(ctx, 0x557BE4u, gen::fn_sub_5649A8_005649a8);
        a0 = 1;
        lb(v1, s1, 2);
        v0 = 3;
        if (v1 != 0) {
            // 0x00557bfc
            charge(ctx, 2);
            cc = v1 == v0;  // the condition, before the delay slot changes it
            v0 = 9;
            if (cc) {
                goto L_00557c0c;
            }
            // 0x00557c04
            charge(ctx, 2);
            if (v1 == v0) {
                goto L_00557c0c;
            }
            goto L_00557c38;
        }
    L_00557c0c:
        charge(ctx, 11);
        sb(a0, s1, 2);
        s4 = 1;
        sb(a0, s1, 1);
        sw(s3, s1, 8);
        lwl(v0, s2, 3);
        lwr(v0, s2, 0);
        swl(v0, s1, 23);
        swr(v0, s1, 20);
        sw(s5, s1, 12);
        sw(s6, s1, 16);
        sw(zero, s1, 4);
    L_00557c38:
        charge(ctx, 3);
        jal(ctx, 0x557C38u, gen::fn_sub_564A20_00564a20);
        v0 = s4;
    }
    // 0x00557c44 (the shared epilogue, written out on this path)
    charge(ctx, 10);
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

// 0x00557FE8 srd_check_dvd_error -- 268 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, s2 sp+0x10, ra sp+0x18
// SRD: maps sceCdGetError to the SRD error state (prints unknown codes).
void srd_check_dvd_error(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00557fe8
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v1 = 0x7A0000;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s0, sp, 0x0);
    v1 = addiu(v1, 2300);  // &0x7A08FC
    sd(s2, sp, 0x10);
    v0 = 0;
    sd(ra, sp, 0x18);
    lw(a0, v1, 0);  // 0x7A08FC
    v1 = 2;
    if (a0 != 0) {
        // 0x00558018
        charge(ctx, 3);
        lb(a0, s1, 2);
        if (a0 == v1) {
            // 0x00558024
            charge(ctx, 9);
            s2 = 0x7A0000;
            a1 = 1;
            a0 = addiu(s2, 2308);  // &0x7A0904
            v0 = 0x7A0000;
            sw(a1, a0, 0);  // 0x7A0904
            v0 = addiu(v0, 2296);  // &0x7A08F8
            lw(v1, v0, 0);  // 0x7A08F8
            if (v1 != a1) {
                // 0x00558080
                charge(ctx, 8);
                a0 = 5376;
                jal(ctx, 0x558080u, gen::fn_sub_558988_00558988);
                jal(ctx, 0x558088u, gen::fn_sceCdGetError_00510ef0);
                a0 = 5377;
                s0 = v0;
                jal(ctx, 0x558094u, gen::fn_sub_558988_00558988);
                v0 = addiu(s0, 1);
            } else {
                // 0x00558048
                charge(ctx, 13);
                jal(ctx, 0x558048u, gen::fn_sub_5649D8_005649d8);
                a0 = 5120;
                jal(ctx, 0x558050u, gen::fn_sub_558988_00558988);
                jal(ctx, 0x558058u, gen::fn_sceCdGetError_00510ef0);
                a0 = 5121;
                s0 = v0;
                jal(ctx, 0x558064u, gen::fn_sub_558988_00558988);
                jal(ctx, 0x55806Cu, gen::fn_sub_564A50_00564a50);
                v0 = addiu(s0, 1);
            }
            // 0x005580a0
            charge(ctx, 5);
            v1 = addiu(s2, 2308);
            v0 = sltiu(v0, 2);
            sw(zero, v1, 0);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = 0;
            if (!cc) {
                // 0x005580b4
                charge(ctx, 3);
                v0 = 32;
                a0 = 0x7C0000;
                if (s0 == v0) {
                    // 0x005580d8
                    charge(ctx, 1);
                    v0 = 0;
                } else {
                    // 0x005580c0
                    charge(ctx, 6);
                    sw(s0, s1, 52);
                    a1 = s0;
                    a0 = addiu(a0, 18168);
                    jal(ctx, 0x5580C8u, gen::fn_scePrintf_00505e48);
                    v0 = 1;
                }
            }
            goto L_005580dc;
        }
        ld(s0, sp, 0x0);
        // 0x005580e0 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
L_005580dc:
    charge(ctx, 1);
    ld(s0, sp, 0x0);
    // 0x005580e0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00558DD0 sub_558DD0 -- 868 bytes; frame 0x70: s2 sp+0x50, s0 sp+0x40, s1 sp+0x48, s3 sp+0x58, ra sp+0x60
// DTR transfer step: moves one chunk between the EE and the IOP ring buffers (sceSifSetDma, SyncDCache), with the
// "Internal Error" checks of the chunk descriptors.
void sub_558DD0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00558dd0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    v0 = 1;
    sd(s2, sp, 0x50);
    s2 = a0;
    sd(s0, sp, 0x40);
    sd(s1, sp, 0x48);
    sd(s3, sp, 0x58);
    sd(ra, sp, 0x60);
    lb(a0, s2, 1);
    ld(s0, sp, 0x40);
    if (a0 == v0) {
        // 0x00558dfc
        charge(ctx, 3);
        lb(v0, s2, 2);
        lbu(v1, s2, 2);
        if (v0 == a0) {
            // 0x00558e08
            charge(ctx, 24);
            lw(a0, s2, 4);
            s0 = addiu(s2, 12);
            a1 = 0;
            a2 = s0;
            lw(v1, a0, 0);
            lw(v0, v1, 32);
            s1 = addiu(s2, 20);
            jalr(ctx, 0x558E20u, v0.u());
            sw(zero, s0, 0);
            lw(a0, s2, 8);
            a1 = 1;
            sw(zero, s2, 16);
            lw(v1, a0, 0);
            lw(v0, v1, 32);
            a2 = s1;
            jalr(ctx, 0x558E40u, v0.u());
            sw(zero, s1, 0);
            lw(v0, s2, 60);
            lw(v1, s2, 16);
            sw(zero, s2, 24);
            v0 = addu(v0, v1);
            sb(zero, s2, 2);
            sw(v0, s2, 60);
            if (v1 != 0) {
                // 0x00558e68
                charge(ctx, 4);
                a0 = 0x7C0000;
                a0 = addiu(a0, 18896);  // "DTR_ExecHndl: Internal Error\n"
                jal(ctx, 0x558E6Cu, gen::fn_sub_541760_00541760);
                for (;;) {
                    // 0x00558e78
                    charge(ctx, 7);
                    backedge(ctx);
                }
            }
            // 0x00558e98
            charge(ctx, 1);
            lbu(v1, s2, 2);
        }
        // 0x00558e9c
        charge(ctx, 2);
        ld(s0, sp, 0x40);
        if (v1 == 0) {
            // 0x00558ea4
            charge(ctx, 27);
            lw(a0, s2, 4);
            a2 = 0x7FFF0000;
            a3 = sp;
            a1 = 1;
            lw(v1, a0, 0);
            lw(v0, v1, 24);
            a2 = a2 | 0xFFFF;
            jalr(ctx, 0x558EBCu, v0.u());
            lw(a0, s2, 8);
            s3 = addiu(sp, 0x20);
            a2 = 0x7FFF0000;
            lw(v1, a0, 0);
            a1 = 0;
            a2 = a2 | 0xFFFF;
            lw(v0, v1, 24);
            a3 = s3;
            jalr(ctx, 0x558EE0u, v0.u());
            lw(a1, s2, 56);
            lw(s1, sp, 0x24);
            s0 = addiu(sp, 0x10);
            lw(t0, sp, 0x4);
            a0 = sp;
            a2 = sp;
            a3 = s0;
            v1 = slt(t0, s1);
            if (a1 == 0) {
                brk(ctx, 0x558F0Cu, 0x7u);
            }
            // 0x00558f10
            charge(ctx, 26);
            if (v1 != 0) s1 = t0;
            div(s1, a1);
            mflo(v0);
            mult(s1, v0, a1);
            a1 = s1;
            jal(ctx, 0x558F20u, gen::fn_sub_563C28_00563c28);
            lw(a0, s2, 4);
            a2 = s0;
            lw(v1, a0, 0);
            lw(v0, v1, 28);
            a1 = 1;
            jalr(ctx, 0x558F38u, v0.u());
            a0 = s3;
            s0 = addiu(sp, 0x30);
            a1 = s1;
            a2 = s3;
            a3 = s0;
            jal(ctx, 0x558F50u, gen::fn_sub_563C28_00563c28);
            lw(a0, s2, 8);
            a2 = s0;
            lw(v1, a0, 0);
            lw(v0, v1, 28);
            a1 = 0;
            jalr(ctx, 0x558F68u, v0.u());
            if (i64(s1) <= 0) {
                ld(s0, sp, 0x40);
            } else {
                // 0x00558f78
                charge(ctx, 4);
                lw(v1, sp, 0x4);
                v0 = v1 & 0x3F;
                a0 = 0x7C0000;
                if (v0 != 0) {
                    // 0x00558f88
                    charge(ctx, 8);
                    a0 = addiu(a0, 18928);
                    jal(ctx, 0x558F88u, gen::fn_sub_541760_00541760);
                    a0 = 0x7C0000;
                    lw(a1, sp, 0x0);
                    a0 = addiu(a0, 18968);  // "cks.data=%08x, ckd.data=%08x, cks.len=%d\n"
                    lw(a2, sp, 0x20);
                    link(ctx, 0x558FA0u);  // $ra first: the delay slot below depends on it
                    lw(a3, sp, 0x4);
                    call(ctx, gen::fn_sub_541760_00541760);
                    for (;;) {
                        // 0x00558fa8
                        charge(ctx, 7);
                        backedge(ctx);
                    }
                }
                // 0x00558fc8
                charge(ctx, 4);
                lw(a0, sp, 0x0);
                v0 = a0 & 0x3F;
                if (v0 != 0) {
                    // 0x00558fd8
                    charge(ctx, 10);
                    a0 = 0x7C0000;
                    a0 = addiu(a0, 19016);  // "DTR_ExecHndl: Internal Error cks.data\n"
                    jal(ctx, 0x558FDCu, gen::fn_sub_541760_00541760);
                    a0 = 0x7C0000;
                    lw(a1, sp, 0x0);
                    a0 = addiu(a0, 18968);  // "cks.data=%08x, ckd.data=%08x, cks.len=%d\n"
                    lw(a2, sp, 0x20);
                    link(ctx, 0x558FF4u);  // $ra first: the delay slot below depends on it
                    lw(a3, sp, 0x4);
                    call(ctx, gen::fn_sub_541760_00541760);
                    for (;;) {
                        // 0x00559000
                        charge(ctx, 7);
                        backedge(ctx);
                    }
                }
                lw(v0, sp, 0x20);
                // 0x00559020
                charge(ctx, 3);
                v0 = v0 & 0x3F;
                a1 = addu(a0, v1);
                if (v0 != 0) {
                    // 0x0055902c
                    charge(ctx, 9);
                    a0 = 0x7C0000;
                    a0 = addiu(a0, 19056);  // "DTR_ExecHndl: Internal Error ckd.data\n"
                    jal(ctx, 0x559030u, gen::fn_sub_541760_00541760);
                    a0 = 0x7C0000;
                    lw(a1, sp, 0x0);
                    a0 = addiu(a0, 18968);  // "cks.data=%08x, ckd.data=%08x, cks.len=%d\n"
                    lw(a2, sp, 0x20);
                    link(ctx, 0x559048u);  // $ra first: the delay slot below depends on it
                    lw(a3, sp, 0x4);
                    call(ctx, gen::fn_sub_541760_00541760);
                    for (;;) {
                        // 0x00559050
                        charge(ctx, 7);
                        backedge(ctx);
                    }
                }
                // 0x00559070
                charge(ctx, 17);
                a1 = addiu(a1, -1);
                jal(ctx, 0x559070u, gen::fn_SyncDCache_00503a58);
                v0 = 0xFFF0000;
                lw(v1, sp, 0x0);
                v0 = v0 | 0xFFFF;
                lw(a2, sp, 0x4);
                a0 = addiu(s2, 28);
                lw(a3, sp, 0x20);
                v1 = v1 & v0;
                sw(v1, s2, 28);
                a1 = 1;
                sw(a3, s2, 32);
                sw(a2, s2, 36);
                link(ctx, 0x5590A4u);  // $ra first: the delay slot below depends on it
                sw(zero, s2, 40);
                call(ctx, gen::fn_sceSifSetDma_00506088);
                sw(v0, s2, 44);
                if (v0 != 0) {
                    // 0x005590f0
                    charge(ctx, 11);
                    ldl(a0, sp, 0x7);
                    ldr(a0, sp, 0x0);
                    sdl(a0, s2, 19);
                    sdr(a0, s2, 12);
                    v0 = 1;
                    ldl(a0, s3, 7);
                    ldr(a0, s3, 0);
                    sdl(a0, s2, 27);
                    sdr(a0, s2, 20);
                    sb(v0, s2, 2);
                    ld(s0, sp, 0x40);
                } else {
                    // 0x005590b4
                    charge(ctx, 14);
                    lw(a0, s2, 4);
                    a1 = 1;
                    lw(v1, a0, 0);
                    lw(v0, v1, 28);
                    a2 = sp;
                    jalr(ctx, 0x5590C4u, v0.u());
                    lw(a0, s2, 8);
                    a2 = s3;
                    lw(v1, a0, 0);
                    lw(v0, v1, 28);
                    a1 = 0;
                    jalr(ctx, 0x5590DCu, v0.u());
                    ld(s0, sp, 0x40);
                }
            }
        }
    }
    // 0x0055911c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s1, sp, 0x48);
    ld(s2, sp, 0x50);
    ld(s3, sp, 0x58);
    ld(ra, sp, 0x60);
    sp = addiu(sp, 0x70);
}

// 0x00559140 DTR_ExecServer -- 188 bytes; frame 0x20: ra sp+0x18, s0 sp+0x0, s1 sp+0x8, s2 sp+0x10
// DTR_ExecServer: runs the transfer step for every active DTR while no SIF DMA is pending.
void DTR_ExecServer(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00559140
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x7A0000;
    sd(ra, sp, 0x18);
    sd(s0, sp, 0x0);
    s0 = addiu(v0, 2360);  // &0x7A0938
    sd(s1, sp, 0x8);
    s1 = 0;
    sd(s2, sp, 0x10);
    s2 = 1;
    for (;;) {
        // 0x00559168
        charge(ctx, 3);
        lb(v1, s0, 1);
        if (v1 != s2) {
            s1 = addiu(s1, 1);
        } else {
            // 0x00559174
            charge(ctx, 3);
            lb(v0, s0, 2);
            if (v0 != v1) {
                s1 = addiu(s1, 1);
                goto L_00559194;
            }
            // 0x00559180
            charge(ctx, 4);
            link(ctx, 0x559180u);  // $ra first: the delay slot below depends on it
            lw(a0, s0, 44);
            call(ctx, gen::fn__sceSifDmaStat_00503500);
            if (i64(v0) >= 0) {
                ld(s0, sp, 0x0);
                goto L_005591e8;
            }
            // 0x00559190
            charge(ctx, 1);
            s1 = addiu(s1, 1);
            goto L_00559194;
        }
    L_00559194:
        charge(ctx, 3);
        v0 = slti(s1, 32);
        s0 = addiu(s0, 64);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x005591a0
    charge(ctx, 4);
    v0 = 0x7A0000;
    s2 = 1;
    s0 = addiu(v0, 2360);  // &0x7A0938
    s1 = 31;
    for (;;) {
        // 0x005591b0
        charge(ctx, 3);
        lb(v0, s0, 0);
        if (v0 != s2) {
            s1 = addiu(s1, -1);
        } else {
            // 0x005591bc
            charge(ctx, 3);
            a0 = s0;
            jal(ctx, 0x5591BCu, gen::fn_sub_558DD0_00558dd0);
            s1 = addiu(s1, -1);
        }
        // 0x005591c8
        charge(ctx, 2);
        s0 = addiu(s0, 64);
        if (i64(s1) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x005591d0
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_559D18_00559d18(ctx);  // tail call
    return;
L_005591e8:
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x005593A8 DTR_Stop -- 176 bytes; frame 0x20: s2 sp+0x10, s0 sp+0x0, s1 sp+0x8, ra sp+0x18
// DTR_Stop: waits for the pending SIF DMA and stops the transfer.
void DTR_Stop(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005593a8
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v1 = 1;
    sd(s2, sp, 0x10);
    s2 = a0;
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x18);
    sb(zero, s2, 1);
    lb(v0, s2, 2);
    ld(s0, sp, 0x0);
    if (v0 == v1) {
        // 0x005593d4
        charge(ctx, 1);
        for (;;) {
            // 0x005593d8
            charge(ctx, 4);
            link(ctx, 0x5593D8u);  // $ra first: the delay slot below depends on it
            lw(a0, s2, 44);
            call(ctx, gen::fn__sceSifDmaStat_00503500);
            s0 = addiu(s2, 12);
            if (i64(v0) < 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x005593e8
        charge(ctx, 23);
        lw(a0, s2, 4);
        a1 = 0;
        a2 = s0;
        lw(v1, a0, 0);
        lw(v0, v1, 32);
        s1 = addiu(s2, 20);
        jalr(ctx, 0x5593FCu, v0.u());
        sw(zero, s0, 0);
        lw(a0, s2, 8);
        a1 = 1;
        sw(zero, s2, 16);
        lw(v1, a0, 0);
        lw(v0, v1, 32);
        a2 = s1;
        jalr(ctx, 0x55941Cu, v0.u());
        sw(zero, s1, 0);
        lw(v0, s2, 60);
        lw(v1, s2, 16);
        sb(zero, s2, 2);
        v0 = addu(v0, v1);
        sw(zero, s2, 24);
        sw(v0, s2, 60);
        ld(s0, sp, 0x0);
    }
    // 0x00559444 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00559938 sub_559938 -- 368 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// DTX: sends the EE request buffer to the IOP (sceSifSetDma) and refreshes the reply buffer cache.
void sub_559938(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00559938
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v1 = 0x7A0000;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    v1 = addiu(v1, 4440);  // &0x7A1158
    sd(ra, sp, 0x10);
    a0 = 1;
    lw(v0, v1, 0);  // 0x7A1158
    lb(a1, s0, 1);
    v0 = addiu(v0, 1);
    sw(v0, v1, 0);  // 0x7A1158
    if (a1 == a0) {
        // 0x0055996c
        charge(ctx, 6);
        lw(v0, s0, 20);
        lw(v1, s0, 8);
        lw(a0, v0, 60);
        v1 = slt(v1, a0);
        if (v1 != 0) {
            // 0x00559984
            charge(ctx, 15);
            lw(v0, s0, 16);
            lw(a1, s0, 12);
            a0 = a1;
            a1 = addu(a1, v0);
            a1 = addiu(a1, -1);
            jal(ctx, 0x559994u, gen::fn_InvalidDCache_00503b98);
            lw(v1, s0, 32);
            lw(a0, s0, 36);
            lw(a1, s0, 12);
            jt = v1.u();  // the target, read before the delay slot
            link(ctx, 0x5599A8u);  // $ra = the return address
            lw(a2, s0, 16);
            call_ptr(ctx, jt);
            lw(v0, s0, 20);
            lw(v1, v0, 60);
            sb(zero, s0, 1);
            sw(v1, s0, 8);
            goto L_005599c0;
        }
        lw(v0, s0, 0);
        goto L_005599c4;
    }
L_005599c0:
    charge(ctx, 1);
    lw(v0, s0, 0);
L_005599c4:
    charge(ctx, 6);
    v1 = 0xFF0000;
    v1 = v1 | 0xFF00;  // &0xFFFF00
    a0 = 0x10000;
    v0 = v0 & v1;
    if (v0 != a0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x005599dc
        charge(ctx, 5);
        v0 = 0x7A0000;
        a0 = 1;
        lw(v1, v0, 4428);  // 0x7A114C
        if (v1 != a0) {
            ld(s0, sp, 0x0);
        } else {
            // 0x005599f0
            charge(ctx, 34);
            lw(a2, s0, 16);
            s1 = addiu(s0, 48);
            lw(a0, s0, 44);
            lw(v0, s0, 40);
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x559A00u);  // $ra = the return address
            lw(a1, s0, 12);
            call_ptr(ctx, jt);
            lw(v1, s0, 8);
            lw(v0, s0, 20);
            v1 = addiu(v1, 1);
            lw(a1, s0, 12);
            sw(v1, s0, 8);
            sw(v1, v0, 60);
            a0 = a1;
            lw(v0, s0, 16);
            a1 = addu(a1, v0);
            a1 = addiu(a1, -1);
            jal(ctx, 0x559A2Cu, gen::fn_SyncDCache_00503a58);
            lw(a1, s0, 12);
            lw(v0, s0, 16);
            a0 = a1;
            a1 = addu(a1, v0);
            a1 = addiu(a1, 63);
            jal(ctx, 0x559A44u, gen::fn_InvalidDCache_00503b98);
            lw(v1, s0, 12);
            v0 = 0xFFF0000;
            lw(a0, s0, 24);
            v0 = v0 | 0xFFFF;
            lw(a1, s0, 28);
            v1 = v1 & v0;
            sw(a0, s0, 52);
            sw(v1, s0, 48);
            sw(a1, s0, 56);
            sw(zero, s0, 60);
            for (;;) {
                // 0x00559a78
                charge(ctx, 5);
                a0 = s1;
                a1 = 1;
                jal(ctx, 0x559A7Cu, gen::fn_sceSifSetDma_00506088);
                sw(v0, s0, 64);
                if (v0 != 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00559a8c
            charge(ctx, 3);
            v0 = 1;
            sb(v0, s0, 1);
            ld(s0, sp, 0x0);
        }
    }
    // 0x00559a98 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0055F748 sub_55F748 -- 760 bytes; frame 0x50: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s5 sp+0x28, s6 sp+0x30, s7 sp+0x38, fp sp+0x40, ra sp+0x48
// PS2RNA: creates the IOP sound output handle (IOP heap, stream joints, remote stream).
void sub_55F748(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0055f748
    enter(ctx, 14);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x50);
    lw(v1, v0, -27656);  // 0x7A93F8
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    sd(s4, sp, 0x20);
    sd(s5, sp, 0x28);
    sd(s6, sp, 0x30);
    sd(s7, sp, 0x38);
    sd(fp, sp, 0x40);
    sd(ra, sp, 0x48);
    if (v1 != 0) {
        // 0x0055f7a0
        charge(ctx, 1);
        s5 = 0x7B0000;
    } else {
        // 0x0055f780
        charge(ctx, 8);
        v0 = 0x40000;
        s5 = 0x7B0000;
        v1 = 16;
        a0 = 0x7B0000;
        v0 = v0 | 0x1000;
        sw(v1, s5, -27664);  // 0x7A93F0
        sw(v0, a0, -27660);  // 0x7A93F4
    }
    // 0x0055f7a4
    charge(ctx, 5);
    s3 = 0x7B0000;
    s0 = addiu(s3, -27652);  // &0x7A93FC
    lw(v0, s0, 0);  // 0x7A93FC
    if (v0 != 0) {
        s0 = 0x7B0000;
    } else {
        // 0x0055f7b8
        charge(ctx, 7);
        s2 = 0x7B0000;
        s1 = addiu(s2, -27660);  // &0x7A93F4
        lw(a0, s1, 0);  // 0x7A93F4
        a0 = addiu(a0, 64);
        jal(ctx, 0x55F7C4u, gen::fn_sceSifAllocIopHeap_0050b620);
        sw(v0, s0, 0);
        if (v0 == 0) {
            // 0x0055f7d4
            charge(ctx, 5);
            lw(a1, s1, 0);
            a0 = 0x7C0000;
            a0 = addiu(a0, 25400);  // "PS2RNA: E01112903: Failed, sceSifAllocIopHeap(%d) in ps2rna_init_psj\n"
            a1 = addiu(a1, 64);
            jal(ctx, 0x55F7E0u, gen::fn_sub_541760_00541760);
            for (;;) {
                // 0x0055f7e8
                charge(ctx, 7);
                backedge(ctx);
            }
        }
        // 0x0055f808
        charge(ctx, 16);
        s0 = addiu(s3, -27652);
        lw(a1, s2, -27660);
        lw(a2, s0, 0);
        a0 = 0x7C0000;
        a0 = addiu(a0, 25472);  // "PS2RNA: sceSifAllocIopHeap(%d) ret=0x%08x\n"
        a1 = addiu(a1, 64);
        jal(ctx, 0x55F81Cu, gen::fn_sub_541760_00541760);
        lw(v1, s0, 0);
        a1 = si(-64);
        a0 = 0x7B0000;
        v1 = addiu(v1, 64);
        s0 = 0x7B0000;
        v1 = v1 & a1;
        v0 = 1;
        sb(v0, a0, -27644);  // 0x7A9404
        sw(v1, s0, -27648);  // 0x7A9400
    }
    // 0x0055f848
    charge(ctx, 9);
    s4 = 0x7B0000;
    a1 = 0;
    a0 = addiu(s4, -27568);  // &0x7A9450
    a2 = 768;
    jal(ctx, 0x55F854u, gen::fn_memset_00521408);
    lw(s1, s0, -27648);
    lw(v0, s5, -27664);
    s2 = 0;
    if (i64(v0) > 0) {
        // 0x0055f86c
        charge(ctx, 5);
        s6 = 0x7B0000;
        s3 = 0;
        fp = 0x7C0000;
        s7 = 0x7C0000;
        v0 = addiu(s4, -27568);
        for (;;) {
            // 0x0055f880
            charge(ctx, 5);
            v1 = s1 & 0x3F;
            s0 = addu(s3, v0);
            s3 = addiu(s3, 24);
            sb(zero, s0, 0);
            if (v1 != 0) {
                goto L_0055f894_11;
            }
            // 0x0055f8c0
            charge(ctx, 14);
            a1 = s1;
            s1 = addiu(s1, 256);
            a0 = 1;
            a2 = 256;
            jal(ctx, 0x55F8CCu, gen::fn_sub_563FE0_00563fe0);
            v1 = sll(s2, 8);
            a1 = addiu(s6, -26800);
            a0 = 1;
            a1 = addu(v1, a1);
            v1 = s1 & 0x3F;
            s2 = addiu(s2, 1);
            a2 = 256;
            sw(v0, s0, 4);
            if (v0 == 0) {
                goto L_0055f8f8_14;
            }
            // 0x0055f928
            charge(ctx, 2);
            v0 = 0x7C0000;
            if (v1 != 0) {
                goto L_0055f930_17;
            }
            // 0x0055f958
            charge(ctx, 7);
            jal(ctx, 0x55F958u, gen::fn_sub_562F90_00562f90);
            v1 = 16384;
            sw(v0, s0, 8);
            a1 = 0;
            a2 = addiu(s0, 16);
            if (v0 == 0) {
                goto L_0055f974_20;
            }
            // 0x0055f9a0
            charge(ctx, 13);
            lw(a0, s0, 8);
            sw(v1, s0, 20);
            lw(v1, a0, 0);
            sw(s1, s0, 16);
            lw(v0, v1, 32);
            s1 = addiu(s1, 16384);
            jalr(ctx, 0x55F9B4u, v0.u());
            lw(a0, s0, 8);
            lw(a1, s0, 4);
            a2 = 1;
            jal(ctx, 0x55F9C4u, gen::fn_sub_564738_00564738);
            sw(v0, s0, 12);
            if (v0 == 0) {
                goto L_0055f9d4_23;
            }
            // 0x0055fa00
            charge(ctx, 4);
            lw(v0, s5, -27664);
            v0 = slt(s2, v0);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = addiu(s4, -27568);
            if (!cc) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0055fa10 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(s6, sp, 0x30);
    ld(s7, sp, 0x38);
    ld(fp, sp, 0x40);
    ld(ra, sp, 0x48);
    sp = addiu(sp, 0x50);
    return;
L_0055f894_11:
    charge(ctx, 3);
    v0 = 0x7C0000;
    a0 = addiu(v0, 25520);  // "E0110101: ps2rna_init_psj wk size error\n"
    jal(ctx, 0x55F898u, gen::fn_sub_541760_00541760);
    for (;;) {
        // 0x0055f8a0
        charge(ctx, 7);
        backedge(ctx);
    }
L_0055f8f8_14:
    charge(ctx, 4);
    v0 = 0x7C0000;
    a0 = addiu(v0, 25568);  // "E0110102: ps2rna_init_psj: can't creat SJUNI_CreaetRmt\n"
    jal(ctx, 0x55F8FCu, gen::fn_sub_541760_00541760);
    for (;;) {
        // 0x0055f908
        charge(ctx, 7);
        backedge(ctx);
    }
L_0055f930_17:
    charge(ctx, 2);
    a0 = addiu(v0, 25624);
    jal(ctx, 0x55F930u, gen::fn_sub_541760_00541760);
    for (;;) {
        // 0x0055f938
        charge(ctx, 7);
        backedge(ctx);
    }
L_0055f974_20:
    charge(ctx, 3);
    a0 = addiu(fp, 0x6448);
    jal(ctx, 0x55F974u, gen::fn_sub_541760_00541760);
    for (;;) {
        // 0x0055f980
        charge(ctx, 7);
        backedge(ctx);
    }
L_0055f9d4_23:
    charge(ctx, 3);
    a0 = addiu(s7, 25728);
    jal(ctx, 0x55F9D4u, gen::fn_sub_541760_00541760);
    for (;;) {
        // 0x0055f9e0
        charge(ctx, 7);
        backedge(ctx);
    }
}

// 0x0055FF70 PS2RNA_Init -- 716 bytes; frame 0x60: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, s3 sp+0x28, s4 sp+0x30, s5 sp+0x38, s6 sp+0x40, s7 sp+0x48, ra sp+0x50
// PS2RNA_Init: initialises the PS2 sound output layer (DTX, IOP heap, handle table).
void PS2RNA_Init(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055ff70
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    v1 = 0x7B0000;
    sd(s0, sp, 0x10);
    v0 = 0x7B0000;
    sd(s1, sp, 0x18);
    v0 = addiu(v0, -31672);  // "hb|"
    sd(s2, sp, 0x20);
    sd(s3, sp, 0x28);
    sd(s4, sp, 0x30);
    sd(s5, sp, 0x38);
    sd(s6, sp, 0x40);
    sd(s7, sp, 0x48);
    sd(ra, sp, 0x50);
    lw(a0, v1, -27656);  // 0x7A93F8
    v1 = 1;
    lw(a1, v0, 0);  // 0x7A8448
    s7 = 0x7B0000;
    if (a0 == v1) {
        // 0x0055ffb8
        charge(ctx, 4);
        v0 = 0x7B0000;
        lw(v1, v0, -27664);  // 0x7A93F0
        ld(s0, sp, 0x10);
        if (i64(v1) > 0) {
            // 0x0055ffc8
            charge(ctx, 1);
            s7 = 0x7B0000;
            goto L_0055ffcc;
        }
        // 0x00560214 (the shared epilogue, written out on this path)
        charge(ctx, 10);
        ld(s1, sp, 0x18);
        ld(s2, sp, 0x20);
        ld(s3, sp, 0x28);
        ld(s4, sp, 0x30);
        ld(s5, sp, 0x38);
        ld(s6, sp, 0x40);
        ld(s7, sp, 0x48);
        ld(ra, sp, 0x50);
        sp = addiu(sp, 0x60);
        return;
    }
L_0055ffcc:
    charge(ctx, 3);
    lw(v0, s7, -27588);
    v1 = addiu(s7, -27588);
    if (v0 == 0) {
        // 0x0055ffd8
        charge(ctx, 24);
        s0 = 0x7B0000;
        s3 = 0x7B0000;
        s0 = addiu(s0, -16744);  // &0x7ABE98
        jal(ctx, 0x55FFE0u, gen::fn_sub_5642D0_005642d0);
        s1 = addiu(s3, -27580);  // &0x7A9444
        jal(ctx, 0x55FFE8u, gen::fn_sub_564528_00564528);
        s4 = 0x7B0000;
        jal(ctx, 0x55FFF0u, gen::fn_DTX_Init_00559aa8);
        s2 = 0x7B0000;
        jal(ctx, 0x55FFF8u, gen::fn_PS2RNA_InitIopSnd_00560298);
        jal(ctx, 0x560000u, gen::fn_sub_55F748_0055f748);
        a0 = s0;
        a1 = 0;
        a2 = 2256;
        jal(ctx, 0x560010u, gen::fn_memset_00521408);
        a0 = 2176;
        lw(v1, s1, 0);  // 0x7A9444
        s0 = addiu(s0, 64);  // &0x7ABED8
        v0 = si(-64);
        s0 = s0 & v0;
        sw(a0, s4, -16748);  // 0x7ABE94
        sw(s0, s2, -27584);  // 0x7A9440
        if (v1 == 0) {
            // 0x00560038
            charge(ctx, 4);
            a0 = 2256;
            jal(ctx, 0x560038u, gen::fn_sceSifAllocIopHeap_0050b620);
            sw(v0, s1, 0);
            if (v0 == 0) {
                // 0x00560048
                charge(ctx, 4);
                a0 = 0x7C0000;
                a1 = 2256;
                a0 = addiu(a0, 25784);  // "PS2RNA: E01112902: Failed, sceSifAllocIopHeap(%d) in PS2RNA_Init."
                jal(ctx, 0x560050u, gen::fn_sub_541760_00541760);
                for (;;) {
                    // 0x00560058
                    charge(ctx, 7);
                    backedge(ctx);
                }
            }
        }
        // 0x00560078
        charge(ctx, 20);
        s0 = addiu(s3, -27580);
        s6 = 0x7C0000;
        lw(a2, s0, 0);
        a0 = addiu(s6, 25472);  // "PS2RNA: sceSifAllocIopHeap(%d) ret=0x%08x\n"
        a1 = 2256;
        jal(ctx, 0x560088u, gen::fn_sub_541760_00541760);
        t0 = 0x7B0000;
        lw(v0, s0, 0);
        s0 = 0x7B0000;
        v1 = si(-64);
        lw(a1, s2, -27584);
        v0 = addiu(v0, 64);
        lw(a3, s4, -16748);
        v0 = v0 & v1;
        a0 = 1;
        a2 = v0;
        link(ctx, 0x5600B8u);  // $ra first: the delay slot below depends on it
        sw(v0, t0, -27576);
        call(ctx, gen::fn_sub_559718_00559718);
        sw(v0, s0, -16752);  // 0x7ABE90
        if (v0 == 0) {
            // 0x005600c8
            charge(ctx, 4);
            a0 = 0x7C0000;
            a0 = addiu(a0, 25856);  // "E0100302: PS2RNA_Init can't create DTX\n"
            jal(ctx, 0x5600CCu, gen::fn_sub_541760_00541760);
            for (;;) {
                // 0x005600d8
                charge(ctx, 7);
                backedge(ctx);
            }
        }
        // 0x005600f8
        charge(ctx, 16);
        s0 = addiu(s0, -16752);
        a1 = 0x560000;
        lw(a0, s0, 0);
        a1 = addiu(a1, -1120);  // &sub_55FBA0
        a2 = 0;
        s1 = 0x7B0000;
        jal(ctx, 0x56010Cu, gen::fn_sub_559918_00559918);
        a1 = 0x560000;
        lw(a0, s0, 0);
        a1 = addiu(a1, -1024);  // &sub_55FC00
        a2 = 0;
        s4 = addiu(s1, -27636);  // &0x7A940C
        jal(ctx, 0x560124u, gen::fn_sub_559928_00559928);
        lw(v0, s4, 0);  // 0x7A940C
        s3 = 0x7B0000;
        if (v0 != 0) {
            // 0x005601b8
            charge(ctx, 2);
            s5 = 0x7B0000;
            lw(v0, s1, -27636);
        } else {
            // 0x00560138
            charge(ctx, 13);
            v0 = 0x7B0000;
            s5 = 0x7B0000;
            lw(v1, v0, -27664);  // 0x7A93F0
            s0 = addiu(s5, -27640);  // &0x7A9408
            s2 = s5;
            v0 = sll(v1, 10);
            sw(v1, s3, -27628);
            v0 = addiu(v0, 64);
            sw(v0, s0, 0);  // 0x7A9408
            a0 = v0;
            jal(ctx, 0x56015Cu, gen::fn_sceSifAllocIopHeap_0050b620);
            sw(v0, s4, 0);
            if (v0 == 0) {
                // 0x0056016c
                charge(ctx, 5);
                a0 = 0x7C0000;
                lw(a1, s0, 0);
                a0 = addiu(a0, 25896);  // "E02041101: Failed, sceSifAllocIopHeap(%d) in PS2RNA_Init."
                jal(ctx, 0x560174u, gen::fn_sub_541760_00541760);
                for (;;) {
                    // 0x00560180
                    charge(ctx, 7);
                    backedge(ctx);
                }
            }
            // 0x005601a0
            charge(ctx, 6);
            lw(a1, s2, -27640);
            a0 = addiu(s6, 25472);
            link(ctx, 0x5601A8u);  // $ra first: the delay slot below depends on it
            lw(a2, s1, -27636);
            call(ctx, gen::fn_sub_541760_00541760);
            lw(v0, s1, -27636);
        }
        // 0x005601c0
        charge(ctx, 17);
        v1 = si(-64);
        lw(a1, s3, -27628);
        t1 = 0x7B0000;
        v0 = addiu(v0, 63);
        a0 = 10;
        v0 = v0 & v1;
        lw(v1, s5, -27640);
        sw(a1, sp, 0x0);
        a1 = sp;
        a2 = 3;
        a3 = 0;
        t0 = 0;
        sw(v0, sp, 0x4);
        sw(v0, t1, -27632);  // 0x7A9410
        link(ctx, 0x5601F8u);  // $ra first: the delay slot below depends on it
        sw(v1, sp, 0x8);
        call(ctx, gen::fn_DTX_CallUrpc_00559c10);
        v1 = addiu(s7, -27588);
    }
    // 0x00560204
    charge(ctx, 4);
    lw(v0, v1, 0);
    v0 = addiu(v0, 1);
    sw(v0, v1, 0);
    ld(s0, sp, 0x10);
    // 0x00560214 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(s5, sp, 0x38);
    ld(s6, sp, 0x40);
    ld(s7, sp, 0x48);
    ld(ra, sp, 0x50);
    sp = addiu(sp, 0x60);
}

// 0x00564528 sub_564528 -- 408 bytes; frame 0x40: s5 sp+0x28, s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, ra sp+0x30
// PS2RNA: creates the DTX channel to the IOP sound server.
void sub_564528(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00564528
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s5, sp, 0x28);
    s5 = 0x7B0000;
    lw(v0, s5, 6844);  // 0x7B1ABC
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    sd(s4, sp, 0x20);
    sd(ra, sp, 0x30);
    if (v0 == 0) {
        // 0x00564554
        charge(ctx, 19);
        s0 = 0x7B0000;
        s4 = 0x7B0000;
        s0 = addiu(s0, 7512);  // &0x7B1D58
        a1 = 0;
        a0 = s0;
        s0 = addiu(s0, 64);  // &0x7B1D98
        a2 = 2256;
        s3 = addiu(s4, 6852);  // &0x7B1AC4
        jal(ctx, 0x564570u, gen::fn_memset_00521408);
        s2 = 0x7B0000;
        jal(ctx, 0x564578u, gen::fn_DTX_Init_00559aa8);
        v0 = si(-64);
        lw(v1, s3, 0);  // 0x7B1AC4
        a0 = 2176;
        s0 = s0 & v0;
        s1 = 0x7B0000;
        sw(a0, s2, 7508);  // 0x7B1D54
        sw(s0, s1, 6848);  // 0x7B1AC0
        if (v1 == 0) {
            // 0x005645a0
            charge(ctx, 4);
            a0 = 2256;
            jal(ctx, 0x5645A0u, gen::fn_sceSifAllocIopHeap_0050b620);
            sw(v0, s3, 0);
            if (v0 == 0) {
                // 0x005645b0
                charge(ctx, 4);
                a0 = 0x7C0000;
                a0 = addiu(a0, 27848);  // "E0100301: SJX_Init can't allocate IOP Heap\n"
                jal(ctx, 0x5645B4u, gen::fn_sub_541760_00541760);
                for (;;) {
                    // 0x005645c0
                    charge(ctx, 7);
                    backedge(ctx);
                }
            }
        }
        // 0x005645e0
        charge(ctx, 14);
        lw(v0, s4, 6852);
        v1 = si(-64);
        lw(a1, s1, 6848);
        t0 = 0x7B0000;
        v0 = addiu(v0, 64);
        lw(a3, s2, 7508);
        v0 = v0 & v1;
        a0 = 0;
        a2 = v0;
        sw(v0, t0, 6856);  // 0x7B1AC8
        s0 = 0x7B0000;
        jal(ctx, 0x564608u, gen::fn_sub_559718_00559718);
        sw(v0, s0, 7504);  // 0x7B1D50
        if (v0 == 0) {
            // 0x00564618
            charge(ctx, 4);
            a0 = 0x7C0000;
            a0 = addiu(a0, 27896);  // "E0100302: SJX_Init can't create DTX\n"
            jal(ctx, 0x56461Cu, gen::fn_sub_541760_00541760);
            for (;;) {
                // 0x00564628
                charge(ctx, 7);
                backedge(ctx);
            }
        }
        // 0x00564648
        charge(ctx, 17);
        s0 = addiu(s0, 7504);
        a1 = 0x560000;
        lw(a0, s0, 0);
        a1 = addiu(a1, 17248);  // &sub_564360
        a2 = 0;
        jal(ctx, 0x564658u, gen::fn_sub_559918_00559918);
        a1 = 0x560000;
        lw(a0, s0, 0);
        a1 = addiu(a1, 17408);  // &sub_564400
        a2 = 0;
        jal(ctx, 0x56466Cu, gen::fn_sub_559928_00559928);
        a0 = 3;
        a1 = 0;
        a2 = 0;
        a3 = 0;
        t0 = 0;
        jal(ctx, 0x564684u, gen::fn_DTX_CallUrpc_00559c10);
    }
    // 0x0056468c (the shared epilogue, written out on this path)
    charge(ctx, 13);
    v1 = addiu(s5, 6844);
    ld(s5, sp, 0x28);
    lw(v0, v1, 0);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    v0 = addiu(v0, 1);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x30);
    sw(v0, v1, 0);
    sp = addiu(sp, 0x40);
}

// 0x005658B8 RFHN_WaitCompleteReq -- 180 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// RFHN_WaitCompleteReq: waits until the ROFS handle's request completes (calls the server).
void RFHN_WaitCompleteReq(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005658b8
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = 1;
    sd(s2, sp, 0x10);
    s2 = 2;
    sd(s3, sp, 0x18);
    sd(ra, sp, 0x20);
    s3 = 3;
    jal(ctx, 0x5658DCu, gen::fn_sub_568A78_00568a78);
    for (;;) {
        // 0x005658e8
        charge(ctx, 14);
        lw(v0, s0, 8);
        lw(v1, v0, 56);
        lw(a0, v1, 24);
        jalr(ctx, 0x5658F4u, a0.u());
        jal(ctx, 0x5658FCu, gen::fn_ROFS_ExecServer_00566778);
        jal(ctx, 0x565904u, gen::fn_RFPFS_PfsWait_0056ab78);
        a0 = s0;
        jal(ctx, 0x56590Cu, gen::fn_RFHN_GetStatG_00565fe8);
        v1 = v0;
        v0 = 0;
        if (v1 != s1) {
            // 0x00565920
            charge(ctx, 2);
            v0 = si(-204);
            if (v1 != 0) {
                // 0x00565928
                charge(ctx, 2);
                if (v1 != s2) {
                    goto L_00565930_4;
                }
                lw(v0, s0, 28);
                // 0x00565940
                charge(ctx, 4);
                link(ctx, 0x565940u);  // $ra first: the delay slot below depends on it
                lw(a0, v0, 0);
                call(ctx, gen::fn_sub_568AC0_00568ac0);
                cc = v0 == s1;  // the condition, before the delay slot changes it
                v0 = si(-201);
                if (cc) {
                    backedge(ctx);
                    continue;
                }
            }
        }
        break;
    }
    // 0x00565950 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
    return;
L_00565930_4:
    charge(ctx, 2);
    v0 = si(-1000);
    if (v1 == s3) {
        // 0x00565938
        charge(ctx, 2);
        lh(v0, s0, 58);
    }
    // 0x00565950 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x005672C8 rfmai_addVolList -- 360 bytes; frame 0x40: s3 sp+0x18, s5 sp+0x28, s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s4 sp+0x20, ra sp+0x30
// rfmai_addVolList: adds a mounted volume to the ROFS volume list.
void rfmai_addVolList(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005672c8
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s3, sp, 0x18);
    s3 = a0;
    sd(s5, sp, 0x28);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(s4, sp, 0x20);
    sd(ra, sp, 0x30);
    s5 = a1;
    jal(ctx, 0x5672ECu, gen::fn_strlen_00524388);
    v1 = addiu(v0, -1);
    v1 = sltiu(v1, 8);
    v0 = 0;
    if (v1 != 0) {
        // 0x00567304
        charge(ctx, 12);
        v1 = 0x7B0000;
        a0 = s3;
        lw(v0, v1, 9984);  // g_rofs_work
        lw(s2, v0, 40);
        lw(s0, v0, 8);
        link(ctx, 0x567318u);  // $ra first: the delay slot below depends on it
        lw(s4, v0, 12);
        call(ctx, gen::fn_RFMAI_ToUpperStr_00569848);
        a0 = s3;
        a1 = 0;
        jal(ctx, 0x567324u, gen::fn_rfmai_getVolume_005671f0);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = 0;
        if (cc) {
            goto L_0056740c;
        }
        // 0x00567334
        charge(ctx, 4);
        s1 = 0;
        a0 = slt(s1, s0);
        if (a0 != 0) {
            // 0x00567344
            charge(ctx, 3);
            lb(v0, s2, 22);
            if (v0 != 0) {
                // 0x00567350
                charge(ctx, 2);
                v1 = addiu(s2, 22);
                s1 = addiu(s1, 1);
                for (;;) {
                    // 0x00567358
                    charge(ctx, 3);
                    a0 = slt(s1, s0);
                    v1 = addiu(v1, 52);
                    if (a0 == 0) {
                        goto L_005673fc;
                    }
                    // 0x00567364
                    charge(ctx, 6);
                    lb(v0, v1, 0);
                    if (v0 == 0) {
                        break;
                    }
                    s1 = addiu(s1, 1);
                    backedge(ctx);
                }
            }
            // 0x0056737c
            charge(ctx, 2);
            a1 = 0;
            if (a0 != 0) {
                // 0x00567384
                charge(ctx, 23);
                v0 = sll(s1, 1);
                v0 = addu(v0, s1);
                a2 = 52;
                v0 = sll(v0, 2);
                v0 = addu(v0, s1);
                v0 = sll(v0, 2);
                s0 = addu(v0, s2);
                a0 = s0;
                jal(ctx, 0x5673A0u, gen::fn_memset_00521408);
                a0 = addiu(s0, 22);
                a1 = s3;
                a2 = 8;
                jal(ctx, 0x5673B0u, gen::fn_strncpy_00524828);
                sw(s5, s0, 0);
                sw(zero, s0, 32);
                a0 = addiu(s0, 36);
                a1 = 0;
                a2 = 8;
                jal(ctx, 0x5673C8u, gen::fn_memset_00521408);
                a0 = s1;
                jal(ctx, 0x5673D0u, gen::fn_rfmai_getDirBufAdr_00567188);
                if (v0 != 0) {
                    // 0x005673e0
                    charge(ctx, 5);
                    a0 = v0;
                    a1 = s4;
                    jal(ctx, 0x5673E4u, gen::fn_RFHN_CreateDirhn_00565ac0);
                    sw(v0, s0, 16);
                    if (v0 == 0) {
                        goto L_005673f4;
                    }
                    // 0x00567408
                    charge(ctx, 1);
                    v0 = s0;
                    goto L_0056740c;
                }
            L_005673f4:
                charge(ctx, 2);
                a0 = s0;
                jal(ctx, 0x5673F4u, gen::fn_rfmai_delVolume_00567430);
                goto L_005673fc;
            }
        L_005673fc:
            charge(ctx, 2);
            v0 = 0;
            goto L_0056740c;
        }
        ld(s0, sp, 0x0);
        // 0x00567410 (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(s5, sp, 0x28);
        ld(ra, sp, 0x30);
        sp = addiu(sp, 0x40);
        return;
    }
L_0056740c:
    charge(ctx, 1);
    ld(s0, sp, 0x0);
    // 0x00567410 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x005674C0 rfmai_getCvmfInfo -- 264 bytes; frame 0x40: s0 sp+0x0, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s5 sp+0x28, s1 sp+0x8, ra sp+0x30
// rfmai_getCvmfInfo: reads the CVM file header and zone header of a volume.
void rfmai_getCvmfInfo(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005674c0
    enter(ctx, 26);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = 0x7B0000;
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s2, sp, 0x10);
    s2 = a0;
    sd(s3, sp, 0x18);
    s3 = a3;
    sd(s4, sp, 0x20);
    s4 = a2;
    sd(s5, sp, 0x28);
    s5 = 1;
    lw(v1, v0, 9984);  // g_rofs_work
    a1 = 0;
    sd(s1, sp, 0x8);
    a2 = 1;
    sd(ra, sp, 0x30);
    lw(s1, v1, 72);
    a3 = s1;
    jal(ctx, 0x567508u, gen::fn_RFMAI_ReadWG_00569538);
    a0 = s1;
    v1 = v0;
    v0 = si(-207);
    a1 = s0;
    if (v1 != 0) v0 = v1;
    if (v1 == s5) {
        // 0x00567528
        charge(ctx, 4);
        jal(ctx, 0x567528u, gen::fn_CVMH_AnalyCvmHdr_0056b240);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = si(-105);
        if (!cc) {
            // 0x00567538
            charge(ctx, 19);
            lw(v0, s0, 104);
            a2 = addiu(s2, 36);
            lw(v1, s0, 20);
            a0 = s1;
            v0 = sll(v0, 2);
            lw(a1, s3, 0);
            v0 = addu(v0, s0);
            lw(s0, v0, 112);
            link(ctx, 0x567558u);  // $ra first: the delay slot below depends on it
            sw(v1, s2, 32);
            call(ctx, gen::fn_RSU_GenerateFixedKey_0056d780);
            a0 = s2;
            a1 = s0;
            a2 = 1;
            a3 = s1;
            jal(ctx, 0x56756Cu, gen::fn_RFMAI_ReadWG_00569538);
            a0 = s1;
            v1 = v0;
            a1 = s4;
            if (v1 == s5) {
                // 0x00567590
                charge(ctx, 5);
                jal(ctx, 0x567590u, gen::fn_CVMH_AnalyZoneHdr_0056b300);
                v1 = si(-105);
                if (v0 == 0) v1 = 0;
                v0 = v1;
            } else {
                // 0x00567584
                charge(ctx, 3);
                v0 = si(-207);
                if (v1 != 0) v0 = v1;
            }
        }
    }
    // 0x005675a4 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x005676B0 rfmai_readPvd -- 156 bytes; frame 0x30: s1 sp+0x8, s3 sp+0x18, s0 sp+0x0, s2 sp+0x10, ra sp+0x20
// rfmai_readPvd: reads the ISO-9660 primary volume descriptor.
void rfmai_readPvd(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005676b0
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = 0x7B0000;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s3, sp, 0x18);
    s3 = addiu(v0, 9984);  // &g_rofs_work
    sd(s0, sp, 0x0);
    a2 = 1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x20);
    lw(v1, s3, 0);  // g_rofs_work
    lw(s2, a1, 32);
    lw(v0, s1, 4);
    lw(s0, v1, 72);
    v0 = subu(s2, v0);
    s2 = addiu(v0, 16);
    a3 = s0;
    a1 = s2;
    jal(ctx, 0x5676F4u, gen::fn_RFMAI_ReadWG_00569538);
    a0 = s1;
    v1 = 1;
    a1 = s0;
    a3 = s2;
    a2 = 1;
    if (v0 == v1) {
        // 0x00567720
        charge(ctx, 4);
        jal(ctx, 0x567720u, gen::fn_rfmai_decipherSectors_00569c00);
        lw(v1, s3, 0);
        lw(v0, v1, 72);
    } else {
        // 0x00567714
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x00567730 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00567AF0 sub_567AF0 -- 240 bytes; frame 0x20: s0 sp+0x0, s2 sp+0x10, s1 sp+0x8, ra sp+0x18
// RFMAI_InitG helper: clears the ROFS work area (g_rofs_work) and its volumes.
void sub_567AF0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00567af0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(s2, sp, 0x10);
    s2 = 0x7B0000;
    sd(s1, sp, 0x8);
    s0 = addiu(s2, 9984);  // &g_rofs_work
    sd(ra, sp, 0x18);
    lw(v1, s0, 0);  // g_rofs_work
    v0 = 1;
    if (v1 != 0) {
        // 0x00567b18
        charge(ctx, 3);
        lw(v1, v1, 0);
        if (v1 == v0) {
            // 0x00567b24
            charge(ctx, 6);
            s1 = 0;
            jal(ctx, 0x567B24u, gen::fn_sub_56D740_0056d740);
            lw(v0, s0, 0);
            lw(v1, v0, 4);
            s0 = addiu(v0, 4236);
            if (i64(v1) > 0) {
                // 0x00567b3c
                charge(ctx, 1);
                a0 = s0;
                for (;;) {
                    // 0x00567b40
                    charge(ctx, 8);
                    s0 = addiu(s0, 60);
                    jal(ctx, 0x567B40u, gen::fn_sub_565BC0_00565bc0);
                    lw(v1, s2, 9984);
                    s1 = addiu(s1, 1);
                    lw(v0, v1, 4);
                    v0 = slt(s1, v0);
                    a0 = s0;
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x00567b60
            charge(ctx, 5);
            lw(v0, s2, 9984);
            s1 = 0;
            lw(v1, v0, 8);
            lw(s0, v0, 40);
            if (i64(v1) > 0) {
                // 0x00567b74
                charge(ctx, 1);
                a0 = s0;
                for (;;) {
                    // 0x00567b78
                    charge(ctx, 8);
                    s0 = addiu(s0, 52);
                    jal(ctx, 0x567B78u, gen::fn_rfmai_delVolume_00567430);
                    lw(v1, s2, 9984);
                    s1 = addiu(s1, 1);
                    lw(v0, v1, 8);
                    v0 = slt(s1, v0);
                    a0 = s0;
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x00567b98
            charge(ctx, 12);
            s0 = addiu(s2, 9984);
            lw(v0, s0, 0);
            lw(v1, v0, 56);
            lw(a0, v1, 4);
            jalr(ctx, 0x567BA8u, a0.u());
            lw(a0, s0, 0);
            a1 = 0;
            sw(zero, a0, 0);
            link(ctx, 0x567BBCu);  // $ra first: the delay slot below depends on it
            lw(a2, a0, 16);
            call(ctx, gen::fn_memset_00521408);
            sw(zero, s0, 0);
            goto L_00567bc8;
        }
        ld(s0, sp, 0x0);
        // 0x00567bcc (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
L_00567bc8:
    charge(ctx, 1);
    ld(s0, sp, 0x0);
    // 0x00567bcc (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00567C58 RFMAI_MountG -- 1084 bytes; frame 0x20: s2 sp+0x10, s0 sp+0x0, s1 sp+0x8, ra sp+0x18
// RFMAI_MountG: mounts a CVM / ISO volume (header, PVD, root directory, volume list).
void RFMAI_MountG(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00567c58
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s2, sp, 0x10);
    s2 = a0;
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    s1 = a2;
    sd(ra, sp, 0x18);
    a1 = 963;
    if (s2 != 0) {
        // 0x00567c80
        charge(ctx, 2);
        if (s0 == 0) {
            a0 = 0x7C0000;
        L_00567c94:
            charge(ctx, 11);
            a2 = 0x7C0000;
            ld(s0, sp, 0x0);
            a0 = addiu(a0, 29352);
            ld(s1, sp, 0x8);
            a2 = addiu(a2, 29400);  // "RFMAI_MountG"
            ld(s2, sp, 0x10);
            a3 = 0;
            ld(ra, sp, 0x18);
            t0 = si(-100);
            sp = addiu(sp, 0x20);
            gen::fn_sub_569730_00569730(ctx);  // tail call
            return;
        }
        // 0x00567c88
        charge(ctx, 2);
        if (s1 == 0) {
            goto L_00567c90;
        }
        a1 = 0x7C0000;
        // 0x00567cc0
        charge(ctx, 10);
        a1 = addiu(a1, 29344);
        jal(ctx, 0x567CC0u, gen::fn_strcmp_00524128);
        a0 = 0x7C0000;
        a2 = 0x7C0000;
        a0 = addiu(a0, 29352);  // "../../rofs_mai.c"
        a2 = addiu(a2, 29400);  // "RFMAI_MountG"
        a1 = s0;
        a3 = 0;
        t0 = si(-103);
        if (v0 == 0) {
            // 0x00567ce8
            charge(ctx, 7);
            ld(s0, sp, 0x0);
            a1 = 967;
            ld(s1, sp, 0x8);
            ld(s2, sp, 0x10);
            ld(ra, sp, 0x18);
            sp = addiu(sp, 0x20);
            gen::fn_sub_569730_00569730(ctx);  // tail call
            return;
        }
        // 0x00567d08
        charge(ctx, 8);
        a0 = s2;
        ld(s2, sp, 0x10);
        a2 = s1;
        ld(s1, sp, 0x8);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        // 0x00567d28
        charge(ctx, 15);
        sp = addiu(sp, -0xFF0);
        sd(s3, sp, 0xFC8);
        s3 = a1;
        a1 = 0;
        sd(s0, sp, 0xFB0);
        sd(s5, sp, 0xFD8);
        s5 = a2;
        sd(s1, sp, 0xFB8);
        sd(s2, sp, 0xFC0);
        sd(s4, sp, 0xFD0);
        sd(ra, sp, 0xFE0);
        s0 = a0;
        jal(ctx, 0x567D54u, gen::fn_rfmai_getVolume_005671f0);
        a0 = 0x7C0000;
        if (v0 == 0) {
            // 0x00567d88
            charge(ctx, 6);
            a0 = s0;
            a1 = s3;
            jal(ctx, 0x567D8Cu, gen::fn_rfmai_addVolList_005672c8);
            s1 = v0;
            v0 = 0x7B0000;
            if (s1 == 0) {
                // 0x00567da0
                charge(ctx, 6);
                a0 = 0x7C0000;
                a2 = 0x7C0000;
                a0 = addiu(a0, 29352);  // "../../rofs_mai.c"
                a2 = addiu(a2, 29432);  // "addVolList"
                a1 = 997;
                goto L_00567fa4;
            }
            // 0x00567db8
            charge(ctx, 10);
            a1 = 0;
            lw(v1, v0, 9984);
            a2 = 0;
            a3 = 0;
            t0 = 0;
            link(ctx, 0x567DCCu);  // $ra first: the delay slot below depends on it
            lw(a0, v1, 32);
            call(ctx, gen::fn_RFHN_ReopenHn_00565a78);
            s2 = v0;
            a0 = s2;
            if (s2 != 0) {
                // 0x00567e10
                charge(ctx, 5);
                a1 = s3;
                jal(ctx, 0x567E10u, gen::fn_RFHN_IsUseImgHn_00565b18);
                s4 = 1;
                if (v0 != s4) {
                    // 0x00567e58
                    charge(ctx, 5);
                    jal(ctx, 0x567E58u, gen::fn_RFPFS_PfsLock_0056ab90);
                    s0 = v0;
                    if (s0 != 0) {
                        // 0x00567e6c
                        charge(ctx, 9);
                        a0 = s1;
                        jal(ctx, 0x567E6Cu, gen::fn_rfmai_delVolume_00567430);
                        a0 = 0x7C0000;
                        a2 = 0x7C0000;
                        a0 = addiu(a0, 29352);  // "../../rofs_mai.c"
                        a2 = addiu(a2, 29464);  // "mountVolume / lock"
                        t0 = s0;
                        a1 = 1024;
                        goto L_00567ef8;
                    }
                    // 0x00567e90
                    charge(ctx, 4);
                    a0 = s3;
                    jal(ctx, 0x567E90u, gen::fn_rfmai_isDvdRomAccess_00567478);
                    s3 = addiu(sp, 0x770);
                    if (v0 != s4) {
                        // 0x00567eb8
                        charge(ctx, 6);
                        a3 = s5;
                        a0 = s1;
                        a1 = sp;
                        a2 = s3;
                        jal(ctx, 0x567EC4u, gen::fn_rfmai_getCvmfInfo_005674c0);
                        s0 = v0;
                    } else {
                        // 0x00567ea0
                        charge(ctx, 5);
                        a0 = sp;
                        a1 = s3;
                        jal(ctx, 0x567EA4u, gen::fn_rfmai_setCvmfInfo_005675c8);
                        s0 = v0;
                    }
                    // 0x00567ed0
                    charge(ctx, 2);
                    a0 = s2;
                    if (s0 == 0) {
                        // 0x00567f08
                        charge(ctx, 12);
                        lw(v0, sp, 0x6C);
                        a1 = s3;
                        sw(v0, s1, 4);
                        ldl(v0, sp, 0xF);
                        ldr(v0, sp, 0x8);
                        sdl(v0, s1, 51);
                        sdr(v0, s1, 44);
                        a0 = s1;
                        jal(ctx, 0x567F24u, gen::fn_rfmai_readPvd_005676b0);
                        s0 = v0;
                        a0 = s2;
                        if (s0 != 0) {
                            // 0x00567f68
                            charge(ctx, 8);
                            a1 = 0;
                            jal(ctx, 0x567F68u, gen::fn_sub_568098_00568098);
                            a0 = s0;
                            jal(ctx, 0x567F70u, gen::fn_rfmai_checkMedia_00566f30);
                            s2 = v0;
                            v0 = 1;
                            s3 = addiu(sp, 0x7A0);
                            if (s2 == v0) {
                                // 0x00567fb8
                                charge(ctx, 14);
                                a1 = s0;
                                a0 = s3;
                                jal(ctx, 0x567FBCu, gen::fn_rfmai_copyStructCdVd_0056a0a8);
                                a0 = 0;
                                lw(v0, sp, 0x82C);
                                a1 = 0;
                                a2 = addiu(sp, 0xFA0);
                                sw(v0, s1, 8);
                                lw(v1, sp, 0x824);
                                link(ctx, 0x567FDCu);  // $ra first: the delay slot below depends on it
                                sw(v1, s1, 12);
                                call(ctx, gen::fn_sub_56A040_0056a040);
                                lw(v1, sp, 0xFA0);
                                v0 = 0;
                                if (v1 != s2) {
                                    // 0x00567ff0
                                    charge(ctx, 8);
                                    lw(a2, s1, 16);
                                    a1 = s3;
                                    a0 = s1;
                                    jal(ctx, 0x567FF8u, gen::fn_rfmai_readRootDirRec_00567750);
                                    v1 = si(-109);
                                    s0 = v0;
                                    if (s0 != v1) {
                                        // 0x00568040
                                        charge(ctx, 2);
                                        if (s0 != 0) {
                                            // 0x00568048
                                            charge(ctx, 10);
                                            a0 = s1;
                                            jal(ctx, 0x568048u, gen::fn_rfmai_delVolume_00567430);
                                            a0 = 0x7C0000;
                                            a2 = 0x7C0000;
                                            a0 = addiu(a0, 29352);  // "../../rofs_mai.c"
                                            a2 = addiu(a2, 29528);  // "readRootDirRec"
                                            t0 = s0;
                                            a1 = 1119;
                                            a3 = 0;
                                            jal(ctx, 0x568068u, gen::fn_sub_569730_00569730);
                                            goto L_00568070;
                                        }
                                        ld(s0, sp, 0xFB0);
                                    } else {
                                        // 0x00568010
                                        charge(ctx, 12);
                                        a0 = s1;
                                        jal(ctx, 0x568010u, gen::fn_rfmai_delVolume_00567430);
                                        a0 = 0x7C0000;
                                        a2 = 0x7C0000;
                                        a0 = addiu(a0, 29352);  // "../../rofs_mai.c"
                                        a2 = addiu(a2, 29528);  // "readRootDirRec"
                                        a1 = 1115;
                                        a3 = 0;
                                        t0 = si(-109);
                                        jal(ctx, 0x568030u, gen::fn_sub_569730_00569730);
                                        ld(s0, sp, 0xFB0);
                                    }
                                    // 0x00568074 (the shared epilogue, written out on this path)
                                    charge(ctx, 8);
                                    ld(s1, sp, 0xFB8);
                                    ld(s2, sp, 0xFC0);
                                    ld(s3, sp, 0xFC8);
                                    ld(s4, sp, 0xFD0);
                                    ld(s5, sp, 0xFD8);
                                    ld(ra, sp, 0xFE0);
                                    sp = addiu(sp, 0xFF0);
                                    return;
                                }
                            L_00568070:
                                charge(ctx, 1);
                                ld(s0, sp, 0xFB0);
                            } else {
                                // 0x00567f88
                                charge(ctx, 7);
                                a0 = s1;
                                jal(ctx, 0x567F88u, gen::fn_rfmai_delVolume_00567430);
                                a0 = 0x7C0000;
                                a2 = 0x7C0000;
                                a0 = addiu(a0, 29352);  // "../../rofs_mai.c"
                                a2 = addiu(a2, 29512);  // "checkMedia"
                                a1 = 1076;
                            L_00567fa4:
                                charge(ctx, 5);
                                a3 = 0;
                                t0 = si(-105);
                                jal(ctx, 0x567FA8u, gen::fn_sub_569730_00569730);
                                ld(s0, sp, 0xFB0);
                            }
                        } else {
                            // 0x00567f38
                            charge(ctx, 12);
                            a1 = s1;
                            jal(ctx, 0x567F38u, gen::fn_sub_568098_00568098);
                            a0 = 0x7C0000;
                            a2 = 0x7C0000;
                            a0 = addiu(a0, 29352);  // "../../rofs_mai.c"
                            a2 = addiu(a2, 29504);  // "readPvd"
                            a1 = 1063;
                            a3 = 0;
                            t0 = si(-207);
                            jal(ctx, 0x567F58u, gen::fn_sub_569730_00569730);
                            ld(s0, sp, 0xFB0);
                        }
                    } else {
                        // 0x00567ed8
                        charge(ctx, 8);
                        a1 = s1;
                        jal(ctx, 0x567ED8u, gen::fn_sub_568098_00568098);
                        a0 = 0x7C0000;
                        a2 = 0x7C0000;
                        a0 = addiu(a0, 29352);  // "../../rofs_mai.c"
                        a2 = addiu(a2, 29488);  // "getCvmfInfo"
                        t0 = s0;
                        a1 = 1044;
                    L_00567ef8:
                        charge(ctx, 4);
                        a3 = 0;
                        jal(ctx, 0x567EF8u, gen::fn_sub_569730_00569730);
                        ld(s0, sp, 0xFB0);
                    }
                } else {
                    // 0x00567e24
                    charge(ctx, 12);
                    a0 = s1;
                    jal(ctx, 0x567E24u, gen::fn_rfmai_delVolume_00567430);
                    a0 = 0x7C0000;
                    a2 = 0x7C0000;
                    a0 = addiu(a0, 29352);  // "../../rofs_mai.c"
                    a2 = addiu(a2, 29416);  // "mountVolume"
                    a1 = 1015;
                    a3 = 0;
                    t0 = si(-200);
                    jal(ctx, 0x567E44u, gen::fn_sub_569730_00569730);
                    ld(s0, sp, 0xFB0);
                }
            } else {
                // 0x00567de0
                charge(ctx, 12);
                a0 = s1;
                jal(ctx, 0x567DE0u, gen::fn_rfmai_delVolume_00567430);
                a0 = 0x7C0000;
                a2 = 0x7C0000;
                a0 = addiu(a0, 29352);  // "../../rofs_mai.c"
                a2 = addiu(a2, 29448);  // "RFHN_ReopenHn"
                a1 = 1009;
                a3 = 0;
                t0 = si(-206);
                jal(ctx, 0x567E00u, gen::fn_sub_569730_00569730);
                ld(s0, sp, 0xFB0);
            }
        } else {
            // 0x00567d64
            charge(ctx, 9);
            a2 = 0x7C0000;
            a0 = addiu(a0, 29352);
            a2 = addiu(a2, 29416);  // "mountVolume"
            a1 = 990;
            a3 = 0;
            t0 = si(-104);
            jal(ctx, 0x567D78u, gen::fn_sub_569730_00569730);
            ld(s0, sp, 0xFB0);
        }
        // 0x00568074 (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(s1, sp, 0xFB8);
        ld(s2, sp, 0xFC0);
        ld(s3, sp, 0xFC8);
        ld(s4, sp, 0xFD0);
        ld(s5, sp, 0xFD8);
        ld(ra, sp, 0xFE0);
        sp = addiu(sp, 0xFF0);
        return;
    }
L_00567c90:
    charge(ctx, 1);
    a0 = 0x7C0000;
    goto L_00567c94;
}

// 0x00568098 sub_568098 -- 64 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// RFMAI_MountG cleanup: deletes the half-mounted volume and its handle.
void sub_568098(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00568098
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    a0 = a1;
    if (a1 != 0) {
        // 0x005680b0
        charge(ctx, 2);
        jal(ctx, 0x5680B0u, gen::fn_rfmai_delVolume_00567430);
    }
    // 0x005680b8
    charge(ctx, 2);
    if (s0 == 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x005680c0
        charge(ctx, 3);
        a0 = s0;
        jal(ctx, 0x5680C0u, gen::fn_sub_565BC0_00565bc0);
        ld(s0, sp, 0x0);
    }
    // 0x005680cc
    charge(ctx, 3);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_56ABE0_0056abe0(ctx);  // tail call
}

// 0x00568280 RFMAI_SetDefVolumeG -- 228 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// RFMAI_SetDefVolumeG: selects the default volume by name.
void RFMAI_SetDefVolumeG(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00568280
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    if (s0 == 0) {
        // 0x00568294
        charge(ctx, 11);
        a0 = 0x7C0000;
        a2 = 0x7C0000;
        ld(s0, sp, 0x0);
        a0 = addiu(a0, 29352);  // "../../rofs_mai.c"
        ld(ra, sp, 0x8);
        a2 = addiu(a2, 29576);  // "RFMAI_SetDefVolumeG"
        a1 = 1203;
        a3 = 0;
        t0 = si(-100);
        sp = addiu(sp, 0x10);
        gen::fn_sub_569730_00569730(ctx);  // tail call
        return;
    }
    // 0x005682c0
    charge(ctx, 10);
    a1 = 0x7C0000;
    a1 = addiu(a1, 29344);  // "ROFS"
    jal(ctx, 0x5682C4u, gen::fn_strcmp_00524128);
    a2 = 0x7C0000;
    a0 = s0;
    a2 = addiu(a2, 29576);  // "RFMAI_SetDefVolumeG"
    a1 = 0;
    a3 = 0;
    t0 = si(-103);
    if (v0 == 0) {
        // 0x005682e8
        charge(ctx, 7);
        a0 = 0x7C0000;
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        a0 = addiu(a0, 29352);  // "../../rofs_mai.c"
        a1 = 1208;
        sp = addiu(sp, 0x10);
        gen::fn_sub_569730_00569730(ctx);  // tail call
        return;
    }
    // 0x00568308
    charge(ctx, 12);
    jal(ctx, 0x568308u, gen::fn_rfmai_getVolume_005671f0);
    a0 = 0x7C0000;
    t1 = v0;
    v0 = 0;
    a2 = 0x7C0000;
    a3 = 0;
    a2 = addiu(a2, 29560);  // "getVolume"
    a0 = addiu(a0, 29352);  // "../../rofs_mai.c"
    t0 = si(-103);
    a1 = 1214;
    if (t1 == 0) {
        // 0x00568338
        charge(ctx, 4);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        gen::fn_sub_569730_00569730(ctx);  // tail call
        return;
    }
    // 0x00568348
    charge(ctx, 7);
    v1 = 0x7B0000;
    ld(s0, sp, 0x0);
    lw(a0, v1, 9984);  // g_rofs_work
    ld(ra, sp, 0x8);
    sw(t1, a0, 44);
    sp = addiu(sp, 0x10);
}

// 0x00568388 RFMAI_OpenG -- 556 bytes; frame 0x70: s2 sp+0x40, s4 sp+0x50, s0 sp+0x30, s1 sp+0x38, s3 sp+0x48, s5 sp+0x58, ra sp+0x60
// RFMAI_OpenG: opens a file of a volume (path lookup, handle).
void RFMAI_OpenG(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00568388
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    a2 = 9;
    sd(s2, sp, 0x40);
    s2 = addiu(sp, 0x10);
    sd(s4, sp, 0x50);
    s4 = a0;
    sd(s0, sp, 0x30);
    s0 = a1;
    a0 = sp;
    a3 = 32;
    a1 = s2;
    sd(s1, sp, 0x38);
    sd(s3, sp, 0x48);
    sd(s5, sp, 0x58);
    sd(ra, sp, 0x60);
    t0 = s4;
    jal(ctx, 0x5683C4u, gen::fn_rfmai_divideFname_00566f78);
    if (v0 == 0) {
        // 0x005683d4
        charge(ctx, 8);
        a0 = 0x7C0000;
        a2 = 0x7C0000;
        a0 = addiu(a0, 29352);  // "../../rofs_mai.c"
        a2 = addiu(a2, 29600);  // "divideFname"
        a1 = 1247;
        a3 = 0;
        t0 = si(-100);
        goto L_00568584;
    }
    a0 = sp;
    // 0x005683f8
    charge(ctx, 5);
    a1 = 0;
    jal(ctx, 0x5683F8u, gen::fn_rfmai_getVolume_005671f0);
    s3 = v0;
    a0 = 0x7C0000;
    if (s3 == 0) {
        // 0x0056840c
        charge(ctx, 7);
        a2 = 0x7C0000;
        a0 = addiu(a0, 29352);
        a2 = addiu(a2, 29560);  // "getVolume"
        a1 = 1253;
        a3 = 0;
        t0 = si(-105);
        goto L_00568584;
    }
    // 0x00568428
    charge(ctx, 2);
    a0 = 0x7C0000;
    if (s0 == 0) {
        // 0x00568430
        charge(ctx, 2);
        lw(s0, s3, 16);
        goto L_00568480;
    }
    // 0x00568438
    charge(ctx, 6);
    s1 = addiu(s0, 12);
    a0 = addiu(a0, 29616);
    a1 = s1;
    jal(ctx, 0x568440u, gen::fn_strcmp_00524128);
    a1 = s1;
    if (v0 != 0) {
        // 0x00568450
        charge(ctx, 4);
        a0 = addiu(s3, 22);
        jal(ctx, 0x568450u, gen::fn_strcmp_00524128);
        a0 = 0x7C0000;
        if (v0 == 0) {
            goto L_00568480;
        }
        // 0x00568460
        charge(ctx, 7);
        a2 = 0x7C0000;
        a0 = addiu(a0, 29352);
        a2 = addiu(a2, 29632);  // "dir_buf"
        a1 = 1268;
        a3 = 0;
        t0 = si(-108);
        goto L_00568584;
    }
L_00568480:
    charge(ctx, 7);
    a0 = s2;
    a1 = s0;
    a2 = s3;
    jal(ctx, 0x568488u, gen::fn_RFDIR_SearchName_0056c5b0);
    s2 = v0;
    if (s2 == 0) {
        // 0x0056849c
        charge(ctx, 8);
        a0 = 0x7C0000;
        a2 = 0x7C0000;
        a0 = addiu(a0, 29352);  // "../../rofs_mai.c"
        a2 = addiu(a2, 29640);  // "RFDIR_SearchName"
        a3 = s4;
        a1 = 1278;
        t0 = si(-107);
        goto L_00568584;
    }
    a2 = 0x7B0000;
    // 0x005684c0
    charge(ctx, 6);
    a0 = 0;
    lw(v1, a2, 9984);
    lw(v0, v1, 4);
    v0 = addiu(v0, -1);
    lw(s1, v1, 36);
    if (i64(v0) > 0) {
        // 0x005684d8
        charge(ctx, 6);
        v0 = sll(s2, 1);
        s5 = 0x7C0000;
        v0 = addu(v0, s2);
        s4 = 0x7C0000;
        a1 = sll(v0, 4);
        for (;;) {
            // 0x005684f0
            charge(ctx, 3);
            lh(v0, s1, 52);
            if (v0 == 0) {
                goto L_005684fc_14;
            }
            lw(v1, a2, 9984);
            // 0x00568550
            charge(ctx, 6);
            a0 = addiu(a0, 1);
            lw(v0, v1, 4);
            v0 = addiu(v0, -1);
            v0 = slt(a0, v0);
            s1 = addiu(s1, 60);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00568568
    charge(ctx, 7);
    a0 = 0x7C0000;
    a2 = 0x7C0000;
    a0 = addiu(a0, 29352);  // "../../rofs_mai.c"
    a2 = addiu(a2, 29680);  // "RFMAI_OpenG"
    a1 = 1308;
    a3 = 0;
    t0 = si(-102);
L_00568584:
    charge(ctx, 3);
    jal(ctx, 0x568584u, gen::fn_sub_569730_00569730);
    v0 = 0;
    // 0x00568590 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(s0, sp, 0x30);
    ld(s1, sp, 0x38);
    ld(s2, sp, 0x40);
    ld(s3, sp, 0x48);
    ld(s4, sp, 0x50);
    ld(s5, sp, 0x58);
    ld(ra, sp, 0x60);
    sp = addiu(sp, 0x70);
    return;
L_005684fc_14:
    charge(ctx, 13);
    s0 = addu(s0, a1);
    s0 = addiu(s0, -24);
    lw(a0, s0, 4);
    link(ctx, 0x568508u);  // $ra first: the delay slot below depends on it
    lw(a1, s0, 0);
    call(ctx, gen::fn_sub_569BD0_00569bd0);
    a0 = s1;
    lw(a2, s0, 8);
    a1 = s2;
    a3 = v0;
    t0 = s3;
    jal(ctx, 0x568520u, gen::fn_RFHN_CreateHnG_00565a20);
    v0 = s1;
    if (s1 == 0) {
        // 0x00568530
        charge(ctx, 8);
        a0 = addiu(s5, 29352);
        a2 = addiu(s4, 29664);
        a1 = 1301;
        a3 = 0;
        t0 = si(-102);
        jal(ctx, 0x568540u, gen::fn_sub_569730_00569730);
        v0 = s1;
    }
    // 0x00568590 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(s0, sp, 0x30);
    ld(s1, sp, 0x38);
    ld(s2, sp, 0x40);
    ld(s3, sp, 0x48);
    ld(s4, sp, 0x50);
    ld(s5, sp, 0x58);
    ld(ra, sp, 0x60);
    sp = addiu(sp, 0x70);
}

// 0x00568938 RFMAI_ExecServerG -- 316 bytes; frame 0x30: s2 sp+0x10, s0 sp+0x0, s1 sp+0x8, s3 sp+0x18, s4 sp+0x20, ra sp+0x28
// RFMAI_ExecServerG: runs the ROFS server for every open handle.
void RFMAI_ExecServerG(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00568938
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s2, sp, 0x10);
    s2 = 0x7B0000;
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(s3, sp, 0x18);
    sd(s4, sp, 0x20);
    sd(ra, sp, 0x28);
    s0 = addiu(s2, 9984);  // &g_rofs_work
    jal(ctx, 0x568958u, gen::fn_sub_56ABF8_0056abf8);
    lw(v0, s0, 0);  // g_rofs_work
    if (v0 == 0) {
        // 0x0056896c
        charge(ctx, 8);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(ra, sp, 0x28);
        sp = addiu(sp, 0x30);
        gen::fn_sub_56AC10_0056ac10(ctx);  // tail call
        return;
    }
    lw(v0, v0, 0);
    // 0x00568990
    charge(ctx, 2);
    s4 = 0x7B0000;
    if (v0 == 0) {
        // 0x00568998
        charge(ctx, 8);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(ra, sp, 0x28);
        sp = addiu(sp, 0x30);
        gen::fn_sub_56AC10_0056ac10(ctx);  // tail call
        return;
    }
    // 0x005689b8
    charge(ctx, 4);
    v1 = addiu(s4, 9992);
    lw(v0, v1, 0);
    ld(s1, sp, 0x8);
    if (v0 != 0) {
        // 0x005689c8
        charge(ctx, 7);
        ld(s0, sp, 0x0);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(ra, sp, 0x28);
        sp = addiu(sp, 0x30);
        gen::fn_sub_56AC10_0056ac10(ctx);  // tail call
        return;
    }
    // 0x005689e8
    charge(ctx, 8);
    v0 = 1;
    s1 = 0;
    link(ctx, 0x5689F0u);  // $ra first: the delay slot below depends on it
    sw(v0, v1, 0);
    call(ctx, gen::fn_sub_56AC10_0056ac10);
    lw(v0, s0, 0);
    lw(v1, v0, 4);
    s0 = addiu(v0, 4236);
    if (i64(v1) > 0) {
        // 0x00568a08
        charge(ctx, 2);
        s3 = 1;
        for (;;) {
            // 0x00568a10
            charge(ctx, 3);
            lh(v0, s0, 54);
            lw(v1, s2, 9984);
            if (v0 == s3) {
                // 0x00568a1c
                charge(ctx, 3);
                a0 = s0;
                jal(ctx, 0x568A1Cu, gen::fn_rfmai_updateHnStat_00568710);
                lw(v1, s2, 9984);
            }
            // 0x00568a28
            charge(ctx, 5);
            s1 = addiu(s1, 1);
            lw(v0, v1, 4);
            v0 = slt(s1, v0);
            s0 = addiu(s0, 60);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00568a3c (the shared epilogue, written out on this path)
    charge(ctx, 14);
    lw(v0, s2, 9984);
    a0 = addiu(s4, 9992);
    ld(s0, sp, 0x0);
    lw(v1, v0, 20);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    v1 = addiu(v1, 1);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sw(v1, v0, 20);
    sw(zero, a0, 0);
    sp = addiu(sp, 0x30);
}

// 0x00568BC8 sub_568BC8 -- 76 bytes; frame 0x20: ra sp+0x10
// Looks up a file name in a directory record (rfmai_getEntryFromFname).
void sub_568BC8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00568bc8
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    a2 = sp;
    jal(ctx, 0x568BD0u, gen::fn_rfmai_getEntryFromFname_00568c18);
    a0 = v0;
    if (v0 == 0) {
        // 0x00568be0
        charge(ctx, 9);
        lw(v0, sp, 0x0);
        lw(a0, v0, 4);
        link(ctx, 0x568BE8u);  // $ra first: the delay slot below depends on it
        lw(a1, v0, 0);
        call(ctx, gen::fn_sub_569BD0_00569bd0);
        v1 = si(-1);
        v1 = dsrl(v1, 1);
        a0 = v0;
        v0 = slti(a0, 0);
        if (v0 != 0) a0 = v1;
    }
    // 0x00568c04 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    v0 = a0;
    sp = addiu(sp, 0x20);
}

// 0x00568C18 rfmai_getEntryFromFname -- 404 bytes; frame 0x70: s3 sp+0x48, s4 sp+0x50, s2 sp+0x40, s5 sp+0x58, s0 sp+0x30, s1 sp+0x38, ra sp+0x60
// rfmai_getEntryFromFname: finds a directory entry by name.
void rfmai_getEntryFromFname(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00568c18
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    a3 = 32;
    sd(s3, sp, 0x48);
    s3 = a0;
    sd(s4, sp, 0x50);
    s4 = addiu(sp, 0x10);
    sd(s2, sp, 0x40);
    s2 = a1;
    sd(s5, sp, 0x58);
    s5 = a2;
    a0 = sp;
    a1 = s4;
    a2 = 9;
    sd(s0, sp, 0x30);
    sd(s1, sp, 0x38);
    sd(ra, sp, 0x60);
    t0 = s3;
    jal(ctx, 0x568C58u, gen::fn_rfmai_divideFname_00566f78);
    a0 = sp;
    if (v0 != 0) {
        // 0x00568c90
        charge(ctx, 5);
        a1 = 0;
        jal(ctx, 0x568C90u, gen::fn_rfmai_getVolume_005671f0);
        s1 = v0;
        a0 = 0x7C0000;
        if (s1 != 0) {
            // 0x00568cc8
            charge(ctx, 2);
            a0 = 0x7C0000;
            if (s2 == 0) {
                // 0x00568cd0
                charge(ctx, 2);
                lw(s0, s1, 16);
                goto L_00568d2c;
            }
            // 0x00568cd8
            charge(ctx, 6);
            s0 = addiu(s2, 12);
            a0 = addiu(a0, 29616);
            a1 = s0;
            jal(ctx, 0x568CE0u, gen::fn_strcmp_00524128);
            if (v0 == 0) {
                s0 = s2;
            L_00568d2c:
                charge(ctx, 7);
                a0 = s4;
                a2 = s1;
                a1 = s0;
                jal(ctx, 0x568D34u, gen::fn_RFDIR_SearchName_0056c5b0);
                a0 = v0;
                v1 = sll(a0, 1);
                if (a0 != 0) {
                    // 0x00568d70
                    charge(ctx, 7);
                    v0 = 0;
                    v1 = addu(v1, a0);
                    v1 = sll(v1, 4);
                    v1 = addu(s0, v1);
                    v1 = addiu(v1, -24);
                    sw(v1, s5, 0);
                    ld(s0, sp, 0x30);
                } else {
                    // 0x00568d48
                    charge(ctx, 10);
                    a0 = 0x7C0000;
                    a2 = 0x7C0000;
                    a0 = addiu(a0, 29352);  // "../../rofs_mai.c"
                    a2 = addiu(a2, 29640);  // "RFDIR_SearchName"
                    a3 = s3;
                    a1 = 1696;
                    t0 = si(-107);
                    jal(ctx, 0x568D60u, gen::fn_sub_569730_00569730);
                    ld(s0, sp, 0x30);
                }
            } else {
                // 0x00568cf0
                charge(ctx, 5);
                a1 = s0;
                a0 = addiu(s1, 22);
                jal(ctx, 0x568CF4u, gen::fn_strcmp_00524128);
                a0 = 0x7C0000;
                if (v0 == 0) {
                    // 0x00568d28
                    charge(ctx, 1);
                    s0 = s2;
                    goto L_00568d2c;
                }
                // 0x00568d04
                charge(ctx, 9);
                a2 = 0x7C0000;
                a0 = addiu(a0, 29352);
                a2 = addiu(a2, 29752);  // "RFMAI_GetFileSiz"
                a1 = 1685;
                a3 = 0;
                t0 = si(-108);
                jal(ctx, 0x568D18u, gen::fn_sub_569730_00569730);
                ld(s0, sp, 0x30);
            }
        } else {
            // 0x00568ca4
            charge(ctx, 9);
            a2 = 0x7C0000;
            a0 = addiu(a0, 29352);
            a2 = addiu(a2, 29560);  // "getVolume"
            a1 = 1673;
            a3 = 0;
            t0 = si(-105);
            jal(ctx, 0x568CB8u, gen::fn_sub_569730_00569730);
            ld(s0, sp, 0x30);
        }
    } else {
        // 0x00568c68
        charge(ctx, 10);
        a0 = 0x7C0000;
        a2 = 0x7C0000;
        a0 = addiu(a0, 29352);  // "../../rofs_mai.c"
        a2 = addiu(a2, 29600);  // "divideFname"
        a1 = 1668;
        a3 = 0;
        t0 = si(-100);
        jal(ctx, 0x568C80u, gen::fn_sub_569730_00569730);
        ld(s0, sp, 0x30);
    }
    // 0x00568d8c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s1, sp, 0x38);
    ld(s2, sp, 0x40);
    ld(s3, sp, 0x48);
    ld(s4, sp, 0x50);
    ld(s5, sp, 0x58);
    ld(ra, sp, 0x60);
    sp = addiu(sp, 0x70);
}

// 0x00568DB0 sub_568DB0 -- 132 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// ROFS: returns a volume's name pointer (+22) and first word; -105 when the volume is absent, the rofs_mai.c error
// report (line 1713) on a null output pointer.
void sub_568DB0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00568db0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(ra, sp, 0x8);
    a1 = 1713;
    if (s0 == 0) {
        // 0x00568dc8
        charge(ctx, 10);
        a0 = 0x7C0000;
        a2 = 0x7C0000;
        ld(s0, sp, 0x0);
        a0 = addiu(a0, 29352);  // "../../rofs_mai.c"
        ld(ra, sp, 0x8);
        a2 = addiu(a2, 29776);  // "RFMAI_GetVolumeInfG"
        a3 = 0;
        t0 = si(-100);
        sp = addiu(sp, 0x10);
        gen::fn_sub_569730_00569730(ctx);  // tail call
        return;
    }
    // 0x00568df0
    charge(ctx, 6);
    a1 = 1;
    jal(ctx, 0x568DF0u, gen::fn_rfmai_getVolume_005671f0);
    v1 = v0;
    v0 = 0;
    a0 = addiu(v1, 22);
    if (v1 != 0) {
        // 0x00568e18
        charge(ctx, 3);
        lw(v1, v1, 0);
        sw(a0, s0, 0);
        sw(v1, s0, 4);
    } else {
        // 0x00568e08
        charge(ctx, 4);
        sw(zero, s0, 4);
        v0 = si(-105);
        sw(zero, s0, 0);
    }
    // 0x00568e24 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00569058 RFMAI_SetDirG -- 472 bytes; frame 0x30: s2 sp+0x20, s0 sp+0x10, s1 sp+0x18, ra sp+0x28
// RFMAI_SetDirG: changes the current directory of a volume.
void RFMAI_SetDirG(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00569058
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s2, sp, 0x20);
    s2 = a1;
    sd(s0, sp, 0x10);
    sd(s1, sp, 0x18);
    sd(ra, sp, 0x28);
    if (s2 != 0) {
        // 0x005690a0
        charge(ctx, 5);
        a1 = 1;
        jal(ctx, 0x5690A0u, gen::fn_rfmai_getVolume_005671f0);
        s1 = v0;
        a0 = 0;
        if (s1 != 0) {
            // 0x005690e0
            charge(ctx, 7);
            a1 = 0;
            a2 = sp;
            jal(ctx, 0x5690E4u, gen::fn_sub_56A040_0056a040);
            v1 = 1;
            lw(v0, sp, 0x0);
            a0 = 0x7C0000;
            if (v0 == v1) {
                // 0x005690fc
                charge(ctx, 3);
                sw(s2, s1, 16);
                v0 = 0;
                goto L_00569218;
            }
            // 0x00569108
            charge(ctx, 6);
            s0 = addiu(s2, 12);
            a0 = addiu(a0, 29616);
            a1 = s0;
            jal(ctx, 0x569110u, gen::fn_strcmp_00524128);
            a1 = s0;
            if (v0 != 0) {
                // 0x00569120
                charge(ctx, 4);
                a0 = addiu(s1, 22);
                jal(ctx, 0x569120u, gen::fn_strcmp_00524128);
                a0 = 0x7C0000;
                if (v0 == 0) {
                    goto L_00569158;
                }
                // 0x00569130
                charge(ctx, 9);
                a2 = 0x7C0000;
                a0 = addiu(a0, 29352);
                a2 = addiu(a2, 29632);  // "dir_buf"
                a1 = 1853;
                a3 = 0;
                t0 = si(-108);
                jal(ctx, 0x569144u, gen::fn_sub_569730_00569730);
                ld(s0, sp, 0x10);
                // 0x0056921c (the shared epilogue, written out on this path)
                charge(ctx, 5);
                ld(s1, sp, 0x18);
                ld(s2, sp, 0x20);
                ld(ra, sp, 0x28);
                sp = addiu(sp, 0x30);
                return;
            }
        L_00569158:
            charge(ctx, 12);
            lw(a0, s1, 16);
            t1 = addiu(s2, 24);
            lw(t2, s2, 0);
            t0 = 0;
            lw(a1, a0, 4);
            a2 = addiu(a0, 24);
            a3 = t2;
            lw(v1, s2, 8);
            v0 = slt(t2, a1);
            if (v0 == 0) a3 = a1;
            sw(v1, a0, 8);
            if (i64(a3) > 0) {
                // 0x00569188
                charge(ctx, 2);
                t0 = a3;
                for (;;) {
                    // 0x00569190
                    charge(ctx, 29);
                    ldl(v0, t1, 7);
                    ldr(v0, t1, 0);
                    ldl(v1, t1, 15);
                    ldr(v1, t1, 8);
                    ldl(t3, t1, 23);
                    ldr(t3, t1, 16);
                    ldl(t4, t1, 31);
                    ldr(t4, t1, 24);
                    sdl(v0, a2, 7);
                    sdr(v0, a2, 0);
                    sdl(v1, a2, 15);
                    sdr(v1, a2, 8);
                    sdl(t3, a2, 23);
                    sdr(t3, a2, 16);
                    sdl(t4, a2, 31);
                    sdr(t4, a2, 24);
                    ldl(v0, t1, 39);
                    ldr(v0, t1, 32);
                    ldl(v1, t1, 47);
                    ldr(v1, t1, 40);
                    sdl(v0, a2, 39);
                    sdr(v0, a2, 32);
                    sdl(v1, a2, 47);
                    t0 = addiu(t0, -1);
                    sdr(v1, a2, 40);
                    a2 = addiu(a2, 48);
                    t1 = addiu(t1, 48);
                    if (t0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00569204
                charge(ctx, 1);
                t0 = a3;
            }
            // 0x00569208
            charge(ctx, 4);
            v1 = slt(a1, t2);
            v0 = si(-109);
            sw(t0, a0, 0);
            if (v1 == 0) v0 = 0;
        L_00569218:
            charge(ctx, 1);
            ld(s0, sp, 0x10);
        } else {
            // 0x005690b4
            charge(ctx, 10);
            a0 = 0x7C0000;
            a2 = 0x7C0000;
            a0 = addiu(a0, 29352);  // "../../rofs_mai.c"
            a2 = addiu(a2, 29560);  // "getVolume"
            a1 = 1837;
            a3 = 0;
            t0 = si(-105);
            jal(ctx, 0x5690CCu, gen::fn_sub_569730_00569730);
            ld(s0, sp, 0x10);
        }
    } else {
        // 0x00569074
        charge(ctx, 10);
        a0 = 0x7C0000;
        a2 = 0x7C0000;
        a0 = addiu(a0, 29352);  // "../../rofs_mai.c"
        a2 = addiu(a2, 29632);  // "dir_buf"
        a1 = 1831;
        a3 = 0;
        t0 = si(-100);
        jal(ctx, 0x56908Cu, gen::fn_sub_569730_00569730);
        ld(s0, sp, 0x10);
    }
    // 0x0056921c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x0056C0F8 RFDIR_GetDirEnt -- 144 bytes; frame 0x40: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s5 sp+0x28, ra sp+0x30
// RFDIR_GetDirEnt: reads the next directory entry.
void RFDIR_GetDirEnt(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056c0f8
    enter(ctx, 21);  // entry check point + this block's cycles
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
    sd(s5, sp, 0x28);
    sd(ra, sp, 0x30);
    s4 = t0;
    jal(ctx, 0x56C128u, gen::fn_RFPFS_PfsLock_0056ab90);
    s5 = v0;
    a0 = s0;
    a1 = s1;
    a2 = s2;
    a3 = s3;
    t0 = s4;
    if (s5 == 0) {
        // 0x0056c14c
        charge(ctx, 3);
        jal(ctx, 0x56C14Cu, gen::fn_rfdir_getDirEnt_0056bdc0);
        s5 = v0;
    }
    // 0x0056c158
    charge(ctx, 12);
    jal(ctx, 0x56C158u, gen::fn_sub_56ABE0_0056abe0);
    v0 = s5;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x0056C8C8 ROCI_ExecServer -- 20 bytes; frame 0x10: ra sp+0x0
// ROCI interface wrapper: ExecServer.
void ROCI_ExecServer(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0056c8c8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_ROFS_ExecServer_00566778(ctx);  // tail call
}

// 0x0056C8E8 sub_56C8E8 -- 20 bytes; frame 0x10: ra sp+0x0
// ROCI interface wrapper: GetFileSiz.
void sub_56C8E8(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0056c8e8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_ROFS_GetFileSiz_005667d0(ctx);  // tail call
}

// 0x0056C900 ROCI_Open -- 20 bytes; frame 0x10: ra sp+0x0
// ROCI interface wrapper: Open.
void ROCI_Open(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0056c900
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_ROFS_Open_005665d0(ctx);  // tail call
}

// 0x0056C918 sub_56C918 -- 20 bytes; frame 0x10: ra sp+0x0
// ROCI interface wrapper: Close.
void sub_56C918(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0056c918
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_ROFS_Close_005666e0(ctx);  // tail call
}

// 0x0056C930 sub_56C930 -- 64 bytes; frame 0x10: ra sp+0x0
// ROCI interface wrapper: Seek.
void sub_56C930(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056c930
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 1;
    sd(ra, sp, 0x0);
    if (a2 != v0) {
        // 0x0056c940
        charge(ctx, 2);
        v0 = 0;
        if (a2 == 0) {
            goto L_0056c960;
        }
        // 0x0056c948
        charge(ctx, 3);
        v0 = 2;
        ld(ra, sp, 0x0);
        if (a2 == v0) {
            goto L_0056c960;
        }
        // 0x0056c954
        charge(ctx, 3);
        v0 = si(-205);
        sp = addiu(sp, 0x10);
        return;
    }
L_0056c960:
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    a2 = v0;
    sp = addiu(sp, 0x10);
    gen::fn_ROFS_Seek_00565c10(ctx);  // tail call
}

// 0x0056C970 sub_56C970 -- 20 bytes; frame 0x10: ra sp+0x0
// ROCI interface wrapper: Tell.
void sub_56C970(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0056c970
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_ROFS_Tell_00565d78(ctx);  // tail call
}

// 0x0056C988 ROCI_ReqRd -- 20 bytes; frame 0x10: ra sp+0x0
// ROCI interface wrapper: ReqRd.
void ROCI_ReqRd(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0056c988
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_ROFS_ReqRd_00566708(ctx);  // tail call
}

// 0x0056C9B8 ROCI_GetStat -- 76 bytes; frame 0x10: ra sp+0x0
// ROCI_GetStat: maps the ROFS handle state to the CRI interface state.
void ROCI_GetStat(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056c9b8
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x56C9C0u, gen::fn_ROFS_GetStat_005667a8);
    a0 = v0;
    v1 = 1;
    ld(ra, sp, 0x0);
    if (a0 != v1) {
        // 0x0056c9d8
        charge(ctx, 2);
        if (a0 == 0) {
            v0 = 0;
        } else {
            // 0x0056c9e0
            charge(ctx, 3);
            v1 = 2;
            if (a0 != v1) {
                // 0x0056c9ec
                charge(ctx, 2);
                v0 = 3;
            }
        }
    }
    // 0x0056c9fc (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x0056CAB0 roci_optAddVolume -- 168 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, ra sp+0x20
// roci_optAddVolume: adds a volume by option.
void roci_optAddVolume(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056cab0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = 0x7C0000;
    sd(s0, sp, 0x10);
    s0 = a1;
    a1 = addiu(v0, 30616);  // "ROFS"
    sd(s1, sp, 0x18);
    sd(ra, sp, 0x20);
    s1 = a0;
    link(ctx, 0x56CAD0u);  // $ra first: the delay slot below depends on it
    sw(a2, sp, 0x0);
    call(ctx, gen::fn_strcmp_00524128);
    a0 = s1;
    if (v0 != 0) {
        // 0x0056cae8
        charge(ctx, 9);
        jal(ctx, 0x56CAE8u, gen::fn_strlen_00524388);
        a1 = 0x570000;
        v1 = sltiu(v0, 9);
        v0 = si(-1);
        a1 = addiu(a1, -14152);  // &sceLibgcc32GetErxEntries_13
        a2 = 0;
        a0 = s1;
        if (v1 != 0) {
            // 0x0056cb0c
            charge(ctx, 9);
            jal(ctx, 0x56CB0Cu, gen::fn_cvFsAddDev_00555b10);
            a0 = s1;
            a1 = s0;
            a2 = sp;
            jal(ctx, 0x56CB1Cu, gen::fn_ROFS_AddVolume_005663d8);
            s0 = v0;
            v0 = si(-104);
            if (s0 != 0) {
                // 0x0056cb30
                charge(ctx, 2);
                if (s0 != v0) {
                    // 0x0056cb38
                    charge(ctx, 2);
                    a0 = s1;
                    jal(ctx, 0x56CB38u, gen::fn_sub_555D70_00555d70);
                    goto L_0056cb40;
                }
                v0 = s0;
                // 0x0056cb44 (the shared epilogue, written out on this path)
                charge(ctx, 5);
                ld(s0, sp, 0x10);
                ld(s1, sp, 0x18);
                ld(ra, sp, 0x20);
                sp = addiu(sp, 0x30);
                return;
            }
        L_0056cb40:
            charge(ctx, 1);
            v0 = s0;
        }
    } else {
        // 0x0056cae0
        charge(ctx, 2);
        v0 = si(-1);
    }
    // 0x0056cb44 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0056CBB8 ROCI_OptFn1 -- 568 bytes; frame 0x10: ra sp+0x0
// ROCI_OptFn1: option dispatcher (add volume, default volume, and so on).
void ROCI_OptFn1(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0056cbb8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 100;
    sd(ra, sp, 0x0);
    v1 = a0;
    if (a1 == v0) {
        // 0x0056cd38
        charge(ctx, 2);
        v0 = 1;
    L_0056cde4:
        charge(ctx, 1);
        ld(ra, sp, 0x0);
        // 0x0056cde8 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0056cbcc
    charge(ctx, 3);
    v0 = slti(a1, 101);
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = 203;
    if (cc) {
        // 0x0056cc28
        charge(ctx, 2);
        cc = a1 == v0;  // the condition, before the delay slot changes it
        v0 = slti(a1, 204);
        if (cc) {
            // 0x0056cd90
            charge(ctx, 4);
            a0 = a2;
            jal(ctx, 0x56CD90u, gen::fn_sub_566848_00566848);
        L_0056cdc4:
            charge(ctx, 7);
            v1 = lui(0xFFFF);
            v1 = dsrl32(v1, 0);
            v0 = v0 & v1;
            v0 = dsll32(v0, 0);
            v0 = dsra32(v0, 0);
            ld(ra, sp, 0x0);
        } else {
            // 0x0056cc30
            charge(ctx, 2);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = 205;
            if (cc) {
                // 0x0056cc60
                charge(ctx, 2);
                cc = a1 == v0;  // the condition, before the delay slot changes it
                v0 = slti(a1, 205);
                if (cc) {
                    // 0x0056cdb8
                    charge(ctx, 3);
                    a0 = a2;
                    a1 = a3;
                    jal(ctx, 0x56CDBCu, gen::fn_sub_566938_00566938);
                    goto L_0056cdc4;
                }
                // 0x0056cc68
                charge(ctx, 2);
                a0 = a2;
                if (v0 == 0) {
                    // 0x0056cc70
                    charge(ctx, 3);
                    v1 = 299;
                    v0 = 1;
                    if (a1 != v1) {
                        // 0x0056cc7c
                        charge(ctx, 2);
                        v0 = si(-1);
                    }
                    goto L_0056cde4;
                }
                // 0x0056cda0
                charge(ctx, 5);
                a1 = a3;
                jal(ctx, 0x56CDA0u, gen::fn_sub_566938_00566938);
                v0 = dsra32(v0, 0);
                ld(ra, sp, 0x0);
            } else {
                // 0x0056cc38
                charge(ctx, 3);
                v0 = 201;
                cc = a1 == v0;  // the condition, before the delay slot changes it
                v0 = slti(a1, 202);
                if (cc) {
                    // 0x0056cd60
                    charge(ctx, 2);
                    v0 = si(-1);
                    if (v1 == 0) {
                        goto L_0056cde4;
                    }
                    // 0x0056cd68
                    charge(ctx, 4);
                    jal(ctx, 0x56CD68u, gen::fn_sub_5660F0_005660f0);
                    goto L_0056cdc4;
                }
                // 0x0056cc44
                charge(ctx, 2);
                cc = v0 == 0;  // the condition, before the delay slot changes it
                v0 = 200;
                if (cc) {
                    // 0x0056cd78
                    charge(ctx, 5);
                    a0 = a2;
                    jal(ctx, 0x56CD78u, gen::fn_sub_566848_00566848);
                    v0 = dsra32(v0, 0);
                    ld(ra, sp, 0x0);
                } else {
                    // 0x0056cc4c
                    charge(ctx, 2);
                    cc = a1 == v0;  // the condition, before the delay slot changes it
                    v0 = si(-1);
                    if (cc) {
                        // 0x0056cd40
                        charge(ctx, 2);
                        ld(ra, sp, 0x0);
                        if (v1 != 0) {
                            // 0x0056cd48
                            charge(ctx, 5);
                            jal(ctx, 0x56CD48u, gen::fn_sub_5660F0_005660f0);
                            v0 = dsra32(v0, 0);
                            ld(ra, sp, 0x0);
                        }
                    } else {
                        // 0x0056cc54
                        charge(ctx, 2);
                        ld(ra, sp, 0x0);
                    }
                }
            }
        }
        // 0x0056cde8 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0056cbd8
    charge(ctx, 3);
    v0 = 3;
    cc = a1 == v0;  // the condition, before the delay slot changes it
    v0 = slti(a1, 4);
    if (cc) {
        // 0x0056ccb8
        charge(ctx, 2);
        v0 = si(-1);
        if (v1 == 0) {
            goto L_0056cde4;
        }
        // 0x0056ccc0
        charge(ctx, 3);
        lw(a0, v1, 4);
        ld(ra, sp, 0x0);
        if (a0 == 0) {
            goto L_0056cde4;
        }
        // 0x0056cccc
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        gen::fn_sub_56CB58_0056cb58(ctx);  // tail call
        return;
    }
    // 0x0056cbe4
    charge(ctx, 2);
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = 5;
    if (!cc) {
        // 0x0056cbec
        charge(ctx, 3);
        v0 = 1;
        cc = a1 == v0;  // the condition, before the delay slot changes it
        v0 = 2;
        if (cc) {
            // 0x0056cde0
            charge(ctx, 1);
            v0 = si(-1);
            goto L_0056cde4;
        }
        // 0x0056cbf8
        charge(ctx, 2);
        cc = a1 == v0;  // the condition, before the delay slot changes it
        v0 = si(-1);
        if (!cc) {
            // 0x0056cc00
            charge(ctx, 2);
            ld(ra, sp, 0x0);
            // 0x0056cde8 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            sp = addiu(sp, 0x10);
            return;
        }
        // 0x0056cc88
        charge(ctx, 2);
        ld(ra, sp, 0x0);
        if (v1 == 0) {
            // 0x0056cde8 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            sp = addiu(sp, 0x10);
            return;
        }
        // 0x0056cc90
        charge(ctx, 3);
        lw(a1, v1, 0);
        if (a1 == 0) {
            // 0x0056cde8 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            sp = addiu(sp, 0x10);
            return;
        }
        // 0x0056cc9c
        charge(ctx, 3);
        lw(a0, v1, 4);
        if (a0 == 0) {
            // 0x0056cde8 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            sp = addiu(sp, 0x10);
            return;
        }
        // 0x0056cca8
        charge(ctx, 3);
        lw(a2, v1, 8);
        sp = addiu(sp, 0x10);
        gen::fn_roci_optAddVolume_0056cab0(ctx);  // tail call
        return;
    }
    // 0x0056cc08
    charge(ctx, 2);
    cc = a1 == v0;  // the condition, before the delay slot changes it
    v0 = slti(a1, 5);
    if (cc) {
        // 0x0056ccf8
        charge(ctx, 2);
        v0 = si(-1);
        if (v1 == 0) {
            goto L_0056cde4;
        }
        // 0x0056cd00
        charge(ctx, 3);
        lw(a0, v1, 4);
        ld(ra, sp, 0x0);
        if (a0 == 0) {
            goto L_0056cde4;
        }
        // 0x0056cd0c
        charge(ctx, 3);
        lw(a1, v1, 8);
        sp = addiu(sp, 0x10);
        gen::fn_ROFS_GetVolumeInf_005669d8(ctx);  // tail call
        return;
    }
    // 0x0056cc10
    charge(ctx, 2);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = 6;
    if (cc) {
        // 0x0056ccd8
        charge(ctx, 2);
        v0 = si(-1);
        if (v1 == 0) {
            goto L_0056cde4;
        }
        // 0x0056cce0
        charge(ctx, 3);
        lw(a0, v1, 4);
        ld(ra, sp, 0x0);
        if (a0 == 0) {
            goto L_0056cde4;
        }
        // 0x0056ccec
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        gen::fn_sub_566D28_00566d28(ctx);  // tail call
        return;
    }
    // 0x0056cc18
    charge(ctx, 2);
    cc = a1 == v0;  // the condition, before the delay slot changes it
    v0 = si(-1);
    if (!cc) {
        // 0x0056cc20
        charge(ctx, 2);
        ld(ra, sp, 0x0);
        // 0x0056cde8 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0056cd18
    charge(ctx, 2);
    ld(ra, sp, 0x0);
    if (v1 == 0) {
        // 0x0056cde8 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0056cd20
    charge(ctx, 3);
    lw(a0, v1, 4);
    if (a0 == 0) {
        goto L_0056cde4;
    }
    // 0x0056cd2c
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5664F8_005664f8(ctx);  // tail call
}

}  // namespace p3fes::game
