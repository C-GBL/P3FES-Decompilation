// Pair tests for slice libs25 (skeleton written by p3fes_handgen; docs/PHASE5_AGENT_BRIEF.md "Using p3fes_handgen").
// Every body against its recompiled body, compared by tests/game/handgen_pairs.h: the whole register file and cycle
// count at every check point and at the return / stop, all 32 MiB of RAM (the dead stack included), the scratchpad,
// the BIOS window and the bus log (every hardware-register access, direction, width, address and value).
// Four sets: the skeleton's random worlds; the same worlds on idle hardware (the DMA channels' CHCR read 0, D_STAT reads
// every channel done, the GS CSR and the VIF / GIF status read idle), so the DMA kernels, the sceDma / sceGs / IPU
// routines and the RW DMA ring get past their wait loops; the replay snapshots (the RW DMA ring and Sky state, the ROFS
// work area with its handles and volumes, the PS2RNA / DTR tables) with a0 from those records; and rule checks
// (the kernel stubs' call numbers, the 2D flag normalisation, the RPC packet pool, the DMA pre-allocation, the
// scratchpad fill).
// The G callees (SIF RPC, sceCd, the libmpeg / ROFS helpers) are all claimed by packets libs24 / libs26: they are never
// stood in here and no check depends on where a pair stops.
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/libs25.h"

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <random>
#include <string>
#include <vector>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;

namespace p3fes::recomp_gen {
void fn__sceExitThread_00100220(EEContext&);  // generated body
void fn__sceExitThread_00100220__recomp(EEContext&);  // recompiled
void fn_H_FileSetup_UpdateTstDvdChkDrawTask_001934f0(EEContext&);  // generated body
void fn_H_FileSetup_UpdateTstDvdChkDrawTask_001934f0__recomp(EEContext&);  // recompiled
void fn_sub_344EB0_00344eb0(EEContext&);  // generated body
void fn_sub_344EB0_00344eb0__recomp(EEContext&);  // recompiled
void fn_sub_344FC0_00344fc0(EEContext&);  // generated body
void fn_sub_344FC0_00344fc0__recomp(EEContext&);  // recompiled
void fn_sub_46F400_0046f400(EEContext&);  // generated body
void fn_sub_46F400_0046f400__recomp(EEContext&);  // recompiled
void fn_sub_470200_00470200(EEContext&);  // generated body
void fn_sub_470200_00470200__recomp(EEContext&);  // recompiled
void fn_sub_470E10_00470e10(EEContext&);  // generated body
void fn_sub_470E10_00470e10__recomp(EEContext&);  // recompiled
void fn_sub_473FB0_00473fb0(EEContext&);  // generated body
void fn_sub_473FB0_00473fb0__recomp(EEContext&);  // recompiled
void fn_sub_474D30_00474d30(EEContext&);  // generated body
void fn_sub_474D30_00474d30__recomp(EEContext&);  // recompiled
void fn_sub_476490_00476490(EEContext&);  // generated body
void fn_sub_476490_00476490__recomp(EEContext&);  // recompiled
void fn_sub_476980_00476980(EEContext&);  // generated body
void fn_sub_476980_00476980__recomp(EEContext&);  // recompiled
void fn_sub_47A510_0047a510(EEContext&);  // generated body
void fn_sub_47A510_0047a510__recomp(EEContext&);  // recompiled
void fn_sub_47A710_0047a710(EEContext&);  // generated body
void fn_sub_47A710_0047a710__recomp(EEContext&);  // recompiled
void fn_sub_47C240_0047c240(EEContext&);  // generated body
void fn_sub_47C240_0047c240__recomp(EEContext&);  // recompiled
void fn_sub_47C8C0_0047c8c0(EEContext&);  // generated body
void fn_sub_47C8C0_0047c8c0__recomp(EEContext&);  // recompiled
void fn_sub_47CFD0_0047cfd0(EEContext&);  // generated body
void fn_sub_47CFD0_0047cfd0__recomp(EEContext&);  // recompiled
void fn_sub_47DE30_0047de30(EEContext&);  // generated body
void fn_sub_47DE30_0047de30__recomp(EEContext&);  // recompiled
void fn_sub_47E9E0_0047e9e0(EEContext&);  // generated body
void fn_sub_47E9E0_0047e9e0__recomp(EEContext&);  // recompiled
void fn_sub_47FB10_0047fb10(EEContext&);  // generated body
void fn_sub_47FB10_0047fb10__recomp(EEContext&);  // recompiled
void fn_sub_480C30_00480c30(EEContext&);  // generated body
void fn_sub_480C30_00480c30__recomp(EEContext&);  // recompiled
void fn_sub_481860_00481860(EEContext&);  // generated body
void fn_sub_481860_00481860__recomp(EEContext&);  // recompiled
void fn_sub_482A50_00482a50(EEContext&);  // generated body
void fn_sub_482A50_00482a50__recomp(EEContext&);  // recompiled
void fn_sub_483170_00483170(EEContext&);  // generated body
void fn_sub_483170_00483170__recomp(EEContext&);  // recompiled
void fn_sub_4838E0_004838e0(EEContext&);  // generated body
void fn_sub_4838E0_004838e0__recomp(EEContext&);  // recompiled
void fn_sub_485750_00485750(EEContext&);  // generated body
void fn_sub_485750_00485750__recomp(EEContext&);  // recompiled
void fn_sub_490D40_00490d40(EEContext&);  // generated body
void fn_sub_490D40_00490d40__recomp(EEContext&);  // recompiled
void fn_sub_49CC30_0049cc30(EEContext&);  // generated body
void fn_sub_49CC30_0049cc30__recomp(EEContext&);  // recompiled
void fn_sub_4C08A0_004c08a0(EEContext&);  // generated body
void fn_sub_4C08A0_004c08a0__recomp(EEContext&);  // recompiled
void fn_sub_4C0A70_004c0a70(EEContext&);  // generated body
void fn_sub_4C0A70_004c0a70__recomp(EEContext&);  // recompiled
void fn_sub_4C0A80_004c0a80(EEContext&);  // generated body
void fn_sub_4C0A80_004c0a80__recomp(EEContext&);  // recompiled
void fn_sub_4C0C50_004c0c50(EEContext&);  // generated body
void fn_sub_4C0C50_004c0c50__recomp(EEContext&);  // recompiled
void fn_sub_4C0CF0_004c0cf0(EEContext&);  // generated body
void fn_sub_4C0CF0_004c0cf0__recomp(EEContext&);  // recompiled
void fn_sub_4C0E70_004c0e70(EEContext&);  // generated body
void fn_sub_4C0E70_004c0e70__recomp(EEContext&);  // recompiled
void fn__dispRefImageField_0_004c72e0(EEContext&);  // generated body
void fn__dispRefImageField_0_004c72e0__recomp(EEContext&);  // recompiled
void fn__rwDMAHandler_004d4350(EEContext&);  // generated body
void fn__rwDMAHandler_004d4350__recomp(EEContext&);  // recompiled
void fn__rwDMAVSYNCHandler_004d47f0(EEContext&);  // generated body
void fn__rwDMAVSYNCHandler_004d47f0__recomp(EEContext&);  // recompiled
void fn__rwDMAClosePkt_004d4a60(EEContext&);  // generated body
void fn__rwDMAClosePkt_004d4a60__recomp(EEContext&);  // recompiled
void fn__rwDMAForceBufferSwap_004d4df0(EEContext&);  // generated body
void fn__rwDMAForceBufferSwap_004d4df0__recomp(EEContext&);  // recompiled
void fn__rwDMAAddPkt_004d5000(EEContext&);  // generated body
void fn__rwDMAAddPkt_004d5000__recomp(EEContext&);  // recompiled
void fn__rwDMAAddPURef_004d51c0(EEContext&);  // generated body
void fn__rwDMAAddPURef_004d51c0__recomp(EEContext&);  // recompiled
void fn__rwDMAOpenGIFPkt_004d54e0(EEContext&);  // generated body
void fn__rwDMAOpenGIFPkt_004d54e0__recomp(EEContext&);  // recompiled
void fn__rwDMAOpenVIFPkt_004d59d0(EEContext&);  // generated body
void fn__rwDMAOpenVIFPkt_004d59d0__recomp(EEContext&);  // recompiled
void fn_sub_4D5E90_004d5e90(EEContext&);  // generated body
void fn_sub_4D5E90_004d5e90__recomp(EEContext&);  // recompiled
void fn_sub_4D5FE0_004d5fe0(EEContext&);  // generated body
void fn_sub_4D5FE0_004d5fe0__recomp(EEContext&);  // recompiled
void fn_sub_4D6250_004d6250(EEContext&);  // generated body
void fn_sub_4D6250_004d6250__recomp(EEContext&);  // recompiled
void fn__rwDMAHook_004d6470(EEContext&);  // generated body
void fn__rwDMAHook_004d6470__recomp(EEContext&);  // recompiled
void fn__rwDMAUnhook_004d65a0(EEContext&);  // generated body
void fn__rwDMAUnhook_004d65a0__recomp(EEContext&);  // recompiled
void fn__rwDMADmaOpen_004d67b0(EEContext&);  // generated body
void fn__rwDMADmaOpen_004d67b0__recomp(EEContext&);  // recompiled
void fn__rwDMADmaClose_004d6a50(EEContext&);  // generated body
void fn__rwDMADmaClose_004d6a50__recomp(EEContext&);  // recompiled
void fn__rwDMAPreAlloc_004d6ab0(EEContext&);  // generated body
void fn__rwDMAPreAlloc_004d6ab0__recomp(EEContext&);  // recompiled
void fn__rwSkyInitConfigSystem_004d6b10(EEContext&);  // generated body
void fn__rwSkyInitConfigSystem_004d6b10__recomp(EEContext&);  // recompiled
void fn_setInitialRenderState_004dfdd0(EEContext&);  // generated body
void fn_setInitialRenderState_004dfdd0__recomp(EEContext&);  // recompiled
void fn_SkyOpen_004e01b0(EEContext&);  // generated body
void fn_SkyOpen_004e01b0__recomp(EEContext&);  // recompiled
void fn_sub_4E0540_004e0540(EEContext&);  // generated body
void fn_sub_4E0540_004e0540__recomp(EEContext&);  // recompiled
void fn_SkyStart_004e1060(EEContext&);  // generated body
void fn_SkyStart_004e1060__recomp(EEContext&);  // recompiled
void fn_sub_4E3630_004e3630(EEContext&);  // generated body
void fn_sub_4E3630_004e3630__recomp(EEContext&);  // recompiled
void fn_sub_4EC510_004ec510(EEContext&);  // generated body
void fn_sub_4EC510_004ec510__recomp(EEContext&);  // recompiled
void fn__rwSkyOverloadPipelines_004eebc0(EEContext&);  // generated body
void fn__rwSkyOverloadPipelines_004eebc0__recomp(EEContext&);  // recompiled
void fn_sub_4F0990_004f0990(EEContext&);  // generated body
void fn_sub_4F0990_004f0990__recomp(EEContext&);  // recompiled
void fn_sceGsResetGraph_004f8eb0(EEContext&);  // generated body
void fn_sceGsResetGraph_004f8eb0__recomp(EEContext&);  // recompiled
void fn_sceGsResetPath_004f9050(EEContext&);  // generated body
void fn_sceGsResetPath_004f9050__recomp(EEContext&);  // recompiled
void fn_sceGsPutDispEnv_004f94e0(EEContext&);  // generated body
void fn_sceGsPutDispEnv_004f94e0__recomp(EEContext&);  // recompiled
void fn_sceGsPutDrawEnv_004f9850(EEContext&);  // generated body
void fn_sceGsPutDrawEnv_004f9850__recomp(EEContext&);  // recompiled
void fn_sceGsSyncV_004f9938(EEContext&);  // generated body
void fn_sceGsSyncV_004f9938__recomp(EEContext&);  // recompiled
void fn_sceGsSyncPath_004f99d0(EEContext&);  // generated body
void fn_sceGsSyncPath_004f99d0__recomp(EEContext&);  // recompiled
void fn_sceGsExecStoreImage_004f9e28(EEContext&);  // generated body
void fn_sceGsExecStoreImage_004f9e28__recomp(EEContext&);  // recompiled
void fn_sceGsSyncVCallback_004fa4b8(EEContext&);  // generated body
void fn_sceGsSyncVCallback_004fa4b8__recomp(EEContext&);  // recompiled
void fn_sceGsSwapDBuffDc_004fa738(EEContext&);  // generated body
void fn_sceGsSwapDBuffDc_004fa738__recomp(EEContext&);  // recompiled
void fn_WaitDma_004fa798(EEContext&);  // generated body
void fn_WaitDma_004fa798__recomp(EEContext&);  // recompiled
void fn_WatchDma_004fa808(EEContext&);  // generated body
void fn_WatchDma_004fa808__recomp(EEContext&);  // recompiled
void fn_sceDmaReset_004fa918(EEContext&);  // generated body
void fn_sceDmaReset_004fa918__recomp(EEContext&);  // recompiled
void fn_sceDmaPutEnv_004fa9f8(EEContext&);  // generated body
void fn_sceDmaPutEnv_004fa9f8__recomp(EEContext&);  // recompiled
void fn_sceDmaSend_004fac20(EEContext&);  // generated body
void fn_sceDmaSend_004fac20__recomp(EEContext&);  // recompiled
void fn_sceDmaSendN_004fac88(EEContext&);  // generated body
void fn_sceDmaSendN_004fac88__recomp(EEContext&);  // recompiled
void fn_sceDmaRecvN_004fadc0(EEContext&);  // generated body
void fn_sceDmaRecvN_004fadc0__recomp(EEContext&);  // recompiled
void fn_sceDmaSync_004faec0(EEContext&);  // generated body
void fn_sceDmaSync_004faec0__recomp(EEContext&);  // recompiled
void fn_sceDmaPause_004faf30(EEContext&);  // generated body
void fn_sceDmaPause_004faf30__recomp(EEContext&);  // recompiled
void fn__motionVectors_004fcb00(EEContext&);  // generated body
void fn__motionVectors_004fcb00__recomp(EEContext&);  // recompiled
void fn_sub_4FD8A0_004fd8a0(EEContext&);  // generated body
void fn_sub_4FD8A0_004fd8a0__recomp(EEContext&);  // recompiled
void fn__pictureTemporalScalableExtension_004ff7b8(EEContext&);  // generated body
void fn__pictureTemporalScalableExtension_004ff7b8__recomp(EEContext&);  // recompiled
void fn__ch4dma_00502418(EEContext&);  // generated body
void fn__ch4dma_00502418__recomp(EEContext&);  // recompiled
void fn__sceMpegStopIpuDma_00502500(EEContext&);  // generated body
void fn__sceMpegStopIpuDma_00502500__recomp(EEContext&);  // recompiled
void fn__sceMpegErrorBdec_005025a0(EEContext&);  // generated body
void fn__sceMpegErrorBdec_005025a0__recomp(EEContext&);  // recompiled
void fn_setD3_CHCR_00502700(EEContext&);  // generated body
void fn_setD3_CHCR_00502700__recomp(EEContext&);  // recompiled
void fn_setD4_CHCR_00502778(EEContext&);  // generated body
void fn_setD4_CHCR_00502778__recomp(EEContext&);  // recompiled
void fn_sceIpuStopDMA_005027f0(EEContext&);  // generated body
void fn_sceIpuStopDMA_005027f0__recomp(EEContext&);  // recompiled
void fn_sceIpuRestartDMA_005028d8(EEContext&);  // generated body
void fn_sceIpuRestartDMA_005028d8__recomp(EEContext&);  // recompiled
void fn__sce_ExecPS2_00502db0(EEContext&);  // generated body
void fn__sce_ExecPS2_00502db0__recomp(EEContext&);  // recompiled
void fn__sce_DisableIntc_00502eb0(EEContext&);  // generated body
void fn__sce_DisableIntc_00502eb0__recomp(EEContext&);  // recompiled
void fn__sce_iEnableIntc_00502f00(EEContext&);  // generated body
void fn__sce_iEnableIntc_00502f00__recomp(EEContext&);  // recompiled
void fn__sce_iDisableIntc_00502f10(EEContext&);  // generated body
void fn__sce_iDisableIntc_00502f10__recomp(EEContext&);  // recompiled
void fn__sce_iEnableDmac_00502f20(EEContext&);  // generated body
void fn__sce_iEnableDmac_00502f20__recomp(EEContext&);  // recompiled
void fn__sce_iDisableDmac_00502f30(EEContext&);  // generated body
void fn__sce_iDisableDmac_00502f30__recomp(EEContext&);  // recompiled
void fn__sceDeleteThread_00502f70(EEContext&);  // generated body
void fn__sceDeleteThread_00502f70__recomp(EEContext&);  // recompiled
void fn__sceTerminateThread_00502fb0(EEContext&);  // generated body
void fn__sceTerminateThread_00502fb0__recomp(EEContext&);  // recompiled
void fn__sceiChangeThreadPriority_00503000(EEContext&);  // generated body
void fn__sceiChangeThreadPriority_00503000__recomp(EEContext&);  // recompiled
void fn__sceRotateThreadReadyQueue_00503010(EEContext&);  // generated body
void fn__sceRotateThreadReadyQueue_00503010__recomp(EEContext&);  // recompiled
void fn__sce_iSuspendThread_005030e0(EEContext&);  // generated body
void fn__sce_iSuspendThread_005030e0__recomp(EEContext&);  // recompiled
void fn__sceGsGetIMR_00503480(EEContext&);  // generated body
void fn__sceGsGetIMR_00503480__recomp(EEContext&);  // recompiled
void fn__sceSetVSyncFlag_005034d0(EEContext&);  // generated body
void fn__sceSetVSyncFlag_005034d0__recomp(EEContext&);  // recompiled
void fn__isceSifSetDma_00503530(EEContext&);  // generated body
void fn__isceSifSetDma_00503530__recomp(EEContext&);  // recompiled
void fn__sceGetMemorySize_005035c0(EEContext&);  // generated body
void fn__sceGetMemorySize_005035c0__recomp(EEContext&);  // recompiled
void fn__sce_InitTLB_005035d0(EEContext&);  // generated body
void fn__sce_InitTLB_005035d0__recomp(EEContext&);  // recompiled
void fn_VSync2_00503680(EEContext&);  // generated body
void fn_VSync2_00503680__recomp(EEContext&);  // recompiled
void fn_DisableIntc_00503c40(EEContext&);  // generated body
void fn_DisableIntc_00503c40__recomp(EEContext&);  // recompiled
void fn_DelayThread_005041d8(EEContext&);  // generated body
void fn_DelayThread_005041d8__recomp(EEContext&);  // recompiled
void fn__sceRpcGetFPacket2_00506b68(EEContext&);  // generated body
void fn__sceRpcGetFPacket2_00506b68__recomp(EEContext&);  // recompiled
void fn_sceFsSifCallRpc_00507ad8(EEContext&);  // generated body
void fn_sceFsSifCallRpc_00507ad8__recomp(EEContext&);  // recompiled
void fn_sceSifFreeIopHeap_0050b788(EEContext&);  // generated body
void fn_sceSifFreeIopHeap_0050b788__recomp(EEContext&);  // recompiled
void fn__sceSifLoadModuleBuffer_0050bcb0(EEContext&);  // generated body
void fn__sceSifLoadModuleBuffer_0050bcb0__recomp(EEContext&);  // recompiled
void fn__sceSifLoadElfPart_0050c528(EEContext&);  // generated body
void fn__sceSifLoadElfPart_0050c528__recomp(EEContext&);  // recompiled
void fn__kDebugException_0050d280(EEContext&);  // generated body
void fn__kDebugException_0050d280__recomp(EEContext&);  // recompiled
void fn_sceCdGetDiskType2_00510e30(EEContext&);  // generated body
void fn_sceCdGetDiskType2_00510e30__recomp(EEContext&);  // recompiled
void fn_sceDbcDeleteSocket_0051c8a0(EEContext&);  // generated body
void fn_sceDbcDeleteSocket_0051c8a0__recomp(EEContext&);  // recompiled
void fn_adxt_ExecFsSvr_0053e0e0(EEContext&);  // generated body
void fn_adxt_ExecFsSvr_0053e0e0__recomp(EEContext&);  // recompiled
void fn_adxm_fs_proc_0053fcf8(EEContext&);  // generated body
void fn_adxm_fs_proc_0053fcf8__recomp(EEContext&);  // recompiled
void fn_SRD_ReqRdDvd_00557b80(EEContext&);  // generated body
void fn_SRD_ReqRdDvd_00557b80__recomp(EEContext&);  // recompiled
void fn_srd_check_dvd_error_00557fe8(EEContext&);  // generated body
void fn_srd_check_dvd_error_00557fe8__recomp(EEContext&);  // recompiled
void fn_sub_558DD0_00558dd0(EEContext&);  // generated body
void fn_sub_558DD0_00558dd0__recomp(EEContext&);  // recompiled
void fn_DTR_ExecServer_00559140(EEContext&);  // generated body
void fn_DTR_ExecServer_00559140__recomp(EEContext&);  // recompiled
void fn_DTR_Stop_005593a8(EEContext&);  // generated body
void fn_DTR_Stop_005593a8__recomp(EEContext&);  // recompiled
void fn_sub_559938_00559938(EEContext&);  // generated body
void fn_sub_559938_00559938__recomp(EEContext&);  // recompiled
void fn_sub_55F748_0055f748(EEContext&);  // generated body
void fn_sub_55F748_0055f748__recomp(EEContext&);  // recompiled
void fn_PS2RNA_Init_0055ff70(EEContext&);  // generated body
void fn_PS2RNA_Init_0055ff70__recomp(EEContext&);  // recompiled
void fn_sub_564528_00564528(EEContext&);  // generated body
void fn_sub_564528_00564528__recomp(EEContext&);  // recompiled
void fn_RFHN_WaitCompleteReq_005658b8(EEContext&);  // generated body
void fn_RFHN_WaitCompleteReq_005658b8__recomp(EEContext&);  // recompiled
void fn_rfmai_addVolList_005672c8(EEContext&);  // generated body
void fn_rfmai_addVolList_005672c8__recomp(EEContext&);  // recompiled
void fn_rfmai_getCvmfInfo_005674c0(EEContext&);  // generated body
void fn_rfmai_getCvmfInfo_005674c0__recomp(EEContext&);  // recompiled
void fn_rfmai_readPvd_005676b0(EEContext&);  // generated body
void fn_rfmai_readPvd_005676b0__recomp(EEContext&);  // recompiled
void fn_sub_567AF0_00567af0(EEContext&);  // generated body
void fn_sub_567AF0_00567af0__recomp(EEContext&);  // recompiled
void fn_RFMAI_MountG_00567c58(EEContext&);  // generated body
void fn_RFMAI_MountG_00567c58__recomp(EEContext&);  // recompiled
void fn_sub_568098_00568098(EEContext&);  // generated body
void fn_sub_568098_00568098__recomp(EEContext&);  // recompiled
void fn_RFMAI_SetDefVolumeG_00568280(EEContext&);  // generated body
void fn_RFMAI_SetDefVolumeG_00568280__recomp(EEContext&);  // recompiled
void fn_RFMAI_OpenG_00568388(EEContext&);  // generated body
void fn_RFMAI_OpenG_00568388__recomp(EEContext&);  // recompiled
void fn_RFMAI_ExecServerG_00568938(EEContext&);  // generated body
void fn_RFMAI_ExecServerG_00568938__recomp(EEContext&);  // recompiled
void fn_sub_568BC8_00568bc8(EEContext&);  // generated body
void fn_sub_568BC8_00568bc8__recomp(EEContext&);  // recompiled
void fn_rfmai_getEntryFromFname_00568c18(EEContext&);  // generated body
void fn_rfmai_getEntryFromFname_00568c18__recomp(EEContext&);  // recompiled
void fn_sub_568DB0_00568db0(EEContext&);  // generated body
void fn_sub_568DB0_00568db0__recomp(EEContext&);  // recompiled
void fn_RFMAI_SetDirG_00569058(EEContext&);  // generated body
void fn_RFMAI_SetDirG_00569058__recomp(EEContext&);  // recompiled
void fn_RFDIR_GetDirEnt_0056c0f8(EEContext&);  // generated body
void fn_RFDIR_GetDirEnt_0056c0f8__recomp(EEContext&);  // recompiled
void fn_ROCI_ExecServer_0056c8c8(EEContext&);  // generated body
void fn_ROCI_ExecServer_0056c8c8__recomp(EEContext&);  // recompiled
void fn_sub_56C8E8_0056c8e8(EEContext&);  // generated body
void fn_sub_56C8E8_0056c8e8__recomp(EEContext&);  // recompiled
void fn_ROCI_Open_0056c900(EEContext&);  // generated body
void fn_ROCI_Open_0056c900__recomp(EEContext&);  // recompiled
void fn_sub_56C918_0056c918(EEContext&);  // generated body
void fn_sub_56C918_0056c918__recomp(EEContext&);  // recompiled
void fn_sub_56C930_0056c930(EEContext&);  // generated body
void fn_sub_56C930_0056c930__recomp(EEContext&);  // recompiled
void fn_sub_56C970_0056c970(EEContext&);  // generated body
void fn_sub_56C970_0056c970__recomp(EEContext&);  // recompiled
void fn_ROCI_ReqRd_0056c988(EEContext&);  // generated body
void fn_ROCI_ReqRd_0056c988__recomp(EEContext&);  // recompiled
void fn_ROCI_GetStat_0056c9b8(EEContext&);  // generated body
void fn_ROCI_GetStat_0056c9b8__recomp(EEContext&);  // recompiled
void fn_roci_optAddVolume_0056cab0(EEContext&);  // generated body
void fn_roci_optAddVolume_0056cab0__recomp(EEContext&);  // recompiled
void fn_ROCI_OptFn1_0056cbb8(EEContext&);  // generated body
void fn_ROCI_OptFn1_0056cbb8__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"_sceExitThread", 0x100220, &recomp_gen::fn__sceExitThread_00100220, &recomp_gen::fn__sceExitThread_00100220__recomp},
    {"H_FileSetup_UpdateTstDvdChkDrawTask", 0x1934F0, &recomp_gen::fn_H_FileSetup_UpdateTstDvdChkDrawTask_001934f0, &recomp_gen::fn_H_FileSetup_UpdateTstDvdChkDrawTask_001934f0__recomp},
    {"sub_344EB0", 0x344EB0, &recomp_gen::fn_sub_344EB0_00344eb0, &recomp_gen::fn_sub_344EB0_00344eb0__recomp},
    {"sub_344FC0", 0x344FC0, &recomp_gen::fn_sub_344FC0_00344fc0, &recomp_gen::fn_sub_344FC0_00344fc0__recomp},
    {"sub_46F400", 0x46F400, &recomp_gen::fn_sub_46F400_0046f400, &recomp_gen::fn_sub_46F400_0046f400__recomp},
    {"sub_470200", 0x470200, &recomp_gen::fn_sub_470200_00470200, &recomp_gen::fn_sub_470200_00470200__recomp},
    {"sub_470E10", 0x470E10, &recomp_gen::fn_sub_470E10_00470e10, &recomp_gen::fn_sub_470E10_00470e10__recomp},
    {"sub_473FB0", 0x473FB0, &recomp_gen::fn_sub_473FB0_00473fb0, &recomp_gen::fn_sub_473FB0_00473fb0__recomp},
    {"sub_474D30", 0x474D30, &recomp_gen::fn_sub_474D30_00474d30, &recomp_gen::fn_sub_474D30_00474d30__recomp},
    {"sub_476490", 0x476490, &recomp_gen::fn_sub_476490_00476490, &recomp_gen::fn_sub_476490_00476490__recomp},
    {"sub_476980", 0x476980, &recomp_gen::fn_sub_476980_00476980, &recomp_gen::fn_sub_476980_00476980__recomp},
    {"sub_47A510", 0x47A510, &recomp_gen::fn_sub_47A510_0047a510, &recomp_gen::fn_sub_47A510_0047a510__recomp},
    {"sub_47A710", 0x47A710, &recomp_gen::fn_sub_47A710_0047a710, &recomp_gen::fn_sub_47A710_0047a710__recomp},
    {"sub_47C240", 0x47C240, &recomp_gen::fn_sub_47C240_0047c240, &recomp_gen::fn_sub_47C240_0047c240__recomp},
    {"sub_47C8C0", 0x47C8C0, &recomp_gen::fn_sub_47C8C0_0047c8c0, &recomp_gen::fn_sub_47C8C0_0047c8c0__recomp},
    {"sub_47CFD0", 0x47CFD0, &recomp_gen::fn_sub_47CFD0_0047cfd0, &recomp_gen::fn_sub_47CFD0_0047cfd0__recomp},
    {"sub_47DE30", 0x47DE30, &recomp_gen::fn_sub_47DE30_0047de30, &recomp_gen::fn_sub_47DE30_0047de30__recomp},
    {"sub_47E9E0", 0x47E9E0, &recomp_gen::fn_sub_47E9E0_0047e9e0, &recomp_gen::fn_sub_47E9E0_0047e9e0__recomp},
    {"sub_47FB10", 0x47FB10, &recomp_gen::fn_sub_47FB10_0047fb10, &recomp_gen::fn_sub_47FB10_0047fb10__recomp},
    {"sub_480C30", 0x480C30, &recomp_gen::fn_sub_480C30_00480c30, &recomp_gen::fn_sub_480C30_00480c30__recomp},
    {"sub_481860", 0x481860, &recomp_gen::fn_sub_481860_00481860, &recomp_gen::fn_sub_481860_00481860__recomp},
    {"sub_482A50", 0x482A50, &recomp_gen::fn_sub_482A50_00482a50, &recomp_gen::fn_sub_482A50_00482a50__recomp},
    {"sub_483170", 0x483170, &recomp_gen::fn_sub_483170_00483170, &recomp_gen::fn_sub_483170_00483170__recomp},
    {"sub_4838E0", 0x4838E0, &recomp_gen::fn_sub_4838E0_004838e0, &recomp_gen::fn_sub_4838E0_004838e0__recomp},
    {"sub_485750", 0x485750, &recomp_gen::fn_sub_485750_00485750, &recomp_gen::fn_sub_485750_00485750__recomp},
    {"sub_490D40", 0x490D40, &recomp_gen::fn_sub_490D40_00490d40, &recomp_gen::fn_sub_490D40_00490d40__recomp},
    {"sub_49CC30", 0x49CC30, &recomp_gen::fn_sub_49CC30_0049cc30, &recomp_gen::fn_sub_49CC30_0049cc30__recomp},
    {"sub_4C08A0", 0x4C08A0, &recomp_gen::fn_sub_4C08A0_004c08a0, &recomp_gen::fn_sub_4C08A0_004c08a0__recomp},
    {"sub_4C0A70", 0x4C0A70, &recomp_gen::fn_sub_4C0A70_004c0a70, &recomp_gen::fn_sub_4C0A70_004c0a70__recomp},
    {"sub_4C0A80", 0x4C0A80, &recomp_gen::fn_sub_4C0A80_004c0a80, &recomp_gen::fn_sub_4C0A80_004c0a80__recomp},
    {"sub_4C0C50", 0x4C0C50, &recomp_gen::fn_sub_4C0C50_004c0c50, &recomp_gen::fn_sub_4C0C50_004c0c50__recomp},
    {"sub_4C0CF0", 0x4C0CF0, &recomp_gen::fn_sub_4C0CF0_004c0cf0, &recomp_gen::fn_sub_4C0CF0_004c0cf0__recomp},
    {"sub_4C0E70", 0x4C0E70, &recomp_gen::fn_sub_4C0E70_004c0e70, &recomp_gen::fn_sub_4C0E70_004c0e70__recomp},
    {"_dispRefImageField_0", 0x4C72E0, &recomp_gen::fn__dispRefImageField_0_004c72e0, &recomp_gen::fn__dispRefImageField_0_004c72e0__recomp},
    {"_rwDMAHandler", 0x4D4350, &recomp_gen::fn__rwDMAHandler_004d4350, &recomp_gen::fn__rwDMAHandler_004d4350__recomp},
    {"_rwDMAVSYNCHandler", 0x4D47F0, &recomp_gen::fn__rwDMAVSYNCHandler_004d47f0, &recomp_gen::fn__rwDMAVSYNCHandler_004d47f0__recomp},
    {"_rwDMAClosePkt", 0x4D4A60, &recomp_gen::fn__rwDMAClosePkt_004d4a60, &recomp_gen::fn__rwDMAClosePkt_004d4a60__recomp},
    {"_rwDMAForceBufferSwap", 0x4D4DF0, &recomp_gen::fn__rwDMAForceBufferSwap_004d4df0, &recomp_gen::fn__rwDMAForceBufferSwap_004d4df0__recomp},
    {"_rwDMAAddPkt", 0x4D5000, &recomp_gen::fn__rwDMAAddPkt_004d5000, &recomp_gen::fn__rwDMAAddPkt_004d5000__recomp},
    {"_rwDMAAddPURef", 0x4D51C0, &recomp_gen::fn__rwDMAAddPURef_004d51c0, &recomp_gen::fn__rwDMAAddPURef_004d51c0__recomp},
    {"_rwDMAOpenGIFPkt", 0x4D54E0, &recomp_gen::fn__rwDMAOpenGIFPkt_004d54e0, &recomp_gen::fn__rwDMAOpenGIFPkt_004d54e0__recomp},
    {"_rwDMAOpenVIFPkt", 0x4D59D0, &recomp_gen::fn__rwDMAOpenVIFPkt_004d59d0, &recomp_gen::fn__rwDMAOpenVIFPkt_004d59d0__recomp},
    {"sub_4D5E90", 0x4D5E90, &recomp_gen::fn_sub_4D5E90_004d5e90, &recomp_gen::fn_sub_4D5E90_004d5e90__recomp},
    {"sub_4D5FE0", 0x4D5FE0, &recomp_gen::fn_sub_4D5FE0_004d5fe0, &recomp_gen::fn_sub_4D5FE0_004d5fe0__recomp},
    {"sub_4D6250", 0x4D6250, &recomp_gen::fn_sub_4D6250_004d6250, &recomp_gen::fn_sub_4D6250_004d6250__recomp},
    {"_rwDMAHook", 0x4D6470, &recomp_gen::fn__rwDMAHook_004d6470, &recomp_gen::fn__rwDMAHook_004d6470__recomp},
    {"_rwDMAUnhook", 0x4D65A0, &recomp_gen::fn__rwDMAUnhook_004d65a0, &recomp_gen::fn__rwDMAUnhook_004d65a0__recomp},
    {"_rwDMADmaOpen", 0x4D67B0, &recomp_gen::fn__rwDMADmaOpen_004d67b0, &recomp_gen::fn__rwDMADmaOpen_004d67b0__recomp},
    {"_rwDMADmaClose", 0x4D6A50, &recomp_gen::fn__rwDMADmaClose_004d6a50, &recomp_gen::fn__rwDMADmaClose_004d6a50__recomp},
    {"_rwDMAPreAlloc", 0x4D6AB0, &recomp_gen::fn__rwDMAPreAlloc_004d6ab0, &recomp_gen::fn__rwDMAPreAlloc_004d6ab0__recomp},
    {"_rwSkyInitConfigSystem", 0x4D6B10, &recomp_gen::fn__rwSkyInitConfigSystem_004d6b10, &recomp_gen::fn__rwSkyInitConfigSystem_004d6b10__recomp},
    {"setInitialRenderState", 0x4DFDD0, &recomp_gen::fn_setInitialRenderState_004dfdd0, &recomp_gen::fn_setInitialRenderState_004dfdd0__recomp},
    {"SkyOpen", 0x4E01B0, &recomp_gen::fn_SkyOpen_004e01b0, &recomp_gen::fn_SkyOpen_004e01b0__recomp},
    {"sub_4E0540", 0x4E0540, &recomp_gen::fn_sub_4E0540_004e0540, &recomp_gen::fn_sub_4E0540_004e0540__recomp},
    {"SkyStart", 0x4E1060, &recomp_gen::fn_SkyStart_004e1060, &recomp_gen::fn_SkyStart_004e1060__recomp},
    {"sub_4E3630", 0x4E3630, &recomp_gen::fn_sub_4E3630_004e3630, &recomp_gen::fn_sub_4E3630_004e3630__recomp},
    {"sub_4EC510", 0x4EC510, &recomp_gen::fn_sub_4EC510_004ec510, &recomp_gen::fn_sub_4EC510_004ec510__recomp},
    {"_rwSkyOverloadPipelines", 0x4EEBC0, &recomp_gen::fn__rwSkyOverloadPipelines_004eebc0, &recomp_gen::fn__rwSkyOverloadPipelines_004eebc0__recomp},
    {"sub_4F0990", 0x4F0990, &recomp_gen::fn_sub_4F0990_004f0990, &recomp_gen::fn_sub_4F0990_004f0990__recomp},
    {"sceGsResetGraph", 0x4F8EB0, &recomp_gen::fn_sceGsResetGraph_004f8eb0, &recomp_gen::fn_sceGsResetGraph_004f8eb0__recomp},
    {"sceGsResetPath", 0x4F9050, &recomp_gen::fn_sceGsResetPath_004f9050, &recomp_gen::fn_sceGsResetPath_004f9050__recomp},
    {"sceGsPutDispEnv", 0x4F94E0, &recomp_gen::fn_sceGsPutDispEnv_004f94e0, &recomp_gen::fn_sceGsPutDispEnv_004f94e0__recomp},
    {"sceGsPutDrawEnv", 0x4F9850, &recomp_gen::fn_sceGsPutDrawEnv_004f9850, &recomp_gen::fn_sceGsPutDrawEnv_004f9850__recomp},
    {"sceGsSyncV", 0x4F9938, &recomp_gen::fn_sceGsSyncV_004f9938, &recomp_gen::fn_sceGsSyncV_004f9938__recomp},
    {"sceGsSyncPath", 0x4F99D0, &recomp_gen::fn_sceGsSyncPath_004f99d0, &recomp_gen::fn_sceGsSyncPath_004f99d0__recomp},
    {"sceGsExecStoreImage", 0x4F9E28, &recomp_gen::fn_sceGsExecStoreImage_004f9e28, &recomp_gen::fn_sceGsExecStoreImage_004f9e28__recomp},
    {"sceGsSyncVCallback", 0x4FA4B8, &recomp_gen::fn_sceGsSyncVCallback_004fa4b8, &recomp_gen::fn_sceGsSyncVCallback_004fa4b8__recomp},
    {"sceGsSwapDBuffDc", 0x4FA738, &recomp_gen::fn_sceGsSwapDBuffDc_004fa738, &recomp_gen::fn_sceGsSwapDBuffDc_004fa738__recomp},
    {"WaitDma", 0x4FA798, &recomp_gen::fn_WaitDma_004fa798, &recomp_gen::fn_WaitDma_004fa798__recomp},
    {"WatchDma", 0x4FA808, &recomp_gen::fn_WatchDma_004fa808, &recomp_gen::fn_WatchDma_004fa808__recomp},
    {"sceDmaReset", 0x4FA918, &recomp_gen::fn_sceDmaReset_004fa918, &recomp_gen::fn_sceDmaReset_004fa918__recomp},
    {"sceDmaPutEnv", 0x4FA9F8, &recomp_gen::fn_sceDmaPutEnv_004fa9f8, &recomp_gen::fn_sceDmaPutEnv_004fa9f8__recomp},
    {"sceDmaSend", 0x4FAC20, &recomp_gen::fn_sceDmaSend_004fac20, &recomp_gen::fn_sceDmaSend_004fac20__recomp},
    {"sceDmaSendN", 0x4FAC88, &recomp_gen::fn_sceDmaSendN_004fac88, &recomp_gen::fn_sceDmaSendN_004fac88__recomp},
    {"sceDmaRecvN", 0x4FADC0, &recomp_gen::fn_sceDmaRecvN_004fadc0, &recomp_gen::fn_sceDmaRecvN_004fadc0__recomp},
    {"sceDmaSync", 0x4FAEC0, &recomp_gen::fn_sceDmaSync_004faec0, &recomp_gen::fn_sceDmaSync_004faec0__recomp},
    {"sceDmaPause", 0x4FAF30, &recomp_gen::fn_sceDmaPause_004faf30, &recomp_gen::fn_sceDmaPause_004faf30__recomp},
    {"_motionVectors", 0x4FCB00, &recomp_gen::fn__motionVectors_004fcb00, &recomp_gen::fn__motionVectors_004fcb00__recomp},
    {"sub_4FD8A0", 0x4FD8A0, &recomp_gen::fn_sub_4FD8A0_004fd8a0, &recomp_gen::fn_sub_4FD8A0_004fd8a0__recomp},
    {"_pictureTemporalScalableExtension", 0x4FF7B8, &recomp_gen::fn__pictureTemporalScalableExtension_004ff7b8, &recomp_gen::fn__pictureTemporalScalableExtension_004ff7b8__recomp},
    {"_ch4dma", 0x502418, &recomp_gen::fn__ch4dma_00502418, &recomp_gen::fn__ch4dma_00502418__recomp},
    {"_sceMpegStopIpuDma", 0x502500, &recomp_gen::fn__sceMpegStopIpuDma_00502500, &recomp_gen::fn__sceMpegStopIpuDma_00502500__recomp},
    {"_sceMpegErrorBdec", 0x5025A0, &recomp_gen::fn__sceMpegErrorBdec_005025a0, &recomp_gen::fn__sceMpegErrorBdec_005025a0__recomp},
    {"setD3_CHCR", 0x502700, &recomp_gen::fn_setD3_CHCR_00502700, &recomp_gen::fn_setD3_CHCR_00502700__recomp},
    {"setD4_CHCR", 0x502778, &recomp_gen::fn_setD4_CHCR_00502778, &recomp_gen::fn_setD4_CHCR_00502778__recomp},
    {"sceIpuStopDMA", 0x5027F0, &recomp_gen::fn_sceIpuStopDMA_005027f0, &recomp_gen::fn_sceIpuStopDMA_005027f0__recomp},
    {"sceIpuRestartDMA", 0x5028D8, &recomp_gen::fn_sceIpuRestartDMA_005028d8, &recomp_gen::fn_sceIpuRestartDMA_005028d8__recomp},
    {"_sce_ExecPS2", 0x502DB0, &recomp_gen::fn__sce_ExecPS2_00502db0, &recomp_gen::fn__sce_ExecPS2_00502db0__recomp},
    {"_sce_DisableIntc", 0x502EB0, &recomp_gen::fn__sce_DisableIntc_00502eb0, &recomp_gen::fn__sce_DisableIntc_00502eb0__recomp},
    {"_sce_iEnableIntc", 0x502F00, &recomp_gen::fn__sce_iEnableIntc_00502f00, &recomp_gen::fn__sce_iEnableIntc_00502f00__recomp},
    {"_sce_iDisableIntc", 0x502F10, &recomp_gen::fn__sce_iDisableIntc_00502f10, &recomp_gen::fn__sce_iDisableIntc_00502f10__recomp},
    {"_sce_iEnableDmac", 0x502F20, &recomp_gen::fn__sce_iEnableDmac_00502f20, &recomp_gen::fn__sce_iEnableDmac_00502f20__recomp},
    {"_sce_iDisableDmac", 0x502F30, &recomp_gen::fn__sce_iDisableDmac_00502f30, &recomp_gen::fn__sce_iDisableDmac_00502f30__recomp},
    {"_sceDeleteThread", 0x502F70, &recomp_gen::fn__sceDeleteThread_00502f70, &recomp_gen::fn__sceDeleteThread_00502f70__recomp},
    {"_sceTerminateThread", 0x502FB0, &recomp_gen::fn__sceTerminateThread_00502fb0, &recomp_gen::fn__sceTerminateThread_00502fb0__recomp},
    {"_sceiChangeThreadPriority", 0x503000, &recomp_gen::fn__sceiChangeThreadPriority_00503000, &recomp_gen::fn__sceiChangeThreadPriority_00503000__recomp},
    {"_sceRotateThreadReadyQueue", 0x503010, &recomp_gen::fn__sceRotateThreadReadyQueue_00503010, &recomp_gen::fn__sceRotateThreadReadyQueue_00503010__recomp},
    {"_sce_iSuspendThread", 0x5030E0, &recomp_gen::fn__sce_iSuspendThread_005030e0, &recomp_gen::fn__sce_iSuspendThread_005030e0__recomp},
    {"_sceGsGetIMR", 0x503480, &recomp_gen::fn__sceGsGetIMR_00503480, &recomp_gen::fn__sceGsGetIMR_00503480__recomp},
    {"_sceSetVSyncFlag", 0x5034D0, &recomp_gen::fn__sceSetVSyncFlag_005034d0, &recomp_gen::fn__sceSetVSyncFlag_005034d0__recomp},
    {"_isceSifSetDma", 0x503530, &recomp_gen::fn__isceSifSetDma_00503530, &recomp_gen::fn__isceSifSetDma_00503530__recomp},
    {"_sceGetMemorySize", 0x5035C0, &recomp_gen::fn__sceGetMemorySize_005035c0, &recomp_gen::fn__sceGetMemorySize_005035c0__recomp},
    {"_sce_InitTLB", 0x5035D0, &recomp_gen::fn__sce_InitTLB_005035d0, &recomp_gen::fn__sce_InitTLB_005035d0__recomp},
    {"VSync2", 0x503680, &recomp_gen::fn_VSync2_00503680, &recomp_gen::fn_VSync2_00503680__recomp},
    {"DisableIntc", 0x503C40, &recomp_gen::fn_DisableIntc_00503c40, &recomp_gen::fn_DisableIntc_00503c40__recomp},
    {"DelayThread", 0x5041D8, &recomp_gen::fn_DelayThread_005041d8, &recomp_gen::fn_DelayThread_005041d8__recomp},
    {"_sceRpcGetFPacket2", 0x506B68, &recomp_gen::fn__sceRpcGetFPacket2_00506b68, &recomp_gen::fn__sceRpcGetFPacket2_00506b68__recomp},
    {"sceFsSifCallRpc", 0x507AD8, &recomp_gen::fn_sceFsSifCallRpc_00507ad8, &recomp_gen::fn_sceFsSifCallRpc_00507ad8__recomp},
    {"sceSifFreeIopHeap", 0x50B788, &recomp_gen::fn_sceSifFreeIopHeap_0050b788, &recomp_gen::fn_sceSifFreeIopHeap_0050b788__recomp},
    {"_sceSifLoadModuleBuffer", 0x50BCB0, &recomp_gen::fn__sceSifLoadModuleBuffer_0050bcb0, &recomp_gen::fn__sceSifLoadModuleBuffer_0050bcb0__recomp},
    {"_sceSifLoadElfPart", 0x50C528, &recomp_gen::fn__sceSifLoadElfPart_0050c528, &recomp_gen::fn__sceSifLoadElfPart_0050c528__recomp},
    {"_kDebugException", 0x50D280, &recomp_gen::fn__kDebugException_0050d280, &recomp_gen::fn__kDebugException_0050d280__recomp},
    {"sceCdGetDiskType2", 0x510E30, &recomp_gen::fn_sceCdGetDiskType2_00510e30, &recomp_gen::fn_sceCdGetDiskType2_00510e30__recomp},
    {"sceDbcDeleteSocket", 0x51C8A0, &recomp_gen::fn_sceDbcDeleteSocket_0051c8a0, &recomp_gen::fn_sceDbcDeleteSocket_0051c8a0__recomp},
    {"adxt_ExecFsSvr", 0x53E0E0, &recomp_gen::fn_adxt_ExecFsSvr_0053e0e0, &recomp_gen::fn_adxt_ExecFsSvr_0053e0e0__recomp},
    {"adxm_fs_proc", 0x53FCF8, &recomp_gen::fn_adxm_fs_proc_0053fcf8, &recomp_gen::fn_adxm_fs_proc_0053fcf8__recomp},
    {"SRD_ReqRdDvd", 0x557B80, &recomp_gen::fn_SRD_ReqRdDvd_00557b80, &recomp_gen::fn_SRD_ReqRdDvd_00557b80__recomp},
    {"srd_check_dvd_error", 0x557FE8, &recomp_gen::fn_srd_check_dvd_error_00557fe8, &recomp_gen::fn_srd_check_dvd_error_00557fe8__recomp},
    {"sub_558DD0", 0x558DD0, &recomp_gen::fn_sub_558DD0_00558dd0, &recomp_gen::fn_sub_558DD0_00558dd0__recomp},
    {"DTR_ExecServer", 0x559140, &recomp_gen::fn_DTR_ExecServer_00559140, &recomp_gen::fn_DTR_ExecServer_00559140__recomp},
    {"DTR_Stop", 0x5593A8, &recomp_gen::fn_DTR_Stop_005593a8, &recomp_gen::fn_DTR_Stop_005593a8__recomp},
    {"sub_559938", 0x559938, &recomp_gen::fn_sub_559938_00559938, &recomp_gen::fn_sub_559938_00559938__recomp},
    {"sub_55F748", 0x55F748, &recomp_gen::fn_sub_55F748_0055f748, &recomp_gen::fn_sub_55F748_0055f748__recomp},
    {"PS2RNA_Init", 0x55FF70, &recomp_gen::fn_PS2RNA_Init_0055ff70, &recomp_gen::fn_PS2RNA_Init_0055ff70__recomp},
    {"sub_564528", 0x564528, &recomp_gen::fn_sub_564528_00564528, &recomp_gen::fn_sub_564528_00564528__recomp},
    {"RFHN_WaitCompleteReq", 0x5658B8, &recomp_gen::fn_RFHN_WaitCompleteReq_005658b8, &recomp_gen::fn_RFHN_WaitCompleteReq_005658b8__recomp},
    {"rfmai_addVolList", 0x5672C8, &recomp_gen::fn_rfmai_addVolList_005672c8, &recomp_gen::fn_rfmai_addVolList_005672c8__recomp},
    {"rfmai_getCvmfInfo", 0x5674C0, &recomp_gen::fn_rfmai_getCvmfInfo_005674c0, &recomp_gen::fn_rfmai_getCvmfInfo_005674c0__recomp},
    {"rfmai_readPvd", 0x5676B0, &recomp_gen::fn_rfmai_readPvd_005676b0, &recomp_gen::fn_rfmai_readPvd_005676b0__recomp},
    {"sub_567AF0", 0x567AF0, &recomp_gen::fn_sub_567AF0_00567af0, &recomp_gen::fn_sub_567AF0_00567af0__recomp},
    {"RFMAI_MountG", 0x567C58, &recomp_gen::fn_RFMAI_MountG_00567c58, &recomp_gen::fn_RFMAI_MountG_00567c58__recomp},
    {"sub_568098", 0x568098, &recomp_gen::fn_sub_568098_00568098, &recomp_gen::fn_sub_568098_00568098__recomp},
    {"RFMAI_SetDefVolumeG", 0x568280, &recomp_gen::fn_RFMAI_SetDefVolumeG_00568280, &recomp_gen::fn_RFMAI_SetDefVolumeG_00568280__recomp},
    {"RFMAI_OpenG", 0x568388, &recomp_gen::fn_RFMAI_OpenG_00568388, &recomp_gen::fn_RFMAI_OpenG_00568388__recomp},
    {"RFMAI_ExecServerG", 0x568938, &recomp_gen::fn_RFMAI_ExecServerG_00568938, &recomp_gen::fn_RFMAI_ExecServerG_00568938__recomp},
    {"sub_568BC8", 0x568BC8, &recomp_gen::fn_sub_568BC8_00568bc8, &recomp_gen::fn_sub_568BC8_00568bc8__recomp},
    {"rfmai_getEntryFromFname", 0x568C18, &recomp_gen::fn_rfmai_getEntryFromFname_00568c18, &recomp_gen::fn_rfmai_getEntryFromFname_00568c18__recomp},
    {"sub_568DB0", 0x568DB0, &recomp_gen::fn_sub_568DB0_00568db0, &recomp_gen::fn_sub_568DB0_00568db0__recomp},
    {"RFMAI_SetDirG", 0x569058, &recomp_gen::fn_RFMAI_SetDirG_00569058, &recomp_gen::fn_RFMAI_SetDirG_00569058__recomp},
    {"RFDIR_GetDirEnt", 0x56C0F8, &recomp_gen::fn_RFDIR_GetDirEnt_0056c0f8, &recomp_gen::fn_RFDIR_GetDirEnt_0056c0f8__recomp},
    {"ROCI_ExecServer", 0x56C8C8, &recomp_gen::fn_ROCI_ExecServer_0056c8c8, &recomp_gen::fn_ROCI_ExecServer_0056c8c8__recomp},
    {"sub_56C8E8", 0x56C8E8, &recomp_gen::fn_sub_56C8E8_0056c8e8, &recomp_gen::fn_sub_56C8E8_0056c8e8__recomp},
    {"ROCI_Open", 0x56C900, &recomp_gen::fn_ROCI_Open_0056c900, &recomp_gen::fn_ROCI_Open_0056c900__recomp},
    {"sub_56C918", 0x56C918, &recomp_gen::fn_sub_56C918_0056c918, &recomp_gen::fn_sub_56C918_0056c918__recomp},
    {"sub_56C930", 0x56C930, &recomp_gen::fn_sub_56C930_0056c930, &recomp_gen::fn_sub_56C930_0056c930__recomp},
    {"sub_56C970", 0x56C970, &recomp_gen::fn_sub_56C970_0056c970, &recomp_gen::fn_sub_56C970_0056c970__recomp},
    {"ROCI_ReqRd", 0x56C988, &recomp_gen::fn_ROCI_ReqRd_0056c988, &recomp_gen::fn_ROCI_ReqRd_0056c988__recomp},
    {"ROCI_GetStat", 0x56C9B8, &recomp_gen::fn_ROCI_GetStat_0056c9b8, &recomp_gen::fn_ROCI_GetStat_0056c9b8__recomp},
    {"roci_optAddVolume", 0x56CAB0, &recomp_gen::fn_roci_optAddVolume_0056cab0, &recomp_gen::fn_roci_optAddVolume_0056cab0__recomp},
    {"ROCI_OptFn1", 0x56CBB8, &recomp_gen::fn_ROCI_OptFn1_0056cbb8, &recomp_gen::fn_ROCI_OptFn1_0056cbb8__recomp},
};

// The world: 64 KiB of free RAM above the harness's arena (TODO: the function's real structures).
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 64;

}  // namespace

TEST_CASE("game(libs25): every body equals its recompiled body on random worlds") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const char* env = std::getenv("P3FES_HG_SEEDS");  // more (or fewer) pairs per function
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : kSeeds;
    const char* only = std::getenv("P3FES_HG_ONLY");     // one function by name (debugging)
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;  // name and seed of every pair on stderr
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        int stops = 0;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s seed %u\n", c.name, seed);
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(*m, kWorld, kWorldSize, rng);
            const Args args{hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize),
                            hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize)};
            stops += hgp::pair(*m, c.hand, c.recomp, args, seed, c.name).stopped ? 1 : 0;
        }
        const std::string summary = std::string(c.name) + ": " + std::to_string(seeds) + " pairs, " + std::to_string(stops) + " stopped early";
        MESSAGE(summary);
    }
}

namespace {

constexpr u32 kRec = 0x01820000u;  // a built record of small values / pointers back into it (8 KiB)
constexpr u32 kOut = 0x01822000u;  // out-parameters (8 KiB)
const char* const kSnaps[] = {"dorm_replay_4900", "b_5800", "climb_ref_17000", "fusion_ref_6300", "shop_ref_4100"};

// The game state these bodies read (symbols/ globals).
constexpr u32 kRofsWork = 0x7B2700u;  // g_rofs_work: the ROFS work area (handles 60 bytes each from +4236, volumes at +40)
constexpr u32 kRnaTable = 0x7AB850u;  // PS2RNA handles, 16 x 100 bytes
constexpr u32 kRwDmaOpen = 0x7CE958u; // the RW DMA system's open flag (_rwDMAPreAlloc refuses while it is set)

u32 r32(Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.at(va), 4);
    return v;
}
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
bool ram_ptr(u32 p) { return p >= 0x100000u && p < 0x01FF0000u; }

const Case& by_name(const char* name) {
    for (const Case& c : kCases)
        if (std::string(c.name) == name) return c;
    FAIL("no case " << name);
    return kCases[0];
}

// Idle hardware: every DMA channel's CHCR reads 0 (stopped), D_STAT reads every channel's done bit, the GS CSR reads
// the FINISH / VSINT bits, the VIF / GIF status registers read empty. Writes update the map, so a fixed number of idle
// reads is scripted first (a wait loop then sees what the body wrote, and the runaway cut ends both runs alike).
HwCheck idle_hw() {
    HwCheck hw;
    const std::vector<u64> zeros(512, 0);
    for (const u32 ch : {0x10008000u, 0x10009000u, 0x1000A000u, 0x1000B000u, 0x1000B400u, 0x1000C000u, 0x1000C400u,
                         0x1000D000u, 0x1000D400u})
        hw.reads[ch] = zeros;
    hw.reads[0x1000E010u] = std::vector<u64>(512, 0x3FFu);  // D_STAT: CIS0..CIS9
    hw.reads[0x12001000u] = std::vector<u64>(512, 0xAu);   // GS CSR: FINISH | VSINT
    for (const u32 st : {0x10003020u, 0x10003800u, 0x10003C00u}) hw.reads[st] = zeros;  // GIF_STAT, VIF0/1_STAT
    return hw;
}

// One pair on a long-lived BaseRange (write_tracker.h): the snapshot's 32 MiB stay the base and restore() copies back
// only the pages a pair wrote. The comparison is hgp::pair's.
hgp::Run pr_base(Machine& m, BaseRange& ram, const Case& c, const Args& args, u32 seed, const HwCheck& hw) {
    const std::vector<u8> spr(m.mem.scratchpad(), m.mem.scratchpad() + 0x4000);
    ram.begin();
    hgp::Run h = hgp::run_one(m, c.hand, args, seed, hw);
    std::vector<u8> bios_h;
    if (!hgp::bios_clean(m)) {
        bios_h.assign(m.mem.bios(), m.mem.bios() + EEMemory::kBiosSize);
        std::memset(m.mem.bios(), 0, EEMemory::kBiosSize);
    }
    ram.between();
    std::memcpy(m.mem.scratchpad(), spr.data(), spr.size());
    hgp::Run r = hgp::run_one(m, c.recomp, args, seed, hw);
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

// The records a snapshot holds for these bodies: the ROFS work area, its open handles and volumes, the used PS2RNA
// slots; then the built record and a few sizes (the RW DMA packet openers take a size in $a0).
std::vector<u32> snapshot_records(Machine& m) {
    std::vector<u32> recs{0u, 16u, 0x80u, kRec};
    const auto add = [&](u32 p) {
        if (ram_ptr(p) && std::find(recs.begin(), recs.end(), p) == recs.end()) recs.push_back(p);
    };
    const u32 work = r32(m, kRofsWork);
    if (ram_ptr(work)) {
        add(work);
        const u32 handles = std::min(r32(m, work + 4), 4u);
        for (u32 i = 0; i < handles; ++i) add(work + 4236 + 60 * i);
        add(r32(m, work + 40));
    }
    add(kRnaTable);
    for (u32 i = 1; i < 16; ++i)
        if (m.at(kRnaTable + 100 * i)[0] != 0) add(kRnaTable + 100 * i);
    return recs;
}

void build_record(Machine& m) {
    std::memset(m.at(kRec), 0, 0x4000);
    for (u32 i = 0; i < 0x2000; i += 4) w32(m, kRec + i, (i / 4) % 5 == 0 ? kRec + ((i * 7) & 0x1FF0u) : (i / 4) % 7);
}

}  // namespace

TEST_CASE("game(libs25): every body equals its recompiled body on idle hardware") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const char* env = std::getenv("P3FES_HG_SEEDS");
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : 16u;
    const char* only = std::getenv("P3FES_HG_ONLY");
    const HwCheck hw = idle_hw();
    int total = 0, stops = 0;
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            std::mt19937 rng{seed * 104729u + c.addr};
            hgp::random_world(*m, kWorld, kWorldSize, rng);
            // sizes and counts the bodies loop over stay small (multiples of 16 for the quadword loops)
            const u64 size = (rng() % 64) * 16u;
            const Args args{hgp::random_arg(rng, kWorld, kWorldSize), rng() % 2 ? size : hgp::random_arg(rng, kWorld, kWorldSize),
                            sx(kWorld + ((rng() % 0x4000u) & ~15u)), hgp::random_arg(rng, kWorld, kWorldSize)};
            stops += hgp::pair(*m, c.hand, c.recomp, args, seed, c.name, hw).stopped ? 1 : 0;
            ++total;
        }
    }
    MESSAGE(total << " pairs on idle hardware, " << stops << " stopped early (identically)");
}

// The replay snapshots hold the RW Sky driver's DMA ring and flip state, ROFS over the CVM image (g_rofs_work, its
// handles and volumes) and the PS2RNA table as the game leaves them. Every body runs on each snapshot with a0 from those
// records (and null, sizes, a built record), a1 from the values its branches test and out pointers in a2 / a3, on the
// scripted bus and on idle hardware; each pair starts from the snapshot.
TEST_CASE("game(libs25): every body on the replay snapshots") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const char* only = std::getenv("P3FES_HG_ONLY");
    const HwCheck idle = idle_hw();
    const HwCheck plain{};
    int runs = 0, stops = 0, snaps = 0;
    std::size_t records = 0;
    for (const char* dir : kSnaps) {
        const std::vector<u8> snap = read_snapshot(dir);
        if (snap.size() != EEMemory::kMainRamSize) {
            MESSAGE("SKIP: snapshot " << dir << " not found");
            continue;
        }
        ++snaps;
        std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
        build_record(*m);
        const std::vector<u32> recs = snapshot_records(*m);
        records += recs.size();
        BaseRange base(m->mem.main_ram(), m->mem.main_ram() + EEMemory::kMainRamSize);
        for (const Case& c : kCases) {
            if (only && std::string(only) != c.name) continue;
            u32 seed = 1;
            for (const u32 rec : recs)
                for (const u64 a1 : {0ull, 1ull, 2ull, 16ull, ~0ull, u64{kOut}}) {
                    const HwCheck& hw = (seed & 1) ? idle : plain;
                    const hgp::Run r = pr_base(*m, base, c, Args{sx(rec), a1, sx(kOut + 0x100), sx(kOut + 0x200)}, seed++, hw);
                    base.restore();
                    ++runs;
                    stops += r.stopped ? 1 : 0;
                }
        }
    }
    std::memset(m->mem.main_ram(), 0, EEMemory::kMainRamSize);
    MESSAGE(runs << " pairs from " << snaps << " snapshots (" << records << " records), " << stops << " stopped identically");
}

// Documented rules on the host, from the instructions (both bodies run and are compared, then the result checked).
// Only leaf bodies and the kernel stubs: nothing here depends on a callee's state.
TEST_CASE("game(libs25): kernel call numbers, 2D flag rules, RPC packet pool, DMA pre-allocation, scratchpad fill") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const auto v0 = [](const hgp::Run& r) { return r.end.gpr[GPR_V0].u64[0]; };
    // The kernel stubs: $v1 = the call number (negative for the interrupt-context i* calls), one syscall, return.
    {
        struct Stub {
            const char* name;
            s64 number;
        };
        const Stub kStubs[] = {{"_sce_ExecPS2", 7},         {"_sce_DisableIntc", 21},         {"_sce_iEnableIntc", -26},
                               {"_sce_iDisableIntc", -27},  {"_sce_iEnableDmac", -28},        {"_sce_iDisableDmac", -29},
                               {"_sceDeleteThread", 33},     {"_sceTerminateThread", 37},      {"_sceiChangeThreadPriority", -42},
                               {"_sceRotateThreadReadyQueue", 43}, {"_sce_iSuspendThread", -56}, {"_sceGsGetIMR", 112},
                               {"_sceSetVSyncFlag", 115},    {"_isceSifSetDma", -119},         {"_sceGetMemorySize", 127},
                               {"_sce_InitTLB", 130}};
        for (const Stub& s : kStubs) {
            const Case& c = by_name(s.name);
            const hgp::Run r = hgp::pair(*m, c.hand, c.recomp, Args{1, 2, 3, 4}, 1, c.name);
            INFO(s.name);
            CHECK_FALSE(r.stopped);
            CHECK(r.syscalls == 1);
            CHECK(static_cast<s64>(r.end.gpr[3].u64[0]) == s.number);
            CHECK(v0(r) == 0x600DF00Du);  // the harness's syscall result, passed through
        }
    }
    // sub_473FB0: of each exclusive pair the later flag wins; bit 0 is set when neither bit 0 nor bit 3 is; 0x10000000
    // is added when neither 0x10000000 nor 0x20000000 is set.
    {
        const Case& c = by_name("sub_473FB0");
        const auto norm = [&](u64 f) { return v0(hgp::pair(*m, c.hand, c.recomp, Args{f, 0, 0, 0}, 1, c.name)); };
        CHECK(norm(0) == 0x10000001u);
        CHECK(norm(0x20000000u) == 0x20000001u);
        CHECK(norm(0x10000008u) == 0x10000008u);
        CHECK(norm(0x10000009u) == 0x10000008u);           // bit 3 clears bit 0
        CHECK(norm(0x1000000Cu) == 0x10000008u);           // bit 3 clears bit 2
        CHECK(norm(0x10000028u) == 0x10000008u);           // bit 3 clears 0x20
        CHECK(norm(0x10020021u) == (0x00020000u | 0x10000000u));  // 0x20 with 0x20000: only 0x20000 survives, then the 0x1... default
    }
    // _sceRpcGetFPacket2: packet n of the client's pool (base +28, count +32) is base + 64 n.
    {
        const Case& c = by_name("_sceRpcGetFPacket2");
        w32(*m, kOut + 28, 0x01830000u);
        w32(*m, kOut + 32, 4);
        for (u64 n : {0ull, 1ull, 3ull}) {
            const hgp::Run r = hgp::pair(*m, c.hand, c.recomp, Args{sx(kOut), n, 0, 0}, 1, c.name);
            CHECK_FALSE(r.stopped);
            CHECK(v0(r) == 0x01830000u + 64u * n);
        }
    }
    // sub_4E3630: the word at 0x7CEA70.
    {
        const Case& c = by_name("sub_4E3630");
        w32(*m, 0x7CEA70u, 0x1234567u);
        CHECK(v0(hgp::pair(*m, c.hand, c.recomp, Args{0, 0, 0, 0}, 1, c.name)) == 0x1234567u);
    }
    // _rwDMAPreAlloc: refused (0) while the DMA system is open or for a size that is not 128-byte aligned; otherwise the
    // buffer and size are stored and the result is 1.
    {
        const Case& c = by_name("_rwDMAPreAlloc");
        w32(*m, kRwDmaOpen, 1);
        CHECK(v0(hgp::pair(*m, c.hand, c.recomp, Args{sx(kOut), 64, 0x1000, 0}, 1, c.name)) == 0u);
        w32(*m, kRwDmaOpen, 0);
        CHECK(v0(hgp::pair(*m, c.hand, c.recomp, Args{sx(kOut), 64, 0x1010, 0}, 2, c.name)) == 0u);
        CHECK(v0(hgp::pair(*m, c.hand, c.recomp, Args{sx(kOut), 64, 0x1000, 0}, 3, c.name)) == 1u);
        CHECK(r32(*m, 0x7CE964u) == 0x1000u);
        CHECK(r32(*m, 0x7CE968u) == kOut);
    }
    // sub_476490: the 64-bit pattern at *a2 fills the whole scratchpad before the fromSPR copies start.
    {
        const Case& c = by_name("sub_476490");
        const u64 pattern = 0x0123456789ABCDEFull;
        std::memcpy(m->at(kOut), &pattern, 8);
        const hgp::Run r = hgp::pair(*m, c.hand, c.recomp, Args{sx(kRec), 0x100, sx(kOut), 0}, 1, c.name, idle_hw());
        u64 first = 0, last = 0;
        std::memcpy(&first, r.spr.data(), 8);
        std::memcpy(&last, r.spr.data() + 0x3FF8, 8);
        CHECK(first == pattern);
        CHECK(last == pattern);
    }
}

#else

TEST_CASE("game(libs25): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
