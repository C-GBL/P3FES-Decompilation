// Pair tests for slice libs24 (game/src/lib/libs24.cpp): every body against its recompiled body, compared by
// tests/game/handgen_pairs.h (the whole register file and cycle count at every check point and at the return / stop,
// all 32 MiB of RAM, the scratchpad, the BIOS window and the bus log), on random worlds, on the five replay snapshots'
// library state (SIF RPC, libcdvd, ADXF, H_Cdvd, sound banks) with records from it, and documented-rule checks: the
// syscall numbers, the timer / DMA register stores, the T0 read, the V-blank wait and sbrk.
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/libs24.h"

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <random>
#include <string>
#include <utility>
#include <vector>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;

namespace p3fes::recomp_gen {
void fn_H_Cdvd_InitCd_00100800(EEContext&);  // generated body
void fn_H_Cdvd_InitCd_00100800__recomp(EEContext&);  // recompiled
void fn_H_Cdvd_SetRofsDir_00101520(EEContext&);  // generated body
void fn_H_Cdvd_SetRofsDir_00101520__recomp(EEContext&);  // recompiled
void fn_H_Cdvd_LoadAfsFile_001024a0(EEContext&);  // generated body
void fn_H_Cdvd_LoadAfsFile_001024a0__recomp(EEContext&);  // recompiled
void fn_H_Sndcom_CopyToIop_0010cce0(EEContext&);  // generated body
void fn_H_Sndcom_CopyToIop_0010cce0__recomp(EEContext&);  // recompiled
void fn_H_Sndcom_Update_0010cdd0(EEContext&);  // generated body
void fn_H_Sndcom_Update_0010cdd0__recomp(EEContext&);  // recompiled
void fn_sub_10E630_0010e630(EEContext&);  // generated body
void fn_sub_10E630_0010e630__recomp(EEContext&);  // recompiled
void fn_kwlnT0OverflowHandler_00196fe0(EEContext&);  // generated body
void fn_kwlnT0OverflowHandler_00196fe0__recomp(EEContext&);  // recompiled
void fn_kwlnInitPS2Systems_00197030(EEContext&);  // generated body
void fn_kwlnInitPS2Systems_00197030__recomp(EEContext&);  // recompiled
void fn_kwlnGsSyncVCallback_00197fe0(EEContext&);  // generated body
void fn_kwlnGsSyncVCallback_00197fe0__recomp(EEContext&);  // recompiled
void fn_kwlnInitMain_00198010(EEContext&);  // generated body
void fn_kwlnInitMain_00198010__recomp(EEContext&);  // recompiled
void fn_kwlnUpdate_001983a0(EEContext&);  // generated body
void fn_kwlnUpdate_001983a0__recomp(EEContext&);  // recompiled
void fn_kwlnMain_001984c0(EEContext&);  // generated body
void fn_kwlnMain_001984c0__recomp(EEContext&);  // recompiled
void fn_kwlnRootUpdateShowRasterTask_00199140(EEContext&);  // generated body
void fn_kwlnRootUpdateShowRasterTask_00199140__recomp(EEContext&);  // recompiled
void fn_Y_Misc_GetT0Count_004241d0(EEContext&);  // generated body
void fn_Y_Misc_GetT0Count_004241d0__recomp(EEContext&);  // recompiled
void fn__motionComp0_004fb870(EEContext&);  // generated body
void fn__motionComp0_004fb870__recomp(EEContext&);  // recompiled
void fn__doMC_004fbf48(EEContext&);  // generated body
void fn__doMC_004fbf48__recomp(EEContext&);  // recompiled
void fn__slice0_004fc3a8(EEContext&);  // generated body
void fn__slice0_004fc3a8__recomp(EEContext&);  // recompiled
void fn__motionVector_004fc6d8(EEContext&);  // generated body
void fn__motionVector_004fc6d8__recomp(EEContext&);  // recompiled
void fn__decMB0_004fcca0(EEContext&);  // generated body
void fn__decMB0_004fcca0__recomp(EEContext&);  // recompiled
void fn__sceMpegMbAddressIncrement_004fd1f8(EEContext&);  // generated body
void fn__sceMpegMbAddressIncrement_004fd1f8__recomp(EEContext&);  // recompiled
void fn__sceMpegWaitIpuIdle_004fd370(EEContext&);  // generated body
void fn__sceMpegWaitIpuIdle_004fd370__recomp(EEContext&);  // recompiled
void fn__sceMpegWaitIpuIdle64_004fd4d8(EEContext&);  // generated body
void fn__sceMpegWaitIpuIdle64_004fd4d8__recomp(EEContext&);  // recompiled
void fn__sceMpegFlushBuf_004fd7d0(EEContext&);  // generated body
void fn__sceMpegFlushBuf_004fd7d0__recomp(EEContext&);  // recompiled
void fn__waitIpuIdle_004fd868(EEContext&);  // generated body
void fn__waitIpuIdle_004fd868__recomp(EEContext&);  // recompiled
void fn_dmaRefImage_004fdb18(EEContext&);  // generated body
void fn_dmaRefImage_004fdb18__recomp(EEContext&);  // recompiled
void fn_receiveDataFromIPU_004fe988(EEContext&);  // generated body
void fn_receiveDataFromIPU_004fe988__recomp(EEContext&);  // recompiled
void fn__sceMpegSliceA0_004fea28(EEContext&);  // generated body
void fn__sceMpegSliceA0_004fea28__recomp(EEContext&);  // recompiled
void fn__sequenceHeader_004feee0(EEContext&);  // generated body
void fn__sequenceHeader_004feee0__recomp(EEContext&);  // recompiled
void fn__waitIpuIdle_0_004ff998(EEContext&);  // generated body
void fn__waitIpuIdle_0_004ff998__recomp(EEContext&);  // recompiled
void fn__clearEach_005001b0(EEContext&);  // generated body
void fn__clearEach_005001b0__recomp(EEContext&);  // recompiled
void fn__doCSC2_00501c38(EEContext&);  // generated body
void fn__doCSC2_00501c38__recomp(EEContext&);  // recompiled
void fn__ch3dmaCSC_005022d0(EEContext&);  // generated body
void fn__ch3dmaCSC_005022d0__recomp(EEContext&);  // recompiled
void fn_setD4_CHCR_0_00502a90(EEContext&);  // generated body
void fn_setD4_CHCR_0_00502a90__recomp(EEContext&);  // recompiled
void fn_sceIpuInit_00502b08(EEContext&);  // generated body
void fn_sceIpuInit_00502b08__recomp(EEContext&);  // recompiled
void fn__sceAddIntcHandler_0_00502e50(EEContext&);  // generated body
void fn__sceAddIntcHandler_0_00502e50__recomp(EEContext&);  // recompiled
void fn__sceAddDmacHandler_00502e70(EEContext&);  // generated body
void fn__sceAddDmacHandler_00502e70__recomp(EEContext&);  // recompiled
void fn__sceAddDmacHandler_0_00502e80(EEContext&);  // generated body
void fn__sceAddDmacHandler_0_00502e80__recomp(EEContext&);  // recompiled
void fn__sce_EnableIntc_00502ea0(EEContext&);  // generated body
void fn__sce_EnableIntc_00502ea0__recomp(EEContext&);  // recompiled
void fn__sce_EnableDmac_00502ec0(EEContext&);  // generated body
void fn__sce_EnableDmac_00502ec0__recomp(EEContext&);  // recompiled
void fn__sce_DisableDmac_00502ed0(EEContext&);  // generated body
void fn__sce_DisableDmac_00502ed0__recomp(EEContext&);  // recompiled
void fn__sceStartThread_00502f80(EEContext&);  // generated body
void fn__sceStartThread_00502f80__recomp(EEContext&);  // recompiled
void fn__sceiReferThreadStatus_00503070(EEContext&);  // generated body
void fn__sceiReferThreadStatus_00503070__recomp(EEContext&);  // recompiled
void fn__sce_iWakeupThread_005030a0(EEContext&);  // generated body
void fn__sce_iWakeupThread_005030a0__recomp(EEContext&);  // recompiled
void fn__sceEndOfHeap_00503140(EEContext&);  // generated body
void fn__sceEndOfHeap_00503140__recomp(EEContext&);  // recompiled
void fn__scePollSema_005031b0(EEContext&);  // generated body
void fn__scePollSema_005031b0__recomp(EEContext&);  // recompiled
void fn__sceSetOsdConfigParam_00503200(EEContext&);  // generated body
void fn__sceSetOsdConfigParam_00503200__recomp(EEContext&);  // recompiled
void fn__sceGetOsdConfigParam_00503210(EEContext&);  // generated body
void fn__sceGetOsdConfigParam_00503210__recomp(EEContext&);  // recompiled
void fn__sceFlushCache_005033e0(EEContext&);  // generated body
void fn__sceFlushCache_005033e0__recomp(EEContext&);  // recompiled
void fn__sceSifStopDma_00503430(EEContext&);  // generated body
void fn__sceSifStopDma_00503430__recomp(EEContext&);  // recompiled
void fn__sceGsPutIMR_005034a0(EEContext&);  // generated body
void fn__sceGsPutIMR_005034a0__recomp(EEContext&);  // recompiled
void fn__sceSifDmaStat_00503500(EEContext&);  // generated body
void fn__sceSifDmaStat_00503500__recomp(EEContext&);  // recompiled
void fn__sceSifSetDma_00503520(EEContext&);  // generated body
void fn__sceSifSetDma_00503520__recomp(EEContext&);  // recompiled
void fn__sceSifSetDChain_00503540(EEContext&);  // generated body
void fn__sceSifSetDChain_00503540__recomp(EEContext&);  // recompiled
void fn__isceSifSetDChain_00503550(EEContext&);  // generated body
void fn__isceSifSetDChain_00503550__recomp(EEContext&);  // recompiled
void fn__sceSifSetReg_00503560(EEContext&);  // generated body
void fn__sceSifSetReg_00503560__recomp(EEContext&);  // recompiled
void fn__sceSifGetReg_00503570(EEContext&);  // generated body
void fn__sceSifGetReg_00503570__recomp(EEContext&);  // recompiled
void fn_VSync_005035f0(EEContext&);  // generated body
void fn_VSync_005035f0__recomp(EEContext&);  // recompiled
void fn_sbrk_00503860(EEContext&);  // generated body
void fn_sbrk_00503860__recomp(EEContext&);  // recompiled
void fn__sceSDC_005039b0(EEContext&);  // generated body
void fn__sceSDC_005039b0__recomp(EEContext&);  // recompiled
void fn_SyncDCache_00503a58(EEContext&);  // generated body
void fn_SyncDCache_00503a58__recomp(EEContext&);  // recompiled
void fn__sceIDC_00503af0(EEContext&);  // generated body
void fn__sceIDC_00503af0__recomp(EEContext&);  // recompiled
void fn_InvalidDCache_00503b98(EEContext&);  // generated body
void fn_InvalidDCache_00503b98__recomp(EEContext&);  // recompiled
void fn_QueryIntrContext_00503c30(EEContext&);  // generated body
void fn_QueryIntrContext_00503c30__recomp(EEContext&);  // recompiled
void fn_EnableDmac_00503d78(EEContext&);  // generated body
void fn_EnableDmac_00503d78__recomp(EEContext&);  // recompiled
void fn_sceSifSetDmaInternal_00505fc0(EEContext&);  // generated body
void fn_sceSifSetDmaInternal_00505fc0__recomp(EEContext&);  // recompiled
void fn_sceSifSetDma_00506088(EEContext&);  // generated body
void fn_sceSifSetDma_00506088__recomp(EEContext&);  // recompiled
void fn_sceSifInitCmd_00506148(EEContext&);  // generated body
void fn_sceSifInitCmd_00506148__recomp(EEContext&);  // recompiled
void fn_sub_5066B0_005066b0(EEContext&);  // generated body
void fn_sub_5066B0_005066b0__recomp(EEContext&);  // recompiled
void fn_sceSifInitRpc_005068a8(EEContext&);  // generated body
void fn_sceSifInitRpc_005068a8__recomp(EEContext&);  // recompiled
void fn__request_end_00506ba8(EEContext&);  // generated body
void fn__request_end_00506ba8__recomp(EEContext&);  // recompiled
void fn_sceSifBindRpc_00507050(EEContext&);  // generated body
void fn_sceSifBindRpc_00507050__recomp(EEContext&);  // recompiled
void fn_sceSifCallRpc_00507230(EEContext&);  // generated body
void fn_sceSifCallRpc_00507230__recomp(EEContext&);  // recompiled
void fn_sceSifRpcLoop_00507920(EEContext&);  // generated body
void fn_sceSifRpcLoop_00507920__recomp(EEContext&);  // recompiled
void fn_sceSifInitIopHeap_0050b598(EEContext&);  // generated body
void fn_sceSifInitIopHeap_0050b598__recomp(EEContext&);  // recompiled
void fn_sceSifAllocIopHeap_0050b620(EEContext&);  // generated body
void fn_sceSifAllocIopHeap_0050b620__recomp(EEContext&);  // recompiled
void fn_sceSifAllocSysMemory_0050b690(EEContext&);  // generated body
void fn_sceSifAllocSysMemory_0050b690__recomp(EEContext&);  // recompiled
void fn_sceSifFreeSysMemory_0050b710(EEContext&);  // generated body
void fn_sceSifFreeSysMemory_0050b710__recomp(EEContext&);  // recompiled
void fn__lf_bind_0050bae8(EEContext&);  // generated body
void fn__lf_bind_0050bae8__recomp(EEContext&);  // recompiled
void fn__sceSifLoadModule_0050c2c0(EEContext&);  // generated body
void fn__sceSifLoadModule_0050c2c0__recomp(EEContext&);  // recompiled
void fn_sceSifLoadModule_0050c4e8(EEContext&);  // generated body
void fn_sceSifLoadModule_0050c4e8__recomp(EEContext&);  // recompiled
void fn_sceSifResetIop_0050c848(EEContext&);  // generated body
void fn_sceSifResetIop_0050c848__recomp(EEContext&);  // recompiled
void fn_sceSifSyncIop_0050c9c8(EEContext&);  // generated body
void fn_sceSifSyncIop_0050c9c8__recomp(EEContext&);  // recompiled
void fn_sceSifRebootIop_0050ca18(EEContext&);  // generated body
void fn_sceSifRebootIop_0050ca18__recomp(EEContext&);  // recompiled
void fn__sceCopy_0050cc10(EEContext&);  // generated body
void fn__sceCopy_0050cc10__recomp(EEContext&);  // recompiled
void fn__sceGetEntryAddress_0050cc58(EEContext&);  // generated body
void fn__sceGetEntryAddress_0050cc58__recomp(EEContext&);  // recompiled
void fn__sceSetSyscall_0050cc68(EEContext&);  // generated body
void fn__sceSetSyscall_0050cc68__recomp(EEContext&);  // recompiled
void fn_DIntr_0050d3a0(EEContext&);  // generated body
void fn_DIntr_0050d3a0__recomp(EEContext&);  // recompiled
void fn_EIntr_0050d3f0(EEContext&);  // generated body
void fn_EIntr_0050d3f0__recomp(EEContext&);  // recompiled
void fn__sceFindAddress_0050d500(EEContext&);  // generated body
void fn__sceFindAddress_0050d500__recomp(EEContext&);  // recompiled
void fn__sceSetSyscall_0_0050d648(EEContext&);  // generated body
void fn__sceSetSyscall_0_0050d648__recomp(EEContext&);  // recompiled
void fn__sceSetSyscall_3_0050dad0(EEContext&);  // generated body
void fn__sceSetSyscall_3_0050dad0__recomp(EEContext&);  // recompiled
void fn__sceCopy_3_0050dae0(EEContext&);  // generated body
void fn__sceCopy_3_0050dae0__recomp(EEContext&);  // recompiled
void fn__sceGetEntryAddress_1_0050db28(EEContext&);  // generated body
void fn__sceGetEntryAddress_1_0050db28__recomp(EEContext&);  // recompiled
void fn_InitAlarm_0050db38(EEContext&);  // generated body
void fn_InitAlarm_0050db38__recomp(EEContext&);  // recompiled
void fn_sub_50DC80_0050dc80(EEContext&);  // generated body
void fn_sub_50DC80_0050dc80__recomp(EEContext&);  // recompiled
void fn_sub_50DC90_0050dc90(EEContext&);  // generated body
void fn_sub_50DC90_0050dc90__recomp(EEContext&);  // recompiled
void fn_sub_50DCA0_0050dca0(EEContext&);  // generated body
void fn_sub_50DCA0_0050dca0__recomp(EEContext&);  // recompiled
void fn_InitTimer_0050dcb0(EEContext&);  // generated body
void fn_InitTimer_0050dcb0__recomp(EEContext&);  // recompiled
void fn_StartTimerSystemTime_0050def0(EEContext&);  // generated body
void fn_StartTimerSystemTime_0050def0__recomp(EEContext&);  // recompiled
void fn_cbTimerHandler_0050e250(EEContext&);  // generated body
void fn_cbTimerHandler_0050e250__recomp(EEContext&);  // recompiled
void fn__sceCd_cd_read_intr_0050f8a8(EEContext&);  // generated body
void fn__sceCd_cd_read_intr_0050f8a8__recomp(EEContext&);  // recompiled
void fn_sceCdLayerSearchFile_0050fc38(EEContext&);  // generated body
void fn_sceCdLayerSearchFile_0050fc38__recomp(EEContext&);  // recompiled
void fn__sceCd_ncmd_prechk_0050ff58(EEContext&);  // generated body
void fn__sceCd_ncmd_prechk_0050ff58__recomp(EEContext&);  // recompiled
void fn_sceCdNcmdDiskReady_005100b0(EEContext&);  // generated body
void fn_sceCdNcmdDiskReady_005100b0__recomp(EEContext&);  // recompiled
void fn_sceCdSync_00510148(EEContext&);  // generated body
void fn_sceCdSync_00510148__recomp(EEContext&);  // recompiled
void fn_sceCdSyncS_005101e8(EEContext&);  // generated body
void fn_sceCdSyncS_005101e8__recomp(EEContext&);  // recompiled
void fn__sceCd_scmd_prechk_00510258(EEContext&);  // generated body
void fn__sceCd_scmd_prechk_00510258__recomp(EEContext&);  // recompiled
void fn_sceCdInit_00510460(EEContext&);  // generated body
void fn_sceCdInit_00510460__recomp(EEContext&);  // recompiled
void fn_sceCdDiskReady_00510960(EEContext&);  // generated body
void fn_sceCdDiskReady_00510960__recomp(EEContext&);  // recompiled
void fn_sceCdRead_00510b80(EEContext&);  // generated body
void fn_sceCdRead_00510b80__recomp(EEContext&);  // recompiled
void fn_sceCdGetError_00510ef0(EEContext&);  // generated body
void fn_sceCdGetError_00510ef0__recomp(EEContext&);  // recompiled
void fn_sceCdMmode_00511040(EEContext&);  // generated body
void fn_sceCdMmode_00511040__recomp(EEContext&);  // recompiled
void fn_scePadInit2_005112d0(EEContext&);  // generated body
void fn_scePadInit2_005112d0__recomp(EEContext&);  // recompiled
void fn_scePadSetMainMode_00511fb8(EEContext&);  // generated body
void fn_scePadSetMainMode_00511fb8__recomp(EEContext&);  // recompiled
void fn_scePadSetActAlign_00512138(EEContext&);  // generated body
void fn_scePadSetActAlign_00512138__recomp(EEContext&);  // recompiled
void fn_scePadGetModVersion_00512640(EEContext&);  // generated body
void fn_scePadGetModVersion_00512640__recomp(EEContext&);  // recompiled
void fn_sceSdRemoteCallbackInit_00512d48(EEContext&);  // generated body
void fn_sceSdRemoteCallbackInit_00512d48__recomp(EEContext&);  // recompiled
void fn__sdrCBThread_00512f80(EEContext&);  // generated body
void fn__sdrCBThread_00512f80__recomp(EEContext&);  // recompiled
void fn_sceMc2SifCallback_0051ae38(EEContext&);  // generated body
void fn_sceMc2SifCallback_0051ae38__recomp(EEContext&);  // recompiled
void fn_sceDbcGetModVersion_0051c360(EEContext&);  // generated body
void fn_sceDbcGetModVersion_0051c360__recomp(EEContext&);  // recompiled
void fn_sceDbcSetWorkAddr_0051c700(EEContext&);  // generated body
void fn_sceDbcSetWorkAddr_0051c700__recomp(EEContext&);  // recompiled
void fn_sceDbcCreateSocket_0051c770(EEContext&);  // generated body
void fn_sceDbcCreateSocket_0051c770__recomp(EEContext&);  // recompiled
void fn_sceDbcSendData3_0051d308(EEContext&);  // generated body
void fn_sceDbcSendData3_0051d308__recomp(EEContext&);  // recompiled
void fn_sceSkSsSOUND_Send_0051dbc0(EEContext&);  // generated body
void fn_sceSkSsSOUND_Send_0051dbc0__recomp(EEContext&);  // recompiled
void fn_sceSkSsHSYNTH_Bind_0051dc70(EEContext&);  // generated body
void fn_sceSkSsHSYNTH_Bind_0051dc70__recomp(EEContext&);  // recompiled
void fn_sceSkSsHSYNTH_Unbind_0051dd48(EEContext&);  // generated body
void fn_sceSkSsHSYNTH_Unbind_0051dd48__recomp(EEContext&);  // recompiled
void fn_sceSkSsSESQ_Bind_0051ddf0(EEContext&);  // generated body
void fn_sceSkSsSESQ_Bind_0051ddf0__recomp(EEContext&);  // recompiled
void fn_sceSkSsSESQ_Unbind_0051deb0(EEContext&);  // generated body
void fn_sceSkSsSESQ_Unbind_0051deb0__recomp(EEContext&);  // recompiled
void fn_ADXF_SetupRofs_0053b220(EEContext&);  // generated body
void fn_ADXF_SetupRofs_0053b220__recomp(EEContext&);  // recompiled
void fn_ADXF_AddRofsVol_0053b2c0(EEContext&);  // generated body
void fn_ADXF_AddRofsVol_0053b2c0__recomp(EEContext&);  // recompiled
void fn_sub_53B4F8_0053b4f8(EEContext&);  // generated body
void fn_sub_53B4F8_0053b4f8__recomp(EEContext&);  // recompiled
void fn_ADXF_LoadPartitionNw_0053b868(EEContext&);  // generated body
void fn_ADXF_LoadPartitionNw_0053b868__recomp(EEContext&);  // recompiled
void fn_sub_53BEF0_0053bef0(EEContext&);  // generated body
void fn_sub_53BEF0_0053bef0__recomp(EEContext&);  // recompiled
void fn_sub_53C2A0_0053c2a0(EEContext&);  // generated body
void fn_sub_53C2A0_0053c2a0__recomp(EEContext&);  // recompiled
void fn_ADXF_Open_0053c910(EEContext&);  // generated body
void fn_ADXF_Open_0053c910__recomp(EEContext&);  // recompiled
void fn_adxf_Open_0053c958(EEContext&);  // generated body
void fn_adxf_Open_0053c958__recomp(EEContext&);  // recompiled
void fn_ADXF_ReadNw_0053d380(EEContext&);  // generated body
void fn_ADXF_ReadNw_0053d380__recomp(EEContext&);  // recompiled
void fn_adxf_ReadNw_0053d3d8(EEContext&);  // generated body
void fn_adxf_ReadNw_0053d3d8__recomp(EEContext&);  // recompiled
void fn_ADXF_ExecServer_0053d708(EEContext&);  // generated body
void fn_ADXF_ExecServer_0053d708__recomp(EEContext&);  // recompiled
void fn_adxf_ExecServer_0053d730(EEContext&);  // generated body
void fn_adxf_ExecServer_0053d730__recomp(EEContext&);  // recompiled
void fn_ADXF_GetFsizeSct_0053d968(EEContext&);  // generated body
void fn_ADXF_GetFsizeSct_0053d968__recomp(EEContext&);  // recompiled
void fn_ADXF_GetStat_0053db90(EEContext&);  // generated body
void fn_ADXF_GetStat_0053db90__recomp(EEContext&);  // recompiled
void fn_DTX_Init_00559aa8(EEContext&);  // generated body
void fn_DTX_Init_00559aa8__recomp(EEContext&);  // recompiled
void fn_dvCiCdSearchFile_00559dd8(EEContext&);  // generated body
void fn_dvCiCdSearchFile_00559dd8__recomp(EEContext&);  // recompiled
void fn_sub_594038_00594038(EEContext&);  // generated body
void fn_sub_594038_00594038__recomp(EEContext&);  // recompiled
void fn_sub_5940A0_005940a0(EEContext&);  // generated body
void fn_sub_5940A0_005940a0__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"H_Cdvd_InitCd", 0x100800, &recomp_gen::fn_H_Cdvd_InitCd_00100800, &recomp_gen::fn_H_Cdvd_InitCd_00100800__recomp},
    {"H_Cdvd_SetRofsDir", 0x101520, &recomp_gen::fn_H_Cdvd_SetRofsDir_00101520, &recomp_gen::fn_H_Cdvd_SetRofsDir_00101520__recomp},
    {"H_Cdvd_LoadAfsFile", 0x1024A0, &recomp_gen::fn_H_Cdvd_LoadAfsFile_001024a0, &recomp_gen::fn_H_Cdvd_LoadAfsFile_001024a0__recomp},
    {"H_Sndcom_CopyToIop", 0x10CCE0, &recomp_gen::fn_H_Sndcom_CopyToIop_0010cce0, &recomp_gen::fn_H_Sndcom_CopyToIop_0010cce0__recomp},
    {"H_Sndcom_Update", 0x10CDD0, &recomp_gen::fn_H_Sndcom_Update_0010cdd0, &recomp_gen::fn_H_Sndcom_Update_0010cdd0__recomp},
    {"sub_10E630", 0x10E630, &recomp_gen::fn_sub_10E630_0010e630, &recomp_gen::fn_sub_10E630_0010e630__recomp},
    {"kwlnT0OverflowHandler", 0x196FE0, &recomp_gen::fn_kwlnT0OverflowHandler_00196fe0, &recomp_gen::fn_kwlnT0OverflowHandler_00196fe0__recomp},
    {"kwlnInitPS2Systems", 0x197030, &recomp_gen::fn_kwlnInitPS2Systems_00197030, &recomp_gen::fn_kwlnInitPS2Systems_00197030__recomp},
    {"kwlnGsSyncVCallback", 0x197FE0, &recomp_gen::fn_kwlnGsSyncVCallback_00197fe0, &recomp_gen::fn_kwlnGsSyncVCallback_00197fe0__recomp},
    {"kwlnInitMain", 0x198010, &recomp_gen::fn_kwlnInitMain_00198010, &recomp_gen::fn_kwlnInitMain_00198010__recomp},
    {"kwlnUpdate", 0x1983A0, &recomp_gen::fn_kwlnUpdate_001983a0, &recomp_gen::fn_kwlnUpdate_001983a0__recomp},
    {"kwlnMain", 0x1984C0, &recomp_gen::fn_kwlnMain_001984c0, &recomp_gen::fn_kwlnMain_001984c0__recomp},
    {"kwlnRootUpdateShowRasterTask", 0x199140, &recomp_gen::fn_kwlnRootUpdateShowRasterTask_00199140, &recomp_gen::fn_kwlnRootUpdateShowRasterTask_00199140__recomp},
    {"Y_Misc_GetT0Count", 0x4241D0, &recomp_gen::fn_Y_Misc_GetT0Count_004241d0, &recomp_gen::fn_Y_Misc_GetT0Count_004241d0__recomp},
    {"_motionComp0", 0x4FB870, &recomp_gen::fn__motionComp0_004fb870, &recomp_gen::fn__motionComp0_004fb870__recomp},
    {"_doMC", 0x4FBF48, &recomp_gen::fn__doMC_004fbf48, &recomp_gen::fn__doMC_004fbf48__recomp},
    {"_slice0", 0x4FC3A8, &recomp_gen::fn__slice0_004fc3a8, &recomp_gen::fn__slice0_004fc3a8__recomp},
    {"_motionVector", 0x4FC6D8, &recomp_gen::fn__motionVector_004fc6d8, &recomp_gen::fn__motionVector_004fc6d8__recomp},
    {"_decMB0", 0x4FCCA0, &recomp_gen::fn__decMB0_004fcca0, &recomp_gen::fn__decMB0_004fcca0__recomp},
    {"_sceMpegMbAddressIncrement", 0x4FD1F8, &recomp_gen::fn__sceMpegMbAddressIncrement_004fd1f8, &recomp_gen::fn__sceMpegMbAddressIncrement_004fd1f8__recomp},
    {"_sceMpegWaitIpuIdle", 0x4FD370, &recomp_gen::fn__sceMpegWaitIpuIdle_004fd370, &recomp_gen::fn__sceMpegWaitIpuIdle_004fd370__recomp},
    {"_sceMpegWaitIpuIdle64", 0x4FD4D8, &recomp_gen::fn__sceMpegWaitIpuIdle64_004fd4d8, &recomp_gen::fn__sceMpegWaitIpuIdle64_004fd4d8__recomp},
    {"_sceMpegFlushBuf", 0x4FD7D0, &recomp_gen::fn__sceMpegFlushBuf_004fd7d0, &recomp_gen::fn__sceMpegFlushBuf_004fd7d0__recomp},
    {"_waitIpuIdle", 0x4FD868, &recomp_gen::fn__waitIpuIdle_004fd868, &recomp_gen::fn__waitIpuIdle_004fd868__recomp},
    {"dmaRefImage", 0x4FDB18, &recomp_gen::fn_dmaRefImage_004fdb18, &recomp_gen::fn_dmaRefImage_004fdb18__recomp},
    {"receiveDataFromIPU", 0x4FE988, &recomp_gen::fn_receiveDataFromIPU_004fe988, &recomp_gen::fn_receiveDataFromIPU_004fe988__recomp},
    {"_sceMpegSliceA0", 0x4FEA28, &recomp_gen::fn__sceMpegSliceA0_004fea28, &recomp_gen::fn__sceMpegSliceA0_004fea28__recomp},
    {"_sequenceHeader", 0x4FEEE0, &recomp_gen::fn__sequenceHeader_004feee0, &recomp_gen::fn__sequenceHeader_004feee0__recomp},
    {"_waitIpuIdle_0", 0x4FF998, &recomp_gen::fn__waitIpuIdle_0_004ff998, &recomp_gen::fn__waitIpuIdle_0_004ff998__recomp},
    {"_clearEach", 0x5001B0, &recomp_gen::fn__clearEach_005001b0, &recomp_gen::fn__clearEach_005001b0__recomp},
    {"_doCSC2", 0x501C38, &recomp_gen::fn__doCSC2_00501c38, &recomp_gen::fn__doCSC2_00501c38__recomp},
    {"_ch3dmaCSC", 0x5022D0, &recomp_gen::fn__ch3dmaCSC_005022d0, &recomp_gen::fn__ch3dmaCSC_005022d0__recomp},
    {"setD4_CHCR_0", 0x502A90, &recomp_gen::fn_setD4_CHCR_0_00502a90, &recomp_gen::fn_setD4_CHCR_0_00502a90__recomp},
    {"sceIpuInit", 0x502B08, &recomp_gen::fn_sceIpuInit_00502b08, &recomp_gen::fn_sceIpuInit_00502b08__recomp},
    {"_sceAddIntcHandler_0", 0x502E50, &recomp_gen::fn__sceAddIntcHandler_0_00502e50, &recomp_gen::fn__sceAddIntcHandler_0_00502e50__recomp},
    {"_sceAddDmacHandler", 0x502E70, &recomp_gen::fn__sceAddDmacHandler_00502e70, &recomp_gen::fn__sceAddDmacHandler_00502e70__recomp},
    {"_sceAddDmacHandler_0", 0x502E80, &recomp_gen::fn__sceAddDmacHandler_0_00502e80, &recomp_gen::fn__sceAddDmacHandler_0_00502e80__recomp},
    {"_sce_EnableIntc", 0x502EA0, &recomp_gen::fn__sce_EnableIntc_00502ea0, &recomp_gen::fn__sce_EnableIntc_00502ea0__recomp},
    {"_sce_EnableDmac", 0x502EC0, &recomp_gen::fn__sce_EnableDmac_00502ec0, &recomp_gen::fn__sce_EnableDmac_00502ec0__recomp},
    {"_sce_DisableDmac", 0x502ED0, &recomp_gen::fn__sce_DisableDmac_00502ed0, &recomp_gen::fn__sce_DisableDmac_00502ed0__recomp},
    {"_sceStartThread", 0x502F80, &recomp_gen::fn__sceStartThread_00502f80, &recomp_gen::fn__sceStartThread_00502f80__recomp},
    {"_sceiReferThreadStatus", 0x503070, &recomp_gen::fn__sceiReferThreadStatus_00503070, &recomp_gen::fn__sceiReferThreadStatus_00503070__recomp},
    {"_sce_iWakeupThread", 0x5030A0, &recomp_gen::fn__sce_iWakeupThread_005030a0, &recomp_gen::fn__sce_iWakeupThread_005030a0__recomp},
    {"_sceEndOfHeap", 0x503140, &recomp_gen::fn__sceEndOfHeap_00503140, &recomp_gen::fn__sceEndOfHeap_00503140__recomp},
    {"_scePollSema", 0x5031B0, &recomp_gen::fn__scePollSema_005031b0, &recomp_gen::fn__scePollSema_005031b0__recomp},
    {"_sceSetOsdConfigParam", 0x503200, &recomp_gen::fn__sceSetOsdConfigParam_00503200, &recomp_gen::fn__sceSetOsdConfigParam_00503200__recomp},
    {"_sceGetOsdConfigParam", 0x503210, &recomp_gen::fn__sceGetOsdConfigParam_00503210, &recomp_gen::fn__sceGetOsdConfigParam_00503210__recomp},
    {"_sceFlushCache", 0x5033E0, &recomp_gen::fn__sceFlushCache_005033e0, &recomp_gen::fn__sceFlushCache_005033e0__recomp},
    {"_sceSifStopDma", 0x503430, &recomp_gen::fn__sceSifStopDma_00503430, &recomp_gen::fn__sceSifStopDma_00503430__recomp},
    {"_sceGsPutIMR", 0x5034A0, &recomp_gen::fn__sceGsPutIMR_005034a0, &recomp_gen::fn__sceGsPutIMR_005034a0__recomp},
    {"_sceSifDmaStat", 0x503500, &recomp_gen::fn__sceSifDmaStat_00503500, &recomp_gen::fn__sceSifDmaStat_00503500__recomp},
    {"_sceSifSetDma", 0x503520, &recomp_gen::fn__sceSifSetDma_00503520, &recomp_gen::fn__sceSifSetDma_00503520__recomp},
    {"_sceSifSetDChain", 0x503540, &recomp_gen::fn__sceSifSetDChain_00503540, &recomp_gen::fn__sceSifSetDChain_00503540__recomp},
    {"_isceSifSetDChain", 0x503550, &recomp_gen::fn__isceSifSetDChain_00503550, &recomp_gen::fn__isceSifSetDChain_00503550__recomp},
    {"_sceSifSetReg", 0x503560, &recomp_gen::fn__sceSifSetReg_00503560, &recomp_gen::fn__sceSifSetReg_00503560__recomp},
    {"_sceSifGetReg", 0x503570, &recomp_gen::fn__sceSifGetReg_00503570, &recomp_gen::fn__sceSifGetReg_00503570__recomp},
    {"VSync", 0x5035F0, &recomp_gen::fn_VSync_005035f0, &recomp_gen::fn_VSync_005035f0__recomp},
    {"sbrk", 0x503860, &recomp_gen::fn_sbrk_00503860, &recomp_gen::fn_sbrk_00503860__recomp},
    {"_sceSDC", 0x5039B0, &recomp_gen::fn__sceSDC_005039b0, &recomp_gen::fn__sceSDC_005039b0__recomp},
    {"SyncDCache", 0x503A58, &recomp_gen::fn_SyncDCache_00503a58, &recomp_gen::fn_SyncDCache_00503a58__recomp},
    {"_sceIDC", 0x503AF0, &recomp_gen::fn__sceIDC_00503af0, &recomp_gen::fn__sceIDC_00503af0__recomp},
    {"InvalidDCache", 0x503B98, &recomp_gen::fn_InvalidDCache_00503b98, &recomp_gen::fn_InvalidDCache_00503b98__recomp},
    {"QueryIntrContext", 0x503C30, &recomp_gen::fn_QueryIntrContext_00503c30, &recomp_gen::fn_QueryIntrContext_00503c30__recomp},
    {"EnableDmac", 0x503D78, &recomp_gen::fn_EnableDmac_00503d78, &recomp_gen::fn_EnableDmac_00503d78__recomp},
    {"sceSifSetDmaInternal", 0x505FC0, &recomp_gen::fn_sceSifSetDmaInternal_00505fc0, &recomp_gen::fn_sceSifSetDmaInternal_00505fc0__recomp},
    {"sceSifSetDma", 0x506088, &recomp_gen::fn_sceSifSetDma_00506088, &recomp_gen::fn_sceSifSetDma_00506088__recomp},
    {"sceSifInitCmd", 0x506148, &recomp_gen::fn_sceSifInitCmd_00506148, &recomp_gen::fn_sceSifInitCmd_00506148__recomp},
    {"sub_5066B0", 0x5066B0, &recomp_gen::fn_sub_5066B0_005066b0, &recomp_gen::fn_sub_5066B0_005066b0__recomp},
    {"sceSifInitRpc", 0x5068A8, &recomp_gen::fn_sceSifInitRpc_005068a8, &recomp_gen::fn_sceSifInitRpc_005068a8__recomp},
    {"_request_end", 0x506BA8, &recomp_gen::fn__request_end_00506ba8, &recomp_gen::fn__request_end_00506ba8__recomp},
    {"sceSifBindRpc", 0x507050, &recomp_gen::fn_sceSifBindRpc_00507050, &recomp_gen::fn_sceSifBindRpc_00507050__recomp},
    {"sceSifCallRpc", 0x507230, &recomp_gen::fn_sceSifCallRpc_00507230, &recomp_gen::fn_sceSifCallRpc_00507230__recomp},
    {"sceSifRpcLoop", 0x507920, &recomp_gen::fn_sceSifRpcLoop_00507920, &recomp_gen::fn_sceSifRpcLoop_00507920__recomp},
    {"sceSifInitIopHeap", 0x50B598, &recomp_gen::fn_sceSifInitIopHeap_0050b598, &recomp_gen::fn_sceSifInitIopHeap_0050b598__recomp},
    {"sceSifAllocIopHeap", 0x50B620, &recomp_gen::fn_sceSifAllocIopHeap_0050b620, &recomp_gen::fn_sceSifAllocIopHeap_0050b620__recomp},
    {"sceSifAllocSysMemory", 0x50B690, &recomp_gen::fn_sceSifAllocSysMemory_0050b690, &recomp_gen::fn_sceSifAllocSysMemory_0050b690__recomp},
    {"sceSifFreeSysMemory", 0x50B710, &recomp_gen::fn_sceSifFreeSysMemory_0050b710, &recomp_gen::fn_sceSifFreeSysMemory_0050b710__recomp},
    {"_lf_bind", 0x50BAE8, &recomp_gen::fn__lf_bind_0050bae8, &recomp_gen::fn__lf_bind_0050bae8__recomp},
    {"_sceSifLoadModule", 0x50C2C0, &recomp_gen::fn__sceSifLoadModule_0050c2c0, &recomp_gen::fn__sceSifLoadModule_0050c2c0__recomp},
    {"sceSifLoadModule", 0x50C4E8, &recomp_gen::fn_sceSifLoadModule_0050c4e8, &recomp_gen::fn_sceSifLoadModule_0050c4e8__recomp},
    {"sceSifResetIop", 0x50C848, &recomp_gen::fn_sceSifResetIop_0050c848, &recomp_gen::fn_sceSifResetIop_0050c848__recomp},
    {"sceSifSyncIop", 0x50C9C8, &recomp_gen::fn_sceSifSyncIop_0050c9c8, &recomp_gen::fn_sceSifSyncIop_0050c9c8__recomp},
    {"sceSifRebootIop", 0x50CA18, &recomp_gen::fn_sceSifRebootIop_0050ca18, &recomp_gen::fn_sceSifRebootIop_0050ca18__recomp},
    {"_sceCopy", 0x50CC10, &recomp_gen::fn__sceCopy_0050cc10, &recomp_gen::fn__sceCopy_0050cc10__recomp},
    {"_sceGetEntryAddress", 0x50CC58, &recomp_gen::fn__sceGetEntryAddress_0050cc58, &recomp_gen::fn__sceGetEntryAddress_0050cc58__recomp},
    {"_sceSetSyscall", 0x50CC68, &recomp_gen::fn__sceSetSyscall_0050cc68, &recomp_gen::fn__sceSetSyscall_0050cc68__recomp},
    {"DIntr", 0x50D3A0, &recomp_gen::fn_DIntr_0050d3a0, &recomp_gen::fn_DIntr_0050d3a0__recomp},
    {"EIntr", 0x50D3F0, &recomp_gen::fn_EIntr_0050d3f0, &recomp_gen::fn_EIntr_0050d3f0__recomp},
    {"_sceFindAddress", 0x50D500, &recomp_gen::fn__sceFindAddress_0050d500, &recomp_gen::fn__sceFindAddress_0050d500__recomp},
    {"_sceSetSyscall_0", 0x50D648, &recomp_gen::fn__sceSetSyscall_0_0050d648, &recomp_gen::fn__sceSetSyscall_0_0050d648__recomp},
    {"_sceSetSyscall_3", 0x50DAD0, &recomp_gen::fn__sceSetSyscall_3_0050dad0, &recomp_gen::fn__sceSetSyscall_3_0050dad0__recomp},
    {"_sceCopy_3", 0x50DAE0, &recomp_gen::fn__sceCopy_3_0050dae0, &recomp_gen::fn__sceCopy_3_0050dae0__recomp},
    {"_sceGetEntryAddress_1", 0x50DB28, &recomp_gen::fn__sceGetEntryAddress_1_0050db28, &recomp_gen::fn__sceGetEntryAddress_1_0050db28__recomp},
    {"InitAlarm", 0x50DB38, &recomp_gen::fn_InitAlarm_0050db38, &recomp_gen::fn_InitAlarm_0050db38__recomp},
    {"sub_50DC80", 0x50DC80, &recomp_gen::fn_sub_50DC80_0050dc80, &recomp_gen::fn_sub_50DC80_0050dc80__recomp},
    {"sub_50DC90", 0x50DC90, &recomp_gen::fn_sub_50DC90_0050dc90, &recomp_gen::fn_sub_50DC90_0050dc90__recomp},
    {"sub_50DCA0", 0x50DCA0, &recomp_gen::fn_sub_50DCA0_0050dca0, &recomp_gen::fn_sub_50DCA0_0050dca0__recomp},
    {"InitTimer", 0x50DCB0, &recomp_gen::fn_InitTimer_0050dcb0, &recomp_gen::fn_InitTimer_0050dcb0__recomp},
    {"StartTimerSystemTime", 0x50DEF0, &recomp_gen::fn_StartTimerSystemTime_0050def0, &recomp_gen::fn_StartTimerSystemTime_0050def0__recomp},
    {"cbTimerHandler", 0x50E250, &recomp_gen::fn_cbTimerHandler_0050e250, &recomp_gen::fn_cbTimerHandler_0050e250__recomp},
    {"_sceCd_cd_read_intr", 0x50F8A8, &recomp_gen::fn__sceCd_cd_read_intr_0050f8a8, &recomp_gen::fn__sceCd_cd_read_intr_0050f8a8__recomp},
    {"sceCdLayerSearchFile", 0x50FC38, &recomp_gen::fn_sceCdLayerSearchFile_0050fc38, &recomp_gen::fn_sceCdLayerSearchFile_0050fc38__recomp},
    {"_sceCd_ncmd_prechk", 0x50FF58, &recomp_gen::fn__sceCd_ncmd_prechk_0050ff58, &recomp_gen::fn__sceCd_ncmd_prechk_0050ff58__recomp},
    {"sceCdNcmdDiskReady", 0x5100B0, &recomp_gen::fn_sceCdNcmdDiskReady_005100b0, &recomp_gen::fn_sceCdNcmdDiskReady_005100b0__recomp},
    {"sceCdSync", 0x510148, &recomp_gen::fn_sceCdSync_00510148, &recomp_gen::fn_sceCdSync_00510148__recomp},
    {"sceCdSyncS", 0x5101E8, &recomp_gen::fn_sceCdSyncS_005101e8, &recomp_gen::fn_sceCdSyncS_005101e8__recomp},
    {"_sceCd_scmd_prechk", 0x510258, &recomp_gen::fn__sceCd_scmd_prechk_00510258, &recomp_gen::fn__sceCd_scmd_prechk_00510258__recomp},
    {"sceCdInit", 0x510460, &recomp_gen::fn_sceCdInit_00510460, &recomp_gen::fn_sceCdInit_00510460__recomp},
    {"sceCdDiskReady", 0x510960, &recomp_gen::fn_sceCdDiskReady_00510960, &recomp_gen::fn_sceCdDiskReady_00510960__recomp},
    {"sceCdRead", 0x510B80, &recomp_gen::fn_sceCdRead_00510b80, &recomp_gen::fn_sceCdRead_00510b80__recomp},
    {"sceCdGetError", 0x510EF0, &recomp_gen::fn_sceCdGetError_00510ef0, &recomp_gen::fn_sceCdGetError_00510ef0__recomp},
    {"sceCdMmode", 0x511040, &recomp_gen::fn_sceCdMmode_00511040, &recomp_gen::fn_sceCdMmode_00511040__recomp},
    {"scePadInit2", 0x5112D0, &recomp_gen::fn_scePadInit2_005112d0, &recomp_gen::fn_scePadInit2_005112d0__recomp},
    {"scePadSetMainMode", 0x511FB8, &recomp_gen::fn_scePadSetMainMode_00511fb8, &recomp_gen::fn_scePadSetMainMode_00511fb8__recomp},
    {"scePadSetActAlign", 0x512138, &recomp_gen::fn_scePadSetActAlign_00512138, &recomp_gen::fn_scePadSetActAlign_00512138__recomp},
    {"scePadGetModVersion", 0x512640, &recomp_gen::fn_scePadGetModVersion_00512640, &recomp_gen::fn_scePadGetModVersion_00512640__recomp},
    {"sceSdRemoteCallbackInit", 0x512D48, &recomp_gen::fn_sceSdRemoteCallbackInit_00512d48, &recomp_gen::fn_sceSdRemoteCallbackInit_00512d48__recomp},
    {"_sdrCBThread", 0x512F80, &recomp_gen::fn__sdrCBThread_00512f80, &recomp_gen::fn__sdrCBThread_00512f80__recomp},
    {"sceMc2SifCallback", 0x51AE38, &recomp_gen::fn_sceMc2SifCallback_0051ae38, &recomp_gen::fn_sceMc2SifCallback_0051ae38__recomp},
    {"sceDbcGetModVersion", 0x51C360, &recomp_gen::fn_sceDbcGetModVersion_0051c360, &recomp_gen::fn_sceDbcGetModVersion_0051c360__recomp},
    {"sceDbcSetWorkAddr", 0x51C700, &recomp_gen::fn_sceDbcSetWorkAddr_0051c700, &recomp_gen::fn_sceDbcSetWorkAddr_0051c700__recomp},
    {"sceDbcCreateSocket", 0x51C770, &recomp_gen::fn_sceDbcCreateSocket_0051c770, &recomp_gen::fn_sceDbcCreateSocket_0051c770__recomp},
    {"sceDbcSendData3", 0x51D308, &recomp_gen::fn_sceDbcSendData3_0051d308, &recomp_gen::fn_sceDbcSendData3_0051d308__recomp},
    {"sceSkSsSOUND_Send", 0x51DBC0, &recomp_gen::fn_sceSkSsSOUND_Send_0051dbc0, &recomp_gen::fn_sceSkSsSOUND_Send_0051dbc0__recomp},
    {"sceSkSsHSYNTH_Bind", 0x51DC70, &recomp_gen::fn_sceSkSsHSYNTH_Bind_0051dc70, &recomp_gen::fn_sceSkSsHSYNTH_Bind_0051dc70__recomp},
    {"sceSkSsHSYNTH_Unbind", 0x51DD48, &recomp_gen::fn_sceSkSsHSYNTH_Unbind_0051dd48, &recomp_gen::fn_sceSkSsHSYNTH_Unbind_0051dd48__recomp},
    {"sceSkSsSESQ_Bind", 0x51DDF0, &recomp_gen::fn_sceSkSsSESQ_Bind_0051ddf0, &recomp_gen::fn_sceSkSsSESQ_Bind_0051ddf0__recomp},
    {"sceSkSsSESQ_Unbind", 0x51DEB0, &recomp_gen::fn_sceSkSsSESQ_Unbind_0051deb0, &recomp_gen::fn_sceSkSsSESQ_Unbind_0051deb0__recomp},
    {"ADXF_SetupRofs", 0x53B220, &recomp_gen::fn_ADXF_SetupRofs_0053b220, &recomp_gen::fn_ADXF_SetupRofs_0053b220__recomp},
    {"ADXF_AddRofsVol", 0x53B2C0, &recomp_gen::fn_ADXF_AddRofsVol_0053b2c0, &recomp_gen::fn_ADXF_AddRofsVol_0053b2c0__recomp},
    {"sub_53B4F8", 0x53B4F8, &recomp_gen::fn_sub_53B4F8_0053b4f8, &recomp_gen::fn_sub_53B4F8_0053b4f8__recomp},
    {"ADXF_LoadPartitionNw", 0x53B868, &recomp_gen::fn_ADXF_LoadPartitionNw_0053b868, &recomp_gen::fn_ADXF_LoadPartitionNw_0053b868__recomp},
    {"sub_53BEF0", 0x53BEF0, &recomp_gen::fn_sub_53BEF0_0053bef0, &recomp_gen::fn_sub_53BEF0_0053bef0__recomp},
    {"sub_53C2A0", 0x53C2A0, &recomp_gen::fn_sub_53C2A0_0053c2a0, &recomp_gen::fn_sub_53C2A0_0053c2a0__recomp},
    {"ADXF_Open", 0x53C910, &recomp_gen::fn_ADXF_Open_0053c910, &recomp_gen::fn_ADXF_Open_0053c910__recomp},
    {"adxf_Open", 0x53C958, &recomp_gen::fn_adxf_Open_0053c958, &recomp_gen::fn_adxf_Open_0053c958__recomp},
    {"ADXF_ReadNw", 0x53D380, &recomp_gen::fn_ADXF_ReadNw_0053d380, &recomp_gen::fn_ADXF_ReadNw_0053d380__recomp},
    {"adxf_ReadNw", 0x53D3D8, &recomp_gen::fn_adxf_ReadNw_0053d3d8, &recomp_gen::fn_adxf_ReadNw_0053d3d8__recomp},
    {"ADXF_ExecServer", 0x53D708, &recomp_gen::fn_ADXF_ExecServer_0053d708, &recomp_gen::fn_ADXF_ExecServer_0053d708__recomp},
    {"adxf_ExecServer", 0x53D730, &recomp_gen::fn_adxf_ExecServer_0053d730, &recomp_gen::fn_adxf_ExecServer_0053d730__recomp},
    {"ADXF_GetFsizeSct", 0x53D968, &recomp_gen::fn_ADXF_GetFsizeSct_0053d968, &recomp_gen::fn_ADXF_GetFsizeSct_0053d968__recomp},
    {"ADXF_GetStat", 0x53DB90, &recomp_gen::fn_ADXF_GetStat_0053db90, &recomp_gen::fn_ADXF_GetStat_0053db90__recomp},
    {"DTX_Init", 0x559AA8, &recomp_gen::fn_DTX_Init_00559aa8, &recomp_gen::fn_DTX_Init_00559aa8__recomp},
    {"dvCiCdSearchFile", 0x559DD8, &recomp_gen::fn_dvCiCdSearchFile_00559dd8, &recomp_gen::fn_dvCiCdSearchFile_00559dd8__recomp},
    {"sub_594038", 0x594038, &recomp_gen::fn_sub_594038_00594038, &recomp_gen::fn_sub_594038_00594038__recomp},
    {"sub_5940A0", 0x5940A0, &recomp_gen::fn_sub_5940A0_005940a0, &recomp_gen::fn_sub_5940A0_005940a0__recomp},
};

// The world: 64 KiB of free RAM above the harness's arena (random worlds), and a record / out area for the snapshot runs.
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 64;
constexpr u32 kRec = 0x01820000u;  // a built record of small values / pointers back into it (8 KiB)
constexpr u32 kOut = 0x01822000u;  // out-parameters (8 KiB)
const char* const kSnaps[] = {"dorm_replay_4900", "b_5800", "climb_ref_17000", "fusion_ref_6300", "shop_ref_4100"};

// The game's state these bodies read (from the instructions and symbols/).
constexpr u32 kAdxfHandles = 0x784A60u;  // the 16 ADXF handles, 68 bytes each (adxf_ExecServer's walk)
constexpr u32 kCdNcmdClient = 0x781D50u; // libcdvd's N-command RPC client data (sceCdSync's sceSifCheckStatRpc)
constexpr u32 kCdvdCache = 0x7D6F80u;    // sCdvdCache: 256 entries of 148 bytes (H_Cdvd_InitCd's loop)
constexpr u32 kSndBanks = 0x833710u;     // the sound-bank slots of H_Sndcom_Update
constexpr u32 kHeapEnd = 0x77F494u;      // sbrk's current heap end

u32 r32(Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.at(va), 4);
    return v;
}
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }

const Case& by_name(const char* name) {
    for (const Case& c : kCases)
        if (std::string(c.name) == name) return c;
    FAIL("no case " << name);
    return kCases[0];
}

// One pair on a long-lived BaseRange (write_tracker.h): the snapshot's 32 MiB stay the base and restore() copies back
// only the pages a pair wrote. The comparison is hgp::pair's.
hgp::Run pr_base(Machine& m, BaseRange& ram, const Case& c, const Args& args, u32 seed) {
    const std::vector<u8> spr(m.mem.scratchpad(), m.mem.scratchpad() + 0x4000);
    ram.begin();
    hgp::Run h = hgp::run_one(m, c.hand, args, seed, {});
    std::vector<u8> bios_h;
    if (!hgp::bios_clean(m)) {
        bios_h.assign(m.mem.bios(), m.mem.bios() + EEMemory::kBiosSize);
        std::memset(m.mem.bios(), 0, EEMemory::kBiosSize);
    }
    ram.between();
    std::memcpy(m.mem.scratchpad(), spr.data(), spr.size());
    hgp::Run r = hgp::run_one(m, c.recomp, args, seed, {});
    const bool bios_r = !hgp::bios_clean(m);
    INFO(c.name << " a0=" << hex64(args[0]) << " a1=" << hex64(args[1]) << " a2=" << hex64(args[2]) << " a3=" << hex64(args[3])
                << " seed=" << seed << (r.stopped ? " (recomp stopped: " + r.what + " at " + hex64(r.stop_pc) + ")" : std::string()));
    CHECK(bios_r == !bios_h.empty());
    if (bios_r) std::memset(m.mem.bios(), 0, EEMemory::kBiosSize);
    CHECK(h.stopped == r.stopped);
    CHECK(h.stop_pc == r.stop_pc);
    CHECK(h.what == r.what);
    CHECK(h.syscalls == r.syscalls);
    CHECK(h.snaps.size() == r.snaps.size());
    for (std::size_t i = 0; i < std::min(h.snaps.size(), r.snaps.size()); ++i) {
        const std::string d = hgp::diff(h.snaps[i], r.snaps[i]);
        if (!d.empty()) {
            INFO("check point " << i << ": " << d);
            CHECK(false);
            break;
        }
    }
    {
        const std::string d = hgp::diff(h.end, r.end);
        INFO((r.stopped ? "at the stop: " : "at the return: ") << d);
        CHECK(d.empty());
    }
    if (const std::size_t first = ram.first_difference(); first != ram.size()) {
        INFO("main RAM: first differing byte at " << hex64(first));
        CHECK(false);
    }
    CHECK(h.spr == r.spr);
    CHECK(h.bus.size() == r.bus.size());
    for (std::size_t i = 0; i < std::min(h.bus.size(), r.bus.size()); ++i) {
        const auto &x = h.bus[i], &y = r.bus[i];
        if (x.write != y.write || x.bits != y.bits || x.pa != y.pa || x.lo != y.lo || x.hi != y.hi) {
            INFO("bus access " << i << " differs");
            CHECK(false);
            break;
        }
    }
    CHECK(h.vu_control == r.vu_control);
    return r;
}

// The first used ADXF handle of a snapshot (state byte != 0), else the first handle.
u32 adxf_handle(Machine& m) {
    for (u32 i = 0; i < 16; ++i)
        if (m.at(kAdxfHandles + 68 * i)[0] != 0) return kAdxfHandles + 68 * i;
    return kAdxfHandles;
}

const hgp::Run* find_write(const hgp::Run& r, u32 pa, u64* value) {
    for (const auto& a : r.bus)
        if (a.write && a.pa == pa) {
            *value = a.lo;
            return &r;
        }
    return nullptr;
}

}  // namespace

TEST_CASE("game(libs24): every body equals its recompiled body on random worlds") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const char* env = std::getenv("P3FES_HG_SEEDS");  // more (or fewer) pairs per function
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : kSeeds;
    const char* only = std::getenv("P3FES_HG_ONLY");     // one function by name (debugging)
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;  // name and seed of every pair on stderr
    int total = 0, stops = 0;
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s seed %u\n", c.name, seed);
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(*m, kWorld, kWorldSize, rng);
            const Args args{hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize),
                            hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize)};
            stops += hgp::pair(*m, c.hand, c.recomp, args, seed, c.name).stopped ? 1 : 0;
            ++total;
        }
    }
    MESSAGE(total << " pairs, " << stops << " stopped early (identically)");
}

// The replay snapshots hold the libraries as the game leaves them after boot: the SIF RPC client and server state,
// libcdvd's clients and semaphores, the ADXF handles and AFS partition state, the H_Cdvd request list and cache, the
// sound-bank slots, the heap end. Every body runs on each snapshot with a0 from those records (and null and a built
// record), a1 from the values its branches test, and out pointers in a2 / a3; each pair starts from the snapshot.
TEST_CASE("game(libs24): every body on the replay snapshots' library state") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const char* only = std::getenv("P3FES_HG_ONLY");
    int runs = 0, stops = 0, snaps = 0;
    for (const char* dir : kSnaps) {
        const std::vector<u8> snap = read_snapshot(dir);
        if (snap.size() != EEMemory::kMainRamSize) {
            MESSAGE("SKIP: snapshot " << dir << " not found");
            continue;
        }
        ++snaps;
        std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
        std::memset(m->at(kRec), 0, 0x4000);
        for (u32 i = 0; i < 0x2000; i += 4) w32(*m, kRec + i, (i / 4) % 5 == 0 ? kRec + ((i * 7) & 0x1FF0u) : (i / 4) % 7);
        const u32 adxf = adxf_handle(*m);
        const std::vector<std::pair<u32, u64>> sets = {
            {0u, 0ull}, {kRec, 1ull}, {adxf, 2ull}, {kCdNcmdClient, u64{kOut}}, {kCdvdCache, 0x10ull}, {kSndBanks, ~0ull}};
        BaseRange base(m->mem.main_ram(), m->mem.main_ram() + EEMemory::kMainRamSize);
        for (const Case& c : kCases) {
            if (only && std::string(only) != c.name) continue;
            u32 seed = 1;
            for (const auto& [a0, a1] : sets) {
                const hgp::Run r = pr_base(*m, base, c, Args{sx(a0), a1, sx(kOut + 0x100), sx(kOut + 0x200)}, seed++);
                base.restore();
                ++runs;
                stops += r.stopped ? 1 : 0;
            }
        }
    }
    std::memset(m->mem.main_ram(), 0, EEMemory::kMainRamSize);
    MESSAGE(runs << " pairs from " << snaps << " snapshots, " << stops << " stopped identically");
}

// Documented rules on the host, from the instructions (both bodies run and are compared, then the result checked).
// Only bodies whose checked effect comes before any callee another slice may replace.
TEST_CASE("game(libs24): syscall numbers, timer / DMA register stores, T0 read, V-blank wait and sbrk rules") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const auto v0 = [](const hgp::Run& r) { return r.end.gpr[GPR_V0].u64[0]; };
    const auto v1 = [](const hgp::Run& r) { return r.end.gpr[GPR_V1].u64[0]; };
    // The kernel syscall wrappers: one syscall with its number in $v1 (the harness answers 0x600DF00D in $v0).
    {
        const std::pair<const char*, s32> calls[] = {
            {"_sceAddIntcHandler_0", 16}, {"_sceAddDmacHandler", 18}, {"_sceAddDmacHandler_0", 18}, {"_sce_EnableIntc", 20},
            {"_sce_EnableDmac", 22}, {"_sce_DisableDmac", 23}, {"_sceStartThread", 34}, {"_sceiReferThreadStatus", -49},
            {"_sce_iWakeupThread", -52}, {"_sceEndOfHeap", 62}, {"_scePollSema", 69}, {"_sceSetOsdConfigParam", 74},
            {"_sceGetOsdConfigParam", 75}, {"_sceFlushCache", 100}, {"_sceSifStopDma", 107}, {"_sceGsPutIMR", 113},
            {"_sceSifDmaStat", 118}, {"_sceSifSetDma", 119}, {"_sceSifSetDChain", 120}, {"_isceSifSetDChain", -120},
            {"_sceSifSetReg", 121}, {"_sceSifGetReg", 122}, {"_sceCopy", 90}, {"_sceGetEntryAddress", 91},
            {"_sceSetSyscall", 116}, {"_sceFindAddress", 131}, {"_sceSetSyscall_0", 116}, {"_sceSetSyscall_3", 116},
            {"_sceCopy_3", 90}, {"_sceGetEntryAddress_1", 91}};
        for (const auto& [name, num] : calls) {
            const Case& c = by_name(name);
            const hgp::Run r = hgp::pair(*m, c.hand, c.recomp, Args{1, 2, 3, 4}, 1, c.name);
            INFO(name);
            CHECK_FALSE(r.stopped);
            CHECK(r.syscalls == 1);
            CHECK(v1(r) == sx(static_cast<u32>(num)));
            CHECK(v0(r) == 0x600DF00Du);
        }
    }
    // Y_Misc_GetT0Count: T0_COUNT (0x10000000) in $v0.
    {
        const Case& c = by_name("Y_Misc_GetT0Count");
        HwCheck hw;
        hw.regs[0x10000000u] = 0x1234u;
        const hgp::Run r = hgp::pair(*m, c.hand, c.recomp, Args{0, 0, 0, 0}, 1, c.name, hw);
        CHECK_FALSE(r.stopped);
        CHECK((v0(r) & 0xFFFFFFFFu) == 0x1234u);
    }
    // sub_50DC80 / 90 / A0: a0 stored to T2_COUNT / T2_MODE / T2_COMP (through kseg1).
    for (const auto& [name, pa] : {std::pair<const char*, u32>{"sub_50DC80", 0x10001000u}, {"sub_50DC90", 0x10001010u}, {"sub_50DCA0", 0x10001020u}}) {
        const Case& c = by_name(name);
        const hgp::Run r = hgp::pair(*m, c.hand, c.recomp, Args{0x83, 0, 0, 0}, 1, c.name);
        u64 value = 0;
        INFO(name);
        CHECK(find_write(r, pa, &value) != nullptr);
        CHECK((value & 0xFFFFFFFFu) == 0x83u);
    }
    // sub_594038 / sub_5940A0: the DMAC suspended (D_ENABLEW = D_ENABLER | 0x10000), a0 to D3_CHCR / D4_CHCR, then the
    // DMAC resumed (D_ENABLEW = D_ENABLER & ~0x10000), in that order.
    for (const auto& [name, pa] : {std::pair<const char*, u32>{"sub_594038", 0x1000B000u}, {"sub_5940A0", 0x1000B400u}}) {
        const Case& c = by_name(name);
        HwCheck hw;
        hw.regs[0x1000F520u] = 0x00011201u;
        const hgp::Run r = hgp::pair(*m, c.hand, c.recomp, Args{0x101, 0, 0, 0}, 1, c.name, hw);
        INFO(name);
        CHECK_FALSE(r.stopped);
        std::vector<std::pair<u32, u32>> writes;
        for (const auto& a : r.bus)
            if (a.write) writes.emplace_back(static_cast<u32>(a.pa), static_cast<u32>(a.lo));
        REQUIRE(writes.size() == 3u);
        CHECK(writes[0] == std::pair<u32, u32>{0x1000F590u, 0x00011201u});
        CHECK(writes[1] == std::pair<u32, u32>{pa, 0x101u});
        CHECK(writes[2] == std::pair<u32, u32>{0x1000F590u, 0x00001201u});
    }
    // VSync: acknowledge INTC_STAT bit 2, spin until it is set, acknowledge again.
    {
        const Case& c = by_name("VSync");
        HwCheck hw;
        hw.reads[0x1000F000u] = {0, 0, 4};
        const hgp::Run r = hgp::pair(*m, c.hand, c.recomp, Args{0, 0, 0, 0}, 1, c.name, hw);
        CHECK_FALSE(r.stopped);
        int acks = 0;
        for (const auto& a : r.bus)
            if (a.write && a.pa == 0x1000F000u && (a.lo & 0xFFFFFFFFu) == 4u) ++acks;
        CHECK(acks == 2);
    }
    // sbrk: the heap end moves by a0 while it stays under EndOfHeap (the harness answers 0x600DF00D); returns the old end.
    {
        const Case& c = by_name("sbrk");
        w32(*m, kHeapEnd, 0x01000000u);
        const hgp::Run r = hgp::pair(*m, c.hand, c.recomp, Args{0x100, 0, 0, 0}, 1, c.name);
        CHECK_FALSE(r.stopped);
        CHECK(v0(r) == 0x01000000u);
        CHECK(r32(*m, kHeapEnd) == 0x01000100u);
    }
}

#else

TEST_CASE("game(libs24): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
